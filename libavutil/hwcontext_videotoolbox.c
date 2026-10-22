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

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ <VideoToolbox/VideoToolbox.h>

#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "buffer_internal.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_videotoolbox.h"
#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixel_ಬಫರ್_Pool_Ref pool;
} VTFramesContext;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    uint32_t cv_fmt;
    bool ತುಂಬಿದ_range;
    ಎಣಿಕೆ AVPixelFormat pix_fmt;
} cv_pix_fmts[] = {
    { kCVPixelFormatType_420YpCbCr8Planar,              false, AV_PIX_FMT_YUV420P },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr8_Planar_ತುಂಬಿದ_Range,     true,  AV_PIX_FMT_YUV420P },
    { kCVPixelFormatType_422YpCbCr8,                    false, AV_PIX_FMT_UYVY422 },
    { kCVPixelFormatType_32BGRA,                        true,  AV_PIX_FMT_BGRA },
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ k_CFCore_Foundation_ಆವೃತ್ತಿ_Number10_7
    { kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV12 },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr8_Bi_Planar_ತುಂಬಿದ_Range,   true,  AV_PIX_FMT_NV12 },
    { kCVPixelFormatType_4444AYpCbCr8,                  false, AV_PIX_FMT_AYUV },
    { kCVPixelFormatType_4444AYpCbCr16,                 false, AV_PIX_FMT_AYUV64 },
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr10_Bi_Planar_ತುಂಬಿದ_Range,  true,  AV_PIX_FMT_P010 },
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { k_CVPixel_Format_Type_422_Yp_Cb_Cr8_Bi_Planar_ತುಂಬಿದ_Range,   true,  AV_PIX_FMT_NV16 },
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { k_CVPixel_Format_Type_422_Yp_Cb_Cr10_Bi_Planar_ತುಂಬಿದ_Range,  true,  AV_PIX_FMT_P210 },
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { k_CVPixel_Format_Type_444_Yp_Cb_Cr8_Bi_Planar_ತುಂಬಿದ_Range,   true,  AV_PIX_FMT_NV24 },
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { k_CVPixel_Format_Type_444_Yp_Cb_Cr10_Bi_Planar_ತುಂಬಿದ_Range,  true,  AV_PIX_FMT_P410 },
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#ಆದರೆ_ಅಂತ್ಯ
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat supported_formats[] = {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ k_CFCore_Foundation_ಆವೃತ್ತಿ_Number10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#ಆದರೆ_ಅಂತ್ಯ
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#ಆದರೆ_ಅಂತ್ಯ
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_ಚೌಕಟ್ಟುಗಳು_get_constraints(AVHWDeviceContext *ctx,
                                     ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    ಪೂರ್ಣಾಂಕ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    ಗಾತ್ರ(*constraints->valid_sw_formats));
    ಆದರೆ (!constraints->valid_sw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ಗಾತ್ರ(*constraints->valid_hw_formats));
    ಆದರೆ (!constraints->valid_hw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ಹಿಂತಿರುಗಿ 0;
}

ಎಣಿಕೆ AVPixelFormat av_map_videotoolbox_format_ಗಮ್ಯ_pixfmt(uint32_t cv_fmt)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        ಆದರೆ (cv_pix_fmts[i].cv_fmt == cv_fmt)
            ಹಿಂತಿರುಗಿ cv_pix_fmts[i].pix_fmt;
    }
    ಹಿಂತಿರುಗಿ AV_PIX_FMT_NONE;
}

ಸ್ಥಿರ uint32_t vt_format_from_pixfmt(ಎಣಿಕೆ AVPixelFormat pix_fmt,
                                      ಎಣಿಕೆ AVColorRange range)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        ಆದರೆ (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            ಪೂರ್ಣಾಂಕ ತುಂಬಿದ_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            ಆದರೆ (range == AVCOL_RANGE_UNSPECIFIED)
                ಹಿಂತಿರುಗಿ cv_pix_fmts[i].cv_fmt;

            ಆದರೆ (cv_pix_fmts[i].ತುಂಬಿದ_range == ತುಂಬಿದ_range)
                ಹಿಂತಿರುಗಿ cv_pix_fmts[i].cv_fmt;
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(ಎಣಿಕೆ AVPixelFormat pix_fmt)
{
    ಹಿಂತಿರುಗಿ av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(ಎಣಿಕೆ AVPixelFormat pix_fmt, bool ತುಂಬಿದ_range)
{
    ಹಿಂತಿರುಗಿ vt_format_from_pixfmt(pix_fmt, ತುಂಬಿದ_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef ಗುಣಲಕ್ಷಣಗಳು, iosurface_properties;

    ಗುಣಲಕ್ಷಣಗಳು = CFDictionaryCreateMutable(
        ಖಾಲಿ,
        2,
        &k_CFType_Dictionary_ಕೀಲಿ_Call_Backs,
        &k_CFType_Dictionary_ಮೌಲ್ಯ_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(ಖಾಲಿ, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_ಗಣ_ಮೌಲ್ಯ(
        ಗುಣಲಕ್ಷಣಗಳು,
        k_CVPixel_ಬಫರ್_Pixel_Format_Type_ಕೀಲಿ,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        ಖಾಲಿ,
        0,
        &k_CFType_Dictionary_ಕೀಲಿ_Call_Backs,
        &k_CFType_Dictionary_ಮೌಲ್ಯ_Call_Backs);
    CFDictionary_ಗಣ_ಮೌಲ್ಯ(ಗುಣಲಕ್ಷಣಗಳು, k_CVPixel_ಬಫರ್_IOSurface_Properties_ಕೀಲಿ, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(ಖಾಲಿ, kCFNumberSInt32Type, &ctx->ಅಗಲ);
    h = CFNumberCreate(ಖಾಲಿ, kCFNumberSInt32Type, &ctx->ಎತ್ತರ);
    CFDictionary_ಗಣ_ಮೌಲ್ಯ(ಗುಣಲಕ್ಷಣಗಳು, k_CVPixel_ಬಫರ್_ಅಗಲ_ಕೀಲಿ, w);
    CFDictionary_ಗಣ_ಮೌಲ್ಯ(ಗುಣಲಕ್ಷಣಗಳು, k_CVPixel_ಬಫರ್_ಎತ್ತರ_ಕೀಲಿ, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixel_ಬಫರ್_Pool_Create(
        ಖಾಲಿ,
        ಖಾಲಿ,
        ಗುಣಲಕ್ಷಣಗಳು,
        &fctx->pool);
    CFRelease(ಗುಣಲಕ್ಷಣಗಳು);

    ಆದರೆ (err == kCVReturnSuccess)
        ಹಿಂತಿರುಗಿ 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    ಹಿಂತಿರುಗಿ AVERROR_EXTERNAL;
}

ಸ್ಥಿರ ಶೂನ್ಯ videotoolbox_ಬಫರ್_release(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    CVPixel_ಬಫರ್_Release((CVPixel_ಬಫರ್_Ref)ದತ್ತಾಂಶ);
}

ಸ್ಥಿರ AVBufferRef *vt_pool_alloc_ಬಫರ್(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    CVPixel_ಬಫರ್_Ref pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixel_ಬಫರ್_Pool_Create_Pixel_ಬಫರ್(
        ಖಾಲಿ,
        fctx->pool,
        &pixbuf
    );
    ಆದರೆ (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    buf = av_ಬಫರ್_create((uint8_t *)pixbuf, ಗಾತ್ರ_2,
                           videotoolbox_ಬಫರ್_release, ಖಾಲಿ, 0);
    ಆದರೆ (!buf) {
        CVPixel_ಬಫರ್_Release(pixbuf);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ buf;
}

ಸ್ಥಿರ ಶೂನ್ಯ vt_ಚೌಕಟ್ಟುಗಳು_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    ಆದರೆ (fctx->pool) {
        CVPixel_ಬಫರ್_Pool_Release(fctx->pool);
        fctx->pool = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_ಚೌಕಟ್ಟುಗಳು_init(AVHWFramesContext *ctx)
{
    ಪೂರ್ಣಾಂಕ i, ret;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ಆದರೆ (ctx->sw_format == supported_formats[i])
            ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    ಆದರೆ (!ctx->pool) {
        ffhwframesctx(ctx)->pool_ಆಂತರಿಕ = av_ಬಫರ್_pool_init2(
                ಗಾತ್ರ(CVPixel_ಬಫರ್_Ref), ctx, vt_pool_alloc_ಬಫರ್, ಖಾಲಿ);
        ಆದರೆ (!ffhwframesctx(ctx)->pool_ಆಂತರಿಕ)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_get_ಬಫರ್(AVHWFramesContext *ctx, AVFrame *ಚೌಕಟ್ಟು)
{
    ಚೌಕಟ್ಟು->buf[0] = av_ಬಫರ್_pool_get(ctx->pool);
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0])
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[3] = ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ;
    ಚೌಕಟ್ಟು->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    ಚೌಕಟ್ಟು->ಅಗಲ   = ctx->ಅಗಲ;
    ಚೌಕಟ್ಟು->ಎತ್ತರ  = ctx->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                   ಎಣಿಕೆ AVPixelFormat **formats)
{
    ಎಣಿಕೆ AVPixelFormat *fmts = av_malloc_array(2, ಗಾತ್ರ(*fmts));
    ಆದರೆ (!fmts)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixel_ಬಫರ್_Ref pixbuf = (CVPixel_ಬಫರ್_Ref)hwmap->ಮೂಲ->ದತ್ತಾಂಶ[3];

    CVPixel_ಬಫರ್_Unlock_ತಳ_ವಿಳಾಸ(pixbuf, (uintptr_t)hwmap->priv);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_pixbuf_ಗಣ_par(ಶೂನ್ಯ *log_ctx,
                             CVPixel_ಬಫರ್_Ref pixbuf, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    CFMutableDictionaryRef par = ಖಾಲಿ;
    CFNumberRef ಅಂಕೆ = ಖಾಲಿ, den = ಖಾಲಿ;
    AVRational avpar = src->sample_aspect_ಅನುಪಾತ;

    ಆದರೆ (avpar.ಅಂಕೆ == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_ಬಫರ್_Pixel_Aspect_ಅನುಪಾತ_ಕೀಲಿ);
        ಹಿಂತಿರುಗಿ 0;
    }

    av_reduce(&avpar.ಅಂಕೆ, &avpar.den,
                avpar.ಅಂಕೆ, avpar.den,
                0xFFFFFFFF);

    ಅಂಕೆ = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.ಅಂಕೆ);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_ಕೀಲಿ_Call_Backs,
                                    &k_CFType_Dictionary_ಮೌಲ್ಯ_Call_Backs);

    ಆದರೆ (!par || !ಅಂಕೆ || !den) {
        ಆದರೆ (par) CFRelease(par);
        ಆದರೆ (ಅಂಕೆ) CFRelease(ಅಂಕೆ);
        ಆದರೆ (den) CFRelease(den);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    CFDictionary_ಗಣ_ಮೌಲ್ಯ(
        par,
        k_CVImage_ಬಫರ್_Pixel_Aspect_ಅನುಪಾತ_Horizontal_Spacing_ಕೀಲಿ,
        ಅಂಕೆ);
    CFDictionary_ಗಣ_ಮೌಲ್ಯ(
        par,
        k_CVImage_ಬಫರ್_Pixel_Aspect_ಅನುಪಾತ_Vertical_Spacing_ಕೀಲಿ,
        den);

    CVBuffer_ಗಣ_Attachment(
        pixbuf,
        k_CVImage_ಬಫರ್_Pixel_Aspect_ಅನುಪಾತ_ಕೀಲಿ,
        par,
        k_CVAttachment_ಬಹುಲಕ_Should_Propagate
    );

    CFRelease(par);
    CFRelease(ಅಂಕೆ);
    CFRelease(den);

    ಹಿಂತಿರುಗಿ 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(ಎಣಿಕೆ AVChromaLocation loc)
{
    ಆಯ್ಕೆ (loc) {
    ಸ್ಥಿತಿ AVCHROMA_LOC_ಎಡ:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Chroma_Location_ಎಡ;
    ಸ್ಥಿತಿ AVCHROMA_LOC_CENTER:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Chroma_Location_Center;
    ಸ್ಥಿತಿ AVCHROMA_LOC_ತುದಿ:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Chroma_Location_ತುದಿ;
    ಸ್ಥಿತಿ AVCHROMA_LOC_BOTTOM:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Chroma_Location_Bottom;
    ಸ್ಥಿತಿ AVCHROMA_LOC_TOPLEFT:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Chroma_Location_ತುದಿ_ಎಡ;
    ಸ್ಥಿತಿ AVCHROMA_LOC_BOTTOMLEFT:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Chroma_Location_Bottom_ಎಡ;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_pixbuf_ಗಣ_chromaloc(ಶೂನ್ಯ *log_ctx,
                                   CVPixel_ಬಫರ್_Ref pixbuf, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    ಆದರೆ (loc) {
        CVBuffer_ಗಣ_Attachment(
            pixbuf,
            k_CVImage_ಬಫರ್_Chroma_Location_ತುದಿ_ಕ್ಷೇತ್ರ_ಕೀಲಿ,
            loc,
            k_CVAttachment_ಬಹುಲಕ_Should_Propagate);
    } ಇಲ್ಲದಿದ್ದರೆ
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_ಬಫರ್_Chroma_Location_ತುದಿ_ಕ್ಷೇತ್ರ_ಕೀಲಿ);

    ಹಿಂತಿರುಗಿ 0;
}

CFStringRef av_map_videotoolbox_color_ಮಾತೃಕೆ_from_av(ಎಣಿಕೆ AVColorSpace space)
{
    ಆಯ್ಕೆ (space) {
    ಸ್ಥಿತಿ AVCOL_SPC_BT2020_CL:
    ಸ್ಥಿತಿ AVCOL_SPC_BT2020_NCL:
#ಆದರೆ HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        ಆದರೆ (__builtin_available(macOS 10.11, iOS 9, *))
            ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_YCb_Cr_ಮಾತೃಕೆ_ITU_R_2020;
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ CFSTR("ITU_R_2020");
    ಸ್ಥಿತಿ AVCOL_SPC_BT470BG:
    ಸ್ಥಿತಿ AVCOL_SPC_SMPTE170M:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_YCb_Cr_ಮಾತೃಕೆ_ITU_R_601_4;
    ಸ್ಥಿತಿ AVCOL_SPC_BT709:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_YCb_Cr_ಮಾತೃಕೆ_ITU_R_709_2;
    ಸ್ಥಿತಿ AVCOL_SPC_SMPTE240M:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_YCb_Cr_ಮಾತೃಕೆ_SMPTE_240_M_1995;
    ಪೂರ್ವನಿಯೋಜಿತ:
#ಆದರೆ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ಆದರೆ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ಹಿಂತಿರುಗಿ CVYCb_Cr_ಮಾತೃಕೆ_Get_String_For_Integer_ಸಂಕೇತ_ಬಿಂದು(space);
        av_fallthrough;
#ಆದರೆ_ಅಂತ್ಯ
    ಸ್ಥಿತಿ AVCOL_SPC_UNSPECIFIED:
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(ಎಣಿಕೆ AVColorPrimaries pri)
{
    ಆಯ್ಕೆ (pri) {
    ಸ್ಥಿತಿ AVCOL_PRI_BT2020:
#ಆದರೆ HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        ಆದರೆ (__builtin_available(macOS 10.11, iOS 9, *))
            ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Color_Primaries_ITU_R_2020;
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ CFSTR("ITU_R_2020");
    ಸ್ಥಿತಿ AVCOL_PRI_BT709:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Color_Primaries_ITU_R_709_2;
    ಸ್ಥಿತಿ AVCOL_PRI_SMPTE170M:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Color_Primaries_SMPTE_C;
    ಸ್ಥಿತಿ AVCOL_PRI_BT470BG:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Color_Primaries_EBU_3213;
    ಪೂರ್ವನಿಯೋಜಿತ:
#ಆದರೆ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ಆದರೆ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ಹಿಂತಿರುಗಿ CVColor_Primaries_Get_String_For_Integer_ಸಂಕೇತ_ಬಿಂದು(pri);
        av_fallthrough;
#ಆದರೆ_ಅಂತ್ಯ
    ಸ್ಥಿತಿ AVCOL_PRI_UNSPECIFIED:
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(ಎಣಿಕೆ AVColorTransferCharacteristic trc)
{

    ಆಯ್ಕೆ (trc) {
    ಸ್ಥಿತಿ AVCOL_TRC_SMPTE2084:
#ಆದರೆ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        ಆದರೆ (__builtin_available(macOS 10.13, iOS 11, *))
            ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Transfer_Function_SMPTE_ST_2084_PQ;
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ CFSTR("SMPTE_ST_2084_PQ");
    ಸ್ಥಿತಿ AVCOL_TRC_BT2020_10:
    ಸ್ಥಿತಿ AVCOL_TRC_BT2020_12:
#ಆದರೆ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        ಆದರೆ (__builtin_available(macOS 10.11, iOS 9, *))
            ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Transfer_Function_ITU_R_2020;
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ CFSTR("ITU_R_2020");
    ಸ್ಥಿತಿ AVCOL_TRC_BT709:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Transfer_Function_ITU_R_709_2;
    ಸ್ಥಿತಿ AVCOL_TRC_SMPTE240M:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Transfer_Function_SMPTE_240_M_1995;
    ಸ್ಥಿತಿ AVCOL_TRC_SMPTE428:
#ಆದರೆ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        ಆದರೆ (__builtin_available(macOS 10.12, iOS 10, *))
            ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Transfer_Function_SMPTE_ST_428_1;
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ CFSTR("SMPTE_ST_428_1");
    ಸ್ಥಿತಿ AVCOL_TRC_ARIB_STD_B67:
#ಆದರೆ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ಆದರೆ (__builtin_available(macOS 10.13, iOS 11, *))
            ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Transfer_Function_ITU_R_2100_HLG;
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ CFSTR("ITU_R_2100_HLG");
    ಸ್ಥಿತಿ AVCOL_TRC_GAMMA22:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Transfer_Function_Use_Gamma;
    ಸ್ಥಿತಿ AVCOL_TRC_GAMMA28:
        ಹಿಂತಿರುಗಿ k_CVImage_ಬಫರ್_Transfer_Function_Use_Gamma;
    ಪೂರ್ವನಿಯೋಜಿತ:
#ಆದರೆ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ಆದರೆ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ಹಿಂತಿರುಗಿ CVTransfer_Function_Get_String_For_Integer_ಸಂಕೇತ_ಬಿಂದು(trc);
        av_fallthrough;
#ಆದರೆ_ಅಂತ್ಯ
    ಸ್ಥಿತಿ AVCOL_TRC_UNSPECIFIED:
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
ಸ್ಥಿರ CFDictionaryRef vt_cv_ಬಫರ್_copy_attachments(CVBufferRef ಬಫರ್,
                                                     CVAttachment_ಬಹುಲಕ attachment_ಬಹುಲಕ)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #ಆದರೆ (ಗುರಿ_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (ಗುರಿ_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (ಗುರಿ_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        ಆದರೆ (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            ಹಿಂತಿರುಗಿ CVBufferCopyAttachments(ಬಫರ್, attachment_ಬಹುಲಕ);
    #ಆದರೆ_ಅಂತ್ಯ

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #ಆದರೆ (ಗುರಿ_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (ಗುರಿ_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (ಗುರಿ_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(ಬಫರ್, attachment_ಬಹುಲಕ);
        ಹಿಂತಿರುಗಿ (dict) ? CFDictionaryCreateCopy(ಖಾಲಿ, dict) : ಖಾಲಿ;
    #ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ ಖಾಲಿ; // Impossible, just make the compiler happy
    #ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_pixbuf_ಗಣ_colorspace(ಶೂನ್ಯ *log_ctx,
                                    CVPixel_ಬಫರ್_Ref pixbuf, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    CGColorSpaceRef colorspace = ಖಾಲಿ;
    CFStringRef colormatrix = ಖಾಲಿ, colorpri = ಖಾಲಿ, colortrc = ಖಾಲಿ;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_ಮಾತೃಕೆ_from_av(src->colorspace);
    ಆದರೆ (colormatrix)
        CVBuffer_ಗಣ_Attachment(pixbuf, k_CVImage_ಬಫರ್_YCb_Cr_ಮಾತೃಕೆ_ಕೀಲಿ,
            colormatrix, k_CVAttachment_ಬಹುಲಕ_Should_Propagate);
    ಇಲ್ಲದಿದ್ದರೆ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_ಬಫರ್_YCb_Cr_ಮಾತೃಕೆ_ಕೀಲಿ);
        ಆದರೆ (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    ಆದರೆ (colorpri)
        CVBuffer_ಗಣ_Attachment(pixbuf, k_CVImage_ಬಫರ್_Color_Primaries_ಕೀಲಿ,
            colorpri, k_CVAttachment_ಬಹುಲಕ_Should_Propagate);
    ಇಲ್ಲದಿದ್ದರೆ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_ಬಫರ್_Color_Primaries_ಕೀಲಿ);
        ಆದರೆ (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    ಆದರೆ (colortrc)
        CVBuffer_ಗಣ_Attachment(pixbuf, k_CVImage_ಬಫರ್_Transfer_Function_ಕೀಲಿ,
            colortrc, k_CVAttachment_ಬಹುಲಕ_Should_Propagate);
    ಇಲ್ಲದಿದ್ದರೆ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_ಬಫರ್_Transfer_Function_ಕೀಲಿ);
        ಆದರೆ (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    ಆದರೆ (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    ಆದರೆ (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(ಖಾಲಿ, kCFNumberFloat32Type, &gamma);
        CVBuffer_ಗಣ_Attachment(pixbuf, k_CVImage_ಬಫರ್_Gamma_Level_ಕೀಲಿ,
            gamma_level, k_CVAttachment_ಬಹುಲಕ_Should_Propagate);
        CFRelease(gamma_level);
    } ಇಲ್ಲದಿದ್ದರೆ
        CVBufferRemoveAttachment(pixbuf, k_CVImage_ಬಫರ್_Gamma_Level_ಕೀಲಿ);

#ಆದರೆ (ಗುರಿ_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (ಗುರಿ_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    ಆದರೆ (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_ಬಫರ್_copy_attachments(pixbuf, k_CVAttachment_ಬಹುಲಕ_Should_Propagate);

        ಆದರೆ (attachments) {
            colorspace =
                CVImage_ಬಫರ್_Create_Color_Space_From_Attachments(attachments);
            CFRelease(attachments);
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    ಆದರೆ (colorspace) {
        CVBuffer_ಗಣ_Attachment(pixbuf, k_CVImage_ಬಫರ್_CGColor_Space_ಕೀಲಿ,
            colorspace, k_CVAttachment_ಬಹುಲಕ_Should_Propagate);
        CFRelease(colorspace);
    } ಇಲ್ಲದಿದ್ದರೆ
        CVBufferRemoveAttachment(pixbuf, k_CVImage_ಬಫರ್_CGColor_Space_ಕೀಲಿ);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_pixbuf_ಗಣ_attachments(ಶೂನ್ಯ *log_ctx,
                                     CVPixel_ಬಫರ್_Ref pixbuf, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    ಪೂರ್ಣಾಂಕ ret;
    ret = vt_pixbuf_ಗಣ_par(log_ctx, pixbuf, src);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;
    ret = vt_pixbuf_ಗಣ_colorspace(log_ctx, pixbuf, src);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;
    ret = vt_pixbuf_ಗಣ_chromaloc(log_ctx, pixbuf, src);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_vt_pixbuf_ಗಣ_attachments(ಶೂನ್ಯ *log_ctx,
                                 CVPixel_ಬಫರ್_Ref pixbuf, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    ಹಿಂತಿರುಗಿ vt_pixbuf_ಗಣ_attachments(log_ctx, pixbuf, src);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_map_ಚೌಕಟ್ಟು(AVHWFramesContext *ctx, AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src,
                        ಪೂರ್ಣಾಂಕ flags)
{
    CVPixel_ಬಫರ್_Ref pixbuf = (CVPixel_ಬಫರ್_Ref)src->ದತ್ತಾಂಶ[3];
    OSType pixel_format = CVPixel_ಬಫರ್_Get_Pixel_Format_Type(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    ಪೂರ್ಣಾಂಕ ret;
    ಪೂರ್ಣಾಂಕ i;
    ಎಣಿಕೆ AVPixelFormat format;

    format = av_map_videotoolbox_format_ಗಮ್ಯ_pixfmt(pixel_format);
    ಆದರೆ (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಆದರೆ (CVPixel_ಬಫರ್_Get_ಅಗಲ(pixbuf) != ctx->ಅಗಲ ||
        CVPixel_ಬಫರ್_Get_ಎತ್ತರ(pixbuf) != ctx->ಎತ್ತರ) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಆದರೆ (flags == AV_HWFRAME_MAP_READ)
        map_flags = k_CVPixel_ಬಫರ್_ಬೀಗ_Read_Only;

    err = CVPixel_ಬಫರ್_ಬೀಗ_ತಳ_ವಿಳಾಸ(pixbuf, map_flags);
    ಆದರೆ (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಆದರೆ (CVPixel_ಬಫರ್_Is_Planar(pixbuf)) {
        ಪೂರ್ಣಾಂಕ planes = CVPixel_ಬಫರ್_Get_Plane_ಎಣಿಕೆ(pixbuf);
        ಗಾಗಿ (i = 0; i < planes; i++) {
            dst->ದತ್ತಾಂಶ[i]     = CVPixel_ಬಫರ್_Get_ತಳ_ವಿಳಾಸ_ದ_Plane(pixbuf, i);
            dst->linesize[i] = CVPixel_ಬಫರ್_Get_ಬೈಟುಗಳು_ಪ್ರತಿ_ಅಡ್ಡಸಾಲು_ದ_Plane(pixbuf, i);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        dst->ದತ್ತಾಂಶ[0]     = CVPixel_ಬಫರ್_Get_ತಳ_ವಿಳಾಸ(pixbuf);
        dst->linesize[0] = CVPixel_ಬಫರ್_Get_ಬೈಟುಗಳು_ಪ್ರತಿ_ಅಡ್ಡಸಾಲು(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_ಚೌಕಟ್ಟುಗಳು_ctx, dst, src, vt_unmap,
                                (ಶೂನ್ಯ *)(uintptr_t)map_flags);
    ಆದರೆ (ret < 0)
        ಹೋಗು unlock;

    ಹಿಂತಿರುಗಿ 0;

unlock:
    CVPixel_ಬಫರ್_Unlock_ತಳ_ವಿಳಾಸ(pixbuf, map_flags);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_transfer_ದತ್ತಾಂಶ_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಂಕ err;

    ಆದರೆ (dst->ಅಗಲ > hwfc->ಅಗಲ || dst->ಎತ್ತರ > hwfc->ಎತ್ತರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    map = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_ಚೌಕಟ್ಟು(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ಆದರೆ (err)
        ಹೋಗು fail;

    map->ಅಗಲ  = dst->ಅಗಲ;
    map->ಎತ್ತರ = dst->ಎತ್ತರ;

    err = av_ಚೌಕಟ್ಟು_copy(dst, map);
    ಆದರೆ (err)
        ಹೋಗು fail;

    err = 0;
fail:
    av_ಚೌಕಟ್ಟು_free(&map);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ(AVHWFramesContext *hwfc,
                               AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಂಕ err;

    ಆದರೆ (src->ಅಗಲ > hwfc->ಅಗಲ || src->ಎತ್ತರ > hwfc->ಎತ್ತರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    map = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_ಚೌಕಟ್ಟು(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ಆದರೆ (err)
        ಹೋಗು fail;

    map->ಅಗಲ  = src->ಅಗಲ;
    map->ಎತ್ತರ = src->ಎತ್ತರ;

    err = av_ಚೌಕಟ್ಟು_copy(map, src);
    ಆದರೆ (err)
        ಹೋಗು fail;

    err = vt_pixbuf_ಗಣ_attachments(hwfc, (CVPixel_ಬಫರ್_Ref)dst->ದತ್ತಾಂಶ[3], src);
    ಆದರೆ (err)
        ಹೋಗು fail;

    err = 0;
fail:
    av_ಚೌಕಟ್ಟು_free(&map);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ err;

    ಆದರೆ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dst->format != hwfc->sw_format)
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);

    err = vt_map_ಚೌಕಟ್ಟು(hwfc, dst, src, flags);
    ಆದರೆ (err)
        ಹಿಂತಿರುಗಿ err;

    dst->ಅಗಲ  = src->ಅಗಲ;
    dst->ಎತ್ತರ = src->ಎತ್ತರ;

    err = av_ಚೌಕಟ್ಟು_copy_props(dst, src);
    ಆದರೆ (err)
        ಹಿಂತಿರುಗಿ err;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vt_device_create(AVHWDeviceContext *ctx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                            AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    ಆದರೆ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ    = ಗಾತ್ರ(VTFramesContext),

    .device_create        = vt_device_create,
    .ಚೌಕಟ್ಟುಗಳು_init          = vt_ಚೌಕಟ್ಟುಗಳು_init,
    .ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್    = vt_get_ಬಫರ್,
    .ಚೌಕಟ್ಟುಗಳು_get_constraints = vt_ಚೌಕಟ್ಟುಗಳು_get_constraints,
    .ಚೌಕಟ್ಟುಗಳು_uninit        = vt_ಚೌಕಟ್ಟುಗಳು_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ     = vt_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ,
    .transfer_ದತ್ತಾಂಶ_from   = vt_transfer_ದತ್ತಾಂಶ_from,
    .map_from             = vt_map_from,

    .pix_fmts = (ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
