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

#અન્તર્ભાવ "pixfmt.h"
#અન્તર્ભાવ "hwcontext.h"
#અન્તર્ભાવ <AMF/core/Factory.h>
#અન્તર્ભાવ <AMF/core/Context.h>
#અન્તર્ભાવ <AMF/core/Trace.h>
#અન્તર્ભાવ <AMF/core/Debug.h>
#અન્તર્ભાવ <AMF/components/ColorSpace.h>
#અન્તર્ભાવ "libavutil/mastering_display_metadata.h"

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
પ્રકારવ્યાખ્યા સંરચના AVAMFDeviceContext {
    શૂન્ય *              library;
    AMFFactory         *factory;
    શૂન્ય               *trace_writer;

    int64_t             version; ///< version of AMF runtime
    AMFContext         *context;
    AMF_MEMORY_TYPE     memory_type;

    શૂન્ય (*lock)(શૂન્ય *lock_ctx);
    શૂન્ય (*unlock)(શૂન્ય *lock_ctx);
    શૂન્ય *lock_ctx;
} AVAMFDeviceContext;

ગણના AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx);

ગણના AMF_SURFACE_FORMAT av_av_to_amf_format(ગણના AVPixelFormat fmt);
ગણના AVPixelFormat av_amf_to_av_format(ગણના AMF_SURFACE_FORMAT fmt);

ગણના AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(ગણના AVColorRange color_range, ગણના AVColorSpace color_space);
પૂર્ણાંક av_amf_display_mastering_meta_to_hdrmeta(અચલ AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
પૂર્ણાંક av_amf_light_metadata_to_hdrmeta(અચલ AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
પૂર્ણાંક av_amf_extract_hdr_metadata(અચલ AVFrame *frame, AMFHDRMetadata *hdrmeta);
પૂર્ણાંક av_amf_attach_hdr_metadata(AVFrame *frame, અચલ AMFHDRMetadata *hdrmeta);

#endif /* AVUTIL_HWCONTEXT_AMF_H */
