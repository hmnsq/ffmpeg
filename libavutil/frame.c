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

ساكن فراغ get_چوکھٹا_defaults(AVFrame *چوکھٹا)
{
    memset(چوکھٹا, 0, حجم(*چوکھٹا));

    چوکھٹا->pts                   =
    چوکھٹا->pkt_dts               = AV_NOPTS_قدر;
    چوکھٹا->بہترین_effort_timestamp = AV_NOPTS_قدر;
    چوکھٹا->duration            = 0;
    چوکھٹا->ویلا_ادھار           = (AVRational){ 0, 1 };
    چوکھٹا->sample_aspect_تناسب = (AVRational){ 0, 1 };
    چوکھٹا->format              = -1; /* unknown */
    چوکھٹا->extended_انکڑے       = چوکھٹا->انکڑے;
    چوکھٹا->color_primaries     = AVCOL_PRI_UNSPECIFIED;
    چوکھٹا->color_trc           = AVCOL_TRC_UNSPECIFIED;
    چوکھٹا->colorspace          = AVCOL_SPC_UNSPECIFIED;
    چوکھٹا->color_range         = AVCOL_RANGE_UNSPECIFIED;
    چوکھٹا->chroma_location     = AVCHROMA_LOC_UNSPECIFIED;
    چوکھٹا->alpha_منوال          = AVALPHA_منوال_UNSPECIFIED;
    چوکھٹا->flags               = 0;
}

AVFrame *av_چوکھٹا_alloc(فراغ)
{
    AVFrame *چوکھٹا = av_malloc(حجم(*چوکھٹا));

    إذا (!چوکھٹا)
        أرجع عدم;

    get_چوکھٹا_defaults(چوکھٹا);

    أرجع چوکھٹا;
}

فراغ av_چوکھٹا_free(AVFrame **چوکھٹا)
{
    إذا (!چوکھٹا || !*چوکھٹا)
        أرجع;

    av_چوکھٹا_unref(*چوکھٹا);
    av_freep(چوکھٹا);
}

#تعریف_کرو ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

صحيح ff_چوکھٹا_get_video_بفر(AVFrame *چوکھٹا, صحيح align,
                              AVBufferRef *(*alloc)(فراغ *opaque, size_t ناپ),
                              فراغ *opaque)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(چوکھٹا->format);
    صحيح ret, padded_اچائی;
    صحيح plane_padding;
    ptrdiff_t linesizes[4];
    size_t کل_ناپ, sizes[4];

    إذا (!desc)
        أرجع AVERROR(EINVAL);

    إذا ((ret = av_image_check_ناپ(چوکھٹا->چوڑائی, چوکھٹا->اچائی, 0, عدم)) < 0)
        أرجع ret;

    إذا (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    إذا (!چوکھٹا->linesize[0]) {
        لكل (صحيح i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(چوکھٹا->linesize, چوکھٹا->format,
                                          FFALIGN(چوکھٹا->چوڑائی, i));
            إذا (ret < 0)
                أرجع ret;
            إذا (!(چوکھٹا->linesize[0] & (align-1)))
                اكسر;
        }

        لكل (صحيح i = 0; i < 4 && چوکھٹا->linesize[i]; i++)
            چوکھٹا->linesize[i] = FFALIGN(چوکھٹا->linesize[i], align);
    }

    لكل (صحيح i = 0; i < 4; i++)
        linesizes[i] = چوکھٹا->linesize[i];

    padded_اچائی = FFALIGN(چوکھٹا->اچائی, 32);
    إذا ((ret = av_image_fill_plane_sizes(sizes, چوکھٹا->format,
                                         padded_اچائی, linesizes)) < 0)
        أرجع ret;

    کل_ناپ = 4 * plane_padding + 4 * align;
    لكل (صحيح i = 0; i < 4; i++) {
        إذا (sizes[i] > SIZE_MAX - کل_ناپ)
            أرجع AVERROR(EINVAL);
        کل_ناپ += sizes[i];
    }

    چوکھٹا->buf[0] = alloc ? alloc(opaque, کل_ناپ) : av_بفر_alloc(کل_ناپ);
    إذا (!چوکھٹا->buf[0]) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    إذا ((ret = av_image_fill_سوچکاں(چوکھٹا->انکڑے, چوکھٹا->format, padded_اچائی,
                                      چوکھٹا->buf[0]->انکڑے, چوکھٹا->linesize)) < 0)
        اذهب fail;

    لكل (صحيح i = 1; i < 4; i++) {
        إذا (چوکھٹا->انکڑے[i])
            چوکھٹا->انکڑے[i] += i * plane_padding;
        چوکھٹا->انکڑے[i] = (uint8_t *)FFALIGN((uintptr_t)چوکھٹا->انکڑے[i], align);
    }

    چوکھٹا->extended_انکڑے = چوکھٹا->انکڑے;

    أرجع 0;
fail:
    av_چوکھٹا_unref(چوکھٹا);
    أرجع ret;
}

ساكن صحيح get_audio_بفر(AVFrame *چوکھٹا, صحيح align)
{
    صحيح planar   = av_sample_fmt_is_planar(چوکھٹا->format);
    صحيح channels, planes;
    size_t ناپ;
    صحيح ret;

    channels = چوکھٹا->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    إذا (!چوکھٹا->linesize[0]) {
        ret = av_samples_get_بفر_ناپ(&چوکھٹا->linesize[0], channels,
                                         چوکھٹا->nb_samples, چوکھٹا->format,
                                         align);
        إذا (ret < 0)
            أرجع ret;
    }

    إذا (align <= 0)
        align = ALIGN;

    إذا (planes > AV_عدد_انکڑے_سوچکاں) {
        چوکھٹا->extended_انکڑے = av_calloc(planes,
                                          حجم(*چوکھٹا->extended_انکڑے));
        چوکھٹا->extended_buf  = av_calloc(planes - AV_عدد_انکڑے_سوچکاں,
                                          حجم(*چوکھٹا->extended_buf));
        إذا (!چوکھٹا->extended_انکڑے || !چوکھٹا->extended_buf) {
            av_freep(&چوکھٹا->extended_انکڑے);
            av_freep(&چوکھٹا->extended_buf);
            أرجع AVERROR(ENOMEM);
        }
        چوکھٹا->nb_extended_buf = planes - AV_عدد_انکڑے_سوچکاں;
    } وإلا
        چوکھٹا->extended_انکڑے = چوکھٹا->انکڑے;

    إذا (چوکھٹا->linesize[0] > SIZE_MAX - align)
        أرجع AVERROR(EINVAL);
    ناپ = چوکھٹا->linesize[0] + (size_t)align;

    لكل (صحيح i = 0; i < FFMIN(planes, AV_عدد_انکڑے_سوچکاں); i++) {
        چوکھٹا->buf[i] = av_بفر_alloc(ناپ);
        إذا (!چوکھٹا->buf[i]) {
            av_چوکھٹا_unref(چوکھٹا);
            أرجع AVERROR(ENOMEM);
        }
        چوکھٹا->extended_انکڑے[i] = چوکھٹا->انکڑے[i] =
            (uint8_t *)FFALIGN((uintptr_t)چوکھٹا->buf[i]->انکڑے, align);
    }
    لكل (صحيح i = 0; i < planes - AV_عدد_انکڑے_سوچکاں; i++) {
        چوکھٹا->extended_buf[i] = av_بفر_alloc(ناپ);
        إذا (!چوکھٹا->extended_buf[i]) {
            av_چوکھٹا_unref(چوکھٹا);
            أرجع AVERROR(ENOMEM);
        }
        چوکھٹا->extended_انکڑے[i + AV_عدد_انکڑے_سوچکاں] =
            (uint8_t *)FFALIGN((uintptr_t)چوکھٹا->extended_buf[i]->انکڑے, align);
    }
    أرجع 0;

}

صحيح av_چوکھٹا_get_بفر(AVFrame *چوکھٹا, صحيح align)
{
    إذا (چوکھٹا->format < 0)
        أرجع AVERROR(EINVAL);

    إذا (چوکھٹا->چوڑائی > 0 && چوکھٹا->اچائی > 0)
        أرجع ff_چوکھٹا_get_video_بفر(چوکھٹا, align, عدم, عدم);
    وإلا إذا (چوکھٹا->nb_samples > 0 &&
             (av_channel_layout_check(&چوکھٹا->ch_layout)))
        أرجع get_audio_بفر(چوکھٹا, align);

    أرجع AVERROR(EINVAL);
}

ساكن صحيح چوکھٹا_copy_props(AVFrame *dst, ثابت AVFrame *src, صحيح force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_تناسب    = src->sample_aspect_تناسب;
    dst->crop_چوٹی               = src->crop_چوٹی;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_بایاں              = src->crop_بایاں;
    dst->crop_دایاں             = src->crop_دایاں;
    dst->pts                    = src->pts;
    dst->duration               = src->duration;
    dst->repeat_pict            = src->repeat_pict;
    dst->sample_شرح            = src->sample_شرح;
    dst->opaque                 = src->opaque;
    dst->pkt_dts                = src->pkt_dts;
    dst->ویلا_ادھار              = src->ویلا_ادھار;
    dst->quality                = src->quality;
    dst->بہترین_effort_timestamp  = src->بہترین_effort_timestamp;
    dst->flags                  = src->flags;
    dst->decode_error_flags     = src->decode_error_flags;
    dst->color_primaries        = src->color_primaries;
    dst->color_trc              = src->color_trc;
    dst->colorspace             = src->colorspace;
    dst->color_range            = src->color_range;
    dst->chroma_location        = src->chroma_location;
    dst->alpha_منوال             = src->alpha_منوال;

    av_dict_copy(&dst->metadata, src->metadata, 0);

    لكل (صحيح i = 0; i < src->nb_side_انکڑے; i++) {
        ثابت AVFrame_Side_انکڑے *sd_src = src->side_انکڑے[i];
        AVFrame_Side_انکڑے *sd_dst;
        إذا (   sd_src->type == AV_چوکھٹا_انکڑے_PANSCAN
            && (src->چوڑائی != dst->چوڑائی || src->اچائی != dst->اچائی))
            استمر;
        إذا (force_copy) {
            sd_dst = av_چوکھٹا_new_side_انکڑے(dst, sd_src->type,
                                            sd_src->ناپ);
            إذا (!sd_dst) {
                av_چوکھٹا_side_انکڑے_free(&dst->side_انکڑے, &dst->nb_side_انکڑے);
                أرجع AVERROR(ENOMEM);
            }
            حافظہ_نقل(sd_dst->انکڑے, sd_src->انکڑے, sd_src->ناپ);
        } وإلا {
            AVBufferRef *ref = av_بفر_ref(sd_src->buf);
            sd_dst = av_چوکھٹا_new_side_انکڑے_from_buf(dst, sd_src->type, ref);
            إذا (!sd_dst) {
                av_بفر_unref(&ref);
                av_چوکھٹا_side_انکڑے_free(&dst->side_انکڑے, &dst->nb_side_انکڑے);
                أرجع AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->نجی_ref, src->نجی_ref);
    أرجع av_بفر_replace(&dst->opaque_ref, src->opaque_ref);
}

صحيح av_چوکھٹا_ref(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح ret = 0;

    av_assert1(dst->چوڑائی == 0 && dst->اچائی == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ترتیب == AV_CHANNEL_ترتیب_UNSPEC);

    dst->format         = src->format;
    dst->چوڑائی          = src->چوڑائی;
    dst->اچائی         = src->اچائی;
    dst->nb_samples     = src->nb_samples;

    ret = چوکھٹا_copy_props(dst, src, 0);
    إذا (ret < 0)
        اذهب fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    إذا (ret < 0)
        اذهب fail;

    /* duplicate the frame data if it's not refcounted */
    إذا (!src->buf[0]) {
        ret = av_چوکھٹا_get_بفر(dst, 0);
        إذا (ret < 0)
            اذهب fail;

        ret = av_چوکھٹا_copy(dst, src);
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

    إذا (src->hw_چوکھٹے_ctx) {
        dst->hw_چوکھٹے_ctx = av_بفر_ref(src->hw_چوکھٹے_ctx);
        إذا (!dst->hw_چوکھٹے_ctx) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    }

    /* duplicate extended data */
    إذا (src->extended_انکڑے != src->انکڑے) {
        صحيح ch = dst->ch_layout.nb_channels;

        إذا (ch <= 0 || ch > SIZE_MAX / حجم(*dst->extended_انکڑے)) {
            ret = AVERROR(EINVAL);
            اذهب fail;
        }

        dst->extended_انکڑے = av_memdup(src->extended_انکڑے, حجم(*dst->extended_انکڑے) * ch);
        إذا (!dst->extended_انکڑے) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    } وإلا
        dst->extended_انکڑے = dst->انکڑے;

    حافظہ_نقل(dst->انکڑے,     src->انکڑے,     حجم(src->انکڑے));
    حافظہ_نقل(dst->linesize, src->linesize, حجم(src->linesize));

    أرجع 0;

fail:
    av_چوکھٹا_unref(dst);
    أرجع ret;
}

صحيح av_چوکھٹا_replace(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح ret = 0;

    إذا (dst == src)
        أرجع AVERROR(EINVAL);

    إذا (!src->buf[0]) {
        av_چوکھٹا_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        إذا (   src->انکڑے[0] || src->انکڑے[1]
            || src->انکڑے[2] || src->انکڑے[3])
            أرجع av_چوکھٹا_ref(dst, src);

        ret = چوکھٹا_copy_props(dst, src, 0);
        إذا (ret < 0)
            اذهب fail;
    }

    dst->format         = src->format;
    dst->چوڑائی          = src->چوڑائی;
    dst->اچائی         = src->اچائی;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    إذا (ret < 0)
        اذهب fail;

    av_چوکھٹا_side_انکڑے_free(&dst->side_انکڑے, &dst->nb_side_انکڑے);
    av_dict_free(&dst->metadata);
    ret = چوکھٹا_copy_props(dst, src, 0);
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

    ret = av_بفر_replace(&dst->hw_چوکھٹے_ctx, src->hw_چوکھٹے_ctx);
    إذا (ret < 0)
        اذهب fail;

    إذا (dst->extended_انکڑے != dst->انکڑے)
        av_freep(&dst->extended_انکڑے);

    إذا (src->extended_انکڑے != src->انکڑے) {
        صحيح ch = dst->ch_layout.nb_channels;

        إذا (ch <= 0 || ch > SIZE_MAX / حجم(*dst->extended_انکڑے)) {
            ret = AVERROR(EINVAL);
            اذهب fail;
        }

        dst->extended_انکڑے = av_memdup(src->extended_انکڑے, حجم(*dst->extended_انکڑے) * ch);
        إذا (!dst->extended_انکڑے) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    } وإلا
        dst->extended_انکڑے = dst->انکڑے;

    حافظہ_نقل(dst->انکڑے,     src->انکڑے,     حجم(src->انکڑے));
    حافظہ_نقل(dst->linesize, src->linesize, حجم(src->linesize));

    أرجع 0;

fail:
    av_چوکھٹا_unref(dst);
    أرجع ret;
}

AVFrame *av_چوکھٹا_clone(ثابت AVFrame *src)
{
    AVFrame *ret = av_چوکھٹا_alloc();

    إذا (!ret)
        أرجع عدم;

    إذا (av_چوکھٹا_ref(ret, src) < 0)
        av_چوکھٹا_free(&ret);

    أرجع ret;
}

فراغ av_چوکھٹا_unref(AVFrame *چوکھٹا)
{
    إذا (!چوکھٹا)
        أرجع;

    av_چوکھٹا_side_انکڑے_free(&چوکھٹا->side_انکڑے, &چوکھٹا->nb_side_انکڑے);

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(چوکھٹا->buf); i++)
        av_بفر_unref(&چوکھٹا->buf[i]);
    لكل (صحيح i = 0; i < چوکھٹا->nb_extended_buf; i++)
        av_بفر_unref(&چوکھٹا->extended_buf[i]);
    av_freep(&چوکھٹا->extended_buf);
    av_dict_free(&چوکھٹا->metadata);

    av_بفر_unref(&چوکھٹا->hw_چوکھٹے_ctx);

    av_بفر_unref(&چوکھٹا->opaque_ref);
    av_refstruct_unref(&چوکھٹا->نجی_ref);

    إذا (چوکھٹا->extended_انکڑے != چوکھٹا->انکڑے)
        av_freep(&چوکھٹا->extended_انکڑے);

    av_channel_layout_uninit(&چوکھٹا->ch_layout);

    get_چوکھٹا_defaults(چوکھٹا);
}

فراغ av_چوکھٹا_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->چوڑائی == 0 && dst->اچائی == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ترتیب == AV_CHANNEL_ترتیب_UNSPEC);

    *dst = *src;
    إذا (src->extended_انکڑے == src->انکڑے)
        dst->extended_انکڑے = dst->انکڑے;
    get_چوکھٹا_defaults(src);
}

صحيح av_چوکھٹا_is_writable(AVFrame *چوکھٹا)
{
    صحيح ret = 1;

    /* assume non-refcounted frames are not writable */
    إذا (!چوکھٹا->buf[0])
        أرجع 0;

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(چوکھٹا->buf); i++)
        إذا (چوکھٹا->buf[i])
            ret &= !!av_بفر_is_writable(چوکھٹا->buf[i]);
    لكل (صحيح i = 0; i < چوکھٹا->nb_extended_buf; i++)
        ret &= !!av_بفر_is_writable(چوکھٹا->extended_buf[i]);

    أرجع ret;
}

صحيح av_چوکھٹا_make_writable(AVFrame *چوکھٹا)
{
    AVFrame tmp;
    صحيح ret;

    إذا (av_چوکھٹا_is_writable(چوکھٹا))
        أرجع 0;

    memset(&tmp, 0, حجم(tmp));
    tmp.format         = چوکھٹا->format;
    tmp.چوڑائی          = چوکھٹا->چوڑائی;
    tmp.اچائی         = چوکھٹا->اچائی;
    tmp.nb_samples     = چوکھٹا->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &چوکھٹا->ch_layout);
    إذا (ret < 0) {
        av_چوکھٹا_unref(&tmp);
        أرجع ret;
    }

    إذا (چوکھٹا->hw_چوکھٹے_ctx)
        ret = av_hwframe_get_بفر(چوکھٹا->hw_چوکھٹے_ctx, &tmp, 0);
    وإلا
        ret = av_چوکھٹا_get_بفر(&tmp, 0);
    إذا (ret < 0)
        أرجع ret;

    ret = av_چوکھٹا_copy(&tmp, چوکھٹا);
    إذا (ret < 0) {
        av_چوکھٹا_unref(&tmp);
        أرجع ret;
    }

    ret = av_چوکھٹا_copy_props(&tmp, چوکھٹا);
    إذا (ret < 0) {
        av_چوکھٹا_unref(&tmp);
        أرجع ret;
    }

    av_چوکھٹا_unref(چوکھٹا);

    *چوکھٹا = tmp;
    إذا (tmp.انکڑے == tmp.extended_انکڑے)
        چوکھٹا->extended_انکڑے = چوکھٹا->انکڑے;

    أرجع 0;
}

صحيح av_چوکھٹا_copy_props(AVFrame *dst, ثابت AVFrame *src)
{
    أرجع چوکھٹا_copy_props(dst, src, 1);
}

AVBufferRef *av_چوکھٹا_get_plane_بفر(ثابت AVFrame *چوکھٹا, صحيح plane)
{
    uintptr_t انکڑے;
    صحيح planes;

    إذا (چوکھٹا->nb_samples) {
        صحيح channels = چوکھٹا->ch_layout.nb_channels;
        إذا (!channels)
            أرجع عدم;
        planes = av_sample_fmt_is_planar(چوکھٹا->format) ? channels : 1;
    } وإلا
        planes = 4;

    إذا (plane < 0 || plane >= planes || !چوکھٹا->extended_انکڑے[plane])
        أرجع عدم;
    انکڑے = (uintptr_t)چوکھٹا->extended_انکڑے[plane];

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(چوکھٹا->buf) && چوکھٹا->buf[i]; i++) {
        AVBufferRef *buf = چوکھٹا->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->انکڑے;

        إذا (انکڑے >= buf_begin && انکڑے < buf_begin + buf->ناپ)
            أرجع buf;
    }
    لكل (صحيح i = 0; i < چوکھٹا->nb_extended_buf; i++) {
        AVBufferRef *buf = چوکھٹا->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->انکڑے;

        إذا (انکڑے >= buf_begin && انکڑے < buf_begin + buf->ناپ)
            أرجع buf;
    }
    أرجع عدم;
}

AVFrame_Side_انکڑے *av_چوکھٹا_new_side_انکڑے_from_buf(AVFrame *چوکھٹا,
                                                 تعداد AVFrame_Side_انکڑے_Type type,
                                                 AVBufferRef *buf)
{
    أرجع
        ff_چوکھٹا_side_انکڑے_جوڑو_from_buf(
            &چوکھٹا->side_انکڑے, &چوکھٹا->nb_side_انکڑے, type, buf);
}

AVFrame_Side_انکڑے *av_چوکھٹا_new_side_انکڑے(AVFrame *چوکھٹا,
                                        تعداد AVFrame_Side_انکڑے_Type type,
                                        size_t ناپ)
{
    AVFrame_Side_انکڑے *ret;
    AVBufferRef *buf = av_بفر_alloc(ناپ);
    ret = av_چوکھٹا_new_side_انکڑے_from_buf(چوکھٹا, type, buf);
    إذا (!ret)
        av_بفر_unref(&buf);
    أرجع ret;
}

AVFrame_Side_انکڑے *av_چوکھٹا_get_side_انکڑے(ثابت AVFrame *چوکھٹا,
                                        تعداد AVFrame_Side_انکڑے_Type type)
{
    أرجع (AVFrame_Side_انکڑے *)av_چوکھٹا_side_انکڑے_get(
        چوکھٹا->side_انکڑے, چوکھٹا->nb_side_انکڑے,
        type
    );
}

ساكن صحيح چوکھٹا_copy_video(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح planes;

    إذا (dst->چوڑائی  < src->چوڑائی ||
        dst->اچائی < src->اچائی)
        أرجع AVERROR(EINVAL);

    إذا (src->hw_چوکھٹے_ctx || dst->hw_چوکھٹے_ctx)
        أرجع av_hwframe_transfer_انکڑے(dst, src, 0);

    planes = av_pix_fmt_گنتی_planes(dst->format);
    لكل (صحيح i = 0; i < planes; i++)
        إذا (!dst->انکڑے[i] || !src->انکڑے[i])
            أرجع AVERROR(EINVAL);

    av_image_copy2(dst->انکڑے, dst->linesize,
                   src->انکڑے, src->linesize,
                   dst->format, src->چوڑائی, src->اچائی);

    أرجع 0;
}

ساكن صحيح چوکھٹا_copy_audio(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح planar   = av_sample_fmt_is_planar(dst->format);
    صحيح channels = dst->ch_layout.nb_channels;
    صحيح planes   = planar ? channels : 1;

    إذا (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        أرجع AVERROR(EINVAL);

    لكل (صحيح i = 0; i < planes; i++)
        إذا (!dst->extended_انکڑے[i] || !src->extended_انکڑے[i])
            أرجع AVERROR(EINVAL);

    av_samples_copy(dst->extended_انکڑے, src->extended_انکڑے, 0, 0,
                    dst->nb_samples, channels, dst->format);

    أرجع 0;
}

صحيح av_چوکھٹا_copy(AVFrame *dst, ثابت AVFrame *src)
{
    إذا (dst->format != src->format || dst->format < 0)
        أرجع AVERROR(EINVAL);

    إذا (dst->چوڑائی > 0 && dst->اچائی > 0)
        أرجع چوکھٹا_copy_video(dst, src);
    وإلا إذا (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        أرجع چوکھٹا_copy_audio(dst, src);

    أرجع AVERROR(EINVAL);
}

فراغ av_چوکھٹا_remove_side_انکڑے(AVFrame *چوکھٹا, تعداد AVFrame_Side_انکڑے_Type type)
{
    av_چوکھٹا_side_انکڑے_remove(&چوکھٹا->side_انکڑے, &چوکھٹا->nb_side_انکڑے, type);
}

ساكن صحيح calc_cropping_offsets(size_t offsets[4], ثابت AVFrame *چوکھٹا,
                                 ثابت AVPixFmtDescriptor *desc)
{
    لكل (صحيح i = 0; چوکھٹا->انکڑے[i]; i++) {
        ثابت AVComponentDescriptor *comp = عدم;
        صحيح کھسکاؤ_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        صحيح کھسکاؤ_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

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

        offsets[i] = (چوکھٹا->crop_چوٹی  >> کھسکاؤ_y) * چوکھٹا->linesize[i] +
                     (چوکھٹا->crop_بایاں >> کھسکاؤ_x) * comp->قدم;
    }

    أرجع 0;
}

صحيح av_چوکھٹا_apply_cropping(AVFrame *چوکھٹا, صحيح flags)
{
    ثابت AVPixFmtDescriptor *desc;
    size_t offsets[4];
    صحيح ret;

    إذا (!(چوکھٹا->چوڑائی > 0 && چوکھٹا->اچائی > 0))
        أرجع AVERROR(EINVAL);

    إذا (چوکھٹا->crop_بایاں >= ودھ_توں_ودھ_عدد - چوکھٹا->crop_دایاں        ||
        چوکھٹا->crop_چوٹی  >= ودھ_توں_ودھ_عدد - چوکھٹا->crop_bottom       ||
        (چوکھٹا->crop_بایاں + چوکھٹا->crop_دایاں) >= چوکھٹا->چوڑائی ||
        (چوکھٹا->crop_چوٹی + چوکھٹا->crop_bottom) >= چوکھٹا->اچائی)
        أرجع AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(چوکھٹا->format);
    إذا (!desc)
        أرجع AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    إذا (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        چوکھٹا->چوڑائی      -= چوکھٹا->crop_دایاں;
        چوکھٹا->اچائی     -= چوکھٹا->crop_bottom;
        چوکھٹا->crop_دایاں  = 0;
        چوکھٹا->crop_bottom = 0;
        أرجع 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, چوکھٹا, desc);
    إذا (ret < 0)
        أرجع ret;

    /* adjust the offsets to avoid breaking alignment */
    إذا (!(flags & AV_چوکھٹا_CROP_UNALIGNED)) {
        صحيح log2_crop_align = چوکھٹا->crop_بایاں ? ff_ctz(چوکھٹا->crop_بایاں) : ودھ_توں_ودھ_عدد;
        صحيح min_log2_align = ودھ_توں_ودھ_عدد;

        لكل (صحيح i = 0; چوکھٹا->انکڑے[i]; i++) {
            صحيح log2_align = offsets[i] ? ff_ctz(offsets[i]) : ودھ_توں_ودھ_عدد;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        إذا (min_log2_align < 5 && log2_crop_align != ودھ_توں_ودھ_عدد) {
            چوکھٹا->crop_بایاں &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, چوکھٹا, desc);
            إذا (ret < 0)
                أرجع ret;
        }
    }

    لكل (صحيح i = 0; چوکھٹا->انکڑے[i]; i++)
        چوکھٹا->انکڑے[i] += offsets[i];

    چوکھٹا->چوڑائی      -= (چوکھٹا->crop_بایاں + چوکھٹا->crop_دایاں);
    چوکھٹا->اچائی     -= (چوکھٹا->crop_چوٹی  + چوکھٹا->crop_bottom);
    چوکھٹا->crop_بایاں   = 0;
    چوکھٹا->crop_دایاں  = 0;
    چوکھٹا->crop_چوٹی    = 0;
    چوکھٹا->crop_bottom = 0;

    أرجع 0;
}
