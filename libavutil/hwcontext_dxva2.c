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

#ವ್ಯಾಖ್ಯಾನಿಸು DXVA2API_USE_BITFIELDS
#ವ್ಯಾಖ್ಯಾನಿಸು COBJMACROS

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

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ IDirect3D9* WINAPI pDirect3DCreate9(UINT);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HRESULT WINAPI pDirect3DCreate9Ex(UINT, IDirect3D9Ex **);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HRESULT WINAPI pCreateDeviceManager9(UINT *, IDirect3DDeviceManager9 **);

#ವ್ಯಾಖ್ಯಾನಿಸು FF_D3DCREATE_FLAGS (D3DCREATE_SOFTWARE_VERTEXPROCESSING | \
                            D3DCREATE_MULTITHREADED | \
                            D3DCREATE_FPU_PRESERVE)

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ D3DPRESENT_PARAMETERS dxva2_present_params = {
    .Windowed         = TRUE,
    .ಹಿಂಭಾಗ_ಬಫರ್_ಅಗಲ  = 640,
    .ಹಿಂಭಾಗ_ಬಫರ್_ಎತ್ತರ = 480,
    .ಹಿಂಭಾಗ_ಬಫರ್_ಎಣಿಕೆ  = 0,
    .ಅದಲುಬದಲು_Effect       = D3DSWAPEFFECT_DISCARD,
    .Flags            = D3DPRESENTFLAG_VIDEO,
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DXVA2Mapping {
    uint32_t palette_dummy[256];
} DXVA2Mapping;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DXVA2_ಚೌಕಟ್ಟುಗಳು_Context {
    /**
     * The public AVDXVA2FramesContext. See hwcontext_dxva2.h for it.
     */
    AVDXVA2_ಚೌಕಟ್ಟುಗಳು_Context p;

    IDirect3DSurface9 **surfaces_ಆಂತರಿಕ;
    ಪೂರ್ಣಾಂಕ              nb_surfaces_ಬಳಸಿದ;

    HANDLE  device_handle;
    IDirectXVideoAccelerationService *service;

    D3DFORMAT format;
} DXVA2_ಚೌಕಟ್ಟುಗಳು_Context;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DXVA2DevicePriv {
    HMODULE d3dlib;
    HMODULE dxva2lib;

    HANDLE device_handle;

    IDirect3D9       *d3d9;
    IDirect3DDevice9 *d3d9device;
} DXVA2DevicePriv;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    D3DFORMAT d3d_format;
    ಎಣಿಕೆ AVPixelFormat pix_fmt;
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

ಸ್ಥಿರ ಶೂನ್ಯ dxva2_ಚೌಕಟ್ಟುಗಳು_uninit(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2_ಚೌಕಟ್ಟುಗಳು_Context              *s = ctx->hwctx;
    AVDXVA2_ಚೌಕಟ್ಟುಗಳು_Context *ಚೌಕಟ್ಟುಗಳು_hwctx = &s->p;
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (ಚೌಕಟ್ಟುಗಳು_hwctx->decoder_ಗಮ್ಯ_release)
        IDirectXVideoDecoder_Release(ಚೌಕಟ್ಟುಗಳು_hwctx->decoder_ಗಮ್ಯ_release);

    ಆದರೆ (s->surfaces_ಆಂತರಿಕ) {
        ಗಾಗಿ (i = 0; i < ಚೌಕಟ್ಟುಗಳು_hwctx->nb_surfaces; i++) {
            ಆದರೆ (s->surfaces_ಆಂತರಿಕ[i])
                IDirect3DSurface9_Release(s->surfaces_ಆಂತರಿಕ[i]);
        }
    }
    av_freep(&s->surfaces_ಆಂತರಿಕ);

    ಆದರೆ (s->service) {
        IDirectXVideoAccelerationService_Release(s->service);
        s->service = ಖಾಲಿ;
    }

    ಆದರೆ (s->device_handle != INVALID_HANDLE_ಮೌಲ್ಯ) {
        IDirect3DDeviceManager9_CloseDeviceHandle(device_hwctx->devmgr, s->device_handle);
        s->device_handle = INVALID_HANDLE_ಮೌಲ್ಯ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ dxva2_pool_release_dummy(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    // important not to free anything here--data is a surface object
    // associated with the call to CreateSurface(), and these surfaces are
    // released in dxva2_frames_uninit()
}

ಸ್ಥಿರ AVBufferRef *dxva2_pool_alloc(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    AVHWFramesContext      *ctx = (AVHWFramesContext*)opaque;
    DXVA2_ಚೌಕಟ್ಟುಗಳು_Context       *s = ctx->hwctx;
    AVDXVA2_ಚೌಕಟ್ಟುಗಳು_Context *hwctx = &s->p;

    ಆದರೆ (s->nb_surfaces_ಬಳಸಿದ < hwctx->nb_surfaces) {
        s->nb_surfaces_ಬಳಸಿದ++;
        ಹಿಂತಿರುಗಿ av_ಬಫರ್_create((uint8_t*)s->surfaces_ಆಂತರಿಕ[s->nb_surfaces_ಬಳಸಿದ - 1],
                                ಗಾತ್ರ(**hwctx->surfaces), dxva2_pool_release_dummy, 0, 0);
    }

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ dxva2_init_pool(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2_ಚೌಕಟ್ಟುಗಳು_Context              *s = ctx->hwctx;
    AVDXVA2_ಚೌಕಟ್ಟುಗಳು_Context *ಚೌಕಟ್ಟುಗಳು_hwctx = &s->p;
    ಪೂರ್ಣಾಂಕ decode = (ಚೌಕಟ್ಟುಗಳು_hwctx->surface_type == DXVA2_Video_Decoder_Render_ಗುರಿ);

    ಪೂರ್ಣಾಂಕ i;
    HRESULT hr;

    ಆದರೆ (ctx->initial_pool_ಗಾತ್ರ <= 0)
        ಹಿಂತಿರುಗಿ 0;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(device_hwctx->devmgr, &s->device_handle);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_GetVideoService(device_hwctx->devmgr,
                                                 s->device_handle,
                                                 decode ? &video_decoder_service : &video_processor_service,
                                                 (ಶೂನ್ಯ **)&s->service);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create the video service\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ಆದರೆ (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            ನಿಲ್ಲಿಸು;
        }
    }
    ಆದರೆ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    s->surfaces_ಆಂತರಿಕ = av_calloc(ctx->initial_pool_ಗಾತ್ರ,
                                     ಗಾತ್ರ(*s->surfaces_ಆಂತರಿಕ));
    ಆದರೆ (!s->surfaces_ಆಂತರಿಕ)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    hr = IDirectXVideoAccelerationService_CreateSurface(s->service,
                                                        ctx->ಅಗಲ, ctx->ಎತ್ತರ,
                                                        ctx->initial_pool_ಗಾತ್ರ - 1,
                                                        s->format, D3DPOOL_DEFAULT, 0,
                                                        ಚೌಕಟ್ಟುಗಳು_hwctx->surface_type,
                                                        s->surfaces_ಆಂತರಿಕ, ಖಾಲಿ);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the surfaces\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ffhwframesctx(ctx)->pool_ಆಂತರಿಕ =
        av_ಬಫರ್_pool_init2(ಗಾತ್ರ(*s->surfaces_ಆಂತರಿಕ),
                             ctx, dxva2_pool_alloc, ಖಾಲಿ);
    ಆದರೆ (!ffhwframesctx(ctx)->pool_ಆಂತರಿಕ)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಚೌಕಟ್ಟುಗಳು_hwctx->surfaces    = s->surfaces_ಆಂತರಿಕ;
    ಚೌಕಟ್ಟುಗಳು_hwctx->nb_surfaces = ctx->initial_pool_ಗಾತ್ರ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ dxva2_ಚೌಕಟ್ಟುಗಳು_init(AVHWFramesContext *ctx)
{
    DXVA2_ಚೌಕಟ್ಟುಗಳು_Context       *s = ctx->hwctx;
    AVDXVA2_ಚೌಕಟ್ಟುಗಳು_Context *hwctx = &s->p;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (hwctx->surface_type != DXVA2_Video_Decoder_Render_ಗುರಿ &&
        hwctx->surface_type != DXVA2_Video_Processor_Render_ಗುರಿ) {
        av_log(ctx, AV_LOG_ERROR, "Unknown surface type: %lu\n",
               hwctx->surface_type);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    s->device_handle = INVALID_HANDLE_ಮೌಲ್ಯ;

    /* init the frame pool if the caller didn't provide one */
    ಆದರೆ (!ctx->pool) {
        ret = dxva2_init_pool(ctx);
        ಆದರೆ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            ಹಿಂತಿರುಗಿ ret;
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ dxva2_get_ಬಫರ್(AVHWFramesContext *ctx, AVFrame *ಚೌಕಟ್ಟು)
{
    ಚೌಕಟ್ಟು->buf[0] = av_ಬಫರ್_pool_get(ctx->pool);
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0])
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[3] = ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ;
    ಚೌಕಟ್ಟು->format  = AV_PIX_FMT_DXVA2_VLD;
    ಚೌಕಟ್ಟು->ಅಗಲ   = ctx->ಅಗಲ;
    ಚೌಕಟ್ಟು->ಎತ್ತರ  = ctx->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ dxva2_transfer_get_formats(AVHWFramesContext *ctx,
                                      ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                      ಎಣಿಕೆ AVPixelFormat **formats)
{
    ಎಣಿಕೆ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ಗಾತ್ರ(*fmts));
    ಆದರೆ (!fmts)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ dxva2_unmap_ಚೌಕಟ್ಟು(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)hwmap->ಮೂಲ->ದತ್ತಾಂಶ[3];
    IDirect3DSurface9_UnlockRect(surface);
    av_freep(&hwmap->priv);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ dxva2_map_ಚೌಕಟ್ಟು(AVHWFramesContext *ctx, AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src,
                           ಪೂರ್ಣಾಂಕ flags)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->ದತ್ತಾಂಶ[3];
    DXVA2Mapping      *map;
    D3DSURFACE_DESC    surfaceDesc;
    D3DLOCKED_RECT     LockedRect;
    HRESULT            hr;
    ಪೂರ್ಣಾಂಕ i, err, nb_planes;
    ಪೂರ್ಣಾಂಕ ಬೀಗ_flags = 0;

    nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(dst->format);

    hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಆದರೆ (!(flags & AV_HWFRAME_MAP_WRITE))
        ಬೀಗ_flags |= D3DLOCK_READONLY;
    ಆದರೆ (flags & AV_HWFRAME_MAP_OVERWRITE)
        ಬೀಗ_flags |= D3DLOCK_DISCARD;

    hr = IDirect3_DSurface9_ಬೀಗ_Rect(surface, &LockedRect, ಖಾಲಿ, ಬೀಗ_flags);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    map = av_mallocz(ಗಾತ್ರ(*map));
    ಆದರೆ (!map) {
        err = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    err = ff_hwframe_map_create(src->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src,
                                dxva2_unmap_ಚೌಕಟ್ಟು, map);
    ಆದರೆ (err < 0) {
        av_freep(&map);
        ಹೋಗು fail;
    }

    ಗಾಗಿ (i = 0; i < nb_planes; i++)
        dst->linesize[i] = LockedRect.Pitch;

    av_image_fill_ಸೂಚಕಗಳು(dst->ದತ್ತಾಂಶ, dst->format, surfaceDesc.ಎತ್ತರ_2,
                           (uint8_t*)LockedRect.p_ಬಿಟ್ಟುಗಳು, dst->linesize);

    ಆದರೆ (dst->format == AV_PIX_FMT_PAL8)
        dst->ದತ್ತಾಂಶ[1] = (uint8_t*)map->palette_dummy;

    ಹಿಂತಿರುಗಿ 0;
fail:
    IDirect3DSurface9_UnlockRect(surface);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ dxva2_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ(AVHWFramesContext *ctx, AVFrame *dst,
                                  ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (src->format != ctx->sw_format)
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);

    map = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_ಚೌಕಟ್ಟು(ctx, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    av_image_copy2(map->ದತ್ತಾಂಶ, map->linesize, src->ದತ್ತಾಂಶ, src->linesize,
                   ctx->sw_format, src->ಅಗಲ, src->ಎತ್ತರ);

fail:
    av_ಚೌಕಟ್ಟು_free(&map);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ dxva2_transfer_ದತ್ತಾಂಶ_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    AVFrame *map;
    ptrdiff_t src_linesize[4], dst_linesize[4];
    ಪೂರ್ಣಾಂಕ ret, i;

    ಆದರೆ (dst->format != ctx->sw_format)
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);

    map = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_ಚೌಕಟ್ಟು(ctx, map, src, AV_HWFRAME_MAP_READ);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    ಗಾಗಿ (i = 0; i < 4; i++) {
        dst_linesize[i] = dst->linesize[i];
        src_linesize[i] = map->linesize[i];
    }
    av_image_copy_uc_from(dst->ದತ್ತಾಂಶ, dst_linesize, (ಸ್ಥಿರಾಂಕ uint8_t **)map->ದತ್ತಾಂಶ, src_linesize,
                          ctx->sw_format, src->ಅಗಲ, src->ಎತ್ತರ);
fail:
    av_ಚೌಕಟ್ಟು_free(&map);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ dxva2_map_from(AVHWFramesContext *ctx,
                          AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ err;

    ಆದರೆ (dst->format != AV_PIX_FMT_NONE && dst->format != ctx->sw_format)
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    dst->format = ctx->sw_format;

    err = dxva2_map_ಚೌಕಟ್ಟು(ctx, dst, src, flags);
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    err = av_ಚೌಕಟ್ಟು_copy_props(dst, src);
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ dxva2_device_free(AVHWDeviceContext *ctx)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv       *priv = ctx->user_opaque;

    ಆದರೆ (hwctx->devmgr && priv->device_handle != INVALID_HANDLE_ಮೌಲ್ಯ)
        IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, priv->device_handle);

    ಆದರೆ (hwctx->devmgr)
        IDirect3DDeviceManager9_Release(hwctx->devmgr);

    ಆದರೆ (priv->d3d9device)
        IDirect3DDevice9_Release(priv->d3d9device);

    ಆದರೆ (priv->d3d9)
        IDirect3D9_Release(priv->d3d9);

    ಆದರೆ (priv->d3dlib)
        dlclose(priv->d3dlib);

    ಆದರೆ (priv->dxva2lib)
        dlclose(priv->dxva2lib);

    av_freep(&ctx->user_opaque);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ dxva2_device_create9(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODE d3ddm;
    HRESULT hr;
    pDirect3DCreate9 *createD3D = (pDirect3DCreate9 *)dlsym(priv->d3dlib, "Direct3DCreate9");
    ಆದರೆ (!createD3D) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate Direct3DCreate9\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    priv->d3d9 = createD3D(D3_D_SDK_ಆವೃತ್ತಿ);
    ಆದರೆ (!priv->d3d9) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create IDirect3D object\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    IDirect3_D9_Get_Adapter_Display_ಬಹುಲಕ(priv->d3d9, adapter, &d3ddm);

    d3dpp.ಹಿಂಭಾಗ_ಬಫರ್_Format = d3ddm.Format;

    hr = IDirect3D9_CreateDevice(priv->d3d9, adapter, D3DDEVTYPE_HAL, Get_Desktop_ಕಿಟಕಿ(),
                                 FF_D3DCREATE_FLAGS,
                                 &d3dpp, &priv->d3d9device);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ dxva2_device_create9ex(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODEEX modeex = {0};
    IDirect3D9Ex *d3d9ex = ಖಾಲಿ;
    IDirect3DDevice9Ex *exdev = ಖಾಲಿ;
    HRESULT hr;
    pDirect3DCreate9Ex *createD3DEx = (pDirect3DCreate9Ex *)dlsym(priv->d3dlib, "Direct3DCreate9Ex");
    ಆದರೆ (!createD3DEx)
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);

    hr = createD3DEx(D3_D_SDK_ಆವೃತ್ತಿ, &d3d9ex);
    ಆದರೆ (FAILED(hr))
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;

    modeex.ಗಾತ್ರ_4 = ಗಾತ್ರ(D3DDISPLAYMODEEX);
    hr = IDirect3_D9_Ex_Get_Adapter_Display_ಬಹುಲಕ_Ex(d3d9ex, adapter, &modeex, ಖಾಲಿ);
    ಆದರೆ (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    d3dpp.ಹಿಂಭಾಗ_ಬಫರ್_Format = modeex.Format;

    hr = IDirect3D9Ex_CreateDeviceEx(d3d9ex, adapter, D3DDEVTYPE_HAL, Get_Desktop_ಕಿಟಕಿ(),
                                     FF_D3DCREATE_FLAGS,
                                     &d3dpp, ಖಾಲಿ, &exdev);
    ಆದರೆ (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Using D3D9Ex device.\n");
    priv->d3d9 = (IDirect3D9 *)d3d9ex;
    priv->d3d9device = (IDirect3DDevice9 *)exdev;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ dxva2_device_create(AVHWDeviceContext *ctx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                               AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv *priv;
    pCreateDeviceManager9 *createDeviceManager = ಖಾಲಿ;
    ಚಿಹ್ನೆರಹಿತ resetToken = 0;
    UINT adapter = D3DADAPTER_DEFAULT;
    HRESULT hr;
    ಪೂರ್ಣಾಂಕ err;

    ಆದರೆ (device)
        adapter = atoi(device);

    priv = av_mallocz(ಗಾತ್ರ(*priv));
    ಆದರೆ (!priv)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ಬಿಡುಗಡೆ        = dxva2_device_free;

    priv->device_handle = INVALID_HANDLE_ಮೌಲ್ಯ;

    priv->d3dlib = dlopen("d3d9.dll", 0);
    ಆದರೆ (!priv->d3dlib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D9 library\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }
    priv->dxva2lib = dlopen("dxva2.dll", 0);
    ಆದರೆ (!priv->dxva2lib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load DXVA2 library\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    createDeviceManager = (pCreateDeviceManager9 *)dlsym(priv->dxva2lib,
                                                         "DXVA2CreateDirect3DDeviceManager9");
    ಆದರೆ (!createDeviceManager) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate DXVA2CreateDirect3DDeviceManager9\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಆದರೆ (dxva2_device_create9ex(ctx, adapter) < 0) {
        // Retry with "classic" d3d9
        err = dxva2_device_create9(ctx, adapter);
        ಆದರೆ (err < 0)
            ಹಿಂತಿರುಗಿ err;
    }

    hr = createDeviceManager(&resetToken, &hwctx->devmgr);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device manager\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_ResetDevice(hwctx->devmgr, priv->d3d9device, resetToken);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind Direct3D device to device manager\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &priv->device_handle);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_dxva2 = {
    .type                 = AV_HWDEVICE_TYPE_DXVA2,
    .name                 = "DXVA2",

    .device_hwctx_ಗಾತ್ರ    = ಗಾತ್ರ(AVDXVA2DeviceContext),
    .ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ    = ಗಾತ್ರ(DXVA2_ಚೌಕಟ್ಟುಗಳು_Context),

    .device_create        = dxva2_device_create,
    .ಚೌಕಟ್ಟುಗಳು_init          = dxva2_ಚೌಕಟ್ಟುಗಳು_init,
    .ಚೌಕಟ್ಟುಗಳು_uninit        = dxva2_ಚೌಕಟ್ಟುಗಳು_uninit,
    .ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್    = dxva2_get_ಬಫರ್,
    .transfer_get_formats = dxva2_transfer_get_formats,
    .transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ     = dxva2_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ,
    .transfer_ದತ್ತಾಂಶ_from   = dxva2_transfer_ದತ್ತಾಂಶ_from,
    .map_from             = dxva2_map_from,

    .pix_fmts             = (ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat[]){ AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_NONE },
};
