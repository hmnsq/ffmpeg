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

#समावेश "config.h"

#समावेश <stdint.h>
#समावेश <string.h>

#समावेश <VideoToolbox/VideoToolbox.h>

#समावेश "buffer.h"
#समावेश "buffer_internal.h"
#समावेश "common.h"
#समावेश "hwcontext.h"
#समावेश "hwcontext_internal.h"
#समावेश "hwcontext_videotoolbox.h"
#समावेश "attributes.h"
#समावेश "mem.h"
#समावेश "pixfmt.h"
#समावेश "pixdesc.h"

प्रकार काष्ठा VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixel_बफर_Pool_Ref pool;
} VTFramesContext;

अटल स्थिर काष्ठा {
    uint32_t cv_fmt;
    bool full_range;
    क्रमागत AVPixelFormat pix_fmt;
} cv_pix_fmts[] = {
    { kCVPixelFormatType_420YpCbCr8Planar,              false, AV_PIX_FMT_YUV420P },
    { kCVPixelFormatType_420YpCbCr8PlanarFullRange,     true,  AV_PIX_FMT_YUV420P },
    { kCVPixelFormatType_422YpCbCr8,                    false, AV_PIX_FMT_UYVY422 },
    { kCVPixelFormatType_32BGRA,                        true,  AV_PIX_FMT_BGRA },
#अगर_घोषित kCFCoreFoundationVersionNumber10_7
    { kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV12 },
    { kCVPixelFormatType_420YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV12 },
    { kCVPixelFormatType_4444AYpCbCr8,                  false, AV_PIX_FMT_AYUV },
    { kCVPixelFormatType_4444AYpCbCr16,                 false, AV_PIX_FMT_AYUV64 },
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#पूर्ण_अगर
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

अटल स्थिर क्रमागत AVPixelFormat supported_formats[] = {
#अगर_घोषित kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#पूर्ण_अगर
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#अगर HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#पूर्ण_अगर
#अगर HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#पूर्ण_अगर
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

अटल पूर्णांक vt_frames_get_constraints(AVHWDeviceContext *ctx,
                                     स्थिर व्योम *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    पूर्णांक i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    माप(*constraints->valid_sw_formats));
    अगर (!constraints->valid_sw_formats)
        वापस AVERROR(ENOMEM);

    क्रम (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, माप(*constraints->valid_hw_formats));
    अगर (!constraints->valid_hw_formats)
        वापस AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    वापस 0;
}

क्रमागत AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    पूर्णांक i;
    क्रम (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        अगर (cv_pix_fmts[i].cv_fmt == cv_fmt)
            वापस cv_pix_fmts[i].pix_fmt;
    }
    वापस AV_PIX_FMT_NONE;
}

अटल uint32_t vt_format_from_pixfmt(क्रमागत AVPixelFormat pix_fmt,
                                      क्रमागत AVColorRange range)
{
    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        अगर (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            पूर्णांक full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            अगर (range == AVCOL_RANGE_UNSPECIFIED)
                वापस cv_pix_fmts[i].cv_fmt;

            अगर (cv_pix_fmts[i].full_range == full_range)
                वापस cv_pix_fmts[i].cv_fmt;
        }
    }

    वापस 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(क्रमागत AVPixelFormat pix_fmt)
{
    वापस av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(क्रमागत AVPixelFormat pix_fmt, bool full_range)
{
    वापस vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

अटल पूर्णांक vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef attributes, iosurface_properties;

    attributes = CFDictionaryCreateMutable(
        शून्य,
        2,
        &k_CFType_Dictionary_कुंजी_Call_Backs,
        &k_CFType_Dictionary_मूल्य_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(शून्य, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_Set_मूल्य(
        attributes,
        k_CVPixel_बफर_Pixel_Format_Type_कुंजी,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        शून्य,
        0,
        &k_CFType_Dictionary_कुंजी_Call_Backs,
        &k_CFType_Dictionary_मूल्य_Call_Backs);
    CFDictionary_Set_मूल्य(attributes, k_CVPixel_बफर_IOSurface_Properties_कुंजी, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(शून्य, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(शून्य, kCFNumberSInt32Type, &ctx->height);
    CFDictionary_Set_मूल्य(attributes, k_CVPixel_बफर_Width_कुंजी, w);
    CFDictionary_Set_मूल्य(attributes, k_CVPixel_बफर_Height_कुंजी, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixel_बफर_Pool_Create(
        शून्य,
        शून्य,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    अगर (err == kCVReturnSuccess)
        वापस 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    वापस AVERROR_EXTERNAL;
}

अटल व्योम videotoolbox_बफर_release(व्योम *opaque, uint8_t *तथ्य)
{
    CVPixel_बफर_Release((CVPixel_बफर_Ref)तथ्य);
}

अटल AVBufferRef *vt_pool_alloc_बफर(व्योम *opaque, माप_प्रकार आकार)
{
    CVPixel_बफर_Ref pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixel_बफर_Pool_Create_Pixel_बफर(
        शून्य,
        fctx->pool,
        &pixbuf
    );
    अगर (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        वापस शून्य;
    }

    buf = av_बफर_create((uint8_t *)pixbuf, आकार,
                           videotoolbox_बफर_release, शून्य, 0);
    अगर (!buf) {
        CVPixel_बफर_Release(pixbuf);
        वापस शून्य;
    }
    वापस buf;
}

अटल व्योम vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    अगर (fctx->pool) {
        CVPixel_बफर_Pool_Release(fctx->pool);
        fctx->pool = शून्य;
    }
}

अटल पूर्णांक vt_frames_init(AVHWFramesContext *ctx)
{
    पूर्णांक i, ret;

    क्रम (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        अगर (ctx->sw_format == supported_formats[i])
            अवरोध;
    }
    अगर (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        वापस AVERROR(ENOSYS);
    }

    अगर (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_बफर_pool_init2(
                माप(CVPixel_बफर_Ref), ctx, vt_pool_alloc_बफर, शून्य);
        अगर (!ffhwframesctx(ctx)->pool_internal)
            वापस AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    अगर (ret < 0)
        वापस ret;

    वापस 0;
}

अटल पूर्णांक vt_get_बफर(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_बफर_pool_get(ctx->pool);
    अगर (!frame->buf[0])
        वापस AVERROR(ENOMEM);

    frame->तथ्य[3] = frame->buf[0]->तथ्य;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    वापस 0;
}

अटल पूर्णांक vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   क्रमागत AVHWFrameTransferDirection dir,
                                   क्रमागत AVPixelFormat **formats)
{
    क्रमागत AVPixelFormat *fmts = av_malloc_array(2, माप(*fmts));
    अगर (!fmts)
        वापस AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    वापस 0;
}

अटल व्योम vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixel_बफर_Ref pixbuf = (CVPixel_बफर_Ref)hwmap->source->तथ्य[3];

    CVPixel_बफर_Unlock_Base_Address(pixbuf, (uintptr_t)hwmap->priv);
}

अटल पूर्णांक vt_pixbuf_set_par(व्योम *log_ctx,
                             CVPixel_बफर_Ref pixbuf, स्थिर AVFrame *src)
{
    CFMutableDictionaryRef par = शून्य;
    CFNumberRef अंक = शून्य, den = शून्य;
    AVRational avpar = src->sample_aspect_ratio;

    अगर (avpar.अंक == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_बफर_Pixel_Aspect_Ratio_कुंजी);
        वापस 0;
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
                                    &k_CFCopy_String_Dictionary_कुंजी_Call_Backs,
                                    &k_CFType_Dictionary_मूल्य_Call_Backs);

    अगर (!par || !अंक || !den) {
        अगर (par) CFRelease(par);
        अगर (अंक) CFRelease(अंक);
        अगर (den) CFRelease(den);
        वापस AVERROR(ENOMEM);
    }

    CFDictionary_Set_मूल्य(
        par,
        k_CVImage_बफर_Pixel_Aspect_Ratio_Horizontal_Spacing_कुंजी,
        अंक);
    CFDictionary_Set_मूल्य(
        par,
        k_CVImage_बफर_Pixel_Aspect_Ratio_Vertical_Spacing_कुंजी,
        den);

    CVBufferSetAttachment(
        pixbuf,
        k_CVImage_बफर_Pixel_Aspect_Ratio_कुंजी,
        par,
        kCVAttachmentMode_ShouldPropagate
    );

    CFRelease(par);
    CFRelease(अंक);
    CFRelease(den);

    वापस 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(क्रमागत AVChromaLocation loc)
{
    चयन (loc) {
    हाल AVCHROMA_LOC_बायाँ:
        वापस k_CVImage_बफर_Chroma_Location_बायाँ;
    हाल AVCHROMA_LOC_CENTER:
        वापस k_CVImage_बफर_Chroma_Location_Center;
    हाल AVCHROMA_LOC_शीर्ष:
        वापस k_CVImage_बफर_Chroma_Location_शीर्ष;
    हाल AVCHROMA_LOC_BOTTOM:
        वापस k_CVImage_बफर_Chroma_Location_Bottom;
    हाल AVCHROMA_LOC_TOPLEFT:
        वापस k_CVImage_बफर_Chroma_Location_शीर्ष_बायाँ;
    हाल AVCHROMA_LOC_BOTTOMLEFT:
        वापस k_CVImage_बफर_Chroma_Location_Bottom_बायाँ;
    शेष:
        वापस शून्य;
    }
}

अटल पूर्णांक vt_pixbuf_set_chromaloc(व्योम *log_ctx,
                                   CVPixel_बफर_Ref pixbuf, स्थिर AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    अगर (loc) {
        CVBufferSetAttachment(
            pixbuf,
            k_CVImage_बफर_Chroma_Location_शीर्ष_Field_कुंजी,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } अन्यथा
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_बफर_Chroma_Location_शीर्ष_Field_कुंजी);

    वापस 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(क्रमागत AVColorSpace space)
{
    चयन (space) {
    हाल AVCOL_SPC_BT2020_CL:
    हाल AVCOL_SPC_BT2020_NCL:
#अगर HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        अगर (__builtin_available(macOS 10.11, iOS 9, *))
            वापस k_CVImage_बफर_YCb_Cr_Matrix_ITU_R_2020;
#पूर्ण_अगर
        वापस CFSTR("ITU_R_2020");
    हाल AVCOL_SPC_BT470BG:
    हाल AVCOL_SPC_SMPTE170M:
        वापस k_CVImage_बफर_YCb_Cr_Matrix_ITU_R_601_4;
    हाल AVCOL_SPC_BT709:
        वापस k_CVImage_बफर_YCb_Cr_Matrix_ITU_R_709_2;
    हाल AVCOL_SPC_SMPTE240M:
        वापस k_CVImage_बफर_YCb_Cr_Matrix_SMPTE_240_M_1995;
    शेष:
#अगर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        अगर (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            वापस CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#पूर्ण_अगर
    हाल AVCOL_SPC_UNSPECIFIED:
        वापस शून्य;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(क्रमागत AVColorPrimaries pri)
{
    चयन (pri) {
    हाल AVCOL_PRI_BT2020:
#अगर HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        अगर (__builtin_available(macOS 10.11, iOS 9, *))
            वापस k_CVImage_बफर_Color_Primaries_ITU_R_2020;
#पूर्ण_अगर
        वापस CFSTR("ITU_R_2020");
    हाल AVCOL_PRI_BT709:
        वापस k_CVImage_बफर_Color_Primaries_ITU_R_709_2;
    हाल AVCOL_PRI_SMPTE170M:
        वापस k_CVImage_बफर_Color_Primaries_SMPTE_C;
    हाल AVCOL_PRI_BT470BG:
        वापस k_CVImage_बफर_Color_Primaries_EBU_3213;
    शेष:
#अगर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        अगर (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            वापस CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#पूर्ण_अगर
    हाल AVCOL_PRI_UNSPECIFIED:
        वापस शून्य;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(क्रमागत AVColorTransferCharacteristic trc)
{

    चयन (trc) {
    हाल AVCOL_TRC_SMPTE2084:
#अगर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        अगर (__builtin_available(macOS 10.13, iOS 11, *))
            वापस k_CVImage_बफर_Transfer_Function_SMPTE_ST_2084_PQ;
#पूर्ण_अगर
        वापस CFSTR("SMPTE_ST_2084_PQ");
    हाल AVCOL_TRC_BT2020_10:
    हाल AVCOL_TRC_BT2020_12:
#अगर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        अगर (__builtin_available(macOS 10.11, iOS 9, *))
            वापस k_CVImage_बफर_Transfer_Function_ITU_R_2020;
#पूर्ण_अगर
        वापस CFSTR("ITU_R_2020");
    हाल AVCOL_TRC_BT709:
        वापस k_CVImage_बफर_Transfer_Function_ITU_R_709_2;
    हाल AVCOL_TRC_SMPTE240M:
        वापस k_CVImage_बफर_Transfer_Function_SMPTE_240_M_1995;
    हाल AVCOL_TRC_SMPTE428:
#अगर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        अगर (__builtin_available(macOS 10.12, iOS 10, *))
            वापस k_CVImage_बफर_Transfer_Function_SMPTE_ST_428_1;
#पूर्ण_अगर
        वापस CFSTR("SMPTE_ST_428_1");
    हाल AVCOL_TRC_ARIB_STD_B67:
#अगर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        अगर (__builtin_available(macOS 10.13, iOS 11, *))
            वापस k_CVImage_बफर_Transfer_Function_ITU_R_2100_HLG;
#पूर्ण_अगर
        वापस CFSTR("ITU_R_2100_HLG");
    हाल AVCOL_TRC_GAMMA22:
        वापस k_CVImage_बफर_Transfer_Function_Use_Gamma;
    हाल AVCOL_TRC_GAMMA28:
        वापस k_CVImage_बफर_Transfer_Function_Use_Gamma;
    शेष:
#अगर HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        अगर (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            वापस CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#पूर्ण_अगर
    हाल AVCOL_TRC_UNSPECIFIED:
        वापस शून्य;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
अटल CFDictionaryRef vt_cv_बफर_copy_attachments(CVBufferRef बफर,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #अगर (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        अगर (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            वापस CVBufferCopyAttachments(बफर, attachment_mode);
    #पूर्ण_अगर

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #अगर (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(बफर, attachment_mode);
        वापस (dict) ? CFDictionaryCreateCopy(शून्य, dict) : शून्य;
    #अन्यथा
        वापस शून्य; // Impossible, just make the compiler happy
    #पूर्ण_अगर
}

अटल पूर्णांक vt_pixbuf_set_colorspace(व्योम *log_ctx,
                                    CVPixel_बफर_Ref pixbuf, स्थिर AVFrame *src)
{
    CGColorSpaceRef colorspace = शून्य;
    CFStringRef colormatrix = शून्य, colorpri = शून्य, colortrc = शून्य;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    अगर (colormatrix)
        CVBufferSetAttachment(pixbuf, k_CVImage_बफर_YCb_Cr_Matrix_कुंजी,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    अन्यथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_बफर_YCb_Cr_Matrix_कुंजी);
        अगर (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    अगर (colorpri)
        CVBufferSetAttachment(pixbuf, k_CVImage_बफर_Color_Primaries_कुंजी,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    अन्यथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_बफर_Color_Primaries_कुंजी);
        अगर (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    अगर (colortrc)
        CVBufferSetAttachment(pixbuf, k_CVImage_बफर_Transfer_Function_कुंजी,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    अन्यथा {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_बफर_Transfer_Function_कुंजी);
        अगर (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    अगर (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    अन्यथा अगर (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    अगर (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(शून्य, kCFNumberFloat32Type, &gamma);
        CVBufferSetAttachment(pixbuf, k_CVImage_बफर_Gamma_Level_कुंजी,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } अन्यथा
        CVBufferRemoveAttachment(pixbuf, k_CVImage_बफर_Gamma_Level_कुंजी);

#अगर (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    अगर (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_बफर_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        अगर (attachments) {
            colorspace =
                CVImage_बफर_Create_Color_Space_From_Attachments(attachments);
            CFRelease(attachments);
        }
    }
#पूर्ण_अगर

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    अगर (colorspace) {
        CVBufferSetAttachment(pixbuf, k_CVImage_बफर_CGColor_Space_कुंजी,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } अन्यथा
        CVBufferRemoveAttachment(pixbuf, k_CVImage_बफर_CGColor_Space_कुंजी);

    वापस 0;
}

अटल पूर्णांक vt_pixbuf_set_attachments(व्योम *log_ctx,
                                     CVPixel_बफर_Ref pixbuf, स्थिर AVFrame *src)
{
    पूर्णांक ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    अगर (ret < 0)
        वापस ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    अगर (ret < 0)
        वापस ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    अगर (ret < 0)
        वापस ret;
    वापस 0;
}

पूर्णांक av_vt_pixbuf_set_attachments(व्योम *log_ctx,
                                 CVPixel_बफर_Ref pixbuf, स्थिर AVFrame *src)
{
    वापस vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

अटल पूर्णांक vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, स्थिर AVFrame *src,
                        पूर्णांक flags)
{
    CVPixel_बफर_Ref pixbuf = (CVPixel_बफर_Ref)src->तथ्य[3];
    OSType pixel_format = CVPixel_बफर_Get_Pixel_Format_Type(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    पूर्णांक ret;
    पूर्णांक i;
    क्रमागत AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    अगर (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        वापस AVERROR_UNKNOWN;
    }

    अगर (CVPixel_बफर_Get_Width(pixbuf) != ctx->width ||
        CVPixel_बफर_Get_Height(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        वापस AVERROR_UNKNOWN;
    }

    अगर (flags == AV_HWFRAME_MAP_READ)
        map_flags = k_CVPixel_बफर_Lock_Read_Only;

    err = CVPixel_बफर_Lock_Base_Address(pixbuf, map_flags);
    अगर (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        वापस AVERROR_UNKNOWN;
    }

    अगर (CVPixel_बफर_Is_Planar(pixbuf)) {
        पूर्णांक planes = CVPixel_बफर_Get_Plane_गिनती(pixbuf);
        क्रम (i = 0; i < planes; i++) {
            dst->तथ्य[i]     = CVPixel_बफर_Get_Base_Address_Of_Plane(pixbuf, i);
            dst->linesize[i] = CVPixel_बफर_Get_Bytes_Per_Row_Of_Plane(pixbuf, i);
        }
    } अन्यथा {
        dst->तथ्य[0]     = CVPixel_बफर_Get_Base_Address(pixbuf);
        dst->linesize[0] = CVPixel_बफर_Get_Bytes_Per_Row(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (व्योम *)(uintptr_t)map_flags);
    अगर (ret < 0)
        जाओ unlock;

    वापस 0;

unlock:
    CVPixel_बफर_Unlock_Base_Address(pixbuf, map_flags);
    वापस ret;
}

अटल पूर्णांक vt_transfer_तथ्य_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, स्थिर AVFrame *src)
{
    AVFrame *map;
    पूर्णांक err;

    अगर (dst->width > hwfc->width || dst->height > hwfc->height)
        वापस AVERROR(EINVAL);

    map = av_frame_alloc();
    अगर (!map)
        वापस AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    अगर (err)
        जाओ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    अगर (err)
        जाओ fail;

    err = 0;
fail:
    av_frame_free(&map);
    वापस err;
}

अटल पूर्णांक vt_transfer_तथ्य_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, स्थिर AVFrame *src)
{
    AVFrame *map;
    पूर्णांक err;

    अगर (src->width > hwfc->width || src->height > hwfc->height)
        वापस AVERROR(EINVAL);

    map = av_frame_alloc();
    अगर (!map)
        वापस AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    अगर (err)
        जाओ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    अगर (err)
        जाओ fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixel_बफर_Ref)dst->तथ्य[3], src);
    अगर (err)
        जाओ fail;

    err = 0;
fail:
    av_frame_free(&map);
    वापस err;
}

अटल पूर्णांक vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       स्थिर AVFrame *src, पूर्णांक flags)
{
    पूर्णांक err;

    अगर (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    अन्यथा अगर (dst->format != hwfc->sw_format)
        वापस AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    अगर (err)
        वापस err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    अगर (err)
        वापस err;

    वापस 0;
}

अटल पूर्णांक vt_device_create(AVHWDeviceContext *ctx, स्थिर अक्षर *device,
                            AVDictionary *opts, पूर्णांक flags)
{
    अगर (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        वापस AVERROR_UNKNOWN;
    }

    वापस 0;
}

स्थिर HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .frames_hwctx_आकार    = माप(VTFramesContext),

    .device_create        = vt_device_create,
    .frames_init          = vt_frames_init,
    .frames_get_बफर    = vt_get_बफर,
    .frames_get_constraints = vt_frames_get_constraints,
    .frames_uninit        = vt_frames_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_तथ्य_to     = vt_transfer_तथ्य_to,
    .transfer_तथ्य_from   = vt_transfer_तथ्य_from,
    .map_from             = vt_map_from,

    .pix_fmts = (स्थिर क्रमागत AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
