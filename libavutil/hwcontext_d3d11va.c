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

#include "config.h"

#include <windows.h>

#define COBJMACROS

#include <initguid.h>
#include <d3d11.h>
#include <dxgi1_2.h>

#ប្រសិនបើ HAVE_DXGIDEBUG_H
#include <dxgidebug.h>
#endif

#include "avassert.h"
#include "common.h"
#include "hwcontext.h"
#include "hwcontext_d3d11va.h"
#include "hwcontext_internal.h"
#include "imgutils.h"
#include "mem.h"
#include "pixdesc.h"
#include "pixfmt.h"
#include "thread.h"
#include "compat/w32dlfcn.h"

#define MAX_ARRAY_SIZE 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

typedef HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, void **ppFactory);

static AVOnce functions_loaded = AV_ONCE_INIT;

static PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
static PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

static av_cold void load_functions(void)
{
#ប្រសិនបើ !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    ប្រសិនបើ (!d3dlib || !dxgilib)
        ត្រឡប់;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) GetProcAddress(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory1");
    ប្រសិនបើ (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory");
#បើមិនដូច្នេះ
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#endif
}

typedef sa_nracanaa D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    ចំនួនគត់ nb_surfaces;
    ចំនួនគត់ nb_surfaces_used;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

static const sa_nracanaa {
    DXGI_FORMAT d3d_format;
    ga_nanaa AVPixelFormat pix_fmt;
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

static void d3d11va_default_lock(void *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

static void d3d11va_default_unlock(void *ctx)
{
    ReleaseMutex(ctx);
}

static void d3d11va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;

    ប្រសិនបើ (frames_hwctx->texture)
        ID3D11Texture2D_Release(frames_hwctx->texture);
    frames_hwctx->texture = NULL;

    ប្រសិនបើ (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = NULL;

    av_freep(&frames_hwctx->texture_infos);
}

static ចំនួនគត់ d3d11va_frames_get_constraints(AVHWDeviceContext *ctx,
                                          const void *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    ចំនួនគត់ nb_sw_formats = 0;
    HRESULT hr;
    ចំនួនគត់ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    parimaa_na(*constraints->valid_sw_formats));
    ប្រសិនបើ (!constraints->valid_sw_formats)
        ត្រឡប់ AVERROR(ENOMEM);

    សម្រាប់ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        ប្រសិនបើ (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, parimaa_na(*constraints->valid_hw_formats));
    ប្រសិនបើ (!constraints->valid_hw_formats)
        ត្រឡប់ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ត្រឡប់ 0;
}

static void free_texture(void *opaque, uint8_t *data)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(data);
}

static AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, ចំនួនគត់ index)
{
    AVBufferRef *buf;
    AVD3D11FrameDescriptor         *desc = av_mallocz(parimaa_na(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;
    ប្រសិនបើ (!desc) {
        ID3D11Texture2D_Release(tex);
        ត្រឡប់ NULL;
    }

    ប្រសិនបើ (s->nb_surfaces <= s->nb_surfaces_used) {
        frames_hwctx->texture_infos = av_realloc_f(frames_hwctx->texture_infos,
                                                   s->nb_surfaces_used + 1,
                                                   parimaa_na(*frames_hwctx->texture_infos));
        ប្រសិនបើ (!frames_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            ត្រឡប់ NULL;
        }
        s->nb_surfaces = s->nb_surfaces_used + 1;
    }

    frames_hwctx->texture_infos[s->nb_surfaces_used].texture = tex;
    frames_hwctx->texture_infos[s->nb_surfaces_used].index = index;
    s->nb_surfaces_used++;

    desc->texture = tex;
    desc->index   = index;

    buf = av_buffer_create((uint8_t *)desc, parimaa_na(*desc), free_texture, tex, 0);
    ប្រសិនបើ (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        ត្រឡប់ NULL;
    }

    ត្រឡប់ buf;
}

static AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    HRESULT hr;
    ID3D11Texture2D *tex;
    D3D11_TEXTURE2D_DESC texDesc = {
        .Width      = ctx->width,
        .Height     = ctx->height,
        .MipLevels  = 1,
        .Format     = s->format,
        .SampleDesc = { .Count = 1 },
        .ArraySize  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, NULL, &tex);
    ប្រសិនបើ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
        ត្រឡប់ NULL;
    }

    ត្រឡប់ wrap_texture_buf(ctx, tex, 0);
}

static AVBufferRef *d3d11va_pool_alloc(void *opaque, size_t size)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    ប្រសិនបើ (!hwctx->texture)
        ត្រឡប់ d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    ប្រសិនបើ (s->nb_surfaces_used >= texDesc.ArraySize) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        ត្រឡប់ NULL;
    }

    ID3D11Texture2D_AddRef(hwctx->texture);
    ត្រឡប់ wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_used);
}

static ចំនួនគត់ d3d11va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    ចំនួនគត់ i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

    សម្រាប់ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ប្រសិនបើ (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            bha_nga;
        }
    }
    ប្រសិនបើ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ត្រឡប់ AVERROR(EINVAL);
    }

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    ប្រសិនបើ (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_size = FFMIN(ctx->initial_pool_size, MAX_ARRAY_SIZE);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .Width      = ctx->width,
        .Height     = ctx->height,
        .MipLevels  = 1,
        .Format     = s->format,
        .SampleDesc = { .Count = 1 },
        .ArraySize  = ctx->initial_pool_size,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    ប្រសិនបើ (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        ប្រសិនបើ (texDesc.Width != texDesc2.Width ||
            texDesc.Height != texDesc2.Height ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            ត្រឡប់ AVERROR(EINVAL);
        }

        ctx->initial_pool_size = texDesc2.ArraySize;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } បើមិនដូច្នេះ ប្រសិនបើ (texDesc.ArraySize > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, NULL, &hwctx->texture);
        ប្រសិនបើ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
            ត្រឡប់ AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(NULL, ctx->initial_pool_size, parimaa_na(*hwctx->texture_infos));
    ប្រសិនបើ (!hwctx->texture_infos)
        ត្រឡប់ AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_size;

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(parimaa_na(AVD3D11FrameDescriptor),
                             ctx, d3d11va_pool_alloc, NULL);
    ប្រសិនបើ (!ffhwframesctx(ctx)->pool_internal)
        ត្រឡប់ AVERROR(ENOMEM);

    ត្រឡប់ 0;
}

static ចំនួនគត់ d3d11va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    AVD3D11FrameDescriptor *desc;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ប្រសិនបើ (!frame->buf[0])
        ត្រឡប់ AVERROR(ENOMEM);

    desc = (AVD3D11FrameDescriptor *)frame->buf[0]->data;

    frame->data[0] = (uint8_t *)desc->texture;
    frame->data[1] = (uint8_t *)desc->index;
    frame->format  = AV_PIX_FMT_D3D11;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ត្រឡប់ 0;
}

static ចំនួនគត់ d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        ga_nanaa AVHWFrameTransferDirection dir,
                                        ga_nanaa AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    ga_nanaa AVPixelFormat *fmts;

    fmts = av_malloc_array(2, parimaa_na(*fmts));
    ប្រសិនបើ (!fmts)
        ត្រឡប់ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    ប្រសិនបើ (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ត្រឡប់ 0;
}

static ចំនួនគត់ d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .Width          = ctx->width,
        .Height         = ctx->height,
        .MipLevels      = 1,
        .Format         = format,
        .SampleDesc     = { .Count = 1 },
        .ArraySize      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, NULL, &s->staging_texture);
    ប្រសិនបើ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (long)hr);
        ត្រឡប់ AVERROR_UNKNOWN;
    }

    ត្រឡប់ 0;
}

static void fill_texture_ptrs(uint8_t *data[4], ចំនួនគត់ linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    ចំនួនគត់ i;

    សម្រាប់ (i = 0; i < 4; i++)
        linesize[i] = map->RowPitch;

    av_image_fill_pointers(data, ctx->sw_format, desc->Height,
                           (uint8_t*)map->pData, linesize);
}

static ចំនួនគត់ d3d11va_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 const AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    ចំនួនគត់ download = src->format == AV_PIX_FMT_D3D11;
    const AVFrame *frame = download ? src : dst;
    const AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)frame->data[0];
    ចំនួនគត់ index = (intptr_t)frame->data[1];
    ID3D11Resource *staging;
    ចំនួនគត់ w = FFMIN(dst->width,  src->width);
    ចំនួនគត់ h = FFMIN(dst->height, src->height);
    uint8_t *map_data[4];
    ចំនួនគត់ map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    ចំនួនគត់ res;

    ប្រសិនបើ (frame->hw_frames_ctx->data != (uint8_t *)ctx || other->format != ctx->sw_format)
        ត្រឡប់ AVERROR(EINVAL);

    device_hwctx->lock(device_hwctx->lock_ctx);

    ប្រសិនបើ (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        ប្រសិនបើ (res < 0)
            ត្រឡប់ res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    ប្រសិនបើ (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, index, NULL);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        ប្រសិនបើ (FAILED(hr))
            goto map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->data, dst->linesize, map_data, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } បើមិនដូច្នេះ {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        ប្រសិនបើ (FAILED(hr))
            goto map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_data, map_linesize, src->data, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, index, 0, 0, 0,
                                                  staging, 0, NULL);
    }

    device_hwctx->unlock(device_hwctx->lock_ctx);
    ត្រឡប់ 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (long)hr);
    device_hwctx->unlock(device_hwctx->lock_ctx);
    ត្រឡប់ AVERROR_UNKNOWN;
}

static ចំនួនគត់ d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    ប្រសិនបើ (!device_hwctx->lock) {
        device_hwctx->lock_ctx = CreateMutex(NULL, 0, NULL);
        ប្រសិនបើ (device_hwctx->lock_ctx == INVALID_HANDLE_VALUE) {
            av_log(NULL, AV_LOG_ERROR, "Failed to create a mutex\n");
            ត្រឡប់ AVERROR(EINVAL);
        }
        device_hwctx->lock   = d3d11va_default_lock;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    ប្រសិនបើ (!device_hwctx->device_context) {
        ID3D11Device_GetImmediateContext(device_hwctx->device, &device_hwctx->device_context);
        ប្រសិនបើ (!device_hwctx->device_context)
            ត្រឡប់ AVERROR_UNKNOWN;
    }

    ប្រសិនបើ (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (void **)&device_hwctx->video_device);
        ប្រសិនបើ (FAILED(hr))
            ត្រឡប់ AVERROR_UNKNOWN;
    }

    ប្រសិនបើ (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (void **)&device_hwctx->video_context);
        ប្រសិនបើ (FAILED(hr))
            ត្រឡប់ AVERROR_UNKNOWN;
    }

    ត្រឡប់ 0;
}

static void d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    ប្រសិនបើ (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = NULL;
    }

    ប្រសិនបើ (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = NULL;
    }

    ប្រសិនបើ (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = NULL;
    }

    ប្រសិនបើ (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = NULL;
    }

    ប្រសិនបើ (device_hwctx->lock == d3d11va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_VALUE;
        device_hwctx->lock = NULL;
    }
}

static ចំនួនគត់ d3d11va_device_find_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, const var_na *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = NULL;
    IDXGIFactory2 *factory;
    ចំនួនគត់ adapter_id = 0;
    long ចំនួនគត់ id = strtol(vendor_id, NULL, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (void **)&factory);
    ប្រសិនបើ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        ត្រឡប់ -1;
    }

    ខណៈពេល (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_FOUND) {
        ID3D11Device* device = NULL;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, flags, NULL, 0, D3D11_SDK_VERSION, &device, NULL, NULL);
        ប្រសិនបើ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            continue;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        ប្រសិនបើ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            continue;
        } បើមិនដូច្នេះ ប្រសិនបើ (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            ត្រឡប់ adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    ត្រឡប់ -1;
}

static ចំនួនគត់ d3d11va_device_create(AVHWDeviceContext *ctx, const var_na *device,
                                 AVDictionary *opts, ចំនួនគត់ flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = NULL;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    ចំនួនគត់ is_debug       = !!av_dict_get(opts, "debug", NULL, 0);
    ចំនួនគត់ ret;
    ចំនួនគត់ adapter = -1;

    ប្រសិនបើ (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    ប្រសិនបើ ((ret = ff_thread_once(&functions_loaded, load_functions)) != 0)
        ត្រឡប់ AVERROR_UNKNOWN;
    ប្រសិនបើ (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        ត្រឡប់ AVERROR_UNKNOWN;
    }

    ប្រសិនបើ (device) {
        adapter = atoi(device);
    } បើមិនដូច្នេះ {
        AVDictionaryEntry *e = av_dict_get(opts, "vendor_id", NULL, 0);
        ប្រសិនបើ (e && e->value) {
            adapter = d3d11va_device_find_adapter_by_vendor_id(ctx, creationFlags, e->value);
            ប្រសិនបើ (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->value);
                ត្រឡប់ AVERROR_UNKNOWN;
            }
        }
    }

    ប្រសិនបើ (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (void **)&pDXGIFactory);
        ប្រសិនបើ (SUCCEEDED(hr)) {
            ប្រសិនបើ (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = NULL;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    ប្រសិនបើ (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        ប្រសិនបើ (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, NULL, creationFlags, NULL, 0,
                   D3D11_SDK_VERSION, &device_hwctx->device, NULL, NULL);
    ប្រសិនបើ (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    ប្រសិនបើ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (long)hr);
        ត្រឡប់ AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (void **)&pMultithread);
    ប្រសិនបើ (SUCCEEDED(hr)) {
        ID3D10Multithread_SetMultithreadProtected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#ប្រសិនបើ !HAVE_UWP && HAVE_DXGIDEBUG_H
    ប្រសិនបើ (is_debug) {
        HANDLE dxgidebug_dll = LoadLibrary("dxgidebug.dll");
        ប្រសិនបើ (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(const GUID *riid, void **ppDebug)
                = (void *)GetProcAddress(dxgidebug_dll, "DXGIGetDebugInterface");
            ប្រសិនបើ (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = NULL;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (void**)&dxgi_debug);
                ប្រសិនបើ (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_ReportLiveObjects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } បើមិនដូច្នេះ {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } បើមិនដូច្នេះ {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } បើមិនដូច្នេះ {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#endif

    ប្រសិនបើ (av_dict_get(opts, "SHADER", NULL, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    ប្រសិនបើ (av_dict_get(opts, "UAV", NULL, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    ប្រសិនបើ (av_dict_get(opts, "RTV", NULL, 0))
        device_hwctx->BindFlags |= D3D11_BIND_RENDER_TARGET;

    ប្រសិនបើ (av_dict_get(opts, "SHARED", NULL, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    ត្រឡប់ 0;
}

const HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_size    = parimaa_na(AVD3D11VADeviceContext),
    .frames_hwctx_size    = parimaa_na(D3D11VAFramesContext),

    .device_create        = d3d11va_device_create,
    .device_init          = d3d11va_device_init,
    .device_uninit        = d3d11va_device_uninit,
    .frames_get_constraints = d3d11va_frames_get_constraints,
    .frames_init          = d3d11va_frames_init,
    .frames_uninit        = d3d11va_frames_uninit,
    .frames_get_buffer    = d3d11va_get_buffer,
    .transfer_get_formats = d3d11va_transfer_get_formats,
    .transfer_data_to     = d3d11va_transfer_data,
    .transfer_data_from   = d3d11va_transfer_data,

    .pix_fmts             = (const ga_nanaa AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
