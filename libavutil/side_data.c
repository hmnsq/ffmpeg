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

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "buffer.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "dict.h"
#അന്തര്ഭാവ "frame.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "side_data.h"

സ്ഥിതം സ്ഥിരം AVSideDataDescriptor sd_props[] = {
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

സ്ഥിരം AVSideDataDescriptor *av_frame_side_data_desc(എണ്ണൽ AVFrameSideDataType type)
{
    unsigned t = type;
    എങ്കിൽ (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        തിരികെ &sd_props[t];
    തിരികെ ശൂന്യ;
}

സ്ഥിരം അക്ഷരം *av_frame_side_data_name(എണ്ണൽ AVFrameSideDataType type)
{
    സ്ഥിരം AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    തിരികെ desc ? desc->name : ശൂന്യ;
}

സ്ഥിതം ശൂന്യം free_side_data_entry(AVFrameSideData **ptr_sd)
{
    AVFrameSideData *sd = *ptr_sd;

    av_buffer_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

സ്ഥിതം ശൂന്യം remove_side_data_by_entry(AVFrameSideData ***sd, പൂർണ്ണസംഖ്യ *nb_sd,
                                      സ്ഥിരം AVFrameSideData *target)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        എങ്കിൽ (entry != target)
            തുടരുക;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        തിരികെ;
    }
}

ശൂന്യം av_frame_side_data_remove(AVFrameSideData ***sd, പൂർണ്ണസംഖ്യ *nb_sd,
                               എണ്ണൽ AVFrameSideDataType type)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        എങ്കിൽ (entry->type != type)
            തുടരുക;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

ശൂന്യം av_frame_side_data_remove_by_props(AVFrameSideData ***sd, പൂർണ്ണസംഖ്യ *nb_sd,
                                        പൂർണ്ണസംഖ്യ props)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        സ്ഥിരം AVSideDataDescriptor *desc = av_frame_side_data_desc(entry->type);
        എങ്കിൽ (!desc || !(desc->props & props))
            തുടരുക;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

ശൂന്യം av_frame_side_data_free(AVFrameSideData ***sd, പൂർണ്ണസംഖ്യ *nb_sd)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < *nb_sd; i++)
        free_side_data_entry(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

സ്ഥിതം AVFrameSideData *add_side_data_from_buf_ext(AVFrameSideData ***sd,
                                                   പൂർണ്ണസംഖ്യ *nb_sd,
                                                   എണ്ണൽ AVFrameSideDataType type,
                                                   AVBufferRef *buf, uint8_t *data,
                                                   size_t size)
{
    AVFrameSideData *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    എങ്കിൽ ((unsigned)*nb_sd >= FFMIN(INT_MAX, SIZE_MAX))
        തിരികെ ശൂന്യ;

    tmp = av_realloc_array(*sd, *nb_sd + 1, വലുപ്പം(**sd));
    എങ്കിൽ (!tmp)
        തിരികെ ശൂന്യ;
    *sd = tmp;

    ret = av_mallocz(വലുപ്പം(*ret));
    എങ്കിൽ (!ret)
        തിരികെ ശൂന്യ;

    ret->buf = buf;
    ret->data = data;
    ret->size = size;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    തിരികെ ret;
}

AVFrameSideData *ff_frame_side_data_add_from_buf(AVFrameSideData ***sd,
                                                 പൂർണ്ണസംഖ്യ *nb_sd,
                                                 എണ്ണൽ AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    എങ്കിൽ (!buf)
        തിരികെ ശൂന്യ;

    തിരികെ add_side_data_from_buf_ext(sd, nb_sd, type, buf, buf->data, buf->size);
}

സ്ഥിതം AVFrameSideData *replace_side_data_from_buf(AVFrameSideData *dst,
                                                   AVBufferRef *buf, പൂർണ്ണസംഖ്യ flags)
{
    എങ്കിൽ (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
        തിരികെ ശൂന്യ;

    av_dict_free(&dst->metadata);
    av_buffer_unref(&dst->buf);
    dst->buf  = buf;
    dst->data = buf->data;
    dst->size = buf->size;
    തിരികെ dst;
}

AVFrameSideData *av_frame_side_data_new(AVFrameSideData ***sd, പൂർണ്ണസംഖ്യ *nb_sd,
                                        എണ്ണൽ AVFrameSideDataType type,
                                        size_t size, unsigned പൂർണ്ണസംഖ്യ flags)
{
    സ്ഥിരം AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVBufferRef     *buf = av_buffer_alloc(size);
    AVFrameSideData *ret = ശൂന്യ;

    എങ്കിൽ (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    എങ്കിൽ ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (ret = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        ret = replace_side_data_from_buf(ret, buf, flags);
        എങ്കിൽ (!ret)
            av_buffer_unref(&buf);
        തിരികെ ret;
    }

    ret = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);
    എങ്കിൽ (!ret)
        av_buffer_unref(&buf);

    തിരികെ ret;
}

AVFrameSideData *av_frame_side_data_add(AVFrameSideData ***sd, പൂർണ്ണസംഖ്യ *nb_sd,
                                        എണ്ണൽ AVFrameSideDataType type,
                                        AVBufferRef **pbuf, unsigned പൂർണ്ണസംഖ്യ flags)
{
    സ്ഥിരം AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVFrameSideData *sd_dst  = ശൂന്യ;
    AVBufferRef *buf = *pbuf;

    എങ്കിൽ ((flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF) && !(buf = av_buffer_ref(*pbuf)))
        തിരികെ ശൂന്യ;
    എങ്കിൽ (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    എങ്കിൽ ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_data_from_buf(sd_dst, buf, flags);
    } അല്ലെങ്കിൽ
        sd_dst = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);

    എങ്കിൽ (sd_dst && !(flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        *pbuf = ശൂന്യ;
    അല്ലെങ്കിൽ എങ്കിൽ (!sd_dst && (flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        av_buffer_unref(&buf);
    തിരികെ sd_dst;
}

പൂർണ്ണസംഖ്യ av_frame_side_data_clone(AVFrameSideData ***sd, പൂർണ്ണസംഖ്യ *nb_sd,
                             സ്ഥിരം AVFrameSideData *src, unsigned പൂർണ്ണസംഖ്യ flags)
{
    സ്ഥിരം AVSideDataDescriptor *desc;
    AVBufferRef     *buf    = ശൂന്യ;
    AVFrameSideData *sd_dst = ശൂന്യ;
    പൂർണ്ണസംഖ്യ              ret    = AVERROR_BUG;

    എങ്കിൽ (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        തിരികെ AVERROR(EINVAL);

    desc = av_frame_side_data_desc(src->type);
    എങ്കിൽ (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, src->type);
    എങ്കിൽ ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = ശൂന്യ;

        എങ്കിൽ (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
            തിരികെ AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        എങ്കിൽ (ret < 0)
            തിരികെ ret;

        ret = av_buffer_replace(&sd_dst->buf, src->buf);
        എങ്കിൽ (ret < 0) {
            av_dict_free(&dict);
            തിരികെ ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->data     = src->data;
        sd_dst->size     = src->size;
        തിരികെ 0;
    }

    buf = av_buffer_ref(src->buf);
    എങ്കിൽ (!buf)
        തിരികെ AVERROR(ENOMEM);

    sd_dst = add_side_data_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->data, src->size);
    എങ്കിൽ (!sd_dst) {
        av_buffer_unref(&buf);
        തിരികെ AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    എങ്കിൽ (ret < 0) {
        remove_side_data_by_entry(sd, nb_sd, sd_dst);
        തിരികെ ret;
    }

    തിരികെ 0;
}

സ്ഥിരം AVFrameSideData *av_frame_side_data_get_c(സ്ഥിരം AVFrameSideData * സ്ഥിരം *sd,
                                                സ്ഥിരം പൂർണ്ണസംഖ്യ nb_sd,
                                                എണ്ണൽ AVFrameSideDataType type)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < nb_sd; i++) {
        എങ്കിൽ (sd[i]->type == type)
            തിരികെ sd[i];
    }
    തിരികെ ശൂന്യ;
}
