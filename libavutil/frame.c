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

#ਅਨ੍ਤਰ੍ਭਾਵ "channel_layout.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "dict.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "frame_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "imgutils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "refstruct.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "samplefmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "side_data.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"

ਸਥਿਰ ਖਾਲੀ get_ਚੌਖਟਾ_defaults(AVFrame *ਚੌਖਟਾ)
{
    memset(ਚੌਖਟਾ, 0, ਆਕਾਰ(*ਚੌਖਟਾ));

    ਚੌਖਟਾ->pts                   =
    ਚੌਖਟਾ->pkt_dts               = AV_NOPTS_ਮੁੱਲ;
    ਚੌਖਟਾ->ਉੱਤਮ_effort_timestamp = AV_NOPTS_ਮੁੱਲ;
    ਚੌਖਟਾ->duration            = 0;
    ਚੌਖਟਾ->ਸਮਾਂ_ਅਧਾਰ           = (AVRational){ 0, 1 };
    ਚੌਖਟਾ->sample_aspect_ਅਨੁਪਾਤ = (AVRational){ 0, 1 };
    ਚੌਖਟਾ->format              = -1; /* unknown */
    ਚੌਖਟਾ->extended_ਅੰਕੜੇ       = ਚੌਖਟਾ->ਅੰਕੜੇ;
    ਚੌਖਟਾ->color_primaries     = AVCOL_PRI_UNSPECIFIED;
    ਚੌਖਟਾ->color_trc           = AVCOL_TRC_UNSPECIFIED;
    ਚੌਖਟਾ->colorspace          = AVCOL_SPC_UNSPECIFIED;
    ਚੌਖਟਾ->color_range         = AVCOL_RANGE_UNSPECIFIED;
    ਚੌਖਟਾ->chroma_location     = AVCHROMA_LOC_UNSPECIFIED;
    ਚੌਖਟਾ->alpha_ਬਹੁਲਕ          = AVALPHA_ਬਹੁਲਕ_UNSPECIFIED;
    ਚੌਖਟਾ->flags               = 0;
}

AVFrame *av_ਚੌਖਟਾ_alloc(ਖਾਲੀ)
{
    AVFrame *ਚੌਖਟਾ = av_malloc(ਆਕਾਰ(*ਚੌਖਟਾ));

    ਜੇ (!ਚੌਖਟਾ)
        ਵਾਪਸ ਨਿਰਾ;

    get_ਚੌਖਟਾ_defaults(ਚੌਖਟਾ);

    ਵਾਪਸ ਚੌਖਟਾ;
}

ਖਾਲੀ av_ਚੌਖਟਾ_free(AVFrame **ਚੌਖਟਾ)
{
    ਜੇ (!ਚੌਖਟਾ || !*ਚੌਖਟਾ)
        ਵਾਪਸ;

    av_ਚੌਖਟਾ_unref(*ਚੌਖਟਾ);
    av_freep(ਚੌਖਟਾ);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

ਪੂਰਨ ff_ਚੌਖਟਾ_get_video_ਬਫਰ(AVFrame *ਚੌਖਟਾ, ਪੂਰਨ align,
                              AVBufferRef *(*alloc)(ਖਾਲੀ *opaque, size_t ਮਾਪ),
                              ਖਾਲੀ *opaque)
{
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ਚੌਖਟਾ->format);
    ਪੂਰਨ ret, padded_ਉਚਾਈ;
    ਪੂਰਨ plane_padding;
    ptrdiff_t linesizes[4];
    size_t ਕੁੱਲ_ਮਾਪ, sizes[4];

    ਜੇ (!desc)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ ((ret = av_image_check_ਮਾਪ(ਚੌਖਟਾ->ਚੌੜਾਈ, ਚੌਖਟਾ->ਉਚਾਈ, 0, ਨਿਰਾ)) < 0)
        ਵਾਪਸ ret;

    ਜੇ (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    ਜੇ (!ਚੌਖਟਾ->linesize[0]) {
        ਲਈ (ਪੂਰਨ i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(ਚੌਖਟਾ->linesize, ਚੌਖਟਾ->format,
                                          FFALIGN(ਚੌਖਟਾ->ਚੌੜਾਈ, i));
            ਜੇ (ret < 0)
                ਵਾਪਸ ret;
            ਜੇ (!(ਚੌਖਟਾ->linesize[0] & (align-1)))
                ਰੋਕੋ;
        }

        ਲਈ (ਪੂਰਨ i = 0; i < 4 && ਚੌਖਟਾ->linesize[i]; i++)
            ਚੌਖਟਾ->linesize[i] = FFALIGN(ਚੌਖਟਾ->linesize[i], align);
    }

    ਲਈ (ਪੂਰਨ i = 0; i < 4; i++)
        linesizes[i] = ਚੌਖਟਾ->linesize[i];

    padded_ਉਚਾਈ = FFALIGN(ਚੌਖਟਾ->ਉਚਾਈ, 32);
    ਜੇ ((ret = av_image_fill_plane_sizes(sizes, ਚੌਖਟਾ->format,
                                         padded_ਉਚਾਈ, linesizes)) < 0)
        ਵਾਪਸ ret;

    ਕੁੱਲ_ਮਾਪ = 4 * plane_padding + 4 * align;
    ਲਈ (ਪੂਰਨ i = 0; i < 4; i++) {
        ਜੇ (sizes[i] > SIZE_MAX - ਕੁੱਲ_ਮਾਪ)
            ਵਾਪਸ AVERROR(EINVAL);
        ਕੁੱਲ_ਮਾਪ += sizes[i];
    }

    ਚੌਖਟਾ->buf[0] = alloc ? alloc(opaque, ਕੁੱਲ_ਮਾਪ) : av_ਬਫਰ_alloc(ਕੁੱਲ_ਮਾਪ);
    ਜੇ (!ਚੌਖਟਾ->buf[0]) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    ਜੇ ((ret = av_image_fill_ਸੂਚਕ_ਸਾਰੇ(ਚੌਖਟਾ->ਅੰਕੜੇ, ਚੌਖਟਾ->format, padded_ਉਚਾਈ,
                                      ਚੌਖਟਾ->buf[0]->ਅੰਕੜੇ, ਚੌਖਟਾ->linesize)) < 0)
        ਜਾਓ fail;

    ਲਈ (ਪੂਰਨ i = 1; i < 4; i++) {
        ਜੇ (ਚੌਖਟਾ->ਅੰਕੜੇ[i])
            ਚੌਖਟਾ->ਅੰਕੜੇ[i] += i * plane_padding;
        ਚੌਖਟਾ->ਅੰਕੜੇ[i] = (uint8_t *)FFALIGN((uintptr_t)ਚੌਖਟਾ->ਅੰਕੜੇ[i], align);
    }

    ਚੌਖਟਾ->extended_ਅੰਕੜੇ = ਚੌਖਟਾ->ਅੰਕੜੇ;

    ਵਾਪਸ 0;
fail:
    av_ਚੌਖਟਾ_unref(ਚੌਖਟਾ);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ get_audio_ਬਫਰ(AVFrame *ਚੌਖਟਾ, ਪੂਰਨ align)
{
    ਪੂਰਨ planar   = av_sample_fmt_is_planar(ਚੌਖਟਾ->format);
    ਪੂਰਨ channels, planes;
    size_t ਮਾਪ;
    ਪੂਰਨ ret;

    channels = ਚੌਖਟਾ->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    ਜੇ (!ਚੌਖਟਾ->linesize[0]) {
        ret = av_samples_get_ਬਫਰ_ਮਾਪ(&ਚੌਖਟਾ->linesize[0], channels,
                                         ਚੌਖਟਾ->nb_samples, ਚੌਖਟਾ->format,
                                         align);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
    }

    ਜੇ (align <= 0)
        align = ALIGN;

    ਜੇ (planes > AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ) {
        ਚੌਖਟਾ->extended_ਅੰਕੜੇ = av_calloc(planes,
                                          ਆਕਾਰ(*ਚੌਖਟਾ->extended_ਅੰਕੜੇ));
        ਚੌਖਟਾ->extended_buf  = av_calloc(planes - AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ,
                                          ਆਕਾਰ(*ਚੌਖਟਾ->extended_buf));
        ਜੇ (!ਚੌਖਟਾ->extended_ਅੰਕੜੇ || !ਚੌਖਟਾ->extended_buf) {
            av_freep(&ਚੌਖਟਾ->extended_ਅੰਕੜੇ);
            av_freep(&ਚੌਖਟਾ->extended_buf);
            ਵਾਪਸ AVERROR(ENOMEM);
        }
        ਚੌਖਟਾ->nb_extended_buf = planes - AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ;
    } ਨਹੀਂਤਾਂ
        ਚੌਖਟਾ->extended_ਅੰਕੜੇ = ਚੌਖਟਾ->ਅੰਕੜੇ;

    ਜੇ (ਚੌਖਟਾ->linesize[0] > SIZE_MAX - align)
        ਵਾਪਸ AVERROR(EINVAL);
    ਮਾਪ = ਚੌਖਟਾ->linesize[0] + (size_t)align;

    ਲਈ (ਪੂਰਨ i = 0; i < FFMIN(planes, AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ); i++) {
        ਚੌਖਟਾ->buf[i] = av_ਬਫਰ_alloc(ਮਾਪ);
        ਜੇ (!ਚੌਖਟਾ->buf[i]) {
            av_ਚੌਖਟਾ_unref(ਚੌਖਟਾ);
            ਵਾਪਸ AVERROR(ENOMEM);
        }
        ਚੌਖਟਾ->extended_ਅੰਕੜੇ[i] = ਚੌਖਟਾ->ਅੰਕੜੇ[i] =
            (uint8_t *)FFALIGN((uintptr_t)ਚੌਖਟਾ->buf[i]->ਅੰਕੜੇ, align);
    }
    ਲਈ (ਪੂਰਨ i = 0; i < planes - AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ; i++) {
        ਚੌਖਟਾ->extended_buf[i] = av_ਬਫਰ_alloc(ਮਾਪ);
        ਜੇ (!ਚੌਖਟਾ->extended_buf[i]) {
            av_ਚੌਖਟਾ_unref(ਚੌਖਟਾ);
            ਵਾਪਸ AVERROR(ENOMEM);
        }
        ਚੌਖਟਾ->extended_ਅੰਕੜੇ[i + AV_ਅੰਕ_ਅੰਕੜੇ_ਸੂਚਕ_ਸਾਰੇ] =
            (uint8_t *)FFALIGN((uintptr_t)ਚੌਖਟਾ->extended_buf[i]->ਅੰਕੜੇ, align);
    }
    ਵਾਪਸ 0;

}

ਪੂਰਨ av_ਚੌਖਟਾ_get_ਬਫਰ(AVFrame *ਚੌਖਟਾ, ਪੂਰਨ align)
{
    ਜੇ (ਚੌਖਟਾ->format < 0)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (ਚੌਖਟਾ->ਚੌੜਾਈ > 0 && ਚੌਖਟਾ->ਉਚਾਈ > 0)
        ਵਾਪਸ ff_ਚੌਖਟਾ_get_video_ਬਫਰ(ਚੌਖਟਾ, align, ਨਿਰਾ, ਨਿਰਾ);
    ਨਹੀਂਤਾਂ ਜੇ (ਚੌਖਟਾ->nb_samples > 0 &&
             (av_channel_layout_check(&ਚੌਖਟਾ->ch_layout)))
        ਵਾਪਸ get_audio_ਬਫਰ(ਚੌਖਟਾ, align);

    ਵਾਪਸ AVERROR(EINVAL);
}

ਸਥਿਰ ਪੂਰਨ ਚੌਖਟਾ_copy_props(AVFrame *dst, ਅਚਲ AVFrame *src, ਪੂਰਨ force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ਅਨੁਪਾਤ    = src->sample_aspect_ਅਨੁਪਾਤ;
    dst->crop_ਸਿਖਰ               = src->crop_ਸਿਖਰ;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_ਖੱਬਾ              = src->crop_ਖੱਬਾ;
    dst->crop_ਸੱਜਾ             = src->crop_ਸੱਜਾ;
    dst->pts                    = src->pts;
    dst->duration               = src->duration;
    dst->repeat_pict            = src->repeat_pict;
    dst->sample_ਦਰ            = src->sample_ਦਰ;
    dst->opaque                 = src->opaque;
    dst->pkt_dts                = src->pkt_dts;
    dst->ਸਮਾਂ_ਅਧਾਰ              = src->ਸਮਾਂ_ਅਧਾਰ;
    dst->quality                = src->quality;
    dst->ਉੱਤਮ_effort_timestamp  = src->ਉੱਤਮ_effort_timestamp;
    dst->flags                  = src->flags;
    dst->decode_error_flags     = src->decode_error_flags;
    dst->color_primaries        = src->color_primaries;
    dst->color_trc              = src->color_trc;
    dst->colorspace             = src->colorspace;
    dst->color_range            = src->color_range;
    dst->chroma_location        = src->chroma_location;
    dst->alpha_ਬਹੁਲਕ             = src->alpha_ਬਹੁਲਕ;

    av_dict_copy(&dst->metadata, src->metadata, 0);

    ਲਈ (ਪੂਰਨ i = 0; i < src->nb_side_ਅੰਕੜੇ; i++) {
        ਅਚਲ AVFrame_Side_ਅੰਕੜੇ *sd_src = src->side_ਅੰਕੜੇ[i];
        AVFrame_Side_ਅੰਕੜੇ *sd_dst;
        ਜੇ (   sd_src->type == AV_ਚੌਖਟਾ_ਅੰਕੜੇ_PANSCAN
            && (src->ਚੌੜਾਈ != dst->ਚੌੜਾਈ || src->ਉਚਾਈ != dst->ਉਚਾਈ))
            ਜਾਰੀ;
        ਜੇ (force_copy) {
            sd_dst = av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ(dst, sd_src->type,
                                            sd_src->ਮਾਪ);
            ਜੇ (!sd_dst) {
                av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_free(&dst->side_ਅੰਕੜੇ, &dst->nb_side_ਅੰਕੜੇ);
                ਵਾਪਸ AVERROR(ENOMEM);
            }
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(sd_dst->ਅੰਕੜੇ, sd_src->ਅੰਕੜੇ, sd_src->ਮਾਪ);
        } ਨਹੀਂਤਾਂ {
            AVBufferRef *ref = av_ਬਫਰ_ref(sd_src->buf);
            sd_dst = av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ_from_buf(dst, sd_src->type, ref);
            ਜੇ (!sd_dst) {
                av_ਬਫਰ_unref(&ref);
                av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_free(&dst->side_ਅੰਕੜੇ, &dst->nb_side_ਅੰਕੜੇ);
                ਵਾਪਸ AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->ਨਿੱਜੀ_ref, src->ਨਿੱਜੀ_ref);
    ਵਾਪਸ av_ਬਫਰ_replace(&dst->opaque_ref, src->opaque_ref);
}

ਪੂਰਨ av_ਚੌਖਟਾ_ref(AVFrame *dst, ਅਚਲ AVFrame *src)
{
    ਪੂਰਨ ret = 0;

    av_assert1(dst->ਚੌੜਾਈ == 0 && dst->ਉਚਾਈ == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_UNSPEC);

    dst->format         = src->format;
    dst->ਚੌੜਾਈ          = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ         = src->ਉਚਾਈ;
    dst->nb_samples     = src->nb_samples;

    ret = ਚੌਖਟਾ_copy_props(dst, src, 0);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    /* duplicate the frame data if it's not refcounted */
    ਜੇ (!src->buf[0]) {
        ret = av_ਚੌਖਟਾ_get_ਬਫਰ(dst, 0);
        ਜੇ (ret < 0)
            ਜਾਓ fail;

        ret = av_ਚੌਖਟਾ_copy(dst, src);
        ਜੇ (ret < 0)
            ਜਾਓ fail;

        ਵਾਪਸ 0;
    }

    /* ref the buffers */
    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ਜੇ (!src->buf[i])
            ਜਾਰੀ;
        dst->buf[i] = av_ਬਫਰ_ref(src->buf[i]);
        ਜੇ (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            ਜਾਓ fail;
        }
    }

    ਜੇ (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      ਆਕਾਰ(*dst->extended_buf));
        ਜੇ (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            ਜਾਓ fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        ਲਈ (ਪੂਰਨ i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_ਬਫਰ_ref(src->extended_buf[i]);
            ਜੇ (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                ਜਾਓ fail;
            }
        }
    }

    ਜੇ (src->hw_ਚੌਖਟੇ_ctx) {
        dst->hw_ਚੌਖਟੇ_ctx = av_ਬਫਰ_ref(src->hw_ਚੌਖਟੇ_ctx);
        ਜੇ (!dst->hw_ਚੌਖਟੇ_ctx) {
            ret = AVERROR(ENOMEM);
            ਜਾਓ fail;
        }
    }

    /* duplicate extended data */
    ਜੇ (src->extended_ਅੰਕੜੇ != src->ਅੰਕੜੇ) {
        ਪੂਰਨ ch = dst->ch_layout.nb_channels;

        ਜੇ (ch <= 0 || ch > SIZE_MAX / ਆਕਾਰ(*dst->extended_ਅੰਕੜੇ)) {
            ret = AVERROR(EINVAL);
            ਜਾਓ fail;
        }

        dst->extended_ਅੰਕੜੇ = av_memdup(src->extended_ਅੰਕੜੇ, ਆਕਾਰ(*dst->extended_ਅੰਕੜੇ) * ch);
        ਜੇ (!dst->extended_ਅੰਕੜੇ) {
            ret = AVERROR(ENOMEM);
            ਜਾਓ fail;
        }
    } ਨਹੀਂਤਾਂ
        dst->extended_ਅੰਕੜੇ = dst->ਅੰਕੜੇ;

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst->ਅੰਕੜੇ,     src->ਅੰਕੜੇ,     ਆਕਾਰ(src->ਅੰਕੜੇ));
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst->linesize, src->linesize, ਆਕਾਰ(src->linesize));

    ਵਾਪਸ 0;

fail:
    av_ਚੌਖਟਾ_unref(dst);
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_ਚੌਖਟਾ_replace(AVFrame *dst, ਅਚਲ AVFrame *src)
{
    ਪੂਰਨ ret = 0;

    ਜੇ (dst == src)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (!src->buf[0]) {
        av_ਚੌਖਟਾ_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        ਜੇ (   src->ਅੰਕੜੇ[0] || src->ਅੰਕੜੇ[1]
            || src->ਅੰਕੜੇ[2] || src->ਅੰਕੜੇ[3])
            ਵਾਪਸ av_ਚੌਖਟਾ_ref(dst, src);

        ret = ਚੌਖਟਾ_copy_props(dst, src, 0);
        ਜੇ (ret < 0)
            ਜਾਓ fail;
    }

    dst->format         = src->format;
    dst->ਚੌੜਾਈ          = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ         = src->ਉਚਾਈ;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_free(&dst->side_ਅੰਕੜੇ, &dst->nb_side_ਅੰਕੜੇ);
    av_dict_free(&dst->metadata);
    ret = ਚੌਖਟਾ_copy_props(dst, src, 0);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    /* replace the buffers */
    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_ਬਫਰ_replace(&dst->buf[i], src->buf[i]);
        ਜੇ (ret < 0)
            ਜਾਓ fail;
    }

    ਜੇ (src->extended_buf) {
        ਜੇ (dst->nb_extended_buf != src->nb_extended_buf) {
            ਪੂਰਨ nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            ਖਾਲੀ *tmp;

            ਲਈ (ਪੂਰਨ i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_ਬਫਰ_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   ਆਕਾਰ(*dst->extended_buf));
            ਜੇ (!tmp) {
                ret = AVERROR(ENOMEM);
                ਜਾਓ fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * ਆਕਾਰ(*dst->extended_buf));
        }

        ਲਈ (ਪੂਰਨ i = 0; i < src->nb_extended_buf; i++) {
            ret = av_ਬਫਰ_replace(&dst->extended_buf[i], src->extended_buf[i]);
            ਜੇ (ret < 0)
                ਜਾਓ fail;
        }
    } ਨਹੀਂਤਾਂ ਜੇ (dst->extended_buf) {
        ਲਈ (ਪੂਰਨ i = 0; i < dst->nb_extended_buf; i++)
            av_ਬਫਰ_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_ਬਫਰ_replace(&dst->hw_ਚੌਖਟੇ_ctx, src->hw_ਚੌਖਟੇ_ctx);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    ਜੇ (dst->extended_ਅੰਕੜੇ != dst->ਅੰਕੜੇ)
        av_freep(&dst->extended_ਅੰਕੜੇ);

    ਜੇ (src->extended_ਅੰਕੜੇ != src->ਅੰਕੜੇ) {
        ਪੂਰਨ ch = dst->ch_layout.nb_channels;

        ਜੇ (ch <= 0 || ch > SIZE_MAX / ਆਕਾਰ(*dst->extended_ਅੰਕੜੇ)) {
            ret = AVERROR(EINVAL);
            ਜਾਓ fail;
        }

        dst->extended_ਅੰਕੜੇ = av_memdup(src->extended_ਅੰਕੜੇ, ਆਕਾਰ(*dst->extended_ਅੰਕੜੇ) * ch);
        ਜੇ (!dst->extended_ਅੰਕੜੇ) {
            ret = AVERROR(ENOMEM);
            ਜਾਓ fail;
        }
    } ਨਹੀਂਤਾਂ
        dst->extended_ਅੰਕੜੇ = dst->ਅੰਕੜੇ;

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst->ਅੰਕੜੇ,     src->ਅੰਕੜੇ,     ਆਕਾਰ(src->ਅੰਕੜੇ));
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst->linesize, src->linesize, ਆਕਾਰ(src->linesize));

    ਵਾਪਸ 0;

fail:
    av_ਚੌਖਟਾ_unref(dst);
    ਵਾਪਸ ret;
}

AVFrame *av_ਚੌਖਟਾ_clone(ਅਚਲ AVFrame *src)
{
    AVFrame *ret = av_ਚੌਖਟਾ_alloc();

    ਜੇ (!ret)
        ਵਾਪਸ ਨਿਰਾ;

    ਜੇ (av_ਚੌਖਟਾ_ref(ret, src) < 0)
        av_ਚੌਖਟਾ_free(&ret);

    ਵਾਪਸ ret;
}

ਖਾਲੀ av_ਚੌਖਟਾ_unref(AVFrame *ਚੌਖਟਾ)
{
    ਜੇ (!ਚੌਖਟਾ)
        ਵਾਪਸ;

    av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_free(&ਚੌਖਟਾ->side_ਅੰਕੜੇ, &ਚੌਖਟਾ->nb_side_ਅੰਕੜੇ);

    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(ਚੌਖਟਾ->buf); i++)
        av_ਬਫਰ_unref(&ਚੌਖਟਾ->buf[i]);
    ਲਈ (ਪੂਰਨ i = 0; i < ਚੌਖਟਾ->nb_extended_buf; i++)
        av_ਬਫਰ_unref(&ਚੌਖਟਾ->extended_buf[i]);
    av_freep(&ਚੌਖਟਾ->extended_buf);
    av_dict_free(&ਚੌਖਟਾ->metadata);

    av_ਬਫਰ_unref(&ਚੌਖਟਾ->hw_ਚੌਖਟੇ_ctx);

    av_ਬਫਰ_unref(&ਚੌਖਟਾ->opaque_ref);
    av_refstruct_unref(&ਚੌਖਟਾ->ਨਿੱਜੀ_ref);

    ਜੇ (ਚੌਖਟਾ->extended_ਅੰਕੜੇ != ਚੌਖਟਾ->ਅੰਕੜੇ)
        av_freep(&ਚੌਖਟਾ->extended_ਅੰਕੜੇ);

    av_channel_layout_uninit(&ਚੌਖਟਾ->ch_layout);

    get_ਚੌਖਟਾ_defaults(ਚੌਖਟਾ);
}

ਖਾਲੀ av_ਚੌਖਟਾ_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->ਚੌੜਾਈ == 0 && dst->ਉਚਾਈ == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_UNSPEC);

    *dst = *src;
    ਜੇ (src->extended_ਅੰਕੜੇ == src->ਅੰਕੜੇ)
        dst->extended_ਅੰਕੜੇ = dst->ਅੰਕੜੇ;
    get_ਚੌਖਟਾ_defaults(src);
}

ਪੂਰਨ av_ਚੌਖਟਾ_is_writable(AVFrame *ਚੌਖਟਾ)
{
    ਪੂਰਨ ret = 1;

    /* assume non-refcounted frames are not writable */
    ਜੇ (!ਚੌਖਟਾ->buf[0])
        ਵਾਪਸ 0;

    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(ਚੌਖਟਾ->buf); i++)
        ਜੇ (ਚੌਖਟਾ->buf[i])
            ret &= !!av_ਬਫਰ_is_writable(ਚੌਖਟਾ->buf[i]);
    ਲਈ (ਪੂਰਨ i = 0; i < ਚੌਖਟਾ->nb_extended_buf; i++)
        ret &= !!av_ਬਫਰ_is_writable(ਚੌਖਟਾ->extended_buf[i]);

    ਵਾਪਸ ret;
}

ਪੂਰਨ av_ਚੌਖਟਾ_make_writable(AVFrame *ਚੌਖਟਾ)
{
    AVFrame tmp;
    ਪੂਰਨ ret;

    ਜੇ (av_ਚੌਖਟਾ_is_writable(ਚੌਖਟਾ))
        ਵਾਪਸ 0;

    memset(&tmp, 0, ਆਕਾਰ(tmp));
    tmp.format         = ਚੌਖਟਾ->format;
    tmp.ਚੌੜਾਈ          = ਚੌਖਟਾ->ਚੌੜਾਈ;
    tmp.ਉਚਾਈ         = ਚੌਖਟਾ->ਉਚਾਈ;
    tmp.nb_samples     = ਚੌਖਟਾ->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &ਚੌਖਟਾ->ch_layout);
    ਜੇ (ret < 0) {
        av_ਚੌਖਟਾ_unref(&tmp);
        ਵਾਪਸ ret;
    }

    ਜੇ (ਚੌਖਟਾ->hw_ਚੌਖਟੇ_ctx)
        ret = av_hwframe_get_ਬਫਰ(ਚੌਖਟਾ->hw_ਚੌਖਟੇ_ctx, &tmp, 0);
    ਨਹੀਂਤਾਂ
        ret = av_ਚੌਖਟਾ_get_ਬਫਰ(&tmp, 0);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ret = av_ਚੌਖਟਾ_copy(&tmp, ਚੌਖਟਾ);
    ਜੇ (ret < 0) {
        av_ਚੌਖਟਾ_unref(&tmp);
        ਵਾਪਸ ret;
    }

    ret = av_ਚੌਖਟਾ_copy_props(&tmp, ਚੌਖਟਾ);
    ਜੇ (ret < 0) {
        av_ਚੌਖਟਾ_unref(&tmp);
        ਵਾਪਸ ret;
    }

    av_ਚੌਖਟਾ_unref(ਚੌਖਟਾ);

    *ਚੌਖਟਾ = tmp;
    ਜੇ (tmp.ਅੰਕੜੇ == tmp.extended_ਅੰਕੜੇ)
        ਚੌਖਟਾ->extended_ਅੰਕੜੇ = ਚੌਖਟਾ->ਅੰਕੜੇ;

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_ਚੌਖਟਾ_copy_props(AVFrame *dst, ਅਚਲ AVFrame *src)
{
    ਵਾਪਸ ਚੌਖਟਾ_copy_props(dst, src, 1);
}

AVBufferRef *av_ਚੌਖਟਾ_get_plane_ਬਫਰ(ਅਚਲ AVFrame *ਚੌਖਟਾ, ਪੂਰਨ plane)
{
    uintptr_t ਅੰਕੜੇ;
    ਪੂਰਨ planes;

    ਜੇ (ਚੌਖਟਾ->nb_samples) {
        ਪੂਰਨ channels = ਚੌਖਟਾ->ch_layout.nb_channels;
        ਜੇ (!channels)
            ਵਾਪਸ ਨਿਰਾ;
        planes = av_sample_fmt_is_planar(ਚੌਖਟਾ->format) ? channels : 1;
    } ਨਹੀਂਤਾਂ
        planes = 4;

    ਜੇ (plane < 0 || plane >= planes || !ਚੌਖਟਾ->extended_ਅੰਕੜੇ[plane])
        ਵਾਪਸ ਨਿਰਾ;
    ਅੰਕੜੇ = (uintptr_t)ਚੌਖਟਾ->extended_ਅੰਕੜੇ[plane];

    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(ਚੌਖਟਾ->buf) && ਚੌਖਟਾ->buf[i]; i++) {
        AVBufferRef *buf = ਚੌਖਟਾ->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->ਅੰਕੜੇ;

        ਜੇ (ਅੰਕੜੇ >= buf_begin && ਅੰਕੜੇ < buf_begin + buf->ਮਾਪ)
            ਵਾਪਸ buf;
    }
    ਲਈ (ਪੂਰਨ i = 0; i < ਚੌਖਟਾ->nb_extended_buf; i++) {
        AVBufferRef *buf = ਚੌਖਟਾ->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->ਅੰਕੜੇ;

        ਜੇ (ਅੰਕੜੇ >= buf_begin && ਅੰਕੜੇ < buf_begin + buf->ਮਾਪ)
            ਵਾਪਸ buf;
    }
    ਵਾਪਸ ਨਿਰਾ;
}

AVFrame_Side_ਅੰਕੜੇ *av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ_from_buf(AVFrame *ਚੌਖਟਾ,
                                                 ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type type,
                                                 AVBufferRef *buf)
{
    ਵਾਪਸ
        ff_ਚੌਖਟਾ_side_ਅੰਕੜੇ_ਜੋੜੋ_from_buf(
            &ਚੌਖਟਾ->side_ਅੰਕੜੇ, &ਚੌਖਟਾ->nb_side_ਅੰਕੜੇ, type, buf);
}

AVFrame_Side_ਅੰਕੜੇ *av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ,
                                        ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type type,
                                        size_t ਮਾਪ)
{
    AVFrame_Side_ਅੰਕੜੇ *ret;
    AVBufferRef *buf = av_ਬਫਰ_alloc(ਮਾਪ);
    ret = av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ_from_buf(ਚੌਖਟਾ, type, buf);
    ਜੇ (!ret)
        av_ਬਫਰ_unref(&buf);
    ਵਾਪਸ ret;
}

AVFrame_Side_ਅੰਕੜੇ *av_ਚੌਖਟਾ_get_side_ਅੰਕੜੇ(ਅਚਲ AVFrame *ਚੌਖਟਾ,
                                        ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type type)
{
    ਵਾਪਸ (AVFrame_Side_ਅੰਕੜੇ *)av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_get(
        ਚੌਖਟਾ->side_ਅੰਕੜੇ, ਚੌਖਟਾ->nb_side_ਅੰਕੜੇ,
        type
    );
}

ਸਥਿਰ ਪੂਰਨ ਚੌਖਟਾ_copy_video(AVFrame *dst, ਅਚਲ AVFrame *src)
{
    ਪੂਰਨ planes;

    ਜੇ (dst->ਚੌੜਾਈ  < src->ਚੌੜਾਈ ||
        dst->ਉਚਾਈ < src->ਉਚਾਈ)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (src->hw_ਚੌਖਟੇ_ctx || dst->hw_ਚੌਖਟੇ_ctx)
        ਵਾਪਸ av_hwframe_transfer_ਅੰਕੜੇ(dst, src, 0);

    planes = av_pix_fmt_ਗਿਣਤੀ_planes(dst->format);
    ਲਈ (ਪੂਰਨ i = 0; i < planes; i++)
        ਜੇ (!dst->ਅੰਕੜੇ[i] || !src->ਅੰਕੜੇ[i])
            ਵਾਪਸ AVERROR(EINVAL);

    av_image_copy2(dst->ਅੰਕੜੇ, dst->linesize,
                   src->ਅੰਕੜੇ, src->linesize,
                   dst->format, src->ਚੌੜਾਈ, src->ਉਚਾਈ);

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ ਚੌਖਟਾ_copy_audio(AVFrame *dst, ਅਚਲ AVFrame *src)
{
    ਪੂਰਨ planar   = av_sample_fmt_is_planar(dst->format);
    ਪੂਰਨ channels = dst->ch_layout.nb_channels;
    ਪੂਰਨ planes   = planar ? channels : 1;

    ਜੇ (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        ਵਾਪਸ AVERROR(EINVAL);

    ਲਈ (ਪੂਰਨ i = 0; i < planes; i++)
        ਜੇ (!dst->extended_ਅੰਕੜੇ[i] || !src->extended_ਅੰਕੜੇ[i])
            ਵਾਪਸ AVERROR(EINVAL);

    av_samples_copy(dst->extended_ਅੰਕੜੇ, src->extended_ਅੰਕੜੇ, 0, 0,
                    dst->nb_samples, channels, dst->format);

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_ਚੌਖਟਾ_copy(AVFrame *dst, ਅਚਲ AVFrame *src)
{
    ਜੇ (dst->format != src->format || dst->format < 0)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (dst->ਚੌੜਾਈ > 0 && dst->ਉਚਾਈ > 0)
        ਵਾਪਸ ਚੌਖਟਾ_copy_video(dst, src);
    ਨਹੀਂਤਾਂ ਜੇ (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        ਵਾਪਸ ਚੌਖਟਾ_copy_audio(dst, src);

    ਵਾਪਸ AVERROR(EINVAL);
}

ਖਾਲੀ av_ਚੌਖਟਾ_remove_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ, ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type type)
{
    av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_remove(&ਚੌਖਟਾ->side_ਅੰਕੜੇ, &ਚੌਖਟਾ->nb_side_ਅੰਕੜੇ, type);
}

ਸਥਿਰ ਪੂਰਨ calc_cropping_offsets(size_t offsets[4], ਅਚਲ AVFrame *ਚੌਖਟਾ,
                                 ਅਚਲ AVPixFmtDescriptor *desc)
{
    ਲਈ (ਪੂਰਨ i = 0; ਚੌਖਟਾ->ਅੰਕੜੇ[i]; i++) {
        ਅਚਲ AVComponentDescriptor *comp = ਨਿਰਾ;
        ਪੂਰਨ ਖਿਸਕਾਓ_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        ਪੂਰਨ ਖਿਸਕਾਓ_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        ਜੇ (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            ਰੋਕੋ;
        }

        /* find any component descriptor for this plane */
        ਲਈ (ਪੂਰਨ j = 0; j < desc->nb_components; j++) {
            ਜੇ (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                ਰੋਕੋ;
            }
        }
        ਜੇ (!comp)
            ਵਾਪਸ AVERROR_BUG;

        offsets[i] = (ਚੌਖਟਾ->crop_ਸਿਖਰ  >> ਖਿਸਕਾਓ_y) * ਚੌਖਟਾ->linesize[i] +
                     (ਚੌਖਟਾ->crop_ਖੱਬਾ >> ਖਿਸਕਾਓ_x) * comp->ਕਦਮ;
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_ਚੌਖਟਾ_apply_cropping(AVFrame *ਚੌਖਟਾ, ਪੂਰਨ flags)
{
    ਅਚਲ AVPixFmtDescriptor *desc;
    size_t offsets[4];
    ਪੂਰਨ ret;

    ਜੇ (!(ਚੌਖਟਾ->ਚੌੜਾਈ > 0 && ਚੌਖਟਾ->ਉਚਾਈ > 0))
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (ਚੌਖਟਾ->crop_ਖੱਬਾ >= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ - ਚੌਖਟਾ->crop_ਸੱਜਾ        ||
        ਚੌਖਟਾ->crop_ਸਿਖਰ  >= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ - ਚੌਖਟਾ->crop_bottom       ||
        (ਚੌਖਟਾ->crop_ਖੱਬਾ + ਚੌਖਟਾ->crop_ਸੱਜਾ) >= ਚੌਖਟਾ->ਚੌੜਾਈ ||
        (ਚੌਖਟਾ->crop_ਸਿਖਰ + ਚੌਖਟਾ->crop_bottom) >= ਚੌਖਟਾ->ਉਚਾਈ)
        ਵਾਪਸ AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(ਚੌਖਟਾ->format);
    ਜੇ (!desc)
        ਵਾਪਸ AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    ਜੇ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        ਚੌਖਟਾ->ਚੌੜਾਈ      -= ਚੌਖਟਾ->crop_ਸੱਜਾ;
        ਚੌਖਟਾ->ਉਚਾਈ     -= ਚੌਖਟਾ->crop_bottom;
        ਚੌਖਟਾ->crop_ਸੱਜਾ  = 0;
        ਚੌਖਟਾ->crop_bottom = 0;
        ਵਾਪਸ 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, ਚੌਖਟਾ, desc);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    /* adjust the offsets to avoid breaking alignment */
    ਜੇ (!(flags & AV_ਚੌਖਟਾ_CROP_UNALIGNED)) {
        ਪੂਰਨ log2_crop_align = ਚੌਖਟਾ->crop_ਖੱਬਾ ? ff_ctz(ਚੌਖਟਾ->crop_ਖੱਬਾ) : ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ;
        ਪੂਰਨ min_log2_align = ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ;

        ਲਈ (ਪੂਰਨ i = 0; ਚੌਖਟਾ->ਅੰਕੜੇ[i]; i++) {
            ਪੂਰਨ log2_align = offsets[i] ? ff_ctz(offsets[i]) : ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        ਜੇ (min_log2_align < 5 && log2_crop_align != ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ) {
            ਚੌਖਟਾ->crop_ਖੱਬਾ &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, ਚੌਖਟਾ, desc);
            ਜੇ (ret < 0)
                ਵਾਪਸ ret;
        }
    }

    ਲਈ (ਪੂਰਨ i = 0; ਚੌਖਟਾ->ਅੰਕੜੇ[i]; i++)
        ਚੌਖਟਾ->ਅੰਕੜੇ[i] += offsets[i];

    ਚੌਖਟਾ->ਚੌੜਾਈ      -= (ਚੌਖਟਾ->crop_ਖੱਬਾ + ਚੌਖਟਾ->crop_ਸੱਜਾ);
    ਚੌਖਟਾ->ਉਚਾਈ     -= (ਚੌਖਟਾ->crop_ਸਿਖਰ  + ਚੌਖਟਾ->crop_bottom);
    ਚੌਖਟਾ->crop_ਖੱਬਾ   = 0;
    ਚੌਖਟਾ->crop_ਸੱਜਾ  = 0;
    ਚੌਖਟਾ->crop_ਸਿਖਰ    = 0;
    ਚੌਖਟਾ->crop_bottom = 0;

    ਵਾਪਸ 0;
}
