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

#অন্তর্ভাব "channel_layout.h"
#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "buffer.h"
#অন্তর্ভাব "dict.h"
#অন্তর্ভাব "frame.h"
#অন্তর্ভাব "frame_internal.h"
#অন্তর্ভাব "imgutils.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "refstruct.h"
#অন্তর্ভাব "samplefmt.h"
#অন্তর্ভাব "side_data.h"
#অন্তর্ভাব "hwcontext.h"

স্থির শূন্য get_frame_defaults(AVFrame *frame)
{
    memset(frame, 0, আকার(*frame));

    frame->pts                   =
    frame->pkt_dts               = AV_NOPTS_মান;
    frame->best_effort_timestamp = AV_NOPTS_মান;
    frame->duration            = 0;
    frame->time_base           = (AVRational){ 0, 1 };
    frame->sample_aspect_ratio = (AVRational){ 0, 1 };
    frame->format              = -1; /* unknown */
    frame->extended_তথ্য       = frame->তথ্য;
    frame->color_primaries     = AVCOL_PRI_UNSPECIFIED;
    frame->color_trc           = AVCOL_TRC_UNSPECIFIED;
    frame->colorspace          = AVCOL_SPC_UNSPECIFIED;
    frame->color_range         = AVCOL_RANGE_UNSPECIFIED;
    frame->chroma_location     = AVCHROMA_LOC_UNSPECIFIED;
    frame->alpha_mode          = AVALPHA_MODE_UNSPECIFIED;
    frame->flags               = 0;
}

AVFrame *av_frame_alloc(শূন্য)
{
    AVFrame *frame = av_malloc(আকার(*frame));

    যদি (!frame)
        ফেরত ফাঁকা;

    get_frame_defaults(frame);

    ফেরত frame;
}

শূন্য av_frame_free(AVFrame **frame)
{
    যদি (!frame || !*frame)
        ফেরত;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

পূর্ণসংখ্যা ff_frame_get_video_বাফার(AVFrame *frame, পূর্ণসংখ্যা align,
                              AVBufferRef *(*alloc)(শূন্য *opaque, size_t আকার_2),
                              শূন্য *opaque)
{
    ধ্রুবক AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    পূর্ণসংখ্যা ret, padded_height;
    পূর্ণসংখ্যা plane_padding;
    ptrdiff_t linesizes[4];
    size_t যোগ_আকার, sizes[4];

    যদি (!desc)
        ফেরত AVERROR(EINVAL);

    যদি ((ret = av_image_check_আকার(frame->width, frame->height, 0, ফাঁকা)) < 0)
        ফেরত ret;

    যদি (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    যদি (!frame->linesize[0]) {
        জন্য (পূর্ণসংখ্যা i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            যদি (ret < 0)
                ফেরত ret;
            যদি (!(frame->linesize[0] & (align-1)))
                বিরতি;
        }

        জন্য (পূর্ণসংখ্যা i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    জন্য (পূর্ণসংখ্যা i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    যদি ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        ফেরত ret;

    যোগ_আকার = 4 * plane_padding + 4 * align;
    জন্য (পূর্ণসংখ্যা i = 0; i < 4; i++) {
        যদি (sizes[i] > SIZE_MAX - যোগ_আকার)
            ফেরত AVERROR(EINVAL);
        যোগ_আকার += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, যোগ_আকার) : av_বাফার_alloc(যোগ_আকার);
    যদি (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        যাও fail;
    }

    যদি ((ret = av_image_fill_pointers(frame->তথ্য, frame->format, padded_height,
                                      frame->buf[0]->তথ্য, frame->linesize)) < 0)
        যাও fail;

    জন্য (পূর্ণসংখ্যা i = 1; i < 4; i++) {
        যদি (frame->তথ্য[i])
            frame->তথ্য[i] += i * plane_padding;
        frame->তথ্য[i] = (uint8_t *)FFALIGN((uintptr_t)frame->তথ্য[i], align);
    }

    frame->extended_তথ্য = frame->তথ্য;

    ফেরত 0;
fail:
    av_frame_unref(frame);
    ফেরত ret;
}

স্থির পূর্ণসংখ্যা get_audio_বাফার(AVFrame *frame, পূর্ণসংখ্যা align)
{
    পূর্ণসংখ্যা planar   = av_sample_fmt_is_planar(frame->format);
    পূর্ণসংখ্যা channels, planes;
    size_t আকার_2;
    পূর্ণসংখ্যা ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    যদি (!frame->linesize[0]) {
        ret = av_samples_get_বাফার_আকার(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        যদি (ret < 0)
            ফেরত ret;
    }

    যদি (align <= 0)
        align = ALIGN;

    যদি (planes > AV_অঙ্ক_তথ্য_POINTERS) {
        frame->extended_তথ্য = av_calloc(planes,
                                          আকার(*frame->extended_তথ্য));
        frame->extended_buf  = av_calloc(planes - AV_অঙ্ক_তথ্য_POINTERS,
                                          আকার(*frame->extended_buf));
        যদি (!frame->extended_তথ্য || !frame->extended_buf) {
            av_freep(&frame->extended_তথ্য);
            av_freep(&frame->extended_buf);
            ফেরত AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_অঙ্ক_তথ্য_POINTERS;
    } অন্যথা
        frame->extended_তথ্য = frame->তথ্য;

    যদি (frame->linesize[0] > SIZE_MAX - align)
        ফেরত AVERROR(EINVAL);
    আকার_2 = frame->linesize[0] + (size_t)align;

    জন্য (পূর্ণসংখ্যা i = 0; i < FFMIN(planes, AV_অঙ্ক_তথ্য_POINTERS); i++) {
        frame->buf[i] = av_বাফার_alloc(আকার_2);
        যদি (!frame->buf[i]) {
            av_frame_unref(frame);
            ফেরত AVERROR(ENOMEM);
        }
        frame->extended_তথ্য[i] = frame->তথ্য[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->তথ্য, align);
    }
    জন্য (পূর্ণসংখ্যা i = 0; i < planes - AV_অঙ্ক_তথ্য_POINTERS; i++) {
        frame->extended_buf[i] = av_বাফার_alloc(আকার_2);
        যদি (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            ফেরত AVERROR(ENOMEM);
        }
        frame->extended_তথ্য[i + AV_অঙ্ক_তথ্য_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->তথ্য, align);
    }
    ফেরত 0;

}

পূর্ণসংখ্যা av_frame_get_বাফার(AVFrame *frame, পূর্ণসংখ্যা align)
{
    যদি (frame->format < 0)
        ফেরত AVERROR(EINVAL);

    যদি (frame->width > 0 && frame->height > 0)
        ফেরত ff_frame_get_video_বাফার(frame, align, ফাঁকা, ফাঁকা);
    অন্যথা যদি (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        ফেরত get_audio_বাফার(frame, align);

    ফেরত AVERROR(EINVAL);
}

স্থির পূর্ণসংখ্যা frame_copy_props(AVFrame *dst, ধ্রুবক AVFrame *src, পূর্ণসংখ্যা force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ratio    = src->sample_aspect_ratio;
    dst->crop_শীর্ষ               = src->crop_শীর্ষ;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_বাম              = src->crop_বাম;
    dst->crop_ডান             = src->crop_ডান;
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

    জন্য (পূর্ণসংখ্যা i = 0; i < src->nb_side_তথ্য; i++) {
        ধ্রুবক AVFrame_Side_তথ্য *sd_src = src->side_তথ্য[i];
        AVFrame_Side_তথ্য *sd_dst;
        যদি (   sd_src->type == AV_FRAME_তথ্য_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            চালু;
        যদি (force_copy) {
            sd_dst = av_frame_new_side_তথ্য(dst, sd_src->type,
                                            sd_src->আকার_2);
            যদি (!sd_dst) {
                av_frame_side_তথ্য_free(&dst->side_তথ্য, &dst->nb_side_তথ্য);
                ফেরত AVERROR(ENOMEM);
            }
            memcpy(sd_dst->তথ্য, sd_src->তথ্য, sd_src->আকার_2);
        } অন্যথা {
            AVBufferRef *ref = av_বাফার_ref(sd_src->buf);
            sd_dst = av_frame_new_side_তথ্য_from_buf(dst, sd_src->type, ref);
            যদি (!sd_dst) {
                av_বাফার_unref(&ref);
                av_frame_side_তথ্য_free(&dst->side_তথ্য, &dst->nb_side_তথ্য);
                ফেরত AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    ফেরত av_বাফার_replace(&dst->opaque_ref, src->opaque_ref);
}

পূর্ণসংখ্যা av_frame_ref(AVFrame *dst, ধ্রুবক AVFrame *src)
{
    পূর্ণসংখ্যা ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    যদি (ret < 0)
        যাও fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    যদি (ret < 0)
        যাও fail;

    /* duplicate the frame data if it's not refcounted */
    যদি (!src->buf[0]) {
        ret = av_frame_get_বাফার(dst, 0);
        যদি (ret < 0)
            যাও fail;

        ret = av_frame_copy(dst, src);
        যদি (ret < 0)
            যাও fail;

        ফেরত 0;
    }

    /* ref the buffers */
    জন্য (পূর্ণসংখ্যা i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        যদি (!src->buf[i])
            চালু;
        dst->buf[i] = av_বাফার_ref(src->buf[i]);
        যদি (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            যাও fail;
        }
    }

    যদি (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      আকার(*dst->extended_buf));
        যদি (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            যাও fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        জন্য (পূর্ণসংখ্যা i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_বাফার_ref(src->extended_buf[i]);
            যদি (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                যাও fail;
            }
        }
    }

    যদি (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_বাফার_ref(src->hw_frames_ctx);
        যদি (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            যাও fail;
        }
    }

    /* duplicate extended data */
    যদি (src->extended_তথ্য != src->তথ্য) {
        পূর্ণসংখ্যা ch = dst->ch_layout.nb_channels;

        যদি (ch <= 0 || ch > SIZE_MAX / আকার(*dst->extended_তথ্য)) {
            ret = AVERROR(EINVAL);
            যাও fail;
        }

        dst->extended_তথ্য = av_memdup(src->extended_তথ্য, আকার(*dst->extended_তথ্য) * ch);
        যদি (!dst->extended_তথ্য) {
            ret = AVERROR(ENOMEM);
            যাও fail;
        }
    } অন্যথা
        dst->extended_তথ্য = dst->তথ্য;

    memcpy(dst->তথ্য,     src->তথ্য,     আকার(src->তথ্য));
    memcpy(dst->linesize, src->linesize, আকার(src->linesize));

    ফেরত 0;

fail:
    av_frame_unref(dst);
    ফেরত ret;
}

পূর্ণসংখ্যা av_frame_replace(AVFrame *dst, ধ্রুবক AVFrame *src)
{
    পূর্ণসংখ্যা ret = 0;

    যদি (dst == src)
        ফেরত AVERROR(EINVAL);

    যদি (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        যদি (   src->তথ্য[0] || src->তথ্য[1]
            || src->তথ্য[2] || src->তথ্য[3])
            ফেরত av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        যদি (ret < 0)
            যাও fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    যদি (ret < 0)
        যাও fail;

    av_frame_side_তথ্য_free(&dst->side_তথ্য, &dst->nb_side_তথ্য);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    যদি (ret < 0)
        যাও fail;

    /* replace the buffers */
    জন্য (পূর্ণসংখ্যা i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_বাফার_replace(&dst->buf[i], src->buf[i]);
        যদি (ret < 0)
            যাও fail;
    }

    যদি (src->extended_buf) {
        যদি (dst->nb_extended_buf != src->nb_extended_buf) {
            পূর্ণসংখ্যা nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            শূন্য *tmp;

            জন্য (পূর্ণসংখ্যা i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_বাফার_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   আকার(*dst->extended_buf));
            যদি (!tmp) {
                ret = AVERROR(ENOMEM);
                যাও fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * আকার(*dst->extended_buf));
        }

        জন্য (পূর্ণসংখ্যা i = 0; i < src->nb_extended_buf; i++) {
            ret = av_বাফার_replace(&dst->extended_buf[i], src->extended_buf[i]);
            যদি (ret < 0)
                যাও fail;
        }
    } অন্যথা যদি (dst->extended_buf) {
        জন্য (পূর্ণসংখ্যা i = 0; i < dst->nb_extended_buf; i++)
            av_বাফার_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_বাফার_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    যদি (ret < 0)
        যাও fail;

    যদি (dst->extended_তথ্য != dst->তথ্য)
        av_freep(&dst->extended_তথ্য);

    যদি (src->extended_তথ্য != src->তথ্য) {
        পূর্ণসংখ্যা ch = dst->ch_layout.nb_channels;

        যদি (ch <= 0 || ch > SIZE_MAX / আকার(*dst->extended_তথ্য)) {
            ret = AVERROR(EINVAL);
            যাও fail;
        }

        dst->extended_তথ্য = av_memdup(src->extended_তথ্য, আকার(*dst->extended_তথ্য) * ch);
        যদি (!dst->extended_তথ্য) {
            ret = AVERROR(ENOMEM);
            যাও fail;
        }
    } অন্যথা
        dst->extended_তথ্য = dst->তথ্য;

    memcpy(dst->তথ্য,     src->তথ্য,     আকার(src->তথ্য));
    memcpy(dst->linesize, src->linesize, আকার(src->linesize));

    ফেরত 0;

fail:
    av_frame_unref(dst);
    ফেরত ret;
}

AVFrame *av_frame_clone(ধ্রুবক AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    যদি (!ret)
        ফেরত ফাঁকা;

    যদি (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    ফেরত ret;
}

শূন্য av_frame_unref(AVFrame *frame)
{
    যদি (!frame)
        ফেরত;

    av_frame_side_তথ্য_free(&frame->side_তথ্য, &frame->nb_side_তথ্য);

    জন্য (পূর্ণসংখ্যা i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_বাফার_unref(&frame->buf[i]);
    জন্য (পূর্ণসংখ্যা i = 0; i < frame->nb_extended_buf; i++)
        av_বাফার_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_বাফার_unref(&frame->hw_frames_ctx);

    av_বাফার_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    যদি (frame->extended_তথ্য != frame->তথ্য)
        av_freep(&frame->extended_তথ্য);

    av_channel_layout_uninit(&frame->ch_layout);

    get_frame_defaults(frame);
}

শূন্য av_frame_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    *dst = *src;
    যদি (src->extended_তথ্য == src->তথ্য)
        dst->extended_তথ্য = dst->তথ্য;
    get_frame_defaults(src);
}

পূর্ণসংখ্যা av_frame_is_writable(AVFrame *frame)
{
    পূর্ণসংখ্যা ret = 1;

    /* assume non-refcounted frames are not writable */
    যদি (!frame->buf[0])
        ফেরত 0;

    জন্য (পূর্ণসংখ্যা i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        যদি (frame->buf[i])
            ret &= !!av_বাফার_is_writable(frame->buf[i]);
    জন্য (পূর্ণসংখ্যা i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_বাফার_is_writable(frame->extended_buf[i]);

    ফেরত ret;
}

পূর্ণসংখ্যা av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    পূর্ণসংখ্যা ret;

    যদি (av_frame_is_writable(frame))
        ফেরত 0;

    memset(&tmp, 0, আকার(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    যদি (ret < 0) {
        av_frame_unref(&tmp);
        ফেরত ret;
    }

    যদি (frame->hw_frames_ctx)
        ret = av_hwframe_get_বাফার(frame->hw_frames_ctx, &tmp, 0);
    অন্যথা
        ret = av_frame_get_বাফার(&tmp, 0);
    যদি (ret < 0)
        ফেরত ret;

    ret = av_frame_copy(&tmp, frame);
    যদি (ret < 0) {
        av_frame_unref(&tmp);
        ফেরত ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    যদি (ret < 0) {
        av_frame_unref(&tmp);
        ফেরত ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    যদি (tmp.তথ্য == tmp.extended_তথ্য)
        frame->extended_তথ্য = frame->তথ্য;

    ফেরত 0;
}

পূর্ণসংখ্যা av_frame_copy_props(AVFrame *dst, ধ্রুবক AVFrame *src)
{
    ফেরত frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_বাফার(ধ্রুবক AVFrame *frame, পূর্ণসংখ্যা plane)
{
    uintptr_t তথ্য;
    পূর্ণসংখ্যা planes;

    যদি (frame->nb_samples) {
        পূর্ণসংখ্যা channels = frame->ch_layout.nb_channels;
        যদি (!channels)
            ফেরত ফাঁকা;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } অন্যথা
        planes = 4;

    যদি (plane < 0 || plane >= planes || !frame->extended_তথ্য[plane])
        ফেরত ফাঁকা;
    তথ্য = (uintptr_t)frame->extended_তথ্য[plane];

    জন্য (পূর্ণসংখ্যা i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->তথ্য;

        যদি (তথ্য >= buf_begin && তথ্য < buf_begin + buf->আকার_2)
            ফেরত buf;
    }
    জন্য (পূর্ণসংখ্যা i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->তথ্য;

        যদি (তথ্য >= buf_begin && তথ্য < buf_begin + buf->আকার_2)
            ফেরত buf;
    }
    ফেরত ফাঁকা;
}

AVFrame_Side_তথ্য *av_frame_new_side_তথ্য_from_buf(AVFrame *frame,
                                                 গণনা AVFrame_Side_তথ্য_Type type,
                                                 AVBufferRef *buf)
{
    ফেরত
        ff_frame_side_তথ্য_add_from_buf(
            &frame->side_তথ্য, &frame->nb_side_তথ্য, type, buf);
}

AVFrame_Side_তথ্য *av_frame_new_side_তথ্য(AVFrame *frame,
                                        গণনা AVFrame_Side_তথ্য_Type type,
                                        size_t আকার_2)
{
    AVFrame_Side_তথ্য *ret;
    AVBufferRef *buf = av_বাফার_alloc(আকার_2);
    ret = av_frame_new_side_তথ্য_from_buf(frame, type, buf);
    যদি (!ret)
        av_বাফার_unref(&buf);
    ফেরত ret;
}

AVFrame_Side_তথ্য *av_frame_get_side_তথ্য(ধ্রুবক AVFrame *frame,
                                        গণনা AVFrame_Side_তথ্য_Type type)
{
    ফেরত (AVFrame_Side_তথ্য *)av_frame_side_তথ্য_get(
        frame->side_তথ্য, frame->nb_side_তথ্য,
        type
    );
}

স্থির পূর্ণসংখ্যা frame_copy_video(AVFrame *dst, ধ্রুবক AVFrame *src)
{
    পূর্ণসংখ্যা planes;

    যদি (dst->width  < src->width ||
        dst->height < src->height)
        ফেরত AVERROR(EINVAL);

    যদি (src->hw_frames_ctx || dst->hw_frames_ctx)
        ফেরত av_hwframe_transfer_তথ্য(dst, src, 0);

    planes = av_pix_fmt_গুনতি_planes(dst->format);
    জন্য (পূর্ণসংখ্যা i = 0; i < planes; i++)
        যদি (!dst->তথ্য[i] || !src->তথ্য[i])
            ফেরত AVERROR(EINVAL);

    av_image_copy2(dst->তথ্য, dst->linesize,
                   src->তথ্য, src->linesize,
                   dst->format, src->width, src->height);

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা frame_copy_audio(AVFrame *dst, ধ্রুবক AVFrame *src)
{
    পূর্ণসংখ্যা planar   = av_sample_fmt_is_planar(dst->format);
    পূর্ণসংখ্যা channels = dst->ch_layout.nb_channels;
    পূর্ণসংখ্যা planes   = planar ? channels : 1;

    যদি (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        ফেরত AVERROR(EINVAL);

    জন্য (পূর্ণসংখ্যা i = 0; i < planes; i++)
        যদি (!dst->extended_তথ্য[i] || !src->extended_তথ্য[i])
            ফেরত AVERROR(EINVAL);

    av_samples_copy(dst->extended_তথ্য, src->extended_তথ্য, 0, 0,
                    dst->nb_samples, channels, dst->format);

    ফেরত 0;
}

পূর্ণসংখ্যা av_frame_copy(AVFrame *dst, ধ্রুবক AVFrame *src)
{
    যদি (dst->format != src->format || dst->format < 0)
        ফেরত AVERROR(EINVAL);

    যদি (dst->width > 0 && dst->height > 0)
        ফেরত frame_copy_video(dst, src);
    অন্যথা যদি (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        ফেরত frame_copy_audio(dst, src);

    ফেরত AVERROR(EINVAL);
}

শূন্য av_frame_remove_side_তথ্য(AVFrame *frame, গণনা AVFrame_Side_তথ্য_Type type)
{
    av_frame_side_তথ্য_remove(&frame->side_তথ্য, &frame->nb_side_তথ্য, type);
}

স্থির পূর্ণসংখ্যা calc_cropping_offsets(size_t offsets[4], ধ্রুবক AVFrame *frame,
                                 ধ্রুবক AVPixFmtDescriptor *desc)
{
    জন্য (পূর্ণসংখ্যা i = 0; frame->তথ্য[i]; i++) {
        ধ্রুবক AVComponentDescriptor *comp = ফাঁকা;
        পূর্ণসংখ্যা shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        পূর্ণসংখ্যা shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        যদি (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            বিরতি;
        }

        /* find any component descriptor for this plane */
        জন্য (পূর্ণসংখ্যা j = 0; j < desc->nb_components; j++) {
            যদি (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                বিরতি;
            }
        }
        যদি (!comp)
            ফেরত AVERROR_BUG;

        offsets[i] = (frame->crop_শীর্ষ  >> shift_y) * frame->linesize[i] +
                     (frame->crop_বাম >> shift_x) * comp->step;
    }

    ফেরত 0;
}

পূর্ণসংখ্যা av_frame_apply_cropping(AVFrame *frame, পূর্ণসংখ্যা flags)
{
    ধ্রুবক AVPixFmtDescriptor *desc;
    size_t offsets[4];
    পূর্ণসংখ্যা ret;

    যদি (!(frame->width > 0 && frame->height > 0))
        ফেরত AVERROR(EINVAL);

    যদি (frame->crop_বাম >= INT_MAX - frame->crop_ডান        ||
        frame->crop_শীর্ষ  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_বাম + frame->crop_ডান) >= frame->width ||
        (frame->crop_শীর্ষ + frame->crop_bottom) >= frame->height)
        ফেরত AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    যদি (!desc)
        ফেরত AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    যদি (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_ডান;
        frame->height     -= frame->crop_bottom;
        frame->crop_ডান  = 0;
        frame->crop_bottom = 0;
        ফেরত 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    যদি (ret < 0)
        ফেরত ret;

    /* adjust the offsets to avoid breaking alignment */
    যদি (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        পূর্ণসংখ্যা log2_crop_align = frame->crop_বাম ? ff_ctz(frame->crop_বাম) : INT_MAX;
        পূর্ণসংখ্যা min_log2_align = INT_MAX;

        জন্য (পূর্ণসংখ্যা i = 0; frame->তথ্য[i]; i++) {
            পূর্ণসংখ্যা log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        যদি (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_বাম &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            যদি (ret < 0)
                ফেরত ret;
        }
    }

    জন্য (পূর্ণসংখ্যা i = 0; frame->তথ্য[i]; i++)
        frame->তথ্য[i] += offsets[i];

    frame->width      -= (frame->crop_বাম + frame->crop_ডান);
    frame->height     -= (frame->crop_শীর্ষ  + frame->crop_bottom);
    frame->crop_বাম   = 0;
    frame->crop_ডান  = 0;
    frame->crop_শীর্ষ    = 0;
    frame->crop_bottom = 0;

    ফেরত 0;
}
