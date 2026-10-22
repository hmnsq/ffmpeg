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

#અન્તર્ભાવ "buffer.h"
#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "hwcontext.h"
#અન્તર્ભાવ "hwcontext_internal.h"
#અન્તર્ભાવ "hwcontext_cuda_internal.h"
#જો CONFIG_VULKAN
#અન્તર્ભાવ "hwcontext_vulkan.h"
#endif
#અન્તર્ભાવ "cuda_check.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "pixdesc.h"
#અન્તર્ભાવ "pixfmt.h"
#અન્તર્ભાવ "imgutils.h"

પ્રકારવ્યાખ્યા સંરચના CUDAFramesContext {
    AVCUDAFramesContext p;

    પૂર્ણાંક shift_width, shift_height;
    પૂર્ણાંક tex_alignment;

    પૂર્ણાંક cuarray_અંક_surfaces_used;
} CUDAFramesContext;

પ્રકારવ્યાખ્યા સંરચના CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADeviceContextInternal internal;
} CUDADeviceContext;



#define CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

સ્થિર CUarray_format cuda_array_format_for_pix_fmt(ગણના AVPixelFormat fmt);

સ્થિર પૂર્ણાંક cuda_frames_get_constraints(AVHWDeviceContext *ctx,
                                       અચલ શૂન્ય *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    અચલ AVCUDAHWConfig *config = hwconfig;
    ગણના AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    પૂર્ણાંક n = 0;

    જો (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, કદ(*constraints->valid_hw_formats));
        જો (!constraints->valid_hw_formats)
            પાછા AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } નહીંતર {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, કદ(*constraints->valid_hw_formats));
        જો (!constraints->valid_hw_formats)
            પાછા AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#જો HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#નહીંતર
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#endif
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    કદ(*constraints->valid_sw_formats));
    જો (!constraints->valid_sw_formats)
        પાછા AVERROR(ENOMEM);

    n = 0;
    માટે (પૂર્ણાંક i = 0; i < AV_PIX_FMT_NB; i++) {
        જો (req_fmt == AV_PIX_FMT_CUARRAY) {
            જો (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } નહીંતર {
            અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            જો (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#જો CONFIG_VULKAN
    જો (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#endif
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    પાછા 0;
}

સ્થિર શૂન્ય cuda_buffer_free(શૂન્ય *opaque, uint8_t *data)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ધકેલો_Current(hwctx->cuda_ctx));

    જો (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)data;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } નહીંતર {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)data));
    }

    CHECK_CU(cu->cu_Ctx_કાઢો_Current(&dummy));
}

સ્થિર AVBufferRef *cuda_pool_alloc(શૂન્ય *opaque, size_t size)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    AVBufferRef *ret = ખાલી;
    CUcontext dummy = ખાલી;
    CUdeviceptr data;
    પૂર્ણાંક err;

    err = CHECK_CU(cu->cu_Ctx_ધકેલો_Current(hwctx->cuda_ctx));
    જો (err < 0)
        પાછા ખાલી;

    જો (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = av_mallocz(કદ(*desc));
        જો (!desc)
            જાઓ done;

        જો (priv->p.cuarray_અંક_surfaces > 0) {
            જો (priv->cuarray_અંક_surfaces_used >= priv->p.cuarray_અંક_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                જાઓ done;
            }
            desc->index = priv->cuarray_અંક_surfaces_used++;
            desc->array = priv->p.cuarray_surfaces[desc->index];
        } નહીંતર {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            જો (err < 0) {
                av_free(desc);
                જાઓ done;
            }
        }

        ret = av_buffer_create((uint8_t*)desc, કદ(*desc), cuda_buffer_free, ctx, 0);
        જો (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            જાઓ done;
        }

        જાઓ done;
    }

    err = CHECK_CU(cu->cuMemAlloc(&data, size));
    જો (err < 0)
        જાઓ done;

    ret = av_buffer_create((uint8_t*)data, size, cuda_buffer_free, ctx, 0);
    જો (!ret) {
        CHECK_CU(cu->cuMemFree(data));
        જાઓ done;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
done:
    CHECK_CU(cu->cu_Ctx_કાઢો_Current(&dummy));
    પાછા ret;
}

#જો HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
સ્થિર શૂન્ય cuda_transfer_buffer_free(શૂન્ય *opaque, uint8_t *data)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ધકેલો_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(data));
    CHECK_CU(cu->cu_Ctx_કાઢો_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
સ્થિર AVBufferRef *cuda_transfer_buffer_alloc(શૂન્ય *device_ref, size_t size)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->data;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    AVBufferRef *ret = ખાલી;
    CUcontext dummy;
    શૂન્ય *host;

    જો (CHECK_CU(cu->cu_Ctx_ધકેલો_Current(hwctx->cuda_ctx)) < 0)
        પાછા av_buffer_alloc(size);

    જો (CHECK_CU(cu->cuMemHostAlloc(&host, size, 0)) >= 0) {
        ret = av_buffer_create(host, size, cuda_transfer_buffer_free, device_ctx, 0);
        જો (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_કાઢો_Current(&dummy));
    પાછા ret ? ret : av_buffer_alloc(size);
}
#endif

સ્થિર શૂન્ય cuda_frames_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    જો (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_ધકેલો_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        માટે (પૂર્ણાંક i = priv->cuarray_અંક_surfaces_used; i < priv->p.cuarray_અંક_surfaces; i++)
            જો (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_કાઢો_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_અંક_surfaces = 0;
    }
}

સ્થિર CUarray_format cuda_array_format_for_pix_fmt(ગણના AVPixelFormat fmt)
{
    પસંદગી (fmt) {
#જો HAVE_FFNVCODEC_CUARRAY
    સ્થિતિ AV_PIX_FMT_NV12:      પાછા CU_AD_FORMAT_NV12;
    સ્થિતિ AV_PIX_FMT_P010:
    સ્થિતિ AV_PIX_FMT_P012:
    સ્થિતિ AV_PIX_FMT_P016:      પાછા CU_AD_FORMAT_P016;
    સ્થિતિ AV_PIX_FMT_NV16:      પાછા CU_AD_FORMAT_NV16;
    સ્થિતિ AV_PIX_FMT_P210:
    સ્થિતિ AV_PIX_FMT_P212:
    સ્થિતિ AV_PIX_FMT_P216:      પાછા CU_AD_FORMAT_P216;
    સ્થિતિ AV_PIX_FMT_NV24:      પાછા CU_AD_FORMAT_YUV444_8BIT_SEMIPLANAR;
    સ્થિતિ AV_PIX_FMT_P410:
    સ્થિતિ AV_PIX_FMT_P412:
    સ્થિતિ AV_PIX_FMT_P416:      પાછા CU_AD_FORMAT_YUV444_16BIT_SEMIPLANAR;
    સ્થિતિ AV_PIX_FMT_YUV420P:   પાછા CU_AD_FORMAT_UINT8_PLANAR_420;
    સ્થિતિ AV_PIX_FMT_YUV422P:   પાછા CU_AD_FORMAT_UINT8_PLANAR_422;
    સ્થિતિ AV_PIX_FMT_YUV444P:   પાછા CU_AD_FORMAT_UINT8_PLANAR_444;
    સ્થિતિ AV_PIX_FMT_YUV420P10: પાછા CU_AD_FORMAT_UINT16_PLANAR_420;
    સ્થિતિ AV_PIX_FMT_YUV422P10: પાછા CU_AD_FORMAT_UINT16_PLANAR_422;
    સ્થિતિ AV_PIX_FMT_YUV444P10:
    સ્થિતિ AV_PIX_FMT_YUV444P10MSB:
    સ્થિતિ AV_PIX_FMT_YUV444P12MSB:
    સ્થિતિ AV_PIX_FMT_YUV444P16: પાછા CU_AD_FORMAT_UINT16_PLANAR_444;
    સ્થિતિ AV_PIX_FMT_0RGB32:
    સ્થિતિ AV_PIX_FMT_0BGR32:
    સ્થિતિ AV_PIX_FMT_RGB32:
    સ્થિતિ AV_PIX_FMT_BGR32:     પાછા CU_AD_FORMAT_UNSIGNED_INT8;
#endif
    મૂળભૂત:                   પાછા 0;
    }
}

#જો HAVE_FFNVCODEC_CUARRAY
સ્થિર unsigned પૂર્ણાંક cuda_array_numchannels_for_pix_fmt(ગણના AVPixelFormat fmt)
{
    પસંદગી (fmt) {
    સ્થિતિ AV_PIX_FMT_0RGB32:
    સ્થિતિ AV_PIX_FMT_0BGR32:
    સ્થિતિ AV_PIX_FMT_RGB32:
    સ્થિતિ AV_PIX_FMT_BGR32:     પાછા 4;
    મૂળભૂત:                   પાછા 3;
    }
}
#endif

સ્થિર પૂર્ણાંક cuda_frames_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    પૂર્ણાંક err;

    જો (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        પાછા AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    જો (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        પાછા AVERROR(ENOSYS);
    }

#જો HAVE_FFNVCODEC_CUARRAY
    જો (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        પાછા AVERROR(ENOSYS);
    }
#નહીંતર
    જો (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        પાછા AVERROR(ENOSYS);
    }
#endif

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->internal->cuda_device));
    જો (err < 0)
        પાછા err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    જો (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->shift_width, &priv->shift_height);

#જો HAVE_FFNVCODEC_CUARRAY
    જો (ctx->format == AV_PIX_FMT_CUARRAY) {
        જો (!priv->p.cuarray_desc.Width)
            priv->p.cuarray_desc.Width = ctx->width;
        જો (!priv->p.cuarray_desc.Height)
            priv->p.cuarray_desc.Height = ctx->height;
        જો (!priv->p.cuarray_desc.અંક_Channels)
            priv->p.cuarray_desc.અંક_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        જો (priv->p.cuarray_desc.Depth) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            પાછા AVERROR(EINVAL);
        }

        જો (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        જો (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            પાછા AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    જો (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_અંક_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_અંક_surfaces, કદ(*priv->p.cuarray_surfaces));
        જો (!priv->p.cuarray_surfaces)
            પાછા AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_ધકેલો_Current(hwctx->cuda_ctx));
        જો (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            પાછા err;
        }

        માટે (પૂર્ણાંક i = 0; i < priv->p.cuarray_અંક_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            જો (err < 0) {
                માટે (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_કાઢો_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                પાછા err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_કાઢો_Current(&dummy));
        જો (err < 0)
            જાઓ fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_અંક_surfaces, priv->p.cuarray_desc.Width, priv->p.cuarray_desc.Height);
    }
#endif

    જો (!ctx->pool) {
        પૂર્ણાંક size = av_image_get_buffer_size(ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        જો (size < 0) {
            err = size;
            જાઓ fail;
        }

        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(size, ctx, cuda_pool_alloc, ખાલી);
        જો (!ffhwframesctx(ctx)->pool_internal) {
            err = AVERROR(ENOMEM);
            જાઓ fail;
        }
    }

    પાછા 0;

fail:
    cuda_frames_uninit(ctx);
    પાછા err;
}

સ્થિર પૂર્ણાંક cuda_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#જો HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;
#endif
    પૂર્ણાંક res;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    જો (!frame->buf[0])
        પાછા AVERROR(ENOMEM);

    જો (ctx->format == AV_PIX_FMT_CUARRAY) {
#જો HAVE_FFNVCODEC_CUARRAY
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)frame->buf[0]->data;
        જો (!desc) {
            frame->format = ctx->format;
            frame->width  = ctx->width;
            frame->height = ctx->height;
            પાછા 0;
        }
        frame->data[0] = (uint8_t*)desc->array;
        frame->data[1] = (uint8_t*)desc->index;

        res = CHECK_CU(cu->cu_Ctx_ધકેલો_Current(hwctx->cuda_ctx));
        જો (res < 0)
            પાછા res;

        માટે (પૂર્ણાંક i = 0; i < FF_ARRAY_ELEMS(frame->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            જો (arr_plane_res == CUDA_ERROR_INVALID_કિંમત) {
                જો (i > 0)
                    તોડો;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                જો (res < 0)
                    જાઓ fail;
            } નહીંતર જો (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                જાઓ fail;
            } નહીંતર {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                જો (res < 0)
                    જાઓ fail;
            }

            પૂર્ણાંક elem_size = ff_cuda_cuarray_elem_size(plane_desc.Format);
            જો (elem_size <= 0) {
                res = AVERROR_BUG;
                જાઓ fail;
            }

            frame->linesize[i] = plane_desc.Width * plane_desc.અંક_Channels * elem_size;

            જો (arr_plane_res == CUDA_ERROR_INVALID_કિંમત)
                તોડો;
        }

        res = CHECK_CU(cu->cu_Ctx_કાઢો_Current(&dummy));
        જો (res < 0)
            પાછા res;
#નહીંતર
        પાછા AVERROR(ENOSYS);
#endif
    } નહીંતર {
        res = av_image_fill_arrays(frame->data, frame->linesize, frame->buf[0]->data,
                                   ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        જો (res < 0)
            પાછા res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        જો (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
            frame->data[2]     = frame->data[1];
            frame->data[1]     = frame->data[2] + frame->linesize[2] * AV_CEIL_RSHIFT(ctx->height, 1);
        }
    }

    frame->format = ctx->format;
    frame->width  = ctx->width;
    frame->height = ctx->height;

    પાછા 0;

#જો HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_કાઢો_Current(&dummy));
    પાછા res;
#endif
}

સ્થિર ગણના AVPixelFormat cuda_frame_hw_format(અચલ AVFrame *frame)
{
    જો (!frame->hw_frames_ctx)
        પાછા AV_PIX_FMT_NONE;
    પાછા ((AVHWFramesContext *)frame->hw_frames_ctx->data)->format;
}

સ્થિર પૂર્ણાંક cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     ગણના AVHWFrameTransferDirection dir,
                                     ગણના AVPixelFormat **formats)
{
    ગણના AVPixelFormat *fmts;

    fmts = av_malloc_array(2, કદ(*fmts));
    જો (!fmts)
        પાછા AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    પાછા 0;
}

સ્થિર પૂર્ણાંક cuda_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 અચલ AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    અચલ AVFrame *sw_frame = src->hw_frames_ctx ? dst : src;
    AVFrame *ટોચ_down = ખાલી, *bottom_up_dst = ખાલી;
    CUcontext dummy;
    પૂર્ણાંક i, ret, copy_queued = 0, bottom_up = 0;

    {
        ગણના AVPixelFormat src_fmt = cuda_frame_hw_format(src);
        ગણના AVPixelFormat dst_fmt = cuda_frame_hw_format(dst);
        જો ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            પાછા AVERROR(ENOSYS);
    }

    માટે (i = 0; i < FF_ARRAY_ELEMS(sw_frame->linesize); i++)
        bottom_up |= sw_frame->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    જો (bottom_up) {
        ટોચ_down = av_frame_alloc();
        જો (!ટોચ_down)
            પાછા AVERROR(ENOMEM);
        ટોચ_down->format = ctx->sw_format;
        ટોચ_down->width  = ctx->width;
        ટોચ_down->height = ctx->height;
        ret = av_hwframe_get_transfer_buffer((src->hw_frames_ctx ? src : dst)->hw_frames_ctx,
                                             ટોચ_down);
        જો (ret < 0)
            જાઓ free_ટોચ_down;
        ટોચ_down->width  = src->width;
        ટોચ_down->height = src->height;
        જો (sw_frame == src) {
            av_image_copy2(ટોચ_down->data, ટોચ_down->linesize, src->data, src->linesize,
                           ctx->sw_format, src->width, src->height);
            src = ટોચ_down;
        } નહીંતર {
            bottom_up_dst = dst;
            dst           = ટોચ_down;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_ધકેલો_Current(hwctx->cuda_ctx));
    જો (ret < 0)
        જાઓ free_ટોચ_down;

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
    માટે (i = 0; i < FF_ARRAY_ELEMS(src->data) && src->linesize[i]; i++) {
        પૂર્ણાંક src_is_nonplanar_cuarray = 0;
        પૂર્ણાંક dst_is_nonplanar_cuarray = 0;

        પૂર્ણાંક bytewidth = av_image_get_linesize(ctx->sw_format, src->width, i);
        જો (bytewidth < 0) {
            ret = bytewidth;
            જાઓ fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .WidthInBytes  = bytewidth,
            .Height        = AV_CEIL_RSHIFT(src->height, ((i == 0 || i == 3) ? 0 : priv->shift_height)),
        };

        જો (src->format == AV_PIX_FMT_CUDA) {
            cpy.srcMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->data[i];
        } નહીંતર જો (src->format == AV_PIX_FMT_CUARRAY) {
#જો HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->data[0], i);
            જો (cures == CUDA_ERROR_INVALID_કિંમત && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->data[0];
                src_is_nonplanar_cuarray = 1;
            } નહીંતર જો (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                જાઓ fail;
            }

            cpy.srcMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#નહીંતર
            ret = AVERROR(ENOSYS);
            જાઓ exit;
#endif
        } નહીંતર {
            cpy.srcMemoryType = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->data[i];
        }

        જો (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dstMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->data[i];
        } નહીંતર જો (dst->format == AV_PIX_FMT_CUARRAY) {
#જો HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->data[0], i);
            જો (cures == CUDA_ERROR_INVALID_કિંમત && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->data[0];
                dst_is_nonplanar_cuarray = 1;
            } નહીંતર જો (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                જાઓ fail;
            }

            cpy.dstMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#નહીંતર
            ret = AVERROR(ENOSYS);
            જાઓ exit;
#endif
        } નહીંતર {
            cpy.dstMemoryType = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->data[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->stream));
        જો (ret < 0)
            જાઓ fail;
        copy_queued = 1;

        જો (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            તોડો;
    }

    /* The caller may reuse host memory once the transfer returns. */
    જો (!src->hw_frames_ctx || !dst->hw_frames_ctx) {
        ret = CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
        જો (ret < 0)
            જાઓ exit;
    }

fail:
    જો (ret < 0 && copy_queued)
        CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
exit:
    CHECK_CU(cu->cu_Ctx_કાઢો_Current(&dummy));

    જો (bottom_up_dst && ret >= 0)
        av_image_copy2(bottom_up_dst->data, bottom_up_dst->linesize,
                       ટોચ_down->data, ટોચ_down->linesize,
                       ctx->sw_format, src->width, src->height);
free_ટોચ_down:
    av_frame_free(&ટોચ_down);

    પાછા ret;
}

સ્થિર શૂન્ય cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    જો (hwctx->p.internal) {
        CudaFunctions *cu = hwctx->internal.cuda_dl;

        જો (hwctx->internal.is_allocated && hwctx->p.cuda_ctx) {
            જો (hwctx->internal.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->internal.cuda_device));
            નહીંતર જો (!(hwctx->internal.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = ખાલી;
        }

        cuda_free_functions(&hwctx->internal.cuda_dl);
        memset(&hwctx->internal, 0, કદ(hwctx->internal));
        hwctx->p.internal = ખાલી;
    }
}

સ્થિર પૂર્ણાંક cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    પૂર્ણાંક ret;

    hwctx->p.internal = &hwctx->internal;

    જો (!hwctx->internal.cuda_dl) {
        ret = cuda_load_functions(&hwctx->internal.cuda_dl, ctx);
        જો (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            જાઓ error;
        }
    }

    પાછા 0;

error:
    cuda_device_uninit(ctx);
    પાછા ret;
}

સ્થિર પૂર્ણાંક cuda_context_init(AVHWDeviceContext *device_ctx, પૂર્ણાંક flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    પૂર્ણાંક ret, dev_active = 0;
    unsigned પૂર્ણાંક dev_flags = 0;

    અચલ unsigned પૂર્ણાંક desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->internal->cuda_dl;

    hwctx->internal->flags = flags;

    જો (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->internal->cuda_device,
                       &dev_flags, &dev_active));
        જો (ret < 0)
            પાછા ret;

        જો (dev_active && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            પાછા AVERROR(ENOTSUP);
        } નહીંતર જો (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cuDevicePrimaryCtxSetFlags(hwctx->internal->cuda_device,
                           desired_flags));
            જો (ret < 0)
                પાછા ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->internal->cuda_device));
        જો (ret < 0)
            પાછા ret;
    } નહીંતર જો (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        જો (ret < 0)
            પાછા ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } નહીંતર {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->internal->cuda_device));
        જો (ret < 0)
            પાછા ret;

        CHECK_CU(cu->cu_Ctx_કાઢો_Current(&dummy));
    }

    hwctx->internal->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->stream = ખાલી;

    પાછા 0;
}

સ્થિર પૂર્ણાંક cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, પૂર્ણાંક *flags)
{
    AVDictionaryEntry *primary_ctx_opt = av_dict_get(opts, "primary_ctx", ખાલી, 0);
    AVDictionaryEntry *current_ctx_opt = av_dict_get(opts, "current_ctx", ખાલી, 0);

    પૂર્ણાંક use_primary_ctx = 0, use_current_ctx = 0;
    જો (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->કિંમત, ખાલી, 10);

    જો (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->કિંમત, ખાલી, 10);

    જો (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        પાછા AVERROR(EINVAL);
    }

    જો (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } નહીંતર જો (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    જો (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } નહીંતર જો (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    પાછા 0;
}

સ્થિર પૂર્ણાંક cuda_device_create(AVHWDeviceContext *device_ctx,
                              અચલ અક્ષર *device,
                              AVDictionary *opts, પૂર્ણાંક flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    પૂર્ણાંક ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    જો (ret < 0)
        જાઓ error;

    જો (device)
        device_idx = strtol(device, ખાલી, 0);

    ret = cuda_device_init(device_ctx);
    જો (ret < 0)
        જાઓ error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    જો (ret < 0)
        જાઓ error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->internal->cuda_device, device_idx));
    જો (ret < 0)
        જાઓ error;

    ret = cuda_context_init(device_ctx, flags);
    જો (ret < 0)
        જાઓ error;

    પાછા 0;

error:
    cuda_device_uninit(device_ctx);
    પાછા ret;
}

સ્થિર પૂર્ણાંક cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              પૂર્ણાંક flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    અચલ અક્ષર *src_uuid = ખાલી;
#જો CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#endif
    પૂર્ણાંક ret, i, device_ગણતરી;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    જો (ret < 0)
        જાઓ error;

#જો CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#endif

    પસંદગી (src_ctx->type) {
#જો CONFIG_VULKAN
#define TYPE PFN_vkGetPhysicalDeviceProperties2
    સ્થિતિ AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .pNext = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        તોડો;
    }
#undef TYPE
#endif
    મૂળભૂત:
        ret = AVERROR(ENOSYS);
        જાઓ error;
    }

    જો (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        જાઓ error;
    }

    ret = cuda_device_init(device_ctx);
    જો (ret < 0)
        જાઓ error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    જો (ret < 0)
        જાઓ error;

    ret = CHECK_CU(cu->cu_Device_Get_ગણતરી(&device_ગણતરી));
    જો (ret < 0)
        જાઓ error;

    hwctx->internal->cuda_device = -1;
    માટે (i = 0; i < device_ગણતરી; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        જો (ret < 0)
            જાઓ error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        જો (ret < 0)
            જાઓ error;

        જો (memcmp(src_uuid, uuid.bytes, કદ (uuid.bytes)) == 0) {
            hwctx->internal->cuda_device = dev;
            તોડો;
        }
    }

    જો (hwctx->internal->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        જાઓ error;
    }

    ret = cuda_context_init(device_ctx, flags);
    જો (ret < 0)
        જાઓ error;

    પાછા 0;

error:
    cuda_device_uninit(device_ctx);
    પાછા ret;
}

અચલ HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_size    = કદ(CUDADeviceContext),
    .frames_hwctx_size    = કદ(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .frames_get_constraints = cuda_frames_get_constraints,
    .frames_init          = cuda_frames_init,
    .frames_uninit        = cuda_frames_uninit,
    .frames_get_buffer    = cuda_get_buffer,
    .transfer_get_formats = cuda_transfer_get_formats,
#જો HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_buffer_alloc = cuda_transfer_buffer_alloc,
#endif
    .transfer_data_to     = cuda_transfer_data,
    .transfer_data_from   = cuda_transfer_data,

    .pix_fmts             = (અચલ ગણના AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#જો HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#endif
                                                          AV_PIX_FMT_NONE },
};
