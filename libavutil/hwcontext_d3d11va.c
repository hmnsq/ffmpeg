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

#అన్తర్భావ "config.h"

#అన్తర్భావ <windows.h>

#నిర్వచించు COBJMACROS

#అన్తర్భావ <initguid.h>
#అన్తర్భావ <d3d11.h>
#అన్తర్భావ <dxgi1_2.h>

#ఒకవేళ HAVE_DXGIDEBUG_H
#అన్తర్భావ <dxgidebug.h>
#అయితే_ముగింపు

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_d3d11va.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "imgutils.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "pixdesc.h"
#అన్తర్భావ "pixfmt.h"
#అన్తర్భావ "thread.h"
#అన్తర్భావ "compat/w32dlfcn.h"

#నిర్వచించు MAX_ARRAY_కొలత 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

రకనిర్వచనం HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, శూన్య **ppFactory);

స్థిర AVOnce functions_loaded = AV_ONCE_INIT;

స్థిర PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
స్థిర PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

స్థిర av_cold శూన్య ఎక్కించు_functions(శూన్య)
{
#ఒకవేళ !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    ఒకవేళ (!d3dlib || !dxgilib)
        తిరిగి;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) Get_Proc_చిరునామా(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) Get_Proc_చిరునామా(dxgilib, "CreateDXGIFactory1");
    ఒకవేళ (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) Get_Proc_చిరునామా(dxgilib, "CreateDXGIFactory");
#లేకపోతే
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#అయితే_ముగింపు
}

రకనిర్వచనం నిర్మాణం D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    పూర్ణాంకం nb_surfaces;
    పూర్ణాంకం nb_surfaces_వాడిన;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

స్థిర స్థిరరాశి నిర్మాణం {
    DXGI_FORMAT d3d_format;
    గణన AVPixelFormat pix_fmt;
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

స్థిర శూన్య d3d11va_default_తాళం(శూన్య *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

స్థిర శూన్య d3d11va_default_unlock(శూన్య *ctx)
{
    ReleaseMutex(ctx);
}

స్థిర శూన్య d3d11va_చట్రాలు_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *చట్రాలు_hwctx = &s->p;

    ఒకవేళ (చట్రాలు_hwctx->texture)
        ID3D11Texture2D_Release(చట్రాలు_hwctx->texture);
    చట్రాలు_hwctx->texture = ఖాళీ;

    ఒకవేళ (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = ఖాళీ;

    av_freep(&చట్రాలు_hwctx->texture_infos);
}

స్థిర పూర్ణాంకం d3d11va_చట్రాలు_get_constraints(AVHWDeviceContext *ctx,
                                          స్థిరరాశి శూన్య *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    పూర్ణాంకం nb_sw_formats = 0;
    HRESULT hr;
    పూర్ణాంకం i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    పరిమాణం(*constraints->valid_sw_formats));
    ఒకవేళ (!constraints->valid_sw_formats)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        ఒకవేళ (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, పరిమాణం(*constraints->valid_hw_formats));
    ఒకవేళ (!constraints->valid_hw_formats)
        తిరిగి AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    తిరిగి 0;
}

స్థిర శూన్య free_texture(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(దత్తాంశం);
}

స్థిర AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, పూర్ణాంకం సూచీ)
{
    AVBufferRef *buf;
    AVD3_D11_చట్రం_Descriptor         *desc = av_mallocz(పరిమాణం(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *చట్రాలు_hwctx = &s->p;
    ఒకవేళ (!desc) {
        ID3D11Texture2D_Release(tex);
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (s->nb_surfaces <= s->nb_surfaces_వాడిన) {
        చట్రాలు_hwctx->texture_infos = av_realloc_f(చట్రాలు_hwctx->texture_infos,
                                                   s->nb_surfaces_వాడిన + 1,
                                                   పరిమాణం(*చట్రాలు_hwctx->texture_infos));
        ఒకవేళ (!చట్రాలు_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            తిరిగి ఖాళీ;
        }
        s->nb_surfaces = s->nb_surfaces_వాడిన + 1;
    }

    చట్రాలు_hwctx->texture_infos[s->nb_surfaces_వాడిన].texture = tex;
    చట్రాలు_hwctx->texture_infos[s->nb_surfaces_వాడిన].సూచీ = సూచీ;
    s->nb_surfaces_వాడిన++;

    desc->texture = tex;
    desc->సూచీ   = సూచీ;

    buf = av_బఫరు_create((uint8_t *)desc, పరిమాణం(*desc), free_texture, tex, 0);
    ఒకవేళ (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        తిరిగి ఖాళీ;
    }

    తిరిగి buf;
}

స్థిర AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    HRESULT hr;
    ID3D11Texture2D *tex;
    D3D11_TEXTURE2D_DESC texDesc = {
        .వెడల్పు_2      = ctx->వెడల్పు,
        .ఎత్తు_2     = ctx->ఎత్తు,
        .Mip_స్థాయిలు  = 1,
        .Format     = s->format,
        .SampleDesc = { .లెక్క_2 = 1 },
        .Array_కొలత  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ఖాళీ, &tex);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (దీర్ఘ)hr);
        తిరిగి ఖాళీ;
    }

    తిరిగి wrap_texture_buf(ctx, tex, 0);
}

స్థిర AVBufferRef *d3d11va_pool_alloc(శూన్య *opaque, size_t కొలత)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    ఒకవేళ (!hwctx->texture)
        తిరిగి d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    ఒకవేళ (s->nb_surfaces_వాడిన >= texDesc.Array_కొలత) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        తిరిగి ఖాళీ;
    }

    ID3_D11_Texture2_D_కూడు_Ref(hwctx->texture);
    తిరిగి wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_వాడిన);
}

స్థిర పూర్ణాంకం d3d11va_చట్రాలు_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    పూర్ణాంకం i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ఒకవేళ (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            ఆపు;
        }
    }
    ఒకవేళ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        తిరిగి AVERROR(EINVAL);
    }

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    ఒకవేళ (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_కొలత = FFMIN(ctx->initial_pool_కొలత, MAX_ARRAY_కొలత);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .వెడల్పు_2      = ctx->వెడల్పు,
        .ఎత్తు_2     = ctx->ఎత్తు,
        .Mip_స్థాయిలు  = 1,
        .Format     = s->format,
        .SampleDesc = { .లెక్క_2 = 1 },
        .Array_కొలత  = ctx->initial_pool_కొలత,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    ఒకవేళ (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        ఒకవేళ (texDesc.వెడల్పు_2 != texDesc2.వెడల్పు_2 ||
            texDesc.ఎత్తు_2 != texDesc2.ఎత్తు_2 ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            తిరిగి AVERROR(EINVAL);
        }

        ctx->initial_pool_కొలత = texDesc2.Array_కొలత;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } లేకపోతే ఒకవేళ (texDesc.Array_కొలత > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ఖాళీ, &hwctx->texture);
        ఒకవేళ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (దీర్ఘ)hr);
            తిరిగి AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(ఖాళీ, ctx->initial_pool_కొలత, పరిమాణం(*hwctx->texture_infos));
    ఒకవేళ (!hwctx->texture_infos)
        తిరిగి AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_కొలత;

    ffhwframesctx(ctx)->pool_అంతర్గత =
        av_బఫరు_pool_init2(పరిమాణం(AVD3_D11_చట్రం_Descriptor),
                             ctx, d3d11va_pool_alloc, ఖాళీ);
    ఒకవేళ (!ffhwframesctx(ctx)->pool_అంతర్గత)
        తిరిగి AVERROR(ENOMEM);

    తిరిగి 0;
}

స్థిర పూర్ణాంకం d3d11va_get_బఫరు(AVHWFramesContext *ctx, AVFrame *చట్రం)
{
    AVD3_D11_చట్రం_Descriptor *desc;

    చట్రం->buf[0] = av_బఫరు_pool_get(ctx->pool);
    ఒకవేళ (!చట్రం->buf[0])
        తిరిగి AVERROR(ENOMEM);

    desc = (AVD3_D11_చట్రం_Descriptor *)చట్రం->buf[0]->దత్తాంశం;

    చట్రం->దత్తాంశం[0] = (uint8_t *)desc->texture;
    చట్రం->దత్తాంశం[1] = (uint8_t *)desc->సూచీ;
    చట్రం->format  = AV_PIX_FMT_D3D11;
    చట్రం->వెడల్పు   = ctx->వెడల్పు;
    చట్రం->ఎత్తు  = ctx->ఎత్తు;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        గణన AVHWFrameTransferDirection dir,
                                        గణన AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    గణన AVPixelFormat *fmts;

    fmts = av_malloc_array(2, పరిమాణం(*fmts));
    ఒకవేళ (!fmts)
        తిరిగి AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    ఒకవేళ (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .వెడల్పు_2          = ctx->వెడల్పు,
        .ఎత్తు_2         = ctx->ఎత్తు,
        .Mip_స్థాయిలు      = 1,
        .Format         = format,
        .SampleDesc     = { .లెక్క_2 = 1 },
        .Array_కొలత      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ఖాళీ, &s->staging_texture);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (దీర్ఘ)hr);
        తిరిగి AVERROR_UNKNOWN;
    }

    తిరిగి 0;
}

స్థిర శూన్య fill_texture_ptrs(uint8_t *దత్తాంశం[4], పూర్ణాంకం linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    పూర్ణాంకం i;

    కొరకు (i = 0; i < 4; i++)
        linesize[i] = map->అడ్డువరుస_Pitch;

    av_image_fill_సూచికలు(దత్తాంశం, ctx->sw_format, desc->ఎత్తు_2,
                           (uint8_t*)map->p_దత్తాంశం, linesize);
}

స్థిర పూర్ణాంకం d3d11va_transfer_దత్తాంశం(AVHWFramesContext *ctx, AVFrame *dst,
                                 స్థిరరాశి AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    పూర్ణాంకం download = src->format == AV_PIX_FMT_D3D11;
    స్థిరరాశి AVFrame *చట్రం = download ? src : dst;
    స్థిరరాశి AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)చట్రం->దత్తాంశం[0];
    పూర్ణాంకం సూచీ = (intptr_t)చట్రం->దత్తాంశం[1];
    ID3D11Resource *staging;
    పూర్ణాంకం w = FFMIN(dst->వెడల్పు,  src->వెడల్పు);
    పూర్ణాంకం h = FFMIN(dst->ఎత్తు, src->ఎత్తు);
    uint8_t *map_దత్తాంశం[4];
    పూర్ణాంకం map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    పూర్ణాంకం res;

    ఒకవేళ (చట్రం->hw_చట్రాలు_ctx->దత్తాంశం != (uint8_t *)ctx || other->format != ctx->sw_format)
        తిరిగి AVERROR(EINVAL);

    device_hwctx->తాళం_2(device_hwctx->తాళం_ctx);

    ఒకవేళ (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        ఒకవేళ (res < 0)
            తిరిగి res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    ఒకవేళ (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, సూచీ, ఖాళీ);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        ఒకవేళ (FAILED(hr))
            వెళ్ళు map_failed;

        fill_texture_ptrs(map_దత్తాంశం, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->దత్తాంశం, dst->linesize, map_దత్తాంశం, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } లేకపోతే {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        ఒకవేళ (FAILED(hr))
            వెళ్ళు map_failed;

        fill_texture_ptrs(map_దత్తాంశం, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_దత్తాంశం, map_linesize, src->దత్తాంశం, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, సూచీ, 0, 0, 0,
                                                  staging, 0, ఖాళీ);
    }

    device_hwctx->unlock(device_hwctx->తాళం_ctx);
    తిరిగి 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (దీర్ఘ)hr);
    device_hwctx->unlock(device_hwctx->తాళం_ctx);
    తిరిగి AVERROR_UNKNOWN;
}

స్థిర పూర్ణాంకం d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    ఒకవేళ (!device_hwctx->తాళం_2) {
        device_hwctx->తాళం_ctx = CreateMutex(ఖాళీ, 0, ఖాళీ);
        ఒకవేళ (device_hwctx->తాళం_ctx == INVALID_HANDLE_విలువ) {
            av_log(ఖాళీ, AV_LOG_ERROR, "Failed to create a mutex\n");
            తిరిగి AVERROR(EINVAL);
        }
        device_hwctx->తాళం_2   = d3d11va_default_తాళం;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    ఒకవేళ (!device_hwctx->device_context) {
        ID3_D11_Device_Get_తక్షణ_Context(device_hwctx->device, &device_hwctx->device_context);
        ఒకవేళ (!device_hwctx->device_context)
            తిరిగి AVERROR_UNKNOWN;
    }

    ఒకవేళ (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (శూన్య **)&device_hwctx->video_device);
        ఒకవేళ (FAILED(hr))
            తిరిగి AVERROR_UNKNOWN;
    }

    ఒకవేళ (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (శూన్య **)&device_hwctx->video_context);
        ఒకవేళ (FAILED(hr))
            తిరిగి AVERROR_UNKNOWN;
    }

    తిరిగి 0;
}

స్థిర శూన్య d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    ఒకవేళ (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = ఖాళీ;
    }

    ఒకవేళ (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = ఖాళీ;
    }

    ఒకవేళ (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = ఖాళీ;
    }

    ఒకవేళ (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = ఖాళీ;
    }

    ఒకవేళ (device_hwctx->తాళం_2 == d3d11va_default_తాళం) {
        CloseHandle(device_hwctx->తాళం_ctx);
        device_hwctx->తాళం_ctx = INVALID_HANDLE_విలువ;
        device_hwctx->తాళం_2 = ఖాళీ;
    }
}

స్థిర పూర్ణాంకం d3d11va_device_కనుగొను_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, స్థిరరాశి అక్షరం *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = ఖాళీ;
    IDXGIFactory2 *factory;
    పూర్ణాంకం adapter_id = 0;
    దీర్ఘ పూర్ణాంకం id = strtol(vendor_id, ఖాళీ, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (శూన్య **)&factory);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        తిరిగి -1;
    }

    అయితే (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_దొరికింది) {
        ID3D11Device* device = ఖాళీ;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, ఖాళీ, flags, ఖాళీ, 0, D3_D11_SDK_సంస్కరణ, &device, ఖాళీ, ఖాళీ);
        ఒకవేళ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            కొనసాగు;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        ఒకవేళ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            కొనసాగు;
        } లేకపోతే ఒకవేళ (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            తిరిగి adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    తిరిగి -1;
}

స్థిర పూర్ణాంకం d3d11va_device_create(AVHWDeviceContext *ctx, స్థిరరాశి అక్షరం *device,
                                 AVDictionary *opts, పూర్ణాంకం flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = ఖాళీ;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    పూర్ణాంకం is_debug       = !!av_dict_get(opts, "debug", ఖాళీ, 0);
    పూర్ణాంకం ret;
    పూర్ణాంకం adapter = -1;

    ఒకవేళ (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    ఒకవేళ ((ret = ff_thread_once(&functions_loaded, ఎక్కించు_functions)) != 0)
        తిరిగి AVERROR_UNKNOWN;
    ఒకవేళ (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    ఒకవేళ (device) {
        adapter = atoi(device);
    } లేకపోతే {
        AVDictionary_నమోదు *e = av_dict_get(opts, "vendor_id", ఖాళీ, 0);
        ఒకవేళ (e && e->విలువ) {
            adapter = d3d11va_device_కనుగొను_adapter_by_vendor_id(ctx, creationFlags, e->విలువ);
            ఒకవేళ (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->విలువ);
                తిరిగి AVERROR_UNKNOWN;
            }
        }
    }

    ఒకవేళ (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (శూన్య **)&pDXGIFactory);
        ఒకవేళ (SUCCEEDED(hr)) {
            ఒకవేళ (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = ఖాళీ;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    ఒకవేళ (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        ఒకవేళ (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, ఖాళీ, creationFlags, ఖాళీ, 0,
                   D3_D11_SDK_సంస్కరణ, &device_hwctx->device, ఖాళీ, ఖాళీ);
    ఒకవేళ (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (దీర్ఘ)hr);
        తిరిగి AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (శూన్య **)&pMultithread);
    ఒకవేళ (SUCCEEDED(hr)) {
        ID3_D10_Multithread_సమితి_Multithread_Protected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#ఒకవేళ !HAVE_UWP && HAVE_DXGIDEBUG_H
    ఒకవేళ (is_debug) {
        HANDLE dxgidebug_dll = ఎక్కించు_Library("dxgidebug.dll");
        ఒకవేళ (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(స్థిరరాశి GUID *riid, శూన్య **ppDebug)
                = (శూన్య *)Get_Proc_చిరునామా(dxgidebug_dll, "DXGIGetDebugInterface");
            ఒకవేళ (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = ఖాళీ;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (శూన్య**)&dxgi_debug);
                ఒకవేళ (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_Report_సజీవ_Objects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } లేకపోతే {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } లేకపోతే {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } లేకపోతే {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#అయితే_ముగింపు

    ఒకవేళ (av_dict_get(opts, "SHADER", ఖాళీ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    ఒకవేళ (av_dict_get(opts, "UAV", ఖాళీ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    ఒకవేళ (av_dict_get(opts, "RTV", ఖాళీ, 0))
        device_hwctx->BindFlags |= D3_D11_BIND_RENDER_లక్ష్యం;

    ఒకవేళ (av_dict_get(opts, "SHARED", ఖాళీ, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    తిరిగి 0;
}

స్థిరరాశి HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_కొలత    = పరిమాణం(AVD3D11VADeviceContext),
    .చట్రాలు_hwctx_కొలత    = పరిమాణం(D3D11VAFramesContext),

    .device_create        = d3d11va_device_create,
    .device_init          = d3d11va_device_init,
    .device_uninit        = d3d11va_device_uninit,
    .చట్రాలు_get_constraints = d3d11va_చట్రాలు_get_constraints,
    .చట్రాలు_init          = d3d11va_చట్రాలు_init,
    .చట్రాలు_uninit        = d3d11va_చట్రాలు_uninit,
    .చట్రాలు_get_బఫరు    = d3d11va_get_బఫరు,
    .transfer_get_formats = d3d11va_transfer_get_formats,
    .transfer_దత్తాంశం_గమ్యం     = d3d11va_transfer_దత్తాంశం,
    .transfer_దత్తాంశం_from   = d3d11va_transfer_దత్తాంశం,

    .pix_fmts             = (స్థిరరాశి గణన AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
