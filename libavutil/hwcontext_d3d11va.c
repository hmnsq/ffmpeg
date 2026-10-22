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

#define COBJMACROS

#شامل <initguid.h>
#شامل <d3d11.h>
#شامل <dxgi1_2.h>

#اگر HAVE_DXGIDEBUG_H
#شامل <dxgidebug.h>
#endif

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

#define MAX_ARRAY_SIZE 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

تعریفنوع HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, تهی **ppFactory);

ایستا AVOnce functions_loaded = AV_ONCE_INIT;

ایستا PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
ایستا PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

ایستا av_cold تهی load_functions(تهی)
{
#اگر !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    اگر (!d3dlib || !dxgilib)
        بازگشت;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) GetProcAddress(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory1");
    اگر (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory");
#وگرنه
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#endif
}

تعریفنوع ساختار D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    صحیح nb_surfaces;
    صحیح nb_surfaces_used;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

ایستا ثابت ساختار {
    DXGI_FORMAT d3d_format;
    شمارش AVPixelFormat pix_fmt;
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

ایستا تهی d3d11va_default_lock(تهی *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

ایستا تهی d3d11va_default_unlock(تهی *ctx)
{
    ReleaseMutex(ctx);
}

ایستا تهی d3d11va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;

    اگر (frames_hwctx->texture)
        ID3D11Texture2D_Release(frames_hwctx->texture);
    frames_hwctx->texture = پوچ;

    اگر (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = پوچ;

    av_freep(&frames_hwctx->texture_infos);
}

ایستا صحیح d3d11va_frames_get_constraints(AVHWDeviceContext *ctx,
                                          ثابت تهی *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    صحیح nb_sw_formats = 0;
    HRESULT hr;
    صحیح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    اندازه(*constraints->valid_sw_formats));
    اگر (!constraints->valid_sw_formats)
        بازگشت AVERROR(ENOMEM);

    برای (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        اگر (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, اندازه(*constraints->valid_hw_formats));
    اگر (!constraints->valid_hw_formats)
        بازگشت AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    بازگشت 0;
}

ایستا تهی free_texture(تهی *opaque, uint8_t *data)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(data);
}

ایستا AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, صحیح index)
{
    AVBufferRef *buf;
    AVD3D11FrameDescriptor         *desc = av_mallocz(اندازه(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;
    اگر (!desc) {
        ID3D11Texture2D_Release(tex);
        بازگشت پوچ;
    }

    اگر (s->nb_surfaces <= s->nb_surfaces_used) {
        frames_hwctx->texture_infos = av_realloc_f(frames_hwctx->texture_infos,
                                                   s->nb_surfaces_used + 1,
                                                   اندازه(*frames_hwctx->texture_infos));
        اگر (!frames_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            بازگشت پوچ;
        }
        s->nb_surfaces = s->nb_surfaces_used + 1;
    }

    frames_hwctx->texture_infos[s->nb_surfaces_used].texture = tex;
    frames_hwctx->texture_infos[s->nb_surfaces_used].index = index;
    s->nb_surfaces_used++;

    desc->texture = tex;
    desc->index   = index;

    buf = av_buffer_create((uint8_t *)desc, اندازه(*desc), free_texture, tex, 0);
    اگر (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        بازگشت پوچ;
    }

    بازگشت buf;
}

ایستا AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
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
        .SampleDesc = { .شمار_2 = 1 },
        .ArraySize  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, پوچ, &tex);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
        بازگشت پوچ;
    }

    بازگشت wrap_texture_buf(ctx, tex, 0);
}

ایستا AVBufferRef *d3d11va_pool_alloc(تهی *opaque, size_t size)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    اگر (!hwctx->texture)
        بازگشت d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    اگر (s->nb_surfaces_used >= texDesc.ArraySize) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        بازگشت پوچ;
    }

    ID3D11Texture2D_AddRef(hwctx->texture);
    بازگشت wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_used);
}

ایستا صحیح d3d11va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    صحیح i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

    برای (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        اگر (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            بشکن;
        }
    }
    اگر (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        بازگشت AVERROR(EINVAL);
    }

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    اگر (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_size = FFMIN(ctx->initial_pool_size, MAX_ARRAY_SIZE);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .Width      = ctx->width,
        .Height     = ctx->height,
        .MipLevels  = 1,
        .Format     = s->format,
        .SampleDesc = { .شمار_2 = 1 },
        .ArraySize  = ctx->initial_pool_size,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    اگر (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        اگر (texDesc.Width != texDesc2.Width ||
            texDesc.Height != texDesc2.Height ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            بازگشت AVERROR(EINVAL);
        }

        ctx->initial_pool_size = texDesc2.ArraySize;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } وگرنه اگر (texDesc.ArraySize > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, پوچ, &hwctx->texture);
        اگر (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
            بازگشت AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(پوچ, ctx->initial_pool_size, اندازه(*hwctx->texture_infos));
    اگر (!hwctx->texture_infos)
        بازگشت AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_size;

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(اندازه(AVD3D11FrameDescriptor),
                             ctx, d3d11va_pool_alloc, پوچ);
    اگر (!ffhwframesctx(ctx)->pool_internal)
        بازگشت AVERROR(ENOMEM);

    بازگشت 0;
}

ایستا صحیح d3d11va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    AVD3D11FrameDescriptor *desc;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    اگر (!frame->buf[0])
        بازگشت AVERROR(ENOMEM);

    desc = (AVD3D11FrameDescriptor *)frame->buf[0]->data;

    frame->data[0] = (uint8_t *)desc->texture;
    frame->data[1] = (uint8_t *)desc->index;
    frame->format  = AV_PIX_FMT_D3D11;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    بازگشت 0;
}

ایستا صحیح d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        شمارش AVHWFrameTransferDirection dir,
                                        شمارش AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    شمارش AVPixelFormat *fmts;

    fmts = av_malloc_array(2, اندازه(*fmts));
    اگر (!fmts)
        بازگشت AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    اگر (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    بازگشت 0;
}

ایستا صحیح d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .Width          = ctx->width,
        .Height         = ctx->height,
        .MipLevels      = 1,
        .Format         = format,
        .SampleDesc     = { .شمار_2 = 1 },
        .ArraySize      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, پوچ, &s->staging_texture);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (long)hr);
        بازگشت AVERROR_UNKNOWN;
    }

    بازگشت 0;
}

ایستا تهی fill_texture_ptrs(uint8_t *data[4], صحیح linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    صحیح i;

    برای (i = 0; i < 4; i++)
        linesize[i] = map->RowPitch;

    av_image_fill_pointers(data, ctx->sw_format, desc->Height,
                           (uint8_t*)map->pData, linesize);
}

ایستا صحیح d3d11va_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    صحیح download = src->format == AV_PIX_FMT_D3D11;
    ثابت AVFrame *frame = download ? src : dst;
    ثابت AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)frame->data[0];
    صحیح index = (intptr_t)frame->data[1];
    ID3D11Resource *staging;
    صحیح w = FFMIN(dst->width,  src->width);
    صحیح h = FFMIN(dst->height, src->height);
    uint8_t *map_data[4];
    صحیح map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    صحیح res;

    اگر (frame->hw_frames_ctx->data != (uint8_t *)ctx || other->format != ctx->sw_format)
        بازگشت AVERROR(EINVAL);

    device_hwctx->lock(device_hwctx->lock_ctx);

    اگر (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        اگر (res < 0)
            بازگشت res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    اگر (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, index, پوچ);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        اگر (FAILED(hr))
            برو map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->data, dst->linesize, map_data, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } وگرنه {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        اگر (FAILED(hr))
            برو map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_data, map_linesize, src->data, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, index, 0, 0, 0,
                                                  staging, 0, پوچ);
    }

    device_hwctx->unlock(device_hwctx->lock_ctx);
    بازگشت 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (long)hr);
    device_hwctx->unlock(device_hwctx->lock_ctx);
    بازگشت AVERROR_UNKNOWN;
}

ایستا صحیح d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    اگر (!device_hwctx->lock) {
        device_hwctx->lock_ctx = CreateMutex(پوچ, 0, پوچ);
        اگر (device_hwctx->lock_ctx == INVALID_HANDLE_مقدار) {
            av_log(پوچ, AV_LOG_ERROR, "Failed to create a mutex\n");
            بازگشت AVERROR(EINVAL);
        }
        device_hwctx->lock   = d3d11va_default_lock;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    اگر (!device_hwctx->device_context) {
        ID3D11Device_GetImmediateContext(device_hwctx->device, &device_hwctx->device_context);
        اگر (!device_hwctx->device_context)
            بازگشت AVERROR_UNKNOWN;
    }

    اگر (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (تهی **)&device_hwctx->video_device);
        اگر (FAILED(hr))
            بازگشت AVERROR_UNKNOWN;
    }

    اگر (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (تهی **)&device_hwctx->video_context);
        اگر (FAILED(hr))
            بازگشت AVERROR_UNKNOWN;
    }

    بازگشت 0;
}

ایستا تهی d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    اگر (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = پوچ;
    }

    اگر (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = پوچ;
    }

    اگر (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = پوچ;
    }

    اگر (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = پوچ;
    }

    اگر (device_hwctx->lock == d3d11va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_مقدار;
        device_hwctx->lock = پوچ;
    }
}

ایستا صحیح d3d11va_device_find_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, ثابت نویسه *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = پوچ;
    IDXGIFactory2 *factory;
    صحیح adapter_id = 0;
    long صحیح id = strtol(vendor_id, پوچ, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (تهی **)&factory);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        بازگشت -1;
    }

    وقتی (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_FOUND) {
        ID3D11Device* device = پوچ;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, پوچ, flags, پوچ, 0, D3D11_SDK_VERSION, &device, پوچ, پوچ);
        اگر (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            ادامه;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        اگر (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            ادامه;
        } وگرنه اگر (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            بازگشت adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    بازگشت -1;
}

ایستا صحیح d3d11va_device_create(AVHWDeviceContext *ctx, ثابت نویسه *device,
                                 AVDictionary *opts, صحیح flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = پوچ;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    صحیح is_debug       = !!av_dict_get(opts, "debug", پوچ, 0);
    صحیح ret;
    صحیح adapter = -1;

    اگر (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    اگر ((ret = ff_thread_once(&functions_loaded, load_functions)) != 0)
        بازگشت AVERROR_UNKNOWN;
    اگر (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        بازگشت AVERROR_UNKNOWN;
    }

    اگر (device) {
        adapter = atoi(device);
    } وگرنه {
        AVDictionaryEntry *e = av_dict_get(opts, "vendor_id", پوچ, 0);
        اگر (e && e->مقدار) {
            adapter = d3d11va_device_find_adapter_by_vendor_id(ctx, creationFlags, e->مقدار);
            اگر (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->مقدار);
                بازگشت AVERROR_UNKNOWN;
            }
        }
    }

    اگر (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (تهی **)&pDXGIFactory);
        اگر (SUCCEEDED(hr)) {
            اگر (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = پوچ;
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

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, پوچ, creationFlags, پوچ, 0,
                   D3D11_SDK_VERSION, &device_hwctx->device, پوچ, پوچ);
    اگر (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (long)hr);
        بازگشت AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (تهی **)&pMultithread);
    اگر (SUCCEEDED(hr)) {
        ID3D10Multithread_SetMultithreadProtected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#اگر !HAVE_UWP && HAVE_DXGIDEBUG_H
    اگر (is_debug) {
        HANDLE dxgidebug_dll = LoadLibrary("dxgidebug.dll");
        اگر (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(ثابت GUID *riid, تهی **ppDebug)
                = (تهی *)GetProcAddress(dxgidebug_dll, "DXGIGetDebugInterface");
            اگر (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = پوچ;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (تهی**)&dxgi_debug);
                اگر (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_ReportLiveObjects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } وگرنه {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } وگرنه {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } وگرنه {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#endif

    اگر (av_dict_get(opts, "SHADER", پوچ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    اگر (av_dict_get(opts, "UAV", پوچ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    اگر (av_dict_get(opts, "RTV", پوچ, 0))
        device_hwctx->BindFlags |= D3D11_BIND_RENDER_TARGET;

    اگر (av_dict_get(opts, "SHARED", پوچ, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    بازگشت 0;
}

ثابت HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_size    = اندازه(AVD3D11VADeviceContext),
    .frames_hwctx_size    = اندازه(D3D11VAFramesContext),

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

    .pix_fmts             = (ثابت شمارش AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
