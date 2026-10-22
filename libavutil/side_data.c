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

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "buffer.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "dict.h"
#ଅନ୍ତର୍ଭାଵ "frame.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "side_data.h"

ସ୍ଥିର ଅଚଳ AVSideDataDescriptor sd_props[] = {
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

ଅଚଳ AVSideDataDescriptor *av_frame_side_data_desc(ଗଣନା AVFrameSideDataType type)
{
    unsigned t = type;
    ଯଦି (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        ଫେରନ୍ତୁ &sd_props[t];
    ଫେରନ୍ତୁ ଖାଲି;
}

ଅଚଳ ଅକ୍ଷର *av_frame_side_data_name(ଗଣନା AVFrameSideDataType type)
{
    ଅଚଳ AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    ଫେରନ୍ତୁ desc ? desc->name : ଖାଲି;
}

ସ୍ଥିର ଶୂନ୍ୟ free_side_data_entry(AVFrameSideData **ptr_sd)
{
    AVFrameSideData *sd = *ptr_sd;

    av_buffer_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

ସ୍ଥିର ଶୂନ୍ୟ remove_side_data_by_entry(AVFrameSideData ***sd, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_sd,
                                      ଅଚଳ AVFrameSideData *target)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        ଯଦି (entry != target)
            ଜାରି;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        ଫେରନ୍ତୁ;
    }
}

ଶୂନ୍ୟ av_frame_side_data_remove(AVFrameSideData ***sd, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_sd,
                               ଗଣନା AVFrameSideDataType type)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        ଯଦି (entry->type != type)
            ଜାରି;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

ଶୂନ୍ୟ av_frame_side_data_remove_by_props(AVFrameSideData ***sd, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_sd,
                                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା props)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        ଅଚଳ AVSideDataDescriptor *desc = av_frame_side_data_desc(entry->type);
        ଯଦି (!desc || !(desc->props & props))
            ଜାରି;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

ଶୂନ୍ୟ av_frame_side_data_free(AVFrameSideData ***sd, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_sd)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < *nb_sd; i++)
        free_side_data_entry(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

ସ୍ଥିର AVFrameSideData *add_side_data_from_buf_ext(AVFrameSideData ***sd,
                                                   ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_sd,
                                                   ଗଣନା AVFrameSideDataType type,
                                                   AVBufferRef *buf, uint8_t *data,
                                                   size_t size)
{
    AVFrameSideData *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    ଯଦି ((unsigned)*nb_sd >= FFMIN(INT_MAX, SIZE_MAX))
        ଫେରନ୍ତୁ ଖାଲି;

    tmp = av_realloc_array(*sd, *nb_sd + 1, ଆକାର(**sd));
    ଯଦି (!tmp)
        ଫେରନ୍ତୁ ଖାଲି;
    *sd = tmp;

    ret = av_mallocz(ଆକାର(*ret));
    ଯଦି (!ret)
        ଫେରନ୍ତୁ ଖାଲି;

    ret->buf = buf;
    ret->data = data;
    ret->size = size;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    ଫେରନ୍ତୁ ret;
}

AVFrameSideData *ff_frame_side_data_add_from_buf(AVFrameSideData ***sd,
                                                 ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_sd,
                                                 ଗଣନା AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    ଯଦି (!buf)
        ଫେରନ୍ତୁ ଖାଲି;

    ଫେରନ୍ତୁ add_side_data_from_buf_ext(sd, nb_sd, type, buf, buf->data, buf->size);
}

ସ୍ଥିର AVFrameSideData *replace_side_data_from_buf(AVFrameSideData *dst,
                                                   AVBufferRef *buf, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଯଦି (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
        ଫେରନ୍ତୁ ଖାଲି;

    av_dict_free(&dst->metadata);
    av_buffer_unref(&dst->buf);
    dst->buf  = buf;
    dst->data = buf->data;
    dst->size = buf->size;
    ଫେରନ୍ତୁ dst;
}

AVFrameSideData *av_frame_side_data_new(AVFrameSideData ***sd, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_sd,
                                        ଗଣନା AVFrameSideDataType type,
                                        size_t size, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଅଚଳ AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVBufferRef     *buf = av_buffer_alloc(size);
    AVFrameSideData *ret = ଖାଲି;

    ଯଦି (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    ଯଦି ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (ret = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        ret = replace_side_data_from_buf(ret, buf, flags);
        ଯଦି (!ret)
            av_buffer_unref(&buf);
        ଫେରନ୍ତୁ ret;
    }

    ret = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);
    ଯଦି (!ret)
        av_buffer_unref(&buf);

    ଫେରନ୍ତୁ ret;
}

AVFrameSideData *av_frame_side_data_add(AVFrameSideData ***sd, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_sd,
                                        ଗଣନା AVFrameSideDataType type,
                                        AVBufferRef **pbuf, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଅଚଳ AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVFrameSideData *sd_dst  = ଖାଲି;
    AVBufferRef *buf = *pbuf;

    ଯଦି ((flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF) && !(buf = av_buffer_ref(*pbuf)))
        ଫେରନ୍ତୁ ଖାଲି;
    ଯଦି (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    ଯଦି ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_data_from_buf(sd_dst, buf, flags);
    } ଅନ୍ୟଥା
        sd_dst = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);

    ଯଦି (sd_dst && !(flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        *pbuf = ଖାଲି;
    ଅନ୍ୟଥା ଯଦି (!sd_dst && (flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        av_buffer_unref(&buf);
    ଫେରନ୍ତୁ sd_dst;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_frame_side_data_clone(AVFrameSideData ***sd, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_sd,
                             ଅଚଳ AVFrameSideData *src, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଅଚଳ AVSideDataDescriptor *desc;
    AVBufferRef     *buf    = ଖାଲି;
    AVFrameSideData *sd_dst = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              ret    = AVERROR_BUG;

    ଯଦି (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    desc = av_frame_side_data_desc(src->type);
    ଯଦି (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, src->type);
    ଯଦି ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = ଖାଲି;

        ଯଦି (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
            ଫେରନ୍ତୁ AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;

        ret = av_buffer_replace(&sd_dst->buf, src->buf);
        ଯଦି (ret < 0) {
            av_dict_free(&dict);
            ଫେରନ୍ତୁ ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->data     = src->data;
        sd_dst->size     = src->size;
        ଫେରନ୍ତୁ 0;
    }

    buf = av_buffer_ref(src->buf);
    ଯଦି (!buf)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    sd_dst = add_side_data_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->data, src->size);
    ଯଦି (!sd_dst) {
        av_buffer_unref(&buf);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    ଯଦି (ret < 0) {
        remove_side_data_by_entry(sd, nb_sd, sd_dst);
        ଫେରନ୍ତୁ ret;
    }

    ଫେରନ୍ତୁ 0;
}

ଅଚଳ AVFrameSideData *av_frame_side_data_get_c(ଅଚଳ AVFrameSideData * ଅଚଳ *sd,
                                                ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_sd,
                                                ଗଣନା AVFrameSideDataType type)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_sd; i++) {
        ଯଦି (sd[i]->type == type)
            ଫେରନ୍ତୁ sd[i];
    }
    ଫେରନ୍ତୁ ଖାଲି;
}
