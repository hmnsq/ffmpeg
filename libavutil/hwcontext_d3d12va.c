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

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "hwcontext.h"
#অন্তর্ভাব "hwcontext_internal.h"
#অন্তর্ভাব "hwcontext_d3d12va_internal.h"
#অন্তর্ভাব "hwcontext_d3d12va.h"
#অন্তর্ভাব "imgutils.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "pixdesc.h"
#অন্তর্ভাব "pixfmt.h"
#অন্তর্ভাব "thread.h"
#অন্তর্ভাব "compat/w32dlfcn.h"
#অন্তর্ভাব <dxgi1_3.h>

প্রকারলেখ HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY2)(UINT Flags, REFIID riid, শূন্য **ppFactory);

প্রকারলেখ কাঠামো D3D12VAFramesContext {
    /**
     * The public AVD3D12VAFramesContext. See hwcontext_d3d12va.h for it.
     */
    AVD3D12VAFramesContext p;

    ID3D12Resource            *staging_download_বাফার;
    ID3D12Resource            *staging_upload_বাফার;
    ID3D12CommandQueue        *command_queue;
    ID3D12CommandAllocator    *command_allocator;
    ID3D12GraphicsCommandList *command_list;
    AVD3D12VASyncContext       sync_ctx;
    UINT                       luma_component_আকার;
    পূর্ণসংখ্যা                        nb_surfaces_used;
} D3D12VAFramesContext;

প্রকারলেখ কাঠামো D3D12VADevicePriv {
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

স্থির ধ্রুবক কাঠামো {
    DXGI_FORMAT d3d_format;
    গণনা AVPixelFormat pix_fmt;
} supported_formats[] = {
    { DXGI_FORMAT_NV12, AV_PIX_FMT_NV12 },
    { DXGI_FORMAT_P010, AV_PIX_FMT_P010 },
    { DXGI_FORMAT_P016, AV_PIX_FMT_P012 },
};

স্থির শূন্য d3d12va_default_lock(শূন্য *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

স্থির শূন্য d3d12va_default_unlock(শূন্য *ctx)
{
    ReleaseMutex(ctx);
}

স্থির পূর্ণসংখ্যা d3d12va_fence_completion(AVD3D12VASyncContext *psync_ctx)
{
    uint64_t completion = ID3_D12_Fence_Get_Completed_মান(psync_ctx->fence);
    যদি (completion < psync_ctx->fence_মান) {
        যদি (FAILED(ID3D12Fence_SetEventOnCompletion(psync_ctx->fence, psync_ctx->fence_মান, psync_ctx->event)))
            ফেরত AVERROR(EINVAL);

        WaitForSingleObjectEx(psync_ctx->event, INFINITE, FALSE);
    }

    ফেরত 0;
}

স্থির অন্তঃরেখ পূর্ণসংখ্যা d3d12va_wait_queue_idle(AVD3D12VASyncContext *psync_ctx, ID3D12CommandQueue *command_queue)
{
    DX_CHECK(ID3D12CommandQueue_Signal(command_queue, psync_ctx->fence, ++psync_ctx->fence_মান));
    ফেরত d3d12va_fence_completion(psync_ctx);

fail:
    ফেরত AVERROR(EINVAL);
}

স্থির পূর্ণসংখ্যা d3d12va_create_staging_বাফার_resource(AVHWFramesContext *ctx, D3D12_RESOURCE_STATES states,
                                                  ID3D12Resource **ppResource, পূর্ণসংখ্যা download)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    D3D12_HEAP_PROPERTIES props = { .Type = download ? D3D12_HEAP_TYPE_READBACK : D3D12_HEAP_TYPE_UPLOAD };
    D3D12_RESOURCE_DESC desc = {
        .Dimension          = D3_D12_RESOURCE_DIMENSION_বাফার,
        .Alignment          = 0,
        .Width              = s->luma_component_আকার + (s->luma_component_আকার >> 1),
        .Height             = 1,
        .Depth_Or_Array_আকার   = 1,
        .MipLevels          = 1,
        .Format             = DXGI_FORMAT_UNKNOWN,
        .SampleDesc         = { .গুনতি_2 = 1, .Quality = 0 },
        .Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
        .Flags              = D3D12_RESOURCE_FLAG_NONE,
    };

    যদি (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, D3D12_HEAP_FLAG_NONE, &desc,
        states, ফাঁকা, &IID_ID3D12Resource, (শূন্য **)ppResource))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging buffer resource\n");
        ফেরত AVERROR_UNKNOWN;
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা d3d12va_create_helper_objects(AVHWFramesContext *ctx)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *frames_hwctx = &s->p;

    D3D12_COMMAND_QUEUE_DESC queue_desc = {
        .Type     = D3D12_COMMAND_LIST_TYPE_COPY,
        .Priority = 0,
        .গ্রন্থি_Mask = 0,
    };

    s->luma_component_আকার = FFALIGN(ctx->width * (frames_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                                     D3_D12_TEXTURE_তথ্য_PITCH_ALIGNMENT) * ctx->height;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (শূন্য **)&s->sync_ctx.fence));

    s->sync_ctx.event = CreateEvent(ফাঁকা, FALSE, FALSE, ফাঁকা);
    যদি (!s->sync_ctx.event)
        যাও fail;

    DX_CHECK(ID3D12Device_CreateCommandQueue(device_hwctx->device, &queue_desc,
             &IID_ID3D12CommandQueue, (শূন্য **)&s->command_queue));

    DX_CHECK(ID3D12Device_CreateCommandAllocator(device_hwctx->device, queue_desc.Type,
             &IID_ID3D12CommandAllocator, (শূন্য **)&s->command_allocator));

    DX_CHECK(ID3D12Device_CreateCommandList(device_hwctx->device, 0, queue_desc.Type,
             s->command_allocator, ফাঁকা, &IID_ID3D12GraphicsCommandList, (শূন্য **)&s->command_list));

    DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

    ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

    ফেরত d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);

fail:
    ফেরত AVERROR(EINVAL);
}

স্থির শূন্য d3d12va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;

    D3D12_OBJECT_RELEASE(s->sync_ctx.fence);
    যদি (s->sync_ctx.event)
        CloseHandle(s->sync_ctx.event);

    D3D12_OBJECT_RELEASE(s->staging_download_বাফার);
    D3D12_OBJECT_RELEASE(s->staging_upload_বাফার);
    D3D12_OBJECT_RELEASE(s->command_allocator);
    D3D12_OBJECT_RELEASE(s->command_list);
    D3D12_OBJECT_RELEASE(s->command_queue);

    যদি (hwctx->texture_array)
        D3D12_OBJECT_RELEASE(hwctx->texture_array);
}

স্থির পূর্ণসংখ্যা d3d12va_frames_get_constraints(AVHWDeviceContext *ctx, ধ্রুবক শূন্য *hwconfig, AVHWFramesConstraints *constraints)
{
    HRESULT hr;
    পূর্ণসংখ্যা nb_sw_formats = 0;
    AVD3D12VADeviceContext *device_hwctx = ctx->hwctx;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    আকার(*constraints->valid_sw_formats));
    যদি (!constraints->valid_sw_formats)
        ফেরত AVERROR(ENOMEM);

    জন্য (পূর্ণসংখ্যা i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        D3_D12_FEATURE_তথ্য_FORMAT_SUPPORT format_support = { supported_formats[i].d3d_format };
        hr = ID3D12Device_CheckFeatureSupport(device_hwctx->device, D3D12_FEATURE_FORMAT_SUPPORT, &format_support, আকার(format_support));
        যদি (SUCCEEDED(hr) && (format_support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, আকার(*constraints->valid_hw_formats));
    যদি (!constraints->valid_hw_formats)
        ফেরত AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D12;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ফেরত 0;
}

স্থির শূন্য free_texture(শূন্য *opaque, uint8_t *তথ্য)
{
    AVD3D12VAFrame *frame = (AVD3D12VAFrame *)তথ্য;

    যদি (!(frame->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY))
        D3D12_OBJECT_RELEASE(frame->texture);

    D3D12_OBJECT_RELEASE(frame->sync_ctx.fence);
    যদি (frame->sync_ctx.event)
        CloseHandle(frame->sync_ctx.event);

    av_freep(&তথ্য);
}

স্থির AVBufferRef *d3d12va_pool_alloc_texture_array(AVHWFramesContext *ctx)
{
    AVD3D12VAFrame         *frame  = av_mallocz(আকার(*frame));
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    AVBufferRef *buf;

    frame->flags |= AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (শূন্য **)&frame->sync_ctx.fence));
    frame->sync_ctx.event = CreateEvent(ফাঁকা, FALSE, FALSE, ফাঁকা);
    যদি (!frame->sync_ctx.event)
        যাও fail;

    যদি (s->nb_surfaces_used >= ctx->initial_pool_আকার) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        যাও fail;
    }

    frame->texture = hwctx->texture_array;
    frame->subresource_সূচক = s->nb_surfaces_used;

    buf = av_বাফার_create((uint8_t *)frame, আকার(*frame), free_texture, ফাঁকা, 0);

    যদি (!buf)
        যাও fail;

    s->nb_surfaces_used++;
    ফেরত buf;
fail:
    free_texture(ফাঁকা, (uint8_t *)frame);
    ফেরত ফাঁকা;
}

স্থির AVBufferRef *d3d12va_pool_alloc(শূন্য *opaque, size_t আকার_2)
{
    AVHWFramesContext      *ctx          = (AVHWFramesContext *)opaque;
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    AVBufferRef *buf;
    AVD3D12VAFrame *frame;

    যদি (ctx->initial_pool_আকার > 0 && hwctx->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY)
        ফেরত d3d12va_pool_alloc_texture_array(ctx);

    D3D12_HEAP_PROPERTIES props = { .Type = D3D12_HEAP_TYPE_DEFAULT };
    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .Width            = ctx->width,
        .Height           = ctx->height,
        .Depth_Or_Array_আকার = 1,
        .MipLevels        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.গুনতি_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    frame = av_mallocz(আকার(AVD3D12VAFrame));
    যদি (!frame)
        ফেরত ফাঁকা;

    যদি (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->heap_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, ফাঁকা, &IID_ID3D12Resource, (শূন্য **)&frame->texture))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture\n");
        যাও fail;
    }

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (শূন্য **)&frame->sync_ctx.fence));

    frame->sync_ctx.event = CreateEvent(ফাঁকা, FALSE, FALSE, ফাঁকা);
    যদি (!frame->sync_ctx.event)
        যাও fail;

    buf = av_বাফার_create((uint8_t *)frame, আকার(*frame), free_texture, ফাঁকা, 0);
    যদি (!buf)
        যাও fail;

    ফেরত buf;

fail:
    free_texture(ফাঁকা, (uint8_t *)frame);
    ফেরত ফাঁকা;
}

স্থির পূর্ণসংখ্যা d3d12va_texture_array_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    D3D12_HEAP_PROPERTIES props = { .Type = D3D12_HEAP_TYPE_DEFAULT };

    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .Width            = ctx->width,
        .Height           = ctx->height,
        .Depth_Or_Array_আকার = ctx->initial_pool_আকার,
        .MipLevels        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.গুনতি_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    যদি (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->heap_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, ফাঁকা, &IID_ID3D12Resource, (শূন্য **)&hwctx->texture_array))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture array\n");
        ফেরত AVERROR(EINVAL);
    }
    ফেরত 0;
}

স্থির পূর্ণসংখ্যা d3d12va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        যদি (ctx->sw_format == supported_formats[i].pix_fmt) {
            যদি (hwctx->format != DXGI_FORMAT_UNKNOWN &&
                hwctx->format != supported_formats[i].d3d_format)
                av_log(ctx, AV_LOG_WARNING, "Incompatible DXGI format provided by user, will be overided\n");
            hwctx->format = supported_formats[i].d3d_format;
            বিরতি;
        }
    }

    যদি (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ফেরত AVERROR(EINVAL);
    }

    hwctx->resource_flags |= device_hwctx->resource_flags;
    hwctx->heap_flags     |= device_hwctx->heap_flags;

    যদি (ctx->initial_pool_আকার > 0 && hwctx->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY) {
        পূর্ণসংখ্যা err = d3d12va_texture_array_init(ctx);
        যদি (err < 0)
            ফেরত err;
    }

    ffhwframesctx(ctx)->pool_internal = av_বাফার_pool_init2(আকার(AVD3D12VAFrame),
        ctx, d3d12va_pool_alloc, ফাঁকা);

    যদি (!ffhwframesctx(ctx)->pool_internal)
        ফেরত AVERROR(ENOMEM);

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা d3d12va_get_বাফার(AVHWFramesContext *ctx, AVFrame *frame)
{
    পূর্ণসংখ্যা ret;

    frame->buf[0] = av_বাফার_pool_get(ctx->pool);
    যদি (!frame->buf[0])
        ফেরত AVERROR(ENOMEM);

    ret = av_image_fill_arrays(frame->তথ্য, frame->linesize, ফাঁকা,
                               ctx->sw_format, ctx->width, ctx->height,
                               D3_D12_TEXTURE_তথ্য_PITCH_ALIGNMENT);
    যদি (ret < 0)
        ফেরত ret;

    frame->তথ্য[0] = frame->buf[0]->তথ্য;
    frame->format  = AV_PIX_FMT_D3D12;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা d3d12va_transfer_get_formats(AVHWFramesContext *ctx,
                                        গণনা AVHWFrameTransferDirection dir,
                                        গণনা AVPixelFormat **formats)
{
    গণনা AVPixelFormat *fmts;

    fmts = av_malloc_array(2, আকার(*fmts));
    যদি (!fmts)
        ফেরত AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা d3d12va_transfer_তথ্য(AVHWFramesContext *ctx, AVFrame *dst,
                                 ধ্রুবক AVFrame *src)
{
    AVD3D12VADeviceContext *hwctx        = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *frames_hwctx = &s->p;

    পূর্ণসংখ্যা ret;
    পূর্ণসংখ্যা download = src->format == AV_PIX_FMT_D3D12;
    ধ্রুবক AVFrame *frame = download ? src : dst;
    ধ্রুবক AVFrame *other = download ? dst : src;

    AVD3D12VAFrame *f = (AVD3D12VAFrame *)frame->তথ্য[0];
    ID3D12Resource *texture = (ID3D12Resource *)f->texture;

    uint8_t *mapped_তথ্য;
    uint8_t *তথ্য[4];
    পূর্ণসংখ্যা linesizes[4];

    D3D12_TEXTURE_COPY_LOCATION staging_y_location  = { 0 };
    D3D12_TEXTURE_COPY_LOCATION staging_uv_location = { 0 };

    D3D12_TEXTURE_COPY_LOCATION texture_y_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_সূচক,
        .Subresource_সূচক = 0,
    };

    D3D12_TEXTURE_COPY_LOCATION texture_uv_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_সূচক,
        .Subresource_সূচক = 1,
    };

    D3D12_RESOURCE_BARRIER barrier = {
        .Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
        .Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
        .Transition = {
            .pResource   = texture,
            .StateBefore = D3D12_RESOURCE_STATE_COMMON,
            .StateAfter  = download ? D3D12_RESOURCE_STATE_COPY_SOURCE : D3D12_RESOURCE_STATE_COPY_DEST,
            .Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
        },
    };

    যদি (frame->hw_frames_ctx->তথ্য != (uint8_t *)ctx || other->format != ctx->sw_format)
        ফেরত AVERROR(EINVAL);

    hwctx->lock(hwctx->lock_ctx);

    যদি (!s->command_queue) {
        ret = d3d12va_create_helper_objects(ctx);
        যদি (ret < 0)
            যাও fail;
    }

    জন্য (পূর্ণসংখ্যা i = 0; i < 4; i++)
        linesizes[i] = FFALIGN(frame->width * (frames_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                               D3_D12_TEXTURE_তথ্য_PITCH_ALIGNMENT);

    staging_y_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .Offset = 0,
            .Footprint = {
                .Format   = frames_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16_UNORM : DXGI_FORMAT_R8_UNORM,
                .Width    = ctx->width,
                .Height   = ctx->height,
                .Depth    = 1,
                .RowPitch = linesizes[0],
            },
        },
    };

    staging_uv_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .Offset = s->luma_component_আকার,
            .Footprint = {
                .Format   = frames_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16G16_UNORM : DXGI_FORMAT_R8G8_UNORM,
                .Width    = ctx->width  >> 1,
                .Height   = ctx->height >> 1,
                .Depth    = 1,
                .RowPitch = linesizes[0],
            },
        },
    };

    DX_CHECK(ID3D12CommandAllocator_Reset(s->command_allocator));

    DX_CHECK(ID3D12GraphicsCommandList_Reset(s->command_list, s->command_allocator, ফাঁকা));

    যদি (download) {
        যদি (!s->staging_download_বাফার) {
            ret = d3d12va_create_staging_বাফার_resource(ctx, D3D12_RESOURCE_STATE_COPY_DEST,
                                                         &s->staging_download_বাফার, 1);
            যদি (ret < 0) {
                যাও fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_download_বাফার;

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_y_location, 0, 0, 0,
                                                    &texture_y_location, ফাঁকা);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_uv_location, 0, 0, 0,
                                                    &texture_uv_location, ফাঁকা);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        DX_CHECK(ID3D12CommandQueue_Wait(s->command_queue, f->sync_ctx.fence, f->sync_ctx.fence_মান));

        ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);
        যদি (ret < 0)
            যাও fail;

        DX_CHECK(ID3D12Resource_Map(s->staging_download_বাফার, 0, ফাঁকা, (শূন্য **)&mapped_তথ্য));
        av_image_fill_pointers(তথ্য, ctx->sw_format, ctx->height, mapped_তথ্য, linesizes);

        av_image_copy2(dst->তথ্য, dst->linesize, তথ্য, linesizes,
                       ctx->sw_format, ctx->width, ctx->height);

        ID3D12Resource_Unmap(s->staging_download_বাফার, 0, ফাঁকা);
    } অন্যথা {
        যদি (!s->staging_upload_বাফার) {
            ret = d3d12va_create_staging_বাফার_resource(ctx, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                        &s->staging_upload_বাফার, 0);
            যদি (ret < 0) {
                যাও fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_upload_বাফার;

        DX_CHECK(ID3D12Resource_Map(s->staging_upload_বাফার, 0, ফাঁকা, (শূন্য **)&mapped_তথ্য));
        av_image_fill_pointers(তথ্য, ctx->sw_format, ctx->height, mapped_তথ্য, linesizes);

        av_image_copy2(তথ্য, linesizes, src->তথ্য, src->linesize,
                       ctx->sw_format, ctx->width, ctx->height);

        ID3D12Resource_Unmap(s->staging_upload_বাফার, 0, ফাঁকা);

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_y_location, 0, 0, 0,
                                                    &staging_y_location, ফাঁকা);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_uv_location, 0, 0, 0,
                                                    &staging_uv_location, ফাঁকা);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);
        যদি (ret < 0)
            যাও fail;
    }

    hwctx->unlock(hwctx->lock_ctx);

    ফেরত 0;

fail:
    hwctx->unlock(hwctx->lock_ctx);
    ফেরত AVERROR(EINVAL);
}

স্থির পূর্ণসংখ্যা d3d12va_load_functions(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv *priv = hwdev->hwctx;

#যদি !HAVE_UWP
    priv->d3d12lib = dlopen("d3d12.dll", 0);
    priv->dxgilib  = dlopen("dxgi.dll", 0);

    যদি (!priv->d3d12lib || !priv->dxgilib)
        যাও fail;

    priv->create_device = (PFN_D3D12_CREATE_DEVICE)GetProcAddress(priv->d3d12lib, "D3D12CreateDevice");
    যদি (!priv->create_device)
        যাও fail;

    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2)GetProcAddress(priv->dxgilib, "CreateDXGIFactory2");
    যদি (!priv->create_dxgi_factory2)
        যাও fail;

    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE)GetProcAddress(priv->d3d12lib, "D3D12GetDebugInterface");
#অন্যথা
    priv->create_device        = (PFN_D3D12_CREATE_DEVICE) D3D12CreateDevice;
    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2) CreateDXGIFactory2;
    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE) D3D12GetDebugInterface;
#endif
    ফেরত 0;

#যদি !HAVE_UWP
fail:
    av_log(hwdev, AV_LOG_ERROR, "Failed to load D3D12 library or its functions\n");
    ফেরত AVERROR_UNKNOWN;
#endif
}

স্থির শূন্য d3d12va_device_free(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    D3D12_OBJECT_RELEASE(ctx->device);

    যদি (priv->d3d12lib)
        dlclose(priv->d3d12lib);

    যদি (priv->dxgilib)
        dlclose(priv->dxgilib);
}

স্থির পূর্ণসংখ্যা d3d12va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *ctx = hwdev->hwctx;

    যদি (!ctx->lock) {
        ctx->lock_ctx = CreateMutex(ফাঁকা, 0, ফাঁকা);
        যদি (ctx->lock_ctx == INVALID_HANDLE_মান) {
            av_log(ফাঁকা, AV_LOG_ERROR, "Failed to create a mutex\n");
            ফেরত AVERROR(EINVAL);
        }
        ctx->lock   = d3d12va_default_lock;
        ctx->unlock = d3d12va_default_unlock;
    }

    যদি (!ctx->video_device)
        DX_CHECK(ID3D12Device_QueryInterface(ctx->device, &IID_ID3D12VideoDevice, (শূন্য **)&ctx->video_device));

    ফেরত 0;

fail:
    ফেরত AVERROR(EINVAL);
}

স্থির শূন্য d3d12va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *device_hwctx = hwdev->hwctx;

    D3D12_OBJECT_RELEASE(device_hwctx->video_device);

    যদি (device_hwctx->lock == d3d12va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_মান;
        device_hwctx->lock = ফাঁকা;
    }
}

স্থির পূর্ণসংখ্যা d3d12va_device_create(AVHWDeviceContext *hwdev, ধ্রুবক অক্ষর *device,
                                 AVDictionary *opts, পূর্ণসংখ্যা flags)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    HRESULT hr;
    UINT create_flags = 0;
    IDXGIAdapter *pAdapter = ফাঁকা;

    পূর্ণসংখ্যা ret;
    পূর্ণসংখ্যা is_debug = !!av_dict_get(opts, "debug", ফাঁকা, 0);

    hwdev->মুক্ত = d3d12va_device_free;

    ret = d3d12va_load_functions(hwdev);
    যদি (ret < 0)
        ফেরত ret;

    যদি (is_debug) {
        ID3D12Debug *pDebug;
        যদি (priv->get_debug_interface && SUCCEEDED(priv->get_debug_interface(&IID_ID3D12Debug, (শূন্য **)&pDebug))) {
            create_flags |= DXGI_CREATE_FACTORY_DEBUG;
            ID3D12Debug_EnableDebugLayer(pDebug);
            D3D12_OBJECT_RELEASE(pDebug);
            av_log(hwdev, AV_LOG_INFO, "D3D12 debug layer is enabled!\n");
        }
    }

    যদি (!ctx->device) {
        IDXGIFactory2 *pDXGIFactory = ফাঁকা;

        hr = priv->create_dxgi_factory2(create_flags, &IID_IDXGIFactory2, (শূন্য **)&pDXGIFactory);
        যদি (SUCCEEDED(hr)) {
            পূর্ণসংখ্যা adapter = device ? atoi(device) : 0;
            যদি (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = ফাঁকা;
            IDXGIFactory2_Release(pDXGIFactory);
        }

        যদি (pAdapter) {
            DXGI_ADAPTER_DESC desc;
            hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
            যদি (!FAILED(hr)) {
                av_log(hwdev, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                       desc.VendorId, desc.DeviceId, desc.Description);
            }
        }

        hr = priv->create_device((IUnknown *)pAdapter, D3D_FEATURE_LEVEL_12_0, &IID_ID3D12Device, (শূন্য **)&ctx->device);
        D3D12_OBJECT_RELEASE(pAdapter);
        যদি (FAILED(hr)) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create Direct 3D 12 device (%lx)\n", (long)hr);
            ফেরত AVERROR_UNKNOWN;
        }
    }

    যদি (av_dict_get(opts, "UAV", ফাঁকা, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    যদি (av_dict_get(opts, "RTV", ফাঁকা, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

    যদি (av_dict_get(opts, "SHARED", ফাঁকা, 0))
        ctx->heap_flags |= D3D12_HEAP_FLAG_SHARED;

    ফেরত 0;
}

ধ্রুবক HWContextType ff_hwcontext_type_d3d12va = {
    .type                   = AV_HWDEVICE_TYPE_D3D12VA,
    .name                   = "D3D12VA",

    .device_hwctx_আকার      = আকার(D3D12VADevicePriv),
    .frames_hwctx_আকার      = আকার(D3D12VAFramesContext),

    .device_create          = d3d12va_device_create,
    .device_init            = d3d12va_device_init,
    .device_uninit          = d3d12va_device_uninit,
    .frames_get_constraints = d3d12va_frames_get_constraints,
    .frames_init            = d3d12va_frames_init,
    .frames_uninit          = d3d12va_frames_uninit,
    .frames_get_বাফার      = d3d12va_get_বাফার,
    .transfer_get_formats   = d3d12va_transfer_get_formats,
    .transfer_তথ্য_to       = d3d12va_transfer_তথ্য,
    .transfer_তথ্য_from     = d3d12va_transfer_তথ্য,

    .pix_fmts               = (ধ্রুবক গণনা AVPixelFormat[]){ AV_PIX_FMT_D3D12, AV_PIX_FMT_NONE },
};
