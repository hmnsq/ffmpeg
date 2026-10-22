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

#شامل <windows.h>

#define DXVA2API_USE_BITFIELDS
#define COBJMACROS

#شامل <d3d9.h>
#شامل <dxva2api.h>
#شامل <initguid.h>

#شامل "avassert.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_dxva2.h"
#شامل "hwcontext_internal.h"
#شامل "imgutils.h"
#شامل "mem.h"
#شامل "pixdesc.h"
#شامل "pixfmt.h"
#شامل "compat/w32dlfcn.h"

تعریفنوع IDirect3D9* WINAPI pDirect3DCreate9(UINT);
تعریفنوع HRESULT WINAPI pDirect3DCreate9Ex(UINT, IDirect3D9Ex **);
تعریفنوع HRESULT WINAPI pCreateDeviceManager9(UINT *, IDirect3DDeviceManager9 **);

#define FF_D3DCREATE_FLAGS (D3DCREATE_SOFTWARE_VERTEXPROCESSING | \
                            D3DCREATE_MULTITHREADED | \
                            D3DCREATE_FPU_PRESERVE)

ایستا ثابت D3DPRESENT_PARAMETERS dxva2_present_params = {
    .Windowed         = TRUE,
    .BackBufferWidth  = 640,
    .BackBufferHeight = 480,
    .Back_Buffer_شمار  = 0,
    .SwapEffect       = D3DSWAPEFFECT_DISCARD,
    .Flags            = D3DPRESENTFLAG_VIDEO,
};

تعریفنوع ساختار DXVA2Mapping {
    uint32_t palette_dummy[256];
} DXVA2Mapping;

تعریفنوع ساختار DXVA2FramesContext {
    /**
     * The public AVDXVA2FramesContext. See hwcontext_dxva2.h for it.
     */
    AVDXVA2FramesContext p;

    IDirect3DSurface9 **surfaces_internal;
    صحیح              nb_surfaces_used;

    HANDLE  device_handle;
    IDirectXVideoAccelerationService *service;

    D3DFORMAT format;
} DXVA2FramesContext;

تعریفنوع ساختار DXVA2DevicePriv {
    HMODULE d3dlib;
    HMODULE dxva2lib;

    HANDLE device_handle;

    IDirect3D9       *d3d9;
    IDirect3DDevice9 *d3d9device;
} DXVA2DevicePriv;

ایستا ثابت ساختار {
    D3DFORMAT d3d_format;
    شمارش AVPixelFormat pix_fmt;
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

ایستا تهی dxva2_frames_uninit(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2FramesContext              *s = ctx->hwctx;
    AVDXVA2FramesContext *frames_hwctx = &s->p;
    صحیح i;

    اگر (frames_hwctx->decoder_to_release)
        IDirectXVideoDecoder_Release(frames_hwctx->decoder_to_release);

    اگر (s->surfaces_internal) {
        برای (i = 0; i < frames_hwctx->nb_surfaces; i++) {
            اگر (s->surfaces_internal[i])
                IDirect3DSurface9_Release(s->surfaces_internal[i]);
        }
    }
    av_freep(&s->surfaces_internal);

    اگر (s->service) {
        IDirectXVideoAccelerationService_Release(s->service);
        s->service = پوچ;
    }

    اگر (s->device_handle != INVALID_HANDLE_مقدار) {
        IDirect3DDeviceManager9_CloseDeviceHandle(device_hwctx->devmgr, s->device_handle);
        s->device_handle = INVALID_HANDLE_مقدار;
    }
}

ایستا تهی dxva2_pool_release_dummy(تهی *opaque, uint8_t *data)
{
    // important not to free anything here--data is a surface object
    // associated with the call to CreateSurface(), and these surfaces are
    // released in dxva2_frames_uninit()
}

ایستا AVBufferRef *dxva2_pool_alloc(تهی *opaque, size_t size)
{
    AVHWFramesContext      *ctx = (AVHWFramesContext*)opaque;
    DXVA2FramesContext       *s = ctx->hwctx;
    AVDXVA2FramesContext *hwctx = &s->p;

    اگر (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        بازگشت av_buffer_create((uint8_t*)s->surfaces_internal[s->nb_surfaces_used - 1],
                                اندازه(**hwctx->surfaces), dxva2_pool_release_dummy, 0, 0);
    }

    بازگشت پوچ;
}

ایستا صحیح dxva2_init_pool(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2FramesContext              *s = ctx->hwctx;
    AVDXVA2FramesContext *frames_hwctx = &s->p;
    صحیح decode = (frames_hwctx->surface_type == DXVA2_VideoDecoderRenderTarget);

    صحیح i;
    HRESULT hr;

    اگر (ctx->initial_pool_size <= 0)
        بازگشت 0;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(device_hwctx->devmgr, &s->device_handle);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        بازگشت AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_GetVideoService(device_hwctx->devmgr,
                                                 s->device_handle,
                                                 decode ? &video_decoder_service : &video_processor_service,
                                                 (تهی **)&s->service);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create the video service\n");
        بازگشت AVERROR_UNKNOWN;
    }

    برای (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        اگر (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            بشکن;
        }
    }
    اگر (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        بازگشت AVERROR(EINVAL);
    }

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     اندازه(*s->surfaces_internal));
    اگر (!s->surfaces_internal)
        بازگشت AVERROR(ENOMEM);

    hr = IDirectXVideoAccelerationService_CreateSurface(s->service,
                                                        ctx->width, ctx->height,
                                                        ctx->initial_pool_size - 1,
                                                        s->format, D3DPOOL_DEFAULT, 0,
                                                        frames_hwctx->surface_type,
                                                        s->surfaces_internal, پوچ);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the surfaces\n");
        بازگشت AVERROR_UNKNOWN;
    }

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(اندازه(*s->surfaces_internal),
                             ctx, dxva2_pool_alloc, پوچ);
    اگر (!ffhwframesctx(ctx)->pool_internal)
        بازگشت AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    بازگشت 0;
}

ایستا صحیح dxva2_frames_init(AVHWFramesContext *ctx)
{
    DXVA2FramesContext       *s = ctx->hwctx;
    AVDXVA2FramesContext *hwctx = &s->p;
    صحیح ret;

    اگر (hwctx->surface_type != DXVA2_VideoDecoderRenderTarget &&
        hwctx->surface_type != DXVA2_VideoProcessorRenderTarget) {
        av_log(ctx, AV_LOG_ERROR, "Unknown surface type: %lu\n",
               hwctx->surface_type);
        بازگشت AVERROR(EINVAL);
    }

    s->device_handle = INVALID_HANDLE_مقدار;

    /* init the frame pool if the caller didn't provide one */
    اگر (!ctx->pool) {
        ret = dxva2_init_pool(ctx);
        اگر (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            بازگشت ret;
        }
    }

    بازگشت 0;
}

ایستا صحیح dxva2_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    اگر (!frame->buf[0])
        بازگشت AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_DXVA2_VLD;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    بازگشت 0;
}

ایستا صحیح dxva2_transfer_get_formats(AVHWFramesContext *ctx,
                                      شمارش AVHWFrameTransferDirection dir,
                                      شمارش AVPixelFormat **formats)
{
    شمارش AVPixelFormat *fmts;

    fmts = av_malloc_array(2, اندازه(*fmts));
    اگر (!fmts)
        بازگشت AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    بازگشت 0;
}

ایستا تهی dxva2_unmap_frame(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)hwmap->source->data[3];
    IDirect3DSurface9_UnlockRect(surface);
    av_freep(&hwmap->priv);
}

ایستا صحیح dxva2_map_frame(AVHWFramesContext *ctx, AVFrame *dst, ثابت AVFrame *src,
                           صحیح flags)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->data[3];
    DXVA2Mapping      *map;
    D3DSURFACE_DESC    surfaceDesc;
    D3DLOCKED_RECT     LockedRect;
    HRESULT            hr;
    صحیح i, err, nb_planes;
    صحیح lock_flags = 0;

    nb_planes = av_pix_fmt_شمار_planes(dst->format);

    hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");
        بازگشت AVERROR_UNKNOWN;
    }

    اگر (!(flags & AV_HWFRAME_MAP_WRITE))
        lock_flags |= D3DLOCK_READONLY;
    اگر (flags & AV_HWFRAME_MAP_OVERWRITE)
        lock_flags |= D3DLOCK_DISCARD;

    hr = IDirect3DSurface9_LockRect(surface, &LockedRect, پوچ, lock_flags);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");
        بازگشت AVERROR_UNKNOWN;
    }

    map = av_mallocz(اندازه(*map));
    اگر (!map) {
        err = AVERROR(ENOMEM);
        برو fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                dxva2_unmap_frame, map);
    اگر (err < 0) {
        av_freep(&map);
        برو fail;
    }

    برای (i = 0; i < nb_planes; i++)
        dst->linesize[i] = LockedRect.Pitch;

    av_image_fill_pointers(dst->data, dst->format, surfaceDesc.Height,
                           (uint8_t*)LockedRect.pBits, dst->linesize);

    اگر (dst->format == AV_PIX_FMT_PAL8)
        dst->data[1] = (uint8_t*)map->palette_dummy;

    بازگشت 0;
fail:
    IDirect3DSurface9_UnlockRect(surface);
    بازگشت err;
}

ایستا صحیح dxva2_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح ret;

    اگر (src->format != ctx->sw_format)
        بازگشت AVERROR(ENOSYS);

    map = av_frame_alloc();
    اگر (!map)
        بازگشت AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    اگر (ret < 0)
        برو fail;

    av_image_copy2(map->data, map->linesize, src->data, src->linesize,
                   ctx->sw_format, src->width, src->height);

fail:
    av_frame_free(&map);
    بازگشت ret;
}

ایستا صحیح dxva2_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ثابت AVFrame *src)
{
    AVFrame *map;
    ptrdiff_t src_linesize[4], dst_linesize[4];
    صحیح ret, i;

    اگر (dst->format != ctx->sw_format)
        بازگشت AVERROR(ENOSYS);

    map = av_frame_alloc();
    اگر (!map)
        بازگشت AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, src, AV_HWFRAME_MAP_READ);
    اگر (ret < 0)
        برو fail;

    برای (i = 0; i < 4; i++) {
        dst_linesize[i] = dst->linesize[i];
        src_linesize[i] = map->linesize[i];
    }
    av_image_copy_uc_from(dst->data, dst_linesize, (ثابت uint8_t **)map->data, src_linesize,
                          ctx->sw_format, src->width, src->height);
fail:
    av_frame_free(&map);
    بازگشت ret;
}

ایستا صحیح dxva2_map_from(AVHWFramesContext *ctx,
                          AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    صحیح err;

    اگر (dst->format != AV_PIX_FMT_NONE && dst->format != ctx->sw_format)
        بازگشت AVERROR(ENOSYS);
    dst->format = ctx->sw_format;

    err = dxva2_map_frame(ctx, dst, src, flags);
    اگر (err < 0)
        بازگشت err;

    err = av_frame_copy_props(dst, src);
    اگر (err < 0)
        بازگشت err;

    بازگشت 0;
}

ایستا تهی dxva2_device_free(AVHWDeviceContext *ctx)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv       *priv = ctx->user_opaque;

    اگر (hwctx->devmgr && priv->device_handle != INVALID_HANDLE_مقدار)
        IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, priv->device_handle);

    اگر (hwctx->devmgr)
        IDirect3DDeviceManager9_Release(hwctx->devmgr);

    اگر (priv->d3d9device)
        IDirect3DDevice9_Release(priv->d3d9device);

    اگر (priv->d3d9)
        IDirect3D9_Release(priv->d3d9);

    اگر (priv->d3dlib)
        dlclose(priv->d3dlib);

    اگر (priv->dxva2lib)
        dlclose(priv->dxva2lib);

    av_freep(&ctx->user_opaque);
}

ایستا صحیح dxva2_device_create9(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODE d3ddm;
    HRESULT hr;
    pDirect3DCreate9 *createD3D = (pDirect3DCreate9 *)dlsym(priv->d3dlib, "Direct3DCreate9");
    اگر (!createD3D) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate Direct3DCreate9\n");
        بازگشت AVERROR_UNKNOWN;
    }

    priv->d3d9 = createD3D(D3D_SDK_VERSION);
    اگر (!priv->d3d9) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create IDirect3D object\n");
        بازگشت AVERROR_UNKNOWN;
    }

    IDirect3D9_GetAdapterDisplayMode(priv->d3d9, adapter, &d3ddm);

    d3dpp.BackBufferFormat = d3ddm.Format;

    hr = IDirect3D9_CreateDevice(priv->d3d9, adapter, D3DDEVTYPE_HAL, GetDesktopWindow(),
                                 FF_D3DCREATE_FLAGS,
                                 &d3dpp, &priv->d3d9device);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device\n");
        بازگشت AVERROR_UNKNOWN;
    }

    بازگشت 0;
}

ایستا صحیح dxva2_device_create9ex(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODEEX modeex = {0};
    IDirect3D9Ex *d3d9ex = پوچ;
    IDirect3DDevice9Ex *exdev = پوچ;
    HRESULT hr;
    pDirect3DCreate9Ex *createD3DEx = (pDirect3DCreate9Ex *)dlsym(priv->d3dlib, "Direct3DCreate9Ex");
    اگر (!createD3DEx)
        بازگشت AVERROR(ENOSYS);

    hr = createD3DEx(D3D_SDK_VERSION, &d3d9ex);
    اگر (FAILED(hr))
        بازگشت AVERROR_UNKNOWN;

    modeex.Size = اندازه(D3DDISPLAYMODEEX);
    hr = IDirect3D9Ex_GetAdapterDisplayModeEx(d3d9ex, adapter, &modeex, پوچ);
    اگر (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        بازگشت AVERROR_UNKNOWN;
    }

    d3dpp.BackBufferFormat = modeex.Format;

    hr = IDirect3D9Ex_CreateDeviceEx(d3d9ex, adapter, D3DDEVTYPE_HAL, GetDesktopWindow(),
                                     FF_D3DCREATE_FLAGS,
                                     &d3dpp, پوچ, &exdev);
    اگر (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        بازگشت AVERROR_UNKNOWN;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Using D3D9Ex device.\n");
    priv->d3d9 = (IDirect3D9 *)d3d9ex;
    priv->d3d9device = (IDirect3DDevice9 *)exdev;
    بازگشت 0;
}

ایستا صحیح dxva2_device_create(AVHWDeviceContext *ctx, ثابت نویسه *device,
                               AVDictionary *opts, صحیح flags)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv *priv;
    pCreateDeviceManager9 *createDeviceManager = پوچ;
    unsigned resetToken = 0;
    UINT adapter = D3DADAPTER_DEFAULT;
    HRESULT hr;
    صحیح err;

    اگر (device)
        adapter = atoi(device);

    priv = av_mallocz(اندازه(*priv));
    اگر (!priv)
        بازگشت AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->آزاد        = dxva2_device_free;

    priv->device_handle = INVALID_HANDLE_مقدار;

    priv->d3dlib = dlopen("d3d9.dll", 0);
    اگر (!priv->d3dlib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D9 library\n");
        بازگشت AVERROR_UNKNOWN;
    }
    priv->dxva2lib = dlopen("dxva2.dll", 0);
    اگر (!priv->dxva2lib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load DXVA2 library\n");
        بازگشت AVERROR_UNKNOWN;
    }

    createDeviceManager = (pCreateDeviceManager9 *)dlsym(priv->dxva2lib,
                                                         "DXVA2CreateDirect3DDeviceManager9");
    اگر (!createDeviceManager) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate DXVA2CreateDirect3DDeviceManager9\n");
        بازگشت AVERROR_UNKNOWN;
    }

    اگر (dxva2_device_create9ex(ctx, adapter) < 0) {
        // Retry with "classic" d3d9
        err = dxva2_device_create9(ctx, adapter);
        اگر (err < 0)
            بازگشت err;
    }

    hr = createDeviceManager(&resetToken, &hwctx->devmgr);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device manager\n");
        بازگشت AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_ResetDevice(hwctx->devmgr, priv->d3d9device, resetToken);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind Direct3D device to device manager\n");
        بازگشت AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &priv->device_handle);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        بازگشت AVERROR_UNKNOWN;
    }

    بازگشت 0;
}

ثابت HWContextType ff_hwcontext_type_dxva2 = {
    .type                 = AV_HWDEVICE_TYPE_DXVA2,
    .name                 = "DXVA2",

    .device_hwctx_size    = اندازه(AVDXVA2DeviceContext),
    .frames_hwctx_size    = اندازه(DXVA2FramesContext),

    .device_create        = dxva2_device_create,
    .frames_init          = dxva2_frames_init,
    .frames_uninit        = dxva2_frames_uninit,
    .frames_get_buffer    = dxva2_get_buffer,
    .transfer_get_formats = dxva2_transfer_get_formats,
    .transfer_data_to     = dxva2_transfer_data_to,
    .transfer_data_from   = dxva2_transfer_data_from,
    .map_from             = dxva2_map_from,

    .pix_fmts             = (ثابت شمارش AVPixelFormat[]){ AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_NONE },
};
