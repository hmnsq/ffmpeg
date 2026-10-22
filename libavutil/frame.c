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

#ضمن "channel_layout.h"
#ضمن "avassert.h"
#ضمن "buffer.h"
#ضمن "dict.h"
#ضمن "frame.h"
#ضمن "frame_internal.h"
#ضمن "imgutils.h"
#ضمن "mem.h"
#ضمن "refstruct.h"
#ضمن "samplefmt.h"
#ضمن "side_data.h"
#ضمن "hwcontext.h"

ساكن فراغ get_frame_defaults(AVFrame *frame)
{
    memset(frame, 0, حجم(*frame));

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

AVFrame *av_frame_alloc(فراغ)
{
    AVFrame *frame = av_malloc(حجم(*frame));

    ܐܢ (!frame)
        ܦܢܐ عدم;

    get_frame_defaults(frame);

    ܦܢܐ frame;
}

فراغ av_frame_free(AVFrame **frame)
{
    ܐܢ (!frame || !*frame)
        ܦܢܐ;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

صحيح ff_frame_get_video_buffer(AVFrame *frame, صحيح align,
                              AVBufferRef *(*alloc)(فراغ *opaque, size_t size),
                              فراغ *opaque)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    صحيح ret, padded_height;
    صحيح plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    ܐܢ (!desc)
        ܦܢܐ AVERROR(EINVAL);

    ܐܢ ((ret = av_image_check_size(frame->width, frame->height, 0, عدم)) < 0)
        ܦܢܐ ret;

    ܐܢ (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    ܐܢ (!frame->linesize[0]) {
        لكل (صحيح i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            ܐܢ (ret < 0)
                ܦܢܐ ret;
            ܐܢ (!(frame->linesize[0] & (align-1)))
                اكسر;
        }

        لكل (صحيح i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    لكل (صحيح i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    ܐܢ ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        ܦܢܐ ret;

    total_size = 4 * plane_padding + 4 * align;
    لكل (صحيح i = 0; i < 4; i++) {
        ܐܢ (sizes[i] > SIZE_MAX - total_size)
            ܦܢܐ AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    ܐܢ (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    ܐܢ ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        اذهب fail;

    لكل (صحيح i = 1; i < 4; i++) {
        ܐܢ (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    ܦܢܐ 0;
fail:
    av_frame_unref(frame);
    ܦܢܐ ret;
}

ساكن صحيح get_audio_buffer(AVFrame *frame, صحيح align)
{
    صحيح planar   = av_sample_fmt_is_planar(frame->format);
    صحيح channels, planes;
    size_t size;
    صحيح ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    ܐܢ (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        ܐܢ (ret < 0)
            ܦܢܐ ret;
    }

    ܐܢ (align <= 0)
        align = ALIGN;

    ܐܢ (planes > AV_NUM_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          حجم(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_NUM_DATA_POINTERS,
                                          حجم(*frame->extended_buf));
        ܐܢ (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            ܦܢܐ AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_NUM_DATA_POINTERS;
    } ܐܚܪܢܐ
        frame->extended_data = frame->data;

    ܐܢ (frame->linesize[0] > SIZE_MAX - align)
        ܦܢܐ AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    لكل (صحيح i = 0; i < FFMIN(planes, AV_NUM_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        ܐܢ (!frame->buf[i]) {
            av_frame_unref(frame);
            ܦܢܐ AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    لكل (صحيح i = 0; i < planes - AV_NUM_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        ܐܢ (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            ܦܢܐ AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_NUM_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    ܦܢܐ 0;

}

صحيح av_frame_get_buffer(AVFrame *frame, صحيح align)
{
    ܐܢ (frame->format < 0)
        ܦܢܐ AVERROR(EINVAL);

    ܐܢ (frame->width > 0 && frame->height > 0)
        ܦܢܐ ff_frame_get_video_buffer(frame, align, عدم, عدم);
    ܐܚܪܢܐ ܐܢ (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        ܦܢܐ get_audio_buffer(frame, align);

    ܦܢܐ AVERROR(EINVAL);
}

ساكن صحيح frame_copy_props(AVFrame *dst, ثابت AVFrame *src, صحيح force_copy)
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

    لكل (صحيح i = 0; i < src->nb_side_data; i++) {
        ثابت AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        ܐܢ (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            استمر;
        ܐܢ (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            ܐܢ (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ܦܢܐ AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } ܐܚܪܢܐ {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            ܐܢ (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ܦܢܐ AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    ܦܢܐ av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

صحيح av_frame_ref(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    ܐܢ (ret < 0)
        اذهب fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ܐܢ (ret < 0)
        اذهب fail;

    /* duplicate the frame data if it's not refcounted */
    ܐܢ (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        ܐܢ (ret < 0)
            اذهب fail;

        ret = av_frame_copy(dst, src);
        ܐܢ (ret < 0)
            اذهب fail;

        ܦܢܐ 0;
    }

    /* ref the buffers */
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ܐܢ (!src->buf[i])
            استمر;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        ܐܢ (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    }

    ܐܢ (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      حجم(*dst->extended_buf));
        ܐܢ (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        لكل (صحيح i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            ܐܢ (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                اذهب fail;
            }
        }
    }

    ܐܢ (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        ܐܢ (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    }

    /* duplicate extended data */
    ܐܢ (src->extended_data != src->data) {
        صحيح ch = dst->ch_layout.nb_channels;

        ܐܢ (ch <= 0 || ch > SIZE_MAX / حجم(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            اذهب fail;
        }

        dst->extended_data = av_memdup(src->extended_data, حجم(*dst->extended_data) * ch);
        ܐܢ (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    } ܐܚܪܢܐ
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     حجم(src->data));
    memcpy(dst->linesize, src->linesize, حجم(src->linesize));

    ܦܢܐ 0;

fail:
    av_frame_unref(dst);
    ܦܢܐ ret;
}

صحيح av_frame_replace(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح ret = 0;

    ܐܢ (dst == src)
        ܦܢܐ AVERROR(EINVAL);

    ܐܢ (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        ܐܢ (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            ܦܢܐ av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        ܐܢ (ret < 0)
            اذهب fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ܐܢ (ret < 0)
        اذهب fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    ܐܢ (ret < 0)
        اذهب fail;

    /* replace the buffers */
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        ܐܢ (ret < 0)
            اذهب fail;
    }

    ܐܢ (src->extended_buf) {
        ܐܢ (dst->nb_extended_buf != src->nb_extended_buf) {
            صحيح nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            فراغ *tmp;

            لكل (صحيح i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   حجم(*dst->extended_buf));
            ܐܢ (!tmp) {
                ret = AVERROR(ENOMEM);
                اذهب fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * حجم(*dst->extended_buf));
        }

        لكل (صحيح i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            ܐܢ (ret < 0)
                اذهب fail;
        }
    } ܐܚܪܢܐ ܐܢ (dst->extended_buf) {
        لكل (صحيح i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    ܐܢ (ret < 0)
        اذهب fail;

    ܐܢ (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    ܐܢ (src->extended_data != src->data) {
        صحيح ch = dst->ch_layout.nb_channels;

        ܐܢ (ch <= 0 || ch > SIZE_MAX / حجم(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            اذهب fail;
        }

        dst->extended_data = av_memdup(src->extended_data, حجم(*dst->extended_data) * ch);
        ܐܢ (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    } ܐܚܪܢܐ
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     حجم(src->data));
    memcpy(dst->linesize, src->linesize, حجم(src->linesize));

    ܦܢܐ 0;

fail:
    av_frame_unref(dst);
    ܦܢܐ ret;
}

AVFrame *av_frame_clone(ثابت AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    ܐܢ (!ret)
        ܦܢܐ عدم;

    ܐܢ (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    ܦܢܐ ret;
}

فراغ av_frame_unref(AVFrame *frame)
{
    ܐܢ (!frame)
        ܦܢܐ;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    لكل (صحيح i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    ܐܢ (frame->extended_data != frame->data)
        av_freep(&frame->extended_data);

    av_channel_layout_uninit(&frame->ch_layout);

    get_frame_defaults(frame);
}

فراغ av_frame_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    *dst = *src;
    ܐܢ (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

صحيح av_frame_is_writable(AVFrame *frame)
{
    صحيح ret = 1;

    /* assume non-refcounted frames are not writable */
    ܐܢ (!frame->buf[0])
        ܦܢܐ 0;

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        ܐܢ (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    لكل (صحيح i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    ܦܢܐ ret;
}

صحيح av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    صحيح ret;

    ܐܢ (av_frame_is_writable(frame))
        ܦܢܐ 0;

    memset(&tmp, 0, حجم(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    ܐܢ (ret < 0) {
        av_frame_unref(&tmp);
        ܦܢܐ ret;
    }

    ܐܢ (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    ܐܚܪܢܐ
        ret = av_frame_get_buffer(&tmp, 0);
    ܐܢ (ret < 0)
        ܦܢܐ ret;

    ret = av_frame_copy(&tmp, frame);
    ܐܢ (ret < 0) {
        av_frame_unref(&tmp);
        ܦܢܐ ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    ܐܢ (ret < 0) {
        av_frame_unref(&tmp);
        ܦܢܐ ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    ܐܢ (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    ܦܢܐ 0;
}

صحيح av_frame_copy_props(AVFrame *dst, ثابت AVFrame *src)
{
    ܦܢܐ frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(ثابت AVFrame *frame, صحيح plane)
{
    uintptr_t data;
    صحيح planes;

    ܐܢ (frame->nb_samples) {
        صحيح channels = frame->ch_layout.nb_channels;
        ܐܢ (!channels)
            ܦܢܐ عدم;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } ܐܚܪܢܐ
        planes = 4;

    ܐܢ (plane < 0 || plane >= planes || !frame->extended_data[plane])
        ܦܢܐ عدم;
    data = (uintptr_t)frame->extended_data[plane];

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        ܐܢ (data >= buf_begin && data < buf_begin + buf->size)
            ܦܢܐ buf;
    }
    لكل (صحيح i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        ܐܢ (data >= buf_begin && data < buf_begin + buf->size)
            ܦܢܐ buf;
    }
    ܦܢܐ عدم;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 تعداد AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    ܦܢܐ
        ff_frame_side_data_add_from_buf(
            &frame->side_data, &frame->nb_side_data, type, buf);
}

AVFrameSideData *av_frame_new_side_data(AVFrame *frame,
                                        تعداد AVFrameSideDataType type,
                                        size_t size)
{
    AVFrameSideData *ret;
    AVBufferRef *buf = av_buffer_alloc(size);
    ret = av_frame_new_side_data_from_buf(frame, type, buf);
    ܐܢ (!ret)
        av_buffer_unref(&buf);
    ܦܢܐ ret;
}

AVFrameSideData *av_frame_get_side_data(ثابت AVFrame *frame,
                                        تعداد AVFrameSideDataType type)
{
    ܦܢܐ (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

ساكن صحيح frame_copy_video(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح planes;

    ܐܢ (dst->width  < src->width ||
        dst->height < src->height)
        ܦܢܐ AVERROR(EINVAL);

    ܐܢ (src->hw_frames_ctx || dst->hw_frames_ctx)
        ܦܢܐ av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_count_planes(dst->format);
    لكل (صحيح i = 0; i < planes; i++)
        ܐܢ (!dst->data[i] || !src->data[i])
            ܦܢܐ AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    ܦܢܐ 0;
}

ساكن صحيح frame_copy_audio(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح planar   = av_sample_fmt_is_planar(dst->format);
    صحيح channels = dst->ch_layout.nb_channels;
    صحيح planes   = planar ? channels : 1;

    ܐܢ (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        ܦܢܐ AVERROR(EINVAL);

    لكل (صحيح i = 0; i < planes; i++)
        ܐܢ (!dst->extended_data[i] || !src->extended_data[i])
            ܦܢܐ AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    ܦܢܐ 0;
}

صحيح av_frame_copy(AVFrame *dst, ثابت AVFrame *src)
{
    ܐܢ (dst->format != src->format || dst->format < 0)
        ܦܢܐ AVERROR(EINVAL);

    ܐܢ (dst->width > 0 && dst->height > 0)
        ܦܢܐ frame_copy_video(dst, src);
    ܐܚܪܢܐ ܐܢ (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        ܦܢܐ frame_copy_audio(dst, src);

    ܦܢܐ AVERROR(EINVAL);
}

فراغ av_frame_remove_side_data(AVFrame *frame, تعداد AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

ساكن صحيح calc_cropping_offsets(size_t offsets[4], ثابت AVFrame *frame,
                                 ثابت AVPixFmtDescriptor *desc)
{
    لكل (صحيح i = 0; frame->data[i]; i++) {
        ثابت AVComponentDescriptor *comp = عدم;
        صحيح shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        صحيح shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        ܐܢ (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            اكسر;
        }

        /* find any component descriptor for this plane */
        لكل (صحيح j = 0; j < desc->nb_components; j++) {
            ܐܢ (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                اكسر;
            }
        }
        ܐܢ (!comp)
            ܦܢܐ AVERROR_BUG;

        offsets[i] = (frame->crop_top  >> shift_y) * frame->linesize[i] +
                     (frame->crop_left >> shift_x) * comp->step;
    }

    ܦܢܐ 0;
}

صحيح av_frame_apply_cropping(AVFrame *frame, صحيح flags)
{
    ثابت AVPixFmtDescriptor *desc;
    size_t offsets[4];
    صحيح ret;

    ܐܢ (!(frame->width > 0 && frame->height > 0))
        ܦܢܐ AVERROR(EINVAL);

    ܐܢ (frame->crop_left >= INT_MAX - frame->crop_right        ||
        frame->crop_top  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_left + frame->crop_right) >= frame->width ||
        (frame->crop_top + frame->crop_bottom) >= frame->height)
        ܦܢܐ AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    ܐܢ (!desc)
        ܦܢܐ AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    ܐܢ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_right;
        frame->height     -= frame->crop_bottom;
        frame->crop_right  = 0;
        frame->crop_bottom = 0;
        ܦܢܐ 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    ܐܢ (ret < 0)
        ܦܢܐ ret;

    /* adjust the offsets to avoid breaking alignment */
    ܐܢ (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        صحيح log2_crop_align = frame->crop_left ? ff_ctz(frame->crop_left) : INT_MAX;
        صحيح min_log2_align = INT_MAX;

        لكل (صحيح i = 0; frame->data[i]; i++) {
            صحيح log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        ܐܢ (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_left &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            ܐܢ (ret < 0)
                ܦܢܐ ret;
        }
    }

    لكل (صحيح i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_left + frame->crop_right);
    frame->height     -= (frame->crop_top  + frame->crop_bottom);
    frame->crop_left   = 0;
    frame->crop_right  = 0;
    frame->crop_top    = 0;
    frame->crop_bottom = 0;

    ܦܢܐ 0;
}
