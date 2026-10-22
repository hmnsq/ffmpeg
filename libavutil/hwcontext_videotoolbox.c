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

प्रकारव्याख्या संरचना VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixelBufferPoolRef pool;
} VTFramesContext;

स्थिर स्थिरांक संरचना {
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
#जर HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#जर HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#जर HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#जर HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#जर HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#जर HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#जर HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#जर HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#endif
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

स्थिर स्थिरांक गणना AVPixelFormat supported_formats[] = {
#ifdef kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#endif
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#जर HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#जर HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#जर HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#जर HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#जर HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#जर HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#जर HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#जर HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#endif
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

स्थिर पूर्णांक vt_frames_get_constraints(AVHWDeviceContext *ctx,
                                     स्थिरांक शून्य *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    पूर्णांक i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    आकार(*constraints->valid_sw_formats));
    जर (!constraints->valid_sw_formats)
        परत AVERROR(ENOMEM);

    साठी (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, आकार(*constraints->valid_hw_formats));
    जर (!constraints->valid_hw_formats)
        परत AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    परत 0;
}

गणना AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    पूर्णांक i;
    साठी (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        जर (cv_pix_fmts[i].cv_fmt == cv_fmt)
            परत cv_pix_fmts[i].pix_fmt;
    }
    परत AV_PIX_FMT_NONE;
}

स्थिर uint32_t vt_format_from_pixfmt(गणना AVPixelFormat pix_fmt,
                                      गणना AVColorRange range)
{
    साठी (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        जर (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            पूर्णांक full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            जर (range == AVCOL_RANGE_UNSPECIFIED)
                परत cv_pix_fmts[i].cv_fmt;

            जर (cv_pix_fmts[i].full_range == full_range)
                परत cv_pix_fmts[i].cv_fmt;
        }
    }

    परत 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(गणना AVPixelFormat pix_fmt)
{
    परत av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(गणना AVPixelFormat pix_fmt, bool full_range)
{
    परत vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

स्थिर पूर्णांक vt_pool_alloc(AVHWFramesContext *ctx)
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
        &k_CFType_Dictionary_किल्ली_Call_Backs,
        &k_CFType_Dictionary_मूल्य_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(रिक्त, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_Set_मूल्य(
        attributes,
        k_CVPixel_Buffer_Pixel_Format_Type_किल्ली,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        रिक्त,
        0,
        &k_CFType_Dictionary_किल्ली_Call_Backs,
        &k_CFType_Dictionary_मूल्य_Call_Backs);
    CFDictionary_Set_मूल्य(attributes, k_CVPixel_Buffer_IOSurface_Properties_किल्ली, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(रिक्त, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(रिक्त, kCFNumberSInt32Type, &ctx->height);
    CFDictionary_Set_मूल्य(attributes, k_CVPixel_Buffer_Width_किल्ली, w);
    CFDictionary_Set_मूल्य(attributes, k_CVPixel_Buffer_Height_किल्ली, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixelBufferPoolCreate(
        रिक्त,
        रिक्त,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    जर (err == kCVReturnSuccess)
        परत 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    परत AVERROR_EXTERNAL;
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
    जर (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        परत रिक्त;
    }

    buf = av_buffer_create((uint8_t *)pixbuf, size,
                           videotoolbox_buffer_release, रिक्त, 0);
    जर (!buf) {
        CVPixelBufferRelease(pixbuf);
        परत रिक्त;
    }
    परत buf;
}

स्थिर शून्य vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    जर (fctx->pool) {
        CVPixelBufferPoolRelease(fctx->pool);
        fctx->pool = रिक्त;
    }
}

स्थिर पूर्णांक vt_frames_init(AVHWFramesContext *ctx)
{
    पूर्णांक i, ret;

    साठी (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        जर (ctx->sw_format == supported_formats[i])
            थांबा;
    }
    जर (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        परत AVERROR(ENOSYS);
    }

    जर (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(
                आकार(CVPixelBufferRef), ctx, vt_pool_alloc_buffer, रिक्त);
        जर (!ffhwframesctx(ctx)->pool_internal)
            परत AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    जर (ret < 0)
        परत ret;

    परत 0;
}

स्थिर पूर्णांक vt_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    जर (!frame->buf[0])
        परत AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    परत 0;
}

स्थिर पूर्णांक vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   गणना AVHWFrameTransferDirection dir,
                                   गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts = av_malloc_array(2, आकार(*fmts));
    जर (!fmts)
        परत AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    परत 0;
}

स्थिर शून्य vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)hwmap->source->data[3];

    CVPixelBufferUnlockBaseAddress(pixbuf, (uintptr_t)hwmap->priv);
}

स्थिर पूर्णांक vt_pixbuf_set_par(शून्य *log_ctx,
                             CVPixelBufferRef pixbuf, स्थिरांक AVFrame *src)
{
    CFMutableDictionaryRef par = रिक्त;
    CFNumberRef अंक = रिक्त, den = रिक्त;
    AVRational avpar = src->sample_aspect_ratio;

    जर (avpar.अंक == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Pixel_Aspect_Ratio_किल्ली);
        परत 0;
    }

    av_reduce(&avpar.अंक, &avpar.den,
                avpar.अंक, avpar.den,
                0xFFFFFFFF);

    अंक = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.अंक);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_किल्ली_Call_Backs,
                                    &k_CFType_Dictionary_मूल्य_Call_Backs);

    जर (!par || !अंक || !den) {
        जर (par) CFRelease(par);
        जर (अंक) CFRelease(अंक);
        जर (den) CFRelease(den);
        परत AVERROR(ENOMEM);
    }

    CFDictionary_Set_मूल्य(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Horizontal_Spacing_किल्ली,
        अंक);
    CFDictionary_Set_मूल्य(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Vertical_Spacing_किल्ली,
        den);

    CVBufferSetAttachment(
        pixbuf,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_किल्ली,
        par,
        kCVAttachmentMode_ShouldPropagate
    );

    CFRelease(par);
    CFRelease(अंक);
    CFRelease(den);

    परत 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(गणना AVChromaLocation loc)
{
    निवड (loc) {
    स्थिती AVCHROMA_LOC_डावा:
        परत k_CVImage_Buffer_Chroma_Location_डावा;
    स्थिती AVCHROMA_LOC_CENTER:
        परत kCVImageBufferChromaLocation_Center;
    स्थिती AVCHROMA_LOC_शीर्ष:
        परत k_CVImage_Buffer_Chroma_Location_शीर्ष;
    स्थिती AVCHROMA_LOC_BOTTOM:
        परत kCVImageBufferChromaLocation_Bottom;
    स्थिती AVCHROMA_LOC_TOPLEFT:
        परत k_CVImage_Buffer_Chroma_Location_शीर्ष_डावा;
    स्थिती AVCHROMA_LOC_BOTTOMLEFT:
        परत k_CVImage_Buffer_Chroma_Location_Bottom_डावा;
    पूर्वनिर्धारित:
        परत रिक्त;
    }
}

स्थिर पूर्णांक vt_pixbuf_set_chromaloc(शून्य *log_ctx,
                                   CVPixelBufferRef pixbuf, स्थिरांक AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    जर (loc) {
        CVBufferSetAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_शीर्ष_Field_किल्ली,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } अन्यथा
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_शीर्ष_Field_किल्ली);

    परत 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(गणना AVColorSpace space)
{
    निवड (space) {
    स्थिती AVCOL_SPC_BT2020_CL:
    स्थिती AVCOL_SPC_BT2020_NCL:
#जर HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        जर (__builtin_available(macOS 10.11, iOS 9, *))
            परत kCVImageBufferYCbCrMatrix_ITU_R_2020;
#endif
        परत CFSTR("ITU_R_2020");
    स्थिती AVCOL_SPC_BT470BG:
    स्थिती AVCOL_SPC_SMPTE170M:
        परत kCVImageBufferYCbCrMatrix_ITU_R_601_4;
    स्थिती AVCOL_SPC_BT709:
        परत kCVImageBufferYCbCrMatrix_ITU_R_709_2;
    स्थिती AVCOL_SPC_SMPTE240M:
        परत kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
    पूर्वनिर्धारित:
#जर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        जर (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            परत CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
    स्थिती AVCOL_SPC_UNSPECIFIED:
        परत रिक्त;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(गणना AVColorPrimaries pri)
{
    निवड (pri) {
    स्थिती AVCOL_PRI_BT2020:
#जर HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        जर (__builtin_available(macOS 10.11, iOS 9, *))
            परत kCVImageBufferColorPrimaries_ITU_R_2020;
#endif
        परत CFSTR("ITU_R_2020");
    स्थिती AVCOL_PRI_BT709:
        परत kCVImageBufferColorPrimaries_ITU_R_709_2;
    स्थिती AVCOL_PRI_SMPTE170M:
        परत kCVImageBufferColorPrimaries_SMPTE_C;
    स्थिती AVCOL_PRI_BT470BG:
        परत kCVImageBufferColorPrimaries_EBU_3213;
    पूर्वनिर्धारित:
#जर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        जर (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            परत CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
    स्थिती AVCOL_PRI_UNSPECIFIED:
        परत रिक्त;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(गणना AVColorTransferCharacteristic trc)
{

    निवड (trc) {
    स्थिती AVCOL_TRC_SMPTE2084:
#जर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        जर (__builtin_available(macOS 10.13, iOS 11, *))
            परत kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
#endif
        परत CFSTR("SMPTE_ST_2084_PQ");
    स्थिती AVCOL_TRC_BT2020_10:
    स्थिती AVCOL_TRC_BT2020_12:
#जर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        जर (__builtin_available(macOS 10.11, iOS 9, *))
            परत kCVImageBufferTransferFunction_ITU_R_2020;
#endif
        परत CFSTR("ITU_R_2020");
    स्थिती AVCOL_TRC_BT709:
        परत kCVImageBufferTransferFunction_ITU_R_709_2;
    स्थिती AVCOL_TRC_SMPTE240M:
        परत kCVImageBufferTransferFunction_SMPTE_240M_1995;
    स्थिती AVCOL_TRC_SMPTE428:
#जर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        जर (__builtin_available(macOS 10.12, iOS 10, *))
            परत kCVImageBufferTransferFunction_SMPTE_ST_428_1;
#endif
        परत CFSTR("SMPTE_ST_428_1");
    स्थिती AVCOL_TRC_ARIB_STD_B67:
#जर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        जर (__builtin_available(macOS 10.13, iOS 11, *))
            परत kCVImageBufferTransferFunction_ITU_R_2100_HLG;
#endif
        परत CFSTR("ITU_R_2100_HLG");
    स्थिती AVCOL_TRC_GAMMA22:
        परत kCVImageBufferTransferFunction_UseGamma;
    स्थिती AVCOL_TRC_GAMMA28:
        परत kCVImageBufferTransferFunction_UseGamma;
    पूर्वनिर्धारित:
#जर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        जर (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            परत CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    स्थिती AVCOL_TRC_UNSPECIFIED:
        परत रिक्त;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
स्थिर CFDictionaryRef vt_cv_buffer_copy_attachments(CVBufferRef buffer,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #जर (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        जर (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            परत CVBufferCopyAttachments(buffer, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #जर (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(buffer, attachment_mode);
        परत (dict) ? CFDictionaryCreateCopy(रिक्त, dict) : रिक्त;
    #अन्यथा
        परत रिक्त; // Impossible, just make the compiler happy
    #endif
}

स्थिर पूर्णांक vt_pixbuf_set_colorspace(शून्य *log_ctx,
                                    CVPixelBufferRef pixbuf, स्थिरांक AVFrame *src)
{
    CGColorSpaceRef colorspace = रिक्त;
    CFStringRef colormatrix = रिक्त, colorpri = रिक्त, colortrc = रिक्त;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    जर (colormatrix)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_किल्ली,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    अन्यथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_किल्ली);
        जर (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    जर (colorpri)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_किल्ली,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    अन्यथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_किल्ली);
        जर (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    जर (colortrc)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_किल्ली,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    अन्यथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_किल्ली);
        जर (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    जर (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    अन्यथा जर (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    जर (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(रिक्त, kCFNumberFloat32Type, &gamma);
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_किल्ली,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } अन्यथा
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_किल्ली);

#जर (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    जर (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_buffer_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        जर (attachments) {
            colorspace =
                CVImageBufferCreateColorSpaceFromAttachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    जर (colorspace) {
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_किल्ली,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } अन्यथा
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_किल्ली);

    परत 0;
}

स्थिर पूर्णांक vt_pixbuf_set_attachments(शून्य *log_ctx,
                                     CVPixelBufferRef pixbuf, स्थिरांक AVFrame *src)
{
    पूर्णांक ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    जर (ret < 0)
        परत ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    जर (ret < 0)
        परत ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    जर (ret < 0)
        परत ret;
    परत 0;
}

पूर्णांक av_vt_pixbuf_set_attachments(शून्य *log_ctx,
                                 CVPixelBufferRef pixbuf, स्थिरांक AVFrame *src)
{
    परत vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

स्थिर पूर्णांक vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, स्थिरांक AVFrame *src,
                        पूर्णांक flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)src->data[3];
    OSType pixel_format = CVPixelBufferGetPixelFormatType(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    पूर्णांक ret;
    पूर्णांक i;
    गणना AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    जर (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        परत AVERROR_UNKNOWN;
    }

    जर (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        परत AVERROR_UNKNOWN;
    }

    जर (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    जर (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        परत AVERROR_UNKNOWN;
    }

    जर (CVPixelBufferIsPlanar(pixbuf)) {
        पूर्णांक planes = CVPixel_Buffer_Get_Plane_मोजणी(pixbuf);
        साठी (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } अन्यथा {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (शून्य *)(uintptr_t)map_flags);
    जर (ret < 0)
        जा unlock;

    परत 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    परत ret;
}

स्थिर पूर्णांक vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, स्थिरांक AVFrame *src)
{
    AVFrame *map;
    पूर्णांक err;

    जर (dst->width > hwfc->width || dst->height > hwfc->height)
        परत AVERROR(EINVAL);

    map = av_frame_alloc();
    जर (!map)
        परत AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    जर (err)
        जा fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    जर (err)
        जा fail;

    err = 0;
fail:
    av_frame_free(&map);
    परत err;
}

स्थिर पूर्णांक vt_transfer_data_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, स्थिरांक AVFrame *src)
{
    AVFrame *map;
    पूर्णांक err;

    जर (src->width > hwfc->width || src->height > hwfc->height)
        परत AVERROR(EINVAL);

    map = av_frame_alloc();
    जर (!map)
        परत AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    जर (err)
        जा fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    जर (err)
        जा fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixelBufferRef)dst->data[3], src);
    जर (err)
        जा fail;

    err = 0;
fail:
    av_frame_free(&map);
    परत err;
}

स्थिर पूर्णांक vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       स्थिरांक AVFrame *src, पूर्णांक flags)
{
    पूर्णांक err;

    जर (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    अन्यथा जर (dst->format != hwfc->sw_format)
        परत AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    जर (err)
        परत err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    जर (err)
        परत err;

    परत 0;
}

स्थिर पूर्णांक vt_device_create(AVHWDeviceContext *ctx, स्थिरांक अक्षर *device,
                            AVDictionary *opts, पूर्णांक flags)
{
    जर (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        परत AVERROR_UNKNOWN;
    }

    परत 0;
}

स्थिरांक HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .frames_hwctx_size    = आकार(VTFramesContext),

    .device_create        = vt_device_create,
    .frames_init          = vt_frames_init,
    .frames_get_buffer    = vt_get_buffer,
    .frames_get_constraints = vt_frames_get_constraints,
    .frames_uninit        = vt_frames_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_data_to     = vt_transfer_data_to,
    .transfer_data_from   = vt_transfer_data_from,
    .map_from             = vt_map_from,

    .pix_fmts = (स्थिरांक गणना AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
