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

ساكن فراغ vflip(AVFrame *چوکھٹا, ثابت AVPixFmtDescriptor *desc)
{
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(چوکھٹا->انکڑے) && چوکھٹا->انکڑے[i]; i++) {
        صحيح کھسکاؤ = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        چوکھٹا->انکڑے[i]    += (AV_CEIL_RSHIFT(چوکھٹا->اچائی, کھسکاؤ) - 1) * چوکھٹا->linesize[i];
        چوکھٹا->linesize[i] = -چوکھٹا->linesize[i];
    }
}

ساكن صحيح test_format(AVBufferRef *device_ref, تعداد AVPixelFormat fmt,
                       صحيح flip_upload, صحيح flip_download)
{
    AVBufferRef *چوکھٹے_ref = عدم;
    AVHWFramesContext *hwfc;
    AVFrame *sw_چوکھٹا = عدم, *hw_چوکھٹا = عدم, *download = عدم;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    صحيح ret;

    چوکھٹے_ref = av_hwframe_ctx_alloc(device_ref);
    إذا (!چوکھٹے_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    hwfc = (AVHWFramesContext *)چوکھٹے_ref->انکڑے;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->چوڑائی     = 64;
    hwfc->اچائی    = 64;

    ret = av_hwframe_ctx_init(چوکھٹے_ref);
    إذا (ret < 0)
        اذهب fail;

    sw_چوکھٹا = av_چوکھٹا_alloc();
    hw_چوکھٹا = av_چوکھٹا_alloc();
    download = av_چوکھٹا_alloc();
    إذا (!sw_چوکھٹا || !hw_چوکھٹا || !download) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    sw_چوکھٹا->format = fmt;
    sw_چوکھٹا->چوڑائی  = 64;
    sw_چوکھٹا->اچائی = 64;
    ret = av_چوکھٹا_get_بفر(sw_چوکھٹا, 0);
    إذا (ret < 0)
        اذهب fail;
    إذا (flip_upload)
        vflip(sw_چوکھٹا, desc);

    {
        صحيح linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(sw_چوکھٹا->انکڑے) && sw_چوکھٹا->انکڑے[i]; i++) {
            صحيح کھسکاؤ = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            صحيح h = AV_CEIL_RSHIFT(64, کھسکاؤ);

            لكل (صحيح y = 0; y < h; y++)
                لكل (صحيح x = 0; x < linesizes[i]; x++)
                    sw_چوکھٹا->انکڑے[i][y * sw_چوکھٹا->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_بفر(چوکھٹے_ref, hw_چوکھٹا, 0);
    إذا (ret < 0)
        اذهب fail;

    ret = av_hwframe_transfer_انکڑے(hw_چوکھٹا, sw_چوکھٹا, 0);
    إذا (ret < 0)
        اذهب fail;

    download->format = fmt;
    download->چوڑائی  = 64;
    download->اچائی = 64;
    ret = av_چوکھٹا_get_بفر(download, 0);
    إذا (ret < 0)
        اذهب fail;
    إذا (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_انکڑے(download, hw_چوکھٹا, 0);
    إذا (ret < 0)
        اذهب fail;

    {
        صحيح linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(download->انکڑے) && download->انکڑے[i]; i++) {
            صحيح کھسکاؤ = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            صحيح h = AV_CEIL_RSHIFT(64, کھسکاؤ);

            لكل (صحيح y = 0; y < h; y++) {
                إذا (memcmp(sw_چوکھٹا->انکڑے[i] + y * sw_چوکھٹا->linesize[i],
                           download->انکڑے[i] + y * download->linesize[i],
                           linesizes[i])) {
                    لکھو("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    اذهب fail;
                }
            }
        }
    }

fail:
    av_چوکھٹا_free(&sw_چوکھٹا);
    av_چوکھٹا_free(&hw_چوکھٹا);
    av_چوکھٹا_free(&download);
    av_بفر_unref(&چوکھٹے_ref);
    أرجع ret;
}

ساكن atomic_int سروت_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
ساكن فراغ CUDAAPI hold_دھارا(CUstream دھارا, CUresult حالت, فراغ *opaque)
{
    int64_t شروع = av_gettime_relative();
    طالما (!atomic_load(&سروت_overwritten) && av_gettime_relative() - شروع < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
ساكن صحيح test_سروت_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->انکڑے)->hwctx;
    CudaFunctions *cu = hwctx->اندرونی->cuda_dl;
    AVBufferRef *چوکھٹے_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_چوکھٹا = av_چوکھٹا_alloc(), *hw_چوکھٹا = av_چوکھٹا_alloc();
    AVFrame *download = av_چوکھٹا_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    صحيح ret = AVERROR(ENOMEM);

    إذا (!چوکھٹے_ref || !sw_چوکھٹا || !hw_چوکھٹا || !download)
        اذهب fail;

    hwfc = (AVHWFramesContext *)چوکھٹے_ref->انکڑے;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->چوڑائی     = 64;
    hwfc->اچائی    = 64;
    إذا ((ret = av_hwframe_ctx_init(چوکھٹے_ref)) < 0 ||
        (ret = av_hwframe_get_بفر(چوکھٹے_ref, hw_چوکھٹا, 0)) < 0)
        اذهب fail;

    لكل (صحيح قدر = 0x11; قدر <= 0x22; قدر += 0x11) {
        av_چوکھٹا_unref(sw_چوکھٹا);
        sw_چوکھٹا->format = AV_PIX_FMT_GRAY8;
        sw_چوکھٹا->چوڑائی  = 64;
        sw_چوکھٹا->اچائی = 64;
        إذا ((ret = av_hwframe_get_transfer_بفر(چوکھٹے_ref, sw_چوکھٹا)) < 0)
            اذهب fail;
        لكل (صحيح y = 0; y < 64; y++)
            memset(sw_چوکھٹا->انکڑے[0] + y * sw_چوکھٹا->linesize[0], قدر, 64);
        إذا (قدر == 0x22) {
            atomic_store(&سروت_overwritten, 1);
            اكسر;
        }

        ret = AVERROR_EXTERNAL;
        إذا (cu->cu_Ctx_ڈالو_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            اذهب fail;
        إذا (cu->cu_دھارا_جوڑو_Callback(hwctx->دھارا, hold_دھارا, عدم, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_نکالو_Current(&dummy);
        إذا (ret < 0)
            اذهب fail;

        إذا ((ret = av_hwframe_transfer_انکڑے(hw_چوکھٹا, sw_چوکھٹا, 0)) < 0)
            اذهب fail;
    }

    إذا ((ret = av_hwframe_transfer_انکڑے(download, hw_چوکھٹا, 0)) < 0)
        اذهب fail;
    لكل (صحيح y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->انکڑے[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_چوکھٹا_free(&sw_چوکھٹا);
    av_چوکھٹا_free(&hw_چوکھٹا);
    av_چوکھٹا_free(&download);
    av_بفر_unref(&چوکھٹے_ref);
    أرجع ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
ساكن صحيح test_rejected(AVBufferRef *device_ref, تعداد AVPixelFormat fmt)
{
    AVBufferRef *چوکھٹے_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    صحيح ret;

    إذا (!چوکھٹے_ref)
        أرجع AVERROR(ENOMEM);

    hwfc = (AVHWFramesContext *)چوکھٹے_ref->انکڑے;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->چوڑائی     = 64;
    hwfc->اچائی    = 64;

    /* Init is expected to fail; silence the resulting error log. */
    av_log_سیٹ_level(AV_LOG_QUIET);
    ret = av_hwframe_ctx_init(چوکھٹے_ref);
    av_log_سیٹ_level(AV_LOG_INFO);

    av_بفر_unref(&چوکھٹے_ref);

    أرجع ret >= 0 ? AVERROR(EINVAL) : 0;
}

صحيح مکھ(فراغ)
{
    AVBufferRef *device_ref = عدم;
    تعداد AVPixelFormat fmt;
    صحيح ret, failures = 0, کل = 0;

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

        کل++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        إذا (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            إذا (test_rejected(device_ref, fmt) < 0) {
                لکھو("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } وإلا {
            ret = 0;
            لكل (صحيح flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            إذا (ret < 0) {
                لکھو("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    کل++;
    ret = test_سروت_reuse(device_ref);
    إذا (ret < 0) {
        لکھو("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_بفر_unref(&device_ref);

    إذا (failures)
        لکھو("%d / %d tests failed.\n", failures, کل);
    وإلا
        لکھو("%d tests passed.\n", کل);

    أرجع !!failures;
}
