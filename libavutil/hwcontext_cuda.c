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
#जर CONFIG_VULKAN
#अन्तर्भाव "hwcontext_vulkan.h"
#endif
#अन्तर्भाव "cuda_check.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "imgutils.h"

प्रकारव्याख्या संरचना CUDAFramesContext {
    AVCUDAFramesContext p;

    पूर्णांक shift_width, shift_height;
    पूर्णांक tex_alignment;

    पूर्णांक cuarray_अंक_surfaces_used;
} CUDAFramesContext;

प्रकारव्याख्या संरचना CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADeviceContextInternal internal;
} CUDADeviceContext;



#define CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

स्थिर CUarray_format cuda_array_format_for_pix_fmt(गणना AVPixelFormat fmt);

स्थिर पूर्णांक cuda_frames_get_constraints(AVHWDeviceContext *ctx,
                                       स्थिरांक शून्य *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    स्थिरांक AVCUDAHWConfig *config = hwconfig;
    गणना AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    पूर्णांक n = 0;

    जर (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, आकार(*constraints->valid_hw_formats));
        जर (!constraints->valid_hw_formats)
            परत AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } अन्यथा {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, आकार(*constraints->valid_hw_formats));
        जर (!constraints->valid_hw_formats)
            परत AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#जर HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#अन्यथा
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#endif
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    आकार(*constraints->valid_sw_formats));
    जर (!constraints->valid_sw_formats)
        परत AVERROR(ENOMEM);

    n = 0;
    साठी (पूर्णांक i = 0; i < AV_PIX_FMT_NB; i++) {
        जर (req_fmt == AV_PIX_FMT_CUARRAY) {
            जर (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } अन्यथा {
            स्थिरांक AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            जर (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#जर CONFIG_VULKAN
    जर (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#endif
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    परत 0;
}

स्थिर शून्य cuda_buffer_free(शून्य *opaque, uint8_t *data)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ढकला_Current(hwctx->cuda_ctx));

    जर (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)data;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } अन्यथा {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)data));
    }

    CHECK_CU(cu->cu_Ctx_काढा_Current(&dummy));
}

स्थिर AVBufferRef *cuda_pool_alloc(शून्य *opaque, माप_प्रकार size)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    AVBufferRef *ret = रिक्त;
    CUcontext dummy = रिक्त;
    CUdeviceptr data;
    पूर्णांक err;

    err = CHECK_CU(cu->cu_Ctx_ढकला_Current(hwctx->cuda_ctx));
    जर (err < 0)
        परत रिक्त;

    जर (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = av_mallocz(आकार(*desc));
        जर (!desc)
            जा done;

        जर (priv->p.cuarray_अंक_surfaces > 0) {
            जर (priv->cuarray_अंक_surfaces_used >= priv->p.cuarray_अंक_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                जा done;
            }
            desc->index = priv->cuarray_अंक_surfaces_used++;
            desc->array = priv->p.cuarray_surfaces[desc->index];
        } अन्यथा {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            जर (err < 0) {
                av_free(desc);
                जा done;
            }
        }

        ret = av_buffer_create((uint8_t*)desc, आकार(*desc), cuda_buffer_free, ctx, 0);
        जर (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            जा done;
        }

        जा done;
    }

    err = CHECK_CU(cu->cuMemAlloc(&data, size));
    जर (err < 0)
        जा done;

    ret = av_buffer_create((uint8_t*)data, size, cuda_buffer_free, ctx, 0);
    जर (!ret) {
        CHECK_CU(cu->cuMemFree(data));
        जा done;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
done:
    CHECK_CU(cu->cu_Ctx_काढा_Current(&dummy));
    परत ret;
}

#जर HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
स्थिर शून्य cuda_transfer_buffer_free(शून्य *opaque, uint8_t *data)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ढकला_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(data));
    CHECK_CU(cu->cu_Ctx_काढा_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
स्थिर AVBufferRef *cuda_transfer_buffer_alloc(शून्य *device_ref, माप_प्रकार size)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->data;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    AVBufferRef *ret = रिक्त;
    CUcontext dummy;
    शून्य *host;

    जर (CHECK_CU(cu->cu_Ctx_ढकला_Current(hwctx->cuda_ctx)) < 0)
        परत av_buffer_alloc(size);

    जर (CHECK_CU(cu->cuMemHostAlloc(&host, size, 0)) >= 0) {
        ret = av_buffer_create(host, size, cuda_transfer_buffer_free, device_ctx, 0);
        जर (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_काढा_Current(&dummy));
    परत ret ? ret : av_buffer_alloc(size);
}
#endif

स्थिर शून्य cuda_frames_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    जर (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_ढकला_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        साठी (पूर्णांक i = priv->cuarray_अंक_surfaces_used; i < priv->p.cuarray_अंक_surfaces; i++)
            जर (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_काढा_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_अंक_surfaces = 0;
    }
}

स्थिर CUarray_format cuda_array_format_for_pix_fmt(गणना AVPixelFormat fmt)
{
    निवड (fmt) {
#जर HAVE_FFNVCODEC_CUARRAY
    स्थिती AV_PIX_FMT_NV12:      परत CU_AD_FORMAT_NV12;
    स्थिती AV_PIX_FMT_P010:
    स्थिती AV_PIX_FMT_P012:
    स्थिती AV_PIX_FMT_P016:      परत CU_AD_FORMAT_P016;
    स्थिती AV_PIX_FMT_NV16:      परत CU_AD_FORMAT_NV16;
    स्थिती AV_PIX_FMT_P210:
    स्थिती AV_PIX_FMT_P212:
    स्थिती AV_PIX_FMT_P216:      परत CU_AD_FORMAT_P216;
    स्थिती AV_PIX_FMT_NV24:      परत CU_AD_FORMAT_YUV444_8BIT_SEMIPLANAR;
    स्थिती AV_PIX_FMT_P410:
    स्थिती AV_PIX_FMT_P412:
    स्थिती AV_PIX_FMT_P416:      परत CU_AD_FORMAT_YUV444_16BIT_SEMIPLANAR;
    स्थिती AV_PIX_FMT_YUV420P:   परत CU_AD_FORMAT_UINT8_PLANAR_420;
    स्थिती AV_PIX_FMT_YUV422P:   परत CU_AD_FORMAT_UINT8_PLANAR_422;
    स्थिती AV_PIX_FMT_YUV444P:   परत CU_AD_FORMAT_UINT8_PLANAR_444;
    स्थिती AV_PIX_FMT_YUV420P10: परत CU_AD_FORMAT_UINT16_PLANAR_420;
    स्थिती AV_PIX_FMT_YUV422P10: परत CU_AD_FORMAT_UINT16_PLANAR_422;
    स्थिती AV_PIX_FMT_YUV444P10:
    स्थिती AV_PIX_FMT_YUV444P10MSB:
    स्थिती AV_PIX_FMT_YUV444P12MSB:
    स्थिती AV_PIX_FMT_YUV444P16: परत CU_AD_FORMAT_UINT16_PLANAR_444;
    स्थिती AV_PIX_FMT_0RGB32:
    स्थिती AV_PIX_FMT_0BGR32:
    स्थिती AV_PIX_FMT_RGB32:
    स्थिती AV_PIX_FMT_BGR32:     परत CU_AD_FORMAT_UNSIGNED_INT8;
#endif
    पूर्वनिर्धारित:                   परत 0;
    }
}

#जर HAVE_FFNVCODEC_CUARRAY
स्थिर अचिन्हित पूर्णांक cuda_array_numchannels_for_pix_fmt(गणना AVPixelFormat fmt)
{
    निवड (fmt) {
    स्थिती AV_PIX_FMT_0RGB32:
    स्थिती AV_PIX_FMT_0BGR32:
    स्थिती AV_PIX_FMT_RGB32:
    स्थिती AV_PIX_FMT_BGR32:     परत 4;
    पूर्वनिर्धारित:                   परत 3;
    }
}
#endif

स्थिर पूर्णांक cuda_frames_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    स्थिरांक AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    पूर्णांक err;

    जर (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        परत AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    जर (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        परत AVERROR(ENOSYS);
    }

#जर HAVE_FFNVCODEC_CUARRAY
    जर (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        परत AVERROR(ENOSYS);
    }
#अन्यथा
    जर (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        परत AVERROR(ENOSYS);
    }
#endif

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->internal->cuda_device));
    जर (err < 0)
        परत err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    जर (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->shift_width, &priv->shift_height);

#जर HAVE_FFNVCODEC_CUARRAY
    जर (ctx->format == AV_PIX_FMT_CUARRAY) {
        जर (!priv->p.cuarray_desc.Width)
            priv->p.cuarray_desc.Width = ctx->width;
        जर (!priv->p.cuarray_desc.Height)
            priv->p.cuarray_desc.Height = ctx->height;
        जर (!priv->p.cuarray_desc.अंक_Channels)
            priv->p.cuarray_desc.अंक_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        जर (priv->p.cuarray_desc.Depth) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            परत AVERROR(EINVAL);
        }

        जर (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        जर (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            परत AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    जर (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_अंक_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_अंक_surfaces, आकार(*priv->p.cuarray_surfaces));
        जर (!priv->p.cuarray_surfaces)
            परत AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_ढकला_Current(hwctx->cuda_ctx));
        जर (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            परत err;
        }

        साठी (पूर्णांक i = 0; i < priv->p.cuarray_अंक_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            जर (err < 0) {
                साठी (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_काढा_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                परत err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_काढा_Current(&dummy));
        जर (err < 0)
            जा fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_अंक_surfaces, priv->p.cuarray_desc.Width, priv->p.cuarray_desc.Height);
    }
#endif

    जर (!ctx->pool) {
        पूर्णांक size = av_image_get_buffer_size(ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        जर (size < 0) {
            err = size;
            जा fail;
        }

        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(size, ctx, cuda_pool_alloc, रिक्त);
        जर (!ffhwframesctx(ctx)->pool_internal) {
            err = AVERROR(ENOMEM);
            जा fail;
        }
    }

    परत 0;

fail:
    cuda_frames_uninit(ctx);
    परत err;
}

स्थिर पूर्णांक cuda_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#जर HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;
#endif
    पूर्णांक res;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    जर (!frame->buf[0])
        परत AVERROR(ENOMEM);

    जर (ctx->format == AV_PIX_FMT_CUARRAY) {
#जर HAVE_FFNVCODEC_CUARRAY
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)frame->buf[0]->data;
        जर (!desc) {
            frame->format = ctx->format;
            frame->width  = ctx->width;
            frame->height = ctx->height;
            परत 0;
        }
        frame->data[0] = (uint8_t*)desc->array;
        frame->data[1] = (uint8_t*)desc->index;

        res = CHECK_CU(cu->cu_Ctx_ढकला_Current(hwctx->cuda_ctx));
        जर (res < 0)
            परत res;

        साठी (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(frame->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            जर (arr_plane_res == CUDA_ERROR_INVALID_मूल्य) {
                जर (i > 0)
                    थांबा;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                जर (res < 0)
                    जा fail;
            } अन्यथा जर (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                जा fail;
            } अन्यथा {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                जर (res < 0)
                    जा fail;
            }

            पूर्णांक elem_size = ff_cuda_cuarray_elem_size(plane_desc.Format);
            जर (elem_size <= 0) {
                res = AVERROR_BUG;
                जा fail;
            }

            frame->linesize[i] = plane_desc.Width * plane_desc.अंक_Channels * elem_size;

            जर (arr_plane_res == CUDA_ERROR_INVALID_मूल्य)
                थांबा;
        }

        res = CHECK_CU(cu->cu_Ctx_काढा_Current(&dummy));
        जर (res < 0)
            परत res;
#अन्यथा
        परत AVERROR(ENOSYS);
#endif
    } अन्यथा {
        res = av_image_fill_arrays(frame->data, frame->linesize, frame->buf[0]->data,
                                   ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        जर (res < 0)
            परत res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        जर (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
            frame->data[2]     = frame->data[1];
            frame->data[1]     = frame->data[2] + frame->linesize[2] * AV_CEIL_RSHIFT(ctx->height, 1);
        }
    }

    frame->format = ctx->format;
    frame->width  = ctx->width;
    frame->height = ctx->height;

    परत 0;

#जर HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_काढा_Current(&dummy));
    परत res;
#endif
}

स्थिर गणना AVPixelFormat cuda_frame_hw_format(स्थिरांक AVFrame *frame)
{
    जर (!frame->hw_frames_ctx)
        परत AV_PIX_FMT_NONE;
    परत ((AVHWFramesContext *)frame->hw_frames_ctx->data)->format;
}

स्थिर पूर्णांक cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     गणना AVHWFrameTransferDirection dir,
                                     गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts;

    fmts = av_malloc_array(2, आकार(*fmts));
    जर (!fmts)
        परत AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    परत 0;
}

स्थिर पूर्णांक cuda_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 स्थिरांक AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    स्थिरांक AVFrame *sw_frame = src->hw_frames_ctx ? dst : src;
    AVFrame *शीर्ष_down = रिक्त, *bottom_up_dst = रिक्त;
    CUcontext dummy;
    पूर्णांक i, ret, copy_queued = 0, bottom_up = 0;

    {
        गणना AVPixelFormat src_fmt = cuda_frame_hw_format(src);
        गणना AVPixelFormat dst_fmt = cuda_frame_hw_format(dst);
        जर ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            परत AVERROR(ENOSYS);
    }

    साठी (i = 0; i < FF_ARRAY_ELEMS(sw_frame->linesize); i++)
        bottom_up |= sw_frame->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    जर (bottom_up) {
        शीर्ष_down = av_frame_alloc();
        जर (!शीर्ष_down)
            परत AVERROR(ENOMEM);
        शीर्ष_down->format = ctx->sw_format;
        शीर्ष_down->width  = ctx->width;
        शीर्ष_down->height = ctx->height;
        ret = av_hwframe_get_transfer_buffer((src->hw_frames_ctx ? src : dst)->hw_frames_ctx,
                                             शीर्ष_down);
        जर (ret < 0)
            जा free_शीर्ष_down;
        शीर्ष_down->width  = src->width;
        शीर्ष_down->height = src->height;
        जर (sw_frame == src) {
            av_image_copy2(शीर्ष_down->data, शीर्ष_down->linesize, src->data, src->linesize,
                           ctx->sw_format, src->width, src->height);
            src = शीर्ष_down;
        } अन्यथा {
            bottom_up_dst = dst;
            dst           = शीर्ष_down;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_ढकला_Current(hwctx->cuda_ctx));
    जर (ret < 0)
        जा free_शीर्ष_down;

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
    साठी (i = 0; i < FF_ARRAY_ELEMS(src->data) && src->linesize[i]; i++) {
        पूर्णांक src_is_nonplanar_cuarray = 0;
        पूर्णांक dst_is_nonplanar_cuarray = 0;

        पूर्णांक bytewidth = av_image_get_linesize(ctx->sw_format, src->width, i);
        जर (bytewidth < 0) {
            ret = bytewidth;
            जा fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .WidthInBytes  = bytewidth,
            .Height        = AV_CEIL_RSHIFT(src->height, ((i == 0 || i == 3) ? 0 : priv->shift_height)),
        };

        जर (src->format == AV_PIX_FMT_CUDA) {
            cpy.srcMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->data[i];
        } अन्यथा जर (src->format == AV_PIX_FMT_CUARRAY) {
#जर HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->data[0], i);
            जर (cures == CUDA_ERROR_INVALID_मूल्य && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->data[0];
                src_is_nonplanar_cuarray = 1;
            } अन्यथा जर (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                जा fail;
            }

            cpy.srcMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#अन्यथा
            ret = AVERROR(ENOSYS);
            जा निकास;
#endif
        } अन्यथा {
            cpy.srcMemoryType = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->data[i];
        }

        जर (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dstMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->data[i];
        } अन्यथा जर (dst->format == AV_PIX_FMT_CUARRAY) {
#जर HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->data[0], i);
            जर (cures == CUDA_ERROR_INVALID_मूल्य && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->data[0];
                dst_is_nonplanar_cuarray = 1;
            } अन्यथा जर (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                जा fail;
            }

            cpy.dstMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#अन्यथा
            ret = AVERROR(ENOSYS);
            जा निकास;
#endif
        } अन्यथा {
            cpy.dstMemoryType = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->data[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->stream));
        जर (ret < 0)
            जा fail;
        copy_queued = 1;

        जर (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            थांबा;
    }

    /* The caller may reuse host memory once the transfer returns. */
    जर (!src->hw_frames_ctx || !dst->hw_frames_ctx) {
        ret = CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
        जर (ret < 0)
            जा निकास;
    }

fail:
    जर (ret < 0 && copy_queued)
        CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
निकास:
    CHECK_CU(cu->cu_Ctx_काढा_Current(&dummy));

    जर (bottom_up_dst && ret >= 0)
        av_image_copy2(bottom_up_dst->data, bottom_up_dst->linesize,
                       शीर्ष_down->data, शीर्ष_down->linesize,
                       ctx->sw_format, src->width, src->height);
free_शीर्ष_down:
    av_frame_free(&शीर्ष_down);

    परत ret;
}

स्थिर शून्य cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    जर (hwctx->p.internal) {
        CudaFunctions *cu = hwctx->internal.cuda_dl;

        जर (hwctx->internal.is_allocated && hwctx->p.cuda_ctx) {
            जर (hwctx->internal.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->internal.cuda_device));
            अन्यथा जर (!(hwctx->internal.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = रिक्त;
        }

        cuda_free_functions(&hwctx->internal.cuda_dl);
        स_रखो(&hwctx->internal, 0, आकार(hwctx->internal));
        hwctx->p.internal = रिक्त;
    }
}

स्थिर पूर्णांक cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    पूर्णांक ret;

    hwctx->p.internal = &hwctx->internal;

    जर (!hwctx->internal.cuda_dl) {
        ret = cuda_load_functions(&hwctx->internal.cuda_dl, ctx);
        जर (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            जा error;
        }
    }

    परत 0;

error:
    cuda_device_uninit(ctx);
    परत ret;
}

स्थिर पूर्णांक cuda_context_init(AVHWDeviceContext *device_ctx, पूर्णांक flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    पूर्णांक ret, dev_active = 0;
    अचिन्हित पूर्णांक dev_flags = 0;

    स्थिरांक अचिन्हित पूर्णांक desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->internal->cuda_dl;

    hwctx->internal->flags = flags;

    जर (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->internal->cuda_device,
                       &dev_flags, &dev_active));
        जर (ret < 0)
            परत ret;

        जर (dev_active && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            परत AVERROR(ENOTSUP);
        } अन्यथा जर (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cuDevicePrimaryCtxSetFlags(hwctx->internal->cuda_device,
                           desired_flags));
            जर (ret < 0)
                परत ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->internal->cuda_device));
        जर (ret < 0)
            परत ret;
    } अन्यथा जर (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        जर (ret < 0)
            परत ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } अन्यथा {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->internal->cuda_device));
        जर (ret < 0)
            परत ret;

        CHECK_CU(cu->cu_Ctx_काढा_Current(&dummy));
    }

    hwctx->internal->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->stream = रिक्त;

    परत 0;
}

स्थिर पूर्णांक cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, पूर्णांक *flags)
{
    AVDictionaryEntry *primary_ctx_opt = av_dict_get(opts, "primary_ctx", रिक्त, 0);
    AVDictionaryEntry *current_ctx_opt = av_dict_get(opts, "current_ctx", रिक्त, 0);

    पूर्णांक use_primary_ctx = 0, use_current_ctx = 0;
    जर (primary_ctx_opt)
        use_primary_ctx = म_से_दीर्घ(primary_ctx_opt->मूल्य, रिक्त, 10);

    जर (current_ctx_opt)
        use_current_ctx = म_से_दीर्घ(current_ctx_opt->मूल्य, रिक्त, 10);

    जर (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        परत AVERROR(EINVAL);
    }

    जर (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } अन्यथा जर (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    जर (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } अन्यथा जर (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    परत 0;
}

स्थिर पूर्णांक cuda_device_create(AVHWDeviceContext *device_ctx,
                              स्थिरांक अक्षर *device,
                              AVDictionary *opts, पूर्णांक flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    पूर्णांक ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    जर (ret < 0)
        जा error;

    जर (device)
        device_idx = म_से_दीर्घ(device, रिक्त, 0);

    ret = cuda_device_init(device_ctx);
    जर (ret < 0)
        जा error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    जर (ret < 0)
        जा error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->internal->cuda_device, device_idx));
    जर (ret < 0)
        जा error;

    ret = cuda_context_init(device_ctx, flags);
    जर (ret < 0)
        जा error;

    परत 0;

error:
    cuda_device_uninit(device_ctx);
    परत ret;
}

स्थिर पूर्णांक cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              पूर्णांक flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    स्थिरांक अक्षर *src_uuid = रिक्त;
#जर CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#endif
    पूर्णांक ret, i, device_मोजणी;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    जर (ret < 0)
        जा error;

#जर CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#endif

    निवड (src_ctx->type) {
#जर CONFIG_VULKAN
#define TYPE PFN_vkGetPhysicalDeviceProperties2
    स्थिती AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .pNext = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        थांबा;
    }
#undef TYPE
#endif
    पूर्वनिर्धारित:
        ret = AVERROR(ENOSYS);
        जा error;
    }

    जर (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        जा error;
    }

    ret = cuda_device_init(device_ctx);
    जर (ret < 0)
        जा error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    जर (ret < 0)
        जा error;

    ret = CHECK_CU(cu->cu_Device_Get_मोजणी(&device_मोजणी));
    जर (ret < 0)
        जा error;

    hwctx->internal->cuda_device = -1;
    साठी (i = 0; i < device_मोजणी; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        जर (ret < 0)
            जा error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        जर (ret < 0)
            जा error;

        जर (स_भेद(src_uuid, uuid.bytes, आकार (uuid.bytes)) == 0) {
            hwctx->internal->cuda_device = dev;
            थांबा;
        }
    }

    जर (hwctx->internal->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        जा error;
    }

    ret = cuda_context_init(device_ctx, flags);
    जर (ret < 0)
        जा error;

    परत 0;

error:
    cuda_device_uninit(device_ctx);
    परत ret;
}

स्थिरांक HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_size    = आकार(CUDADeviceContext),
    .frames_hwctx_size    = आकार(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .frames_get_constraints = cuda_frames_get_constraints,
    .frames_init          = cuda_frames_init,
    .frames_uninit        = cuda_frames_uninit,
    .frames_get_buffer    = cuda_get_buffer,
    .transfer_get_formats = cuda_transfer_get_formats,
#जर HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_buffer_alloc = cuda_transfer_buffer_alloc,
#endif
    .transfer_data_to     = cuda_transfer_data,
    .transfer_data_from   = cuda_transfer_data,

    .pix_fmts             = (स्थिरांक गणना AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#जर HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#endif
                                                          AV_PIX_FMT_NONE },
};
