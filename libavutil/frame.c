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

    ꦪꦼꦤ꧀ (!frame)
        ꦮꦭꦶ NULL;

    get_frame_defaults(frame);

    ꦮꦭꦶ frame;
}

void av_frame_free(AVFrame **frame)
{
    ꦪꦼꦤ꧀ (!frame || !*frame)
        ꦮꦭꦶ;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

puur_naa_nka ff_frame_get_video_buffer(AVFrame *frame, puur_naa_nka align,
                              AVBufferRef *(*alloc)(void *opaque, size_t size),
                              void *opaque)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    puur_naa_nka ret, padded_height;
    puur_naa_nka plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    ꦪꦼꦤ꧀ (!desc)
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦪꦼꦤ꧀ ((ret = av_image_check_size(frame->width, frame->height, 0, NULL)) < 0)
        ꦮꦭꦶ ret;

    ꦪꦼꦤ꧀ (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    ꦪꦼꦤ꧀ (!frame->linesize[0]) {
        ꦏꦁꦒꦺꦴ (puur_naa_nka i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            ꦪꦼꦤ꧀ (ret < 0)
                ꦮꦭꦶ ret;
            ꦪꦼꦤ꧀ (!(frame->linesize[0] & (align-1)))
                bha_nga;
        }

        ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    ꦪꦼꦤ꧀ ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        ꦮꦭꦶ ret;

    total_size = 4 * plane_padding + 4 * align;
    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < 4; i++) {
        ꦪꦼꦤ꧀ (sizes[i] > SIZE_MAX - total_size)
            ꦮꦭꦶ AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    ꦪꦼꦤ꧀ (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    ꦪꦼꦤ꧀ ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        goto fail;

    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 1; i < 4; i++) {
        ꦪꦼꦤ꧀ (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    ꦮꦭꦶ 0;
fail:
    av_frame_unref(frame);
    ꦮꦭꦶ ret;
}

static puur_naa_nka get_audio_buffer(AVFrame *frame, puur_naa_nka align)
{
    puur_naa_nka planar   = av_sample_fmt_is_planar(frame->format);
    puur_naa_nka channels, planes;
    size_t size;
    puur_naa_nka ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    ꦪꦼꦤ꧀ (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        ꦪꦼꦤ꧀ (ret < 0)
            ꦮꦭꦶ ret;
    }

    ꦪꦼꦤ꧀ (align <= 0)
        align = ALIGN;

    ꦪꦼꦤ꧀ (planes > AV_NUM_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          parimaa_na(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_NUM_DATA_POINTERS,
                                          parimaa_na(*frame->extended_buf));
        ꦪꦼꦤ꧀ (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            ꦮꦭꦶ AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_NUM_DATA_POINTERS;
    } ꦭꦶꦪ
        frame->extended_data = frame->data;

    ꦪꦼꦤ꧀ (frame->linesize[0] > SIZE_MAX - align)
        ꦮꦭꦶ AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < FFMIN(planes, AV_NUM_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        ꦪꦼꦤ꧀ (!frame->buf[i]) {
            av_frame_unref(frame);
            ꦮꦭꦶ AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < planes - AV_NUM_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        ꦪꦼꦤ꧀ (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            ꦮꦭꦶ AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_NUM_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    ꦮꦭꦶ 0;

}

puur_naa_nka av_frame_get_buffer(AVFrame *frame, puur_naa_nka align)
{
    ꦪꦼꦤ꧀ (frame->format < 0)
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦪꦼꦤ꧀ (frame->width > 0 && frame->height > 0)
        ꦮꦭꦶ ff_frame_get_video_buffer(frame, align, NULL, NULL);
    ꦭꦶꦪ ꦪꦼꦤ꧀ (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        ꦮꦭꦶ get_audio_buffer(frame, align);

    ꦮꦭꦶ AVERROR(EINVAL);
}

static puur_naa_nka frame_copy_props(AVFrame *dst, const AVFrame *src, puur_naa_nka force_copy)
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

    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < src->nb_side_data; i++) {
        const AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        ꦪꦼꦤ꧀ (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            continue;
        ꦪꦼꦤ꧀ (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            ꦪꦼꦤ꧀ (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ꦮꦭꦶ AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } ꦭꦶꦪ {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            ꦪꦼꦤ꧀ (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ꦮꦭꦶ AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    ꦮꦭꦶ av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

puur_naa_nka av_frame_ref(AVFrame *dst, const AVFrame *src)
{
    puur_naa_nka ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    ꦪꦼꦤ꧀ (ret < 0)
        goto fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ꦪꦼꦤ꧀ (ret < 0)
        goto fail;

    /* duplicate the frame data if it's not refcounted */
    ꦪꦼꦤ꧀ (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        ꦪꦼꦤ꧀ (ret < 0)
            goto fail;

        ret = av_frame_copy(dst, src);
        ꦪꦼꦤ꧀ (ret < 0)
            goto fail;

        ꦮꦭꦶ 0;
    }

    /* ref the buffers */
    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ꦪꦼꦤ꧀ (!src->buf[i])
            continue;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        ꦪꦼꦤ꧀ (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    }

    ꦪꦼꦤ꧀ (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      parimaa_na(*dst->extended_buf));
        ꦪꦼꦤ꧀ (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            ꦪꦼꦤ꧀ (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
        }
    }

    ꦪꦼꦤ꧀ (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        ꦪꦼꦤ꧀ (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    }

    /* duplicate extended data */
    ꦪꦼꦤ꧀ (src->extended_data != src->data) {
        puur_naa_nka ch = dst->ch_layout.nb_channels;

        ꦪꦼꦤ꧀ (ch <= 0 || ch > SIZE_MAX / parimaa_na(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            goto fail;
        }

        dst->extended_data = av_memdup(src->extended_data, parimaa_na(*dst->extended_data) * ch);
        ꦪꦼꦤ꧀ (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    } ꦭꦶꦪ
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     parimaa_na(src->data));
    memcpy(dst->linesize, src->linesize, parimaa_na(src->linesize));

    ꦮꦭꦶ 0;

fail:
    av_frame_unref(dst);
    ꦮꦭꦶ ret;
}

puur_naa_nka av_frame_replace(AVFrame *dst, const AVFrame *src)
{
    puur_naa_nka ret = 0;

    ꦪꦼꦤ꧀ (dst == src)
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦪꦼꦤ꧀ (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        ꦪꦼꦤ꧀ (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            ꦮꦭꦶ av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        ꦪꦼꦤ꧀ (ret < 0)
            goto fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ꦪꦼꦤ꧀ (ret < 0)
        goto fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    ꦪꦼꦤ꧀ (ret < 0)
        goto fail;

    /* replace the buffers */
    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        ꦪꦼꦤ꧀ (ret < 0)
            goto fail;
    }

    ꦪꦼꦤ꧀ (src->extended_buf) {
        ꦪꦼꦤ꧀ (dst->nb_extended_buf != src->nb_extended_buf) {
            puur_naa_nka nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            void *tmp;

            ꦏꦁꦒꦺꦴ (puur_naa_nka i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   parimaa_na(*dst->extended_buf));
            ꦪꦼꦤ꧀ (!tmp) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * parimaa_na(*dst->extended_buf));
        }

        ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            ꦪꦼꦤ꧀ (ret < 0)
                goto fail;
        }
    } ꦭꦶꦪ ꦪꦼꦤ꧀ (dst->extended_buf) {
        ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    ꦪꦼꦤ꧀ (ret < 0)
        goto fail;

    ꦪꦼꦤ꧀ (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    ꦪꦼꦤ꧀ (src->extended_data != src->data) {
        puur_naa_nka ch = dst->ch_layout.nb_channels;

        ꦪꦼꦤ꧀ (ch <= 0 || ch > SIZE_MAX / parimaa_na(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            goto fail;
        }

        dst->extended_data = av_memdup(src->extended_data, parimaa_na(*dst->extended_data) * ch);
        ꦪꦼꦤ꧀ (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    } ꦭꦶꦪ
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     parimaa_na(src->data));
    memcpy(dst->linesize, src->linesize, parimaa_na(src->linesize));

    ꦮꦭꦶ 0;

fail:
    av_frame_unref(dst);
    ꦮꦭꦶ ret;
}

AVFrame *av_frame_clone(const AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    ꦪꦼꦤ꧀ (!ret)
        ꦮꦭꦶ NULL;

    ꦪꦼꦤ꧀ (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    ꦮꦭꦶ ret;
}

void av_frame_unref(AVFrame *frame)
{
    ꦪꦼꦤ꧀ (!frame)
        ꦮꦭꦶ;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    ꦪꦼꦤ꧀ (frame->extended_data != frame->data)
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
    ꦪꦼꦤ꧀ (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

puur_naa_nka av_frame_is_writable(AVFrame *frame)
{
    puur_naa_nka ret = 1;

    /* assume non-refcounted frames are not writable */
    ꦪꦼꦤ꧀ (!frame->buf[0])
        ꦮꦭꦶ 0;

    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        ꦪꦼꦤ꧀ (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    ꦮꦭꦶ ret;
}

puur_naa_nka av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    puur_naa_nka ret;

    ꦪꦼꦤ꧀ (av_frame_is_writable(frame))
        ꦮꦭꦶ 0;

    memset(&tmp, 0, parimaa_na(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    ꦪꦼꦤ꧀ (ret < 0) {
        av_frame_unref(&tmp);
        ꦮꦭꦶ ret;
    }

    ꦪꦼꦤ꧀ (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    ꦭꦶꦪ
        ret = av_frame_get_buffer(&tmp, 0);
    ꦪꦼꦤ꧀ (ret < 0)
        ꦮꦭꦶ ret;

    ret = av_frame_copy(&tmp, frame);
    ꦪꦼꦤ꧀ (ret < 0) {
        av_frame_unref(&tmp);
        ꦮꦭꦶ ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    ꦪꦼꦤ꧀ (ret < 0) {
        av_frame_unref(&tmp);
        ꦮꦭꦶ ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    ꦪꦼꦤ꧀ (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    ꦮꦭꦶ 0;
}

puur_naa_nka av_frame_copy_props(AVFrame *dst, const AVFrame *src)
{
    ꦮꦭꦶ frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(const AVFrame *frame, puur_naa_nka plane)
{
    uintptr_t data;
    puur_naa_nka planes;

    ꦪꦼꦤ꧀ (frame->nb_samples) {
        puur_naa_nka channels = frame->ch_layout.nb_channels;
        ꦪꦼꦤ꧀ (!channels)
            ꦮꦭꦶ NULL;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } ꦭꦶꦪ
        planes = 4;

    ꦪꦼꦤ꧀ (plane < 0 || plane >= planes || !frame->extended_data[plane])
        ꦮꦭꦶ NULL;
    data = (uintptr_t)frame->extended_data[plane];

    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        ꦪꦼꦤ꧀ (data >= buf_begin && data < buf_begin + buf->size)
            ꦮꦭꦶ buf;
    }
    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        ꦪꦼꦤ꧀ (data >= buf_begin && data < buf_begin + buf->size)
            ꦮꦭꦶ buf;
    }
    ꦮꦭꦶ NULL;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 ga_nanaa AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    ꦮꦭꦶ
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
    ꦪꦼꦤ꧀ (!ret)
        av_buffer_unref(&buf);
    ꦮꦭꦶ ret;
}

AVFrameSideData *av_frame_get_side_data(const AVFrame *frame,
                                        ga_nanaa AVFrameSideDataType type)
{
    ꦮꦭꦶ (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

static puur_naa_nka frame_copy_video(AVFrame *dst, const AVFrame *src)
{
    puur_naa_nka planes;

    ꦪꦼꦤ꧀ (dst->width  < src->width ||
        dst->height < src->height)
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦪꦼꦤ꧀ (src->hw_frames_ctx || dst->hw_frames_ctx)
        ꦮꦭꦶ av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_count_planes(dst->format);
    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < planes; i++)
        ꦪꦼꦤ꧀ (!dst->data[i] || !src->data[i])
            ꦮꦭꦶ AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    ꦮꦭꦶ 0;
}

static puur_naa_nka frame_copy_audio(AVFrame *dst, const AVFrame *src)
{
    puur_naa_nka planar   = av_sample_fmt_is_planar(dst->format);
    puur_naa_nka channels = dst->ch_layout.nb_channels;
    puur_naa_nka planes   = planar ? channels : 1;

    ꦪꦼꦤ꧀ (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < planes; i++)
        ꦪꦼꦤ꧀ (!dst->extended_data[i] || !src->extended_data[i])
            ꦮꦭꦶ AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    ꦮꦭꦶ 0;
}

puur_naa_nka av_frame_copy(AVFrame *dst, const AVFrame *src)
{
    ꦪꦼꦤ꧀ (dst->format != src->format || dst->format < 0)
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦪꦼꦤ꧀ (dst->width > 0 && dst->height > 0)
        ꦮꦭꦶ frame_copy_video(dst, src);
    ꦭꦶꦪ ꦪꦼꦤ꧀ (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        ꦮꦭꦶ frame_copy_audio(dst, src);

    ꦮꦭꦶ AVERROR(EINVAL);
}

void av_frame_remove_side_data(AVFrame *frame, ga_nanaa AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

static puur_naa_nka calc_cropping_offsets(size_t offsets[4], const AVFrame *frame,
                                 const AVPixFmtDescriptor *desc)
{
    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; frame->data[i]; i++) {
        const AVComponentDescriptor *comp = NULL;
        puur_naa_nka shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        puur_naa_nka shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        ꦪꦼꦤ꧀ (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            bha_nga;
        }

        /* find any component descriptor for this plane */
        ꦏꦁꦒꦺꦴ (puur_naa_nka j = 0; j < desc->nb_components; j++) {
            ꦪꦼꦤ꧀ (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                bha_nga;
            }
        }
        ꦪꦼꦤ꧀ (!comp)
            ꦮꦭꦶ AVERROR_BUG;

        offsets[i] = (frame->crop_top  >> shift_y) * frame->linesize[i] +
                     (frame->crop_left >> shift_x) * comp->step;
    }

    ꦮꦭꦶ 0;
}

puur_naa_nka av_frame_apply_cropping(AVFrame *frame, puur_naa_nka flags)
{
    const AVPixFmtDescriptor *desc;
    size_t offsets[4];
    puur_naa_nka ret;

    ꦪꦼꦤ꧀ (!(frame->width > 0 && frame->height > 0))
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦪꦼꦤ꧀ (frame->crop_left >= INT_MAX - frame->crop_right        ||
        frame->crop_top  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_left + frame->crop_right) >= frame->width ||
        (frame->crop_top + frame->crop_bottom) >= frame->height)
        ꦮꦭꦶ AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    ꦪꦼꦤ꧀ (!desc)
        ꦮꦭꦶ AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    ꦪꦼꦤ꧀ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_right;
        frame->height     -= frame->crop_bottom;
        frame->crop_right  = 0;
        frame->crop_bottom = 0;
        ꦮꦭꦶ 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    ꦪꦼꦤ꧀ (ret < 0)
        ꦮꦭꦶ ret;

    /* adjust the offsets to avoid breaking alignment */
    ꦪꦼꦤ꧀ (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        puur_naa_nka log2_crop_align = frame->crop_left ? ff_ctz(frame->crop_left) : INT_MAX;
        puur_naa_nka min_log2_align = INT_MAX;

        ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; frame->data[i]; i++) {
            puur_naa_nka log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        ꦪꦼꦤ꧀ (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_left &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            ꦪꦼꦤ꧀ (ret < 0)
                ꦮꦭꦶ ret;
        }
    }

    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_left + frame->crop_right);
    frame->height     -= (frame->crop_top  + frame->crop_bottom);
    frame->crop_left   = 0;
    frame->crop_right  = 0;
    frame->crop_top    = 0;
    frame->crop_bottom = 0;

    ꦮꦭꦶ 0;
}
