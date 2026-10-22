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

#अन्तर्भाव <inttypes.h>
#अन्तर्भाव <stdatomic.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/adler32.h"
#अन्तर्भाव "libavutil/hwcontext.h"
#अन्तर्भाव "libavutil/hwcontext_cuda_internal.h"
#अन्तर्भाव "libavutil/imgutils.h"
#अन्तर्भाव "libavutil/log.h"
#अन्तर्भाव "libavutil/mem.h"
#अन्तर्भाव "libavutil/pixdesc.h"
#अन्तर्भाव "libavutil/pixfmt.h"
#अन्तर्भाव "libavutil/time.h"

स्थिर शून्य vflip(AVFrame *frame, ध्रुव AVPixFmtDescriptor *desc)
{
    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(frame->data) && frame->data[i]; i++) {
        पूर्णाङ्क shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        frame->data[i]    += (AV_CEIL_RSHIFT(frame->height, shift) - 1) * frame->linesize[i];
        frame->linesize[i] = -frame->linesize[i];
    }
}

स्थिर पूर्णाङ्क test_format(AVBufferRef *device_ref, गणना AVPixelFormat fmt,
                       पूर्णाङ्क flip_upload, पूर्णाङ्क flip_download)
{
    AVBufferRef *frames_ref = रिक्त;
    AVHWFramesContext *hwfc;
    AVFrame *sw_frame = रिक्त, *hw_frame = रिक्त, *download = रिक्त;
    ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    पूर्णाङ्क ret;

    frames_ref = av_hwframe_ctx_alloc(device_ref);
    यदि (!frames_ref) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->width     = 64;
    hwfc->height    = 64;

    ret = av_hwframe_ctx_init(frames_ref);
    यदि (ret < 0)
        गच्छ fail;

    sw_frame = av_frame_alloc();
    hw_frame = av_frame_alloc();
    download = av_frame_alloc();
    यदि (!sw_frame || !hw_frame || !download) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    sw_frame->format = fmt;
    sw_frame->width  = 64;
    sw_frame->height = 64;
    ret = av_frame_get_buffer(sw_frame, 0);
    यदि (ret < 0)
        गच्छ fail;
    यदि (flip_upload)
        vflip(sw_frame, desc);

    {
        पूर्णाङ्क linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(sw_frame->data) && sw_frame->data[i]; i++) {
            पूर्णाङ्क shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            पूर्णाङ्क h = AV_CEIL_RSHIFT(64, shift);

            प्रति (पूर्णाङ्क y = 0; y < h; y++)
                प्रति (पूर्णाङ्क x = 0; x < linesizes[i]; x++)
                    sw_frame->data[i][y * sw_frame->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0);
    यदि (ret < 0)
        गच्छ fail;

    ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0);
    यदि (ret < 0)
        गच्छ fail;

    download->format = fmt;
    download->width  = 64;
    download->height = 64;
    ret = av_frame_get_buffer(download, 0);
    यदि (ret < 0)
        गच्छ fail;
    यदि (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_data(download, hw_frame, 0);
    यदि (ret < 0)
        गच्छ fail;

    {
        पूर्णाङ्क linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(download->data) && download->data[i]; i++) {
            पूर्णाङ्क shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            पूर्णाङ्क h = AV_CEIL_RSHIFT(64, shift);

            प्रति (पूर्णाङ्क y = 0; y < h; y++) {
                यदि (memcmp(sw_frame->data[i] + y * sw_frame->linesize[i],
                           download->data[i] + y * download->linesize[i],
                           linesizes[i])) {
                    printf("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    गच्छ fail;
                }
            }
        }
    }

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    प्रत्यागम ret;
}

स्थिर atomic_int source_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
स्थिर शून्य CUDAAPI hold_stream(CUstream stream, CUresult status, शून्य *opaque)
{
    int64_t start = av_gettime_relative();
    यावत् (!atomic_load(&source_overwritten) && av_gettime_relative() - start < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
स्थिर पूर्णाङ्क test_source_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->data)->hwctx;
    CudaFunctions *cu = hwctx->internal->cuda_dl;
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_frame = av_frame_alloc(), *hw_frame = av_frame_alloc();
    AVFrame *download = av_frame_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    पूर्णाङ्क ret = AVERROR(ENOMEM);

    यदि (!frames_ref || !sw_frame || !hw_frame || !download)
        गच्छ fail;

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->width     = 64;
    hwfc->height    = 64;
    यदि ((ret = av_hwframe_ctx_init(frames_ref)) < 0 ||
        (ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0)) < 0)
        गच्छ fail;

    प्रति (पूर्णाङ्क मूल्य = 0x11; मूल्य <= 0x22; मूल्य += 0x11) {
        av_frame_unref(sw_frame);
        sw_frame->format = AV_PIX_FMT_GRAY8;
        sw_frame->width  = 64;
        sw_frame->height = 64;
        यदि ((ret = av_hwframe_get_transfer_buffer(frames_ref, sw_frame)) < 0)
            गच्छ fail;
        प्रति (पूर्णाङ्क y = 0; y < 64; y++)
            memset(sw_frame->data[0] + y * sw_frame->linesize[0], मूल्य, 64);
        यदि (मूल्य == 0x22) {
            atomic_store(&source_overwritten, 1);
            भङ्ग;
        }

        ret = AVERROR_EXTERNAL;
        यदि (cu->cu_Ctx_धकेलो_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            गच्छ fail;
        यदि (cu->cuStreamAddCallback(hwctx->stream, hold_stream, रिक्त, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_निकालो_Current(&dummy);
        यदि (ret < 0)
            गच्छ fail;

        यदि ((ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0)) < 0)
            गच्छ fail;
    }

    यदि ((ret = av_hwframe_transfer_data(download, hw_frame, 0)) < 0)
        गच्छ fail;
    प्रति (पूर्णाङ्क y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->data[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    प्रत्यागम ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
स्थिर पूर्णाङ्क test_rejected(AVBufferRef *device_ref, गणना AVPixelFormat fmt)
{
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    पूर्णाङ्क ret;

    यदि (!frames_ref)
        प्रत्यागम AVERROR(ENOMEM);

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

    प्रत्यागम ret >= 0 ? AVERROR(EINVAL) : 0;
}

पूर्णाङ्क main(शून्य)
{
    AVBufferRef *device_ref = रिक्त;
    गणना AVPixelFormat fmt;
    पूर्णाङ्क ret, failures = 0, total = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, रिक्त, रिक्त, 0);
    यदि (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        fprintf(stderr, "No CUDA device available, skipping.\n");
        प्रत्यागम 0;
    }

    प्रति (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        यदि (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            अनुवर्त;

        total++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        यदि (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            यदि (test_rejected(device_ref, fmt) < 0) {
                printf("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } अन्यथा {
            ret = 0;
            प्रति (पूर्णाङ्क flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            यदि (ret < 0) {
                printf("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    total++;
    ret = test_source_reuse(device_ref);
    यदि (ret < 0) {
        printf("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_buffer_unref(&device_ref);

    यदि (failures)
        printf("%d / %d tests failed.\n", failures, total);
    अन्यथा
        printf("%d tests passed.\n", total);

    प्रत्यागम !!failures;
}
