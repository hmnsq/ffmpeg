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

#ضمن "buffer.h"
#ضمن "common.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_internal.h"
#ضمن "hwcontext_cuda_internal.h"
#إذا CONFIG_VULKAN
#ضمن "hwcontext_vulkan.h"
#جيڪڏهن_پورو
#ضمن "cuda_check.h"
#ضمن "mem.h"
#ضمن "pixdesc.h"
#ضمن "pixfmt.h"
#ضمن "imgutils.h"

تعريفنوع بنية CUDAFramesContext {
    AVCUDAFramesContext p;

    صحيح سرڪايو_ويڪر, سرڪايو_اوچائي;
    صحيح tex_alignment;

    صحيح cuarray_انگ_surfaces_استعمال_ٿيل;
} CUDAFramesContext;

تعريفنوع بنية CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADevice_Context_اندروني اندروني;
} CUDADeviceContext;



#وصف_ڪريو CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

ساكن CUarray_format cuda_array_format_for_pix_fmt(تعداد AVPixelFormat fmt);

ساكن صحيح cuda_چوکٺا_get_constraints(AVHWDeviceContext *ctx,
                                       ثابت فراغ *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ثابت AVCUDAHWConfig *config = hwconfig;
    تعداد AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    صحيح n = 0;

    إذا (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
        إذا (!constraints->valid_hw_formats)
            أرجع AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } وإلا {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, حجم(*constraints->valid_hw_formats));
        إذا (!constraints->valid_hw_formats)
            أرجع AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#إذا HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#وإلا
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#جيڪڏهن_پورو
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    حجم(*constraints->valid_sw_formats));
    إذا (!constraints->valid_sw_formats)
        أرجع AVERROR(ENOMEM);

    n = 0;
    لكل (صحيح i = 0; i < AV_PIX_FMT_NB; i++) {
        إذا (req_fmt == AV_PIX_FMT_CUARRAY) {
            إذا (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } وإلا {
            ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            إذا (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#إذا CONFIG_VULKAN
    إذا (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#جيڪڏهن_پورو
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    أرجع 0;
}

ساكن فراغ cuda_بفر_free(فراغ *opaque, uint8_t *معلومات)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندروني->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ڌڪو_Current(hwctx->cuda_ctx));

    إذا (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArray_چوکٺو_Descriptor *desc = (AVCUDAArray_چوکٺو_Descriptor*)معلومات;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } وإلا {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)معلومات));
    }

    CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));
}

ساكن AVBufferRef *cuda_pool_alloc(فراغ *opaque, size_t سائيز)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندروني->cuda_dl;

    AVBufferRef *ret = عدم;
    CUcontext dummy = عدم;
    CUdeviceptr معلومات;
    صحيح err;

    err = CHECK_CU(cu->cu_Ctx_ڌڪو_Current(hwctx->cuda_ctx));
    إذا (err < 0)
        أرجع عدم;

    إذا (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArray_چوکٺو_Descriptor *desc = av_mallocz(حجم(*desc));
        إذا (!desc)
            اذهب پورو;

        إذا (priv->p.cuarray_انگ_surfaces > 0) {
            إذا (priv->cuarray_انگ_surfaces_استعمال_ٿيل >= priv->p.cuarray_انگ_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                اذهب پورو;
            }
            desc->اشاريو = priv->cuarray_انگ_surfaces_استعمال_ٿيل++;
            desc->array = priv->p.cuarray_surfaces[desc->اشاريو];
        } وإلا {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            إذا (err < 0) {
                av_free(desc);
                اذهب پورو;
            }
        }

        ret = av_بفر_create((uint8_t*)desc, حجم(*desc), cuda_بفر_free, ctx, 0);
        إذا (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            اذهب پورو;
        }

        اذهب پورو;
    }

    err = CHECK_CU(cu->cuMemAlloc(&معلومات, سائيز));
    إذا (err < 0)
        اذهب پورو;

    ret = av_بفر_create((uint8_t*)معلومات, سائيز, cuda_بفر_free, ctx, 0);
    إذا (!ret) {
        CHECK_CU(cu->cuMemFree(معلومات));
        اذهب پورو;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
پورو:
    CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));
    أرجع ret;
}

#إذا HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
ساكن فراغ cuda_transfer_بفر_free(فراغ *opaque, uint8_t *معلومات)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندروني->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ڌڪو_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(معلومات));
    CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
ساكن AVBufferRef *cuda_transfer_بفر_alloc(فراغ *device_ref, size_t سائيز)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->معلومات;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندروني->cuda_dl;
    AVBufferRef *ret = عدم;
    CUcontext dummy;
    فراغ *host;

    إذا (CHECK_CU(cu->cu_Ctx_ڌڪو_Current(hwctx->cuda_ctx)) < 0)
        أرجع av_بفر_alloc(سائيز);

    إذا (CHECK_CU(cu->cuMemHostAlloc(&host, سائيز, 0)) >= 0) {
        ret = av_بفر_create(host, سائيز, cuda_transfer_بفر_free, device_ctx, 0);
        إذا (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));
    أرجع ret ? ret : av_بفر_alloc(سائيز);
}
#جيڪڏهن_پورو

ساكن فراغ cuda_چوکٺا_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندروني->cuda_dl;

    إذا (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_ڌڪو_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        لكل (صحيح i = priv->cuarray_انگ_surfaces_استعمال_ٿيل; i < priv->p.cuarray_انگ_surfaces; i++)
            إذا (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_انگ_surfaces = 0;
    }
}

ساكن CUarray_format cuda_array_format_for_pix_fmt(تعداد AVPixelFormat fmt)
{
    بدل (fmt) {
#إذا HAVE_FFNVCODEC_CUARRAY
    حالة AV_PIX_FMT_NV12:      أرجع CU_AD_FORMAT_NV12;
    حالة AV_PIX_FMT_P010:
    حالة AV_PIX_FMT_P012:
    حالة AV_PIX_FMT_P016:      أرجع CU_AD_FORMAT_P016;
    حالة AV_PIX_FMT_NV16:      أرجع CU_AD_FORMAT_NV16;
    حالة AV_PIX_FMT_P210:
    حالة AV_PIX_FMT_P212:
    حالة AV_PIX_FMT_P216:      أرجع CU_AD_FORMAT_P216;
    حالة AV_PIX_FMT_NV24:      أرجع CU_AD_FORMAT_YUV444_8_ٻٽو_انگ_SEMIPLANAR;
    حالة AV_PIX_FMT_P410:
    حالة AV_PIX_FMT_P412:
    حالة AV_PIX_FMT_P416:      أرجع CU_AD_FORMAT_YUV444_16_ٻٽو_انگ_SEMIPLANAR;
    حالة AV_PIX_FMT_YUV420P:   أرجع CU_AD_FORMAT_UINT8_PLANAR_420;
    حالة AV_PIX_FMT_YUV422P:   أرجع CU_AD_FORMAT_UINT8_PLANAR_422;
    حالة AV_PIX_FMT_YUV444P:   أرجع CU_AD_FORMAT_UINT8_PLANAR_444;
    حالة AV_PIX_FMT_YUV420P10: أرجع CU_AD_FORMAT_UINT16_PLANAR_420;
    حالة AV_PIX_FMT_YUV422P10: أرجع CU_AD_FORMAT_UINT16_PLANAR_422;
    حالة AV_PIX_FMT_YUV444P10:
    حالة AV_PIX_FMT_YUV444P10MSB:
    حالة AV_PIX_FMT_YUV444P12MSB:
    حالة AV_PIX_FMT_YUV444P16: أرجع CU_AD_FORMAT_UINT16_PLANAR_444;
    حالة AV_PIX_FMT_0RGB32:
    حالة AV_PIX_FMT_0BGR32:
    حالة AV_PIX_FMT_RGB32:
    حالة AV_PIX_FMT_BGR32:     أرجع CU_AD_FORMAT_UNSIGNED_INT8;
#جيڪڏهن_پورو
    افتراضي:                   أرجع 0;
    }
}

#إذا HAVE_FFNVCODEC_CUARRAY
ساكن بنانشان صحيح cuda_array_numchannels_for_pix_fmt(تعداد AVPixelFormat fmt)
{
    بدل (fmt) {
    حالة AV_PIX_FMT_0RGB32:
    حالة AV_PIX_FMT_0BGR32:
    حالة AV_PIX_FMT_RGB32:
    حالة AV_PIX_FMT_BGR32:     أرجع 4;
    افتراضي:                   أرجع 3;
    }
}
#جيڪڏهن_پورو

ساكن صحيح cuda_چوکٺا_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندروني->cuda_dl;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    صحيح err;

    إذا (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        أرجع AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    إذا (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        أرجع AVERROR(ENOSYS);
    }

#إذا HAVE_FFNVCODEC_CUARRAY
    إذا (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        أرجع AVERROR(ENOSYS);
    }
#وإلا
    إذا (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        أرجع AVERROR(ENOSYS);
    }
#جيڪڏهن_پورو

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->اندروني->cuda_device));
    إذا (err < 0)
        أرجع err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    إذا (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->سرڪايو_ويڪر, &priv->سرڪايو_اوچائي);

#إذا HAVE_FFNVCODEC_CUARRAY
    إذا (ctx->format == AV_PIX_FMT_CUARRAY) {
        إذا (!priv->p.cuarray_desc.ويڪر_2)
            priv->p.cuarray_desc.ويڪر_2 = ctx->ويڪر;
        إذا (!priv->p.cuarray_desc.اوچائي_2)
            priv->p.cuarray_desc.اوچائي_2 = ctx->اوچائي;
        إذا (!priv->p.cuarray_desc.انگ_Channels)
            priv->p.cuarray_desc.انگ_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        إذا (priv->p.cuarray_desc.اونهائي_2) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            أرجع AVERROR(EINVAL);
        }

        إذا (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        إذا (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            أرجع AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    إذا (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_انگ_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_انگ_surfaces, حجم(*priv->p.cuarray_surfaces));
        إذا (!priv->p.cuarray_surfaces)
            أرجع AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_ڌڪو_Current(hwctx->cuda_ctx));
        إذا (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            أرجع err;
        }

        لكل (صحيح i = 0; i < priv->p.cuarray_انگ_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            إذا (err < 0) {
                لكل (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                أرجع err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));
        إذا (err < 0)
            اذهب fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_انگ_surfaces, priv->p.cuarray_desc.ويڪر_2, priv->p.cuarray_desc.اوچائي_2);
    }
#جيڪڏهن_پورو

    إذا (!ctx->pool) {
        صحيح سائيز = av_image_get_بفر_سائيز(ctx->sw_format, ctx->ويڪر, ctx->اوچائي, priv->tex_alignment);
        إذا (سائيز < 0) {
            err = سائيز;
            اذهب fail;
        }

        ffhwframesctx(ctx)->pool_اندروني =
            av_بفر_pool_init2(سائيز, ctx, cuda_pool_alloc, عدم);
        إذا (!ffhwframesctx(ctx)->pool_اندروني) {
            err = AVERROR(ENOMEM);
            اذهب fail;
        }
    }

    أرجع 0;

fail:
    cuda_چوکٺا_uninit(ctx);
    أرجع err;
}

ساكن صحيح cuda_get_بفر(AVHWFramesContext *ctx, AVFrame *چوکٺو)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#إذا HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندروني->cuda_dl;

    CUcontext dummy;
#جيڪڏهن_پورو
    صحيح res;

    چوکٺو->buf[0] = av_بفر_pool_get(ctx->pool);
    إذا (!چوکٺو->buf[0])
        أرجع AVERROR(ENOMEM);

    إذا (ctx->format == AV_PIX_FMT_CUARRAY) {
#إذا HAVE_FFNVCODEC_CUARRAY
        AVCUDAArray_چوکٺو_Descriptor *desc = (AVCUDAArray_چوکٺو_Descriptor*)چوکٺو->buf[0]->معلومات;
        إذا (!desc) {
            چوکٺو->format = ctx->format;
            چوکٺو->ويڪر  = ctx->ويڪر;
            چوکٺو->اوچائي = ctx->اوچائي;
            أرجع 0;
        }
        چوکٺو->معلومات[0] = (uint8_t*)desc->array;
        چوکٺو->معلومات[1] = (uint8_t*)desc->اشاريو;

        res = CHECK_CU(cu->cu_Ctx_ڌڪو_Current(hwctx->cuda_ctx));
        إذا (res < 0)
            أرجع res;

        لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(چوکٺو->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            إذا (arr_plane_res == CUDA_ERROR_INVALID_قدر) {
                إذا (i > 0)
                    اكسر;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                إذا (res < 0)
                    اذهب fail;
            } وإلا إذا (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                اذهب fail;
            } وإلا {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                إذا (res < 0)
                    اذهب fail;
            }

            صحيح elem_سائيز = ff_cuda_cuarray_elem_سائيز(plane_desc.Format);
            إذا (elem_سائيز <= 0) {
                res = AVERROR_BUG;
                اذهب fail;
            }

            چوکٺو->linesize[i] = plane_desc.ويڪر_2 * plane_desc.انگ_Channels * elem_سائيز;

            إذا (arr_plane_res == CUDA_ERROR_INVALID_قدر)
                اكسر;
        }

        res = CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));
        إذا (res < 0)
            أرجع res;
#وإلا
        أرجع AVERROR(ENOSYS);
#جيڪڏهن_پورو
    } وإلا {
        res = av_image_fill_arrays(چوکٺو->معلومات, چوکٺو->linesize, چوکٺو->buf[0]->معلومات,
                                   ctx->sw_format, ctx->ويڪر, ctx->اوچائي, priv->tex_alignment);
        إذا (res < 0)
            أرجع res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        إذا (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            چوکٺو->linesize[1] = چوکٺو->linesize[2] = چوکٺو->linesize[0] / 2;
            چوکٺو->معلومات[2]     = چوکٺو->معلومات[1];
            چوکٺو->معلومات[1]     = چوکٺو->معلومات[2] + چوکٺو->linesize[2] * AV_CEIL_RSHIFT(ctx->اوچائي, 1);
        }
    }

    چوکٺو->format = ctx->format;
    چوکٺو->ويڪر  = ctx->ويڪر;
    چوکٺو->اوچائي = ctx->اوچائي;

    أرجع 0;

#إذا HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));
    أرجع res;
#جيڪڏهن_پورو
}

ساكن تعداد AVPixelFormat cuda_چوکٺو_hw_format(ثابت AVFrame *چوکٺو)
{
    إذا (!چوکٺو->hw_چوکٺا_ctx)
        أرجع AV_PIX_FMT_NONE;
    أرجع ((AVHWFramesContext *)چوکٺو->hw_چوکٺا_ctx->معلومات)->format;
}

ساكن صحيح cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     تعداد AVHWFrameTransferDirection dir,
                                     تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    إذا (!fmts)
        أرجع AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    أرجع 0;
}

ساكن صحيح cuda_transfer_معلومات(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندروني->cuda_dl;

    ثابت AVFrame *sw_چوکٺو = src->hw_چوکٺا_ctx ? dst : src;
    AVFrame *چوٽي_هيٺ_ڏانهن = عدم, *bottom_مٿي_dst = عدم;
    CUcontext dummy;
    صحيح i, ret, copy_queued = 0, bottom_مٿي = 0;

    {
        تعداد AVPixelFormat src_fmt = cuda_چوکٺو_hw_format(src);
        تعداد AVPixelFormat dst_fmt = cuda_چوکٺو_hw_format(dst);
        إذا ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            أرجع AVERROR(ENOSYS);
    }

    لكل (i = 0; i < FF_ARRAY_ELEMS(sw_چوکٺو->linesize); i++)
        bottom_مٿي |= sw_چوکٺو->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    إذا (bottom_مٿي) {
        چوٽي_هيٺ_ڏانهن = av_چوکٺو_alloc();
        إذا (!چوٽي_هيٺ_ڏانهن)
            أرجع AVERROR(ENOMEM);
        چوٽي_هيٺ_ڏانهن->format = ctx->sw_format;
        چوٽي_هيٺ_ڏانهن->ويڪر  = ctx->ويڪر;
        چوٽي_هيٺ_ڏانهن->اوچائي = ctx->اوچائي;
        ret = av_hwframe_get_transfer_بفر((src->hw_چوکٺا_ctx ? src : dst)->hw_چوکٺا_ctx,
                                             چوٽي_هيٺ_ڏانهن);
        إذا (ret < 0)
            اذهب free_چوٽي_هيٺ_ڏانهن;
        چوٽي_هيٺ_ڏانهن->ويڪر  = src->ويڪر;
        چوٽي_هيٺ_ڏانهن->اوچائي = src->اوچائي;
        إذا (sw_چوکٺو == src) {
            av_image_copy2(چوٽي_هيٺ_ڏانهن->معلومات, چوٽي_هيٺ_ڏانهن->linesize, src->معلومات, src->linesize,
                           ctx->sw_format, src->ويڪر, src->اوچائي);
            src = چوٽي_هيٺ_ڏانهن;
        } وإلا {
            bottom_مٿي_dst = dst;
            dst           = چوٽي_هيٺ_ڏانهن;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_ڌڪو_Current(hwctx->cuda_ctx));
    إذا (ret < 0)
        اذهب free_چوٽي_هيٺ_ڏانهن;

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
    لكل (i = 0; i < FF_ARRAY_ELEMS(src->معلومات) && src->linesize[i]; i++) {
        صحيح src_is_nonplanar_cuarray = 0;
        صحيح dst_is_nonplanar_cuarray = 0;

        صحيح bytewidth = av_image_get_linesize(ctx->sw_format, src->ويڪر, i);
        إذا (bytewidth < 0) {
            ret = bytewidth;
            اذهب fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .ويڪر_اندريون_بائيٽون  = bytewidth,
            .اوچائي_2        = AV_CEIL_RSHIFT(src->اوچائي, ((i == 0 || i == 3) ? 0 : priv->سرڪايو_اوچائي)),
        };

        إذا (src->format == AV_PIX_FMT_CUDA) {
            cpy.src_يادگيري_Type = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->معلومات[i];
        } وإلا إذا (src->format == AV_PIX_FMT_CUARRAY) {
#إذا HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->معلومات[0], i);
            إذا (cures == CUDA_ERROR_INVALID_قدر && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->معلومات[0];
                src_is_nonplanar_cuarray = 1;
            } وإلا إذا (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                اذهب fail;
            }

            cpy.src_يادگيري_Type = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#وإلا
            ret = AVERROR(ENOSYS);
            اذهب ٻاهر_نڪرو;
#جيڪڏهن_پورو
        } وإلا {
            cpy.src_يادگيري_Type = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->معلومات[i];
        }

        إذا (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dst_يادگيري_Type = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->معلومات[i];
        } وإلا إذا (dst->format == AV_PIX_FMT_CUARRAY) {
#إذا HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->معلومات[0], i);
            إذا (cures == CUDA_ERROR_INVALID_قدر && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->معلومات[0];
                dst_is_nonplanar_cuarray = 1;
            } وإلا إذا (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                اذهب fail;
            }

            cpy.dst_يادگيري_Type = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#وإلا
            ret = AVERROR(ENOSYS);
            اذهب ٻاهر_نڪرو;
#جيڪڏهن_پورو
        } وإلا {
            cpy.dst_يادگيري_Type = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->معلومات[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->وهڪرو));
        إذا (ret < 0)
            اذهب fail;
        copy_queued = 1;

        إذا (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            اكسر;
    }

    /* The caller may reuse host memory once the transfer returns. */
    إذا (!src->hw_چوکٺا_ctx || !dst->hw_چوکٺا_ctx) {
        ret = CHECK_CU(cu->cu_وهڪرو_Synchronize(hwctx->وهڪرو));
        إذا (ret < 0)
            اذهب ٻاهر_نڪرو;
    }

fail:
    إذا (ret < 0 && copy_queued)
        CHECK_CU(cu->cu_وهڪرو_Synchronize(hwctx->وهڪرو));
ٻاهر_نڪرو:
    CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));

    إذا (bottom_مٿي_dst && ret >= 0)
        av_image_copy2(bottom_مٿي_dst->معلومات, bottom_مٿي_dst->linesize,
                       چوٽي_هيٺ_ڏانهن->معلومات, چوٽي_هيٺ_ڏانهن->linesize,
                       ctx->sw_format, src->ويڪر, src->اوچائي);
free_چوٽي_هيٺ_ڏانهن:
    av_چوکٺو_free(&چوٽي_هيٺ_ڏانهن);

    أرجع ret;
}

ساكن فراغ cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    إذا (hwctx->p.اندروني) {
        CudaFunctions *cu = hwctx->اندروني.cuda_dl;

        إذا (hwctx->اندروني.is_allocated && hwctx->p.cuda_ctx) {
            إذا (hwctx->اندروني.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->اندروني.cuda_device));
            وإلا إذا (!(hwctx->اندروني.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = عدم;
        }

        cuda_free_functions(&hwctx->اندروني.cuda_dl);
        memset(&hwctx->اندروني, 0, حجم(hwctx->اندروني));
        hwctx->p.اندروني = عدم;
    }
}

ساكن صحيح cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    صحيح ret;

    hwctx->p.اندروني = &hwctx->اندروني;

    إذا (!hwctx->اندروني.cuda_dl) {
        ret = cuda_ڀريو_functions(&hwctx->اندروني.cuda_dl, ctx);
        إذا (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            اذهب error;
        }
    }

    أرجع 0;

error:
    cuda_device_uninit(ctx);
    أرجع ret;
}

ساكن صحيح cuda_context_init(AVHWDeviceContext *device_ctx, صحيح flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    صحيح ret, dev_سرگرم = 0;
    بنانشان صحيح dev_flags = 0;

    ثابت بنانشان صحيح desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->اندروني->cuda_dl;

    hwctx->اندروني->flags = flags;

    إذا (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->اندروني->cuda_device,
                       &dev_flags, &dev_سرگرم));
        إذا (ret < 0)
            أرجع ret;

        إذا (dev_سرگرم && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            أرجع AVERROR(ENOTSUP);
        } وإلا إذا (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cu_Device_Primary_Ctx_سيٽ_Flags(hwctx->اندروني->cuda_device,
                           desired_flags));
            إذا (ret < 0)
                أرجع ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->اندروني->cuda_device));
        إذا (ret < 0)
            أرجع ret;
    } وإلا إذا (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        إذا (ret < 0)
            أرجع ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } وإلا {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->اندروني->cuda_device));
        إذا (ret < 0)
            أرجع ret;

        CHECK_CU(cu->cu_Ctx_ڪڍو_Current(&dummy));
    }

    hwctx->اندروني->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->وهڪرو = عدم;

    أرجع 0;
}

ساكن صحيح cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, صحيح *flags)
{
    AVDictionary_داخلا *primary_ctx_opt = av_dict_get(opts, "primary_ctx", عدم, 0);
    AVDictionary_داخلا *current_ctx_opt = av_dict_get(opts, "current_ctx", عدم, 0);

    صحيح use_primary_ctx = 0, use_current_ctx = 0;
    إذا (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->قدر, عدم, 10);

    إذا (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->قدر, عدم, 10);

    إذا (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        أرجع AVERROR(EINVAL);
    }

    إذا (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } وإلا إذا (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    إذا (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } وإلا إذا (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    أرجع 0;
}

ساكن صحيح cuda_device_create(AVHWDeviceContext *device_ctx,
                              ثابت حرف *device,
                              AVDictionary *opts, صحيح flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    صحيح ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    إذا (ret < 0)
        اذهب error;

    إذا (device)
        device_idx = strtol(device, عدم, 0);

    ret = cuda_device_init(device_ctx);
    إذا (ret < 0)
        اذهب error;

    cu = hwctx->اندروني->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    إذا (ret < 0)
        اذهب error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->اندروني->cuda_device, device_idx));
    إذا (ret < 0)
        اذهب error;

    ret = cuda_context_init(device_ctx, flags);
    إذا (ret < 0)
        اذهب error;

    أرجع 0;

error:
    cuda_device_uninit(device_ctx);
    أرجع ret;
}

ساكن صحيح cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              صحيح flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ثابت حرف *src_uuid = عدم;
#إذا CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#جيڪڏهن_پورو
    صحيح ret, i, device_ڳڻپ;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    إذا (ret < 0)
        اذهب error;

#إذا CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#جيڪڏهن_پورو

    بدل (src_ctx->type) {
#إذا CONFIG_VULKAN
#وصف_ڪريو TYPE PFN_vkGetPhysicalDeviceProperties2
    حالة AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .p_ايندڙ = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        اكسر;
    }
#وصف_رد TYPE
#جيڪڏهن_پورو
    افتراضي:
        ret = AVERROR(ENOSYS);
        اذهب error;
    }

    إذا (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        اذهب error;
    }

    ret = cuda_device_init(device_ctx);
    إذا (ret < 0)
        اذهب error;

    cu = hwctx->اندروني->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    إذا (ret < 0)
        اذهب error;

    ret = CHECK_CU(cu->cu_Device_Get_ڳڻپ(&device_ڳڻپ));
    إذا (ret < 0)
        اذهب error;

    hwctx->اندروني->cuda_device = -1;
    لكل (i = 0; i < device_ڳڻپ; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        إذا (ret < 0)
            اذهب error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        إذا (ret < 0)
            اذهب error;

        إذا (memcmp(src_uuid, uuid.بائيٽون, حجم (uuid.بائيٽون)) == 0) {
            hwctx->اندروني->cuda_device = dev;
            اكسر;
        }
    }

    إذا (hwctx->اندروني->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        اذهب error;
    }

    ret = cuda_context_init(device_ctx, flags);
    إذا (ret < 0)
        اذهب error;

    أرجع 0;

error:
    cuda_device_uninit(device_ctx);
    أرجع ret;
}

ثابت HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_سائيز    = حجم(CUDADeviceContext),
    .چوکٺا_hwctx_سائيز    = حجم(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .چوکٺا_get_constraints = cuda_چوکٺا_get_constraints,
    .چوکٺا_init          = cuda_چوکٺا_init,
    .چوکٺا_uninit        = cuda_چوکٺا_uninit,
    .چوکٺا_get_بفر    = cuda_get_بفر,
    .transfer_get_formats = cuda_transfer_get_formats,
#إذا HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_بفر_alloc = cuda_transfer_بفر_alloc,
#جيڪڏهن_پورو
    .transfer_معلومات_منزل     = cuda_transfer_معلومات,
    .transfer_معلومات_from   = cuda_transfer_معلومات,

    .pix_fmts             = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#إذا HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#جيڪڏهن_پورو
                                                          AV_PIX_FMT_NONE },
};
