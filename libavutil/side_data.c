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

ساكن ثابت AVSide_معلومات_Descriptor sd_props[] = {
    [AV_چوکٺو_معلومات_PANSCAN]                     = { "AVPanScan",                                    AV_SIDE_معلومات_PROP_سائيز_DEPENDENT },
    [AV_چوکٺو_معلومات_A53_CC]                      = { "ATSC A53 Part 4 Closed Captions" },
    [AV_چوکٺو_معلومات_MATRIXENCODING]              = { "AVMatrixEncoding",                             AV_SIDE_معلومات_PROP_CHANNEL_DEPENDENT },
    [AV_چوکٺو_معلومات_DOWNMIX_INFO]                = { "Metadata relevant to a downmix procedure",     AV_SIDE_معلومات_PROP_CHANNEL_DEPENDENT },
    [AV_چوکٺو_معلومات_AFD]                         = { "Active format description" },
    [AV_چوکٺو_معلومات_MOTION_VECTORS]              = { "Motion vectors",                               AV_SIDE_معلومات_PROP_سائيز_DEPENDENT },
    [AV_چوکٺو_معلومات_SKIP_SAMPLES]                = { "Skip samples" },
    [AV_چوکٺو_معلومات_GOP_TIMECODE]                = { "GOP timecode" },
    [AV_چوکٺو_معلومات_S12_M_TIMECODE]               = { "SMPTE 12-1 timecode" },
    [AV_چوکٺو_معلومات_DYNAMIC_HDR_PLUS]            = { "HDR Dynamic Metadata SMPTE2094-40 (HDR10+)",   AV_SIDE_معلومات_PROP_COLOR_DEPENDENT },
    [AV_چوکٺو_معلومات_DYNAMIC_HDR_VIVID]           = { "HDR Dynamic Metadata CUVA 005.1 2021 (Vivid)", AV_SIDE_معلومات_PROP_COLOR_DEPENDENT },
    [AV_چوکٺو_معلومات_DYNAMIC_HDR_SMPTE_2094_APP5] = { "HDR Dynamic Metadata SMPTE2094-50",            AV_SIDE_معلومات_PROP_COLOR_DEPENDENT },
    [AV_چوکٺو_معلومات_REGIONS_جو_INTEREST]         = { "Regions Of Interest",                          AV_SIDE_معلومات_PROP_سائيز_DEPENDENT },
    [AV_چوکٺو_معلومات_VIDEO_ENC_PARAMS]            = { "Video encoding parameters" },
    [AV_چوکٺو_معلومات_FILM_GRAIN_PARAMS]           = { "Film grain parameters" },
    [AV_چوکٺو_معلومات_DETECTION_BBOXES]            = { "Bounding boxes for object detection and classification", AV_SIDE_معلومات_PROP_سائيز_DEPENDENT },
    [AV_چوکٺو_معلومات_DOVI_RPU_بفر]             = { "Dolby Vision RPU Data",                        AV_SIDE_معلومات_PROP_COLOR_DEPENDENT },
    [AV_چوکٺو_معلومات_DOVI_METADATA]               = { "Dolby Vision Metadata",                        AV_SIDE_معلومات_PROP_COLOR_DEPENDENT },
    [AV_چوکٺو_معلومات_LCEVC]                       = { "LCEVC NAL data",                               AV_SIDE_معلومات_PROP_سائيز_DEPENDENT },
    [AV_چوکٺو_معلومات_VIEW_ID]                     = { "View ID" },
    [AV_چوکٺو_معلومات_STEREO3_D]                    = { "Stereo 3D",                                    AV_SIDE_معلومات_PROP_GLOBAL },
    [AV_چوکٺو_معلومات_REPLAYGAIN]                  = { "AVReplayGain",                                 AV_SIDE_معلومات_PROP_GLOBAL },
    [AV_چوکٺو_معلومات_DISPLAYMATRIX]               = { "3x3 displaymatrix",                            AV_SIDE_معلومات_PROP_GLOBAL },
    [AV_چوکٺو_معلومات_AUDIO_SERVICE_TYPE]          = { "Audio service type",                           AV_SIDE_معلومات_PROP_GLOBAL },
    [AV_چوکٺو_معلومات_MASTERING_DISPLAY_METADATA]  = { "Mastering display metadata",                   AV_SIDE_معلومات_PROP_GLOBAL | AV_SIDE_معلومات_PROP_COLOR_DEPENDENT },
    [AV_چوکٺو_معلومات_CONTENT_LIGHT_LEVEL]         = { "Content light level metadata",                 AV_SIDE_معلومات_PROP_GLOBAL | AV_SIDE_معلومات_PROP_COLOR_DEPENDENT },
    [AV_چوکٺو_معلومات_AMBIENT_VIEWING_ENVIRONMENT] = { "Ambient viewing environment",                  AV_SIDE_معلومات_PROP_GLOBAL },
    [AV_چوکٺو_معلومات_SPHERICAL]                   = { "Spherical Mapping",                            AV_SIDE_معلومات_PROP_GLOBAL | AV_SIDE_معلومات_PROP_سائيز_DEPENDENT },
    [AV_چوکٺو_معلومات_ICC_PROFILE]                 = { "ICC profile",                                  AV_SIDE_معلومات_PROP_GLOBAL | AV_SIDE_معلومات_PROP_COLOR_DEPENDENT },
    [AV_چوکٺو_معلومات_EXIF]                        = { "EXIF metadata",                                AV_SIDE_معلومات_PROP_GLOBAL },
    [AV_چوکٺو_معلومات_SEI_UNREGISTERED]            = { "H.26[45] User Data Unregistered SEI message",  AV_SIDE_معلومات_PROP_MULTI },
    [AV_چوکٺو_معلومات_VIDEO_HINT]                  = { "Encoding video hint",                          AV_SIDE_معلومات_PROP_سائيز_DEPENDENT },
    [AV_چوکٺو_معلومات_3_D_REFERENCE_DISPLAYS]       = { "3D Reference Displays Information",            AV_SIDE_معلومات_PROP_GLOBAL },
    [AV_چوکٺو_معلومات_IAMF_MIX_GAIN_PARAM]         = { "IAMF Mix Gain Parameter Data" },
    [AV_چوکٺو_معلومات_IAMF_DEMIXING_INFO_PARAM]    = { "IAMF Demixing Info Parameter Data",            AV_SIDE_معلومات_PROP_CHANNEL_DEPENDENT },
    [AV_چوکٺو_معلومات_IAMF_RECON_GAIN_INFO_PARAM]  = { "IAMF Recon Gain Info Parameter Data" },
    [AV_چوکٺو_معلومات_RAW_COLOR_PARAMS]            = { "RAW camera color parameters",                  AV_SIDE_معلومات_PROP_GLOBAL | AV_SIDE_معلومات_PROP_COLOR_DEPENDENT },
    [AV_چوکٺو_معلومات_DOWNMIX_ميٽرڪس]              = { "Downmix Matrix",                               AV_SIDE_معلومات_PROP_CHANNEL_DEPENDENT },
    [AV_چوکٺو_معلومات_GAIN_MAP_PARAMS]             = { "Gain map parameters",                          AV_SIDE_معلومات_PROP_GLOBAL | AV_SIDE_معلومات_PROP_COLOR_DEPENDENT },
};

ثابت AVSide_معلومات_Descriptor *av_چوکٺو_side_معلومات_desc(تعداد AVFrame_Side_معلومات_Type type)
{
    بنانشان t = type;
    إذا (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        أرجع &sd_props[t];
    أرجع عدم;
}

ثابت حرف *av_چوکٺو_side_معلومات_name(تعداد AVFrame_Side_معلومات_Type type)
{
    ثابت AVSide_معلومات_Descriptor *desc = av_چوکٺو_side_معلومات_desc(type);
    أرجع desc ? desc->name : عدم;
}

ساكن فراغ free_side_معلومات_داخلا(AVFrame_Side_معلومات **ptr_sd)
{
    AVFrame_Side_معلومات *sd = *ptr_sd;

    av_بفر_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

ساكن فراغ remove_side_معلومات_by_داخلا(AVFrame_Side_معلومات ***sd, صحيح *nb_sd,
                                      ثابت AVFrame_Side_معلومات *هدف)
{
    لكل (صحيح i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_معلومات *داخلا = ((*sd)[i]);
        إذا (داخلا != هدف)
            استمر;

        free_side_معلومات_داخلا(&داخلا);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        أرجع;
    }
}

فراغ av_چوکٺو_side_معلومات_remove(AVFrame_Side_معلومات ***sd, صحيح *nb_sd,
                               تعداد AVFrame_Side_معلومات_Type type)
{
    لكل (صحيح i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_معلومات *داخلا = ((*sd)[i]);
        إذا (داخلا->type != type)
            استمر;

        free_side_معلومات_داخلا(&داخلا);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

فراغ av_چوکٺو_side_معلومات_remove_by_props(AVFrame_Side_معلومات ***sd, صحيح *nb_sd,
                                        صحيح props)
{
    لكل (صحيح i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_معلومات *داخلا = ((*sd)[i]);
        ثابت AVSide_معلومات_Descriptor *desc = av_چوکٺو_side_معلومات_desc(داخلا->type);
        إذا (!desc || !(desc->props & props))
            استمر;

        free_side_معلومات_داخلا(&داخلا);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

فراغ av_چوکٺو_side_معلومات_free(AVFrame_Side_معلومات ***sd, صحيح *nb_sd)
{
    لكل (صحيح i = 0; i < *nb_sd; i++)
        free_side_معلومات_داخلا(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

ساكن AVFrame_Side_معلومات *جوڙيو_side_معلومات_from_buf_ext(AVFrame_Side_معلومات ***sd,
                                                   صحيح *nb_sd,
                                                   تعداد AVFrame_Side_معلومات_Type type,
                                                   AVBufferRef *buf, uint8_t *معلومات,
                                                   size_t سائيز)
{
    AVFrame_Side_معلومات *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    إذا ((بنانشان)*nb_sd >= FFMIN(وڌ_کان_وڌ_عدد, SIZE_MAX))
        أرجع عدم;

    tmp = av_realloc_array(*sd, *nb_sd + 1, حجم(**sd));
    إذا (!tmp)
        أرجع عدم;
    *sd = tmp;

    ret = av_mallocz(حجم(*ret));
    إذا (!ret)
        أرجع عدم;

    ret->buf = buf;
    ret->معلومات = معلومات;
    ret->سائيز = سائيز;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    أرجع ret;
}

AVFrame_Side_معلومات *ff_چوکٺو_side_معلومات_جوڙيو_from_buf(AVFrame_Side_معلومات ***sd,
                                                 صحيح *nb_sd,
                                                 تعداد AVFrame_Side_معلومات_Type type,
                                                 AVBufferRef *buf)
{
    إذا (!buf)
        أرجع عدم;

    أرجع جوڙيو_side_معلومات_from_buf_ext(sd, nb_sd, type, buf, buf->معلومات, buf->سائيز);
}

ساكن AVFrame_Side_معلومات *replace_side_معلومات_from_buf(AVFrame_Side_معلومات *dst,
                                                   AVBufferRef *buf, صحيح flags)
{
    إذا (!(flags & AV_چوکٺو_SIDE_معلومات_FLAG_REPLACE))
        أرجع عدم;

    av_dict_free(&dst->metadata);
    av_بفر_unref(&dst->buf);
    dst->buf  = buf;
    dst->معلومات = buf->معلومات;
    dst->سائيز = buf->سائيز;
    أرجع dst;
}

AVFrame_Side_معلومات *av_چوکٺو_side_معلومات_new(AVFrame_Side_معلومات ***sd, صحيح *nb_sd,
                                        تعداد AVFrame_Side_معلومات_Type type,
                                        size_t سائيز, بنانشان صحيح flags)
{
    ثابت AVSide_معلومات_Descriptor *desc = av_چوکٺو_side_معلومات_desc(type);
    AVBufferRef     *buf = av_بفر_alloc(سائيز);
    AVFrame_Side_معلومات *ret = عدم;

    إذا (flags & AV_چوکٺو_SIDE_معلومات_FLAG_UNIQUE)
        av_چوکٺو_side_معلومات_remove(sd, nb_sd, type);
    إذا ((!desc || !(desc->props & AV_SIDE_معلومات_PROP_MULTI)) &&
        (ret = (AVFrame_Side_معلومات *)av_چوکٺو_side_معلومات_get(*sd, *nb_sd, type))) {
        ret = replace_side_معلومات_from_buf(ret, buf, flags);
        إذا (!ret)
            av_بفر_unref(&buf);
        أرجع ret;
    }

    ret = ff_چوکٺو_side_معلومات_جوڙيو_from_buf(sd, nb_sd, type, buf);
    إذا (!ret)
        av_بفر_unref(&buf);

    أرجع ret;
}

AVFrame_Side_معلومات *av_چوکٺو_side_معلومات_جوڙيو(AVFrame_Side_معلومات ***sd, صحيح *nb_sd,
                                        تعداد AVFrame_Side_معلومات_Type type,
                                        AVBufferRef **pbuf, بنانشان صحيح flags)
{
    ثابت AVSide_معلومات_Descriptor *desc = av_چوکٺو_side_معلومات_desc(type);
    AVFrame_Side_معلومات *sd_dst  = عدم;
    AVBufferRef *buf = *pbuf;

    إذا ((flags & AV_چوکٺو_SIDE_معلومات_FLAG_NEW_REF) && !(buf = av_بفر_ref(*pbuf)))
        أرجع عدم;
    إذا (flags & AV_چوکٺو_SIDE_معلومات_FLAG_UNIQUE)
        av_چوکٺو_side_معلومات_remove(sd, nb_sd, type);
    إذا ((!desc || !(desc->props & AV_SIDE_معلومات_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_معلومات *)av_چوکٺو_side_معلومات_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_معلومات_from_buf(sd_dst, buf, flags);
    } وإلا
        sd_dst = ff_چوکٺو_side_معلومات_جوڙيو_from_buf(sd, nb_sd, type, buf);

    إذا (sd_dst && !(flags & AV_چوکٺو_SIDE_معلومات_FLAG_NEW_REF))
        *pbuf = عدم;
    وإلا إذا (!sd_dst && (flags & AV_چوکٺو_SIDE_معلومات_FLAG_NEW_REF))
        av_بفر_unref(&buf);
    أرجع sd_dst;
}

صحيح av_چوکٺو_side_معلومات_clone(AVFrame_Side_معلومات ***sd, صحيح *nb_sd,
                             ثابت AVFrame_Side_معلومات *src, بنانشان صحيح flags)
{
    ثابت AVSide_معلومات_Descriptor *desc;
    AVBufferRef     *buf    = عدم;
    AVFrame_Side_معلومات *sd_dst = عدم;
    صحيح              ret    = AVERROR_BUG;

    إذا (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        أرجع AVERROR(EINVAL);

    desc = av_چوکٺو_side_معلومات_desc(src->type);
    إذا (flags & AV_چوکٺو_SIDE_معلومات_FLAG_UNIQUE)
        av_چوکٺو_side_معلومات_remove(sd, nb_sd, src->type);
    إذا ((!desc || !(desc->props & AV_SIDE_معلومات_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_معلومات *)av_چوکٺو_side_معلومات_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = عدم;

        إذا (!(flags & AV_چوکٺو_SIDE_معلومات_FLAG_REPLACE))
            أرجع AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        إذا (ret < 0)
            أرجع ret;

        ret = av_بفر_replace(&sd_dst->buf, src->buf);
        إذا (ret < 0) {
            av_dict_free(&dict);
            أرجع ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->معلومات     = src->معلومات;
        sd_dst->سائيز     = src->سائيز;
        أرجع 0;
    }

    buf = av_بفر_ref(src->buf);
    إذا (!buf)
        أرجع AVERROR(ENOMEM);

    sd_dst = جوڙيو_side_معلومات_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->معلومات, src->سائيز);
    إذا (!sd_dst) {
        av_بفر_unref(&buf);
        أرجع AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    إذا (ret < 0) {
        remove_side_معلومات_by_داخلا(sd, nb_sd, sd_dst);
        أرجع ret;
    }

    أرجع 0;
}

ثابت AVFrame_Side_معلومات *av_چوکٺو_side_معلومات_get_c(ثابت AVFrame_Side_معلومات * ثابت *sd,
                                                ثابت صحيح nb_sd,
                                                تعداد AVFrame_Side_معلومات_Type type)
{
    لكل (صحيح i = 0; i < nb_sd; i++) {
        إذا (sd[i]->type == type)
            أرجع sd[i];
    }
    أرجع عدم;
}
