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

#अन्तर्भाव "config.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "hwcontext_d3d12va_internal.h"
#अन्तर्भाव "hwcontext_d3d12va.h"
#अन्तर्भाव "imgutils.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "thread.h"
#अन्तर्भाव "compat/w32dlfcn.h"
#अन्तर्भाव <dxgi1_3.h>

प्रकारनिर्देश HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY2)(UINT Flags, REFIID riid, शून्य **ppFactory);

प्रकारनिर्देश संरचना D3D12VAFramesContext {
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
    पूर्णाङ्क                        nb_surfaces_प्रयुक्तम्;
} D3D12VAFramesContext;

प्रकारनिर्देश संरचना D3D12VADevicePriv {
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

स्थिर ध्रुव संरचना {
    DXGI_FORMAT d3d_format;
    गणना AVPixelFormat pix_fmt;
} supported_formats[] = {
    { DXGI_FORMAT_NV12, AV_PIX_FMT_NV12 },
    { DXGI_FORMAT_P010, AV_PIX_FMT_P010 },
    { DXGI_FORMAT_P016, AV_PIX_FMT_P012 },
};

स्थिर शून्य d3d12va_default_तालकम्(शून्य *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

स्थिर शून्य d3d12va_default_unlock(शून्य *ctx)
{
    ReleaseMutex(ctx);
}

स्थिर पूर्णाङ्क d3d12va_fence_completion(AVD3D12VASyncContext *psync_ctx)
{
    uint64_t completion = ID3_D12_Fence_Get_Completed_मानम्(psync_ctx->fence);
    यदि (completion < psync_ctx->fence_मानम्) {
        यदि (FAILED(ID3_D12_Fence_समुच्चयः_Event_On_Completion(psync_ctx->fence, psync_ctx->fence_मानम्, psync_ctx->event)))
            प्रत्यागम AVERROR(EINVAL);

        WaitForSingleObjectEx(psync_ctx->event, INFINITE, FALSE);
    }

    प्रत्यागम 0;
}

स्थिर अन्तःस्थ पूर्णाङ्क d3d12va_wait_queue_idle(AVD3D12VASyncContext *psync_ctx, ID3D12CommandQueue *command_queue)
{
    DX_CHECK(ID3D12CommandQueue_Signal(command_queue, psync_ctx->fence, ++psync_ctx->fence_मानम्));
    प्रत्यागम d3d12va_fence_completion(psync_ctx);

fail:
    प्रत्यागम AVERROR(EINVAL);
}

स्थिर पूर्णाङ्क d3d12va_create_staging_बफर_resource(AVHWFramesContext *ctx, D3_D12_RESOURCE_अवस्थाः अवस्थाः,
                                                  ID3D12Resource **ppResource, पूर्णाङ्क download)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    D3D12_HEAP_PROPERTIES props = { .Type = download ? D3D12_HEAP_TYPE_READBACK : D3D12_HEAP_TYPE_UPLOAD };
    D3D12_RESOURCE_DESC desc = {
        .Dimension          = D3_D12_RESOURCE_DIMENSION_बफर,
        .Alignment          = 0,
        .विस्तारः_2              = s->luma_component_आकार + (s->luma_component_आकार >> 1),
        .Height             = 1,
        .गभीरता_Or_Array_आकार   = 1,
        .Mip_स्तराः          = 1,
        .Format             = DXGI_FORMAT_UNKNOWN,
        .SampleDesc         = { .गणनम्_2 = 1, .Quality = 0 },
        .Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
        .Flags              = D3D12_RESOURCE_FLAG_NONE,
    };

    यदि (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, D3D12_HEAP_FLAG_NONE, &desc,
        अवस्थाः, रिक्त, &IID_ID3D12Resource, (शून्य **)ppResource))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging buffer resource\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क d3d12va_create_helper_objects(AVHWFramesContext *ctx)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *चौकटाः_hwctx = &s->p;

    D3D12_COMMAND_QUEUE_DESC queue_desc = {
        .Type     = D3D12_COMMAND_LIST_TYPE_COPY,
        .प्राथमिकता = 0,
        .ग्रन्थिः_आवरणम् = 0,
    };

    s->luma_component_आकार = FFALIGN(ctx->विस्तारः * (चौकटाः_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                                     D3_D12_TEXTURE_दत्त_PITCH_ALIGNMENT) * ctx->height;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (शून्य **)&s->sync_ctx.fence));

    s->sync_ctx.event = CreateEvent(रिक्त, FALSE, FALSE, रिक्त);
    यदि (!s->sync_ctx.event)
        गच्छ fail;

    DX_CHECK(ID3D12Device_CreateCommandQueue(device_hwctx->device, &queue_desc,
             &IID_ID3D12CommandQueue, (शून्य **)&s->command_queue));

    DX_CHECK(ID3D12Device_CreateCommandAllocator(device_hwctx->device, queue_desc.Type,
             &IID_ID3D12CommandAllocator, (शून्य **)&s->command_allocator));

    DX_CHECK(ID3D12Device_CreateCommandList(device_hwctx->device, 0, queue_desc.Type,
             s->command_allocator, रिक्त, &IID_ID3D12GraphicsCommandList, (शून्य **)&s->command_list));

    DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

    ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

    प्रत्यागम d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);

fail:
    प्रत्यागम AVERROR(EINVAL);
}

स्थिर शून्य d3d12va_चौकटाः_uninit(AVHWFramesContext *ctx)
{
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;

    D3D12_OBJECT_RELEASE(s->sync_ctx.fence);
    यदि (s->sync_ctx.event)
        CloseHandle(s->sync_ctx.event);

    D3D12_OBJECT_RELEASE(s->staging_download_बफर);
    D3D12_OBJECT_RELEASE(s->staging_upload_बफर);
    D3D12_OBJECT_RELEASE(s->command_allocator);
    D3D12_OBJECT_RELEASE(s->command_list);
    D3D12_OBJECT_RELEASE(s->command_queue);

    यदि (hwctx->texture_array)
        D3D12_OBJECT_RELEASE(hwctx->texture_array);
}

स्थिर पूर्णाङ्क d3d12va_चौकटाः_get_constraints(AVHWDeviceContext *ctx, ध्रुव शून्य *hwconfig, AVHWFramesConstraints *constraints)
{
    HRESULT hr;
    पूर्णाङ्क nb_sw_formats = 0;
    AVD3D12VADeviceContext *device_hwctx = ctx->hwctx;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    परिमाण(*constraints->valid_sw_formats));
    यदि (!constraints->valid_sw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        D3_D12_FEATURE_दत्त_FORMAT_SUPPORT format_support = { supported_formats[i].d3d_format };
        hr = ID3D12Device_CheckFeatureSupport(device_hwctx->device, D3D12_FEATURE_FORMAT_SUPPORT, &format_support, परिमाण(format_support));
        यदि (SUCCEEDED(hr) && (format_support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, परिमाण(*constraints->valid_hw_formats));
    यदि (!constraints->valid_hw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D12;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    प्रत्यागम 0;
}

स्थिर शून्य free_texture(शून्य *opaque, uint8_t *दत्त)
{
    AVD3D12VAFrame *frame = (AVD3D12VAFrame *)दत्त;

    यदि (!(frame->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY))
        D3D12_OBJECT_RELEASE(frame->texture);

    D3D12_OBJECT_RELEASE(frame->sync_ctx.fence);
    यदि (frame->sync_ctx.event)
        CloseHandle(frame->sync_ctx.event);

    av_freep(&दत्त);
}

स्थिर AVBufferRef *d3d12va_pool_alloc_texture_array(AVHWFramesContext *ctx)
{
    AVD3D12VAFrame         *frame  = av_mallocz(परिमाण(*frame));
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    AVBufferRef *buf;

    frame->flags |= AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (शून्य **)&frame->sync_ctx.fence));
    frame->sync_ctx.event = CreateEvent(रिक्त, FALSE, FALSE, रिक्त);
    यदि (!frame->sync_ctx.event)
        गच्छ fail;

    यदि (s->nb_surfaces_प्रयुक्तम् >= ctx->initial_pool_आकार) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        गच्छ fail;
    }

    frame->texture = hwctx->texture_array;
    frame->subresource_सूचकांक = s->nb_surfaces_प्रयुक्तम्;

    buf = av_बफर_create((uint8_t *)frame, परिमाण(*frame), free_texture, रिक्त, 0);

    यदि (!buf)
        गच्छ fail;

    s->nb_surfaces_प्रयुक्तम्++;
    प्रत्यागम buf;
fail:
    free_texture(रिक्त, (uint8_t *)frame);
    प्रत्यागम रिक्त;
}

स्थिर AVBufferRef *d3d12va_pool_alloc(शून्य *opaque, size_t आकार)
{
    AVHWFramesContext      *ctx          = (AVHWFramesContext *)opaque;
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    AVBufferRef *buf;
    AVD3D12VAFrame *frame;

    यदि (ctx->initial_pool_आकार > 0 && hwctx->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY)
        प्रत्यागम d3d12va_pool_alloc_texture_array(ctx);

    D3D12_HEAP_PROPERTIES props = { .Type = D3D12_HEAP_TYPE_DEFAULT };
    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .विस्तारः_2            = ctx->विस्तारः,
        .Height           = ctx->height,
        .गभीरता_Or_Array_आकार = 1,
        .Mip_स्तराः        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.गणनम्_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    frame = av_mallocz(परिमाण(AVD3D12VAFrame));
    यदि (!frame)
        प्रत्यागम रिक्त;

    यदि (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->heap_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, रिक्त, &IID_ID3D12Resource, (शून्य **)&frame->texture))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture\n");
        गच्छ fail;
    }

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (शून्य **)&frame->sync_ctx.fence));

    frame->sync_ctx.event = CreateEvent(रिक्त, FALSE, FALSE, रिक्त);
    यदि (!frame->sync_ctx.event)
        गच्छ fail;

    buf = av_बफर_create((uint8_t *)frame, परिमाण(*frame), free_texture, रिक्त, 0);
    यदि (!buf)
        गच्छ fail;

    प्रत्यागम buf;

fail:
    free_texture(रिक्त, (uint8_t *)frame);
    प्रत्यागम रिक्त;
}

स्थिर पूर्णाङ्क d3d12va_texture_array_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    D3D12_HEAP_PROPERTIES props = { .Type = D3D12_HEAP_TYPE_DEFAULT };

    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .विस्तारः_2            = ctx->विस्तारः,
        .Height           = ctx->height,
        .गभीरता_Or_Array_आकार = ctx->initial_pool_आकार,
        .Mip_स्तराः        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.गणनम्_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    यदि (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->heap_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, रिक्त, &IID_ID3D12Resource, (शून्य **)&hwctx->texture_array))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture array\n");
        प्रत्यागम AVERROR(EINVAL);
    }
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क d3d12va_चौकटाः_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    पूर्णाङ्क i;

    प्रति (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        यदि (ctx->sw_format == supported_formats[i].pix_fmt) {
            यदि (hwctx->format != DXGI_FORMAT_UNKNOWN &&
                hwctx->format != supported_formats[i].d3d_format)
                av_log(ctx, AV_LOG_WARNING, "Incompatible DXGI format provided by user, will be overided\n");
            hwctx->format = supported_formats[i].d3d_format;
            भङ्ग;
        }
    }

    यदि (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        प्रत्यागम AVERROR(EINVAL);
    }

    hwctx->resource_flags |= device_hwctx->resource_flags;
    hwctx->heap_flags     |= device_hwctx->heap_flags;

    यदि (ctx->initial_pool_आकार > 0 && hwctx->flags & AV_D3D12VA_FRAME_FLAG_TEXTURE_ARRAY) {
        पूर्णाङ्क err = d3d12va_texture_array_init(ctx);
        यदि (err < 0)
            प्रत्यागम err;
    }

    ffhwframesctx(ctx)->pool_आन्तरिकम् = av_बफर_pool_init2(परिमाण(AVD3D12VAFrame),
        ctx, d3d12va_pool_alloc, रिक्त);

    यदि (!ffhwframesctx(ctx)->pool_आन्तरिकम्)
        प्रत्यागम AVERROR(ENOMEM);

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क d3d12va_get_बफर(AVHWFramesContext *ctx, AVFrame *frame)
{
    पूर्णाङ्क ret;

    frame->buf[0] = av_बफर_pool_get(ctx->pool);
    यदि (!frame->buf[0])
        प्रत्यागम AVERROR(ENOMEM);

    ret = av_image_fill_arrays(frame->दत्त, frame->linesize, रिक्त,
                               ctx->sw_format, ctx->विस्तारः, ctx->height,
                               D3_D12_TEXTURE_दत्त_PITCH_ALIGNMENT);
    यदि (ret < 0)
        प्रत्यागम ret;

    frame->दत्त[0] = frame->buf[0]->दत्त;
    frame->format  = AV_PIX_FMT_D3D12;
    frame->विस्तारः   = ctx->विस्तारः;
    frame->height  = ctx->height;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क d3d12va_transfer_get_formats(AVHWFramesContext *ctx,
                                        गणना AVHWFrameTransferDirection dir,
                                        गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts;

    fmts = av_malloc_array(2, परिमाण(*fmts));
    यदि (!fmts)
        प्रत्यागम AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क d3d12va_transfer_दत्त(AVHWFramesContext *ctx, AVFrame *dst,
                                 ध्रुव AVFrame *src)
{
    AVD3D12VADeviceContext *hwctx        = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *चौकटाः_hwctx = &s->p;

    पूर्णाङ्क ret;
    पूर्णाङ्क download = src->format == AV_PIX_FMT_D3D12;
    ध्रुव AVFrame *frame = download ? src : dst;
    ध्रुव AVFrame *other = download ? dst : src;

    AVD3D12VAFrame *f = (AVD3D12VAFrame *)frame->दत्त[0];
    ID3D12Resource *texture = (ID3D12Resource *)f->texture;

    uint8_t *mapped_दत्त;
    uint8_t *दत्त[4];
    पूर्णाङ्क linesizes[4];

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

    यदि (frame->hw_चौकटाः_ctx->दत्त != (uint8_t *)ctx || other->format != ctx->sw_format)
        प्रत्यागम AVERROR(EINVAL);

    hwctx->तालकम्(hwctx->तालकम्_ctx);

    यदि (!s->command_queue) {
        ret = d3d12va_create_helper_objects(ctx);
        यदि (ret < 0)
            गच्छ fail;
    }

    प्रति (पूर्णाङ्क i = 0; i < 4; i++)
        linesizes[i] = FFALIGN(frame->विस्तारः * (चौकटाः_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                               D3_D12_TEXTURE_दत्त_PITCH_ALIGNMENT);

    staging_y_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .विस्थापनम्_4 = 0,
            .Footprint = {
                .Format   = चौकटाः_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16_UNORM : DXGI_FORMAT_R8_UNORM,
                .विस्तारः_2    = ctx->विस्तारः,
                .Height   = ctx->height,
                .गभीरता_2    = 1,
                .RowPitch = linesizes[0],
            },
        },
    };

    staging_uv_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .विस्थापनम्_4 = s->luma_component_आकार,
            .Footprint = {
                .Format   = चौकटाः_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16G16_UNORM : DXGI_FORMAT_R8G8_UNORM,
                .विस्तारः_2    = ctx->विस्तारः  >> 1,
                .Height   = ctx->height >> 1,
                .गभीरता_2    = 1,
                .RowPitch = linesizes[0],
            },
        },
    };

    DX_CHECK(ID3D12CommandAllocator_Reset(s->command_allocator));

    DX_CHECK(ID3D12GraphicsCommandList_Reset(s->command_list, s->command_allocator, रिक्त));

    यदि (download) {
        यदि (!s->staging_download_बफर) {
            ret = d3d12va_create_staging_बफर_resource(ctx, D3D12_RESOURCE_STATE_COPY_DEST,
                                                         &s->staging_download_बफर, 1);
            यदि (ret < 0) {
                गच्छ fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_download_बफर;

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_y_location, 0, 0, 0,
                                                    &texture_y_location, रिक्त);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_uv_location, 0, 0, 0,
                                                    &texture_uv_location, रिक्त);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        DX_CHECK(ID3D12CommandQueue_Wait(s->command_queue, f->sync_ctx.fence, f->sync_ctx.fence_मानम्));

        ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);
        यदि (ret < 0)
            गच्छ fail;

        DX_CHECK(ID3D12Resource_Map(s->staging_download_बफर, 0, रिक्त, (शून्य **)&mapped_दत्त));
        av_image_fill_सूचकाः(दत्त, ctx->sw_format, ctx->height, mapped_दत्त, linesizes);

        av_image_copy2(dst->दत्त, dst->linesize, दत्त, linesizes,
                       ctx->sw_format, ctx->विस्तारः, ctx->height);

        ID3D12Resource_Unmap(s->staging_download_बफर, 0, रिक्त);
    } अन्यथा {
        यदि (!s->staging_upload_बफर) {
            ret = d3d12va_create_staging_बफर_resource(ctx, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                        &s->staging_upload_बफर, 0);
            यदि (ret < 0) {
                गच्छ fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_upload_बफर;

        DX_CHECK(ID3D12Resource_Map(s->staging_upload_बफर, 0, रिक्त, (शून्य **)&mapped_दत्त));
        av_image_fill_सूचकाः(दत्त, ctx->sw_format, ctx->height, mapped_दत्त, linesizes);

        av_image_copy2(दत्त, linesizes, src->दत्त, src->linesize,
                       ctx->sw_format, ctx->विस्तारः, ctx->height);

        ID3D12Resource_Unmap(s->staging_upload_बफर, 0, रिक्त);

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_y_location, 0, 0, 0,
                                                    &staging_y_location, रिक्त);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_uv_location, 0, 0, 0,
                                                    &staging_uv_location, रिक्त);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        ID3D12CommandQueue_ExecuteCommandLists(s->command_queue, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_queue_idle(&s->sync_ctx, s->command_queue);
        यदि (ret < 0)
            गच्छ fail;
    }

    hwctx->unlock(hwctx->तालकम्_ctx);

    प्रत्यागम 0;

fail:
    hwctx->unlock(hwctx->तालकम्_ctx);
    प्रत्यागम AVERROR(EINVAL);
}

स्थिर पूर्णाङ्क d3d12va_आरोपय_functions(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv *priv = hwdev->hwctx;

#यदि !HAVE_UWP
    priv->d3d12lib = dlopen("d3d12.dll", 0);
    priv->dxgilib  = dlopen("dxgi.dll", 0);

    यदि (!priv->d3d12lib || !priv->dxgilib)
        गच्छ fail;

    priv->create_device = (PFN_D3D12_CREATE_DEVICE)Get_Proc_स्थानाङ्कः(priv->d3d12lib, "D3D12CreateDevice");
    यदि (!priv->create_device)
        गच्छ fail;

    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2)Get_Proc_स्थानाङ्कः(priv->dxgilib, "CreateDXGIFactory2");
    यदि (!priv->create_dxgi_factory2)
        गच्छ fail;

    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE)Get_Proc_स्थानाङ्कः(priv->d3d12lib, "D3D12GetDebugInterface");
#अन्यथा
    priv->create_device        = (PFN_D3D12_CREATE_DEVICE) D3D12CreateDevice;
    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2) CreateDXGIFactory2;
    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE) D3D12GetDebugInterface;
#यदि_अन्तः
    प्रत्यागम 0;

#यदि !HAVE_UWP
fail:
    av_log(hwdev, AV_LOG_ERROR, "Failed to load D3D12 library or its functions\n");
    प्रत्यागम AVERROR_UNKNOWN;
#यदि_अन्तः
}

स्थिर शून्य d3d12va_device_free(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    D3D12_OBJECT_RELEASE(ctx->device);

    यदि (priv->d3d12lib)
        dlclose(priv->d3d12lib);

    यदि (priv->dxgilib)
        dlclose(priv->dxgilib);
}

स्थिर पूर्णाङ्क d3d12va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *ctx = hwdev->hwctx;

    यदि (!ctx->तालकम्) {
        ctx->तालकम्_ctx = CreateMutex(रिक्त, 0, रिक्त);
        यदि (ctx->तालकम्_ctx == INVALID_HANDLE_मानम्) {
            av_log(रिक्त, AV_LOG_ERROR, "Failed to create a mutex\n");
            प्रत्यागम AVERROR(EINVAL);
        }
        ctx->तालकम्   = d3d12va_default_तालकम्;
        ctx->unlock = d3d12va_default_unlock;
    }

    यदि (!ctx->video_device)
        DX_CHECK(ID3D12Device_QueryInterface(ctx->device, &IID_ID3D12VideoDevice, (शून्य **)&ctx->video_device));

    प्रत्यागम 0;

fail:
    प्रत्यागम AVERROR(EINVAL);
}

स्थिर शून्य d3d12va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *device_hwctx = hwdev->hwctx;

    D3D12_OBJECT_RELEASE(device_hwctx->video_device);

    यदि (device_hwctx->तालकम् == d3d12va_default_तालकम्) {
        CloseHandle(device_hwctx->तालकम्_ctx);
        device_hwctx->तालकम्_ctx = INVALID_HANDLE_मानम्;
        device_hwctx->तालकम् = रिक्त;
    }
}

स्थिर पूर्णाङ्क d3d12va_device_create(AVHWDeviceContext *hwdev, ध्रुव वर्ण *device,
                                 AVDictionary *opts, पूर्णाङ्क flags)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    HRESULT hr;
    UINT create_flags = 0;
    IDXGIAdapter *pAdapter = रिक्त;

    पूर्णाङ्क ret;
    पूर्णाङ्क is_debug = !!av_dict_get(opts, "debug", रिक्त, 0);

    hwdev->मुक्त = d3d12va_device_free;

    ret = d3d12va_आरोपय_functions(hwdev);
    यदि (ret < 0)
        प्रत्यागम ret;

    यदि (is_debug) {
        ID3D12Debug *pDebug;
        यदि (priv->get_debug_interface && SUCCEEDED(priv->get_debug_interface(&IID_ID3D12Debug, (शून्य **)&pDebug))) {
            create_flags |= DXGI_CREATE_FACTORY_DEBUG;
            ID3D12Debug_EnableDebugLayer(pDebug);
            D3D12_OBJECT_RELEASE(pDebug);
            av_log(hwdev, AV_LOG_INFO, "D3D12 debug layer is enabled!\n");
        }
    }

    यदि (!ctx->device) {
        IDXGIFactory2 *pDXGIFactory = रिक्त;

        hr = priv->create_dxgi_factory2(create_flags, &IID_IDXGIFactory2, (शून्य **)&pDXGIFactory);
        यदि (SUCCEEDED(hr)) {
            पूर्णाङ्क adapter = device ? atoi(device) : 0;
            यदि (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = रिक्त;
            IDXGIFactory2_Release(pDXGIFactory);
        }

        यदि (pAdapter) {
            DXGI_ADAPTER_DESC desc;
            hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
            यदि (!FAILED(hr)) {
                av_log(hwdev, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                       desc.VendorId, desc.DeviceId, desc.Description);
            }
        }

        hr = priv->create_device((IUnknown *)pAdapter, D3D_FEATURE_LEVEL_12_0, &IID_ID3D12Device, (शून्य **)&ctx->device);
        D3D12_OBJECT_RELEASE(pAdapter);
        यदि (FAILED(hr)) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create Direct 3D 12 device (%lx)\n", (दीर्घ)hr);
            प्रत्यागम AVERROR_UNKNOWN;
        }
    }

    यदि (av_dict_get(opts, "UAV", रिक्त, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    यदि (av_dict_get(opts, "RTV", रिक्त, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

    यदि (av_dict_get(opts, "SHARED", रिक्त, 0))
        ctx->heap_flags |= D3D12_HEAP_FLAG_SHARED;

    प्रत्यागम 0;
}

ध्रुव HWContextType ff_hwcontext_type_d3d12va = {
    .type                   = AV_HWDEVICE_TYPE_D3D12VA,
    .name                   = "D3D12VA",

    .device_hwctx_आकार      = परिमाण(D3D12VADevicePriv),
    .चौकटाः_hwctx_आकार      = परिमाण(D3D12VAFramesContext),

    .device_create          = d3d12va_device_create,
    .device_init            = d3d12va_device_init,
    .device_uninit          = d3d12va_device_uninit,
    .चौकटाः_get_constraints = d3d12va_चौकटाः_get_constraints,
    .चौकटाः_init            = d3d12va_चौकटाः_init,
    .चौकटाः_uninit          = d3d12va_चौकटाः_uninit,
    .चौकटाः_get_बफर      = d3d12va_get_बफर,
    .transfer_get_formats   = d3d12va_transfer_get_formats,
    .transfer_दत्त_गन्तव्यम्       = d3d12va_transfer_दत्त,
    .transfer_दत्त_from     = d3d12va_transfer_दत्त,

    .pix_fmts               = (ध्रुव गणना AVPixelFormat[]){ AV_PIX_FMT_D3D12, AV_PIX_FMT_NONE },
};
