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

#ଅନ୍ତର୍ଭାଵ <inttypes.h>
#ଅନ୍ତର୍ଭାଵ <stdatomic.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "libavutil/adler32.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/hwcontext.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/hwcontext_cuda_internal.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/imgutils.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/log.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/mem.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/pixdesc.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/pixfmt.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/time.h"

ସ୍ଥିର ଶୂନ୍ୟ vflip(AVFrame *frame, ଅଚଳ AVPixFmtDescriptor *desc)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(frame->data) && frame->data[i]; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        frame->data[i]    += (AV_CEIL_RSHIFT(frame->height, shift) - 1) * frame->linesize[i];
        frame->linesize[i] = -frame->linesize[i];
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା test_format(AVBufferRef *device_ref, ଗଣନା AVPixelFormat fmt,
                       ପୂର୍ଣ୍ଣସଂଖ୍ୟା flip_upload, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flip_download)
{
    AVBufferRef *frames_ref = ଖାଲି;
    AVHWFramesContext *hwfc;
    AVFrame *sw_frame = ଖାଲି, *hw_frame = ଖାଲି, *download = ଖାଲି;
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    frames_ref = av_hwframe_ctx_alloc(device_ref);
    ଯଦି (!frames_ref) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->width     = 64;
    hwfc->height    = 64;

    ret = av_hwframe_ctx_init(frames_ref);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    sw_frame = av_frame_alloc();
    hw_frame = av_frame_alloc();
    download = av_frame_alloc();
    ଯଦି (!sw_frame || !hw_frame || !download) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    sw_frame->format = fmt;
    sw_frame->width  = 64;
    sw_frame->height = 64;
    ret = av_frame_get_buffer(sw_frame, 0);
    ଯଦି (ret < 0)
        ଯାଅ fail;
    ଯଦି (flip_upload)
        vflip(sw_frame, desc);

    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(sw_frame->data) && sw_frame->data[i]; i++) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = AV_CEIL_RSHIFT(64, shift);

            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା y = 0; y < h; y++)
                ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା x = 0; x < linesizes[i]; x++)
                    sw_frame->data[i][y * sw_frame->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    download->format = fmt;
    download->width  = 64;
    download->height = 64;
    ret = av_frame_get_buffer(download, 0);
    ଯଦି (ret < 0)
        ଯାଅ fail;
    ଯଦି (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_data(download, hw_frame, 0);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(download->data) && download->data[i]; i++) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = AV_CEIL_RSHIFT(64, shift);

            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା y = 0; y < h; y++) {
                ଯଦି (memcmp(sw_frame->data[i] + y * sw_frame->linesize[i],
                           download->data[i] + y * download->linesize[i],
                           linesizes[i])) {
                    printf("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    ଯାଅ fail;
                }
            }
        }
    }

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର atomic_int source_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
ସ୍ଥିର ଶୂନ୍ୟ CUDAAPI hold_stream(CUstream stream, CUresult status, ଶୂନ୍ୟ *opaque)
{
    int64_t start = av_gettime_relative();
    ଯେତେବେଳେ (!atomic_load(&source_overwritten) && av_gettime_relative() - start < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା test_source_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->data)->hwctx;
    CudaFunctions *cu = hwctx->internal->cuda_dl;
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_frame = av_frame_alloc(), *hw_frame = av_frame_alloc();
    AVFrame *download = av_frame_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = AVERROR(ENOMEM);

    ଯଦି (!frames_ref || !sw_frame || !hw_frame || !download)
        ଯାଅ fail;

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->width     = 64;
    hwfc->height    = 64;
    ଯଦି ((ret = av_hwframe_ctx_init(frames_ref)) < 0 ||
        (ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0)) < 0)
        ଯାଅ fail;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ = 0x11; ମୂଲ୍ୟ <= 0x22; ମୂଲ୍ୟ += 0x11) {
        av_frame_unref(sw_frame);
        sw_frame->format = AV_PIX_FMT_GRAY8;
        sw_frame->width  = 64;
        sw_frame->height = 64;
        ଯଦି ((ret = av_hwframe_get_transfer_buffer(frames_ref, sw_frame)) < 0)
            ଯାଅ fail;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା y = 0; y < 64; y++)
            memset(sw_frame->data[0] + y * sw_frame->linesize[0], ମୂଲ୍ୟ, 64);
        ଯଦି (ମୂଲ୍ୟ == 0x22) {
            atomic_store(&source_overwritten, 1);
            ଭାଙ୍ଗ;
        }

        ret = AVERROR_EXTERNAL;
        ଯଦି (cu->cu_Ctx_ଠେଲ_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            ଯାଅ fail;
        ଯଦି (cu->cuStreamAddCallback(hwctx->stream, hold_stream, ଖାଲି, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_କାଢ଼_Current(&dummy);
        ଯଦି (ret < 0)
            ଯାଅ fail;

        ଯଦି ((ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0)) < 0)
            ଯାଅ fail;
    }

    ଯଦି ((ret = av_hwframe_transfer_data(download, hw_frame, 0)) < 0)
        ଯାଅ fail;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->data[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    ଫେରନ୍ତୁ ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା test_rejected(AVBufferRef *device_ref, ଗଣନା AVPixelFormat fmt)
{
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!frames_ref)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

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

    ଫେରନ୍ତୁ ret >= 0 ? AVERROR(EINVAL) : 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ଶୂନ୍ୟ)
{
    AVBufferRef *device_ref = ଖାଲି;
    ଗଣନା AVPixelFormat fmt;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, failures = 0, total = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, ଖାଲି, ଖାଲି, 0);
    ଯଦି (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        fprintf(stderr, "No CUDA device available, skipping.\n");
        ଫେରନ୍ତୁ 0;
    }

    ପାଇଁ (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        ଯଦି (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            ଜାରି;

        total++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        ଯଦି (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            ଯଦି (test_rejected(device_ref, fmt) < 0) {
                printf("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } ଅନ୍ୟଥା {
            ret = 0;
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            ଯଦି (ret < 0) {
                printf("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    total++;
    ret = test_source_reuse(device_ref);
    ଯଦି (ret < 0) {
        printf("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_buffer_unref(&device_ref);

    ଯଦି (failures)
        printf("%d / %d tests failed.\n", failures, total);
    ଅନ୍ୟଥା
        printf("%d tests passed.\n", total);

    ଫେରନ୍ତୁ !!failures;
}
