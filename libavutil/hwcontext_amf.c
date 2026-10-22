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
#جے_انت
#إذا CONFIG_D3D11VA
#ضمن "libavutil/hwcontext_d3d11va.h"
#جے_انت
#إذا CONFIG_D3D12VA
#ضمن "libavutil/hwcontext_d3d12va.h"
#جے_انت
#إذا CONFIG_DXVA2
#تعریف_کرو COBJMACROS
#ضمن "libavutil/hwcontext_dxva2.h"
#جے_انت
#جے_تعریف_شدہ _WIN32
#ضمن "compat/w32dlfcn.h"
#وإلا
#ضمن <dlfcn.h>
#جے_انت
#تعریف_کرو FFMPEG_AMF_WRITER_ID L"ffmpeg_amf"

ساكن فراغ amf_جندرا_default(فراغ *opaque)
{
    ff_mutex_جندرا((AVMutex*)opaque);
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
    ثابت wchar_t *scope, ثابت wchar_t *سنیہا)
{
    AmfTraceWriter *tracer = (AmfTraceWriter*)pThis;
    av_log(tracer->avctx, AV_LOG_DEBUG, "%ls: %ls", scope, سنیہا); // \n is provided from AMF
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

تعداد AMF_SURFACE_FORMAT av_av_منزل_amf_format(تعداد AVPixelFormat fmt)
{
    صحيح i;
    لكل (i = 0; i < amf_countof(format_map); i++) {
        إذا (format_map[i].av_format == fmt) {
            أرجع format_map[i].amf_format;
        }
    }
    أرجع AMF_SURFACE_UNKNOWN;
}

تعداد AVPixelFormat av_amf_منزل_av_format(تعداد AMF_SURFACE_FORMAT fmt)
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
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_بھریا_601;
        } وإلا {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_601;
        }
        اكسر;
    حالة AVCOL_SPC_BT709:
        إذا (color_range == AVCOL_RANGE_JPEG) {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_بھریا_709;
        } وإلا {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_709;
        }
        اكسر;
    حالة AVCOL_SPC_BT2020_NCL:
    حالة AVCOL_SPC_BT2020_CL:
        إذا (color_range == AVCOL_RANGE_JPEG) {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_بھریا_2020;
        } وإلا {
            أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_2020;
        }
        اكسر;

    افتراضي:
        أرجع AMF_VIDEO_CONVERTER_COLOR_PROFILE_UNKNOWN;
    }
}

صحيح av_amf_display_mastering_meta_منزل_hdrmeta(ثابت AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta)
{
    إذا (!display_meta || !hdrmeta)
        أرجع AVERROR(EINVAL);

    إذا (display_meta->has_luminance) {
        ثابت بنانشانی صحيح luma_den = 10000;
        hdrmeta->maxMasteringLuminance =
            (amf_uint32)(luma_den * av_q2d(display_meta->max_luminance));
        hdrmeta->minMasteringLuminance =
            FFMIN((amf_uint32)(luma_den * av_q2d(display_meta->min_luminance)), hdrmeta->maxMasteringLuminance);
    }

    إذا (display_meta->has_primaries) {
        ثابت بنانشانی صحيح chroma_den = 50000;
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
        hdrmeta->white_نقطہ[0] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_نقطہ_2[0])), chroma_den);
        hdrmeta->white_نقطہ[1] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_نقطہ_2[1])), chroma_den);
    }

    أرجع 0;
}

صحيح av_amf_light_metadata_منزل_hdrmeta(ثابت AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta)
{
    إذا (!light_meta || !hdrmeta)
        أرجع AVERROR(EINVAL);

    hdrmeta->maxContentLightLevel = (amf_uint16)light_meta->MaxCLL;
    hdrmeta->max_چوکھٹا_اوسطن_Light_Level = (amf_uint16)light_meta->MaxFALL;

    أرجع 0;
}

صحيح av_amf_کڈھو_hdr_metadata(ثابت AVFrame *چوکھٹا, AMFHDRMetadata *hdrmeta)
{
    AVFrame_Side_انکڑے *sidedata;
    AVContentLightMetadata *content_light = عدم;
    AVMasteringDisplayMetadata *mastering_display = عدم;

    إذا (!چوکھٹا || !hdrmeta)
        أرجع AVERROR(EINVAL);

    sidedata = av_چوکھٹا_get_side_انکڑے(چوکھٹا, AV_چوکھٹا_انکڑے_MASTERING_DISPLAY_METADATA);
    إذا (sidedata) {
        mastering_display = (AVMasteringDisplayMetadata *)sidedata->انکڑے;
        إذا (av_amf_display_mastering_meta_منزل_hdrmeta(mastering_display, hdrmeta) != 0)
            mastering_display = عدم;
    }

    sidedata = av_چوکھٹا_get_side_انکڑے(چوکھٹا, AV_چوکھٹا_انکڑے_CONTENT_LIGHT_LEVEL);
    إذا (sidedata) {
        content_light = (AVContentLightMetadata *)sidedata->انکڑے;
        إذا (av_amf_light_metadata_منزل_hdrmeta(content_light, hdrmeta) != 0)
            content_light = عدم;
    }

    إذا (!mastering_display && !content_light)
        أرجع AVERROR(ENODATA);

    أرجع 0;
}

صحيح av_amf_attach_hdr_metadata(AVFrame *چوکھٹا, ثابت AMFHDRMetadata *hdrmeta) {
    إذا (!hdrmeta || !چوکھٹا)
        أرجع AVERROR(EINVAL);

    AVMasteringDisplayMetadata *mastering =
        av_mastering_display_metadata_create_side_انکڑے(چوکھٹا);
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

    mastering->white_نقطہ_2[0] = av_make_q(hdrmeta->white_نقطہ[0], chroma_den);
    mastering->white_نقطہ_2[1] = av_make_q(hdrmeta->white_نقطہ[1], chroma_den);

    mastering->max_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);
    mastering->min_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);

    mastering->has_luminance = 1;
    mastering->has_primaries = 1;
    إذا (hdrmeta->maxContentLightLevel) {
      AVContentLightMetadata *light =
          av_content_light_metadata_create_side_انکڑے(چوکھٹا);

      إذا (!light)
        أرجع AVERROR(ENOMEM);

      light->MaxCLL = hdrmeta->maxContentLightLevel;
      light->MaxFALL = hdrmeta->max_چوکھٹا_اوسطن_Light_Level;
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
#جے_انت
#إذا CONFIG_D3D12VA
    AV_PIX_FMT_D3D12,
#جے_انت
#إذا CONFIG_DXVA2
    AV_PIX_FMT_DXVA2_VLD,
#جے_انت
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

ساكن صحيح amf_چوکھٹے_get_constraints(AVHWDeviceContext *ctx,
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

ساكن فراغ amf_dummy_free(فراغ *opaque, uint8_t *انکڑے)
{

}

ساكن AVBufferRef *amf_pool_alloc(فراغ *opaque, size_t ناپ)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)opaque;
    AVBufferRef *buf;

    buf = av_بفر_create(عدم, 0, amf_dummy_free, hwfc, AV_بفر_FLAG_READONLY);
    إذا (!buf) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create buffer for AMF context.\n");
        أرجع عدم;
    }
    أرجع buf;
}

ساكن صحيح amf_چوکھٹے_init(AVHWFramesContext *ctx)
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

    ffhwframesctx(ctx)->pool_اندرونی =
            av_بفر_pool_init2(حجم(AMFSurface), ctx,
                                 &amf_pool_alloc, عدم);

    أرجع 0;
}


ساكن صحيح amf_get_بفر(AVHWFramesContext *ctx, AVFrame *چوکھٹا)
{
    چوکھٹا->buf[0] = av_بفر_pool_get(ctx->pool);
    إذا (!چوکھٹا->buf[0])
        أرجع AVERROR(ENOMEM);

    چوکھٹا->انکڑے[0] = چوکھٹا->buf[0]->انکڑے;
    چوکھٹا->format  = AV_PIX_FMT_AMF_SURFACE;
    چوکھٹا->چوڑائی   = ctx->چوڑائی;
    چوکھٹا->اچائی  = ctx->اچائی;
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

ساكن فراغ amf_free_amfsurface(فراغ *opaque, uint8_t *انکڑے)
{
    إذا(!!انکڑے){
        AMFSurface *surface = (AMFSurface*)(انکڑے);
        surface->pVtbl->Release(surface);
    }
}

ساكن صحيح amf_transfer_انکڑے_منزل(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)dst->انکڑے[0];
    AMFPlane *plane;
    uint8_t  *dst_انکڑے[4];
    صحيح       dst_linesize[4];
    صحيح       planes;
    صحيح       i;
    صحيح       res;
    صحيح w = FFMIN(dst->چوڑائی,  src->چوڑائی);
    صحيح h = FFMIN(dst->اچائی, src->اچائی);

    إذا (dst->hw_چوکھٹے_ctx->انکڑے != (uint8_t *)ctx || src->format != ctx->sw_format)
        أرجع AVERROR(EINVAL);

    إذا (!surface) {
        AVHWDeviceContext   *hwdev_ctx = ctx->device_ctx;
        AVAMFDeviceContext  *amf_device_ctx = (AVAMFDeviceContext *)hwdev_ctx->hwctx;
        AMF_SURFACE_FORMAT  format = av_av_منزل_amf_format(ctx->sw_format);
        res = amf_device_ctx->context->pVtbl->AllocSurface(amf_device_ctx->context, AMF_حافظہ_HOST, format, dst->چوڑائی, dst->اچائی, &surface);
        AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR(ENOMEM), "AllocSurface() failed  with error %d\n", res);
        dst->انکڑے[0] = (uint8_t *)surface;
        dst->buf[1] = av_بفر_create((uint8_t *)surface, حجم(surface),
                                            amf_free_amfsurface,
                                            عدم,
                                            AV_بفر_FLAG_READONLY);
    AMF_RETURN_IF_FALSE(ctx, !!dst->buf[1], AVERROR(ENOMEM), "av_buffer_create for amf surface failed.");
    }

    planes = (صحيح)surface->pVtbl->Get_Planes_گنتی(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(dst_انکڑے));

    لكل (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        dst_انکڑے[i] = plane->pVtbl->GetNative(plane);
        dst_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst_انکڑے, dst_linesize,
                   src->انکڑے, src->linesize, src->format,
                   w, h);

    أرجع 0;
}

ساكن صحيح amf_transfer_انکڑے_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ثابت AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)src->انکڑے[0];
    AMFPlane *plane;
    uint8_t  *src_انکڑے[4];
    صحيح       src_linesize[4];
    صحيح       planes;
    صحيح       i;
    صحيح w = FFMIN(dst->چوڑائی,  src->چوڑائی);
    صحيح h = FFMIN(dst->اچائی, src->اچائی);
    صحيح ret;

    إذا (src->hw_چوکھٹے_ctx->انکڑے != (uint8_t *)ctx || dst->format != ctx->sw_format)
        أرجع AVERROR(EINVAL);

    ret = surface->pVtbl->Convert(surface, AMF_حافظہ_HOST);
    AMF_RETURN_IF_FALSE(ctx, ret == AMF_OK, AVERROR_UNKNOWN, "Convert(amf::AMF_MEMORY_HOST) failed with error %d\n", AVERROR_UNKNOWN);

    planes = (صحيح)surface->pVtbl->Get_Planes_گنتی(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(src_انکڑے));

    لكل (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        src_انکڑے[i] = plane->pVtbl->GetNative(plane);
        src_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst->انکڑے, dst->linesize,
                   src_انکڑے, src_linesize, dst->format,
                   w, h);
    أرجع 0;
}



ساكن فراغ amf_device_uninit(AVHWDeviceContext *device_ctx)
{
    AVAMFDeviceContext *amf_ctx = device_ctx->hwctx;
    AMF_نتیجہ          res = AMF_NOT_INITIALIZED;
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

    إذا (amf_ctx->جندرا_ctx == amf_جندرا_default) {
        ff_mutex_destroy((AVMutex*)amf_ctx->جندرا_ctx);
        av_freep(&amf_ctx->جندرا_ctx);
        amf_ctx->جندرا = عدم;
        amf_ctx->unlock = عدم;
    }

    amf_ctx->نسخہ = 0;
}

تعداد AMF_حافظہ_TYPE av_amf_get_حافظہ_type(AVAMFDeviceContext *amf_ctx)
{
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = عدم;
    AMFGuid guid1 = IID_AMFContext1();
    فراغ * device = عدم;

#جے_تعریف_شدہ _WIN32
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
#جے_انت

    إذا (!amf_ctx)
        أرجع AMF_حافظہ_UNKNOWN;

#جے_تعریف_شدہ _WIN32
    إذا (AMF_IFACE_CALL(context, QueryInterface, &guid2, (فراغ**)&context2) == AMF_OK)
    {
        device = AMF_IFACE_CALL(context2, GetDX12Device, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);

        إذا (device)
            أرجع AMF_حافظہ_DX12;
    }

    إذا (AMF_IFACE_CALL(context, GetDX11Device, AMF_DX11_1))
        أرجع AMF_حافظہ_DX11;

    إذا (AMF_IFACE_CALL(context, GetDX9Device, AMF_DX9))
        أرجع AMF_حافظہ_DX9;
#جے_انت

    إذا (AMF_IFACE_CALL(context, QueryInterface, &guid1, (فراغ**)&context1) != AMF_OK)
        أرجع AMF_حافظہ_UNKNOWN;

    device = AMF_IFACE_CALL(context1, GetVulkanDevice);
    AMF_IFACE_CALL(context1, Release);
    إذا (device)
        أرجع AMF_حافظہ_VULKAN;

    أرجع AMF_حافظہ_UNKNOWN;
}

ساكن صحيح amf_device_init(AVHWDeviceContext *ctx)
{
    AVAMFDeviceContext *amf_ctx = ctx->hwctx;
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = عدم;
    AMFGuid guid1 = IID_AMFContext1();
    AMF_نتیجہ res;

#جے_تعریف_شدہ _WIN32
    AMFContext2 *context2 = عدم;
    ساكن ثابت AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#جے_انت

    إذا (!amf_ctx->جندرا) {
        amf_ctx->جندرا_ctx = av_mallocz(حجم(AVMutex));
        إذا (!amf_ctx->جندرا_ctx) {
            أرجع AVERROR(ENOMEM);
        }
        ff_mutex_init((AVMutex*)amf_ctx->جندرا_ctx, عدم);
        amf_ctx->جندرا   = amf_جندرا_default;
        amf_ctx->unlock = amf_unlock_default;
    }

    إذا (av_amf_get_حافظہ_type(amf_ctx) != AMF_حافظہ_UNKNOWN) {
        av_log(ctx, AV_LOG_VERBOSE, "AMF is already initialized, skipping init.\n");
        أرجع 0;
    }

#جے_تعریف_شدہ _WIN32
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
#جے_انت

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

ساكن صحيح amf_لدو_library(AVAMFDeviceContext* amf_ctx,  فراغ* avcl)
{
    AMFInit_Fn         init_fun;
    AMFQuery_نسخہ_Fn نسخہ_fun;
    AMF_نتیجہ         res;

    amf_ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(avcl, amf_ctx->library != عدم,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(amf_ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, init_fun != عدم, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    نسخہ_fun = (AMFQuery_نسخہ_Fn)dlsym(amf_ctx->library, AMF_QUERY_نسخہ_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, نسخہ_fun != عدم, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_نسخہ_FUNCTION_NAME);

    amf_uint64 نسخہ;
    res = نسخہ_fun(&نسخہ);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_نسخہ_FUNCTION_NAME, res);
    amf_ctx->نسخہ = نسخہ;
    res = init_fun(AMF_بھریا_نسخہ, &amf_ctx->factory);
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
    إذا ((ret = amf_لدو_library(ctx, device_ctx)) == 0) {
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
            إذا(ctx->نسخہ == AMF_MAKE_بھریا_نسخہ(1, 4, 35, 0)){// get around a bug in trace in AMF runtime driver 24.20
                level_amf = AMF_TRACE_WARNING;
            }

            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_CONSOLE, 0);
            trace->pVtbl->سیٹ_Global_Level(trace, level_amf);

            // connect AMF logger to av_log
            ctx->trace_writer = amf_writer_alloc(device_ctx);
            trace->pVtbl->رجسٹر_Writer(trace, FFMPEG_AMF_WRITER_ID, (AMFTraceWriter*)ctx->trace_writer, 1);
            trace->pVtbl->سیٹ_Writer_Level(trace, FFMPEG_AMF_WRITER_ID, level_amf);
            trace->pVtbl->EnableWriter(trace, FFMPEG_AMF_WRITER_ID, enable_log);
            trace->pVtbl->سیٹ_Writer_Level(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, level_amf);
            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, enable_log);
        }


        ret = ctx->factory->pVtbl->CreateContext(ctx->factory, &ctx->context);
        إذا (ret == AMF_OK) {
            AMF_سونپو_PROPERTY_INT64(ret, ctx->context, L"DeviceSurfaceCacheSize", 50 );
            أرجع 0;
        }
        av_log(device_ctx, AV_LOG_ERROR, "CreateContext() failed with error %d.\n", ret);
    }
    amf_device_uninit(device_ctx);
    أرجع ret;
}

#إذا CONFIG_DXVA2
ساكن صحيح amf_init_from_dxva2_device(AVAMFDeviceContext * amf_ctx, AVHWDeviceContext *بچہ_device_ctx)
{
    AVDXVA2DeviceContext *hwctx = بچہ_device_ctx->hwctx;
    IDirect3DDevice9    *device;
    HANDLE              device_handle;
    HRESULT             hr;
    AMF_نتیجہ          res;
    صحيح ret;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &device_handle);
    إذا (FAILED(hr)) {
        av_log(بچہ_device_ctx, AV_LOG_ERROR, "Failed to open device handle for Direct3D9 device: %lx.\n", (بنانشانی لما)hr);
        أرجع AVERROR_EXTERNAL;
    }

    hr = IDirect3_DDevice_Manager9_جندرا_Device(hwctx->devmgr, device_handle, &device, FALSE);
    إذا (SUCCEEDED(hr)) {
        IDirect3DDeviceManager9_UnlockDevice(hwctx->devmgr, device_handle, FALSE);
        ret = 0;
    } وإلا {
        av_log(بچہ_device_ctx, AV_LOG_ERROR, "Failed to lock device handle for Direct3D9 device: %lx.\n", (بنانشانی لما)hr);
        ret = AVERROR_EXTERNAL;
    }


    IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, device_handle);

    إذا (ret < 0)
        أرجع ret;

    res = amf_ctx->context->pVtbl->InitDX9(amf_ctx->context, device);

    IDirect3DDevice9_Release(device);

    إذا (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        إذا (res == AMF_NOT_SUPPORTED)
            av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF via D3D9 is not supported on the given device.\n");
        وإلا
            av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on given D3D9 device: %d.\n", res);
        أرجع AVERROR(ENODEV);
    }
    av_log(بچہ_device_ctx, AV_LOG_INFO, "AMF via DXVA2.\n");
    أرجع 0;
}
#جے_انت

#إذا CONFIG_D3D11VA
ساكن صحيح amf_init_from_d3d11_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *بچہ_device_ctx)
{
    AMF_نتیجہ res;
    AVD3D11VADeviceContext *hwctx = بچہ_device_ctx->hwctx;
    res = amf_ctx->context->pVtbl->InitDX11(amf_ctx->context, hwctx->device, AMF_DX11_1);
    إذا (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        إذا (res == AMF_NOT_SUPPORTED)
            av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF via D3D11 is not supported on the given device.\n");
        وإلا
            av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D11 device: %d.\n", res);
        أرجع AVERROR(ENODEV);
    }
    av_log(بچہ_device_ctx, AV_LOG_INFO, "AMF via D3D11.\n");
    hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    أرجع 0;
}
#جے_انت

#إذا CONFIG_D3D12VA
ساكن صحيح amf_init_from_d3d12_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *بچہ_device_ctx)
{
    AVD3D12VADeviceContext *hwctx = بچہ_device_ctx->hwctx;
    AMF_نتیجہ res;
    AMFContext2 *context2 = عدم;
    AMFGuid guid = IID_AMFContext2();
    res = amf_ctx->context->pVtbl->QueryInterface(amf_ctx->context, &guid, (فراغ**)&context2);
    AMF_RETURN_IF_FALSE(بچہ_device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "CreateContext2() failed with error %d\n", res);
    res = context2->pVtbl->InitDX12(context2, hwctx->device, AMF_DX12);
    context2->pVtbl->Release(context2);
    إذا (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        إذا (res == AMF_NOT_SUPPORTED)
            av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF via D3D12 is not supported on the given device.\n");
        وإلا
            av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D12 device: %d.\n", res);
        أرجع AVERROR(ENODEV);
    }
    av_log(بچہ_device_ctx, AV_LOG_INFO, "AMF via D3D12.\n");
    أرجع 0;
}
#جے_انت


ساكن صحيح amf_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *بچہ_device_ctx, AVDictionary *opts,
                              صحيح flags)
{
#إذا CONFIG_DXVA2 || CONFIG_D3D11VA || CONFIG_D3D12VA
    AVAMFDeviceContext        *amf_ctx = device_ctx->hwctx;
#جے_انت
    صحيح ret;

    ret = amf_device_create(device_ctx, "", opts, flags);
    إذا(ret < 0)
        أرجع ret;

    بدل (بچہ_device_ctx->type) {
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        أرجع amf_init_from_dxva2_device(amf_ctx, بچہ_device_ctx);
#جے_انت
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        أرجع amf_init_from_d3d11_device(amf_ctx, بچہ_device_ctx);
#جے_انت
#إذا CONFIG_D3D12VA
    حالة AV_HWDEVICE_TYPE_D3D12VA:
        أرجع amf_init_from_d3d12_device(amf_ctx, بچہ_device_ctx);
#جے_انت
    افتراضي:
        av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF initialisation from a %s device is not supported.\n",
               av_hwdevice_get_type_name(بچہ_device_ctx->type));
        أرجع AVERROR(ENOSYS);
    }
}

ساكن فراغ amf_unmap_چوکھٹا(av_بن_ورتیا AVHWFramesContext *بن_ورتیا, HWMapDescriptor *hwmap)
{
    AMFSurface1 *surface1 = hwmap->priv;
    AMF_IFACE_CALL(surface1, Unmap);
    AMF_IFACE_CALL(surface1, Release);
}

ساكن صحيح amf_map_چوکھٹا(AVHWFramesContext *device_ctx, AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AMFSurface *surface = (AMFSurface *)src->انکڑے[0];
    AMFSurface1 *surface1 = عدم;
    size_t *linesizes = عدم;
    uint8_t **map = عدم;
    صحيح amf_mem_flags = AMF_حافظہ_CPU_NONE;
    ثابت AMFGuid guid = IID_AMFSurface1();
    AMF_نتیجہ res = AMF_FAIL;
    size_t plane_گنتی = 0;
    صحيح ret = -1;

    AMF_RETURN_IF_FALSE(device_ctx, surface != عدم, AVERROR(EINVAL) , "Source surface is null");

    res = AMF_IFACE_CALL(surface, QueryInterface, &guid, (فراغ**)&surface1);
    AMF_RETURN_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "QueryInterface(AMFSurface1) failed with error %d\n", res);

    إذا (flags & AV_HWFRAME_MAP_READ)
        amf_mem_flags |= AMF_حافظہ_CPU_READ;

    إذا (flags & AV_HWFRAME_MAP_WRITE)
        amf_mem_flags |= AMF_حافظہ_CPU_WRITE;

    plane_گنتی = AMF_IFACE_CALL(surface, Get_Planes_گنتی);
    linesizes = av_malloc_array(حجم(size_t), plane_گنتی);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, linesizes, AVERROR(ENOMEM), "Unable to allocate line sizes array\n");

    map = av_malloc_array(حجم(uint8_t *), plane_گنتی);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, map, AVERROR(ENOMEM), "Unable to allocate mapping buffer\n");

    dst->format = av_amf_منزل_av_format(AMF_IFACE_CALL(surface, GetFormat));

    res = AMF_IFACE_CALL(surface1, Map, amf_mem_flags, plane_گنتی, linesizes, (فراغ**)map);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "AMFSurface1->Map() failed with error %d\n", res);

    ret = ff_hwframe_map_create(src->hw_چوکھٹے_ctx, dst, src, &amf_unmap_چوکھٹا, surface1);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, ret >= 0, ret, "ff_hwframe_map_create failed with error %d\n", ret);

    dst->چوڑائی  = src->چوڑائی;
    dst->اچائی = src->اچائی;
    av_چوکھٹا_copy_props(dst, src);

    // The dst frame is no longer a hardware frame, from the perspective of any dst frame consumer.
    av_بفر_unref(&dst->hw_چوکھٹے_ctx);

    لكل (صحيح plane = 0; plane < plane_گنتی; ++plane)
    {
        dst->انکڑے[plane] = map[plane];
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

    .device_hwctx_ناپ    = حجم(AVAMFDeviceContext),
    .چوکھٹے_hwctx_ناپ    = حجم(AMFFramesContext),

    .device_create        = amf_device_create,
    .device_derive        = amf_device_derive,
    .device_init          = amf_device_init,
    .device_uninit        = amf_device_uninit,
    .چوکھٹے_get_constraints = amf_چوکھٹے_get_constraints,
    .چوکھٹے_init          = amf_چوکھٹے_init,
    .چوکھٹے_get_بفر    = amf_get_بفر,
    .transfer_get_formats = amf_transfer_get_formats,
    .transfer_انکڑے_منزل     = amf_transfer_انکڑے_منزل,
    .transfer_انکڑے_from   = amf_transfer_انکڑے_from,
    .map_from             = amf_map_چوکھٹا,

    .pix_fmts             = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_AMF_SURFACE, AV_PIX_FMT_NONE },
};
