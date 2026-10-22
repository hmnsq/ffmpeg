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

স্থির ধ্রুবক AVSide_তথ্য_Descriptor sd_props[] = {
    [AV_FRAME_তথ্য_PANSCAN]                     = { "AVPanScan",                                    AV_SIDE_তথ্য_PROP_আকার_DEPENDENT },
    [AV_FRAME_তথ্য_A53_CC]                      = { "ATSC A53 Part 4 Closed Captions" },
    [AV_FRAME_তথ্য_MATRIXENCODING]              = { "AVMatrixEncoding",                             AV_SIDE_তথ্য_PROP_CHANNEL_DEPENDENT },
    [AV_FRAME_তথ্য_DOWNMIX_INFO]                = { "Metadata relevant to a downmix procedure",     AV_SIDE_তথ্য_PROP_CHANNEL_DEPENDENT },
    [AV_FRAME_তথ্য_AFD]                         = { "Active format description" },
    [AV_FRAME_তথ্য_MOTION_VECTORS]              = { "Motion vectors",                               AV_SIDE_তথ্য_PROP_আকার_DEPENDENT },
    [AV_FRAME_তথ্য_SKIP_SAMPLES]                = { "Skip samples" },
    [AV_FRAME_তথ্য_GOP_TIMECODE]                = { "GOP timecode" },
    [AV_FRAME_তথ্য_S12_M_TIMECODE]               = { "SMPTE 12-1 timecode" },
    [AV_FRAME_তথ্য_DYNAMIC_HDR_PLUS]            = { "HDR Dynamic Metadata SMPTE2094-40 (HDR10+)",   AV_SIDE_তথ্য_PROP_COLOR_DEPENDENT },
    [AV_FRAME_তথ্য_DYNAMIC_HDR_VIVID]           = { "HDR Dynamic Metadata CUVA 005.1 2021 (Vivid)", AV_SIDE_তথ্য_PROP_COLOR_DEPENDENT },
    [AV_FRAME_তথ্য_DYNAMIC_HDR_SMPTE_2094_APP5] = { "HDR Dynamic Metadata SMPTE2094-50",            AV_SIDE_তথ্য_PROP_COLOR_DEPENDENT },
    [AV_FRAME_তথ্য_REGIONS_OF_INTEREST]         = { "Regions Of Interest",                          AV_SIDE_তথ্য_PROP_আকার_DEPENDENT },
    [AV_FRAME_তথ্য_VIDEO_ENC_PARAMS]            = { "Video encoding parameters" },
    [AV_FRAME_তথ্য_FILM_GRAIN_PARAMS]           = { "Film grain parameters" },
    [AV_FRAME_তথ্য_DETECTION_BBOXES]            = { "Bounding boxes for object detection and classification", AV_SIDE_তথ্য_PROP_আকার_DEPENDENT },
    [AV_FRAME_তথ্য_DOVI_RPU_বাফার]             = { "Dolby Vision RPU Data",                        AV_SIDE_তথ্য_PROP_COLOR_DEPENDENT },
    [AV_FRAME_তথ্য_DOVI_METADATA]               = { "Dolby Vision Metadata",                        AV_SIDE_তথ্য_PROP_COLOR_DEPENDENT },
    [AV_FRAME_তথ্য_LCEVC]                       = { "LCEVC NAL data",                               AV_SIDE_তথ্য_PROP_আকার_DEPENDENT },
    [AV_FRAME_তথ্য_VIEW_ID]                     = { "View ID" },
    [AV_FRAME_তথ্য_STEREO3_D]                    = { "Stereo 3D",                                    AV_SIDE_তথ্য_PROP_GLOBAL },
    [AV_FRAME_তথ্য_REPLAYGAIN]                  = { "AVReplayGain",                                 AV_SIDE_তথ্য_PROP_GLOBAL },
    [AV_FRAME_তথ্য_DISPLAYMATRIX]               = { "3x3 displaymatrix",                            AV_SIDE_তথ্য_PROP_GLOBAL },
    [AV_FRAME_তথ্য_AUDIO_SERVICE_TYPE]          = { "Audio service type",                           AV_SIDE_তথ্য_PROP_GLOBAL },
    [AV_FRAME_তথ্য_MASTERING_DISPLAY_METADATA]  = { "Mastering display metadata",                   AV_SIDE_তথ্য_PROP_GLOBAL | AV_SIDE_তথ্য_PROP_COLOR_DEPENDENT },
    [AV_FRAME_তথ্য_CONTENT_LIGHT_LEVEL]         = { "Content light level metadata",                 AV_SIDE_তথ্য_PROP_GLOBAL | AV_SIDE_তথ্য_PROP_COLOR_DEPENDENT },
    [AV_FRAME_তথ্য_AMBIENT_VIEWING_ENVIRONMENT] = { "Ambient viewing environment",                  AV_SIDE_তথ্য_PROP_GLOBAL },
    [AV_FRAME_তথ্য_SPHERICAL]                   = { "Spherical Mapping",                            AV_SIDE_তথ্য_PROP_GLOBAL | AV_SIDE_তথ্য_PROP_আকার_DEPENDENT },
    [AV_FRAME_তথ্য_ICC_PROFILE]                 = { "ICC profile",                                  AV_SIDE_তথ্য_PROP_GLOBAL | AV_SIDE_তথ্য_PROP_COLOR_DEPENDENT },
    [AV_FRAME_তথ্য_EXIF]                        = { "EXIF metadata",                                AV_SIDE_তথ্য_PROP_GLOBAL },
    [AV_FRAME_তথ্য_SEI_UNREGISTERED]            = { "H.26[45] User Data Unregistered SEI message",  AV_SIDE_তথ্য_PROP_MULTI },
    [AV_FRAME_তথ্য_VIDEO_HINT]                  = { "Encoding video hint",                          AV_SIDE_তথ্য_PROP_আকার_DEPENDENT },
    [AV_FRAME_তথ্য_3_D_REFERENCE_DISPLAYS]       = { "3D Reference Displays Information",            AV_SIDE_তথ্য_PROP_GLOBAL },
    [AV_FRAME_তথ্য_IAMF_MIX_GAIN_PARAM]         = { "IAMF Mix Gain Parameter Data" },
    [AV_FRAME_তথ্য_IAMF_DEMIXING_INFO_PARAM]    = { "IAMF Demixing Info Parameter Data",            AV_SIDE_তথ্য_PROP_CHANNEL_DEPENDENT },
    [AV_FRAME_তথ্য_IAMF_RECON_GAIN_INFO_PARAM]  = { "IAMF Recon Gain Info Parameter Data" },
    [AV_FRAME_তথ্য_RAW_COLOR_PARAMS]            = { "RAW camera color parameters",                  AV_SIDE_তথ্য_PROP_GLOBAL | AV_SIDE_তথ্য_PROP_COLOR_DEPENDENT },
    [AV_FRAME_তথ্য_DOWNMIX_MATRIX]              = { "Downmix Matrix",                               AV_SIDE_তথ্য_PROP_CHANNEL_DEPENDENT },
    [AV_FRAME_তথ্য_GAIN_MAP_PARAMS]             = { "Gain map parameters",                          AV_SIDE_তথ্য_PROP_GLOBAL | AV_SIDE_তথ্য_PROP_COLOR_DEPENDENT },
};

ধ্রুবক AVSide_তথ্য_Descriptor *av_frame_side_তথ্য_desc(গণনা AVFrame_Side_তথ্য_Type type)
{
    unsigned t = type;
    যদি (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        ফেরত &sd_props[t];
    ফেরত ফাঁকা;
}

ধ্রুবক অক্ষর *av_frame_side_তথ্য_name(গণনা AVFrame_Side_তথ্য_Type type)
{
    ধ্রুবক AVSide_তথ্য_Descriptor *desc = av_frame_side_তথ্য_desc(type);
    ফেরত desc ? desc->name : ফাঁকা;
}

স্থির শূন্য free_side_তথ্য_entry(AVFrame_Side_তথ্য **ptr_sd)
{
    AVFrame_Side_তথ্য *sd = *ptr_sd;

    av_বাফার_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

স্থির শূন্য remove_side_তথ্য_by_entry(AVFrame_Side_তথ্য ***sd, পূর্ণসংখ্যা *nb_sd,
                                      ধ্রুবক AVFrame_Side_তথ্য *target)
{
    জন্য (পূর্ণসংখ্যা i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_তথ্য *entry = ((*sd)[i]);
        যদি (entry != target)
            চালু;

        free_side_তথ্য_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        ফেরত;
    }
}

শূন্য av_frame_side_তথ্য_remove(AVFrame_Side_তথ্য ***sd, পূর্ণসংখ্যা *nb_sd,
                               গণনা AVFrame_Side_তথ্য_Type type)
{
    জন্য (পূর্ণসংখ্যা i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_তথ্য *entry = ((*sd)[i]);
        যদি (entry->type != type)
            চালু;

        free_side_তথ্য_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

শূন্য av_frame_side_তথ্য_remove_by_props(AVFrame_Side_তথ্য ***sd, পূর্ণসংখ্যা *nb_sd,
                                        পূর্ণসংখ্যা props)
{
    জন্য (পূর্ণসংখ্যা i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_তথ্য *entry = ((*sd)[i]);
        ধ্রুবক AVSide_তথ্য_Descriptor *desc = av_frame_side_তথ্য_desc(entry->type);
        যদি (!desc || !(desc->props & props))
            চালু;

        free_side_তথ্য_entry(&entry);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

শূন্য av_frame_side_তথ্য_free(AVFrame_Side_তথ্য ***sd, পূর্ণসংখ্যা *nb_sd)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < *nb_sd; i++)
        free_side_তথ্য_entry(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

স্থির AVFrame_Side_তথ্য *add_side_তথ্য_from_buf_ext(AVFrame_Side_তথ্য ***sd,
                                                   পূর্ণসংখ্যা *nb_sd,
                                                   গণনা AVFrame_Side_তথ্য_Type type,
                                                   AVBufferRef *buf, uint8_t *তথ্য,
                                                   size_t আকার_2)
{
    AVFrame_Side_তথ্য *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    যদি ((unsigned)*nb_sd >= FFMIN(INT_MAX, SIZE_MAX))
        ফেরত ফাঁকা;

    tmp = av_realloc_array(*sd, *nb_sd + 1, আকার(**sd));
    যদি (!tmp)
        ফেরত ফাঁকা;
    *sd = tmp;

    ret = av_mallocz(আকার(*ret));
    যদি (!ret)
        ফেরত ফাঁকা;

    ret->buf = buf;
    ret->তথ্য = তথ্য;
    ret->আকার_2 = আকার_2;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    ফেরত ret;
}

AVFrame_Side_তথ্য *ff_frame_side_তথ্য_add_from_buf(AVFrame_Side_তথ্য ***sd,
                                                 পূর্ণসংখ্যা *nb_sd,
                                                 গণনা AVFrame_Side_তথ্য_Type type,
                                                 AVBufferRef *buf)
{
    যদি (!buf)
        ফেরত ফাঁকা;

    ফেরত add_side_তথ্য_from_buf_ext(sd, nb_sd, type, buf, buf->তথ্য, buf->আকার_2);
}

স্থির AVFrame_Side_তথ্য *replace_side_তথ্য_from_buf(AVFrame_Side_তথ্য *dst,
                                                   AVBufferRef *buf, পূর্ণসংখ্যা flags)
{
    যদি (!(flags & AV_FRAME_SIDE_তথ্য_FLAG_REPLACE))
        ফেরত ফাঁকা;

    av_dict_free(&dst->metadata);
    av_বাফার_unref(&dst->buf);
    dst->buf  = buf;
    dst->তথ্য = buf->তথ্য;
    dst->আকার_2 = buf->আকার_2;
    ফেরত dst;
}

AVFrame_Side_তথ্য *av_frame_side_তথ্য_new(AVFrame_Side_তথ্য ***sd, পূর্ণসংখ্যা *nb_sd,
                                        গণনা AVFrame_Side_তথ্য_Type type,
                                        size_t আকার_2, unsigned পূর্ণসংখ্যা flags)
{
    ধ্রুবক AVSide_তথ্য_Descriptor *desc = av_frame_side_তথ্য_desc(type);
    AVBufferRef     *buf = av_বাফার_alloc(আকার_2);
    AVFrame_Side_তথ্য *ret = ফাঁকা;

    যদি (flags & AV_FRAME_SIDE_তথ্য_FLAG_UNIQUE)
        av_frame_side_তথ্য_remove(sd, nb_sd, type);
    যদি ((!desc || !(desc->props & AV_SIDE_তথ্য_PROP_MULTI)) &&
        (ret = (AVFrame_Side_তথ্য *)av_frame_side_তথ্য_get(*sd, *nb_sd, type))) {
        ret = replace_side_তথ্য_from_buf(ret, buf, flags);
        যদি (!ret)
            av_বাফার_unref(&buf);
        ফেরত ret;
    }

    ret = ff_frame_side_তথ্য_add_from_buf(sd, nb_sd, type, buf);
    যদি (!ret)
        av_বাফার_unref(&buf);

    ফেরত ret;
}

AVFrame_Side_তথ্য *av_frame_side_তথ্য_add(AVFrame_Side_তথ্য ***sd, পূর্ণসংখ্যা *nb_sd,
                                        গণনা AVFrame_Side_তথ্য_Type type,
                                        AVBufferRef **pbuf, unsigned পূর্ণসংখ্যা flags)
{
    ধ্রুবক AVSide_তথ্য_Descriptor *desc = av_frame_side_তথ্য_desc(type);
    AVFrame_Side_তথ্য *sd_dst  = ফাঁকা;
    AVBufferRef *buf = *pbuf;

    যদি ((flags & AV_FRAME_SIDE_তথ্য_FLAG_NEW_REF) && !(buf = av_বাফার_ref(*pbuf)))
        ফেরত ফাঁকা;
    যদি (flags & AV_FRAME_SIDE_তথ্য_FLAG_UNIQUE)
        av_frame_side_তথ্য_remove(sd, nb_sd, type);
    যদি ((!desc || !(desc->props & AV_SIDE_তথ্য_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_তথ্য *)av_frame_side_তথ্য_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_তথ্য_from_buf(sd_dst, buf, flags);
    } অন্যথা
        sd_dst = ff_frame_side_তথ্য_add_from_buf(sd, nb_sd, type, buf);

    যদি (sd_dst && !(flags & AV_FRAME_SIDE_তথ্য_FLAG_NEW_REF))
        *pbuf = ফাঁকা;
    অন্যথা যদি (!sd_dst && (flags & AV_FRAME_SIDE_তথ্য_FLAG_NEW_REF))
        av_বাফার_unref(&buf);
    ফেরত sd_dst;
}

পূর্ণসংখ্যা av_frame_side_তথ্য_clone(AVFrame_Side_তথ্য ***sd, পূর্ণসংখ্যা *nb_sd,
                             ধ্রুবক AVFrame_Side_তথ্য *src, unsigned পূর্ণসংখ্যা flags)
{
    ধ্রুবক AVSide_তথ্য_Descriptor *desc;
    AVBufferRef     *buf    = ফাঁকা;
    AVFrame_Side_তথ্য *sd_dst = ফাঁকা;
    পূর্ণসংখ্যা              ret    = AVERROR_BUG;

    যদি (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        ফেরত AVERROR(EINVAL);

    desc = av_frame_side_তথ্য_desc(src->type);
    যদি (flags & AV_FRAME_SIDE_তথ্য_FLAG_UNIQUE)
        av_frame_side_তথ্য_remove(sd, nb_sd, src->type);
    যদি ((!desc || !(desc->props & AV_SIDE_তথ্য_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_তথ্য *)av_frame_side_তথ্য_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = ফাঁকা;

        যদি (!(flags & AV_FRAME_SIDE_তথ্য_FLAG_REPLACE))
            ফেরত AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        যদি (ret < 0)
            ফেরত ret;

        ret = av_বাফার_replace(&sd_dst->buf, src->buf);
        যদি (ret < 0) {
            av_dict_free(&dict);
            ফেরত ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->তথ্য     = src->তথ্য;
        sd_dst->আকার_2     = src->আকার_2;
        ফেরত 0;
    }

    buf = av_বাফার_ref(src->buf);
    যদি (!buf)
        ফেরত AVERROR(ENOMEM);

    sd_dst = add_side_তথ্য_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->তথ্য, src->আকার_2);
    যদি (!sd_dst) {
        av_বাফার_unref(&buf);
        ফেরত AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    যদি (ret < 0) {
        remove_side_তথ্য_by_entry(sd, nb_sd, sd_dst);
        ফেরত ret;
    }

    ফেরত 0;
}

ধ্রুবক AVFrame_Side_তথ্য *av_frame_side_তথ্য_get_c(ধ্রুবক AVFrame_Side_তথ্য * ধ্রুবক *sd,
                                                ধ্রুবক পূর্ণসংখ্যা nb_sd,
                                                গণনা AVFrame_Side_তথ্য_Type type)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < nb_sd; i++) {
        যদি (sd[i]->type == type)
            ফেরত sd[i];
    }
    ফেরত ফাঁকা;
}
