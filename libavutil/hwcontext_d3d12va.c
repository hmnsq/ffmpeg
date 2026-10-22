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

#అన్తర్భావ "config.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "hwcontext_d3d12va_internal.h"
#అన్తర్భావ "hwcontext_d3d12va.h"
#అన్తర్భావ "imgutils.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "pixdesc.h"
#అన్తర్భావ "pixfmt.h"
#అన్తర్భావ "thread.h"
#అన్తర్భావ "compat/w32dlfcn.h"
#అన్తర్భావ <dxgi1_3.h>

రకనిర్వచనం HRESULT(WINAPI *PFN_CREATE_DXGI_FACTORY2)(UINT Flags, REFIID riid, శూన్య **ppFactory);

రకనిర్వచనం నిర్మాణం D3D12VAFramesContext {
    /**
     * The public AVD3D12VAFramesContext. See hwcontext_d3d12va.h for it.
     */
    AVD3D12VAFramesContext p;

    ID3D12Resource            *staging_download_బఫరు;
    ID3D12Resource            *staging_upload_బఫరు;
    ID3_D12_Command_వరుస        *command_వరుస;
    ID3D12CommandAllocator    *command_allocator;
    ID3D12GraphicsCommandList *command_list;
    AVD3D12VASyncContext       sync_ctx;
    UINT                       luma_component_కొలత;
    పూర్ణాంకం                        nb_surfaces_వాడిన;
} D3D12VAFramesContext;

రకనిర్వచనం నిర్మాణం D3D12VADevicePriv {
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

స్థిర స్థిరరాశి నిర్మాణం {
    DXGI_FORMAT d3d_format;
    గణన AVPixelFormat pix_fmt;
} supported_formats[] = {
    { DXGI_FORMAT_NV12, AV_PIX_FMT_NV12 },
    { DXGI_FORMAT_P010, AV_PIX_FMT_P010 },
    { DXGI_FORMAT_P016, AV_PIX_FMT_P012 },
};

స్థిర శూన్య d3d12va_default_తాళం(శూన్య *ctx)
{
    WaitForSingleObjectEx(ctx, INFINITE, FALSE);
}

స్థిర శూన్య d3d12va_default_unlock(శూన్య *ctx)
{
    ReleaseMutex(ctx);
}

స్థిర పూర్ణాంకం d3d12va_fence_completion(AVD3D12VASyncContext *psync_ctx)
{
    uint64_t completion = ID3_D12_Fence_Get_Completed_విలువ(psync_ctx->fence);
    ఒకవేళ (completion < psync_ctx->fence_విలువ) {
        ఒకవేళ (FAILED(ID3_D12_Fence_సమితి_Event_On_Completion(psync_ctx->fence, psync_ctx->fence_విలువ, psync_ctx->event)))
            తిరిగి AVERROR(EINVAL);

        WaitForSingleObjectEx(psync_ctx->event, INFINITE, FALSE);
    }

    తిరిగి 0;
}

స్థిర అంతఃవరుస పూర్ణాంకం d3d12va_wait_వరుస_idle(AVD3D12VASyncContext *psync_ctx, ID3_D12_Command_వరుస *command_వరుస)
{
    DX_CHECK(ID3_D12_Command_వరుస_Signal(command_వరుస, psync_ctx->fence, ++psync_ctx->fence_విలువ));
    తిరిగి d3d12va_fence_completion(psync_ctx);

fail:
    తిరిగి AVERROR(EINVAL);
}

స్థిర పూర్ణాంకం d3d12va_create_staging_బఫరు_resource(AVHWFramesContext *ctx, D3_D12_RESOURCE_స్థితులు స్థితులు,
                                                  ID3D12Resource **ppResource, పూర్ణాంకం download)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    D3_D12_కుప్ప_PROPERTIES props = { .Type = download ? D3_D12_కుప్ప_TYPE_READBACK : D3_D12_కుప్ప_TYPE_UPLOAD };
    D3D12_RESOURCE_DESC desc = {
        .Dimension          = D3_D12_RESOURCE_DIMENSION_బఫరు,
        .Alignment          = 0,
        .వెడల్పు_2              = s->luma_component_కొలత + (s->luma_component_కొలత >> 1),
        .ఎత్తు_2             = 1,
        .లోతు_Or_Array_కొలత   = 1,
        .Mip_స్థాయిలు          = 1,
        .Format             = DXGI_FORMAT_UNKNOWN,
        .SampleDesc         = { .లెక్క_2 = 1, .Quality = 0 },
        .Layout             = D3_D12_TEXTURE_LAYOUT_అడ్డువరుస_MAJOR,
        .Flags              = D3D12_RESOURCE_FLAG_NONE,
    };

    ఒకవేళ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, D3_D12_కుప్ప_FLAG_NONE, &desc,
        స్థితులు, ఖాళీ, &IID_ID3D12Resource, (శూన్య **)ppResource))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the staging buffer resource\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం d3d12va_create_helper_objects(AVHWFramesContext *ctx)
{
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *చట్రాలు_hwctx = &s->p;

    D3_D12_COMMAND_వరుస_DESC వరుస_desc = {
        .Type     = D3D12_COMMAND_LIST_TYPE_COPY,
        .ప్రాధాన్యత = 0,
        .కణుపు_ముసుగు = 0,
    };

    s->luma_component_కొలత = FFALIGN(ctx->వెడల్పు * (చట్రాలు_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                                     D3_D12_TEXTURE_దత్తాంశం_PITCH_ALIGNMENT) * ctx->ఎత్తు;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (శూన్య **)&s->sync_ctx.fence));

    s->sync_ctx.event = CreateEvent(ఖాళీ, FALSE, FALSE, ఖాళీ);
    ఒకవేళ (!s->sync_ctx.event)
        వెళ్ళు fail;

    DX_CHECK(ID3_D12_Device_Create_Command_వరుస(device_hwctx->device, &వరుస_desc,
             &IID_ID3_D12_Command_వరుస, (శూన్య **)&s->command_వరుస));

    DX_CHECK(ID3D12Device_CreateCommandAllocator(device_hwctx->device, వరుస_desc.Type,
             &IID_ID3D12CommandAllocator, (శూన్య **)&s->command_allocator));

    DX_CHECK(ID3D12Device_CreateCommandList(device_hwctx->device, 0, వరుస_desc.Type,
             s->command_allocator, ఖాళీ, &IID_ID3D12GraphicsCommandList, (శూన్య **)&s->command_list));

    DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

    ID3_D12_Command_వరుస_Execute_Command_Lists(s->command_వరుస, 1, (ID3D12CommandList **)&s->command_list);

    తిరిగి d3d12va_wait_వరుస_idle(&s->sync_ctx, s->command_వరుస);

fail:
    తిరిగి AVERROR(EINVAL);
}

స్థిర శూన్య d3d12va_చట్రాలు_uninit(AVHWFramesContext *ctx)
{
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;

    D3D12_OBJECT_RELEASE(s->sync_ctx.fence);
    ఒకవేళ (s->sync_ctx.event)
        CloseHandle(s->sync_ctx.event);

    D3D12_OBJECT_RELEASE(s->staging_download_బఫరు);
    D3D12_OBJECT_RELEASE(s->staging_upload_బఫరు);
    D3D12_OBJECT_RELEASE(s->command_allocator);
    D3D12_OBJECT_RELEASE(s->command_list);
    D3D12_OBJECT_RELEASE(s->command_వరుస);

    ఒకవేళ (hwctx->texture_array)
        D3D12_OBJECT_RELEASE(hwctx->texture_array);
}

స్థిర పూర్ణాంకం d3d12va_చట్రాలు_get_constraints(AVHWDeviceContext *ctx, స్థిరరాశి శూన్య *hwconfig, AVHWFramesConstraints *constraints)
{
    HRESULT hr;
    పూర్ణాంకం nb_sw_formats = 0;
    AVD3D12VADeviceContext *device_hwctx = ctx->hwctx;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    పరిమాణం(*constraints->valid_sw_formats));
    ఒకవేళ (!constraints->valid_sw_formats)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        D3_D12_FEATURE_దత్తాంశం_FORMAT_SUPPORT format_support = { supported_formats[i].d3d_format };
        hr = ID3D12Device_CheckFeatureSupport(device_hwctx->device, D3D12_FEATURE_FORMAT_SUPPORT, &format_support, పరిమాణం(format_support));
        ఒకవేళ (SUCCEEDED(hr) && (format_support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D))
            constraints->valid_sw_formats[nb_sw_formats++] = supported_formats[i].pix_fmt;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, పరిమాణం(*constraints->valid_hw_formats));
    ఒకవేళ (!constraints->valid_hw_formats)
        తిరిగి AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_D3D12;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    తిరిగి 0;
}

స్థిర శూన్య free_texture(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    AVD3D12VAFrame *చట్రం = (AVD3D12VAFrame *)దత్తాంశం;

    ఒకవేళ (!(చట్రం->flags & AV_D3_D12_VA_చట్రం_FLAG_TEXTURE_ARRAY))
        D3D12_OBJECT_RELEASE(చట్రం->texture);

    D3D12_OBJECT_RELEASE(చట్రం->sync_ctx.fence);
    ఒకవేళ (చట్రం->sync_ctx.event)
        CloseHandle(చట్రం->sync_ctx.event);

    av_freep(&దత్తాంశం);
}

స్థిర AVBufferRef *d3d12va_pool_alloc_texture_array(AVHWFramesContext *ctx)
{
    AVD3D12VAFrame         *చట్రం  = av_mallocz(పరిమాణం(*చట్రం));
    D3D12VAFramesContext   *s     = ctx->hwctx;
    AVD3D12VAFramesContext *hwctx = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    AVBufferRef *buf;

    చట్రం->flags |= AV_D3_D12_VA_చట్రం_FLAG_TEXTURE_ARRAY;

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (శూన్య **)&చట్రం->sync_ctx.fence));
    చట్రం->sync_ctx.event = CreateEvent(ఖాళీ, FALSE, FALSE, ఖాళీ);
    ఒకవేళ (!చట్రం->sync_ctx.event)
        వెళ్ళు fail;

    ఒకవేళ (s->nb_surfaces_వాడిన >= ctx->initial_pool_కొలత) {
        av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
        వెళ్ళు fail;
    }

    చట్రం->texture = hwctx->texture_array;
    చట్రం->subresource_సూచీ = s->nb_surfaces_వాడిన;

    buf = av_బఫరు_create((uint8_t *)చట్రం, పరిమాణం(*చట్రం), free_texture, ఖాళీ, 0);

    ఒకవేళ (!buf)
        వెళ్ళు fail;

    s->nb_surfaces_వాడిన++;
    తిరిగి buf;
fail:
    free_texture(ఖాళీ, (uint8_t *)చట్రం);
    తిరిగి ఖాళీ;
}

స్థిర AVBufferRef *d3d12va_pool_alloc(శూన్య *opaque, size_t కొలత)
{
    AVHWFramesContext      *ctx          = (AVHWFramesContext *)opaque;
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    AVBufferRef *buf;
    AVD3D12VAFrame *చట్రం;

    ఒకవేళ (ctx->initial_pool_కొలత > 0 && hwctx->flags & AV_D3_D12_VA_చట్రం_FLAG_TEXTURE_ARRAY)
        తిరిగి d3d12va_pool_alloc_texture_array(ctx);

    D3_D12_కుప్ప_PROPERTIES props = { .Type = D3_D12_కుప్ప_TYPE_DEFAULT };
    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .వెడల్పు_2            = ctx->వెడల్పు,
        .ఎత్తు_2           = ctx->ఎత్తు,
        .లోతు_Or_Array_కొలత = 1,
        .Mip_స్థాయిలు        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.లెక్క_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    చట్రం = av_mallocz(పరిమాణం(AVD3D12VAFrame));
    ఒకవేళ (!చట్రం)
        తిరిగి ఖాళీ;

    ఒకవేళ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->కుప్ప_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, ఖాళీ, &IID_ID3D12Resource, (శూన్య **)&చట్రం->texture))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture\n");
        వెళ్ళు fail;
    }

    DX_CHECK(ID3D12Device_CreateFence(device_hwctx->device, 0, D3D12_FENCE_FLAG_NONE,
                                      &IID_ID3D12Fence, (శూన్య **)&చట్రం->sync_ctx.fence));

    చట్రం->sync_ctx.event = CreateEvent(ఖాళీ, FALSE, FALSE, ఖాళీ);
    ఒకవేళ (!చట్రం->sync_ctx.event)
        వెళ్ళు fail;

    buf = av_బఫరు_create((uint8_t *)చట్రం, పరిమాణం(*చట్రం), free_texture, ఖాళీ, 0);
    ఒకవేళ (!buf)
        వెళ్ళు fail;

    తిరిగి buf;

fail:
    free_texture(ఖాళీ, (uint8_t *)చట్రం);
    తిరిగి ఖాళీ;
}

స్థిర పూర్ణాంకం d3d12va_texture_array_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;

    D3_D12_కుప్ప_PROPERTIES props = { .Type = D3_D12_కుప్ప_TYPE_DEFAULT };

    D3D12_RESOURCE_DESC desc = {
        .Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        .Alignment        = 0,
        .వెడల్పు_2            = ctx->వెడల్పు,
        .ఎత్తు_2           = ctx->ఎత్తు,
        .లోతు_Or_Array_కొలత = ctx->initial_pool_కొలత,
        .Mip_స్థాయిలు        = 1,
        .Format           = hwctx->format,
        .SampleDesc       = {.లెక్క_2 = 1, .Quality = 0 },
        .Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags            = hwctx->resource_flags,
    };

    ఒకవేళ (FAILED(ID3D12Device_CreateCommittedResource(device_hwctx->device, &props, hwctx->కుప్ప_flags, &desc,
        D3D12_RESOURCE_STATE_COMMON, ఖాళీ, &IID_ID3D12Resource, (శూన్య **)&hwctx->texture_array))) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the texture array\n");
        తిరిగి AVERROR(EINVAL);
    }
    తిరిగి 0;
}

స్థిర పూర్ణాంకం d3d12va_చట్రాలు_init(AVHWFramesContext *ctx)
{
    AVD3D12VAFramesContext *hwctx        = ctx->hwctx;
    AVD3D12VADeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    పూర్ణాంకం i;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ఒకవేళ (ctx->sw_format == supported_formats[i].pix_fmt) {
            ఒకవేళ (hwctx->format != DXGI_FORMAT_UNKNOWN &&
                hwctx->format != supported_formats[i].d3d_format)
                av_log(ctx, AV_LOG_WARNING, "Incompatible DXGI format provided by user, will be overided\n");
            hwctx->format = supported_formats[i].d3d_format;
            ఆపు;
        }
    }

    ఒకవేళ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        తిరిగి AVERROR(EINVAL);
    }

    hwctx->resource_flags |= device_hwctx->resource_flags;
    hwctx->కుప్ప_flags     |= device_hwctx->కుప్ప_flags;

    ఒకవేళ (ctx->initial_pool_కొలత > 0 && hwctx->flags & AV_D3_D12_VA_చట్రం_FLAG_TEXTURE_ARRAY) {
        పూర్ణాంకం err = d3d12va_texture_array_init(ctx);
        ఒకవేళ (err < 0)
            తిరిగి err;
    }

    ffhwframesctx(ctx)->pool_అంతర్గత = av_బఫరు_pool_init2(పరిమాణం(AVD3D12VAFrame),
        ctx, d3d12va_pool_alloc, ఖాళీ);

    ఒకవేళ (!ffhwframesctx(ctx)->pool_అంతర్గత)
        తిరిగి AVERROR(ENOMEM);

    తిరిగి 0;
}

స్థిర పూర్ణాంకం d3d12va_get_బఫరు(AVHWFramesContext *ctx, AVFrame *చట్రం)
{
    పూర్ణాంకం ret;

    చట్రం->buf[0] = av_బఫరు_pool_get(ctx->pool);
    ఒకవేళ (!చట్రం->buf[0])
        తిరిగి AVERROR(ENOMEM);

    ret = av_image_fill_arrays(చట్రం->దత్తాంశం, చట్రం->linesize, ఖాళీ,
                               ctx->sw_format, ctx->వెడల్పు, ctx->ఎత్తు,
                               D3_D12_TEXTURE_దత్తాంశం_PITCH_ALIGNMENT);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    చట్రం->దత్తాంశం[0] = చట్రం->buf[0]->దత్తాంశం;
    చట్రం->format  = AV_PIX_FMT_D3D12;
    చట్రం->వెడల్పు   = ctx->వెడల్పు;
    చట్రం->ఎత్తు  = ctx->ఎత్తు;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం d3d12va_transfer_get_formats(AVHWFramesContext *ctx,
                                        గణన AVHWFrameTransferDirection dir,
                                        గణన AVPixelFormat **formats)
{
    గణన AVPixelFormat *fmts;

    fmts = av_malloc_array(2, పరిమాణం(*fmts));
    ఒకవేళ (!fmts)
        తిరిగి AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం d3d12va_transfer_దత్తాంశం(AVHWFramesContext *ctx, AVFrame *dst,
                                 స్థిరరాశి AVFrame *src)
{
    AVD3D12VADeviceContext *hwctx        = ctx->device_ctx->hwctx;
    D3D12VAFramesContext   *s            = ctx->hwctx;
    AVD3D12VAFramesContext *చట్రాలు_hwctx = &s->p;

    పూర్ణాంకం ret;
    పూర్ణాంకం download = src->format == AV_PIX_FMT_D3D12;
    స్థిరరాశి AVFrame *చట్రం = download ? src : dst;
    స్థిరరాశి AVFrame *other = download ? dst : src;

    AVD3D12VAFrame *f = (AVD3D12VAFrame *)చట్రం->దత్తాంశం[0];
    ID3D12Resource *texture = (ID3D12Resource *)f->texture;

    uint8_t *mapped_దత్తాంశం;
    uint8_t *దత్తాంశం[4];
    పూర్ణాంకం linesizes[4];

    D3D12_TEXTURE_COPY_LOCATION staging_y_location  = { 0 };
    D3D12_TEXTURE_COPY_LOCATION staging_uv_location = { 0 };

    D3D12_TEXTURE_COPY_LOCATION texture_y_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_సూచీ,
        .Subresource_సూచీ = 0,
    };

    D3D12_TEXTURE_COPY_LOCATION texture_uv_location = {
        .pResource        = texture,
        .Type             = D3_D12_TEXTURE_COPY_TYPE_SUBRESOURCE_సూచీ,
        .Subresource_సూచీ = 1,
    };

    D3D12_RESOURCE_BARRIER barrier = {
        .Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
        .Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
        .Transition = {
            .pResource   = texture,
            .StateBefore = D3D12_RESOURCE_STATE_COMMON,
            .StateAfter  = download ? D3_D12_RESOURCE_STATE_COPY_ఆధారం : D3D12_RESOURCE_STATE_COPY_DEST,
            .Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
        },
    };

    ఒకవేళ (చట్రం->hw_చట్రాలు_ctx->దత్తాంశం != (uint8_t *)ctx || other->format != ctx->sw_format)
        తిరిగి AVERROR(EINVAL);

    hwctx->తాళం_2(hwctx->తాళం_ctx);

    ఒకవేళ (!s->command_వరుస) {
        ret = d3d12va_create_helper_objects(ctx);
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;
    }

    కొరకు (పూర్ణాంకం i = 0; i < 4; i++)
        linesizes[i] = FFALIGN(చట్రం->వెడల్పు * (చట్రాలు_hwctx->format != DXGI_FORMAT_NV12 ? 2 : 1),
                               D3_D12_TEXTURE_దత్తాంశం_PITCH_ALIGNMENT);

    staging_y_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .స్థానభ్రంశం_4 = 0,
            .Footprint = {
                .Format   = చట్రాలు_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16_UNORM : DXGI_FORMAT_R8_UNORM,
                .వెడల్పు_2    = ctx->వెడల్పు,
                .ఎత్తు_2   = ctx->ఎత్తు,
                .లోతు_2    = 1,
                .అడ్డువరుస_Pitch = linesizes[0],
            },
        },
    };

    staging_uv_location = (D3D12_TEXTURE_COPY_LOCATION) {
        .Type      = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
        .PlacedFootprint = {
            .స్థానభ్రంశం_4 = s->luma_component_కొలత,
            .Footprint = {
                .Format   = చట్రాలు_hwctx->format != DXGI_FORMAT_NV12 ?
                                                    DXGI_FORMAT_R16G16_UNORM : DXGI_FORMAT_R8G8_UNORM,
                .వెడల్పు_2    = ctx->వెడల్పు  >> 1,
                .ఎత్తు_2   = ctx->ఎత్తు >> 1,
                .లోతు_2    = 1,
                .అడ్డువరుస_Pitch = linesizes[0],
            },
        },
    };

    DX_CHECK(ID3D12CommandAllocator_Reset(s->command_allocator));

    DX_CHECK(ID3D12GraphicsCommandList_Reset(s->command_list, s->command_allocator, ఖాళీ));

    ఒకవేళ (download) {
        ఒకవేళ (!s->staging_download_బఫరు) {
            ret = d3d12va_create_staging_బఫరు_resource(ctx, D3D12_RESOURCE_STATE_COPY_DEST,
                                                         &s->staging_download_బఫరు, 1);
            ఒకవేళ (ret < 0) {
                వెళ్ళు fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_download_బఫరు;

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_y_location, 0, 0, 0,
                                                    &texture_y_location, ఖాళీ);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &staging_uv_location, 0, 0, 0,
                                                    &texture_uv_location, ఖాళీ);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        DX_CHECK(ID3_D12_Command_వరుస_Wait(s->command_వరుస, f->sync_ctx.fence, f->sync_ctx.fence_విలువ));

        ID3_D12_Command_వరుస_Execute_Command_Lists(s->command_వరుస, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_వరుస_idle(&s->sync_ctx, s->command_వరుస);
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;

        DX_CHECK(ID3D12Resource_Map(s->staging_download_బఫరు, 0, ఖాళీ, (శూన్య **)&mapped_దత్తాంశం));
        av_image_fill_సూచికలు(దత్తాంశం, ctx->sw_format, ctx->ఎత్తు, mapped_దత్తాంశం, linesizes);

        av_image_copy2(dst->దత్తాంశం, dst->linesize, దత్తాంశం, linesizes,
                       ctx->sw_format, ctx->వెడల్పు, ctx->ఎత్తు);

        ID3D12Resource_Unmap(s->staging_download_బఫరు, 0, ఖాళీ);
    } లేకపోతే {
        ఒకవేళ (!s->staging_upload_బఫరు) {
            ret = d3d12va_create_staging_బఫరు_resource(ctx, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                        &s->staging_upload_బఫరు, 0);
            ఒకవేళ (ret < 0) {
                వెళ్ళు fail;
            }
        }

        staging_y_location.pResource = staging_uv_location.pResource = s->staging_upload_బఫరు;

        DX_CHECK(ID3D12Resource_Map(s->staging_upload_బఫరు, 0, ఖాళీ, (శూన్య **)&mapped_దత్తాంశం));
        av_image_fill_సూచికలు(దత్తాంశం, ctx->sw_format, ctx->ఎత్తు, mapped_దత్తాంశం, linesizes);

        av_image_copy2(దత్తాంశం, linesizes, src->దత్తాంశం, src->linesize,
                       ctx->sw_format, ctx->వెడల్పు, ctx->ఎత్తు);

        ID3D12Resource_Unmap(s->staging_upload_బఫరు, 0, ఖాళీ);

        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_y_location, 0, 0, 0,
                                                    &staging_y_location, ఖాళీ);

        ID3D12GraphicsCommandList_CopyTextureRegion(s->command_list,
                                                    &texture_uv_location, 0, 0, 0,
                                                    &staging_uv_location, ఖాళీ);

        barrier.Transition.StateBefore = barrier.Transition.StateAfter;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COMMON;
        ID3D12GraphicsCommandList_ResourceBarrier(s->command_list, 1, &barrier);

        DX_CHECK(ID3D12GraphicsCommandList_Close(s->command_list));

        ID3_D12_Command_వరుస_Execute_Command_Lists(s->command_వరుస, 1, (ID3D12CommandList **)&s->command_list);

        ret = d3d12va_wait_వరుస_idle(&s->sync_ctx, s->command_వరుస);
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;
    }

    hwctx->unlock(hwctx->తాళం_ctx);

    తిరిగి 0;

fail:
    hwctx->unlock(hwctx->తాళం_ctx);
    తిరిగి AVERROR(EINVAL);
}

స్థిర పూర్ణాంకం d3d12va_ఎక్కించు_functions(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv *priv = hwdev->hwctx;

#ఒకవేళ !HAVE_UWP
    priv->d3d12lib = dlopen("d3d12.dll", 0);
    priv->dxgilib  = dlopen("dxgi.dll", 0);

    ఒకవేళ (!priv->d3d12lib || !priv->dxgilib)
        వెళ్ళు fail;

    priv->create_device = (PFN_D3D12_CREATE_DEVICE)Get_Proc_చిరునామా(priv->d3d12lib, "D3D12CreateDevice");
    ఒకవేళ (!priv->create_device)
        వెళ్ళు fail;

    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2)Get_Proc_చిరునామా(priv->dxgilib, "CreateDXGIFactory2");
    ఒకవేళ (!priv->create_dxgi_factory2)
        వెళ్ళు fail;

    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE)Get_Proc_చిరునామా(priv->d3d12lib, "D3D12GetDebugInterface");
#లేకపోతే
    priv->create_device        = (PFN_D3D12_CREATE_DEVICE) D3D12CreateDevice;
    priv->create_dxgi_factory2 = (PFN_CREATE_DXGI_FACTORY2) CreateDXGIFactory2;
    priv->get_debug_interface  = (PFN_D3D12_GET_DEBUG_INTERFACE) D3D12GetDebugInterface;
#అయితే_ముగింపు
    తిరిగి 0;

#ఒకవేళ !HAVE_UWP
fail:
    av_log(hwdev, AV_LOG_ERROR, "Failed to load D3D12 library or its functions\n");
    తిరిగి AVERROR_UNKNOWN;
#అయితే_ముగింపు
}

స్థిర శూన్య d3d12va_device_free(AVHWDeviceContext *hwdev)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    D3D12_OBJECT_RELEASE(ctx->device);

    ఒకవేళ (priv->d3d12lib)
        dlclose(priv->d3d12lib);

    ఒకవేళ (priv->dxgilib)
        dlclose(priv->dxgilib);
}

స్థిర పూర్ణాంకం d3d12va_device_init(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *ctx = hwdev->hwctx;

    ఒకవేళ (!ctx->తాళం_2) {
        ctx->తాళం_ctx = CreateMutex(ఖాళీ, 0, ఖాళీ);
        ఒకవేళ (ctx->తాళం_ctx == INVALID_HANDLE_విలువ) {
            av_log(ఖాళీ, AV_LOG_ERROR, "Failed to create a mutex\n");
            తిరిగి AVERROR(EINVAL);
        }
        ctx->తాళం_2   = d3d12va_default_తాళం;
        ctx->unlock = d3d12va_default_unlock;
    }

    ఒకవేళ (!ctx->video_device)
        DX_CHECK(ID3D12Device_QueryInterface(ctx->device, &IID_ID3D12VideoDevice, (శూన్య **)&ctx->video_device));

    తిరిగి 0;

fail:
    తిరిగి AVERROR(EINVAL);
}

స్థిర శూన్య d3d12va_device_uninit(AVHWDeviceContext *hwdev)
{
    AVD3D12VADeviceContext *device_hwctx = hwdev->hwctx;

    D3D12_OBJECT_RELEASE(device_hwctx->video_device);

    ఒకవేళ (device_hwctx->తాళం_2 == d3d12va_default_తాళం) {
        CloseHandle(device_hwctx->తాళం_ctx);
        device_hwctx->తాళం_ctx = INVALID_HANDLE_విలువ;
        device_hwctx->తాళం_2 = ఖాళీ;
    }
}

స్థిర పూర్ణాంకం d3d12va_device_create(AVHWDeviceContext *hwdev, స్థిరరాశి అక్షరం *device,
                                 AVDictionary *opts, పూర్ణాంకం flags)
{
    D3D12VADevicePriv      *priv = hwdev->hwctx;
    AVD3D12VADeviceContext *ctx  = &priv->p;

    HRESULT hr;
    UINT create_flags = 0;
    IDXGIAdapter *pAdapter = ఖాళీ;

    పూర్ణాంకం ret;
    పూర్ణాంకం is_debug = !!av_dict_get(opts, "debug", ఖాళీ, 0);

    hwdev->విడుదల = d3d12va_device_free;

    ret = d3d12va_ఎక్కించు_functions(hwdev);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ఒకవేళ (is_debug) {
        ID3D12Debug *pDebug;
        ఒకవేళ (priv->get_debug_interface && SUCCEEDED(priv->get_debug_interface(&IID_ID3D12Debug, (శూన్య **)&pDebug))) {
            create_flags |= DXGI_CREATE_FACTORY_DEBUG;
            ID3D12Debug_EnableDebugLayer(pDebug);
            D3D12_OBJECT_RELEASE(pDebug);
            av_log(hwdev, AV_LOG_INFO, "D3D12 debug layer is enabled!\n");
        }
    }

    ఒకవేళ (!ctx->device) {
        IDXGIFactory2 *pDXGIFactory = ఖాళీ;

        hr = priv->create_dxgi_factory2(create_flags, &IID_IDXGIFactory2, (శూన్య **)&pDXGIFactory);
        ఒకవేళ (SUCCEEDED(hr)) {
            పూర్ణాంకం adapter = device ? atoi(device) : 0;
            ఒకవేళ (FAILED(IDXGIFactory2_EnumAdapters(pDXGIFactory, adapter, &pAdapter)))
                pAdapter = ఖాళీ;
            IDXGIFactory2_Release(pDXGIFactory);
        }

        ఒకవేళ (pAdapter) {
            DXGI_ADAPTER_DESC desc;
            hr = IDXGIAdapter2_GetDesc(pAdapter, &desc);
            ఒకవేళ (!FAILED(hr)) {
                av_log(hwdev, AV_LOG_INFO, "Using device %04x:%04x (%ls).\n",
                       desc.VendorId, desc.DeviceId, desc.Description);
            }
        }

        hr = priv->create_device((IUnknown *)pAdapter, D3D_FEATURE_LEVEL_12_0, &IID_ID3D12Device, (శూన్య **)&ctx->device);
        D3D12_OBJECT_RELEASE(pAdapter);
        ఒకవేళ (FAILED(hr)) {
            av_log(hwdev, AV_LOG_ERROR, "Failed to create Direct 3D 12 device (%lx)\n", (దీర్ఘ)hr);
            తిరిగి AVERROR_UNKNOWN;
        }
    }

    ఒకవేళ (av_dict_get(opts, "UAV", ఖాళీ, 0))
        ctx->resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    ఒకవేళ (av_dict_get(opts, "RTV", ఖాళీ, 0))
        ctx->resource_flags |= D3_D12_RESOURCE_FLAG_ALLOW_RENDER_లక్ష్యం;

    ఒకవేళ (av_dict_get(opts, "SHARED", ఖాళీ, 0))
        ctx->కుప్ప_flags |= D3_D12_కుప్ప_FLAG_SHARED;

    తిరిగి 0;
}

స్థిరరాశి HWContextType ff_hwcontext_type_d3d12va = {
    .type                   = AV_HWDEVICE_TYPE_D3D12VA,
    .name                   = "D3D12VA",

    .device_hwctx_కొలత      = పరిమాణం(D3D12VADevicePriv),
    .చట్రాలు_hwctx_కొలత      = పరిమాణం(D3D12VAFramesContext),

    .device_create          = d3d12va_device_create,
    .device_init            = d3d12va_device_init,
    .device_uninit          = d3d12va_device_uninit,
    .చట్రాలు_get_constraints = d3d12va_చట్రాలు_get_constraints,
    .చట్రాలు_init            = d3d12va_చట్రాలు_init,
    .చట్రాలు_uninit          = d3d12va_చట్రాలు_uninit,
    .చట్రాలు_get_బఫరు      = d3d12va_get_బఫరు,
    .transfer_get_formats   = d3d12va_transfer_get_formats,
    .transfer_దత్తాంశం_గమ్యం       = d3d12va_transfer_దత్తాంశం,
    .transfer_దత్తాంశం_from     = d3d12va_transfer_దత్తాంశం,

    .pix_fmts               = (స్థిరరాశి గణన AVPixelFormat[]){ AV_PIX_FMT_D3D12, AV_PIX_FMT_NONE },
};
