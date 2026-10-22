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

#समावेश <inttypes.h>
#समावेश <stdatomic.h>
#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "libavutil/adler32.h"
#समावेश "libavutil/hwcontext.h"
#समावेश "libavutil/hwcontext_cuda_internal.h"
#समावेश "libavutil/imgutils.h"
#समावेश "libavutil/log.h"
#समावेश "libavutil/mem.h"
#समावेश "libavutil/pixdesc.h"
#समावेश "libavutil/pixfmt.h"
#समावेश "libavutil/time.h"

अटल व्योम vflip(AVFrame *frame, स्थिर AVPixFmtDescriptor *desc)
{
    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(frame->तथ्य) && frame->तथ्य[i]; i++) {
        पूर्णांक shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        frame->तथ्य[i]    += (AV_CEIL_RSHIFT(frame->height, shift) - 1) * frame->linesize[i];
        frame->linesize[i] = -frame->linesize[i];
    }
}

अटल पूर्णांक test_format(AVBufferRef *device_ref, क्रमागत AVPixelFormat fmt,
                       पूर्णांक flip_upload, पूर्णांक flip_download)
{
    AVBufferRef *frames_ref = शून्य;
    AVHWFramesContext *hwfc;
    AVFrame *sw_frame = शून्य, *hw_frame = शून्य, *download = शून्य;
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    पूर्णांक ret;

    frames_ref = av_hwframe_ctx_alloc(device_ref);
    अगर (!frames_ref) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }

    hwfc = (AVHWFramesContext *)frames_ref->तथ्य;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->width     = 64;
    hwfc->height    = 64;

    ret = av_hwframe_ctx_init(frames_ref);
    अगर (ret < 0)
        जाओ fail;

    sw_frame = av_frame_alloc();
    hw_frame = av_frame_alloc();
    download = av_frame_alloc();
    अगर (!sw_frame || !hw_frame || !download) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }

    sw_frame->format = fmt;
    sw_frame->width  = 64;
    sw_frame->height = 64;
    ret = av_frame_get_बफर(sw_frame, 0);
    अगर (ret < 0)
        जाओ fail;
    अगर (flip_upload)
        vflip(sw_frame, desc);

    {
        पूर्णांक linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(sw_frame->तथ्य) && sw_frame->तथ्य[i]; i++) {
            पूर्णांक shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            पूर्णांक h = AV_CEIL_RSHIFT(64, shift);

            क्रम (पूर्णांक y = 0; y < h; y++)
                क्रम (पूर्णांक x = 0; x < linesizes[i]; x++)
                    sw_frame->तथ्य[i][y * sw_frame->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_बफर(frames_ref, hw_frame, 0);
    अगर (ret < 0)
        जाओ fail;

    ret = av_hwframe_transfer_तथ्य(hw_frame, sw_frame, 0);
    अगर (ret < 0)
        जाओ fail;

    download->format = fmt;
    download->width  = 64;
    download->height = 64;
    ret = av_frame_get_बफर(download, 0);
    अगर (ret < 0)
        जाओ fail;
    अगर (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_तथ्य(download, hw_frame, 0);
    अगर (ret < 0)
        जाओ fail;

    {
        पूर्णांक linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(download->तथ्य) && download->तथ्य[i]; i++) {
            पूर्णांक shift = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            पूर्णांक h = AV_CEIL_RSHIFT(64, shift);

            क्रम (पूर्णांक y = 0; y < h; y++) {
                अगर (स_भेद(sw_frame->तथ्य[i] + y * sw_frame->linesize[i],
                           download->तथ्य[i] + y * download->linesize[i],
                           linesizes[i])) {
                    म_लिखो("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    जाओ fail;
                }
            }
        }
    }

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_बफर_unref(&frames_ref);
    वापस ret;
}

अटल atomic_int source_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
अटल व्योम CUDAAPI hold_stream(CUstream stream, CUresult status, व्योम *opaque)
{
    int64_t start = av_gettime_relative();
    जबतक (!atomic_load(&source_overwritten) && av_gettime_relative() - start < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
अटल पूर्णांक test_source_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->तथ्य)->hwctx;
    CudaFunctions *cu = hwctx->internal->cuda_dl;
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_frame = av_frame_alloc(), *hw_frame = av_frame_alloc();
    AVFrame *download = av_frame_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    पूर्णांक ret = AVERROR(ENOMEM);

    अगर (!frames_ref || !sw_frame || !hw_frame || !download)
        जाओ fail;

    hwfc = (AVHWFramesContext *)frames_ref->तथ्य;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->width     = 64;
    hwfc->height    = 64;
    अगर ((ret = av_hwframe_ctx_init(frames_ref)) < 0 ||
        (ret = av_hwframe_get_बफर(frames_ref, hw_frame, 0)) < 0)
        जाओ fail;

    क्रम (पूर्णांक मूल्य = 0x11; मूल्य <= 0x22; मूल्य += 0x11) {
        av_frame_unref(sw_frame);
        sw_frame->format = AV_PIX_FMT_GRAY8;
        sw_frame->width  = 64;
        sw_frame->height = 64;
        अगर ((ret = av_hwframe_get_transfer_बफर(frames_ref, sw_frame)) < 0)
            जाओ fail;
        क्रम (पूर्णांक y = 0; y < 64; y++)
            स_रखो(sw_frame->तथ्य[0] + y * sw_frame->linesize[0], मूल्य, 64);
        अगर (मूल्य == 0x22) {
            atomic_store(&source_overwritten, 1);
            अवरोध;
        }

        ret = AVERROR_EXTERNAL;
        अगर (cu->cu_Ctx_धकेलो_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            जाओ fail;
        अगर (cu->cuStreamAddCallback(hwctx->stream, hold_stream, शून्य, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_निकालो_Current(&dummy);
        अगर (ret < 0)
            जाओ fail;

        अगर ((ret = av_hwframe_transfer_तथ्य(hw_frame, sw_frame, 0)) < 0)
            जाओ fail;
    }

    अगर ((ret = av_hwframe_transfer_तथ्य(download, hw_frame, 0)) < 0)
        जाओ fail;
    क्रम (पूर्णांक y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->तथ्य[0] + y * download->linesize[0], 64);
    ख_लिखो(मानक_त्रुटि, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_frame_free(&sw_frame);
    av_frame_free(&hw_frame);
    av_frame_free(&download);
    av_बफर_unref(&frames_ref);
    वापस ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
अटल पूर्णांक test_rejected(AVBufferRef *device_ref, क्रमागत AVPixelFormat fmt)
{
    AVBufferRef *frames_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    पूर्णांक ret;

    अगर (!frames_ref)
        वापस AVERROR(ENOMEM);

    hwfc = (AVHWFramesContext *)frames_ref->तथ्य;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->width     = 64;
    hwfc->height    = 64;

    /* Init is expected to fail; silence the resulting error log. */
    av_log_set_level(AV_LOG_QUIET);
    ret = av_hwframe_ctx_init(frames_ref);
    av_log_set_level(AV_LOG_INFO);

    av_बफर_unref(&frames_ref);

    वापस ret >= 0 ? AVERROR(EINVAL) : 0;
}

पूर्णांक मुख्य(व्योम)
{
    AVBufferRef *device_ref = शून्य;
    क्रमागत AVPixelFormat fmt;
    पूर्णांक ret, failures = 0, योग_2 = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, शून्य, शून्य, 0);
    अगर (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        ख_लिखो(मानक_त्रुटि, "No CUDA device available, skipping.\n");
        वापस 0;
    }

    क्रम (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        अगर (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            जारी;

        योग_2++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        अगर (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            अगर (test_rejected(device_ref, fmt) < 0) {
                म_लिखो("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } अन्यथा {
            ret = 0;
            क्रम (पूर्णांक flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            अगर (ret < 0) {
                म_लिखो("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    योग_2++;
    ret = test_source_reuse(device_ref);
    अगर (ret < 0) {
        म_लिखो("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_बफर_unref(&device_ref);

    अगर (failures)
        म_लिखो("%d / %d tests failed.\n", failures, योग_2);
    अन्यथा
        म_लिखो("%d tests passed.\n", योग_2);

    वापस !!failures;
}
