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

#شامل "config.h"

#شامل <windows.h>

#تعریف_کرو COBJMACROS

#شامل <initguid.h>
#شامل <d3d11.h>
#شامل <dxgi1_2.h>

#اگر HAVE_DXGIDEBUG_H
#شامل <dxgidebug.h>
#اگر_ختم

#شامل "avassert.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_d3d11va.h"
#شامل "hwcontext_internal.h"
#شامل "imgutils.h"
#شامل "mem.h"
#شامل "pixdesc.h"
#شامل "pixfmt.h"
#شامل "thread.h"
#شامل "compat/w32dlfcn.h"

#تعریف_کرو MAX_ARRAY_سائز 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

قسمتعریف HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, خالی **ppFactory);

ساکن AVOnce functions_loaded = AV_ONCE_INIT;

ساکن PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
ساکن PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

ساکن av_cold خالی بھرو_functions(خالی)
{
#اگر !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    اگر (!d3dlib || !dxgilib)
        واپس;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) Get_Proc_پتہ(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) Get_Proc_پتہ(dxgilib, "CreateDXGIFactory1");
    اگر (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) Get_Proc_پتہ(dxgilib, "CreateDXGIFactory");
#ورنہ
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#اگر_ختم
}

قسمتعریف ساخت D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    صحیح nb_surfaces;
    صحیح nb_surfaces_مستعمل;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

ساکن ثابت ساخت {
    DXGI_FORMAT d3d_format;
    شمار AVPixelFormat pix_fmt;
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

ساکن خالی d3d11va_default_تالا(خالی *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

ساکن خالی d3d11va_default_unlock(خالی *ctx)
{
    ReleaseMutex(ctx);
}

ساکن خالی d3d11va_چوکھٹے_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *چوکھٹے_hwctx = &s->p;

    اگر (چوکھٹے_hwctx->texture)
        ID3D11Texture2D_Release(چوکھٹے_hwctx->texture);
    چوکھٹے_hwctx->texture = تہی;

    اگر (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = تہی;

    av_freep(&چوکھٹے_hwctx->texture_infos);
}

ساکن صحیح d3d11va_چوکھٹے_get_constraints(AVHWDeviceContext *ctx,
                                          ثابت خالی *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    صحیح nb_sw_formats = 0;
    HRESULT hr;
    صحیح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    اگر (!constraints->valid_sw_formats)
        واپس AVERROR(ENOMEM);

    برائے (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        اگر (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    اگر (!constraints->valid_hw_formats)
        واپس AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    واپس 0;
}

ساکن خالی free_texture(خالی *opaque, uint8_t *ڈیٹا)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(ڈیٹا);
}

ساکن AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, صحیح اشاریہ)
{
    AVBufferRef *buf;
    AVD3_D11_چوکھٹا_Descriptor         *desc = av_mallocz(حجم(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *چوکھٹے_hwctx = &s->p;
    اگر (!desc) {
        ID3D11Texture2D_Release(tex);
        واپس تہی;
    }

    اگر (s->nb_surfaces <= s->nb_surfaces_مستعمل) {
        چوکھٹے_hwctx->texture_infos = av_realloc_f(چوکھٹے_hwctx->texture_infos,
                                                   s->nb_surfaces_مستعمل + 1,
                                                   حجم(*چوکھٹے_hwctx->texture_infos));
        اگر (!چوکھٹے_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            واپس تہی;
        }
        s->nb_surfaces = s->nb_surfaces_مستعمل + 1;
    }

    چوکھٹے_hwctx->texture_infos[s->nb_surfaces_مستعمل].texture = tex;
    چوکھٹے_hwctx->texture_infos[s->nb_surfaces_مستعمل].اشاریہ = اشاریہ;
    s->nb_surfaces_مستعمل++;

    desc->texture = tex;
    desc->اشاریہ   = اشاریہ;

    buf = av_بفر_create((uint8_t *)desc, حجم(*desc), free_texture, tex, 0);
    اگر (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        واپس تہی;
    }

    واپس buf;
}

ساکن AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    HRESULT hr;
    ID3D11Texture2D *tex;
    D3D11_TEXTURE2D_DESC texDesc = {
        .چوڑائی_2      = ctx->چوڑائی,
        .اونچائی_2     = ctx->اونچائی,
        .Mip_سطحیں  = 1,
        .Format     = s->format,
        .SampleDesc = { .گنتی_2 = 1 },
        .Array_سائز  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, تہی, &tex);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (طویل)hr);
        واپس تہی;
    }

    واپس wrap_texture_buf(ctx, tex, 0);
}

ساکن AVBufferRef *d3d11va_pool_alloc(خالی *opaque, size_t سائز)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    اگر (!hwctx->texture)
        واپس d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    اگر (s->nb_surfaces_مستعمل >= texDesc.Array_سائز) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        واپس تہی;
    }

    ID3_D11_Texture2_D_جوڑو_Ref(hwctx->texture);
    واپس wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_مستعمل);
}

ساکن صحیح d3d11va_چوکھٹے_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    صحیح i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

    برائے (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        اگر (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            توڑو;
        }
    }
    اگر (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        واپس AVERROR(EINVAL);
    }

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    اگر (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_سائز = FFMIN(ctx->initial_pool_سائز, MAX_ARRAY_سائز);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .چوڑائی_2      = ctx->چوڑائی,
        .اونچائی_2     = ctx->اونچائی,
        .Mip_سطحیں  = 1,
        .Format     = s->format,
        .SampleDesc = { .گنتی_2 = 1 },
        .Array_سائز  = ctx->initial_pool_سائز,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    اگر (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        اگر (texDesc.چوڑائی_2 != texDesc2.چوڑائی_2 ||
            texDesc.اونچائی_2 != texDesc2.اونچائی_2 ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            واپس AVERROR(EINVAL);
        }

        ctx->initial_pool_سائز = texDesc2.Array_سائز;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } ورنہ اگر (texDesc.Array_سائز > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, تہی, &hwctx->texture);
        اگر (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (طویل)hr);
            واپس AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(تہی, ctx->initial_pool_سائز, حجم(*hwctx->texture_infos));
    اگر (!hwctx->texture_infos)
        واپس AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_سائز;

    ffhwframesctx(ctx)->pool_اندرونی =
        av_بفر_pool_init2(حجم(AVD3_D11_چوکھٹا_Descriptor),
                             ctx, d3d11va_pool_alloc, تہی);
    اگر (!ffhwframesctx(ctx)->pool_اندرونی)
        واپس AVERROR(ENOMEM);

    واپس 0;
}

ساکن صحیح d3d11va_get_بفر(AVHWFramesContext *ctx, AVFrame *چوکھٹا)
{
    AVD3_D11_چوکھٹا_Descriptor *desc;

    چوکھٹا->buf[0] = av_بفر_pool_get(ctx->pool);
    اگر (!چوکھٹا->buf[0])
        واپس AVERROR(ENOMEM);

    desc = (AVD3_D11_چوکھٹا_Descriptor *)چوکھٹا->buf[0]->ڈیٹا;

    چوکھٹا->ڈیٹا[0] = (uint8_t *)desc->texture;
    چوکھٹا->ڈیٹا[1] = (uint8_t *)desc->اشاریہ;
    چوکھٹا->format  = AV_PIX_FMT_D3D11;
    چوکھٹا->چوڑائی   = ctx->چوڑائی;
    چوکھٹا->اونچائی  = ctx->اونچائی;

    واپس 0;
}

ساکن صحیح d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        شمار AVHWFrameTransferDirection dir,
                                        شمار AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    شمار AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    اگر (!fmts)
        واپس AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    اگر (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    واپس 0;
}

ساکن صحیح d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .چوڑائی_2          = ctx->چوڑائی,
        .اونچائی_2         = ctx->اونچائی,
        .Mip_سطحیں      = 1,
        .Format         = format,
        .SampleDesc     = { .گنتی_2 = 1 },
        .Array_سائز      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, تہی, &s->staging_texture);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (طویل)hr);
        واپس AVERROR_UNKNOWN;
    }

    واپس 0;
}

ساکن خالی fill_texture_ptrs(uint8_t *ڈیٹا[4], صحیح linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    صحیح i;

    برائے (i = 0; i < 4; i++)
        linesize[i] = map->صف_Pitch;

    av_image_fill_اشارے(ڈیٹا, ctx->sw_format, desc->اونچائی_2,
                           (uint8_t*)map->p_ڈیٹا, linesize);
}

ساکن صحیح d3d11va_transfer_ڈیٹا(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    صحیح download = src->format == AV_PIX_FMT_D3D11;
    ثابت AVFrame *چوکھٹا = download ? src : dst;
    ثابت AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)چوکھٹا->ڈیٹا[0];
    صحیح اشاریہ = (intptr_t)چوکھٹا->ڈیٹا[1];
    ID3D11Resource *staging;
    صحیح w = FFMIN(dst->چوڑائی,  src->چوڑائی);
    صحیح h = FFMIN(dst->اونچائی, src->اونچائی);
    uint8_t *map_ڈیٹا[4];
    صحیح map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    صحیح res;

    اگر (چوکھٹا->hw_چوکھٹے_ctx->ڈیٹا != (uint8_t *)ctx || other->format != ctx->sw_format)
        واپس AVERROR(EINVAL);

    device_hwctx->تالا_2(device_hwctx->تالا_ctx);

    اگر (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        اگر (res < 0)
            واپس res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    اگر (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, اشاریہ, تہی);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        اگر (FAILED(hr))
            جاؤ map_failed;

        fill_texture_ptrs(map_ڈیٹا, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->ڈیٹا, dst->linesize, map_ڈیٹا, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } ورنہ {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        اگر (FAILED(hr))
            جاؤ map_failed;

        fill_texture_ptrs(map_ڈیٹا, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_ڈیٹا, map_linesize, src->ڈیٹا, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, اشاریہ, 0, 0, 0,
                                                  staging, 0, تہی);
    }

    device_hwctx->unlock(device_hwctx->تالا_ctx);
    واپس 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (طویل)hr);
    device_hwctx->unlock(device_hwctx->تالا_ctx);
    واپس AVERROR_UNKNOWN;
}

ساکن صحیح d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    اگر (!device_hwctx->تالا_2) {
        device_hwctx->تالا_ctx = CreateMutex(تہی, 0, تہی);
        اگر (device_hwctx->تالا_ctx == INVALID_HANDLE_قدر) {
            av_log(تہی, AV_LOG_ERROR, "Failed to create a mutex\n");
            واپس AVERROR(EINVAL);
        }
        device_hwctx->تالا_2   = d3d11va_default_تالا;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    اگر (!device_hwctx->device_context) {
        ID3_D11_Device_Get_فوری_Context(device_hwctx->device, &device_hwctx->device_context);
        اگر (!device_hwctx->device_context)
            واپس AVERROR_UNKNOWN;
    }

    اگر (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (خالی **)&device_hwctx->video_device);
        اگر (FAILED(hr))
            واپس AVERROR_UNKNOWN;
    }

    اگر (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (خالی **)&device_hwctx->video_context);
        اگر (FAILED(hr))
            واپس AVERROR_UNKNOWN;
    }

    واپس 0;
}

ساکن خالی d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    اگر (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = تہی;
    }

    اگر (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = تہی;
    }

    اگر (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = تہی;
    }

    اگر (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = تہی;
    }

    اگر (device_hwctx->تالا_2 == d3d11va_default_تالا) {
        CloseHandle(device_hwctx->تالا_ctx);
        device_hwctx->تالا_ctx = INVALID_HANDLE_قدر;
        device_hwctx->تالا_2 = تہی;
    }
}

ساکن صحیح d3d11va_device_ڈھونڈو_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, ثابت حرف *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = تہی;
    IDXGIFactory2 *factory;
    صحیح adapter_id = 0;
    طویل صحیح id = strtol(vendor_id, تہی, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (خالی **)&factory);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        واپس -1;
    }

    جب (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_ملا) {
        ID3D11Device* device = تہی;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, تہی, flags, تہی, 0, D3_D11_SDK_نسخہ, &device, تہی, تہی);
        اگر (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            جاری;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        اگر (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            جاری;
        } ورنہ اگر (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            واپس adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    واپس -1;
}

ساکن صحیح d3d11va_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                                 AVDictionary *opts, صحیح flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = تہی;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    صحیح is_debug       = !!av_dict_get(opts, "debug", تہی, 0);
    صحیح ret;
    صحیح adapter = -1;

    اگر (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    اگر ((ret = ff_thread_once(&functions_loaded, بھرو_functions)) != 0)
        واپس AVERROR_UNKNOWN;
    اگر (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        واپس AVERROR_UNKNOWN;
    }

    اگر (device) {
        adapter = atoi(device);
    } ورنہ {
        AVDictionary_اندراج *e = av_dict_get(opts, "vendor_id", تہی, 0);
        اگر (e && e->قدر) {
            adapter = d3d11va_device_ڈھونڈو_adapter_by_vendor_id(ctx, creationFlags, e->قدر);
            اگر (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->قدر);
                واپس AVERROR_UNKNOWN;
            }
        }
    }

    اگر (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (خالی **)&pDXGIFactory);
        اگر (SUCCEEDED(hr)) {
            اگر (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = تہی;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    اگر (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        اگر (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, تہی, creationFlags, تہی, 0,
                   D3_D11_SDK_نسخہ, &device_hwctx->device, تہی, تہی);
    اگر (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (طویل)hr);
        واپس AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (خالی **)&pMultithread);
    اگر (SUCCEEDED(hr)) {
        ID3_D10_Multithread_سیٹ_Multithread_Protected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#اگر !HAVE_UWP && HAVE_DXGIDEBUG_H
    اگر (is_debug) {
        HANDLE dxgidebug_dll = بھرو_Library("dxgidebug.dll");
        اگر (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(ثابت GUID *riid, خالی **ppDebug)
                = (خالی *)Get_Proc_پتہ(dxgidebug_dll, "DXGIGetDebugInterface");
            اگر (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = تہی;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (خالی**)&dxgi_debug);
                اگر (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_Report_زندہ_Objects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } ورنہ {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } ورنہ {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } ورنہ {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#اگر_ختم

    اگر (av_dict_get(opts, "SHADER", تہی, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    اگر (av_dict_get(opts, "UAV", تہی, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    اگر (av_dict_get(opts, "RTV", تہی, 0))
        device_hwctx->BindFlags |= D3_D11_BIND_RENDER_ہدف;

    اگر (av_dict_get(opts, "SHARED", تہی, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    واپس 0;
}

ثابت HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_سائز    = حجم(AVD3D11VADeviceContext),
    .چوکھٹے_hwctx_سائز    = حجم(D3D11VAFramesContext),

    .device_create        = d3d11va_device_create,
    .device_init          = d3d11va_device_init,
    .device_uninit        = d3d11va_device_uninit,
    .چوکھٹے_get_constraints = d3d11va_چوکھٹے_get_constraints,
    .چوکھٹے_init          = d3d11va_چوکھٹے_init,
    .چوکھٹے_uninit        = d3d11va_چوکھٹے_uninit,
    .چوکھٹے_get_بفر    = d3d11va_get_بفر,
    .transfer_get_formats = d3d11va_transfer_get_formats,
    .transfer_ڈیٹا_مقصد     = d3d11va_transfer_ڈیٹا,
    .transfer_ڈیٹا_from   = d3d11va_transfer_ڈیٹا,

    .pix_fmts             = (ثابت شمار AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
