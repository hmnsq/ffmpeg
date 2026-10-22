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

#شامل <inttypes.h>
#شامل <stdatomic.h>
#شامل <stdio.h>
#شامل <string.h>

#شامل "libavutil/adler32.h"
#شامل "libavutil/hwcontext.h"
#شامل "libavutil/hwcontext_cuda_internal.h"
#شامل "libavutil/imgutils.h"
#شامل "libavutil/log.h"
#شامل "libavutil/mem.h"
#شامل "libavutil/pixdesc.h"
#شامل "libavutil/pixfmt.h"
#شامل "libavutil/time.h"

ساکن خالی vflip(AVFrame *چوکھٹا, ثابت AVPixFmtDescriptor *desc)
{
    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(چوکھٹا->ڈیٹا) && چوکھٹا->ڈیٹا[i]; i++) {
        صحیح سرکاؤ = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        چوکھٹا->ڈیٹا[i]    += (AV_CEIL_RSHIFT(چوکھٹا->اونچائی, سرکاؤ) - 1) * چوکھٹا->linesize[i];
        چوکھٹا->linesize[i] = -چوکھٹا->linesize[i];
    }
}

ساکن صحیح test_format(AVBufferRef *device_ref, شمار AVPixelFormat fmt,
                       صحیح flip_upload, صحیح flip_download)
{
    AVBufferRef *چوکھٹے_ref = تہی;
    AVHWFramesContext *hwfc;
    AVFrame *sw_چوکھٹا = تہی, *hw_چوکھٹا = تہی, *download = تہی;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    صحیح ret;

    چوکھٹے_ref = av_hwframe_ctx_alloc(device_ref);
    اگر (!چوکھٹے_ref) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }

    hwfc = (AVHWFramesContext *)چوکھٹے_ref->ڈیٹا;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->چوڑائی     = 64;
    hwfc->اونچائی    = 64;

    ret = av_hwframe_ctx_init(چوکھٹے_ref);
    اگر (ret < 0)
        جاؤ fail;

    sw_چوکھٹا = av_چوکھٹا_alloc();
    hw_چوکھٹا = av_چوکھٹا_alloc();
    download = av_چوکھٹا_alloc();
    اگر (!sw_چوکھٹا || !hw_چوکھٹا || !download) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }

    sw_چوکھٹا->format = fmt;
    sw_چوکھٹا->چوڑائی  = 64;
    sw_چوکھٹا->اونچائی = 64;
    ret = av_چوکھٹا_get_بفر(sw_چوکھٹا, 0);
    اگر (ret < 0)
        جاؤ fail;
    اگر (flip_upload)
        vflip(sw_چوکھٹا, desc);

    {
        صحیح linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(sw_چوکھٹا->ڈیٹا) && sw_چوکھٹا->ڈیٹا[i]; i++) {
            صحیح سرکاؤ = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            صحیح h = AV_CEIL_RSHIFT(64, سرکاؤ);

            برائے (صحیح y = 0; y < h; y++)
                برائے (صحیح x = 0; x < linesizes[i]; x++)
                    sw_چوکھٹا->ڈیٹا[i][y * sw_چوکھٹا->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_بفر(چوکھٹے_ref, hw_چوکھٹا, 0);
    اگر (ret < 0)
        جاؤ fail;

    ret = av_hwframe_transfer_ڈیٹا(hw_چوکھٹا, sw_چوکھٹا, 0);
    اگر (ret < 0)
        جاؤ fail;

    download->format = fmt;
    download->چوڑائی  = 64;
    download->اونچائی = 64;
    ret = av_چوکھٹا_get_بفر(download, 0);
    اگر (ret < 0)
        جاؤ fail;
    اگر (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_ڈیٹا(download, hw_چوکھٹا, 0);
    اگر (ret < 0)
        جاؤ fail;

    {
        صحیح linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(download->ڈیٹا) && download->ڈیٹا[i]; i++) {
            صحیح سرکاؤ = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            صحیح h = AV_CEIL_RSHIFT(64, سرکاؤ);

            برائے (صحیح y = 0; y < h; y++) {
                اگر (memcmp(sw_چوکھٹا->ڈیٹا[i] + y * sw_چوکھٹا->linesize[i],
                           download->ڈیٹا[i] + y * download->linesize[i],
                           linesizes[i])) {
                    لکھو("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    جاؤ fail;
                }
            }
        }
    }

fail:
    av_چوکھٹا_free(&sw_چوکھٹا);
    av_چوکھٹا_free(&hw_چوکھٹا);
    av_چوکھٹا_free(&download);
    av_بفر_unref(&چوکھٹے_ref);
    واپس ret;
}

ساکن atomic_int ماخذ_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
ساکن خالی CUDAAPI hold_دھارا(CUstream دھارا, CUresult حالت_2, خالی *opaque)
{
    int64_t آغاز = av_gettime_relative();
    جب (!atomic_load(&ماخذ_overwritten) && av_gettime_relative() - آغاز < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
ساکن صحیح test_ماخذ_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->ڈیٹا)->hwctx;
    CudaFunctions *cu = hwctx->اندرونی_2->cuda_dl;
    AVBufferRef *چوکھٹے_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_چوکھٹا = av_چوکھٹا_alloc(), *hw_چوکھٹا = av_چوکھٹا_alloc();
    AVFrame *download = av_چوکھٹا_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    صحیح ret = AVERROR(ENOMEM);

    اگر (!چوکھٹے_ref || !sw_چوکھٹا || !hw_چوکھٹا || !download)
        جاؤ fail;

    hwfc = (AVHWFramesContext *)چوکھٹے_ref->ڈیٹا;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->چوڑائی     = 64;
    hwfc->اونچائی    = 64;
    اگر ((ret = av_hwframe_ctx_init(چوکھٹے_ref)) < 0 ||
        (ret = av_hwframe_get_بفر(چوکھٹے_ref, hw_چوکھٹا, 0)) < 0)
        جاؤ fail;

    برائے (صحیح قدر = 0x11; قدر <= 0x22; قدر += 0x11) {
        av_چوکھٹا_unref(sw_چوکھٹا);
        sw_چوکھٹا->format = AV_PIX_FMT_GRAY8;
        sw_چوکھٹا->چوڑائی  = 64;
        sw_چوکھٹا->اونچائی = 64;
        اگر ((ret = av_hwframe_get_transfer_بفر(چوکھٹے_ref, sw_چوکھٹا)) < 0)
            جاؤ fail;
        برائے (صحیح y = 0; y < 64; y++)
            memset(sw_چوکھٹا->ڈیٹا[0] + y * sw_چوکھٹا->linesize[0], قدر, 64);
        اگر (قدر == 0x22) {
            atomic_store(&ماخذ_overwritten, 1);
            توڑو;
        }

        ret = AVERROR_EXTERNAL;
        اگر (cu->cu_Ctx_ڈالو_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            جاؤ fail;
        اگر (cu->cu_دھارا_جوڑو_Callback(hwctx->دھارا, hold_دھارا, تہی, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_نکالو_Current(&dummy);
        اگر (ret < 0)
            جاؤ fail;

        اگر ((ret = av_hwframe_transfer_ڈیٹا(hw_چوکھٹا, sw_چوکھٹا, 0)) < 0)
            جاؤ fail;
    }

    اگر ((ret = av_hwframe_transfer_ڈیٹا(download, hw_چوکھٹا, 0)) < 0)
        جاؤ fail;
    برائے (صحیح y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->ڈیٹا[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_چوکھٹا_free(&sw_چوکھٹا);
    av_چوکھٹا_free(&hw_چوکھٹا);
    av_چوکھٹا_free(&download);
    av_بفر_unref(&چوکھٹے_ref);
    واپس ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
ساکن صحیح test_rejected(AVBufferRef *device_ref, شمار AVPixelFormat fmt)
{
    AVBufferRef *چوکھٹے_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    صحیح ret;

    اگر (!چوکھٹے_ref)
        واپس AVERROR(ENOMEM);

    hwfc = (AVHWFramesContext *)چوکھٹے_ref->ڈیٹا;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->چوڑائی     = 64;
    hwfc->اونچائی    = 64;

    /* Init is expected to fail; silence the resulting error log. */
    av_log_سیٹ_level(AV_LOG_QUIET);
    ret = av_hwframe_ctx_init(چوکھٹے_ref);
    av_log_سیٹ_level(AV_LOG_INFO);

    av_بفر_unref(&چوکھٹے_ref);

    واپس ret >= 0 ? AVERROR(EINVAL) : 0;
}

صحیح مین(خالی)
{
    AVBufferRef *device_ref = تہی;
    شمار AVPixelFormat fmt;
    صحیح ret, failures = 0, کل = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, تہی, تہی, 0);
    اگر (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        fprintf(stderr, "No CUDA device available, skipping.\n");
        واپس 0;
    }

    برائے (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        اگر (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            جاری;

        کل++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        اگر (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            اگر (test_rejected(device_ref, fmt) < 0) {
                لکھو("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } ورنہ {
            ret = 0;
            برائے (صحیح flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            اگر (ret < 0) {
                لکھو("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    کل++;
    ret = test_ماخذ_reuse(device_ref);
    اگر (ret < 0) {
        لکھو("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_بفر_unref(&device_ref);

    اگر (failures)
        لکھو("%d / %d tests failed.\n", failures, کل);
    ورنہ
        لکھو("%d tests passed.\n", کل);

    واپس !!failures;
}
