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

#define COBJMACROS

#ضمن <initguid.h>
#ضمن <d3d11.h>
#ضمن <dxgi1_2.h>

#ܐܢ HAVE_DXGIDEBUG_H
#ضمن <dxgidebug.h>
#endif

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

#define MAX_ARRAY_SIZE 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

تعريفنوع HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, فراغ **ppFactory);

ساكن AVOnce functions_loaded = AV_ONCE_INIT;

ساكن PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
ساكن PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

ساكن av_cold فراغ load_functions(فراغ)
{
#ܐܢ !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    ܐܢ (!d3dlib || !dxgilib)
        ܦܢܐ;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) GetProcAddress(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory1");
    ܐܢ (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory");
#ܐܚܪܢܐ
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#endif
}

تعريفنوع بنية D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    صحيح nb_surfaces;
    صحيح nb_surfaces_used;

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

ساكن فراغ d3d11va_default_lock(فراغ *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

ساكن فراغ d3d11va_default_unlock(فراغ *ctx)
{
    ReleaseMutex(ctx);
}

ساكن فراغ d3d11va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;

    ܐܢ (frames_hwctx->texture)
        ID3D11Texture2D_Release(frames_hwctx->texture);
    frames_hwctx->texture = عدم;

    ܐܢ (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = عدم;

    av_freep(&frames_hwctx->texture_infos);
}

ساكن صحيح d3d11va_frames_get_constraints(AVHWDeviceContext *ctx,
                                          ثابت فراغ *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    صحيح nb_sw_formats = 0;
    HRESULT hr;
    صحيح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    ܐܢ (!constraints->valid_sw_formats)
        ܦܢܐ AVERROR(ENOMEM);

    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        ܐܢ (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    ܐܢ (!constraints->valid_hw_formats)
        ܦܢܐ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ܦܢܐ 0;
}

ساكن فراغ free_texture(فراغ *opaque, uint8_t *data)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(data);
}

ساكن AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, صحيح index)
{
    AVBufferRef *buf;
    AVD3D11FrameDescriptor         *desc = av_mallocz(حجم(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;
    ܐܢ (!desc) {
        ID3D11Texture2D_Release(tex);
        ܦܢܐ عدم;
    }

    ܐܢ (s->nb_surfaces <= s->nb_surfaces_used) {
        frames_hwctx->texture_infos = av_realloc_f(frames_hwctx->texture_infos,
                                                   s->nb_surfaces_used + 1,
                                                   حجم(*frames_hwctx->texture_infos));
        ܐܢ (!frames_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            ܦܢܐ عدم;
        }
        s->nb_surfaces = s->nb_surfaces_used + 1;
    }

    frames_hwctx->texture_infos[s->nb_surfaces_used].texture = tex;
    frames_hwctx->texture_infos[s->nb_surfaces_used].index = index;
    s->nb_surfaces_used++;

    desc->texture = tex;
    desc->index   = index;

    buf = av_buffer_create((uint8_t *)desc, حجم(*desc), free_texture, tex, 0);
    ܐܢ (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        ܦܢܐ عدم;
    }

    ܦܢܐ buf;
}

ساكن AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
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

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, عدم, &tex);
    ܐܢ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
        ܦܢܐ عدم;
    }

    ܦܢܐ wrap_texture_buf(ctx, tex, 0);
}

ساكن AVBufferRef *d3d11va_pool_alloc(فراغ *opaque, size_t size)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    ܐܢ (!hwctx->texture)
        ܦܢܐ d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    ܐܢ (s->nb_surfaces_used >= texDesc.ArraySize) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        ܦܢܐ عدم;
    }

    ID3D11Texture2D_AddRef(hwctx->texture);
    ܦܢܐ wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_used);
}

ساكن صحيح d3d11va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    صحيح i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ܐܢ (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            اكسر;
        }
    }
    ܐܢ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ܦܢܐ AVERROR(EINVAL);
    }

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    ܐܢ (s->format == DXGI_FORMAT_420_OPAQUE)
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

    ܐܢ (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        ܐܢ (texDesc.Width != texDesc2.Width ||
            texDesc.Height != texDesc2.Height ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            ܦܢܐ AVERROR(EINVAL);
        }

        ctx->initial_pool_size = texDesc2.ArraySize;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } ܐܚܪܢܐ ܐܢ (texDesc.ArraySize > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, عدم, &hwctx->texture);
        ܐܢ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
            ܦܢܐ AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(عدم, ctx->initial_pool_size, حجم(*hwctx->texture_infos));
    ܐܢ (!hwctx->texture_infos)
        ܦܢܐ AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_size;

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(حجم(AVD3D11FrameDescriptor),
                             ctx, d3d11va_pool_alloc, عدم);
    ܐܢ (!ffhwframesctx(ctx)->pool_internal)
        ܦܢܐ AVERROR(ENOMEM);

    ܦܢܐ 0;
}

ساكن صحيح d3d11va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    AVD3D11FrameDescriptor *desc;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ܐܢ (!frame->buf[0])
        ܦܢܐ AVERROR(ENOMEM);

    desc = (AVD3D11FrameDescriptor *)frame->buf[0]->data;

    frame->data[0] = (uint8_t *)desc->texture;
    frame->data[1] = (uint8_t *)desc->index;
    frame->format  = AV_PIX_FMT_D3D11;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ܦܢܐ 0;
}

ساكن صحيح d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        تعداد AVHWFrameTransferDirection dir,
                                        تعداد AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    تعداد AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    ܐܢ (!fmts)
        ܦܢܐ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    ܐܢ (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ܦܢܐ 0;
}

ساكن صحيح d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
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

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, عدم, &s->staging_texture);
    ܐܢ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (long)hr);
        ܦܢܐ AVERROR_UNKNOWN;
    }

    ܦܢܐ 0;
}

ساكن فراغ fill_texture_ptrs(uint8_t *data[4], صحيح linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    صحيح i;

    لكل (i = 0; i < 4; i++)
        linesize[i] = map->RowPitch;

    av_image_fill_pointers(data, ctx->sw_format, desc->Height,
                           (uint8_t*)map->pData, linesize);
}

ساكن صحيح d3d11va_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    صحيح download = src->format == AV_PIX_FMT_D3D11;
    ثابت AVFrame *frame = download ? src : dst;
    ثابت AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)frame->data[0];
    صحيح index = (intptr_t)frame->data[1];
    ID3D11Resource *staging;
    صحيح w = FFMIN(dst->width,  src->width);
    صحيح h = FFMIN(dst->height, src->height);
    uint8_t *map_data[4];
    صحيح map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    صحيح res;

    ܐܢ (frame->hw_frames_ctx->data != (uint8_t *)ctx || other->format != ctx->sw_format)
        ܦܢܐ AVERROR(EINVAL);

    device_hwctx->lock(device_hwctx->lock_ctx);

    ܐܢ (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        ܐܢ (res < 0)
            ܦܢܐ res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    ܐܢ (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, index, عدم);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        ܐܢ (FAILED(hr))
            اذهب map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->data, dst->linesize, map_data, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } ܐܚܪܢܐ {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        ܐܢ (FAILED(hr))
            اذهب map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_data, map_linesize, src->data, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, index, 0, 0, 0,
                                                  staging, 0, عدم);
    }

    device_hwctx->unlock(device_hwctx->lock_ctx);
    ܦܢܐ 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (long)hr);
    device_hwctx->unlock(device_hwctx->lock_ctx);
    ܦܢܐ AVERROR_UNKNOWN;
}

ساكن صحيح d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    ܐܢ (!device_hwctx->lock) {
        device_hwctx->lock_ctx = CreateMutex(عدم, 0, عدم);
        ܐܢ (device_hwctx->lock_ctx == INVALID_HANDLE_VALUE) {
            av_log(عدم, AV_LOG_ERROR, "Failed to create a mutex\n");
            ܦܢܐ AVERROR(EINVAL);
        }
        device_hwctx->lock   = d3d11va_default_lock;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    ܐܢ (!device_hwctx->device_context) {
        ID3D11Device_GetImmediateContext(device_hwctx->device, &device_hwctx->device_context);
        ܐܢ (!device_hwctx->device_context)
            ܦܢܐ AVERROR_UNKNOWN;
    }

    ܐܢ (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (فراغ **)&device_hwctx->video_device);
        ܐܢ (FAILED(hr))
            ܦܢܐ AVERROR_UNKNOWN;
    }

    ܐܢ (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (فراغ **)&device_hwctx->video_context);
        ܐܢ (FAILED(hr))
            ܦܢܐ AVERROR_UNKNOWN;
    }

    ܦܢܐ 0;
}

ساكن فراغ d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    ܐܢ (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = عدم;
    }

    ܐܢ (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = عدم;
    }

    ܐܢ (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = عدم;
    }

    ܐܢ (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = عدم;
    }

    ܐܢ (device_hwctx->lock == d3d11va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_VALUE;
        device_hwctx->lock = عدم;
    }
}

ساكن صحيح d3d11va_device_find_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, ثابت حرف *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = عدم;
    IDXGIFactory2 *factory;
    صحيح adapter_id = 0;
    long صحيح id = strtol(vendor_id, عدم, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (فراغ **)&factory);
    ܐܢ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        ܦܢܐ -1;
    }

    ܟܡܐ (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_FOUND) {
        ID3D11Device* device = عدم;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, عدم, flags, عدم, 0, D3D11_SDK_VERSION, &device, عدم, عدم);
        ܐܢ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            استمر;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        ܐܢ (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            استمر;
        } ܐܚܪܢܐ ܐܢ (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            ܦܢܐ adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    ܦܢܐ -1;
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

    ܐܢ (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    ܐܢ ((ret = ff_thread_once(&functions_loaded, load_functions)) != 0)
        ܦܢܐ AVERROR_UNKNOWN;
    ܐܢ (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        ܦܢܐ AVERROR_UNKNOWN;
    }

    ܐܢ (device) {
        adapter = atoi(device);
    } ܐܚܪܢܐ {
        AVDictionaryEntry *e = av_dict_get(opts, "vendor_id", عدم, 0);
        ܐܢ (e && e->value) {
            adapter = d3d11va_device_find_adapter_by_vendor_id(ctx, creationFlags, e->value);
            ܐܢ (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->value);
                ܦܢܐ AVERROR_UNKNOWN;
            }
        }
    }

    ܐܢ (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (فراغ **)&pDXGIFactory);
        ܐܢ (SUCCEEDED(hr)) {
            ܐܢ (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = عدم;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    ܐܢ (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        ܐܢ (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, عدم, creationFlags, عدم, 0,
                   D3D11_SDK_VERSION, &device_hwctx->device, عدم, عدم);
    ܐܢ (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    ܐܢ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (long)hr);
        ܦܢܐ AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (فراغ **)&pMultithread);
    ܐܢ (SUCCEEDED(hr)) {
        ID3D10Multithread_SetMultithreadProtected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#ܐܢ !HAVE_UWP && HAVE_DXGIDEBUG_H
    ܐܢ (is_debug) {
        HANDLE dxgidebug_dll = LoadLibrary("dxgidebug.dll");
        ܐܢ (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(ثابت GUID *riid, فراغ **ppDebug)
                = (فراغ *)GetProcAddress(dxgidebug_dll, "DXGIGetDebugInterface");
            ܐܢ (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = عدم;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (فراغ**)&dxgi_debug);
                ܐܢ (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_ReportLiveObjects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } ܐܚܪܢܐ {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } ܐܚܪܢܐ {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } ܐܚܪܢܐ {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#endif

    ܐܢ (av_dict_get(opts, "SHADER", عدم, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    ܐܢ (av_dict_get(opts, "UAV", عدم, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    ܐܢ (av_dict_get(opts, "RTV", عدم, 0))
        device_hwctx->BindFlags |= D3D11_BIND_RENDER_TARGET;

    ܐܢ (av_dict_get(opts, "SHARED", عدم, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    ܦܢܐ 0;
}

ثابت HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_size    = حجم(AVD3D11VADeviceContext),
    .frames_hwctx_size    = حجم(D3D11VAFramesContext),

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

    .pix_fmts             = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
