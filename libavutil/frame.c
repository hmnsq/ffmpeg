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
    स_रखो(frame, 0, परिमाण(*frame));

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
    AVFrame *frame = av_malloc(परिमाण(*frame));

    यदि (!frame)
        प्रत्यागम रिक्त;

    get_frame_defaults(frame);

    प्रत्यागम frame;
}

शून्य av_frame_free(AVFrame **frame)
{
    यदि (!frame || !*frame)
        प्रत्यागम;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

पूर्णाङ्क ff_frame_get_video_buffer(AVFrame *frame, पूर्णाङ्क align,
                              AVBufferRef *(*alloc)(शून्य *opaque, माप_प्रकार size),
                              शून्य *opaque)
{
    ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    पूर्णाङ्क ret, padded_height;
    पूर्णाङ्क plane_padding;
    सूचक_भेद_प्रकार linesizes[4];
    माप_प्रकार total_size, sizes[4];

    यदि (!desc)
        प्रत्यागम AVERROR(EINVAL);

    यदि ((ret = av_image_check_size(frame->width, frame->height, 0, रिक्त)) < 0)
        प्रत्यागम ret;

    यदि (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    यदि (!frame->linesize[0]) {
        प्रति (पूर्णाङ्क i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            यदि (ret < 0)
                प्रत्यागम ret;
            यदि (!(frame->linesize[0] & (align-1)))
                भङ्ग;
        }

        प्रति (पूर्णाङ्क i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    प्रति (पूर्णाङ्क i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    यदि ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        प्रत्यागम ret;

    total_size = 4 * plane_padding + 4 * align;
    प्रति (पूर्णाङ्क i = 0; i < 4; i++) {
        यदि (sizes[i] > SIZE_MAX - total_size)
            प्रत्यागम AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    यदि (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    यदि ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        गच्छ fail;

    प्रति (पूर्णाङ्क i = 1; i < 4; i++) {
        यदि (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    प्रत्यागम 0;
fail:
    av_frame_unref(frame);
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क get_audio_buffer(AVFrame *frame, पूर्णाङ्क align)
{
    पूर्णाङ्क planar   = av_sample_fmt_is_planar(frame->format);
    पूर्णाङ्क channels, planes;
    माप_प्रकार size;
    पूर्णाङ्क ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    यदि (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        यदि (ret < 0)
            प्रत्यागम ret;
    }

    यदि (align <= 0)
        align = ALIGN;

    यदि (planes > AV_अंक_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          परिमाण(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_अंक_DATA_POINTERS,
                                          परिमाण(*frame->extended_buf));
        यदि (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            प्रत्यागम AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_अंक_DATA_POINTERS;
    } अन्यथा
        frame->extended_data = frame->data;

    यदि (frame->linesize[0] > SIZE_MAX - align)
        प्रत्यागम AVERROR(EINVAL);
    size = frame->linesize[0] + (माप_प्रकार)align;

    प्रति (पूर्णाङ्क i = 0; i < FFMIN(planes, AV_अंक_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        यदि (!frame->buf[i]) {
            av_frame_unref(frame);
            प्रत्यागम AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    प्रति (पूर्णाङ्क i = 0; i < planes - AV_अंक_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        यदि (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            प्रत्यागम AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_अंक_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    प्रत्यागम 0;

}

पूर्णाङ्क av_frame_get_buffer(AVFrame *frame, पूर्णाङ्क align)
{
    यदि (frame->format < 0)
        प्रत्यागम AVERROR(EINVAL);

    यदि (frame->width > 0 && frame->height > 0)
        प्रत्यागम ff_frame_get_video_buffer(frame, align, रिक्त, रिक्त);
    अन्यथा यदि (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        प्रत्यागम get_audio_buffer(frame, align);

    प्रत्यागम AVERROR(EINVAL);
}

स्थिर पूर्णाङ्क frame_copy_props(AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ratio    = src->sample_aspect_ratio;
    dst->crop_शीर्ष               = src->crop_शीर्ष;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_बायाँ              = src->crop_बायाँ;
    dst->crop_दायाँ             = src->crop_दायाँ;
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

    प्रति (पूर्णाङ्क i = 0; i < src->nb_side_data; i++) {
        ध्रुव AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        यदि (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            अनुवर्त;
        यदि (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            यदि (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                प्रत्यागम AVERROR(ENOMEM);
            }
            स_नकल(sd_dst->data, sd_src->data, sd_src->size);
        } अन्यथा {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            यदि (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                प्रत्यागम AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    प्रत्यागम av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

पूर्णाङ्क av_frame_ref(AVFrame *dst, ध्रुव AVFrame *src)
{
    पूर्णाङ्क ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    यदि (ret < 0)
        गच्छ fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    यदि (ret < 0)
        गच्छ fail;

    /* duplicate the frame data if it's not refcounted */
    यदि (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        यदि (ret < 0)
            गच्छ fail;

        ret = av_frame_copy(dst, src);
        यदि (ret < 0)
            गच्छ fail;

        प्रत्यागम 0;
    }

    /* ref the buffers */
    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        यदि (!src->buf[i])
            अनुवर्त;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        यदि (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }
    }

    यदि (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      परिमाण(*dst->extended_buf));
        यदि (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        प्रति (पूर्णाङ्क i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            यदि (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                गच्छ fail;
            }
        }
    }

    यदि (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        यदि (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }
    }

    /* duplicate extended data */
    यदि (src->extended_data != src->data) {
        पूर्णाङ्क ch = dst->ch_layout.nb_channels;

        यदि (ch <= 0 || ch > SIZE_MAX / परिमाण(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            गच्छ fail;
        }

        dst->extended_data = av_memdup(src->extended_data, परिमाण(*dst->extended_data) * ch);
        यदि (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }
    } अन्यथा
        dst->extended_data = dst->data;

    स_नकल(dst->data,     src->data,     परिमाण(src->data));
    स_नकल(dst->linesize, src->linesize, परिमाण(src->linesize));

    प्रत्यागम 0;

fail:
    av_frame_unref(dst);
    प्रत्यागम ret;
}

पूर्णाङ्क av_frame_replace(AVFrame *dst, ध्रुव AVFrame *src)
{
    पूर्णाङ्क ret = 0;

    यदि (dst == src)
        प्रत्यागम AVERROR(EINVAL);

    यदि (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        यदि (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            प्रत्यागम av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        यदि (ret < 0)
            गच्छ fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    यदि (ret < 0)
        गच्छ fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    यदि (ret < 0)
        गच्छ fail;

    /* replace the buffers */
    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        यदि (ret < 0)
            गच्छ fail;
    }

    यदि (src->extended_buf) {
        यदि (dst->nb_extended_buf != src->nb_extended_buf) {
            पूर्णाङ्क nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            शून्य *tmp;

            प्रति (पूर्णाङ्क i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   परिमाण(*dst->extended_buf));
            यदि (!tmp) {
                ret = AVERROR(ENOMEM);
                गच्छ fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            स_रखो(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * परिमाण(*dst->extended_buf));
        }

        प्रति (पूर्णाङ्क i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            यदि (ret < 0)
                गच्छ fail;
        }
    } अन्यथा यदि (dst->extended_buf) {
        प्रति (पूर्णाङ्क i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    यदि (ret < 0)
        गच्छ fail;

    यदि (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    यदि (src->extended_data != src->data) {
        पूर्णाङ्क ch = dst->ch_layout.nb_channels;

        यदि (ch <= 0 || ch > SIZE_MAX / परिमाण(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            गच्छ fail;
        }

        dst->extended_data = av_memdup(src->extended_data, परिमाण(*dst->extended_data) * ch);
        यदि (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }
    } अन्यथा
        dst->extended_data = dst->data;

    स_नकल(dst->data,     src->data,     परिमाण(src->data));
    स_नकल(dst->linesize, src->linesize, परिमाण(src->linesize));

    प्रत्यागम 0;

fail:
    av_frame_unref(dst);
    प्रत्यागम ret;
}

AVFrame *av_frame_clone(ध्रुव AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    यदि (!ret)
        प्रत्यागम रिक्त;

    यदि (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    प्रत्यागम ret;
}

शून्य av_frame_unref(AVFrame *frame)
{
    यदि (!frame)
        प्रत्यागम;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    प्रति (पूर्णाङ्क i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    यदि (frame->extended_data != frame->data)
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
    यदि (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

पूर्णाङ्क av_frame_is_writable(AVFrame *frame)
{
    पूर्णाङ्क ret = 1;

    /* assume non-refcounted frames are not writable */
    यदि (!frame->buf[0])
        प्रत्यागम 0;

    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        यदि (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    प्रति (पूर्णाङ्क i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    प्रत्यागम ret;
}

पूर्णाङ्क av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    पूर्णाङ्क ret;

    यदि (av_frame_is_writable(frame))
        प्रत्यागम 0;

    स_रखो(&tmp, 0, परिमाण(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    यदि (ret < 0) {
        av_frame_unref(&tmp);
        प्रत्यागम ret;
    }

    यदि (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    अन्यथा
        ret = av_frame_get_buffer(&tmp, 0);
    यदि (ret < 0)
        प्रत्यागम ret;

    ret = av_frame_copy(&tmp, frame);
    यदि (ret < 0) {
        av_frame_unref(&tmp);
        प्रत्यागम ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    यदि (ret < 0) {
        av_frame_unref(&tmp);
        प्रत्यागम ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    यदि (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    प्रत्यागम 0;
}

पूर्णाङ्क av_frame_copy_props(AVFrame *dst, ध्रुव AVFrame *src)
{
    प्रत्यागम frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(ध्रुव AVFrame *frame, पूर्णाङ्क plane)
{
    uintptr_t data;
    पूर्णाङ्क planes;

    यदि (frame->nb_samples) {
        पूर्णाङ्क channels = frame->ch_layout.nb_channels;
        यदि (!channels)
            प्रत्यागम रिक्त;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } अन्यथा
        planes = 4;

    यदि (plane < 0 || plane >= planes || !frame->extended_data[plane])
        प्रत्यागम रिक्त;
    data = (uintptr_t)frame->extended_data[plane];

    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        यदि (data >= buf_begin && data < buf_begin + buf->size)
            प्रत्यागम buf;
    }
    प्रति (पूर्णाङ्क i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        यदि (data >= buf_begin && data < buf_begin + buf->size)
            प्रत्यागम buf;
    }
    प्रत्यागम रिक्त;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 गणना AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    प्रत्यागम
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
    यदि (!ret)
        av_buffer_unref(&buf);
    प्रत्यागम ret;
}

AVFrameSideData *av_frame_get_side_data(ध्रुव AVFrame *frame,
                                        गणना AVFrameSideDataType type)
{
    प्रत्यागम (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

स्थिर पूर्णाङ्क frame_copy_video(AVFrame *dst, ध्रुव AVFrame *src)
{
    पूर्णाङ्क planes;

    यदि (dst->width  < src->width ||
        dst->height < src->height)
        प्रत्यागम AVERROR(EINVAL);

    यदि (src->hw_frames_ctx || dst->hw_frames_ctx)
        प्रत्यागम av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_गिनती_planes(dst->format);
    प्रति (पूर्णाङ्क i = 0; i < planes; i++)
        यदि (!dst->data[i] || !src->data[i])
            प्रत्यागम AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क frame_copy_audio(AVFrame *dst, ध्रुव AVFrame *src)
{
    पूर्णाङ्क planar   = av_sample_fmt_is_planar(dst->format);
    पूर्णाङ्क channels = dst->ch_layout.nb_channels;
    पूर्णाङ्क planes   = planar ? channels : 1;

    यदि (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        प्रत्यागम AVERROR(EINVAL);

    प्रति (पूर्णाङ्क i = 0; i < planes; i++)
        यदि (!dst->extended_data[i] || !src->extended_data[i])
            प्रत्यागम AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    प्रत्यागम 0;
}

पूर्णाङ्क av_frame_copy(AVFrame *dst, ध्रुव AVFrame *src)
{
    यदि (dst->format != src->format || dst->format < 0)
        प्रत्यागम AVERROR(EINVAL);

    यदि (dst->width > 0 && dst->height > 0)
        प्रत्यागम frame_copy_video(dst, src);
    अन्यथा यदि (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        प्रत्यागम frame_copy_audio(dst, src);

    प्रत्यागम AVERROR(EINVAL);
}

शून्य av_frame_remove_side_data(AVFrame *frame, गणना AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

स्थिर पूर्णाङ्क calc_cropping_offsets(माप_प्रकार offsets[4], ध्रुव AVFrame *frame,
                                 ध्रुव AVPixFmtDescriptor *desc)
{
    प्रति (पूर्णाङ्क i = 0; frame->data[i]; i++) {
        ध्रुव AVComponentDescriptor *comp = रिक्त;
        पूर्णाङ्क shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        पूर्णाङ्क shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        यदि (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            भङ्ग;
        }

        /* find any component descriptor for this plane */
        प्रति (पूर्णाङ्क j = 0; j < desc->nb_components; j++) {
            यदि (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                भङ्ग;
            }
        }
        यदि (!comp)
            प्रत्यागम AVERROR_BUG;

        offsets[i] = (frame->crop_शीर्ष  >> shift_y) * frame->linesize[i] +
                     (frame->crop_बायाँ >> shift_x) * comp->step;
    }

    प्रत्यागम 0;
}

पूर्णाङ्क av_frame_apply_cropping(AVFrame *frame, पूर्णाङ्क flags)
{
    ध्रुव AVPixFmtDescriptor *desc;
    माप_प्रकार offsets[4];
    पूर्णाङ्क ret;

    यदि (!(frame->width > 0 && frame->height > 0))
        प्रत्यागम AVERROR(EINVAL);

    यदि (frame->crop_बायाँ >= पूर्णांक_उच्च - frame->crop_दायाँ        ||
        frame->crop_शीर्ष  >= पूर्णांक_उच्च - frame->crop_bottom       ||
        (frame->crop_बायाँ + frame->crop_दायाँ) >= frame->width ||
        (frame->crop_शीर्ष + frame->crop_bottom) >= frame->height)
        प्रत्यागम AVERROR(दुस्फल);

    desc = av_pix_fmt_desc_get(frame->format);
    यदि (!desc)
        प्रत्यागम AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    यदि (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_दायाँ;
        frame->height     -= frame->crop_bottom;
        frame->crop_दायाँ  = 0;
        frame->crop_bottom = 0;
        प्रत्यागम 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    यदि (ret < 0)
        प्रत्यागम ret;

    /* adjust the offsets to avoid breaking alignment */
    यदि (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        पूर्णाङ्क log2_crop_align = frame->crop_बायाँ ? ff_ctz(frame->crop_बायाँ) : पूर्णांक_उच्च;
        पूर्णाङ्क min_log2_align = पूर्णांक_उच्च;

        प्रति (पूर्णाङ्क i = 0; frame->data[i]; i++) {
            पूर्णाङ्क log2_align = offsets[i] ? ff_ctz(offsets[i]) : पूर्णांक_उच्च;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        यदि (min_log2_align < 5 && log2_crop_align != पूर्णांक_उच्च) {
            frame->crop_बायाँ &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            यदि (ret < 0)
                प्रत्यागम ret;
        }
    }

    प्रति (पूर्णाङ्क i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_बायाँ + frame->crop_दायाँ);
    frame->height     -= (frame->crop_शीर्ष  + frame->crop_bottom);
    frame->crop_बायाँ   = 0;
    frame->crop_दायाँ  = 0;
    frame->crop_शीर्ष    = 0;
    frame->crop_bottom = 0;

    प्रत्यागम 0;
}
