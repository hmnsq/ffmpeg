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

#परिभाषय COBJMACROS

#अन्तर्भाव <initguid.h>
#अन्तर्भाव <d3d11.h>
#अन्तर्भाव <dxgi1_2.h>

#यदि HAVE_DXGIDEBUG_H
#अन्तर्भाव <dxgidebug.h>
#यदि_अन्तः

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

#परिभाषय MAX_ARRAY_आकार 64 // Driver specification limits ArraySize to 64 for decoder-bound resources

प्रकारनिर्देश HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID riid, शून्य **ppFactory);

स्थिर AVOnce functions_loaded = AV_ONCE_INIT;

स्थिर PFN_CREATE_DXGI_FACTORY mCreateDXGIFactory;
स्थिर PFN_D3D11_CREATE_DEVICE mD3D11CreateDevice;

स्थिर av_cold शून्य आरोपय_functions(शून्य)
{
#यदि !HAVE_UWP
    // We let these "leak" - this is fine, as unloading has no great benefit, and
    // Windows will mark a DLL as loaded forever if its internal refcount overflows
    // from too many LoadLibrary calls.
    HANDLE d3dlib, dxgilib;

    d3dlib  = dlopen("d3d11.dll", 0);
    dxgilib = dlopen("dxgi.dll", 0);
    यदि (!d3dlib || !dxgilib)
        प्रत्यागम;

    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) Get_Proc_स्थानाङ्कः(d3dlib, "D3D11CreateDevice");
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) Get_Proc_स्थानाङ्कः(dxgilib, "CreateDXGIFactory1");
    यदि (!mCreateDXGIFactory)
        mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) Get_Proc_स्थानाङ्कः(dxgilib, "CreateDXGIFactory");
#अन्यथा
    // In UWP (which lacks LoadLibrary), CreateDXGIFactory isn't available,
    // only CreateDXGIFactory1
    mD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE) D3D11CreateDevice;
    mCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY) CreateDXGIFactory1;
#यदि_अन्तः
}

प्रकारनिर्देश संरचना D3D11VAFramesContext {
    /**
     * The public AVD3D11VAFramesContext. See hwcontext_d3d11va.h for it.
     */
    AVD3D11VAFramesContext p;

    पूर्णाङ्क nb_surfaces;
    पूर्णाङ्क nb_surfaces_प्रयुक्तम्;

    DXGI_FORMAT format;

    ID3D11Texture2D *staging_texture;
} D3D11VAFramesContext;

स्थिर ध्रुव संरचना {
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

स्थिर शून्य d3d11va_default_तालकम्(शून्य *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

स्थिर शून्य d3d11va_default_unlock(शून्य *ctx)
{
    ReleaseMutex(ctx);
}

स्थिर शून्य d3d11va_चौकटाः_uninit(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    AVD3D11VAFramesContext *चौकटाः_hwctx = &s->p;

    यदि (चौकटाः_hwctx->texture)
        ID3D11Texture2D_Release(चौकटाः_hwctx->texture);
    चौकटाः_hwctx->texture = रिक्त;

    यदि (s->staging_texture)
        ID3D11Texture2D_Release(s->staging_texture);
    s->staging_texture = रिक्त;

    av_freep(&चौकटाः_hwctx->texture_infos);
}

स्थिर पूर्णाङ्क d3d11va_चौकटाः_get_constraints(AVHWDeviceContext *ctx,
                                          ध्रुव शून्य *hwconfig,
                                          AVHWFramesConstraints *constraints)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;
    पूर्णाङ्क nb_sw_formats = 0;
    HRESULT hr;
    पूर्णाङ्क i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    परिमाण(*constraints->valid_sw_formats));
    यदि (!constraints->valid_sw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        UINT format_support = 0;
        hr = ID3D11Device_CheckFormatSupport(device_hwctx->device, supported_formats[i].d3d_format, &format_support);
        यदि (SUCCEEDED(hr) && (format_support & D3D11_FORMAT_SUPPORT_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, परिमाण(*constraints->valid_hw_formats));
    यदि (!constraints->valid_hw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D11;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    प्रत्यागम 0;
}

स्थिर शून्य free_texture(शून्य *opaque, uint8_t *दत्त)
{
    ID3D11Texture2D_Release((ID3D11Texture2D *)opaque);
    av_free(दत्त);
}

स्थिर AVBufferRef *wrap_texture_buf(AVHWFramesContext *ctx, ID3D11Texture2D *tex, पूर्णाङ्क सूचकांक)
{
    AVBufferRef *buf;
    AVD3D11FrameDescriptor         *desc = av_mallocz(परिमाण(*desc));
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext *चौकटाः_hwctx = &s->p;
    यदि (!desc) {
        ID3D11Texture2D_Release(tex);
        प्रत्यागम रिक्त;
    }

    यदि (s->nb_surfaces <= s->nb_surfaces_प्रयुक्तम्) {
        चौकटाः_hwctx->texture_infos = av_realloc_f(चौकटाः_hwctx->texture_infos,
                                                   s->nb_surfaces_प्रयुक्तम् + 1,
                                                   परिमाण(*चौकटाः_hwctx->texture_infos));
        यदि (!चौकटाः_hwctx->texture_infos) {
            ID3D11Texture2D_Release(tex);
            av_free(desc);
            प्रत्यागम रिक्त;
        }
        s->nb_surfaces = s->nb_surfaces_प्रयुक्तम् + 1;
    }

    चौकटाः_hwctx->texture_infos[s->nb_surfaces_प्रयुक्तम्].texture = tex;
    चौकटाः_hwctx->texture_infos[s->nb_surfaces_प्रयुक्तम्].सूचकांक = सूचकांक;
    s->nb_surfaces_प्रयुक्तम्++;

    desc->texture = tex;
    desc->सूचकांक   = सूचकांक;

    buf = av_बफर_create((uint8_t *)desc, परिमाण(*desc), free_texture, tex, 0);
    यदि (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम buf;
}

स्थिर AVBufferRef *d3d11va_alloc_single(AVHWFramesContext *ctx)
{
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    HRESULT hr;
    ID3D11Texture2D *tex;
    D3D11_TEXTURE2D_DESC texDesc = {
        .विस्तारः_2      = ctx->विस्तारः,
        .Height     = ctx->height,
        .Mip_स्तराः  = 1,
        .Format     = s->format,
        .SampleDesc = { .गणनम्_2 = 1 },
        .Array_आकार  = 1,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, रिक्त, &tex);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (दीर्घ)hr);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम wrap_texture_buf(ctx, tex, 0);
}

स्थिर AVBufferRef *d3d11va_pool_alloc(शून्य *opaque, size_t आकार)
{
    AVHWFramesContext        *ctx = (AVHWFramesContext*)opaque;
    D3D11VAFramesContext       *s = ctx->hwctx;
    AVD3D11VAFramesContext *hwctx = &s->p;
    D3D11_TEXTURE2D_DESC  texDesc;

    यदि (!hwctx->texture)
        प्रत्यागम d3d11va_alloc_single(ctx);

    ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc);

    यदि (s->nb_surfaces_प्रयुक्तम् >= texDesc.Array_आकार) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        प्रत्यागम रिक्त;
    }

    ID3_D11_Texture2_D_सङ्कलय_Ref(hwctx->texture);
    प्रत्यागम wrap_texture_buf(ctx, hwctx->texture, s->nb_surfaces_प्रयुक्तम्);
}

स्थिर पूर्णाङ्क d3d11va_चौकटाः_init(AVHWFramesContext *ctx)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    AVD3D11VAFramesContext        *hwctx = &s->p;

    पूर्णाङ्क i;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc;

    प्रति (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        यदि (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            भङ्ग;
        }
    }
    यदि (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        प्रत्यागम AVERROR(EINVAL);
    }

    hwctx->BindFlags |= device_hwctx->BindFlags;
    hwctx->MiscFlags |= device_hwctx->MiscFlags;

    यदि (s->format == DXGI_FORMAT_420_OPAQUE)
        hwctx->BindFlags &= ~D3D11_BIND_SHADER_RESOURCE;

    ctx->initial_pool_आकार = FFMIN(ctx->initial_pool_आकार, MAX_ARRAY_आकार);

    texDesc = (D3D11_TEXTURE2D_DESC){
        .विस्तारः_2      = ctx->विस्तारः,
        .Height     = ctx->height,
        .Mip_स्तराः  = 1,
        .Format     = s->format,
        .SampleDesc = { .गणनम्_2 = 1 },
        .Array_आकार  = ctx->initial_pool_आकार,
        .Usage      = D3D11_USAGE_DEFAULT,
        .BindFlags  = hwctx->BindFlags,
        .MiscFlags  = hwctx->MiscFlags,
    };

    यदि (hwctx->texture) {
        D3D11_TEXTURE2D_DESC texDesc2;
        ID3D11Texture2D_GetDesc(hwctx->texture, &texDesc2);

        यदि (texDesc.विस्तारः_2 != texDesc2.विस्तारः_2 ||
            texDesc.Height != texDesc2.Height ||
            texDesc.Format != texDesc2.Format) {
            av_log(ctx, AV_LOG_ERROR, "User-provided texture has mismatching parameters\n");
            प्रत्यागम AVERROR(EINVAL);
        }

        ctx->initial_pool_आकार = texDesc2.Array_आकार;
        hwctx->BindFlags = texDesc2.BindFlags;
        hwctx->MiscFlags = texDesc2.MiscFlags;
    } अन्यथा यदि (texDesc.Array_आकार > 0) {
        hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, रिक्त, &hwctx->texture);
        यदि (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Could not create the texture (%lx)\n", (दीर्घ)hr);
            प्रत्यागम AVERROR_UNKNOWN;
        }
    }

    hwctx->texture_infos = av_realloc_f(रिक्त, ctx->initial_pool_आकार, परिमाण(*hwctx->texture_infos));
    यदि (!hwctx->texture_infos)
        प्रत्यागम AVERROR(ENOMEM);
    s->nb_surfaces = ctx->initial_pool_आकार;

    ffhwframesctx(ctx)->pool_आन्तरिकम् =
        av_बफर_pool_init2(परिमाण(AVD3D11FrameDescriptor),
                             ctx, d3d11va_pool_alloc, रिक्त);
    यदि (!ffhwframesctx(ctx)->pool_आन्तरिकम्)
        प्रत्यागम AVERROR(ENOMEM);

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क d3d11va_get_बफर(AVHWFramesContext *ctx, AVFrame *frame)
{
    AVD3D11FrameDescriptor *desc;

    frame->buf[0] = av_बफर_pool_get(ctx->pool);
    यदि (!frame->buf[0])
        प्रत्यागम AVERROR(ENOMEM);

    desc = (AVD3D11FrameDescriptor *)frame->buf[0]->दत्त;

    frame->दत्त[0] = (uint8_t *)desc->texture;
    frame->दत्त[1] = (uint8_t *)desc->सूचकांक;
    frame->format  = AV_PIX_FMT_D3D11;
    frame->विस्तारः   = ctx->विस्तारः;
    frame->height  = ctx->height;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        गणना AVHWFrameTransferDirection dir,
                                        गणना AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->hwctx;
    गणना AVPixelFormat *fmts;

    fmts = av_malloc_array(2, परिमाण(*fmts));
    यदि (!fmts)
        प्रत्यागम AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    यदि (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क d3d11va_create_staging_texture(AVHWFramesContext *ctx, DXGI_FORMAT format)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC texDesc = {
        .विस्तारः_2          = ctx->विस्तारः,
        .Height         = ctx->height,
        .Mip_स्तराः      = 1,
        .Format         = format,
        .SampleDesc     = { .गणनम्_2 = 1 },
        .Array_आकार      = 1,
        .Usage          = D3D11_USAGE_STAGING,
        .CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
    };

    hr = ID3D11Device_CreateTexture2D(device_hwctx->device, &texDesc, रिक्त, &s->staging_texture);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging texture (%lx)\n", (दीर्घ)hr);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रत्यागम 0;
}

स्थिर शून्य fill_texture_ptrs(uint8_t *दत्त[4], पूर्णाङ्क linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    पूर्णाङ्क i;

    प्रति (i = 0; i < 4; i++)
        linesize[i] = map->RowPitch;

    av_image_fill_सूचकाः(दत्त, ctx->sw_format, desc->Height,
                           (uint8_t*)map->p_दत्त, linesize);
}

स्थिर पूर्णाङ्क d3d11va_transfer_दत्त(AVHWFramesContext *ctx, AVFrame *dst,
                                 ध्रुव AVFrame *src)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D11VAFramesContext              *s = ctx->hwctx;
    पूर्णाङ्क download = src->format == AV_PIX_FMT_D3D11;
    ध्रुव AVFrame *frame = download ? src : dst;
    ध्रुव AVFrame *other = download ? dst : src;
    // (The interface types are compatible.)
    ID3D11Resource *texture = (ID3D11Resource *)(ID3D11Texture2D *)frame->दत्त[0];
    पूर्णाङ्क सूचकांक = (intptr_t)frame->दत्त[1];
    ID3D11Resource *staging;
    पूर्णाङ्क w = FFMIN(dst->विस्तारः,  src->विस्तारः);
    पूर्णाङ्क h = FFMIN(dst->height, src->height);
    uint8_t *map_दत्त[4];
    पूर्णाङ्क map_linesize[4];
    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE map;
    HRESULT hr;
    पूर्णाङ्क res;

    यदि (frame->hw_चौकटाः_ctx->दत्त != (uint8_t *)ctx || other->format != ctx->sw_format)
        प्रत्यागम AVERROR(EINVAL);

    device_hwctx->तालकम्(device_hwctx->तालकम्_ctx);

    यदि (!s->staging_texture) {
        ID3D11Texture2D_GetDesc((ID3D11Texture2D *)texture, &desc);
        res = d3d11va_create_staging_texture(ctx, desc.Format);
        यदि (res < 0)
            प्रत्यागम res;
    }

    staging = (ID3D11Resource *)s->staging_texture;

    ID3D11Texture2D_GetDesc(s->staging_texture, &desc);

    यदि (download) {
        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  staging, 0, 0, 0, 0,
                                                  texture, सूचकांक, रिक्त);

        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_READ, 0, &map);
        यदि (FAILED(hr))
            गच्छ map_failed;

        fill_texture_ptrs(map_दत्त, map_linesize, ctx, &desc, &map);

        av_image_copy2(dst->दत्त, dst->linesize, map_दत्त, map_linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);
    } अन्यथा {
        hr = ID3D11DeviceContext_Map(device_hwctx->device_context,
                                     staging, 0, D3D11_MAP_WRITE, 0, &map);
        यदि (FAILED(hr))
            गच्छ map_failed;

        fill_texture_ptrs(map_दत्त, map_linesize, ctx, &desc, &map);

        av_image_copy2(map_दत्त, map_linesize, src->दत्त, src->linesize,
                       ctx->sw_format, w, h);

        ID3D11DeviceContext_Unmap(device_hwctx->device_context, staging, 0);

        ID3D11DeviceContext_CopySubresourceRegion(device_hwctx->device_context,
                                                  texture, सूचकांक, 0, 0, 0,
                                                  staging, 0, रिक्त);
    }

    device_hwctx->unlock(device_hwctx->तालकम्_ctx);
    प्रत्यागम 0;

map_failed:
    av_log(ctx, AV_LOG_ERROR, "Unable to lock D3D11VA surface (%lx)\n", (दीर्घ)hr);
    device_hwctx->unlock(device_hwctx->तालकम्_ctx);
    प्रत्यागम AVERROR_UNKNOWN;
}

स्थिर पूर्णाङ्क d3d11va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;
    HRESULT hr;

    यदि (!device_hwctx->तालकम्) {
        device_hwctx->तालकम्_ctx = CreateMutex(रिक्त, 0, रिक्त);
        यदि (device_hwctx->तालकम्_ctx == INVALID_HANDLE_मानम्) {
            av_log(रिक्त, AV_LOG_ERROR, "Failed to create a mutex\n");
            प्रत्यागम AVERROR(EINVAL);
        }
        device_hwctx->तालकम्   = d3d11va_default_तालकम्;
        device_hwctx->unlock = d3d11va_default_unlock;
    }

    यदि (!device_hwctx->device_context) {
        ID3_D11_Device_Get_तात्कालिकम्_Context(device_hwctx->device, &device_hwctx->device_context);
        यदि (!device_hwctx->device_context)
            प्रत्यागम AVERROR_UNKNOWN;
    }

    यदि (!device_hwctx->video_device) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device, &IID_ID3D11VideoDevice,
                                                (शून्य **)&device_hwctx->video_device);
        यदि (FAILED(hr))
            प्रत्यागम AVERROR_UNKNOWN;
    }

    यदि (!device_hwctx->video_context) {
        hr = ID3D11DeviceContext_QueryInterface(device_hwctx->device_context, &IID_ID3D11VideoContext,
                                                (शून्य **)&device_hwctx->video_context);
        यदि (FAILED(hr))
            प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रत्यागम 0;
}

स्थिर शून्य d3d11va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D11VADeviceContext *device_hwctx = hwdev->hwctx;

    यदि (device_hwctx->device) {
        ID3D11Device_Release(device_hwctx->device);
        device_hwctx->device = रिक्त;
    }

    यदि (device_hwctx->device_context) {
        ID3D11DeviceContext_Release(device_hwctx->device_context);
        device_hwctx->device_context = रिक्त;
    }

    यदि (device_hwctx->video_device) {
        ID3D11VideoDevice_Release(device_hwctx->video_device);
        device_hwctx->video_device = रिक्त;
    }

    यदि (device_hwctx->video_context) {
        ID3D11VideoContext_Release(device_hwctx->video_context);
        device_hwctx->video_context = रिक्त;
    }

    यदि (device_hwctx->तालकम् == d3d11va_default_तालकम्) {
        CloseHandle(device_hwctx->तालकम्_ctx);
        device_hwctx->तालकम्_ctx = INVALID_HANDLE_मानम्;
        device_hwctx->तालकम् = रिक्त;
    }
}

स्थिर पूर्णाङ्क d3d11va_device_find_adapter_by_vendor_id(AVHWDeviceContext *ctx, uint32_t flags, ध्रुव वर्ण *vendor_id)
{
    HRESULT hr;
    IDXGIAdapter *adapter = रिक्त;
    IDXGIFactory2 *factory;
    पूर्णाङ्क adapter_id = 0;
    दीर्घ पूर्णाङ्क id = strtol(vendor_id, रिक्त, 0);

    hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (शून्य **)&factory);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "CreateDXGIFactory returned error\n");
        प्रत्यागम -1;
    }

    यावत् (IDXGIFactory2_EnumAdapters(factory, adapter_id++, &adapter) != DXGI_ERROR_NOT_प्राप्तम्) {
        ID3D11Device* device = रिक्त;
        DXGI_ADAPTER_DESC adapter_desc;

        hr = mD3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, रिक्त, flags, रिक्त, 0, D3_D11_SDK_संस्करणम्, &device, रिक्त, रिक्त);
        यदि (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "D3D11CreateDevice returned error, try next adapter\n");
            IDXGIAdapter_Release(adapter);
            अनुवर्त;
        }

        hr = IDXGIAdapter2_GetDesc(adapter, &adapter_desc);
        ID3D11Device_Release(device);
        IDXGIAdapter_Release(adapter);
        यदि (FAILED(hr)) {
            av_log(ctx, AV_LOG_DEBUG, "IDXGIAdapter2_GetDesc returned error, try next adapter\n");
            अनुवर्त;
        } अन्यथा यदि (adapter_desc.VendorId == id) {
            IDXGIFactory2_Release(factory);
            प्रत्यागम adapter_id - 1;
        }
    }

    IDXGIFactory2_Release(factory);
    प्रत्यागम -1;
}

स्थिर पूर्णाङ्क d3d11va_device_create(AVHWDeviceContext *ctx, ध्रुव वर्ण *device,
                                 AVDictionary *opts, पूर्णाङ्क flags)
{
    AVD3D11VADeviceContext *device_hwctx = ctx->hwctx;

    HRESULT hr;
    IDXGIAdapter           *pAdapter = रिक्त;
    ID3D10Multithread      *pMultithread;
    UINT creationFlags = D3D11_CREATE_DEVICE_VIDEO_SUPPORT;
    पूर्णाङ्क is_debug       = !!av_dict_get(opts, "debug", रिक्त, 0);
    पूर्णाङ्क ret;
    पूर्णाङ्क adapter = -1;

    यदि (is_debug) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        av_log(ctx, AV_LOG_INFO, "Enabling d3d11 debugging.\n");
    }

    यदि ((ret = ff_thread_once(&functions_loaded, आरोपय_functions)) != 0)
        प्रत्यागम AVERROR_UNKNOWN;
    यदि (!mD3D11CreateDevice || !mCreateDXGIFactory) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D11 library or its functions\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    यदि (device) {
        adapter = atoi(device);
    } अन्यथा {
        AVDictionary_प्रविष्टिः *e = av_dict_get(opts, "vendor_id", रिक्त, 0);
        यदि (e && e->मानम्) {
            adapter = d3d11va_device_find_adapter_by_vendor_id(ctx, creationFlags, e->मानम्);
            यदि (adapter < 0) {
                av_log(ctx, AV_LOG_ERROR, "Failed to find d3d11va adapter by "
                       "vendor id %s\n", e->मानम्);
                प्रत्यागम AVERROR_UNKNOWN;
            }
        }
    }

    यदि (adapter >= 0) {
        IDXGIFactory2 *pDXGIFactory;

        av_log(ctx, AV_LOG_VERBOSE, "Selecting d3d11va adapter %d\n", adapter);
        hr = mCreateDXGIFactory(&IID_IDXGIFactory2, (शून्य **)&pDXGIFactory);
        यदि (SUCCEEDED(hr)) {
            यदि (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = रिक्त;
            IDXGIFactory2_Release(pDXGIFactory);
        }
    }

    यदि (pAdapter) {
        DXGI_ADAPTER_DESC desc;
        hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
        यदि (!FAILED(hr)) {
            av_log(ctx, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                   desc.VendorId, desc.DeviceId, desc.Description);
        }
    }

    hr = mD3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, रिक्त, creationFlags, रिक्त, 0,
                   D3_D11_SDK_संस्करणम्, &device_hwctx->device, रिक्त, रिक्त);
    यदि (pAdapter)
        IDXGIAdapter_Release(pAdapter);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device (%lx)\n", (दीर्घ)hr);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    hr = ID3D11Device_QueryInterface(device_hwctx->device, &IID_ID3D10Multithread, (शून्य **)&pMultithread);
    यदि (SUCCEEDED(hr)) {
        ID3_D10_Multithread_समुच्चयः_Multithread_Protected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

#यदि !HAVE_UWP && HAVE_DXGIDEBUG_H
    यदि (is_debug) {
        HANDLE dxgidebug_dll = आरोपय_Library("dxgidebug.dll");
        यदि (dxgidebug_dll) {
            HRESULT (WINAPI  * pf_DXGIGetDebugInterface)(ध्रुव GUID *riid, शून्य **ppDebug)
                = (शून्य *)Get_Proc_स्थानाङ्कः(dxgidebug_dll, "DXGIGetDebugInterface");
            यदि (pf_DXGIGetDebugInterface) {
                IDXGIDebug *dxgi_debug = रिक्त;
                hr = pf_DXGIGetDebugInterface(&IID_IDXGIDebug, (शून्य**)&dxgi_debug);
                यदि (SUCCEEDED(hr) && dxgi_debug) {
                    IDXGIDebug_Report_जीवितम्_Objects(dxgi_debug, DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
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
#यदि_अन्तः

    यदि (av_dict_get(opts, "SHADER", रिक्त, 0))
        device_hwctx->BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    यदि (av_dict_get(opts, "UAV", रिक्त, 0))
        device_hwctx->BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

    यदि (av_dict_get(opts, "RTV", रिक्त, 0))
        device_hwctx->BindFlags |= D3D11_BIND_RENDER_TARGET;

    यदि (av_dict_get(opts, "SHARED", रिक्त, 0))
        device_hwctx->MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    प्रत्यागम 0;
}

ध्रुव HWContextType ff_hwcontext_type_d3d11va = {
    .type                 = AV_HWDEVICE_TYPE_D3D11VA,
    .name                 = "D3D11VA",

    .device_hwctx_आकार    = परिमाण(AVD3D11VADeviceContext),
    .चौकटाः_hwctx_आकार    = परिमाण(D3D11VAFramesContext),

    .device_create        = d3d11va_device_create,
    .device_init          = d3d11va_device_init,
    .device_uninit        = d3d11va_device_uninit,
    .चौकटाः_get_constraints = d3d11va_चौकटाः_get_constraints,
    .चौकटाः_init          = d3d11va_चौकटाः_init,
    .चौकटाः_uninit        = d3d11va_चौकटाः_uninit,
    .चौकटाः_get_बफर    = d3d11va_get_बफर,
    .transfer_get_formats = d3d11va_transfer_get_formats,
    .transfer_दत्त_गन्तव्यम्     = d3d11va_transfer_दत्त,
    .transfer_दत्त_from   = d3d11va_transfer_दत्त,

    .pix_fmts             = (ध्रुव गणना AVPixelFormat[]){ AV_PIX_FMT_D3D11, AV_PIX_FMT_NONE },
};
