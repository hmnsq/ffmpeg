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
    CVPixelBufferPoolRef pool;
} VTFramesContext;

स्थिर अचर संरचना {
    uint32_t cv_fmt;
    bool full_range;
    गणना AVPixelFormat pix_fmt;
} cv_pix_fmts[] = {
    { kCVPixelFormatType_420YpCbCr8Planar,              false, AV_PIX_FMT_YUV420P },
    { kCVPixelFormatType_420YpCbCr8PlanarFullRange,     true,  AV_PIX_FMT_YUV420P },
    { kCVPixelFormatType_422YpCbCr8,                    false, AV_PIX_FMT_UYVY422 },
    { kCVPixelFormatType_32BGRA,                        true,  AV_PIX_FMT_BGRA },
#ifdef kCFCoreFoundationVersionNumber10_7
    { kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV12 },
    { kCVPixelFormatType_420YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV12 },
    { kCVPixelFormatType_4444AYpCbCr8,                  false, AV_PIX_FMT_AYUV },
    { kCVPixelFormatType_4444AYpCbCr16,                 false, AV_PIX_FMT_AYUV64 },
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#endif
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

स्थिर अचर गणना AVPixelFormat supported_formats[] = {
#ifdef kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#endif
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#यदि HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#यदि HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#endif
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

स्थिर पूर्णाङ्क vt_frames_get_constraints(AVHWDeviceContext *ctx,
                                     अचर शून्य *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    पूर्णाङ्क i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    परिमाण(*constraints->valid_sw_formats));
    यदि (!constraints->valid_sw_formats)
        फर्काऊ AVERROR(ENOMEM);

    लागि (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, परिमाण(*constraints->valid_hw_formats));
    यदि (!constraints->valid_hw_formats)
        फर्काऊ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    फर्काऊ 0;
}

गणना AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    पूर्णाङ्क i;
    लागि (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        यदि (cv_pix_fmts[i].cv_fmt == cv_fmt)
            फर्काऊ cv_pix_fmts[i].pix_fmt;
    }
    फर्काऊ AV_PIX_FMT_NONE;
}

स्थिर uint32_t vt_format_from_pixfmt(गणना AVPixelFormat pix_fmt,
                                      गणना AVColorRange range)
{
    लागि (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        यदि (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            पूर्णाङ्क full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            यदि (range == AVCOL_RANGE_UNSPECIFIED)
                फर्काऊ cv_pix_fmts[i].cv_fmt;

            यदि (cv_pix_fmts[i].full_range == full_range)
                फर्काऊ cv_pix_fmts[i].cv_fmt;
        }
    }

    फर्काऊ 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(गणना AVPixelFormat pix_fmt)
{
    फर्काऊ av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(गणना AVPixelFormat pix_fmt, bool full_range)
{
    फर्काऊ vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

स्थिर पूर्णाङ्क vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef attributes, iosurface_properties;

    attributes = CFDictionaryCreateMutable(
        रिक्त,
        2,
        &k_CFType_Dictionary_साँचो_Call_Backs,
        &k_CFType_Dictionary_मान_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(रिक्त, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_Set_मान(
        attributes,
        k_CVPixel_Buffer_Pixel_Format_Type_साँचो,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        रिक्त,
        0,
        &k_CFType_Dictionary_साँचो_Call_Backs,
        &k_CFType_Dictionary_मान_Call_Backs);
    CFDictionary_Set_मान(attributes, k_CVPixel_Buffer_IOSurface_Properties_साँचो, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(रिक्त, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(रिक्त, kCFNumberSInt32Type, &ctx->height);
    CFDictionary_Set_मान(attributes, k_CVPixel_Buffer_Width_साँचो, w);
    CFDictionary_Set_मान(attributes, k_CVPixel_Buffer_Height_साँचो, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixelBufferPoolCreate(
        रिक्त,
        रिक्त,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    यदि (err == kCVReturnSuccess)
        फर्काऊ 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    फर्काऊ AVERROR_EXTERNAL;
}

स्थिर शून्य videotoolbox_buffer_release(शून्य *opaque, uint8_t *data)
{
    CVPixelBufferRelease((CVPixelBufferRef)data);
}

स्थिर AVBufferRef *vt_pool_alloc_buffer(शून्य *opaque, माप_प्रकार size)
{
    CVPixelBufferRef pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixelBufferPoolCreatePixelBuffer(
        रिक्त,
        fctx->pool,
        &pixbuf
    );
    यदि (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        फर्काऊ रिक्त;
    }

    buf = av_buffer_create((uint8_t *)pixbuf, size,
                           videotoolbox_buffer_release, रिक्त, 0);
    यदि (!buf) {
        CVPixelBufferRelease(pixbuf);
        फर्काऊ रिक्त;
    }
    फर्काऊ buf;
}

स्थिर शून्य vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    यदि (fctx->pool) {
        CVPixelBufferPoolRelease(fctx->pool);
        fctx->pool = रिक्त;
    }
}

स्थिर पूर्णाङ्क vt_frames_init(AVHWFramesContext *ctx)
{
    पूर्णाङ्क i, ret;

    लागि (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        यदि (ctx->sw_format == supported_formats[i])
            रोक;
    }
    यदि (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        फर्काऊ AVERROR(ENOSYS);
    }

    यदि (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(
                परिमाण(CVPixelBufferRef), ctx, vt_pool_alloc_buffer, रिक्त);
        यदि (!ffhwframesctx(ctx)->pool_internal)
            फर्काऊ AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    यदि (ret < 0)
        फर्काऊ ret;

    फर्काऊ 0;
}

स्थिर पूर्णाङ्क vt_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    यदि (!frame->buf[0])
        फर्काऊ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    फर्काऊ 0;
}

स्थिर पूर्णाङ्क vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   गणना AVHWFrameTransferDirection dir,
                                   गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts = av_malloc_array(2, परिमाण(*fmts));
    यदि (!fmts)
        फर्काऊ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    फर्काऊ 0;
}

स्थिर शून्य vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)hwmap->source->data[3];

    CVPixelBufferUnlockBaseAddress(pixbuf, (uintptr_t)hwmap->priv);
}

स्थिर पूर्णाङ्क vt_pixbuf_set_par(शून्य *log_ctx,
                             CVPixelBufferRef pixbuf, अचर AVFrame *src)
{
    CFMutableDictionaryRef par = रिक्त;
    CFNumberRef अङ्क = रिक्त, den = रिक्त;
    AVRational avpar = src->sample_aspect_ratio;

    यदि (avpar.अङ्क == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Pixel_Aspect_Ratio_साँचो);
        फर्काऊ 0;
    }

    av_reduce(&avpar.अङ्क, &avpar.den,
                avpar.अङ्क, avpar.den,
                0xFFFFFFFF);

    अङ्क = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.अङ्क);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_साँचो_Call_Backs,
                                    &k_CFType_Dictionary_मान_Call_Backs);

    यदि (!par || !अङ्क || !den) {
        यदि (par) CFRelease(par);
        यदि (अङ्क) CFRelease(अङ्क);
        यदि (den) CFRelease(den);
        फर्काऊ AVERROR(ENOMEM);
    }

    CFDictionary_Set_मान(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Horizontal_Spacing_साँचो,
        अङ्क);
    CFDictionary_Set_मान(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Vertical_Spacing_साँचो,
        den);

    CVBufferSetAttachment(
        pixbuf,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_साँचो,
        par,
        kCVAttachmentMode_ShouldPropagate
    );

    CFRelease(par);
    CFRelease(अङ्क);
    CFRelease(den);

    फर्काऊ 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(गणना AVChromaLocation loc)
{
    विकल्प (loc) {
    पक्ष AVCHROMA_LOC_बायाँ:
        फर्काऊ k_CVImage_Buffer_Chroma_Location_बायाँ;
    पक्ष AVCHROMA_LOC_CENTER:
        फर्काऊ kCVImageBufferChromaLocation_Center;
    पक्ष AVCHROMA_LOC_शीर्ष:
        फर्काऊ k_CVImage_Buffer_Chroma_Location_शीर्ष;
    पक्ष AVCHROMA_LOC_BOTTOM:
        फर्काऊ kCVImageBufferChromaLocation_Bottom;
    पक्ष AVCHROMA_LOC_TOPLEFT:
        फर्काऊ k_CVImage_Buffer_Chroma_Location_शीर्ष_बायाँ;
    पक्ष AVCHROMA_LOC_BOTTOMLEFT:
        फर्काऊ k_CVImage_Buffer_Chroma_Location_Bottom_बायाँ;
    स्वभाव:
        फर्काऊ रिक्त;
    }
}

स्थिर पूर्णाङ्क vt_pixbuf_set_chromaloc(शून्य *log_ctx,
                                   CVPixelBufferRef pixbuf, अचर AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    यदि (loc) {
        CVBufferSetAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_शीर्ष_Field_साँचो,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } अन्यथा
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_शीर्ष_Field_साँचो);

    फर्काऊ 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(गणना AVColorSpace space)
{
    विकल्प (space) {
    पक्ष AVCOL_SPC_BT2020_CL:
    पक्ष AVCOL_SPC_BT2020_NCL:
#यदि HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        यदि (__builtin_available(macOS 10.11, iOS 9, *))
            फर्काऊ kCVImageBufferYCbCrMatrix_ITU_R_2020;
#endif
        फर्काऊ CFSTR("ITU_R_2020");
    पक्ष AVCOL_SPC_BT470BG:
    पक्ष AVCOL_SPC_SMPTE170M:
        फर्काऊ kCVImageBufferYCbCrMatrix_ITU_R_601_4;
    पक्ष AVCOL_SPC_BT709:
        फर्काऊ kCVImageBufferYCbCrMatrix_ITU_R_709_2;
    पक्ष AVCOL_SPC_SMPTE240M:
        फर्काऊ kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
    स्वभाव:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        यदि (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            फर्काऊ CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
    पक्ष AVCOL_SPC_UNSPECIFIED:
        फर्काऊ रिक्त;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(गणना AVColorPrimaries pri)
{
    विकल्प (pri) {
    पक्ष AVCOL_PRI_BT2020:
#यदि HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        यदि (__builtin_available(macOS 10.11, iOS 9, *))
            फर्काऊ kCVImageBufferColorPrimaries_ITU_R_2020;
#endif
        फर्काऊ CFSTR("ITU_R_2020");
    पक्ष AVCOL_PRI_BT709:
        फर्काऊ kCVImageBufferColorPrimaries_ITU_R_709_2;
    पक्ष AVCOL_PRI_SMPTE170M:
        फर्काऊ kCVImageBufferColorPrimaries_SMPTE_C;
    पक्ष AVCOL_PRI_BT470BG:
        फर्काऊ kCVImageBufferColorPrimaries_EBU_3213;
    स्वभाव:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        यदि (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            फर्काऊ CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
    पक्ष AVCOL_PRI_UNSPECIFIED:
        फर्काऊ रिक्त;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(गणना AVColorTransferCharacteristic trc)
{

    विकल्प (trc) {
    पक्ष AVCOL_TRC_SMPTE2084:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        यदि (__builtin_available(macOS 10.13, iOS 11, *))
            फर्काऊ kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
#endif
        फर्काऊ CFSTR("SMPTE_ST_2084_PQ");
    पक्ष AVCOL_TRC_BT2020_10:
    पक्ष AVCOL_TRC_BT2020_12:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        यदि (__builtin_available(macOS 10.11, iOS 9, *))
            फर्काऊ kCVImageBufferTransferFunction_ITU_R_2020;
#endif
        फर्काऊ CFSTR("ITU_R_2020");
    पक्ष AVCOL_TRC_BT709:
        फर्काऊ kCVImageBufferTransferFunction_ITU_R_709_2;
    पक्ष AVCOL_TRC_SMPTE240M:
        फर्काऊ kCVImageBufferTransferFunction_SMPTE_240M_1995;
    पक्ष AVCOL_TRC_SMPTE428:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        यदि (__builtin_available(macOS 10.12, iOS 10, *))
            फर्काऊ kCVImageBufferTransferFunction_SMPTE_ST_428_1;
#endif
        फर्काऊ CFSTR("SMPTE_ST_428_1");
    पक्ष AVCOL_TRC_ARIB_STD_B67:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        यदि (__builtin_available(macOS 10.13, iOS 11, *))
            फर्काऊ kCVImageBufferTransferFunction_ITU_R_2100_HLG;
#endif
        फर्काऊ CFSTR("ITU_R_2100_HLG");
    पक्ष AVCOL_TRC_GAMMA22:
        फर्काऊ kCVImageBufferTransferFunction_UseGamma;
    पक्ष AVCOL_TRC_GAMMA28:
        फर्काऊ kCVImageBufferTransferFunction_UseGamma;
    स्वभाव:
#यदि HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        यदि (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            फर्काऊ CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    पक्ष AVCOL_TRC_UNSPECIFIED:
        फर्काऊ रिक्त;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
स्थिर CFDictionaryRef vt_cv_buffer_copy_attachments(CVBufferRef buffer,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #यदि (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        यदि (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            फर्काऊ CVBufferCopyAttachments(buffer, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #यदि (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(buffer, attachment_mode);
        फर्काऊ (dict) ? CFDictionaryCreateCopy(रिक्त, dict) : रिक्त;
    #अन्यथा
        फर्काऊ रिक्त; // Impossible, just make the compiler happy
    #endif
}

स्थिर पूर्णाङ्क vt_pixbuf_set_colorspace(शून्य *log_ctx,
                                    CVPixelBufferRef pixbuf, अचर AVFrame *src)
{
    CGColorSpaceRef colorspace = रिक्त;
    CFStringRef colormatrix = रिक्त, colorpri = रिक्त, colortrc = रिक्त;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    यदि (colormatrix)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_साँचो,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    अन्यथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_साँचो);
        यदि (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    यदि (colorpri)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_साँचो,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    अन्यथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_साँचो);
        यदि (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    यदि (colortrc)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_साँचो,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    अन्यथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_साँचो);
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
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_साँचो,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } अन्यथा
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_साँचो);

#यदि (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    यदि (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_buffer_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        यदि (attachments) {
            colorspace =
                CVImageBufferCreateColorSpaceFromAttachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    यदि (colorspace) {
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_साँचो,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } अन्यथा
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_साँचो);

    फर्काऊ 0;
}

स्थिर पूर्णाङ्क vt_pixbuf_set_attachments(शून्य *log_ctx,
                                     CVPixelBufferRef pixbuf, अचर AVFrame *src)
{
    पूर्णाङ्क ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    यदि (ret < 0)
        फर्काऊ ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    यदि (ret < 0)
        फर्काऊ ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    यदि (ret < 0)
        फर्काऊ ret;
    फर्काऊ 0;
}

पूर्णाङ्क av_vt_pixbuf_set_attachments(शून्य *log_ctx,
                                 CVPixelBufferRef pixbuf, अचर AVFrame *src)
{
    फर्काऊ vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

स्थिर पूर्णाङ्क vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, अचर AVFrame *src,
                        पूर्णाङ्क flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)src->data[3];
    OSType pixel_format = CVPixelBufferGetPixelFormatType(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    पूर्णाङ्क ret;
    पूर्णाङ्क i;
    गणना AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    यदि (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        फर्काऊ AVERROR_UNKNOWN;
    }

    यदि (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        फर्काऊ AVERROR_UNKNOWN;
    }

    यदि (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    यदि (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        फर्काऊ AVERROR_UNKNOWN;
    }

    यदि (CVPixelBufferIsPlanar(pixbuf)) {
        पूर्णाङ्क planes = CVPixel_Buffer_Get_Plane_गन्ती(pixbuf);
        लागि (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } अन्यथा {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (शून्य *)(uintptr_t)map_flags);
    यदि (ret < 0)
        गच्छ unlock;

    फर्काऊ 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    फर्काऊ ret;
}

स्थिर पूर्णाङ्क vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, अचर AVFrame *src)
{
    AVFrame *map;
    पूर्णाङ्क err;

    यदि (dst->width > hwfc->width || dst->height > hwfc->height)
        फर्काऊ AVERROR(EINVAL);

    map = av_frame_alloc();
    यदि (!map)
        फर्काऊ AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    यदि (err)
        गच्छ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    यदि (err)
        गच्छ fail;

    err = 0;
fail:
    av_frame_free(&map);
    फर्काऊ err;
}

स्थिर पूर्णाङ्क vt_transfer_data_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, अचर AVFrame *src)
{
    AVFrame *map;
    पूर्णाङ्क err;

    यदि (src->width > hwfc->width || src->height > hwfc->height)
        फर्काऊ AVERROR(EINVAL);

    map = av_frame_alloc();
    यदि (!map)
        फर्काऊ AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    यदि (err)
        गच्छ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    यदि (err)
        गच्छ fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixelBufferRef)dst->data[3], src);
    यदि (err)
        गच्छ fail;

    err = 0;
fail:
    av_frame_free(&map);
    फर्काऊ err;
}

स्थिर पूर्णाङ्क vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       अचर AVFrame *src, पूर्णाङ्क flags)
{
    पूर्णाङ्क err;

    यदि (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    अन्यथा यदि (dst->format != hwfc->sw_format)
        फर्काऊ AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    यदि (err)
        फर्काऊ err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    यदि (err)
        फर्काऊ err;

    फर्काऊ 0;
}

स्थिर पूर्णाङ्क vt_device_create(AVHWDeviceContext *ctx, अचर वर्ण *device,
                            AVDictionary *opts, पूर्णाङ्क flags)
{
    यदि (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        फर्काऊ AVERROR_UNKNOWN;
    }

    फर्काऊ 0;
}

अचर HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .frames_hwctx_size    = परिमाण(VTFramesContext),

    .device_create        = vt_device_create,
    .frames_init          = vt_frames_init,
    .frames_get_buffer    = vt_get_buffer,
    .frames_get_constraints = vt_frames_get_constraints,
    .frames_uninit        = vt_frames_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_data_to     = vt_transfer_data_to,
    .transfer_data_from   = vt_transfer_data_from,
    .map_from             = vt_map_from,

    .pix_fmts = (अचर गणना AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
