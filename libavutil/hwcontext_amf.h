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


#अगर_अघोषित AVUTIL_HWCONTEXT_AMF_H
#घोषणा AVUTIL_HWCONTEXT_AMF_H

#समावेश "pixfmt.h"
#समावेश "hwcontext.h"
#समावेश <AMF/core/Factory.h>
#समावेश <AMF/core/Context.h>
#समावेश <AMF/core/Trace.h>
#समावेश <AMF/core/Debug.h>
#समावेश <AMF/components/ColorSpace.h>
#समावेश "libavutil/mastering_display_metadata.h"

/**
 * This struct is allocated as AVHWDeviceContext.hwctx
 */
प्रकार काष्ठा AVAMFDeviceContext {
    व्योम *              library;
    AMFFactory         *factory;
    व्योम               *trace_writer;

    int64_t             version; ///< version of AMF runtime
    AMFContext         *context;
    AMF_MEMORY_TYPE     memory_type;

    व्योम (*lock)(व्योम *lock_ctx);
    व्योम (*unlock)(व्योम *lock_ctx);
    व्योम *lock_ctx;
} AVAMFDeviceContext;

क्रमागत AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx);

क्रमागत AMF_SURFACE_FORMAT av_av_to_amf_format(क्रमागत AVPixelFormat fmt);
क्रमागत AVPixelFormat av_amf_to_av_format(क्रमागत AMF_SURFACE_FORMAT fmt);

क्रमागत AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(क्रमागत AVColorRange color_range, क्रमागत AVColorSpace color_space);
पूर्णांक av_amf_display_mastering_meta_to_hdrmeta(स्थिर AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta);
पूर्णांक av_amf_light_metadata_to_hdrmeta(स्थिर AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta);
पूर्णांक av_amf_extract_hdr_metadata(स्थिर AVFrame *frame, AMFHDRMetadata *hdrmeta);
पूर्णांक av_amf_attach_hdr_metadata(AVFrame *frame, स्थिर AMFHDRMetadata *hdrmeta);

#पूर्ण_अगर /* AVUTIL_HWCONTEXT_AMF_H */
