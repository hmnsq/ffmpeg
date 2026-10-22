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

#شامل "avassert.h"
#شامل "buffer.h"
#شامل "common.h"
#شامل "dict.h"
#شامل "frame.h"
#شامل "mem.h"
#شامل "side_data.h"

ساکن ثابت AVSide_ڈیٹا_Descriptor sd_props[] = {
    [AV_چوکھٹا_ڈیٹا_PANSCAN]                     = { "AVPanScan",                                    AV_SIDE_ڈیٹا_PROP_سائز_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_A53_CC]                      = { "ATSC A53 Part 4 Closed Captions" },
    [AV_چوکھٹا_ڈیٹا_MATRIXENCODING]              = { "AVMatrixEncoding",                             AV_SIDE_ڈیٹا_PROP_CHANNEL_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_DOWNMIX_INFO]                = { "Metadata relevant to a downmix procedure",     AV_SIDE_ڈیٹا_PROP_CHANNEL_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_AFD]                         = { "Active format description" },
    [AV_چوکھٹا_ڈیٹا_MOTION_VECTORS]              = { "Motion vectors",                               AV_SIDE_ڈیٹا_PROP_سائز_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_SKIP_SAMPLES]                = { "Skip samples" },
    [AV_چوکھٹا_ڈیٹا_GOP_TIMECODE]                = { "GOP timecode" },
    [AV_چوکھٹا_ڈیٹا_S12_M_TIMECODE]               = { "SMPTE 12-1 timecode" },
    [AV_چوکھٹا_ڈیٹا_DYNAMIC_HDR_PLUS]            = { "HDR Dynamic Metadata SMPTE2094-40 (HDR10+)",   AV_SIDE_ڈیٹا_PROP_COLOR_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_DYNAMIC_HDR_VIVID]           = { "HDR Dynamic Metadata CUVA 005.1 2021 (Vivid)", AV_SIDE_ڈیٹا_PROP_COLOR_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_DYNAMIC_HDR_SMPTE_2094_APP5] = { "HDR Dynamic Metadata SMPTE2094-50",            AV_SIDE_ڈیٹا_PROP_COLOR_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_REGIONS_کا_INTEREST]         = { "Regions Of Interest",                          AV_SIDE_ڈیٹا_PROP_سائز_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_VIDEO_ENC_PARAMS]            = { "Video encoding parameters" },
    [AV_چوکھٹا_ڈیٹا_FILM_GRAIN_PARAMS]           = { "Film grain parameters" },
    [AV_چوکھٹا_ڈیٹا_DETECTION_BBOXES]            = { "Bounding boxes for object detection and classification", AV_SIDE_ڈیٹا_PROP_سائز_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_DOVI_RPU_بفر]             = { "Dolby Vision RPU Data",                        AV_SIDE_ڈیٹا_PROP_COLOR_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_DOVI_METADATA]               = { "Dolby Vision Metadata",                        AV_SIDE_ڈیٹا_PROP_COLOR_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_LCEVC]                       = { "LCEVC NAL data",                               AV_SIDE_ڈیٹا_PROP_سائز_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_VIEW_ID]                     = { "View ID" },
    [AV_چوکھٹا_ڈیٹا_STEREO3_D]                    = { "Stereo 3D",                                    AV_SIDE_ڈیٹا_PROP_GLOBAL },
    [AV_چوکھٹا_ڈیٹا_REPLAYGAIN]                  = { "AVReplayGain",                                 AV_SIDE_ڈیٹا_PROP_GLOBAL },
    [AV_چوکھٹا_ڈیٹا_DISPLAYMATRIX]               = { "3x3 displaymatrix",                            AV_SIDE_ڈیٹا_PROP_GLOBAL },
    [AV_چوکھٹا_ڈیٹا_AUDIO_SERVICE_TYPE]          = { "Audio service type",                           AV_SIDE_ڈیٹا_PROP_GLOBAL },
    [AV_چوکھٹا_ڈیٹا_MASTERING_DISPLAY_METADATA]  = { "Mastering display metadata",                   AV_SIDE_ڈیٹا_PROP_GLOBAL | AV_SIDE_ڈیٹا_PROP_COLOR_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_CONTENT_LIGHT_LEVEL]         = { "Content light level metadata",                 AV_SIDE_ڈیٹا_PROP_GLOBAL | AV_SIDE_ڈیٹا_PROP_COLOR_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_AMBIENT_VIEWING_ENVIRONMENT] = { "Ambient viewing environment",                  AV_SIDE_ڈیٹا_PROP_GLOBAL },
    [AV_چوکھٹا_ڈیٹا_SPHERICAL]                   = { "Spherical Mapping",                            AV_SIDE_ڈیٹا_PROP_GLOBAL | AV_SIDE_ڈیٹا_PROP_سائز_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_ICC_PROFILE]                 = { "ICC profile",                                  AV_SIDE_ڈیٹا_PROP_GLOBAL | AV_SIDE_ڈیٹا_PROP_COLOR_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_EXIF]                        = { "EXIF metadata",                                AV_SIDE_ڈیٹا_PROP_GLOBAL },
    [AV_چوکھٹا_ڈیٹا_SEI_UNREGISTERED]            = { "H.26[45] User Data Unregistered SEI message",  AV_SIDE_ڈیٹا_PROP_MULTI },
    [AV_چوکھٹا_ڈیٹا_VIDEO_HINT]                  = { "Encoding video hint",                          AV_SIDE_ڈیٹا_PROP_سائز_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_3_D_REFERENCE_DISPLAYS]       = { "3D Reference Displays Information",            AV_SIDE_ڈیٹا_PROP_GLOBAL },
    [AV_چوکھٹا_ڈیٹا_IAMF_MIX_GAIN_PARAM]         = { "IAMF Mix Gain Parameter Data" },
    [AV_چوکھٹا_ڈیٹا_IAMF_DEMIXING_INFO_PARAM]    = { "IAMF Demixing Info Parameter Data",            AV_SIDE_ڈیٹا_PROP_CHANNEL_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_IAMF_RECON_GAIN_INFO_PARAM]  = { "IAMF Recon Gain Info Parameter Data" },
    [AV_چوکھٹا_ڈیٹا_RAW_COLOR_PARAMS]            = { "RAW camera color parameters",                  AV_SIDE_ڈیٹا_PROP_GLOBAL | AV_SIDE_ڈیٹا_PROP_COLOR_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_DOWNMIX_میٹرکس]              = { "Downmix Matrix",                               AV_SIDE_ڈیٹا_PROP_CHANNEL_DEPENDENT },
    [AV_چوکھٹا_ڈیٹا_GAIN_MAP_PARAMS]             = { "Gain map parameters",                          AV_SIDE_ڈیٹا_PROP_GLOBAL | AV_SIDE_ڈیٹا_PROP_COLOR_DEPENDENT },
};

ثابت AVSide_ڈیٹا_Descriptor *av_چوکھٹا_side_ڈیٹا_desc(شمار AVFrame_Side_ڈیٹا_Type type)
{
    غیرعلامتی t = type;
    اگر (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        واپس &sd_props[t];
    واپس تہی;
}

ثابت حرف *av_چوکھٹا_side_ڈیٹا_name(شمار AVFrame_Side_ڈیٹا_Type type)
{
    ثابت AVSide_ڈیٹا_Descriptor *desc = av_چوکھٹا_side_ڈیٹا_desc(type);
    واپس desc ? desc->name : تہی;
}

ساکن خالی free_side_ڈیٹا_اندراج(AVFrame_Side_ڈیٹا **ptr_sd)
{
    AVFrame_Side_ڈیٹا *sd = *ptr_sd;

    av_بفر_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

ساکن خالی remove_side_ڈیٹا_by_اندراج(AVFrame_Side_ڈیٹا ***sd, صحیح *nb_sd,
                                      ثابت AVFrame_Side_ڈیٹا *ہدف)
{
    برائے (صحیح i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_ڈیٹا *اندراج_2 = ((*sd)[i]);
        اگر (اندراج_2 != ہدف)
            جاری;

        free_side_ڈیٹا_اندراج(&اندراج_2);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        واپس;
    }
}

خالی av_چوکھٹا_side_ڈیٹا_remove(AVFrame_Side_ڈیٹا ***sd, صحیح *nb_sd,
                               شمار AVFrame_Side_ڈیٹا_Type type)
{
    برائے (صحیح i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_ڈیٹا *اندراج_2 = ((*sd)[i]);
        اگر (اندراج_2->type != type)
            جاری;

        free_side_ڈیٹا_اندراج(&اندراج_2);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

خالی av_چوکھٹا_side_ڈیٹا_remove_by_props(AVFrame_Side_ڈیٹا ***sd, صحیح *nb_sd,
                                        صحیح props)
{
    برائے (صحیح i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_ڈیٹا *اندراج_2 = ((*sd)[i]);
        ثابت AVSide_ڈیٹا_Descriptor *desc = av_چوکھٹا_side_ڈیٹا_desc(اندراج_2->type);
        اگر (!desc || !(desc->props & props))
            جاری;

        free_side_ڈیٹا_اندراج(&اندراج_2);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

خالی av_چوکھٹا_side_ڈیٹا_free(AVFrame_Side_ڈیٹا ***sd, صحیح *nb_sd)
{
    برائے (صحیح i = 0; i < *nb_sd; i++)
        free_side_ڈیٹا_اندراج(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

ساکن AVFrame_Side_ڈیٹا *جوڑو_side_ڈیٹا_from_buf_ext(AVFrame_Side_ڈیٹا ***sd,
                                                   صحیح *nb_sd,
                                                   شمار AVFrame_Side_ڈیٹا_Type type,
                                                   AVBufferRef *buf, uint8_t *ڈیٹا,
                                                   size_t سائز)
{
    AVFrame_Side_ڈیٹا *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    اگر ((غیرعلامتی)*nb_sd >= FFMIN(زیادہ_سے_زیادہ_عدد, SIZE_MAX))
        واپس تہی;

    tmp = av_realloc_array(*sd, *nb_sd + 1, حجم(**sd));
    اگر (!tmp)
        واپس تہی;
    *sd = tmp;

    ret = av_mallocz(حجم(*ret));
    اگر (!ret)
        واپس تہی;

    ret->buf = buf;
    ret->ڈیٹا = ڈیٹا;
    ret->سائز = سائز;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    واپس ret;
}

AVFrame_Side_ڈیٹا *ff_چوکھٹا_side_ڈیٹا_جوڑو_from_buf(AVFrame_Side_ڈیٹا ***sd,
                                                 صحیح *nb_sd,
                                                 شمار AVFrame_Side_ڈیٹا_Type type,
                                                 AVBufferRef *buf)
{
    اگر (!buf)
        واپس تہی;

    واپس جوڑو_side_ڈیٹا_from_buf_ext(sd, nb_sd, type, buf, buf->ڈیٹا, buf->سائز);
}

ساکن AVFrame_Side_ڈیٹا *replace_side_ڈیٹا_from_buf(AVFrame_Side_ڈیٹا *dst,
                                                   AVBufferRef *buf, صحیح flags)
{
    اگر (!(flags & AV_چوکھٹا_SIDE_ڈیٹا_FLAG_REPLACE))
        واپس تہی;

    av_dict_free(&dst->metadata);
    av_بفر_unref(&dst->buf);
    dst->buf  = buf;
    dst->ڈیٹا = buf->ڈیٹا;
    dst->سائز = buf->سائز;
    واپس dst;
}

AVFrame_Side_ڈیٹا *av_چوکھٹا_side_ڈیٹا_new(AVFrame_Side_ڈیٹا ***sd, صحیح *nb_sd,
                                        شمار AVFrame_Side_ڈیٹا_Type type,
                                        size_t سائز, غیرعلامتی صحیح flags)
{
    ثابت AVSide_ڈیٹا_Descriptor *desc = av_چوکھٹا_side_ڈیٹا_desc(type);
    AVBufferRef     *buf = av_بفر_alloc(سائز);
    AVFrame_Side_ڈیٹا *ret = تہی;

    اگر (flags & AV_چوکھٹا_SIDE_ڈیٹا_FLAG_UNIQUE)
        av_چوکھٹا_side_ڈیٹا_remove(sd, nb_sd, type);
    اگر ((!desc || !(desc->props & AV_SIDE_ڈیٹا_PROP_MULTI)) &&
        (ret = (AVFrame_Side_ڈیٹا *)av_چوکھٹا_side_ڈیٹا_get(*sd, *nb_sd, type))) {
        ret = replace_side_ڈیٹا_from_buf(ret, buf, flags);
        اگر (!ret)
            av_بفر_unref(&buf);
        واپس ret;
    }

    ret = ff_چوکھٹا_side_ڈیٹا_جوڑو_from_buf(sd, nb_sd, type, buf);
    اگر (!ret)
        av_بفر_unref(&buf);

    واپس ret;
}

AVFrame_Side_ڈیٹا *av_چوکھٹا_side_ڈیٹا_جوڑو(AVFrame_Side_ڈیٹا ***sd, صحیح *nb_sd,
                                        شمار AVFrame_Side_ڈیٹا_Type type,
                                        AVBufferRef **pbuf, غیرعلامتی صحیح flags)
{
    ثابت AVSide_ڈیٹا_Descriptor *desc = av_چوکھٹا_side_ڈیٹا_desc(type);
    AVFrame_Side_ڈیٹا *sd_dst  = تہی;
    AVBufferRef *buf = *pbuf;

    اگر ((flags & AV_چوکھٹا_SIDE_ڈیٹا_FLAG_NEW_REF) && !(buf = av_بفر_ref(*pbuf)))
        واپس تہی;
    اگر (flags & AV_چوکھٹا_SIDE_ڈیٹا_FLAG_UNIQUE)
        av_چوکھٹا_side_ڈیٹا_remove(sd, nb_sd, type);
    اگر ((!desc || !(desc->props & AV_SIDE_ڈیٹا_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_ڈیٹا *)av_چوکھٹا_side_ڈیٹا_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_ڈیٹا_from_buf(sd_dst, buf, flags);
    } ورنہ
        sd_dst = ff_چوکھٹا_side_ڈیٹا_جوڑو_from_buf(sd, nb_sd, type, buf);

    اگر (sd_dst && !(flags & AV_چوکھٹا_SIDE_ڈیٹا_FLAG_NEW_REF))
        *pbuf = تہی;
    ورنہ اگر (!sd_dst && (flags & AV_چوکھٹا_SIDE_ڈیٹا_FLAG_NEW_REF))
        av_بفر_unref(&buf);
    واپس sd_dst;
}

صحیح av_چوکھٹا_side_ڈیٹا_clone(AVFrame_Side_ڈیٹا ***sd, صحیح *nb_sd,
                             ثابت AVFrame_Side_ڈیٹا *src, غیرعلامتی صحیح flags)
{
    ثابت AVSide_ڈیٹا_Descriptor *desc;
    AVBufferRef     *buf    = تہی;
    AVFrame_Side_ڈیٹا *sd_dst = تہی;
    صحیح              ret    = AVERROR_BUG;

    اگر (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        واپس AVERROR(EINVAL);

    desc = av_چوکھٹا_side_ڈیٹا_desc(src->type);
    اگر (flags & AV_چوکھٹا_SIDE_ڈیٹا_FLAG_UNIQUE)
        av_چوکھٹا_side_ڈیٹا_remove(sd, nb_sd, src->type);
    اگر ((!desc || !(desc->props & AV_SIDE_ڈیٹا_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_ڈیٹا *)av_چوکھٹا_side_ڈیٹا_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = تہی;

        اگر (!(flags & AV_چوکھٹا_SIDE_ڈیٹا_FLAG_REPLACE))
            واپس AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        اگر (ret < 0)
            واپس ret;

        ret = av_بفر_replace(&sd_dst->buf, src->buf);
        اگر (ret < 0) {
            av_dict_free(&dict);
            واپس ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->ڈیٹا     = src->ڈیٹا;
        sd_dst->سائز     = src->سائز;
        واپس 0;
    }

    buf = av_بفر_ref(src->buf);
    اگر (!buf)
        واپس AVERROR(ENOMEM);

    sd_dst = جوڑو_side_ڈیٹا_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->ڈیٹا, src->سائز);
    اگر (!sd_dst) {
        av_بفر_unref(&buf);
        واپس AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    اگر (ret < 0) {
        remove_side_ڈیٹا_by_اندراج(sd, nb_sd, sd_dst);
        واپس ret;
    }

    واپس 0;
}

ثابت AVFrame_Side_ڈیٹا *av_چوکھٹا_side_ڈیٹا_get_c(ثابت AVFrame_Side_ڈیٹا * ثابت *sd,
                                                ثابت صحیح nb_sd,
                                                شمار AVFrame_Side_ڈیٹا_Type type)
{
    برائے (صحیح i = 0; i < nb_sd; i++) {
        اگر (sd[i]->type == type)
            واپس sd[i];
    }
    واپس تہی;
}
