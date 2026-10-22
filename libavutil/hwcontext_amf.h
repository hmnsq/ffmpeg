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


#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_HWCONTEXT_AMF_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_HWCONTEXT_AMF_H

#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <AMF/core/Factory.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <AMF/core/Context.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <AMF/core/Trace.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <AMF/core/Debug.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <AMF/components/ColorSpace.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mastering_display_metadata.h"

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVAMFDeviceContext {
    ਖਾਲੀ *              library;
    AMFFactory         *factory;
    ਖਾਲੀ               *trace_writer;

    int64_t             ਸੰਸਕਰਣ; ///< version of AMF runtime
    AMFContext         *context;
    AMF_ਸਮ੍ਰਿਤੀ_TYPE     ਸਮ੍ਰਿਤੀ_type;

    ਖਾਲੀ (*ਤਾਲਾ)(ਖਾਲੀ *ਤਾਲਾ_ctx);
    ਖਾਲੀ (*unlock)(ਖਾਲੀ *ਤਾਲਾ_ctx);
    ਖਾਲੀ *ਤਾਲਾ_ctx;
} AVAMFDeviceContext;

ਗਿਣਤੀ AMF_ਸਮ੍ਰਿਤੀ_TYPE av_amf_get_ਸਮ੍ਰਿਤੀ_type(AVAMFDeviceContext *amf_ctx);

ਗਿਣਤੀ AMF_SURFACE_FORMAT av_av_ਮੰਜ਼ਿਲ_amf_format(ਗਿਣਤੀ AVPixelFormat fmt);
ਗਿਣਤੀ AVPixelFormat av_amf_ਮੰਜ਼ਿਲ_av_format(ਗਿਣਤੀ AMF_SURFACE_FORMAT fmt);

ਗਿਣਤੀ AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(ਗਿਣਤੀ AVColorRange color_range, ਗਿਣਤੀ AVColorSpace color_space);
ਪੂਰਨ av_amf_display_mastering_meta_ਮੰਜ਼ਿਲ_hdrmeta(ਅਚਲ AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
ਪੂਰਨ av_amf_light_metadata_ਮੰਜ਼ਿਲ_hdrmeta(ਅਚਲ AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
ਪੂਰਨ av_amf_ਕੱਢੋ_hdr_metadata(ਅਚਲ AVFrame *ਚੌਖਟਾ, AMFHDRMetadata *hdrmeta);
ਪੂਰਨ av_amf_attach_hdr_metadata(AVFrame *ਚੌਖਟਾ, ਅਚਲ AMFHDRMetadata *hdrmeta);

#ਜੇ_ਅੰਤ /* AVUTIL_HWCONTEXT_AMF_H */
