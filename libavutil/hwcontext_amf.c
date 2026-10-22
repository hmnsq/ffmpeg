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

#అన్తర్భావ "mem.h"
#అన్తర్భావ "buffer.h"
#అన్తర్భావ "pixfmt.h"
#అన్తర్భావ "pixdesc.h"
#అన్తర్భావ "imgutils.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_amf.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "hwcontext_amf_internal.h"

#అన్తర్భావ "libavutil/thread.h"
#అన్తర్భావ "libavutil/avassert.h"

#అన్తర్భావ <AMF/core/Surface.h>
#అన్తర్భావ <AMF/core/Trace.h>

#ఒకవేళ CONFIG_VULKAN
#అన్తర్భావ "hwcontext_vulkan.h"
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D11VA
#అన్తర్భావ "libavutil/hwcontext_d3d11va.h"
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D12VA
#అన్తర్భావ "libavutil/hwcontext_d3d12va.h"
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
#నిర్వచించు COBJMACROS
#అన్తర్భావ "libavutil/hwcontext_dxva2.h"
#అయితే_ముగింపు
#నిర్వచితమైతే _WIN32
#అన్తర్భావ "compat/w32dlfcn.h"
#లేకపోతే
#అన్తర్భావ <dlfcn.h>
#అయితే_ముగింపు
#నిర్వచించు FFMPEG_AMF_WRITER_ID L"ffmpeg_amf"

స్థిర శూన్య amf_తాళం_default(శూన్య *opaque)
{
    ff_mutex_తాళం((AVMutex*)opaque);
}

స్థిర శూన్య amf_unlock_default(శూన్య *opaque)
{
    ff_mutex_unlock((AVMutex*)opaque);
}

రకనిర్వచనం నిర్మాణం AmfTraceWriter {
    AMFTraceWriterVtbl *vtblp;
    శూన్య               *avctx;
    AMFTraceWriterVtbl  vtbl;
} AmfTraceWriter;

స్థిర శూన్య AMF_CDECL_CALL AMFTraceWriter_Write(AMFTraceWriter *pThis,
    స్థిరరాశి wchar_t *scope, స్థిరరాశి wchar_t *సందేశం_2)
{
    AmfTraceWriter *tracer = (AmfTraceWriter*)pThis;
    av_log(tracer->avctx, AV_LOG_DEBUG, "%ls: %ls", scope, సందేశం_2); // \n is provided from AMF
}

స్థిర శూన్య AMF_CDECL_CALL AMFTraceWriter_Flush(AMFTraceWriter *pThis)
{
}

స్థిర AmfTraceWriter * amf_writer_alloc(శూన్య  *avctx)
{
    AmfTraceWriter * writer = av_mallocz(పరిమాణం(AmfTraceWriter));
    ఒకవేళ (!writer)
        తిరిగి ఖాళీ;

    writer->vtblp = &writer->vtbl;
    writer->vtblp->Write = AMFTraceWriter_Write;
    writer->vtblp->Flush = AMFTraceWriter_Flush;
    writer->avctx = avctx;

    తిరిగి writer;
}

స్థిర శూన్య amf_writer_free(శూన్య  *opaque)
{
    AmfTraceWriter *writer = (AmfTraceWriter *)opaque;
    av_freep(&writer);
}

/**
 * We still need AVHWFramesContext to utilize our hardware memory
 * otherwise, we will receive the error "HW format requires hw_frames_ctx to be non-NULL".
 * (libavfilter\buffersrc.c function query_formats)
*/
రకనిర్వచనం నిర్మాణం {
    శూన్య *dummy;
} AMFFramesContext;

రకనిర్వచనం నిర్మాణం AVAMFFormatMap {
    గణన AVPixelFormat       av_format;
    గణన AMF_SURFACE_FORMAT  amf_format;
} FormatMap;

స్థిరరాశి FormatMap format_map[] =
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

గణన AMF_SURFACE_FORMAT av_av_గమ్యం_amf_format(గణన AVPixelFormat fmt)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < amf_countof(format_map); i++) {
        ఒకవేళ (format_map[i].av_format == fmt) {
            తిరిగి format_map[i].amf_format;
        }
    }
    తిరిగి AMF_SURFACE_UNKNOWN;
}

గణన AVPixelFormat av_amf_గమ్యం_av_format(గణన AMF_SURFACE_FORMAT fmt)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < amf_countof(format_map); i++) {
        ఒకవేళ (format_map[i].amf_format == fmt) {
            తిరిగి format_map[i].av_format;
        }
    }
    తిరిగి AV_PIX_FMT_NONE;
}

గణన AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(గణన AVColorRange color_range, గణన AVColorSpace color_space)
{
    ఎంపిక (color_space) {
    స్థితి AVCOL_SPC_SMPTE170M:
        ఒకవేళ (color_range == AVCOL_RANGE_JPEG) {
            తిరిగి AMF_VIDEO_CONVERTER_COLOR_PROFILE_నిండిన_601;
        } లేకపోతే {
            తిరిగి AMF_VIDEO_CONVERTER_COLOR_PROFILE_601;
        }
        ఆపు;
    స్థితి AVCOL_SPC_BT709:
        ఒకవేళ (color_range == AVCOL_RANGE_JPEG) {
            తిరిగి AMF_VIDEO_CONVERTER_COLOR_PROFILE_నిండిన_709;
        } లేకపోతే {
            తిరిగి AMF_VIDEO_CONVERTER_COLOR_PROFILE_709;
        }
        ఆపు;
    స్థితి AVCOL_SPC_BT2020_NCL:
    స్థితి AVCOL_SPC_BT2020_CL:
        ఒకవేళ (color_range == AVCOL_RANGE_JPEG) {
            తిరిగి AMF_VIDEO_CONVERTER_COLOR_PROFILE_నిండిన_2020;
        } లేకపోతే {
            తిరిగి AMF_VIDEO_CONVERTER_COLOR_PROFILE_2020;
        }
        ఆపు;

    అప్రమేయ:
        తిరిగి AMF_VIDEO_CONVERTER_COLOR_PROFILE_UNKNOWN;
    }
}

పూర్ణాంకం av_amf_display_mastering_meta_గమ్యం_hdrmeta(స్థిరరాశి AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta)
{
    ఒకవేళ (!display_meta || !hdrmeta)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (display_meta->has_luminance) {
        స్థిరరాశి గుర్తులేని పూర్ణాంకం luma_den = 10000;
        hdrmeta->maxMasteringLuminance =
            (amf_uint32)(luma_den * av_q2d(display_meta->max_luminance));
        hdrmeta->minMasteringLuminance =
            FFMIN((amf_uint32)(luma_den * av_q2d(display_meta->min_luminance)), hdrmeta->maxMasteringLuminance);
    }

    ఒకవేళ (display_meta->has_primaries) {
        స్థిరరాశి గుర్తులేని పూర్ణాంకం chroma_den = 50000;
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
        hdrmeta->white_బిందువు[0] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_బిందువు_2[0])), chroma_den);
        hdrmeta->white_బిందువు[1] =
            FFMIN((amf_uint16)(chroma_den * av_q2d(display_meta->white_బిందువు_2[1])), chroma_den);
    }

    తిరిగి 0;
}

పూర్ణాంకం av_amf_light_metadata_గమ్యం_hdrmeta(స్థిరరాశి AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta)
{
    ఒకవేళ (!light_meta || !hdrmeta)
        తిరిగి AVERROR(EINVAL);

    hdrmeta->maxContentLightLevel = (amf_uint16)light_meta->MaxCLL;
    hdrmeta->max_చట్రం_సరాసరి_Light_Level = (amf_uint16)light_meta->MaxFALL;

    తిరిగి 0;
}

పూర్ణాంకం av_amf_వెలికితీయి_hdr_metadata(స్థిరరాశి AVFrame *చట్రం, AMFHDRMetadata *hdrmeta)
{
    AVFrame_Side_దత్తాంశం *sidedata;
    AVContentLightMetadata *content_light = ఖాళీ;
    AVMasteringDisplayMetadata *mastering_display = ఖాళీ;

    ఒకవేళ (!చట్రం || !hdrmeta)
        తిరిగి AVERROR(EINVAL);

    sidedata = av_చట్రం_get_side_దత్తాంశం(చట్రం, AV_చట్రం_దత్తాంశం_MASTERING_DISPLAY_METADATA);
    ఒకవేళ (sidedata) {
        mastering_display = (AVMasteringDisplayMetadata *)sidedata->దత్తాంశం;
        ఒకవేళ (av_amf_display_mastering_meta_గమ్యం_hdrmeta(mastering_display, hdrmeta) != 0)
            mastering_display = ఖాళీ;
    }

    sidedata = av_చట్రం_get_side_దత్తాంశం(చట్రం, AV_చట్రం_దత్తాంశం_CONTENT_LIGHT_LEVEL);
    ఒకవేళ (sidedata) {
        content_light = (AVContentLightMetadata *)sidedata->దత్తాంశం;
        ఒకవేళ (av_amf_light_metadata_గమ్యం_hdrmeta(content_light, hdrmeta) != 0)
            content_light = ఖాళీ;
    }

    ఒకవేళ (!mastering_display && !content_light)
        తిరిగి AVERROR(ENODATA);

    తిరిగి 0;
}

పూర్ణాంకం av_amf_attach_hdr_metadata(AVFrame *చట్రం, స్థిరరాశి AMFHDRMetadata *hdrmeta) {
    ఒకవేళ (!hdrmeta || !చట్రం)
        తిరిగి AVERROR(EINVAL);

    AVMasteringDisplayMetadata *mastering =
        av_mastering_display_metadata_create_side_దత్తాంశం(చట్రం);
    స్థిరరాశి పూర్ణాంకం chroma_den = 50000;
    స్థిరరాశి పూర్ణాంకం luma_den = 10000;

    ఒకవేళ (!mastering)
      తిరిగి AVERROR(ENOMEM);

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

    mastering->white_బిందువు_2[0] = av_make_q(hdrmeta->white_బిందువు[0], chroma_den);
    mastering->white_బిందువు_2[1] = av_make_q(hdrmeta->white_బిందువు[1], chroma_den);

    mastering->max_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);
    mastering->min_luminance =
        av_make_q(hdrmeta->maxMasteringLuminance, luma_den);

    mastering->has_luminance = 1;
    mastering->has_primaries = 1;
    ఒకవేళ (hdrmeta->maxContentLightLevel) {
      AVContentLightMetadata *light =
          av_content_light_metadata_create_side_దత్తాంశం(చట్రం);

      ఒకవేళ (!light)
        తిరిగి AVERROR(ENOMEM);

      light->MaxCLL = hdrmeta->maxContentLightLevel;
      light->MaxFALL = hdrmeta->max_చట్రం_సరాసరి_Light_Level;
    }

    తిరిగి 0;
}

స్థిర స్థిరరాశి గణన AVPixelFormat supported_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_BGR0,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
#ఒకవేళ CONFIG_D3D11VA
    AV_PIX_FMT_D3D11,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D12VA
    AV_PIX_FMT_D3D12,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
    AV_PIX_FMT_DXVA2_VLD,
#అయితే_ముగింపు
};

స్థిర స్థిరరాశి గణన AVPixelFormat supported_transfer_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
    AV_PIX_FMT_NONE,
};

స్థిర పూర్ణాంకం amf_చట్రాలు_get_constraints(AVHWDeviceContext *ctx,
                                       స్థిరరాశి శూన్య *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    పూర్ణాంకం i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    పరిమాణం(*constraints->valid_sw_formats));
    ఒకవేళ (!constraints->valid_sw_formats)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, పరిమాణం(*constraints->valid_hw_formats));
    ఒకవేళ (!constraints->valid_hw_formats)
        తిరిగి AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_AMF_SURFACE;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    తిరిగి 0;
}

స్థిర శూన్య amf_dummy_free(శూన్య *opaque, uint8_t *దత్తాంశం)
{

}

స్థిర AVBufferRef *amf_pool_alloc(శూన్య *opaque, size_t కొలత)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)opaque;
    AVBufferRef *buf;

    buf = av_బఫరు_create(ఖాళీ, 0, amf_dummy_free, hwfc, AV_బఫరు_FLAG_READONLY);
    ఒకవేళ (!buf) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create buffer for AMF context.\n");
        తిరిగి ఖాళీ;
    }
    తిరిగి buf;
}

స్థిర పూర్ణాంకం amf_చట్రాలు_init(AVHWFramesContext *ctx)
{
    పూర్ణాంకం i;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ఒకవేళ (ctx->sw_format == supported_formats[i])
            ఆపు;
    }
    ఒకవేళ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        తిరిగి AVERROR(ENOSYS);
    }

    ffhwframesctx(ctx)->pool_అంతర్గత =
            av_బఫరు_pool_init2(పరిమాణం(AMFSurface), ctx,
                                 &amf_pool_alloc, ఖాళీ);

    తిరిగి 0;
}


స్థిర పూర్ణాంకం amf_get_బఫరు(AVHWFramesContext *ctx, AVFrame *చట్రం)
{
    చట్రం->buf[0] = av_బఫరు_pool_get(ctx->pool);
    ఒకవేళ (!చట్రం->buf[0])
        తిరిగి AVERROR(ENOMEM);

    చట్రం->దత్తాంశం[0] = చట్రం->buf[0]->దత్తాంశం;
    చట్రం->format  = AV_PIX_FMT_AMF_SURFACE;
    చట్రం->వెడల్పు   = ctx->వెడల్పు;
    చట్రం->ఎత్తు  = ctx->ఎత్తు;
    తిరిగి 0;
}

స్థిర పూర్ణాంకం amf_transfer_get_formats(AVHWFramesContext *ctx,
                                     గణన AVHWFrameTransferDirection dir,
                                     గణన AVPixelFormat **formats)
{
    గణన AVPixelFormat *fmts;
    పూర్ణాంకం i;

    fmts = av_malloc_array(FF_ARRAY_ELEMS(supported_transfer_formats), పరిమాణం(*fmts));
    ఒకవేళ (!fmts)
        తిరిగి AVERROR(ENOMEM);
    కొరకు (i = 0; i < FF_ARRAY_ELEMS(supported_transfer_formats); i++)
        fmts[i] = supported_transfer_formats[i];

    *formats = fmts;

    తిరిగి 0;
}

స్థిర శూన్య amf_free_amfsurface(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    ఒకవేళ(!!దత్తాంశం){
        AMFSurface *surface = (AMFSurface*)(దత్తాంశం);
        surface->pVtbl->Release(surface);
    }
}

స్థిర పూర్ణాంకం amf_transfer_దత్తాంశం_గమ్యం(AVHWFramesContext *ctx, AVFrame *dst,
                                 స్థిరరాశి AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)dst->దత్తాంశం[0];
    AMFPlane *plane;
    uint8_t  *dst_దత్తాంశం[4];
    పూర్ణాంకం       dst_linesize[4];
    పూర్ణాంకం       planes;
    పూర్ణాంకం       i;
    పూర్ణాంకం       res;
    పూర్ణాంకం w = FFMIN(dst->వెడల్పు,  src->వెడల్పు);
    పూర్ణాంకం h = FFMIN(dst->ఎత్తు, src->ఎత్తు);

    ఒకవేళ (dst->hw_చట్రాలు_ctx->దత్తాంశం != (uint8_t *)ctx || src->format != ctx->sw_format)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (!surface) {
        AVHWDeviceContext   *hwdev_ctx = ctx->device_ctx;
        AVAMFDeviceContext  *amf_device_ctx = (AVAMFDeviceContext *)hwdev_ctx->hwctx;
        AMF_SURFACE_FORMAT  format = av_av_గమ్యం_amf_format(ctx->sw_format);
        res = amf_device_ctx->context->pVtbl->AllocSurface(amf_device_ctx->context, AMF_జ్ఞాపకం_HOST, format, dst->వెడల్పు, dst->ఎత్తు, &surface);
        AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR(ENOMEM), "AllocSurface() failed  with error %d\n", res);
        dst->దత్తాంశం[0] = (uint8_t *)surface;
        dst->buf[1] = av_బఫరు_create((uint8_t *)surface, పరిమాణం(surface),
                                            amf_free_amfsurface,
                                            ఖాళీ,
                                            AV_బఫరు_FLAG_READONLY);
    AMF_RETURN_IF_FALSE(ctx, !!dst->buf[1], AVERROR(ENOMEM), "av_buffer_create for amf surface failed.");
    }

    planes = (పూర్ణాంకం)surface->pVtbl->Get_Planes_లెక్క(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(dst_దత్తాంశం));

    కొరకు (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        dst_దత్తాంశం[i] = plane->pVtbl->GetNative(plane);
        dst_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst_దత్తాంశం, dst_linesize,
                   src->దత్తాంశం, src->linesize, src->format,
                   w, h);

    తిరిగి 0;
}

స్థిర పూర్ణాంకం amf_transfer_దత్తాంశం_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    స్థిరరాశి AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)src->దత్తాంశం[0];
    AMFPlane *plane;
    uint8_t  *src_దత్తాంశం[4];
    పూర్ణాంకం       src_linesize[4];
    పూర్ణాంకం       planes;
    పూర్ణాంకం       i;
    పూర్ణాంకం w = FFMIN(dst->వెడల్పు,  src->వెడల్పు);
    పూర్ణాంకం h = FFMIN(dst->ఎత్తు, src->ఎత్తు);
    పూర్ణాంకం ret;

    ఒకవేళ (src->hw_చట్రాలు_ctx->దత్తాంశం != (uint8_t *)ctx || dst->format != ctx->sw_format)
        తిరిగి AVERROR(EINVAL);

    ret = surface->pVtbl->Convert(surface, AMF_జ్ఞాపకం_HOST);
    AMF_RETURN_IF_FALSE(ctx, ret == AMF_OK, AVERROR_UNKNOWN, "Convert(amf::AMF_MEMORY_HOST) failed with error %d\n", AVERROR_UNKNOWN);

    planes = (పూర్ణాంకం)surface->pVtbl->Get_Planes_లెక్క(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(src_దత్తాంశం));

    కొరకు (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        src_దత్తాంశం[i] = plane->pVtbl->GetNative(plane);
        src_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst->దత్తాంశం, dst->linesize,
                   src_దత్తాంశం, src_linesize, dst->format,
                   w, h);
    తిరిగి 0;
}



స్థిర శూన్య amf_device_uninit(AVHWDeviceContext *device_ctx)
{
    AVAMFDeviceContext *amf_ctx = device_ctx->hwctx;
    AMF_ఫలితం          res = AMF_NOT_INITIALIZED;
    AMFTrace           *trace;

    ఒకవేళ (amf_ctx->context) {
        amf_ctx->context->pVtbl->Terminate(amf_ctx->context);
        amf_ctx->context->pVtbl->Release(amf_ctx->context);
        amf_ctx->context = ఖాళీ;
    }

    ఒకవేళ (amf_ctx->factory)
        res = amf_ctx->factory->pVtbl->GetTrace(amf_ctx->factory, &trace);

    ఒకవేళ (res == AMF_OK) {
        trace->pVtbl->UnregisterWriter(trace, FFMPEG_AMF_WRITER_ID);
    }

    ఒకవేళ(amf_ctx->library) {
        dlclose(amf_ctx->library);
        amf_ctx->library = ఖాళీ;
    }
    ఒకవేళ (amf_ctx->trace_writer) {
        amf_writer_free(amf_ctx->trace_writer);
    }

    ఒకవేళ (amf_ctx->తాళం_ctx == amf_తాళం_default) {
        ff_mutex_destroy((AVMutex*)amf_ctx->తాళం_ctx);
        av_freep(&amf_ctx->తాళం_ctx);
        amf_ctx->తాళం_2 = ఖాళీ;
        amf_ctx->unlock = ఖాళీ;
    }

    amf_ctx->సంస్కరణ = 0;
}

గణన AMF_జ్ఞాపకం_TYPE av_amf_get_జ్ఞాపకం_type(AVAMFDeviceContext *amf_ctx)
{
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = ఖాళీ;
    AMFGuid guid1 = IID_AMFContext1();
    శూన్య * device = ఖాళీ;

#నిర్వచితమైతే _WIN32
    // At the moment used only for DX12.
    AMFContext2 *context2 = ఖాళీ;

    /*
    Work around the incorrect C Context2 IID in unpatched AMF 1.5.2 headers;
    mostly pedantic fix as it works as it is in practice.
    TODO: replace with AMFGuid guid2 = IID_AMFContext2()
    once AMF 1.5.3 is available to public and marked as required version in ffmpeg.
    */
    స్థిర స్థిరరాశి AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#అయితే_ముగింపు

    ఒకవేళ (!amf_ctx)
        తిరిగి AMF_జ్ఞాపకం_UNKNOWN;

#నిర్వచితమైతే _WIN32
    ఒకవేళ (AMF_IFACE_CALL(context, QueryInterface, &guid2, (శూన్య**)&context2) == AMF_OK)
    {
        device = AMF_IFACE_CALL(context2, GetDX12Device, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);

        ఒకవేళ (device)
            తిరిగి AMF_జ్ఞాపకం_DX12;
    }

    ఒకవేళ (AMF_IFACE_CALL(context, GetDX11Device, AMF_DX11_1))
        తిరిగి AMF_జ్ఞాపకం_DX11;

    ఒకవేళ (AMF_IFACE_CALL(context, GetDX9Device, AMF_DX9))
        తిరిగి AMF_జ్ఞాపకం_DX9;
#అయితే_ముగింపు

    ఒకవేళ (AMF_IFACE_CALL(context, QueryInterface, &guid1, (శూన్య**)&context1) != AMF_OK)
        తిరిగి AMF_జ్ఞాపకం_UNKNOWN;

    device = AMF_IFACE_CALL(context1, GetVulkanDevice);
    AMF_IFACE_CALL(context1, Release);
    ఒకవేళ (device)
        తిరిగి AMF_జ్ఞాపకం_VULKAN;

    తిరిగి AMF_జ్ఞాపకం_UNKNOWN;
}

స్థిర పూర్ణాంకం amf_device_init(AVHWDeviceContext *ctx)
{
    AVAMFDeviceContext *amf_ctx = ctx->hwctx;
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = ఖాళీ;
    AMFGuid guid1 = IID_AMFContext1();
    AMF_ఫలితం res;

#నిర్వచితమైతే _WIN32
    AMFContext2 *context2 = ఖాళీ;
    స్థిర స్థిరరాశి AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#అయితే_ముగింపు

    ఒకవేళ (!amf_ctx->తాళం_2) {
        amf_ctx->తాళం_ctx = av_mallocz(పరిమాణం(AVMutex));
        ఒకవేళ (!amf_ctx->తాళం_ctx) {
            తిరిగి AVERROR(ENOMEM);
        }
        ff_mutex_init((AVMutex*)amf_ctx->తాళం_ctx, ఖాళీ);
        amf_ctx->తాళం_2   = amf_తాళం_default;
        amf_ctx->unlock = amf_unlock_default;
    }

    ఒకవేళ (av_amf_get_జ్ఞాపకం_type(amf_ctx) != AMF_జ్ఞాపకం_UNKNOWN) {
        av_log(ctx, AV_LOG_VERBOSE, "AMF is already initialized, skipping init.\n");
        తిరిగి 0;
    }

#నిర్వచితమైతే _WIN32
    res = AMF_IFACE_CALL(context, InitDX11, ఖాళీ, AMF_DX11_1);
    ఒకవేళ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D11.\n");
        తిరిగి 0;
    }

    res = AMF_IFACE_CALL(context, QueryInterface, &guid2, (శూన్య**)&context2);
    ఒకవేళ (res == AMF_OK) {
        res = AMF_IFACE_CALL(context2, InitDX12, ఖాళీ, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);
        ఒకవేళ (res == AMF_OK) {
            av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D12.\n");
            తిరిగి 0;
        }
    } లేకపోతే {
        av_log(ctx, AV_LOG_VERBOSE, "QueryInterface(AMFContext2) failed with error %d, trying older D3D APIs...\n", res);
    }

    res = AMF_IFACE_CALL(context, InitDX9, ఖాళీ);
    ఒకవేళ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D9.\n");
        తిరిగి 0;
    }

    av_log(ctx, AV_LOG_WARNING, "AMF failed to initialize with any of supported versions of DirectX, trying Vulkan instead...\n");
#అయితే_ముగింపు

    res = AMF_IFACE_CALL(context, QueryInterface, &guid1, (శూన్య**)&context1);
    ఒకవేళ (res != AMF_OK) {
        av_log(ctx, AV_LOG_ERROR, "QueryInterface(AMFContext1) failed with error %d\n", res);
        తిరిగి AVERROR_UNKNOWN;
    }

    res = AMF_IFACE_CALL(context1, InitVulkan, ఖాళీ);
    AMF_IFACE_CALL(context1, Release);

    ఒకవేళ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via Vulkan.\n");
    } లేకపోతే {
        ఒకవేళ (res == AMF_NOT_SUPPORTED)
            av_log(ctx, AV_LOG_ERROR, "AMF via Vulkan is not supported on the given device.\n");
        లేకపోతే
            av_log(ctx, AV_LOG_ERROR, "Failed to initialize AMF via Vulkan, error %d\n", res);

        తిరిగి AVERROR(ENOSYS);
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం amf_ఎక్కించు_library(AVAMFDeviceContext* amf_ctx,  శూన్య* avcl)
{
    AMFInit_Fn         init_fun;
    AMFQuery_సంస్కరణ_Fn సంస్కరణ_fun;
    AMF_ఫలితం         res;

    amf_ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(avcl, amf_ctx->library != ఖాళీ,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(amf_ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, init_fun != ఖాళీ, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    సంస్కరణ_fun = (AMFQuery_సంస్కరణ_Fn)dlsym(amf_ctx->library, AMF_QUERY_సంస్కరణ_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, సంస్కరణ_fun != ఖాళీ, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_సంస్కరణ_FUNCTION_NAME);

    amf_uint64 సంస్కరణ;
    res = సంస్కరణ_fun(&సంస్కరణ);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_సంస్కరణ_FUNCTION_NAME, res);
    amf_ctx->సంస్కరణ = సంస్కరణ;
    res = init_fun(AMF_నిండిన_సంస్కరణ, &amf_ctx->factory);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_INIT_FUNCTION_NAME, res);
    తిరిగి 0;
}

స్థిర పూర్ణాంకం amf_device_create(AVHWDeviceContext *device_ctx,
                              స్థిరరాశి అక్షరం *device,
                              AVDictionary *opts, పూర్ణాంకం flags)
{
    AVAMFDeviceContext        *ctx = device_ctx->hwctx;
    AMFTrace           *trace;
    పూర్ణాంకం ret;
    ఒకవేళ ((ret = amf_ఎక్కించు_library(ctx, device_ctx)) == 0) {
        ret = ctx->factory->pVtbl->GetTrace(ctx->factory, &trace);
        ఒకవేళ (ret == AMF_OK) {
            పూర్ణాంకం level_ff = av_log_get_level();
            పూర్ణాంకం level_amf = AMF_TRACE_TRACE;
            amf_bool enable_log = true;
            ఎంపిక(level_ff)
            {
            స్థితి AV_LOG_QUIET:
                level_amf = AMF_TRACE_ERROR;
                enable_log = false;
                ఆపు;
            స్థితి AV_LOG_PANIC:
            స్థితి AV_LOG_FATAL:
            స్థితి AV_LOG_ERROR:
                level_amf = AMF_TRACE_ERROR;
                ఆపు;
            స్థితి AV_LOG_WARNING:
            స్థితి AV_LOG_INFO:
                level_amf = AMF_TRACE_WARNING;
                ఆపు;
            స్థితి AV_LOG_VERBOSE:
                level_amf = AMF_TRACE_INFO;
                ఆపు;
            స్థితి AV_LOG_DEBUG:
                level_amf = AMF_TRACE_DEBUG;
                ఆపు;
            స్థితి AV_LOG_TRACE:
                level_amf = AMF_TRACE_TRACE;
                ఆపు;
            }
            ఒకవేళ(ctx->సంస్కరణ == AMF_MAKE_నిండిన_సంస్కరణ(1, 4, 35, 0)){// get around a bug in trace in AMF runtime driver 24.20
                level_amf = AMF_TRACE_WARNING;
            }

            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_CONSOLE, 0);
            trace->pVtbl->సమితి_Global_Level(trace, level_amf);

            // connect AMF logger to av_log
            ctx->trace_writer = amf_writer_alloc(device_ctx);
            trace->pVtbl->రిజిస్టరు_Writer(trace, FFMPEG_AMF_WRITER_ID, (AMFTraceWriter*)ctx->trace_writer, 1);
            trace->pVtbl->సమితి_Writer_Level(trace, FFMPEG_AMF_WRITER_ID, level_amf);
            trace->pVtbl->EnableWriter(trace, FFMPEG_AMF_WRITER_ID, enable_log);
            trace->pVtbl->సమితి_Writer_Level(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, level_amf);
            trace->pVtbl->EnableWriter(trace, AMF_TRACE_WRITER_DEBUG_OUTPUT, enable_log);
        }


        ret = ctx->factory->pVtbl->CreateContext(ctx->factory, &ctx->context);
        ఒకవేళ (ret == AMF_OK) {
            AMF_కేటాయించు_PROPERTY_INT64(ret, ctx->context, L"DeviceSurfaceCacheSize", 50 );
            తిరిగి 0;
        }
        av_log(device_ctx, AV_LOG_ERROR, "CreateContext() failed with error %d.\n", ret);
    }
    amf_device_uninit(device_ctx);
    తిరిగి ret;
}

#ఒకవేళ CONFIG_DXVA2
స్థిర పూర్ణాంకం amf_init_from_dxva2_device(AVAMFDeviceContext * amf_ctx, AVHWDeviceContext *బిడ్డ_device_ctx)
{
    AVDXVA2DeviceContext *hwctx = బిడ్డ_device_ctx->hwctx;
    IDirect3DDevice9    *device;
    HANDLE              device_handle;
    HRESULT             hr;
    AMF_ఫలితం          res;
    పూర్ణాంకం ret;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &device_handle);
    ఒకవేళ (FAILED(hr)) {
        av_log(బిడ్డ_device_ctx, AV_LOG_ERROR, "Failed to open device handle for Direct3D9 device: %lx.\n", (గుర్తులేని దీర్ఘ)hr);
        తిరిగి AVERROR_EXTERNAL;
    }

    hr = IDirect3_DDevice_Manager9_తాళం_Device(hwctx->devmgr, device_handle, &device, FALSE);
    ఒకవేళ (SUCCEEDED(hr)) {
        IDirect3DDeviceManager9_UnlockDevice(hwctx->devmgr, device_handle, FALSE);
        ret = 0;
    } లేకపోతే {
        av_log(బిడ్డ_device_ctx, AV_LOG_ERROR, "Failed to lock device handle for Direct3D9 device: %lx.\n", (గుర్తులేని దీర్ఘ)hr);
        ret = AVERROR_EXTERNAL;
    }


    IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, device_handle);

    ఒకవేళ (ret < 0)
        తిరిగి ret;

    res = amf_ctx->context->pVtbl->InitDX9(amf_ctx->context, device);

    IDirect3DDevice9_Release(device);

    ఒకవేళ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        ఒకవేళ (res == AMF_NOT_SUPPORTED)
            av_log(బిడ్డ_device_ctx, AV_LOG_ERROR, "AMF via D3D9 is not supported on the given device.\n");
        లేకపోతే
            av_log(బిడ్డ_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on given D3D9 device: %d.\n", res);
        తిరిగి AVERROR(ENODEV);
    }
    av_log(బిడ్డ_device_ctx, AV_LOG_INFO, "AMF via DXVA2.\n");
    తిరిగి 0;
}
#అయితే_ముగింపు

#ఒకవేళ CONFIG_D3D11VA
స్థిర పూర్ణాంకం amf_init_from_d3d11_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *బిడ్డ_device_ctx)
{
    AMF_ఫలితం res;
    AVD3D11VADeviceContext *hwctx = బిడ్డ_device_ctx->hwctx;
    res = amf_ctx->context->pVtbl->InitDX11(amf_ctx->context, hwctx->device, AMF_DX11_1);
    ఒకవేళ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        ఒకవేళ (res == AMF_NOT_SUPPORTED)
            av_log(బిడ్డ_device_ctx, AV_LOG_ERROR, "AMF via D3D11 is not supported on the given device.\n");
        లేకపోతే
            av_log(బిడ్డ_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D11 device: %d.\n", res);
        తిరిగి AVERROR(ENODEV);
    }
    av_log(బిడ్డ_device_ctx, AV_LOG_INFO, "AMF via D3D11.\n");
    hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    తిరిగి 0;
}
#అయితే_ముగింపు

#ఒకవేళ CONFIG_D3D12VA
స్థిర పూర్ణాంకం amf_init_from_d3d12_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *బిడ్డ_device_ctx)
{
    AVD3D12VADeviceContext *hwctx = బిడ్డ_device_ctx->hwctx;
    AMF_ఫలితం res;
    AMFContext2 *context2 = ఖాళీ;
    AMFGuid guid = IID_AMFContext2();
    res = amf_ctx->context->pVtbl->QueryInterface(amf_ctx->context, &guid, (శూన్య**)&context2);
    AMF_RETURN_IF_FALSE(బిడ్డ_device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "CreateContext2() failed with error %d\n", res);
    res = context2->pVtbl->InitDX12(context2, hwctx->device, AMF_DX12);
    context2->pVtbl->Release(context2);
    ఒకవేళ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        ఒకవేళ (res == AMF_NOT_SUPPORTED)
            av_log(బిడ్డ_device_ctx, AV_LOG_ERROR, "AMF via D3D12 is not supported on the given device.\n");
        లేకపోతే
            av_log(బిడ్డ_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D12 device: %d.\n", res);
        తిరిగి AVERROR(ENODEV);
    }
    av_log(బిడ్డ_device_ctx, AV_LOG_INFO, "AMF via D3D12.\n");
    తిరిగి 0;
}
#అయితే_ముగింపు


స్థిర పూర్ణాంకం amf_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *బిడ్డ_device_ctx, AVDictionary *opts,
                              పూర్ణాంకం flags)
{
#ఒకవేళ CONFIG_DXVA2 || CONFIG_D3D11VA || CONFIG_D3D12VA
    AVAMFDeviceContext        *amf_ctx = device_ctx->hwctx;
#అయితే_ముగింపు
    పూర్ణాంకం ret;

    ret = amf_device_create(device_ctx, "", opts, flags);
    ఒకవేళ(ret < 0)
        తిరిగి ret;

    ఎంపిక (బిడ్డ_device_ctx->type) {
#ఒకవేళ CONFIG_DXVA2
    స్థితి AV_HWDEVICE_TYPE_DXVA2:
        తిరిగి amf_init_from_dxva2_device(amf_ctx, బిడ్డ_device_ctx);
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D11VA
    స్థితి AV_HWDEVICE_TYPE_D3D11VA:
        తిరిగి amf_init_from_d3d11_device(amf_ctx, బిడ్డ_device_ctx);
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D12VA
    స్థితి AV_HWDEVICE_TYPE_D3D12VA:
        తిరిగి amf_init_from_d3d12_device(amf_ctx, బిడ్డ_device_ctx);
#అయితే_ముగింపు
    అప్రమేయ:
        av_log(బిడ్డ_device_ctx, AV_LOG_ERROR, "AMF initialisation from a %s device is not supported.\n",
               av_hwdevice_get_type_name(బిడ్డ_device_ctx->type));
        తిరిగి AVERROR(ENOSYS);
    }
}

స్థిర శూన్య amf_unmap_చట్రం(av_వాడని AVHWFramesContext *వాడని, HWMapDescriptor *hwmap)
{
    AMFSurface1 *surface1 = hwmap->priv;
    AMF_IFACE_CALL(surface1, Unmap);
    AMF_IFACE_CALL(surface1, Release);
}

స్థిర పూర్ణాంకం amf_map_చట్రం(AVHWFramesContext *device_ctx, AVFrame *dst, స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    AMFSurface *surface = (AMFSurface *)src->దత్తాంశం[0];
    AMFSurface1 *surface1 = ఖాళీ;
    size_t *linesizes = ఖాళీ;
    uint8_t **map = ఖాళీ;
    పూర్ణాంకం amf_mem_flags = AMF_జ్ఞాపకం_CPU_NONE;
    స్థిరరాశి AMFGuid guid = IID_AMFSurface1();
    AMF_ఫలితం res = AMF_FAIL;
    size_t plane_లెక్క = 0;
    పూర్ణాంకం ret = -1;

    AMF_RETURN_IF_FALSE(device_ctx, surface != ఖాళీ, AVERROR(EINVAL) , "Source surface is null");

    res = AMF_IFACE_CALL(surface, QueryInterface, &guid, (శూన్య**)&surface1);
    AMF_RETURN_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "QueryInterface(AMFSurface1) failed with error %d\n", res);

    ఒకవేళ (flags & AV_HWFRAME_MAP_READ)
        amf_mem_flags |= AMF_జ్ఞాపకం_CPU_READ;

    ఒకవేళ (flags & AV_HWFRAME_MAP_WRITE)
        amf_mem_flags |= AMF_జ్ఞాపకం_CPU_WRITE;

    plane_లెక్క = AMF_IFACE_CALL(surface, Get_Planes_లెక్క);
    linesizes = av_malloc_array(పరిమాణం(size_t), plane_లెక్క);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, linesizes, AVERROR(ENOMEM), "Unable to allocate line sizes array\n");

    map = av_malloc_array(పరిమాణం(uint8_t *), plane_లెక్క);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, map, AVERROR(ENOMEM), "Unable to allocate mapping buffer\n");

    dst->format = av_amf_గమ్యం_av_format(AMF_IFACE_CALL(surface, GetFormat));

    res = AMF_IFACE_CALL(surface1, Map, amf_mem_flags, plane_లెక్క, linesizes, (శూన్య**)map);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "AMFSurface1->Map() failed with error %d\n", res);

    ret = ff_hwframe_map_create(src->hw_చట్రాలు_ctx, dst, src, &amf_unmap_చట్రం, surface1);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, ret >= 0, ret, "ff_hwframe_map_create failed with error %d\n", ret);

    dst->వెడల్పు  = src->వెడల్పు;
    dst->ఎత్తు = src->ఎత్తు;
    av_చట్రం_copy_props(dst, src);

    // The dst frame is no longer a hardware frame, from the perspective of any dst frame consumer.
    av_బఫరు_unref(&dst->hw_చట్రాలు_ctx);

    కొరకు (పూర్ణాంకం plane = 0; plane < plane_లెక్క; ++plane)
    {
        dst->దత్తాంశం[plane] = map[plane];
        dst->linesize[plane] = linesizes[plane];
    }

fail:
    ఒకవేళ (map)
        av_free(map);

    ఒకవేళ (linesizes)
        av_free(linesizes);

    ఒకవేళ (ret < 0 && surface1 != ఖాళీ)
        AMF_IFACE_CALL(surface1, Release);

    తిరిగి ret;
}

స్థిరరాశి HWContextType ff_hwcontext_type_amf = {
    .type                 = AV_HWDEVICE_TYPE_AMF,
    .name                 = "AMF",

    .device_hwctx_కొలత    = పరిమాణం(AVAMFDeviceContext),
    .చట్రాలు_hwctx_కొలత    = పరిమాణం(AMFFramesContext),

    .device_create        = amf_device_create,
    .device_derive        = amf_device_derive,
    .device_init          = amf_device_init,
    .device_uninit        = amf_device_uninit,
    .చట్రాలు_get_constraints = amf_చట్రాలు_get_constraints,
    .చట్రాలు_init          = amf_చట్రాలు_init,
    .చట్రాలు_get_బఫరు    = amf_get_బఫరు,
    .transfer_get_formats = amf_transfer_get_formats,
    .transfer_దత్తాంశం_గమ్యం     = amf_transfer_దత్తాంశం_గమ్యం,
    .transfer_దత్తాంశం_from   = amf_transfer_దత్తాంశం_from,
    .map_from             = amf_map_చట్రం,

    .pix_fmts             = (స్థిరరాశి గణన AVPixelFormat[]){ AV_PIX_FMT_AMF_SURFACE, AV_PIX_FMT_NONE },
};
