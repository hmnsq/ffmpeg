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

#ضمن "buffer.h"
#ضمن "common.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_internal.h"
#ضمن "hwcontext_cuda_internal.h"
#إذا CONFIG_VULKAN
#ضمن "hwcontext_vulkan.h"
#endif
#ضمن "cuda_check.h"
#ضمن "mem.h"
#ضمن "pixdesc.h"
#ضمن "pixfmt.h"
#ضمن "imgutils.h"

تعريفنوع بنية CUDAFramesContext {
    AVCUDAFramesContext p;

    صحيح shift_width, shift_height;
    صحيح tex_alignment;

    صحيح cuarray_لمب_surfaces_used;
} CUDAFramesContext;

تعريفنوع بنية CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADeviceContextInternal internal;
} CUDADeviceContext;



#define CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

ساكن CUarray_format cuda_array_format_for_pix_fmt(تعداد AVPixelFormat fmt);

ساكن صحيح cuda_frames_get_constraints(AVHWDeviceContext *ctx,
                                       ثابت فراغ *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ثابت AVCUDAHWConfig *config = hwconfig;
    تعداد AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    صحيح n = 0;

    إذا (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
        إذا (!constraints->valid_hw_formats)
            أرجع AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } وإلا {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, حجم(*constraints->valid_hw_formats));
        إذا (!constraints->valid_hw_formats)
            أرجع AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#إذا HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#وإلا
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#endif
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    حجم(*constraints->valid_sw_formats));
    إذا (!constraints->valid_sw_formats)
        أرجع AVERROR(ENOMEM);

    n = 0;
    لكل (صحيح i = 0; i < AV_PIX_FMT_NB; i++) {
        إذا (req_fmt == AV_PIX_FMT_CUARRAY) {
            إذا (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } وإلا {
            ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            إذا (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#إذا CONFIG_VULKAN
    إذا (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#endif
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    أرجع 0;
}

ساكن فراغ cuda_buffer_free(فراغ *opaque, uint8_t *data)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_تور_Current(hwctx->cuda_ctx));

    إذا (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)data;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } وإلا {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)data));
    }

    CHECK_CU(cu->cu_Ctx_چرو_Current(&dummy));
}

ساكن AVBufferRef *cuda_pool_alloc(فراغ *opaque, size_t size)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    AVBufferRef *ret = عدم;
    CUcontext dummy = عدم;
    CUdeviceptr data;
    صحيح err;

    err = CHECK_CU(cu->cu_Ctx_تور_Current(hwctx->cuda_ctx));
    إذا (err < 0)
        أرجع عدم;

    إذا (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = av_mallocz(حجم(*desc));
        إذا (!desc)
            اذهب done;

        إذا (priv->p.cuarray_لمب_surfaces > 0) {
            إذا (priv->cuarray_لمب_surfaces_used >= priv->p.cuarray_لمب_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                اذهب done;
            }
            desc->index = priv->cuarray_لمب_surfaces_used++;
            desc->array = priv->p.cuarray_surfaces[desc->index];
        } وإلا {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            إذا (err < 0) {
                av_free(desc);
                اذهب done;
            }
        }

        ret = av_buffer_create((uint8_t*)desc, حجم(*desc), cuda_buffer_free, ctx, 0);
        إذا (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            اذهب done;
        }

        اذهب done;
    }

    err = CHECK_CU(cu->cuMemAlloc(&data, size));
    إذا (err < 0)
        اذهب done;

    ret = av_buffer_create((uint8_t*)data, size, cuda_buffer_free, ctx, 0);
    إذا (!ret) {
        CHECK_CU(cu->cuMemFree(data));
        اذهب done;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
done:
    CHECK_CU(cu->cu_Ctx_چرو_Current(&dummy));
    أرجع ret;
}

#إذا HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
ساكن فراغ cuda_transfer_buffer_free(فراغ *opaque, uint8_t *data)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_تور_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(data));
    CHECK_CU(cu->cu_Ctx_چرو_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
ساكن AVBufferRef *cuda_transfer_buffer_alloc(فراغ *device_ref, size_t size)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->data;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    AVBufferRef *ret = عدم;
    CUcontext dummy;
    فراغ *host;

    إذا (CHECK_CU(cu->cu_Ctx_تور_Current(hwctx->cuda_ctx)) < 0)
        أرجع av_buffer_alloc(size);

    إذا (CHECK_CU(cu->cuMemHostAlloc(&host, size, 0)) >= 0) {
        ret = av_buffer_create(host, size, cuda_transfer_buffer_free, device_ctx, 0);
        إذا (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_چرو_Current(&dummy));
    أرجع ret ? ret : av_buffer_alloc(size);
}
#endif

ساكن فراغ cuda_frames_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    إذا (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_تور_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        لكل (صحيح i = priv->cuarray_لمب_surfaces_used; i < priv->p.cuarray_لمب_surfaces; i++)
            إذا (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_چرو_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_لمب_surfaces = 0;
    }
}

ساكن CUarray_format cuda_array_format_for_pix_fmt(تعداد AVPixelFormat fmt)
{
    بدل (fmt) {
#إذا HAVE_FFNVCODEC_CUARRAY
    حالة AV_PIX_FMT_NV12:      أرجع CU_AD_FORMAT_NV12;
    حالة AV_PIX_FMT_P010:
    حالة AV_PIX_FMT_P012:
    حالة AV_PIX_FMT_P016:      أرجع CU_AD_FORMAT_P016;
    حالة AV_PIX_FMT_NV16:      أرجع CU_AD_FORMAT_NV16;
    حالة AV_PIX_FMT_P210:
    حالة AV_PIX_FMT_P212:
    حالة AV_PIX_FMT_P216:      أرجع CU_AD_FORMAT_P216;
    حالة AV_PIX_FMT_NV24:      أرجع CU_AD_FORMAT_YUV444_8BIT_SEMIPLANAR;
    حالة AV_PIX_FMT_P410:
    حالة AV_PIX_FMT_P412:
    حالة AV_PIX_FMT_P416:      أرجع CU_AD_FORMAT_YUV444_16BIT_SEMIPLANAR;
    حالة AV_PIX_FMT_YUV420P:   أرجع CU_AD_FORMAT_UINT8_PLANAR_420;
    حالة AV_PIX_FMT_YUV422P:   أرجع CU_AD_FORMAT_UINT8_PLANAR_422;
    حالة AV_PIX_FMT_YUV444P:   أرجع CU_AD_FORMAT_UINT8_PLANAR_444;
    حالة AV_PIX_FMT_YUV420P10: أرجع CU_AD_FORMAT_UINT16_PLANAR_420;
    حالة AV_PIX_FMT_YUV422P10: أرجع CU_AD_FORMAT_UINT16_PLANAR_422;
    حالة AV_PIX_FMT_YUV444P10:
    حالة AV_PIX_FMT_YUV444P10MSB:
    حالة AV_PIX_FMT_YUV444P12MSB:
    حالة AV_PIX_FMT_YUV444P16: أرجع CU_AD_FORMAT_UINT16_PLANAR_444;
    حالة AV_PIX_FMT_0RGB32:
    حالة AV_PIX_FMT_0BGR32:
    حالة AV_PIX_FMT_RGB32:
    حالة AV_PIX_FMT_BGR32:     أرجع CU_AD_FORMAT_UNSIGNED_INT8;
#endif
    افتراضي:                   أرجع 0;
    }
}

#إذا HAVE_FFNVCODEC_CUARRAY
ساكن unsigned صحيح cuda_array_numchannels_for_pix_fmt(تعداد AVPixelFormat fmt)
{
    بدل (fmt) {
    حالة AV_PIX_FMT_0RGB32:
    حالة AV_PIX_FMT_0BGR32:
    حالة AV_PIX_FMT_RGB32:
    حالة AV_PIX_FMT_BGR32:     أرجع 4;
    افتراضي:                   أرجع 3;
    }
}
#endif

ساكن صحيح cuda_frames_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    صحيح err;

    إذا (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        أرجع AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    إذا (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        أرجع AVERROR(ENOSYS);
    }

#إذا HAVE_FFNVCODEC_CUARRAY
    إذا (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        أرجع AVERROR(ENOSYS);
    }
#وإلا
    إذا (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        أرجع AVERROR(ENOSYS);
    }
#endif

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->internal->cuda_device));
    إذا (err < 0)
        أرجع err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    إذا (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->shift_width, &priv->shift_height);

#إذا HAVE_FFNVCODEC_CUARRAY
    إذا (ctx->format == AV_PIX_FMT_CUARRAY) {
        إذا (!priv->p.cuarray_desc.Width)
            priv->p.cuarray_desc.Width = ctx->width;
        إذا (!priv->p.cuarray_desc.Height)
            priv->p.cuarray_desc.Height = ctx->height;
        إذا (!priv->p.cuarray_desc.لمب_Channels)
            priv->p.cuarray_desc.لمب_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        إذا (priv->p.cuarray_desc.Depth) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            أرجع AVERROR(EINVAL);
        }

        إذا (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        إذا (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            أرجع AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    إذا (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_لمب_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_لمب_surfaces, حجم(*priv->p.cuarray_surfaces));
        إذا (!priv->p.cuarray_surfaces)
            أرجع AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_تور_Current(hwctx->cuda_ctx));
        إذا (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            أرجع err;
        }

        لكل (صحيح i = 0; i < priv->p.cuarray_لمب_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            إذا (err < 0) {
                لكل (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_چرو_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                أرجع err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_چرو_Current(&dummy));
        إذا (err < 0)
            اذهب fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_لمب_surfaces, priv->p.cuarray_desc.Width, priv->p.cuarray_desc.Height);
    }
#endif

    إذا (!ctx->pool) {
        صحيح size = av_image_get_buffer_size(ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        إذا (size < 0) {
            err = size;
            اذهب fail;
        }

        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(size, ctx, cuda_pool_alloc, عدم);
        إذا (!ffhwframesctx(ctx)->pool_internal) {
            err = AVERROR(ENOMEM);
            اذهب fail;
        }
    }

    أرجع 0;

fail:
    cuda_frames_uninit(ctx);
    أرجع err;
}

ساكن صحيح cuda_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#إذا HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;
#endif
    صحيح res;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    إذا (!frame->buf[0])
        أرجع AVERROR(ENOMEM);

    إذا (ctx->format == AV_PIX_FMT_CUARRAY) {
#إذا HAVE_FFNVCODEC_CUARRAY
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)frame->buf[0]->data;
        إذا (!desc) {
            frame->format = ctx->format;
            frame->width  = ctx->width;
            frame->height = ctx->height;
            أرجع 0;
        }
        frame->data[0] = (uint8_t*)desc->array;
        frame->data[1] = (uint8_t*)desc->index;

        res = CHECK_CU(cu->cu_Ctx_تور_Current(hwctx->cuda_ctx));
        إذا (res < 0)
            أرجع res;

        لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(frame->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            إذا (arr_plane_res == CUDA_ERROR_INVALID_درج) {
                إذا (i > 0)
                    اكسر;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                إذا (res < 0)
                    اذهب fail;
            } وإلا إذا (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                اذهب fail;
            } وإلا {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                إذا (res < 0)
                    اذهب fail;
            }

            صحيح elem_size = ff_cuda_cuarray_elem_size(plane_desc.Format);
            إذا (elem_size <= 0) {
                res = AVERROR_BUG;
                اذهب fail;
            }

            frame->linesize[i] = plane_desc.Width * plane_desc.لمب_Channels * elem_size;

            إذا (arr_plane_res == CUDA_ERROR_INVALID_درج)
                اكسر;
        }

        res = CHECK_CU(cu->cu_Ctx_چرو_Current(&dummy));
        إذا (res < 0)
            أرجع res;
#وإلا
        أرجع AVERROR(ENOSYS);
#endif
    } وإلا {
        res = av_image_fill_arrays(frame->data, frame->linesize, frame->buf[0]->data,
                                   ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        إذا (res < 0)
            أرجع res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        إذا (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
            frame->data[2]     = frame->data[1];
            frame->data[1]     = frame->data[2] + frame->linesize[2] * AV_CEIL_RSHIFT(ctx->height, 1);
        }
    }

    frame->format = ctx->format;
    frame->width  = ctx->width;
    frame->height = ctx->height;

    أرجع 0;

#إذا HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_چرو_Current(&dummy));
    أرجع res;
#endif
}

ساكن تعداد AVPixelFormat cuda_frame_hw_format(ثابت AVFrame *frame)
{
    إذا (!frame->hw_frames_ctx)
        أرجع AV_PIX_FMT_NONE;
    أرجع ((AVHWFramesContext *)frame->hw_frames_ctx->data)->format;
}

ساكن صحيح cuda_transfer_get_formats(AVHWFramesContext *ctx,
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

ساكن صحيح cuda_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    ثابت AVFrame *sw_frame = src->hw_frames_ctx ? dst : src;
    AVFrame *كولي_down = عدم, *bottom_up_dst = عدم;
    CUcontext dummy;
    صحيح i, ret, copy_queued = 0, bottom_up = 0;

    {
        تعداد AVPixelFormat src_fmt = cuda_frame_hw_format(src);
        تعداد AVPixelFormat dst_fmt = cuda_frame_hw_format(dst);
        إذا ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            أرجع AVERROR(ENOSYS);
    }

    لكل (i = 0; i < FF_ARRAY_ELEMS(sw_frame->linesize); i++)
        bottom_up |= sw_frame->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    إذا (bottom_up) {
        كولي_down = av_frame_alloc();
        إذا (!كولي_down)
            أرجع AVERROR(ENOMEM);
        كولي_down->format = ctx->sw_format;
        كولي_down->width  = ctx->width;
        كولي_down->height = ctx->height;
        ret = av_hwframe_get_transfer_buffer((src->hw_frames_ctx ? src : dst)->hw_frames_ctx,
                                             كولي_down);
        إذا (ret < 0)
            اذهب free_كولي_down;
        كولي_down->width  = src->width;
        كولي_down->height = src->height;
        إذا (sw_frame == src) {
            av_image_copy2(كولي_down->data, كولي_down->linesize, src->data, src->linesize,
                           ctx->sw_format, src->width, src->height);
            src = كولي_down;
        } وإلا {
            bottom_up_dst = dst;
            dst           = كولي_down;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_تور_Current(hwctx->cuda_ctx));
    إذا (ret < 0)
        اذهب free_كولي_down;

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
    لكل (i = 0; i < FF_ARRAY_ELEMS(src->data) && src->linesize[i]; i++) {
        صحيح src_is_nonplanar_cuarray = 0;
        صحيح dst_is_nonplanar_cuarray = 0;

        صحيح bytewidth = av_image_get_linesize(ctx->sw_format, src->width, i);
        إذا (bytewidth < 0) {
            ret = bytewidth;
            اذهب fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .WidthInBytes  = bytewidth,
            .Height        = AV_CEIL_RSHIFT(src->height, ((i == 0 || i == 3) ? 0 : priv->shift_height)),
        };

        إذا (src->format == AV_PIX_FMT_CUDA) {
            cpy.srcMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->data[i];
        } وإلا إذا (src->format == AV_PIX_FMT_CUARRAY) {
#إذا HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->data[0], i);
            إذا (cures == CUDA_ERROR_INVALID_درج && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->data[0];
                src_is_nonplanar_cuarray = 1;
            } وإلا إذا (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                اذهب fail;
            }

            cpy.srcMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#وإلا
            ret = AVERROR(ENOSYS);
            اذهب exit;
#endif
        } وإلا {
            cpy.srcMemoryType = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->data[i];
        }

        إذا (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dstMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->data[i];
        } وإلا إذا (dst->format == AV_PIX_FMT_CUARRAY) {
#إذا HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->data[0], i);
            إذا (cures == CUDA_ERROR_INVALID_درج && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->data[0];
                dst_is_nonplanar_cuarray = 1;
            } وإلا إذا (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                اذهب fail;
            }

            cpy.dstMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#وإلا
            ret = AVERROR(ENOSYS);
            اذهب exit;
#endif
        } وإلا {
            cpy.dstMemoryType = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->data[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->stream));
        إذا (ret < 0)
            اذهب fail;
        copy_queued = 1;

        إذا (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            اكسر;
    }

    /* The caller may reuse host memory once the transfer returns. */
    إذا (!src->hw_frames_ctx || !dst->hw_frames_ctx) {
        ret = CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
        إذا (ret < 0)
            اذهب exit;
    }

fail:
    إذا (ret < 0 && copy_queued)
        CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
exit:
    CHECK_CU(cu->cu_Ctx_چرو_Current(&dummy));

    إذا (bottom_up_dst && ret >= 0)
        av_image_copy2(bottom_up_dst->data, bottom_up_dst->linesize,
                       كولي_down->data, كولي_down->linesize,
                       ctx->sw_format, src->width, src->height);
free_كولي_down:
    av_frame_free(&كولي_down);

    أرجع ret;
}

ساكن فراغ cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    إذا (hwctx->p.internal) {
        CudaFunctions *cu = hwctx->internal.cuda_dl;

        إذا (hwctx->internal.is_allocated && hwctx->p.cuda_ctx) {
            إذا (hwctx->internal.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->internal.cuda_device));
            وإلا إذا (!(hwctx->internal.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = عدم;
        }

        cuda_free_functions(&hwctx->internal.cuda_dl);
        memset(&hwctx->internal, 0, حجم(hwctx->internal));
        hwctx->p.internal = عدم;
    }
}

ساكن صحيح cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    صحيح ret;

    hwctx->p.internal = &hwctx->internal;

    إذا (!hwctx->internal.cuda_dl) {
        ret = cuda_load_functions(&hwctx->internal.cuda_dl, ctx);
        إذا (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            اذهب error;
        }
    }

    أرجع 0;

error:
    cuda_device_uninit(ctx);
    أرجع ret;
}

ساكن صحيح cuda_context_init(AVHWDeviceContext *device_ctx, صحيح flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    صحيح ret, dev_active = 0;
    unsigned صحيح dev_flags = 0;

    ثابت unsigned صحيح desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->internal->cuda_dl;

    hwctx->internal->flags = flags;

    إذا (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->internal->cuda_device,
                       &dev_flags, &dev_active));
        إذا (ret < 0)
            أرجع ret;

        إذا (dev_active && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            أرجع AVERROR(ENOTSUP);
        } وإلا إذا (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cuDevicePrimaryCtxSetFlags(hwctx->internal->cuda_device,
                           desired_flags));
            إذا (ret < 0)
                أرجع ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->internal->cuda_device));
        إذا (ret < 0)
            أرجع ret;
    } وإلا إذا (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        إذا (ret < 0)
            أرجع ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } وإلا {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->internal->cuda_device));
        إذا (ret < 0)
            أرجع ret;

        CHECK_CU(cu->cu_Ctx_چرو_Current(&dummy));
    }

    hwctx->internal->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->stream = عدم;

    أرجع 0;
}

ساكن صحيح cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, صحيح *flags)
{
    AVDictionaryEntry *primary_ctx_opt = av_dict_get(opts, "primary_ctx", عدم, 0);
    AVDictionaryEntry *current_ctx_opt = av_dict_get(opts, "current_ctx", عدم, 0);

    صحيح use_primary_ctx = 0, use_current_ctx = 0;
    إذا (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->درج, عدم, 10);

    إذا (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->درج, عدم, 10);

    إذا (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        أرجع AVERROR(EINVAL);
    }

    إذا (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } وإلا إذا (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    إذا (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } وإلا إذا (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    أرجع 0;
}

ساكن صحيح cuda_device_create(AVHWDeviceContext *device_ctx,
                              ثابت حرف *device,
                              AVDictionary *opts, صحيح flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    صحيح ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    إذا (ret < 0)
        اذهب error;

    إذا (device)
        device_idx = strtol(device, عدم, 0);

    ret = cuda_device_init(device_ctx);
    إذا (ret < 0)
        اذهب error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    إذا (ret < 0)
        اذهب error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->internal->cuda_device, device_idx));
    إذا (ret < 0)
        اذهب error;

    ret = cuda_context_init(device_ctx, flags);
    إذا (ret < 0)
        اذهب error;

    أرجع 0;

error:
    cuda_device_uninit(device_ctx);
    أرجع ret;
}

ساكن صحيح cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              صحيح flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ثابت حرف *src_uuid = عدم;
#إذا CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#endif
    صحيح ret, i, device_كدي;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    إذا (ret < 0)
        اذهب error;

#إذا CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#endif

    بدل (src_ctx->type) {
#إذا CONFIG_VULKAN
#define TYPE PFN_vkGetPhysicalDeviceProperties2
    حالة AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .pNext = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        اكسر;
    }
#undef TYPE
#endif
    افتراضي:
        ret = AVERROR(ENOSYS);
        اذهب error;
    }

    إذا (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        اذهب error;
    }

    ret = cuda_device_init(device_ctx);
    إذا (ret < 0)
        اذهب error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    إذا (ret < 0)
        اذهب error;

    ret = CHECK_CU(cu->cu_Device_Get_كدي(&device_كدي));
    إذا (ret < 0)
        اذهب error;

    hwctx->internal->cuda_device = -1;
    لكل (i = 0; i < device_كدي; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        إذا (ret < 0)
            اذهب error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        إذا (ret < 0)
            اذهب error;

        إذا (memcmp(src_uuid, uuid.bytes, حجم (uuid.bytes)) == 0) {
            hwctx->internal->cuda_device = dev;
            اكسر;
        }
    }

    إذا (hwctx->internal->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        اذهب error;
    }

    ret = cuda_context_init(device_ctx, flags);
    إذا (ret < 0)
        اذهب error;

    أرجع 0;

error:
    cuda_device_uninit(device_ctx);
    أرجع ret;
}

ثابت HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_size    = حجم(CUDADeviceContext),
    .frames_hwctx_size    = حجم(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .frames_get_constraints = cuda_frames_get_constraints,
    .frames_init          = cuda_frames_init,
    .frames_uninit        = cuda_frames_uninit,
    .frames_get_buffer    = cuda_get_buffer,
    .transfer_get_formats = cuda_transfer_get_formats,
#إذا HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_buffer_alloc = cuda_transfer_buffer_alloc,
#endif
    .transfer_data_to     = cuda_transfer_data,
    .transfer_data_from   = cuda_transfer_data,

    .pix_fmts             = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#إذا HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#endif
                                                          AV_PIX_FMT_NONE },
};
