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

#ಅನ್ತರ್ಭಾವ "channel_layout.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "dict.h"
#ಅನ್ತರ್ಭಾವ "frame.h"
#ಅನ್ತರ್ಭಾವ "frame_internal.h"
#ಅನ್ತರ್ಭಾವ "imgutils.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "refstruct.h"
#ಅನ್ತರ್ಭಾವ "samplefmt.h"
#ಅನ್ತರ್ಭಾವ "side_data.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"

ಸ್ಥಿರ ಶೂನ್ಯ get_ಚೌಕಟ್ಟು_defaults(AVFrame *ಚೌಕಟ್ಟು)
{
    memset(ಚೌಕಟ್ಟು, 0, ಗಾತ್ರ(*ಚೌಕಟ್ಟು));

    ಚೌಕಟ್ಟು->pts                   =
    ಚೌಕಟ್ಟು->pkt_dts               = AV_NOPTS_ಮೌಲ್ಯ;
    ಚೌಕಟ್ಟು->ಉತ್ತಮ_effort_timestamp = AV_NOPTS_ಮೌಲ್ಯ;
    ಚೌಕಟ್ಟು->duration            = 0;
    ಚೌಕಟ್ಟು->ಸಮಯ_ತಳ           = (AVRational){ 0, 1 };
    ಚೌಕಟ್ಟು->sample_aspect_ಅನುಪಾತ = (AVRational){ 0, 1 };
    ಚೌಕಟ್ಟು->format              = -1; /* unknown */
    ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ       = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ;
    ಚೌಕಟ್ಟು->color_primaries     = AVCOL_PRI_UNSPECIFIED;
    ಚೌಕಟ್ಟು->color_trc           = AVCOL_TRC_UNSPECIFIED;
    ಚೌಕಟ್ಟು->colorspace          = AVCOL_SPC_UNSPECIFIED;
    ಚೌಕಟ್ಟು->color_range         = AVCOL_RANGE_UNSPECIFIED;
    ಚೌಕಟ್ಟು->chroma_location     = AVCHROMA_LOC_UNSPECIFIED;
    ಚೌಕಟ್ಟು->alpha_ಬಹುಲಕ          = AVALPHA_ಬಹುಲಕ_UNSPECIFIED;
    ಚೌಕಟ್ಟು->flags               = 0;
}

AVFrame *av_ಚೌಕಟ್ಟು_alloc(ಶೂನ್ಯ)
{
    AVFrame *ಚೌಕಟ್ಟು = av_malloc(ಗಾತ್ರ(*ಚೌಕಟ್ಟು));

    ಆದರೆ (!ಚೌಕಟ್ಟು)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    get_ಚೌಕಟ್ಟು_defaults(ಚೌಕಟ್ಟು);

    ಹಿಂತಿರುಗಿ ಚೌಕಟ್ಟು;
}

ಶೂನ್ಯ av_ಚೌಕಟ್ಟು_free(AVFrame **ಚೌಕಟ್ಟು)
{
    ಆದರೆ (!ಚೌಕಟ್ಟು || !*ಚೌಕಟ್ಟು)
        ಹಿಂತಿರುಗಿ;

    av_ಚೌಕಟ್ಟು_unref(*ಚೌಕಟ್ಟು);
    av_freep(ಚೌಕಟ್ಟು);
}

#ವ್ಯಾಖ್ಯಾನಿಸು ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

ಪೂರ್ಣಾಂಕ ff_ಚೌಕಟ್ಟು_get_video_ಬಫರ್(AVFrame *ಚೌಕಟ್ಟು, ಪೂರ್ಣಾಂಕ align,
                              AVBufferRef *(*alloc)(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2),
                              ಶೂನ್ಯ *opaque)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ಚೌಕಟ್ಟು->format);
    ಪೂರ್ಣಾಂಕ ret, padded_ಎತ್ತರ;
    ಪೂರ್ಣಾಂಕ plane_padding;
    ptrdiff_t linesizes[4];
    size_t ಒಟ್ಟು_ಗಾತ್ರ, sizes[4];

    ಆದರೆ (!desc)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ ((ret = av_image_check_ಗಾತ್ರ(ಚೌಕಟ್ಟು->ಅಗಲ, ಚೌಕಟ್ಟು->ಎತ್ತರ, 0, ಖಾಲಿ)) < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    ಆದರೆ (!ಚೌಕಟ್ಟು->linesize[0]) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(ಚೌಕಟ್ಟು->linesize, ಚೌಕಟ್ಟು->format,
                                          FFALIGN(ಚೌಕಟ್ಟು->ಅಗಲ, i));
            ಆದರೆ (ret < 0)
                ಹಿಂತಿರುಗಿ ret;
            ಆದರೆ (!(ಚೌಕಟ್ಟು->linesize[0] & (align-1)))
                ನಿಲ್ಲಿಸು;
        }

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 4 && ಚೌಕಟ್ಟು->linesize[i]; i++)
            ಚೌಕಟ್ಟು->linesize[i] = FFALIGN(ಚೌಕಟ್ಟು->linesize[i], align);
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 4; i++)
        linesizes[i] = ಚೌಕಟ್ಟು->linesize[i];

    padded_ಎತ್ತರ = FFALIGN(ಚೌಕಟ್ಟು->ಎತ್ತರ, 32);
    ಆದರೆ ((ret = av_image_fill_plane_sizes(sizes, ಚೌಕಟ್ಟು->format,
                                         padded_ಎತ್ತರ, linesizes)) < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಒಟ್ಟು_ಗಾತ್ರ = 4 * plane_padding + 4 * align;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 4; i++) {
        ಆದರೆ (sizes[i] > SIZE_MAX - ಒಟ್ಟು_ಗಾತ್ರ)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        ಒಟ್ಟು_ಗಾತ್ರ += sizes[i];
    }

    ಚೌಕಟ್ಟು->buf[0] = alloc ? alloc(opaque, ಒಟ್ಟು_ಗಾತ್ರ) : av_ಬಫರ್_alloc(ಒಟ್ಟು_ಗಾತ್ರ);
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0]) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    ಆದರೆ ((ret = av_image_fill_ಸೂಚಕಗಳು(ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ, ಚೌಕಟ್ಟು->format, padded_ಎತ್ತರ,
                                      ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ, ಚೌಕಟ್ಟು->linesize)) < 0)
        ಹೋಗು fail;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 1; i < 4; i++) {
        ಆದರೆ (ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i])
            ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i] += i * plane_padding;
        ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i] = (uint8_t *)FFALIGN((uintptr_t)ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i], align);
    }

    ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ;

    ಹಿಂತಿರುಗಿ 0;
fail:
    av_ಚೌಕಟ್ಟು_unref(ಚೌಕಟ್ಟು);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_audio_ಬಫರ್(AVFrame *ಚೌಕಟ್ಟು, ಪೂರ್ಣಾಂಕ align)
{
    ಪೂರ್ಣಾಂಕ planar   = av_sample_fmt_is_planar(ಚೌಕಟ್ಟು->format);
    ಪೂರ್ಣಾಂಕ channels, planes;
    size_t ಗಾತ್ರ_2;
    ಪೂರ್ಣಾಂಕ ret;

    channels = ಚೌಕಟ್ಟು->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    ಆದರೆ (!ಚೌಕಟ್ಟು->linesize[0]) {
        ret = av_samples_get_ಬಫರ್_ಗಾತ್ರ(&ಚೌಕಟ್ಟು->linesize[0], channels,
                                         ಚೌಕಟ್ಟು->nb_samples, ಚೌಕಟ್ಟು->format,
                                         align);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
    }

    ಆದರೆ (align <= 0)
        align = ALIGN;

    ಆದರೆ (planes > AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು) {
        ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ = av_calloc(planes,
                                          ಗಾತ್ರ(*ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ));
        ಚೌಕಟ್ಟು->extended_buf  = av_calloc(planes - AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು,
                                          ಗಾತ್ರ(*ಚೌಕಟ್ಟು->extended_buf));
        ಆದರೆ (!ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ || !ಚೌಕಟ್ಟು->extended_buf) {
            av_freep(&ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ);
            av_freep(&ಚೌಕಟ್ಟು->extended_buf);
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
        ಚೌಕಟ್ಟು->nb_extended_buf = planes - AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು;
    } ಇಲ್ಲದಿದ್ದರೆ
        ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ;

    ಆದರೆ (ಚೌಕಟ್ಟು->linesize[0] > SIZE_MAX - align)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    ಗಾತ್ರ_2 = ಚೌಕಟ್ಟು->linesize[0] + (size_t)align;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FFMIN(planes, AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು); i++) {
        ಚೌಕಟ್ಟು->buf[i] = av_ಬಫರ್_alloc(ಗಾತ್ರ_2);
        ಆದರೆ (!ಚೌಕಟ್ಟು->buf[i]) {
            av_ಚೌಕಟ್ಟು_unref(ಚೌಕಟ್ಟು);
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
        ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ[i] = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i] =
            (uint8_t *)FFALIGN((uintptr_t)ಚೌಕಟ್ಟು->buf[i]->ದತ್ತಾಂಶ, align);
    }
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes - AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು; i++) {
        ಚೌಕಟ್ಟು->extended_buf[i] = av_ಬಫರ್_alloc(ಗಾತ್ರ_2);
        ಆದರೆ (!ಚೌಕಟ್ಟು->extended_buf[i]) {
            av_ಚೌಕಟ್ಟು_unref(ಚೌಕಟ್ಟು);
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
        ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ[i + AV_ಅಂಕೆ_ದತ್ತಾಂಶ_ಸೂಚಕಗಳು] =
            (uint8_t *)FFALIGN((uintptr_t)ಚೌಕಟ್ಟು->extended_buf[i]->ದತ್ತಾಂಶ, align);
    }
    ಹಿಂತಿರುಗಿ 0;

}

ಪೂರ್ಣಾಂಕ av_ಚೌಕಟ್ಟು_get_ಬಫರ್(AVFrame *ಚೌಕಟ್ಟು, ಪೂರ್ಣಾಂಕ align)
{
    ಆದರೆ (ಚೌಕಟ್ಟು->format < 0)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (ಚೌಕಟ್ಟು->ಅಗಲ > 0 && ಚೌಕಟ್ಟು->ಎತ್ತರ > 0)
        ಹಿಂತಿರುಗಿ ff_ಚೌಕಟ್ಟು_get_video_ಬಫರ್(ಚೌಕಟ್ಟು, align, ಖಾಲಿ, ಖಾಲಿ);
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಚೌಕಟ್ಟು->nb_samples > 0 &&
             (av_channel_layout_check(&ಚೌಕಟ್ಟು->ch_layout)))
        ಹಿಂತಿರುಗಿ get_audio_ಬಫರ್(ಚೌಕಟ್ಟು, align);

    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_copy_props(AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ಅನುಪಾತ    = src->sample_aspect_ಅನುಪಾತ;
    dst->crop_ತುದಿ               = src->crop_ತುದಿ;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_ಎಡ              = src->crop_ಎಡ;
    dst->crop_ಬಲ             = src->crop_ಬಲ;
    dst->pts                    = src->pts;
    dst->duration               = src->duration;
    dst->repeat_pict            = src->repeat_pict;
    dst->sample_ದರ            = src->sample_ದರ;
    dst->opaque                 = src->opaque;
    dst->pkt_dts                = src->pkt_dts;
    dst->ಸಮಯ_ತಳ              = src->ಸಮಯ_ತಳ;
    dst->quality                = src->quality;
    dst->ಉತ್ತಮ_effort_timestamp  = src->ಉತ್ತಮ_effort_timestamp;
    dst->flags                  = src->flags;
    dst->decode_error_flags     = src->decode_error_flags;
    dst->color_primaries        = src->color_primaries;
    dst->color_trc              = src->color_trc;
    dst->colorspace             = src->colorspace;
    dst->color_range            = src->color_range;
    dst->chroma_location        = src->chroma_location;
    dst->alpha_ಬಹುಲಕ             = src->alpha_ಬಹುಲಕ;

    av_dict_copy(&dst->metadata, src->metadata, 0);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < src->nb_side_ದತ್ತಾಂಶ; i++) {
        ಸ್ಥಿರಾಂಕ AVFrame_Side_ದತ್ತಾಂಶ *sd_src = src->side_ದತ್ತಾಂಶ[i];
        AVFrame_Side_ದತ್ತಾಂಶ *sd_dst;
        ಆದರೆ (   sd_src->type == AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_PANSCAN
            && (src->ಅಗಲ != dst->ಅಗಲ || src->ಎತ್ತರ != dst->ಎತ್ತರ))
            ಮುಂದುವರಿ;
        ಆದರೆ (force_copy) {
            sd_dst = av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ(dst, sd_src->type,
                                            sd_src->ಗಾತ್ರ_2);
            ಆದರೆ (!sd_dst) {
                av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_free(&dst->side_ದತ್ತಾಂಶ, &dst->nb_side_ದತ್ತಾಂಶ);
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            }
            ಸ್ಮರಣೆ_ನಕಲು(sd_dst->ದತ್ತಾಂಶ, sd_src->ದತ್ತಾಂಶ, sd_src->ಗಾತ್ರ_2);
        } ಇಲ್ಲದಿದ್ದರೆ {
            AVBufferRef *ref = av_ಬಫರ್_ref(sd_src->buf);
            sd_dst = av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ_from_buf(dst, sd_src->type, ref);
            ಆದರೆ (!sd_dst) {
                av_ಬಫರ್_unref(&ref);
                av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_free(&dst->side_ದತ್ತಾಂಶ, &dst->nb_side_ದತ್ತಾಂಶ);
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->ಖಾಸಗಿ_ref, src->ಖಾಸಗಿ_ref);
    ಹಿಂತಿರುಗಿ av_ಬಫರ್_replace(&dst->opaque_ref, src->opaque_ref);
}

ಪೂರ್ಣಾಂಕ av_ಚೌಕಟ್ಟು_ref(AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    ಪೂರ್ಣಾಂಕ ret = 0;

    av_assert1(dst->ಅಗಲ == 0 && dst->ಎತ್ತರ == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_UNSPEC);

    dst->format         = src->format;
    dst->ಅಗಲ          = src->ಅಗಲ;
    dst->ಎತ್ತರ         = src->ಎತ್ತರ;
    dst->nb_samples     = src->nb_samples;

    ret = ಚೌಕಟ್ಟು_copy_props(dst, src, 0);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    /* duplicate the frame data if it's not refcounted */
    ಆದರೆ (!src->buf[0]) {
        ret = av_ಚೌಕಟ್ಟು_get_ಬಫರ್(dst, 0);
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;

        ret = av_ಚೌಕಟ್ಟು_copy(dst, src);
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;

        ಹಿಂತಿರುಗಿ 0;
    }

    /* ref the buffers */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ಆದರೆ (!src->buf[i])
            ಮುಂದುವರಿ;
        dst->buf[i] = av_ಬಫರ್_ref(src->buf[i]);
        ಆದರೆ (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }
    }

    ಆದರೆ (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      ಗಾತ್ರ(*dst->extended_buf));
        ಆದರೆ (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_ಬಫರ್_ref(src->extended_buf[i]);
            ಆದರೆ (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                ಹೋಗು fail;
            }
        }
    }

    ಆದರೆ (src->hw_ಚೌಕಟ್ಟುಗಳು_ctx) {
        dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx = av_ಬಫರ್_ref(src->hw_ಚೌಕಟ್ಟುಗಳು_ctx);
        ಆದರೆ (!dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx) {
            ret = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }
    }

    /* duplicate extended data */
    ಆದರೆ (src->extended_ದತ್ತಾಂಶ != src->ದತ್ತಾಂಶ) {
        ಪೂರ್ಣಾಂಕ ch = dst->ch_layout.nb_channels;

        ಆದರೆ (ch <= 0 || ch > SIZE_MAX / ಗಾತ್ರ(*dst->extended_ದತ್ತಾಂಶ)) {
            ret = AVERROR(EINVAL);
            ಹೋಗು fail;
        }

        dst->extended_ದತ್ತಾಂಶ = av_memdup(src->extended_ದತ್ತಾಂಶ, ಗಾತ್ರ(*dst->extended_ದತ್ತಾಂಶ) * ch);
        ಆದರೆ (!dst->extended_ದತ್ತಾಂಶ) {
            ret = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }
    } ಇಲ್ಲದಿದ್ದರೆ
        dst->extended_ದತ್ತಾಂಶ = dst->ದತ್ತಾಂಶ;

    ಸ್ಮರಣೆ_ನಕಲು(dst->ದತ್ತಾಂಶ,     src->ದತ್ತಾಂಶ,     ಗಾತ್ರ(src->ದತ್ತಾಂಶ));
    ಸ್ಮರಣೆ_ನಕಲು(dst->linesize, src->linesize, ಗಾತ್ರ(src->linesize));

    ಹಿಂತಿರುಗಿ 0;

fail:
    av_ಚೌಕಟ್ಟು_unref(dst);
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_ಚೌಕಟ್ಟು_replace(AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    ಪೂರ್ಣಾಂಕ ret = 0;

    ಆದರೆ (dst == src)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (!src->buf[0]) {
        av_ಚೌಕಟ್ಟು_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        ಆದರೆ (   src->ದತ್ತಾಂಶ[0] || src->ದತ್ತಾಂಶ[1]
            || src->ದತ್ತಾಂಶ[2] || src->ದತ್ತಾಂಶ[3])
            ಹಿಂತಿರುಗಿ av_ಚೌಕಟ್ಟು_ref(dst, src);

        ret = ಚೌಕಟ್ಟು_copy_props(dst, src, 0);
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;
    }

    dst->format         = src->format;
    dst->ಅಗಲ          = src->ಅಗಲ;
    dst->ಎತ್ತರ         = src->ಎತ್ತರ;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_free(&dst->side_ದತ್ತಾಂಶ, &dst->nb_side_ದತ್ತಾಂಶ);
    av_dict_free(&dst->metadata);
    ret = ಚೌಕಟ್ಟು_copy_props(dst, src, 0);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    /* replace the buffers */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_ಬಫರ್_replace(&dst->buf[i], src->buf[i]);
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;
    }

    ಆದರೆ (src->extended_buf) {
        ಆದರೆ (dst->nb_extended_buf != src->nb_extended_buf) {
            ಪೂರ್ಣಾಂಕ nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            ಶೂನ್ಯ *tmp;

            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_ಬಫರ್_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   ಗಾತ್ರ(*dst->extended_buf));
            ಆದರೆ (!tmp) {
                ret = AVERROR(ENOMEM);
                ಹೋಗು fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * ಗಾತ್ರ(*dst->extended_buf));
        }

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < src->nb_extended_buf; i++) {
            ret = av_ಬಫರ್_replace(&dst->extended_buf[i], src->extended_buf[i]);
            ಆದರೆ (ret < 0)
                ಹೋಗು fail;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dst->extended_buf) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < dst->nb_extended_buf; i++)
            av_ಬಫರ್_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_ಬಫರ್_replace(&dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx, src->hw_ಚೌಕಟ್ಟುಗಳು_ctx);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    ಆದರೆ (dst->extended_ದತ್ತಾಂಶ != dst->ದತ್ತಾಂಶ)
        av_freep(&dst->extended_ದತ್ತಾಂಶ);

    ಆದರೆ (src->extended_ದತ್ತಾಂಶ != src->ದತ್ತಾಂಶ) {
        ಪೂರ್ಣಾಂಕ ch = dst->ch_layout.nb_channels;

        ಆದರೆ (ch <= 0 || ch > SIZE_MAX / ಗಾತ್ರ(*dst->extended_ದತ್ತಾಂಶ)) {
            ret = AVERROR(EINVAL);
            ಹೋಗು fail;
        }

        dst->extended_ದತ್ತಾಂಶ = av_memdup(src->extended_ದತ್ತಾಂಶ, ಗಾತ್ರ(*dst->extended_ದತ್ತಾಂಶ) * ch);
        ಆದರೆ (!dst->extended_ದತ್ತಾಂಶ) {
            ret = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }
    } ಇಲ್ಲದಿದ್ದರೆ
        dst->extended_ದತ್ತಾಂಶ = dst->ದತ್ತಾಂಶ;

    ಸ್ಮರಣೆ_ನಕಲು(dst->ದತ್ತಾಂಶ,     src->ದತ್ತಾಂಶ,     ಗಾತ್ರ(src->ದತ್ತಾಂಶ));
    ಸ್ಮರಣೆ_ನಕಲು(dst->linesize, src->linesize, ಗಾತ್ರ(src->linesize));

    ಹಿಂತಿರುಗಿ 0;

fail:
    av_ಚೌಕಟ್ಟು_unref(dst);
    ಹಿಂತಿರುಗಿ ret;
}

AVFrame *av_ಚೌಕಟ್ಟು_clone(ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    AVFrame *ret = av_ಚೌಕಟ್ಟು_alloc();

    ಆದರೆ (!ret)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಆದರೆ (av_ಚೌಕಟ್ಟು_ref(ret, src) < 0)
        av_ಚೌಕಟ್ಟು_free(&ret);

    ಹಿಂತಿರುಗಿ ret;
}

ಶೂನ್ಯ av_ಚೌಕಟ್ಟು_unref(AVFrame *ಚೌಕಟ್ಟು)
{
    ಆದರೆ (!ಚೌಕಟ್ಟು)
        ಹಿಂತಿರುಗಿ;

    av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_free(&ಚೌಕಟ್ಟು->side_ದತ್ತಾಂಶ, &ಚೌಕಟ್ಟು->nb_side_ದತ್ತಾಂಶ);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(ಚೌಕಟ್ಟು->buf); i++)
        av_ಬಫರ್_unref(&ಚೌಕಟ್ಟು->buf[i]);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಚೌಕಟ್ಟು->nb_extended_buf; i++)
        av_ಬಫರ್_unref(&ಚೌಕಟ್ಟು->extended_buf[i]);
    av_freep(&ಚೌಕಟ್ಟು->extended_buf);
    av_dict_free(&ಚೌಕಟ್ಟು->metadata);

    av_ಬಫರ್_unref(&ಚೌಕಟ್ಟು->hw_ಚೌಕಟ್ಟುಗಳು_ctx);

    av_ಬಫರ್_unref(&ಚೌಕಟ್ಟು->opaque_ref);
    av_refstruct_unref(&ಚೌಕಟ್ಟು->ಖಾಸಗಿ_ref);

    ಆದರೆ (ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ != ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ)
        av_freep(&ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ);

    av_channel_layout_uninit(&ಚೌಕಟ್ಟು->ch_layout);

    get_ಚೌಕಟ್ಟು_defaults(ಚೌಕಟ್ಟು);
}

ಶೂನ್ಯ av_ಚೌಕಟ್ಟು_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->ಅಗಲ == 0 && dst->ಎತ್ತರ == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_UNSPEC);

    *dst = *src;
    ಆದರೆ (src->extended_ದತ್ತಾಂಶ == src->ದತ್ತಾಂಶ)
        dst->extended_ದತ್ತಾಂಶ = dst->ದತ್ತಾಂಶ;
    get_ಚೌಕಟ್ಟು_defaults(src);
}

ಪೂರ್ಣಾಂಕ av_ಚೌಕಟ್ಟು_is_writable(AVFrame *ಚೌಕಟ್ಟು)
{
    ಪೂರ್ಣಾಂಕ ret = 1;

    /* assume non-refcounted frames are not writable */
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0])
        ಹಿಂತಿರುಗಿ 0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(ಚೌಕಟ್ಟು->buf); i++)
        ಆದರೆ (ಚೌಕಟ್ಟು->buf[i])
            ret &= !!av_ಬಫರ್_is_writable(ಚೌಕಟ್ಟು->buf[i]);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಚೌಕಟ್ಟು->nb_extended_buf; i++)
        ret &= !!av_ಬಫರ್_is_writable(ಚೌಕಟ್ಟು->extended_buf[i]);

    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_ಚೌಕಟ್ಟು_make_writable(AVFrame *ಚೌಕಟ್ಟು)
{
    AVFrame tmp;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (av_ಚೌಕಟ್ಟು_is_writable(ಚೌಕಟ್ಟು))
        ಹಿಂತಿರುಗಿ 0;

    memset(&tmp, 0, ಗಾತ್ರ(tmp));
    tmp.format         = ಚೌಕಟ್ಟು->format;
    tmp.ಅಗಲ          = ಚೌಕಟ್ಟು->ಅಗಲ;
    tmp.ಎತ್ತರ         = ಚೌಕಟ್ಟು->ಎತ್ತರ;
    tmp.nb_samples     = ಚೌಕಟ್ಟು->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &ಚೌಕಟ್ಟು->ch_layout);
    ಆದರೆ (ret < 0) {
        av_ಚೌಕಟ್ಟು_unref(&tmp);
        ಹಿಂತಿರುಗಿ ret;
    }

    ಆದರೆ (ಚೌಕಟ್ಟು->hw_ಚೌಕಟ್ಟುಗಳು_ctx)
        ret = av_hwframe_get_ಬಫರ್(ಚೌಕಟ್ಟು->hw_ಚೌಕಟ್ಟುಗಳು_ctx, &tmp, 0);
    ಇಲ್ಲದಿದ್ದರೆ
        ret = av_ಚೌಕಟ್ಟು_get_ಬಫರ್(&tmp, 0);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ret = av_ಚೌಕಟ್ಟು_copy(&tmp, ಚೌಕಟ್ಟು);
    ಆದರೆ (ret < 0) {
        av_ಚೌಕಟ್ಟು_unref(&tmp);
        ಹಿಂತಿರುಗಿ ret;
    }

    ret = av_ಚೌಕಟ್ಟು_copy_props(&tmp, ಚೌಕಟ್ಟು);
    ಆದರೆ (ret < 0) {
        av_ಚೌಕಟ್ಟು_unref(&tmp);
        ಹಿಂತಿರುಗಿ ret;
    }

    av_ಚೌಕಟ್ಟು_unref(ಚೌಕಟ್ಟು);

    *ಚೌಕಟ್ಟು = tmp;
    ಆದರೆ (tmp.ದತ್ತಾಂಶ == tmp.extended_ದತ್ತಾಂಶ)
        ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_ಚೌಕಟ್ಟು_copy_props(AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    ಹಿಂತಿರುಗಿ ಚೌಕಟ್ಟು_copy_props(dst, src, 1);
}

AVBufferRef *av_ಚೌಕಟ್ಟು_get_plane_ಬಫರ್(ಸ್ಥಿರಾಂಕ AVFrame *ಚೌಕಟ್ಟು, ಪೂರ್ಣಾಂಕ plane)
{
    uintptr_t ದತ್ತಾಂಶ;
    ಪೂರ್ಣಾಂಕ planes;

    ಆದರೆ (ಚೌಕಟ್ಟು->nb_samples) {
        ಪೂರ್ಣಾಂಕ channels = ಚೌಕಟ್ಟು->ch_layout.nb_channels;
        ಆದರೆ (!channels)
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        planes = av_sample_fmt_is_planar(ಚೌಕಟ್ಟು->format) ? channels : 1;
    } ಇಲ್ಲದಿದ್ದರೆ
        planes = 4;

    ಆದರೆ (plane < 0 || plane >= planes || !ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ[plane])
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ದತ್ತಾಂಶ = (uintptr_t)ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ[plane];

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(ಚೌಕಟ್ಟು->buf) && ಚೌಕಟ್ಟು->buf[i]; i++) {
        AVBufferRef *buf = ಚೌಕಟ್ಟು->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->ದತ್ತಾಂಶ;

        ಆದರೆ (ದತ್ತಾಂಶ >= buf_begin && ದತ್ತಾಂಶ < buf_begin + buf->ಗಾತ್ರ_2)
            ಹಿಂತಿರುಗಿ buf;
    }
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಚೌಕಟ್ಟು->nb_extended_buf; i++) {
        AVBufferRef *buf = ಚೌಕಟ್ಟು->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->ದತ್ತಾಂಶ;

        ಆದರೆ (ದತ್ತಾಂಶ >= buf_begin && ದತ್ತಾಂಶ < buf_begin + buf->ಗಾತ್ರ_2)
            ಹಿಂತಿರುಗಿ buf;
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

AVFrame_Side_ದತ್ತಾಂಶ *av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ_from_buf(AVFrame *ಚೌಕಟ್ಟು,
                                                 ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type type,
                                                 AVBufferRef *buf)
{
    ಹಿಂತಿರುಗಿ
        ff_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_ಕೂಡಿಸು_from_buf(
            &ಚೌಕಟ್ಟು->side_ದತ್ತಾಂಶ, &ಚೌಕಟ್ಟು->nb_side_ದತ್ತಾಂಶ, type, buf);
}

AVFrame_Side_ದತ್ತಾಂಶ *av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು,
                                        ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type type,
                                        size_t ಗಾತ್ರ_2)
{
    AVFrame_Side_ದತ್ತಾಂಶ *ret;
    AVBufferRef *buf = av_ಬಫರ್_alloc(ಗಾತ್ರ_2);
    ret = av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ_from_buf(ಚೌಕಟ್ಟು, type, buf);
    ಆದರೆ (!ret)
        av_ಬಫರ್_unref(&buf);
    ಹಿಂತಿರುಗಿ ret;
}

AVFrame_Side_ದತ್ತಾಂಶ *av_ಚೌಕಟ್ಟು_get_side_ದತ್ತಾಂಶ(ಸ್ಥಿರಾಂಕ AVFrame *ಚೌಕಟ್ಟು,
                                        ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type type)
{
    ಹಿಂತಿರುಗಿ (AVFrame_Side_ದತ್ತಾಂಶ *)av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_get(
        ಚೌಕಟ್ಟು->side_ದತ್ತಾಂಶ, ಚೌಕಟ್ಟು->nb_side_ದತ್ತಾಂಶ,
        type
    );
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_copy_video(AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    ಪೂರ್ಣಾಂಕ planes;

    ಆದರೆ (dst->ಅಗಲ  < src->ಅಗಲ ||
        dst->ಎತ್ತರ < src->ಎತ್ತರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (src->hw_ಚೌಕಟ್ಟುಗಳು_ctx || dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx)
        ಹಿಂತಿರುಗಿ av_hwframe_transfer_ದತ್ತಾಂಶ(dst, src, 0);

    planes = av_pix_fmt_ಎಣಿಕೆ_planes(dst->format);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++)
        ಆದರೆ (!dst->ದತ್ತಾಂಶ[i] || !src->ದತ್ತಾಂಶ[i])
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    av_image_copy2(dst->ದತ್ತಾಂಶ, dst->linesize,
                   src->ದತ್ತಾಂಶ, src->linesize,
                   dst->format, src->ಅಗಲ, src->ಎತ್ತರ);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_copy_audio(AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    ಪೂರ್ಣಾಂಕ planar   = av_sample_fmt_is_planar(dst->format);
    ಪೂರ್ಣಾಂಕ channels = dst->ch_layout.nb_channels;
    ಪೂರ್ಣಾಂಕ planes   = planar ? channels : 1;

    ಆದರೆ (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < planes; i++)
        ಆದರೆ (!dst->extended_ದತ್ತಾಂಶ[i] || !src->extended_ದತ್ತಾಂಶ[i])
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    av_samples_copy(dst->extended_ದತ್ತಾಂಶ, src->extended_ದತ್ತಾಂಶ, 0, 0,
                    dst->nb_samples, channels, dst->format);

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_ಚೌಕಟ್ಟು_copy(AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    ಆದರೆ (dst->format != src->format || dst->format < 0)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (dst->ಅಗಲ > 0 && dst->ಎತ್ತರ > 0)
        ಹಿಂತಿರುಗಿ ಚೌಕಟ್ಟು_copy_video(dst, src);
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        ಹಿಂತಿರುಗಿ ಚೌಕಟ್ಟು_copy_audio(dst, src);

    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಶೂನ್ಯ av_ಚೌಕಟ್ಟು_remove_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು, ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type type)
{
    av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_remove(&ಚೌಕಟ್ಟು->side_ದತ್ತಾಂಶ, &ಚೌಕಟ್ಟು->nb_side_ದತ್ತಾಂಶ, type);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ calc_cropping_offsets(size_t offsets[4], ಸ್ಥಿರಾಂಕ AVFrame *ಚೌಕಟ್ಟು,
                                 ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i]; i++) {
        ಸ್ಥಿರಾಂಕ AVComponentDescriptor *comp = ಖಾಲಿ;
        ಪೂರ್ಣಾಂಕ ಸರಿಸು_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        ಪೂರ್ಣಾಂಕ ಸರಿಸು_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        ಆದರೆ (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            ನಿಲ್ಲಿಸು;
        }

        /* find any component descriptor for this plane */
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < desc->nb_components; j++) {
            ಆದರೆ (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (!comp)
            ಹಿಂತಿರುಗಿ AVERROR_BUG;

        offsets[i] = (ಚೌಕಟ್ಟು->crop_ತುದಿ  >> ಸರಿಸು_y) * ಚೌಕಟ್ಟು->linesize[i] +
                     (ಚೌಕಟ್ಟು->crop_ಎಡ >> ಸರಿಸು_x) * comp->ಹೆಜ್ಜೆ;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_ಚೌಕಟ್ಟು_apply_cropping(AVFrame *ಚೌಕಟ್ಟು, ಪೂರ್ಣಾಂಕ flags)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc;
    size_t offsets[4];
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!(ಚೌಕಟ್ಟು->ಅಗಲ > 0 && ಚೌಕಟ್ಟು->ಎತ್ತರ > 0))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (ಚೌಕಟ್ಟು->crop_ಎಡ >= ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ - ಚೌಕಟ್ಟು->crop_ಬಲ        ||
        ಚೌಕಟ್ಟು->crop_ತುದಿ  >= ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ - ಚೌಕಟ್ಟು->crop_bottom       ||
        (ಚೌಕಟ್ಟು->crop_ಎಡ + ಚೌಕಟ್ಟು->crop_ಬಲ) >= ಚೌಕಟ್ಟು->ಅಗಲ ||
        (ಚೌಕಟ್ಟು->crop_ತುದಿ + ಚೌಕಟ್ಟು->crop_bottom) >= ಚೌಕಟ್ಟು->ಎತ್ತರ)
        ಹಿಂತಿರುಗಿ AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(ಚೌಕಟ್ಟು->format);
    ಆದರೆ (!desc)
        ಹಿಂತಿರುಗಿ AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    ಆದರೆ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        ಚೌಕಟ್ಟು->ಅಗಲ      -= ಚೌಕಟ್ಟು->crop_ಬಲ;
        ಚೌಕಟ್ಟು->ಎತ್ತರ     -= ಚೌಕಟ್ಟು->crop_bottom;
        ಚೌಕಟ್ಟು->crop_ಬಲ  = 0;
        ಚೌಕಟ್ಟು->crop_bottom = 0;
        ಹಿಂತಿರುಗಿ 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, ಚೌಕಟ್ಟು, desc);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    /* adjust the offsets to avoid breaking alignment */
    ಆದರೆ (!(flags & AV_ಚೌಕಟ್ಟು_CROP_UNALIGNED)) {
        ಪೂರ್ಣಾಂಕ log2_crop_align = ಚೌಕಟ್ಟು->crop_ಎಡ ? ff_ctz(ಚೌಕಟ್ಟು->crop_ಎಡ) : ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;
        ಪೂರ್ಣಾಂಕ min_log2_align = ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i]; i++) {
            ಪೂರ್ಣಾಂಕ log2_align = offsets[i] ? ff_ctz(offsets[i]) : ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        ಆದರೆ (min_log2_align < 5 && log2_crop_align != ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ) {
            ಚೌಕಟ್ಟು->crop_ಎಡ &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, ಚೌಕಟ್ಟು, desc);
            ಆದರೆ (ret < 0)
                ಹಿಂತಿರುಗಿ ret;
        }
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i]; i++)
        ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i] += offsets[i];

    ಚೌಕಟ್ಟು->ಅಗಲ      -= (ಚೌಕಟ್ಟು->crop_ಎಡ + ಚೌಕಟ್ಟು->crop_ಬಲ);
    ಚೌಕಟ್ಟು->ಎತ್ತರ     -= (ಚೌಕಟ್ಟು->crop_ತುದಿ  + ಚೌಕಟ್ಟು->crop_bottom);
    ಚೌಕಟ್ಟು->crop_ಎಡ   = 0;
    ಚೌಕಟ್ಟು->crop_ಬಲ  = 0;
    ಚೌಕಟ್ಟು->crop_ತುದಿ    = 0;
    ಚೌಕಟ್ಟು->crop_bottom = 0;

    ಹಿಂತಿರುಗಿ 0;
}
