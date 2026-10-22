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

#అన్తర్భావ "buffer.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "hwcontext_cuda_internal.h"
#ఒకవేళ CONFIG_VULKAN
#అన్తర్భావ "hwcontext_vulkan.h"
#అయితే_ముగింపు
#అన్తర్భావ "cuda_check.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "pixdesc.h"
#అన్తర్భావ "pixfmt.h"
#అన్తర్భావ "imgutils.h"

రకనిర్వచనం నిర్మాణం CUDAFramesContext {
    AVCUDAFramesContext p;

    పూర్ణాంకం జరుపు_వెడల్పు, జరుపు_ఎత్తు;
    పూర్ణాంకం tex_alignment;

    పూర్ణాంకం cuarray_అంకె_surfaces_వాడిన;
} CUDAFramesContext;

రకనిర్వచనం నిర్మాణం CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADevice_Context_అంతర్గత అంతర్గత;
} CUDADeviceContext;



#నిర్వచించు CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

స్థిర CUarray_format cuda_array_format_for_pix_fmt(గణన AVPixelFormat fmt);

స్థిర పూర్ణాంకం cuda_చట్రాలు_get_constraints(AVHWDeviceContext *ctx,
                                       స్థిరరాశి శూన్య *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    స్థిరరాశి AVCUDAHWConfig *config = hwconfig;
    గణన AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    పూర్ణాంకం n = 0;

    ఒకవేళ (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, పరిమాణం(*constraints->valid_hw_formats));
        ఒకవేళ (!constraints->valid_hw_formats)
            తిరిగి AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } లేకపోతే {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, పరిమాణం(*constraints->valid_hw_formats));
        ఒకవేళ (!constraints->valid_hw_formats)
            తిరిగి AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#ఒకవేళ HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#లేకపోతే
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#అయితే_ముగింపు
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    పరిమాణం(*constraints->valid_sw_formats));
    ఒకవేళ (!constraints->valid_sw_formats)
        తిరిగి AVERROR(ENOMEM);

    n = 0;
    కొరకు (పూర్ణాంకం i = 0; i < AV_PIX_FMT_NB; i++) {
        ఒకవేళ (req_fmt == AV_PIX_FMT_CUARRAY) {
            ఒకవేళ (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } లేకపోతే {
            స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            ఒకవేళ (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#ఒకవేళ CONFIG_VULKAN
    ఒకవేళ (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#అయితే_ముగింపు
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    తిరిగి 0;
}

స్థిర శూన్య cuda_బఫరు_free(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->అంతర్గత->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_నెట్టు_Current(hwctx->cuda_ctx));

    ఒకవేళ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArray_చట్రం_Descriptor *desc = (AVCUDAArray_చట్రం_Descriptor*)దత్తాంశం;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } లేకపోతే {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)దత్తాంశం));
    }

    CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));
}

స్థిర AVBufferRef *cuda_pool_alloc(శూన్య *opaque, size_t కొలత)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->అంతర్గత->cuda_dl;

    AVBufferRef *ret = ఖాళీ;
    CUcontext dummy = ఖాళీ;
    CUdeviceptr దత్తాంశం;
    పూర్ణాంకం err;

    err = CHECK_CU(cu->cu_Ctx_నెట్టు_Current(hwctx->cuda_ctx));
    ఒకవేళ (err < 0)
        తిరిగి ఖాళీ;

    ఒకవేళ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArray_చట్రం_Descriptor *desc = av_mallocz(పరిమాణం(*desc));
        ఒకవేళ (!desc)
            వెళ్ళు పూర్తి;

        ఒకవేళ (priv->p.cuarray_అంకె_surfaces > 0) {
            ఒకవేళ (priv->cuarray_అంకె_surfaces_వాడిన >= priv->p.cuarray_అంకె_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                వెళ్ళు పూర్తి;
            }
            desc->సూచీ = priv->cuarray_అంకె_surfaces_వాడిన++;
            desc->array = priv->p.cuarray_surfaces[desc->సూచీ];
        } లేకపోతే {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            ఒకవేళ (err < 0) {
                av_free(desc);
                వెళ్ళు పూర్తి;
            }
        }

        ret = av_బఫరు_create((uint8_t*)desc, పరిమాణం(*desc), cuda_బఫరు_free, ctx, 0);
        ఒకవేళ (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            వెళ్ళు పూర్తి;
        }

        వెళ్ళు పూర్తి;
    }

    err = CHECK_CU(cu->cuMemAlloc(&దత్తాంశం, కొలత));
    ఒకవేళ (err < 0)
        వెళ్ళు పూర్తి;

    ret = av_బఫరు_create((uint8_t*)దత్తాంశం, కొలత, cuda_బఫరు_free, ctx, 0);
    ఒకవేళ (!ret) {
        CHECK_CU(cu->cuMemFree(దత్తాంశం));
        వెళ్ళు పూర్తి;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
పూర్తి:
    CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));
    తిరిగి ret;
}

#ఒకవేళ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
స్థిర శూన్య cuda_transfer_బఫరు_free(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->అంతర్గత->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_నెట్టు_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(దత్తాంశం));
    CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
స్థిర AVBufferRef *cuda_transfer_బఫరు_alloc(శూన్య *device_ref, size_t కొలత)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->దత్తాంశం;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->అంతర్గత->cuda_dl;
    AVBufferRef *ret = ఖాళీ;
    CUcontext dummy;
    శూన్య *host;

    ఒకవేళ (CHECK_CU(cu->cu_Ctx_నెట్టు_Current(hwctx->cuda_ctx)) < 0)
        తిరిగి av_బఫరు_alloc(కొలత);

    ఒకవేళ (CHECK_CU(cu->cuMemHostAlloc(&host, కొలత, 0)) >= 0) {
        ret = av_బఫరు_create(host, కొలత, cuda_transfer_బఫరు_free, device_ctx, 0);
        ఒకవేళ (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));
    తిరిగి ret ? ret : av_బఫరు_alloc(కొలత);
}
#అయితే_ముగింపు

స్థిర శూన్య cuda_చట్రాలు_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->అంతర్గత->cuda_dl;

    ఒకవేళ (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_నెట్టు_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        కొరకు (పూర్ణాంకం i = priv->cuarray_అంకె_surfaces_వాడిన; i < priv->p.cuarray_అంకె_surfaces; i++)
            ఒకవేళ (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_అంకె_surfaces = 0;
    }
}

స్థిర CUarray_format cuda_array_format_for_pix_fmt(గణన AVPixelFormat fmt)
{
    ఎంపిక (fmt) {
#ఒకవేళ HAVE_FFNVCODEC_CUARRAY
    స్థితి AV_PIX_FMT_NV12:      తిరిగి CU_AD_FORMAT_NV12;
    స్థితి AV_PIX_FMT_P010:
    స్థితి AV_PIX_FMT_P012:
    స్థితి AV_PIX_FMT_P016:      తిరిగి CU_AD_FORMAT_P016;
    స్థితి AV_PIX_FMT_NV16:      తిరిగి CU_AD_FORMAT_NV16;
    స్థితి AV_PIX_FMT_P210:
    స్థితి AV_PIX_FMT_P212:
    స్థితి AV_PIX_FMT_P216:      తిరిగి CU_AD_FORMAT_P216;
    స్థితి AV_PIX_FMT_NV24:      తిరిగి CU_AD_FORMAT_YUV444_8_బిట్టు_SEMIPLANAR;
    స్థితి AV_PIX_FMT_P410:
    స్థితి AV_PIX_FMT_P412:
    స్థితి AV_PIX_FMT_P416:      తిరిగి CU_AD_FORMAT_YUV444_16_బిట్టు_SEMIPLANAR;
    స్థితి AV_PIX_FMT_YUV420P:   తిరిగి CU_AD_FORMAT_UINT8_PLANAR_420;
    స్థితి AV_PIX_FMT_YUV422P:   తిరిగి CU_AD_FORMAT_UINT8_PLANAR_422;
    స్థితి AV_PIX_FMT_YUV444P:   తిరిగి CU_AD_FORMAT_UINT8_PLANAR_444;
    స్థితి AV_PIX_FMT_YUV420P10: తిరిగి CU_AD_FORMAT_UINT16_PLANAR_420;
    స్థితి AV_PIX_FMT_YUV422P10: తిరిగి CU_AD_FORMAT_UINT16_PLANAR_422;
    స్థితి AV_PIX_FMT_YUV444P10:
    స్థితి AV_PIX_FMT_YUV444P10MSB:
    స్థితి AV_PIX_FMT_YUV444P12MSB:
    స్థితి AV_PIX_FMT_YUV444P16: తిరిగి CU_AD_FORMAT_UINT16_PLANAR_444;
    స్థితి AV_PIX_FMT_0RGB32:
    స్థితి AV_PIX_FMT_0BGR32:
    స్థితి AV_PIX_FMT_RGB32:
    స్థితి AV_PIX_FMT_BGR32:     తిరిగి CU_AD_FORMAT_UNSIGNED_INT8;
#అయితే_ముగింపు
    అప్రమేయ:                   తిరిగి 0;
    }
}

#ఒకవేళ HAVE_FFNVCODEC_CUARRAY
స్థిర గుర్తులేని పూర్ణాంకం cuda_array_numchannels_for_pix_fmt(గణన AVPixelFormat fmt)
{
    ఎంపిక (fmt) {
    స్థితి AV_PIX_FMT_0RGB32:
    స్థితి AV_PIX_FMT_0BGR32:
    స్థితి AV_PIX_FMT_RGB32:
    స్థితి AV_PIX_FMT_BGR32:     తిరిగి 4;
    అప్రమేయ:                   తిరిగి 3;
    }
}
#అయితే_ముగింపు

స్థిర పూర్ణాంకం cuda_చట్రాలు_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->అంతర్గత->cuda_dl;
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    పూర్ణాంకం err;

    ఒకవేళ (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        తిరిగి AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    ఒకవేళ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        తిరిగి AVERROR(ENOSYS);
    }

#ఒకవేళ HAVE_FFNVCODEC_CUARRAY
    ఒకవేళ (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        తిరిగి AVERROR(ENOSYS);
    }
#లేకపోతే
    ఒకవేళ (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        తిరిగి AVERROR(ENOSYS);
    }
#అయితే_ముగింపు

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->అంతర్గత->cuda_device));
    ఒకవేళ (err < 0)
        తిరిగి err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    ఒకవేళ (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->జరుపు_వెడల్పు, &priv->జరుపు_ఎత్తు);

#ఒకవేళ HAVE_FFNVCODEC_CUARRAY
    ఒకవేళ (ctx->format == AV_PIX_FMT_CUARRAY) {
        ఒకవేళ (!priv->p.cuarray_desc.వెడల్పు_2)
            priv->p.cuarray_desc.వెడల్పు_2 = ctx->వెడల్పు;
        ఒకవేళ (!priv->p.cuarray_desc.ఎత్తు_2)
            priv->p.cuarray_desc.ఎత్తు_2 = ctx->ఎత్తు;
        ఒకవేళ (!priv->p.cuarray_desc.అంకె_Channels)
            priv->p.cuarray_desc.అంకె_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        ఒకవేళ (priv->p.cuarray_desc.లోతు_2) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            తిరిగి AVERROR(EINVAL);
        }

        ఒకవేళ (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        ఒకవేళ (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            తిరిగి AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    ఒకవేళ (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_అంకె_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_అంకె_surfaces, పరిమాణం(*priv->p.cuarray_surfaces));
        ఒకవేళ (!priv->p.cuarray_surfaces)
            తిరిగి AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_నెట్టు_Current(hwctx->cuda_ctx));
        ఒకవేళ (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            తిరిగి err;
        }

        కొరకు (పూర్ణాంకం i = 0; i < priv->p.cuarray_అంకె_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            ఒకవేళ (err < 0) {
                కొరకు (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                తిరిగి err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));
        ఒకవేళ (err < 0)
            వెళ్ళు fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_అంకె_surfaces, priv->p.cuarray_desc.వెడల్పు_2, priv->p.cuarray_desc.ఎత్తు_2);
    }
#అయితే_ముగింపు

    ఒకవేళ (!ctx->pool) {
        పూర్ణాంకం కొలత = av_image_get_బఫరు_కొలత(ctx->sw_format, ctx->వెడల్పు, ctx->ఎత్తు, priv->tex_alignment);
        ఒకవేళ (కొలత < 0) {
            err = కొలత;
            వెళ్ళు fail;
        }

        ffhwframesctx(ctx)->pool_అంతర్గత =
            av_బఫరు_pool_init2(కొలత, ctx, cuda_pool_alloc, ఖాళీ);
        ఒకవేళ (!ffhwframesctx(ctx)->pool_అంతర్గత) {
            err = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }
    }

    తిరిగి 0;

fail:
    cuda_చట్రాలు_uninit(ctx);
    తిరిగి err;
}

స్థిర పూర్ణాంకం cuda_get_బఫరు(AVHWFramesContext *ctx, AVFrame *చట్రం)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#ఒకవేళ HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->అంతర్గత->cuda_dl;

    CUcontext dummy;
#అయితే_ముగింపు
    పూర్ణాంకం res;

    చట్రం->buf[0] = av_బఫరు_pool_get(ctx->pool);
    ఒకవేళ (!చట్రం->buf[0])
        తిరిగి AVERROR(ENOMEM);

    ఒకవేళ (ctx->format == AV_PIX_FMT_CUARRAY) {
#ఒకవేళ HAVE_FFNVCODEC_CUARRAY
        AVCUDAArray_చట్రం_Descriptor *desc = (AVCUDAArray_చట్రం_Descriptor*)చట్రం->buf[0]->దత్తాంశం;
        ఒకవేళ (!desc) {
            చట్రం->format = ctx->format;
            చట్రం->వెడల్పు  = ctx->వెడల్పు;
            చట్రం->ఎత్తు = ctx->ఎత్తు;
            తిరిగి 0;
        }
        చట్రం->దత్తాంశం[0] = (uint8_t*)desc->array;
        చట్రం->దత్తాంశం[1] = (uint8_t*)desc->సూచీ;

        res = CHECK_CU(cu->cu_Ctx_నెట్టు_Current(hwctx->cuda_ctx));
        ఒకవేళ (res < 0)
            తిరిగి res;

        కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(చట్రం->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            ఒకవేళ (arr_plane_res == CUDA_ERROR_INVALID_విలువ) {
                ఒకవేళ (i > 0)
                    ఆపు;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                ఒకవేళ (res < 0)
                    వెళ్ళు fail;
            } లేకపోతే ఒకవేళ (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                వెళ్ళు fail;
            } లేకపోతే {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                ఒకవేళ (res < 0)
                    వెళ్ళు fail;
            }

            పూర్ణాంకం elem_కొలత = ff_cuda_cuarray_elem_కొలత(plane_desc.Format);
            ఒకవేళ (elem_కొలత <= 0) {
                res = AVERROR_BUG;
                వెళ్ళు fail;
            }

            చట్రం->linesize[i] = plane_desc.వెడల్పు_2 * plane_desc.అంకె_Channels * elem_కొలత;

            ఒకవేళ (arr_plane_res == CUDA_ERROR_INVALID_విలువ)
                ఆపు;
        }

        res = CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));
        ఒకవేళ (res < 0)
            తిరిగి res;
#లేకపోతే
        తిరిగి AVERROR(ENOSYS);
#అయితే_ముగింపు
    } లేకపోతే {
        res = av_image_fill_arrays(చట్రం->దత్తాంశం, చట్రం->linesize, చట్రం->buf[0]->దత్తాంశం,
                                   ctx->sw_format, ctx->వెడల్పు, ctx->ఎత్తు, priv->tex_alignment);
        ఒకవేళ (res < 0)
            తిరిగి res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        ఒకవేళ (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            చట్రం->linesize[1] = చట్రం->linesize[2] = చట్రం->linesize[0] / 2;
            చట్రం->దత్తాంశం[2]     = చట్రం->దత్తాంశం[1];
            చట్రం->దత్తాంశం[1]     = చట్రం->దత్తాంశం[2] + చట్రం->linesize[2] * AV_CEIL_RSHIFT(ctx->ఎత్తు, 1);
        }
    }

    చట్రం->format = ctx->format;
    చట్రం->వెడల్పు  = ctx->వెడల్పు;
    చట్రం->ఎత్తు = ctx->ఎత్తు;

    తిరిగి 0;

#ఒకవేళ HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));
    తిరిగి res;
#అయితే_ముగింపు
}

స్థిర గణన AVPixelFormat cuda_చట్రం_hw_format(స్థిరరాశి AVFrame *చట్రం)
{
    ఒకవేళ (!చట్రం->hw_చట్రాలు_ctx)
        తిరిగి AV_PIX_FMT_NONE;
    తిరిగి ((AVHWFramesContext *)చట్రం->hw_చట్రాలు_ctx->దత్తాంశం)->format;
}

స్థిర పూర్ణాంకం cuda_transfer_get_formats(AVHWFramesContext *ctx,
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

స్థిర పూర్ణాంకం cuda_transfer_దత్తాంశం(AVHWFramesContext *ctx, AVFrame *dst,
                                 స్థిరరాశి AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->అంతర్గత->cuda_dl;

    స్థిరరాశి AVFrame *sw_చట్రం = src->hw_చట్రాలు_ctx ? dst : src;
    AVFrame *శిఖరం_కిందికి = ఖాళీ, *bottom_పైకి_dst = ఖాళీ;
    CUcontext dummy;
    పూర్ణాంకం i, ret, copy_queued = 0, bottom_పైకి = 0;

    {
        గణన AVPixelFormat src_fmt = cuda_చట్రం_hw_format(src);
        గణన AVPixelFormat dst_fmt = cuda_చట్రం_hw_format(dst);
        ఒకవేళ ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            తిరిగి AVERROR(ENOSYS);
    }

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(sw_చట్రం->linesize); i++)
        bottom_పైకి |= sw_చట్రం->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    ఒకవేళ (bottom_పైకి) {
        శిఖరం_కిందికి = av_చట్రం_alloc();
        ఒకవేళ (!శిఖరం_కిందికి)
            తిరిగి AVERROR(ENOMEM);
        శిఖరం_కిందికి->format = ctx->sw_format;
        శిఖరం_కిందికి->వెడల్పు  = ctx->వెడల్పు;
        శిఖరం_కిందికి->ఎత్తు = ctx->ఎత్తు;
        ret = av_hwframe_get_transfer_బఫరు((src->hw_చట్రాలు_ctx ? src : dst)->hw_చట్రాలు_ctx,
                                             శిఖరం_కిందికి);
        ఒకవేళ (ret < 0)
            వెళ్ళు free_శిఖరం_కిందికి;
        శిఖరం_కిందికి->వెడల్పు  = src->వెడల్పు;
        శిఖరం_కిందికి->ఎత్తు = src->ఎత్తు;
        ఒకవేళ (sw_చట్రం == src) {
            av_image_copy2(శిఖరం_కిందికి->దత్తాంశం, శిఖరం_కిందికి->linesize, src->దత్తాంశం, src->linesize,
                           ctx->sw_format, src->వెడల్పు, src->ఎత్తు);
            src = శిఖరం_కిందికి;
        } లేకపోతే {
            bottom_పైకి_dst = dst;
            dst           = శిఖరం_కిందికి;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_నెట్టు_Current(hwctx->cuda_ctx));
    ఒకవేళ (ret < 0)
        వెళ్ళు free_శిఖరం_కిందికి;

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
    కొరకు (i = 0; i < FF_ARRAY_ELEMS(src->దత్తాంశం) && src->linesize[i]; i++) {
        పూర్ణాంకం src_is_nonplanar_cuarray = 0;
        పూర్ణాంకం dst_is_nonplanar_cuarray = 0;

        పూర్ణాంకం bytewidth = av_image_get_linesize(ctx->sw_format, src->వెడల్పు, i);
        ఒకవేళ (bytewidth < 0) {
            ret = bytewidth;
            వెళ్ళు fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .వెడల్పు_లోపల_బైట్లు  = bytewidth,
            .ఎత్తు_2        = AV_CEIL_RSHIFT(src->ఎత్తు, ((i == 0 || i == 3) ? 0 : priv->జరుపు_ఎత్తు)),
        };

        ఒకవేళ (src->format == AV_PIX_FMT_CUDA) {
            cpy.src_జ్ఞాపకం_Type = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->దత్తాంశం[i];
        } లేకపోతే ఒకవేళ (src->format == AV_PIX_FMT_CUARRAY) {
#ఒకవేళ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->దత్తాంశం[0], i);
            ఒకవేళ (cures == CUDA_ERROR_INVALID_విలువ && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->దత్తాంశం[0];
                src_is_nonplanar_cuarray = 1;
            } లేకపోతే ఒకవేళ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                వెళ్ళు fail;
            }

            cpy.src_జ్ఞాపకం_Type = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#లేకపోతే
            ret = AVERROR(ENOSYS);
            వెళ్ళు నిష్క్రమించు;
#అయితే_ముగింపు
        } లేకపోతే {
            cpy.src_జ్ఞాపకం_Type = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->దత్తాంశం[i];
        }

        ఒకవేళ (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dst_జ్ఞాపకం_Type = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->దత్తాంశం[i];
        } లేకపోతే ఒకవేళ (dst->format == AV_PIX_FMT_CUARRAY) {
#ఒకవేళ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->దత్తాంశం[0], i);
            ఒకవేళ (cures == CUDA_ERROR_INVALID_విలువ && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->దత్తాంశం[0];
                dst_is_nonplanar_cuarray = 1;
            } లేకపోతే ఒకవేళ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                వెళ్ళు fail;
            }

            cpy.dst_జ్ఞాపకం_Type = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#లేకపోతే
            ret = AVERROR(ENOSYS);
            వెళ్ళు నిష్క్రమించు;
#అయితే_ముగింపు
        } లేకపోతే {
            cpy.dst_జ్ఞాపకం_Type = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->దత్తాంశం[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->ప్రవాహం));
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;
        copy_queued = 1;

        ఒకవేళ (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            ఆపు;
    }

    /* The caller may reuse host memory once the transfer returns. */
    ఒకవేళ (!src->hw_చట్రాలు_ctx || !dst->hw_చట్రాలు_ctx) {
        ret = CHECK_CU(cu->cu_ప్రవాహం_Synchronize(hwctx->ప్రవాహం));
        ఒకవేళ (ret < 0)
            వెళ్ళు నిష్క్రమించు;
    }

fail:
    ఒకవేళ (ret < 0 && copy_queued)
        CHECK_CU(cu->cu_ప్రవాహం_Synchronize(hwctx->ప్రవాహం));
నిష్క్రమించు:
    CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));

    ఒకవేళ (bottom_పైకి_dst && ret >= 0)
        av_image_copy2(bottom_పైకి_dst->దత్తాంశం, bottom_పైకి_dst->linesize,
                       శిఖరం_కిందికి->దత్తాంశం, శిఖరం_కిందికి->linesize,
                       ctx->sw_format, src->వెడల్పు, src->ఎత్తు);
free_శిఖరం_కిందికి:
    av_చట్రం_free(&శిఖరం_కిందికి);

    తిరిగి ret;
}

స్థిర శూన్య cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    ఒకవేళ (hwctx->p.అంతర్గత) {
        CudaFunctions *cu = hwctx->అంతర్గత.cuda_dl;

        ఒకవేళ (hwctx->అంతర్గత.is_allocated && hwctx->p.cuda_ctx) {
            ఒకవేళ (hwctx->అంతర్గత.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->అంతర్గత.cuda_device));
            లేకపోతే ఒకవేళ (!(hwctx->అంతర్గత.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = ఖాళీ;
        }

        cuda_free_functions(&hwctx->అంతర్గత.cuda_dl);
        memset(&hwctx->అంతర్గత, 0, పరిమాణం(hwctx->అంతర్గత));
        hwctx->p.అంతర్గత = ఖాళీ;
    }
}

స్థిర పూర్ణాంకం cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    పూర్ణాంకం ret;

    hwctx->p.అంతర్గత = &hwctx->అంతర్గత;

    ఒకవేళ (!hwctx->అంతర్గత.cuda_dl) {
        ret = cuda_ఎక్కించు_functions(&hwctx->అంతర్గత.cuda_dl, ctx);
        ఒకవేళ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            వెళ్ళు error;
        }
    }

    తిరిగి 0;

error:
    cuda_device_uninit(ctx);
    తిరిగి ret;
}

స్థిర పూర్ణాంకం cuda_context_init(AVHWDeviceContext *device_ctx, పూర్ణాంకం flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    పూర్ణాంకం ret, dev_చురుకైన = 0;
    గుర్తులేని పూర్ణాంకం dev_flags = 0;

    స్థిరరాశి గుర్తులేని పూర్ణాంకం desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->అంతర్గత->cuda_dl;

    hwctx->అంతర్గత->flags = flags;

    ఒకవేళ (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->అంతర్గత->cuda_device,
                       &dev_flags, &dev_చురుకైన));
        ఒకవేళ (ret < 0)
            తిరిగి ret;

        ఒకవేళ (dev_చురుకైన && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            తిరిగి AVERROR(ENOTSUP);
        } లేకపోతే ఒకవేళ (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cu_Device_Primary_Ctx_సమితి_Flags(hwctx->అంతర్గత->cuda_device,
                           desired_flags));
            ఒకవేళ (ret < 0)
                తిరిగి ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->అంతర్గత->cuda_device));
        ఒకవేళ (ret < 0)
            తిరిగి ret;
    } లేకపోతే ఒకవేళ (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        ఒకవేళ (ret < 0)
            తిరిగి ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } లేకపోతే {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->అంతర్గత->cuda_device));
        ఒకవేళ (ret < 0)
            తిరిగి ret;

        CHECK_CU(cu->cu_Ctx_తీయి_Current(&dummy));
    }

    hwctx->అంతర్గత->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->ప్రవాహం = ఖాళీ;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, పూర్ణాంకం *flags)
{
    AVDictionary_నమోదు *primary_ctx_opt = av_dict_get(opts, "primary_ctx", ఖాళీ, 0);
    AVDictionary_నమోదు *current_ctx_opt = av_dict_get(opts, "current_ctx", ఖాళీ, 0);

    పూర్ణాంకం use_primary_ctx = 0, use_current_ctx = 0;
    ఒకవేళ (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->విలువ, ఖాళీ, 10);

    ఒకవేళ (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->విలువ, ఖాళీ, 10);

    ఒకవేళ (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        తిరిగి AVERROR(EINVAL);
    }

    ఒకవేళ (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } లేకపోతే ఒకవేళ (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    ఒకవేళ (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } లేకపోతే ఒకవేళ (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం cuda_device_create(AVHWDeviceContext *device_ctx,
                              స్థిరరాశి అక్షరం *device,
                              AVDictionary *opts, పూర్ణాంకం flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    పూర్ణాంకం ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    ఒకవేళ (ret < 0)
        వెళ్ళు error;

    ఒకవేళ (device)
        device_idx = strtol(device, ఖాళీ, 0);

    ret = cuda_device_init(device_ctx);
    ఒకవేళ (ret < 0)
        వెళ్ళు error;

    cu = hwctx->అంతర్గత->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    ఒకవేళ (ret < 0)
        వెళ్ళు error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->అంతర్గత->cuda_device, device_idx));
    ఒకవేళ (ret < 0)
        వెళ్ళు error;

    ret = cuda_context_init(device_ctx, flags);
    ఒకవేళ (ret < 0)
        వెళ్ళు error;

    తిరిగి 0;

error:
    cuda_device_uninit(device_ctx);
    తిరిగి ret;
}

స్థిర పూర్ణాంకం cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              పూర్ణాంకం flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    స్థిరరాశి అక్షరం *src_uuid = ఖాళీ;
#ఒకవేళ CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#అయితే_ముగింపు
    పూర్ణాంకం ret, i, device_లెక్క;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    ఒకవేళ (ret < 0)
        వెళ్ళు error;

#ఒకవేళ CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#అయితే_ముగింపు

    ఎంపిక (src_ctx->type) {
#ఒకవేళ CONFIG_VULKAN
#నిర్వచించు TYPE PFN_vkGetPhysicalDeviceProperties2
    స్థితి AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .p_తదుపరి = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        ఆపు;
    }
#నిర్వచనం_రద్దు TYPE
#అయితే_ముగింపు
    అప్రమేయ:
        ret = AVERROR(ENOSYS);
        వెళ్ళు error;
    }

    ఒకవేళ (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        వెళ్ళు error;
    }

    ret = cuda_device_init(device_ctx);
    ఒకవేళ (ret < 0)
        వెళ్ళు error;

    cu = hwctx->అంతర్గత->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    ఒకవేళ (ret < 0)
        వెళ్ళు error;

    ret = CHECK_CU(cu->cu_Device_Get_లెక్క(&device_లెక్క));
    ఒకవేళ (ret < 0)
        వెళ్ళు error;

    hwctx->అంతర్గత->cuda_device = -1;
    కొరకు (i = 0; i < device_లెక్క; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        ఒకవేళ (ret < 0)
            వెళ్ళు error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        ఒకవేళ (ret < 0)
            వెళ్ళు error;

        ఒకవేళ (memcmp(src_uuid, uuid.బైట్లు, పరిమాణం (uuid.బైట్లు)) == 0) {
            hwctx->అంతర్గత->cuda_device = dev;
            ఆపు;
        }
    }

    ఒకవేళ (hwctx->అంతర్గత->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        వెళ్ళు error;
    }

    ret = cuda_context_init(device_ctx, flags);
    ఒకవేళ (ret < 0)
        వెళ్ళు error;

    తిరిగి 0;

error:
    cuda_device_uninit(device_ctx);
    తిరిగి ret;
}

స్థిరరాశి HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_కొలత    = పరిమాణం(CUDADeviceContext),
    .చట్రాలు_hwctx_కొలత    = పరిమాణం(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .చట్రాలు_get_constraints = cuda_చట్రాలు_get_constraints,
    .చట్రాలు_init          = cuda_చట్రాలు_init,
    .చట్రాలు_uninit        = cuda_చట్రాలు_uninit,
    .చట్రాలు_get_బఫరు    = cuda_get_బఫరు,
    .transfer_get_formats = cuda_transfer_get_formats,
#ఒకవేళ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_బఫరు_alloc = cuda_transfer_బఫరు_alloc,
#అయితే_ముగింపు
    .transfer_దత్తాంశం_గమ్యం     = cuda_transfer_దత్తాంశం,
    .transfer_దత్తాంశం_from   = cuda_transfer_దత్తాంశం,

    .pix_fmts             = (స్థిరరాశి గణన AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#ఒకవేళ HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#అయితే_ముగింపు
                                                          AV_PIX_FMT_NONE },
};
