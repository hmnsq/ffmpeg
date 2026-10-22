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

#அந்தர்பாவ <inttypes.h>
#அந்தர்பாவ <stdatomic.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "libavutil/adler32.h"
#அந்தர்பாவ "libavutil/hwcontext.h"
#அந்தர்பாவ "libavutil/hwcontext_cuda_internal.h"
#அந்தர்பாவ "libavutil/imgutils.h"
#அந்தர்பாவ "libavutil/log.h"
#அந்தர்பாவ "libavutil/mem.h"
#அந்தர்பாவ "libavutil/pixdesc.h"
#அந்தர்பாவ "libavutil/pixfmt.h"
#அந்தர்பாவ "libavutil/time.h"

நிலையான வெறுமை vflip(AVFrame *frame, மாறிலி AVPixFmtDescriptor *desc)
{
    க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(frame->data) && frame->data[i]; i++) {
        முழு shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        frame->data[i]    += (AV_CEIL_RSHIFT(frame->height, shift) - 1) * frame->linesize[i];
        frame->linesize[i] = -frame->linesize[i];
    }
}

நிலையான முழு test_format(AVBufferRef *device_ref, எண்ணிக்கை AVPixelFormat fmt,
                       முழு flip_upload, முழு flip_download)
{
    AVBufferRef *frames_ref = வெற்று;
    AVHWFramesContext *hwfc;
    AVFrame *sw_frame = வெற்று, *hw_frame = வெற்று, *download = வெற்று;
    மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    முழு ret;

    frames_ref = av_hwframe_ctx_alloc(device_ref);
    எனில் (!frames_ref) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->width     = 64;
    hwfc->height    = 64;

    ret = av_hwframe_ctx_init(frames_ref);
    எனில் (ret < 0)
        செல் fail;

    sw_frame = av_frame_alloc();
    hw_frame = av_frame_alloc();
    download = av_frame_alloc();
    எனில் (!sw_frame || !hw_frame || !download) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }

    sw_frame->format = fmt;
    sw_frame->width  = 64;
    sw_frame->height = 64;
    ret = av_frame_get_buffer(sw_frame, 0);
    எனில் (ret < 0)
        செல் fail;
    எனில் (flip_upload)
        vflip(sw_frame, desc);

    {
        முழு linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(sw_frame->data) && sw_frame->data[i]; i++) {
            முழு shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            முழு h = AV_CEIL_RSHIFT(64, shift);

            க்கு (முழு y = 0; y < h; y++)
                க்கு (முழு x = 0; x < linesizes[i]; x++)
                    sw_frame->data[i][y * sw_frame->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0);
    எனில் (ret < 0)
        செல் fail;

    ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0);
    எனில் (ret < 0)
        செல் fail;

    download->format = fmt;
    download->width  = 64;
    download->height = 64;
    ret = av_frame_get_buffer(download, 0);
    எனில் (ret < 0)
        செல் fail;
    எனில் (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_data(download, hw_frame, 0);
    எனில் (ret < 0)
        செல் fail;

    {
        முழு linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(download->data) && download->data[i]; i++) {
            முழு shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            முழு h = AV_CEIL_RSHIFT(64, shift);

            க்கு (முழு y = 0; y < h; y++) {
                எனில் (memcmp(sw_frame->data[i] + y * sw_frame->linesize[i],
                           download->data[i] + y * download->linesize[i],
                           linesizes[i])) {
                    printf("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    செல் fail;
                }
            }
        }
    }

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    திரும்பு ret;
}

நிலையான atomic_int source_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
நிலையான வெறுமை CUDAAPI hold_stream(CUstream stream, CUresult status, வெறுமை *opaque)
{
    int64_t start = av_gettime_relative();
    போது (!atomic_load(&source_overwritten) && av_gettime_relative() - start < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
நிலையான முழு test_source_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->data)->hwctx;
    CudaFunctions *cu = hwctx->internal->cuda_dl;
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_frame = av_frame_alloc(), *hw_frame = av_frame_alloc();
    AVFrame *download = av_frame_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    முழு ret = AVERROR(ENOMEM);

    எனில் (!frames_ref || !sw_frame || !hw_frame || !download)
        செல் fail;

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->width     = 64;
    hwfc->height    = 64;
    எனில் ((ret = av_hwframe_ctx_init(frames_ref)) < 0 ||
        (ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0)) < 0)
        செல் fail;

    க்கு (முழு மதிப்பு = 0x11; மதிப்பு <= 0x22; மதிப்பு += 0x11) {
        av_frame_unref(sw_frame);
        sw_frame->format = AV_PIX_FMT_GRAY8;
        sw_frame->width  = 64;
        sw_frame->height = 64;
        எனில் ((ret = av_hwframe_get_transfer_buffer(frames_ref, sw_frame)) < 0)
            செல் fail;
        க்கு (முழு y = 0; y < 64; y++)
            memset(sw_frame->data[0] + y * sw_frame->linesize[0], மதிப்பு, 64);
        எனில் (மதிப்பு == 0x22) {
            atomic_store(&source_overwritten, 1);
            நிறுத்து;
        }

        ret = AVERROR_EXTERNAL;
        எனில் (cu->cu_Ctx_தள்ளு_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            செல் fail;
        எனில் (cu->cuStreamAddCallback(hwctx->stream, hold_stream, வெற்று, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_எடு_Current(&dummy);
        எனில் (ret < 0)
            செல் fail;

        எனில் ((ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0)) < 0)
            செல் fail;
    }

    எனில் ((ret = av_hwframe_transfer_data(download, hw_frame, 0)) < 0)
        செல் fail;
    க்கு (முழு y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->data[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    திரும்பு ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
நிலையான முழு test_rejected(AVBufferRef *device_ref, எண்ணிக்கை AVPixelFormat fmt)
{
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    முழு ret;

    எனில் (!frames_ref)
        திரும்பு AVERROR(ENOMEM);

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

    திரும்பு ret >= 0 ? AVERROR(EINVAL) : 0;
}

முழு முதன்மை(வெறுமை)
{
    AVBufferRef *device_ref = வெற்று;
    எண்ணிக்கை AVPixelFormat fmt;
    முழு ret, failures = 0, total = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, வெற்று, வெற்று, 0);
    எனில் (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        fprintf(stderr, "No CUDA device available, skipping.\n");
        திரும்பு 0;
    }

    க்கு (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        எனில் (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            தொடர்;

        total++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        எனில் (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            எனில் (test_rejected(device_ref, fmt) < 0) {
                printf("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } இல்லையெனில் {
            ret = 0;
            க்கு (முழு flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            எனில் (ret < 0) {
                printf("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    total++;
    ret = test_source_reuse(device_ref);
    எனில் (ret < 0) {
        printf("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_buffer_unref(&device_ref);

    எனில் (failures)
        printf("%d / %d tests failed.\n", failures, total);
    இல்லையெனில்
        printf("%d tests passed.\n", total);

    திரும்பு !!failures;
}
