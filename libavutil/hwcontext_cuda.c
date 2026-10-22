/*
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

#شامل "buffer.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_internal.h"
#شامل "hwcontext_cuda_internal.h"
#اگر CONFIG_VULKAN
#شامل "hwcontext_vulkan.h"
#endif
#شامل "cuda_check.h"
#شامل "mem.h"
#شامل "pixdesc.h"
#شامل "pixfmt.h"
#شامل "imgutils.h"

تعریفنوع ساختار CUDAFramesContext {
    AVCUDAFramesContext p;

    صحیح shift_width, shift_height;
    صحیح tex_alignment;

    صحیح cuarray_رقم_surfaces_used;
} CUDAFramesContext;

تعریفنوع ساختار CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADeviceContextInternal internal;
} CUDADeviceContext;



#define CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

ایستا CUarray_format cuda_array_format_for_pix_fmt(شمارش AVPixelFormat fmt);

ایستا صحیح cuda_frames_get_constraints(AVHWDeviceContext *ctx,
                                       ثابت تهی *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ثابت AVCUDAHWConfig *config = hwconfig;
    شمارش AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    صحیح n = 0;

    اگر (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, اندازه(*constraints->valid_hw_formats));
        اگر (!constraints->valid_hw_formats)
            بازگشت AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } وگرنه {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, اندازه(*constraints->valid_hw_formats));
        اگر (!constraints->valid_hw_formats)
            بازگشت AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#اگر HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#وگرنه
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#endif
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    اندازه(*constraints->valid_sw_formats));
    اگر (!constraints->valid_sw_formats)
        بازگشت AVERROR(ENOMEM);

    n = 0;
    برای (صحیح i = 0; i < AV_PIX_FMT_NB; i++) {
        اگر (req_fmt == AV_PIX_FMT_CUARRAY) {
            اگر (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } وگرنه {
            ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            اگر (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#اگر CONFIG_VULKAN
    اگر (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#endif
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    بازگشت 0;
}

ایستا تهی cuda_buffer_free(تهی *opaque, uint8_t *data)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_افزودن_Current(hwctx->cuda_ctx));

    اگر (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)data;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } وگرنه {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)data));
    }

    CHECK_CU(cu->cu_Ctx_برداشت_Current(&dummy));
}

ایستا AVBufferRef *cuda_pool_alloc(تهی *opaque, size_t size)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    AVBufferRef *ret = پوچ;
    CUcontext dummy = پوچ;
    CUdeviceptr data;
    صحیح err;

    err = CHECK_CU(cu->cu_Ctx_افزودن_Current(hwctx->cuda_ctx));
    اگر (err < 0)
        بازگشت پوچ;

    اگر (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = av_mallocz(اندازه(*desc));
        اگر (!desc)
            برو done;

        اگر (priv->p.cuarray_رقم_surfaces > 0) {
            اگر (priv->cuarray_رقم_surfaces_used >= priv->p.cuarray_رقم_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                برو done;
            }
            desc->index = priv->cuarray_رقم_surfaces_used++;
            desc->array = priv->p.cuarray_surfaces[desc->index];
        } وگرنه {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            اگر (err < 0) {
                av_free(desc);
                برو done;
            }
        }

        ret = av_buffer_create((uint8_t*)desc, اندازه(*desc), cuda_buffer_free, ctx, 0);
        اگر (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            برو done;
        }

        برو done;
    }

    err = CHECK_CU(cu->cuMemAlloc(&data, size));
    اگر (err < 0)
        برو done;

    ret = av_buffer_create((uint8_t*)data, size, cuda_buffer_free, ctx, 0);
    اگر (!ret) {
        CHECK_CU(cu->cuMemFree(data));
        برو done;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
done:
    CHECK_CU(cu->cu_Ctx_برداشت_Current(&dummy));
    بازگشت ret;
}

#اگر HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
ایستا تهی cuda_transfer_buffer_free(تهی *opaque, uint8_t *data)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_افزودن_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(data));
    CHECK_CU(cu->cu_Ctx_برداشت_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
ایستا AVBufferRef *cuda_transfer_buffer_alloc(تهی *device_ref, size_t size)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->data;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    AVBufferRef *ret = پوچ;
    CUcontext dummy;
    تهی *host;

    اگر (CHECK_CU(cu->cu_Ctx_افزودن_Current(hwctx->cuda_ctx)) < 0)
        بازگشت av_buffer_alloc(size);

    اگر (CHECK_CU(cu->cuMemHostAlloc(&host, size, 0)) >= 0) {
        ret = av_buffer_create(host, size, cuda_transfer_buffer_free, device_ctx, 0);
        اگر (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_برداشت_Current(&dummy));
    بازگشت ret ? ret : av_buffer_alloc(size);
}
#endif

ایستا تهی cuda_frames_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    اگر (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_افزودن_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        برای (صحیح i = priv->cuarray_رقم_surfaces_used; i < priv->p.cuarray_رقم_surfaces; i++)
            اگر (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_برداشت_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_رقم_surfaces = 0;
    }
}

ایستا CUarray_format cuda_array_format_for_pix_fmt(شمارش AVPixelFormat fmt)
{
    انتخاب (fmt) {
#اگر HAVE_FFNVCODEC_CUARRAY
    حالت AV_PIX_FMT_NV12:      بازگشت CU_AD_FORMAT_NV12;
    حالت AV_PIX_FMT_P010:
    حالت AV_PIX_FMT_P012:
    حالت AV_PIX_FMT_P016:      بازگشت CU_AD_FORMAT_P016;
    حالت AV_PIX_FMT_NV16:      بازگشت CU_AD_FORMAT_NV16;
    حالت AV_PIX_FMT_P210:
    حالت AV_PIX_FMT_P212:
    حالت AV_PIX_FMT_P216:      بازگشت CU_AD_FORMAT_P216;
    حالت AV_PIX_FMT_NV24:      بازگشت CU_AD_FORMAT_YUV444_8BIT_SEMIPLANAR;
    حالت AV_PIX_FMT_P410:
    حالت AV_PIX_FMT_P412:
    حالت AV_PIX_FMT_P416:      بازگشت CU_AD_FORMAT_YUV444_16BIT_SEMIPLANAR;
    حالت AV_PIX_FMT_YUV420P:   بازگشت CU_AD_FORMAT_UINT8_PLANAR_420;
    حالت AV_PIX_FMT_YUV422P:   بازگشت CU_AD_FORMAT_UINT8_PLANAR_422;
    حالت AV_PIX_FMT_YUV444P:   بازگشت CU_AD_FORMAT_UINT8_PLANAR_444;
    حالت AV_PIX_FMT_YUV420P10: بازگشت CU_AD_FORMAT_UINT16_PLANAR_420;
    حالت AV_PIX_FMT_YUV422P10: بازگشت CU_AD_FORMAT_UINT16_PLANAR_422;
    حالت AV_PIX_FMT_YUV444P10:
    حالت AV_PIX_FMT_YUV444P10MSB:
    حالت AV_PIX_FMT_YUV444P12MSB:
    حالت AV_PIX_FMT_YUV444P16: بازگشت CU_AD_FORMAT_UINT16_PLANAR_444;
    حالت AV_PIX_FMT_0RGB32:
    حالت AV_PIX_FMT_0BGR32:
    حالت AV_PIX_FMT_RGB32:
    حالت AV_PIX_FMT_BGR32:     بازگشت CU_AD_FORMAT_UNSIGNED_INT8;
#endif
    پیشفرض:                   بازگشت 0;
    }
}

#اگر HAVE_FFNVCODEC_CUARRAY
ایستا unsigned صحیح cuda_array_numchannels_for_pix_fmt(شمارش AVPixelFormat fmt)
{
    انتخاب (fmt) {
    حالت AV_PIX_FMT_0RGB32:
    حالت AV_PIX_FMT_0BGR32:
    حالت AV_PIX_FMT_RGB32:
    حالت AV_PIX_FMT_BGR32:     بازگشت 4;
    پیشفرض:                   بازگشت 3;
    }
}
#endif

ایستا صحیح cuda_frames_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    صحیح err;

    اگر (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        بازگشت AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    اگر (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        بازگشت AVERROR(ENOSYS);
    }

#اگر HAVE_FFNVCODEC_CUARRAY
    اگر (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        بازگشت AVERROR(ENOSYS);
    }
#وگرنه
    اگر (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        بازگشت AVERROR(ENOSYS);
    }
#endif

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->internal->cuda_device));
    اگر (err < 0)
        بازگشت err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    اگر (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->shift_width, &priv->shift_height);

#اگر HAVE_FFNVCODEC_CUARRAY
    اگر (ctx->format == AV_PIX_FMT_CUARRAY) {
        اگر (!priv->p.cuarray_desc.Width)
            priv->p.cuarray_desc.Width = ctx->width;
        اگر (!priv->p.cuarray_desc.Height)
            priv->p.cuarray_desc.Height = ctx->height;
        اگر (!priv->p.cuarray_desc.رقم_Channels)
            priv->p.cuarray_desc.رقم_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        اگر (priv->p.cuarray_desc.Depth) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            بازگشت AVERROR(EINVAL);
        }

        اگر (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        اگر (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            بازگشت AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    اگر (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_رقم_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_رقم_surfaces, اندازه(*priv->p.cuarray_surfaces));
        اگر (!priv->p.cuarray_surfaces)
            بازگشت AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_افزودن_Current(hwctx->cuda_ctx));
        اگر (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            بازگشت err;
        }

        برای (صحیح i = 0; i < priv->p.cuarray_رقم_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            اگر (err < 0) {
                برای (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_برداشت_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                بازگشت err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_برداشت_Current(&dummy));
        اگر (err < 0)
            برو fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_رقم_surfaces, priv->p.cuarray_desc.Width, priv->p.cuarray_desc.Height);
    }
#endif

    اگر (!ctx->pool) {
        صحیح size = av_image_get_buffer_size(ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        اگر (size < 0) {
            err = size;
            برو fail;
        }

        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(size, ctx, cuda_pool_alloc, پوچ);
        اگر (!ffhwframesctx(ctx)->pool_internal) {
            err = AVERROR(ENOMEM);
            برو fail;
        }
    }

    بازگشت 0;

fail:
    cuda_frames_uninit(ctx);
    بازگشت err;
}

ایستا صحیح cuda_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#اگر HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;
#endif
    صحیح res;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    اگر (!frame->buf[0])
        بازگشت AVERROR(ENOMEM);

    اگر (ctx->format == AV_PIX_FMT_CUARRAY) {
#اگر HAVE_FFNVCODEC_CUARRAY
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)frame->buf[0]->data;
        اگر (!desc) {
            frame->format = ctx->format;
            frame->width  = ctx->width;
            frame->height = ctx->height;
            بازگشت 0;
        }
        frame->data[0] = (uint8_t*)desc->array;
        frame->data[1] = (uint8_t*)desc->index;

        res = CHECK_CU(cu->cu_Ctx_افزودن_Current(hwctx->cuda_ctx));
        اگر (res < 0)
            بازگشت res;

        برای (صحیح i = 0; i < FF_ARRAY_ELEMS(frame->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            اگر (arr_plane_res == CUDA_ERROR_INVALID_مقدار) {
                اگر (i > 0)
                    بشکن;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                اگر (res < 0)
                    برو fail;
            } وگرنه اگر (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                برو fail;
            } وگرنه {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                اگر (res < 0)
                    برو fail;
            }

            صحیح elem_size = ff_cuda_cuarray_elem_size(plane_desc.Format);
            اگر (elem_size <= 0) {
                res = AVERROR_BUG;
                برو fail;
            }

            frame->linesize[i] = plane_desc.Width * plane_desc.رقم_Channels * elem_size;

            اگر (arr_plane_res == CUDA_ERROR_INVALID_مقدار)
                بشکن;
        }

        res = CHECK_CU(cu->cu_Ctx_برداشت_Current(&dummy));
        اگر (res < 0)
            بازگشت res;
#وگرنه
        بازگشت AVERROR(ENOSYS);
#endif
    } وگرنه {
        res = av_image_fill_arrays(frame->data, frame->linesize, frame->buf[0]->data,
                                   ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        اگر (res < 0)
            بازگشت res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        اگر (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
            frame->data[2]     = frame->data[1];
            frame->data[1]     = frame->data[2] + frame->linesize[2] * AV_CEIL_RSHIFT(ctx->height, 1);
        }
    }

    frame->format = ctx->format;
    frame->width  = ctx->width;
    frame->height = ctx->height;

    بازگشت 0;

#اگر HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_برداشت_Current(&dummy));
    بازگشت res;
#endif
}

ایستا شمارش AVPixelFormat cuda_frame_hw_format(ثابت AVFrame *frame)
{
    اگر (!frame->hw_frames_ctx)
        بازگشت AV_PIX_FMT_NONE;
    بازگشت ((AVHWFramesContext *)frame->hw_frames_ctx->data)->format;
}

ایستا صحیح cuda_transfer_get_formats(AVHWFramesContext *ctx,
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

ایستا صحیح cuda_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    ثابت AVFrame *sw_frame = src->hw_frames_ctx ? dst : src;
    AVFrame *بالاترین_down = پوچ, *bottom_up_dst = پوچ;
    CUcontext dummy;
    صحیح i, ret, copy_queued = 0, bottom_up = 0;

    {
        شمارش AVPixelFormat src_fmt = cuda_frame_hw_format(src);
        شمارش AVPixelFormat dst_fmt = cuda_frame_hw_format(dst);
        اگر ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            بازگشت AVERROR(ENOSYS);
    }

    برای (i = 0; i < FF_ARRAY_ELEMS(sw_frame->linesize); i++)
        bottom_up |= sw_frame->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    اگر (bottom_up) {
        بالاترین_down = av_frame_alloc();
        اگر (!بالاترین_down)
            بازگشت AVERROR(ENOMEM);
        بالاترین_down->format = ctx->sw_format;
        بالاترین_down->width  = ctx->width;
        بالاترین_down->height = ctx->height;
        ret = av_hwframe_get_transfer_buffer((src->hw_frames_ctx ? src : dst)->hw_frames_ctx,
                                             بالاترین_down);
        اگر (ret < 0)
            برو free_بالاترین_down;
        بالاترین_down->width  = src->width;
        بالاترین_down->height = src->height;
        اگر (sw_frame == src) {
            av_image_copy2(بالاترین_down->data, بالاترین_down->linesize, src->data, src->linesize,
                           ctx->sw_format, src->width, src->height);
            src = بالاترین_down;
        } وگرنه {
            bottom_up_dst = dst;
            dst           = بالاترین_down;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_افزودن_Current(hwctx->cuda_ctx));
    اگر (ret < 0)
        برو free_بالاترین_down;

    /*
     * Copy one plane per iteration, bounded by the AVFrame linesizes. src and
     * dst always share the same sw_format (this path never converts), so they
     * are either both multi-planar or both single-plane.
     *
     * For a CUARRAY side, cuArrayGetPlane() returns the sub-array for plane i
     * of a multi-planar CUarray (NV12, P0xx, NV24, planar 4:4:4, ...).
     * cuArrayGetPlane() returns CUDA_ERROR_INVALID_VALUE either when the array
     * is not multi-planar or when the plane index exceeds its plane count:
     *   - i == 0: the array is packed (e.g. RGB), i.e. a single plane, so the
     *     whole array is used as that plane.
     *   - i  > 0: the planes of a multi-planar array always have a non-zero
     *     linesize, so a valid plane is never skipped by the loop bound;
     *     getting INVALID_VALUE here means src/dst disagree on the plane count,
     *     which is an inconsistency and is treated as an error (handled by the
     *     generic cures != CUDA_SUCCESS branch) rather than silently copying a
     *     subset of the planes.
     */
    برای (i = 0; i < FF_ARRAY_ELEMS(src->data) && src->linesize[i]; i++) {
        صحیح src_is_nonplanar_cuarray = 0;
        صحیح dst_is_nonplanar_cuarray = 0;

        صحیح bytewidth = av_image_get_linesize(ctx->sw_format, src->width, i);
        اگر (bytewidth < 0) {
            ret = bytewidth;
            برو fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .WidthInBytes  = bytewidth,
            .Height        = AV_CEIL_RSHIFT(src->height, ((i == 0 || i == 3) ? 0 : priv->shift_height)),
        };

        اگر (src->format == AV_PIX_FMT_CUDA) {
            cpy.srcMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->data[i];
        } وگرنه اگر (src->format == AV_PIX_FMT_CUARRAY) {
#اگر HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->data[0], i);
            اگر (cures == CUDA_ERROR_INVALID_مقدار && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->data[0];
                src_is_nonplanar_cuarray = 1;
            } وگرنه اگر (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                برو fail;
            }

            cpy.srcMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#وگرنه
            ret = AVERROR(ENOSYS);
            برو exit;
#endif
        } وگرنه {
            cpy.srcMemoryType = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->data[i];
        }

        اگر (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dstMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->data[i];
        } وگرنه اگر (dst->format == AV_PIX_FMT_CUARRAY) {
#اگر HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->data[0], i);
            اگر (cures == CUDA_ERROR_INVALID_مقدار && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->data[0];
                dst_is_nonplanar_cuarray = 1;
            } وگرنه اگر (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                برو fail;
            }

            cpy.dstMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#وگرنه
            ret = AVERROR(ENOSYS);
            برو exit;
#endif
        } وگرنه {
            cpy.dstMemoryType = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->data[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->stream));
        اگر (ret < 0)
            برو fail;
        copy_queued = 1;

        اگر (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            بشکن;
    }

    /* The caller may reuse host memory once the transfer returns. */
    اگر (!src->hw_frames_ctx || !dst->hw_frames_ctx) {
        ret = CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
        اگر (ret < 0)
            برو exit;
    }

fail:
    اگر (ret < 0 && copy_queued)
        CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
exit:
    CHECK_CU(cu->cu_Ctx_برداشت_Current(&dummy));

    اگر (bottom_up_dst && ret >= 0)
        av_image_copy2(bottom_up_dst->data, bottom_up_dst->linesize,
                       بالاترین_down->data, بالاترین_down->linesize,
                       ctx->sw_format, src->width, src->height);
free_بالاترین_down:
    av_frame_free(&بالاترین_down);

    بازگشت ret;
}

ایستا تهی cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    اگر (hwctx->p.internal) {
        CudaFunctions *cu = hwctx->internal.cuda_dl;

        اگر (hwctx->internal.is_allocated && hwctx->p.cuda_ctx) {
            اگر (hwctx->internal.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->internal.cuda_device));
            وگرنه اگر (!(hwctx->internal.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = پوچ;
        }

        cuda_free_functions(&hwctx->internal.cuda_dl);
        memset(&hwctx->internal, 0, اندازه(hwctx->internal));
        hwctx->p.internal = پوچ;
    }
}

ایستا صحیح cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    صحیح ret;

    hwctx->p.internal = &hwctx->internal;

    اگر (!hwctx->internal.cuda_dl) {
        ret = cuda_load_functions(&hwctx->internal.cuda_dl, ctx);
        اگر (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            برو error;
        }
    }

    بازگشت 0;

error:
    cuda_device_uninit(ctx);
    بازگشت ret;
}

ایستا صحیح cuda_context_init(AVHWDeviceContext *device_ctx, صحیح flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    صحیح ret, dev_active = 0;
    unsigned صحیح dev_flags = 0;

    ثابت unsigned صحیح desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->internal->cuda_dl;

    hwctx->internal->flags = flags;

    اگر (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->internal->cuda_device,
                       &dev_flags, &dev_active));
        اگر (ret < 0)
            بازگشت ret;

        اگر (dev_active && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            بازگشت AVERROR(ENOTSUP);
        } وگرنه اگر (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cuDevicePrimaryCtxSetFlags(hwctx->internal->cuda_device,
                           desired_flags));
            اگر (ret < 0)
                بازگشت ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->internal->cuda_device));
        اگر (ret < 0)
            بازگشت ret;
    } وگرنه اگر (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        اگر (ret < 0)
            بازگشت ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } وگرنه {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->internal->cuda_device));
        اگر (ret < 0)
            بازگشت ret;

        CHECK_CU(cu->cu_Ctx_برداشت_Current(&dummy));
    }

    hwctx->internal->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->stream = پوچ;

    بازگشت 0;
}

ایستا صحیح cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, صحیح *flags)
{
    AVDictionaryEntry *primary_ctx_opt = av_dict_get(opts, "primary_ctx", پوچ, 0);
    AVDictionaryEntry *current_ctx_opt = av_dict_get(opts, "current_ctx", پوچ, 0);

    صحیح use_primary_ctx = 0, use_current_ctx = 0;
    اگر (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->مقدار, پوچ, 10);

    اگر (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->مقدار, پوچ, 10);

    اگر (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        بازگشت AVERROR(EINVAL);
    }

    اگر (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } وگرنه اگر (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    اگر (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } وگرنه اگر (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    بازگشت 0;
}

ایستا صحیح cuda_device_create(AVHWDeviceContext *device_ctx,
                              ثابت نویسه *device,
                              AVDictionary *opts, صحیح flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    صحیح ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    اگر (ret < 0)
        برو error;

    اگر (device)
        device_idx = strtol(device, پوچ, 0);

    ret = cuda_device_init(device_ctx);
    اگر (ret < 0)
        برو error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    اگر (ret < 0)
        برو error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->internal->cuda_device, device_idx));
    اگر (ret < 0)
        برو error;

    ret = cuda_context_init(device_ctx, flags);
    اگر (ret < 0)
        برو error;

    بازگشت 0;

error:
    cuda_device_uninit(device_ctx);
    بازگشت ret;
}

ایستا صحیح cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              صحیح flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ثابت نویسه *src_uuid = پوچ;
#اگر CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#endif
    صحیح ret, i, device_شمار;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    اگر (ret < 0)
        برو error;

#اگر CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#endif

    انتخاب (src_ctx->type) {
#اگر CONFIG_VULKAN
#define TYPE PFN_vkGetPhysicalDeviceProperties2
    حالت AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .pNext = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        بشکن;
    }
#undef TYPE
#endif
    پیشفرض:
        ret = AVERROR(ENOSYS);
        برو error;
    }

    اگر (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        برو error;
    }

    ret = cuda_device_init(device_ctx);
    اگر (ret < 0)
        برو error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    اگر (ret < 0)
        برو error;

    ret = CHECK_CU(cu->cu_Device_Get_شمار(&device_شمار));
    اگر (ret < 0)
        برو error;

    hwctx->internal->cuda_device = -1;
    برای (i = 0; i < device_شمار; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        اگر (ret < 0)
            برو error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        اگر (ret < 0)
            برو error;

        اگر (memcmp(src_uuid, uuid.bytes, اندازه (uuid.bytes)) == 0) {
            hwctx->internal->cuda_device = dev;
            بشکن;
        }
    }

    اگر (hwctx->internal->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        برو error;
    }

    ret = cuda_context_init(device_ctx, flags);
    اگر (ret < 0)
        برو error;

    بازگشت 0;

error:
    cuda_device_uninit(device_ctx);
    بازگشت ret;
}

ثابت HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_size    = اندازه(CUDADeviceContext),
    .frames_hwctx_size    = اندازه(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .frames_get_constraints = cuda_frames_get_constraints,
    .frames_init          = cuda_frames_init,
    .frames_uninit        = cuda_frames_uninit,
    .frames_get_buffer    = cuda_get_buffer,
    .transfer_get_formats = cuda_transfer_get_formats,
#اگر HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_buffer_alloc = cuda_transfer_buffer_alloc,
#endif
    .transfer_data_to     = cuda_transfer_data,
    .transfer_data_from   = cuda_transfer_data,

    .pix_fmts             = (ثابت شمارش AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#اگر HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#endif
                                                          AV_PIX_FMT_NONE },
};
