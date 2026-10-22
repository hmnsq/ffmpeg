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
    memset(frame, 0, parimaa_na(*frame));

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
    AVFrame *frame = av_malloc(parimaa_na(*frame));

    ຖ້າ (!frame)
        ສົ່ງຄືນ NULL;

    get_frame_defaults(frame);

    ສົ່ງຄືນ frame;
}

void av_frame_free(AVFrame **frame)
{
    ຖ້າ (!frame || !*frame)
        ສົ່ງຄືນ;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

ຈຳນວນເຕັມ ff_frame_get_video_buffer(AVFrame *frame, ຈຳນວນເຕັມ align,
                              AVBufferRef *(*alloc)(void *opaque, size_t size),
                              void *opaque)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    ຈຳນວນເຕັມ ret, padded_height;
    ຈຳນວນເຕັມ plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    ຖ້າ (!desc)
        ສົ່ງຄືນ AVERROR(EINVAL);

    ຖ້າ ((ret = av_image_check_size(frame->width, frame->height, 0, NULL)) < 0)
        ສົ່ງຄືນ ret;

    ຖ້າ (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    ຖ້າ (!frame->linesize[0]) {
        ສຳລັບ (ຈຳນວນເຕັມ i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            ຖ້າ (ret < 0)
                ສົ່ງຄືນ ret;
            ຖ້າ (!(frame->linesize[0] & (align-1)))
                bha_nga;
        }

        ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    ຖ້າ ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        ສົ່ງຄືນ ret;

    total_size = 4 * plane_padding + 4 * align;
    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < 4; i++) {
        ຖ້າ (sizes[i] > SIZE_MAX - total_size)
            ສົ່ງຄືນ AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    ຖ້າ (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    ຖ້າ ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        goto fail;

    ສຳລັບ (ຈຳນວນເຕັມ i = 1; i < 4; i++) {
        ຖ້າ (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    ສົ່ງຄືນ 0;
fail:
    av_frame_unref(frame);
    ສົ່ງຄືນ ret;
}

static ຈຳນວນເຕັມ get_audio_buffer(AVFrame *frame, ຈຳນວນເຕັມ align)
{
    ຈຳນວນເຕັມ planar   = av_sample_fmt_is_planar(frame->format);
    ຈຳນວນເຕັມ channels, planes;
    size_t size;
    ຈຳນວນເຕັມ ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    ຖ້າ (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        ຖ້າ (ret < 0)
            ສົ່ງຄືນ ret;
    }

    ຖ້າ (align <= 0)
        align = ALIGN;

    ຖ້າ (planes > AV_NUM_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          parimaa_na(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_NUM_DATA_POINTERS,
                                          parimaa_na(*frame->extended_buf));
        ຖ້າ (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            ສົ່ງຄືນ AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_NUM_DATA_POINTERS;
    } ບໍ່ດັ່ງນັ້ນ
        frame->extended_data = frame->data;

    ຖ້າ (frame->linesize[0] > SIZE_MAX - align)
        ສົ່ງຄືນ AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < FFMIN(planes, AV_NUM_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        ຖ້າ (!frame->buf[i]) {
            av_frame_unref(frame);
            ສົ່ງຄືນ AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < planes - AV_NUM_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        ຖ້າ (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            ສົ່ງຄືນ AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_NUM_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    ສົ່ງຄືນ 0;

}

ຈຳນວນເຕັມ av_frame_get_buffer(AVFrame *frame, ຈຳນວນເຕັມ align)
{
    ຖ້າ (frame->format < 0)
        ສົ່ງຄືນ AVERROR(EINVAL);

    ຖ້າ (frame->width > 0 && frame->height > 0)
        ສົ່ງຄືນ ff_frame_get_video_buffer(frame, align, NULL, NULL);
    ບໍ່ດັ່ງນັ້ນ ຖ້າ (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        ສົ່ງຄືນ get_audio_buffer(frame, align);

    ສົ່ງຄືນ AVERROR(EINVAL);
}

static ຈຳນວນເຕັມ frame_copy_props(AVFrame *dst, const AVFrame *src, ຈຳນວນເຕັມ force_copy)
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

    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < src->nb_side_data; i++) {
        const AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        ຖ້າ (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            continue;
        ຖ້າ (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            ຖ້າ (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ສົ່ງຄືນ AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } ບໍ່ດັ່ງນັ້ນ {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            ຖ້າ (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ສົ່ງຄືນ AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    ສົ່ງຄືນ av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

ຈຳນວນເຕັມ av_frame_ref(AVFrame *dst, const AVFrame *src)
{
    ຈຳນວນເຕັມ ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    ຖ້າ (ret < 0)
        goto fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ຖ້າ (ret < 0)
        goto fail;

    /* duplicate the frame data if it's not refcounted */
    ຖ້າ (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        ຖ້າ (ret < 0)
            goto fail;

        ret = av_frame_copy(dst, src);
        ຖ້າ (ret < 0)
            goto fail;

        ສົ່ງຄືນ 0;
    }

    /* ref the buffers */
    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ຖ້າ (!src->buf[i])
            continue;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        ຖ້າ (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    }

    ຖ້າ (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      parimaa_na(*dst->extended_buf));
        ຖ້າ (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            ຖ້າ (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
        }
    }

    ຖ້າ (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        ຖ້າ (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    }

    /* duplicate extended data */
    ຖ້າ (src->extended_data != src->data) {
        ຈຳນວນເຕັມ ch = dst->ch_layout.nb_channels;

        ຖ້າ (ch <= 0 || ch > SIZE_MAX / parimaa_na(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            goto fail;
        }

        dst->extended_data = av_memdup(src->extended_data, parimaa_na(*dst->extended_data) * ch);
        ຖ້າ (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    } ບໍ່ດັ່ງນັ້ນ
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     parimaa_na(src->data));
    memcpy(dst->linesize, src->linesize, parimaa_na(src->linesize));

    ສົ່ງຄືນ 0;

fail:
    av_frame_unref(dst);
    ສົ່ງຄືນ ret;
}

ຈຳນວນເຕັມ av_frame_replace(AVFrame *dst, const AVFrame *src)
{
    ຈຳນວນເຕັມ ret = 0;

    ຖ້າ (dst == src)
        ສົ່ງຄືນ AVERROR(EINVAL);

    ຖ້າ (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        ຖ້າ (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            ສົ່ງຄືນ av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        ຖ້າ (ret < 0)
            goto fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ຖ້າ (ret < 0)
        goto fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    ຖ້າ (ret < 0)
        goto fail;

    /* replace the buffers */
    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        ຖ້າ (ret < 0)
            goto fail;
    }

    ຖ້າ (src->extended_buf) {
        ຖ້າ (dst->nb_extended_buf != src->nb_extended_buf) {
            ຈຳນວນເຕັມ nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            void *tmp;

            ສຳລັບ (ຈຳນວນເຕັມ i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   parimaa_na(*dst->extended_buf));
            ຖ້າ (!tmp) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * parimaa_na(*dst->extended_buf));
        }

        ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            ຖ້າ (ret < 0)
                goto fail;
        }
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (dst->extended_buf) {
        ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    ຖ້າ (ret < 0)
        goto fail;

    ຖ້າ (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    ຖ້າ (src->extended_data != src->data) {
        ຈຳນວນເຕັມ ch = dst->ch_layout.nb_channels;

        ຖ້າ (ch <= 0 || ch > SIZE_MAX / parimaa_na(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            goto fail;
        }

        dst->extended_data = av_memdup(src->extended_data, parimaa_na(*dst->extended_data) * ch);
        ຖ້າ (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    } ບໍ່ດັ່ງນັ້ນ
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     parimaa_na(src->data));
    memcpy(dst->linesize, src->linesize, parimaa_na(src->linesize));

    ສົ່ງຄືນ 0;

fail:
    av_frame_unref(dst);
    ສົ່ງຄືນ ret;
}

AVFrame *av_frame_clone(const AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    ຖ້າ (!ret)
        ສົ່ງຄືນ NULL;

    ຖ້າ (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    ສົ່ງຄືນ ret;
}

void av_frame_unref(AVFrame *frame)
{
    ຖ້າ (!frame)
        ສົ່ງຄືນ;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    ຖ້າ (frame->extended_data != frame->data)
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
    ຖ້າ (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

ຈຳນວນເຕັມ av_frame_is_writable(AVFrame *frame)
{
    ຈຳນວນເຕັມ ret = 1;

    /* assume non-refcounted frames are not writable */
    ຖ້າ (!frame->buf[0])
        ສົ່ງຄືນ 0;

    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        ຖ້າ (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    ສົ່ງຄືນ ret;
}

ຈຳນວນເຕັມ av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    ຈຳນວນເຕັມ ret;

    ຖ້າ (av_frame_is_writable(frame))
        ສົ່ງຄືນ 0;

    memset(&tmp, 0, parimaa_na(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    ຖ້າ (ret < 0) {
        av_frame_unref(&tmp);
        ສົ່ງຄືນ ret;
    }

    ຖ້າ (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    ບໍ່ດັ່ງນັ້ນ
        ret = av_frame_get_buffer(&tmp, 0);
    ຖ້າ (ret < 0)
        ສົ່ງຄືນ ret;

    ret = av_frame_copy(&tmp, frame);
    ຖ້າ (ret < 0) {
        av_frame_unref(&tmp);
        ສົ່ງຄືນ ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    ຖ້າ (ret < 0) {
        av_frame_unref(&tmp);
        ສົ່ງຄືນ ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    ຖ້າ (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    ສົ່ງຄືນ 0;
}

ຈຳນວນເຕັມ av_frame_copy_props(AVFrame *dst, const AVFrame *src)
{
    ສົ່ງຄືນ frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(const AVFrame *frame, ຈຳນວນເຕັມ plane)
{
    uintptr_t data;
    ຈຳນວນເຕັມ planes;

    ຖ້າ (frame->nb_samples) {
        ຈຳນວນເຕັມ channels = frame->ch_layout.nb_channels;
        ຖ້າ (!channels)
            ສົ່ງຄືນ NULL;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } ບໍ່ດັ່ງນັ້ນ
        planes = 4;

    ຖ້າ (plane < 0 || plane >= planes || !frame->extended_data[plane])
        ສົ່ງຄືນ NULL;
    data = (uintptr_t)frame->extended_data[plane];

    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        ຖ້າ (data >= buf_begin && data < buf_begin + buf->size)
            ສົ່ງຄືນ buf;
    }
    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        ຖ້າ (data >= buf_begin && data < buf_begin + buf->size)
            ສົ່ງຄືນ buf;
    }
    ສົ່ງຄືນ NULL;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 ga_nanaa AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    ສົ່ງຄືນ
        ff_frame_side_data_add_from_buf(
            &frame->side_data, &frame->nb_side_data, type, buf);
}

AVFrameSideData *av_frame_new_side_data(AVFrame *frame,
                                        ga_nanaa AVFrameSideDataType type,
                                        size_t size)
{
    AVFrameSideData *ret;
    AVBufferRef *buf = av_buffer_alloc(size);
    ret = av_frame_new_side_data_from_buf(frame, type, buf);
    ຖ້າ (!ret)
        av_buffer_unref(&buf);
    ສົ່ງຄືນ ret;
}

AVFrameSideData *av_frame_get_side_data(const AVFrame *frame,
                                        ga_nanaa AVFrameSideDataType type)
{
    ສົ່ງຄືນ (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

static ຈຳນວນເຕັມ frame_copy_video(AVFrame *dst, const AVFrame *src)
{
    ຈຳນວນເຕັມ planes;

    ຖ້າ (dst->width  < src->width ||
        dst->height < src->height)
        ສົ່ງຄືນ AVERROR(EINVAL);

    ຖ້າ (src->hw_frames_ctx || dst->hw_frames_ctx)
        ສົ່ງຄືນ av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_count_planes(dst->format);
    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < planes; i++)
        ຖ້າ (!dst->data[i] || !src->data[i])
            ສົ່ງຄືນ AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    ສົ່ງຄືນ 0;
}

static ຈຳນວນເຕັມ frame_copy_audio(AVFrame *dst, const AVFrame *src)
{
    ຈຳນວນເຕັມ planar   = av_sample_fmt_is_planar(dst->format);
    ຈຳນວນເຕັມ channels = dst->ch_layout.nb_channels;
    ຈຳນວນເຕັມ planes   = planar ? channels : 1;

    ຖ້າ (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        ສົ່ງຄືນ AVERROR(EINVAL);

    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < planes; i++)
        ຖ້າ (!dst->extended_data[i] || !src->extended_data[i])
            ສົ່ງຄືນ AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    ສົ່ງຄືນ 0;
}

ຈຳນວນເຕັມ av_frame_copy(AVFrame *dst, const AVFrame *src)
{
    ຖ້າ (dst->format != src->format || dst->format < 0)
        ສົ່ງຄືນ AVERROR(EINVAL);

    ຖ້າ (dst->width > 0 && dst->height > 0)
        ສົ່ງຄືນ frame_copy_video(dst, src);
    ບໍ່ດັ່ງນັ້ນ ຖ້າ (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        ສົ່ງຄືນ frame_copy_audio(dst, src);

    ສົ່ງຄືນ AVERROR(EINVAL);
}

void av_frame_remove_side_data(AVFrame *frame, ga_nanaa AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

static ຈຳນວນເຕັມ calc_cropping_offsets(size_t offsets[4], const AVFrame *frame,
                                 const AVPixFmtDescriptor *desc)
{
    ສຳລັບ (ຈຳນວນເຕັມ i = 0; frame->data[i]; i++) {
        const AVComponentDescriptor *comp = NULL;
        ຈຳນວນເຕັມ shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        ຈຳນວນເຕັມ shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        ຖ້າ (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            bha_nga;
        }

        /* find any component descriptor for this plane */
        ສຳລັບ (ຈຳນວນເຕັມ j = 0; j < desc->nb_components; j++) {
            ຖ້າ (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                bha_nga;
            }
        }
        ຖ້າ (!comp)
            ສົ່ງຄືນ AVERROR_BUG;

        offsets[i] = (frame->crop_top  >> shift_y) * frame->linesize[i] +
                     (frame->crop_left >> shift_x) * comp->step;
    }

    ສົ່ງຄືນ 0;
}

ຈຳນວນເຕັມ av_frame_apply_cropping(AVFrame *frame, ຈຳນວນເຕັມ flags)
{
    const AVPixFmtDescriptor *desc;
    size_t offsets[4];
    ຈຳນວນເຕັມ ret;

    ຖ້າ (!(frame->width > 0 && frame->height > 0))
        ສົ່ງຄືນ AVERROR(EINVAL);

    ຖ້າ (frame->crop_left >= INT_MAX - frame->crop_right        ||
        frame->crop_top  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_left + frame->crop_right) >= frame->width ||
        (frame->crop_top + frame->crop_bottom) >= frame->height)
        ສົ່ງຄືນ AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    ຖ້າ (!desc)
        ສົ່ງຄືນ AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    ຖ້າ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_right;
        frame->height     -= frame->crop_bottom;
        frame->crop_right  = 0;
        frame->crop_bottom = 0;
        ສົ່ງຄືນ 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    ຖ້າ (ret < 0)
        ສົ່ງຄືນ ret;

    /* adjust the offsets to avoid breaking alignment */
    ຖ້າ (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        ຈຳນວນເຕັມ log2_crop_align = frame->crop_left ? ff_ctz(frame->crop_left) : INT_MAX;
        ຈຳນວນເຕັມ min_log2_align = INT_MAX;

        ສຳລັບ (ຈຳນວນເຕັມ i = 0; frame->data[i]; i++) {
            ຈຳນວນເຕັມ log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        ຖ້າ (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_left &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            ຖ້າ (ret < 0)
                ສົ່ງຄືນ ret;
        }
    }

    ສຳລັບ (ຈຳນວນເຕັມ i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_left + frame->crop_right);
    frame->height     -= (frame->crop_top  + frame->crop_bottom);
    frame->crop_left   = 0;
    frame->crop_right  = 0;
    frame->crop_top    = 0;
    frame->crop_bottom = 0;

    ສົ່ງຄືນ 0;
}
