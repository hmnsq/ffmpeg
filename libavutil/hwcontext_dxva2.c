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

#অন্তর্ভাৱ <windows.h>

#define DXVA2API_USE_BITFIELDS
#define COBJMACROS

#অন্তর্ভাৱ <d3d9.h>
#অন্তর্ভাৱ <dxva2api.h>
#অন্তর্ভাৱ <initguid.h>

#অন্তর্ভাৱ "avassert.h"
#অন্তর্ভাৱ "common.h"
#অন্তর্ভাৱ "hwcontext.h"
#অন্তর্ভাৱ "hwcontext_dxva2.h"
#অন্তর্ভাৱ "hwcontext_internal.h"
#অন্তর্ভাৱ "imgutils.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "pixdesc.h"
#অন্তর্ভাৱ "pixfmt.h"
#অন্তর্ভাৱ "compat/w32dlfcn.h"

প্রকারনির্দেশ IDirect3D9* WINAPI pDirect3DCreate9(UINT);
প্রকারনির্দেশ HRESULT WINAPI pDirect3DCreate9Ex(UINT, IDirect3D9Ex **);
প্রকারনির্দেশ HRESULT WINAPI pCreateDeviceManager9(UINT *, IDirect3DDeviceManager9 **);

#define FF_D3DCREATE_FLAGS (D3DCREATE_SOFTWARE_VERTEXPROCESSING | \
                            D3DCREATE_MULTITHREADED | \
                            D3DCREATE_FPU_PRESERVE)

স্থির ধ্রুৱ D3DPRESENT_PARAMETERS dxva2_present_params = {
    .Windowed         = TRUE,
    .BackBufferWidth  = 640,
    .BackBufferHeight = 480,
    .Back_Buffer_গুনতি  = 0,
    .SwapEffect       = D3DSWAPEFFECT_DISCARD,
    .Flags            = D3DPRESENTFLAG_VIDEO,
};

প্রকারনির্দেশ সংরচনা DXVA2Mapping {
    uint32_t palette_dummy[256];
} DXVA2Mapping;

প্রকারনির্দেশ সংরচনা DXVA2FramesContext {
    /**
     * The public AVDXVA2FramesContext. See hwcontext_dxva2.h for it.
     */
    AVDXVA2FramesContext p;

    IDirect3DSurface9 **surfaces_internal;
    পূর্ণাঙ্ক              nb_surfaces_used;

    HANDLE  device_handle;
    IDirectXVideoAccelerationService *service;

    D3DFORMAT format;
} DXVA2FramesContext;

প্রকারনির্দেশ সংরচনা DXVA2DevicePriv {
    HMODULE d3dlib;
    HMODULE dxva2lib;

    HANDLE device_handle;

    IDirect3D9       *d3d9;
    IDirect3DDevice9 *d3d9device;
} DXVA2DevicePriv;

স্থির ধ্রুৱ সংরচনা {
    D3DFORMAT d3d_format;
    গণনা AVPixelFormat pix_fmt;
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

স্থির শূন্য dxva2_frames_uninit(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2FramesContext              *s = ctx->hwctx;
    AVDXVA2FramesContext *frames_hwctx = &s->p;
    পূর্ণাঙ্ক i;

    যদি (frames_hwctx->decoder_to_release)
        IDirectXVideoDecoder_Release(frames_hwctx->decoder_to_release);

    যদি (s->surfaces_internal) {
        বাবে (i = 0; i < frames_hwctx->nb_surfaces; i++) {
            যদি (s->surfaces_internal[i])
                IDirect3DSurface9_Release(s->surfaces_internal[i]);
        }
    }
    av_freep(&s->surfaces_internal);

    যদি (s->service) {
        IDirectXVideoAccelerationService_Release(s->service);
        s->service = রিক্ত;
    }

    যদি (s->device_handle != INVALID_HANDLE_মান) {
        IDirect3DDeviceManager9_CloseDeviceHandle(device_hwctx->devmgr, s->device_handle);
        s->device_handle = INVALID_HANDLE_মান;
    }
}

স্থির শূন্য dxva2_pool_release_dummy(শূন্য *opaque, uint8_t *data)
{
    // important not to free anything here--data is a surface object
    // associated with the call to CreateSurface(), and these surfaces are
    // released in dxva2_frames_uninit()
}

স্থির AVBufferRef *dxva2_pool_alloc(শূন্য *opaque, size_t size)
{
    AVHWFramesContext      *ctx = (AVHWFramesContext*)opaque;
    DXVA2FramesContext       *s = ctx->hwctx;
    AVDXVA2FramesContext *hwctx = &s->p;

    যদি (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        ঘূৰাই av_buffer_create((uint8_t*)s->surfaces_internal[s->nb_surfaces_used - 1],
                                পরিমাণ(**hwctx->surfaces), dxva2_pool_release_dummy, 0, 0);
    }

    ঘূৰাই রিক্ত;
}

স্থির পূর্ণাঙ্ক dxva2_init_pool(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2FramesContext              *s = ctx->hwctx;
    AVDXVA2FramesContext *frames_hwctx = &s->p;
    পূর্ণাঙ্ক decode = (frames_hwctx->surface_type == DXVA2_VideoDecoderRenderTarget);

    পূর্ণাঙ্ক i;
    HRESULT hr;

    যদি (ctx->initial_pool_size <= 0)
        ঘূৰাই 0;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(device_hwctx->devmgr, &s->device_handle);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_GetVideoService(device_hwctx->devmgr,
                                                 s->device_handle,
                                                 decode ? &video_decoder_service : &video_processor_service,
                                                 (শূন্য **)&s->service);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create the video service\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }

    বাবে (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        যদি (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            ভঙ্গ;
        }
    }
    যদি (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ঘূৰাই AVERROR(EINVAL);
    }

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     পরিমাণ(*s->surfaces_internal));
    যদি (!s->surfaces_internal)
        ঘূৰাই AVERROR(ENOMEM);

    hr = IDirectXVideoAccelerationService_CreateSurface(s->service,
                                                        ctx->width, ctx->height,
                                                        ctx->initial_pool_size - 1,
                                                        s->format, D3DPOOL_DEFAULT, 0,
                                                        frames_hwctx->surface_type,
                                                        s->surfaces_internal, রিক্ত);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the surfaces\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(পরিমাণ(*s->surfaces_internal),
                             ctx, dxva2_pool_alloc, রিক্ত);
    যদি (!ffhwframesctx(ctx)->pool_internal)
        ঘূৰাই AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক dxva2_frames_init(AVHWFramesContext *ctx)
{
    DXVA2FramesContext       *s = ctx->hwctx;
    AVDXVA2FramesContext *hwctx = &s->p;
    পূর্ণাঙ্ক ret;

    যদি (hwctx->surface_type != DXVA2_VideoDecoderRenderTarget &&
        hwctx->surface_type != DXVA2_VideoProcessorRenderTarget) {
        av_log(ctx, AV_LOG_ERROR, "Unknown surface type: %lu\n",
               hwctx->surface_type);
        ঘূৰাই AVERROR(EINVAL);
    }

    s->device_handle = INVALID_HANDLE_মান;

    /* init the frame pool if the caller didn't provide one */
    যদি (!ctx->pool) {
        ret = dxva2_init_pool(ctx);
        যদি (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            ঘূৰাই ret;
        }
    }

    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক dxva2_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    যদি (!frame->buf[0])
        ঘূৰাই AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_DXVA2_VLD;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক dxva2_transfer_get_formats(AVHWFramesContext *ctx,
                                      গণনা AVHWFrameTransferDirection dir,
                                      গণনা AVPixelFormat **formats)
{
    গণনা AVPixelFormat *fmts;

    fmts = av_malloc_array(2, পরিমাণ(*fmts));
    যদি (!fmts)
        ঘূৰাই AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ঘূৰাই 0;
}

স্থির শূন্য dxva2_unmap_frame(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)hwmap->source->data[3];
    IDirect3DSurface9_UnlockRect(surface);
    av_freep(&hwmap->priv);
}

স্থির পূর্ণাঙ্ক dxva2_map_frame(AVHWFramesContext *ctx, AVFrame *dst, ধ্রুৱ AVFrame *src,
                           পূর্ণাঙ্ক flags)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->data[3];
    DXVA2Mapping      *map;
    D3DSURFACE_DESC    surfaceDesc;
    D3DLOCKED_RECT     LockedRect;
    HRESULT            hr;
    পূর্ণাঙ্ক i, err, nb_planes;
    পূর্ণাঙ্ক lock_flags = 0;

    nb_planes = av_pix_fmt_গুনতি_planes(dst->format);

    hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }

    যদি (!(flags & AV_HWFRAME_MAP_WRITE))
        lock_flags |= D3DLOCK_READONLY;
    যদি (flags & AV_HWFRAME_MAP_OVERWRITE)
        lock_flags |= D3DLOCK_DISCARD;

    hr = IDirect3DSurface9_LockRect(surface, &LockedRect, রিক্ত, lock_flags);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }

    map = av_mallocz(পরিমাণ(*map));
    যদি (!map) {
        err = AVERROR(ENOMEM);
        গচ্ছ fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                dxva2_unmap_frame, map);
    যদি (err < 0) {
        av_freep(&map);
        গচ্ছ fail;
    }

    বাবে (i = 0; i < nb_planes; i++)
        dst->linesize[i] = LockedRect.Pitch;

    av_image_fill_pointers(dst->data, dst->format, surfaceDesc.Height,
                           (uint8_t*)LockedRect.pBits, dst->linesize);

    যদি (dst->format == AV_PIX_FMT_PAL8)
        dst->data[1] = (uint8_t*)map->palette_dummy;

    ঘূৰাই 0;
fail:
    IDirect3DSurface9_UnlockRect(surface);
    ঘূৰাই err;
}

স্থির পূর্ণাঙ্ক dxva2_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  ধ্রুৱ AVFrame *src)
{
    AVFrame *map;
    পূর্ণাঙ্ক ret;

    যদি (src->format != ctx->sw_format)
        ঘূৰাই AVERROR(ENOSYS);

    map = av_frame_alloc();
    যদি (!map)
        ঘূৰাই AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    যদি (ret < 0)
        গচ্ছ fail;

    av_image_copy2(map->data, map->linesize, src->data, src->linesize,
                   ctx->sw_format, src->width, src->height);

fail:
    av_frame_free(&map);
    ঘূৰাই ret;
}

স্থির পূর্ণাঙ্ক dxva2_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ধ্রুৱ AVFrame *src)
{
    AVFrame *map;
    ptrdiff_t src_linesize[4], dst_linesize[4];
    পূর্ণাঙ্ক ret, i;

    যদি (dst->format != ctx->sw_format)
        ঘূৰাই AVERROR(ENOSYS);

    map = av_frame_alloc();
    যদি (!map)
        ঘূৰাই AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, src, AV_HWFRAME_MAP_READ);
    যদি (ret < 0)
        গচ্ছ fail;

    বাবে (i = 0; i < 4; i++) {
        dst_linesize[i] = dst->linesize[i];
        src_linesize[i] = map->linesize[i];
    }
    av_image_copy_uc_from(dst->data, dst_linesize, (ধ্রুৱ uint8_t **)map->data, src_linesize,
                          ctx->sw_format, src->width, src->height);
fail:
    av_frame_free(&map);
    ঘূৰাই ret;
}

স্থির পূর্ণাঙ্ক dxva2_map_from(AVHWFramesContext *ctx,
                          AVFrame *dst, ধ্রুৱ AVFrame *src, পূর্ণাঙ্ক flags)
{
    পূর্ণাঙ্ক err;

    যদি (dst->format != AV_PIX_FMT_NONE && dst->format != ctx->sw_format)
        ঘূৰাই AVERROR(ENOSYS);
    dst->format = ctx->sw_format;

    err = dxva2_map_frame(ctx, dst, src, flags);
    যদি (err < 0)
        ঘূৰাই err;

    err = av_frame_copy_props(dst, src);
    যদি (err < 0)
        ঘূৰাই err;

    ঘূৰাই 0;
}

স্থির শূন্য dxva2_device_free(AVHWDeviceContext *ctx)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv       *priv = ctx->user_opaque;

    যদি (hwctx->devmgr && priv->device_handle != INVALID_HANDLE_মান)
        IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, priv->device_handle);

    যদি (hwctx->devmgr)
        IDirect3DDeviceManager9_Release(hwctx->devmgr);

    যদি (priv->d3d9device)
        IDirect3DDevice9_Release(priv->d3d9device);

    যদি (priv->d3d9)
        IDirect3D9_Release(priv->d3d9);

    যদি (priv->d3dlib)
        dlclose(priv->d3dlib);

    যদি (priv->dxva2lib)
        dlclose(priv->dxva2lib);

    av_freep(&ctx->user_opaque);
}

স্থির পূর্ণাঙ্ক dxva2_device_create9(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODE d3ddm;
    HRESULT hr;
    pDirect3DCreate9 *createD3D = (pDirect3DCreate9 *)dlsym(priv->d3dlib, "Direct3DCreate9");
    যদি (!createD3D) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate Direct3DCreate9\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }

    priv->d3d9 = createD3D(D3D_SDK_VERSION);
    যদি (!priv->d3d9) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create IDirect3D object\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }

    IDirect3D9_GetAdapterDisplayMode(priv->d3d9, adapter, &d3ddm);

    d3dpp.BackBufferFormat = d3ddm.Format;

    hr = IDirect3D9_CreateDevice(priv->d3d9, adapter, D3DDEVTYPE_HAL, GetDesktopWindow(),
                                 FF_D3DCREATE_FLAGS,
                                 &d3dpp, &priv->d3d9device);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }

    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক dxva2_device_create9ex(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODEEX modeex = {0};
    IDirect3D9Ex *d3d9ex = রিক্ত;
    IDirect3DDevice9Ex *exdev = রিক্ত;
    HRESULT hr;
    pDirect3DCreate9Ex *createD3DEx = (pDirect3DCreate9Ex *)dlsym(priv->d3dlib, "Direct3DCreate9Ex");
    যদি (!createD3DEx)
        ঘূৰাই AVERROR(ENOSYS);

    hr = createD3DEx(D3D_SDK_VERSION, &d3d9ex);
    যদি (FAILED(hr))
        ঘূৰাই AVERROR_UNKNOWN;

    modeex.Size = পরিমাণ(D3DDISPLAYMODEEX);
    hr = IDirect3D9Ex_GetAdapterDisplayModeEx(d3d9ex, adapter, &modeex, রিক্ত);
    যদি (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        ঘূৰাই AVERROR_UNKNOWN;
    }

    d3dpp.BackBufferFormat = modeex.Format;

    hr = IDirect3D9Ex_CreateDeviceEx(d3d9ex, adapter, D3DDEVTYPE_HAL, GetDesktopWindow(),
                                     FF_D3DCREATE_FLAGS,
                                     &d3dpp, রিক্ত, &exdev);
    যদি (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        ঘূৰাই AVERROR_UNKNOWN;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Using D3D9Ex device.\n");
    priv->d3d9 = (IDirect3D9 *)d3d9ex;
    priv->d3d9device = (IDirect3DDevice9 *)exdev;
    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক dxva2_device_create(AVHWDeviceContext *ctx, ধ্রুৱ ৱর্ণ *device,
                               AVDictionary *opts, পূর্ণাঙ্ক flags)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv *priv;
    pCreateDeviceManager9 *createDeviceManager = রিক্ত;
    unsigned resetToken = 0;
    UINT adapter = D3DADAPTER_DEFAULT;
    HRESULT hr;
    পূর্ণাঙ্ক err;

    যদি (device)
        adapter = atoi(device);

    priv = av_mallocz(পরিমাণ(*priv));
    যদি (!priv)
        ঘূৰাই AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->মুক্ত        = dxva2_device_free;

    priv->device_handle = INVALID_HANDLE_মান;

    priv->d3dlib = dlopen("d3d9.dll", 0);
    যদি (!priv->d3dlib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D9 library\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }
    priv->dxva2lib = dlopen("dxva2.dll", 0);
    যদি (!priv->dxva2lib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load DXVA2 library\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }

    createDeviceManager = (pCreateDeviceManager9 *)dlsym(priv->dxva2lib,
                                                         "DXVA2CreateDirect3DDeviceManager9");
    যদি (!createDeviceManager) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate DXVA2CreateDirect3DDeviceManager9\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }

    যদি (dxva2_device_create9ex(ctx, adapter) < 0) {
        // Retry with "classic" d3d9
        err = dxva2_device_create9(ctx, adapter);
        যদি (err < 0)
            ঘূৰাই err;
    }

    hr = createDeviceManager(&resetToken, &hwctx->devmgr);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device manager\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_ResetDevice(hwctx->devmgr, priv->d3d9device, resetToken);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind Direct3D device to device manager\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &priv->device_handle);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        ঘূৰাই AVERROR_UNKNOWN;
    }

    ঘূৰাই 0;
}

ধ্রুৱ HWContextType ff_hwcontext_type_dxva2 = {
    .type                 = AV_HWDEVICE_TYPE_DXVA2,
    .name                 = "DXVA2",

    .device_hwctx_size    = পরিমাণ(AVDXVA2DeviceContext),
    .frames_hwctx_size    = পরিমাণ(DXVA2FramesContext),

    .device_create        = dxva2_device_create,
    .frames_init          = dxva2_frames_init,
    .frames_uninit        = dxva2_frames_uninit,
    .frames_get_buffer    = dxva2_get_buffer,
    .transfer_get_formats = dxva2_transfer_get_formats,
    .transfer_data_to     = dxva2_transfer_data_to,
    .transfer_data_from   = dxva2_transfer_data_from,
    .map_from             = dxva2_map_from,

    .pix_fmts             = (ধ্রুৱ গণনা AVPixelFormat[]){ AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_NONE },
};
