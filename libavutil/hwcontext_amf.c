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

#ضمن "mem.h"
#ضمن "buffer.h"
#ضمن "pixfmt.h"
#ضمن "pixdesc.h"
#ضمن "imgutils.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_amf.h"
#ضمن "hwcontext_internal.h"
#ضمن "hwcontext_amf_internal.h"

#ضمن "libavutil/thread.h"
#ضمن "libavutil/avassert.h"

#ضمن <AMF/core/Surface.h>
#ضمن <AMF/core/Trace.h>

#𐡄𐡍 CONFIG_VULKAN
#ضمن "hwcontext_vulkan.h"
#endif
#𐡄𐡍 CONFIG_D3D11VA
#ضمن "libavutil/hwcontext_d3d11va.h"
#endif
#𐡄𐡍 CONFIG_D3D12VA
#ضمن "libavutil/hwcontext_d3d12va.h"
#endif
#𐡄𐡍 CONFIG_DXVA2
#define COBJMACROS
#ضمن "libavutil/hwcontext_dxva2.h"
#endif
#ifdef _WIN32
#ضمن "compat/w32dlfcn.h"
#وإلا
#ضمن <dlfcn.h>
#endif
#define FFMPEG_AMF_WRITER_ID L"ffmpeg_amf"

ساكن فراغ amf_lock_default(فراغ *opaque)
{
    ff_mutex_lock((AVMutex*)opaque);
}

ساكن فراغ amf_unlock_default(فراغ *opaque)
{
    ff_mutex_unlock((AVMutex*)opaque);
}

تعريفنوع بنية AmfTraceWriter {
    AMFTraceWriterVtbl *vtblp;
    فراغ               *avctx;
    AMFTraceWriterVtbl  vtbl;
} AmfTraceWriter;

ساكن فراغ AMF_CDECL_CALL AMFTraceWriter_Write(AMFTraceWriter *pThis,
    ثابت wchar_t *scope, ثابت wchar_t *message)
{
    AmfTraceWriter *tracer = (AmfTraceWriter*)pThis;
    av_log(tracer->avctx, AV_LOG_DEBUG, "%ls: %ls", scope, message); // \n is provided from AMF
}

ساكن فراغ AMF_CDECL_CALL AMFTraceWriter_Flush(AMFTraceWriter *pThis)
{
}

ساكن AmfTraceWriter * amf_writer_alloc(فراغ  *avctx)
{
    AmfTraceWriter * writer = av_mallocz(حجم(AmfTraceWriter));
    𐡄𐡍 (!writer)
        أرجع عدم;

    writer->vtblp = &writer->vtbl;
    writer->vtblp->Write = AMFTraceWriter_Write;
    writer->vtblp->Flush = AMFTraceWriter_Flush;
    writer->avctx = avctx;

    أرجع writer;
}

ساكن فراغ amf_writer_free(فراغ  *opaque)
{
    AmfTraceWriter *writer = (AmfTraceWriter *)opaque;
    av_freep(&writer);
}

/**
 * We still need AVHWFramesContext to utilize our hardware memory
 * otherwise, we will receive the error "HW format requires hw_frames_ctx to be non-NULL".
 * (libavfilter\buffersrc.c function query_formats)
*/
تعريفنوع بنية {
    فراغ *dummy;
} AMFFramesContext;

تعريفنوع بنية AVAMFFormatMap {
    تعداد AVPixelFormat       av_format;
    تعداد AMF_SURFACE_FORMAT  amf_format;
} FormatMap;

ثابت FormatMap format_map[] =
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

تعداد AMF_SURFACE_FORMAT av_av_to_amf_format(تعداد AVPixelFormat fmt)
{
    صحيح i;
    لكل (i = 0; i < amf_countof(format_map); i++) {
        𐡄𐡍 (format_map[i].av_format == fmt) {
            أرجع format_map[i].amf_format;
        }
    }
    أرجع AMF_SURFACE_UNKNOWN;
}

تعداد AVPixelFormat av_amf_to_av_format(تعداد AMF_SURFACE_FORMAT fmt)
{
    صحيح i;
    لكل (i = 0; i < amf_countof(format_map); i++) {
        𐡄𐡍 (format_map[i].amf_format == fmt) {
            أرجع format_map[i].av_format;
        }
    }
    أرجع AV_PIX_FMT_NONE;
}

تعداد AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(تعداد AVColorRange color_range, تعداد AVColorSpace color_space)
{
    بدل (color_space) {
    حالة AVCOL_SPC_SMPTE170M:
        𐡄𐡍 (color_range == AVCOL_RANGE_JPEG) {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_601;
        } وإلا {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_601;
        }
        اكسر;
    حالة AVCOL_SPC_BT709:
        𐡄𐡍 (color_range == AVCOL_RANGE_JPEG) {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_709;
        } وإلا {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_709;
        }
        اكسر;
    حالة AVCOL_SPC_BT2020_NCL:
    حالة AVCOL_SPC_BT2020_CL:
        𐡄𐡍 (color_range == AVCOL_RANGE_JPEG) {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_2020;
        } وإلا {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_2020;
        }
        اكسر;

    افتراضي:
        أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_UNKNOWN;
    }
}

صحيح av_amf_display_mastering_meta_to_hdrmeta(ثابت AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta)
{
    𐡄𐡍 (!display_meta || !hdrmeta)
        أرجع AVERROR(EINVAL);

    𐡄𐡍 (display_meta->has_luminance) {
        ثابت unsigned صحيح luma_den = 10000;
        hdrmeta->maxMasteringLuminance =
            (amf_uint32)(luma_den * av_q2d(display_meta->max_luminance));
        hdrmeta->minMasteringLuminance =
            FFMIN((amf_uint32)(luma_den * av_q2d(display_meta->min_luminance)), hdrmeta->maxMasteringLuminance);
    }

    𐡄𐡍 (display_meta->has_primaries) {
        ثابت unsigned صحيح chroma_den = 50000;
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

    أرجع 0;
}

صحيح av_amf_light_metadata_to_hdrmeta(ثابت AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta)
{
    𐡄𐡍 (!light_meta || !hdrmeta)
        أرجع AVERROR(EINVAL);

    hdrmeta->maxContentLightLevel = (amf_uint16)light_meta->MaxCLL;
    hdrmeta->maxFrameAverageLightLevel = (amf_uint16)light_meta->MaxFALL;

    أرجع 0;
}

صحيح av_amf_extract_hdr_metadata(ثابت AVFrame *frame, AMFHDRMetadata *hdrmeta)
{
    AVFrameSideData *sidedata;
    AVContentLightMetadata *content_light = عدم;
    AVMasteringDisplayMetadata *mastering_display = عدم;

    𐡄𐡍 (!frame || !hdrmeta)
        أرجع AVERROR(EINVAL);

    sidedata = av_frame_get_side_data(frame, AV_FRAME_DATA_MASTERING_DISPLAY_METADATA);
    𐡄𐡍 (sidedata) {
        mastering_display = (AVMasteringDisplayMetadata *)sidedata->data;
        𐡄𐡍 (av_amf_display_mastering_meta_to_hdrmeta(mastering_display, hdrmeta) != 0)
            mastering_display = عدم;
    }

    sidedata = av_frame_get_side_data(frame, AV_FRAME_DATA_CONTENT_LIGHT_LEVEL);
    𐡄𐡍 (sidedata) {
        content_light = (AVContentLightMetadata *)sidedata->data;
        𐡄𐡍 (av_amf_light_metadata_to_hdrmeta(content_light, hdrmeta) != 0)
            content_light = عدم;
    }

    𐡄𐡍 (!mastering_display && !content_light)
        أرجع AVERROR(ENODATA);

    أرجع 0;
}

صحيح av_amf_attach_hdr_metadata(AVFrame *frame, ثابت AMFHDRMetadata *hdrmeta) {
    𐡄𐡍 (!hdrmeta || !frame)
        أرجع AVERROR(EINVAL);

    AVMasteringDisplayMetadata *mastering =
        av_mastering_display_metadata_create_side_data(frame);
    ثابت صحيح chroma_den = 50000;
    ثابت صحيح luma_den = 10000;

    𐡄𐡍 (!mastering)
      أرجع AVERROR(ENOMEM);

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
    𐡄𐡍 (hdrmeta->maxContentLightLevel) {
      AVContentLightMetadata *light =
          av_content_light_metadata_create_side_data(frame);

      𐡄𐡍 (!light)
        أرجع AVERROR(ENOMEM);

      light->MaxCLL = hdrmeta->maxContentLightLevel;
      light->MaxFALL = hdrmeta->maxFrameAverageLightLevel;
    }

    أرجع 0;
}

ساكن ثابت تعداد AVPixelFormat supported_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_BGR0,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
#𐡄𐡍 CONFIG_D3D11VA
    AV_PIX_FMT_D3D11,
#endif
#𐡄𐡍 CONFIG_D3D12VA
    AV_PIX_FMT_D3D12,
#endif
#𐡄𐡍 CONFIG_DXVA2
    AV_PIX_FMT_DXVA2_VLD,
#endif
};

ساكن ثابت تعداد AVPixelFormat supported_transfer_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
    AV_PIX_FMT_NONE,
};

ساكن صحيح amf_frames_get_constraints(AVHWDeviceContext *ctx,
                                       ثابت فراغ *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    صحيح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    𐡄𐡍 (!constraints->valid_sw_formats)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    𐡄𐡍 (!constraints->valid_hw_formats)
        أرجع AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_AMF_SURFACE;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    أرجع 0;
}

ساكن فراغ amf_dummy_free(فراغ *opaque, uint8_t *data)
{

}

ساكن AVBufferRef *amf_pool_alloc(فراغ *opaque, size_t size)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)opaque;
    AVBufferRef *buf;

    buf = av_buffer_create(عدم, 0, amf_dummy_free, hwfc, AV_BUFFER_FLAG_READONLY);
    𐡄𐡍 (!buf) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create buffer for AMF context.\n");
        أرجع عدم;
    }
    أرجع buf;
}

ساكن صحيح amf_frames_init(AVHWFramesContext *ctx)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        𐡄𐡍 (ctx->sw_format == supported_formats[i])
            اكسر;
    }
    𐡄𐡍 (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        أرجع AVERROR(ENOSYS);
    }

    ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(حجم(AMFSurface), ctx,
                                 &amf_pool_alloc, عدم);

    أرجع 0;
}


ساكن صحيح amf_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    𐡄𐡍 (!frame->buf[0])
        أرجع AVERROR(ENOMEM);

    frame->data[0] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_AMF_SURFACE;
    frame->width   = ctx->width;
    frame->height  = ctx->height;
    أرجع 0;
}

ساكن صحيح amf_transfer_get_formats(AVHWFramesContext *ctx,
                                     تعداد AVHWFrameTransferDirection dir,
                                     تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *fmts;
    صحيح i;

    fmts = av_malloc_array(FF_ARRAY_ELEMS(supported_transfer_formats), حجم(*fmts));
    𐡄𐡍 (!fmts)
        أرجع AVERROR(ENOMEM);
    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_transfer_formats); i++)
        fmts[i] = supported_transfer_formats[i];

    *formats = fmts;

    أرجع 0;
}

ساكن فراغ amf_free_amfsurface(فراغ *opaque, uint8_t *data)
{
    𐡄𐡍(!!data){
        AMFSurface *surface = (AMFSurface*)(data);
        surface->pVtbl->Release(surface);
    }
}

ساكن صحيح amf_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)dst->data[0];
    AMFPlane *plane;
    uint8_t  *dst_data[4];
    صحيح       dst_linesize[4];
    صحيح       planes;
    صحيح       i;
    صحيح       res;
    صحيح w = FFMIN(dst->width,  src->width);
    صحيح h = FFMIN(dst->height, src->height);

    𐡄𐡍 (dst->hw_frames_ctx->data != (uint8_t *)ctx || src->format != ctx->sw_format)
        أرجع AVERROR(EINVAL);

    𐡄𐡍 (!surface) {
        AVHWDeviceContext   *hwdev_ctx = ctx->device_ctx;
        AVAMFDeviceContext  *amf_device_ctx = (AVAMFDeviceContext *)hwdev_ctx->hwctx;
        AMF_SURFACE_FORMAT  format = av_av_to_amf_format(ctx->sw_format);
        res = amf_device_ctx->context->pVtbl->AllocSurface(amf_device_ctx->context, AMF_MEMORY_HOST, format, dst->width, dst->height, &surface);
        AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR(ENOMEM), "AllocSurface() failed  with error %d\n", res);
        dst->data[0] = (uint8_t *)surface;
        dst->buf[1] = av_buffer_create((uint8_t *)surface, حجم(surface),
                                            amf_free_amfsurface,
                                            عدم,
                                            AV_BUFFER_FLAG_READONLY);
    AMF_RETURN_IF_FALSE(ctx, !!dst->buf[1], AVERROR(ENOMEM), "av_buffer_create for amf surface failed.");
    }

    planes = (صحيح)surface->pVtbl->GetPlanesCount(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(dst_data));

    لكل (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        dst_data[i] = plane->pVtbl->GetNative(plane);
        dst_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst_data, dst_linesize,
                   src->data, src->linesize, src->format,
                   w, h);

    أرجع 0;
}

ساكن صحيح amf_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ثابت AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)src->data[0];
    AMFPlane *plane;
    uint8_t  *src_data[4];
    صحيح       src_linesize[4];
    صحيح       planes;
    صحيح       i;
    صحيح w = FFMIN(dst->width,  src->width);
    صحيح h = FFMIN(dst->height, src->height);
    صحيح ret;

    𐡄𐡍 (src->hw_frames_ctx->data != (uint8_t *)ctx || dst->format != ctx->sw_format)
        أرجع AVERROR(EINVAL);

    ret = surface->pVtbl->Convert(surface, AMF_MEMORY_HOST);
    AMF_RETURN_IF_FALSE(ctx, ret == AMF_OK, AVERROR_UNKNOWN, "Convert(amf::AMF_MEMORY_HOST) failed with error %d\n", AVERROR_UNKNOWN);

    planes = (صحيح)surface->pVtbl->GetPlanesCount(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(src_data));

    لكل (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        src_data[i] = plane->pVtbl->GetNative(plane);
        src_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst->data, dst->linesize,
                   src_data, src_linesize, dst->format,
                   w, h);
    أرجع 0;
}



ساكن فراغ amf_device_uninit(AVHWDeviceContext *device_ctx)
{
    AVAMFDeviceContext *amf_ctx = device_ctx->hwctx;
    AMF_RESULT          res = AMF_NOT_INITIALIZED;
    AMFTrace           *trace;

    𐡄𐡍 (amf_ctx->context) {
        amf_ctx->context->pVtbl->Terminate(amf_ctx->context);
        amf_ctx->context->pVtbl->Release(amf_ctx->context);
        amf_ctx->context = عدم;
    }

    𐡄𐡍 (amf_ctx->factory)
        res = amf_ctx->factory->pVtbl->GetTrace(amf_ctx->factory, &trace);

    𐡄𐡍 (res == AMF_OK) {
        trace->pVtbl->UnregisterWriter(trace, FFMPEG_AMF_WRITER_ID);
    }

    𐡄𐡍(amf_ctx->library) {
        dlclose(amf_ctx->library);
        amf_ctx->library = عدم;
    }
    𐡄𐡍 (amf_ctx->trace_writer) {
        amf_writer_free(amf_ctx->trace_writer);
    }

    𐡄𐡍 (amf_ctx->lock_ctx == amf_lock_default) {
        ff_mutex_destroy((AVMutex*)amf_ctx->lock_ctx);
        av_freep(&amf_ctx->lock_ctx);
        amf_ctx->lock = عدم;
        amf_ctx->unlock = عدم;
    }

    amf_ctx->version = 0;
}

تعداد AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx)
{
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = عدم;
    AMFGuid guid1 = IID_AMFContext1();
    فراغ * device = عدم;

#ifdef _WIN32
    // At the moment used only for DX12.
    AMFContext2 *context2 = عدم;

    /*
    Work around the incorrect C Context2 IID in unpatched AMF 1.5.2 headers;
    mostly pedantic fix as it works as it is in practice.
    TODO: replace with AMFGuid guid2 = IID_AMFContext2()
    once AMF 1.5.3 is available to public and marked as required version in ffmpeg.
    */
    ساكن ثابت AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#endif

    𐡄𐡍 (!amf_ctx)
        أرجع AMF_MEMORY_UNKNOWN;

#ifdef _WIN32
    𐡄𐡍 (AMF_IFACE_CALL(context, QueryInterface, &guid2, (فراغ**)&context2) == AMF_OK)
    {
        device = AMF_IFACE_CALL(context2, GetDX12Device, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);

        𐡄𐡍 (device)
            أرجع AMF_MEMORY_DX12;
    }

    𐡄𐡍 (AMF_IFACE_CALL(context, GetDX11Device, AMF_DX11_1))
        أرجع AMF_MEMORY_DX11;

    𐡄𐡍 (AMF_IFACE_CALL(context, GetDX9Device, AMF_DX9))
        أرجع AMF_MEMORY_DX9;
#endif

    𐡄𐡍 (AMF_IFACE_CALL(context, QueryInterface, &guid1, (فراغ**)&context1) != AMF_OK)
        أرجع AMF_MEMORY_UNKNOWN;

    device = AMF_IFACE_CALL(context1, GetVulkanDevice);
    AMF_IFACE_CALL(context1, Release);
    𐡄𐡍 (device)
        أرجع AMF_MEMORY_VULKAN;

    أرجع AMF_MEMORY_UNKNOWN;
}

ساكن صحيح amf_device_init(AVHWDeviceContext *ctx)
{
    AVAMFDeviceContext *amf_ctx = ctx->hwctx;
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = عدم;
    AMFGuid guid1 = IID_AMFContext1();
    AMF_RESULT res;

#ifdef _WIN32
    AMFContext2 *context2 = عدم;
    ساكن ثابت AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#endif

    𐡄𐡍 (!amf_ctx->lock) {
        amf_ctx->lock_ctx = av_mallocz(حجم(AVMutex));
        𐡄𐡍 (!amf_ctx->lock_ctx) {
            أرجع AVERROR(ENOMEM);
        }
        ff_mutex_init((AVMutex*)amf_ctx->lock_ctx, عدم);
        amf_ctx->lock   = amf_lock_default;
        amf_ctx->unlock = amf_unlock_default;
    }

    𐡄𐡍 (av_amf_get_memory_type(amf_ctx) != AMF_MEMORY_UNKNOWN) {
        av_log(ctx, AV_LOG_VERBOSE, "AMF is already initialized, skipping init.\n");
        أرجع 0;
    }

#ifdef _WIN32
    res = AMF_IFACE_CALL(context, InitDX11, عدم, AMF_DX11_1);
    𐡄𐡍 (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D11.\n");
        أرجع 0;
    }

    res = AMF_IFACE_CALL(context, QueryInterface, &guid2, (فراغ**)&context2);
    𐡄𐡍 (res == AMF_OK) {
        res = AMF_IFACE_CALL(context2, InitDX12, عدم, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);
        𐡄𐡍 (res == AMF_OK) {
            av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D12.\n");
            أرجع 0;
        }
    } وإلا {
        av_log(ctx, AV_LOG_VERBOSE, "QueryInterface(AMFContext2) failed with error %d, trying older D3D APIs...\n", res);
    }

    res = AMF_IFACE_CALL(context, InitDX9, عدم);
    𐡄𐡍 (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D9.\n");
        أرجع 0;
    }

    av_log(ctx, AV_LOG_WARNING, "AMF failed to initialize with any of supported versions of DirectX, trying Vulkan instead...\n");
#endif

    res = AMF_IFACE_CALL(context, QueryInterface, &guid1, (فراغ**)&context1);
    𐡄𐡍 (res != AMF_OK) {
        av_log(ctx, AV_LOG_ERROR, "QueryInterface(AMFContext1) failed with error %d\n", res);
        أرجع AVERROR_UNKNOWN;
    }

    res = AMF_IFACE_CALL(context1, InitVulkan, عدم);
    AMF_IFACE_CALL(context1, Release);

    𐡄𐡍 (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via Vulkan.\n");
    } وإلا {
        𐡄𐡍 (res == AMF_NOT_SUPPORTED)
            av_log(ctx, AV_LOG_ERROR, "AMF via Vulkan is not supported on the given device.\n");
        وإلا
            av_log(ctx, AV_LOG_ERROR, "Failed to initialize AMF via Vulkan, error %d\n", res);

        أرجع AVERROR(ENOSYS);
    }

    أرجع 0;
}

ساكن صحيح amf_load_library(AVAMFDeviceContext* amf_ctx,  فراغ* avcl)
{
    AMFInit_Fn         init_fun;
    AMFQueryVersion_Fn version_fun;
    AMF_RESULT         res;

    amf_ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(avcl, amf_ctx->library != عدم,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(amf_ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, init_fun != عدم, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    version_fun = (AMFQueryVersion_Fn)dlsym(amf_ctx->library, AMF_QUERY_VERSION_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, version_fun != عدم, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_VERSION_FUNCTION_NAME);

    amf_uint64 version;
    res = version_fun(&version);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_VERSION_FUNCTION_NAME, res);
    amf_ctx->version = version;
    res = init_fun(AMF_FULL_VERSION, &amf_ctx->factory);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_INIT_FUNCTION_NAME, res);
    أرجع 0;
}

ساكن صحيح amf_device_create(AVHWDeviceContext *device_ctx,
                              ثابت حرف *device,
                              AVDictionary *opts, صحيح flags)
{
    AVAMFDeviceContext        *ctx = device_ctx->hwctx;
    AMFTrace           *trace;
    صحيح ret;
    𐡄𐡍 ((ret = amf_load_library(ctx, device_ctx)) == 0) {
        ret = ctx->factory->pVtbl->GetTrace(ctx->factory, &trace);
        𐡄𐡍 (ret == AMF_OK) {
            صحيح level_ff = av_log_get_level();
            صحيح level_amf = AMF_TRACE_TRACE;
            amf_bool enable_log = true;
            بدل(level_ff)
            {
            حالة AV_LOG_QUIET:
                level_amf = AMF_TRACE_ERROR;
                enable_log = false;
                اكسر;
            حالة AV_LOG_PANIC:
            حالة AV_LOG_FATAL:
            حالة AV_LOG_ERROR:
                level_amf = AMF_TRACE_ERROR;
                اكسر;
            حالة AV_LOG_WARNING:
            حالة AV_LOG_INFO:
                level_amf = AMF_TRACE_WARNING;
                اكسر;
            حالة AV_LOG_VERBOSE:
                level_amf = AMF_TRACE_INFO;
                اكسر;
            حالة AV_LOG_DEBUG:
                level_amf = AMF_TRACE_DEBUG;
                اكسر;
            حالة AV_LOG_TRACE:
                level_amf = AMF_TRACE_TRACE;
                اكسر;
            }
            𐡄𐡍(ctx->version == AMF_MAKE_FULL_VERSION(1, 4, 35, 0)){// get around a bug in trace in AMF runtime driver 24.20
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
        𐡄𐡍 (ret == AMF_OK) {
            AMF_ASSIGN_PROPERTY_INT64(ret, ctx->context, L"DeviceSurfaceCacheSize", 50 );
            أرجع 0;
        }
        av_log(device_ctx, AV_LOG_ERROR, "CreateContext() failed with error %d.\n", ret);
    }
    amf_device_uninit(device_ctx);
    أرجع ret;
}

#𐡄𐡍 CONFIG_DXVA2
ساكن صحيح amf_init_from_dxva2_device(AVAMFDeviceContext * amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVDXVA2DeviceContext *hwctx = child_device_ctx->hwctx;
    IDirect3DDevice9    *device;
    HANDLE              device_handle;
    HRESULT             hr;
    AMF_RESULT          res;
    صحيح ret;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &device_handle);
    𐡄𐡍 (FAILED(hr)) {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to open device handle for Direct3D9 device: %lx.\n", (unsigned long)hr);
        أرجع AVERROR_EXTERNAL;
    }

    hr = IDirect3DDeviceManager9_LockDevice(hwctx->devmgr, device_handle, &device, FALSE);
    𐡄𐡍 (SUCCEEDED(hr)) {
        IDirect3DDeviceManager9_UnlockDevice(hwctx->devmgr, device_handle, FALSE);
        ret = 0;
    } وإلا {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to lock device handle for Direct3D9 device: %lx.\n", (unsigned long)hr);
        ret = AVERROR_EXTERNAL;
    }


    IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, device_handle);

    𐡄𐡍 (ret < 0)
        أرجع ret;

    res = amf_ctx->context->pVtbl->InitDX9(amf_ctx->context, device);

    IDirect3DDevice9_Release(device);

    𐡄𐡍 (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        𐡄𐡍 (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D9 is not supported on the given device.\n");
        وإلا
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on given D3D9 device: %d.\n", res);
        أرجع AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via DXVA2.\n");
    أرجع 0;
}
#endif

#𐡄𐡍 CONFIG_D3D11VA
ساكن صحيح amf_init_from_d3d11_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AMF_RESULT res;
    AVD3D11VADeviceContext *hwctx = child_device_ctx->hwctx;
    res = amf_ctx->context->pVtbl->InitDX11(amf_ctx->context, hwctx->device, AMF_DX11_1);
    𐡄𐡍 (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        𐡄𐡍 (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D11 is not supported on the given device.\n");
        وإلا
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D11 device: %d.\n", res);
        أرجع AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D11.\n");
    hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    أرجع 0;
}
#endif

#𐡄𐡍 CONFIG_D3D12VA
ساكن صحيح amf_init_from_d3d12_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVD3D12VADeviceContext *hwctx = child_device_ctx->hwctx;
    AMF_RESULT res;
    AMFContext2 *context2 = عدم;
    AMFGuid guid = IID_AMFContext2();
    res = amf_ctx->context->pVtbl->QueryInterface(amf_ctx->context, &guid, (فراغ**)&context2);
    AMF_RETURN_IF_FALSE(child_device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "CreateContext2() failed with error %d\n", res);
    res = context2->pVtbl->InitDX12(context2, hwctx->device, AMF_DX12);
    context2->pVtbl->Release(context2);
    𐡄𐡍 (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        𐡄𐡍 (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D12 is not supported on the given device.\n");
        وإلا
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D12 device: %d.\n", res);
        أرجع AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D12.\n");
    أرجع 0;
}
#endif


ساكن صحيح amf_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *child_device_ctx, AVDictionary *opts,
                              صحيح flags)
{
#𐡄𐡍 CONFIG_DXVA2 || CONFIG_D3D11VA || CONFIG_D3D12VA
    AVAMFDeviceContext        *amf_ctx = device_ctx->hwctx;
#endif
    صحيح ret;

    ret = amf_device_create(device_ctx, "", opts, flags);
    𐡄𐡍(ret < 0)
        أرجع ret;

    بدل (child_device_ctx->type) {
#𐡄𐡍 CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        أرجع amf_init_from_dxva2_device(amf_ctx, child_device_ctx);
#endif
#𐡄𐡍 CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        أرجع amf_init_from_d3d11_device(amf_ctx, child_device_ctx);
#endif
#𐡄𐡍 CONFIG_D3D12VA
    حالة AV_HWDEVICE_TYPE_D3D12VA:
        أرجع amf_init_from_d3d12_device(amf_ctx, child_device_ctx);
#endif
    افتراضي:
        av_log(child_device_ctx, AV_LOG_ERROR, "AMF initialisation from a %s device is not supported.\n",
               av_hwdevice_get_type_name(child_device_ctx->type));
        أرجع AVERROR(ENOSYS);
    }
}

ساكن فراغ amf_unmap_frame(av_unused AVHWFramesContext *unused, HWMapDescriptor *hwmap)
{
    AMFSurface1 *surface1 = hwmap->priv;
    AMF_IFACE_CALL(surface1, Unmap);
    AMF_IFACE_CALL(surface1, Release);
}

ساكن صحيح amf_map_frame(AVHWFramesContext *device_ctx, AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AMFSurface *surface = (AMFSurface *)src->data[0];
    AMFSurface1 *surface1 = عدم;
    size_t *linesizes = عدم;
    uint8_t **map = عدم;
    صحيح amf_mem_flags = AMF_MEMORY_CPU_NONE;
    ثابت AMFGuid guid = IID_AMFSurface1();
    AMF_RESULT res = AMF_FAIL;
    size_t plane_count = 0;
    صحيح ret = -1;

    AMF_RETURN_IF_FALSE(device_ctx, surface != عدم, AVERROR(EINVAL) , "Source surface is null");

    res = AMF_IFACE_CALL(surface, QueryInterface, &guid, (فراغ**)&surface1);
    AMF_RETURN_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "QueryInterface(AMFSurface1) failed with error %d\n", res);

    𐡄𐡍 (flags & AV_HWFRAME_MAP_READ)
        amf_mem_flags |= AMF_MEMORY_CPU_READ;

    𐡄𐡍 (flags & AV_HWFRAME_MAP_WRITE)
        amf_mem_flags |= AMF_MEMORY_CPU_WRITE;

    plane_count = AMF_IFACE_CALL(surface, GetPlanesCount);
    linesizes = av_malloc_array(حجم(size_t), plane_count);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, linesizes, AVERROR(ENOMEM), "Unable to allocate line sizes array\n");

    map = av_malloc_array(حجم(uint8_t *), plane_count);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, map, AVERROR(ENOMEM), "Unable to allocate mapping buffer\n");

    dst->format = av_amf_to_av_format(AMF_IFACE_CALL(surface, GetFormat));

    res = AMF_IFACE_CALL(surface1, Map, amf_mem_flags, plane_count, linesizes, (فراغ**)map);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "AMFSurface1->Map() failed with error %d\n", res);

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, &amf_unmap_frame, surface1);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, ret >= 0, ret, "ff_hwframe_map_create failed with error %d\n", ret);

    dst->width  = src->width;
    dst->height = src->height;
    av_frame_copy_props(dst, src);

    // The dst frame is no longer a hardware frame, from the perspective of any dst frame consumer.
    av_buffer_unref(&dst->hw_frames_ctx);

    لكل (صحيح plane = 0; plane < plane_count; ++plane)
    {
        dst->data[plane] = map[plane];
        dst->linesize[plane] = linesizes[plane];
    }

fail:
    𐡄𐡍 (map)
        av_free(map);

    𐡄𐡍 (linesizes)
        av_free(linesizes);

    𐡄𐡍 (ret < 0 && surface1 != عدم)
        AMF_IFACE_CALL(surface1, Release);

    أرجع ret;
}

ثابت HWContextType ff_hwcontext_type_amf = {
    .type                 = AV_HWDEVICE_TYPE_AMF,
    .name                 = "AMF",

    .device_hwctx_size    = حجم(AVAMFDeviceContext),
    .frames_hwctx_size    = حجم(AMFFramesContext),

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

    .pix_fmts             = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_AMF_SURFACE, AV_PIX_FMT_NONE },
};
