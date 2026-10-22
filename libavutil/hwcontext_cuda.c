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

#ਅਨ੍ਤਰ੍ਭਾਵ "buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_cuda_internal.h"
#ਜੇ CONFIG_VULKAN
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_vulkan.h"
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "cuda_check.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "imgutils.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ CUDAFramesContext {
    AVCUDAFramesContext p;

    ਪੂਰਨ ਖਿਸਕਾਓ_ਚੌੜਾਈ, ਖਿਸਕਾਓ_ਉਚਾਈ;
    ਪੂਰਨ tex_alignment;

    ਪੂਰਨ cuarray_ਅੰਕ_surfaces_ਵਰਤਿਆ;
} CUDAFramesContext;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADevice_Context_ਅੰਦਰੂਨੀ ਅੰਦਰੂਨੀ;
} CUDADeviceContext;



#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

ਸਥਿਰ CUarray_format cuda_array_format_for_pix_fmt(ਗਿਣਤੀ AVPixelFormat fmt);

ਸਥਿਰ ਪੂਰਨ cuda_ਚੌਖਟੇ_get_constraints(AVHWDeviceContext *ctx,
                                       ਅਚਲ ਖਾਲੀ *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ਅਚਲ AVCUDAHWConfig *config = hwconfig;
    ਗਿਣਤੀ AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    ਪੂਰਨ n = 0;

    ਜੇ (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, ਆਕਾਰ(*constraints->valid_hw_formats));
        ਜੇ (!constraints->valid_hw_formats)
            ਵਾਪਸ AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } ਨਹੀਂਤਾਂ {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, ਆਕਾਰ(*constraints->valid_hw_formats));
        ਜੇ (!constraints->valid_hw_formats)
            ਵਾਪਸ AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#ਜੇ HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#ਨਹੀਂਤਾਂ
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#ਜੇ_ਅੰਤ
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    ਆਕਾਰ(*constraints->valid_sw_formats));
    ਜੇ (!constraints->valid_sw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    n = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < AV_PIX_FMT_NB; i++) {
        ਜੇ (req_fmt == AV_PIX_FMT_CUARRAY) {
            ਜੇ (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } ਨਹੀਂਤਾਂ {
            ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            ਜੇ (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#ਜੇ CONFIG_VULKAN
    ਜੇ (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#ਜੇ_ਅੰਤ
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ cuda_ਬਫਰ_free(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->ਅੰਦਰੂਨੀ->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ਧੱਕੋ_Current(hwctx->cuda_ctx));

    ਜੇ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArray_ਚੌਖਟਾ_Descriptor *desc = (AVCUDAArray_ਚੌਖਟਾ_Descriptor*)ਅੰਕੜੇ;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } ਨਹੀਂਤਾਂ {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)ਅੰਕੜੇ));
    }

    CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));
}

ਸਥਿਰ AVBufferRef *cuda_pool_alloc(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->ਅੰਦਰੂਨੀ->cuda_dl;

    AVBufferRef *ret = ਨਿਰਾ;
    CUcontext dummy = ਨਿਰਾ;
    CUdeviceptr ਅੰਕੜੇ;
    ਪੂਰਨ err;

    err = CHECK_CU(cu->cu_Ctx_ਧੱਕੋ_Current(hwctx->cuda_ctx));
    ਜੇ (err < 0)
        ਵਾਪਸ ਨਿਰਾ;

    ਜੇ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArray_ਚੌਖਟਾ_Descriptor *desc = av_mallocz(ਆਕਾਰ(*desc));
        ਜੇ (!desc)
            ਜਾਓ ਪੂਰਾ;

        ਜੇ (priv->p.cuarray_ਅੰਕ_surfaces > 0) {
            ਜੇ (priv->cuarray_ਅੰਕ_surfaces_ਵਰਤਿਆ >= priv->p.cuarray_ਅੰਕ_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                ਜਾਓ ਪੂਰਾ;
            }
            desc->ਸੂਚਕਾਂਕ = priv->cuarray_ਅੰਕ_surfaces_ਵਰਤਿਆ++;
            desc->array = priv->p.cuarray_surfaces[desc->ਸੂਚਕਾਂਕ];
        } ਨਹੀਂਤਾਂ {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            ਜੇ (err < 0) {
                av_free(desc);
                ਜਾਓ ਪੂਰਾ;
            }
        }

        ret = av_ਬਫਰ_create((uint8_t*)desc, ਆਕਾਰ(*desc), cuda_ਬਫਰ_free, ctx, 0);
        ਜੇ (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            ਜਾਓ ਪੂਰਾ;
        }

        ਜਾਓ ਪੂਰਾ;
    }

    err = CHECK_CU(cu->cuMemAlloc(&ਅੰਕੜੇ, ਮਾਪ));
    ਜੇ (err < 0)
        ਜਾਓ ਪੂਰਾ;

    ret = av_ਬਫਰ_create((uint8_t*)ਅੰਕੜੇ, ਮਾਪ, cuda_ਬਫਰ_free, ctx, 0);
    ਜੇ (!ret) {
        CHECK_CU(cu->cuMemFree(ਅੰਕੜੇ));
        ਜਾਓ ਪੂਰਾ;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
ਪੂਰਾ:
    CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));
    ਵਾਪਸ ret;
}

#ਜੇ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
ਸਥਿਰ ਖਾਲੀ cuda_transfer_ਬਫਰ_free(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->ਅੰਦਰੂਨੀ->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ਧੱਕੋ_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(ਅੰਕੜੇ));
    CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
ਸਥਿਰ AVBufferRef *cuda_transfer_ਬਫਰ_alloc(ਖਾਲੀ *device_ref, size_t ਮਾਪ)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->ਅੰਕੜੇ;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->ਅੰਦਰੂਨੀ->cuda_dl;
    AVBufferRef *ret = ਨਿਰਾ;
    CUcontext dummy;
    ਖਾਲੀ *host;

    ਜੇ (CHECK_CU(cu->cu_Ctx_ਧੱਕੋ_Current(hwctx->cuda_ctx)) < 0)
        ਵਾਪਸ av_ਬਫਰ_alloc(ਮਾਪ);

    ਜੇ (CHECK_CU(cu->cuMemHostAlloc(&host, ਮਾਪ, 0)) >= 0) {
        ret = av_ਬਫਰ_create(host, ਮਾਪ, cuda_transfer_ਬਫਰ_free, device_ctx, 0);
        ਜੇ (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));
    ਵਾਪਸ ret ? ret : av_ਬਫਰ_alloc(ਮਾਪ);
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ cuda_ਚੌਖਟੇ_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->ਅੰਦਰੂਨੀ->cuda_dl;

    ਜੇ (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_ਧੱਕੋ_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        ਲਈ (ਪੂਰਨ i = priv->cuarray_ਅੰਕ_surfaces_ਵਰਤਿਆ; i < priv->p.cuarray_ਅੰਕ_surfaces; i++)
            ਜੇ (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_ਅੰਕ_surfaces = 0;
    }
}

ਸਥਿਰ CUarray_format cuda_array_format_for_pix_fmt(ਗਿਣਤੀ AVPixelFormat fmt)
{
    ਚੋਣ (fmt) {
#ਜੇ HAVE_FFNVCODEC_CUARRAY
    ਹਾਲਤ AV_PIX_FMT_NV12:      ਵਾਪਸ CU_AD_FORMAT_NV12;
    ਹਾਲਤ AV_PIX_FMT_P010:
    ਹਾਲਤ AV_PIX_FMT_P012:
    ਹਾਲਤ AV_PIX_FMT_P016:      ਵਾਪਸ CU_AD_FORMAT_P016;
    ਹਾਲਤ AV_PIX_FMT_NV16:      ਵਾਪਸ CU_AD_FORMAT_NV16;
    ਹਾਲਤ AV_PIX_FMT_P210:
    ਹਾਲਤ AV_PIX_FMT_P212:
    ਹਾਲਤ AV_PIX_FMT_P216:      ਵਾਪਸ CU_AD_FORMAT_P216;
    ਹਾਲਤ AV_PIX_FMT_NV24:      ਵਾਪਸ CU_AD_FORMAT_YUV444_8_ਦੋਆਧਾਰੀ_ਅੰਕ_SEMIPLANAR;
    ਹਾਲਤ AV_PIX_FMT_P410:
    ਹਾਲਤ AV_PIX_FMT_P412:
    ਹਾਲਤ AV_PIX_FMT_P416:      ਵਾਪਸ CU_AD_FORMAT_YUV444_16_ਦੋਆਧਾਰੀ_ਅੰਕ_SEMIPLANAR;
    ਹਾਲਤ AV_PIX_FMT_YUV420P:   ਵਾਪਸ CU_AD_FORMAT_UINT8_PLANAR_420;
    ਹਾਲਤ AV_PIX_FMT_YUV422P:   ਵਾਪਸ CU_AD_FORMAT_UINT8_PLANAR_422;
    ਹਾਲਤ AV_PIX_FMT_YUV444P:   ਵਾਪਸ CU_AD_FORMAT_UINT8_PLANAR_444;
    ਹਾਲਤ AV_PIX_FMT_YUV420P10: ਵਾਪਸ CU_AD_FORMAT_UINT16_PLANAR_420;
    ਹਾਲਤ AV_PIX_FMT_YUV422P10: ਵਾਪਸ CU_AD_FORMAT_UINT16_PLANAR_422;
    ਹਾਲਤ AV_PIX_FMT_YUV444P10:
    ਹਾਲਤ AV_PIX_FMT_YUV444P10MSB:
    ਹਾਲਤ AV_PIX_FMT_YUV444P12MSB:
    ਹਾਲਤ AV_PIX_FMT_YUV444P16: ਵਾਪਸ CU_AD_FORMAT_UINT16_PLANAR_444;
    ਹਾਲਤ AV_PIX_FMT_0RGB32:
    ਹਾਲਤ AV_PIX_FMT_0BGR32:
    ਹਾਲਤ AV_PIX_FMT_RGB32:
    ਹਾਲਤ AV_PIX_FMT_BGR32:     ਵਾਪਸ CU_AD_FORMAT_UNSIGNED_INT8;
#ਜੇ_ਅੰਤ
    ਮੂਲ:                   ਵਾਪਸ 0;
    }
}

#ਜੇ HAVE_FFNVCODEC_CUARRAY
ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ cuda_array_numchannels_for_pix_fmt(ਗਿਣਤੀ AVPixelFormat fmt)
{
    ਚੋਣ (fmt) {
    ਹਾਲਤ AV_PIX_FMT_0RGB32:
    ਹਾਲਤ AV_PIX_FMT_0BGR32:
    ਹਾਲਤ AV_PIX_FMT_RGB32:
    ਹਾਲਤ AV_PIX_FMT_BGR32:     ਵਾਪਸ 4;
    ਮੂਲ:                   ਵਾਪਸ 3;
    }
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ cuda_ਚੌਖਟੇ_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->ਅੰਦਰੂਨੀ->cuda_dl;
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    ਪੂਰਨ err;

    ਜੇ (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        ਵਾਪਸ AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    ਜੇ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        ਵਾਪਸ AVERROR(ENOSYS);
    }

#ਜੇ HAVE_FFNVCODEC_CUARRAY
    ਜੇ (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        ਵਾਪਸ AVERROR(ENOSYS);
    }
#ਨਹੀਂਤਾਂ
    ਜੇ (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        ਵਾਪਸ AVERROR(ENOSYS);
    }
#ਜੇ_ਅੰਤ

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->ਅੰਦਰੂਨੀ->cuda_device));
    ਜੇ (err < 0)
        ਵਾਪਸ err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    ਜੇ (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->ਖਿਸਕਾਓ_ਚੌੜਾਈ, &priv->ਖਿਸਕਾਓ_ਉਚਾਈ);

#ਜੇ HAVE_FFNVCODEC_CUARRAY
    ਜੇ (ctx->format == AV_PIX_FMT_CUARRAY) {
        ਜੇ (!priv->p.cuarray_desc.ਚੌੜਾਈ_2)
            priv->p.cuarray_desc.ਚੌੜਾਈ_2 = ctx->ਚੌੜਾਈ;
        ਜੇ (!priv->p.cuarray_desc.ਉਚਾਈ_2)
            priv->p.cuarray_desc.ਉਚਾਈ_2 = ctx->ਉਚਾਈ;
        ਜੇ (!priv->p.cuarray_desc.ਅੰਕ_Channels)
            priv->p.cuarray_desc.ਅੰਕ_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        ਜੇ (priv->p.cuarray_desc.ਡੂੰਘਾਈ_2) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            ਵਾਪਸ AVERROR(EINVAL);
        }

        ਜੇ (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        ਜੇ (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            ਵਾਪਸ AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    ਜੇ (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_ਅੰਕ_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_ਅੰਕ_surfaces, ਆਕਾਰ(*priv->p.cuarray_surfaces));
        ਜੇ (!priv->p.cuarray_surfaces)
            ਵਾਪਸ AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_ਧੱਕੋ_Current(hwctx->cuda_ctx));
        ਜੇ (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            ਵਾਪਸ err;
        }

        ਲਈ (ਪੂਰਨ i = 0; i < priv->p.cuarray_ਅੰਕ_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            ਜੇ (err < 0) {
                ਲਈ (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                ਵਾਪਸ err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));
        ਜੇ (err < 0)
            ਜਾਓ fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_ਅੰਕ_surfaces, priv->p.cuarray_desc.ਚੌੜਾਈ_2, priv->p.cuarray_desc.ਉਚਾਈ_2);
    }
#ਜੇ_ਅੰਤ

    ਜੇ (!ctx->pool) {
        ਪੂਰਨ ਮਾਪ = av_image_get_ਬਫਰ_ਮਾਪ(ctx->sw_format, ctx->ਚੌੜਾਈ, ctx->ਉਚਾਈ, priv->tex_alignment);
        ਜੇ (ਮਾਪ < 0) {
            err = ਮਾਪ;
            ਜਾਓ fail;
        }

        ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ =
            av_ਬਫਰ_pool_init2(ਮਾਪ, ctx, cuda_pool_alloc, ਨਿਰਾ);
        ਜੇ (!ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ) {
            err = AVERROR(ENOMEM);
            ਜਾਓ fail;
        }
    }

    ਵਾਪਸ 0;

fail:
    cuda_ਚੌਖਟੇ_uninit(ctx);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ cuda_get_ਬਫਰ(AVHWFramesContext *ctx, AVFrame *ਚੌਖਟਾ)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#ਜੇ HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->ਅੰਦਰੂਨੀ->cuda_dl;

    CUcontext dummy;
#ਜੇ_ਅੰਤ
    ਪੂਰਨ res;

    ਚੌਖਟਾ->buf[0] = av_ਬਫਰ_pool_get(ctx->pool);
    ਜੇ (!ਚੌਖਟਾ->buf[0])
        ਵਾਪਸ AVERROR(ENOMEM);

    ਜੇ (ctx->format == AV_PIX_FMT_CUARRAY) {
#ਜੇ HAVE_FFNVCODEC_CUARRAY
        AVCUDAArray_ਚੌਖਟਾ_Descriptor *desc = (AVCUDAArray_ਚੌਖਟਾ_Descriptor*)ਚੌਖਟਾ->buf[0]->ਅੰਕੜੇ;
        ਜੇ (!desc) {
            ਚੌਖਟਾ->format = ctx->format;
            ਚੌਖਟਾ->ਚੌੜਾਈ  = ctx->ਚੌੜਾਈ;
            ਚੌਖਟਾ->ਉਚਾਈ = ctx->ਉਚਾਈ;
            ਵਾਪਸ 0;
        }
        ਚੌਖਟਾ->ਅੰਕੜੇ[0] = (uint8_t*)desc->array;
        ਚੌਖਟਾ->ਅੰਕੜੇ[1] = (uint8_t*)desc->ਸੂਚਕਾਂਕ;

        res = CHECK_CU(cu->cu_Ctx_ਧੱਕੋ_Current(hwctx->cuda_ctx));
        ਜੇ (res < 0)
            ਵਾਪਸ res;

        ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(ਚੌਖਟਾ->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            ਜੇ (arr_plane_res == CUDA_ERROR_INVALID_ਮੁੱਲ) {
                ਜੇ (i > 0)
                    ਰੋਕੋ;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                ਜੇ (res < 0)
                    ਜਾਓ fail;
            } ਨਹੀਂਤਾਂ ਜੇ (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                ਜਾਓ fail;
            } ਨਹੀਂਤਾਂ {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                ਜੇ (res < 0)
                    ਜਾਓ fail;
            }

            ਪੂਰਨ elem_ਮਾਪ = ff_cuda_cuarray_elem_ਮਾਪ(plane_desc.Format);
            ਜੇ (elem_ਮਾਪ <= 0) {
                res = AVERROR_BUG;
                ਜਾਓ fail;
            }

            ਚੌਖਟਾ->linesize[i] = plane_desc.ਚੌੜਾਈ_2 * plane_desc.ਅੰਕ_Channels * elem_ਮਾਪ;

            ਜੇ (arr_plane_res == CUDA_ERROR_INVALID_ਮੁੱਲ)
                ਰੋਕੋ;
        }

        res = CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));
        ਜੇ (res < 0)
            ਵਾਪਸ res;
#ਨਹੀਂਤਾਂ
        ਵਾਪਸ AVERROR(ENOSYS);
#ਜੇ_ਅੰਤ
    } ਨਹੀਂਤਾਂ {
        res = av_image_fill_arrays(ਚੌਖਟਾ->ਅੰਕੜੇ, ਚੌਖਟਾ->linesize, ਚੌਖਟਾ->buf[0]->ਅੰਕੜੇ,
                                   ctx->sw_format, ctx->ਚੌੜਾਈ, ctx->ਉਚਾਈ, priv->tex_alignment);
        ਜੇ (res < 0)
            ਵਾਪਸ res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        ਜੇ (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            ਚੌਖਟਾ->linesize[1] = ਚੌਖਟਾ->linesize[2] = ਚੌਖਟਾ->linesize[0] / 2;
            ਚੌਖਟਾ->ਅੰਕੜੇ[2]     = ਚੌਖਟਾ->ਅੰਕੜੇ[1];
            ਚੌਖਟਾ->ਅੰਕੜੇ[1]     = ਚੌਖਟਾ->ਅੰਕੜੇ[2] + ਚੌਖਟਾ->linesize[2] * AV_CEIL_RSHIFT(ctx->ਉਚਾਈ, 1);
        }
    }

    ਚੌਖਟਾ->format = ctx->format;
    ਚੌਖਟਾ->ਚੌੜਾਈ  = ctx->ਚੌੜਾਈ;
    ਚੌਖਟਾ->ਉਚਾਈ = ctx->ਉਚਾਈ;

    ਵਾਪਸ 0;

#ਜੇ HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));
    ਵਾਪਸ res;
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ ਗਿਣਤੀ AVPixelFormat cuda_ਚੌਖਟਾ_hw_format(ਅਚਲ AVFrame *ਚੌਖਟਾ)
{
    ਜੇ (!ਚੌਖਟਾ->hw_ਚੌਖਟੇ_ctx)
        ਵਾਪਸ AV_PIX_FMT_NONE;
    ਵਾਪਸ ((AVHWFramesContext *)ਚੌਖਟਾ->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ)->format;
}

ਸਥਿਰ ਪੂਰਨ cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     ਗਿਣਤੀ AVHWFrameTransferDirection dir,
                                     ਗਿਣਤੀ AVPixelFormat **formats)
{
    ਗਿਣਤੀ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ਆਕਾਰ(*fmts));
    ਜੇ (!fmts)
        ਵਾਪਸ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ cuda_transfer_ਅੰਕੜੇ(AVHWFramesContext *ctx, AVFrame *dst,
                                 ਅਚਲ AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->ਅੰਦਰੂਨੀ->cuda_dl;

    ਅਚਲ AVFrame *sw_ਚੌਖਟਾ = src->hw_ਚੌਖਟੇ_ctx ? dst : src;
    AVFrame *ਸਿਖਰ_ਥੱਲੇ = ਨਿਰਾ, *bottom_ਉੱਪਰ_dst = ਨਿਰਾ;
    CUcontext dummy;
    ਪੂਰਨ i, ret, copy_queued = 0, bottom_ਉੱਪਰ = 0;

    {
        ਗਿਣਤੀ AVPixelFormat src_fmt = cuda_ਚੌਖਟਾ_hw_format(src);
        ਗਿਣਤੀ AVPixelFormat dst_fmt = cuda_ਚੌਖਟਾ_hw_format(dst);
        ਜੇ ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            ਵਾਪਸ AVERROR(ENOSYS);
    }

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(sw_ਚੌਖਟਾ->linesize); i++)
        bottom_ਉੱਪਰ |= sw_ਚੌਖਟਾ->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    ਜੇ (bottom_ਉੱਪਰ) {
        ਸਿਖਰ_ਥੱਲੇ = av_ਚੌਖਟਾ_alloc();
        ਜੇ (!ਸਿਖਰ_ਥੱਲੇ)
            ਵਾਪਸ AVERROR(ENOMEM);
        ਸਿਖਰ_ਥੱਲੇ->format = ctx->sw_format;
        ਸਿਖਰ_ਥੱਲੇ->ਚੌੜਾਈ  = ctx->ਚੌੜਾਈ;
        ਸਿਖਰ_ਥੱਲੇ->ਉਚਾਈ = ctx->ਉਚਾਈ;
        ret = av_hwframe_get_transfer_ਬਫਰ((src->hw_ਚੌਖਟੇ_ctx ? src : dst)->hw_ਚੌਖਟੇ_ctx,
                                             ਸਿਖਰ_ਥੱਲੇ);
        ਜੇ (ret < 0)
            ਜਾਓ free_ਸਿਖਰ_ਥੱਲੇ;
        ਸਿਖਰ_ਥੱਲੇ->ਚੌੜਾਈ  = src->ਚੌੜਾਈ;
        ਸਿਖਰ_ਥੱਲੇ->ਉਚਾਈ = src->ਉਚਾਈ;
        ਜੇ (sw_ਚੌਖਟਾ == src) {
            av_image_copy2(ਸਿਖਰ_ਥੱਲੇ->ਅੰਕੜੇ, ਸਿਖਰ_ਥੱਲੇ->linesize, src->ਅੰਕੜੇ, src->linesize,
                           ctx->sw_format, src->ਚੌੜਾਈ, src->ਉਚਾਈ);
            src = ਸਿਖਰ_ਥੱਲੇ;
        } ਨਹੀਂਤਾਂ {
            bottom_ਉੱਪਰ_dst = dst;
            dst           = ਸਿਖਰ_ਥੱਲੇ;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_ਧੱਕੋ_Current(hwctx->cuda_ctx));
    ਜੇ (ret < 0)
        ਜਾਓ free_ਸਿਖਰ_ਥੱਲੇ;

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
    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(src->ਅੰਕੜੇ) && src->linesize[i]; i++) {
        ਪੂਰਨ src_is_nonplanar_cuarray = 0;
        ਪੂਰਨ dst_is_nonplanar_cuarray = 0;

        ਪੂਰਨ bytewidth = av_image_get_linesize(ctx->sw_format, src->ਚੌੜਾਈ, i);
        ਜੇ (bytewidth < 0) {
            ret = bytewidth;
            ਜਾਓ fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .ਚੌੜਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ  = bytewidth,
            .ਉਚਾਈ_2        = AV_CEIL_RSHIFT(src->ਉਚਾਈ, ((i == 0 || i == 3) ? 0 : priv->ਖਿਸਕਾਓ_ਉਚਾਈ)),
        };

        ਜੇ (src->format == AV_PIX_FMT_CUDA) {
            cpy.src_ਸਮ੍ਰਿਤੀ_Type = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->ਅੰਕੜੇ[i];
        } ਨਹੀਂਤਾਂ ਜੇ (src->format == AV_PIX_FMT_CUARRAY) {
#ਜੇ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->ਅੰਕੜੇ[0], i);
            ਜੇ (cures == CUDA_ERROR_INVALID_ਮੁੱਲ && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->ਅੰਕੜੇ[0];
                src_is_nonplanar_cuarray = 1;
            } ਨਹੀਂਤਾਂ ਜੇ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                ਜਾਓ fail;
            }

            cpy.src_ਸਮ੍ਰਿਤੀ_Type = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#ਨਹੀਂਤਾਂ
            ret = AVERROR(ENOSYS);
            ਜਾਓ ਬਾਹਰ_ਨਿਕਲੋ;
#ਜੇ_ਅੰਤ
        } ਨਹੀਂਤਾਂ {
            cpy.src_ਸਮ੍ਰਿਤੀ_Type = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->ਅੰਕੜੇ[i];
        }

        ਜੇ (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dst_ਸਮ੍ਰਿਤੀ_Type = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->ਅੰਕੜੇ[i];
        } ਨਹੀਂਤਾਂ ਜੇ (dst->format == AV_PIX_FMT_CUARRAY) {
#ਜੇ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->ਅੰਕੜੇ[0], i);
            ਜੇ (cures == CUDA_ERROR_INVALID_ਮੁੱਲ && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->ਅੰਕੜੇ[0];
                dst_is_nonplanar_cuarray = 1;
            } ਨਹੀਂਤਾਂ ਜੇ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                ਜਾਓ fail;
            }

            cpy.dst_ਸਮ੍ਰਿਤੀ_Type = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#ਨਹੀਂਤਾਂ
            ret = AVERROR(ENOSYS);
            ਜਾਓ ਬਾਹਰ_ਨਿਕਲੋ;
#ਜੇ_ਅੰਤ
        } ਨਹੀਂਤਾਂ {
            cpy.dst_ਸਮ੍ਰਿਤੀ_Type = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->ਅੰਕੜੇ[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->ਧਾਰਾ));
        ਜੇ (ret < 0)
            ਜਾਓ fail;
        copy_queued = 1;

        ਜੇ (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            ਰੋਕੋ;
    }

    /* The caller may reuse host memory once the transfer returns. */
    ਜੇ (!src->hw_ਚੌਖਟੇ_ctx || !dst->hw_ਚੌਖਟੇ_ctx) {
        ret = CHECK_CU(cu->cu_ਧਾਰਾ_Synchronize(hwctx->ਧਾਰਾ));
        ਜੇ (ret < 0)
            ਜਾਓ ਬਾਹਰ_ਨਿਕਲੋ;
    }

fail:
    ਜੇ (ret < 0 && copy_queued)
        CHECK_CU(cu->cu_ਧਾਰਾ_Synchronize(hwctx->ਧਾਰਾ));
ਬਾਹਰ_ਨਿਕਲੋ:
    CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));

    ਜੇ (bottom_ਉੱਪਰ_dst && ret >= 0)
        av_image_copy2(bottom_ਉੱਪਰ_dst->ਅੰਕੜੇ, bottom_ਉੱਪਰ_dst->linesize,
                       ਸਿਖਰ_ਥੱਲੇ->ਅੰਕੜੇ, ਸਿਖਰ_ਥੱਲੇ->linesize,
                       ctx->sw_format, src->ਚੌੜਾਈ, src->ਉਚਾਈ);
free_ਸਿਖਰ_ਥੱਲੇ:
    av_ਚੌਖਟਾ_free(&ਸਿਖਰ_ਥੱਲੇ);

    ਵਾਪਸ ret;
}

ਸਥਿਰ ਖਾਲੀ cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    ਜੇ (hwctx->p.ਅੰਦਰੂਨੀ) {
        CudaFunctions *cu = hwctx->ਅੰਦਰੂਨੀ.cuda_dl;

        ਜੇ (hwctx->ਅੰਦਰੂਨੀ.is_allocated && hwctx->p.cuda_ctx) {
            ਜੇ (hwctx->ਅੰਦਰੂਨੀ.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->ਅੰਦਰੂਨੀ.cuda_device));
            ਨਹੀਂਤਾਂ ਜੇ (!(hwctx->ਅੰਦਰੂਨੀ.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = ਨਿਰਾ;
        }

        cuda_free_functions(&hwctx->ਅੰਦਰੂਨੀ.cuda_dl);
        memset(&hwctx->ਅੰਦਰੂਨੀ, 0, ਆਕਾਰ(hwctx->ਅੰਦਰੂਨੀ));
        hwctx->p.ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    }
}

ਸਥਿਰ ਪੂਰਨ cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    ਪੂਰਨ ret;

    hwctx->p.ਅੰਦਰੂਨੀ = &hwctx->ਅੰਦਰੂਨੀ;

    ਜੇ (!hwctx->ਅੰਦਰੂਨੀ.cuda_dl) {
        ret = cuda_ਲੱਦੋ_functions(&hwctx->ਅੰਦਰੂਨੀ.cuda_dl, ctx);
        ਜੇ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            ਜਾਓ error;
        }
    }

    ਵਾਪਸ 0;

error:
    cuda_device_uninit(ctx);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ cuda_context_init(AVHWDeviceContext *device_ctx, ਪੂਰਨ flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    ਪੂਰਨ ret, dev_ਸਰਗਰਮ = 0;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ dev_flags = 0;

    ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->ਅੰਦਰੂਨੀ->cuda_dl;

    hwctx->ਅੰਦਰੂਨੀ->flags = flags;

    ਜੇ (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->ਅੰਦਰੂਨੀ->cuda_device,
                       &dev_flags, &dev_ਸਰਗਰਮ));
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;

        ਜੇ (dev_ਸਰਗਰਮ && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            ਵਾਪਸ AVERROR(ENOTSUP);
        } ਨਹੀਂਤਾਂ ਜੇ (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cu_Device_Primary_Ctx_ਸੈੱਟ_Flags(hwctx->ਅੰਦਰੂਨੀ->cuda_device,
                           desired_flags));
            ਜੇ (ret < 0)
                ਵਾਪਸ ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->ਅੰਦਰੂਨੀ->cuda_device));
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
    } ਨਹੀਂਤਾਂ ਜੇ (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } ਨਹੀਂਤਾਂ {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->ਅੰਦਰੂਨੀ->cuda_device));
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;

        CHECK_CU(cu->cu_Ctx_ਕੱਢੋ_Current(&dummy));
    }

    hwctx->ਅੰਦਰੂਨੀ->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->ਧਾਰਾ = ਨਿਰਾ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, ਪੂਰਨ *flags)
{
    AVDictionary_ਇੰਦਰਾਜ *primary_ctx_opt = av_dict_get(opts, "primary_ctx", ਨਿਰਾ, 0);
    AVDictionary_ਇੰਦਰਾਜ *current_ctx_opt = av_dict_get(opts, "current_ctx", ਨਿਰਾ, 0);

    ਪੂਰਨ use_primary_ctx = 0, use_current_ctx = 0;
    ਜੇ (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->ਮੁੱਲ, ਨਿਰਾ, 10);

    ਜੇ (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->ਮੁੱਲ, ਨਿਰਾ, 10);

    ਜੇ (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        ਵਾਪਸ AVERROR(EINVAL);
    }

    ਜੇ (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } ਨਹੀਂਤਾਂ ਜੇ (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    ਜੇ (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } ਨਹੀਂਤਾਂ ਜੇ (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ cuda_device_create(AVHWDeviceContext *device_ctx,
                              ਅਚਲ ਅੱਖਰ *device,
                              AVDictionary *opts, ਪੂਰਨ flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ਪੂਰਨ ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    ਜੇ (ret < 0)
        ਜਾਓ error;

    ਜੇ (device)
        device_idx = strtol(device, ਨਿਰਾ, 0);

    ret = cuda_device_init(device_ctx);
    ਜੇ (ret < 0)
        ਜਾਓ error;

    cu = hwctx->ਅੰਦਰੂਨੀ->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    ਜੇ (ret < 0)
        ਜਾਓ error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->ਅੰਦਰੂਨੀ->cuda_device, device_idx));
    ਜੇ (ret < 0)
        ਜਾਓ error;

    ret = cuda_context_init(device_ctx, flags);
    ਜੇ (ret < 0)
        ਜਾਓ error;

    ਵਾਪਸ 0;

error:
    cuda_device_uninit(device_ctx);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              ਪੂਰਨ flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ਅਚਲ ਅੱਖਰ *src_uuid = ਨਿਰਾ;
#ਜੇ CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#ਜੇ_ਅੰਤ
    ਪੂਰਨ ret, i, device_ਗਿਣਤੀ;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    ਜੇ (ret < 0)
        ਜਾਓ error;

#ਜੇ CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#ਜੇ_ਅੰਤ

    ਚੋਣ (src_ctx->type) {
#ਜੇ CONFIG_VULKAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TYPE PFN_vkGetPhysicalDeviceProperties2
    ਹਾਲਤ AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .p_ਅਗਲਾ = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        ਰੋਕੋ;
    }
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ TYPE
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ret = AVERROR(ENOSYS);
        ਜਾਓ error;
    }

    ਜੇ (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        ਜਾਓ error;
    }

    ret = cuda_device_init(device_ctx);
    ਜੇ (ret < 0)
        ਜਾਓ error;

    cu = hwctx->ਅੰਦਰੂਨੀ->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    ਜੇ (ret < 0)
        ਜਾਓ error;

    ret = CHECK_CU(cu->cu_Device_Get_ਗਿਣਤੀ(&device_ਗਿਣਤੀ));
    ਜੇ (ret < 0)
        ਜਾਓ error;

    hwctx->ਅੰਦਰੂਨੀ->cuda_device = -1;
    ਲਈ (i = 0; i < device_ਗਿਣਤੀ; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        ਜੇ (ret < 0)
            ਜਾਓ error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        ਜੇ (ret < 0)
            ਜਾਓ error;

        ਜੇ (memcmp(src_uuid, uuid.ਬਾਈਟਾਂ, ਆਕਾਰ (uuid.ਬਾਈਟਾਂ)) == 0) {
            hwctx->ਅੰਦਰੂਨੀ->cuda_device = dev;
            ਰੋਕੋ;
        }
    }

    ਜੇ (hwctx->ਅੰਦਰੂਨੀ->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        ਜਾਓ error;
    }

    ret = cuda_context_init(device_ctx, flags);
    ਜੇ (ret < 0)
        ਜਾਓ error;

    ਵਾਪਸ 0;

error:
    cuda_device_uninit(device_ctx);
    ਵਾਪਸ ret;
}

ਅਚਲ HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_ਮਾਪ    = ਆਕਾਰ(CUDADeviceContext),
    .ਚੌਖਟੇ_hwctx_ਮਾਪ    = ਆਕਾਰ(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .ਚੌਖਟੇ_get_constraints = cuda_ਚੌਖਟੇ_get_constraints,
    .ਚੌਖਟੇ_init          = cuda_ਚੌਖਟੇ_init,
    .ਚੌਖਟੇ_uninit        = cuda_ਚੌਖਟੇ_uninit,
    .ਚੌਖਟੇ_get_ਬਫਰ    = cuda_get_ਬਫਰ,
    .transfer_get_formats = cuda_transfer_get_formats,
#ਜੇ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_ਬਫਰ_alloc = cuda_transfer_ਬਫਰ_alloc,
#ਜੇ_ਅੰਤ
    .transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ     = cuda_transfer_ਅੰਕੜੇ,
    .transfer_ਅੰਕੜੇ_from   = cuda_transfer_ਅੰਕੜੇ,

    .pix_fmts             = (ਅਚਲ ਗਿਣਤੀ AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#ਜੇ HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#ਜੇ_ਅੰਤ
                                                          AV_PIX_FMT_NONE },
};
