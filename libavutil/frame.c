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

    если (!frame)
        вернуть NULL;

    get_frame_defaults(frame);

    вернуть frame;
}

void av_frame_free(AVFrame **frame)
{
    если (!frame || !*frame)
        вернуть;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

целое ff_frame_get_video_buffer(AVFrame *frame, целое align,
                              AVBufferRef *(*alloc)(void *opaque, size_t size),
                              void *opaque)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    целое ret, padded_height;
    целое plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    если (!desc)
        вернуть AVERROR(EINVAL);

    если ((ret = av_image_check_size(frame->width, frame->height, 0, NULL)) < 0)
        вернуть ret;

    если (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    если (!frame->linesize[0]) {
        для (целое i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            если (ret < 0)
                вернуть ret;
            если (!(frame->linesize[0] & (align-1)))
                break;
        }

        для (целое i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    для (целое i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    если ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        вернуть ret;

    total_size = 4 * plane_padding + 4 * align;
    для (целое i = 0; i < 4; i++) {
        если (sizes[i] > SIZE_MAX - total_size)
            вернуть AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    если (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    если ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        goto fail;

    для (целое i = 1; i < 4; i++) {
        если (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    вернуть 0;
fail:
    av_frame_unref(frame);
    вернуть ret;
}

static целое get_audio_buffer(AVFrame *frame, целое align)
{
    целое planar   = av_sample_fmt_is_planar(frame->format);
    целое channels, planes;
    size_t size;
    целое ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    если (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        если (ret < 0)
            вернуть ret;
    }

    если (align <= 0)
        align = ALIGN;

    если (planes > AV_NUM_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          sizeof(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_NUM_DATA_POINTERS,
                                          sizeof(*frame->extended_buf));
        если (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            вернуть AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_NUM_DATA_POINTERS;
    } иначе
        frame->extended_data = frame->data;

    если (frame->linesize[0] > SIZE_MAX - align)
        вернуть AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    для (целое i = 0; i < FFMIN(planes, AV_NUM_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        если (!frame->buf[i]) {
            av_frame_unref(frame);
            вернуть AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    для (целое i = 0; i < planes - AV_NUM_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        если (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            вернуть AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_NUM_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    вернуть 0;

}

целое av_frame_get_buffer(AVFrame *frame, целое align)
{
    если (frame->format < 0)
        вернуть AVERROR(EINVAL);

    если (frame->width > 0 && frame->height > 0)
        вернуть ff_frame_get_video_buffer(frame, align, NULL, NULL);
    иначе если (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        вернуть get_audio_buffer(frame, align);

    вернуть AVERROR(EINVAL);
}

static целое frame_copy_props(AVFrame *dst, const AVFrame *src, целое force_copy)
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

    для (целое i = 0; i < src->nb_side_data; i++) {
        const AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        если (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            continue;
        если (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            если (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                вернуть AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } иначе {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            если (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                вернуть AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    вернуть av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

целое av_frame_ref(AVFrame *dst, const AVFrame *src)
{
    целое ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    если (ret < 0)
        goto fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    если (ret < 0)
        goto fail;

    /* duplicate the frame data if it's not refcounted */
    если (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        если (ret < 0)
            goto fail;

        ret = av_frame_copy(dst, src);
        если (ret < 0)
            goto fail;

        вернуть 0;
    }

    /* ref the buffers */
    для (целое i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        если (!src->buf[i])
            continue;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        если (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    }

    если (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      sizeof(*dst->extended_buf));
        если (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        для (целое i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            если (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
        }
    }

    если (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        если (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    }

    /* duplicate extended data */
    если (src->extended_data != src->data) {
        целое ch = dst->ch_layout.nb_channels;

        если (ch <= 0 || ch > SIZE_MAX / sizeof(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            goto fail;
        }

        dst->extended_data = av_memdup(src->extended_data, sizeof(*dst->extended_data) * ch);
        если (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    } иначе
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     sizeof(src->data));
    memcpy(dst->linesize, src->linesize, sizeof(src->linesize));

    вернуть 0;

fail:
    av_frame_unref(dst);
    вернуть ret;
}

целое av_frame_replace(AVFrame *dst, const AVFrame *src)
{
    целое ret = 0;

    если (dst == src)
        вернуть AVERROR(EINVAL);

    если (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        если (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            вернуть av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        если (ret < 0)
            goto fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    если (ret < 0)
        goto fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    если (ret < 0)
        goto fail;

    /* replace the buffers */
    для (целое i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        если (ret < 0)
            goto fail;
    }

    если (src->extended_buf) {
        если (dst->nb_extended_buf != src->nb_extended_buf) {
            целое nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            void *tmp;

            для (целое i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   sizeof(*dst->extended_buf));
            если (!tmp) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * sizeof(*dst->extended_buf));
        }

        для (целое i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            если (ret < 0)
                goto fail;
        }
    } иначе если (dst->extended_buf) {
        для (целое i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    если (ret < 0)
        goto fail;

    если (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    если (src->extended_data != src->data) {
        целое ch = dst->ch_layout.nb_channels;

        если (ch <= 0 || ch > SIZE_MAX / sizeof(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            goto fail;
        }

        dst->extended_data = av_memdup(src->extended_data, sizeof(*dst->extended_data) * ch);
        если (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    } иначе
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     sizeof(src->data));
    memcpy(dst->linesize, src->linesize, sizeof(src->linesize));

    вернуть 0;

fail:
    av_frame_unref(dst);
    вернуть ret;
}

AVFrame *av_frame_clone(const AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    если (!ret)
        вернуть NULL;

    если (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    вернуть ret;
}

void av_frame_unref(AVFrame *frame)
{
    если (!frame)
        вернуть;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    для (целое i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    для (целое i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    если (frame->extended_data != frame->data)
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
    если (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

целое av_frame_is_writable(AVFrame *frame)
{
    целое ret = 1;

    /* assume non-refcounted frames are not writable */
    если (!frame->buf[0])
        вернуть 0;

    для (целое i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        если (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    для (целое i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    вернуть ret;
}

целое av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    целое ret;

    если (av_frame_is_writable(frame))
        вернуть 0;

    memset(&tmp, 0, sizeof(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    если (ret < 0) {
        av_frame_unref(&tmp);
        вернуть ret;
    }

    если (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    иначе
        ret = av_frame_get_buffer(&tmp, 0);
    если (ret < 0)
        вернуть ret;

    ret = av_frame_copy(&tmp, frame);
    если (ret < 0) {
        av_frame_unref(&tmp);
        вернуть ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    если (ret < 0) {
        av_frame_unref(&tmp);
        вернуть ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    если (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    вернуть 0;
}

целое av_frame_copy_props(AVFrame *dst, const AVFrame *src)
{
    вернуть frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(const AVFrame *frame, целое plane)
{
    uintptr_t data;
    целое planes;

    если (frame->nb_samples) {
        целое channels = frame->ch_layout.nb_channels;
        если (!channels)
            вернуть NULL;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } иначе
        planes = 4;

    если (plane < 0 || plane >= planes || !frame->extended_data[plane])
        вернуть NULL;
    data = (uintptr_t)frame->extended_data[plane];

    для (целое i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        если (data >= buf_begin && data < buf_begin + buf->size)
            вернуть buf;
    }
    для (целое i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        если (data >= buf_begin && data < buf_begin + buf->size)
            вернуть buf;
    }
    вернуть NULL;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 enum AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    вернуть
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
    если (!ret)
        av_buffer_unref(&buf);
    вернуть ret;
}

AVFrameSideData *av_frame_get_side_data(const AVFrame *frame,
                                        enum AVFrameSideDataType type)
{
    вернуть (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

static целое frame_copy_video(AVFrame *dst, const AVFrame *src)
{
    целое planes;

    если (dst->width  < src->width ||
        dst->height < src->height)
        вернуть AVERROR(EINVAL);

    если (src->hw_frames_ctx || dst->hw_frames_ctx)
        вернуть av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_count_planes(dst->format);
    для (целое i = 0; i < planes; i++)
        если (!dst->data[i] || !src->data[i])
            вернуть AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    вернуть 0;
}

static целое frame_copy_audio(AVFrame *dst, const AVFrame *src)
{
    целое planar   = av_sample_fmt_is_planar(dst->format);
    целое channels = dst->ch_layout.nb_channels;
    целое planes   = planar ? channels : 1;

    если (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        вернуть AVERROR(EINVAL);

    для (целое i = 0; i < planes; i++)
        если (!dst->extended_data[i] || !src->extended_data[i])
            вернуть AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    вернуть 0;
}

целое av_frame_copy(AVFrame *dst, const AVFrame *src)
{
    если (dst->format != src->format || dst->format < 0)
        вернуть AVERROR(EINVAL);

    если (dst->width > 0 && dst->height > 0)
        вернуть frame_copy_video(dst, src);
    иначе если (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        вернуть frame_copy_audio(dst, src);

    вернуть AVERROR(EINVAL);
}

void av_frame_remove_side_data(AVFrame *frame, enum AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

static целое calc_cropping_offsets(size_t offsets[4], const AVFrame *frame,
                                 const AVPixFmtDescriptor *desc)
{
    для (целое i = 0; frame->data[i]; i++) {
        const AVComponentDescriptor *comp = NULL;
        целое shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        целое shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        если (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            break;
        }

        /* find any component descriptor for this plane */
        для (целое j = 0; j < desc->nb_components; j++) {
            если (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                break;
            }
        }
        если (!comp)
            вернуть AVERROR_BUG;

        offsets[i] = (frame->crop_top  >> shift_y) * frame->linesize[i] +
                     (frame->crop_left >> shift_x) * comp->step;
    }

    вернуть 0;
}

целое av_frame_apply_cropping(AVFrame *frame, целое flags)
{
    const AVPixFmtDescriptor *desc;
    size_t offsets[4];
    целое ret;

    если (!(frame->width > 0 && frame->height > 0))
        вернуть AVERROR(EINVAL);

    если (frame->crop_left >= INT_MAX - frame->crop_right        ||
        frame->crop_top  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_left + frame->crop_right) >= frame->width ||
        (frame->crop_top + frame->crop_bottom) >= frame->height)
        вернуть AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    если (!desc)
        вернуть AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    если (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_right;
        frame->height     -= frame->crop_bottom;
        frame->crop_right  = 0;
        frame->crop_bottom = 0;
        вернуть 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    если (ret < 0)
        вернуть ret;

    /* adjust the offsets to avoid breaking alignment */
    если (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        целое log2_crop_align = frame->crop_left ? ff_ctz(frame->crop_left) : INT_MAX;
        целое min_log2_align = INT_MAX;

        для (целое i = 0; frame->data[i]; i++) {
            целое log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        если (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_left &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            если (ret < 0)
                вернуть ret;
        }
    }

    для (целое i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_left + frame->crop_right);
    frame->height     -= (frame->crop_top  + frame->crop_bottom);
    frame->crop_left   = 0;
    frame->crop_right  = 0;
    frame->crop_top    = 0;
    frame->crop_bottom = 0;

    вернуть 0;
}
