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

#అన్తర్భావ "config.h"

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ <VideoToolbox/VideoToolbox.h>

#అన్తర్భావ "buffer.h"
#అన్తర్భావ "buffer_internal.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "hwcontext_videotoolbox.h"
#అన్తర్భావ "attributes.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "pixfmt.h"
#అన్తర్భావ "pixdesc.h"

రకనిర్వచనం నిర్మాణం VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixel_బఫరు_Pool_Ref pool;
} VTFramesContext;

స్థిర స్థిరరాశి నిర్మాణం {
    uint32_t cv_fmt;
    bool నిండిన_range;
    గణన AVPixelFormat pix_fmt;
} cv_pix_fmts[] = {
    { kCVPixelFormatType_420YpCbCr8Planar,              false, AV_PIX_FMT_YUV420P },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr8_Planar_నిండిన_Range,     true,  AV_PIX_FMT_YUV420P },
    { kCVPixelFormatType_422YpCbCr8,                    false, AV_PIX_FMT_UYVY422 },
    { kCVPixelFormatType_32BGRA,                        true,  AV_PIX_FMT_BGRA },
#నిర్వచితమైతే k_CFCore_Foundation_సంస్కరణ_Number10_7
    { kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV12 },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr8_Bi_Planar_నిండిన_Range,   true,  AV_PIX_FMT_NV12 },
    { kCVPixelFormatType_4444AYpCbCr8,                  false, AV_PIX_FMT_AYUV },
    { kCVPixelFormatType_4444AYpCbCr16,                 false, AV_PIX_FMT_AYUV64 },
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { k_CVPixel_Format_Type_420_Yp_Cb_Cr10_Bi_Planar_నిండిన_Range,  true,  AV_PIX_FMT_P010 },
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { k_CVPixel_Format_Type_422_Yp_Cb_Cr8_Bi_Planar_నిండిన_Range,   true,  AV_PIX_FMT_NV16 },
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { k_CVPixel_Format_Type_422_Yp_Cb_Cr10_Bi_Planar_నిండిన_Range,  true,  AV_PIX_FMT_P210 },
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { k_CVPixel_Format_Type_444_Yp_Cb_Cr8_Bi_Planar_నిండిన_Range,   true,  AV_PIX_FMT_NV24 },
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { k_CVPixel_Format_Type_444_Yp_Cb_Cr10_Bi_Planar_నిండిన_Range,  true,  AV_PIX_FMT_P410 },
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#అయితే_ముగింపు
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

స్థిర స్థిరరాశి గణన AVPixelFormat supported_formats[] = {
#నిర్వచితమైతే k_CFCore_Foundation_సంస్కరణ_Number10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#అయితే_ముగింపు
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#అయితే_ముగింపు
#ఒకవేళ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#అయితే_ముగింపు
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

స్థిర పూర్ణాంకం vt_చట్రాలు_get_constraints(AVHWDeviceContext *ctx,
                                     స్థిరరాశి శూన్య *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    పూర్ణాంకం i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    పరిమాణం(*constraints->valid_sw_formats));
    ఒకవేళ (!constraints->valid_sw_formats)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, పరిమాణం(*constraints->valid_hw_formats));
    ఒకవేళ (!constraints->valid_hw_formats)
        తిరిగి AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    తిరిగి 0;
}

గణన AVPixelFormat av_map_videotoolbox_format_గమ్యం_pixfmt(uint32_t cv_fmt)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        ఒకవేళ (cv_pix_fmts[i].cv_fmt == cv_fmt)
            తిరిగి cv_pix_fmts[i].pix_fmt;
    }
    తిరిగి AV_PIX_FMT_NONE;
}

స్థిర uint32_t vt_format_from_pixfmt(గణన AVPixelFormat pix_fmt,
                                      గణన AVColorRange range)
{
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        ఒకవేళ (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            పూర్ణాంకం నిండిన_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            ఒకవేళ (range == AVCOL_RANGE_UNSPECIFIED)
                తిరిగి cv_pix_fmts[i].cv_fmt;

            ఒకవేళ (cv_pix_fmts[i].నిండిన_range == నిండిన_range)
                తిరిగి cv_pix_fmts[i].cv_fmt;
        }
    }

    తిరిగి 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(గణన AVPixelFormat pix_fmt)
{
    తిరిగి av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(గణన AVPixelFormat pix_fmt, bool నిండిన_range)
{
    తిరిగి vt_format_from_pixfmt(pix_fmt, నిండిన_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

స్థిర పూర్ణాంకం vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef లక్షణాలు, iosurface_properties;

    లక్షణాలు = CFDictionaryCreateMutable(
        ఖాళీ,
        2,
        &k_CFType_Dictionary_కీలకం_Call_Backs,
        &k_CFType_Dictionary_విలువ_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(ఖాళీ, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_సమితి_విలువ(
        లక్షణాలు,
        k_CVPixel_బఫరు_Pixel_Format_Type_కీలకం,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        ఖాళీ,
        0,
        &k_CFType_Dictionary_కీలకం_Call_Backs,
        &k_CFType_Dictionary_విలువ_Call_Backs);
    CFDictionary_సమితి_విలువ(లక్షణాలు, k_CVPixel_బఫరు_IOSurface_Properties_కీలకం, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(ఖాళీ, kCFNumberSInt32Type, &ctx->వెడల్పు);
    h = CFNumberCreate(ఖాళీ, kCFNumberSInt32Type, &ctx->ఎత్తు);
    CFDictionary_సమితి_విలువ(లక్షణాలు, k_CVPixel_బఫరు_వెడల్పు_కీలకం, w);
    CFDictionary_సమితి_విలువ(లక్షణాలు, k_CVPixel_బఫరు_ఎత్తు_కీలకం, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixel_బఫరు_Pool_Create(
        ఖాళీ,
        ఖాళీ,
        లక్షణాలు,
        &fctx->pool);
    CFRelease(లక్షణాలు);

    ఒకవేళ (err == kCVReturnSuccess)
        తిరిగి 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    తిరిగి AVERROR_EXTERNAL;
}

స్థిర శూన్య videotoolbox_బఫరు_release(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    CVPixel_బఫరు_Release((CVPixel_బఫరు_Ref)దత్తాంశం);
}

స్థిర AVBufferRef *vt_pool_alloc_బఫరు(శూన్య *opaque, size_t కొలత)
{
    CVPixel_బఫరు_Ref pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixel_బఫరు_Pool_Create_Pixel_బఫరు(
        ఖాళీ,
        fctx->pool,
        &pixbuf
    );
    ఒకవేళ (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        తిరిగి ఖాళీ;
    }

    buf = av_బఫరు_create((uint8_t *)pixbuf, కొలత,
                           videotoolbox_బఫరు_release, ఖాళీ, 0);
    ఒకవేళ (!buf) {
        CVPixel_బఫరు_Release(pixbuf);
        తిరిగి ఖాళీ;
    }
    తిరిగి buf;
}

స్థిర శూన్య vt_చట్రాలు_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    ఒకవేళ (fctx->pool) {
        CVPixel_బఫరు_Pool_Release(fctx->pool);
        fctx->pool = ఖాళీ;
    }
}

స్థిర పూర్ణాంకం vt_చట్రాలు_init(AVHWFramesContext *ctx)
{
    పూర్ణాంకం i, ret;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ఒకవేళ (ctx->sw_format == supported_formats[i])
            ఆపు;
    }
    ఒకవేళ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        తిరిగి AVERROR(ENOSYS);
    }

    ఒకవేళ (!ctx->pool) {
        ffhwframesctx(ctx)->pool_అంతర్గత = av_బఫరు_pool_init2(
                పరిమాణం(CVPixel_బఫరు_Ref), ctx, vt_pool_alloc_బఫరు, ఖాళీ);
        ఒకవేళ (!ffhwframesctx(ctx)->pool_అంతర్గత)
            తిరిగి AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vt_get_బఫరు(AVHWFramesContext *ctx, AVFrame *చట్రం)
{
    చట్రం->buf[0] = av_బఫరు_pool_get(ctx->pool);
    ఒకవేళ (!చట్రం->buf[0])
        తిరిగి AVERROR(ENOMEM);

    చట్రం->దత్తాంశం[3] = చట్రం->buf[0]->దత్తాంశం;
    చట్రం->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    చట్రం->వెడల్పు   = ctx->వెడల్పు;
    చట్రం->ఎత్తు  = ctx->ఎత్తు;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   గణన AVHWFrameTransferDirection dir,
                                   గణన AVPixelFormat **formats)
{
    గణన AVPixelFormat *fmts = av_malloc_array(2, పరిమాణం(*fmts));
    ఒకవేళ (!fmts)
        తిరిగి AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    తిరిగి 0;
}

స్థిర శూన్య vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixel_బఫరు_Ref pixbuf = (CVPixel_బఫరు_Ref)hwmap->ఆధారం->దత్తాంశం[3];

    CVPixel_బఫరు_Unlock_పునాది_చిరునామా(pixbuf, (uintptr_t)hwmap->priv);
}

స్థిర పూర్ణాంకం vt_pixbuf_సమితి_par(శూన్య *log_ctx,
                             CVPixel_బఫరు_Ref pixbuf, స్థిరరాశి AVFrame *src)
{
    CFMutableDictionaryRef par = ఖాళీ;
    CFNumberRef అంకె = ఖాళీ, den = ఖాళీ;
    AVRational avpar = src->sample_aspect_నిష్పత్తి;

    ఒకవేళ (avpar.అంకె == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_బఫరు_Pixel_Aspect_నిష్పత్తి_కీలకం);
        తిరిగి 0;
    }

    av_reduce(&avpar.అంకె, &avpar.den,
                avpar.అంకె, avpar.den,
                0xFFFFFFFF);

    అంకె = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.అంకె);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_కీలకం_Call_Backs,
                                    &k_CFType_Dictionary_విలువ_Call_Backs);

    ఒకవేళ (!par || !అంకె || !den) {
        ఒకవేళ (par) CFRelease(par);
        ఒకవేళ (అంకె) CFRelease(అంకె);
        ఒకవేళ (den) CFRelease(den);
        తిరిగి AVERROR(ENOMEM);
    }

    CFDictionary_సమితి_విలువ(
        par,
        k_CVImage_బఫరు_Pixel_Aspect_నిష్పత్తి_Horizontal_Spacing_కీలకం,
        అంకె);
    CFDictionary_సమితి_విలువ(
        par,
        k_CVImage_బఫరు_Pixel_Aspect_నిష్పత్తి_Vertical_Spacing_కీలకం,
        den);

    CVBuffer_సమితి_Attachment(
        pixbuf,
        k_CVImage_బఫరు_Pixel_Aspect_నిష్పత్తి_కీలకం,
        par,
        k_CVAttachment_బహుళకం_Should_Propagate
    );

    CFRelease(par);
    CFRelease(అంకె);
    CFRelease(den);

    తిరిగి 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(గణన AVChromaLocation loc)
{
    ఎంపిక (loc) {
    స్థితి AVCHROMA_LOC_ఎడమ:
        తిరిగి k_CVImage_బఫరు_Chroma_Location_ఎడమ;
    స్థితి AVCHROMA_LOC_CENTER:
        తిరిగి k_CVImage_బఫరు_Chroma_Location_Center;
    స్థితి AVCHROMA_LOC_శిఖరం:
        తిరిగి k_CVImage_బఫరు_Chroma_Location_శిఖరం;
    స్థితి AVCHROMA_LOC_BOTTOM:
        తిరిగి k_CVImage_బఫరు_Chroma_Location_Bottom;
    స్థితి AVCHROMA_LOC_TOPLEFT:
        తిరిగి k_CVImage_బఫరు_Chroma_Location_శిఖరం_ఎడమ;
    స్థితి AVCHROMA_LOC_BOTTOMLEFT:
        తిరిగి k_CVImage_బఫరు_Chroma_Location_Bottom_ఎడమ;
    అప్రమేయ:
        తిరిగి ఖాళీ;
    }
}

స్థిర పూర్ణాంకం vt_pixbuf_సమితి_chromaloc(శూన్య *log_ctx,
                                   CVPixel_బఫరు_Ref pixbuf, స్థిరరాశి AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    ఒకవేళ (loc) {
        CVBuffer_సమితి_Attachment(
            pixbuf,
            k_CVImage_బఫరు_Chroma_Location_శిఖరం_క్షేత్రం_కీలకం,
            loc,
            k_CVAttachment_బహుళకం_Should_Propagate);
    } లేకపోతే
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_బఫరు_Chroma_Location_శిఖరం_క్షేత్రం_కీలకం);

    తిరిగి 0;
}

CFStringRef av_map_videotoolbox_color_మాతృక_from_av(గణన AVColorSpace space)
{
    ఎంపిక (space) {
    స్థితి AVCOL_SPC_BT2020_CL:
    స్థితి AVCOL_SPC_BT2020_NCL:
#ఒకవేళ HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        ఒకవేళ (__builtin_available(macOS 10.11, iOS 9, *))
            తిరిగి k_CVImage_బఫరు_YCb_Cr_మాతృక_ITU_R_2020;
#అయితే_ముగింపు
        తిరిగి CFSTR("ITU_R_2020");
    స్థితి AVCOL_SPC_BT470BG:
    స్థితి AVCOL_SPC_SMPTE170M:
        తిరిగి k_CVImage_బఫరు_YCb_Cr_మాతృక_ITU_R_601_4;
    స్థితి AVCOL_SPC_BT709:
        తిరిగి k_CVImage_బఫరు_YCb_Cr_మాతృక_ITU_R_709_2;
    స్థితి AVCOL_SPC_SMPTE240M:
        తిరిగి k_CVImage_బఫరు_YCb_Cr_మాతృక_SMPTE_240_M_1995;
    అప్రమేయ:
#ఒకవేళ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ఒకవేళ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            తిరిగి CVYCb_Cr_మాతృక_Get_String_For_Integer_సంకేతం_బిందువు(space);
        av_fallthrough;
#అయితే_ముగింపు
    స్థితి AVCOL_SPC_UNSPECIFIED:
        తిరిగి ఖాళీ;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(గణన AVColorPrimaries pri)
{
    ఎంపిక (pri) {
    స్థితి AVCOL_PRI_BT2020:
#ఒకవేళ HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        ఒకవేళ (__builtin_available(macOS 10.11, iOS 9, *))
            తిరిగి k_CVImage_బఫరు_Color_Primaries_ITU_R_2020;
#అయితే_ముగింపు
        తిరిగి CFSTR("ITU_R_2020");
    స్థితి AVCOL_PRI_BT709:
        తిరిగి k_CVImage_బఫరు_Color_Primaries_ITU_R_709_2;
    స్థితి AVCOL_PRI_SMPTE170M:
        తిరిగి k_CVImage_బఫరు_Color_Primaries_SMPTE_C;
    స్థితి AVCOL_PRI_BT470BG:
        తిరిగి k_CVImage_బఫరు_Color_Primaries_EBU_3213;
    అప్రమేయ:
#ఒకవేళ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ఒకవేళ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            తిరిగి CVColor_Primaries_Get_String_For_Integer_సంకేతం_బిందువు(pri);
        av_fallthrough;
#అయితే_ముగింపు
    స్థితి AVCOL_PRI_UNSPECIFIED:
        తిరిగి ఖాళీ;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(గణన AVColorTransferCharacteristic trc)
{

    ఎంపిక (trc) {
    స్థితి AVCOL_TRC_SMPTE2084:
#ఒకవేళ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        ఒకవేళ (__builtin_available(macOS 10.13, iOS 11, *))
            తిరిగి k_CVImage_బఫరు_Transfer_Function_SMPTE_ST_2084_PQ;
#అయితే_ముగింపు
        తిరిగి CFSTR("SMPTE_ST_2084_PQ");
    స్థితి AVCOL_TRC_BT2020_10:
    స్థితి AVCOL_TRC_BT2020_12:
#ఒకవేళ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        ఒకవేళ (__builtin_available(macOS 10.11, iOS 9, *))
            తిరిగి k_CVImage_బఫరు_Transfer_Function_ITU_R_2020;
#అయితే_ముగింపు
        తిరిగి CFSTR("ITU_R_2020");
    స్థితి AVCOL_TRC_BT709:
        తిరిగి k_CVImage_బఫరు_Transfer_Function_ITU_R_709_2;
    స్థితి AVCOL_TRC_SMPTE240M:
        తిరిగి k_CVImage_బఫరు_Transfer_Function_SMPTE_240_M_1995;
    స్థితి AVCOL_TRC_SMPTE428:
#ఒకవేళ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        ఒకవేళ (__builtin_available(macOS 10.12, iOS 10, *))
            తిరిగి k_CVImage_బఫరు_Transfer_Function_SMPTE_ST_428_1;
#అయితే_ముగింపు
        తిరిగి CFSTR("SMPTE_ST_428_1");
    స్థితి AVCOL_TRC_ARIB_STD_B67:
#ఒకవేళ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ఒకవేళ (__builtin_available(macOS 10.13, iOS 11, *))
            తిరిగి k_CVImage_బఫరు_Transfer_Function_ITU_R_2100_HLG;
#అయితే_ముగింపు
        తిరిగి CFSTR("ITU_R_2100_HLG");
    స్థితి AVCOL_TRC_GAMMA22:
        తిరిగి k_CVImage_బఫరు_Transfer_Function_Use_Gamma;
    స్థితి AVCOL_TRC_GAMMA28:
        తిరిగి k_CVImage_బఫరు_Transfer_Function_Use_Gamma;
    అప్రమేయ:
#ఒకవేళ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ఒకవేళ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            తిరిగి CVTransfer_Function_Get_String_For_Integer_సంకేతం_బిందువు(trc);
        av_fallthrough;
#అయితే_ముగింపు
    స్థితి AVCOL_TRC_UNSPECIFIED:
        తిరిగి ఖాళీ;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
స్థిర CFDictionaryRef vt_cv_బఫరు_copy_attachments(CVBufferRef బఫరు,
                                                     CVAttachment_బహుళకం attachment_బహుళకం)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #ఒకవేళ (లక్ష్యం_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (లక్ష్యం_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (లక్ష్యం_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        ఒకవేళ (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            తిరిగి CVBufferCopyAttachments(బఫరు, attachment_బహుళకం);
    #అయితే_ముగింపు

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #ఒకవేళ (లక్ష్యం_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (లక్ష్యం_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (లక్ష్యం_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(బఫరు, attachment_బహుళకం);
        తిరిగి (dict) ? CFDictionaryCreateCopy(ఖాళీ, dict) : ఖాళీ;
    #లేకపోతే
        తిరిగి ఖాళీ; // Impossible, just make the compiler happy
    #అయితే_ముగింపు
}

స్థిర పూర్ణాంకం vt_pixbuf_సమితి_colorspace(శూన్య *log_ctx,
                                    CVPixel_బఫరు_Ref pixbuf, స్థిరరాశి AVFrame *src)
{
    CGColorSpaceRef colorspace = ఖాళీ;
    CFStringRef colormatrix = ఖాళీ, colorpri = ఖాళీ, colortrc = ఖాళీ;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_మాతృక_from_av(src->colorspace);
    ఒకవేళ (colormatrix)
        CVBuffer_సమితి_Attachment(pixbuf, k_CVImage_బఫరు_YCb_Cr_మాతృక_కీలకం,
            colormatrix, k_CVAttachment_బహుళకం_Should_Propagate);
    లేకపోతే {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_బఫరు_YCb_Cr_మాతృక_కీలకం);
        ఒకవేళ (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    ఒకవేళ (colorpri)
        CVBuffer_సమితి_Attachment(pixbuf, k_CVImage_బఫరు_Color_Primaries_కీలకం,
            colorpri, k_CVAttachment_బహుళకం_Should_Propagate);
    లేకపోతే {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_బఫరు_Color_Primaries_కీలకం);
        ఒకవేళ (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    ఒకవేళ (colortrc)
        CVBuffer_సమితి_Attachment(pixbuf, k_CVImage_బఫరు_Transfer_Function_కీలకం,
            colortrc, k_CVAttachment_బహుళకం_Should_Propagate);
    లేకపోతే {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_బఫరు_Transfer_Function_కీలకం);
        ఒకవేళ (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    ఒకవేళ (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    లేకపోతే ఒకవేళ (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    ఒకవేళ (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(ఖాళీ, kCFNumberFloat32Type, &gamma);
        CVBuffer_సమితి_Attachment(pixbuf, k_CVImage_బఫరు_Gamma_Level_కీలకం,
            gamma_level, k_CVAttachment_బహుళకం_Should_Propagate);
        CFRelease(gamma_level);
    } లేకపోతే
        CVBufferRemoveAttachment(pixbuf, k_CVImage_బఫరు_Gamma_Level_కీలకం);

#ఒకవేళ (లక్ష్యం_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (లక్ష్యం_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    ఒకవేళ (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_బఫరు_copy_attachments(pixbuf, k_CVAttachment_బహుళకం_Should_Propagate);

        ఒకవేళ (attachments) {
            colorspace =
                CVImage_బఫరు_Create_Color_Space_From_Attachments(attachments);
            CFRelease(attachments);
        }
    }
#అయితే_ముగింపు

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    ఒకవేళ (colorspace) {
        CVBuffer_సమితి_Attachment(pixbuf, k_CVImage_బఫరు_CGColor_Space_కీలకం,
            colorspace, k_CVAttachment_బహుళకం_Should_Propagate);
        CFRelease(colorspace);
    } లేకపోతే
        CVBufferRemoveAttachment(pixbuf, k_CVImage_బఫరు_CGColor_Space_కీలకం);

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vt_pixbuf_సమితి_attachments(శూన్య *log_ctx,
                                     CVPixel_బఫరు_Ref pixbuf, స్థిరరాశి AVFrame *src)
{
    పూర్ణాంకం ret;
    ret = vt_pixbuf_సమితి_par(log_ctx, pixbuf, src);
    ఒకవేళ (ret < 0)
        తిరిగి ret;
    ret = vt_pixbuf_సమితి_colorspace(log_ctx, pixbuf, src);
    ఒకవేళ (ret < 0)
        తిరిగి ret;
    ret = vt_pixbuf_సమితి_chromaloc(log_ctx, pixbuf, src);
    ఒకవేళ (ret < 0)
        తిరిగి ret;
    తిరిగి 0;
}

పూర్ణాంకం av_vt_pixbuf_సమితి_attachments(శూన్య *log_ctx,
                                 CVPixel_బఫరు_Ref pixbuf, స్థిరరాశి AVFrame *src)
{
    తిరిగి vt_pixbuf_సమితి_attachments(log_ctx, pixbuf, src);
}

స్థిర పూర్ణాంకం vt_map_చట్రం(AVHWFramesContext *ctx, AVFrame *dst, స్థిరరాశి AVFrame *src,
                        పూర్ణాంకం flags)
{
    CVPixel_బఫరు_Ref pixbuf = (CVPixel_బఫరు_Ref)src->దత్తాంశం[3];
    OSType pixel_format = CVPixel_బఫరు_Get_Pixel_Format_Type(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    పూర్ణాంకం ret;
    పూర్ణాంకం i;
    గణన AVPixelFormat format;

    format = av_map_videotoolbox_format_గమ్యం_pixfmt(pixel_format);
    ఒకవేళ (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        తిరిగి AVERROR_UNKNOWN;
    }

    ఒకవేళ (CVPixel_బఫరు_Get_వెడల్పు(pixbuf) != ctx->వెడల్పు ||
        CVPixel_బఫరు_Get_ఎత్తు(pixbuf) != ctx->ఎత్తు) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    ఒకవేళ (flags == AV_HWFRAME_MAP_READ)
        map_flags = k_CVPixel_బఫరు_తాళం_Read_Only;

    err = CVPixel_బఫరు_తాళం_పునాది_చిరునామా(pixbuf, map_flags);
    ఒకవేళ (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    ఒకవేళ (CVPixel_బఫరు_Is_Planar(pixbuf)) {
        పూర్ణాంకం planes = CVPixel_బఫరు_Get_Plane_లెక్క(pixbuf);
        కొరకు (i = 0; i < planes; i++) {
            dst->దత్తాంశం[i]     = CVPixel_బఫరు_Get_పునాది_చిరునామా_యొక్క_Plane(pixbuf, i);
            dst->linesize[i] = CVPixel_బఫరు_Get_బైట్లు_చొప్పున_అడ్డువరుస_యొక్క_Plane(pixbuf, i);
        }
    } లేకపోతే {
        dst->దత్తాంశం[0]     = CVPixel_బఫరు_Get_పునాది_చిరునామా(pixbuf);
        dst->linesize[0] = CVPixel_బఫరు_Get_బైట్లు_చొప్పున_అడ్డువరుస(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_చట్రాలు_ctx, dst, src, vt_unmap,
                                (శూన్య *)(uintptr_t)map_flags);
    ఒకవేళ (ret < 0)
        వెళ్ళు unlock;

    తిరిగి 0;

unlock:
    CVPixel_బఫరు_Unlock_పునాది_చిరునామా(pixbuf, map_flags);
    తిరిగి ret;
}

స్థిర పూర్ణాంకం vt_transfer_దత్తాంశం_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    AVFrame *map;
    పూర్ణాంకం err;

    ఒకవేళ (dst->వెడల్పు > hwfc->వెడల్పు || dst->ఎత్తు > hwfc->ఎత్తు)
        తిరిగి AVERROR(EINVAL);

    map = av_చట్రం_alloc();
    ఒకవేళ (!map)
        తిరిగి AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_చట్రం(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ఒకవేళ (err)
        వెళ్ళు fail;

    map->వెడల్పు  = dst->వెడల్పు;
    map->ఎత్తు = dst->ఎత్తు;

    err = av_చట్రం_copy(dst, map);
    ఒకవేళ (err)
        వెళ్ళు fail;

    err = 0;
fail:
    av_చట్రం_free(&map);
    తిరిగి err;
}

స్థిర పూర్ణాంకం vt_transfer_దత్తాంశం_గమ్యం(AVHWFramesContext *hwfc,
                               AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    AVFrame *map;
    పూర్ణాంకం err;

    ఒకవేళ (src->వెడల్పు > hwfc->వెడల్పు || src->ఎత్తు > hwfc->ఎత్తు)
        తిరిగి AVERROR(EINVAL);

    map = av_చట్రం_alloc();
    ఒకవేళ (!map)
        తిరిగి AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_చట్రం(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ఒకవేళ (err)
        వెళ్ళు fail;

    map->వెడల్పు  = src->వెడల్పు;
    map->ఎత్తు = src->ఎత్తు;

    err = av_చట్రం_copy(map, src);
    ఒకవేళ (err)
        వెళ్ళు fail;

    err = vt_pixbuf_సమితి_attachments(hwfc, (CVPixel_బఫరు_Ref)dst->దత్తాంశం[3], src);
    ఒకవేళ (err)
        వెళ్ళు fail;

    err = 0;
fail:
    av_చట్రం_free(&map);
    తిరిగి err;
}

స్థిర పూర్ణాంకం vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    పూర్ణాంకం err;

    ఒకవేళ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    లేకపోతే ఒకవేళ (dst->format != hwfc->sw_format)
        తిరిగి AVERROR(ENOSYS);

    err = vt_map_చట్రం(hwfc, dst, src, flags);
    ఒకవేళ (err)
        తిరిగి err;

    dst->వెడల్పు  = src->వెడల్పు;
    dst->ఎత్తు = src->ఎత్తు;

    err = av_చట్రం_copy_props(dst, src);
    ఒకవేళ (err)
        తిరిగి err;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vt_device_create(AVHWDeviceContext *ctx, స్థిరరాశి అక్షరం *device,
                            AVDictionary *opts, పూర్ణాంకం flags)
{
    ఒకవేళ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    తిరిగి 0;
}

స్థిరరాశి HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .చట్రాలు_hwctx_కొలత    = పరిమాణం(VTFramesContext),

    .device_create        = vt_device_create,
    .చట్రాలు_init          = vt_చట్రాలు_init,
    .చట్రాలు_get_బఫరు    = vt_get_బఫరు,
    .చట్రాలు_get_constraints = vt_చట్రాలు_get_constraints,
    .చట్రాలు_uninit        = vt_చట్రాలు_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_దత్తాంశం_గమ్యం     = vt_transfer_దత్తాంశం_గమ్యం,
    .transfer_దత్తాంశం_from   = vt_transfer_దత్తాంశం_from,
    .map_from             = vt_map_from,

    .pix_fmts = (స్థిరరాశి గణన AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
