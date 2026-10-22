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

ಸ್ಥಿರ ಶೂನ್ಯ vflip(AVFrame *frame, ಧ್ರುವ AVPixFmtDescriptor *desc)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(frame->data) && frame->data[i]; i++) {
        ಪೂರ್ಣಾಙ್ಕ shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        frame->data[i]    += (AV_CEIL_RSHIFT(frame->height, shift) - 1) * frame->linesize[i];
        frame->linesize[i] = -frame->linesize[i];
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_format(AVBufferRef *device_ref, ಗಣನಾ AVPixelFormat fmt,
                       ಪೂರ್ಣಾಙ್ಕ flip_upload, ಪೂರ್ಣಾಙ್ಕ flip_download)
{
    AVBufferRef *frames_ref = ರಿಕ್ತ;
    AVHWFramesContext *hwfc;
    AVFrame *sw_frame = ರಿಕ್ತ, *hw_frame = ರಿಕ್ತ, *download = ರಿಕ್ತ;
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    ಪೂರ್ಣಾಙ್ಕ ret;

    frames_ref = av_hwframe_ctx_alloc(device_ref);
    ಯದಿ (!frames_ref) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->width     = 64;
    hwfc->height    = 64;

    ret = av_hwframe_ctx_init(frames_ref);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    sw_frame = av_frame_alloc();
    hw_frame = av_frame_alloc();
    download = av_frame_alloc();
    ಯದಿ (!sw_frame || !hw_frame || !download) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    sw_frame->format = fmt;
    sw_frame->width  = 64;
    sw_frame->height = 64;
    ret = av_frame_get_buffer(sw_frame, 0);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;
    ಯದಿ (flip_upload)
        vflip(sw_frame, desc);

    {
        ಪೂರ್ಣಾಙ್ಕ linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(sw_frame->data) && sw_frame->data[i]; i++) {
            ಪೂರ್ಣಾಙ್ಕ shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            ಪೂರ್ಣಾಙ್ಕ h = AV_CEIL_RSHIFT(64, shift);

            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ y = 0; y < h; y++)
                ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ x = 0; x < linesizes[i]; x++)
                    sw_frame->data[i][y * sw_frame->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    download->format = fmt;
    download->width  = 64;
    download->height = 64;
    ret = av_frame_get_buffer(download, 0);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;
    ಯದಿ (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_data(download, hw_frame, 0);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    {
        ಪೂರ್ಣಾಙ್ಕ linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(download->data) && download->data[i]; i++) {
            ಪೂರ್ಣಾಙ್ಕ shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            ಪೂರ್ಣಾಙ್ಕ h = AV_CEIL_RSHIFT(64, shift);

            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ y = 0; y < h; y++) {
                ಯದಿ (memcmp(sw_frame->data[i] + y * sw_frame->linesize[i],
                           download->data[i] + y * download->linesize[i],
                           linesizes[i])) {
                    printf("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    ಗಚ್ಛ fail;
                }
            }
        }
    }

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ atomic_int source_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
ಸ್ಥಿರ ಶೂನ್ಯ CUDAAPI hold_stream(CUstream stream, CUresult status, ಶೂನ್ಯ *opaque)
{
    int64_t start = av_gettime_relative();
    ಯಾವತ್ (!atomic_load(&source_overwritten) && av_gettime_relative() - start < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_source_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->data)->hwctx;
    CudaFunctions *cu = hwctx->internal->cuda_dl;
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_frame = av_frame_alloc(), *hw_frame = av_frame_alloc();
    AVFrame *download = av_frame_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    ಪೂರ್ಣಾಙ್ಕ ret = AVERROR(ENOMEM);

    ಯದಿ (!frames_ref || !sw_frame || !hw_frame || !download)
        ಗಚ್ಛ fail;

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->width     = 64;
    hwfc->height    = 64;
    ಯದಿ ((ret = av_hwframe_ctx_init(frames_ref)) < 0 ||
        (ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0)) < 0)
        ಗಚ್ಛ fail;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ ಮೌಲ್ಯ = 0x11; ಮೌಲ್ಯ <= 0x22; ಮೌಲ್ಯ += 0x11) {
        av_frame_unref(sw_frame);
        sw_frame->format = AV_PIX_FMT_GRAY8;
        sw_frame->width  = 64;
        sw_frame->height = 64;
        ಯದಿ ((ret = av_hwframe_get_transfer_buffer(frames_ref, sw_frame)) < 0)
            ಗಚ್ಛ fail;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ y = 0; y < 64; y++)
            memset(sw_frame->data[0] + y * sw_frame->linesize[0], ಮೌಲ್ಯ, 64);
        ಯದಿ (ಮೌಲ್ಯ == 0x22) {
            atomic_store(&source_overwritten, 1);
            ಭಙ್ಗ;
        }

        ret = AVERROR_EXTERNAL;
        ಯದಿ (cu->cu_Ctx_ತಳ್ಳು_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            ಗಚ್ಛ fail;
        ಯದಿ (cu->cuStreamAddCallback(hwctx->stream, hold_stream, ರಿಕ್ತ, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_ತೆಗೆ_Current(&dummy);
        ಯದಿ (ret < 0)
            ಗಚ್ಛ fail;

        ಯದಿ ((ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0)) < 0)
            ಗಚ್ಛ fail;
    }

    ಯದಿ ((ret = av_hwframe_transfer_data(download, hw_frame, 0)) < 0)
        ಗಚ್ಛ fail;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->data[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    ಪ್ರತ್ಯಾಗಮ ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ test_rejected(AVBufferRef *device_ref, ಗಣನಾ AVPixelFormat fmt)
{
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (!frames_ref)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->width     = 64;
    hwfc->height    = 64;

    /* Init is expected to fail; silence the resulting error log. */
    av_log_set_level(AV_LOG_QUIET);
    ret = av_hwframe_ctx_init(frames_ref);
    av_log_set_level(AV_LOG_INFO);

    av_buffer_unref(&frames_ref);

    ಪ್ರತ್ಯಾಗಮ ret >= 0 ? AVERROR(EINVAL) : 0;
}

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    AVBufferRef *device_ref = ರಿಕ್ತ;
    ಗಣನಾ AVPixelFormat fmt;
    ಪೂರ್ಣಾಙ್ಕ ret, failures = 0, total = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, ರಿಕ್ತ, ರಿಕ್ತ, 0);
    ಯದಿ (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        fprintf(stderr, "No CUDA device available, skipping.\n");
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಪ್ರತಿ (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        ಯದಿ (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            ಅನುವರ್ತ;

        total++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        ಯದಿ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            ಯದಿ (test_rejected(device_ref, fmt) < 0) {
                printf("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } ಅನ್ಯಥಾ {
            ret = 0;
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            ಯದಿ (ret < 0) {
                printf("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    total++;
    ret = test_source_reuse(device_ref);
    ಯದಿ (ret < 0) {
        printf("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_buffer_unref(&device_ref);

    ಯದಿ (failures)
        printf("%d / %d tests failed.\n", failures, total);
    ಅನ್ಯಥಾ
        printf("%d tests passed.\n", total);

    ಪ್ರತ್ಯಾಗಮ !!failures;
}
