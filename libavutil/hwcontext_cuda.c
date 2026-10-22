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

#अन्तर्भाव "buffer.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "hwcontext_cuda_internal.h"
#यदि CONFIG_VULKAN
#अन्तर्भाव "hwcontext_vulkan.h"
#यदि_अन्तः
#अन्तर्भाव "cuda_check.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "imgutils.h"

प्रकारनिर्देश संरचना CUDAFramesContext {
    AVCUDAFramesContext p;

    पूर्णाङ्क सरणम्_विस्तारः, सरणम्_height;
    पूर्णाङ्क tex_alignment;

    पूर्णाङ्क cuarray_अङ्कः_surfaces_प्रयुक्तम्;
} CUDAFramesContext;

प्रकारनिर्देश संरचना CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADevice_Context_आन्तरिकम् आन्तरिकम्;
} CUDADeviceContext;



#परिभाषय CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

स्थिर CUarray_format cuda_array_format_for_pix_fmt(गणना AVPixelFormat fmt);

स्थिर पूर्णाङ्क cuda_चौकटाः_get_constraints(AVHWDeviceContext *ctx,
                                       ध्रुव शून्य *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ध्रुव AVCUDAHWConfig *config = hwconfig;
    गणना AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    पूर्णाङ्क n = 0;

    यदि (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, परिमाण(*constraints->valid_hw_formats));
        यदि (!constraints->valid_hw_formats)
            प्रत्यागम AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } अन्यथा {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, परिमाण(*constraints->valid_hw_formats));
        यदि (!constraints->valid_hw_formats)
            प्रत्यागम AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#यदि HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#अन्यथा
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#यदि_अन्तः
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    परिमाण(*constraints->valid_sw_formats));
    यदि (!constraints->valid_sw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    n = 0;
    प्रति (पूर्णाङ्क i = 0; i < AV_PIX_FMT_NB; i++) {
        यदि (req_fmt == AV_PIX_FMT_CUARRAY) {
            यदि (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } अन्यथा {
            ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            यदि (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#यदि CONFIG_VULKAN
    यदि (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#यदि_अन्तः
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    प्रत्यागम 0;
}

स्थिर शून्य cuda_बफर_free(शून्य *opaque, uint8_t *दत्त)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->आन्तरिकम्->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));

    यदि (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)दत्त;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } अन्यथा {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)दत्त));
    }

    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
}

स्थिर AVBufferRef *cuda_pool_alloc(शून्य *opaque, size_t आकार)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->आन्तरिकम्->cuda_dl;

    AVBufferRef *ret = रिक्त;
    CUcontext dummy = रिक्त;
    CUdeviceptr दत्त;
    पूर्णाङ्क err;

    err = CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));
    यदि (err < 0)
        प्रत्यागम रिक्त;

    यदि (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = av_mallocz(परिमाण(*desc));
        यदि (!desc)
            गच्छ समाप्तम्;

        यदि (priv->p.cuarray_अङ्कः_surfaces > 0) {
            यदि (priv->cuarray_अङ्कः_surfaces_प्रयुक्तम् >= priv->p.cuarray_अङ्कः_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                गच्छ समाप्तम्;
            }
            desc->सूचकांक = priv->cuarray_अङ्कः_surfaces_प्रयुक्तम्++;
            desc->array = priv->p.cuarray_surfaces[desc->सूचकांक];
        } अन्यथा {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            यदि (err < 0) {
                av_free(desc);
                गच्छ समाप्तम्;
            }
        }

        ret = av_बफर_create((uint8_t*)desc, परिमाण(*desc), cuda_बफर_free, ctx, 0);
        यदि (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            गच्छ समाप्तम्;
        }

        गच्छ समाप्तम्;
    }

    err = CHECK_CU(cu->cuMemAlloc(&दत्त, आकार));
    यदि (err < 0)
        गच्छ समाप्तम्;

    ret = av_बफर_create((uint8_t*)दत्त, आकार, cuda_बफर_free, ctx, 0);
    यदि (!ret) {
        CHECK_CU(cu->cuMemFree(दत्त));
        गच्छ समाप्तम्;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
समाप्तम्:
    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
    प्रत्यागम ret;
}

#यदि HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
स्थिर शून्य cuda_transfer_बफर_free(शून्य *opaque, uint8_t *दत्त)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->आन्तरिकम्->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(दत्त));
    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
स्थिर AVBufferRef *cuda_transfer_बफर_alloc(शून्य *device_ref, size_t आकार)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->दत्त;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->आन्तरिकम्->cuda_dl;
    AVBufferRef *ret = रिक्त;
    CUcontext dummy;
    शून्य *host;

    यदि (CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx)) < 0)
        प्रत्यागम av_बफर_alloc(आकार);

    यदि (CHECK_CU(cu->cuMemHostAlloc(&host, आकार, 0)) >= 0) {
        ret = av_बफर_create(host, आकार, cuda_transfer_बफर_free, device_ctx, 0);
        यदि (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
    प्रत्यागम ret ? ret : av_बफर_alloc(आकार);
}
#यदि_अन्तः

स्थिर शून्य cuda_चौकटाः_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->आन्तरिकम्->cuda_dl;

    यदि (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        प्रति (पूर्णाङ्क i = priv->cuarray_अङ्कः_surfaces_प्रयुक्तम्; i < priv->p.cuarray_अङ्कः_surfaces; i++)
            यदि (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_अङ्कः_surfaces = 0;
    }
}

स्थिर CUarray_format cuda_array_format_for_pix_fmt(गणना AVPixelFormat fmt)
{
    विकल्प (fmt) {
#यदि HAVE_FFNVCODEC_CUARRAY
    पक्ष AV_PIX_FMT_NV12:      प्रत्यागम CU_AD_FORMAT_NV12;
    पक्ष AV_PIX_FMT_P010:
    पक्ष AV_PIX_FMT_P012:
    पक्ष AV_PIX_FMT_P016:      प्रत्यागम CU_AD_FORMAT_P016;
    पक्ष AV_PIX_FMT_NV16:      प्रत्यागम CU_AD_FORMAT_NV16;
    पक्ष AV_PIX_FMT_P210:
    पक्ष AV_PIX_FMT_P212:
    पक्ष AV_PIX_FMT_P216:      प्रत्यागम CU_AD_FORMAT_P216;
    पक्ष AV_PIX_FMT_NV24:      प्रत्यागम CU_AD_FORMAT_YUV444_8BIT_SEMIPLANAR;
    पक्ष AV_PIX_FMT_P410:
    पक्ष AV_PIX_FMT_P412:
    पक्ष AV_PIX_FMT_P416:      प्रत्यागम CU_AD_FORMAT_YUV444_16BIT_SEMIPLANAR;
    पक्ष AV_PIX_FMT_YUV420P:   प्रत्यागम CU_AD_FORMAT_UINT8_PLANAR_420;
    पक्ष AV_PIX_FMT_YUV422P:   प्रत्यागम CU_AD_FORMAT_UINT8_PLANAR_422;
    पक्ष AV_PIX_FMT_YUV444P:   प्रत्यागम CU_AD_FORMAT_UINT8_PLANAR_444;
    पक्ष AV_PIX_FMT_YUV420P10: प्रत्यागम CU_AD_FORMAT_UINT16_PLANAR_420;
    पक्ष AV_PIX_FMT_YUV422P10: प्रत्यागम CU_AD_FORMAT_UINT16_PLANAR_422;
    पक्ष AV_PIX_FMT_YUV444P10:
    पक्ष AV_PIX_FMT_YUV444P10MSB:
    पक्ष AV_PIX_FMT_YUV444P12MSB:
    पक्ष AV_PIX_FMT_YUV444P16: प्रत्यागम CU_AD_FORMAT_UINT16_PLANAR_444;
    पक्ष AV_PIX_FMT_0RGB32:
    पक्ष AV_PIX_FMT_0BGR32:
    पक्ष AV_PIX_FMT_RGB32:
    पक्ष AV_PIX_FMT_BGR32:     प्रत्यागम CU_AD_FORMAT_UNSIGNED_INT8;
#यदि_अन्तः
    स्वभाव:                   प्रत्यागम 0;
    }
}

#यदि HAVE_FFNVCODEC_CUARRAY
स्थिर अचिह्नित पूर्णाङ्क cuda_array_numchannels_for_pix_fmt(गणना AVPixelFormat fmt)
{
    विकल्प (fmt) {
    पक्ष AV_PIX_FMT_0RGB32:
    पक्ष AV_PIX_FMT_0BGR32:
    पक्ष AV_PIX_FMT_RGB32:
    पक्ष AV_PIX_FMT_BGR32:     प्रत्यागम 4;
    स्वभाव:                   प्रत्यागम 3;
    }
}
#यदि_अन्तः

स्थिर पूर्णाङ्क cuda_चौकटाः_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->आन्तरिकम्->cuda_dl;
    ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    पूर्णाङ्क err;

    यदि (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    यदि (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        प्रत्यागम AVERROR(ENOSYS);
    }

#यदि HAVE_FFNVCODEC_CUARRAY
    यदि (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        प्रत्यागम AVERROR(ENOSYS);
    }
#अन्यथा
    यदि (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        प्रत्यागम AVERROR(ENOSYS);
    }
#यदि_अन्तः

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->आन्तरिकम्->cuda_device));
    यदि (err < 0)
        प्रत्यागम err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    यदि (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->सरणम्_विस्तारः, &priv->सरणम्_height);

#यदि HAVE_FFNVCODEC_CUARRAY
    यदि (ctx->format == AV_PIX_FMT_CUARRAY) {
        यदि (!priv->p.cuarray_desc.विस्तारः_2)
            priv->p.cuarray_desc.विस्तारः_2 = ctx->विस्तारः;
        यदि (!priv->p.cuarray_desc.Height)
            priv->p.cuarray_desc.Height = ctx->height;
        यदि (!priv->p.cuarray_desc.अङ्कः_Channels)
            priv->p.cuarray_desc.अङ्कः_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        यदि (priv->p.cuarray_desc.गभीरता_2) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            प्रत्यागम AVERROR(EINVAL);
        }

        यदि (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        यदि (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            प्रत्यागम AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    यदि (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_अङ्कः_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_अङ्कः_surfaces, परिमाण(*priv->p.cuarray_surfaces));
        यदि (!priv->p.cuarray_surfaces)
            प्रत्यागम AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));
        यदि (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            प्रत्यागम err;
        }

        प्रति (पूर्णाङ्क i = 0; i < priv->p.cuarray_अङ्कः_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            यदि (err < 0) {
                प्रति (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                प्रत्यागम err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
        यदि (err < 0)
            गच्छ fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_अङ्कः_surfaces, priv->p.cuarray_desc.विस्तारः_2, priv->p.cuarray_desc.Height);
    }
#यदि_अन्तः

    यदि (!ctx->pool) {
        पूर्णाङ्क आकार = av_image_get_बफर_आकार(ctx->sw_format, ctx->विस्तारः, ctx->height, priv->tex_alignment);
        यदि (आकार < 0) {
            err = आकार;
            गच्छ fail;
        }

        ffhwframesctx(ctx)->pool_आन्तरिकम् =
            av_बफर_pool_init2(आकार, ctx, cuda_pool_alloc, रिक्त);
        यदि (!ffhwframesctx(ctx)->pool_आन्तरिकम्) {
            err = AVERROR(ENOMEM);
            गच्छ fail;
        }
    }

    प्रत्यागम 0;

fail:
    cuda_चौकटाः_uninit(ctx);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क cuda_get_बफर(AVHWFramesContext *ctx, AVFrame *frame)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#यदि HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->आन्तरिकम्->cuda_dl;

    CUcontext dummy;
#यदि_अन्तः
    पूर्णाङ्क res;

    frame->buf[0] = av_बफर_pool_get(ctx->pool);
    यदि (!frame->buf[0])
        प्रत्यागम AVERROR(ENOMEM);

    यदि (ctx->format == AV_PIX_FMT_CUARRAY) {
#यदि HAVE_FFNVCODEC_CUARRAY
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)frame->buf[0]->दत्त;
        यदि (!desc) {
            frame->format = ctx->format;
            frame->विस्तारः  = ctx->विस्तारः;
            frame->height = ctx->height;
            प्रत्यागम 0;
        }
        frame->दत्त[0] = (uint8_t*)desc->array;
        frame->दत्त[1] = (uint8_t*)desc->सूचकांक;

        res = CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));
        यदि (res < 0)
            प्रत्यागम res;

        प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(frame->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            यदि (arr_plane_res == CUDA_ERROR_INVALID_मानम्) {
                यदि (i > 0)
                    भङ्ग;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                यदि (res < 0)
                    गच्छ fail;
            } अन्यथा यदि (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                गच्छ fail;
            } अन्यथा {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                यदि (res < 0)
                    गच्छ fail;
            }

            पूर्णाङ्क elem_आकार = ff_cuda_cuarray_elem_आकार(plane_desc.Format);
            यदि (elem_आकार <= 0) {
                res = AVERROR_BUG;
                गच्छ fail;
            }

            frame->linesize[i] = plane_desc.विस्तारः_2 * plane_desc.अङ्कः_Channels * elem_आकार;

            यदि (arr_plane_res == CUDA_ERROR_INVALID_मानम्)
                भङ्ग;
        }

        res = CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
        यदि (res < 0)
            प्रत्यागम res;
#अन्यथा
        प्रत्यागम AVERROR(ENOSYS);
#यदि_अन्तः
    } अन्यथा {
        res = av_image_fill_arrays(frame->दत्त, frame->linesize, frame->buf[0]->दत्त,
                                   ctx->sw_format, ctx->विस्तारः, ctx->height, priv->tex_alignment);
        यदि (res < 0)
            प्रत्यागम res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        यदि (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
            frame->दत्त[2]     = frame->दत्त[1];
            frame->दत्त[1]     = frame->दत्त[2] + frame->linesize[2] * AV_CEIL_RSHIFT(ctx->height, 1);
        }
    }

    frame->format = ctx->format;
    frame->विस्तारः  = ctx->विस्तारः;
    frame->height = ctx->height;

    प्रत्यागम 0;

#यदि HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
    प्रत्यागम res;
#यदि_अन्तः
}

स्थिर गणना AVPixelFormat cuda_frame_hw_format(ध्रुव AVFrame *frame)
{
    यदि (!frame->hw_चौकटाः_ctx)
        प्रत्यागम AV_PIX_FMT_NONE;
    प्रत्यागम ((AVHWFramesContext *)frame->hw_चौकटाः_ctx->दत्त)->format;
}

स्थिर पूर्णाङ्क cuda_transfer_get_formats(AVHWFramesContext *ctx,
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

स्थिर पूर्णाङ्क cuda_transfer_दत्त(AVHWFramesContext *ctx, AVFrame *dst,
                                 ध्रुव AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->आन्तरिकम्->cuda_dl;

    ध्रुव AVFrame *sw_frame = src->hw_चौकटाः_ctx ? dst : src;
    AVFrame *शिखरम्_अधस्तात् = रिक्त, *bottom_ऊर्ध्वम्_dst = रिक्त;
    CUcontext dummy;
    पूर्णाङ्क i, ret, copy_queued = 0, bottom_ऊर्ध्वम् = 0;

    {
        गणना AVPixelFormat src_fmt = cuda_frame_hw_format(src);
        गणना AVPixelFormat dst_fmt = cuda_frame_hw_format(dst);
        यदि ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            प्रत्यागम AVERROR(ENOSYS);
    }

    प्रति (i = 0; i < FF_ARRAY_ELEMS(sw_frame->linesize); i++)
        bottom_ऊर्ध्वम् |= sw_frame->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    यदि (bottom_ऊर्ध्वम्) {
        शिखरम्_अधस्तात् = av_frame_alloc();
        यदि (!शिखरम्_अधस्तात्)
            प्रत्यागम AVERROR(ENOMEM);
        शिखरम्_अधस्तात्->format = ctx->sw_format;
        शिखरम्_अधस्तात्->विस्तारः  = ctx->विस्तारः;
        शिखरम्_अधस्तात्->height = ctx->height;
        ret = av_hwframe_get_transfer_बफर((src->hw_चौकटाः_ctx ? src : dst)->hw_चौकटाः_ctx,
                                             शिखरम्_अधस्तात्);
        यदि (ret < 0)
            गच्छ free_शिखरम्_अधस्तात्;
        शिखरम्_अधस्तात्->विस्तारः  = src->विस्तारः;
        शिखरम्_अधस्तात्->height = src->height;
        यदि (sw_frame == src) {
            av_image_copy2(शिखरम्_अधस्तात्->दत्त, शिखरम्_अधस्तात्->linesize, src->दत्त, src->linesize,
                           ctx->sw_format, src->विस्तारः, src->height);
            src = शिखरम्_अधस्तात्;
        } अन्यथा {
            bottom_ऊर्ध्वम्_dst = dst;
            dst           = शिखरम्_अधस्तात्;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));
    यदि (ret < 0)
        गच्छ free_शिखरम्_अधस्तात्;

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
    प्रति (i = 0; i < FF_ARRAY_ELEMS(src->दत्त) && src->linesize[i]; i++) {
        पूर्णाङ्क src_is_nonplanar_cuarray = 0;
        पूर्णाङ्क dst_is_nonplanar_cuarray = 0;

        पूर्णाङ्क bytewidth = av_image_get_linesize(ctx->sw_format, src->विस्तारः, i);
        यदि (bytewidth < 0) {
            ret = bytewidth;
            गच्छ fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .विस्तारः_अन्तर्_अष्टकानि  = bytewidth,
            .Height        = AV_CEIL_RSHIFT(src->height, ((i == 0 || i == 3) ? 0 : priv->सरणम्_height)),
        };

        यदि (src->format == AV_PIX_FMT_CUDA) {
            cpy.src_स्मृतिः_Type = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->दत्त[i];
        } अन्यथा यदि (src->format == AV_PIX_FMT_CUARRAY) {
#यदि HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->दत्त[0], i);
            यदि (cures == CUDA_ERROR_INVALID_मानम् && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->दत्त[0];
                src_is_nonplanar_cuarray = 1;
            } अन्यथा यदि (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                गच्छ fail;
            }

            cpy.src_स्मृतिः_Type = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#अन्यथा
            ret = AVERROR(ENOSYS);
            गच्छ निर्गच्छ;
#यदि_अन्तः
        } अन्यथा {
            cpy.src_स्मृतिः_Type = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->दत्त[i];
        }

        यदि (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dst_स्मृतिः_Type = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->दत्त[i];
        } अन्यथा यदि (dst->format == AV_PIX_FMT_CUARRAY) {
#यदि HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->दत्त[0], i);
            यदि (cures == CUDA_ERROR_INVALID_मानम् && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->दत्त[0];
                dst_is_nonplanar_cuarray = 1;
            } अन्यथा यदि (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                गच्छ fail;
            }

            cpy.dst_स्मृतिः_Type = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#अन्यथा
            ret = AVERROR(ENOSYS);
            गच्छ निर्गच्छ;
#यदि_अन्तः
        } अन्यथा {
            cpy.dst_स्मृतिः_Type = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->दत्त[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->प्रवाहः));
        यदि (ret < 0)
            गच्छ fail;
        copy_queued = 1;

        यदि (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            भङ्ग;
    }

    /* The caller may reuse host memory once the transfer returns. */
    यदि (!src->hw_चौकटाः_ctx || !dst->hw_चौकटाः_ctx) {
        ret = CHECK_CU(cu->cu_प्रवाहः_Synchronize(hwctx->प्रवाहः));
        यदि (ret < 0)
            गच्छ निर्गच्छ;
    }

fail:
    यदि (ret < 0 && copy_queued)
        CHECK_CU(cu->cu_प्रवाहः_Synchronize(hwctx->प्रवाहः));
निर्गच्छ:
    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));

    यदि (bottom_ऊर्ध्वम्_dst && ret >= 0)
        av_image_copy2(bottom_ऊर्ध्वम्_dst->दत्त, bottom_ऊर्ध्वम्_dst->linesize,
                       शिखरम्_अधस्तात्->दत्त, शिखरम्_अधस्तात्->linesize,
                       ctx->sw_format, src->विस्तारः, src->height);
free_शिखरम्_अधस्तात्:
    av_frame_free(&शिखरम्_अधस्तात्);

    प्रत्यागम ret;
}

स्थिर शून्य cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    यदि (hwctx->p.आन्तरिकम्) {
        CudaFunctions *cu = hwctx->आन्तरिकम्.cuda_dl;

        यदि (hwctx->आन्तरिकम्.is_allocated && hwctx->p.cuda_ctx) {
            यदि (hwctx->आन्तरिकम्.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->आन्तरिकम्.cuda_device));
            अन्यथा यदि (!(hwctx->आन्तरिकम्.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = रिक्त;
        }

        cuda_free_functions(&hwctx->आन्तरिकम्.cuda_dl);
        स्मृतिं_पूरय(&hwctx->आन्तरिकम्, 0, परिमाण(hwctx->आन्तरिकम्));
        hwctx->p.आन्तरिकम् = रिक्त;
    }
}

स्थिर पूर्णाङ्क cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    पूर्णाङ्क ret;

    hwctx->p.आन्तरिकम् = &hwctx->आन्तरिकम्;

    यदि (!hwctx->आन्तरिकम्.cuda_dl) {
        ret = cuda_आरोपय_functions(&hwctx->आन्तरिकम्.cuda_dl, ctx);
        यदि (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            गच्छ error;
        }
    }

    प्रत्यागम 0;

error:
    cuda_device_uninit(ctx);
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क cuda_context_init(AVHWDeviceContext *device_ctx, पूर्णाङ्क flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    पूर्णाङ्क ret, dev_सक्रिय = 0;
    अचिह्नित पूर्णाङ्क dev_flags = 0;

    ध्रुव अचिह्नित पूर्णाङ्क desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->आन्तरिकम्->cuda_dl;

    hwctx->आन्तरिकम्->flags = flags;

    यदि (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->आन्तरिकम्->cuda_device,
                       &dev_flags, &dev_सक्रिय));
        यदि (ret < 0)
            प्रत्यागम ret;

        यदि (dev_सक्रिय && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            प्रत्यागम AVERROR(ENOTSUP);
        } अन्यथा यदि (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cu_Device_Primary_Ctx_समुच्चयः_Flags(hwctx->आन्तरिकम्->cuda_device,
                           desired_flags));
            यदि (ret < 0)
                प्रत्यागम ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->आन्तरिकम्->cuda_device));
        यदि (ret < 0)
            प्रत्यागम ret;
    } अन्यथा यदि (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        यदि (ret < 0)
            प्रत्यागम ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } अन्यथा {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->आन्तरिकम्->cuda_device));
        यदि (ret < 0)
            प्रत्यागम ret;

        CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
    }

    hwctx->आन्तरिकम्->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->प्रवाहः = रिक्त;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, पूर्णाङ्क *flags)
{
    AVDictionary_प्रविष्टिः *primary_ctx_opt = av_dict_get(opts, "primary_ctx", रिक्त, 0);
    AVDictionary_प्रविष्टिः *current_ctx_opt = av_dict_get(opts, "current_ctx", रिक्त, 0);

    पूर्णाङ्क use_primary_ctx = 0, use_current_ctx = 0;
    यदि (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->मानम्, रिक्त, 10);

    यदि (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->मानम्, रिक्त, 10);

    यदि (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    यदि (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } अन्यथा यदि (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    यदि (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } अन्यथा यदि (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क cuda_device_create(AVHWDeviceContext *device_ctx,
                              ध्रुव वर्ण *device,
                              AVDictionary *opts, पूर्णाङ्क flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    पूर्णाङ्क ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    यदि (ret < 0)
        गच्छ error;

    यदि (device)
        device_idx = strtol(device, रिक्त, 0);

    ret = cuda_device_init(device_ctx);
    यदि (ret < 0)
        गच्छ error;

    cu = hwctx->आन्तरिकम्->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    यदि (ret < 0)
        गच्छ error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->आन्तरिकम्->cuda_device, device_idx));
    यदि (ret < 0)
        गच्छ error;

    ret = cuda_context_init(device_ctx, flags);
    यदि (ret < 0)
        गच्छ error;

    प्रत्यागम 0;

error:
    cuda_device_uninit(device_ctx);
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              पूर्णाङ्क flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ध्रुव वर्ण *src_uuid = रिक्त;
#यदि CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#यदि_अन्तः
    पूर्णाङ्क ret, i, device_गणनम्;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    यदि (ret < 0)
        गच्छ error;

#यदि CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#यदि_अन्तः

    विकल्प (src_ctx->type) {
#यदि CONFIG_VULKAN
#परिभाषय TYPE PFN_vkGetPhysicalDeviceProperties2
    पक्ष AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .p_अग्र = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        भङ्ग;
    }
#अपरिभाषय TYPE
#यदि_अन्तः
    स्वभाव:
        ret = AVERROR(ENOSYS);
        गच्छ error;
    }

    यदि (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        गच्छ error;
    }

    ret = cuda_device_init(device_ctx);
    यदि (ret < 0)
        गच्छ error;

    cu = hwctx->आन्तरिकम्->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    यदि (ret < 0)
        गच्छ error;

    ret = CHECK_CU(cu->cu_Device_Get_गणनम्(&device_गणनम्));
    यदि (ret < 0)
        गच्छ error;

    hwctx->आन्तरिकम्->cuda_device = -1;
    प्रति (i = 0; i < device_गणनम्; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        यदि (ret < 0)
            गच्छ error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        यदि (ret < 0)
            गच्छ error;

        यदि (memcmp(src_uuid, uuid.अष्टकानि, परिमाण (uuid.अष्टकानि)) == 0) {
            hwctx->आन्तरिकम्->cuda_device = dev;
            भङ्ग;
        }
    }

    यदि (hwctx->आन्तरिकम्->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        गच्छ error;
    }

    ret = cuda_context_init(device_ctx, flags);
    यदि (ret < 0)
        गच्छ error;

    प्रत्यागम 0;

error:
    cuda_device_uninit(device_ctx);
    प्रत्यागम ret;
}

ध्रुव HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_आकार    = परिमाण(CUDADeviceContext),
    .चौकटाः_hwctx_आकार    = परिमाण(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .चौकटाः_get_constraints = cuda_चौकटाः_get_constraints,
    .चौकटाः_init          = cuda_चौकटाः_init,
    .चौकटाः_uninit        = cuda_चौकटाः_uninit,
    .चौकटाः_get_बफर    = cuda_get_बफर,
    .transfer_get_formats = cuda_transfer_get_formats,
#यदि HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_बफर_alloc = cuda_transfer_बफर_alloc,
#यदि_अन्तः
    .transfer_दत्त_गन्तव्यम्     = cuda_transfer_दत्त,
    .transfer_दत्त_from   = cuda_transfer_दत्त,

    .pix_fmts             = (ध्रुव गणना AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#यदि HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#यदि_अन्तः
                                                          AV_PIX_FMT_NONE },
};
