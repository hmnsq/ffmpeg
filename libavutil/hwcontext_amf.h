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


#اگر_تعریف_نشده AVUTIL_HWCONTEXT_AMF_H
#تعریف_کن AVUTIL_HWCONTEXT_AMF_H

#ضمن "pixfmt.h"
#ضمن "hwcontext.h"
#ضمن <AMF/core/Factory.h>
#ضمن <AMF/core/Context.h>
#ضمن <AMF/core/Trace.h>
#ضمن <AMF/core/Debug.h>
#ضمن <AMF/components/ColorSpace.h>
#ضمن "libavutil/mastering_display_metadata.h"

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
تعريفنوع بنية AVAMFDeviceContext {
    فراغ *              library;
    AMFFactory         *factory;
    فراغ               *trace_writer;

    int64_t             نسخه; ///< version of AMF runtime
    AMFContext         *context;
    AMF_حافظه_TYPE     حافظه_type;

    فراغ (*قفل_2)(فراغ *قفل_ctx);
    فراغ (*unlock)(فراغ *قفل_ctx);
    فراغ *قفل_ctx;
} AVAMFDeviceContext;

تعداد AMF_حافظه_TYPE av_amf_get_حافظه_type(AVAMFDeviceContext *amf_ctx);

تعداد AMF_SURFACE_FORMAT av_av_مقصد_amf_format(تعداد AVPixelFormat fmt);
تعداد AVPixelFormat av_amf_مقصد_av_format(تعداد AMF_SURFACE_FORMAT fmt);

تعداد AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(تعداد AVColorRange color_range, تعداد AVColorSpace color_space);
صحيح av_amf_display_mastering_meta_مقصد_hdrmeta(ثابت AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
صحيح av_amf_light_metadata_مقصد_hdrmeta(ثابت AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
صحيح av_amf_استخراج_hdr_metadata(ثابت AVFrame *قاب, AMFHDRMetadata *hdrmeta);
صحيح av_amf_attach_hdr_metadata(AVFrame *قاب, ثابت AMFHDRMetadata *hdrmeta);

#پایان_اگر /* AVUTIL_HWCONTEXT_AMF_H */
