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

#ضمن <windows.h>

#تعریف_کن DXVA2API_USE_BITFIELDS
#تعریف_کن COBJMACROS

#ضمن <d3d9.h>
#ضمن <dxva2api.h>
#ضمن <initguid.h>

#ضمن "avassert.h"
#ضمن "common.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_dxva2.h"
#ضمن "hwcontext_internal.h"
#ضمن "imgutils.h"
#ضمن "mem.h"
#ضمن "pixdesc.h"
#ضمن "pixfmt.h"
#ضمن "compat/w32dlfcn.h"

تعريفنوع IDirect3D9* WINAPI pDirect3DCreate9(UINT);
تعريفنوع HRESULT WINAPI pDirect3DCreate9Ex(UINT, IDirect3D9Ex **);
تعريفنوع HRESULT WINAPI pCreateDeviceManager9(UINT *, IDirect3DDeviceManager9 **);

#تعریف_کن FF_D3DCREATE_FLAGS (D3DCREATE_SOFTWARE_VERTEXPROCESSING | \
                            D3DCREATE_MULTITHREADED | \
                            D3DCREATE_FPU_PRESERVE)

ساكن ثابت D3DPRESENT_PARAMETERS dxva2_present_params = {
    .Windowed         = TRUE,
    .پشت_میانگیر_عرض  = 640,
    .پشت_میانگیر_ارتفاع = 480,
    .پشت_میانگیر_شمار  = 0,
    .جابجا_Effect       = D3DSWAPEFFECT_DISCARD,
    .Flags            = D3DPRESENTFLAG_VIDEO,
};

تعريفنوع بنية DXVA2Mapping {
    uint32_t palette_dummy[256];
} DXVA2Mapping;

تعريفنوع بنية DXVA2_قابها_Context {
    /**
     * The public AVDXVA2FramesContext. See hwcontext_dxva2.h for it.
     */
    AVDXVA2_قابها_Context p;

    IDirect3DSurface9 **surfaces_داخلی;
    صحيح              nb_surfaces_استفاده_شده;

    HANDLE  device_handle;
    IDirectXVideoAccelerationService *service;

    D3DFORMAT format;
} DXVA2_قابها_Context;

تعريفنوع بنية DXVA2DevicePriv {
    HMODULE d3dlib;
    HMODULE dxva2lib;

    HANDLE device_handle;

    IDirect3D9       *d3d9;
    IDirect3DDevice9 *d3d9device;
} DXVA2DevicePriv;

ساكن ثابت بنية {
    D3DFORMAT d3d_format;
    تعداد AVPixelFormat pix_fmt;
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

ساكن فراغ dxva2_قابها_uninit(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2_قابها_Context              *s = ctx->hwctx;
    AVDXVA2_قابها_Context *قابها_hwctx = &s->p;
    صحيح i;

    إذا (قابها_hwctx->decoder_مقصد_release)
        IDirectXVideoDecoder_Release(قابها_hwctx->decoder_مقصد_release);

    إذا (s->surfaces_داخلی) {
        لكل (i = 0; i < قابها_hwctx->nb_surfaces; i++) {
            إذا (s->surfaces_داخلی[i])
                IDirect3DSurface9_Release(s->surfaces_داخلی[i]);
        }
    }
    av_freep(&s->surfaces_داخلی);

    إذا (s->service) {
        IDirectXVideoAccelerationService_Release(s->service);
        s->service = عدم;
    }

    إذا (s->device_handle != INVALID_HANDLE_مقدار) {
        IDirect3DDeviceManager9_CloseDeviceHandle(device_hwctx->devmgr, s->device_handle);
        s->device_handle = INVALID_HANDLE_مقدار;
    }
}

ساكن فراغ dxva2_pool_release_dummy(فراغ *opaque, uint8_t *داده)
{
    // important not to free anything here--data is a surface object
    // associated with the call to CreateSurface(), and these surfaces are
    // released in dxva2_frames_uninit()
}

ساكن AVBufferRef *dxva2_pool_alloc(فراغ *opaque, size_t اندازه)
{
    AVHWFramesContext      *ctx = (AVHWFramesContext*)opaque;
    DXVA2_قابها_Context       *s = ctx->hwctx;
    AVDXVA2_قابها_Context *hwctx = &s->p;

    إذا (s->nb_surfaces_استفاده_شده < hwctx->nb_surfaces) {
        s->nb_surfaces_استفاده_شده++;
        أرجع av_میانگیر_create((uint8_t*)s->surfaces_داخلی[s->nb_surfaces_استفاده_شده - 1],
                                حجم(**hwctx->surfaces), dxva2_pool_release_dummy, 0, 0);
    }

    أرجع عدم;
}

ساكن صحيح dxva2_init_pool(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2_قابها_Context              *s = ctx->hwctx;
    AVDXVA2_قابها_Context *قابها_hwctx = &s->p;
    صحيح decode = (قابها_hwctx->surface_type == DXVA2_Video_Decoder_Render_هدف);

    صحيح i;
    HRESULT hr;

    إذا (ctx->initial_pool_اندازه <= 0)
        أرجع 0;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(device_hwctx->devmgr, &s->device_handle);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        أرجع AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_GetVideoService(device_hwctx->devmgr,
                                                 s->device_handle,
                                                 decode ? &video_decoder_service : &video_processor_service,
                                                 (فراغ **)&s->service);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create the video service\n");
        أرجع AVERROR_UNKNOWN;
    }

    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        إذا (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            اكسر;
        }
    }
    إذا (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        أرجع AVERROR(EINVAL);
    }

    s->surfaces_داخلی = av_calloc(ctx->initial_pool_اندازه,
                                     حجم(*s->surfaces_داخلی));
    إذا (!s->surfaces_داخلی)
        أرجع AVERROR(ENOMEM);

    hr = IDirectXVideoAccelerationService_CreateSurface(s->service,
                                                        ctx->عرض, ctx->ارتفاع,
                                                        ctx->initial_pool_اندازه - 1,
                                                        s->format, D3DPOOL_DEFAULT, 0,
                                                        قابها_hwctx->surface_type,
                                                        s->surfaces_داخلی, عدم);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the surfaces\n");
        أرجع AVERROR_UNKNOWN;
    }

    ffhwframesctx(ctx)->pool_داخلی =
        av_میانگیر_pool_init2(حجم(*s->surfaces_داخلی),
                             ctx, dxva2_pool_alloc, عدم);
    إذا (!ffhwframesctx(ctx)->pool_داخلی)
        أرجع AVERROR(ENOMEM);

    قابها_hwctx->surfaces    = s->surfaces_داخلی;
    قابها_hwctx->nb_surfaces = ctx->initial_pool_اندازه;

    أرجع 0;
}

ساكن صحيح dxva2_قابها_init(AVHWFramesContext *ctx)
{
    DXVA2_قابها_Context       *s = ctx->hwctx;
    AVDXVA2_قابها_Context *hwctx = &s->p;
    صحيح ret;

    إذا (hwctx->surface_type != DXVA2_Video_Decoder_Render_هدف &&
        hwctx->surface_type != DXVA2_Video_Processor_Render_هدف) {
        av_log(ctx, AV_LOG_ERROR, "Unknown surface type: %lu\n",
               hwctx->surface_type);
        أرجع AVERROR(EINVAL);
    }

    s->device_handle = INVALID_HANDLE_مقدار;

    /* init the frame pool if the caller didn't provide one */
    إذا (!ctx->pool) {
        ret = dxva2_init_pool(ctx);
        إذا (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            أرجع ret;
        }
    }

    أرجع 0;
}

ساكن صحيح dxva2_get_میانگیر(AVHWFramesContext *ctx, AVFrame *قاب)
{
    قاب->buf[0] = av_میانگیر_pool_get(ctx->pool);
    إذا (!قاب->buf[0])
        أرجع AVERROR(ENOMEM);

    قاب->داده[3] = قاب->buf[0]->داده;
    قاب->format  = AV_PIX_FMT_DXVA2_VLD;
    قاب->عرض   = ctx->عرض;
    قاب->ارتفاع  = ctx->ارتفاع;

    أرجع 0;
}

ساكن صحيح dxva2_transfer_get_formats(AVHWFramesContext *ctx,
                                      تعداد AVHWFrameTransferDirection dir,
                                      تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    إذا (!fmts)
        أرجع AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    أرجع 0;
}

ساكن فراغ dxva2_unmap_قاب(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)hwmap->منبع->داده[3];
    IDirect3DSurface9_UnlockRect(surface);
    av_freep(&hwmap->priv);
}

ساكن صحيح dxva2_map_قاب(AVHWFramesContext *ctx, AVFrame *dst, ثابت AVFrame *src,
                           صحيح flags)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->داده[3];
    DXVA2Mapping      *map;
    D3DSURFACE_DESC    surfaceDesc;
    D3DLOCKED_RECT     LockedRect;
    HRESULT            hr;
    صحيح i, err, nb_planes;
    صحيح قفل_flags = 0;

    nb_planes = av_pix_fmt_شمار_planes(dst->format);

    hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");
        أرجع AVERROR_UNKNOWN;
    }

    إذا (!(flags & AV_HWFRAME_MAP_WRITE))
        قفل_flags |= D3DLOCK_READONLY;
    إذا (flags & AV_HWFRAME_MAP_OVERWRITE)
        قفل_flags |= D3DLOCK_DISCARD;

    hr = IDirect3_DSurface9_قفل_Rect(surface, &LockedRect, عدم, قفل_flags);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");
        أرجع AVERROR_UNKNOWN;
    }

    map = av_mallocz(حجم(*map));
    إذا (!map) {
        err = AVERROR(ENOMEM);
        اذهب fail;
    }

    err = ff_hwframe_map_create(src->hw_قابها_ctx, dst, src,
                                dxva2_unmap_قاب, map);
    إذا (err < 0) {
        av_freep(&map);
        اذهب fail;
    }

    لكل (i = 0; i < nb_planes; i++)
        dst->linesize[i] = LockedRect.Pitch;

    av_image_fill_اشارهگرها(dst->داده, dst->format, surfaceDesc.ارتفاع_2,
                           (uint8_t*)LockedRect.p_بیتها, dst->linesize);

    إذا (dst->format == AV_PIX_FMT_PAL8)
        dst->داده[1] = (uint8_t*)map->palette_dummy;

    أرجع 0;
fail:
    IDirect3DSurface9_UnlockRect(surface);
    أرجع err;
}

ساكن صحيح dxva2_transfer_داده_مقصد(AVHWFramesContext *ctx, AVFrame *dst,
                                  ثابت AVFrame *src)
{
    AVFrame *map;
    صحيح ret;

    إذا (src->format != ctx->sw_format)
        أرجع AVERROR(ENOSYS);

    map = av_قاب_alloc();
    إذا (!map)
        أرجع AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_قاب(ctx, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    إذا (ret < 0)
        اذهب fail;

    av_image_copy2(map->داده, map->linesize, src->داده, src->linesize,
                   ctx->sw_format, src->عرض, src->ارتفاع);

fail:
    av_قاب_free(&map);
    أرجع ret;
}

ساكن صحيح dxva2_transfer_داده_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ثابت AVFrame *src)
{
    AVFrame *map;
    ptrdiff_t src_linesize[4], dst_linesize[4];
    صحيح ret, i;

    إذا (dst->format != ctx->sw_format)
        أرجع AVERROR(ENOSYS);

    map = av_قاب_alloc();
    إذا (!map)
        أرجع AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_قاب(ctx, map, src, AV_HWFRAME_MAP_READ);
    إذا (ret < 0)
        اذهب fail;

    لكل (i = 0; i < 4; i++) {
        dst_linesize[i] = dst->linesize[i];
        src_linesize[i] = map->linesize[i];
    }
    av_image_copy_uc_from(dst->داده, dst_linesize, (ثابت uint8_t **)map->داده, src_linesize,
                          ctx->sw_format, src->عرض, src->ارتفاع);
fail:
    av_قاب_free(&map);
    أرجع ret;
}

ساكن صحيح dxva2_map_from(AVHWFramesContext *ctx,
                          AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    صحيح err;

    إذا (dst->format != AV_PIX_FMT_NONE && dst->format != ctx->sw_format)
        أرجع AVERROR(ENOSYS);
    dst->format = ctx->sw_format;

    err = dxva2_map_قاب(ctx, dst, src, flags);
    إذا (err < 0)
        أرجع err;

    err = av_قاب_copy_props(dst, src);
    إذا (err < 0)
        أرجع err;

    أرجع 0;
}

ساكن فراغ dxva2_device_free(AVHWDeviceContext *ctx)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv       *priv = ctx->user_opaque;

    إذا (hwctx->devmgr && priv->device_handle != INVALID_HANDLE_مقدار)
        IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, priv->device_handle);

    إذا (hwctx->devmgr)
        IDirect3DDeviceManager9_Release(hwctx->devmgr);

    إذا (priv->d3d9device)
        IDirect3DDevice9_Release(priv->d3d9device);

    إذا (priv->d3d9)
        IDirect3D9_Release(priv->d3d9);

    إذا (priv->d3dlib)
        dlclose(priv->d3dlib);

    إذا (priv->dxva2lib)
        dlclose(priv->dxva2lib);

    av_freep(&ctx->user_opaque);
}

ساكن صحيح dxva2_device_create9(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODE d3ddm;
    HRESULT hr;
    pDirect3DCreate9 *createD3D = (pDirect3DCreate9 *)dlsym(priv->d3dlib, "Direct3DCreate9");
    إذا (!createD3D) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate Direct3DCreate9\n");
        أرجع AVERROR_UNKNOWN;
    }

    priv->d3d9 = createD3D(D3_D_SDK_نسخه);
    إذا (!priv->d3d9) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create IDirect3D object\n");
        أرجع AVERROR_UNKNOWN;
    }

    IDirect3_D9_Get_Adapter_Display_نما(priv->d3d9, adapter, &d3ddm);

    d3dpp.پشت_میانگیر_Format = d3ddm.Format;

    hr = IDirect3D9_CreateDevice(priv->d3d9, adapter, D3DDEVTYPE_HAL, Get_Desktop_پنجره(),
                                 FF_D3DCREATE_FLAGS,
                                 &d3dpp, &priv->d3d9device);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device\n");
        أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}

ساكن صحيح dxva2_device_create9ex(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODEEX modeex = {0};
    IDirect3D9Ex *d3d9ex = عدم;
    IDirect3DDevice9Ex *exdev = عدم;
    HRESULT hr;
    pDirect3DCreate9Ex *createD3DEx = (pDirect3DCreate9Ex *)dlsym(priv->d3dlib, "Direct3DCreate9Ex");
    إذا (!createD3DEx)
        أرجع AVERROR(ENOSYS);

    hr = createD3DEx(D3_D_SDK_نسخه, &d3d9ex);
    إذا (FAILED(hr))
        أرجع AVERROR_UNKNOWN;

    modeex.اندازه_3 = حجم(D3DDISPLAYMODEEX);
    hr = IDirect3_D9_Ex_Get_Adapter_Display_نما_Ex(d3d9ex, adapter, &modeex, عدم);
    إذا (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        أرجع AVERROR_UNKNOWN;
    }

    d3dpp.پشت_میانگیر_Format = modeex.Format;

    hr = IDirect3D9Ex_CreateDeviceEx(d3d9ex, adapter, D3DDEVTYPE_HAL, Get_Desktop_پنجره(),
                                     FF_D3DCREATE_FLAGS,
                                     &d3dpp, عدم, &exdev);
    إذا (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        أرجع AVERROR_UNKNOWN;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Using D3D9Ex device.\n");
    priv->d3d9 = (IDirect3D9 *)d3d9ex;
    priv->d3d9device = (IDirect3DDevice9 *)exdev;
    أرجع 0;
}

ساكن صحيح dxva2_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                               AVDictionary *opts, صحيح flags)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv *priv;
    pCreateDeviceManager9 *createDeviceManager = عدم;
    بیعلامت resetToken = 0;
    UINT adapter = D3DADAPTER_DEFAULT;
    HRESULT hr;
    صحيح err;

    إذا (device)
        adapter = atoi(device);

    priv = av_mallocz(حجم(*priv));
    إذا (!priv)
        أرجع AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->حرر        = dxva2_device_free;

    priv->device_handle = INVALID_HANDLE_مقدار;

    priv->d3dlib = dlopen("d3d9.dll", 0);
    إذا (!priv->d3dlib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D9 library\n");
        أرجع AVERROR_UNKNOWN;
    }
    priv->dxva2lib = dlopen("dxva2.dll", 0);
    إذا (!priv->dxva2lib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load DXVA2 library\n");
        أرجع AVERROR_UNKNOWN;
    }

    createDeviceManager = (pCreateDeviceManager9 *)dlsym(priv->dxva2lib,
                                                         "DXVA2CreateDirect3DDeviceManager9");
    إذا (!createDeviceManager) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate DXVA2CreateDirect3DDeviceManager9\n");
        أرجع AVERROR_UNKNOWN;
    }

    إذا (dxva2_device_create9ex(ctx, adapter) < 0) {
        // Retry with "classic" d3d9
        err = dxva2_device_create9(ctx, adapter);
        إذا (err < 0)
            أرجع err;
    }

    hr = createDeviceManager(&resetToken, &hwctx->devmgr);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device manager\n");
        أرجع AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_ResetDevice(hwctx->devmgr, priv->d3d9device, resetToken);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind Direct3D device to device manager\n");
        أرجع AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &priv->device_handle);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}

ثابت HWContextType ff_hwcontext_type_dxva2 = {
    .type                 = AV_HWDEVICE_TYPE_DXVA2,
    .name                 = "DXVA2",

    .device_hwctx_اندازه    = حجم(AVDXVA2DeviceContext),
    .قابها_hwctx_اندازه    = حجم(DXVA2_قابها_Context),

    .device_create        = dxva2_device_create,
    .قابها_init          = dxva2_قابها_init,
    .قابها_uninit        = dxva2_قابها_uninit,
    .قابها_get_میانگیر    = dxva2_get_میانگیر,
    .transfer_get_formats = dxva2_transfer_get_formats,
    .transfer_داده_مقصد     = dxva2_transfer_داده_مقصد,
    .transfer_داده_from   = dxva2_transfer_داده_from,
    .map_from             = dxva2_map_from,

    .pix_fmts             = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_NONE },
};
