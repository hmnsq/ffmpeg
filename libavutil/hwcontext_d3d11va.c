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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଅନ୍ତର୍ଭାଵ <windows.h>

#define COBJMACROS

#ଅନ୍ତର୍ଭାଵ <initguid.h>
#ଅନ୍ତର୍ଭାଵ <d3d11.h>
#ଅନ୍ତର୍ଭାଵ <dxgi1_2.h>

#ଯଦି HAVE_DXGIDEBUG_H
#ଅନ୍ତର୍ଭାଵ <dxgidebug.h>
#endif

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_d3d11va.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_internal.h"
#ଅନ୍ତର୍ଭାଵ "imgutils.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "pixdesc.h"
#ଅନ୍ତର୍ଭାଵ "pixfmt.h"
#ଅନ୍ତର୍ଭାଵ "thread.h"
#ଅନ୍ତର୍ଭାଵ "compat/w32dlfcn.h"

#define MAX_ARRAY_SIZE 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

ପ୍ରକାରବ୍ୟାଖ୍ୟା HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, ଶୂନ୍ୟ **ppFactory);

ସ୍ଥିର AVOnce functions_loaded = AV_ONCE_INIT;

ସ୍ଥିର PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
ସ୍ଥିର PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

ସ୍ଥିର av_cold ଶୂନ୍ୟ load_functions(ଶୂନ୍ୟ)
{
#ଯଦି !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    ଯଦି (!d3dlib || !dxgilib)
        ଫେରନ୍ତୁ;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) GetProcAddress(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory1");
    ଯଦି (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory");
#ଅନ୍ୟଥା
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#endif
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_surfaces;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_surfaces_used;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

ସ୍ଥିର ଅଚଳ ସଂରଚନା {
    DXGI_FORMAT d3d_format;
    ଗଣନା AVPixelFormat pix_fmt;
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

ସ୍ଥିର ଶୂନ୍ୟ d3d11va_default_lock(ଶୂନ୍ୟ *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

ସ୍ଥିର ଶୂନ୍ୟ d3d11va_default_unlock(ଶୂନ୍ୟ *ctx)
{
    ReleaseMutex(ctx);
}

ସ୍ଥିର ଶୂନ୍ୟ d3d11va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;

    ଯଦି (frames_hwctx->texture)
        ID3D11Texture2D_Release(frames_hwctx->texture);
    frames_hwctx->texture = ଖାଲି;

    ଯଦି (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = ଖାଲି;

    av_freep(&frames_hwctx->texture_infos);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା d3d11va_frames_get_constraints(AVHWDeviceContext *ctx,
                                          ଅଚଳ ଶୂନ୍ୟ *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_sw_formats = 0;
    HRESULT hr;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    ଆକାର(*constraints->valid_sw_formats));
    ଯଦି (!constraints->valid_sw_formats)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        ଯଦି (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ଆକାର(*constraints->valid_hw_formats));
    ଯଦି (!constraints->valid_hw_formats)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ free_texture(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(data);
}

ସ୍ଥିର AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, ପୂର୍ଣ୍ଣସଂଖ୍ୟା index)
{
    AVBufferRef *buf;
    AVD3D11FrameDescriptor         *desc = av_mallocz(ଆକାର(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;
    ଯଦି (!desc) {
        ID3D11Texture2D_Release(tex);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (s->nb_surfaces <= s->nb_surfaces_used) {
        frames_hwctx->texture_infos = av_realloc_f(frames_hwctx->texture_infos,
                                                   s->nb_surfaces_used + 1,
                                                   ଆକାର(*frames_hwctx->texture_infos));
        ଯଦି (!frames_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            ଫେରନ୍ତୁ ଖାଲି;
        }
        s->nb_surfaces = s->nb_surfaces_used + 1;
    }

    frames_hwctx->texture_infos[s->nb_surfaces_used].texture = tex;
    frames_hwctx->texture_infos[s->nb_surfaces_used].index = index;
    s->nb_surfaces_used++;

    desc->texture = tex;
    desc->index   = index;

    buf = av_buffer_create((uint8_t *)desc, ଆକାର(*desc), free_texture, tex, 0);
    ଯଦି (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ buf;
}

ସ୍ଥିର AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
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
        .SampleDesc = { .ଗଣନା_3 = 1 },
        .ArraySize  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ଖାଲି, &tex);
    ଯଦି (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ wrap_texture_buf(ctx, tex, 0);
}

ସ୍ଥିର AVBufferRef *d3d11va_pool_alloc(ଶୂନ୍ୟ *opaque, size_t size)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    ଯଦି (!hwctx->texture)
        ଫେରନ୍ତୁ d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    ଯଦି (s->nb_surfaces_used >= texDesc.ArraySize) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ID3D11Texture2D_AddRef(hwctx->texture);
    ଫେରନ୍ତୁ wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_used);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା d3d11va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ଯଦି (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            ଭାଙ୍ଗ;
        }
    }
    ଯଦି (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    ଯଦି (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_size = FFMIN(ctx->initial_pool_size, MAX_ARRAY_SIZE);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .Width      = ctx->width,
        .Height     = ctx->height,
        .MipLevels  = 1,
        .Format     = s->format,
        .SampleDesc = { .ଗଣନା_3 = 1 },
        .ArraySize  = ctx->initial_pool_size,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    ଯଦି (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        ଯଦି (texDesc.Width != texDesc2.Width ||
            texDesc.Height != texDesc2.Height ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }

        ctx->initial_pool_size = texDesc2.ArraySize;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } ଅନ୍ୟଥା ଯଦି (texDesc.ArraySize > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ଖାଲି, &hwctx->texture);
        ଯଦି (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (long)hr);
            ଫେରନ୍ତୁ AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(ଖାଲି, ctx->initial_pool_size, ଆକାର(*hwctx->texture_infos));
    ଯଦି (!hwctx->texture_infos)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_size;

    ffhwframesctx(ctx)->pool_internal =
        av_buffer_pool_init2(ଆକାର(AVD3D11FrameDescriptor),
                             ctx, d3d11va_pool_alloc, ଖାଲି);
    ଯଦି (!ffhwframesctx(ctx)->pool_internal)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା d3d11va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    AVD3D11FrameDescriptor *desc;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ଯଦି (!frame->buf[0])
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    desc = (AVD3D11FrameDescriptor *)frame->buf[0]->data;

    frame->data[0] = (uint8_t *)desc->texture;
    frame->data[1] = (uint8_t *)desc->index;
    frame->format  = AV_PIX_FMT_D3D11;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        ଗଣନା AVHWFrameTransferDirection dir,
                                        ଗଣନା AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    ଗଣନା AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ଆକାର(*fmts));
    ଯଦି (!fmts)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    ଯଦି (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .Width          = ctx->width,
        .Height         = ctx->height,
        .MipLevels      = 1,
        .Format         = format,
        .SampleDesc     = { .ଗଣନା_3 = 1 },
        .ArraySize      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, ଖାଲି, &s->staging_texture);
    ଯଦି (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (long)hr);
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ fill_texture_ptrs(uint8_t *data[4], ପୂର୍ଣ୍ଣସଂଖ୍ୟା linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < 4; i++)
        linesize[i] = map->RowPitch;

    av_image_fill_pointers(data, ctx->sw_format, desc->Height,
                           (uint8_t*)map->pData, linesize);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା d3d11va_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 ଅଚଳ AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା download = src->format == AV_PIX_FMT_D3D11;
    ଅଚଳ AVFrame *frame = download ? src : dst;
    ଅଚଳ AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)frame->data[0];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା index = (intptr_t)frame->data[1];
    ID3D11Resource *staging;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = FFMIN(dst->width,  src->width);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = FFMIN(dst->height, src->height);
    uint8_t *map_data[4];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା res;

    ଯଦି (frame->hw_frames_ctx->data != (uint8_t *)ctx || other->format != ctx->sw_format)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    device_hwctx->lock(device_hwctx->lock_ctx);

    ଯଦି (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        ଯଦି (res < 0)
            ଫେରନ୍ତୁ res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    ଯଦି (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, index, ଖାଲି);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        ଯଦି (FAILED(hr))
            ଯାଅ map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->data, dst->linesize, map_data, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } ଅନ୍ୟଥା {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        ଯଦି (FAILED(hr))
            ଯାଅ map_failed;

        fill_texture_ptrs(map_data, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_data, map_linesize, src->data, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, index, 0, 0, 0,
                                                  staging, 0, ଖାଲି);
    }

    device_hwctx->unlock(device_hwctx->lock_ctx);
    ଫେରନ୍ତୁ 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (long)hr);
    device_hwctx->unlock(device_hwctx->lock_ctx);
    ଫେରନ୍ତୁ AVERROR_UNKNOWN;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    ଯଦି (!device_hwctx->lock) {
        device_hwctx->lock_ctx = CreateMutex(ଖାଲି, 0, ଖାଲି);
        ଯଦି (device_hwctx->lock_ctx == INVALID_HANDLE_ମୂଲ୍ୟ) {
            av_log(ଖାଲି, AV_LOG_ERROR, "Failed to create a mutex\n");
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
        device_hwctx->lock   = d3d11va_default_lock;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    ଯଦି (!device_hwctx->device_context) {
        ID3D11Device_GetImmediateContext(device_hwctx->device, &device_hwctx->device_context);
        ଯଦି (!device_hwctx->device_context)
            ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଯଦି (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (ଶୂନ୍ୟ **)&device_hwctx->video_device);
        ଯଦି (FAILED(hr))
            ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଯଦି (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (ଶୂନ୍ୟ **)&device_hwctx->video_context);
        ଯଦି (FAILED(hr))
            ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    ଯଦି (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = ଖାଲି;
    }

    ଯଦି (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = ଖାଲି;
    }

    ଯଦି (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = ଖାଲି;
    }

    ଯଦି (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = ଖାଲି;
    }

    ଯଦି (device_hwctx->lock == d3d11va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_ମୂଲ୍ୟ;
        device_hwctx->lock = ଖାଲି;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା d3d11va_device_find_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, ଅଚଳ ଅକ୍ଷର *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = ଖାଲି;
    IDXGIFactory2 *factory;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା adapter_id = 0;
    long ପୂର୍ଣ୍ଣସଂଖ୍ୟା id = strtol(vendor_id, ଖାଲି, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (ଶୂନ୍ୟ **)&factory);
    ଯଦି (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        ଫେରନ୍ତୁ -1;
    }

    ଯେତେବେଳେ (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_FOUND) {
        ID3D11Device* device = ଖାଲି;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, ଖାଲି, flags, ଖାଲି, 0, D3D11_SDK_VERSION, &device, ଖାଲି, ଖାଲି);
        ଯଦି (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            ଜାରି;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        ଯଦି (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            ଜାରି;
        } ଅନ୍ୟଥା ଯଦି (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            ଫେରନ୍ତୁ adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    ଫେରନ୍ତୁ -1;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା d3d11va_device_create(AVHWDeviceContext *ctx, ଅଚଳ ଅକ୍ଷର *device,
                                 AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = ଖାଲି;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_debug       = !!av_dict_get(opts, "debug", ଖାଲି, 0);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା adapter = -1;

    ଯଦି (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    ଯଦି ((ret = ff_thread_once(&functions_loaded, load_functions)) != 0)
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    ଯଦି (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଯଦି (device) {
        adapter = atoi(device);
    } ଅନ୍ୟଥା {
        AVDictionaryEntry *e = av_dict_get(opts, "vendor_id", ଖାଲି, 0);
        ଯଦି (e && e->ମୂଲ୍ୟ) {
            adapter = d3d11va_device_find_adapter_by_vendor_id(ctx, creationFlags, e->ମୂଲ୍ୟ);
            ଯଦି (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->ମୂଲ୍ୟ);
                ଫେରନ୍ତୁ AVERROR_UNKNOWN;
            }
        }
    }

    ଯଦି (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (ଶୂନ୍ୟ **)&pDXGIFactory);
        ଯଦି (SUCCEEDED(hr)) {
            ଯଦି (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = ଖାଲି;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    ଯଦି (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        ଯଦି (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, ଖାଲି, creationFlags, ଖାଲି, 0,
                   D3D11_SDK_VERSION, &device_hwctx->device, ଖାଲି, ଖାଲି);
    ଯଦି (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    ଯଦି (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (long)hr);
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (ଶୂନ୍ୟ **)&pMultithread);
    ଯଦି (SUCCEEDED(hr)) {
        ID3D10Multithread_SetMultithreadProtected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#ଯଦି !HAVE_UWP && HAVE_DXGIDEBUG_H
    ଯଦି (is_debug) {
        HANDLE dxgidebug_dll = LoadLibrary("dxgidebug.dll");
        ଯଦି (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(ଅଚଳ GUID *riid, ଶୂନ୍ୟ **ppDebug)
                = (ଶୂନ୍ୟ *)GetProcAddress(dxgidebug_dll, "DXGIGetDebugInterface");
            ଯଦି (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = ଖାଲି;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (ଶୂନ୍ୟ**)&dxgi_debug);
                ଯଦି (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_ReportLiveObjects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
                    av_log(ctx, AV_LOG_INFO, "Enabled dxgi debugging.\n");
                } ଅନ୍ୟଥା {
                    av_log(ctx, AV_LOG_WARNING, "Failed enabling dxgi debugging.\n");
                }
            } ଅନ୍ୟଥା {
                av_log(ctx, AV_LOG_WARNING, "Failed getting dxgi debug interface.\n");
            }
        } ଅନ୍ୟଥା {
            av_log(ctx, AV_LOG_WARNING, "Failed loading dxgi debug library.\n");
        }
    }
#endif

    ଯଦି (av_dict_get(opts, "SHADER", ଖାଲି, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    ଯଦି (av_dict_get(opts, "UAV", ଖାଲି, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    ଯଦି (av_dict_get(opts, "RTV", ଖାଲି, 0))
        device_hwctx->BindFlags |= D3D11_BIND_RENDER_TARGET;

    ଯଦି (av_dict_get(opts, "SHARED", ଖାଲି, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    ଫେରନ୍ତୁ 0;
}

ଅଚଳ HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_size    = ଆକାର(AVD3D11VADeviceContext),
    .frames_hwctx_size    = ଆକାର(D3D11VAFramesContext),

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

    .pix_fmts             = (ଅଚଳ ଗଣନା AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
