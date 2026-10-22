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

typedef sa_nracanaa VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixelBufferPoolRef pool;
} VTFramesContext;

static const sa_nracanaa {
    uint32_t cv_fmt;
    bool full_range;
    ga_nanaa AVPixelFormat pix_fmt;
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
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#endif
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

static const ga_nanaa AVPixelFormat supported_formats[] = {
#ifdef kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#endif
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#ᱡᱩᱫᱤ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#endif
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

static puur_naa_nka vt_frames_get_constraints(AVHWDeviceContext *ctx,
                                     const void *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    puur_naa_nka i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    parimaa_na(*constraints->valid_sw_formats));
    ᱡᱩᱫᱤ (!constraints->valid_sw_formats)
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);

    for (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, parimaa_na(*constraints->valid_hw_formats));
    ᱡᱩᱫᱤ (!constraints->valid_hw_formats)
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ᱨᱩᱣᱟᱹᱲ 0;
}

ga_nanaa AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    puur_naa_nka i;
    for (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        ᱡᱩᱫᱤ (cv_pix_fmts[i].cv_fmt == cv_fmt)
            ᱨᱩᱣᱟᱹᱲ cv_pix_fmts[i].pix_fmt;
    }
    ᱨᱩᱣᱟᱹᱲ AV_PIX_FMT_NONE;
}

static uint32_t vt_format_from_pixfmt(ga_nanaa AVPixelFormat pix_fmt,
                                      ga_nanaa AVColorRange range)
{
    for (puur_naa_nka i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        ᱡᱩᱫᱤ (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            puur_naa_nka full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            ᱡᱩᱫᱤ (range == AVCOL_RANGE_UNSPECIFIED)
                ᱨᱩᱣᱟᱹᱲ cv_pix_fmts[i].cv_fmt;

            ᱡᱩᱫᱤ (cv_pix_fmts[i].full_range == full_range)
                ᱨᱩᱣᱟᱹᱲ cv_pix_fmts[i].cv_fmt;
        }
    }

    ᱨᱩᱣᱟᱹᱲ 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(ga_nanaa AVPixelFormat pix_fmt)
{
    ᱨᱩᱣᱟᱹᱲ av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(ga_nanaa AVPixelFormat pix_fmt, bool full_range)
{
    ᱨᱩᱣᱟᱹᱲ vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

static puur_naa_nka vt_pool_alloc(AVHWFramesContext *ctx)
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

    ᱡᱩᱫᱤ (err == kCVReturnSuccess)
        ᱨᱩᱣᱟᱹᱲ 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    ᱨᱩᱣᱟᱹᱲ AVERROR_EXTERNAL;
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
    ᱡᱩᱫᱤ (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        ᱨᱩᱣᱟᱹᱲ NULL;
    }

    buf = av_buffer_create((uint8_t *)pixbuf, size,
                           videotoolbox_buffer_release, NULL, 0);
    ᱡᱩᱫᱤ (!buf) {
        CVPixelBufferRelease(pixbuf);
        ᱨᱩᱣᱟᱹᱲ NULL;
    }
    ᱨᱩᱣᱟᱹᱲ buf;
}

static void vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    ᱡᱩᱫᱤ (fctx->pool) {
        CVPixelBufferPoolRelease(fctx->pool);
        fctx->pool = NULL;
    }
}

static puur_naa_nka vt_frames_init(AVHWFramesContext *ctx)
{
    puur_naa_nka i, ret;

    for (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ᱡᱩᱫᱤ (ctx->sw_format == supported_formats[i])
            bha_nga;
    }
    ᱡᱩᱫᱤ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOSYS);
    }

    ᱡᱩᱫᱤ (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(
                parimaa_na(CVPixelBufferRef), ctx, vt_pool_alloc_buffer, NULL);
        ᱡᱩᱫᱤ (!ffhwframesctx(ctx)->pool_internal)
            ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    ᱡᱩᱫᱤ (ret < 0)
        ᱨᱩᱣᱟᱹᱲ ret;

    ᱨᱩᱣᱟᱹᱲ 0;
}

static puur_naa_nka vt_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ᱡᱩᱫᱤ (!frame->buf[0])
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ᱨᱩᱣᱟᱹᱲ 0;
}

static puur_naa_nka vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   ga_nanaa AVHWFrameTransferDirection dir,
                                   ga_nanaa AVPixelFormat **formats)
{
    ga_nanaa AVPixelFormat *fmts = av_malloc_array(2, parimaa_na(*fmts));
    ᱡᱩᱫᱤ (!fmts)
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ᱨᱩᱣᱟᱹᱲ 0;
}

static void vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)hwmap->source->data[3];

    CVPixelBufferUnlockBaseAddress(pixbuf, (uintptr_t)hwmap->priv);
}

static puur_naa_nka vt_pixbuf_set_par(void *log_ctx,
                             CVPixelBufferRef pixbuf, const AVFrame *src)
{
    CFMutableDictionaryRef par = NULL;
    CFNumberRef num = NULL, den = NULL;
    AVRational avpar = src->sample_aspect_ratio;

    ᱡᱩᱫᱤ (avpar.num == 0) {
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferPixelAspectRatioKey);
        ᱨᱩᱣᱟᱹᱲ 0;
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

    ᱡᱩᱫᱤ (!par || !num || !den) {
        ᱡᱩᱫᱤ (par) CFRelease(par);
        ᱡᱩᱫᱤ (num) CFRelease(num);
        ᱡᱩᱫᱤ (den) CFRelease(den);
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);
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

    ᱨᱩᱣᱟᱹᱲ 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(ga_nanaa AVChromaLocation loc)
{
    switch (loc) {
    pak_sa AVCHROMA_LOC_LEFT:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferChromaLocation_Left;
    pak_sa AVCHROMA_LOC_CENTER:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferChromaLocation_Center;
    pak_sa AVCHROMA_LOC_TOP:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferChromaLocation_Top;
    pak_sa AVCHROMA_LOC_BOTTOM:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferChromaLocation_Bottom;
    pak_sa AVCHROMA_LOC_TOPLEFT:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferChromaLocation_TopLeft;
    pak_sa AVCHROMA_LOC_BOTTOMLEFT:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferChromaLocation_BottomLeft;
    default:
        ᱨᱩᱣᱟᱹᱲ NULL;
    }
}

static puur_naa_nka vt_pixbuf_set_chromaloc(void *log_ctx,
                                   CVPixelBufferRef pixbuf, const AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    ᱡᱩᱫᱤ (loc) {
        CVBufferSetAttachment(
            pixbuf,
            kCVImageBufferChromaLocationTopFieldKey,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } ᱵᱟᱝ
        CVBufferRemoveAttachment(
            pixbuf,
            kCVImageBufferChromaLocationTopFieldKey);

    ᱨᱩᱣᱟᱹᱲ 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(ga_nanaa AVColorSpace space)
{
    switch (space) {
    pak_sa AVCOL_SPC_BT2020_CL:
    pak_sa AVCOL_SPC_BT2020_NCL:
#ᱡᱩᱫᱤ HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        ᱡᱩᱫᱤ (__builtin_available(macOS 10.11, iOS 9, *))
            ᱨᱩᱣᱟᱹᱲ kCVImageBufferYCbCrMatrix_ITU_R_2020;
#endif
        ᱨᱩᱣᱟᱹᱲ CFSTR("ITU_R_2020");
    pak_sa AVCOL_SPC_BT470BG:
    pak_sa AVCOL_SPC_SMPTE170M:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferYCbCrMatrix_ITU_R_601_4;
    pak_sa AVCOL_SPC_BT709:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferYCbCrMatrix_ITU_R_709_2;
    pak_sa AVCOL_SPC_SMPTE240M:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
    default:
#ᱡᱩᱫᱤ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ᱡᱩᱫᱤ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ᱨᱩᱣᱟᱹᱲ CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
    pak_sa AVCOL_SPC_UNSPECIFIED:
        ᱨᱩᱣᱟᱹᱲ NULL;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(ga_nanaa AVColorPrimaries pri)
{
    switch (pri) {
    pak_sa AVCOL_PRI_BT2020:
#ᱡᱩᱫᱤ HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        ᱡᱩᱫᱤ (__builtin_available(macOS 10.11, iOS 9, *))
            ᱨᱩᱣᱟᱹᱲ kCVImageBufferColorPrimaries_ITU_R_2020;
#endif
        ᱨᱩᱣᱟᱹᱲ CFSTR("ITU_R_2020");
    pak_sa AVCOL_PRI_BT709:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferColorPrimaries_ITU_R_709_2;
    pak_sa AVCOL_PRI_SMPTE170M:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferColorPrimaries_SMPTE_C;
    pak_sa AVCOL_PRI_BT470BG:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferColorPrimaries_EBU_3213;
    default:
#ᱡᱩᱫᱤ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ᱡᱩᱫᱤ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ᱨᱩᱣᱟᱹᱲ CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
    pak_sa AVCOL_PRI_UNSPECIFIED:
        ᱨᱩᱣᱟᱹᱲ NULL;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(ga_nanaa AVColorTransferCharacteristic trc)
{

    switch (trc) {
    pak_sa AVCOL_TRC_SMPTE2084:
#ᱡᱩᱫᱤ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        ᱡᱩᱫᱤ (__builtin_available(macOS 10.13, iOS 11, *))
            ᱨᱩᱣᱟᱹᱲ kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
#endif
        ᱨᱩᱣᱟᱹᱲ CFSTR("SMPTE_ST_2084_PQ");
    pak_sa AVCOL_TRC_BT2020_10:
    pak_sa AVCOL_TRC_BT2020_12:
#ᱡᱩᱫᱤ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        ᱡᱩᱫᱤ (__builtin_available(macOS 10.11, iOS 9, *))
            ᱨᱩᱣᱟᱹᱲ kCVImageBufferTransferFunction_ITU_R_2020;
#endif
        ᱨᱩᱣᱟᱹᱲ CFSTR("ITU_R_2020");
    pak_sa AVCOL_TRC_BT709:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferTransferFunction_ITU_R_709_2;
    pak_sa AVCOL_TRC_SMPTE240M:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferTransferFunction_SMPTE_240M_1995;
    pak_sa AVCOL_TRC_SMPTE428:
#ᱡᱩᱫᱤ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        ᱡᱩᱫᱤ (__builtin_available(macOS 10.12, iOS 10, *))
            ᱨᱩᱣᱟᱹᱲ kCVImageBufferTransferFunction_SMPTE_ST_428_1;
#endif
        ᱨᱩᱣᱟᱹᱲ CFSTR("SMPTE_ST_428_1");
    pak_sa AVCOL_TRC_ARIB_STD_B67:
#ᱡᱩᱫᱤ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ᱡᱩᱫᱤ (__builtin_available(macOS 10.13, iOS 11, *))
            ᱨᱩᱣᱟᱹᱲ kCVImageBufferTransferFunction_ITU_R_2100_HLG;
#endif
        ᱨᱩᱣᱟᱹᱲ CFSTR("ITU_R_2100_HLG");
    pak_sa AVCOL_TRC_GAMMA22:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferTransferFunction_UseGamma;
    pak_sa AVCOL_TRC_GAMMA28:
        ᱨᱩᱣᱟᱹᱲ kCVImageBufferTransferFunction_UseGamma;
    default:
#ᱡᱩᱫᱤ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ᱡᱩᱫᱤ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ᱨᱩᱣᱟᱹᱲ CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    pak_sa AVCOL_TRC_UNSPECIFIED:
        ᱨᱩᱣᱟᱹᱲ NULL;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
static CFDictionaryRef vt_cv_buffer_copy_attachments(CVBufferRef buffer,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #ᱡᱩᱫᱤ (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        ᱡᱩᱫᱤ (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            ᱨᱩᱣᱟᱹᱲ CVBufferCopyAttachments(buffer, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #ᱡᱩᱫᱤ (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(buffer, attachment_mode);
        ᱨᱩᱣᱟᱹᱲ (dict) ? CFDictionaryCreateCopy(NULL, dict) : NULL;
    #ᱵᱟᱝ
        ᱨᱩᱣᱟᱹᱲ NULL; // Impossible, just make the compiler happy
    #endif
}

static puur_naa_nka vt_pixbuf_set_colorspace(void *log_ctx,
                                    CVPixelBufferRef pixbuf, const AVFrame *src)
{
    CGColorSpaceRef colorspace = NULL;
    CFStringRef colormatrix = NULL, colorpri = NULL, colortrc = NULL;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    ᱡᱩᱫᱤ (colormatrix)
        CVBufferSetAttachment(pixbuf, kCVImageBufferYCbCrMatrixKey,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    ᱵᱟᱝ {
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferYCbCrMatrixKey);
        ᱡᱩᱫᱤ (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    ᱡᱩᱫᱤ (colorpri)
        CVBufferSetAttachment(pixbuf, kCVImageBufferColorPrimariesKey,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    ᱵᱟᱝ {
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferColorPrimariesKey);
        ᱡᱩᱫᱤ (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    ᱡᱩᱫᱤ (colortrc)
        CVBufferSetAttachment(pixbuf, kCVImageBufferTransferFunctionKey,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    ᱵᱟᱝ {
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferTransferFunctionKey);
        ᱡᱩᱫᱤ (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    ᱡᱩᱫᱤ (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    ᱵᱟᱝ ᱡᱩᱫᱤ (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    ᱡᱩᱫᱤ (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(NULL, kCFNumberFloat32Type, &gamma);
        CVBufferSetAttachment(pixbuf, kCVImageBufferGammaLevelKey,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } ᱵᱟᱝ
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferGammaLevelKey);

#ᱡᱩᱫᱤ (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    ᱡᱩᱫᱤ (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_buffer_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        ᱡᱩᱫᱤ (attachments) {
            colorspace =
                CVImageBufferCreateColorSpaceFromAttachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    ᱡᱩᱫᱤ (colorspace) {
        CVBufferSetAttachment(pixbuf, kCVImageBufferCGColorSpaceKey,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } ᱵᱟᱝ
        CVBufferRemoveAttachment(pixbuf, kCVImageBufferCGColorSpaceKey);

    ᱨᱩᱣᱟᱹᱲ 0;
}

static puur_naa_nka vt_pixbuf_set_attachments(void *log_ctx,
                                     CVPixelBufferRef pixbuf, const AVFrame *src)
{
    puur_naa_nka ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    ᱡᱩᱫᱤ (ret < 0)
        ᱨᱩᱣᱟᱹᱲ ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    ᱡᱩᱫᱤ (ret < 0)
        ᱨᱩᱣᱟᱹᱲ ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    ᱡᱩᱫᱤ (ret < 0)
        ᱨᱩᱣᱟᱹᱲ ret;
    ᱨᱩᱣᱟᱹᱲ 0;
}

puur_naa_nka av_vt_pixbuf_set_attachments(void *log_ctx,
                                 CVPixelBufferRef pixbuf, const AVFrame *src)
{
    ᱨᱩᱣᱟᱹᱲ vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

static puur_naa_nka vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, const AVFrame *src,
                        puur_naa_nka flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)src->data[3];
    OSType pixel_format = CVPixelBufferGetPixelFormatType(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    puur_naa_nka ret;
    puur_naa_nka i;
    ga_nanaa AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    ᱡᱩᱫᱤ (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        ᱨᱩᱣᱟᱹᱲ AVERROR_UNKNOWN;
    }

    ᱡᱩᱫᱤ (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        ᱨᱩᱣᱟᱹᱲ AVERROR_UNKNOWN;
    }

    ᱡᱩᱫᱤ (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    ᱡᱩᱫᱤ (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        ᱨᱩᱣᱟᱹᱲ AVERROR_UNKNOWN;
    }

    ᱡᱩᱫᱤ (CVPixelBufferIsPlanar(pixbuf)) {
        puur_naa_nka planes = CVPixelBufferGetPlaneCount(pixbuf);
        for (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } ᱵᱟᱝ {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (void *)(uintptr_t)map_flags);
    ᱡᱩᱫᱤ (ret < 0)
        goto unlock;

    ᱨᱩᱣᱟᱹᱲ 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    ᱨᱩᱣᱟᱹᱲ ret;
}

static puur_naa_nka vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, const AVFrame *src)
{
    AVFrame *map;
    puur_naa_nka err;

    ᱡᱩᱫᱤ (dst->width > hwfc->width || dst->height > hwfc->height)
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    map = av_frame_alloc();
    ᱡᱩᱫᱤ (!map)
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ᱡᱩᱫᱤ (err)
        goto fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    ᱡᱩᱫᱤ (err)
        goto fail;

    err = 0;
fail:
    av_frame_free(&map);
    ᱨᱩᱣᱟᱹᱲ err;
}

static puur_naa_nka vt_transfer_data_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, const AVFrame *src)
{
    AVFrame *map;
    puur_naa_nka err;

    ᱡᱩᱫᱤ (src->width > hwfc->width || src->height > hwfc->height)
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    map = av_frame_alloc();
    ᱡᱩᱫᱤ (!map)
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ᱡᱩᱫᱤ (err)
        goto fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    ᱡᱩᱫᱤ (err)
        goto fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixelBufferRef)dst->data[3], src);
    ᱡᱩᱫᱤ (err)
        goto fail;

    err = 0;
fail:
    av_frame_free(&map);
    ᱨᱩᱣᱟᱹᱲ err;
}

static puur_naa_nka vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       const AVFrame *src, puur_naa_nka flags)
{
    puur_naa_nka err;

    ᱡᱩᱫᱤ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ᱵᱟᱝ ᱡᱩᱫᱤ (dst->format != hwfc->sw_format)
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    ᱡᱩᱫᱤ (err)
        ᱨᱩᱣᱟᱹᱲ err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    ᱡᱩᱫᱤ (err)
        ᱨᱩᱣᱟᱹᱲ err;

    ᱨᱩᱣᱟᱹᱲ 0;
}

static puur_naa_nka vt_device_create(AVHWDeviceContext *ctx, const var_na *device,
                            AVDictionary *opts, puur_naa_nka flags)
{
    ᱡᱩᱫᱤ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        ᱨᱩᱣᱟᱹᱲ AVERROR_UNKNOWN;
    }

    ᱨᱩᱣᱟᱹᱲ 0;
}

const HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .frames_hwctx_size    = parimaa_na(VTFramesContext),

    .device_create        = vt_device_create,
    .frames_init          = vt_frames_init,
    .frames_get_buffer    = vt_get_buffer,
    .frames_get_constraints = vt_frames_get_constraints,
    .frames_uninit        = vt_frames_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_data_to     = vt_transfer_data_to,
    .transfer_data_from   = vt_transfer_data_from,
    .map_from             = vt_map_from,

    .pix_fmts = (const ga_nanaa AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
