/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ଅନ୍ତର୍ଭାଵ "channel_layout.h"
#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "buffer.h"
#ଅନ୍ତର୍ଭାଵ "dict.h"
#ଅନ୍ତର୍ଭାଵ "frame.h"
#ଅନ୍ତର୍ଭାଵ "frame_internal.h"
#ଅନ୍ତର୍ଭାଵ "imgutils.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "refstruct.h"
#ଅନ୍ତର୍ଭାଵ "samplefmt.h"
#ଅନ୍ତର୍ଭାଵ "side_data.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"

ସ୍ଥିର ଶୂନ୍ୟ get_frame_defaults(AVFrame *frame)
{
    memset(frame, 0, ଆକାର(*frame));

    frame->pts                   =
    frame->pkt_dts               = AV_NOPTS_ମୂଲ୍ୟ;
    frame->best_effort_timestamp = AV_NOPTS_ମୂଲ୍ୟ;
    frame->duration            = 0;
    frame->time_base           = (AVRational){ 0, 1 };
    frame->sample_aspect_ratio = (AVRational){ 0, 1 };
    frame->format              = -1; /* unknown */
    frame->extended_data       = frame->data;
    frame->color_primaries     = AVCOL_PRI_UNSPECIFIED;
    frame->color_trc           = AVCOL_TRC_UNSPECIFIED;
    frame->colorspace          = AVCOL_SPC_UNSPECIFIED;
    frame->color_range         = AVCOL_RANGE_UNSPECIFIED;
    frame->chroma_location     = AVCHROMA_LOC_UNSPECIFIED;
    frame->alpha_mode          = AVALPHA_MODE_UNSPECIFIED;
    frame->flags               = 0;
}

AVFrame *av_frame_alloc(ଶୂନ୍ୟ)
{
    AVFrame *frame = av_malloc(ଆକାର(*frame));

    ଯଦି (!frame)
        ଫେରନ୍ତୁ ଖାଲି;

    get_frame_defaults(frame);

    ଫେରନ୍ତୁ frame;
}

ଶୂନ୍ୟ av_frame_free(AVFrame **frame)
{
    ଯଦି (!frame || !*frame)
        ଫେରନ୍ତୁ;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_frame_get_video_buffer(AVFrame *frame, ପୂର୍ଣ୍ଣସଂଖ୍ୟା align,
                              AVBufferRef *(*alloc)(ଶୂନ୍ୟ *opaque, size_t size),
                              ଶୂନ୍ୟ *opaque)
{
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, padded_height;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    ଯଦି (!desc)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି ((ret = av_image_check_size(frame->width, frame->height, 0, ଖାଲି)) < 0)
        ଫେରନ୍ତୁ ret;

    ଯଦି (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    ଯଦି (!frame->linesize[0]) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            ଯଦି (ret < 0)
                ଫେରନ୍ତୁ ret;
            ଯଦି (!(frame->linesize[0] & (align-1)))
                ଭାଙ୍ଗ;
        }

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    ଯଦି ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        ଫେରନ୍ତୁ ret;

    total_size = 4 * plane_padding + 4 * align;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 4; i++) {
        ଯଦି (sizes[i] > SIZE_MAX - total_size)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    ଯଦି (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    ଯଦି ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        ଯାଅ fail;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 1; i < 4; i++) {
        ଯଦି (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    ଫେରନ୍ତୁ 0;
fail:
    av_frame_unref(frame);
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_audio_buffer(AVFrame *frame, ପୂର୍ଣ୍ଣସଂଖ୍ୟା align)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା planar   = av_sample_fmt_is_planar(frame->format);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା channels, planes;
    size_t size;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    ଯଦି (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
    }

    ଯଦି (align <= 0)
        align = ALIGN;

    ଯଦି (planes > AV_ଅଙ୍କ_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          ଆକାର(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_ଅଙ୍କ_DATA_POINTERS,
                                          ଆକାର(*frame->extended_buf));
        ଯଦି (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_ଅଙ୍କ_DATA_POINTERS;
    } ଅନ୍ୟଥା
        frame->extended_data = frame->data;

    ଯଦି (frame->linesize[0] > SIZE_MAX - align)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FFMIN(planes, AV_ଅଙ୍କ_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        ଯଦି (!frame->buf[i]) {
            av_frame_unref(frame);
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes - AV_ଅଙ୍କ_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        ଯଦି (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_ଅଙ୍କ_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    ଫେରନ୍ତୁ 0;

}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_frame_get_buffer(AVFrame *frame, ପୂର୍ଣ୍ଣସଂଖ୍ୟା align)
{
    ଯଦି (frame->format < 0)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (frame->width > 0 && frame->height > 0)
        ଫେରନ୍ତୁ ff_frame_get_video_buffer(frame, align, ଖାଲି, ଖାଲି);
    ଅନ୍ୟଥା ଯଦି (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        ଫେରନ୍ତୁ get_audio_buffer(frame, align);

    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା frame_copy_props(AVFrame *dst, ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ratio    = src->sample_aspect_ratio;
    dst->crop_ଶୀର୍ଷ               = src->crop_ଶୀର୍ଷ;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_ବାମ              = src->crop_ବାମ;
    dst->crop_ଡାହାଣ             = src->crop_ଡାହାଣ;
    dst->pts                    = src->pts;
    dst->duration               = src->duration;
    dst->repeat_pict            = src->repeat_pict;
    dst->sample_rate            = src->sample_rate;
    dst->opaque                 = src->opaque;
    dst->pkt_dts                = src->pkt_dts;
    dst->time_base              = src->time_base;
    dst->quality                = src->quality;
    dst->best_effort_timestamp  = src->best_effort_timestamp;
    dst->flags                  = src->flags;
    dst->decode_error_flags     = src->decode_error_flags;
    dst->color_primaries        = src->color_primaries;
    dst->color_trc              = src->color_trc;
    dst->colorspace             = src->colorspace;
    dst->color_range            = src->color_range;
    dst->chroma_location        = src->chroma_location;
    dst->alpha_mode             = src->alpha_mode;

    av_dict_copy(&dst->metadata, src->metadata, 0);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < src->nb_side_data; i++) {
        ଅଚଳ AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        ଯଦି (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            ଜାରି;
        ଯଦି (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            ଯଦି (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } ଅନ୍ୟଥା {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            ଯଦି (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    ଫେରନ୍ତୁ av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_frame_ref(AVFrame *dst, ଅଚଳ AVFrame *src)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    /* duplicate the frame data if it's not refcounted */
    ଯଦି (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        ଯଦି (ret < 0)
            ଯାଅ fail;

        ret = av_frame_copy(dst, src);
        ଯଦି (ret < 0)
            ଯାଅ fail;

        ଫେରନ୍ତୁ 0;
    }

    /* ref the buffers */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ଯଦି (!src->buf[i])
            ଜାରି;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        ଯଦି (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            ଯାଅ fail;
        }
    }

    ଯଦି (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      ଆକାର(*dst->extended_buf));
        ଯଦି (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            ଯାଅ fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            ଯଦି (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                ଯାଅ fail;
            }
        }
    }

    ଯଦି (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        ଯଦି (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            ଯାଅ fail;
        }
    }

    /* duplicate extended data */
    ଯଦି (src->extended_data != src->data) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ch = dst->ch_layout.nb_channels;

        ଯଦି (ch <= 0 || ch > SIZE_MAX / ଆକାର(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            ଯାଅ fail;
        }

        dst->extended_data = av_memdup(src->extended_data, ଆକାର(*dst->extended_data) * ch);
        ଯଦି (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            ଯାଅ fail;
        }
    } ଅନ୍ୟଥା
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     ଆକାର(src->data));
    memcpy(dst->linesize, src->linesize, ଆକାର(src->linesize));

    ଫେରନ୍ତୁ 0;

fail:
    av_frame_unref(dst);
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_frame_replace(AVFrame *dst, ଅଚଳ AVFrame *src)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    ଯଦି (dst == src)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        ଯଦି (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            ଫେରନ୍ତୁ av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        ଯଦି (ret < 0)
            ଯାଅ fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    /* replace the buffers */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        ଯଦି (ret < 0)
            ଯାଅ fail;
    }

    ଯଦି (src->extended_buf) {
        ଯଦି (dst->nb_extended_buf != src->nb_extended_buf) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            ଶୂନ୍ୟ *tmp;

            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   ଆକାର(*dst->extended_buf));
            ଯଦି (!tmp) {
                ret = AVERROR(ENOMEM);
                ଯାଅ fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * ଆକାର(*dst->extended_buf));
        }

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            ଯଦି (ret < 0)
                ଯାଅ fail;
        }
    } ଅନ୍ୟଥା ଯଦି (dst->extended_buf) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    ଯଦି (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    ଯଦି (src->extended_data != src->data) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ch = dst->ch_layout.nb_channels;

        ଯଦି (ch <= 0 || ch > SIZE_MAX / ଆକାର(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            ଯାଅ fail;
        }

        dst->extended_data = av_memdup(src->extended_data, ଆକାର(*dst->extended_data) * ch);
        ଯଦି (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            ଯାଅ fail;
        }
    } ଅନ୍ୟଥା
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     ଆକାର(src->data));
    memcpy(dst->linesize, src->linesize, ଆକାର(src->linesize));

    ଫେରନ୍ତୁ 0;

fail:
    av_frame_unref(dst);
    ଫେରନ୍ତୁ ret;
}

AVFrame *av_frame_clone(ଅଚଳ AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    ଯଦି (!ret)
        ଫେରନ୍ତୁ ଖାଲି;

    ଯଦି (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    ଫେରନ୍ତୁ ret;
}

ଶୂନ୍ୟ av_frame_unref(AVFrame *frame)
{
    ଯଦି (!frame)
        ଫେରନ୍ତୁ;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    ଯଦି (frame->extended_data != frame->data)
        av_freep(&frame->extended_data);

    av_channel_layout_uninit(&frame->ch_layout);

    get_frame_defaults(frame);
}

ଶୂନ୍ୟ av_frame_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    *dst = *src;
    ଯଦି (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_frame_is_writable(AVFrame *frame)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 1;

    /* assume non-refcounted frames are not writable */
    ଯଦି (!frame->buf[0])
        ଫେରନ୍ତୁ 0;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        ଯଦି (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (av_frame_is_writable(frame))
        ଫେରନ୍ତୁ 0;

    memset(&tmp, 0, ଆକାର(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    ଯଦି (ret < 0) {
        av_frame_unref(&tmp);
        ଫେରନ୍ତୁ ret;
    }

    ଯଦି (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    ଅନ୍ୟଥା
        ret = av_frame_get_buffer(&tmp, 0);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ret = av_frame_copy(&tmp, frame);
    ଯଦି (ret < 0) {
        av_frame_unref(&tmp);
        ଫେରନ୍ତୁ ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    ଯଦି (ret < 0) {
        av_frame_unref(&tmp);
        ଫେରନ୍ତୁ ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    ଯଦି (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_frame_copy_props(AVFrame *dst, ଅଚଳ AVFrame *src)
{
    ଫେରନ୍ତୁ frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(ଅଚଳ AVFrame *frame, ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane)
{
    uintptr_t data;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes;

    ଯଦି (frame->nb_samples) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା channels = frame->ch_layout.nb_channels;
        ଯଦି (!channels)
            ଫେରନ୍ତୁ ଖାଲି;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } ଅନ୍ୟଥା
        planes = 4;

    ଯଦି (plane < 0 || plane >= planes || !frame->extended_data[plane])
        ଫେରନ୍ତୁ ଖାଲି;
    data = (uintptr_t)frame->extended_data[plane];

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        ଯଦି (data >= buf_begin && data < buf_begin + buf->size)
            ଫେରନ୍ତୁ buf;
    }
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        ଯଦି (data >= buf_begin && data < buf_begin + buf->size)
            ଫେରନ୍ତୁ buf;
    }
    ଫେରନ୍ତୁ ଖାଲି;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 ଗଣନା AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    ଫେରନ୍ତୁ
        ff_frame_side_data_add_from_buf(
            &frame->side_data, &frame->nb_side_data, type, buf);
}

AVFrameSideData *av_frame_new_side_data(AVFrame *frame,
                                        ଗଣନା AVFrameSideDataType type,
                                        size_t size)
{
    AVFrameSideData *ret;
    AVBufferRef *buf = av_buffer_alloc(size);
    ret = av_frame_new_side_data_from_buf(frame, type, buf);
    ଯଦି (!ret)
        av_buffer_unref(&buf);
    ଫେରନ୍ତୁ ret;
}

AVFrameSideData *av_frame_get_side_data(ଅଚଳ AVFrame *frame,
                                        ଗଣନା AVFrameSideDataType type)
{
    ଫେରନ୍ତୁ (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା frame_copy_video(AVFrame *dst, ଅଚଳ AVFrame *src)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes;

    ଯଦି (dst->width  < src->width ||
        dst->height < src->height)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (src->hw_frames_ctx || dst->hw_frames_ctx)
        ଫେରନ୍ତୁ av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_ଗଣନା_planes(dst->format);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++)
        ଯଦି (!dst->data[i] || !src->data[i])
            ଫେରନ୍ତୁ AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା frame_copy_audio(AVFrame *dst, ଅଚଳ AVFrame *src)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା planar   = av_sample_fmt_is_planar(dst->format);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା channels = dst->ch_layout.nb_channels;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes   = planar ? channels : 1;

    ଯଦି (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < planes; i++)
        ଯଦି (!dst->extended_data[i] || !src->extended_data[i])
            ଫେରନ୍ତୁ AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_frame_copy(AVFrame *dst, ଅଚଳ AVFrame *src)
{
    ଯଦି (dst->format != src->format || dst->format < 0)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (dst->width > 0 && dst->height > 0)
        ଫେରନ୍ତୁ frame_copy_video(dst, src);
    ଅନ୍ୟଥା ଯଦି (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        ଫେରନ୍ତୁ frame_copy_audio(dst, src);

    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ଶୂନ୍ୟ av_frame_remove_side_data(AVFrame *frame, ଗଣନା AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା calc_cropping_offsets(size_t offsets[4], ଅଚଳ AVFrame *frame,
                                 ଅଚଳ AVPixFmtDescriptor *desc)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; frame->data[i]; i++) {
        ଅଚଳ AVComponentDescriptor *comp = ଖାଲି;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        ଯଦି (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            ଭାଙ୍ଗ;
        }

        /* find any component descriptor for this plane */
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < desc->nb_components; j++) {
            ଯଦି (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (!comp)
            ଫେରନ୍ତୁ AVERROR_BUG;

        offsets[i] = (frame->crop_ଶୀର୍ଷ  >> shift_y) * frame->linesize[i] +
                     (frame->crop_ବାମ >> shift_x) * comp->step;
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_frame_apply_cropping(AVFrame *frame, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଅଚଳ AVPixFmtDescriptor *desc;
    size_t offsets[4];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!(frame->width > 0 && frame->height > 0))
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (frame->crop_ବାମ >= INT_MAX - frame->crop_ଡାହାଣ        ||
        frame->crop_ଶୀର୍ଷ  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_ବାମ + frame->crop_ଡାହାଣ) >= frame->width ||
        (frame->crop_ଶୀର୍ଷ + frame->crop_bottom) >= frame->height)
        ଫେରନ୍ତୁ AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    ଯଦି (!desc)
        ଫେରନ୍ତୁ AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    ଯଦି (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_ଡାହାଣ;
        frame->height     -= frame->crop_bottom;
        frame->crop_ଡାହାଣ  = 0;
        frame->crop_bottom = 0;
        ଫେରନ୍ତୁ 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    /* adjust the offsets to avoid breaking alignment */
    ଯଦି (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା log2_crop_align = frame->crop_ବାମ ? ff_ctz(frame->crop_ବାମ) : INT_MAX;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା min_log2_align = INT_MAX;

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; frame->data[i]; i++) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        ଯଦି (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_ବାମ &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            ଯଦି (ret < 0)
                ଫେରନ୍ତୁ ret;
        }
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_ବାମ + frame->crop_ଡାହାଣ);
    frame->height     -= (frame->crop_ଶୀର୍ଷ  + frame->crop_bottom);
    frame->crop_ବାମ   = 0;
    frame->crop_ଡାହାଣ  = 0;
    frame->crop_ଶୀର୍ଷ    = 0;
    frame->crop_bottom = 0;

    ଫେରନ୍ତୁ 0;
}
