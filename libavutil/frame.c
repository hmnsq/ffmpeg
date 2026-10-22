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

#include "channel_layout.h"
#include "avassert.h"
#include "buffer.h"
#include "dict.h"
#include "frame.h"
#include "frame_internal.h"
#include "imgutils.h"
#include "mem.h"
#include "refstruct.h"
#include "samplefmt.h"
#include "side_data.h"
#include "hwcontext.h"

static void get_frame_defaults(AVFrame *frame)
{
    memset(frame, 0, sizeof(*frame));

    frame->pts                   =
    frame->pkt_dts               = AV_NOPTS_VALUE;
    frame->best_effort_timestamp = AV_NOPTS_VALUE;
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

AVFrame *av_frame_alloc(void)
{
    AVFrame *frame = av_malloc(sizeof(*frame));

    nếu (!frame)
        trả_về NULL;

    get_frame_defaults(frame);

    trả_về frame;
}

void av_frame_free(AVFrame **frame)
{
    nếu (!frame || !*frame)
        trả_về;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

số_nguyên ff_frame_get_video_buffer(AVFrame *frame, số_nguyên align,
                              AVBufferRef *(*alloc)(void *opaque, size_t size),
                              void *opaque)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    số_nguyên ret, padded_height;
    số_nguyên plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    nếu (!desc)
        trả_về AVERROR(EINVAL);

    nếu ((ret = av_image_check_size(frame->width, frame->height, 0, NULL)) < 0)
        trả_về ret;

    nếu (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    nếu (!frame->linesize[0]) {
        cho (số_nguyên i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            nếu (ret < 0)
                trả_về ret;
            nếu (!(frame->linesize[0] & (align-1)))
                break;
        }

        cho (số_nguyên i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    cho (số_nguyên i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    nếu ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        trả_về ret;

    total_size = 4 * plane_padding + 4 * align;
    cho (số_nguyên i = 0; i < 4; i++) {
        nếu (sizes[i] > SIZE_MAX - total_size)
            trả_về AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    nếu (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    nếu ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        goto fail;

    cho (số_nguyên i = 1; i < 4; i++) {
        nếu (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    trả_về 0;
fail:
    av_frame_unref(frame);
    trả_về ret;
}

static số_nguyên get_audio_buffer(AVFrame *frame, số_nguyên align)
{
    số_nguyên planar   = av_sample_fmt_is_planar(frame->format);
    số_nguyên channels, planes;
    size_t size;
    số_nguyên ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    nếu (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        nếu (ret < 0)
            trả_về ret;
    }

    nếu (align <= 0)
        align = ALIGN;

    nếu (planes > AV_NUM_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          sizeof(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_NUM_DATA_POINTERS,
                                          sizeof(*frame->extended_buf));
        nếu (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            trả_về AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_NUM_DATA_POINTERS;
    } không_thì
        frame->extended_data = frame->data;

    nếu (frame->linesize[0] > SIZE_MAX - align)
        trả_về AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    cho (số_nguyên i = 0; i < FFMIN(planes, AV_NUM_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        nếu (!frame->buf[i]) {
            av_frame_unref(frame);
            trả_về AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    cho (số_nguyên i = 0; i < planes - AV_NUM_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        nếu (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            trả_về AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_NUM_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    trả_về 0;

}

số_nguyên av_frame_get_buffer(AVFrame *frame, số_nguyên align)
{
    nếu (frame->format < 0)
        trả_về AVERROR(EINVAL);

    nếu (frame->width > 0 && frame->height > 0)
        trả_về ff_frame_get_video_buffer(frame, align, NULL, NULL);
    không_thì nếu (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        trả_về get_audio_buffer(frame, align);

    trả_về AVERROR(EINVAL);
}

static số_nguyên frame_copy_props(AVFrame *dst, const AVFrame *src, số_nguyên force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ratio    = src->sample_aspect_ratio;
    dst->crop_top               = src->crop_top;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_left              = src->crop_left;
    dst->crop_right             = src->crop_right;
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

    cho (số_nguyên i = 0; i < src->nb_side_data; i++) {
        const AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        nếu (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            continue;
        nếu (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            nếu (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                trả_về AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } không_thì {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            nếu (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                trả_về AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    trả_về av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

số_nguyên av_frame_ref(AVFrame *dst, const AVFrame *src)
{
    số_nguyên ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    nếu (ret < 0)
        goto fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    nếu (ret < 0)
        goto fail;

    /* duplicate the frame data if it's not refcounted */
    nếu (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        nếu (ret < 0)
            goto fail;

        ret = av_frame_copy(dst, src);
        nếu (ret < 0)
            goto fail;

        trả_về 0;
    }

    /* ref the buffers */
    cho (số_nguyên i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        nếu (!src->buf[i])
            continue;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        nếu (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    }

    nếu (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      sizeof(*dst->extended_buf));
        nếu (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        cho (số_nguyên i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            nếu (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
        }
    }

    nếu (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        nếu (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    }

    /* duplicate extended data */
    nếu (src->extended_data != src->data) {
        số_nguyên ch = dst->ch_layout.nb_channels;

        nếu (ch <= 0 || ch > SIZE_MAX / sizeof(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            goto fail;
        }

        dst->extended_data = av_memdup(src->extended_data, sizeof(*dst->extended_data) * ch);
        nếu (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    } không_thì
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     sizeof(src->data));
    memcpy(dst->linesize, src->linesize, sizeof(src->linesize));

    trả_về 0;

fail:
    av_frame_unref(dst);
    trả_về ret;
}

số_nguyên av_frame_replace(AVFrame *dst, const AVFrame *src)
{
    số_nguyên ret = 0;

    nếu (dst == src)
        trả_về AVERROR(EINVAL);

    nếu (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        nếu (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            trả_về av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        nếu (ret < 0)
            goto fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    nếu (ret < 0)
        goto fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    nếu (ret < 0)
        goto fail;

    /* replace the buffers */
    cho (số_nguyên i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        nếu (ret < 0)
            goto fail;
    }

    nếu (src->extended_buf) {
        nếu (dst->nb_extended_buf != src->nb_extended_buf) {
            số_nguyên nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            void *tmp;

            cho (số_nguyên i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   sizeof(*dst->extended_buf));
            nếu (!tmp) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * sizeof(*dst->extended_buf));
        }

        cho (số_nguyên i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            nếu (ret < 0)
                goto fail;
        }
    } không_thì nếu (dst->extended_buf) {
        cho (số_nguyên i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    nếu (ret < 0)
        goto fail;

    nếu (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    nếu (src->extended_data != src->data) {
        số_nguyên ch = dst->ch_layout.nb_channels;

        nếu (ch <= 0 || ch > SIZE_MAX / sizeof(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            goto fail;
        }

        dst->extended_data = av_memdup(src->extended_data, sizeof(*dst->extended_data) * ch);
        nếu (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    } không_thì
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     sizeof(src->data));
    memcpy(dst->linesize, src->linesize, sizeof(src->linesize));

    trả_về 0;

fail:
    av_frame_unref(dst);
    trả_về ret;
}

AVFrame *av_frame_clone(const AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    nếu (!ret)
        trả_về NULL;

    nếu (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    trả_về ret;
}

void av_frame_unref(AVFrame *frame)
{
    nếu (!frame)
        trả_về;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    cho (số_nguyên i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    cho (số_nguyên i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    nếu (frame->extended_data != frame->data)
        av_freep(&frame->extended_data);

    av_channel_layout_uninit(&frame->ch_layout);

    get_frame_defaults(frame);
}

void av_frame_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    *dst = *src;
    nếu (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

số_nguyên av_frame_is_writable(AVFrame *frame)
{
    số_nguyên ret = 1;

    /* assume non-refcounted frames are not writable */
    nếu (!frame->buf[0])
        trả_về 0;

    cho (số_nguyên i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        nếu (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    cho (số_nguyên i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    trả_về ret;
}

số_nguyên av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    số_nguyên ret;

    nếu (av_frame_is_writable(frame))
        trả_về 0;

    memset(&tmp, 0, sizeof(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    nếu (ret < 0) {
        av_frame_unref(&tmp);
        trả_về ret;
    }

    nếu (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    không_thì
        ret = av_frame_get_buffer(&tmp, 0);
    nếu (ret < 0)
        trả_về ret;

    ret = av_frame_copy(&tmp, frame);
    nếu (ret < 0) {
        av_frame_unref(&tmp);
        trả_về ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    nếu (ret < 0) {
        av_frame_unref(&tmp);
        trả_về ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    nếu (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    trả_về 0;
}

số_nguyên av_frame_copy_props(AVFrame *dst, const AVFrame *src)
{
    trả_về frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(const AVFrame *frame, số_nguyên plane)
{
    uintptr_t data;
    số_nguyên planes;

    nếu (frame->nb_samples) {
        số_nguyên channels = frame->ch_layout.nb_channels;
        nếu (!channels)
            trả_về NULL;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } không_thì
        planes = 4;

    nếu (plane < 0 || plane >= planes || !frame->extended_data[plane])
        trả_về NULL;
    data = (uintptr_t)frame->extended_data[plane];

    cho (số_nguyên i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        nếu (data >= buf_begin && data < buf_begin + buf->size)
            trả_về buf;
    }
    cho (số_nguyên i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        nếu (data >= buf_begin && data < buf_begin + buf->size)
            trả_về buf;
    }
    trả_về NULL;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 enum AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    trả_về
        ff_frame_side_data_add_from_buf(
            &frame->side_data, &frame->nb_side_data, type, buf);
}

AVFrameSideData *av_frame_new_side_data(AVFrame *frame,
                                        enum AVFrameSideDataType type,
                                        size_t size)
{
    AVFrameSideData *ret;
    AVBufferRef *buf = av_buffer_alloc(size);
    ret = av_frame_new_side_data_from_buf(frame, type, buf);
    nếu (!ret)
        av_buffer_unref(&buf);
    trả_về ret;
}

AVFrameSideData *av_frame_get_side_data(const AVFrame *frame,
                                        enum AVFrameSideDataType type)
{
    trả_về (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

static số_nguyên frame_copy_video(AVFrame *dst, const AVFrame *src)
{
    số_nguyên planes;

    nếu (dst->width  < src->width ||
        dst->height < src->height)
        trả_về AVERROR(EINVAL);

    nếu (src->hw_frames_ctx || dst->hw_frames_ctx)
        trả_về av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_count_planes(dst->format);
    cho (số_nguyên i = 0; i < planes; i++)
        nếu (!dst->data[i] || !src->data[i])
            trả_về AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    trả_về 0;
}

static số_nguyên frame_copy_audio(AVFrame *dst, const AVFrame *src)
{
    số_nguyên planar   = av_sample_fmt_is_planar(dst->format);
    số_nguyên channels = dst->ch_layout.nb_channels;
    số_nguyên planes   = planar ? channels : 1;

    nếu (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        trả_về AVERROR(EINVAL);

    cho (số_nguyên i = 0; i < planes; i++)
        nếu (!dst->extended_data[i] || !src->extended_data[i])
            trả_về AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    trả_về 0;
}

số_nguyên av_frame_copy(AVFrame *dst, const AVFrame *src)
{
    nếu (dst->format != src->format || dst->format < 0)
        trả_về AVERROR(EINVAL);

    nếu (dst->width > 0 && dst->height > 0)
        trả_về frame_copy_video(dst, src);
    không_thì nếu (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        trả_về frame_copy_audio(dst, src);

    trả_về AVERROR(EINVAL);
}

void av_frame_remove_side_data(AVFrame *frame, enum AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

static số_nguyên calc_cropping_offsets(size_t offsets[4], const AVFrame *frame,
                                 const AVPixFmtDescriptor *desc)
{
    cho (số_nguyên i = 0; frame->data[i]; i++) {
        const AVComponentDescriptor *comp = NULL;
        số_nguyên shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        số_nguyên shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        nếu (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            break;
        }

        /* find any component descriptor for this plane */
        cho (số_nguyên j = 0; j < desc->nb_components; j++) {
            nếu (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                break;
            }
        }
        nếu (!comp)
            trả_về AVERROR_BUG;

        offsets[i] = (frame->crop_top  >> shift_y) * frame->linesize[i] +
                     (frame->crop_left >> shift_x) * comp->step;
    }

    trả_về 0;
}

số_nguyên av_frame_apply_cropping(AVFrame *frame, số_nguyên flags)
{
    const AVPixFmtDescriptor *desc;
    size_t offsets[4];
    số_nguyên ret;

    nếu (!(frame->width > 0 && frame->height > 0))
        trả_về AVERROR(EINVAL);

    nếu (frame->crop_left >= INT_MAX - frame->crop_right        ||
        frame->crop_top  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_left + frame->crop_right) >= frame->width ||
        (frame->crop_top + frame->crop_bottom) >= frame->height)
        trả_về AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    nếu (!desc)
        trả_về AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    nếu (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_right;
        frame->height     -= frame->crop_bottom;
        frame->crop_right  = 0;
        frame->crop_bottom = 0;
        trả_về 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    nếu (ret < 0)
        trả_về ret;

    /* adjust the offsets to avoid breaking alignment */
    nếu (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        số_nguyên log2_crop_align = frame->crop_left ? ff_ctz(frame->crop_left) : INT_MAX;
        số_nguyên min_log2_align = INT_MAX;

        cho (số_nguyên i = 0; frame->data[i]; i++) {
            số_nguyên log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        nếu (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_left &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            nếu (ret < 0)
                trả_về ret;
        }
    }

    cho (số_nguyên i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_left + frame->crop_right);
    frame->height     -= (frame->crop_top  + frame->crop_bottom);
    frame->crop_left   = 0;
    frame->crop_right  = 0;
    frame->crop_top    = 0;
    frame->crop_bottom = 0;

    trả_về 0;
}
