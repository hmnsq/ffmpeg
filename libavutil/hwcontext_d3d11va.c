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

#define COBJMACROS

#ಅನ್ತರ್ಭಾವ <initguid.h>
#ಅನ್ತರ್ಭಾವ <d3d11.h>
#ಅನ್ತರ್ಭಾವ <dxgi1_2.h>

#ಯದಿ HAVE_DXGIDEBUG_H
#ಅನ್ತರ್ಭಾವ <dxgidebug.h>
#endif

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

#define MAX_ARRAY_SIZE 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

ಪ್ರಕಾರನಿರ್ದೇಶ HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, ಶೂನ್ಯ **ppFactory);

ಸ್ಥಿರ AVOnce functions_loaded = AV_ONCE_INIT;

ಸ್ಥಿರ PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
ಸ್ಥಿರ PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

ಸ್ಥಿರ av_cold ಶೂನ್ಯ load_functions(ಶೂನ್ಯ)
{
#ಯದಿ !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    ಯದಿ (!d3dlib || !dxgilib)
        ಪ್ರತ್ಯಾಗಮ;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) GetProcAddress(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory1");
    ಯದಿ (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory");
#ಅನ್ಯಥಾ
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#endif
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    ಪೂರ್ಣಾಙ್ಕ nb_surfaces;
    ಪೂರ್ಣಾಙ್ಕ nb_surfaces_used;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
    DXGI_FORMAT d3d_format;
    ಗಣನಾ AVPixelFormat pix_fmt;
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

ಸ್ಥಿರ ಶೂನ್ಯ d3d11va_default_lock(ಶೂನ್ಯ *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

ಸ್ಥಿರ ಶೂನ್ಯ d3d11va_default_unlock(ಶೂನ್ಯ *ctx)
{
    ReleaseMutex(ctx);
}

ಸ್ಥಿರ ಶೂನ್ಯ d3d11va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;

    ಯದಿ (frames_hwctx->texture)
        ID3D11Texture2D_Release(frames_hwctx->texture);
    frames_hwctx->texture = ರಿಕ್ತ;

    ಯದಿ (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = ರಿಕ್ತ;

    av_freep(&frames_hwctx->texture_infos);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ d3d11va_frames_get_constraints(AVHWDeviceContext *ctx,
                                          ಧ್ರುವ ಶೂನ್ಯ *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    ಪೂರ್ಣಾಙ್ಕ nb_sw_formats = 0;
    HRESULT hr;
    ಪೂರ್ಣಾಙ್ಕ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    ಪರಿಮಾಣ(*constraints->valid_sw_formats));
    ಯದಿ (!constraints->valid_sw_formats)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        ಯದಿ (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ಪರಿಮಾಣ(*constraints->valid_hw_formats));
    ಯದಿ (!constraints->valid_hw_formats)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ free_texture(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(data);
}

ಸ್ಥಿರ AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, ಪೂರ್ಣಾಙ್ಕ index)
{
    AVBufferRef *buf;
    AVD3D11FrameDescriptor         *desc = av_mallocz(ಪರಿಮಾಣ(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;
    ಯದಿ (!desc) {
        ID3D11Texture2D_Release(tex);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (s->nb_surfaces <= s->nb_surfaces_used) {
        frames_hwctx->texture_infos = av_realloc_f(frames_hwctx->texture_infos,
                                                   s->nb_surfaces_used + 1,
                                                   ಪರಿಮಾಣ(*frames_hwctx->texture_infos));
        ಯದಿ (!frames_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
        s->nb_surfaces = s->nb_surfaces_used + 1;
    }

    frames_hwctx->texture_infos[s->nb_surfaces_used].texture = tex;
    frames_hwctx->texture_infos[s->nb_surfaces_used].index = index;
    s->nb_surfaces_used++;

    desc->texture = tex;
    desc->index   = index;

    buf = av_buffer_create((uint8_t *)desc, ಪರಿಮಾಣ(*desc), free_texture, tex, 0);
    ಯದಿ (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ buf;
}

ಸ್ಥಿರ AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
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
        .SampleDesc = { .ಎಣಿಕೆ_2 = 1 },
        .ArraySize  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ರಿಕ್ತ, &tex);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ wrap_texture_buf(ctx, tex, 0);
}

ಸ್ಥಿರ AVBufferRef *d3d11va_pool_alloc(ಶೂನ್ಯ *opaque, size_t size)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    ಯದಿ (!hwctx->texture)
        ಪ್ರತ್ಯಾಗಮ d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    ಯದಿ (s->nb_surfaces_used >= texDesc.ArraySize) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ID3D11Texture2D_AddRef(hwctx->texture);
    ಪ್ರತ್ಯಾಗಮ wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_used);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ d3d11va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    ಪೂರ್ಣಾಙ್ಕ i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ಯದಿ (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            ಭಙ್ಗ;
        }
    }
    ಯದಿ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    ಯದಿ (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_size = FFMIN(ctx->initial_pool_size, MAX_ARRAY_SIZE);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .Width      = ctx->width,
        .Height     = ctx->height,
        .MipLevels  = 1,
        .Format     = s->format,
        .SampleDesc = { .ಎಣಿಕೆ_2 = 1 },
        .ArraySize  = ctx->initial_pool_size,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    ಯದಿ (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        ಯದಿ (texDesc.Width != texDesc2.Width ||
            texDesc.Height != texDesc2.Height ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }

        ctx->initial_pool_size = texDesc2.ArraySize;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } ಅನ್ಯಥಾ ಯದಿ (texDesc.ArraySize > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ರಿಕ್ತ, &hwctx->texture);
        ಯದಿ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
            ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(ರಿಕ್ತ, ctx->initial_pool_size, ಪರಿಮಾಣ(*hwctx->texture_infos));
    ಯದಿ (!hwctx->texture_infos)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_size;

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(ಪರಿಮಾಣ(AVD3D11FrameDescriptor),
                             ctx, d3d11va_pool_alloc, ರಿಕ್ತ);
    ಯದಿ (!ffhwframesctx(ctx)->pool_internal)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ d3d11va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    AVD3D11FrameDescriptor *desc;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ಯದಿ (!frame->buf[0])
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    desc = (AVD3D11FrameDescriptor *)frame->buf[0]->data;

    frame->data[0] = (uint8_t *)desc->texture;
    frame->data[1] = (uint8_t *)desc->index;
    frame->format  = AV_PIX_FMT_D3D11;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        ಗಣನಾ AVHWFrameTransferDirection dir,
                                        ಗಣನಾ AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    ಗಣನಾ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ಪರಿಮಾಣ(*fmts));
    ಯದಿ (!fmts)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    ಯದಿ (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .Width          = ctx->width,
        .Height         = ctx->height,
        .MipLevels      = 1,
        .Format         = format,
        .SampleDesc     = { .ಎಣಿಕೆ_2 = 1 },
        .ArraySize      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ರಿಕ್ತ, &s->staging_texture);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (long)hr);
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ fill_texture_ptrs(uint8_t *data[4], ಪೂರ್ಣಾಙ್ಕ linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < 4; i++)
        linesize[i] = map->RowPitch;

    av_image_fill_pointers(data, ctx->sw_format, desc->Height,
                           (uint8_t*)map->pData, linesize);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ d3d11va_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 ಧ್ರುವ AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    ಪೂರ್ಣಾಙ್ಕ download = src->format == AV_PIX_FMT_D3D11;
    ಧ್ರುವ AVFrame *frame = download ? src : dst;
    ಧ್ರುವ AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)frame->data[0];
    ಪೂರ್ಣಾಙ್ಕ index = (intptr_t)frame->data[1];
    ID3D11Resource *staging;
    ಪೂರ್ಣಾಙ್ಕ w = FFMIN(dst->width,  src->width);
    ಪೂರ್ಣಾಙ್ಕ h = FFMIN(dst->height, src->height);
    uint8_t *map_data[4];
    ಪೂರ್ಣಾಙ್ಕ map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    ಪೂರ್ಣಾಙ್ಕ res;

    ಯದಿ (frame->hw_frames_ctx->data != (uint8_t *)ctx || other->format != ctx->sw_format)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    device_hwctx->lock(device_hwctx->lock_ctx);

    ಯದಿ (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        ಯದಿ (res < 0)
            ಪ್ರತ್ಯಾಗಮ res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    ಯದಿ (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, index, ರಿಕ್ತ);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        ಯದಿ (FAILED(hr))
            ಗಚ್ಛ map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->data, dst->linesize, map_data, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } ಅನ್ಯಥಾ {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        ಯದಿ (FAILED(hr))
            ಗಚ್ಛ map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_data, map_linesize, src->data, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, index, 0, 0, 0,
                                                  staging, 0, ರಿಕ್ತ);
    }

    device_hwctx->unlock(device_hwctx->lock_ctx);
    ಪ್ರತ್ಯಾಗಮ 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (long)hr);
    device_hwctx->unlock(device_hwctx->lock_ctx);
    ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    ಯದಿ (!device_hwctx->lock) {
        device_hwctx->lock_ctx = CreateMutex(ರಿಕ್ತ, 0, ರಿಕ್ತ);
        ಯದಿ (device_hwctx->lock_ctx == INVALID_HANDLE_ಮೌಲ್ಯ) {
            av_log(ರಿಕ್ತ, AV_LOG_ERROR, "Failed to create a mutex\n");
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
        device_hwctx->lock   = d3d11va_default_lock;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    ಯದಿ (!device_hwctx->device_context) {
        ID3D11Device_GetImmediateContext(device_hwctx->device, &device_hwctx->device_context);
        ಯದಿ (!device_hwctx->device_context)
            ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಯದಿ (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (ಶೂನ್ಯ **)&device_hwctx->video_device);
        ಯದಿ (FAILED(hr))
            ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಯದಿ (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (ಶೂನ್ಯ **)&device_hwctx->video_context);
        ಯದಿ (FAILED(hr))
            ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    ಯದಿ (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = ರಿಕ್ತ;
    }

    ಯದಿ (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = ರಿಕ್ತ;
    }

    ಯದಿ (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = ರಿಕ್ತ;
    }

    ಯದಿ (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = ರಿಕ್ತ;
    }

    ಯದಿ (device_hwctx->lock == d3d11va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_ಮೌಲ್ಯ;
        device_hwctx->lock = ರಿಕ್ತ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ d3d11va_device_find_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, ಧ್ರುವ ವರ್ಣ *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = ರಿಕ್ತ;
    IDXGIFactory2 *factory;
    ಪೂರ್ಣಾಙ್ಕ adapter_id = 0;
    long ಪೂರ್ಣಾಙ್ಕ id = strtol(vendor_id, ರಿಕ್ತ, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (ಶೂನ್ಯ **)&factory);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        ಪ್ರತ್ಯಾಗಮ -1;
    }

    ಯಾವತ್ (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_FOUND) {
        ID3D11Device* device = ರಿಕ್ತ;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, ರಿಕ್ತ, flags, ರಿಕ್ತ, 0, D3D11_SDK_VERSION, &device, ರಿಕ್ತ, ರಿಕ್ತ);
        ಯದಿ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            ಅನುವರ್ತ;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        ಯದಿ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            ಅನುವರ್ತ;
        } ಅನ್ಯಥಾ ಯದಿ (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            ಪ್ರತ್ಯಾಗಮ adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    ಪ್ರತ್ಯಾಗಮ -1;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ d3d11va_device_create(AVHWDeviceContext *ctx, ಧ್ರುವ ವರ್ಣ *device,
                                 AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = ರಿಕ್ತ;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    ಪೂರ್ಣಾಙ್ಕ is_debug       = !!av_dict_get(opts, "debug", ರಿಕ್ತ, 0);
    ಪೂರ್ಣಾಙ್ಕ ret;
    ಪೂರ್ಣಾಙ್ಕ adapter = -1;

    ಯದಿ (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    ಯದಿ ((ret = ff_thread_once(&functions_loaded, load_functions)) != 0)
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    ಯದಿ (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಯದಿ (device) {
        adapter = atoi(device);
    } ಅನ್ಯಥಾ {
        AVDictionaryEntry *e = av_dict_get(opts, "vendor_id", ರಿಕ್ತ, 0);
        ಯದಿ (e && e->ಮೌಲ್ಯ) {
            adapter = d3d11va_device_find_adapter_by_vendor_id(ctx, creationFlags, e->ಮೌಲ್ಯ);
            ಯದಿ (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->ಮೌಲ್ಯ);
                ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
            }
        }
    }

    ಯದಿ (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (ಶೂನ್ಯ **)&pDXGIFactory);
        ಯದಿ (SUCCEEDED(hr)) {
            ಯದಿ (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = ರಿಕ್ತ;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    ಯದಿ (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        ಯದಿ (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, ರಿಕ್ತ, creationFlags, ರಿಕ್ತ, 0,
                   D3D11_SDK_VERSION, &device_hwctx->device, ರಿಕ್ತ, ರಿಕ್ತ);
    ಯದಿ (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (long)hr);
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (ಶೂನ್ಯ **)&pMultithread);
    ಯದಿ (SUCCEEDED(hr)) {
        ID3D10Multithread_SetMultithreadProtected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#ಯದಿ !HAVE_UWP && HAVE_DXGIDEBUG_H
    ಯದಿ (is_debug) {
        HANDLE dxgidebug_dll = LoadLibrary("dxgidebug.dll");
        ಯದಿ (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(ಧ್ರುವ GUID *riid, ಶೂನ್ಯ **ppDebug)
                = (ಶೂನ್ಯ *)GetProcAddress(dxgidebug_dll, "DXGIGetDebugInterface");
            ಯದಿ (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = ರಿಕ್ತ;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (ಶೂನ್ಯ**)&dxgi_debug);
                ಯದಿ (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_ReportLiveObjects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } ಅನ್ಯಥಾ {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } ಅನ್ಯಥಾ {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } ಅನ್ಯಥಾ {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#endif

    ಯದಿ (av_dict_get(opts, "SHADER", ರಿಕ್ತ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    ಯದಿ (av_dict_get(opts, "UAV", ರಿಕ್ತ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    ಯದಿ (av_dict_get(opts, "RTV", ರಿಕ್ತ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_RENDER_TARGET;

    ಯದಿ (av_dict_get(opts, "SHARED", ರಿಕ್ತ, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಧ್ರುವ HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_size    = ಪರಿಮಾಣ(AVD3D11VADeviceContext),
    .frames_hwctx_size    = ಪರಿಮಾಣ(D3D11VAFramesContext),

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

    .pix_fmts             = (ಧ್ರುವ ಗಣನಾ AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
