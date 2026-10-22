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

#അന്തര്ഭാവ <inttypes.h>
#അന്തര്ഭാവ <stdatomic.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "libavutil/adler32.h"
#അന്തര്ഭാവ "libavutil/hwcontext.h"
#അന്തര്ഭാവ "libavutil/hwcontext_cuda_internal.h"
#അന്തര്ഭാവ "libavutil/imgutils.h"
#അന്തര്ഭാവ "libavutil/log.h"
#അന്തര്ഭാവ "libavutil/mem.h"
#അന്തര്ഭാവ "libavutil/pixdesc.h"
#അന്തര്ഭാവ "libavutil/pixfmt.h"
#അന്തര്ഭാവ "libavutil/time.h"

സ്ഥിതം ശൂന്യം vflip(AVFrame *frame, സ്ഥിരം AVPixFmtDescriptor *desc)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(frame->data) && frame->data[i]; i++) {
        പൂർണ്ണസംഖ്യ shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        frame->data[i]    += (AV_CEIL_RSHIFT(frame->height, shift) - 1) * frame->linesize[i];
        frame->linesize[i] = -frame->linesize[i];
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ test_format(AVBufferRef *device_ref, എണ്ണൽ AVPixelFormat fmt,
                       പൂർണ്ണസംഖ്യ flip_upload, പൂർണ്ണസംഖ്യ flip_download)
{
    AVBufferRef *frames_ref = ശൂന്യ;
    AVHWFramesContext *hwfc;
    AVFrame *sw_frame = ശൂന്യ, *hw_frame = ശൂന്യ, *download = ശൂന്യ;
    സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    പൂർണ്ണസംഖ്യ ret;

    frames_ref = av_hwframe_ctx_alloc(device_ref);
    എങ്കിൽ (!frames_ref) {
        ret = AVERROR(ENOMEM);
        പോകുക fail;
    }

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->width     = 64;
    hwfc->height    = 64;

    ret = av_hwframe_ctx_init(frames_ref);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    sw_frame = av_frame_alloc();
    hw_frame = av_frame_alloc();
    download = av_frame_alloc();
    എങ്കിൽ (!sw_frame || !hw_frame || !download) {
        ret = AVERROR(ENOMEM);
        പോകുക fail;
    }

    sw_frame->format = fmt;
    sw_frame->width  = 64;
    sw_frame->height = 64;
    ret = av_frame_get_buffer(sw_frame, 0);
    എങ്കിൽ (ret < 0)
        പോകുക fail;
    എങ്കിൽ (flip_upload)
        vflip(sw_frame, desc);

    {
        പൂർണ്ണസംഖ്യ linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(sw_frame->data) && sw_frame->data[i]; i++) {
            പൂർണ്ണസംഖ്യ shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            പൂർണ്ണസംഖ്യ h = AV_CEIL_RSHIFT(64, shift);

            വേണ്ടി (പൂർണ്ണസംഖ്യ y = 0; y < h; y++)
                വേണ്ടി (പൂർണ്ണസംഖ്യ x = 0; x < linesizes[i]; x++)
                    sw_frame->data[i][y * sw_frame->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    download->format = fmt;
    download->width  = 64;
    download->height = 64;
    ret = av_frame_get_buffer(download, 0);
    എങ്കിൽ (ret < 0)
        പോകുക fail;
    എങ്കിൽ (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_data(download, hw_frame, 0);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    {
        പൂർണ്ണസംഖ്യ linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(download->data) && download->data[i]; i++) {
            പൂർണ്ണസംഖ്യ shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            പൂർണ്ണസംഖ്യ h = AV_CEIL_RSHIFT(64, shift);

            വേണ്ടി (പൂർണ്ണസംഖ്യ y = 0; y < h; y++) {
                എങ്കിൽ (memcmp(sw_frame->data[i] + y * sw_frame->linesize[i],
                           download->data[i] + y * download->linesize[i],
                           linesizes[i])) {
                    printf("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    പോകുക fail;
                }
            }
        }
    }

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    തിരികെ ret;
}

സ്ഥിതം atomic_int source_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
സ്ഥിതം ശൂന്യം CUDAAPI hold_stream(CUstream stream, CUresult status, ശൂന്യം *opaque)
{
    int64_t start = av_gettime_relative();
    ആകുമ്പോൾ (!atomic_load(&source_overwritten) && av_gettime_relative() - start < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
സ്ഥിതം പൂർണ്ണസംഖ്യ test_source_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->data)->hwctx;
    CudaFunctions *cu = hwctx->internal->cuda_dl;
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_frame = av_frame_alloc(), *hw_frame = av_frame_alloc();
    AVFrame *download = av_frame_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    പൂർണ്ണസംഖ്യ ret = AVERROR(ENOMEM);

    എങ്കിൽ (!frames_ref || !sw_frame || !hw_frame || !download)
        പോകുക fail;

    hwfc = (AVHWFramesContext *)frames_ref->data;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->width     = 64;
    hwfc->height    = 64;
    എങ്കിൽ ((ret = av_hwframe_ctx_init(frames_ref)) < 0 ||
        (ret = av_hwframe_get_buffer(frames_ref, hw_frame, 0)) < 0)
        പോകുക fail;

    വേണ്ടി (പൂർണ്ണസംഖ്യ മൂല്യം = 0x11; മൂല്യം <= 0x22; മൂല്യം += 0x11) {
        av_frame_unref(sw_frame);
        sw_frame->format = AV_PIX_FMT_GRAY8;
        sw_frame->width  = 64;
        sw_frame->height = 64;
        എങ്കിൽ ((ret = av_hwframe_get_transfer_buffer(frames_ref, sw_frame)) < 0)
            പോകുക fail;
        വേണ്ടി (പൂർണ്ണസംഖ്യ y = 0; y < 64; y++)
            memset(sw_frame->data[0] + y * sw_frame->linesize[0], മൂല്യം, 64);
        എങ്കിൽ (മൂല്യം == 0x22) {
            atomic_store(&source_overwritten, 1);
            നിർത്തുക;
        }

        ret = AVERROR_EXTERNAL;
        എങ്കിൽ (cu->cu_Ctx_തള്ളുക_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            പോകുക fail;
        എങ്കിൽ (cu->cuStreamAddCallback(hwctx->stream, hold_stream, ശൂന്യ, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_എടുക്കുക_Current(&dummy);
        എങ്കിൽ (ret < 0)
            പോകുക fail;

        എങ്കിൽ ((ret = av_hwframe_transfer_data(hw_frame, sw_frame, 0)) < 0)
            പോകുക fail;
    }

    എങ്കിൽ ((ret = av_hwframe_transfer_data(download, hw_frame, 0)) < 0)
        പോകുക fail;
    വേണ്ടി (പൂർണ്ണസംഖ്യ y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->data[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_buffer_unref(&frames_ref);
    തിരികെ ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
സ്ഥിതം പൂർണ്ണസംഖ്യ test_rejected(AVBufferRef *device_ref, എണ്ണൽ AVPixelFormat fmt)
{
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (!frames_ref)
        തിരികെ AVERROR(ENOMEM);

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

    തിരികെ ret >= 0 ? AVERROR(EINVAL) : 0;
}

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    AVBufferRef *device_ref = ശൂന്യ;
    എണ്ണൽ AVPixelFormat fmt;
    പൂർണ്ണസംഖ്യ ret, failures = 0, total = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, ശൂന്യ, ശൂന്യ, 0);
    എങ്കിൽ (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        fprintf(stderr, "No CUDA device available, skipping.\n");
        തിരികെ 0;
    }

    വേണ്ടി (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        എങ്കിൽ (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            തുടരുക;

        total++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        എങ്കിൽ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            എങ്കിൽ (test_rejected(device_ref, fmt) < 0) {
                printf("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } അല്ലെങ്കിൽ {
            ret = 0;
            വേണ്ടി (പൂർണ്ണസംഖ്യ flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            എങ്കിൽ (ret < 0) {
                printf("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    total++;
    ret = test_source_reuse(device_ref);
    എങ്കിൽ (ret < 0) {
        printf("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_buffer_unref(&device_ref);

    എങ്കിൽ (failures)
        printf("%d / %d tests failed.\n", failures, total);
    അല്ലെങ്കിൽ
        printf("%d tests passed.\n", total);

    തിരികെ !!failures;
}
