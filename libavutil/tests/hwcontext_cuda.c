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

#ਅਨ੍ਤਰ੍ਭਾਵ <inttypes.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdatomic.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/adler32.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/hwcontext_cuda_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/imgutils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixfmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/time.h"

ਸਥਿਰ ਖਾਲੀ vflip(AVFrame *ਚੌਖਟਾ, ਅਚਲ AVPixFmtDescriptor *desc)
{
    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(ਚੌਖਟਾ->ਅੰਕੜੇ) && ਚੌਖਟਾ->ਅੰਕੜੇ[i]; i++) {
        ਪੂਰਨ ਖਿਸਕਾਓ = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        ਚੌਖਟਾ->ਅੰਕੜੇ[i]    += (AV_CEIL_RSHIFT(ਚੌਖਟਾ->ਉਚਾਈ, ਖਿਸਕਾਓ) - 1) * ਚੌਖਟਾ->linesize[i];
        ਚੌਖਟਾ->linesize[i] = -ਚੌਖਟਾ->linesize[i];
    }
}

ਸਥਿਰ ਪੂਰਨ test_format(AVBufferRef *device_ref, ਗਿਣਤੀ AVPixelFormat fmt,
                       ਪੂਰਨ flip_upload, ਪੂਰਨ flip_download)
{
    AVBufferRef *ਚੌਖਟੇ_ref = ਨਿਰਾ;
    AVHWFramesContext *hwfc;
    AVFrame *sw_ਚੌਖਟਾ = ਨਿਰਾ, *hw_ਚੌਖਟਾ = ਨਿਰਾ, *download = ਨਿਰਾ;
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    ਪੂਰਨ ret;

    ਚੌਖਟੇ_ref = av_hwframe_ctx_alloc(device_ref);
    ਜੇ (!ਚੌਖਟੇ_ref) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    hwfc = (AVHWFramesContext *)ਚੌਖਟੇ_ref->ਅੰਕੜੇ;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->ਚੌੜਾਈ     = 64;
    hwfc->ਉਚਾਈ    = 64;

    ret = av_hwframe_ctx_init(ਚੌਖਟੇ_ref);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    sw_ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    hw_ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    download = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!sw_ਚੌਖਟਾ || !hw_ਚੌਖਟਾ || !download) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    sw_ਚੌਖਟਾ->format = fmt;
    sw_ਚੌਖਟਾ->ਚੌੜਾਈ  = 64;
    sw_ਚੌਖਟਾ->ਉਚਾਈ = 64;
    ret = av_ਚੌਖਟਾ_get_ਬਫਰ(sw_ਚੌਖਟਾ, 0);
    ਜੇ (ret < 0)
        ਜਾਓ fail;
    ਜੇ (flip_upload)
        vflip(sw_ਚੌਖਟਾ, desc);

    {
        ਪੂਰਨ linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(sw_ਚੌਖਟਾ->ਅੰਕੜੇ) && sw_ਚੌਖਟਾ->ਅੰਕੜੇ[i]; i++) {
            ਪੂਰਨ ਖਿਸਕਾਓ = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            ਪੂਰਨ h = AV_CEIL_RSHIFT(64, ਖਿਸਕਾਓ);

            ਲਈ (ਪੂਰਨ y = 0; y < h; y++)
                ਲਈ (ਪੂਰਨ x = 0; x < linesizes[i]; x++)
                    sw_ਚੌਖਟਾ->ਅੰਕੜੇ[i][y * sw_ਚੌਖਟਾ->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_ਬਫਰ(ਚੌਖਟੇ_ref, hw_ਚੌਖਟਾ, 0);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    ret = av_hwframe_transfer_ਅੰਕੜੇ(hw_ਚੌਖਟਾ, sw_ਚੌਖਟਾ, 0);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    download->format = fmt;
    download->ਚੌੜਾਈ  = 64;
    download->ਉਚਾਈ = 64;
    ret = av_ਚੌਖਟਾ_get_ਬਫਰ(download, 0);
    ਜੇ (ret < 0)
        ਜਾਓ fail;
    ਜੇ (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_ਅੰਕੜੇ(download, hw_ਚੌਖਟਾ, 0);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    {
        ਪੂਰਨ linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(download->ਅੰਕੜੇ) && download->ਅੰਕੜੇ[i]; i++) {
            ਪੂਰਨ ਖਿਸਕਾਓ = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            ਪੂਰਨ h = AV_CEIL_RSHIFT(64, ਖਿਸਕਾਓ);

            ਲਈ (ਪੂਰਨ y = 0; y < h; y++) {
                ਜੇ (memcmp(sw_ਚੌਖਟਾ->ਅੰਕੜੇ[i] + y * sw_ਚੌਖਟਾ->linesize[i],
                           download->ਅੰਕੜੇ[i] + y * download->linesize[i],
                           linesizes[i])) {
                    ਲਿਖੋ("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    ਜਾਓ fail;
                }
            }
        }
    }

fail:
    av_ਚੌਖਟਾ_free(&sw_ਚੌਖਟਾ);
    av_ਚੌਖਟਾ_free(&hw_ਚੌਖਟਾ);
    av_ਚੌਖਟਾ_free(&download);
    av_ਬਫਰ_unref(&ਚੌਖਟੇ_ref);
    ਵਾਪਸ ret;
}

ਸਥਿਰ atomic_int ਸਰੋਤ_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
ਸਥਿਰ ਖਾਲੀ CUDAAPI hold_ਧਾਰਾ(CUstream ਧਾਰਾ, CUresult ਸਥਿਤੀ, ਖਾਲੀ *opaque)
{
    int64_t ਸ਼ੁਰੂ = av_gettime_relative();
    ਜਦੋਂ (!atomic_load(&ਸਰੋਤ_overwritten) && av_gettime_relative() - ਸ਼ੁਰੂ < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
ਸਥਿਰ ਪੂਰਨ test_ਸਰੋਤ_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->ਅੰਕੜੇ)->hwctx;
    CudaFunctions *cu = hwctx->ਅੰਦਰੂਨੀ->cuda_dl;
    AVBufferRef *ਚੌਖਟੇ_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc(), *hw_ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    AVFrame *download = av_ਚੌਖਟਾ_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    ਪੂਰਨ ret = AVERROR(ENOMEM);

    ਜੇ (!ਚੌਖਟੇ_ref || !sw_ਚੌਖਟਾ || !hw_ਚੌਖਟਾ || !download)
        ਜਾਓ fail;

    hwfc = (AVHWFramesContext *)ਚੌਖਟੇ_ref->ਅੰਕੜੇ;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->ਚੌੜਾਈ     = 64;
    hwfc->ਉਚਾਈ    = 64;
    ਜੇ ((ret = av_hwframe_ctx_init(ਚੌਖਟੇ_ref)) < 0 ||
        (ret = av_hwframe_get_ਬਫਰ(ਚੌਖਟੇ_ref, hw_ਚੌਖਟਾ, 0)) < 0)
        ਜਾਓ fail;

    ਲਈ (ਪੂਰਨ ਮੁੱਲ = 0x11; ਮੁੱਲ <= 0x22; ਮੁੱਲ += 0x11) {
        av_ਚੌਖਟਾ_unref(sw_ਚੌਖਟਾ);
        sw_ਚੌਖਟਾ->format = AV_PIX_FMT_GRAY8;
        sw_ਚੌਖਟਾ->ਚੌੜਾਈ  = 64;
        sw_ਚੌਖਟਾ->ਉਚਾਈ = 64;
        ਜੇ ((ret = av_hwframe_get_transfer_ਬਫਰ(ਚੌਖਟੇ_ref, sw_ਚੌਖਟਾ)) < 0)
            ਜਾਓ fail;
        ਲਈ (ਪੂਰਨ y = 0; y < 64; y++)
            memset(sw_ਚੌਖਟਾ->ਅੰਕੜੇ[0] + y * sw_ਚੌਖਟਾ->linesize[0], ਮੁੱਲ, 64);
        ਜੇ (ਮੁੱਲ == 0x22) {
            atomic_store(&ਸਰੋਤ_overwritten, 1);
            ਰੋਕੋ;
        }

        ret = AVERROR_EXTERNAL;
        ਜੇ (cu->cu_Ctx_ਧੱਕੋ_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            ਜਾਓ fail;
        ਜੇ (cu->cu_ਧਾਰਾ_ਜੋੜੋ_Callback(hwctx->ਧਾਰਾ, hold_ਧਾਰਾ, ਨਿਰਾ, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_ਕੱਢੋ_Current(&dummy);
        ਜੇ (ret < 0)
            ਜਾਓ fail;

        ਜੇ ((ret = av_hwframe_transfer_ਅੰਕੜੇ(hw_ਚੌਖਟਾ, sw_ਚੌਖਟਾ, 0)) < 0)
            ਜਾਓ fail;
    }

    ਜੇ ((ret = av_hwframe_transfer_ਅੰਕੜੇ(download, hw_ਚੌਖਟਾ, 0)) < 0)
        ਜਾਓ fail;
    ਲਈ (ਪੂਰਨ y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->ਅੰਕੜੇ[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_ਚੌਖਟਾ_free(&sw_ਚੌਖਟਾ);
    av_ਚੌਖਟਾ_free(&hw_ਚੌਖਟਾ);
    av_ਚੌਖਟਾ_free(&download);
    av_ਬਫਰ_unref(&ਚੌਖਟੇ_ref);
    ਵਾਪਸ ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
ਸਥਿਰ ਪੂਰਨ test_rejected(AVBufferRef *device_ref, ਗਿਣਤੀ AVPixelFormat fmt)
{
    AVBufferRef *ਚੌਖਟੇ_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    ਪੂਰਨ ret;

    ਜੇ (!ਚੌਖਟੇ_ref)
        ਵਾਪਸ AVERROR(ENOMEM);

    hwfc = (AVHWFramesContext *)ਚੌਖਟੇ_ref->ਅੰਕੜੇ;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->ਚੌੜਾਈ     = 64;
    hwfc->ਉਚਾਈ    = 64;

    /* Init is expected to fail; silence the resulting error log. */
    av_log_ਸੈੱਟ_level(AV_LOG_QUIET);
    ret = av_hwframe_ctx_init(ਚੌਖਟੇ_ref);
    av_log_ਸੈੱਟ_level(AV_LOG_INFO);

    av_ਬਫਰ_unref(&ਚੌਖਟੇ_ref);

    ਵਾਪਸ ret >= 0 ? AVERROR(EINVAL) : 0;
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVBufferRef *device_ref = ਨਿਰਾ;
    ਗਿਣਤੀ AVPixelFormat fmt;
    ਪੂਰਨ ret, failures = 0, ਕੁੱਲ = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, ਨਿਰਾ, ਨਿਰਾ, 0);
    ਜੇ (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        fprintf(stderr, "No CUDA device available, skipping.\n");
        ਵਾਪਸ 0;
    }

    ਲਈ (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        ਜੇ (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            ਜਾਰੀ;

        ਕੁੱਲ++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        ਜੇ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            ਜੇ (test_rejected(device_ref, fmt) < 0) {
                ਲਿਖੋ("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } ਨਹੀਂਤਾਂ {
            ret = 0;
            ਲਈ (ਪੂਰਨ flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            ਜੇ (ret < 0) {
                ਲਿਖੋ("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    ਕੁੱਲ++;
    ret = test_ਸਰੋਤ_reuse(device_ref);
    ਜੇ (ret < 0) {
        ਲਿਖੋ("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_ਬਫਰ_unref(&device_ref);

    ਜੇ (failures)
        ਲਿਖੋ("%d / %d tests failed.\n", failures, ਕੁੱਲ);
    ਨਹੀਂਤਾਂ
        ਲਿਖੋ("%d tests passed.\n", ਕੁੱਲ);

    ਵਾਪਸ !!failures;
}
