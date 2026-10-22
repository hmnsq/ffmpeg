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

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "buffer.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "dict.h"
#అన్తర్భావ "frame.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "side_data.h"

స్థిర స్థిరరాశి AVSide_దత్తాంశం_Descriptor sd_props[] = {
    [AV_చట్రం_దత్తాంశం_PANSCAN]                     = { "AVPanScan",                                    AV_SIDE_దత్తాంశం_PROP_కొలత_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_A53_CC]                      = { "ATSC A53 Part 4 Closed Captions" },
    [AV_చట్రం_దత్తాంశం_MATRIXENCODING]              = { "AVMatrixEncoding",                             AV_SIDE_దత్తాంశం_PROP_CHANNEL_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_DOWNMIX_INFO]                = { "Metadata relevant to a downmix procedure",     AV_SIDE_దత్తాంశం_PROP_CHANNEL_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_AFD]                         = { "Active format description" },
    [AV_చట్రం_దత్తాంశం_MOTION_VECTORS]              = { "Motion vectors",                               AV_SIDE_దత్తాంశం_PROP_కొలత_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_SKIP_SAMPLES]                = { "Skip samples" },
    [AV_చట్రం_దత్తాంశం_GOP_TIMECODE]                = { "GOP timecode" },
    [AV_చట్రం_దత్తాంశం_S12_M_TIMECODE]               = { "SMPTE 12-1 timecode" },
    [AV_చట్రం_దత్తాంశం_DYNAMIC_HDR_PLUS]            = { "HDR Dynamic Metadata SMPTE2094-40 (HDR10+)",   AV_SIDE_దత్తాంశం_PROP_COLOR_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_DYNAMIC_HDR_VIVID]           = { "HDR Dynamic Metadata CUVA 005.1 2021 (Vivid)", AV_SIDE_దత్తాంశం_PROP_COLOR_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_DYNAMIC_HDR_SMPTE_2094_APP5] = { "HDR Dynamic Metadata SMPTE2094-50",            AV_SIDE_దత్తాంశం_PROP_COLOR_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_REGIONS_యొక్క_INTEREST]         = { "Regions Of Interest",                          AV_SIDE_దత్తాంశం_PROP_కొలత_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_VIDEO_ENC_PARAMS]            = { "Video encoding parameters" },
    [AV_చట్రం_దత్తాంశం_FILM_GRAIN_PARAMS]           = { "Film grain parameters" },
    [AV_చట్రం_దత్తాంశం_DETECTION_BBOXES]            = { "Bounding boxes for object detection and classification", AV_SIDE_దత్తాంశం_PROP_కొలత_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_DOVI_RPU_బఫరు]             = { "Dolby Vision RPU Data",                        AV_SIDE_దత్తాంశం_PROP_COLOR_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_DOVI_METADATA]               = { "Dolby Vision Metadata",                        AV_SIDE_దత్తాంశం_PROP_COLOR_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_LCEVC]                       = { "LCEVC NAL data",                               AV_SIDE_దత్తాంశం_PROP_కొలత_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_VIEW_ID]                     = { "View ID" },
    [AV_చట్రం_దత్తాంశం_STEREO3_D]                    = { "Stereo 3D",                                    AV_SIDE_దత్తాంశం_PROP_GLOBAL },
    [AV_చట్రం_దత్తాంశం_REPLAYGAIN]                  = { "AVReplayGain",                                 AV_SIDE_దత్తాంశం_PROP_GLOBAL },
    [AV_చట్రం_దత్తాంశం_DISPLAYMATRIX]               = { "3x3 displaymatrix",                            AV_SIDE_దత్తాంశం_PROP_GLOBAL },
    [AV_చట్రం_దత్తాంశం_AUDIO_SERVICE_TYPE]          = { "Audio service type",                           AV_SIDE_దత్తాంశం_PROP_GLOBAL },
    [AV_చట్రం_దత్తాంశం_MASTERING_DISPLAY_METADATA]  = { "Mastering display metadata",                   AV_SIDE_దత్తాంశం_PROP_GLOBAL | AV_SIDE_దత్తాంశం_PROP_COLOR_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_CONTENT_LIGHT_LEVEL]         = { "Content light level metadata",                 AV_SIDE_దత్తాంశం_PROP_GLOBAL | AV_SIDE_దత్తాంశం_PROP_COLOR_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_AMBIENT_VIEWING_ENVIRONMENT] = { "Ambient viewing environment",                  AV_SIDE_దత్తాంశం_PROP_GLOBAL },
    [AV_చట్రం_దత్తాంశం_SPHERICAL]                   = { "Spherical Mapping",                            AV_SIDE_దత్తాంశం_PROP_GLOBAL | AV_SIDE_దత్తాంశం_PROP_కొలత_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_ICC_PROFILE]                 = { "ICC profile",                                  AV_SIDE_దత్తాంశం_PROP_GLOBAL | AV_SIDE_దత్తాంశం_PROP_COLOR_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_EXIF]                        = { "EXIF metadata",                                AV_SIDE_దత్తాంశం_PROP_GLOBAL },
    [AV_చట్రం_దత్తాంశం_SEI_UNREGISTERED]            = { "H.26[45] User Data Unregistered SEI message",  AV_SIDE_దత్తాంశం_PROP_MULTI },
    [AV_చట్రం_దత్తాంశం_VIDEO_HINT]                  = { "Encoding video hint",                          AV_SIDE_దత్తాంశం_PROP_కొలత_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_3_D_REFERENCE_DISPLAYS]       = { "3D Reference Displays Information",            AV_SIDE_దత్తాంశం_PROP_GLOBAL },
    [AV_చట్రం_దత్తాంశం_IAMF_MIX_GAIN_PARAM]         = { "IAMF Mix Gain Parameter Data" },
    [AV_చట్రం_దత్తాంశం_IAMF_DEMIXING_INFO_PARAM]    = { "IAMF Demixing Info Parameter Data",            AV_SIDE_దత్తాంశం_PROP_CHANNEL_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_IAMF_RECON_GAIN_INFO_PARAM]  = { "IAMF Recon Gain Info Parameter Data" },
    [AV_చట్రం_దత్తాంశం_RAW_COLOR_PARAMS]            = { "RAW camera color parameters",                  AV_SIDE_దత్తాంశం_PROP_GLOBAL | AV_SIDE_దత్తాంశం_PROP_COLOR_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_DOWNMIX_మాతృక]              = { "Downmix Matrix",                               AV_SIDE_దత్తాంశం_PROP_CHANNEL_DEPENDENT },
    [AV_చట్రం_దత్తాంశం_GAIN_MAP_PARAMS]             = { "Gain map parameters",                          AV_SIDE_దత్తాంశం_PROP_GLOBAL | AV_SIDE_దత్తాంశం_PROP_COLOR_DEPENDENT },
};

స్థిరరాశి AVSide_దత్తాంశం_Descriptor *av_చట్రం_side_దత్తాంశం_desc(గణన AVFrame_Side_దత్తాంశం_Type type)
{
    గుర్తులేని t = type;
    ఒకవేళ (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        తిరిగి &sd_props[t];
    తిరిగి ఖాళీ;
}

స్థిరరాశి అక్షరం *av_చట్రం_side_దత్తాంశం_name(గణన AVFrame_Side_దత్తాంశం_Type type)
{
    స్థిరరాశి AVSide_దత్తాంశం_Descriptor *desc = av_చట్రం_side_దత్తాంశం_desc(type);
    తిరిగి desc ? desc->name : ఖాళీ;
}

స్థిర శూన్య free_side_దత్తాంశం_నమోదు(AVFrame_Side_దత్తాంశం **ptr_sd)
{
    AVFrame_Side_దత్తాంశం *sd = *ptr_sd;

    av_బఫరు_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

స్థిర శూన్య remove_side_దత్తాంశం_by_నమోదు(AVFrame_Side_దత్తాంశం ***sd, పూర్ణాంకం *nb_sd,
                                      స్థిరరాశి AVFrame_Side_దత్తాంశం *లక్ష్యం)
{
    కొరకు (పూర్ణాంకం i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_దత్తాంశం *నమోదు_2 = ((*sd)[i]);
        ఒకవేళ (నమోదు_2 != లక్ష్యం)
            కొనసాగు;

        free_side_దత్తాంశం_నమోదు(&నమోదు_2);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        తిరిగి;
    }
}

శూన్య av_చట్రం_side_దత్తాంశం_remove(AVFrame_Side_దత్తాంశం ***sd, పూర్ణాంకం *nb_sd,
                               గణన AVFrame_Side_దత్తాంశం_Type type)
{
    కొరకు (పూర్ణాంకం i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_దత్తాంశం *నమోదు_2 = ((*sd)[i]);
        ఒకవేళ (నమోదు_2->type != type)
            కొనసాగు;

        free_side_దత్తాంశం_నమోదు(&నమోదు_2);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

శూన్య av_చట్రం_side_దత్తాంశం_remove_by_props(AVFrame_Side_దత్తాంశం ***sd, పూర్ణాంకం *nb_sd,
                                        పూర్ణాంకం props)
{
    కొరకు (పూర్ణాంకం i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_దత్తాంశం *నమోదు_2 = ((*sd)[i]);
        స్థిరరాశి AVSide_దత్తాంశం_Descriptor *desc = av_చట్రం_side_దత్తాంశం_desc(నమోదు_2->type);
        ఒకవేళ (!desc || !(desc->props & props))
            కొనసాగు;

        free_side_దత్తాంశం_నమోదు(&నమోదు_2);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

శూన్య av_చట్రం_side_దత్తాంశం_free(AVFrame_Side_దత్తాంశం ***sd, పూర్ణాంకం *nb_sd)
{
    కొరకు (పూర్ణాంకం i = 0; i < *nb_sd; i++)
        free_side_దత్తాంశం_నమోదు(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

స్థిర AVFrame_Side_దత్తాంశం *కూడు_side_దత్తాంశం_from_buf_ext(AVFrame_Side_దత్తాంశం ***sd,
                                                   పూర్ణాంకం *nb_sd,
                                                   గణన AVFrame_Side_దత్తాంశం_Type type,
                                                   AVBufferRef *buf, uint8_t *దత్తాంశం,
                                                   size_t కొలత)
{
    AVFrame_Side_దత్తాంశం *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    ఒకవేళ ((గుర్తులేని)*nb_sd >= FFMIN(గరిష్ఠ_పూర్ణాంకం, SIZE_MAX))
        తిరిగి ఖాళీ;

    tmp = av_realloc_array(*sd, *nb_sd + 1, పరిమాణం(**sd));
    ఒకవేళ (!tmp)
        తిరిగి ఖాళీ;
    *sd = tmp;

    ret = av_mallocz(పరిమాణం(*ret));
    ఒకవేళ (!ret)
        తిరిగి ఖాళీ;

    ret->buf = buf;
    ret->దత్తాంశం = దత్తాంశం;
    ret->కొలత = కొలత;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    తిరిగి ret;
}

AVFrame_Side_దత్తాంశం *ff_చట్రం_side_దత్తాంశం_కూడు_from_buf(AVFrame_Side_దత్తాంశం ***sd,
                                                 పూర్ణాంకం *nb_sd,
                                                 గణన AVFrame_Side_దత్తాంశం_Type type,
                                                 AVBufferRef *buf)
{
    ఒకవేళ (!buf)
        తిరిగి ఖాళీ;

    తిరిగి కూడు_side_దత్తాంశం_from_buf_ext(sd, nb_sd, type, buf, buf->దత్తాంశం, buf->కొలత);
}

స్థిర AVFrame_Side_దత్తాంశం *replace_side_దత్తాంశం_from_buf(AVFrame_Side_దత్తాంశం *dst,
                                                   AVBufferRef *buf, పూర్ణాంకం flags)
{
    ఒకవేళ (!(flags & AV_చట్రం_SIDE_దత్తాంశం_FLAG_REPLACE))
        తిరిగి ఖాళీ;

    av_dict_free(&dst->metadata);
    av_బఫరు_unref(&dst->buf);
    dst->buf  = buf;
    dst->దత్తాంశం = buf->దత్తాంశం;
    dst->కొలత = buf->కొలత;
    తిరిగి dst;
}

AVFrame_Side_దత్తాంశం *av_చట్రం_side_దత్తాంశం_new(AVFrame_Side_దత్తాంశం ***sd, పూర్ణాంకం *nb_sd,
                                        గణన AVFrame_Side_దత్తాంశం_Type type,
                                        size_t కొలత, గుర్తులేని పూర్ణాంకం flags)
{
    స్థిరరాశి AVSide_దత్తాంశం_Descriptor *desc = av_చట్రం_side_దత్తాంశం_desc(type);
    AVBufferRef     *buf = av_బఫరు_alloc(కొలత);
    AVFrame_Side_దత్తాంశం *ret = ఖాళీ;

    ఒకవేళ (flags & AV_చట్రం_SIDE_దత్తాంశం_FLAG_UNIQUE)
        av_చట్రం_side_దత్తాంశం_remove(sd, nb_sd, type);
    ఒకవేళ ((!desc || !(desc->props & AV_SIDE_దత్తాంశం_PROP_MULTI)) &&
        (ret = (AVFrame_Side_దత్తాంశం *)av_చట్రం_side_దత్తాంశం_get(*sd, *nb_sd, type))) {
        ret = replace_side_దత్తాంశం_from_buf(ret, buf, flags);
        ఒకవేళ (!ret)
            av_బఫరు_unref(&buf);
        తిరిగి ret;
    }

    ret = ff_చట్రం_side_దత్తాంశం_కూడు_from_buf(sd, nb_sd, type, buf);
    ఒకవేళ (!ret)
        av_బఫరు_unref(&buf);

    తిరిగి ret;
}

AVFrame_Side_దత్తాంశం *av_చట్రం_side_దత్తాంశం_కూడు(AVFrame_Side_దత్తాంశం ***sd, పూర్ణాంకం *nb_sd,
                                        గణన AVFrame_Side_దత్తాంశం_Type type,
                                        AVBufferRef **pbuf, గుర్తులేని పూర్ణాంకం flags)
{
    స్థిరరాశి AVSide_దత్తాంశం_Descriptor *desc = av_చట్రం_side_దత్తాంశం_desc(type);
    AVFrame_Side_దత్తాంశం *sd_dst  = ఖాళీ;
    AVBufferRef *buf = *pbuf;

    ఒకవేళ ((flags & AV_చట్రం_SIDE_దత్తాంశం_FLAG_NEW_REF) && !(buf = av_బఫరు_ref(*pbuf)))
        తిరిగి ఖాళీ;
    ఒకవేళ (flags & AV_చట్రం_SIDE_దత్తాంశం_FLAG_UNIQUE)
        av_చట్రం_side_దత్తాంశం_remove(sd, nb_sd, type);
    ఒకవేళ ((!desc || !(desc->props & AV_SIDE_దత్తాంశం_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_దత్తాంశం *)av_చట్రం_side_దత్తాంశం_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_దత్తాంశం_from_buf(sd_dst, buf, flags);
    } లేకపోతే
        sd_dst = ff_చట్రం_side_దత్తాంశం_కూడు_from_buf(sd, nb_sd, type, buf);

    ఒకవేళ (sd_dst && !(flags & AV_చట్రం_SIDE_దత్తాంశం_FLAG_NEW_REF))
        *pbuf = ఖాళీ;
    లేకపోతే ఒకవేళ (!sd_dst && (flags & AV_చట్రం_SIDE_దత్తాంశం_FLAG_NEW_REF))
        av_బఫరు_unref(&buf);
    తిరిగి sd_dst;
}

పూర్ణాంకం av_చట్రం_side_దత్తాంశం_clone(AVFrame_Side_దత్తాంశం ***sd, పూర్ణాంకం *nb_sd,
                             స్థిరరాశి AVFrame_Side_దత్తాంశం *src, గుర్తులేని పూర్ణాంకం flags)
{
    స్థిరరాశి AVSide_దత్తాంశం_Descriptor *desc;
    AVBufferRef     *buf    = ఖాళీ;
    AVFrame_Side_దత్తాంశం *sd_dst = ఖాళీ;
    పూర్ణాంకం              ret    = AVERROR_BUG;

    ఒకవేళ (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        తిరిగి AVERROR(EINVAL);

    desc = av_చట్రం_side_దత్తాంశం_desc(src->type);
    ఒకవేళ (flags & AV_చట్రం_SIDE_దత్తాంశం_FLAG_UNIQUE)
        av_చట్రం_side_దత్తాంశం_remove(sd, nb_sd, src->type);
    ఒకవేళ ((!desc || !(desc->props & AV_SIDE_దత్తాంశం_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_దత్తాంశం *)av_చట్రం_side_దత్తాంశం_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = ఖాళీ;

        ఒకవేళ (!(flags & AV_చట్రం_SIDE_దత్తాంశం_FLAG_REPLACE))
            తిరిగి AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        ఒకవేళ (ret < 0)
            తిరిగి ret;

        ret = av_బఫరు_replace(&sd_dst->buf, src->buf);
        ఒకవేళ (ret < 0) {
            av_dict_free(&dict);
            తిరిగి ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->దత్తాంశం     = src->దత్తాంశం;
        sd_dst->కొలత     = src->కొలత;
        తిరిగి 0;
    }

    buf = av_బఫరు_ref(src->buf);
    ఒకవేళ (!buf)
        తిరిగి AVERROR(ENOMEM);

    sd_dst = కూడు_side_దత్తాంశం_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->దత్తాంశం, src->కొలత);
    ఒకవేళ (!sd_dst) {
        av_బఫరు_unref(&buf);
        తిరిగి AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    ఒకవేళ (ret < 0) {
        remove_side_దత్తాంశం_by_నమోదు(sd, nb_sd, sd_dst);
        తిరిగి ret;
    }

    తిరిగి 0;
}

స్థిరరాశి AVFrame_Side_దత్తాంశం *av_చట్రం_side_దత్తాంశం_get_c(స్థిరరాశి AVFrame_Side_దత్తాంశం * స్థిరరాశి *sd,
                                                స్థిరరాశి పూర్ణాంకం nb_sd,
                                                గణన AVFrame_Side_దత్తాంశం_Type type)
{
    కొరకు (పూర్ణాంకం i = 0; i < nb_sd; i++) {
        ఒకవేళ (sd[i]->type == type)
            తిరిగి sd[i];
    }
    తిరిగి ఖాళీ;
}
