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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <windows.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COBJMACROS

#ਅਨ੍ਤਰ੍ਭਾਵ <initguid.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <d3d11.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <dxgi1_2.h>

#ਜੇ HAVE_DXGIDEBUG_H
#ਅਨ੍ਤਰ੍ਭਾਵ <dxgidebug.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_d3d11va.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "imgutils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "compat/w32dlfcn.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_ARRAY_ਮਾਪ 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

ਕਿਸਮਪਰਿਭਾਸ਼ਾ HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, ਖਾਲੀ **ppFactory);

ਸਥਿਰ AVOnce functions_loaded = AV_ONCE_INIT;

ਸਥਿਰ PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
ਸਥਿਰ PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

ਸਥਿਰ av_cold ਖਾਲੀ ਲੱਦੋ_functions(ਖਾਲੀ)
{
#ਜੇ !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    ਜੇ (!d3dlib || !dxgilib)
        ਵਾਪਸ;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) Get_Proc_ਪਤਾ(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) Get_Proc_ਪਤਾ(dxgilib, "CreateDXGIFactory1");
    ਜੇ (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) Get_Proc_ਪਤਾ(dxgilib, "CreateDXGIFactory");
#ਨਹੀਂਤਾਂ
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#ਜੇ_ਅੰਤ
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    ਪੂਰਨ nb_surfaces;
    ਪੂਰਨ nb_surfaces_ਵਰਤਿਆ;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
    DXGI_FORMAT d3d_format;
    ਗਿਣਤੀ AVPixelFormat pix_fmt;
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

ਸਥਿਰ ਖਾਲੀ d3d11va_default_ਤਾਲਾ(ਖਾਲੀ *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

ਸਥਿਰ ਖਾਲੀ d3d11va_default_unlock(ਖਾਲੀ *ctx)
{
    ReleaseMutex(ctx);
}

ਸਥਿਰ ਖਾਲੀ d3d11va_ਚੌਖਟੇ_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *ਚੌਖਟੇ_hwctx = &s->p;

    ਜੇ (ਚੌਖਟੇ_hwctx->texture)
        ID3D11Texture2D_Release(ਚੌਖਟੇ_hwctx->texture);
    ਚੌਖਟੇ_hwctx->texture = ਨਿਰਾ;

    ਜੇ (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = ਨਿਰਾ;

    av_freep(&ਚੌਖਟੇ_hwctx->texture_infos);
}

ਸਥਿਰ ਪੂਰਨ d3d11va_ਚੌਖਟੇ_get_constraints(AVHWDeviceContext *ctx,
                                          ਅਚਲ ਖਾਲੀ *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    ਪੂਰਨ nb_sw_formats = 0;
    HRESULT hr;
    ਪੂਰਨ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    ਆਕਾਰ(*constraints->valid_sw_formats));
    ਜੇ (!constraints->valid_sw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        ਜੇ (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ਆਕਾਰ(*constraints->valid_hw_formats));
    ਜੇ (!constraints->valid_hw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ free_texture(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(ਅੰਕੜੇ);
}

ਸਥਿਰ AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, ਪੂਰਨ ਸੂਚਕਾਂਕ)
{
    AVBufferRef *buf;
    AVD3_D11_ਚੌਖਟਾ_Descriptor         *desc = av_mallocz(ਆਕਾਰ(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *ਚੌਖਟੇ_hwctx = &s->p;
    ਜੇ (!desc) {
        ID3D11Texture2D_Release(tex);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (s->nb_surfaces <= s->nb_surfaces_ਵਰਤਿਆ) {
        ਚੌਖਟੇ_hwctx->texture_infos = av_realloc_f(ਚੌਖਟੇ_hwctx->texture_infos,
                                                   s->nb_surfaces_ਵਰਤਿਆ + 1,
                                                   ਆਕਾਰ(*ਚੌਖਟੇ_hwctx->texture_infos));
        ਜੇ (!ਚੌਖਟੇ_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            ਵਾਪਸ ਨਿਰਾ;
        }
        s->nb_surfaces = s->nb_surfaces_ਵਰਤਿਆ + 1;
    }

    ਚੌਖਟੇ_hwctx->texture_infos[s->nb_surfaces_ਵਰਤਿਆ].texture = tex;
    ਚੌਖਟੇ_hwctx->texture_infos[s->nb_surfaces_ਵਰਤਿਆ].ਸੂਚਕਾਂਕ = ਸੂਚਕਾਂਕ;
    s->nb_surfaces_ਵਰਤਿਆ++;

    desc->texture = tex;
    desc->ਸੂਚਕਾਂਕ   = ਸੂਚਕਾਂਕ;

    buf = av_ਬਫਰ_create((uint8_t *)desc, ਆਕਾਰ(*desc), free_texture, tex, 0);
    ਜੇ (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ buf;
}

ਸਥਿਰ AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    HRESULT hr;
    ID3D11Texture2D *tex;
    D3D11_TEXTURE2D_DESC texDesc = {
        .ਚੌੜਾਈ_2      = ctx->ਚੌੜਾਈ,
        .ਉਚਾਈ_2     = ctx->ਉਚਾਈ,
        .Mip_ਪੱਧਰ  = 1,
        .Format     = s->format,
        .SampleDesc = { .ਗਿਣਤੀ_3 = 1 },
        .Array_ਮਾਪ  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ਨਿਰਾ, &tex);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (ਲੰਮਾ)hr);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ wrap_texture_buf(ctx, tex, 0);
}

ਸਥਿਰ AVBufferRef *d3d11va_pool_alloc(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    ਜੇ (!hwctx->texture)
        ਵਾਪਸ d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    ਜੇ (s->nb_surfaces_ਵਰਤਿਆ >= texDesc.Array_ਮਾਪ) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ID3_D11_Texture2_D_ਜੋੜੋ_Ref(hwctx->texture);
    ਵਾਪਸ wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_ਵਰਤਿਆ);
}

ਸਥਿਰ ਪੂਰਨ d3d11va_ਚੌਖਟੇ_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    ਪੂਰਨ i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

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

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    ਜੇ (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_ਮਾਪ = FFMIN(ctx->initial_pool_ਮਾਪ, MAX_ARRAY_ਮਾਪ);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .ਚੌੜਾਈ_2      = ctx->ਚੌੜਾਈ,
        .ਉਚਾਈ_2     = ctx->ਉਚਾਈ,
        .Mip_ਪੱਧਰ  = 1,
        .Format     = s->format,
        .SampleDesc = { .ਗਿਣਤੀ_3 = 1 },
        .Array_ਮਾਪ  = ctx->initial_pool_ਮਾਪ,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    ਜੇ (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        ਜੇ (texDesc.ਚੌੜਾਈ_2 != texDesc2.ਚੌੜਾਈ_2 ||
            texDesc.ਉਚਾਈ_2 != texDesc2.ਉਚਾਈ_2 ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            ਵਾਪਸ AVERROR(EINVAL);
        }

        ctx->initial_pool_ਮਾਪ = texDesc2.Array_ਮਾਪ;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } ਨਹੀਂਤਾਂ ਜੇ (texDesc.Array_ਮਾਪ > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ਨਿਰਾ, &hwctx->texture);
        ਜੇ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (ਲੰਮਾ)hr);
            ਵਾਪਸ AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(ਨਿਰਾ, ctx->initial_pool_ਮਾਪ, ਆਕਾਰ(*hwctx->texture_infos));
    ਜੇ (!hwctx->texture_infos)
        ਵਾਪਸ AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_ਮਾਪ;

    ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ =
        av_ਬਫਰ_pool_init2(ਆਕਾਰ(AVD3_D11_ਚੌਖਟਾ_Descriptor),
                             ctx, d3d11va_pool_alloc, ਨਿਰਾ);
    ਜੇ (!ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ d3d11va_get_ਬਫਰ(AVHWFramesContext *ctx, AVFrame *ਚੌਖਟਾ)
{
    AVD3_D11_ਚੌਖਟਾ_Descriptor *desc;

    ਚੌਖਟਾ->buf[0] = av_ਬਫਰ_pool_get(ctx->pool);
    ਜੇ (!ਚੌਖਟਾ->buf[0])
        ਵਾਪਸ AVERROR(ENOMEM);

    desc = (AVD3_D11_ਚੌਖਟਾ_Descriptor *)ਚੌਖਟਾ->buf[0]->ਅੰਕੜੇ;

    ਚੌਖਟਾ->ਅੰਕੜੇ[0] = (uint8_t *)desc->texture;
    ਚੌਖਟਾ->ਅੰਕੜੇ[1] = (uint8_t *)desc->ਸੂਚਕਾਂਕ;
    ਚੌਖਟਾ->format  = AV_PIX_FMT_D3D11;
    ਚੌਖਟਾ->ਚੌੜਾਈ   = ctx->ਚੌੜਾਈ;
    ਚੌਖਟਾ->ਉਚਾਈ  = ctx->ਉਚਾਈ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        ਗਿਣਤੀ AVHWFrameTransferDirection dir,
                                        ਗਿਣਤੀ AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    ਗਿਣਤੀ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ਆਕਾਰ(*fmts));
    ਜੇ (!fmts)
        ਵਾਪਸ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    ਜੇ (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .ਚੌੜਾਈ_2          = ctx->ਚੌੜਾਈ,
        .ਉਚਾਈ_2         = ctx->ਉਚਾਈ,
        .Mip_ਪੱਧਰ      = 1,
        .Format         = format,
        .SampleDesc     = { .ਗਿਣਤੀ_3 = 1 },
        .Array_ਮਾਪ      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ਨਿਰਾ, &s->staging_texture);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (ਲੰਮਾ)hr);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ fill_texture_ptrs(uint8_t *ਅੰਕੜੇ[4], ਪੂਰਨ linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < 4; i++)
        linesize[i] = map->ਪੰਕਤੀ_Pitch;

    av_image_fill_ਸੂਚਕ_ਸਾਰੇ(ਅੰਕੜੇ, ctx->sw_format, desc->ਉਚਾਈ_2,
                           (uint8_t*)map->p_ਅੰਕੜੇ, linesize);
}

ਸਥਿਰ ਪੂਰਨ d3d11va_transfer_ਅੰਕੜੇ(AVHWFramesContext *ctx, AVFrame *dst,
                                 ਅਚਲ AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    ਪੂਰਨ download = src->format == AV_PIX_FMT_D3D11;
    ਅਚਲ AVFrame *ਚੌਖਟਾ = download ? src : dst;
    ਅਚਲ AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)ਚੌਖਟਾ->ਅੰਕੜੇ[0];
    ਪੂਰਨ ਸੂਚਕਾਂਕ = (intptr_t)ਚੌਖਟਾ->ਅੰਕੜੇ[1];
    ID3D11Resource *staging;
    ਪੂਰਨ w = FFMIN(dst->ਚੌੜਾਈ,  src->ਚੌੜਾਈ);
    ਪੂਰਨ h = FFMIN(dst->ਉਚਾਈ, src->ਉਚਾਈ);
    uint8_t *map_ਅੰਕੜੇ[4];
    ਪੂਰਨ map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    ਪੂਰਨ res;

    ਜੇ (ਚੌਖਟਾ->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ != (uint8_t *)ctx || other->format != ctx->sw_format)
        ਵਾਪਸ AVERROR(EINVAL);

    device_hwctx->ਤਾਲਾ(device_hwctx->ਤਾਲਾ_ctx);

    ਜੇ (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        ਜੇ (res < 0)
            ਵਾਪਸ res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    ਜੇ (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, ਸੂਚਕਾਂਕ, ਨਿਰਾ);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        ਜੇ (FAILED(hr))
            ਜਾਓ map_failed;

        fill_texture_ptrs(map_ਅੰਕੜੇ, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->ਅੰਕੜੇ, dst->linesize, map_ਅੰਕੜੇ, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } ਨਹੀਂਤਾਂ {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        ਜੇ (FAILED(hr))
            ਜਾਓ map_failed;

        fill_texture_ptrs(map_ਅੰਕੜੇ, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_ਅੰਕੜੇ, map_linesize, src->ਅੰਕੜੇ, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, ਸੂਚਕਾਂਕ, 0, 0, 0,
                                                  staging, 0, ਨਿਰਾ);
    }

    device_hwctx->unlock(device_hwctx->ਤਾਲਾ_ctx);
    ਵਾਪਸ 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (ਲੰਮਾ)hr);
    device_hwctx->unlock(device_hwctx->ਤਾਲਾ_ctx);
    ਵਾਪਸ AVERROR_UNKNOWN;
}

ਸਥਿਰ ਪੂਰਨ d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    ਜੇ (!device_hwctx->ਤਾਲਾ) {
        device_hwctx->ਤਾਲਾ_ctx = CreateMutex(ਨਿਰਾ, 0, ਨਿਰਾ);
        ਜੇ (device_hwctx->ਤਾਲਾ_ctx == INVALID_HANDLE_ਮੁੱਲ) {
            av_log(ਨਿਰਾ, AV_LOG_ERROR, "Failed to create a mutex\n");
            ਵਾਪਸ AVERROR(EINVAL);
        }
        device_hwctx->ਤਾਲਾ   = d3d11va_default_ਤਾਲਾ;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    ਜੇ (!device_hwctx->device_context) {
        ID3_D11_Device_Get_ਤੁਰੰਤ_Context(device_hwctx->device, &device_hwctx->device_context);
        ਜੇ (!device_hwctx->device_context)
            ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਜੇ (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (ਖਾਲੀ **)&device_hwctx->video_device);
        ਜੇ (FAILED(hr))
            ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਜੇ (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (ਖਾਲੀ **)&device_hwctx->video_context);
        ਜੇ (FAILED(hr))
            ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    ਜੇ (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = ਨਿਰਾ;
    }

    ਜੇ (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = ਨਿਰਾ;
    }

    ਜੇ (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = ਨਿਰਾ;
    }

    ਜੇ (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = ਨਿਰਾ;
    }

    ਜੇ (device_hwctx->ਤਾਲਾ == d3d11va_default_ਤਾਲਾ) {
        CloseHandle(device_hwctx->ਤਾਲਾ_ctx);
        device_hwctx->ਤਾਲਾ_ctx = INVALID_HANDLE_ਮੁੱਲ;
        device_hwctx->ਤਾਲਾ = ਨਿਰਾ;
    }
}

ਸਥਿਰ ਪੂਰਨ d3d11va_device_ਲੱਭੋ_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, ਅਚਲ ਅੱਖਰ *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = ਨਿਰਾ;
    IDXGIFactory2 *factory;
    ਪੂਰਨ adapter_id = 0;
    ਲੰਮਾ ਪੂਰਨ id = strtol(vendor_id, ਨਿਰਾ, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (ਖਾਲੀ **)&factory);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        ਵਾਪਸ -1;
    }

    ਜਦੋਂ (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_ਮਿਲਿਆ) {
        ID3D11Device* device = ਨਿਰਾ;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, ਨਿਰਾ, flags, ਨਿਰਾ, 0, D3_D11_SDK_ਸੰਸਕਰਣ, &device, ਨਿਰਾ, ਨਿਰਾ);
        ਜੇ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            ਜਾਰੀ;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        ਜੇ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ ਜੇ (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            ਵਾਪਸ adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    ਵਾਪਸ -1;
}

ਸਥਿਰ ਪੂਰਨ d3d11va_device_create(AVHWDeviceContext *ctx, ਅਚਲ ਅੱਖਰ *device,
                                 AVDictionary *opts, ਪੂਰਨ flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = ਨਿਰਾ;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    ਪੂਰਨ is_debug       = !!av_dict_get(opts, "debug", ਨਿਰਾ, 0);
    ਪੂਰਨ ret;
    ਪੂਰਨ adapter = -1;

    ਜੇ (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    ਜੇ ((ret = ff_thread_once(&functions_loaded, ਲੱਦੋ_functions)) != 0)
        ਵਾਪਸ AVERROR_UNKNOWN;
    ਜੇ (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਜੇ (device) {
        adapter = atoi(device);
    } ਨਹੀਂਤਾਂ {
        AVDictionary_ਇੰਦਰਾਜ *e = av_dict_get(opts, "vendor_id", ਨਿਰਾ, 0);
        ਜੇ (e && e->ਮੁੱਲ) {
            adapter = d3d11va_device_ਲੱਭੋ_adapter_by_vendor_id(ctx, creationFlags, e->ਮੁੱਲ);
            ਜੇ (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->ਮੁੱਲ);
                ਵਾਪਸ AVERROR_UNKNOWN;
            }
        }
    }

    ਜੇ (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (ਖਾਲੀ **)&pDXGIFactory);
        ਜੇ (SUCCEEDED(hr)) {
            ਜੇ (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = ਨਿਰਾ;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    ਜੇ (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        ਜੇ (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, ਨਿਰਾ, creationFlags, ਨਿਰਾ, 0,
                   D3_D11_SDK_ਸੰਸਕਰਣ, &device_hwctx->device, ਨਿਰਾ, ਨਿਰਾ);
    ਜੇ (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (ਲੰਮਾ)hr);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (ਖਾਲੀ **)&pMultithread);
    ਜੇ (SUCCEEDED(hr)) {
        ID3_D10_Multithread_ਸੈੱਟ_Multithread_Protected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#ਜੇ !HAVE_UWP && HAVE_DXGIDEBUG_H
    ਜੇ (is_debug) {
        HANDLE dxgidebug_dll = ਲੱਦੋ_Library("dxgidebug.dll");
        ਜੇ (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(ਅਚਲ GUID *riid, ਖਾਲੀ **ppDebug)
                = (ਖਾਲੀ *)Get_Proc_ਪਤਾ(dxgidebug_dll, "DXGIGetDebugInterface");
            ਜੇ (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = ਨਿਰਾ;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (ਖਾਲੀ**)&dxgi_debug);
                ਜੇ (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_Report_ਜੀਵਤ_Objects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } ਨਹੀਂਤਾਂ {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } ਨਹੀਂਤਾਂ {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } ਨਹੀਂਤਾਂ {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#ਜੇ_ਅੰਤ

    ਜੇ (av_dict_get(opts, "SHADER", ਨਿਰਾ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    ਜੇ (av_dict_get(opts, "UAV", ਨਿਰਾ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    ਜੇ (av_dict_get(opts, "RTV", ਨਿਰਾ, 0))
        device_hwctx->BindFlags |= D3_D11_BIND_RENDER_ਨਿਸ਼ਾਨਾ;

    ਜੇ (av_dict_get(opts, "SHARED", ਨਿਰਾ, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    ਵਾਪਸ 0;
}

ਅਚਲ HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_ਮਾਪ    = ਆਕਾਰ(AVD3D11VADeviceContext),
    .ਚੌਖਟੇ_hwctx_ਮਾਪ    = ਆਕਾਰ(D3D11VAFramesContext),

    .device_create        = d3d11va_device_create,
    .device_init          = d3d11va_device_init,
    .device_uninit        = d3d11va_device_uninit,
    .ਚੌਖਟੇ_get_constraints = d3d11va_ਚੌਖਟੇ_get_constraints,
    .ਚੌਖਟੇ_init          = d3d11va_ਚੌਖਟੇ_init,
    .ਚੌਖਟੇ_uninit        = d3d11va_ਚੌਖਟੇ_uninit,
    .ਚੌਖਟੇ_get_ਬਫਰ    = d3d11va_get_ਬਫਰ,
    .transfer_get_formats = d3d11va_transfer_get_formats,
    .transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ     = d3d11va_transfer_ਅੰਕੜੇ,
    .transfer_ਅੰਕੜੇ_from   = d3d11va_transfer_ਅੰਕੜੇ,

    .pix_fmts             = (ਅਚਲ ਗਿਣਤੀ AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
