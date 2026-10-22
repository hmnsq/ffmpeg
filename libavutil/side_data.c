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

#ضمن "avassert.h"
#ضمن "buffer.h"
#ضمن "common.h"
#ضمن "dict.h"
#ضمن "frame.h"
#ضمن "mem.h"
#ضمن "side_data.h"

ساكن ثابت AVSideDataDescriptor sd_props[] = {
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

ثابت AVSideDataDescriptor *av_frame_side_data_desc(تعداد AVFrameSideDataType type)
{
    unsigned t = type;
    𐤀𐤌 (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        أرجع &sd_props[t];
    أرجع عدم;
}

ثابت حرف *av_frame_side_data_name(تعداد AVFrameSideDataType type)
{
    ثابت AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    أرجع desc ? desc->name : عدم;
}

ساكن فراغ free_side_data_entry(AVFrameSideData **ptr_sd)
{
    AVFrameSideData *sd = *ptr_sd;

    av_buffer_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

ساكن فراغ remove_side_data_by_entry(AVFrameSideData ***sd, صحيح *nb_sd,
                                      ثابت AVFrameSideData *target)
{
    لكل (صحيح i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        𐤀𐤌 (entry != target)
            استمر;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        أرجع;
    }
}

فراغ av_frame_side_data_remove(AVFrameSideData ***sd, صحيح *nb_sd,
                               تعداد AVFrameSideDataType type)
{
    لكل (صحيح i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        𐤀𐤌 (entry->type != type)
            استمر;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

فراغ av_frame_side_data_remove_by_props(AVFrameSideData ***sd, صحيح *nb_sd,
                                        صحيح props)
{
    لكل (صحيح i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        ثابت AVSideDataDescriptor *desc = av_frame_side_data_desc(entry->type);
        𐤀𐤌 (!desc || !(desc->props & props))
            استمر;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

فراغ av_frame_side_data_free(AVFrameSideData ***sd, صحيح *nb_sd)
{
    لكل (صحيح i = 0; i < *nb_sd; i++)
        free_side_data_entry(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

ساكن AVFrameSideData *add_side_data_from_buf_ext(AVFrameSideData ***sd,
                                                   صحيح *nb_sd,
                                                   تعداد AVFrameSideDataType type,
                                                   AVBufferRef *buf, uint8_t *data,
                                                   size_t size)
{
    AVFrameSideData *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    𐤀𐤌 ((unsigned)*nb_sd >= FFMIN(INT_MAX, SIZE_MAX))
        أرجع عدم;

    tmp = av_realloc_array(*sd, *nb_sd + 1, حجم(**sd));
    𐤀𐤌 (!tmp)
        أرجع عدم;
    *sd = tmp;

    ret = av_mallocz(حجم(*ret));
    𐤀𐤌 (!ret)
        أرجع عدم;

    ret->buf = buf;
    ret->data = data;
    ret->size = size;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    أرجع ret;
}

AVFrameSideData *ff_frame_side_data_add_from_buf(AVFrameSideData ***sd,
                                                 صحيح *nb_sd,
                                                 تعداد AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    𐤀𐤌 (!buf)
        أرجع عدم;

    أرجع add_side_data_from_buf_ext(sd, nb_sd, type, buf, buf->data, buf->size);
}

ساكن AVFrameSideData *replace_side_data_from_buf(AVFrameSideData *dst,
                                                   AVBufferRef *buf, صحيح flags)
{
    𐤀𐤌 (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
        أرجع عدم;

    av_dict_free(&dst->metadata);
    av_buffer_unref(&dst->buf);
    dst->buf  = buf;
    dst->data = buf->data;
    dst->size = buf->size;
    أرجع dst;
}

AVFrameSideData *av_frame_side_data_new(AVFrameSideData ***sd, صحيح *nb_sd,
                                        تعداد AVFrameSideDataType type,
                                        size_t size, unsigned صحيح flags)
{
    ثابت AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVBufferRef     *buf = av_buffer_alloc(size);
    AVFrameSideData *ret = عدم;

    𐤀𐤌 (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    𐤀𐤌 ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (ret = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        ret = replace_side_data_from_buf(ret, buf, flags);
        𐤀𐤌 (!ret)
            av_buffer_unref(&buf);
        أرجع ret;
    }

    ret = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);
    𐤀𐤌 (!ret)
        av_buffer_unref(&buf);

    أرجع ret;
}

AVFrameSideData *av_frame_side_data_add(AVFrameSideData ***sd, صحيح *nb_sd,
                                        تعداد AVFrameSideDataType type,
                                        AVBufferRef **pbuf, unsigned صحيح flags)
{
    ثابت AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVFrameSideData *sd_dst  = عدم;
    AVBufferRef *buf = *pbuf;

    𐤀𐤌 ((flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF) && !(buf = av_buffer_ref(*pbuf)))
        أرجع عدم;
    𐤀𐤌 (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    𐤀𐤌 ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_data_from_buf(sd_dst, buf, flags);
    } وإلا
        sd_dst = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);

    𐤀𐤌 (sd_dst && !(flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        *pbuf = عدم;
    وإلا 𐤀𐤌 (!sd_dst && (flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        av_buffer_unref(&buf);
    أرجع sd_dst;
}

صحيح av_frame_side_data_clone(AVFrameSideData ***sd, صحيح *nb_sd,
                             ثابت AVFrameSideData *src, unsigned صحيح flags)
{
    ثابت AVSideDataDescriptor *desc;
    AVBufferRef     *buf    = عدم;
    AVFrameSideData *sd_dst = عدم;
    صحيح              ret    = AVERROR_BUG;

    𐤀𐤌 (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        أرجع AVERROR(EINVAL);

    desc = av_frame_side_data_desc(src->type);
    𐤀𐤌 (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, src->type);
    𐤀𐤌 ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = عدم;

        𐤀𐤌 (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
            أرجع AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        𐤀𐤌 (ret < 0)
            أرجع ret;

        ret = av_buffer_replace(&sd_dst->buf, src->buf);
        𐤀𐤌 (ret < 0) {
            av_dict_free(&dict);
            أرجع ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->data     = src->data;
        sd_dst->size     = src->size;
        أرجع 0;
    }

    buf = av_buffer_ref(src->buf);
    𐤀𐤌 (!buf)
        أرجع AVERROR(ENOMEM);

    sd_dst = add_side_data_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->data, src->size);
    𐤀𐤌 (!sd_dst) {
        av_buffer_unref(&buf);
        أرجع AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    𐤀𐤌 (ret < 0) {
        remove_side_data_by_entry(sd, nb_sd, sd_dst);
        أرجع ret;
    }

    أرجع 0;
}

ثابت AVFrameSideData *av_frame_side_data_get_c(ثابت AVFrameSideData * ثابت *sd,
                                                ثابت صحيح nb_sd,
                                                تعداد AVFrameSideDataType type)
{
    لكل (صحيح i = 0; i < nb_sd; i++) {
        𐤀𐤌 (sd[i]->type == type)
            أرجع sd[i];
    }
    أرجع عدم;
}
