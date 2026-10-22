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

#அந்தர்பாவ "pixfmt.h"
#அந்தர்பாவ "hwcontext.h"
#அந்தர்பாவ <AMF/core/Factory.h>
#அந்தர்பாவ <AMF/core/Context.h>
#அந்தர்பாவ <AMF/core/Trace.h>
#அந்தர்பாவ <AMF/core/Debug.h>
#அந்தர்பாவ <AMF/components/ColorSpace.h>
#அந்தர்பாவ "libavutil/mastering_display_metadata.h"

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
வகைவரை கட்டமைப்பு AVAMFDeviceContext {
    வெறுமை *              library;
    AMFFactory         *factory;
    வெறுமை               *trace_writer;

    int64_t             version; ///< version of AMF runtime
    AMFContext         *context;
    AMF_MEMORY_TYPE     memory_type;

    வெறுமை (*lock)(வெறுமை *lock_ctx);
    வெறுமை (*unlock)(வெறுமை *lock_ctx);
    வெறுமை *lock_ctx;
} AVAMFDeviceContext;

எண்ணிக்கை AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx);

எண்ணிக்கை AMF_SURFACE_FORMAT av_av_to_amf_format(எண்ணிக்கை AVPixelFormat fmt);
எண்ணிக்கை AVPixelFormat av_amf_to_av_format(எண்ணிக்கை AMF_SURFACE_FORMAT fmt);

எண்ணிக்கை AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(எண்ணிக்கை AVColorRange color_range, எண்ணிக்கை AVColorSpace color_space);
முழு av_amf_display_mastering_meta_to_hdrmeta(மாறிலி AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
முழு av_amf_light_metadata_to_hdrmeta(மாறிலி AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
முழு av_amf_extract_hdr_metadata(மாறிலி AVFrame *frame, AMFHDRMetadata *hdrmeta);
முழு av_amf_attach_hdr_metadata(AVFrame *frame, மாறிலி AMFHDRMetadata *hdrmeta);

#endif /* AVUTIL_HWCONTEXT_AMF_H */
