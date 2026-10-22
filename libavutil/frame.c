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

#समावेश "channel_layout.h"
#समावेश "avassert.h"
#समावेश "buffer.h"
#समावेश "dict.h"
#समावेश "frame.h"
#समावेश "frame_internal.h"
#समावेश "imgutils.h"
#समावेश "mem.h"
#समावेश "refstruct.h"
#समावेश "samplefmt.h"
#समावेश "side_data.h"
#समावेश "hwcontext.h"

अटल व्योम get_frame_defaults(AVFrame *frame)
{
    स_रखो(frame, 0, माप(*frame));

    frame->pts                   =
    frame->pkt_dts               = AV_NOPTS_मूल्य;
    frame->best_effort_timestamp = AV_NOPTS_मूल्य;
    frame->duration            = 0;
    frame->time_base           = (AVRational){ 0, 1 };
    frame->sample_aspect_ratio = (AVRational){ 0, 1 };
    frame->format              = -1; /* unknown */
    frame->extended_तथ्य       = frame->तथ्य;
    frame->color_primaries     = AVCOL_PRI_UNSPECIFIED;
    frame->color_trc           = AVCOL_TRC_UNSPECIFIED;
    frame->colorspace          = AVCOL_SPC_UNSPECIFIED;
    frame->color_range         = AVCOL_RANGE_UNSPECIFIED;
    frame->chroma_location     = AVCHROMA_LOC_UNSPECIFIED;
    frame->alpha_mode          = AVALPHA_MODE_UNSPECIFIED;
    frame->flags               = 0;
}

AVFrame *av_frame_alloc(व्योम)
{
    AVFrame *frame = av_malloc(माप(*frame));

    अगर (!frame)
        वापस शून्य;

    get_frame_defaults(frame);

    वापस frame;
}

व्योम av_frame_free(AVFrame **frame)
{
    अगर (!frame || !*frame)
        वापस;

    av_frame_unref(*frame);
    av_freep(frame);
}

#घोषणा ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

पूर्णांक ff_frame_get_video_बफर(AVFrame *frame, पूर्णांक align,
                              AVBufferRef *(*alloc)(व्योम *opaque, माप_प्रकार आकार),
                              व्योम *opaque)
{
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    पूर्णांक ret, padded_height;
    पूर्णांक plane_padding;
    सूचक_भेद_प्रकार linesizes[4];
    माप_प्रकार योग_आकार, sizes[4];

    अगर (!desc)
        वापस AVERROR(EINVAL);

    अगर ((ret = av_image_check_आकार(frame->width, frame->height, 0, शून्य)) < 0)
        वापस ret;

    अगर (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    अगर (!frame->linesize[0]) {
        क्रम (पूर्णांक i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            अगर (ret < 0)
                वापस ret;
            अगर (!(frame->linesize[0] & (align-1)))
                अवरोध;
        }

        क्रम (पूर्णांक i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    क्रम (पूर्णांक i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    अगर ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        वापस ret;

    योग_आकार = 4 * plane_padding + 4 * align;
    क्रम (पूर्णांक i = 0; i < 4; i++) {
        अगर (sizes[i] > SIZE_MAX - योग_आकार)
            वापस AVERROR(EINVAL);
        योग_आकार += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, योग_आकार) : av_बफर_alloc(योग_आकार);
    अगर (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }

    अगर ((ret = av_image_fill_pointers(frame->तथ्य, frame->format, padded_height,
                                      frame->buf[0]->तथ्य, frame->linesize)) < 0)
        जाओ fail;

    क्रम (पूर्णांक i = 1; i < 4; i++) {
        अगर (frame->तथ्य[i])
            frame->तथ्य[i] += i * plane_padding;
        frame->तथ्य[i] = (uint8_t *)FFALIGN((uintptr_t)frame->तथ्य[i], align);
    }

    frame->extended_तथ्य = frame->तथ्य;

    वापस 0;
fail:
    av_frame_unref(frame);
    वापस ret;
}

अटल पूर्णांक get_audio_बफर(AVFrame *frame, पूर्णांक align)
{
    पूर्णांक planar   = av_sample_fmt_is_planar(frame->format);
    पूर्णांक channels, planes;
    माप_प्रकार आकार;
    पूर्णांक ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    अगर (!frame->linesize[0]) {
        ret = av_samples_get_बफर_आकार(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        अगर (ret < 0)
            वापस ret;
    }

    अगर (align <= 0)
        align = ALIGN;

    अगर (planes > AV_अंक_तथ्य_POINTERS) {
        frame->extended_तथ्य = av_calloc(planes,
                                          माप(*frame->extended_तथ्य));
        frame->extended_buf  = av_calloc(planes - AV_अंक_तथ्य_POINTERS,
                                          माप(*frame->extended_buf));
        अगर (!frame->extended_तथ्य || !frame->extended_buf) {
            av_freep(&frame->extended_तथ्य);
            av_freep(&frame->extended_buf);
            वापस AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_अंक_तथ्य_POINTERS;
    } अन्यथा
        frame->extended_तथ्य = frame->तथ्य;

    अगर (frame->linesize[0] > SIZE_MAX - align)
        वापस AVERROR(EINVAL);
    आकार = frame->linesize[0] + (माप_प्रकार)align;

    क्रम (पूर्णांक i = 0; i < FFMIN(planes, AV_अंक_तथ्य_POINTERS); i++) {
        frame->buf[i] = av_बफर_alloc(आकार);
        अगर (!frame->buf[i]) {
            av_frame_unref(frame);
            वापस AVERROR(ENOMEM);
        }
        frame->extended_तथ्य[i] = frame->तथ्य[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->तथ्य, align);
    }
    क्रम (पूर्णांक i = 0; i < planes - AV_अंक_तथ्य_POINTERS; i++) {
        frame->extended_buf[i] = av_बफर_alloc(आकार);
        अगर (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            वापस AVERROR(ENOMEM);
        }
        frame->extended_तथ्य[i + AV_अंक_तथ्य_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->तथ्य, align);
    }
    वापस 0;

}

पूर्णांक av_frame_get_बफर(AVFrame *frame, पूर्णांक align)
{
    अगर (frame->format < 0)
        वापस AVERROR(EINVAL);

    अगर (frame->width > 0 && frame->height > 0)
        वापस ff_frame_get_video_बफर(frame, align, शून्य, शून्य);
    अन्यथा अगर (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        वापस get_audio_बफर(frame, align);

    वापस AVERROR(EINVAL);
}

अटल पूर्णांक frame_copy_props(AVFrame *dst, स्थिर AVFrame *src, पूर्णांक force_copy)
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

    क्रम (पूर्णांक i = 0; i < src->nb_side_तथ्य; i++) {
        स्थिर AVFrame_Side_तथ्य *sd_src = src->side_तथ्य[i];
        AVFrame_Side_तथ्य *sd_dst;
        अगर (   sd_src->type == AV_FRAME_तथ्य_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            जारी;
        अगर (force_copy) {
            sd_dst = av_frame_new_side_तथ्य(dst, sd_src->type,
                                            sd_src->आकार);
            अगर (!sd_dst) {
                av_frame_side_तथ्य_free(&dst->side_तथ्य, &dst->nb_side_तथ्य);
                वापस AVERROR(ENOMEM);
            }
            स_नकल(sd_dst->तथ्य, sd_src->तथ्य, sd_src->आकार);
        } अन्यथा {
            AVBufferRef *ref = av_बफर_ref(sd_src->buf);
            sd_dst = av_frame_new_side_तथ्य_from_buf(dst, sd_src->type, ref);
            अगर (!sd_dst) {
                av_बफर_unref(&ref);
                av_frame_side_तथ्य_free(&dst->side_तथ्य, &dst->nb_side_तथ्य);
                वापस AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    वापस av_बफर_replace(&dst->opaque_ref, src->opaque_ref);
}

पूर्णांक av_frame_ref(AVFrame *dst, स्थिर AVFrame *src)
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
    अगर (ret < 0)
        जाओ fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    अगर (ret < 0)
        जाओ fail;

    /* duplicate the frame data if it's not refcounted */
    अगर (!src->buf[0]) {
        ret = av_frame_get_बफर(dst, 0);
        अगर (ret < 0)
            जाओ fail;

        ret = av_frame_copy(dst, src);
        अगर (ret < 0)
            जाओ fail;

        वापस 0;
    }

    /* ref the buffers */
    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        अगर (!src->buf[i])
            जारी;
        dst->buf[i] = av_बफर_ref(src->buf[i]);
        अगर (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            जाओ fail;
        }
    }

    अगर (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      माप(*dst->extended_buf));
        अगर (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            जाओ fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        क्रम (पूर्णांक i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_बफर_ref(src->extended_buf[i]);
            अगर (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                जाओ fail;
            }
        }
    }

    अगर (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_बफर_ref(src->hw_frames_ctx);
        अगर (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            जाओ fail;
        }
    }

    /* duplicate extended data */
    अगर (src->extended_तथ्य != src->तथ्य) {
        पूर्णांक ch = dst->ch_layout.nb_channels;

        अगर (ch <= 0 || ch > SIZE_MAX / माप(*dst->extended_तथ्य)) {
            ret = AVERROR(EINVAL);
            जाओ fail;
        }

        dst->extended_तथ्य = av_memdup(src->extended_तथ्य, माप(*dst->extended_तथ्य) * ch);
        अगर (!dst->extended_तथ्य) {
            ret = AVERROR(ENOMEM);
            जाओ fail;
        }
    } अन्यथा
        dst->extended_तथ्य = dst->तथ्य;

    स_नकल(dst->तथ्य,     src->तथ्य,     माप(src->तथ्य));
    स_नकल(dst->linesize, src->linesize, माप(src->linesize));

    वापस 0;

fail:
    av_frame_unref(dst);
    वापस ret;
}

पूर्णांक av_frame_replace(AVFrame *dst, स्थिर AVFrame *src)
{
    पूर्णांक ret = 0;

    अगर (dst == src)
        वापस AVERROR(EINVAL);

    अगर (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        अगर (   src->तथ्य[0] || src->तथ्य[1]
            || src->तथ्य[2] || src->तथ्य[3])
            वापस av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        अगर (ret < 0)
            जाओ fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    अगर (ret < 0)
        जाओ fail;

    av_frame_side_तथ्य_free(&dst->side_तथ्य, &dst->nb_side_तथ्य);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    अगर (ret < 0)
        जाओ fail;

    /* replace the buffers */
    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_बफर_replace(&dst->buf[i], src->buf[i]);
        अगर (ret < 0)
            जाओ fail;
    }

    अगर (src->extended_buf) {
        अगर (dst->nb_extended_buf != src->nb_extended_buf) {
            पूर्णांक nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            व्योम *tmp;

            क्रम (पूर्णांक i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_बफर_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   माप(*dst->extended_buf));
            अगर (!tmp) {
                ret = AVERROR(ENOMEM);
                जाओ fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            स_रखो(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * माप(*dst->extended_buf));
        }

        क्रम (पूर्णांक i = 0; i < src->nb_extended_buf; i++) {
            ret = av_बफर_replace(&dst->extended_buf[i], src->extended_buf[i]);
            अगर (ret < 0)
                जाओ fail;
        }
    } अन्यथा अगर (dst->extended_buf) {
        क्रम (पूर्णांक i = 0; i < dst->nb_extended_buf; i++)
            av_बफर_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_बफर_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    अगर (ret < 0)
        जाओ fail;

    अगर (dst->extended_तथ्य != dst->तथ्य)
        av_freep(&dst->extended_तथ्य);

    अगर (src->extended_तथ्य != src->तथ्य) {
        पूर्णांक ch = dst->ch_layout.nb_channels;

        अगर (ch <= 0 || ch > SIZE_MAX / माप(*dst->extended_तथ्य)) {
            ret = AVERROR(EINVAL);
            जाओ fail;
        }

        dst->extended_तथ्य = av_memdup(src->extended_तथ्य, माप(*dst->extended_तथ्य) * ch);
        अगर (!dst->extended_तथ्य) {
            ret = AVERROR(ENOMEM);
            जाओ fail;
        }
    } अन्यथा
        dst->extended_तथ्य = dst->तथ्य;

    स_नकल(dst->तथ्य,     src->तथ्य,     माप(src->तथ्य));
    स_नकल(dst->linesize, src->linesize, माप(src->linesize));

    वापस 0;

fail:
    av_frame_unref(dst);
    वापस ret;
}

AVFrame *av_frame_clone(स्थिर AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    अगर (!ret)
        वापस शून्य;

    अगर (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    वापस ret;
}

व्योम av_frame_unref(AVFrame *frame)
{
    अगर (!frame)
        वापस;

    av_frame_side_तथ्य_free(&frame->side_तथ्य, &frame->nb_side_तथ्य);

    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_बफर_unref(&frame->buf[i]);
    क्रम (पूर्णांक i = 0; i < frame->nb_extended_buf; i++)
        av_बफर_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_बफर_unref(&frame->hw_frames_ctx);

    av_बफर_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    अगर (frame->extended_तथ्य != frame->तथ्य)
        av_freep(&frame->extended_तथ्य);

    av_channel_layout_uninit(&frame->ch_layout);

    get_frame_defaults(frame);
}

व्योम av_frame_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    *dst = *src;
    अगर (src->extended_तथ्य == src->तथ्य)
        dst->extended_तथ्य = dst->तथ्य;
    get_frame_defaults(src);
}

पूर्णांक av_frame_is_writable(AVFrame *frame)
{
    पूर्णांक ret = 1;

    /* assume non-refcounted frames are not writable */
    अगर (!frame->buf[0])
        वापस 0;

    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        अगर (frame->buf[i])
            ret &= !!av_बफर_is_writable(frame->buf[i]);
    क्रम (पूर्णांक i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_बफर_is_writable(frame->extended_buf[i]);

    वापस ret;
}

पूर्णांक av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    पूर्णांक ret;

    अगर (av_frame_is_writable(frame))
        वापस 0;

    स_रखो(&tmp, 0, माप(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    अगर (ret < 0) {
        av_frame_unref(&tmp);
        वापस ret;
    }

    अगर (frame->hw_frames_ctx)
        ret = av_hwframe_get_बफर(frame->hw_frames_ctx, &tmp, 0);
    अन्यथा
        ret = av_frame_get_बफर(&tmp, 0);
    अगर (ret < 0)
        वापस ret;

    ret = av_frame_copy(&tmp, frame);
    अगर (ret < 0) {
        av_frame_unref(&tmp);
        वापस ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    अगर (ret < 0) {
        av_frame_unref(&tmp);
        वापस ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    अगर (tmp.तथ्य == tmp.extended_तथ्य)
        frame->extended_तथ्य = frame->तथ्य;

    वापस 0;
}

पूर्णांक av_frame_copy_props(AVFrame *dst, स्थिर AVFrame *src)
{
    वापस frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_बफर(स्थिर AVFrame *frame, पूर्णांक plane)
{
    uintptr_t तथ्य;
    पूर्णांक planes;

    अगर (frame->nb_samples) {
        पूर्णांक channels = frame->ch_layout.nb_channels;
        अगर (!channels)
            वापस शून्य;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } अन्यथा
        planes = 4;

    अगर (plane < 0 || plane >= planes || !frame->extended_तथ्य[plane])
        वापस शून्य;
    तथ्य = (uintptr_t)frame->extended_तथ्य[plane];

    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->तथ्य;

        अगर (तथ्य >= buf_begin && तथ्य < buf_begin + buf->आकार)
            वापस buf;
    }
    क्रम (पूर्णांक i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->तथ्य;

        अगर (तथ्य >= buf_begin && तथ्य < buf_begin + buf->आकार)
            वापस buf;
    }
    वापस शून्य;
}

AVFrame_Side_तथ्य *av_frame_new_side_तथ्य_from_buf(AVFrame *frame,
                                                 क्रमागत AVFrame_Side_तथ्य_Type type,
                                                 AVBufferRef *buf)
{
    वापस
        ff_frame_side_तथ्य_add_from_buf(
            &frame->side_तथ्य, &frame->nb_side_तथ्य, type, buf);
}

AVFrame_Side_तथ्य *av_frame_new_side_तथ्य(AVFrame *frame,
                                        क्रमागत AVFrame_Side_तथ्य_Type type,
                                        माप_प्रकार आकार)
{
    AVFrame_Side_तथ्य *ret;
    AVBufferRef *buf = av_बफर_alloc(आकार);
    ret = av_frame_new_side_तथ्य_from_buf(frame, type, buf);
    अगर (!ret)
        av_बफर_unref(&buf);
    वापस ret;
}

AVFrame_Side_तथ्य *av_frame_get_side_तथ्य(स्थिर AVFrame *frame,
                                        क्रमागत AVFrame_Side_तथ्य_Type type)
{
    वापस (AVFrame_Side_तथ्य *)av_frame_side_तथ्य_get(
        frame->side_तथ्य, frame->nb_side_तथ्य,
        type
    );
}

अटल पूर्णांक frame_copy_video(AVFrame *dst, स्थिर AVFrame *src)
{
    पूर्णांक planes;

    अगर (dst->width  < src->width ||
        dst->height < src->height)
        वापस AVERROR(EINVAL);

    अगर (src->hw_frames_ctx || dst->hw_frames_ctx)
        वापस av_hwframe_transfer_तथ्य(dst, src, 0);

    planes = av_pix_fmt_गिनती_planes(dst->format);
    क्रम (पूर्णांक i = 0; i < planes; i++)
        अगर (!dst->तथ्य[i] || !src->तथ्य[i])
            वापस AVERROR(EINVAL);

    av_image_copy2(dst->तथ्य, dst->linesize,
                   src->तथ्य, src->linesize,
                   dst->format, src->width, src->height);

    वापस 0;
}

अटल पूर्णांक frame_copy_audio(AVFrame *dst, स्थिर AVFrame *src)
{
    पूर्णांक planar   = av_sample_fmt_is_planar(dst->format);
    पूर्णांक channels = dst->ch_layout.nb_channels;
    पूर्णांक planes   = planar ? channels : 1;

    अगर (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        वापस AVERROR(EINVAL);

    क्रम (पूर्णांक i = 0; i < planes; i++)
        अगर (!dst->extended_तथ्य[i] || !src->extended_तथ्य[i])
            वापस AVERROR(EINVAL);

    av_samples_copy(dst->extended_तथ्य, src->extended_तथ्य, 0, 0,
                    dst->nb_samples, channels, dst->format);

    वापस 0;
}

पूर्णांक av_frame_copy(AVFrame *dst, स्थिर AVFrame *src)
{
    अगर (dst->format != src->format || dst->format < 0)
        वापस AVERROR(EINVAL);

    अगर (dst->width > 0 && dst->height > 0)
        वापस frame_copy_video(dst, src);
    अन्यथा अगर (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        वापस frame_copy_audio(dst, src);

    वापस AVERROR(EINVAL);
}

व्योम av_frame_remove_side_तथ्य(AVFrame *frame, क्रमागत AVFrame_Side_तथ्य_Type type)
{
    av_frame_side_तथ्य_remove(&frame->side_तथ्य, &frame->nb_side_तथ्य, type);
}

अटल पूर्णांक calc_cropping_offsets(माप_प्रकार offsets[4], स्थिर AVFrame *frame,
                                 स्थिर AVPixFmtDescriptor *desc)
{
    क्रम (पूर्णांक i = 0; frame->तथ्य[i]; i++) {
        स्थिर AVComponentDescriptor *comp = शून्य;
        पूर्णांक shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        पूर्णांक shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        अगर (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            अवरोध;
        }

        /* find any component descriptor for this plane */
        क्रम (पूर्णांक j = 0; j < desc->nb_components; j++) {
            अगर (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                अवरोध;
            }
        }
        अगर (!comp)
            वापस AVERROR_BUG;

        offsets[i] = (frame->crop_शीर्ष  >> shift_y) * frame->linesize[i] +
                     (frame->crop_बायाँ >> shift_x) * comp->step;
    }

    वापस 0;
}

पूर्णांक av_frame_apply_cropping(AVFrame *frame, पूर्णांक flags)
{
    स्थिर AVPixFmtDescriptor *desc;
    माप_प्रकार offsets[4];
    पूर्णांक ret;

    अगर (!(frame->width > 0 && frame->height > 0))
        वापस AVERROR(EINVAL);

    अगर (frame->crop_बायाँ >= पूर्णांक_उच्च - frame->crop_दायाँ        ||
        frame->crop_शीर्ष  >= पूर्णांक_उच्च - frame->crop_bottom       ||
        (frame->crop_बायाँ + frame->crop_दायाँ) >= frame->width ||
        (frame->crop_शीर्ष + frame->crop_bottom) >= frame->height)
        वापस AVERROR(दुस्फल);

    desc = av_pix_fmt_desc_get(frame->format);
    अगर (!desc)
        वापस AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    अगर (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_दायाँ;
        frame->height     -= frame->crop_bottom;
        frame->crop_दायाँ  = 0;
        frame->crop_bottom = 0;
        वापस 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    अगर (ret < 0)
        वापस ret;

    /* adjust the offsets to avoid breaking alignment */
    अगर (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        पूर्णांक log2_crop_align = frame->crop_बायाँ ? ff_ctz(frame->crop_बायाँ) : पूर्णांक_उच्च;
        पूर्णांक min_log2_align = पूर्णांक_उच्च;

        क्रम (पूर्णांक i = 0; frame->तथ्य[i]; i++) {
            पूर्णांक log2_align = offsets[i] ? ff_ctz(offsets[i]) : पूर्णांक_उच्च;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        अगर (min_log2_align < 5 && log2_crop_align != पूर्णांक_उच्च) {
            frame->crop_बायाँ &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            अगर (ret < 0)
                वापस ret;
        }
    }

    क्रम (पूर्णांक i = 0; frame->तथ्य[i]; i++)
        frame->तथ्य[i] += offsets[i];

    frame->width      -= (frame->crop_बायाँ + frame->crop_दायाँ);
    frame->height     -= (frame->crop_शीर्ष  + frame->crop_bottom);
    frame->crop_बायाँ   = 0;
    frame->crop_दायाँ  = 0;
    frame->crop_शीर्ष    = 0;
    frame->crop_bottom = 0;

    वापस 0;
}
