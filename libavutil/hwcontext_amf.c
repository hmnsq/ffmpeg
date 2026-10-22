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

#अन्तर्भाव "mem.h"
#अन्तर्भाव "buffer.h"
#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "imgutils.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_amf.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "hwcontext_amf_internal.h"

#अन्तर्भाव "libavutil/thread.h"
#अन्तर्भाव "libavutil/avassert.h"

#अन्तर्भाव <AMF/core/Surface.h>
#अन्तर्भाव <AMF/core/Trace.h>

#सचे CONFIG_VULKAN
#अन्तर्भाव "hwcontext_vulkan.h"
#endif
#सचे CONFIG_D3D11VA
#अन्तर्भाव "libavutil/hwcontext_d3d11va.h"
#endif
#सचे CONFIG_D3D12VA
#अन्तर्भाव "libavutil/hwcontext_d3d12va.h"
#endif
#सचे CONFIG_DXVA2
#define COBJMACROS
#अन्तर्भाव "libavutil/hwcontext_dxva2.h"
#endif
#ifdef _WIN32
#अन्तर्भाव "compat/w32dlfcn.h"
#अञ्ञथा
#अन्तर्भाव <dlfcn.h>
#endif
#define FFMPEG_AMF_WRITER_ID L"ffmpeg_amf"

स्थिर शून्य amf_lock_default(शून्य *opaque)
{
    ff_mutex_lock((AVMutex*)opaque);
}

स्थिर शून्य amf_unlock_default(शून्य *opaque)
{
    ff_mutex_unlock((AVMutex*)opaque);
}

प्रकारनिर्देश संरचना AmfTraceWriter {
    AMFTraceWriterVtbl *vtblp;
    शून्य               *avctx;
    AMFTraceWriterVtbl  vtbl;
} AmfTraceWriter;

स्थिर शून्य AMF_CDECL_CALL AMFTraceWriter_Write(AMFTraceWriter *pThis,
    ध्रुव wchar_t *scope, ध्रुव wchar_t *message)
{
    AmfTraceWriter *tracer = (AmfTraceWriter*)pThis;
    av_log(tracer->avctx, AV_LOG_DEBUG, "%ls: %ls", scope, message); // \n is provided from AMF
}

स्थिर शून्य AMF_CDECL_CALL AMFTraceWriter_Flush(AMFTraceWriter *pThis)
{
}

स्थिर AmfTraceWriter * amf_writer_alloc(शून्य  *avctx)
{
    AmfTraceWriter * writer = av_mallocz(परिमाण(AmfTraceWriter));
    सचे (!writer)
        पटिनिवत्त रिक्त;

    writer->vtblp = &writer->vtbl;
    writer->vtblp->Write = AMFTraceWriter_Write;
    writer->vtblp->Flush = AMFTraceWriter_Flush;
    writer->avctx = avctx;

    पटिनिवत्त writer;
}

स्थिर शून्य amf_writer_free(शून्य  *opaque)
{
    AmfTraceWriter *writer = (AmfTraceWriter *)opaque;
    av_freep(&writer);
}

/**
 * We still need AVHWFramesContext to utilize our hardware memory
 * otherwise, we will receive the error "HW format requires hw_frames_ctx to be non-NULL".
 * (libavfilter\buffersrc.c function query_formats)
*/
प्रकारनिर्देश संरचना {
    शून्य *dummy;
} AMFFramesContext;

प्रकारनिर्देश संरचना AVAMFFormatMap {
    गणना AVPixelFormat       av_format;
    गणना AMF_SURFACE_FORMAT  amf_format;
} FormatMap;

ध्रुव FormatMap format_map[] =
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

गणना AMF_SURFACE_FORMAT av_av_to_amf_format(गणना AVPixelFormat fmt)
{
    पूर्णाङ्क i;
    अत्थाय (i = 0; i < amf_countof(format_map); i++) {
        सचे (format_map[i].av_format == fmt) {
            पटिनिवत्त format_map[i].amf_format;
        }
    }
    पटिनिवत्त AMF_SURFACE_UNKNOWN;
}

गणना AVPixelFormat av_amf_to_av_format(गणना AMF_SURFACE_FORMAT fmt)
{
    पूर्णाङ्क i;
    अत्थाय (i = 0; i < amf_countof(format_map); i++) {
        सचे (format_map[i].amf_format == fmt) {
            पटिनिवत्त format_map[i].av_format;
        }
    }
    पटिनिवत्त AV_PIX_FMT_NONE;
}

गणना AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(गणना AVColorRange color_range, गणना AVColorSpace color_space)
{
    विकल्प (color_space) {
    पक्ष AVCOL_SPC_SMPTE170M:
        सचे (color_range == AVCOL_RANGE_JPEG) {
            पटिनिवत्त AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_601;
        } अञ्ञथा {
            पटिनिवत्त AMF_VIDEO_CONVERTER_COLOR_PROFILE_601;
        }
        भङ्ग;
    पक्ष AVCOL_SPC_BT709:
        सचे (color_range == AVCOL_RANGE_JPEG) {
            पटिनिवत्त AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_709;
        } अञ्ञथा {
            पटिनिवत्त AMF_VIDEO_CONVERTER_COLOR_PROFILE_709;
        }
        भङ्ग;
    पक्ष AVCOL_SPC_BT2020_NCL:
    पक्ष AVCOL_SPC_BT2020_CL:
        सचे (color_range == AVCOL_RANGE_JPEG) {
            पटिनिवत्त AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_2020;
        } अञ्ञथा {
            पटिनिवत्त AMF_VIDEO_CONVERTER_COLOR_PROFILE_2020;
        }
        भङ्ग;

    स्वभाव:
        पटिनिवत्त AMF_VIDEO_CONVERTER_COLOR_PROFILE_UNKNOWN;
    }
}

पूर्णाङ्क av_amf_display_mastering_meta_to_hdrmeta(ध्रुव AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta)
{
    सचे (!display_meta || !hdrmeta)
        पटिनिवत्त AVERROR(EINVAL);

    सचे (display_meta->has_luminance) {
        ध्रुव unsigned पूर्णाङ्क luma_den = 10000;
        hdrmeta->maxMasteringLuminance =
            (amf_uint32)(luma_den * av_q2d(display_meta->max_luminance));
        hdrmeta->minMasteringLuminance =
            FFMIN((amf_uint32)(luma_den * av_q2d(display_meta->min_luminance)), hdrmeta->maxMasteringLuminance);
    }

    सचे (display_meta->has_primaries) {
        ध्रुव unsigned पूर्णाङ्क chroma_den = 50000;
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

    पटिनिवत्त 0;
}

पूर्णाङ्क av_amf_light_metadata_to_hdrmeta(ध्रुव AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta)
{
    सचे (!light_meta || !hdrmeta)
        पटिनिवत्त AVERROR(EINVAL);

    hdrmeta->maxContentLightLevel = (amf_uint16)light_meta->MaxCLL;
    hdrmeta->maxFrameAverageLightLevel = (amf_uint16)light_meta->MaxFALL;

    पटिनिवत्त 0;
}

पूर्णाङ्क av_amf_extract_hdr_metadata(ध्रुव AVFrame *frame, AMFHDRMetadata *hdrmeta)
{
    AVFrameSideData *sidedata;
    AVContentLightMetadata *content_light = रिक्त;
    AVMasteringDisplayMetadata *mastering_display = रिक्त;

    सचे (!frame || !hdrmeta)
        पटिनिवत्त AVERROR(EINVAL);

    sidedata = av_frame_get_side_data(frame, AV_FRAME_DATA_MASTERING_DISPLAY_METADATA);
    सचे (sidedata) {
        mastering_display = (AVMasteringDisplayMetadata *)sidedata->data;
        सचे (av_amf_display_mastering_meta_to_hdrmeta(mastering_display, hdrmeta) != 0)
            mastering_display = रिक्त;
    }

    sidedata = av_frame_get_side_data(frame, AV_FRAME_DATA_CONTENT_LIGHT_LEVEL);
    सचे (sidedata) {
        content_light = (AVContentLightMetadata *)sidedata->data;
        सचे (av_amf_light_metadata_to_hdrmeta(content_light, hdrmeta) != 0)
            content_light = रिक्त;
    }

    सचे (!mastering_display && !content_light)
        पटिनिवत्त AVERROR(ENODATA);

    पटिनिवत्त 0;
}

पूर्णाङ्क av_amf_attach_hdr_metadata(AVFrame *frame, ध्रुव AMFHDRMetadata *hdrmeta) {
    सचे (!hdrmeta || !frame)
        पटिनिवत्त AVERROR(EINVAL);

    AVMasteringDisplayMetadata *mastering =
        av_mastering_display_metadata_create_side_data(frame);
    ध्रुव पूर्णाङ्क chroma_den = 50000;
    ध्रुव पूर्णाङ्क luma_den = 10000;

    सचे (!mastering)
      पटिनिवत्त AVERROR(ENOMEM);

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
    सचे (hdrmeta->maxContentLightLevel) {
      AVContentLightMetadata *light =
          av_content_light_metadata_create_side_data(frame);

      सचे (!light)
        पटिनिवत्त AVERROR(ENOMEM);

      light->MaxCLL = hdrmeta->maxContentLightLevel;
      light->MaxFALL = hdrmeta->maxFrameAverageLightLevel;
    }

    पटिनिवत्त 0;
}

स्थिर ध्रुव गणना AVPixelFormat supported_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_BGR0,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
#सचे CONFIG_D3D11VA
    AV_PIX_FMT_D3D11,
#endif
#सचे CONFIG_D3D12VA
    AV_PIX_FMT_D3D12,
#endif
#सचे CONFIG_DXVA2
    AV_PIX_FMT_DXVA2_VLD,
#endif
};

स्थिर ध्रुव गणना AVPixelFormat supported_transfer_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
    AV_PIX_FMT_NONE,
};

स्थिर पूर्णाङ्क amf_frames_get_constraints(AVHWDeviceContext *ctx,
                                       ध्रुव शून्य *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    पूर्णाङ्क i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    परिमाण(*constraints->valid_sw_formats));
    सचे (!constraints->valid_sw_formats)
        पटिनिवत्त AVERROR(ENOMEM);

    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, परिमाण(*constraints->valid_hw_formats));
    सचे (!constraints->valid_hw_formats)
        पटिनिवत्त AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_AMF_SURFACE;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    पटिनिवत्त 0;
}

स्थिर शून्य amf_dummy_free(शून्य *opaque, uint8_t *data)
{

}

स्थिर AVBufferRef *amf_pool_alloc(शून्य *opaque, size_t size)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)opaque;
    AVBufferRef *buf;

    buf = av_buffer_create(रिक्त, 0, amf_dummy_free, hwfc, AV_BUFFER_FLAG_READONLY);
    सचे (!buf) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create buffer for AMF context.\n");
        पटिनिवत्त रिक्त;
    }
    पटिनिवत्त buf;
}

स्थिर पूर्णाङ्क amf_frames_init(AVHWFramesContext *ctx)
{
    पूर्णाङ्क i;

    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        सचे (ctx->sw_format == supported_formats[i])
            भङ्ग;
    }
    सचे (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        पटिनिवत्त AVERROR(ENOSYS);
    }

    ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(परिमाण(AMFSurface), ctx,
                                 &amf_pool_alloc, रिक्त);

    पटिनिवत्त 0;
}


स्थिर पूर्णाङ्क amf_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    सचे (!frame->buf[0])
        पटिनिवत्त AVERROR(ENOMEM);

    frame->data[0] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_AMF_SURFACE;
    frame->width   = ctx->width;
    frame->height  = ctx->height;
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क amf_transfer_get_formats(AVHWFramesContext *ctx,
                                     गणना AVHWFrameTransferDirection dir,
                                     गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts;
    पूर्णाङ्क i;

    fmts = av_malloc_array(FF_ARRAY_ELEMS(supported_transfer_formats), परिमाण(*fmts));
    सचे (!fmts)
        पटिनिवत्त AVERROR(ENOMEM);
    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(supported_transfer_formats); i++)
        fmts[i] = supported_transfer_formats[i];

    *formats = fmts;

    पटिनिवत्त 0;
}

स्थिर शून्य amf_free_amfsurface(शून्य *opaque, uint8_t *data)
{
    सचे(!!data){
        AMFSurface *surface = (AMFSurface*)(data);
        surface->pVtbl->Release(surface);
    }
}

स्थिर पूर्णाङ्क amf_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                 ध्रुव AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)dst->data[0];
    AMFPlane *plane;
    uint8_t  *dst_data[4];
    पूर्णाङ्क       dst_linesize[4];
    पूर्णाङ्क       planes;
    पूर्णाङ्क       i;
    पूर्णाङ्क       res;
    पूर्णाङ्क w = FFMIN(dst->width,  src->width);
    पूर्णाङ्क h = FFMIN(dst->height, src->height);

    सचे (dst->hw_frames_ctx->data != (uint8_t *)ctx || src->format != ctx->sw_format)
        पटिनिवत्त AVERROR(EINVAL);

    सचे (!surface) {
        AVHWDeviceContext   *hwdev_ctx = ctx->device_ctx;
        AVAMFDeviceContext  *amf_device_ctx = (AVAMFDeviceContext *)hwdev_ctx->hwctx;
        AMF_SURFACE_FORMAT  format = av_av_to_amf_format(ctx->sw_format);
        res = amf_device_ctx->context->pVtbl->AllocSurface(amf_device_ctx->context, AMF_MEMORY_HOST, format, dst->width, dst->height, &surface);
        AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR(ENOMEM), "AllocSurface() failed  with error %d\n", res);
        dst->data[0] = (uint8_t *)surface;
        dst->buf[1] = av_buffer_create((uint8_t *)surface, परिमाण(surface),
                                            amf_free_amfsurface,
                                            रिक्त,
                                            AV_BUFFER_FLAG_READONLY);
    AMF_RETURN_IF_FALSE(ctx, !!dst->buf[1], AVERROR(ENOMEM), "av_buffer_create for amf surface failed.");
    }

    planes = (पूर्णाङ्क)surface->pVtbl->Get_Planes_गणनम्(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(dst_data));

    अत्थाय (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        dst_data[i] = plane->pVtbl->GetNative(plane);
        dst_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst_data, dst_linesize,
                   src->data, src->linesize, src->format,
                   w, h);

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क amf_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ध्रुव AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)src->data[0];
    AMFPlane *plane;
    uint8_t  *src_data[4];
    पूर्णाङ्क       src_linesize[4];
    पूर्णाङ्क       planes;
    पूर्णाङ्क       i;
    पूर्णाङ्क w = FFMIN(dst->width,  src->width);
    पूर्णाङ्क h = FFMIN(dst->height, src->height);
    पूर्णाङ्क ret;

    सचे (src->hw_frames_ctx->data != (uint8_t *)ctx || dst->format != ctx->sw_format)
        पटिनिवत्त AVERROR(EINVAL);

    ret = surface->pVtbl->Convert(surface, AMF_MEMORY_HOST);
    AMF_RETURN_IF_FALSE(ctx, ret == AMF_OK, AVERROR_UNKNOWN, "Convert(amf::AMF_MEMORY_HOST) failed with error %d\n", AVERROR_UNKNOWN);

    planes = (पूर्णाङ्क)surface->pVtbl->Get_Planes_गणनम्(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(src_data));

    अत्थाय (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        src_data[i] = plane->pVtbl->GetNative(plane);
        src_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst->data, dst->linesize,
                   src_data, src_linesize, dst->format,
                   w, h);
    पटिनिवत्त 0;
}



स्थिर शून्य amf_device_uninit(AVHWDeviceContext *device_ctx)
{
    AVAMFDeviceContext *amf_ctx = device_ctx->hwctx;
    AMF_RESULT          res = AMF_NOT_INITIALIZED;
    AMFTrace           *trace;

    सचे (amf_ctx->context) {
        amf_ctx->context->pVtbl->Terminate(amf_ctx->context);
        amf_ctx->context->pVtbl->Release(amf_ctx->context);
        amf_ctx->context = रिक्त;
    }

    सचे (amf_ctx->factory)
        res = amf_ctx->factory->pVtbl->GetTrace(amf_ctx->factory, &trace);

    सचे (res == AMF_OK) {
        trace->pVtbl->UnregisterWriter(trace, FFMPEG_AMF_WRITER_ID);
    }

    सचे(amf_ctx->library) {
        dlclose(amf_ctx->library);
        amf_ctx->library = रिक्त;
    }
    सचे (amf_ctx->trace_writer) {
        amf_writer_free(amf_ctx->trace_writer);
    }

    सचे (amf_ctx->lock_ctx == amf_lock_default) {
        ff_mutex_destroy((AVMutex*)amf_ctx->lock_ctx);
        av_freep(&amf_ctx->lock_ctx);
        amf_ctx->lock = रिक्त;
        amf_ctx->unlock = रिक्त;
    }

    amf_ctx->version = 0;
}

गणना AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx)
{
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = रिक्त;
    AMFGuid guid1 = IID_AMFContext1();
    शून्य * device = रिक्त;

#ifdef _WIN32
    // At the moment used only for DX12.
    AMFContext2 *context2 = रिक्त;

    /*
    Work around the incorrect C Context2 IID in unpatched AMF 1.5.2 headers;
    mostly pedantic fix as it works as it is in practice.
    TODO: replace with AMFGuid guid2 = IID_AMFContext2()
    once AMF 1.5.3 is available to public and marked as required version in ffmpeg.
    */
    स्थिर ध्रुव AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#endif

    सचे (!amf_ctx)
        पटिनिवत्त AMF_MEMORY_UNKNOWN;

#ifdef _WIN32
    सचे (AMF_IFACE_CALL(context, QueryInterface, &guid2, (शून्य**)&context2) == AMF_OK)
    {
        device = AMF_IFACE_CALL(context2, GetDX12Device, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);

        सचे (device)
            पटिनिवत्त AMF_MEMORY_DX12;
    }

    सचे (AMF_IFACE_CALL(context, GetDX11Device, AMF_DX11_1))
        पटिनिवत्त AMF_MEMORY_DX11;

    सचे (AMF_IFACE_CALL(context, GetDX9Device, AMF_DX9))
        पटिनिवत्त AMF_MEMORY_DX9;
#endif

    सचे (AMF_IFACE_CALL(context, QueryInterface, &guid1, (शून्य**)&context1) != AMF_OK)
        पटिनिवत्त AMF_MEMORY_UNKNOWN;

    device = AMF_IFACE_CALL(context1, GetVulkanDevice);
    AMF_IFACE_CALL(context1, Release);
    सचे (device)
        पटिनिवत्त AMF_MEMORY_VULKAN;

    पटिनिवत्त AMF_MEMORY_UNKNOWN;
}

स्थिर पूर्णाङ्क amf_device_init(AVHWDeviceContext *ctx)
{
    AVAMFDeviceContext *amf_ctx = ctx->hwctx;
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = रिक्त;
    AMFGuid guid1 = IID_AMFContext1();
    AMF_RESULT res;

#ifdef _WIN32
    AMFContext2 *context2 = रिक्त;
    स्थिर ध्रुव AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#endif

    सचे (!amf_ctx->lock) {
        amf_ctx->lock_ctx = av_mallocz(परिमाण(AVMutex));
        सचे (!amf_ctx->lock_ctx) {
            पटिनिवत्त AVERROR(ENOMEM);
        }
        ff_mutex_init((AVMutex*)amf_ctx->lock_ctx, रिक्त);
        amf_ctx->lock   = amf_lock_default;
        amf_ctx->unlock = amf_unlock_default;
    }

    सचे (av_amf_get_memory_type(amf_ctx) != AMF_MEMORY_UNKNOWN) {
        av_log(ctx, AV_LOG_VERBOSE, "AMF is already initialized, skipping init.\n");
        पटिनिवत्त 0;
    }

#ifdef _WIN32
    res = AMF_IFACE_CALL(context, InitDX11, रिक्त, AMF_DX11_1);
    सचे (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D11.\n");
        पटिनिवत्त 0;
    }

    res = AMF_IFACE_CALL(context, QueryInterface, &guid2, (शून्य**)&context2);
    सचे (res == AMF_OK) {
        res = AMF_IFACE_CALL(context2, InitDX12, रिक्त, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);
        सचे (res == AMF_OK) {
            av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D12.\n");
            पटिनिवत्त 0;
        }
    } अञ्ञथा {
        av_log(ctx, AV_LOG_VERBOSE, "QueryInterface(AMFContext2) failed with error %d, trying older D3D APIs...\n", res);
    }

    res = AMF_IFACE_CALL(context, InitDX9, रिक्त);
    सचे (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D9.\n");
        पटिनिवत्त 0;
    }

    av_log(ctx, AV_LOG_WARNING, "AMF failed to initialize with any of supported versions of DirectX, trying Vulkan instead...\n");
#endif

    res = AMF_IFACE_CALL(context, QueryInterface, &guid1, (शून्य**)&context1);
    सचे (res != AMF_OK) {
        av_log(ctx, AV_LOG_ERROR, "QueryInterface(AMFContext1) failed with error %d\n", res);
        पटिनिवत्त AVERROR_UNKNOWN;
    }

    res = AMF_IFACE_CALL(context1, InitVulkan, रिक्त);
    AMF_IFACE_CALL(context1, Release);

    सचे (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via Vulkan.\n");
    } अञ्ञथा {
        सचे (res == AMF_NOT_SUPPORTED)
            av_log(ctx, AV_LOG_ERROR, "AMF via Vulkan is not supported on the given device.\n");
        अञ्ञथा
            av_log(ctx, AV_LOG_ERROR, "Failed to initialize AMF via Vulkan, error %d\n", res);

        पटिनिवत्त AVERROR(ENOSYS);
    }

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क amf_load_library(AVAMFDeviceContext* amf_ctx,  शून्य* avcl)
{
    AMFInit_Fn         init_fun;
    AMFQueryVersion_Fn version_fun;
    AMF_RESULT         res;

    amf_ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(avcl, amf_ctx->library != रिक्त,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(amf_ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, init_fun != रिक्त, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    version_fun = (AMFQueryVersion_Fn)dlsym(amf_ctx->library, AMF_QUERY_VERSION_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, version_fun != रिक्त, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_VERSION_FUNCTION_NAME);

    amf_uint64 version;
    res = version_fun(&version);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_VERSION_FUNCTION_NAME, res);
    amf_ctx->version = version;
    res = init_fun(AMF_FULL_VERSION, &amf_ctx->factory);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_INIT_FUNCTION_NAME, res);
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क amf_device_create(AVHWDeviceContext *device_ctx,
                              ध्रुव वर्ण *device,
                              AVDictionary *opts, पूर्णाङ्क flags)
{
    AVAMFDeviceContext        *ctx = device_ctx->hwctx;
    AMFTrace           *trace;
    पूर्णाङ्क ret;
    सचे ((ret = amf_load_library(ctx, device_ctx)) == 0) {
        ret = ctx->factory->pVtbl->GetTrace(ctx->factory, &trace);
        सचे (ret == AMF_OK) {
            पूर्णाङ्क level_ff = av_log_get_level();
            पूर्णाङ्क level_amf = AMF_TRACE_TRACE;
            amf_bool enable_log = true;
            विकल्प(level_ff)
            {
            पक्ष AV_LOG_QUIET:
                level_amf = AMF_TRACE_ERROR;
                enable_log = false;
                भङ्ग;
            पक्ष AV_LOG_PANIC:
            पक्ष AV_LOG_FATAL:
            पक्ष AV_LOG_ERROR:
                level_amf = AMF_TRACE_ERROR;
                भङ्ग;
            पक्ष AV_LOG_WARNING:
            पक्ष AV_LOG_INFO:
                level_amf = AMF_TRACE_WARNING;
                भङ्ग;
            पक्ष AV_LOG_VERBOSE:
                level_amf = AMF_TRACE_INFO;
                भङ्ग;
            पक्ष AV_LOG_DEBUG:
                level_amf = AMF_TRACE_DEBUG;
                भङ्ग;
            पक्ष AV_LOG_TRACE:
                level_amf = AMF_TRACE_TRACE;
                भङ्ग;
            }
            सचे(ctx->version == AMF_MAKE_FULL_VERSION(1, 4, 35, 0)){// get around a bug in trace in AMF runtime driver 24.20
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
        सचे (ret == AMF_OK) {
            AMF_ASSIGN_PROPERTY_INT64(ret, ctx->context, L"DeviceSurfaceCacheSize", 50 );
            पटिनिवत्त 0;
        }
        av_log(device_ctx, AV_LOG_ERROR, "CreateContext() failed with error %d.\n", ret);
    }
    amf_device_uninit(device_ctx);
    पटिनिवत्त ret;
}

#सचे CONFIG_DXVA2
स्थिर पूर्णाङ्क amf_init_from_dxva2_device(AVAMFDeviceContext * amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVDXVA2DeviceContext *hwctx = child_device_ctx->hwctx;
    IDirect3DDevice9    *device;
    HANDLE              device_handle;
    HRESULT             hr;
    AMF_RESULT          res;
    पूर्णाङ्क ret;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &device_handle);
    सचे (FAILED(hr)) {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to open device handle for Direct3D9 device: %lx.\n", (unsigned long)hr);
        पटिनिवत्त AVERROR_EXTERNAL;
    }

    hr = IDirect3DDeviceManager9_LockDevice(hwctx->devmgr, device_handle, &device, FALSE);
    सचे (SUCCEEDED(hr)) {
        IDirect3DDeviceManager9_UnlockDevice(hwctx->devmgr, device_handle, FALSE);
        ret = 0;
    } अञ्ञथा {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to lock device handle for Direct3D9 device: %lx.\n", (unsigned long)hr);
        ret = AVERROR_EXTERNAL;
    }


    IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, device_handle);

    सचे (ret < 0)
        पटिनिवत्त ret;

    res = amf_ctx->context->pVtbl->InitDX9(amf_ctx->context, device);

    IDirect3DDevice9_Release(device);

    सचे (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        सचे (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D9 is not supported on the given device.\n");
        अञ्ञथा
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on given D3D9 device: %d.\n", res);
        पटिनिवत्त AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via DXVA2.\n");
    पटिनिवत्त 0;
}
#endif

#सचे CONFIG_D3D11VA
स्थिर पूर्णाङ्क amf_init_from_d3d11_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AMF_RESULT res;
    AVD3D11VADeviceContext *hwctx = child_device_ctx->hwctx;
    res = amf_ctx->context->pVtbl->InitDX11(amf_ctx->context, hwctx->device, AMF_DX11_1);
    सचे (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        सचे (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D11 is not supported on the given device.\n");
        अञ्ञथा
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D11 device: %d.\n", res);
        पटिनिवत्त AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D11.\n");
    hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    पटिनिवत्त 0;
}
#endif

#सचे CONFIG_D3D12VA
स्थिर पूर्णाङ्क amf_init_from_d3d12_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVD3D12VADeviceContext *hwctx = child_device_ctx->hwctx;
    AMF_RESULT res;
    AMFContext2 *context2 = रिक्त;
    AMFGuid guid = IID_AMFContext2();
    res = amf_ctx->context->pVtbl->QueryInterface(amf_ctx->context, &guid, (शून्य**)&context2);
    AMF_RETURN_IF_FALSE(child_device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "CreateContext2() failed with error %d\n", res);
    res = context2->pVtbl->InitDX12(context2, hwctx->device, AMF_DX12);
    context2->pVtbl->Release(context2);
    सचे (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        सचे (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D12 is not supported on the given device.\n");
        अञ्ञथा
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D12 device: %d.\n", res);
        पटिनिवत्त AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D12.\n");
    पटिनिवत्त 0;
}
#endif


स्थिर पूर्णाङ्क amf_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *child_device_ctx, AVDictionary *opts,
                              पूर्णाङ्क flags)
{
#सचे CONFIG_DXVA2 || CONFIG_D3D11VA || CONFIG_D3D12VA
    AVAMFDeviceContext        *amf_ctx = device_ctx->hwctx;
#endif
    पूर्णाङ्क ret;

    ret = amf_device_create(device_ctx, "", opts, flags);
    सचे(ret < 0)
        पटिनिवत्त ret;

    विकल्प (child_device_ctx->type) {
#सचे CONFIG_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
        पटिनिवत्त amf_init_from_dxva2_device(amf_ctx, child_device_ctx);
#endif
#सचे CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
        पटिनिवत्त amf_init_from_d3d11_device(amf_ctx, child_device_ctx);
#endif
#सचे CONFIG_D3D12VA
    पक्ष AV_HWDEVICE_TYPE_D3D12VA:
        पटिनिवत्त amf_init_from_d3d12_device(amf_ctx, child_device_ctx);
#endif
    स्वभाव:
        av_log(child_device_ctx, AV_LOG_ERROR, "AMF initialisation from a %s device is not supported.\n",
               av_hwdevice_get_type_name(child_device_ctx->type));
        पटिनिवत्त AVERROR(ENOSYS);
    }
}

स्थिर शून्य amf_unmap_frame(av_unused AVHWFramesContext *unused, HWMapDescriptor *hwmap)
{
    AMFSurface1 *surface1 = hwmap->priv;
    AMF_IFACE_CALL(surface1, Unmap);
    AMF_IFACE_CALL(surface1, Release);
}

स्थिर पूर्णाङ्क amf_map_frame(AVHWFramesContext *device_ctx, AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    AMFSurface *surface = (AMFSurface *)src->data[0];
    AMFSurface1 *surface1 = रिक्त;
    size_t *linesizes = रिक्त;
    uint8_t **map = रिक्त;
    पूर्णाङ्क amf_mem_flags = AMF_MEMORY_CPU_NONE;
    ध्रुव AMFGuid guid = IID_AMFSurface1();
    AMF_RESULT res = AMF_FAIL;
    size_t plane_गणनम् = 0;
    पूर्णाङ्क ret = -1;

    AMF_RETURN_IF_FALSE(device_ctx, surface != रिक्त, AVERROR(EINVAL) , "Source surface is null");

    res = AMF_IFACE_CALL(surface, QueryInterface, &guid, (शून्य**)&surface1);
    AMF_RETURN_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "QueryInterface(AMFSurface1) failed with error %d\n", res);

    सचे (flags & AV_HWFRAME_MAP_READ)
        amf_mem_flags |= AMF_MEMORY_CPU_READ;

    सचे (flags & AV_HWFRAME_MAP_WRITE)
        amf_mem_flags |= AMF_MEMORY_CPU_WRITE;

    plane_गणनम् = AMF_IFACE_CALL(surface, Get_Planes_गणनम्);
    linesizes = av_malloc_array(परिमाण(size_t), plane_गणनम्);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, linesizes, AVERROR(ENOMEM), "Unable to allocate line sizes array\n");

    map = av_malloc_array(परिमाण(uint8_t *), plane_गणनम्);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, map, AVERROR(ENOMEM), "Unable to allocate mapping buffer\n");

    dst->format = av_amf_to_av_format(AMF_IFACE_CALL(surface, GetFormat));

    res = AMF_IFACE_CALL(surface1, Map, amf_mem_flags, plane_गणनम्, linesizes, (शून्य**)map);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "AMFSurface1->Map() failed with error %d\n", res);

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, &amf_unmap_frame, surface1);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, ret >= 0, ret, "ff_hwframe_map_create failed with error %d\n", ret);

    dst->width  = src->width;
    dst->height = src->height;
    av_frame_copy_props(dst, src);

    // The dst frame is no longer a hardware frame, from the perspective of any dst frame consumer.
    av_buffer_unref(&dst->hw_frames_ctx);

    अत्थाय (पूर्णाङ्क plane = 0; plane < plane_गणनम्; ++plane)
    {
        dst->data[plane] = map[plane];
        dst->linesize[plane] = linesizes[plane];
    }

fail:
    सचे (map)
        av_free(map);

    सचे (linesizes)
        av_free(linesizes);

    सचे (ret < 0 && surface1 != रिक्त)
        AMF_IFACE_CALL(surface1, Release);

    पटिनिवत्त ret;
}

ध्रुव HWContextType ff_hwcontext_type_amf = {
    .type                 = AV_HWDEVICE_TYPE_AMF,
    .name                 = "AMF",

    .device_hwctx_size    = परिमाण(AVAMFDeviceContext),
    .frames_hwctx_size    = परिमाण(AMFFramesContext),

    .device_create        = amf_device_create,
    .device_derive        = amf_device_derive,
    .device_init          = amf_device_init,
    .device_uninit        = amf_device_uninit,
    .frames_get_constraints = amf_frames_get_constraints,
    .frames_init          = amf_frames_init,
    .frames_get_buffer    = amf_get_buffer,
    .transfer_get_formats = amf_transfer_get_formats,
    .transfer_data_to     = amf_transfer_data_to,
    .transfer_data_from   = amf_transfer_data_from,
    .map_from             = amf_map_frame,

    .pix_fmts             = (ध्रुव गणना AVPixelFormat[]){ AV_PIX_FMT_AMF_SURFACE, AV_PIX_FMT_NONE },
};
