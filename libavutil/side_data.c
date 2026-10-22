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

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "dict.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "side_data.h"

ਸਥਿਰ ਅਚਲ AVSide_ਅੰਕੜੇ_Descriptor sd_props[] = {
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_PANSCAN]                     = { "AVPanScan",                                    AV_SIDE_ਅੰਕੜੇ_PROP_ਮਾਪ_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_A53_CC]                      = { "ATSC A53 Part 4 Closed Captions" },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_MATRIXENCODING]              = { "AVMatrixEncoding",                             AV_SIDE_ਅੰਕੜੇ_PROP_CHANNEL_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DOWNMIX_INFO]                = { "Metadata relevant to a downmix procedure",     AV_SIDE_ਅੰਕੜੇ_PROP_CHANNEL_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_AFD]                         = { "Active format description" },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_MOTION_VECTORS]              = { "Motion vectors",                               AV_SIDE_ਅੰਕੜੇ_PROP_ਮਾਪ_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SKIP_SAMPLES]                = { "Skip samples" },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_GOP_TIMECODE]                = { "GOP timecode" },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_S12_M_TIMECODE]               = { "SMPTE 12-1 timecode" },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DYNAMIC_HDR_PLUS]            = { "HDR Dynamic Metadata SMPTE2094-40 (HDR10+)",   AV_SIDE_ਅੰਕੜੇ_PROP_COLOR_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DYNAMIC_HDR_VIVID]           = { "HDR Dynamic Metadata CUVA 005.1 2021 (Vivid)", AV_SIDE_ਅੰਕੜੇ_PROP_COLOR_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DYNAMIC_HDR_SMPTE_2094_APP5] = { "HDR Dynamic Metadata SMPTE2094-50",            AV_SIDE_ਅੰਕੜੇ_PROP_COLOR_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_REGIONS_ਦਾ_INTEREST]         = { "Regions Of Interest",                          AV_SIDE_ਅੰਕੜੇ_PROP_ਮਾਪ_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_VIDEO_ENC_PARAMS]            = { "Video encoding parameters" },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_FILM_GRAIN_PARAMS]           = { "Film grain parameters" },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DETECTION_BBOXES]            = { "Bounding boxes for object detection and classification", AV_SIDE_ਅੰਕੜੇ_PROP_ਮਾਪ_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DOVI_RPU_ਬਫਰ]             = { "Dolby Vision RPU Data",                        AV_SIDE_ਅੰਕੜੇ_PROP_COLOR_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DOVI_METADATA]               = { "Dolby Vision Metadata",                        AV_SIDE_ਅੰਕੜੇ_PROP_COLOR_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_LCEVC]                       = { "LCEVC NAL data",                               AV_SIDE_ਅੰਕੜੇ_PROP_ਮਾਪ_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_VIEW_ID]                     = { "View ID" },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_STEREO3_D]                    = { "Stereo 3D",                                    AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_REPLAYGAIN]                  = { "AVReplayGain",                                 AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DISPLAYMATRIX]               = { "3x3 displaymatrix",                            AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_AUDIO_SERVICE_TYPE]          = { "Audio service type",                           AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_MASTERING_DISPLAY_METADATA]  = { "Mastering display metadata",                   AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL | AV_SIDE_ਅੰਕੜੇ_PROP_COLOR_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_CONTENT_LIGHT_LEVEL]         = { "Content light level metadata",                 AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL | AV_SIDE_ਅੰਕੜੇ_PROP_COLOR_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_AMBIENT_VIEWING_ENVIRONMENT] = { "Ambient viewing environment",                  AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SPHERICAL]                   = { "Spherical Mapping",                            AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL | AV_SIDE_ਅੰਕੜੇ_PROP_ਮਾਪ_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_ICC_PROFILE]                 = { "ICC profile",                                  AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL | AV_SIDE_ਅੰਕੜੇ_PROP_COLOR_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_EXIF]                        = { "EXIF metadata",                                AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SEI_UNREGISTERED]            = { "H.26[45] User Data Unregistered SEI message",  AV_SIDE_ਅੰਕੜੇ_PROP_MULTI },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_VIDEO_HINT]                  = { "Encoding video hint",                          AV_SIDE_ਅੰਕੜੇ_PROP_ਮਾਪ_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_3_D_REFERENCE_DISPLAYS]       = { "3D Reference Displays Information",            AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_IAMF_MIX_GAIN_PARAM]         = { "IAMF Mix Gain Parameter Data" },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_IAMF_DEMIXING_INFO_PARAM]    = { "IAMF Demixing Info Parameter Data",            AV_SIDE_ਅੰਕੜੇ_PROP_CHANNEL_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_IAMF_RECON_GAIN_INFO_PARAM]  = { "IAMF Recon Gain Info Parameter Data" },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_RAW_COLOR_PARAMS]            = { "RAW camera color parameters",                  AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL | AV_SIDE_ਅੰਕੜੇ_PROP_COLOR_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DOWNMIX_ਮੈਟ੍ਰਿਕਸ]              = { "Downmix Matrix",                               AV_SIDE_ਅੰਕੜੇ_PROP_CHANNEL_DEPENDENT },
    [AV_ਚੌਖਟਾ_ਅੰਕੜੇ_GAIN_MAP_PARAMS]             = { "Gain map parameters",                          AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL | AV_SIDE_ਅੰਕੜੇ_PROP_COLOR_DEPENDENT },
};

ਅਚਲ AVSide_ਅੰਕੜੇ_Descriptor *av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_desc(ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type type)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ t = type;
    ਜੇ (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        ਵਾਪਸ &sd_props[t];
    ਵਾਪਸ ਨਿਰਾ;
}

ਅਚਲ ਅੱਖਰ *av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_name(ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type type)
{
    ਅਚਲ AVSide_ਅੰਕੜੇ_Descriptor *desc = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_desc(type);
    ਵਾਪਸ desc ? desc->name : ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ free_side_ਅੰਕੜੇ_ਇੰਦਰਾਜ(AVFrame_Side_ਅੰਕੜੇ **ptr_sd)
{
    AVFrame_Side_ਅੰਕੜੇ *sd = *ptr_sd;

    av_ਬਫਰ_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

ਸਥਿਰ ਖਾਲੀ remove_side_ਅੰਕੜੇ_by_ਇੰਦਰਾਜ(AVFrame_Side_ਅੰਕੜੇ ***sd, ਪੂਰਨ *nb_sd,
                                      ਅਚਲ AVFrame_Side_ਅੰਕੜੇ *ਨਿਸ਼ਾਨਾ)
{
    ਲਈ (ਪੂਰਨ i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_ਅੰਕੜੇ *ਇੰਦਰਾਜ = ((*sd)[i]);
        ਜੇ (ਇੰਦਰਾਜ != ਨਿਸ਼ਾਨਾ)
            ਜਾਰੀ;

        free_side_ਅੰਕੜੇ_ਇੰਦਰਾਜ(&ਇੰਦਰਾਜ);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        ਵਾਪਸ;
    }
}

ਖਾਲੀ av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_remove(AVFrame_Side_ਅੰਕੜੇ ***sd, ਪੂਰਨ *nb_sd,
                               ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type type)
{
    ਲਈ (ਪੂਰਨ i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_ਅੰਕੜੇ *ਇੰਦਰਾਜ = ((*sd)[i]);
        ਜੇ (ਇੰਦਰਾਜ->type != type)
            ਜਾਰੀ;

        free_side_ਅੰਕੜੇ_ਇੰਦਰਾਜ(&ਇੰਦਰਾਜ);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

ਖਾਲੀ av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_remove_by_props(AVFrame_Side_ਅੰਕੜੇ ***sd, ਪੂਰਨ *nb_sd,
                                        ਪੂਰਨ props)
{
    ਲਈ (ਪੂਰਨ i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_ਅੰਕੜੇ *ਇੰਦਰਾਜ = ((*sd)[i]);
        ਅਚਲ AVSide_ਅੰਕੜੇ_Descriptor *desc = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_desc(ਇੰਦਰਾਜ->type);
        ਜੇ (!desc || !(desc->props & props))
            ਜਾਰੀ;

        free_side_ਅੰਕੜੇ_ਇੰਦਰਾਜ(&ਇੰਦਰਾਜ);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

ਖਾਲੀ av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_free(AVFrame_Side_ਅੰਕੜੇ ***sd, ਪੂਰਨ *nb_sd)
{
    ਲਈ (ਪੂਰਨ i = 0; i < *nb_sd; i++)
        free_side_ਅੰਕੜੇ_ਇੰਦਰਾਜ(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

ਸਥਿਰ AVFrame_Side_ਅੰਕੜੇ *ਜੋੜੋ_side_ਅੰਕੜੇ_from_buf_ext(AVFrame_Side_ਅੰਕੜੇ ***sd,
                                                   ਪੂਰਨ *nb_sd,
                                                   ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type type,
                                                   AVBufferRef *buf, uint8_t *ਅੰਕੜੇ,
                                                   size_t ਮਾਪ)
{
    AVFrame_Side_ਅੰਕੜੇ *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)*nb_sd >= FFMIN(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, SIZE_MAX))
        ਵਾਪਸ ਨਿਰਾ;

    tmp = av_realloc_array(*sd, *nb_sd + 1, ਆਕਾਰ(**sd));
    ਜੇ (!tmp)
        ਵਾਪਸ ਨਿਰਾ;
    *sd = tmp;

    ret = av_mallocz(ਆਕਾਰ(*ret));
    ਜੇ (!ret)
        ਵਾਪਸ ਨਿਰਾ;

    ret->buf = buf;
    ret->ਅੰਕੜੇ = ਅੰਕੜੇ;
    ret->ਮਾਪ = ਮਾਪ;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    ਵਾਪਸ ret;
}

AVFrame_Side_ਅੰਕੜੇ *ff_ਚੌਖਟਾ_side_ਅੰਕੜੇ_ਜੋੜੋ_from_buf(AVFrame_Side_ਅੰਕੜੇ ***sd,
                                                 ਪੂਰਨ *nb_sd,
                                                 ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type type,
                                                 AVBufferRef *buf)
{
    ਜੇ (!buf)
        ਵਾਪਸ ਨਿਰਾ;

    ਵਾਪਸ ਜੋੜੋ_side_ਅੰਕੜੇ_from_buf_ext(sd, nb_sd, type, buf, buf->ਅੰਕੜੇ, buf->ਮਾਪ);
}

ਸਥਿਰ AVFrame_Side_ਅੰਕੜੇ *replace_side_ਅੰਕੜੇ_from_buf(AVFrame_Side_ਅੰਕੜੇ *dst,
                                                   AVBufferRef *buf, ਪੂਰਨ flags)
{
    ਜੇ (!(flags & AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_REPLACE))
        ਵਾਪਸ ਨਿਰਾ;

    av_dict_free(&dst->metadata);
    av_ਬਫਰ_unref(&dst->buf);
    dst->buf  = buf;
    dst->ਅੰਕੜੇ = buf->ਅੰਕੜੇ;
    dst->ਮਾਪ = buf->ਮਾਪ;
    ਵਾਪਸ dst;
}

AVFrame_Side_ਅੰਕੜੇ *av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_new(AVFrame_Side_ਅੰਕੜੇ ***sd, ਪੂਰਨ *nb_sd,
                                        ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type type,
                                        size_t ਮਾਪ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flags)
{
    ਅਚਲ AVSide_ਅੰਕੜੇ_Descriptor *desc = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_desc(type);
    AVBufferRef     *buf = av_ਬਫਰ_alloc(ਮਾਪ);
    AVFrame_Side_ਅੰਕੜੇ *ret = ਨਿਰਾ;

    ਜੇ (flags & AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_UNIQUE)
        av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_remove(sd, nb_sd, type);
    ਜੇ ((!desc || !(desc->props & AV_SIDE_ਅੰਕੜੇ_PROP_MULTI)) &&
        (ret = (AVFrame_Side_ਅੰਕੜੇ *)av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_get(*sd, *nb_sd, type))) {
        ret = replace_side_ਅੰਕੜੇ_from_buf(ret, buf, flags);
        ਜੇ (!ret)
            av_ਬਫਰ_unref(&buf);
        ਵਾਪਸ ret;
    }

    ret = ff_ਚੌਖਟਾ_side_ਅੰਕੜੇ_ਜੋੜੋ_from_buf(sd, nb_sd, type, buf);
    ਜੇ (!ret)
        av_ਬਫਰ_unref(&buf);

    ਵਾਪਸ ret;
}

AVFrame_Side_ਅੰਕੜੇ *av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_ਜੋੜੋ(AVFrame_Side_ਅੰਕੜੇ ***sd, ਪੂਰਨ *nb_sd,
                                        ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type type,
                                        AVBufferRef **pbuf, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flags)
{
    ਅਚਲ AVSide_ਅੰਕੜੇ_Descriptor *desc = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_desc(type);
    AVFrame_Side_ਅੰਕੜੇ *sd_dst  = ਨਿਰਾ;
    AVBufferRef *buf = *pbuf;

    ਜੇ ((flags & AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_NEW_REF) && !(buf = av_ਬਫਰ_ref(*pbuf)))
        ਵਾਪਸ ਨਿਰਾ;
    ਜੇ (flags & AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_UNIQUE)
        av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_remove(sd, nb_sd, type);
    ਜੇ ((!desc || !(desc->props & AV_SIDE_ਅੰਕੜੇ_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_ਅੰਕੜੇ *)av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_ਅੰਕੜੇ_from_buf(sd_dst, buf, flags);
    } ਨਹੀਂਤਾਂ
        sd_dst = ff_ਚੌਖਟਾ_side_ਅੰਕੜੇ_ਜੋੜੋ_from_buf(sd, nb_sd, type, buf);

    ਜੇ (sd_dst && !(flags & AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_NEW_REF))
        *pbuf = ਨਿਰਾ;
    ਨਹੀਂਤਾਂ ਜੇ (!sd_dst && (flags & AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_NEW_REF))
        av_ਬਫਰ_unref(&buf);
    ਵਾਪਸ sd_dst;
}

ਪੂਰਨ av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_clone(AVFrame_Side_ਅੰਕੜੇ ***sd, ਪੂਰਨ *nb_sd,
                             ਅਚਲ AVFrame_Side_ਅੰਕੜੇ *src, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flags)
{
    ਅਚਲ AVSide_ਅੰਕੜੇ_Descriptor *desc;
    AVBufferRef     *buf    = ਨਿਰਾ;
    AVFrame_Side_ਅੰਕੜੇ *sd_dst = ਨਿਰਾ;
    ਪੂਰਨ              ret    = AVERROR_BUG;

    ਜੇ (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        ਵਾਪਸ AVERROR(EINVAL);

    desc = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_desc(src->type);
    ਜੇ (flags & AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_UNIQUE)
        av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_remove(sd, nb_sd, src->type);
    ਜੇ ((!desc || !(desc->props & AV_SIDE_ਅੰਕੜੇ_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_ਅੰਕੜੇ *)av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = ਨਿਰਾ;

        ਜੇ (!(flags & AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_REPLACE))
            ਵਾਪਸ AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;

        ret = av_ਬਫਰ_replace(&sd_dst->buf, src->buf);
        ਜੇ (ret < 0) {
            av_dict_free(&dict);
            ਵਾਪਸ ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->ਅੰਕੜੇ     = src->ਅੰਕੜੇ;
        sd_dst->ਮਾਪ     = src->ਮਾਪ;
        ਵਾਪਸ 0;
    }

    buf = av_ਬਫਰ_ref(src->buf);
    ਜੇ (!buf)
        ਵਾਪਸ AVERROR(ENOMEM);

    sd_dst = ਜੋੜੋ_side_ਅੰਕੜੇ_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->ਅੰਕੜੇ, src->ਮਾਪ);
    ਜੇ (!sd_dst) {
        av_ਬਫਰ_unref(&buf);
        ਵਾਪਸ AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    ਜੇ (ret < 0) {
        remove_side_ਅੰਕੜੇ_by_ਇੰਦਰਾਜ(sd, nb_sd, sd_dst);
        ਵਾਪਸ ret;
    }

    ਵਾਪਸ 0;
}

ਅਚਲ AVFrame_Side_ਅੰਕੜੇ *av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_get_c(ਅਚਲ AVFrame_Side_ਅੰਕੜੇ * ਅਚਲ *sd,
                                                ਅਚਲ ਪੂਰਨ nb_sd,
                                                ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type type)
{
    ਲਈ (ਪੂਰਨ i = 0; i < nb_sd; i++) {
        ਜੇ (sd[i]->type == type)
            ਵਾਪਸ sd[i];
    }
    ਵਾਪਸ ਨਿਰਾ;
}
