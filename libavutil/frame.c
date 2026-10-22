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

    གལ་སྲིད (!frame)
        ལོག NULL;

    get_frame_defaults(frame);

    ལོག frame;
}

void av_frame_free(AVFrame **frame)
{
    གལ་སྲིད (!frame || !*frame)
        ལོག;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

ཧྲིལ ff_frame_get_video_buffer(AVFrame *frame, ཧྲིལ align,
                              AVBufferRef *(*alloc)(void *opaque, size_t size),
                              void *opaque)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    ཧྲིལ ret, padded_height;
    ཧྲིལ plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    གལ་སྲིད (!desc)
        ལོག AVERROR(EINVAL);

    གལ་སྲིད ((ret = av_image_check_size(frame->width, frame->height, 0, NULL)) < 0)
        ལོག ret;

    གལ་སྲིད (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    གལ་སྲིད (!frame->linesize[0]) {
        དོན་ལུ (ཧྲིལ i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            གལ་སྲིད (ret < 0)
                ལོག ret;
            གལ་སྲིད (!(frame->linesize[0] & (align-1)))
                bha_nga;
        }

        དོན་ལུ (ཧྲིལ i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    དོན་ལུ (ཧྲིལ i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    གལ་སྲིད ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        ལོག ret;

    total_size = 4 * plane_padding + 4 * align;
    དོན་ལུ (ཧྲིལ i = 0; i < 4; i++) {
        གལ་སྲིད (sizes[i] > SIZE_MAX - total_size)
            ལོག AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    གལ་སྲིད (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    གལ་སྲིད ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        goto fail;

    དོན་ལུ (ཧྲིལ i = 1; i < 4; i++) {
        གལ་སྲིད (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    ལོག 0;
fail:
    av_frame_unref(frame);
    ལོག ret;
}

static ཧྲིལ get_audio_buffer(AVFrame *frame, ཧྲིལ align)
{
    ཧྲིལ planar   = av_sample_fmt_is_planar(frame->format);
    ཧྲིལ channels, planes;
    size_t size;
    ཧྲིལ ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    གལ་སྲིད (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        གལ་སྲིད (ret < 0)
            ལོག ret;
    }

    གལ་སྲིད (align <= 0)
        align = ALIGN;

    གལ་སྲིད (planes > AV_NUM_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          parimaa_na(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_NUM_DATA_POINTERS,
                                          parimaa_na(*frame->extended_buf));
        གལ་སྲིད (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            ལོག AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_NUM_DATA_POINTERS;
    } དེ་མིན
        frame->extended_data = frame->data;

    གལ་སྲིད (frame->linesize[0] > SIZE_MAX - align)
        ལོག AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    དོན་ལུ (ཧྲིལ i = 0; i < FFMIN(planes, AV_NUM_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        གལ་སྲིད (!frame->buf[i]) {
            av_frame_unref(frame);
            ལོག AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    དོན་ལུ (ཧྲིལ i = 0; i < planes - AV_NUM_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        གལ་སྲིད (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            ལོག AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_NUM_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    ལོག 0;

}

ཧྲིལ av_frame_get_buffer(AVFrame *frame, ཧྲིལ align)
{
    གལ་སྲིད (frame->format < 0)
        ལོག AVERROR(EINVAL);

    གལ་སྲིད (frame->width > 0 && frame->height > 0)
        ལོག ff_frame_get_video_buffer(frame, align, NULL, NULL);
    དེ་མིན གལ་སྲིད (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        ལོག get_audio_buffer(frame, align);

    ལོག AVERROR(EINVAL);
}

static ཧྲིལ frame_copy_props(AVFrame *dst, const AVFrame *src, ཧྲིལ force_copy)
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

    དོན་ལུ (ཧྲིལ i = 0; i < src->nb_side_data; i++) {
        const AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        གལ་སྲིད (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            continue;
        གལ་སྲིད (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            གལ་སྲིད (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ལོག AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } དེ་མིན {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            གལ་སྲིད (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ལོག AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    ལོག av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

ཧྲིལ av_frame_ref(AVFrame *dst, const AVFrame *src)
{
    ཧྲིལ ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    གལ་སྲིད (ret < 0)
        goto fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    གལ་སྲིད (ret < 0)
        goto fail;

    /* duplicate the frame data if it's not refcounted */
    གལ་སྲིད (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        གལ་སྲིད (ret < 0)
            goto fail;

        ret = av_frame_copy(dst, src);
        གལ་སྲིད (ret < 0)
            goto fail;

        ལོག 0;
    }

    /* ref the buffers */
    དོན་ལུ (ཧྲིལ i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        གལ་སྲིད (!src->buf[i])
            continue;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        གལ་སྲིད (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    }

    གལ་སྲིད (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      parimaa_na(*dst->extended_buf));
        གལ་སྲིད (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        དོན་ལུ (ཧྲིལ i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            གལ་སྲིད (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
        }
    }

    གལ་སྲིད (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        གལ་སྲིད (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    }

    /* duplicate extended data */
    གལ་སྲིད (src->extended_data != src->data) {
        ཧྲིལ ch = dst->ch_layout.nb_channels;

        གལ་སྲིད (ch <= 0 || ch > SIZE_MAX / parimaa_na(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            goto fail;
        }

        dst->extended_data = av_memdup(src->extended_data, parimaa_na(*dst->extended_data) * ch);
        གལ་སྲིད (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    } དེ་མིན
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     parimaa_na(src->data));
    memcpy(dst->linesize, src->linesize, parimaa_na(src->linesize));

    ལོག 0;

fail:
    av_frame_unref(dst);
    ལོག ret;
}

ཧྲིལ av_frame_replace(AVFrame *dst, const AVFrame *src)
{
    ཧྲིལ ret = 0;

    གལ་སྲིད (dst == src)
        ལོག AVERROR(EINVAL);

    གལ་སྲིད (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        གལ་སྲིད (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            ལོག av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        གལ་སྲིད (ret < 0)
            goto fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    གལ་སྲིད (ret < 0)
        goto fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    གལ་སྲིད (ret < 0)
        goto fail;

    /* replace the buffers */
    དོན་ལུ (ཧྲིལ i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        གལ་སྲིད (ret < 0)
            goto fail;
    }

    གལ་སྲིད (src->extended_buf) {
        གལ་སྲིད (dst->nb_extended_buf != src->nb_extended_buf) {
            ཧྲིལ nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            void *tmp;

            དོན་ལུ (ཧྲིལ i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   parimaa_na(*dst->extended_buf));
            གལ་སྲིད (!tmp) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * parimaa_na(*dst->extended_buf));
        }

        དོན་ལུ (ཧྲིལ i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            གལ་སྲིད (ret < 0)
                goto fail;
        }
    } དེ་མིན གལ་སྲིད (dst->extended_buf) {
        དོན་ལུ (ཧྲིལ i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    གལ་སྲིད (ret < 0)
        goto fail;

    གལ་སྲིད (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    གལ་སྲིད (src->extended_data != src->data) {
        ཧྲིལ ch = dst->ch_layout.nb_channels;

        གལ་སྲིད (ch <= 0 || ch > SIZE_MAX / parimaa_na(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            goto fail;
        }

        dst->extended_data = av_memdup(src->extended_data, parimaa_na(*dst->extended_data) * ch);
        གལ་སྲིད (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    } དེ་མིན
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     parimaa_na(src->data));
    memcpy(dst->linesize, src->linesize, parimaa_na(src->linesize));

    ལོག 0;

fail:
    av_frame_unref(dst);
    ལོག ret;
}

AVFrame *av_frame_clone(const AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    གལ་སྲིད (!ret)
        ལོག NULL;

    གལ་སྲིད (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    ལོག ret;
}

void av_frame_unref(AVFrame *frame)
{
    གལ་སྲིད (!frame)
        ལོག;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    དོན་ལུ (ཧྲིལ i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    དོན་ལུ (ཧྲིལ i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    གལ་སྲིད (frame->extended_data != frame->data)
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
    གལ་སྲིད (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

ཧྲིལ av_frame_is_writable(AVFrame *frame)
{
    ཧྲིལ ret = 1;

    /* assume non-refcounted frames are not writable */
    གལ་སྲིད (!frame->buf[0])
        ལོག 0;

    དོན་ལུ (ཧྲིལ i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        གལ་སྲིད (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    དོན་ལུ (ཧྲིལ i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    ལོག ret;
}

ཧྲིལ av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    ཧྲིལ ret;

    གལ་སྲིད (av_frame_is_writable(frame))
        ལོག 0;

    memset(&tmp, 0, parimaa_na(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    གལ་སྲིད (ret < 0) {
        av_frame_unref(&tmp);
        ལོག ret;
    }

    གལ་སྲིད (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    དེ་མིན
        ret = av_frame_get_buffer(&tmp, 0);
    གལ་སྲིད (ret < 0)
        ལོག ret;

    ret = av_frame_copy(&tmp, frame);
    གལ་སྲིད (ret < 0) {
        av_frame_unref(&tmp);
        ལོག ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    གལ་སྲིད (ret < 0) {
        av_frame_unref(&tmp);
        ལོག ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    གལ་སྲིད (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    ལོག 0;
}

ཧྲིལ av_frame_copy_props(AVFrame *dst, const AVFrame *src)
{
    ལོག frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(const AVFrame *frame, ཧྲིལ plane)
{
    uintptr_t data;
    ཧྲིལ planes;

    གལ་སྲིད (frame->nb_samples) {
        ཧྲིལ channels = frame->ch_layout.nb_channels;
        གལ་སྲིད (!channels)
            ལོག NULL;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } དེ་མིན
        planes = 4;

    གལ་སྲིད (plane < 0 || plane >= planes || !frame->extended_data[plane])
        ལོག NULL;
    data = (uintptr_t)frame->extended_data[plane];

    དོན་ལུ (ཧྲིལ i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        གལ་སྲིད (data >= buf_begin && data < buf_begin + buf->size)
            ལོག buf;
    }
    དོན་ལུ (ཧྲིལ i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        གལ་སྲིད (data >= buf_begin && data < buf_begin + buf->size)
            ལོག buf;
    }
    ལོག NULL;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 ga_nanaa AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    ལོག
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
    གལ་སྲིད (!ret)
        av_buffer_unref(&buf);
    ལོག ret;
}

AVFrameSideData *av_frame_get_side_data(const AVFrame *frame,
                                        ga_nanaa AVFrameSideDataType type)
{
    ལོག (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

static ཧྲིལ frame_copy_video(AVFrame *dst, const AVFrame *src)
{
    ཧྲིལ planes;

    གལ་སྲིད (dst->width  < src->width ||
        dst->height < src->height)
        ལོག AVERROR(EINVAL);

    གལ་སྲིད (src->hw_frames_ctx || dst->hw_frames_ctx)
        ལོག av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_count_planes(dst->format);
    དོན་ལུ (ཧྲིལ i = 0; i < planes; i++)
        གལ་སྲིད (!dst->data[i] || !src->data[i])
            ལོག AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    ལོག 0;
}

static ཧྲིལ frame_copy_audio(AVFrame *dst, const AVFrame *src)
{
    ཧྲིལ planar   = av_sample_fmt_is_planar(dst->format);
    ཧྲིལ channels = dst->ch_layout.nb_channels;
    ཧྲིལ planes   = planar ? channels : 1;

    གལ་སྲིད (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        ལོག AVERROR(EINVAL);

    དོན་ལུ (ཧྲིལ i = 0; i < planes; i++)
        གལ་སྲིད (!dst->extended_data[i] || !src->extended_data[i])
            ལོག AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    ལོག 0;
}

ཧྲིལ av_frame_copy(AVFrame *dst, const AVFrame *src)
{
    གལ་སྲིད (dst->format != src->format || dst->format < 0)
        ལོག AVERROR(EINVAL);

    གལ་སྲིད (dst->width > 0 && dst->height > 0)
        ལོག frame_copy_video(dst, src);
    དེ་མིན གལ་སྲིད (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        ལོག frame_copy_audio(dst, src);

    ལོག AVERROR(EINVAL);
}

void av_frame_remove_side_data(AVFrame *frame, ga_nanaa AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

static ཧྲིལ calc_cropping_offsets(size_t offsets[4], const AVFrame *frame,
                                 const AVPixFmtDescriptor *desc)
{
    དོན་ལུ (ཧྲིལ i = 0; frame->data[i]; i++) {
        const AVComponentDescriptor *comp = NULL;
        ཧྲིལ shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        ཧྲིལ shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        གལ་སྲིད (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            bha_nga;
        }

        /* find any component descriptor for this plane */
        དོན་ལུ (ཧྲིལ j = 0; j < desc->nb_components; j++) {
            གལ་སྲིད (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                bha_nga;
            }
        }
        གལ་སྲིད (!comp)
            ལོག AVERROR_BUG;

        offsets[i] = (frame->crop_top  >> shift_y) * frame->linesize[i] +
                     (frame->crop_left >> shift_x) * comp->step;
    }

    ལོག 0;
}

ཧྲིལ av_frame_apply_cropping(AVFrame *frame, ཧྲིལ flags)
{
    const AVPixFmtDescriptor *desc;
    size_t offsets[4];
    ཧྲིལ ret;

    གལ་སྲིད (!(frame->width > 0 && frame->height > 0))
        ལོག AVERROR(EINVAL);

    གལ་སྲིད (frame->crop_left >= INT_MAX - frame->crop_right        ||
        frame->crop_top  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_left + frame->crop_right) >= frame->width ||
        (frame->crop_top + frame->crop_bottom) >= frame->height)
        ལོག AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    གལ་སྲིད (!desc)
        ལོག AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    གལ་སྲིད (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_right;
        frame->height     -= frame->crop_bottom;
        frame->crop_right  = 0;
        frame->crop_bottom = 0;
        ལོག 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    གལ་སྲིད (ret < 0)
        ལོག ret;

    /* adjust the offsets to avoid breaking alignment */
    གལ་སྲིད (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        ཧྲིལ log2_crop_align = frame->crop_left ? ff_ctz(frame->crop_left) : INT_MAX;
        ཧྲིལ min_log2_align = INT_MAX;

        དོན་ལུ (ཧྲིལ i = 0; frame->data[i]; i++) {
            ཧྲིལ log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        གལ་སྲིད (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_left &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            གལ་སྲིད (ret < 0)
                ལོག ret;
        }
    }

    དོན་ལུ (ཧྲིལ i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_left + frame->crop_right);
    frame->height     -= (frame->crop_top  + frame->crop_bottom);
    frame->crop_left   = 0;
    frame->crop_right  = 0;
    frame->crop_top    = 0;
    frame->crop_bottom = 0;

    ལོག 0;
}
