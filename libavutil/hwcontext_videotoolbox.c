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

#include "config.h"

#include <stdint.h>
#include <string.h>

#include <VideoToolbox/VideoToolbox.h>

#include "buffer.h"
#include "buffer_internal.h"
#include "common.h"
#include "hwcontext.h"
#include "hwcontext_internal.h"
#include "hwcontext_videotoolbox.h"
#include "attributes.h"
#include "mem.h"
#include "pixfmt.h"
#include "pixdesc.h"

typedef struct VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixelBufferPoolRef pool;
} VTFramesContext;

static const struct {
    uint32_t cv_fmt;
    bool full_range;
    enum AVPixelFormat pix_fmt;
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
#якщо HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#endif
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

static const enum AVPixelFormat supported_formats[] = {
#ifdef kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#endif
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#якщо HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#якщо HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#endif
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

static ціле vt_frames_get_constraints(AVHWDeviceContext *ctx,
                                     const void *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    ціле i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    sizeof(*constraints->valid_sw_formats));
    якщо (!constraints->valid_sw_formats)
        повернути AVERROR(ENOMEM);

    для (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, sizeof(*constraints->valid_hw_formats));
    якщо (!constraints->valid_hw_formats)
        повернути AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    повернути 0;
}

enum AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    ціле i;
    для (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        якщо (cv_pix_fmts[i].cv_fmt == cv_fmt)
            повернути cv_pix_fmts[i].pix_fmt;
    }
    повернути AV_PIX_FMT_NONE;
}

static uint32_t vt_format_from_pixfmt(enum AVPixelFormat pix_fmt,
                                      enum AVColorRange range)
{
    для (ціле i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        якщо (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            ціле full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            якщо (range == AVCOL_RANGE_UNSPECIFIED)
                повернути cv_pix_fmts[i].cv_fmt;

            якщо (cv_pix_fmts[i].full_range == full_range)
                повернути cv_pix_fmts[i].cv_fmt;
        }
    }

    повернути 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(enum AVPixelFormat pix_fmt)
{
    повернути av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(enum AVPixelFormat pix_fmt, bool full_range)
{
    повернути vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

static ціле vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef attributes, iosurface_properties;

    attributes = CFDictionaryCreateMutable(
        NULL,
        2,
        &kCFTypeDictionaryKeyCallBacks,
        &kCFTypeDictionaryValueCallBacks);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(NULL, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionarySetValue(
        attributes,
        kCVPixelBufferPixelFormatTypeKey,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        NULL,
        0,
        &kCFTypeDictionaryKeyCallBacks,
        &kCFTypeDictionaryValueCallBacks);
    CFDictionarySetValue(attributes, kCVPixelBufferIOSurfacePropertiesKey, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(NULL, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(NULL, kCFNumberSInt32Type, &ctx->height);
    CFDictionarySetValue(attributes, kCVPixelBufferWidthKey, w);
    CFDictionarySetValue(attributes, kCVPixelBufferHeightKey, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixelBufferPoolCreate(
        NULL,
        NULL,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    якщо (err == kCVReturnSuccess)
        повернути 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    повернути AVERROR_EXTERNAL;
}

static void videotoolbox_buffer_release(void *opaque, uint8_t *data)
{
    CVPixelBufferRelease((CVPixelBufferRef)data);
}

static AVBufferRef *vt_pool_alloc_buffer(void *opaque, size_t size)
{
    CVPixelBufferRef pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixelBufferPoolCreatePixelBuffer(
        NULL,
        fctx->pool,
        &pixbuf
    );
    якщо (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        повернути NULL;
    }

    buf = av_buffer_create((uint8_t *)pixbuf, size,
                           videotoolbox_buffer_release, NULL, 0);
    якщо (!buf) {
        CVPixelBufferRelease(pixbuf);
        повернути NULL;
    }
    повернути buf;
}

static void vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    якщо (fctx->pool) {
        CVPixelBufferPoolRelease(fctx->pool);
        fctx->pool = NULL;
    }
}

static ціле vt_frames_init(AVHWFramesContext *ctx)
{
    ціле i, ret;

    для (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        якщо (ctx->sw_format == supported_formats[i])
            break;
    }
    якщо (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        повернути AVERROR(ENOSYS);
    }

    якщо (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(
                sizeof(CVPixelBufferRef), ctx, vt_pool_alloc_buffer, NULL);
        якщо (!ffhwframesctx(ctx)->pool_internal)
            повернути AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    якщо (ret < 0)
        повернути ret;

    повернути 0;
}

static ціле vt_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    якщо (!frame->buf[0])
        повернути AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    повернути 0;
}

static ціле vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   enum AVHWFrameTransferDirection dir,
                                   enum AVPixelFormat **formats)
{
    enum AVPixelFormat *fmts = av_malloc_array(2, sizeof(*fmts));
    якщо (!fmts)
        повернути AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    повернути 0;
}

static void vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)hwmap->source->data[3];

    CVPixelBufferUnlockBaseAddress(pixbuf, (uintptr_t)hwmap->priv);
}

static ціле vt_pixbuf_set_par(void *log_ctx,
                             CVPixelBufferRef pixbuf, const AVFrame *src)
{
    CFMutableDictionaryRef par = NULL;
    CFNumberRef num = NULL, den = NULL;
    AVRational avpar = src->sample_aspect_ratio;

    якщо (avpar.num == 0) {
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferPixelAspectRatioKey);
        повернути 0;
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

    якщо (!par || !num || !den) {
        якщо (par) CFRelease(par);
        якщо (num) CFRelease(num);
        якщо (den) CFRelease(den);
        повернути AVERROR(ENOMEM);
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

    повернути 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(enum AVChromaLocation loc)
{
    switch (loc) {
    case AVCHROMA_LOC_LEFT:
        повернути kCVImageBufferChromaLocation_Left;
    case AVCHROMA_LOC_CENTER:
        повернути kCVImageBufferChromaLocation_Center;
    case AVCHROMA_LOC_TOP:
        повернути kCVImageBufferChromaLocation_Top;
    case AVCHROMA_LOC_BOTTOM:
        повернути kCVImageBufferChromaLocation_Bottom;
    case AVCHROMA_LOC_TOPLEFT:
        повернути kCVImageBufferChromaLocation_TopLeft;
    case AVCHROMA_LOC_BOTTOMLEFT:
        повернути kCVImageBufferChromaLocation_BottomLeft;
    default:
        повернути NULL;
    }
}

static ціле vt_pixbuf_set_chromaloc(void *log_ctx,
                                   CVPixelBufferRef pixbuf, const AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    якщо (loc) {
        CVBufferSetAttachment(
            pixbuf,
            kCVImageBufferChromaLocationTopFieldKey,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } інакше
        CVBufferRemoveAttachment(
            pixbuf,
            kCVImageBufferChromaLocationTopFieldKey);

    повернути 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(enum AVColorSpace space)
{
    switch (space) {
    case AVCOL_SPC_BT2020_CL:
    case AVCOL_SPC_BT2020_NCL:
#якщо HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        якщо (__builtin_available(macOS 10.11, iOS 9, *))
            повернути kCVImageBufferYCbCrMatrix_ITU_R_2020;
#endif
        повернути CFSTR("ITU_R_2020");
    case AVCOL_SPC_BT470BG:
    case AVCOL_SPC_SMPTE170M:
        повернути kCVImageBufferYCbCrMatrix_ITU_R_601_4;
    case AVCOL_SPC_BT709:
        повернути kCVImageBufferYCbCrMatrix_ITU_R_709_2;
    case AVCOL_SPC_SMPTE240M:
        повернути kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
    default:
#якщо HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        якщо (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            повернути CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
    case AVCOL_SPC_UNSPECIFIED:
        повернути NULL;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(enum AVColorPrimaries pri)
{
    switch (pri) {
    case AVCOL_PRI_BT2020:
#якщо HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        якщо (__builtin_available(macOS 10.11, iOS 9, *))
            повернути kCVImageBufferColorPrimaries_ITU_R_2020;
#endif
        повернути CFSTR("ITU_R_2020");
    case AVCOL_PRI_BT709:
        повернути kCVImageBufferColorPrimaries_ITU_R_709_2;
    case AVCOL_PRI_SMPTE170M:
        повернути kCVImageBufferColorPrimaries_SMPTE_C;
    case AVCOL_PRI_BT470BG:
        повернути kCVImageBufferColorPrimaries_EBU_3213;
    default:
#якщо HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        якщо (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            повернути CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
    case AVCOL_PRI_UNSPECIFIED:
        повернути NULL;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(enum AVColorTransferCharacteristic trc)
{

    switch (trc) {
    case AVCOL_TRC_SMPTE2084:
#якщо HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        якщо (__builtin_available(macOS 10.13, iOS 11, *))
            повернути kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
#endif
        повернути CFSTR("SMPTE_ST_2084_PQ");
    case AVCOL_TRC_BT2020_10:
    case AVCOL_TRC_BT2020_12:
#якщо HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        якщо (__builtin_available(macOS 10.11, iOS 9, *))
            повернути kCVImageBufferTransferFunction_ITU_R_2020;
#endif
        повернути CFSTR("ITU_R_2020");
    case AVCOL_TRC_BT709:
        повернути kCVImageBufferTransferFunction_ITU_R_709_2;
    case AVCOL_TRC_SMPTE240M:
        повернути kCVImageBufferTransferFunction_SMPTE_240M_1995;
    case AVCOL_TRC_SMPTE428:
#якщо HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        якщо (__builtin_available(macOS 10.12, iOS 10, *))
            повернути kCVImageBufferTransferFunction_SMPTE_ST_428_1;
#endif
        повернути CFSTR("SMPTE_ST_428_1");
    case AVCOL_TRC_ARIB_STD_B67:
#якщо HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        якщо (__builtin_available(macOS 10.13, iOS 11, *))
            повернути kCVImageBufferTransferFunction_ITU_R_2100_HLG;
#endif
        повернути CFSTR("ITU_R_2100_HLG");
    case AVCOL_TRC_GAMMA22:
        повернути kCVImageBufferTransferFunction_UseGamma;
    case AVCOL_TRC_GAMMA28:
        повернути kCVImageBufferTransferFunction_UseGamma;
    default:
#якщо HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        якщо (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            повернути CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    case AVCOL_TRC_UNSPECIFIED:
        повернути NULL;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
static CFDictionaryRef vt_cv_buffer_copy_attachments(CVBufferRef buffer,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #якщо (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        якщо (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            повернути CVBufferCopyAttachments(buffer, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #якщо (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(buffer, attachment_mode);
        повернути (dict) ? CFDictionaryCreateCopy(NULL, dict) : NULL;
    #інакше
        повернути NULL; // Impossible, just make the compiler happy
    #endif
}

static ціле vt_pixbuf_set_colorspace(void *log_ctx,
                                    CVPixelBufferRef pixbuf, const AVFrame *src)
{
    CGColorSpaceRef colorspace = NULL;
    CFStringRef colormatrix = NULL, colorpri = NULL, colortrc = NULL;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    якщо (colormatrix)
        CVBufferSetAttachment(pixbuf, kCVImageBufferYCbCrMatrixKey,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    інакше {
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferYCbCrMatrixKey);
        якщо (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    якщо (colorpri)
        CVBufferSetAttachment(pixbuf, kCVImageBufferColorPrimariesKey,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    інакше {
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferColorPrimariesKey);
        якщо (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    якщо (colortrc)
        CVBufferSetAttachment(pixbuf, kCVImageBufferTransferFunctionKey,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    інакше {
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferTransferFunctionKey);
        якщо (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    якщо (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    інакше якщо (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    якщо (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(NULL, kCFNumberFloat32Type, &gamma);
        CVBufferSetAttachment(pixbuf, kCVImageBufferGammaLevelKey,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } інакше
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferGammaLevelKey);

#якщо (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    якщо (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_buffer_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        якщо (attachments) {
            colorspace =
                CVImageBufferCreateColorSpaceFromAttachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    якщо (colorspace) {
        CVBufferSetAttachment(pixbuf, kCVImageBufferCGColorSpaceKey,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } інакше
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferCGColorSpaceKey);

    повернути 0;
}

static ціле vt_pixbuf_set_attachments(void *log_ctx,
                                     CVPixelBufferRef pixbuf, const AVFrame *src)
{
    ціле ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    якщо (ret < 0)
        повернути ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    якщо (ret < 0)
        повернути ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    якщо (ret < 0)
        повернути ret;
    повернути 0;
}

ціле av_vt_pixbuf_set_attachments(void *log_ctx,
                                 CVPixelBufferRef pixbuf, const AVFrame *src)
{
    повернути vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

static ціле vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, const AVFrame *src,
                        ціле flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)src->data[3];
    OSType pixel_format = CVPixelBufferGetPixelFormatType(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    ціле ret;
    ціле i;
    enum AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    якщо (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        повернути AVERROR_UNKNOWN;
    }

    якщо (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        повернути AVERROR_UNKNOWN;
    }

    якщо (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    якщо (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        повернути AVERROR_UNKNOWN;
    }

    якщо (CVPixelBufferIsPlanar(pixbuf)) {
        ціле planes = CVPixelBufferGetPlaneCount(pixbuf);
        для (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } інакше {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (void *)(uintptr_t)map_flags);
    якщо (ret < 0)
        goto unlock;

    повернути 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    повернути ret;
}

static ціле vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, const AVFrame *src)
{
    AVFrame *map;
    ціле err;

    якщо (dst->width > hwfc->width || dst->height > hwfc->height)
        повернути AVERROR(EINVAL);

    map = av_frame_alloc();
    якщо (!map)
        повернути AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    якщо (err)
        goto fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    якщо (err)
        goto fail;

    err = 0;
fail:
    av_frame_free(&map);
    повернути err;
}

static ціле vt_transfer_data_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, const AVFrame *src)
{
    AVFrame *map;
    ціле err;

    якщо (src->width > hwfc->width || src->height > hwfc->height)
        повернути AVERROR(EINVAL);

    map = av_frame_alloc();
    якщо (!map)
        повернути AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    якщо (err)
        goto fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    якщо (err)
        goto fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixelBufferRef)dst->data[3], src);
    якщо (err)
        goto fail;

    err = 0;
fail:
    av_frame_free(&map);
    повернути err;
}

static ціле vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       const AVFrame *src, ціле flags)
{
    ціле err;

    якщо (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    інакше якщо (dst->format != hwfc->sw_format)
        повернути AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    якщо (err)
        повернути err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    якщо (err)
        повернути err;

    повернути 0;
}

static ціле vt_device_create(AVHWDeviceContext *ctx, const char *device,
                            AVDictionary *opts, ціле flags)
{
    якщо (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        повернути AVERROR_UNKNOWN;
    }

    повернути 0;
}

const HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .frames_hwctx_size    = sizeof(VTFramesContext),

    .device_create        = vt_device_create,
    .frames_init          = vt_frames_init,
    .frames_get_buffer    = vt_get_buffer,
    .frames_get_constraints = vt_frames_get_constraints,
    .frames_uninit        = vt_frames_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_data_to     = vt_transfer_data_to,
    .transfer_data_from   = vt_transfer_data_from,
    .map_from             = vt_map_from,

    .pix_fmts = (const enum AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
