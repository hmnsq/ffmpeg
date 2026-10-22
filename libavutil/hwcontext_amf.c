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

#समावेश "mem.h"
#समावेश "buffer.h"
#समावेश "pixfmt.h"
#समावेश "pixdesc.h"
#समावेश "imgutils.h"
#समावेश "hwcontext.h"
#समावेश "hwcontext_amf.h"
#समावेश "hwcontext_internal.h"
#समावेश "hwcontext_amf_internal.h"

#समावेश "libavutil/thread.h"
#समावेश "libavutil/avassert.h"

#समावेश <AMF/core/Surface.h>
#समावेश <AMF/core/Trace.h>

#अगर CONFIG_VULKAN
#समावेश "hwcontext_vulkan.h"
#पूर्ण_अगर
#अगर CONFIG_D3D11VA
#समावेश "libavutil/hwcontext_d3d11va.h"
#पूर्ण_अगर
#अगर CONFIG_D3D12VA
#समावेश "libavutil/hwcontext_d3d12va.h"
#पूर्ण_अगर
#अगर CONFIG_DXVA2
#घोषणा COBJMACROS
#समावेश "libavutil/hwcontext_dxva2.h"
#पूर्ण_अगर
#अगर_घोषित _WIN32
#समावेश "compat/w32dlfcn.h"
#अन्यथा
#समावेश <dlfcn.h>
#पूर्ण_अगर
#घोषणा FFMPEG_AMF_WRITER_ID L"ffmpeg_amf"

अटल व्योम amf_lock_default(व्योम *opaque)
{
    ff_mutex_lock((AVMutex*)opaque);
}

अटल व्योम amf_unlock_default(व्योम *opaque)
{
    ff_mutex_unlock((AVMutex*)opaque);
}

प्रकार काष्ठा AmfTraceWriter {
    AMFTraceWriterVtbl *vtblp;
    व्योम               *avctx;
    AMFTraceWriterVtbl  vtbl;
} AmfTraceWriter;

अटल व्योम AMF_CDECL_CALL AMFTraceWriter_Write(AMFTraceWriter *pThis,
    स्थिर ब_अक्षर_प्रकार *scope, स्थिर ब_अक्षर_प्रकार *message)
{
    AmfTraceWriter *tracer = (AmfTraceWriter*)pThis;
    av_log(tracer->avctx, AV_LOG_DEBUG, "%ls: %ls", scope, message); // \n is provided from AMF
}

अटल व्योम AMF_CDECL_CALL AMFTraceWriter_Flush(AMFTraceWriter *pThis)
{
}

अटल AmfTraceWriter * amf_writer_alloc(व्योम  *avctx)
{
    AmfTraceWriter * writer = av_mallocz(माप(AmfTraceWriter));
    अगर (!writer)
        वापस शून्य;

    writer->vtblp = &writer->vtbl;
    writer->vtblp->Write = AMFTraceWriter_Write;
    writer->vtblp->Flush = AMFTraceWriter_Flush;
    writer->avctx = avctx;

    वापस writer;
}

अटल व्योम amf_writer_free(व्योम  *opaque)
{
    AmfTraceWriter *writer = (AmfTraceWriter *)opaque;
    av_freep(&writer);
}

/**
 * We still need AVHWFramesContext to utilize our hardware memory
 * otherwise, we will receive the error "HW format requires hw_frames_ctx to be non-NULL".
 * (libavfilter\buffersrc.c function query_formats)
*/
प्रकार काष्ठा {
    व्योम *dummy;
} AMFFramesContext;

प्रकार काष्ठा AVAMFFormatMap {
    क्रमागत AVPixelFormat       av_format;
    क्रमागत AMF_SURFACE_FORMAT  amf_format;
} FormatMap;

स्थिर FormatMap format_map[] =
{
    { AV_PIX_FMT_NONE,          AMF_SURFACE_UNKNOWN },
    { AV_PIX_FMT_NV12,          AMF_SURFACE_NV12 },
    { AV_PIX_FMT_BGR0,          AMF_SURFACE_BGRA },
    { AV_PIX_FMT_RGB0,          AMF_SURFACE_RGBA },
    { AV_PIX_FMT_BGRA,          AMF_SURFACE_BGRA },
    { AV_PIX_FMT_ARGB,          AMF_SURFACE_ARGB },
    { AV_PIX_FMT_RGBA,          AMF_SURFACE_RGBA },
    { AV_PIX_FMT_GRAY8,         AMF_SURFACE_GRAY8 },
    { AV_PIX_FMT_YUV420P,       AMF_SURFACE_YUV420P },
    { AV_PIX_FMT_YUYV422,       AMF_SURFACE_YUY2 },
    { AV_PIX_FMT_P010,          AMF_SURFACE_P010 },
    { AV_PIX_FMT_X2BGR10,       AMF_SURFACE_R10G10B10A2 },
    { AV_PIX_FMT_RGBAF16,       AMF_SURFACE_RGBA_F16},
};

क्रमागत AMF_SURFACE_FORMAT av_av_to_amf_format(क्रमागत AVPixelFormat fmt)
{
    पूर्णांक i;
    क्रम (i = 0; i < amf_countof(format_map); i++) {
        अगर (format_map[i].av_format == fmt) {
            वापस format_map[i].amf_format;
        }
    }
    वापस AMF_SURFACE_UNKNOWN;
}

क्रमागत AVPixelFormat av_amf_to_av_format(क्रमागत AMF_SURFACE_FORMAT fmt)
{
    पूर्णांक i;
    क्रम (i = 0; i < amf_countof(format_map); i++) {
        अगर (format_map[i].amf_format == fmt) {
            वापस format_map[i].av_format;
        }
    }
    वापस AV_PIX_FMT_NONE;
}

क्रमागत AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(क्रमागत AVColorRange color_range, क्रमागत AVColorSpace color_space)
{
    चयन (color_space) {
    हाल AVCOL_SPC_SMPTE170M:
        अगर (color_range == AVCOL_RANGE_JPEG) {
            वापस AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_601;
        } अन्यथा {
            वापस AMF_VIDEO_CONVERTER_COLOR_PROFILE_601;
        }
        अवरोध;
    हाल AVCOL_SPC_BT709:
        अगर (color_range == AVCOL_RANGE_JPEG) {
            वापस AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_709;
        } अन्यथा {
            वापस AMF_VIDEO_CONVERTER_COLOR_PROFILE_709;
        }
        अवरोध;
    हाल AVCOL_SPC_BT2020_NCL:
    हाल AVCOL_SPC_BT2020_CL:
        अगर (color_range == AVCOL_RANGE_JPEG) {
            वापस AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_2020;
        } अन्यथा {
            वापस AMF_VIDEO_CONVERTER_COLOR_PROFILE_2020;
        }
        अवरोध;

    शेष:
        वापस AMF_VIDEO_CONVERTER_COLOR_PROFILE_UNKNOWN;
    }
}

पूर्णांक av_amf_display_mastering_meta_to_hdrmeta(स्थिर AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta)
{
    अगर (!display_meta || !hdrmeta)
        वापस AVERROR(EINVAL);

    अगर (display_meta->has_luminance) {
        स्थिर अचिन्हित पूर्णांक luma_den = 10000;
        hdrmeta->maxMasteringLuminance =
            (amf_uint32)(luma_den * av_q2d(display_meta->max_luminance));
        hdrmeta->minMasteringLuminance =
            FFMIN((amf_uint32)(luma_den * av_q2d(display_meta->min_luminance)), hdrmeta->maxMasteringLuminance);
    }

    अगर (display_meta->has_primaries) {
        स्थिर अचिन्हित पूर्णांक chroma_den = 50000;
        hdrmeta->redPrimary[0] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->display_primaries[0][0])), chroma_den);
        hdrmeta->redPrimary[1] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->display_primaries[0][1])), chroma_den);
        hdrmeta->greenPrimary[0] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->display_primaries[1][0])), chroma_den);
        hdrmeta->greenPrimary[1] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->display_primaries[1][1])), chroma_den);
        hdrmeta->bluePrimary[0] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->display_primaries[2][0])), chroma_den);
        hdrmeta->bluePrimary[1] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->display_primaries[2][1])), chroma_den);
        hdrmeta->whitePoint[0] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_point[0])), chroma_den);
        hdrmeta->whitePoint[1] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_point[1])), chroma_den);
    }

    वापस 0;
}

पूर्णांक av_amf_light_metadata_to_hdrmeta(स्थिर AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta)
{
    अगर (!light_meta || !hdrmeta)
        वापस AVERROR(EINVAL);

    hdrmeta->maxContentLightLevel = (amf_uint16)light_meta->MaxCLL;
    hdrmeta->maxFrameAverageLightLevel = (amf_uint16)light_meta->MaxFALL;

    वापस 0;
}

पूर्णांक av_amf_extract_hdr_metadata(स्थिर AVFrame *frame, AMFHDRMetadata *hdrmeta)
{
    AVFrame_Side_तथ्य *sidedata;
    AVContentLightMetadata *content_light = शून्य;
    AVMasteringDisplayMetadata *mastering_display = शून्य;

    अगर (!frame || !hdrmeta)
        वापस AVERROR(EINVAL);

    sidedata = av_frame_get_side_तथ्य(frame, AV_FRAME_तथ्य_MASTERING_DISPLAY_METADATA);
    अगर (sidedata) {
        mastering_display = (AVMasteringDisplayMetadata *)sidedata->तथ्य;
        अगर (av_amf_display_mastering_meta_to_hdrmeta(mastering_display, hdrmeta) != 0)
            mastering_display = शून्य;
    }

    sidedata = av_frame_get_side_तथ्य(frame, AV_FRAME_तथ्य_CONTENT_LIGHT_LEVEL);
    अगर (sidedata) {
        content_light = (AVContentLightMetadata *)sidedata->तथ्य;
        अगर (av_amf_light_metadata_to_hdrmeta(content_light, hdrmeta) != 0)
            content_light = शून्य;
    }

    अगर (!mastering_display && !content_light)
        वापस AVERROR(ENODATA);

    वापस 0;
}

पूर्णांक av_amf_attach_hdr_metadata(AVFrame *frame, स्थिर AMFHDRMetadata *hdrmeta) {
    अगर (!hdrmeta || !frame)
        वापस AVERROR(EINVAL);

    AVMasteringDisplayMetadata *mastering =
        av_mastering_display_metadata_create_side_तथ्य(frame);
    स्थिर पूर्णांक chroma_den = 50000;
    स्थिर पूर्णांक luma_den = 10000;

    अगर (!mastering)
      वापस AVERROR(ENOMEM);

    mastering->display_primaries[0][0] =
        av_make_q(hdrmeta->redPrimary[0], chroma_den);
    mastering->display_primaries[0][1] =
        av_make_q(hdrmeta->redPrimary[1], chroma_den);

    mastering->display_primaries[1][0] =
        av_make_q(hdrmeta->greenPrimary[0], chroma_den);
    mastering->display_primaries[1][1] =
        av_make_q(hdrmeta->greenPrimary[1], chroma_den);

    mastering->display_primaries[2][0] =
        av_make_q(hdrmeta->bluePrimary[0], chroma_den);
    mastering->display_primaries[2][1] =
        av_make_q(hdrmeta->bluePrimary[1], chroma_den);

    mastering->white_point[0] = av_make_q(hdrmeta->whitePoint[0], chroma_den);
    mastering->white_point[1] = av_make_q(hdrmeta->whitePoint[1], chroma_den);

    mastering->max_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);
    mastering->min_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);

    mastering->has_luminance = 1;
    mastering->has_primaries = 1;
    अगर (hdrmeta->maxContentLightLevel) {
      AVContentLightMetadata *light =
          av_content_light_metadata_create_side_तथ्य(frame);

      अगर (!light)
        वापस AVERROR(ENOMEM);

      light->MaxCLL = hdrmeta->maxContentLightLevel;
      light->MaxFALL = hdrmeta->maxFrameAverageLightLevel;
    }

    वापस 0;
}

अटल स्थिर क्रमागत AVPixelFormat supported_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_BGR0,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
#अगर CONFIG_D3D11VA
    AV_PIX_FMT_D3D11,
#पूर्ण_अगर
#अगर CONFIG_D3D12VA
    AV_PIX_FMT_D3D12,
#पूर्ण_अगर
#अगर CONFIG_DXVA2
    AV_PIX_FMT_DXVA2_VLD,
#पूर्ण_अगर
};

अटल स्थिर क्रमागत AVPixelFormat supported_transfer_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
    AV_PIX_FMT_NONE,
};

अटल पूर्णांक amf_frames_get_constraints(AVHWDeviceContext *ctx,
                                       स्थिर व्योम *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    पूर्णांक i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    माप(*constraints->valid_sw_formats));
    अगर (!constraints->valid_sw_formats)
        वापस AVERROR(ENOMEM);

    क्रम (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, माप(*constraints->valid_hw_formats));
    अगर (!constraints->valid_hw_formats)
        वापस AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_AMF_SURFACE;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    वापस 0;
}

अटल व्योम amf_dummy_free(व्योम *opaque, uint8_t *तथ्य)
{

}

अटल AVBufferRef *amf_pool_alloc(व्योम *opaque, माप_प्रकार आकार)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)opaque;
    AVBufferRef *buf;

    buf = av_बफर_create(शून्य, 0, amf_dummy_free, hwfc, AV_बफर_FLAG_READONLY);
    अगर (!buf) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create buffer for AMF context.\n");
        वापस शून्य;
    }
    वापस buf;
}

अटल पूर्णांक amf_frames_init(AVHWFramesContext *ctx)
{
    पूर्णांक i;

    क्रम (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        अगर (ctx->sw_format == supported_formats[i])
            अवरोध;
    }
    अगर (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        वापस AVERROR(ENOSYS);
    }

    ffhwframesctx(ctx)->pool_internal =
            av_बफर_pool_init2(माप(AMFSurface), ctx,
                                 &amf_pool_alloc, शून्य);

    वापस 0;
}


अटल पूर्णांक amf_get_बफर(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_बफर_pool_get(ctx->pool);
    अगर (!frame->buf[0])
        वापस AVERROR(ENOMEM);

    frame->तथ्य[0] = frame->buf[0]->तथ्य;
    frame->format  = AV_PIX_FMT_AMF_SURFACE;
    frame->width   = ctx->width;
    frame->height  = ctx->height;
    वापस 0;
}

अटल पूर्णांक amf_transfer_get_formats(AVHWFramesContext *ctx,
                                     क्रमागत AVHWFrameTransferDirection dir,
                                     क्रमागत AVPixelFormat **formats)
{
    क्रमागत AVPixelFormat *fmts;
    पूर्णांक i;

    fmts = av_malloc_array(FF_ARRAY_ELEMS(supported_transfer_formats), माप(*fmts));
    अगर (!fmts)
        वापस AVERROR(ENOMEM);
    क्रम (i = 0; i < FF_ARRAY_ELEMS(supported_transfer_formats); i++)
        fmts[i] = supported_transfer_formats[i];

    *formats = fmts;

    वापस 0;
}

अटल व्योम amf_free_amfsurface(व्योम *opaque, uint8_t *तथ्य)
{
    अगर(!!तथ्य){
        AMFSurface *surface = (AMFSurface*)(तथ्य);
        surface->pVtbl->Release(surface);
    }
}

अटल पूर्णांक amf_transfer_तथ्य_to(AVHWFramesContext *ctx, AVFrame *dst,
                                 स्थिर AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)dst->तथ्य[0];
    AMFPlane *plane;
    uint8_t  *dst_तथ्य[4];
    पूर्णांक       dst_linesize[4];
    पूर्णांक       planes;
    पूर्णांक       i;
    पूर्णांक       res;
    पूर्णांक w = FFMIN(dst->width,  src->width);
    पूर्णांक h = FFMIN(dst->height, src->height);

    अगर (dst->hw_frames_ctx->तथ्य != (uint8_t *)ctx || src->format != ctx->sw_format)
        वापस AVERROR(EINVAL);

    अगर (!surface) {
        AVHWDeviceContext   *hwdev_ctx = ctx->device_ctx;
        AVAMFDeviceContext  *amf_device_ctx = (AVAMFDeviceContext *)hwdev_ctx->hwctx;
        AMF_SURFACE_FORMAT  format = av_av_to_amf_format(ctx->sw_format);
        res = amf_device_ctx->context->pVtbl->AllocSurface(amf_device_ctx->context, AMF_MEMORY_HOST, format, dst->width, dst->height, &surface);
        AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR(ENOMEM), "AllocSurface() failed  with error %d\n", res);
        dst->तथ्य[0] = (uint8_t *)surface;
        dst->buf[1] = av_बफर_create((uint8_t *)surface, माप(surface),
                                            amf_free_amfsurface,
                                            शून्य,
                                            AV_बफर_FLAG_READONLY);
    AMF_RETURN_IF_FALSE(ctx, !!dst->buf[1], AVERROR(ENOMEM), "av_buffer_create for amf surface failed.");
    }

    planes = (पूर्णांक)surface->pVtbl->Get_Planes_गिनती(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(dst_तथ्य));

    क्रम (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        dst_तथ्य[i] = plane->pVtbl->GetNative(plane);
        dst_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst_तथ्य, dst_linesize,
                   src->तथ्य, src->linesize, src->format,
                   w, h);

    वापस 0;
}

अटल पूर्णांक amf_transfer_तथ्य_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    स्थिर AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)src->तथ्य[0];
    AMFPlane *plane;
    uint8_t  *src_तथ्य[4];
    पूर्णांक       src_linesize[4];
    पूर्णांक       planes;
    पूर्णांक       i;
    पूर्णांक w = FFMIN(dst->width,  src->width);
    पूर्णांक h = FFMIN(dst->height, src->height);
    पूर्णांक ret;

    अगर (src->hw_frames_ctx->तथ्य != (uint8_t *)ctx || dst->format != ctx->sw_format)
        वापस AVERROR(EINVAL);

    ret = surface->pVtbl->Convert(surface, AMF_MEMORY_HOST);
    AMF_RETURN_IF_FALSE(ctx, ret == AMF_OK, AVERROR_UNKNOWN, "Convert(amf::AMF_MEMORY_HOST) failed with error %d\n", AVERROR_UNKNOWN);

    planes = (पूर्णांक)surface->pVtbl->Get_Planes_गिनती(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(src_तथ्य));

    क्रम (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        src_तथ्य[i] = plane->pVtbl->GetNative(plane);
        src_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst->तथ्य, dst->linesize,
                   src_तथ्य, src_linesize, dst->format,
                   w, h);
    वापस 0;
}



अटल व्योम amf_device_uninit(AVHWDeviceContext *device_ctx)
{
    AVAMFDeviceContext *amf_ctx = device_ctx->hwctx;
    AMF_परिणाम          res = AMF_NOT_INITIALIZED;
    AMFTrace           *trace;

    अगर (amf_ctx->context) {
        amf_ctx->context->pVtbl->Terminate(amf_ctx->context);
        amf_ctx->context->pVtbl->Release(amf_ctx->context);
        amf_ctx->context = शून्य;
    }

    अगर (amf_ctx->factory)
        res = amf_ctx->factory->pVtbl->GetTrace(amf_ctx->factory, &trace);

    अगर (res == AMF_OK) {
        trace->pVtbl->UnregisterWriter(trace, FFMPEG_AMF_WRITER_ID);
    }

    अगर(amf_ctx->library) {
        dlclose(amf_ctx->library);
        amf_ctx->library = शून्य;
    }
    अगर (amf_ctx->trace_writer) {
        amf_writer_free(amf_ctx->trace_writer);
    }

    अगर (amf_ctx->lock_ctx == amf_lock_default) {
        ff_mutex_destroy((AVMutex*)amf_ctx->lock_ctx);
        av_freep(&amf_ctx->lock_ctx);
        amf_ctx->lock = शून्य;
        amf_ctx->unlock = शून्य;
    }

    amf_ctx->version = 0;
}

क्रमागत AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx)
{
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = शून्य;
    AMFGuid guid1 = IID_AMFContext1();
    व्योम * device = शून्य;

#अगर_घोषित _WIN32
    // At the moment used only for DX12.
    AMFContext2 *context2 = शून्य;

    /*
    Work around the incorrect C Context2 IID in unpatched AMF 1.5.2 headers;
    mostly pedantic fix as it works as it is in practice.
    TODO: replace with AMFGuid guid2 = IID_AMFContext2()
    once AMF 1.5.3 is available to public and marked as required version in ffmpeg.
    */
    अटल स्थिर AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#पूर्ण_अगर

    अगर (!amf_ctx)
        वापस AMF_MEMORY_UNKNOWN;

#अगर_घोषित _WIN32
    अगर (AMF_IFACE_CALL(context, QueryInterface, &guid2, (व्योम**)&context2) == AMF_OK)
    {
        device = AMF_IFACE_CALL(context2, GetDX12Device, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);

        अगर (device)
            वापस AMF_MEMORY_DX12;
    }

    अगर (AMF_IFACE_CALL(context, GetDX11Device, AMF_DX11_1))
        वापस AMF_MEMORY_DX11;

    अगर (AMF_IFACE_CALL(context, GetDX9Device, AMF_DX9))
        वापस AMF_MEMORY_DX9;
#पूर्ण_अगर

    अगर (AMF_IFACE_CALL(context, QueryInterface, &guid1, (व्योम**)&context1) != AMF_OK)
        वापस AMF_MEMORY_UNKNOWN;

    device = AMF_IFACE_CALL(context1, GetVulkanDevice);
    AMF_IFACE_CALL(context1, Release);
    अगर (device)
        वापस AMF_MEMORY_VULKAN;

    वापस AMF_MEMORY_UNKNOWN;
}

अटल पूर्णांक amf_device_init(AVHWDeviceContext *ctx)
{
    AVAMFDeviceContext *amf_ctx = ctx->hwctx;
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = शून्य;
    AMFGuid guid1 = IID_AMFContext1();
    AMF_परिणाम res;

#अगर_घोषित _WIN32
    AMFContext2 *context2 = शून्य;
    अटल स्थिर AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#पूर्ण_अगर

    अगर (!amf_ctx->lock) {
        amf_ctx->lock_ctx = av_mallocz(माप(AVMutex));
        अगर (!amf_ctx->lock_ctx) {
            वापस AVERROR(ENOMEM);
        }
        ff_mutex_init((AVMutex*)amf_ctx->lock_ctx, शून्य);
        amf_ctx->lock   = amf_lock_default;
        amf_ctx->unlock = amf_unlock_default;
    }

    अगर (av_amf_get_memory_type(amf_ctx) != AMF_MEMORY_UNKNOWN) {
        av_log(ctx, AV_LOG_VERBOSE, "AMF is already initialized, skipping init.\n");
        वापस 0;
    }

#अगर_घोषित _WIN32
    res = AMF_IFACE_CALL(context, InitDX11, शून्य, AMF_DX11_1);
    अगर (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D11.\n");
        वापस 0;
    }

    res = AMF_IFACE_CALL(context, QueryInterface, &guid2, (व्योम**)&context2);
    अगर (res == AMF_OK) {
        res = AMF_IFACE_CALL(context2, InitDX12, शून्य, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);
        अगर (res == AMF_OK) {
            av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D12.\n");
            वापस 0;
        }
    } अन्यथा {
        av_log(ctx, AV_LOG_VERBOSE, "QueryInterface(AMFContext2) failed with error %d, trying older D3D APIs...\n", res);
    }

    res = AMF_IFACE_CALL(context, InitDX9, शून्य);
    अगर (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D9.\n");
        वापस 0;
    }

    av_log(ctx, AV_LOG_WARNING, "AMF failed to initialize with any of supported versions of DirectX, trying Vulkan instead...\n");
#पूर्ण_अगर

    res = AMF_IFACE_CALL(context, QueryInterface, &guid1, (व्योम**)&context1);
    अगर (res != AMF_OK) {
        av_log(ctx, AV_LOG_ERROR, "QueryInterface(AMFContext1) failed with error %d\n", res);
        वापस AVERROR_UNKNOWN;
    }

    res = AMF_IFACE_CALL(context1, InitVulkan, शून्य);
    AMF_IFACE_CALL(context1, Release);

    अगर (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via Vulkan.\n");
    } अन्यथा {
        अगर (res == AMF_NOT_SUPPORTED)
            av_log(ctx, AV_LOG_ERROR, "AMF via Vulkan is not supported on the given device.\n");
        अन्यथा
            av_log(ctx, AV_LOG_ERROR, "Failed to initialize AMF via Vulkan, error %d\n", res);

        वापस AVERROR(ENOSYS);
    }

    वापस 0;
}

अटल पूर्णांक amf_load_library(AVAMFDeviceContext* amf_ctx,  व्योम* avcl)
{
    AMFInit_Fn         init_fun;
    AMFQueryVersion_Fn version_fun;
    AMF_परिणाम         res;

    amf_ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(avcl, amf_ctx->library != शून्य,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(amf_ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, init_fun != शून्य, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    version_fun = (AMFQueryVersion_Fn)dlsym(amf_ctx->library, AMF_QUERY_VERSION_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, version_fun != शून्य, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_VERSION_FUNCTION_NAME);

    amf_uint64 version;
    res = version_fun(&version);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_VERSION_FUNCTION_NAME, res);
    amf_ctx->version = version;
    res = init_fun(AMF_FULL_VERSION, &amf_ctx->factory);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_INIT_FUNCTION_NAME, res);
    वापस 0;
}

अटल पूर्णांक amf_device_create(AVHWDeviceContext *device_ctx,
                              स्थिर अक्षर *device,
                              AVDictionary *opts, पूर्णांक flags)
{
    AVAMFDeviceContext        *ctx = device_ctx->hwctx;
    AMFTrace           *trace;
    पूर्णांक ret;
    अगर ((ret = amf_load_library(ctx, device_ctx)) == 0) {
        ret = ctx->factory->pVtbl->GetTrace(ctx->factory, &trace);
        अगर (ret == AMF_OK) {
            पूर्णांक level_ff = av_log_get_level();
            पूर्णांक level_amf = AMF_TRACE_TRACE;
            amf_bool enable_log = true;
            चयन(level_ff)
            {
            हाल AV_LOG_QUIET:
                level_amf = AMF_TRACE_ERROR;
                enable_log = false;
                अवरोध;
            हाल AV_LOG_PANIC:
            हाल AV_LOG_FATAL:
            हाल AV_LOG_ERROR:
                level_amf = AMF_TRACE_ERROR;
                अवरोध;
            हाल AV_LOG_WARNING:
            हाल AV_LOG_INFO:
                level_amf = AMF_TRACE_WARNING;
                अवरोध;
            हाल AV_LOG_VERBOSE:
                level_amf = AMF_TRACE_INFO;
                अवरोध;
            हाल AV_LOG_DEBUG:
                level_amf = AMF_TRACE_DEBUG;
                अवरोध;
            हाल AV_LOG_TRACE:
                level_amf = AMF_TRACE_TRACE;
                अवरोध;
            }
            अगर(ctx->version == AMF_MAKE_FULL_VERSION(1, 4, 35, 0)){// get around a bug in trace in AMF runtime driver 24.20
                level_amf = AMF_TRACE_WARNING;
            }

            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_CONSOLE, 0);
            trace->pVtbl->SetGlobalLevel(trace, level_amf);

            // connect AMF logger to av_log
            ctx->trace_writer = amf_writer_alloc(device_ctx);
            trace->pVtbl->RegisterWriter(trace, FFMPEG_AMF_WRITER_ID, (AMFTraceWriter*)ctx->trace_writer, 1);
            trace->pVtbl->SetWriterLevel(trace, FFMPEG_AMF_WRITER_ID, level_amf);
            trace->pVtbl->EnableWriter(trace, FFMPEG_AMF_WRITER_ID, enable_log);
            trace->pVtbl->SetWriterLevel(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, level_amf);
            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, enable_log);
        }


        ret = ctx->factory->pVtbl->CreateContext(ctx->factory, &ctx->context);
        अगर (ret == AMF_OK) {
            AMF_ASSIGN_PROPERTY_INT64(ret, ctx->context, L"DeviceSurfaceCacheSize", 50 );
            वापस 0;
        }
        av_log(device_ctx, AV_LOG_ERROR, "CreateContext() failed with error %d.\n", ret);
    }
    amf_device_uninit(device_ctx);
    वापस ret;
}

#अगर CONFIG_DXVA2
अटल पूर्णांक amf_init_from_dxva2_device(AVAMFDeviceContext * amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVDXVA2DeviceContext *hwctx = child_device_ctx->hwctx;
    IDirect3DDevice9    *device;
    HANDLE              device_handle;
    HRESULT             hr;
    AMF_परिणाम          res;
    पूर्णांक ret;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &device_handle);
    अगर (FAILED(hr)) {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to open device handle for Direct3D9 device: %lx.\n", (अचिन्हित दीर्घ)hr);
        वापस AVERROR_EXTERNAL;
    }

    hr = IDirect3DDeviceManager9_LockDevice(hwctx->devmgr, device_handle, &device, FALSE);
    अगर (SUCCEEDED(hr)) {
        IDirect3DDeviceManager9_UnlockDevice(hwctx->devmgr, device_handle, FALSE);
        ret = 0;
    } अन्यथा {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to lock device handle for Direct3D9 device: %lx.\n", (अचिन्हित दीर्घ)hr);
        ret = AVERROR_EXTERNAL;
    }


    IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, device_handle);

    अगर (ret < 0)
        वापस ret;

    res = amf_ctx->context->pVtbl->InitDX9(amf_ctx->context, device);

    IDirect3DDevice9_Release(device);

    अगर (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        अगर (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D9 is not supported on the given device.\n");
        अन्यथा
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on given D3D9 device: %d.\n", res);
        वापस AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via DXVA2.\n");
    वापस 0;
}
#पूर्ण_अगर

#अगर CONFIG_D3D11VA
अटल पूर्णांक amf_init_from_d3d11_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AMF_परिणाम res;
    AVD3D11VADeviceContext *hwctx = child_device_ctx->hwctx;
    res = amf_ctx->context->pVtbl->InitDX11(amf_ctx->context, hwctx->device, AMF_DX11_1);
    अगर (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        अगर (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D11 is not supported on the given device.\n");
        अन्यथा
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D11 device: %d.\n", res);
        वापस AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D11.\n");
    hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    वापस 0;
}
#पूर्ण_अगर

#अगर CONFIG_D3D12VA
अटल पूर्णांक amf_init_from_d3d12_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVD3D12VADeviceContext *hwctx = child_device_ctx->hwctx;
    AMF_परिणाम res;
    AMFContext2 *context2 = शून्य;
    AMFGuid guid = IID_AMFContext2();
    res = amf_ctx->context->pVtbl->QueryInterface(amf_ctx->context, &guid, (व्योम**)&context2);
    AMF_RETURN_IF_FALSE(child_device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "CreateContext2() failed with error %d\n", res);
    res = context2->pVtbl->InitDX12(context2, hwctx->device, AMF_DX12);
    context2->pVtbl->Release(context2);
    अगर (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        अगर (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D12 is not supported on the given device.\n");
        अन्यथा
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D12 device: %d.\n", res);
        वापस AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D12.\n");
    वापस 0;
}
#पूर्ण_अगर


अटल पूर्णांक amf_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *child_device_ctx, AVDictionary *opts,
                              पूर्णांक flags)
{
#अगर CONFIG_DXVA2 || CONFIG_D3D11VA || CONFIG_D3D12VA
    AVAMFDeviceContext        *amf_ctx = device_ctx->hwctx;
#पूर्ण_अगर
    पूर्णांक ret;

    ret = amf_device_create(device_ctx, "", opts, flags);
    अगर(ret < 0)
        वापस ret;

    चयन (child_device_ctx->type) {
#अगर CONFIG_DXVA2
    हाल AV_HWDEVICE_TYPE_DXVA2:
        वापस amf_init_from_dxva2_device(amf_ctx, child_device_ctx);
#पूर्ण_अगर
#अगर CONFIG_D3D11VA
    हाल AV_HWDEVICE_TYPE_D3D11VA:
        वापस amf_init_from_d3d11_device(amf_ctx, child_device_ctx);
#पूर्ण_अगर
#अगर CONFIG_D3D12VA
    हाल AV_HWDEVICE_TYPE_D3D12VA:
        वापस amf_init_from_d3d12_device(amf_ctx, child_device_ctx);
#पूर्ण_अगर
    शेष:
        av_log(child_device_ctx, AV_LOG_ERROR, "AMF initialisation from a %s device is not supported.\n",
               av_hwdevice_get_type_name(child_device_ctx->type));
        वापस AVERROR(ENOSYS);
    }
}

अटल व्योम amf_unmap_frame(av_unused AVHWFramesContext *unused, HWMapDescriptor *hwmap)
{
    AMFSurface1 *surface1 = hwmap->priv;
    AMF_IFACE_CALL(surface1, Unmap);
    AMF_IFACE_CALL(surface1, Release);
}

अटल पूर्णांक amf_map_frame(AVHWFramesContext *device_ctx, AVFrame *dst, स्थिर AVFrame *src, पूर्णांक flags)
{
    AMFSurface *surface = (AMFSurface *)src->तथ्य[0];
    AMFSurface1 *surface1 = शून्य;
    माप_प्रकार *linesizes = शून्य;
    uint8_t **map = शून्य;
    पूर्णांक amf_mem_flags = AMF_MEMORY_CPU_NONE;
    स्थिर AMFGuid guid = IID_AMFSurface1();
    AMF_परिणाम res = AMF_FAIL;
    माप_प्रकार plane_गिनती = 0;
    पूर्णांक ret = -1;

    AMF_RETURN_IF_FALSE(device_ctx, surface != शून्य, AVERROR(EINVAL) , "Source surface is null");

    res = AMF_IFACE_CALL(surface, QueryInterface, &guid, (व्योम**)&surface1);
    AMF_RETURN_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "QueryInterface(AMFSurface1) failed with error %d\n", res);

    अगर (flags & AV_HWFRAME_MAP_READ)
        amf_mem_flags |= AMF_MEMORY_CPU_READ;

    अगर (flags & AV_HWFRAME_MAP_WRITE)
        amf_mem_flags |= AMF_MEMORY_CPU_WRITE;

    plane_गिनती = AMF_IFACE_CALL(surface, Get_Planes_गिनती);
    linesizes = av_malloc_array(माप(माप_प्रकार), plane_गिनती);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, linesizes, AVERROR(ENOMEM), "Unable to allocate line sizes array\n");

    map = av_malloc_array(माप(uint8_t *), plane_गिनती);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, map, AVERROR(ENOMEM), "Unable to allocate mapping buffer\n");

    dst->format = av_amf_to_av_format(AMF_IFACE_CALL(surface, GetFormat));

    res = AMF_IFACE_CALL(surface1, Map, amf_mem_flags, plane_गिनती, linesizes, (व्योम**)map);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "AMFSurface1->Map() failed with error %d\n", res);

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, &amf_unmap_frame, surface1);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, ret >= 0, ret, "ff_hwframe_map_create failed with error %d\n", ret);

    dst->width  = src->width;
    dst->height = src->height;
    av_frame_copy_props(dst, src);

    // The dst frame is no longer a hardware frame, from the perspective of any dst frame consumer.
    av_बफर_unref(&dst->hw_frames_ctx);

    क्रम (पूर्णांक plane = 0; plane < plane_गिनती; ++plane)
    {
        dst->तथ्य[plane] = map[plane];
        dst->linesize[plane] = linesizes[plane];
    }

fail:
    अगर (map)
        av_free(map);

    अगर (linesizes)
        av_free(linesizes);

    अगर (ret < 0 && surface1 != शून्य)
        AMF_IFACE_CALL(surface1, Release);

    वापस ret;
}

स्थिर HWContextType ff_hwcontext_type_amf = {
    .type                 = AV_HWDEVICE_TYPE_AMF,
    .name                 = "AMF",

    .device_hwctx_आकार    = माप(AVAMFDeviceContext),
    .frames_hwctx_आकार    = माप(AMFFramesContext),

    .device_create        = amf_device_create,
    .device_derive        = amf_device_derive,
    .device_init          = amf_device_init,
    .device_uninit        = amf_device_uninit,
    .frames_get_constraints = amf_frames_get_constraints,
    .frames_init          = amf_frames_init,
    .frames_get_बफर    = amf_get_बफर,
    .transfer_get_formats = amf_transfer_get_formats,
    .transfer_तथ्य_to     = amf_transfer_तथ्य_to,
    .transfer_तथ्य_from   = amf_transfer_तथ्य_from,
    .map_from             = amf_map_frame,

    .pix_fmts             = (स्थिर क्रमागत AVPixelFormat[]){ AV_PIX_FMT_AMF_SURFACE, AV_PIX_FMT_NONE },
};
