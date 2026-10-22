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


#ifndef AVUTIL_HWCONTEXT_AMF_H
#define AVUTIL_HWCONTEXT_AMF_H

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
تعریفنوع ساختار AVAMFDeviceContext {
    تهی *              library;
    AMFFactory         *factory;
    تهی               *trace_writer;

    int64_t             version; ///< version of AMF runtime
    AMFContext         *context;
    AMF_MEMORY_TYPE     memory_type;

    تهی (*lock)(تهی *lock_ctx);
    تهی (*unlock)(تهی *lock_ctx);
    تهی *lock_ctx;
} AVAMFDeviceContext;

شمارش AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx);

شمارش AMF_SURFACE_FORMAT av_av_to_amf_format(شمارش AVPixelFormat fmt);
شمارش AVPixelFormat av_amf_to_av_format(شمارش AMF_SURFACE_FORMAT fmt);

شمارش AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(شمارش AVColorRange color_range, شمارش AVColorSpace color_space);
صحیح av_amf_display_mastering_meta_to_hdrmeta(ثابت AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
صحیح av_amf_light_metadata_to_hdrmeta(ثابت AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
صحیح av_amf_extract_hdr_metadata(ثابت AVFrame *frame, AMFHDRMetadata *hdrmeta);
صحیح av_amf_attach_hdr_metadata(AVFrame *frame, ثابت AMFHDRMetadata *hdrmeta);

#endif /* AVUTIL_HWCONTEXT_AMF_H */
