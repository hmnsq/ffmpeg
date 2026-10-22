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

#ଅନ୍ତର୍ଭାଵ "pixfmt.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"
#ଅନ୍ତର୍ଭାଵ <AMF/core/Factory.h>
#ଅନ୍ତର୍ଭାଵ <AMF/core/Context.h>
#ଅନ୍ତର୍ଭାଵ <AMF/core/Trace.h>
#ଅନ୍ତର୍ଭାଵ <AMF/core/Debug.h>
#ଅନ୍ତର୍ଭାଵ <AMF/components/ColorSpace.h>
#ଅନ୍ତର୍ଭାଵ "libavutil/mastering_display_metadata.h"

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା AVAMFDeviceContext {
    ଶୂନ୍ୟ *              library;
    AMFFactory         *factory;
    ଶୂନ୍ୟ               *trace_writer;

    int64_t             version; ///< version of AMF runtime
    AMFContext         *context;
    AMF_MEMORY_TYPE     memory_type;

    ଶୂନ୍ୟ (*lock)(ଶୂନ୍ୟ *lock_ctx);
    ଶୂନ୍ୟ (*unlock)(ଶୂନ୍ୟ *lock_ctx);
    ଶୂନ୍ୟ *lock_ctx;
} AVAMFDeviceContext;

ଗଣନା AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx);

ଗଣନା AMF_SURFACE_FORMAT av_av_to_amf_format(ଗଣନା AVPixelFormat fmt);
ଗଣନା AVPixelFormat av_amf_to_av_format(ଗଣନା AMF_SURFACE_FORMAT fmt);

ଗଣନା AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(ଗଣନା AVColorRange color_range, ଗଣନା AVColorSpace color_space);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_amf_display_mastering_meta_to_hdrmeta(ଅଚଳ AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_amf_light_metadata_to_hdrmeta(ଅଚଳ AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_amf_extract_hdr_metadata(ଅଚଳ AVFrame *frame, AMFHDRMetadata *hdrmeta);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_amf_attach_hdr_metadata(AVFrame *frame, ଅଚଳ AMFHDRMetadata *hdrmeta);

#endif /* AVUTIL_HWCONTEXT_AMF_H */
