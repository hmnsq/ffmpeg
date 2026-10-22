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
    CVPixelBufferPoolRef pool;
} VTFramesContext;

ساكن ثابت بنية {
    uint32_t cv_fmt;
    bool full_range;
    تعداد AVPixelFormat pix_fmt;
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
#إذا HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#endif
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

ساكن ثابت تعداد AVPixelFormat supported_formats[] = {
#ifdef kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#endif
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#إذا HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#إذا HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#endif
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

ساكن صحيح vt_frames_get_constraints(AVHWDeviceContext *ctx,
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

تعداد AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
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
            صحيح full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            إذا (range == AVCOL_RANGE_UNSPECIFIED)
                أرجع cv_pix_fmts[i].cv_fmt;

            إذا (cv_pix_fmts[i].full_range == full_range)
                أرجع cv_pix_fmts[i].cv_fmt;
        }
    }

    أرجع 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(تعداد AVPixelFormat pix_fmt)
{
    أرجع av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(تعداد AVPixelFormat pix_fmt, bool full_range)
{
    أرجع vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

ساكن صحيح vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef attributes, iosurface_properties;

    attributes = CFDictionaryCreateMutable(
        عدم,
        2,
        &k_CFType_Dictionary_کلیل_Call_Backs,
        &k_CFType_Dictionary_بەها_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(عدم, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_Set_بەها(
        attributes,
        k_CVPixel_Buffer_Pixel_Format_Type_کلیل,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        عدم,
        0,
        &k_CFType_Dictionary_کلیل_Call_Backs,
        &k_CFType_Dictionary_بەها_Call_Backs);
    CFDictionary_Set_بەها(attributes, k_CVPixel_Buffer_IOSurface_Properties_کلیل, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(عدم, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(عدم, kCFNumberSInt32Type, &ctx->height);
    CFDictionary_Set_بەها(attributes, k_CVPixel_Buffer_Width_کلیل, w);
    CFDictionary_Set_بەها(attributes, k_CVPixel_Buffer_Height_کلیل, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixelBufferPoolCreate(
        عدم,
        عدم,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    إذا (err == kCVReturnSuccess)
        أرجع 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    أرجع AVERROR_EXTERNAL;
}

ساكن فراغ videotoolbox_buffer_release(فراغ *opaque, uint8_t *data)
{
    CVPixelBufferRelease((CVPixelBufferRef)data);
}

ساكن AVBufferRef *vt_pool_alloc_buffer(فراغ *opaque, size_t size)
{
    CVPixelBufferRef pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixelBufferPoolCreatePixelBuffer(
        عدم,
        fctx->pool,
        &pixbuf
    );
    إذا (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        أرجع عدم;
    }

    buf = av_buffer_create((uint8_t *)pixbuf, size,
                           videotoolbox_buffer_release, عدم, 0);
    إذا (!buf) {
        CVPixelBufferRelease(pixbuf);
        أرجع عدم;
    }
    أرجع buf;
}

ساكن فراغ vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    إذا (fctx->pool) {
        CVPixelBufferPoolRelease(fctx->pool);
        fctx->pool = عدم;
    }
}

ساكن صحيح vt_frames_init(AVHWFramesContext *ctx)
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
        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(
                حجم(CVPixelBufferRef), ctx, vt_pool_alloc_buffer, عدم);
        إذا (!ffhwframesctx(ctx)->pool_internal)
            أرجع AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    إذا (ret < 0)
        أرجع ret;

    أرجع 0;
}

ساكن صحيح vt_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    إذا (!frame->buf[0])
        أرجع AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

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
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)hwmap->source->data[3];

    CVPixelBufferUnlockBaseAddress(pixbuf, (uintptr_t)hwmap->priv);
}

ساكن صحيح vt_pixbuf_set_par(فراغ *log_ctx,
                             CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    CFMutableDictionaryRef par = عدم;
    CFNumberRef ژمارە = عدم, den = عدم;
    AVRational avpar = src->sample_aspect_ratio;

    إذا (avpar.ژمارە == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Pixel_Aspect_Ratio_کلیل);
        أرجع 0;
    }

    av_reduce(&avpar.ژمارە, &avpar.den,
                avpar.ژمارە, avpar.den,
                0xFFFFFFFF);

    ژمارە = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.ژمارە);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_کلیل_Call_Backs,
                                    &k_CFType_Dictionary_بەها_Call_Backs);

    إذا (!par || !ژمارە || !den) {
        إذا (par) CFRelease(par);
        إذا (ژمارە) CFRelease(ژمارە);
        إذا (den) CFRelease(den);
        أرجع AVERROR(ENOMEM);
    }

    CFDictionary_Set_بەها(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Horizontal_Spacing_کلیل,
        ژمارە);
    CFDictionary_Set_بەها(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Vertical_Spacing_کلیل,
        den);

    CVBufferSetAttachment(
        pixbuf,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_کلیل,
        par,
        kCVAttachmentMode_ShouldPropagate
    );

    CFRelease(par);
    CFRelease(ژمارە);
    CFRelease(den);

    أرجع 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(تعداد AVChromaLocation loc)
{
    بدل (loc) {
    حالة AVCHROMA_LOC_چەپ:
        أرجع k_CVImage_Buffer_Chroma_Location_چەپ;
    حالة AVCHROMA_LOC_CENTER:
        أرجع kCVImageBufferChromaLocation_Center;
    حالة AVCHROMA_LOC_لووتکە:
        أرجع k_CVImage_Buffer_Chroma_Location_لووتکە;
    حالة AVCHROMA_LOC_BOTTOM:
        أرجع kCVImageBufferChromaLocation_Bottom;
    حالة AVCHROMA_LOC_TOPLEFT:
        أرجع k_CVImage_Buffer_Chroma_Location_لووتکە_چەپ;
    حالة AVCHROMA_LOC_BOTTOMLEFT:
        أرجع k_CVImage_Buffer_Chroma_Location_Bottom_چەپ;
    افتراضي:
        أرجع عدم;
    }
}

ساكن صحيح vt_pixbuf_set_chromaloc(فراغ *log_ctx,
                                   CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    إذا (loc) {
        CVBufferSetAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_لووتکە_Field_کلیل,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } وإلا
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_لووتکە_Field_کلیل);

    أرجع 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(تعداد AVColorSpace space)
{
    بدل (space) {
    حالة AVCOL_SPC_BT2020_CL:
    حالة AVCOL_SPC_BT2020_NCL:
#إذا HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        إذا (__builtin_available(macOS 10.11, iOS 9, *))
            أرجع kCVImageBufferYCbCrMatrix_ITU_R_2020;
#endif
        أرجع CFSTR("ITU_R_2020");
    حالة AVCOL_SPC_BT470BG:
    حالة AVCOL_SPC_SMPTE170M:
        أرجع kCVImageBufferYCbCrMatrix_ITU_R_601_4;
    حالة AVCOL_SPC_BT709:
        أرجع kCVImageBufferYCbCrMatrix_ITU_R_709_2;
    حالة AVCOL_SPC_SMPTE240M:
        أرجع kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
    افتراضي:
#إذا HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        إذا (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            أرجع CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
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
            أرجع kCVImageBufferColorPrimaries_ITU_R_2020;
#endif
        أرجع CFSTR("ITU_R_2020");
    حالة AVCOL_PRI_BT709:
        أرجع kCVImageBufferColorPrimaries_ITU_R_709_2;
    حالة AVCOL_PRI_SMPTE170M:
        أرجع kCVImageBufferColorPrimaries_SMPTE_C;
    حالة AVCOL_PRI_BT470BG:
        أرجع kCVImageBufferColorPrimaries_EBU_3213;
    افتراضي:
#إذا HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        إذا (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            أرجع CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
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
            أرجع kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
#endif
        أرجع CFSTR("SMPTE_ST_2084_PQ");
    حالة AVCOL_TRC_BT2020_10:
    حالة AVCOL_TRC_BT2020_12:
#إذا HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        إذا (__builtin_available(macOS 10.11, iOS 9, *))
            أرجع kCVImageBufferTransferFunction_ITU_R_2020;
#endif
        أرجع CFSTR("ITU_R_2020");
    حالة AVCOL_TRC_BT709:
        أرجع kCVImageBufferTransferFunction_ITU_R_709_2;
    حالة AVCOL_TRC_SMPTE240M:
        أرجع kCVImageBufferTransferFunction_SMPTE_240M_1995;
    حالة AVCOL_TRC_SMPTE428:
#إذا HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        إذا (__builtin_available(macOS 10.12, iOS 10, *))
            أرجع kCVImageBufferTransferFunction_SMPTE_ST_428_1;
#endif
        أرجع CFSTR("SMPTE_ST_428_1");
    حالة AVCOL_TRC_ARIB_STD_B67:
#إذا HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        إذا (__builtin_available(macOS 10.13, iOS 11, *))
            أرجع kCVImageBufferTransferFunction_ITU_R_2100_HLG;
#endif
        أرجع CFSTR("ITU_R_2100_HLG");
    حالة AVCOL_TRC_GAMMA22:
        أرجع kCVImageBufferTransferFunction_UseGamma;
    حالة AVCOL_TRC_GAMMA28:
        أرجع kCVImageBufferTransferFunction_UseGamma;
    افتراضي:
#إذا HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        إذا (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            أرجع CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    حالة AVCOL_TRC_UNSPECIFIED:
        أرجع عدم;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
ساكن CFDictionaryRef vt_cv_buffer_copy_attachments(CVBufferRef buffer,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #إذا (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        إذا (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            أرجع CVBufferCopyAttachments(buffer, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #إذا (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(buffer, attachment_mode);
        أرجع (dict) ? CFDictionaryCreateCopy(عدم, dict) : عدم;
    #وإلا
        أرجع عدم; // Impossible, just make the compiler happy
    #endif
}

ساكن صحيح vt_pixbuf_set_colorspace(فراغ *log_ctx,
                                    CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    CGColorSpaceRef colorspace = عدم;
    CFStringRef colormatrix = عدم, colorpri = عدم, colortrc = عدم;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    إذا (colormatrix)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_کلیل,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    وإلا {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_کلیل);
        إذا (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    إذا (colorpri)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_کلیل,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    وإلا {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_کلیل);
        إذا (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    إذا (colortrc)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_کلیل,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    وإلا {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_کلیل);
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
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_کلیل,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } وإلا
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_کلیل);

#إذا (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    إذا (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_buffer_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        إذا (attachments) {
            colorspace =
                CVImageBufferCreateColorSpaceFromAttachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    إذا (colorspace) {
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_کلیل,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } وإلا
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_کلیل);

    أرجع 0;
}

ساكن صحيح vt_pixbuf_set_attachments(فراغ *log_ctx,
                                     CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    صحيح ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    إذا (ret < 0)
        أرجع ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    إذا (ret < 0)
        أرجع ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    إذا (ret < 0)
        أرجع ret;
    أرجع 0;
}

صحيح av_vt_pixbuf_set_attachments(فراغ *log_ctx,
                                 CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    أرجع vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

ساكن صحيح vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, ثابت AVFrame *src,
                        صحيح flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)src->data[3];
    OSType pixel_format = CVPixelBufferGetPixelFormatType(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    صحيح ret;
    صحيح i;
    تعداد AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    إذا (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        أرجع AVERROR_UNKNOWN;
    }

    إذا (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        أرجع AVERROR_UNKNOWN;
    }

    إذا (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    إذا (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        أرجع AVERROR_UNKNOWN;
    }

    إذا (CVPixelBufferIsPlanar(pixbuf)) {
        صحيح planes = CVPixel_Buffer_Get_Plane_ژماردن(pixbuf);
        لكل (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } وإلا {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (فراغ *)(uintptr_t)map_flags);
    إذا (ret < 0)
        اذهب unlock;

    أرجع 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    أرجع ret;
}

ساكن صحيح vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحيح err;

    إذا (dst->width > hwfc->width || dst->height > hwfc->height)
        أرجع AVERROR(EINVAL);

    map = av_frame_alloc();
    إذا (!map)
        أرجع AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    إذا (err)
        اذهب fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    إذا (err)
        اذهب fail;

    err = 0;
fail:
    av_frame_free(&map);
    أرجع err;
}

ساكن صحيح vt_transfer_data_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحيح err;

    إذا (src->width > hwfc->width || src->height > hwfc->height)
        أرجع AVERROR(EINVAL);

    map = av_frame_alloc();
    إذا (!map)
        أرجع AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    إذا (err)
        اذهب fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    إذا (err)
        اذهب fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixelBufferRef)dst->data[3], src);
    إذا (err)
        اذهب fail;

    err = 0;
fail:
    av_frame_free(&map);
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

    err = vt_map_frame(hwfc, dst, src, flags);
    إذا (err)
        أرجع err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
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

    .frames_hwctx_size    = حجم(VTFramesContext),

    .device_create        = vt_device_create,
    .frames_init          = vt_frames_init,
    .frames_get_buffer    = vt_get_buffer,
    .frames_get_constraints = vt_frames_get_constraints,
    .frames_uninit        = vt_frames_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_data_to     = vt_transfer_data_to,
    .transfer_data_from   = vt_transfer_data_from,
    .map_from             = vt_map_from,

    .pix_fmts = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
