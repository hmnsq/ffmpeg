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

#অন্তর্ভাব "config.h"

#অন্তর্ভাব <windows.h>

#define COBJMACROS

#অন্তর্ভাব <initguid.h>
#অন্তর্ভাব <d3d11.h>
#অন্তর্ভাব <dxgi1_2.h>

#যদি HAVE_DXGIDEBUG_H
#অন্তর্ভাব <dxgidebug.h>
#endif

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "hwcontext.h"
#অন্তর্ভাব "hwcontext_d3d11va.h"
#অন্তর্ভাব "hwcontext_internal.h"
#অন্তর্ভাব "imgutils.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "pixdesc.h"
#অন্তর্ভাব "pixfmt.h"
#অন্তর্ভাব "thread.h"
#অন্তর্ভাব "compat/w32dlfcn.h"

#define MAX_ARRAY_SIZE 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

প্রকারনির্দেশ HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, শূন্য **ppFactory);

স্থির AVOnce functions_loaded = AV_ONCE_INIT;

স্থির PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
স্থির PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

স্থির av_cold শূন্য load_functions(শূন্য)
{
#যদি !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    যদি (!d3dlib || !dxgilib)
        প্রত্যাগম;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) GetProcAddress(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory1");
    যদি (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory");
#অন্যথা
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#endif
}

প্রকারনির্দেশ সংরচনা D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    পূর্ণাঙ্ক nb_surfaces;
    পূর্ণাঙ্ক nb_surfaces_used;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

স্থির ধ্রুব সংরচনা {
    DXGI_FORMAT d3d_format;
    গণনা AVPixelFormat pix_fmt;
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

স্থির শূন্য d3d11va_default_lock(শূন্য *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

স্থির শূন্য d3d11va_default_unlock(শূন্য *ctx)
{
    ReleaseMutex(ctx);
}

স্থির শূন্য d3d11va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;

    যদি (frames_hwctx->texture)
        ID3D11Texture2D_Release(frames_hwctx->texture);
    frames_hwctx->texture = রিক্ত;

    যদি (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = রিক্ত;

    av_freep(&frames_hwctx->texture_infos);
}

স্থির পূর্ণাঙ্ক d3d11va_frames_get_constraints(AVHWDeviceContext *ctx,
                                          ধ্রুব শূন্য *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    পূর্ণাঙ্ক nb_sw_formats = 0;
    HRESULT hr;
    পূর্ণাঙ্ক i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    পরিমাণ(*constraints->valid_sw_formats));
    যদি (!constraints->valid_sw_formats)
        প্রত্যাগম AVERROR(ENOMEM);

    প্রতি (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        যদি (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, পরিমাণ(*constraints->valid_hw_formats));
    যদি (!constraints->valid_hw_formats)
        প্রত্যাগম AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    প্রত্যাগম 0;
}

স্থির শূন্য free_texture(শূন্য *opaque, uint8_t *data)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(data);
}

স্থির AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, পূর্ণাঙ্ক index)
{
    AVBufferRef *buf;
    AVD3D11FrameDescriptor         *desc = av_mallocz(পরিমাণ(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;
    যদি (!desc) {
        ID3D11Texture2D_Release(tex);
        প্রত্যাগম রিক্ত;
    }

    যদি (s->nb_surfaces <= s->nb_surfaces_used) {
        frames_hwctx->texture_infos = av_realloc_f(frames_hwctx->texture_infos,
                                                   s->nb_surfaces_used + 1,
                                                   পরিমাণ(*frames_hwctx->texture_infos));
        যদি (!frames_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            প্রত্যাগম রিক্ত;
        }
        s->nb_surfaces = s->nb_surfaces_used + 1;
    }

    frames_hwctx->texture_infos[s->nb_surfaces_used].texture = tex;
    frames_hwctx->texture_infos[s->nb_surfaces_used].index = index;
    s->nb_surfaces_used++;

    desc->texture = tex;
    desc->index   = index;

    buf = av_buffer_create((uint8_t *)desc, পরিমাণ(*desc), free_texture, tex, 0);
    যদি (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        প্রত্যাগম রিক্ত;
    }

    প্রত্যাগম buf;
}

স্থির AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
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
        .SampleDesc = { .গুনতি_2 = 1 },
        .ArraySize  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, রিক্ত, &tex);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
        প্রত্যাগম রিক্ত;
    }

    প্রত্যাগম wrap_texture_buf(ctx, tex, 0);
}

স্থির AVBufferRef *d3d11va_pool_alloc(শূন্য *opaque, size_t size)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    যদি (!hwctx->texture)
        প্রত্যাগম d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    যদি (s->nb_surfaces_used >= texDesc.ArraySize) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        প্রত্যাগম রিক্ত;
    }

    ID3D11Texture2D_AddRef(hwctx->texture);
    প্রত্যাগম wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_used);
}

স্থির পূর্ণাঙ্ক d3d11va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    পূর্ণাঙ্ক i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

    প্রতি (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        যদি (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            ভঙ্গ;
        }
    }
    যদি (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        প্রত্যাগম AVERROR(EINVAL);
    }

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    যদি (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_size = FFMIN(ctx->initial_pool_size, MAX_ARRAY_SIZE);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .Width      = ctx->width,
        .Height     = ctx->height,
        .MipLevels  = 1,
        .Format     = s->format,
        .SampleDesc = { .গুনতি_2 = 1 },
        .ArraySize  = ctx->initial_pool_size,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    যদি (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        যদি (texDesc.Width != texDesc2.Width ||
            texDesc.Height != texDesc2.Height ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            প্রত্যাগম AVERROR(EINVAL);
        }

        ctx->initial_pool_size = texDesc2.ArraySize;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } অন্যথা যদি (texDesc.ArraySize > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, রিক্ত, &hwctx->texture);
        যদি (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
            প্রত্যাগম AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(রিক্ত, ctx->initial_pool_size, পরিমাণ(*hwctx->texture_infos));
    যদি (!hwctx->texture_infos)
        প্রত্যাগম AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_size;

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(পরিমাণ(AVD3D11FrameDescriptor),
                             ctx, d3d11va_pool_alloc, রিক্ত);
    যদি (!ffhwframesctx(ctx)->pool_internal)
        প্রত্যাগম AVERROR(ENOMEM);

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক d3d11va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    AVD3D11FrameDescriptor *desc;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    যদি (!frame->buf[0])
        প্রত্যাগম AVERROR(ENOMEM);

    desc = (AVD3D11FrameDescriptor *)frame->buf[0]->data;

    frame->data[0] = (uint8_t *)desc->texture;
    frame->data[1] = (uint8_t *)desc->index;
    frame->format  = AV_PIX_FMT_D3D11;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        গণনা AVHWFrameTransferDirection dir,
                                        গণনা AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    গণনা AVPixelFormat *fmts;

    fmts = av_malloc_array(2, পরিমাণ(*fmts));
    যদি (!fmts)
        প্রত্যাগম AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    যদি (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .Width          = ctx->width,
        .Height         = ctx->height,
        .MipLevels      = 1,
        .Format         = format,
        .SampleDesc     = { .গুনতি_2 = 1 },
        .ArraySize      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, রিক্ত, &s->staging_texture);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (long)hr);
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    প্রত্যাগম 0;
}

স্থির শূন্য fill_texture_ptrs(uint8_t *data[4], পূর্ণাঙ্ক linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; i < 4; i++)
        linesize[i] = map->RowPitch;

    av_image_fill_pointers(data, ctx->sw_format, desc->Height,
                           (uint8_t*)map->pData, linesize);
}

স্থির পূর্ণাঙ্ক d3d11va_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 ধ্রুব AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    পূর্ণাঙ্ক download = src->format == AV_PIX_FMT_D3D11;
    ধ্রুব AVFrame *frame = download ? src : dst;
    ধ্রুব AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)frame->data[0];
    পূর্ণাঙ্ক index = (intptr_t)frame->data[1];
    ID3D11Resource *staging;
    পূর্ণাঙ্ক w = FFMIN(dst->width,  src->width);
    পূর্ণাঙ্ক h = FFMIN(dst->height, src->height);
    uint8_t *map_data[4];
    পূর্ণাঙ্ক map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    পূর্ণাঙ্ক res;

    যদি (frame->hw_frames_ctx->data != (uint8_t *)ctx || other->format != ctx->sw_format)
        প্রত্যাগম AVERROR(EINVAL);

    device_hwctx->lock(device_hwctx->lock_ctx);

    যদি (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        যদি (res < 0)
            প্রত্যাগম res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    যদি (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, index, রিক্ত);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        যদি (FAILED(hr))
            গচ্ছ map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->data, dst->linesize, map_data, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } অন্যথা {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        যদি (FAILED(hr))
            গচ্ছ map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_data, map_linesize, src->data, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, index, 0, 0, 0,
                                                  staging, 0, রিক্ত);
    }

    device_hwctx->unlock(device_hwctx->lock_ctx);
    প্রত্যাগম 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (long)hr);
    device_hwctx->unlock(device_hwctx->lock_ctx);
    প্রত্যাগম AVERROR_UNKNOWN;
}

স্থির পূর্ণাঙ্ক d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    যদি (!device_hwctx->lock) {
        device_hwctx->lock_ctx = CreateMutex(রিক্ত, 0, রিক্ত);
        যদি (device_hwctx->lock_ctx == INVALID_HANDLE_মান) {
            av_log(রিক্ত, AV_LOG_ERROR, "Failed to create a mutex\n");
            প্রত্যাগম AVERROR(EINVAL);
        }
        device_hwctx->lock   = d3d11va_default_lock;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    যদি (!device_hwctx->device_context) {
        ID3D11Device_GetImmediateContext(device_hwctx->device, &device_hwctx->device_context);
        যদি (!device_hwctx->device_context)
            প্রত্যাগম AVERROR_UNKNOWN;
    }

    যদি (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (শূন্য **)&device_hwctx->video_device);
        যদি (FAILED(hr))
            প্রত্যাগম AVERROR_UNKNOWN;
    }

    যদি (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (শূন্য **)&device_hwctx->video_context);
        যদি (FAILED(hr))
            প্রত্যাগম AVERROR_UNKNOWN;
    }

    প্রত্যাগম 0;
}

স্থির শূন্য d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    যদি (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = রিক্ত;
    }

    যদি (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = রিক্ত;
    }

    যদি (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = রিক্ত;
    }

    যদি (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = রিক্ত;
    }

    যদি (device_hwctx->lock == d3d11va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_মান;
        device_hwctx->lock = রিক্ত;
    }
}

স্থির পূর্ণাঙ্ক d3d11va_device_find_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, ধ্রুব বর্ণ *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = রিক্ত;
    IDXGIFactory2 *factory;
    পূর্ণাঙ্ক adapter_id = 0;
    long পূর্ণাঙ্ক id = strtol(vendor_id, রিক্ত, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (শূন্য **)&factory);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        প্রত্যাগম -1;
    }

    যাবত্ (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_FOUND) {
        ID3D11Device* device = রিক্ত;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, রিক্ত, flags, রিক্ত, 0, D3D11_SDK_VERSION, &device, রিক্ত, রিক্ত);
        যদি (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            অনুবর্ত;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        যদি (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            অনুবর্ত;
        } অন্যথা যদি (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            প্রত্যাগম adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    প্রত্যাগম -1;
}

স্থির পূর্ণাঙ্ক d3d11va_device_create(AVHWDeviceContext *ctx, ধ্রুব বর্ণ *device,
                                 AVDictionary *opts, পূর্ণাঙ্ক flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = রিক্ত;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    পূর্ণাঙ্ক is_debug       = !!av_dict_get(opts, "debug", রিক্ত, 0);
    পূর্ণাঙ্ক ret;
    পূর্ণাঙ্ক adapter = -1;

    যদি (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    যদি ((ret = ff_thread_once(&functions_loaded, load_functions)) != 0)
        প্রত্যাগম AVERROR_UNKNOWN;
    যদি (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    যদি (device) {
        adapter = atoi(device);
    } অন্যথা {
        AVDictionaryEntry *e = av_dict_get(opts, "vendor_id", রিক্ত, 0);
        যদি (e && e->মান) {
            adapter = d3d11va_device_find_adapter_by_vendor_id(ctx, creationFlags, e->মান);
            যদি (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->মান);
                প্রত্যাগম AVERROR_UNKNOWN;
            }
        }
    }

    যদি (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (শূন্য **)&pDXGIFactory);
        যদি (SUCCEEDED(hr)) {
            যদি (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = রিক্ত;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    যদি (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        যদি (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, রিক্ত, creationFlags, রিক্ত, 0,
                   D3D11_SDK_VERSION, &device_hwctx->device, রিক্ত, রিক্ত);
    যদি (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (long)hr);
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (শূন্য **)&pMultithread);
    যদি (SUCCEEDED(hr)) {
        ID3D10Multithread_SetMultithreadProtected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#যদি !HAVE_UWP && HAVE_DXGIDEBUG_H
    যদি (is_debug) {
        HANDLE dxgidebug_dll = LoadLibrary("dxgidebug.dll");
        যদি (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(ধ্রুব GUID *riid, শূন্য **ppDebug)
                = (শূন্য *)GetProcAddress(dxgidebug_dll, "DXGIGetDebugInterface");
            যদি (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = রিক্ত;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (শূন্য**)&dxgi_debug);
                যদি (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_ReportLiveObjects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } অন্যথা {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } অন্যথা {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } অন্যথা {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#endif

    যদি (av_dict_get(opts, "SHADER", রিক্ত, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    যদি (av_dict_get(opts, "UAV", রিক্ত, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    যদি (av_dict_get(opts, "RTV", রিক্ত, 0))
        device_hwctx->BindFlags |= D3D11_BIND_RENDER_TARGET;

    যদি (av_dict_get(opts, "SHARED", রিক্ত, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    প্রত্যাগম 0;
}

ধ্রুব HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_size    = পরিমাণ(AVD3D11VADeviceContext),
    .frames_hwctx_size    = পরিমাণ(D3D11VAFramesContext),

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

    .pix_fmts             = (ধ্রুব গণনা AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
