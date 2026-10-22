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

#ଅନ୍ତର୍ଭାଵ "buffer.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_internal.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_cuda_internal.h"
#ଯଦି CONFIG_VULKAN
#ଅନ୍ତର୍ଭାଵ "hwcontext_vulkan.h"
#endif
#ଅନ୍ତର୍ଭାଵ "cuda_check.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "pixdesc.h"
#ଅନ୍ତର୍ଭାଵ "pixfmt.h"
#ଅନ୍ତର୍ଭାଵ "imgutils.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା CUDAFramesContext {
    AVCUDAFramesContext p;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା shift_width, shift_height;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା tex_alignment;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cuarray_ଅଙ୍କ_surfaces_used;
} CUDAFramesContext;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADeviceContextInternal internal;
} CUDADeviceContext;



#define CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

ସ୍ଥିର CUarray_format cuda_array_format_for_pix_fmt(ଗଣନା AVPixelFormat fmt);

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cuda_frames_get_constraints(AVHWDeviceContext *ctx,
                                       ଅଚଳ ଶୂନ୍ୟ *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    ଅଚଳ AVCUDAHWConfig *config = hwconfig;
    ଗଣନା AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = 0;

    ଯଦି (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, ଆକାର(*constraints->valid_hw_formats));
        ଯଦି (!constraints->valid_hw_formats)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } ଅନ୍ୟଥା {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, ଆକାର(*constraints->valid_hw_formats));
        ଯଦି (!constraints->valid_hw_formats)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#ଯଦି HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#ଅନ୍ୟଥା
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#endif
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    ଆକାର(*constraints->valid_sw_formats));
    ଯଦି (!constraints->valid_sw_formats)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    n = 0;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < AV_PIX_FMT_NB; i++) {
        ଯଦି (req_fmt == AV_PIX_FMT_CUARRAY) {
            ଯଦି (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } ଅନ୍ୟଥା {
            ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            ଯଦି (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#ଯଦି CONFIG_VULKAN
    ଯଦି (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#endif
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ cuda_buffer_free(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ଠେଲ_Current(hwctx->cuda_ctx));

    ଯଦି (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)data;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } ଅନ୍ୟଥା {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)data));
    }

    CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));
}

ସ୍ଥିର AVBufferRef *cuda_pool_alloc(ଶୂନ୍ୟ *opaque, size_t size)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    AVBufferRef *ret = ଖାଲି;
    CUcontext dummy = ଖାଲି;
    CUdeviceptr data;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    err = CHECK_CU(cu->cu_Ctx_ଠେଲ_Current(hwctx->cuda_ctx));
    ଯଦି (err < 0)
        ଫେରନ୍ତୁ ଖାଲି;

    ଯଦି (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = av_mallocz(ଆକାର(*desc));
        ଯଦି (!desc)
            ଯାଅ done;

        ଯଦି (priv->p.cuarray_ଅଙ୍କ_surfaces > 0) {
            ଯଦି (priv->cuarray_ଅଙ୍କ_surfaces_used >= priv->p.cuarray_ଅଙ୍କ_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                ଯାଅ done;
            }
            desc->index = priv->cuarray_ଅଙ୍କ_surfaces_used++;
            desc->array = priv->p.cuarray_surfaces[desc->index];
        } ଅନ୍ୟଥା {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            ଯଦି (err < 0) {
                av_free(desc);
                ଯାଅ done;
            }
        }

        ret = av_buffer_create((uint8_t*)desc, ଆକାର(*desc), cuda_buffer_free, ctx, 0);
        ଯଦି (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            ଯାଅ done;
        }

        ଯାଅ done;
    }

    err = CHECK_CU(cu->cuMemAlloc(&data, size));
    ଯଦି (err < 0)
        ଯାଅ done;

    ret = av_buffer_create((uint8_t*)data, size, cuda_buffer_free, ctx, 0);
    ଯଦି (!ret) {
        CHECK_CU(cu->cuMemFree(data));
        ଯାଅ done;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
done:
    CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));
    ଫେରନ୍ତୁ ret;
}

#ଯଦି HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
ସ୍ଥିର ଶୂନ୍ୟ cuda_transfer_buffer_free(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cu_Ctx_ଠେଲ_Current(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(data));
    CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
ସ୍ଥିର AVBufferRef *cuda_transfer_buffer_alloc(ଶୂନ୍ୟ *device_ref, size_t size)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->data;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    AVBufferRef *ret = ଖାଲି;
    CUcontext dummy;
    ଶୂନ୍ୟ *host;

    ଯଦି (CHECK_CU(cu->cu_Ctx_ଠେଲ_Current(hwctx->cuda_ctx)) < 0)
        ଫେରନ୍ତୁ av_buffer_alloc(size);

    ଯଦି (CHECK_CU(cu->cuMemHostAlloc(&host, size, 0)) >= 0) {
        ret = av_buffer_create(host, size, cuda_transfer_buffer_free, device_ctx, 0);
        ଯଦି (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));
    ଫେରନ୍ତୁ ret ? ret : av_buffer_alloc(size);
}
#endif

ସ୍ଥିର ଶୂନ୍ୟ cuda_frames_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    ଯଦି (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cu_Ctx_ଠେଲ_Current(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = priv->cuarray_ଅଙ୍କ_surfaces_used; i < priv->p.cuarray_ଅଙ୍କ_surfaces; i++)
            ଯଦି (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_ଅଙ୍କ_surfaces = 0;
    }
}

ସ୍ଥିର CUarray_format cuda_array_format_for_pix_fmt(ଗଣନା AVPixelFormat fmt)
{
    ବାଛ (fmt) {
#ଯଦି HAVE_FFNVCODEC_CUARRAY
    ସ୍ଥିତି AV_PIX_FMT_NV12:      ଫେରନ୍ତୁ CU_AD_FORMAT_NV12;
    ସ୍ଥିତି AV_PIX_FMT_P010:
    ସ୍ଥିତି AV_PIX_FMT_P012:
    ସ୍ଥିତି AV_PIX_FMT_P016:      ଫେରନ୍ତୁ CU_AD_FORMAT_P016;
    ସ୍ଥିତି AV_PIX_FMT_NV16:      ଫେରନ୍ତୁ CU_AD_FORMAT_NV16;
    ସ୍ଥିତି AV_PIX_FMT_P210:
    ସ୍ଥିତି AV_PIX_FMT_P212:
    ସ୍ଥିତି AV_PIX_FMT_P216:      ଫେରନ୍ତୁ CU_AD_FORMAT_P216;
    ସ୍ଥିତି AV_PIX_FMT_NV24:      ଫେରନ୍ତୁ CU_AD_FORMAT_YUV444_8BIT_SEMIPLANAR;
    ସ୍ଥିତି AV_PIX_FMT_P410:
    ସ୍ଥିତି AV_PIX_FMT_P412:
    ସ୍ଥିତି AV_PIX_FMT_P416:      ଫେରନ୍ତୁ CU_AD_FORMAT_YUV444_16BIT_SEMIPLANAR;
    ସ୍ଥିତି AV_PIX_FMT_YUV420P:   ଫେରନ୍ତୁ CU_AD_FORMAT_UINT8_PLANAR_420;
    ସ୍ଥିତି AV_PIX_FMT_YUV422P:   ଫେରନ୍ତୁ CU_AD_FORMAT_UINT8_PLANAR_422;
    ସ୍ଥିତି AV_PIX_FMT_YUV444P:   ଫେରନ୍ତୁ CU_AD_FORMAT_UINT8_PLANAR_444;
    ସ୍ଥିତି AV_PIX_FMT_YUV420P10: ଫେରନ୍ତୁ CU_AD_FORMAT_UINT16_PLANAR_420;
    ସ୍ଥିତି AV_PIX_FMT_YUV422P10: ଫେରନ୍ତୁ CU_AD_FORMAT_UINT16_PLANAR_422;
    ସ୍ଥିତି AV_PIX_FMT_YUV444P10:
    ସ୍ଥିତି AV_PIX_FMT_YUV444P10MSB:
    ସ୍ଥିତି AV_PIX_FMT_YUV444P12MSB:
    ସ୍ଥିତି AV_PIX_FMT_YUV444P16: ଫେରନ୍ତୁ CU_AD_FORMAT_UINT16_PLANAR_444;
    ସ୍ଥିତି AV_PIX_FMT_0RGB32:
    ସ୍ଥିତି AV_PIX_FMT_0BGR32:
    ସ୍ଥିତି AV_PIX_FMT_RGB32:
    ସ୍ଥିତି AV_PIX_FMT_BGR32:     ଫେରନ୍ତୁ CU_AD_FORMAT_UNSIGNED_INT8;
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:                   ଫେରନ୍ତୁ 0;
    }
}

#ଯଦି HAVE_FFNVCODEC_CUARRAY
ସ୍ଥିର unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା cuda_array_numchannels_for_pix_fmt(ଗଣନା AVPixelFormat fmt)
{
    ବାଛ (fmt) {
    ସ୍ଥିତି AV_PIX_FMT_0RGB32:
    ସ୍ଥିତି AV_PIX_FMT_0BGR32:
    ସ୍ଥିତି AV_PIX_FMT_RGB32:
    ସ୍ଥିତି AV_PIX_FMT_BGR32:     ଫେରନ୍ତୁ 4;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:                   ଫେରନ୍ତୁ 3;
    }
}
#endif

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cuda_frames_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    ଯଦି (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    ଯଦି (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

#ଯଦି HAVE_FFNVCODEC_CUARRAY
    ଯଦି (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }
#ଅନ୍ୟଥା
    ଯଦି (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }
#endif

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->internal->cuda_device));
    ଯଦି (err < 0)
        ଫେରନ୍ତୁ err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    ଯଦି (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->shift_width, &priv->shift_height);

#ଯଦି HAVE_FFNVCODEC_CUARRAY
    ଯଦି (ctx->format == AV_PIX_FMT_CUARRAY) {
        ଯଦି (!priv->p.cuarray_desc.Width)
            priv->p.cuarray_desc.Width = ctx->width;
        ଯଦି (!priv->p.cuarray_desc.Height)
            priv->p.cuarray_desc.Height = ctx->height;
        ଯଦି (!priv->p.cuarray_desc.ଅଙ୍କ_Channels)
            priv->p.cuarray_desc.ଅଙ୍କ_Channels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        ଯଦି (priv->p.cuarray_desc.Depth) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }

        ଯଦି (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        ଯଦି (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            ଫେରନ୍ତୁ AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    ଯଦି (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_ଅଙ୍କ_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_ଅଙ୍କ_surfaces, ଆକାର(*priv->p.cuarray_surfaces));
        ଯଦି (!priv->p.cuarray_surfaces)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        err = CHECK_CU(cu->cu_Ctx_ଠେଲ_Current(hwctx->cuda_ctx));
        ଯଦି (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            ଫେରନ୍ତୁ err;
        }

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < priv->p.cuarray_ଅଙ୍କ_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            ଯଦି (err < 0) {
                ପାଇଁ (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                ଫେରନ୍ତୁ err;
            }
        }

        err = CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));
        ଯଦି (err < 0)
            ଯାଅ fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_ଅଙ୍କ_surfaces, priv->p.cuarray_desc.Width, priv->p.cuarray_desc.Height);
    }
#endif

    ଯଦି (!ctx->pool) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା size = av_image_get_buffer_size(ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        ଯଦି (size < 0) {
            err = size;
            ଯାଅ fail;
        }

        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(size, ctx, cuda_pool_alloc, ଖାଲି);
        ଯଦି (!ffhwframesctx(ctx)->pool_internal) {
            err = AVERROR(ENOMEM);
            ଯାଅ fail;
        }
    }

    ଫେରନ୍ତୁ 0;

fail:
    cuda_frames_uninit(ctx);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cuda_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#ଯଦି HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;
#endif
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା res;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ଯଦି (!frame->buf[0])
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ଯଦି (ctx->format == AV_PIX_FMT_CUARRAY) {
#ଯଦି HAVE_FFNVCODEC_CUARRAY
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)frame->buf[0]->data;
        ଯଦି (!desc) {
            frame->format = ctx->format;
            frame->width  = ctx->width;
            frame->height = ctx->height;
            ଫେରନ୍ତୁ 0;
        }
        frame->data[0] = (uint8_t*)desc->array;
        frame->data[1] = (uint8_t*)desc->index;

        res = CHECK_CU(cu->cu_Ctx_ଠେଲ_Current(hwctx->cuda_ctx));
        ଯଦି (res < 0)
            ଫେରନ୍ତୁ res;

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(frame->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            ଯଦି (arr_plane_res == CUDA_ERROR_INVALID_ମୂଲ୍ୟ) {
                ଯଦି (i > 0)
                    ଭାଙ୍ଗ;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                ଯଦି (res < 0)
                    ଯାଅ fail;
            } ଅନ୍ୟଥା ଯଦି (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                ଯାଅ fail;
            } ଅନ୍ୟଥା {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                ଯଦି (res < 0)
                    ଯାଅ fail;
            }

            ପୂର୍ଣ୍ଣସଂଖ୍ୟା elem_size = ff_cuda_cuarray_elem_size(plane_desc.Format);
            ଯଦି (elem_size <= 0) {
                res = AVERROR_BUG;
                ଯାଅ fail;
            }

            frame->linesize[i] = plane_desc.Width * plane_desc.ଅଙ୍କ_Channels * elem_size;

            ଯଦି (arr_plane_res == CUDA_ERROR_INVALID_ମୂଲ୍ୟ)
                ଭାଙ୍ଗ;
        }

        res = CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));
        ଯଦି (res < 0)
            ଫେରନ୍ତୁ res;
#ଅନ୍ୟଥା
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
#endif
    } ଅନ୍ୟଥା {
        res = av_image_fill_arrays(frame->data, frame->linesize, frame->buf[0]->data,
                                   ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        ଯଦି (res < 0)
            ଫେରନ୍ତୁ res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        ଯଦି (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
            frame->data[2]     = frame->data[1];
            frame->data[1]     = frame->data[2] + frame->linesize[2] * AV_CEIL_RSHIFT(ctx->height, 1);
        }
    }

    frame->format = ctx->format;
    frame->width  = ctx->width;
    frame->height = ctx->height;

    ଫେରନ୍ତୁ 0;

#ଯଦି HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));
    ଫେରନ୍ତୁ res;
#endif
}

ସ୍ଥିର ଗଣନା AVPixelFormat cuda_frame_hw_format(ଅଚଳ AVFrame *frame)
{
    ଯଦି (!frame->hw_frames_ctx)
        ଫେରନ୍ତୁ AV_PIX_FMT_NONE;
    ଫେରନ୍ତୁ ((AVHWFramesContext *)frame->hw_frames_ctx->data)->format;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     ଗଣନା AVHWFrameTransferDirection dir,
                                     ଗଣନା AVPixelFormat **formats)
{
    ଗଣନା AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ଆକାର(*fmts));
    ଯଦି (!fmts)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cuda_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 ଅଚଳ AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    ଅଚଳ AVFrame *sw_frame = src->hw_frames_ctx ? dst : src;
    AVFrame *ଶୀର୍ଷ_down = ଖାଲି, *bottom_up_dst = ଖାଲି;
    CUcontext dummy;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret, copy_queued = 0, bottom_up = 0;

    {
        ଗଣନା AVPixelFormat src_fmt = cuda_frame_hw_format(src);
        ଗଣନା AVPixelFormat dst_fmt = cuda_frame_hw_format(dst);
        ଯଦି ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(sw_frame->linesize); i++)
        bottom_up |= sw_frame->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    ଯଦି (bottom_up) {
        ଶୀର୍ଷ_down = av_frame_alloc();
        ଯଦି (!ଶୀର୍ଷ_down)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        ଶୀର୍ଷ_down->format = ctx->sw_format;
        ଶୀର୍ଷ_down->width  = ctx->width;
        ଶୀର୍ଷ_down->height = ctx->height;
        ret = av_hwframe_get_transfer_buffer((src->hw_frames_ctx ? src : dst)->hw_frames_ctx,
                                             ଶୀର୍ଷ_down);
        ଯଦି (ret < 0)
            ଯାଅ free_ଶୀର୍ଷ_down;
        ଶୀର୍ଷ_down->width  = src->width;
        ଶୀର୍ଷ_down->height = src->height;
        ଯଦି (sw_frame == src) {
            av_image_copy2(ଶୀର୍ଷ_down->data, ଶୀର୍ଷ_down->linesize, src->data, src->linesize,
                           ctx->sw_format, src->width, src->height);
            src = ଶୀର୍ଷ_down;
        } ଅନ୍ୟଥା {
            bottom_up_dst = dst;
            dst           = ଶୀର୍ଷ_down;
        }
    }

    ret = CHECK_CU(cu->cu_Ctx_ଠେଲ_Current(hwctx->cuda_ctx));
    ଯଦି (ret < 0)
        ଯାଅ free_ଶୀର୍ଷ_down;

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
    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(src->data) && src->linesize[i]; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_is_nonplanar_cuarray = 0;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_is_nonplanar_cuarray = 0;

        ପୂର୍ଣ୍ଣସଂଖ୍ୟା bytewidth = av_image_get_linesize(ctx->sw_format, src->width, i);
        ଯଦି (bytewidth < 0) {
            ret = bytewidth;
            ଯାଅ fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .WidthInBytes  = bytewidth,
            .Height        = AV_CEIL_RSHIFT(src->height, ((i == 0 || i == 3) ? 0 : priv->shift_height)),
        };

        ଯଦି (src->format == AV_PIX_FMT_CUDA) {
            cpy.srcMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->data[i];
        } ଅନ୍ୟଥା ଯଦି (src->format == AV_PIX_FMT_CUARRAY) {
#ଯଦି HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->data[0], i);
            ଯଦି (cures == CUDA_ERROR_INVALID_ମୂଲ୍ୟ && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->data[0];
                src_is_nonplanar_cuarray = 1;
            } ଅନ୍ୟଥା ଯଦି (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                ଯାଅ fail;
            }

            cpy.srcMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#ଅନ୍ୟଥା
            ret = AVERROR(ENOSYS);
            ଯାଅ exit;
#endif
        } ଅନ୍ୟଥା {
            cpy.srcMemoryType = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->data[i];
        }

        ଯଦି (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dstMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->data[i];
        } ଅନ୍ୟଥା ଯଦି (dst->format == AV_PIX_FMT_CUARRAY) {
#ଯଦି HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->data[0], i);
            ଯଦି (cures == CUDA_ERROR_INVALID_ମୂଲ୍ୟ && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->data[0];
                dst_is_nonplanar_cuarray = 1;
            } ଅନ୍ୟଥା ଯଦି (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                ଯାଅ fail;
            }

            cpy.dstMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#ଅନ୍ୟଥା
            ret = AVERROR(ENOSYS);
            ଯାଅ exit;
#endif
        } ଅନ୍ୟଥା {
            cpy.dstMemoryType = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->data[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->stream));
        ଯଦି (ret < 0)
            ଯାଅ fail;
        copy_queued = 1;

        ଯଦି (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            ଭାଙ୍ଗ;
    }

    /* The caller may reuse host memory once the transfer returns. */
    ଯଦି (!src->hw_frames_ctx || !dst->hw_frames_ctx) {
        ret = CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
        ଯଦି (ret < 0)
            ଯାଅ exit;
    }

fail:
    ଯଦି (ret < 0 && copy_queued)
        CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
exit:
    CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));

    ଯଦି (bottom_up_dst && ret >= 0)
        av_image_copy2(bottom_up_dst->data, bottom_up_dst->linesize,
                       ଶୀର୍ଷ_down->data, ଶୀର୍ଷ_down->linesize,
                       ctx->sw_format, src->width, src->height);
free_ଶୀର୍ଷ_down:
    av_frame_free(&ଶୀର୍ଷ_down);

    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ଶୂନ୍ୟ cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    ଯଦି (hwctx->p.internal) {
        CudaFunctions *cu = hwctx->internal.cuda_dl;

        ଯଦି (hwctx->internal.is_allocated && hwctx->p.cuda_ctx) {
            ଯଦି (hwctx->internal.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->internal.cuda_device));
            ଅନ୍ୟଥା ଯଦି (!(hwctx->internal.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = ଖାଲି;
        }

        cuda_free_functions(&hwctx->internal.cuda_dl);
        memset(&hwctx->internal, 0, ଆକାର(hwctx->internal));
        hwctx->p.internal = ଖାଲି;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    hwctx->p.internal = &hwctx->internal;

    ଯଦି (!hwctx->internal.cuda_dl) {
        ret = cuda_load_functions(&hwctx->internal.cuda_dl, ctx);
        ଯଦି (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            ଯାଅ error;
        }
    }

    ଫେରନ୍ତୁ 0;

error:
    cuda_device_uninit(ctx);
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cuda_context_init(AVHWDeviceContext *device_ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, dev_active = 0;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା dev_flags = 0;

    ଅଚଳ unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->internal->cuda_dl;

    hwctx->internal->flags = flags;

    ଯଦି (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->internal->cuda_device,
                       &dev_flags, &dev_active));
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;

        ଯଦି (dev_active && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            ଫେରନ୍ତୁ AVERROR(ENOTSUP);
        } ଅନ୍ୟଥା ଯଦି (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cuDevicePrimaryCtxSetFlags(hwctx->internal->cuda_device,
                           desired_flags));
            ଯଦି (ret < 0)
                ଫେରନ୍ତୁ ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->internal->cuda_device));
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
    } ଅନ୍ୟଥା ଯଦି (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } ଅନ୍ୟଥା {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->internal->cuda_device));
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;

        CHECK_CU(cu->cu_Ctx_କାଢ଼_Current(&dummy));
    }

    hwctx->internal->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->stream = ଖାଲି;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *flags)
{
    AVDictionaryEntry *primary_ctx_opt = av_dict_get(opts, "primary_ctx", ଖାଲି, 0);
    AVDictionaryEntry *current_ctx_opt = av_dict_get(opts, "current_ctx", ଖାଲି, 0);

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା use_primary_ctx = 0, use_current_ctx = 0;
    ଯଦି (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->ମୂଲ୍ୟ, ଖାଲି, 10);

    ଯଦି (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->ମୂଲ୍ୟ, ଖାଲି, 10);

    ଯଦି (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ଯଦି (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } ଅନ୍ୟଥା ଯଦି (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    ଯଦି (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } ଅନ୍ୟଥା ଯଦି (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cuda_device_create(AVHWDeviceContext *device_ctx,
                              ଅଚଳ ଅକ୍ଷର *device,
                              AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    ଯଦି (ret < 0)
        ଯାଅ error;

    ଯଦି (device)
        device_idx = strtol(device, ଖାଲି, 0);

    ret = cuda_device_init(device_ctx);
    ଯଦି (ret < 0)
        ଯାଅ error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    ଯଦି (ret < 0)
        ଯାଅ error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->internal->cuda_device, device_idx));
    ଯଦି (ret < 0)
        ଯାଅ error;

    ret = cuda_context_init(device_ctx, flags);
    ଯଦି (ret < 0)
        ଯାଅ error;

    ଫେରନ୍ତୁ 0;

error:
    cuda_device_uninit(device_ctx);
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ଅଚଳ ଅକ୍ଷର *src_uuid = ଖାଲି;
#ଯଦି CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#endif
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, i, device_ଗଣନା;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    ଯଦି (ret < 0)
        ଯାଅ error;

#ଯଦି CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#endif

    ବାଛ (src_ctx->type) {
#ଯଦି CONFIG_VULKAN
#define TYPE PFN_vkGetPhysicalDeviceProperties2
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .pNext = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        ଭାଙ୍ଗ;
    }
#undef TYPE
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ret = AVERROR(ENOSYS);
        ଯାଅ error;
    }

    ଯଦି (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        ଯାଅ error;
    }

    ret = cuda_device_init(device_ctx);
    ଯଦି (ret < 0)
        ଯାଅ error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    ଯଦି (ret < 0)
        ଯାଅ error;

    ret = CHECK_CU(cu->cu_Device_Get_ଗଣନା(&device_ଗଣନା));
    ଯଦି (ret < 0)
        ଯାଅ error;

    hwctx->internal->cuda_device = -1;
    ପାଇଁ (i = 0; i < device_ଗଣନା; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        ଯଦି (ret < 0)
            ଯାଅ error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        ଯଦି (ret < 0)
            ଯାଅ error;

        ଯଦି (memcmp(src_uuid, uuid.bytes, ଆକାର (uuid.bytes)) == 0) {
            hwctx->internal->cuda_device = dev;
            ଭାଙ୍ଗ;
        }
    }

    ଯଦି (hwctx->internal->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        ଯାଅ error;
    }

    ret = cuda_context_init(device_ctx, flags);
    ଯଦି (ret < 0)
        ଯାଅ error;

    ଫେରନ୍ତୁ 0;

error:
    cuda_device_uninit(device_ctx);
    ଫେରନ୍ତୁ ret;
}

ଅଚଳ HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_size    = ଆକାର(CUDADeviceContext),
    .frames_hwctx_size    = ଆକାର(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .frames_get_constraints = cuda_frames_get_constraints,
    .frames_init          = cuda_frames_init,
    .frames_uninit        = cuda_frames_uninit,
    .frames_get_buffer    = cuda_get_buffer,
    .transfer_get_formats = cuda_transfer_get_formats,
#ଯଦି HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_buffer_alloc = cuda_transfer_buffer_alloc,
#endif
    .transfer_data_to     = cuda_transfer_data,
    .transfer_data_from   = cuda_transfer_data,

    .pix_fmts             = (ଅଚଳ ଗଣନା AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#ଯଦି HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#endif
                                                          AV_PIX_FMT_NONE },
};
