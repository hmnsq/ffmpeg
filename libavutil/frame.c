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

    אם (!frame)
        החזר عدم;

    get_frame_defaults(frame);

    החזר frame;
}

فراغ av_frame_free(AVFrame **frame)
{
    אם (!frame || !*frame)
        החזר;

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

    אם (!desc)
        החזר AVERROR(EINVAL);

    אם ((ret = av_image_check_size(frame->width, frame->height, 0, عدم)) < 0)
        החזר ret;

    אם (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    אם (!frame->linesize[0]) {
        עבור (صحيح i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            אם (ret < 0)
                החזר ret;
            אם (!(frame->linesize[0] & (align-1)))
                اكسر;
        }

        עבור (صحيح i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    עבור (صحيح i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    אם ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        החזר ret;

    total_size = 4 * plane_padding + 4 * align;
    עבור (صحيح i = 0; i < 4; i++) {
        אם (sizes[i] > SIZE_MAX - total_size)
            החזר AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    אם (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    אם ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        اذهب fail;

    עבור (صحيح i = 1; i < 4; i++) {
        אם (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    החזר 0;
fail:
    av_frame_unref(frame);
    החזר ret;
}

ساكن صحيح get_audio_buffer(AVFrame *frame, صحيح align)
{
    صحيح planar   = av_sample_fmt_is_planar(frame->format);
    صحيح channels, planes;
    size_t size;
    صحيح ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    אם (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        אם (ret < 0)
            החזר ret;
    }

    אם (align <= 0)
        align = ALIGN;

    אם (planes > AV_NUM_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          حجم(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_NUM_DATA_POINTERS,
                                          حجم(*frame->extended_buf));
        אם (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            החזר AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_NUM_DATA_POINTERS;
    } אחרת
        frame->extended_data = frame->data;

    אם (frame->linesize[0] > SIZE_MAX - align)
        החזר AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    עבור (صحيح i = 0; i < FFMIN(planes, AV_NUM_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        אם (!frame->buf[i]) {
            av_frame_unref(frame);
            החזר AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    עבור (صحيح i = 0; i < planes - AV_NUM_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        אם (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            החזר AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_NUM_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    החזר 0;

}

صحيح av_frame_get_buffer(AVFrame *frame, صحيح align)
{
    אם (frame->format < 0)
        החזר AVERROR(EINVAL);

    אם (frame->width > 0 && frame->height > 0)
        החזר ff_frame_get_video_buffer(frame, align, عدم, عدم);
    אחרת אם (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        החזר get_audio_buffer(frame, align);

    החזר AVERROR(EINVAL);
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

    עבור (صحيح i = 0; i < src->nb_side_data; i++) {
        ثابت AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        אם (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            استمر;
        אם (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            אם (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                החזר AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } אחרת {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            אם (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                החזר AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    החזר av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
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
    אם (ret < 0)
        اذهب fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    אם (ret < 0)
        اذهب fail;

    /* duplicate the frame data if it's not refcounted */
    אם (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        אם (ret < 0)
            اذهب fail;

        ret = av_frame_copy(dst, src);
        אם (ret < 0)
            اذهب fail;

        החזר 0;
    }

    /* ref the buffers */
    עבור (صحيح i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        אם (!src->buf[i])
            استمر;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        אם (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    }

    אם (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      حجم(*dst->extended_buf));
        אם (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        עבור (صحيح i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            אם (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                اذهب fail;
            }
        }
    }

    אם (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        אם (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    }

    /* duplicate extended data */
    אם (src->extended_data != src->data) {
        صحيح ch = dst->ch_layout.nb_channels;

        אם (ch <= 0 || ch > SIZE_MAX / حجم(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            اذهب fail;
        }

        dst->extended_data = av_memdup(src->extended_data, حجم(*dst->extended_data) * ch);
        אם (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    } אחרת
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     حجم(src->data));
    memcpy(dst->linesize, src->linesize, حجم(src->linesize));

    החזר 0;

fail:
    av_frame_unref(dst);
    החזר ret;
}

صحيح av_frame_replace(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح ret = 0;

    אם (dst == src)
        החזר AVERROR(EINVAL);

    אם (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        אם (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            החזר av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        אם (ret < 0)
            اذهب fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    אם (ret < 0)
        اذهب fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    אם (ret < 0)
        اذهب fail;

    /* replace the buffers */
    עבור (صحيح i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        אם (ret < 0)
            اذهب fail;
    }

    אם (src->extended_buf) {
        אם (dst->nb_extended_buf != src->nb_extended_buf) {
            صحيح nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            فراغ *tmp;

            עבור (صحيح i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   حجم(*dst->extended_buf));
            אם (!tmp) {
                ret = AVERROR(ENOMEM);
                اذهب fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * حجم(*dst->extended_buf));
        }

        עבור (صحيح i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            אם (ret < 0)
                اذهب fail;
        }
    } אחרת אם (dst->extended_buf) {
        עבור (صحيح i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    אם (ret < 0)
        اذهب fail;

    אם (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    אם (src->extended_data != src->data) {
        صحيح ch = dst->ch_layout.nb_channels;

        אם (ch <= 0 || ch > SIZE_MAX / حجم(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            اذهب fail;
        }

        dst->extended_data = av_memdup(src->extended_data, حجم(*dst->extended_data) * ch);
        אם (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    } אחרת
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     حجم(src->data));
    memcpy(dst->linesize, src->linesize, حجم(src->linesize));

    החזר 0;

fail:
    av_frame_unref(dst);
    החזר ret;
}

AVFrame *av_frame_clone(ثابت AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    אם (!ret)
        החזר عدم;

    אם (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    החזר ret;
}

فراغ av_frame_unref(AVFrame *frame)
{
    אם (!frame)
        החזר;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    עבור (صحيح i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    עבור (صحيح i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    אם (frame->extended_data != frame->data)
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
    אם (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

صحيح av_frame_is_writable(AVFrame *frame)
{
    صحيح ret = 1;

    /* assume non-refcounted frames are not writable */
    אם (!frame->buf[0])
        החזר 0;

    עבור (صحيح i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        אם (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    עבור (صحيح i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    החזר ret;
}

صحيح av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    صحيح ret;

    אם (av_frame_is_writable(frame))
        החזר 0;

    memset(&tmp, 0, حجم(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    אם (ret < 0) {
        av_frame_unref(&tmp);
        החזר ret;
    }

    אם (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    אחרת
        ret = av_frame_get_buffer(&tmp, 0);
    אם (ret < 0)
        החזר ret;

    ret = av_frame_copy(&tmp, frame);
    אם (ret < 0) {
        av_frame_unref(&tmp);
        החזר ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    אם (ret < 0) {
        av_frame_unref(&tmp);
        החזר ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    אם (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    החזר 0;
}

صحيح av_frame_copy_props(AVFrame *dst, ثابت AVFrame *src)
{
    החזר frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(ثابت AVFrame *frame, صحيح plane)
{
    uintptr_t data;
    صحيح planes;

    אם (frame->nb_samples) {
        صحيح channels = frame->ch_layout.nb_channels;
        אם (!channels)
            החזר عدم;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } אחרת
        planes = 4;

    אם (plane < 0 || plane >= planes || !frame->extended_data[plane])
        החזר عدم;
    data = (uintptr_t)frame->extended_data[plane];

    עבור (صحيح i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        אם (data >= buf_begin && data < buf_begin + buf->size)
            החזר buf;
    }
    עבור (صحيح i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        אם (data >= buf_begin && data < buf_begin + buf->size)
            החזר buf;
    }
    החזר عدم;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 تعداد AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    החזר
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
    אם (!ret)
        av_buffer_unref(&buf);
    החזר ret;
}

AVFrameSideData *av_frame_get_side_data(ثابت AVFrame *frame,
                                        تعداد AVFrameSideDataType type)
{
    החזר (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

ساكن صحيح frame_copy_video(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح planes;

    אם (dst->width  < src->width ||
        dst->height < src->height)
        החזר AVERROR(EINVAL);

    אם (src->hw_frames_ctx || dst->hw_frames_ctx)
        החזר av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_count_planes(dst->format);
    עבור (صحيح i = 0; i < planes; i++)
        אם (!dst->data[i] || !src->data[i])
            החזר AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    החזר 0;
}

ساكن صحيح frame_copy_audio(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح planar   = av_sample_fmt_is_planar(dst->format);
    صحيح channels = dst->ch_layout.nb_channels;
    صحيح planes   = planar ? channels : 1;

    אם (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        החזר AVERROR(EINVAL);

    עבור (صحيح i = 0; i < planes; i++)
        אם (!dst->extended_data[i] || !src->extended_data[i])
            החזר AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    החזר 0;
}

صحيح av_frame_copy(AVFrame *dst, ثابت AVFrame *src)
{
    אם (dst->format != src->format || dst->format < 0)
        החזר AVERROR(EINVAL);

    אם (dst->width > 0 && dst->height > 0)
        החזר frame_copy_video(dst, src);
    אחרת אם (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        החזר frame_copy_audio(dst, src);

    החזר AVERROR(EINVAL);
}

فراغ av_frame_remove_side_data(AVFrame *frame, تعداد AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

ساكن صحيح calc_cropping_offsets(size_t offsets[4], ثابت AVFrame *frame,
                                 ثابت AVPixFmtDescriptor *desc)
{
    עבור (صحيح i = 0; frame->data[i]; i++) {
        ثابت AVComponentDescriptor *comp = عدم;
        صحيح shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        صحيح shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        אם (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            اكسر;
        }

        /* find any component descriptor for this plane */
        עבור (صحيح j = 0; j < desc->nb_components; j++) {
            אם (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                اكسر;
            }
        }
        אם (!comp)
            החזר AVERROR_BUG;

        offsets[i] = (frame->crop_top  >> shift_y) * frame->linesize[i] +
                     (frame->crop_left >> shift_x) * comp->step;
    }

    החזר 0;
}

صحيح av_frame_apply_cropping(AVFrame *frame, صحيح flags)
{
    ثابت AVPixFmtDescriptor *desc;
    size_t offsets[4];
    صحيح ret;

    אם (!(frame->width > 0 && frame->height > 0))
        החזר AVERROR(EINVAL);

    אם (frame->crop_left >= INT_MAX - frame->crop_right        ||
        frame->crop_top  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_left + frame->crop_right) >= frame->width ||
        (frame->crop_top + frame->crop_bottom) >= frame->height)
        החזר AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    אם (!desc)
        החזר AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    אם (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_right;
        frame->height     -= frame->crop_bottom;
        frame->crop_right  = 0;
        frame->crop_bottom = 0;
        החזר 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    אם (ret < 0)
        החזר ret;

    /* adjust the offsets to avoid breaking alignment */
    אם (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        صحيح log2_crop_align = frame->crop_left ? ff_ctz(frame->crop_left) : INT_MAX;
        صحيح min_log2_align = INT_MAX;

        עבור (صحيح i = 0; frame->data[i]; i++) {
            صحيح log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        אם (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_left &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            אם (ret < 0)
                החזר ret;
        }
    }

    עבור (صحيح i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_left + frame->crop_right);
    frame->height     -= (frame->crop_top  + frame->crop_bottom);
    frame->crop_left   = 0;
    frame->crop_right  = 0;
    frame->crop_top    = 0;
    frame->crop_bottom = 0;

    החזר 0;
}
