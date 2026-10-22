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

ساكن فراغ get_چوکٺو_defaults(AVFrame *چوکٺو)
{
    memset(چوکٺو, 0, حجم(*چوکٺو));

    چوکٺو->pts                   =
    چوکٺو->pkt_dts               = AV_NOPTS_قدر;
    چوکٺو->بهترين_effort_timestamp = AV_NOPTS_قدر;
    چوکٺو->duration            = 0;
    چوکٺو->وقت_بنياد           = (AVRational){ 0, 1 };
    چوکٺو->sample_aspect_تناسب = (AVRational){ 0, 1 };
    چوکٺو->format              = -1; /* unknown */
    چوکٺو->extended_معلومات       = چوکٺو->معلومات;
    چوکٺو->color_primaries     = AVCOL_PRI_UNSPECIFIED;
    چوکٺو->color_trc           = AVCOL_TRC_UNSPECIFIED;
    چوکٺو->colorspace          = AVCOL_SPC_UNSPECIFIED;
    چوکٺو->color_range         = AVCOL_RANGE_UNSPECIFIED;
    چوکٺو->chroma_location     = AVCHROMA_LOC_UNSPECIFIED;
    چوکٺو->alpha_گهڻائي          = AVALPHA_گهڻائي_UNSPECIFIED;
    چوکٺو->flags               = 0;
}

AVFrame *av_چوکٺو_alloc(فراغ)
{
    AVFrame *چوکٺو = av_malloc(حجم(*چوکٺو));

    إذا (!چوکٺو)
        أرجع عدم;

    get_چوکٺو_defaults(چوکٺو);

    أرجع چوکٺو;
}

فراغ av_چوکٺو_free(AVFrame **چوکٺو)
{
    إذا (!چوکٺو || !*چوکٺو)
        أرجع;

    av_چوکٺو_unref(*چوکٺو);
    av_freep(چوکٺو);
}

#وصف_ڪريو ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

صحيح ff_چوکٺو_get_video_بفر(AVFrame *چوکٺو, صحيح align,
                              AVBufferRef *(*alloc)(فراغ *opaque, size_t سائيز),
                              فراغ *opaque)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(چوکٺو->format);
    صحيح ret, padded_اوچائي;
    صحيح plane_padding;
    ptrdiff_t linesizes[4];
    size_t ڪل_سائيز, sizes[4];

    إذا (!desc)
        أرجع AVERROR(EINVAL);

    إذا ((ret = av_image_check_سائيز(چوکٺو->ويڪر, چوکٺو->اوچائي, 0, عدم)) < 0)
        أرجع ret;

    إذا (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    إذا (!چوکٺو->linesize[0]) {
        لكل (صحيح i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(چوکٺو->linesize, چوکٺو->format,
                                          FFALIGN(چوکٺو->ويڪر, i));
            إذا (ret < 0)
                أرجع ret;
            إذا (!(چوکٺو->linesize[0] & (align-1)))
                اكسر;
        }

        لكل (صحيح i = 0; i < 4 && چوکٺو->linesize[i]; i++)
            چوکٺو->linesize[i] = FFALIGN(چوکٺو->linesize[i], align);
    }

    لكل (صحيح i = 0; i < 4; i++)
        linesizes[i] = چوکٺو->linesize[i];

    padded_اوچائي = FFALIGN(چوکٺو->اوچائي, 32);
    إذا ((ret = av_image_fill_plane_sizes(sizes, چوکٺو->format,
                                         padded_اوچائي, linesizes)) < 0)
        أرجع ret;

    ڪل_سائيز = 4 * plane_padding + 4 * align;
    لكل (صحيح i = 0; i < 4; i++) {
        إذا (sizes[i] > SIZE_MAX - ڪل_سائيز)
            أرجع AVERROR(EINVAL);
        ڪل_سائيز += sizes[i];
    }

    چوکٺو->buf[0] = alloc ? alloc(opaque, ڪل_سائيز) : av_بفر_alloc(ڪل_سائيز);
    إذا (!چوکٺو->buf[0]) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    إذا ((ret = av_image_fill_اشارا(چوکٺو->معلومات, چوکٺو->format, padded_اوچائي,
                                      چوکٺو->buf[0]->معلومات, چوکٺو->linesize)) < 0)
        اذهب fail;

    لكل (صحيح i = 1; i < 4; i++) {
        إذا (چوکٺو->معلومات[i])
            چوکٺو->معلومات[i] += i * plane_padding;
        چوکٺو->معلومات[i] = (uint8_t *)FFALIGN((uintptr_t)چوکٺو->معلومات[i], align);
    }

    چوکٺو->extended_معلومات = چوکٺو->معلومات;

    أرجع 0;
fail:
    av_چوکٺو_unref(چوکٺو);
    أرجع ret;
}

ساكن صحيح get_audio_بفر(AVFrame *چوکٺو, صحيح align)
{
    صحيح planar   = av_sample_fmt_is_planar(چوکٺو->format);
    صحيح channels, planes;
    size_t سائيز;
    صحيح ret;

    channels = چوکٺو->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    إذا (!چوکٺو->linesize[0]) {
        ret = av_samples_get_بفر_سائيز(&چوکٺو->linesize[0], channels,
                                         چوکٺو->nb_samples, چوکٺو->format,
                                         align);
        إذا (ret < 0)
            أرجع ret;
    }

    إذا (align <= 0)
        align = ALIGN;

    إذا (planes > AV_انگ_معلومات_اشارا) {
        چوکٺو->extended_معلومات = av_calloc(planes,
                                          حجم(*چوکٺو->extended_معلومات));
        چوکٺو->extended_buf  = av_calloc(planes - AV_انگ_معلومات_اشارا,
                                          حجم(*چوکٺو->extended_buf));
        إذا (!چوکٺو->extended_معلومات || !چوکٺو->extended_buf) {
            av_freep(&چوکٺو->extended_معلومات);
            av_freep(&چوکٺو->extended_buf);
            أرجع AVERROR(ENOMEM);
        }
        چوکٺو->nb_extended_buf = planes - AV_انگ_معلومات_اشارا;
    } وإلا
        چوکٺو->extended_معلومات = چوکٺو->معلومات;

    إذا (چوکٺو->linesize[0] > SIZE_MAX - align)
        أرجع AVERROR(EINVAL);
    سائيز = چوکٺو->linesize[0] + (size_t)align;

    لكل (صحيح i = 0; i < FFMIN(planes, AV_انگ_معلومات_اشارا); i++) {
        چوکٺو->buf[i] = av_بفر_alloc(سائيز);
        إذا (!چوکٺو->buf[i]) {
            av_چوکٺو_unref(چوکٺو);
            أرجع AVERROR(ENOMEM);
        }
        چوکٺو->extended_معلومات[i] = چوکٺو->معلومات[i] =
            (uint8_t *)FFALIGN((uintptr_t)چوکٺو->buf[i]->معلومات, align);
    }
    لكل (صحيح i = 0; i < planes - AV_انگ_معلومات_اشارا; i++) {
        چوکٺو->extended_buf[i] = av_بفر_alloc(سائيز);
        إذا (!چوکٺو->extended_buf[i]) {
            av_چوکٺو_unref(چوکٺو);
            أرجع AVERROR(ENOMEM);
        }
        چوکٺو->extended_معلومات[i + AV_انگ_معلومات_اشارا] =
            (uint8_t *)FFALIGN((uintptr_t)چوکٺو->extended_buf[i]->معلومات, align);
    }
    أرجع 0;

}

صحيح av_چوکٺو_get_بفر(AVFrame *چوکٺو, صحيح align)
{
    إذا (چوکٺو->format < 0)
        أرجع AVERROR(EINVAL);

    إذا (چوکٺو->ويڪر > 0 && چوکٺو->اوچائي > 0)
        أرجع ff_چوکٺو_get_video_بفر(چوکٺو, align, عدم, عدم);
    وإلا إذا (چوکٺو->nb_samples > 0 &&
             (av_channel_layout_check(&چوکٺو->ch_layout)))
        أرجع get_audio_بفر(چوکٺو, align);

    أرجع AVERROR(EINVAL);
}

ساكن صحيح چوکٺو_copy_props(AVFrame *dst, ثابت AVFrame *src, صحيح force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_تناسب    = src->sample_aspect_تناسب;
    dst->crop_چوٽي               = src->crop_چوٽي;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_کاٻو              = src->crop_کاٻو;
    dst->crop_ساڄو             = src->crop_ساڄو;
    dst->pts                    = src->pts;
    dst->duration               = src->duration;
    dst->repeat_pict            = src->repeat_pict;
    dst->sample_شرح            = src->sample_شرح;
    dst->opaque                 = src->opaque;
    dst->pkt_dts                = src->pkt_dts;
    dst->وقت_بنياد              = src->وقت_بنياد;
    dst->quality                = src->quality;
    dst->بهترين_effort_timestamp  = src->بهترين_effort_timestamp;
    dst->flags                  = src->flags;
    dst->decode_error_flags     = src->decode_error_flags;
    dst->color_primaries        = src->color_primaries;
    dst->color_trc              = src->color_trc;
    dst->colorspace             = src->colorspace;
    dst->color_range            = src->color_range;
    dst->chroma_location        = src->chroma_location;
    dst->alpha_گهڻائي             = src->alpha_گهڻائي;

    av_dict_copy(&dst->metadata, src->metadata, 0);

    لكل (صحيح i = 0; i < src->nb_side_معلومات; i++) {
        ثابت AVFrame_Side_معلومات *sd_src = src->side_معلومات[i];
        AVFrame_Side_معلومات *sd_dst;
        إذا (   sd_src->type == AV_چوکٺو_معلومات_PANSCAN
            && (src->ويڪر != dst->ويڪر || src->اوچائي != dst->اوچائي))
            استمر;
        إذا (force_copy) {
            sd_dst = av_چوکٺو_new_side_معلومات(dst, sd_src->type,
                                            sd_src->سائيز);
            إذا (!sd_dst) {
                av_چوکٺو_side_معلومات_free(&dst->side_معلومات, &dst->nb_side_معلومات);
                أرجع AVERROR(ENOMEM);
            }
            يادگيري_نقل(sd_dst->معلومات, sd_src->معلومات, sd_src->سائيز);
        } وإلا {
            AVBufferRef *ref = av_بفر_ref(sd_src->buf);
            sd_dst = av_چوکٺو_new_side_معلومات_from_buf(dst, sd_src->type, ref);
            إذا (!sd_dst) {
                av_بفر_unref(&ref);
                av_چوکٺو_side_معلومات_free(&dst->side_معلومات, &dst->nb_side_معلومات);
                أرجع AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->ذاتي_ref, src->ذاتي_ref);
    أرجع av_بفر_replace(&dst->opaque_ref, src->opaque_ref);
}

صحيح av_چوکٺو_ref(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح ret = 0;

    av_assert1(dst->ويڪر == 0 && dst->اوچائي == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ترتيب == AV_CHANNEL_ترتيب_UNSPEC);

    dst->format         = src->format;
    dst->ويڪر          = src->ويڪر;
    dst->اوچائي         = src->اوچائي;
    dst->nb_samples     = src->nb_samples;

    ret = چوکٺو_copy_props(dst, src, 0);
    إذا (ret < 0)
        اذهب fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    إذا (ret < 0)
        اذهب fail;

    /* duplicate the frame data if it's not refcounted */
    إذا (!src->buf[0]) {
        ret = av_چوکٺو_get_بفر(dst, 0);
        إذا (ret < 0)
            اذهب fail;

        ret = av_چوکٺو_copy(dst, src);
        إذا (ret < 0)
            اذهب fail;

        أرجع 0;
    }

    /* ref the buffers */
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        إذا (!src->buf[i])
            استمر;
        dst->buf[i] = av_بفر_ref(src->buf[i]);
        إذا (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    }

    إذا (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      حجم(*dst->extended_buf));
        إذا (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        لكل (صحيح i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_بفر_ref(src->extended_buf[i]);
            إذا (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                اذهب fail;
            }
        }
    }

    إذا (src->hw_چوکٺا_ctx) {
        dst->hw_چوکٺا_ctx = av_بفر_ref(src->hw_چوکٺا_ctx);
        إذا (!dst->hw_چوکٺا_ctx) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    }

    /* duplicate extended data */
    إذا (src->extended_معلومات != src->معلومات) {
        صحيح ch = dst->ch_layout.nb_channels;

        إذا (ch <= 0 || ch > SIZE_MAX / حجم(*dst->extended_معلومات)) {
            ret = AVERROR(EINVAL);
            اذهب fail;
        }

        dst->extended_معلومات = av_memdup(src->extended_معلومات, حجم(*dst->extended_معلومات) * ch);
        إذا (!dst->extended_معلومات) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    } وإلا
        dst->extended_معلومات = dst->معلومات;

    يادگيري_نقل(dst->معلومات,     src->معلومات,     حجم(src->معلومات));
    يادگيري_نقل(dst->linesize, src->linesize, حجم(src->linesize));

    أرجع 0;

fail:
    av_چوکٺو_unref(dst);
    أرجع ret;
}

صحيح av_چوکٺو_replace(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح ret = 0;

    إذا (dst == src)
        أرجع AVERROR(EINVAL);

    إذا (!src->buf[0]) {
        av_چوکٺو_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        إذا (   src->معلومات[0] || src->معلومات[1]
            || src->معلومات[2] || src->معلومات[3])
            أرجع av_چوکٺو_ref(dst, src);

        ret = چوکٺو_copy_props(dst, src, 0);
        إذا (ret < 0)
            اذهب fail;
    }

    dst->format         = src->format;
    dst->ويڪر          = src->ويڪر;
    dst->اوچائي         = src->اوچائي;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    إذا (ret < 0)
        اذهب fail;

    av_چوکٺو_side_معلومات_free(&dst->side_معلومات, &dst->nb_side_معلومات);
    av_dict_free(&dst->metadata);
    ret = چوکٺو_copy_props(dst, src, 0);
    إذا (ret < 0)
        اذهب fail;

    /* replace the buffers */
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_بفر_replace(&dst->buf[i], src->buf[i]);
        إذا (ret < 0)
            اذهب fail;
    }

    إذا (src->extended_buf) {
        إذا (dst->nb_extended_buf != src->nb_extended_buf) {
            صحيح nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            فراغ *tmp;

            لكل (صحيح i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_بفر_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   حجم(*dst->extended_buf));
            إذا (!tmp) {
                ret = AVERROR(ENOMEM);
                اذهب fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * حجم(*dst->extended_buf));
        }

        لكل (صحيح i = 0; i < src->nb_extended_buf; i++) {
            ret = av_بفر_replace(&dst->extended_buf[i], src->extended_buf[i]);
            إذا (ret < 0)
                اذهب fail;
        }
    } وإلا إذا (dst->extended_buf) {
        لكل (صحيح i = 0; i < dst->nb_extended_buf; i++)
            av_بفر_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_بفر_replace(&dst->hw_چوکٺا_ctx, src->hw_چوکٺا_ctx);
    إذا (ret < 0)
        اذهب fail;

    إذا (dst->extended_معلومات != dst->معلومات)
        av_freep(&dst->extended_معلومات);

    إذا (src->extended_معلومات != src->معلومات) {
        صحيح ch = dst->ch_layout.nb_channels;

        إذا (ch <= 0 || ch > SIZE_MAX / حجم(*dst->extended_معلومات)) {
            ret = AVERROR(EINVAL);
            اذهب fail;
        }

        dst->extended_معلومات = av_memdup(src->extended_معلومات, حجم(*dst->extended_معلومات) * ch);
        إذا (!dst->extended_معلومات) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    } وإلا
        dst->extended_معلومات = dst->معلومات;

    يادگيري_نقل(dst->معلومات,     src->معلومات,     حجم(src->معلومات));
    يادگيري_نقل(dst->linesize, src->linesize, حجم(src->linesize));

    أرجع 0;

fail:
    av_چوکٺو_unref(dst);
    أرجع ret;
}

AVFrame *av_چوکٺو_clone(ثابت AVFrame *src)
{
    AVFrame *ret = av_چوکٺو_alloc();

    إذا (!ret)
        أرجع عدم;

    إذا (av_چوکٺو_ref(ret, src) < 0)
        av_چوکٺو_free(&ret);

    أرجع ret;
}

فراغ av_چوکٺو_unref(AVFrame *چوکٺو)
{
    إذا (!چوکٺو)
        أرجع;

    av_چوکٺو_side_معلومات_free(&چوکٺو->side_معلومات, &چوکٺو->nb_side_معلومات);

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(چوکٺو->buf); i++)
        av_بفر_unref(&چوکٺو->buf[i]);
    لكل (صحيح i = 0; i < چوکٺو->nb_extended_buf; i++)
        av_بفر_unref(&چوکٺو->extended_buf[i]);
    av_freep(&چوکٺو->extended_buf);
    av_dict_free(&چوکٺو->metadata);

    av_بفر_unref(&چوکٺو->hw_چوکٺا_ctx);

    av_بفر_unref(&چوکٺو->opaque_ref);
    av_refstruct_unref(&چوکٺو->ذاتي_ref);

    إذا (چوکٺو->extended_معلومات != چوکٺو->معلومات)
        av_freep(&چوکٺو->extended_معلومات);

    av_channel_layout_uninit(&چوکٺو->ch_layout);

    get_چوکٺو_defaults(چوکٺو);
}

فراغ av_چوکٺو_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->ويڪر == 0 && dst->اوچائي == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ترتيب == AV_CHANNEL_ترتيب_UNSPEC);

    *dst = *src;
    إذا (src->extended_معلومات == src->معلومات)
        dst->extended_معلومات = dst->معلومات;
    get_چوکٺو_defaults(src);
}

صحيح av_چوکٺو_is_writable(AVFrame *چوکٺو)
{
    صحيح ret = 1;

    /* assume non-refcounted frames are not writable */
    إذا (!چوکٺو->buf[0])
        أرجع 0;

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(چوکٺو->buf); i++)
        إذا (چوکٺو->buf[i])
            ret &= !!av_بفر_is_writable(چوکٺو->buf[i]);
    لكل (صحيح i = 0; i < چوکٺو->nb_extended_buf; i++)
        ret &= !!av_بفر_is_writable(چوکٺو->extended_buf[i]);

    أرجع ret;
}

صحيح av_چوکٺو_make_writable(AVFrame *چوکٺو)
{
    AVFrame tmp;
    صحيح ret;

    إذا (av_چوکٺو_is_writable(چوکٺو))
        أرجع 0;

    memset(&tmp, 0, حجم(tmp));
    tmp.format         = چوکٺو->format;
    tmp.ويڪر          = چوکٺو->ويڪر;
    tmp.اوچائي         = چوکٺو->اوچائي;
    tmp.nb_samples     = چوکٺو->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &چوکٺو->ch_layout);
    إذا (ret < 0) {
        av_چوکٺو_unref(&tmp);
        أرجع ret;
    }

    إذا (چوکٺو->hw_چوکٺا_ctx)
        ret = av_hwframe_get_بفر(چوکٺو->hw_چوکٺا_ctx, &tmp, 0);
    وإلا
        ret = av_چوکٺو_get_بفر(&tmp, 0);
    إذا (ret < 0)
        أرجع ret;

    ret = av_چوکٺو_copy(&tmp, چوکٺو);
    إذا (ret < 0) {
        av_چوکٺو_unref(&tmp);
        أرجع ret;
    }

    ret = av_چوکٺو_copy_props(&tmp, چوکٺو);
    إذا (ret < 0) {
        av_چوکٺو_unref(&tmp);
        أرجع ret;
    }

    av_چوکٺو_unref(چوکٺو);

    *چوکٺو = tmp;
    إذا (tmp.معلومات == tmp.extended_معلومات)
        چوکٺو->extended_معلومات = چوکٺو->معلومات;

    أرجع 0;
}

صحيح av_چوکٺو_copy_props(AVFrame *dst, ثابت AVFrame *src)
{
    أرجع چوکٺو_copy_props(dst, src, 1);
}

AVBufferRef *av_چوکٺو_get_plane_بفر(ثابت AVFrame *چوکٺو, صحيح plane)
{
    uintptr_t معلومات;
    صحيح planes;

    إذا (چوکٺو->nb_samples) {
        صحيح channels = چوکٺو->ch_layout.nb_channels;
        إذا (!channels)
            أرجع عدم;
        planes = av_sample_fmt_is_planar(چوکٺو->format) ? channels : 1;
    } وإلا
        planes = 4;

    إذا (plane < 0 || plane >= planes || !چوکٺو->extended_معلومات[plane])
        أرجع عدم;
    معلومات = (uintptr_t)چوکٺو->extended_معلومات[plane];

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(چوکٺو->buf) && چوکٺو->buf[i]; i++) {
        AVBufferRef *buf = چوکٺو->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->معلومات;

        إذا (معلومات >= buf_begin && معلومات < buf_begin + buf->سائيز)
            أرجع buf;
    }
    لكل (صحيح i = 0; i < چوکٺو->nb_extended_buf; i++) {
        AVBufferRef *buf = چوکٺو->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->معلومات;

        إذا (معلومات >= buf_begin && معلومات < buf_begin + buf->سائيز)
            أرجع buf;
    }
    أرجع عدم;
}

AVFrame_Side_معلومات *av_چوکٺو_new_side_معلومات_from_buf(AVFrame *چوکٺو,
                                                 تعداد AVFrame_Side_معلومات_Type type,
                                                 AVBufferRef *buf)
{
    أرجع
        ff_چوکٺو_side_معلومات_جوڙيو_from_buf(
            &چوکٺو->side_معلومات, &چوکٺو->nb_side_معلومات, type, buf);
}

AVFrame_Side_معلومات *av_چوکٺو_new_side_معلومات(AVFrame *چوکٺو,
                                        تعداد AVFrame_Side_معلومات_Type type,
                                        size_t سائيز)
{
    AVFrame_Side_معلومات *ret;
    AVBufferRef *buf = av_بفر_alloc(سائيز);
    ret = av_چوکٺو_new_side_معلومات_from_buf(چوکٺو, type, buf);
    إذا (!ret)
        av_بفر_unref(&buf);
    أرجع ret;
}

AVFrame_Side_معلومات *av_چوکٺو_get_side_معلومات(ثابت AVFrame *چوکٺو,
                                        تعداد AVFrame_Side_معلومات_Type type)
{
    أرجع (AVFrame_Side_معلومات *)av_چوکٺو_side_معلومات_get(
        چوکٺو->side_معلومات, چوکٺو->nb_side_معلومات,
        type
    );
}

ساكن صحيح چوکٺو_copy_video(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح planes;

    إذا (dst->ويڪر  < src->ويڪر ||
        dst->اوچائي < src->اوچائي)
        أرجع AVERROR(EINVAL);

    إذا (src->hw_چوکٺا_ctx || dst->hw_چوکٺا_ctx)
        أرجع av_hwframe_transfer_معلومات(dst, src, 0);

    planes = av_pix_fmt_ڳڻپ_planes(dst->format);
    لكل (صحيح i = 0; i < planes; i++)
        إذا (!dst->معلومات[i] || !src->معلومات[i])
            أرجع AVERROR(EINVAL);

    av_image_copy2(dst->معلومات, dst->linesize,
                   src->معلومات, src->linesize,
                   dst->format, src->ويڪر, src->اوچائي);

    أرجع 0;
}

ساكن صحيح چوکٺو_copy_audio(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح planar   = av_sample_fmt_is_planar(dst->format);
    صحيح channels = dst->ch_layout.nb_channels;
    صحيح planes   = planar ? channels : 1;

    إذا (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        أرجع AVERROR(EINVAL);

    لكل (صحيح i = 0; i < planes; i++)
        إذا (!dst->extended_معلومات[i] || !src->extended_معلومات[i])
            أرجع AVERROR(EINVAL);

    av_samples_copy(dst->extended_معلومات, src->extended_معلومات, 0, 0,
                    dst->nb_samples, channels, dst->format);

    أرجع 0;
}

صحيح av_چوکٺو_copy(AVFrame *dst, ثابت AVFrame *src)
{
    إذا (dst->format != src->format || dst->format < 0)
        أرجع AVERROR(EINVAL);

    إذا (dst->ويڪر > 0 && dst->اوچائي > 0)
        أرجع چوکٺو_copy_video(dst, src);
    وإلا إذا (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        أرجع چوکٺو_copy_audio(dst, src);

    أرجع AVERROR(EINVAL);
}

فراغ av_چوکٺو_remove_side_معلومات(AVFrame *چوکٺو, تعداد AVFrame_Side_معلومات_Type type)
{
    av_چوکٺو_side_معلومات_remove(&چوکٺو->side_معلومات, &چوکٺو->nb_side_معلومات, type);
}

ساكن صحيح calc_cropping_offsets(size_t offsets[4], ثابت AVFrame *چوکٺو,
                                 ثابت AVPixFmtDescriptor *desc)
{
    لكل (صحيح i = 0; چوکٺو->معلومات[i]; i++) {
        ثابت AVComponentDescriptor *comp = عدم;
        صحيح سرڪايو_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        صحيح سرڪايو_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        إذا (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            اكسر;
        }

        /* find any component descriptor for this plane */
        لكل (صحيح j = 0; j < desc->nb_components; j++) {
            إذا (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                اكسر;
            }
        }
        إذا (!comp)
            أرجع AVERROR_BUG;

        offsets[i] = (چوکٺو->crop_چوٽي  >> سرڪايو_y) * چوکٺو->linesize[i] +
                     (چوکٺو->crop_کاٻو >> سرڪايو_x) * comp->قدم;
    }

    أرجع 0;
}

صحيح av_چوکٺو_apply_cropping(AVFrame *چوکٺو, صحيح flags)
{
    ثابت AVPixFmtDescriptor *desc;
    size_t offsets[4];
    صحيح ret;

    إذا (!(چوکٺو->ويڪر > 0 && چوکٺو->اوچائي > 0))
        أرجع AVERROR(EINVAL);

    إذا (چوکٺو->crop_کاٻو >= وڌ_کان_وڌ_عدد - چوکٺو->crop_ساڄو        ||
        چوکٺو->crop_چوٽي  >= وڌ_کان_وڌ_عدد - چوکٺو->crop_bottom       ||
        (چوکٺو->crop_کاٻو + چوکٺو->crop_ساڄو) >= چوکٺو->ويڪر ||
        (چوکٺو->crop_چوٽي + چوکٺو->crop_bottom) >= چوکٺو->اوچائي)
        أرجع AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(چوکٺو->format);
    إذا (!desc)
        أرجع AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    إذا (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        چوکٺو->ويڪر      -= چوکٺو->crop_ساڄو;
        چوکٺو->اوچائي     -= چوکٺو->crop_bottom;
        چوکٺو->crop_ساڄو  = 0;
        چوکٺو->crop_bottom = 0;
        أرجع 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, چوکٺو, desc);
    إذا (ret < 0)
        أرجع ret;

    /* adjust the offsets to avoid breaking alignment */
    إذا (!(flags & AV_چوکٺو_CROP_UNALIGNED)) {
        صحيح log2_crop_align = چوکٺو->crop_کاٻو ? ff_ctz(چوکٺو->crop_کاٻو) : وڌ_کان_وڌ_عدد;
        صحيح min_log2_align = وڌ_کان_وڌ_عدد;

        لكل (صحيح i = 0; چوکٺو->معلومات[i]; i++) {
            صحيح log2_align = offsets[i] ? ff_ctz(offsets[i]) : وڌ_کان_وڌ_عدد;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        إذا (min_log2_align < 5 && log2_crop_align != وڌ_کان_وڌ_عدد) {
            چوکٺو->crop_کاٻو &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, چوکٺو, desc);
            إذا (ret < 0)
                أرجع ret;
        }
    }

    لكل (صحيح i = 0; چوکٺو->معلومات[i]; i++)
        چوکٺو->معلومات[i] += offsets[i];

    چوکٺو->ويڪر      -= (چوکٺو->crop_کاٻو + چوکٺو->crop_ساڄو);
    چوکٺو->اوچائي     -= (چوکٺو->crop_چوٽي  + چوکٺو->crop_bottom);
    چوکٺو->crop_کاٻو   = 0;
    چوکٺو->crop_ساڄو  = 0;
    چوکٺو->crop_چوٽي    = 0;
    چوکٺو->crop_bottom = 0;

    أرجع 0;
}
