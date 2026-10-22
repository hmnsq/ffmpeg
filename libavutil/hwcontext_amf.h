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

#അന്തര്ഭാവ "pixfmt.h"
#അന്തര്ഭാവ "hwcontext.h"
#അന്തര്ഭാവ <AMF/core/Factory.h>
#അന്തര്ഭാവ <AMF/core/Context.h>
#അന്തര്ഭാവ <AMF/core/Trace.h>
#അന്തര്ഭാവ <AMF/core/Debug.h>
#അന്തര്ഭാവ <AMF/components/ColorSpace.h>
#അന്തര്ഭാവ "libavutil/mastering_display_metadata.h"

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
തരനിർവചനം ഘടന AVAMFDeviceContext {
    ശൂന്യം *              library;
    AMFFactory         *factory;
    ശൂന്യം               *trace_writer;

    int64_t             version; ///< version of AMF runtime
    AMFContext         *context;
    AMF_MEMORY_TYPE     memory_type;

    ശൂന്യം (*lock)(ശൂന്യം *lock_ctx);
    ശൂന്യം (*unlock)(ശൂന്യം *lock_ctx);
    ശൂന്യം *lock_ctx;
} AVAMFDeviceContext;

എണ്ണൽ AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx);

എണ്ണൽ AMF_SURFACE_FORMAT av_av_to_amf_format(എണ്ണൽ AVPixelFormat fmt);
എണ്ണൽ AVPixelFormat av_amf_to_av_format(എണ്ണൽ AMF_SURFACE_FORMAT fmt);

എണ്ണൽ AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(എണ്ണൽ AVColorRange color_range, എണ്ണൽ AVColorSpace color_space);
പൂർണ്ണസംഖ്യ av_amf_display_mastering_meta_to_hdrmeta(സ്ഥിരം AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
പൂർണ്ണസംഖ്യ av_amf_light_metadata_to_hdrmeta(സ്ഥിരം AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
പൂർണ്ണസംഖ്യ av_amf_extract_hdr_metadata(സ്ഥിരം AVFrame *frame, AMFHDRMetadata *hdrmeta);
പൂർണ്ണസംഖ്യ av_amf_attach_hdr_metadata(AVFrame *frame, സ്ഥിരം AMFHDRMetadata *hdrmeta);

#endif /* AVUTIL_HWCONTEXT_AMF_H */
