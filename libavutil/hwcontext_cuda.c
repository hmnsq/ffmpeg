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
#ಆದರೆ CONFIG_VULKAN
#ಅನ್ತರ್ಭಾವ "hwcontext_vulkan.h"
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "cuda_check.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"
#ಅನ್ತರ್ಭಾವ "imgutils.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ CUDAFramesContext {
    AVCUDAFramesContext p;

    ಪೂರ್ಣಾಂಕ ಸರಿಸು_ಅಗಲ, ಸರಿಸು_ಎತ್ತರ;
    ಪೂರ್ಣಾಂಕ tex_alignment;

    ಪೂರ್ಣಾಂಕ cuarray_ಅಂಕೆ_surfaces_ಬಳಸಿದ;
} CUDAFramesContext;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADevice_Context_ಆಂತರಿಕ ಆಂತರಿಕ;
} CUDADeviceContext;



#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

ಸ್ಥಿರ CUarray_format cuda_array_format_for_pix_fmt(ಎಣಿಕೆ AVPixelFormat fmt);

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cuda_ಚೌಕಟ್ಟುಗಳು_get_constraints(AVHWDeviceContext *ctx,
                                       ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ಸ್ಥಿರಾಂಕ AVCUDAHWConfig *config = hwconfig;
    ಎಣಿಕೆ AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    ಪೂರ್ಣಾಂಕ n = 0;

    ಆದರೆ (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, ಗಾತ್ರ(*constraints->valid_hw_formats));
        ಆದರೆ (!constraints->valid_hw_formats)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } ಇಲ್ಲದಿದ್ದರೆ {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, ಗಾತ್ರ(*constraints->valid_hw_formats));
        ಆದರೆ (!constraints->valid_hw_formats)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#ಆದರೆ HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#ಇಲ್ಲದಿದ್ದರೆ
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#ಆದರೆ_ಅಂತ್ಯ
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    ಗಾತ್ರ(*constraints->valid_sw_formats));
    ಆದರೆ (!constraints->valid_sw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    n = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AV_PIX_FMT_NB; i++) {
        ಆದರೆ (req_fmt == AV_PIX_FMT_CUARRAY) {
            ಆದರೆ (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            ಆದರೆ (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#ಆದರೆ CONFIG_VULKAN
    ಆದರೆ (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#ಆದರೆ_ಅಂತ್ಯ
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ cuda_ಬಫರ್_free(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->ಆಂತರಿಕ->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));

    ಆದರೆ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArray_ಚೌಕಟ್ಟು_Descriptor *desc = (AVCUDAArray_ಚೌಕಟ್ಟು_Descriptor*)ದತ್ತಾಂಶ;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } ಇಲ್ಲದಿದ್ದರೆ {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)ದತ್ತಾಂಶ));
    }

    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
}

ಸ್ಥಿರ AVBufferRef *cuda_pool_alloc(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->ಆಂತರಿಕ->cuda_dl;

    AVBufferRef *ret = ಖಾಲಿ;
    CUcontext dummy = ಖಾಲಿ;
    CUdeviceptr ದತ್ತಾಂಶ;
    ಪೂರ್ಣಾಂಕ err;

    err = CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಆದರೆ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArray_ಚೌಕಟ್ಟು_Descriptor *desc = av_mallocz(ಗಾತ್ರ(*desc));
        ಆದರೆ (!desc)
            ಹೋಗು ಮುಗಿದ;

        ಆದರೆ (priv->p.cuarray_ಅಂಕೆ_surfaces > 0) {
            ಆದರೆ (priv->cuarray_ಅಂಕೆ_surfaces_ಬಳಸಿದ >= priv->p.cuarray_ಅಂಕೆ_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                ಹೋಗು ಮುಗಿದ;
            }
            desc->ಸೂಚ್ಯಂಕ = priv->cuarray_ಅಂಕೆ_surfaces_ಬಳಸಿದ++;
            desc->array = priv->p.cuarray_surfaces[desc->ಸೂಚ್ಯಂಕ];
        } ಇಲ್ಲದಿದ್ದರೆ {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            ಆದರೆ (err < 0) {
                av_free(desc);
                ಹೋಗು ಮುಗಿದ;
            }
        }

        ret = av_ಬಫರ್_create((uint8_t*)desc, ಗಾತ್ರ(*desc), cuda_ಬಫರ್_free, ctx, 0);
        ಆದರೆ (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            ಹೋಗು ಮುಗಿದ;
        }

        ಹೋಗು ಮುಗಿದ;
    }

    err = CHECK_CU(cu->cuMemAlloc(&ದತ್ತಾಂಶ, ಗಾತ್ರ_2));
    ಆದರೆ (err < 0)
        ಹೋಗು ಮುಗಿದ;

    ret = av_ಬಫರ್_create((uint8_t*)ದತ್ತಾಂಶ, ಗಾತ್ರ_2, cuda_ಬಫರ್_free, ctx, 0);
    ಆದರೆ (!ret) {
        CHECK_CU(cu->cuMemFree(ದತ್ತಾಂಶ));
        ಹೋಗು ಮುಗಿದ;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
ಮುಗಿದ:
    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
    ಹಿಂತಿರುಗಿ ret;
}

#ಆದರೆ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
ಸ್ಥಿರ ಶೂನ್ಯ cuda_transfer_ಬಫರ್_free(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->ಆಂತರಿಕ->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(ದತ್ತಾಂಶ));
    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
ಸ್ಥಿರ AVBufferRef *cuda_transfer_ಬಫರ್_alloc(ಶೂನ್ಯ *device_ref, size_t ಗಾತ್ರ_2)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->ದತ್ತಾಂಶ;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->ಆಂತರಿಕ->cuda_dl;
    AVBufferRef *ret = ಖಾಲಿ;
    CUcontext dummy;
    ಶೂನ್ಯ *host;

    ಆದರೆ (CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx)) < 0)
        ಹಿಂತಿರುಗಿ av_ಬಫರ್_alloc(ಗಾತ್ರ_2);

    ಆದರೆ (CHECK_CU(cu->cuMemHostAlloc(&host, ಗಾತ್ರ_2, 0)) >= 0) {
        ret = av_ಬಫರ್_create(host, ಗಾತ್ರ_2, cuda_transfer_ಬಫರ್_free, device_ctx, 0);
        ಆದರೆ (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
    ಹಿಂತಿರುಗಿ ret ? ret : av_ಬಫರ್_alloc(ಗಾತ್ರ_2);
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ cuda_ಚೌಕಟ್ಟುಗಳು_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->ಆಂತರಿಕ->cuda_dl;

    ಆದರೆ (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = priv->cuarray_ಅಂಕೆ_surfaces_ಬಳಸಿದ; i < priv->p.cuarray_ಅಂಕೆ_surfaces; i++)
            ಆದರೆ (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_ಅಂಕೆ_surfaces = 0;
    }
}

ಸ್ಥಿರ CUarray_format cuda_array_format_for_pix_fmt(ಎಣಿಕೆ AVPixelFormat fmt)
{
    ಆಯ್ಕೆ (fmt) {
#ಆದರೆ HAVE_FFNVCODEC_CUARRAY
    ಸ್ಥಿತಿ AV_PIX_FMT_NV12:      ಹಿಂತಿರುಗಿ CU_AD_FORMAT_NV12;
    ಸ್ಥಿತಿ AV_PIX_FMT_P010:
    ಸ್ಥಿತಿ AV_PIX_FMT_P012:
    ಸ್ಥಿತಿ AV_PIX_FMT_P016:      ಹಿಂತಿರುಗಿ CU_AD_FORMAT_P016;
    ಸ್ಥಿತಿ AV_PIX_FMT_NV16:      ಹಿಂತಿರುಗಿ CU_AD_FORMAT_NV16;
    ಸ್ಥಿತಿ AV_PIX_FMT_P210:
    ಸ್ಥಿತಿ AV_PIX_FMT_P212:
    ಸ್ಥಿತಿ AV_PIX_FMT_P216:      ಹಿಂತಿರುಗಿ CU_AD_FORMAT_P216;
    ಸ್ಥಿತಿ AV_PIX_FMT_NV24:      ಹಿಂತಿರುಗಿ CU_AD_FORMAT_YUV444_8_ಬಿಟ್_SEMIPLANAR;
    ಸ್ಥಿತಿ AV_PIX_FMT_P410:
    ಸ್ಥಿತಿ AV_PIX_FMT_P412:
    ಸ್ಥಿತಿ AV_PIX_FMT_P416:      ಹಿಂತಿರುಗಿ CU_AD_FORMAT_YUV444_16_ಬಿಟ್_SEMIPLANAR;
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV420P:   ಹಿಂತಿರುಗಿ CU_AD_FORMAT_UINT8_PLANAR_420;
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV422P:   ಹಿಂತಿರುಗಿ CU_AD_FORMAT_UINT8_PLANAR_422;
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV444P:   ಹಿಂತಿರುಗಿ CU_AD_FORMAT_UINT8_PLANAR_444;
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV420P10: ಹಿಂತಿರುಗಿ CU_AD_FORMAT_UINT16_PLANAR_420;
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV422P10: ಹಿಂತಿರುಗಿ CU_AD_FORMAT_UINT16_PLANAR_422;
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV444P10:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV444P10MSB:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV444P12MSB:
    ಸ್ಥಿತಿ AV_PIX_FMT_YUV444P16: ಹಿಂತಿರುಗಿ CU_AD_FORMAT_UINT16_PLANAR_444;
    ಸ್ಥಿತಿ AV_PIX_FMT_0RGB32:
    ಸ್ಥಿತಿ AV_PIX_FMT_0BGR32:
    ಸ್ಥಿತಿ AV_PIX_FMT_RGB32:
    ಸ್ಥಿತಿ AV_PIX_FMT_BGR32:     ಹಿಂತಿರುಗಿ CU_AD_FORMAT_UNSIGNED_INT8;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:                   ಹಿಂತಿರುಗಿ 0;
    }
}

#ಆದರೆ HAVE_FFNVCODEC_CUARRAY
ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ cuda_array_numchannels_for_pix_fmt(ಎಣಿಕೆ AVPixelFormat fmt)
{
    ಆಯ್ಕೆ (fmt) {
    ಸ್ಥಿತಿ AV_PIX_FMT_0RGB32:
    ಸ್ಥಿತಿ AV_PIX_FMT_0BGR32:
    ಸ್ಥಿತಿ AV_PIX_FMT_RGB32:
    ಸ್ಥಿತಿ AV_PIX_FMT_BGR32:     ಹಿಂತಿರುಗಿ 4;
    ಪೂರ್ವನಿಯೋಜಿತ:                   ಹಿಂತಿರುಗಿ 3;
    }
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cuda_ಚೌಕಟ್ಟುಗಳು_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->ಆಂತರಿಕ->cuda_dl;
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    ಪೂರ್ಣಾಂಕ err;

    ಆದರೆ (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    ಆದರೆ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

#ಆದರೆ HAVE_FFNVCODEC_CUARRAY
    ಆದರೆ (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ಆದರೆ (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }
#ಆದರೆ_ಅಂತ್ಯ

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->ಆಂತರಿಕ->cuda_device));
    ಆದರೆ (err < 0)
        ಹಿಂತಿರುಗಿ err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    ಆದರೆ (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->ಸರಿಸು_ಅಗಲ, &priv->ಸರಿಸು_ಎತ್ತರ);

#ಆದರೆ HAVE_FFNVCODEC_CUARRAY
    ಆದರೆ (ctx->format == AV_PIX_FMT_CUARRAY) {
        ಆದರೆ (!priv->p.cuarray_desc.ಅಗಲ_2)
            priv->p.cuarray_desc.ಅಗಲ_2 = ctx->ಅಗಲ;
        ಆದರೆ (!priv->p.cuarray_desc.ಎತ್ತರ_2)
            priv->p.cuarray_desc.ಎತ್ತರ_2 = ctx->ಎತ್ತರ;
        ಆದರೆ (!priv->p.cuarray_desc.ಅಂಕೆ_Channels)
            priv->p.cuarray_desc.ಅಂಕೆ_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        ಆದರೆ (priv->p.cuarray_desc.ಆಳ_2) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }

        ಆದರೆ (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        ಆದರೆ (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            ಹಿಂತಿರುಗಿ AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    ಆದರೆ (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_ಅಂಕೆ_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_ಅಂಕೆ_surfaces, ಗಾತ್ರ(*priv->p.cuarray_surfaces));
        ಆದರೆ (!priv->p.cuarray_surfaces)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));
        ಆದರೆ (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            ಹಿಂತಿರುಗಿ err;
        }

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < priv->p.cuarray_ಅಂಕೆ_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            ಆದರೆ (err < 0) {
                ಗಾಗಿ (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                ಹಿಂತಿರುಗಿ err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
        ಆದರೆ (err < 0)
            ಹೋಗು fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_ಅಂಕೆ_surfaces, priv->p.cuarray_desc.ಅಗಲ_2, priv->p.cuarray_desc.ಎತ್ತರ_2);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!ctx->pool) {
        ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 = av_image_get_ಬಫರ್_ಗಾತ್ರ(ctx->sw_format, ctx->ಅಗಲ, ctx->ಎತ್ತರ, priv->tex_alignment);
        ಆದರೆ (ಗಾತ್ರ_2 < 0) {
            err = ಗಾತ್ರ_2;
            ಹೋಗು fail;
        }

        ffhwframesctx(ctx)->pool_ಆಂತರಿಕ =
            av_ಬಫರ್_pool_init2(ಗಾತ್ರ_2, ctx, cuda_pool_alloc, ಖಾಲಿ);
        ಆದರೆ (!ffhwframesctx(ctx)->pool_ಆಂತರಿಕ) {
            err = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }
    }

    ಹಿಂತಿರುಗಿ 0;

fail:
    cuda_ಚೌಕಟ್ಟುಗಳು_uninit(ctx);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cuda_get_ಬಫರ್(AVHWFramesContext *ctx, AVFrame *ಚೌಕಟ್ಟು)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#ಆದರೆ HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->ಆಂತರಿಕ->cuda_dl;

    CUcontext dummy;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ಣಾಂಕ res;

    ಚೌಕಟ್ಟು->buf[0] = av_ಬಫರ್_pool_get(ctx->pool);
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0])
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಆದರೆ (ctx->format == AV_PIX_FMT_CUARRAY) {
#ಆದರೆ HAVE_FFNVCODEC_CUARRAY
        AVCUDAArray_ಚೌಕಟ್ಟು_Descriptor *desc = (AVCUDAArray_ಚೌಕಟ್ಟು_Descriptor*)ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ;
        ಆದರೆ (!desc) {
            ಚೌಕಟ್ಟು->format = ctx->format;
            ಚೌಕಟ್ಟು->ಅಗಲ  = ctx->ಅಗಲ;
            ಚೌಕಟ್ಟು->ಎತ್ತರ = ctx->ಎತ್ತರ;
            ಹಿಂತಿರುಗಿ 0;
        }
        ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] = (uint8_t*)desc->array;
        ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[1] = (uint8_t*)desc->ಸೂಚ್ಯಂಕ;

        res = CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));
        ಆದರೆ (res < 0)
            ಹಿಂತಿರುಗಿ res;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(ಚೌಕಟ್ಟು->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            ಆದರೆ (arr_plane_res == CUDA_ERROR_INVALID_ಮೌಲ್ಯ) {
                ಆದರೆ (i > 0)
                    ನಿಲ್ಲಿಸು;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                ಆದರೆ (res < 0)
                    ಹೋಗು fail;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                ಹೋಗು fail;
            } ಇಲ್ಲದಿದ್ದರೆ {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                ಆದರೆ (res < 0)
                    ಹೋಗು fail;
            }

            ಪೂರ್ಣಾಂಕ elem_ಗಾತ್ರ = ff_cuda_cuarray_elem_ಗಾತ್ರ(plane_desc.Format);
            ಆದರೆ (elem_ಗಾತ್ರ <= 0) {
                res = AVERROR_BUG;
                ಹೋಗು fail;
            }

            ಚೌಕಟ್ಟು->linesize[i] = plane_desc.ಅಗಲ_2 * plane_desc.ಅಂಕೆ_Channels * elem_ಗಾತ್ರ;

            ಆದರೆ (arr_plane_res == CUDA_ERROR_INVALID_ಮೌಲ್ಯ)
                ನಿಲ್ಲಿಸು;
        }

        res = CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
        ಆದರೆ (res < 0)
            ಹಿಂತಿರುಗಿ res;
#ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
#ಆದರೆ_ಅಂತ್ಯ
    } ಇಲ್ಲದಿದ್ದರೆ {
        res = av_image_fill_arrays(ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ, ಚೌಕಟ್ಟು->linesize, ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ,
                                   ctx->sw_format, ctx->ಅಗಲ, ctx->ಎತ್ತರ, priv->tex_alignment);
        ಆದರೆ (res < 0)
            ಹಿಂತಿರುಗಿ res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        ಆದರೆ (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            ಚೌಕಟ್ಟು->linesize[1] = ಚೌಕಟ್ಟು->linesize[2] = ಚೌಕಟ್ಟು->linesize[0] / 2;
            ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[2]     = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[1];
            ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[1]     = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[2] + ಚೌಕಟ್ಟು->linesize[2] * AV_CEIL_RSHIFT(ctx->ಎತ್ತರ, 1);
        }
    }

    ಚೌಕಟ್ಟು->format = ctx->format;
    ಚೌಕಟ್ಟು->ಅಗಲ  = ctx->ಅಗಲ;
    ಚೌಕಟ್ಟು->ಎತ್ತರ = ctx->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;

#ಆದರೆ HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
    ಹಿಂತಿರುಗಿ res;
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಎಣಿಕೆ AVPixelFormat cuda_ಚೌಕಟ್ಟು_hw_format(ಸ್ಥಿರಾಂಕ AVFrame *ಚೌಕಟ್ಟು)
{
    ಆದರೆ (!ಚೌಕಟ್ಟು->hw_ಚೌಕಟ್ಟುಗಳು_ctx)
        ಹಿಂತಿರುಗಿ AV_PIX_FMT_NONE;
    ಹಿಂತಿರುಗಿ ((AVHWFramesContext *)ಚೌಕಟ್ಟು->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ)->format;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                     ಎಣಿಕೆ AVPixelFormat **formats)
{
    ಎಣಿಕೆ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ಗಾತ್ರ(*fmts));
    ಆದರೆ (!fmts)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cuda_transfer_ದತ್ತಾಂಶ(AVHWFramesContext *ctx, AVFrame *dst,
                                 ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->ಆಂತರಿಕ->cuda_dl;

    ಸ್ಥಿರಾಂಕ AVFrame *sw_ಚೌಕಟ್ಟು = src->hw_ಚೌಕಟ್ಟುಗಳು_ctx ? dst : src;
    AVFrame *ತುದಿ_ಕೆಳಕ್ಕೆ = ಖಾಲಿ, *bottom_ಮೇಲೆ_dst = ಖಾಲಿ;
    CUcontext dummy;
    ಪೂರ್ಣಾಂಕ i, ret, copy_queued = 0, bottom_ಮೇಲೆ = 0;

    {
        ಎಣಿಕೆ AVPixelFormat src_fmt = cuda_ಚೌಕಟ್ಟು_hw_format(src);
        ಎಣಿಕೆ AVPixelFormat dst_fmt = cuda_ಚೌಕಟ್ಟು_hw_format(dst);
        ಆದರೆ ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(sw_ಚೌಕಟ್ಟು->linesize); i++)
        bottom_ಮೇಲೆ |= sw_ಚೌಕಟ್ಟು->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    ಆದರೆ (bottom_ಮೇಲೆ) {
        ತುದಿ_ಕೆಳಕ್ಕೆ = av_ಚೌಕಟ್ಟು_alloc();
        ಆದರೆ (!ತುದಿ_ಕೆಳಕ್ಕೆ)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        ತುದಿ_ಕೆಳಕ್ಕೆ->format = ctx->sw_format;
        ತುದಿ_ಕೆಳಕ್ಕೆ->ಅಗಲ  = ctx->ಅಗಲ;
        ತುದಿ_ಕೆಳಕ್ಕೆ->ಎತ್ತರ = ctx->ಎತ್ತರ;
        ret = av_hwframe_get_transfer_ಬಫರ್((src->hw_ಚೌಕಟ್ಟುಗಳು_ctx ? src : dst)->hw_ಚೌಕಟ್ಟುಗಳು_ctx,
                                             ತುದಿ_ಕೆಳಕ್ಕೆ);
        ಆದರೆ (ret < 0)
            ಹೋಗು free_ತುದಿ_ಕೆಳಕ್ಕೆ;
        ತುದಿ_ಕೆಳಕ್ಕೆ->ಅಗಲ  = src->ಅಗಲ;
        ತುದಿ_ಕೆಳಕ್ಕೆ->ಎತ್ತರ = src->ಎತ್ತರ;
        ಆದರೆ (sw_ಚೌಕಟ್ಟು == src) {
            av_image_copy2(ತುದಿ_ಕೆಳಕ್ಕೆ->ದತ್ತಾಂಶ, ತುದಿ_ಕೆಳಕ್ಕೆ->linesize, src->ದತ್ತಾಂಶ, src->linesize,
                           ctx->sw_format, src->ಅಗಲ, src->ಎತ್ತರ);
            src = ತುದಿ_ಕೆಳಕ್ಕೆ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            bottom_ಮೇಲೆ_dst = dst;
            dst           = ತುದಿ_ಕೆಳಕ್ಕೆ;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx));
    ಆದರೆ (ret < 0)
        ಹೋಗು free_ತುದಿ_ಕೆಳಕ್ಕೆ;

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
    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(src->ದತ್ತಾಂಶ) && src->linesize[i]; i++) {
        ಪೂರ್ಣಾಂಕ src_is_nonplanar_cuarray = 0;
        ಪೂರ್ಣಾಂಕ dst_is_nonplanar_cuarray = 0;

        ಪೂರ್ಣಾಂಕ bytewidth = av_image_get_linesize(ctx->sw_format, src->ಅಗಲ, i);
        ಆದರೆ (bytewidth < 0) {
            ret = bytewidth;
            ಹೋಗು fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .ಅಗಲ_ಒಳ_ಬೈಟುಗಳು  = bytewidth,
            .ಎತ್ತರ_2        = AV_CEIL_RSHIFT(src->ಎತ್ತರ, ((i == 0 || i == 3) ? 0 : priv->ಸರಿಸು_ಎತ್ತರ)),
        };

        ಆದರೆ (src->format == AV_PIX_FMT_CUDA) {
            cpy.src_ಸ್ಮರಣೆ_Type = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->ದತ್ತಾಂಶ[i];
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (src->format == AV_PIX_FMT_CUARRAY) {
#ಆದರೆ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->ದತ್ತಾಂಶ[0], i);
            ಆದರೆ (cures == CUDA_ERROR_INVALID_ಮೌಲ್ಯ && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->ದತ್ತಾಂಶ[0];
                src_is_nonplanar_cuarray = 1;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                ಹೋಗು fail;
            }

            cpy.src_ಸ್ಮರಣೆ_Type = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#ಇಲ್ಲದಿದ್ದರೆ
            ret = AVERROR(ENOSYS);
            ಹೋಗು ನಿರ್ಗಮಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
        } ಇಲ್ಲದಿದ್ದರೆ {
            cpy.src_ಸ್ಮರಣೆ_Type = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->ದತ್ತಾಂಶ[i];
        }

        ಆದರೆ (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dst_ಸ್ಮರಣೆ_Type = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->ದತ್ತಾಂಶ[i];
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dst->format == AV_PIX_FMT_CUARRAY) {
#ಆದರೆ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->ದತ್ತಾಂಶ[0], i);
            ಆದರೆ (cures == CUDA_ERROR_INVALID_ಮೌಲ್ಯ && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->ದತ್ತಾಂಶ[0];
                dst_is_nonplanar_cuarray = 1;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                ಹೋಗು fail;
            }

            cpy.dst_ಸ್ಮರಣೆ_Type = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#ಇಲ್ಲದಿದ್ದರೆ
            ret = AVERROR(ENOSYS);
            ಹೋಗು ನಿರ್ಗಮಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
        } ಇಲ್ಲದಿದ್ದರೆ {
            cpy.dst_ಸ್ಮರಣೆ_Type = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->ದತ್ತಾಂಶ[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->ಹರಿವು));
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;
        copy_queued = 1;

        ಆದರೆ (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            ನಿಲ್ಲಿಸು;
    }

    /* The caller may reuse host memory once the transfer returns. */
    ಆದರೆ (!src->hw_ಚೌಕಟ್ಟುಗಳು_ctx || !dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx) {
        ret = CHECK_CU(cu->cu_ಹರಿವು_Synchronize(hwctx->ಹರಿವು));
        ಆದರೆ (ret < 0)
            ಹೋಗು ನಿರ್ಗಮಿಸು;
    }

fail:
    ಆದರೆ (ret < 0 && copy_queued)
        CHECK_CU(cu->cu_ಹರಿವು_Synchronize(hwctx->ಹರಿವು));
ನಿರ್ಗಮಿಸು:
    CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));

    ಆದರೆ (bottom_ಮೇಲೆ_dst && ret >= 0)
        av_image_copy2(bottom_ಮೇಲೆ_dst->ದತ್ತಾಂಶ, bottom_ಮೇಲೆ_dst->linesize,
                       ತುದಿ_ಕೆಳಕ್ಕೆ->ದತ್ತಾಂಶ, ತುದಿ_ಕೆಳಕ್ಕೆ->linesize,
                       ctx->sw_format, src->ಅಗಲ, src->ಎತ್ತರ);
free_ತುದಿ_ಕೆಳಕ್ಕೆ:
    av_ಚೌಕಟ್ಟು_free(&ತುದಿ_ಕೆಳಕ್ಕೆ);

    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಶೂನ್ಯ cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    ಆದರೆ (hwctx->p.ಆಂತರಿಕ) {
        CudaFunctions *cu = hwctx->ಆಂತರಿಕ.cuda_dl;

        ಆದರೆ (hwctx->ಆಂತರಿಕ.is_allocated && hwctx->p.cuda_ctx) {
            ಆದರೆ (hwctx->ಆಂತರಿಕ.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->ಆಂತರಿಕ.cuda_device));
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(hwctx->ಆಂತರಿಕ.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = ಖಾಲಿ;
        }

        cuda_free_functions(&hwctx->ಆಂತರಿಕ.cuda_dl);
        memset(&hwctx->ಆಂತರಿಕ, 0, ಗಾತ್ರ(hwctx->ಆಂತರಿಕ));
        hwctx->p.ಆಂತರಿಕ = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    ಪೂರ್ಣಾಂಕ ret;

    hwctx->p.ಆಂತರಿಕ = &hwctx->ಆಂತರಿಕ;

    ಆದರೆ (!hwctx->ಆಂತರಿಕ.cuda_dl) {
        ret = cuda_ತುಂಬು_functions(&hwctx->ಆಂತರಿಕ.cuda_dl, ctx);
        ಆದರೆ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            ಹೋಗು error;
        }
    }

    ಹಿಂತಿರುಗಿ 0;

error:
    cuda_device_uninit(ctx);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cuda_context_init(AVHWDeviceContext *device_ctx, ಪೂರ್ಣಾಂಕ flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    ಪೂರ್ಣಾಂಕ ret, dev_ಸಕ್ರಿಯ = 0;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ dev_flags = 0;

    ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->ಆಂತರಿಕ->cuda_dl;

    hwctx->ಆಂತರಿಕ->flags = flags;

    ಆದರೆ (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->ಆಂತರಿಕ->cuda_device,
                       &dev_flags, &dev_ಸಕ್ರಿಯ));
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;

        ಆದರೆ (dev_ಸಕ್ರಿಯ && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            ಹಿಂತಿರುಗಿ AVERROR(ENOTSUP);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cu_Device_Primary_Ctx_ಗಣ_Flags(hwctx->ಆಂತರಿಕ->cuda_device,
                           desired_flags));
            ಆದರೆ (ret < 0)
                ಹಿಂತಿರುಗಿ ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->ಆಂತರಿಕ->cuda_device));
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } ಇಲ್ಲದಿದ್ದರೆ {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->ಆಂತರಿಕ->cuda_device));
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;

        CHECK_CU(cu->cu_Ctx_ತೆಗೆ_Current(&dummy));
    }

    hwctx->ಆಂತರಿಕ->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->ಹರಿವು = ಖಾಲಿ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, ಪೂರ್ಣಾಂಕ *flags)
{
    AVDictionary_ನಮೂದು *primary_ctx_opt = av_dict_get(opts, "primary_ctx", ಖಾಲಿ, 0);
    AVDictionary_ನಮೂದು *current_ctx_opt = av_dict_get(opts, "current_ctx", ಖಾಲಿ, 0);

    ಪೂರ್ಣಾಂಕ use_primary_ctx = 0, use_current_ctx = 0;
    ಆದರೆ (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->ಮೌಲ್ಯ, ಖಾಲಿ, 10);

    ಆದರೆ (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->ಮೌಲ್ಯ, ಖಾಲಿ, 10);

    ಆದರೆ (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ಆದರೆ (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    ಆದರೆ (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cuda_device_create(AVHWDeviceContext *device_ctx,
                              ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                              AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ಪೂರ್ಣಾಂಕ ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    ಆದರೆ (ret < 0)
        ಹೋಗು error;

    ಆದರೆ (device)
        device_idx = strtol(device, ಖಾಲಿ, 0);

    ret = cuda_device_init(device_ctx);
    ಆದರೆ (ret < 0)
        ಹೋಗು error;

    cu = hwctx->ಆಂತರಿಕ->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    ಆದರೆ (ret < 0)
        ಹೋಗು error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->ಆಂತರಿಕ->cuda_device, device_idx));
    ಆದರೆ (ret < 0)
        ಹೋಗು error;

    ret = cuda_context_init(device_ctx, flags);
    ಆದರೆ (ret < 0)
        ಹೋಗು error;

    ಹಿಂತಿರುಗಿ 0;

error:
    cuda_device_uninit(device_ctx);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              ಪೂರ್ಣಾಂಕ flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src_uuid = ಖಾಲಿ;
#ಆದರೆ CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ಣಾಂಕ ret, i, device_ಎಣಿಕೆ;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    ಆದರೆ (ret < 0)
        ಹೋಗು error;

#ಆದರೆ CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#ಆದರೆ_ಅಂತ್ಯ

    ಆಯ್ಕೆ (src_ctx->type) {
#ಆದರೆ CONFIG_VULKAN
#ವ್ಯಾಖ್ಯಾನಿಸು TYPE PFN_vkGetPhysicalDeviceProperties2
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .p_ಮುಂದಿನ = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        ನಿಲ್ಲಿಸು;
    }
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು TYPE
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ret = AVERROR(ENOSYS);
        ಹೋಗು error;
    }

    ಆದರೆ (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        ಹೋಗು error;
    }

    ret = cuda_device_init(device_ctx);
    ಆದರೆ (ret < 0)
        ಹೋಗು error;

    cu = hwctx->ಆಂತರಿಕ->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    ಆದರೆ (ret < 0)
        ಹೋಗು error;

    ret = CHECK_CU(cu->cu_Device_Get_ಎಣಿಕೆ(&device_ಎಣಿಕೆ));
    ಆದರೆ (ret < 0)
        ಹೋಗು error;

    hwctx->ಆಂತರಿಕ->cuda_device = -1;
    ಗಾಗಿ (i = 0; i < device_ಎಣಿಕೆ; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        ಆದರೆ (ret < 0)
            ಹೋಗು error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        ಆದರೆ (ret < 0)
            ಹೋಗು error;

        ಆದರೆ (memcmp(src_uuid, uuid.ಬೈಟುಗಳು, ಗಾತ್ರ (uuid.ಬೈಟುಗಳು)) == 0) {
            hwctx->ಆಂತರಿಕ->cuda_device = dev;
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (hwctx->ಆಂತರಿಕ->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        ಹೋಗು error;
    }

    ret = cuda_context_init(device_ctx, flags);
    ಆದರೆ (ret < 0)
        ಹೋಗು error;

    ಹಿಂತಿರುಗಿ 0;

error:
    cuda_device_uninit(device_ctx);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_ಗಾತ್ರ    = ಗಾತ್ರ(CUDADeviceContext),
    .ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ    = ಗಾತ್ರ(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .ಚೌಕಟ್ಟುಗಳು_get_constraints = cuda_ಚೌಕಟ್ಟುಗಳು_get_constraints,
    .ಚೌಕಟ್ಟುಗಳು_init          = cuda_ಚೌಕಟ್ಟುಗಳು_init,
    .ಚೌಕಟ್ಟುಗಳು_uninit        = cuda_ಚೌಕಟ್ಟುಗಳು_uninit,
    .ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್    = cuda_get_ಬಫರ್,
    .transfer_get_formats = cuda_transfer_get_formats,
#ಆದರೆ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_ಬಫರ್_alloc = cuda_transfer_ಬಫರ್_alloc,
#ಆದರೆ_ಅಂತ್ಯ
    .transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ     = cuda_transfer_ದತ್ತಾಂಶ,
    .transfer_ದತ್ತಾಂಶ_from   = cuda_transfer_ದತ್ತಾಂಶ,

    .pix_fmts             = (ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#ಆದರೆ HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#ಆದರೆ_ಅಂತ್ಯ
                                                          AV_PIX_FMT_NONE },
};
