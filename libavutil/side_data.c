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

#समावेश "avassert.h"
#समावेश "buffer.h"
#समावेश "common.h"
#समावेश "dict.h"
#समावेश "frame.h"
#समावेश "mem.h"
#समावेश "side_data.h"

अटल स्थिर AVSide_तथ्य_Descriptor sd_props[] = {
    [AV_FRAME_तथ्य_PANSCAN]                     = { "AVPanScan",                                    AV_SIDE_तथ्य_PROP_आकार_DEPENDENT },
    [AV_FRAME_तथ्य_A53_CC]                      = { "ATSC A53 Part 4 Closed Captions" },
    [AV_FRAME_तथ्य_MATRIXENCODING]              = { "AVMatrixEncoding",                             AV_SIDE_तथ्य_PROP_CHANNEL_DEPENDENT },
    [AV_FRAME_तथ्य_DOWNMIX_INFO]                = { "Metadata relevant to a downmix procedure",     AV_SIDE_तथ्य_PROP_CHANNEL_DEPENDENT },
    [AV_FRAME_तथ्य_AFD]                         = { "Active format description" },
    [AV_FRAME_तथ्य_MOTION_VECTORS]              = { "Motion vectors",                               AV_SIDE_तथ्य_PROP_आकार_DEPENDENT },
    [AV_FRAME_तथ्य_SKIP_SAMPLES]                = { "Skip samples" },
    [AV_FRAME_तथ्य_GOP_TIMECODE]                = { "GOP timecode" },
    [AV_FRAME_तथ्य_S12_M_TIMECODE]               = { "SMPTE 12-1 timecode" },
    [AV_FRAME_तथ्य_DYNAMIC_HDR_PLUS]            = { "HDR Dynamic Metadata SMPTE2094-40 (HDR10+)",   AV_SIDE_तथ्य_PROP_COLOR_DEPENDENT },
    [AV_FRAME_तथ्य_DYNAMIC_HDR_VIVID]           = { "HDR Dynamic Metadata CUVA 005.1 2021 (Vivid)", AV_SIDE_तथ्य_PROP_COLOR_DEPENDENT },
    [AV_FRAME_तथ्य_DYNAMIC_HDR_SMPTE_2094_APP5] = { "HDR Dynamic Metadata SMPTE2094-50",            AV_SIDE_तथ्य_PROP_COLOR_DEPENDENT },
    [AV_FRAME_तथ्य_REGIONS_OF_INTEREST]         = { "Regions Of Interest",                          AV_SIDE_तथ्य_PROP_आकार_DEPENDENT },
    [AV_FRAME_तथ्य_VIDEO_ENC_PARAMS]            = { "Video encoding parameters" },
    [AV_FRAME_तथ्य_FILM_GRAIN_PARAMS]           = { "Film grain parameters" },
    [AV_FRAME_तथ्य_DETECTION_BBOXES]            = { "Bounding boxes for object detection and classification", AV_SIDE_तथ्य_PROP_आकार_DEPENDENT },
    [AV_FRAME_तथ्य_DOVI_RPU_बफर]             = { "Dolby Vision RPU Data",                        AV_SIDE_तथ्य_PROP_COLOR_DEPENDENT },
    [AV_FRAME_तथ्य_DOVI_METADATA]               = { "Dolby Vision Metadata",                        AV_SIDE_तथ्य_PROP_COLOR_DEPENDENT },
    [AV_FRAME_तथ्य_LCEVC]                       = { "LCEVC NAL data",                               AV_SIDE_तथ्य_PROP_आकार_DEPENDENT },
    [AV_FRAME_तथ्य_VIEW_ID]                     = { "View ID" },
    [AV_FRAME_तथ्य_STEREO3_D]                    = { "Stereo 3D",                                    AV_SIDE_तथ्य_PROP_GLOBAL },
    [AV_FRAME_तथ्य_REPLAYGAIN]                  = { "AVReplayGain",                                 AV_SIDE_तथ्य_PROP_GLOBAL },
    [AV_FRAME_तथ्य_DISPLAYMATRIX]               = { "3x3 displaymatrix",                            AV_SIDE_तथ्य_PROP_GLOBAL },
    [AV_FRAME_तथ्य_AUDIO_SERVICE_TYPE]          = { "Audio service type",                           AV_SIDE_तथ्य_PROP_GLOBAL },
    [AV_FRAME_तथ्य_MASTERING_DISPLAY_METADATA]  = { "Mastering display metadata",                   AV_SIDE_तथ्य_PROP_GLOBAL | AV_SIDE_तथ्य_PROP_COLOR_DEPENDENT },
    [AV_FRAME_तथ्य_CONTENT_LIGHT_LEVEL]         = { "Content light level metadata",                 AV_SIDE_तथ्य_PROP_GLOBAL | AV_SIDE_तथ्य_PROP_COLOR_DEPENDENT },
    [AV_FRAME_तथ्य_AMBIENT_VIEWING_ENVIRONMENT] = { "Ambient viewing environment",                  AV_SIDE_तथ्य_PROP_GLOBAL },
    [AV_FRAME_तथ्य_SPHERICAL]                   = { "Spherical Mapping",                            AV_SIDE_तथ्य_PROP_GLOBAL | AV_SIDE_तथ्य_PROP_आकार_DEPENDENT },
    [AV_FRAME_तथ्य_ICC_PROFILE]                 = { "ICC profile",                                  AV_SIDE_तथ्य_PROP_GLOBAL | AV_SIDE_तथ्य_PROP_COLOR_DEPENDENT },
    [AV_FRAME_तथ्य_EXIF]                        = { "EXIF metadata",                                AV_SIDE_तथ्य_PROP_GLOBAL },
    [AV_FRAME_तथ्य_SEI_UNREGISTERED]            = { "H.26[45] User Data Unregistered SEI message",  AV_SIDE_तथ्य_PROP_MULTI },
    [AV_FRAME_तथ्य_VIDEO_HINT]                  = { "Encoding video hint",                          AV_SIDE_तथ्य_PROP_आकार_DEPENDENT },
    [AV_FRAME_तथ्य_3_D_REFERENCE_DISPLAYS]       = { "3D Reference Displays Information",            AV_SIDE_तथ्य_PROP_GLOBAL },
    [AV_FRAME_तथ्य_IAMF_MIX_GAIN_PARAM]         = { "IAMF Mix Gain Parameter Data" },
    [AV_FRAME_तथ्य_IAMF_DEMIXING_INFO_PARAM]    = { "IAMF Demixing Info Parameter Data",            AV_SIDE_तथ्य_PROP_CHANNEL_DEPENDENT },
    [AV_FRAME_तथ्य_IAMF_RECON_GAIN_INFO_PARAM]  = { "IAMF Recon Gain Info Parameter Data" },
    [AV_FRAME_तथ्य_RAW_COLOR_PARAMS]            = { "RAW camera color parameters",                  AV_SIDE_तथ्य_PROP_GLOBAL | AV_SIDE_तथ्य_PROP_COLOR_DEPENDENT },
    [AV_FRAME_तथ्य_DOWNMIX_MATRIX]              = { "Downmix Matrix",                               AV_SIDE_तथ्य_PROP_CHANNEL_DEPENDENT },
    [AV_FRAME_तथ्य_GAIN_MAP_PARAMS]             = { "Gain map parameters",                          AV_SIDE_तथ्य_PROP_GLOBAL | AV_SIDE_तथ्य_PROP_COLOR_DEPENDENT },
};

स्थिर AVSide_तथ्य_Descriptor *av_frame_side_तथ्य_desc(क्रमागत AVFrame_Side_तथ्य_Type type)
{
    अचिन्हित t = type;
    अगर (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        वापस &sd_props[t];
    वापस शून्य;
}

स्थिर अक्षर *av_frame_side_तथ्य_name(क्रमागत AVFrame_Side_तथ्य_Type type)
{
    स्थिर AVSide_तथ्य_Descriptor *desc = av_frame_side_तथ्य_desc(type);
    वापस desc ? desc->name : शून्य;
}

अटल व्योम free_side_तथ्य_entry(AVFrame_Side_तथ्य **ptr_sd)
{
    AVFrame_Side_तथ्य *sd = *ptr_sd;

    av_बफर_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

अटल व्योम remove_side_तथ्य_by_entry(AVFrame_Side_तथ्य ***sd, पूर्णांक *nb_sd,
                                      स्थिर AVFrame_Side_तथ्य *target)
{
    क्रम (पूर्णांक i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_तथ्य *entry = ((*sd)[i]);
        अगर (entry != target)
            जारी;

        free_side_तथ्य_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        वापस;
    }
}

व्योम av_frame_side_तथ्य_remove(AVFrame_Side_तथ्य ***sd, पूर्णांक *nb_sd,
                               क्रमागत AVFrame_Side_तथ्य_Type type)
{
    क्रम (पूर्णांक i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_तथ्य *entry = ((*sd)[i]);
        अगर (entry->type != type)
            जारी;

        free_side_तथ्य_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

व्योम av_frame_side_तथ्य_remove_by_props(AVFrame_Side_तथ्य ***sd, पूर्णांक *nb_sd,
                                        पूर्णांक props)
{
    क्रम (पूर्णांक i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_तथ्य *entry = ((*sd)[i]);
        स्थिर AVSide_तथ्य_Descriptor *desc = av_frame_side_तथ्य_desc(entry->type);
        अगर (!desc || !(desc->props & props))
            जारी;

        free_side_तथ्य_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

व्योम av_frame_side_तथ्य_free(AVFrame_Side_तथ्य ***sd, पूर्णांक *nb_sd)
{
    क्रम (पूर्णांक i = 0; i < *nb_sd; i++)
        free_side_तथ्य_entry(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

अटल AVFrame_Side_तथ्य *add_side_तथ्य_from_buf_ext(AVFrame_Side_तथ्य ***sd,
                                                   पूर्णांक *nb_sd,
                                                   क्रमागत AVFrame_Side_तथ्य_Type type,
                                                   AVBufferRef *buf, uint8_t *तथ्य,
                                                   माप_प्रकार आकार)
{
    AVFrame_Side_तथ्य *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    अगर ((अचिन्हित)*nb_sd >= FFMIN(पूर्णांक_उच्च, SIZE_MAX))
        वापस शून्य;

    tmp = av_realloc_array(*sd, *nb_sd + 1, माप(**sd));
    अगर (!tmp)
        वापस शून्य;
    *sd = tmp;

    ret = av_mallocz(माप(*ret));
    अगर (!ret)
        वापस शून्य;

    ret->buf = buf;
    ret->तथ्य = तथ्य;
    ret->आकार = आकार;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    वापस ret;
}

AVFrame_Side_तथ्य *ff_frame_side_तथ्य_add_from_buf(AVFrame_Side_तथ्य ***sd,
                                                 पूर्णांक *nb_sd,
                                                 क्रमागत AVFrame_Side_तथ्य_Type type,
                                                 AVBufferRef *buf)
{
    अगर (!buf)
        वापस शून्य;

    वापस add_side_तथ्य_from_buf_ext(sd, nb_sd, type, buf, buf->तथ्य, buf->आकार);
}

अटल AVFrame_Side_तथ्य *replace_side_तथ्य_from_buf(AVFrame_Side_तथ्य *dst,
                                                   AVBufferRef *buf, पूर्णांक flags)
{
    अगर (!(flags & AV_FRAME_SIDE_तथ्य_FLAG_REPLACE))
        वापस शून्य;

    av_dict_free(&dst->metadata);
    av_बफर_unref(&dst->buf);
    dst->buf  = buf;
    dst->तथ्य = buf->तथ्य;
    dst->आकार = buf->आकार;
    वापस dst;
}

AVFrame_Side_तथ्य *av_frame_side_तथ्य_new(AVFrame_Side_तथ्य ***sd, पूर्णांक *nb_sd,
                                        क्रमागत AVFrame_Side_तथ्य_Type type,
                                        माप_प्रकार आकार, अचिन्हित पूर्णांक flags)
{
    स्थिर AVSide_तथ्य_Descriptor *desc = av_frame_side_तथ्य_desc(type);
    AVBufferRef     *buf = av_बफर_alloc(आकार);
    AVFrame_Side_तथ्य *ret = शून्य;

    अगर (flags & AV_FRAME_SIDE_तथ्य_FLAG_UNIQUE)
        av_frame_side_तथ्य_remove(sd, nb_sd, type);
    अगर ((!desc || !(desc->props & AV_SIDE_तथ्य_PROP_MULTI)) &&
        (ret = (AVFrame_Side_तथ्य *)av_frame_side_तथ्य_get(*sd, *nb_sd, type))) {
        ret = replace_side_तथ्य_from_buf(ret, buf, flags);
        अगर (!ret)
            av_बफर_unref(&buf);
        वापस ret;
    }

    ret = ff_frame_side_तथ्य_add_from_buf(sd, nb_sd, type, buf);
    अगर (!ret)
        av_बफर_unref(&buf);

    वापस ret;
}

AVFrame_Side_तथ्य *av_frame_side_तथ्य_add(AVFrame_Side_तथ्य ***sd, पूर्णांक *nb_sd,
                                        क्रमागत AVFrame_Side_तथ्य_Type type,
                                        AVBufferRef **pbuf, अचिन्हित पूर्णांक flags)
{
    स्थिर AVSide_तथ्य_Descriptor *desc = av_frame_side_तथ्य_desc(type);
    AVFrame_Side_तथ्य *sd_dst  = शून्य;
    AVBufferRef *buf = *pbuf;

    अगर ((flags & AV_FRAME_SIDE_तथ्य_FLAG_NEW_REF) && !(buf = av_बफर_ref(*pbuf)))
        वापस शून्य;
    अगर (flags & AV_FRAME_SIDE_तथ्य_FLAG_UNIQUE)
        av_frame_side_तथ्य_remove(sd, nb_sd, type);
    अगर ((!desc || !(desc->props & AV_SIDE_तथ्य_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_तथ्य *)av_frame_side_तथ्य_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_तथ्य_from_buf(sd_dst, buf, flags);
    } अन्यथा
        sd_dst = ff_frame_side_तथ्य_add_from_buf(sd, nb_sd, type, buf);

    अगर (sd_dst && !(flags & AV_FRAME_SIDE_तथ्य_FLAG_NEW_REF))
        *pbuf = शून्य;
    अन्यथा अगर (!sd_dst && (flags & AV_FRAME_SIDE_तथ्य_FLAG_NEW_REF))
        av_बफर_unref(&buf);
    वापस sd_dst;
}

पूर्णांक av_frame_side_तथ्य_clone(AVFrame_Side_तथ्य ***sd, पूर्णांक *nb_sd,
                             स्थिर AVFrame_Side_तथ्य *src, अचिन्हित पूर्णांक flags)
{
    स्थिर AVSide_तथ्य_Descriptor *desc;
    AVBufferRef     *buf    = शून्य;
    AVFrame_Side_तथ्य *sd_dst = शून्य;
    पूर्णांक              ret    = AVERROR_BUG;

    अगर (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        वापस AVERROR(EINVAL);

    desc = av_frame_side_तथ्य_desc(src->type);
    अगर (flags & AV_FRAME_SIDE_तथ्य_FLAG_UNIQUE)
        av_frame_side_तथ्य_remove(sd, nb_sd, src->type);
    अगर ((!desc || !(desc->props & AV_SIDE_तथ्य_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_तथ्य *)av_frame_side_तथ्य_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = शून्य;

        अगर (!(flags & AV_FRAME_SIDE_तथ्य_FLAG_REPLACE))
            वापस AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        अगर (ret < 0)
            वापस ret;

        ret = av_बफर_replace(&sd_dst->buf, src->buf);
        अगर (ret < 0) {
            av_dict_free(&dict);
            वापस ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->तथ्य     = src->तथ्य;
        sd_dst->आकार     = src->आकार;
        वापस 0;
    }

    buf = av_बफर_ref(src->buf);
    अगर (!buf)
        वापस AVERROR(ENOMEM);

    sd_dst = add_side_तथ्य_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->तथ्य, src->आकार);
    अगर (!sd_dst) {
        av_बफर_unref(&buf);
        वापस AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    अगर (ret < 0) {
        remove_side_तथ्य_by_entry(sd, nb_sd, sd_dst);
        वापस ret;
    }

    वापस 0;
}

स्थिर AVFrame_Side_तथ्य *av_frame_side_तथ्य_get_c(स्थिर AVFrame_Side_तथ्य * स्थिर *sd,
                                                स्थिर पूर्णांक nb_sd,
                                                क्रमागत AVFrame_Side_तथ्य_Type type)
{
    क्रम (पूर्णांक i = 0; i < nb_sd; i++) {
        अगर (sd[i]->type == type)
            वापस sd[i];
    }
    वापस शून्य;
}
