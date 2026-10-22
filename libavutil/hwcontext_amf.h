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


#اگر_غیر_تعریف_شدہ AVUTIL_HWCONTEXT_AMF_H
#تعریف_کرو AVUTIL_HWCONTEXT_AMF_H

#شامل "pixfmt.h"
#شامل "hwcontext.h"
#شامل <AMF/core/Factory.h>
#شامل <AMF/core/Context.h>
#شامل <AMF/core/Trace.h>
#شامل <AMF/core/Debug.h>
#شامل <AMF/components/ColorSpace.h>
#شامل "libavutil/mastering_display_metadata.h"

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
قسمتعریف ساخت AVAMFDeviceContext {
    خالی *              library;
    AMFFactory         *factory;
    خالی               *trace_writer;

    int64_t             نسخہ; ///< version of AMF runtime
    AMFContext         *context;
    AMF_حافظہ_TYPE     حافظہ_type;

    خالی (*تالا_2)(خالی *تالا_ctx);
    خالی (*unlock)(خالی *تالا_ctx);
    خالی *تالا_ctx;
} AVAMFDeviceContext;

شمار AMF_حافظہ_TYPE av_amf_get_حافظہ_type(AVAMFDeviceContext *amf_ctx);

شمار AMF_SURFACE_FORMAT av_av_مقصد_amf_format(شمار AVPixelFormat fmt);
شمار AVPixelFormat av_amf_مقصد_av_format(شمار AMF_SURFACE_FORMAT fmt);

شمار AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(شمار AVColorRange color_range, شمار AVColorSpace color_space);
صحیح av_amf_display_mastering_meta_مقصد_hdrmeta(ثابت AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
صحیح av_amf_light_metadata_مقصد_hdrmeta(ثابت AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
صحیح av_amf_نکالو_hdr_metadata(ثابت AVFrame *چوکھٹا, AMFHDRMetadata *hdrmeta);
صحیح av_amf_attach_hdr_metadata(AVFrame *چوکھٹا, ثابت AMFHDRMetadata *hdrmeta);

#اگر_ختم /* AVUTIL_HWCONTEXT_AMF_H */
