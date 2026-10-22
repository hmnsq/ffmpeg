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

ساكن فراغ get_قاب_defaults(AVFrame *قاب)
{
    memset(قاب, 0, حجم(*قاب));

    قاب->pts                   =
    قاب->pkt_dts               = AV_NOPTS_مقدار;
    قاب->بهترین_effort_timestamp = AV_NOPTS_مقدار;
    قاب->duration            = 0;
    قاب->زمان_پایه           = (AVRational){ 0, 1 };
    قاب->sample_aspect_نسبت = (AVRational){ 0, 1 };
    قاب->format              = -1; /* unknown */
    قاب->extended_داده       = قاب->داده;
    قاب->color_primaries     = AVCOL_PRI_UNSPECIFIED;
    قاب->color_trc           = AVCOL_TRC_UNSPECIFIED;
    قاب->colorspace          = AVCOL_SPC_UNSPECIFIED;
    قاب->color_range         = AVCOL_RANGE_UNSPECIFIED;
    قاب->chroma_location     = AVCHROMA_LOC_UNSPECIFIED;
    قاب->alpha_نما          = AVALPHA_نما_UNSPECIFIED;
    قاب->flags               = 0;
}

AVFrame *av_قاب_alloc(فراغ)
{
    AVFrame *قاب = av_malloc(حجم(*قاب));

    إذا (!قاب)
        أرجع عدم;

    get_قاب_defaults(قاب);

    أرجع قاب;
}

فراغ av_قاب_free(AVFrame **قاب)
{
    إذا (!قاب || !*قاب)
        أرجع;

    av_قاب_unref(*قاب);
    av_freep(قاب);
}

#تعریف_کن ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

صحيح ff_قاب_get_video_میانگیر(AVFrame *قاب, صحيح align,
                              AVBufferRef *(*alloc)(فراغ *opaque, size_t اندازه),
                              فراغ *opaque)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(قاب->format);
    صحيح ret, padded_ارتفاع;
    صحيح plane_padding;
    ptrdiff_t linesizes[4];
    size_t مجموع_اندازه, sizes[4];

    إذا (!desc)
        أرجع AVERROR(EINVAL);

    إذا ((ret = av_image_check_اندازه(قاب->عرض, قاب->ارتفاع, 0, عدم)) < 0)
        أرجع ret;

    إذا (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    إذا (!قاب->linesize[0]) {
        لكل (صحيح i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(قاب->linesize, قاب->format,
                                          FFALIGN(قاب->عرض, i));
            إذا (ret < 0)
                أرجع ret;
            إذا (!(قاب->linesize[0] & (align-1)))
                اكسر;
        }

        لكل (صحيح i = 0; i < 4 && قاب->linesize[i]; i++)
            قاب->linesize[i] = FFALIGN(قاب->linesize[i], align);
    }

    لكل (صحيح i = 0; i < 4; i++)
        linesizes[i] = قاب->linesize[i];

    padded_ارتفاع = FFALIGN(قاب->ارتفاع, 32);
    إذا ((ret = av_image_fill_plane_sizes(sizes, قاب->format,
                                         padded_ارتفاع, linesizes)) < 0)
        أرجع ret;

    مجموع_اندازه = 4 * plane_padding + 4 * align;
    لكل (صحيح i = 0; i < 4; i++) {
        إذا (sizes[i] > SIZE_MAX - مجموع_اندازه)
            أرجع AVERROR(EINVAL);
        مجموع_اندازه += sizes[i];
    }

    قاب->buf[0] = alloc ? alloc(opaque, مجموع_اندازه) : av_میانگیر_alloc(مجموع_اندازه);
    إذا (!قاب->buf[0]) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    إذا ((ret = av_image_fill_اشارهگرها(قاب->داده, قاب->format, padded_ارتفاع,
                                      قاب->buf[0]->داده, قاب->linesize)) < 0)
        اذهب fail;

    لكل (صحيح i = 1; i < 4; i++) {
        إذا (قاب->داده[i])
            قاب->داده[i] += i * plane_padding;
        قاب->داده[i] = (uint8_t *)FFALIGN((uintptr_t)قاب->داده[i], align);
    }

    قاب->extended_داده = قاب->داده;

    أرجع 0;
fail:
    av_قاب_unref(قاب);
    أرجع ret;
}

ساكن صحيح get_audio_میانگیر(AVFrame *قاب, صحيح align)
{
    صحيح planar   = av_sample_fmt_is_planar(قاب->format);
    صحيح channels, planes;
    size_t اندازه;
    صحيح ret;

    channels = قاب->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    إذا (!قاب->linesize[0]) {
        ret = av_samples_get_میانگیر_اندازه(&قاب->linesize[0], channels,
                                         قاب->nb_samples, قاب->format,
                                         align);
        إذا (ret < 0)
            أرجع ret;
    }

    إذا (align <= 0)
        align = ALIGN;

    إذا (planes > AV_رقم_داده_اشارهگرها) {
        قاب->extended_داده = av_calloc(planes,
                                          حجم(*قاب->extended_داده));
        قاب->extended_buf  = av_calloc(planes - AV_رقم_داده_اشارهگرها,
                                          حجم(*قاب->extended_buf));
        إذا (!قاب->extended_داده || !قاب->extended_buf) {
            av_freep(&قاب->extended_داده);
            av_freep(&قاب->extended_buf);
            أرجع AVERROR(ENOMEM);
        }
        قاب->nb_extended_buf = planes - AV_رقم_داده_اشارهگرها;
    } وإلا
        قاب->extended_داده = قاب->داده;

    إذا (قاب->linesize[0] > SIZE_MAX - align)
        أرجع AVERROR(EINVAL);
    اندازه = قاب->linesize[0] + (size_t)align;

    لكل (صحيح i = 0; i < FFMIN(planes, AV_رقم_داده_اشارهگرها); i++) {
        قاب->buf[i] = av_میانگیر_alloc(اندازه);
        إذا (!قاب->buf[i]) {
            av_قاب_unref(قاب);
            أرجع AVERROR(ENOMEM);
        }
        قاب->extended_داده[i] = قاب->داده[i] =
            (uint8_t *)FFALIGN((uintptr_t)قاب->buf[i]->داده, align);
    }
    لكل (صحيح i = 0; i < planes - AV_رقم_داده_اشارهگرها; i++) {
        قاب->extended_buf[i] = av_میانگیر_alloc(اندازه);
        إذا (!قاب->extended_buf[i]) {
            av_قاب_unref(قاب);
            أرجع AVERROR(ENOMEM);
        }
        قاب->extended_داده[i + AV_رقم_داده_اشارهگرها] =
            (uint8_t *)FFALIGN((uintptr_t)قاب->extended_buf[i]->داده, align);
    }
    أرجع 0;

}

صحيح av_قاب_get_میانگیر(AVFrame *قاب, صحيح align)
{
    إذا (قاب->format < 0)
        أرجع AVERROR(EINVAL);

    إذا (قاب->عرض > 0 && قاب->ارتفاع > 0)
        أرجع ff_قاب_get_video_میانگیر(قاب, align, عدم, عدم);
    وإلا إذا (قاب->nb_samples > 0 &&
             (av_channel_layout_check(&قاب->ch_layout)))
        أرجع get_audio_میانگیر(قاب, align);

    أرجع AVERROR(EINVAL);
}

ساكن صحيح قاب_copy_props(AVFrame *dst, ثابت AVFrame *src, صحيح force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_نسبت    = src->sample_aspect_نسبت;
    dst->crop_بالاترین               = src->crop_بالاترین;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_چپ              = src->crop_چپ;
    dst->crop_راست             = src->crop_راست;
    dst->pts                    = src->pts;
    dst->duration               = src->duration;
    dst->repeat_pict            = src->repeat_pict;
    dst->sample_نرخ            = src->sample_نرخ;
    dst->opaque                 = src->opaque;
    dst->pkt_dts                = src->pkt_dts;
    dst->زمان_پایه              = src->زمان_پایه;
    dst->quality                = src->quality;
    dst->بهترین_effort_timestamp  = src->بهترین_effort_timestamp;
    dst->flags                  = src->flags;
    dst->decode_error_flags     = src->decode_error_flags;
    dst->color_primaries        = src->color_primaries;
    dst->color_trc              = src->color_trc;
    dst->colorspace             = src->colorspace;
    dst->color_range            = src->color_range;
    dst->chroma_location        = src->chroma_location;
    dst->alpha_نما             = src->alpha_نما;

    av_dict_copy(&dst->metadata, src->metadata, 0);

    لكل (صحيح i = 0; i < src->nb_side_داده; i++) {
        ثابت AVFrame_Side_داده *sd_src = src->side_داده[i];
        AVFrame_Side_داده *sd_dst;
        إذا (   sd_src->type == AV_قاب_داده_PANSCAN
            && (src->عرض != dst->عرض || src->ارتفاع != dst->ارتفاع))
            استمر;
        إذا (force_copy) {
            sd_dst = av_قاب_new_side_داده(dst, sd_src->type,
                                            sd_src->اندازه);
            إذا (!sd_dst) {
                av_قاب_side_داده_free(&dst->side_داده, &dst->nb_side_داده);
                أرجع AVERROR(ENOMEM);
            }
            کپی_حافظه(sd_dst->داده, sd_src->داده, sd_src->اندازه);
        } وإلا {
            AVBufferRef *ref = av_میانگیر_ref(sd_src->buf);
            sd_dst = av_قاب_new_side_داده_from_buf(dst, sd_src->type, ref);
            إذا (!sd_dst) {
                av_میانگیر_unref(&ref);
                av_قاب_side_داده_free(&dst->side_داده, &dst->nb_side_داده);
                أرجع AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->خصوصی_ref, src->خصوصی_ref);
    أرجع av_میانگیر_replace(&dst->opaque_ref, src->opaque_ref);
}

صحيح av_قاب_ref(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح ret = 0;

    av_assert1(dst->عرض == 0 && dst->ارتفاع == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ترتیب == AV_CHANNEL_ترتیب_UNSPEC);

    dst->format         = src->format;
    dst->عرض          = src->عرض;
    dst->ارتفاع         = src->ارتفاع;
    dst->nb_samples     = src->nb_samples;

    ret = قاب_copy_props(dst, src, 0);
    إذا (ret < 0)
        اذهب fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    إذا (ret < 0)
        اذهب fail;

    /* duplicate the frame data if it's not refcounted */
    إذا (!src->buf[0]) {
        ret = av_قاب_get_میانگیر(dst, 0);
        إذا (ret < 0)
            اذهب fail;

        ret = av_قاب_copy(dst, src);
        إذا (ret < 0)
            اذهب fail;

        أرجع 0;
    }

    /* ref the buffers */
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        إذا (!src->buf[i])
            استمر;
        dst->buf[i] = av_میانگیر_ref(src->buf[i]);
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
            dst->extended_buf[i] = av_میانگیر_ref(src->extended_buf[i]);
            إذا (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                اذهب fail;
            }
        }
    }

    إذا (src->hw_قابها_ctx) {
        dst->hw_قابها_ctx = av_میانگیر_ref(src->hw_قابها_ctx);
        إذا (!dst->hw_قابها_ctx) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    }

    /* duplicate extended data */
    إذا (src->extended_داده != src->داده) {
        صحيح ch = dst->ch_layout.nb_channels;

        إذا (ch <= 0 || ch > SIZE_MAX / حجم(*dst->extended_داده)) {
            ret = AVERROR(EINVAL);
            اذهب fail;
        }

        dst->extended_داده = av_memdup(src->extended_داده, حجم(*dst->extended_داده) * ch);
        إذا (!dst->extended_داده) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    } وإلا
        dst->extended_داده = dst->داده;

    کپی_حافظه(dst->داده,     src->داده,     حجم(src->داده));
    کپی_حافظه(dst->linesize, src->linesize, حجم(src->linesize));

    أرجع 0;

fail:
    av_قاب_unref(dst);
    أرجع ret;
}

صحيح av_قاب_replace(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح ret = 0;

    إذا (dst == src)
        أرجع AVERROR(EINVAL);

    إذا (!src->buf[0]) {
        av_قاب_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        إذا (   src->داده[0] || src->داده[1]
            || src->داده[2] || src->داده[3])
            أرجع av_قاب_ref(dst, src);

        ret = قاب_copy_props(dst, src, 0);
        إذا (ret < 0)
            اذهب fail;
    }

    dst->format         = src->format;
    dst->عرض          = src->عرض;
    dst->ارتفاع         = src->ارتفاع;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    إذا (ret < 0)
        اذهب fail;

    av_قاب_side_داده_free(&dst->side_داده, &dst->nb_side_داده);
    av_dict_free(&dst->metadata);
    ret = قاب_copy_props(dst, src, 0);
    إذا (ret < 0)
        اذهب fail;

    /* replace the buffers */
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_میانگیر_replace(&dst->buf[i], src->buf[i]);
        إذا (ret < 0)
            اذهب fail;
    }

    إذا (src->extended_buf) {
        إذا (dst->nb_extended_buf != src->nb_extended_buf) {
            صحيح nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            فراغ *tmp;

            لكل (صحيح i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_میانگیر_unref(&dst->extended_buf[i]);

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
            ret = av_میانگیر_replace(&dst->extended_buf[i], src->extended_buf[i]);
            إذا (ret < 0)
                اذهب fail;
        }
    } وإلا إذا (dst->extended_buf) {
        لكل (صحيح i = 0; i < dst->nb_extended_buf; i++)
            av_میانگیر_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_میانگیر_replace(&dst->hw_قابها_ctx, src->hw_قابها_ctx);
    إذا (ret < 0)
        اذهب fail;

    إذا (dst->extended_داده != dst->داده)
        av_freep(&dst->extended_داده);

    إذا (src->extended_داده != src->داده) {
        صحيح ch = dst->ch_layout.nb_channels;

        إذا (ch <= 0 || ch > SIZE_MAX / حجم(*dst->extended_داده)) {
            ret = AVERROR(EINVAL);
            اذهب fail;
        }

        dst->extended_داده = av_memdup(src->extended_داده, حجم(*dst->extended_داده) * ch);
        إذا (!dst->extended_داده) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
    } وإلا
        dst->extended_داده = dst->داده;

    کپی_حافظه(dst->داده,     src->داده,     حجم(src->داده));
    کپی_حافظه(dst->linesize, src->linesize, حجم(src->linesize));

    أرجع 0;

fail:
    av_قاب_unref(dst);
    أرجع ret;
}

AVFrame *av_قاب_clone(ثابت AVFrame *src)
{
    AVFrame *ret = av_قاب_alloc();

    إذا (!ret)
        أرجع عدم;

    إذا (av_قاب_ref(ret, src) < 0)
        av_قاب_free(&ret);

    أرجع ret;
}

فراغ av_قاب_unref(AVFrame *قاب)
{
    إذا (!قاب)
        أرجع;

    av_قاب_side_داده_free(&قاب->side_داده, &قاب->nb_side_داده);

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(قاب->buf); i++)
        av_میانگیر_unref(&قاب->buf[i]);
    لكل (صحيح i = 0; i < قاب->nb_extended_buf; i++)
        av_میانگیر_unref(&قاب->extended_buf[i]);
    av_freep(&قاب->extended_buf);
    av_dict_free(&قاب->metadata);

    av_میانگیر_unref(&قاب->hw_قابها_ctx);

    av_میانگیر_unref(&قاب->opaque_ref);
    av_refstruct_unref(&قاب->خصوصی_ref);

    إذا (قاب->extended_داده != قاب->داده)
        av_freep(&قاب->extended_داده);

    av_channel_layout_uninit(&قاب->ch_layout);

    get_قاب_defaults(قاب);
}

فراغ av_قاب_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->عرض == 0 && dst->ارتفاع == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ترتیب == AV_CHANNEL_ترتیب_UNSPEC);

    *dst = *src;
    إذا (src->extended_داده == src->داده)
        dst->extended_داده = dst->داده;
    get_قاب_defaults(src);
}

صحيح av_قاب_is_writable(AVFrame *قاب)
{
    صحيح ret = 1;

    /* assume non-refcounted frames are not writable */
    إذا (!قاب->buf[0])
        أرجع 0;

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(قاب->buf); i++)
        إذا (قاب->buf[i])
            ret &= !!av_میانگیر_is_writable(قاب->buf[i]);
    لكل (صحيح i = 0; i < قاب->nb_extended_buf; i++)
        ret &= !!av_میانگیر_is_writable(قاب->extended_buf[i]);

    أرجع ret;
}

صحيح av_قاب_make_writable(AVFrame *قاب)
{
    AVFrame tmp;
    صحيح ret;

    إذا (av_قاب_is_writable(قاب))
        أرجع 0;

    memset(&tmp, 0, حجم(tmp));
    tmp.format         = قاب->format;
    tmp.عرض          = قاب->عرض;
    tmp.ارتفاع         = قاب->ارتفاع;
    tmp.nb_samples     = قاب->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &قاب->ch_layout);
    إذا (ret < 0) {
        av_قاب_unref(&tmp);
        أرجع ret;
    }

    إذا (قاب->hw_قابها_ctx)
        ret = av_hwframe_get_میانگیر(قاب->hw_قابها_ctx, &tmp, 0);
    وإلا
        ret = av_قاب_get_میانگیر(&tmp, 0);
    إذا (ret < 0)
        أرجع ret;

    ret = av_قاب_copy(&tmp, قاب);
    إذا (ret < 0) {
        av_قاب_unref(&tmp);
        أرجع ret;
    }

    ret = av_قاب_copy_props(&tmp, قاب);
    إذا (ret < 0) {
        av_قاب_unref(&tmp);
        أرجع ret;
    }

    av_قاب_unref(قاب);

    *قاب = tmp;
    إذا (tmp.داده == tmp.extended_داده)
        قاب->extended_داده = قاب->داده;

    أرجع 0;
}

صحيح av_قاب_copy_props(AVFrame *dst, ثابت AVFrame *src)
{
    أرجع قاب_copy_props(dst, src, 1);
}

AVBufferRef *av_قاب_get_plane_میانگیر(ثابت AVFrame *قاب, صحيح plane)
{
    uintptr_t داده;
    صحيح planes;

    إذا (قاب->nb_samples) {
        صحيح channels = قاب->ch_layout.nb_channels;
        إذا (!channels)
            أرجع عدم;
        planes = av_sample_fmt_is_planar(قاب->format) ? channels : 1;
    } وإلا
        planes = 4;

    إذا (plane < 0 || plane >= planes || !قاب->extended_داده[plane])
        أرجع عدم;
    داده = (uintptr_t)قاب->extended_داده[plane];

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(قاب->buf) && قاب->buf[i]; i++) {
        AVBufferRef *buf = قاب->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->داده;

        إذا (داده >= buf_begin && داده < buf_begin + buf->اندازه)
            أرجع buf;
    }
    لكل (صحيح i = 0; i < قاب->nb_extended_buf; i++) {
        AVBufferRef *buf = قاب->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->داده;

        إذا (داده >= buf_begin && داده < buf_begin + buf->اندازه)
            أرجع buf;
    }
    أرجع عدم;
}

AVFrame_Side_داده *av_قاب_new_side_داده_from_buf(AVFrame *قاب,
                                                 تعداد AVFrame_Side_داده_Type type,
                                                 AVBufferRef *buf)
{
    أرجع
        ff_قاب_side_داده_جمع_کن_from_buf(
            &قاب->side_داده, &قاب->nb_side_داده, type, buf);
}

AVFrame_Side_داده *av_قاب_new_side_داده(AVFrame *قاب,
                                        تعداد AVFrame_Side_داده_Type type,
                                        size_t اندازه)
{
    AVFrame_Side_داده *ret;
    AVBufferRef *buf = av_میانگیر_alloc(اندازه);
    ret = av_قاب_new_side_داده_from_buf(قاب, type, buf);
    إذا (!ret)
        av_میانگیر_unref(&buf);
    أرجع ret;
}

AVFrame_Side_داده *av_قاب_get_side_داده(ثابت AVFrame *قاب,
                                        تعداد AVFrame_Side_داده_Type type)
{
    أرجع (AVFrame_Side_داده *)av_قاب_side_داده_get(
        قاب->side_داده, قاب->nb_side_داده,
        type
    );
}

ساكن صحيح قاب_copy_video(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح planes;

    إذا (dst->عرض  < src->عرض ||
        dst->ارتفاع < src->ارتفاع)
        أرجع AVERROR(EINVAL);

    إذا (src->hw_قابها_ctx || dst->hw_قابها_ctx)
        أرجع av_hwframe_transfer_داده(dst, src, 0);

    planes = av_pix_fmt_شمار_planes(dst->format);
    لكل (صحيح i = 0; i < planes; i++)
        إذا (!dst->داده[i] || !src->داده[i])
            أرجع AVERROR(EINVAL);

    av_image_copy2(dst->داده, dst->linesize,
                   src->داده, src->linesize,
                   dst->format, src->عرض, src->ارتفاع);

    أرجع 0;
}

ساكن صحيح قاب_copy_audio(AVFrame *dst, ثابت AVFrame *src)
{
    صحيح planar   = av_sample_fmt_is_planar(dst->format);
    صحيح channels = dst->ch_layout.nb_channels;
    صحيح planes   = planar ? channels : 1;

    إذا (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        أرجع AVERROR(EINVAL);

    لكل (صحيح i = 0; i < planes; i++)
        إذا (!dst->extended_داده[i] || !src->extended_داده[i])
            أرجع AVERROR(EINVAL);

    av_samples_copy(dst->extended_داده, src->extended_داده, 0, 0,
                    dst->nb_samples, channels, dst->format);

    أرجع 0;
}

صحيح av_قاب_copy(AVFrame *dst, ثابت AVFrame *src)
{
    إذا (dst->format != src->format || dst->format < 0)
        أرجع AVERROR(EINVAL);

    إذا (dst->عرض > 0 && dst->ارتفاع > 0)
        أرجع قاب_copy_video(dst, src);
    وإلا إذا (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        أرجع قاب_copy_audio(dst, src);

    أرجع AVERROR(EINVAL);
}

فراغ av_قاب_remove_side_داده(AVFrame *قاب, تعداد AVFrame_Side_داده_Type type)
{
    av_قاب_side_داده_remove(&قاب->side_داده, &قاب->nb_side_داده, type);
}

ساكن صحيح calc_cropping_offsets(size_t offsets[4], ثابت AVFrame *قاب,
                                 ثابت AVPixFmtDescriptor *desc)
{
    لكل (صحيح i = 0; قاب->داده[i]; i++) {
        ثابت AVComponentDescriptor *comp = عدم;
        صحيح لغزش_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        صحيح لغزش_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

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

        offsets[i] = (قاب->crop_بالاترین  >> لغزش_y) * قاب->linesize[i] +
                     (قاب->crop_چپ >> لغزش_x) * comp->گام;
    }

    أرجع 0;
}

صحيح av_قاب_apply_cropping(AVFrame *قاب, صحيح flags)
{
    ثابت AVPixFmtDescriptor *desc;
    size_t offsets[4];
    صحيح ret;

    إذا (!(قاب->عرض > 0 && قاب->ارتفاع > 0))
        أرجع AVERROR(EINVAL);

    إذا (قاب->crop_چپ >= بیشترین_صحیح - قاب->crop_راست        ||
        قاب->crop_بالاترین  >= بیشترین_صحیح - قاب->crop_bottom       ||
        (قاب->crop_چپ + قاب->crop_راست) >= قاب->عرض ||
        (قاب->crop_بالاترین + قاب->crop_bottom) >= قاب->ارتفاع)
        أرجع AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(قاب->format);
    إذا (!desc)
        أرجع AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    إذا (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        قاب->عرض      -= قاب->crop_راست;
        قاب->ارتفاع     -= قاب->crop_bottom;
        قاب->crop_راست  = 0;
        قاب->crop_bottom = 0;
        أرجع 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, قاب, desc);
    إذا (ret < 0)
        أرجع ret;

    /* adjust the offsets to avoid breaking alignment */
    إذا (!(flags & AV_قاب_CROP_UNALIGNED)) {
        صحيح log2_crop_align = قاب->crop_چپ ? ff_ctz(قاب->crop_چپ) : بیشترین_صحیح;
        صحيح min_log2_align = بیشترین_صحیح;

        لكل (صحيح i = 0; قاب->داده[i]; i++) {
            صحيح log2_align = offsets[i] ? ff_ctz(offsets[i]) : بیشترین_صحیح;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        إذا (min_log2_align < 5 && log2_crop_align != بیشترین_صحیح) {
            قاب->crop_چپ &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, قاب, desc);
            إذا (ret < 0)
                أرجع ret;
        }
    }

    لكل (صحيح i = 0; قاب->داده[i]; i++)
        قاب->داده[i] += offsets[i];

    قاب->عرض      -= (قاب->crop_چپ + قاب->crop_راست);
    قاب->ارتفاع     -= (قاب->crop_بالاترین  + قاب->crop_bottom);
    قاب->crop_چپ   = 0;
    قاب->crop_راست  = 0;
    قاب->crop_بالاترین    = 0;
    قاب->crop_bottom = 0;

    أرجع 0;
}
