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

#ಅನ್ತರ್ಭಾವ "channel_layout.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "dict.h"
#ಅನ್ತರ್ಭಾವ "frame.h"
#ಅನ್ತರ್ಭಾವ "frame_internal.h"
#ಅನ್ತರ್ಭಾವ "imgutils.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "refstruct.h"
#ಅನ್ತರ್ಭಾವ "samplefmt.h"
#ಅನ್ತರ್ಭಾವ "side_data.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"

ಸ್ಥಿರ ಶೂನ್ಯ get_frame_defaults(AVFrame *frame)
{
    memset(frame, 0, ಪರಿಮಾಣ(*frame));

    frame->pts                   =
    frame->pkt_dts               = AV_NOPTS_ಮೌಲ್ಯ;
    frame->best_effort_timestamp = AV_NOPTS_ಮೌಲ್ಯ;
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

AVFrame *av_frame_alloc(ಶೂನ್ಯ)
{
    AVFrame *frame = av_malloc(ಪರಿಮಾಣ(*frame));

    ಯದಿ (!frame)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    get_frame_defaults(frame);

    ಪ್ರತ್ಯಾಗಮ frame;
}

ಶೂನ್ಯ av_frame_free(AVFrame **frame)
{
    ಯದಿ (!frame || !*frame)
        ಪ್ರತ್ಯಾಗಮ;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

ಪೂರ್ಣಾಙ್ಕ ff_frame_get_video_buffer(AVFrame *frame, ಪೂರ್ಣಾಙ್ಕ align,
                              AVBufferRef *(*alloc)(ಶೂನ್ಯ *opaque, size_t size),
                              ಶೂನ್ಯ *opaque)
{
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    ಪೂರ್ಣಾಙ್ಕ ret, padded_height;
    ಪೂರ್ಣಾಙ್ಕ plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    ಯದಿ (!desc)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ ((ret = av_image_check_size(frame->width, frame->height, 0, ರಿಕ್ತ)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಯದಿ (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    ಯದಿ (!frame->linesize[0]) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            ಯದಿ (ret < 0)
                ಪ್ರತ್ಯಾಗಮ ret;
            ಯದಿ (!(frame->linesize[0] & (align-1)))
                ಭಙ್ಗ;
        }

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    ಯದಿ ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    total_size = 4 * plane_padding + 4 * align;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 4; i++) {
        ಯದಿ (sizes[i] > SIZE_MAX - total_size)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    ಯದಿ (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    ಯದಿ ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        ಗಚ್ಛ fail;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 1; i < 4; i++) {
        ಯದಿ (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    ಪ್ರತ್ಯಾಗಮ 0;
fail:
    av_frame_unref(frame);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_audio_buffer(AVFrame *frame, ಪೂರ್ಣಾಙ್ಕ align)
{
    ಪೂರ್ಣಾಙ್ಕ planar   = av_sample_fmt_is_planar(frame->format);
    ಪೂರ್ಣಾಙ್ಕ channels, planes;
    size_t size;
    ಪೂರ್ಣಾಙ್ಕ ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    ಯದಿ (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
    }

    ಯದಿ (align <= 0)
        align = ALIGN;

    ಯದಿ (planes > AV_ಅಂಕೆ_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          ಪರಿಮಾಣ(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_ಅಂಕೆ_DATA_POINTERS,
                                          ಪರಿಮಾಣ(*frame->extended_buf));
        ಯದಿ (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_ಅಂಕೆ_DATA_POINTERS;
    } ಅನ್ಯಥಾ
        frame->extended_data = frame->data;

    ಯದಿ (frame->linesize[0] > SIZE_MAX - align)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FFMIN(planes, AV_ಅಂಕೆ_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        ಯದಿ (!frame->buf[i]) {
            av_frame_unref(frame);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes - AV_ಅಂಕೆ_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        ಯದಿ (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_ಅಂಕೆ_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    ಪ್ರತ್ಯಾಗಮ 0;

}

ಪೂರ್ಣಾಙ್ಕ av_frame_get_buffer(AVFrame *frame, ಪೂರ್ಣಾಙ್ಕ align)
{
    ಯದಿ (frame->format < 0)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (frame->width > 0 && frame->height > 0)
        ಪ್ರತ್ಯಾಗಮ ff_frame_get_video_buffer(frame, align, ರಿಕ್ತ, ರಿಕ್ತ);
    ಅನ್ಯಥಾ ಯದಿ (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        ಪ್ರತ್ಯಾಗಮ get_audio_buffer(frame, align);

    ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ frame_copy_props(AVFrame *dst, ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ratio    = src->sample_aspect_ratio;
    dst->crop_ತುದಿ               = src->crop_ತುದಿ;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_ಎಡ              = src->crop_ಎಡ;
    dst->crop_ಬಲ             = src->crop_ಬಲ;
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

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < src->nb_side_data; i++) {
        ಧ್ರುವ AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        ಯದಿ (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            ಅನುವರ್ತ;
        ಯದಿ (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            ಯದಿ (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } ಅನ್ಯಥಾ {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            ಯದಿ (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    ಪ್ರತ್ಯಾಗಮ av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

ಪೂರ್ಣಾಙ್ಕ av_frame_ref(AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    /* duplicate the frame data if it's not refcounted */
    ಯದಿ (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        ಯದಿ (ret < 0)
            ಗಚ್ಛ fail;

        ret = av_frame_copy(dst, src);
        ಯದಿ (ret < 0)
            ಗಚ್ಛ fail;

        ಪ್ರತ್ಯಾಗಮ 0;
    }

    /* ref the buffers */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ಯದಿ (!src->buf[i])
            ಅನುವರ್ತ;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        ಯದಿ (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }
    }

    ಯದಿ (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      ಪರಿಮಾಣ(*dst->extended_buf));
        ಯದಿ (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            ಯದಿ (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                ಗಚ್ಛ fail;
            }
        }
    }

    ಯದಿ (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        ಯದಿ (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }
    }

    /* duplicate extended data */
    ಯದಿ (src->extended_data != src->data) {
        ಪೂರ್ಣಾಙ್ಕ ch = dst->ch_layout.nb_channels;

        ಯದಿ (ch <= 0 || ch > SIZE_MAX / ಪರಿಮಾಣ(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            ಗಚ್ಛ fail;
        }

        dst->extended_data = av_memdup(src->extended_data, ಪರಿಮಾಣ(*dst->extended_data) * ch);
        ಯದಿ (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }
    } ಅನ್ಯಥಾ
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     ಪರಿಮಾಣ(src->data));
    memcpy(dst->linesize, src->linesize, ಪರಿಮಾಣ(src->linesize));

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    av_frame_unref(dst);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_frame_replace(AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    ಯದಿ (dst == src)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        ಯದಿ (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            ಪ್ರತ್ಯಾಗಮ av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        ಯದಿ (ret < 0)
            ಗಚ್ಛ fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    /* replace the buffers */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        ಯದಿ (ret < 0)
            ಗಚ್ಛ fail;
    }

    ಯದಿ (src->extended_buf) {
        ಯದಿ (dst->nb_extended_buf != src->nb_extended_buf) {
            ಪೂರ್ಣಾಙ್ಕ nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            ಶೂನ್ಯ *tmp;

            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   ಪರಿಮಾಣ(*dst->extended_buf));
            ಯದಿ (!tmp) {
                ret = AVERROR(ENOMEM);
                ಗಚ್ಛ fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * ಪರಿಮಾಣ(*dst->extended_buf));
        }

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            ಯದಿ (ret < 0)
                ಗಚ್ಛ fail;
        }
    } ಅನ್ಯಥಾ ಯದಿ (dst->extended_buf) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    ಯದಿ (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    ಯದಿ (src->extended_data != src->data) {
        ಪೂರ್ಣಾಙ್ಕ ch = dst->ch_layout.nb_channels;

        ಯದಿ (ch <= 0 || ch > SIZE_MAX / ಪರಿಮಾಣ(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            ಗಚ್ಛ fail;
        }

        dst->extended_data = av_memdup(src->extended_data, ಪರಿಮಾಣ(*dst->extended_data) * ch);
        ಯದಿ (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }
    } ಅನ್ಯಥಾ
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     ಪರಿಮಾಣ(src->data));
    memcpy(dst->linesize, src->linesize, ಪರಿಮಾಣ(src->linesize));

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    av_frame_unref(dst);
    ಪ್ರತ್ಯಾಗಮ ret;
}

AVFrame *av_frame_clone(ಧ್ರುವ AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    ಯದಿ (!ret)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಯದಿ (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಶೂನ್ಯ av_frame_unref(AVFrame *frame)
{
    ಯದಿ (!frame)
        ಪ್ರತ್ಯಾಗಮ;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    ಯದಿ (frame->extended_data != frame->data)
        av_freep(&frame->extended_data);

    av_channel_layout_uninit(&frame->ch_layout);

    get_frame_defaults(frame);
}

ಶೂನ್ಯ av_frame_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    *dst = *src;
    ಯದಿ (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

ಪೂರ್ಣಾಙ್ಕ av_frame_is_writable(AVFrame *frame)
{
    ಪೂರ್ಣಾಙ್ಕ ret = 1;

    /* assume non-refcounted frames are not writable */
    ಯದಿ (!frame->buf[0])
        ಪ್ರತ್ಯಾಗಮ 0;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        ಯದಿ (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (av_frame_is_writable(frame))
        ಪ್ರತ್ಯಾಗಮ 0;

    memset(&tmp, 0, ಪರಿಮಾಣ(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    ಯದಿ (ret < 0) {
        av_frame_unref(&tmp);
        ಪ್ರತ್ಯಾಗಮ ret;
    }

    ಯದಿ (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    ಅನ್ಯಥಾ
        ret = av_frame_get_buffer(&tmp, 0);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ret = av_frame_copy(&tmp, frame);
    ಯದಿ (ret < 0) {
        av_frame_unref(&tmp);
        ಪ್ರತ್ಯಾಗಮ ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    ಯದಿ (ret < 0) {
        av_frame_unref(&tmp);
        ಪ್ರತ್ಯಾಗಮ ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    ಯದಿ (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_frame_copy_props(AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    ಪ್ರತ್ಯಾಗಮ frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(ಧ್ರುವ AVFrame *frame, ಪೂರ್ಣಾಙ್ಕ plane)
{
    uintptr_t data;
    ಪೂರ್ಣಾಙ್ಕ planes;

    ಯದಿ (frame->nb_samples) {
        ಪೂರ್ಣಾಙ್ಕ channels = frame->ch_layout.nb_channels;
        ಯದಿ (!channels)
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } ಅನ್ಯಥಾ
        planes = 4;

    ಯದಿ (plane < 0 || plane >= planes || !frame->extended_data[plane])
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    data = (uintptr_t)frame->extended_data[plane];

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        ಯದಿ (data >= buf_begin && data < buf_begin + buf->size)
            ಪ್ರತ್ಯಾಗಮ buf;
    }
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        ಯದಿ (data >= buf_begin && data < buf_begin + buf->size)
            ಪ್ರತ್ಯಾಗಮ buf;
    }
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 ಗಣನಾ AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    ಪ್ರತ್ಯಾಗಮ
        ff_frame_side_data_add_from_buf(
            &frame->side_data, &frame->nb_side_data, type, buf);
}

AVFrameSideData *av_frame_new_side_data(AVFrame *frame,
                                        ಗಣನಾ AVFrameSideDataType type,
                                        size_t size)
{
    AVFrameSideData *ret;
    AVBufferRef *buf = av_buffer_alloc(size);
    ret = av_frame_new_side_data_from_buf(frame, type, buf);
    ಯದಿ (!ret)
        av_buffer_unref(&buf);
    ಪ್ರತ್ಯಾಗಮ ret;
}

AVFrameSideData *av_frame_get_side_data(ಧ್ರುವ AVFrame *frame,
                                        ಗಣನಾ AVFrameSideDataType type)
{
    ಪ್ರತ್ಯಾಗಮ (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ frame_copy_video(AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    ಪೂರ್ಣಾಙ್ಕ planes;

    ಯದಿ (dst->width  < src->width ||
        dst->height < src->height)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (src->hw_frames_ctx || dst->hw_frames_ctx)
        ಪ್ರತ್ಯಾಗಮ av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_ಎಣಿಕೆ_planes(dst->format);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++)
        ಯದಿ (!dst->data[i] || !src->data[i])
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ frame_copy_audio(AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    ಪೂರ್ಣಾಙ್ಕ planar   = av_sample_fmt_is_planar(dst->format);
    ಪೂರ್ಣಾಙ್ಕ channels = dst->ch_layout.nb_channels;
    ಪೂರ್ಣಾಙ್ಕ planes   = planar ? channels : 1;

    ಯದಿ (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < planes; i++)
        ಯದಿ (!dst->extended_data[i] || !src->extended_data[i])
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_frame_copy(AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    ಯದಿ (dst->format != src->format || dst->format < 0)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (dst->width > 0 && dst->height > 0)
        ಪ್ರತ್ಯಾಗಮ frame_copy_video(dst, src);
    ಅನ್ಯಥಾ ಯದಿ (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        ಪ್ರತ್ಯಾಗಮ frame_copy_audio(dst, src);

    ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
}

ಶೂನ್ಯ av_frame_remove_side_data(AVFrame *frame, ಗಣನಾ AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ calc_cropping_offsets(size_t offsets[4], ಧ್ರುವ AVFrame *frame,
                                 ಧ್ರುವ AVPixFmtDescriptor *desc)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; frame->data[i]; i++) {
        ಧ್ರುವ AVComponentDescriptor *comp = ರಿಕ್ತ;
        ಪೂರ್ಣಾಙ್ಕ shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        ಪೂರ್ಣಾಙ್ಕ shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        ಯದಿ (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            ಭಙ್ಗ;
        }

        /* find any component descriptor for this plane */
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < desc->nb_components; j++) {
            ಯದಿ (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (!comp)
            ಪ್ರತ್ಯಾಗಮ AVERROR_BUG;

        offsets[i] = (frame->crop_ತುದಿ  >> shift_y) * frame->linesize[i] +
                     (frame->crop_ಎಡ >> shift_x) * comp->step;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_frame_apply_cropping(AVFrame *frame, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಧ್ರುವ AVPixFmtDescriptor *desc;
    size_t offsets[4];
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (!(frame->width > 0 && frame->height > 0))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (frame->crop_ಎಡ >= INT_MAX - frame->crop_ಬಲ        ||
        frame->crop_ತುದಿ  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_ಎಡ + frame->crop_ಬಲ) >= frame->width ||
        (frame->crop_ತುದಿ + frame->crop_bottom) >= frame->height)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    ಯದಿ (!desc)
        ಪ್ರತ್ಯಾಗಮ AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    ಯದಿ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_ಬಲ;
        frame->height     -= frame->crop_bottom;
        frame->crop_ಬಲ  = 0;
        frame->crop_bottom = 0;
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    /* adjust the offsets to avoid breaking alignment */
    ಯದಿ (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        ಪೂರ್ಣಾಙ್ಕ log2_crop_align = frame->crop_ಎಡ ? ff_ctz(frame->crop_ಎಡ) : INT_MAX;
        ಪೂರ್ಣಾಙ್ಕ min_log2_align = INT_MAX;

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; frame->data[i]; i++) {
            ಪೂರ್ಣಾಙ್ಕ log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        ಯದಿ (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_ಎಡ &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            ಯದಿ (ret < 0)
                ಪ್ರತ್ಯಾಗಮ ret;
        }
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_ಎಡ + frame->crop_ಬಲ);
    frame->height     -= (frame->crop_ತುದಿ  + frame->crop_bottom);
    frame->crop_ಎಡ   = 0;
    frame->crop_ಬಲ  = 0;
    frame->crop_ತುದಿ    = 0;
    frame->crop_bottom = 0;

    ಪ್ರತ್ಯಾಗಮ 0;
}
