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
    memset(frame, 0, परिमाण(*frame));

    frame->pts                   =
    frame->pkt_dts               = AV_NOPTS_मानम्;
    frame->best_effort_timestamp = AV_NOPTS_मानम्;
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

    सचे (!frame)
        पटिनिवत्त रिक्त;

    get_frame_defaults(frame);

    पटिनिवत्त frame;
}

शून्य av_frame_free(AVFrame **frame)
{
    सचे (!frame || !*frame)
        पटिनिवत्त;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

पूर्णाङ्क ff_frame_get_video_buffer(AVFrame *frame, पूर्णाङ्क align,
                              AVBufferRef *(*alloc)(शून्य *opaque, size_t size),
                              शून्य *opaque)
{
    ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    पूर्णाङ्क ret, padded_height;
    पूर्णाङ्क plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    सचे (!desc)
        पटिनिवत्त AVERROR(EINVAL);

    सचे ((ret = av_image_check_size(frame->width, frame->height, 0, रिक्त)) < 0)
        पटिनिवत्त ret;

    सचे (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    सचे (!frame->linesize[0]) {
        अत्थाय (पूर्णाङ्क i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            सचे (ret < 0)
                पटिनिवत्त ret;
            सचे (!(frame->linesize[0] & (align-1)))
                भङ्ग;
        }

        अत्थाय (पूर्णाङ्क i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    अत्थाय (पूर्णाङ्क i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    सचे ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        पटिनिवत्त ret;

    total_size = 4 * plane_padding + 4 * align;
    अत्थाय (पूर्णाङ्क i = 0; i < 4; i++) {
        सचे (sizes[i] > SIZE_MAX - total_size)
            पटिनिवत्त AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    सचे (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    सचे ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        गच्छ fail;

    अत्थाय (पूर्णाङ्क i = 1; i < 4; i++) {
        सचे (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    पटिनिवत्त 0;
fail:
    av_frame_unref(frame);
    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क get_audio_buffer(AVFrame *frame, पूर्णाङ्क align)
{
    पूर्णाङ्क planar   = av_sample_fmt_is_planar(frame->format);
    पूर्णाङ्क channels, planes;
    size_t size;
    पूर्णाङ्क ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    सचे (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        सचे (ret < 0)
            पटिनिवत्त ret;
    }

    सचे (align <= 0)
        align = ALIGN;

    सचे (planes > AV_अङ्कः_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          परिमाण(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_अङ्कः_DATA_POINTERS,
                                          परिमाण(*frame->extended_buf));
        सचे (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            पटिनिवत्त AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_अङ्कः_DATA_POINTERS;
    } अञ्ञथा
        frame->extended_data = frame->data;

    सचे (frame->linesize[0] > SIZE_MAX - align)
        पटिनिवत्त AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    अत्थाय (पूर्णाङ्क i = 0; i < FFMIN(planes, AV_अङ्कः_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        सचे (!frame->buf[i]) {
            av_frame_unref(frame);
            पटिनिवत्त AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    अत्थाय (पूर्णाङ्क i = 0; i < planes - AV_अङ्कः_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        सचे (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            पटिनिवत्त AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_अङ्कः_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    पटिनिवत्त 0;

}

पूर्णाङ्क av_frame_get_buffer(AVFrame *frame, पूर्णाङ्क align)
{
    सचे (frame->format < 0)
        पटिनिवत्त AVERROR(EINVAL);

    सचे (frame->width > 0 && frame->height > 0)
        पटिनिवत्त ff_frame_get_video_buffer(frame, align, रिक्त, रिक्त);
    अञ्ञथा सचे (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        पटिनिवत्त get_audio_buffer(frame, align);

    पटिनिवत्त AVERROR(EINVAL);
}

स्थिर पूर्णाङ्क frame_copy_props(AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ratio    = src->sample_aspect_ratio;
    dst->crop_शिखरम्               = src->crop_शिखरम्;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_वामः              = src->crop_वामः;
    dst->crop_दक्षिणः             = src->crop_दक्षिणः;
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

    अत्थाय (पूर्णाङ्क i = 0; i < src->nb_side_data; i++) {
        ध्रुव AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        सचे (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            अनुवर्त;
        सचे (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            सचे (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                पटिनिवत्त AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } अञ्ञथा {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            सचे (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                पटिनिवत्त AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    पटिनिवत्त av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
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
    सचे (ret < 0)
        गच्छ fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    सचे (ret < 0)
        गच्छ fail;

    /* duplicate the frame data if it's not refcounted */
    सचे (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        सचे (ret < 0)
            गच्छ fail;

        ret = av_frame_copy(dst, src);
        सचे (ret < 0)
            गच्छ fail;

        पटिनिवत्त 0;
    }

    /* ref the buffers */
    अत्थाय (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        सचे (!src->buf[i])
            अनुवर्त;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        सचे (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }
    }

    सचे (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      परिमाण(*dst->extended_buf));
        सचे (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        अत्थाय (पूर्णाङ्क i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            सचे (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                गच्छ fail;
            }
        }
    }

    सचे (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        सचे (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }
    }

    /* duplicate extended data */
    सचे (src->extended_data != src->data) {
        पूर्णाङ्क ch = dst->ch_layout.nb_channels;

        सचे (ch <= 0 || ch > SIZE_MAX / परिमाण(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            गच्छ fail;
        }

        dst->extended_data = av_memdup(src->extended_data, परिमाण(*dst->extended_data) * ch);
        सचे (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }
    } अञ्ञथा
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     परिमाण(src->data));
    memcpy(dst->linesize, src->linesize, परिमाण(src->linesize));

    पटिनिवत्त 0;

fail:
    av_frame_unref(dst);
    पटिनिवत्त ret;
}

पूर्णाङ्क av_frame_replace(AVFrame *dst, ध्रुव AVFrame *src)
{
    पूर्णाङ्क ret = 0;

    सचे (dst == src)
        पटिनिवत्त AVERROR(EINVAL);

    सचे (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        सचे (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            पटिनिवत्त av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        सचे (ret < 0)
            गच्छ fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    सचे (ret < 0)
        गच्छ fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    सचे (ret < 0)
        गच्छ fail;

    /* replace the buffers */
    अत्थाय (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        सचे (ret < 0)
            गच्छ fail;
    }

    सचे (src->extended_buf) {
        सचे (dst->nb_extended_buf != src->nb_extended_buf) {
            पूर्णाङ्क nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            शून्य *tmp;

            अत्थाय (पूर्णाङ्क i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   परिमाण(*dst->extended_buf));
            सचे (!tmp) {
                ret = AVERROR(ENOMEM);
                गच्छ fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * परिमाण(*dst->extended_buf));
        }

        अत्थाय (पूर्णाङ्क i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            सचे (ret < 0)
                गच्छ fail;
        }
    } अञ्ञथा सचे (dst->extended_buf) {
        अत्थाय (पूर्णाङ्क i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    सचे (ret < 0)
        गच्छ fail;

    सचे (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    सचे (src->extended_data != src->data) {
        पूर्णाङ्क ch = dst->ch_layout.nb_channels;

        सचे (ch <= 0 || ch > SIZE_MAX / परिमाण(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            गच्छ fail;
        }

        dst->extended_data = av_memdup(src->extended_data, परिमाण(*dst->extended_data) * ch);
        सचे (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }
    } अञ्ञथा
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     परिमाण(src->data));
    memcpy(dst->linesize, src->linesize, परिमाण(src->linesize));

    पटिनिवत्त 0;

fail:
    av_frame_unref(dst);
    पटिनिवत्त ret;
}

AVFrame *av_frame_clone(ध्रुव AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    सचे (!ret)
        पटिनिवत्त रिक्त;

    सचे (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    पटिनिवत्त ret;
}

शून्य av_frame_unref(AVFrame *frame)
{
    सचे (!frame)
        पटिनिवत्त;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    अत्थाय (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    अत्थाय (पूर्णाङ्क i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    सचे (frame->extended_data != frame->data)
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
    सचे (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

पूर्णाङ्क av_frame_is_writable(AVFrame *frame)
{
    पूर्णाङ्क ret = 1;

    /* assume non-refcounted frames are not writable */
    सचे (!frame->buf[0])
        पटिनिवत्त 0;

    अत्थाय (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        सचे (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    अत्थाय (पूर्णाङ्क i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    पटिनिवत्त ret;
}

पूर्णाङ्क av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    पूर्णाङ्क ret;

    सचे (av_frame_is_writable(frame))
        पटिनिवत्त 0;

    memset(&tmp, 0, परिमाण(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    सचे (ret < 0) {
        av_frame_unref(&tmp);
        पटिनिवत्त ret;
    }

    सचे (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    अञ्ञथा
        ret = av_frame_get_buffer(&tmp, 0);
    सचे (ret < 0)
        पटिनिवत्त ret;

    ret = av_frame_copy(&tmp, frame);
    सचे (ret < 0) {
        av_frame_unref(&tmp);
        पटिनिवत्त ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    सचे (ret < 0) {
        av_frame_unref(&tmp);
        पटिनिवत्त ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    सचे (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    पटिनिवत्त 0;
}

पूर्णाङ्क av_frame_copy_props(AVFrame *dst, ध्रुव AVFrame *src)
{
    पटिनिवत्त frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(ध्रुव AVFrame *frame, पूर्णाङ्क plane)
{
    uintptr_t data;
    पूर्णाङ्क planes;

    सचे (frame->nb_samples) {
        पूर्णाङ्क channels = frame->ch_layout.nb_channels;
        सचे (!channels)
            पटिनिवत्त रिक्त;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } अञ्ञथा
        planes = 4;

    सचे (plane < 0 || plane >= planes || !frame->extended_data[plane])
        पटिनिवत्त रिक्त;
    data = (uintptr_t)frame->extended_data[plane];

    अत्थाय (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        सचे (data >= buf_begin && data < buf_begin + buf->size)
            पटिनिवत्त buf;
    }
    अत्थाय (पूर्णाङ्क i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        सचे (data >= buf_begin && data < buf_begin + buf->size)
            पटिनिवत्त buf;
    }
    पटिनिवत्त रिक्त;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 गणना AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    पटिनिवत्त
        ff_frame_side_data_add_from_buf(
            &frame->side_data, &frame->nb_side_data, type, buf);
}

AVFrameSideData *av_frame_new_side_data(AVFrame *frame,
                                        गणना AVFrameSideDataType type,
                                        size_t size)
{
    AVFrameSideData *ret;
    AVBufferRef *buf = av_buffer_alloc(size);
    ret = av_frame_new_side_data_from_buf(frame, type, buf);
    सचे (!ret)
        av_buffer_unref(&buf);
    पटिनिवत्त ret;
}

AVFrameSideData *av_frame_get_side_data(ध्रुव AVFrame *frame,
                                        गणना AVFrameSideDataType type)
{
    पटिनिवत्त (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

स्थिर पूर्णाङ्क frame_copy_video(AVFrame *dst, ध्रुव AVFrame *src)
{
    पूर्णाङ्क planes;

    सचे (dst->width  < src->width ||
        dst->height < src->height)
        पटिनिवत्त AVERROR(EINVAL);

    सचे (src->hw_frames_ctx || dst->hw_frames_ctx)
        पटिनिवत्त av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_गणनम्_planes(dst->format);
    अत्थाय (पूर्णाङ्क i = 0; i < planes; i++)
        सचे (!dst->data[i] || !src->data[i])
            पटिनिवत्त AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क frame_copy_audio(AVFrame *dst, ध्रुव AVFrame *src)
{
    पूर्णाङ्क planar   = av_sample_fmt_is_planar(dst->format);
    पूर्णाङ्क channels = dst->ch_layout.nb_channels;
    पूर्णाङ्क planes   = planar ? channels : 1;

    सचे (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        पटिनिवत्त AVERROR(EINVAL);

    अत्थाय (पूर्णाङ्क i = 0; i < planes; i++)
        सचे (!dst->extended_data[i] || !src->extended_data[i])
            पटिनिवत्त AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    पटिनिवत्त 0;
}

पूर्णाङ्क av_frame_copy(AVFrame *dst, ध्रुव AVFrame *src)
{
    सचे (dst->format != src->format || dst->format < 0)
        पटिनिवत्त AVERROR(EINVAL);

    सचे (dst->width > 0 && dst->height > 0)
        पटिनिवत्त frame_copy_video(dst, src);
    अञ्ञथा सचे (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        पटिनिवत्त frame_copy_audio(dst, src);

    पटिनिवत्त AVERROR(EINVAL);
}

शून्य av_frame_remove_side_data(AVFrame *frame, गणना AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

स्थिर पूर्णाङ्क calc_cropping_offsets(size_t offsets[4], ध्रुव AVFrame *frame,
                                 ध्रुव AVPixFmtDescriptor *desc)
{
    अत्थाय (पूर्णाङ्क i = 0; frame->data[i]; i++) {
        ध्रुव AVComponentDescriptor *comp = रिक्त;
        पूर्णाङ्क shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        पूर्णाङ्क shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        सचे (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            भङ्ग;
        }

        /* find any component descriptor for this plane */
        अत्थाय (पूर्णाङ्क j = 0; j < desc->nb_components; j++) {
            सचे (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                भङ्ग;
            }
        }
        सचे (!comp)
            पटिनिवत्त AVERROR_BUG;

        offsets[i] = (frame->crop_शिखरम्  >> shift_y) * frame->linesize[i] +
                     (frame->crop_वामः >> shift_x) * comp->step;
    }

    पटिनिवत्त 0;
}

पूर्णाङ्क av_frame_apply_cropping(AVFrame *frame, पूर्णाङ्क flags)
{
    ध्रुव AVPixFmtDescriptor *desc;
    size_t offsets[4];
    पूर्णाङ्क ret;

    सचे (!(frame->width > 0 && frame->height > 0))
        पटिनिवत्त AVERROR(EINVAL);

    सचे (frame->crop_वामः >= INT_MAX - frame->crop_दक्षिणः        ||
        frame->crop_शिखरम्  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_वामः + frame->crop_दक्षिणः) >= frame->width ||
        (frame->crop_शिखरम् + frame->crop_bottom) >= frame->height)
        पटिनिवत्त AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    सचे (!desc)
        पटिनिवत्त AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    सचे (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_दक्षिणः;
        frame->height     -= frame->crop_bottom;
        frame->crop_दक्षिणः  = 0;
        frame->crop_bottom = 0;
        पटिनिवत्त 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    सचे (ret < 0)
        पटिनिवत्त ret;

    /* adjust the offsets to avoid breaking alignment */
    सचे (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        पूर्णाङ्क log2_crop_align = frame->crop_वामः ? ff_ctz(frame->crop_वामः) : INT_MAX;
        पूर्णाङ्क min_log2_align = INT_MAX;

        अत्थाय (पूर्णाङ्क i = 0; frame->data[i]; i++) {
            पूर्णाङ्क log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        सचे (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_वामः &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            सचे (ret < 0)
                पटिनिवत्त ret;
        }
    }

    अत्थाय (पूर्णाङ्क i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_वामः + frame->crop_दक्षिणः);
    frame->height     -= (frame->crop_शिखरम्  + frame->crop_bottom);
    frame->crop_वामः   = 0;
    frame->crop_दक्षिणः  = 0;
    frame->crop_शिखरम्    = 0;
    frame->crop_bottom = 0;

    पटिनिवत्त 0;
}
