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

#অন্তর্ভাব "buffer.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "hwcontext.h"
#অন্তর্ভাব "hwcontext_internal.h"
#অন্তর্ভাব "hwcontext_cuda_internal.h"
#যদি CONFIG_VULKAN
#অন্তর্ভাব "hwcontext_vulkan.h"
#endif
#অন্তর্ভাব "cuda_check.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "pixdesc.h"
#অন্তর্ভাব "pixfmt.h"
#অন্তর্ভাব "imgutils.h"

প্রকারলেখ কাঠামো CUDAFramesContext {
    AVCUDAFramesContext p;

    পূর্ণসংখ্যা shift_width, shift_height;
    পূর্ণসংখ্যা tex_alignment;

    পূর্ণসংখ্যা cuarray_অঙ্ক_surfaces_used;
} CUDAFramesContext;

প্রকারলেখ কাঠামো CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADeviceContextInternal internal;
} CUDADeviceContext;



#define CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

স্থির CUarray_format cuda_array_format_for_pix_fmt(গণনা AVPixelFormat fmt);

স্থির পূর্ণসংখ্যা cuda_frames_get_constraints(AVHWDeviceContext *ctx,
                                       ধ্রুবক শূন্য *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ধ্রুবক AVCUDAHWConfig *config = hwconfig;
    গণনা AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    পূর্ণসংখ্যা n = 0;

    যদি (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, আকার(*constraints->valid_hw_formats));
        যদি (!constraints->valid_hw_formats)
            ফেরত AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } অন্যথা {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, আকার(*constraints->valid_hw_formats));
        যদি (!constraints->valid_hw_formats)
            ফেরত AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#যদি HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#অন্যথা
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#endif
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    আকার(*constraints->valid_sw_formats));
    যদি (!constraints->valid_sw_formats)
        ফেরত AVERROR(ENOMEM);

    n = 0;
    জন্য (পূর্ণসংখ্যা i = 0; i < AV_PIX_FMT_NB; i++) {
        যদি (req_fmt == AV_PIX_FMT_CUARRAY) {
            যদি (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } অন্যথা {
            ধ্রুবক AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            যদি (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#যদি CONFIG_VULKAN
    যদি (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#endif
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    ফেরত 0;
}

স্থির শূন্য cuda_বাফার_free(শূন্য *opaque, uint8_t *তথ্য)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ঠেলো_Current(hwctx->cuda_ctx));

    যদি (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)তথ্য;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } অন্যথা {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)তথ্য));
    }

    CHECK_CU(cu->cu_Ctx_বের_করো_Current(&dummy));
}

স্থির AVBufferRef *cuda_pool_alloc(শূন্য *opaque, size_t আকার_2)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    AVBufferRef *ret = ফাঁকা;
    CUcontext dummy = ফাঁকা;
    CUdeviceptr তথ্য;
    পূর্ণসংখ্যা err;

    err = CHECK_CU(cu->cu_Ctx_ঠেলো_Current(hwctx->cuda_ctx));
    যদি (err < 0)
        ফেরত ফাঁকা;

    যদি (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = av_mallocz(আকার(*desc));
        যদি (!desc)
            যাও done;

        যদি (priv->p.cuarray_অঙ্ক_surfaces > 0) {
            যদি (priv->cuarray_অঙ্ক_surfaces_used >= priv->p.cuarray_অঙ্ক_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                যাও done;
            }
            desc->সূচক = priv->cuarray_অঙ্ক_surfaces_used++;
            desc->array = priv->p.cuarray_surfaces[desc->সূচক];
        } অন্যথা {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            যদি (err < 0) {
                av_free(desc);
                যাও done;
            }
        }

        ret = av_বাফার_create((uint8_t*)desc, আকার(*desc), cuda_বাফার_free, ctx, 0);
        যদি (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            যাও done;
        }

        যাও done;
    }

    err = CHECK_CU(cu->cuMemAlloc(&তথ্য, আকার_2));
    যদি (err < 0)
        যাও done;

    ret = av_বাফার_create((uint8_t*)তথ্য, আকার_2, cuda_বাফার_free, ctx, 0);
    যদি (!ret) {
        CHECK_CU(cu->cuMemFree(তথ্য));
        যাও done;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
done:
    CHECK_CU(cu->cu_Ctx_বের_করো_Current(&dummy));
    ফেরত ret;
}

#যদি HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
স্থির শূন্য cuda_transfer_বাফার_free(শূন্য *opaque, uint8_t *তথ্য)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ঠেলো_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(তথ্য));
    CHECK_CU(cu->cu_Ctx_বের_করো_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
স্থির AVBufferRef *cuda_transfer_বাফার_alloc(শূন্য *device_ref, size_t আকার_2)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->তথ্য;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    AVBufferRef *ret = ফাঁকা;
    CUcontext dummy;
    শূন্য *host;

    যদি (CHECK_CU(cu->cu_Ctx_ঠেলো_Current(hwctx->cuda_ctx)) < 0)
        ফেরত av_বাফার_alloc(আকার_2);

    যদি (CHECK_CU(cu->cuMemHostAlloc(&host, আকার_2, 0)) >= 0) {
        ret = av_বাফার_create(host, আকার_2, cuda_transfer_বাফার_free, device_ctx, 0);
        যদি (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_বের_করো_Current(&dummy));
    ফেরত ret ? ret : av_বাফার_alloc(আকার_2);
}
#endif

স্থির শূন্য cuda_frames_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    যদি (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_ঠেলো_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        জন্য (পূর্ণসংখ্যা i = priv->cuarray_অঙ্ক_surfaces_used; i < priv->p.cuarray_অঙ্ক_surfaces; i++)
            যদি (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_বের_করো_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_অঙ্ক_surfaces = 0;
    }
}

স্থির CUarray_format cuda_array_format_for_pix_fmt(গণনা AVPixelFormat fmt)
{
    নির্বাচন (fmt) {
#যদি HAVE_FFNVCODEC_CUARRAY
    ক্ষেত্র AV_PIX_FMT_NV12:      ফেরত CU_AD_FORMAT_NV12;
    ক্ষেত্র AV_PIX_FMT_P010:
    ক্ষেত্র AV_PIX_FMT_P012:
    ক্ষেত্র AV_PIX_FMT_P016:      ফেরত CU_AD_FORMAT_P016;
    ক্ষেত্র AV_PIX_FMT_NV16:      ফেরত CU_AD_FORMAT_NV16;
    ক্ষেত্র AV_PIX_FMT_P210:
    ক্ষেত্র AV_PIX_FMT_P212:
    ক্ষেত্র AV_PIX_FMT_P216:      ফেরত CU_AD_FORMAT_P216;
    ক্ষেত্র AV_PIX_FMT_NV24:      ফেরত CU_AD_FORMAT_YUV444_8BIT_SEMIPLANAR;
    ক্ষেত্র AV_PIX_FMT_P410:
    ক্ষেত্র AV_PIX_FMT_P412:
    ক্ষেত্র AV_PIX_FMT_P416:      ফেরত CU_AD_FORMAT_YUV444_16BIT_SEMIPLANAR;
    ক্ষেত্র AV_PIX_FMT_YUV420P:   ফেরত CU_AD_FORMAT_UINT8_PLANAR_420;
    ক্ষেত্র AV_PIX_FMT_YUV422P:   ফেরত CU_AD_FORMAT_UINT8_PLANAR_422;
    ক্ষেত্র AV_PIX_FMT_YUV444P:   ফেরত CU_AD_FORMAT_UINT8_PLANAR_444;
    ক্ষেত্র AV_PIX_FMT_YUV420P10: ফেরত CU_AD_FORMAT_UINT16_PLANAR_420;
    ক্ষেত্র AV_PIX_FMT_YUV422P10: ফেরত CU_AD_FORMAT_UINT16_PLANAR_422;
    ক্ষেত্র AV_PIX_FMT_YUV444P10:
    ক্ষেত্র AV_PIX_FMT_YUV444P10MSB:
    ক্ষেত্র AV_PIX_FMT_YUV444P12MSB:
    ক্ষেত্র AV_PIX_FMT_YUV444P16: ফেরত CU_AD_FORMAT_UINT16_PLANAR_444;
    ক্ষেত্র AV_PIX_FMT_0RGB32:
    ক্ষেত্র AV_PIX_FMT_0BGR32:
    ক্ষেত্র AV_PIX_FMT_RGB32:
    ক্ষেত্র AV_PIX_FMT_BGR32:     ফেরত CU_AD_FORMAT_UNSIGNED_INT8;
#endif
    পূর্বনির্ধারিত:                   ফেরত 0;
    }
}

#যদি HAVE_FFNVCODEC_CUARRAY
স্থির unsigned পূর্ণসংখ্যা cuda_array_numchannels_for_pix_fmt(গণনা AVPixelFormat fmt)
{
    নির্বাচন (fmt) {
    ক্ষেত্র AV_PIX_FMT_0RGB32:
    ক্ষেত্র AV_PIX_FMT_0BGR32:
    ক্ষেত্র AV_PIX_FMT_RGB32:
    ক্ষেত্র AV_PIX_FMT_BGR32:     ফেরত 4;
    পূর্বনির্ধারিত:                   ফেরত 3;
    }
}
#endif

স্থির পূর্ণসংখ্যা cuda_frames_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    ধ্রুবক AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    পূর্ণসংখ্যা err;

    যদি (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        ফেরত AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    যদি (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        ফেরত AVERROR(ENOSYS);
    }

#যদি HAVE_FFNVCODEC_CUARRAY
    যদি (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        ফেরত AVERROR(ENOSYS);
    }
#অন্যথা
    যদি (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        ফেরত AVERROR(ENOSYS);
    }
#endif

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->internal->cuda_device));
    যদি (err < 0)
        ফেরত err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    যদি (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->shift_width, &priv->shift_height);

#যদি HAVE_FFNVCODEC_CUARRAY
    যদি (ctx->format == AV_PIX_FMT_CUARRAY) {
        যদি (!priv->p.cuarray_desc.Width)
            priv->p.cuarray_desc.Width = ctx->width;
        যদি (!priv->p.cuarray_desc.Height)
            priv->p.cuarray_desc.Height = ctx->height;
        যদি (!priv->p.cuarray_desc.অঙ্ক_Channels)
            priv->p.cuarray_desc.অঙ্ক_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        যদি (priv->p.cuarray_desc.Depth) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            ফেরত AVERROR(EINVAL);
        }

        যদি (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        যদি (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            ফেরত AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    যদি (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_অঙ্ক_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_অঙ্ক_surfaces, আকার(*priv->p.cuarray_surfaces));
        যদি (!priv->p.cuarray_surfaces)
            ফেরত AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_ঠেলো_Current(hwctx->cuda_ctx));
        যদি (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            ফেরত err;
        }

        জন্য (পূর্ণসংখ্যা i = 0; i < priv->p.cuarray_অঙ্ক_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            যদি (err < 0) {
                জন্য (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_বের_করো_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                ফেরত err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_বের_করো_Current(&dummy));
        যদি (err < 0)
            যাও fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_অঙ্ক_surfaces, priv->p.cuarray_desc.Width, priv->p.cuarray_desc.Height);
    }
#endif

    যদি (!ctx->pool) {
        পূর্ণসংখ্যা আকার_2 = av_image_get_বাফার_আকার(ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        যদি (আকার_2 < 0) {
            err = আকার_2;
            যাও fail;
        }

        ffhwframesctx(ctx)->pool_internal =
            av_বাফার_pool_init2(আকার_2, ctx, cuda_pool_alloc, ফাঁকা);
        যদি (!ffhwframesctx(ctx)->pool_internal) {
            err = AVERROR(ENOMEM);
            যাও fail;
        }
    }

    ফেরত 0;

fail:
    cuda_frames_uninit(ctx);
    ফেরত err;
}

স্থির পূর্ণসংখ্যা cuda_get_বাফার(AVHWFramesContext *ctx, AVFrame *frame)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#যদি HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;
#endif
    পূর্ণসংখ্যা res;

    frame->buf[0] = av_বাফার_pool_get(ctx->pool);
    যদি (!frame->buf[0])
        ফেরত AVERROR(ENOMEM);

    যদি (ctx->format == AV_PIX_FMT_CUARRAY) {
#যদি HAVE_FFNVCODEC_CUARRAY
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)frame->buf[0]->তথ্য;
        যদি (!desc) {
            frame->format = ctx->format;
            frame->width  = ctx->width;
            frame->height = ctx->height;
            ফেরত 0;
        }
        frame->তথ্য[0] = (uint8_t*)desc->array;
        frame->তথ্য[1] = (uint8_t*)desc->সূচক;

        res = CHECK_CU(cu->cu_Ctx_ঠেলো_Current(hwctx->cuda_ctx));
        যদি (res < 0)
            ফেরত res;

        জন্য (পূর্ণসংখ্যা i = 0; i < FF_ARRAY_ELEMS(frame->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            যদি (arr_plane_res == CUDA_ERROR_INVALID_মান) {
                যদি (i > 0)
                    বিরতি;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                যদি (res < 0)
                    যাও fail;
            } অন্যথা যদি (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                যাও fail;
            } অন্যথা {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                যদি (res < 0)
                    যাও fail;
            }

            পূর্ণসংখ্যা elem_আকার = ff_cuda_cuarray_elem_আকার(plane_desc.Format);
            যদি (elem_আকার <= 0) {
                res = AVERROR_BUG;
                যাও fail;
            }

            frame->linesize[i] = plane_desc.Width * plane_desc.অঙ্ক_Channels * elem_আকার;

            যদি (arr_plane_res == CUDA_ERROR_INVALID_মান)
                বিরতি;
        }

        res = CHECK_CU(cu->cu_Ctx_বের_করো_Current(&dummy));
        যদি (res < 0)
            ফেরত res;
#অন্যথা
        ফেরত AVERROR(ENOSYS);
#endif
    } অন্যথা {
        res = av_image_fill_arrays(frame->তথ্য, frame->linesize, frame->buf[0]->তথ্য,
                                   ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        যদি (res < 0)
            ফেরত res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        যদি (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
            frame->তথ্য[2]     = frame->তথ্য[1];
            frame->তথ্য[1]     = frame->তথ্য[2] + frame->linesize[2] * AV_CEIL_RSHIFT(ctx->height, 1);
        }
    }

    frame->format = ctx->format;
    frame->width  = ctx->width;
    frame->height = ctx->height;

    ফেরত 0;

#যদি HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_বের_করো_Current(&dummy));
    ফেরত res;
#endif
}

স্থির গণনা AVPixelFormat cuda_frame_hw_format(ধ্রুবক AVFrame *frame)
{
    যদি (!frame->hw_frames_ctx)
        ফেরত AV_PIX_FMT_NONE;
    ফেরত ((AVHWFramesContext *)frame->hw_frames_ctx->তথ্য)->format;
}

স্থির পূর্ণসংখ্যা cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     গণনা AVHWFrameTransferDirection dir,
                                     গণনা AVPixelFormat **formats)
{
    গণনা AVPixelFormat *fmts;

    fmts = av_malloc_array(2, আকার(*fmts));
    যদি (!fmts)
        ফেরত AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা cuda_transfer_তথ্য(AVHWFramesContext *ctx, AVFrame *dst,
                                 ধ্রুবক AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    ধ্রুবক AVFrame *sw_frame = src->hw_frames_ctx ? dst : src;
    AVFrame *শীর্ষ_down = ফাঁকা, *bottom_up_dst = ফাঁকা;
    CUcontext dummy;
    পূর্ণসংখ্যা i, ret, copy_queued = 0, bottom_up = 0;

    {
        গণনা AVPixelFormat src_fmt = cuda_frame_hw_format(src);
        গণনা AVPixelFormat dst_fmt = cuda_frame_hw_format(dst);
        যদি ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            ফেরত AVERROR(ENOSYS);
    }

    জন্য (i = 0; i < FF_ARRAY_ELEMS(sw_frame->linesize); i++)
        bottom_up |= sw_frame->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    যদি (bottom_up) {
        শীর্ষ_down = av_frame_alloc();
        যদি (!শীর্ষ_down)
            ফেরত AVERROR(ENOMEM);
        শীর্ষ_down->format = ctx->sw_format;
        শীর্ষ_down->width  = ctx->width;
        শীর্ষ_down->height = ctx->height;
        ret = av_hwframe_get_transfer_বাফার((src->hw_frames_ctx ? src : dst)->hw_frames_ctx,
                                             শীর্ষ_down);
        যদি (ret < 0)
            যাও free_শীর্ষ_down;
        শীর্ষ_down->width  = src->width;
        শীর্ষ_down->height = src->height;
        যদি (sw_frame == src) {
            av_image_copy2(শীর্ষ_down->তথ্য, শীর্ষ_down->linesize, src->তথ্য, src->linesize,
                           ctx->sw_format, src->width, src->height);
            src = শীর্ষ_down;
        } অন্যথা {
            bottom_up_dst = dst;
            dst           = শীর্ষ_down;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_ঠেলো_Current(hwctx->cuda_ctx));
    যদি (ret < 0)
        যাও free_শীর্ষ_down;

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
    জন্য (i = 0; i < FF_ARRAY_ELEMS(src->তথ্য) && src->linesize[i]; i++) {
        পূর্ণসংখ্যা src_is_nonplanar_cuarray = 0;
        পূর্ণসংখ্যা dst_is_nonplanar_cuarray = 0;

        পূর্ণসংখ্যা bytewidth = av_image_get_linesize(ctx->sw_format, src->width, i);
        যদি (bytewidth < 0) {
            ret = bytewidth;
            যাও fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .WidthInBytes  = bytewidth,
            .Height        = AV_CEIL_RSHIFT(src->height, ((i == 0 || i == 3) ? 0 : priv->shift_height)),
        };

        যদি (src->format == AV_PIX_FMT_CUDA) {
            cpy.srcMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->তথ্য[i];
        } অন্যথা যদি (src->format == AV_PIX_FMT_CUARRAY) {
#যদি HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->তথ্য[0], i);
            যদি (cures == CUDA_ERROR_INVALID_মান && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->তথ্য[0];
                src_is_nonplanar_cuarray = 1;
            } অন্যথা যদি (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                যাও fail;
            }

            cpy.srcMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#অন্যথা
            ret = AVERROR(ENOSYS);
            যাও exit;
#endif
        } অন্যথা {
            cpy.srcMemoryType = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->তথ্য[i];
        }

        যদি (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dstMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->তথ্য[i];
        } অন্যথা যদি (dst->format == AV_PIX_FMT_CUARRAY) {
#যদি HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->তথ্য[0], i);
            যদি (cures == CUDA_ERROR_INVALID_মান && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->তথ্য[0];
                dst_is_nonplanar_cuarray = 1;
            } অন্যথা যদি (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                যাও fail;
            }

            cpy.dstMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#অন্যথা
            ret = AVERROR(ENOSYS);
            যাও exit;
#endif
        } অন্যথা {
            cpy.dstMemoryType = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->তথ্য[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->stream));
        যদি (ret < 0)
            যাও fail;
        copy_queued = 1;

        যদি (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            বিরতি;
    }

    /* The caller may reuse host memory once the transfer returns. */
    যদি (!src->hw_frames_ctx || !dst->hw_frames_ctx) {
        ret = CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
        যদি (ret < 0)
            যাও exit;
    }

fail:
    যদি (ret < 0 && copy_queued)
        CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
exit:
    CHECK_CU(cu->cu_Ctx_বের_করো_Current(&dummy));

    যদি (bottom_up_dst && ret >= 0)
        av_image_copy2(bottom_up_dst->তথ্য, bottom_up_dst->linesize,
                       শীর্ষ_down->তথ্য, শীর্ষ_down->linesize,
                       ctx->sw_format, src->width, src->height);
free_শীর্ষ_down:
    av_frame_free(&শীর্ষ_down);

    ফেরত ret;
}

স্থির শূন্য cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    যদি (hwctx->p.internal) {
        CudaFunctions *cu = hwctx->internal.cuda_dl;

        যদি (hwctx->internal.is_allocated && hwctx->p.cuda_ctx) {
            যদি (hwctx->internal.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->internal.cuda_device));
            অন্যথা যদি (!(hwctx->internal.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = ফাঁকা;
        }

        cuda_free_functions(&hwctx->internal.cuda_dl);
        memset(&hwctx->internal, 0, আকার(hwctx->internal));
        hwctx->p.internal = ফাঁকা;
    }
}

স্থির পূর্ণসংখ্যা cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    পূর্ণসংখ্যা ret;

    hwctx->p.internal = &hwctx->internal;

    যদি (!hwctx->internal.cuda_dl) {
        ret = cuda_load_functions(&hwctx->internal.cuda_dl, ctx);
        যদি (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            যাও error;
        }
    }

    ফেরত 0;

error:
    cuda_device_uninit(ctx);
    ফেরত ret;
}

স্থির পূর্ণসংখ্যা cuda_context_init(AVHWDeviceContext *device_ctx, পূর্ণসংখ্যা flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    পূর্ণসংখ্যা ret, dev_active = 0;
    unsigned পূর্ণসংখ্যা dev_flags = 0;

    ধ্রুবক unsigned পূর্ণসংখ্যা desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->internal->cuda_dl;

    hwctx->internal->flags = flags;

    যদি (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->internal->cuda_device,
                       &dev_flags, &dev_active));
        যদি (ret < 0)
            ফেরত ret;

        যদি (dev_active && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            ফেরত AVERROR(ENOTSUP);
        } অন্যথা যদি (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cuDevicePrimaryCtxSetFlags(hwctx->internal->cuda_device,
                           desired_flags));
            যদি (ret < 0)
                ফেরত ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->internal->cuda_device));
        যদি (ret < 0)
            ফেরত ret;
    } অন্যথা যদি (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        যদি (ret < 0)
            ফেরত ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } অন্যথা {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->internal->cuda_device));
        যদি (ret < 0)
            ফেরত ret;

        CHECK_CU(cu->cu_Ctx_বের_করো_Current(&dummy));
    }

    hwctx->internal->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->stream = ফাঁকা;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, পূর্ণসংখ্যা *flags)
{
    AVDictionaryEntry *primary_ctx_opt = av_dict_get(opts, "primary_ctx", ফাঁকা, 0);
    AVDictionaryEntry *current_ctx_opt = av_dict_get(opts, "current_ctx", ফাঁকা, 0);

    পূর্ণসংখ্যা use_primary_ctx = 0, use_current_ctx = 0;
    যদি (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->মান, ফাঁকা, 10);

    যদি (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->মান, ফাঁকা, 10);

    যদি (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        ফেরত AVERROR(EINVAL);
    }

    যদি (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } অন্যথা যদি (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    যদি (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } অন্যথা যদি (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা cuda_device_create(AVHWDeviceContext *device_ctx,
                              ধ্রুবক অক্ষর *device,
                              AVDictionary *opts, পূর্ণসংখ্যা flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    পূর্ণসংখ্যা ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    যদি (ret < 0)
        যাও error;

    যদি (device)
        device_idx = strtol(device, ফাঁকা, 0);

    ret = cuda_device_init(device_ctx);
    যদি (ret < 0)
        যাও error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    যদি (ret < 0)
        যাও error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->internal->cuda_device, device_idx));
    যদি (ret < 0)
        যাও error;

    ret = cuda_context_init(device_ctx, flags);
    যদি (ret < 0)
        যাও error;

    ফেরত 0;

error:
    cuda_device_uninit(device_ctx);
    ফেরত ret;
}

স্থির পূর্ণসংখ্যা cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              পূর্ণসংখ্যা flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ধ্রুবক অক্ষর *src_uuid = ফাঁকা;
#যদি CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#endif
    পূর্ণসংখ্যা ret, i, device_গুনতি;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    যদি (ret < 0)
        যাও error;

#যদি CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#endif

    নির্বাচন (src_ctx->type) {
#যদি CONFIG_VULKAN
#define TYPE PFN_vkGetPhysicalDeviceProperties2
    ক্ষেত্র AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .p_পরবর্তী = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        বিরতি;
    }
#undef TYPE
#endif
    পূর্বনির্ধারিত:
        ret = AVERROR(ENOSYS);
        যাও error;
    }

    যদি (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        যাও error;
    }

    ret = cuda_device_init(device_ctx);
    যদি (ret < 0)
        যাও error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    যদি (ret < 0)
        যাও error;

    ret = CHECK_CU(cu->cu_Device_Get_গুনতি(&device_গুনতি));
    যদি (ret < 0)
        যাও error;

    hwctx->internal->cuda_device = -1;
    জন্য (i = 0; i < device_গুনতি; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        যদি (ret < 0)
            যাও error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        যদি (ret < 0)
            যাও error;

        যদি (memcmp(src_uuid, uuid.bytes, আকার (uuid.bytes)) == 0) {
            hwctx->internal->cuda_device = dev;
            বিরতি;
        }
    }

    যদি (hwctx->internal->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        যাও error;
    }

    ret = cuda_context_init(device_ctx, flags);
    যদি (ret < 0)
        যাও error;

    ফেরত 0;

error:
    cuda_device_uninit(device_ctx);
    ফেরত ret;
}

ধ্রুবক HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_আকার    = আকার(CUDADeviceContext),
    .frames_hwctx_আকার    = আকার(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .frames_get_constraints = cuda_frames_get_constraints,
    .frames_init          = cuda_frames_init,
    .frames_uninit        = cuda_frames_uninit,
    .frames_get_বাফার    = cuda_get_বাফার,
    .transfer_get_formats = cuda_transfer_get_formats,
#যদি HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_বাফার_alloc = cuda_transfer_বাফার_alloc,
#endif
    .transfer_তথ্য_to     = cuda_transfer_তথ্য,
    .transfer_তথ্য_from   = cuda_transfer_তথ্য,

    .pix_fmts             = (ধ্রুবক গণনা AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#যদি HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#endif
                                                          AV_PIX_FMT_NONE },
};
