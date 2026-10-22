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

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ <windows.h>

#ವ್ಯಾಖ್ಯಾನಿಸು COBJMACROS

#ಅನ್ತರ್ಭಾವ <initguid.h>
#ಅನ್ತರ್ಭಾವ <d3d11.h>
#ಅನ್ತರ್ಭಾವ <dxgi1_2.h>

#ಆದರೆ HAVE_DXGIDEBUG_H
#ಅನ್ತರ್ಭಾವ <dxgidebug.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_d3d11va.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "imgutils.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"
#ಅನ್ತರ್ಭಾವ "thread.h"
#ಅನ್ತರ್ಭಾವ "compat/w32dlfcn.h"

#ವ್ಯಾಖ್ಯಾನಿಸು MAX_ARRAY_ಗಾತ್ರ 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, ಶೂನ್ಯ **ppFactory);

ಸ್ಥಿರ AVOnce functions_loaded = AV_ONCE_INIT;

ಸ್ಥಿರ PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
ಸ್ಥಿರ PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

ಸ್ಥಿರ av_cold ಶೂನ್ಯ ತುಂಬು_functions(ಶೂನ್ಯ)
{
#ಆದರೆ !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    ಆದರೆ (!d3dlib || !dxgilib)
        ಹಿಂತಿರುಗಿ;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) Get_Proc_ವಿಳಾಸ(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) Get_Proc_ವಿಳಾಸ(dxgilib, "CreateDXGIFactory1");
    ಆದರೆ (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) Get_Proc_ವಿಳಾಸ(dxgilib, "CreateDXGIFactory");
#ಇಲ್ಲದಿದ್ದರೆ
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#ಆದರೆ_ಅಂತ್ಯ
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    ಪೂರ್ಣಾಂಕ nb_surfaces;
    ಪೂರ್ಣಾಂಕ nb_surfaces_ಬಳಸಿದ;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    DXGI_FORMAT d3d_format;
    ಎಣಿಕೆ AVPixelFormat pix_fmt;
} supported_formats[] = {
    { DXGI_FORMAT_NV12,         AV_PIX_FMT_NV12 },
    { DXGI_FORMAT_P010,         AV_PIX_FMT_P010 },
    { DXGI_FORMAT_B8G8R8A8_UNORM,    AV_PIX_FMT_BGRA },
    { DXGI_FORMAT_R10G10B10A2_UNORM, AV_PIX_FMT_X2BGR10 },
    { DXGI_FORMAT_R16G16B16A16_FLOAT, AV_PIX_FMT_RGBAF16 },
    { DXGI_FORMAT_AYUV,         AV_PIX_FMT_VUYX },
    { DXGI_FORMAT_YUY2,         AV_PIX_FMT_YUYV422 },
    { DXGI_FORMAT_Y210,         AV_PIX_FMT_Y210 },
    { DXGI_FORMAT_Y410,         AV_PIX_FMT_XV30 },
    { DXGI_FORMAT_P016,         AV_PIX_FMT_P016 },
    { DXGI_FORMAT_Y216,         AV_PIX_FMT_Y216 },
    { DXGI_FORMAT_Y416,         AV_PIX_FMT_XV48 },
    // There is no 12bit pixel format defined in DXGI_FORMAT*, use 16bit to compatible
    // with 12 bit AV_PIX_FMT* formats.
    { DXGI_FORMAT_P016,         AV_PIX_FMT_P012 },
    { DXGI_FORMAT_Y216,         AV_PIX_FMT_Y212 },
    { DXGI_FORMAT_Y416,         AV_PIX_FMT_XV36 },
    // Special opaque formats. The pix_fmt is merely a place holder, as the
    // opaque format cannot be accessed directly.
    { DXGI_FORMAT_420_OPAQUE,   AV_PIX_FMT_YUV420P },
};

ಸ್ಥಿರ ಶೂನ್ಯ d3d11va_default_ಬೀಗ(ಶೂನ್ಯ *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

ಸ್ಥಿರ ಶೂನ್ಯ d3d11va_default_unlock(ಶೂನ್ಯ *ctx)
{
    ReleaseMutex(ctx);
}

ಸ್ಥಿರ ಶೂನ್ಯ d3d11va_ಚೌಕಟ್ಟುಗಳು_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *ಚೌಕಟ್ಟುಗಳು_hwctx = &s->p;

    ಆದರೆ (ಚೌಕಟ್ಟುಗಳು_hwctx->texture)
        ID3D11Texture2D_Release(ಚೌಕಟ್ಟುಗಳು_hwctx->texture);
    ಚೌಕಟ್ಟುಗಳು_hwctx->texture = ಖಾಲಿ;

    ಆದರೆ (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = ಖಾಲಿ;

    av_freep(&ಚೌಕಟ್ಟುಗಳು_hwctx->texture_infos);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d11va_ಚೌಕಟ್ಟುಗಳು_get_constraints(AVHWDeviceContext *ctx,
                                          ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    ಪೂರ್ಣಾಂಕ nb_sw_formats = 0;
    HRESULT hr;
    ಪೂರ್ಣಾಂಕ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    ಗಾತ್ರ(*constraints->valid_sw_formats));
    ಆದರೆ (!constraints->valid_sw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        ಆದರೆ (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ಗಾತ್ರ(*constraints->valid_hw_formats));
    ಆದರೆ (!constraints->valid_hw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ free_texture(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(ದತ್ತಾಂಶ);
}

ಸ್ಥಿರ AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ)
{
    AVBufferRef *buf;
    AVD3_D11_ಚೌಕಟ್ಟು_Descriptor         *desc = av_mallocz(ಗಾತ್ರ(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *ಚೌಕಟ್ಟುಗಳು_hwctx = &s->p;
    ಆದರೆ (!desc) {
        ID3D11Texture2D_Release(tex);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (s->nb_surfaces <= s->nb_surfaces_ಬಳಸಿದ) {
        ಚೌಕಟ್ಟುಗಳು_hwctx->texture_infos = av_realloc_f(ಚೌಕಟ್ಟುಗಳು_hwctx->texture_infos,
                                                   s->nb_surfaces_ಬಳಸಿದ + 1,
                                                   ಗಾತ್ರ(*ಚೌಕಟ್ಟುಗಳು_hwctx->texture_infos));
        ಆದರೆ (!ಚೌಕಟ್ಟುಗಳು_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        s->nb_surfaces = s->nb_surfaces_ಬಳಸಿದ + 1;
    }

    ಚೌಕಟ್ಟುಗಳು_hwctx->texture_infos[s->nb_surfaces_ಬಳಸಿದ].texture = tex;
    ಚೌಕಟ್ಟುಗಳು_hwctx->texture_infos[s->nb_surfaces_ಬಳಸಿದ].ಸೂಚ್ಯಂಕ = ಸೂಚ್ಯಂಕ;
    s->nb_surfaces_ಬಳಸಿದ++;

    desc->texture = tex;
    desc->ಸೂಚ್ಯಂಕ   = ಸೂಚ್ಯಂಕ;

    buf = av_ಬಫರ್_create((uint8_t *)desc, ಗಾತ್ರ(*desc), free_texture, tex, 0);
    ಆದರೆ (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ buf;
}

ಸ್ಥಿರ AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    HRESULT hr;
    ID3D11Texture2D *tex;
    D3D11_TEXTURE2D_DESC texDesc = {
        .ಅಗಲ_2      = ctx->ಅಗಲ,
        .ಎತ್ತರ_2     = ctx->ಎತ್ತರ,
        .Mip_ಮಟ್ಟಗಳು  = 1,
        .Format     = s->format,
        .SampleDesc = { .ಎಣಿಕೆ_3 = 1 },
        .Array_ಗಾತ್ರ  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ಖಾಲಿ, &tex);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (ದೀರ್ಘ)hr);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ wrap_texture_buf(ctx, tex, 0);
}

ಸ್ಥಿರ AVBufferRef *d3d11va_pool_alloc(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    ಆದರೆ (!hwctx->texture)
        ಹಿಂತಿರುಗಿ d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    ಆದರೆ (s->nb_surfaces_ಬಳಸಿದ >= texDesc.Array_ಗಾತ್ರ) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ID3_D11_Texture2_D_ಕೂಡಿಸು_Ref(hwctx->texture);
    ಹಿಂತಿರುಗಿ wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_ಬಳಸಿದ);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d11va_ಚೌಕಟ್ಟುಗಳು_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    ಪೂರ್ಣಾಂಕ i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

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

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    ಆದರೆ (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_ಗಾತ್ರ = FFMIN(ctx->initial_pool_ಗಾತ್ರ, MAX_ARRAY_ಗಾತ್ರ);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .ಅಗಲ_2      = ctx->ಅಗಲ,
        .ಎತ್ತರ_2     = ctx->ಎತ್ತರ,
        .Mip_ಮಟ್ಟಗಳು  = 1,
        .Format     = s->format,
        .SampleDesc = { .ಎಣಿಕೆ_3 = 1 },
        .Array_ಗಾತ್ರ  = ctx->initial_pool_ಗಾತ್ರ,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    ಆದರೆ (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        ಆದರೆ (texDesc.ಅಗಲ_2 != texDesc2.ಅಗಲ_2 ||
            texDesc.ಎತ್ತರ_2 != texDesc2.ಎತ್ತರ_2 ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }

        ctx->initial_pool_ಗಾತ್ರ = texDesc2.Array_ಗಾತ್ರ;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (texDesc.Array_ಗಾತ್ರ > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ಖಾಲಿ, &hwctx->texture);
        ಆದರೆ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (ದೀರ್ಘ)hr);
            ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(ಖಾಲಿ, ctx->initial_pool_ಗಾತ್ರ, ಗಾತ್ರ(*hwctx->texture_infos));
    ಆದರೆ (!hwctx->texture_infos)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_ಗಾತ್ರ;

    ffhwframesctx(ctx)->pool_ಆಂತರಿಕ =
        av_ಬಫರ್_pool_init2(ಗಾತ್ರ(AVD3_D11_ಚೌಕಟ್ಟು_Descriptor),
                             ctx, d3d11va_pool_alloc, ಖಾಲಿ);
    ಆದರೆ (!ffhwframesctx(ctx)->pool_ಆಂತರಿಕ)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d11va_get_ಬಫರ್(AVHWFramesContext *ctx, AVFrame *ಚೌಕಟ್ಟು)
{
    AVD3_D11_ಚೌಕಟ್ಟು_Descriptor *desc;

    ಚೌಕಟ್ಟು->buf[0] = av_ಬಫರ್_pool_get(ctx->pool);
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0])
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    desc = (AVD3_D11_ಚೌಕಟ್ಟು_Descriptor *)ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ;

    ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] = (uint8_t *)desc->texture;
    ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[1] = (uint8_t *)desc->ಸೂಚ್ಯಂಕ;
    ಚೌಕಟ್ಟು->format  = AV_PIX_FMT_D3D11;
    ಚೌಕಟ್ಟು->ಅಗಲ   = ctx->ಅಗಲ;
    ಚೌಕಟ್ಟು->ಎತ್ತರ  = ctx->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                        ಎಣಿಕೆ AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    ಎಣಿಕೆ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ಗಾತ್ರ(*fmts));
    ಆದರೆ (!fmts)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    ಆದರೆ (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .ಅಗಲ_2          = ctx->ಅಗಲ,
        .ಎತ್ತರ_2         = ctx->ಎತ್ತರ,
        .Mip_ಮಟ್ಟಗಳು      = 1,
        .Format         = format,
        .SampleDesc     = { .ಎಣಿಕೆ_3 = 1 },
        .Array_ಗಾತ್ರ      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ಖಾಲಿ, &s->staging_texture);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (ದೀರ್ಘ)hr);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ fill_texture_ptrs(uint8_t *ದತ್ತಾಂಶ[4], ಪೂರ್ಣಾಂಕ linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < 4; i++)
        linesize[i] = map->ಅಡ್ಡಸಾಲು_Pitch;

    av_image_fill_ಸೂಚಕಗಳು(ದತ್ತಾಂಶ, ctx->sw_format, desc->ಎತ್ತರ_2,
                           (uint8_t*)map->p_ದತ್ತಾಂಶ, linesize);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d11va_transfer_ದತ್ತಾಂಶ(AVHWFramesContext *ctx, AVFrame *dst,
                                 ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    ಪೂರ್ಣಾಂಕ download = src->format == AV_PIX_FMT_D3D11;
    ಸ್ಥಿರಾಂಕ AVFrame *ಚೌಕಟ್ಟು = download ? src : dst;
    ಸ್ಥಿರಾಂಕ AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0];
    ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ = (intptr_t)ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[1];
    ID3D11Resource *staging;
    ಪೂರ್ಣಾಂಕ w = FFMIN(dst->ಅಗಲ,  src->ಅಗಲ);
    ಪೂರ್ಣಾಂಕ h = FFMIN(dst->ಎತ್ತರ, src->ಎತ್ತರ);
    uint8_t *map_ದತ್ತಾಂಶ[4];
    ಪೂರ್ಣಾಂಕ map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    ಪೂರ್ಣಾಂಕ res;

    ಆದರೆ (ಚೌಕಟ್ಟು->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ != (uint8_t *)ctx || other->format != ctx->sw_format)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    device_hwctx->ಬೀಗ_2(device_hwctx->ಬೀಗ_ctx);

    ಆದರೆ (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        ಆದರೆ (res < 0)
            ಹಿಂತಿರುಗಿ res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    ಆದರೆ (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, ಸೂಚ್ಯಂಕ, ಖಾಲಿ);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        ಆದರೆ (FAILED(hr))
            ಹೋಗು map_failed;

        fill_texture_ptrs(map_ದತ್ತಾಂಶ, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->ದತ್ತಾಂಶ, dst->linesize, map_ದತ್ತಾಂಶ, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } ಇಲ್ಲದಿದ್ದರೆ {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        ಆದರೆ (FAILED(hr))
            ಹೋಗು map_failed;

        fill_texture_ptrs(map_ದತ್ತಾಂಶ, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_ದತ್ತಾಂಶ, map_linesize, src->ದತ್ತಾಂಶ, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, ಸೂಚ್ಯಂಕ, 0, 0, 0,
                                                  staging, 0, ಖಾಲಿ);
    }

    device_hwctx->unlock(device_hwctx->ಬೀಗ_ctx);
    ಹಿಂತಿರುಗಿ 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (ದೀರ್ಘ)hr);
    device_hwctx->unlock(device_hwctx->ಬೀಗ_ctx);
    ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    ಆದರೆ (!device_hwctx->ಬೀಗ_2) {
        device_hwctx->ಬೀಗ_ctx = CreateMutex(ಖಾಲಿ, 0, ಖಾಲಿ);
        ಆದರೆ (device_hwctx->ಬೀಗ_ctx == INVALID_HANDLE_ಮೌಲ್ಯ) {
            av_log(ಖಾಲಿ, AV_LOG_ERROR, "Failed to create a mutex\n");
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
        device_hwctx->ಬೀಗ_2   = d3d11va_default_ಬೀಗ;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    ಆದರೆ (!device_hwctx->device_context) {
        ID3_D11_Device_Get_ತಕ್ಷಣ_Context(device_hwctx->device, &device_hwctx->device_context);
        ಆದರೆ (!device_hwctx->device_context)
            ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಆದರೆ (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (ಶೂನ್ಯ **)&device_hwctx->video_device);
        ಆದರೆ (FAILED(hr))
            ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಆದರೆ (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (ಶೂನ್ಯ **)&device_hwctx->video_context);
        ಆದರೆ (FAILED(hr))
            ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    ಆದರೆ (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = ಖಾಲಿ;
    }

    ಆದರೆ (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = ಖಾಲಿ;
    }

    ಆದರೆ (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = ಖಾಲಿ;
    }

    ಆದರೆ (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = ಖಾಲಿ;
    }

    ಆದರೆ (device_hwctx->ಬೀಗ_2 == d3d11va_default_ಬೀಗ) {
        CloseHandle(device_hwctx->ಬೀಗ_ctx);
        device_hwctx->ಬೀಗ_ctx = INVALID_HANDLE_ಮೌಲ್ಯ;
        device_hwctx->ಬೀಗ_2 = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d11va_device_ಕಂಡುಹಿಡಿ_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = ಖಾಲಿ;
    IDXGIFactory2 *factory;
    ಪೂರ್ಣಾಂಕ adapter_id = 0;
    ದೀರ್ಘ ಪೂರ್ಣಾಂಕ id = strtol(vendor_id, ಖಾಲಿ, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (ಶೂನ್ಯ **)&factory);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        ಹಿಂತಿರುಗಿ -1;
    }

    ಆಗ (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_ಸಿಕ್ಕಿತು) {
        ID3D11Device* device = ಖಾಲಿ;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, ಖಾಲಿ, flags, ಖಾಲಿ, 0, D3_D11_SDK_ಆವೃತ್ತಿ, &device, ಖಾಲಿ, ಖಾಲಿ);
        ಆದರೆ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            ಮುಂದುವರಿ;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        ಆದರೆ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            ಹಿಂತಿರುಗಿ adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    ಹಿಂತಿರುಗಿ -1;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d11va_device_create(AVHWDeviceContext *ctx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                                 AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = ಖಾಲಿ;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    ಪೂರ್ಣಾಂಕ is_debug       = !!av_dict_get(opts, "debug", ಖಾಲಿ, 0);
    ಪೂರ್ಣಾಂಕ ret;
    ಪೂರ್ಣಾಂಕ adapter = -1;

    ಆದರೆ (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    ಆದರೆ ((ret = ff_thread_once(&functions_loaded, ತುಂಬು_functions)) != 0)
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    ಆದರೆ (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಆದರೆ (device) {
        adapter = atoi(device);
    } ಇಲ್ಲದಿದ್ದರೆ {
        AVDictionary_ನಮೂದು *e = av_dict_get(opts, "vendor_id", ಖಾಲಿ, 0);
        ಆದರೆ (e && e->ಮೌಲ್ಯ) {
            adapter = d3d11va_device_ಕಂಡುಹಿಡಿ_adapter_by_vendor_id(ctx, creationFlags, e->ಮೌಲ್ಯ);
            ಆದರೆ (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->ಮೌಲ್ಯ);
                ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
            }
        }
    }

    ಆದರೆ (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (ಶೂನ್ಯ **)&pDXGIFactory);
        ಆದರೆ (SUCCEEDED(hr)) {
            ಆದರೆ (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = ಖಾಲಿ;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    ಆದರೆ (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        ಆದರೆ (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, ಖಾಲಿ, creationFlags, ಖಾಲಿ, 0,
                   D3_D11_SDK_ಆವೃತ್ತಿ, &device_hwctx->device, ಖಾಲಿ, ಖಾಲಿ);
    ಆದರೆ (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (ದೀರ್ಘ)hr);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (ಶೂನ್ಯ **)&pMultithread);
    ಆದರೆ (SUCCEEDED(hr)) {
        ID3_D10_Multithread_ಗಣ_Multithread_Protected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#ಆದರೆ !HAVE_UWP && HAVE_DXGIDEBUG_H
    ಆದರೆ (is_debug) {
        HANDLE dxgidebug_dll = ತುಂಬು_Library("dxgidebug.dll");
        ಆದರೆ (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(ಸ್ಥಿರಾಂಕ GUID *riid, ಶೂನ್ಯ **ppDebug)
                = (ಶೂನ್ಯ *)Get_Proc_ವಿಳಾಸ(dxgidebug_dll, "DXGIGetDebugInterface");
            ಆದರೆ (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = ಖಾಲಿ;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (ಶೂನ್ಯ**)&dxgi_debug);
                ಆದರೆ (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_Report_ಜೀವಂತ_Objects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } ಇಲ್ಲದಿದ್ದರೆ {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (av_dict_get(opts, "SHADER", ಖಾಲಿ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    ಆದರೆ (av_dict_get(opts, "UAV", ಖಾಲಿ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    ಆದರೆ (av_dict_get(opts, "RTV", ಖಾಲಿ, 0))
        device_hwctx->BindFlags |= D3_D11_BIND_RENDER_ಗುರಿ;

    ಆದರೆ (av_dict_get(opts, "SHARED", ಖಾಲಿ, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_ಗಾತ್ರ    = ಗಾತ್ರ(AVD3D11VADeviceContext),
    .ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ    = ಗಾತ್ರ(D3D11VAFramesContext),

    .device_create        = d3d11va_device_create,
    .device_init          = d3d11va_device_init,
    .device_uninit        = d3d11va_device_uninit,
    .ಚೌಕಟ್ಟುಗಳು_get_constraints = d3d11va_ಚೌಕಟ್ಟುಗಳು_get_constraints,
    .ಚೌಕಟ್ಟುಗಳು_init          = d3d11va_ಚೌಕಟ್ಟುಗಳು_init,
    .ಚೌಕಟ್ಟುಗಳು_uninit        = d3d11va_ಚೌಕಟ್ಟುಗಳು_uninit,
    .ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್    = d3d11va_get_ಬಫರ್,
    .transfer_get_formats = d3d11va_transfer_get_formats,
    .transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ     = d3d11va_transfer_ದತ್ತಾಂಶ,
    .transfer_ದತ್ತಾಂಶ_from   = d3d11va_transfer_ದತ್ತಾಂಶ,

    .pix_fmts             = (ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
