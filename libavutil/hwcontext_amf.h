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

#ಅನ್ತರ್ಭಾವ "pixfmt.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ <AMF/core/Factory.h>
#ಅನ್ತರ್ಭಾವ <AMF/core/Context.h>
#ಅನ್ತರ್ಭಾವ <AMF/core/Trace.h>
#ಅನ್ತರ್ಭಾವ <AMF/core/Debug.h>
#ಅನ್ತರ್ಭಾವ <AMF/components/ColorSpace.h>
#ಅನ್ತರ್ಭಾವ "libavutil/mastering_display_metadata.h"

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AVAMFDeviceContext {
    ಶೂನ್ಯ *              library;
    AMFFactory         *factory;
    ಶೂನ್ಯ               *trace_writer;

    int64_t             version; ///< version of AMF runtime
    AMFContext         *context;
    AMF_MEMORY_TYPE     memory_type;

    ಶೂನ್ಯ (*lock)(ಶೂನ್ಯ *lock_ctx);
    ಶೂನ್ಯ (*unlock)(ಶೂನ್ಯ *lock_ctx);
    ಶೂನ್ಯ *lock_ctx;
} AVAMFDeviceContext;

ಗಣನಾ AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx);

ಗಣನಾ AMF_SURFACE_FORMAT av_av_to_amf_format(ಗಣನಾ AVPixelFormat fmt);
ಗಣನಾ AVPixelFormat av_amf_to_av_format(ಗಣನಾ AMF_SURFACE_FORMAT fmt);

ಗಣನಾ AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(ಗಣನಾ AVColorRange color_range, ಗಣನಾ AVColorSpace color_space);
ಪೂರ್ಣಾಙ್ಕ av_amf_display_mastering_meta_to_hdrmeta(ಧ್ರುವ AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
ಪೂರ್ಣಾಙ್ಕ av_amf_light_metadata_to_hdrmeta(ಧ್ರುವ AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
ಪೂರ್ಣಾಙ್ಕ av_amf_extract_hdr_metadata(ಧ್ರುವ AVFrame *frame, AMFHDRMetadata *hdrmeta);
ಪೂರ್ಣಾಙ್ಕ av_amf_attach_hdr_metadata(AVFrame *frame, ಧ್ರುವ AMFHDRMetadata *hdrmeta);

#endif /* AVUTIL_HWCONTEXT_AMF_H */
