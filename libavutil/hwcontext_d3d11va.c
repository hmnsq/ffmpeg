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

#ضمن "config.h"

#ضمن <windows.h>

#تعریف_کن COBJMACROS

#ضمن <initguid.h>
#ضمن <d3d11.h>
#ضمن <dxgi1_2.h>

#إذا HAVE_DXGIDEBUG_H
#ضمن <dxgidebug.h>
#پایان_اگر

#ضمن "avassert.h"
#ضمن "common.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_d3d11va.h"
#ضمن "hwcontext_internal.h"
#ضمن "imgutils.h"
#ضمن "mem.h"
#ضمن "pixdesc.h"
#ضمن "pixfmt.h"
#ضمن "thread.h"
#ضمن "compat/w32dlfcn.h"

#تعریف_کن MAX_ARRAY_اندازه 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

تعريفنوع HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, فراغ **ppFactory);

ساكن AVOnce functions_loaded = AV_ONCE_INIT;

ساكن PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
ساكن PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

ساكن av_cold فراغ بارگیری_functions(فراغ)
{
#إذا !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    إذا (!d3dlib || !dxgilib)
        أرجع;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) Get_Proc_آدرس(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) Get_Proc_آدرس(dxgilib, "CreateDXGIFactory1");
    إذا (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) Get_Proc_آدرس(dxgilib, "CreateDXGIFactory");
#وإلا
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#پایان_اگر
}

تعريفنوع بنية D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    صحيح nb_surfaces;
    صحيح nb_surfaces_استفاده_شده;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

ساكن ثابت بنية {
    DXGI_FORMAT d3d_format;
    تعداد AVPixelFormat pix_fmt;
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

ساكن فراغ d3d11va_default_قفل(فراغ *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

ساكن فراغ d3d11va_default_unlock(فراغ *ctx)
{
    ReleaseMutex(ctx);
}

ساكن فراغ d3d11va_قابها_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *قابها_hwctx = &s->p;

    إذا (قابها_hwctx->texture)
        ID3D11Texture2D_Release(قابها_hwctx->texture);
    قابها_hwctx->texture = عدم;

    إذا (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = عدم;

    av_freep(&قابها_hwctx->texture_infos);
}

ساكن صحيح d3d11va_قابها_get_constraints(AVHWDeviceContext *ctx,
                                          ثابت فراغ *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    صحيح nb_sw_formats = 0;
    HRESULT hr;
    صحيح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    إذا (!constraints->valid_sw_formats)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        إذا (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    إذا (!constraints->valid_hw_formats)
        أرجع AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    أرجع 0;
}

ساكن فراغ free_texture(فراغ *opaque, uint8_t *داده)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(داده);
}

ساكن AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, صحيح شاخص)
{
    AVBufferRef *buf;
    AVD3_D11_قاب_Descriptor         *desc = av_mallocz(حجم(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *قابها_hwctx = &s->p;
    إذا (!desc) {
        ID3D11Texture2D_Release(tex);
        أرجع عدم;
    }

    إذا (s->nb_surfaces <= s->nb_surfaces_استفاده_شده) {
        قابها_hwctx->texture_infos = av_realloc_f(قابها_hwctx->texture_infos,
                                                   s->nb_surfaces_استفاده_شده + 1,
                                                   حجم(*قابها_hwctx->texture_infos));
        إذا (!قابها_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            أرجع عدم;
        }
        s->nb_surfaces = s->nb_surfaces_استفاده_شده + 1;
    }

    قابها_hwctx->texture_infos[s->nb_surfaces_استفاده_شده].texture = tex;
    قابها_hwctx->texture_infos[s->nb_surfaces_استفاده_شده].شاخص = شاخص;
    s->nb_surfaces_استفاده_شده++;

    desc->texture = tex;
    desc->شاخص   = شاخص;

    buf = av_میانگیر_create((uint8_t *)desc, حجم(*desc), free_texture, tex, 0);
    إذا (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        أرجع عدم;
    }

    أرجع buf;
}

ساكن AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    HRESULT hr;
    ID3D11Texture2D *tex;
    D3D11_TEXTURE2D_DESC texDesc = {
        .عرض_2      = ctx->عرض,
        .ارتفاع_2     = ctx->ارتفاع,
        .Mip_سطوح  = 1,
        .Format     = s->format,
        .SampleDesc = { .شمار_2 = 1 },
        .Array_اندازه  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, عدم, &tex);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (دراز)hr);
        أرجع عدم;
    }

    أرجع wrap_texture_buf(ctx, tex, 0);
}

ساكن AVBufferRef *d3d11va_pool_alloc(فراغ *opaque, size_t اندازه)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    إذا (!hwctx->texture)
        أرجع d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    إذا (s->nb_surfaces_استفاده_شده >= texDesc.Array_اندازه) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        أرجع عدم;
    }

    ID3_D11_Texture2_D_جمع_کن_Ref(hwctx->texture);
    أرجع wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_استفاده_شده);
}

ساكن صحيح d3d11va_قابها_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    صحيح i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

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

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    إذا (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_اندازه = FFMIN(ctx->initial_pool_اندازه, MAX_ARRAY_اندازه);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .عرض_2      = ctx->عرض,
        .ارتفاع_2     = ctx->ارتفاع,
        .Mip_سطوح  = 1,
        .Format     = s->format,
        .SampleDesc = { .شمار_2 = 1 },
        .Array_اندازه  = ctx->initial_pool_اندازه,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    إذا (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        إذا (texDesc.عرض_2 != texDesc2.عرض_2 ||
            texDesc.ارتفاع_2 != texDesc2.ارتفاع_2 ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            أرجع AVERROR(EINVAL);
        }

        ctx->initial_pool_اندازه = texDesc2.Array_اندازه;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } وإلا إذا (texDesc.Array_اندازه > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, عدم, &hwctx->texture);
        إذا (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (دراز)hr);
            أرجع AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(عدم, ctx->initial_pool_اندازه, حجم(*hwctx->texture_infos));
    إذا (!hwctx->texture_infos)
        أرجع AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_اندازه;

    ffhwframesctx(ctx)->pool_داخلی =
        av_میانگیر_pool_init2(حجم(AVD3_D11_قاب_Descriptor),
                             ctx, d3d11va_pool_alloc, عدم);
    إذا (!ffhwframesctx(ctx)->pool_داخلی)
        أرجع AVERROR(ENOMEM);

    أرجع 0;
}

ساكن صحيح d3d11va_get_میانگیر(AVHWFramesContext *ctx, AVFrame *قاب)
{
    AVD3_D11_قاب_Descriptor *desc;

    قاب->buf[0] = av_میانگیر_pool_get(ctx->pool);
    إذا (!قاب->buf[0])
        أرجع AVERROR(ENOMEM);

    desc = (AVD3_D11_قاب_Descriptor *)قاب->buf[0]->داده;

    قاب->داده[0] = (uint8_t *)desc->texture;
    قاب->داده[1] = (uint8_t *)desc->شاخص;
    قاب->format  = AV_PIX_FMT_D3D11;
    قاب->عرض   = ctx->عرض;
    قاب->ارتفاع  = ctx->ارتفاع;

    أرجع 0;
}

ساكن صحيح d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        تعداد AVHWFrameTransferDirection dir,
                                        تعداد AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    تعداد AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    إذا (!fmts)
        أرجع AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    إذا (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    أرجع 0;
}

ساكن صحيح d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .عرض_2          = ctx->عرض,
        .ارتفاع_2         = ctx->ارتفاع,
        .Mip_سطوح      = 1,
        .Format         = format,
        .SampleDesc     = { .شمار_2 = 1 },
        .Array_اندازه      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, عدم, &s->staging_texture);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (دراز)hr);
        أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}

ساكن فراغ fill_texture_ptrs(uint8_t *داده[4], صحيح linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    صحيح i;

    لكل (i = 0; i < 4; i++)
        linesize[i] = map->ردیف_Pitch;

    av_image_fill_اشارهگرها(داده, ctx->sw_format, desc->ارتفاع_2,
                           (uint8_t*)map->p_داده, linesize);
}

ساكن صحيح d3d11va_transfer_داده(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    صحيح download = src->format == AV_PIX_FMT_D3D11;
    ثابت AVFrame *قاب = download ? src : dst;
    ثابت AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)قاب->داده[0];
    صحيح شاخص = (intptr_t)قاب->داده[1];
    ID3D11Resource *staging;
    صحيح w = FFMIN(dst->عرض,  src->عرض);
    صحيح h = FFMIN(dst->ارتفاع, src->ارتفاع);
    uint8_t *map_داده[4];
    صحيح map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    صحيح res;

    إذا (قاب->hw_قابها_ctx->داده != (uint8_t *)ctx || other->format != ctx->sw_format)
        أرجع AVERROR(EINVAL);

    device_hwctx->قفل_2(device_hwctx->قفل_ctx);

    إذا (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        إذا (res < 0)
            أرجع res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    إذا (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, شاخص, عدم);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        إذا (FAILED(hr))
            اذهب map_failed;

        fill_texture_ptrs(map_داده, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->داده, dst->linesize, map_داده, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } وإلا {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        إذا (FAILED(hr))
            اذهب map_failed;

        fill_texture_ptrs(map_داده, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_داده, map_linesize, src->داده, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, شاخص, 0, 0, 0,
                                                  staging, 0, عدم);
    }

    device_hwctx->unlock(device_hwctx->قفل_ctx);
    أرجع 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (دراز)hr);
    device_hwctx->unlock(device_hwctx->قفل_ctx);
    أرجع AVERROR_UNKNOWN;
}

ساكن صحيح d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    إذا (!device_hwctx->قفل_2) {
        device_hwctx->قفل_ctx = CreateMutex(عدم, 0, عدم);
        إذا (device_hwctx->قفل_ctx == INVALID_HANDLE_مقدار) {
            av_log(عدم, AV_LOG_ERROR, "Failed to create a mutex\n");
            أرجع AVERROR(EINVAL);
        }
        device_hwctx->قفل_2   = d3d11va_default_قفل;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    إذا (!device_hwctx->device_context) {
        ID3_D11_Device_Get_فوری_Context(device_hwctx->device, &device_hwctx->device_context);
        إذا (!device_hwctx->device_context)
            أرجع AVERROR_UNKNOWN;
    }

    إذا (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (فراغ **)&device_hwctx->video_device);
        إذا (FAILED(hr))
            أرجع AVERROR_UNKNOWN;
    }

    إذا (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (فراغ **)&device_hwctx->video_context);
        إذا (FAILED(hr))
            أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}

ساكن فراغ d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    إذا (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = عدم;
    }

    إذا (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = عدم;
    }

    إذا (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = عدم;
    }

    إذا (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = عدم;
    }

    إذا (device_hwctx->قفل_2 == d3d11va_default_قفل) {
        CloseHandle(device_hwctx->قفل_ctx);
        device_hwctx->قفل_ctx = INVALID_HANDLE_مقدار;
        device_hwctx->قفل_2 = عدم;
    }
}

ساكن صحيح d3d11va_device_پیدا_کن_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, ثابت حرف *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = عدم;
    IDXGIFactory2 *factory;
    صحيح adapter_id = 0;
    دراز صحيح id = strtol(vendor_id, عدم, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (فراغ **)&factory);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        أرجع -1;
    }

    طالما (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_یافت) {
        ID3D11Device* device = عدم;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, عدم, flags, عدم, 0, D3_D11_SDK_نسخه, &device, عدم, عدم);
        إذا (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            استمر;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        إذا (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            استمر;
        } وإلا إذا (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            أرجع adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    أرجع -1;
}

ساكن صحيح d3d11va_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                                 AVDictionary *opts, صحيح flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = عدم;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    صحيح is_debug       = !!av_dict_get(opts, "debug", عدم, 0);
    صحيح ret;
    صحيح adapter = -1;

    إذا (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    إذا ((ret = ff_thread_once(&functions_loaded, بارگیری_functions)) != 0)
        أرجع AVERROR_UNKNOWN;
    إذا (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        أرجع AVERROR_UNKNOWN;
    }

    إذا (device) {
        adapter = atoi(device);
    } وإلا {
        AVDictionary_مدخل *e = av_dict_get(opts, "vendor_id", عدم, 0);
        إذا (e && e->مقدار) {
            adapter = d3d11va_device_پیدا_کن_adapter_by_vendor_id(ctx, creationFlags, e->مقدار);
            إذا (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->مقدار);
                أرجع AVERROR_UNKNOWN;
            }
        }
    }

    إذا (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (فراغ **)&pDXGIFactory);
        إذا (SUCCEEDED(hr)) {
            إذا (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = عدم;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    إذا (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        إذا (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, عدم, creationFlags, عدم, 0,
                   D3_D11_SDK_نسخه, &device_hwctx->device, عدم, عدم);
    إذا (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (دراز)hr);
        أرجع AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (فراغ **)&pMultithread);
    إذا (SUCCEEDED(hr)) {
        ID3_D10_Multithread_مجموعه_Multithread_Protected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#إذا !HAVE_UWP && HAVE_DXGIDEBUG_H
    إذا (is_debug) {
        HANDLE dxgidebug_dll = بارگیری_Library("dxgidebug.dll");
        إذا (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(ثابت GUID *riid, فراغ **ppDebug)
                = (فراغ *)Get_Proc_آدرس(dxgidebug_dll, "DXGIGetDebugInterface");
            إذا (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = عدم;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (فراغ**)&dxgi_debug);
                إذا (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_Report_زنده_Objects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } وإلا {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } وإلا {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } وإلا {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#پایان_اگر

    إذا (av_dict_get(opts, "SHADER", عدم, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    إذا (av_dict_get(opts, "UAV", عدم, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    إذا (av_dict_get(opts, "RTV", عدم, 0))
        device_hwctx->BindFlags |= D3_D11_BIND_RENDER_هدف;

    إذا (av_dict_get(opts, "SHARED", عدم, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    أرجع 0;
}

ثابت HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_اندازه    = حجم(AVD3D11VADeviceContext),
    .قابها_hwctx_اندازه    = حجم(D3D11VAFramesContext),

    .device_create        = d3d11va_device_create,
    .device_init          = d3d11va_device_init,
    .device_uninit        = d3d11va_device_uninit,
    .قابها_get_constraints = d3d11va_قابها_get_constraints,
    .قابها_init          = d3d11va_قابها_init,
    .قابها_uninit        = d3d11va_قابها_uninit,
    .قابها_get_میانگیر    = d3d11va_get_میانگیر,
    .transfer_get_formats = d3d11va_transfer_get_formats,
    .transfer_داده_مقصد     = d3d11va_transfer_داده,
    .transfer_داده_from   = d3d11va_transfer_داده,

    .pix_fmts             = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
