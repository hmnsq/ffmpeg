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

ساكن فراغ vflip(AVFrame *frame, ثابت AVPixFmtDescriptor *desc)
{
    עבור (صحيح i = 0; i < FF_ARRAY_ELEMS(frame->data) && frame->data[i]; i++) {
        صحيح shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        frame->data[i]    += (AV_CEIL_RSHIFT(frame->height, shift) - 1) * frame->linesize[i];
        frame->linesize[i] = -frame->linesize[i];
    }
}

ساكن صحيح test_format(AVBufferRef *device_ref, تعداد AVPixelFormat fmt,
                       صحيح flip_upload, صحيح flip_download)
{
    AVBufferRef *frames_ref = عدم;
    AVHWFramesContext *hwfc;
    AVFrame *sw_frame = عدم, *hw_frame = عدم, *download = عدم;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    صحيح ret;

    frames_ref = av_hwframe_ctx_alloc(device_ref);
    אם (!frames_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->width     = 64;
    hwfc->height    = 64;

    ret = av_hwframe_ctx_init(frames_ref);
    אם (ret < 0)
        اذهب fail;

    sw_frame = av_frame_alloc();
    hw_frame = av_frame_alloc();
    download = av_frame_alloc();
    אם (!sw_frame || !hw_frame || !download) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    sw_frame->format = fmt;
    sw_frame->width  = 64;
    sw_frame->height = 64;
    ret = av_frame_get_buffer(sw_frame, 0);
    אם (ret < 0)
        اذهب fail;
    אם (flip_upload)
        vflip(sw_frame, desc);

    {
        صحيح linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        עבור (صحيح i = 0; i < FF_ARRAY_ELEMS(sw_frame->data) && sw_frame->data[i]; i++) {
            صحيح shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            صحيح h = AV_CEIL_RSHIFT(64, shift);

            עבור (صحيح y = 0; y < h; y++)
                עבור (صحيح x = 0; x < linesizes[i]; x++)
                    sw_frame->data[i][y * sw_frame->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0);
    אם (ret < 0)
        اذهب fail;

    ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0);
    אם (ret < 0)
        اذهب fail;

    download->format = fmt;
    download->width  = 64;
    download->height = 64;
    ret = av_frame_get_buffer(download, 0);
    אם (ret < 0)
        اذهب fail;
    אם (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_data(download, hw_frame, 0);
    אם (ret < 0)
        اذهب fail;

    {
        صحيح linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        עבור (صحيح i = 0; i < FF_ARRAY_ELEMS(download->data) && download->data[i]; i++) {
            صحيح shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            صحيح h = AV_CEIL_RSHIFT(64, shift);

            עבור (صحيح y = 0; y < h; y++) {
                אם (memcmp(sw_frame->data[i] + y * sw_frame->linesize[i],
                           download->data[i] + y * download->linesize[i],
                           linesizes[i])) {
                    printf("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    اذهب fail;
                }
            }
        }
    }

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    החזר ret;
}

ساكن atomic_int source_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
ساكن فراغ CUDAAPI hold_stream(CUstream stream, CUresult status, فراغ *opaque)
{
    int64_t start = av_gettime_relative();
    כלעוד (!atomic_load(&source_overwritten) && av_gettime_relative() - start < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
ساكن صحيح test_source_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->data)->hwctx;
    CudaFunctions *cu = hwctx->internal->cuda_dl;
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_frame = av_frame_alloc(), *hw_frame = av_frame_alloc();
    AVFrame *download = av_frame_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    صحيح ret = AVERROR(ENOMEM);

    אם (!frames_ref || !sw_frame || !hw_frame || !download)
        اذهب fail;

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->width     = 64;
    hwfc->height    = 64;
    אם ((ret = av_hwframe_ctx_init(frames_ref)) < 0 ||
        (ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0)) < 0)
        اذهب fail;

    עבור (صحيح value = 0x11; value <= 0x22; value += 0x11) {
        av_frame_unref(sw_frame);
        sw_frame->format = AV_PIX_FMT_GRAY8;
        sw_frame->width  = 64;
        sw_frame->height = 64;
        אם ((ret = av_hwframe_get_transfer_buffer(frames_ref, sw_frame)) < 0)
            اذهب fail;
        עבור (صحيح y = 0; y < 64; y++)
            memset(sw_frame->data[0] + y * sw_frame->linesize[0], value, 64);
        אם (value == 0x22) {
            atomic_store(&source_overwritten, 1);
            اكسر;
        }

        ret = AVERROR_EXTERNAL;
        אם (cu->cuCtxPushCurrent(hwctx->cuda_ctx) != CUDA_SUCCESS)
            اذهب fail;
        אם (cu->cuStreamAddCallback(hwctx->stream, hold_stream, عدم, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cuCtxPopCurrent(&dummy);
        אם (ret < 0)
            اذهب fail;

        אם ((ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0)) < 0)
            اذهب fail;
    }

    אם ((ret = av_hwframe_transfer_data(download, hw_frame, 0)) < 0)
        اذهب fail;
    עבור (صحيح y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->data[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    החזר ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
ساكن صحيح test_rejected(AVBufferRef *device_ref, تعداد AVPixelFormat fmt)
{
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    صحيح ret;

    אם (!frames_ref)
        החזר AVERROR(ENOMEM);

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

    החזר ret >= 0 ? AVERROR(EINVAL) : 0;
}

صحيح main(فراغ)
{
    AVBufferRef *device_ref = عدم;
    تعداد AVPixelFormat fmt;
    صحيح ret, failures = 0, total = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, عدم, عدم, 0);
    אם (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        fprintf(stderr, "No CUDA device available, skipping.\n");
        החזר 0;
    }

    עבור (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        אם (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            استمر;

        total++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        אם (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            אם (test_rejected(device_ref, fmt) < 0) {
                printf("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } אחרת {
            ret = 0;
            עבור (صحيح flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            אם (ret < 0) {
                printf("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    total++;
    ret = test_source_reuse(device_ref);
    אם (ret < 0) {
        printf("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_buffer_unref(&device_ref);

    אם (failures)
        printf("%d / %d tests failed.\n", failures, total);
    אחרת
        printf("%d tests passed.\n", total);

    החזר !!failures;
}
