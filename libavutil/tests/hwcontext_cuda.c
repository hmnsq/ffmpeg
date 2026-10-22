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

#అన్తర్భావ <inttypes.h>
#అన్తర్భావ <stdatomic.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/adler32.h"
#అన్తర్భావ "libavutil/hwcontext.h"
#అన్తర్భావ "libavutil/hwcontext_cuda_internal.h"
#అన్తర్భావ "libavutil/imgutils.h"
#అన్తర్భావ "libavutil/log.h"
#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/pixdesc.h"
#అన్తర్భావ "libavutil/pixfmt.h"
#అన్తర్భావ "libavutil/time.h"

స్థిర శూన్య vflip(AVFrame *చట్రం, స్థిరరాశి AVPixFmtDescriptor *desc)
{
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(చట్రం->దత్తాంశం) && చట్రం->దత్తాంశం[i]; i++) {
        పూర్ణాంకం జరుపు = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        చట్రం->దత్తాంశం[i]    += (AV_CEIL_RSHIFT(చట్రం->ఎత్తు, జరుపు) - 1) * చట్రం->linesize[i];
        చట్రం->linesize[i] = -చట్రం->linesize[i];
    }
}

స్థిర పూర్ణాంకం test_format(AVBufferRef *device_ref, గణన AVPixelFormat fmt,
                       పూర్ణాంకం flip_upload, పూర్ణాంకం flip_download)
{
    AVBufferRef *చట్రాలు_ref = ఖాళీ;
    AVHWFramesContext *hwfc;
    AVFrame *sw_చట్రం = ఖాళీ, *hw_చట్రం = ఖాళీ, *download = ఖాళీ;
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    పూర్ణాంకం ret;

    చట్రాలు_ref = av_hwframe_ctx_alloc(device_ref);
    ఒకవేళ (!చట్రాలు_ref) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    hwfc = (AVHWFramesContext *)చట్రాలు_ref->దత్తాంశం;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->వెడల్పు     = 64;
    hwfc->ఎత్తు    = 64;

    ret = av_hwframe_ctx_init(చట్రాలు_ref);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    sw_చట్రం = av_చట్రం_alloc();
    hw_చట్రం = av_చట్రం_alloc();
    download = av_చట్రం_alloc();
    ఒకవేళ (!sw_చట్రం || !hw_చట్రం || !download) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    sw_చట్రం->format = fmt;
    sw_చట్రం->వెడల్పు  = 64;
    sw_చట్రం->ఎత్తు = 64;
    ret = av_చట్రం_get_బఫరు(sw_చట్రం, 0);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;
    ఒకవేళ (flip_upload)
        vflip(sw_చట్రం, desc);

    {
        పూర్ణాంకం linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(sw_చట్రం->దత్తాంశం) && sw_చట్రం->దత్తాంశం[i]; i++) {
            పూర్ణాంకం జరుపు = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            పూర్ణాంకం h = AV_CEIL_RSHIFT(64, జరుపు);

            కొరకు (పూర్ణాంకం y = 0; y < h; y++)
                కొరకు (పూర్ణాంకం x = 0; x < linesizes[i]; x++)
                    sw_చట్రం->దత్తాంశం[i][y * sw_చట్రం->linesize[i] + x] =
                        (uint8_t)(x + y * 3 + i * 17);
        }
    }

    ret = av_hwframe_get_బఫరు(చట్రాలు_ref, hw_చట్రం, 0);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    ret = av_hwframe_transfer_దత్తాంశం(hw_చట్రం, sw_చట్రం, 0);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    download->format = fmt;
    download->వెడల్పు  = 64;
    download->ఎత్తు = 64;
    ret = av_చట్రం_get_బఫరు(download, 0);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;
    ఒకవేళ (flip_download)
        vflip(download, desc);

    ret = av_hwframe_transfer_దత్తాంశం(download, hw_చట్రం, 0);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    {
        పూర్ణాంకం linesizes[4];
        av_image_fill_linesizes(linesizes, fmt, 64);

        కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(download->దత్తాంశం) && download->దత్తాంశం[i]; i++) {
            పూర్ణాంకం జరుపు = (i == 1 || i == 2) && desc ? desc->log2_chroma_h : 0;
            పూర్ణాంకం h = AV_CEIL_RSHIFT(64, జరుపు);

            కొరకు (పూర్ణాంకం y = 0; y < h; y++) {
                ఒకవేళ (memcmp(sw_చట్రం->దత్తాంశం[i] + y * sw_చట్రం->linesize[i],
                           download->దత్తాంశం[i] + y * download->linesize[i],
                           linesizes[i])) {
                    రాయి("fail: %-16s plane %d row %d mismatch\n",
                           av_get_pix_fmt_name(fmt), i, y);
                    ret = AVERROR(EINVAL);
                    వెళ్ళు fail;
                }
            }
        }
    }

fail:
    av_చట్రం_free(&sw_చట్రం);
    av_చట్రం_free(&hw_చట్రం);
    av_చట్రం_free(&download);
    av_బఫరు_unref(&చట్రాలు_ref);
    తిరిగి ret;
}

స్థిర atomic_int ఆధారం_overwritten;

/* Hold the stream until the source was overwritten, at most 100 ms. */
స్థిర శూన్య CUDAAPI hold_ప్రవాహం(CUstream ప్రవాహం, CUresult స్థితి_2, శూన్య *opaque)
{
    int64_t ప్రారంభం = av_gettime_relative();
    అయితే (!atomic_load(&ఆధారం_overwritten) && av_gettime_relative() - ప్రారంభం < 100000);
}

/* Reuse the memory of an uploaded transfer buffer while the stream is still
 * busy, the upload must not see the new contents. */
స్థిర పూర్ణాంకం test_ఆధారం_reuse(AVBufferRef *device_ref)
{
    AVCUDADeviceContext *hwctx = ((AVHWDeviceContext *)device_ref->దత్తాంశం)->hwctx;
    CudaFunctions *cu = hwctx->అంతర్గత->cuda_dl;
    AVBufferRef *చట్రాలు_ref = av_hwframe_ctx_alloc(device_ref);
    AVFrame *sw_చట్రం = av_చట్రం_alloc(), *hw_చట్రం = av_చట్రం_alloc();
    AVFrame *download = av_చట్రం_alloc();
    AVHWFramesContext *hwfc;
    CUcontext dummy;
    AVAdler checksum = 1;
    పూర్ణాంకం ret = AVERROR(ENOMEM);

    ఒకవేళ (!చట్రాలు_ref || !sw_చట్రం || !hw_చట్రం || !download)
        వెళ్ళు fail;

    hwfc = (AVHWFramesContext *)చట్రాలు_ref->దత్తాంశం;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = AV_PIX_FMT_GRAY8;
    hwfc->వెడల్పు     = 64;
    hwfc->ఎత్తు    = 64;
    ఒకవేళ ((ret = av_hwframe_ctx_init(చట్రాలు_ref)) < 0 ||
        (ret = av_hwframe_get_బఫరు(చట్రాలు_ref, hw_చట్రం, 0)) < 0)
        వెళ్ళు fail;

    కొరకు (పూర్ణాంకం విలువ = 0x11; విలువ <= 0x22; విలువ += 0x11) {
        av_చట్రం_unref(sw_చట్రం);
        sw_చట్రం->format = AV_PIX_FMT_GRAY8;
        sw_చట్రం->వెడల్పు  = 64;
        sw_చట్రం->ఎత్తు = 64;
        ఒకవేళ ((ret = av_hwframe_get_transfer_బఫరు(చట్రాలు_ref, sw_చట్రం)) < 0)
            వెళ్ళు fail;
        కొరకు (పూర్ణాంకం y = 0; y < 64; y++)
            memset(sw_చట్రం->దత్తాంశం[0] + y * sw_చట్రం->linesize[0], విలువ, 64);
        ఒకవేళ (విలువ == 0x22) {
            atomic_store(&ఆధారం_overwritten, 1);
            ఆపు;
        }

        ret = AVERROR_EXTERNAL;
        ఒకవేళ (cu->cu_Ctx_నెట్టు_Current(hwctx->cuda_ctx) != CUDA_SUCCESS)
            వెళ్ళు fail;
        ఒకవేళ (cu->cu_ప్రవాహం_కూడు_Callback(hwctx->ప్రవాహం, hold_ప్రవాహం, ఖాళీ, 0) == CUDA_SUCCESS)
            ret = 0;
        cu->cu_Ctx_తీయి_Current(&dummy);
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;

        ఒకవేళ ((ret = av_hwframe_transfer_దత్తాంశం(hw_చట్రం, sw_చట్రం, 0)) < 0)
            వెళ్ళు fail;
    }

    ఒకవేళ ((ret = av_hwframe_transfer_దత్తాంశం(download, hw_చట్రం, 0)) < 0)
        వెళ్ళు fail;
    కొరకు (పూర్ణాంకం y = 0; y < 64; y++)
        checksum = av_adler32_update(checksum,
                                     download->దత్తాంశం[0] + y * download->linesize[0], 64);
    fprintf(stderr, "source reuse checksum: %08"PRIx32"\n", checksum);

fail:
    av_చట్రం_free(&sw_చట్రం);
    av_చట్రం_free(&hw_చట్రం);
    av_చట్రం_free(&download);
    av_బఫరు_unref(&చట్రాలు_ref);
    తిరిగి ret;
}

/* Verify that an unsupported sw_format is refused at init time. Returns 0 when
 * the format is correctly rejected, and an error when it is wrongly accepted. */
స్థిర పూర్ణాంకం test_rejected(AVBufferRef *device_ref, గణన AVPixelFormat fmt)
{
    AVBufferRef *చట్రాలు_ref = av_hwframe_ctx_alloc(device_ref);
    AVHWFramesContext *hwfc;
    పూర్ణాంకం ret;

    ఒకవేళ (!చట్రాలు_ref)
        తిరిగి AVERROR(ENOMEM);

    hwfc = (AVHWFramesContext *)చట్రాలు_ref->దత్తాంశం;
    hwfc->format    = AV_PIX_FMT_CUDA;
    hwfc->sw_format = fmt;
    hwfc->వెడల్పు     = 64;
    hwfc->ఎత్తు    = 64;

    /* Init is expected to fail; silence the resulting error log. */
    av_log_సమితి_level(AV_LOG_QUIET);
    ret = av_hwframe_ctx_init(చట్రాలు_ref);
    av_log_సమితి_level(AV_LOG_INFO);

    av_బఫరు_unref(&చట్రాలు_ref);

    తిరిగి ret >= 0 ? AVERROR(EINVAL) : 0;
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVBufferRef *device_ref = ఖాళీ;
    గణన AVPixelFormat fmt;
    పూర్ణాంకం ret, failures = 0, మొత్తం = 0;

    ret = av_hwdevice_ctx_create(&device_ref, AV_HWDEVICE_TYPE_CUDA, ఖాళీ, ఖాళీ, 0);
    ఒకవేళ (ret < 0) {
        /* CONFIG_CUDA only requires the ffnvcodec headers and a dynamic
         * loader; a FATE host that compiled CUDA support need not have an
         * NVIDIA GPU or usable driver. Skip cleanly in that case so that
         * make fate does not fail for an unavailable test environment. A real
         * transfer mismatch below still returns a nonzero exit status. */
        fprintf(stderr, "No CUDA device available, skipping.\n");
        తిరిగి 0;
    }

    కొరకు (fmt = 0; fmt < AV_PIX_FMT_NB; fmt++) {
        స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
        ఒకవేళ (!desc || (desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            కొనసాగు;

        మొత్తం++;
        /* Palette formats must be refused rather than silently dropping the
         * palette across a transfer; every other format must round-trip. */
        ఒకవేళ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
            ఒకవేళ (test_rejected(device_ref, fmt) < 0) {
                రాయి("fail: %-16s wrongly accepted\n",
                       av_get_pix_fmt_name(fmt));
                failures++;
            }
        } లేకపోతే {
            ret = 0;
            కొరకు (పూర్ణాంకం flip = 0; flip < 4 && ret >= 0; flip++)
                ret = test_format(device_ref, fmt, flip & 1, flip & 2);
            ఒకవేళ (ret < 0) {
                రాయి("fail: %-16s %s\n",
                       av_get_pix_fmt_name(fmt),
                       av_err2str(ret));
                failures++;
            }
        }
    }

    మొత్తం++;
    ret = test_ఆధారం_reuse(device_ref);
    ఒకవేళ (ret < 0) {
        రాయి("fail: source reuse %s\n", av_err2str(ret));
        failures++;
    }

    av_బఫరు_unref(&device_ref);

    ఒకవేళ (failures)
        రాయి("%d / %d tests failed.\n", failures, మొత్తం);
    లేకపోతే
        రాయి("%d tests passed.\n", మొత్తం);

    తిరిగి !!failures;
}
