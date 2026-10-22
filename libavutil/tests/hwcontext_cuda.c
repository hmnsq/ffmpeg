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

#অন্তর্ভাব <inttypes.h>
#অন্তর্ভাব <stdatomic.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "libavutil/adler32.h"
#অন্তর্ভাব "libavutil/hwcontext.h"
#অন্তর্ভাব "libavutil/hwcontext_cuda_internal.h"
#অন্তর্ভাব "libavutil/imgutils.h"
#অন্তর্ভাব "libavutil/log.h"
#অন্তর্ভাব "libavutil/mem.h"
#অন্তর্ভাব "libavutil/pixdesc.h"
#অন্তর্ভাব "libavutil/pixfmt.h"
#অন্তর্ভাব "libavutil/time.h"

স্থির শূন্য vflip(AVFrame *frame, ধ্রুব AVPixFmtDescriptor *desc)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < FF_ARRAY_ELEMS(frame->data) && frame->data[i]; i++) {
        পূর্ণাঙ্ক shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        frame->data[i]    += (AV_CEIL_RSHIFT(frame->height, shift) - 1) * frame->linesize[i];
        frame->linesize[i] = -frame->linesize[i];
    }
}

স্থির পূর্ণাঙ্ক test_format(AVBufferRef *device_ref, গণনা AVPixelFormat fmt,
                       পূর্ণাঙ্ক flip_upload, পূর্ণাঙ্ক flip_download)
{
    AVBufferRef *frames_ref = রিক্ত;
    AVHWFramesContext *hwfc;
    AVFrame *sw_frame = রিক্ত, *hw_frame = রিক্ত, *download = রিক্ত;
    ধ্রুব AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    পূর্ণাঙ্ক ret;

    frames_ref = av_hwframe_ctx_alloc(device_ref);
    যদি (!frames_ref) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->width     = 64;
    hwfc->height    = 64;

    ret = av_hwframe_ctx_init(frames_ref);
    যদি (ret < 0)
        গচ্ছ fail;

    sw_frame = av_frame_alloc();
    hw_frame = av_frame_alloc();
    download = av_frame_alloc();
    যদি (!sw_frame || !hw_frame || !download) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }

    sw_frame->format = fmt;
    sw_frame->width  = 64;
    sw_frame->height = 64;
    ret = av_frame_get_buffer(sw_frame, 0);
    যদি (ret < 0)
        গচ্ছ fail;
    যদি (flip_upload)
        vflip(sw_frame, desc);

    {
        পূর্ণাঙ্ক linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        প্রতি (পূর্ণাঙ্ক i = 0; i < FF_ARRAY_ELEMS(sw_frame->data) && sw_frame->data[i]; i++) {
            পূর্ণাঙ্ক shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            পূর্ণাঙ্ক h = AV_CEIL_RSHIFT(64, shift);

            প্রতি (পূর্ণাঙ্ক y = 0; y < h; y++)
                প্রতি (পূর্ণাঙ্ক x = 0; x < linesizes[i]; x++)
                    sw_frame->data[i][y * sw_frame->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0);
    যদি (ret < 0)
        গচ্ছ fail;

    ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0);
    যদি (ret < 0)
        গচ্ছ fail;

    download->format = fmt;
    download->width  = 64;
    download->height = 64;
    ret = av_frame_get_buffer(download, 0);
    যদি (ret < 0)
        গচ্ছ fail;
    যদি (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_data(download, hw_frame, 0);
    যদি (ret < 0)
        গচ্ছ fail;

    {
        পূর্ণাঙ্ক linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        প্রতি (পূর্ণাঙ্ক i = 0; i < FF_ARRAY_ELEMS(download->data) && download->data[i]; i++) {
            পূর্ণাঙ্ক shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            পূর্ণাঙ্ক h = AV_CEIL_RSHIFT(64, shift);

            প্রতি (পূর্ণাঙ্ক y = 0; y < h; y++) {
                যদি (memcmp(sw_frame->data[i] + y * sw_frame->linesize[i],
                           download->data[i] + y * download->linesize[i],
                           linesizes[i])) {
                    printf("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    গচ্ছ fail;
                }
            }
        }
    }

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    প্রত্যাগম ret;
}

স্থির atomic_int source_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
স্থির শূন্য CUDAAPI hold_stream(CUstream stream, CUresult status, শূন্য *opaque)
{
    int64_t start = av_gettime_relative();
    যাবত্ (!atomic_load(&source_overwritten) && av_gettime_relative() - start < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
স্থির পূর্ণাঙ্ক test_source_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->data)->hwctx;
    CudaFunctions *cu = hwctx->internal->cuda_dl;
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_frame = av_frame_alloc(), *hw_frame = av_frame_alloc();
    AVFrame *download = av_frame_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    পূর্ণাঙ্ক ret = AVERROR(ENOMEM);

    যদি (!frames_ref || !sw_frame || !hw_frame || !download)
        গচ্ছ fail;

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->width     = 64;
    hwfc->height    = 64;
    যদি ((ret = av_hwframe_ctx_init(frames_ref)) < 0 ||
        (ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0)) < 0)
        গচ্ছ fail;

    প্রতি (পূর্ণাঙ্ক মান = 0x11; মান <= 0x22; মান += 0x11) {
        av_frame_unref(sw_frame);
        sw_frame->format = AV_PIX_FMT_GRAY8;
        sw_frame->width  = 64;
        sw_frame->height = 64;
        যদি ((ret = av_hwframe_get_transfer_buffer(frames_ref, sw_frame)) < 0)
            গচ্ছ fail;
        প্রতি (পূর্ণাঙ্ক y = 0; y < 64; y++)
            memset(sw_frame->data[0] + y * sw_frame->linesize[0], মান, 64);
        যদি (মান == 0x22) {
            atomic_store(&source_overwritten, 1);
            ভঙ্গ;
        }

        ret = AVERROR_EXTERNAL;
        যদি (cu->cu_Ctx_ঠেলো_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            গচ্ছ fail;
        যদি (cu->cuStreamAddCallback(hwctx->stream, hold_stream, রিক্ত, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_বের_করো_Current(&dummy);
        যদি (ret < 0)
            গচ্ছ fail;

        যদি ((ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0)) < 0)
            গচ্ছ fail;
    }

    যদি ((ret = av_hwframe_transfer_data(download, hw_frame, 0)) < 0)
        গচ্ছ fail;
    প্রতি (পূর্ণাঙ্ক y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->data[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    প্রত্যাগম ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
স্থির পূর্ণাঙ্ক test_rejected(AVBufferRef *device_ref, গণনা AVPixelFormat fmt)
{
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    পূর্ণাঙ্ক ret;

    যদি (!frames_ref)
        প্রত্যাগম AVERROR(ENOMEM);

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

    প্রত্যাগম ret >= 0 ? AVERROR(EINVAL) : 0;
}

পূর্ণাঙ্ক main(শূন্য)
{
    AVBufferRef *device_ref = রিক্ত;
    গণনা AVPixelFormat fmt;
    পূর্ণাঙ্ক ret, failures = 0, total = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, রিক্ত, রিক্ত, 0);
    যদি (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        fprintf(stderr, "No CUDA device available, skipping.\n");
        প্রত্যাগম 0;
    }

    প্রতি (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        ধ্রুব AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        যদি (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            অনুবর্ত;

        total++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        যদি (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            যদি (test_rejected(device_ref, fmt) < 0) {
                printf("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } অন্যথা {
            ret = 0;
            প্রতি (পূর্ণাঙ্ক flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            যদি (ret < 0) {
                printf("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    total++;
    ret = test_source_reuse(device_ref);
    যদি (ret < 0) {
        printf("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_buffer_unref(&device_ref);

    যদি (failures)
        printf("%d / %d tests failed.\n", failures, total);
    অন্যথা
        printf("%d tests passed.\n", total);

    প্রত্যাগম !!failures;
}
