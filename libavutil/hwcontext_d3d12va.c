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

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_d3d12va_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_d3d12va.h"
#ಅನ್ತರ್ಭಾವ "imgutils.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"
#ಅನ್ತರ್ಭಾವ "thread.h"
#ಅನ್ತರ್ಭಾವ "compat/w32dlfcn.h"
#ಅನ್ತರ್ಭಾವ <dxgi1_3.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY2)(UINT Flags, REFIID riid, ಶೂನ್ಯ **ppFactory);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ D3D12VAFramesContext {
    /**
     * The public AVD3D12VAFramesContext. See hwcontext_d3d12va.h for it.
     */
    AVD3D12VAFramesContext p;

    ID3D12Resource            *staging_download_ಬಫರ್;
    ID3D12Resource            *staging_upload_ಬಫರ್;
    ID3_D12_Command_ಸರತಿ        *command_ಸರತಿ;
    ID3D12CommandAllocator    *command_allocator;
    ID3D12GraphicsCommandList *command_list;
    AVD3D12VASyncContext       sync_ctx;
    UINT                       luma_component_ಗಾತ್ರ;
    ಪೂರ್ಣಾಂಕ                        nb_surfaces_ಬಳಸಿದ;
} D3D12VAFramesContext;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ D3D12VADevicePriv {
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    DXGI_FORMAT d3d_format;
    ಎಣಿಕೆ AVPixelFormat pix_fmt;
} supported_formats[] = {
    { DXGI_FORMAT_NV12, AV_PIX_FMT_NV12 },
    { DXGI_FORMAT_P010, AV_PIX_FMT_P010 },
    { DXGI_FORMAT_P016, AV_PIX_FMT_P012 },
};

ಸ್ಥಿರ ಶೂನ್ಯ d3d12va_default_ಬೀಗ(ಶೂನ್ಯ *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

ಸ್ಥಿರ ಶೂನ್ಯ d3d12va_default_unlock(ಶೂನ್ಯ *ctx)
{
    ReleaseMutex(ctx);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d12va_fence_completion(AVD3D12VASyncContext *psync_ctx)
{
    uint64_t completion = ID3_D12_Fence_Get_Completed_ಮೌಲ್ಯ(psync_ctx->fence);
    ಆದರೆ (completion < psync_ctx->fence_ಮೌಲ್ಯ) {
        ಆದರೆ (FAILED(ID3_D12_Fence_ಗಣ_Event_On_Completion(psync_ctx->fence, psync_ctx->fence_ಮೌಲ್ಯ, psync_ctx->event)))
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

        WaitForSingleObjectEx(psync_ctx->event, INFINITE, FALSE);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ d3d12va_wait_ಸರತಿ_idle(AVD3D12VASyncContext *psync_ctx, ID3_D12_Command_ಸರತಿ *command_ಸರತಿ)
{
    DX_CHECK(ID3_D12_Command_ಸರತಿ_Signal(command_ಸರತಿ, psync_ctx->fence, ++psync_ctx->fence_ಮೌಲ್ಯ));
    ಹಿಂತಿರುಗಿ d3d12va_fence_completion(psync_ctx);

fail:
    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d12va_create_staging_ಬಫರ್_resource(AVHWFramesContext *ctx, D3_D12_RESOURCE_ಸ್ಥಿತಿಗಳು ಸ್ಥಿತಿಗಳು,
                                                  ID3D12Resource **ppResource, ಪೂರ್ಣಾಂಕ download)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    D3_D12_ರಾಶಿ_PROPERTIES props = { .Type = download ? D3_D12_ರಾಶಿ_TYPE_READBACK : D3_D12_ರಾಶಿ_TYPE_UPLOAD };
    D3D12_RESOURCE_DESC desc = {
        .Dimension          = D3_D12_RESOURCE_DIMENSION_ಬಫರ್,
        .Alignment          = 0,
        .ಅಗಲ_2              = s->luma_component_ಗಾತ್ರ + (s->luma_component_ಗಾತ್ರ >> 1),
        .ಎತ್ತರ_2             = 1,
        .ಆಳ_Or_Array_ಗಾತ್ರ   = 1,
        .Mip_ಮಟ್ಟಗಳು          = 1,
        .Format             = DXGI_FORMAT_UNKNOWN,
        .SampleDesc         = { .ಎಣಿಕೆ_3 = 1, .Quality = 0 },
        .Layout             = D3_D12_TEXTURE_LAYOUT_ಅಡ್ಡಸಾಲು_MAJOR,
        .Flags              = D3D12_RESOURCE_FLAG_NONE,
    };

    ಆದರೆ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, D3_D12_ರಾಶಿ_FLAG_NONE, &desc,
        ಸ್ಥಿತಿಗಳು, ಖಾಲಿ, &IID_ID3D12Resource, (ಶೂನ್ಯ **)ppResource))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging buffer resource\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d12va_create_helper_objects(AVHWFramesContext *ctx)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *ಚೌಕಟ್ಟುಗಳು_hwctx = &s->p;

    D3_D12_COMMAND_ಸರತಿ_DESC ಸರತಿ_desc = {
        .Type     = D3D12_COMMAND_LIST_TYPE_COPY,
        .ಆದ್ಯತೆ = 0,
        .ಗಂಟು_ಮುಖವಾಡ = 0,
    };

    s->luma_component_ಗಾತ್ರ = FFALIGN(ctx->ಅಗಲ * (ಚೌಕಟ್ಟುಗಳು_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                                     D3_D12_TEXTURE_ದತ್ತಾಂಶ_PITCH_ALIGNMENT) * ctx->ಎತ್ತರ;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (ಶೂನ್ಯ **)&s->sync_ctx.fence));

    s->sync_ctx.event = CreateEvent(ಖಾಲಿ, FALSE, FALSE, ಖಾಲಿ);
    ಆದರೆ (!s->sync_ctx.event)
        ಹೋಗು fail;

    DX_CHECK(ID3_D12_Device_Create_Command_ಸರತಿ(device_hwctx->device, &ಸರತಿ_desc,
             &IID_ID3_D12_Command_ಸರತಿ, (ಶೂನ್ಯ **)&s->command_ಸರತಿ));

    DX_CHECK(ID3D12Device_CreateCommandAllocator(device_hwctx->device, ಸರತಿ_desc.Type,
             &IID_ID3D12CommandAllocator, (ಶೂನ್ಯ **)&s->command_allocator));

    DX_CHECK(ID3D12Device_CreateCommandList(device_hwctx->device, 0, ಸರತಿ_desc.Type,
             s->command_allocator, ಖಾಲಿ, &IID_ID3D12GraphicsCommandList, (ಶೂನ್ಯ **)&s->command_list));

    DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

    ID3_D12_Command_ಸರತಿ_Execute_Command_Lists(s->command_ಸರತಿ, 1, (ID3D12CommandList **)&s->command_list);

    ಹಿಂತಿರುಗಿ d3d12va_wait_ಸರತಿ_idle(&s->sync_ctx, s->command_ಸರತಿ);

fail:
    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಶೂನ್ಯ d3d12va_ಚೌಕಟ್ಟುಗಳು_uninit(AVHWFramesContext *ctx)
{
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;

    D3D12_OBJECT_RELEASE(s->sync_ctx.fence);
    ಆದರೆ (s->sync_ctx.event)
        CloseHandle(s->sync_ctx.event);

    D3D12_OBJECT_RELEASE(s->staging_download_ಬಫರ್);
    D3D12_OBJECT_RELEASE(s->staging_upload_ಬಫರ್);
    D3D12_OBJECT_RELEASE(s->command_allocator);
    D3D12_OBJECT_RELEASE(s->command_list);
    D3D12_OBJECT_RELEASE(s->command_ಸರತಿ);

    ಆದರೆ (hwctx->texture_array)
        D3D12_OBJECT_RELEASE(hwctx->texture_array);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d12va_ಚೌಕಟ್ಟುಗಳು_get_constraints(AVHWDeviceContext *ctx, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *hwconfig, AVHWFramesConstraints *constraints)
{
    HRESULT hr;
    ಪೂರ್ಣಾಂಕ nb_sw_formats = 0;
    AVD3D12VADeviceContext *device_hwctx = ctx->hwctx;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    ಗಾತ್ರ(*constraints->valid_sw_formats));
    ಆದರೆ (!constraints->valid_sw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        D3_D12_FEATURE_ದತ್ತಾಂಶ_FORMAT_SUPPORT format_support = { supported_formats[i].d3d_format };
        hr = ID3D12Device_CheckFeatureSupport(device_hwctx->device, D3D12_FEATURE_FORMAT_SUPPORT, &format_support, ಗಾತ್ರ(format_support));
        ಆದರೆ (SUCCEEDED(hr) && (format_support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ಗಾತ್ರ(*constraints->valid_hw_formats));
    ಆದರೆ (!constraints->valid_hw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D12;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ free_texture(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    AVD3D12VAFrame *ಚೌಕಟ್ಟು = (AVD3D12VAFrame *)ದತ್ತಾಂಶ;

    ಆದರೆ (!(ಚೌಕಟ್ಟು->flags & AV_D3_D12_VA_ಚೌಕಟ್ಟು_FLAG_TEXTURE_ARRAY))
        D3D12_OBJECT_RELEASE(ಚೌಕಟ್ಟು->texture);

    D3D12_OBJECT_RELEASE(ಚೌಕಟ್ಟು->sync_ctx.fence);
    ಆದರೆ (ಚೌಕಟ್ಟು->sync_ctx.event)
        CloseHandle(ಚೌಕಟ್ಟು->sync_ctx.event);

    av_freep(&ದತ್ತಾಂಶ);
}

ಸ್ಥಿರ AVBufferRef *d3d12va_pool_alloc_texture_array(AVHWFramesContext *ctx)
{
    AVD3D12VAFrame         *ಚೌಕಟ್ಟು  = av_mallocz(ಗಾತ್ರ(*ಚೌಕಟ್ಟು));
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    AVBufferRef *buf;

    ಚೌಕಟ್ಟು->flags |= AV_D3_D12_VA_ಚೌಕಟ್ಟು_FLAG_TEXTURE_ARRAY;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (ಶೂನ್ಯ **)&ಚೌಕಟ್ಟು->sync_ctx.fence));
    ಚೌಕಟ್ಟು->sync_ctx.event = CreateEvent(ಖಾಲಿ, FALSE, FALSE, ಖಾಲಿ);
    ಆದರೆ (!ಚೌಕಟ್ಟು->sync_ctx.event)
        ಹೋಗು fail;

    ಆದರೆ (s->nb_surfaces_ಬಳಸಿದ >= ctx->initial_pool_ಗಾತ್ರ) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        ಹೋಗು fail;
    }

    ಚೌಕಟ್ಟು->texture = hwctx->texture_array;
    ಚೌಕಟ್ಟು->subresource_ಸೂಚ್ಯಂಕ = s->nb_surfaces_ಬಳಸಿದ;

    buf = av_ಬಫರ್_create((uint8_t *)ಚೌಕಟ್ಟು, ಗಾತ್ರ(*ಚೌಕಟ್ಟು), free_texture, ಖಾಲಿ, 0);

    ಆದರೆ (!buf)
        ಹೋಗು fail;

    s->nb_surfaces_ಬಳಸಿದ++;
    ಹಿಂತಿರುಗಿ buf;
fail:
    free_texture(ಖಾಲಿ, (uint8_t *)ಚೌಕಟ್ಟು);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ AVBufferRef *d3d12va_pool_alloc(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    AVHWFramesContext      *ctx          = (AVHWFramesContext *)opaque;
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    AVBufferRef *buf;
    AVD3D12VAFrame *ಚೌಕಟ್ಟು;

    ಆದರೆ (ctx->initial_pool_ಗಾತ್ರ > 0 && hwctx->flags & AV_D3_D12_VA_ಚೌಕಟ್ಟು_FLAG_TEXTURE_ARRAY)
        ಹಿಂತಿರುಗಿ d3d12va_pool_alloc_texture_array(ctx);

    D3_D12_ರಾಶಿ_PROPERTIES props = { .Type = D3_D12_ರಾಶಿ_TYPE_DEFAULT };
    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .ಅಗಲ_2            = ctx->ಅಗಲ,
        .ಎತ್ತರ_2           = ctx->ಎತ್ತರ,
        .ಆಳ_Or_Array_ಗಾತ್ರ = 1,
        .Mip_ಮಟ್ಟಗಳು        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.ಎಣಿಕೆ_3 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    ಚೌಕಟ್ಟು = av_mallocz(ಗಾತ್ರ(AVD3D12VAFrame));
    ಆದರೆ (!ಚೌಕಟ್ಟು)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಆದರೆ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->ರಾಶಿ_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, ಖಾಲಿ, &IID_ID3D12Resource, (ಶೂನ್ಯ **)&ಚೌಕಟ್ಟು->texture))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture\n");
        ಹೋಗು fail;
    }

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (ಶೂನ್ಯ **)&ಚೌಕಟ್ಟು->sync_ctx.fence));

    ಚೌಕಟ್ಟು->sync_ctx.event = CreateEvent(ಖಾಲಿ, FALSE, FALSE, ಖಾಲಿ);
    ಆದರೆ (!ಚೌಕಟ್ಟು->sync_ctx.event)
        ಹೋಗು fail;

    buf = av_ಬಫರ್_create((uint8_t *)ಚೌಕಟ್ಟು, ಗಾತ್ರ(*ಚೌಕಟ್ಟು), free_texture, ಖಾಲಿ, 0);
    ಆದರೆ (!buf)
        ಹೋಗು fail;

    ಹಿಂತಿರುಗಿ buf;

fail:
    free_texture(ಖಾಲಿ, (uint8_t *)ಚೌಕಟ್ಟು);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d12va_texture_array_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    D3_D12_ರಾಶಿ_PROPERTIES props = { .Type = D3_D12_ರಾಶಿ_TYPE_DEFAULT };

    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .ಅಗಲ_2            = ctx->ಅಗಲ,
        .ಎತ್ತರ_2           = ctx->ಎತ್ತರ,
        .ಆಳ_Or_Array_ಗಾತ್ರ = ctx->initial_pool_ಗಾತ್ರ,
        .Mip_ಮಟ್ಟಗಳು        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.ಎಣಿಕೆ_3 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    ಆದರೆ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->ರಾಶಿ_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, ಖಾಲಿ, &IID_ID3D12Resource, (ಶೂನ್ಯ **)&hwctx->texture_array))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture array\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d12va_ಚೌಕಟ್ಟುಗಳು_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ಆದರೆ (ctx->sw_format == supported_formats[i].pix_fmt) {
            ಆದರೆ (hwctx->format != DXGI_FORMAT_UNKNOWN &&
                hwctx->format != supported_formats[i].d3d_format)
                av_log(ctx, AV_LOG_WARNING, "Incompatible DXGI format provided by user, will be overided\n");
            hwctx->format = supported_formats[i].d3d_format;
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    hwctx->resource_flags |= device_hwctx->resource_flags;
    hwctx->ರಾಶಿ_flags     |= device_hwctx->ರಾಶಿ_flags;

    ಆದರೆ (ctx->initial_pool_ಗಾತ್ರ > 0 && hwctx->flags & AV_D3_D12_VA_ಚೌಕಟ್ಟು_FLAG_TEXTURE_ARRAY) {
        ಪೂರ್ಣಾಂಕ err = d3d12va_texture_array_init(ctx);
        ಆದರೆ (err < 0)
            ಹಿಂತಿರುಗಿ err;
    }

    ffhwframesctx(ctx)->pool_ಆಂತರಿಕ = av_ಬಫರ್_pool_init2(ಗಾತ್ರ(AVD3D12VAFrame),
        ctx, d3d12va_pool_alloc, ಖಾಲಿ);

    ಆದರೆ (!ffhwframesctx(ctx)->pool_ಆಂತರಿಕ)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d12va_get_ಬಫರ್(AVHWFramesContext *ctx, AVFrame *ಚೌಕಟ್ಟು)
{
    ಪೂರ್ಣಾಂಕ ret;

    ಚೌಕಟ್ಟು->buf[0] = av_ಬಫರ್_pool_get(ctx->pool);
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0])
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ret = av_image_fill_arrays(ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ, ಚೌಕಟ್ಟು->linesize, ಖಾಲಿ,
                               ctx->sw_format, ctx->ಅಗಲ, ctx->ಎತ್ತರ,
                               D3_D12_TEXTURE_ದತ್ತಾಂಶ_PITCH_ALIGNMENT);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] = ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ;
    ಚೌಕಟ್ಟು->format  = AV_PIX_FMT_D3D12;
    ಚೌಕಟ್ಟು->ಅಗಲ   = ctx->ಅಗಲ;
    ಚೌಕಟ್ಟು->ಎತ್ತರ  = ctx->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d12va_transfer_get_formats(AVHWFramesContext *ctx,
                                        ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                        ಎಣಿಕೆ AVPixelFormat **formats)
{
    ಎಣಿಕೆ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ಗಾತ್ರ(*fmts));
    ಆದರೆ (!fmts)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d12va_transfer_ದತ್ತಾಂಶ(AVHWFramesContext *ctx, AVFrame *dst,
                                 ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    AVD3D12VADeviceContext *hwctx        = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *ಚೌಕಟ್ಟುಗಳು_hwctx = &s->p;

    ಪೂರ್ಣಾಂಕ ret;
    ಪೂರ್ಣಾಂಕ download = src->format == AV_PIX_FMT_D3D12;
    ಸ್ಥಿರಾಂಕ AVFrame *ಚೌಕಟ್ಟು = download ? src : dst;
    ಸ್ಥಿರಾಂಕ AVFrame *other = download ? dst : src;

    AVD3D12VAFrame *f = (AVD3D12VAFrame *)ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0];
    ID3D12Resource *texture = (ID3D12Resource *)f->texture;

    uint8_t *mapped_ದತ್ತಾಂಶ;
    uint8_t *ದತ್ತಾಂಶ[4];
    ಪೂರ್ಣಾಂಕ linesizes[4];

    D3D12_TEXTURE_COPY_LOCATION staging_y_location  = { 0 };
    D3D12_TEXTURE_COPY_LOCATION staging_uv_location = { 0 };

    D3D12_TEXTURE_COPY_LOCATION texture_y_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_ಸೂಚ್ಯಂಕ,
        .Subresource_ಸೂಚ್ಯಂಕ = 0,
    };

    D3D12_TEXTURE_COPY_LOCATION texture_uv_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_ಸೂಚ್ಯಂಕ,
        .Subresource_ಸೂಚ್ಯಂಕ = 1,
    };

    D3D12_RESOURCE_BARRIER barrier = {
        .Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
        .Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
        .Transition = {
            .pResource   = texture,
            .StateBefore = D3D12_RESOURCE_STATE_COMMON,
            .StateAfter  = download ? D3_D12_RESOURCE_STATE_COPY_ಮೂಲ : D3D12_RESOURCE_STATE_COPY_DEST,
            .Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
        },
    };

    ಆದರೆ (ಚೌಕಟ್ಟು->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ != (uint8_t *)ctx || other->format != ctx->sw_format)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    hwctx->ಬೀಗ_2(hwctx->ಬೀಗ_ctx);

    ಆದರೆ (!s->command_ಸರತಿ) {
        ret = d3d12va_create_helper_objects(ctx);
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 4; i++)
        linesizes[i] = FFALIGN(ಚೌಕಟ್ಟು->ಅಗಲ * (ಚೌಕಟ್ಟುಗಳು_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                               D3_D12_TEXTURE_ದತ್ತಾಂಶ_PITCH_ALIGNMENT);

    staging_y_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .ಸ್ಥಾನಾಂತರ_4 = 0,
            .Footprint = {
                .Format   = ಚೌಕಟ್ಟುಗಳು_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16_UNORM : DXGI_FORMAT_R8_UNORM,
                .ಅಗಲ_2    = ctx->ಅಗಲ,
                .ಎತ್ತರ_2   = ctx->ಎತ್ತರ,
                .ಆಳ_2    = 1,
                .ಅಡ್ಡಸಾಲು_Pitch = linesizes[0],
            },
        },
    };

    staging_uv_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .ಸ್ಥಾನಾಂತರ_4 = s->luma_component_ಗಾತ್ರ,
            .Footprint = {
                .Format   = ಚೌಕಟ್ಟುಗಳು_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16G16_UNORM : DXGI_FORMAT_R8G8_UNORM,
                .ಅಗಲ_2    = ctx->ಅಗಲ  >> 1,
                .ಎತ್ತರ_2   = ctx->ಎತ್ತರ >> 1,
                .ಆಳ_2    = 1,
                .ಅಡ್ಡಸಾಲು_Pitch = linesizes[0],
            },
        },
    };

    DX_CHECK(ID3D12CommandAllocator_Reset(s->command_allocator));

    DX_CHECK(ID3D12GraphicsCommandList_Reset(s->command_list, s->command_allocator, ಖಾಲಿ));

    ಆದರೆ (download) {
        ಆದರೆ (!s->staging_download_ಬಫರ್) {
            ret = d3d12va_create_staging_ಬಫರ್_resource(ctx, D3D12_RESOURCE_STATE_COPY_DEST,
                                                         &s->staging_download_ಬಫರ್, 1);
            ಆದರೆ (ret < 0) {
                ಹೋಗು fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_download_ಬಫರ್;

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_y_location, 0, 0, 0,
                                                    &texture_y_location, ಖಾಲಿ);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_uv_location, 0, 0, 0,
                                                    &texture_uv_location, ಖಾಲಿ);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        DX_CHECK(ID3_D12_Command_ಸರತಿ_Wait(s->command_ಸರತಿ, f->sync_ctx.fence, f->sync_ctx.fence_ಮೌಲ್ಯ));

        ID3_D12_Command_ಸರತಿ_Execute_Command_Lists(s->command_ಸರತಿ, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_ಸರತಿ_idle(&s->sync_ctx, s->command_ಸರತಿ);
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;

        DX_CHECK(ID3D12Resource_Map(s->staging_download_ಬಫರ್, 0, ಖಾಲಿ, (ಶೂನ್ಯ **)&mapped_ದತ್ತಾಂಶ));
        av_image_fill_ಸೂಚಕಗಳು(ದತ್ತಾಂಶ, ctx->sw_format, ctx->ಎತ್ತರ, mapped_ದತ್ತಾಂಶ, linesizes);

        av_image_copy2(dst->ದತ್ತಾಂಶ, dst->linesize, ದತ್ತಾಂಶ, linesizes,
                       ctx->sw_format, ctx->ಅಗಲ, ctx->ಎತ್ತರ);

        ID3D12Resource_Unmap(s->staging_download_ಬಫರ್, 0, ಖಾಲಿ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!s->staging_upload_ಬಫರ್) {
            ret = d3d12va_create_staging_ಬಫರ್_resource(ctx, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                        &s->staging_upload_ಬಫರ್, 0);
            ಆದರೆ (ret < 0) {
                ಹೋಗು fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_upload_ಬಫರ್;

        DX_CHECK(ID3D12Resource_Map(s->staging_upload_ಬಫರ್, 0, ಖಾಲಿ, (ಶೂನ್ಯ **)&mapped_ದತ್ತಾಂಶ));
        av_image_fill_ಸೂಚಕಗಳು(ದತ್ತಾಂಶ, ctx->sw_format, ctx->ಎತ್ತರ, mapped_ದತ್ತಾಂಶ, linesizes);

        av_image_copy2(ದತ್ತಾಂಶ, linesizes, src->ದತ್ತಾಂಶ, src->linesize,
                       ctx->sw_format, ctx->ಅಗಲ, ctx->ಎತ್ತರ);

        ID3D12Resource_Unmap(s->staging_upload_ಬಫರ್, 0, ಖಾಲಿ);

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_y_location, 0, 0, 0,
                                                    &staging_y_location, ಖಾಲಿ);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_uv_location, 0, 0, 0,
                                                    &staging_uv_location, ಖಾಲಿ);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        ID3_D12_Command_ಸರತಿ_Execute_Command_Lists(s->command_ಸರತಿ, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_ಸರತಿ_idle(&s->sync_ctx, s->command_ಸರತಿ);
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;
    }

    hwctx->unlock(hwctx->ಬೀಗ_ctx);

    ಹಿಂತಿರುಗಿ 0;

fail:
    hwctx->unlock(hwctx->ಬೀಗ_ctx);
    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d12va_ತುಂಬು_functions(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv *priv = hwdev->hwctx;

#ಆದರೆ !HAVE_UWP
    priv->d3d12lib = dlopen("d3d12.dll", 0);
    priv->dxgilib  = dlopen("dxgi.dll", 0);

    ಆದರೆ (!priv->d3d12lib || !priv->dxgilib)
        ಹೋಗು fail;

    priv->create_device = (PFN_D3D12_CREATE_DEVICE)Get_Proc_ವಿಳಾಸ(priv->d3d12lib, "D3D12CreateDevice");
    ಆದರೆ (!priv->create_device)
        ಹೋಗು fail;

    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2)Get_Proc_ವಿಳಾಸ(priv->dxgilib, "CreateDXGIFactory2");
    ಆದರೆ (!priv->create_dxgi_factory2)
        ಹೋಗು fail;

    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE)Get_Proc_ವಿಳಾಸ(priv->d3d12lib, "D3D12GetDebugInterface");
#ಇಲ್ಲದಿದ್ದರೆ
    priv->create_device        = (PFN_D3D12_CREATE_DEVICE) D3D12CreateDevice;
    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2) CreateDXGIFactory2;
    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE) D3D12GetDebugInterface;
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ 0;

#ಆದರೆ !HAVE_UWP
fail:
    av_log(hwdev, AV_LOG_ERROR, "Failed to load D3D12 library or its functions\n");
    ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಶೂನ್ಯ d3d12va_device_free(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    D3D12_OBJECT_RELEASE(ctx->device);

    ಆದರೆ (priv->d3d12lib)
        dlclose(priv->d3d12lib);

    ಆದರೆ (priv->dxgilib)
        dlclose(priv->dxgilib);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d12va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *ctx = hwdev->hwctx;

    ಆದರೆ (!ctx->ಬೀಗ_2) {
        ctx->ಬೀಗ_ctx = CreateMutex(ಖಾಲಿ, 0, ಖಾಲಿ);
        ಆದರೆ (ctx->ಬೀಗ_ctx == INVALID_HANDLE_ಮೌಲ್ಯ) {
            av_log(ಖಾಲಿ, AV_LOG_ERROR, "Failed to create a mutex\n");
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
        ctx->ಬೀಗ_2   = d3d12va_default_ಬೀಗ;
        ctx->unlock = d3d12va_default_unlock;
    }

    ಆದರೆ (!ctx->video_device)
        DX_CHECK(ID3D12Device_QueryInterface(ctx->device, &IID_ID3D12VideoDevice, (ಶೂನ್ಯ **)&ctx->video_device));

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಶೂನ್ಯ d3d12va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *device_hwctx = hwdev->hwctx;

    D3D12_OBJECT_RELEASE(device_hwctx->video_device);

    ಆದರೆ (device_hwctx->ಬೀಗ_2 == d3d12va_default_ಬೀಗ) {
        CloseHandle(device_hwctx->ಬೀಗ_ctx);
        device_hwctx->ಬೀಗ_ctx = INVALID_HANDLE_ಮೌಲ್ಯ;
        device_hwctx->ಬೀಗ_2 = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ d3d12va_device_create(AVHWDeviceContext *hwdev, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                                 AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    HRESULT hr;
    UINT create_flags = 0;
    IDXGIAdapter *pAdapter = ಖಾಲಿ;

    ಪೂರ್ಣಾಂಕ ret;
    ಪೂರ್ಣಾಂಕ is_debug = !!av_dict_get(opts, "debug", ಖಾಲಿ, 0);

    hwdev->ಬಿಡುಗಡೆ = d3d12va_device_free;

    ret = d3d12va_ತುಂಬು_functions(hwdev);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (is_debug) {
        ID3D12Debug *pDebug;
        ಆದರೆ (priv->get_debug_interface && SUCCEEDED(priv->get_debug_interface(&IID_ID3D12Debug, (ಶೂನ್ಯ **)&pDebug))) {
            create_flags |= DXGI_CREATE_FACTORY_DEBUG;
            ID3D12Debug_EnableDebugLayer(pDebug);
            D3D12_OBJECT_RELEASE(pDebug);
            av_log(hwdev, AV_LOG_INFO, "D3D12 debug layer is enabled!\n");
        }
    }

    ಆದರೆ (!ctx->device) {
        IDXGIFactory2 *pDXGIFactory = ಖಾಲಿ;

        hr = priv->create_dxgi_factory2(create_flags, &IID_IDXGIFactory2, (ಶೂನ್ಯ **)&pDXGIFactory);
        ಆದರೆ (SUCCEEDED(hr)) {
            ಪೂರ್ಣಾಂಕ adapter = device ? atoi(device) : 0;
            ಆದರೆ (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = ಖಾಲಿ;
            IDXGIFactory2_Release(pDXGIFactory);
        }

        ಆದರೆ (pAdapter) {
            DXGI_ADAPTER_DESC desc;
            hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
            ಆದರೆ (!FAILED(hr)) {
                av_log(hwdev, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                       desc.VendorId, desc.DeviceId, desc.Description);
            }
        }

        hr = priv->create_device((IUnknown *)pAdapter, D3D_FEATURE_LEVEL_12_0, &IID_ID3D12Device, (ಶೂನ್ಯ **)&ctx->device);
        D3D12_OBJECT_RELEASE(pAdapter);
        ಆದರೆ (FAILED(hr)) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create Direct 3D 12 device (%lx)\n", (ದೀರ್ಘ)hr);
            ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
        }
    }

    ಆದರೆ (av_dict_get(opts, "UAV", ಖಾಲಿ, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    ಆದರೆ (av_dict_get(opts, "RTV", ಖಾಲಿ, 0))
        ctx->resource_flags |= D3_D12_RESOURCE_FLAG_ALLOW_RENDER_ಗುರಿ;

    ಆದರೆ (av_dict_get(opts, "SHARED", ಖಾಲಿ, 0))
        ctx->ರಾಶಿ_flags |= D3_D12_ರಾಶಿ_FLAG_SHARED;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_d3d12va = {
    .type                   = AV_HWDEVICE_TYPE_D3D12VA,
    .name                   = "D3D12VA",

    .device_hwctx_ಗಾತ್ರ      = ಗಾತ್ರ(D3D12VADevicePriv),
    .ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ      = ಗಾತ್ರ(D3D12VAFramesContext),

    .device_create          = d3d12va_device_create,
    .device_init            = d3d12va_device_init,
    .device_uninit          = d3d12va_device_uninit,
    .ಚೌಕಟ್ಟುಗಳು_get_constraints = d3d12va_ಚೌಕಟ್ಟುಗಳು_get_constraints,
    .ಚೌಕಟ್ಟುಗಳು_init            = d3d12va_ಚೌಕಟ್ಟುಗಳು_init,
    .ಚೌಕಟ್ಟುಗಳು_uninit          = d3d12va_ಚೌಕಟ್ಟುಗಳು_uninit,
    .ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್      = d3d12va_get_ಬಫರ್,
    .transfer_get_formats   = d3d12va_transfer_get_formats,
    .transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ       = d3d12va_transfer_ದತ್ತಾಂಶ,
    .transfer_ದತ್ತಾಂಶ_from     = d3d12va_transfer_ದತ್ತಾಂಶ,

    .pix_fmts               = (ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat[]){ AV_PIX_FMT_D3D12, AV_PIX_FMT_NONE },
};
