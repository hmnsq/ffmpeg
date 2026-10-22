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
#जइ CONFIG_VULKAN
#अन्तर्भाव "hwcontext_vulkan.h"
#endif
#अन्तर्भाव "cuda_check.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "imgutils.h"

प्रकारनिर्देश संरचना CUDAFramesContext {
    AVCUDAFramesContext p;

    पूर्णाङ्क shift_width, shift_height;
    पूर्णाङ्क tex_alignment;

    पूर्णाङ्क cuarray_अङ्कः_surfaces_used;
} CUDAFramesContext;

प्रकारनिर्देश संरचना CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADeviceContextInternal internal;
} CUDADeviceContext;



#define CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

स्थिर CUarray_format cuda_array_format_for_pix_fmt(गणना AVPixelFormat fmt);

स्थिर पूर्णाङ्क cuda_frames_get_constraints(AVHWDeviceContext *ctx,
                                       ध्रुव शून्य *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ध्रुव AVCUDAHWConfig *config = hwconfig;
    गणना AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    पूर्णाङ्क n = 0;

    जइ (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, परिमाण(*constraints->valid_hw_formats));
        जइ (!constraints->valid_hw_formats)
            प्रत्यागम AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } अण्णहा {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, परिमाण(*constraints->valid_hw_formats));
        जइ (!constraints->valid_hw_formats)
            प्रत्यागम AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#जइ HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#अण्णहा
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#endif
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    परिमाण(*constraints->valid_sw_formats));
    जइ (!constraints->valid_sw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    n = 0;
    प्रति (पूर्णाङ्क i = 0; i < AV_PIX_FMT_NB; i++) {
        जइ (req_fmt == AV_PIX_FMT_CUARRAY) {
            जइ (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } अण्णहा {
            ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            जइ (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#जइ CONFIG_VULKAN
    जइ (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#endif
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    प्रत्यागम 0;
}

स्थिर शून्य cuda_buffer_free(शून्य *opaque, uint8_t *data)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));

    जइ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)data;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } अण्णहा {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)data));
    }

    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
}

स्थिर AVBufferRef *cuda_pool_alloc(शून्य *opaque, size_t size)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    AVBufferRef *ret = रिक्त;
    CUcontext dummy = रिक्त;
    CUdeviceptr data;
    पूर्णाङ्क err;

    err = CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));
    जइ (err < 0)
        प्रत्यागम रिक्त;

    जइ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = av_mallocz(परिमाण(*desc));
        जइ (!desc)
            गच्छ done;

        जइ (priv->p.cuarray_अङ्कः_surfaces > 0) {
            जइ (priv->cuarray_अङ्कः_surfaces_used >= priv->p.cuarray_अङ्कः_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                गच्छ done;
            }
            desc->index = priv->cuarray_अङ्कः_surfaces_used++;
            desc->array = priv->p.cuarray_surfaces[desc->index];
        } अण्णहा {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            जइ (err < 0) {
                av_free(desc);
                गच्छ done;
            }
        }

        ret = av_buffer_create((uint8_t*)desc, परिमाण(*desc), cuda_buffer_free, ctx, 0);
        जइ (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            गच्छ done;
        }

        गच्छ done;
    }

    err = CHECK_CU(cu->cuMemAlloc(&data, size));
    जइ (err < 0)
        गच्छ done;

    ret = av_buffer_create((uint8_t*)data, size, cuda_buffer_free, ctx, 0);
    जइ (!ret) {
        CHECK_CU(cu->cuMemFree(data));
        गच्छ done;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
done:
    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
    प्रत्यागम ret;
}

#जइ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
स्थिर शून्य cuda_transfer_buffer_free(शून्य *opaque, uint8_t *data)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(data));
    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
स्थिर AVBufferRef *cuda_transfer_buffer_alloc(शून्य *device_ref, size_t size)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->data;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    AVBufferRef *ret = रिक्त;
    CUcontext dummy;
    शून्य *host;

    जइ (CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx)) < 0)
        प्रत्यागम av_buffer_alloc(size);

    जइ (CHECK_CU(cu->cuMemHostAlloc(&host, size, 0)) >= 0) {
        ret = av_buffer_create(host, size, cuda_transfer_buffer_free, device_ctx, 0);
        जइ (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
    प्रत्यागम ret ? ret : av_buffer_alloc(size);
}
#endif

स्थिर शून्य cuda_frames_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    जइ (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        प्रति (पूर्णाङ्क i = priv->cuarray_अङ्कः_surfaces_used; i < priv->p.cuarray_अङ्कः_surfaces; i++)
            जइ (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_अङ्कः_surfaces = 0;
    }
}

स्थिर CUarray_format cuda_array_format_for_pix_fmt(गणना AVPixelFormat fmt)
{
    विकल्प (fmt) {
#जइ HAVE_FFNVCODEC_CUARRAY
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
#endif
    स्वभाव:                   प्रत्यागम 0;
    }
}

#जइ HAVE_FFNVCODEC_CUARRAY
स्थिर unsigned पूर्णाङ्क cuda_array_numchannels_for_pix_fmt(गणना AVPixelFormat fmt)
{
    विकल्प (fmt) {
    पक्ष AV_PIX_FMT_0RGB32:
    पक्ष AV_PIX_FMT_0BGR32:
    पक्ष AV_PIX_FMT_RGB32:
    पक्ष AV_PIX_FMT_BGR32:     प्रत्यागम 4;
    स्वभाव:                   प्रत्यागम 3;
    }
}
#endif

स्थिर पूर्णाङ्क cuda_frames_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    पूर्णाङ्क err;

    जइ (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    जइ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        प्रत्यागम AVERROR(ENOSYS);
    }

#जइ HAVE_FFNVCODEC_CUARRAY
    जइ (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        प्रत्यागम AVERROR(ENOSYS);
    }
#अण्णहा
    जइ (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        प्रत्यागम AVERROR(ENOSYS);
    }
#endif

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->internal->cuda_device));
    जइ (err < 0)
        प्रत्यागम err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    जइ (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->shift_width, &priv->shift_height);

#जइ HAVE_FFNVCODEC_CUARRAY
    जइ (ctx->format == AV_PIX_FMT_CUARRAY) {
        जइ (!priv->p.cuarray_desc.Width)
            priv->p.cuarray_desc.Width = ctx->width;
        जइ (!priv->p.cuarray_desc.Height)
            priv->p.cuarray_desc.Height = ctx->height;
        जइ (!priv->p.cuarray_desc.अङ्कः_Channels)
            priv->p.cuarray_desc.अङ्कः_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        जइ (priv->p.cuarray_desc.Depth) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            प्रत्यागम AVERROR(EINVAL);
        }

        जइ (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        जइ (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            प्रत्यागम AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    जइ (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_अङ्कः_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_अङ्कः_surfaces, परिमाण(*priv->p.cuarray_surfaces));
        जइ (!priv->p.cuarray_surfaces)
            प्रत्यागम AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));
        जइ (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            प्रत्यागम err;
        }

        प्रति (पूर्णाङ्क i = 0; i < priv->p.cuarray_अङ्कः_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            जइ (err < 0) {
                प्रति (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                प्रत्यागम err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
        जइ (err < 0)
            गच्छ fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_अङ्कः_surfaces, priv->p.cuarray_desc.Width, priv->p.cuarray_desc.Height);
    }
#endif

    जइ (!ctx->pool) {
        पूर्णाङ्क size = av_image_get_buffer_size(ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        जइ (size < 0) {
            err = size;
            गच्छ fail;
        }

        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(size, ctx, cuda_pool_alloc, रिक्त);
        जइ (!ffhwframesctx(ctx)->pool_internal) {
            err = AVERROR(ENOMEM);
            गच्छ fail;
        }
    }

    प्रत्यागम 0;

fail:
    cuda_frames_uninit(ctx);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क cuda_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#जइ HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;
#endif
    पूर्णाङ्क res;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    जइ (!frame->buf[0])
        प्रत्यागम AVERROR(ENOMEM);

    जइ (ctx->format == AV_PIX_FMT_CUARRAY) {
#जइ HAVE_FFNVCODEC_CUARRAY
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)frame->buf[0]->data;
        जइ (!desc) {
            frame->format = ctx->format;
            frame->width  = ctx->width;
            frame->height = ctx->height;
            प्रत्यागम 0;
        }
        frame->data[0] = (uint8_t*)desc->array;
        frame->data[1] = (uint8_t*)desc->index;

        res = CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));
        जइ (res < 0)
            प्रत्यागम res;

        प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(frame->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            जइ (arr_plane_res == CUDA_ERROR_INVALID_मानम्) {
                जइ (i > 0)
                    भङ्ग;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                जइ (res < 0)
                    गच्छ fail;
            } अण्णहा जइ (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                गच्छ fail;
            } अण्णहा {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                जइ (res < 0)
                    गच्छ fail;
            }

            पूर्णाङ्क elem_size = ff_cuda_cuarray_elem_size(plane_desc.Format);
            जइ (elem_size <= 0) {
                res = AVERROR_BUG;
                गच्छ fail;
            }

            frame->linesize[i] = plane_desc.Width * plane_desc.अङ्कः_Channels * elem_size;

            जइ (arr_plane_res == CUDA_ERROR_INVALID_मानम्)
                भङ्ग;
        }

        res = CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
        जइ (res < 0)
            प्रत्यागम res;
#अण्णहा
        प्रत्यागम AVERROR(ENOSYS);
#endif
    } अण्णहा {
        res = av_image_fill_arrays(frame->data, frame->linesize, frame->buf[0]->data,
                                   ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        जइ (res < 0)
            प्रत्यागम res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        जइ (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
            frame->data[2]     = frame->data[1];
            frame->data[1]     = frame->data[2] + frame->linesize[2] * AV_CEIL_RSHIFT(ctx->height, 1);
        }
    }

    frame->format = ctx->format;
    frame->width  = ctx->width;
    frame->height = ctx->height;

    प्रत्यागम 0;

#जइ HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
    प्रत्यागम res;
#endif
}

स्थिर गणना AVPixelFormat cuda_frame_hw_format(ध्रुव AVFrame *frame)
{
    जइ (!frame->hw_frames_ctx)
        प्रत्यागम AV_PIX_FMT_NONE;
    प्रत्यागम ((AVHWFramesContext *)frame->hw_frames_ctx->data)->format;
}

स्थिर पूर्णाङ्क cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     गणना AVHWFrameTransferDirection dir,
                                     गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts;

    fmts = av_malloc_array(2, परिमाण(*fmts));
    जइ (!fmts)
        प्रत्यागम AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क cuda_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 ध्रुव AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    ध्रुव AVFrame *sw_frame = src->hw_frames_ctx ? dst : src;
    AVFrame *शिखरम्_down = रिक्त, *bottom_up_dst = रिक्त;
    CUcontext dummy;
    पूर्णाङ्क i, ret, copy_queued = 0, bottom_up = 0;

    {
        गणना AVPixelFormat src_fmt = cuda_frame_hw_format(src);
        गणना AVPixelFormat dst_fmt = cuda_frame_hw_format(dst);
        जइ ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            प्रत्यागम AVERROR(ENOSYS);
    }

    प्रति (i = 0; i < FF_ARRAY_ELEMS(sw_frame->linesize); i++)
        bottom_up |= sw_frame->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    जइ (bottom_up) {
        शिखरम्_down = av_frame_alloc();
        जइ (!शिखरम्_down)
            प्रत्यागम AVERROR(ENOMEM);
        शिखरम्_down->format = ctx->sw_format;
        शिखरम्_down->width  = ctx->width;
        शिखरम्_down->height = ctx->height;
        ret = av_hwframe_get_transfer_buffer((src->hw_frames_ctx ? src : dst)->hw_frames_ctx,
                                             शिखरम्_down);
        जइ (ret < 0)
            गच्छ free_शिखरम्_down;
        शिखरम्_down->width  = src->width;
        शिखरम्_down->height = src->height;
        जइ (sw_frame == src) {
            av_image_copy2(शिखरम्_down->data, शिखरम्_down->linesize, src->data, src->linesize,
                           ctx->sw_format, src->width, src->height);
            src = शिखरम्_down;
        } अण्णहा {
            bottom_up_dst = dst;
            dst           = शिखरम्_down;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_प्रक्षिप_Current(hwctx->cuda_ctx));
    जइ (ret < 0)
        गच्छ free_शिखरम्_down;

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
    प्रति (i = 0; i < FF_ARRAY_ELEMS(src->data) && src->linesize[i]; i++) {
        पूर्णाङ्क src_is_nonplanar_cuarray = 0;
        पूर्णाङ्क dst_is_nonplanar_cuarray = 0;

        पूर्णाङ्क bytewidth = av_image_get_linesize(ctx->sw_format, src->width, i);
        जइ (bytewidth < 0) {
            ret = bytewidth;
            गच्छ fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .WidthInBytes  = bytewidth,
            .Height        = AV_CEIL_RSHIFT(src->height, ((i == 0 || i == 3) ? 0 : priv->shift_height)),
        };

        जइ (src->format == AV_PIX_FMT_CUDA) {
            cpy.srcMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->data[i];
        } अण्णहा जइ (src->format == AV_PIX_FMT_CUARRAY) {
#जइ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->data[0], i);
            जइ (cures == CUDA_ERROR_INVALID_मानम् && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->data[0];
                src_is_nonplanar_cuarray = 1;
            } अण्णहा जइ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                गच्छ fail;
            }

            cpy.srcMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#अण्णहा
            ret = AVERROR(ENOSYS);
            गच्छ exit;
#endif
        } अण्णहा {
            cpy.srcMemoryType = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->data[i];
        }

        जइ (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dstMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->data[i];
        } अण्णहा जइ (dst->format == AV_PIX_FMT_CUARRAY) {
#जइ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->data[0], i);
            जइ (cures == CUDA_ERROR_INVALID_मानम् && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->data[0];
                dst_is_nonplanar_cuarray = 1;
            } अण्णहा जइ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                गच्छ fail;
            }

            cpy.dstMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#अण्णहा
            ret = AVERROR(ENOSYS);
            गच्छ exit;
#endif
        } अण्णहा {
            cpy.dstMemoryType = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->data[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->stream));
        जइ (ret < 0)
            गच्छ fail;
        copy_queued = 1;

        जइ (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            भङ्ग;
    }

    /* The caller may reuse host memory once the transfer returns. */
    जइ (!src->hw_frames_ctx || !dst->hw_frames_ctx) {
        ret = CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
        जइ (ret < 0)
            गच्छ exit;
    }

fail:
    जइ (ret < 0 && copy_queued)
        CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
exit:
    CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));

    जइ (bottom_up_dst && ret >= 0)
        av_image_copy2(bottom_up_dst->data, bottom_up_dst->linesize,
                       शिखरम्_down->data, शिखरम्_down->linesize,
                       ctx->sw_format, src->width, src->height);
free_शिखरम्_down:
    av_frame_free(&शिखरम्_down);

    प्रत्यागम ret;
}

स्थिर शून्य cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    जइ (hwctx->p.internal) {
        CudaFunctions *cu = hwctx->internal.cuda_dl;

        जइ (hwctx->internal.is_allocated && hwctx->p.cuda_ctx) {
            जइ (hwctx->internal.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->internal.cuda_device));
            अण्णहा जइ (!(hwctx->internal.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = रिक्त;
        }

        cuda_free_functions(&hwctx->internal.cuda_dl);
        memset(&hwctx->internal, 0, परिमाण(hwctx->internal));
        hwctx->p.internal = रिक्त;
    }
}

स्थिर पूर्णाङ्क cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    पूर्णाङ्क ret;

    hwctx->p.internal = &hwctx->internal;

    जइ (!hwctx->internal.cuda_dl) {
        ret = cuda_load_functions(&hwctx->internal.cuda_dl, ctx);
        जइ (ret < 0) {
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
    पूर्णाङ्क ret, dev_active = 0;
    unsigned पूर्णाङ्क dev_flags = 0;

    ध्रुव unsigned पूर्णाङ्क desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->internal->cuda_dl;

    hwctx->internal->flags = flags;

    जइ (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->internal->cuda_device,
                       &dev_flags, &dev_active));
        जइ (ret < 0)
            प्रत्यागम ret;

        जइ (dev_active && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            प्रत्यागम AVERROR(ENOTSUP);
        } अण्णहा जइ (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cuDevicePrimaryCtxSetFlags(hwctx->internal->cuda_device,
                           desired_flags));
            जइ (ret < 0)
                प्रत्यागम ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->internal->cuda_device));
        जइ (ret < 0)
            प्रत्यागम ret;
    } अण्णहा जइ (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        जइ (ret < 0)
            प्रत्यागम ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } अण्णहा {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->internal->cuda_device));
        जइ (ret < 0)
            प्रत्यागम ret;

        CHECK_CU(cu->cu_Ctx_निष्कासय_Current(&dummy));
    }

    hwctx->internal->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->stream = रिक्त;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, पूर्णाङ्क *flags)
{
    AVDictionaryEntry *primary_ctx_opt = av_dict_get(opts, "primary_ctx", रिक्त, 0);
    AVDictionaryEntry *current_ctx_opt = av_dict_get(opts, "current_ctx", रिक्त, 0);

    पूर्णाङ्क use_primary_ctx = 0, use_current_ctx = 0;
    जइ (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->मानम्, रिक्त, 10);

    जइ (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->मानम्, रिक्त, 10);

    जइ (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    जइ (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } अण्णहा जइ (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    जइ (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } अण्णहा जइ (current_ctx_opt) {
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
    जइ (ret < 0)
        गच्छ error;

    जइ (device)
        device_idx = strtol(device, रिक्त, 0);

    ret = cuda_device_init(device_ctx);
    जइ (ret < 0)
        गच्छ error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    जइ (ret < 0)
        गच्छ error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->internal->cuda_device, device_idx));
    जइ (ret < 0)
        गच्छ error;

    ret = cuda_context_init(device_ctx, flags);
    जइ (ret < 0)
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
#जइ CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#endif
    पूर्णाङ्क ret, i, device_गणनम्;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    जइ (ret < 0)
        गच्छ error;

#जइ CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#endif

    विकल्प (src_ctx->type) {
#जइ CONFIG_VULKAN
#define TYPE PFN_vkGetPhysicalDeviceProperties2
    पक्ष AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .pNext = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        भङ्ग;
    }
#undef TYPE
#endif
    स्वभाव:
        ret = AVERROR(ENOSYS);
        गच्छ error;
    }

    जइ (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        गच्छ error;
    }

    ret = cuda_device_init(device_ctx);
    जइ (ret < 0)
        गच्छ error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    जइ (ret < 0)
        गच्छ error;

    ret = CHECK_CU(cu->cu_Device_Get_गणनम्(&device_गणनम्));
    जइ (ret < 0)
        गच्छ error;

    hwctx->internal->cuda_device = -1;
    प्रति (i = 0; i < device_गणनम्; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        जइ (ret < 0)
            गच्छ error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        जइ (ret < 0)
            गच्छ error;

        जइ (memcmp(src_uuid, uuid.bytes, परिमाण (uuid.bytes)) == 0) {
            hwctx->internal->cuda_device = dev;
            भङ्ग;
        }
    }

    जइ (hwctx->internal->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        गच्छ error;
    }

    ret = cuda_context_init(device_ctx, flags);
    जइ (ret < 0)
        गच्छ error;

    प्रत्यागम 0;

error:
    cuda_device_uninit(device_ctx);
    प्रत्यागम ret;
}

ध्रुव HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_size    = परिमाण(CUDADeviceContext),
    .frames_hwctx_size    = परिमाण(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .frames_get_constraints = cuda_frames_get_constraints,
    .frames_init          = cuda_frames_init,
    .frames_uninit        = cuda_frames_uninit,
    .frames_get_buffer    = cuda_get_buffer,
    .transfer_get_formats = cuda_transfer_get_formats,
#जइ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_buffer_alloc = cuda_transfer_buffer_alloc,
#endif
    .transfer_data_to     = cuda_transfer_data,
    .transfer_data_from   = cuda_transfer_data,

    .pix_fmts             = (ध्रुव गणना AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#जइ HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#endif
                                                          AV_PIX_FMT_NONE },
};
