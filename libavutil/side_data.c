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

ಸ್ಥಿರ ಧ್ರುವ AVSideDataDescriptor sd_props[] = {
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

ಧ್ರುವ AVSideDataDescriptor *av_frame_side_data_desc(ಗಣನಾ AVFrameSideDataType type)
{
    unsigned t = type;
    ಯದಿ (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        ಪ್ರತ್ಯಾಗಮ &sd_props[t];
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಧ್ರುವ ವರ್ಣ *av_frame_side_data_name(ಗಣನಾ AVFrameSideDataType type)
{
    ಧ್ರುವ AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    ಪ್ರತ್ಯಾಗಮ desc ? desc->name : ರಿಕ್ತ;
}

ಸ್ಥಿರ ಶೂನ್ಯ free_side_data_entry(AVFrameSideData **ptr_sd)
{
    AVFrameSideData *sd = *ptr_sd;

    av_buffer_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

ಸ್ಥಿರ ಶೂನ್ಯ remove_side_data_by_entry(AVFrameSideData ***sd, ಪೂರ್ಣಾಙ್ಕ *nb_sd,
                                      ಧ್ರುವ AVFrameSideData *target)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        ಯದಿ (entry != target)
            ಅನುವರ್ತ;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        ಪ್ರತ್ಯಾಗಮ;
    }
}

ಶೂನ್ಯ av_frame_side_data_remove(AVFrameSideData ***sd, ಪೂರ್ಣಾಙ್ಕ *nb_sd,
                               ಗಣನಾ AVFrameSideDataType type)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        ಯದಿ (entry->type != type)
            ಅನುವರ್ತ;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

ಶೂನ್ಯ av_frame_side_data_remove_by_props(AVFrameSideData ***sd, ಪೂರ್ಣಾಙ್ಕ *nb_sd,
                                        ಪೂರ್ಣಾಙ್ಕ props)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        ಧ್ರುವ AVSideDataDescriptor *desc = av_frame_side_data_desc(entry->type);
        ಯದಿ (!desc || !(desc->props & props))
            ಅನುವರ್ತ;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

ಶೂನ್ಯ av_frame_side_data_free(AVFrameSideData ***sd, ಪೂರ್ಣಾಙ್ಕ *nb_sd)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < *nb_sd; i++)
        free_side_data_entry(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

ಸ್ಥಿರ AVFrameSideData *add_side_data_from_buf_ext(AVFrameSideData ***sd,
                                                   ಪೂರ್ಣಾಙ್ಕ *nb_sd,
                                                   ಗಣನಾ AVFrameSideDataType type,
                                                   AVBufferRef *buf, uint8_t *data,
                                                   size_t size)
{
    AVFrameSideData *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    ಯದಿ ((unsigned)*nb_sd >= FFMIN(INT_MAX, SIZE_MAX))
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    tmp = av_realloc_array(*sd, *nb_sd + 1, ಪರಿಮಾಣ(**sd));
    ಯದಿ (!tmp)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    *sd = tmp;

    ret = av_mallocz(ಪರಿಮಾಣ(*ret));
    ಯದಿ (!ret)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ret->buf = buf;
    ret->data = data;
    ret->size = size;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    ಪ್ರತ್ಯಾಗಮ ret;
}

AVFrameSideData *ff_frame_side_data_add_from_buf(AVFrameSideData ***sd,
                                                 ಪೂರ್ಣಾಙ್ಕ *nb_sd,
                                                 ಗಣನಾ AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    ಯದಿ (!buf)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಪ್ರತ್ಯಾಗಮ add_side_data_from_buf_ext(sd, nb_sd, type, buf, buf->data, buf->size);
}

ಸ್ಥಿರ AVFrameSideData *replace_side_data_from_buf(AVFrameSideData *dst,
                                                   AVBufferRef *buf, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಯದಿ (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    av_dict_free(&dst->metadata);
    av_buffer_unref(&dst->buf);
    dst->buf  = buf;
    dst->data = buf->data;
    dst->size = buf->size;
    ಪ್ರತ್ಯಾಗಮ dst;
}

AVFrameSideData *av_frame_side_data_new(AVFrameSideData ***sd, ಪೂರ್ಣಾಙ್ಕ *nb_sd,
                                        ಗಣನಾ AVFrameSideDataType type,
                                        size_t size, unsigned ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಧ್ರುವ AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVBufferRef     *buf = av_buffer_alloc(size);
    AVFrameSideData *ret = ರಿಕ್ತ;

    ಯದಿ (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    ಯದಿ ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (ret = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        ret = replace_side_data_from_buf(ret, buf, flags);
        ಯದಿ (!ret)
            av_buffer_unref(&buf);
        ಪ್ರತ್ಯಾಗಮ ret;
    }

    ret = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);
    ಯದಿ (!ret)
        av_buffer_unref(&buf);

    ಪ್ರತ್ಯಾಗಮ ret;
}

AVFrameSideData *av_frame_side_data_add(AVFrameSideData ***sd, ಪೂರ್ಣಾಙ್ಕ *nb_sd,
                                        ಗಣನಾ AVFrameSideDataType type,
                                        AVBufferRef **pbuf, unsigned ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಧ್ರುವ AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVFrameSideData *sd_dst  = ರಿಕ್ತ;
    AVBufferRef *buf = *pbuf;

    ಯದಿ ((flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF) && !(buf = av_buffer_ref(*pbuf)))
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಯದಿ (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    ಯದಿ ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_data_from_buf(sd_dst, buf, flags);
    } ಅನ್ಯಥಾ
        sd_dst = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);

    ಯದಿ (sd_dst && !(flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        *pbuf = ರಿಕ್ತ;
    ಅನ್ಯಥಾ ಯದಿ (!sd_dst && (flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        av_buffer_unref(&buf);
    ಪ್ರತ್ಯಾಗಮ sd_dst;
}

ಪೂರ್ಣಾಙ್ಕ av_frame_side_data_clone(AVFrameSideData ***sd, ಪೂರ್ಣಾಙ್ಕ *nb_sd,
                             ಧ್ರುವ AVFrameSideData *src, unsigned ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಧ್ರುವ AVSideDataDescriptor *desc;
    AVBufferRef     *buf    = ರಿಕ್ತ;
    AVFrameSideData *sd_dst = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ              ret    = AVERROR_BUG;

    ಯದಿ (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    desc = av_frame_side_data_desc(src->type);
    ಯದಿ (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, src->type);
    ಯದಿ ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = ರಿಕ್ತ;

        ಯದಿ (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
            ಪ್ರತ್ಯಾಗಮ AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;

        ret = av_buffer_replace(&sd_dst->buf, src->buf);
        ಯದಿ (ret < 0) {
            av_dict_free(&dict);
            ಪ್ರತ್ಯಾಗಮ ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->data     = src->data;
        sd_dst->size     = src->size;
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    buf = av_buffer_ref(src->buf);
    ಯದಿ (!buf)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    sd_dst = add_side_data_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->data, src->size);
    ಯದಿ (!sd_dst) {
        av_buffer_unref(&buf);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    ಯದಿ (ret < 0) {
        remove_side_data_by_entry(sd, nb_sd, sd_dst);
        ಪ್ರತ್ಯಾಗಮ ret;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಧ್ರುವ AVFrameSideData *av_frame_side_data_get_c(ಧ್ರುವ AVFrameSideData * ಧ್ರುವ *sd,
                                                ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ nb_sd,
                                                ಗಣನಾ AVFrameSideDataType type)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_sd; i++) {
        ಯದಿ (sd[i]->type == type)
            ಪ್ರತ್ಯಾಗಮ sd[i];
    }
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}
