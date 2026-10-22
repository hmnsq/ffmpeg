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
#אם HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#אם HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#אם HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#אם HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#אם HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#אם HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#אם HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#אם HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
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
#אם HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#אם HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#אם HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#אם HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#אם HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#אם HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#אם HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#אם HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
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
    אם (!constraints->valid_sw_formats)
        החזר AVERROR(ENOMEM);

    עבור (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    אם (!constraints->valid_hw_formats)
        החזר AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    החזר 0;
}

تعداد AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    صحيح i;
    עבור (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        אם (cv_pix_fmts[i].cv_fmt == cv_fmt)
            החזר cv_pix_fmts[i].pix_fmt;
    }
    החזר AV_PIX_FMT_NONE;
}

ساكن uint32_t vt_format_from_pixfmt(تعداد AVPixelFormat pix_fmt,
                                      تعداد AVColorRange range)
{
    עבור (صحيح i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        אם (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            صحيح full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            אם (range == AVCOL_RANGE_UNSPECIFIED)
                החזר cv_pix_fmts[i].cv_fmt;

            אם (cv_pix_fmts[i].full_range == full_range)
                החזר cv_pix_fmts[i].cv_fmt;
        }
    }

    החזר 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(تعداد AVPixelFormat pix_fmt)
{
    החזר av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(تعداد AVPixelFormat pix_fmt, bool full_range)
{
    החזר vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
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
        &kCFTypeDictionaryKeyCallBacks,
        &kCFTypeDictionaryValueCallBacks);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(عدم, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionarySetValue(
        attributes,
        kCVPixelBufferPixelFormatTypeKey,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        عدم,
        0,
        &kCFTypeDictionaryKeyCallBacks,
        &kCFTypeDictionaryValueCallBacks);
    CFDictionarySetValue(attributes, kCVPixelBufferIOSurfacePropertiesKey, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(عدم, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(عدم, kCFNumberSInt32Type, &ctx->height);
    CFDictionarySetValue(attributes, kCVPixelBufferWidthKey, w);
    CFDictionarySetValue(attributes, kCVPixelBufferHeightKey, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixelBufferPoolCreate(
        عدم,
        عدم,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    אם (err == kCVReturnSuccess)
        החזר 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    החזר AVERROR_EXTERNAL;
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
    אם (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        החזר عدم;
    }

    buf = av_buffer_create((uint8_t *)pixbuf, size,
                           videotoolbox_buffer_release, عدم, 0);
    אם (!buf) {
        CVPixelBufferRelease(pixbuf);
        החזר عدم;
    }
    החזר buf;
}

ساكن فراغ vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    אם (fctx->pool) {
        CVPixelBufferPoolRelease(fctx->pool);
        fctx->pool = عدم;
    }
}

ساكن صحيح vt_frames_init(AVHWFramesContext *ctx)
{
    صحيح i, ret;

    עבור (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        אם (ctx->sw_format == supported_formats[i])
            اكسر;
    }
    אם (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        החזר AVERROR(ENOSYS);
    }

    אם (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(
                حجم(CVPixelBufferRef), ctx, vt_pool_alloc_buffer, عدم);
        אם (!ffhwframesctx(ctx)->pool_internal)
            החזר AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    אם (ret < 0)
        החזר ret;

    החזר 0;
}

ساكن صحيح vt_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    אם (!frame->buf[0])
        החזר AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    החזר 0;
}

ساكن صحيح vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   تعداد AVHWFrameTransferDirection dir,
                                   تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *fmts = av_malloc_array(2, حجم(*fmts));
    אם (!fmts)
        החזר AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    החזר 0;
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
    CFNumberRef num = عدم, den = عدم;
    AVRational avpar = src->sample_aspect_ratio;

    אם (avpar.num == 0) {
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferPixelAspectRatioKey);
        החזר 0;
    }

    av_reduce(&avpar.num, &avpar.den,
                avpar.num, avpar.den,
                0xFFFFFFFF);

    num = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.num);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &kCFCopyStringDictionaryKeyCallBacks,
                                    &kCFTypeDictionaryValueCallBacks);

    אם (!par || !num || !den) {
        אם (par) CFRelease(par);
        אם (num) CFRelease(num);
        אם (den) CFRelease(den);
        החזר AVERROR(ENOMEM);
    }

    CFDictionarySetValue(
        par,
        kCVImageBufferPixelAspectRatioHorizontalSpacingKey,
        num);
    CFDictionarySetValue(
        par,
        kCVImageBufferPixelAspectRatioVerticalSpacingKey,
        den);

    CVBufferSetAttachment(
        pixbuf,
        kCVImageBufferPixelAspectRatioKey,
        par,
        kCVAttachmentMode_ShouldPropagate
    );

    CFRelease(par);
    CFRelease(num);
    CFRelease(den);

    החזר 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(تعداد AVChromaLocation loc)
{
    بدل (loc) {
    حالة AVCHROMA_LOC_LEFT:
        החזר kCVImageBufferChromaLocation_Left;
    حالة AVCHROMA_LOC_CENTER:
        החזר kCVImageBufferChromaLocation_Center;
    حالة AVCHROMA_LOC_TOP:
        החזר kCVImageBufferChromaLocation_Top;
    حالة AVCHROMA_LOC_BOTTOM:
        החזר kCVImageBufferChromaLocation_Bottom;
    حالة AVCHROMA_LOC_TOPLEFT:
        החזר kCVImageBufferChromaLocation_TopLeft;
    حالة AVCHROMA_LOC_BOTTOMLEFT:
        החזר kCVImageBufferChromaLocation_BottomLeft;
    افتراضي:
        החזר عدم;
    }
}

ساكن صحيح vt_pixbuf_set_chromaloc(فراغ *log_ctx,
                                   CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    אם (loc) {
        CVBufferSetAttachment(
            pixbuf,
            kCVImageBufferChromaLocationTopFieldKey,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } אחרת
        CVBufferRemoveAttachment(
            pixbuf,
            kCVImageBufferChromaLocationTopFieldKey);

    החזר 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(تعداد AVColorSpace space)
{
    بدل (space) {
    حالة AVCOL_SPC_BT2020_CL:
    حالة AVCOL_SPC_BT2020_NCL:
#אם HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        אם (__builtin_available(macOS 10.11, iOS 9, *))
            החזר kCVImageBufferYCbCrMatrix_ITU_R_2020;
#endif
        החזר CFSTR("ITU_R_2020");
    حالة AVCOL_SPC_BT470BG:
    حالة AVCOL_SPC_SMPTE170M:
        החזר kCVImageBufferYCbCrMatrix_ITU_R_601_4;
    حالة AVCOL_SPC_BT709:
        החזר kCVImageBufferYCbCrMatrix_ITU_R_709_2;
    حالة AVCOL_SPC_SMPTE240M:
        החזר kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
    افتراضي:
#אם HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        אם (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            החזר CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
    حالة AVCOL_SPC_UNSPECIFIED:
        החזר عدم;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(تعداد AVColorPrimaries pri)
{
    بدل (pri) {
    حالة AVCOL_PRI_BT2020:
#אם HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        אם (__builtin_available(macOS 10.11, iOS 9, *))
            החזר kCVImageBufferColorPrimaries_ITU_R_2020;
#endif
        החזר CFSTR("ITU_R_2020");
    حالة AVCOL_PRI_BT709:
        החזר kCVImageBufferColorPrimaries_ITU_R_709_2;
    حالة AVCOL_PRI_SMPTE170M:
        החזר kCVImageBufferColorPrimaries_SMPTE_C;
    حالة AVCOL_PRI_BT470BG:
        החזר kCVImageBufferColorPrimaries_EBU_3213;
    افتراضي:
#אם HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        אם (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            החזר CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
    حالة AVCOL_PRI_UNSPECIFIED:
        החזר عدم;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(تعداد AVColorTransferCharacteristic trc)
{

    بدل (trc) {
    حالة AVCOL_TRC_SMPTE2084:
#אם HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        אם (__builtin_available(macOS 10.13, iOS 11, *))
            החזר kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
#endif
        החזר CFSTR("SMPTE_ST_2084_PQ");
    حالة AVCOL_TRC_BT2020_10:
    حالة AVCOL_TRC_BT2020_12:
#אם HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        אם (__builtin_available(macOS 10.11, iOS 9, *))
            החזר kCVImageBufferTransferFunction_ITU_R_2020;
#endif
        החזר CFSTR("ITU_R_2020");
    حالة AVCOL_TRC_BT709:
        החזר kCVImageBufferTransferFunction_ITU_R_709_2;
    حالة AVCOL_TRC_SMPTE240M:
        החזר kCVImageBufferTransferFunction_SMPTE_240M_1995;
    حالة AVCOL_TRC_SMPTE428:
#אם HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        אם (__builtin_available(macOS 10.12, iOS 10, *))
            החזר kCVImageBufferTransferFunction_SMPTE_ST_428_1;
#endif
        החזר CFSTR("SMPTE_ST_428_1");
    حالة AVCOL_TRC_ARIB_STD_B67:
#אם HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        אם (__builtin_available(macOS 10.13, iOS 11, *))
            החזר kCVImageBufferTransferFunction_ITU_R_2100_HLG;
#endif
        החזר CFSTR("ITU_R_2100_HLG");
    حالة AVCOL_TRC_GAMMA22:
        החזר kCVImageBufferTransferFunction_UseGamma;
    حالة AVCOL_TRC_GAMMA28:
        החזר kCVImageBufferTransferFunction_UseGamma;
    افتراضي:
#אם HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        אם (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            החזר CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    حالة AVCOL_TRC_UNSPECIFIED:
        החזר عدم;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
ساكن CFDictionaryRef vt_cv_buffer_copy_attachments(CVBufferRef buffer,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #אם (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        אם (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            החזר CVBufferCopyAttachments(buffer, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #אם (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(buffer, attachment_mode);
        החזר (dict) ? CFDictionaryCreateCopy(عدم, dict) : عدم;
    #אחרת
        החזר عدم; // Impossible, just make the compiler happy
    #endif
}

ساكن صحيح vt_pixbuf_set_colorspace(فراغ *log_ctx,
                                    CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    CGColorSpaceRef colorspace = عدم;
    CFStringRef colormatrix = عدم, colorpri = عدم, colortrc = عدم;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    אם (colormatrix)
        CVBufferSetAttachment(pixbuf, kCVImageBufferYCbCrMatrixKey,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    אחרת {
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferYCbCrMatrixKey);
        אם (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    אם (colorpri)
        CVBufferSetAttachment(pixbuf, kCVImageBufferColorPrimariesKey,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    אחרת {
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferColorPrimariesKey);
        אם (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    אם (colortrc)
        CVBufferSetAttachment(pixbuf, kCVImageBufferTransferFunctionKey,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    אחרת {
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferTransferFunctionKey);
        אם (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    אם (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    אחרת אם (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    אם (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(عدم, kCFNumberFloat32Type, &gamma);
        CVBufferSetAttachment(pixbuf, kCVImageBufferGammaLevelKey,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } אחרת
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferGammaLevelKey);

#אם (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    אם (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_buffer_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        אם (attachments) {
            colorspace =
                CVImageBufferCreateColorSpaceFromAttachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    אם (colorspace) {
        CVBufferSetAttachment(pixbuf, kCVImageBufferCGColorSpaceKey,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } אחרת
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferCGColorSpaceKey);

    החזר 0;
}

ساكن صحيح vt_pixbuf_set_attachments(فراغ *log_ctx,
                                     CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    صحيح ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    אם (ret < 0)
        החזר ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    אם (ret < 0)
        החזר ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    אם (ret < 0)
        החזר ret;
    החזר 0;
}

صحيح av_vt_pixbuf_set_attachments(فراغ *log_ctx,
                                 CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    החזר vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
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
    אם (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        החזר AVERROR_UNKNOWN;
    }

    אם (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        החזר AVERROR_UNKNOWN;
    }

    אם (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    אם (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        החזר AVERROR_UNKNOWN;
    }

    אם (CVPixelBufferIsPlanar(pixbuf)) {
        صحيح planes = CVPixelBufferGetPlaneCount(pixbuf);
        עבור (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } אחרת {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (فراغ *)(uintptr_t)map_flags);
    אם (ret < 0)
        اذهب unlock;

    החזר 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    החזר ret;
}

ساكن صحيح vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحيح err;

    אם (dst->width > hwfc->width || dst->height > hwfc->height)
        החזר AVERROR(EINVAL);

    map = av_frame_alloc();
    אם (!map)
        החזר AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    אם (err)
        اذهب fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    אם (err)
        اذهب fail;

    err = 0;
fail:
    av_frame_free(&map);
    החזר err;
}

ساكن صحيح vt_transfer_data_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحيح err;

    אם (src->width > hwfc->width || src->height > hwfc->height)
        החזר AVERROR(EINVAL);

    map = av_frame_alloc();
    אם (!map)
        החזר AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    אם (err)
        اذهب fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    אם (err)
        اذهب fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixelBufferRef)dst->data[3], src);
    אם (err)
        اذهب fail;

    err = 0;
fail:
    av_frame_free(&map);
    החזר err;
}

ساكن صحيح vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       ثابت AVFrame *src, صحيح flags)
{
    صحيح err;

    אם (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    אחרת אם (dst->format != hwfc->sw_format)
        החזר AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    אם (err)
        החזר err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    אם (err)
        החזר err;

    החזר 0;
}

ساكن صحيح vt_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                            AVDictionary *opts, صحيح flags)
{
    אם (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        החזר AVERROR_UNKNOWN;
    }

    החזר 0;
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
