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

#અન્તર્ભાવ "channel_layout.h"
#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "buffer.h"
#અન્તર્ભાવ "dict.h"
#અન્તર્ભાવ "frame.h"
#અન્તર્ભાવ "frame_internal.h"
#અન્તર્ભાવ "imgutils.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "refstruct.h"
#અન્તર્ભાવ "samplefmt.h"
#અન્તર્ભાવ "side_data.h"
#અન્તર્ભાવ "hwcontext.h"

સ્થિર શૂન્ય get_frame_defaults(AVFrame *frame)
{
    memset(frame, 0, કદ(*frame));

    frame->pts                   =
    frame->pkt_dts               = AV_NOPTS_કિંમત;
    frame->best_effort_timestamp = AV_NOPTS_કિંમત;
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

AVFrame *av_frame_alloc(શૂન્ય)
{
    AVFrame *frame = av_malloc(કદ(*frame));

    જો (!frame)
        પાછા ખાલી;

    get_frame_defaults(frame);

    પાછા frame;
}

શૂન્ય av_frame_free(AVFrame **frame)
{
    જો (!frame || !*frame)
        પાછા;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

પૂર્ણાંક ff_frame_get_video_buffer(AVFrame *frame, પૂર્ણાંક align,
                              AVBufferRef *(*alloc)(શૂન્ય *opaque, size_t size),
                              શૂન્ય *opaque)
{
    અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    પૂર્ણાંક ret, padded_height;
    પૂર્ણાંક plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    જો (!desc)
        પાછા AVERROR(EINVAL);

    જો ((ret = av_image_check_size(frame->width, frame->height, 0, ખાલી)) < 0)
        પાછા ret;

    જો (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    જો (!frame->linesize[0]) {
        માટે (પૂર્ણાંક i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            જો (ret < 0)
                પાછા ret;
            જો (!(frame->linesize[0] & (align-1)))
                તોડો;
        }

        માટે (પૂર્ણાંક i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    માટે (પૂર્ણાંક i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    જો ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        પાછા ret;

    total_size = 4 * plane_padding + 4 * align;
    માટે (પૂર્ણાંક i = 0; i < 4; i++) {
        જો (sizes[i] > SIZE_MAX - total_size)
            પાછા AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    જો (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        જાઓ fail;
    }

    જો ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        જાઓ fail;

    માટે (પૂર્ણાંક i = 1; i < 4; i++) {
        જો (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    પાછા 0;
fail:
    av_frame_unref(frame);
    પાછા ret;
}

સ્થિર પૂર્ણાંક get_audio_buffer(AVFrame *frame, પૂર્ણાંક align)
{
    પૂર્ણાંક planar   = av_sample_fmt_is_planar(frame->format);
    પૂર્ણાંક channels, planes;
    size_t size;
    પૂર્ણાંક ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    જો (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        જો (ret < 0)
            પાછા ret;
    }

    જો (align <= 0)
        align = ALIGN;

    જો (planes > AV_અંક_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          કદ(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_અંક_DATA_POINTERS,
                                          કદ(*frame->extended_buf));
        જો (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            પાછા AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_અંક_DATA_POINTERS;
    } નહીંતર
        frame->extended_data = frame->data;

    જો (frame->linesize[0] > SIZE_MAX - align)
        પાછા AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    માટે (પૂર્ણાંક i = 0; i < FFMIN(planes, AV_અંક_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        જો (!frame->buf[i]) {
            av_frame_unref(frame);
            પાછા AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    માટે (પૂર્ણાંક i = 0; i < planes - AV_અંક_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        જો (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            પાછા AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_અંક_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    પાછા 0;

}

પૂર્ણાંક av_frame_get_buffer(AVFrame *frame, પૂર્ણાંક align)
{
    જો (frame->format < 0)
        પાછા AVERROR(EINVAL);

    જો (frame->width > 0 && frame->height > 0)
        પાછા ff_frame_get_video_buffer(frame, align, ખાલી, ખાલી);
    નહીંતર જો (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        પાછા get_audio_buffer(frame, align);

    પાછા AVERROR(EINVAL);
}

સ્થિર પૂર્ણાંક frame_copy_props(AVFrame *dst, અચલ AVFrame *src, પૂર્ણાંક force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ratio    = src->sample_aspect_ratio;
    dst->crop_ટોચ               = src->crop_ટોચ;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_ડાબું              = src->crop_ડાબું;
    dst->crop_જમણું             = src->crop_જમણું;
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

    માટે (પૂર્ણાંક i = 0; i < src->nb_side_data; i++) {
        અચલ AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        જો (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            ચાલુ;
        જો (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            જો (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                પાછા AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } નહીંતર {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            જો (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                પાછા AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    પાછા av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

પૂર્ણાંક av_frame_ref(AVFrame *dst, અચલ AVFrame *src)
{
    પૂર્ણાંક ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    જો (ret < 0)
        જાઓ fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    જો (ret < 0)
        જાઓ fail;

    /* duplicate the frame data if it's not refcounted */
    જો (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        જો (ret < 0)
            જાઓ fail;

        ret = av_frame_copy(dst, src);
        જો (ret < 0)
            જાઓ fail;

        પાછા 0;
    }

    /* ref the buffers */
    માટે (પૂર્ણાંક i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        જો (!src->buf[i])
            ચાલુ;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        જો (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            જાઓ fail;
        }
    }

    જો (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      કદ(*dst->extended_buf));
        જો (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            જાઓ fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        માટે (પૂર્ણાંક i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            જો (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                જાઓ fail;
            }
        }
    }

    જો (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        જો (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            જાઓ fail;
        }
    }

    /* duplicate extended data */
    જો (src->extended_data != src->data) {
        પૂર્ણાંક ch = dst->ch_layout.nb_channels;

        જો (ch <= 0 || ch > SIZE_MAX / કદ(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            જાઓ fail;
        }

        dst->extended_data = av_memdup(src->extended_data, કદ(*dst->extended_data) * ch);
        જો (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            જાઓ fail;
        }
    } નહીંતર
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     કદ(src->data));
    memcpy(dst->linesize, src->linesize, કદ(src->linesize));

    પાછા 0;

fail:
    av_frame_unref(dst);
    પાછા ret;
}

પૂર્ણાંક av_frame_replace(AVFrame *dst, અચલ AVFrame *src)
{
    પૂર્ણાંક ret = 0;

    જો (dst == src)
        પાછા AVERROR(EINVAL);

    જો (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        જો (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            પાછા av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        જો (ret < 0)
            જાઓ fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    જો (ret < 0)
        જાઓ fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    જો (ret < 0)
        જાઓ fail;

    /* replace the buffers */
    માટે (પૂર્ણાંક i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        જો (ret < 0)
            જાઓ fail;
    }

    જો (src->extended_buf) {
        જો (dst->nb_extended_buf != src->nb_extended_buf) {
            પૂર્ણાંક nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            શૂન્ય *tmp;

            માટે (પૂર્ણાંક i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   કદ(*dst->extended_buf));
            જો (!tmp) {
                ret = AVERROR(ENOMEM);
                જાઓ fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * કદ(*dst->extended_buf));
        }

        માટે (પૂર્ણાંક i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            જો (ret < 0)
                જાઓ fail;
        }
    } નહીંતર જો (dst->extended_buf) {
        માટે (પૂર્ણાંક i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    જો (ret < 0)
        જાઓ fail;

    જો (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    જો (src->extended_data != src->data) {
        પૂર્ણાંક ch = dst->ch_layout.nb_channels;

        જો (ch <= 0 || ch > SIZE_MAX / કદ(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            જાઓ fail;
        }

        dst->extended_data = av_memdup(src->extended_data, કદ(*dst->extended_data) * ch);
        જો (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            જાઓ fail;
        }
    } નહીંતર
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     કદ(src->data));
    memcpy(dst->linesize, src->linesize, કદ(src->linesize));

    પાછા 0;

fail:
    av_frame_unref(dst);
    પાછા ret;
}

AVFrame *av_frame_clone(અચલ AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    જો (!ret)
        પાછા ખાલી;

    જો (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    પાછા ret;
}

શૂન્ય av_frame_unref(AVFrame *frame)
{
    જો (!frame)
        પાછા;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    માટે (પૂર્ણાંક i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    માટે (પૂર્ણાંક i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    જો (frame->extended_data != frame->data)
        av_freep(&frame->extended_data);

    av_channel_layout_uninit(&frame->ch_layout);

    get_frame_defaults(frame);
}

શૂન્ય av_frame_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    *dst = *src;
    જો (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

પૂર્ણાંક av_frame_is_writable(AVFrame *frame)
{
    પૂર્ણાંક ret = 1;

    /* assume non-refcounted frames are not writable */
    જો (!frame->buf[0])
        પાછા 0;

    માટે (પૂર્ણાંક i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        જો (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    માટે (પૂર્ણાંક i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    પાછા ret;
}

પૂર્ણાંક av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    પૂર્ણાંક ret;

    જો (av_frame_is_writable(frame))
        પાછા 0;

    memset(&tmp, 0, કદ(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    જો (ret < 0) {
        av_frame_unref(&tmp);
        પાછા ret;
    }

    જો (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    નહીંતર
        ret = av_frame_get_buffer(&tmp, 0);
    જો (ret < 0)
        પાછા ret;

    ret = av_frame_copy(&tmp, frame);
    જો (ret < 0) {
        av_frame_unref(&tmp);
        પાછા ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    જો (ret < 0) {
        av_frame_unref(&tmp);
        પાછા ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    જો (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    પાછા 0;
}

પૂર્ણાંક av_frame_copy_props(AVFrame *dst, અચલ AVFrame *src)
{
    પાછા frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(અચલ AVFrame *frame, પૂર્ણાંક plane)
{
    uintptr_t data;
    પૂર્ણાંક planes;

    જો (frame->nb_samples) {
        પૂર્ણાંક channels = frame->ch_layout.nb_channels;
        જો (!channels)
            પાછા ખાલી;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } નહીંતર
        planes = 4;

    જો (plane < 0 || plane >= planes || !frame->extended_data[plane])
        પાછા ખાલી;
    data = (uintptr_t)frame->extended_data[plane];

    માટે (પૂર્ણાંક i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        જો (data >= buf_begin && data < buf_begin + buf->size)
            પાછા buf;
    }
    માટે (પૂર્ણાંક i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        જો (data >= buf_begin && data < buf_begin + buf->size)
            પાછા buf;
    }
    પાછા ખાલી;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 ગણના AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    પાછા
        ff_frame_side_data_add_from_buf(
            &frame->side_data, &frame->nb_side_data, type, buf);
}

AVFrameSideData *av_frame_new_side_data(AVFrame *frame,
                                        ગણના AVFrameSideDataType type,
                                        size_t size)
{
    AVFrameSideData *ret;
    AVBufferRef *buf = av_buffer_alloc(size);
    ret = av_frame_new_side_data_from_buf(frame, type, buf);
    જો (!ret)
        av_buffer_unref(&buf);
    પાછા ret;
}

AVFrameSideData *av_frame_get_side_data(અચલ AVFrame *frame,
                                        ગણના AVFrameSideDataType type)
{
    પાછા (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

સ્થિર પૂર્ણાંક frame_copy_video(AVFrame *dst, અચલ AVFrame *src)
{
    પૂર્ણાંક planes;

    જો (dst->width  < src->width ||
        dst->height < src->height)
        પાછા AVERROR(EINVAL);

    જો (src->hw_frames_ctx || dst->hw_frames_ctx)
        પાછા av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_ગણતરી_planes(dst->format);
    માટે (પૂર્ણાંક i = 0; i < planes; i++)
        જો (!dst->data[i] || !src->data[i])
            પાછા AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    પાછા 0;
}

સ્થિર પૂર્ણાંક frame_copy_audio(AVFrame *dst, અચલ AVFrame *src)
{
    પૂર્ણાંક planar   = av_sample_fmt_is_planar(dst->format);
    પૂર્ણાંક channels = dst->ch_layout.nb_channels;
    પૂર્ણાંક planes   = planar ? channels : 1;

    જો (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        પાછા AVERROR(EINVAL);

    માટે (પૂર્ણાંક i = 0; i < planes; i++)
        જો (!dst->extended_data[i] || !src->extended_data[i])
            પાછા AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    પાછા 0;
}

પૂર્ણાંક av_frame_copy(AVFrame *dst, અચલ AVFrame *src)
{
    જો (dst->format != src->format || dst->format < 0)
        પાછા AVERROR(EINVAL);

    જો (dst->width > 0 && dst->height > 0)
        પાછા frame_copy_video(dst, src);
    નહીંતર જો (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        પાછા frame_copy_audio(dst, src);

    પાછા AVERROR(EINVAL);
}

શૂન્ય av_frame_remove_side_data(AVFrame *frame, ગણના AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

સ્થિર પૂર્ણાંક calc_cropping_offsets(size_t offsets[4], અચલ AVFrame *frame,
                                 અચલ AVPixFmtDescriptor *desc)
{
    માટે (પૂર્ણાંક i = 0; frame->data[i]; i++) {
        અચલ AVComponentDescriptor *comp = ખાલી;
        પૂર્ણાંક shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        પૂર્ણાંક shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        જો (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            તોડો;
        }

        /* find any component descriptor for this plane */
        માટે (પૂર્ણાંક j = 0; j < desc->nb_components; j++) {
            જો (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                તોડો;
            }
        }
        જો (!comp)
            પાછા AVERROR_BUG;

        offsets[i] = (frame->crop_ટોચ  >> shift_y) * frame->linesize[i] +
                     (frame->crop_ડાબું >> shift_x) * comp->step;
    }

    પાછા 0;
}

પૂર્ણાંક av_frame_apply_cropping(AVFrame *frame, પૂર્ણાંક flags)
{
    અચલ AVPixFmtDescriptor *desc;
    size_t offsets[4];
    પૂર્ણાંક ret;

    જો (!(frame->width > 0 && frame->height > 0))
        પાછા AVERROR(EINVAL);

    જો (frame->crop_ડાબું >= INT_MAX - frame->crop_જમણું        ||
        frame->crop_ટોચ  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_ડાબું + frame->crop_જમણું) >= frame->width ||
        (frame->crop_ટોચ + frame->crop_bottom) >= frame->height)
        પાછા AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    જો (!desc)
        પાછા AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    જો (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_જમણું;
        frame->height     -= frame->crop_bottom;
        frame->crop_જમણું  = 0;
        frame->crop_bottom = 0;
        પાછા 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    જો (ret < 0)
        પાછા ret;

    /* adjust the offsets to avoid breaking alignment */
    જો (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        પૂર્ણાંક log2_crop_align = frame->crop_ડાબું ? ff_ctz(frame->crop_ડાબું) : INT_MAX;
        પૂર્ણાંક min_log2_align = INT_MAX;

        માટે (પૂર્ણાંક i = 0; frame->data[i]; i++) {
            પૂર્ણાંક log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        જો (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_ડાબું &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            જો (ret < 0)
                પાછા ret;
        }
    }

    માટે (પૂર્ણાંક i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_ડાબું + frame->crop_જમણું);
    frame->height     -= (frame->crop_ટોચ  + frame->crop_bottom);
    frame->crop_ડાબું   = 0;
    frame->crop_જમણું  = 0;
    frame->crop_ટોચ    = 0;
    frame->crop_bottom = 0;

    પાછા 0;
}
