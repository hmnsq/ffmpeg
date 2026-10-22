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

#شامل "buffer.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_internal.h"
#شامل "hwcontext_cuda_internal.h"
#اگر CONFIG_VULKAN
#شامل "hwcontext_vulkan.h"
#اگر_ختم
#شامل "cuda_check.h"
#شامل "mem.h"
#شامل "pixdesc.h"
#شامل "pixfmt.h"
#شامل "imgutils.h"

قسمتعریف ساخت CUDAFramesContext {
    AVCUDAFramesContext p;

    صحیح سرکاؤ_چوڑائی, سرکاؤ_اونچائی;
    صحیح tex_alignment;

    صحیح cuarray_عدد_surfaces_مستعمل;
} CUDAFramesContext;

قسمتعریف ساخت CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADevice_Context_اندرونی اندرونی_2;
} CUDADeviceContext;



#تعریف_کرو CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

ساکن CUarray_format cuda_array_format_for_pix_fmt(شمار AVPixelFormat fmt);

ساکن صحیح cuda_چوکھٹے_get_constraints(AVHWDeviceContext *ctx,
                                       ثابت خالی *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ثابت AVCUDAHWConfig *config = hwconfig;
    شمار AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    صحیح n = 0;

    اگر (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
        اگر (!constraints->valid_hw_formats)
            واپس AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } ورنہ {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, حجم(*constraints->valid_hw_formats));
        اگر (!constraints->valid_hw_formats)
            واپس AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#اگر HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#ورنہ
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#اگر_ختم
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    حجم(*constraints->valid_sw_formats));
    اگر (!constraints->valid_sw_formats)
        واپس AVERROR(ENOMEM);

    n = 0;
    برائے (صحیح i = 0; i < AV_PIX_FMT_NB; i++) {
        اگر (req_fmt == AV_PIX_FMT_CUARRAY) {
            اگر (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } ورنہ {
            ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            اگر (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#اگر CONFIG_VULKAN
    اگر (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#اگر_ختم
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    واپس 0;
}

ساکن خالی cuda_بفر_free(خالی *opaque, uint8_t *ڈیٹا)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندرونی_2->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ڈالو_Current(hwctx->cuda_ctx));

    اگر (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArray_چوکھٹا_Descriptor *desc = (AVCUDAArray_چوکھٹا_Descriptor*)ڈیٹا;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } ورنہ {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)ڈیٹا));
    }

    CHECK_CU(cu->cu_Ctx_نکالو_Current(&dummy));
}

ساکن AVBufferRef *cuda_pool_alloc(خالی *opaque, size_t سائز)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندرونی_2->cuda_dl;

    AVBufferRef *ret = تہی;
    CUcontext dummy = تہی;
    CUdeviceptr ڈیٹا;
    صحیح err;

    err = CHECK_CU(cu->cu_Ctx_ڈالو_Current(hwctx->cuda_ctx));
    اگر (err < 0)
        واپس تہی;

    اگر (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArray_چوکھٹا_Descriptor *desc = av_mallocz(حجم(*desc));
        اگر (!desc)
            جاؤ مکمل;

        اگر (priv->p.cuarray_عدد_surfaces > 0) {
            اگر (priv->cuarray_عدد_surfaces_مستعمل >= priv->p.cuarray_عدد_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                جاؤ مکمل;
            }
            desc->اشاریہ = priv->cuarray_عدد_surfaces_مستعمل++;
            desc->array = priv->p.cuarray_surfaces[desc->اشاریہ];
        } ورنہ {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            اگر (err < 0) {
                av_free(desc);
                جاؤ مکمل;
            }
        }

        ret = av_بفر_create((uint8_t*)desc, حجم(*desc), cuda_بفر_free, ctx, 0);
        اگر (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            جاؤ مکمل;
        }

        جاؤ مکمل;
    }

    err = CHECK_CU(cu->cuMemAlloc(&ڈیٹا, سائز));
    اگر (err < 0)
        جاؤ مکمل;

    ret = av_بفر_create((uint8_t*)ڈیٹا, سائز, cuda_بفر_free, ctx, 0);
    اگر (!ret) {
        CHECK_CU(cu->cuMemFree(ڈیٹا));
        جاؤ مکمل;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
مکمل:
    CHECK_CU(cu->cu_Ctx_نکالو_Current(&dummy));
    واپس ret;
}

#اگر HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
ساکن خالی cuda_transfer_بفر_free(خالی *opaque, uint8_t *ڈیٹا)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندرونی_2->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ڈالو_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(ڈیٹا));
    CHECK_CU(cu->cu_Ctx_نکالو_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
ساکن AVBufferRef *cuda_transfer_بفر_alloc(خالی *device_ref, size_t سائز)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->ڈیٹا;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندرونی_2->cuda_dl;
    AVBufferRef *ret = تہی;
    CUcontext dummy;
    خالی *host;

    اگر (CHECK_CU(cu->cu_Ctx_ڈالو_Current(hwctx->cuda_ctx)) < 0)
        واپس av_بفر_alloc(سائز);

    اگر (CHECK_CU(cu->cuMemHostAlloc(&host, سائز, 0)) >= 0) {
        ret = av_بفر_create(host, سائز, cuda_transfer_بفر_free, device_ctx, 0);
        اگر (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_نکالو_Current(&dummy));
    واپس ret ? ret : av_بفر_alloc(سائز);
}
#اگر_ختم

ساکن خالی cuda_چوکھٹے_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندرونی_2->cuda_dl;

    اگر (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_ڈالو_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        برائے (صحیح i = priv->cuarray_عدد_surfaces_مستعمل; i < priv->p.cuarray_عدد_surfaces; i++)
            اگر (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_نکالو_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_عدد_surfaces = 0;
    }
}

ساکن CUarray_format cuda_array_format_for_pix_fmt(شمار AVPixelFormat fmt)
{
    انتخاب (fmt) {
#اگر HAVE_FFNVCODEC_CUARRAY
    حالت AV_PIX_FMT_NV12:      واپس CU_AD_FORMAT_NV12;
    حالت AV_PIX_FMT_P010:
    حالت AV_PIX_FMT_P012:
    حالت AV_PIX_FMT_P016:      واپس CU_AD_FORMAT_P016;
    حالت AV_PIX_FMT_NV16:      واپس CU_AD_FORMAT_NV16;
    حالت AV_PIX_FMT_P210:
    حالت AV_PIX_FMT_P212:
    حالت AV_PIX_FMT_P216:      واپس CU_AD_FORMAT_P216;
    حالت AV_PIX_FMT_NV24:      واپس CU_AD_FORMAT_YUV444_8_ثنائی_ہندسہ_SEMIPLANAR;
    حالت AV_PIX_FMT_P410:
    حالت AV_PIX_FMT_P412:
    حالت AV_PIX_FMT_P416:      واپس CU_AD_FORMAT_YUV444_16_ثنائی_ہندسہ_SEMIPLANAR;
    حالت AV_PIX_FMT_YUV420P:   واپس CU_AD_FORMAT_UINT8_PLANAR_420;
    حالت AV_PIX_FMT_YUV422P:   واپس CU_AD_FORMAT_UINT8_PLANAR_422;
    حالت AV_PIX_FMT_YUV444P:   واپس CU_AD_FORMAT_UINT8_PLANAR_444;
    حالت AV_PIX_FMT_YUV420P10: واپس CU_AD_FORMAT_UINT16_PLANAR_420;
    حالت AV_PIX_FMT_YUV422P10: واپس CU_AD_FORMAT_UINT16_PLANAR_422;
    حالت AV_PIX_FMT_YUV444P10:
    حالت AV_PIX_FMT_YUV444P10MSB:
    حالت AV_PIX_FMT_YUV444P12MSB:
    حالت AV_PIX_FMT_YUV444P16: واپس CU_AD_FORMAT_UINT16_PLANAR_444;
    حالت AV_PIX_FMT_0RGB32:
    حالت AV_PIX_FMT_0BGR32:
    حالت AV_PIX_FMT_RGB32:
    حالت AV_PIX_FMT_BGR32:     واپس CU_AD_FORMAT_UNSIGNED_INT8;
#اگر_ختم
    طےشدہ:                   واپس 0;
    }
}

#اگر HAVE_FFNVCODEC_CUARRAY
ساکن غیرعلامتی صحیح cuda_array_numchannels_for_pix_fmt(شمار AVPixelFormat fmt)
{
    انتخاب (fmt) {
    حالت AV_PIX_FMT_0RGB32:
    حالت AV_PIX_FMT_0BGR32:
    حالت AV_PIX_FMT_RGB32:
    حالت AV_PIX_FMT_BGR32:     واپس 4;
    طےشدہ:                   واپس 3;
    }
}
#اگر_ختم

ساکن صحیح cuda_چوکھٹے_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندرونی_2->cuda_dl;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    صحیح err;

    اگر (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        واپس AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    اگر (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        واپس AVERROR(ENOSYS);
    }

#اگر HAVE_FFNVCODEC_CUARRAY
    اگر (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        واپس AVERROR(ENOSYS);
    }
#ورنہ
    اگر (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        واپس AVERROR(ENOSYS);
    }
#اگر_ختم

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->اندرونی_2->cuda_device));
    اگر (err < 0)
        واپس err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    اگر (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->سرکاؤ_چوڑائی, &priv->سرکاؤ_اونچائی);

#اگر HAVE_FFNVCODEC_CUARRAY
    اگر (ctx->format == AV_PIX_FMT_CUARRAY) {
        اگر (!priv->p.cuarray_desc.چوڑائی_2)
            priv->p.cuarray_desc.چوڑائی_2 = ctx->چوڑائی;
        اگر (!priv->p.cuarray_desc.اونچائی_2)
            priv->p.cuarray_desc.اونچائی_2 = ctx->اونچائی;
        اگر (!priv->p.cuarray_desc.عدد_Channels)
            priv->p.cuarray_desc.عدد_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        اگر (priv->p.cuarray_desc.گہرائی_2) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            واپس AVERROR(EINVAL);
        }

        اگر (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        اگر (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            واپس AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    اگر (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_عدد_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_عدد_surfaces, حجم(*priv->p.cuarray_surfaces));
        اگر (!priv->p.cuarray_surfaces)
            واپس AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_ڈالو_Current(hwctx->cuda_ctx));
        اگر (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            واپس err;
        }

        برائے (صحیح i = 0; i < priv->p.cuarray_عدد_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            اگر (err < 0) {
                برائے (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_نکالو_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                واپس err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_نکالو_Current(&dummy));
        اگر (err < 0)
            جاؤ fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_عدد_surfaces, priv->p.cuarray_desc.چوڑائی_2, priv->p.cuarray_desc.اونچائی_2);
    }
#اگر_ختم

    اگر (!ctx->pool) {
        صحیح سائز = av_image_get_بفر_سائز(ctx->sw_format, ctx->چوڑائی, ctx->اونچائی, priv->tex_alignment);
        اگر (سائز < 0) {
            err = سائز;
            جاؤ fail;
        }

        ffhwframesctx(ctx)->pool_اندرونی =
            av_بفر_pool_init2(سائز, ctx, cuda_pool_alloc, تہی);
        اگر (!ffhwframesctx(ctx)->pool_اندرونی) {
            err = AVERROR(ENOMEM);
            جاؤ fail;
        }
    }

    واپس 0;

fail:
    cuda_چوکھٹے_uninit(ctx);
    واپس err;
}

ساکن صحیح cuda_get_بفر(AVHWFramesContext *ctx, AVFrame *چوکھٹا)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#اگر HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندرونی_2->cuda_dl;

    CUcontext dummy;
#اگر_ختم
    صحیح res;

    چوکھٹا->buf[0] = av_بفر_pool_get(ctx->pool);
    اگر (!چوکھٹا->buf[0])
        واپس AVERROR(ENOMEM);

    اگر (ctx->format == AV_PIX_FMT_CUARRAY) {
#اگر HAVE_FFNVCODEC_CUARRAY
        AVCUDAArray_چوکھٹا_Descriptor *desc = (AVCUDAArray_چوکھٹا_Descriptor*)چوکھٹا->buf[0]->ڈیٹا;
        اگر (!desc) {
            چوکھٹا->format = ctx->format;
            چوکھٹا->چوڑائی  = ctx->چوڑائی;
            چوکھٹا->اونچائی = ctx->اونچائی;
            واپس 0;
        }
        چوکھٹا->ڈیٹا[0] = (uint8_t*)desc->array;
        چوکھٹا->ڈیٹا[1] = (uint8_t*)desc->اشاریہ;

        res = CHECK_CU(cu->cu_Ctx_ڈالو_Current(hwctx->cuda_ctx));
        اگر (res < 0)
            واپس res;

        برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(چوکھٹا->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            اگر (arr_plane_res == CUDA_ERROR_INVALID_قدر) {
                اگر (i > 0)
                    توڑو;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                اگر (res < 0)
                    جاؤ fail;
            } ورنہ اگر (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                جاؤ fail;
            } ورنہ {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                اگر (res < 0)
                    جاؤ fail;
            }

            صحیح elem_سائز = ff_cuda_cuarray_elem_سائز(plane_desc.Format);
            اگر (elem_سائز <= 0) {
                res = AVERROR_BUG;
                جاؤ fail;
            }

            چوکھٹا->linesize[i] = plane_desc.چوڑائی_2 * plane_desc.عدد_Channels * elem_سائز;

            اگر (arr_plane_res == CUDA_ERROR_INVALID_قدر)
                توڑو;
        }

        res = CHECK_CU(cu->cu_Ctx_نکالو_Current(&dummy));
        اگر (res < 0)
            واپس res;
#ورنہ
        واپس AVERROR(ENOSYS);
#اگر_ختم
    } ورنہ {
        res = av_image_fill_arrays(چوکھٹا->ڈیٹا, چوکھٹا->linesize, چوکھٹا->buf[0]->ڈیٹا,
                                   ctx->sw_format, ctx->چوڑائی, ctx->اونچائی, priv->tex_alignment);
        اگر (res < 0)
            واپس res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        اگر (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            چوکھٹا->linesize[1] = چوکھٹا->linesize[2] = چوکھٹا->linesize[0] / 2;
            چوکھٹا->ڈیٹا[2]     = چوکھٹا->ڈیٹا[1];
            چوکھٹا->ڈیٹا[1]     = چوکھٹا->ڈیٹا[2] + چوکھٹا->linesize[2] * AV_CEIL_RSHIFT(ctx->اونچائی, 1);
        }
    }

    چوکھٹا->format = ctx->format;
    چوکھٹا->چوڑائی  = ctx->چوڑائی;
    چوکھٹا->اونچائی = ctx->اونچائی;

    واپس 0;

#اگر HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_نکالو_Current(&dummy));
    واپس res;
#اگر_ختم
}

ساکن شمار AVPixelFormat cuda_چوکھٹا_hw_format(ثابت AVFrame *چوکھٹا)
{
    اگر (!چوکھٹا->hw_چوکھٹے_ctx)
        واپس AV_PIX_FMT_NONE;
    واپس ((AVHWFramesContext *)چوکھٹا->hw_چوکھٹے_ctx->ڈیٹا)->format;
}

ساکن صحیح cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     شمار AVHWFrameTransferDirection dir,
                                     شمار AVPixelFormat **formats)
{
    شمار AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    اگر (!fmts)
        واپس AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    واپس 0;
}

ساکن صحیح cuda_transfer_ڈیٹا(AVHWFramesContext *ctx, AVFrame *dst,
                                 ثابت AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->اندرونی_2->cuda_dl;

    ثابت AVFrame *sw_چوکھٹا = src->hw_چوکھٹے_ctx ? dst : src;
    AVFrame *چوٹی_نیچے_کو = تہی, *bottom_اوپر_dst = تہی;
    CUcontext dummy;
    صحیح i, ret, copy_queued = 0, bottom_اوپر = 0;

    {
        شمار AVPixelFormat src_fmt = cuda_چوکھٹا_hw_format(src);
        شمار AVPixelFormat dst_fmt = cuda_چوکھٹا_hw_format(dst);
        اگر ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            واپس AVERROR(ENOSYS);
    }

    برائے (i = 0; i < FF_ARRAY_ELEMS(sw_چوکھٹا->linesize); i++)
        bottom_اوپر |= sw_چوکھٹا->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    اگر (bottom_اوپر) {
        چوٹی_نیچے_کو = av_چوکھٹا_alloc();
        اگر (!چوٹی_نیچے_کو)
            واپس AVERROR(ENOMEM);
        چوٹی_نیچے_کو->format = ctx->sw_format;
        چوٹی_نیچے_کو->چوڑائی  = ctx->چوڑائی;
        چوٹی_نیچے_کو->اونچائی = ctx->اونچائی;
        ret = av_hwframe_get_transfer_بفر((src->hw_چوکھٹے_ctx ? src : dst)->hw_چوکھٹے_ctx,
                                             چوٹی_نیچے_کو);
        اگر (ret < 0)
            جاؤ free_چوٹی_نیچے_کو;
        چوٹی_نیچے_کو->چوڑائی  = src->چوڑائی;
        چوٹی_نیچے_کو->اونچائی = src->اونچائی;
        اگر (sw_چوکھٹا == src) {
            av_image_copy2(چوٹی_نیچے_کو->ڈیٹا, چوٹی_نیچے_کو->linesize, src->ڈیٹا, src->linesize,
                           ctx->sw_format, src->چوڑائی, src->اونچائی);
            src = چوٹی_نیچے_کو;
        } ورنہ {
            bottom_اوپر_dst = dst;
            dst           = چوٹی_نیچے_کو;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_ڈالو_Current(hwctx->cuda_ctx));
    اگر (ret < 0)
        جاؤ free_چوٹی_نیچے_کو;

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
    برائے (i = 0; i < FF_ARRAY_ELEMS(src->ڈیٹا) && src->linesize[i]; i++) {
        صحیح src_is_nonplanar_cuarray = 0;
        صحیح dst_is_nonplanar_cuarray = 0;

        صحیح bytewidth = av_image_get_linesize(ctx->sw_format, src->چوڑائی, i);
        اگر (bytewidth < 0) {
            ret = bytewidth;
            جاؤ fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .چوڑائی_اندر_بائٹیں  = bytewidth,
            .اونچائی_2        = AV_CEIL_RSHIFT(src->اونچائی, ((i == 0 || i == 3) ? 0 : priv->سرکاؤ_اونچائی)),
        };

        اگر (src->format == AV_PIX_FMT_CUDA) {
            cpy.src_حافظہ_Type = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->ڈیٹا[i];
        } ورنہ اگر (src->format == AV_PIX_FMT_CUARRAY) {
#اگر HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->ڈیٹا[0], i);
            اگر (cures == CUDA_ERROR_INVALID_قدر && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->ڈیٹا[0];
                src_is_nonplanar_cuarray = 1;
            } ورنہ اگر (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                جاؤ fail;
            }

            cpy.src_حافظہ_Type = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#ورنہ
            ret = AVERROR(ENOSYS);
            جاؤ باہر_نکلو;
#اگر_ختم
        } ورنہ {
            cpy.src_حافظہ_Type = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->ڈیٹا[i];
        }

        اگر (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dst_حافظہ_Type = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->ڈیٹا[i];
        } ورنہ اگر (dst->format == AV_PIX_FMT_CUARRAY) {
#اگر HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->ڈیٹا[0], i);
            اگر (cures == CUDA_ERROR_INVALID_قدر && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->ڈیٹا[0];
                dst_is_nonplanar_cuarray = 1;
            } ورنہ اگر (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                جاؤ fail;
            }

            cpy.dst_حافظہ_Type = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#ورنہ
            ret = AVERROR(ENOSYS);
            جاؤ باہر_نکلو;
#اگر_ختم
        } ورنہ {
            cpy.dst_حافظہ_Type = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->ڈیٹا[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->دھارا));
        اگر (ret < 0)
            جاؤ fail;
        copy_queued = 1;

        اگر (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            توڑو;
    }

    /* The caller may reuse host memory once the transfer returns. */
    اگر (!src->hw_چوکھٹے_ctx || !dst->hw_چوکھٹے_ctx) {
        ret = CHECK_CU(cu->cu_دھارا_Synchronize(hwctx->دھارا));
        اگر (ret < 0)
            جاؤ باہر_نکلو;
    }

fail:
    اگر (ret < 0 && copy_queued)
        CHECK_CU(cu->cu_دھارا_Synchronize(hwctx->دھارا));
باہر_نکلو:
    CHECK_CU(cu->cu_Ctx_نکالو_Current(&dummy));

    اگر (bottom_اوپر_dst && ret >= 0)
        av_image_copy2(bottom_اوپر_dst->ڈیٹا, bottom_اوپر_dst->linesize,
                       چوٹی_نیچے_کو->ڈیٹا, چوٹی_نیچے_کو->linesize,
                       ctx->sw_format, src->چوڑائی, src->اونچائی);
free_چوٹی_نیچے_کو:
    av_چوکھٹا_free(&چوٹی_نیچے_کو);

    واپس ret;
}

ساکن خالی cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    اگر (hwctx->p.اندرونی_2) {
        CudaFunctions *cu = hwctx->اندرونی_2.cuda_dl;

        اگر (hwctx->اندرونی_2.is_allocated && hwctx->p.cuda_ctx) {
            اگر (hwctx->اندرونی_2.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->اندرونی_2.cuda_device));
            ورنہ اگر (!(hwctx->اندرونی_2.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = تہی;
        }

        cuda_free_functions(&hwctx->اندرونی_2.cuda_dl);
        memset(&hwctx->اندرونی_2, 0, حجم(hwctx->اندرونی_2));
        hwctx->p.اندرونی_2 = تہی;
    }
}

ساکن صحیح cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    صحیح ret;

    hwctx->p.اندرونی_2 = &hwctx->اندرونی_2;

    اگر (!hwctx->اندرونی_2.cuda_dl) {
        ret = cuda_بھرو_functions(&hwctx->اندرونی_2.cuda_dl, ctx);
        اگر (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            جاؤ error;
        }
    }

    واپس 0;

error:
    cuda_device_uninit(ctx);
    واپس ret;
}

ساکن صحیح cuda_context_init(AVHWDeviceContext *device_ctx, صحیح flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    صحیح ret, dev_فعال = 0;
    غیرعلامتی صحیح dev_flags = 0;

    ثابت غیرعلامتی صحیح desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->اندرونی_2->cuda_dl;

    hwctx->اندرونی_2->flags = flags;

    اگر (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->اندرونی_2->cuda_device,
                       &dev_flags, &dev_فعال));
        اگر (ret < 0)
            واپس ret;

        اگر (dev_فعال && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            واپس AVERROR(ENOTSUP);
        } ورنہ اگر (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cu_Device_Primary_Ctx_سیٹ_Flags(hwctx->اندرونی_2->cuda_device,
                           desired_flags));
            اگر (ret < 0)
                واپس ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->اندرونی_2->cuda_device));
        اگر (ret < 0)
            واپس ret;
    } ورنہ اگر (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        اگر (ret < 0)
            واپس ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } ورنہ {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->اندرونی_2->cuda_device));
        اگر (ret < 0)
            واپس ret;

        CHECK_CU(cu->cu_Ctx_نکالو_Current(&dummy));
    }

    hwctx->اندرونی_2->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->دھارا = تہی;

    واپس 0;
}

ساکن صحیح cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, صحیح *flags)
{
    AVDictionary_اندراج *primary_ctx_opt = av_dict_get(opts, "primary_ctx", تہی, 0);
    AVDictionary_اندراج *current_ctx_opt = av_dict_get(opts, "current_ctx", تہی, 0);

    صحیح use_primary_ctx = 0, use_current_ctx = 0;
    اگر (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->قدر, تہی, 10);

    اگر (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->قدر, تہی, 10);

    اگر (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        واپس AVERROR(EINVAL);
    }

    اگر (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } ورنہ اگر (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    اگر (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } ورنہ اگر (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    واپس 0;
}

ساکن صحیح cuda_device_create(AVHWDeviceContext *device_ctx,
                              ثابت حرف *device,
                              AVDictionary *opts, صحیح flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    صحیح ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    اگر (ret < 0)
        جاؤ error;

    اگر (device)
        device_idx = strtol(device, تہی, 0);

    ret = cuda_device_init(device_ctx);
    اگر (ret < 0)
        جاؤ error;

    cu = hwctx->اندرونی_2->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    اگر (ret < 0)
        جاؤ error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->اندرونی_2->cuda_device, device_idx));
    اگر (ret < 0)
        جاؤ error;

    ret = cuda_context_init(device_ctx, flags);
    اگر (ret < 0)
        جاؤ error;

    واپس 0;

error:
    cuda_device_uninit(device_ctx);
    واپس ret;
}

ساکن صحیح cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              صحیح flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ثابت حرف *src_uuid = تہی;
#اگر CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#اگر_ختم
    صحیح ret, i, device_گنتی;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    اگر (ret < 0)
        جاؤ error;

#اگر CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#اگر_ختم

    انتخاب (src_ctx->type) {
#اگر CONFIG_VULKAN
#تعریف_کرو TYPE PFN_vkGetPhysicalDeviceProperties2
    حالت AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .p_اگلا = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        توڑو;
    }
#تعریف_منسوخ TYPE
#اگر_ختم
    طےشدہ:
        ret = AVERROR(ENOSYS);
        جاؤ error;
    }

    اگر (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        جاؤ error;
    }

    ret = cuda_device_init(device_ctx);
    اگر (ret < 0)
        جاؤ error;

    cu = hwctx->اندرونی_2->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    اگر (ret < 0)
        جاؤ error;

    ret = CHECK_CU(cu->cu_Device_Get_گنتی(&device_گنتی));
    اگر (ret < 0)
        جاؤ error;

    hwctx->اندرونی_2->cuda_device = -1;
    برائے (i = 0; i < device_گنتی; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        اگر (ret < 0)
            جاؤ error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        اگر (ret < 0)
            جاؤ error;

        اگر (memcmp(src_uuid, uuid.بائٹیں, حجم (uuid.بائٹیں)) == 0) {
            hwctx->اندرونی_2->cuda_device = dev;
            توڑو;
        }
    }

    اگر (hwctx->اندرونی_2->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        جاؤ error;
    }

    ret = cuda_context_init(device_ctx, flags);
    اگر (ret < 0)
        جاؤ error;

    واپس 0;

error:
    cuda_device_uninit(device_ctx);
    واپس ret;
}

ثابت HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_سائز    = حجم(CUDADeviceContext),
    .چوکھٹے_hwctx_سائز    = حجم(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .چوکھٹے_get_constraints = cuda_چوکھٹے_get_constraints,
    .چوکھٹے_init          = cuda_چوکھٹے_init,
    .چوکھٹے_uninit        = cuda_چوکھٹے_uninit,
    .چوکھٹے_get_بفر    = cuda_get_بفر,
    .transfer_get_formats = cuda_transfer_get_formats,
#اگر HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_بفر_alloc = cuda_transfer_بفر_alloc,
#اگر_ختم
    .transfer_ڈیٹا_مقصد     = cuda_transfer_ڈیٹا,
    .transfer_ڈیٹا_from   = cuda_transfer_ڈیٹا,

    .pix_fmts             = (ثابت شمار AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#اگر HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#اگر_ختم
                                                          AV_PIX_FMT_NONE },
};
