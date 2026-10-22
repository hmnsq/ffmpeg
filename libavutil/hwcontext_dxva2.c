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

#अन्तर्भाव <windows.h>

#define DXVA2API_USE_BITFIELDS
#define COBJMACROS

#अन्तर्भाव <d3d9.h>
#अन्तर्भाव <dxva2api.h>
#अन्तर्भाव <initguid.h>

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_dxva2.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "imgutils.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "compat/w32dlfcn.h"

प्रकारव्याख्या IDirect3D9* WINAPI pDirect3DCreate9(UINT);
प्रकारव्याख्या HRESULT WINAPI pDirect3DCreate9Ex(UINT, IDirect3D9Ex **);
प्रकारव्याख्या HRESULT WINAPI pCreateDeviceManager9(UINT *, IDirect3DDeviceManager9 **);

#define FF_D3DCREATE_FLAGS (D3DCREATE_SOFTWARE_VERTEXPROCESSING | \
                            D3DCREATE_MULTITHREADED | \
                            D3DCREATE_FPU_PRESERVE)

स्थिर स्थिरांक D3DPRESENT_PARAMETERS dxva2_present_params = {
    .Windowed         = TRUE,
    .BackBufferWidth  = 640,
    .BackBufferHeight = 480,
    .Back_Buffer_मोजणी  = 0,
    .SwapEffect       = D3DSWAPEFFECT_DISCARD,
    .Flags            = D3DPRESENTFLAG_VIDEO,
};

प्रकारव्याख्या संरचना DXVA2Mapping {
    uint32_t palette_dummy[256];
} DXVA2Mapping;

प्रकारव्याख्या संरचना DXVA2FramesContext {
    /**
     * The public AVDXVA2FramesContext. See hwcontext_dxva2.h for it.
     */
    AVDXVA2FramesContext p;

    IDirect3DSurface9 **surfaces_internal;
    पूर्णांक              nb_surfaces_used;

    HANDLE  device_handle;
    IDirectXVideoAccelerationService *service;

    D3DFORMAT format;
} DXVA2FramesContext;

प्रकारव्याख्या संरचना DXVA2DevicePriv {
    HMODULE d3dlib;
    HMODULE dxva2lib;

    HANDLE device_handle;

    IDirect3D9       *d3d9;
    IDirect3DDevice9 *d3d9device;
} DXVA2DevicePriv;

स्थिर स्थिरांक संरचना {
    D3DFORMAT d3d_format;
    गणना AVPixelFormat pix_fmt;
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

स्थिर शून्य dxva2_frames_uninit(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2FramesContext              *s = ctx->hwctx;
    AVDXVA2FramesContext *frames_hwctx = &s->p;
    पूर्णांक i;

    जर (frames_hwctx->decoder_to_release)
        IDirectXVideoDecoder_Release(frames_hwctx->decoder_to_release);

    जर (s->surfaces_internal) {
        साठी (i = 0; i < frames_hwctx->nb_surfaces; i++) {
            जर (s->surfaces_internal[i])
                IDirect3DSurface9_Release(s->surfaces_internal[i]);
        }
    }
    av_freep(&s->surfaces_internal);

    जर (s->service) {
        IDirectXVideoAccelerationService_Release(s->service);
        s->service = रिक्त;
    }

    जर (s->device_handle != INVALID_HANDLE_मूल्य) {
        IDirect3DDeviceManager9_CloseDeviceHandle(device_hwctx->devmgr, s->device_handle);
        s->device_handle = INVALID_HANDLE_मूल्य;
    }
}

स्थिर शून्य dxva2_pool_release_dummy(शून्य *opaque, uint8_t *data)
{
    // important not to free anything here--data is a surface object
    // associated with the call to CreateSurface(), and these surfaces are
    // released in dxva2_frames_uninit()
}

स्थिर AVBufferRef *dxva2_pool_alloc(शून्य *opaque, माप_प्रकार size)
{
    AVHWFramesContext      *ctx = (AVHWFramesContext*)opaque;
    DXVA2FramesContext       *s = ctx->hwctx;
    AVDXVA2FramesContext *hwctx = &s->p;

    जर (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        परत av_buffer_create((uint8_t*)s->surfaces_internal[s->nb_surfaces_used - 1],
                                आकार(**hwctx->surfaces), dxva2_pool_release_dummy, 0, 0);
    }

    परत रिक्त;
}

स्थिर पूर्णांक dxva2_init_pool(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2FramesContext              *s = ctx->hwctx;
    AVDXVA2FramesContext *frames_hwctx = &s->p;
    पूर्णांक decode = (frames_hwctx->surface_type == DXVA2_VideoDecoderRenderTarget);

    पूर्णांक i;
    HRESULT hr;

    जर (ctx->initial_pool_size <= 0)
        परत 0;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(device_hwctx->devmgr, &s->device_handle);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        परत AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_GetVideoService(device_hwctx->devmgr,
                                                 s->device_handle,
                                                 decode ? &video_decoder_service : &video_processor_service,
                                                 (शून्य **)&s->service);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create the video service\n");
        परत AVERROR_UNKNOWN;
    }

    साठी (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        जर (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            थांबा;
        }
    }
    जर (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        परत AVERROR(EINVAL);
    }

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     आकार(*s->surfaces_internal));
    जर (!s->surfaces_internal)
        परत AVERROR(ENOMEM);

    hr = IDirectXVideoAccelerationService_CreateSurface(s->service,
                                                        ctx->width, ctx->height,
                                                        ctx->initial_pool_size - 1,
                                                        s->format, D3DPOOL_DEFAULT, 0,
                                                        frames_hwctx->surface_type,
                                                        s->surfaces_internal, रिक्त);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the surfaces\n");
        परत AVERROR_UNKNOWN;
    }

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(आकार(*s->surfaces_internal),
                             ctx, dxva2_pool_alloc, रिक्त);
    जर (!ffhwframesctx(ctx)->pool_internal)
        परत AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    परत 0;
}

स्थिर पूर्णांक dxva2_frames_init(AVHWFramesContext *ctx)
{
    DXVA2FramesContext       *s = ctx->hwctx;
    AVDXVA2FramesContext *hwctx = &s->p;
    पूर्णांक ret;

    जर (hwctx->surface_type != DXVA2_VideoDecoderRenderTarget &&
        hwctx->surface_type != DXVA2_VideoProcessorRenderTarget) {
        av_log(ctx, AV_LOG_ERROR, "Unknown surface type: %lu\n",
               hwctx->surface_type);
        परत AVERROR(EINVAL);
    }

    s->device_handle = INVALID_HANDLE_मूल्य;

    /* init the frame pool if the caller didn't provide one */
    जर (!ctx->pool) {
        ret = dxva2_init_pool(ctx);
        जर (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            परत ret;
        }
    }

    परत 0;
}

स्थिर पूर्णांक dxva2_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    जर (!frame->buf[0])
        परत AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_DXVA2_VLD;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    परत 0;
}

स्थिर पूर्णांक dxva2_transfer_get_formats(AVHWFramesContext *ctx,
                                      गणना AVHWFrameTransferDirection dir,
                                      गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts;

    fmts = av_malloc_array(2, आकार(*fmts));
    जर (!fmts)
        परत AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    परत 0;
}

स्थिर शून्य dxva2_unmap_frame(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)hwmap->source->data[3];
    IDirect3DSurface9_UnlockRect(surface);
    av_freep(&hwmap->priv);
}

स्थिर पूर्णांक dxva2_map_frame(AVHWFramesContext *ctx, AVFrame *dst, स्थिरांक AVFrame *src,
                           पूर्णांक flags)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->data[3];
    DXVA2Mapping      *map;
    D3DSURFACE_DESC    surfaceDesc;
    D3DLOCKED_RECT     LockedRect;
    HRESULT            hr;
    पूर्णांक i, err, nb_planes;
    पूर्णांक lock_flags = 0;

    nb_planes = av_pix_fmt_मोजणी_planes(dst->format);

    hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");
        परत AVERROR_UNKNOWN;
    }

    जर (!(flags & AV_HWFRAME_MAP_WRITE))
        lock_flags |= D3DLOCK_READONLY;
    जर (flags & AV_HWFRAME_MAP_OVERWRITE)
        lock_flags |= D3DLOCK_DISCARD;

    hr = IDirect3DSurface9_LockRect(surface, &LockedRect, रिक्त, lock_flags);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");
        परत AVERROR_UNKNOWN;
    }

    map = av_mallocz(आकार(*map));
    जर (!map) {
        err = AVERROR(ENOMEM);
        जा fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                dxva2_unmap_frame, map);
    जर (err < 0) {
        av_freep(&map);
        जा fail;
    }

    साठी (i = 0; i < nb_planes; i++)
        dst->linesize[i] = LockedRect.Pitch;

    av_image_fill_pointers(dst->data, dst->format, surfaceDesc.Height,
                           (uint8_t*)LockedRect.pBits, dst->linesize);

    जर (dst->format == AV_PIX_FMT_PAL8)
        dst->data[1] = (uint8_t*)map->palette_dummy;

    परत 0;
fail:
    IDirect3DSurface9_UnlockRect(surface);
    परत err;
}

स्थिर पूर्णांक dxva2_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  स्थिरांक AVFrame *src)
{
    AVFrame *map;
    पूर्णांक ret;

    जर (src->format != ctx->sw_format)
        परत AVERROR(ENOSYS);

    map = av_frame_alloc();
    जर (!map)
        परत AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    जर (ret < 0)
        जा fail;

    av_image_copy2(map->data, map->linesize, src->data, src->linesize,
                   ctx->sw_format, src->width, src->height);

fail:
    av_frame_free(&map);
    परत ret;
}

स्थिर पूर्णांक dxva2_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    स्थिरांक AVFrame *src)
{
    AVFrame *map;
    सूचक_भेद_प्रकार src_linesize[4], dst_linesize[4];
    पूर्णांक ret, i;

    जर (dst->format != ctx->sw_format)
        परत AVERROR(ENOSYS);

    map = av_frame_alloc();
    जर (!map)
        परत AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, src, AV_HWFRAME_MAP_READ);
    जर (ret < 0)
        जा fail;

    साठी (i = 0; i < 4; i++) {
        dst_linesize[i] = dst->linesize[i];
        src_linesize[i] = map->linesize[i];
    }
    av_image_copy_uc_from(dst->data, dst_linesize, (स्थिरांक uint8_t **)map->data, src_linesize,
                          ctx->sw_format, src->width, src->height);
fail:
    av_frame_free(&map);
    परत ret;
}

स्थिर पूर्णांक dxva2_map_from(AVHWFramesContext *ctx,
                          AVFrame *dst, स्थिरांक AVFrame *src, पूर्णांक flags)
{
    पूर्णांक err;

    जर (dst->format != AV_PIX_FMT_NONE && dst->format != ctx->sw_format)
        परत AVERROR(ENOSYS);
    dst->format = ctx->sw_format;

    err = dxva2_map_frame(ctx, dst, src, flags);
    जर (err < 0)
        परत err;

    err = av_frame_copy_props(dst, src);
    जर (err < 0)
        परत err;

    परत 0;
}

स्थिर शून्य dxva2_device_free(AVHWDeviceContext *ctx)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv       *priv = ctx->user_opaque;

    जर (hwctx->devmgr && priv->device_handle != INVALID_HANDLE_मूल्य)
        IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, priv->device_handle);

    जर (hwctx->devmgr)
        IDirect3DDeviceManager9_Release(hwctx->devmgr);

    जर (priv->d3d9device)
        IDirect3DDevice9_Release(priv->d3d9device);

    जर (priv->d3d9)
        IDirect3D9_Release(priv->d3d9);

    जर (priv->d3dlib)
        dlclose(priv->d3dlib);

    जर (priv->dxva2lib)
        dlclose(priv->dxva2lib);

    av_freep(&ctx->user_opaque);
}

स्थिर पूर्णांक dxva2_device_create9(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODE d3ddm;
    HRESULT hr;
    pDirect3DCreate9 *createD3D = (pDirect3DCreate9 *)dlsym(priv->d3dlib, "Direct3DCreate9");
    जर (!createD3D) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate Direct3DCreate9\n");
        परत AVERROR_UNKNOWN;
    }

    priv->d3d9 = createD3D(D3D_SDK_VERSION);
    जर (!priv->d3d9) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create IDirect3D object\n");
        परत AVERROR_UNKNOWN;
    }

    IDirect3D9_GetAdapterDisplayMode(priv->d3d9, adapter, &d3ddm);

    d3dpp.BackBufferFormat = d3ddm.Format;

    hr = IDirect3D9_CreateDevice(priv->d3d9, adapter, D3DDEVTYPE_HAL, GetDesktopWindow(),
                                 FF_D3DCREATE_FLAGS,
                                 &d3dpp, &priv->d3d9device);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device\n");
        परत AVERROR_UNKNOWN;
    }

    परत 0;
}

स्थिर पूर्णांक dxva2_device_create9ex(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODEEX modeex = {0};
    IDirect3D9Ex *d3d9ex = रिक्त;
    IDirect3DDevice9Ex *exdev = रिक्त;
    HRESULT hr;
    pDirect3DCreate9Ex *createD3DEx = (pDirect3DCreate9Ex *)dlsym(priv->d3dlib, "Direct3DCreate9Ex");
    जर (!createD3DEx)
        परत AVERROR(ENOSYS);

    hr = createD3DEx(D3D_SDK_VERSION, &d3d9ex);
    जर (FAILED(hr))
        परत AVERROR_UNKNOWN;

    modeex.Size = आकार(D3DDISPLAYMODEEX);
    hr = IDirect3D9Ex_GetAdapterDisplayModeEx(d3d9ex, adapter, &modeex, रिक्त);
    जर (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        परत AVERROR_UNKNOWN;
    }

    d3dpp.BackBufferFormat = modeex.Format;

    hr = IDirect3D9Ex_CreateDeviceEx(d3d9ex, adapter, D3DDEVTYPE_HAL, GetDesktopWindow(),
                                     FF_D3DCREATE_FLAGS,
                                     &d3dpp, रिक्त, &exdev);
    जर (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        परत AVERROR_UNKNOWN;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Using D3D9Ex device.\n");
    priv->d3d9 = (IDirect3D9 *)d3d9ex;
    priv->d3d9device = (IDirect3DDevice9 *)exdev;
    परत 0;
}

स्थिर पूर्णांक dxva2_device_create(AVHWDeviceContext *ctx, स्थिरांक अक्षर *device,
                               AVDictionary *opts, पूर्णांक flags)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv *priv;
    pCreateDeviceManager9 *createDeviceManager = रिक्त;
    अचिन्हित resetToken = 0;
    UINT adapter = D3DADAPTER_DEFAULT;
    HRESULT hr;
    पूर्णांक err;

    जर (device)
        adapter = म_से_प(device);

    priv = av_mallocz(आकार(*priv));
    जर (!priv)
        परत AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->मुक्त        = dxva2_device_free;

    priv->device_handle = INVALID_HANDLE_मूल्य;

    priv->d3dlib = dlopen("d3d9.dll", 0);
    जर (!priv->d3dlib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D9 library\n");
        परत AVERROR_UNKNOWN;
    }
    priv->dxva2lib = dlopen("dxva2.dll", 0);
    जर (!priv->dxva2lib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load DXVA2 library\n");
        परत AVERROR_UNKNOWN;
    }

    createDeviceManager = (pCreateDeviceManager9 *)dlsym(priv->dxva2lib,
                                                         "DXVA2CreateDirect3DDeviceManager9");
    जर (!createDeviceManager) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate DXVA2CreateDirect3DDeviceManager9\n");
        परत AVERROR_UNKNOWN;
    }

    जर (dxva2_device_create9ex(ctx, adapter) < 0) {
        // Retry with "classic" d3d9
        err = dxva2_device_create9(ctx, adapter);
        जर (err < 0)
            परत err;
    }

    hr = createDeviceManager(&resetToken, &hwctx->devmgr);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device manager\n");
        परत AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_ResetDevice(hwctx->devmgr, priv->d3d9device, resetToken);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind Direct3D device to device manager\n");
        परत AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &priv->device_handle);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        परत AVERROR_UNKNOWN;
    }

    परत 0;
}

स्थिरांक HWContextType ff_hwcontext_type_dxva2 = {
    .type                 = AV_HWDEVICE_TYPE_DXVA2,
    .name                 = "DXVA2",

    .device_hwctx_size    = आकार(AVDXVA2DeviceContext),
    .frames_hwctx_size    = आकार(DXVA2FramesContext),

    .device_create        = dxva2_device_create,
    .frames_init          = dxva2_frames_init,
    .frames_uninit        = dxva2_frames_uninit,
    .frames_get_buffer    = dxva2_get_buffer,
    .transfer_get_formats = dxva2_transfer_get_formats,
    .transfer_data_to     = dxva2_transfer_data_to,
    .transfer_data_from   = dxva2_transfer_data_from,
    .map_from             = dxva2_map_from,

    .pix_fmts             = (स्थिरांक गणना AVPixelFormat[]){ AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_NONE },
};
