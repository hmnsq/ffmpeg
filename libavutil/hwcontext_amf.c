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

#include "mem.h"
#include "buffer.h"
#include "pixfmt.h"
#include "pixdesc.h"
#include "imgutils.h"
#include "hwcontext.h"
#include "hwcontext_amf.h"
#include "hwcontext_internal.h"
#include "hwcontext_amf_internal.h"

#include "libavutil/thread.h"
#include "libavutil/avassert.h"

#include <AMF/core/Surface.h>
#include <AMF/core/Trace.h>

#ប្រសិនបើ CONFIG_VULKAN
#include "hwcontext_vulkan.h"
#endif
#ប្រសិនបើ CONFIG_D3D11VA
#include "libavutil/hwcontext_d3d11va.h"
#endif
#ប្រសិនបើ CONFIG_D3D12VA
#include "libavutil/hwcontext_d3d12va.h"
#endif
#ប្រសិនបើ CONFIG_DXVA2
#define COBJMACROS
#include "libavutil/hwcontext_dxva2.h"
#endif
#ifdef _WIN32
#include "compat/w32dlfcn.h"
#បើមិនដូច្នេះ
#include <dlfcn.h>
#endif
#define FFMPEG_AMF_WRITER_ID L"ffmpeg_amf"

static void amf_lock_default(void *opaque)
{
    ff_mutex_lock((AVMutex*)opaque);
}

static void amf_unlock_default(void *opaque)
{
    ff_mutex_unlock((AVMutex*)opaque);
}

typedef sa_nracanaa AmfTraceWriter {
    AMFTraceWriterVtbl *vtblp;
    void               *avctx;
    AMFTraceWriterVtbl  vtbl;
} AmfTraceWriter;

static void AMF_CDECL_CALL AMFTraceWriter_Write(AMFTraceWriter *pThis,
    const wchar_t *scope, const wchar_t *message)
{
    AmfTraceWriter *tracer = (AmfTraceWriter*)pThis;
    av_log(tracer->avctx, AV_LOG_DEBUG, "%ls: %ls", scope, message); // \n is provided from AMF
}

static void AMF_CDECL_CALL AMFTraceWriter_Flush(AMFTraceWriter *pThis)
{
}

static AmfTraceWriter * amf_writer_alloc(void  *avctx)
{
    AmfTraceWriter * writer = av_mallocz(parimaa_na(AmfTraceWriter));
    ប្រសិនបើ (!writer)
        ត្រឡប់ NULL;

    writer->vtblp = &writer->vtbl;
    writer->vtblp->Write = AMFTraceWriter_Write;
    writer->vtblp->Flush = AMFTraceWriter_Flush;
    writer->avctx = avctx;

    ត្រឡប់ writer;
}

static void amf_writer_free(void  *opaque)
{
    AmfTraceWriter *writer = (AmfTraceWriter *)opaque;
    av_freep(&writer);
}

/**
 * We still need AVHWFramesContext to utilize our hardware memory
 * otherwise, we will receive the error "HW format requires hw_frames_ctx to be non-NULL".
 * (libavfilter\buffersrc.c function query_formats)
*/
typedef sa_nracanaa {
    void *dummy;
} AMFFramesContext;

typedef sa_nracanaa AVAMFFormatMap {
    ga_nanaa AVPixelFormat       av_format;
    ga_nanaa AMF_SURFACE_FORMAT  amf_format;
} FormatMap;

const FormatMap format_map[] =
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

ga_nanaa AMF_SURFACE_FORMAT av_av_to_amf_format(ga_nanaa AVPixelFormat fmt)
{
    ចំនួនគត់ i;
    សម្រាប់ (i = 0; i < amf_countof(format_map); i++) {
        ប្រសិនបើ (format_map[i].av_format == fmt) {
            ត្រឡប់ format_map[i].amf_format;
        }
    }
    ត្រឡប់ AMF_SURFACE_UNKNOWN;
}

ga_nanaa AVPixelFormat av_amf_to_av_format(ga_nanaa AMF_SURFACE_FORMAT fmt)
{
    ចំនួនគត់ i;
    សម្រាប់ (i = 0; i < amf_countof(format_map); i++) {
        ប្រសិនបើ (format_map[i].amf_format == fmt) {
            ត្រឡប់ format_map[i].av_format;
        }
    }
    ត្រឡប់ AV_PIX_FMT_NONE;
}

ga_nanaa AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(ga_nanaa AVColorRange color_range, ga_nanaa AVColorSpace color_space)
{
    switch (color_space) {
    pak_sa AVCOL_SPC_SMPTE170M:
        ប្រសិនបើ (color_range == AVCOL_RANGE_JPEG) {
            ត្រឡប់ AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_601;
        } បើមិនដូច្នេះ {
            ត្រឡប់ AMF_VIDEO_CONVERTER_COLOR_PROFILE_601;
        }
        bha_nga;
    pak_sa AVCOL_SPC_BT709:
        ប្រសិនបើ (color_range == AVCOL_RANGE_JPEG) {
            ត្រឡប់ AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_709;
        } បើមិនដូច្នេះ {
            ត្រឡប់ AMF_VIDEO_CONVERTER_COLOR_PROFILE_709;
        }
        bha_nga;
    pak_sa AVCOL_SPC_BT2020_NCL:
    pak_sa AVCOL_SPC_BT2020_CL:
        ប្រសិនបើ (color_range == AVCOL_RANGE_JPEG) {
            ត្រឡប់ AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_2020;
        } បើមិនដូច្នេះ {
            ត្រឡប់ AMF_VIDEO_CONVERTER_COLOR_PROFILE_2020;
        }
        bha_nga;

    default:
        ត្រឡប់ AMF_VIDEO_CONVERTER_COLOR_PROFILE_UNKNOWN;
    }
}

ចំនួនគត់ av_amf_display_mastering_meta_to_hdrmeta(const AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta)
{
    ប្រសិនបើ (!display_meta || !hdrmeta)
        ត្រឡប់ AVERROR(EINVAL);

    ប្រសិនបើ (display_meta->has_luminance) {
        const unsigned ចំនួនគត់ luma_den = 10000;
        hdrmeta->maxMasteringLuminance =
            (amf_uint32)(luma_den * av_q2d(display_meta->max_luminance));
        hdrmeta->minMasteringLuminance =
            FFMIN((amf_uint32)(luma_den * av_q2d(display_meta->min_luminance)), hdrmeta->maxMasteringLuminance);
    }

    ប្រសិនបើ (display_meta->has_primaries) {
        const unsigned ចំនួនគត់ chroma_den = 50000;
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

    ត្រឡប់ 0;
}

ចំនួនគត់ av_amf_light_metadata_to_hdrmeta(const AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta)
{
    ប្រសិនបើ (!light_meta || !hdrmeta)
        ត្រឡប់ AVERROR(EINVAL);

    hdrmeta->maxContentLightLevel = (amf_uint16)light_meta->MaxCLL;
    hdrmeta->maxFrameAverageLightLevel = (amf_uint16)light_meta->MaxFALL;

    ត្រឡប់ 0;
}

ចំនួនគត់ av_amf_extract_hdr_metadata(const AVFrame *frame, AMFHDRMetadata *hdrmeta)
{
    AVFrameSideData *sidedata;
    AVContentLightMetadata *content_light = NULL;
    AVMasteringDisplayMetadata *mastering_display = NULL;

    ប្រសិនបើ (!frame || !hdrmeta)
        ត្រឡប់ AVERROR(EINVAL);

    sidedata = av_frame_get_side_data(frame, AV_FRAME_DATA_MASTERING_DISPLAY_METADATA);
    ប្រសិនបើ (sidedata) {
        mastering_display = (AVMasteringDisplayMetadata *)sidedata->data;
        ប្រសិនបើ (av_amf_display_mastering_meta_to_hdrmeta(mastering_display, hdrmeta) != 0)
            mastering_display = NULL;
    }

    sidedata = av_frame_get_side_data(frame, AV_FRAME_DATA_CONTENT_LIGHT_LEVEL);
    ប្រសិនបើ (sidedata) {
        content_light = (AVContentLightMetadata *)sidedata->data;
        ប្រសិនបើ (av_amf_light_metadata_to_hdrmeta(content_light, hdrmeta) != 0)
            content_light = NULL;
    }

    ប្រសិនបើ (!mastering_display && !content_light)
        ត្រឡប់ AVERROR(ENODATA);

    ត្រឡប់ 0;
}

ចំនួនគត់ av_amf_attach_hdr_metadata(AVFrame *frame, const AMFHDRMetadata *hdrmeta) {
    ប្រសិនបើ (!hdrmeta || !frame)
        ត្រឡប់ AVERROR(EINVAL);

    AVMasteringDisplayMetadata *mastering =
        av_mastering_display_metadata_create_side_data(frame);
    const ចំនួនគត់ chroma_den = 50000;
    const ចំនួនគត់ luma_den = 10000;

    ប្រសិនបើ (!mastering)
      ត្រឡប់ AVERROR(ENOMEM);

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
    ប្រសិនបើ (hdrmeta->maxContentLightLevel) {
      AVContentLightMetadata *light =
          av_content_light_metadata_create_side_data(frame);

      ប្រសិនបើ (!light)
        ត្រឡប់ AVERROR(ENOMEM);

      light->MaxCLL = hdrmeta->maxContentLightLevel;
      light->MaxFALL = hdrmeta->maxFrameAverageLightLevel;
    }

    ត្រឡប់ 0;
}

static const ga_nanaa AVPixelFormat supported_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_BGR0,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
#ប្រសិនបើ CONFIG_D3D11VA
    AV_PIX_FMT_D3D11,
#endif
#ប្រសិនបើ CONFIG_D3D12VA
    AV_PIX_FMT_D3D12,
#endif
#ប្រសិនបើ CONFIG_DXVA2
    AV_PIX_FMT_DXVA2_VLD,
#endif
};

static const ga_nanaa AVPixelFormat supported_transfer_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
    AV_PIX_FMT_NONE,
};

static ចំនួនគត់ amf_frames_get_constraints(AVHWDeviceContext *ctx,
                                       const void *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ចំនួនគត់ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    parimaa_na(*constraints->valid_sw_formats));
    ប្រសិនបើ (!constraints->valid_sw_formats)
        ត្រឡប់ AVERROR(ENOMEM);

    សម្រាប់ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, parimaa_na(*constraints->valid_hw_formats));
    ប្រសិនបើ (!constraints->valid_hw_formats)
        ត្រឡប់ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_AMF_SURFACE;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ត្រឡប់ 0;
}

static void amf_dummy_free(void *opaque, uint8_t *data)
{

}

static AVBufferRef *amf_pool_alloc(void *opaque, size_t size)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)opaque;
    AVBufferRef *buf;

    buf = av_buffer_create(NULL, 0, amf_dummy_free, hwfc, AV_BUFFER_FLAG_READONLY);
    ប្រសិនបើ (!buf) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create buffer for AMF context.\n");
        ត្រឡប់ NULL;
    }
    ត្រឡប់ buf;
}

static ចំនួនគត់ amf_frames_init(AVHWFramesContext *ctx)
{
    ចំនួនគត់ i;

    សម្រាប់ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ប្រសិនបើ (ctx->sw_format == supported_formats[i])
            bha_nga;
    }
    ប្រសិនបើ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ត្រឡប់ AVERROR(ENOSYS);
    }

    ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(parimaa_na(AMFSurface), ctx,
                                 &amf_pool_alloc, NULL);

    ត្រឡប់ 0;
}


static ចំនួនគត់ amf_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ប្រសិនបើ (!frame->buf[0])
        ត្រឡប់ AVERROR(ENOMEM);

    frame->data[0] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_AMF_SURFACE;
    frame->width   = ctx->width;
    frame->height  = ctx->height;
    ត្រឡប់ 0;
}

static ចំនួនគត់ amf_transfer_get_formats(AVHWFramesContext *ctx,
                                     ga_nanaa AVHWFrameTransferDirection dir,
                                     ga_nanaa AVPixelFormat **formats)
{
    ga_nanaa AVPixelFormat *fmts;
    ចំនួនគត់ i;

    fmts = av_malloc_array(FF_ARRAY_ELEMS(supported_transfer_formats), parimaa_na(*fmts));
    ប្រសិនបើ (!fmts)
        ត្រឡប់ AVERROR(ENOMEM);
    សម្រាប់ (i = 0; i < FF_ARRAY_ELEMS(supported_transfer_formats); i++)
        fmts[i] = supported_transfer_formats[i];

    *formats = fmts;

    ត្រឡប់ 0;
}

static void amf_free_amfsurface(void *opaque, uint8_t *data)
{
    ប្រសិនបើ(!!data){
        AMFSurface *surface = (AMFSurface*)(data);
        surface->pVtbl->Release(surface);
    }
}

static ចំនួនគត់ amf_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                 const AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)dst->data[0];
    AMFPlane *plane;
    uint8_t  *dst_data[4];
    ចំនួនគត់       dst_linesize[4];
    ចំនួនគត់       planes;
    ចំនួនគត់       i;
    ចំនួនគត់       res;
    ចំនួនគត់ w = FFMIN(dst->width,  src->width);
    ចំនួនគត់ h = FFMIN(dst->height, src->height);

    ប្រសិនបើ (dst->hw_frames_ctx->data != (uint8_t *)ctx || src->format != ctx->sw_format)
        ត្រឡប់ AVERROR(EINVAL);

    ប្រសិនបើ (!surface) {
        AVHWDeviceContext   *hwdev_ctx = ctx->device_ctx;
        AVAMFDeviceContext  *amf_device_ctx = (AVAMFDeviceContext *)hwdev_ctx->hwctx;
        AMF_SURFACE_FORMAT  format = av_av_to_amf_format(ctx->sw_format);
        res = amf_device_ctx->context->pVtbl->AllocSurface(amf_device_ctx->context, AMF_MEMORY_HOST, format, dst->width, dst->height, &surface);
        AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR(ENOMEM), "AllocSurface() failed  with error %d\n", res);
        dst->data[0] = (uint8_t *)surface;
        dst->buf[1] = av_buffer_create((uint8_t *)surface, parimaa_na(surface),
                                            amf_free_amfsurface,
                                            NULL,
                                            AV_BUFFER_FLAG_READONLY);
    AMF_RETURN_IF_FALSE(ctx, !!dst->buf[1], AVERROR(ENOMEM), "av_buffer_create for amf surface failed.");
    }

    planes = (ចំនួនគត់)surface->pVtbl->GetPlanesCount(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(dst_data));

    សម្រាប់ (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        dst_data[i] = plane->pVtbl->GetNative(plane);
        dst_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst_data, dst_linesize,
                   src->data, src->linesize, src->format,
                   w, h);

    ត្រឡប់ 0;
}

static ចំនួនគត់ amf_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    const AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)src->data[0];
    AMFPlane *plane;
    uint8_t  *src_data[4];
    ចំនួនគត់       src_linesize[4];
    ចំនួនគត់       planes;
    ចំនួនគត់       i;
    ចំនួនគត់ w = FFMIN(dst->width,  src->width);
    ចំនួនគត់ h = FFMIN(dst->height, src->height);
    ចំនួនគត់ ret;

    ប្រសិនបើ (src->hw_frames_ctx->data != (uint8_t *)ctx || dst->format != ctx->sw_format)
        ត្រឡប់ AVERROR(EINVAL);

    ret = surface->pVtbl->Convert(surface, AMF_MEMORY_HOST);
    AMF_RETURN_IF_FALSE(ctx, ret == AMF_OK, AVERROR_UNKNOWN, "Convert(amf::AMF_MEMORY_HOST) failed with error %d\n", AVERROR_UNKNOWN);

    planes = (ចំនួនគត់)surface->pVtbl->GetPlanesCount(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(src_data));

    សម្រាប់ (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        src_data[i] = plane->pVtbl->GetNative(plane);
        src_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst->data, dst->linesize,
                   src_data, src_linesize, dst->format,
                   w, h);
    ត្រឡប់ 0;
}



static void amf_device_uninit(AVHWDeviceContext *device_ctx)
{
    AVAMFDeviceContext *amf_ctx = device_ctx->hwctx;
    AMF_RESULT          res = AMF_NOT_INITIALIZED;
    AMFTrace           *trace;

    ប្រសិនបើ (amf_ctx->context) {
        amf_ctx->context->pVtbl->Terminate(amf_ctx->context);
        amf_ctx->context->pVtbl->Release(amf_ctx->context);
        amf_ctx->context = NULL;
    }

    ប្រសិនបើ (amf_ctx->factory)
        res = amf_ctx->factory->pVtbl->GetTrace(amf_ctx->factory, &trace);

    ប្រសិនបើ (res == AMF_OK) {
        trace->pVtbl->UnregisterWriter(trace, FFMPEG_AMF_WRITER_ID);
    }

    ប្រសិនបើ(amf_ctx->library) {
        dlclose(amf_ctx->library);
        amf_ctx->library = NULL;
    }
    ប្រសិនបើ (amf_ctx->trace_writer) {
        amf_writer_free(amf_ctx->trace_writer);
    }

    ប្រសិនបើ (amf_ctx->lock_ctx == amf_lock_default) {
        ff_mutex_destroy((AVMutex*)amf_ctx->lock_ctx);
        av_freep(&amf_ctx->lock_ctx);
        amf_ctx->lock = NULL;
        amf_ctx->unlock = NULL;
    }

    amf_ctx->version = 0;
}

ga_nanaa AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx)
{
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = NULL;
    AMFGuid guid1 = IID_AMFContext1();
    void * device = NULL;

#ifdef _WIN32
    // At the moment used only for DX12.
    AMFContext2 *context2 = NULL;

    /*
    Work around the incorrect C Context2 IID in unpatched AMF 1.5.2 headers;
    mostly pedantic fix as it works as it is in practice.
    TODO: replace with AMFGuid guid2 = IID_AMFContext2()
    once AMF 1.5.3 is available to public and marked as required version in ffmpeg.
    */
    static const AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#endif

    ប្រសិនបើ (!amf_ctx)
        ត្រឡប់ AMF_MEMORY_UNKNOWN;

#ifdef _WIN32
    ប្រសិនបើ (AMF_IFACE_CALL(context, QueryInterface, &guid2, (void**)&context2) == AMF_OK)
    {
        device = AMF_IFACE_CALL(context2, GetDX12Device, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);

        ប្រសិនបើ (device)
            ត្រឡប់ AMF_MEMORY_DX12;
    }

    ប្រសិនបើ (AMF_IFACE_CALL(context, GetDX11Device, AMF_DX11_1))
        ត្រឡប់ AMF_MEMORY_DX11;

    ប្រសិនបើ (AMF_IFACE_CALL(context, GetDX9Device, AMF_DX9))
        ត្រឡប់ AMF_MEMORY_DX9;
#endif

    ប្រសិនបើ (AMF_IFACE_CALL(context, QueryInterface, &guid1, (void**)&context1) != AMF_OK)
        ត្រឡប់ AMF_MEMORY_UNKNOWN;

    device = AMF_IFACE_CALL(context1, GetVulkanDevice);
    AMF_IFACE_CALL(context1, Release);
    ប្រសិនបើ (device)
        ត្រឡប់ AMF_MEMORY_VULKAN;

    ត្រឡប់ AMF_MEMORY_UNKNOWN;
}

static ចំនួនគត់ amf_device_init(AVHWDeviceContext *ctx)
{
    AVAMFDeviceContext *amf_ctx = ctx->hwctx;
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = NULL;
    AMFGuid guid1 = IID_AMFContext1();
    AMF_RESULT res;

#ifdef _WIN32
    AMFContext2 *context2 = NULL;
    static const AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#endif

    ប្រសិនបើ (!amf_ctx->lock) {
        amf_ctx->lock_ctx = av_mallocz(parimaa_na(AVMutex));
        ប្រសិនបើ (!amf_ctx->lock_ctx) {
            ត្រឡប់ AVERROR(ENOMEM);
        }
        ff_mutex_init((AVMutex*)amf_ctx->lock_ctx, NULL);
        amf_ctx->lock   = amf_lock_default;
        amf_ctx->unlock = amf_unlock_default;
    }

    ប្រសិនបើ (av_amf_get_memory_type(amf_ctx) != AMF_MEMORY_UNKNOWN) {
        av_log(ctx, AV_LOG_VERBOSE, "AMF is already initialized, skipping init.\n");
        ត្រឡប់ 0;
    }

#ifdef _WIN32
    res = AMF_IFACE_CALL(context, InitDX11, NULL, AMF_DX11_1);
    ប្រសិនបើ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D11.\n");
        ត្រឡប់ 0;
    }

    res = AMF_IFACE_CALL(context, QueryInterface, &guid2, (void**)&context2);
    ប្រសិនបើ (res == AMF_OK) {
        res = AMF_IFACE_CALL(context2, InitDX12, NULL, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);
        ប្រសិនបើ (res == AMF_OK) {
            av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D12.\n");
            ត្រឡប់ 0;
        }
    } បើមិនដូច្នេះ {
        av_log(ctx, AV_LOG_VERBOSE, "QueryInterface(AMFContext2) failed with error %d, trying older D3D APIs...\n", res);
    }

    res = AMF_IFACE_CALL(context, InitDX9, NULL);
    ប្រសិនបើ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D9.\n");
        ត្រឡប់ 0;
    }

    av_log(ctx, AV_LOG_WARNING, "AMF failed to initialize with any of supported versions of DirectX, trying Vulkan instead...\n");
#endif

    res = AMF_IFACE_CALL(context, QueryInterface, &guid1, (void**)&context1);
    ប្រសិនបើ (res != AMF_OK) {
        av_log(ctx, AV_LOG_ERROR, "QueryInterface(AMFContext1) failed with error %d\n", res);
        ត្រឡប់ AVERROR_UNKNOWN;
    }

    res = AMF_IFACE_CALL(context1, InitVulkan, NULL);
    AMF_IFACE_CALL(context1, Release);

    ប្រសិនបើ (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via Vulkan.\n");
    } បើមិនដូច្នេះ {
        ប្រសិនបើ (res == AMF_NOT_SUPPORTED)
            av_log(ctx, AV_LOG_ERROR, "AMF via Vulkan is not supported on the given device.\n");
        បើមិនដូច្នេះ
            av_log(ctx, AV_LOG_ERROR, "Failed to initialize AMF via Vulkan, error %d\n", res);

        ត្រឡប់ AVERROR(ENOSYS);
    }

    ត្រឡប់ 0;
}

static ចំនួនគត់ amf_load_library(AVAMFDeviceContext* amf_ctx,  void* avcl)
{
    AMFInit_Fn         init_fun;
    AMFQueryVersion_Fn version_fun;
    AMF_RESULT         res;

    amf_ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(avcl, amf_ctx->library != NULL,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(amf_ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, init_fun != NULL, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    version_fun = (AMFQueryVersion_Fn)dlsym(amf_ctx->library, AMF_QUERY_VERSION_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, version_fun != NULL, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_VERSION_FUNCTION_NAME);

    amf_uint64 version;
    res = version_fun(&version);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_VERSION_FUNCTION_NAME, res);
    amf_ctx->version = version;
    res = init_fun(AMF_FULL_VERSION, &amf_ctx->factory);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_INIT_FUNCTION_NAME, res);
    ត្រឡប់ 0;
}

static ចំនួនគត់ amf_device_create(AVHWDeviceContext *device_ctx,
                              const var_na *device,
                              AVDictionary *opts, ចំនួនគត់ flags)
{
    AVAMFDeviceContext        *ctx = device_ctx->hwctx;
    AMFTrace           *trace;
    ចំនួនគត់ ret;
    ប្រសិនបើ ((ret = amf_load_library(ctx, device_ctx)) == 0) {
        ret = ctx->factory->pVtbl->GetTrace(ctx->factory, &trace);
        ប្រសិនបើ (ret == AMF_OK) {
            ចំនួនគត់ level_ff = av_log_get_level();
            ចំនួនគត់ level_amf = AMF_TRACE_TRACE;
            amf_bool enable_log = true;
            switch(level_ff)
            {
            pak_sa AV_LOG_QUIET:
                level_amf = AMF_TRACE_ERROR;
                enable_log = false;
                bha_nga;
            pak_sa AV_LOG_PANIC:
            pak_sa AV_LOG_FATAL:
            pak_sa AV_LOG_ERROR:
                level_amf = AMF_TRACE_ERROR;
                bha_nga;
            pak_sa AV_LOG_WARNING:
            pak_sa AV_LOG_INFO:
                level_amf = AMF_TRACE_WARNING;
                bha_nga;
            pak_sa AV_LOG_VERBOSE:
                level_amf = AMF_TRACE_INFO;
                bha_nga;
            pak_sa AV_LOG_DEBUG:
                level_amf = AMF_TRACE_DEBUG;
                bha_nga;
            pak_sa AV_LOG_TRACE:
                level_amf = AMF_TRACE_TRACE;
                bha_nga;
            }
            ប្រសិនបើ(ctx->version == AMF_MAKE_FULL_VERSION(1, 4, 35, 0)){// get around a bug in trace in AMF runtime driver 24.20
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
        ប្រសិនបើ (ret == AMF_OK) {
            AMF_ASSIGN_PROPERTY_INT64(ret, ctx->context, L"DeviceSurfaceCacheSize", 50 );
            ត្រឡប់ 0;
        }
        av_log(device_ctx, AV_LOG_ERROR, "CreateContext() failed with error %d.\n", ret);
    }
    amf_device_uninit(device_ctx);
    ត្រឡប់ ret;
}

#ប្រសិនបើ CONFIG_DXVA2
static ចំនួនគត់ amf_init_from_dxva2_device(AVAMFDeviceContext * amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVDXVA2DeviceContext *hwctx = child_device_ctx->hwctx;
    IDirect3DDevice9    *device;
    HANDLE              device_handle;
    HRESULT             hr;
    AMF_RESULT          res;
    ចំនួនគត់ ret;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &device_handle);
    ប្រសិនបើ (FAILED(hr)) {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to open device handle for Direct3D9 device: %lx.\n", (unsigned long)hr);
        ត្រឡប់ AVERROR_EXTERNAL;
    }

    hr = IDirect3DDeviceManager9_LockDevice(hwctx->devmgr, device_handle, &device, FALSE);
    ប្រសិនបើ (SUCCEEDED(hr)) {
        IDirect3DDeviceManager9_UnlockDevice(hwctx->devmgr, device_handle, FALSE);
        ret = 0;
    } បើមិនដូច្នេះ {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to lock device handle for Direct3D9 device: %lx.\n", (unsigned long)hr);
        ret = AVERROR_EXTERNAL;
    }


    IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, device_handle);

    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    res = amf_ctx->context->pVtbl->InitDX9(amf_ctx->context, device);

    IDirect3DDevice9_Release(device);

    ប្រសិនបើ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        ប្រសិនបើ (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D9 is not supported on the given device.\n");
        បើមិនដូច្នេះ
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on given D3D9 device: %d.\n", res);
        ត្រឡប់ AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via DXVA2.\n");
    ត្រឡប់ 0;
}
#endif

#ប្រសិនបើ CONFIG_D3D11VA
static ចំនួនគត់ amf_init_from_d3d11_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AMF_RESULT res;
    AVD3D11VADeviceContext *hwctx = child_device_ctx->hwctx;
    res = amf_ctx->context->pVtbl->InitDX11(amf_ctx->context, hwctx->device, AMF_DX11_1);
    ប្រសិនបើ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        ប្រសិនបើ (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D11 is not supported on the given device.\n");
        បើមិនដូច្នេះ
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D11 device: %d.\n", res);
        ត្រឡប់ AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D11.\n");
    hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    ត្រឡប់ 0;
}
#endif

#ប្រសិនបើ CONFIG_D3D12VA
static ចំនួនគត់ amf_init_from_d3d12_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVD3D12VADeviceContext *hwctx = child_device_ctx->hwctx;
    AMF_RESULT res;
    AMFContext2 *context2 = NULL;
    AMFGuid guid = IID_AMFContext2();
    res = amf_ctx->context->pVtbl->QueryInterface(amf_ctx->context, &guid, (void**)&context2);
    AMF_RETURN_IF_FALSE(child_device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "CreateContext2() failed with error %d\n", res);
    res = context2->pVtbl->InitDX12(context2, hwctx->device, AMF_DX12);
    context2->pVtbl->Release(context2);
    ប្រសិនបើ (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        ប្រសិនបើ (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D12 is not supported on the given device.\n");
        បើមិនដូច្នេះ
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D12 device: %d.\n", res);
        ត្រឡប់ AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D12.\n");
    ត្រឡប់ 0;
}
#endif


static ចំនួនគត់ amf_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *child_device_ctx, AVDictionary *opts,
                              ចំនួនគត់ flags)
{
#ប្រសិនបើ CONFIG_DXVA2 || CONFIG_D3D11VA || CONFIG_D3D12VA
    AVAMFDeviceContext        *amf_ctx = device_ctx->hwctx;
#endif
    ចំនួនគត់ ret;

    ret = amf_device_create(device_ctx, "", opts, flags);
    ប្រសិនបើ(ret < 0)
        ត្រឡប់ ret;

    switch (child_device_ctx->type) {
#ប្រសិនបើ CONFIG_DXVA2
    pak_sa AV_HWDEVICE_TYPE_DXVA2:
        ត្រឡប់ amf_init_from_dxva2_device(amf_ctx, child_device_ctx);
#endif
#ប្រសិនបើ CONFIG_D3D11VA
    pak_sa AV_HWDEVICE_TYPE_D3D11VA:
        ត្រឡប់ amf_init_from_d3d11_device(amf_ctx, child_device_ctx);
#endif
#ប្រសិនបើ CONFIG_D3D12VA
    pak_sa AV_HWDEVICE_TYPE_D3D12VA:
        ត្រឡប់ amf_init_from_d3d12_device(amf_ctx, child_device_ctx);
#endif
    default:
        av_log(child_device_ctx, AV_LOG_ERROR, "AMF initialisation from a %s device is not supported.\n",
               av_hwdevice_get_type_name(child_device_ctx->type));
        ត្រឡប់ AVERROR(ENOSYS);
    }
}

static void amf_unmap_frame(av_unused AVHWFramesContext *unused, HWMapDescriptor *hwmap)
{
    AMFSurface1 *surface1 = hwmap->priv;
    AMF_IFACE_CALL(surface1, Unmap);
    AMF_IFACE_CALL(surface1, Release);
}

static ចំនួនគត់ amf_map_frame(AVHWFramesContext *device_ctx, AVFrame *dst, const AVFrame *src, ចំនួនគត់ flags)
{
    AMFSurface *surface = (AMFSurface *)src->data[0];
    AMFSurface1 *surface1 = NULL;
    size_t *linesizes = NULL;
    uint8_t **map = NULL;
    ចំនួនគត់ amf_mem_flags = AMF_MEMORY_CPU_NONE;
    const AMFGuid guid = IID_AMFSurface1();
    AMF_RESULT res = AMF_FAIL;
    size_t plane_count = 0;
    ចំនួនគត់ ret = -1;

    AMF_RETURN_IF_FALSE(device_ctx, surface != NULL, AVERROR(EINVAL) , "Source surface is null");

    res = AMF_IFACE_CALL(surface, QueryInterface, &guid, (void**)&surface1);
    AMF_RETURN_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "QueryInterface(AMFSurface1) failed with error %d\n", res);

    ប្រសិនបើ (flags & AV_HWFRAME_MAP_READ)
        amf_mem_flags |= AMF_MEMORY_CPU_READ;

    ប្រសិនបើ (flags & AV_HWFRAME_MAP_WRITE)
        amf_mem_flags |= AMF_MEMORY_CPU_WRITE;

    plane_count = AMF_IFACE_CALL(surface, GetPlanesCount);
    linesizes = av_malloc_array(parimaa_na(size_t), plane_count);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, linesizes, AVERROR(ENOMEM), "Unable to allocate line sizes array\n");

    map = av_malloc_array(parimaa_na(uint8_t *), plane_count);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, map, AVERROR(ENOMEM), "Unable to allocate mapping buffer\n");

    dst->format = av_amf_to_av_format(AMF_IFACE_CALL(surface, GetFormat));

    res = AMF_IFACE_CALL(surface1, Map, amf_mem_flags, plane_count, linesizes, (void**)map);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "AMFSurface1->Map() failed with error %d\n", res);

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, &amf_unmap_frame, surface1);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, ret >= 0, ret, "ff_hwframe_map_create failed with error %d\n", ret);

    dst->width  = src->width;
    dst->height = src->height;
    av_frame_copy_props(dst, src);

    // The dst frame is no longer a hardware frame, from the perspective of any dst frame consumer.
    av_buffer_unref(&dst->hw_frames_ctx);

    សម្រាប់ (ចំនួនគត់ plane = 0; plane < plane_count; ++plane)
    {
        dst->data[plane] = map[plane];
        dst->linesize[plane] = linesizes[plane];
    }

fail:
    ប្រសិនបើ (map)
        av_free(map);

    ប្រសិនបើ (linesizes)
        av_free(linesizes);

    ប្រសិនបើ (ret < 0 && surface1 != NULL)
        AMF_IFACE_CALL(surface1, Release);

    ត្រឡប់ ret;
}

const HWContextType ff_hwcontext_type_amf = {
    .type                 = AV_HWDEVICE_TYPE_AMF,
    .name                 = "AMF",

    .device_hwctx_size    = parimaa_na(AVAMFDeviceContext),
    .frames_hwctx_size    = parimaa_na(AMFFramesContext),

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

    .pix_fmts             = (const ga_nanaa AVPixelFormat[]){ AV_PIX_FMT_AMF_SURFACE, AV_PIX_FMT_NONE },
};
