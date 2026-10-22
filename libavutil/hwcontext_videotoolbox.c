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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ <VideoToolbox/VideoToolbox.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "buffer_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_videotoolbox.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixel_ਬਫਰ_Pool_Ref pool;
} VTFramesContext;

ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
    uint32_t cv_fmt;
    bool ਭਰਿਆ_range;
    ਗਿਣਤੀ AVPixelFormat pix_fmt;
} cv_pix_fmts[] = {
    { kCVPixelFormatType_420YpCbCr8Planar,              false, AV_PIX_FMT_YUV420P },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr8_Planar_ਭਰਿਆ_Range,     true,  AV_PIX_FMT_YUV420P },
    { kCVPixelFormatType_422YpCbCr8,                    false, AV_PIX_FMT_UYVY422 },
    { kCVPixelFormatType_32BGRA,                        true,  AV_PIX_FMT_BGRA },
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ k_CFCore_Foundation_ਸੰਸਕਰਣ_Number10_7
    { kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV12 },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr8_Bi_Planar_ਭਰਿਆ_Range,   true,  AV_PIX_FMT_NV12 },
    { kCVPixelFormatType_4444AYpCbCr8,                  false, AV_PIX_FMT_AYUV },
    { kCVPixelFormatType_4444AYpCbCr16,                 false, AV_PIX_FMT_AYUV64 },
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr10_Bi_Planar_ਭਰਿਆ_Range,  true,  AV_PIX_FMT_P010 },
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { k_CVPixel_Format_Type_422_Yp_Cb_Cr8_Bi_Planar_ਭਰਿਆ_Range,   true,  AV_PIX_FMT_NV16 },
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { k_CVPixel_Format_Type_422_Yp_Cb_Cr10_Bi_Planar_ਭਰਿਆ_Range,  true,  AV_PIX_FMT_P210 },
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { k_CVPixel_Format_Type_444_Yp_Cb_Cr8_Bi_Planar_ਭਰਿਆ_Range,   true,  AV_PIX_FMT_NV24 },
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { k_CVPixel_Format_Type_444_Yp_Cb_Cr10_Bi_Planar_ਭਰਿਆ_Range,  true,  AV_PIX_FMT_P410 },
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#ਜੇ_ਅੰਤ
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

ਸਥਿਰ ਅਚਲ ਗਿਣਤੀ AVPixelFormat supported_formats[] = {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ k_CFCore_Foundation_ਸੰਸਕਰਣ_Number10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#ਜੇ_ਅੰਤ
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#ਜੇ HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#ਜੇ_ਅੰਤ
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

ਸਥਿਰ ਪੂਰਨ vt_ਚੌਖਟੇ_get_constraints(AVHWDeviceContext *ctx,
                                     ਅਚਲ ਖਾਲੀ *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    ਪੂਰਨ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    ਆਕਾਰ(*constraints->valid_sw_formats));
    ਜੇ (!constraints->valid_sw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ਆਕਾਰ(*constraints->valid_hw_formats));
    ਜੇ (!constraints->valid_hw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ਵਾਪਸ 0;
}

ਗਿਣਤੀ AVPixelFormat av_map_videotoolbox_format_ਮੰਜ਼ਿਲ_pixfmt(uint32_t cv_fmt)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        ਜੇ (cv_pix_fmts[i].cv_fmt == cv_fmt)
            ਵਾਪਸ cv_pix_fmts[i].pix_fmt;
    }
    ਵਾਪਸ AV_PIX_FMT_NONE;
}

ਸਥਿਰ uint32_t vt_format_from_pixfmt(ਗਿਣਤੀ AVPixelFormat pix_fmt,
                                      ਗਿਣਤੀ AVColorRange range)
{
    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        ਜੇ (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            ਪੂਰਨ ਭਰਿਆ_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            ਜੇ (range == AVCOL_RANGE_UNSPECIFIED)
                ਵਾਪਸ cv_pix_fmts[i].cv_fmt;

            ਜੇ (cv_pix_fmts[i].ਭਰਿਆ_range == ਭਰਿਆ_range)
                ਵਾਪਸ cv_pix_fmts[i].cv_fmt;
        }
    }

    ਵਾਪਸ 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(ਗਿਣਤੀ AVPixelFormat pix_fmt)
{
    ਵਾਪਸ av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(ਗਿਣਤੀ AVPixelFormat pix_fmt, bool ਭਰਿਆ_range)
{
    ਵਾਪਸ vt_format_from_pixfmt(pix_fmt, ਭਰਿਆ_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

ਸਥਿਰ ਪੂਰਨ vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef ਗੁਣ, iosurface_properties;

    ਗੁਣ = CFDictionaryCreateMutable(
        ਨਿਰਾ,
        2,
        &k_CFType_Dictionary_ਕੁੰਜੀ_Call_Backs,
        &k_CFType_Dictionary_ਮੁੱਲ_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(ਨਿਰਾ, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_ਸੈੱਟ_ਮੁੱਲ(
        ਗੁਣ,
        k_CVPixel_ਬਫਰ_Pixel_Format_Type_ਕੁੰਜੀ,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        ਨਿਰਾ,
        0,
        &k_CFType_Dictionary_ਕੁੰਜੀ_Call_Backs,
        &k_CFType_Dictionary_ਮੁੱਲ_Call_Backs);
    CFDictionary_ਸੈੱਟ_ਮੁੱਲ(ਗੁਣ, k_CVPixel_ਬਫਰ_IOSurface_Properties_ਕੁੰਜੀ, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(ਨਿਰਾ, kCFNumberSInt32Type, &ctx->ਚੌੜਾਈ);
    h = CFNumberCreate(ਨਿਰਾ, kCFNumberSInt32Type, &ctx->ਉਚਾਈ);
    CFDictionary_ਸੈੱਟ_ਮੁੱਲ(ਗੁਣ, k_CVPixel_ਬਫਰ_ਚੌੜਾਈ_ਕੁੰਜੀ, w);
    CFDictionary_ਸੈੱਟ_ਮੁੱਲ(ਗੁਣ, k_CVPixel_ਬਫਰ_ਉਚਾਈ_ਕੁੰਜੀ, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixel_ਬਫਰ_Pool_Create(
        ਨਿਰਾ,
        ਨਿਰਾ,
        ਗੁਣ,
        &fctx->pool);
    CFRelease(ਗੁਣ);

    ਜੇ (err == kCVReturnSuccess)
        ਵਾਪਸ 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    ਵਾਪਸ AVERROR_EXTERNAL;
}

ਸਥਿਰ ਖਾਲੀ videotoolbox_ਬਫਰ_release(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    CVPixel_ਬਫਰ_Release((CVPixel_ਬਫਰ_Ref)ਅੰਕੜੇ);
}

ਸਥਿਰ AVBufferRef *vt_pool_alloc_ਬਫਰ(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    CVPixel_ਬਫਰ_Ref pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixel_ਬਫਰ_Pool_Create_Pixel_ਬਫਰ(
        ਨਿਰਾ,
        fctx->pool,
        &pixbuf
    );
    ਜੇ (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        ਵਾਪਸ ਨਿਰਾ;
    }

    buf = av_ਬਫਰ_create((uint8_t *)pixbuf, ਮਾਪ,
                           videotoolbox_ਬਫਰ_release, ਨਿਰਾ, 0);
    ਜੇ (!buf) {
        CVPixel_ਬਫਰ_Release(pixbuf);
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ buf;
}

ਸਥਿਰ ਖਾਲੀ vt_ਚੌਖਟੇ_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    ਜੇ (fctx->pool) {
        CVPixel_ਬਫਰ_Pool_Release(fctx->pool);
        fctx->pool = ਨਿਰਾ;
    }
}

ਸਥਿਰ ਪੂਰਨ vt_ਚੌਖਟੇ_init(AVHWFramesContext *ctx)
{
    ਪੂਰਨ i, ret;

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ਜੇ (ctx->sw_format == supported_formats[i])
            ਰੋਕੋ;
    }
    ਜੇ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    ਜੇ (!ctx->pool) {
        ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ = av_ਬਫਰ_pool_init2(
                ਆਕਾਰ(CVPixel_ਬਫਰ_Ref), ctx, vt_pool_alloc_ਬਫਰ, ਨਿਰਾ);
        ਜੇ (!ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ)
            ਵਾਪਸ AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ vt_get_ਬਫਰ(AVHWFramesContext *ctx, AVFrame *ਚੌਖਟਾ)
{
    ਚੌਖਟਾ->buf[0] = av_ਬਫਰ_pool_get(ctx->pool);
    ਜੇ (!ਚੌਖਟਾ->buf[0])
        ਵਾਪਸ AVERROR(ENOMEM);

    ਚੌਖਟਾ->ਅੰਕੜੇ[3] = ਚੌਖਟਾ->buf[0]->ਅੰਕੜੇ;
    ਚੌਖਟਾ->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    ਚੌਖਟਾ->ਚੌੜਾਈ   = ctx->ਚੌੜਾਈ;
    ਚੌਖਟਾ->ਉਚਾਈ  = ctx->ਉਚਾਈ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   ਗਿਣਤੀ AVHWFrameTransferDirection dir,
                                   ਗਿਣਤੀ AVPixelFormat **formats)
{
    ਗਿਣਤੀ AVPixelFormat *fmts = av_malloc_array(2, ਆਕਾਰ(*fmts));
    ਜੇ (!fmts)
        ਵਾਪਸ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixel_ਬਫਰ_Ref pixbuf = (CVPixel_ਬਫਰ_Ref)hwmap->ਸਰੋਤ->ਅੰਕੜੇ[3];

    CVPixel_ਬਫਰ_Unlock_ਅਧਾਰ_ਪਤਾ(pixbuf, (uintptr_t)hwmap->priv);
}

ਸਥਿਰ ਪੂਰਨ vt_pixbuf_ਸੈੱਟ_par(ਖਾਲੀ *log_ctx,
                             CVPixel_ਬਫਰ_Ref pixbuf, ਅਚਲ AVFrame *src)
{
    CFMutableDictionaryRef par = ਨਿਰਾ;
    CFNumberRef ਅੰਕ = ਨਿਰਾ, den = ਨਿਰਾ;
    AVRational avpar = src->sample_aspect_ਅਨੁਪਾਤ;

    ਜੇ (avpar.ਅੰਕ == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_ਬਫਰ_Pixel_Aspect_ਅਨੁਪਾਤ_ਕੁੰਜੀ);
        ਵਾਪਸ 0;
    }

    av_reduce(&avpar.ਅੰਕ, &avpar.den,
                avpar.ਅੰਕ, avpar.den,
                0xFFFFFFFF);

    ਅੰਕ = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.ਅੰਕ);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_ਕੁੰਜੀ_Call_Backs,
                                    &k_CFType_Dictionary_ਮੁੱਲ_Call_Backs);

    ਜੇ (!par || !ਅੰਕ || !den) {
        ਜੇ (par) CFRelease(par);
        ਜੇ (ਅੰਕ) CFRelease(ਅੰਕ);
        ਜੇ (den) CFRelease(den);
        ਵਾਪਸ AVERROR(ENOMEM);
    }

    CFDictionary_ਸੈੱਟ_ਮੁੱਲ(
        par,
        k_CVImage_ਬਫਰ_Pixel_Aspect_ਅਨੁਪਾਤ_Horizontal_Spacing_ਕੁੰਜੀ,
        ਅੰਕ);
    CFDictionary_ਸੈੱਟ_ਮੁੱਲ(
        par,
        k_CVImage_ਬਫਰ_Pixel_Aspect_ਅਨੁਪਾਤ_Vertical_Spacing_ਕੁੰਜੀ,
        den);

    CVBuffer_ਸੈੱਟ_Attachment(
        pixbuf,
        k_CVImage_ਬਫਰ_Pixel_Aspect_ਅਨੁਪਾਤ_ਕੁੰਜੀ,
        par,
        k_CVAttachment_ਬਹੁਲਕ_Should_Propagate
    );

    CFRelease(par);
    CFRelease(ਅੰਕ);
    CFRelease(den);

    ਵਾਪਸ 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(ਗਿਣਤੀ AVChromaLocation loc)
{
    ਚੋਣ (loc) {
    ਹਾਲਤ AVCHROMA_LOC_ਖੱਬਾ:
        ਵਾਪਸ k_CVImage_ਬਫਰ_Chroma_Location_ਖੱਬਾ;
    ਹਾਲਤ AVCHROMA_LOC_CENTER:
        ਵਾਪਸ k_CVImage_ਬਫਰ_Chroma_Location_Center;
    ਹਾਲਤ AVCHROMA_LOC_ਸਿਖਰ:
        ਵਾਪਸ k_CVImage_ਬਫਰ_Chroma_Location_ਸਿਖਰ;
    ਹਾਲਤ AVCHROMA_LOC_BOTTOM:
        ਵਾਪਸ k_CVImage_ਬਫਰ_Chroma_Location_Bottom;
    ਹਾਲਤ AVCHROMA_LOC_TOPLEFT:
        ਵਾਪਸ k_CVImage_ਬਫਰ_Chroma_Location_ਸਿਖਰ_ਖੱਬਾ;
    ਹਾਲਤ AVCHROMA_LOC_BOTTOMLEFT:
        ਵਾਪਸ k_CVImage_ਬਫਰ_Chroma_Location_Bottom_ਖੱਬਾ;
    ਮੂਲ:
        ਵਾਪਸ ਨਿਰਾ;
    }
}

ਸਥਿਰ ਪੂਰਨ vt_pixbuf_ਸੈੱਟ_chromaloc(ਖਾਲੀ *log_ctx,
                                   CVPixel_ਬਫਰ_Ref pixbuf, ਅਚਲ AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    ਜੇ (loc) {
        CVBuffer_ਸੈੱਟ_Attachment(
            pixbuf,
            k_CVImage_ਬਫਰ_Chroma_Location_ਸਿਖਰ_ਖੇਤਰ_ਕੁੰਜੀ,
            loc,
            k_CVAttachment_ਬਹੁਲਕ_Should_Propagate);
    } ਨਹੀਂਤਾਂ
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_ਬਫਰ_Chroma_Location_ਸਿਖਰ_ਖੇਤਰ_ਕੁੰਜੀ);

    ਵਾਪਸ 0;
}

CFStringRef av_map_videotoolbox_color_ਮੈਟ੍ਰਿਕਸ_from_av(ਗਿਣਤੀ AVColorSpace space)
{
    ਚੋਣ (space) {
    ਹਾਲਤ AVCOL_SPC_BT2020_CL:
    ਹਾਲਤ AVCOL_SPC_BT2020_NCL:
#ਜੇ HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        ਜੇ (__builtin_available(macOS 10.11, iOS 9, *))
            ਵਾਪਸ k_CVImage_ਬਫਰ_YCb_Cr_ਮੈਟ੍ਰਿਕਸ_ITU_R_2020;
#ਜੇ_ਅੰਤ
        ਵਾਪਸ CFSTR("ITU_R_2020");
    ਹਾਲਤ AVCOL_SPC_BT470BG:
    ਹਾਲਤ AVCOL_SPC_SMPTE170M:
        ਵਾਪਸ k_CVImage_ਬਫਰ_YCb_Cr_ਮੈਟ੍ਰਿਕਸ_ITU_R_601_4;
    ਹਾਲਤ AVCOL_SPC_BT709:
        ਵਾਪਸ k_CVImage_ਬਫਰ_YCb_Cr_ਮੈਟ੍ਰਿਕਸ_ITU_R_709_2;
    ਹਾਲਤ AVCOL_SPC_SMPTE240M:
        ਵਾਪਸ k_CVImage_ਬਫਰ_YCb_Cr_ਮੈਟ੍ਰਿਕਸ_SMPTE_240_M_1995;
    ਮੂਲ:
#ਜੇ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ਜੇ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ਵਾਪਸ CVYCb_Cr_ਮੈਟ੍ਰਿਕਸ_Get_String_For_Integer_ਕੋਡ_ਬਿੰਦੂ(space);
        av_fallthrough;
#ਜੇ_ਅੰਤ
    ਹਾਲਤ AVCOL_SPC_UNSPECIFIED:
        ਵਾਪਸ ਨਿਰਾ;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(ਗਿਣਤੀ AVColorPrimaries pri)
{
    ਚੋਣ (pri) {
    ਹਾਲਤ AVCOL_PRI_BT2020:
#ਜੇ HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        ਜੇ (__builtin_available(macOS 10.11, iOS 9, *))
            ਵਾਪਸ k_CVImage_ਬਫਰ_Color_Primaries_ITU_R_2020;
#ਜੇ_ਅੰਤ
        ਵਾਪਸ CFSTR("ITU_R_2020");
    ਹਾਲਤ AVCOL_PRI_BT709:
        ਵਾਪਸ k_CVImage_ਬਫਰ_Color_Primaries_ITU_R_709_2;
    ਹਾਲਤ AVCOL_PRI_SMPTE170M:
        ਵਾਪਸ k_CVImage_ਬਫਰ_Color_Primaries_SMPTE_C;
    ਹਾਲਤ AVCOL_PRI_BT470BG:
        ਵਾਪਸ k_CVImage_ਬਫਰ_Color_Primaries_EBU_3213;
    ਮੂਲ:
#ਜੇ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ਜੇ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ਵਾਪਸ CVColor_Primaries_Get_String_For_Integer_ਕੋਡ_ਬਿੰਦੂ(pri);
        av_fallthrough;
#ਜੇ_ਅੰਤ
    ਹਾਲਤ AVCOL_PRI_UNSPECIFIED:
        ਵਾਪਸ ਨਿਰਾ;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(ਗਿਣਤੀ AVColorTransferCharacteristic trc)
{

    ਚੋਣ (trc) {
    ਹਾਲਤ AVCOL_TRC_SMPTE2084:
#ਜੇ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        ਜੇ (__builtin_available(macOS 10.13, iOS 11, *))
            ਵਾਪਸ k_CVImage_ਬਫਰ_Transfer_Function_SMPTE_ST_2084_PQ;
#ਜੇ_ਅੰਤ
        ਵਾਪਸ CFSTR("SMPTE_ST_2084_PQ");
    ਹਾਲਤ AVCOL_TRC_BT2020_10:
    ਹਾਲਤ AVCOL_TRC_BT2020_12:
#ਜੇ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        ਜੇ (__builtin_available(macOS 10.11, iOS 9, *))
            ਵਾਪਸ k_CVImage_ਬਫਰ_Transfer_Function_ITU_R_2020;
#ਜੇ_ਅੰਤ
        ਵਾਪਸ CFSTR("ITU_R_2020");
    ਹਾਲਤ AVCOL_TRC_BT709:
        ਵਾਪਸ k_CVImage_ਬਫਰ_Transfer_Function_ITU_R_709_2;
    ਹਾਲਤ AVCOL_TRC_SMPTE240M:
        ਵਾਪਸ k_CVImage_ਬਫਰ_Transfer_Function_SMPTE_240_M_1995;
    ਹਾਲਤ AVCOL_TRC_SMPTE428:
#ਜੇ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        ਜੇ (__builtin_available(macOS 10.12, iOS 10, *))
            ਵਾਪਸ k_CVImage_ਬਫਰ_Transfer_Function_SMPTE_ST_428_1;
#ਜੇ_ਅੰਤ
        ਵਾਪਸ CFSTR("SMPTE_ST_428_1");
    ਹਾਲਤ AVCOL_TRC_ARIB_STD_B67:
#ਜੇ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ਜੇ (__builtin_available(macOS 10.13, iOS 11, *))
            ਵਾਪਸ k_CVImage_ਬਫਰ_Transfer_Function_ITU_R_2100_HLG;
#ਜੇ_ਅੰਤ
        ਵਾਪਸ CFSTR("ITU_R_2100_HLG");
    ਹਾਲਤ AVCOL_TRC_GAMMA22:
        ਵਾਪਸ k_CVImage_ਬਫਰ_Transfer_Function_Use_Gamma;
    ਹਾਲਤ AVCOL_TRC_GAMMA28:
        ਵਾਪਸ k_CVImage_ਬਫਰ_Transfer_Function_Use_Gamma;
    ਮੂਲ:
#ਜੇ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ਜੇ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ਵਾਪਸ CVTransfer_Function_Get_String_For_Integer_ਕੋਡ_ਬਿੰਦੂ(trc);
        av_fallthrough;
#ਜੇ_ਅੰਤ
    ਹਾਲਤ AVCOL_TRC_UNSPECIFIED:
        ਵਾਪਸ ਨਿਰਾ;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
ਸਥਿਰ CFDictionaryRef vt_cv_ਬਫਰ_copy_attachments(CVBufferRef ਬਫਰ,
                                                     CVAttachment_ਬਹੁਲਕ attachment_ਬਹੁਲਕ)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #ਜੇ (ਨਿਸ਼ਾਨਾ_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (ਨਿਸ਼ਾਨਾ_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (ਨਿਸ਼ਾਨਾ_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        ਜੇ (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            ਵਾਪਸ CVBufferCopyAttachments(ਬਫਰ, attachment_ਬਹੁਲਕ);
    #ਜੇ_ਅੰਤ

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #ਜੇ (ਨਿਸ਼ਾਨਾ_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (ਨਿਸ਼ਾਨਾ_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (ਨਿਸ਼ਾਨਾ_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(ਬਫਰ, attachment_ਬਹੁਲਕ);
        ਵਾਪਸ (dict) ? CFDictionaryCreateCopy(ਨਿਰਾ, dict) : ਨਿਰਾ;
    #ਨਹੀਂਤਾਂ
        ਵਾਪਸ ਨਿਰਾ; // Impossible, just make the compiler happy
    #ਜੇ_ਅੰਤ
}

ਸਥਿਰ ਪੂਰਨ vt_pixbuf_ਸੈੱਟ_colorspace(ਖਾਲੀ *log_ctx,
                                    CVPixel_ਬਫਰ_Ref pixbuf, ਅਚਲ AVFrame *src)
{
    CGColorSpaceRef colorspace = ਨਿਰਾ;
    CFStringRef colormatrix = ਨਿਰਾ, colorpri = ਨਿਰਾ, colortrc = ਨਿਰਾ;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_ਮੈਟ੍ਰਿਕਸ_from_av(src->colorspace);
    ਜੇ (colormatrix)
        CVBuffer_ਸੈੱਟ_Attachment(pixbuf, k_CVImage_ਬਫਰ_YCb_Cr_ਮੈਟ੍ਰਿਕਸ_ਕੁੰਜੀ,
            colormatrix, k_CVAttachment_ਬਹੁਲਕ_Should_Propagate);
    ਨਹੀਂਤਾਂ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_ਬਫਰ_YCb_Cr_ਮੈਟ੍ਰਿਕਸ_ਕੁੰਜੀ);
        ਜੇ (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    ਜੇ (colorpri)
        CVBuffer_ਸੈੱਟ_Attachment(pixbuf, k_CVImage_ਬਫਰ_Color_Primaries_ਕੁੰਜੀ,
            colorpri, k_CVAttachment_ਬਹੁਲਕ_Should_Propagate);
    ਨਹੀਂਤਾਂ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_ਬਫਰ_Color_Primaries_ਕੁੰਜੀ);
        ਜੇ (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    ਜੇ (colortrc)
        CVBuffer_ਸੈੱਟ_Attachment(pixbuf, k_CVImage_ਬਫਰ_Transfer_Function_ਕੁੰਜੀ,
            colortrc, k_CVAttachment_ਬਹੁਲਕ_Should_Propagate);
    ਨਹੀਂਤਾਂ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_ਬਫਰ_Transfer_Function_ਕੁੰਜੀ);
        ਜੇ (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    ਜੇ (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    ਨਹੀਂਤਾਂ ਜੇ (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    ਜੇ (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(ਨਿਰਾ, kCFNumberFloat32Type, &gamma);
        CVBuffer_ਸੈੱਟ_Attachment(pixbuf, k_CVImage_ਬਫਰ_Gamma_Level_ਕੁੰਜੀ,
            gamma_level, k_CVAttachment_ਬਹੁਲਕ_Should_Propagate);
        CFRelease(gamma_level);
    } ਨਹੀਂਤਾਂ
        CVBufferRemoveAttachment(pixbuf, k_CVImage_ਬਫਰ_Gamma_Level_ਕੁੰਜੀ);

#ਜੇ (ਨਿਸ਼ਾਨਾ_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (ਨਿਸ਼ਾਨਾ_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    ਜੇ (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_ਬਫਰ_copy_attachments(pixbuf, k_CVAttachment_ਬਹੁਲਕ_Should_Propagate);

        ਜੇ (attachments) {
            colorspace =
                CVImage_ਬਫਰ_Create_Color_Space_From_Attachments(attachments);
            CFRelease(attachments);
        }
    }
#ਜੇ_ਅੰਤ

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    ਜੇ (colorspace) {
        CVBuffer_ਸੈੱਟ_Attachment(pixbuf, k_CVImage_ਬਫਰ_CGColor_Space_ਕੁੰਜੀ,
            colorspace, k_CVAttachment_ਬਹੁਲਕ_Should_Propagate);
        CFRelease(colorspace);
    } ਨਹੀਂਤਾਂ
        CVBufferRemoveAttachment(pixbuf, k_CVImage_ਬਫਰ_CGColor_Space_ਕੁੰਜੀ);

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ vt_pixbuf_ਸੈੱਟ_attachments(ਖਾਲੀ *log_ctx,
                                     CVPixel_ਬਫਰ_Ref pixbuf, ਅਚਲ AVFrame *src)
{
    ਪੂਰਨ ret;
    ret = vt_pixbuf_ਸੈੱਟ_par(log_ctx, pixbuf, src);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;
    ret = vt_pixbuf_ਸੈੱਟ_colorspace(log_ctx, pixbuf, src);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;
    ret = vt_pixbuf_ਸੈੱਟ_chromaloc(log_ctx, pixbuf, src);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_vt_pixbuf_ਸੈੱਟ_attachments(ਖਾਲੀ *log_ctx,
                                 CVPixel_ਬਫਰ_Ref pixbuf, ਅਚਲ AVFrame *src)
{
    ਵਾਪਸ vt_pixbuf_ਸੈੱਟ_attachments(log_ctx, pixbuf, src);
}

ਸਥਿਰ ਪੂਰਨ vt_map_ਚੌਖਟਾ(AVHWFramesContext *ctx, AVFrame *dst, ਅਚਲ AVFrame *src,
                        ਪੂਰਨ flags)
{
    CVPixel_ਬਫਰ_Ref pixbuf = (CVPixel_ਬਫਰ_Ref)src->ਅੰਕੜੇ[3];
    OSType pixel_format = CVPixel_ਬਫਰ_Get_Pixel_Format_Type(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    ਪੂਰਨ ret;
    ਪੂਰਨ i;
    ਗਿਣਤੀ AVPixelFormat format;

    format = av_map_videotoolbox_format_ਮੰਜ਼ਿਲ_pixfmt(pixel_format);
    ਜੇ (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਜੇ (CVPixel_ਬਫਰ_Get_ਚੌੜਾਈ(pixbuf) != ctx->ਚੌੜਾਈ ||
        CVPixel_ਬਫਰ_Get_ਉਚਾਈ(pixbuf) != ctx->ਉਚਾਈ) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਜੇ (flags == AV_HWFRAME_MAP_READ)
        map_flags = k_CVPixel_ਬਫਰ_ਤਾਲਾ_Read_Only;

    err = CVPixel_ਬਫਰ_ਤਾਲਾ_ਅਧਾਰ_ਪਤਾ(pixbuf, map_flags);
    ਜੇ (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਜੇ (CVPixel_ਬਫਰ_Is_Planar(pixbuf)) {
        ਪੂਰਨ planes = CVPixel_ਬਫਰ_Get_Plane_ਗਿਣਤੀ(pixbuf);
        ਲਈ (i = 0; i < planes; i++) {
            dst->ਅੰਕੜੇ[i]     = CVPixel_ਬਫਰ_Get_ਅਧਾਰ_ਪਤਾ_ਦਾ_Plane(pixbuf, i);
            dst->linesize[i] = CVPixel_ਬਫਰ_Get_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_ਪੰਕਤੀ_ਦਾ_Plane(pixbuf, i);
        }
    } ਨਹੀਂਤਾਂ {
        dst->ਅੰਕੜੇ[0]     = CVPixel_ਬਫਰ_Get_ਅਧਾਰ_ਪਤਾ(pixbuf);
        dst->linesize[0] = CVPixel_ਬਫਰ_Get_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_ਪੰਕਤੀ(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_ਚੌਖਟੇ_ctx, dst, src, vt_unmap,
                                (ਖਾਲੀ *)(uintptr_t)map_flags);
    ਜੇ (ret < 0)
        ਜਾਓ unlock;

    ਵਾਪਸ 0;

unlock:
    CVPixel_ਬਫਰ_Unlock_ਅਧਾਰ_ਪਤਾ(pixbuf, map_flags);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ vt_transfer_ਅੰਕੜੇ_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, ਅਚਲ AVFrame *src)
{
    AVFrame *map;
    ਪੂਰਨ err;

    ਜੇ (dst->ਚੌੜਾਈ > hwfc->ਚੌੜਾਈ || dst->ਉਚਾਈ > hwfc->ਉਚਾਈ)
        ਵਾਪਸ AVERROR(EINVAL);

    map = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!map)
        ਵਾਪਸ AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_ਚੌਖਟਾ(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ਜੇ (err)
        ਜਾਓ fail;

    map->ਚੌੜਾਈ  = dst->ਚੌੜਾਈ;
    map->ਉਚਾਈ = dst->ਉਚਾਈ;

    err = av_ਚੌਖਟਾ_copy(dst, map);
    ਜੇ (err)
        ਜਾਓ fail;

    err = 0;
fail:
    av_ਚੌਖਟਾ_free(&map);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ vt_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ(AVHWFramesContext *hwfc,
                               AVFrame *dst, ਅਚਲ AVFrame *src)
{
    AVFrame *map;
    ਪੂਰਨ err;

    ਜੇ (src->ਚੌੜਾਈ > hwfc->ਚੌੜਾਈ || src->ਉਚਾਈ > hwfc->ਉਚਾਈ)
        ਵਾਪਸ AVERROR(EINVAL);

    map = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!map)
        ਵਾਪਸ AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_ਚੌਖਟਾ(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ਜੇ (err)
        ਜਾਓ fail;

    map->ਚੌੜਾਈ  = src->ਚੌੜਾਈ;
    map->ਉਚਾਈ = src->ਉਚਾਈ;

    err = av_ਚੌਖਟਾ_copy(map, src);
    ਜੇ (err)
        ਜਾਓ fail;

    err = vt_pixbuf_ਸੈੱਟ_attachments(hwfc, (CVPixel_ਬਫਰ_Ref)dst->ਅੰਕੜੇ[3], src);
    ਜੇ (err)
        ਜਾਓ fail;

    err = 0;
fail:
    av_ਚੌਖਟਾ_free(&map);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    ਪੂਰਨ err;

    ਜੇ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ਨਹੀਂਤਾਂ ਜੇ (dst->format != hwfc->sw_format)
        ਵਾਪਸ AVERROR(ENOSYS);

    err = vt_map_ਚੌਖਟਾ(hwfc, dst, src, flags);
    ਜੇ (err)
        ਵਾਪਸ err;

    dst->ਚੌੜਾਈ  = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ = src->ਉਚਾਈ;

    err = av_ਚੌਖਟਾ_copy_props(dst, src);
    ਜੇ (err)
        ਵਾਪਸ err;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ vt_device_create(AVHWDeviceContext *ctx, ਅਚਲ ਅੱਖਰ *device,
                            AVDictionary *opts, ਪੂਰਨ flags)
{
    ਜੇ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਵਾਪਸ 0;
}

ਅਚਲ HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .ਚੌਖਟੇ_hwctx_ਮਾਪ    = ਆਕਾਰ(VTFramesContext),

    .device_create        = vt_device_create,
    .ਚੌਖਟੇ_init          = vt_ਚੌਖਟੇ_init,
    .ਚੌਖਟੇ_get_ਬਫਰ    = vt_get_ਬਫਰ,
    .ਚੌਖਟੇ_get_constraints = vt_ਚੌਖਟੇ_get_constraints,
    .ਚੌਖਟੇ_uninit        = vt_ਚੌਖਟੇ_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ     = vt_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ,
    .transfer_ਅੰਕੜੇ_from   = vt_transfer_ਅੰਕੜੇ_from,
    .map_from             = vt_map_from,

    .pix_fmts = (ਅਚਲ ਗਿਣਤੀ AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
