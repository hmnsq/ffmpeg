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

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "hwcontext.h"
#അന്തര്ഭാവ "hwcontext_internal.h"
#അന്തര്ഭാവ "hwcontext_d3d12va_internal.h"
#അന്തര്ഭാവ "hwcontext_d3d12va.h"
#അന്തര്ഭാവ "imgutils.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "pixdesc.h"
#അന്തര്ഭാവ "pixfmt.h"
#അന്തര്ഭാവ "thread.h"
#അന്തര്ഭാവ "compat/w32dlfcn.h"
#അന്തര്ഭാവ <dxgi1_3.h>

തരനിർവചനം HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY2)(UINT Flags, REFIID riid, ശൂന്യം **ppFactory);

തരനിർവചനം ഘടന D3D12VAFramesContext {
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
    പൂർണ്ണസംഖ്യ                        nb_surfaces_used;
} D3D12VAFramesContext;

തരനിർവചനം ഘടന D3D12VADevicePriv {
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

സ്ഥിതം സ്ഥിരം ഘടന {
    DXGI_FORMAT d3d_format;
    എണ്ണൽ AVPixelFormat pix_fmt;
} supported_formats[] = {
    { DXGI_FORMAT_NV12, AV_PIX_FMT_NV12 },
    { DXGI_FORMAT_P010, AV_PIX_FMT_P010 },
    { DXGI_FORMAT_P016, AV_PIX_FMT_P012 },
};

സ്ഥിതം ശൂന്യം d3d12va_default_lock(ശൂന്യം *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

സ്ഥിതം ശൂന്യം d3d12va_default_unlock(ശൂന്യം *ctx)
{
    ReleaseMutex(ctx);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d12va_fence_completion(AVD3D12VASyncContext *psync_ctx)
{
    uint64_t completion = ID3_D12_Fence_Get_Completed_മൂല്യം(psync_ctx->fence);
    എങ്കിൽ (completion < psync_ctx->fence_മൂല്യം) {
        എങ്കിൽ (FAILED(ID3D12Fence_SetEventOnCompletion(psync_ctx->fence, psync_ctx->fence_മൂല്യം, psync_ctx->event)))
            തിരികെ AVERROR(EINVAL);

        WaitForSingleObjectEx(psync_ctx->event, INFINITE, FALSE);
    }

    തിരികെ 0;
}

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ d3d12va_wait_queue_idle(AVD3D12VASyncContext *psync_ctx, ID3D12CommandQueue *command_queue)
{
    DX_CHECK(ID3D12CommandQueue_Signal(command_queue, psync_ctx->fence, ++psync_ctx->fence_മൂല്യം));
    തിരികെ d3d12va_fence_completion(psync_ctx);

fail:
    തിരികെ AVERROR(EINVAL);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d12va_create_staging_buffer_resource(AVHWFramesContext *ctx, D3D12_RESOURCE_STATES states,
                                                  ID3D12Resource **ppResource, പൂർണ്ണസംഖ്യ download)
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
        .SampleDesc         = { .എണ്ണം_2 = 1, .Quality = 0 },
        .Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
        .Flags              = D3D12_RESOURCE_FLAG_NONE,
    };

    എങ്കിൽ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, D3D12_HEAP_FLAG_NONE, &desc,
        states, ശൂന്യ, &IID_ID3D12Resource, (ശൂന്യം **)ppResource))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging buffer resource\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d12va_create_helper_objects(AVHWFramesContext *ctx)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *frames_hwctx = &s->p;

    D3D12_COMMAND_QUEUE_DESC queue_desc = {
        .Type     = D3D12_COMMAND_LIST_TYPE_COPY,
        .Priority = 0,
        .കണ്ണി_Mask = 0,
    };

    s->luma_component_size = FFALIGN(ctx->width * (frames_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                                     D3D12_TEXTURE_DATA_PITCH_ALIGNMENT) * ctx->height;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (ശൂന്യം **)&s->sync_ctx.fence));

    s->sync_ctx.event = CreateEvent(ശൂന്യ, FALSE, FALSE, ശൂന്യ);
    എങ്കിൽ (!s->sync_ctx.event)
        പോകുക fail;

    DX_CHECK(ID3D12Device_CreateCommandQueue(device_hwctx->device, &queue_desc,
             &IID_ID3D12CommandQueue, (ശൂന്യം **)&s->command_queue));

    DX_CHECK(ID3D12Device_CreateCommandAllocator(device_hwctx->device, queue_desc.Type,
             &IID_ID3D12CommandAllocator, (ശൂന്യം **)&s->command_allocator));

    DX_CHECK(ID3D12Device_CreateCommandList(device_hwctx->device, 0, queue_desc.Type,
             s->command_allocator, ശൂന്യ, &IID_ID3D12GraphicsCommandList, (ശൂന്യം **)&s->command_list));

    DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

    ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

    തിരികെ d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);

fail:
    തിരികെ AVERROR(EINVAL);
}

സ്ഥിതം ശൂന്യം d3d12va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;

    D3D12_OBJECT_RELEASE(s->sync_ctx.fence);
    എങ്കിൽ (s->sync_ctx.event)
        CloseHandle(s->sync_ctx.event);

    D3D12_OBJECT_RELEASE(s->staging_download_buffer);
    D3D12_OBJECT_RELEASE(s->staging_upload_buffer);
    D3D12_OBJECT_RELEASE(s->command_allocator);
    D3D12_OBJECT_RELEASE(s->command_list);
    D3D12_OBJECT_RELEASE(s->command_queue);

    എങ്കിൽ (hwctx->texture_array)
        D3D12_OBJECT_RELEASE(hwctx->texture_array);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d12va_frames_get_constraints(AVHWDeviceContext *ctx, സ്ഥിരം ശൂന്യം *hwconfig, AVHWFramesConstraints *constraints)
{
    HRESULT hr;
    പൂർണ്ണസംഖ്യ nb_sw_formats = 0;
    AVD3D12VADeviceContext *device_hwctx = ctx->hwctx;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    വലുപ്പം(*constraints->valid_sw_formats));
    എങ്കിൽ (!constraints->valid_sw_formats)
        തിരികെ AVERROR(ENOMEM);

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        D3D12_FEATURE_DATA_FORMAT_SUPPORT format_support = { supported_formats[i].d3d_format };
        hr = ID3D12Device_CheckFeatureSupport(device_hwctx->device, D3D12_FEATURE_FORMAT_SUPPORT, &format_support, വലുപ്പം(format_support));
        എങ്കിൽ (SUCCEEDED(hr) && (format_support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, വലുപ്പം(*constraints->valid_hw_formats));
    എങ്കിൽ (!constraints->valid_hw_formats)
        തിരികെ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D12;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം free_texture(ശൂന്യം *opaque, uint8_t *data)
{
    AVD3D12VAFrame *frame = (AVD3D12VAFrame *)data;

    എങ്കിൽ (!(frame->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY))
        D3D12_OBJECT_RELEASE(frame->texture);

    D3D12_OBJECT_RELEASE(frame->sync_ctx.fence);
    എങ്കിൽ (frame->sync_ctx.event)
        CloseHandle(frame->sync_ctx.event);

    av_freep(&data);
}

സ്ഥിതം AVBufferRef *d3d12va_pool_alloc_texture_array(AVHWFramesContext *ctx)
{
    AVD3D12VAFrame         *frame  = av_mallocz(വലുപ്പം(*frame));
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    AVBufferRef *buf;

    frame->flags |= AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (ശൂന്യം **)&frame->sync_ctx.fence));
    frame->sync_ctx.event = CreateEvent(ശൂന്യ, FALSE, FALSE, ശൂന്യ);
    എങ്കിൽ (!frame->sync_ctx.event)
        പോകുക fail;

    എങ്കിൽ (s->nb_surfaces_used >= ctx->initial_pool_size) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        പോകുക fail;
    }

    frame->texture = hwctx->texture_array;
    frame->subresource_index = s->nb_surfaces_used;

    buf = av_buffer_create((uint8_t *)frame, വലുപ്പം(*frame), free_texture, ശൂന്യ, 0);

    എങ്കിൽ (!buf)
        പോകുക fail;

    s->nb_surfaces_used++;
    തിരികെ buf;
fail:
    free_texture(ശൂന്യ, (uint8_t *)frame);
    തിരികെ ശൂന്യ;
}

സ്ഥിതം AVBufferRef *d3d12va_pool_alloc(ശൂന്യം *opaque, size_t size)
{
    AVHWFramesContext      *ctx          = (AVHWFramesContext *)opaque;
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    AVBufferRef *buf;
    AVD3D12VAFrame *frame;

    എങ്കിൽ (ctx->initial_pool_size > 0 && hwctx->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY)
        തിരികെ d3d12va_pool_alloc_texture_array(ctx);

    D3D12_HEAP_PROPERTIES props = { .Type = D3D12_HEAP_TYPE_DEFAULT };
    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .Width            = ctx->width,
        .Height           = ctx->height,
        .DepthOrArraySize = 1,
        .MipLevels        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.എണ്ണം_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    frame = av_mallocz(വലുപ്പം(AVD3D12VAFrame));
    എങ്കിൽ (!frame)
        തിരികെ ശൂന്യ;

    എങ്കിൽ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->heap_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, ശൂന്യ, &IID_ID3D12Resource, (ശൂന്യം **)&frame->texture))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture\n");
        പോകുക fail;
    }

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (ശൂന്യം **)&frame->sync_ctx.fence));

    frame->sync_ctx.event = CreateEvent(ശൂന്യ, FALSE, FALSE, ശൂന്യ);
    എങ്കിൽ (!frame->sync_ctx.event)
        പോകുക fail;

    buf = av_buffer_create((uint8_t *)frame, വലുപ്പം(*frame), free_texture, ശൂന്യ, 0);
    എങ്കിൽ (!buf)
        പോകുക fail;

    തിരികെ buf;

fail:
    free_texture(ശൂന്യ, (uint8_t *)frame);
    തിരികെ ശൂന്യ;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d12va_texture_array_init(AVHWFramesContext *ctx)
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
        .SampleDesc       = {.എണ്ണം_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    എങ്കിൽ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->heap_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, ശൂന്യ, &IID_ID3D12Resource, (ശൂന്യം **)&hwctx->texture_array))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture array\n");
        തിരികെ AVERROR(EINVAL);
    }
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d12va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        എങ്കിൽ (ctx->sw_format == supported_formats[i].pix_fmt) {
            എങ്കിൽ (hwctx->format != DXGI_FORMAT_UNKNOWN &&
                hwctx->format != supported_formats[i].d3d_format)
                av_log(ctx, AV_LOG_WARNING, "Incompatible DXGI format provided by user, will be overided\n");
            hwctx->format = supported_formats[i].d3d_format;
            നിർത്തുക;
        }
    }

    എങ്കിൽ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        തിരികെ AVERROR(EINVAL);
    }

    hwctx->resource_flags |= device_hwctx->resource_flags;
    hwctx->heap_flags     |= device_hwctx->heap_flags;

    എങ്കിൽ (ctx->initial_pool_size > 0 && hwctx->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY) {
        പൂർണ്ണസംഖ്യ err = d3d12va_texture_array_init(ctx);
        എങ്കിൽ (err < 0)
            തിരികെ err;
    }

    ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(വലുപ്പം(AVD3D12VAFrame),
        ctx, d3d12va_pool_alloc, ശൂന്യ);

    എങ്കിൽ (!ffhwframesctx(ctx)->pool_internal)
        തിരികെ AVERROR(ENOMEM);

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d12va_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    പൂർണ്ണസംഖ്യ ret;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    എങ്കിൽ (!frame->buf[0])
        തിരികെ AVERROR(ENOMEM);

    ret = av_image_fill_arrays(frame->data, frame->linesize, ശൂന്യ,
                               ctx->sw_format, ctx->width, ctx->height,
                               D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    frame->data[0] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_D3D12;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d12va_transfer_get_formats(AVHWFramesContext *ctx,
                                        എണ്ണൽ AVHWFrameTransferDirection dir,
                                        എണ്ണൽ AVPixelFormat **formats)
{
    എണ്ണൽ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, വലുപ്പം(*fmts));
    എങ്കിൽ (!fmts)
        തിരികെ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d12va_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 സ്ഥിരം AVFrame *src)
{
    AVD3D12VADeviceContext *hwctx        = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *frames_hwctx = &s->p;

    പൂർണ്ണസംഖ്യ ret;
    പൂർണ്ണസംഖ്യ download = src->format == AV_PIX_FMT_D3D12;
    സ്ഥിരം AVFrame *frame = download ? src : dst;
    സ്ഥിരം AVFrame *other = download ? dst : src;

    AVD3D12VAFrame *f = (AVD3D12VAFrame *)frame->data[0];
    ID3D12Resource *texture = (ID3D12Resource *)f->texture;

    uint8_t *mapped_data;
    uint8_t *data[4];
    പൂർണ്ണസംഖ്യ linesizes[4];

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

    എങ്കിൽ (frame->hw_frames_ctx->data != (uint8_t *)ctx || other->format != ctx->sw_format)
        തിരികെ AVERROR(EINVAL);

    hwctx->lock(hwctx->lock_ctx);

    എങ്കിൽ (!s->command_queue) {
        ret = d3d12va_create_helper_objects(ctx);
        എങ്കിൽ (ret < 0)
            പോകുക fail;
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < 4; i++)
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

    DX_CHECK(ID3D12GraphicsCommandList_Reset(s->command_list, s->command_allocator, ശൂന്യ));

    എങ്കിൽ (download) {
        എങ്കിൽ (!s->staging_download_buffer) {
            ret = d3d12va_create_staging_buffer_resource(ctx, D3D12_RESOURCE_STATE_COPY_DEST,
                                                         &s->staging_download_buffer, 1);
            എങ്കിൽ (ret < 0) {
                പോകുക fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_download_buffer;

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_y_location, 0, 0, 0,
                                                    &texture_y_location, ശൂന്യ);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_uv_location, 0, 0, 0,
                                                    &texture_uv_location, ശൂന്യ);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        DX_CHECK(ID3D12CommandQueue_Wait(s->command_queue, f->sync_ctx.fence, f->sync_ctx.fence_മൂല്യം));

        ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);
        എങ്കിൽ (ret < 0)
            പോകുക fail;

        DX_CHECK(ID3D12Resource_Map(s->staging_download_buffer, 0, ശൂന്യ, (ശൂന്യം **)&mapped_data));
        av_image_fill_pointers(data, ctx->sw_format, ctx->height, mapped_data, linesizes);

        av_image_copy2(dst->data, dst->linesize, data, linesizes,
                       ctx->sw_format, ctx->width, ctx->height);

        ID3D12Resource_Unmap(s->staging_download_buffer, 0, ശൂന്യ);
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (!s->staging_upload_buffer) {
            ret = d3d12va_create_staging_buffer_resource(ctx, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                        &s->staging_upload_buffer, 0);
            എങ്കിൽ (ret < 0) {
                പോകുക fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_upload_buffer;

        DX_CHECK(ID3D12Resource_Map(s->staging_upload_buffer, 0, ശൂന്യ, (ശൂന്യം **)&mapped_data));
        av_image_fill_pointers(data, ctx->sw_format, ctx->height, mapped_data, linesizes);

        av_image_copy2(data, linesizes, src->data, src->linesize,
                       ctx->sw_format, ctx->width, ctx->height);

        ID3D12Resource_Unmap(s->staging_upload_buffer, 0, ശൂന്യ);

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_y_location, 0, 0, 0,
                                                    &staging_y_location, ശൂന്യ);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_uv_location, 0, 0, 0,
                                                    &staging_uv_location, ശൂന്യ);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);
        എങ്കിൽ (ret < 0)
            പോകുക fail;
    }

    hwctx->unlock(hwctx->lock_ctx);

    തിരികെ 0;

fail:
    hwctx->unlock(hwctx->lock_ctx);
    തിരികെ AVERROR(EINVAL);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d12va_load_functions(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv *priv = hwdev->hwctx;

#എങ്കിൽ !HAVE_UWP
    priv->d3d12lib = dlopen("d3d12.dll", 0);
    priv->dxgilib  = dlopen("dxgi.dll", 0);

    എങ്കിൽ (!priv->d3d12lib || !priv->dxgilib)
        പോകുക fail;

    priv->create_device = (PFN_D3D12_CREATE_DEVICE)GetProcAddress(priv->d3d12lib, "D3D12CreateDevice");
    എങ്കിൽ (!priv->create_device)
        പോകുക fail;

    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2)GetProcAddress(priv->dxgilib, "CreateDXGIFactory2");
    എങ്കിൽ (!priv->create_dxgi_factory2)
        പോകുക fail;

    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE)GetProcAddress(priv->d3d12lib, "D3D12GetDebugInterface");
#അല്ലെങ്കിൽ
    priv->create_device        = (PFN_D3D12_CREATE_DEVICE) D3D12CreateDevice;
    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2) CreateDXGIFactory2;
    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE) D3D12GetDebugInterface;
#endif
    തിരികെ 0;

#എങ്കിൽ !HAVE_UWP
fail:
    av_log(hwdev, AV_LOG_ERROR, "Failed to load D3D12 library or its functions\n");
    തിരികെ AVERROR_UNKNOWN;
#endif
}

സ്ഥിതം ശൂന്യം d3d12va_device_free(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    D3D12_OBJECT_RELEASE(ctx->device);

    എങ്കിൽ (priv->d3d12lib)
        dlclose(priv->d3d12lib);

    എങ്കിൽ (priv->dxgilib)
        dlclose(priv->dxgilib);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d12va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *ctx = hwdev->hwctx;

    എങ്കിൽ (!ctx->lock) {
        ctx->lock_ctx = CreateMutex(ശൂന്യ, 0, ശൂന്യ);
        എങ്കിൽ (ctx->lock_ctx == INVALID_HANDLE_മൂല്യം) {
            av_log(ശൂന്യ, AV_LOG_ERROR, "Failed to create a mutex\n");
            തിരികെ AVERROR(EINVAL);
        }
        ctx->lock   = d3d12va_default_lock;
        ctx->unlock = d3d12va_default_unlock;
    }

    എങ്കിൽ (!ctx->video_device)
        DX_CHECK(ID3D12Device_QueryInterface(ctx->device, &IID_ID3D12VideoDevice, (ശൂന്യം **)&ctx->video_device));

    തിരികെ 0;

fail:
    തിരികെ AVERROR(EINVAL);
}

സ്ഥിതം ശൂന്യം d3d12va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *device_hwctx = hwdev->hwctx;

    D3D12_OBJECT_RELEASE(device_hwctx->video_device);

    എങ്കിൽ (device_hwctx->lock == d3d12va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_മൂല്യം;
        device_hwctx->lock = ശൂന്യ;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ d3d12va_device_create(AVHWDeviceContext *hwdev, സ്ഥിരം അക്ഷരം *device,
                                 AVDictionary *opts, പൂർണ്ണസംഖ്യ flags)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    HRESULT hr;
    UINT create_flags = 0;
    IDXGIAdapter *pAdapter = ശൂന്യ;

    പൂർണ്ണസംഖ്യ ret;
    പൂർണ്ണസംഖ്യ is_debug = !!av_dict_get(opts, "debug", ശൂന്യ, 0);

    hwdev->സ്വതന്ത്രം = d3d12va_device_free;

    ret = d3d12va_load_functions(hwdev);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    എങ്കിൽ (is_debug) {
        ID3D12Debug *pDebug;
        എങ്കിൽ (priv->get_debug_interface && SUCCEEDED(priv->get_debug_interface(&IID_ID3D12Debug, (ശൂന്യം **)&pDebug))) {
            create_flags |= DXGI_CREATE_FACTORY_DEBUG;
            ID3D12Debug_EnableDebugLayer(pDebug);
            D3D12_OBJECT_RELEASE(pDebug);
            av_log(hwdev, AV_LOG_INFO, "D3D12 debug layer is enabled!\n");
        }
    }

    എങ്കിൽ (!ctx->device) {
        IDXGIFactory2 *pDXGIFactory = ശൂന്യ;

        hr = priv->create_dxgi_factory2(create_flags, &IID_IDXGIFactory2, (ശൂന്യം **)&pDXGIFactory);
        എങ്കിൽ (SUCCEEDED(hr)) {
            പൂർണ്ണസംഖ്യ adapter = device ? atoi(device) : 0;
            എങ്കിൽ (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = ശൂന്യ;
            IDXGIFactory2_Release(pDXGIFactory);
        }

        എങ്കിൽ (pAdapter) {
            DXGI_ADAPTER_DESC desc;
            hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
            എങ്കിൽ (!FAILED(hr)) {
                av_log(hwdev, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                       desc.VendorId, desc.DeviceId, desc.Description);
            }
        }

        hr = priv->create_device((IUnknown *)pAdapter, D3D_FEATURE_LEVEL_12_0, &IID_ID3D12Device, (ശൂന്യം **)&ctx->device);
        D3D12_OBJECT_RELEASE(pAdapter);
        എങ്കിൽ (FAILED(hr)) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create Direct 3D 12 device (%lx)\n", (long)hr);
            തിരികെ AVERROR_UNKNOWN;
        }
    }

    എങ്കിൽ (av_dict_get(opts, "UAV", ശൂന്യ, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    എങ്കിൽ (av_dict_get(opts, "RTV", ശൂന്യ, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

    എങ്കിൽ (av_dict_get(opts, "SHARED", ശൂന്യ, 0))
        ctx->heap_flags |= D3D12_HEAP_FLAG_SHARED;

    തിരികെ 0;
}

സ്ഥിരം HWContextType ff_hwcontext_type_d3d12va = {
    .type                   = AV_HWDEVICE_TYPE_D3D12VA,
    .name                   = "D3D12VA",

    .device_hwctx_size      = വലുപ്പം(D3D12VADevicePriv),
    .frames_hwctx_size      = വലുപ്പം(D3D12VAFramesContext),

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

    .pix_fmts               = (സ്ഥിരം എണ്ണൽ AVPixelFormat[]){ AV_PIX_FMT_D3D12, AV_PIX_FMT_NONE },
};
