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

#અન્તર્ભાવ <windows.h>

#define DXVA2API_USE_BITFIELDS
#define COBJMACROS

#અન્તર્ભાવ <d3d9.h>
#અન્તર્ભાવ <dxva2api.h>
#અન્તર્ભાવ <initguid.h>

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "hwcontext.h"
#અન્તર્ભાવ "hwcontext_dxva2.h"
#અન્તર્ભાવ "hwcontext_internal.h"
#અન્તર્ભાવ "imgutils.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "pixdesc.h"
#અન્તર્ભાવ "pixfmt.h"
#અન્તર્ભાવ "compat/w32dlfcn.h"

પ્રકારવ્યાખ્યા IDirect3D9* WINAPI pDirect3DCreate9(UINT);
પ્રકારવ્યાખ્યા HRESULT WINAPI pDirect3DCreate9Ex(UINT, IDirect3D9Ex **);
પ્રકારવ્યાખ્યા HRESULT WINAPI pCreateDeviceManager9(UINT *, IDirect3DDeviceManager9 **);

#define FF_D3DCREATE_FLAGS (D3DCREATE_SOFTWARE_VERTEXPROCESSING | \
                            D3DCREATE_MULTITHREADED | \
                            D3DCREATE_FPU_PRESERVE)

સ્થિર અચલ D3DPRESENT_PARAMETERS dxva2_present_params = {
    .Windowed         = TRUE,
    .BackBufferWidth  = 640,
    .BackBufferHeight = 480,
    .Back_Buffer_ગણતરી  = 0,
    .SwapEffect       = D3DSWAPEFFECT_DISCARD,
    .Flags            = D3DPRESENTFLAG_VIDEO,
};

પ્રકારવ્યાખ્યા સંરચના DXVA2Mapping {
    uint32_t palette_dummy[256];
} DXVA2Mapping;

પ્રકારવ્યાખ્યા સંરચના DXVA2FramesContext {
    /**
     * The public AVDXVA2FramesContext. See hwcontext_dxva2.h for it.
     */
    AVDXVA2FramesContext p;

    IDirect3DSurface9 **surfaces_internal;
    પૂર્ણાંક              nb_surfaces_used;

    HANDLE  device_handle;
    IDirectXVideoAccelerationService *service;

    D3DFORMAT format;
} DXVA2FramesContext;

પ્રકારવ્યાખ્યા સંરચના DXVA2DevicePriv {
    HMODULE d3dlib;
    HMODULE dxva2lib;

    HANDLE device_handle;

    IDirect3D9       *d3d9;
    IDirect3DDevice9 *d3d9device;
} DXVA2DevicePriv;

સ્થિર અચલ સંરચના {
    D3DFORMAT d3d_format;
    ગણના AVPixelFormat pix_fmt;
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

સ્થિર શૂન્ય dxva2_frames_uninit(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2FramesContext              *s = ctx->hwctx;
    AVDXVA2FramesContext *frames_hwctx = &s->p;
    પૂર્ણાંક i;

    જો (frames_hwctx->decoder_to_release)
        IDirectXVideoDecoder_Release(frames_hwctx->decoder_to_release);

    જો (s->surfaces_internal) {
        માટે (i = 0; i < frames_hwctx->nb_surfaces; i++) {
            જો (s->surfaces_internal[i])
                IDirect3DSurface9_Release(s->surfaces_internal[i]);
        }
    }
    av_freep(&s->surfaces_internal);

    જો (s->service) {
        IDirectXVideoAccelerationService_Release(s->service);
        s->service = ખાલી;
    }

    જો (s->device_handle != INVALID_HANDLE_કિંમત) {
        IDirect3DDeviceManager9_CloseDeviceHandle(device_hwctx->devmgr, s->device_handle);
        s->device_handle = INVALID_HANDLE_કિંમત;
    }
}

સ્થિર શૂન્ય dxva2_pool_release_dummy(શૂન્ય *opaque, uint8_t *data)
{
    // important not to free anything here--data is a surface object
    // associated with the call to CreateSurface(), and these surfaces are
    // released in dxva2_frames_uninit()
}

સ્થિર AVBufferRef *dxva2_pool_alloc(શૂન્ય *opaque, size_t size)
{
    AVHWFramesContext      *ctx = (AVHWFramesContext*)opaque;
    DXVA2FramesContext       *s = ctx->hwctx;
    AVDXVA2FramesContext *hwctx = &s->p;

    જો (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        પાછા av_buffer_create((uint8_t*)s->surfaces_internal[s->nb_surfaces_used - 1],
                                કદ(**hwctx->surfaces), dxva2_pool_release_dummy, 0, 0);
    }

    પાછા ખાલી;
}

સ્થિર પૂર્ણાંક dxva2_init_pool(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2FramesContext              *s = ctx->hwctx;
    AVDXVA2FramesContext *frames_hwctx = &s->p;
    પૂર્ણાંક decode = (frames_hwctx->surface_type == DXVA2_VideoDecoderRenderTarget);

    પૂર્ણાંક i;
    HRESULT hr;

    જો (ctx->initial_pool_size <= 0)
        પાછા 0;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(device_hwctx->devmgr, &s->device_handle);
    જો (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        પાછા AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_GetVideoService(device_hwctx->devmgr,
                                                 s->device_handle,
                                                 decode ? &video_decoder_service : &video_processor_service,
                                                 (શૂન્ય **)&s->service);
    જો (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create the video service\n");
        પાછા AVERROR_UNKNOWN;
    }

    માટે (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        જો (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            તોડો;
        }
    }
    જો (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        પાછા AVERROR(EINVAL);
    }

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     કદ(*s->surfaces_internal));
    જો (!s->surfaces_internal)
        પાછા AVERROR(ENOMEM);

    hr = IDirectXVideoAccelerationService_CreateSurface(s->service,
                                                        ctx->width, ctx->height,
                                                        ctx->initial_pool_size - 1,
                                                        s->format, D3DPOOL_DEFAULT, 0,
                                                        frames_hwctx->surface_type,
                                                        s->surfaces_internal, ખાલી);
    જો (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the surfaces\n");
        પાછા AVERROR_UNKNOWN;
    }

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(કદ(*s->surfaces_internal),
                             ctx, dxva2_pool_alloc, ખાલી);
    જો (!ffhwframesctx(ctx)->pool_internal)
        પાછા AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    પાછા 0;
}

સ્થિર પૂર્ણાંક dxva2_frames_init(AVHWFramesContext *ctx)
{
    DXVA2FramesContext       *s = ctx->hwctx;
    AVDXVA2FramesContext *hwctx = &s->p;
    પૂર્ણાંક ret;

    જો (hwctx->surface_type != DXVA2_VideoDecoderRenderTarget &&
        hwctx->surface_type != DXVA2_VideoProcessorRenderTarget) {
        av_log(ctx, AV_LOG_ERROR, "Unknown surface type: %lu\n",
               hwctx->surface_type);
        પાછા AVERROR(EINVAL);
    }

    s->device_handle = INVALID_HANDLE_કિંમત;

    /* init the frame pool if the caller didn't provide one */
    જો (!ctx->pool) {
        ret = dxva2_init_pool(ctx);
        જો (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            પાછા ret;
        }
    }

    પાછા 0;
}

સ્થિર પૂર્ણાંક dxva2_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    જો (!frame->buf[0])
        પાછા AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_DXVA2_VLD;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    પાછા 0;
}

સ્થિર પૂર્ણાંક dxva2_transfer_get_formats(AVHWFramesContext *ctx,
                                      ગણના AVHWFrameTransferDirection dir,
                                      ગણના AVPixelFormat **formats)
{
    ગણના AVPixelFormat *fmts;

    fmts = av_malloc_array(2, કદ(*fmts));
    જો (!fmts)
        પાછા AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    પાછા 0;
}

સ્થિર શૂન્ય dxva2_unmap_frame(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)hwmap->source->data[3];
    IDirect3DSurface9_UnlockRect(surface);
    av_freep(&hwmap->priv);
}

સ્થિર પૂર્ણાંક dxva2_map_frame(AVHWFramesContext *ctx, AVFrame *dst, અચલ AVFrame *src,
                           પૂર્ણાંક flags)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->data[3];
    DXVA2Mapping      *map;
    D3DSURFACE_DESC    surfaceDesc;
    D3DLOCKED_RECT     LockedRect;
    HRESULT            hr;
    પૂર્ણાંક i, err, nb_planes;
    પૂર્ણાંક lock_flags = 0;

    nb_planes = av_pix_fmt_ગણતરી_planes(dst->format);

    hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);
    જો (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");
        પાછા AVERROR_UNKNOWN;
    }

    જો (!(flags & AV_HWFRAME_MAP_WRITE))
        lock_flags |= D3DLOCK_READONLY;
    જો (flags & AV_HWFRAME_MAP_OVERWRITE)
        lock_flags |= D3DLOCK_DISCARD;

    hr = IDirect3DSurface9_LockRect(surface, &LockedRect, ખાલી, lock_flags);
    જો (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");
        પાછા AVERROR_UNKNOWN;
    }

    map = av_mallocz(કદ(*map));
    જો (!map) {
        err = AVERROR(ENOMEM);
        જાઓ fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                dxva2_unmap_frame, map);
    જો (err < 0) {
        av_freep(&map);
        જાઓ fail;
    }

    માટે (i = 0; i < nb_planes; i++)
        dst->linesize[i] = LockedRect.Pitch;

    av_image_fill_pointers(dst->data, dst->format, surfaceDesc.Height,
                           (uint8_t*)LockedRect.pBits, dst->linesize);

    જો (dst->format == AV_PIX_FMT_PAL8)
        dst->data[1] = (uint8_t*)map->palette_dummy;

    પાછા 0;
fail:
    IDirect3DSurface9_UnlockRect(surface);
    પાછા err;
}

સ્થિર પૂર્ણાંક dxva2_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  અચલ AVFrame *src)
{
    AVFrame *map;
    પૂર્ણાંક ret;

    જો (src->format != ctx->sw_format)
        પાછા AVERROR(ENOSYS);

    map = av_frame_alloc();
    જો (!map)
        પાછા AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    જો (ret < 0)
        જાઓ fail;

    av_image_copy2(map->data, map->linesize, src->data, src->linesize,
                   ctx->sw_format, src->width, src->height);

fail:
    av_frame_free(&map);
    પાછા ret;
}

સ્થિર પૂર્ણાંક dxva2_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    અચલ AVFrame *src)
{
    AVFrame *map;
    ptrdiff_t src_linesize[4], dst_linesize[4];
    પૂર્ણાંક ret, i;

    જો (dst->format != ctx->sw_format)
        પાછા AVERROR(ENOSYS);

    map = av_frame_alloc();
    જો (!map)
        પાછા AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, src, AV_HWFRAME_MAP_READ);
    જો (ret < 0)
        જાઓ fail;

    માટે (i = 0; i < 4; i++) {
        dst_linesize[i] = dst->linesize[i];
        src_linesize[i] = map->linesize[i];
    }
    av_image_copy_uc_from(dst->data, dst_linesize, (અચલ uint8_t **)map->data, src_linesize,
                          ctx->sw_format, src->width, src->height);
fail:
    av_frame_free(&map);
    પાછા ret;
}

સ્થિર પૂર્ણાંક dxva2_map_from(AVHWFramesContext *ctx,
                          AVFrame *dst, અચલ AVFrame *src, પૂર્ણાંક flags)
{
    પૂર્ણાંક err;

    જો (dst->format != AV_PIX_FMT_NONE && dst->format != ctx->sw_format)
        પાછા AVERROR(ENOSYS);
    dst->format = ctx->sw_format;

    err = dxva2_map_frame(ctx, dst, src, flags);
    જો (err < 0)
        પાછા err;

    err = av_frame_copy_props(dst, src);
    જો (err < 0)
        પાછા err;

    પાછા 0;
}

સ્થિર શૂન્ય dxva2_device_free(AVHWDeviceContext *ctx)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv       *priv = ctx->user_opaque;

    જો (hwctx->devmgr && priv->device_handle != INVALID_HANDLE_કિંમત)
        IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, priv->device_handle);

    જો (hwctx->devmgr)
        IDirect3DDeviceManager9_Release(hwctx->devmgr);

    જો (priv->d3d9device)
        IDirect3DDevice9_Release(priv->d3d9device);

    જો (priv->d3d9)
        IDirect3D9_Release(priv->d3d9);

    જો (priv->d3dlib)
        dlclose(priv->d3dlib);

    જો (priv->dxva2lib)
        dlclose(priv->dxva2lib);

    av_freep(&ctx->user_opaque);
}

સ્થિર પૂર્ણાંક dxva2_device_create9(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODE d3ddm;
    HRESULT hr;
    pDirect3DCreate9 *createD3D = (pDirect3DCreate9 *)dlsym(priv->d3dlib, "Direct3DCreate9");
    જો (!createD3D) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate Direct3DCreate9\n");
        પાછા AVERROR_UNKNOWN;
    }

    priv->d3d9 = createD3D(D3D_SDK_VERSION);
    જો (!priv->d3d9) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create IDirect3D object\n");
        પાછા AVERROR_UNKNOWN;
    }

    IDirect3D9_GetAdapterDisplayMode(priv->d3d9, adapter, &d3ddm);

    d3dpp.BackBufferFormat = d3ddm.Format;

    hr = IDirect3D9_CreateDevice(priv->d3d9, adapter, D3DDEVTYPE_HAL, GetDesktopWindow(),
                                 FF_D3DCREATE_FLAGS,
                                 &d3dpp, &priv->d3d9device);
    જો (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device\n");
        પાછા AVERROR_UNKNOWN;
    }

    પાછા 0;
}

સ્થિર પૂર્ણાંક dxva2_device_create9ex(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODEEX modeex = {0};
    IDirect3D9Ex *d3d9ex = ખાલી;
    IDirect3DDevice9Ex *exdev = ખાલી;
    HRESULT hr;
    pDirect3DCreate9Ex *createD3DEx = (pDirect3DCreate9Ex *)dlsym(priv->d3dlib, "Direct3DCreate9Ex");
    જો (!createD3DEx)
        પાછા AVERROR(ENOSYS);

    hr = createD3DEx(D3D_SDK_VERSION, &d3d9ex);
    જો (FAILED(hr))
        પાછા AVERROR_UNKNOWN;

    modeex.Size = કદ(D3DDISPLAYMODEEX);
    hr = IDirect3D9Ex_GetAdapterDisplayModeEx(d3d9ex, adapter, &modeex, ખાલી);
    જો (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        પાછા AVERROR_UNKNOWN;
    }

    d3dpp.BackBufferFormat = modeex.Format;

    hr = IDirect3D9Ex_CreateDeviceEx(d3d9ex, adapter, D3DDEVTYPE_HAL, GetDesktopWindow(),
                                     FF_D3DCREATE_FLAGS,
                                     &d3dpp, ખાલી, &exdev);
    જો (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        પાછા AVERROR_UNKNOWN;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Using D3D9Ex device.\n");
    priv->d3d9 = (IDirect3D9 *)d3d9ex;
    priv->d3d9device = (IDirect3DDevice9 *)exdev;
    પાછા 0;
}

સ્થિર પૂર્ણાંક dxva2_device_create(AVHWDeviceContext *ctx, અચલ અક્ષર *device,
                               AVDictionary *opts, પૂર્ણાંક flags)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv *priv;
    pCreateDeviceManager9 *createDeviceManager = ખાલી;
    unsigned resetToken = 0;
    UINT adapter = D3DADAPTER_DEFAULT;
    HRESULT hr;
    પૂર્ણાંક err;

    જો (device)
        adapter = atoi(device);

    priv = av_mallocz(કદ(*priv));
    જો (!priv)
        પાછા AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->મુક્ત        = dxva2_device_free;

    priv->device_handle = INVALID_HANDLE_કિંમત;

    priv->d3dlib = dlopen("d3d9.dll", 0);
    જો (!priv->d3dlib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D9 library\n");
        પાછા AVERROR_UNKNOWN;
    }
    priv->dxva2lib = dlopen("dxva2.dll", 0);
    જો (!priv->dxva2lib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load DXVA2 library\n");
        પાછા AVERROR_UNKNOWN;
    }

    createDeviceManager = (pCreateDeviceManager9 *)dlsym(priv->dxva2lib,
                                                         "DXVA2CreateDirect3DDeviceManager9");
    જો (!createDeviceManager) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate DXVA2CreateDirect3DDeviceManager9\n");
        પાછા AVERROR_UNKNOWN;
    }

    જો (dxva2_device_create9ex(ctx, adapter) < 0) {
        // Retry with "classic" d3d9
        err = dxva2_device_create9(ctx, adapter);
        જો (err < 0)
            પાછા err;
    }

    hr = createDeviceManager(&resetToken, &hwctx->devmgr);
    જો (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device manager\n");
        પાછા AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_ResetDevice(hwctx->devmgr, priv->d3d9device, resetToken);
    જો (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind Direct3D device to device manager\n");
        પાછા AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &priv->device_handle);
    જો (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        પાછા AVERROR_UNKNOWN;
    }

    પાછા 0;
}

અચલ HWContextType ff_hwcontext_type_dxva2 = {
    .type                 = AV_HWDEVICE_TYPE_DXVA2,
    .name                 = "DXVA2",

    .device_hwctx_size    = કદ(AVDXVA2DeviceContext),
    .frames_hwctx_size    = કદ(DXVA2FramesContext),

    .device_create        = dxva2_device_create,
    .frames_init          = dxva2_frames_init,
    .frames_uninit        = dxva2_frames_uninit,
    .frames_get_buffer    = dxva2_get_buffer,
    .transfer_get_formats = dxva2_transfer_get_formats,
    .transfer_data_to     = dxva2_transfer_data_to,
    .transfer_data_from   = dxva2_transfer_data_from,
    .map_from             = dxva2_map_from,

    .pix_fmts             = (અચલ ગણના AVPixelFormat[]){ AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_NONE },
};
