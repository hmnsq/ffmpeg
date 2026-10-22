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

#అన్తర్భావ "channel_layout.h"
#అన్తర్భావ "avassert.h"
#అన్తర్భావ "buffer.h"
#అన్తర్భావ "dict.h"
#అన్తర్భావ "frame.h"
#అన్తర్భావ "frame_internal.h"
#అన్తర్భావ "imgutils.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "refstruct.h"
#అన్తర్భావ "samplefmt.h"
#అన్తర్భావ "side_data.h"
#అన్తర్భావ "hwcontext.h"

స్థిర శూన్య get_చట్రం_defaults(AVFrame *చట్రం)
{
    memset(చట్రం, 0, పరిమాణం(*చట్రం));

    చట్రం->pts                   =
    చట్రం->pkt_dts               = AV_NOPTS_విలువ;
    చట్రం->ఉత్తమ_effort_timestamp = AV_NOPTS_విలువ;
    చట్రం->duration            = 0;
    చట్రం->సమయం_పునాది           = (AVRational){ 0, 1 };
    చట్రం->sample_aspect_నిష్పత్తి = (AVRational){ 0, 1 };
    చట్రం->format              = -1; /* unknown */
    చట్రం->extended_దత్తాంశం       = చట్రం->దత్తాంశం;
    చట్రం->color_primaries     = AVCOL_PRI_UNSPECIFIED;
    చట్రం->color_trc           = AVCOL_TRC_UNSPECIFIED;
    చట్రం->colorspace          = AVCOL_SPC_UNSPECIFIED;
    చట్రం->color_range         = AVCOL_RANGE_UNSPECIFIED;
    చట్రం->chroma_location     = AVCHROMA_LOC_UNSPECIFIED;
    చట్రం->alpha_బహుళకం          = AVALPHA_బహుళకం_UNSPECIFIED;
    చట్రం->flags               = 0;
}

AVFrame *av_చట్రం_alloc(శూన్య)
{
    AVFrame *చట్రం = av_malloc(పరిమాణం(*చట్రం));

    ఒకవేళ (!చట్రం)
        తిరిగి ఖాళీ;

    get_చట్రం_defaults(చట్రం);

    తిరిగి చట్రం;
}

శూన్య av_చట్రం_free(AVFrame **చట్రం)
{
    ఒకవేళ (!చట్రం || !*చట్రం)
        తిరిగి;

    av_చట్రం_unref(*చట్రం);
    av_freep(చట్రం);
}

#నిర్వచించు ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

పూర్ణాంకం ff_చట్రం_get_video_బఫరు(AVFrame *చట్రం, పూర్ణాంకం align,
                              AVBufferRef *(*alloc)(శూన్య *opaque, size_t కొలత),
                              శూన్య *opaque)
{
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(చట్రం->format);
    పూర్ణాంకం ret, padded_ఎత్తు;
    పూర్ణాంకం plane_padding;
    ptrdiff_t linesizes[4];
    size_t మొత్తం_కొలత, sizes[4];

    ఒకవేళ (!desc)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ ((ret = av_image_check_కొలత(చట్రం->వెడల్పు, చట్రం->ఎత్తు, 0, ఖాళీ)) < 0)
        తిరిగి ret;

    ఒకవేళ (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    ఒకవేళ (!చట్రం->linesize[0]) {
        కొరకు (పూర్ణాంకం i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(చట్రం->linesize, చట్రం->format,
                                          FFALIGN(చట్రం->వెడల్పు, i));
            ఒకవేళ (ret < 0)
                తిరిగి ret;
            ఒకవేళ (!(చట్రం->linesize[0] & (align-1)))
                ఆపు;
        }

        కొరకు (పూర్ణాంకం i = 0; i < 4 && చట్రం->linesize[i]; i++)
            చట్రం->linesize[i] = FFALIGN(చట్రం->linesize[i], align);
    }

    కొరకు (పూర్ణాంకం i = 0; i < 4; i++)
        linesizes[i] = చట్రం->linesize[i];

    padded_ఎత్తు = FFALIGN(చట్రం->ఎత్తు, 32);
    ఒకవేళ ((ret = av_image_fill_plane_sizes(sizes, చట్రం->format,
                                         padded_ఎత్తు, linesizes)) < 0)
        తిరిగి ret;

    మొత్తం_కొలత = 4 * plane_padding + 4 * align;
    కొరకు (పూర్ణాంకం i = 0; i < 4; i++) {
        ఒకవేళ (sizes[i] > SIZE_MAX - మొత్తం_కొలత)
            తిరిగి AVERROR(EINVAL);
        మొత్తం_కొలత += sizes[i];
    }

    చట్రం->buf[0] = alloc ? alloc(opaque, మొత్తం_కొలత) : av_బఫరు_alloc(మొత్తం_కొలత);
    ఒకవేళ (!చట్రం->buf[0]) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    ఒకవేళ ((ret = av_image_fill_సూచికలు(చట్రం->దత్తాంశం, చట్రం->format, padded_ఎత్తు,
                                      చట్రం->buf[0]->దత్తాంశం, చట్రం->linesize)) < 0)
        వెళ్ళు fail;

    కొరకు (పూర్ణాంకం i = 1; i < 4; i++) {
        ఒకవేళ (చట్రం->దత్తాంశం[i])
            చట్రం->దత్తాంశం[i] += i * plane_padding;
        చట్రం->దత్తాంశం[i] = (uint8_t *)FFALIGN((uintptr_t)చట్రం->దత్తాంశం[i], align);
    }

    చట్రం->extended_దత్తాంశం = చట్రం->దత్తాంశం;

    తిరిగి 0;
fail:
    av_చట్రం_unref(చట్రం);
    తిరిగి ret;
}

స్థిర పూర్ణాంకం get_audio_బఫరు(AVFrame *చట్రం, పూర్ణాంకం align)
{
    పూర్ణాంకం planar   = av_sample_fmt_is_planar(చట్రం->format);
    పూర్ణాంకం channels, planes;
    size_t కొలత;
    పూర్ణాంకం ret;

    channels = చట్రం->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    ఒకవేళ (!చట్రం->linesize[0]) {
        ret = av_samples_get_బఫరు_కొలత(&చట్రం->linesize[0], channels,
                                         చట్రం->nb_samples, చట్రం->format,
                                         align);
        ఒకవేళ (ret < 0)
            తిరిగి ret;
    }

    ఒకవేళ (align <= 0)
        align = ALIGN;

    ఒకవేళ (planes > AV_అంకె_దత్తాంశం_సూచికలు) {
        చట్రం->extended_దత్తాంశం = av_calloc(planes,
                                          పరిమాణం(*చట్రం->extended_దత్తాంశం));
        చట్రం->extended_buf  = av_calloc(planes - AV_అంకె_దత్తాంశం_సూచికలు,
                                          పరిమాణం(*చట్రం->extended_buf));
        ఒకవేళ (!చట్రం->extended_దత్తాంశం || !చట్రం->extended_buf) {
            av_freep(&చట్రం->extended_దత్తాంశం);
            av_freep(&చట్రం->extended_buf);
            తిరిగి AVERROR(ENOMEM);
        }
        చట్రం->nb_extended_buf = planes - AV_అంకె_దత్తాంశం_సూచికలు;
    } లేకపోతే
        చట్రం->extended_దత్తాంశం = చట్రం->దత్తాంశం;

    ఒకవేళ (చట్రం->linesize[0] > SIZE_MAX - align)
        తిరిగి AVERROR(EINVAL);
    కొలత = చట్రం->linesize[0] + (size_t)align;

    కొరకు (పూర్ణాంకం i = 0; i < FFMIN(planes, AV_అంకె_దత్తాంశం_సూచికలు); i++) {
        చట్రం->buf[i] = av_బఫరు_alloc(కొలత);
        ఒకవేళ (!చట్రం->buf[i]) {
            av_చట్రం_unref(చట్రం);
            తిరిగి AVERROR(ENOMEM);
        }
        చట్రం->extended_దత్తాంశం[i] = చట్రం->దత్తాంశం[i] =
            (uint8_t *)FFALIGN((uintptr_t)చట్రం->buf[i]->దత్తాంశం, align);
    }
    కొరకు (పూర్ణాంకం i = 0; i < planes - AV_అంకె_దత్తాంశం_సూచికలు; i++) {
        చట్రం->extended_buf[i] = av_బఫరు_alloc(కొలత);
        ఒకవేళ (!చట్రం->extended_buf[i]) {
            av_చట్రం_unref(చట్రం);
            తిరిగి AVERROR(ENOMEM);
        }
        చట్రం->extended_దత్తాంశం[i + AV_అంకె_దత్తాంశం_సూచికలు] =
            (uint8_t *)FFALIGN((uintptr_t)చట్రం->extended_buf[i]->దత్తాంశం, align);
    }
    తిరిగి 0;

}

పూర్ణాంకం av_చట్రం_get_బఫరు(AVFrame *చట్రం, పూర్ణాంకం align)
{
    ఒకవేళ (చట్రం->format < 0)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (చట్రం->వెడల్పు > 0 && చట్రం->ఎత్తు > 0)
        తిరిగి ff_చట్రం_get_video_బఫరు(చట్రం, align, ఖాళీ, ఖాళీ);
    లేకపోతే ఒకవేళ (చట్రం->nb_samples > 0 &&
             (av_channel_layout_check(&చట్రం->ch_layout)))
        తిరిగి get_audio_బఫరు(చట్రం, align);

    తిరిగి AVERROR(EINVAL);
}

స్థిర పూర్ణాంకం చట్రం_copy_props(AVFrame *dst, స్థిరరాశి AVFrame *src, పూర్ణాంకం force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_నిష్పత్తి    = src->sample_aspect_నిష్పత్తి;
    dst->crop_శిఖరం               = src->crop_శిఖరం;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_ఎడమ              = src->crop_ఎడమ;
    dst->crop_కుడి             = src->crop_కుడి;
    dst->pts                    = src->pts;
    dst->duration               = src->duration;
    dst->repeat_pict            = src->repeat_pict;
    dst->sample_రేటు            = src->sample_రేటు;
    dst->opaque                 = src->opaque;
    dst->pkt_dts                = src->pkt_dts;
    dst->సమయం_పునాది              = src->సమయం_పునాది;
    dst->quality                = src->quality;
    dst->ఉత్తమ_effort_timestamp  = src->ఉత్తమ_effort_timestamp;
    dst->flags                  = src->flags;
    dst->decode_error_flags     = src->decode_error_flags;
    dst->color_primaries        = src->color_primaries;
    dst->color_trc              = src->color_trc;
    dst->colorspace             = src->colorspace;
    dst->color_range            = src->color_range;
    dst->chroma_location        = src->chroma_location;
    dst->alpha_బహుళకం             = src->alpha_బహుళకం;

    av_dict_copy(&dst->metadata, src->metadata, 0);

    కొరకు (పూర్ణాంకం i = 0; i < src->nb_side_దత్తాంశం; i++) {
        స్థిరరాశి AVFrame_Side_దత్తాంశం *sd_src = src->side_దత్తాంశం[i];
        AVFrame_Side_దత్తాంశం *sd_dst;
        ఒకవేళ (   sd_src->type == AV_చట్రం_దత్తాంశం_PANSCAN
            && (src->వెడల్పు != dst->వెడల్పు || src->ఎత్తు != dst->ఎత్తు))
            కొనసాగు;
        ఒకవేళ (force_copy) {
            sd_dst = av_చట్రం_new_side_దత్తాంశం(dst, sd_src->type,
                                            sd_src->కొలత);
            ఒకవేళ (!sd_dst) {
                av_చట్రం_side_దత్తాంశం_free(&dst->side_దత్తాంశం, &dst->nb_side_దత్తాంశం);
                తిరిగి AVERROR(ENOMEM);
            }
            జ్ఞాపకం_నకలు(sd_dst->దత్తాంశం, sd_src->దత్తాంశం, sd_src->కొలత);
        } లేకపోతే {
            AVBufferRef *ref = av_బఫరు_ref(sd_src->buf);
            sd_dst = av_చట్రం_new_side_దత్తాంశం_from_buf(dst, sd_src->type, ref);
            ఒకవేళ (!sd_dst) {
                av_బఫరు_unref(&ref);
                av_చట్రం_side_దత్తాంశం_free(&dst->side_దత్తాంశం, &dst->nb_side_దత్తాంశం);
                తిరిగి AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->వ్యక్తిగత_ref, src->వ్యక్తిగత_ref);
    తిరిగి av_బఫరు_replace(&dst->opaque_ref, src->opaque_ref);
}

పూర్ణాంకం av_చట్రం_ref(AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    పూర్ణాంకం ret = 0;

    av_assert1(dst->వెడల్పు == 0 && dst->ఎత్తు == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.క్రమం == AV_CHANNEL_క్రమం_UNSPEC);

    dst->format         = src->format;
    dst->వెడల్పు          = src->వెడల్పు;
    dst->ఎత్తు         = src->ఎత్తు;
    dst->nb_samples     = src->nb_samples;

    ret = చట్రం_copy_props(dst, src, 0);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    /* duplicate the frame data if it's not refcounted */
    ఒకవేళ (!src->buf[0]) {
        ret = av_చట్రం_get_బఫరు(dst, 0);
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;

        ret = av_చట్రం_copy(dst, src);
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;

        తిరిగి 0;
    }

    /* ref the buffers */
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ఒకవేళ (!src->buf[i])
            కొనసాగు;
        dst->buf[i] = av_బఫరు_ref(src->buf[i]);
        ఒకవేళ (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }
    }

    ఒకవేళ (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      పరిమాణం(*dst->extended_buf));
        ఒకవేళ (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        కొరకు (పూర్ణాంకం i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_బఫరు_ref(src->extended_buf[i]);
            ఒకవేళ (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                వెళ్ళు fail;
            }
        }
    }

    ఒకవేళ (src->hw_చట్రాలు_ctx) {
        dst->hw_చట్రాలు_ctx = av_బఫరు_ref(src->hw_చట్రాలు_ctx);
        ఒకవేళ (!dst->hw_చట్రాలు_ctx) {
            ret = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }
    }

    /* duplicate extended data */
    ఒకవేళ (src->extended_దత్తాంశం != src->దత్తాంశం) {
        పూర్ణాంకం ch = dst->ch_layout.nb_channels;

        ఒకవేళ (ch <= 0 || ch > SIZE_MAX / పరిమాణం(*dst->extended_దత్తాంశం)) {
            ret = AVERROR(EINVAL);
            వెళ్ళు fail;
        }

        dst->extended_దత్తాంశం = av_memdup(src->extended_దత్తాంశం, పరిమాణం(*dst->extended_దత్తాంశం) * ch);
        ఒకవేళ (!dst->extended_దత్తాంశం) {
            ret = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }
    } లేకపోతే
        dst->extended_దత్తాంశం = dst->దత్తాంశం;

    జ్ఞాపకం_నకలు(dst->దత్తాంశం,     src->దత్తాంశం,     పరిమాణం(src->దత్తాంశం));
    జ్ఞాపకం_నకలు(dst->linesize, src->linesize, పరిమాణం(src->linesize));

    తిరిగి 0;

fail:
    av_చట్రం_unref(dst);
    తిరిగి ret;
}

పూర్ణాంకం av_చట్రం_replace(AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    పూర్ణాంకం ret = 0;

    ఒకవేళ (dst == src)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (!src->buf[0]) {
        av_చట్రం_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        ఒకవేళ (   src->దత్తాంశం[0] || src->దత్తాంశం[1]
            || src->దత్తాంశం[2] || src->దత్తాంశం[3])
            తిరిగి av_చట్రం_ref(dst, src);

        ret = చట్రం_copy_props(dst, src, 0);
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;
    }

    dst->format         = src->format;
    dst->వెడల్పు          = src->వెడల్పు;
    dst->ఎత్తు         = src->ఎత్తు;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    av_చట్రం_side_దత్తాంశం_free(&dst->side_దత్తాంశం, &dst->nb_side_దత్తాంశం);
    av_dict_free(&dst->metadata);
    ret = చట్రం_copy_props(dst, src, 0);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    /* replace the buffers */
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_బఫరు_replace(&dst->buf[i], src->buf[i]);
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;
    }

    ఒకవేళ (src->extended_buf) {
        ఒకవేళ (dst->nb_extended_buf != src->nb_extended_buf) {
            పూర్ణాంకం nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            శూన్య *tmp;

            కొరకు (పూర్ణాంకం i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_బఫరు_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   పరిమాణం(*dst->extended_buf));
            ఒకవేళ (!tmp) {
                ret = AVERROR(ENOMEM);
                వెళ్ళు fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * పరిమాణం(*dst->extended_buf));
        }

        కొరకు (పూర్ణాంకం i = 0; i < src->nb_extended_buf; i++) {
            ret = av_బఫరు_replace(&dst->extended_buf[i], src->extended_buf[i]);
            ఒకవేళ (ret < 0)
                వెళ్ళు fail;
        }
    } లేకపోతే ఒకవేళ (dst->extended_buf) {
        కొరకు (పూర్ణాంకం i = 0; i < dst->nb_extended_buf; i++)
            av_బఫరు_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_బఫరు_replace(&dst->hw_చట్రాలు_ctx, src->hw_చట్రాలు_ctx);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    ఒకవేళ (dst->extended_దత్తాంశం != dst->దత్తాంశం)
        av_freep(&dst->extended_దత్తాంశం);

    ఒకవేళ (src->extended_దత్తాంశం != src->దత్తాంశం) {
        పూర్ణాంకం ch = dst->ch_layout.nb_channels;

        ఒకవేళ (ch <= 0 || ch > SIZE_MAX / పరిమాణం(*dst->extended_దత్తాంశం)) {
            ret = AVERROR(EINVAL);
            వెళ్ళు fail;
        }

        dst->extended_దత్తాంశం = av_memdup(src->extended_దత్తాంశం, పరిమాణం(*dst->extended_దత్తాంశం) * ch);
        ఒకవేళ (!dst->extended_దత్తాంశం) {
            ret = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }
    } లేకపోతే
        dst->extended_దత్తాంశం = dst->దత్తాంశం;

    జ్ఞాపకం_నకలు(dst->దత్తాంశం,     src->దత్తాంశం,     పరిమాణం(src->దత్తాంశం));
    జ్ఞాపకం_నకలు(dst->linesize, src->linesize, పరిమాణం(src->linesize));

    తిరిగి 0;

fail:
    av_చట్రం_unref(dst);
    తిరిగి ret;
}

AVFrame *av_చట్రం_clone(స్థిరరాశి AVFrame *src)
{
    AVFrame *ret = av_చట్రం_alloc();

    ఒకవేళ (!ret)
        తిరిగి ఖాళీ;

    ఒకవేళ (av_చట్రం_ref(ret, src) < 0)
        av_చట్రం_free(&ret);

    తిరిగి ret;
}

శూన్య av_చట్రం_unref(AVFrame *చట్రం)
{
    ఒకవేళ (!చట్రం)
        తిరిగి;

    av_చట్రం_side_దత్తాంశం_free(&చట్రం->side_దత్తాంశం, &చట్రం->nb_side_దత్తాంశం);

    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(చట్రం->buf); i++)
        av_బఫరు_unref(&చట్రం->buf[i]);
    కొరకు (పూర్ణాంకం i = 0; i < చట్రం->nb_extended_buf; i++)
        av_బఫరు_unref(&చట్రం->extended_buf[i]);
    av_freep(&చట్రం->extended_buf);
    av_dict_free(&చట్రం->metadata);

    av_బఫరు_unref(&చట్రం->hw_చట్రాలు_ctx);

    av_బఫరు_unref(&చట్రం->opaque_ref);
    av_refstruct_unref(&చట్రం->వ్యక్తిగత_ref);

    ఒకవేళ (చట్రం->extended_దత్తాంశం != చట్రం->దత్తాంశం)
        av_freep(&చట్రం->extended_దత్తాంశం);

    av_channel_layout_uninit(&చట్రం->ch_layout);

    get_చట్రం_defaults(చట్రం);
}

శూన్య av_చట్రం_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->వెడల్పు == 0 && dst->ఎత్తు == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.క్రమం == AV_CHANNEL_క్రమం_UNSPEC);

    *dst = *src;
    ఒకవేళ (src->extended_దత్తాంశం == src->దత్తాంశం)
        dst->extended_దత్తాంశం = dst->దత్తాంశం;
    get_చట్రం_defaults(src);
}

పూర్ణాంకం av_చట్రం_is_writable(AVFrame *చట్రం)
{
    పూర్ణాంకం ret = 1;

    /* assume non-refcounted frames are not writable */
    ఒకవేళ (!చట్రం->buf[0])
        తిరిగి 0;

    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(చట్రం->buf); i++)
        ఒకవేళ (చట్రం->buf[i])
            ret &= !!av_బఫరు_is_writable(చట్రం->buf[i]);
    కొరకు (పూర్ణాంకం i = 0; i < చట్రం->nb_extended_buf; i++)
        ret &= !!av_బఫరు_is_writable(చట్రం->extended_buf[i]);

    తిరిగి ret;
}

పూర్ణాంకం av_చట్రం_make_writable(AVFrame *చట్రం)
{
    AVFrame tmp;
    పూర్ణాంకం ret;

    ఒకవేళ (av_చట్రం_is_writable(చట్రం))
        తిరిగి 0;

    memset(&tmp, 0, పరిమాణం(tmp));
    tmp.format         = చట్రం->format;
    tmp.వెడల్పు          = చట్రం->వెడల్పు;
    tmp.ఎత్తు         = చట్రం->ఎత్తు;
    tmp.nb_samples     = చట్రం->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &చట్రం->ch_layout);
    ఒకవేళ (ret < 0) {
        av_చట్రం_unref(&tmp);
        తిరిగి ret;
    }

    ఒకవేళ (చట్రం->hw_చట్రాలు_ctx)
        ret = av_hwframe_get_బఫరు(చట్రం->hw_చట్రాలు_ctx, &tmp, 0);
    లేకపోతే
        ret = av_చట్రం_get_బఫరు(&tmp, 0);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ret = av_చట్రం_copy(&tmp, చట్రం);
    ఒకవేళ (ret < 0) {
        av_చట్రం_unref(&tmp);
        తిరిగి ret;
    }

    ret = av_చట్రం_copy_props(&tmp, చట్రం);
    ఒకవేళ (ret < 0) {
        av_చట్రం_unref(&tmp);
        తిరిగి ret;
    }

    av_చట్రం_unref(చట్రం);

    *చట్రం = tmp;
    ఒకవేళ (tmp.దత్తాంశం == tmp.extended_దత్తాంశం)
        చట్రం->extended_దత్తాంశం = చట్రం->దత్తాంశం;

    తిరిగి 0;
}

పూర్ణాంకం av_చట్రం_copy_props(AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    తిరిగి చట్రం_copy_props(dst, src, 1);
}

AVBufferRef *av_చట్రం_get_plane_బఫరు(స్థిరరాశి AVFrame *చట్రం, పూర్ణాంకం plane)
{
    uintptr_t దత్తాంశం;
    పూర్ణాంకం planes;

    ఒకవేళ (చట్రం->nb_samples) {
        పూర్ణాంకం channels = చట్రం->ch_layout.nb_channels;
        ఒకవేళ (!channels)
            తిరిగి ఖాళీ;
        planes = av_sample_fmt_is_planar(చట్రం->format) ? channels : 1;
    } లేకపోతే
        planes = 4;

    ఒకవేళ (plane < 0 || plane >= planes || !చట్రం->extended_దత్తాంశం[plane])
        తిరిగి ఖాళీ;
    దత్తాంశం = (uintptr_t)చట్రం->extended_దత్తాంశం[plane];

    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(చట్రం->buf) && చట్రం->buf[i]; i++) {
        AVBufferRef *buf = చట్రం->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->దత్తాంశం;

        ఒకవేళ (దత్తాంశం >= buf_begin && దత్తాంశం < buf_begin + buf->కొలత)
            తిరిగి buf;
    }
    కొరకు (పూర్ణాంకం i = 0; i < చట్రం->nb_extended_buf; i++) {
        AVBufferRef *buf = చట్రం->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->దత్తాంశం;

        ఒకవేళ (దత్తాంశం >= buf_begin && దత్తాంశం < buf_begin + buf->కొలత)
            తిరిగి buf;
    }
    తిరిగి ఖాళీ;
}

AVFrame_Side_దత్తాంశం *av_చట్రం_new_side_దత్తాంశం_from_buf(AVFrame *చట్రం,
                                                 గణన AVFrame_Side_దత్తాంశం_Type type,
                                                 AVBufferRef *buf)
{
    తిరిగి
        ff_చట్రం_side_దత్తాంశం_కూడు_from_buf(
            &చట్రం->side_దత్తాంశం, &చట్రం->nb_side_దత్తాంశం, type, buf);
}

AVFrame_Side_దత్తాంశం *av_చట్రం_new_side_దత్తాంశం(AVFrame *చట్రం,
                                        గణన AVFrame_Side_దత్తాంశం_Type type,
                                        size_t కొలత)
{
    AVFrame_Side_దత్తాంశం *ret;
    AVBufferRef *buf = av_బఫరు_alloc(కొలత);
    ret = av_చట్రం_new_side_దత్తాంశం_from_buf(చట్రం, type, buf);
    ఒకవేళ (!ret)
        av_బఫరు_unref(&buf);
    తిరిగి ret;
}

AVFrame_Side_దత్తాంశం *av_చట్రం_get_side_దత్తాంశం(స్థిరరాశి AVFrame *చట్రం,
                                        గణన AVFrame_Side_దత్తాంశం_Type type)
{
    తిరిగి (AVFrame_Side_దత్తాంశం *)av_చట్రం_side_దత్తాంశం_get(
        చట్రం->side_దత్తాంశం, చట్రం->nb_side_దత్తాంశం,
        type
    );
}

స్థిర పూర్ణాంకం చట్రం_copy_video(AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    పూర్ణాంకం planes;

    ఒకవేళ (dst->వెడల్పు  < src->వెడల్పు ||
        dst->ఎత్తు < src->ఎత్తు)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (src->hw_చట్రాలు_ctx || dst->hw_చట్రాలు_ctx)
        తిరిగి av_hwframe_transfer_దత్తాంశం(dst, src, 0);

    planes = av_pix_fmt_లెక్క_planes(dst->format);
    కొరకు (పూర్ణాంకం i = 0; i < planes; i++)
        ఒకవేళ (!dst->దత్తాంశం[i] || !src->దత్తాంశం[i])
            తిరిగి AVERROR(EINVAL);

    av_image_copy2(dst->దత్తాంశం, dst->linesize,
                   src->దత్తాంశం, src->linesize,
                   dst->format, src->వెడల్పు, src->ఎత్తు);

    తిరిగి 0;
}

స్థిర పూర్ణాంకం చట్రం_copy_audio(AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    పూర్ణాంకం planar   = av_sample_fmt_is_planar(dst->format);
    పూర్ణాంకం channels = dst->ch_layout.nb_channels;
    పూర్ణాంకం planes   = planar ? channels : 1;

    ఒకవేళ (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        తిరిగి AVERROR(EINVAL);

    కొరకు (పూర్ణాంకం i = 0; i < planes; i++)
        ఒకవేళ (!dst->extended_దత్తాంశం[i] || !src->extended_దత్తాంశం[i])
            తిరిగి AVERROR(EINVAL);

    av_samples_copy(dst->extended_దత్తాంశం, src->extended_దత్తాంశం, 0, 0,
                    dst->nb_samples, channels, dst->format);

    తిరిగి 0;
}

పూర్ణాంకం av_చట్రం_copy(AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    ఒకవేళ (dst->format != src->format || dst->format < 0)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (dst->వెడల్పు > 0 && dst->ఎత్తు > 0)
        తిరిగి చట్రం_copy_video(dst, src);
    లేకపోతే ఒకవేళ (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        తిరిగి చట్రం_copy_audio(dst, src);

    తిరిగి AVERROR(EINVAL);
}

శూన్య av_చట్రం_remove_side_దత్తాంశం(AVFrame *చట్రం, గణన AVFrame_Side_దత్తాంశం_Type type)
{
    av_చట్రం_side_దత్తాంశం_remove(&చట్రం->side_దత్తాంశం, &చట్రం->nb_side_దత్తాంశం, type);
}

స్థిర పూర్ణాంకం calc_cropping_offsets(size_t offsets[4], స్థిరరాశి AVFrame *చట్రం,
                                 స్థిరరాశి AVPixFmtDescriptor *desc)
{
    కొరకు (పూర్ణాంకం i = 0; చట్రం->దత్తాంశం[i]; i++) {
        స్థిరరాశి AVComponentDescriptor *comp = ఖాళీ;
        పూర్ణాంకం జరుపు_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        పూర్ణాంకం జరుపు_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        ఒకవేళ (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            ఆపు;
        }

        /* find any component descriptor for this plane */
        కొరకు (పూర్ణాంకం j = 0; j < desc->nb_components; j++) {
            ఒకవేళ (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                ఆపు;
            }
        }
        ఒకవేళ (!comp)
            తిరిగి AVERROR_BUG;

        offsets[i] = (చట్రం->crop_శిఖరం  >> జరుపు_y) * చట్రం->linesize[i] +
                     (చట్రం->crop_ఎడమ >> జరుపు_x) * comp->అడుగు;
    }

    తిరిగి 0;
}

పూర్ణాంకం av_చట్రం_apply_cropping(AVFrame *చట్రం, పూర్ణాంకం flags)
{
    స్థిరరాశి AVPixFmtDescriptor *desc;
    size_t offsets[4];
    పూర్ణాంకం ret;

    ఒకవేళ (!(చట్రం->వెడల్పు > 0 && చట్రం->ఎత్తు > 0))
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (చట్రం->crop_ఎడమ >= గరిష్ఠ_పూర్ణాంకం - చట్రం->crop_కుడి        ||
        చట్రం->crop_శిఖరం  >= గరిష్ఠ_పూర్ణాంకం - చట్రం->crop_bottom       ||
        (చట్రం->crop_ఎడమ + చట్రం->crop_కుడి) >= చట్రం->వెడల్పు ||
        (చట్రం->crop_శిఖరం + చట్రం->crop_bottom) >= చట్రం->ఎత్తు)
        తిరిగి AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(చట్రం->format);
    ఒకవేళ (!desc)
        తిరిగి AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    ఒకవేళ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        చట్రం->వెడల్పు      -= చట్రం->crop_కుడి;
        చట్రం->ఎత్తు     -= చట్రం->crop_bottom;
        చట్రం->crop_కుడి  = 0;
        చట్రం->crop_bottom = 0;
        తిరిగి 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, చట్రం, desc);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    /* adjust the offsets to avoid breaking alignment */
    ఒకవేళ (!(flags & AV_చట్రం_CROP_UNALIGNED)) {
        పూర్ణాంకం log2_crop_align = చట్రం->crop_ఎడమ ? ff_ctz(చట్రం->crop_ఎడమ) : గరిష్ఠ_పూర్ణాంకం;
        పూర్ణాంకం min_log2_align = గరిష్ఠ_పూర్ణాంకం;

        కొరకు (పూర్ణాంకం i = 0; చట్రం->దత్తాంశం[i]; i++) {
            పూర్ణాంకం log2_align = offsets[i] ? ff_ctz(offsets[i]) : గరిష్ఠ_పూర్ణాంకం;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        ఒకవేళ (min_log2_align < 5 && log2_crop_align != గరిష్ఠ_పూర్ణాంకం) {
            చట్రం->crop_ఎడమ &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, చట్రం, desc);
            ఒకవేళ (ret < 0)
                తిరిగి ret;
        }
    }

    కొరకు (పూర్ణాంకం i = 0; చట్రం->దత్తాంశం[i]; i++)
        చట్రం->దత్తాంశం[i] += offsets[i];

    చట్రం->వెడల్పు      -= (చట్రం->crop_ఎడమ + చట్రం->crop_కుడి);
    చట్రం->ఎత్తు     -= (చట్రం->crop_శిఖరం  + చట్రం->crop_bottom);
    చట్రం->crop_ఎడమ   = 0;
    చట్రం->crop_కుడి  = 0;
    చట్రం->crop_శిఖరం    = 0;
    చట్రం->crop_bottom = 0;

    తిరిగి 0;
}
