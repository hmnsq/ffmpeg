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

#समावेश "buffer.h"
#समावेश "common.h"
#समावेश "hwcontext.h"
#समावेश "hwcontext_internal.h"
#समावेश "hwcontext_cuda_internal.h"
#अगर CONFIG_VULKAN
#समावेश "hwcontext_vulkan.h"
#पूर्ण_अगर
#समावेश "cuda_check.h"
#समावेश "mem.h"
#समावेश "pixdesc.h"
#समावेश "pixfmt.h"
#समावेश "imgutils.h"

प्रकार काष्ठा CUDAFramesContext {
    AVCUDAFramesContext p;

    पूर्णांक shift_width, shift_height;
    पूर्णांक tex_alignment;

    पूर्णांक cuarray_अंक_surfaces_used;
} CUDAFramesContext;

प्रकार काष्ठा CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADeviceContextInternal internal;
} CUDADeviceContext;



#घोषणा CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

अटल CUarray_format cuda_array_format_for_pix_fmt(क्रमागत AVPixelFormat fmt);

अटल पूर्णांक cuda_frames_get_constraints(AVHWDeviceContext *ctx,
                                       स्थिर व्योम *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    स्थिर AVCUDAHWConfig *config = hwconfig;
    क्रमागत AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    पूर्णांक n = 0;

    अगर (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, माप(*constraints->valid_hw_formats));
        अगर (!constraints->valid_hw_formats)
            वापस AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } अन्यथा {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, माप(*constraints->valid_hw_formats));
        अगर (!constraints->valid_hw_formats)
            वापस AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#अगर HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#अन्यथा
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#पूर्ण_अगर
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    माप(*constraints->valid_sw_formats));
    अगर (!constraints->valid_sw_formats)
        वापस AVERROR(ENOMEM);

    n = 0;
    क्रम (पूर्णांक i = 0; i < AV_PIX_FMT_NB; i++) {
        अगर (req_fmt == AV_PIX_FMT_CUARRAY) {
            अगर (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } अन्यथा {
            स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            अगर (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#अगर CONFIG_VULKAN
    अगर (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#पूर्ण_अगर
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    वापस 0;
}

अटल व्योम cuda_बफर_free(व्योम *opaque, uint8_t *तथ्य)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_धकेलो_Current(hwctx->cuda_ctx));

    अगर (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)तथ्य;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } अन्यथा {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)तथ्य));
    }

    CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));
}

अटल AVBufferRef *cuda_pool_alloc(व्योम *opaque, माप_प्रकार आकार)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    AVBufferRef *ret = शून्य;
    CUcontext dummy = शून्य;
    CUdeviceptr तथ्य;
    पूर्णांक err;

    err = CHECK_CU(cu->cu_Ctx_धकेलो_Current(hwctx->cuda_ctx));
    अगर (err < 0)
        वापस शून्य;

    अगर (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = av_mallocz(माप(*desc));
        अगर (!desc)
            जाओ done;

        अगर (priv->p.cuarray_अंक_surfaces > 0) {
            अगर (priv->cuarray_अंक_surfaces_used >= priv->p.cuarray_अंक_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                जाओ done;
            }
            desc->सूचकांक = priv->cuarray_अंक_surfaces_used++;
            desc->array = priv->p.cuarray_surfaces[desc->सूचकांक];
        } अन्यथा {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            अगर (err < 0) {
                av_free(desc);
                जाओ done;
            }
        }

        ret = av_बफर_create((uint8_t*)desc, माप(*desc), cuda_बफर_free, ctx, 0);
        अगर (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            जाओ done;
        }

        जाओ done;
    }

    err = CHECK_CU(cu->cuMemAlloc(&तथ्य, आकार));
    अगर (err < 0)
        जाओ done;

    ret = av_बफर_create((uint8_t*)तथ्य, आकार, cuda_बफर_free, ctx, 0);
    अगर (!ret) {
        CHECK_CU(cu->cuMemFree(तथ्य));
        जाओ done;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
done:
    CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));
    वापस ret;
}

#अगर HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
अटल व्योम cuda_transfer_बफर_free(व्योम *opaque, uint8_t *तथ्य)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_धकेलो_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(तथ्य));
    CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
अटल AVBufferRef *cuda_transfer_बफर_alloc(व्योम *device_ref, माप_प्रकार आकार)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->तथ्य;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    AVBufferRef *ret = शून्य;
    CUcontext dummy;
    व्योम *host;

    अगर (CHECK_CU(cu->cu_Ctx_धकेलो_Current(hwctx->cuda_ctx)) < 0)
        वापस av_बफर_alloc(आकार);

    अगर (CHECK_CU(cu->cuMemHostAlloc(&host, आकार, 0)) >= 0) {
        ret = av_बफर_create(host, आकार, cuda_transfer_बफर_free, device_ctx, 0);
        अगर (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));
    वापस ret ? ret : av_बफर_alloc(आकार);
}
#पूर्ण_अगर

अटल व्योम cuda_frames_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    अगर (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_धकेलो_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        क्रम (पूर्णांक i = priv->cuarray_अंक_surfaces_used; i < priv->p.cuarray_अंक_surfaces; i++)
            अगर (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_अंक_surfaces = 0;
    }
}

अटल CUarray_format cuda_array_format_for_pix_fmt(क्रमागत AVPixelFormat fmt)
{
    चयन (fmt) {
#अगर HAVE_FFNVCODEC_CUARRAY
    हाल AV_PIX_FMT_NV12:      वापस CU_AD_FORMAT_NV12;
    हाल AV_PIX_FMT_P010:
    हाल AV_PIX_FMT_P012:
    हाल AV_PIX_FMT_P016:      वापस CU_AD_FORMAT_P016;
    हाल AV_PIX_FMT_NV16:      वापस CU_AD_FORMAT_NV16;
    हाल AV_PIX_FMT_P210:
    हाल AV_PIX_FMT_P212:
    हाल AV_PIX_FMT_P216:      वापस CU_AD_FORMAT_P216;
    हाल AV_PIX_FMT_NV24:      वापस CU_AD_FORMAT_YUV444_8BIT_SEMIPLANAR;
    हाल AV_PIX_FMT_P410:
    हाल AV_PIX_FMT_P412:
    हाल AV_PIX_FMT_P416:      वापस CU_AD_FORMAT_YUV444_16BIT_SEMIPLANAR;
    हाल AV_PIX_FMT_YUV420P:   वापस CU_AD_FORMAT_UINT8_PLANAR_420;
    हाल AV_PIX_FMT_YUV422P:   वापस CU_AD_FORMAT_UINT8_PLANAR_422;
    हाल AV_PIX_FMT_YUV444P:   वापस CU_AD_FORMAT_UINT8_PLANAR_444;
    हाल AV_PIX_FMT_YUV420P10: वापस CU_AD_FORMAT_UINT16_PLANAR_420;
    हाल AV_PIX_FMT_YUV422P10: वापस CU_AD_FORMAT_UINT16_PLANAR_422;
    हाल AV_PIX_FMT_YUV444P10:
    हाल AV_PIX_FMT_YUV444P10MSB:
    हाल AV_PIX_FMT_YUV444P12MSB:
    हाल AV_PIX_FMT_YUV444P16: वापस CU_AD_FORMAT_UINT16_PLANAR_444;
    हाल AV_PIX_FMT_0RGB32:
    हाल AV_PIX_FMT_0BGR32:
    हाल AV_PIX_FMT_RGB32:
    हाल AV_PIX_FMT_BGR32:     वापस CU_AD_FORMAT_UNSIGNED_INT8;
#पूर्ण_अगर
    शेष:                   वापस 0;
    }
}

#अगर HAVE_FFNVCODEC_CUARRAY
अटल अचिन्हित पूर्णांक cuda_array_numchannels_for_pix_fmt(क्रमागत AVPixelFormat fmt)
{
    चयन (fmt) {
    हाल AV_PIX_FMT_0RGB32:
    हाल AV_PIX_FMT_0BGR32:
    हाल AV_PIX_FMT_RGB32:
    हाल AV_PIX_FMT_BGR32:     वापस 4;
    शेष:                   वापस 3;
    }
}
#पूर्ण_अगर

अटल पूर्णांक cuda_frames_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    पूर्णांक err;

    अगर (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        वापस AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    अगर (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        वापस AVERROR(ENOSYS);
    }

#अगर HAVE_FFNVCODEC_CUARRAY
    अगर (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        वापस AVERROR(ENOSYS);
    }
#अन्यथा
    अगर (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        वापस AVERROR(ENOSYS);
    }
#पूर्ण_अगर

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->internal->cuda_device));
    अगर (err < 0)
        वापस err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    अगर (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->shift_width, &priv->shift_height);

#अगर HAVE_FFNVCODEC_CUARRAY
    अगर (ctx->format == AV_PIX_FMT_CUARRAY) {
        अगर (!priv->p.cuarray_desc.Width)
            priv->p.cuarray_desc.Width = ctx->width;
        अगर (!priv->p.cuarray_desc.Height)
            priv->p.cuarray_desc.Height = ctx->height;
        अगर (!priv->p.cuarray_desc.अंक_Channels)
            priv->p.cuarray_desc.अंक_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        अगर (priv->p.cuarray_desc.Depth) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            वापस AVERROR(EINVAL);
        }

        अगर (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        अगर (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            वापस AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    अगर (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_अंक_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_अंक_surfaces, माप(*priv->p.cuarray_surfaces));
        अगर (!priv->p.cuarray_surfaces)
            वापस AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_धकेलो_Current(hwctx->cuda_ctx));
        अगर (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            वापस err;
        }

        क्रम (पूर्णांक i = 0; i < priv->p.cuarray_अंक_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            अगर (err < 0) {
                क्रम (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                वापस err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));
        अगर (err < 0)
            जाओ fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_अंक_surfaces, priv->p.cuarray_desc.Width, priv->p.cuarray_desc.Height);
    }
#पूर्ण_अगर

    अगर (!ctx->pool) {
        पूर्णांक आकार = av_image_get_बफर_आकार(ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        अगर (आकार < 0) {
            err = आकार;
            जाओ fail;
        }

        ffhwframesctx(ctx)->pool_internal =
            av_बफर_pool_init2(आकार, ctx, cuda_pool_alloc, शून्य);
        अगर (!ffhwframesctx(ctx)->pool_internal) {
            err = AVERROR(ENOMEM);
            जाओ fail;
        }
    }

    वापस 0;

fail:
    cuda_frames_uninit(ctx);
    वापस err;
}

अटल पूर्णांक cuda_get_बफर(AVHWFramesContext *ctx, AVFrame *frame)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#अगर HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;
#पूर्ण_अगर
    पूर्णांक res;

    frame->buf[0] = av_बफर_pool_get(ctx->pool);
    अगर (!frame->buf[0])
        वापस AVERROR(ENOMEM);

    अगर (ctx->format == AV_PIX_FMT_CUARRAY) {
#अगर HAVE_FFNVCODEC_CUARRAY
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)frame->buf[0]->तथ्य;
        अगर (!desc) {
            frame->format = ctx->format;
            frame->width  = ctx->width;
            frame->height = ctx->height;
            वापस 0;
        }
        frame->तथ्य[0] = (uint8_t*)desc->array;
        frame->तथ्य[1] = (uint8_t*)desc->सूचकांक;

        res = CHECK_CU(cu->cu_Ctx_धकेलो_Current(hwctx->cuda_ctx));
        अगर (res < 0)
            वापस res;

        क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(frame->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            अगर (arr_plane_res == CUDA_ERROR_INVALID_मूल्य) {
                अगर (i > 0)
                    अवरोध;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                अगर (res < 0)
                    जाओ fail;
            } अन्यथा अगर (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                जाओ fail;
            } अन्यथा {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                अगर (res < 0)
                    जाओ fail;
            }

            पूर्णांक elem_आकार = ff_cuda_cuarray_elem_आकार(plane_desc.Format);
            अगर (elem_आकार <= 0) {
                res = AVERROR_BUG;
                जाओ fail;
            }

            frame->linesize[i] = plane_desc.Width * plane_desc.अंक_Channels * elem_आकार;

            अगर (arr_plane_res == CUDA_ERROR_INVALID_मूल्य)
                अवरोध;
        }

        res = CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));
        अगर (res < 0)
            वापस res;
#अन्यथा
        वापस AVERROR(ENOSYS);
#पूर्ण_अगर
    } अन्यथा {
        res = av_image_fill_arrays(frame->तथ्य, frame->linesize, frame->buf[0]->तथ्य,
                                   ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        अगर (res < 0)
            वापस res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        अगर (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
            frame->तथ्य[2]     = frame->तथ्य[1];
            frame->तथ्य[1]     = frame->तथ्य[2] + frame->linesize[2] * AV_CEIL_RSHIFT(ctx->height, 1);
        }
    }

    frame->format = ctx->format;
    frame->width  = ctx->width;
    frame->height = ctx->height;

    वापस 0;

#अगर HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));
    वापस res;
#पूर्ण_अगर
}

अटल क्रमागत AVPixelFormat cuda_frame_hw_format(स्थिर AVFrame *frame)
{
    अगर (!frame->hw_frames_ctx)
        वापस AV_PIX_FMT_NONE;
    वापस ((AVHWFramesContext *)frame->hw_frames_ctx->तथ्य)->format;
}

अटल पूर्णांक cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     क्रमागत AVHWFrameTransferDirection dir,
                                     क्रमागत AVPixelFormat **formats)
{
    क्रमागत AVPixelFormat *fmts;

    fmts = av_malloc_array(2, माप(*fmts));
    अगर (!fmts)
        वापस AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    वापस 0;
}

अटल पूर्णांक cuda_transfer_तथ्य(AVHWFramesContext *ctx, AVFrame *dst,
                                 स्थिर AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    स्थिर AVFrame *sw_frame = src->hw_frames_ctx ? dst : src;
    AVFrame *शीर्ष_down = शून्य, *bottom_up_dst = शून्य;
    CUcontext dummy;
    पूर्णांक i, ret, copy_queued = 0, bottom_up = 0;

    {
        क्रमागत AVPixelFormat src_fmt = cuda_frame_hw_format(src);
        क्रमागत AVPixelFormat dst_fmt = cuda_frame_hw_format(dst);
        अगर ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            वापस AVERROR(ENOSYS);
    }

    क्रम (i = 0; i < FF_ARRAY_ELEMS(sw_frame->linesize); i++)
        bottom_up |= sw_frame->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    अगर (bottom_up) {
        शीर्ष_down = av_frame_alloc();
        अगर (!शीर्ष_down)
            वापस AVERROR(ENOMEM);
        शीर्ष_down->format = ctx->sw_format;
        शीर्ष_down->width  = ctx->width;
        शीर्ष_down->height = ctx->height;
        ret = av_hwframe_get_transfer_बफर((src->hw_frames_ctx ? src : dst)->hw_frames_ctx,
                                             शीर्ष_down);
        अगर (ret < 0)
            जाओ free_शीर्ष_down;
        शीर्ष_down->width  = src->width;
        शीर्ष_down->height = src->height;
        अगर (sw_frame == src) {
            av_image_copy2(शीर्ष_down->तथ्य, शीर्ष_down->linesize, src->तथ्य, src->linesize,
                           ctx->sw_format, src->width, src->height);
            src = शीर्ष_down;
        } अन्यथा {
            bottom_up_dst = dst;
            dst           = शीर्ष_down;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_धकेलो_Current(hwctx->cuda_ctx));
    अगर (ret < 0)
        जाओ free_शीर्ष_down;

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
    क्रम (i = 0; i < FF_ARRAY_ELEMS(src->तथ्य) && src->linesize[i]; i++) {
        पूर्णांक src_is_nonplanar_cuarray = 0;
        पूर्णांक dst_is_nonplanar_cuarray = 0;

        पूर्णांक bytewidth = av_image_get_linesize(ctx->sw_format, src->width, i);
        अगर (bytewidth < 0) {
            ret = bytewidth;
            जाओ fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .WidthInBytes  = bytewidth,
            .Height        = AV_CEIL_RSHIFT(src->height, ((i == 0 || i == 3) ? 0 : priv->shift_height)),
        };

        अगर (src->format == AV_PIX_FMT_CUDA) {
            cpy.srcMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->तथ्य[i];
        } अन्यथा अगर (src->format == AV_PIX_FMT_CUARRAY) {
#अगर HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->तथ्य[0], i);
            अगर (cures == CUDA_ERROR_INVALID_मूल्य && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->तथ्य[0];
                src_is_nonplanar_cuarray = 1;
            } अन्यथा अगर (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                जाओ fail;
            }

            cpy.srcMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#अन्यथा
            ret = AVERROR(ENOSYS);
            जाओ निकास;
#पूर्ण_अगर
        } अन्यथा {
            cpy.srcMemoryType = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->तथ्य[i];
        }

        अगर (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dstMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->तथ्य[i];
        } अन्यथा अगर (dst->format == AV_PIX_FMT_CUARRAY) {
#अगर HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->तथ्य[0], i);
            अगर (cures == CUDA_ERROR_INVALID_मूल्य && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->तथ्य[0];
                dst_is_nonplanar_cuarray = 1;
            } अन्यथा अगर (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                जाओ fail;
            }

            cpy.dstMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#अन्यथा
            ret = AVERROR(ENOSYS);
            जाओ निकास;
#पूर्ण_अगर
        } अन्यथा {
            cpy.dstMemoryType = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->तथ्य[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->stream));
        अगर (ret < 0)
            जाओ fail;
        copy_queued = 1;

        अगर (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            अवरोध;
    }

    /* The caller may reuse host memory once the transfer returns. */
    अगर (!src->hw_frames_ctx || !dst->hw_frames_ctx) {
        ret = CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
        अगर (ret < 0)
            जाओ निकास;
    }

fail:
    अगर (ret < 0 && copy_queued)
        CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
निकास:
    CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));

    अगर (bottom_up_dst && ret >= 0)
        av_image_copy2(bottom_up_dst->तथ्य, bottom_up_dst->linesize,
                       शीर्ष_down->तथ्य, शीर्ष_down->linesize,
                       ctx->sw_format, src->width, src->height);
free_शीर्ष_down:
    av_frame_free(&शीर्ष_down);

    वापस ret;
}

अटल व्योम cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    अगर (hwctx->p.internal) {
        CudaFunctions *cu = hwctx->internal.cuda_dl;

        अगर (hwctx->internal.is_allocated && hwctx->p.cuda_ctx) {
            अगर (hwctx->internal.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->internal.cuda_device));
            अन्यथा अगर (!(hwctx->internal.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = शून्य;
        }

        cuda_free_functions(&hwctx->internal.cuda_dl);
        स_रखो(&hwctx->internal, 0, माप(hwctx->internal));
        hwctx->p.internal = शून्य;
    }
}

अटल पूर्णांक cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    पूर्णांक ret;

    hwctx->p.internal = &hwctx->internal;

    अगर (!hwctx->internal.cuda_dl) {
        ret = cuda_load_functions(&hwctx->internal.cuda_dl, ctx);
        अगर (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            जाओ error;
        }
    }

    वापस 0;

error:
    cuda_device_uninit(ctx);
    वापस ret;
}

अटल पूर्णांक cuda_context_init(AVHWDeviceContext *device_ctx, पूर्णांक flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    पूर्णांक ret, dev_active = 0;
    अचिन्हित पूर्णांक dev_flags = 0;

    स्थिर अचिन्हित पूर्णांक desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->internal->cuda_dl;

    hwctx->internal->flags = flags;

    अगर (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->internal->cuda_device,
                       &dev_flags, &dev_active));
        अगर (ret < 0)
            वापस ret;

        अगर (dev_active && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            वापस AVERROR(ENOTSUP);
        } अन्यथा अगर (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cuDevicePrimaryCtxSetFlags(hwctx->internal->cuda_device,
                           desired_flags));
            अगर (ret < 0)
                वापस ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->internal->cuda_device));
        अगर (ret < 0)
            वापस ret;
    } अन्यथा अगर (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        अगर (ret < 0)
            वापस ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } अन्यथा {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->internal->cuda_device));
        अगर (ret < 0)
            वापस ret;

        CHECK_CU(cu->cu_Ctx_निकालो_Current(&dummy));
    }

    hwctx->internal->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->stream = शून्य;

    वापस 0;
}

अटल पूर्णांक cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, पूर्णांक *flags)
{
    AVDictionaryEntry *primary_ctx_opt = av_dict_get(opts, "primary_ctx", शून्य, 0);
    AVDictionaryEntry *current_ctx_opt = av_dict_get(opts, "current_ctx", शून्य, 0);

    पूर्णांक use_primary_ctx = 0, use_current_ctx = 0;
    अगर (primary_ctx_opt)
        use_primary_ctx = म_से_दीर्घ(primary_ctx_opt->मूल्य, शून्य, 10);

    अगर (current_ctx_opt)
        use_current_ctx = म_से_दीर्घ(current_ctx_opt->मूल्य, शून्य, 10);

    अगर (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        वापस AVERROR(EINVAL);
    }

    अगर (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } अन्यथा अगर (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    अगर (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } अन्यथा अगर (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    वापस 0;
}

अटल पूर्णांक cuda_device_create(AVHWDeviceContext *device_ctx,
                              स्थिर अक्षर *device,
                              AVDictionary *opts, पूर्णांक flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    पूर्णांक ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    अगर (ret < 0)
        जाओ error;

    अगर (device)
        device_idx = म_से_दीर्घ(device, शून्य, 0);

    ret = cuda_device_init(device_ctx);
    अगर (ret < 0)
        जाओ error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    अगर (ret < 0)
        जाओ error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->internal->cuda_device, device_idx));
    अगर (ret < 0)
        जाओ error;

    ret = cuda_context_init(device_ctx, flags);
    अगर (ret < 0)
        जाओ error;

    वापस 0;

error:
    cuda_device_uninit(device_ctx);
    वापस ret;
}

अटल पूर्णांक cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              पूर्णांक flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    स्थिर अक्षर *src_uuid = शून्य;
#अगर CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#पूर्ण_अगर
    पूर्णांक ret, i, device_गिनती;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    अगर (ret < 0)
        जाओ error;

#अगर CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#पूर्ण_अगर

    चयन (src_ctx->type) {
#अगर CONFIG_VULKAN
#घोषणा TYPE PFN_vkGetPhysicalDeviceProperties2
    हाल AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .p_अग्र = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        अवरोध;
    }
#अघोषित TYPE
#पूर्ण_अगर
    शेष:
        ret = AVERROR(ENOSYS);
        जाओ error;
    }

    अगर (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        जाओ error;
    }

    ret = cuda_device_init(device_ctx);
    अगर (ret < 0)
        जाओ error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    अगर (ret < 0)
        जाओ error;

    ret = CHECK_CU(cu->cu_Device_Get_गिनती(&device_गिनती));
    अगर (ret < 0)
        जाओ error;

    hwctx->internal->cuda_device = -1;
    क्रम (i = 0; i < device_गिनती; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        अगर (ret < 0)
            जाओ error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        अगर (ret < 0)
            जाओ error;

        अगर (स_भेद(src_uuid, uuid.bytes, माप (uuid.bytes)) == 0) {
            hwctx->internal->cuda_device = dev;
            अवरोध;
        }
    }

    अगर (hwctx->internal->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        जाओ error;
    }

    ret = cuda_context_init(device_ctx, flags);
    अगर (ret < 0)
        जाओ error;

    वापस 0;

error:
    cuda_device_uninit(device_ctx);
    वापस ret;
}

स्थिर HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_आकार    = माप(CUDADeviceContext),
    .frames_hwctx_आकार    = माप(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .frames_get_constraints = cuda_frames_get_constraints,
    .frames_init          = cuda_frames_init,
    .frames_uninit        = cuda_frames_uninit,
    .frames_get_बफर    = cuda_get_बफर,
    .transfer_get_formats = cuda_transfer_get_formats,
#अगर HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_बफर_alloc = cuda_transfer_बफर_alloc,
#पूर्ण_अगर
    .transfer_तथ्य_to     = cuda_transfer_तथ्य,
    .transfer_तथ्य_from   = cuda_transfer_तथ्य,

    .pix_fmts             = (स्थिर क्रमागत AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#अगर HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#पूर्ण_अगर
                                                          AV_PIX_FMT_NONE },
};
