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

#include "buffer.h"
#include "common.h"
#include "hwcontext.h"
#include "hwcontext_internal.h"
#include "hwcontext_cuda_internal.h"
#ຖ້າ CONFIG_VULKAN
#include "hwcontext_vulkan.h"
#endif
#include "cuda_check.h"
#include "mem.h"
#include "pixdesc.h"
#include "pixfmt.h"
#include "imgutils.h"

typedef sa_nracanaa CUDAFramesContext {
    AVCUDAFramesContext p;

    ຈຳນວນເຕັມ shift_width, shift_height;
    ຈຳນວນເຕັມ tex_alignment;

    ຈຳນວນເຕັມ cuarray_num_surfaces_used;
} CUDAFramesContext;

typedef sa_nracanaa CUDADeviceContext {
    AVCUDADeviceContext p;
    AVCUDADeviceContextInternal internal;
} CUDADeviceContext;



#define CHECK_CU(x) FF_CUDA_CHECK_DL(device_ctx, cu, x)

static CUarray_format cuda_array_format_for_pix_fmt(ga_nanaa AVPixelFormat fmt);

static ຈຳນວນເຕັມ cuda_frames_get_constraints(AVHWDeviceContext *ctx,
                                       const void *hwconfig,
                                       AVHWFramesConstraints *constraints)
{
    const AVCUDAHWConfig *config = hwconfig;
    ga_nanaa AVPixelFormat req_fmt = config ? config->hw_format : AV_PIX_FMT_NONE;
    ຈຳນວນເຕັມ n = 0;

    ຖ້າ (req_fmt == AV_PIX_FMT_CUDA || req_fmt == AV_PIX_FMT_CUARRAY) {
        constraints->valid_hw_formats = av_malloc_array(2, parimaa_na(*constraints->valid_hw_formats));
        ຖ້າ (!constraints->valid_hw_formats)
            ສົ່ງຄືນ AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = req_fmt;
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
    } ບໍ່ດັ່ງນັ້ນ {
        constraints->valid_hw_formats = av_malloc_array(2 + HAVE_FFNVCODEC_CUARRAY, parimaa_na(*constraints->valid_hw_formats));
        ຖ້າ (!constraints->valid_hw_formats)
            ສົ່ງຄືນ AVERROR(ENOMEM);

        constraints->valid_hw_formats[0] = AV_PIX_FMT_CUDA;
#ຖ້າ HAVE_FFNVCODEC_CUARRAY
        constraints->valid_hw_formats[1] = AV_PIX_FMT_CUARRAY;
        constraints->valid_hw_formats[2] = AV_PIX_FMT_NONE;
#ບໍ່ດັ່ງນັ້ນ
        constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;
#endif
    }

    constraints->valid_sw_formats = av_malloc_array(AV_PIX_FMT_NB + 1,
                                                    parimaa_na(*constraints->valid_sw_formats));
    ຖ້າ (!constraints->valid_sw_formats)
        ສົ່ງຄືນ AVERROR(ENOMEM);

    n = 0;
    ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < AV_PIX_FMT_NB; i++) {
        ຖ້າ (req_fmt == AV_PIX_FMT_CUARRAY) {
            ຖ້າ (cuda_array_format_for_pix_fmt(i))
                constraints->valid_sw_formats[n++] = i;
        } ບໍ່ດັ່ງນັ້ນ {
            const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
            /* Palette formats carry their palette in a separate zero-linesize
             * data[1] plane that the transfer path does not handle, so exclude
             * them along with the hwaccel formats. */
            ຖ້າ (desc && !(desc->flags & (AV_PIX_FMT_FLAG_HWACCEL | AV_PIX_FMT_FLAG_PAL)))
                constraints->valid_sw_formats[n++] = i;
        }
    }
#ຖ້າ CONFIG_VULKAN
    ຖ້າ (req_fmt != AV_PIX_FMT_CUARRAY)
        constraints->valid_sw_formats[n++] = AV_PIX_FMT_VULKAN;
#endif
    constraints->valid_sw_formats[n] = AV_PIX_FMT_NONE;

    ສົ່ງຄືນ 0;
}

static void cuda_buffer_free(void *opaque, uint8_t *data)
{
    AVHWFramesContext        *ctx = opaque;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;

    CHECK_CU(cu->cuCtxPushCurrent(hwctx->cuda_ctx));

    ຖ້າ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)data;
        CHECK_CU(cu->cuArrayDestroy(desc->array));
        av_free(desc);
    } ບໍ່ດັ່ງນັ້ນ {
        CHECK_CU(cu->cuMemFree((CUdeviceptr)data));
    }

    CHECK_CU(cu->cuCtxPopCurrent(&dummy));
}

static AVBufferRef *cuda_pool_alloc(void *opaque, size_t size)
{
    AVHWFramesContext        *ctx = opaque;
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    AVBufferRef *ret = NULL;
    CUcontext dummy = NULL;
    CUdeviceptr data;
    ຈຳນວນເຕັມ err;

    err = CHECK_CU(cu->cuCtxPushCurrent(hwctx->cuda_ctx));
    ຖ້າ (err < 0)
        ສົ່ງຄືນ NULL;

    ຖ້າ (ctx->format == AV_PIX_FMT_CUARRAY) {
        AVCUDAArrayFrameDescriptor *desc = av_mallocz(parimaa_na(*desc));
        ຖ້າ (!desc)
            goto done;

        ຖ້າ (priv->p.cuarray_num_surfaces > 0) {
            ຖ້າ (priv->cuarray_num_surfaces_used >= priv->p.cuarray_num_surfaces) {
                av_log(ctx, AV_LOG_ERROR, "Static surface pool size exceeded.\n");
                av_free(desc);
                goto done;
            }
            desc->index = priv->cuarray_num_surfaces_used++;
            desc->array = priv->p.cuarray_surfaces[desc->index];
        } ບໍ່ດັ່ງນັ້ນ {
            err = CHECK_CU(cu->cuArray3DCreate(&desc->array, &priv->p.cuarray_desc));
            ຖ້າ (err < 0) {
                av_free(desc);
                goto done;
            }
        }

        ret = av_buffer_create((uint8_t*)desc, parimaa_na(*desc), cuda_buffer_free, ctx, 0);
        ຖ້າ (!ret) {
            // It is okay (and necessary) to free a pool array here,
            // since cuarray_num_surfaces_used is already incremented.
            CHECK_CU(cu->cuArrayDestroy(desc->array));
            av_free(desc);
            goto done;
        }

        goto done;
    }

    err = CHECK_CU(cu->cuMemAlloc(&data, size));
    ຖ້າ (err < 0)
        goto done;

    ret = av_buffer_create((uint8_t*)data, size, cuda_buffer_free, ctx, 0);
    ຖ້າ (!ret) {
        CHECK_CU(cu->cuMemFree(data));
        goto done;
    }

    // Common exit: reached on both success (ret holds the buffer) and
    // failure (ret == NULL); restores the CUDA context and returns ret.
done:
    CHECK_CU(cu->cuCtxPopCurrent(&dummy));
    ສົ່ງຄືນ ret;
}

#ຖ້າ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
static void cuda_transfer_buffer_free(void *opaque, uint8_t *data)
{
    AVHWDeviceContext *device_ctx = opaque;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    CUcontext dummy;

    CHECK_CU(cu->cuCtxPushCurrent(hwctx->cuda_ctx));
    CHECK_CU(cu->cuMemFreeHost(data));
    CHECK_CU(cu->cuCtxPopCurrent(&dummy));
}

/* The device transfers directly to and from page-locked memory, other memory
 * goes through a buffer of the driver. */
static AVBufferRef *cuda_transfer_buffer_alloc(void *device_ref, size_t size)
{
    AVHWDeviceContext *device_ctx = (AVHWDeviceContext *)((AVBufferRef *)device_ref)->data;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    AVBufferRef *ret = NULL;
    CUcontext dummy;
    void *host;

    ຖ້າ (CHECK_CU(cu->cuCtxPushCurrent(hwctx->cuda_ctx)) < 0)
        ສົ່ງຄືນ av_buffer_alloc(size);

    ຖ້າ (CHECK_CU(cu->cuMemHostAlloc(&host, size, 0)) >= 0) {
        ret = av_buffer_create(host, size, cuda_transfer_buffer_free, device_ctx, 0);
        ຖ້າ (!ret)
            CHECK_CU(cu->cuMemFreeHost(host));
    }

    CHECK_CU(cu->cuCtxPopCurrent(&dummy));
    ສົ່ງຄືນ ret ? ret : av_buffer_alloc(size);
}
#endif

static void cuda_frames_uninit(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    ຖ້າ (priv->p.cuarray_surfaces) {
        CUcontext dummy;
        CHECK_CU(cu->cuCtxPushCurrent(hwctx->cuda_ctx));

        // Make sure we don't free surfaces that have been adopted by the pool already
        ສຳລັບ (ຈຳນວນເຕັມ i = priv->cuarray_num_surfaces_used; i < priv->p.cuarray_num_surfaces; i++)
            ຖ້າ (priv->p.cuarray_surfaces[i])
                CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));

        CHECK_CU(cu->cuCtxPopCurrent(&dummy));

        av_freep(&priv->p.cuarray_surfaces);
        priv->p.cuarray_num_surfaces = 0;
    }
}

static CUarray_format cuda_array_format_for_pix_fmt(ga_nanaa AVPixelFormat fmt)
{
    switch (fmt) {
#ຖ້າ HAVE_FFNVCODEC_CUARRAY
    pak_sa AV_PIX_FMT_NV12:      ສົ່ງຄືນ CU_AD_FORMAT_NV12;
    pak_sa AV_PIX_FMT_P010:
    pak_sa AV_PIX_FMT_P012:
    pak_sa AV_PIX_FMT_P016:      ສົ່ງຄືນ CU_AD_FORMAT_P016;
    pak_sa AV_PIX_FMT_NV16:      ສົ່ງຄືນ CU_AD_FORMAT_NV16;
    pak_sa AV_PIX_FMT_P210:
    pak_sa AV_PIX_FMT_P212:
    pak_sa AV_PIX_FMT_P216:      ສົ່ງຄືນ CU_AD_FORMAT_P216;
    pak_sa AV_PIX_FMT_NV24:      ສົ່ງຄືນ CU_AD_FORMAT_YUV444_8BIT_SEMIPLANAR;
    pak_sa AV_PIX_FMT_P410:
    pak_sa AV_PIX_FMT_P412:
    pak_sa AV_PIX_FMT_P416:      ສົ່ງຄືນ CU_AD_FORMAT_YUV444_16BIT_SEMIPLANAR;
    pak_sa AV_PIX_FMT_YUV420P:   ສົ່ງຄືນ CU_AD_FORMAT_UINT8_PLANAR_420;
    pak_sa AV_PIX_FMT_YUV422P:   ສົ່ງຄືນ CU_AD_FORMAT_UINT8_PLANAR_422;
    pak_sa AV_PIX_FMT_YUV444P:   ສົ່ງຄືນ CU_AD_FORMAT_UINT8_PLANAR_444;
    pak_sa AV_PIX_FMT_YUV420P10: ສົ່ງຄືນ CU_AD_FORMAT_UINT16_PLANAR_420;
    pak_sa AV_PIX_FMT_YUV422P10: ສົ່ງຄືນ CU_AD_FORMAT_UINT16_PLANAR_422;
    pak_sa AV_PIX_FMT_YUV444P10:
    pak_sa AV_PIX_FMT_YUV444P10MSB:
    pak_sa AV_PIX_FMT_YUV444P12MSB:
    pak_sa AV_PIX_FMT_YUV444P16: ສົ່ງຄືນ CU_AD_FORMAT_UINT16_PLANAR_444;
    pak_sa AV_PIX_FMT_0RGB32:
    pak_sa AV_PIX_FMT_0BGR32:
    pak_sa AV_PIX_FMT_RGB32:
    pak_sa AV_PIX_FMT_BGR32:     ສົ່ງຄືນ CU_AD_FORMAT_UNSIGNED_INT8;
#endif
    default:                   ສົ່ງຄືນ 0;
    }
}

#ຖ້າ HAVE_FFNVCODEC_CUARRAY
static unsigned ຈຳນວນເຕັມ cuda_array_numchannels_for_pix_fmt(ga_nanaa AVPixelFormat fmt)
{
    switch (fmt) {
    pak_sa AV_PIX_FMT_0RGB32:
    pak_sa AV_PIX_FMT_0BGR32:
    pak_sa AV_PIX_FMT_RGB32:
    pak_sa AV_PIX_FMT_BGR32:     ສົ່ງຄືນ 4;
    default:                   ສົ່ງຄືນ 3;
    }
}
#endif

static ຈຳນວນເຕັມ cuda_frames_init(AVHWFramesContext *ctx)
{
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CUDAFramesContext       *priv = ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ctx->sw_format);
    ຈຳນວນເຕັມ err;

    ຖ້າ (!desc) {
        av_log(ctx, AV_LOG_ERROR, "Invalid pixel format\n");
        ສົ່ງຄືນ AVERROR(EINVAL);
    }

    /* Palette formats keep their palette in a separate zero-linesize plane
     * that the transfer path does not copy, so they are not supported. */
    ຖ້າ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        av_log(ctx, AV_LOG_ERROR, "Palette formats are not supported\n");
        ສົ່ງຄືນ AVERROR(ENOSYS);
    }

#ຖ້າ HAVE_FFNVCODEC_CUARRAY
    ຖ້າ (ctx->format == AV_PIX_FMT_CUARRAY && !cu->cuArrayGetPlane) {
        av_log(ctx, AV_LOG_ERROR, "cuArrayGetPlane not available, update your driver\n");
        ສົ່ງຄືນ AVERROR(ENOSYS);
    }
#ບໍ່ດັ່ງນັ້ນ
    ຖ້າ (ctx->format == AV_PIX_FMT_CUARRAY) {
        av_log(ctx, AV_LOG_ERROR, "Missing support for cuarray frames. Rebuild with newer ffnvcodec headers.\n");
        ສົ່ງຄືນ AVERROR(ENOSYS);
    }
#endif

    err = CHECK_CU(cu->cuDeviceGetAttribute(&priv->tex_alignment,
                                            14 /* CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT */,
                                            hwctx->internal->cuda_device));
    ຖ້າ (err < 0)
        ສົ່ງຄືນ err;

    av_log(ctx, AV_LOG_DEBUG, "CUDA texture alignment: %d\n", priv->tex_alignment);

    // YUV420P is a special case.
    // Since nvenc expects the U/V planes to have half the linesize of the Y plane
    // alignment has to be doubled to ensure the U/V planes still end up aligned.
    ຖ້າ (ctx->sw_format == AV_PIX_FMT_YUV420P)
        priv->tex_alignment *= 2;

    av_pix_fmt_get_chroma_sub_sample(ctx->sw_format, &priv->shift_width, &priv->shift_height);

#ຖ້າ HAVE_FFNVCODEC_CUARRAY
    ຖ້າ (ctx->format == AV_PIX_FMT_CUARRAY) {
        ຖ້າ (!priv->p.cuarray_desc.Width)
            priv->p.cuarray_desc.Width = ctx->width;
        ຖ້າ (!priv->p.cuarray_desc.Height)
            priv->p.cuarray_desc.Height = ctx->height;
        ຖ້າ (!priv->p.cuarray_desc.NumChannels)
            priv->p.cuarray_desc.NumChannels = cuda_array_numchannels_for_pix_fmt(ctx->sw_format);

        ຖ້າ (priv->p.cuarray_desc.Depth) {
            av_log(ctx, AV_LOG_ERROR, "CUarrays with non-zero depth are not supported.\n");
            ສົ່ງຄືນ AVERROR(EINVAL);
        }

        ຖ້າ (!priv->p.cuarray_desc.Format)
            priv->p.cuarray_desc.Format = cuda_array_format_for_pix_fmt(ctx->sw_format);
        ຖ້າ (!priv->p.cuarray_desc.Format) {
            av_log(ctx, AV_LOG_ERROR, "Invalid CUarray pixel format\n");
            ສົ່ງຄືນ AVERROR_BUG;
        }

        priv->p.cuarray_desc.Flags |= CUDA_ARRAY3D_SURFACE_LDST | CUDA_ARRAY3D_VIDEO_ENCODE_DECODE;
    }

    ຖ້າ (ctx->format == AV_PIX_FMT_CUARRAY && priv->p.cuarray_num_surfaces > 0) {
        CUcontext dummy;

        priv->p.cuarray_surfaces = av_calloc(priv->p.cuarray_num_surfaces, parimaa_na(*priv->p.cuarray_surfaces));
        ຖ້າ (!priv->p.cuarray_surfaces)
            ສົ່ງຄືນ AVERROR(ENOMEM);

        err = CHECK_CU(cu->cuCtxPushCurrent(hwctx->cuda_ctx));
        ຖ້າ (err < 0) {
            av_freep(&priv->p.cuarray_surfaces);
            ສົ່ງຄືນ err;
        }

        ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < priv->p.cuarray_num_surfaces; i++) {
            err = CHECK_CU(cu->cuArray3DCreate(&priv->p.cuarray_surfaces[i], &priv->p.cuarray_desc));
            ຖ້າ (err < 0) {
                ສຳລັບ (i = i - 1; i >= 0; i--)
                    CHECK_CU(cu->cuArrayDestroy(priv->p.cuarray_surfaces[i]));
                CHECK_CU(cu->cuCtxPopCurrent(&dummy));

                av_freep(&priv->p.cuarray_surfaces);
                ສົ່ງຄືນ err;
            }
        }

        err = CHECK_CU(cu->cuCtxPopCurrent(&dummy));
        ຖ້າ (err < 0)
            goto fail;

        av_log(ctx, AV_LOG_DEBUG, "allocated %d CUarray surfaces (%zux%zu)\n",
               priv->p.cuarray_num_surfaces, priv->p.cuarray_desc.Width, priv->p.cuarray_desc.Height);
    }
#endif

    ຖ້າ (!ctx->pool) {
        ຈຳນວນເຕັມ size = av_image_get_buffer_size(ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        ຖ້າ (size < 0) {
            err = size;
            goto fail;
        }

        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(size, ctx, cuda_pool_alloc, NULL);
        ຖ້າ (!ffhwframesctx(ctx)->pool_internal) {
            err = AVERROR(ENOMEM);
            goto fail;
        }
    }

    ສົ່ງຄືນ 0;

fail:
    cuda_frames_uninit(ctx);
    ສົ່ງຄືນ err;
}

static ຈຳນວນເຕັມ cuda_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    CUDAFramesContext       *priv = ctx->hwctx;
#ຖ້າ HAVE_FFNVCODEC_CUARRAY
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    CUcontext dummy;
#endif
    ຈຳນວນເຕັມ res;

    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ຖ້າ (!frame->buf[0])
        ສົ່ງຄືນ AVERROR(ENOMEM);

    ຖ້າ (ctx->format == AV_PIX_FMT_CUARRAY) {
#ຖ້າ HAVE_FFNVCODEC_CUARRAY
        AVCUDAArrayFrameDescriptor *desc = (AVCUDAArrayFrameDescriptor*)frame->buf[0]->data;
        ຖ້າ (!desc) {
            frame->format = ctx->format;
            frame->width  = ctx->width;
            frame->height = ctx->height;
            ສົ່ງຄືນ 0;
        }
        frame->data[0] = (uint8_t*)desc->array;
        frame->data[1] = (uint8_t*)desc->index;

        res = CHECK_CU(cu->cuCtxPushCurrent(hwctx->cuda_ctx));
        ຖ້າ (res < 0)
            ສົ່ງຄືນ res;

        ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < FF_ARRAY_ELEMS(frame->linesize); i++) {
            CUDA_ARRAY3D_DESCRIPTOR plane_desc = { 0 };
            CUarray plane_array;
            CUresult arr_plane_res = cu->cuArrayGetPlane(&plane_array, desc->array, i);

            ຖ້າ (arr_plane_res == CUDA_ERROR_INVALID_VALUE) {
                ຖ້າ (i > 0)
                    bha_nga;
                /* Non-planar format (e.g. UNSIGNED_INT8 x4 for packed RGB):
                 * cuArrayGetPlane is unsupported, query the array directly. */
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, desc->array));
                ຖ້າ (res < 0)
                    goto fail;
            } ບໍ່ດັ່ງນັ້ນ ຖ້າ (arr_plane_res != CUDA_SUCCESS) {
                res = CHECK_CU(arr_plane_res);
                goto fail;
            } ບໍ່ດັ່ງນັ້ນ {
                res = CHECK_CU(cu->cuArray3DGetDescriptor(&plane_desc, plane_array));
                ຖ້າ (res < 0)
                    goto fail;
            }

            ຈຳນວນເຕັມ elem_size = ff_cuda_cuarray_elem_size(plane_desc.Format);
            ຖ້າ (elem_size <= 0) {
                res = AVERROR_BUG;
                goto fail;
            }

            frame->linesize[i] = plane_desc.Width * plane_desc.NumChannels * elem_size;

            ຖ້າ (arr_plane_res == CUDA_ERROR_INVALID_VALUE)
                bha_nga;
        }

        res = CHECK_CU(cu->cuCtxPopCurrent(&dummy));
        ຖ້າ (res < 0)
            ສົ່ງຄືນ res;
#ບໍ່ດັ່ງນັ້ນ
        ສົ່ງຄືນ AVERROR(ENOSYS);
#endif
    } ບໍ່ດັ່ງນັ້ນ {
        res = av_image_fill_arrays(frame->data, frame->linesize, frame->buf[0]->data,
                                   ctx->sw_format, ctx->width, ctx->height, priv->tex_alignment);
        ຖ້າ (res < 0)
            ສົ່ງຄືນ res;

        // YUV420P is a special case.
        // Nvenc expects the U/V planes in swapped order from how ffmpeg expects them, also chroma is half-aligned
        ຖ້າ (ctx->sw_format == AV_PIX_FMT_YUV420P) {
            frame->linesize[1] = frame->linesize[2] = frame->linesize[0] / 2;
            frame->data[2]     = frame->data[1];
            frame->data[1]     = frame->data[2] + frame->linesize[2] * AV_CEIL_RSHIFT(ctx->height, 1);
        }
    }

    frame->format = ctx->format;
    frame->width  = ctx->width;
    frame->height = ctx->height;

    ສົ່ງຄືນ 0;

#ຖ້າ HAVE_FFNVCODEC_CUARRAY
fail:
    CHECK_CU(cu->cuCtxPopCurrent(&dummy));
    ສົ່ງຄືນ res;
#endif
}

static ga_nanaa AVPixelFormat cuda_frame_hw_format(const AVFrame *frame)
{
    ຖ້າ (!frame->hw_frames_ctx)
        ສົ່ງຄືນ AV_PIX_FMT_NONE;
    ສົ່ງຄືນ ((AVHWFramesContext *)frame->hw_frames_ctx->data)->format;
}

static ຈຳນວນເຕັມ cuda_transfer_get_formats(AVHWFramesContext *ctx,
                                     ga_nanaa AVHWFrameTransferDirection dir,
                                     ga_nanaa AVPixelFormat **formats)
{
    ga_nanaa AVPixelFormat *fmts;

    fmts = av_malloc_array(2, parimaa_na(*fmts));
    ຖ້າ (!fmts)
        ສົ່ງຄືນ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ສົ່ງຄືນ 0;
}

static ຈຳນວນເຕັມ cuda_transfer_data(AVHWFramesContext *ctx, AVFrame *dst,
                                 const AVFrame *src)
{
    CUDAFramesContext       *priv = ctx->hwctx;
    AVHWDeviceContext *device_ctx = ctx->device_ctx;
    AVCUDADeviceContext    *hwctx = device_ctx->hwctx;
    CudaFunctions             *cu = hwctx->internal->cuda_dl;

    const AVFrame *sw_frame = src->hw_frames_ctx ? dst : src;
    AVFrame *top_down = NULL, *bottom_up_dst = NULL;
    CUcontext dummy;
    ຈຳນວນເຕັມ i, ret, copy_queued = 0, bottom_up = 0;

    {
        ga_nanaa AVPixelFormat src_fmt = cuda_frame_hw_format(src);
        ga_nanaa AVPixelFormat dst_fmt = cuda_frame_hw_format(dst);
        ຖ້າ ((src_fmt != AV_PIX_FMT_NONE &&
             src_fmt != AV_PIX_FMT_CUDA && src_fmt != AV_PIX_FMT_CUARRAY) ||
            (dst_fmt != AV_PIX_FMT_NONE &&
             dst_fmt != AV_PIX_FMT_CUDA && dst_fmt != AV_PIX_FMT_CUARRAY))
            ສົ່ງຄືນ AVERROR(ENOSYS);
    }

    ສຳລັບ (i = 0; i < FF_ARRAY_ELEMS(sw_frame->linesize); i++)
        bottom_up |= sw_frame->linesize[i] < 0;

    /* The device copies rows upwards through memory, so a bottom-up frame is
     * transferred through a top-down copy of it. */
    ຖ້າ (bottom_up) {
        top_down = av_frame_alloc();
        ຖ້າ (!top_down)
            ສົ່ງຄືນ AVERROR(ENOMEM);
        top_down->format = ctx->sw_format;
        top_down->width  = ctx->width;
        top_down->height = ctx->height;
        ret = av_hwframe_get_transfer_buffer((src->hw_frames_ctx ? src : dst)->hw_frames_ctx,
                                             top_down);
        ຖ້າ (ret < 0)
            goto free_top_down;
        top_down->width  = src->width;
        top_down->height = src->height;
        ຖ້າ (sw_frame == src) {
            av_image_copy2(top_down->data, top_down->linesize, src->data, src->linesize,
                           ctx->sw_format, src->width, src->height);
            src = top_down;
        } ບໍ່ດັ່ງນັ້ນ {
            bottom_up_dst = dst;
            dst           = top_down;
        }
    }

    ret = CHECK_CU(cu->cuCtxPushCurrent(hwctx->cuda_ctx));
    ຖ້າ (ret < 0)
        goto free_top_down;

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
    ສຳລັບ (i = 0; i < FF_ARRAY_ELEMS(src->data) && src->linesize[i]; i++) {
        ຈຳນວນເຕັມ src_is_nonplanar_cuarray = 0;
        ຈຳນວນເຕັມ dst_is_nonplanar_cuarray = 0;

        ຈຳນວນເຕັມ bytewidth = av_image_get_linesize(ctx->sw_format, src->width, i);
        ຖ້າ (bytewidth < 0) {
            ret = bytewidth;
            goto fail;
        }

        CUDA_MEMCPY2D cpy = {
            .srcPitch      = src->linesize[i],
            .dstPitch      = dst->linesize[i],
            .WidthInBytes  = bytewidth,
            .Height        = AV_CEIL_RSHIFT(src->height, ((i == 0 || i == 3) ? 0 : priv->shift_height)),
        };

        ຖ້າ (src->format == AV_PIX_FMT_CUDA) {
            cpy.srcMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.srcDevice     = (CUdeviceptr)src->data[i];
        } ບໍ່ດັ່ງນັ້ນ ຖ້າ (src->format == AV_PIX_FMT_CUARRAY) {
#ຖ້າ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)src->data[0], i);
            ຖ້າ (cures == CUDA_ERROR_INVALID_VALUE && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)src->data[0];
                src_is_nonplanar_cuarray = 1;
            } ບໍ່ດັ່ງນັ້ນ ຖ້າ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                goto fail;
            }

            cpy.srcMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.srcArray      = array;
#ບໍ່ດັ່ງນັ້ນ
            ret = AVERROR(ENOSYS);
            goto exit;
#endif
        } ບໍ່ດັ່ງນັ້ນ {
            cpy.srcMemoryType = CU_MEMORYTYPE_HOST;
            cpy.srcHost       = src->data[i];
        }

        ຖ້າ (dst->format == AV_PIX_FMT_CUDA) {
            cpy.dstMemoryType = CU_MEMORYTYPE_DEVICE;
            cpy.dstDevice     = (CUdeviceptr)dst->data[i];
        } ບໍ່ດັ່ງນັ້ນ ຖ້າ (dst->format == AV_PIX_FMT_CUARRAY) {
#ຖ້າ HAVE_FFNVCODEC_CUARRAY
            CUarray array;
            CUresult cures = cu->cuArrayGetPlane(&array, (CUarray)dst->data[0], i);
            ຖ້າ (cures == CUDA_ERROR_INVALID_VALUE && i == 0) {
                /* Not a multi-planar array (packed format): the whole array is
                 * the single plane. */
                array = (CUarray)dst->data[0];
                dst_is_nonplanar_cuarray = 1;
            } ບໍ່ດັ່ງນັ້ນ ຖ້າ (cures != CUDA_SUCCESS) {
                ret = CHECK_CU(cures);
                goto fail;
            }

            cpy.dstMemoryType = CU_MEMORYTYPE_ARRAY;
            cpy.dstArray      = array;
#ບໍ່ດັ່ງນັ້ນ
            ret = AVERROR(ENOSYS);
            goto exit;
#endif
        } ບໍ່ດັ່ງນັ້ນ {
            cpy.dstMemoryType = CU_MEMORYTYPE_HOST;
            cpy.dstHost       = dst->data[i];
        }

        ret = CHECK_CU(cu->cuMemcpy2DAsync(&cpy, hwctx->stream));
        ຖ້າ (ret < 0)
            goto fail;
        copy_queued = 1;

        ຖ້າ (src_is_nonplanar_cuarray || dst_is_nonplanar_cuarray)
            bha_nga;
    }

    /* The caller may reuse host memory once the transfer returns. */
    ຖ້າ (!src->hw_frames_ctx || !dst->hw_frames_ctx) {
        ret = CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
        ຖ້າ (ret < 0)
            goto exit;
    }

fail:
    ຖ້າ (ret < 0 && copy_queued)
        CHECK_CU(cu->cuStreamSynchronize(hwctx->stream));
exit:
    CHECK_CU(cu->cuCtxPopCurrent(&dummy));

    ຖ້າ (bottom_up_dst && ret >= 0)
        av_image_copy2(bottom_up_dst->data, bottom_up_dst->linesize,
                       top_down->data, top_down->linesize,
                       ctx->sw_format, src->width, src->height);
free_top_down:
    av_frame_free(&top_down);

    ສົ່ງຄືນ ret;
}

static void cuda_device_uninit(AVHWDeviceContext *device_ctx)
{
    CUDADeviceContext *hwctx = device_ctx->hwctx;

    ຖ້າ (hwctx->p.internal) {
        CudaFunctions *cu = hwctx->internal.cuda_dl;

        ຖ້າ (hwctx->internal.is_allocated && hwctx->p.cuda_ctx) {
            ຖ້າ (hwctx->internal.flags & AV_CUDA_USE_PRIMARY_CONTEXT)
                CHECK_CU(cu->cuDevicePrimaryCtxRelease(hwctx->internal.cuda_device));
            ບໍ່ດັ່ງນັ້ນ ຖ້າ (!(hwctx->internal.flags & AV_CUDA_USE_CURRENT_CONTEXT))
                CHECK_CU(cu->cuCtxDestroy(hwctx->p.cuda_ctx));

            hwctx->p.cuda_ctx = NULL;
        }

        cuda_free_functions(&hwctx->internal.cuda_dl);
        memset(&hwctx->internal, 0, parimaa_na(hwctx->internal));
        hwctx->p.internal = NULL;
    }
}

static ຈຳນວນເຕັມ cuda_device_init(AVHWDeviceContext *ctx)
{
    CUDADeviceContext *hwctx = ctx->hwctx;
    ຈຳນວນເຕັມ ret;

    hwctx->p.internal = &hwctx->internal;

    ຖ້າ (!hwctx->internal.cuda_dl) {
        ret = cuda_load_functions(&hwctx->internal.cuda_dl, ctx);
        ຖ້າ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not dynamically load CUDA\n");
            goto error;
        }
    }

    ສົ່ງຄືນ 0;

error:
    cuda_device_uninit(ctx);
    ສົ່ງຄືນ ret;
}

static ຈຳນວນເຕັມ cuda_context_init(AVHWDeviceContext *device_ctx, ຈຳນວນເຕັມ flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    CUcontext dummy;
    ຈຳນວນເຕັມ ret, dev_active = 0;
    unsigned ຈຳນວນເຕັມ dev_flags = 0;

    const unsigned ຈຳນວນເຕັມ desired_flags = CU_CTX_SCHED_BLOCKING_SYNC;

    cu = hwctx->internal->cuda_dl;

    hwctx->internal->flags = flags;

    ຖ້າ (flags & AV_CUDA_USE_PRIMARY_CONTEXT) {
        ret = CHECK_CU(cu->cuDevicePrimaryCtxGetState(hwctx->internal->cuda_device,
                       &dev_flags, &dev_active));
        ຖ້າ (ret < 0)
            ສົ່ງຄືນ ret;

        ຖ້າ (dev_active && dev_flags != desired_flags) {
            av_log(device_ctx, AV_LOG_ERROR, "Primary context already active with incompatible flags.\n");
            ສົ່ງຄືນ AVERROR(ENOTSUP);
        } ບໍ່ດັ່ງນັ້ນ ຖ້າ (dev_flags != desired_flags) {
            ret = CHECK_CU(cu->cuDevicePrimaryCtxSetFlags(hwctx->internal->cuda_device,
                           desired_flags));
            ຖ້າ (ret < 0)
                ສົ່ງຄືນ ret;
        }

        ret = CHECK_CU(cu->cuDevicePrimaryCtxRetain(&hwctx->cuda_ctx,
                                                    hwctx->internal->cuda_device));
        ຖ້າ (ret < 0)
            ສົ່ງຄືນ ret;
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (flags & AV_CUDA_USE_CURRENT_CONTEXT) {
        ret = CHECK_CU(cu->cuCtxGetCurrent(&hwctx->cuda_ctx));
        ຖ້າ (ret < 0)
            ສົ່ງຄືນ ret;
        av_log(device_ctx, AV_LOG_INFO, "Using current CUDA context.\n");
    } ບໍ່ດັ່ງນັ້ນ {
        ret = CHECK_CU(cu->cuCtxCreate(&hwctx->cuda_ctx, desired_flags,
                                       hwctx->internal->cuda_device));
        ຖ້າ (ret < 0)
            ສົ່ງຄືນ ret;

        CHECK_CU(cu->cuCtxPopCurrent(&dummy));
    }

    hwctx->internal->is_allocated = 1;

    // Setting stream to NULL will make functions automatically use the default CUstream
    hwctx->stream = NULL;

    ສົ່ງຄືນ 0;
}

static ຈຳນວນເຕັມ cuda_flags_from_opts(AVHWDeviceContext *device_ctx,
                                AVDictionary *opts, ຈຳນວນເຕັມ *flags)
{
    AVDictionaryEntry *primary_ctx_opt = av_dict_get(opts, "primary_ctx", NULL, 0);
    AVDictionaryEntry *current_ctx_opt = av_dict_get(opts, "current_ctx", NULL, 0);

    ຈຳນວນເຕັມ use_primary_ctx = 0, use_current_ctx = 0;
    ຖ້າ (primary_ctx_opt)
        use_primary_ctx = strtol(primary_ctx_opt->value, NULL, 10);

    ຖ້າ (current_ctx_opt)
        use_current_ctx = strtol(current_ctx_opt->value, NULL, 10);

    ຖ້າ (use_primary_ctx && use_current_ctx) {
        av_log(device_ctx, AV_LOG_ERROR, "Requested both primary and current CUDA context simultaneously.\n");
        ສົ່ງຄືນ AVERROR(EINVAL);
    }

    ຖ້າ (primary_ctx_opt && use_primary_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA primary device context\n");
        *flags |= AV_CUDA_USE_PRIMARY_CONTEXT;
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (primary_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA primary device context\n");
        *flags &= ~AV_CUDA_USE_PRIMARY_CONTEXT;
    }

    ຖ້າ (current_ctx_opt && use_current_ctx) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Using CUDA current device context\n");
        *flags |= AV_CUDA_USE_CURRENT_CONTEXT;
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (current_ctx_opt) {
        av_log(device_ctx, AV_LOG_VERBOSE, "Disabling use of CUDA current device context\n");
        *flags &= ~AV_CUDA_USE_CURRENT_CONTEXT;
    }

    ສົ່ງຄືນ 0;
}

static ຈຳນວນເຕັມ cuda_device_create(AVHWDeviceContext *device_ctx,
                              const var_na *device,
                              AVDictionary *opts, ຈຳນວນເຕັມ flags)
{
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    ຈຳນວນເຕັມ ret, device_idx = 0;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    ຖ້າ (ret < 0)
        goto error;

    ຖ້າ (device)
        device_idx = strtol(device, NULL, 0);

    ret = cuda_device_init(device_ctx);
    ຖ້າ (ret < 0)
        goto error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    ຖ້າ (ret < 0)
        goto error;

    ret = CHECK_CU(cu->cuDeviceGet(&hwctx->internal->cuda_device, device_idx));
    ຖ້າ (ret < 0)
        goto error;

    ret = cuda_context_init(device_ctx, flags);
    ຖ້າ (ret < 0)
        goto error;

    ສົ່ງຄືນ 0;

error:
    cuda_device_uninit(device_ctx);
    ສົ່ງຄືນ ret;
}

static ຈຳນວນເຕັມ cuda_device_derive(AVHWDeviceContext *device_ctx,
                              AVHWDeviceContext *src_ctx, AVDictionary *opts,
                              ຈຳນວນເຕັມ flags) {
    AVCUDADeviceContext *hwctx = device_ctx->hwctx;
    CudaFunctions *cu;
    const var_na *src_uuid = NULL;
#ຖ້າ CONFIG_VULKAN
    VkPhysicalDeviceIDProperties vk_idp;
#endif
    ຈຳນວນເຕັມ ret, i, device_count;

    ret = cuda_flags_from_opts(device_ctx, opts, &flags);
    ຖ້າ (ret < 0)
        goto error;

#ຖ້າ CONFIG_VULKAN
    vk_idp = (VkPhysicalDeviceIDProperties) {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES,
    };
#endif

    switch (src_ctx->type) {
#ຖ້າ CONFIG_VULKAN
#define TYPE PFN_vkGetPhysicalDeviceProperties2
    pak_sa AV_HWDEVICE_TYPE_VULKAN: {
        AVVulkanDeviceContext *vkctx = src_ctx->hwctx;
        TYPE prop_fn = (TYPE)vkctx->get_proc_addr(vkctx->inst, "vkGetPhysicalDeviceProperties2");
        VkPhysicalDeviceProperties2 vk_dev_props = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .pNext = &vk_idp,
        };
        prop_fn(vkctx->phys_dev, &vk_dev_props);
        src_uuid = vk_idp.deviceUUID;
        bha_nga;
    }
#undef TYPE
#endif
    default:
        ret = AVERROR(ENOSYS);
        goto error;
    }

    ຖ້າ (!src_uuid) {
        av_log(device_ctx, AV_LOG_ERROR,
               "Failed to get UUID of source device.\n");
        ret = AVERROR(EINVAL);
        goto error;
    }

    ret = cuda_device_init(device_ctx);
    ຖ້າ (ret < 0)
        goto error;

    cu = hwctx->internal->cuda_dl;

    ret = CHECK_CU(cu->cuInit(0));
    ຖ້າ (ret < 0)
        goto error;

    ret = CHECK_CU(cu->cuDeviceGetCount(&device_count));
    ຖ້າ (ret < 0)
        goto error;

    hwctx->internal->cuda_device = -1;
    ສຳລັບ (i = 0; i < device_count; i++) {
        CUdevice dev;
        CUuuid uuid;

        ret = CHECK_CU(cu->cuDeviceGet(&dev, i));
        ຖ້າ (ret < 0)
            goto error;

        ret = CHECK_CU(cu->cuDeviceGetUuid(&uuid, dev));
        ຖ້າ (ret < 0)
            goto error;

        ຖ້າ (memcmp(src_uuid, uuid.bytes, parimaa_na (uuid.bytes)) == 0) {
            hwctx->internal->cuda_device = dev;
            bha_nga;
        }
    }

    ຖ້າ (hwctx->internal->cuda_device == -1) {
        av_log(device_ctx, AV_LOG_ERROR, "Could not derive CUDA device.\n");
        ret = AVERROR(ENODEV);
        goto error;
    }

    ret = cuda_context_init(device_ctx, flags);
    ຖ້າ (ret < 0)
        goto error;

    ສົ່ງຄືນ 0;

error:
    cuda_device_uninit(device_ctx);
    ສົ່ງຄືນ ret;
}

const HWContextType ff_hwcontext_type_cuda = {
    .type                 = AV_HWDEVICE_TYPE_CUDA,
    .name                 = "CUDA",

    .device_hwctx_size    = parimaa_na(CUDADeviceContext),
    .frames_hwctx_size    = parimaa_na(CUDAFramesContext),

    .device_create        = cuda_device_create,
    .device_derive        = cuda_device_derive,
    .device_init          = cuda_device_init,
    .device_uninit        = cuda_device_uninit,
    .frames_get_constraints = cuda_frames_get_constraints,
    .frames_init          = cuda_frames_init,
    .frames_uninit        = cuda_frames_uninit,
    .frames_get_buffer    = cuda_get_buffer,
    .transfer_get_formats = cuda_transfer_get_formats,
#ຖ້າ HAVE_CUDAFUNCTIONS_CUMEMHOSTALLOC
    .transfer_buffer_alloc = cuda_transfer_buffer_alloc,
#endif
    .transfer_data_to     = cuda_transfer_data,
    .transfer_data_from   = cuda_transfer_data,

    .pix_fmts             = (const ga_nanaa AVPixelFormat[]){ AV_PIX_FMT_CUDA,
#ຖ້າ HAVE_FFNVCODEC_CUARRAY
                                                          AV_PIX_FMT_CUARRAY,
#endif
                                                          AV_PIX_FMT_NONE },
};
