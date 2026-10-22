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

#അന്തര്ഭാവ "config.h"

#അന്തര്ഭാവ <windows.h>

#define COBJMACROS

#അന്തര്ഭാവ <initguid.h>
#അന്തര്ഭാവ <d3d11.h>
#അന്തര്ഭാവ <dxgi1_2.h>

#എങ്കിൽ HAVE_DXGIDEBUG_H
#അന്തര്ഭാവ <dxgidebug.h>
#endif

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "hwcontext.h"
#അന്തര്ഭാവ "hwcontext_d3d11va.h"
#അന്തര്ഭാവ "hwcontext_internal.h"
#അന്തര്ഭാവ "imgutils.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "pixdesc.h"
#അന്തര്ഭാവ "pixfmt.h"
#അന്തര്ഭാവ "thread.h"
#അന്തര്ഭാവ "compat/w32dlfcn.h"

#define MAX_ARRAY_SIZE 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

തരനിർവചനം HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, ശൂന്യം **ppFactory);

സ്ഥിതം AVOnce functions_loaded = AV_ONCE_INIT;

സ്ഥിതം PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
സ്ഥിതം PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

സ്ഥിതം av_cold ശൂന്യം load_functions(ശൂന്യം)
{
#എങ്കിൽ !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    എങ്കിൽ (!d3dlib || !dxgilib)
        തിരികെ;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) GetProcAddress(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory1");
    എങ്കിൽ (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory");
#അല്ലെങ്കിൽ
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#endif
}

തരനിർവചനം ഘടന D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    പൂർണ്ണസംഖ്യ nb_surfaces;
    പൂർണ്ണസംഖ്യ nb_surfaces_used;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

സ്ഥിതം സ്ഥിരം ഘടന {
    DXGI_FORMAT d3d_format;
    എണ്ണൽ AVPixelFormat pix_fmt;
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

സ്ഥിതം ശൂന്യം d3d11va_default_lock(ശൂന്യം *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

സ്ഥിതം ശൂന്യം d3d11va_default_unlock(ശൂന്യം *ctx)
{
    ReleaseMutex(ctx);
}

സ്ഥിതം ശൂന്യം d3d11va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;

    എങ്കിൽ (frames_hwctx->texture)
        ID3D11Texture2D_Release(frames_hwctx->texture);
    frames_hwctx->texture = ശൂന്യ;

    എങ്കിൽ (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = ശൂന്യ;

    av_freep(&frames_hwctx->texture_infos);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d11va_frames_get_constraints(AVHWDeviceContext *ctx,
                                          സ്ഥിരം ശൂന്യം *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    പൂർണ്ണസംഖ്യ nb_sw_formats = 0;
    HRESULT hr;
    പൂർണ്ണസംഖ്യ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    വലുപ്പം(*constraints->valid_sw_formats));
    എങ്കിൽ (!constraints->valid_sw_formats)
        തിരികെ AVERROR(ENOMEM);

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        എങ്കിൽ (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, വലുപ്പം(*constraints->valid_hw_formats));
    എങ്കിൽ (!constraints->valid_hw_formats)
        തിരികെ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം free_texture(ശൂന്യം *opaque, uint8_t *data)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(data);
}

സ്ഥിതം AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, പൂർണ്ണസംഖ്യ index)
{
    AVBufferRef *buf;
    AVD3D11FrameDescriptor         *desc = av_mallocz(വലുപ്പം(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;
    എങ്കിൽ (!desc) {
        ID3D11Texture2D_Release(tex);
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (s->nb_surfaces <= s->nb_surfaces_used) {
        frames_hwctx->texture_infos = av_realloc_f(frames_hwctx->texture_infos,
                                                   s->nb_surfaces_used + 1,
                                                   വലുപ്പം(*frames_hwctx->texture_infos));
        എങ്കിൽ (!frames_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            തിരികെ ശൂന്യ;
        }
        s->nb_surfaces = s->nb_surfaces_used + 1;
    }

    frames_hwctx->texture_infos[s->nb_surfaces_used].texture = tex;
    frames_hwctx->texture_infos[s->nb_surfaces_used].index = index;
    s->nb_surfaces_used++;

    desc->texture = tex;
    desc->index   = index;

    buf = av_buffer_create((uint8_t *)desc, വലുപ്പം(*desc), free_texture, tex, 0);
    എങ്കിൽ (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        തിരികെ ശൂന്യ;
    }

    തിരികെ buf;
}

സ്ഥിതം AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
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
        .SampleDesc = { .എണ്ണം_2 = 1 },
        .ArraySize  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ശൂന്യ, &tex);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
        തിരികെ ശൂന്യ;
    }

    തിരികെ wrap_texture_buf(ctx, tex, 0);
}

സ്ഥിതം AVBufferRef *d3d11va_pool_alloc(ശൂന്യം *opaque, size_t size)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    എങ്കിൽ (!hwctx->texture)
        തിരികെ d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    എങ്കിൽ (s->nb_surfaces_used >= texDesc.ArraySize) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        തിരികെ ശൂന്യ;
    }

    ID3D11Texture2D_AddRef(hwctx->texture);
    തിരികെ wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_used);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d11va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    പൂർണ്ണസംഖ്യ i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

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

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    എങ്കിൽ (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_size = FFMIN(ctx->initial_pool_size, MAX_ARRAY_SIZE);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .Width      = ctx->width,
        .Height     = ctx->height,
        .MipLevels  = 1,
        .Format     = s->format,
        .SampleDesc = { .എണ്ണം_2 = 1 },
        .ArraySize  = ctx->initial_pool_size,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    എങ്കിൽ (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        എങ്കിൽ (texDesc.Width != texDesc2.Width ||
            texDesc.Height != texDesc2.Height ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            തിരികെ AVERROR(EINVAL);
        }

        ctx->initial_pool_size = texDesc2.ArraySize;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } അല്ലെങ്കിൽ എങ്കിൽ (texDesc.ArraySize > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ശൂന്യ, &hwctx->texture);
        എങ്കിൽ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
            തിരികെ AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(ശൂന്യ, ctx->initial_pool_size, വലുപ്പം(*hwctx->texture_infos));
    എങ്കിൽ (!hwctx->texture_infos)
        തിരികെ AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_size;

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(വലുപ്പം(AVD3D11FrameDescriptor),
                             ctx, d3d11va_pool_alloc, ശൂന്യ);
    എങ്കിൽ (!ffhwframesctx(ctx)->pool_internal)
        തിരികെ AVERROR(ENOMEM);

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d11va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    AVD3D11FrameDescriptor *desc;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    എങ്കിൽ (!frame->buf[0])
        തിരികെ AVERROR(ENOMEM);

    desc = (AVD3D11FrameDescriptor *)frame->buf[0]->data;

    frame->data[0] = (uint8_t *)desc->texture;
    frame->data[1] = (uint8_t *)desc->index;
    frame->format  = AV_PIX_FMT_D3D11;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        എണ്ണൽ AVHWFrameTransferDirection dir,
                                        എണ്ണൽ AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    എണ്ണൽ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, വലുപ്പം(*fmts));
    എങ്കിൽ (!fmts)
        തിരികെ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    എങ്കിൽ (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .Width          = ctx->width,
        .Height         = ctx->height,
        .MipLevels      = 1,
        .Format         = format,
        .SampleDesc     = { .എണ്ണം_2 = 1 },
        .ArraySize      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ശൂന്യ, &s->staging_texture);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (long)hr);
        തിരികെ AVERROR_UNKNOWN;
    }

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം fill_texture_ptrs(uint8_t *data[4], പൂർണ്ണസംഖ്യ linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < 4; i++)
        linesize[i] = map->RowPitch;

    av_image_fill_pointers(data, ctx->sw_format, desc->Height,
                           (uint8_t*)map->pData, linesize);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d11va_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 സ്ഥിരം AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    പൂർണ്ണസംഖ്യ download = src->format == AV_PIX_FMT_D3D11;
    സ്ഥിരം AVFrame *frame = download ? src : dst;
    സ്ഥിരം AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)frame->data[0];
    പൂർണ്ണസംഖ്യ index = (intptr_t)frame->data[1];
    ID3D11Resource *staging;
    പൂർണ്ണസംഖ്യ w = FFMIN(dst->width,  src->width);
    പൂർണ്ണസംഖ്യ h = FFMIN(dst->height, src->height);
    uint8_t *map_data[4];
    പൂർണ്ണസംഖ്യ map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    പൂർണ്ണസംഖ്യ res;

    എങ്കിൽ (frame->hw_frames_ctx->data != (uint8_t *)ctx || other->format != ctx->sw_format)
        തിരികെ AVERROR(EINVAL);

    device_hwctx->lock(device_hwctx->lock_ctx);

    എങ്കിൽ (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        എങ്കിൽ (res < 0)
            തിരികെ res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    എങ്കിൽ (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, index, ശൂന്യ);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        എങ്കിൽ (FAILED(hr))
            പോകുക map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->data, dst->linesize, map_data, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } അല്ലെങ്കിൽ {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        എങ്കിൽ (FAILED(hr))
            പോകുക map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_data, map_linesize, src->data, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, index, 0, 0, 0,
                                                  staging, 0, ശൂന്യ);
    }

    device_hwctx->unlock(device_hwctx->lock_ctx);
    തിരികെ 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (long)hr);
    device_hwctx->unlock(device_hwctx->lock_ctx);
    തിരികെ AVERROR_UNKNOWN;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    എങ്കിൽ (!device_hwctx->lock) {
        device_hwctx->lock_ctx = CreateMutex(ശൂന്യ, 0, ശൂന്യ);
        എങ്കിൽ (device_hwctx->lock_ctx == INVALID_HANDLE_മൂല്യം) {
            av_log(ശൂന്യ, AV_LOG_ERROR, "Failed to create a mutex\n");
            തിരികെ AVERROR(EINVAL);
        }
        device_hwctx->lock   = d3d11va_default_lock;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    എങ്കിൽ (!device_hwctx->device_context) {
        ID3D11Device_GetImmediateContext(device_hwctx->device, &device_hwctx->device_context);
        എങ്കിൽ (!device_hwctx->device_context)
            തിരികെ AVERROR_UNKNOWN;
    }

    എങ്കിൽ (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (ശൂന്യം **)&device_hwctx->video_device);
        എങ്കിൽ (FAILED(hr))
            തിരികെ AVERROR_UNKNOWN;
    }

    എങ്കിൽ (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (ശൂന്യം **)&device_hwctx->video_context);
        എങ്കിൽ (FAILED(hr))
            തിരികെ AVERROR_UNKNOWN;
    }

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    എങ്കിൽ (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = ശൂന്യ;
    }

    എങ്കിൽ (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = ശൂന്യ;
    }

    എങ്കിൽ (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = ശൂന്യ;
    }

    എങ്കിൽ (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = ശൂന്യ;
    }

    എങ്കിൽ (device_hwctx->lock == d3d11va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_മൂല്യം;
        device_hwctx->lock = ശൂന്യ;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d11va_device_find_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, സ്ഥിരം അക്ഷരം *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = ശൂന്യ;
    IDXGIFactory2 *factory;
    പൂർണ്ണസംഖ്യ adapter_id = 0;
    long പൂർണ്ണസംഖ്യ id = strtol(vendor_id, ശൂന്യ, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (ശൂന്യം **)&factory);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        തിരികെ -1;
    }

    ആകുമ്പോൾ (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_FOUND) {
        ID3D11Device* device = ശൂന്യ;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, ശൂന്യ, flags, ശൂന്യ, 0, D3D11_SDK_VERSION, &device, ശൂന്യ, ശൂന്യ);
        എങ്കിൽ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            തുടരുക;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        എങ്കിൽ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            തുടരുക;
        } അല്ലെങ്കിൽ എങ്കിൽ (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            തിരികെ adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    തിരികെ -1;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d11va_device_create(AVHWDeviceContext *ctx, സ്ഥിരം അക്ഷരം *device,
                                 AVDictionary *opts, പൂർണ്ണസംഖ്യ flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = ശൂന്യ;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    പൂർണ്ണസംഖ്യ is_debug       = !!av_dict_get(opts, "debug", ശൂന്യ, 0);
    പൂർണ്ണസംഖ്യ ret;
    പൂർണ്ണസംഖ്യ adapter = -1;

    എങ്കിൽ (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    എങ്കിൽ ((ret = ff_thread_once(&functions_loaded, load_functions)) != 0)
        തിരികെ AVERROR_UNKNOWN;
    എങ്കിൽ (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    എങ്കിൽ (device) {
        adapter = atoi(device);
    } അല്ലെങ്കിൽ {
        AVDictionaryEntry *e = av_dict_get(opts, "vendor_id", ശൂന്യ, 0);
        എങ്കിൽ (e && e->മൂല്യം) {
            adapter = d3d11va_device_find_adapter_by_vendor_id(ctx, creationFlags, e->മൂല്യം);
            എങ്കിൽ (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->മൂല്യം);
                തിരികെ AVERROR_UNKNOWN;
            }
        }
    }

    എങ്കിൽ (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (ശൂന്യം **)&pDXGIFactory);
        എങ്കിൽ (SUCCEEDED(hr)) {
            എങ്കിൽ (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = ശൂന്യ;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    എങ്കിൽ (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        എങ്കിൽ (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, ശൂന്യ, creationFlags, ശൂന്യ, 0,
                   D3D11_SDK_VERSION, &device_hwctx->device, ശൂന്യ, ശൂന്യ);
    എങ്കിൽ (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (long)hr);
        തിരികെ AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (ശൂന്യം **)&pMultithread);
    എങ്കിൽ (SUCCEEDED(hr)) {
        ID3D10Multithread_SetMultithreadProtected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#എങ്കിൽ !HAVE_UWP && HAVE_DXGIDEBUG_H
    എങ്കിൽ (is_debug) {
        HANDLE dxgidebug_dll = LoadLibrary("dxgidebug.dll");
        എങ്കിൽ (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(സ്ഥിരം GUID *riid, ശൂന്യം **ppDebug)
                = (ശൂന്യം *)GetProcAddress(dxgidebug_dll, "DXGIGetDebugInterface");
            എങ്കിൽ (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = ശൂന്യ;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (ശൂന്യം**)&dxgi_debug);
                എങ്കിൽ (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_ReportLiveObjects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } അല്ലെങ്കിൽ {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } അല്ലെങ്കിൽ {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } അല്ലെങ്കിൽ {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#endif

    എങ്കിൽ (av_dict_get(opts, "SHADER", ശൂന്യ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    എങ്കിൽ (av_dict_get(opts, "UAV", ശൂന്യ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    എങ്കിൽ (av_dict_get(opts, "RTV", ശൂന്യ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_RENDER_TARGET;

    എങ്കിൽ (av_dict_get(opts, "SHARED", ശൂന്യ, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    തിരികെ 0;
}

സ്ഥിരം HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_size    = വലുപ്പം(AVD3D11VADeviceContext),
    .frames_hwctx_size    = വലുപ്പം(D3D11VAFramesContext),

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

    .pix_fmts             = (സ്ഥിരം എണ്ണൽ AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
