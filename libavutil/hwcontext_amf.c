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

#شامل "mem.h"
#شامل "buffer.h"
#شامل "pixfmt.h"
#شامل "pixdesc.h"
#شامل "imgutils.h"
#شامل "hwcontext.h"
#شامل "hwcontext_amf.h"
#شامل "hwcontext_internal.h"
#شامل "hwcontext_amf_internal.h"

#شامل "libavutil/thread.h"
#شامل "libavutil/avassert.h"

#شامل <AMF/core/Surface.h>
#شامل <AMF/core/Trace.h>

#اگر CONFIG_VULKAN
#شامل "hwcontext_vulkan.h"
#اگر_ختم
#اگر CONFIG_D3D11VA
#شامل "libavutil/hwcontext_d3d11va.h"
#اگر_ختم
#اگر CONFIG_D3D12VA
#شامل "libavutil/hwcontext_d3d12va.h"
#اگر_ختم
#اگر CONFIG_DXVA2
#تعریف_کرو COBJMACROS
#شامل "libavutil/hwcontext_dxva2.h"
#اگر_ختم
#اگر_تعریف_شدہ _WIN32
#شامل "compat/w32dlfcn.h"
#ورنہ
#شامل <dlfcn.h>
#اگر_ختم
#تعریف_کرو FFMPEG_AMF_WRITER_ID L"ffmpeg_amf"

ساکن خالی amf_تالا_default(خالی *opaque)
{
    ff_mutex_تالا((AVMutex*)opaque);
}

ساکن خالی amf_unlock_default(خالی *opaque)
{
    ff_mutex_unlock((AVMutex*)opaque);
}

قسمتعریف ساخت AmfTraceWriter {
    AMFTraceWriterVtbl *vtblp;
    خالی               *avctx;
    AMFTraceWriterVtbl  vtbl;
} AmfTraceWriter;

ساکن خالی AMF_CDECL_CALL AMFTraceWriter_Write(AMFTraceWriter *pThis,
    ثابت wchar_t *scope, ثابت wchar_t *پیغام_2)
{
    AmfTraceWriter *tracer = (AmfTraceWriter*)pThis;
    av_log(tracer->avctx, AV_LOG_DEBUG, "%ls: %ls", scope, پیغام_2); // \n is provided from AMF
}

ساکن خالی AMF_CDECL_CALL AMFTraceWriter_Flush(AMFTraceWriter *pThis)
{
}

ساکن AmfTraceWriter * amf_writer_alloc(خالی  *avctx)
{
    AmfTraceWriter * writer = av_mallocz(حجم(AmfTraceWriter));
    اگر (!writer)
        واپس تہی;

    writer->vtblp = &writer->vtbl;
    writer->vtblp->Write = AMFTraceWriter_Write;
    writer->vtblp->Flush = AMFTraceWriter_Flush;
    writer->avctx = avctx;

    واپس writer;
}

ساکن خالی amf_writer_free(خالی  *opaque)
{
    AmfTraceWriter *writer = (AmfTraceWriter *)opaque;
    av_freep(&writer);
}

/**
 * We still need AVHWFramesContext to utilize our hardware memory
 * otherwise, we will receive the error "HW format requires hw_frames_ctx to be non-NULL".
 * (libavfilter\buffersrc.c function query_formats)
*/
قسمتعریف ساخت {
    خالی *dummy;
} AMFFramesContext;

قسمتعریف ساخت AVAMFFormatMap {
    شمار AVPixelFormat       av_format;
    شمار AMF_SURFACE_FORMAT  amf_format;
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

شمار AMF_SURFACE_FORMAT av_av_مقصد_amf_format(شمار AVPixelFormat fmt)
{
    صحیح i;
    برائے (i = 0; i < amf_countof(format_map); i++) {
        اگر (format_map[i].av_format == fmt) {
            واپس format_map[i].amf_format;
        }
    }
    واپس AMF_SURFACE_UNKNOWN;
}

شمار AVPixelFormat av_amf_مقصد_av_format(شمار AMF_SURFACE_FORMAT fmt)
{
    صحیح i;
    برائے (i = 0; i < amf_countof(format_map); i++) {
        اگر (format_map[i].amf_format == fmt) {
            واپس format_map[i].av_format;
        }
    }
    واپس AV_PIX_FMT_NONE;
}

شمار AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(شمار AVColorRange color_range, شمار AVColorSpace color_space)
{
    انتخاب (color_space) {
    حالت AVCOL_SPC_SMPTE170M:
        اگر (color_range == AVCOL_RANGE_JPEG) {
            واپس AMF_VIDEO_CONVERTER_COLOR_PROFILE_بھرا_601;
        } ورنہ {
            واپس AMF_VIDEO_CONVERTER_COLOR_PROFILE_601;
        }
        توڑو;
    حالت AVCOL_SPC_BT709:
        اگر (color_range == AVCOL_RANGE_JPEG) {
            واپس AMF_VIDEO_CONVERTER_COLOR_PROFILE_بھرا_709;
        } ورنہ {
            واپس AMF_VIDEO_CONVERTER_COLOR_PROFILE_709;
        }
        توڑو;
    حالت AVCOL_SPC_BT2020_NCL:
    حالت AVCOL_SPC_BT2020_CL:
        اگر (color_range == AVCOL_RANGE_JPEG) {
            واپس AMF_VIDEO_CONVERTER_COLOR_PROFILE_بھرا_2020;
        } ورنہ {
            واپس AMF_VIDEO_CONVERTER_COLOR_PROFILE_2020;
        }
        توڑو;

    طےشدہ:
        واپس AMF_VIDEO_CONVERTER_COLOR_PROFILE_UNKNOWN;
    }
}

صحیح av_amf_display_mastering_meta_مقصد_hdrmeta(ثابت AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta)
{
    اگر (!display_meta || !hdrmeta)
        واپس AVERROR(EINVAL);

    اگر (display_meta->has_luminance) {
        ثابت غیرعلامتی صحیح luma_den = 10000;
        hdrmeta->maxMasteringLuminance =
            (amf_uint32)(luma_den * av_q2d(display_meta->max_luminance));
        hdrmeta->minMasteringLuminance =
            FFMIN((amf_uint32)(luma_den * av_q2d(display_meta->min_luminance)), hdrmeta->maxMasteringLuminance);
    }

    اگر (display_meta->has_primaries) {
        ثابت غیرعلامتی صحیح chroma_den = 50000;
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

    واپس 0;
}

صحیح av_amf_light_metadata_مقصد_hdrmeta(ثابت AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta)
{
    اگر (!light_meta || !hdrmeta)
        واپس AVERROR(EINVAL);

    hdrmeta->maxContentLightLevel = (amf_uint16)light_meta->MaxCLL;
    hdrmeta->max_چوکھٹا_اوسط_قدر_Light_Level = (amf_uint16)light_meta->MaxFALL;

    واپس 0;
}

صحیح av_amf_نکالو_hdr_metadata(ثابت AVFrame *چوکھٹا, AMFHDRMetadata *hdrmeta)
{
    AVFrame_Side_ڈیٹا *sidedata;
    AVContentLightMetadata *content_light = تہی;
    AVMasteringDisplayMetadata *mastering_display = تہی;

    اگر (!چوکھٹا || !hdrmeta)
        واپس AVERROR(EINVAL);

    sidedata = av_چوکھٹا_get_side_ڈیٹا(چوکھٹا, AV_چوکھٹا_ڈیٹا_MASTERING_DISPLAY_METADATA);
    اگر (sidedata) {
        mastering_display = (AVMasteringDisplayMetadata *)sidedata->ڈیٹا;
        اگر (av_amf_display_mastering_meta_مقصد_hdrmeta(mastering_display, hdrmeta) != 0)
            mastering_display = تہی;
    }

    sidedata = av_چوکھٹا_get_side_ڈیٹا(چوکھٹا, AV_چوکھٹا_ڈیٹا_CONTENT_LIGHT_LEVEL);
    اگر (sidedata) {
        content_light = (AVContentLightMetadata *)sidedata->ڈیٹا;
        اگر (av_amf_light_metadata_مقصد_hdrmeta(content_light, hdrmeta) != 0)
            content_light = تہی;
    }

    اگر (!mastering_display && !content_light)
        واپس AVERROR(ENODATA);

    واپس 0;
}

صحیح av_amf_attach_hdr_metadata(AVFrame *چوکھٹا, ثابت AMFHDRMetadata *hdrmeta) {
    اگر (!hdrmeta || !چوکھٹا)
        واپس AVERROR(EINVAL);

    AVMasteringDisplayMetadata *mastering =
        av_mastering_display_metadata_create_side_ڈیٹا(چوکھٹا);
    ثابت صحیح chroma_den = 50000;
    ثابت صحیح luma_den = 10000;

    اگر (!mastering)
      واپس AVERROR(ENOMEM);

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
    اگر (hdrmeta->maxContentLightLevel) {
      AVContentLightMetadata *light =
          av_content_light_metadata_create_side_ڈیٹا(چوکھٹا);

      اگر (!light)
        واپس AVERROR(ENOMEM);

      light->MaxCLL = hdrmeta->maxContentLightLevel;
      light->MaxFALL = hdrmeta->max_چوکھٹا_اوسط_قدر_Light_Level;
    }

    واپس 0;
}

ساکن ثابت شمار AVPixelFormat supported_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_BGR0,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
#اگر CONFIG_D3D11VA
    AV_PIX_FMT_D3D11,
#اگر_ختم
#اگر CONFIG_D3D12VA
    AV_PIX_FMT_D3D12,
#اگر_ختم
#اگر CONFIG_DXVA2
    AV_PIX_FMT_DXVA2_VLD,
#اگر_ختم
};

ساکن ثابت شمار AVPixelFormat supported_transfer_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
    AV_PIX_FMT_NONE,
};

ساکن صحیح amf_چوکھٹے_get_constraints(AVHWDeviceContext *ctx,
                                       ثابت خالی *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    صحیح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    اگر (!constraints->valid_sw_formats)
        واپس AVERROR(ENOMEM);

    برائے (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    اگر (!constraints->valid_hw_formats)
        واپس AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_AMF_SURFACE;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    واپس 0;
}

ساکن خالی amf_dummy_free(خالی *opaque, uint8_t *ڈیٹا)
{

}

ساکن AVBufferRef *amf_pool_alloc(خالی *opaque, size_t سائز)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)opaque;
    AVBufferRef *buf;

    buf = av_بفر_create(تہی, 0, amf_dummy_free, hwfc, AV_بفر_FLAG_READONLY);
    اگر (!buf) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create buffer for AMF context.\n");
        واپس تہی;
    }
    واپس buf;
}

ساکن صحیح amf_چوکھٹے_init(AVHWFramesContext *ctx)
{
    صحیح i;

    برائے (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        اگر (ctx->sw_format == supported_formats[i])
            توڑو;
    }
    اگر (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        واپس AVERROR(ENOSYS);
    }

    ffhwframesctx(ctx)->pool_اندرونی =
            av_بفر_pool_init2(حجم(AMFSurface), ctx,
                                 &amf_pool_alloc, تہی);

    واپس 0;
}


ساکن صحیح amf_get_بفر(AVHWFramesContext *ctx, AVFrame *چوکھٹا)
{
    چوکھٹا->buf[0] = av_بفر_pool_get(ctx->pool);
    اگر (!چوکھٹا->buf[0])
        واپس AVERROR(ENOMEM);

    چوکھٹا->ڈیٹا[0] = چوکھٹا->buf[0]->ڈیٹا;
    چوکھٹا->format  = AV_PIX_FMT_AMF_SURFACE;
    چوکھٹا->چوڑائی   = ctx->چوڑائی;
    چوکھٹا->اونچائی  = ctx->اونچائی;
    واپس 0;
}

ساکن صحیح amf_transfer_get_formats(AVHWFramesContext *ctx,
                                     شمار AVHWFrameTransferDirection dir,
                                     شمار AVPixelFormat **formats)
{
    شمار AVPixelFormat *fmts;
    صحیح i;

    fmts = av_malloc_array(FF_ARRAY_ELEMS(supported_transfer_formats), حجم(*fmts));
    اگر (!fmts)
        واپس AVERROR(ENOMEM);
    برائے (i = 0; i < FF_ARRAY_ELEMS(supported_transfer_formats); i++)
        fmts[i] = supported_transfer_formats[i];

    *formats = fmts;

    واپس 0;
}

ساکن خالی amf_free_amfsurface(خالی *opaque, uint8_t *ڈیٹا)
{
    اگر(!!ڈیٹا){
        AMFSurface *surface = (AMFSurface*)(ڈیٹا);
        surface->pVtbl->Release(surface);
    }
}

ساکن صحیح amf_transfer_ڈیٹا_مقصد(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)dst->ڈیٹا[0];
    AMFPlane *plane;
    uint8_t  *dst_ڈیٹا[4];
    صحیح       dst_linesize[4];
    صحیح       planes;
    صحیح       i;
    صحیح       res;
    صحیح w = FFMIN(dst->چوڑائی,  src->چوڑائی);
    صحیح h = FFMIN(dst->اونچائی, src->اونچائی);

    اگر (dst->hw_چوکھٹے_ctx->ڈیٹا != (uint8_t *)ctx || src->format != ctx->sw_format)
        واپس AVERROR(EINVAL);

    اگر (!surface) {
        AVHWDeviceContext   *hwdev_ctx = ctx->device_ctx;
        AVAMFDeviceContext  *amf_device_ctx = (AVAMFDeviceContext *)hwdev_ctx->hwctx;
        AMF_SURFACE_FORMAT  format = av_av_مقصد_amf_format(ctx->sw_format);
        res = amf_device_ctx->context->pVtbl->AllocSurface(amf_device_ctx->context, AMF_حافظہ_HOST, format, dst->چوڑائی, dst->اونچائی, &surface);
        AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR(ENOMEM), "AllocSurface() failed  with error %d\n", res);
        dst->ڈیٹا[0] = (uint8_t *)surface;
        dst->buf[1] = av_بفر_create((uint8_t *)surface, حجم(surface),
                                            amf_free_amfsurface,
                                            تہی,
                                            AV_بفر_FLAG_READONLY);
    AMF_RETURN_IF_FALSE(ctx, !!dst->buf[1], AVERROR(ENOMEM), "av_buffer_create for amf surface failed.");
    }

    planes = (صحیح)surface->pVtbl->Get_Planes_گنتی(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(dst_ڈیٹا));

    برائے (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        dst_ڈیٹا[i] = plane->pVtbl->GetNative(plane);
        dst_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst_ڈیٹا, dst_linesize,
                   src->ڈیٹا, src->linesize, src->format,
                   w, h);

    واپس 0;
}

ساکن صحیح amf_transfer_ڈیٹا_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ثابت AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)src->ڈیٹا[0];
    AMFPlane *plane;
    uint8_t  *src_ڈیٹا[4];
    صحیح       src_linesize[4];
    صحیح       planes;
    صحیح       i;
    صحیح w = FFMIN(dst->چوڑائی,  src->چوڑائی);
    صحیح h = FFMIN(dst->اونچائی, src->اونچائی);
    صحیح ret;

    اگر (src->hw_چوکھٹے_ctx->ڈیٹا != (uint8_t *)ctx || dst->format != ctx->sw_format)
        واپس AVERROR(EINVAL);

    ret = surface->pVtbl->Convert(surface, AMF_حافظہ_HOST);
    AMF_RETURN_IF_FALSE(ctx, ret == AMF_OK, AVERROR_UNKNOWN, "Convert(amf::AMF_MEMORY_HOST) failed with error %d\n", AVERROR_UNKNOWN);

    planes = (صحیح)surface->pVtbl->Get_Planes_گنتی(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(src_ڈیٹا));

    برائے (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        src_ڈیٹا[i] = plane->pVtbl->GetNative(plane);
        src_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst->ڈیٹا, dst->linesize,
                   src_ڈیٹا, src_linesize, dst->format,
                   w, h);
    واپس 0;
}



ساکن خالی amf_device_uninit(AVHWDeviceContext *device_ctx)
{
    AVAMFDeviceContext *amf_ctx = device_ctx->hwctx;
    AMF_نتیجہ          res = AMF_NOT_INITIALIZED;
    AMFTrace           *trace;

    اگر (amf_ctx->context) {
        amf_ctx->context->pVtbl->Terminate(amf_ctx->context);
        amf_ctx->context->pVtbl->Release(amf_ctx->context);
        amf_ctx->context = تہی;
    }

    اگر (amf_ctx->factory)
        res = amf_ctx->factory->pVtbl->GetTrace(amf_ctx->factory, &trace);

    اگر (res == AMF_OK) {
        trace->pVtbl->UnregisterWriter(trace, FFMPEG_AMF_WRITER_ID);
    }

    اگر(amf_ctx->library) {
        dlclose(amf_ctx->library);
        amf_ctx->library = تہی;
    }
    اگر (amf_ctx->trace_writer) {
        amf_writer_free(amf_ctx->trace_writer);
    }

    اگر (amf_ctx->تالا_ctx == amf_تالا_default) {
        ff_mutex_destroy((AVMutex*)amf_ctx->تالا_ctx);
        av_freep(&amf_ctx->تالا_ctx);
        amf_ctx->تالا_2 = تہی;
        amf_ctx->unlock = تہی;
    }

    amf_ctx->نسخہ = 0;
}

شمار AMF_حافظہ_TYPE av_amf_get_حافظہ_type(AVAMFDeviceContext *amf_ctx)
{
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = تہی;
    AMFGuid guid1 = IID_AMFContext1();
    خالی * device = تہی;

#اگر_تعریف_شدہ _WIN32
    // At the moment used only for DX12.
    AMFContext2 *context2 = تہی;

    /*
    Work around the incorrect C Context2 IID in unpatched AMF 1.5.2 headers;
    mostly pedantic fix as it works as it is in practice.
    TODO: replace with AMFGuid guid2 = IID_AMFContext2()
    once AMF 1.5.3 is available to public and marked as required version in ffmpeg.
    */
    ساکن ثابت AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#اگر_ختم

    اگر (!amf_ctx)
        واپس AMF_حافظہ_UNKNOWN;

#اگر_تعریف_شدہ _WIN32
    اگر (AMF_IFACE_CALL(context, QueryInterface, &guid2, (خالی**)&context2) == AMF_OK)
    {
        device = AMF_IFACE_CALL(context2, GetDX12Device, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);

        اگر (device)
            واپس AMF_حافظہ_DX12;
    }

    اگر (AMF_IFACE_CALL(context, GetDX11Device, AMF_DX11_1))
        واپس AMF_حافظہ_DX11;

    اگر (AMF_IFACE_CALL(context, GetDX9Device, AMF_DX9))
        واپس AMF_حافظہ_DX9;
#اگر_ختم

    اگر (AMF_IFACE_CALL(context, QueryInterface, &guid1, (خالی**)&context1) != AMF_OK)
        واپس AMF_حافظہ_UNKNOWN;

    device = AMF_IFACE_CALL(context1, GetVulkanDevice);
    AMF_IFACE_CALL(context1, Release);
    اگر (device)
        واپس AMF_حافظہ_VULKAN;

    واپس AMF_حافظہ_UNKNOWN;
}

ساکن صحیح amf_device_init(AVHWDeviceContext *ctx)
{
    AVAMFDeviceContext *amf_ctx = ctx->hwctx;
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = تہی;
    AMFGuid guid1 = IID_AMFContext1();
    AMF_نتیجہ res;

#اگر_تعریف_شدہ _WIN32
    AMFContext2 *context2 = تہی;
    ساکن ثابت AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#اگر_ختم

    اگر (!amf_ctx->تالا_2) {
        amf_ctx->تالا_ctx = av_mallocz(حجم(AVMutex));
        اگر (!amf_ctx->تالا_ctx) {
            واپس AVERROR(ENOMEM);
        }
        ff_mutex_init((AVMutex*)amf_ctx->تالا_ctx, تہی);
        amf_ctx->تالا_2   = amf_تالا_default;
        amf_ctx->unlock = amf_unlock_default;
    }

    اگر (av_amf_get_حافظہ_type(amf_ctx) != AMF_حافظہ_UNKNOWN) {
        av_log(ctx, AV_LOG_VERBOSE, "AMF is already initialized, skipping init.\n");
        واپس 0;
    }

#اگر_تعریف_شدہ _WIN32
    res = AMF_IFACE_CALL(context, InitDX11, تہی, AMF_DX11_1);
    اگر (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D11.\n");
        واپس 0;
    }

    res = AMF_IFACE_CALL(context, QueryInterface, &guid2, (خالی**)&context2);
    اگر (res == AMF_OK) {
        res = AMF_IFACE_CALL(context2, InitDX12, تہی, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);
        اگر (res == AMF_OK) {
            av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D12.\n");
            واپس 0;
        }
    } ورنہ {
        av_log(ctx, AV_LOG_VERBOSE, "QueryInterface(AMFContext2) failed with error %d, trying older D3D APIs...\n", res);
    }

    res = AMF_IFACE_CALL(context, InitDX9, تہی);
    اگر (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D9.\n");
        واپس 0;
    }

    av_log(ctx, AV_LOG_WARNING, "AMF failed to initialize with any of supported versions of DirectX, trying Vulkan instead...\n");
#اگر_ختم

    res = AMF_IFACE_CALL(context, QueryInterface, &guid1, (خالی**)&context1);
    اگر (res != AMF_OK) {
        av_log(ctx, AV_LOG_ERROR, "QueryInterface(AMFContext1) failed with error %d\n", res);
        واپس AVERROR_UNKNOWN;
    }

    res = AMF_IFACE_CALL(context1, InitVulkan, تہی);
    AMF_IFACE_CALL(context1, Release);

    اگر (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via Vulkan.\n");
    } ورنہ {
        اگر (res == AMF_NOT_SUPPORTED)
            av_log(ctx, AV_LOG_ERROR, "AMF via Vulkan is not supported on the given device.\n");
        ورنہ
            av_log(ctx, AV_LOG_ERROR, "Failed to initialize AMF via Vulkan, error %d\n", res);

        واپس AVERROR(ENOSYS);
    }

    واپس 0;
}

ساکن صحیح amf_بھرو_library(AVAMFDeviceContext* amf_ctx,  خالی* avcl)
{
    AMFInit_Fn         init_fun;
    AMFQuery_نسخہ_Fn نسخہ_fun;
    AMF_نتیجہ         res;

    amf_ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(avcl, amf_ctx->library != تہی,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(amf_ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, init_fun != تہی, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    نسخہ_fun = (AMFQuery_نسخہ_Fn)dlsym(amf_ctx->library, AMF_QUERY_نسخہ_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, نسخہ_fun != تہی, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_نسخہ_FUNCTION_NAME);

    amf_uint64 نسخہ;
    res = نسخہ_fun(&نسخہ);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_نسخہ_FUNCTION_NAME, res);
    amf_ctx->نسخہ = نسخہ;
    res = init_fun(AMF_بھرا_نسخہ, &amf_ctx->factory);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_INIT_FUNCTION_NAME, res);
    واپس 0;
}

ساکن صحیح amf_device_create(AVHWDeviceContext *device_ctx,
                              ثابت حرف *device,
                              AVDictionary *opts, صحیح flags)
{
    AVAMFDeviceContext        *ctx = device_ctx->hwctx;
    AMFTrace           *trace;
    صحیح ret;
    اگر ((ret = amf_بھرو_library(ctx, device_ctx)) == 0) {
        ret = ctx->factory->pVtbl->GetTrace(ctx->factory, &trace);
        اگر (ret == AMF_OK) {
            صحیح level_ff = av_log_get_level();
            صحیح level_amf = AMF_TRACE_TRACE;
            amf_bool enable_log = true;
            انتخاب(level_ff)
            {
            حالت AV_LOG_QUIET:
                level_amf = AMF_TRACE_ERROR;
                enable_log = false;
                توڑو;
            حالت AV_LOG_PANIC:
            حالت AV_LOG_FATAL:
            حالت AV_LOG_ERROR:
                level_amf = AMF_TRACE_ERROR;
                توڑو;
            حالت AV_LOG_WARNING:
            حالت AV_LOG_INFO:
                level_amf = AMF_TRACE_WARNING;
                توڑو;
            حالت AV_LOG_VERBOSE:
                level_amf = AMF_TRACE_INFO;
                توڑو;
            حالت AV_LOG_DEBUG:
                level_amf = AMF_TRACE_DEBUG;
                توڑو;
            حالت AV_LOG_TRACE:
                level_amf = AMF_TRACE_TRACE;
                توڑو;
            }
            اگر(ctx->نسخہ == AMF_MAKE_بھرا_نسخہ(1, 4, 35, 0)){// get around a bug in trace in AMF runtime driver 24.20
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
        اگر (ret == AMF_OK) {
            AMF_تفویض_PROPERTY_INT64(ret, ctx->context, L"DeviceSurfaceCacheSize", 50 );
            واپس 0;
        }
        av_log(device_ctx, AV_LOG_ERROR, "CreateContext() failed with error %d.\n", ret);
    }
    amf_device_uninit(device_ctx);
    واپس ret;
}

#اگر CONFIG_DXVA2
ساکن صحیح amf_init_from_dxva2_device(AVAMFDeviceContext * amf_ctx, AVHWDeviceContext *بچہ_device_ctx)
{
    AVDXVA2DeviceContext *hwctx = بچہ_device_ctx->hwctx;
    IDirect3DDevice9    *device;
    HANDLE              device_handle;
    HRESULT             hr;
    AMF_نتیجہ          res;
    صحیح ret;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &device_handle);
    اگر (FAILED(hr)) {
        av_log(بچہ_device_ctx, AV_LOG_ERROR, "Failed to open device handle for Direct3D9 device: %lx.\n", (غیرعلامتی طویل)hr);
        واپس AVERROR_EXTERNAL;
    }

    hr = IDirect3_DDevice_Manager9_تالا_Device(hwctx->devmgr, device_handle, &device, FALSE);
    اگر (SUCCEEDED(hr)) {
        IDirect3DDeviceManager9_UnlockDevice(hwctx->devmgr, device_handle, FALSE);
        ret = 0;
    } ورنہ {
        av_log(بچہ_device_ctx, AV_LOG_ERROR, "Failed to lock device handle for Direct3D9 device: %lx.\n", (غیرعلامتی طویل)hr);
        ret = AVERROR_EXTERNAL;
    }


    IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, device_handle);

    اگر (ret < 0)
        واپس ret;

    res = amf_ctx->context->pVtbl->InitDX9(amf_ctx->context, device);

    IDirect3DDevice9_Release(device);

    اگر (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        اگر (res == AMF_NOT_SUPPORTED)
            av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF via D3D9 is not supported on the given device.\n");
        ورنہ
            av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on given D3D9 device: %d.\n", res);
        واپس AVERROR(ENODEV);
    }
    av_log(بچہ_device_ctx, AV_LOG_INFO, "AMF via DXVA2.\n");
    واپس 0;
}
#اگر_ختم

#اگر CONFIG_D3D11VA
ساکن صحیح amf_init_from_d3d11_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *بچہ_device_ctx)
{
    AMF_نتیجہ res;
    AVD3D11VADeviceContext *hwctx = بچہ_device_ctx->hwctx;
    res = amf_ctx->context->pVtbl->InitDX11(amf_ctx->context, hwctx->device, AMF_DX11_1);
    اگر (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        اگر (res == AMF_NOT_SUPPORTED)
            av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF via D3D11 is not supported on the given device.\n");
        ورنہ
            av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D11 device: %d.\n", res);
        واپس AVERROR(ENODEV);
    }
    av_log(بچہ_device_ctx, AV_LOG_INFO, "AMF via D3D11.\n");
    hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    واپس 0;
}
#اگر_ختم

#اگر CONFIG_D3D12VA
ساکن صحیح amf_init_from_d3d12_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *بچہ_device_ctx)
{
    AVD3D12VADeviceContext *hwctx = بچہ_device_ctx->hwctx;
    AMF_نتیجہ res;
    AMFContext2 *context2 = تہی;
    AMFGuid guid = IID_AMFContext2();
    res = amf_ctx->context->pVtbl->QueryInterface(amf_ctx->context, &guid, (خالی**)&context2);
    AMF_RETURN_IF_FALSE(بچہ_device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "CreateContext2() failed with error %d\n", res);
    res = context2->pVtbl->InitDX12(context2, hwctx->device, AMF_DX12);
    context2->pVtbl->Release(context2);
    اگر (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        اگر (res == AMF_NOT_SUPPORTED)
            av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF via D3D12 is not supported on the given device.\n");
        ورنہ
            av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D12 device: %d.\n", res);
        واپس AVERROR(ENODEV);
    }
    av_log(بچہ_device_ctx, AV_LOG_INFO, "AMF via D3D12.\n");
    واپس 0;
}
#اگر_ختم


ساکن صحیح amf_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *بچہ_device_ctx, AVDictionary *opts,
                              صحیح flags)
{
#اگر CONFIG_DXVA2 || CONFIG_D3D11VA || CONFIG_D3D12VA
    AVAMFDeviceContext        *amf_ctx = device_ctx->hwctx;
#اگر_ختم
    صحیح ret;

    ret = amf_device_create(device_ctx, "", opts, flags);
    اگر(ret < 0)
        واپس ret;

    انتخاب (بچہ_device_ctx->type) {
#اگر CONFIG_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
        واپس amf_init_from_dxva2_device(amf_ctx, بچہ_device_ctx);
#اگر_ختم
#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
        واپس amf_init_from_d3d11_device(amf_ctx, بچہ_device_ctx);
#اگر_ختم
#اگر CONFIG_D3D12VA
    حالت AV_HWDEVICE_TYPE_D3D12VA:
        واپس amf_init_from_d3d12_device(amf_ctx, بچہ_device_ctx);
#اگر_ختم
    طےشدہ:
        av_log(بچہ_device_ctx, AV_LOG_ERROR, "AMF initialisation from a %s device is not supported.\n",
               av_hwdevice_get_type_name(بچہ_device_ctx->type));
        واپس AVERROR(ENOSYS);
    }
}

ساکن خالی amf_unmap_چوکھٹا(av_غیر_مستعمل AVHWFramesContext *غیر_مستعمل, HWMapDescriptor *hwmap)
{
    AMFSurface1 *surface1 = hwmap->priv;
    AMF_IFACE_CALL(surface1, Unmap);
    AMF_IFACE_CALL(surface1, Release);
}

ساکن صحیح amf_map_چوکھٹا(AVHWFramesContext *device_ctx, AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    AMFSurface *surface = (AMFSurface *)src->ڈیٹا[0];
    AMFSurface1 *surface1 = تہی;
    size_t *linesizes = تہی;
    uint8_t **map = تہی;
    صحیح amf_mem_flags = AMF_حافظہ_CPU_NONE;
    ثابت AMFGuid guid = IID_AMFSurface1();
    AMF_نتیجہ res = AMF_FAIL;
    size_t plane_گنتی = 0;
    صحیح ret = -1;

    AMF_RETURN_IF_FALSE(device_ctx, surface != تہی, AVERROR(EINVAL) , "Source surface is null");

    res = AMF_IFACE_CALL(surface, QueryInterface, &guid, (خالی**)&surface1);
    AMF_RETURN_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "QueryInterface(AMFSurface1) failed with error %d\n", res);

    اگر (flags & AV_HWFRAME_MAP_READ)
        amf_mem_flags |= AMF_حافظہ_CPU_READ;

    اگر (flags & AV_HWFRAME_MAP_WRITE)
        amf_mem_flags |= AMF_حافظہ_CPU_WRITE;

    plane_گنتی = AMF_IFACE_CALL(surface, Get_Planes_گنتی);
    linesizes = av_malloc_array(حجم(size_t), plane_گنتی);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, linesizes, AVERROR(ENOMEM), "Unable to allocate line sizes array\n");

    map = av_malloc_array(حجم(uint8_t *), plane_گنتی);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, map, AVERROR(ENOMEM), "Unable to allocate mapping buffer\n");

    dst->format = av_amf_مقصد_av_format(AMF_IFACE_CALL(surface, GetFormat));

    res = AMF_IFACE_CALL(surface1, Map, amf_mem_flags, plane_گنتی, linesizes, (خالی**)map);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "AMFSurface1->Map() failed with error %d\n", res);

    ret = ff_hwframe_map_create(src->hw_چوکھٹے_ctx, dst, src, &amf_unmap_چوکھٹا, surface1);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, ret >= 0, ret, "ff_hwframe_map_create failed with error %d\n", ret);

    dst->چوڑائی  = src->چوڑائی;
    dst->اونچائی = src->اونچائی;
    av_چوکھٹا_copy_props(dst, src);

    // The dst frame is no longer a hardware frame, from the perspective of any dst frame consumer.
    av_بفر_unref(&dst->hw_چوکھٹے_ctx);

    برائے (صحیح plane = 0; plane < plane_گنتی; ++plane)
    {
        dst->ڈیٹا[plane] = map[plane];
        dst->linesize[plane] = linesizes[plane];
    }

fail:
    اگر (map)
        av_free(map);

    اگر (linesizes)
        av_free(linesizes);

    اگر (ret < 0 && surface1 != تہی)
        AMF_IFACE_CALL(surface1, Release);

    واپس ret;
}

ثابت HWContextType ff_hwcontext_type_amf = {
    .type                 = AV_HWDEVICE_TYPE_AMF,
    .name                 = "AMF",

    .device_hwctx_سائز    = حجم(AVAMFDeviceContext),
    .چوکھٹے_hwctx_سائز    = حجم(AMFFramesContext),

    .device_create        = amf_device_create,
    .device_derive        = amf_device_derive,
    .device_init          = amf_device_init,
    .device_uninit        = amf_device_uninit,
    .چوکھٹے_get_constraints = amf_چوکھٹے_get_constraints,
    .چوکھٹے_init          = amf_چوکھٹے_init,
    .چوکھٹے_get_بفر    = amf_get_بفر,
    .transfer_get_formats = amf_transfer_get_formats,
    .transfer_ڈیٹا_مقصد     = amf_transfer_ڈیٹا_مقصد,
    .transfer_ڈیٹا_from   = amf_transfer_ڈیٹا_from,
    .map_from             = amf_map_چوکھٹا,

    .pix_fmts             = (ثابت شمار AVPixelFormat[]){ AV_PIX_FMT_AMF_SURFACE, AV_PIX_FMT_NONE },
};
