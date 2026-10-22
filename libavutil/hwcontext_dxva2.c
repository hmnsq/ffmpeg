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

#ಅನ್ತರ್ಭಾವ <windows.h>

#define DXVA2API_USE_BITFIELDS
#define COBJMACROS

#ಅನ್ತರ್ಭಾವ <d3d9.h>
#ಅನ್ತರ್ಭಾವ <dxva2api.h>
#ಅನ್ತರ್ಭಾವ <initguid.h>

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_dxva2.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "imgutils.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"
#ಅನ್ತರ್ಭಾವ "compat/w32dlfcn.h"

ಪ್ರಕಾರನಿರ್ದೇಶ IDirect3D9* WINAPI pDirect3DCreate9(UINT);
ಪ್ರಕಾರನಿರ್ದೇಶ HRESULT WINAPI pDirect3DCreate9Ex(UINT, IDirect3D9Ex **);
ಪ್ರಕಾರನಿರ್ದೇಶ HRESULT WINAPI pCreateDeviceManager9(UINT *, IDirect3DDeviceManager9 **);

#define FF_D3DCREATE_FLAGS (D3DCREATE_SOFTWARE_VERTEXPROCESSING | \
                            D3DCREATE_MULTITHREADED | \
                            D3DCREATE_FPU_PRESERVE)

ಸ್ಥಿರ ಧ್ರುವ D3DPRESENT_PARAMETERS dxva2_present_params = {
    .Windowed         = TRUE,
    .BackBufferWidth  = 640,
    .BackBufferHeight = 480,
    .Back_Buffer_ಎಣಿಕೆ  = 0,
    .SwapEffect       = D3DSWAPEFFECT_DISCARD,
    .Flags            = D3DPRESENTFLAG_VIDEO,
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ DXVA2Mapping {
    uint32_t palette_dummy[256];
} DXVA2Mapping;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ DXVA2FramesContext {
    /**
     * The public AVDXVA2FramesContext. See hwcontext_dxva2.h for it.
     */
    AVDXVA2FramesContext p;

    IDirect3DSurface9 **surfaces_internal;
    ಪೂರ್ಣಾಙ್ಕ              nb_surfaces_used;

    HANDLE  device_handle;
    IDirectXVideoAccelerationService *service;

    D3DFORMAT format;
} DXVA2FramesContext;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ DXVA2DevicePriv {
    HMODULE d3dlib;
    HMODULE dxva2lib;

    HANDLE device_handle;

    IDirect3D9       *d3d9;
    IDirect3DDevice9 *d3d9device;
} DXVA2DevicePriv;

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
    D3DFORMAT d3d_format;
    ಗಣನಾ AVPixelFormat pix_fmt;
} supported_formats[] = {
    { MKTAG('N', 'V', '1', '2'), AV_PIX_FMT_NV12 },
    { MKTAG('P', '0', '1', '0'), AV_PIX_FMT_P010 },
    { MKTAG('A', 'Y', 'U', 'V'), AV_PIX_FMT_VUYX },
    { MKTAG('Y', 'U', 'Y', '2'), AV_PIX_FMT_YUYV422 },
    { MKTAG('Y', '2', '1', '0'), AV_PIX_FMT_Y210 },
    { MKTAG('Y', '4', '1', '0'), AV_PIX_FMT_XV30 },
    { MKTAG('P', '0', '1', '6'), AV_PIX_FMT_P012 },
    { MKTAG('Y', '2', '1', '6'), AV_PIX_FMT_Y216 },
    { MKTAG('Y', '4', '1', '6'), AV_PIX_FMT_XV48 },
    // There is no 12bit pixel format defined in D3DFMT*, use 16bit to compatible
    // with 12 bit AV_PIX_FMT* formats.
    { MKTAG('Y', '2', '1', '6'), AV_PIX_FMT_Y212 },
    { MKTAG('Y', '4', '1', '6'), AV_PIX_FMT_XV36 },
    { D3DFMT_P8,                 AV_PIX_FMT_PAL8 },
    { D3DFMT_A8R8G8B8,           AV_PIX_FMT_BGRA },
};

DEFINE_GUID(video_decoder_service,   0xfc51a551, 0xd5e7, 0x11d9, 0xaf, 0x55, 0x00, 0x05, 0x4e, 0x43, 0xff, 0x02);
DEFINE_GUID(video_processor_service, 0xfc51a552, 0xd5e7, 0x11d9, 0xaf, 0x55, 0x00, 0x05, 0x4e, 0x43, 0xff, 0x02);

ಸ್ಥಿರ ಶೂನ್ಯ dxva2_frames_uninit(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2FramesContext              *s = ctx->hwctx;
    AVDXVA2FramesContext *frames_hwctx = &s->p;
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯದಿ (frames_hwctx->decoder_to_release)
        IDirectXVideoDecoder_Release(frames_hwctx->decoder_to_release);

    ಯದಿ (s->surfaces_internal) {
        ಪ್ರತಿ (i = 0; i < frames_hwctx->nb_surfaces; i++) {
            ಯದಿ (s->surfaces_internal[i])
                IDirect3DSurface9_Release(s->surfaces_internal[i]);
        }
    }
    av_freep(&s->surfaces_internal);

    ಯದಿ (s->service) {
        IDirectXVideoAccelerationService_Release(s->service);
        s->service = ರಿಕ್ತ;
    }

    ಯದಿ (s->device_handle != INVALID_HANDLE_ಮೌಲ್ಯ) {
        IDirect3DDeviceManager9_CloseDeviceHandle(device_hwctx->devmgr, s->device_handle);
        s->device_handle = INVALID_HANDLE_ಮೌಲ್ಯ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ dxva2_pool_release_dummy(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    // important not to free anything here--data is a surface object
    // associated with the call to CreateSurface(), and these surfaces are
    // released in dxva2_frames_uninit()
}

ಸ್ಥಿರ AVBufferRef *dxva2_pool_alloc(ಶೂನ್ಯ *opaque, size_t size)
{
    AVHWFramesContext      *ctx = (AVHWFramesContext*)opaque;
    DXVA2FramesContext       *s = ctx->hwctx;
    AVDXVA2FramesContext *hwctx = &s->p;

    ಯದಿ (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        ಪ್ರತ್ಯಾಗಮ av_buffer_create((uint8_t*)s->surfaces_internal[s->nb_surfaces_used - 1],
                                ಪರಿಮಾಣ(**hwctx->surfaces), dxva2_pool_release_dummy, 0, 0);
    }

    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ dxva2_init_pool(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2FramesContext              *s = ctx->hwctx;
    AVDXVA2FramesContext *frames_hwctx = &s->p;
    ಪೂರ್ಣಾಙ್ಕ decode = (frames_hwctx->surface_type == DXVA2_VideoDecoderRenderTarget);

    ಪೂರ್ಣಾಙ್ಕ i;
    HRESULT hr;

    ಯದಿ (ctx->initial_pool_size <= 0)
        ಪ್ರತ್ಯಾಗಮ 0;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(device_hwctx->devmgr, &s->device_handle);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_GetVideoService(device_hwctx->devmgr,
                                                 s->device_handle,
                                                 decode ? &video_decoder_service : &video_processor_service,
                                                 (ಶೂನ್ಯ **)&s->service);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create the video service\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ಯದಿ (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            ಭಙ್ಗ;
        }
    }
    ಯದಿ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     ಪರಿಮಾಣ(*s->surfaces_internal));
    ಯದಿ (!s->surfaces_internal)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    hr = IDirectXVideoAccelerationService_CreateSurface(s->service,
                                                        ctx->width, ctx->height,
                                                        ctx->initial_pool_size - 1,
                                                        s->format, D3DPOOL_DEFAULT, 0,
                                                        frames_hwctx->surface_type,
                                                        s->surfaces_internal, ರಿಕ್ತ);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the surfaces\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(ಪರಿಮಾಣ(*s->surfaces_internal),
                             ctx, dxva2_pool_alloc, ರಿಕ್ತ);
    ಯದಿ (!ffhwframesctx(ctx)->pool_internal)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ dxva2_frames_init(AVHWFramesContext *ctx)
{
    DXVA2FramesContext       *s = ctx->hwctx;
    AVDXVA2FramesContext *hwctx = &s->p;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (hwctx->surface_type != DXVA2_VideoDecoderRenderTarget &&
        hwctx->surface_type != DXVA2_VideoProcessorRenderTarget) {
        av_log(ctx, AV_LOG_ERROR, "Unknown surface type: %lu\n",
               hwctx->surface_type);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    s->device_handle = INVALID_HANDLE_ಮೌಲ್ಯ;

    /* init the frame pool if the caller didn't provide one */
    ಯದಿ (!ctx->pool) {
        ret = dxva2_init_pool(ctx);
        ಯದಿ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            ಪ್ರತ್ಯಾಗಮ ret;
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ dxva2_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ಯದಿ (!frame->buf[0])
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_DXVA2_VLD;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ dxva2_transfer_get_formats(AVHWFramesContext *ctx,
                                      ಗಣನಾ AVHWFrameTransferDirection dir,
                                      ಗಣನಾ AVPixelFormat **formats)
{
    ಗಣನಾ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ಪರಿಮಾಣ(*fmts));
    ಯದಿ (!fmts)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ dxva2_unmap_frame(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)hwmap->source->data[3];
    IDirect3DSurface9_UnlockRect(surface);
    av_freep(&hwmap->priv);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ dxva2_map_frame(AVHWFramesContext *ctx, AVFrame *dst, ಧ್ರುವ AVFrame *src,
                           ಪೂರ್ಣಾಙ್ಕ flags)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->data[3];
    DXVA2Mapping      *map;
    D3DSURFACE_DESC    surfaceDesc;
    D3DLOCKED_RECT     LockedRect;
    HRESULT            hr;
    ಪೂರ್ಣಾಙ್ಕ i, err, nb_planes;
    ಪೂರ್ಣಾಙ್ಕ lock_flags = 0;

    nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(dst->format);

    hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಯದಿ (!(flags & AV_HWFRAME_MAP_WRITE))
        lock_flags |= D3DLOCK_READONLY;
    ಯದಿ (flags & AV_HWFRAME_MAP_OVERWRITE)
        lock_flags |= D3DLOCK_DISCARD;

    hr = IDirect3DSurface9_LockRect(surface, &LockedRect, ರಿಕ್ತ, lock_flags);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    map = av_mallocz(ಪರಿಮಾಣ(*map));
    ಯದಿ (!map) {
        err = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                dxva2_unmap_frame, map);
    ಯದಿ (err < 0) {
        av_freep(&map);
        ಗಚ್ಛ fail;
    }

    ಪ್ರತಿ (i = 0; i < nb_planes; i++)
        dst->linesize[i] = LockedRect.Pitch;

    av_image_fill_pointers(dst->data, dst->format, surfaceDesc.Height,
                           (uint8_t*)LockedRect.pBits, dst->linesize);

    ಯದಿ (dst->format == AV_PIX_FMT_PAL8)
        dst->data[1] = (uint8_t*)map->palette_dummy;

    ಪ್ರತ್ಯಾಗಮ 0;
fail:
    IDirect3DSurface9_UnlockRect(surface);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ dxva2_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  ಧ್ರುವ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (src->format != ctx->sw_format)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);

    map = av_frame_alloc();
    ಯದಿ (!map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    av_image_copy2(map->data, map->linesize, src->data, src->linesize,
                   ctx->sw_format, src->width, src->height);

fail:
    av_frame_free(&map);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ dxva2_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ಧ್ರುವ AVFrame *src)
{
    AVFrame *map;
    ptrdiff_t src_linesize[4], dst_linesize[4];
    ಪೂರ್ಣಾಙ್ಕ ret, i;

    ಯದಿ (dst->format != ctx->sw_format)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);

    map = av_frame_alloc();
    ಯದಿ (!map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, src, AV_HWFRAME_MAP_READ);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    ಪ್ರತಿ (i = 0; i < 4; i++) {
        dst_linesize[i] = dst->linesize[i];
        src_linesize[i] = map->linesize[i];
    }
    av_image_copy_uc_from(dst->data, dst_linesize, (ಧ್ರುವ uint8_t **)map->data, src_linesize,
                          ctx->sw_format, src->width, src->height);
fail:
    av_frame_free(&map);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ dxva2_map_from(AVHWFramesContext *ctx,
                          AVFrame *dst, ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ err;

    ಯದಿ (dst->format != AV_PIX_FMT_NONE && dst->format != ctx->sw_format)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    dst->format = ctx->sw_format;

    err = dxva2_map_frame(ctx, dst, src, flags);
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    err = av_frame_copy_props(dst, src);
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ dxva2_device_free(AVHWDeviceContext *ctx)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv       *priv = ctx->user_opaque;

    ಯದಿ (hwctx->devmgr && priv->device_handle != INVALID_HANDLE_ಮೌಲ್ಯ)
        IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, priv->device_handle);

    ಯದಿ (hwctx->devmgr)
        IDirect3DDeviceManager9_Release(hwctx->devmgr);

    ಯದಿ (priv->d3d9device)
        IDirect3DDevice9_Release(priv->d3d9device);

    ಯದಿ (priv->d3d9)
        IDirect3D9_Release(priv->d3d9);

    ಯದಿ (priv->d3dlib)
        dlclose(priv->d3dlib);

    ಯದಿ (priv->dxva2lib)
        dlclose(priv->dxva2lib);

    av_freep(&ctx->user_opaque);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ dxva2_device_create9(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODE d3ddm;
    HRESULT hr;
    pDirect3DCreate9 *createD3D = (pDirect3DCreate9 *)dlsym(priv->d3dlib, "Direct3DCreate9");
    ಯದಿ (!createD3D) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate Direct3DCreate9\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    priv->d3d9 = createD3D(D3D_SDK_VERSION);
    ಯದಿ (!priv->d3d9) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create IDirect3D object\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    IDirect3D9_GetAdapterDisplayMode(priv->d3d9, adapter, &d3ddm);

    d3dpp.BackBufferFormat = d3ddm.Format;

    hr = IDirect3D9_CreateDevice(priv->d3d9, adapter, D3DDEVTYPE_HAL, GetDesktopWindow(),
                                 FF_D3DCREATE_FLAGS,
                                 &d3dpp, &priv->d3d9device);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ dxva2_device_create9ex(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODEEX modeex = {0};
    IDirect3D9Ex *d3d9ex = ರಿಕ್ತ;
    IDirect3DDevice9Ex *exdev = ರಿಕ್ತ;
    HRESULT hr;
    pDirect3DCreate9Ex *createD3DEx = (pDirect3DCreate9Ex *)dlsym(priv->d3dlib, "Direct3DCreate9Ex");
    ಯದಿ (!createD3DEx)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);

    hr = createD3DEx(D3D_SDK_VERSION, &d3d9ex);
    ಯದಿ (FAILED(hr))
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;

    modeex.Size = ಪರಿಮಾಣ(D3DDISPLAYMODEEX);
    hr = IDirect3D9Ex_GetAdapterDisplayModeEx(d3d9ex, adapter, &modeex, ರಿಕ್ತ);
    ಯದಿ (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    d3dpp.BackBufferFormat = modeex.Format;

    hr = IDirect3D9Ex_CreateDeviceEx(d3d9ex, adapter, D3DDEVTYPE_HAL, GetDesktopWindow(),
                                     FF_D3DCREATE_FLAGS,
                                     &d3dpp, ರಿಕ್ತ, &exdev);
    ಯದಿ (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Using D3D9Ex device.\n");
    priv->d3d9 = (IDirect3D9 *)d3d9ex;
    priv->d3d9device = (IDirect3DDevice9 *)exdev;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ dxva2_device_create(AVHWDeviceContext *ctx, ಧ್ರುವ ವರ್ಣ *device,
                               AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv *priv;
    pCreateDeviceManager9 *createDeviceManager = ರಿಕ್ತ;
    unsigned resetToken = 0;
    UINT adapter = D3DADAPTER_DEFAULT;
    HRESULT hr;
    ಪೂರ್ಣಾಙ್ಕ err;

    ಯದಿ (device)
        adapter = atoi(device);

    priv = av_mallocz(ಪರಿಮಾಣ(*priv));
    ಯದಿ (!priv)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ಮುಕ್ತ        = dxva2_device_free;

    priv->device_handle = INVALID_HANDLE_ಮೌಲ್ಯ;

    priv->d3dlib = dlopen("d3d9.dll", 0);
    ಯದಿ (!priv->d3dlib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D9 library\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }
    priv->dxva2lib = dlopen("dxva2.dll", 0);
    ಯದಿ (!priv->dxva2lib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load DXVA2 library\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    createDeviceManager = (pCreateDeviceManager9 *)dlsym(priv->dxva2lib,
                                                         "DXVA2CreateDirect3DDeviceManager9");
    ಯದಿ (!createDeviceManager) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate DXVA2CreateDirect3DDeviceManager9\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಯದಿ (dxva2_device_create9ex(ctx, adapter) < 0) {
        // Retry with "classic" d3d9
        err = dxva2_device_create9(ctx, adapter);
        ಯದಿ (err < 0)
            ಪ್ರತ್ಯಾಗಮ err;
    }

    hr = createDeviceManager(&resetToken, &hwctx->devmgr);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device manager\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_ResetDevice(hwctx->devmgr, priv->d3d9device, resetToken);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind Direct3D device to device manager\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &priv->device_handle);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಧ್ರುವ HWContextType ff_hwcontext_type_dxva2 = {
    .type                 = AV_HWDEVICE_TYPE_DXVA2,
    .name                 = "DXVA2",

    .device_hwctx_size    = ಪರಿಮಾಣ(AVDXVA2DeviceContext),
    .frames_hwctx_size    = ಪರಿಮಾಣ(DXVA2FramesContext),

    .device_create        = dxva2_device_create,
    .frames_init          = dxva2_frames_init,
    .frames_uninit        = dxva2_frames_uninit,
    .frames_get_buffer    = dxva2_get_buffer,
    .transfer_get_formats = dxva2_transfer_get_formats,
    .transfer_data_to     = dxva2_transfer_data_to,
    .transfer_data_from   = dxva2_transfer_data_from,
    .map_from             = dxva2_map_from,

    .pix_fmts             = (ಧ್ರುವ ಗಣನಾ AVPixelFormat[]){ AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_NONE },
};
