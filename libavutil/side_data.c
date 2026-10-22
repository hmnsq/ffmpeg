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

#include "avassert.h"
#include "buffer.h"
#include "common.h"
#include "dict.h"
#include "frame.h"
#include "mem.h"
#include "side_data.h"

static const AVSideDataDescriptor sd_props[] = {
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

const AVSideDataDescriptor *av_frame_side_data_desc(ga_nanaa AVFrameSideDataType type)
{
    unsigned t = type;
    ᬬᬾᬦ᭄ (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        ᬯᬮᬶ &sd_props[t];
    ᬯᬮᬶ NULL;
}

const var_na *av_frame_side_data_name(ga_nanaa AVFrameSideDataType type)
{
    const AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    ᬯᬮᬶ desc ? desc->name : NULL;
}

static void free_side_data_entry(AVFrameSideData **ptr_sd)
{
    AVFrameSideData *sd = *ptr_sd;

    av_buffer_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

static void remove_side_data_by_entry(AVFrameSideData ***sd, puur_naa_nka *nb_sd,
                                      const AVFrameSideData *target)
{
    for (puur_naa_nka i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        ᬬᬾᬦ᭄ (entry != target)
            continue;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        ᬯᬮᬶ;
    }
}

void av_frame_side_data_remove(AVFrameSideData ***sd, puur_naa_nka *nb_sd,
                               ga_nanaa AVFrameSideDataType type)
{
    for (puur_naa_nka i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        ᬬᬾᬦ᭄ (entry->type != type)
            continue;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

void av_frame_side_data_remove_by_props(AVFrameSideData ***sd, puur_naa_nka *nb_sd,
                                        puur_naa_nka props)
{
    for (puur_naa_nka i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        const AVSideDataDescriptor *desc = av_frame_side_data_desc(entry->type);
        ᬬᬾᬦ᭄ (!desc || !(desc->props & props))
            continue;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

void av_frame_side_data_free(AVFrameSideData ***sd, puur_naa_nka *nb_sd)
{
    for (puur_naa_nka i = 0; i < *nb_sd; i++)
        free_side_data_entry(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

static AVFrameSideData *add_side_data_from_buf_ext(AVFrameSideData ***sd,
                                                   puur_naa_nka *nb_sd,
                                                   ga_nanaa AVFrameSideDataType type,
                                                   AVBufferRef *buf, uint8_t *data,
                                                   size_t size)
{
    AVFrameSideData *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    ᬬᬾᬦ᭄ ((unsigned)*nb_sd >= FFMIN(INT_MAX, SIZE_MAX))
        ᬯᬮᬶ NULL;

    tmp = av_realloc_array(*sd, *nb_sd + 1, parimaa_na(**sd));
    ᬬᬾᬦ᭄ (!tmp)
        ᬯᬮᬶ NULL;
    *sd = tmp;

    ret = av_mallocz(parimaa_na(*ret));
    ᬬᬾᬦ᭄ (!ret)
        ᬯᬮᬶ NULL;

    ret->buf = buf;
    ret->data = data;
    ret->size = size;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    ᬯᬮᬶ ret;
}

AVFrameSideData *ff_frame_side_data_add_from_buf(AVFrameSideData ***sd,
                                                 puur_naa_nka *nb_sd,
                                                 ga_nanaa AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    ᬬᬾᬦ᭄ (!buf)
        ᬯᬮᬶ NULL;

    ᬯᬮᬶ add_side_data_from_buf_ext(sd, nb_sd, type, buf, buf->data, buf->size);
}

static AVFrameSideData *replace_side_data_from_buf(AVFrameSideData *dst,
                                                   AVBufferRef *buf, puur_naa_nka flags)
{
    ᬬᬾᬦ᭄ (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
        ᬯᬮᬶ NULL;

    av_dict_free(&dst->metadata);
    av_buffer_unref(&dst->buf);
    dst->buf  = buf;
    dst->data = buf->data;
    dst->size = buf->size;
    ᬯᬮᬶ dst;
}

AVFrameSideData *av_frame_side_data_new(AVFrameSideData ***sd, puur_naa_nka *nb_sd,
                                        ga_nanaa AVFrameSideDataType type,
                                        size_t size, unsigned puur_naa_nka flags)
{
    const AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVBufferRef     *buf = av_buffer_alloc(size);
    AVFrameSideData *ret = NULL;

    ᬬᬾᬦ᭄ (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    ᬬᬾᬦ᭄ ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (ret = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        ret = replace_side_data_from_buf(ret, buf, flags);
        ᬬᬾᬦ᭄ (!ret)
            av_buffer_unref(&buf);
        ᬯᬮᬶ ret;
    }

    ret = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);
    ᬬᬾᬦ᭄ (!ret)
        av_buffer_unref(&buf);

    ᬯᬮᬶ ret;
}

AVFrameSideData *av_frame_side_data_add(AVFrameSideData ***sd, puur_naa_nka *nb_sd,
                                        ga_nanaa AVFrameSideDataType type,
                                        AVBufferRef **pbuf, unsigned puur_naa_nka flags)
{
    const AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVFrameSideData *sd_dst  = NULL;
    AVBufferRef *buf = *pbuf;

    ᬬᬾᬦ᭄ ((flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF) && !(buf = av_buffer_ref(*pbuf)))
        ᬯᬮᬶ NULL;
    ᬬᬾᬦ᭄ (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    ᬬᬾᬦ᭄ ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_data_from_buf(sd_dst, buf, flags);
    } ᬮᬶᬬ
        sd_dst = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);

    ᬬᬾᬦ᭄ (sd_dst && !(flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        *pbuf = NULL;
    ᬮᬶᬬ ᬬᬾᬦ᭄ (!sd_dst && (flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        av_buffer_unref(&buf);
    ᬯᬮᬶ sd_dst;
}

puur_naa_nka av_frame_side_data_clone(AVFrameSideData ***sd, puur_naa_nka *nb_sd,
                             const AVFrameSideData *src, unsigned puur_naa_nka flags)
{
    const AVSideDataDescriptor *desc;
    AVBufferRef     *buf    = NULL;
    AVFrameSideData *sd_dst = NULL;
    puur_naa_nka              ret    = AVERROR_BUG;

    ᬬᬾᬦ᭄ (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        ᬯᬮᬶ AVERROR(EINVAL);

    desc = av_frame_side_data_desc(src->type);
    ᬬᬾᬦ᭄ (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, src->type);
    ᬬᬾᬦ᭄ ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = NULL;

        ᬬᬾᬦ᭄ (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
            ᬯᬮᬶ AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        ᬬᬾᬦ᭄ (ret < 0)
            ᬯᬮᬶ ret;

        ret = av_buffer_replace(&sd_dst->buf, src->buf);
        ᬬᬾᬦ᭄ (ret < 0) {
            av_dict_free(&dict);
            ᬯᬮᬶ ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->data     = src->data;
        sd_dst->size     = src->size;
        ᬯᬮᬶ 0;
    }

    buf = av_buffer_ref(src->buf);
    ᬬᬾᬦ᭄ (!buf)
        ᬯᬮᬶ AVERROR(ENOMEM);

    sd_dst = add_side_data_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->data, src->size);
    ᬬᬾᬦ᭄ (!sd_dst) {
        av_buffer_unref(&buf);
        ᬯᬮᬶ AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    ᬬᬾᬦ᭄ (ret < 0) {
        remove_side_data_by_entry(sd, nb_sd, sd_dst);
        ᬯᬮᬶ ret;
    }

    ᬯᬮᬶ 0;
}

const AVFrameSideData *av_frame_side_data_get_c(const AVFrameSideData * const *sd,
                                                const puur_naa_nka nb_sd,
                                                ga_nanaa AVFrameSideDataType type)
{
    for (puur_naa_nka i = 0; i < nb_sd; i++) {
        ᬬᬾᬦ᭄ (sd[i]->type == type)
            ᬯᬮᬶ sd[i];
    }
    ᬯᬮᬶ NULL;
}
