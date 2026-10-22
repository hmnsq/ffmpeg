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

#समावेश "config.h"
#समावेश "common.h"
#समावेश "hwcontext.h"
#समावेश "hwcontext_internal.h"
#समावेश "hwcontext_d3d12va_internal.h"
#समावेश "hwcontext_d3d12va.h"
#समावेश "imgutils.h"
#समावेश "mem.h"
#समावेश "pixdesc.h"
#समावेश "pixfmt.h"
#समावेश "thread.h"
#समावेश "compat/w32dlfcn.h"
#समावेश <dxgi1_3.h>

प्रकार HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY2)(UINT Flags, REFIID riid, व्योम **ppFactory);

प्रकार काष्ठा D3D12VAFramesContext {
    /**
     * The public AVD3D12VAFramesContext. See hwcontext_d3d12va.h for it.
     */
    AVD3D12VAFramesContext p;

    ID3D12Resource            *staging_download_बफर;
    ID3D12Resource            *staging_upload_बफर;
    ID3D12CommandQueue        *command_queue;
    ID3D12CommandAllocator    *command_allocator;
    ID3D12GraphicsCommandList *command_list;
    AVD3D12VASyncContext       sync_ctx;
    UINT                       luma_component_आकार;
    पूर्णांक                        nb_surfaces_used;
} D3D12VAFramesContext;

प्रकार काष्ठा D3D12VADevicePriv {
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

अटल स्थिर काष्ठा {
    DXGI_FORMAT d3d_format;
    क्रमागत AVPixelFormat pix_fmt;
} supported_formats[] = {
    { DXGI_FORMAT_NV12, AV_PIX_FMT_NV12 },
    { DXGI_FORMAT_P010, AV_PIX_FMT_P010 },
    { DXGI_FORMAT_P016, AV_PIX_FMT_P012 },
};

अटल व्योम d3d12va_default_lock(व्योम *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

अटल व्योम d3d12va_default_unlock(व्योम *ctx)
{
    ReleaseMutex(ctx);
}

अटल पूर्णांक d3d12va_fence_completion(AVD3D12VASyncContext *psync_ctx)
{
    uint64_t completion = ID3_D12_Fence_Get_Completed_मूल्य(psync_ctx->fence);
    अगर (completion < psync_ctx->fence_मूल्य) {
        अगर (FAILED(ID3D12Fence_SetEventOnCompletion(psync_ctx->fence, psync_ctx->fence_मूल्य, psync_ctx->event)))
            वापस AVERROR(EINVAL);

        WaitForSingleObjectEx(psync_ctx->event, INFINITE, FALSE);
    }

    वापस 0;
}

अटल अंतरभूत पूर्णांक d3d12va_wait_queue_idle(AVD3D12VASyncContext *psync_ctx, ID3D12CommandQueue *command_queue)
{
    DX_CHECK(ID3D12CommandQueue_Signal(command_queue, psync_ctx->fence, ++psync_ctx->fence_मूल्य));
    वापस d3d12va_fence_completion(psync_ctx);

fail:
    वापस AVERROR(EINVAL);
}

अटल पूर्णांक d3d12va_create_staging_बफर_resource(AVHWFramesContext *ctx, D3D12_RESOURCE_STATES states,
                                                  ID3D12Resource **ppResource, पूर्णांक download)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    D3D12_HEAP_PROPERTIES props = { .Type = download ? D3D12_HEAP_TYPE_READBACK : D3D12_HEAP_TYPE_UPLOAD };
    D3D12_RESOURCE_DESC desc = {
        .Dimension          = D3_D12_RESOURCE_DIMENSION_बफर,
        .Alignment          = 0,
        .Width              = s->luma_component_आकार + (s->luma_component_आकार >> 1),
        .Height             = 1,
        .Depth_Or_Array_आकार   = 1,
        .MipLevels          = 1,
        .Format             = DXGI_FORMAT_UNKNOWN,
        .SampleDesc         = { .गिनती_2 = 1, .Quality = 0 },
        .Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
        .Flags              = D3D12_RESOURCE_FLAG_NONE,
    };

    अगर (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, D3D12_HEAP_FLAG_NONE, &desc,
        states, शून्य, &IID_ID3D12Resource, (व्योम **)ppResource))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging buffer resource\n");
        वापस AVERROR_UNKNOWN;
    }

    वापस 0;
}

अटल पूर्णांक d3d12va_create_helper_objects(AVHWFramesContext *ctx)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *frames_hwctx = &s->p;

    D3D12_COMMAND_QUEUE_DESC queue_desc = {
        .Type     = D3D12_COMMAND_LIST_TYPE_COPY,
        .Priority = 0,
        .गाँठ_Mask = 0,
    };

    s->luma_component_आकार = FFALIGN(ctx->width * (frames_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                                     D3_D12_TEXTURE_तथ्य_PITCH_ALIGNMENT) * ctx->height;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (व्योम **)&s->sync_ctx.fence));

    s->sync_ctx.event = CreateEvent(शून्य, FALSE, FALSE, शून्य);
    अगर (!s->sync_ctx.event)
        जाओ fail;

    DX_CHECK(ID3D12Device_CreateCommandQueue(device_hwctx->device, &queue_desc,
             &IID_ID3D12CommandQueue, (व्योम **)&s->command_queue));

    DX_CHECK(ID3D12Device_CreateCommandAllocator(device_hwctx->device, queue_desc.Type,
             &IID_ID3D12CommandAllocator, (व्योम **)&s->command_allocator));

    DX_CHECK(ID3D12Device_CreateCommandList(device_hwctx->device, 0, queue_desc.Type,
             s->command_allocator, शून्य, &IID_ID3D12GraphicsCommandList, (व्योम **)&s->command_list));

    DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

    ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

    वापस d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);

fail:
    वापस AVERROR(EINVAL);
}

अटल व्योम d3d12va_frames_uninit(AVHWFramesContext *ctx)
{
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;

    D3D12_OBJECT_RELEASE(s->sync_ctx.fence);
    अगर (s->sync_ctx.event)
        CloseHandle(s->sync_ctx.event);

    D3D12_OBJECT_RELEASE(s->staging_download_बफर);
    D3D12_OBJECT_RELEASE(s->staging_upload_बफर);
    D3D12_OBJECT_RELEASE(s->command_allocator);
    D3D12_OBJECT_RELEASE(s->command_list);
    D3D12_OBJECT_RELEASE(s->command_queue);

    अगर (hwctx->texture_array)
        D3D12_OBJECT_RELEASE(hwctx->texture_array);
}

अटल पूर्णांक d3d12va_frames_get_constraints(AVHWDeviceContext *ctx, स्थिर व्योम *hwconfig, AVHWFramesConstraints *constraints)
{
    HRESULT hr;
    पूर्णांक nb_sw_formats = 0;
    AVD3D12VADeviceContext *device_hwctx = ctx->hwctx;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    माप(*constraints->valid_sw_formats));
    अगर (!constraints->valid_sw_formats)
        वापस AVERROR(ENOMEM);

    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        D3_D12_FEATURE_तथ्य_FORMAT_SUPPORT format_support = { supported_formats[i].d3d_format };
        hr = ID3D12Device_CheckFeatureSupport(device_hwctx->device, D3D12_FEATURE_FORMAT_SUPPORT, &format_support, माप(format_support));
        अगर (SUCCEEDED(hr) && (format_support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, माप(*constraints->valid_hw_formats));
    अगर (!constraints->valid_hw_formats)
        वापस AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D12;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    वापस 0;
}

अटल व्योम free_texture(व्योम *opaque, uint8_t *तथ्य)
{
    AVD3D12VAFrame *frame = (AVD3D12VAFrame *)तथ्य;

    अगर (!(frame->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY))
        D3D12_OBJECT_RELEASE(frame->texture);

    D3D12_OBJECT_RELEASE(frame->sync_ctx.fence);
    अगर (frame->sync_ctx.event)
        CloseHandle(frame->sync_ctx.event);

    av_freep(&तथ्य);
}

अटल AVBufferRef *d3d12va_pool_alloc_texture_array(AVHWFramesContext *ctx)
{
    AVD3D12VAFrame         *frame  = av_mallocz(माप(*frame));
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    AVBufferRef *buf;

    frame->flags |= AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (व्योम **)&frame->sync_ctx.fence));
    frame->sync_ctx.event = CreateEvent(शून्य, FALSE, FALSE, शून्य);
    अगर (!frame->sync_ctx.event)
        जाओ fail;

    अगर (s->nb_surfaces_used >= ctx->initial_pool_आकार) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        जाओ fail;
    }

    frame->texture = hwctx->texture_array;
    frame->subresource_सूचकांक = s->nb_surfaces_used;

    buf = av_बफर_create((uint8_t *)frame, माप(*frame), free_texture, शून्य, 0);

    अगर (!buf)
        जाओ fail;

    s->nb_surfaces_used++;
    वापस buf;
fail:
    free_texture(शून्य, (uint8_t *)frame);
    वापस शून्य;
}

अटल AVBufferRef *d3d12va_pool_alloc(व्योम *opaque, माप_प्रकार आकार)
{
    AVHWFramesContext      *ctx          = (AVHWFramesContext *)opaque;
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    AVBufferRef *buf;
    AVD3D12VAFrame *frame;

    अगर (ctx->initial_pool_आकार > 0 && hwctx->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY)
        वापस d3d12va_pool_alloc_texture_array(ctx);

    D3D12_HEAP_PROPERTIES props = { .Type = D3D12_HEAP_TYPE_DEFAULT };
    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .Width            = ctx->width,
        .Height           = ctx->height,
        .Depth_Or_Array_आकार = 1,
        .MipLevels        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.गिनती_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    frame = av_mallocz(माप(AVD3D12VAFrame));
    अगर (!frame)
        वापस शून्य;

    अगर (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->heap_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, शून्य, &IID_ID3D12Resource, (व्योम **)&frame->texture))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture\n");
        जाओ fail;
    }

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (व्योम **)&frame->sync_ctx.fence));

    frame->sync_ctx.event = CreateEvent(शून्य, FALSE, FALSE, शून्य);
    अगर (!frame->sync_ctx.event)
        जाओ fail;

    buf = av_बफर_create((uint8_t *)frame, माप(*frame), free_texture, शून्य, 0);
    अगर (!buf)
        जाओ fail;

    वापस buf;

fail:
    free_texture(शून्य, (uint8_t *)frame);
    वापस शून्य;
}

अटल पूर्णांक d3d12va_texture_array_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    D3D12_HEAP_PROPERTIES props = { .Type = D3D12_HEAP_TYPE_DEFAULT };

    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .Width            = ctx->width,
        .Height           = ctx->height,
        .Depth_Or_Array_आकार = ctx->initial_pool_आकार,
        .MipLevels        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.गिनती_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    अगर (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->heap_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, शून्य, &IID_ID3D12Resource, (व्योम **)&hwctx->texture_array))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture array\n");
        वापस AVERROR(EINVAL);
    }
    वापस 0;
}

अटल पूर्णांक d3d12va_frames_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    पूर्णांक i;

    क्रम (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        अगर (ctx->sw_format == supported_formats[i].pix_fmt) {
            अगर (hwctx->format != DXGI_FORMAT_UNKNOWN &&
                hwctx->format != supported_formats[i].d3d_format)
                av_log(ctx, AV_LOG_WARNING, "Incompatible DXGI format provided by user, will be overided\n");
            hwctx->format = supported_formats[i].d3d_format;
            अवरोध;
        }
    }

    अगर (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        वापस AVERROR(EINVAL);
    }

    hwctx->resource_flags |= device_hwctx->resource_flags;
    hwctx->heap_flags     |= device_hwctx->heap_flags;

    अगर (ctx->initial_pool_आकार > 0 && hwctx->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY) {
        पूर्णांक err = d3d12va_texture_array_init(ctx);
        अगर (err < 0)
            वापस err;
    }

    ffhwframesctx(ctx)->pool_internal = av_बफर_pool_init2(माप(AVD3D12VAFrame),
        ctx, d3d12va_pool_alloc, शून्य);

    अगर (!ffhwframesctx(ctx)->pool_internal)
        वापस AVERROR(ENOMEM);

    वापस 0;
}

अटल पूर्णांक d3d12va_get_बफर(AVHWFramesContext *ctx, AVFrame *frame)
{
    पूर्णांक ret;

    frame->buf[0] = av_बफर_pool_get(ctx->pool);
    अगर (!frame->buf[0])
        वापस AVERROR(ENOMEM);

    ret = av_image_fill_arrays(frame->तथ्य, frame->linesize, शून्य,
                               ctx->sw_format, ctx->width, ctx->height,
                               D3_D12_TEXTURE_तथ्य_PITCH_ALIGNMENT);
    अगर (ret < 0)
        वापस ret;

    frame->तथ्य[0] = frame->buf[0]->तथ्य;
    frame->format  = AV_PIX_FMT_D3D12;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    वापस 0;
}

अटल पूर्णांक d3d12va_transfer_get_formats(AVHWFramesContext *ctx,
                                        क्रमागत AVHWFrameTransferDirection dir,
                                        क्रमागत AVPixelFormat **formats)
{
    क्रमागत AVPixelFormat *fmts;

    fmts = av_malloc_array(2, माप(*fmts));
    अगर (!fmts)
        वापस AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    वापस 0;
}

अटल पूर्णांक d3d12va_transfer_तथ्य(AVHWFramesContext *ctx, AVFrame *dst,
                                 स्थिर AVFrame *src)
{
    AVD3D12VADeviceContext *hwctx        = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *frames_hwctx = &s->p;

    पूर्णांक ret;
    पूर्णांक download = src->format == AV_PIX_FMT_D3D12;
    स्थिर AVFrame *frame = download ? src : dst;
    स्थिर AVFrame *other = download ? dst : src;

    AVD3D12VAFrame *f = (AVD3D12VAFrame *)frame->तथ्य[0];
    ID3D12Resource *texture = (ID3D12Resource *)f->texture;

    uint8_t *mapped_तथ्य;
    uint8_t *तथ्य[4];
    पूर्णांक linesizes[4];

    D3D12_TEXTURE_COPY_LOCATION staging_y_location  = { 0 };
    D3D12_TEXTURE_COPY_LOCATION staging_uv_location = { 0 };

    D3D12_TEXTURE_COPY_LOCATION texture_y_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_सूचकांक,
        .Subresource_सूचकांक = 0,
    };

    D3D12_TEXTURE_COPY_LOCATION texture_uv_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_सूचकांक,
        .Subresource_सूचकांक = 1,
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

    अगर (frame->hw_frames_ctx->तथ्य != (uint8_t *)ctx || other->format != ctx->sw_format)
        वापस AVERROR(EINVAL);

    hwctx->lock(hwctx->lock_ctx);

    अगर (!s->command_queue) {
        ret = d3d12va_create_helper_objects(ctx);
        अगर (ret < 0)
            जाओ fail;
    }

    क्रम (पूर्णांक i = 0; i < 4; i++)
        linesizes[i] = FFALIGN(frame->width * (frames_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                               D3_D12_TEXTURE_तथ्य_PITCH_ALIGNMENT);

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
            .Offset = s->luma_component_आकार,
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

    DX_CHECK(ID3D12GraphicsCommandList_Reset(s->command_list, s->command_allocator, शून्य));

    अगर (download) {
        अगर (!s->staging_download_बफर) {
            ret = d3d12va_create_staging_बफर_resource(ctx, D3D12_RESOURCE_STATE_COPY_DEST,
                                                         &s->staging_download_बफर, 1);
            अगर (ret < 0) {
                जाओ fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_download_बफर;

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_y_location, 0, 0, 0,
                                                    &texture_y_location, शून्य);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_uv_location, 0, 0, 0,
                                                    &texture_uv_location, शून्य);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        DX_CHECK(ID3D12CommandQueue_Wait(s->command_queue, f->sync_ctx.fence, f->sync_ctx.fence_मूल्य));

        ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);
        अगर (ret < 0)
            जाओ fail;

        DX_CHECK(ID3D12Resource_Map(s->staging_download_बफर, 0, शून्य, (व्योम **)&mapped_तथ्य));
        av_image_fill_pointers(तथ्य, ctx->sw_format, ctx->height, mapped_तथ्य, linesizes);

        av_image_copy2(dst->तथ्य, dst->linesize, तथ्य, linesizes,
                       ctx->sw_format, ctx->width, ctx->height);

        ID3D12Resource_Unmap(s->staging_download_बफर, 0, शून्य);
    } अन्यथा {
        अगर (!s->staging_upload_बफर) {
            ret = d3d12va_create_staging_बफर_resource(ctx, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                        &s->staging_upload_बफर, 0);
            अगर (ret < 0) {
                जाओ fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_upload_बफर;

        DX_CHECK(ID3D12Resource_Map(s->staging_upload_बफर, 0, शून्य, (व्योम **)&mapped_तथ्य));
        av_image_fill_pointers(तथ्य, ctx->sw_format, ctx->height, mapped_तथ्य, linesizes);

        av_image_copy2(तथ्य, linesizes, src->तथ्य, src->linesize,
                       ctx->sw_format, ctx->width, ctx->height);

        ID3D12Resource_Unmap(s->staging_upload_बफर, 0, शून्य);

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_y_location, 0, 0, 0,
                                                    &staging_y_location, शून्य);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_uv_location, 0, 0, 0,
                                                    &staging_uv_location, शून्य);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);
        अगर (ret < 0)
            जाओ fail;
    }

    hwctx->unlock(hwctx->lock_ctx);

    वापस 0;

fail:
    hwctx->unlock(hwctx->lock_ctx);
    वापस AVERROR(EINVAL);
}

अटल पूर्णांक d3d12va_load_functions(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv *priv = hwdev->hwctx;

#अगर !HAVE_UWP
    priv->d3d12lib = dlopen("d3d12.dll", 0);
    priv->dxgilib  = dlopen("dxgi.dll", 0);

    अगर (!priv->d3d12lib || !priv->dxgilib)
        जाओ fail;

    priv->create_device = (PFN_D3D12_CREATE_DEVICE)GetProcAddress(priv->d3d12lib, "D3D12CreateDevice");
    अगर (!priv->create_device)
        जाओ fail;

    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2)GetProcAddress(priv->dxgilib, "CreateDXGIFactory2");
    अगर (!priv->create_dxgi_factory2)
        जाओ fail;

    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE)GetProcAddress(priv->d3d12lib, "D3D12GetDebugInterface");
#अन्यथा
    priv->create_device        = (PFN_D3D12_CREATE_DEVICE) D3D12CreateDevice;
    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2) CreateDXGIFactory2;
    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE) D3D12GetDebugInterface;
#पूर्ण_अगर
    वापस 0;

#अगर !HAVE_UWP
fail:
    av_log(hwdev, AV_LOG_ERROR, "Failed to load D3D12 library or its functions\n");
    वापस AVERROR_UNKNOWN;
#पूर्ण_अगर
}

अटल व्योम d3d12va_device_free(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    D3D12_OBJECT_RELEASE(ctx->device);

    अगर (priv->d3d12lib)
        dlclose(priv->d3d12lib);

    अगर (priv->dxgilib)
        dlclose(priv->dxgilib);
}

अटल पूर्णांक d3d12va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *ctx = hwdev->hwctx;

    अगर (!ctx->lock) {
        ctx->lock_ctx = CreateMutex(शून्य, 0, शून्य);
        अगर (ctx->lock_ctx == INVALID_HANDLE_मूल्य) {
            av_log(शून्य, AV_LOG_ERROR, "Failed to create a mutex\n");
            वापस AVERROR(EINVAL);
        }
        ctx->lock   = d3d12va_default_lock;
        ctx->unlock = d3d12va_default_unlock;
    }

    अगर (!ctx->video_device)
        DX_CHECK(ID3D12Device_QueryInterface(ctx->device, &IID_ID3D12VideoDevice, (व्योम **)&ctx->video_device));

    वापस 0;

fail:
    वापस AVERROR(EINVAL);
}

अटल व्योम d3d12va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *device_hwctx = hwdev->hwctx;

    D3D12_OBJECT_RELEASE(device_hwctx->video_device);

    अगर (device_hwctx->lock == d3d12va_default_lock) {
        CloseHandle(device_hwctx->lock_ctx);
        device_hwctx->lock_ctx = INVALID_HANDLE_मूल्य;
        device_hwctx->lock = शून्य;
    }
}

अटल पूर्णांक d3d12va_device_create(AVHWDeviceContext *hwdev, स्थिर अक्षर *device,
                                 AVDictionary *opts, पूर्णांक flags)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    HRESULT hr;
    UINT create_flags = 0;
    IDXGIAdapter *pAdapter = शून्य;

    पूर्णांक ret;
    पूर्णांक is_debug = !!av_dict_get(opts, "debug", शून्य, 0);

    hwdev->मुक्त = d3d12va_device_free;

    ret = d3d12va_load_functions(hwdev);
    अगर (ret < 0)
        वापस ret;

    अगर (is_debug) {
        ID3D12Debug *pDebug;
        अगर (priv->get_debug_interface && SUCCEEDED(priv->get_debug_interface(&IID_ID3D12Debug, (व्योम **)&pDebug))) {
            create_flags |= DXGI_CREATE_FACTORY_DEBUG;
            ID3D12Debug_EnableDebugLayer(pDebug);
            D3D12_OBJECT_RELEASE(pDebug);
            av_log(hwdev, AV_LOG_INFO, "D3D12 debug layer is enabled!\n");
        }
    }

    अगर (!ctx->device) {
        IDXGIFactory2 *pDXGIFactory = शून्य;

        hr = priv->create_dxgi_factory2(create_flags, &IID_IDXGIFactory2, (व्योम **)&pDXGIFactory);
        अगर (SUCCEEDED(hr)) {
            पूर्णांक adapter = device ? म_से_प(device) : 0;
            अगर (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = शून्य;
            IDXGIFactory2_Release(pDXGIFactory);
        }

        अगर (pAdapter) {
            DXGI_ADAPTER_DESC desc;
            hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
            अगर (!FAILED(hr)) {
                av_log(hwdev, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                       desc.VendorId, desc.DeviceId, desc.Description);
            }
        }

        hr = priv->create_device((IUnknown *)pAdapter, D3D_FEATURE_LEVEL_12_0, &IID_ID3D12Device, (व्योम **)&ctx->device);
        D3D12_OBJECT_RELEASE(pAdapter);
        अगर (FAILED(hr)) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create Direct 3D 12 device (%lx)\n", (दीर्घ)hr);
            वापस AVERROR_UNKNOWN;
        }
    }

    अगर (av_dict_get(opts, "UAV", शून्य, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    अगर (av_dict_get(opts, "RTV", शून्य, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

    अगर (av_dict_get(opts, "SHARED", शून्य, 0))
        ctx->heap_flags |= D3D12_HEAP_FLAG_SHARED;

    वापस 0;
}

स्थिर HWContextType ff_hwcontext_type_d3d12va = {
    .type                   = AV_HWDEVICE_TYPE_D3D12VA,
    .name                   = "D3D12VA",

    .device_hwctx_आकार      = माप(D3D12VADevicePriv),
    .frames_hwctx_आकार      = माप(D3D12VAFramesContext),

    .device_create          = d3d12va_device_create,
    .device_init            = d3d12va_device_init,
    .device_uninit          = d3d12va_device_uninit,
    .frames_get_constraints = d3d12va_frames_get_constraints,
    .frames_init            = d3d12va_frames_init,
    .frames_uninit          = d3d12va_frames_uninit,
    .frames_get_बफर      = d3d12va_get_बफर,
    .transfer_get_formats   = d3d12va_transfer_get_formats,
    .transfer_तथ्य_to       = d3d12va_transfer_तथ्य,
    .transfer_तथ्य_from     = d3d12va_transfer_तथ्य,

    .pix_fmts               = (स्थिर क्रमागत AVPixelFormat[]){ AV_PIX_FMT_D3D12, AV_PIX_FMT_NONE },
};
