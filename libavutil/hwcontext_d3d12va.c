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

تعریفنوع HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY2)(UINT Flags, REFIID riid, تهی **ppFactory);

تعریفنوع ساختار D3D12VAFramesContext {
    /**
     * The public AVD3D12VAFramesContext. See hwcontext_d3d12va.h for it.
     */
    AVD3D12VAFramesContext p;

    ID3D12Resource            *staging_download_buffer;
    ID3D12Resource            *staging_upload_buffer;
    ID3D12CommandQueue        *command_queue;
    ID3D12CommandAllocator    *command_allocator;
    ID3D12GraphicsCommandList *command_list;
    AVD3D12VASyncContext       sync_ctx;
    UINT                       luma_component_size;
    صحیح                        nb_surfaces_used;
} D3D12VAFramesContext;

تعریفنوع ساختار D3D12VADevicePriv {
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

ایستا ثابت ساختار {
    DXGI_FORMAT d3d_format;
    شمارش AVPixelFormat pix_fmt;
} supported_formats[] = {
    { DXGI_FORMAT_NV12, AV_PIX_FMT_NV12 },
    { DXGI_FORMAT_P010, AV_PIX_FMT_P010 },
    { DXGI_FORMAT_P016, AV_PIX_FMT_P012 },
};

ایستا تهی d3d12va_default_lock(تهی *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

ایستا تهی d3d12va_default_unlock(تهی *ctx)
{
    ReleaseMutex(ctx);
}

ایستا صحیح d3d12va_fence_completion(AVD3D12VASyncContext *psync_ctx)
{
    uint64_t completion = ID3_D12_Fence_Get_Completed_مقدار(psync_ctx->fence);
    اگر (completion < psync_ctx->fence_مقدار) {
        اگر (FAILED(ID3D12Fence_SetEventOnCompletion(psync_ctx->fence, psync_ctx->fence_مقدار, psync_ctx->event)))
            بازگشت AVERROR(EINVAL);

        WaitForSingleObjectEx(psync_ctx->event, INFINITE, FALSE);
    }

    بازگشت 0;
}

ایستا درونخطی صحیح d3d12va_wait_queue_idle(AVD3D12VASyncContext *psync_ctx, ID3D12CommandQueue *command_queue)
{
    DX_CHECK(ID3D12CommandQueue_Signal(command_queue, psync_ctx->fence, ++psync_ctx->fence_مقدار));
    بازگشت d3d12va_fence_completion(psync_ctx);

fail:
    بازگشت AVERROR(EINVAL);
}

ایستا صحیح d3d12va_create_staging_buffer_resource(AVHWFramesContext *ctx, D3D12_RESOURCE_STATES states,
                                                  ID3D12Resource **ppResource, صحیح download)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    D3D12_HEAP_PROPERTIES props = { .Type = download ? D3D12_HEAP_TYPE_READBACK : D3D12_HEAP_TYPE_UPLOAD };
    D3D12_RESOURCE_DESC desc = {
        .Dimension          = D3D12_RESOURCE_DIMENSION_BUFFER,
        .Alignment          = 0,
        .Width              = s->luma_component_size + (s->luma_component_size >> 1),
        .Height             = 1,
        .DepthOrArraySize   = 1,
        .MipLevels          = 1,
        .Format             = DXGI_FORMAT_UNKNOWN,
        .SampleDesc         = { .شمار_2 = 1, .Quality = 0 },
        .Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
        .Flags              = D3D12_RESOURCE_FLAG_NONE,
    };

    اگر (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, D3D12_HEAP_FLAG_NONE, &desc,
        states, پوچ, &IID_ID3D12Resource, (تهی **)ppResource))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging buffer resource\n");
        بازگشت AVERROR_UNKNOWN;
    }

    بازگشت 0;
}

ایستا صحیح d3d12va_create_helper_objects(AVHWFramesContext *ctx)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *frames_hwctx = &s->p;

    D3D12_COMMAND_QUEUE_DESC queue_desc = {
        .Type     = D3D12_COMMAND_LIST_TYPE_COPY,
        .Priority = 0,
        .گره_Mask = 0,
    };

    s->luma_component_size = FFALIGN(ctx->width * (frames_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                                     D3D12_TEXTURE_DATA_PITCH_ALIGNMENT) * ctx->height;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (تهی **)&s->sync_ctx.fence));

    s->sync_ctx.event = CreateEvent(پوچ, FALSE, FALSE, پوچ);
    اگر (!s->sync_ctx.event)
        برو fail;

    DX_CHECK(ID3D12Device_CreateCommandQueue(device_hwctx->device, &queue_desc,
             &IID_ID3D12CommandQueue, (تهی **)&s->command_queue));

    DX_CHECK(ID3D12Device_CreateCommandAllocator(device_hwctx->device, queue_desc.Type,
             &IID_ID3D12CommandAllocator, (تهی **)&s->command_allocator));

    DX_CHECK(ID3D12Device_CreateCommandList(device_hwctx->device, 0, queue_desc.Type,
             s->command_allocator, پوچ, &IID_ID3D12GraphicsCommandList, (تهی **)&s->command_list));

    DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

    ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

    بازگشت d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);

fail:
    بازگشت AVERROR(EINVAL);
}

ایستا تهی d3d12va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;

    D3D12_OBJECT_RELEASE(s->sync_ctx.fence);
    اگر (s->sync_ctx.event)
        CloseHandle(s->sync_ctx.event);

    D3D12_OBJECT_RELEASE(s->staging_download_buffer);
    D3D12_OBJECT_RELEASE(s->staging_upload_buffer);
    D3D12_OBJECT_RELEASE(s->command_allocator);
    D3D12_OBJECT_RELEASE(s->command_list);
    D3D12_OBJECT_RELEASE(s->command_queue);

    اگر (hwctx->texture_array)
        D3D12_OBJECT_RELEASE(hwctx->texture_array);
}

ایستا صحیح d3d12va_frames_get_constraints(AVHWDeviceContext *ctx, ثابت تهی *hwconfig, AVHWFramesConstraints *constraints)
{
    HRESULT hr;
    صحیح nb_sw_formats = 0;
    AVD3D12VADeviceContext *device_hwctx = ctx->hwctx;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    اندازه(*constraints->valid_sw_formats));
    اگر (!constraints->valid_sw_formats)
        بازگشت AVERROR(ENOMEM);

    برای (صحیح i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        D3D12_FEATURE_DATA_FORMAT_SUPPORT format_support = { supported_formats[i].d3d_format };
        hr = ID3D12Device_CheckFeatureSupport(device_hwctx->device, D3D12_FEATURE_FORMAT_SUPPORT, &format_support, اندازه(format_support));
        اگر (SUCCEEDED(hr) && (format_support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, اندازه(*constraints->valid_hw_formats));
    اگر (!constraints->valid_hw_formats)
        بازگشت AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D12;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    بازگشت 0;
}

ایستا تهی free_texture(تهی *opaque, uint8_t *data)
{
    AVD3D12VAFrame *frame = (AVD3D12VAFrame *)data;

    اگر (!(frame->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY))
        D3D12_OBJECT_RELEASE(frame->texture);

    D3D12_OBJECT_RELEASE(frame->sync_ctx.fence);
    اگر (frame->sync_ctx.event)
        CloseHandle(frame->sync_ctx.event);

    av_freep(&data);
}

ایستا AVBufferRef *d3d12va_pool_alloc_texture_array(AVHWFramesContext *ctx)
{
    AVD3D12VAFrame         *frame  = av_mallocz(اندازه(*frame));
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    AVBufferRef *buf;

    frame->flags |= AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (تهی **)&frame->sync_ctx.fence));
    frame->sync_ctx.event = CreateEvent(پوچ, FALSE, FALSE, پوچ);
    اگر (!frame->sync_ctx.event)
        برو fail;

    اگر (s->nb_surfaces_used >= ctx->initial_pool_size) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        برو fail;
    }

    frame->texture = hwctx->texture_array;
    frame->subresource_index = s->nb_surfaces_used;

    buf = av_buffer_create((uint8_t *)frame, اندازه(*frame), free_texture, پوچ, 0);

    اگر (!buf)
        برو fail;

    s->nb_surfaces_used++;
    بازگشت buf;
fail:
    free_texture(پوچ, (uint8_t *)frame);
    بازگشت پوچ;
}

ایستا AVBufferRef *d3d12va_pool_alloc(تهی *opaque, size_t size)
{
    AVHWFramesContext      *ctx          = (AVHWFramesContext *)opaque;
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    AVBufferRef *buf;
    AVD3D12VAFrame *frame;

    اگر (ctx->initial_pool_size > 0 && hwctx->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY)
        بازگشت d3d12va_pool_alloc_texture_array(ctx);

    D3D12_HEAP_PROPERTIES props = { .Type = D3D12_HEAP_TYPE_DEFAULT };
    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .Width            = ctx->width,
        .Height           = ctx->height,
        .DepthOrArraySize = 1,
        .MipLevels        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.شمار_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    frame = av_mallocz(اندازه(AVD3D12VAFrame));
    اگر (!frame)
        بازگشت پوچ;

    اگر (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->heap_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, پوچ, &IID_ID3D12Resource, (تهی **)&frame->texture))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture\n");
        برو fail;
    }

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (تهی **)&frame->sync_ctx.fence));

    frame->sync_ctx.event = CreateEvent(پوچ, FALSE, FALSE, پوچ);
    اگر (!frame->sync_ctx.event)
        برو fail;

    buf = av_buffer_create((uint8_t *)frame, اندازه(*frame), free_texture, پوچ, 0);
    اگر (!buf)
        برو fail;

    بازگشت buf;

fail:
    free_texture(پوچ, (uint8_t *)frame);
    بازگشت پوچ;
}

ایستا صحیح d3d12va_texture_array_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    D3D12_HEAP_PROPERTIES props = { .Type = D3D12_HEAP_TYPE_DEFAULT };

    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .Width            = ctx->width,
        .Height           = ctx->height,
        .DepthOrArraySize = ctx->initial_pool_size,
        .MipLevels        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.شمار_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    اگر (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->heap_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, پوچ, &IID_ID3D12Resource, (تهی **)&hwctx->texture_array))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture array\n");
        بازگشت AVERROR(EINVAL);
    }
    بازگشت 0;
}

ایستا صحیح d3d12va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    صحیح i;

    برای (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        اگر (ctx->sw_format == supported_formats[i].pix_fmt) {
            اگر (hwctx->format != DXGI_FORMAT_UNKNOWN &&
                hwctx->format != supported_formats[i].d3d_format)
                av_log(ctx, AV_LOG_WARNING, "Incompatible DXGI format provided by user, will be overided\n");
            hwctx->format = supported_formats[i].d3d_format;
            بشکن;
        }
    }

    اگر (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        بازگشت AVERROR(EINVAL);
    }

    hwctx->resource_flags |= device_hwctx->resource_flags;
    hwctx->heap_flags     |= device_hwctx->heap_flags;

    اگر (ctx->initial_pool_size > 0 && hwctx->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY) {
        صحیح err = d3d12va_texture_array_init(ctx);
        اگر (err < 0)
            بازگشت err;
    }

    ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(اندازه(AVD3D12VAFrame),
        ctx, d3d12va_pool_alloc, پوچ);

    اگر (!ffhwframesctx(ctx)->pool_internal)
        بازگشت AVERROR(ENOMEM);

    بازگشت 0;
}

ایستا صحیح d3d12va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    صحیح ret;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    اگر (!frame->buf[0])
        بازگشت AVERROR(ENOMEM);

    ret = av_image_fill_arrays(frame->data, frame->linesize, پوچ,
                               ctx->sw_format, ctx->width, ctx->height,
                               D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
    اگر (ret < 0)
        بازگشت ret;

    frame->data[0] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_D3D12;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    بازگشت 0;
}

ایستا صحیح d3d12va_transfer_get_formats(AVHWFramesContext *ctx,
                                        شمارش AVHWFrameTransferDirection dir,
                                        شمارش AVPixelFormat **formats)
{
    شمارش AVPixelFormat *fmts;

    fmts = av_malloc_array(2, اندازه(*fmts));
    اگر (!fmts)
        بازگشت AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    بازگشت 0;
}

ایستا صحیح d3d12va_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    AVD3D12VADeviceContext *hwctx        = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *frames_hwctx = &s->p;

    صحیح ret;
    صحیح download = src->format == AV_PIX_FMT_D3D12;
    ثابت AVFrame *frame = download ? src : dst;
    ثابت AVFrame *other = download ? dst : src;

    AVD3D12VAFrame *f = (AVD3D12VAFrame *)frame->data[0];
    ID3D12Resource *texture = (ID3D12Resource *)f->texture;

    uint8_t *mapped_data;
    uint8_t *data[4];
    صحیح linesizes[4];

    D3D12_TEXTURE_COPY_LOCATION staging_y_location  = { 0 };
    D3D12_TEXTURE_COPY_LOCATION staging_uv_location = { 0 };

    D3D12_TEXTURE_COPY_LOCATION texture_y_location = {
        .pResource        = texture,
        .Type             = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
        .SubresourceIndex = 0,
    };

    D3D12_TEXTURE_COPY_LOCATION texture_uv_location = {
        .pResource        = texture,
        .Type             = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
        .SubresourceIndex = 1,
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

    اگر (frame->hw_frames_ctx->data != (uint8_t *)ctx || other->format != ctx->sw_format)
        بازگشت AVERROR(EINVAL);

    hwctx->lock(hwctx->lock_ctx);

    اگر (!s->command_queue) {
        ret = d3d12va_create_helper_objects(ctx);
        اگر (ret < 0)
            برو fail;
    }

    برای (صحیح i = 0; i < 4; i++)
        linesizes[i] = FFALIGN(frame->width * (frames_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                               D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);

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
            .Offset = s->luma_component_size,
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

    DX_CHECK(ID3D12GraphicsCommandList_Reset(s->command_list, s->command_allocator, پوچ));

    اگر (download) {
        اگر (!s->staging_download_buffer) {
            ret = d3d12va_create_staging_buffer_resource(ctx, D3D12_RESOURCE_STATE_COPY_DEST,
                                                         &s->staging_download_buffer, 1);
            اگر (ret < 0) {
                برو fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_download_buffer;

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_y_location, 0, 0, 0,
                                                    &texture_y_location, پوچ);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_uv_location, 0, 0, 0,
                                                    &texture_uv_location, پوچ);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        DX_CHECK(ID3D12CommandQueue_Wait(s->command_queue, f->sync_ctx.fence, f->sync_ctx.fence_مقدار));

        ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);
        اگر (ret < 0)
            برو fail;

        DX_CHECK(ID3D12Resource_Map(s->staging_download_buffer, 0, پوچ, (تهی **)&mapped_data));
        av_image_fill_pointers(data, ctx->sw_format, ctx->height, mapped_data, linesizes);

        av_image_copy2(dst->data, dst->linesize, data, linesizes,
                       ctx->sw_format, ctx->width, ctx->height);

        ID3D12Resource_Unmap(s->staging_download_buffer, 0, پوچ);
    } وگرنه {
        اگر (!s->staging_upload_buffer) {
            ret = d3d12va_create_staging_buffer_resource(ctx, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                        &s->staging_upload_buffer, 0);
            اگر (ret < 0) {
                برو fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_upload_buffer;

        DX_CHECK(ID3D12Resource_Map(s->staging_upload_buffer, 0, پوچ, (تهی **)&mapped_data));
        av_image_fill_pointers(data, ctx->sw_format, ctx->height, mapped_data, linesizes);

        av_image_copy2(data, linesizes, src->data, src->linesize,
                       ctx->sw_format, ctx->width, ctx->height);

        ID3D12Resource_Unmap(s->staging_upload_buffer, 0, پوچ);

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_y_location, 0, 0, 0,
                                                    &staging_y_location, پوچ);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_uv_location, 0, 0, 0,
                                                    &staging_uv_location, پوچ);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);
        اگر (ret < 0)
            برو fail;
    }

    hwctx->unlock(hwctx->lock_ctx);

    بازگشت 0;

fail:
    hwctx->unlock(hwctx->lock_ctx);
    بازگشت AVERROR(EINVAL);
}

ایستا صحیح d3d12va_load_functions(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv *priv = hwdev->hwctx;

#اگر !HAVE_UWP
    priv->d3d12lib = dlopen("d3d12.dll", 0);
    priv->dxgilib  = dlopen("dxgi.dll", 0);

    اگر (!priv->d3d12lib || !priv->dxgilib)
        برو fail;

    priv->create_device = (PFN_D3D12_CREATE_DEVICE)GetProcAddress(priv->d3d12lib, "D3D12CreateDevice");
    اگر (!priv->create_device)
        برو fail;

    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2)GetProcAddress(priv->dxgilib, "CreateDXGIFactory2");
    اگر (!priv->create_dxgi_factory2)
        برو fail;

    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE)GetProcAddress(priv->d3d12lib, "D3D12GetDebugInterface");
#وگرنه
    priv->create_device        = (PFN_D3D12_CREATE_DEVICE) D3D12CreateDevice;
    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2) CreateDXGIFactory2;
    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE) D3D12GetDebugInterface;
#endif
    بازگشت 0;

#اگر !HAVE_UWP
fail:
    av_log(hwdev, AV_LOG_ERROR, "Failed to load D3D12 library or its functions\n");
    بازگشت AVERROR_UNKNOWN;
#endif
}

ایستا تهی d3d12va_device_free(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    D3D12_OBJECT_RELEASE(ctx->device);

    اگر (priv->d3d12lib)
        dlclose(priv->d3d12lib);

    اگر (priv->dxgilib)
        dlclose(priv->dxgilib);
}

ایستا صحیح d3d12va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *ctx = hwdev->hwctx;

    اگر (!ctx->lock) {
        ctx->lock_ctx = CreateMutex(پوچ, 0, پوچ);
        اگر (ctx->lock_ctx == INVALID_HANDLE_مقدار) {
            av_log(پوچ, AV_LOG_ERROR, "Failed to create a mutex\n");
            بازگشت AVERROR(EINVAL);
        }
        ctx->lock   = d3d12va_default_lock;
        ctx->unlock = d3d12va_default_unlock;
    }

    اگر (!ctx->video_device)
        DX_CHECK(ID3D12Device_QueryInterface(ctx->device, &IID_ID3D12VideoDevice, (تهی **)&ctx->video_device));

    بازگشت 0;

fail:
    بازگشت AVERROR(EINVAL);
}

ایستا تهی d3d12va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *device_hwctx = hwdev->hwctx;

    D3D12_OBJECT_RELEASE(device_hwctx->video_device);

    اگر (device_hwctx->lock == d3d12va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_مقدار;
        device_hwctx->lock = پوچ;
    }
}

ایستا صحیح d3d12va_device_create(AVHWDeviceContext *hwdev, ثابت نویسه *device,
                                 AVDictionary *opts, صحیح flags)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    HRESULT hr;
    UINT create_flags = 0;
    IDXGIAdapter *pAdapter = پوچ;

    صحیح ret;
    صحیح is_debug = !!av_dict_get(opts, "debug", پوچ, 0);

    hwdev->آزاد = d3d12va_device_free;

    ret = d3d12va_load_functions(hwdev);
    اگر (ret < 0)
        بازگشت ret;

    اگر (is_debug) {
        ID3D12Debug *pDebug;
        اگر (priv->get_debug_interface && SUCCEEDED(priv->get_debug_interface(&IID_ID3D12Debug, (تهی **)&pDebug))) {
            create_flags |= DXGI_CREATE_FACTORY_DEBUG;
            ID3D12Debug_EnableDebugLayer(pDebug);
            D3D12_OBJECT_RELEASE(pDebug);
            av_log(hwdev, AV_LOG_INFO, "D3D12 debug layer is enabled!\n");
        }
    }

    اگر (!ctx->device) {
        IDXGIFactory2 *pDXGIFactory = پوچ;

        hr = priv->create_dxgi_factory2(create_flags, &IID_IDXGIFactory2, (تهی **)&pDXGIFactory);
        اگر (SUCCEEDED(hr)) {
            صحیح adapter = device ? atoi(device) : 0;
            اگر (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = پوچ;
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

        hr = priv->create_device((IUnknown *)pAdapter, D3D_FEATURE_LEVEL_12_0, &IID_ID3D12Device, (تهی **)&ctx->device);
        D3D12_OBJECT_RELEASE(pAdapter);
        اگر (FAILED(hr)) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create Direct 3D 12 device (%lx)\n", (long)hr);
            بازگشت AVERROR_UNKNOWN;
        }
    }

    اگر (av_dict_get(opts, "UAV", پوچ, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    اگر (av_dict_get(opts, "RTV", پوچ, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

    اگر (av_dict_get(opts, "SHARED", پوچ, 0))
        ctx->heap_flags |= D3D12_HEAP_FLAG_SHARED;

    بازگشت 0;
}

ثابت HWContextType ff_hwcontext_type_d3d12va = {
    .type                   = AV_HWDEVICE_TYPE_D3D12VA,
    .name                   = "D3D12VA",

    .device_hwctx_size      = اندازه(D3D12VADevicePriv),
    .frames_hwctx_size      = اندازه(D3D12VAFramesContext),

    .device_create          = d3d12va_device_create,
    .device_init            = d3d12va_device_init,
    .device_uninit          = d3d12va_device_uninit,
    .frames_get_constraints = d3d12va_frames_get_constraints,
    .frames_init            = d3d12va_frames_init,
    .frames_uninit          = d3d12va_frames_uninit,
    .frames_get_buffer      = d3d12va_get_buffer,
    .transfer_get_formats   = d3d12va_transfer_get_formats,
    .transfer_data_to       = d3d12va_transfer_data,
    .transfer_data_from     = d3d12va_transfer_data,

    .pix_fmts               = (ثابت شمارش AVPixelFormat[]){ AV_PIX_FMT_D3D12, AV_PIX_FMT_NONE },
};
