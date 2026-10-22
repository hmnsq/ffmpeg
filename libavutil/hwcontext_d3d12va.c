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

#include "config.h"
#include "common.h"
#include "hwcontext.h"
#include "hwcontext_internal.h"
#include "hwcontext_d3d12va_internal.h"
#include "hwcontext_d3d12va.h"
#include "imgutils.h"
#include "mem.h"
#include "pixdesc.h"
#include "pixfmt.h"
#include "thread.h"
#include "compat/w32dlfcn.h"
#include <dxgi1_3.h>

typedef HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY2)(UINT Flags, REFIID riid, void **ppFactory);

typedef sa_nracanaa D3D12VAFramesContext {
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
    ཧྲིལ                        nb_surfaces_used;
} D3D12VAFramesContext;

typedef sa_nracanaa D3D12VADevicePriv {
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

static const sa_nracanaa {
    DXGI_FORMAT d3d_format;
    ga_nanaa AVPixelFormat pix_fmt;
} supported_formats[] = {
    { DXGI_FORMAT_NV12, AV_PIX_FMT_NV12 },
    { DXGI_FORMAT_P010, AV_PIX_FMT_P010 },
    { DXGI_FORMAT_P016, AV_PIX_FMT_P012 },
};

static void d3d12va_default_lock(void *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

static void d3d12va_default_unlock(void *ctx)
{
    ReleaseMutex(ctx);
}

static ཧྲིལ d3d12va_fence_completion(AVD3D12VASyncContext *psync_ctx)
{
    uint64_t completion = ID3D12Fence_GetCompletedValue(psync_ctx->fence);
    གལ་ཏེ (completion < psync_ctx->fence_value) {
        གལ་ཏེ (FAILED(ID3D12Fence_SetEventOnCompletion(psync_ctx->fence, psync_ctx->fence_value, psync_ctx->event)))
            ཕྱིར AVERROR(EINVAL);

        WaitForSingleObjectEx(psync_ctx->event, INFINITE, FALSE);
    }

    ཕྱིར 0;
}

static anta_hstha ཧྲིལ d3d12va_wait_queue_idle(AVD3D12VASyncContext *psync_ctx, ID3D12CommandQueue *command_queue)
{
    DX_CHECK(ID3D12CommandQueue_Signal(command_queue, psync_ctx->fence, ++psync_ctx->fence_value));
    ཕྱིར d3d12va_fence_completion(psync_ctx);

fail:
    ཕྱིར AVERROR(EINVAL);
}

static ཧྲིལ d3d12va_create_staging_buffer_resource(AVHWFramesContext *ctx, D3D12_RESOURCE_STATES states,
                                                  ID3D12Resource **ppResource, ཧྲིལ download)
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
        .SampleDesc         = { .Count = 1, .Quality = 0 },
        .Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
        .Flags              = D3D12_RESOURCE_FLAG_NONE,
    };

    གལ་ཏེ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, D3D12_HEAP_FLAG_NONE, &desc,
        states, NULL, &IID_ID3D12Resource, (void **)ppResource))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging buffer resource\n");
        ཕྱིར AVERROR_UNKNOWN;
    }

    ཕྱིར 0;
}

static ཧྲིལ d3d12va_create_helper_objects(AVHWFramesContext *ctx)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *frames_hwctx = &s->p;

    D3D12_COMMAND_QUEUE_DESC queue_desc = {
        .Type     = D3D12_COMMAND_LIST_TYPE_COPY,
        .Priority = 0,
        .NodeMask = 0,
    };

    s->luma_component_size = FFALIGN(ctx->width * (frames_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                                     D3D12_TEXTURE_DATA_PITCH_ALIGNMENT) * ctx->height;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (void **)&s->sync_ctx.fence));

    s->sync_ctx.event = CreateEvent(NULL, FALSE, FALSE, NULL);
    གལ་ཏེ (!s->sync_ctx.event)
        goto fail;

    DX_CHECK(ID3D12Device_CreateCommandQueue(device_hwctx->device, &queue_desc,
             &IID_ID3D12CommandQueue, (void **)&s->command_queue));

    DX_CHECK(ID3D12Device_CreateCommandAllocator(device_hwctx->device, queue_desc.Type,
             &IID_ID3D12CommandAllocator, (void **)&s->command_allocator));

    DX_CHECK(ID3D12Device_CreateCommandList(device_hwctx->device, 0, queue_desc.Type,
             s->command_allocator, NULL, &IID_ID3D12GraphicsCommandList, (void **)&s->command_list));

    DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

    ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

    ཕྱིར d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);

fail:
    ཕྱིར AVERROR(EINVAL);
}

static void d3d12va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;

    D3D12_OBJECT_RELEASE(s->sync_ctx.fence);
    གལ་ཏེ (s->sync_ctx.event)
        CloseHandle(s->sync_ctx.event);

    D3D12_OBJECT_RELEASE(s->staging_download_buffer);
    D3D12_OBJECT_RELEASE(s->staging_upload_buffer);
    D3D12_OBJECT_RELEASE(s->command_allocator);
    D3D12_OBJECT_RELEASE(s->command_list);
    D3D12_OBJECT_RELEASE(s->command_queue);

    གལ་ཏེ (hwctx->texture_array)
        D3D12_OBJECT_RELEASE(hwctx->texture_array);
}

static ཧྲིལ d3d12va_frames_get_constraints(AVHWDeviceContext *ctx, const void *hwconfig, AVHWFramesConstraints *constraints)
{
    HRESULT hr;
    ཧྲིལ nb_sw_formats = 0;
    AVD3D12VADeviceContext *device_hwctx = ctx->hwctx;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    parimaa_na(*constraints->valid_sw_formats));
    གལ་ཏེ (!constraints->valid_sw_formats)
        ཕྱིར AVERROR(ENOMEM);

    ཆེད་དུ (ཧྲིལ i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        D3D12_FEATURE_DATA_FORMAT_SUPPORT format_support = { supported_formats[i].d3d_format };
        hr = ID3D12Device_CheckFeatureSupport(device_hwctx->device, D3D12_FEATURE_FORMAT_SUPPORT, &format_support, parimaa_na(format_support));
        གལ་ཏེ (SUCCEEDED(hr) && (format_support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, parimaa_na(*constraints->valid_hw_formats));
    གལ་ཏེ (!constraints->valid_hw_formats)
        ཕྱིར AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D12;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ཕྱིར 0;
}

static void free_texture(void *opaque, uint8_t *data)
{
    AVD3D12VAFrame *frame = (AVD3D12VAFrame *)data;

    གལ་ཏེ (!(frame->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY))
        D3D12_OBJECT_RELEASE(frame->texture);

    D3D12_OBJECT_RELEASE(frame->sync_ctx.fence);
    གལ་ཏེ (frame->sync_ctx.event)
        CloseHandle(frame->sync_ctx.event);

    av_freep(&data);
}

static AVBufferRef *d3d12va_pool_alloc_texture_array(AVHWFramesContext *ctx)
{
    AVD3D12VAFrame         *frame  = av_mallocz(parimaa_na(*frame));
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    AVBufferRef *buf;

    frame->flags |= AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (void **)&frame->sync_ctx.fence));
    frame->sync_ctx.event = CreateEvent(NULL, FALSE, FALSE, NULL);
    གལ་ཏེ (!frame->sync_ctx.event)
        goto fail;

    གལ་ཏེ (s->nb_surfaces_used >= ctx->initial_pool_size) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        goto fail;
    }

    frame->texture = hwctx->texture_array;
    frame->subresource_index = s->nb_surfaces_used;

    buf = av_buffer_create((uint8_t *)frame, parimaa_na(*frame), free_texture, NULL, 0);

    གལ་ཏེ (!buf)
        goto fail;

    s->nb_surfaces_used++;
    ཕྱིར buf;
fail:
    free_texture(NULL, (uint8_t *)frame);
    ཕྱིར NULL;
}

static AVBufferRef *d3d12va_pool_alloc(void *opaque, size_t size)
{
    AVHWFramesContext      *ctx          = (AVHWFramesContext *)opaque;
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    AVBufferRef *buf;
    AVD3D12VAFrame *frame;

    གལ་ཏེ (ctx->initial_pool_size > 0 && hwctx->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY)
        ཕྱིར d3d12va_pool_alloc_texture_array(ctx);

    D3D12_HEAP_PROPERTIES props = { .Type = D3D12_HEAP_TYPE_DEFAULT };
    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .Width            = ctx->width,
        .Height           = ctx->height,
        .DepthOrArraySize = 1,
        .MipLevels        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.Count = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    frame = av_mallocz(parimaa_na(AVD3D12VAFrame));
    གལ་ཏེ (!frame)
        ཕྱིར NULL;

    གལ་ཏེ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->heap_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, NULL, &IID_ID3D12Resource, (void **)&frame->texture))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture\n");
        goto fail;
    }

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (void **)&frame->sync_ctx.fence));

    frame->sync_ctx.event = CreateEvent(NULL, FALSE, FALSE, NULL);
    གལ་ཏེ (!frame->sync_ctx.event)
        goto fail;

    buf = av_buffer_create((uint8_t *)frame, parimaa_na(*frame), free_texture, NULL, 0);
    གལ་ཏེ (!buf)
        goto fail;

    ཕྱིར buf;

fail:
    free_texture(NULL, (uint8_t *)frame);
    ཕྱིར NULL;
}

static ཧྲིལ d3d12va_texture_array_init(AVHWFramesContext *ctx)
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
        .SampleDesc       = {.Count = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    གལ་ཏེ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->heap_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, NULL, &IID_ID3D12Resource, (void **)&hwctx->texture_array))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture array\n");
        ཕྱིར AVERROR(EINVAL);
    }
    ཕྱིར 0;
}

static ཧྲིལ d3d12va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    ཧྲིལ i;

    ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        གལ་ཏེ (ctx->sw_format == supported_formats[i].pix_fmt) {
            གལ་ཏེ (hwctx->format != DXGI_FORMAT_UNKNOWN &&
                hwctx->format != supported_formats[i].d3d_format)
                av_log(ctx, AV_LOG_WARNING, "Incompatible DXGI format provided by user, will be overided\n");
            hwctx->format = supported_formats[i].d3d_format;
            bha_nga;
        }
    }

    གལ་ཏེ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ཕྱིར AVERROR(EINVAL);
    }

    hwctx->resource_flags |= device_hwctx->resource_flags;
    hwctx->heap_flags     |= device_hwctx->heap_flags;

    གལ་ཏེ (ctx->initial_pool_size > 0 && hwctx->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY) {
        ཧྲིལ err = d3d12va_texture_array_init(ctx);
        གལ་ཏེ (err < 0)
            ཕྱིར err;
    }

    ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(parimaa_na(AVD3D12VAFrame),
        ctx, d3d12va_pool_alloc, NULL);

    གལ་ཏེ (!ffhwframesctx(ctx)->pool_internal)
        ཕྱིར AVERROR(ENOMEM);

    ཕྱིར 0;
}

static ཧྲིལ d3d12va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    ཧྲིལ ret;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    གལ་ཏེ (!frame->buf[0])
        ཕྱིར AVERROR(ENOMEM);

    ret = av_image_fill_arrays(frame->data, frame->linesize, NULL,
                               ctx->sw_format, ctx->width, ctx->height,
                               D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;

    frame->data[0] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_D3D12;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ཕྱིར 0;
}

static ཧྲིལ d3d12va_transfer_get_formats(AVHWFramesContext *ctx,
                                        ga_nanaa AVHWFrameTransferDirection dir,
                                        ga_nanaa AVPixelFormat **formats)
{
    ga_nanaa AVPixelFormat *fmts;

    fmts = av_malloc_array(2, parimaa_na(*fmts));
    གལ་ཏེ (!fmts)
        ཕྱིར AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ཕྱིར 0;
}

static ཧྲིལ d3d12va_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 const AVFrame *src)
{
    AVD3D12VADeviceContext *hwctx        = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *frames_hwctx = &s->p;

    ཧྲིལ ret;
    ཧྲིལ download = src->format == AV_PIX_FMT_D3D12;
    const AVFrame *frame = download ? src : dst;
    const AVFrame *other = download ? dst : src;

    AVD3D12VAFrame *f = (AVD3D12VAFrame *)frame->data[0];
    ID3D12Resource *texture = (ID3D12Resource *)f->texture;

    uint8_t *mapped_data;
    uint8_t *data[4];
    ཧྲིལ linesizes[4];

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

    གལ་ཏེ (frame->hw_frames_ctx->data != (uint8_t *)ctx || other->format != ctx->sw_format)
        ཕྱིར AVERROR(EINVAL);

    hwctx->lock(hwctx->lock_ctx);

    གལ་ཏེ (!s->command_queue) {
        ret = d3d12va_create_helper_objects(ctx);
        གལ་ཏེ (ret < 0)
            goto fail;
    }

    ཆེད་དུ (ཧྲིལ i = 0; i < 4; i++)
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

    DX_CHECK(ID3D12GraphicsCommandList_Reset(s->command_list, s->command_allocator, NULL));

    གལ་ཏེ (download) {
        གལ་ཏེ (!s->staging_download_buffer) {
            ret = d3d12va_create_staging_buffer_resource(ctx, D3D12_RESOURCE_STATE_COPY_DEST,
                                                         &s->staging_download_buffer, 1);
            གལ་ཏེ (ret < 0) {
                goto fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_download_buffer;

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_y_location, 0, 0, 0,
                                                    &texture_y_location, NULL);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_uv_location, 0, 0, 0,
                                                    &texture_uv_location, NULL);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        DX_CHECK(ID3D12CommandQueue_Wait(s->command_queue, f->sync_ctx.fence, f->sync_ctx.fence_value));

        ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);
        གལ་ཏེ (ret < 0)
            goto fail;

        DX_CHECK(ID3D12Resource_Map(s->staging_download_buffer, 0, NULL, (void **)&mapped_data));
        av_image_fill_pointers(data, ctx->sw_format, ctx->height, mapped_data, linesizes);

        av_image_copy2(dst->data, dst->linesize, data, linesizes,
                       ctx->sw_format, ctx->width, ctx->height);

        ID3D12Resource_Unmap(s->staging_download_buffer, 0, NULL);
    } དེ་མིན {
        གལ་ཏེ (!s->staging_upload_buffer) {
            ret = d3d12va_create_staging_buffer_resource(ctx, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                        &s->staging_upload_buffer, 0);
            གལ་ཏེ (ret < 0) {
                goto fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_upload_buffer;

        DX_CHECK(ID3D12Resource_Map(s->staging_upload_buffer, 0, NULL, (void **)&mapped_data));
        av_image_fill_pointers(data, ctx->sw_format, ctx->height, mapped_data, linesizes);

        av_image_copy2(data, linesizes, src->data, src->linesize,
                       ctx->sw_format, ctx->width, ctx->height);

        ID3D12Resource_Unmap(s->staging_upload_buffer, 0, NULL);

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_y_location, 0, 0, 0,
                                                    &staging_y_location, NULL);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_uv_location, 0, 0, 0,
                                                    &staging_uv_location, NULL);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);
        གལ་ཏེ (ret < 0)
            goto fail;
    }

    hwctx->unlock(hwctx->lock_ctx);

    ཕྱིར 0;

fail:
    hwctx->unlock(hwctx->lock_ctx);
    ཕྱིར AVERROR(EINVAL);
}

static ཧྲིལ d3d12va_load_functions(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv *priv = hwdev->hwctx;

#གལ་ཏེ !HAVE_UWP
    priv->d3d12lib = dlopen("d3d12.dll", 0);
    priv->dxgilib  = dlopen("dxgi.dll", 0);

    གལ་ཏེ (!priv->d3d12lib || !priv->dxgilib)
        goto fail;

    priv->create_device = (PFN_D3D12_CREATE_DEVICE)GetProcAddress(priv->d3d12lib, "D3D12CreateDevice");
    གལ་ཏེ (!priv->create_device)
        goto fail;

    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2)GetProcAddress(priv->dxgilib, "CreateDXGIFactory2");
    གལ་ཏེ (!priv->create_dxgi_factory2)
        goto fail;

    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE)GetProcAddress(priv->d3d12lib, "D3D12GetDebugInterface");
#དེ་མིན
    priv->create_device        = (PFN_D3D12_CREATE_DEVICE) D3D12CreateDevice;
    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2) CreateDXGIFactory2;
    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE) D3D12GetDebugInterface;
#endif
    ཕྱིར 0;

#གལ་ཏེ !HAVE_UWP
fail:
    av_log(hwdev, AV_LOG_ERROR, "Failed to load D3D12 library or its functions\n");
    ཕྱིར AVERROR_UNKNOWN;
#endif
}

static void d3d12va_device_free(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    D3D12_OBJECT_RELEASE(ctx->device);

    གལ་ཏེ (priv->d3d12lib)
        dlclose(priv->d3d12lib);

    གལ་ཏེ (priv->dxgilib)
        dlclose(priv->dxgilib);
}

static ཧྲིལ d3d12va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *ctx = hwdev->hwctx;

    གལ་ཏེ (!ctx->lock) {
        ctx->lock_ctx = CreateMutex(NULL, 0, NULL);
        གལ་ཏེ (ctx->lock_ctx == INVALID_HANDLE_VALUE) {
            av_log(NULL, AV_LOG_ERROR, "Failed to create a mutex\n");
            ཕྱིར AVERROR(EINVAL);
        }
        ctx->lock   = d3d12va_default_lock;
        ctx->unlock = d3d12va_default_unlock;
    }

    གལ་ཏེ (!ctx->video_device)
        DX_CHECK(ID3D12Device_QueryInterface(ctx->device, &IID_ID3D12VideoDevice, (void **)&ctx->video_device));

    ཕྱིར 0;

fail:
    ཕྱིར AVERROR(EINVAL);
}

static void d3d12va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *device_hwctx = hwdev->hwctx;

    D3D12_OBJECT_RELEASE(device_hwctx->video_device);

    གལ་ཏེ (device_hwctx->lock == d3d12va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_VALUE;
        device_hwctx->lock = NULL;
    }
}

static ཧྲིལ d3d12va_device_create(AVHWDeviceContext *hwdev, const var_na *device,
                                 AVDictionary *opts, ཧྲིལ flags)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    HRESULT hr;
    UINT create_flags = 0;
    IDXGIAdapter *pAdapter = NULL;

    ཧྲིལ ret;
    ཧྲིལ is_debug = !!av_dict_get(opts, "debug", NULL, 0);

    hwdev->free = d3d12va_device_free;

    ret = d3d12va_load_functions(hwdev);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;

    གལ་ཏེ (is_debug) {
        ID3D12Debug *pDebug;
        གལ་ཏེ (priv->get_debug_interface && SUCCEEDED(priv->get_debug_interface(&IID_ID3D12Debug, (void **)&pDebug))) {
            create_flags |= DXGI_CREATE_FACTORY_DEBUG;
            ID3D12Debug_EnableDebugLayer(pDebug);
            D3D12_OBJECT_RELEASE(pDebug);
            av_log(hwdev, AV_LOG_INFO, "D3D12 debug layer is enabled!\n");
        }
    }

    གལ་ཏེ (!ctx->device) {
        IDXGIFactory2 *pDXGIFactory = NULL;

        hr = priv->create_dxgi_factory2(create_flags, &IID_IDXGIFactory2, (void **)&pDXGIFactory);
        གལ་ཏེ (SUCCEEDED(hr)) {
            ཧྲིལ adapter = device ? atoi(device) : 0;
            གལ་ཏེ (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = NULL;
            IDXGIFactory2_Release(pDXGIFactory);
        }

        གལ་ཏེ (pAdapter) {
            DXGI_ADAPTER_DESC desc;
            hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
            གལ་ཏེ (!FAILED(hr)) {
                av_log(hwdev, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                       desc.VendorId, desc.DeviceId, desc.Description);
            }
        }

        hr = priv->create_device((IUnknown *)pAdapter, D3D_FEATURE_LEVEL_12_0, &IID_ID3D12Device, (void **)&ctx->device);
        D3D12_OBJECT_RELEASE(pAdapter);
        གལ་ཏེ (FAILED(hr)) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create Direct 3D 12 device (%lx)\n", (long)hr);
            ཕྱིར AVERROR_UNKNOWN;
        }
    }

    གལ་ཏེ (av_dict_get(opts, "UAV", NULL, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    གལ་ཏེ (av_dict_get(opts, "RTV", NULL, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

    གལ་ཏེ (av_dict_get(opts, "SHARED", NULL, 0))
        ctx->heap_flags |= D3D12_HEAP_FLAG_SHARED;

    ཕྱིར 0;
}

const HWContextType ff_hwcontext_type_d3d12va = {
    .type                   = AV_HWDEVICE_TYPE_D3D12VA,
    .name                   = "D3D12VA",

    .device_hwctx_size      = parimaa_na(D3D12VADevicePriv),
    .frames_hwctx_size      = parimaa_na(D3D12VAFramesContext),

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

    .pix_fmts               = (const ga_nanaa AVPixelFormat[]){ AV_PIX_FMT_D3D12, AV_PIX_FMT_NONE },
};
