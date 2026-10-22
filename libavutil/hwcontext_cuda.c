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

#அந்தர்பாவ "buffer.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "hwcontext.h"
#அந்தர்பாவ "hwcontext_internal.h"
#அந்தர்பாவ "hwcontext_cuda_internal.h"
#எனில் CONFIG_VULKAN
#அந்தர்பாவ "hwcontext_vulkan.h"
#endif
#அந்தர்பாவ "cuda_check.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "pixdesc.h"
#அந்தர்பாவ "pixfmt.h"
#அந்தர்பாவ "imgutils.h"

வகைவரை கட்டமைப்பு CUDAFramesContext {
    AVCUDAFramesContext p;

    முழு shift_width, shift_height;
    முழு tex_alignment;

    முழு cuarray_இலக்கம்_surfaces_used;
} CUDAFramesContext;

வகைவரை கட்டமைப்பு CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADeviceContextInternal internal;
} CUDADeviceContext;



#define CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

நிலையான CUarray_format cuda_array_format_for_pix_fmt(எண்ணிக்கை AVPixelFormat fmt);

நிலையான முழு cuda_frames_get_constraints(AVHWDeviceContext *ctx,
                                       மாறிலி வெறுமை *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    மாறிலி AVCUDAHWConfig *config = hwconfig;
    எண்ணிக்கை AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    முழு n = 0;

    எனில் (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, அளவு(*constraints->valid_hw_formats));
        எனில் (!constraints->valid_hw_formats)
            திரும்பு AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } இல்லையெனில் {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, அளவு(*constraints->valid_hw_formats));
        எனில் (!constraints->valid_hw_formats)
            திரும்பு AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#எனில் HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#இல்லையெனில்
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#endif
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    அளவு(*constraints->valid_sw_formats));
    எனில் (!constraints->valid_sw_formats)
        திரும்பு AVERROR(ENOMEM);

    n = 0;
    க்கு (முழு i = 0; i < AV_PIX_FMT_NB; i++) {
        எனில் (req_fmt == AV_PIX_FMT_CUARRAY) {
            எனில் (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } இல்லையெனில் {
            மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            எனில் (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#எனில் CONFIG_VULKAN
    எனில் (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#endif
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    திரும்பு 0;
}

நிலையான வெறுமை cuda_buffer_free(வெறுமை *opaque, uint8_t *data)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_தள்ளு_Current(hwctx->cuda_ctx));

    எனில் (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)data;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } இல்லையெனில் {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)data));
    }

    CHECK_CU(cu->cu_Ctx_எடு_Current(&dummy));
}

நிலையான AVBufferRef *cuda_pool_alloc(வெறுமை *opaque, size_t size)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    AVBufferRef *ret = வெற்று;
    CUcontext dummy = வெற்று;
    CUdeviceptr data;
    முழு err;

    err = CHECK_CU(cu->cu_Ctx_தள்ளு_Current(hwctx->cuda_ctx));
    எனில் (err < 0)
        திரும்பு வெற்று;

    எனில் (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = av_mallocz(அளவு(*desc));
        எனில் (!desc)
            செல் done;

        எனில் (priv->p.cuarray_இலக்கம்_surfaces > 0) {
            எனில் (priv->cuarray_இலக்கம்_surfaces_used >= priv->p.cuarray_இலக்கம்_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                செல் done;
            }
            desc->index = priv->cuarray_இலக்கம்_surfaces_used++;
            desc->array = priv->p.cuarray_surfaces[desc->index];
        } இல்லையெனில் {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            எனில் (err < 0) {
                av_free(desc);
                செல் done;
            }
        }

        ret = av_buffer_create((uint8_t*)desc, அளவு(*desc), cuda_buffer_free, ctx, 0);
        எனில் (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            செல் done;
        }

        செல் done;
    }

    err = CHECK_CU(cu->cuMemAlloc(&data, size));
    எனில் (err < 0)
        செல் done;

    ret = av_buffer_create((uint8_t*)data, size, cuda_buffer_free, ctx, 0);
    எனில் (!ret) {
        CHECK_CU(cu->cuMemFree(data));
        செல் done;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
done:
    CHECK_CU(cu->cu_Ctx_எடு_Current(&dummy));
    திரும்பு ret;
}

#எனில் HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
நிலையான வெறுமை cuda_transfer_buffer_free(வெறுமை *opaque, uint8_t *data)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_தள்ளு_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(data));
    CHECK_CU(cu->cu_Ctx_எடு_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
நிலையான AVBufferRef *cuda_transfer_buffer_alloc(வெறுமை *device_ref, size_t size)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->data;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    AVBufferRef *ret = வெற்று;
    CUcontext dummy;
    வெறுமை *host;

    எனில் (CHECK_CU(cu->cu_Ctx_தள்ளு_Current(hwctx->cuda_ctx)) < 0)
        திரும்பு av_buffer_alloc(size);

    எனில் (CHECK_CU(cu->cuMemHostAlloc(&host, size, 0)) >= 0) {
        ret = av_buffer_create(host, size, cuda_transfer_buffer_free, device_ctx, 0);
        எனில் (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_எடு_Current(&dummy));
    திரும்பு ret ? ret : av_buffer_alloc(size);
}
#endif

நிலையான வெறுமை cuda_frames_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    எனில் (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_தள்ளு_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        க்கு (முழு i = priv->cuarray_இலக்கம்_surfaces_used; i < priv->p.cuarray_இலக்கம்_surfaces; i++)
            எனில் (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_எடு_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_இலக்கம்_surfaces = 0;
    }
}

நிலையான CUarray_format cuda_array_format_for_pix_fmt(எண்ணிக்கை AVPixelFormat fmt)
{
    தேர்வு (fmt) {
#எனில் HAVE_FFNVCODEC_CUARRAY
    நிலை AV_PIX_FMT_NV12:      திரும்பு CU_AD_FORMAT_NV12;
    நிலை AV_PIX_FMT_P010:
    நிலை AV_PIX_FMT_P012:
    நிலை AV_PIX_FMT_P016:      திரும்பு CU_AD_FORMAT_P016;
    நிலை AV_PIX_FMT_NV16:      திரும்பு CU_AD_FORMAT_NV16;
    நிலை AV_PIX_FMT_P210:
    நிலை AV_PIX_FMT_P212:
    நிலை AV_PIX_FMT_P216:      திரும்பு CU_AD_FORMAT_P216;
    நிலை AV_PIX_FMT_NV24:      திரும்பு CU_AD_FORMAT_YUV444_8BIT_SEMIPLANAR;
    நிலை AV_PIX_FMT_P410:
    நிலை AV_PIX_FMT_P412:
    நிலை AV_PIX_FMT_P416:      திரும்பு CU_AD_FORMAT_YUV444_16BIT_SEMIPLANAR;
    நிலை AV_PIX_FMT_YUV420P:   திரும்பு CU_AD_FORMAT_UINT8_PLANAR_420;
    நிலை AV_PIX_FMT_YUV422P:   திரும்பு CU_AD_FORMAT_UINT8_PLANAR_422;
    நிலை AV_PIX_FMT_YUV444P:   திரும்பு CU_AD_FORMAT_UINT8_PLANAR_444;
    நிலை AV_PIX_FMT_YUV420P10: திரும்பு CU_AD_FORMAT_UINT16_PLANAR_420;
    நிலை AV_PIX_FMT_YUV422P10: திரும்பு CU_AD_FORMAT_UINT16_PLANAR_422;
    நிலை AV_PIX_FMT_YUV444P10:
    நிலை AV_PIX_FMT_YUV444P10MSB:
    நிலை AV_PIX_FMT_YUV444P12MSB:
    நிலை AV_PIX_FMT_YUV444P16: திரும்பு CU_AD_FORMAT_UINT16_PLANAR_444;
    நிலை AV_PIX_FMT_0RGB32:
    நிலை AV_PIX_FMT_0BGR32:
    நிலை AV_PIX_FMT_RGB32:
    நிலை AV_PIX_FMT_BGR32:     திரும்பு CU_AD_FORMAT_UNSIGNED_INT8;
#endif
    இயல்பு:                   திரும்பு 0;
    }
}

#எனில் HAVE_FFNVCODEC_CUARRAY
நிலையான unsigned முழு cuda_array_numchannels_for_pix_fmt(எண்ணிக்கை AVPixelFormat fmt)
{
    தேர்வு (fmt) {
    நிலை AV_PIX_FMT_0RGB32:
    நிலை AV_PIX_FMT_0BGR32:
    நிலை AV_PIX_FMT_RGB32:
    நிலை AV_PIX_FMT_BGR32:     திரும்பு 4;
    இயல்பு:                   திரும்பு 3;
    }
}
#endif

நிலையான முழு cuda_frames_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    முழு err;

    எனில் (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        திரும்பு AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    எனில் (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        திரும்பு AVERROR(ENOSYS);
    }

#எனில் HAVE_FFNVCODEC_CUARRAY
    எனில் (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        திரும்பு AVERROR(ENOSYS);
    }
#இல்லையெனில்
    எனில் (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        திரும்பு AVERROR(ENOSYS);
    }
#endif

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->internal->cuda_device));
    எனில் (err < 0)
        திரும்பு err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    எனில் (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->shift_width, &priv->shift_height);

#எனில் HAVE_FFNVCODEC_CUARRAY
    எனில் (ctx->format == AV_PIX_FMT_CUARRAY) {
        எனில் (!priv->p.cuarray_desc.Width)
            priv->p.cuarray_desc.Width = ctx->width;
        எனில் (!priv->p.cuarray_desc.Height)
            priv->p.cuarray_desc.Height = ctx->height;
        எனில் (!priv->p.cuarray_desc.இலக்கம்_Channels)
            priv->p.cuarray_desc.இலக்கம்_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        எனில் (priv->p.cuarray_desc.Depth) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            திரும்பு AVERROR(EINVAL);
        }

        எனில் (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        எனில் (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            திரும்பு AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    எனில் (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_இலக்கம்_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_இலக்கம்_surfaces, அளவு(*priv->p.cuarray_surfaces));
        எனில் (!priv->p.cuarray_surfaces)
            திரும்பு AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_தள்ளு_Current(hwctx->cuda_ctx));
        எனில் (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            திரும்பு err;
        }

        க்கு (முழு i = 0; i < priv->p.cuarray_இலக்கம்_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            எனில் (err < 0) {
                க்கு (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_எடு_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                திரும்பு err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_எடு_Current(&dummy));
        எனில் (err < 0)
            செல் fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_இலக்கம்_surfaces, priv->p.cuarray_desc.Width, priv->p.cuarray_desc.Height);
    }
#endif

    எனில் (!ctx->pool) {
        முழு size = av_image_get_buffer_size(ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        எனில் (size < 0) {
            err = size;
            செல் fail;
        }

        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(size, ctx, cuda_pool_alloc, வெற்று);
        எனில் (!ffhwframesctx(ctx)->pool_internal) {
            err = AVERROR(ENOMEM);
            செல் fail;
        }
    }

    திரும்பு 0;

fail:
    cuda_frames_uninit(ctx);
    திரும்பு err;
}

நிலையான முழு cuda_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#எனில் HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;
#endif
    முழு res;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    எனில் (!frame->buf[0])
        திரும்பு AVERROR(ENOMEM);

    எனில் (ctx->format == AV_PIX_FMT_CUARRAY) {
#எனில் HAVE_FFNVCODEC_CUARRAY
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)frame->buf[0]->data;
        எனில் (!desc) {
            frame->format = ctx->format;
            frame->width  = ctx->width;
            frame->height = ctx->height;
            திரும்பு 0;
        }
        frame->data[0] = (uint8_t*)desc->array;
        frame->data[1] = (uint8_t*)desc->index;

        res = CHECK_CU(cu->cu_Ctx_தள்ளு_Current(hwctx->cuda_ctx));
        எனில் (res < 0)
            திரும்பு res;

        க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(frame->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            எனில் (arr_plane_res == CUDA_ERROR_INVALID_மதிப்பு) {
                எனில் (i > 0)
                    நிறுத்து;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                எனில் (res < 0)
                    செல் fail;
            } இல்லையெனில் எனில் (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                செல் fail;
            } இல்லையெனில் {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                எனில் (res < 0)
                    செல் fail;
            }

            முழு elem_size = ff_cuda_cuarray_elem_size(plane_desc.Format);
            எனில் (elem_size <= 0) {
                res = AVERROR_BUG;
                செல் fail;
            }

            frame->linesize[i] = plane_desc.Width * plane_desc.இலக்கம்_Channels * elem_size;

            எனில் (arr_plane_res == CUDA_ERROR_INVALID_மதிப்பு)
                நிறுத்து;
        }

        res = CHECK_CU(cu->cu_Ctx_எடு_Current(&dummy));
        எனில் (res < 0)
            திரும்பு res;
#இல்லையெனில்
        திரும்பு AVERROR(ENOSYS);
#endif
    } இல்லையெனில் {
        res = av_image_fill_arrays(frame->data, frame->linesize, frame->buf[0]->data,
                                   ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        எனில் (res < 0)
            திரும்பு res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        எனில் (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
            frame->data[2]     = frame->data[1];
            frame->data[1]     = frame->data[2] + frame->linesize[2] * AV_CEIL_RSHIFT(ctx->height, 1);
        }
    }

    frame->format = ctx->format;
    frame->width  = ctx->width;
    frame->height = ctx->height;

    திரும்பு 0;

#எனில் HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_எடு_Current(&dummy));
    திரும்பு res;
#endif
}

நிலையான எண்ணிக்கை AVPixelFormat cuda_frame_hw_format(மாறிலி AVFrame *frame)
{
    எனில் (!frame->hw_frames_ctx)
        திரும்பு AV_PIX_FMT_NONE;
    திரும்பு ((AVHWFramesContext *)frame->hw_frames_ctx->data)->format;
}

நிலையான முழு cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     எண்ணிக்கை AVHWFrameTransferDirection dir,
                                     எண்ணிக்கை AVPixelFormat **formats)
{
    எண்ணிக்கை AVPixelFormat *fmts;

    fmts = av_malloc_array(2, அளவு(*fmts));
    எனில் (!fmts)
        திரும்பு AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    திரும்பு 0;
}

நிலையான முழு cuda_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 மாறிலி AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    மாறிலி AVFrame *sw_frame = src->hw_frames_ctx ? dst : src;
    AVFrame *உச்சி_down = வெற்று, *bottom_up_dst = வெற்று;
    CUcontext dummy;
    முழு i, ret, copy_queued = 0, bottom_up = 0;

    {
        எண்ணிக்கை AVPixelFormat src_fmt = cuda_frame_hw_format(src);
        எண்ணிக்கை AVPixelFormat dst_fmt = cuda_frame_hw_format(dst);
        எனில் ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            திரும்பு AVERROR(ENOSYS);
    }

    க்கு (i = 0; i < FF_ARRAY_ELEMS(sw_frame->linesize); i++)
        bottom_up |= sw_frame->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    எனில் (bottom_up) {
        உச்சி_down = av_frame_alloc();
        எனில் (!உச்சி_down)
            திரும்பு AVERROR(ENOMEM);
        உச்சி_down->format = ctx->sw_format;
        உச்சி_down->width  = ctx->width;
        உச்சி_down->height = ctx->height;
        ret = av_hwframe_get_transfer_buffer((src->hw_frames_ctx ? src : dst)->hw_frames_ctx,
                                             உச்சி_down);
        எனில் (ret < 0)
            செல் free_உச்சி_down;
        உச்சி_down->width  = src->width;
        உச்சி_down->height = src->height;
        எனில் (sw_frame == src) {
            av_image_copy2(உச்சி_down->data, உச்சி_down->linesize, src->data, src->linesize,
                           ctx->sw_format, src->width, src->height);
            src = உச்சி_down;
        } இல்லையெனில் {
            bottom_up_dst = dst;
            dst           = உச்சி_down;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_தள்ளு_Current(hwctx->cuda_ctx));
    எனில் (ret < 0)
        செல் free_உச்சி_down;

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
    க்கு (i = 0; i < FF_ARRAY_ELEMS(src->data) && src->linesize[i]; i++) {
        முழு src_is_nonplanar_cuarray = 0;
        முழு dst_is_nonplanar_cuarray = 0;

        முழு bytewidth = av_image_get_linesize(ctx->sw_format, src->width, i);
        எனில் (bytewidth < 0) {
            ret = bytewidth;
            செல் fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .WidthInBytes  = bytewidth,
            .Height        = AV_CEIL_RSHIFT(src->height, ((i == 0 || i == 3) ? 0 : priv->shift_height)),
        };

        எனில் (src->format == AV_PIX_FMT_CUDA) {
            cpy.srcMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->data[i];
        } இல்லையெனில் எனில் (src->format == AV_PIX_FMT_CUARRAY) {
#எனில் HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->data[0], i);
            எனில் (cures == CUDA_ERROR_INVALID_மதிப்பு && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->data[0];
                src_is_nonplanar_cuarray = 1;
            } இல்லையெனில் எனில் (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                செல் fail;
            }

            cpy.srcMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#இல்லையெனில்
            ret = AVERROR(ENOSYS);
            செல் exit;
#endif
        } இல்லையெனில் {
            cpy.srcMemoryType = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->data[i];
        }

        எனில் (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dstMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->data[i];
        } இல்லையெனில் எனில் (dst->format == AV_PIX_FMT_CUARRAY) {
#எனில் HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->data[0], i);
            எனில் (cures == CUDA_ERROR_INVALID_மதிப்பு && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->data[0];
                dst_is_nonplanar_cuarray = 1;
            } இல்லையெனில் எனில் (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                செல் fail;
            }

            cpy.dstMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#இல்லையெனில்
            ret = AVERROR(ENOSYS);
            செல் exit;
#endif
        } இல்லையெனில் {
            cpy.dstMemoryType = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->data[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->stream));
        எனில் (ret < 0)
            செல் fail;
        copy_queued = 1;

        எனில் (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            நிறுத்து;
    }

    /* The caller may reuse host memory once the transfer returns. */
    எனில் (!src->hw_frames_ctx || !dst->hw_frames_ctx) {
        ret = CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
        எனில் (ret < 0)
            செல் exit;
    }

fail:
    எனில் (ret < 0 && copy_queued)
        CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
exit:
    CHECK_CU(cu->cu_Ctx_எடு_Current(&dummy));

    எனில் (bottom_up_dst && ret >= 0)
        av_image_copy2(bottom_up_dst->data, bottom_up_dst->linesize,
                       உச்சி_down->data, உச்சி_down->linesize,
                       ctx->sw_format, src->width, src->height);
free_உச்சி_down:
    av_frame_free(&உச்சி_down);

    திரும்பு ret;
}

நிலையான வெறுமை cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    எனில் (hwctx->p.internal) {
        CudaFunctions *cu = hwctx->internal.cuda_dl;

        எனில் (hwctx->internal.is_allocated && hwctx->p.cuda_ctx) {
            எனில் (hwctx->internal.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->internal.cuda_device));
            இல்லையெனில் எனில் (!(hwctx->internal.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = வெற்று;
        }

        cuda_free_functions(&hwctx->internal.cuda_dl);
        memset(&hwctx->internal, 0, அளவு(hwctx->internal));
        hwctx->p.internal = வெற்று;
    }
}

நிலையான முழு cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    முழு ret;

    hwctx->p.internal = &hwctx->internal;

    எனில் (!hwctx->internal.cuda_dl) {
        ret = cuda_load_functions(&hwctx->internal.cuda_dl, ctx);
        எனில் (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            செல் error;
        }
    }

    திரும்பு 0;

error:
    cuda_device_uninit(ctx);
    திரும்பு ret;
}

நிலையான முழு cuda_context_init(AVHWDeviceContext *device_ctx, முழு flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    முழு ret, dev_active = 0;
    unsigned முழு dev_flags = 0;

    மாறிலி unsigned முழு desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->internal->cuda_dl;

    hwctx->internal->flags = flags;

    எனில் (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->internal->cuda_device,
                       &dev_flags, &dev_active));
        எனில் (ret < 0)
            திரும்பு ret;

        எனில் (dev_active && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            திரும்பு AVERROR(ENOTSUP);
        } இல்லையெனில் எனில் (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cuDevicePrimaryCtxSetFlags(hwctx->internal->cuda_device,
                           desired_flags));
            எனில் (ret < 0)
                திரும்பு ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->internal->cuda_device));
        எனில் (ret < 0)
            திரும்பு ret;
    } இல்லையெனில் எனில் (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        எனில் (ret < 0)
            திரும்பு ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } இல்லையெனில் {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->internal->cuda_device));
        எனில் (ret < 0)
            திரும்பு ret;

        CHECK_CU(cu->cu_Ctx_எடு_Current(&dummy));
    }

    hwctx->internal->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->stream = வெற்று;

    திரும்பு 0;
}

நிலையான முழு cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, முழு *flags)
{
    AVDictionaryEntry *primary_ctx_opt = av_dict_get(opts, "primary_ctx", வெற்று, 0);
    AVDictionaryEntry *current_ctx_opt = av_dict_get(opts, "current_ctx", வெற்று, 0);

    முழு use_primary_ctx = 0, use_current_ctx = 0;
    எனில் (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->மதிப்பு, வெற்று, 10);

    எனில் (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->மதிப்பு, வெற்று, 10);

    எனில் (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        திரும்பு AVERROR(EINVAL);
    }

    எனில் (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } இல்லையெனில் எனில் (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    எனில் (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } இல்லையெனில் எனில் (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    திரும்பு 0;
}

நிலையான முழு cuda_device_create(AVHWDeviceContext *device_ctx,
                              மாறிலி எழுத்து *device,
                              AVDictionary *opts, முழு flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    முழு ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    எனில் (ret < 0)
        செல் error;

    எனில் (device)
        device_idx = strtol(device, வெற்று, 0);

    ret = cuda_device_init(device_ctx);
    எனில் (ret < 0)
        செல் error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    எனில் (ret < 0)
        செல் error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->internal->cuda_device, device_idx));
    எனில் (ret < 0)
        செல் error;

    ret = cuda_context_init(device_ctx, flags);
    எனில் (ret < 0)
        செல் error;

    திரும்பு 0;

error:
    cuda_device_uninit(device_ctx);
    திரும்பு ret;
}

நிலையான முழு cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              முழு flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    மாறிலி எழுத்து *src_uuid = வெற்று;
#எனில் CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#endif
    முழு ret, i, device_மொத்தம்;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    எனில் (ret < 0)
        செல் error;

#எனில் CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#endif

    தேர்வு (src_ctx->type) {
#எனில் CONFIG_VULKAN
#define TYPE PFN_vkGetPhysicalDeviceProperties2
    நிலை AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .pNext = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        நிறுத்து;
    }
#undef TYPE
#endif
    இயல்பு:
        ret = AVERROR(ENOSYS);
        செல் error;
    }

    எனில் (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        செல் error;
    }

    ret = cuda_device_init(device_ctx);
    எனில் (ret < 0)
        செல் error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    எனில் (ret < 0)
        செல் error;

    ret = CHECK_CU(cu->cu_Device_Get_மொத்தம்(&device_மொத்தம்));
    எனில் (ret < 0)
        செல் error;

    hwctx->internal->cuda_device = -1;
    க்கு (i = 0; i < device_மொத்தம்; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        எனில் (ret < 0)
            செல் error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        எனில் (ret < 0)
            செல் error;

        எனில் (memcmp(src_uuid, uuid.bytes, அளவு (uuid.bytes)) == 0) {
            hwctx->internal->cuda_device = dev;
            நிறுத்து;
        }
    }

    எனில் (hwctx->internal->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        செல் error;
    }

    ret = cuda_context_init(device_ctx, flags);
    எனில் (ret < 0)
        செல் error;

    திரும்பு 0;

error:
    cuda_device_uninit(device_ctx);
    திரும்பு ret;
}

மாறிலி HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_size    = அளவு(CUDADeviceContext),
    .frames_hwctx_size    = அளவு(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .frames_get_constraints = cuda_frames_get_constraints,
    .frames_init          = cuda_frames_init,
    .frames_uninit        = cuda_frames_uninit,
    .frames_get_buffer    = cuda_get_buffer,
    .transfer_get_formats = cuda_transfer_get_formats,
#எனில் HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_buffer_alloc = cuda_transfer_buffer_alloc,
#endif
    .transfer_data_to     = cuda_transfer_data,
    .transfer_data_from   = cuda_transfer_data,

    .pix_fmts             = (மாறிலி எண்ணிக்கை AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#எனில் HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#endif
                                                          AV_PIX_FMT_NONE },
};
