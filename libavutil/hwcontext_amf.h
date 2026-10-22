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

#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव <AMF/core/Factory.h>
#अन्तर्भाव <AMF/core/Context.h>
#अन्तर्भाव <AMF/core/Trace.h>
#अन्तर्भाव <AMF/core/Debug.h>
#अन्तर्भाव <AMF/components/ColorSpace.h>
#अन्तर्भाव "libavutil/mastering_display_metadata.h"

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
प्रकारव्याख्या संरचना AVAMFDeviceContext {
    शून्य *              library;
    AMFFactory         *factory;
    शून्य               *trace_writer;

    int64_t             version; ///< version of AMF runtime
    AMFContext         *context;
    AMF_MEMORY_TYPE     memory_type;

    शून्य (*lock)(शून्य *lock_ctx);
    शून्य (*unlock)(शून्य *lock_ctx);
    शून्य *lock_ctx;
} AVAMFDeviceContext;

गणना AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx);

गणना AMF_SURFACE_FORMAT av_av_to_amf_format(गणना AVPixelFormat fmt);
गणना AVPixelFormat av_amf_to_av_format(गणना AMF_SURFACE_FORMAT fmt);

गणना AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(गणना AVColorRange color_range, गणना AVColorSpace color_space);
पूर्णांक av_amf_display_mastering_meta_to_hdrmeta(स्थिरांक AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
पूर्णांक av_amf_light_metadata_to_hdrmeta(स्थिरांक AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
पूर्णांक av_amf_extract_hdr_metadata(स्थिरांक AVFrame *frame, AMFHDRMetadata *hdrmeta);
पूर्णांक av_amf_attach_hdr_metadata(AVFrame *frame, स्थिरांक AMFHDRMetadata *hdrmeta);

#endif /* AVUTIL_HWCONTEXT_AMF_H */
