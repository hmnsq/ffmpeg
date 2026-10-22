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

ساكن ثابت AVSide_داده_Descriptor sd_props[] = {
    [AV_قاب_داده_PANSCAN]                     = { "AVPanScan",                                    AV_SIDE_داده_PROP_اندازه_DEPENDENT },
    [AV_قاب_داده_A53_CC]                      = { "ATSC A53 Part 4 Closed Captions" },
    [AV_قاب_داده_MATRIXENCODING]              = { "AVMatrixEncoding",                             AV_SIDE_داده_PROP_CHANNEL_DEPENDENT },
    [AV_قاب_داده_DOWNMIX_INFO]                = { "Metadata relevant to a downmix procedure",     AV_SIDE_داده_PROP_CHANNEL_DEPENDENT },
    [AV_قاب_داده_AFD]                         = { "Active format description" },
    [AV_قاب_داده_MOTION_VECTORS]              = { "Motion vectors",                               AV_SIDE_داده_PROP_اندازه_DEPENDENT },
    [AV_قاب_داده_SKIP_SAMPLES]                = { "Skip samples" },
    [AV_قاب_داده_GOP_TIMECODE]                = { "GOP timecode" },
    [AV_قاب_داده_S12_M_TIMECODE]               = { "SMPTE 12-1 timecode" },
    [AV_قاب_داده_DYNAMIC_HDR_PLUS]            = { "HDR Dynamic Metadata SMPTE2094-40 (HDR10+)",   AV_SIDE_داده_PROP_COLOR_DEPENDENT },
    [AV_قاب_داده_DYNAMIC_HDR_VIVID]           = { "HDR Dynamic Metadata CUVA 005.1 2021 (Vivid)", AV_SIDE_داده_PROP_COLOR_DEPENDENT },
    [AV_قاب_داده_DYNAMIC_HDR_SMPTE_2094_APP5] = { "HDR Dynamic Metadata SMPTE2094-50",            AV_SIDE_داده_PROP_COLOR_DEPENDENT },
    [AV_قاب_داده_REGIONS_از_INTEREST]         = { "Regions Of Interest",                          AV_SIDE_داده_PROP_اندازه_DEPENDENT },
    [AV_قاب_داده_VIDEO_ENC_PARAMS]            = { "Video encoding parameters" },
    [AV_قاب_داده_FILM_GRAIN_PARAMS]           = { "Film grain parameters" },
    [AV_قاب_داده_DETECTION_BBOXES]            = { "Bounding boxes for object detection and classification", AV_SIDE_داده_PROP_اندازه_DEPENDENT },
    [AV_قاب_داده_DOVI_RPU_میانگیر]             = { "Dolby Vision RPU Data",                        AV_SIDE_داده_PROP_COLOR_DEPENDENT },
    [AV_قاب_داده_DOVI_METADATA]               = { "Dolby Vision Metadata",                        AV_SIDE_داده_PROP_COLOR_DEPENDENT },
    [AV_قاب_داده_LCEVC]                       = { "LCEVC NAL data",                               AV_SIDE_داده_PROP_اندازه_DEPENDENT },
    [AV_قاب_داده_VIEW_ID]                     = { "View ID" },
    [AV_قاب_داده_STEREO3_D]                    = { "Stereo 3D",                                    AV_SIDE_داده_PROP_GLOBAL },
    [AV_قاب_داده_REPLAYGAIN]                  = { "AVReplayGain",                                 AV_SIDE_داده_PROP_GLOBAL },
    [AV_قاب_داده_DISPLAYMATRIX]               = { "3x3 displaymatrix",                            AV_SIDE_داده_PROP_GLOBAL },
    [AV_قاب_داده_AUDIO_SERVICE_TYPE]          = { "Audio service type",                           AV_SIDE_داده_PROP_GLOBAL },
    [AV_قاب_داده_MASTERING_DISPLAY_METADATA]  = { "Mastering display metadata",                   AV_SIDE_داده_PROP_GLOBAL | AV_SIDE_داده_PROP_COLOR_DEPENDENT },
    [AV_قاب_داده_CONTENT_LIGHT_LEVEL]         = { "Content light level metadata",                 AV_SIDE_داده_PROP_GLOBAL | AV_SIDE_داده_PROP_COLOR_DEPENDENT },
    [AV_قاب_داده_AMBIENT_VIEWING_ENVIRONMENT] = { "Ambient viewing environment",                  AV_SIDE_داده_PROP_GLOBAL },
    [AV_قاب_داده_SPHERICAL]                   = { "Spherical Mapping",                            AV_SIDE_داده_PROP_GLOBAL | AV_SIDE_داده_PROP_اندازه_DEPENDENT },
    [AV_قاب_داده_ICC_PROFILE]                 = { "ICC profile",                                  AV_SIDE_داده_PROP_GLOBAL | AV_SIDE_داده_PROP_COLOR_DEPENDENT },
    [AV_قاب_داده_EXIF]                        = { "EXIF metadata",                                AV_SIDE_داده_PROP_GLOBAL },
    [AV_قاب_داده_SEI_UNREGISTERED]            = { "H.26[45] User Data Unregistered SEI message",  AV_SIDE_داده_PROP_MULTI },
    [AV_قاب_داده_VIDEO_HINT]                  = { "Encoding video hint",                          AV_SIDE_داده_PROP_اندازه_DEPENDENT },
    [AV_قاب_داده_3_D_REFERENCE_DISPLAYS]       = { "3D Reference Displays Information",            AV_SIDE_داده_PROP_GLOBAL },
    [AV_قاب_داده_IAMF_MIX_GAIN_PARAM]         = { "IAMF Mix Gain Parameter Data" },
    [AV_قاب_داده_IAMF_DEMIXING_INFO_PARAM]    = { "IAMF Demixing Info Parameter Data",            AV_SIDE_داده_PROP_CHANNEL_DEPENDENT },
    [AV_قاب_داده_IAMF_RECON_GAIN_INFO_PARAM]  = { "IAMF Recon Gain Info Parameter Data" },
    [AV_قاب_داده_RAW_COLOR_PARAMS]            = { "RAW camera color parameters",                  AV_SIDE_داده_PROP_GLOBAL | AV_SIDE_داده_PROP_COLOR_DEPENDENT },
    [AV_قاب_داده_DOWNMIX_ماتریس]              = { "Downmix Matrix",                               AV_SIDE_داده_PROP_CHANNEL_DEPENDENT },
    [AV_قاب_داده_GAIN_MAP_PARAMS]             = { "Gain map parameters",                          AV_SIDE_داده_PROP_GLOBAL | AV_SIDE_داده_PROP_COLOR_DEPENDENT },
};

ثابت AVSide_داده_Descriptor *av_قاب_side_داده_desc(تعداد AVFrame_Side_داده_Type type)
{
    بیعلامت t = type;
    إذا (t < FF_ARRAY_ELEMS(sd_props) && sd_props[t].name)
        أرجع &sd_props[t];
    أرجع عدم;
}

ثابت حرف *av_قاب_side_داده_name(تعداد AVFrame_Side_داده_Type type)
{
    ثابت AVSide_داده_Descriptor *desc = av_قاب_side_داده_desc(type);
    أرجع desc ? desc->name : عدم;
}

ساكن فراغ free_side_داده_مدخل(AVFrame_Side_داده **ptr_sd)
{
    AVFrame_Side_داده *sd = *ptr_sd;

    av_میانگیر_unref(&sd->buf);
    av_dict_free(&sd->metadata);
    av_freep(ptr_sd);
}

ساكن فراغ remove_side_داده_by_مدخل(AVFrame_Side_داده ***sd, صحيح *nb_sd,
                                      ثابت AVFrame_Side_داده *هدف)
{
    لكل (صحيح i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_داده *مدخل = ((*sd)[i]);
        إذا (مدخل != هدف)
            استمر;

        free_side_داده_مدخل(&مدخل);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;

        أرجع;
    }
}

فراغ av_قاب_side_داده_remove(AVFrame_Side_داده ***sd, صحيح *nb_sd,
                               تعداد AVFrame_Side_داده_Type type)
{
    لكل (صحيح i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_داده *مدخل = ((*sd)[i]);
        إذا (مدخل->type != type)
            استمر;

        free_side_داده_مدخل(&مدخل);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

فراغ av_قاب_side_داده_remove_by_props(AVFrame_Side_داده ***sd, صحيح *nb_sd,
                                        صحيح props)
{
    لكل (صحيح i = *nb_sd - 1; i >= 0; i--) {
        AVFrame_Side_داده *مدخل = ((*sd)[i]);
        ثابت AVSide_داده_Descriptor *desc = av_قاب_side_داده_desc(مدخل->type);
        إذا (!desc || !(desc->props & props))
            استمر;

        free_side_داده_مدخل(&مدخل);

        ((*sd)[i]) = ((*sd)[*nb_sd - 1]);
        (*nb_sd)--;
    }
}

فراغ av_قاب_side_داده_free(AVFrame_Side_داده ***sd, صحيح *nb_sd)
{
    لكل (صحيح i = 0; i < *nb_sd; i++)
        free_side_داده_مدخل(&((*sd)[i]));
    *nb_sd = 0;

    av_freep(sd);
}

ساكن AVFrame_Side_داده *جمع_کن_side_داده_from_buf_ext(AVFrame_Side_داده ***sd,
                                                   صحيح *nb_sd,
                                                   تعداد AVFrame_Side_داده_Type type,
                                                   AVBufferRef *buf, uint8_t *داده,
                                                   size_t اندازه)
{
    AVFrame_Side_داده *ret, **tmp;

    // *nb_sd + 1 needs to fit into an int and a size_t.
    إذا ((بیعلامت)*nb_sd >= FFMIN(بیشترین_صحیح, SIZE_MAX))
        أرجع عدم;

    tmp = av_realloc_array(*sd, *nb_sd + 1, حجم(**sd));
    إذا (!tmp)
        أرجع عدم;
    *sd = tmp;

    ret = av_mallocz(حجم(*ret));
    إذا (!ret)
        أرجع عدم;

    ret->buf = buf;
    ret->داده = داده;
    ret->اندازه = اندازه;
    ret->type = type;

    (*sd)[(*nb_sd)++] = ret;

    أرجع ret;
}

AVFrame_Side_داده *ff_قاب_side_داده_جمع_کن_from_buf(AVFrame_Side_داده ***sd,
                                                 صحيح *nb_sd,
                                                 تعداد AVFrame_Side_داده_Type type,
                                                 AVBufferRef *buf)
{
    إذا (!buf)
        أرجع عدم;

    أرجع جمع_کن_side_داده_from_buf_ext(sd, nb_sd, type, buf, buf->داده, buf->اندازه);
}

ساكن AVFrame_Side_داده *replace_side_داده_from_buf(AVFrame_Side_داده *dst,
                                                   AVBufferRef *buf, صحيح flags)
{
    إذا (!(flags & AV_قاب_SIDE_داده_FLAG_REPLACE))
        أرجع عدم;

    av_dict_free(&dst->metadata);
    av_میانگیر_unref(&dst->buf);
    dst->buf  = buf;
    dst->داده = buf->داده;
    dst->اندازه = buf->اندازه;
    أرجع dst;
}

AVFrame_Side_داده *av_قاب_side_داده_new(AVFrame_Side_داده ***sd, صحيح *nb_sd,
                                        تعداد AVFrame_Side_داده_Type type,
                                        size_t اندازه, بیعلامت صحيح flags)
{
    ثابت AVSide_داده_Descriptor *desc = av_قاب_side_داده_desc(type);
    AVBufferRef     *buf = av_میانگیر_alloc(اندازه);
    AVFrame_Side_داده *ret = عدم;

    إذا (flags & AV_قاب_SIDE_داده_FLAG_UNIQUE)
        av_قاب_side_داده_remove(sd, nb_sd, type);
    إذا ((!desc || !(desc->props & AV_SIDE_داده_PROP_MULTI)) &&
        (ret = (AVFrame_Side_داده *)av_قاب_side_داده_get(*sd, *nb_sd, type))) {
        ret = replace_side_داده_from_buf(ret, buf, flags);
        إذا (!ret)
            av_میانگیر_unref(&buf);
        أرجع ret;
    }

    ret = ff_قاب_side_داده_جمع_کن_from_buf(sd, nb_sd, type, buf);
    إذا (!ret)
        av_میانگیر_unref(&buf);

    أرجع ret;
}

AVFrame_Side_داده *av_قاب_side_داده_جمع_کن(AVFrame_Side_داده ***sd, صحيح *nb_sd,
                                        تعداد AVFrame_Side_داده_Type type,
                                        AVBufferRef **pbuf, بیعلامت صحيح flags)
{
    ثابت AVSide_داده_Descriptor *desc = av_قاب_side_داده_desc(type);
    AVFrame_Side_داده *sd_dst  = عدم;
    AVBufferRef *buf = *pbuf;

    إذا ((flags & AV_قاب_SIDE_داده_FLAG_NEW_REF) && !(buf = av_میانگیر_ref(*pbuf)))
        أرجع عدم;
    إذا (flags & AV_قاب_SIDE_داده_FLAG_UNIQUE)
        av_قاب_side_داده_remove(sd, nb_sd, type);
    إذا ((!desc || !(desc->props & AV_SIDE_داده_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_داده *)av_قاب_side_داده_get(*sd, *nb_sd, type))) {
        sd_dst = replace_side_داده_from_buf(sd_dst, buf, flags);
    } وإلا
        sd_dst = ff_قاب_side_داده_جمع_کن_from_buf(sd, nb_sd, type, buf);

    إذا (sd_dst && !(flags & AV_قاب_SIDE_داده_FLAG_NEW_REF))
        *pbuf = عدم;
    وإلا إذا (!sd_dst && (flags & AV_قاب_SIDE_داده_FLAG_NEW_REF))
        av_میانگیر_unref(&buf);
    أرجع sd_dst;
}

صحيح av_قاب_side_داده_clone(AVFrame_Side_داده ***sd, صحيح *nb_sd,
                             ثابت AVFrame_Side_داده *src, بیعلامت صحيح flags)
{
    ثابت AVSide_داده_Descriptor *desc;
    AVBufferRef     *buf    = عدم;
    AVFrame_Side_داده *sd_dst = عدم;
    صحيح              ret    = AVERROR_BUG;

    إذا (!sd || !src || !nb_sd || (*nb_sd && !*sd))
        أرجع AVERROR(EINVAL);

    desc = av_قاب_side_داده_desc(src->type);
    إذا (flags & AV_قاب_SIDE_داده_FLAG_UNIQUE)
        av_قاب_side_داده_remove(sd, nb_sd, src->type);
    إذا ((!desc || !(desc->props & AV_SIDE_داده_PROP_MULTI)) &&
        (sd_dst = (AVFrame_Side_داده *)av_قاب_side_داده_get(*sd, *nb_sd, src->type))) {
        AVDictionary *dict = عدم;

        إذا (!(flags & AV_قاب_SIDE_داده_FLAG_REPLACE))
            أرجع AVERROR(EEXIST);

        ret = av_dict_copy(&dict, src->metadata, 0);
        إذا (ret < 0)
            أرجع ret;

        ret = av_میانگیر_replace(&sd_dst->buf, src->buf);
        إذا (ret < 0) {
            av_dict_free(&dict);
            أرجع ret;
        }

        av_dict_free(&sd_dst->metadata);
        sd_dst->metadata = dict;
        sd_dst->داده     = src->داده;
        sd_dst->اندازه     = src->اندازه;
        أرجع 0;
    }

    buf = av_میانگیر_ref(src->buf);
    إذا (!buf)
        أرجع AVERROR(ENOMEM);

    sd_dst = جمع_کن_side_داده_from_buf_ext(sd, nb_sd, src->type, buf,
                                        src->داده, src->اندازه);
    إذا (!sd_dst) {
        av_میانگیر_unref(&buf);
        أرجع AVERROR(ENOMEM);
    }

    ret = av_dict_copy(&sd_dst->metadata, src->metadata, 0);
    إذا (ret < 0) {
        remove_side_داده_by_مدخل(sd, nb_sd, sd_dst);
        أرجع ret;
    }

    أرجع 0;
}

ثابت AVFrame_Side_داده *av_قاب_side_داده_get_c(ثابت AVFrame_Side_داده * ثابت *sd,
                                                ثابت صحيح nb_sd,
                                                تعداد AVFrame_Side_داده_Type type)
{
    لكل (صحيح i = 0; i < nb_sd; i++) {
        إذا (sd[i]->type == type)
            أرجع sd[i];
    }
    أرجع عدم;
}
