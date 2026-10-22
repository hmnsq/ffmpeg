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

#شامل "channel_layout.h"
#شامل "avassert.h"
#شامل "buffer.h"
#شامل "dict.h"
#شامل "frame.h"
#شامل "frame_internal.h"
#شامل "imgutils.h"
#شامل "mem.h"
#شامل "refstruct.h"
#شامل "samplefmt.h"
#شامل "side_data.h"
#شامل "hwcontext.h"

ایستا تهی get_frame_defaults(AVFrame *frame)
{
    memset(frame, 0, اندازه(*frame));

    frame->pts                   =
    frame->pkt_dts               = AV_NOPTS_مقدار;
    frame->best_effort_timestamp = AV_NOPTS_مقدار;
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

AVFrame *av_frame_alloc(تهی)
{
    AVFrame *frame = av_malloc(اندازه(*frame));

    اگر (!frame)
        بازگشت پوچ;

    get_frame_defaults(frame);

    بازگشت frame;
}

تهی av_frame_free(AVFrame **frame)
{
    اگر (!frame || !*frame)
        بازگشت;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

صحیح ff_frame_get_video_buffer(AVFrame *frame, صحیح align,
                              AVBufferRef *(*alloc)(تهی *opaque, size_t size),
                              تهی *opaque)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    صحیح ret, padded_height;
    صحیح plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    اگر (!desc)
        بازگشت AVERROR(EINVAL);

    اگر ((ret = av_image_check_size(frame->width, frame->height, 0, پوچ)) < 0)
        بازگشت ret;

    اگر (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    اگر (!frame->linesize[0]) {
        برای (صحیح i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            اگر (ret < 0)
                بازگشت ret;
            اگر (!(frame->linesize[0] & (align-1)))
                بشکن;
        }

        برای (صحیح i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    برای (صحیح i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    اگر ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        بازگشت ret;

    total_size = 4 * plane_padding + 4 * align;
    برای (صحیح i = 0; i < 4; i++) {
        اگر (sizes[i] > SIZE_MAX - total_size)
            بازگشت AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    اگر (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        برو fail;
    }

    اگر ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        برو fail;

    برای (صحیح i = 1; i < 4; i++) {
        اگر (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    بازگشت 0;
fail:
    av_frame_unref(frame);
    بازگشت ret;
}

ایستا صحیح get_audio_buffer(AVFrame *frame, صحیح align)
{
    صحیح planar   = av_sample_fmt_is_planar(frame->format);
    صحیح channels, planes;
    size_t size;
    صحیح ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    اگر (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        اگر (ret < 0)
            بازگشت ret;
    }

    اگر (align <= 0)
        align = ALIGN;

    اگر (planes > AV_رقم_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          اندازه(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_رقم_DATA_POINTERS,
                                          اندازه(*frame->extended_buf));
        اگر (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            بازگشت AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_رقم_DATA_POINTERS;
    } وگرنه
        frame->extended_data = frame->data;

    اگر (frame->linesize[0] > SIZE_MAX - align)
        بازگشت AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    برای (صحیح i = 0; i < FFMIN(planes, AV_رقم_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        اگر (!frame->buf[i]) {
            av_frame_unref(frame);
            بازگشت AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    برای (صحیح i = 0; i < planes - AV_رقم_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        اگر (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            بازگشت AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_رقم_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    بازگشت 0;

}

صحیح av_frame_get_buffer(AVFrame *frame, صحیح align)
{
    اگر (frame->format < 0)
        بازگشت AVERROR(EINVAL);

    اگر (frame->width > 0 && frame->height > 0)
        بازگشت ff_frame_get_video_buffer(frame, align, پوچ, پوچ);
    وگرنه اگر (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        بازگشت get_audio_buffer(frame, align);

    بازگشت AVERROR(EINVAL);
}

ایستا صحیح frame_copy_props(AVFrame *dst, ثابت AVFrame *src, صحیح force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ratio    = src->sample_aspect_ratio;
    dst->crop_بالاترین               = src->crop_بالاترین;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_چپ              = src->crop_چپ;
    dst->crop_راست             = src->crop_راست;
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

    برای (صحیح i = 0; i < src->nb_side_data; i++) {
        ثابت AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        اگر (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            ادامه;
        اگر (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            اگر (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                بازگشت AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } وگرنه {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            اگر (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                بازگشت AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    بازگشت av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

صحیح av_frame_ref(AVFrame *dst, ثابت AVFrame *src)
{
    صحیح ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    اگر (ret < 0)
        برو fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    اگر (ret < 0)
        برو fail;

    /* duplicate the frame data if it's not refcounted */
    اگر (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        اگر (ret < 0)
            برو fail;

        ret = av_frame_copy(dst, src);
        اگر (ret < 0)
            برو fail;

        بازگشت 0;
    }

    /* ref the buffers */
    برای (صحیح i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        اگر (!src->buf[i])
            ادامه;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        اگر (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            برو fail;
        }
    }

    اگر (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      اندازه(*dst->extended_buf));
        اگر (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            برو fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        برای (صحیح i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            اگر (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                برو fail;
            }
        }
    }

    اگر (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        اگر (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            برو fail;
        }
    }

    /* duplicate extended data */
    اگر (src->extended_data != src->data) {
        صحیح ch = dst->ch_layout.nb_channels;

        اگر (ch <= 0 || ch > SIZE_MAX / اندازه(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            برو fail;
        }

        dst->extended_data = av_memdup(src->extended_data, اندازه(*dst->extended_data) * ch);
        اگر (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            برو fail;
        }
    } وگرنه
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     اندازه(src->data));
    memcpy(dst->linesize, src->linesize, اندازه(src->linesize));

    بازگشت 0;

fail:
    av_frame_unref(dst);
    بازگشت ret;
}

صحیح av_frame_replace(AVFrame *dst, ثابت AVFrame *src)
{
    صحیح ret = 0;

    اگر (dst == src)
        بازگشت AVERROR(EINVAL);

    اگر (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        اگر (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            بازگشت av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        اگر (ret < 0)
            برو fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    اگر (ret < 0)
        برو fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    اگر (ret < 0)
        برو fail;

    /* replace the buffers */
    برای (صحیح i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        اگر (ret < 0)
            برو fail;
    }

    اگر (src->extended_buf) {
        اگر (dst->nb_extended_buf != src->nb_extended_buf) {
            صحیح nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            تهی *tmp;

            برای (صحیح i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   اندازه(*dst->extended_buf));
            اگر (!tmp) {
                ret = AVERROR(ENOMEM);
                برو fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * اندازه(*dst->extended_buf));
        }

        برای (صحیح i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            اگر (ret < 0)
                برو fail;
        }
    } وگرنه اگر (dst->extended_buf) {
        برای (صحیح i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    اگر (ret < 0)
        برو fail;

    اگر (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    اگر (src->extended_data != src->data) {
        صحیح ch = dst->ch_layout.nb_channels;

        اگر (ch <= 0 || ch > SIZE_MAX / اندازه(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            برو fail;
        }

        dst->extended_data = av_memdup(src->extended_data, اندازه(*dst->extended_data) * ch);
        اگر (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            برو fail;
        }
    } وگرنه
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     اندازه(src->data));
    memcpy(dst->linesize, src->linesize, اندازه(src->linesize));

    بازگشت 0;

fail:
    av_frame_unref(dst);
    بازگشت ret;
}

AVFrame *av_frame_clone(ثابت AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    اگر (!ret)
        بازگشت پوچ;

    اگر (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    بازگشت ret;
}

تهی av_frame_unref(AVFrame *frame)
{
    اگر (!frame)
        بازگشت;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    برای (صحیح i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    برای (صحیح i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    اگر (frame->extended_data != frame->data)
        av_freep(&frame->extended_data);

    av_channel_layout_uninit(&frame->ch_layout);

    get_frame_defaults(frame);
}

تهی av_frame_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    *dst = *src;
    اگر (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

صحیح av_frame_is_writable(AVFrame *frame)
{
    صحیح ret = 1;

    /* assume non-refcounted frames are not writable */
    اگر (!frame->buf[0])
        بازگشت 0;

    برای (صحیح i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        اگر (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    برای (صحیح i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    بازگشت ret;
}

صحیح av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    صحیح ret;

    اگر (av_frame_is_writable(frame))
        بازگشت 0;

    memset(&tmp, 0, اندازه(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    اگر (ret < 0) {
        av_frame_unref(&tmp);
        بازگشت ret;
    }

    اگر (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    وگرنه
        ret = av_frame_get_buffer(&tmp, 0);
    اگر (ret < 0)
        بازگشت ret;

    ret = av_frame_copy(&tmp, frame);
    اگر (ret < 0) {
        av_frame_unref(&tmp);
        بازگشت ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    اگر (ret < 0) {
        av_frame_unref(&tmp);
        بازگشت ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    اگر (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    بازگشت 0;
}

صحیح av_frame_copy_props(AVFrame *dst, ثابت AVFrame *src)
{
    بازگشت frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(ثابت AVFrame *frame, صحیح plane)
{
    uintptr_t data;
    صحیح planes;

    اگر (frame->nb_samples) {
        صحیح channels = frame->ch_layout.nb_channels;
        اگر (!channels)
            بازگشت پوچ;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } وگرنه
        planes = 4;

    اگر (plane < 0 || plane >= planes || !frame->extended_data[plane])
        بازگشت پوچ;
    data = (uintptr_t)frame->extended_data[plane];

    برای (صحیح i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        اگر (data >= buf_begin && data < buf_begin + buf->size)
            بازگشت buf;
    }
    برای (صحیح i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        اگر (data >= buf_begin && data < buf_begin + buf->size)
            بازگشت buf;
    }
    بازگشت پوچ;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 شمارش AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    بازگشت
        ff_frame_side_data_add_from_buf(
            &frame->side_data, &frame->nb_side_data, type, buf);
}

AVFrameSideData *av_frame_new_side_data(AVFrame *frame,
                                        شمارش AVFrameSideDataType type,
                                        size_t size)
{
    AVFrameSideData *ret;
    AVBufferRef *buf = av_buffer_alloc(size);
    ret = av_frame_new_side_data_from_buf(frame, type, buf);
    اگر (!ret)
        av_buffer_unref(&buf);
    بازگشت ret;
}

AVFrameSideData *av_frame_get_side_data(ثابت AVFrame *frame,
                                        شمارش AVFrameSideDataType type)
{
    بازگشت (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

ایستا صحیح frame_copy_video(AVFrame *dst, ثابت AVFrame *src)
{
    صحیح planes;

    اگر (dst->width  < src->width ||
        dst->height < src->height)
        بازگشت AVERROR(EINVAL);

    اگر (src->hw_frames_ctx || dst->hw_frames_ctx)
        بازگشت av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_شمار_planes(dst->format);
    برای (صحیح i = 0; i < planes; i++)
        اگر (!dst->data[i] || !src->data[i])
            بازگشت AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    بازگشت 0;
}

ایستا صحیح frame_copy_audio(AVFrame *dst, ثابت AVFrame *src)
{
    صحیح planar   = av_sample_fmt_is_planar(dst->format);
    صحیح channels = dst->ch_layout.nb_channels;
    صحیح planes   = planar ? channels : 1;

    اگر (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        بازگشت AVERROR(EINVAL);

    برای (صحیح i = 0; i < planes; i++)
        اگر (!dst->extended_data[i] || !src->extended_data[i])
            بازگشت AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    بازگشت 0;
}

صحیح av_frame_copy(AVFrame *dst, ثابت AVFrame *src)
{
    اگر (dst->format != src->format || dst->format < 0)
        بازگشت AVERROR(EINVAL);

    اگر (dst->width > 0 && dst->height > 0)
        بازگشت frame_copy_video(dst, src);
    وگرنه اگر (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        بازگشت frame_copy_audio(dst, src);

    بازگشت AVERROR(EINVAL);
}

تهی av_frame_remove_side_data(AVFrame *frame, شمارش AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

ایستا صحیح calc_cropping_offsets(size_t offsets[4], ثابت AVFrame *frame,
                                 ثابت AVPixFmtDescriptor *desc)
{
    برای (صحیح i = 0; frame->data[i]; i++) {
        ثابت AVComponentDescriptor *comp = پوچ;
        صحیح shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        صحیح shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        اگر (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            بشکن;
        }

        /* find any component descriptor for this plane */
        برای (صحیح j = 0; j < desc->nb_components; j++) {
            اگر (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                بشکن;
            }
        }
        اگر (!comp)
            بازگشت AVERROR_BUG;

        offsets[i] = (frame->crop_بالاترین  >> shift_y) * frame->linesize[i] +
                     (frame->crop_چپ >> shift_x) * comp->step;
    }

    بازگشت 0;
}

صحیح av_frame_apply_cropping(AVFrame *frame, صحیح flags)
{
    ثابت AVPixFmtDescriptor *desc;
    size_t offsets[4];
    صحیح ret;

    اگر (!(frame->width > 0 && frame->height > 0))
        بازگشت AVERROR(EINVAL);

    اگر (frame->crop_چپ >= INT_MAX - frame->crop_راست        ||
        frame->crop_بالاترین  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_چپ + frame->crop_راست) >= frame->width ||
        (frame->crop_بالاترین + frame->crop_bottom) >= frame->height)
        بازگشت AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    اگر (!desc)
        بازگشت AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    اگر (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_راست;
        frame->height     -= frame->crop_bottom;
        frame->crop_راست  = 0;
        frame->crop_bottom = 0;
        بازگشت 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    اگر (ret < 0)
        بازگشت ret;

    /* adjust the offsets to avoid breaking alignment */
    اگر (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        صحیح log2_crop_align = frame->crop_چپ ? ff_ctz(frame->crop_چپ) : INT_MAX;
        صحیح min_log2_align = INT_MAX;

        برای (صحیح i = 0; frame->data[i]; i++) {
            صحیح log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        اگر (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_چپ &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            اگر (ret < 0)
                بازگشت ret;
        }
    }

    برای (صحیح i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_چپ + frame->crop_راست);
    frame->height     -= (frame->crop_بالاترین  + frame->crop_bottom);
    frame->crop_چپ   = 0;
    frame->crop_راست  = 0;
    frame->crop_بالاترین    = 0;
    frame->crop_bottom = 0;

    بازگشت 0;
}
