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


#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_HWCONTEXT_AMF_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_HWCONTEXT_AMF_H

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
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVAMFDeviceContext {
    ಶೂನ್ಯ *              library;
    AMFFactory         *factory;
    ಶೂನ್ಯ               *trace_writer;

    int64_t             ಆವೃತ್ತಿ; ///< version of AMF runtime
    AMFContext         *context;
    AMF_ಸ್ಮರಣೆ_TYPE     ಸ್ಮರಣೆ_type;

    ಶೂನ್ಯ (*ಬೀಗ_2)(ಶೂನ್ಯ *ಬೀಗ_ctx);
    ಶೂನ್ಯ (*unlock)(ಶೂನ್ಯ *ಬೀಗ_ctx);
    ಶೂನ್ಯ *ಬೀಗ_ctx;
} AVAMFDeviceContext;

ಎಣಿಕೆ AMF_ಸ್ಮರಣೆ_TYPE av_amf_get_ಸ್ಮರಣೆ_type(AVAMFDeviceContext *amf_ctx);

ಎಣಿಕೆ AMF_SURFACE_FORMAT av_av_ಗಮ್ಯ_amf_format(ಎಣಿಕೆ AVPixelFormat fmt);
ಎಣಿಕೆ AVPixelFormat av_amf_ಗಮ್ಯ_av_format(ಎಣಿಕೆ AMF_SURFACE_FORMAT fmt);

ಎಣಿಕೆ AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(ಎಣಿಕೆ AVColorRange color_range, ಎಣಿಕೆ AVColorSpace color_space);
ಪೂರ್ಣಾಂಕ av_amf_display_mastering_meta_ಗಮ್ಯ_hdrmeta(ಸ್ಥಿರಾಂಕ AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
ಪೂರ್ಣಾಂಕ av_amf_light_metadata_ಗಮ್ಯ_hdrmeta(ಸ್ಥಿರಾಂಕ AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
ಪೂರ್ಣಾಂಕ av_amf_ಹೊರತೆಗೆ_hdr_metadata(ಸ್ಥಿರಾಂಕ AVFrame *ಚೌಕಟ್ಟು, AMFHDRMetadata *hdrmeta);
ಪೂರ್ಣಾಂಕ av_amf_attach_hdr_metadata(AVFrame *ಚೌಕಟ್ಟು, ಸ್ಥಿರಾಂಕ AMFHDRMetadata *hdrmeta);

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_HWCONTEXT_AMF_H */
