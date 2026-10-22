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

#إذا CONFIG_VULKAN
#ضمن "hwcontext_vulkan.h"
#پایان_اگر
#إذا CONFIG_D3D11VA
#ضمن "libavutil/hwcontext_d3d11va.h"
#پایان_اگر
#إذا CONFIG_D3D12VA
#ضمن "libavutil/hwcontext_d3d12va.h"
#پایان_اگر
#إذا CONFIG_DXVA2
#تعریف_کن COBJMACROS
#ضمن "libavutil/hwcontext_dxva2.h"
#پایان_اگر
#اگر_تعریف_شده _WIN32
#ضمن "compat/w32dlfcn.h"
#وإلا
#ضمن <dlfcn.h>
#پایان_اگر
#تعریف_کن FFMPEG_AMF_WRITER_ID L"ffmpeg_amf"

ساكن فراغ amf_قفل_default(فراغ *opaque)
{
    ff_mutex_قفل((AVMutex*)opaque);
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
    ثابت wchar_t *scope, ثابت wchar_t *پیام_2)
{
    AmfTraceWriter *tracer = (AmfTraceWriter*)pThis;
    av_log(tracer->avctx, AV_LOG_DEBUG, "%ls: %ls", scope, پیام_2); // \n is provided from AMF
}

ساكن فراغ AMF_CDECL_CALL AMFTraceWriter_Flush(AMFTraceWriter *pThis)
{
}

ساكن AmfTraceWriter * amf_writer_alloc(فراغ  *avctx)
{
    AmfTraceWriter * writer = av_mallocz(حجم(AmfTraceWriter));
    إذا (!writer)
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

تعداد AMF_SURFACE_FORMAT av_av_مقصد_amf_format(تعداد AVPixelFormat fmt)
{
    صحيح i;
    لكل (i = 0; i < amf_countof(format_map); i++) {
        إذا (format_map[i].av_format == fmt) {
            أرجع format_map[i].amf_format;
        }
    }
    أرجع AMF_SURFACE_UNKNOWN;
}

تعداد AVPixelFormat av_amf_مقصد_av_format(تعداد AMF_SURFACE_FORMAT fmt)
{
    صحيح i;
    لكل (i = 0; i < amf_countof(format_map); i++) {
        إذا (format_map[i].amf_format == fmt) {
            أرجع format_map[i].av_format;
        }
    }
    أرجع AV_PIX_FMT_NONE;
}

تعداد AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(تعداد AVColorRange color_range, تعداد AVColorSpace color_space)
{
    بدل (color_space) {
    حالة AVCOL_SPC_SMPTE170M:
        إذا (color_range == AVCOL_RANGE_JPEG) {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_پر_601;
        } وإلا {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_601;
        }
        اكسر;
    حالة AVCOL_SPC_BT709:
        إذا (color_range == AVCOL_RANGE_JPEG) {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_پر_709;
        } وإلا {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_709;
        }
        اكسر;
    حالة AVCOL_SPC_BT2020_NCL:
    حالة AVCOL_SPC_BT2020_CL:
        إذا (color_range == AVCOL_RANGE_JPEG) {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_پر_2020;
        } وإلا {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_2020;
        }
        اكسر;

    افتراضي:
        أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_UNKNOWN;
    }
}

صحيح av_amf_display_mastering_meta_مقصد_hdrmeta(ثابت AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta)
{
    إذا (!display_meta || !hdrmeta)
        أرجع AVERROR(EINVAL);

    إذا (display_meta->has_luminance) {
        ثابت بیعلامت صحيح luma_den = 10000;
        hdrmeta->maxMasteringLuminance =
            (amf_uint32)(luma_den * av_q2d(display_meta->max_luminance));
        hdrmeta->minMasteringLuminance =
            FFMIN((amf_uint32)(luma_den * av_q2d(display_meta->min_luminance)), hdrmeta->maxMasteringLuminance);
    }

    إذا (display_meta->has_primaries) {
        ثابت بیعلامت صحيح chroma_den = 50000;
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
        hdrmeta->white_نقطه[0] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_نقطه_2[0])), chroma_den);
        hdrmeta->white_نقطه[1] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_نقطه_2[1])), chroma_den);
    }

    أرجع 0;
}

صحيح av_amf_light_metadata_مقصد_hdrmeta(ثابت AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta)
{
    إذا (!light_meta || !hdrmeta)
        أرجع AVERROR(EINVAL);

    hdrmeta->maxContentLightLevel = (amf_uint16)light_meta->MaxCLL;
    hdrmeta->max_قاب_معدل_Light_Level = (amf_uint16)light_meta->MaxFALL;

    أرجع 0;
}

صحيح av_amf_استخراج_hdr_metadata(ثابت AVFrame *قاب, AMFHDRMetadata *hdrmeta)
{
    AVFrame_Side_داده *sidedata;
    AVContentLightMetadata *content_light = عدم;
    AVMasteringDisplayMetadata *mastering_display = عدم;

    إذا (!قاب || !hdrmeta)
        أرجع AVERROR(EINVAL);

    sidedata = av_قاب_get_side_داده(قاب, AV_قاب_داده_MASTERING_DISPLAY_METADATA);
    إذا (sidedata) {
        mastering_display = (AVMasteringDisplayMetadata *)sidedata->داده;
        إذا (av_amf_display_mastering_meta_مقصد_hdrmeta(mastering_display, hdrmeta) != 0)
            mastering_display = عدم;
    }

    sidedata = av_قاب_get_side_داده(قاب, AV_قاب_داده_CONTENT_LIGHT_LEVEL);
    إذا (sidedata) {
        content_light = (AVContentLightMetadata *)sidedata->داده;
        إذا (av_amf_light_metadata_مقصد_hdrmeta(content_light, hdrmeta) != 0)
            content_light = عدم;
    }

    إذا (!mastering_display && !content_light)
        أرجع AVERROR(ENODATA);

    أرجع 0;
}

صحيح av_amf_attach_hdr_metadata(AVFrame *قاب, ثابت AMFHDRMetadata *hdrmeta) {
    إذا (!hdrmeta || !قاب)
        أرجع AVERROR(EINVAL);

    AVMasteringDisplayMetadata *mastering =
        av_mastering_display_metadata_create_side_داده(قاب);
    ثابت صحيح chroma_den = 50000;
    ثابت صحيح luma_den = 10000;

    إذا (!mastering)
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

    mastering->white_نقطه_2[0] = av_make_q(hdrmeta->white_نقطه[0], chroma_den);
    mastering->white_نقطه_2[1] = av_make_q(hdrmeta->white_نقطه[1], chroma_den);

    mastering->max_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);
    mastering->min_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);

    mastering->has_luminance = 1;
    mastering->has_primaries = 1;
    إذا (hdrmeta->maxContentLightLevel) {
      AVContentLightMetadata *light =
          av_content_light_metadata_create_side_داده(قاب);

      إذا (!light)
        أرجع AVERROR(ENOMEM);

      light->MaxCLL = hdrmeta->maxContentLightLevel;
      light->MaxFALL = hdrmeta->max_قاب_معدل_Light_Level;
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
#إذا CONFIG_D3D11VA
    AV_PIX_FMT_D3D11,
#پایان_اگر
#إذا CONFIG_D3D12VA
    AV_PIX_FMT_D3D12,
#پایان_اگر
#إذا CONFIG_DXVA2
    AV_PIX_FMT_DXVA2_VLD,
#پایان_اگر
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

ساكن صحيح amf_قابها_get_constraints(AVHWDeviceContext *ctx,
                                       ثابت فراغ *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    صحيح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    إذا (!constraints->valid_sw_formats)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    إذا (!constraints->valid_hw_formats)
        أرجع AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_AMF_SURFACE;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    أرجع 0;
}

ساكن فراغ amf_dummy_free(فراغ *opaque, uint8_t *داده)
{

}

ساكن AVBufferRef *amf_pool_alloc(فراغ *opaque, size_t اندازه)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)opaque;
    AVBufferRef *buf;

    buf = av_میانگیر_create(عدم, 0, amf_dummy_free, hwfc, AV_میانگیر_FLAG_READONLY);
    إذا (!buf) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create buffer for AMF context.\n");
        أرجع عدم;
    }
    أرجع buf;
}

ساكن صحيح amf_قابها_init(AVHWFramesContext *ctx)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        إذا (ctx->sw_format == supported_formats[i])
            اكسر;
    }
    إذا (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        أرجع AVERROR(ENOSYS);
    }

    ffhwframesctx(ctx)->pool_داخلی =
            av_میانگیر_pool_init2(حجم(AMFSurface), ctx,
                                 &amf_pool_alloc, عدم);

    أرجع 0;
}


ساكن صحيح amf_get_میانگیر(AVHWFramesContext *ctx, AVFrame *قاب)
{
    قاب->buf[0] = av_میانگیر_pool_get(ctx->pool);
    إذا (!قاب->buf[0])
        أرجع AVERROR(ENOMEM);

    قاب->داده[0] = قاب->buf[0]->داده;
    قاب->format  = AV_PIX_FMT_AMF_SURFACE;
    قاب->عرض   = ctx->عرض;
    قاب->ارتفاع  = ctx->ارتفاع;
    أرجع 0;
}

ساكن صحيح amf_transfer_get_formats(AVHWFramesContext *ctx,
                                     تعداد AVHWFrameTransferDirection dir,
                                     تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *fmts;
    صحيح i;

    fmts = av_malloc_array(FF_ARRAY_ELEMS(supported_transfer_formats), حجم(*fmts));
    إذا (!fmts)
        أرجع AVERROR(ENOMEM);
    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_transfer_formats); i++)
        fmts[i] = supported_transfer_formats[i];

    *formats = fmts;

    أرجع 0;
}

ساكن فراغ amf_free_amfsurface(فراغ *opaque, uint8_t *داده)
{
    إذا(!!داده){
        AMFSurface *surface = (AMFSurface*)(داده);
        surface->pVtbl->Release(surface);
    }
}

ساكن صحيح amf_transfer_داده_مقصد(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)dst->داده[0];
    AMFPlane *plane;
    uint8_t  *dst_داده[4];
    صحيح       dst_linesize[4];
    صحيح       planes;
    صحيح       i;
    صحيح       res;
    صحيح w = FFMIN(dst->عرض,  src->عرض);
    صحيح h = FFMIN(dst->ارتفاع, src->ارتفاع);

    إذا (dst->hw_قابها_ctx->داده != (uint8_t *)ctx || src->format != ctx->sw_format)
        أرجع AVERROR(EINVAL);

    إذا (!surface) {
        AVHWDeviceContext   *hwdev_ctx = ctx->device_ctx;
        AVAMFDeviceContext  *amf_device_ctx = (AVAMFDeviceContext *)hwdev_ctx->hwctx;
        AMF_SURFACE_FORMAT  format = av_av_مقصد_amf_format(ctx->sw_format);
        res = amf_device_ctx->context->pVtbl->AllocSurface(amf_device_ctx->context, AMF_حافظه_HOST, format, dst->عرض, dst->ارتفاع, &surface);
        AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR(ENOMEM), "AllocSurface() failed  with error %d\n", res);
        dst->داده[0] = (uint8_t *)surface;
        dst->buf[1] = av_میانگیر_create((uint8_t *)surface, حجم(surface),
                                            amf_free_amfsurface,
                                            عدم,
                                            AV_میانگیر_FLAG_READONLY);
    AMF_RETURN_IF_FALSE(ctx, !!dst->buf[1], AVERROR(ENOMEM), "av_buffer_create for amf surface failed.");
    }

    planes = (صحيح)surface->pVtbl->Get_Planes_شمار(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(dst_داده));

    لكل (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        dst_داده[i] = plane->pVtbl->GetNative(plane);
        dst_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst_داده, dst_linesize,
                   src->داده, src->linesize, src->format,
                   w, h);

    أرجع 0;
}

ساكن صحيح amf_transfer_داده_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ثابت AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)src->داده[0];
    AMFPlane *plane;
    uint8_t  *src_داده[4];
    صحيح       src_linesize[4];
    صحيح       planes;
    صحيح       i;
    صحيح w = FFMIN(dst->عرض,  src->عرض);
    صحيح h = FFMIN(dst->ارتفاع, src->ارتفاع);
    صحيح ret;

    إذا (src->hw_قابها_ctx->داده != (uint8_t *)ctx || dst->format != ctx->sw_format)
        أرجع AVERROR(EINVAL);

    ret = surface->pVtbl->Convert(surface, AMF_حافظه_HOST);
    AMF_RETURN_IF_FALSE(ctx, ret == AMF_OK, AVERROR_UNKNOWN, "Convert(amf::AMF_MEMORY_HOST) failed with error %d\n", AVERROR_UNKNOWN);

    planes = (صحيح)surface->pVtbl->Get_Planes_شمار(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(src_داده));

    لكل (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        src_داده[i] = plane->pVtbl->GetNative(plane);
        src_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst->داده, dst->linesize,
                   src_داده, src_linesize, dst->format,
                   w, h);
    أرجع 0;
}



ساكن فراغ amf_device_uninit(AVHWDeviceContext *device_ctx)
{
    AVAMFDeviceContext *amf_ctx = device_ctx->hwctx;
    AMF_نتیجه          res = AMF_NOT_INITIALIZED;
    AMFTrace           *trace;

    إذا (amf_ctx->context) {
        amf_ctx->context->pVtbl->Terminate(amf_ctx->context);
        amf_ctx->context->pVtbl->Release(amf_ctx->context);
        amf_ctx->context = عدم;
    }

    إذا (amf_ctx->factory)
        res = amf_ctx->factory->pVtbl->GetTrace(amf_ctx->factory, &trace);

    إذا (res == AMF_OK) {
        trace->pVtbl->UnregisterWriter(trace, FFMPEG_AMF_WRITER_ID);
    }

    إذا(amf_ctx->library) {
        dlclose(amf_ctx->library);
        amf_ctx->library = عدم;
    }
    إذا (amf_ctx->trace_writer) {
        amf_writer_free(amf_ctx->trace_writer);
    }

    إذا (amf_ctx->قفل_ctx == amf_قفل_default) {
        ff_mutex_destroy((AVMutex*)amf_ctx->قفل_ctx);
        av_freep(&amf_ctx->قفل_ctx);
        amf_ctx->قفل_2 = عدم;
        amf_ctx->unlock = عدم;
    }

    amf_ctx->نسخه = 0;
}

تعداد AMF_حافظه_TYPE av_amf_get_حافظه_type(AVAMFDeviceContext *amf_ctx)
{
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = عدم;
    AMFGuid guid1 = IID_AMFContext1();
    فراغ * device = عدم;

#اگر_تعریف_شده _WIN32
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
#پایان_اگر

    إذا (!amf_ctx)
        أرجع AMF_حافظه_UNKNOWN;

#اگر_تعریف_شده _WIN32
    إذا (AMF_IFACE_CALL(context, QueryInterface, &guid2, (فراغ**)&context2) == AMF_OK)
    {
        device = AMF_IFACE_CALL(context2, GetDX12Device, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);

        إذا (device)
            أرجع AMF_حافظه_DX12;
    }

    إذا (AMF_IFACE_CALL(context, GetDX11Device, AMF_DX11_1))
        أرجع AMF_حافظه_DX11;

    إذا (AMF_IFACE_CALL(context, GetDX9Device, AMF_DX9))
        أرجع AMF_حافظه_DX9;
#پایان_اگر

    إذا (AMF_IFACE_CALL(context, QueryInterface, &guid1, (فراغ**)&context1) != AMF_OK)
        أرجع AMF_حافظه_UNKNOWN;

    device = AMF_IFACE_CALL(context1, GetVulkanDevice);
    AMF_IFACE_CALL(context1, Release);
    إذا (device)
        أرجع AMF_حافظه_VULKAN;

    أرجع AMF_حافظه_UNKNOWN;
}

ساكن صحيح amf_device_init(AVHWDeviceContext *ctx)
{
    AVAMFDeviceContext *amf_ctx = ctx->hwctx;
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = عدم;
    AMFGuid guid1 = IID_AMFContext1();
    AMF_نتیجه res;

#اگر_تعریف_شده _WIN32
    AMFContext2 *context2 = عدم;
    ساكن ثابت AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#پایان_اگر

    إذا (!amf_ctx->قفل_2) {
        amf_ctx->قفل_ctx = av_mallocz(حجم(AVMutex));
        إذا (!amf_ctx->قفل_ctx) {
            أرجع AVERROR(ENOMEM);
        }
        ff_mutex_init((AVMutex*)amf_ctx->قفل_ctx, عدم);
        amf_ctx->قفل_2   = amf_قفل_default;
        amf_ctx->unlock = amf_unlock_default;
    }

    إذا (av_amf_get_حافظه_type(amf_ctx) != AMF_حافظه_UNKNOWN) {
        av_log(ctx, AV_LOG_VERBOSE, "AMF is already initialized, skipping init.\n");
        أرجع 0;
    }

#اگر_تعریف_شده _WIN32
    res = AMF_IFACE_CALL(context, InitDX11, عدم, AMF_DX11_1);
    إذا (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D11.\n");
        أرجع 0;
    }

    res = AMF_IFACE_CALL(context, QueryInterface, &guid2, (فراغ**)&context2);
    إذا (res == AMF_OK) {
        res = AMF_IFACE_CALL(context2, InitDX12, عدم, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);
        إذا (res == AMF_OK) {
            av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D12.\n");
            أرجع 0;
        }
    } وإلا {
        av_log(ctx, AV_LOG_VERBOSE, "QueryInterface(AMFContext2) failed with error %d, trying older D3D APIs...\n", res);
    }

    res = AMF_IFACE_CALL(context, InitDX9, عدم);
    إذا (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D9.\n");
        أرجع 0;
    }

    av_log(ctx, AV_LOG_WARNING, "AMF failed to initialize with any of supported versions of DirectX, trying Vulkan instead...\n");
#پایان_اگر

    res = AMF_IFACE_CALL(context, QueryInterface, &guid1, (فراغ**)&context1);
    إذا (res != AMF_OK) {
        av_log(ctx, AV_LOG_ERROR, "QueryInterface(AMFContext1) failed with error %d\n", res);
        أرجع AVERROR_UNKNOWN;
    }

    res = AMF_IFACE_CALL(context1, InitVulkan, عدم);
    AMF_IFACE_CALL(context1, Release);

    إذا (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via Vulkan.\n");
    } وإلا {
        إذا (res == AMF_NOT_SUPPORTED)
            av_log(ctx, AV_LOG_ERROR, "AMF via Vulkan is not supported on the given device.\n");
        وإلا
            av_log(ctx, AV_LOG_ERROR, "Failed to initialize AMF via Vulkan, error %d\n", res);

        أرجع AVERROR(ENOSYS);
    }

    أرجع 0;
}

ساكن صحيح amf_بارگیری_library(AVAMFDeviceContext* amf_ctx,  فراغ* avcl)
{
    AMFInit_Fn         init_fun;
    AMFQuery_نسخه_Fn نسخه_fun;
    AMF_نتیجه         res;

    amf_ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(avcl, amf_ctx->library != عدم,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(amf_ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, init_fun != عدم, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    نسخه_fun = (AMFQuery_نسخه_Fn)dlsym(amf_ctx->library, AMF_QUERY_نسخه_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, نسخه_fun != عدم, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_نسخه_FUNCTION_NAME);

    amf_uint64 نسخه;
    res = نسخه_fun(&نسخه);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_نسخه_FUNCTION_NAME, res);
    amf_ctx->نسخه = نسخه;
    res = init_fun(AMF_پر_نسخه, &amf_ctx->factory);
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
    إذا ((ret = amf_بارگیری_library(ctx, device_ctx)) == 0) {
        ret = ctx->factory->pVtbl->GetTrace(ctx->factory, &trace);
        إذا (ret == AMF_OK) {
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
            إذا(ctx->نسخه == AMF_MAKE_پر_نسخه(1, 4, 35, 0)){// get around a bug in trace in AMF runtime driver 24.20
                level_amf = AMF_TRACE_WARNING;
            }

            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_CONSOLE, 0);
            trace->pVtbl->مجموعه_Global_Level(trace, level_amf);

            // connect AMF logger to av_log
            ctx->trace_writer = amf_writer_alloc(device_ctx);
            trace->pVtbl->ثبات_Writer(trace, FFMPEG_AMF_WRITER_ID, (AMFTraceWriter*)ctx->trace_writer, 1);
            trace->pVtbl->مجموعه_Writer_Level(trace, FFMPEG_AMF_WRITER_ID, level_amf);
            trace->pVtbl->EnableWriter(trace, FFMPEG_AMF_WRITER_ID, enable_log);
            trace->pVtbl->مجموعه_Writer_Level(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, level_amf);
            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, enable_log);
        }


        ret = ctx->factory->pVtbl->CreateContext(ctx->factory, &ctx->context);
        إذا (ret == AMF_OK) {
            AMF_تخصیص_بده_PROPERTY_INT64(ret, ctx->context, L"DeviceSurfaceCacheSize", 50 );
            أرجع 0;
        }
        av_log(device_ctx, AV_LOG_ERROR, "CreateContext() failed with error %d.\n", ret);
    }
    amf_device_uninit(device_ctx);
    أرجع ret;
}

#إذا CONFIG_DXVA2
ساكن صحيح amf_init_from_dxva2_device(AVAMFDeviceContext * amf_ctx, AVHWDeviceContext *فرزند_device_ctx)
{
    AVDXVA2DeviceContext *hwctx = فرزند_device_ctx->hwctx;
    IDirect3DDevice9    *device;
    HANDLE              device_handle;
    HRESULT             hr;
    AMF_نتیجه          res;
    صحيح ret;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &device_handle);
    إذا (FAILED(hr)) {
        av_log(فرزند_device_ctx, AV_LOG_ERROR, "Failed to open device handle for Direct3D9 device: %lx.\n", (بیعلامت دراز)hr);
        أرجع AVERROR_EXTERNAL;
    }

    hr = IDirect3_DDevice_Manager9_قفل_Device(hwctx->devmgr, device_handle, &device, FALSE);
    إذا (SUCCEEDED(hr)) {
        IDirect3DDeviceManager9_UnlockDevice(hwctx->devmgr, device_handle, FALSE);
        ret = 0;
    } وإلا {
        av_log(فرزند_device_ctx, AV_LOG_ERROR, "Failed to lock device handle for Direct3D9 device: %lx.\n", (بیعلامت دراز)hr);
        ret = AVERROR_EXTERNAL;
    }


    IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, device_handle);

    إذا (ret < 0)
        أرجع ret;

    res = amf_ctx->context->pVtbl->InitDX9(amf_ctx->context, device);

    IDirect3DDevice9_Release(device);

    إذا (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        إذا (res == AMF_NOT_SUPPORTED)
            av_log(فرزند_device_ctx, AV_LOG_ERROR, "AMF via D3D9 is not supported on the given device.\n");
        وإلا
            av_log(فرزند_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on given D3D9 device: %d.\n", res);
        أرجع AVERROR(ENODEV);
    }
    av_log(فرزند_device_ctx, AV_LOG_INFO, "AMF via DXVA2.\n");
    أرجع 0;
}
#پایان_اگر

#إذا CONFIG_D3D11VA
ساكن صحيح amf_init_from_d3d11_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *فرزند_device_ctx)
{
    AMF_نتیجه res;
    AVD3D11VADeviceContext *hwctx = فرزند_device_ctx->hwctx;
    res = amf_ctx->context->pVtbl->InitDX11(amf_ctx->context, hwctx->device, AMF_DX11_1);
    إذا (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        إذا (res == AMF_NOT_SUPPORTED)
            av_log(فرزند_device_ctx, AV_LOG_ERROR, "AMF via D3D11 is not supported on the given device.\n");
        وإلا
            av_log(فرزند_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D11 device: %d.\n", res);
        أرجع AVERROR(ENODEV);
    }
    av_log(فرزند_device_ctx, AV_LOG_INFO, "AMF via D3D11.\n");
    hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    أرجع 0;
}
#پایان_اگر

#إذا CONFIG_D3D12VA
ساكن صحيح amf_init_from_d3d12_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *فرزند_device_ctx)
{
    AVD3D12VADeviceContext *hwctx = فرزند_device_ctx->hwctx;
    AMF_نتیجه res;
    AMFContext2 *context2 = عدم;
    AMFGuid guid = IID_AMFContext2();
    res = amf_ctx->context->pVtbl->QueryInterface(amf_ctx->context, &guid, (فراغ**)&context2);
    AMF_RETURN_IF_FALSE(فرزند_device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "CreateContext2() failed with error %d\n", res);
    res = context2->pVtbl->InitDX12(context2, hwctx->device, AMF_DX12);
    context2->pVtbl->Release(context2);
    إذا (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        إذا (res == AMF_NOT_SUPPORTED)
            av_log(فرزند_device_ctx, AV_LOG_ERROR, "AMF via D3D12 is not supported on the given device.\n");
        وإلا
            av_log(فرزند_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D12 device: %d.\n", res);
        أرجع AVERROR(ENODEV);
    }
    av_log(فرزند_device_ctx, AV_LOG_INFO, "AMF via D3D12.\n");
    أرجع 0;
}
#پایان_اگر


ساكن صحيح amf_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *فرزند_device_ctx, AVDictionary *opts,
                              صحيح flags)
{
#إذا CONFIG_DXVA2 || CONFIG_D3D11VA || CONFIG_D3D12VA
    AVAMFDeviceContext        *amf_ctx = device_ctx->hwctx;
#پایان_اگر
    صحيح ret;

    ret = amf_device_create(device_ctx, "", opts, flags);
    إذا(ret < 0)
        أرجع ret;

    بدل (فرزند_device_ctx->type) {
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        أرجع amf_init_from_dxva2_device(amf_ctx, فرزند_device_ctx);
#پایان_اگر
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        أرجع amf_init_from_d3d11_device(amf_ctx, فرزند_device_ctx);
#پایان_اگر
#إذا CONFIG_D3D12VA
    حالة AV_HWDEVICE_TYPE_D3D12VA:
        أرجع amf_init_from_d3d12_device(amf_ctx, فرزند_device_ctx);
#پایان_اگر
    افتراضي:
        av_log(فرزند_device_ctx, AV_LOG_ERROR, "AMF initialisation from a %s device is not supported.\n",
               av_hwdevice_get_type_name(فرزند_device_ctx->type));
        أرجع AVERROR(ENOSYS);
    }
}

ساكن فراغ amf_unmap_قاب(av_استفادهنشده AVHWFramesContext *استفادهنشده, HWMapDescriptor *hwmap)
{
    AMFSurface1 *surface1 = hwmap->priv;
    AMF_IFACE_CALL(surface1, Unmap);
    AMF_IFACE_CALL(surface1, Release);
}

ساكن صحيح amf_map_قاب(AVHWFramesContext *device_ctx, AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AMFSurface *surface = (AMFSurface *)src->داده[0];
    AMFSurface1 *surface1 = عدم;
    size_t *linesizes = عدم;
    uint8_t **map = عدم;
    صحيح amf_mem_flags = AMF_حافظه_CPU_NONE;
    ثابت AMFGuid guid = IID_AMFSurface1();
    AMF_نتیجه res = AMF_FAIL;
    size_t plane_شمار = 0;
    صحيح ret = -1;

    AMF_RETURN_IF_FALSE(device_ctx, surface != عدم, AVERROR(EINVAL) , "Source surface is null");

    res = AMF_IFACE_CALL(surface, QueryInterface, &guid, (فراغ**)&surface1);
    AMF_RETURN_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "QueryInterface(AMFSurface1) failed with error %d\n", res);

    إذا (flags & AV_HWFRAME_MAP_READ)
        amf_mem_flags |= AMF_حافظه_CPU_READ;

    إذا (flags & AV_HWFRAME_MAP_WRITE)
        amf_mem_flags |= AMF_حافظه_CPU_WRITE;

    plane_شمار = AMF_IFACE_CALL(surface, Get_Planes_شمار);
    linesizes = av_malloc_array(حجم(size_t), plane_شمار);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, linesizes, AVERROR(ENOMEM), "Unable to allocate line sizes array\n");

    map = av_malloc_array(حجم(uint8_t *), plane_شمار);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, map, AVERROR(ENOMEM), "Unable to allocate mapping buffer\n");

    dst->format = av_amf_مقصد_av_format(AMF_IFACE_CALL(surface, GetFormat));

    res = AMF_IFACE_CALL(surface1, Map, amf_mem_flags, plane_شمار, linesizes, (فراغ**)map);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "AMFSurface1->Map() failed with error %d\n", res);

    ret = ff_hwframe_map_create(src->hw_قابها_ctx, dst, src, &amf_unmap_قاب, surface1);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, ret >= 0, ret, "ff_hwframe_map_create failed with error %d\n", ret);

    dst->عرض  = src->عرض;
    dst->ارتفاع = src->ارتفاع;
    av_قاب_copy_props(dst, src);

    // The dst frame is no longer a hardware frame, from the perspective of any dst frame consumer.
    av_میانگیر_unref(&dst->hw_قابها_ctx);

    لكل (صحيح plane = 0; plane < plane_شمار; ++plane)
    {
        dst->داده[plane] = map[plane];
        dst->linesize[plane] = linesizes[plane];
    }

fail:
    إذا (map)
        av_free(map);

    إذا (linesizes)
        av_free(linesizes);

    إذا (ret < 0 && surface1 != عدم)
        AMF_IFACE_CALL(surface1, Release);

    أرجع ret;
}

ثابت HWContextType ff_hwcontext_type_amf = {
    .type                 = AV_HWDEVICE_TYPE_AMF,
    .name                 = "AMF",

    .device_hwctx_اندازه    = حجم(AVAMFDeviceContext),
    .قابها_hwctx_اندازه    = حجم(AMFFramesContext),

    .device_create        = amf_device_create,
    .device_derive        = amf_device_derive,
    .device_init          = amf_device_init,
    .device_uninit        = amf_device_uninit,
    .قابها_get_constraints = amf_قابها_get_constraints,
    .قابها_init          = amf_قابها_init,
    .قابها_get_میانگیر    = amf_get_میانگیر,
    .transfer_get_formats = amf_transfer_get_formats,
    .transfer_داده_مقصد     = amf_transfer_داده_مقصد,
    .transfer_داده_from   = amf_transfer_داده_from,
    .map_from             = amf_map_قاب,

    .pix_fmts             = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_AMF_SURFACE, AV_PIX_FMT_NONE },
};
