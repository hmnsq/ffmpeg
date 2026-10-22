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

ساكن فراغ vflip(AVFrame *چوکٺو, ثابت AVPixFmtDescriptor *desc)
{
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(چوکٺو->معلومات) && چوکٺو->معلومات[i]; i++) {
        صحيح سرڪايو = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        چوکٺو->معلومات[i]    += (AV_CEIL_RSHIFT(چوکٺو->اوچائي, سرڪايو) - 1) * چوکٺو->linesize[i];
        چوکٺو->linesize[i] = -چوکٺو->linesize[i];
    }
}

ساكن صحيح test_format(AVBufferRef *device_ref, تعداد AVPixelFormat fmt,
                       صحيح flip_upload, صحيح flip_download)
{
    AVBufferRef *چوکٺا_ref = عدم;
    AVHWFramesContext *hwfc;
    AVFrame *sw_چوکٺو = عدم, *hw_چوکٺو = عدم, *download = عدم;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    صحيح ret;

    چوکٺا_ref = av_hwframe_ctx_alloc(device_ref);
    إذا (!چوکٺا_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    hwfc = (AVHWFramesContext *)چوکٺا_ref->معلومات;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->ويڪر     = 64;
    hwfc->اوچائي    = 64;

    ret = av_hwframe_ctx_init(چوکٺا_ref);
    إذا (ret < 0)
        اذهب fail;

    sw_چوکٺو = av_چوکٺو_alloc();
    hw_چوکٺو = av_چوکٺو_alloc();
    download = av_چوکٺو_alloc();
    إذا (!sw_چوکٺو || !hw_چوکٺو || !download) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    sw_چوکٺو->format = fmt;
    sw_چوکٺو->ويڪر  = 64;
    sw_چوکٺو->اوچائي = 64;
    ret = av_چوکٺو_get_بفر(sw_چوکٺو, 0);
    إذا (ret < 0)
        اذهب fail;
    إذا (flip_upload)
        vflip(sw_چوکٺو, desc);

    {
        صحيح linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(sw_چوکٺو->معلومات) && sw_چوکٺو->معلومات[i]; i++) {
            صحيح سرڪايو = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            صحيح h = AV_CEIL_RSHIFT(64, سرڪايو);

            لكل (صحيح y = 0; y < h; y++)
                لكل (صحيح x = 0; x < linesizes[i]; x++)
                    sw_چوکٺو->معلومات[i][y * sw_چوکٺو->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_بفر(چوکٺا_ref, hw_چوکٺو, 0);
    إذا (ret < 0)
        اذهب fail;

    ret = av_hwframe_transfer_معلومات(hw_چوکٺو, sw_چوکٺو, 0);
    إذا (ret < 0)
        اذهب fail;

    download->format = fmt;
    download->ويڪر  = 64;
    download->اوچائي = 64;
    ret = av_چوکٺو_get_بفر(download, 0);
    إذا (ret < 0)
        اذهب fail;
    إذا (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_معلومات(download, hw_چوکٺو, 0);
    إذا (ret < 0)
        اذهب fail;

    {
        صحيح linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(download->معلومات) && download->معلومات[i]; i++) {
            صحيح سرڪايو = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            صحيح h = AV_CEIL_RSHIFT(64, سرڪايو);

            لكل (صحيح y = 0; y < h; y++) {
                إذا (memcmp(sw_چوکٺو->معلومات[i] + y * sw_چوکٺو->linesize[i],
                           download->معلومات[i] + y * download->linesize[i],
                           linesizes[i])) {
                    لکو("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    اذهب fail;
                }
            }
        }
    }

fail:
    av_چوکٺو_free(&sw_چوکٺو);
    av_چوکٺو_free(&hw_چوکٺو);
    av_چوکٺو_free(&download);
    av_بفر_unref(&چوکٺا_ref);
    أرجع ret;
}

ساكن atomic_int ذريعو_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
ساكن فراغ CUDAAPI hold_وهڪرو(CUstream وهڪرو, CUresult حالت, فراغ *opaque)
{
    int64_t شروعات = av_gettime_relative();
    طالما (!atomic_load(&ذريعو_overwritten) && av_gettime_relative() - شروعات < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
ساكن صحيح test_ذريعو_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->معلومات)->hwctx;
    CudaFunctions *cu = hwctx->اندروني->cuda_dl;
    AVBufferRef *چوکٺا_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_چوکٺو = av_چوکٺو_alloc(), *hw_چوکٺو = av_چوکٺو_alloc();
    AVFrame *download = av_چوکٺو_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    صحيح ret = AVERROR(ENOMEM);

    إذا (!چوکٺا_ref || !sw_چوکٺو || !hw_چوکٺو || !download)
        اذهب fail;

    hwfc = (AVHWFramesContext *)چوکٺا_ref->معلومات;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->ويڪر     = 64;
    hwfc->اوچائي    = 64;
    إذا ((ret = av_hwframe_ctx_init(چوکٺا_ref)) < 0 ||
        (ret = av_hwframe_get_بفر(چوکٺا_ref, hw_چوکٺو, 0)) < 0)
        اذهب fail;

    لكل (صحيح قدر = 0x11; قدر <= 0x22; قدر += 0x11) {
        av_چوکٺو_unref(sw_چوکٺو);
        sw_چوکٺو->format = AV_PIX_FMT_GRAY8;
        sw_چوکٺو->ويڪر  = 64;
        sw_چوکٺو->اوچائي = 64;
        إذا ((ret = av_hwframe_get_transfer_بفر(چوکٺا_ref, sw_چوکٺو)) < 0)
            اذهب fail;
        لكل (صحيح y = 0; y < 64; y++)
            memset(sw_چوکٺو->معلومات[0] + y * sw_چوکٺو->linesize[0], قدر, 64);
        إذا (قدر == 0x22) {
            atomic_store(&ذريعو_overwritten, 1);
            اكسر;
        }

        ret = AVERROR_EXTERNAL;
        إذا (cu->cu_Ctx_ڌڪو_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            اذهب fail;
        إذا (cu->cu_وهڪرو_جوڙيو_Callback(hwctx->وهڪرو, hold_وهڪرو, عدم, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_ڪڍو_Current(&dummy);
        إذا (ret < 0)
            اذهب fail;

        إذا ((ret = av_hwframe_transfer_معلومات(hw_چوکٺو, sw_چوکٺو, 0)) < 0)
            اذهب fail;
    }

    إذا ((ret = av_hwframe_transfer_معلومات(download, hw_چوکٺو, 0)) < 0)
        اذهب fail;
    لكل (صحيح y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->معلومات[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_چوکٺو_free(&sw_چوکٺو);
    av_چوکٺو_free(&hw_چوکٺو);
    av_چوکٺو_free(&download);
    av_بفر_unref(&چوکٺا_ref);
    أرجع ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
ساكن صحيح test_rejected(AVBufferRef *device_ref, تعداد AVPixelFormat fmt)
{
    AVBufferRef *چوکٺا_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    صحيح ret;

    إذا (!چوکٺا_ref)
        أرجع AVERROR(ENOMEM);

    hwfc = (AVHWFramesContext *)چوکٺا_ref->معلومات;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->ويڪر     = 64;
    hwfc->اوچائي    = 64;

    /* Init is expected to fail; silence the resulting error log. */
    av_log_سيٽ_level(AV_LOG_QUIET);
    ret = av_hwframe_ctx_init(چوکٺا_ref);
    av_log_سيٽ_level(AV_LOG_INFO);

    av_بفر_unref(&چوکٺا_ref);

    أرجع ret >= 0 ? AVERROR(EINVAL) : 0;
}

صحيح مکيه(فراغ)
{
    AVBufferRef *device_ref = عدم;
    تعداد AVPixelFormat fmt;
    صحيح ret, failures = 0, ڪل = 0;

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

        ڪل++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        إذا (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            إذا (test_rejected(device_ref, fmt) < 0) {
                لکو("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } وإلا {
            ret = 0;
            لكل (صحيح flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            إذا (ret < 0) {
                لکو("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    ڪل++;
    ret = test_ذريعو_reuse(device_ref);
    إذا (ret < 0) {
        لکو("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_بفر_unref(&device_ref);

    إذا (failures)
        لکو("%d / %d tests failed.\n", failures, ڪل);
    وإلا
        لکو("%d tests passed.\n", ڪل);

    أرجع !!failures;
}
