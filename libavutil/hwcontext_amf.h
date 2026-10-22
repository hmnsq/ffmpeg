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


#यदि_अपरिभाषितम् AVUTIL_HWCONTEXT_AMF_H
#परिभाषय AVUTIL_HWCONTEXT_AMF_H

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
प्रकारनिर्देश संरचना AVAMFDeviceContext {
    शून्य *              library;
    AMFFactory         *factory;
    शून्य               *trace_writer;

    int64_t             संस्करणम्; ///< version of AMF runtime
    AMFContext         *context;
    AMF_स्मृतिः_TYPE     स्मृतिः_type;

    शून्य (*तालकम्)(शून्य *तालकम्_ctx);
    शून्य (*unlock)(शून्य *तालकम्_ctx);
    शून्य *तालकम्_ctx;
} AVAMFDeviceContext;

गणना AMF_स्मृतिः_TYPE av_amf_get_स्मृतिः_type(AVAMFDeviceContext *amf_ctx);

गणना AMF_SURFACE_FORMAT av_av_गन्तव्यम्_amf_format(गणना AVPixelFormat fmt);
गणना AVPixelFormat av_amf_गन्तव्यम्_av_format(गणना AMF_SURFACE_FORMAT fmt);

गणना AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(गणना AVColorRange color_range, गणना AVColorSpace color_space);
पूर्णाङ्क av_amf_display_mastering_meta_गन्तव्यम्_hdrmeta(ध्रुव AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
पूर्णाङ्क av_amf_light_metadata_गन्तव्यम्_hdrmeta(ध्रुव AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
पूर्णाङ्क av_amf_extract_hdr_metadata(ध्रुव AVFrame *frame, AMFHDRMetadata *hdrmeta);
पूर्णाङ्क av_amf_attach_hdr_metadata(AVFrame *frame, ध्रुव AMFHDRMetadata *hdrmeta);

#यदि_अन्तः /* AVUTIL_HWCONTEXT_AMF_H */
