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

#समावेश "config.h"

#समावेश <windows.h>

#घोषणा COBJMACROS

#समावेश <initguid.h>
#समावेश <d3d11.h>
#समावेश <dxgi1_2.h>

#अगर HAVE_DXGIDEBUG_H
#समावेश <dxgidebug.h>
#पूर्ण_अगर

#समावेश "avassert.h"
#समावेश "common.h"
#समावेश "hwcontext.h"
#समावेश "hwcontext_d3d11va.h"
#समावेश "hwcontext_internal.h"
#समावेश "imgutils.h"
#समावेश "mem.h"
#समावेश "pixdesc.h"
#समावेश "pixfmt.h"
#समावेश "thread.h"
#समावेश "compat/w32dlfcn.h"

#घोषणा MAX_ARRAY_आकार 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

प्रकार HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, व्योम **ppFactory);

अटल AVOnce functions_loaded = AV_ONCE_INIT;

अटल PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
अटल PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

अटल av_cold व्योम load_functions(व्योम)
{
#अगर !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    अगर (!d3dlib || !dxgilib)
        वापस;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) GetProcAddress(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory1");
    अगर (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) GetProcAddress(dxgilib, "CreateDXGIFactory");
#अन्यथा
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#पूर्ण_अगर
}

प्रकार काष्ठा D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    पूर्णांक nb_surfaces;
    पूर्णांक nb_surfaces_used;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

अटल स्थिर काष्ठा {
    DXGI_FORMAT d3d_format;
    क्रमागत AVPixelFormat pix_fmt;
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

अटल व्योम d3d11va_default_lock(व्योम *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

अटल व्योम d3d11va_default_unlock(व्योम *ctx)
{
    ReleaseMutex(ctx);
}

अटल व्योम d3d11va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;

    अगर (frames_hwctx->texture)
        ID3D11Texture2D_Release(frames_hwctx->texture);
    frames_hwctx->texture = शून्य;

    अगर (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = शून्य;

    av_freep(&frames_hwctx->texture_infos);
}

अटल पूर्णांक d3d11va_frames_get_constraints(AVHWDeviceContext *ctx,
                                          स्थिर व्योम *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    पूर्णांक nb_sw_formats = 0;
    HRESULT hr;
    पूर्णांक i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    माप(*constraints->valid_sw_formats));
    अगर (!constraints->valid_sw_formats)
        वापस AVERROR(ENOMEM);

    क्रम (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        अगर (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, माप(*constraints->valid_hw_formats));
    अगर (!constraints->valid_hw_formats)
        वापस AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    वापस 0;
}

अटल व्योम free_texture(व्योम *opaque, uint8_t *तथ्य)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(तथ्य);
}

अटल AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, पूर्णांक सूचकांक)
{
    AVBufferRef *buf;
    AVD3D11FrameDescriptor         *desc = av_mallocz(माप(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *frames_hwctx = &s->p;
    अगर (!desc) {
        ID3D11Texture2D_Release(tex);
        वापस शून्य;
    }

    अगर (s->nb_surfaces <= s->nb_surfaces_used) {
        frames_hwctx->texture_infos = av_realloc_f(frames_hwctx->texture_infos,
                                                   s->nb_surfaces_used + 1,
                                                   माप(*frames_hwctx->texture_infos));
        अगर (!frames_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            वापस शून्य;
        }
        s->nb_surfaces = s->nb_surfaces_used + 1;
    }

    frames_hwctx->texture_infos[s->nb_surfaces_used].texture = tex;
    frames_hwctx->texture_infos[s->nb_surfaces_used].सूचकांक = सूचकांक;
    s->nb_surfaces_used++;

    desc->texture = tex;
    desc->सूचकांक   = सूचकांक;

    buf = av_बफर_create((uint8_t *)desc, माप(*desc), free_texture, tex, 0);
    अगर (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        वापस शून्य;
    }

    वापस buf;
}

अटल AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
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
        .SampleDesc = { .गिनती_2 = 1 },
        .Array_आकार  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, शून्य, &tex);
    अगर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (दीर्घ)hr);
        वापस शून्य;
    }

    वापस wrap_texture_buf(ctx, tex, 0);
}

अटल AVBufferRef *d3d11va_pool_alloc(व्योम *opaque, माप_प्रकार आकार)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    अगर (!hwctx->texture)
        वापस d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    अगर (s->nb_surfaces_used >= texDesc.Array_आकार) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        वापस शून्य;
    }

    ID3D11Texture2D_AddRef(hwctx->texture);
    वापस wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_used);
}

अटल पूर्णांक d3d11va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    पूर्णांक i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

    क्रम (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        अगर (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            अवरोध;
        }
    }
    अगर (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        वापस AVERROR(EINVAL);
    }

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    अगर (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_आकार = FFMIN(ctx->initial_pool_आकार, MAX_ARRAY_आकार);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .Width      = ctx->width,
        .Height     = ctx->height,
        .MipLevels  = 1,
        .Format     = s->format,
        .SampleDesc = { .गिनती_2 = 1 },
        .Array_आकार  = ctx->initial_pool_आकार,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    अगर (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        अगर (texDesc.Width != texDesc2.Width ||
            texDesc.Height != texDesc2.Height ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            वापस AVERROR(EINVAL);
        }

        ctx->initial_pool_आकार = texDesc2.Array_आकार;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } अन्यथा अगर (texDesc.Array_आकार > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, शून्य, &hwctx->texture);
        अगर (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (दीर्घ)hr);
            वापस AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(शून्य, ctx->initial_pool_आकार, माप(*hwctx->texture_infos));
    अगर (!hwctx->texture_infos)
        वापस AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_आकार;

    ffhwframesctx(ctx)->pool_internal =
        av_बफर_pool_init2(माप(AVD3D11FrameDescriptor),
                             ctx, d3d11va_pool_alloc, शून्य);
    अगर (!ffhwframesctx(ctx)->pool_internal)
        वापस AVERROR(ENOMEM);

    वापस 0;
}

अटल पूर्णांक d3d11va_get_बफर(AVHWFramesContext *ctx, AVFrame *frame)
{
    AVD3D11FrameDescriptor *desc;

    frame->buf[0] = av_बफर_pool_get(ctx->pool);
    अगर (!frame->buf[0])
        वापस AVERROR(ENOMEM);

    desc = (AVD3D11FrameDescriptor *)frame->buf[0]->तथ्य;

    frame->तथ्य[0] = (uint8_t *)desc->texture;
    frame->तथ्य[1] = (uint8_t *)desc->सूचकांक;
    frame->format  = AV_PIX_FMT_D3D11;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    वापस 0;
}

अटल पूर्णांक d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        क्रमागत AVHWFrameTransferDirection dir,
                                        क्रमागत AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    क्रमागत AVPixelFormat *fmts;

    fmts = av_malloc_array(2, माप(*fmts));
    अगर (!fmts)
        वापस AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    अगर (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    वापस 0;
}

अटल पूर्णांक d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .Width          = ctx->width,
        .Height         = ctx->height,
        .MipLevels      = 1,
        .Format         = format,
        .SampleDesc     = { .गिनती_2 = 1 },
        .Array_आकार      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, शून्य, &s->staging_texture);
    अगर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (दीर्घ)hr);
        वापस AVERROR_UNKNOWN;
    }

    वापस 0;
}

अटल व्योम fill_texture_ptrs(uint8_t *तथ्य[4], पूर्णांक linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    पूर्णांक i;

    क्रम (i = 0; i < 4; i++)
        linesize[i] = map->RowPitch;

    av_image_fill_pointers(तथ्य, ctx->sw_format, desc->Height,
                           (uint8_t*)map->p_तथ्य, linesize);
}

अटल पूर्णांक d3d11va_transfer_तथ्य(AVHWFramesContext *ctx, AVFrame *dst,
                                 स्थिर AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    पूर्णांक download = src->format == AV_PIX_FMT_D3D11;
    स्थिर AVFrame *frame = download ? src : dst;
    स्थिर AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)frame->तथ्य[0];
    पूर्णांक सूचकांक = (intptr_t)frame->तथ्य[1];
    ID3D11Resource *staging;
    पूर्णांक w = FFMIN(dst->width,  src->width);
    पूर्णांक h = FFMIN(dst->height, src->height);
    uint8_t *map_तथ्य[4];
    पूर्णांक map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    पूर्णांक res;

    अगर (frame->hw_frames_ctx->तथ्य != (uint8_t *)ctx || other->format != ctx->sw_format)
        वापस AVERROR(EINVAL);

    device_hwctx->lock(device_hwctx->lock_ctx);

    अगर (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        अगर (res < 0)
            वापस res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    अगर (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, सूचकांक, शून्य);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        अगर (FAILED(hr))
            जाओ map_failed;

        fill_texture_ptrs(map_तथ्य, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->तथ्य, dst->linesize, map_तथ्य, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } अन्यथा {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        अगर (FAILED(hr))
            जाओ map_failed;

        fill_texture_ptrs(map_तथ्य, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_तथ्य, map_linesize, src->तथ्य, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, सूचकांक, 0, 0, 0,
                                                  staging, 0, शून्य);
    }

    device_hwctx->unlock(device_hwctx->lock_ctx);
    वापस 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (दीर्घ)hr);
    device_hwctx->unlock(device_hwctx->lock_ctx);
    वापस AVERROR_UNKNOWN;
}

अटल पूर्णांक d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    अगर (!device_hwctx->lock) {
        device_hwctx->lock_ctx = CreateMutex(शून्य, 0, शून्य);
        अगर (device_hwctx->lock_ctx == INVALID_HANDLE_मूल्य) {
            av_log(शून्य, AV_LOG_ERROR, "Failed to create a mutex\n");
            वापस AVERROR(EINVAL);
        }
        device_hwctx->lock   = d3d11va_default_lock;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    अगर (!device_hwctx->device_context) {
        ID3D11Device_GetImmediateContext(device_hwctx->device, &device_hwctx->device_context);
        अगर (!device_hwctx->device_context)
            वापस AVERROR_UNKNOWN;
    }

    अगर (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (व्योम **)&device_hwctx->video_device);
        अगर (FAILED(hr))
            वापस AVERROR_UNKNOWN;
    }

    अगर (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (व्योम **)&device_hwctx->video_context);
        अगर (FAILED(hr))
            वापस AVERROR_UNKNOWN;
    }

    वापस 0;
}

अटल व्योम d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    अगर (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = शून्य;
    }

    अगर (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = शून्य;
    }

    अगर (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = शून्य;
    }

    अगर (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = शून्य;
    }

    अगर (device_hwctx->lock == d3d11va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_मूल्य;
        device_hwctx->lock = शून्य;
    }
}

अटल पूर्णांक d3d11va_device_find_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, स्थिर अक्षर *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = शून्य;
    IDXGIFactory2 *factory;
    पूर्णांक adapter_id = 0;
    दीर्घ पूर्णांक id = म_से_दीर्घ(vendor_id, शून्य, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (व्योम **)&factory);
    अगर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        वापस -1;
    }

    जबतक (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_FOUND) {
        ID3D11Device* device = शून्य;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, शून्य, flags, शून्य, 0, D3D11_SDK_VERSION, &device, शून्य, शून्य);
        अगर (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            जारी;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        अगर (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            जारी;
        } अन्यथा अगर (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            वापस adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    वापस -1;
}

अटल पूर्णांक d3d11va_device_create(AVHWDeviceContext *ctx, स्थिर अक्षर *device,
                                 AVDictionary *opts, पूर्णांक flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = शून्य;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    पूर्णांक is_debug       = !!av_dict_get(opts, "debug", शून्य, 0);
    पूर्णांक ret;
    पूर्णांक adapter = -1;

    अगर (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    अगर ((ret = ff_thread_once(&functions_loaded, load_functions)) != 0)
        वापस AVERROR_UNKNOWN;
    अगर (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        वापस AVERROR_UNKNOWN;
    }

    अगर (device) {
        adapter = म_से_प(device);
    } अन्यथा {
        AVDictionaryEntry *e = av_dict_get(opts, "vendor_id", शून्य, 0);
        अगर (e && e->मूल्य) {
            adapter = d3d11va_device_find_adapter_by_vendor_id(ctx, creationFlags, e->मूल्य);
            अगर (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->मूल्य);
                वापस AVERROR_UNKNOWN;
            }
        }
    }

    अगर (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (व्योम **)&pDXGIFactory);
        अगर (SUCCEEDED(hr)) {
            अगर (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = शून्य;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    अगर (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        अगर (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, शून्य, creationFlags, शून्य, 0,
                   D3D11_SDK_VERSION, &device_hwctx->device, शून्य, शून्य);
    अगर (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    अगर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (दीर्घ)hr);
        वापस AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (व्योम **)&pMultithread);
    अगर (SUCCEEDED(hr)) {
        ID3D10Multithread_SetMultithreadProtected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#अगर !HAVE_UWP && HAVE_DXGIDEBUG_H
    अगर (is_debug) {
        HANDLE dxgidebug_dll = LoadLibrary("dxgidebug.dll");
        अगर (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(स्थिर GUID *riid, व्योम **ppDebug)
                = (व्योम *)GetProcAddress(dxgidebug_dll, "DXGIGetDebugInterface");
            अगर (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = शून्य;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (व्योम**)&dxgi_debug);
                अगर (SUCCEEDED(hr) && dxgi_debug) {
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
#पूर्ण_अगर

    अगर (av_dict_get(opts, "SHADER", शून्य, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    अगर (av_dict_get(opts, "UAV", शून्य, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    अगर (av_dict_get(opts, "RTV", शून्य, 0))
        device_hwctx->BindFlags |= D3D11_BIND_RENDER_TARGET;

    अगर (av_dict_get(opts, "SHARED", शून्य, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    वापस 0;
}

स्थिर HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_आकार    = माप(AVD3D11VADeviceContext),
    .frames_hwctx_आकार    = माप(D3D11VAFramesContext),

    .device_create        = d3d11va_device_create,
    .device_init          = d3d11va_device_init,
    .device_uninit        = d3d11va_device_uninit,
    .frames_get_constraints = d3d11va_frames_get_constraints,
    .frames_init          = d3d11va_frames_init,
    .frames_uninit        = d3d11va_frames_uninit,
    .frames_get_बफर    = d3d11va_get_बफर,
    .transfer_get_formats = d3d11va_transfer_get_formats,
    .transfer_तथ्य_to     = d3d11va_transfer_तथ्य,
    .transfer_तथ्य_from   = d3d11va_transfer_तथ्य,

    .pix_fmts             = (स्थिर क्रमागत AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
