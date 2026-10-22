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


#నిర్వచితం_కాకపోతే AVUTIL_HWCONTEXT_AMF_H
#నిర్వచించు AVUTIL_HWCONTEXT_AMF_H

#అన్తర్భావ "pixfmt.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ <AMF/core/Factory.h>
#అన్తర్భావ <AMF/core/Context.h>
#అన్తర్భావ <AMF/core/Trace.h>
#అన్తర్భావ <AMF/core/Debug.h>
#అన్తర్భావ <AMF/components/ColorSpace.h>
#అన్తర్భావ "libavutil/mastering_display_metadata.h"

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
రకనిర్వచనం నిర్మాణం AVAMFDeviceContext {
    శూన్య *              library;
    AMFFactory         *factory;
    శూన్య               *trace_writer;

    int64_t             సంస్కరణ; ///< version of AMF runtime
    AMFContext         *context;
    AMF_జ్ఞాపకం_TYPE     జ్ఞాపకం_type;

    శూన్య (*తాళం_2)(శూన్య *తాళం_ctx);
    శూన్య (*unlock)(శూన్య *తాళం_ctx);
    శూన్య *తాళం_ctx;
} AVAMFDeviceContext;

గణన AMF_జ్ఞాపకం_TYPE av_amf_get_జ్ఞాపకం_type(AVAMFDeviceContext *amf_ctx);

గణన AMF_SURFACE_FORMAT av_av_గమ్యం_amf_format(గణన AVPixelFormat fmt);
గణన AVPixelFormat av_amf_గమ్యం_av_format(గణన AMF_SURFACE_FORMAT fmt);

గణన AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(గణన AVColorRange color_range, గణన AVColorSpace color_space);
పూర్ణాంకం av_amf_display_mastering_meta_గమ్యం_hdrmeta(స్థిరరాశి AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
పూర్ణాంకం av_amf_light_metadata_గమ్యం_hdrmeta(స్థిరరాశి AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
పూర్ణాంకం av_amf_వెలికితీయి_hdr_metadata(స్థిరరాశి AVFrame *చట్రం, AMFHDRMetadata *hdrmeta);
పూర్ణాంకం av_amf_attach_hdr_metadata(AVFrame *చట్రం, స్థిరరాశి AMFHDRMetadata *hdrmeta);

#అయితే_ముగింపు /* AVUTIL_HWCONTEXT_AMF_H */
