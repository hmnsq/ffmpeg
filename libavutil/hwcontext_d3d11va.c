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

#அந்தர்பாவ "config.h"

#அந்தர்பாவ <windows.h>

#define COBJMACROS

#அந்தர்பாவ <initguid.h>
#அந்தர்பாவ <d3d11.h>
#அந்தர்பாவ <dxgi1_2.h>

#எனில் HAVE_DXGIDEBUG_H
#அந்தர்பாவ <dxgidebug.h>
#endif

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "hwcontext.h"
#அந்தர்பாவ "hwcontext_d3d11va.h"
#அந்தர்பாவ "hwcontext_internal.h"
#அந்தர்பாவ "imgutils.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "pixdesc.h"
#அந்தர்பாவ "pixfmt.h"
#அந்தர்பாவ "thread.h"
#அந்தர்பாவ "compat/w32dlfcn.h"

#define MAX_ARRAY_SIZE 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

வகைவரை HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, வெறுமை **ppFactory);

நிலையான AVOnce functions_loaded = AV_ONCE_INIT;

நிலையான PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
நிலையான PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

நிலையான av_cold வெறுமை load_functions(வெறுமை)
{
#எனில் !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    எனில் (!d3dlib || !dxgilib)
        திரும்பு;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) GetProcAddress(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory1");
    எனில் (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory");
#இல்லையெனில்
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#endif
}

வகைவரை கட்டமைப்பு D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    முழு nb_surfaces;
    முழு nb_surfaces_used;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

நிலையான மாறிலி கட்டமைப்பு {
    DXGI_FORMAT d3d_format;
    எண்ணிக்கை AVPixelFormat pix_fmt;
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

நிலையான வெறுமை d3d11va_default_lock(வெறுமை *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

நிலையான வெறுமை d3d11va_default_unlock(வெறுமை *ctx)
{
    ReleaseMutex(ctx);
}

நிலையான வெறுமை d3d11va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;

    எனில் (frames_hwctx->texture)
        ID3D11Texture2D_Release(frames_hwctx->texture);
    frames_hwctx->texture = வெற்று;

    எனில் (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = வெற்று;

    av_freep(&frames_hwctx->texture_infos);
}

நிலையான முழு d3d11va_frames_get_constraints(AVHWDeviceContext *ctx,
                                          மாறிலி வெறுமை *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    முழு nb_sw_formats = 0;
    HRESULT hr;
    முழு i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    அளவு(*constraints->valid_sw_formats));
    எனில் (!constraints->valid_sw_formats)
        திரும்பு AVERROR(ENOMEM);

    க்கு (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        எனில் (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, அளவு(*constraints->valid_hw_formats));
    எனில் (!constraints->valid_hw_formats)
        திரும்பு AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    திரும்பு 0;
}

நிலையான வெறுமை free_texture(வெறுமை *opaque, uint8_t *data)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(data);
}

நிலையான AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, முழு index)
{
    AVBufferRef *buf;
    AVD3D11FrameDescriptor         *desc = av_mallocz(அளவு(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;
    எனில் (!desc) {
        ID3D11Texture2D_Release(tex);
        திரும்பு வெற்று;
    }

    எனில் (s->nb_surfaces <= s->nb_surfaces_used) {
        frames_hwctx->texture_infos = av_realloc_f(frames_hwctx->texture_infos,
                                                   s->nb_surfaces_used + 1,
                                                   அளவு(*frames_hwctx->texture_infos));
        எனில் (!frames_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            திரும்பு வெற்று;
        }
        s->nb_surfaces = s->nb_surfaces_used + 1;
    }

    frames_hwctx->texture_infos[s->nb_surfaces_used].texture = tex;
    frames_hwctx->texture_infos[s->nb_surfaces_used].index = index;
    s->nb_surfaces_used++;

    desc->texture = tex;
    desc->index   = index;

    buf = av_buffer_create((uint8_t *)desc, அளவு(*desc), free_texture, tex, 0);
    எனில் (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        திரும்பு வெற்று;
    }

    திரும்பு buf;
}

நிலையான AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
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
        .SampleDesc = { .மொத்தம்_2 = 1 },
        .ArraySize  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, வெற்று, &tex);
    எனில் (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
        திரும்பு வெற்று;
    }

    திரும்பு wrap_texture_buf(ctx, tex, 0);
}

நிலையான AVBufferRef *d3d11va_pool_alloc(வெறுமை *opaque, size_t size)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    எனில் (!hwctx->texture)
        திரும்பு d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    எனில் (s->nb_surfaces_used >= texDesc.ArraySize) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        திரும்பு வெற்று;
    }

    ID3D11Texture2D_AddRef(hwctx->texture);
    திரும்பு wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_used);
}

நிலையான முழு d3d11va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    முழு i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

    க்கு (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        எனில் (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            நிறுத்து;
        }
    }
    எனில் (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        திரும்பு AVERROR(EINVAL);
    }

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    எனில் (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_size = FFMIN(ctx->initial_pool_size, MAX_ARRAY_SIZE);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .Width      = ctx->width,
        .Height     = ctx->height,
        .MipLevels  = 1,
        .Format     = s->format,
        .SampleDesc = { .மொத்தம்_2 = 1 },
        .ArraySize  = ctx->initial_pool_size,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    எனில் (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        எனில் (texDesc.Width != texDesc2.Width ||
            texDesc.Height != texDesc2.Height ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            திரும்பு AVERROR(EINVAL);
        }

        ctx->initial_pool_size = texDesc2.ArraySize;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } இல்லையெனில் எனில் (texDesc.ArraySize > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, வெற்று, &hwctx->texture);
        எனில் (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
            திரும்பு AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(வெற்று, ctx->initial_pool_size, அளவு(*hwctx->texture_infos));
    எனில் (!hwctx->texture_infos)
        திரும்பு AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_size;

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(அளவு(AVD3D11FrameDescriptor),
                             ctx, d3d11va_pool_alloc, வெற்று);
    எனில் (!ffhwframesctx(ctx)->pool_internal)
        திரும்பு AVERROR(ENOMEM);

    திரும்பு 0;
}

நிலையான முழு d3d11va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    AVD3D11FrameDescriptor *desc;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    எனில் (!frame->buf[0])
        திரும்பு AVERROR(ENOMEM);

    desc = (AVD3D11FrameDescriptor *)frame->buf[0]->data;

    frame->data[0] = (uint8_t *)desc->texture;
    frame->data[1] = (uint8_t *)desc->index;
    frame->format  = AV_PIX_FMT_D3D11;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    திரும்பு 0;
}

நிலையான முழு d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        எண்ணிக்கை AVHWFrameTransferDirection dir,
                                        எண்ணிக்கை AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    எண்ணிக்கை AVPixelFormat *fmts;

    fmts = av_malloc_array(2, அளவு(*fmts));
    எனில் (!fmts)
        திரும்பு AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    எனில் (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    திரும்பு 0;
}

நிலையான முழு d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .Width          = ctx->width,
        .Height         = ctx->height,
        .MipLevels      = 1,
        .Format         = format,
        .SampleDesc     = { .மொத்தம்_2 = 1 },
        .ArraySize      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, வெற்று, &s->staging_texture);
    எனில் (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (long)hr);
        திரும்பு AVERROR_UNKNOWN;
    }

    திரும்பு 0;
}

நிலையான வெறுமை fill_texture_ptrs(uint8_t *data[4], முழு linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    முழு i;

    க்கு (i = 0; i < 4; i++)
        linesize[i] = map->RowPitch;

    av_image_fill_pointers(data, ctx->sw_format, desc->Height,
                           (uint8_t*)map->pData, linesize);
}

நிலையான முழு d3d11va_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 மாறிலி AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    முழு download = src->format == AV_PIX_FMT_D3D11;
    மாறிலி AVFrame *frame = download ? src : dst;
    மாறிலி AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)frame->data[0];
    முழு index = (intptr_t)frame->data[1];
    ID3D11Resource *staging;
    முழு w = FFMIN(dst->width,  src->width);
    முழு h = FFMIN(dst->height, src->height);
    uint8_t *map_data[4];
    முழு map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    முழு res;

    எனில் (frame->hw_frames_ctx->data != (uint8_t *)ctx || other->format != ctx->sw_format)
        திரும்பு AVERROR(EINVAL);

    device_hwctx->lock(device_hwctx->lock_ctx);

    எனில் (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        எனில் (res < 0)
            திரும்பு res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    எனில் (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, index, வெற்று);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        எனில் (FAILED(hr))
            செல் map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->data, dst->linesize, map_data, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } இல்லையெனில் {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        எனில் (FAILED(hr))
            செல் map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_data, map_linesize, src->data, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, index, 0, 0, 0,
                                                  staging, 0, வெற்று);
    }

    device_hwctx->unlock(device_hwctx->lock_ctx);
    திரும்பு 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (long)hr);
    device_hwctx->unlock(device_hwctx->lock_ctx);
    திரும்பு AVERROR_UNKNOWN;
}

நிலையான முழு d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    எனில் (!device_hwctx->lock) {
        device_hwctx->lock_ctx = CreateMutex(வெற்று, 0, வெற்று);
        எனில் (device_hwctx->lock_ctx == INVALID_HANDLE_மதிப்பு) {
            av_log(வெற்று, AV_LOG_ERROR, "Failed to create a mutex\n");
            திரும்பு AVERROR(EINVAL);
        }
        device_hwctx->lock   = d3d11va_default_lock;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    எனில் (!device_hwctx->device_context) {
        ID3D11Device_GetImmediateContext(device_hwctx->device, &device_hwctx->device_context);
        எனில் (!device_hwctx->device_context)
            திரும்பு AVERROR_UNKNOWN;
    }

    எனில் (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (வெறுமை **)&device_hwctx->video_device);
        எனில் (FAILED(hr))
            திரும்பு AVERROR_UNKNOWN;
    }

    எனில் (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (வெறுமை **)&device_hwctx->video_context);
        எனில் (FAILED(hr))
            திரும்பு AVERROR_UNKNOWN;
    }

    திரும்பு 0;
}

நிலையான வெறுமை d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    எனில் (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = வெற்று;
    }

    எனில் (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = வெற்று;
    }

    எனில் (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = வெற்று;
    }

    எனில் (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = வெற்று;
    }

    எனில் (device_hwctx->lock == d3d11va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_மதிப்பு;
        device_hwctx->lock = வெற்று;
    }
}

நிலையான முழு d3d11va_device_find_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, மாறிலி எழுத்து *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = வெற்று;
    IDXGIFactory2 *factory;
    முழு adapter_id = 0;
    long முழு id = strtol(vendor_id, வெற்று, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (வெறுமை **)&factory);
    எனில் (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        திரும்பு -1;
    }

    போது (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_FOUND) {
        ID3D11Device* device = வெற்று;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, வெற்று, flags, வெற்று, 0, D3D11_SDK_VERSION, &device, வெற்று, வெற்று);
        எனில் (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            தொடர்;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        எனில் (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            தொடர்;
        } இல்லையெனில் எனில் (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            திரும்பு adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    திரும்பு -1;
}

நிலையான முழு d3d11va_device_create(AVHWDeviceContext *ctx, மாறிலி எழுத்து *device,
                                 AVDictionary *opts, முழு flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = வெற்று;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    முழு is_debug       = !!av_dict_get(opts, "debug", வெற்று, 0);
    முழு ret;
    முழு adapter = -1;

    எனில் (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    எனில் ((ret = ff_thread_once(&functions_loaded, load_functions)) != 0)
        திரும்பு AVERROR_UNKNOWN;
    எனில் (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    எனில் (device) {
        adapter = atoi(device);
    } இல்லையெனில் {
        AVDictionaryEntry *e = av_dict_get(opts, "vendor_id", வெற்று, 0);
        எனில் (e && e->மதிப்பு) {
            adapter = d3d11va_device_find_adapter_by_vendor_id(ctx, creationFlags, e->மதிப்பு);
            எனில் (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->மதிப்பு);
                திரும்பு AVERROR_UNKNOWN;
            }
        }
    }

    எனில் (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (வெறுமை **)&pDXGIFactory);
        எனில் (SUCCEEDED(hr)) {
            எனில் (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = வெற்று;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    எனில் (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        எனில் (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, வெற்று, creationFlags, வெற்று, 0,
                   D3D11_SDK_VERSION, &device_hwctx->device, வெற்று, வெற்று);
    எனில் (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    எனில் (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (long)hr);
        திரும்பு AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (வெறுமை **)&pMultithread);
    எனில் (SUCCEEDED(hr)) {
        ID3D10Multithread_SetMultithreadProtected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#எனில் !HAVE_UWP && HAVE_DXGIDEBUG_H
    எனில் (is_debug) {
        HANDLE dxgidebug_dll = LoadLibrary("dxgidebug.dll");
        எனில் (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(மாறிலி GUID *riid, வெறுமை **ppDebug)
                = (வெறுமை *)GetProcAddress(dxgidebug_dll, "DXGIGetDebugInterface");
            எனில் (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = வெற்று;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (வெறுமை**)&dxgi_debug);
                எனில் (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_ReportLiveObjects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } இல்லையெனில் {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } இல்லையெனில் {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } இல்லையெனில் {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#endif

    எனில் (av_dict_get(opts, "SHADER", வெற்று, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    எனில் (av_dict_get(opts, "UAV", வெற்று, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    எனில் (av_dict_get(opts, "RTV", வெற்று, 0))
        device_hwctx->BindFlags |= D3D11_BIND_RENDER_TARGET;

    எனில் (av_dict_get(opts, "SHARED", வெற்று, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    திரும்பு 0;
}

மாறிலி HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_size    = அளவு(AVD3D11VADeviceContext),
    .frames_hwctx_size    = அளவு(D3D11VAFramesContext),

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

    .pix_fmts             = (மாறிலி எண்ணிக்கை AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
