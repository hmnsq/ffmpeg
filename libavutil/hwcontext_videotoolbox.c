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

स्थिर ध्रुव संरचना {
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
#सचे HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#endif
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

स्थिर ध्रुव गणना AVPixelFormat supported_formats[] = {
#ifdef kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#endif
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#सचे HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#सचे HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#endif
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

स्थिर पूर्णाङ्क vt_frames_get_constraints(AVHWDeviceContext *ctx,
                                     ध्रुव शून्य *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    पूर्णाङ्क i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    परिमाण(*constraints->valid_sw_formats));
    सचे (!constraints->valid_sw_formats)
        पटिनिवत्त AVERROR(ENOMEM);

    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, परिमाण(*constraints->valid_hw_formats));
    सचे (!constraints->valid_hw_formats)
        पटिनिवत्त AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    पटिनिवत्त 0;
}

गणना AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    पूर्णाङ्क i;
    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        सचे (cv_pix_fmts[i].cv_fmt == cv_fmt)
            पटिनिवत्त cv_pix_fmts[i].pix_fmt;
    }
    पटिनिवत्त AV_PIX_FMT_NONE;
}

स्थिर uint32_t vt_format_from_pixfmt(गणना AVPixelFormat pix_fmt,
                                      गणना AVColorRange range)
{
    अत्थाय (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        सचे (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            पूर्णाङ्क full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            सचे (range == AVCOL_RANGE_UNSPECIFIED)
                पटिनिवत्त cv_pix_fmts[i].cv_fmt;

            सचे (cv_pix_fmts[i].full_range == full_range)
                पटिनिवत्त cv_pix_fmts[i].cv_fmt;
        }
    }

    पटिनिवत्त 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(गणना AVPixelFormat pix_fmt)
{
    पटिनिवत्त av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(गणना AVPixelFormat pix_fmt, bool full_range)
{
    पटिनिवत्त vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
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
        &k_CFType_Dictionary_कुञ्चिका_Call_Backs,
        &k_CFType_Dictionary_मानम्_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(रिक्त, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_Set_मानम्(
        attributes,
        k_CVPixel_Buffer_Pixel_Format_Type_कुञ्चिका,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        रिक्त,
        0,
        &k_CFType_Dictionary_कुञ्चिका_Call_Backs,
        &k_CFType_Dictionary_मानम्_Call_Backs);
    CFDictionary_Set_मानम्(attributes, k_CVPixel_Buffer_IOSurface_Properties_कुञ्चिका, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(रिक्त, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(रिक्त, kCFNumberSInt32Type, &ctx->height);
    CFDictionary_Set_मानम्(attributes, k_CVPixel_Buffer_Width_कुञ्चिका, w);
    CFDictionary_Set_मानम्(attributes, k_CVPixel_Buffer_Height_कुञ्चिका, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixelBufferPoolCreate(
        रिक्त,
        रिक्त,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    सचे (err == kCVReturnSuccess)
        पटिनिवत्त 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    पटिनिवत्त AVERROR_EXTERNAL;
}

स्थिर शून्य videotoolbox_buffer_release(शून्य *opaque, uint8_t *data)
{
    CVPixelBufferRelease((CVPixelBufferRef)data);
}

स्थिर AVBufferRef *vt_pool_alloc_buffer(शून्य *opaque, size_t size)
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
    सचे (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        पटिनिवत्त रिक्त;
    }

    buf = av_buffer_create((uint8_t *)pixbuf, size,
                           videotoolbox_buffer_release, रिक्त, 0);
    सचे (!buf) {
        CVPixelBufferRelease(pixbuf);
        पटिनिवत्त रिक्त;
    }
    पटिनिवत्त buf;
}

स्थिर शून्य vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    सचे (fctx->pool) {
        CVPixelBufferPoolRelease(fctx->pool);
        fctx->pool = रिक्त;
    }
}

स्थिर पूर्णाङ्क vt_frames_init(AVHWFramesContext *ctx)
{
    पूर्णाङ्क i, ret;

    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        सचे (ctx->sw_format == supported_formats[i])
            भङ्ग;
    }
    सचे (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        पटिनिवत्त AVERROR(ENOSYS);
    }

    सचे (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(
                परिमाण(CVPixelBufferRef), ctx, vt_pool_alloc_buffer, रिक्त);
        सचे (!ffhwframesctx(ctx)->pool_internal)
            पटिनिवत्त AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    सचे (ret < 0)
        पटिनिवत्त ret;

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क vt_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    सचे (!frame->buf[0])
        पटिनिवत्त AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   गणना AVHWFrameTransferDirection dir,
                                   गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts = av_malloc_array(2, परिमाण(*fmts));
    सचे (!fmts)
        पटिनिवत्त AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    पटिनिवत्त 0;
}

स्थिर शून्य vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)hwmap->source->data[3];

    CVPixelBufferUnlockBaseAddress(pixbuf, (uintptr_t)hwmap->priv);
}

स्थिर पूर्णाङ्क vt_pixbuf_set_par(शून्य *log_ctx,
                             CVPixelBufferRef pixbuf, ध्रुव AVFrame *src)
{
    CFMutableDictionaryRef par = रिक्त;
    CFNumberRef अङ्कः = रिक्त, den = रिक्त;
    AVRational avpar = src->sample_aspect_ratio;

    सचे (avpar.अङ्कः == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Pixel_Aspect_Ratio_कुञ्चिका);
        पटिनिवत्त 0;
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

    सचे (!par || !अङ्कः || !den) {
        सचे (par) CFRelease(par);
        सचे (अङ्कः) CFRelease(अङ्कः);
        सचे (den) CFRelease(den);
        पटिनिवत्त AVERROR(ENOMEM);
    }

    CFDictionary_Set_मानम्(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Horizontal_Spacing_कुञ्चिका,
        अङ्कः);
    CFDictionary_Set_मानम्(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Vertical_Spacing_कुञ्चिका,
        den);

    CVBufferSetAttachment(
        pixbuf,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_कुञ्चिका,
        par,
        kCVAttachmentMode_ShouldPropagate
    );

    CFRelease(par);
    CFRelease(अङ्कः);
    CFRelease(den);

    पटिनिवत्त 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(गणना AVChromaLocation loc)
{
    विकल्प (loc) {
    पक्ष AVCHROMA_LOC_वामः:
        पटिनिवत्त k_CVImage_Buffer_Chroma_Location_वामः;
    पक्ष AVCHROMA_LOC_CENTER:
        पटिनिवत्त kCVImageBufferChromaLocation_Center;
    पक्ष AVCHROMA_LOC_शिखरम्:
        पटिनिवत्त k_CVImage_Buffer_Chroma_Location_शिखरम्;
    पक्ष AVCHROMA_LOC_BOTTOM:
        पटिनिवत्त kCVImageBufferChromaLocation_Bottom;
    पक्ष AVCHROMA_LOC_TOPLEFT:
        पटिनिवत्त k_CVImage_Buffer_Chroma_Location_शिखरम्_वामः;
    पक्ष AVCHROMA_LOC_BOTTOMLEFT:
        पटिनिवत्त k_CVImage_Buffer_Chroma_Location_Bottom_वामः;
    स्वभाव:
        पटिनिवत्त रिक्त;
    }
}

स्थिर पूर्णाङ्क vt_pixbuf_set_chromaloc(शून्य *log_ctx,
                                   CVPixelBufferRef pixbuf, ध्रुव AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    सचे (loc) {
        CVBufferSetAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_शिखरम्_Field_कुञ्चिका,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } अञ्ञथा
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_शिखरम्_Field_कुञ्चिका);

    पटिनिवत्त 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(गणना AVColorSpace space)
{
    विकल्प (space) {
    पक्ष AVCOL_SPC_BT2020_CL:
    पक्ष AVCOL_SPC_BT2020_NCL:
#सचे HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        सचे (__builtin_available(macOS 10.11, iOS 9, *))
            पटिनिवत्त kCVImageBufferYCbCrMatrix_ITU_R_2020;
#endif
        पटिनिवत्त CFSTR("ITU_R_2020");
    पक्ष AVCOL_SPC_BT470BG:
    पक्ष AVCOL_SPC_SMPTE170M:
        पटिनिवत्त kCVImageBufferYCbCrMatrix_ITU_R_601_4;
    पक्ष AVCOL_SPC_BT709:
        पटिनिवत्त kCVImageBufferYCbCrMatrix_ITU_R_709_2;
    पक्ष AVCOL_SPC_SMPTE240M:
        पटिनिवत्त kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
    स्वभाव:
#सचे HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        सचे (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            पटिनिवत्त CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
    पक्ष AVCOL_SPC_UNSPECIFIED:
        पटिनिवत्त रिक्त;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(गणना AVColorPrimaries pri)
{
    विकल्प (pri) {
    पक्ष AVCOL_PRI_BT2020:
#सचे HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        सचे (__builtin_available(macOS 10.11, iOS 9, *))
            पटिनिवत्त kCVImageBufferColorPrimaries_ITU_R_2020;
#endif
        पटिनिवत्त CFSTR("ITU_R_2020");
    पक्ष AVCOL_PRI_BT709:
        पटिनिवत्त kCVImageBufferColorPrimaries_ITU_R_709_2;
    पक्ष AVCOL_PRI_SMPTE170M:
        पटिनिवत्त kCVImageBufferColorPrimaries_SMPTE_C;
    पक्ष AVCOL_PRI_BT470BG:
        पटिनिवत्त kCVImageBufferColorPrimaries_EBU_3213;
    स्वभाव:
#सचे HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        सचे (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            पटिनिवत्त CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
    पक्ष AVCOL_PRI_UNSPECIFIED:
        पटिनिवत्त रिक्त;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(गणना AVColorTransferCharacteristic trc)
{

    विकल्प (trc) {
    पक्ष AVCOL_TRC_SMPTE2084:
#सचे HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        सचे (__builtin_available(macOS 10.13, iOS 11, *))
            पटिनिवत्त kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
#endif
        पटिनिवत्त CFSTR("SMPTE_ST_2084_PQ");
    पक्ष AVCOL_TRC_BT2020_10:
    पक्ष AVCOL_TRC_BT2020_12:
#सचे HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        सचे (__builtin_available(macOS 10.11, iOS 9, *))
            पटिनिवत्त kCVImageBufferTransferFunction_ITU_R_2020;
#endif
        पटिनिवत्त CFSTR("ITU_R_2020");
    पक्ष AVCOL_TRC_BT709:
        पटिनिवत्त kCVImageBufferTransferFunction_ITU_R_709_2;
    पक्ष AVCOL_TRC_SMPTE240M:
        पटिनिवत्त kCVImageBufferTransferFunction_SMPTE_240M_1995;
    पक्ष AVCOL_TRC_SMPTE428:
#सचे HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        सचे (__builtin_available(macOS 10.12, iOS 10, *))
            पटिनिवत्त kCVImageBufferTransferFunction_SMPTE_ST_428_1;
#endif
        पटिनिवत्त CFSTR("SMPTE_ST_428_1");
    पक्ष AVCOL_TRC_ARIB_STD_B67:
#सचे HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        सचे (__builtin_available(macOS 10.13, iOS 11, *))
            पटिनिवत्त kCVImageBufferTransferFunction_ITU_R_2100_HLG;
#endif
        पटिनिवत्त CFSTR("ITU_R_2100_HLG");
    पक्ष AVCOL_TRC_GAMMA22:
        पटिनिवत्त kCVImageBufferTransferFunction_UseGamma;
    पक्ष AVCOL_TRC_GAMMA28:
        पटिनिवत्त kCVImageBufferTransferFunction_UseGamma;
    स्वभाव:
#सचे HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        सचे (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            पटिनिवत्त CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    पक्ष AVCOL_TRC_UNSPECIFIED:
        पटिनिवत्त रिक्त;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
स्थिर CFDictionaryRef vt_cv_buffer_copy_attachments(CVBufferRef buffer,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #सचे (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        सचे (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            पटिनिवत्त CVBufferCopyAttachments(buffer, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #सचे (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(buffer, attachment_mode);
        पटिनिवत्त (dict) ? CFDictionaryCreateCopy(रिक्त, dict) : रिक्त;
    #अञ्ञथा
        पटिनिवत्त रिक्त; // Impossible, just make the compiler happy
    #endif
}

स्थिर पूर्णाङ्क vt_pixbuf_set_colorspace(शून्य *log_ctx,
                                    CVPixelBufferRef pixbuf, ध्रुव AVFrame *src)
{
    CGColorSpaceRef colorspace = रिक्त;
    CFStringRef colormatrix = रिक्त, colorpri = रिक्त, colortrc = रिक्त;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    सचे (colormatrix)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_कुञ्चिका,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    अञ्ञथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_कुञ्चिका);
        सचे (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    सचे (colorpri)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_कुञ्चिका,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    अञ्ञथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_कुञ्चिका);
        सचे (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    सचे (colortrc)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_कुञ्चिका,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    अञ्ञथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_कुञ्चिका);
        सचे (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    सचे (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    अञ्ञथा सचे (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    सचे (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(रिक्त, kCFNumberFloat32Type, &gamma);
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_कुञ्चिका,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } अञ्ञथा
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_कुञ्चिका);

#सचे (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    सचे (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_buffer_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        सचे (attachments) {
            colorspace =
                CVImageBufferCreateColorSpaceFromAttachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    सचे (colorspace) {
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_कुञ्चिका,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } अञ्ञथा
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_कुञ्चिका);

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क vt_pixbuf_set_attachments(शून्य *log_ctx,
                                     CVPixelBufferRef pixbuf, ध्रुव AVFrame *src)
{
    पूर्णाङ्क ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    सचे (ret < 0)
        पटिनिवत्त ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    सचे (ret < 0)
        पटिनिवत्त ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    सचे (ret < 0)
        पटिनिवत्त ret;
    पटिनिवत्त 0;
}

पूर्णाङ्क av_vt_pixbuf_set_attachments(शून्य *log_ctx,
                                 CVPixelBufferRef pixbuf, ध्रुव AVFrame *src)
{
    पटिनिवत्त vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

स्थिर पूर्णाङ्क vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, ध्रुव AVFrame *src,
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
    सचे (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        पटिनिवत्त AVERROR_UNKNOWN;
    }

    सचे (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        पटिनिवत्त AVERROR_UNKNOWN;
    }

    सचे (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    सचे (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        पटिनिवत्त AVERROR_UNKNOWN;
    }

    सचे (CVPixelBufferIsPlanar(pixbuf)) {
        पूर्णाङ्क planes = CVPixel_Buffer_Get_Plane_गणनम्(pixbuf);
        अत्थाय (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } अञ्ञथा {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (शून्य *)(uintptr_t)map_flags);
    सचे (ret < 0)
        गच्छ unlock;

    पटिनिवत्त 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, ध्रुव AVFrame *src)
{
    AVFrame *map;
    पूर्णाङ्क err;

    सचे (dst->width > hwfc->width || dst->height > hwfc->height)
        पटिनिवत्त AVERROR(EINVAL);

    map = av_frame_alloc();
    सचे (!map)
        पटिनिवत्त AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    सचे (err)
        गच्छ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    सचे (err)
        गच्छ fail;

    err = 0;
fail:
    av_frame_free(&map);
    पटिनिवत्त err;
}

स्थिर पूर्णाङ्क vt_transfer_data_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, ध्रुव AVFrame *src)
{
    AVFrame *map;
    पूर्णाङ्क err;

    सचे (src->width > hwfc->width || src->height > hwfc->height)
        पटिनिवत्त AVERROR(EINVAL);

    map = av_frame_alloc();
    सचे (!map)
        पटिनिवत्त AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    सचे (err)
        गच्छ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    सचे (err)
        गच्छ fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixelBufferRef)dst->data[3], src);
    सचे (err)
        गच्छ fail;

    err = 0;
fail:
    av_frame_free(&map);
    पटिनिवत्त err;
}

स्थिर पूर्णाङ्क vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    पूर्णाङ्क err;

    सचे (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    अञ्ञथा सचे (dst->format != hwfc->sw_format)
        पटिनिवत्त AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    सचे (err)
        पटिनिवत्त err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    सचे (err)
        पटिनिवत्त err;

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क vt_device_create(AVHWDeviceContext *ctx, ध्रुव वर्ण *device,
                            AVDictionary *opts, पूर्णाङ्क flags)
{
    सचे (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        पटिनिवत्त AVERROR_UNKNOWN;
    }

    पटिनिवत्त 0;
}

ध्रुव HWContextType ff_hwcontext_type_videotoolbox = {
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

    .pix_fmts = (ध्रुव गणना AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
