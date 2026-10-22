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

#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "buffer.h"
#અન્તર્ભાવ "pixfmt.h"
#અન્તર્ભાવ "pixdesc.h"
#અન્તર્ભાવ "imgutils.h"
#અન્તર્ભાવ "hwcontext.h"
#અન્તર્ભાવ "hwcontext_amf.h"
#અન્તર્ભાવ "hwcontext_internal.h"
#અન્તર્ભાવ "hwcontext_amf_internal.h"

#અન્તર્ભાવ "libavutil/thread.h"
#અન્તર્ભાવ "libavutil/avassert.h"

#અન્તર્ભાવ <AMF/core/Surface.h>
#અન્તર્ભાવ <AMF/core/Trace.h>

#જો CONFIG_VULKAN
#અન્તર્ભાવ "hwcontext_vulkan.h"
#endif
#જો CONFIG_D3D11VA
#અન્તર્ભાવ "libavutil/hwcontext_d3d11va.h"
#endif
#જો CONFIG_D3D12VA
#અન્તર્ભાવ "libavutil/hwcontext_d3d12va.h"
#endif
#જો CONFIG_DXVA2
#define COBJMACROS
#અન્તર્ભાવ "libavutil/hwcontext_dxva2.h"
#endif
#ifdef _WIN32
#અન્તર્ભાવ "compat/w32dlfcn.h"
#નહીંતર
#અન્તર્ભાવ <dlfcn.h>
#endif
#define FFMPEG_AMF_WRITER_ID L"ffmpeg_amf"

સ્થિર શૂન્ય amf_lock_default(શૂન્ય *opaque)
{
    ff_mutex_lock((AVMutex*)opaque);
}

સ્થિર શૂન્ય amf_unlock_default(શૂન્ય *opaque)
{
    ff_mutex_unlock((AVMutex*)opaque);
}

પ્રકારવ્યાખ્યા સંરચના AmfTraceWriter {
    AMFTraceWriterVtbl *vtblp;
    શૂન્ય               *avctx;
    AMFTraceWriterVtbl  vtbl;
} AmfTraceWriter;

સ્થિર શૂન્ય AMF_CDECL_CALL AMFTraceWriter_Write(AMFTraceWriter *pThis,
    અચલ wchar_t *scope, અચલ wchar_t *message)
{
    AmfTraceWriter *tracer = (AmfTraceWriter*)pThis;
    av_log(tracer->avctx, AV_LOG_DEBUG, "%ls: %ls", scope, message); // \n is provided from AMF
}

સ્થિર શૂન્ય AMF_CDECL_CALL AMFTraceWriter_Flush(AMFTraceWriter *pThis)
{
}

સ્થિર AmfTraceWriter * amf_writer_alloc(શૂન્ય  *avctx)
{
    AmfTraceWriter * writer = av_mallocz(કદ(AmfTraceWriter));
    જો (!writer)
        પાછા ખાલી;

    writer->vtblp = &writer->vtbl;
    writer->vtblp->Write = AMFTraceWriter_Write;
    writer->vtblp->Flush = AMFTraceWriter_Flush;
    writer->avctx = avctx;

    પાછા writer;
}

સ્થિર શૂન્ય amf_writer_free(શૂન્ય  *opaque)
{
    AmfTraceWriter *writer = (AmfTraceWriter *)opaque;
    av_freep(&writer);
}

/**
 * We still need AVHWFramesContext to utilize our hardware memory
 * otherwise, we will receive the error "HW format requires hw_frames_ctx to be non-NULL".
 * (libavfilter\buffersrc.c function query_formats)
*/
પ્રકારવ્યાખ્યા સંરચના {
    શૂન્ય *dummy;
} AMFFramesContext;

પ્રકારવ્યાખ્યા સંરચના AVAMFFormatMap {
    ગણના AVPixelFormat       av_format;
    ગણના AMF_SURFACE_FORMAT  amf_format;
} FormatMap;

અચલ FormatMap format_map[] =
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

ગણના AMF_SURFACE_FORMAT av_av_to_amf_format(ગણના AVPixelFormat fmt)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < amf_countof(format_map); i++) {
        જો (format_map[i].av_format == fmt) {
            પાછા format_map[i].amf_format;
        }
    }
    પાછા AMF_SURFACE_UNKNOWN;
}

ગણના AVPixelFormat av_amf_to_av_format(ગણના AMF_SURFACE_FORMAT fmt)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < amf_countof(format_map); i++) {
        જો (format_map[i].amf_format == fmt) {
            પાછા format_map[i].av_format;
        }
    }
    પાછા AV_PIX_FMT_NONE;
}

ગણના AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(ગણના AVColorRange color_range, ગણના AVColorSpace color_space)
{
    પસંદગી (color_space) {
    સ્થિતિ AVCOL_SPC_SMPTE170M:
        જો (color_range == AVCOL_RANGE_JPEG) {
            પાછા AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_601;
        } નહીંતર {
            પાછા AMF_VIDEO_CONVERTER_COLOR_PROFILE_601;
        }
        તોડો;
    સ્થિતિ AVCOL_SPC_BT709:
        જો (color_range == AVCOL_RANGE_JPEG) {
            પાછા AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_709;
        } નહીંતર {
            પાછા AMF_VIDEO_CONVERTER_COLOR_PROFILE_709;
        }
        તોડો;
    સ્થિતિ AVCOL_SPC_BT2020_NCL:
    સ્થિતિ AVCOL_SPC_BT2020_CL:
        જો (color_range == AVCOL_RANGE_JPEG) {
            પાછા AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_2020;
        } નહીંતર {
            પાછા AMF_VIDEO_CONVERTER_COLOR_PROFILE_2020;
        }
        તોડો;

    મૂળભૂત:
        પાછા AMF_VIDEO_CONVERTER_COLOR_PROFILE_UNKNOWN;
    }
}

પૂર્ણાંક av_amf_display_mastering_meta_to_hdrmeta(અચલ AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta)
{
    જો (!display_meta || !hdrmeta)
        પાછા AVERROR(EINVAL);

    જો (display_meta->has_luminance) {
        અચલ unsigned પૂર્ણાંક luma_den = 10000;
        hdrmeta->maxMasteringLuminance =
            (amf_uint32)(luma_den * av_q2d(display_meta->max_luminance));
        hdrmeta->minMasteringLuminance =
            FFMIN((amf_uint32)(luma_den * av_q2d(display_meta->min_luminance)), hdrmeta->maxMasteringLuminance);
    }

    જો (display_meta->has_primaries) {
        અચલ unsigned પૂર્ણાંક chroma_den = 50000;
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

    પાછા 0;
}

પૂર્ણાંક av_amf_light_metadata_to_hdrmeta(અચલ AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta)
{
    જો (!light_meta || !hdrmeta)
        પાછા AVERROR(EINVAL);

    hdrmeta->maxContentLightLevel = (amf_uint16)light_meta->MaxCLL;
    hdrmeta->maxFrameAverageLightLevel = (amf_uint16)light_meta->MaxFALL;

    પાછા 0;
}

પૂર્ણાંક av_amf_extract_hdr_metadata(અચલ AVFrame *frame, AMFHDRMetadata *hdrmeta)
{
    AVFrameSideData *sidedata;
    AVContentLightMetadata *content_light = ખાલી;
    AVMasteringDisplayMetadata *mastering_display = ખાલી;

    જો (!frame || !hdrmeta)
        પાછા AVERROR(EINVAL);

    sidedata = av_frame_get_side_data(frame, AV_FRAME_DATA_MASTERING_DISPLAY_METADATA);
    જો (sidedata) {
        mastering_display = (AVMasteringDisplayMetadata *)sidedata->data;
        જો (av_amf_display_mastering_meta_to_hdrmeta(mastering_display, hdrmeta) != 0)
            mastering_display = ખાલી;
    }

    sidedata = av_frame_get_side_data(frame, AV_FRAME_DATA_CONTENT_LIGHT_LEVEL);
    જો (sidedata) {
        content_light = (AVContentLightMetadata *)sidedata->data;
        જો (av_amf_light_metadata_to_hdrmeta(content_light, hdrmeta) != 0)
            content_light = ખાલી;
    }

    જો (!mastering_display && !content_light)
        પાછા AVERROR(ENODATA);

    પાછા 0;
}

પૂર્ણાંક av_amf_attach_hdr_metadata(AVFrame *frame, અચલ AMFHDRMetadata *hdrmeta) {
    જો (!hdrmeta || !frame)
        પાછા AVERROR(EINVAL);

    AVMasteringDisplayMetadata *mastering =
        av_mastering_display_metadata_create_side_data(frame);
    અચલ પૂર્ણાંક chroma_den = 50000;
    અચલ પૂર્ણાંક luma_den = 10000;

    જો (!mastering)
      પાછા AVERROR(ENOMEM);

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
    જો (hdrmeta->maxContentLightLevel) {
      AVContentLightMetadata *light =
          av_content_light_metadata_create_side_data(frame);

      જો (!light)
        પાછા AVERROR(ENOMEM);

      light->MaxCLL = hdrmeta->maxContentLightLevel;
      light->MaxFALL = hdrmeta->maxFrameAverageLightLevel;
    }

    પાછા 0;
}

સ્થિર અચલ ગણના AVPixelFormat supported_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_BGR0,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
#જો CONFIG_D3D11VA
    AV_PIX_FMT_D3D11,
#endif
#જો CONFIG_D3D12VA
    AV_PIX_FMT_D3D12,
#endif
#જો CONFIG_DXVA2
    AV_PIX_FMT_DXVA2_VLD,
#endif
};

સ્થિર અચલ ગણના AVPixelFormat supported_transfer_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
    AV_PIX_FMT_NONE,
};

સ્થિર પૂર્ણાંક amf_frames_get_constraints(AVHWDeviceContext *ctx,
                                       અચલ શૂન્ય *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    પૂર્ણાંક i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    કદ(*constraints->valid_sw_formats));
    જો (!constraints->valid_sw_formats)
        પાછા AVERROR(ENOMEM);

    માટે (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, કદ(*constraints->valid_hw_formats));
    જો (!constraints->valid_hw_formats)
        પાછા AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_AMF_SURFACE;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    પાછા 0;
}

સ્થિર શૂન્ય amf_dummy_free(શૂન્ય *opaque, uint8_t *data)
{

}

સ્થિર AVBufferRef *amf_pool_alloc(શૂન્ય *opaque, size_t size)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)opaque;
    AVBufferRef *buf;

    buf = av_buffer_create(ખાલી, 0, amf_dummy_free, hwfc, AV_BUFFER_FLAG_READONLY);
    જો (!buf) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create buffer for AMF context.\n");
        પાછા ખાલી;
    }
    પાછા buf;
}

સ્થિર પૂર્ણાંક amf_frames_init(AVHWFramesContext *ctx)
{
    પૂર્ણાંક i;

    માટે (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        જો (ctx->sw_format == supported_formats[i])
            તોડો;
    }
    જો (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        પાછા AVERROR(ENOSYS);
    }

    ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(કદ(AMFSurface), ctx,
                                 &amf_pool_alloc, ખાલી);

    પાછા 0;
}


સ્થિર પૂર્ણાંક amf_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    જો (!frame->buf[0])
        પાછા AVERROR(ENOMEM);

    frame->data[0] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_AMF_SURFACE;
    frame->width   = ctx->width;
    frame->height  = ctx->height;
    પાછા 0;
}

સ્થિર પૂર્ણાંક amf_transfer_get_formats(AVHWFramesContext *ctx,
                                     ગણના AVHWFrameTransferDirection dir,
                                     ગણના AVPixelFormat **formats)
{
    ગણના AVPixelFormat *fmts;
    પૂર્ણાંક i;

    fmts = av_malloc_array(FF_ARRAY_ELEMS(supported_transfer_formats), કદ(*fmts));
    જો (!fmts)
        પાછા AVERROR(ENOMEM);
    માટે (i = 0; i < FF_ARRAY_ELEMS(supported_transfer_formats); i++)
        fmts[i] = supported_transfer_formats[i];

    *formats = fmts;

    પાછા 0;
}

સ્થિર શૂન્ય amf_free_amfsurface(શૂન્ય *opaque, uint8_t *data)
{
    જો(!!data){
        AMFSurface *surface = (AMFSurface*)(data);
        surface->pVtbl->Release(surface);
    }
}

સ્થિર પૂર્ણાંક amf_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                 અચલ AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)dst->data[0];
    AMFPlane *plane;
    uint8_t  *dst_data[4];
    પૂર્ણાંક       dst_linesize[4];
    પૂર્ણાંક       planes;
    પૂર્ણાંક       i;
    પૂર્ણાંક       res;
    પૂર્ણાંક w = FFMIN(dst->width,  src->width);
    પૂર્ણાંક h = FFMIN(dst->height, src->height);

    જો (dst->hw_frames_ctx->data != (uint8_t *)ctx || src->format != ctx->sw_format)
        પાછા AVERROR(EINVAL);

    જો (!surface) {
        AVHWDeviceContext   *hwdev_ctx = ctx->device_ctx;
        AVAMFDeviceContext  *amf_device_ctx = (AVAMFDeviceContext *)hwdev_ctx->hwctx;
        AMF_SURFACE_FORMAT  format = av_av_to_amf_format(ctx->sw_format);
        res = amf_device_ctx->context->pVtbl->AllocSurface(amf_device_ctx->context, AMF_MEMORY_HOST, format, dst->width, dst->height, &surface);
        AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR(ENOMEM), "AllocSurface() failed  with error %d\n", res);
        dst->data[0] = (uint8_t *)surface;
        dst->buf[1] = av_buffer_create((uint8_t *)surface, કદ(surface),
                                            amf_free_amfsurface,
                                            ખાલી,
                                            AV_BUFFER_FLAG_READONLY);
    AMF_RETURN_IF_FALSE(ctx, !!dst->buf[1], AVERROR(ENOMEM), "av_buffer_create for amf surface failed.");
    }

    planes = (પૂર્ણાંક)surface->pVtbl->Get_Planes_ગણતરી(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(dst_data));

    માટે (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        dst_data[i] = plane->pVtbl->GetNative(plane);
        dst_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst_data, dst_linesize,
                   src->data, src->linesize, src->format,
                   w, h);

    પાછા 0;
}

સ્થિર પૂર્ણાંક amf_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    અચલ AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)src->data[0];
    AMFPlane *plane;
    uint8_t  *src_data[4];
    પૂર્ણાંક       src_linesize[4];
    પૂર્ણાંક       planes;
    પૂર્ણાંક       i;
    પૂર્ણાંક w = FFMIN(dst->width,  src->width);
    પૂર્ણાંક h = FFMIN(dst->height, src->height);
    પૂર્ણાંક ret;

    જો (src->hw_frames_ctx->data != (uint8_t *)ctx || dst->format != ctx->sw_format)
        પાછા AVERROR(EINVAL);

    ret = surface->pVtbl->Convert(surface, AMF_MEMORY_HOST);
    AMF_RETURN_IF_FALSE(ctx, ret == AMF_OK, AVERROR_UNKNOWN, "Convert(amf::AMF_MEMORY_HOST) failed with error %d\n", AVERROR_UNKNOWN);

    planes = (પૂર્ણાંક)surface->pVtbl->Get_Planes_ગણતરી(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(src_data));

    માટે (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        src_data[i] = plane->pVtbl->GetNative(plane);
        src_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst->data, dst->linesize,
                   src_data, src_linesize, dst->format,
                   w, h);
    પાછા 0;
}



સ્થિર શૂન્ય amf_device_uninit(AVHWDeviceContext *device_ctx)
{
    AVAMFDeviceContext *amf_ctx = device_ctx->hwctx;
    AMF_RESULT          res = AMF_NOT_INITIALIZED;
    AMFTrace           *trace;

    જો (amf_ctx->context) {
        amf_ctx->context->pVtbl->Terminate(amf_ctx->context);
        amf_ctx->context->pVtbl->Release(amf_ctx->context);
        amf_ctx->context = ખાલી;
    }

    જો (amf_ctx->factory)
        res = amf_ctx->factory->pVtbl->GetTrace(amf_ctx->factory, &trace);

    જો (res == AMF_OK) {
        trace->pVtbl->UnregisterWriter(trace, FFMPEG_AMF_WRITER_ID);
    }

    જો(amf_ctx->library) {
        dlclose(amf_ctx->library);
        amf_ctx->library = ખાલી;
    }
    જો (amf_ctx->trace_writer) {
        amf_writer_free(amf_ctx->trace_writer);
    }

    જો (amf_ctx->lock_ctx == amf_lock_default) {
        ff_mutex_destroy((AVMutex*)amf_ctx->lock_ctx);
        av_freep(&amf_ctx->lock_ctx);
        amf_ctx->lock = ખાલી;
        amf_ctx->unlock = ખાલી;
    }

    amf_ctx->version = 0;
}

ગણના AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx)
{
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = ખાલી;
    AMFGuid guid1 = IID_AMFContext1();
    શૂન્ય * device = ખાલી;

#ifdef _WIN32
    // At the moment used only for DX12.
    AMFContext2 *context2 = ખાલી;

    /*
    Work around the incorrect C Context2 IID in unpatched AMF 1.5.2 headers;
    mostly pedantic fix as it works as it is in practice.
    TODO: replace with AMFGuid guid2 = IID_AMFContext2()
    once AMF 1.5.3 is available to public and marked as required version in ffmpeg.
    */
    સ્થિર અચલ AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#endif

    જો (!amf_ctx)
        પાછા AMF_MEMORY_UNKNOWN;

#ifdef _WIN32
    જો (AMF_IFACE_CALL(context, QueryInterface, &guid2, (શૂન્ય**)&context2) == AMF_OK)
    {
        device = AMF_IFACE_CALL(context2, GetDX12Device, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);

        જો (device)
            પાછા AMF_MEMORY_DX12;
    }

    જો (AMF_IFACE_CALL(context, GetDX11Device, AMF_DX11_1))
        પાછા AMF_MEMORY_DX11;

    જો (AMF_IFACE_CALL(context, GetDX9Device, AMF_DX9))
        પાછા AMF_MEMORY_DX9;
#endif

    જો (AMF_IFACE_CALL(context, QueryInterface, &guid1, (શૂન્ય**)&context1) != AMF_OK)
        પાછા AMF_MEMORY_UNKNOWN;

    device = AMF_IFACE_CALL(context1, GetVulkanDevice);
    AMF_IFACE_CALL(context1, Release);
    જો (device)
        પાછા AMF_MEMORY_VULKAN;

    પાછા AMF_MEMORY_UNKNOWN;
}

સ્થિર પૂર્ણાંક amf_device_init(AVHWDeviceContext *ctx)
{
    AVAMFDeviceContext *amf_ctx = ctx->hwctx;
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = ખાલી;
    AMFGuid guid1 = IID_AMFContext1();
    AMF_RESULT res;

#ifdef _WIN32
    AMFContext2 *context2 = ખાલી;
    સ્થિર અચલ AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#endif

    જો (!amf_ctx->lock) {
        amf_ctx->lock_ctx = av_mallocz(કદ(AVMutex));
        જો (!amf_ctx->lock_ctx) {
            પાછા AVERROR(ENOMEM);
        }
        ff_mutex_init((AVMutex*)amf_ctx->lock_ctx, ખાલી);
        amf_ctx->lock   = amf_lock_default;
        amf_ctx->unlock = amf_unlock_default;
    }

    જો (av_amf_get_memory_type(amf_ctx) != AMF_MEMORY_UNKNOWN) {
        av_log(ctx, AV_LOG_VERBOSE, "AMF is already initialized, skipping init.\n");
        પાછા 0;
    }

#ifdef _WIN32
    res = AMF_IFACE_CALL(context, InitDX11, ખાલી, AMF_DX11_1);
    જો (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D11.\n");
        પાછા 0;
    }

    res = AMF_IFACE_CALL(context, QueryInterface, &guid2, (શૂન્ય**)&context2);
    જો (res == AMF_OK) {
        res = AMF_IFACE_CALL(context2, InitDX12, ખાલી, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);
        જો (res == AMF_OK) {
            av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D12.\n");
            પાછા 0;
        }
    } નહીંતર {
        av_log(ctx, AV_LOG_VERBOSE, "QueryInterface(AMFContext2) failed with error %d, trying older D3D APIs...\n", res);
    }

    res = AMF_IFACE_CALL(context, InitDX9, ખાલી);
    જો (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D9.\n");
        પાછા 0;
    }

    av_log(ctx, AV_LOG_WARNING, "AMF failed to initialize with any of supported versions of DirectX, trying Vulkan instead...\n");
#endif

    res = AMF_IFACE_CALL(context, QueryInterface, &guid1, (શૂન્ય**)&context1);
    જો (res != AMF_OK) {
        av_log(ctx, AV_LOG_ERROR, "QueryInterface(AMFContext1) failed with error %d\n", res);
        પાછા AVERROR_UNKNOWN;
    }

    res = AMF_IFACE_CALL(context1, InitVulkan, ખાલી);
    AMF_IFACE_CALL(context1, Release);

    જો (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via Vulkan.\n");
    } નહીંતર {
        જો (res == AMF_NOT_SUPPORTED)
            av_log(ctx, AV_LOG_ERROR, "AMF via Vulkan is not supported on the given device.\n");
        નહીંતર
            av_log(ctx, AV_LOG_ERROR, "Failed to initialize AMF via Vulkan, error %d\n", res);

        પાછા AVERROR(ENOSYS);
    }

    પાછા 0;
}

સ્થિર પૂર્ણાંક amf_load_library(AVAMFDeviceContext* amf_ctx,  શૂન્ય* avcl)
{
    AMFInit_Fn         init_fun;
    AMFQueryVersion_Fn version_fun;
    AMF_RESULT         res;

    amf_ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(avcl, amf_ctx->library != ખાલી,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(amf_ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, init_fun != ખાલી, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    version_fun = (AMFQueryVersion_Fn)dlsym(amf_ctx->library, AMF_QUERY_VERSION_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, version_fun != ખાલી, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_VERSION_FUNCTION_NAME);

    amf_uint64 version;
    res = version_fun(&version);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_VERSION_FUNCTION_NAME, res);
    amf_ctx->version = version;
    res = init_fun(AMF_FULL_VERSION, &amf_ctx->factory);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_INIT_FUNCTION_NAME, res);
    પાછા 0;
}

સ્થિર પૂર્ણાંક amf_device_create(AVHWDeviceContext *device_ctx,
                              અચલ અક્ષર *device,
                              AVDictionary *opts, પૂર્ણાંક flags)
{
    AVAMFDeviceContext        *ctx = device_ctx->hwctx;
    AMFTrace           *trace;
    પૂર્ણાંક ret;
    જો ((ret = amf_load_library(ctx, device_ctx)) == 0) {
        ret = ctx->factory->pVtbl->GetTrace(ctx->factory, &trace);
        જો (ret == AMF_OK) {
            પૂર્ણાંક level_ff = av_log_get_level();
            પૂર્ણાંક level_amf = AMF_TRACE_TRACE;
            amf_bool enable_log = true;
            પસંદગી(level_ff)
            {
            સ્થિતિ AV_LOG_QUIET:
                level_amf = AMF_TRACE_ERROR;
                enable_log = false;
                તોડો;
            સ્થિતિ AV_LOG_PANIC:
            સ્થિતિ AV_LOG_FATAL:
            સ્થિતિ AV_LOG_ERROR:
                level_amf = AMF_TRACE_ERROR;
                તોડો;
            સ્થિતિ AV_LOG_WARNING:
            સ્થિતિ AV_LOG_INFO:
                level_amf = AMF_TRACE_WARNING;
                તોડો;
            સ્થિતિ AV_LOG_VERBOSE:
                level_amf = AMF_TRACE_INFO;
                તોડો;
            સ્થિતિ AV_LOG_DEBUG:
                level_amf = AMF_TRACE_DEBUG;
                તોડો;
            સ્થિતિ AV_LOG_TRACE:
                level_amf = AMF_TRACE_TRACE;
                તોડો;
            }
            જો(ctx->version == AMF_MAKE_FULL_VERSION(1, 4, 35, 0)){// get around a bug in trace in AMF runtime driver 24.20
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
        જો (ret == AMF_OK) {
            AMF_ASSIGN_PROPERTY_INT64(ret, ctx->context, L"DeviceSurfaceCacheSize", 50 );
            પાછા 0;
        }
        av_log(device_ctx, AV_LOG_ERROR, "CreateContext() failed with error %d.\n", ret);
    }
    amf_device_uninit(device_ctx);
    પાછા ret;
}

#જો CONFIG_DXVA2
સ્થિર પૂર્ણાંક amf_init_from_dxva2_device(AVAMFDeviceContext * amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVDXVA2DeviceContext *hwctx = child_device_ctx->hwctx;
    IDirect3DDevice9    *device;
    HANDLE              device_handle;
    HRESULT             hr;
    AMF_RESULT          res;
    પૂર્ણાંક ret;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &device_handle);
    જો (FAILED(hr)) {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to open device handle for Direct3D9 device: %lx.\n", (unsigned long)hr);
        પાછા AVERROR_EXTERNAL;
    }

    hr = IDirect3DDeviceManager9_LockDevice(hwctx->devmgr, device_handle, &device, FALSE);
    જો (SUCCEEDED(hr)) {
        IDirect3DDeviceManager9_UnlockDevice(hwctx->devmgr, device_handle, FALSE);
        ret = 0;
    } નહીંતર {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to lock device handle for Direct3D9 device: %lx.\n", (unsigned long)hr);
        ret = AVERROR_EXTERNAL;
    }


    IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, device_handle);

    જો (ret < 0)
        પાછા ret;

    res = amf_ctx->context->pVtbl->InitDX9(amf_ctx->context, device);

    IDirect3DDevice9_Release(device);

    જો (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        જો (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D9 is not supported on the given device.\n");
        નહીંતર
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on given D3D9 device: %d.\n", res);
        પાછા AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via DXVA2.\n");
    પાછા 0;
}
#endif

#જો CONFIG_D3D11VA
સ્થિર પૂર્ણાંક amf_init_from_d3d11_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AMF_RESULT res;
    AVD3D11VADeviceContext *hwctx = child_device_ctx->hwctx;
    res = amf_ctx->context->pVtbl->InitDX11(amf_ctx->context, hwctx->device, AMF_DX11_1);
    જો (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        જો (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D11 is not supported on the given device.\n");
        નહીંતર
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D11 device: %d.\n", res);
        પાછા AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D11.\n");
    hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    પાછા 0;
}
#endif

#જો CONFIG_D3D12VA
સ્થિર પૂર્ણાંક amf_init_from_d3d12_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVD3D12VADeviceContext *hwctx = child_device_ctx->hwctx;
    AMF_RESULT res;
    AMFContext2 *context2 = ખાલી;
    AMFGuid guid = IID_AMFContext2();
    res = amf_ctx->context->pVtbl->QueryInterface(amf_ctx->context, &guid, (શૂન્ય**)&context2);
    AMF_RETURN_IF_FALSE(child_device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "CreateContext2() failed with error %d\n", res);
    res = context2->pVtbl->InitDX12(context2, hwctx->device, AMF_DX12);
    context2->pVtbl->Release(context2);
    જો (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        જો (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D12 is not supported on the given device.\n");
        નહીંતર
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D12 device: %d.\n", res);
        પાછા AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D12.\n");
    પાછા 0;
}
#endif


સ્થિર પૂર્ણાંક amf_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *child_device_ctx, AVDictionary *opts,
                              પૂર્ણાંક flags)
{
#જો CONFIG_DXVA2 || CONFIG_D3D11VA || CONFIG_D3D12VA
    AVAMFDeviceContext        *amf_ctx = device_ctx->hwctx;
#endif
    પૂર્ણાંક ret;

    ret = amf_device_create(device_ctx, "", opts, flags);
    જો(ret < 0)
        પાછા ret;

    પસંદગી (child_device_ctx->type) {
#જો CONFIG_DXVA2
    સ્થિતિ AV_HWDEVICE_TYPE_DXVA2:
        પાછા amf_init_from_dxva2_device(amf_ctx, child_device_ctx);
#endif
#જો CONFIG_D3D11VA
    સ્થિતિ AV_HWDEVICE_TYPE_D3D11VA:
        પાછા amf_init_from_d3d11_device(amf_ctx, child_device_ctx);
#endif
#જો CONFIG_D3D12VA
    સ્થિતિ AV_HWDEVICE_TYPE_D3D12VA:
        પાછા amf_init_from_d3d12_device(amf_ctx, child_device_ctx);
#endif
    મૂળભૂત:
        av_log(child_device_ctx, AV_LOG_ERROR, "AMF initialisation from a %s device is not supported.\n",
               av_hwdevice_get_type_name(child_device_ctx->type));
        પાછા AVERROR(ENOSYS);
    }
}

સ્થિર શૂન્ય amf_unmap_frame(av_unused AVHWFramesContext *unused, HWMapDescriptor *hwmap)
{
    AMFSurface1 *surface1 = hwmap->priv;
    AMF_IFACE_CALL(surface1, Unmap);
    AMF_IFACE_CALL(surface1, Release);
}

સ્થિર પૂર્ણાંક amf_map_frame(AVHWFramesContext *device_ctx, AVFrame *dst, અચલ AVFrame *src, પૂર્ણાંક flags)
{
    AMFSurface *surface = (AMFSurface *)src->data[0];
    AMFSurface1 *surface1 = ખાલી;
    size_t *linesizes = ખાલી;
    uint8_t **map = ખાલી;
    પૂર્ણાંક amf_mem_flags = AMF_MEMORY_CPU_NONE;
    અચલ AMFGuid guid = IID_AMFSurface1();
    AMF_RESULT res = AMF_FAIL;
    size_t plane_ગણતરી = 0;
    પૂર્ણાંક ret = -1;

    AMF_RETURN_IF_FALSE(device_ctx, surface != ખાલી, AVERROR(EINVAL) , "Source surface is null");

    res = AMF_IFACE_CALL(surface, QueryInterface, &guid, (શૂન્ય**)&surface1);
    AMF_RETURN_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "QueryInterface(AMFSurface1) failed with error %d\n", res);

    જો (flags & AV_HWFRAME_MAP_READ)
        amf_mem_flags |= AMF_MEMORY_CPU_READ;

    જો (flags & AV_HWFRAME_MAP_WRITE)
        amf_mem_flags |= AMF_MEMORY_CPU_WRITE;

    plane_ગણતરી = AMF_IFACE_CALL(surface, Get_Planes_ગણતરી);
    linesizes = av_malloc_array(કદ(size_t), plane_ગણતરી);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, linesizes, AVERROR(ENOMEM), "Unable to allocate line sizes array\n");

    map = av_malloc_array(કદ(uint8_t *), plane_ગણતરી);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, map, AVERROR(ENOMEM), "Unable to allocate mapping buffer\n");

    dst->format = av_amf_to_av_format(AMF_IFACE_CALL(surface, GetFormat));

    res = AMF_IFACE_CALL(surface1, Map, amf_mem_flags, plane_ગણતરી, linesizes, (શૂન્ય**)map);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "AMFSurface1->Map() failed with error %d\n", res);

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, &amf_unmap_frame, surface1);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, ret >= 0, ret, "ff_hwframe_map_create failed with error %d\n", ret);

    dst->width  = src->width;
    dst->height = src->height;
    av_frame_copy_props(dst, src);

    // The dst frame is no longer a hardware frame, from the perspective of any dst frame consumer.
    av_buffer_unref(&dst->hw_frames_ctx);

    માટે (પૂર્ણાંક plane = 0; plane < plane_ગણતરી; ++plane)
    {
        dst->data[plane] = map[plane];
        dst->linesize[plane] = linesizes[plane];
    }

fail:
    જો (map)
        av_free(map);

    જો (linesizes)
        av_free(linesizes);

    જો (ret < 0 && surface1 != ખાલી)
        AMF_IFACE_CALL(surface1, Release);

    પાછા ret;
}

અચલ HWContextType ff_hwcontext_type_amf = {
    .type                 = AV_HWDEVICE_TYPE_AMF,
    .name                 = "AMF",

    .device_hwctx_size    = કદ(AVAMFDeviceContext),
    .frames_hwctx_size    = કદ(AMFFramesContext),

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

    .pix_fmts             = (અચલ ગણના AVPixelFormat[]){ AV_PIX_FMT_AMF_SURFACE, AV_PIX_FMT_NONE },
};
