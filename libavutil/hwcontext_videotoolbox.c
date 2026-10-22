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

#شامل "config.h"

#شامل <stdint.h>
#شامل <string.h>

#شامل <VideoToolbox/VideoToolbox.h>

#شامل "buffer.h"
#شامل "buffer_internal.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_internal.h"
#شامل "hwcontext_videotoolbox.h"
#شامل "attributes.h"
#شامل "mem.h"
#شامل "pixfmt.h"
#شامل "pixdesc.h"

قسمتعریف ساخت VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixel_بفر_Pool_Ref pool;
} VTFramesContext;

ساکن ثابت ساخت {
    uint32_t cv_fmt;
    bool بھرا_range;
    شمار AVPixelFormat pix_fmt;
} cv_pix_fmts[] = {
    { kCVPixelFormatType_420YpCbCr8Planar,              false, AV_PIX_FMT_YUV420P },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr8_Planar_بھرا_Range,     true,  AV_PIX_FMT_YUV420P },
    { kCVPixelFormatType_422YpCbCr8,                    false, AV_PIX_FMT_UYVY422 },
    { kCVPixelFormatType_32BGRA,                        true,  AV_PIX_FMT_BGRA },
#اگر_تعریف_شدہ k_CFCore_Foundation_نسخہ_Number10_7
    { kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV12 },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr8_Bi_Planar_بھرا_Range,   true,  AV_PIX_FMT_NV12 },
    { kCVPixelFormatType_4444AYpCbCr8,                  false, AV_PIX_FMT_AYUV },
    { kCVPixelFormatType_4444AYpCbCr16,                 false, AV_PIX_FMT_AYUV64 },
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr10_Bi_Planar_بھرا_Range,  true,  AV_PIX_FMT_P010 },
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { k_CVPixel_Format_Type_422_Yp_Cb_Cr8_Bi_Planar_بھرا_Range,   true,  AV_PIX_FMT_NV16 },
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { k_CVPixel_Format_Type_422_Yp_Cb_Cr10_Bi_Planar_بھرا_Range,  true,  AV_PIX_FMT_P210 },
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { k_CVPixel_Format_Type_444_Yp_Cb_Cr8_Bi_Planar_بھرا_Range,   true,  AV_PIX_FMT_NV24 },
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { k_CVPixel_Format_Type_444_Yp_Cb_Cr10_Bi_Planar_بھرا_Range,  true,  AV_PIX_FMT_P410 },
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#اگر_ختم
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

ساکن ثابت شمار AVPixelFormat supported_formats[] = {
#اگر_تعریف_شدہ k_CFCore_Foundation_نسخہ_Number10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#اگر_ختم
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#اگر HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#اگر_ختم
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#اگر_ختم
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

ساکن صحیح vt_چوکھٹے_get_constraints(AVHWDeviceContext *ctx,
                                     ثابت خالی *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    صحیح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    اگر (!constraints->valid_sw_formats)
        واپس AVERROR(ENOMEM);

    برائے (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    اگر (!constraints->valid_hw_formats)
        واپس AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    واپس 0;
}

شمار AVPixelFormat av_map_videotoolbox_format_مقصد_pixfmt(uint32_t cv_fmt)
{
    صحیح i;
    برائے (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        اگر (cv_pix_fmts[i].cv_fmt == cv_fmt)
            واپس cv_pix_fmts[i].pix_fmt;
    }
    واپس AV_PIX_FMT_NONE;
}

ساکن uint32_t vt_format_from_pixfmt(شمار AVPixelFormat pix_fmt,
                                      شمار AVColorRange range)
{
    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        اگر (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            صحیح بھرا_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            اگر (range == AVCOL_RANGE_UNSPECIFIED)
                واپس cv_pix_fmts[i].cv_fmt;

            اگر (cv_pix_fmts[i].بھرا_range == بھرا_range)
                واپس cv_pix_fmts[i].cv_fmt;
        }
    }

    واپس 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(شمار AVPixelFormat pix_fmt)
{
    واپس av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(شمار AVPixelFormat pix_fmt, bool بھرا_range)
{
    واپس vt_format_from_pixfmt(pix_fmt, بھرا_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

ساکن صحیح vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef اوصاف, iosurface_properties;

    اوصاف = CFDictionaryCreateMutable(
        تہی,
        2,
        &k_CFType_Dictionary_کلید_Call_Backs,
        &k_CFType_Dictionary_قدر_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(تہی, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_سیٹ_قدر(
        اوصاف,
        k_CVPixel_بفر_Pixel_Format_Type_کلید,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        تہی,
        0,
        &k_CFType_Dictionary_کلید_Call_Backs,
        &k_CFType_Dictionary_قدر_Call_Backs);
    CFDictionary_سیٹ_قدر(اوصاف, k_CVPixel_بفر_IOSurface_Properties_کلید, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(تہی, kCFNumberSInt32Type, &ctx->چوڑائی);
    h = CFNumberCreate(تہی, kCFNumberSInt32Type, &ctx->اونچائی);
    CFDictionary_سیٹ_قدر(اوصاف, k_CVPixel_بفر_چوڑائی_کلید, w);
    CFDictionary_سیٹ_قدر(اوصاف, k_CVPixel_بفر_اونچائی_کلید, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixel_بفر_Pool_Create(
        تہی,
        تہی,
        اوصاف,
        &fctx->pool);
    CFRelease(اوصاف);

    اگر (err == kCVReturnSuccess)
        واپس 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    واپس AVERROR_EXTERNAL;
}

ساکن خالی videotoolbox_بفر_release(خالی *opaque, uint8_t *ڈیٹا)
{
    CVPixel_بفر_Release((CVPixel_بفر_Ref)ڈیٹا);
}

ساکن AVBufferRef *vt_pool_alloc_بفر(خالی *opaque, size_t سائز)
{
    CVPixel_بفر_Ref pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixel_بفر_Pool_Create_Pixel_بفر(
        تہی,
        fctx->pool,
        &pixbuf
    );
    اگر (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        واپس تہی;
    }

    buf = av_بفر_create((uint8_t *)pixbuf, سائز,
                           videotoolbox_بفر_release, تہی, 0);
    اگر (!buf) {
        CVPixel_بفر_Release(pixbuf);
        واپس تہی;
    }
    واپس buf;
}

ساکن خالی vt_چوکھٹے_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    اگر (fctx->pool) {
        CVPixel_بفر_Pool_Release(fctx->pool);
        fctx->pool = تہی;
    }
}

ساکن صحیح vt_چوکھٹے_init(AVHWFramesContext *ctx)
{
    صحیح i, ret;

    برائے (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        اگر (ctx->sw_format == supported_formats[i])
            توڑو;
    }
    اگر (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        واپس AVERROR(ENOSYS);
    }

    اگر (!ctx->pool) {
        ffhwframesctx(ctx)->pool_اندرونی = av_بفر_pool_init2(
                حجم(CVPixel_بفر_Ref), ctx, vt_pool_alloc_بفر, تہی);
        اگر (!ffhwframesctx(ctx)->pool_اندرونی)
            واپس AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    اگر (ret < 0)
        واپس ret;

    واپس 0;
}

ساکن صحیح vt_get_بفر(AVHWFramesContext *ctx, AVFrame *چوکھٹا)
{
    چوکھٹا->buf[0] = av_بفر_pool_get(ctx->pool);
    اگر (!چوکھٹا->buf[0])
        واپس AVERROR(ENOMEM);

    چوکھٹا->ڈیٹا[3] = چوکھٹا->buf[0]->ڈیٹا;
    چوکھٹا->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    چوکھٹا->چوڑائی   = ctx->چوڑائی;
    چوکھٹا->اونچائی  = ctx->اونچائی;

    واپس 0;
}

ساکن صحیح vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   شمار AVHWFrameTransferDirection dir,
                                   شمار AVPixelFormat **formats)
{
    شمار AVPixelFormat *fmts = av_malloc_array(2, حجم(*fmts));
    اگر (!fmts)
        واپس AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    واپس 0;
}

ساکن خالی vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixel_بفر_Ref pixbuf = (CVPixel_بفر_Ref)hwmap->ماخذ->ڈیٹا[3];

    CVPixel_بفر_Unlock_بنیاد_پتہ(pixbuf, (uintptr_t)hwmap->priv);
}

ساکن صحیح vt_pixbuf_سیٹ_par(خالی *log_ctx,
                             CVPixel_بفر_Ref pixbuf, ثابت AVFrame *src)
{
    CFMutableDictionaryRef par = تہی;
    CFNumberRef عدد = تہی, den = تہی;
    AVRational avpar = src->sample_aspect_تناسب;

    اگر (avpar.عدد == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_بفر_Pixel_Aspect_تناسب_کلید);
        واپس 0;
    }

    av_reduce(&avpar.عدد, &avpar.den,
                avpar.عدد, avpar.den,
                0xFFFFFFFF);

    عدد = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.عدد);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_کلید_Call_Backs,
                                    &k_CFType_Dictionary_قدر_Call_Backs);

    اگر (!par || !عدد || !den) {
        اگر (par) CFRelease(par);
        اگر (عدد) CFRelease(عدد);
        اگر (den) CFRelease(den);
        واپس AVERROR(ENOMEM);
    }

    CFDictionary_سیٹ_قدر(
        par,
        k_CVImage_بفر_Pixel_Aspect_تناسب_Horizontal_Spacing_کلید,
        عدد);
    CFDictionary_سیٹ_قدر(
        par,
        k_CVImage_بفر_Pixel_Aspect_تناسب_Vertical_Spacing_کلید,
        den);

    CVBuffer_سیٹ_Attachment(
        pixbuf,
        k_CVImage_بفر_Pixel_Aspect_تناسب_کلید,
        par,
        k_CVAttachment_منوال_Should_Propagate
    );

    CFRelease(par);
    CFRelease(عدد);
    CFRelease(den);

    واپس 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(شمار AVChromaLocation loc)
{
    انتخاب (loc) {
    حالت AVCHROMA_LOC_بایاں:
        واپس k_CVImage_بفر_Chroma_Location_بایاں;
    حالت AVCHROMA_LOC_CENTER:
        واپس k_CVImage_بفر_Chroma_Location_Center;
    حالت AVCHROMA_LOC_چوٹی:
        واپس k_CVImage_بفر_Chroma_Location_چوٹی;
    حالت AVCHROMA_LOC_BOTTOM:
        واپس k_CVImage_بفر_Chroma_Location_Bottom;
    حالت AVCHROMA_LOC_TOPLEFT:
        واپس k_CVImage_بفر_Chroma_Location_چوٹی_بایاں;
    حالت AVCHROMA_LOC_BOTTOMLEFT:
        واپس k_CVImage_بفر_Chroma_Location_Bottom_بایاں;
    طےشدہ:
        واپس تہی;
    }
}

ساکن صحیح vt_pixbuf_سیٹ_chromaloc(خالی *log_ctx,
                                   CVPixel_بفر_Ref pixbuf, ثابت AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    اگر (loc) {
        CVBuffer_سیٹ_Attachment(
            pixbuf,
            k_CVImage_بفر_Chroma_Location_چوٹی_میدان_کلید,
            loc,
            k_CVAttachment_منوال_Should_Propagate);
    } ورنہ
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_بفر_Chroma_Location_چوٹی_میدان_کلید);

    واپس 0;
}

CFStringRef av_map_videotoolbox_color_میٹرکس_from_av(شمار AVColorSpace space)
{
    انتخاب (space) {
    حالت AVCOL_SPC_BT2020_CL:
    حالت AVCOL_SPC_BT2020_NCL:
#اگر HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        اگر (__builtin_available(macOS 10.11, iOS 9, *))
            واپس k_CVImage_بفر_YCb_Cr_میٹرکس_ITU_R_2020;
#اگر_ختم
        واپس CFSTR("ITU_R_2020");
    حالت AVCOL_SPC_BT470BG:
    حالت AVCOL_SPC_SMPTE170M:
        واپس k_CVImage_بفر_YCb_Cr_میٹرکس_ITU_R_601_4;
    حالت AVCOL_SPC_BT709:
        واپس k_CVImage_بفر_YCb_Cr_میٹرکس_ITU_R_709_2;
    حالت AVCOL_SPC_SMPTE240M:
        واپس k_CVImage_بفر_YCb_Cr_میٹرکس_SMPTE_240_M_1995;
    طےشدہ:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        اگر (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            واپس CVYCb_Cr_میٹرکس_Get_String_For_Integer_رمز_نقطہ(space);
        av_fallthrough;
#اگر_ختم
    حالت AVCOL_SPC_UNSPECIFIED:
        واپس تہی;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(شمار AVColorPrimaries pri)
{
    انتخاب (pri) {
    حالت AVCOL_PRI_BT2020:
#اگر HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        اگر (__builtin_available(macOS 10.11, iOS 9, *))
            واپس k_CVImage_بفر_Color_Primaries_ITU_R_2020;
#اگر_ختم
        واپس CFSTR("ITU_R_2020");
    حالت AVCOL_PRI_BT709:
        واپس k_CVImage_بفر_Color_Primaries_ITU_R_709_2;
    حالت AVCOL_PRI_SMPTE170M:
        واپس k_CVImage_بفر_Color_Primaries_SMPTE_C;
    حالت AVCOL_PRI_BT470BG:
        واپس k_CVImage_بفر_Color_Primaries_EBU_3213;
    طےشدہ:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        اگر (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            واپس CVColor_Primaries_Get_String_For_Integer_رمز_نقطہ(pri);
        av_fallthrough;
#اگر_ختم
    حالت AVCOL_PRI_UNSPECIFIED:
        واپس تہی;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(شمار AVColorTransferCharacteristic trc)
{

    انتخاب (trc) {
    حالت AVCOL_TRC_SMPTE2084:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        اگر (__builtin_available(macOS 10.13, iOS 11, *))
            واپس k_CVImage_بفر_Transfer_Function_SMPTE_ST_2084_PQ;
#اگر_ختم
        واپس CFSTR("SMPTE_ST_2084_PQ");
    حالت AVCOL_TRC_BT2020_10:
    حالت AVCOL_TRC_BT2020_12:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        اگر (__builtin_available(macOS 10.11, iOS 9, *))
            واپس k_CVImage_بفر_Transfer_Function_ITU_R_2020;
#اگر_ختم
        واپس CFSTR("ITU_R_2020");
    حالت AVCOL_TRC_BT709:
        واپس k_CVImage_بفر_Transfer_Function_ITU_R_709_2;
    حالت AVCOL_TRC_SMPTE240M:
        واپس k_CVImage_بفر_Transfer_Function_SMPTE_240_M_1995;
    حالت AVCOL_TRC_SMPTE428:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        اگر (__builtin_available(macOS 10.12, iOS 10, *))
            واپس k_CVImage_بفر_Transfer_Function_SMPTE_ST_428_1;
#اگر_ختم
        واپس CFSTR("SMPTE_ST_428_1");
    حالت AVCOL_TRC_ARIB_STD_B67:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        اگر (__builtin_available(macOS 10.13, iOS 11, *))
            واپس k_CVImage_بفر_Transfer_Function_ITU_R_2100_HLG;
#اگر_ختم
        واپس CFSTR("ITU_R_2100_HLG");
    حالت AVCOL_TRC_GAMMA22:
        واپس k_CVImage_بفر_Transfer_Function_Use_Gamma;
    حالت AVCOL_TRC_GAMMA28:
        واپس k_CVImage_بفر_Transfer_Function_Use_Gamma;
    طےشدہ:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        اگر (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            واپس CVTransfer_Function_Get_String_For_Integer_رمز_نقطہ(trc);
        av_fallthrough;
#اگر_ختم
    حالت AVCOL_TRC_UNSPECIFIED:
        واپس تہی;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
ساکن CFDictionaryRef vt_cv_بفر_copy_attachments(CVBufferRef بفر,
                                                     CVAttachment_منوال attachment_منوال)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #اگر (ہدف_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (ہدف_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (ہدف_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        اگر (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            واپس CVBufferCopyAttachments(بفر, attachment_منوال);
    #اگر_ختم

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #اگر (ہدف_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (ہدف_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (ہدف_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(بفر, attachment_منوال);
        واپس (dict) ? CFDictionaryCreateCopy(تہی, dict) : تہی;
    #ورنہ
        واپس تہی; // Impossible, just make the compiler happy
    #اگر_ختم
}

ساکن صحیح vt_pixbuf_سیٹ_colorspace(خالی *log_ctx,
                                    CVPixel_بفر_Ref pixbuf, ثابت AVFrame *src)
{
    CGColorSpaceRef colorspace = تہی;
    CFStringRef colormatrix = تہی, colorpri = تہی, colortrc = تہی;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_میٹرکس_from_av(src->colorspace);
    اگر (colormatrix)
        CVBuffer_سیٹ_Attachment(pixbuf, k_CVImage_بفر_YCb_Cr_میٹرکس_کلید,
            colormatrix, k_CVAttachment_منوال_Should_Propagate);
    ورنہ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_بفر_YCb_Cr_میٹرکس_کلید);
        اگر (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    اگر (colorpri)
        CVBuffer_سیٹ_Attachment(pixbuf, k_CVImage_بفر_Color_Primaries_کلید,
            colorpri, k_CVAttachment_منوال_Should_Propagate);
    ورنہ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_بفر_Color_Primaries_کلید);
        اگر (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    اگر (colortrc)
        CVBuffer_سیٹ_Attachment(pixbuf, k_CVImage_بفر_Transfer_Function_کلید,
            colortrc, k_CVAttachment_منوال_Should_Propagate);
    ورنہ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_بفر_Transfer_Function_کلید);
        اگر (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    اگر (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    ورنہ اگر (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    اگر (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(تہی, kCFNumberFloat32Type, &gamma);
        CVBuffer_سیٹ_Attachment(pixbuf, k_CVImage_بفر_Gamma_Level_کلید,
            gamma_level, k_CVAttachment_منوال_Should_Propagate);
        CFRelease(gamma_level);
    } ورنہ
        CVBufferRemoveAttachment(pixbuf, k_CVImage_بفر_Gamma_Level_کلید);

#اگر (ہدف_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (ہدف_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    اگر (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_بفر_copy_attachments(pixbuf, k_CVAttachment_منوال_Should_Propagate);

        اگر (attachments) {
            colorspace =
                CVImage_بفر_Create_Color_Space_From_Attachments(attachments);
            CFRelease(attachments);
        }
    }
#اگر_ختم

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    اگر (colorspace) {
        CVBuffer_سیٹ_Attachment(pixbuf, k_CVImage_بفر_CGColor_Space_کلید,
            colorspace, k_CVAttachment_منوال_Should_Propagate);
        CFRelease(colorspace);
    } ورنہ
        CVBufferRemoveAttachment(pixbuf, k_CVImage_بفر_CGColor_Space_کلید);

    واپس 0;
}

ساکن صحیح vt_pixbuf_سیٹ_attachments(خالی *log_ctx,
                                     CVPixel_بفر_Ref pixbuf, ثابت AVFrame *src)
{
    صحیح ret;
    ret = vt_pixbuf_سیٹ_par(log_ctx, pixbuf, src);
    اگر (ret < 0)
        واپس ret;
    ret = vt_pixbuf_سیٹ_colorspace(log_ctx, pixbuf, src);
    اگر (ret < 0)
        واپس ret;
    ret = vt_pixbuf_سیٹ_chromaloc(log_ctx, pixbuf, src);
    اگر (ret < 0)
        واپس ret;
    واپس 0;
}

صحیح av_vt_pixbuf_سیٹ_attachments(خالی *log_ctx,
                                 CVPixel_بفر_Ref pixbuf, ثابت AVFrame *src)
{
    واپس vt_pixbuf_سیٹ_attachments(log_ctx, pixbuf, src);
}

ساکن صحیح vt_map_چوکھٹا(AVHWFramesContext *ctx, AVFrame *dst, ثابت AVFrame *src,
                        صحیح flags)
{
    CVPixel_بفر_Ref pixbuf = (CVPixel_بفر_Ref)src->ڈیٹا[3];
    OSType pixel_format = CVPixel_بفر_Get_Pixel_Format_Type(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    صحیح ret;
    صحیح i;
    شمار AVPixelFormat format;

    format = av_map_videotoolbox_format_مقصد_pixfmt(pixel_format);
    اگر (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        واپس AVERROR_UNKNOWN;
    }

    اگر (CVPixel_بفر_Get_چوڑائی(pixbuf) != ctx->چوڑائی ||
        CVPixel_بفر_Get_اونچائی(pixbuf) != ctx->اونچائی) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        واپس AVERROR_UNKNOWN;
    }

    اگر (flags == AV_HWFRAME_MAP_READ)
        map_flags = k_CVPixel_بفر_تالا_Read_Only;

    err = CVPixel_بفر_تالا_بنیاد_پتہ(pixbuf, map_flags);
    اگر (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        واپس AVERROR_UNKNOWN;
    }

    اگر (CVPixel_بفر_Is_Planar(pixbuf)) {
        صحیح planes = CVPixel_بفر_Get_Plane_گنتی(pixbuf);
        برائے (i = 0; i < planes; i++) {
            dst->ڈیٹا[i]     = CVPixel_بفر_Get_بنیاد_پتہ_کا_Plane(pixbuf, i);
            dst->linesize[i] = CVPixel_بفر_Get_بائٹیں_فی_صف_کا_Plane(pixbuf, i);
        }
    } ورنہ {
        dst->ڈیٹا[0]     = CVPixel_بفر_Get_بنیاد_پتہ(pixbuf);
        dst->linesize[0] = CVPixel_بفر_Get_بائٹیں_فی_صف(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_چوکھٹے_ctx, dst, src, vt_unmap,
                                (خالی *)(uintptr_t)map_flags);
    اگر (ret < 0)
        جاؤ unlock;

    واپس 0;

unlock:
    CVPixel_بفر_Unlock_بنیاد_پتہ(pixbuf, map_flags);
    واپس ret;
}

ساکن صحیح vt_transfer_ڈیٹا_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح err;

    اگر (dst->چوڑائی > hwfc->چوڑائی || dst->اونچائی > hwfc->اونچائی)
        واپس AVERROR(EINVAL);

    map = av_چوکھٹا_alloc();
    اگر (!map)
        واپس AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_چوکھٹا(hwfc, map, src, AV_HWFRAME_MAP_READ);
    اگر (err)
        جاؤ fail;

    map->چوڑائی  = dst->چوڑائی;
    map->اونچائی = dst->اونچائی;

    err = av_چوکھٹا_copy(dst, map);
    اگر (err)
        جاؤ fail;

    err = 0;
fail:
    av_چوکھٹا_free(&map);
    واپس err;
}

ساکن صحیح vt_transfer_ڈیٹا_مقصد(AVHWFramesContext *hwfc,
                               AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح err;

    اگر (src->چوڑائی > hwfc->چوڑائی || src->اونچائی > hwfc->اونچائی)
        واپس AVERROR(EINVAL);

    map = av_چوکھٹا_alloc();
    اگر (!map)
        واپس AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_چوکھٹا(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    اگر (err)
        جاؤ fail;

    map->چوڑائی  = src->چوڑائی;
    map->اونچائی = src->اونچائی;

    err = av_چوکھٹا_copy(map, src);
    اگر (err)
        جاؤ fail;

    err = vt_pixbuf_سیٹ_attachments(hwfc, (CVPixel_بفر_Ref)dst->ڈیٹا[3], src);
    اگر (err)
        جاؤ fail;

    err = 0;
fail:
    av_چوکھٹا_free(&map);
    واپس err;
}

ساکن صحیح vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       ثابت AVFrame *src, صحیح flags)
{
    صحیح err;

    اگر (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ورنہ اگر (dst->format != hwfc->sw_format)
        واپس AVERROR(ENOSYS);

    err = vt_map_چوکھٹا(hwfc, dst, src, flags);
    اگر (err)
        واپس err;

    dst->چوڑائی  = src->چوڑائی;
    dst->اونچائی = src->اونچائی;

    err = av_چوکھٹا_copy_props(dst, src);
    اگر (err)
        واپس err;

    واپس 0;
}

ساکن صحیح vt_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                            AVDictionary *opts, صحیح flags)
{
    اگر (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        واپس AVERROR_UNKNOWN;
    }

    واپس 0;
}

ثابت HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .چوکھٹے_hwctx_سائز    = حجم(VTFramesContext),

    .device_create        = vt_device_create,
    .چوکھٹے_init          = vt_چوکھٹے_init,
    .چوکھٹے_get_بفر    = vt_get_بفر,
    .چوکھٹے_get_constraints = vt_چوکھٹے_get_constraints,
    .چوکھٹے_uninit        = vt_چوکھٹے_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_ڈیٹا_مقصد     = vt_transfer_ڈیٹا_مقصد,
    .transfer_ڈیٹا_from   = vt_transfer_ڈیٹا_from,
    .map_from             = vt_map_from,

    .pix_fmts = (ثابت شمار AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
