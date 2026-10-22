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

#અન્તર્ભાવ <inttypes.h>
#અન્તર્ભાવ <stdatomic.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "libavutil/adler32.h"
#અન્તર્ભાવ "libavutil/hwcontext.h"
#અન્તર્ભાવ "libavutil/hwcontext_cuda_internal.h"
#અન્તર્ભાવ "libavutil/imgutils.h"
#અન્તર્ભાવ "libavutil/log.h"
#અન્તર્ભાવ "libavutil/mem.h"
#અન્તર્ભાવ "libavutil/pixdesc.h"
#અન્તર્ભાવ "libavutil/pixfmt.h"
#અન્તર્ભાવ "libavutil/time.h"

સ્થિર શૂન્ય vflip(AVFrame *frame, અચલ AVPixFmtDescriptor *desc)
{
    માટે (પૂર્ણાંક i = 0; i < FF_ARRAY_ELEMS(frame->data) && frame->data[i]; i++) {
        પૂર્ણાંક shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        frame->data[i]    += (AV_CEIL_RSHIFT(frame->height, shift) - 1) * frame->linesize[i];
        frame->linesize[i] = -frame->linesize[i];
    }
}

સ્થિર પૂર્ણાંક test_format(AVBufferRef *device_ref, ગણના AVPixelFormat fmt,
                       પૂર્ણાંક flip_upload, પૂર્ણાંક flip_download)
{
    AVBufferRef *frames_ref = ખાલી;
    AVHWFramesContext *hwfc;
    AVFrame *sw_frame = ખાલી, *hw_frame = ખાલી, *download = ખાલી;
    અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    પૂર્ણાંક ret;

    frames_ref = av_hwframe_ctx_alloc(device_ref);
    જો (!frames_ref) {
        ret = AVERROR(ENOMEM);
        જાઓ fail;
    }

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->width     = 64;
    hwfc->height    = 64;

    ret = av_hwframe_ctx_init(frames_ref);
    જો (ret < 0)
        જાઓ fail;

    sw_frame = av_frame_alloc();
    hw_frame = av_frame_alloc();
    download = av_frame_alloc();
    જો (!sw_frame || !hw_frame || !download) {
        ret = AVERROR(ENOMEM);
        જાઓ fail;
    }

    sw_frame->format = fmt;
    sw_frame->width  = 64;
    sw_frame->height = 64;
    ret = av_frame_get_buffer(sw_frame, 0);
    જો (ret < 0)
        જાઓ fail;
    જો (flip_upload)
        vflip(sw_frame, desc);

    {
        પૂર્ણાંક linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        માટે (પૂર્ણાંક i = 0; i < FF_ARRAY_ELEMS(sw_frame->data) && sw_frame->data[i]; i++) {
            પૂર્ણાંક shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            પૂર્ણાંક h = AV_CEIL_RSHIFT(64, shift);

            માટે (પૂર્ણાંક y = 0; y < h; y++)
                માટે (પૂર્ણાંક x = 0; x < linesizes[i]; x++)
                    sw_frame->data[i][y * sw_frame->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0);
    જો (ret < 0)
        જાઓ fail;

    ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0);
    જો (ret < 0)
        જાઓ fail;

    download->format = fmt;
    download->width  = 64;
    download->height = 64;
    ret = av_frame_get_buffer(download, 0);
    જો (ret < 0)
        જાઓ fail;
    જો (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_data(download, hw_frame, 0);
    જો (ret < 0)
        જાઓ fail;

    {
        પૂર્ણાંક linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        માટે (પૂર્ણાંક i = 0; i < FF_ARRAY_ELEMS(download->data) && download->data[i]; i++) {
            પૂર્ણાંક shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            પૂર્ણાંક h = AV_CEIL_RSHIFT(64, shift);

            માટે (પૂર્ણાંક y = 0; y < h; y++) {
                જો (memcmp(sw_frame->data[i] + y * sw_frame->linesize[i],
                           download->data[i] + y * download->linesize[i],
                           linesizes[i])) {
                    printf("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    જાઓ fail;
                }
            }
        }
    }

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    પાછા ret;
}

સ્થિર atomic_int source_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
સ્થિર શૂન્ય CUDAAPI hold_stream(CUstream stream, CUresult status, શૂન્ય *opaque)
{
    int64_t start = av_gettime_relative();
    જ્યારે (!atomic_load(&source_overwritten) && av_gettime_relative() - start < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
સ્થિર પૂર્ણાંક test_source_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->data)->hwctx;
    CudaFunctions *cu = hwctx->internal->cuda_dl;
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_frame = av_frame_alloc(), *hw_frame = av_frame_alloc();
    AVFrame *download = av_frame_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    પૂર્ણાંક ret = AVERROR(ENOMEM);

    જો (!frames_ref || !sw_frame || !hw_frame || !download)
        જાઓ fail;

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->width     = 64;
    hwfc->height    = 64;
    જો ((ret = av_hwframe_ctx_init(frames_ref)) < 0 ||
        (ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0)) < 0)
        જાઓ fail;

    માટે (પૂર્ણાંક કિંમત = 0x11; કિંમત <= 0x22; કિંમત += 0x11) {
        av_frame_unref(sw_frame);
        sw_frame->format = AV_PIX_FMT_GRAY8;
        sw_frame->width  = 64;
        sw_frame->height = 64;
        જો ((ret = av_hwframe_get_transfer_buffer(frames_ref, sw_frame)) < 0)
            જાઓ fail;
        માટે (પૂર્ણાંક y = 0; y < 64; y++)
            memset(sw_frame->data[0] + y * sw_frame->linesize[0], કિંમત, 64);
        જો (કિંમત == 0x22) {
            atomic_store(&source_overwritten, 1);
            તોડો;
        }

        ret = AVERROR_EXTERNAL;
        જો (cu->cu_Ctx_ધકેલો_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            જાઓ fail;
        જો (cu->cuStreamAddCallback(hwctx->stream, hold_stream, ખાલી, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_કાઢો_Current(&dummy);
        જો (ret < 0)
            જાઓ fail;

        જો ((ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0)) < 0)
            જાઓ fail;
    }

    જો ((ret = av_hwframe_transfer_data(download, hw_frame, 0)) < 0)
        જાઓ fail;
    માટે (પૂર્ણાંક y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->data[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    પાછા ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
સ્થિર પૂર્ણાંક test_rejected(AVBufferRef *device_ref, ગણના AVPixelFormat fmt)
{
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    પૂર્ણાંક ret;

    જો (!frames_ref)
        પાછા AVERROR(ENOMEM);

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

    પાછા ret >= 0 ? AVERROR(EINVAL) : 0;
}

પૂર્ણાંક મુખ્ય(શૂન્ય)
{
    AVBufferRef *device_ref = ખાલી;
    ગણના AVPixelFormat fmt;
    પૂર્ણાંક ret, failures = 0, total = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, ખાલી, ખાલી, 0);
    જો (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        fprintf(stderr, "No CUDA device available, skipping.\n");
        પાછા 0;
    }

    માટે (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        જો (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            ચાલુ;

        total++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        જો (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            જો (test_rejected(device_ref, fmt) < 0) {
                printf("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } નહીંતર {
            ret = 0;
            માટે (પૂર્ણાંક flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            જો (ret < 0) {
                printf("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    total++;
    ret = test_source_reuse(device_ref);
    જો (ret < 0) {
        printf("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_buffer_unref(&device_ref);

    જો (failures)
        printf("%d / %d tests failed.\n", failures, total);
    નહીંતર
        printf("%d tests passed.\n", total);

    પાછા !!failures;
}
