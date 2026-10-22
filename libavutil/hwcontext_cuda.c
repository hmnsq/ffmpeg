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

#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_cuda_internal.h"
#ಯದಿ CONFIG_VULKAN
#ಅನ್ತರ್ಭಾವ "hwcontext_vulkan.h"
#endif
#ಅನ್ತರ್ಭಾವ "cuda_check.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"
#ಅನ್ತರ್ಭಾವ "imgutils.h"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ CUDAFramesContext {
    AVCUDAFramesContext p;

    ಪೂರ್ಣಾಙ್ಕ shift_width, shift_height;
    ಪೂರ್ಣಾಙ್ಕ tex_alignment;

    ಪೂರ್ಣಾಙ್ಕ cuarray_ಅಂಕೆ_surfaces_used;
} CUDAFramesContext;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADeviceContextInternal internal;
} CUDADeviceContext;



#define CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

ಸ್ಥಿರ CUarray_format cuda_array_format_for_pix_fmt(ಗಣನಾ AVPixelFormat fmt);

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cuda_frames_get_constraints(AVHWDeviceContext *ctx,
                                       ಧ್ರುವ ಶೂನ್ಯ *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ಧ್ರುವ AVCUDAHWConfig *config = hwconfig;
    ಗಣನಾ AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    ಪೂರ್ಣಾಙ್ಕ n = 0;

    ಯದಿ (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, ಪರಿಮಾಣ(*constraints->valid_hw_formats));
        ಯದಿ (!constraints->valid_hw_formats)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } ಅನ್ಯಥಾ {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, ಪರಿಮಾಣ(*constraints->valid_hw_formats));
        ಯದಿ (!constraints->valid_hw_formats)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#ಯದಿ HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#ಅನ್ಯಥಾ
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#endif
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    ಪರಿಮಾಣ(*constraints->valid_sw_formats));
    ಯದಿ (!constraints->valid_sw_formats)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    n = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < AV_PIX_FMT_NB; i++) {
        ಯದಿ (req_fmt == AV_PIX_FMT_CUARRAY) {
            ಯದಿ (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } ಅನ್ಯಥಾ {
            ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            ಯದಿ (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#ಯದಿ CONFIG_VULKAN
    ಯದಿ (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#endif
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ cuda_buffer_free(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));

    ಯದಿ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)data;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } ಅನ್ಯಥಾ {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)data));
    }

    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
}

ಸ್ಥಿರ AVBufferRef *cuda_pool_alloc(ಶೂನ್ಯ *opaque, size_t size)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    AVBufferRef *ret = ರಿಕ್ತ;
    CUcontext dummy = ರಿಕ್ತ;
    CUdeviceptr data;
    ಪೂರ್ಣಾಙ್ಕ err;

    err = CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಯದಿ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = av_mallocz(ಪರಿಮಾಣ(*desc));
        ಯದಿ (!desc)
            ಗಚ್ಛ done;

        ಯದಿ (priv->p.cuarray_ಅಂಕೆ_surfaces > 0) {
            ಯದಿ (priv->cuarray_ಅಂಕೆ_surfaces_used >= priv->p.cuarray_ಅಂಕೆ_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                ಗಚ್ಛ done;
            }
            desc->index = priv->cuarray_ಅಂಕೆ_surfaces_used++;
            desc->array = priv->p.cuarray_surfaces[desc->index];
        } ಅನ್ಯಥಾ {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            ಯದಿ (err < 0) {
                av_free(desc);
                ಗಚ್ಛ done;
            }
        }

        ret = av_buffer_create((uint8_t*)desc, ಪರಿಮಾಣ(*desc), cuda_buffer_free, ctx, 0);
        ಯದಿ (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            ಗಚ್ಛ done;
        }

        ಗಚ್ಛ done;
    }

    err = CHECK_CU(cu->cuMemAlloc(&data, size));
    ಯದಿ (err < 0)
        ಗಚ್ಛ done;

    ret = av_buffer_create((uint8_t*)data, size, cuda_buffer_free, ctx, 0);
    ಯದಿ (!ret) {
        CHECK_CU(cu->cuMemFree(data));
        ಗಚ್ಛ done;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
done:
    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
    ಪ್ರತ್ಯಾಗಮ ret;
}

#ಯದಿ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
ಸ್ಥಿರ ಶೂನ್ಯ cuda_transfer_buffer_free(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(data));
    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
ಸ್ಥಿರ AVBufferRef *cuda_transfer_buffer_alloc(ಶೂನ್ಯ *device_ref, size_t size)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->data;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    AVBufferRef *ret = ರಿಕ್ತ;
    CUcontext dummy;
    ಶೂನ್ಯ *host;

    ಯದಿ (CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx)) < 0)
        ಪ್ರತ್ಯಾಗಮ av_buffer_alloc(size);

    ಯದಿ (CHECK_CU(cu->cuMemHostAlloc(&host, size, 0)) >= 0) {
        ret = av_buffer_create(host, size, cuda_transfer_buffer_free, device_ctx, 0);
        ಯದಿ (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
    ಪ್ರತ್ಯಾಗಮ ret ? ret : av_buffer_alloc(size);
}
#endif

ಸ್ಥಿರ ಶೂನ್ಯ cuda_frames_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    ಯದಿ (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = priv->cuarray_ಅಂಕೆ_surfaces_used; i < priv->p.cuarray_ಅಂಕೆ_surfaces; i++)
            ಯದಿ (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_ಅಂಕೆ_surfaces = 0;
    }
}

ಸ್ಥಿರ CUarray_format cuda_array_format_for_pix_fmt(ಗಣನಾ AVPixelFormat fmt)
{
    ವಿಕಲ್ಪ (fmt) {
#ಯದಿ HAVE_FFNVCODEC_CUARRAY
    ಪಕ್ಷ AV_PIX_FMT_NV12:      ಪ್ರತ್ಯಾಗಮ CU_AD_FORMAT_NV12;
    ಪಕ್ಷ AV_PIX_FMT_P010:
    ಪಕ್ಷ AV_PIX_FMT_P012:
    ಪಕ್ಷ AV_PIX_FMT_P016:      ಪ್ರತ್ಯಾಗಮ CU_AD_FORMAT_P016;
    ಪಕ್ಷ AV_PIX_FMT_NV16:      ಪ್ರತ್ಯಾಗಮ CU_AD_FORMAT_NV16;
    ಪಕ್ಷ AV_PIX_FMT_P210:
    ಪಕ್ಷ AV_PIX_FMT_P212:
    ಪಕ್ಷ AV_PIX_FMT_P216:      ಪ್ರತ್ಯಾಗಮ CU_AD_FORMAT_P216;
    ಪಕ್ಷ AV_PIX_FMT_NV24:      ಪ್ರತ್ಯಾಗಮ CU_AD_FORMAT_YUV444_8BIT_SEMIPLANAR;
    ಪಕ್ಷ AV_PIX_FMT_P410:
    ಪಕ್ಷ AV_PIX_FMT_P412:
    ಪಕ್ಷ AV_PIX_FMT_P416:      ಪ್ರತ್ಯಾಗಮ CU_AD_FORMAT_YUV444_16BIT_SEMIPLANAR;
    ಪಕ್ಷ AV_PIX_FMT_YUV420P:   ಪ್ರತ್ಯಾಗಮ CU_AD_FORMAT_UINT8_PLANAR_420;
    ಪಕ್ಷ AV_PIX_FMT_YUV422P:   ಪ್ರತ್ಯಾಗಮ CU_AD_FORMAT_UINT8_PLANAR_422;
    ಪಕ್ಷ AV_PIX_FMT_YUV444P:   ಪ್ರತ್ಯಾಗಮ CU_AD_FORMAT_UINT8_PLANAR_444;
    ಪಕ್ಷ AV_PIX_FMT_YUV420P10: ಪ್ರತ್ಯಾಗಮ CU_AD_FORMAT_UINT16_PLANAR_420;
    ಪಕ್ಷ AV_PIX_FMT_YUV422P10: ಪ್ರತ್ಯಾಗಮ CU_AD_FORMAT_UINT16_PLANAR_422;
    ಪಕ್ಷ AV_PIX_FMT_YUV444P10:
    ಪಕ್ಷ AV_PIX_FMT_YUV444P10MSB:
    ಪಕ್ಷ AV_PIX_FMT_YUV444P12MSB:
    ಪಕ್ಷ AV_PIX_FMT_YUV444P16: ಪ್ರತ್ಯಾಗಮ CU_AD_FORMAT_UINT16_PLANAR_444;
    ಪಕ್ಷ AV_PIX_FMT_0RGB32:
    ಪಕ್ಷ AV_PIX_FMT_0BGR32:
    ಪಕ್ಷ AV_PIX_FMT_RGB32:
    ಪಕ್ಷ AV_PIX_FMT_BGR32:     ಪ್ರತ್ಯಾಗಮ CU_AD_FORMAT_UNSIGNED_INT8;
#endif
    ಸ್ವಭಾವ:                   ಪ್ರತ್ಯಾಗಮ 0;
    }
}

#ಯದಿ HAVE_FFNVCODEC_CUARRAY
ಸ್ಥಿರ unsigned ಪೂರ್ಣಾಙ್ಕ cuda_array_numchannels_for_pix_fmt(ಗಣನಾ AVPixelFormat fmt)
{
    ವಿಕಲ್ಪ (fmt) {
    ಪಕ್ಷ AV_PIX_FMT_0RGB32:
    ಪಕ್ಷ AV_PIX_FMT_0BGR32:
    ಪಕ್ಷ AV_PIX_FMT_RGB32:
    ಪಕ್ಷ AV_PIX_FMT_BGR32:     ಪ್ರತ್ಯಾಗಮ 4;
    ಸ್ವಭಾವ:                   ಪ್ರತ್ಯಾಗಮ 3;
    }
}
#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cuda_frames_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    ಪೂರ್ಣಾಙ್ಕ err;

    ಯದಿ (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    ಯದಿ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

#ಯದಿ HAVE_FFNVCODEC_CUARRAY
    ಯದಿ (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }
#ಅನ್ಯಥಾ
    ಯದಿ (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }
#endif

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->internal->cuda_device));
    ಯದಿ (err < 0)
        ಪ್ರತ್ಯಾಗಮ err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    ಯದಿ (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->shift_width, &priv->shift_height);

#ಯದಿ HAVE_FFNVCODEC_CUARRAY
    ಯದಿ (ctx->format == AV_PIX_FMT_CUARRAY) {
        ಯದಿ (!priv->p.cuarray_desc.Width)
            priv->p.cuarray_desc.Width = ctx->width;
        ಯದಿ (!priv->p.cuarray_desc.Height)
            priv->p.cuarray_desc.Height = ctx->height;
        ಯದಿ (!priv->p.cuarray_desc.ಅಂಕೆ_Channels)
            priv->p.cuarray_desc.ಅಂಕೆ_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        ಯದಿ (priv->p.cuarray_desc.Depth) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }

        ಯದಿ (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        ಯದಿ (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            ಪ್ರತ್ಯಾಗಮ AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    ಯದಿ (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_ಅಂಕೆ_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_ಅಂಕೆ_surfaces, ಪರಿಮಾಣ(*priv->p.cuarray_surfaces));
        ಯದಿ (!priv->p.cuarray_surfaces)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));
        ಯದಿ (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            ಪ್ರತ್ಯಾಗಮ err;
        }

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < priv->p.cuarray_ಅಂಕೆ_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            ಯದಿ (err < 0) {
                ಪ್ರತಿ (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                ಪ್ರತ್ಯಾಗಮ err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
        ಯದಿ (err < 0)
            ಗಚ್ಛ fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_ಅಂಕೆ_surfaces, priv->p.cuarray_desc.Width, priv->p.cuarray_desc.Height);
    }
#endif

    ಯದಿ (!ctx->pool) {
        ಪೂರ್ಣಾಙ್ಕ size = av_image_get_buffer_size(ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        ಯದಿ (size < 0) {
            err = size;
            ಗಚ್ಛ fail;
        }

        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(size, ctx, cuda_pool_alloc, ರಿಕ್ತ);
        ಯದಿ (!ffhwframesctx(ctx)->pool_internal) {
            err = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    cuda_frames_uninit(ctx);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cuda_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#ಯದಿ HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;
#endif
    ಪೂರ್ಣಾಙ್ಕ res;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ಯದಿ (!frame->buf[0])
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಯದಿ (ctx->format == AV_PIX_FMT_CUARRAY) {
#ಯದಿ HAVE_FFNVCODEC_CUARRAY
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)frame->buf[0]->data;
        ಯದಿ (!desc) {
            frame->format = ctx->format;
            frame->width  = ctx->width;
            frame->height = ctx->height;
            ಪ್ರತ್ಯಾಗಮ 0;
        }
        frame->data[0] = (uint8_t*)desc->array;
        frame->data[1] = (uint8_t*)desc->index;

        res = CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));
        ಯದಿ (res < 0)
            ಪ್ರತ್ಯಾಗಮ res;

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(frame->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            ಯದಿ (arr_plane_res == CUDA_ERROR_INVALID_ಮೌಲ್ಯ) {
                ಯದಿ (i > 0)
                    ಭಙ್ಗ;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                ಯದಿ (res < 0)
                    ಗಚ್ಛ fail;
            } ಅನ್ಯಥಾ ಯದಿ (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                ಗಚ್ಛ fail;
            } ಅನ್ಯಥಾ {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                ಯದಿ (res < 0)
                    ಗಚ್ಛ fail;
            }

            ಪೂರ್ಣಾಙ್ಕ elem_size = ff_cuda_cuarray_elem_size(plane_desc.Format);
            ಯದಿ (elem_size <= 0) {
                res = AVERROR_BUG;
                ಗಚ್ಛ fail;
            }

            frame->linesize[i] = plane_desc.Width * plane_desc.ಅಂಕೆ_Channels * elem_size;

            ಯದಿ (arr_plane_res == CUDA_ERROR_INVALID_ಮೌಲ್ಯ)
                ಭಙ್ಗ;
        }

        res = CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
        ಯದಿ (res < 0)
            ಪ್ರತ್ಯಾಗಮ res;
#ಅನ್ಯಥಾ
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
#endif
    } ಅನ್ಯಥಾ {
        res = av_image_fill_arrays(frame->data, frame->linesize, frame->buf[0]->data,
                                   ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        ಯದಿ (res < 0)
            ಪ್ರತ್ಯಾಗಮ res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        ಯದಿ (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
            frame->data[2]     = frame->data[1];
            frame->data[1]     = frame->data[2] + frame->linesize[2] * AV_CEIL_RSHIFT(ctx->height, 1);
        }
    }

    frame->format = ctx->format;
    frame->width  = ctx->width;
    frame->height = ctx->height;

    ಪ್ರತ್ಯಾಗಮ 0;

#ಯದಿ HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
    ಪ್ರತ್ಯಾಗಮ res;
#endif
}

ಸ್ಥಿರ ಗಣನಾ AVPixelFormat cuda_frame_hw_format(ಧ್ರುವ AVFrame *frame)
{
    ಯದಿ (!frame->hw_frames_ctx)
        ಪ್ರತ್ಯಾಗಮ AV_PIX_FMT_NONE;
    ಪ್ರತ್ಯಾಗಮ ((AVHWFramesContext *)frame->hw_frames_ctx->data)->format;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     ಗಣನಾ AVHWFrameTransferDirection dir,
                                     ಗಣನಾ AVPixelFormat **formats)
{
    ಗಣನಾ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ಪರಿಮಾಣ(*fmts));
    ಯದಿ (!fmts)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cuda_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 ಧ್ರುವ AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    ಧ್ರುವ AVFrame *sw_frame = src->hw_frames_ctx ? dst : src;
    AVFrame *ತುದಿ_down = ರಿಕ್ತ, *bottom_up_dst = ರಿಕ್ತ;
    CUcontext dummy;
    ಪೂರ್ಣಾಙ್ಕ i, ret, copy_queued = 0, bottom_up = 0;

    {
        ಗಣನಾ AVPixelFormat src_fmt = cuda_frame_hw_format(src);
        ಗಣನಾ AVPixelFormat dst_fmt = cuda_frame_hw_format(dst);
        ಯದಿ ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(sw_frame->linesize); i++)
        bottom_up |= sw_frame->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    ಯದಿ (bottom_up) {
        ತುದಿ_down = av_frame_alloc();
        ಯದಿ (!ತುದಿ_down)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        ತುದಿ_down->format = ctx->sw_format;
        ತುದಿ_down->width  = ctx->width;
        ತುದಿ_down->height = ctx->height;
        ret = av_hwframe_get_transfer_buffer((src->hw_frames_ctx ? src : dst)->hw_frames_ctx,
                                             ತುದಿ_down);
        ಯದಿ (ret < 0)
            ಗಚ್ಛ free_ತುದಿ_down;
        ತುದಿ_down->width  = src->width;
        ತುದಿ_down->height = src->height;
        ಯದಿ (sw_frame == src) {
            av_image_copy2(ತುದಿ_down->data, ತುದಿ_down->linesize, src->data, src->linesize,
                           ctx->sw_format, src->width, src->height);
            src = ತುದಿ_down;
        } ಅನ್ಯಥಾ {
            bottom_up_dst = dst;
            dst           = ತುದಿ_down;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));
    ಯದಿ (ret < 0)
        ಗಚ್ಛ free_ತುದಿ_down;

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
    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(src->data) && src->linesize[i]; i++) {
        ಪೂರ್ಣಾಙ್ಕ src_is_nonplanar_cuarray = 0;
        ಪೂರ್ಣಾಙ್ಕ dst_is_nonplanar_cuarray = 0;

        ಪೂರ್ಣಾಙ್ಕ bytewidth = av_image_get_linesize(ctx->sw_format, src->width, i);
        ಯದಿ (bytewidth < 0) {
            ret = bytewidth;
            ಗಚ್ಛ fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .WidthInBytes  = bytewidth,
            .Height        = AV_CEIL_RSHIFT(src->height, ((i == 0 || i == 3) ? 0 : priv->shift_height)),
        };

        ಯದಿ (src->format == AV_PIX_FMT_CUDA) {
            cpy.srcMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->data[i];
        } ಅನ್ಯಥಾ ಯದಿ (src->format == AV_PIX_FMT_CUARRAY) {
#ಯದಿ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->data[0], i);
            ಯದಿ (cures == CUDA_ERROR_INVALID_ಮೌಲ್ಯ && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->data[0];
                src_is_nonplanar_cuarray = 1;
            } ಅನ್ಯಥಾ ಯದಿ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                ಗಚ್ಛ fail;
            }

            cpy.srcMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#ಅನ್ಯಥಾ
            ret = AVERROR(ENOSYS);
            ಗಚ್ಛ exit;
#endif
        } ಅನ್ಯಥಾ {
            cpy.srcMemoryType = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->data[i];
        }

        ಯದಿ (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dstMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->data[i];
        } ಅನ್ಯಥಾ ಯದಿ (dst->format == AV_PIX_FMT_CUARRAY) {
#ಯದಿ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->data[0], i);
            ಯದಿ (cures == CUDA_ERROR_INVALID_ಮೌಲ್ಯ && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->data[0];
                dst_is_nonplanar_cuarray = 1;
            } ಅನ್ಯಥಾ ಯದಿ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                ಗಚ್ಛ fail;
            }

            cpy.dstMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#ಅನ್ಯಥಾ
            ret = AVERROR(ENOSYS);
            ಗಚ್ಛ exit;
#endif
        } ಅನ್ಯಥಾ {
            cpy.dstMemoryType = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->data[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->stream));
        ಯದಿ (ret < 0)
            ಗಚ್ಛ fail;
        copy_queued = 1;

        ಯದಿ (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            ಭಙ್ಗ;
    }

    /* The caller may reuse host memory once the transfer returns. */
    ಯದಿ (!src->hw_frames_ctx || !dst->hw_frames_ctx) {
        ret = CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
        ಯದಿ (ret < 0)
            ಗಚ್ಛ exit;
    }

fail:
    ಯದಿ (ret < 0 && copy_queued)
        CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
exit:
    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));

    ಯದಿ (bottom_up_dst && ret >= 0)
        av_image_copy2(bottom_up_dst->data, bottom_up_dst->linesize,
                       ತುದಿ_down->data, ತುದಿ_down->linesize,
                       ctx->sw_format, src->width, src->height);
free_ತುದಿ_down:
    av_frame_free(&ತುದಿ_down);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಶೂನ್ಯ cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    ಯದಿ (hwctx->p.internal) {
        CudaFunctions *cu = hwctx->internal.cuda_dl;

        ಯದಿ (hwctx->internal.is_allocated && hwctx->p.cuda_ctx) {
            ಯದಿ (hwctx->internal.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->internal.cuda_device));
            ಅನ್ಯಥಾ ಯದಿ (!(hwctx->internal.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = ರಿಕ್ತ;
        }

        cuda_free_functions(&hwctx->internal.cuda_dl);
        memset(&hwctx->internal, 0, ಪರಿಮಾಣ(hwctx->internal));
        hwctx->p.internal = ರಿಕ್ತ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    ಪೂರ್ಣಾಙ್ಕ ret;

    hwctx->p.internal = &hwctx->internal;

    ಯದಿ (!hwctx->internal.cuda_dl) {
        ret = cuda_load_functions(&hwctx->internal.cuda_dl, ctx);
        ಯದಿ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            ಗಚ್ಛ error;
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;

error:
    cuda_device_uninit(ctx);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cuda_context_init(AVHWDeviceContext *device_ctx, ಪೂರ್ಣಾಙ್ಕ flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    ಪೂರ್ಣಾಙ್ಕ ret, dev_active = 0;
    unsigned ಪೂರ್ಣಾಙ್ಕ dev_flags = 0;

    ಧ್ರುವ unsigned ಪೂರ್ಣಾಙ್ಕ desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->internal->cuda_dl;

    hwctx->internal->flags = flags;

    ಯದಿ (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->internal->cuda_device,
                       &dev_flags, &dev_active));
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;

        ಯದಿ (dev_active && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOTSUP);
        } ಅನ್ಯಥಾ ಯದಿ (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cuDevicePrimaryCtxSetFlags(hwctx->internal->cuda_device,
                           desired_flags));
            ಯದಿ (ret < 0)
                ಪ್ರತ್ಯಾಗಮ ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->internal->cuda_device));
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
    } ಅನ್ಯಥಾ ಯದಿ (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } ಅನ್ಯಥಾ {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->internal->cuda_device));
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;

        CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
    }

    hwctx->internal->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->stream = ರಿಕ್ತ;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ *flags)
{
    AVDictionaryEntry *primary_ctx_opt = av_dict_get(opts, "primary_ctx", ರಿಕ್ತ, 0);
    AVDictionaryEntry *current_ctx_opt = av_dict_get(opts, "current_ctx", ರಿಕ್ತ, 0);

    ಪೂರ್ಣಾಙ್ಕ use_primary_ctx = 0, use_current_ctx = 0;
    ಯದಿ (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->ಮೌಲ್ಯ, ರಿಕ್ತ, 10);

    ಯದಿ (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->ಮೌಲ್ಯ, ರಿಕ್ತ, 10);

    ಯದಿ (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    ಯದಿ (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } ಅನ್ಯಥಾ ಯದಿ (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    ಯದಿ (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } ಅನ್ಯಥಾ ಯದಿ (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cuda_device_create(AVHWDeviceContext *device_ctx,
                              ಧ್ರುವ ವರ್ಣ *device,
                              AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ಪೂರ್ಣಾಙ್ಕ ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ error;

    ಯದಿ (device)
        device_idx = strtol(device, ರಿಕ್ತ, 0);

    ret = cuda_device_init(device_ctx);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    ಯದಿ (ret < 0)
        ಗಚ್ಛ error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->internal->cuda_device, device_idx));
    ಯದಿ (ret < 0)
        ಗಚ್ಛ error;

    ret = cuda_context_init(device_ctx, flags);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ error;

    ಪ್ರತ್ಯಾಗಮ 0;

error:
    cuda_device_uninit(device_ctx);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              ಪೂರ್ಣಾಙ್ಕ flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ಧ್ರುವ ವರ್ಣ *src_uuid = ರಿಕ್ತ;
#ಯದಿ CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#endif
    ಪೂರ್ಣಾಙ್ಕ ret, i, device_ಎಣಿಕೆ;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ error;

#ಯದಿ CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#endif

    ವಿಕಲ್ಪ (src_ctx->type) {
#ಯದಿ CONFIG_VULKAN
#define TYPE PFN_vkGetPhysicalDeviceProperties2
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .pNext = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        ಭಙ್ಗ;
    }
#undef TYPE
#endif
    ಸ್ವಭಾವ:
        ret = AVERROR(ENOSYS);
        ಗಚ್ಛ error;
    }

    ಯದಿ (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        ಗಚ್ಛ error;
    }

    ret = cuda_device_init(device_ctx);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    ಯದಿ (ret < 0)
        ಗಚ್ಛ error;

    ret = CHECK_CU(cu->cu_Device_Get_ಎಣಿಕೆ(&device_ಎಣಿಕೆ));
    ಯದಿ (ret < 0)
        ಗಚ್ಛ error;

    hwctx->internal->cuda_device = -1;
    ಪ್ರತಿ (i = 0; i < device_ಎಣಿಕೆ; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        ಯದಿ (ret < 0)
            ಗಚ್ಛ error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        ಯದಿ (ret < 0)
            ಗಚ್ಛ error;

        ಯದಿ (memcmp(src_uuid, uuid.bytes, ಪರಿಮಾಣ (uuid.bytes)) == 0) {
            hwctx->internal->cuda_device = dev;
            ಭಙ್ಗ;
        }
    }

    ಯದಿ (hwctx->internal->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        ಗಚ್ಛ error;
    }

    ret = cuda_context_init(device_ctx, flags);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ error;

    ಪ್ರತ್ಯಾಗಮ 0;

error:
    cuda_device_uninit(device_ctx);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಧ್ರುವ HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_size    = ಪರಿಮಾಣ(CUDADeviceContext),
    .frames_hwctx_size    = ಪರಿಮಾಣ(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .frames_get_constraints = cuda_frames_get_constraints,
    .frames_init          = cuda_frames_init,
    .frames_uninit        = cuda_frames_uninit,
    .frames_get_buffer    = cuda_get_buffer,
    .transfer_get_formats = cuda_transfer_get_formats,
#ಯದಿ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_buffer_alloc = cuda_transfer_buffer_alloc,
#endif
    .transfer_data_to     = cuda_transfer_data,
    .transfer_data_from   = cuda_transfer_data,

    .pix_fmts             = (ಧ್ರುವ ಗಣನಾ AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#ಯದಿ HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#endif
                                                          AV_PIX_FMT_NONE },
};
