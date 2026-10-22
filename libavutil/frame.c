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

ساکن خالی get_چوکھٹا_defaults(AVFrame *چوکھٹا)
{
    memset(چوکھٹا, 0, حجم(*چوکھٹا));

    چوکھٹا->pts                   =
    چوکھٹا->pkt_dts               = AV_NOPTS_قدر;
    چوکھٹا->بہترین_effort_timestamp = AV_NOPTS_قدر;
    چوکھٹا->duration            = 0;
    چوکھٹا->وقت_بنیاد           = (AVRational){ 0, 1 };
    چوکھٹا->sample_aspect_تناسب = (AVRational){ 0, 1 };
    چوکھٹا->format              = -1; /* unknown */
    چوکھٹا->extended_ڈیٹا       = چوکھٹا->ڈیٹا;
    چوکھٹا->color_primaries     = AVCOL_PRI_UNSPECIFIED;
    چوکھٹا->color_trc           = AVCOL_TRC_UNSPECIFIED;
    چوکھٹا->colorspace          = AVCOL_SPC_UNSPECIFIED;
    چوکھٹا->color_range         = AVCOL_RANGE_UNSPECIFIED;
    چوکھٹا->chroma_location     = AVCHROMA_LOC_UNSPECIFIED;
    چوکھٹا->alpha_منوال          = AVALPHA_منوال_UNSPECIFIED;
    چوکھٹا->flags               = 0;
}

AVFrame *av_چوکھٹا_alloc(خالی)
{
    AVFrame *چوکھٹا = av_malloc(حجم(*چوکھٹا));

    اگر (!چوکھٹا)
        واپس تہی;

    get_چوکھٹا_defaults(چوکھٹا);

    واپس چوکھٹا;
}

خالی av_چوکھٹا_free(AVFrame **چوکھٹا)
{
    اگر (!چوکھٹا || !*چوکھٹا)
        واپس;

    av_چوکھٹا_unref(*چوکھٹا);
    av_freep(چوکھٹا);
}

#تعریف_کرو ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

صحیح ff_چوکھٹا_get_video_بفر(AVFrame *چوکھٹا, صحیح align,
                              AVBufferRef *(*alloc)(خالی *opaque, size_t سائز),
                              خالی *opaque)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(چوکھٹا->format);
    صحیح ret, padded_اونچائی;
    صحیح plane_padding;
    ptrdiff_t linesizes[4];
    size_t کل_سائز, sizes[4];

    اگر (!desc)
        واپس AVERROR(EINVAL);

    اگر ((ret = av_image_check_سائز(چوکھٹا->چوڑائی, چوکھٹا->اونچائی, 0, تہی)) < 0)
        واپس ret;

    اگر (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    اگر (!چوکھٹا->linesize[0]) {
        برائے (صحیح i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(چوکھٹا->linesize, چوکھٹا->format,
                                          FFALIGN(چوکھٹا->چوڑائی, i));
            اگر (ret < 0)
                واپس ret;
            اگر (!(چوکھٹا->linesize[0] & (align-1)))
                توڑو;
        }

        برائے (صحیح i = 0; i < 4 && چوکھٹا->linesize[i]; i++)
            چوکھٹا->linesize[i] = FFALIGN(چوکھٹا->linesize[i], align);
    }

    برائے (صحیح i = 0; i < 4; i++)
        linesizes[i] = چوکھٹا->linesize[i];

    padded_اونچائی = FFALIGN(چوکھٹا->اونچائی, 32);
    اگر ((ret = av_image_fill_plane_sizes(sizes, چوکھٹا->format,
                                         padded_اونچائی, linesizes)) < 0)
        واپس ret;

    کل_سائز = 4 * plane_padding + 4 * align;
    برائے (صحیح i = 0; i < 4; i++) {
        اگر (sizes[i] > SIZE_MAX - کل_سائز)
            واپس AVERROR(EINVAL);
        کل_سائز += sizes[i];
    }

    چوکھٹا->buf[0] = alloc ? alloc(opaque, کل_سائز) : av_بفر_alloc(کل_سائز);
    اگر (!چوکھٹا->buf[0]) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }

    اگر ((ret = av_image_fill_اشارے(چوکھٹا->ڈیٹا, چوکھٹا->format, padded_اونچائی,
                                      چوکھٹا->buf[0]->ڈیٹا, چوکھٹا->linesize)) < 0)
        جاؤ fail;

    برائے (صحیح i = 1; i < 4; i++) {
        اگر (چوکھٹا->ڈیٹا[i])
            چوکھٹا->ڈیٹا[i] += i * plane_padding;
        چوکھٹا->ڈیٹا[i] = (uint8_t *)FFALIGN((uintptr_t)چوکھٹا->ڈیٹا[i], align);
    }

    چوکھٹا->extended_ڈیٹا = چوکھٹا->ڈیٹا;

    واپس 0;
fail:
    av_چوکھٹا_unref(چوکھٹا);
    واپس ret;
}

ساکن صحیح get_audio_بفر(AVFrame *چوکھٹا, صحیح align)
{
    صحیح planar   = av_sample_fmt_is_planar(چوکھٹا->format);
    صحیح channels, planes;
    size_t سائز;
    صحیح ret;

    channels = چوکھٹا->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    اگر (!چوکھٹا->linesize[0]) {
        ret = av_samples_get_بفر_سائز(&چوکھٹا->linesize[0], channels,
                                         چوکھٹا->nb_samples, چوکھٹا->format,
                                         align);
        اگر (ret < 0)
            واپس ret;
    }

    اگر (align <= 0)
        align = ALIGN;

    اگر (planes > AV_عدد_ڈیٹا_اشارے) {
        چوکھٹا->extended_ڈیٹا = av_calloc(planes,
                                          حجم(*چوکھٹا->extended_ڈیٹا));
        چوکھٹا->extended_buf  = av_calloc(planes - AV_عدد_ڈیٹا_اشارے,
                                          حجم(*چوکھٹا->extended_buf));
        اگر (!چوکھٹا->extended_ڈیٹا || !چوکھٹا->extended_buf) {
            av_freep(&چوکھٹا->extended_ڈیٹا);
            av_freep(&چوکھٹا->extended_buf);
            واپس AVERROR(ENOMEM);
        }
        چوکھٹا->nb_extended_buf = planes - AV_عدد_ڈیٹا_اشارے;
    } ورنہ
        چوکھٹا->extended_ڈیٹا = چوکھٹا->ڈیٹا;

    اگر (چوکھٹا->linesize[0] > SIZE_MAX - align)
        واپس AVERROR(EINVAL);
    سائز = چوکھٹا->linesize[0] + (size_t)align;

    برائے (صحیح i = 0; i < FFMIN(planes, AV_عدد_ڈیٹا_اشارے); i++) {
        چوکھٹا->buf[i] = av_بفر_alloc(سائز);
        اگر (!چوکھٹا->buf[i]) {
            av_چوکھٹا_unref(چوکھٹا);
            واپس AVERROR(ENOMEM);
        }
        چوکھٹا->extended_ڈیٹا[i] = چوکھٹا->ڈیٹا[i] =
            (uint8_t *)FFALIGN((uintptr_t)چوکھٹا->buf[i]->ڈیٹا, align);
    }
    برائے (صحیح i = 0; i < planes - AV_عدد_ڈیٹا_اشارے; i++) {
        چوکھٹا->extended_buf[i] = av_بفر_alloc(سائز);
        اگر (!چوکھٹا->extended_buf[i]) {
            av_چوکھٹا_unref(چوکھٹا);
            واپس AVERROR(ENOMEM);
        }
        چوکھٹا->extended_ڈیٹا[i + AV_عدد_ڈیٹا_اشارے] =
            (uint8_t *)FFALIGN((uintptr_t)چوکھٹا->extended_buf[i]->ڈیٹا, align);
    }
    واپس 0;

}

صحیح av_چوکھٹا_get_بفر(AVFrame *چوکھٹا, صحیح align)
{
    اگر (چوکھٹا->format < 0)
        واپس AVERROR(EINVAL);

    اگر (چوکھٹا->چوڑائی > 0 && چوکھٹا->اونچائی > 0)
        واپس ff_چوکھٹا_get_video_بفر(چوکھٹا, align, تہی, تہی);
    ورنہ اگر (چوکھٹا->nb_samples > 0 &&
             (av_channel_layout_check(&چوکھٹا->ch_layout)))
        واپس get_audio_بفر(چوکھٹا, align);

    واپس AVERROR(EINVAL);
}

ساکن صحیح چوکھٹا_copy_props(AVFrame *dst, ثابت AVFrame *src, صحیح force_copy)
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
    dst->وقت_بنیاد              = src->وقت_بنیاد;
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

    برائے (صحیح i = 0; i < src->nb_side_ڈیٹا; i++) {
        ثابت AVFrame_Side_ڈیٹا *sd_src = src->side_ڈیٹا[i];
        AVFrame_Side_ڈیٹا *sd_dst;
        اگر (   sd_src->type == AV_چوکھٹا_ڈیٹا_PANSCAN
            && (src->چوڑائی != dst->چوڑائی || src->اونچائی != dst->اونچائی))
            جاری;
        اگر (force_copy) {
            sd_dst = av_چوکھٹا_new_side_ڈیٹا(dst, sd_src->type,
                                            sd_src->سائز);
            اگر (!sd_dst) {
                av_چوکھٹا_side_ڈیٹا_free(&dst->side_ڈیٹا, &dst->nb_side_ڈیٹا);
                واپس AVERROR(ENOMEM);
            }
            حافظہ_نقل(sd_dst->ڈیٹا, sd_src->ڈیٹا, sd_src->سائز);
        } ورنہ {
            AVBufferRef *ref = av_بفر_ref(sd_src->buf);
            sd_dst = av_چوکھٹا_new_side_ڈیٹا_from_buf(dst, sd_src->type, ref);
            اگر (!sd_dst) {
                av_بفر_unref(&ref);
                av_چوکھٹا_side_ڈیٹا_free(&dst->side_ڈیٹا, &dst->nb_side_ڈیٹا);
                واپس AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->نجی_ref, src->نجی_ref);
    واپس av_بفر_replace(&dst->opaque_ref, src->opaque_ref);
}

صحیح av_چوکھٹا_ref(AVFrame *dst, ثابت AVFrame *src)
{
    صحیح ret = 0;

    av_assert1(dst->چوڑائی == 0 && dst->اونچائی == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ترتیب == AV_CHANNEL_ترتیب_UNSPEC);

    dst->format         = src->format;
    dst->چوڑائی          = src->چوڑائی;
    dst->اونچائی         = src->اونچائی;
    dst->nb_samples     = src->nb_samples;

    ret = چوکھٹا_copy_props(dst, src, 0);
    اگر (ret < 0)
        جاؤ fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    اگر (ret < 0)
        جاؤ fail;

    /* duplicate the frame data if it's not refcounted */
    اگر (!src->buf[0]) {
        ret = av_چوکھٹا_get_بفر(dst, 0);
        اگر (ret < 0)
            جاؤ fail;

        ret = av_چوکھٹا_copy(dst, src);
        اگر (ret < 0)
            جاؤ fail;

        واپس 0;
    }

    /* ref the buffers */
    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        اگر (!src->buf[i])
            جاری;
        dst->buf[i] = av_بفر_ref(src->buf[i]);
        اگر (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            جاؤ fail;
        }
    }

    اگر (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      حجم(*dst->extended_buf));
        اگر (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            جاؤ fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        برائے (صحیح i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_بفر_ref(src->extended_buf[i]);
            اگر (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                جاؤ fail;
            }
        }
    }

    اگر (src->hw_چوکھٹے_ctx) {
        dst->hw_چوکھٹے_ctx = av_بفر_ref(src->hw_چوکھٹے_ctx);
        اگر (!dst->hw_چوکھٹے_ctx) {
            ret = AVERROR(ENOMEM);
            جاؤ fail;
        }
    }

    /* duplicate extended data */
    اگر (src->extended_ڈیٹا != src->ڈیٹا) {
        صحیح ch = dst->ch_layout.nb_channels;

        اگر (ch <= 0 || ch > SIZE_MAX / حجم(*dst->extended_ڈیٹا)) {
            ret = AVERROR(EINVAL);
            جاؤ fail;
        }

        dst->extended_ڈیٹا = av_memdup(src->extended_ڈیٹا, حجم(*dst->extended_ڈیٹا) * ch);
        اگر (!dst->extended_ڈیٹا) {
            ret = AVERROR(ENOMEM);
            جاؤ fail;
        }
    } ورنہ
        dst->extended_ڈیٹا = dst->ڈیٹا;

    حافظہ_نقل(dst->ڈیٹا,     src->ڈیٹا,     حجم(src->ڈیٹا));
    حافظہ_نقل(dst->linesize, src->linesize, حجم(src->linesize));

    واپس 0;

fail:
    av_چوکھٹا_unref(dst);
    واپس ret;
}

صحیح av_چوکھٹا_replace(AVFrame *dst, ثابت AVFrame *src)
{
    صحیح ret = 0;

    اگر (dst == src)
        واپس AVERROR(EINVAL);

    اگر (!src->buf[0]) {
        av_چوکھٹا_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        اگر (   src->ڈیٹا[0] || src->ڈیٹا[1]
            || src->ڈیٹا[2] || src->ڈیٹا[3])
            واپس av_چوکھٹا_ref(dst, src);

        ret = چوکھٹا_copy_props(dst, src, 0);
        اگر (ret < 0)
            جاؤ fail;
    }

    dst->format         = src->format;
    dst->چوڑائی          = src->چوڑائی;
    dst->اونچائی         = src->اونچائی;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    اگر (ret < 0)
        جاؤ fail;

    av_چوکھٹا_side_ڈیٹا_free(&dst->side_ڈیٹا, &dst->nb_side_ڈیٹا);
    av_dict_free(&dst->metadata);
    ret = چوکھٹا_copy_props(dst, src, 0);
    اگر (ret < 0)
        جاؤ fail;

    /* replace the buffers */
    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_بفر_replace(&dst->buf[i], src->buf[i]);
        اگر (ret < 0)
            جاؤ fail;
    }

    اگر (src->extended_buf) {
        اگر (dst->nb_extended_buf != src->nb_extended_buf) {
            صحیح nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            خالی *tmp;

            برائے (صحیح i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_بفر_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   حجم(*dst->extended_buf));
            اگر (!tmp) {
                ret = AVERROR(ENOMEM);
                جاؤ fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * حجم(*dst->extended_buf));
        }

        برائے (صحیح i = 0; i < src->nb_extended_buf; i++) {
            ret = av_بفر_replace(&dst->extended_buf[i], src->extended_buf[i]);
            اگر (ret < 0)
                جاؤ fail;
        }
    } ورنہ اگر (dst->extended_buf) {
        برائے (صحیح i = 0; i < dst->nb_extended_buf; i++)
            av_بفر_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_بفر_replace(&dst->hw_چوکھٹے_ctx, src->hw_چوکھٹے_ctx);
    اگر (ret < 0)
        جاؤ fail;

    اگر (dst->extended_ڈیٹا != dst->ڈیٹا)
        av_freep(&dst->extended_ڈیٹا);

    اگر (src->extended_ڈیٹا != src->ڈیٹا) {
        صحیح ch = dst->ch_layout.nb_channels;

        اگر (ch <= 0 || ch > SIZE_MAX / حجم(*dst->extended_ڈیٹا)) {
            ret = AVERROR(EINVAL);
            جاؤ fail;
        }

        dst->extended_ڈیٹا = av_memdup(src->extended_ڈیٹا, حجم(*dst->extended_ڈیٹا) * ch);
        اگر (!dst->extended_ڈیٹا) {
            ret = AVERROR(ENOMEM);
            جاؤ fail;
        }
    } ورنہ
        dst->extended_ڈیٹا = dst->ڈیٹا;

    حافظہ_نقل(dst->ڈیٹا,     src->ڈیٹا,     حجم(src->ڈیٹا));
    حافظہ_نقل(dst->linesize, src->linesize, حجم(src->linesize));

    واپس 0;

fail:
    av_چوکھٹا_unref(dst);
    واپس ret;
}

AVFrame *av_چوکھٹا_clone(ثابت AVFrame *src)
{
    AVFrame *ret = av_چوکھٹا_alloc();

    اگر (!ret)
        واپس تہی;

    اگر (av_چوکھٹا_ref(ret, src) < 0)
        av_چوکھٹا_free(&ret);

    واپس ret;
}

خالی av_چوکھٹا_unref(AVFrame *چوکھٹا)
{
    اگر (!چوکھٹا)
        واپس;

    av_چوکھٹا_side_ڈیٹا_free(&چوکھٹا->side_ڈیٹا, &چوکھٹا->nb_side_ڈیٹا);

    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(چوکھٹا->buf); i++)
        av_بفر_unref(&چوکھٹا->buf[i]);
    برائے (صحیح i = 0; i < چوکھٹا->nb_extended_buf; i++)
        av_بفر_unref(&چوکھٹا->extended_buf[i]);
    av_freep(&چوکھٹا->extended_buf);
    av_dict_free(&چوکھٹا->metadata);

    av_بفر_unref(&چوکھٹا->hw_چوکھٹے_ctx);

    av_بفر_unref(&چوکھٹا->opaque_ref);
    av_refstruct_unref(&چوکھٹا->نجی_ref);

    اگر (چوکھٹا->extended_ڈیٹا != چوکھٹا->ڈیٹا)
        av_freep(&چوکھٹا->extended_ڈیٹا);

    av_channel_layout_uninit(&چوکھٹا->ch_layout);

    get_چوکھٹا_defaults(چوکھٹا);
}

خالی av_چوکھٹا_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->چوڑائی == 0 && dst->اونچائی == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ترتیب == AV_CHANNEL_ترتیب_UNSPEC);

    *dst = *src;
    اگر (src->extended_ڈیٹا == src->ڈیٹا)
        dst->extended_ڈیٹا = dst->ڈیٹا;
    get_چوکھٹا_defaults(src);
}

صحیح av_چوکھٹا_is_writable(AVFrame *چوکھٹا)
{
    صحیح ret = 1;

    /* assume non-refcounted frames are not writable */
    اگر (!چوکھٹا->buf[0])
        واپس 0;

    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(چوکھٹا->buf); i++)
        اگر (چوکھٹا->buf[i])
            ret &= !!av_بفر_is_writable(چوکھٹا->buf[i]);
    برائے (صحیح i = 0; i < چوکھٹا->nb_extended_buf; i++)
        ret &= !!av_بفر_is_writable(چوکھٹا->extended_buf[i]);

    واپس ret;
}

صحیح av_چوکھٹا_make_writable(AVFrame *چوکھٹا)
{
    AVFrame tmp;
    صحیح ret;

    اگر (av_چوکھٹا_is_writable(چوکھٹا))
        واپس 0;

    memset(&tmp, 0, حجم(tmp));
    tmp.format         = چوکھٹا->format;
    tmp.چوڑائی          = چوکھٹا->چوڑائی;
    tmp.اونچائی         = چوکھٹا->اونچائی;
    tmp.nb_samples     = چوکھٹا->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &چوکھٹا->ch_layout);
    اگر (ret < 0) {
        av_چوکھٹا_unref(&tmp);
        واپس ret;
    }

    اگر (چوکھٹا->hw_چوکھٹے_ctx)
        ret = av_hwframe_get_بفر(چوکھٹا->hw_چوکھٹے_ctx, &tmp, 0);
    ورنہ
        ret = av_چوکھٹا_get_بفر(&tmp, 0);
    اگر (ret < 0)
        واپس ret;

    ret = av_چوکھٹا_copy(&tmp, چوکھٹا);
    اگر (ret < 0) {
        av_چوکھٹا_unref(&tmp);
        واپس ret;
    }

    ret = av_چوکھٹا_copy_props(&tmp, چوکھٹا);
    اگر (ret < 0) {
        av_چوکھٹا_unref(&tmp);
        واپس ret;
    }

    av_چوکھٹا_unref(چوکھٹا);

    *چوکھٹا = tmp;
    اگر (tmp.ڈیٹا == tmp.extended_ڈیٹا)
        چوکھٹا->extended_ڈیٹا = چوکھٹا->ڈیٹا;

    واپس 0;
}

صحیح av_چوکھٹا_copy_props(AVFrame *dst, ثابت AVFrame *src)
{
    واپس چوکھٹا_copy_props(dst, src, 1);
}

AVBufferRef *av_چوکھٹا_get_plane_بفر(ثابت AVFrame *چوکھٹا, صحیح plane)
{
    uintptr_t ڈیٹا;
    صحیح planes;

    اگر (چوکھٹا->nb_samples) {
        صحیح channels = چوکھٹا->ch_layout.nb_channels;
        اگر (!channels)
            واپس تہی;
        planes = av_sample_fmt_is_planar(چوکھٹا->format) ? channels : 1;
    } ورنہ
        planes = 4;

    اگر (plane < 0 || plane >= planes || !چوکھٹا->extended_ڈیٹا[plane])
        واپس تہی;
    ڈیٹا = (uintptr_t)چوکھٹا->extended_ڈیٹا[plane];

    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(چوکھٹا->buf) && چوکھٹا->buf[i]; i++) {
        AVBufferRef *buf = چوکھٹا->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->ڈیٹا;

        اگر (ڈیٹا >= buf_begin && ڈیٹا < buf_begin + buf->سائز)
            واپس buf;
    }
    برائے (صحیح i = 0; i < چوکھٹا->nb_extended_buf; i++) {
        AVBufferRef *buf = چوکھٹا->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->ڈیٹا;

        اگر (ڈیٹا >= buf_begin && ڈیٹا < buf_begin + buf->سائز)
            واپس buf;
    }
    واپس تہی;
}

AVFrame_Side_ڈیٹا *av_چوکھٹا_new_side_ڈیٹا_from_buf(AVFrame *چوکھٹا,
                                                 شمار AVFrame_Side_ڈیٹا_Type type,
                                                 AVBufferRef *buf)
{
    واپس
        ff_چوکھٹا_side_ڈیٹا_جوڑو_from_buf(
            &چوکھٹا->side_ڈیٹا, &چوکھٹا->nb_side_ڈیٹا, type, buf);
}

AVFrame_Side_ڈیٹا *av_چوکھٹا_new_side_ڈیٹا(AVFrame *چوکھٹا,
                                        شمار AVFrame_Side_ڈیٹا_Type type,
                                        size_t سائز)
{
    AVFrame_Side_ڈیٹا *ret;
    AVBufferRef *buf = av_بفر_alloc(سائز);
    ret = av_چوکھٹا_new_side_ڈیٹا_from_buf(چوکھٹا, type, buf);
    اگر (!ret)
        av_بفر_unref(&buf);
    واپس ret;
}

AVFrame_Side_ڈیٹا *av_چوکھٹا_get_side_ڈیٹا(ثابت AVFrame *چوکھٹا,
                                        شمار AVFrame_Side_ڈیٹا_Type type)
{
    واپس (AVFrame_Side_ڈیٹا *)av_چوکھٹا_side_ڈیٹا_get(
        چوکھٹا->side_ڈیٹا, چوکھٹا->nb_side_ڈیٹا,
        type
    );
}

ساکن صحیح چوکھٹا_copy_video(AVFrame *dst, ثابت AVFrame *src)
{
    صحیح planes;

    اگر (dst->چوڑائی  < src->چوڑائی ||
        dst->اونچائی < src->اونچائی)
        واپس AVERROR(EINVAL);

    اگر (src->hw_چوکھٹے_ctx || dst->hw_چوکھٹے_ctx)
        واپس av_hwframe_transfer_ڈیٹا(dst, src, 0);

    planes = av_pix_fmt_گنتی_planes(dst->format);
    برائے (صحیح i = 0; i < planes; i++)
        اگر (!dst->ڈیٹا[i] || !src->ڈیٹا[i])
            واپس AVERROR(EINVAL);

    av_image_copy2(dst->ڈیٹا, dst->linesize,
                   src->ڈیٹا, src->linesize,
                   dst->format, src->چوڑائی, src->اونچائی);

    واپس 0;
}

ساکن صحیح چوکھٹا_copy_audio(AVFrame *dst, ثابت AVFrame *src)
{
    صحیح planar   = av_sample_fmt_is_planar(dst->format);
    صحیح channels = dst->ch_layout.nb_channels;
    صحیح planes   = planar ? channels : 1;

    اگر (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        واپس AVERROR(EINVAL);

    برائے (صحیح i = 0; i < planes; i++)
        اگر (!dst->extended_ڈیٹا[i] || !src->extended_ڈیٹا[i])
            واپس AVERROR(EINVAL);

    av_samples_copy(dst->extended_ڈیٹا, src->extended_ڈیٹا, 0, 0,
                    dst->nb_samples, channels, dst->format);

    واپس 0;
}

صحیح av_چوکھٹا_copy(AVFrame *dst, ثابت AVFrame *src)
{
    اگر (dst->format != src->format || dst->format < 0)
        واپس AVERROR(EINVAL);

    اگر (dst->چوڑائی > 0 && dst->اونچائی > 0)
        واپس چوکھٹا_copy_video(dst, src);
    ورنہ اگر (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        واپس چوکھٹا_copy_audio(dst, src);

    واپس AVERROR(EINVAL);
}

خالی av_چوکھٹا_remove_side_ڈیٹا(AVFrame *چوکھٹا, شمار AVFrame_Side_ڈیٹا_Type type)
{
    av_چوکھٹا_side_ڈیٹا_remove(&چوکھٹا->side_ڈیٹا, &چوکھٹا->nb_side_ڈیٹا, type);
}

ساکن صحیح calc_cropping_offsets(size_t offsets[4], ثابت AVFrame *چوکھٹا,
                                 ثابت AVPixFmtDescriptor *desc)
{
    برائے (صحیح i = 0; چوکھٹا->ڈیٹا[i]; i++) {
        ثابت AVComponentDescriptor *comp = تہی;
        صحیح سرکاؤ_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        صحیح سرکاؤ_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        اگر (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            توڑو;
        }

        /* find any component descriptor for this plane */
        برائے (صحیح j = 0; j < desc->nb_components; j++) {
            اگر (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                توڑو;
            }
        }
        اگر (!comp)
            واپس AVERROR_BUG;

        offsets[i] = (چوکھٹا->crop_چوٹی  >> سرکاؤ_y) * چوکھٹا->linesize[i] +
                     (چوکھٹا->crop_بایاں >> سرکاؤ_x) * comp->قدم;
    }

    واپس 0;
}

صحیح av_چوکھٹا_apply_cropping(AVFrame *چوکھٹا, صحیح flags)
{
    ثابت AVPixFmtDescriptor *desc;
    size_t offsets[4];
    صحیح ret;

    اگر (!(چوکھٹا->چوڑائی > 0 && چوکھٹا->اونچائی > 0))
        واپس AVERROR(EINVAL);

    اگر (چوکھٹا->crop_بایاں >= زیادہ_سے_زیادہ_عدد - چوکھٹا->crop_دایاں        ||
        چوکھٹا->crop_چوٹی  >= زیادہ_سے_زیادہ_عدد - چوکھٹا->crop_bottom       ||
        (چوکھٹا->crop_بایاں + چوکھٹا->crop_دایاں) >= چوکھٹا->چوڑائی ||
        (چوکھٹا->crop_چوٹی + چوکھٹا->crop_bottom) >= چوکھٹا->اونچائی)
        واپس AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(چوکھٹا->format);
    اگر (!desc)
        واپس AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    اگر (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        چوکھٹا->چوڑائی      -= چوکھٹا->crop_دایاں;
        چوکھٹا->اونچائی     -= چوکھٹا->crop_bottom;
        چوکھٹا->crop_دایاں  = 0;
        چوکھٹا->crop_bottom = 0;
        واپس 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, چوکھٹا, desc);
    اگر (ret < 0)
        واپس ret;

    /* adjust the offsets to avoid breaking alignment */
    اگر (!(flags & AV_چوکھٹا_CROP_UNALIGNED)) {
        صحیح log2_crop_align = چوکھٹا->crop_بایاں ? ff_ctz(چوکھٹا->crop_بایاں) : زیادہ_سے_زیادہ_عدد;
        صحیح min_log2_align = زیادہ_سے_زیادہ_عدد;

        برائے (صحیح i = 0; چوکھٹا->ڈیٹا[i]; i++) {
            صحیح log2_align = offsets[i] ? ff_ctz(offsets[i]) : زیادہ_سے_زیادہ_عدد;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        اگر (min_log2_align < 5 && log2_crop_align != زیادہ_سے_زیادہ_عدد) {
            چوکھٹا->crop_بایاں &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, چوکھٹا, desc);
            اگر (ret < 0)
                واپس ret;
        }
    }

    برائے (صحیح i = 0; چوکھٹا->ڈیٹا[i]; i++)
        چوکھٹا->ڈیٹا[i] += offsets[i];

    چوکھٹا->چوڑائی      -= (چوکھٹا->crop_بایاں + چوکھٹا->crop_دایاں);
    چوکھٹا->اونچائی     -= (چوکھٹا->crop_چوٹی  + چوکھٹا->crop_bottom);
    چوکھٹا->crop_بایاں   = 0;
    چوکھٹا->crop_دایاں  = 0;
    چوکھٹا->crop_چوٹی    = 0;
    چوکھٹا->crop_bottom = 0;

    واپس 0;
}
