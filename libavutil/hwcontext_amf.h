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

#অন্তর্ভাৱ "pixfmt.h"
#অন্তর্ভাৱ "hwcontext.h"
#অন্তর্ভাৱ <AMF/core/Factory.h>
#অন্তর্ভাৱ <AMF/core/Context.h>
#অন্তর্ভাৱ <AMF/core/Trace.h>
#অন্তর্ভাৱ <AMF/core/Debug.h>
#অন্তর্ভাৱ <AMF/components/ColorSpace.h>
#অন্তর্ভাৱ "libavutil/mastering_display_metadata.h"

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
প্রকারনির্দেশ সংরচনা AVAMFDeviceContext {
    শূন্য *              library;
    AMFFactory         *factory;
    শূন্য               *trace_writer;

    int64_t             version; ///< version of AMF runtime
    AMFContext         *context;
    AMF_MEMORY_TYPE     memory_type;

    শূন্য (*lock)(শূন্য *lock_ctx);
    শূন্য (*unlock)(শূন্য *lock_ctx);
    শূন্য *lock_ctx;
} AVAMFDeviceContext;

গণনা AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx);

গণনা AMF_SURFACE_FORMAT av_av_to_amf_format(গণনা AVPixelFormat fmt);
গণনা AVPixelFormat av_amf_to_av_format(গণনা AMF_SURFACE_FORMAT fmt);

গণনা AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(গণনা AVColorRange color_range, গণনা AVColorSpace color_space);
পূর্ণাঙ্ক av_amf_display_mastering_meta_to_hdrmeta(ধ্রুৱ AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
পূর্ণাঙ্ক av_amf_light_metadata_to_hdrmeta(ধ্রুৱ AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
পূর্ণাঙ্ক av_amf_extract_hdr_metadata(ধ্রুৱ AVFrame *frame, AMFHDRMetadata *hdrmeta);
পূর্ণাঙ্ক av_amf_attach_hdr_metadata(AVFrame *frame, ধ্রুৱ AMFHDRMetadata *hdrmeta);

#endif /* AVUTIL_HWCONTEXT_AMF_H */
