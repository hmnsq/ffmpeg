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

#അന്തര്ഭാവ "buffer.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "hwcontext.h"
#അന്തര്ഭാവ "hwcontext_internal.h"
#അന്തര്ഭാവ "hwcontext_cuda_internal.h"
#എങ്കിൽ CONFIG_VULKAN
#അന്തര്ഭാവ "hwcontext_vulkan.h"
#endif
#അന്തര്ഭാവ "cuda_check.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "pixdesc.h"
#അന്തര്ഭാവ "pixfmt.h"
#അന്തര്ഭാവ "imgutils.h"

തരനിർവചനം ഘടന CUDAFramesContext {
    AVCUDAFramesContext p;

    പൂർണ്ണസംഖ്യ shift_width, shift_height;
    പൂർണ്ണസംഖ്യ tex_alignment;

    പൂർണ്ണസംഖ്യ cuarray_അക്കം_surfaces_used;
} CUDAFramesContext;

തരനിർവചനം ഘടന CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADeviceContextInternal internal;
} CUDADeviceContext;



#define CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

സ്ഥിതം CUarray_format cuda_array_format_for_pix_fmt(എണ്ണൽ AVPixelFormat fmt);

സ്ഥിതം പൂർണ്ണസംഖ്യ cuda_frames_get_constraints(AVHWDeviceContext *ctx,
                                       സ്ഥിരം ശൂന്യം *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    സ്ഥിരം AVCUDAHWConfig *config = hwconfig;
    എണ്ണൽ AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    പൂർണ്ണസംഖ്യ n = 0;

    എങ്കിൽ (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, വലുപ്പം(*constraints->valid_hw_formats));
        എങ്കിൽ (!constraints->valid_hw_formats)
            തിരികെ AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } അല്ലെങ്കിൽ {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, വലുപ്പം(*constraints->valid_hw_formats));
        എങ്കിൽ (!constraints->valid_hw_formats)
            തിരികെ AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#എങ്കിൽ HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#അല്ലെങ്കിൽ
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#endif
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    വലുപ്പം(*constraints->valid_sw_formats));
    എങ്കിൽ (!constraints->valid_sw_formats)
        തിരികെ AVERROR(ENOMEM);

    n = 0;
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < AV_PIX_FMT_NB; i++) {
        എങ്കിൽ (req_fmt == AV_PIX_FMT_CUARRAY) {
            എങ്കിൽ (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } അല്ലെങ്കിൽ {
            സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            എങ്കിൽ (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#എങ്കിൽ CONFIG_VULKAN
    എങ്കിൽ (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#endif
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം cuda_buffer_free(ശൂന്യം *opaque, uint8_t *data)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_തള്ളുക_Current(hwctx->cuda_ctx));

    എങ്കിൽ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)data;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } അല്ലെങ്കിൽ {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)data));
    }

    CHECK_CU(cu->cu_Ctx_എടുക്കുക_Current(&dummy));
}

സ്ഥിതം AVBufferRef *cuda_pool_alloc(ശൂന്യം *opaque, size_t size)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    AVBufferRef *ret = ശൂന്യ;
    CUcontext dummy = ശൂന്യ;
    CUdeviceptr data;
    പൂർണ്ണസംഖ്യ err;

    err = CHECK_CU(cu->cu_Ctx_തള്ളുക_Current(hwctx->cuda_ctx));
    എങ്കിൽ (err < 0)
        തിരികെ ശൂന്യ;

    എങ്കിൽ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = av_mallocz(വലുപ്പം(*desc));
        എങ്കിൽ (!desc)
            പോകുക done;

        എങ്കിൽ (priv->p.cuarray_അക്കം_surfaces > 0) {
            എങ്കിൽ (priv->cuarray_അക്കം_surfaces_used >= priv->p.cuarray_അക്കം_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                പോകുക done;
            }
            desc->index = priv->cuarray_അക്കം_surfaces_used++;
            desc->array = priv->p.cuarray_surfaces[desc->index];
        } അല്ലെങ്കിൽ {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            എങ്കിൽ (err < 0) {
                av_free(desc);
                പോകുക done;
            }
        }

        ret = av_buffer_create((uint8_t*)desc, വലുപ്പം(*desc), cuda_buffer_free, ctx, 0);
        എങ്കിൽ (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            പോകുക done;
        }

        പോകുക done;
    }

    err = CHECK_CU(cu->cuMemAlloc(&data, size));
    എങ്കിൽ (err < 0)
        പോകുക done;

    ret = av_buffer_create((uint8_t*)data, size, cuda_buffer_free, ctx, 0);
    എങ്കിൽ (!ret) {
        CHECK_CU(cu->cuMemFree(data));
        പോകുക done;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
done:
    CHECK_CU(cu->cu_Ctx_എടുക്കുക_Current(&dummy));
    തിരികെ ret;
}

#എങ്കിൽ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
സ്ഥിതം ശൂന്യം cuda_transfer_buffer_free(ശൂന്യം *opaque, uint8_t *data)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_തള്ളുക_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(data));
    CHECK_CU(cu->cu_Ctx_എടുക്കുക_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
സ്ഥിതം AVBufferRef *cuda_transfer_buffer_alloc(ശൂന്യം *device_ref, size_t size)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->data;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    AVBufferRef *ret = ശൂന്യ;
    CUcontext dummy;
    ശൂന്യം *host;

    എങ്കിൽ (CHECK_CU(cu->cu_Ctx_തള്ളുക_Current(hwctx->cuda_ctx)) < 0)
        തിരികെ av_buffer_alloc(size);

    എങ്കിൽ (CHECK_CU(cu->cuMemHostAlloc(&host, size, 0)) >= 0) {
        ret = av_buffer_create(host, size, cuda_transfer_buffer_free, device_ctx, 0);
        എങ്കിൽ (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_എടുക്കുക_Current(&dummy));
    തിരികെ ret ? ret : av_buffer_alloc(size);
}
#endif

സ്ഥിതം ശൂന്യം cuda_frames_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    എങ്കിൽ (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_തള്ളുക_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = priv->cuarray_അക്കം_surfaces_used; i < priv->p.cuarray_അക്കം_surfaces; i++)
            എങ്കിൽ (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_എടുക്കുക_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_അക്കം_surfaces = 0;
    }
}

സ്ഥിതം CUarray_format cuda_array_format_for_pix_fmt(എണ്ണൽ AVPixelFormat fmt)
{
    തിരഞ്ഞെടുപ്പ് (fmt) {
#എങ്കിൽ HAVE_FFNVCODEC_CUARRAY
    അവസ്ഥ AV_PIX_FMT_NV12:      തിരികെ CU_AD_FORMAT_NV12;
    അവസ്ഥ AV_PIX_FMT_P010:
    അവസ്ഥ AV_PIX_FMT_P012:
    അവസ്ഥ AV_PIX_FMT_P016:      തിരികെ CU_AD_FORMAT_P016;
    അവസ്ഥ AV_PIX_FMT_NV16:      തിരികെ CU_AD_FORMAT_NV16;
    അവസ്ഥ AV_PIX_FMT_P210:
    അവസ്ഥ AV_PIX_FMT_P212:
    അവസ്ഥ AV_PIX_FMT_P216:      തിരികെ CU_AD_FORMAT_P216;
    അവസ്ഥ AV_PIX_FMT_NV24:      തിരികെ CU_AD_FORMAT_YUV444_8BIT_SEMIPLANAR;
    അവസ്ഥ AV_PIX_FMT_P410:
    അവസ്ഥ AV_PIX_FMT_P412:
    അവസ്ഥ AV_PIX_FMT_P416:      തിരികെ CU_AD_FORMAT_YUV444_16BIT_SEMIPLANAR;
    അവസ്ഥ AV_PIX_FMT_YUV420P:   തിരികെ CU_AD_FORMAT_UINT8_PLANAR_420;
    അവസ്ഥ AV_PIX_FMT_YUV422P:   തിരികെ CU_AD_FORMAT_UINT8_PLANAR_422;
    അവസ്ഥ AV_PIX_FMT_YUV444P:   തിരികെ CU_AD_FORMAT_UINT8_PLANAR_444;
    അവസ്ഥ AV_PIX_FMT_YUV420P10: തിരികെ CU_AD_FORMAT_UINT16_PLANAR_420;
    അവസ്ഥ AV_PIX_FMT_YUV422P10: തിരികെ CU_AD_FORMAT_UINT16_PLANAR_422;
    അവസ്ഥ AV_PIX_FMT_YUV444P10:
    അവസ്ഥ AV_PIX_FMT_YUV444P10MSB:
    അവസ്ഥ AV_PIX_FMT_YUV444P12MSB:
    അവസ്ഥ AV_PIX_FMT_YUV444P16: തിരികെ CU_AD_FORMAT_UINT16_PLANAR_444;
    അവസ്ഥ AV_PIX_FMT_0RGB32:
    അവസ്ഥ AV_PIX_FMT_0BGR32:
    അവസ്ഥ AV_PIX_FMT_RGB32:
    അവസ്ഥ AV_PIX_FMT_BGR32:     തിരികെ CU_AD_FORMAT_UNSIGNED_INT8;
#endif
    സ്ഥിരസ്ഥിതി:                   തിരികെ 0;
    }
}

#എങ്കിൽ HAVE_FFNVCODEC_CUARRAY
സ്ഥിതം unsigned പൂർണ്ണസംഖ്യ cuda_array_numchannels_for_pix_fmt(എണ്ണൽ AVPixelFormat fmt)
{
    തിരഞ്ഞെടുപ്പ് (fmt) {
    അവസ്ഥ AV_PIX_FMT_0RGB32:
    അവസ്ഥ AV_PIX_FMT_0BGR32:
    അവസ്ഥ AV_PIX_FMT_RGB32:
    അവസ്ഥ AV_PIX_FMT_BGR32:     തിരികെ 4;
    സ്ഥിരസ്ഥിതി:                   തിരികെ 3;
    }
}
#endif

സ്ഥിതം പൂർണ്ണസംഖ്യ cuda_frames_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    പൂർണ്ണസംഖ്യ err;

    എങ്കിൽ (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        തിരികെ AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    എങ്കിൽ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        തിരികെ AVERROR(ENOSYS);
    }

#എങ്കിൽ HAVE_FFNVCODEC_CUARRAY
    എങ്കിൽ (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        തിരികെ AVERROR(ENOSYS);
    }
#അല്ലെങ്കിൽ
    എങ്കിൽ (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        തിരികെ AVERROR(ENOSYS);
    }
#endif

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->internal->cuda_device));
    എങ്കിൽ (err < 0)
        തിരികെ err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    എങ്കിൽ (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->shift_width, &priv->shift_height);

#എങ്കിൽ HAVE_FFNVCODEC_CUARRAY
    എങ്കിൽ (ctx->format == AV_PIX_FMT_CUARRAY) {
        എങ്കിൽ (!priv->p.cuarray_desc.Width)
            priv->p.cuarray_desc.Width = ctx->width;
        എങ്കിൽ (!priv->p.cuarray_desc.Height)
            priv->p.cuarray_desc.Height = ctx->height;
        എങ്കിൽ (!priv->p.cuarray_desc.അക്കം_Channels)
            priv->p.cuarray_desc.അക്കം_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        എങ്കിൽ (priv->p.cuarray_desc.Depth) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            തിരികെ AVERROR(EINVAL);
        }

        എങ്കിൽ (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        എങ്കിൽ (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            തിരികെ AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    എങ്കിൽ (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_അക്കം_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_അക്കം_surfaces, വലുപ്പം(*priv->p.cuarray_surfaces));
        എങ്കിൽ (!priv->p.cuarray_surfaces)
            തിരികെ AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_തള്ളുക_Current(hwctx->cuda_ctx));
        എങ്കിൽ (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            തിരികെ err;
        }

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < priv->p.cuarray_അക്കം_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            എങ്കിൽ (err < 0) {
                വേണ്ടി (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_എടുക്കുക_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                തിരികെ err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_എടുക്കുക_Current(&dummy));
        എങ്കിൽ (err < 0)
            പോകുക fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_അക്കം_surfaces, priv->p.cuarray_desc.Width, priv->p.cuarray_desc.Height);
    }
#endif

    എങ്കിൽ (!ctx->pool) {
        പൂർണ്ണസംഖ്യ size = av_image_get_buffer_size(ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        എങ്കിൽ (size < 0) {
            err = size;
            പോകുക fail;
        }

        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(size, ctx, cuda_pool_alloc, ശൂന്യ);
        എങ്കിൽ (!ffhwframesctx(ctx)->pool_internal) {
            err = AVERROR(ENOMEM);
            പോകുക fail;
        }
    }

    തിരികെ 0;

fail:
    cuda_frames_uninit(ctx);
    തിരികെ err;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ cuda_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#എങ്കിൽ HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;
#endif
    പൂർണ്ണസംഖ്യ res;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    എങ്കിൽ (!frame->buf[0])
        തിരികെ AVERROR(ENOMEM);

    എങ്കിൽ (ctx->format == AV_PIX_FMT_CUARRAY) {
#എങ്കിൽ HAVE_FFNVCODEC_CUARRAY
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)frame->buf[0]->data;
        എങ്കിൽ (!desc) {
            frame->format = ctx->format;
            frame->width  = ctx->width;
            frame->height = ctx->height;
            തിരികെ 0;
        }
        frame->data[0] = (uint8_t*)desc->array;
        frame->data[1] = (uint8_t*)desc->index;

        res = CHECK_CU(cu->cu_Ctx_തള്ളുക_Current(hwctx->cuda_ctx));
        എങ്കിൽ (res < 0)
            തിരികെ res;

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(frame->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            എങ്കിൽ (arr_plane_res == CUDA_ERROR_INVALID_മൂല്യം) {
                എങ്കിൽ (i > 0)
                    നിർത്തുക;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                എങ്കിൽ (res < 0)
                    പോകുക fail;
            } അല്ലെങ്കിൽ എങ്കിൽ (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                പോകുക fail;
            } അല്ലെങ്കിൽ {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                എങ്കിൽ (res < 0)
                    പോകുക fail;
            }

            പൂർണ്ണസംഖ്യ elem_size = ff_cuda_cuarray_elem_size(plane_desc.Format);
            എങ്കിൽ (elem_size <= 0) {
                res = AVERROR_BUG;
                പോകുക fail;
            }

            frame->linesize[i] = plane_desc.Width * plane_desc.അക്കം_Channels * elem_size;

            എങ്കിൽ (arr_plane_res == CUDA_ERROR_INVALID_മൂല്യം)
                നിർത്തുക;
        }

        res = CHECK_CU(cu->cu_Ctx_എടുക്കുക_Current(&dummy));
        എങ്കിൽ (res < 0)
            തിരികെ res;
#അല്ലെങ്കിൽ
        തിരികെ AVERROR(ENOSYS);
#endif
    } അല്ലെങ്കിൽ {
        res = av_image_fill_arrays(frame->data, frame->linesize, frame->buf[0]->data,
                                   ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        എങ്കിൽ (res < 0)
            തിരികെ res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        എങ്കിൽ (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
            frame->data[2]     = frame->data[1];
            frame->data[1]     = frame->data[2] + frame->linesize[2] * AV_CEIL_RSHIFT(ctx->height, 1);
        }
    }

    frame->format = ctx->format;
    frame->width  = ctx->width;
    frame->height = ctx->height;

    തിരികെ 0;

#എങ്കിൽ HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_എടുക്കുക_Current(&dummy));
    തിരികെ res;
#endif
}

സ്ഥിതം എണ്ണൽ AVPixelFormat cuda_frame_hw_format(സ്ഥിരം AVFrame *frame)
{
    എങ്കിൽ (!frame->hw_frames_ctx)
        തിരികെ AV_PIX_FMT_NONE;
    തിരികെ ((AVHWFramesContext *)frame->hw_frames_ctx->data)->format;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     എണ്ണൽ AVHWFrameTransferDirection dir,
                                     എണ്ണൽ AVPixelFormat **formats)
{
    എണ്ണൽ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, വലുപ്പം(*fmts));
    എങ്കിൽ (!fmts)
        തിരികെ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ cuda_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 സ്ഥിരം AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    സ്ഥിരം AVFrame *sw_frame = src->hw_frames_ctx ? dst : src;
    AVFrame *മുകൾ_down = ശൂന്യ, *bottom_up_dst = ശൂന്യ;
    CUcontext dummy;
    പൂർണ്ണസംഖ്യ i, ret, copy_queued = 0, bottom_up = 0;

    {
        എണ്ണൽ AVPixelFormat src_fmt = cuda_frame_hw_format(src);
        എണ്ണൽ AVPixelFormat dst_fmt = cuda_frame_hw_format(dst);
        എങ്കിൽ ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            തിരികെ AVERROR(ENOSYS);
    }

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(sw_frame->linesize); i++)
        bottom_up |= sw_frame->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    എങ്കിൽ (bottom_up) {
        മുകൾ_down = av_frame_alloc();
        എങ്കിൽ (!മുകൾ_down)
            തിരികെ AVERROR(ENOMEM);
        മുകൾ_down->format = ctx->sw_format;
        മുകൾ_down->width  = ctx->width;
        മുകൾ_down->height = ctx->height;
        ret = av_hwframe_get_transfer_buffer((src->hw_frames_ctx ? src : dst)->hw_frames_ctx,
                                             മുകൾ_down);
        എങ്കിൽ (ret < 0)
            പോകുക free_മുകൾ_down;
        മുകൾ_down->width  = src->width;
        മുകൾ_down->height = src->height;
        എങ്കിൽ (sw_frame == src) {
            av_image_copy2(മുകൾ_down->data, മുകൾ_down->linesize, src->data, src->linesize,
                           ctx->sw_format, src->width, src->height);
            src = മുകൾ_down;
        } അല്ലെങ്കിൽ {
            bottom_up_dst = dst;
            dst           = മുകൾ_down;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_തള്ളുക_Current(hwctx->cuda_ctx));
    എങ്കിൽ (ret < 0)
        പോകുക free_മുകൾ_down;

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
    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(src->data) && src->linesize[i]; i++) {
        പൂർണ്ണസംഖ്യ src_is_nonplanar_cuarray = 0;
        പൂർണ്ണസംഖ്യ dst_is_nonplanar_cuarray = 0;

        പൂർണ്ണസംഖ്യ bytewidth = av_image_get_linesize(ctx->sw_format, src->width, i);
        എങ്കിൽ (bytewidth < 0) {
            ret = bytewidth;
            പോകുക fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .WidthInBytes  = bytewidth,
            .Height        = AV_CEIL_RSHIFT(src->height, ((i == 0 || i == 3) ? 0 : priv->shift_height)),
        };

        എങ്കിൽ (src->format == AV_PIX_FMT_CUDA) {
            cpy.srcMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->data[i];
        } അല്ലെങ്കിൽ എങ്കിൽ (src->format == AV_PIX_FMT_CUARRAY) {
#എങ്കിൽ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->data[0], i);
            എങ്കിൽ (cures == CUDA_ERROR_INVALID_മൂല്യം && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->data[0];
                src_is_nonplanar_cuarray = 1;
            } അല്ലെങ്കിൽ എങ്കിൽ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                പോകുക fail;
            }

            cpy.srcMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#അല്ലെങ്കിൽ
            ret = AVERROR(ENOSYS);
            പോകുക exit;
#endif
        } അല്ലെങ്കിൽ {
            cpy.srcMemoryType = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->data[i];
        }

        എങ്കിൽ (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dstMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->data[i];
        } അല്ലെങ്കിൽ എങ്കിൽ (dst->format == AV_PIX_FMT_CUARRAY) {
#എങ്കിൽ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->data[0], i);
            എങ്കിൽ (cures == CUDA_ERROR_INVALID_മൂല്യം && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->data[0];
                dst_is_nonplanar_cuarray = 1;
            } അല്ലെങ്കിൽ എങ്കിൽ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                പോകുക fail;
            }

            cpy.dstMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#അല്ലെങ്കിൽ
            ret = AVERROR(ENOSYS);
            പോകുക exit;
#endif
        } അല്ലെങ്കിൽ {
            cpy.dstMemoryType = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->data[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->stream));
        എങ്കിൽ (ret < 0)
            പോകുക fail;
        copy_queued = 1;

        എങ്കിൽ (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            നിർത്തുക;
    }

    /* The caller may reuse host memory once the transfer returns. */
    എങ്കിൽ (!src->hw_frames_ctx || !dst->hw_frames_ctx) {
        ret = CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
        എങ്കിൽ (ret < 0)
            പോകുക exit;
    }

fail:
    എങ്കിൽ (ret < 0 && copy_queued)
        CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
exit:
    CHECK_CU(cu->cu_Ctx_എടുക്കുക_Current(&dummy));

    എങ്കിൽ (bottom_up_dst && ret >= 0)
        av_image_copy2(bottom_up_dst->data, bottom_up_dst->linesize,
                       മുകൾ_down->data, മുകൾ_down->linesize,
                       ctx->sw_format, src->width, src->height);
free_മുകൾ_down:
    av_frame_free(&മുകൾ_down);

    തിരികെ ret;
}

സ്ഥിതം ശൂന്യം cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    എങ്കിൽ (hwctx->p.internal) {
        CudaFunctions *cu = hwctx->internal.cuda_dl;

        എങ്കിൽ (hwctx->internal.is_allocated && hwctx->p.cuda_ctx) {
            എങ്കിൽ (hwctx->internal.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->internal.cuda_device));
            അല്ലെങ്കിൽ എങ്കിൽ (!(hwctx->internal.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = ശൂന്യ;
        }

        cuda_free_functions(&hwctx->internal.cuda_dl);
        memset(&hwctx->internal, 0, വലുപ്പം(hwctx->internal));
        hwctx->p.internal = ശൂന്യ;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    പൂർണ്ണസംഖ്യ ret;

    hwctx->p.internal = &hwctx->internal;

    എങ്കിൽ (!hwctx->internal.cuda_dl) {
        ret = cuda_load_functions(&hwctx->internal.cuda_dl, ctx);
        എങ്കിൽ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            പോകുക error;
        }
    }

    തിരികെ 0;

error:
    cuda_device_uninit(ctx);
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ cuda_context_init(AVHWDeviceContext *device_ctx, പൂർണ്ണസംഖ്യ flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    പൂർണ്ണസംഖ്യ ret, dev_active = 0;
    unsigned പൂർണ്ണസംഖ്യ dev_flags = 0;

    സ്ഥിരം unsigned പൂർണ്ണസംഖ്യ desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->internal->cuda_dl;

    hwctx->internal->flags = flags;

    എങ്കിൽ (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->internal->cuda_device,
                       &dev_flags, &dev_active));
        എങ്കിൽ (ret < 0)
            തിരികെ ret;

        എങ്കിൽ (dev_active && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            തിരികെ AVERROR(ENOTSUP);
        } അല്ലെങ്കിൽ എങ്കിൽ (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cuDevicePrimaryCtxSetFlags(hwctx->internal->cuda_device,
                           desired_flags));
            എങ്കിൽ (ret < 0)
                തിരികെ ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->internal->cuda_device));
        എങ്കിൽ (ret < 0)
            തിരികെ ret;
    } അല്ലെങ്കിൽ എങ്കിൽ (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        എങ്കിൽ (ret < 0)
            തിരികെ ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } അല്ലെങ്കിൽ {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->internal->cuda_device));
        എങ്കിൽ (ret < 0)
            തിരികെ ret;

        CHECK_CU(cu->cu_Ctx_എടുക്കുക_Current(&dummy));
    }

    hwctx->internal->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->stream = ശൂന്യ;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, പൂർണ്ണസംഖ്യ *flags)
{
    AVDictionaryEntry *primary_ctx_opt = av_dict_get(opts, "primary_ctx", ശൂന്യ, 0);
    AVDictionaryEntry *current_ctx_opt = av_dict_get(opts, "current_ctx", ശൂന്യ, 0);

    പൂർണ്ണസംഖ്യ use_primary_ctx = 0, use_current_ctx = 0;
    എങ്കിൽ (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->മൂല്യം, ശൂന്യ, 10);

    എങ്കിൽ (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->മൂല്യം, ശൂന്യ, 10);

    എങ്കിൽ (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        തിരികെ AVERROR(EINVAL);
    }

    എങ്കിൽ (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } അല്ലെങ്കിൽ എങ്കിൽ (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    എങ്കിൽ (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } അല്ലെങ്കിൽ എങ്കിൽ (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ cuda_device_create(AVHWDeviceContext *device_ctx,
                              സ്ഥിരം അക്ഷരം *device,
                              AVDictionary *opts, പൂർണ്ണസംഖ്യ flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    പൂർണ്ണസംഖ്യ ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    എങ്കിൽ (ret < 0)
        പോകുക error;

    എങ്കിൽ (device)
        device_idx = strtol(device, ശൂന്യ, 0);

    ret = cuda_device_init(device_ctx);
    എങ്കിൽ (ret < 0)
        പോകുക error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    എങ്കിൽ (ret < 0)
        പോകുക error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->internal->cuda_device, device_idx));
    എങ്കിൽ (ret < 0)
        പോകുക error;

    ret = cuda_context_init(device_ctx, flags);
    എങ്കിൽ (ret < 0)
        പോകുക error;

    തിരികെ 0;

error:
    cuda_device_uninit(device_ctx);
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              പൂർണ്ണസംഖ്യ flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    സ്ഥിരം അക്ഷരം *src_uuid = ശൂന്യ;
#എങ്കിൽ CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#endif
    പൂർണ്ണസംഖ്യ ret, i, device_എണ്ണം;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    എങ്കിൽ (ret < 0)
        പോകുക error;

#എങ്കിൽ CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#endif

    തിരഞ്ഞെടുപ്പ് (src_ctx->type) {
#എങ്കിൽ CONFIG_VULKAN
#define TYPE PFN_vkGetPhysicalDeviceProperties2
    അവസ്ഥ AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .pNext = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        നിർത്തുക;
    }
#undef TYPE
#endif
    സ്ഥിരസ്ഥിതി:
        ret = AVERROR(ENOSYS);
        പോകുക error;
    }

    എങ്കിൽ (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        പോകുക error;
    }

    ret = cuda_device_init(device_ctx);
    എങ്കിൽ (ret < 0)
        പോകുക error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    എങ്കിൽ (ret < 0)
        പോകുക error;

    ret = CHECK_CU(cu->cu_Device_Get_എണ്ണം(&device_എണ്ണം));
    എങ്കിൽ (ret < 0)
        പോകുക error;

    hwctx->internal->cuda_device = -1;
    വേണ്ടി (i = 0; i < device_എണ്ണം; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        എങ്കിൽ (ret < 0)
            പോകുക error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        എങ്കിൽ (ret < 0)
            പോകുക error;

        എങ്കിൽ (memcmp(src_uuid, uuid.bytes, വലുപ്പം (uuid.bytes)) == 0) {
            hwctx->internal->cuda_device = dev;
            നിർത്തുക;
        }
    }

    എങ്കിൽ (hwctx->internal->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        പോകുക error;
    }

    ret = cuda_context_init(device_ctx, flags);
    എങ്കിൽ (ret < 0)
        പോകുക error;

    തിരികെ 0;

error:
    cuda_device_uninit(device_ctx);
    തിരികെ ret;
}

സ്ഥിരം HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_size    = വലുപ്പം(CUDADeviceContext),
    .frames_hwctx_size    = വലുപ്പം(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .frames_get_constraints = cuda_frames_get_constraints,
    .frames_init          = cuda_frames_init,
    .frames_uninit        = cuda_frames_uninit,
    .frames_get_buffer    = cuda_get_buffer,
    .transfer_get_formats = cuda_transfer_get_formats,
#എങ്കിൽ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_buffer_alloc = cuda_transfer_buffer_alloc,
#endif
    .transfer_data_to     = cuda_transfer_data,
    .transfer_data_from   = cuda_transfer_data,

    .pix_fmts             = (സ്ഥിരം എണ്ണൽ AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#എങ്കിൽ HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#endif
                                                          AV_PIX_FMT_NONE },
};
