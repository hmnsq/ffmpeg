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

#अन्तर्भाव "channel_layout.h"
#अन्तर्भाव "avassert.h"
#अन्तर्भाव "buffer.h"
#अन्तर्भाव "dict.h"
#अन्तर्भाव "frame.h"
#अन्तर्भाव "frame_internal.h"
#अन्तर्भाव "imgutils.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "refstruct.h"
#अन्तर्भाव "samplefmt.h"
#अन्तर्भाव "side_data.h"
#अन्तर्भाव "hwcontext.h"

स्थिर शून्य get_frame_defaults(AVFrame *frame)
{
    स_रखो(frame, 0, आकार(*frame));

    frame->pts                   =
    frame->pkt_dts               = AV_NOPTS_मूल्य;
    frame->best_effort_timestamp = AV_NOPTS_मूल्य;
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

AVFrame *av_frame_alloc(शून्य)
{
    AVFrame *frame = av_malloc(आकार(*frame));

    जर (!frame)
        परत रिक्त;

    get_frame_defaults(frame);

    परत frame;
}

शून्य av_frame_free(AVFrame **frame)
{
    जर (!frame || !*frame)
        परत;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

पूर्णांक ff_frame_get_video_buffer(AVFrame *frame, पूर्णांक align,
                              AVBufferRef *(*alloc)(शून्य *opaque, माप_प्रकार size),
                              शून्य *opaque)
{
    स्थिरांक AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    पूर्णांक ret, padded_height;
    पूर्णांक plane_padding;
    सूचक_भेद_प्रकार linesizes[4];
    माप_प्रकार total_size, sizes[4];

    जर (!desc)
        परत AVERROR(EINVAL);

    जर ((ret = av_image_check_size(frame->width, frame->height, 0, रिक्त)) < 0)
        परत ret;

    जर (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    जर (!frame->linesize[0]) {
        साठी (पूर्णांक i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            जर (ret < 0)
                परत ret;
            जर (!(frame->linesize[0] & (align-1)))
                थांबा;
        }

        साठी (पूर्णांक i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    साठी (पूर्णांक i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    जर ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        परत ret;

    total_size = 4 * plane_padding + 4 * align;
    साठी (पूर्णांक i = 0; i < 4; i++) {
        जर (sizes[i] > SIZE_MAX - total_size)
            परत AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    जर (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        जा fail;
    }

    जर ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        जा fail;

    साठी (पूर्णांक i = 1; i < 4; i++) {
        जर (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    परत 0;
fail:
    av_frame_unref(frame);
    परत ret;
}

स्थिर पूर्णांक get_audio_buffer(AVFrame *frame, पूर्णांक align)
{
    पूर्णांक planar   = av_sample_fmt_is_planar(frame->format);
    पूर्णांक channels, planes;
    माप_प्रकार size;
    पूर्णांक ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    जर (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        जर (ret < 0)
            परत ret;
    }

    जर (align <= 0)
        align = ALIGN;

    जर (planes > AV_अंक_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          आकार(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_अंक_DATA_POINTERS,
                                          आकार(*frame->extended_buf));
        जर (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            परत AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_अंक_DATA_POINTERS;
    } अन्यथा
        frame->extended_data = frame->data;

    जर (frame->linesize[0] > SIZE_MAX - align)
        परत AVERROR(EINVAL);
    size = frame->linesize[0] + (माप_प्रकार)align;

    साठी (पूर्णांक i = 0; i < FFMIN(planes, AV_अंक_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        जर (!frame->buf[i]) {
            av_frame_unref(frame);
            परत AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    साठी (पूर्णांक i = 0; i < planes - AV_अंक_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        जर (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            परत AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_अंक_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    परत 0;

}

पूर्णांक av_frame_get_buffer(AVFrame *frame, पूर्णांक align)
{
    जर (frame->format < 0)
        परत AVERROR(EINVAL);

    जर (frame->width > 0 && frame->height > 0)
        परत ff_frame_get_video_buffer(frame, align, रिक्त, रिक्त);
    अन्यथा जर (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        परत get_audio_buffer(frame, align);

    परत AVERROR(EINVAL);
}

स्थिर पूर्णांक frame_copy_props(AVFrame *dst, स्थिरांक AVFrame *src, पूर्णांक force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ratio    = src->sample_aspect_ratio;
    dst->crop_शीर्ष               = src->crop_शीर्ष;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_डावा              = src->crop_डावा;
    dst->crop_उजवा             = src->crop_उजवा;
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

    साठी (पूर्णांक i = 0; i < src->nb_side_data; i++) {
        स्थिरांक AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        जर (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            सुरूठेवा;
        जर (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            जर (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                परत AVERROR(ENOMEM);
            }
            स_नकल(sd_dst->data, sd_src->data, sd_src->size);
        } अन्यथा {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            जर (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                परत AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    परत av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

पूर्णांक av_frame_ref(AVFrame *dst, स्थिरांक AVFrame *src)
{
    पूर्णांक ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    जर (ret < 0)
        जा fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    जर (ret < 0)
        जा fail;

    /* duplicate the frame data if it's not refcounted */
    जर (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        जर (ret < 0)
            जा fail;

        ret = av_frame_copy(dst, src);
        जर (ret < 0)
            जा fail;

        परत 0;
    }

    /* ref the buffers */
    साठी (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        जर (!src->buf[i])
            सुरूठेवा;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        जर (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            जा fail;
        }
    }

    जर (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      आकार(*dst->extended_buf));
        जर (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            जा fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        साठी (पूर्णांक i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            जर (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                जा fail;
            }
        }
    }

    जर (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        जर (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            जा fail;
        }
    }

    /* duplicate extended data */
    जर (src->extended_data != src->data) {
        पूर्णांक ch = dst->ch_layout.nb_channels;

        जर (ch <= 0 || ch > SIZE_MAX / आकार(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            जा fail;
        }

        dst->extended_data = av_memdup(src->extended_data, आकार(*dst->extended_data) * ch);
        जर (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            जा fail;
        }
    } अन्यथा
        dst->extended_data = dst->data;

    स_नकल(dst->data,     src->data,     आकार(src->data));
    स_नकल(dst->linesize, src->linesize, आकार(src->linesize));

    परत 0;

fail:
    av_frame_unref(dst);
    परत ret;
}

पूर्णांक av_frame_replace(AVFrame *dst, स्थिरांक AVFrame *src)
{
    पूर्णांक ret = 0;

    जर (dst == src)
        परत AVERROR(EINVAL);

    जर (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        जर (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            परत av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        जर (ret < 0)
            जा fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    जर (ret < 0)
        जा fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    जर (ret < 0)
        जा fail;

    /* replace the buffers */
    साठी (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        जर (ret < 0)
            जा fail;
    }

    जर (src->extended_buf) {
        जर (dst->nb_extended_buf != src->nb_extended_buf) {
            पूर्णांक nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            शून्य *tmp;

            साठी (पूर्णांक i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   आकार(*dst->extended_buf));
            जर (!tmp) {
                ret = AVERROR(ENOMEM);
                जा fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            स_रखो(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * आकार(*dst->extended_buf));
        }

        साठी (पूर्णांक i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            जर (ret < 0)
                जा fail;
        }
    } अन्यथा जर (dst->extended_buf) {
        साठी (पूर्णांक i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    जर (ret < 0)
        जा fail;

    जर (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    जर (src->extended_data != src->data) {
        पूर्णांक ch = dst->ch_layout.nb_channels;

        जर (ch <= 0 || ch > SIZE_MAX / आकार(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            जा fail;
        }

        dst->extended_data = av_memdup(src->extended_data, आकार(*dst->extended_data) * ch);
        जर (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            जा fail;
        }
    } अन्यथा
        dst->extended_data = dst->data;

    स_नकल(dst->data,     src->data,     आकार(src->data));
    स_नकल(dst->linesize, src->linesize, आकार(src->linesize));

    परत 0;

fail:
    av_frame_unref(dst);
    परत ret;
}

AVFrame *av_frame_clone(स्थिरांक AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    जर (!ret)
        परत रिक्त;

    जर (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    परत ret;
}

शून्य av_frame_unref(AVFrame *frame)
{
    जर (!frame)
        परत;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    साठी (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    साठी (पूर्णांक i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    जर (frame->extended_data != frame->data)
        av_freep(&frame->extended_data);

    av_channel_layout_uninit(&frame->ch_layout);

    get_frame_defaults(frame);
}

शून्य av_frame_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    *dst = *src;
    जर (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

पूर्णांक av_frame_is_writable(AVFrame *frame)
{
    पूर्णांक ret = 1;

    /* assume non-refcounted frames are not writable */
    जर (!frame->buf[0])
        परत 0;

    साठी (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        जर (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    साठी (पूर्णांक i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    परत ret;
}

पूर्णांक av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    पूर्णांक ret;

    जर (av_frame_is_writable(frame))
        परत 0;

    स_रखो(&tmp, 0, आकार(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    जर (ret < 0) {
        av_frame_unref(&tmp);
        परत ret;
    }

    जर (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    अन्यथा
        ret = av_frame_get_buffer(&tmp, 0);
    जर (ret < 0)
        परत ret;

    ret = av_frame_copy(&tmp, frame);
    जर (ret < 0) {
        av_frame_unref(&tmp);
        परत ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    जर (ret < 0) {
        av_frame_unref(&tmp);
        परत ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    जर (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    परत 0;
}

पूर्णांक av_frame_copy_props(AVFrame *dst, स्थिरांक AVFrame *src)
{
    परत frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(स्थिरांक AVFrame *frame, पूर्णांक plane)
{
    uintptr_t data;
    पूर्णांक planes;

    जर (frame->nb_samples) {
        पूर्णांक channels = frame->ch_layout.nb_channels;
        जर (!channels)
            परत रिक्त;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } अन्यथा
        planes = 4;

    जर (plane < 0 || plane >= planes || !frame->extended_data[plane])
        परत रिक्त;
    data = (uintptr_t)frame->extended_data[plane];

    साठी (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        जर (data >= buf_begin && data < buf_begin + buf->size)
            परत buf;
    }
    साठी (पूर्णांक i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        जर (data >= buf_begin && data < buf_begin + buf->size)
            परत buf;
    }
    परत रिक्त;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 गणना AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    परत
        ff_frame_side_data_add_from_buf(
            &frame->side_data, &frame->nb_side_data, type, buf);
}

AVFrameSideData *av_frame_new_side_data(AVFrame *frame,
                                        गणना AVFrameSideDataType type,
                                        माप_प्रकार size)
{
    AVFrameSideData *ret;
    AVBufferRef *buf = av_buffer_alloc(size);
    ret = av_frame_new_side_data_from_buf(frame, type, buf);
    जर (!ret)
        av_buffer_unref(&buf);
    परत ret;
}

AVFrameSideData *av_frame_get_side_data(स्थिरांक AVFrame *frame,
                                        गणना AVFrameSideDataType type)
{
    परत (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

स्थिर पूर्णांक frame_copy_video(AVFrame *dst, स्थिरांक AVFrame *src)
{
    पूर्णांक planes;

    जर (dst->width  < src->width ||
        dst->height < src->height)
        परत AVERROR(EINVAL);

    जर (src->hw_frames_ctx || dst->hw_frames_ctx)
        परत av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_मोजणी_planes(dst->format);
    साठी (पूर्णांक i = 0; i < planes; i++)
        जर (!dst->data[i] || !src->data[i])
            परत AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    परत 0;
}

स्थिर पूर्णांक frame_copy_audio(AVFrame *dst, स्थिरांक AVFrame *src)
{
    पूर्णांक planar   = av_sample_fmt_is_planar(dst->format);
    पूर्णांक channels = dst->ch_layout.nb_channels;
    पूर्णांक planes   = planar ? channels : 1;

    जर (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        परत AVERROR(EINVAL);

    साठी (पूर्णांक i = 0; i < planes; i++)
        जर (!dst->extended_data[i] || !src->extended_data[i])
            परत AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    परत 0;
}

पूर्णांक av_frame_copy(AVFrame *dst, स्थिरांक AVFrame *src)
{
    जर (dst->format != src->format || dst->format < 0)
        परत AVERROR(EINVAL);

    जर (dst->width > 0 && dst->height > 0)
        परत frame_copy_video(dst, src);
    अन्यथा जर (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        परत frame_copy_audio(dst, src);

    परत AVERROR(EINVAL);
}

शून्य av_frame_remove_side_data(AVFrame *frame, गणना AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

स्थिर पूर्णांक calc_cropping_offsets(माप_प्रकार offsets[4], स्थिरांक AVFrame *frame,
                                 स्थिरांक AVPixFmtDescriptor *desc)
{
    साठी (पूर्णांक i = 0; frame->data[i]; i++) {
        स्थिरांक AVComponentDescriptor *comp = रिक्त;
        पूर्णांक shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        पूर्णांक shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        जर (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            थांबा;
        }

        /* find any component descriptor for this plane */
        साठी (पूर्णांक j = 0; j < desc->nb_components; j++) {
            जर (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                थांबा;
            }
        }
        जर (!comp)
            परत AVERROR_BUG;

        offsets[i] = (frame->crop_शीर्ष  >> shift_y) * frame->linesize[i] +
                     (frame->crop_डावा >> shift_x) * comp->step;
    }

    परत 0;
}

पूर्णांक av_frame_apply_cropping(AVFrame *frame, पूर्णांक flags)
{
    स्थिरांक AVPixFmtDescriptor *desc;
    माप_प्रकार offsets[4];
    पूर्णांक ret;

    जर (!(frame->width > 0 && frame->height > 0))
        परत AVERROR(EINVAL);

    जर (frame->crop_डावा >= पूर्णांक_उच्च - frame->crop_उजवा        ||
        frame->crop_शीर्ष  >= पूर्णांक_उच्च - frame->crop_bottom       ||
        (frame->crop_डावा + frame->crop_उजवा) >= frame->width ||
        (frame->crop_शीर्ष + frame->crop_bottom) >= frame->height)
        परत AVERROR(दुस्फल);

    desc = av_pix_fmt_desc_get(frame->format);
    जर (!desc)
        परत AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    जर (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_उजवा;
        frame->height     -= frame->crop_bottom;
        frame->crop_उजवा  = 0;
        frame->crop_bottom = 0;
        परत 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    जर (ret < 0)
        परत ret;

    /* adjust the offsets to avoid breaking alignment */
    जर (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        पूर्णांक log2_crop_align = frame->crop_डावा ? ff_ctz(frame->crop_डावा) : पूर्णांक_उच्च;
        पूर्णांक min_log2_align = पूर्णांक_उच्च;

        साठी (पूर्णांक i = 0; frame->data[i]; i++) {
            पूर्णांक log2_align = offsets[i] ? ff_ctz(offsets[i]) : पूर्णांक_उच्च;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        जर (min_log2_align < 5 && log2_crop_align != पूर्णांक_उच्च) {
            frame->crop_डावा &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            जर (ret < 0)
                परत ret;
        }
    }

    साठी (पूर्णांक i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_डावा + frame->crop_उजवा);
    frame->height     -= (frame->crop_शीर्ष  + frame->crop_bottom);
    frame->crop_डावा   = 0;
    frame->crop_उजवा  = 0;
    frame->crop_शीर्ष    = 0;
    frame->crop_bottom = 0;

    परत 0;
}
