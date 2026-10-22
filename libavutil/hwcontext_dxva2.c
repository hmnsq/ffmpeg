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

#അന്തര്ഭാവ <windows.h>

#define DXVA2API_USE_BITFIELDS
#define COBJMACROS

#അന്തര്ഭാവ <d3d9.h>
#അന്തര്ഭാവ <dxva2api.h>
#അന്തര്ഭാവ <initguid.h>

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "hwcontext.h"
#അന്തര്ഭാവ "hwcontext_dxva2.h"
#അന്തര്ഭാവ "hwcontext_internal.h"
#അന്തര്ഭാവ "imgutils.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "pixdesc.h"
#അന്തര്ഭാവ "pixfmt.h"
#അന്തര്ഭാവ "compat/w32dlfcn.h"

തരനിർവചനം IDirect3D9* WINAPI pDirect3DCreate9(UINT);
തരനിർവചനം HRESULT WINAPI pDirect3DCreate9Ex(UINT, IDirect3D9Ex **);
തരനിർവചനം HRESULT WINAPI pCreateDeviceManager9(UINT *, IDirect3DDeviceManager9 **);

#define FF_D3DCREATE_FLAGS (D3DCREATE_SOFTWARE_VERTEXPROCESSING | \
                            D3DCREATE_MULTITHREADED | \
                            D3DCREATE_FPU_PRESERVE)

സ്ഥിതം സ്ഥിരം D3DPRESENT_PARAMETERS dxva2_present_params = {
    .Windowed         = TRUE,
    .BackBufferWidth  = 640,
    .BackBufferHeight = 480,
    .Back_Buffer_എണ്ണം  = 0,
    .SwapEffect       = D3DSWAPEFFECT_DISCARD,
    .Flags            = D3DPRESENTFLAG_VIDEO,
};

തരനിർവചനം ഘടന DXVA2Mapping {
    uint32_t palette_dummy[256];
} DXVA2Mapping;

തരനിർവചനം ഘടന DXVA2FramesContext {
    /**
     * The public AVDXVA2FramesContext. See hwcontext_dxva2.h for it.
     */
    AVDXVA2FramesContext p;

    IDirect3DSurface9 **surfaces_internal;
    പൂർണ്ണസംഖ്യ              nb_surfaces_used;

    HANDLE  device_handle;
    IDirectXVideoAccelerationService *service;

    D3DFORMAT format;
} DXVA2FramesContext;

തരനിർവചനം ഘടന DXVA2DevicePriv {
    HMODULE d3dlib;
    HMODULE dxva2lib;

    HANDLE device_handle;

    IDirect3D9       *d3d9;
    IDirect3DDevice9 *d3d9device;
} DXVA2DevicePriv;

സ്ഥിതം സ്ഥിരം ഘടന {
    D3DFORMAT d3d_format;
    എണ്ണൽ AVPixelFormat pix_fmt;
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

സ്ഥിതം ശൂന്യം dxva2_frames_uninit(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2FramesContext              *s = ctx->hwctx;
    AVDXVA2FramesContext *frames_hwctx = &s->p;
    പൂർണ്ണസംഖ്യ i;

    എങ്കിൽ (frames_hwctx->decoder_to_release)
        IDirectXVideoDecoder_Release(frames_hwctx->decoder_to_release);

    എങ്കിൽ (s->surfaces_internal) {
        വേണ്ടി (i = 0; i < frames_hwctx->nb_surfaces; i++) {
            എങ്കിൽ (s->surfaces_internal[i])
                IDirect3DSurface9_Release(s->surfaces_internal[i]);
        }
    }
    av_freep(&s->surfaces_internal);

    എങ്കിൽ (s->service) {
        IDirectXVideoAccelerationService_Release(s->service);
        s->service = ശൂന്യ;
    }

    എങ്കിൽ (s->device_handle != INVALID_HANDLE_മൂല്യം) {
        IDirect3DDeviceManager9_CloseDeviceHandle(device_hwctx->devmgr, s->device_handle);
        s->device_handle = INVALID_HANDLE_മൂല്യം;
    }
}

സ്ഥിതം ശൂന്യം dxva2_pool_release_dummy(ശൂന്യം *opaque, uint8_t *data)
{
    // important not to free anything here--data is a surface object
    // associated with the call to CreateSurface(), and these surfaces are
    // released in dxva2_frames_uninit()
}

സ്ഥിതം AVBufferRef *dxva2_pool_alloc(ശൂന്യം *opaque, size_t size)
{
    AVHWFramesContext      *ctx = (AVHWFramesContext*)opaque;
    DXVA2FramesContext       *s = ctx->hwctx;
    AVDXVA2FramesContext *hwctx = &s->p;

    എങ്കിൽ (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        തിരികെ av_buffer_create((uint8_t*)s->surfaces_internal[s->nb_surfaces_used - 1],
                                വലുപ്പം(**hwctx->surfaces), dxva2_pool_release_dummy, 0, 0);
    }

    തിരികെ ശൂന്യ;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ dxva2_init_pool(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2FramesContext              *s = ctx->hwctx;
    AVDXVA2FramesContext *frames_hwctx = &s->p;
    പൂർണ്ണസംഖ്യ decode = (frames_hwctx->surface_type == DXVA2_VideoDecoderRenderTarget);

    പൂർണ്ണസംഖ്യ i;
    HRESULT hr;

    എങ്കിൽ (ctx->initial_pool_size <= 0)
        തിരികെ 0;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(device_hwctx->devmgr, &s->device_handle);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_GetVideoService(device_hwctx->devmgr,
                                                 s->device_handle,
                                                 decode ? &video_decoder_service : &video_processor_service,
                                                 (ശൂന്യം **)&s->service);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create the video service\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        എങ്കിൽ (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            നിർത്തുക;
        }
    }
    എങ്കിൽ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        തിരികെ AVERROR(EINVAL);
    }

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     വലുപ്പം(*s->surfaces_internal));
    എങ്കിൽ (!s->surfaces_internal)
        തിരികെ AVERROR(ENOMEM);

    hr = IDirectXVideoAccelerationService_CreateSurface(s->service,
                                                        ctx->width, ctx->height,
                                                        ctx->initial_pool_size - 1,
                                                        s->format, D3DPOOL_DEFAULT, 0,
                                                        frames_hwctx->surface_type,
                                                        s->surfaces_internal, ശൂന്യ);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the surfaces\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(വലുപ്പം(*s->surfaces_internal),
                             ctx, dxva2_pool_alloc, ശൂന്യ);
    എങ്കിൽ (!ffhwframesctx(ctx)->pool_internal)
        തിരികെ AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ dxva2_frames_init(AVHWFramesContext *ctx)
{
    DXVA2FramesContext       *s = ctx->hwctx;
    AVDXVA2FramesContext *hwctx = &s->p;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (hwctx->surface_type != DXVA2_VideoDecoderRenderTarget &&
        hwctx->surface_type != DXVA2_VideoProcessorRenderTarget) {
        av_log(ctx, AV_LOG_ERROR, "Unknown surface type: %lu\n",
               hwctx->surface_type);
        തിരികെ AVERROR(EINVAL);
    }

    s->device_handle = INVALID_HANDLE_മൂല്യം;

    /* init the frame pool if the caller didn't provide one */
    എങ്കിൽ (!ctx->pool) {
        ret = dxva2_init_pool(ctx);
        എങ്കിൽ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            തിരികെ ret;
        }
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ dxva2_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    എങ്കിൽ (!frame->buf[0])
        തിരികെ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_DXVA2_VLD;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ dxva2_transfer_get_formats(AVHWFramesContext *ctx,
                                      എണ്ണൽ AVHWFrameTransferDirection dir,
                                      എണ്ണൽ AVPixelFormat **formats)
{
    എണ്ണൽ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, വലുപ്പം(*fmts));
    എങ്കിൽ (!fmts)
        തിരികെ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം dxva2_unmap_frame(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)hwmap->source->data[3];
    IDirect3DSurface9_UnlockRect(surface);
    av_freep(&hwmap->priv);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ dxva2_map_frame(AVHWFramesContext *ctx, AVFrame *dst, സ്ഥിരം AVFrame *src,
                           പൂർണ്ണസംഖ്യ flags)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->data[3];
    DXVA2Mapping      *map;
    D3DSURFACE_DESC    surfaceDesc;
    D3DLOCKED_RECT     LockedRect;
    HRESULT            hr;
    പൂർണ്ണസംഖ്യ i, err, nb_planes;
    പൂർണ്ണസംഖ്യ lock_flags = 0;

    nb_planes = av_pix_fmt_എണ്ണം_planes(dst->format);

    hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    എങ്കിൽ (!(flags & AV_HWFRAME_MAP_WRITE))
        lock_flags |= D3DLOCK_READONLY;
    എങ്കിൽ (flags & AV_HWFRAME_MAP_OVERWRITE)
        lock_flags |= D3DLOCK_DISCARD;

    hr = IDirect3DSurface9_LockRect(surface, &LockedRect, ശൂന്യ, lock_flags);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    map = av_mallocz(വലുപ്പം(*map));
    എങ്കിൽ (!map) {
        err = AVERROR(ENOMEM);
        പോകുക fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                dxva2_unmap_frame, map);
    എങ്കിൽ (err < 0) {
        av_freep(&map);
        പോകുക fail;
    }

    വേണ്ടി (i = 0; i < nb_planes; i++)
        dst->linesize[i] = LockedRect.Pitch;

    av_image_fill_pointers(dst->data, dst->format, surfaceDesc.Height,
                           (uint8_t*)LockedRect.pBits, dst->linesize);

    എങ്കിൽ (dst->format == AV_PIX_FMT_PAL8)
        dst->data[1] = (uint8_t*)map->palette_dummy;

    തിരികെ 0;
fail:
    IDirect3DSurface9_UnlockRect(surface);
    തിരികെ err;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ dxva2_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  സ്ഥിരം AVFrame *src)
{
    AVFrame *map;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (src->format != ctx->sw_format)
        തിരികെ AVERROR(ENOSYS);

    map = av_frame_alloc();
    എങ്കിൽ (!map)
        തിരികെ AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    av_image_copy2(map->data, map->linesize, src->data, src->linesize,
                   ctx->sw_format, src->width, src->height);

fail:
    av_frame_free(&map);
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ dxva2_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    സ്ഥിരം AVFrame *src)
{
    AVFrame *map;
    ptrdiff_t src_linesize[4], dst_linesize[4];
    പൂർണ്ണസംഖ്യ ret, i;

    എങ്കിൽ (dst->format != ctx->sw_format)
        തിരികെ AVERROR(ENOSYS);

    map = av_frame_alloc();
    എങ്കിൽ (!map)
        തിരികെ AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, src, AV_HWFRAME_MAP_READ);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    വേണ്ടി (i = 0; i < 4; i++) {
        dst_linesize[i] = dst->linesize[i];
        src_linesize[i] = map->linesize[i];
    }
    av_image_copy_uc_from(dst->data, dst_linesize, (സ്ഥിരം uint8_t **)map->data, src_linesize,
                          ctx->sw_format, src->width, src->height);
fail:
    av_frame_free(&map);
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ dxva2_map_from(AVHWFramesContext *ctx,
                          AVFrame *dst, സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    പൂർണ്ണസംഖ്യ err;

    എങ്കിൽ (dst->format != AV_PIX_FMT_NONE && dst->format != ctx->sw_format)
        തിരികെ AVERROR(ENOSYS);
    dst->format = ctx->sw_format;

    err = dxva2_map_frame(ctx, dst, src, flags);
    എങ്കിൽ (err < 0)
        തിരികെ err;

    err = av_frame_copy_props(dst, src);
    എങ്കിൽ (err < 0)
        തിരികെ err;

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം dxva2_device_free(AVHWDeviceContext *ctx)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv       *priv = ctx->user_opaque;

    എങ്കിൽ (hwctx->devmgr && priv->device_handle != INVALID_HANDLE_മൂല്യം)
        IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, priv->device_handle);

    എങ്കിൽ (hwctx->devmgr)
        IDirect3DDeviceManager9_Release(hwctx->devmgr);

    എങ്കിൽ (priv->d3d9device)
        IDirect3DDevice9_Release(priv->d3d9device);

    എങ്കിൽ (priv->d3d9)
        IDirect3D9_Release(priv->d3d9);

    എങ്കിൽ (priv->d3dlib)
        dlclose(priv->d3dlib);

    എങ്കിൽ (priv->dxva2lib)
        dlclose(priv->dxva2lib);

    av_freep(&ctx->user_opaque);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ dxva2_device_create9(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODE d3ddm;
    HRESULT hr;
    pDirect3DCreate9 *createD3D = (pDirect3DCreate9 *)dlsym(priv->d3dlib, "Direct3DCreate9");
    എങ്കിൽ (!createD3D) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate Direct3DCreate9\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    priv->d3d9 = createD3D(D3D_SDK_VERSION);
    എങ്കിൽ (!priv->d3d9) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create IDirect3D object\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    IDirect3D9_GetAdapterDisplayMode(priv->d3d9, adapter, &d3ddm);

    d3dpp.BackBufferFormat = d3ddm.Format;

    hr = IDirect3D9_CreateDevice(priv->d3d9, adapter, D3DDEVTYPE_HAL, GetDesktopWindow(),
                                 FF_D3DCREATE_FLAGS,
                                 &d3dpp, &priv->d3d9device);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ dxva2_device_create9ex(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODEEX modeex = {0};
    IDirect3D9Ex *d3d9ex = ശൂന്യ;
    IDirect3DDevice9Ex *exdev = ശൂന്യ;
    HRESULT hr;
    pDirect3DCreate9Ex *createD3DEx = (pDirect3DCreate9Ex *)dlsym(priv->d3dlib, "Direct3DCreate9Ex");
    എങ്കിൽ (!createD3DEx)
        തിരികെ AVERROR(ENOSYS);

    hr = createD3DEx(D3D_SDK_VERSION, &d3d9ex);
    എങ്കിൽ (FAILED(hr))
        തിരികെ AVERROR_UNKNOWN;

    modeex.Size = വലുപ്പം(D3DDISPLAYMODEEX);
    hr = IDirect3D9Ex_GetAdapterDisplayModeEx(d3d9ex, adapter, &modeex, ശൂന്യ);
    എങ്കിൽ (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        തിരികെ AVERROR_UNKNOWN;
    }

    d3dpp.BackBufferFormat = modeex.Format;

    hr = IDirect3D9Ex_CreateDeviceEx(d3d9ex, adapter, D3DDEVTYPE_HAL, GetDesktopWindow(),
                                     FF_D3DCREATE_FLAGS,
                                     &d3dpp, ശൂന്യ, &exdev);
    എങ്കിൽ (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        തിരികെ AVERROR_UNKNOWN;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Using D3D9Ex device.\n");
    priv->d3d9 = (IDirect3D9 *)d3d9ex;
    priv->d3d9device = (IDirect3DDevice9 *)exdev;
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ dxva2_device_create(AVHWDeviceContext *ctx, സ്ഥിരം അക്ഷരം *device,
                               AVDictionary *opts, പൂർണ്ണസംഖ്യ flags)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv *priv;
    pCreateDeviceManager9 *createDeviceManager = ശൂന്യ;
    unsigned resetToken = 0;
    UINT adapter = D3DADAPTER_DEFAULT;
    HRESULT hr;
    പൂർണ്ണസംഖ്യ err;

    എങ്കിൽ (device)
        adapter = atoi(device);

    priv = av_mallocz(വലുപ്പം(*priv));
    എങ്കിൽ (!priv)
        തിരികെ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->സ്വതന്ത്രം        = dxva2_device_free;

    priv->device_handle = INVALID_HANDLE_മൂല്യം;

    priv->d3dlib = dlopen("d3d9.dll", 0);
    എങ്കിൽ (!priv->d3dlib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D9 library\n");
        തിരികെ AVERROR_UNKNOWN;
    }
    priv->dxva2lib = dlopen("dxva2.dll", 0);
    എങ്കിൽ (!priv->dxva2lib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load DXVA2 library\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    createDeviceManager = (pCreateDeviceManager9 *)dlsym(priv->dxva2lib,
                                                         "DXVA2CreateDirect3DDeviceManager9");
    എങ്കിൽ (!createDeviceManager) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate DXVA2CreateDirect3DDeviceManager9\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    എങ്കിൽ (dxva2_device_create9ex(ctx, adapter) < 0) {
        // Retry with "classic" d3d9
        err = dxva2_device_create9(ctx, adapter);
        എങ്കിൽ (err < 0)
            തിരികെ err;
    }

    hr = createDeviceManager(&resetToken, &hwctx->devmgr);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device manager\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_ResetDevice(hwctx->devmgr, priv->d3d9device, resetToken);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind Direct3D device to device manager\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &priv->device_handle);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    തിരികെ 0;
}

സ്ഥിരം HWContextType ff_hwcontext_type_dxva2 = {
    .type                 = AV_HWDEVICE_TYPE_DXVA2,
    .name                 = "DXVA2",

    .device_hwctx_size    = വലുപ്പം(AVDXVA2DeviceContext),
    .frames_hwctx_size    = വലുപ്പം(DXVA2FramesContext),

    .device_create        = dxva2_device_create,
    .frames_init          = dxva2_frames_init,
    .frames_uninit        = dxva2_frames_uninit,
    .frames_get_buffer    = dxva2_get_buffer,
    .transfer_get_formats = dxva2_transfer_get_formats,
    .transfer_data_to     = dxva2_transfer_data_to,
    .transfer_data_from   = dxva2_transfer_data_from,
    .map_from             = dxva2_map_from,

    .pix_fmts             = (സ്ഥിരം എണ്ണൽ AVPixelFormat[]){ AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_NONE },
};
