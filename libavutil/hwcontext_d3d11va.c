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

#અન્તર્ભાવ "config.h"

#અન્તર્ભાવ <windows.h>

#define COBJMACROS

#અન્તર્ભાવ <initguid.h>
#અન્તર્ભાવ <d3d11.h>
#અન્તર્ભાવ <dxgi1_2.h>

#જો HAVE_DXGIDEBUG_H
#અન્તર્ભાવ <dxgidebug.h>
#endif

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "hwcontext.h"
#અન્તર્ભાવ "hwcontext_d3d11va.h"
#અન્તર્ભાવ "hwcontext_internal.h"
#અન્તર્ભાવ "imgutils.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "pixdesc.h"
#અન્તર્ભાવ "pixfmt.h"
#અન્તર્ભાવ "thread.h"
#અન્તર્ભાવ "compat/w32dlfcn.h"

#define MAX_ARRAY_SIZE 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

પ્રકારવ્યાખ્યા HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, શૂન્ય **ppFactory);

સ્થિર AVOnce functions_loaded = AV_ONCE_INIT;

સ્થિર PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
સ્થિર PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

સ્થિર av_cold શૂન્ય load_functions(શૂન્ય)
{
#જો !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    જો (!d3dlib || !dxgilib)
        પાછા;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) GetProcAddress(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory1");
    જો (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory");
#નહીંતર
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#endif
}

પ્રકારવ્યાખ્યા સંરચના D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    પૂર્ણાંક nb_surfaces;
    પૂર્ણાંક nb_surfaces_used;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

સ્થિર અચલ સંરચના {
    DXGI_FORMAT d3d_format;
    ગણના AVPixelFormat pix_fmt;
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

સ્થિર શૂન્ય d3d11va_default_lock(શૂન્ય *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

સ્થિર શૂન્ય d3d11va_default_unlock(શૂન્ય *ctx)
{
    ReleaseMutex(ctx);
}

સ્થિર શૂન્ય d3d11va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;

    જો (frames_hwctx->texture)
        ID3D11Texture2D_Release(frames_hwctx->texture);
    frames_hwctx->texture = ખાલી;

    જો (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = ખાલી;

    av_freep(&frames_hwctx->texture_infos);
}

સ્થિર પૂર્ણાંક d3d11va_frames_get_constraints(AVHWDeviceContext *ctx,
                                          અચલ શૂન્ય *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    પૂર્ણાંક nb_sw_formats = 0;
    HRESULT hr;
    પૂર્ણાંક i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    કદ(*constraints->valid_sw_formats));
    જો (!constraints->valid_sw_formats)
        પાછા AVERROR(ENOMEM);

    માટે (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        જો (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, કદ(*constraints->valid_hw_formats));
    જો (!constraints->valid_hw_formats)
        પાછા AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    પાછા 0;
}

સ્થિર શૂન્ય free_texture(શૂન્ય *opaque, uint8_t *data)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(data);
}

સ્થિર AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, પૂર્ણાંક index)
{
    AVBufferRef *buf;
    AVD3D11FrameDescriptor         *desc = av_mallocz(કદ(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;
    જો (!desc) {
        ID3D11Texture2D_Release(tex);
        પાછા ખાલી;
    }

    જો (s->nb_surfaces <= s->nb_surfaces_used) {
        frames_hwctx->texture_infos = av_realloc_f(frames_hwctx->texture_infos,
                                                   s->nb_surfaces_used + 1,
                                                   કદ(*frames_hwctx->texture_infos));
        જો (!frames_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            પાછા ખાલી;
        }
        s->nb_surfaces = s->nb_surfaces_used + 1;
    }

    frames_hwctx->texture_infos[s->nb_surfaces_used].texture = tex;
    frames_hwctx->texture_infos[s->nb_surfaces_used].index = index;
    s->nb_surfaces_used++;

    desc->texture = tex;
    desc->index   = index;

    buf = av_buffer_create((uint8_t *)desc, કદ(*desc), free_texture, tex, 0);
    જો (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        પાછા ખાલી;
    }

    પાછા buf;
}

સ્થિર AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
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
        .SampleDesc = { .ગણતરી_2 = 1 },
        .ArraySize  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ખાલી, &tex);
    જો (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
        પાછા ખાલી;
    }

    પાછા wrap_texture_buf(ctx, tex, 0);
}

સ્થિર AVBufferRef *d3d11va_pool_alloc(શૂન્ય *opaque, size_t size)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    જો (!hwctx->texture)
        પાછા d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    જો (s->nb_surfaces_used >= texDesc.ArraySize) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        પાછા ખાલી;
    }

    ID3D11Texture2D_AddRef(hwctx->texture);
    પાછા wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_used);
}

સ્થિર પૂર્ણાંક d3d11va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    પૂર્ણાંક i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

    માટે (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        જો (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            તોડો;
        }
    }
    જો (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        પાછા AVERROR(EINVAL);
    }

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    જો (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_size = FFMIN(ctx->initial_pool_size, MAX_ARRAY_SIZE);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .Width      = ctx->width,
        .Height     = ctx->height,
        .MipLevels  = 1,
        .Format     = s->format,
        .SampleDesc = { .ગણતરી_2 = 1 },
        .ArraySize  = ctx->initial_pool_size,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    જો (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        જો (texDesc.Width != texDesc2.Width ||
            texDesc.Height != texDesc2.Height ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            પાછા AVERROR(EINVAL);
        }

        ctx->initial_pool_size = texDesc2.ArraySize;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } નહીંતર જો (texDesc.ArraySize > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ખાલી, &hwctx->texture);
        જો (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
            પાછા AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(ખાલી, ctx->initial_pool_size, કદ(*hwctx->texture_infos));
    જો (!hwctx->texture_infos)
        પાછા AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_size;

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(કદ(AVD3D11FrameDescriptor),
                             ctx, d3d11va_pool_alloc, ખાલી);
    જો (!ffhwframesctx(ctx)->pool_internal)
        પાછા AVERROR(ENOMEM);

    પાછા 0;
}

સ્થિર પૂર્ણાંક d3d11va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    AVD3D11FrameDescriptor *desc;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    જો (!frame->buf[0])
        પાછા AVERROR(ENOMEM);

    desc = (AVD3D11FrameDescriptor *)frame->buf[0]->data;

    frame->data[0] = (uint8_t *)desc->texture;
    frame->data[1] = (uint8_t *)desc->index;
    frame->format  = AV_PIX_FMT_D3D11;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    પાછા 0;
}

સ્થિર પૂર્ણાંક d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        ગણના AVHWFrameTransferDirection dir,
                                        ગણના AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    ગણના AVPixelFormat *fmts;

    fmts = av_malloc_array(2, કદ(*fmts));
    જો (!fmts)
        પાછા AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    જો (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    પાછા 0;
}

સ્થિર પૂર્ણાંક d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .Width          = ctx->width,
        .Height         = ctx->height,
        .MipLevels      = 1,
        .Format         = format,
        .SampleDesc     = { .ગણતરી_2 = 1 },
        .ArraySize      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ખાલી, &s->staging_texture);
    જો (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (long)hr);
        પાછા AVERROR_UNKNOWN;
    }

    પાછા 0;
}

સ્થિર શૂન્ય fill_texture_ptrs(uint8_t *data[4], પૂર્ણાંક linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    પૂર્ણાંક i;

    માટે (i = 0; i < 4; i++)
        linesize[i] = map->RowPitch;

    av_image_fill_pointers(data, ctx->sw_format, desc->Height,
                           (uint8_t*)map->pData, linesize);
}

સ્થિર પૂર્ણાંક d3d11va_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 અચલ AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    પૂર્ણાંક download = src->format == AV_PIX_FMT_D3D11;
    અચલ AVFrame *frame = download ? src : dst;
    અચલ AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)frame->data[0];
    પૂર્ણાંક index = (intptr_t)frame->data[1];
    ID3D11Resource *staging;
    પૂર્ણાંક w = FFMIN(dst->width,  src->width);
    પૂર્ણાંક h = FFMIN(dst->height, src->height);
    uint8_t *map_data[4];
    પૂર્ણાંક map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    પૂર્ણાંક res;

    જો (frame->hw_frames_ctx->data != (uint8_t *)ctx || other->format != ctx->sw_format)
        પાછા AVERROR(EINVAL);

    device_hwctx->lock(device_hwctx->lock_ctx);

    જો (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        જો (res < 0)
            પાછા res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    જો (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, index, ખાલી);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        જો (FAILED(hr))
            જાઓ map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->data, dst->linesize, map_data, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } નહીંતર {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        જો (FAILED(hr))
            જાઓ map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_data, map_linesize, src->data, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, index, 0, 0, 0,
                                                  staging, 0, ખાલી);
    }

    device_hwctx->unlock(device_hwctx->lock_ctx);
    પાછા 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (long)hr);
    device_hwctx->unlock(device_hwctx->lock_ctx);
    પાછા AVERROR_UNKNOWN;
}

સ્થિર પૂર્ણાંક d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    જો (!device_hwctx->lock) {
        device_hwctx->lock_ctx = CreateMutex(ખાલી, 0, ખાલી);
        જો (device_hwctx->lock_ctx == INVALID_HANDLE_કિંમત) {
            av_log(ખાલી, AV_LOG_ERROR, "Failed to create a mutex\n");
            પાછા AVERROR(EINVAL);
        }
        device_hwctx->lock   = d3d11va_default_lock;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    જો (!device_hwctx->device_context) {
        ID3D11Device_GetImmediateContext(device_hwctx->device, &device_hwctx->device_context);
        જો (!device_hwctx->device_context)
            પાછા AVERROR_UNKNOWN;
    }

    જો (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (શૂન્ય **)&device_hwctx->video_device);
        જો (FAILED(hr))
            પાછા AVERROR_UNKNOWN;
    }

    જો (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (શૂન્ય **)&device_hwctx->video_context);
        જો (FAILED(hr))
            પાછા AVERROR_UNKNOWN;
    }

    પાછા 0;
}

સ્થિર શૂન્ય d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    જો (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = ખાલી;
    }

    જો (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = ખાલી;
    }

    જો (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = ખાલી;
    }

    જો (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = ખાલી;
    }

    જો (device_hwctx->lock == d3d11va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_કિંમત;
        device_hwctx->lock = ખાલી;
    }
}

સ્થિર પૂર્ણાંક d3d11va_device_find_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, અચલ અક્ષર *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = ખાલી;
    IDXGIFactory2 *factory;
    પૂર્ણાંક adapter_id = 0;
    long પૂર્ણાંક id = strtol(vendor_id, ખાલી, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (શૂન્ય **)&factory);
    જો (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        પાછા -1;
    }

    જ્યારે (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_FOUND) {
        ID3D11Device* device = ખાલી;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, ખાલી, flags, ખાલી, 0, D3D11_SDK_VERSION, &device, ખાલી, ખાલી);
        જો (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            ચાલુ;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        જો (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            ચાલુ;
        } નહીંતર જો (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            પાછા adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    પાછા -1;
}

સ્થિર પૂર્ણાંક d3d11va_device_create(AVHWDeviceContext *ctx, અચલ અક્ષર *device,
                                 AVDictionary *opts, પૂર્ણાંક flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = ખાલી;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    પૂર્ણાંક is_debug       = !!av_dict_get(opts, "debug", ખાલી, 0);
    પૂર્ણાંક ret;
    પૂર્ણાંક adapter = -1;

    જો (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    જો ((ret = ff_thread_once(&functions_loaded, load_functions)) != 0)
        પાછા AVERROR_UNKNOWN;
    જો (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        પાછા AVERROR_UNKNOWN;
    }

    જો (device) {
        adapter = atoi(device);
    } નહીંતર {
        AVDictionaryEntry *e = av_dict_get(opts, "vendor_id", ખાલી, 0);
        જો (e && e->કિંમત) {
            adapter = d3d11va_device_find_adapter_by_vendor_id(ctx, creationFlags, e->કિંમત);
            જો (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->કિંમત);
                પાછા AVERROR_UNKNOWN;
            }
        }
    }

    જો (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (શૂન્ય **)&pDXGIFactory);
        જો (SUCCEEDED(hr)) {
            જો (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = ખાલી;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    જો (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        જો (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, ખાલી, creationFlags, ખાલી, 0,
                   D3D11_SDK_VERSION, &device_hwctx->device, ખાલી, ખાલી);
    જો (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    જો (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (long)hr);
        પાછા AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (શૂન્ય **)&pMultithread);
    જો (SUCCEEDED(hr)) {
        ID3D10Multithread_SetMultithreadProtected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#જો !HAVE_UWP && HAVE_DXGIDEBUG_H
    જો (is_debug) {
        HANDLE dxgidebug_dll = LoadLibrary("dxgidebug.dll");
        જો (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(અચલ GUID *riid, શૂન્ય **ppDebug)
                = (શૂન્ય *)GetProcAddress(dxgidebug_dll, "DXGIGetDebugInterface");
            જો (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = ખાલી;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (શૂન્ય**)&dxgi_debug);
                જો (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_ReportLiveObjects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } નહીંતર {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } નહીંતર {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } નહીંતર {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#endif

    જો (av_dict_get(opts, "SHADER", ખાલી, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    જો (av_dict_get(opts, "UAV", ખાલી, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    જો (av_dict_get(opts, "RTV", ખાલી, 0))
        device_hwctx->BindFlags |= D3D11_BIND_RENDER_TARGET;

    જો (av_dict_get(opts, "SHARED", ખાલી, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    પાછા 0;
}

અચલ HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_size    = કદ(AVD3D11VADeviceContext),
    .frames_hwctx_size    = કદ(D3D11VAFramesContext),

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

    .pix_fmts             = (અચલ ગણના AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
