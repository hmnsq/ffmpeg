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

#ضمن "config.h"
#ضمن "common.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_internal.h"
#ضمن "hwcontext_d3d12va_internal.h"
#ضمن "hwcontext_d3d12va.h"
#ضمن "imgutils.h"
#ضمن "mem.h"
#ضمن "pixdesc.h"
#ضمن "pixfmt.h"
#ضمن "thread.h"
#ضمن "compat/w32dlfcn.h"
#ضمن <dxgi1_3.h>

تعريفنوع HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY2)(UINT Flags, REFIID riid, فراغ **ppFactory);

تعريفنوع بنية D3D12VAFramesContext {
    /**
     * The public AVD3D12VAFramesContext. See hwcontext_d3d12va.h for it.
     */
    AVD3D12VAFramesContext p;

    ID3D12Resource            *staging_download_میانگیر;
    ID3D12Resource            *staging_upload_میانگیر;
    ID3_D12_Command_صف        *command_صف;
    ID3D12CommandAllocator    *command_allocator;
    ID3D12GraphicsCommandList *command_list;
    AVD3D12VASyncContext       sync_ctx;
    UINT                       luma_component_اندازه;
    صحيح                        nb_surfaces_استفاده_شده;
} D3D12VAFramesContext;

تعريفنوع بنية D3D12VADevicePriv {
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

ساكن ثابت بنية {
    DXGI_FORMAT d3d_format;
    تعداد AVPixelFormat pix_fmt;
} supported_formats[] = {
    { DXGI_FORMAT_NV12, AV_PIX_FMT_NV12 },
    { DXGI_FORMAT_P010, AV_PIX_FMT_P010 },
    { DXGI_FORMAT_P016, AV_PIX_FMT_P012 },
};

ساكن فراغ d3d12va_default_قفل(فراغ *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

ساكن فراغ d3d12va_default_unlock(فراغ *ctx)
{
    ReleaseMutex(ctx);
}

ساكن صحيح d3d12va_fence_completion(AVD3D12VASyncContext *psync_ctx)
{
    uint64_t completion = ID3_D12_Fence_Get_Completed_مقدار(psync_ctx->fence);
    إذا (completion < psync_ctx->fence_مقدار) {
        إذا (FAILED(ID3_D12_Fence_مجموعه_Event_On_Completion(psync_ctx->fence, psync_ctx->fence_مقدار, psync_ctx->event)))
            أرجع AVERROR(EINVAL);

        WaitForSingleObjectEx(psync_ctx->event, INFINITE, FALSE);
    }

    أرجع 0;
}

ساكن مضمن صحيح d3d12va_wait_صف_idle(AVD3D12VASyncContext *psync_ctx, ID3_D12_Command_صف *command_صف)
{
    DX_CHECK(ID3_D12_Command_صف_Signal(command_صف, psync_ctx->fence, ++psync_ctx->fence_مقدار));
    أرجع d3d12va_fence_completion(psync_ctx);

fail:
    أرجع AVERROR(EINVAL);
}

ساكن صحيح d3d12va_create_staging_میانگیر_resource(AVHWFramesContext *ctx, D3_D12_RESOURCE_حالتها حالتها,
                                                  ID3D12Resource **ppResource, صحيح download)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    D3_D12_انباشته_PROPERTIES props = { .Type = download ? D3_D12_انباشته_TYPE_READBACK : D3_D12_انباشته_TYPE_UPLOAD };
    D3D12_RESOURCE_DESC desc = {
        .Dimension          = D3_D12_RESOURCE_DIMENSION_میانگیر,
        .Alignment          = 0,
        .عرض_2              = s->luma_component_اندازه + (s->luma_component_اندازه >> 1),
        .ارتفاع_2             = 1,
        .عمق_Or_Array_اندازه   = 1,
        .Mip_سطوح          = 1,
        .Format             = DXGI_FORMAT_UNKNOWN,
        .SampleDesc         = { .شمار_2 = 1, .Quality = 0 },
        .Layout             = D3_D12_TEXTURE_LAYOUT_ردیف_MAJOR,
        .Flags              = D3D12_RESOURCE_FLAG_NONE,
    };

    إذا (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, D3_D12_انباشته_FLAG_NONE, &desc,
        حالتها, عدم, &IID_ID3D12Resource, (فراغ **)ppResource))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging buffer resource\n");
        أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}

ساكن صحيح d3d12va_create_helper_objects(AVHWFramesContext *ctx)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *قابها_hwctx = &s->p;

    D3_D12_COMMAND_صف_DESC صف_desc = {
        .Type     = D3D12_COMMAND_LIST_TYPE_COPY,
        .اولویت = 0,
        .گره_ماسک = 0,
    };

    s->luma_component_اندازه = FFALIGN(ctx->عرض * (قابها_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                                     D3_D12_TEXTURE_داده_PITCH_ALIGNMENT) * ctx->ارتفاع;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (فراغ **)&s->sync_ctx.fence));

    s->sync_ctx.event = CreateEvent(عدم, FALSE, FALSE, عدم);
    إذا (!s->sync_ctx.event)
        اذهب fail;

    DX_CHECK(ID3_D12_Device_Create_Command_صف(device_hwctx->device, &صف_desc,
             &IID_ID3_D12_Command_صف, (فراغ **)&s->command_صف));

    DX_CHECK(ID3D12Device_CreateCommandAllocator(device_hwctx->device, صف_desc.Type,
             &IID_ID3D12CommandAllocator, (فراغ **)&s->command_allocator));

    DX_CHECK(ID3D12Device_CreateCommandList(device_hwctx->device, 0, صف_desc.Type,
             s->command_allocator, عدم, &IID_ID3D12GraphicsCommandList, (فراغ **)&s->command_list));

    DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

    ID3_D12_Command_صف_Execute_Command_Lists(s->command_صف, 1, (ID3D12CommandList **)&s->command_list);

    أرجع d3d12va_wait_صف_idle(&s->sync_ctx, s->command_صف);

fail:
    أرجع AVERROR(EINVAL);
}

ساكن فراغ d3d12va_قابها_uninit(AVHWFramesContext *ctx)
{
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;

    D3D12_OBJECT_RELEASE(s->sync_ctx.fence);
    إذا (s->sync_ctx.event)
        CloseHandle(s->sync_ctx.event);

    D3D12_OBJECT_RELEASE(s->staging_download_میانگیر);
    D3D12_OBJECT_RELEASE(s->staging_upload_میانگیر);
    D3D12_OBJECT_RELEASE(s->command_allocator);
    D3D12_OBJECT_RELEASE(s->command_list);
    D3D12_OBJECT_RELEASE(s->command_صف);

    إذا (hwctx->texture_array)
        D3D12_OBJECT_RELEASE(hwctx->texture_array);
}

ساكن صحيح d3d12va_قابها_get_constraints(AVHWDeviceContext *ctx, ثابت فراغ *hwconfig, AVHWFramesConstraints *constraints)
{
    HRESULT hr;
    صحيح nb_sw_formats = 0;
    AVD3D12VADeviceContext *device_hwctx = ctx->hwctx;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    إذا (!constraints->valid_sw_formats)
        أرجع AVERROR(ENOMEM);

    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        D3_D12_FEATURE_داده_FORMAT_SUPPORT format_support = { supported_formats[i].d3d_format };
        hr = ID3D12Device_CheckFeatureSupport(device_hwctx->device, D3D12_FEATURE_FORMAT_SUPPORT, &format_support, حجم(format_support));
        إذا (SUCCEEDED(hr) && (format_support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    إذا (!constraints->valid_hw_formats)
        أرجع AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D12;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    أرجع 0;
}

ساكن فراغ free_texture(فراغ *opaque, uint8_t *داده)
{
    AVD3D12VAFrame *قاب = (AVD3D12VAFrame *)داده;

    إذا (!(قاب->flags & AV_D3_D12_VA_قاب_FLAG_TEXTURE_ARRAY))
        D3D12_OBJECT_RELEASE(قاب->texture);

    D3D12_OBJECT_RELEASE(قاب->sync_ctx.fence);
    إذا (قاب->sync_ctx.event)
        CloseHandle(قاب->sync_ctx.event);

    av_freep(&داده);
}

ساكن AVBufferRef *d3d12va_pool_alloc_texture_array(AVHWFramesContext *ctx)
{
    AVD3D12VAFrame         *قاب  = av_mallocz(حجم(*قاب));
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    AVBufferRef *buf;

    قاب->flags |= AV_D3_D12_VA_قاب_FLAG_TEXTURE_ARRAY;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (فراغ **)&قاب->sync_ctx.fence));
    قاب->sync_ctx.event = CreateEvent(عدم, FALSE, FALSE, عدم);
    إذا (!قاب->sync_ctx.event)
        اذهب fail;

    إذا (s->nb_surfaces_استفاده_شده >= ctx->initial_pool_اندازه) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        اذهب fail;
    }

    قاب->texture = hwctx->texture_array;
    قاب->subresource_شاخص = s->nb_surfaces_استفاده_شده;

    buf = av_میانگیر_create((uint8_t *)قاب, حجم(*قاب), free_texture, عدم, 0);

    إذا (!buf)
        اذهب fail;

    s->nb_surfaces_استفاده_شده++;
    أرجع buf;
fail:
    free_texture(عدم, (uint8_t *)قاب);
    أرجع عدم;
}

ساكن AVBufferRef *d3d12va_pool_alloc(فراغ *opaque, size_t اندازه)
{
    AVHWFramesContext      *ctx          = (AVHWFramesContext *)opaque;
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    AVBufferRef *buf;
    AVD3D12VAFrame *قاب;

    إذا (ctx->initial_pool_اندازه > 0 && hwctx->flags & AV_D3_D12_VA_قاب_FLAG_TEXTURE_ARRAY)
        أرجع d3d12va_pool_alloc_texture_array(ctx);

    D3_D12_انباشته_PROPERTIES props = { .Type = D3_D12_انباشته_TYPE_DEFAULT };
    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .عرض_2            = ctx->عرض,
        .ارتفاع_2           = ctx->ارتفاع,
        .عمق_Or_Array_اندازه = 1,
        .Mip_سطوح        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.شمار_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    قاب = av_mallocz(حجم(AVD3D12VAFrame));
    إذا (!قاب)
        أرجع عدم;

    إذا (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->انباشته_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, عدم, &IID_ID3D12Resource, (فراغ **)&قاب->texture))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture\n");
        اذهب fail;
    }

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (فراغ **)&قاب->sync_ctx.fence));

    قاب->sync_ctx.event = CreateEvent(عدم, FALSE, FALSE, عدم);
    إذا (!قاب->sync_ctx.event)
        اذهب fail;

    buf = av_میانگیر_create((uint8_t *)قاب, حجم(*قاب), free_texture, عدم, 0);
    إذا (!buf)
        اذهب fail;

    أرجع buf;

fail:
    free_texture(عدم, (uint8_t *)قاب);
    أرجع عدم;
}

ساكن صحيح d3d12va_texture_array_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    D3_D12_انباشته_PROPERTIES props = { .Type = D3_D12_انباشته_TYPE_DEFAULT };

    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .عرض_2            = ctx->عرض,
        .ارتفاع_2           = ctx->ارتفاع,
        .عمق_Or_Array_اندازه = ctx->initial_pool_اندازه,
        .Mip_سطوح        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.شمار_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    إذا (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->انباشته_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, عدم, &IID_ID3D12Resource, (فراغ **)&hwctx->texture_array))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture array\n");
        أرجع AVERROR(EINVAL);
    }
    أرجع 0;
}

ساكن صحيح d3d12va_قابها_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        إذا (ctx->sw_format == supported_formats[i].pix_fmt) {
            إذا (hwctx->format != DXGI_FORMAT_UNKNOWN &&
                hwctx->format != supported_formats[i].d3d_format)
                av_log(ctx, AV_LOG_WARNING, "Incompatible DXGI format provided by user, will be overided\n");
            hwctx->format = supported_formats[i].d3d_format;
            اكسر;
        }
    }

    إذا (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        أرجع AVERROR(EINVAL);
    }

    hwctx->resource_flags |= device_hwctx->resource_flags;
    hwctx->انباشته_flags     |= device_hwctx->انباشته_flags;

    إذا (ctx->initial_pool_اندازه > 0 && hwctx->flags & AV_D3_D12_VA_قاب_FLAG_TEXTURE_ARRAY) {
        صحيح err = d3d12va_texture_array_init(ctx);
        إذا (err < 0)
            أرجع err;
    }

    ffhwframesctx(ctx)->pool_داخلی = av_میانگیر_pool_init2(حجم(AVD3D12VAFrame),
        ctx, d3d12va_pool_alloc, عدم);

    إذا (!ffhwframesctx(ctx)->pool_داخلی)
        أرجع AVERROR(ENOMEM);

    أرجع 0;
}

ساكن صحيح d3d12va_get_میانگیر(AVHWFramesContext *ctx, AVFrame *قاب)
{
    صحيح ret;

    قاب->buf[0] = av_میانگیر_pool_get(ctx->pool);
    إذا (!قاب->buf[0])
        أرجع AVERROR(ENOMEM);

    ret = av_image_fill_arrays(قاب->داده, قاب->linesize, عدم,
                               ctx->sw_format, ctx->عرض, ctx->ارتفاع,
                               D3_D12_TEXTURE_داده_PITCH_ALIGNMENT);
    إذا (ret < 0)
        أرجع ret;

    قاب->داده[0] = قاب->buf[0]->داده;
    قاب->format  = AV_PIX_FMT_D3D12;
    قاب->عرض   = ctx->عرض;
    قاب->ارتفاع  = ctx->ارتفاع;

    أرجع 0;
}

ساكن صحيح d3d12va_transfer_get_formats(AVHWFramesContext *ctx,
                                        تعداد AVHWFrameTransferDirection dir,
                                        تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    إذا (!fmts)
        أرجع AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    أرجع 0;
}

ساكن صحيح d3d12va_transfer_داده(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    AVD3D12VADeviceContext *hwctx        = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *قابها_hwctx = &s->p;

    صحيح ret;
    صحيح download = src->format == AV_PIX_FMT_D3D12;
    ثابت AVFrame *قاب = download ? src : dst;
    ثابت AVFrame *other = download ? dst : src;

    AVD3D12VAFrame *f = (AVD3D12VAFrame *)قاب->داده[0];
    ID3D12Resource *texture = (ID3D12Resource *)f->texture;

    uint8_t *mapped_داده;
    uint8_t *داده[4];
    صحيح linesizes[4];

    D3D12_TEXTURE_COPY_LOCATION staging_y_location  = { 0 };
    D3D12_TEXTURE_COPY_LOCATION staging_uv_location = { 0 };

    D3D12_TEXTURE_COPY_LOCATION texture_y_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_شاخص,
        .Subresource_شاخص = 0,
    };

    D3D12_TEXTURE_COPY_LOCATION texture_uv_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_شاخص,
        .Subresource_شاخص = 1,
    };

    D3D12_RESOURCE_BARRIER barrier = {
        .Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
        .Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
        .Transition = {
            .pResource   = texture,
            .StateBefore = D3D12_RESOURCE_STATE_COMMON,
            .StateAfter  = download ? D3_D12_RESOURCE_STATE_COPY_منبع : D3D12_RESOURCE_STATE_COPY_DEST,
            .Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
        },
    };

    إذا (قاب->hw_قابها_ctx->داده != (uint8_t *)ctx || other->format != ctx->sw_format)
        أرجع AVERROR(EINVAL);

    hwctx->قفل_2(hwctx->قفل_ctx);

    إذا (!s->command_صف) {
        ret = d3d12va_create_helper_objects(ctx);
        إذا (ret < 0)
            اذهب fail;
    }

    لكل (صحيح i = 0; i < 4; i++)
        linesizes[i] = FFALIGN(قاب->عرض * (قابها_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                               D3_D12_TEXTURE_داده_PITCH_ALIGNMENT);

    staging_y_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .جابه_جایی_4 = 0,
            .Footprint = {
                .Format   = قابها_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16_UNORM : DXGI_FORMAT_R8_UNORM,
                .عرض_2    = ctx->عرض,
                .ارتفاع_2   = ctx->ارتفاع,
                .عمق_2    = 1,
                .ردیف_Pitch = linesizes[0],
            },
        },
    };

    staging_uv_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .جابه_جایی_4 = s->luma_component_اندازه,
            .Footprint = {
                .Format   = قابها_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16G16_UNORM : DXGI_FORMAT_R8G8_UNORM,
                .عرض_2    = ctx->عرض  >> 1,
                .ارتفاع_2   = ctx->ارتفاع >> 1,
                .عمق_2    = 1,
                .ردیف_Pitch = linesizes[0],
            },
        },
    };

    DX_CHECK(ID3D12CommandAllocator_Reset(s->command_allocator));

    DX_CHECK(ID3D12GraphicsCommandList_Reset(s->command_list, s->command_allocator, عدم));

    إذا (download) {
        إذا (!s->staging_download_میانگیر) {
            ret = d3d12va_create_staging_میانگیر_resource(ctx, D3D12_RESOURCE_STATE_COPY_DEST,
                                                         &s->staging_download_میانگیر, 1);
            إذا (ret < 0) {
                اذهب fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_download_میانگیر;

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_y_location, 0, 0, 0,
                                                    &texture_y_location, عدم);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_uv_location, 0, 0, 0,
                                                    &texture_uv_location, عدم);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        DX_CHECK(ID3_D12_Command_صف_Wait(s->command_صف, f->sync_ctx.fence, f->sync_ctx.fence_مقدار));

        ID3_D12_Command_صف_Execute_Command_Lists(s->command_صف, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_صف_idle(&s->sync_ctx, s->command_صف);
        إذا (ret < 0)
            اذهب fail;

        DX_CHECK(ID3D12Resource_Map(s->staging_download_میانگیر, 0, عدم, (فراغ **)&mapped_داده));
        av_image_fill_اشارهگرها(داده, ctx->sw_format, ctx->ارتفاع, mapped_داده, linesizes);

        av_image_copy2(dst->داده, dst->linesize, داده, linesizes,
                       ctx->sw_format, ctx->عرض, ctx->ارتفاع);

        ID3D12Resource_Unmap(s->staging_download_میانگیر, 0, عدم);
    } وإلا {
        إذا (!s->staging_upload_میانگیر) {
            ret = d3d12va_create_staging_میانگیر_resource(ctx, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                        &s->staging_upload_میانگیر, 0);
            إذا (ret < 0) {
                اذهب fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_upload_میانگیر;

        DX_CHECK(ID3D12Resource_Map(s->staging_upload_میانگیر, 0, عدم, (فراغ **)&mapped_داده));
        av_image_fill_اشارهگرها(داده, ctx->sw_format, ctx->ارتفاع, mapped_داده, linesizes);

        av_image_copy2(داده, linesizes, src->داده, src->linesize,
                       ctx->sw_format, ctx->عرض, ctx->ارتفاع);

        ID3D12Resource_Unmap(s->staging_upload_میانگیر, 0, عدم);

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_y_location, 0, 0, 0,
                                                    &staging_y_location, عدم);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_uv_location, 0, 0, 0,
                                                    &staging_uv_location, عدم);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        ID3_D12_Command_صف_Execute_Command_Lists(s->command_صف, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_صف_idle(&s->sync_ctx, s->command_صف);
        إذا (ret < 0)
            اذهب fail;
    }

    hwctx->unlock(hwctx->قفل_ctx);

    أرجع 0;

fail:
    hwctx->unlock(hwctx->قفل_ctx);
    أرجع AVERROR(EINVAL);
}

ساكن صحيح d3d12va_بارگیری_functions(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv *priv = hwdev->hwctx;

#إذا !HAVE_UWP
    priv->d3d12lib = dlopen("d3d12.dll", 0);
    priv->dxgilib  = dlopen("dxgi.dll", 0);

    إذا (!priv->d3d12lib || !priv->dxgilib)
        اذهب fail;

    priv->create_device = (PFN_D3D12_CREATE_DEVICE)Get_Proc_آدرس(priv->d3d12lib, "D3D12CreateDevice");
    إذا (!priv->create_device)
        اذهب fail;

    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2)Get_Proc_آدرس(priv->dxgilib, "CreateDXGIFactory2");
    إذا (!priv->create_dxgi_factory2)
        اذهب fail;

    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE)Get_Proc_آدرس(priv->d3d12lib, "D3D12GetDebugInterface");
#وإلا
    priv->create_device        = (PFN_D3D12_CREATE_DEVICE) D3D12CreateDevice;
    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2) CreateDXGIFactory2;
    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE) D3D12GetDebugInterface;
#پایان_اگر
    أرجع 0;

#إذا !HAVE_UWP
fail:
    av_log(hwdev, AV_LOG_ERROR, "Failed to load D3D12 library or its functions\n");
    أرجع AVERROR_UNKNOWN;
#پایان_اگر
}

ساكن فراغ d3d12va_device_free(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    D3D12_OBJECT_RELEASE(ctx->device);

    إذا (priv->d3d12lib)
        dlclose(priv->d3d12lib);

    إذا (priv->dxgilib)
        dlclose(priv->dxgilib);
}

ساكن صحيح d3d12va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *ctx = hwdev->hwctx;

    إذا (!ctx->قفل_2) {
        ctx->قفل_ctx = CreateMutex(عدم, 0, عدم);
        إذا (ctx->قفل_ctx == INVALID_HANDLE_مقدار) {
            av_log(عدم, AV_LOG_ERROR, "Failed to create a mutex\n");
            أرجع AVERROR(EINVAL);
        }
        ctx->قفل_2   = d3d12va_default_قفل;
        ctx->unlock = d3d12va_default_unlock;
    }

    إذا (!ctx->video_device)
        DX_CHECK(ID3D12Device_QueryInterface(ctx->device, &IID_ID3D12VideoDevice, (فراغ **)&ctx->video_device));

    أرجع 0;

fail:
    أرجع AVERROR(EINVAL);
}

ساكن فراغ d3d12va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *device_hwctx = hwdev->hwctx;

    D3D12_OBJECT_RELEASE(device_hwctx->video_device);

    إذا (device_hwctx->قفل_2 == d3d12va_default_قفل) {
        CloseHandle(device_hwctx->قفل_ctx);
        device_hwctx->قفل_ctx = INVALID_HANDLE_مقدار;
        device_hwctx->قفل_2 = عدم;
    }
}

ساكن صحيح d3d12va_device_create(AVHWDeviceContext *hwdev, ثابت حرف *device,
                                 AVDictionary *opts, صحيح flags)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    HRESULT hr;
    UINT create_flags = 0;
    IDXGIAdapter *pAdapter = عدم;

    صحيح ret;
    صحيح is_debug = !!av_dict_get(opts, "debug", عدم, 0);

    hwdev->حرر = d3d12va_device_free;

    ret = d3d12va_بارگیری_functions(hwdev);
    إذا (ret < 0)
        أرجع ret;

    إذا (is_debug) {
        ID3D12Debug *pDebug;
        إذا (priv->get_debug_interface && SUCCEEDED(priv->get_debug_interface(&IID_ID3D12Debug, (فراغ **)&pDebug))) {
            create_flags |= DXGI_CREATE_FACTORY_DEBUG;
            ID3D12Debug_EnableDebugLayer(pDebug);
            D3D12_OBJECT_RELEASE(pDebug);
            av_log(hwdev, AV_LOG_INFO, "D3D12 debug layer is enabled!\n");
        }
    }

    إذا (!ctx->device) {
        IDXGIFactory2 *pDXGIFactory = عدم;

        hr = priv->create_dxgi_factory2(create_flags, &IID_IDXGIFactory2, (فراغ **)&pDXGIFactory);
        إذا (SUCCEEDED(hr)) {
            صحيح adapter = device ? atoi(device) : 0;
            إذا (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = عدم;
            IDXGIFactory2_Release(pDXGIFactory);
        }

        إذا (pAdapter) {
            DXGI_ADAPTER_DESC desc;
            hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
            إذا (!FAILED(hr)) {
                av_log(hwdev, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                       desc.VendorId, desc.DeviceId, desc.Description);
            }
        }

        hr = priv->create_device((IUnknown *)pAdapter, D3D_FEATURE_LEVEL_12_0, &IID_ID3D12Device, (فراغ **)&ctx->device);
        D3D12_OBJECT_RELEASE(pAdapter);
        إذا (FAILED(hr)) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create Direct 3D 12 device (%lx)\n", (دراز)hr);
            أرجع AVERROR_UNKNOWN;
        }
    }

    إذا (av_dict_get(opts, "UAV", عدم, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    إذا (av_dict_get(opts, "RTV", عدم, 0))
        ctx->resource_flags |= D3_D12_RESOURCE_FLAG_ALLOW_RENDER_هدف;

    إذا (av_dict_get(opts, "SHARED", عدم, 0))
        ctx->انباشته_flags |= D3_D12_انباشته_FLAG_SHARED;

    أرجع 0;
}

ثابت HWContextType ff_hwcontext_type_d3d12va = {
    .type                   = AV_HWDEVICE_TYPE_D3D12VA,
    .name                   = "D3D12VA",

    .device_hwctx_اندازه      = حجم(D3D12VADevicePriv),
    .قابها_hwctx_اندازه      = حجم(D3D12VAFramesContext),

    .device_create          = d3d12va_device_create,
    .device_init            = d3d12va_device_init,
    .device_uninit          = d3d12va_device_uninit,
    .قابها_get_constraints = d3d12va_قابها_get_constraints,
    .قابها_init            = d3d12va_قابها_init,
    .قابها_uninit          = d3d12va_قابها_uninit,
    .قابها_get_میانگیر      = d3d12va_get_میانگیر,
    .transfer_get_formats   = d3d12va_transfer_get_formats,
    .transfer_داده_مقصد       = d3d12va_transfer_داده,
    .transfer_داده_from     = d3d12va_transfer_داده,

    .pix_fmts               = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_D3D12, AV_PIX_FMT_NONE },
};
