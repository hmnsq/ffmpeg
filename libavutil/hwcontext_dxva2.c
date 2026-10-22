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

#ਅਨ੍ਤਰ੍ਭਾਵ <windows.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DXVA2API_USE_BITFIELDS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COBJMACROS

#ਅਨ੍ਤਰ੍ਭਾਵ <d3d9.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <dxva2api.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <initguid.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_dxva2.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "imgutils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "compat/w32dlfcn.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ IDirect3D9* WINAPI pDirect3DCreate9(UINT);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ HRESULT WINAPI pDirect3DCreate9Ex(UINT, IDirect3D9Ex **);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ HRESULT WINAPI pCreateDeviceManager9(UINT *, IDirect3DDeviceManager9 **);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_D3DCREATE_FLAGS (D3DCREATE_SOFTWARE_VERTEXPROCESSING | \
                            D3DCREATE_MULTITHREADED | \
                            D3DCREATE_FPU_PRESERVE)

ਸਥਿਰ ਅਚਲ D3DPRESENT_PARAMETERS dxva2_present_params = {
    .Windowed         = TRUE,
    .ਪਿੱਠ_ਬਫਰ_ਚੌੜਾਈ  = 640,
    .ਪਿੱਠ_ਬਫਰ_ਉਚਾਈ = 480,
    .ਪਿੱਠ_ਬਫਰ_ਗਿਣਤੀ  = 0,
    .ਅਦਲਾ_ਬਦਲੀ_Effect       = D3DSWAPEFFECT_DISCARD,
    .Flags            = D3DPRESENTFLAG_VIDEO,
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DXVA2Mapping {
    uint32_t palette_dummy[256];
} DXVA2Mapping;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DXVA2_ਚੌਖਟੇ_Context {
    /**
     * The public AVDXVA2FramesContext. See hwcontext_dxva2.h for it.
     */
    AVDXVA2_ਚੌਖਟੇ_Context p;

    IDirect3DSurface9 **surfaces_ਅੰਦਰੂਨੀ;
    ਪੂਰਨ              nb_surfaces_ਵਰਤਿਆ;

    HANDLE  device_handle;
    IDirectXVideoAccelerationService *service;

    D3DFORMAT format;
} DXVA2_ਚੌਖਟੇ_Context;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DXVA2DevicePriv {
    HMODULE d3dlib;
    HMODULE dxva2lib;

    HANDLE device_handle;

    IDirect3D9       *d3d9;
    IDirect3DDevice9 *d3d9device;
} DXVA2DevicePriv;

ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
    D3DFORMAT d3d_format;
    ਗਿਣਤੀ AVPixelFormat pix_fmt;
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

ਸਥਿਰ ਖਾਲੀ dxva2_ਚੌਖਟੇ_uninit(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2_ਚੌਖਟੇ_Context              *s = ctx->hwctx;
    AVDXVA2_ਚੌਖਟੇ_Context *ਚੌਖਟੇ_hwctx = &s->p;
    ਪੂਰਨ i;

    ਜੇ (ਚੌਖਟੇ_hwctx->decoder_ਮੰਜ਼ਿਲ_release)
        IDirectXVideoDecoder_Release(ਚੌਖਟੇ_hwctx->decoder_ਮੰਜ਼ਿਲ_release);

    ਜੇ (s->surfaces_ਅੰਦਰੂਨੀ) {
        ਲਈ (i = 0; i < ਚੌਖਟੇ_hwctx->nb_surfaces; i++) {
            ਜੇ (s->surfaces_ਅੰਦਰੂਨੀ[i])
                IDirect3DSurface9_Release(s->surfaces_ਅੰਦਰੂਨੀ[i]);
        }
    }
    av_freep(&s->surfaces_ਅੰਦਰੂਨੀ);

    ਜੇ (s->service) {
        IDirectXVideoAccelerationService_Release(s->service);
        s->service = ਨਿਰਾ;
    }

    ਜੇ (s->device_handle != INVALID_HANDLE_ਮੁੱਲ) {
        IDirect3DDeviceManager9_CloseDeviceHandle(device_hwctx->devmgr, s->device_handle);
        s->device_handle = INVALID_HANDLE_ਮੁੱਲ;
    }
}

ਸਥਿਰ ਖਾਲੀ dxva2_pool_release_dummy(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    // important not to free anything here--data is a surface object
    // associated with the call to CreateSurface(), and these surfaces are
    // released in dxva2_frames_uninit()
}

ਸਥਿਰ AVBufferRef *dxva2_pool_alloc(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    AVHWFramesContext      *ctx = (AVHWFramesContext*)opaque;
    DXVA2_ਚੌਖਟੇ_Context       *s = ctx->hwctx;
    AVDXVA2_ਚੌਖਟੇ_Context *hwctx = &s->p;

    ਜੇ (s->nb_surfaces_ਵਰਤਿਆ < hwctx->nb_surfaces) {
        s->nb_surfaces_ਵਰਤਿਆ++;
        ਵਾਪਸ av_ਬਫਰ_create((uint8_t*)s->surfaces_ਅੰਦਰੂਨੀ[s->nb_surfaces_ਵਰਤਿਆ - 1],
                                ਆਕਾਰ(**hwctx->surfaces), dxva2_pool_release_dummy, 0, 0);
    }

    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਪੂਰਨ dxva2_init_pool(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2_ਚੌਖਟੇ_Context              *s = ctx->hwctx;
    AVDXVA2_ਚੌਖਟੇ_Context *ਚੌਖਟੇ_hwctx = &s->p;
    ਪੂਰਨ decode = (ਚੌਖਟੇ_hwctx->surface_type == DXVA2_Video_Decoder_Render_ਨਿਸ਼ਾਨਾ);

    ਪੂਰਨ i;
    HRESULT hr;

    ਜੇ (ctx->initial_pool_ਮਾਪ <= 0)
        ਵਾਪਸ 0;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(device_hwctx->devmgr, &s->device_handle);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_GetVideoService(device_hwctx->devmgr,
                                                 s->device_handle,
                                                 decode ? &video_decoder_service : &video_processor_service,
                                                 (ਖਾਲੀ **)&s->service);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create the video service\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ਜੇ (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            ਰੋਕੋ;
        }
    }
    ਜੇ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ਵਾਪਸ AVERROR(EINVAL);
    }

    s->surfaces_ਅੰਦਰੂਨੀ = av_calloc(ctx->initial_pool_ਮਾਪ,
                                     ਆਕਾਰ(*s->surfaces_ਅੰਦਰੂਨੀ));
    ਜੇ (!s->surfaces_ਅੰਦਰੂਨੀ)
        ਵਾਪਸ AVERROR(ENOMEM);

    hr = IDirectXVideoAccelerationService_CreateSurface(s->service,
                                                        ctx->ਚੌੜਾਈ, ctx->ਉਚਾਈ,
                                                        ctx->initial_pool_ਮਾਪ - 1,
                                                        s->format, D3DPOOL_DEFAULT, 0,
                                                        ਚੌਖਟੇ_hwctx->surface_type,
                                                        s->surfaces_ਅੰਦਰੂਨੀ, ਨਿਰਾ);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the surfaces\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ =
        av_ਬਫਰ_pool_init2(ਆਕਾਰ(*s->surfaces_ਅੰਦਰੂਨੀ),
                             ctx, dxva2_pool_alloc, ਨਿਰਾ);
    ਜੇ (!ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਚੌਖਟੇ_hwctx->surfaces    = s->surfaces_ਅੰਦਰੂਨੀ;
    ਚੌਖਟੇ_hwctx->nb_surfaces = ctx->initial_pool_ਮਾਪ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ dxva2_ਚੌਖਟੇ_init(AVHWFramesContext *ctx)
{
    DXVA2_ਚੌਖਟੇ_Context       *s = ctx->hwctx;
    AVDXVA2_ਚੌਖਟੇ_Context *hwctx = &s->p;
    ਪੂਰਨ ret;

    ਜੇ (hwctx->surface_type != DXVA2_Video_Decoder_Render_ਨਿਸ਼ਾਨਾ &&
        hwctx->surface_type != DXVA2_Video_Processor_Render_ਨਿਸ਼ਾਨਾ) {
        av_log(ctx, AV_LOG_ERROR, "Unknown surface type: %lu\n",
               hwctx->surface_type);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    s->device_handle = INVALID_HANDLE_ਮੁੱਲ;

    /* init the frame pool if the caller didn't provide one */
    ਜੇ (!ctx->pool) {
        ret = dxva2_init_pool(ctx);
        ਜੇ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            ਵਾਪਸ ret;
        }
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ dxva2_get_ਬਫਰ(AVHWFramesContext *ctx, AVFrame *ਚੌਖਟਾ)
{
    ਚੌਖਟਾ->buf[0] = av_ਬਫਰ_pool_get(ctx->pool);
    ਜੇ (!ਚੌਖਟਾ->buf[0])
        ਵਾਪਸ AVERROR(ENOMEM);

    ਚੌਖਟਾ->ਅੰਕੜੇ[3] = ਚੌਖਟਾ->buf[0]->ਅੰਕੜੇ;
    ਚੌਖਟਾ->format  = AV_PIX_FMT_DXVA2_VLD;
    ਚੌਖਟਾ->ਚੌੜਾਈ   = ctx->ਚੌੜਾਈ;
    ਚੌਖਟਾ->ਉਚਾਈ  = ctx->ਉਚਾਈ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ dxva2_transfer_get_formats(AVHWFramesContext *ctx,
                                      ਗਿਣਤੀ AVHWFrameTransferDirection dir,
                                      ਗਿਣਤੀ AVPixelFormat **formats)
{
    ਗਿਣਤੀ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ਆਕਾਰ(*fmts));
    ਜੇ (!fmts)
        ਵਾਪਸ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ dxva2_unmap_ਚੌਖਟਾ(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)hwmap->ਸਰੋਤ->ਅੰਕੜੇ[3];
    IDirect3DSurface9_UnlockRect(surface);
    av_freep(&hwmap->priv);
}

ਸਥਿਰ ਪੂਰਨ dxva2_map_ਚੌਖਟਾ(AVHWFramesContext *ctx, AVFrame *dst, ਅਚਲ AVFrame *src,
                           ਪੂਰਨ flags)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->ਅੰਕੜੇ[3];
    DXVA2Mapping      *map;
    D3DSURFACE_DESC    surfaceDesc;
    D3DLOCKED_RECT     LockedRect;
    HRESULT            hr;
    ਪੂਰਨ i, err, nb_planes;
    ਪੂਰਨ ਤਾਲਾ_flags = 0;

    nb_planes = av_pix_fmt_ਗਿਣਤੀ_planes(dst->format);

    hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਜੇ (!(flags & AV_HWFRAME_MAP_WRITE))
        ਤਾਲਾ_flags |= D3DLOCK_READONLY;
    ਜੇ (flags & AV_HWFRAME_MAP_OVERWRITE)
        ਤਾਲਾ_flags |= D3DLOCK_DISCARD;

    hr = IDirect3_DSurface9_ਤਾਲਾ_Rect(surface, &LockedRect, ਨਿਰਾ, ਤਾਲਾ_flags);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    map = av_mallocz(ਆਕਾਰ(*map));
    ਜੇ (!map) {
        err = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    err = ff_hwframe_map_create(src->hw_ਚੌਖਟੇ_ctx, dst, src,
                                dxva2_unmap_ਚੌਖਟਾ, map);
    ਜੇ (err < 0) {
        av_freep(&map);
        ਜਾਓ fail;
    }

    ਲਈ (i = 0; i < nb_planes; i++)
        dst->linesize[i] = LockedRect.Pitch;

    av_image_fill_ਸੂਚਕ_ਸਾਰੇ(dst->ਅੰਕੜੇ, dst->format, surfaceDesc.ਉਚਾਈ_2,
                           (uint8_t*)LockedRect.p_ਬਿੱਟ, dst->linesize);

    ਜੇ (dst->format == AV_PIX_FMT_PAL8)
        dst->ਅੰਕੜੇ[1] = (uint8_t*)map->palette_dummy;

    ਵਾਪਸ 0;
fail:
    IDirect3DSurface9_UnlockRect(surface);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ dxva2_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ(AVHWFramesContext *ctx, AVFrame *dst,
                                  ਅਚਲ AVFrame *src)
{
    AVFrame *map;
    ਪੂਰਨ ret;

    ਜੇ (src->format != ctx->sw_format)
        ਵਾਪਸ AVERROR(ENOSYS);

    map = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!map)
        ਵਾਪਸ AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_ਚੌਖਟਾ(ctx, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    av_image_copy2(map->ਅੰਕੜੇ, map->linesize, src->ਅੰਕੜੇ, src->linesize,
                   ctx->sw_format, src->ਚੌੜਾਈ, src->ਉਚਾਈ);

fail:
    av_ਚੌਖਟਾ_free(&map);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ dxva2_transfer_ਅੰਕੜੇ_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ਅਚਲ AVFrame *src)
{
    AVFrame *map;
    ptrdiff_t src_linesize[4], dst_linesize[4];
    ਪੂਰਨ ret, i;

    ਜੇ (dst->format != ctx->sw_format)
        ਵਾਪਸ AVERROR(ENOSYS);

    map = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!map)
        ਵਾਪਸ AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_ਚੌਖਟਾ(ctx, map, src, AV_HWFRAME_MAP_READ);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    ਲਈ (i = 0; i < 4; i++) {
        dst_linesize[i] = dst->linesize[i];
        src_linesize[i] = map->linesize[i];
    }
    av_image_copy_uc_from(dst->ਅੰਕੜੇ, dst_linesize, (ਅਚਲ uint8_t **)map->ਅੰਕੜੇ, src_linesize,
                          ctx->sw_format, src->ਚੌੜਾਈ, src->ਉਚਾਈ);
fail:
    av_ਚੌਖਟਾ_free(&map);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ dxva2_map_from(AVHWFramesContext *ctx,
                          AVFrame *dst, ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    ਪੂਰਨ err;

    ਜੇ (dst->format != AV_PIX_FMT_NONE && dst->format != ctx->sw_format)
        ਵਾਪਸ AVERROR(ENOSYS);
    dst->format = ctx->sw_format;

    err = dxva2_map_ਚੌਖਟਾ(ctx, dst, src, flags);
    ਜੇ (err < 0)
        ਵਾਪਸ err;

    err = av_ਚੌਖਟਾ_copy_props(dst, src);
    ਜੇ (err < 0)
        ਵਾਪਸ err;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ dxva2_device_free(AVHWDeviceContext *ctx)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv       *priv = ctx->user_opaque;

    ਜੇ (hwctx->devmgr && priv->device_handle != INVALID_HANDLE_ਮੁੱਲ)
        IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, priv->device_handle);

    ਜੇ (hwctx->devmgr)
        IDirect3DDeviceManager9_Release(hwctx->devmgr);

    ਜੇ (priv->d3d9device)
        IDirect3DDevice9_Release(priv->d3d9device);

    ਜੇ (priv->d3d9)
        IDirect3D9_Release(priv->d3d9);

    ਜੇ (priv->d3dlib)
        dlclose(priv->d3dlib);

    ਜੇ (priv->dxva2lib)
        dlclose(priv->dxva2lib);

    av_freep(&ctx->user_opaque);
}

ਸਥਿਰ ਪੂਰਨ dxva2_device_create9(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODE d3ddm;
    HRESULT hr;
    pDirect3DCreate9 *createD3D = (pDirect3DCreate9 *)dlsym(priv->d3dlib, "Direct3DCreate9");
    ਜੇ (!createD3D) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate Direct3DCreate9\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    priv->d3d9 = createD3D(D3_D_SDK_ਸੰਸਕਰਣ);
    ਜੇ (!priv->d3d9) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create IDirect3D object\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    IDirect3_D9_Get_Adapter_Display_ਬਹੁਲਕ(priv->d3d9, adapter, &d3ddm);

    d3dpp.ਪਿੱਠ_ਬਫਰ_Format = d3ddm.Format;

    hr = IDirect3D9_CreateDevice(priv->d3d9, adapter, D3DDEVTYPE_HAL, Get_Desktop_ਖਿੜਕੀ(),
                                 FF_D3DCREATE_FLAGS,
                                 &d3dpp, &priv->d3d9device);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ dxva2_device_create9ex(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODEEX modeex = {0};
    IDirect3D9Ex *d3d9ex = ਨਿਰਾ;
    IDirect3DDevice9Ex *exdev = ਨਿਰਾ;
    HRESULT hr;
    pDirect3DCreate9Ex *createD3DEx = (pDirect3DCreate9Ex *)dlsym(priv->d3dlib, "Direct3DCreate9Ex");
    ਜੇ (!createD3DEx)
        ਵਾਪਸ AVERROR(ENOSYS);

    hr = createD3DEx(D3_D_SDK_ਸੰਸਕਰਣ, &d3d9ex);
    ਜੇ (FAILED(hr))
        ਵਾਪਸ AVERROR_UNKNOWN;

    modeex.ਮਾਪ_3 = ਆਕਾਰ(D3DDISPLAYMODEEX);
    hr = IDirect3_D9_Ex_Get_Adapter_Display_ਬਹੁਲਕ_Ex(d3d9ex, adapter, &modeex, ਨਿਰਾ);
    ਜੇ (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    d3dpp.ਪਿੱਠ_ਬਫਰ_Format = modeex.Format;

    hr = IDirect3D9Ex_CreateDeviceEx(d3d9ex, adapter, D3DDEVTYPE_HAL, Get_Desktop_ਖਿੜਕੀ(),
                                     FF_D3DCREATE_FLAGS,
                                     &d3dpp, ਨਿਰਾ, &exdev);
    ਜੇ (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Using D3D9Ex device.\n");
    priv->d3d9 = (IDirect3D9 *)d3d9ex;
    priv->d3d9device = (IDirect3DDevice9 *)exdev;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ dxva2_device_create(AVHWDeviceContext *ctx, ਅਚਲ ਅੱਖਰ *device,
                               AVDictionary *opts, ਪੂਰਨ flags)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv *priv;
    pCreateDeviceManager9 *createDeviceManager = ਨਿਰਾ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ resetToken = 0;
    UINT adapter = D3DADAPTER_DEFAULT;
    HRESULT hr;
    ਪੂਰਨ err;

    ਜੇ (device)
        adapter = atoi(device);

    priv = av_mallocz(ਆਕਾਰ(*priv));
    ਜੇ (!priv)
        ਵਾਪਸ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ਮੁਕਤ        = dxva2_device_free;

    priv->device_handle = INVALID_HANDLE_ਮੁੱਲ;

    priv->d3dlib = dlopen("d3d9.dll", 0);
    ਜੇ (!priv->d3dlib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D9 library\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }
    priv->dxva2lib = dlopen("dxva2.dll", 0);
    ਜੇ (!priv->dxva2lib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load DXVA2 library\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    createDeviceManager = (pCreateDeviceManager9 *)dlsym(priv->dxva2lib,
                                                         "DXVA2CreateDirect3DDeviceManager9");
    ਜੇ (!createDeviceManager) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate DXVA2CreateDirect3DDeviceManager9\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਜੇ (dxva2_device_create9ex(ctx, adapter) < 0) {
        // Retry with "classic" d3d9
        err = dxva2_device_create9(ctx, adapter);
        ਜੇ (err < 0)
            ਵਾਪਸ err;
    }

    hr = createDeviceManager(&resetToken, &hwctx->devmgr);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device manager\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_ResetDevice(hwctx->devmgr, priv->d3d9device, resetToken);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind Direct3D device to device manager\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &priv->device_handle);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਵਾਪਸ 0;
}

ਅਚਲ HWContextType ff_hwcontext_type_dxva2 = {
    .type                 = AV_HWDEVICE_TYPE_DXVA2,
    .name                 = "DXVA2",

    .device_hwctx_ਮਾਪ    = ਆਕਾਰ(AVDXVA2DeviceContext),
    .ਚੌਖਟੇ_hwctx_ਮਾਪ    = ਆਕਾਰ(DXVA2_ਚੌਖਟੇ_Context),

    .device_create        = dxva2_device_create,
    .ਚੌਖਟੇ_init          = dxva2_ਚੌਖਟੇ_init,
    .ਚੌਖਟੇ_uninit        = dxva2_ਚੌਖਟੇ_uninit,
    .ਚੌਖਟੇ_get_ਬਫਰ    = dxva2_get_ਬਫਰ,
    .transfer_get_formats = dxva2_transfer_get_formats,
    .transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ     = dxva2_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ,
    .transfer_ਅੰਕੜੇ_from   = dxva2_transfer_ਅੰਕੜੇ_from,
    .map_from             = dxva2_map_from,

    .pix_fmts             = (ਅਚਲ ਗਿਣਤੀ AVPixelFormat[]){ AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_NONE },
};
