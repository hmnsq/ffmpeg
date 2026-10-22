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

#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "buffer.h"
#অন্তর্ভাৱ "pixfmt.h"
#অন্তর্ভাৱ "pixdesc.h"
#অন্তর্ভাৱ "imgutils.h"
#অন্তর্ভাৱ "hwcontext.h"
#অন্তর্ভাৱ "hwcontext_amf.h"
#অন্তর্ভাৱ "hwcontext_internal.h"
#অন্তর্ভাৱ "hwcontext_amf_internal.h"

#অন্তর্ভাৱ "libavutil/thread.h"
#অন্তর্ভাৱ "libavutil/avassert.h"

#অন্তর্ভাৱ <AMF/core/Surface.h>
#অন্তর্ভাৱ <AMF/core/Trace.h>

#যদি CONFIG_VULKAN
#অন্তর্ভাৱ "hwcontext_vulkan.h"
#endif
#যদি CONFIG_D3D11VA
#অন্তর্ভাৱ "libavutil/hwcontext_d3d11va.h"
#endif
#যদি CONFIG_D3D12VA
#অন্তর্ভাৱ "libavutil/hwcontext_d3d12va.h"
#endif
#যদি CONFIG_DXVA2
#define COBJMACROS
#অন্তর্ভাৱ "libavutil/hwcontext_dxva2.h"
#endif
#ifdef _WIN32
#অন্তর্ভাৱ "compat/w32dlfcn.h"
#অন্যথা
#অন্তর্ভাৱ <dlfcn.h>
#endif
#define FFMPEG_AMF_WRITER_ID L"ffmpeg_amf"

স্থির শূন্য amf_lock_default(শূন্য *opaque)
{
    ff_mutex_lock((AVMutex*)opaque);
}

স্থির শূন্য amf_unlock_default(শূন্য *opaque)
{
    ff_mutex_unlock((AVMutex*)opaque);
}

প্রকারনির্দেশ সংরচনা AmfTraceWriter {
    AMFTraceWriterVtbl *vtblp;
    শূন্য               *avctx;
    AMFTraceWriterVtbl  vtbl;
} AmfTraceWriter;

স্থির শূন্য AMF_CDECL_CALL AMFTraceWriter_Write(AMFTraceWriter *pThis,
    ধ্রুৱ wchar_t *scope, ধ্রুৱ wchar_t *message)
{
    AmfTraceWriter *tracer = (AmfTraceWriter*)pThis;
    av_log(tracer->avctx, AV_LOG_DEBUG, "%ls: %ls", scope, message); // \n is provided from AMF
}

স্থির শূন্য AMF_CDECL_CALL AMFTraceWriter_Flush(AMFTraceWriter *pThis)
{
}

স্থির AmfTraceWriter * amf_writer_alloc(শূন্য  *avctx)
{
    AmfTraceWriter * writer = av_mallocz(পরিমাণ(AmfTraceWriter));
    যদি (!writer)
        ঘূৰাই রিক্ত;

    writer->vtblp = &writer->vtbl;
    writer->vtblp->Write = AMFTraceWriter_Write;
    writer->vtblp->Flush = AMFTraceWriter_Flush;
    writer->avctx = avctx;

    ঘূৰাই writer;
}

স্থির শূন্য amf_writer_free(শূন্য  *opaque)
{
    AmfTraceWriter *writer = (AmfTraceWriter *)opaque;
    av_freep(&writer);
}

/**
 * We still need AVHWFramesContext to utilize our hardware memory
 * otherwise, we will receive the error "HW format requires hw_frames_ctx to be non-NULL".
 * (libavfilter\buffersrc.c function query_formats)
*/
প্রকারনির্দেশ সংরচনা {
    শূন্য *dummy;
} AMFFramesContext;

প্রকারনির্দেশ সংরচনা AVAMFFormatMap {
    গণনা AVPixelFormat       av_format;
    গণনা AMF_SURFACE_FORMAT  amf_format;
} FormatMap;

ধ্রুৱ FormatMap format_map[] =
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

গণনা AMF_SURFACE_FORMAT av_av_to_amf_format(গণনা AVPixelFormat fmt)
{
    পূর্ণাঙ্ক i;
    বাবে (i = 0; i < amf_countof(format_map); i++) {
        যদি (format_map[i].av_format == fmt) {
            ঘূৰাই format_map[i].amf_format;
        }
    }
    ঘূৰাই AMF_SURFACE_UNKNOWN;
}

গণনা AVPixelFormat av_amf_to_av_format(গণনা AMF_SURFACE_FORMAT fmt)
{
    পূর্ণাঙ্ক i;
    বাবে (i = 0; i < amf_countof(format_map); i++) {
        যদি (format_map[i].amf_format == fmt) {
            ঘূৰাই format_map[i].av_format;
        }
    }
    ঘূৰাই AV_PIX_FMT_NONE;
}

গণনা AMF_VIDEO_CONVERTER_COLOR_PROFILE_ENUM av_amf_get_color_profile(গণনা AVColorRange color_range, গণনা AVColorSpace color_space)
{
    ৱিকল্প (color_space) {
    পক্ষ AVCOL_SPC_SMPTE170M:
        যদি (color_range == AVCOL_RANGE_JPEG) {
            ঘূৰাই AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_601;
        } অন্যথা {
            ঘূৰাই AMF_VIDEO_CONVERTER_COLOR_PROFILE_601;
        }
        ভঙ্গ;
    পক্ষ AVCOL_SPC_BT709:
        যদি (color_range == AVCOL_RANGE_JPEG) {
            ঘূৰাই AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_709;
        } অন্যথা {
            ঘূৰাই AMF_VIDEO_CONVERTER_COLOR_PROFILE_709;
        }
        ভঙ্গ;
    পক্ষ AVCOL_SPC_BT2020_NCL:
    পক্ষ AVCOL_SPC_BT2020_CL:
        যদি (color_range == AVCOL_RANGE_JPEG) {
            ঘূৰাই AMF_VIDEO_CONVERTER_COLOR_PROFILE_FULL_2020;
        } অন্যথা {
            ঘূৰাই AMF_VIDEO_CONVERTER_COLOR_PROFILE_2020;
        }
        ভঙ্গ;

    স্ৱভাৱ:
        ঘূৰাই AMF_VIDEO_CONVERTER_COLOR_PROFILE_UNKNOWN;
    }
}

পূর্ণাঙ্ক av_amf_display_mastering_meta_to_hdrmeta(ধ্রুৱ AVMasteringDisplayMetadata *display_meta, AMFHDRMetadata *hdrmeta)
{
    যদি (!display_meta || !hdrmeta)
        ঘূৰাই AVERROR(EINVAL);

    যদি (display_meta->has_luminance) {
        ধ্রুৱ unsigned পূর্ণাঙ্ক luma_den = 10000;
        hdrmeta->maxMasteringLuminance =
            (amf_uint32)(luma_den * av_q2d(display_meta->max_luminance));
        hdrmeta->minMasteringLuminance =
            FFMIN((amf_uint32)(luma_den * av_q2d(display_meta->min_luminance)), hdrmeta->maxMasteringLuminance);
    }

    যদি (display_meta->has_primaries) {
        ধ্রুৱ unsigned পূর্ণাঙ্ক chroma_den = 50000;
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

    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_amf_light_metadata_to_hdrmeta(ধ্রুৱ AVContentLightMetadata *light_meta, AMFHDRMetadata *hdrmeta)
{
    যদি (!light_meta || !hdrmeta)
        ঘূৰাই AVERROR(EINVAL);

    hdrmeta->maxContentLightLevel = (amf_uint16)light_meta->MaxCLL;
    hdrmeta->maxFrameAverageLightLevel = (amf_uint16)light_meta->MaxFALL;

    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_amf_extract_hdr_metadata(ধ্রুৱ AVFrame *frame, AMFHDRMetadata *hdrmeta)
{
    AVFrameSideData *sidedata;
    AVContentLightMetadata *content_light = রিক্ত;
    AVMasteringDisplayMetadata *mastering_display = রিক্ত;

    যদি (!frame || !hdrmeta)
        ঘূৰাই AVERROR(EINVAL);

    sidedata = av_frame_get_side_data(frame, AV_FRAME_DATA_MASTERING_DISPLAY_METADATA);
    যদি (sidedata) {
        mastering_display = (AVMasteringDisplayMetadata *)sidedata->data;
        যদি (av_amf_display_mastering_meta_to_hdrmeta(mastering_display, hdrmeta) != 0)
            mastering_display = রিক্ত;
    }

    sidedata = av_frame_get_side_data(frame, AV_FRAME_DATA_CONTENT_LIGHT_LEVEL);
    যদি (sidedata) {
        content_light = (AVContentLightMetadata *)sidedata->data;
        যদি (av_amf_light_metadata_to_hdrmeta(content_light, hdrmeta) != 0)
            content_light = রিক্ত;
    }

    যদি (!mastering_display && !content_light)
        ঘূৰাই AVERROR(ENODATA);

    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_amf_attach_hdr_metadata(AVFrame *frame, ধ্রুৱ AMFHDRMetadata *hdrmeta) {
    যদি (!hdrmeta || !frame)
        ঘূৰাই AVERROR(EINVAL);

    AVMasteringDisplayMetadata *mastering =
        av_mastering_display_metadata_create_side_data(frame);
    ধ্রুৱ পূর্ণাঙ্ক chroma_den = 50000;
    ধ্রুৱ পূর্ণাঙ্ক luma_den = 10000;

    যদি (!mastering)
      ঘূৰাই AVERROR(ENOMEM);

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
    যদি (hdrmeta->maxContentLightLevel) {
      AVContentLightMetadata *light =
          av_content_light_metadata_create_side_data(frame);

      যদি (!light)
        ঘূৰাই AVERROR(ENOMEM);

      light->MaxCLL = hdrmeta->maxContentLightLevel;
      light->MaxFALL = hdrmeta->maxFrameAverageLightLevel;
    }

    ঘূৰাই 0;
}

স্থির ধ্রুৱ গণনা AVPixelFormat supported_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_BGR0,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
#যদি CONFIG_D3D11VA
    AV_PIX_FMT_D3D11,
#endif
#যদি CONFIG_D3D12VA
    AV_PIX_FMT_D3D12,
#endif
#যদি CONFIG_DXVA2
    AV_PIX_FMT_DXVA2_VLD,
#endif
};

স্থির ধ্রুৱ গণনা AVPixelFormat supported_transfer_formats[] = {
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_RGBA,
    AV_PIX_FMT_P010,
    AV_PIX_FMT_X2BGR10,
    AV_PIX_FMT_RGBAF16,
    AV_PIX_FMT_NONE,
};

স্থির পূর্ণাঙ্ক amf_frames_get_constraints(AVHWDeviceContext *ctx,
                                       ধ্রুৱ শূন্য *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    পূর্ণাঙ্ক i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    পরিমাণ(*constraints->valid_sw_formats));
    যদি (!constraints->valid_sw_formats)
        ঘূৰাই AVERROR(ENOMEM);

    বাবে (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, পরিমাণ(*constraints->valid_hw_formats));
    যদি (!constraints->valid_hw_formats)
        ঘূৰাই AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_AMF_SURFACE;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ঘূৰাই 0;
}

স্থির শূন্য amf_dummy_free(শূন্য *opaque, uint8_t *data)
{

}

স্থির AVBufferRef *amf_pool_alloc(শূন্য *opaque, size_t size)
{
    AVHWFramesContext *hwfc = (AVHWFramesContext *)opaque;
    AVBufferRef *buf;

    buf = av_buffer_create(রিক্ত, 0, amf_dummy_free, hwfc, AV_BUFFER_FLAG_READONLY);
    যদি (!buf) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create buffer for AMF context.\n");
        ঘূৰাই রিক্ত;
    }
    ঘূৰাই buf;
}

স্থির পূর্ণাঙ্ক amf_frames_init(AVHWFramesContext *ctx)
{
    পূর্ণাঙ্ক i;

    বাবে (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        যদি (ctx->sw_format == supported_formats[i])
            ভঙ্গ;
    }
    যদি (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ঘূৰাই AVERROR(ENOSYS);
    }

    ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(পরিমাণ(AMFSurface), ctx,
                                 &amf_pool_alloc, রিক্ত);

    ঘূৰাই 0;
}


স্থির পূর্ণাঙ্ক amf_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    যদি (!frame->buf[0])
        ঘূৰাই AVERROR(ENOMEM);

    frame->data[0] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_AMF_SURFACE;
    frame->width   = ctx->width;
    frame->height  = ctx->height;
    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক amf_transfer_get_formats(AVHWFramesContext *ctx,
                                     গণনা AVHWFrameTransferDirection dir,
                                     গণনা AVPixelFormat **formats)
{
    গণনা AVPixelFormat *fmts;
    পূর্ণাঙ্ক i;

    fmts = av_malloc_array(FF_ARRAY_ELEMS(supported_transfer_formats), পরিমাণ(*fmts));
    যদি (!fmts)
        ঘূৰাই AVERROR(ENOMEM);
    বাবে (i = 0; i < FF_ARRAY_ELEMS(supported_transfer_formats); i++)
        fmts[i] = supported_transfer_formats[i];

    *formats = fmts;

    ঘূৰাই 0;
}

স্থির শূন্য amf_free_amfsurface(শূন্য *opaque, uint8_t *data)
{
    যদি(!!data){
        AMFSurface *surface = (AMFSurface*)(data);
        surface->pVtbl->Release(surface);
    }
}

স্থির পূর্ণাঙ্ক amf_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                 ধ্রুৱ AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)dst->data[0];
    AMFPlane *plane;
    uint8_t  *dst_data[4];
    পূর্ণাঙ্ক       dst_linesize[4];
    পূর্ণাঙ্ক       planes;
    পূর্ণাঙ্ক       i;
    পূর্ণাঙ্ক       res;
    পূর্ণাঙ্ক w = FFMIN(dst->width,  src->width);
    পূর্ণাঙ্ক h = FFMIN(dst->height, src->height);

    যদি (dst->hw_frames_ctx->data != (uint8_t *)ctx || src->format != ctx->sw_format)
        ঘূৰাই AVERROR(EINVAL);

    যদি (!surface) {
        AVHWDeviceContext   *hwdev_ctx = ctx->device_ctx;
        AVAMFDeviceContext  *amf_device_ctx = (AVAMFDeviceContext *)hwdev_ctx->hwctx;
        AMF_SURFACE_FORMAT  format = av_av_to_amf_format(ctx->sw_format);
        res = amf_device_ctx->context->pVtbl->AllocSurface(amf_device_ctx->context, AMF_MEMORY_HOST, format, dst->width, dst->height, &surface);
        AMF_RETURN_IF_FALSE(ctx, res == AMF_OK, AVERROR(ENOMEM), "AllocSurface() failed  with error %d\n", res);
        dst->data[0] = (uint8_t *)surface;
        dst->buf[1] = av_buffer_create((uint8_t *)surface, পরিমাণ(surface),
                                            amf_free_amfsurface,
                                            রিক্ত,
                                            AV_BUFFER_FLAG_READONLY);
    AMF_RETURN_IF_FALSE(ctx, !!dst->buf[1], AVERROR(ENOMEM), "av_buffer_create for amf surface failed.");
    }

    planes = (পূর্ণাঙ্ক)surface->pVtbl->Get_Planes_গুনতি(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(dst_data));

    বাবে (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        dst_data[i] = plane->pVtbl->GetNative(plane);
        dst_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst_data, dst_linesize,
                   src->data, src->linesize, src->format,
                   w, h);

    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক amf_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ধ্রুৱ AVFrame *src)
{
    AMFSurface* surface = (AMFSurface*)src->data[0];
    AMFPlane *plane;
    uint8_t  *src_data[4];
    পূর্ণাঙ্ক       src_linesize[4];
    পূর্ণাঙ্ক       planes;
    পূর্ণাঙ্ক       i;
    পূর্ণাঙ্ক w = FFMIN(dst->width,  src->width);
    পূর্ণাঙ্ক h = FFMIN(dst->height, src->height);
    পূর্ণাঙ্ক ret;

    যদি (src->hw_frames_ctx->data != (uint8_t *)ctx || dst->format != ctx->sw_format)
        ঘূৰাই AVERROR(EINVAL);

    ret = surface->pVtbl->Convert(surface, AMF_MEMORY_HOST);
    AMF_RETURN_IF_FALSE(ctx, ret == AMF_OK, AVERROR_UNKNOWN, "Convert(amf::AMF_MEMORY_HOST) failed with error %d\n", AVERROR_UNKNOWN);

    planes = (পূর্ণাঙ্ক)surface->pVtbl->Get_Planes_গুনতি(surface);
    av_assert0(planes < FF_ARRAY_ELEMS(src_data));

    বাবে (i = 0; i < planes; i++) {
        plane = surface->pVtbl->GetPlaneAt(surface, i);
        src_data[i] = plane->pVtbl->GetNative(plane);
        src_linesize[i] = plane->pVtbl->GetHPitch(plane);
    }
    av_image_copy2(dst->data, dst->linesize,
                   src_data, src_linesize, dst->format,
                   w, h);
    ঘূৰাই 0;
}



স্থির শূন্য amf_device_uninit(AVHWDeviceContext *device_ctx)
{
    AVAMFDeviceContext *amf_ctx = device_ctx->hwctx;
    AMF_RESULT          res = AMF_NOT_INITIALIZED;
    AMFTrace           *trace;

    যদি (amf_ctx->context) {
        amf_ctx->context->pVtbl->Terminate(amf_ctx->context);
        amf_ctx->context->pVtbl->Release(amf_ctx->context);
        amf_ctx->context = রিক্ত;
    }

    যদি (amf_ctx->factory)
        res = amf_ctx->factory->pVtbl->GetTrace(amf_ctx->factory, &trace);

    যদি (res == AMF_OK) {
        trace->pVtbl->UnregisterWriter(trace, FFMPEG_AMF_WRITER_ID);
    }

    যদি(amf_ctx->library) {
        dlclose(amf_ctx->library);
        amf_ctx->library = রিক্ত;
    }
    যদি (amf_ctx->trace_writer) {
        amf_writer_free(amf_ctx->trace_writer);
    }

    যদি (amf_ctx->lock_ctx == amf_lock_default) {
        ff_mutex_destroy((AVMutex*)amf_ctx->lock_ctx);
        av_freep(&amf_ctx->lock_ctx);
        amf_ctx->lock = রিক্ত;
        amf_ctx->unlock = রিক্ত;
    }

    amf_ctx->version = 0;
}

গণনা AMF_MEMORY_TYPE av_amf_get_memory_type(AVAMFDeviceContext *amf_ctx)
{
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = রিক্ত;
    AMFGuid guid1 = IID_AMFContext1();
    শূন্য * device = রিক্ত;

#ifdef _WIN32
    // At the moment used only for DX12.
    AMFContext2 *context2 = রিক্ত;

    /*
    Work around the incorrect C Context2 IID in unpatched AMF 1.5.2 headers;
    mostly pedantic fix as it works as it is in practice.
    TODO: replace with AMFGuid guid2 = IID_AMFContext2()
    once AMF 1.5.3 is available to public and marked as required version in ffmpeg.
    */
    স্থির ধ্রুৱ AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#endif

    যদি (!amf_ctx)
        ঘূৰাই AMF_MEMORY_UNKNOWN;

#ifdef _WIN32
    যদি (AMF_IFACE_CALL(context, QueryInterface, &guid2, (শূন্য**)&context2) == AMF_OK)
    {
        device = AMF_IFACE_CALL(context2, GetDX12Device, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);

        যদি (device)
            ঘূৰাই AMF_MEMORY_DX12;
    }

    যদি (AMF_IFACE_CALL(context, GetDX11Device, AMF_DX11_1))
        ঘূৰাই AMF_MEMORY_DX11;

    যদি (AMF_IFACE_CALL(context, GetDX9Device, AMF_DX9))
        ঘূৰাই AMF_MEMORY_DX9;
#endif

    যদি (AMF_IFACE_CALL(context, QueryInterface, &guid1, (শূন্য**)&context1) != AMF_OK)
        ঘূৰাই AMF_MEMORY_UNKNOWN;

    device = AMF_IFACE_CALL(context1, GetVulkanDevice);
    AMF_IFACE_CALL(context1, Release);
    যদি (device)
        ঘূৰাই AMF_MEMORY_VULKAN;

    ঘূৰাই AMF_MEMORY_UNKNOWN;
}

স্থির পূর্ণাঙ্ক amf_device_init(AVHWDeviceContext *ctx)
{
    AVAMFDeviceContext *amf_ctx = ctx->hwctx;
    AMFContext  *context = amf_ctx->context;
    AMFContext1 *context1 = রিক্ত;
    AMFGuid guid1 = IID_AMFContext1();
    AMF_RESULT res;

#ifdef _WIN32
    AMFContext2 *context2 = রিক্ত;
    স্থির ধ্রুৱ AMFGuid guid2 = {
        0x726241d3, 0xbd46, 0x4e90,
        0x99, 0x68, 0x93, 0xe0, 0x7e, 0xa2, 0x98, 0x4d
    };
#endif

    যদি (!amf_ctx->lock) {
        amf_ctx->lock_ctx = av_mallocz(পরিমাণ(AVMutex));
        যদি (!amf_ctx->lock_ctx) {
            ঘূৰাই AVERROR(ENOMEM);
        }
        ff_mutex_init((AVMutex*)amf_ctx->lock_ctx, রিক্ত);
        amf_ctx->lock   = amf_lock_default;
        amf_ctx->unlock = amf_unlock_default;
    }

    যদি (av_amf_get_memory_type(amf_ctx) != AMF_MEMORY_UNKNOWN) {
        av_log(ctx, AV_LOG_VERBOSE, "AMF is already initialized, skipping init.\n");
        ঘূৰাই 0;
    }

#ifdef _WIN32
    res = AMF_IFACE_CALL(context, InitDX11, রিক্ত, AMF_DX11_1);
    যদি (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D11.\n");
        ঘূৰাই 0;
    }

    res = AMF_IFACE_CALL(context, QueryInterface, &guid2, (শূন্য**)&context2);
    যদি (res == AMF_OK) {
        res = AMF_IFACE_CALL(context2, InitDX12, রিক্ত, AMF_DX12);
        AMF_IFACE_CALL(context2, Release);
        যদি (res == AMF_OK) {
            av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D12.\n");
            ঘূৰাই 0;
        }
    } অন্যথা {
        av_log(ctx, AV_LOG_VERBOSE, "QueryInterface(AMFContext2) failed with error %d, trying older D3D APIs...\n", res);
    }

    res = AMF_IFACE_CALL(context, InitDX9, রিক্ত);
    যদি (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via D3D9.\n");
        ঘূৰাই 0;
    }

    av_log(ctx, AV_LOG_WARNING, "AMF failed to initialize with any of supported versions of DirectX, trying Vulkan instead...\n");
#endif

    res = AMF_IFACE_CALL(context, QueryInterface, &guid1, (শূন্য**)&context1);
    যদি (res != AMF_OK) {
        av_log(ctx, AV_LOG_ERROR, "QueryInterface(AMFContext1) failed with error %d\n", res);
        ঘূৰাই AVERROR_UNKNOWN;
    }

    res = AMF_IFACE_CALL(context1, InitVulkan, রিক্ত);
    AMF_IFACE_CALL(context1, Release);

    যদি (res == AMF_OK) {
        av_log(ctx, AV_LOG_VERBOSE, "Successfully initialized AMF via Vulkan.\n");
    } অন্যথা {
        যদি (res == AMF_NOT_SUPPORTED)
            av_log(ctx, AV_LOG_ERROR, "AMF via Vulkan is not supported on the given device.\n");
        অন্যথা
            av_log(ctx, AV_LOG_ERROR, "Failed to initialize AMF via Vulkan, error %d\n", res);

        ঘূৰাই AVERROR(ENOSYS);
    }

    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক amf_load_library(AVAMFDeviceContext* amf_ctx,  শূন্য* avcl)
{
    AMFInit_Fn         init_fun;
    AMFQueryVersion_Fn version_fun;
    AMF_RESULT         res;

    amf_ctx->library = dlopen(AMF_DLL_NAMEA, RTLD_NOW | RTLD_LOCAL);
    AMF_RETURN_IF_FALSE(avcl, amf_ctx->library != রিক্ত,
        AVERROR_UNKNOWN, "DLL %s failed to open\n", AMF_DLL_NAMEA);

    init_fun = (AMFInit_Fn)dlsym(amf_ctx->library, AMF_INIT_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, init_fun != রিক্ত, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_INIT_FUNCTION_NAME);

    version_fun = (AMFQueryVersion_Fn)dlsym(amf_ctx->library, AMF_QUERY_VERSION_FUNCTION_NAME);
    AMF_RETURN_IF_FALSE(avcl, version_fun != রিক্ত, AVERROR_UNKNOWN, "DLL %s failed to find function %s\n", AMF_DLL_NAMEA, AMF_QUERY_VERSION_FUNCTION_NAME);

    amf_uint64 version;
    res = version_fun(&version);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_QUERY_VERSION_FUNCTION_NAME, res);
    amf_ctx->version = version;
    res = init_fun(AMF_FULL_VERSION, &amf_ctx->factory);
    AMF_RETURN_IF_FALSE(avcl, res == AMF_OK, AVERROR_UNKNOWN, "%s failed with error %d\n", AMF_INIT_FUNCTION_NAME, res);
    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক amf_device_create(AVHWDeviceContext *device_ctx,
                              ধ্রুৱ ৱর্ণ *device,
                              AVDictionary *opts, পূর্ণাঙ্ক flags)
{
    AVAMFDeviceContext        *ctx = device_ctx->hwctx;
    AMFTrace           *trace;
    পূর্ণাঙ্ক ret;
    যদি ((ret = amf_load_library(ctx, device_ctx)) == 0) {
        ret = ctx->factory->pVtbl->GetTrace(ctx->factory, &trace);
        যদি (ret == AMF_OK) {
            পূর্ণাঙ্ক level_ff = av_log_get_level();
            পূর্ণাঙ্ক level_amf = AMF_TRACE_TRACE;
            amf_bool enable_log = true;
            ৱিকল্প(level_ff)
            {
            পক্ষ AV_LOG_QUIET:
                level_amf = AMF_TRACE_ERROR;
                enable_log = false;
                ভঙ্গ;
            পক্ষ AV_LOG_PANIC:
            পক্ষ AV_LOG_FATAL:
            পক্ষ AV_LOG_ERROR:
                level_amf = AMF_TRACE_ERROR;
                ভঙ্গ;
            পক্ষ AV_LOG_WARNING:
            পক্ষ AV_LOG_INFO:
                level_amf = AMF_TRACE_WARNING;
                ভঙ্গ;
            পক্ষ AV_LOG_VERBOSE:
                level_amf = AMF_TRACE_INFO;
                ভঙ্গ;
            পক্ষ AV_LOG_DEBUG:
                level_amf = AMF_TRACE_DEBUG;
                ভঙ্গ;
            পক্ষ AV_LOG_TRACE:
                level_amf = AMF_TRACE_TRACE;
                ভঙ্গ;
            }
            যদি(ctx->version == AMF_MAKE_FULL_VERSION(1, 4, 35, 0)){// get around a bug in trace in AMF runtime driver 24.20
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
        যদি (ret == AMF_OK) {
            AMF_ASSIGN_PROPERTY_INT64(ret, ctx->context, L"DeviceSurfaceCacheSize", 50 );
            ঘূৰাই 0;
        }
        av_log(device_ctx, AV_LOG_ERROR, "CreateContext() failed with error %d.\n", ret);
    }
    amf_device_uninit(device_ctx);
    ঘূৰাই ret;
}

#যদি CONFIG_DXVA2
স্থির পূর্ণাঙ্ক amf_init_from_dxva2_device(AVAMFDeviceContext * amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVDXVA2DeviceContext *hwctx = child_device_ctx->hwctx;
    IDirect3DDevice9    *device;
    HANDLE              device_handle;
    HRESULT             hr;
    AMF_RESULT          res;
    পূর্ণাঙ্ক ret;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &device_handle);
    যদি (FAILED(hr)) {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to open device handle for Direct3D9 device: %lx.\n", (unsigned long)hr);
        ঘূৰাই AVERROR_EXTERNAL;
    }

    hr = IDirect3DDeviceManager9_LockDevice(hwctx->devmgr, device_handle, &device, FALSE);
    যদি (SUCCEEDED(hr)) {
        IDirect3DDeviceManager9_UnlockDevice(hwctx->devmgr, device_handle, FALSE);
        ret = 0;
    } অন্যথা {
        av_log(child_device_ctx, AV_LOG_ERROR, "Failed to lock device handle for Direct3D9 device: %lx.\n", (unsigned long)hr);
        ret = AVERROR_EXTERNAL;
    }


    IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, device_handle);

    যদি (ret < 0)
        ঘূৰাই ret;

    res = amf_ctx->context->pVtbl->InitDX9(amf_ctx->context, device);

    IDirect3DDevice9_Release(device);

    যদি (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        যদি (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D9 is not supported on the given device.\n");
        অন্যথা
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on given D3D9 device: %d.\n", res);
        ঘূৰাই AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via DXVA2.\n");
    ঘূৰাই 0;
}
#endif

#যদি CONFIG_D3D11VA
স্থির পূর্ণাঙ্ক amf_init_from_d3d11_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AMF_RESULT res;
    AVD3D11VADeviceContext *hwctx = child_device_ctx->hwctx;
    res = amf_ctx->context->pVtbl->InitDX11(amf_ctx->context, hwctx->device, AMF_DX11_1);
    যদি (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        যদি (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D11 is not supported on the given device.\n");
        অন্যথা
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D11 device: %d.\n", res);
        ঘূৰাই AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D11.\n");
    hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;
    ঘূৰাই 0;
}
#endif

#যদি CONFIG_D3D12VA
স্থির পূর্ণাঙ্ক amf_init_from_d3d12_device(AVAMFDeviceContext* amf_ctx, AVHWDeviceContext *child_device_ctx)
{
    AVD3D12VADeviceContext *hwctx = child_device_ctx->hwctx;
    AMF_RESULT res;
    AMFContext2 *context2 = রিক্ত;
    AMFGuid guid = IID_AMFContext2();
    res = amf_ctx->context->pVtbl->QueryInterface(amf_ctx->context, &guid, (শূন্য**)&context2);
    AMF_RETURN_IF_FALSE(child_device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "CreateContext2() failed with error %d\n", res);
    res = context2->pVtbl->InitDX12(context2, hwctx->device, AMF_DX12);
    context2->pVtbl->Release(context2);
    যদি (res != AMF_OK && res != AMF_ALREADY_INITIALIZED) {
        যদি (res == AMF_NOT_SUPPORTED)
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF via D3D12 is not supported on the given device.\n");
        অন্যথা
            av_log(child_device_ctx, AV_LOG_ERROR, "AMF failed to initialise on the given D3D12 device: %d.\n", res);
        ঘূৰাই AVERROR(ENODEV);
    }
    av_log(child_device_ctx, AV_LOG_INFO, "AMF via D3D12.\n");
    ঘূৰাই 0;
}
#endif


স্থির পূর্ণাঙ্ক amf_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *child_device_ctx, AVDictionary *opts,
                              পূর্ণাঙ্ক flags)
{
#যদি CONFIG_DXVA2 || CONFIG_D3D11VA || CONFIG_D3D12VA
    AVAMFDeviceContext        *amf_ctx = device_ctx->hwctx;
#endif
    পূর্ণাঙ্ক ret;

    ret = amf_device_create(device_ctx, "", opts, flags);
    যদি(ret < 0)
        ঘূৰাই ret;

    ৱিকল্প (child_device_ctx->type) {
#যদি CONFIG_DXVA2
    পক্ষ AV_HWDEVICE_TYPE_DXVA2:
        ঘূৰাই amf_init_from_dxva2_device(amf_ctx, child_device_ctx);
#endif
#যদি CONFIG_D3D11VA
    পক্ষ AV_HWDEVICE_TYPE_D3D11VA:
        ঘূৰাই amf_init_from_d3d11_device(amf_ctx, child_device_ctx);
#endif
#যদি CONFIG_D3D12VA
    পক্ষ AV_HWDEVICE_TYPE_D3D12VA:
        ঘূৰাই amf_init_from_d3d12_device(amf_ctx, child_device_ctx);
#endif
    স্ৱভাৱ:
        av_log(child_device_ctx, AV_LOG_ERROR, "AMF initialisation from a %s device is not supported.\n",
               av_hwdevice_get_type_name(child_device_ctx->type));
        ঘূৰাই AVERROR(ENOSYS);
    }
}

স্থির শূন্য amf_unmap_frame(av_unused AVHWFramesContext *unused, HWMapDescriptor *hwmap)
{
    AMFSurface1 *surface1 = hwmap->priv;
    AMF_IFACE_CALL(surface1, Unmap);
    AMF_IFACE_CALL(surface1, Release);
}

স্থির পূর্ণাঙ্ক amf_map_frame(AVHWFramesContext *device_ctx, AVFrame *dst, ধ্রুৱ AVFrame *src, পূর্ণাঙ্ক flags)
{
    AMFSurface *surface = (AMFSurface *)src->data[0];
    AMFSurface1 *surface1 = রিক্ত;
    size_t *linesizes = রিক্ত;
    uint8_t **map = রিক্ত;
    পূর্ণাঙ্ক amf_mem_flags = AMF_MEMORY_CPU_NONE;
    ধ্রুৱ AMFGuid guid = IID_AMFSurface1();
    AMF_RESULT res = AMF_FAIL;
    size_t plane_গুনতি = 0;
    পূর্ণাঙ্ক ret = -1;

    AMF_RETURN_IF_FALSE(device_ctx, surface != রিক্ত, AVERROR(EINVAL) , "Source surface is null");

    res = AMF_IFACE_CALL(surface, QueryInterface, &guid, (শূন্য**)&surface1);
    AMF_RETURN_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "QueryInterface(AMFSurface1) failed with error %d\n", res);

    যদি (flags & AV_HWFRAME_MAP_READ)
        amf_mem_flags |= AMF_MEMORY_CPU_READ;

    যদি (flags & AV_HWFRAME_MAP_WRITE)
        amf_mem_flags |= AMF_MEMORY_CPU_WRITE;

    plane_গুনতি = AMF_IFACE_CALL(surface, Get_Planes_গুনতি);
    linesizes = av_malloc_array(পরিমাণ(size_t), plane_গুনতি);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, linesizes, AVERROR(ENOMEM), "Unable to allocate line sizes array\n");

    map = av_malloc_array(পরিমাণ(uint8_t *), plane_গুনতি);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, map, AVERROR(ENOMEM), "Unable to allocate mapping buffer\n");

    dst->format = av_amf_to_av_format(AMF_IFACE_CALL(surface, GetFormat));

    res = AMF_IFACE_CALL(surface1, Map, amf_mem_flags, plane_গুনতি, linesizes, (শূন্য**)map);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, res == AMF_OK, AVERROR_UNKNOWN, "AMFSurface1->Map() failed with error %d\n", res);

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, &amf_unmap_frame, surface1);
    AMF_GOTO_FAIL_IF_FALSE(device_ctx, ret >= 0, ret, "ff_hwframe_map_create failed with error %d\n", ret);

    dst->width  = src->width;
    dst->height = src->height;
    av_frame_copy_props(dst, src);

    // The dst frame is no longer a hardware frame, from the perspective of any dst frame consumer.
    av_buffer_unref(&dst->hw_frames_ctx);

    বাবে (পূর্ণাঙ্ক plane = 0; plane < plane_গুনতি; ++plane)
    {
        dst->data[plane] = map[plane];
        dst->linesize[plane] = linesizes[plane];
    }

fail:
    যদি (map)
        av_free(map);

    যদি (linesizes)
        av_free(linesizes);

    যদি (ret < 0 && surface1 != রিক্ত)
        AMF_IFACE_CALL(surface1, Release);

    ঘূৰাই ret;
}

ধ্রুৱ HWContextType ff_hwcontext_type_amf = {
    .type                 = AV_HWDEVICE_TYPE_AMF,
    .name                 = "AMF",

    .device_hwctx_size    = পরিমাণ(AVAMFDeviceContext),
    .frames_hwctx_size    = পরিমাণ(AMFFramesContext),

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

    .pix_fmts             = (ধ্রুৱ গণনা AVPixelFormat[]){ AV_PIX_FMT_AMF_SURFACE, AV_PIX_FMT_NONE },
};
