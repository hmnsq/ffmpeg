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

#अन्तर्भाव "config.h"

#अन्तर्भाव <windows.h>

#define COBJMACROS

#अन्तर्भाव <initguid.h>
#अन्तर्भाव <d3d11.h>
#अन्तर्भाव <dxgi1_2.h>

#जर HAVE_DXGIDEBUG_H
#अन्तर्भाव <dxgidebug.h>
#endif

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_d3d11va.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "imgutils.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "thread.h"
#अन्तर्भाव "compat/w32dlfcn.h"

#define MAX_ARRAY_SIZE 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

प्रकारव्याख्या HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, शून्य **ppFactory);

स्थिर AVOnce functions_loaded = AV_ONCE_INIT;

स्थिर PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
स्थिर PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

स्थिर av_cold शून्य load_functions(शून्य)
{
#जर !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    जर (!d3dlib || !dxgilib)
        परत;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) GetProcAddress(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory1");
    जर (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory");
#अन्यथा
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#endif
}

प्रकारव्याख्या संरचना D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    पूर्णांक nb_surfaces;
    पूर्णांक nb_surfaces_used;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

स्थिर स्थिरांक संरचना {
    DXGI_FORMAT d3d_format;
    गणना AVPixelFormat pix_fmt;
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

स्थिर शून्य d3d11va_default_lock(शून्य *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

स्थिर शून्य d3d11va_default_unlock(शून्य *ctx)
{
    ReleaseMutex(ctx);
}

स्थिर शून्य d3d11va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;

    जर (frames_hwctx->texture)
        ID3D11Texture2D_Release(frames_hwctx->texture);
    frames_hwctx->texture = रिक्त;

    जर (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = रिक्त;

    av_freep(&frames_hwctx->texture_infos);
}

स्थिर पूर्णांक d3d11va_frames_get_constraints(AVHWDeviceContext *ctx,
                                          स्थिरांक शून्य *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    पूर्णांक nb_sw_formats = 0;
    HRESULT hr;
    पूर्णांक i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    आकार(*constraints->valid_sw_formats));
    जर (!constraints->valid_sw_formats)
        परत AVERROR(ENOMEM);

    साठी (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        जर (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, आकार(*constraints->valid_hw_formats));
    जर (!constraints->valid_hw_formats)
        परत AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    परत 0;
}

स्थिर शून्य free_texture(शून्य *opaque, uint8_t *data)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(data);
}

स्थिर AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, पूर्णांक index)
{
    AVBufferRef *buf;
    AVD3D11FrameDescriptor         *desc = av_mallocz(आकार(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;
    जर (!desc) {
        ID3D11Texture2D_Release(tex);
        परत रिक्त;
    }

    जर (s->nb_surfaces <= s->nb_surfaces_used) {
        frames_hwctx->texture_infos = av_realloc_f(frames_hwctx->texture_infos,
                                                   s->nb_surfaces_used + 1,
                                                   आकार(*frames_hwctx->texture_infos));
        जर (!frames_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            परत रिक्त;
        }
        s->nb_surfaces = s->nb_surfaces_used + 1;
    }

    frames_hwctx->texture_infos[s->nb_surfaces_used].texture = tex;
    frames_hwctx->texture_infos[s->nb_surfaces_used].index = index;
    s->nb_surfaces_used++;

    desc->texture = tex;
    desc->index   = index;

    buf = av_buffer_create((uint8_t *)desc, आकार(*desc), free_texture, tex, 0);
    जर (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        परत रिक्त;
    }

    परत buf;
}

स्थिर AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
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
        .SampleDesc = { .मोजणी_2 = 1 },
        .ArraySize  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, रिक्त, &tex);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (दीर्घ)hr);
        परत रिक्त;
    }

    परत wrap_texture_buf(ctx, tex, 0);
}

स्थिर AVBufferRef *d3d11va_pool_alloc(शून्य *opaque, माप_प्रकार size)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    जर (!hwctx->texture)
        परत d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    जर (s->nb_surfaces_used >= texDesc.ArraySize) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        परत रिक्त;
    }

    ID3D11Texture2D_AddRef(hwctx->texture);
    परत wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_used);
}

स्थिर पूर्णांक d3d11va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    पूर्णांक i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

    साठी (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        जर (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            थांबा;
        }
    }
    जर (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        परत AVERROR(EINVAL);
    }

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    जर (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_size = FFMIN(ctx->initial_pool_size, MAX_ARRAY_SIZE);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .Width      = ctx->width,
        .Height     = ctx->height,
        .MipLevels  = 1,
        .Format     = s->format,
        .SampleDesc = { .मोजणी_2 = 1 },
        .ArraySize  = ctx->initial_pool_size,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    जर (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        जर (texDesc.Width != texDesc2.Width ||
            texDesc.Height != texDesc2.Height ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            परत AVERROR(EINVAL);
        }

        ctx->initial_pool_size = texDesc2.ArraySize;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } अन्यथा जर (texDesc.ArraySize > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, रिक्त, &hwctx->texture);
        जर (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (दीर्घ)hr);
            परत AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(रिक्त, ctx->initial_pool_size, आकार(*hwctx->texture_infos));
    जर (!hwctx->texture_infos)
        परत AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_size;

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(आकार(AVD3D11FrameDescriptor),
                             ctx, d3d11va_pool_alloc, रिक्त);
    जर (!ffhwframesctx(ctx)->pool_internal)
        परत AVERROR(ENOMEM);

    परत 0;
}

स्थिर पूर्णांक d3d11va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    AVD3D11FrameDescriptor *desc;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    जर (!frame->buf[0])
        परत AVERROR(ENOMEM);

    desc = (AVD3D11FrameDescriptor *)frame->buf[0]->data;

    frame->data[0] = (uint8_t *)desc->texture;
    frame->data[1] = (uint8_t *)desc->index;
    frame->format  = AV_PIX_FMT_D3D11;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    परत 0;
}

स्थिर पूर्णांक d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        गणना AVHWFrameTransferDirection dir,
                                        गणना AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    गणना AVPixelFormat *fmts;

    fmts = av_malloc_array(2, आकार(*fmts));
    जर (!fmts)
        परत AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    जर (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    परत 0;
}

स्थिर पूर्णांक d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .Width          = ctx->width,
        .Height         = ctx->height,
        .MipLevels      = 1,
        .Format         = format,
        .SampleDesc     = { .मोजणी_2 = 1 },
        .ArraySize      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, रिक्त, &s->staging_texture);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (दीर्घ)hr);
        परत AVERROR_UNKNOWN;
    }

    परत 0;
}

स्थिर शून्य fill_texture_ptrs(uint8_t *data[4], पूर्णांक linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    पूर्णांक i;

    साठी (i = 0; i < 4; i++)
        linesize[i] = map->RowPitch;

    av_image_fill_pointers(data, ctx->sw_format, desc->Height,
                           (uint8_t*)map->pData, linesize);
}

स्थिर पूर्णांक d3d11va_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 स्थिरांक AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    पूर्णांक download = src->format == AV_PIX_FMT_D3D11;
    स्थिरांक AVFrame *frame = download ? src : dst;
    स्थिरांक AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)frame->data[0];
    पूर्णांक index = (intptr_t)frame->data[1];
    ID3D11Resource *staging;
    पूर्णांक w = FFMIN(dst->width,  src->width);
    पूर्णांक h = FFMIN(dst->height, src->height);
    uint8_t *map_data[4];
    पूर्णांक map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    पूर्णांक res;

    जर (frame->hw_frames_ctx->data != (uint8_t *)ctx || other->format != ctx->sw_format)
        परत AVERROR(EINVAL);

    device_hwctx->lock(device_hwctx->lock_ctx);

    जर (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        जर (res < 0)
            परत res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    जर (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, index, रिक्त);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        जर (FAILED(hr))
            जा map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->data, dst->linesize, map_data, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } अन्यथा {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        जर (FAILED(hr))
            जा map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_data, map_linesize, src->data, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, index, 0, 0, 0,
                                                  staging, 0, रिक्त);
    }

    device_hwctx->unlock(device_hwctx->lock_ctx);
    परत 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (दीर्घ)hr);
    device_hwctx->unlock(device_hwctx->lock_ctx);
    परत AVERROR_UNKNOWN;
}

स्थिर पूर्णांक d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    जर (!device_hwctx->lock) {
        device_hwctx->lock_ctx = CreateMutex(रिक्त, 0, रिक्त);
        जर (device_hwctx->lock_ctx == INVALID_HANDLE_मूल्य) {
            av_log(रिक्त, AV_LOG_ERROR, "Failed to create a mutex\n");
            परत AVERROR(EINVAL);
        }
        device_hwctx->lock   = d3d11va_default_lock;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    जर (!device_hwctx->device_context) {
        ID3D11Device_GetImmediateContext(device_hwctx->device, &device_hwctx->device_context);
        जर (!device_hwctx->device_context)
            परत AVERROR_UNKNOWN;
    }

    जर (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (शून्य **)&device_hwctx->video_device);
        जर (FAILED(hr))
            परत AVERROR_UNKNOWN;
    }

    जर (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (शून्य **)&device_hwctx->video_context);
        जर (FAILED(hr))
            परत AVERROR_UNKNOWN;
    }

    परत 0;
}

स्थिर शून्य d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    जर (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = रिक्त;
    }

    जर (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = रिक्त;
    }

    जर (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = रिक्त;
    }

    जर (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = रिक्त;
    }

    जर (device_hwctx->lock == d3d11va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_मूल्य;
        device_hwctx->lock = रिक्त;
    }
}

स्थिर पूर्णांक d3d11va_device_find_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, स्थिरांक अक्षर *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = रिक्त;
    IDXGIFactory2 *factory;
    पूर्णांक adapter_id = 0;
    दीर्घ पूर्णांक id = म_से_दीर्घ(vendor_id, रिक्त, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (शून्य **)&factory);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        परत -1;
    }

    पर्यंत (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_FOUND) {
        ID3D11Device* device = रिक्त;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, रिक्त, flags, रिक्त, 0, D3D11_SDK_VERSION, &device, रिक्त, रिक्त);
        जर (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            सुरूठेवा;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        जर (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            सुरूठेवा;
        } अन्यथा जर (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            परत adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    परत -1;
}

स्थिर पूर्णांक d3d11va_device_create(AVHWDeviceContext *ctx, स्थिरांक अक्षर *device,
                                 AVDictionary *opts, पूर्णांक flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = रिक्त;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    पूर्णांक is_debug       = !!av_dict_get(opts, "debug", रिक्त, 0);
    पूर्णांक ret;
    पूर्णांक adapter = -1;

    जर (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    जर ((ret = ff_thread_once(&functions_loaded, load_functions)) != 0)
        परत AVERROR_UNKNOWN;
    जर (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        परत AVERROR_UNKNOWN;
    }

    जर (device) {
        adapter = म_से_प(device);
    } अन्यथा {
        AVDictionaryEntry *e = av_dict_get(opts, "vendor_id", रिक्त, 0);
        जर (e && e->मूल्य) {
            adapter = d3d11va_device_find_adapter_by_vendor_id(ctx, creationFlags, e->मूल्य);
            जर (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->मूल्य);
                परत AVERROR_UNKNOWN;
            }
        }
    }

    जर (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (शून्य **)&pDXGIFactory);
        जर (SUCCEEDED(hr)) {
            जर (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = रिक्त;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    जर (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        जर (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, रिक्त, creationFlags, रिक्त, 0,
                   D3D11_SDK_VERSION, &device_hwctx->device, रिक्त, रिक्त);
    जर (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (दीर्घ)hr);
        परत AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (शून्य **)&pMultithread);
    जर (SUCCEEDED(hr)) {
        ID3D10Multithread_SetMultithreadProtected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#जर !HAVE_UWP && HAVE_DXGIDEBUG_H
    जर (is_debug) {
        HANDLE dxgidebug_dll = LoadLibrary("dxgidebug.dll");
        जर (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(स्थिरांक GUID *riid, शून्य **ppDebug)
                = (शून्य *)GetProcAddress(dxgidebug_dll, "DXGIGetDebugInterface");
            जर (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = रिक्त;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (शून्य**)&dxgi_debug);
                जर (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_ReportLiveObjects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } अन्यथा {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } अन्यथा {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } अन्यथा {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#endif

    जर (av_dict_get(opts, "SHADER", रिक्त, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    जर (av_dict_get(opts, "UAV", रिक्त, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    जर (av_dict_get(opts, "RTV", रिक्त, 0))
        device_hwctx->BindFlags |= D3D11_BIND_RENDER_TARGET;

    जर (av_dict_get(opts, "SHARED", रिक्त, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    परत 0;
}

स्थिरांक HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_size    = आकार(AVD3D11VADeviceContext),
    .frames_hwctx_size    = आकार(D3D11VAFramesContext),

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

    .pix_fmts             = (स्थिरांक गणना AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
