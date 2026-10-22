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

    int64_t             version; ///< version of AMF runtime
    AMFContext         *context;
    AMF_MEMORY_TYPE     memory_type;

    فراغ (*lock)(فراغ *lock_ctx);
    فراغ (*unlock)(فراغ *lock_ctx);
    فراغ *lock_ctx;
} AVAMFDeviceContext;

تعداد AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx);

تعداد AMF_SURFACE_FORMAT av_av_to_amf_format(تعداد AVPixelFormat fmt);
تعداد AVPixelFormat av_amf_to_av_format(تعداد AMF_SURFACE_FORMAT fmt);

تعداد AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(تعداد AVColorRange color_range, تعداد AVColorSpace color_space);
صحيح av_amf_display_mastering_meta_to_hdrmeta(ثابت AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
صحيح av_amf_light_metadata_to_hdrmeta(ثابت AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
صحيح av_amf_extract_hdr_metadata(ثابت AVFrame *frame, AMFHDRMetadata *hdrmeta);
صحيح av_amf_attach_hdr_metadata(AVFrame *frame, ثابت AMFHDRMetadata *hdrmeta);

#endif /* AVUTIL_HWCONTEXT_AMF_H */
