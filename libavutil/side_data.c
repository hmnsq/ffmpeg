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

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "dict.h"
#ಅನ್ತರ್ಭಾವ "frame.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "side_data.h"

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVSide_ದತ್ತಾಂಶ_Descriptor sd_props[] = {
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_PANSCAN]                     = { "AVPanScan",                                    AV_SIDE_ದತ್ತಾಂಶ_PROP_ಗಾತ್ರ_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_A53_CC]                      = { "ATSC A53 Part 4 Closed Captions" },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_MATRIXENCODING]              = { "AVMatrixEncoding",                             AV_SIDE_ದತ್ತಾಂಶ_PROP_CHANNEL_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DOWNMIX_INFO]                = { "Metadata relevant to a downmix procedure",     AV_SIDE_ದತ್ತಾಂಶ_PROP_CHANNEL_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_AFD]                         = { "Active format description" },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_MOTION_VECTORS]              = { "Motion vectors",                               AV_SIDE_ದತ್ತಾಂಶ_PROP_ಗಾತ್ರ_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SKIP_SAMPLES]                = { "Skip samples" },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_GOP_TIMECODE]                = { "GOP timecode" },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_S12_M_TIMECODE]               = { "SMPTE 12-1 timecode" },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DYNAMIC_HDR_PLUS]            = { "HDR Dynamic Metadata SMPTE2094-40 (HDR10+)",   AV_SIDE_ದತ್ತಾಂಶ_PROP_COLOR_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DYNAMIC_HDR_VIVID]           = { "HDR Dynamic Metadata CUVA 005.1 2021 (Vivid)", AV_SIDE_ದತ್ತಾಂಶ_PROP_COLOR_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DYNAMIC_HDR_SMPTE_2094_APP5] = { "HDR Dynamic Metadata SMPTE2094-50",            AV_SIDE_ದತ್ತಾಂಶ_PROP_COLOR_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_REGIONS_ದ_INTEREST]         = { "Regions Of Interest",                          AV_SIDE_ದತ್ತಾಂಶ_PROP_ಗಾತ್ರ_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_VIDEO_ENC_PARAMS]            = { "Video encoding parameters" },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_FILM_GRAIN_PARAMS]           = { "Film grain parameters" },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DETECTION_BBOXES]            = { "Bounding boxes for object detection and classification", AV_SIDE_ದತ್ತಾಂಶ_PROP_ಗಾತ್ರ_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DOVI_RPU_ಬಫರ್]             = { "Dolby Vision RPU Data",                        AV_SIDE_ದತ್ತಾಂಶ_PROP_COLOR_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DOVI_METADATA]               = { "Dolby Vision Metadata",                        AV_SIDE_ದತ್ತಾಂಶ_PROP_COLOR_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_LCEVC]                       = { "LCEVC NAL data",                               AV_SIDE_ದತ್ತಾಂಶ_PROP_ಗಾತ್ರ_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_VIEW_ID]                     = { "View ID" },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_STEREO3_D]                    = { "Stereo 3D",                                    AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_REPLAYGAIN]                  = { "AVReplayGain",                                 AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DISPLAYMATRIX]               = { "3x3 displaymatrix",                            AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_AUDIO_SERVICE_TYPE]          = { "Audio service type",                           AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_MASTERING_DISPLAY_METADATA]  = { "Mastering display metadata",                   AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL | AV_SIDE_ದತ್ತಾಂಶ_PROP_COLOR_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_CONTENT_LIGHT_LEVEL]         = { "Content light level metadata",                 AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL | AV_SIDE_ದತ್ತಾಂಶ_PROP_COLOR_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_AMBIENT_VIEWING_ENVIRONMENT] = { "Ambient viewing environment",                  AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SPHERICAL]                   = { "Spherical Mapping",                            AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL | AV_SIDE_ದತ್ತಾಂಶ_PROP_ಗಾತ್ರ_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_ICC_PROFILE]                 = { "ICC profile",                                  AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL | AV_SIDE_ದತ್ತಾಂಶ_PROP_COLOR_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_EXIF]                        = { "EXIF metadata",                                AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SEI_UNREGISTERED]            = { "H.26[45] User Data Unregistered SEI message",  AV_SIDE_ದತ್ತಾಂಶ_PROP_MULTI },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_VIDEO_HINT]                  = { "Encoding video hint",                          AV_SIDE_ದತ್ತಾಂಶ_PROP_ಗಾತ್ರ_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_3_D_REFERENCE_DISPLAYS]       = { "3D Reference Displays Information",            AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_IAMF_MIX_GAIN_PARAM]         = { "IAMF Mix Gain Parameter Data" },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_IAMF_DEMIXING_INFO_PARAM]    = { "IAMF Demixing Info Parameter Data",            AV_SIDE_ದತ್ತಾಂಶ_PROP_CHANNEL_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_IAMF_RECON_GAIN_INFO_PARAM]  = { "IAMF Recon Gain Info Parameter Data" },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_RAW_COLOR_PARAMS]            = { "RAW camera color parameters",                  AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL | AV_SIDE_ದತ್ತಾಂಶ_PROP_COLOR_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DOWNMIX_ಮಾತೃಕೆ]              = { "Downmix Matrix",                               AV_SIDE_ದತ್ತಾಂಶ_PROP_CHANNEL_DEPENDENT },
    [AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_GAIN_MAP_PARAMS]             = { "Gain map parameters",                          AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL | AV_SIDE_ದತ್ತಾಂಶ_PROP_COLOR_DEPENDENT },
};

ಸ್ಥಿರಾಂಕ AVSide_ದತ್ತಾಂಶ_Descriptor *av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_desc(ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type type)
{
    ಚಿಹ್ನೆರಹಿತ t = type;
    ಆದರೆ (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        ಹಿಂತಿರುಗಿ &sd_props[t];
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_name(ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type type)
{
    ಸ್ಥಿರಾಂಕ AVSide_ದತ್ತಾಂಶ_Descriptor *desc = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_desc(type);
    ಹಿಂತಿರುಗಿ desc ? desc->name : ಖಾಲಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ free_side_ದತ್ತಾಂಶ_ನಮೂದು(AVFrame_Side_ದತ್ತಾಂಶ **ptr_sd)
{
    AVFrame_Side_ದತ್ತಾಂಶ *sd = *ptr_sd;

    av_ಬಫರ್_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

ಸ್ಥಿರ ಶೂನ್ಯ remove_side_ದತ್ತಾಂಶ_by_ನಮೂದು(AVFrame_Side_ದತ್ತಾಂಶ ***sd, ಪೂರ್ಣಾಂಕ *nb_sd,
                                      ಸ್ಥಿರಾಂಕ AVFrame_Side_ದತ್ತಾಂಶ *ಗುರಿ)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_ದತ್ತಾಂಶ *ನಮೂದು = ((*sd)[i]);
        ಆದರೆ (ನಮೂದು != ಗುರಿ)
            ಮುಂದುವರಿ;

        free_side_ದತ್ತಾಂಶ_ನಮೂದು(&ನಮೂದು);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        ಹಿಂತಿರುಗಿ;
    }
}

ಶೂನ್ಯ av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_remove(AVFrame_Side_ದತ್ತಾಂಶ ***sd, ಪೂರ್ಣಾಂಕ *nb_sd,
                               ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type type)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_ದತ್ತಾಂಶ *ನಮೂದು = ((*sd)[i]);
        ಆದರೆ (ನಮೂದು->type != type)
            ಮುಂದುವರಿ;

        free_side_ದತ್ತಾಂಶ_ನಮೂದು(&ನಮೂದು);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

ಶೂನ್ಯ av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_remove_by_props(AVFrame_Side_ದತ್ತಾಂಶ ***sd, ಪೂರ್ಣಾಂಕ *nb_sd,
                                        ಪೂರ್ಣಾಂಕ props)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_ದತ್ತಾಂಶ *ನಮೂದು = ((*sd)[i]);
        ಸ್ಥಿರಾಂಕ AVSide_ದತ್ತಾಂಶ_Descriptor *desc = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_desc(ನಮೂದು->type);
        ಆದರೆ (!desc || !(desc->props & props))
            ಮುಂದುವರಿ;

        free_side_ದತ್ತಾಂಶ_ನಮೂದು(&ನಮೂದು);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

ಶೂನ್ಯ av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_free(AVFrame_Side_ದತ್ತಾಂಶ ***sd, ಪೂರ್ಣಾಂಕ *nb_sd)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < *nb_sd; i++)
        free_side_ದತ್ತಾಂಶ_ನಮೂದು(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

ಸ್ಥಿರ AVFrame_Side_ದತ್ತಾಂಶ *ಕೂಡಿಸು_side_ದತ್ತಾಂಶ_from_buf_ext(AVFrame_Side_ದತ್ತಾಂಶ ***sd,
                                                   ಪೂರ್ಣಾಂಕ *nb_sd,
                                                   ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type type,
                                                   AVBufferRef *buf, uint8_t *ದತ್ತಾಂಶ,
                                                   size_t ಗಾತ್ರ_2)
{
    AVFrame_Side_ದತ್ತಾಂಶ *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    ಆದರೆ ((ಚಿಹ್ನೆರಹಿತ)*nb_sd >= FFMIN(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, SIZE_MAX))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    tmp = av_realloc_array(*sd, *nb_sd + 1, ಗಾತ್ರ(**sd));
    ಆದರೆ (!tmp)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    *sd = tmp;

    ret = av_mallocz(ಗಾತ್ರ(*ret));
    ಆದರೆ (!ret)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ret->buf = buf;
    ret->ದತ್ತಾಂಶ = ದತ್ತಾಂಶ;
    ret->ಗಾತ್ರ_2 = ಗಾತ್ರ_2;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    ಹಿಂತಿರುಗಿ ret;
}

AVFrame_Side_ದತ್ತಾಂಶ *ff_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_ಕೂಡಿಸು_from_buf(AVFrame_Side_ದತ್ತಾಂಶ ***sd,
                                                 ಪೂರ್ಣಾಂಕ *nb_sd,
                                                 ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type type,
                                                 AVBufferRef *buf)
{
    ಆದರೆ (!buf)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_side_ದತ್ತಾಂಶ_from_buf_ext(sd, nb_sd, type, buf, buf->ದತ್ತಾಂಶ, buf->ಗಾತ್ರ_2);
}

ಸ್ಥಿರ AVFrame_Side_ದತ್ತಾಂಶ *replace_side_ದತ್ತಾಂಶ_from_buf(AVFrame_Side_ದತ್ತಾಂಶ *dst,
                                                   AVBufferRef *buf, ಪೂರ್ಣಾಂಕ flags)
{
    ಆದರೆ (!(flags & AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_REPLACE))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    av_dict_free(&dst->metadata);
    av_ಬಫರ್_unref(&dst->buf);
    dst->buf  = buf;
    dst->ದತ್ತಾಂಶ = buf->ದತ್ತಾಂಶ;
    dst->ಗಾತ್ರ_2 = buf->ಗಾತ್ರ_2;
    ಹಿಂತಿರುಗಿ dst;
}

AVFrame_Side_ದತ್ತಾಂಶ *av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_new(AVFrame_Side_ದತ್ತಾಂಶ ***sd, ಪೂರ್ಣಾಂಕ *nb_sd,
                                        ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type type,
                                        size_t ಗಾತ್ರ_2, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flags)
{
    ಸ್ಥಿರಾಂಕ AVSide_ದತ್ತಾಂಶ_Descriptor *desc = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_desc(type);
    AVBufferRef     *buf = av_ಬಫರ್_alloc(ಗಾತ್ರ_2);
    AVFrame_Side_ದತ್ತಾಂಶ *ret = ಖಾಲಿ;

    ಆದರೆ (flags & AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_UNIQUE)
        av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_remove(sd, nb_sd, type);
    ಆದರೆ ((!desc || !(desc->props & AV_SIDE_ದತ್ತಾಂಶ_PROP_MULTI)) &&
        (ret = (AVFrame_Side_ದತ್ತಾಂಶ *)av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_get(*sd, *nb_sd, type))) {
        ret = replace_side_ದತ್ತಾಂಶ_from_buf(ret, buf, flags);
        ಆದರೆ (!ret)
            av_ಬಫರ್_unref(&buf);
        ಹಿಂತಿರುಗಿ ret;
    }

    ret = ff_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_ಕೂಡಿಸು_from_buf(sd, nb_sd, type, buf);
    ಆದರೆ (!ret)
        av_ಬಫರ್_unref(&buf);

    ಹಿಂತಿರುಗಿ ret;
}

AVFrame_Side_ದತ್ತಾಂಶ *av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_ಕೂಡಿಸು(AVFrame_Side_ದತ್ತಾಂಶ ***sd, ಪೂರ್ಣಾಂಕ *nb_sd,
                                        ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type type,
                                        AVBufferRef **pbuf, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flags)
{
    ಸ್ಥಿರಾಂಕ AVSide_ದತ್ತಾಂಶ_Descriptor *desc = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_desc(type);
    AVFrame_Side_ದತ್ತಾಂಶ *sd_dst  = ಖಾಲಿ;
    AVBufferRef *buf = *pbuf;

    ಆದರೆ ((flags & AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_NEW_REF) && !(buf = av_ಬಫರ್_ref(*pbuf)))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಆದರೆ (flags & AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_UNIQUE)
        av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_remove(sd, nb_sd, type);
    ಆದರೆ ((!desc || !(desc->props & AV_SIDE_ದತ್ತಾಂಶ_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_ದತ್ತಾಂಶ *)av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_ದತ್ತಾಂಶ_from_buf(sd_dst, buf, flags);
    } ಇಲ್ಲದಿದ್ದರೆ
        sd_dst = ff_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_ಕೂಡಿಸು_from_buf(sd, nb_sd, type, buf);

    ಆದರೆ (sd_dst && !(flags & AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_NEW_REF))
        *pbuf = ಖಾಲಿ;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!sd_dst && (flags & AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_NEW_REF))
        av_ಬಫರ್_unref(&buf);
    ಹಿಂತಿರುಗಿ sd_dst;
}

ಪೂರ್ಣಾಂಕ av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_clone(AVFrame_Side_ದತ್ತಾಂಶ ***sd, ಪೂರ್ಣಾಂಕ *nb_sd,
                             ಸ್ಥಿರಾಂಕ AVFrame_Side_ದತ್ತಾಂಶ *src, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flags)
{
    ಸ್ಥಿರಾಂಕ AVSide_ದತ್ತಾಂಶ_Descriptor *desc;
    AVBufferRef     *buf    = ಖಾಲಿ;
    AVFrame_Side_ದತ್ತಾಂಶ *sd_dst = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ              ret    = AVERROR_BUG;

    ಆದರೆ (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    desc = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_desc(src->type);
    ಆದರೆ (flags & AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_UNIQUE)
        av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_remove(sd, nb_sd, src->type);
    ಆದರೆ ((!desc || !(desc->props & AV_SIDE_ದತ್ತಾಂಶ_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_ದತ್ತಾಂಶ *)av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = ಖಾಲಿ;

        ಆದರೆ (!(flags & AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_REPLACE))
            ಹಿಂತಿರುಗಿ AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;

        ret = av_ಬಫರ್_replace(&sd_dst->buf, src->buf);
        ಆದರೆ (ret < 0) {
            av_dict_free(&dict);
            ಹಿಂತಿರುಗಿ ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->ದತ್ತಾಂಶ     = src->ದತ್ತಾಂಶ;
        sd_dst->ಗಾತ್ರ_2     = src->ಗಾತ್ರ_2;
        ಹಿಂತಿರುಗಿ 0;
    }

    buf = av_ಬಫರ್_ref(src->buf);
    ಆದರೆ (!buf)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    sd_dst = ಕೂಡಿಸು_side_ದತ್ತಾಂಶ_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->ದತ್ತಾಂಶ, src->ಗಾತ್ರ_2);
    ಆದರೆ (!sd_dst) {
        av_ಬಫರ್_unref(&buf);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    ಆದರೆ (ret < 0) {
        remove_side_ದತ್ತಾಂಶ_by_ನಮೂದು(sd, nb_sd, sd_dst);
        ಹಿಂತಿರುಗಿ ret;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರಾಂಕ AVFrame_Side_ದತ್ತಾಂಶ *av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_get_c(ಸ್ಥಿರಾಂಕ AVFrame_Side_ದತ್ತಾಂಶ * ಸ್ಥಿರಾಂಕ *sd,
                                                ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ nb_sd,
                                                ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type type)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_sd; i++) {
        ಆದರೆ (sd[i]->type == type)
            ಹಿಂತಿರುಗಿ sd[i];
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}
