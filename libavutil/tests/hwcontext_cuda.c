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

#ಅನ್ತರ್ಭಾವ <inttypes.h>
#ಅನ್ತರ್ಭಾವ <stdatomic.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/adler32.h"
#ಅನ್ತರ್ಭಾವ "libavutil/hwcontext.h"
#ಅನ್ತರ್ಭಾವ "libavutil/hwcontext_cuda_internal.h"
#ಅನ್ತರ್ಭಾವ "libavutil/imgutils.h"
#ಅನ್ತರ್ಭಾವ "libavutil/log.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"
#ಅನ್ತರ್ಭಾವ "libavutil/pixdesc.h"
#ಅನ್ತರ್ಭಾವ "libavutil/pixfmt.h"
#ಅನ್ತರ್ಭಾವ "libavutil/time.h"

ಸ್ಥಿರ ಶೂನ್ಯ vflip(AVFrame *ಚೌಕಟ್ಟು, ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ) && ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i]; i++) {
        ಪೂರ್ಣಾಂಕ ಸರಿಸು = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i]    += (AV_CEIL_RSHIFT(ಚೌಕಟ್ಟು->ಎತ್ತರ, ಸರಿಸು) - 1) * ಚೌಕಟ್ಟು->linesize[i];
        ಚೌಕಟ್ಟು->linesize[i] = -ಚೌಕಟ್ಟು->linesize[i];
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_format(AVBufferRef *device_ref, ಎಣಿಕೆ AVPixelFormat fmt,
                       ಪೂರ್ಣಾಂಕ flip_upload, ಪೂರ್ಣಾಂಕ flip_download)
{
    AVBufferRef *ಚೌಕಟ್ಟುಗಳು_ref = ಖಾಲಿ;
    AVHWFramesContext *hwfc;
    AVFrame *sw_ಚೌಕಟ್ಟು = ಖಾಲಿ, *hw_ಚೌಕಟ್ಟು = ಖಾಲಿ, *download = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    ಪೂರ್ಣಾಂಕ ret;

    ಚೌಕಟ್ಟುಗಳು_ref = av_hwframe_ctx_alloc(device_ref);
    ಆದರೆ (!ಚೌಕಟ್ಟುಗಳು_ref) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    hwfc = (AVHWFramesContext *)ಚೌಕಟ್ಟುಗಳು_ref->ದತ್ತಾಂಶ;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->ಅಗಲ     = 64;
    hwfc->ಎತ್ತರ    = 64;

    ret = av_hwframe_ctx_init(ಚೌಕಟ್ಟುಗಳು_ref);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    sw_ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    hw_ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    download = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!sw_ಚೌಕಟ್ಟು || !hw_ಚೌಕಟ್ಟು || !download) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    sw_ಚೌಕಟ್ಟು->format = fmt;
    sw_ಚೌಕಟ್ಟು->ಅಗಲ  = 64;
    sw_ಚೌಕಟ್ಟು->ಎತ್ತರ = 64;
    ret = av_ಚೌಕಟ್ಟು_get_ಬಫರ್(sw_ಚೌಕಟ್ಟು, 0);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;
    ಆದರೆ (flip_upload)
        vflip(sw_ಚೌಕಟ್ಟು, desc);

    {
        ಪೂರ್ಣಾಂಕ linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(sw_ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ) && sw_ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i]; i++) {
            ಪೂರ್ಣಾಂಕ ಸರಿಸು = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            ಪೂರ್ಣಾಂಕ h = AV_CEIL_RSHIFT(64, ಸರಿಸು);

            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ y = 0; y < h; y++)
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ x = 0; x < linesizes[i]; x++)
                    sw_ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i][y * sw_ಚೌಕಟ್ಟು->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_ಬಫರ್(ಚೌಕಟ್ಟುಗಳು_ref, hw_ಚೌಕಟ್ಟು, 0);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    ret = av_hwframe_transfer_ದತ್ತಾಂಶ(hw_ಚೌಕಟ್ಟು, sw_ಚೌಕಟ್ಟು, 0);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    download->format = fmt;
    download->ಅಗಲ  = 64;
    download->ಎತ್ತರ = 64;
    ret = av_ಚೌಕಟ್ಟು_get_ಬಫರ್(download, 0);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;
    ಆದರೆ (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_ದತ್ತಾಂಶ(download, hw_ಚೌಕಟ್ಟು, 0);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    {
        ಪೂರ್ಣಾಂಕ linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(download->ದತ್ತಾಂಶ) && download->ದತ್ತಾಂಶ[i]; i++) {
            ಪೂರ್ಣಾಂಕ ಸರಿಸು = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            ಪೂರ್ಣಾಂಕ h = AV_CEIL_RSHIFT(64, ಸರಿಸು);

            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ y = 0; y < h; y++) {
                ಆದರೆ (memcmp(sw_ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[i] + y * sw_ಚೌಕಟ್ಟು->linesize[i],
                           download->ದತ್ತಾಂಶ[i] + y * download->linesize[i],
                           linesizes[i])) {
                    ಬರೆ("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    ಹೋಗು fail;
                }
            }
        }
    }

fail:
    av_ಚೌಕಟ್ಟು_free(&sw_ಚೌಕಟ್ಟು);
    av_ಚೌಕಟ್ಟು_free(&hw_ಚೌಕಟ್ಟು);
    av_ಚೌಕಟ್ಟು_free(&download);
    av_ಬಫರ್_unref(&ಚೌಕಟ್ಟುಗಳು_ref);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ atomic_int ಮೂಲ_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
ಸ್ಥಿರ ಶೂನ್ಯ CUDAAPI hold_ಹರಿವು(CUstream ಹರಿವು, CUresult ಸ್ಥಿತಿ_2, ಶೂನ್ಯ *opaque)
{
    int64_t ಆರಂಭ = av_gettime_relative();
    ಆಗ (!atomic_load(&ಮೂಲ_overwritten) && av_gettime_relative() - ಆರಂಭ < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_ಮೂಲ_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->ದತ್ತಾಂಶ)->hwctx;
    CudaFunctions *cu = hwctx->ಆಂತರಿಕ->cuda_dl;
    AVBufferRef *ಚೌಕಟ್ಟುಗಳು_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc(), *hw_ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    AVFrame *download = av_ಚೌಕಟ್ಟು_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    ಪೂರ್ಣಾಂಕ ret = AVERROR(ENOMEM);

    ಆದರೆ (!ಚೌಕಟ್ಟುಗಳು_ref || !sw_ಚೌಕಟ್ಟು || !hw_ಚೌಕಟ್ಟು || !download)
        ಹೋಗು fail;

    hwfc = (AVHWFramesContext *)ಚೌಕಟ್ಟುಗಳು_ref->ದತ್ತಾಂಶ;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->ಅಗಲ     = 64;
    hwfc->ಎತ್ತರ    = 64;
    ಆದರೆ ((ret = av_hwframe_ctx_init(ಚೌಕಟ್ಟುಗಳು_ref)) < 0 ||
        (ret = av_hwframe_get_ಬಫರ್(ಚೌಕಟ್ಟುಗಳು_ref, hw_ಚೌಕಟ್ಟು, 0)) < 0)
        ಹೋಗು fail;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ = 0x11; ಮೌಲ್ಯ <= 0x22; ಮೌಲ್ಯ += 0x11) {
        av_ಚೌಕಟ್ಟು_unref(sw_ಚೌಕಟ್ಟು);
        sw_ಚೌಕಟ್ಟು->format = AV_PIX_FMT_GRAY8;
        sw_ಚೌಕಟ್ಟು->ಅಗಲ  = 64;
        sw_ಚೌಕಟ್ಟು->ಎತ್ತರ = 64;
        ಆದರೆ ((ret = av_hwframe_get_transfer_ಬಫರ್(ಚೌಕಟ್ಟುಗಳು_ref, sw_ಚೌಕಟ್ಟು)) < 0)
            ಹೋಗು fail;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ y = 0; y < 64; y++)
            memset(sw_ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + y * sw_ಚೌಕಟ್ಟು->linesize[0], ಮೌಲ್ಯ, 64);
        ಆದರೆ (ಮೌಲ್ಯ == 0x22) {
            atomic_store(&ಮೂಲ_overwritten, 1);
            ನಿಲ್ಲಿಸು;
        }

        ret = AVERROR_EXTERNAL;
        ಆದರೆ (cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            ಹೋಗು fail;
        ಆದರೆ (cu->cu_ಹರಿವು_ಕೂಡಿಸು_Callback(hwctx->ಹರಿವು, hold_ಹರಿವು, ಖಾಲಿ, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_ತೆಗೆ_Current(&dummy);
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;

        ಆದರೆ ((ret = av_hwframe_transfer_ದತ್ತಾಂಶ(hw_ಚೌಕಟ್ಟು, sw_ಚೌಕಟ್ಟು, 0)) < 0)
            ಹೋಗು fail;
    }

    ಆದರೆ ((ret = av_hwframe_transfer_ದತ್ತಾಂಶ(download, hw_ಚೌಕಟ್ಟು, 0)) < 0)
        ಹೋಗು fail;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->ದತ್ತಾಂಶ[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_ಚೌಕಟ್ಟು_free(&sw_ಚೌಕಟ್ಟು);
    av_ಚೌಕಟ್ಟು_free(&hw_ಚೌಕಟ್ಟು);
    av_ಚೌಕಟ್ಟು_free(&download);
    av_ಬಫರ್_unref(&ಚೌಕಟ್ಟುಗಳು_ref);
    ಹಿಂತಿರುಗಿ ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_rejected(AVBufferRef *device_ref, ಎಣಿಕೆ AVPixelFormat fmt)
{
    AVBufferRef *ಚೌಕಟ್ಟುಗಳು_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!ಚೌಕಟ್ಟುಗಳು_ref)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    hwfc = (AVHWFramesContext *)ಚೌಕಟ್ಟುಗಳು_ref->ದತ್ತಾಂಶ;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->ಅಗಲ     = 64;
    hwfc->ಎತ್ತರ    = 64;

    /* Init is expected to fail; silence the resulting error log. */
    av_log_ಗಣ_level(AV_LOG_QUIET);
    ret = av_hwframe_ctx_init(ಚೌಕಟ್ಟುಗಳು_ref);
    av_log_ಗಣ_level(AV_LOG_INFO);

    av_ಬಫರ್_unref(&ಚೌಕಟ್ಟುಗಳು_ref);

    ಹಿಂತಿರುಗಿ ret >= 0 ? AVERROR(EINVAL) : 0;
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVBufferRef *device_ref = ಖಾಲಿ;
    ಎಣಿಕೆ AVPixelFormat fmt;
    ಪೂರ್ಣಾಂಕ ret, failures = 0, ಒಟ್ಟು = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, ಖಾಲಿ, ಖಾಲಿ, 0);
    ಆದರೆ (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        fprintf(stderr, "No CUDA device available, skipping.\n");
        ಹಿಂತಿರುಗಿ 0;
    }

    ಗಾಗಿ (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        ಆದರೆ (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            ಮುಂದುವರಿ;

        ಒಟ್ಟು++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        ಆದರೆ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            ಆದರೆ (test_rejected(device_ref, fmt) < 0) {
                ಬರೆ("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ret = 0;
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            ಆದರೆ (ret < 0) {
                ಬರೆ("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    ಒಟ್ಟು++;
    ret = test_ಮೂಲ_reuse(device_ref);
    ಆದರೆ (ret < 0) {
        ಬರೆ("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_ಬಫರ್_unref(&device_ref);

    ಆದರೆ (failures)
        ಬರೆ("%d / %d tests failed.\n", failures, ಒಟ್ಟು);
    ಇಲ್ಲದಿದ್ದರೆ
        ಬರೆ("%d tests passed.\n", ಒಟ್ಟು);

    ಹಿಂತಿರುಗಿ !!failures;
}
