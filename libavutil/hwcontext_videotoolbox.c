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

#अन्तर्भाव "config.h"

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव <VideoToolbox/VideoToolbox.h>

#अन्तर्भाव "buffer.h"
#अन्तर्भाव "buffer_internal.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "hwcontext_videotoolbox.h"
#अन्तर्भाव "attributes.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "pixdesc.h"

प्रकारनिर्देश संरचना VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixel_बफर_Pool_Ref pool;
} VTFramesContext;

स्थिर ध्रुव संरचना {
    uint32_t cv_fmt;
    bool पूर्णम्_range;
    गणना AVPixelFormat pix_fmt;
} cv_pix_fmts[] = {
    { kCVPixelFormatType_420YpCbCr8Planar,              false, AV_PIX_FMT_YUV420P },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr8_Planar_पूर्णम्_Range,     true,  AV_PIX_FMT_YUV420P },
    { kCVPixelFormatType_422YpCbCr8,                    false, AV_PIX_FMT_UYVY422 },
    { kCVPixelFormatType_32BGRA,                        true,  AV_PIX_FMT_BGRA },
#यदि_परिभाषितम् k_CFCore_Foundation_संस्करणम्_Number10_7
    { kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV12 },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr8_Bi_Planar_पूर्णम्_Range,   true,  AV_PIX_FMT_NV12 },
    { kCVPixelFormatType_4444AYpCbCr8,                  false, AV_PIX_FMT_AYUV },
    { kCVPixelFormatType_4444AYpCbCr16,                 false, AV_PIX_FMT_AYUV64 },
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr10_Bi_Planar_पूर्णम्_Range,  true,  AV_PIX_FMT_P010 },
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { k_CVPixel_Format_Type_422_Yp_Cb_Cr8_Bi_Planar_पूर्णम्_Range,   true,  AV_PIX_FMT_NV16 },
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { k_CVPixel_Format_Type_422_Yp_Cb_Cr10_Bi_Planar_पूर्णम्_Range,  true,  AV_PIX_FMT_P210 },
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { k_CVPixel_Format_Type_444_Yp_Cb_Cr8_Bi_Planar_पूर्णम्_Range,   true,  AV_PIX_FMT_NV24 },
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { k_CVPixel_Format_Type_444_Yp_Cb_Cr10_Bi_Planar_पूर्णम्_Range,  true,  AV_PIX_FMT_P410 },
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#यदि_अन्तः
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

स्थिर ध्रुव गणना AVPixelFormat supported_formats[] = {
#यदि_परिभाषितम् k_CFCore_Foundation_संस्करणम्_Number10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#यदि_अन्तः
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#यदि HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#यदि_अन्तः
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#यदि_अन्तः
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

स्थिर पूर्णाङ्क vt_चौकटाः_get_constraints(AVHWDeviceContext *ctx,
                                     ध्रुव शून्य *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    पूर्णाङ्क i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    परिमाण(*constraints->valid_sw_formats));
    यदि (!constraints->valid_sw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, परिमाण(*constraints->valid_hw_formats));
    यदि (!constraints->valid_hw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    प्रत्यागम 0;
}

गणना AVPixelFormat av_map_videotoolbox_format_गन्तव्यम्_pixfmt(uint32_t cv_fmt)
{
    पूर्णाङ्क i;
    प्रति (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        यदि (cv_pix_fmts[i].cv_fmt == cv_fmt)
            प्रत्यागम cv_pix_fmts[i].pix_fmt;
    }
    प्रत्यागम AV_PIX_FMT_NONE;
}

स्थिर uint32_t vt_format_from_pixfmt(गणना AVPixelFormat pix_fmt,
                                      गणना AVColorRange range)
{
    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        यदि (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            पूर्णाङ्क पूर्णम्_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            यदि (range == AVCOL_RANGE_UNSPECIFIED)
                प्रत्यागम cv_pix_fmts[i].cv_fmt;

            यदि (cv_pix_fmts[i].पूर्णम्_range == पूर्णम्_range)
                प्रत्यागम cv_pix_fmts[i].cv_fmt;
        }
    }

    प्रत्यागम 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(गणना AVPixelFormat pix_fmt)
{
    प्रत्यागम av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(गणना AVPixelFormat pix_fmt, bool पूर्णम्_range)
{
    प्रत्यागम vt_format_from_pixfmt(pix_fmt, पूर्णम्_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

स्थिर पूर्णाङ्क vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef गुणाः, iosurface_properties;

    गुणाः = CFDictionaryCreateMutable(
        रिक्त,
        2,
        &k_CFType_Dictionary_कुञ्चिका_Call_Backs,
        &k_CFType_Dictionary_मानम्_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(रिक्त, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_समुच्चयः_मानम्(
        गुणाः,
        k_CVPixel_बफर_Pixel_Format_Type_कुञ्चिका,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        रिक्त,
        0,
        &k_CFType_Dictionary_कुञ्चिका_Call_Backs,
        &k_CFType_Dictionary_मानम्_Call_Backs);
    CFDictionary_समुच्चयः_मानम्(गुणाः, k_CVPixel_बफर_IOSurface_Properties_कुञ्चिका, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(रिक्त, kCFNumberSInt32Type, &ctx->विस्तारः);
    h = CFNumberCreate(रिक्त, kCFNumberSInt32Type, &ctx->height);
    CFDictionary_समुच्चयः_मानम्(गुणाः, k_CVPixel_बफर_विस्तारः_कुञ्चिका, w);
    CFDictionary_समुच्चयः_मानम्(गुणाः, k_CVPixel_बफर_Height_कुञ्चिका, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixel_बफर_Pool_Create(
        रिक्त,
        रिक्त,
        गुणाः,
        &fctx->pool);
    CFRelease(गुणाः);

    यदि (err == kCVReturnSuccess)
        प्रत्यागम 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    प्रत्यागम AVERROR_EXTERNAL;
}

स्थिर शून्य videotoolbox_बफर_release(शून्य *opaque, uint8_t *दत्त)
{
    CVPixel_बफर_Release((CVPixel_बफर_Ref)दत्त);
}

स्थिर AVBufferRef *vt_pool_alloc_बफर(शून्य *opaque, size_t आकार)
{
    CVPixel_बफर_Ref pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixel_बफर_Pool_Create_Pixel_बफर(
        रिक्त,
        fctx->pool,
        &pixbuf
    );
    यदि (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        प्रत्यागम रिक्त;
    }

    buf = av_बफर_create((uint8_t *)pixbuf, आकार,
                           videotoolbox_बफर_release, रिक्त, 0);
    यदि (!buf) {
        CVPixel_बफर_Release(pixbuf);
        प्रत्यागम रिक्त;
    }
    प्रत्यागम buf;
}

स्थिर शून्य vt_चौकटाः_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    यदि (fctx->pool) {
        CVPixel_बफर_Pool_Release(fctx->pool);
        fctx->pool = रिक्त;
    }
}

स्थिर पूर्णाङ्क vt_चौकटाः_init(AVHWFramesContext *ctx)
{
    पूर्णाङ्क i, ret;

    प्रति (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        यदि (ctx->sw_format == supported_formats[i])
            भङ्ग;
    }
    यदि (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        प्रत्यागम AVERROR(ENOSYS);
    }

    यदि (!ctx->pool) {
        ffhwframesctx(ctx)->pool_आन्तरिकम् = av_बफर_pool_init2(
                परिमाण(CVPixel_बफर_Ref), ctx, vt_pool_alloc_बफर, रिक्त);
        यदि (!ffhwframesctx(ctx)->pool_आन्तरिकम्)
            प्रत्यागम AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    यदि (ret < 0)
        प्रत्यागम ret;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vt_get_बफर(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_बफर_pool_get(ctx->pool);
    यदि (!frame->buf[0])
        प्रत्यागम AVERROR(ENOMEM);

    frame->दत्त[3] = frame->buf[0]->दत्त;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->विस्तारः   = ctx->विस्तारः;
    frame->height  = ctx->height;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   गणना AVHWFrameTransferDirection dir,
                                   गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts = av_malloc_array(2, परिमाण(*fmts));
    यदि (!fmts)
        प्रत्यागम AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    प्रत्यागम 0;
}

स्थिर शून्य vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixel_बफर_Ref pixbuf = (CVPixel_बफर_Ref)hwmap->source->दत्त[3];

    CVPixel_बफर_Unlock_आधारः_स्थानाङ्कः(pixbuf, (uintptr_t)hwmap->priv);
}

स्थिर पूर्णाङ्क vt_pixbuf_समुच्चयः_par(शून्य *log_ctx,
                             CVPixel_बफर_Ref pixbuf, ध्रुव AVFrame *src)
{
    CFMutableDictionaryRef par = रिक्त;
    CFNumberRef अङ्कः = रिक्त, den = रिक्त;
    AVRational avpar = src->sample_aspect_अनुपातः;

    यदि (avpar.अङ्कः == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_बफर_Pixel_Aspect_अनुपातः_कुञ्चिका);
        प्रत्यागम 0;
    }

    av_reduce(&avpar.अङ्कः, &avpar.den,
                avpar.अङ्कः, avpar.den,
                0xFFFFFFFF);

    अङ्कः = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.अङ्कः);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_कुञ्चिका_Call_Backs,
                                    &k_CFType_Dictionary_मानम्_Call_Backs);

    यदि (!par || !अङ्कः || !den) {
        यदि (par) CFRelease(par);
        यदि (अङ्कः) CFRelease(अङ्कः);
        यदि (den) CFRelease(den);
        प्रत्यागम AVERROR(ENOMEM);
    }

    CFDictionary_समुच्चयः_मानम्(
        par,
        k_CVImage_बफर_Pixel_Aspect_अनुपातः_Horizontal_Spacing_कुञ्चिका,
        अङ्कः);
    CFDictionary_समुच्चयः_मानम्(
        par,
        k_CVImage_बफर_Pixel_Aspect_अनुपातः_Vertical_Spacing_कुञ्चिका,
        den);

    CVBuffer_समुच्चयः_Attachment(
        pixbuf,
        k_CVImage_बफर_Pixel_Aspect_अनुपातः_कुञ्चिका,
        par,
        k_CVAttachment_बहुलकम्_Should_Propagate
    );

    CFRelease(par);
    CFRelease(अङ्कः);
    CFRelease(den);

    प्रत्यागम 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(गणना AVChromaLocation loc)
{
    विकल्प (loc) {
    पक्ष AVCHROMA_LOC_वामः:
        प्रत्यागम k_CVImage_बफर_Chroma_Location_वामः;
    पक्ष AVCHROMA_LOC_CENTER:
        प्रत्यागम k_CVImage_बफर_Chroma_Location_Center;
    पक्ष AVCHROMA_LOC_शिखरम्:
        प्रत्यागम k_CVImage_बफर_Chroma_Location_शिखरम्;
    पक्ष AVCHROMA_LOC_BOTTOM:
        प्रत्यागम k_CVImage_बफर_Chroma_Location_Bottom;
    पक्ष AVCHROMA_LOC_TOPLEFT:
        प्रत्यागम k_CVImage_बफर_Chroma_Location_शिखरम्_वामः;
    पक्ष AVCHROMA_LOC_BOTTOMLEFT:
        प्रत्यागम k_CVImage_बफर_Chroma_Location_Bottom_वामः;
    स्वभाव:
        प्रत्यागम रिक्त;
    }
}

स्थिर पूर्णाङ्क vt_pixbuf_समुच्चयः_chromaloc(शून्य *log_ctx,
                                   CVPixel_बफर_Ref pixbuf, ध्रुव AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    यदि (loc) {
        CVBuffer_समुच्चयः_Attachment(
            pixbuf,
            k_CVImage_बफर_Chroma_Location_शिखरम्_क्षेत्रम्_कुञ्चिका,
            loc,
            k_CVAttachment_बहुलकम्_Should_Propagate);
    } अन्यथा
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_बफर_Chroma_Location_शिखरम्_क्षेत्रम्_कुञ्चिका);

    प्रत्यागम 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(गणना AVColorSpace space)
{
    विकल्प (space) {
    पक्ष AVCOL_SPC_BT2020_CL:
    पक्ष AVCOL_SPC_BT2020_NCL:
#यदि HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        यदि (__builtin_available(macOS 10.11, iOS 9, *))
            प्रत्यागम k_CVImage_बफर_YCb_Cr_Matrix_ITU_R_2020;
#यदि_अन्तः
        प्रत्यागम CFSTR("ITU_R_2020");
    पक्ष AVCOL_SPC_BT470BG:
    पक्ष AVCOL_SPC_SMPTE170M:
        प्रत्यागम k_CVImage_बफर_YCb_Cr_Matrix_ITU_R_601_4;
    पक्ष AVCOL_SPC_BT709:
        प्रत्यागम k_CVImage_बफर_YCb_Cr_Matrix_ITU_R_709_2;
    पक्ष AVCOL_SPC_SMPTE240M:
        प्रत्यागम k_CVImage_बफर_YCb_Cr_Matrix_SMPTE_240_M_1995;
    स्वभाव:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        यदि (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            प्रत्यागम CVYCb_Cr_Matrix_Get_String_For_Integer_संहिता_Point(space);
        av_fallthrough;
#यदि_अन्तः
    पक्ष AVCOL_SPC_UNSPECIFIED:
        प्रत्यागम रिक्त;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(गणना AVColorPrimaries pri)
{
    विकल्प (pri) {
    पक्ष AVCOL_PRI_BT2020:
#यदि HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        यदि (__builtin_available(macOS 10.11, iOS 9, *))
            प्रत्यागम k_CVImage_बफर_Color_Primaries_ITU_R_2020;
#यदि_अन्तः
        प्रत्यागम CFSTR("ITU_R_2020");
    पक्ष AVCOL_PRI_BT709:
        प्रत्यागम k_CVImage_बफर_Color_Primaries_ITU_R_709_2;
    पक्ष AVCOL_PRI_SMPTE170M:
        प्रत्यागम k_CVImage_बफर_Color_Primaries_SMPTE_C;
    पक्ष AVCOL_PRI_BT470BG:
        प्रत्यागम k_CVImage_बफर_Color_Primaries_EBU_3213;
    स्वभाव:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        यदि (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            प्रत्यागम CVColor_Primaries_Get_String_For_Integer_संहिता_Point(pri);
        av_fallthrough;
#यदि_अन्तः
    पक्ष AVCOL_PRI_UNSPECIFIED:
        प्रत्यागम रिक्त;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(गणना AVColorTransferCharacteristic trc)
{

    विकल्प (trc) {
    पक्ष AVCOL_TRC_SMPTE2084:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        यदि (__builtin_available(macOS 10.13, iOS 11, *))
            प्रत्यागम k_CVImage_बफर_Transfer_Function_SMPTE_ST_2084_PQ;
#यदि_अन्तः
        प्रत्यागम CFSTR("SMPTE_ST_2084_PQ");
    पक्ष AVCOL_TRC_BT2020_10:
    पक्ष AVCOL_TRC_BT2020_12:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        यदि (__builtin_available(macOS 10.11, iOS 9, *))
            प्रत्यागम k_CVImage_बफर_Transfer_Function_ITU_R_2020;
#यदि_अन्तः
        प्रत्यागम CFSTR("ITU_R_2020");
    पक्ष AVCOL_TRC_BT709:
        प्रत्यागम k_CVImage_बफर_Transfer_Function_ITU_R_709_2;
    पक्ष AVCOL_TRC_SMPTE240M:
        प्रत्यागम k_CVImage_बफर_Transfer_Function_SMPTE_240_M_1995;
    पक्ष AVCOL_TRC_SMPTE428:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        यदि (__builtin_available(macOS 10.12, iOS 10, *))
            प्रत्यागम k_CVImage_बफर_Transfer_Function_SMPTE_ST_428_1;
#यदि_अन्तः
        प्रत्यागम CFSTR("SMPTE_ST_428_1");
    पक्ष AVCOL_TRC_ARIB_STD_B67:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        यदि (__builtin_available(macOS 10.13, iOS 11, *))
            प्रत्यागम k_CVImage_बफर_Transfer_Function_ITU_R_2100_HLG;
#यदि_अन्तः
        प्रत्यागम CFSTR("ITU_R_2100_HLG");
    पक्ष AVCOL_TRC_GAMMA22:
        प्रत्यागम k_CVImage_बफर_Transfer_Function_Use_Gamma;
    पक्ष AVCOL_TRC_GAMMA28:
        प्रत्यागम k_CVImage_बफर_Transfer_Function_Use_Gamma;
    स्वभाव:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        यदि (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            प्रत्यागम CVTransfer_Function_Get_String_For_Integer_संहिता_Point(trc);
        av_fallthrough;
#यदि_अन्तः
    पक्ष AVCOL_TRC_UNSPECIFIED:
        प्रत्यागम रिक्त;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
स्थिर CFDictionaryRef vt_cv_बफर_copy_attachments(CVBufferRef बफर,
                                                     CVAttachment_बहुलकम् attachment_बहुलकम्)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #यदि (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        यदि (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            प्रत्यागम CVBufferCopyAttachments(बफर, attachment_बहुलकम्);
    #यदि_अन्तः

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #यदि (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(बफर, attachment_बहुलकम्);
        प्रत्यागम (dict) ? CFDictionaryCreateCopy(रिक्त, dict) : रिक्त;
    #अन्यथा
        प्रत्यागम रिक्त; // Impossible, just make the compiler happy
    #यदि_अन्तः
}

स्थिर पूर्णाङ्क vt_pixbuf_समुच्चयः_colorspace(शून्य *log_ctx,
                                    CVPixel_बफर_Ref pixbuf, ध्रुव AVFrame *src)
{
    CGColorSpaceRef colorspace = रिक्त;
    CFStringRef colormatrix = रिक्त, colorpri = रिक्त, colortrc = रिक्त;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    यदि (colormatrix)
        CVBuffer_समुच्चयः_Attachment(pixbuf, k_CVImage_बफर_YCb_Cr_Matrix_कुञ्चिका,
            colormatrix, k_CVAttachment_बहुलकम्_Should_Propagate);
    अन्यथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_बफर_YCb_Cr_Matrix_कुञ्चिका);
        यदि (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    यदि (colorpri)
        CVBuffer_समुच्चयः_Attachment(pixbuf, k_CVImage_बफर_Color_Primaries_कुञ्चिका,
            colorpri, k_CVAttachment_बहुलकम्_Should_Propagate);
    अन्यथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_बफर_Color_Primaries_कुञ्चिका);
        यदि (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    यदि (colortrc)
        CVBuffer_समुच्चयः_Attachment(pixbuf, k_CVImage_बफर_Transfer_Function_कुञ्चिका,
            colortrc, k_CVAttachment_बहुलकम्_Should_Propagate);
    अन्यथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_बफर_Transfer_Function_कुञ्चिका);
        यदि (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    यदि (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    अन्यथा यदि (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    यदि (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(रिक्त, kCFNumberFloat32Type, &gamma);
        CVBuffer_समुच्चयः_Attachment(pixbuf, k_CVImage_बफर_Gamma_Level_कुञ्चिका,
            gamma_level, k_CVAttachment_बहुलकम्_Should_Propagate);
        CFRelease(gamma_level);
    } अन्यथा
        CVBufferRemoveAttachment(pixbuf, k_CVImage_बफर_Gamma_Level_कुञ्चिका);

#यदि (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    यदि (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_बफर_copy_attachments(pixbuf, k_CVAttachment_बहुलकम्_Should_Propagate);

        यदि (attachments) {
            colorspace =
                CVImage_बफर_Create_Color_Space_From_Attachments(attachments);
            CFRelease(attachments);
        }
    }
#यदि_अन्तः

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    यदि (colorspace) {
        CVBuffer_समुच्चयः_Attachment(pixbuf, k_CVImage_बफर_CGColor_Space_कुञ्चिका,
            colorspace, k_CVAttachment_बहुलकम्_Should_Propagate);
        CFRelease(colorspace);
    } अन्यथा
        CVBufferRemoveAttachment(pixbuf, k_CVImage_बफर_CGColor_Space_कुञ्चिका);

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vt_pixbuf_समुच्चयः_attachments(शून्य *log_ctx,
                                     CVPixel_बफर_Ref pixbuf, ध्रुव AVFrame *src)
{
    पूर्णाङ्क ret;
    ret = vt_pixbuf_समुच्चयः_par(log_ctx, pixbuf, src);
    यदि (ret < 0)
        प्रत्यागम ret;
    ret = vt_pixbuf_समुच्चयः_colorspace(log_ctx, pixbuf, src);
    यदि (ret < 0)
        प्रत्यागम ret;
    ret = vt_pixbuf_समुच्चयः_chromaloc(log_ctx, pixbuf, src);
    यदि (ret < 0)
        प्रत्यागम ret;
    प्रत्यागम 0;
}

पूर्णाङ्क av_vt_pixbuf_समुच्चयः_attachments(शून्य *log_ctx,
                                 CVPixel_बफर_Ref pixbuf, ध्रुव AVFrame *src)
{
    प्रत्यागम vt_pixbuf_समुच्चयः_attachments(log_ctx, pixbuf, src);
}

स्थिर पूर्णाङ्क vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, ध्रुव AVFrame *src,
                        पूर्णाङ्क flags)
{
    CVPixel_बफर_Ref pixbuf = (CVPixel_बफर_Ref)src->दत्त[3];
    OSType pixel_format = CVPixel_बफर_Get_Pixel_Format_Type(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    पूर्णाङ्क ret;
    पूर्णाङ्क i;
    गणना AVPixelFormat format;

    format = av_map_videotoolbox_format_गन्तव्यम्_pixfmt(pixel_format);
    यदि (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        प्रत्यागम AVERROR_UNKNOWN;
    }

    यदि (CVPixel_बफर_Get_विस्तारः(pixbuf) != ctx->विस्तारः ||
        CVPixel_बफर_Get_Height(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    यदि (flags == AV_HWFRAME_MAP_READ)
        map_flags = k_CVPixel_बफर_तालकम्_Read_Only;

    err = CVPixel_बफर_तालकम्_आधारः_स्थानाङ्कः(pixbuf, map_flags);
    यदि (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    यदि (CVPixel_बफर_Is_Planar(pixbuf)) {
        पूर्णाङ्क planes = CVPixel_बफर_Get_Plane_गणनम्(pixbuf);
        प्रति (i = 0; i < planes; i++) {
            dst->दत्त[i]     = CVPixel_बफर_Get_आधारः_स्थानाङ्कः_सम्बन्धि_Plane(pixbuf, i);
            dst->linesize[i] = CVPixel_बफर_Get_अष्टकानि_प्रत्येकम्_Row_सम्बन्धि_Plane(pixbuf, i);
        }
    } अन्यथा {
        dst->दत्त[0]     = CVPixel_बफर_Get_आधारः_स्थानाङ्कः(pixbuf);
        dst->linesize[0] = CVPixel_बफर_Get_अष्टकानि_प्रत्येकम्_Row(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_चौकटाः_ctx, dst, src, vt_unmap,
                                (शून्य *)(uintptr_t)map_flags);
    यदि (ret < 0)
        गच्छ unlock;

    प्रत्यागम 0;

unlock:
    CVPixel_बफर_Unlock_आधारः_स्थानाङ्कः(pixbuf, map_flags);
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क vt_transfer_दत्त_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, ध्रुव AVFrame *src)
{
    AVFrame *map;
    पूर्णाङ्क err;

    यदि (dst->विस्तारः > hwfc->विस्तारः || dst->height > hwfc->height)
        प्रत्यागम AVERROR(EINVAL);

    map = av_frame_alloc();
    यदि (!map)
        प्रत्यागम AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    यदि (err)
        गच्छ fail;

    map->विस्तारः  = dst->विस्तारः;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    यदि (err)
        गच्छ fail;

    err = 0;
fail:
    av_frame_free(&map);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क vt_transfer_दत्त_गन्तव्यम्(AVHWFramesContext *hwfc,
                               AVFrame *dst, ध्रुव AVFrame *src)
{
    AVFrame *map;
    पूर्णाङ्क err;

    यदि (src->विस्तारः > hwfc->विस्तारः || src->height > hwfc->height)
        प्रत्यागम AVERROR(EINVAL);

    map = av_frame_alloc();
    यदि (!map)
        प्रत्यागम AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    यदि (err)
        गच्छ fail;

    map->विस्तारः  = src->विस्तारः;
    map->height = src->height;

    err = av_frame_copy(map, src);
    यदि (err)
        गच्छ fail;

    err = vt_pixbuf_समुच्चयः_attachments(hwfc, (CVPixel_बफर_Ref)dst->दत्त[3], src);
    यदि (err)
        गच्छ fail;

    err = 0;
fail:
    av_frame_free(&map);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    पूर्णाङ्क err;

    यदि (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    अन्यथा यदि (dst->format != hwfc->sw_format)
        प्रत्यागम AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    यदि (err)
        प्रत्यागम err;

    dst->विस्तारः  = src->विस्तारः;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    यदि (err)
        प्रत्यागम err;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vt_device_create(AVHWDeviceContext *ctx, ध्रुव वर्ण *device,
                            AVDictionary *opts, पूर्णाङ्क flags)
{
    यदि (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रत्यागम 0;
}

ध्रुव HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .चौकटाः_hwctx_आकार    = परिमाण(VTFramesContext),

    .device_create        = vt_device_create,
    .चौकटाः_init          = vt_चौकटाः_init,
    .चौकटाः_get_बफर    = vt_get_बफर,
    .चौकटाः_get_constraints = vt_चौकटाः_get_constraints,
    .चौकटाः_uninit        = vt_चौकटाः_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_दत्त_गन्तव्यम्     = vt_transfer_दत्त_गन्तव्यम्,
    .transfer_दत्त_from   = vt_transfer_दत्त_from,
    .map_from             = vt_map_from,

    .pix_fmts = (ध्रुव गणना AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
