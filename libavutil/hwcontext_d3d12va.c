/*
 * Direct3D 12 HW acceleration.
 *
 * copyright (c) 2022-2023 Wu Jianhua <toqsxw@outlook.com>
 *
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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_d3d12va_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_d3d12va.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "imgutils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "compat/w32dlfcn.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <dxgi1_3.h>

ਕਿਸਮਪਰਿਭਾਸ਼ਾ HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY2)(UINT Flags, REFIID riid, ਖਾਲੀ **ppFactory);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ D3D12VAFramesContext {
    /**
     * The public AVD3D12VAFramesContext. See hwcontext_d3d12va.h for it.
     */
    AVD3D12VAFramesContext p;

    ID3D12Resource            *staging_download_ਬਫਰ;
    ID3D12Resource            *staging_upload_ਬਫਰ;
    ID3_D12_Command_ਕਤਾਰ        *command_ਕਤਾਰ;
    ID3D12CommandAllocator    *command_allocator;
    ID3D12GraphicsCommandList *command_list;
    AVD3D12VASyncContext       sync_ctx;
    UINT                       luma_component_ਮਾਪ;
    ਪੂਰਨ                        nb_surfaces_ਵਰਤਿਆ;
} D3D12VAFramesContext;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ D3D12VADevicePriv {
    /**
     * The public AVD3D12VADeviceContext. See hwcontext_d3d12va.h for it.
     */
    AVD3D12VADeviceContext p;
    HANDLE                        d3d12lib;
    HANDLE                        dxgilib;
    PFN_CREATE_DXGI_FACTORY2      create_dxgi_factory2;
    PFN_D3D12_CREATE_DEVICE       create_device;
    PFN_D3D12_GET_DEBUG_INTERFACE get_debug_interface;
} D3D12VADevicePriv;

ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
    DXGI_FORMAT d3d_format;
    ਗਿਣਤੀ AVPixelFormat pix_fmt;
} supported_formats[] = {
    { DXGI_FORMAT_NV12, AV_PIX_FMT_NV12 },
    { DXGI_FORMAT_P010, AV_PIX_FMT_P010 },
    { DXGI_FORMAT_P016, AV_PIX_FMT_P012 },
};

ਸਥਿਰ ਖਾਲੀ d3d12va_default_ਤਾਲਾ(ਖਾਲੀ *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

ਸਥਿਰ ਖਾਲੀ d3d12va_default_unlock(ਖਾਲੀ *ctx)
{
    ReleaseMutex(ctx);
}

ਸਥਿਰ ਪੂਰਨ d3d12va_fence_completion(AVD3D12VASyncContext *psync_ctx)
{
    uint64_t completion = ID3_D12_Fence_Get_Completed_ਮੁੱਲ(psync_ctx->fence);
    ਜੇ (completion < psync_ctx->fence_ਮੁੱਲ) {
        ਜੇ (FAILED(ID3_D12_Fence_ਸੈੱਟ_Event_On_Completion(psync_ctx->fence, psync_ctx->fence_ਮੁੱਲ, psync_ctx->event)))
            ਵਾਪਸ AVERROR(EINVAL);

        WaitForSingleObjectEx(psync_ctx->event, INFINITE, FALSE);
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ d3d12va_wait_ਕਤਾਰ_idle(AVD3D12VASyncContext *psync_ctx, ID3_D12_Command_ਕਤਾਰ *command_ਕਤਾਰ)
{
    DX_CHECK(ID3_D12_Command_ਕਤਾਰ_Signal(command_ਕਤਾਰ, psync_ctx->fence, ++psync_ctx->fence_ਮੁੱਲ));
    ਵਾਪਸ d3d12va_fence_completion(psync_ctx);

fail:
    ਵਾਪਸ AVERROR(EINVAL);
}

ਸਥਿਰ ਪੂਰਨ d3d12va_create_staging_ਬਫਰ_resource(AVHWFramesContext *ctx, D3_D12_RESOURCE_ਹਾਲਤਾਂ ਹਾਲਤਾਂ,
                                                  ID3D12Resource **ppResource, ਪੂਰਨ download)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    D3_D12_ਢੇਰ_PROPERTIES props = { .Type = download ? D3_D12_ਢੇਰ_TYPE_READBACK : D3_D12_ਢੇਰ_TYPE_UPLOAD };
    D3D12_RESOURCE_DESC desc = {
        .Dimension          = D3_D12_RESOURCE_DIMENSION_ਬਫਰ,
        .Alignment          = 0,
        .ਚੌੜਾਈ_2              = s->luma_component_ਮਾਪ + (s->luma_component_ਮਾਪ >> 1),
        .ਉਚਾਈ_2             = 1,
        .ਡੂੰਘਾਈ_Or_Array_ਮਾਪ   = 1,
        .Mip_ਪੱਧਰ          = 1,
        .Format             = DXGI_FORMAT_UNKNOWN,
        .SampleDesc         = { .ਗਿਣਤੀ_3 = 1, .Quality = 0 },
        .Layout             = D3_D12_TEXTURE_LAYOUT_ਪੰਕਤੀ_MAJOR,
        .Flags              = D3D12_RESOURCE_FLAG_NONE,
    };

    ਜੇ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, D3_D12_ਢੇਰ_FLAG_NONE, &desc,
        ਹਾਲਤਾਂ, ਨਿਰਾ, &IID_ID3D12Resource, (ਖਾਲੀ **)ppResource))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging buffer resource\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ d3d12va_create_helper_objects(AVHWFramesContext *ctx)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *ਚੌਖਟੇ_hwctx = &s->p;

    D3_D12_COMMAND_ਕਤਾਰ_DESC ਕਤਾਰ_desc = {
        .Type     = D3D12_COMMAND_LIST_TYPE_COPY,
        .ਤਰਜੀਹ = 0,
        .ਗੰਢ_ਨਕਾਬ = 0,
    };

    s->luma_component_ਮਾਪ = FFALIGN(ctx->ਚੌੜਾਈ * (ਚੌਖਟੇ_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                                     D3_D12_TEXTURE_ਅੰਕੜੇ_PITCH_ALIGNMENT) * ctx->ਉਚਾਈ;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (ਖਾਲੀ **)&s->sync_ctx.fence));

    s->sync_ctx.event = CreateEvent(ਨਿਰਾ, FALSE, FALSE, ਨਿਰਾ);
    ਜੇ (!s->sync_ctx.event)
        ਜਾਓ fail;

    DX_CHECK(ID3_D12_Device_Create_Command_ਕਤਾਰ(device_hwctx->device, &ਕਤਾਰ_desc,
             &IID_ID3_D12_Command_ਕਤਾਰ, (ਖਾਲੀ **)&s->command_ਕਤਾਰ));

    DX_CHECK(ID3D12Device_CreateCommandAllocator(device_hwctx->device, ਕਤਾਰ_desc.Type,
             &IID_ID3D12CommandAllocator, (ਖਾਲੀ **)&s->command_allocator));

    DX_CHECK(ID3D12Device_CreateCommandList(device_hwctx->device, 0, ਕਤਾਰ_desc.Type,
             s->command_allocator, ਨਿਰਾ, &IID_ID3D12GraphicsCommandList, (ਖਾਲੀ **)&s->command_list));

    DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

    ID3_D12_Command_ਕਤਾਰ_Execute_Command_Lists(s->command_ਕਤਾਰ, 1, (ID3D12CommandList **)&s->command_list);

    ਵਾਪਸ d3d12va_wait_ਕਤਾਰ_idle(&s->sync_ctx, s->command_ਕਤਾਰ);

fail:
    ਵਾਪਸ AVERROR(EINVAL);
}

ਸਥਿਰ ਖਾਲੀ d3d12va_ਚੌਖਟੇ_uninit(AVHWFramesContext *ctx)
{
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;

    D3D12_OBJECT_RELEASE(s->sync_ctx.fence);
    ਜੇ (s->sync_ctx.event)
        CloseHandle(s->sync_ctx.event);

    D3D12_OBJECT_RELEASE(s->staging_download_ਬਫਰ);
    D3D12_OBJECT_RELEASE(s->staging_upload_ਬਫਰ);
    D3D12_OBJECT_RELEASE(s->command_allocator);
    D3D12_OBJECT_RELEASE(s->command_list);
    D3D12_OBJECT_RELEASE(s->command_ਕਤਾਰ);

    ਜੇ (hwctx->texture_array)
        D3D12_OBJECT_RELEASE(hwctx->texture_array);
}

ਸਥਿਰ ਪੂਰਨ d3d12va_ਚੌਖਟੇ_get_constraints(AVHWDeviceContext *ctx, ਅਚਲ ਖਾਲੀ *hwconfig, AVHWFramesConstraints *constraints)
{
    HRESULT hr;
    ਪੂਰਨ nb_sw_formats = 0;
    AVD3D12VADeviceContext *device_hwctx = ctx->hwctx;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    ਆਕਾਰ(*constraints->valid_sw_formats));
    ਜੇ (!constraints->valid_sw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        D3_D12_FEATURE_ਅੰਕੜੇ_FORMAT_SUPPORT format_support = { supported_formats[i].d3d_format };
        hr = ID3D12Device_CheckFeatureSupport(device_hwctx->device, D3D12_FEATURE_FORMAT_SUPPORT, &format_support, ਆਕਾਰ(format_support));
        ਜੇ (SUCCEEDED(hr) && (format_support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ਆਕਾਰ(*constraints->valid_hw_formats));
    ਜੇ (!constraints->valid_hw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D12;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ free_texture(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    AVD3D12VAFrame *ਚੌਖਟਾ = (AVD3D12VAFrame *)ਅੰਕੜੇ;

    ਜੇ (!(ਚੌਖਟਾ->flags & AV_D3_D12_VA_ਚੌਖਟਾ_FLAG_TEXTURE_ARRAY))
        D3D12_OBJECT_RELEASE(ਚੌਖਟਾ->texture);

    D3D12_OBJECT_RELEASE(ਚੌਖਟਾ->sync_ctx.fence);
    ਜੇ (ਚੌਖਟਾ->sync_ctx.event)
        CloseHandle(ਚੌਖਟਾ->sync_ctx.event);

    av_freep(&ਅੰਕੜੇ);
}

ਸਥਿਰ AVBufferRef *d3d12va_pool_alloc_texture_array(AVHWFramesContext *ctx)
{
    AVD3D12VAFrame         *ਚੌਖਟਾ  = av_mallocz(ਆਕਾਰ(*ਚੌਖਟਾ));
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    AVBufferRef *buf;

    ਚੌਖਟਾ->flags |= AV_D3_D12_VA_ਚੌਖਟਾ_FLAG_TEXTURE_ARRAY;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (ਖਾਲੀ **)&ਚੌਖਟਾ->sync_ctx.fence));
    ਚੌਖਟਾ->sync_ctx.event = CreateEvent(ਨਿਰਾ, FALSE, FALSE, ਨਿਰਾ);
    ਜੇ (!ਚੌਖਟਾ->sync_ctx.event)
        ਜਾਓ fail;

    ਜੇ (s->nb_surfaces_ਵਰਤਿਆ >= ctx->initial_pool_ਮਾਪ) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        ਜਾਓ fail;
    }

    ਚੌਖਟਾ->texture = hwctx->texture_array;
    ਚੌਖਟਾ->subresource_ਸੂਚਕਾਂਕ = s->nb_surfaces_ਵਰਤਿਆ;

    buf = av_ਬਫਰ_create((uint8_t *)ਚੌਖਟਾ, ਆਕਾਰ(*ਚੌਖਟਾ), free_texture, ਨਿਰਾ, 0);

    ਜੇ (!buf)
        ਜਾਓ fail;

    s->nb_surfaces_ਵਰਤਿਆ++;
    ਵਾਪਸ buf;
fail:
    free_texture(ਨਿਰਾ, (uint8_t *)ਚੌਖਟਾ);
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ AVBufferRef *d3d12va_pool_alloc(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    AVHWFramesContext      *ctx          = (AVHWFramesContext *)opaque;
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    AVBufferRef *buf;
    AVD3D12VAFrame *ਚੌਖਟਾ;

    ਜੇ (ctx->initial_pool_ਮਾਪ > 0 && hwctx->flags & AV_D3_D12_VA_ਚੌਖਟਾ_FLAG_TEXTURE_ARRAY)
        ਵਾਪਸ d3d12va_pool_alloc_texture_array(ctx);

    D3_D12_ਢੇਰ_PROPERTIES props = { .Type = D3_D12_ਢੇਰ_TYPE_DEFAULT };
    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .ਚੌੜਾਈ_2            = ctx->ਚੌੜਾਈ,
        .ਉਚਾਈ_2           = ctx->ਉਚਾਈ,
        .ਡੂੰਘਾਈ_Or_Array_ਮਾਪ = 1,
        .Mip_ਪੱਧਰ        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.ਗਿਣਤੀ_3 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    ਚੌਖਟਾ = av_mallocz(ਆਕਾਰ(AVD3D12VAFrame));
    ਜੇ (!ਚੌਖਟਾ)
        ਵਾਪਸ ਨਿਰਾ;

    ਜੇ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->ਢੇਰ_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, ਨਿਰਾ, &IID_ID3D12Resource, (ਖਾਲੀ **)&ਚੌਖਟਾ->texture))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture\n");
        ਜਾਓ fail;
    }

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (ਖਾਲੀ **)&ਚੌਖਟਾ->sync_ctx.fence));

    ਚੌਖਟਾ->sync_ctx.event = CreateEvent(ਨਿਰਾ, FALSE, FALSE, ਨਿਰਾ);
    ਜੇ (!ਚੌਖਟਾ->sync_ctx.event)
        ਜਾਓ fail;

    buf = av_ਬਫਰ_create((uint8_t *)ਚੌਖਟਾ, ਆਕਾਰ(*ਚੌਖਟਾ), free_texture, ਨਿਰਾ, 0);
    ਜੇ (!buf)
        ਜਾਓ fail;

    ਵਾਪਸ buf;

fail:
    free_texture(ਨਿਰਾ, (uint8_t *)ਚੌਖਟਾ);
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਪੂਰਨ d3d12va_texture_array_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    D3_D12_ਢੇਰ_PROPERTIES props = { .Type = D3_D12_ਢੇਰ_TYPE_DEFAULT };

    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .ਚੌੜਾਈ_2            = ctx->ਚੌੜਾਈ,
        .ਉਚਾਈ_2           = ctx->ਉਚਾਈ,
        .ਡੂੰਘਾਈ_Or_Array_ਮਾਪ = ctx->initial_pool_ਮਾਪ,
        .Mip_ਪੱਧਰ        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.ਗਿਣਤੀ_3 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    ਜੇ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->ਢੇਰ_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, ਨਿਰਾ, &IID_ID3D12Resource, (ਖਾਲੀ **)&hwctx->texture_array))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture array\n");
        ਵਾਪਸ AVERROR(EINVAL);
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ d3d12va_ਚੌਖਟੇ_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ਜੇ (ctx->sw_format == supported_formats[i].pix_fmt) {
            ਜੇ (hwctx->format != DXGI_FORMAT_UNKNOWN &&
                hwctx->format != supported_formats[i].d3d_format)
                av_log(ctx, AV_LOG_WARNING, "Incompatible DXGI format provided by user, will be overided\n");
            hwctx->format = supported_formats[i].d3d_format;
            ਰੋਕੋ;
        }
    }

    ਜੇ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ਵਾਪਸ AVERROR(EINVAL);
    }

    hwctx->resource_flags |= device_hwctx->resource_flags;
    hwctx->ਢੇਰ_flags     |= device_hwctx->ਢੇਰ_flags;

    ਜੇ (ctx->initial_pool_ਮਾਪ > 0 && hwctx->flags & AV_D3_D12_VA_ਚੌਖਟਾ_FLAG_TEXTURE_ARRAY) {
        ਪੂਰਨ err = d3d12va_texture_array_init(ctx);
        ਜੇ (err < 0)
            ਵਾਪਸ err;
    }

    ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ = av_ਬਫਰ_pool_init2(ਆਕਾਰ(AVD3D12VAFrame),
        ctx, d3d12va_pool_alloc, ਨਿਰਾ);

    ਜੇ (!ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ d3d12va_get_ਬਫਰ(AVHWFramesContext *ctx, AVFrame *ਚੌਖਟਾ)
{
    ਪੂਰਨ ret;

    ਚੌਖਟਾ->buf[0] = av_ਬਫਰ_pool_get(ctx->pool);
    ਜੇ (!ਚੌਖਟਾ->buf[0])
        ਵਾਪਸ AVERROR(ENOMEM);

    ret = av_image_fill_arrays(ਚੌਖਟਾ->ਅੰਕੜੇ, ਚੌਖਟਾ->linesize, ਨਿਰਾ,
                               ctx->sw_format, ctx->ਚੌੜਾਈ, ctx->ਉਚਾਈ,
                               D3_D12_TEXTURE_ਅੰਕੜੇ_PITCH_ALIGNMENT);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਚੌਖਟਾ->ਅੰਕੜੇ[0] = ਚੌਖਟਾ->buf[0]->ਅੰਕੜੇ;
    ਚੌਖਟਾ->format  = AV_PIX_FMT_D3D12;
    ਚੌਖਟਾ->ਚੌੜਾਈ   = ctx->ਚੌੜਾਈ;
    ਚੌਖਟਾ->ਉਚਾਈ  = ctx->ਉਚਾਈ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ d3d12va_transfer_get_formats(AVHWFramesContext *ctx,
                                        ਗਿਣਤੀ AVHWFrameTransferDirection dir,
                                        ਗਿਣਤੀ AVPixelFormat **formats)
{
    ਗਿਣਤੀ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ਆਕਾਰ(*fmts));
    ਜੇ (!fmts)
        ਵਾਪਸ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ d3d12va_transfer_ਅੰਕੜੇ(AVHWFramesContext *ctx, AVFrame *dst,
                                 ਅਚਲ AVFrame *src)
{
    AVD3D12VADeviceContext *hwctx        = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *ਚੌਖਟੇ_hwctx = &s->p;

    ਪੂਰਨ ret;
    ਪੂਰਨ download = src->format == AV_PIX_FMT_D3D12;
    ਅਚਲ AVFrame *ਚੌਖਟਾ = download ? src : dst;
    ਅਚਲ AVFrame *other = download ? dst : src;

    AVD3D12VAFrame *f = (AVD3D12VAFrame *)ਚੌਖਟਾ->ਅੰਕੜੇ[0];
    ID3D12Resource *texture = (ID3D12Resource *)f->texture;

    uint8_t *mapped_ਅੰਕੜੇ;
    uint8_t *ਅੰਕੜੇ[4];
    ਪੂਰਨ linesizes[4];

    D3D12_TEXTURE_COPY_LOCATION staging_y_location  = { 0 };
    D3D12_TEXTURE_COPY_LOCATION staging_uv_location = { 0 };

    D3D12_TEXTURE_COPY_LOCATION texture_y_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_ਸੂਚਕਾਂਕ,
        .Subresource_ਸੂਚਕਾਂਕ = 0,
    };

    D3D12_TEXTURE_COPY_LOCATION texture_uv_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_ਸੂਚਕਾਂਕ,
        .Subresource_ਸੂਚਕਾਂਕ = 1,
    };

    D3D12_RESOURCE_BARRIER barrier = {
        .Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
        .Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
        .Transition = {
            .pResource   = texture,
            .StateBefore = D3D12_RESOURCE_STATE_COMMON,
            .StateAfter  = download ? D3_D12_RESOURCE_STATE_COPY_ਸਰੋਤ : D3D12_RESOURCE_STATE_COPY_DEST,
            .Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
        },
    };

    ਜੇ (ਚੌਖਟਾ->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ != (uint8_t *)ctx || other->format != ctx->sw_format)
        ਵਾਪਸ AVERROR(EINVAL);

    hwctx->ਤਾਲਾ(hwctx->ਤਾਲਾ_ctx);

    ਜੇ (!s->command_ਕਤਾਰ) {
        ret = d3d12va_create_helper_objects(ctx);
        ਜੇ (ret < 0)
            ਜਾਓ fail;
    }

    ਲਈ (ਪੂਰਨ i = 0; i < 4; i++)
        linesizes[i] = FFALIGN(ਚੌਖਟਾ->ਚੌੜਾਈ * (ਚੌਖਟੇ_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                               D3_D12_TEXTURE_ਅੰਕੜੇ_PITCH_ALIGNMENT);

    staging_y_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .ਵਿੱਥ_4 = 0,
            .Footprint = {
                .Format   = ਚੌਖਟੇ_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16_UNORM : DXGI_FORMAT_R8_UNORM,
                .ਚੌੜਾਈ_2    = ctx->ਚੌੜਾਈ,
                .ਉਚਾਈ_2   = ctx->ਉਚਾਈ,
                .ਡੂੰਘਾਈ_2    = 1,
                .ਪੰਕਤੀ_Pitch = linesizes[0],
            },
        },
    };

    staging_uv_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .ਵਿੱਥ_4 = s->luma_component_ਮਾਪ,
            .Footprint = {
                .Format   = ਚੌਖਟੇ_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16G16_UNORM : DXGI_FORMAT_R8G8_UNORM,
                .ਚੌੜਾਈ_2    = ctx->ਚੌੜਾਈ  >> 1,
                .ਉਚਾਈ_2   = ctx->ਉਚਾਈ >> 1,
                .ਡੂੰਘਾਈ_2    = 1,
                .ਪੰਕਤੀ_Pitch = linesizes[0],
            },
        },
    };

    DX_CHECK(ID3D12CommandAllocator_Reset(s->command_allocator));

    DX_CHECK(ID3D12GraphicsCommandList_Reset(s->command_list, s->command_allocator, ਨਿਰਾ));

    ਜੇ (download) {
        ਜੇ (!s->staging_download_ਬਫਰ) {
            ret = d3d12va_create_staging_ਬਫਰ_resource(ctx, D3D12_RESOURCE_STATE_COPY_DEST,
                                                         &s->staging_download_ਬਫਰ, 1);
            ਜੇ (ret < 0) {
                ਜਾਓ fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_download_ਬਫਰ;

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_y_location, 0, 0, 0,
                                                    &texture_y_location, ਨਿਰਾ);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_uv_location, 0, 0, 0,
                                                    &texture_uv_location, ਨਿਰਾ);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        DX_CHECK(ID3_D12_Command_ਕਤਾਰ_Wait(s->command_ਕਤਾਰ, f->sync_ctx.fence, f->sync_ctx.fence_ਮੁੱਲ));

        ID3_D12_Command_ਕਤਾਰ_Execute_Command_Lists(s->command_ਕਤਾਰ, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_ਕਤਾਰ_idle(&s->sync_ctx, s->command_ਕਤਾਰ);
        ਜੇ (ret < 0)
            ਜਾਓ fail;

        DX_CHECK(ID3D12Resource_Map(s->staging_download_ਬਫਰ, 0, ਨਿਰਾ, (ਖਾਲੀ **)&mapped_ਅੰਕੜੇ));
        av_image_fill_ਸੂਚਕ_ਸਾਰੇ(ਅੰਕੜੇ, ctx->sw_format, ctx->ਉਚਾਈ, mapped_ਅੰਕੜੇ, linesizes);

        av_image_copy2(dst->ਅੰਕੜੇ, dst->linesize, ਅੰਕੜੇ, linesizes,
                       ctx->sw_format, ctx->ਚੌੜਾਈ, ctx->ਉਚਾਈ);

        ID3D12Resource_Unmap(s->staging_download_ਬਫਰ, 0, ਨਿਰਾ);
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!s->staging_upload_ਬਫਰ) {
            ret = d3d12va_create_staging_ਬਫਰ_resource(ctx, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                        &s->staging_upload_ਬਫਰ, 0);
            ਜੇ (ret < 0) {
                ਜਾਓ fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_upload_ਬਫਰ;

        DX_CHECK(ID3D12Resource_Map(s->staging_upload_ਬਫਰ, 0, ਨਿਰਾ, (ਖਾਲੀ **)&mapped_ਅੰਕੜੇ));
        av_image_fill_ਸੂਚਕ_ਸਾਰੇ(ਅੰਕੜੇ, ctx->sw_format, ctx->ਉਚਾਈ, mapped_ਅੰਕੜੇ, linesizes);

        av_image_copy2(ਅੰਕੜੇ, linesizes, src->ਅੰਕੜੇ, src->linesize,
                       ctx->sw_format, ctx->ਚੌੜਾਈ, ctx->ਉਚਾਈ);

        ID3D12Resource_Unmap(s->staging_upload_ਬਫਰ, 0, ਨਿਰਾ);

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_y_location, 0, 0, 0,
                                                    &staging_y_location, ਨਿਰਾ);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_uv_location, 0, 0, 0,
                                                    &staging_uv_location, ਨਿਰਾ);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        ID3_D12_Command_ਕਤਾਰ_Execute_Command_Lists(s->command_ਕਤਾਰ, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_ਕਤਾਰ_idle(&s->sync_ctx, s->command_ਕਤਾਰ);
        ਜੇ (ret < 0)
            ਜਾਓ fail;
    }

    hwctx->unlock(hwctx->ਤਾਲਾ_ctx);

    ਵਾਪਸ 0;

fail:
    hwctx->unlock(hwctx->ਤਾਲਾ_ctx);
    ਵਾਪਸ AVERROR(EINVAL);
}

ਸਥਿਰ ਪੂਰਨ d3d12va_ਲੱਦੋ_functions(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv *priv = hwdev->hwctx;

#ਜੇ !HAVE_UWP
    priv->d3d12lib = dlopen("d3d12.dll", 0);
    priv->dxgilib  = dlopen("dxgi.dll", 0);

    ਜੇ (!priv->d3d12lib || !priv->dxgilib)
        ਜਾਓ fail;

    priv->create_device = (PFN_D3D12_CREATE_DEVICE)Get_Proc_ਪਤਾ(priv->d3d12lib, "D3D12CreateDevice");
    ਜੇ (!priv->create_device)
        ਜਾਓ fail;

    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2)Get_Proc_ਪਤਾ(priv->dxgilib, "CreateDXGIFactory2");
    ਜੇ (!priv->create_dxgi_factory2)
        ਜਾਓ fail;

    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE)Get_Proc_ਪਤਾ(priv->d3d12lib, "D3D12GetDebugInterface");
#ਨਹੀਂਤਾਂ
    priv->create_device        = (PFN_D3D12_CREATE_DEVICE) D3D12CreateDevice;
    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2) CreateDXGIFactory2;
    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE) D3D12GetDebugInterface;
#ਜੇ_ਅੰਤ
    ਵਾਪਸ 0;

#ਜੇ !HAVE_UWP
fail:
    av_log(hwdev, AV_LOG_ERROR, "Failed to load D3D12 library or its functions\n");
    ਵਾਪਸ AVERROR_UNKNOWN;
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ ਖਾਲੀ d3d12va_device_free(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    D3D12_OBJECT_RELEASE(ctx->device);

    ਜੇ (priv->d3d12lib)
        dlclose(priv->d3d12lib);

    ਜੇ (priv->dxgilib)
        dlclose(priv->dxgilib);
}

ਸਥਿਰ ਪੂਰਨ d3d12va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *ctx = hwdev->hwctx;

    ਜੇ (!ctx->ਤਾਲਾ) {
        ctx->ਤਾਲਾ_ctx = CreateMutex(ਨਿਰਾ, 0, ਨਿਰਾ);
        ਜੇ (ctx->ਤਾਲਾ_ctx == INVALID_HANDLE_ਮੁੱਲ) {
            av_log(ਨਿਰਾ, AV_LOG_ERROR, "Failed to create a mutex\n");
            ਵਾਪਸ AVERROR(EINVAL);
        }
        ctx->ਤਾਲਾ   = d3d12va_default_ਤਾਲਾ;
        ctx->unlock = d3d12va_default_unlock;
    }

    ਜੇ (!ctx->video_device)
        DX_CHECK(ID3D12Device_QueryInterface(ctx->device, &IID_ID3D12VideoDevice, (ਖਾਲੀ **)&ctx->video_device));

    ਵਾਪਸ 0;

fail:
    ਵਾਪਸ AVERROR(EINVAL);
}

ਸਥਿਰ ਖਾਲੀ d3d12va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *device_hwctx = hwdev->hwctx;

    D3D12_OBJECT_RELEASE(device_hwctx->video_device);

    ਜੇ (device_hwctx->ਤਾਲਾ == d3d12va_default_ਤਾਲਾ) {
        CloseHandle(device_hwctx->ਤਾਲਾ_ctx);
        device_hwctx->ਤਾਲਾ_ctx = INVALID_HANDLE_ਮੁੱਲ;
        device_hwctx->ਤਾਲਾ = ਨਿਰਾ;
    }
}

ਸਥਿਰ ਪੂਰਨ d3d12va_device_create(AVHWDeviceContext *hwdev, ਅਚਲ ਅੱਖਰ *device,
                                 AVDictionary *opts, ਪੂਰਨ flags)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    HRESULT hr;
    UINT create_flags = 0;
    IDXGIAdapter *pAdapter = ਨਿਰਾ;

    ਪੂਰਨ ret;
    ਪੂਰਨ is_debug = !!av_dict_get(opts, "debug", ਨਿਰਾ, 0);

    hwdev->ਮੁਕਤ = d3d12va_device_free;

    ret = d3d12va_ਲੱਦੋ_functions(hwdev);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਜੇ (is_debug) {
        ID3D12Debug *pDebug;
        ਜੇ (priv->get_debug_interface && SUCCEEDED(priv->get_debug_interface(&IID_ID3D12Debug, (ਖਾਲੀ **)&pDebug))) {
            create_flags |= DXGI_CREATE_FACTORY_DEBUG;
            ID3D12Debug_EnableDebugLayer(pDebug);
            D3D12_OBJECT_RELEASE(pDebug);
            av_log(hwdev, AV_LOG_INFO, "D3D12 debug layer is enabled!\n");
        }
    }

    ਜੇ (!ctx->device) {
        IDXGIFactory2 *pDXGIFactory = ਨਿਰਾ;

        hr = priv->create_dxgi_factory2(create_flags, &IID_IDXGIFactory2, (ਖਾਲੀ **)&pDXGIFactory);
        ਜੇ (SUCCEEDED(hr)) {
            ਪੂਰਨ adapter = device ? atoi(device) : 0;
            ਜੇ (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = ਨਿਰਾ;
            IDXGIFactory2_Release(pDXGIFactory);
        }

        ਜੇ (pAdapter) {
            DXGI_ADAPTER_DESC desc;
            hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
            ਜੇ (!FAILED(hr)) {
                av_log(hwdev, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                       desc.VendorId, desc.DeviceId, desc.Description);
            }
        }

        hr = priv->create_device((IUnknown *)pAdapter, D3D_FEATURE_LEVEL_12_0, &IID_ID3D12Device, (ਖਾਲੀ **)&ctx->device);
        D3D12_OBJECT_RELEASE(pAdapter);
        ਜੇ (FAILED(hr)) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create Direct 3D 12 device (%lx)\n", (ਲੰਮਾ)hr);
            ਵਾਪਸ AVERROR_UNKNOWN;
        }
    }

    ਜੇ (av_dict_get(opts, "UAV", ਨਿਰਾ, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    ਜੇ (av_dict_get(opts, "RTV", ਨਿਰਾ, 0))
        ctx->resource_flags |= D3_D12_RESOURCE_FLAG_ALLOW_RENDER_ਨਿਸ਼ਾਨਾ;

    ਜੇ (av_dict_get(opts, "SHARED", ਨਿਰਾ, 0))
        ctx->ਢੇਰ_flags |= D3_D12_ਢੇਰ_FLAG_SHARED;

    ਵਾਪਸ 0;
}

ਅਚਲ HWContextType ff_hwcontext_type_d3d12va = {
    .type                   = AV_HWDEVICE_TYPE_D3D12VA,
    .name                   = "D3D12VA",

    .device_hwctx_ਮਾਪ      = ਆਕਾਰ(D3D12VADevicePriv),
    .ਚੌਖਟੇ_hwctx_ਮਾਪ      = ਆਕਾਰ(D3D12VAFramesContext),

    .device_create          = d3d12va_device_create,
    .device_init            = d3d12va_device_init,
    .device_uninit          = d3d12va_device_uninit,
    .ਚੌਖਟੇ_get_constraints = d3d12va_ਚੌਖਟੇ_get_constraints,
    .ਚੌਖਟੇ_init            = d3d12va_ਚੌਖਟੇ_init,
    .ਚੌਖਟੇ_uninit          = d3d12va_ਚੌਖਟੇ_uninit,
    .ਚੌਖਟੇ_get_ਬਫਰ      = d3d12va_get_ਬਫਰ,
    .transfer_get_formats   = d3d12va_transfer_get_formats,
    .transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ       = d3d12va_transfer_ਅੰਕੜੇ,
    .transfer_ਅੰਕੜੇ_from     = d3d12va_transfer_ਅੰਕੜੇ,

    .pix_fmts               = (ਅਚਲ ਗਿਣਤੀ AVPixelFormat[]){ AV_PIX_FMT_D3D12, AV_PIX_FMT_NONE },
};
