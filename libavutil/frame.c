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

ساكن فراغ get_چوکاټ_defaults(AVFrame *چوکاټ)
{
    memset(چوکاټ, 0, حجم(*چوکاټ));

    چوکاټ->pts                   =
    چوکاټ->pkt_dts               = AV_NOPTS_ارزښت;
    چوکاټ->غوره_effort_timestamp = AV_NOPTS_ارزښت;
    چوکاټ->duration            = 0;
    چوکاټ->وخت_بنسټ           = (AVRational){ 0, 1 };
    چوکاټ->sample_aspect_نسبت = (AVRational){ 0, 1 };
    چوکاټ->format              = -1; /* unknown */
    چوکاټ->extended_معلومات       = چوکاټ->معلومات;
    چوکاټ->color_primaries     = AVCOL_PRI_UNSPECIFIED;
    چوکاټ->color_trc           = AVCOL_TRC_UNSPECIFIED;
    چوکاټ->colorspace          = AVCOL_SPC_UNSPECIFIED;
    چوکاټ->color_range         = AVCOL_RANGE_UNSPECIFIED;
    چوکاټ->chroma_location     = AVCHROMA_LOC_UNSPECIFIED;
    چوکاټ->alpha_ډېرپېښ          = AVALPHA_ډېرپېښ_UNSPECIFIED;
    چوکاټ->flags               = 0;
}

AVFrame *av_چوکاټ_alloc(فراغ)
{
    AVFrame *چوکاټ = av_malloc(حجم(*چوکاټ));

    إذا (!چوکاټ)
        أرجع عدم;

    get_چوکاټ_defaults(چوکاټ);

    أرجع چوکاټ;
}

فراغ av_چوکاټ_free(AVFrame **چوکاټ)
{
    إذا (!چوکاټ || !*چوکاټ)
        أرجع;

    av_چوکاټ_unref(*چوکاټ);
    av_freep(چوکاټ);
}

#تعریف_کړه ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

صحيح ff_چوکاټ_get_video_بفر(AVFrame *چوکاټ, صحيح align,
                              AVBufferRef *(*alloc)(فراغ *opaque, size_t اندازه),
                              فراغ *opaque)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(چوکاټ->format);
    صحيح ret, padded_لوړوالی;
    صحيح plane_padding;
    ptrdiff_t linesizes[4];
    size_t ټول_اندازه, sizes[4];

    إذا (!desc)
        أرجع AVERROR(EINVAL);

    إذا ((ret = av_image_check_اندازه(چوکاټ->پلنوالی, چوکاټ->لوړوالی, 0, عدم)) < 0)
        أرجع ret;

    إذا (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    إذا (!چوکاټ->linesize[0]) {
        لكل (صحيح i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(چوکاټ->linesize, چوکاټ->format,
                                          FFALIGN(چوکاټ->پلنوالی, i));
            إذا (ret < 0)
                أرجع ret;
            إذا (!(چوکاټ->linesize[0] & (align-1)))
                اكسر;
        }

        لكل (صحيح i = 0; i < 4 && چوکاټ->linesize[i]; i++)
            چوکاټ->linesize[i] = FFALIGN(چوکاټ->linesize[i], align);
    }

    لكل (صحيح i = 0; i < 4; i++)
        linesizes[i] = چوکاټ->linesize[i];

    padded_لوړوالی = FFALIGN(چوکاټ->لوړوالی, 32);
    إذا ((ret = av_image_fill_plane_sizes(sizes, چوکاټ->format,
                                         padded_لوړوالی, linesizes)) < 0)
        أرجع ret;

    ټول_اندازه = 4 * plane_padding + 4 * align;
    لكل (صحيح i = 0; i < 4; i++) {
        إذا (sizes[i] > SIZE_MAX - ټول_اندازه)
            أرجع AVERROR(EINVAL);
        ټول_اندازه += sizes[i];
    }

    چوکاټ->buf[0] = alloc ? alloc(opaque, ټول_اندازه) : av_بفر_alloc(ټول_اندازه);
    إذا (!چوکاټ->buf[0]) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    إذا ((ret = av_image_fill_اشارې(چوکاټ->معلومات, چوکاټ->format, padded_لوړوالی,
                                      چوکاټ->buf[0]->معلومات, چوکاټ->linesize)) < 0)
        اذهب fail;

    لكل (صحيح i = 1; i < 4; i++) {
        إذا (چوکاټ->معلومات[i])
            چوکاټ->معلومات[i] += i * plane_padding;
        چوکاټ->معلومات[i] = (uint8_t *)FFALIGN((uintptr_t)چوکاټ->معلومات[i], align);
    }

    چوکاټ->extended_معلومات = چوکاټ->معلومات;

    أرجع 0;
fail:
    av_چوکاټ_unref(چوکاټ);
    أرجع ret;
}

ساكن صحيح get_audio_بفر(AVFrame *چوکاټ, صحيح align)
{
    صحيح planar   = av_sample_fmt_is_planar(چوکاټ->format);
    صحيح channels, planes;
    size_t اندازه;
    صحيح ret;

    channels = چوکاټ->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    إذا (!چوکاټ->linesize[0]) {
        ret = av_samples_get_بفر_اندازه(&چوکاټ->linesize[0], channels,
                                         چوکاټ->nb_samples, چوکاټ->format,
                                         align);
        إذا (ret < 0)
            أرجع ret;
    }

    إذا (align <= 0)
        align = ALIGN;

    إذا (planes > AV_عدد_معلومات_اشارې) {
        چوکاټ->extended_معلومات = av_calloc(planes,
                                          حجم(*چوکاټ->extended_معلومات));
        چوکاټ->extended_buf  = av_calloc(planes - AV_عدد_معلومات_اشارې,
                                          حجم(*چوکاټ->extended_buf));
        إذا (!چوکاټ->extended_معلومات || !چوکاټ->extended_buf) {
            av_freep(&چوکاټ->extended_معلومات);
            av_freep(&چوکاټ->extended_buf);
            أرجع AVERROR(ENOMEM);
        }
        چوکاټ->nb_extended_buf = planes - AV_عدد_معلومات_اشارې;
    } وإلا
        چوکاټ->extended_معلومات = چوکاټ->معلومات;

    إذا (چوکاټ->linesize[0] > SIZE_MAX - align)
        أرجع AVERROR(EINVAL);
    اندازه = چوکاټ->linesize[0] + (size_t)align;

    لكل (صحيح i = 0; i < FFMIN(planes, AV_عدد_معلومات_اشارې); i++) {
        چوکاټ->buf[i] = av_بفر_alloc(اندازه);
        إذا (!چوکاټ->buf[i]) {
            av_چوکاټ_unref(چوکاټ);
            أرجع AVERROR(ENOMEM);
        }
        چوکاټ->extended_معلومات[i] = چوکاټ->معلومات[i] =
            (uint8_t *)FFALIGN((uintptr_t)چوکاټ->buf[i]->معلومات, align);
    }
    لكل (صحيح i = 0; i < planes - AV_عدد_معلومات_اشارې; i++) {
        چوکاټ->extended_buf[i] = av_بفر_alloc(اندازه);
        إذا (!چوکاټ->extended_buf[i]) {
            av_چوکاټ_unref(چوکاټ);
            أرجع AVERROR(ENOMEM);
        }
        چوکاټ->extended_معلومات[i + AV_عدد_معلومات_اشارې] =
            (uint8_t *)FFALIGN((uintptr_t)چوکاټ->extended_buf[i]->معلومات, align);
    }
    أرجع 0;

}

صحيح av_چوکاټ_get_بفر(AVFrame *چوکاټ, صحيح align)
{
    إذا (چوکاټ->format < 0)
        أرجع AVERROR(EINVAL);

    إذا (چوکاټ->پلنوالی > 0 && چوکاټ->لوړوالی > 0)
        أرجع ff_چوکاټ_get_video_بفر(چوکاټ, align, عدم, عدم);
    وإلا إذا (چوکاټ->nb_samples > 0 &&
             (av_channel_layout_check(&چوکاټ->ch_layout)))
        أرجع get_audio_بفر(چوکاټ, align);

    أرجع AVERROR(EINVAL);
}

ساكن صحيح چوکاټ_copy_props(AVFrame *dst, ثابت AVFrame *src, صحيح force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_نسبت    = src->sample_aspect_نسبت;
    dst->crop_سر               = src->crop_سر;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_کیڼ              = src->crop_کیڼ;
    dst->crop_ښی             = src->crop_ښی;
    dst->pts                    = src->pts;
    dst->duration               = src->duration;
    dst->repeat_pict            = src->repeat_pict;
    dst->sample_شرح            = src->sample_شرح;
    dst->opaque                 = src->opaque;
    dst->pkt_dts                = src->pkt_dts;
    dst->وخت_بنسټ              = src->وخت_بنسټ;
    dst->quality                = src->quality;
    dst->غوره_effort_timestamp  = src->غوره_effort_timestamp;
    dst->flags                  = src->flags;
    dst->decode_error_flags     = src->decode_error_flags;
    dst->color_primaries        = src->color_primaries;
    dst->color_trc              = src->color_trc;
    dst->colorspace             = src->colorspace;
    dst->color_range            = src->color_range;
    dst->chroma_location        = src->chroma_location;
    dst->alpha_ډېرپېښ             = src->alpha_ډېرپېښ;

    av_dict_copy(&dst->metadata, src->metadata, 0);

    لكل (صحيح i = 0; i < src->nb_side_معلومات; i++) {
        ثابت AVFrame_Side_معلومات *sd_src = src->side_معلومات[i];
        AVFrame_Side_معلومات *sd_dst;
        إذا (   sd_src->type == AV_چوکاټ_معلومات_PANSCAN
            && (src->پلنوالی != dst->پلنوالی || src->لوړوالی != dst->لوړوالی))
            استمر;
        إذا (force_copy) {
            sd_dst = av_چوکاټ_new_side_معلومات(dst, sd_src->type,
                                            sd_src->اندازه);
            إذا (!sd_dst) {
                av_چوکاټ_side_معلومات_free(&dst->side_معلومات, &dst->nb_side_معلومات);
                أرجع AVERROR(ENOMEM);
            }
            حافظه_نقل(sd_dst->معلومات, sd_src->معلومات, sd_src->اندازه);
        } وإلا {
            AVBufferRef *ref = av_بفر_ref(sd_src->buf);
            sd_dst = av_چوکاټ_new_side_معلومات_from_buf(dst, sd_src->type, ref);
            إذا (!sd_dst) {
                av_بفر_unref(&ref);
                av_چوکاټ_side_معلومات_free(&dst->side_معلومات, &dst->nb_side_معلومات);
                أرجع AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->شخصي_ref, src->شخصي_ref);
    أرجع av_بفر_replace(&dst->opaque_ref, src->opaque_ref);
}

صحيح av_چوکاټ_ref(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح ret = 0;

    av_assert1(dst->پلنوالی == 0 && dst->لوړوالی == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ترتیب == AV_CHANNEL_ترتیب_UNSPEC);

    dst->format         = src->format;
    dst->پلنوالی          = src->پلنوالی;
    dst->لوړوالی         = src->لوړوالی;
    dst->nb_samples     = src->nb_samples;

    ret = چوکاټ_copy_props(dst, src, 0);
    إذا (ret < 0)
        اذهب fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    إذا (ret < 0)
        اذهب fail;

    /* duplicate the frame data if it's not refcounted */
    إذا (!src->buf[0]) {
        ret = av_چوکاټ_get_بفر(dst, 0);
        إذا (ret < 0)
            اذهب fail;

        ret = av_چوکاټ_copy(dst, src);
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

    إذا (src->hw_چوکاټونه_ctx) {
        dst->hw_چوکاټونه_ctx = av_بفر_ref(src->hw_چوکاټونه_ctx);
        إذا (!dst->hw_چوکاټونه_ctx) {
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

    حافظه_نقل(dst->معلومات,     src->معلومات,     حجم(src->معلومات));
    حافظه_نقل(dst->linesize, src->linesize, حجم(src->linesize));

    أرجع 0;

fail:
    av_چوکاټ_unref(dst);
    أرجع ret;
}

صحيح av_چوکاټ_replace(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح ret = 0;

    إذا (dst == src)
        أرجع AVERROR(EINVAL);

    إذا (!src->buf[0]) {
        av_چوکاټ_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        إذا (   src->معلومات[0] || src->معلومات[1]
            || src->معلومات[2] || src->معلومات[3])
            أرجع av_چوکاټ_ref(dst, src);

        ret = چوکاټ_copy_props(dst, src, 0);
        إذا (ret < 0)
            اذهب fail;
    }

    dst->format         = src->format;
    dst->پلنوالی          = src->پلنوالی;
    dst->لوړوالی         = src->لوړوالی;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    إذا (ret < 0)
        اذهب fail;

    av_چوکاټ_side_معلومات_free(&dst->side_معلومات, &dst->nb_side_معلومات);
    av_dict_free(&dst->metadata);
    ret = چوکاټ_copy_props(dst, src, 0);
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

    ret = av_بفر_replace(&dst->hw_چوکاټونه_ctx, src->hw_چوکاټونه_ctx);
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

    حافظه_نقل(dst->معلومات,     src->معلومات,     حجم(src->معلومات));
    حافظه_نقل(dst->linesize, src->linesize, حجم(src->linesize));

    أرجع 0;

fail:
    av_چوکاټ_unref(dst);
    أرجع ret;
}

AVFrame *av_چوکاټ_clone(ثابت AVFrame *src)
{
    AVFrame *ret = av_چوکاټ_alloc();

    إذا (!ret)
        أرجع عدم;

    إذا (av_چوکاټ_ref(ret, src) < 0)
        av_چوکاټ_free(&ret);

    أرجع ret;
}

فراغ av_چوکاټ_unref(AVFrame *چوکاټ)
{
    إذا (!چوکاټ)
        أرجع;

    av_چوکاټ_side_معلومات_free(&چوکاټ->side_معلومات, &چوکاټ->nb_side_معلومات);

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(چوکاټ->buf); i++)
        av_بفر_unref(&چوکاټ->buf[i]);
    لكل (صحيح i = 0; i < چوکاټ->nb_extended_buf; i++)
        av_بفر_unref(&چوکاټ->extended_buf[i]);
    av_freep(&چوکاټ->extended_buf);
    av_dict_free(&چوکاټ->metadata);

    av_بفر_unref(&چوکاټ->hw_چوکاټونه_ctx);

    av_بفر_unref(&چوکاټ->opaque_ref);
    av_refstruct_unref(&چوکاټ->شخصي_ref);

    إذا (چوکاټ->extended_معلومات != چوکاټ->معلومات)
        av_freep(&چوکاټ->extended_معلومات);

    av_channel_layout_uninit(&چوکاټ->ch_layout);

    get_چوکاټ_defaults(چوکاټ);
}

فراغ av_چوکاټ_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->پلنوالی == 0 && dst->لوړوالی == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ترتیب == AV_CHANNEL_ترتیب_UNSPEC);

    *dst = *src;
    إذا (src->extended_معلومات == src->معلومات)
        dst->extended_معلومات = dst->معلومات;
    get_چوکاټ_defaults(src);
}

صحيح av_چوکاټ_is_writable(AVFrame *چوکاټ)
{
    صحيح ret = 1;

    /* assume non-refcounted frames are not writable */
    إذا (!چوکاټ->buf[0])
        أرجع 0;

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(چوکاټ->buf); i++)
        إذا (چوکاټ->buf[i])
            ret &= !!av_بفر_is_writable(چوکاټ->buf[i]);
    لكل (صحيح i = 0; i < چوکاټ->nb_extended_buf; i++)
        ret &= !!av_بفر_is_writable(چوکاټ->extended_buf[i]);

    أرجع ret;
}

صحيح av_چوکاټ_make_writable(AVFrame *چوکاټ)
{
    AVFrame tmp;
    صحيح ret;

    إذا (av_چوکاټ_is_writable(چوکاټ))
        أرجع 0;

    memset(&tmp, 0, حجم(tmp));
    tmp.format         = چوکاټ->format;
    tmp.پلنوالی          = چوکاټ->پلنوالی;
    tmp.لوړوالی         = چوکاټ->لوړوالی;
    tmp.nb_samples     = چوکاټ->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &چوکاټ->ch_layout);
    إذا (ret < 0) {
        av_چوکاټ_unref(&tmp);
        أرجع ret;
    }

    إذا (چوکاټ->hw_چوکاټونه_ctx)
        ret = av_hwframe_get_بفر(چوکاټ->hw_چوکاټونه_ctx, &tmp, 0);
    وإلا
        ret = av_چوکاټ_get_بفر(&tmp, 0);
    إذا (ret < 0)
        أرجع ret;

    ret = av_چوکاټ_copy(&tmp, چوکاټ);
    إذا (ret < 0) {
        av_چوکاټ_unref(&tmp);
        أرجع ret;
    }

    ret = av_چوکاټ_copy_props(&tmp, چوکاټ);
    إذا (ret < 0) {
        av_چوکاټ_unref(&tmp);
        أرجع ret;
    }

    av_چوکاټ_unref(چوکاټ);

    *چوکاټ = tmp;
    إذا (tmp.معلومات == tmp.extended_معلومات)
        چوکاټ->extended_معلومات = چوکاټ->معلومات;

    أرجع 0;
}

صحيح av_چوکاټ_copy_props(AVFrame *dst, ثابت AVFrame *src)
{
    أرجع چوکاټ_copy_props(dst, src, 1);
}

AVBufferRef *av_چوکاټ_get_plane_بفر(ثابت AVFrame *چوکاټ, صحيح plane)
{
    uintptr_t معلومات;
    صحيح planes;

    إذا (چوکاټ->nb_samples) {
        صحيح channels = چوکاټ->ch_layout.nb_channels;
        إذا (!channels)
            أرجع عدم;
        planes = av_sample_fmt_is_planar(چوکاټ->format) ? channels : 1;
    } وإلا
        planes = 4;

    إذا (plane < 0 || plane >= planes || !چوکاټ->extended_معلومات[plane])
        أرجع عدم;
    معلومات = (uintptr_t)چوکاټ->extended_معلومات[plane];

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(چوکاټ->buf) && چوکاټ->buf[i]; i++) {
        AVBufferRef *buf = چوکاټ->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->معلومات;

        إذا (معلومات >= buf_begin && معلومات < buf_begin + buf->اندازه)
            أرجع buf;
    }
    لكل (صحيح i = 0; i < چوکاټ->nb_extended_buf; i++) {
        AVBufferRef *buf = چوکاټ->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->معلومات;

        إذا (معلومات >= buf_begin && معلومات < buf_begin + buf->اندازه)
            أرجع buf;
    }
    أرجع عدم;
}

AVFrame_Side_معلومات *av_چوکاټ_new_side_معلومات_from_buf(AVFrame *چوکاټ,
                                                 تعداد AVFrame_Side_معلومات_Type type,
                                                 AVBufferRef *buf)
{
    أرجع
        ff_چوکاټ_side_معلومات_جمع_کړه_from_buf(
            &چوکاټ->side_معلومات, &چوکاټ->nb_side_معلومات, type, buf);
}

AVFrame_Side_معلومات *av_چوکاټ_new_side_معلومات(AVFrame *چوکاټ,
                                        تعداد AVFrame_Side_معلومات_Type type,
                                        size_t اندازه)
{
    AVFrame_Side_معلومات *ret;
    AVBufferRef *buf = av_بفر_alloc(اندازه);
    ret = av_چوکاټ_new_side_معلومات_from_buf(چوکاټ, type, buf);
    إذا (!ret)
        av_بفر_unref(&buf);
    أرجع ret;
}

AVFrame_Side_معلومات *av_چوکاټ_get_side_معلومات(ثابت AVFrame *چوکاټ,
                                        تعداد AVFrame_Side_معلومات_Type type)
{
    أرجع (AVFrame_Side_معلومات *)av_چوکاټ_side_معلومات_get(
        چوکاټ->side_معلومات, چوکاټ->nb_side_معلومات,
        type
    );
}

ساكن صحيح چوکاټ_copy_video(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح planes;

    إذا (dst->پلنوالی  < src->پلنوالی ||
        dst->لوړوالی < src->لوړوالی)
        أرجع AVERROR(EINVAL);

    إذا (src->hw_چوکاټونه_ctx || dst->hw_چوکاټونه_ctx)
        أرجع av_hwframe_transfer_معلومات(dst, src, 0);

    planes = av_pix_fmt_شمېر_planes(dst->format);
    لكل (صحيح i = 0; i < planes; i++)
        إذا (!dst->معلومات[i] || !src->معلومات[i])
            أرجع AVERROR(EINVAL);

    av_image_copy2(dst->معلومات, dst->linesize,
                   src->معلومات, src->linesize,
                   dst->format, src->پلنوالی, src->لوړوالی);

    أرجع 0;
}

ساكن صحيح چوکاټ_copy_audio(AVFrame *dst, ثابت AVFrame *src)
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

صحيح av_چوکاټ_copy(AVFrame *dst, ثابت AVFrame *src)
{
    إذا (dst->format != src->format || dst->format < 0)
        أرجع AVERROR(EINVAL);

    إذا (dst->پلنوالی > 0 && dst->لوړوالی > 0)
        أرجع چوکاټ_copy_video(dst, src);
    وإلا إذا (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        أرجع چوکاټ_copy_audio(dst, src);

    أرجع AVERROR(EINVAL);
}

فراغ av_چوکاټ_remove_side_معلومات(AVFrame *چوکاټ, تعداد AVFrame_Side_معلومات_Type type)
{
    av_چوکاټ_side_معلومات_remove(&چوکاټ->side_معلومات, &چوکاټ->nb_side_معلومات, type);
}

ساكن صحيح calc_cropping_offsets(size_t offsets[4], ثابت AVFrame *چوکاټ,
                                 ثابت AVPixFmtDescriptor *desc)
{
    لكل (صحيح i = 0; چوکاټ->معلومات[i]; i++) {
        ثابت AVComponentDescriptor *comp = عدم;
        صحيح ښويدنه_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        صحيح ښويدنه_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

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

        offsets[i] = (چوکاټ->crop_سر  >> ښويدنه_y) * چوکاټ->linesize[i] +
                     (چوکاټ->crop_کیڼ >> ښويدنه_x) * comp->ګام;
    }

    أرجع 0;
}

صحيح av_چوکاټ_apply_cropping(AVFrame *چوکاټ, صحيح flags)
{
    ثابت AVPixFmtDescriptor *desc;
    size_t offsets[4];
    صحيح ret;

    إذا (!(چوکاټ->پلنوالی > 0 && چوکاټ->لوړوالی > 0))
        أرجع AVERROR(EINVAL);

    إذا (چوکاټ->crop_کیڼ >= لوی_عدد - چوکاټ->crop_ښی        ||
        چوکاټ->crop_سر  >= لوی_عدد - چوکاټ->crop_bottom       ||
        (چوکاټ->crop_کیڼ + چوکاټ->crop_ښی) >= چوکاټ->پلنوالی ||
        (چوکاټ->crop_سر + چوکاټ->crop_bottom) >= چوکاټ->لوړوالی)
        أرجع AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(چوکاټ->format);
    إذا (!desc)
        أرجع AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    إذا (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        چوکاټ->پلنوالی      -= چوکاټ->crop_ښی;
        چوکاټ->لوړوالی     -= چوکاټ->crop_bottom;
        چوکاټ->crop_ښی  = 0;
        چوکاټ->crop_bottom = 0;
        أرجع 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, چوکاټ, desc);
    إذا (ret < 0)
        أرجع ret;

    /* adjust the offsets to avoid breaking alignment */
    إذا (!(flags & AV_چوکاټ_CROP_UNALIGNED)) {
        صحيح log2_crop_align = چوکاټ->crop_کیڼ ? ff_ctz(چوکاټ->crop_کیڼ) : لوی_عدد;
        صحيح min_log2_align = لوی_عدد;

        لكل (صحيح i = 0; چوکاټ->معلومات[i]; i++) {
            صحيح log2_align = offsets[i] ? ff_ctz(offsets[i]) : لوی_عدد;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        إذا (min_log2_align < 5 && log2_crop_align != لوی_عدد) {
            چوکاټ->crop_کیڼ &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, چوکاټ, desc);
            إذا (ret < 0)
                أرجع ret;
        }
    }

    لكل (صحيح i = 0; چوکاټ->معلومات[i]; i++)
        چوکاټ->معلومات[i] += offsets[i];

    چوکاټ->پلنوالی      -= (چوکاټ->crop_کیڼ + چوکاټ->crop_ښی);
    چوکاټ->لوړوالی     -= (چوکاټ->crop_سر  + چوکاټ->crop_bottom);
    چوکاټ->crop_کیڼ   = 0;
    چوکاټ->crop_ښی  = 0;
    چوکاټ->crop_سر    = 0;
    چوکاټ->crop_bottom = 0;

    أرجع 0;
}
