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

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "buffer.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "dict.h"
#অন্তর্ভাব "frame.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "side_data.h"

স্থির ধ্রুব AVSideDataDescriptor sd_props[] = {
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

ধ্রুব AVSideDataDescriptor *av_frame_side_data_desc(গণনা AVFrameSideDataType type)
{
    unsigned t = type;
    যদি (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        প্রত্যাগম &sd_props[t];
    প্রত্যাগম রিক্ত;
}

ধ্রুব বর্ণ *av_frame_side_data_name(গণনা AVFrameSideDataType type)
{
    ধ্রুব AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    প্রত্যাগম desc ? desc->name : রিক্ত;
}

স্থির শূন্য free_side_data_entry(AVFrameSideData **ptr_sd)
{
    AVFrameSideData *sd = *ptr_sd;

    av_buffer_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

স্থির শূন্য remove_side_data_by_entry(AVFrameSideData ***sd, পূর্ণাঙ্ক *nb_sd,
                                      ধ্রুব AVFrameSideData *target)
{
    প্রতি (পূর্ণাঙ্ক i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        যদি (entry != target)
            অনুবর্ত;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        প্রত্যাগম;
    }
}

শূন্য av_frame_side_data_remove(AVFrameSideData ***sd, পূর্ণাঙ্ক *nb_sd,
                               গণনা AVFrameSideDataType type)
{
    প্রতি (পূর্ণাঙ্ক i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        যদি (entry->type != type)
            অনুবর্ত;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

শূন্য av_frame_side_data_remove_by_props(AVFrameSideData ***sd, পূর্ণাঙ্ক *nb_sd,
                                        পূর্ণাঙ্ক props)
{
    প্রতি (পূর্ণাঙ্ক i = *nb_sd - 1; i >= 0; i--) {
        AVFrameSideData *entry = ((*sd)[i]);
        ধ্রুব AVSideDataDescriptor *desc = av_frame_side_data_desc(entry->type);
        যদি (!desc || !(desc->props & props))
            অনুবর্ত;

        free_side_data_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

শূন্য av_frame_side_data_free(AVFrameSideData ***sd, পূর্ণাঙ্ক *nb_sd)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < *nb_sd; i++)
        free_side_data_entry(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

স্থির AVFrameSideData *add_side_data_from_buf_ext(AVFrameSideData ***sd,
                                                   পূর্ণাঙ্ক *nb_sd,
                                                   গণনা AVFrameSideDataType type,
                                                   AVBufferRef *buf, uint8_t *data,
                                                   size_t size)
{
    AVFrameSideData *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    যদি ((unsigned)*nb_sd >= FFMIN(INT_MAX, SIZE_MAX))
        প্রত্যাগম রিক্ত;

    tmp = av_realloc_array(*sd, *nb_sd + 1, পরিমাণ(**sd));
    যদি (!tmp)
        প্রত্যাগম রিক্ত;
    *sd = tmp;

    ret = av_mallocz(পরিমাণ(*ret));
    যদি (!ret)
        প্রত্যাগম রিক্ত;

    ret->buf = buf;
    ret->data = data;
    ret->size = size;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    প্রত্যাগম ret;
}

AVFrameSideData *ff_frame_side_data_add_from_buf(AVFrameSideData ***sd,
                                                 পূর্ণাঙ্ক *nb_sd,
                                                 গণনা AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    যদি (!buf)
        প্রত্যাগম রিক্ত;

    প্রত্যাগম add_side_data_from_buf_ext(sd, nb_sd, type, buf, buf->data, buf->size);
}

স্থির AVFrameSideData *replace_side_data_from_buf(AVFrameSideData *dst,
                                                   AVBufferRef *buf, পূর্ণাঙ্ক flags)
{
    যদি (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
        প্রত্যাগম রিক্ত;

    av_dict_free(&dst->metadata);
    av_buffer_unref(&dst->buf);
    dst->buf  = buf;
    dst->data = buf->data;
    dst->size = buf->size;
    প্রত্যাগম dst;
}

AVFrameSideData *av_frame_side_data_new(AVFrameSideData ***sd, পূর্ণাঙ্ক *nb_sd,
                                        গণনা AVFrameSideDataType type,
                                        size_t size, unsigned পূর্ণাঙ্ক flags)
{
    ধ্রুব AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVBufferRef     *buf = av_buffer_alloc(size);
    AVFrameSideData *ret = রিক্ত;

    যদি (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    যদি ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (ret = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        ret = replace_side_data_from_buf(ret, buf, flags);
        যদি (!ret)
            av_buffer_unref(&buf);
        প্রত্যাগম ret;
    }

    ret = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);
    যদি (!ret)
        av_buffer_unref(&buf);

    প্রত্যাগম ret;
}

AVFrameSideData *av_frame_side_data_add(AVFrameSideData ***sd, পূর্ণাঙ্ক *nb_sd,
                                        গণনা AVFrameSideDataType type,
                                        AVBufferRef **pbuf, unsigned পূর্ণাঙ্ক flags)
{
    ধ্রুব AVSideDataDescriptor *desc = av_frame_side_data_desc(type);
    AVFrameSideData *sd_dst  = রিক্ত;
    AVBufferRef *buf = *pbuf;

    যদি ((flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF) && !(buf = av_buffer_ref(*pbuf)))
        প্রত্যাগম রিক্ত;
    যদি (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, type);
    যদি ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_data_from_buf(sd_dst, buf, flags);
    } অন্যথা
        sd_dst = ff_frame_side_data_add_from_buf(sd, nb_sd, type, buf);

    যদি (sd_dst && !(flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        *pbuf = রিক্ত;
    অন্যথা যদি (!sd_dst && (flags & AV_FRAME_SIDE_DATA_FLAG_NEW_REF))
        av_buffer_unref(&buf);
    প্রত্যাগম sd_dst;
}

পূর্ণাঙ্ক av_frame_side_data_clone(AVFrameSideData ***sd, পূর্ণাঙ্ক *nb_sd,
                             ধ্রুব AVFrameSideData *src, unsigned পূর্ণাঙ্ক flags)
{
    ধ্রুব AVSideDataDescriptor *desc;
    AVBufferRef     *buf    = রিক্ত;
    AVFrameSideData *sd_dst = রিক্ত;
    পূর্ণাঙ্ক              ret    = AVERROR_BUG;

    যদি (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        প্রত্যাগম AVERROR(EINVAL);

    desc = av_frame_side_data_desc(src->type);
    যদি (flags & AV_FRAME_SIDE_DATA_FLAG_UNIQUE)
        av_frame_side_data_remove(sd, nb_sd, src->type);
    যদি ((!desc || !(desc->props & AV_SIDE_DATA_PROP_MULTI)) &&
        (sd_dst = (AVFrameSideData *)av_frame_side_data_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = রিক্ত;

        যদি (!(flags & AV_FRAME_SIDE_DATA_FLAG_REPLACE))
            প্রত্যাগম AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        যদি (ret < 0)
            প্রত্যাগম ret;

        ret = av_buffer_replace(&sd_dst->buf, src->buf);
        যদি (ret < 0) {
            av_dict_free(&dict);
            প্রত্যাগম ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->data     = src->data;
        sd_dst->size     = src->size;
        প্রত্যাগম 0;
    }

    buf = av_buffer_ref(src->buf);
    যদি (!buf)
        প্রত্যাগম AVERROR(ENOMEM);

    sd_dst = add_side_data_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->data, src->size);
    যদি (!sd_dst) {
        av_buffer_unref(&buf);
        প্রত্যাগম AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    যদি (ret < 0) {
        remove_side_data_by_entry(sd, nb_sd, sd_dst);
        প্রত্যাগম ret;
    }

    প্রত্যাগম 0;
}

ধ্রুব AVFrameSideData *av_frame_side_data_get_c(ধ্রুব AVFrameSideData * ধ্রুব *sd,
                                                ধ্রুব পূর্ণাঙ্ক nb_sd,
                                                গণনা AVFrameSideDataType type)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < nb_sd; i++) {
        যদি (sd[i]->type == type)
            প্রত্যাগম sd[i];
    }
    প্রত্যাগম রিক্ত;
}
