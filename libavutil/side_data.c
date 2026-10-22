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

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "buffer.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "dict.h"
#अन्तर्भाव "frame.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "side_data.h"

स्थिर स्थिरांक AVSideDataDescriptor sd_props[] = {
    [AV_FRAME_DATA_PANSCAN]                     = { "AVPanScan",                                    AV_SIDE_DATA_PROP_SIZE_DEPENDENT },
    [AV_FRAME_DATA_A53_CC]                      = { "ATSC A53 Part 4 Closed Captions" },
    [AV_FRAME_DATA_MATRIXENCODING]              = { "AVMatrixEncoding",                             AV_SIDE_DATA_PROP_CHANNEL_DEPENDENT },
    [AV_FRAME_DATA_DOWNMIX_INFO]                = { "Metadata relevant to a downmix procedure",     AV_SIDE_DATA_PROP_CHANNEL_DEPENDENT },
    [AV_FRAME_DATA_AFD]                         = { "Active format description" },
    [AV_FRAME_DATA_MOTION_VECTORS]              = { "Motion vectors",                               AV_SIDE_DATA_PROP_SIZE_DEPENDENT },
    [AV_FRAME_DATA_SKIP_SAMPLES]                = { "Skip samples" },
    [AV_FRAME_DATA_GOP_TIMECODE]                = { "GOP timecode" },
    [AV_FRAME_DATA_S12M_TIMECODE]               = { "SMPTE 12-1 timecode" },
    [AV_FRAME_DATA_DYNAMIC_HDR_PLUS]            = { "HDR Dynamic Metadata SMPTE2094-40 (HDR10+)",   AV_SIDE_DATA_PROP_COLOR_DEPENDENT },
    [AV_FRAME_DATA_DYNAMIC_HDR_VIVID]           = { "HDR Dynamic Metadata CUVA 005.1 2021 (Vivid)", AV_SIDE_DATA_PROP_COLOR_DEPENDENT },
    [AV_FRAME_DATA_DYNAMIC_HDR_SMPTE_2094_APP5] = { "HDR Dynamic Metadata SMPTE2094-50",            AV_SIDE_DATA_PROP_COLOR_DEPENDENT },
    [AV_FRAME_DATA_REGIONS_OF_INTEREST]         = { "Regions Of Interest",                          AV_SIDE_DATA_PROP_SIZE_DEPENDENT },
    [AV_FRAME_DATA_VIDEO_ENC_PARAMS]            = { "Video encoding parameters" },
    [AV_FRAME_DATA_FILM_GRAIN_PARAMS]           = { "Film grain parameters" },
    [AV_FRAME_DATA_DETECTION_BBOXES]            = { "Bounding boxes for object detection and classification", AV_SIDE_DATA_PROP_SIZE_DEPENDENT },
    [AV_FRAME_DATA_DOVI_RPU_BUFFER]             = { "Dolby Vision RPU Data",                        AV_SIDE_DATA_PROP_COLOR_DEPENDENT },
    [AV_FRAME_DATA_DOVI_METADATA]               = { "Dolby Vision Metadata",                        AV_SIDE_DATA_PROP_COLOR_DEPENDENT },
    [AV_FRAME_DATA_LCEVC]                       = { "LCEVC NAL data",                               AV_SIDE_DATA_PROP_SIZE_DEPENDENT },
    [AV_FRAME_DATA_VIEW_ID]                     = { "View ID" },
    [AV_FRAME_DATA_STEREO3D]                    = { "Stereo 3D",                                    AV_SIDE_DATA_PROP_GLOBAL },
    [AV_FRAME_DATA_REPLAYGAIN]                  = { "AVReplayGain",                                 AV_SIDE_DATA_PROP_GLOBAL },
    [AV_FRAME_DATA_DISPLAYMATRIX]               = { "3x3 displaymatrix",                            AV_SIDE_DATA_PROP_GLOBAL },
    [AV_FRAME_DATA_AUDIO_SERVICE_TYPE]          = { "Audio service type",                           AV_SIDE_DATA_PROP_GLOBAL },
    [AV_FRAME_DATA_MASTERING_DISPLAY_METADATA]  = { "Mastering display metadata",                   AV_SIDE_DATA_PROP_GLOBAL | AV_SIDE_DATA_PROP_COLOR_DEPENDENT },
    [AV_FRAME_DATA_CONTENT_LIGHT_LEVEL]         = { "Content light level metadata",                 AV_SIDE_DATA_PROP_GLOBAL | AV_SIDE_DATA_PROP_COLOR_DEPENDENT },
    [AV_FRAME_DATA_AMBIENT_VIEWING_ENVIRONMENT] = { "Ambient viewing environment",                  AV_SIDE_DATA_PROP_GLOBAL },
    [AV_FRAME_DATA_SPHERICAL]                   = { "Spherical Mapping",                            AV_SIDE_DATA_PROP_GLOBAL | AV_SIDE_DATA_PROP_SIZE_DEPENDENT },
    [AV_FRAME_DATA_ICC_PROFILE]                 = { "ICC profile",                                  AV_SIDE_DATA_PROP_GLOBAL | AV_SIDE_DATA_PROP_COLOR_DEPENDENT },
    [AV_FRAME_DATA_EXIF]                        = { "EXIF metadata",                                AV_SIDE_DATA_PROP_GLOBAL },
    [AV_FRAME_DATA_SEI_UNREGISTERED]            = { "H.26[45] User Data Unregistered SEI message",  AV_SIDE_DATA_PROP_MULTI },
    [AV_FRAME_DATA_VIDEO_HINT]                  = { "Encoding video hint",                          AV_SIDE_DATA_PROP_SIZE_DEPENDENT },
    [AV_FRAME_DATA_3D_REFERENCE_DISPLAYS]       = { "3D Reference Displays Information",            AV_SIDE_DATA_PROP_GLOBAL },
    [AV_FRAME_DATA_IAMF_MIX_GAIN_PARAM]         = { "IAMF Mix Gain Parameter Data" },
    [AV_FRAME_DATA_IAMF_DEMIXING_INFO_PARAM]    = { "IAMF Demixing Info Parameter Data",            AV_SIDE_DATA_PROP_CHANNEL_DEPENDENT },
    [AV_FRAME_DATA_IAMF_RECON_GAIN_INFO_PARAM]  = { "IAMF Recon Gain Info Parameter Data" },
    [AV_FRAME_DATA_RAW_COLOR_PARAMS]            = { "RAW camera color parameters",                  AV_SIDE_DATA_PROP_GLOBAL | AV_SIDE_DATA_PROP_COLOR_DEPENDENT },
    [AV_FRAME_DATA_DOWNMIX_MATRIX]              = { "Downmix Matrix",                               AV_SIDE_DATA_PROP_CHANNEL_DEPENDENT },
    [AV_FRAME_DATA_GAIN_MAP_PARAMS]             = { "Gain map parameters",                          AV_SIDE_DATA_PROP_GLOBAL | AV_SIDE_DATA_PROP_COLOR_DEPENDENT },
};

स्थिरांक AVSideDataDescriptor *av_frame_side_data_desc(गणना AVFrameSideDataType type)
{
    अचिन्हित t = type;
    जर (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        परत &sd_props[t];
    परत रिक्त;
}

स्थिरांक अक्षर *av_frame_side_data_name(गणना AVFrameSideDataType type)
{
    स्थिरांक AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    परत desc ? desc->name : रिक्त;
}

स्थिर शून्य free_side_data_entry(AVFrameSideData **ptr_sd)
{
    AVFrameSideData *sd = *ptr_sd;

    av_buffer_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

स्थिर शून्य remove_side_data_by_entry(AVFrameSideData ***sd, पूर्णांक *nb_sd,
                                      स्थिरांक AVFrameSideData *target)
{
    साठी (पूर्णांक i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        जर (entry != target)
            सुरूठेवा;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        परत;
    }
}

शून्य av_frame_side_data_remove(AVFrameSideData ***sd, पूर्णांक *nb_sd,
                               गणना AVFrameSideDataType type)
{
    साठी (पूर्णांक i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        जर (entry->type != type)
            सुरूठेवा;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

शून्य av_frame_side_data_remove_by_props(AVFrameSideData ***sd, पूर्णांक *nb_sd,
                                        पूर्णांक props)
{
    साठी (पूर्णांक i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        स्थिरांक AVSideDataDescriptor *desc = av_frame_side_data_desc(entry->type);
        जर (!desc || !(desc->props & props))
            सुरूठेवा;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

शून्य av_frame_side_data_free(AVFrameSideData ***sd, पूर्णांक *nb_sd)
{
    साठी (पूर्णांक i = 0; i < *nb_sd; i++)
        free_side_data_entry(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

स्थिर AVFrameSideData *add_side_data_from_buf_ext(AVFrameSideData ***sd,
                                                   पूर्णांक *nb_sd,
                                                   गणना AVFrameSideDataType type,
                                                   AVBufferRef *buf, uint8_t *data,
                                                   माप_प्रकार size)
{
    AVFrameSideData *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    जर ((अचिन्हित)*nb_sd >= FFMIN(पूर्णांक_उच्च, SIZE_MAX))
        परत रिक्त;

    tmp = av_realloc_array(*sd, *nb_sd + 1, आकार(**sd));
    जर (!tmp)
        परत रिक्त;
    *sd = tmp;

    ret = av_mallocz(आकार(*ret));
    जर (!ret)
        परत रिक्त;

    ret->buf = buf;
    ret->data = data;
    ret->size = size;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    परत ret;
}

AVFrameSideData *ff_frame_side_data_add_from_buf(AVFrameSideData ***sd,
                                                 पूर्णांक *nb_sd,
                                                 गणना AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    जर (!buf)
        परत रिक्त;

    परत add_side_data_from_buf_ext(sd, nb_sd, type, buf, buf->data, buf->size);
}

स्थिर AVFrameSideData *replace_side_data_from_buf(AVFrameSideData *dst,
                                                   AVBufferRef *buf, पूर्णांक flags)
{
    जर (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
        परत रिक्त;

    av_dict_free(&dst->metadata);
    av_buffer_unref(&dst->buf);
    dst->buf  = buf;
    dst->data = buf->data;
    dst->size = buf->size;
    परत dst;
}

AVFrameSideData *av_frame_side_data_new(AVFrameSideData ***sd, पूर्णांक *nb_sd,
                                        गणना AVFrameSideDataType type,
                                        माप_प्रकार size, अचिन्हित पूर्णांक flags)
{
    स्थिरांक AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVBufferRef     *buf = av_buffer_alloc(size);
    AVFrameSideData *ret = रिक्त;

    जर (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    जर ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (ret = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        ret = replace_side_data_from_buf(ret, buf, flags);
        जर (!ret)
            av_buffer_unref(&buf);
        परत ret;
    }

    ret = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);
    जर (!ret)
        av_buffer_unref(&buf);

    परत ret;
}

AVFrameSideData *av_frame_side_data_add(AVFrameSideData ***sd, पूर्णांक *nb_sd,
                                        गणना AVFrameSideDataType type,
                                        AVBufferRef **pbuf, अचिन्हित पूर्णांक flags)
{
    स्थिरांक AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVFrameSideData *sd_dst  = रिक्त;
    AVBufferRef *buf = *pbuf;

    जर ((flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF) && !(buf = av_buffer_ref(*pbuf)))
        परत रिक्त;
    जर (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    जर ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_data_from_buf(sd_dst, buf, flags);
    } अन्यथा
        sd_dst = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);

    जर (sd_dst && !(flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        *pbuf = रिक्त;
    अन्यथा जर (!sd_dst && (flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        av_buffer_unref(&buf);
    परत sd_dst;
}

पूर्णांक av_frame_side_data_clone(AVFrameSideData ***sd, पूर्णांक *nb_sd,
                             स्थिरांक AVFrameSideData *src, अचिन्हित पूर्णांक flags)
{
    स्थिरांक AVSideDataDescriptor *desc;
    AVBufferRef     *buf    = रिक्त;
    AVFrameSideData *sd_dst = रिक्त;
    पूर्णांक              ret    = AVERROR_BUG;

    जर (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        परत AVERROR(EINVAL);

    desc = av_frame_side_data_desc(src->type);
    जर (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, src->type);
    जर ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = रिक्त;

        जर (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
            परत AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        जर (ret < 0)
            परत ret;

        ret = av_buffer_replace(&sd_dst->buf, src->buf);
        जर (ret < 0) {
            av_dict_free(&dict);
            परत ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->data     = src->data;
        sd_dst->size     = src->size;
        परत 0;
    }

    buf = av_buffer_ref(src->buf);
    जर (!buf)
        परत AVERROR(ENOMEM);

    sd_dst = add_side_data_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->data, src->size);
    जर (!sd_dst) {
        av_buffer_unref(&buf);
        परत AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    जर (ret < 0) {
        remove_side_data_by_entry(sd, nb_sd, sd_dst);
        परत ret;
    }

    परत 0;
}

स्थिरांक AVFrameSideData *av_frame_side_data_get_c(स्थिरांक AVFrameSideData * स्थिरांक *sd,
                                                स्थिरांक पूर्णांक nb_sd,
                                                गणना AVFrameSideDataType type)
{
    साठी (पूर्णांक i = 0; i < nb_sd; i++) {
        जर (sd[i]->type == type)
            परत sd[i];
    }
    परत रिक्त;
}
