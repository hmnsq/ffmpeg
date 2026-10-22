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

#ضمن <inttypes.h>
#ضمن <stdatomic.h>
#ضمن <stdio.h>
#ضمن <string.h>

#ضمن "libavutil/adler32.h"
#ضمن "libavutil/hwcontext.h"
#ضمن "libavutil/hwcontext_cuda_internal.h"
#ضمن "libavutil/imgutils.h"
#ضمن "libavutil/log.h"
#ضمن "libavutil/mem.h"
#ضمن "libavutil/pixdesc.h"
#ضمن "libavutil/pixfmt.h"
#ضمن "libavutil/time.h"

ساكن فراغ vflip(AVFrame *چوکاټ, ثابت AVPixFmtDescriptor *desc)
{
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(چوکاټ->معلومات) && چوکاټ->معلومات[i]; i++) {
        صحيح ښويدنه = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        چوکاټ->معلومات[i]    += (AV_CEIL_RSHIFT(چوکاټ->لوړوالی, ښويدنه) - 1) * چوکاټ->linesize[i];
        چوکاټ->linesize[i] = -چوکاټ->linesize[i];
    }
}

ساكن صحيح test_format(AVBufferRef *device_ref, تعداد AVPixelFormat fmt,
                       صحيح flip_upload, صحيح flip_download)
{
    AVBufferRef *چوکاټونه_ref = عدم;
    AVHWFramesContext *hwfc;
    AVFrame *sw_چوکاټ = عدم, *hw_چوکاټ = عدم, *download = عدم;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    صحيح ret;

    چوکاټونه_ref = av_hwframe_ctx_alloc(device_ref);
    إذا (!چوکاټونه_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    hwfc = (AVHWFramesContext *)چوکاټونه_ref->معلومات;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->پلنوالی     = 64;
    hwfc->لوړوالی    = 64;

    ret = av_hwframe_ctx_init(چوکاټونه_ref);
    إذا (ret < 0)
        اذهب fail;

    sw_چوکاټ = av_چوکاټ_alloc();
    hw_چوکاټ = av_چوکاټ_alloc();
    download = av_چوکاټ_alloc();
    إذا (!sw_چوکاټ || !hw_چوکاټ || !download) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    sw_چوکاټ->format = fmt;
    sw_چوکاټ->پلنوالی  = 64;
    sw_چوکاټ->لوړوالی = 64;
    ret = av_چوکاټ_get_بفر(sw_چوکاټ, 0);
    إذا (ret < 0)
        اذهب fail;
    إذا (flip_upload)
        vflip(sw_چوکاټ, desc);

    {
        صحيح linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(sw_چوکاټ->معلومات) && sw_چوکاټ->معلومات[i]; i++) {
            صحيح ښويدنه = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            صحيح h = AV_CEIL_RSHIFT(64, ښويدنه);

            لكل (صحيح y = 0; y < h; y++)
                لكل (صحيح x = 0; x < linesizes[i]; x++)
                    sw_چوکاټ->معلومات[i][y * sw_چوکاټ->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_بفر(چوکاټونه_ref, hw_چوکاټ, 0);
    إذا (ret < 0)
        اذهب fail;

    ret = av_hwframe_transfer_معلومات(hw_چوکاټ, sw_چوکاټ, 0);
    إذا (ret < 0)
        اذهب fail;

    download->format = fmt;
    download->پلنوالی  = 64;
    download->لوړوالی = 64;
    ret = av_چوکاټ_get_بفر(download, 0);
    إذا (ret < 0)
        اذهب fail;
    إذا (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_معلومات(download, hw_چوکاټ, 0);
    إذا (ret < 0)
        اذهب fail;

    {
        صحيح linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(download->معلومات) && download->معلومات[i]; i++) {
            صحيح ښويدنه = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            صحيح h = AV_CEIL_RSHIFT(64, ښويدنه);

            لكل (صحيح y = 0; y < h; y++) {
                إذا (memcmp(sw_چوکاټ->معلومات[i] + y * sw_چوکاټ->linesize[i],
                           download->معلومات[i] + y * download->linesize[i],
                           linesizes[i])) {
                    چاپ_کړه("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    اذهب fail;
                }
            }
        }
    }

fail:
    av_چوکاټ_free(&sw_چوکاټ);
    av_چوکاټ_free(&hw_چوکاټ);
    av_چوکاټ_free(&download);
    av_بفر_unref(&چوکاټونه_ref);
    أرجع ret;
}

ساكن atomic_int سرچینه_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
ساكن فراغ CUDAAPI hold_بهیر(CUstream بهیر, CUresult حالت, فراغ *opaque)
{
    int64_t پیل = av_gettime_relative();
    طالما (!atomic_load(&سرچینه_overwritten) && av_gettime_relative() - پیل < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
ساكن صحيح test_سرچینه_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->معلومات)->hwctx;
    CudaFunctions *cu = hwctx->دننی->cuda_dl;
    AVBufferRef *چوکاټونه_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_چوکاټ = av_چوکاټ_alloc(), *hw_چوکاټ = av_چوکاټ_alloc();
    AVFrame *download = av_چوکاټ_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    صحيح ret = AVERROR(ENOMEM);

    إذا (!چوکاټونه_ref || !sw_چوکاټ || !hw_چوکاټ || !download)
        اذهب fail;

    hwfc = (AVHWFramesContext *)چوکاټونه_ref->معلومات;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->پلنوالی     = 64;
    hwfc->لوړوالی    = 64;
    إذا ((ret = av_hwframe_ctx_init(چوکاټونه_ref)) < 0 ||
        (ret = av_hwframe_get_بفر(چوکاټونه_ref, hw_چوکاټ, 0)) < 0)
        اذهب fail;

    لكل (صحيح ارزښت = 0x11; ارزښت <= 0x22; ارزښت += 0x11) {
        av_چوکاټ_unref(sw_چوکاټ);
        sw_چوکاټ->format = AV_PIX_FMT_GRAY8;
        sw_چوکاټ->پلنوالی  = 64;
        sw_چوکاټ->لوړوالی = 64;
        إذا ((ret = av_hwframe_get_transfer_بفر(چوکاټونه_ref, sw_چوکاټ)) < 0)
            اذهب fail;
        لكل (صحيح y = 0; y < 64; y++)
            memset(sw_چوکاټ->معلومات[0] + y * sw_چوکاټ->linesize[0], ارزښت, 64);
        إذا (ارزښت == 0x22) {
            atomic_store(&سرچینه_overwritten, 1);
            اكسر;
        }

        ret = AVERROR_EXTERNAL;
        إذا (cu->cu_Ctx_ټېل_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            اذهب fail;
        إذا (cu->cu_بهیر_جمع_کړه_Callback(hwctx->بهیر, hold_بهیر, عدم, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_راوباسه_Current(&dummy);
        إذا (ret < 0)
            اذهب fail;

        إذا ((ret = av_hwframe_transfer_معلومات(hw_چوکاټ, sw_چوکاټ, 0)) < 0)
            اذهب fail;
    }

    إذا ((ret = av_hwframe_transfer_معلومات(download, hw_چوکاټ, 0)) < 0)
        اذهب fail;
    لكل (صحيح y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->معلومات[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_چوکاټ_free(&sw_چوکاټ);
    av_چوکاټ_free(&hw_چوکاټ);
    av_چوکاټ_free(&download);
    av_بفر_unref(&چوکاټونه_ref);
    أرجع ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
ساكن صحيح test_rejected(AVBufferRef *device_ref, تعداد AVPixelFormat fmt)
{
    AVBufferRef *چوکاټونه_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    صحيح ret;

    إذا (!چوکاټونه_ref)
        أرجع AVERROR(ENOMEM);

    hwfc = (AVHWFramesContext *)چوکاټونه_ref->معلومات;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->پلنوالی     = 64;
    hwfc->لوړوالی    = 64;

    /* Init is expected to fail; silence the resulting error log. */
    av_log_سېټ_level(AV_LOG_QUIET);
    ret = av_hwframe_ctx_init(چوکاټونه_ref);
    av_log_سېټ_level(AV_LOG_INFO);

    av_بفر_unref(&چوکاټونه_ref);

    أرجع ret >= 0 ? AVERROR(EINVAL) : 0;
}

صحيح اصلي(فراغ)
{
    AVBufferRef *device_ref = عدم;
    تعداد AVPixelFormat fmt;
    صحيح ret, failures = 0, ټول = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, عدم, عدم, 0);
    إذا (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        fprintf(stderr, "No CUDA device available, skipping.\n");
        أرجع 0;
    }

    لكل (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        إذا (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            استمر;

        ټول++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        إذا (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            إذا (test_rejected(device_ref, fmt) < 0) {
                چاپ_کړه("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } وإلا {
            ret = 0;
            لكل (صحيح flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            إذا (ret < 0) {
                چاپ_کړه("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    ټول++;
    ret = test_سرچینه_reuse(device_ref);
    إذا (ret < 0) {
        چاپ_کړه("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_بفر_unref(&device_ref);

    إذا (failures)
        چاپ_کړه("%d / %d tests failed.\n", failures, ټول);
    وإلا
        چاپ_کړه("%d tests passed.\n", ټول);

    أرجع !!failures;
}
