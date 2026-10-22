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

#ضمن "config.h"

#ضمن <stdint.h>
#ضمن <string.h>

#ضمن <VideoToolbox/VideoToolbox.h>

#ضمن "buffer.h"
#ضمن "buffer_internal.h"
#ضمن "common.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_internal.h"
#ضمن "hwcontext_videotoolbox.h"
#ضمن "attributes.h"
#ضمن "mem.h"
#ضمن "pixfmt.h"
#ضمن "pixdesc.h"

تعريفنوع بنية VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixel_بفر_Pool_Ref pool;
} VTFramesContext;

ساكن ثابت بنية {
    uint32_t cv_fmt;
    bool ڀريل_range;
    تعداد AVPixelFormat pix_fmt;
} cv_pix_fmts[] = {
    { kCVPixelFormatType_420YpCbCr8Planar,              false, AV_PIX_FMT_YUV420P },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr8_Planar_ڀريل_Range,     true,  AV_PIX_FMT_YUV420P },
    { kCVPixelFormatType_422YpCbCr8,                    false, AV_PIX_FMT_UYVY422 },
    { kCVPixelFormatType_32BGRA,                        true,  AV_PIX_FMT_BGRA },
#جيڪڏهن_وصف_ٿيل k_CFCore_Foundation_نسخو_Number10_7
    { kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV12 },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr8_Bi_Planar_ڀريل_Range,   true,  AV_PIX_FMT_NV12 },
    { kCVPixelFormatType_4444AYpCbCr8,                  false, AV_PIX_FMT_AYUV },
    { kCVPixelFormatType_4444AYpCbCr16,                 false, AV_PIX_FMT_AYUV64 },
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr10_Bi_Planar_ڀريل_Range,  true,  AV_PIX_FMT_P010 },
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { k_CVPixel_Format_Type_422_Yp_Cb_Cr8_Bi_Planar_ڀريل_Range,   true,  AV_PIX_FMT_NV16 },
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { k_CVPixel_Format_Type_422_Yp_Cb_Cr10_Bi_Planar_ڀريل_Range,  true,  AV_PIX_FMT_P210 },
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { k_CVPixel_Format_Type_444_Yp_Cb_Cr8_Bi_Planar_ڀريل_Range,   true,  AV_PIX_FMT_NV24 },
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { k_CVPixel_Format_Type_444_Yp_Cb_Cr10_Bi_Planar_ڀريل_Range,  true,  AV_PIX_FMT_P410 },
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#جيڪڏهن_پورو
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

ساكن ثابت تعداد AVPixelFormat supported_formats[] = {
#جيڪڏهن_وصف_ٿيل k_CFCore_Foundation_نسخو_Number10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#جيڪڏهن_پورو
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#إذا HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#جيڪڏهن_پورو
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#جيڪڏهن_پورو
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

ساكن صحيح vt_چوکٺا_get_constraints(AVHWDeviceContext *ctx,
                                     ثابت فراغ *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    صحيح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    إذا (!constraints->valid_sw_formats)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    إذا (!constraints->valid_hw_formats)
        أرجع AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    أرجع 0;
}

تعداد AVPixelFormat av_map_videotoolbox_format_منزل_pixfmt(uint32_t cv_fmt)
{
    صحيح i;
    لكل (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        إذا (cv_pix_fmts[i].cv_fmt == cv_fmt)
            أرجع cv_pix_fmts[i].pix_fmt;
    }
    أرجع AV_PIX_FMT_NONE;
}

ساكن uint32_t vt_format_from_pixfmt(تعداد AVPixelFormat pix_fmt,
                                      تعداد AVColorRange range)
{
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        إذا (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            صحيح ڀريل_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            إذا (range == AVCOL_RANGE_UNSPECIFIED)
                أرجع cv_pix_fmts[i].cv_fmt;

            إذا (cv_pix_fmts[i].ڀريل_range == ڀريل_range)
                أرجع cv_pix_fmts[i].cv_fmt;
        }
    }

    أرجع 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(تعداد AVPixelFormat pix_fmt)
{
    أرجع av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(تعداد AVPixelFormat pix_fmt, bool ڀريل_range)
{
    أرجع vt_format_from_pixfmt(pix_fmt, ڀريل_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

ساكن صحيح vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef خاصيتون, iosurface_properties;

    خاصيتون = CFDictionaryCreateMutable(
        عدم,
        2,
        &k_CFType_Dictionary_ڪنجي_Call_Backs,
        &k_CFType_Dictionary_قدر_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(عدم, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_سيٽ_قدر(
        خاصيتون,
        k_CVPixel_بفر_Pixel_Format_Type_ڪنجي,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        عدم,
        0,
        &k_CFType_Dictionary_ڪنجي_Call_Backs,
        &k_CFType_Dictionary_قدر_Call_Backs);
    CFDictionary_سيٽ_قدر(خاصيتون, k_CVPixel_بفر_IOSurface_Properties_ڪنجي, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(عدم, kCFNumberSInt32Type, &ctx->ويڪر);
    h = CFNumberCreate(عدم, kCFNumberSInt32Type, &ctx->اوچائي);
    CFDictionary_سيٽ_قدر(خاصيتون, k_CVPixel_بفر_ويڪر_ڪنجي, w);
    CFDictionary_سيٽ_قدر(خاصيتون, k_CVPixel_بفر_اوچائي_ڪنجي, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixel_بفر_Pool_Create(
        عدم,
        عدم,
        خاصيتون,
        &fctx->pool);
    CFRelease(خاصيتون);

    إذا (err == kCVReturnSuccess)
        أرجع 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    أرجع AVERROR_EXTERNAL;
}

ساكن فراغ videotoolbox_بفر_release(فراغ *opaque, uint8_t *معلومات)
{
    CVPixel_بفر_Release((CVPixel_بفر_Ref)معلومات);
}

ساكن AVBufferRef *vt_pool_alloc_بفر(فراغ *opaque, size_t سائيز)
{
    CVPixel_بفر_Ref pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixel_بفر_Pool_Create_Pixel_بفر(
        عدم,
        fctx->pool,
        &pixbuf
    );
    إذا (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        أرجع عدم;
    }

    buf = av_بفر_create((uint8_t *)pixbuf, سائيز,
                           videotoolbox_بفر_release, عدم, 0);
    إذا (!buf) {
        CVPixel_بفر_Release(pixbuf);
        أرجع عدم;
    }
    أرجع buf;
}

ساكن فراغ vt_چوکٺا_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    إذا (fctx->pool) {
        CVPixel_بفر_Pool_Release(fctx->pool);
        fctx->pool = عدم;
    }
}

ساكن صحيح vt_چوکٺا_init(AVHWFramesContext *ctx)
{
    صحيح i, ret;

    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        إذا (ctx->sw_format == supported_formats[i])
            اكسر;
    }
    إذا (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        أرجع AVERROR(ENOSYS);
    }

    إذا (!ctx->pool) {
        ffhwframesctx(ctx)->pool_اندروني = av_بفر_pool_init2(
                حجم(CVPixel_بفر_Ref), ctx, vt_pool_alloc_بفر, عدم);
        إذا (!ffhwframesctx(ctx)->pool_اندروني)
            أرجع AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    إذا (ret < 0)
        أرجع ret;

    أرجع 0;
}

ساكن صحيح vt_get_بفر(AVHWFramesContext *ctx, AVFrame *چوکٺو)
{
    چوکٺو->buf[0] = av_بفر_pool_get(ctx->pool);
    إذا (!چوکٺو->buf[0])
        أرجع AVERROR(ENOMEM);

    چوکٺو->معلومات[3] = چوکٺو->buf[0]->معلومات;
    چوکٺو->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    چوکٺو->ويڪر   = ctx->ويڪر;
    چوکٺو->اوچائي  = ctx->اوچائي;

    أرجع 0;
}

ساكن صحيح vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   تعداد AVHWFrameTransferDirection dir,
                                   تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *fmts = av_malloc_array(2, حجم(*fmts));
    إذا (!fmts)
        أرجع AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    أرجع 0;
}

ساكن فراغ vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixel_بفر_Ref pixbuf = (CVPixel_بفر_Ref)hwmap->ذريعو->معلومات[3];

    CVPixel_بفر_Unlock_بنياد_پتو(pixbuf, (uintptr_t)hwmap->priv);
}

ساكن صحيح vt_pixbuf_سيٽ_par(فراغ *log_ctx,
                             CVPixel_بفر_Ref pixbuf, ثابت AVFrame *src)
{
    CFMutableDictionaryRef par = عدم;
    CFNumberRef انگ = عدم, den = عدم;
    AVRational avpar = src->sample_aspect_تناسب;

    إذا (avpar.انگ == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_بفر_Pixel_Aspect_تناسب_ڪنجي);
        أرجع 0;
    }

    av_reduce(&avpar.انگ, &avpar.den,
                avpar.انگ, avpar.den,
                0xFFFFFFFF);

    انگ = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.انگ);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_ڪنجي_Call_Backs,
                                    &k_CFType_Dictionary_قدر_Call_Backs);

    إذا (!par || !انگ || !den) {
        إذا (par) CFRelease(par);
        إذا (انگ) CFRelease(انگ);
        إذا (den) CFRelease(den);
        أرجع AVERROR(ENOMEM);
    }

    CFDictionary_سيٽ_قدر(
        par,
        k_CVImage_بفر_Pixel_Aspect_تناسب_Horizontal_Spacing_ڪنجي,
        انگ);
    CFDictionary_سيٽ_قدر(
        par,
        k_CVImage_بفر_Pixel_Aspect_تناسب_Vertical_Spacing_ڪنجي,
        den);

    CVBuffer_سيٽ_Attachment(
        pixbuf,
        k_CVImage_بفر_Pixel_Aspect_تناسب_ڪنجي,
        par,
        k_CVAttachment_گهڻائي_Should_Propagate
    );

    CFRelease(par);
    CFRelease(انگ);
    CFRelease(den);

    أرجع 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(تعداد AVChromaLocation loc)
{
    بدل (loc) {
    حالة AVCHROMA_LOC_کاٻو:
        أرجع k_CVImage_بفر_Chroma_Location_کاٻو;
    حالة AVCHROMA_LOC_CENTER:
        أرجع k_CVImage_بفر_Chroma_Location_Center;
    حالة AVCHROMA_LOC_چوٽي:
        أرجع k_CVImage_بفر_Chroma_Location_چوٽي;
    حالة AVCHROMA_LOC_BOTTOM:
        أرجع k_CVImage_بفر_Chroma_Location_Bottom;
    حالة AVCHROMA_LOC_TOPLEFT:
        أرجع k_CVImage_بفر_Chroma_Location_چوٽي_کاٻو;
    حالة AVCHROMA_LOC_BOTTOMLEFT:
        أرجع k_CVImage_بفر_Chroma_Location_Bottom_کاٻو;
    افتراضي:
        أرجع عدم;
    }
}

ساكن صحيح vt_pixbuf_سيٽ_chromaloc(فراغ *log_ctx,
                                   CVPixel_بفر_Ref pixbuf, ثابت AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    إذا (loc) {
        CVBuffer_سيٽ_Attachment(
            pixbuf,
            k_CVImage_بفر_Chroma_Location_چوٽي_ميدان_ڪنجي,
            loc,
            k_CVAttachment_گهڻائي_Should_Propagate);
    } وإلا
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_بفر_Chroma_Location_چوٽي_ميدان_ڪنجي);

    أرجع 0;
}

CFStringRef av_map_videotoolbox_color_ميٽرڪس_from_av(تعداد AVColorSpace space)
{
    بدل (space) {
    حالة AVCOL_SPC_BT2020_CL:
    حالة AVCOL_SPC_BT2020_NCL:
#إذا HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        إذا (__builtin_available(macOS 10.11, iOS 9, *))
            أرجع k_CVImage_بفر_YCb_Cr_ميٽرڪس_ITU_R_2020;
#جيڪڏهن_پورو
        أرجع CFSTR("ITU_R_2020");
    حالة AVCOL_SPC_BT470BG:
    حالة AVCOL_SPC_SMPTE170M:
        أرجع k_CVImage_بفر_YCb_Cr_ميٽرڪس_ITU_R_601_4;
    حالة AVCOL_SPC_BT709:
        أرجع k_CVImage_بفر_YCb_Cr_ميٽرڪس_ITU_R_709_2;
    حالة AVCOL_SPC_SMPTE240M:
        أرجع k_CVImage_بفر_YCb_Cr_ميٽرڪس_SMPTE_240_M_1995;
    افتراضي:
#إذا HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        إذا (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            أرجع CVYCb_Cr_ميٽرڪس_Get_String_For_Integer_ڪوڊ_نقطو(space);
        av_fallthrough;
#جيڪڏهن_پورو
    حالة AVCOL_SPC_UNSPECIFIED:
        أرجع عدم;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(تعداد AVColorPrimaries pri)
{
    بدل (pri) {
    حالة AVCOL_PRI_BT2020:
#إذا HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        إذا (__builtin_available(macOS 10.11, iOS 9, *))
            أرجع k_CVImage_بفر_Color_Primaries_ITU_R_2020;
#جيڪڏهن_پورو
        أرجع CFSTR("ITU_R_2020");
    حالة AVCOL_PRI_BT709:
        أرجع k_CVImage_بفر_Color_Primaries_ITU_R_709_2;
    حالة AVCOL_PRI_SMPTE170M:
        أرجع k_CVImage_بفر_Color_Primaries_SMPTE_C;
    حالة AVCOL_PRI_BT470BG:
        أرجع k_CVImage_بفر_Color_Primaries_EBU_3213;
    افتراضي:
#إذا HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        إذا (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            أرجع CVColor_Primaries_Get_String_For_Integer_ڪوڊ_نقطو(pri);
        av_fallthrough;
#جيڪڏهن_پورو
    حالة AVCOL_PRI_UNSPECIFIED:
        أرجع عدم;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(تعداد AVColorTransferCharacteristic trc)
{

    بدل (trc) {
    حالة AVCOL_TRC_SMPTE2084:
#إذا HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        إذا (__builtin_available(macOS 10.13, iOS 11, *))
            أرجع k_CVImage_بفر_Transfer_Function_SMPTE_ST_2084_PQ;
#جيڪڏهن_پورو
        أرجع CFSTR("SMPTE_ST_2084_PQ");
    حالة AVCOL_TRC_BT2020_10:
    حالة AVCOL_TRC_BT2020_12:
#إذا HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        إذا (__builtin_available(macOS 10.11, iOS 9, *))
            أرجع k_CVImage_بفر_Transfer_Function_ITU_R_2020;
#جيڪڏهن_پورو
        أرجع CFSTR("ITU_R_2020");
    حالة AVCOL_TRC_BT709:
        أرجع k_CVImage_بفر_Transfer_Function_ITU_R_709_2;
    حالة AVCOL_TRC_SMPTE240M:
        أرجع k_CVImage_بفر_Transfer_Function_SMPTE_240_M_1995;
    حالة AVCOL_TRC_SMPTE428:
#إذا HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        إذا (__builtin_available(macOS 10.12, iOS 10, *))
            أرجع k_CVImage_بفر_Transfer_Function_SMPTE_ST_428_1;
#جيڪڏهن_پورو
        أرجع CFSTR("SMPTE_ST_428_1");
    حالة AVCOL_TRC_ARIB_STD_B67:
#إذا HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        إذا (__builtin_available(macOS 10.13, iOS 11, *))
            أرجع k_CVImage_بفر_Transfer_Function_ITU_R_2100_HLG;
#جيڪڏهن_پورو
        أرجع CFSTR("ITU_R_2100_HLG");
    حالة AVCOL_TRC_GAMMA22:
        أرجع k_CVImage_بفر_Transfer_Function_Use_Gamma;
    حالة AVCOL_TRC_GAMMA28:
        أرجع k_CVImage_بفر_Transfer_Function_Use_Gamma;
    افتراضي:
#إذا HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        إذا (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            أرجع CVTransfer_Function_Get_String_For_Integer_ڪوڊ_نقطو(trc);
        av_fallthrough;
#جيڪڏهن_پورو
    حالة AVCOL_TRC_UNSPECIFIED:
        أرجع عدم;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
ساكن CFDictionaryRef vt_cv_بفر_copy_attachments(CVBufferRef بفر,
                                                     CVAttachment_گهڻائي attachment_گهڻائي)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #إذا (هدف_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (هدف_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (هدف_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        إذا (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            أرجع CVBufferCopyAttachments(بفر, attachment_گهڻائي);
    #جيڪڏهن_پورو

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #إذا (هدف_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (هدف_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (هدف_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(بفر, attachment_گهڻائي);
        أرجع (dict) ? CFDictionaryCreateCopy(عدم, dict) : عدم;
    #وإلا
        أرجع عدم; // Impossible, just make the compiler happy
    #جيڪڏهن_پورو
}

ساكن صحيح vt_pixbuf_سيٽ_colorspace(فراغ *log_ctx,
                                    CVPixel_بفر_Ref pixbuf, ثابت AVFrame *src)
{
    CGColorSpaceRef colorspace = عدم;
    CFStringRef colormatrix = عدم, colorpri = عدم, colortrc = عدم;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_ميٽرڪس_from_av(src->colorspace);
    إذا (colormatrix)
        CVBuffer_سيٽ_Attachment(pixbuf, k_CVImage_بفر_YCb_Cr_ميٽرڪس_ڪنجي,
            colormatrix, k_CVAttachment_گهڻائي_Should_Propagate);
    وإلا {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_بفر_YCb_Cr_ميٽرڪس_ڪنجي);
        إذا (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    إذا (colorpri)
        CVBuffer_سيٽ_Attachment(pixbuf, k_CVImage_بفر_Color_Primaries_ڪنجي,
            colorpri, k_CVAttachment_گهڻائي_Should_Propagate);
    وإلا {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_بفر_Color_Primaries_ڪنجي);
        إذا (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    إذا (colortrc)
        CVBuffer_سيٽ_Attachment(pixbuf, k_CVImage_بفر_Transfer_Function_ڪنجي,
            colortrc, k_CVAttachment_گهڻائي_Should_Propagate);
    وإلا {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_بفر_Transfer_Function_ڪنجي);
        إذا (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    إذا (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    وإلا إذا (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    إذا (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(عدم, kCFNumberFloat32Type, &gamma);
        CVBuffer_سيٽ_Attachment(pixbuf, k_CVImage_بفر_Gamma_Level_ڪنجي,
            gamma_level, k_CVAttachment_گهڻائي_Should_Propagate);
        CFRelease(gamma_level);
    } وإلا
        CVBufferRemoveAttachment(pixbuf, k_CVImage_بفر_Gamma_Level_ڪنجي);

#إذا (هدف_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (هدف_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    إذا (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_بفر_copy_attachments(pixbuf, k_CVAttachment_گهڻائي_Should_Propagate);

        إذا (attachments) {
            colorspace =
                CVImage_بفر_Create_Color_Space_From_Attachments(attachments);
            CFRelease(attachments);
        }
    }
#جيڪڏهن_پورو

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    إذا (colorspace) {
        CVBuffer_سيٽ_Attachment(pixbuf, k_CVImage_بفر_CGColor_Space_ڪنجي,
            colorspace, k_CVAttachment_گهڻائي_Should_Propagate);
        CFRelease(colorspace);
    } وإلا
        CVBufferRemoveAttachment(pixbuf, k_CVImage_بفر_CGColor_Space_ڪنجي);

    أرجع 0;
}

ساكن صحيح vt_pixbuf_سيٽ_attachments(فراغ *log_ctx,
                                     CVPixel_بفر_Ref pixbuf, ثابت AVFrame *src)
{
    صحيح ret;
    ret = vt_pixbuf_سيٽ_par(log_ctx, pixbuf, src);
    إذا (ret < 0)
        أرجع ret;
    ret = vt_pixbuf_سيٽ_colorspace(log_ctx, pixbuf, src);
    إذا (ret < 0)
        أرجع ret;
    ret = vt_pixbuf_سيٽ_chromaloc(log_ctx, pixbuf, src);
    إذا (ret < 0)
        أرجع ret;
    أرجع 0;
}

صحيح av_vt_pixbuf_سيٽ_attachments(فراغ *log_ctx,
                                 CVPixel_بفر_Ref pixbuf, ثابت AVFrame *src)
{
    أرجع vt_pixbuf_سيٽ_attachments(log_ctx, pixbuf, src);
}

ساكن صحيح vt_map_چوکٺو(AVHWFramesContext *ctx, AVFrame *dst, ثابت AVFrame *src,
                        صحيح flags)
{
    CVPixel_بفر_Ref pixbuf = (CVPixel_بفر_Ref)src->معلومات[3];
    OSType pixel_format = CVPixel_بفر_Get_Pixel_Format_Type(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    صحيح ret;
    صحيح i;
    تعداد AVPixelFormat format;

    format = av_map_videotoolbox_format_منزل_pixfmt(pixel_format);
    إذا (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        أرجع AVERROR_UNKNOWN;
    }

    إذا (CVPixel_بفر_Get_ويڪر(pixbuf) != ctx->ويڪر ||
        CVPixel_بفر_Get_اوچائي(pixbuf) != ctx->اوچائي) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        أرجع AVERROR_UNKNOWN;
    }

    إذا (flags == AV_HWFRAME_MAP_READ)
        map_flags = k_CVPixel_بفر_تالو_Read_Only;

    err = CVPixel_بفر_تالو_بنياد_پتو(pixbuf, map_flags);
    إذا (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        أرجع AVERROR_UNKNOWN;
    }

    إذا (CVPixel_بفر_Is_Planar(pixbuf)) {
        صحيح planes = CVPixel_بفر_Get_Plane_ڳڻپ(pixbuf);
        لكل (i = 0; i < planes; i++) {
            dst->معلومات[i]     = CVPixel_بفر_Get_بنياد_پتو_جو_Plane(pixbuf, i);
            dst->linesize[i] = CVPixel_بفر_Get_بائيٽون_في_صف_جو_Plane(pixbuf, i);
        }
    } وإلا {
        dst->معلومات[0]     = CVPixel_بفر_Get_بنياد_پتو(pixbuf);
        dst->linesize[0] = CVPixel_بفر_Get_بائيٽون_في_صف(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_چوکٺا_ctx, dst, src, vt_unmap,
                                (فراغ *)(uintptr_t)map_flags);
    إذا (ret < 0)
        اذهب unlock;

    أرجع 0;

unlock:
    CVPixel_بفر_Unlock_بنياد_پتو(pixbuf, map_flags);
    أرجع ret;
}

ساكن صحيح vt_transfer_معلومات_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحيح err;

    إذا (dst->ويڪر > hwfc->ويڪر || dst->اوچائي > hwfc->اوچائي)
        أرجع AVERROR(EINVAL);

    map = av_چوکٺو_alloc();
    إذا (!map)
        أرجع AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_چوکٺو(hwfc, map, src, AV_HWFRAME_MAP_READ);
    إذا (err)
        اذهب fail;

    map->ويڪر  = dst->ويڪر;
    map->اوچائي = dst->اوچائي;

    err = av_چوکٺو_copy(dst, map);
    إذا (err)
        اذهب fail;

    err = 0;
fail:
    av_چوکٺو_free(&map);
    أرجع err;
}

ساكن صحيح vt_transfer_معلومات_منزل(AVHWFramesContext *hwfc,
                               AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحيح err;

    إذا (src->ويڪر > hwfc->ويڪر || src->اوچائي > hwfc->اوچائي)
        أرجع AVERROR(EINVAL);

    map = av_چوکٺو_alloc();
    إذا (!map)
        أرجع AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_چوکٺو(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    إذا (err)
        اذهب fail;

    map->ويڪر  = src->ويڪر;
    map->اوچائي = src->اوچائي;

    err = av_چوکٺو_copy(map, src);
    إذا (err)
        اذهب fail;

    err = vt_pixbuf_سيٽ_attachments(hwfc, (CVPixel_بفر_Ref)dst->معلومات[3], src);
    إذا (err)
        اذهب fail;

    err = 0;
fail:
    av_چوکٺو_free(&map);
    أرجع err;
}

ساكن صحيح vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       ثابت AVFrame *src, صحيح flags)
{
    صحيح err;

    إذا (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    وإلا إذا (dst->format != hwfc->sw_format)
        أرجع AVERROR(ENOSYS);

    err = vt_map_چوکٺو(hwfc, dst, src, flags);
    إذا (err)
        أرجع err;

    dst->ويڪر  = src->ويڪر;
    dst->اوچائي = src->اوچائي;

    err = av_چوکٺو_copy_props(dst, src);
    إذا (err)
        أرجع err;

    أرجع 0;
}

ساكن صحيح vt_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                            AVDictionary *opts, صحيح flags)
{
    إذا (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}

ثابت HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .چوکٺا_hwctx_سائيز    = حجم(VTFramesContext),

    .device_create        = vt_device_create,
    .چوکٺا_init          = vt_چوکٺا_init,
    .چوکٺا_get_بفر    = vt_get_بفر,
    .چوکٺا_get_constraints = vt_چوکٺا_get_constraints,
    .چوکٺا_uninit        = vt_چوکٺا_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_معلومات_منزل     = vt_transfer_معلومات_منزل,
    .transfer_معلومات_from   = vt_transfer_معلومات_from,
    .map_from             = vt_map_from,

    .pix_fmts = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
