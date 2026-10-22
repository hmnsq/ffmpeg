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

#شامل "config.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_internal.h"
#شامل "hwcontext_d3d12va_internal.h"
#شامل "hwcontext_d3d12va.h"
#شامل "imgutils.h"
#شامل "mem.h"
#شامل "pixdesc.h"
#شامل "pixfmt.h"
#شامل "thread.h"
#شامل "compat/w32dlfcn.h"
#شامل <dxgi1_3.h>

قسمتعریف HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY2)(UINT Flags, REFIID riid, خالی **ppFactory);

قسمتعریف ساخت D3D12VAFramesContext {
    /**
     * The public AVD3D12VAFramesContext. See hwcontext_d3d12va.h for it.
     */
    AVD3D12VAFramesContext p;

    ID3D12Resource            *staging_download_بفر;
    ID3D12Resource            *staging_upload_بفر;
    ID3_D12_Command_قطار        *command_قطار;
    ID3D12CommandAllocator    *command_allocator;
    ID3D12GraphicsCommandList *command_list;
    AVD3D12VASyncContext       sync_ctx;
    UINT                       luma_component_سائز;
    صحیح                        nb_surfaces_مستعمل;
} D3D12VAFramesContext;

قسمتعریف ساخت D3D12VADevicePriv {
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

ساکن ثابت ساخت {
    DXGI_FORMAT d3d_format;
    شمار AVPixelFormat pix_fmt;
} supported_formats[] = {
    { DXGI_FORMAT_NV12, AV_PIX_FMT_NV12 },
    { DXGI_FORMAT_P010, AV_PIX_FMT_P010 },
    { DXGI_FORMAT_P016, AV_PIX_FMT_P012 },
};

ساکن خالی d3d12va_default_تالا(خالی *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

ساکن خالی d3d12va_default_unlock(خالی *ctx)
{
    ReleaseMutex(ctx);
}

ساکن صحیح d3d12va_fence_completion(AVD3D12VASyncContext *psync_ctx)
{
    uint64_t completion = ID3_D12_Fence_Get_Completed_قدر(psync_ctx->fence);
    اگر (completion < psync_ctx->fence_قدر) {
        اگر (FAILED(ID3_D12_Fence_سیٹ_Event_On_Completion(psync_ctx->fence, psync_ctx->fence_قدر, psync_ctx->event)))
            واپس AVERROR(EINVAL);

        WaitForSingleObjectEx(psync_ctx->event, INFINITE, FALSE);
    }

    واپس 0;
}

ساکن اندرونی صحیح d3d12va_wait_قطار_idle(AVD3D12VASyncContext *psync_ctx, ID3_D12_Command_قطار *command_قطار)
{
    DX_CHECK(ID3_D12_Command_قطار_Signal(command_قطار, psync_ctx->fence, ++psync_ctx->fence_قدر));
    واپس d3d12va_fence_completion(psync_ctx);

fail:
    واپس AVERROR(EINVAL);
}

ساکن صحیح d3d12va_create_staging_بفر_resource(AVHWFramesContext *ctx, D3_D12_RESOURCE_حالتیں حالتیں,
                                                  ID3D12Resource **ppResource, صحیح download)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    D3_D12_ڈھیر_PROPERTIES props = { .Type = download ? D3_D12_ڈھیر_TYPE_READBACK : D3_D12_ڈھیر_TYPE_UPLOAD };
    D3D12_RESOURCE_DESC desc = {
        .Dimension          = D3_D12_RESOURCE_DIMENSION_بفر,
        .Alignment          = 0,
        .چوڑائی_2              = s->luma_component_سائز + (s->luma_component_سائز >> 1),
        .اونچائی_2             = 1,
        .گہرائی_Or_Array_سائز   = 1,
        .Mip_سطحیں          = 1,
        .Format             = DXGI_FORMAT_UNKNOWN,
        .SampleDesc         = { .گنتی_2 = 1, .Quality = 0 },
        .Layout             = D3_D12_TEXTURE_LAYOUT_صف_MAJOR,
        .Flags              = D3D12_RESOURCE_FLAG_NONE,
    };

    اگر (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, D3_D12_ڈھیر_FLAG_NONE, &desc,
        حالتیں, تہی, &IID_ID3D12Resource, (خالی **)ppResource))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging buffer resource\n");
        واپس AVERROR_UNKNOWN;
    }

    واپس 0;
}

ساکن صحیح d3d12va_create_helper_objects(AVHWFramesContext *ctx)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *چوکھٹے_hwctx = &s->p;

    D3_D12_COMMAND_قطار_DESC قطار_desc = {
        .Type     = D3D12_COMMAND_LIST_TYPE_COPY,
        .ترجیح = 0,
        .گرہ_نقاب = 0,
    };

    s->luma_component_سائز = FFALIGN(ctx->چوڑائی * (چوکھٹے_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                                     D3_D12_TEXTURE_ڈیٹا_PITCH_ALIGNMENT) * ctx->اونچائی;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (خالی **)&s->sync_ctx.fence));

    s->sync_ctx.event = CreateEvent(تہی, FALSE, FALSE, تہی);
    اگر (!s->sync_ctx.event)
        جاؤ fail;

    DX_CHECK(ID3_D12_Device_Create_Command_قطار(device_hwctx->device, &قطار_desc,
             &IID_ID3_D12_Command_قطار, (خالی **)&s->command_قطار));

    DX_CHECK(ID3D12Device_CreateCommandAllocator(device_hwctx->device, قطار_desc.Type,
             &IID_ID3D12CommandAllocator, (خالی **)&s->command_allocator));

    DX_CHECK(ID3D12Device_CreateCommandList(device_hwctx->device, 0, قطار_desc.Type,
             s->command_allocator, تہی, &IID_ID3D12GraphicsCommandList, (خالی **)&s->command_list));

    DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

    ID3_D12_Command_قطار_Execute_Command_Lists(s->command_قطار, 1, (ID3D12CommandList **)&s->command_list);

    واپس d3d12va_wait_قطار_idle(&s->sync_ctx, s->command_قطار);

fail:
    واپس AVERROR(EINVAL);
}

ساکن خالی d3d12va_چوکھٹے_uninit(AVHWFramesContext *ctx)
{
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;

    D3D12_OBJECT_RELEASE(s->sync_ctx.fence);
    اگر (s->sync_ctx.event)
        CloseHandle(s->sync_ctx.event);

    D3D12_OBJECT_RELEASE(s->staging_download_بفر);
    D3D12_OBJECT_RELEASE(s->staging_upload_بفر);
    D3D12_OBJECT_RELEASE(s->command_allocator);
    D3D12_OBJECT_RELEASE(s->command_list);
    D3D12_OBJECT_RELEASE(s->command_قطار);

    اگر (hwctx->texture_array)
        D3D12_OBJECT_RELEASE(hwctx->texture_array);
}

ساکن صحیح d3d12va_چوکھٹے_get_constraints(AVHWDeviceContext *ctx, ثابت خالی *hwconfig, AVHWFramesConstraints *constraints)
{
    HRESULT hr;
    صحیح nb_sw_formats = 0;
    AVD3D12VADeviceContext *device_hwctx = ctx->hwctx;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    اگر (!constraints->valid_sw_formats)
        واپس AVERROR(ENOMEM);

    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        D3_D12_FEATURE_ڈیٹا_FORMAT_SUPPORT format_support = { supported_formats[i].d3d_format };
        hr = ID3D12Device_CheckFeatureSupport(device_hwctx->device, D3D12_FEATURE_FORMAT_SUPPORT, &format_support, حجم(format_support));
        اگر (SUCCEEDED(hr) && (format_support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    اگر (!constraints->valid_hw_formats)
        واپس AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D12;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    واپس 0;
}

ساکن خالی free_texture(خالی *opaque, uint8_t *ڈیٹا)
{
    AVD3D12VAFrame *چوکھٹا = (AVD3D12VAFrame *)ڈیٹا;

    اگر (!(چوکھٹا->flags & AV_D3_D12_VA_چوکھٹا_FLAG_TEXTURE_ARRAY))
        D3D12_OBJECT_RELEASE(چوکھٹا->texture);

    D3D12_OBJECT_RELEASE(چوکھٹا->sync_ctx.fence);
    اگر (چوکھٹا->sync_ctx.event)
        CloseHandle(چوکھٹا->sync_ctx.event);

    av_freep(&ڈیٹا);
}

ساکن AVBufferRef *d3d12va_pool_alloc_texture_array(AVHWFramesContext *ctx)
{
    AVD3D12VAFrame         *چوکھٹا  = av_mallocz(حجم(*چوکھٹا));
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    AVBufferRef *buf;

    چوکھٹا->flags |= AV_D3_D12_VA_چوکھٹا_FLAG_TEXTURE_ARRAY;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (خالی **)&چوکھٹا->sync_ctx.fence));
    چوکھٹا->sync_ctx.event = CreateEvent(تہی, FALSE, FALSE, تہی);
    اگر (!چوکھٹا->sync_ctx.event)
        جاؤ fail;

    اگر (s->nb_surfaces_مستعمل >= ctx->initial_pool_سائز) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        جاؤ fail;
    }

    چوکھٹا->texture = hwctx->texture_array;
    چوکھٹا->subresource_اشاریہ = s->nb_surfaces_مستعمل;

    buf = av_بفر_create((uint8_t *)چوکھٹا, حجم(*چوکھٹا), free_texture, تہی, 0);

    اگر (!buf)
        جاؤ fail;

    s->nb_surfaces_مستعمل++;
    واپس buf;
fail:
    free_texture(تہی, (uint8_t *)چوکھٹا);
    واپس تہی;
}

ساکن AVBufferRef *d3d12va_pool_alloc(خالی *opaque, size_t سائز)
{
    AVHWFramesContext      *ctx          = (AVHWFramesContext *)opaque;
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    AVBufferRef *buf;
    AVD3D12VAFrame *چوکھٹا;

    اگر (ctx->initial_pool_سائز > 0 && hwctx->flags & AV_D3_D12_VA_چوکھٹا_FLAG_TEXTURE_ARRAY)
        واپس d3d12va_pool_alloc_texture_array(ctx);

    D3_D12_ڈھیر_PROPERTIES props = { .Type = D3_D12_ڈھیر_TYPE_DEFAULT };
    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .چوڑائی_2            = ctx->چوڑائی,
        .اونچائی_2           = ctx->اونچائی,
        .گہرائی_Or_Array_سائز = 1,
        .Mip_سطحیں        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.گنتی_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    چوکھٹا = av_mallocz(حجم(AVD3D12VAFrame));
    اگر (!چوکھٹا)
        واپس تہی;

    اگر (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->ڈھیر_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, تہی, &IID_ID3D12Resource, (خالی **)&چوکھٹا->texture))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture\n");
        جاؤ fail;
    }

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (خالی **)&چوکھٹا->sync_ctx.fence));

    چوکھٹا->sync_ctx.event = CreateEvent(تہی, FALSE, FALSE, تہی);
    اگر (!چوکھٹا->sync_ctx.event)
        جاؤ fail;

    buf = av_بفر_create((uint8_t *)چوکھٹا, حجم(*چوکھٹا), free_texture, تہی, 0);
    اگر (!buf)
        جاؤ fail;

    واپس buf;

fail:
    free_texture(تہی, (uint8_t *)چوکھٹا);
    واپس تہی;
}

ساکن صحیح d3d12va_texture_array_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    D3_D12_ڈھیر_PROPERTIES props = { .Type = D3_D12_ڈھیر_TYPE_DEFAULT };

    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .چوڑائی_2            = ctx->چوڑائی,
        .اونچائی_2           = ctx->اونچائی,
        .گہرائی_Or_Array_سائز = ctx->initial_pool_سائز,
        .Mip_سطحیں        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.گنتی_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    اگر (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->ڈھیر_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, تہی, &IID_ID3D12Resource, (خالی **)&hwctx->texture_array))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture array\n");
        واپس AVERROR(EINVAL);
    }
    واپس 0;
}

ساکن صحیح d3d12va_چوکھٹے_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    صحیح i;

    برائے (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        اگر (ctx->sw_format == supported_formats[i].pix_fmt) {
            اگر (hwctx->format != DXGI_FORMAT_UNKNOWN &&
                hwctx->format != supported_formats[i].d3d_format)
                av_log(ctx, AV_LOG_WARNING, "Incompatible DXGI format provided by user, will be overided\n");
            hwctx->format = supported_formats[i].d3d_format;
            توڑو;
        }
    }

    اگر (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        واپس AVERROR(EINVAL);
    }

    hwctx->resource_flags |= device_hwctx->resource_flags;
    hwctx->ڈھیر_flags     |= device_hwctx->ڈھیر_flags;

    اگر (ctx->initial_pool_سائز > 0 && hwctx->flags & AV_D3_D12_VA_چوکھٹا_FLAG_TEXTURE_ARRAY) {
        صحیح err = d3d12va_texture_array_init(ctx);
        اگر (err < 0)
            واپس err;
    }

    ffhwframesctx(ctx)->pool_اندرونی = av_بفر_pool_init2(حجم(AVD3D12VAFrame),
        ctx, d3d12va_pool_alloc, تہی);

    اگر (!ffhwframesctx(ctx)->pool_اندرونی)
        واپس AVERROR(ENOMEM);

    واپس 0;
}

ساکن صحیح d3d12va_get_بفر(AVHWFramesContext *ctx, AVFrame *چوکھٹا)
{
    صحیح ret;

    چوکھٹا->buf[0] = av_بفر_pool_get(ctx->pool);
    اگر (!چوکھٹا->buf[0])
        واپس AVERROR(ENOMEM);

    ret = av_image_fill_arrays(چوکھٹا->ڈیٹا, چوکھٹا->linesize, تہی,
                               ctx->sw_format, ctx->چوڑائی, ctx->اونچائی,
                               D3_D12_TEXTURE_ڈیٹا_PITCH_ALIGNMENT);
    اگر (ret < 0)
        واپس ret;

    چوکھٹا->ڈیٹا[0] = چوکھٹا->buf[0]->ڈیٹا;
    چوکھٹا->format  = AV_PIX_FMT_D3D12;
    چوکھٹا->چوڑائی   = ctx->چوڑائی;
    چوکھٹا->اونچائی  = ctx->اونچائی;

    واپس 0;
}

ساکن صحیح d3d12va_transfer_get_formats(AVHWFramesContext *ctx,
                                        شمار AVHWFrameTransferDirection dir,
                                        شمار AVPixelFormat **formats)
{
    شمار AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    اگر (!fmts)
        واپس AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    واپس 0;
}

ساکن صحیح d3d12va_transfer_ڈیٹا(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    AVD3D12VADeviceContext *hwctx        = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *چوکھٹے_hwctx = &s->p;

    صحیح ret;
    صحیح download = src->format == AV_PIX_FMT_D3D12;
    ثابت AVFrame *چوکھٹا = download ? src : dst;
    ثابت AVFrame *other = download ? dst : src;

    AVD3D12VAFrame *f = (AVD3D12VAFrame *)چوکھٹا->ڈیٹا[0];
    ID3D12Resource *texture = (ID3D12Resource *)f->texture;

    uint8_t *mapped_ڈیٹا;
    uint8_t *ڈیٹا[4];
    صحیح linesizes[4];

    D3D12_TEXTURE_COPY_LOCATION staging_y_location  = { 0 };
    D3D12_TEXTURE_COPY_LOCATION staging_uv_location = { 0 };

    D3D12_TEXTURE_COPY_LOCATION texture_y_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_اشاریہ,
        .Subresource_اشاریہ = 0,
    };

    D3D12_TEXTURE_COPY_LOCATION texture_uv_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_اشاریہ,
        .Subresource_اشاریہ = 1,
    };

    D3D12_RESOURCE_BARRIER barrier = {
        .Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
        .Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
        .Transition = {
            .pResource   = texture,
            .StateBefore = D3D12_RESOURCE_STATE_COMMON,
            .StateAfter  = download ? D3_D12_RESOURCE_STATE_COPY_ماخذ : D3D12_RESOURCE_STATE_COPY_DEST,
            .Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
        },
    };

    اگر (چوکھٹا->hw_چوکھٹے_ctx->ڈیٹا != (uint8_t *)ctx || other->format != ctx->sw_format)
        واپس AVERROR(EINVAL);

    hwctx->تالا_2(hwctx->تالا_ctx);

    اگر (!s->command_قطار) {
        ret = d3d12va_create_helper_objects(ctx);
        اگر (ret < 0)
            جاؤ fail;
    }

    برائے (صحیح i = 0; i < 4; i++)
        linesizes[i] = FFALIGN(چوکھٹا->چوڑائی * (چوکھٹے_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                               D3_D12_TEXTURE_ڈیٹا_PITCH_ALIGNMENT);

    staging_y_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .انحراف_4 = 0,
            .Footprint = {
                .Format   = چوکھٹے_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16_UNORM : DXGI_FORMAT_R8_UNORM,
                .چوڑائی_2    = ctx->چوڑائی,
                .اونچائی_2   = ctx->اونچائی,
                .گہرائی_2    = 1,
                .صف_Pitch = linesizes[0],
            },
        },
    };

    staging_uv_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .انحراف_4 = s->luma_component_سائز,
            .Footprint = {
                .Format   = چوکھٹے_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16G16_UNORM : DXGI_FORMAT_R8G8_UNORM,
                .چوڑائی_2    = ctx->چوڑائی  >> 1,
                .اونچائی_2   = ctx->اونچائی >> 1,
                .گہرائی_2    = 1,
                .صف_Pitch = linesizes[0],
            },
        },
    };

    DX_CHECK(ID3D12CommandAllocator_Reset(s->command_allocator));

    DX_CHECK(ID3D12GraphicsCommandList_Reset(s->command_list, s->command_allocator, تہی));

    اگر (download) {
        اگر (!s->staging_download_بفر) {
            ret = d3d12va_create_staging_بفر_resource(ctx, D3D12_RESOURCE_STATE_COPY_DEST,
                                                         &s->staging_download_بفر, 1);
            اگر (ret < 0) {
                جاؤ fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_download_بفر;

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_y_location, 0, 0, 0,
                                                    &texture_y_location, تہی);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_uv_location, 0, 0, 0,
                                                    &texture_uv_location, تہی);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        DX_CHECK(ID3_D12_Command_قطار_Wait(s->command_قطار, f->sync_ctx.fence, f->sync_ctx.fence_قدر));

        ID3_D12_Command_قطار_Execute_Command_Lists(s->command_قطار, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_قطار_idle(&s->sync_ctx, s->command_قطار);
        اگر (ret < 0)
            جاؤ fail;

        DX_CHECK(ID3D12Resource_Map(s->staging_download_بفر, 0, تہی, (خالی **)&mapped_ڈیٹا));
        av_image_fill_اشارے(ڈیٹا, ctx->sw_format, ctx->اونچائی, mapped_ڈیٹا, linesizes);

        av_image_copy2(dst->ڈیٹا, dst->linesize, ڈیٹا, linesizes,
                       ctx->sw_format, ctx->چوڑائی, ctx->اونچائی);

        ID3D12Resource_Unmap(s->staging_download_بفر, 0, تہی);
    } ورنہ {
        اگر (!s->staging_upload_بفر) {
            ret = d3d12va_create_staging_بفر_resource(ctx, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                        &s->staging_upload_بفر, 0);
            اگر (ret < 0) {
                جاؤ fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_upload_بفر;

        DX_CHECK(ID3D12Resource_Map(s->staging_upload_بفر, 0, تہی, (خالی **)&mapped_ڈیٹا));
        av_image_fill_اشارے(ڈیٹا, ctx->sw_format, ctx->اونچائی, mapped_ڈیٹا, linesizes);

        av_image_copy2(ڈیٹا, linesizes, src->ڈیٹا, src->linesize,
                       ctx->sw_format, ctx->چوڑائی, ctx->اونچائی);

        ID3D12Resource_Unmap(s->staging_upload_بفر, 0, تہی);

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_y_location, 0, 0, 0,
                                                    &staging_y_location, تہی);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_uv_location, 0, 0, 0,
                                                    &staging_uv_location, تہی);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        ID3_D12_Command_قطار_Execute_Command_Lists(s->command_قطار, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_قطار_idle(&s->sync_ctx, s->command_قطار);
        اگر (ret < 0)
            جاؤ fail;
    }

    hwctx->unlock(hwctx->تالا_ctx);

    واپس 0;

fail:
    hwctx->unlock(hwctx->تالا_ctx);
    واپس AVERROR(EINVAL);
}

ساکن صحیح d3d12va_بھرو_functions(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv *priv = hwdev->hwctx;

#اگر !HAVE_UWP
    priv->d3d12lib = dlopen("d3d12.dll", 0);
    priv->dxgilib  = dlopen("dxgi.dll", 0);

    اگر (!priv->d3d12lib || !priv->dxgilib)
        جاؤ fail;

    priv->create_device = (PFN_D3D12_CREATE_DEVICE)Get_Proc_پتہ(priv->d3d12lib, "D3D12CreateDevice");
    اگر (!priv->create_device)
        جاؤ fail;

    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2)Get_Proc_پتہ(priv->dxgilib, "CreateDXGIFactory2");
    اگر (!priv->create_dxgi_factory2)
        جاؤ fail;

    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE)Get_Proc_پتہ(priv->d3d12lib, "D3D12GetDebugInterface");
#ورنہ
    priv->create_device        = (PFN_D3D12_CREATE_DEVICE) D3D12CreateDevice;
    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2) CreateDXGIFactory2;
    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE) D3D12GetDebugInterface;
#اگر_ختم
    واپس 0;

#اگر !HAVE_UWP
fail:
    av_log(hwdev, AV_LOG_ERROR, "Failed to load D3D12 library or its functions\n");
    واپس AVERROR_UNKNOWN;
#اگر_ختم
}

ساکن خالی d3d12va_device_free(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    D3D12_OBJECT_RELEASE(ctx->device);

    اگر (priv->d3d12lib)
        dlclose(priv->d3d12lib);

    اگر (priv->dxgilib)
        dlclose(priv->dxgilib);
}

ساکن صحیح d3d12va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *ctx = hwdev->hwctx;

    اگر (!ctx->تالا_2) {
        ctx->تالا_ctx = CreateMutex(تہی, 0, تہی);
        اگر (ctx->تالا_ctx == INVALID_HANDLE_قدر) {
            av_log(تہی, AV_LOG_ERROR, "Failed to create a mutex\n");
            واپس AVERROR(EINVAL);
        }
        ctx->تالا_2   = d3d12va_default_تالا;
        ctx->unlock = d3d12va_default_unlock;
    }

    اگر (!ctx->video_device)
        DX_CHECK(ID3D12Device_QueryInterface(ctx->device, &IID_ID3D12VideoDevice, (خالی **)&ctx->video_device));

    واپس 0;

fail:
    واپس AVERROR(EINVAL);
}

ساکن خالی d3d12va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *device_hwctx = hwdev->hwctx;

    D3D12_OBJECT_RELEASE(device_hwctx->video_device);

    اگر (device_hwctx->تالا_2 == d3d12va_default_تالا) {
        CloseHandle(device_hwctx->تالا_ctx);
        device_hwctx->تالا_ctx = INVALID_HANDLE_قدر;
        device_hwctx->تالا_2 = تہی;
    }
}

ساکن صحیح d3d12va_device_create(AVHWDeviceContext *hwdev, ثابت حرف *device,
                                 AVDictionary *opts, صحیح flags)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    HRESULT hr;
    UINT create_flags = 0;
    IDXGIAdapter *pAdapter = تہی;

    صحیح ret;
    صحیح is_debug = !!av_dict_get(opts, "debug", تہی, 0);

    hwdev->آزاد = d3d12va_device_free;

    ret = d3d12va_بھرو_functions(hwdev);
    اگر (ret < 0)
        واپس ret;

    اگر (is_debug) {
        ID3D12Debug *pDebug;
        اگر (priv->get_debug_interface && SUCCEEDED(priv->get_debug_interface(&IID_ID3D12Debug, (خالی **)&pDebug))) {
            create_flags |= DXGI_CREATE_FACTORY_DEBUG;
            ID3D12Debug_EnableDebugLayer(pDebug);
            D3D12_OBJECT_RELEASE(pDebug);
            av_log(hwdev, AV_LOG_INFO, "D3D12 debug layer is enabled!\n");
        }
    }

    اگر (!ctx->device) {
        IDXGIFactory2 *pDXGIFactory = تہی;

        hr = priv->create_dxgi_factory2(create_flags, &IID_IDXGIFactory2, (خالی **)&pDXGIFactory);
        اگر (SUCCEEDED(hr)) {
            صحیح adapter = device ? atoi(device) : 0;
            اگر (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = تہی;
            IDXGIFactory2_Release(pDXGIFactory);
        }

        اگر (pAdapter) {
            DXGI_ADAPTER_DESC desc;
            hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
            اگر (!FAILED(hr)) {
                av_log(hwdev, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                       desc.VendorId, desc.DeviceId, desc.Description);
            }
        }

        hr = priv->create_device((IUnknown *)pAdapter, D3D_FEATURE_LEVEL_12_0, &IID_ID3D12Device, (خالی **)&ctx->device);
        D3D12_OBJECT_RELEASE(pAdapter);
        اگر (FAILED(hr)) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create Direct 3D 12 device (%lx)\n", (طویل)hr);
            واپس AVERROR_UNKNOWN;
        }
    }

    اگر (av_dict_get(opts, "UAV", تہی, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    اگر (av_dict_get(opts, "RTV", تہی, 0))
        ctx->resource_flags |= D3_D12_RESOURCE_FLAG_ALLOW_RENDER_ہدف;

    اگر (av_dict_get(opts, "SHARED", تہی, 0))
        ctx->ڈھیر_flags |= D3_D12_ڈھیر_FLAG_SHARED;

    واپس 0;
}

ثابت HWContextType ff_hwcontext_type_d3d12va = {
    .type                   = AV_HWDEVICE_TYPE_D3D12VA,
    .name                   = "D3D12VA",

    .device_hwctx_سائز      = حجم(D3D12VADevicePriv),
    .چوکھٹے_hwctx_سائز      = حجم(D3D12VAFramesContext),

    .device_create          = d3d12va_device_create,
    .device_init            = d3d12va_device_init,
    .device_uninit          = d3d12va_device_uninit,
    .چوکھٹے_get_constraints = d3d12va_چوکھٹے_get_constraints,
    .چوکھٹے_init            = d3d12va_چوکھٹے_init,
    .چوکھٹے_uninit          = d3d12va_چوکھٹے_uninit,
    .چوکھٹے_get_بفر      = d3d12va_get_بفر,
    .transfer_get_formats   = d3d12va_transfer_get_formats,
    .transfer_ڈیٹا_مقصد       = d3d12va_transfer_ڈیٹا,
    .transfer_ڈیٹا_from     = d3d12va_transfer_ڈیٹا,

    .pix_fmts               = (ثابت شمار AVPixelFormat[]){ AV_PIX_FMT_D3D12, AV_PIX_FMT_NONE },
};
