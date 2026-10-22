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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ <VideoToolbox/VideoToolbox.h>

#ଅନ୍ତର୍ଭାଵ "buffer.h"
#ଅନ୍ତର୍ଭାଵ "buffer_internal.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_internal.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_videotoolbox.h"
#ଅନ୍ତର୍ଭାଵ "attributes.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "pixfmt.h"
#ଅନ୍ତର୍ଭାଵ "pixdesc.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixelBufferPoolRef pool;
} VTFramesContext;

ସ୍ଥିର ଅଚଳ ସଂରଚନା {
    uint32_t cv_fmt;
    bool full_range;
    ଗଣନା AVPixelFormat pix_fmt;
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
#ଯଦି HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#endif
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

ସ୍ଥିର ଅଚଳ ଗଣନା AVPixelFormat supported_formats[] = {
#ifdef kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#endif
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#ଯଦି HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#ଯଦି HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#endif
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_frames_get_constraints(AVHWDeviceContext *ctx,
                                     ଅଚଳ ଶୂନ୍ୟ *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    ଆକାର(*constraints->valid_sw_formats));
    ଯଦି (!constraints->valid_sw_formats)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ଆକାର(*constraints->valid_hw_formats));
    ଯଦି (!constraints->valid_hw_formats)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ଫେରନ୍ତୁ 0;
}

ଗଣନା AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        ଯଦି (cv_pix_fmts[i].cv_fmt == cv_fmt)
            ଫେରନ୍ତୁ cv_pix_fmts[i].pix_fmt;
    }
    ଫେରନ୍ତୁ AV_PIX_FMT_NONE;
}

ସ୍ଥିର uint32_t vt_format_from_pixfmt(ଗଣନା AVPixelFormat pix_fmt,
                                      ଗଣନା AVColorRange range)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        ଯଦି (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            ଯଦି (range == AVCOL_RANGE_UNSPECIFIED)
                ଫେରନ୍ତୁ cv_pix_fmts[i].cv_fmt;

            ଯଦି (cv_pix_fmts[i].full_range == full_range)
                ଫେରନ୍ତୁ cv_pix_fmts[i].cv_fmt;
        }
    }

    ଫେରନ୍ତୁ 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(ଗଣନା AVPixelFormat pix_fmt)
{
    ଫେରନ୍ତୁ av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(ଗଣନା AVPixelFormat pix_fmt, bool full_range)
{
    ଫେରନ୍ତୁ vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef attributes, iosurface_properties;

    attributes = CFDictionaryCreateMutable(
        ଖାଲି,
        2,
        &k_CFType_Dictionary_ଚାବି_Call_Backs,
        &k_CFType_Dictionary_ମୂଲ୍ୟ_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(ଖାଲି, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_Set_ମୂଲ୍ୟ(
        attributes,
        k_CVPixel_Buffer_Pixel_Format_Type_ଚାବି,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        ଖାଲି,
        0,
        &k_CFType_Dictionary_ଚାବି_Call_Backs,
        &k_CFType_Dictionary_ମୂଲ୍ୟ_Call_Backs);
    CFDictionary_Set_ମୂଲ୍ୟ(attributes, k_CVPixel_Buffer_IOSurface_Properties_ଚାବି, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(ଖାଲି, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(ଖାଲି, kCFNumberSInt32Type, &ctx->height);
    CFDictionary_Set_ମୂଲ୍ୟ(attributes, k_CVPixel_Buffer_Width_ଚାବି, w);
    CFDictionary_Set_ମୂଲ୍ୟ(attributes, k_CVPixel_Buffer_Height_ଚାବି, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixelBufferPoolCreate(
        ଖାଲି,
        ଖାଲି,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    ଯଦି (err == kCVReturnSuccess)
        ଫେରନ୍ତୁ 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    ଫେରନ୍ତୁ AVERROR_EXTERNAL;
}

ସ୍ଥିର ଶୂନ୍ୟ videotoolbox_buffer_release(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    CVPixelBufferRelease((CVPixelBufferRef)data);
}

ସ୍ଥିର AVBufferRef *vt_pool_alloc_buffer(ଶୂନ୍ୟ *opaque, size_t size)
{
    CVPixelBufferRef pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixelBufferPoolCreatePixelBuffer(
        ଖାଲି,
        fctx->pool,
        &pixbuf
    );
    ଯଦି (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    buf = av_buffer_create((uint8_t *)pixbuf, size,
                           videotoolbox_buffer_release, ଖାଲି, 0);
    ଯଦି (!buf) {
        CVPixelBufferRelease(pixbuf);
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ buf;
}

ସ୍ଥିର ଶୂନ୍ୟ vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    ଯଦି (fctx->pool) {
        CVPixelBufferPoolRelease(fctx->pool);
        fctx->pool = ଖାଲି;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_frames_init(AVHWFramesContext *ctx)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ଯଦି (ctx->sw_format == supported_formats[i])
            ଭାଙ୍ଗ;
    }
    ଯଦି (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    ଯଦି (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(
                ଆକାର(CVPixelBufferRef), ctx, vt_pool_alloc_buffer, ଖାଲି);
        ଯଦି (!ffhwframesctx(ctx)->pool_internal)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ଯଦି (!frame->buf[0])
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   ଗଣନା AVHWFrameTransferDirection dir,
                                   ଗଣନା AVPixelFormat **formats)
{
    ଗଣନା AVPixelFormat *fmts = av_malloc_array(2, ଆକାର(*fmts));
    ଯଦି (!fmts)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)hwmap->source->data[3];

    CVPixelBufferUnlockBaseAddress(pixbuf, (uintptr_t)hwmap->priv);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_pixbuf_set_par(ଶୂନ୍ୟ *log_ctx,
                             CVPixelBufferRef pixbuf, ଅଚଳ AVFrame *src)
{
    CFMutableDictionaryRef par = ଖାଲି;
    CFNumberRef ଅଙ୍କ = ଖାଲି, den = ଖାଲି;
    AVRational avpar = src->sample_aspect_ratio;

    ଯଦି (avpar.ଅଙ୍କ == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Pixel_Aspect_Ratio_ଚାବି);
        ଫେରନ୍ତୁ 0;
    }

    av_reduce(&avpar.ଅଙ୍କ, &avpar.den,
                avpar.ଅଙ୍କ, avpar.den,
                0xFFFFFFFF);

    ଅଙ୍କ = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.ଅଙ୍କ);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_ଚାବି_Call_Backs,
                                    &k_CFType_Dictionary_ମୂଲ୍ୟ_Call_Backs);

    ଯଦି (!par || !ଅଙ୍କ || !den) {
        ଯଦି (par) CFRelease(par);
        ଯଦି (ଅଙ୍କ) CFRelease(ଅଙ୍କ);
        ଯଦି (den) CFRelease(den);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    CFDictionary_Set_ମୂଲ୍ୟ(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Horizontal_Spacing_ଚାବି,
        ଅଙ୍କ);
    CFDictionary_Set_ମୂଲ୍ୟ(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Vertical_Spacing_ଚାବି,
        den);

    CVBufferSetAttachment(
        pixbuf,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_ଚାବି,
        par,
        kCVAttachmentMode_ShouldPropagate
    );

    CFRelease(par);
    CFRelease(ଅଙ୍କ);
    CFRelease(den);

    ଫେରନ୍ତୁ 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(ଗଣନା AVChromaLocation loc)
{
    ବାଛ (loc) {
    ସ୍ଥିତି AVCHROMA_LOC_ବାମ:
        ଫେରନ୍ତୁ k_CVImage_Buffer_Chroma_Location_ବାମ;
    ସ୍ଥିତି AVCHROMA_LOC_CENTER:
        ଫେରନ୍ତୁ kCVImageBufferChromaLocation_Center;
    ସ୍ଥିତି AVCHROMA_LOC_ଶୀର୍ଷ:
        ଫେରନ୍ତୁ k_CVImage_Buffer_Chroma_Location_ଶୀର୍ଷ;
    ସ୍ଥିତି AVCHROMA_LOC_BOTTOM:
        ଫେରନ୍ତୁ kCVImageBufferChromaLocation_Bottom;
    ସ୍ଥିତି AVCHROMA_LOC_TOPLEFT:
        ଫେରନ୍ତୁ k_CVImage_Buffer_Chroma_Location_ଶୀର୍ଷ_ବାମ;
    ସ୍ଥିତି AVCHROMA_LOC_BOTTOMLEFT:
        ଫେରନ୍ତୁ k_CVImage_Buffer_Chroma_Location_Bottom_ବାମ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ ଖାଲି;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_pixbuf_set_chromaloc(ଶୂନ୍ୟ *log_ctx,
                                   CVPixelBufferRef pixbuf, ଅଚଳ AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    ଯଦି (loc) {
        CVBufferSetAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_ଶୀର୍ଷ_Field_ଚାବି,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } ଅନ୍ୟଥା
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_ଶୀର୍ଷ_Field_ଚାବି);

    ଫେରନ୍ତୁ 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(ଗଣନା AVColorSpace space)
{
    ବାଛ (space) {
    ସ୍ଥିତି AVCOL_SPC_BT2020_CL:
    ସ୍ଥିତି AVCOL_SPC_BT2020_NCL:
#ଯଦି HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        ଯଦି (__builtin_available(macOS 10.11, iOS 9, *))
            ଫେରନ୍ତୁ kCVImageBufferYCbCrMatrix_ITU_R_2020;
#endif
        ଫେରନ୍ତୁ CFSTR("ITU_R_2020");
    ସ୍ଥିତି AVCOL_SPC_BT470BG:
    ସ୍ଥିତି AVCOL_SPC_SMPTE170M:
        ଫେରନ୍ତୁ kCVImageBufferYCbCrMatrix_ITU_R_601_4;
    ସ୍ଥିତି AVCOL_SPC_BT709:
        ଫେରନ୍ତୁ kCVImageBufferYCbCrMatrix_ITU_R_709_2;
    ସ୍ଥିତି AVCOL_SPC_SMPTE240M:
        ଫେରନ୍ତୁ kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
#ଯଦି HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ଯଦି (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ଫେରନ୍ତୁ CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
    ସ୍ଥିତି AVCOL_SPC_UNSPECIFIED:
        ଫେରନ୍ତୁ ଖାଲି;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(ଗଣନା AVColorPrimaries pri)
{
    ବାଛ (pri) {
    ସ୍ଥିତି AVCOL_PRI_BT2020:
#ଯଦି HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        ଯଦି (__builtin_available(macOS 10.11, iOS 9, *))
            ଫେରନ୍ତୁ kCVImageBufferColorPrimaries_ITU_R_2020;
#endif
        ଫେରନ୍ତୁ CFSTR("ITU_R_2020");
    ସ୍ଥିତି AVCOL_PRI_BT709:
        ଫେରନ୍ତୁ kCVImageBufferColorPrimaries_ITU_R_709_2;
    ସ୍ଥିତି AVCOL_PRI_SMPTE170M:
        ଫେରନ୍ତୁ kCVImageBufferColorPrimaries_SMPTE_C;
    ସ୍ଥିତି AVCOL_PRI_BT470BG:
        ଫେରନ୍ତୁ kCVImageBufferColorPrimaries_EBU_3213;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
#ଯଦି HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ଯଦି (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ଫେରନ୍ତୁ CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
    ସ୍ଥିତି AVCOL_PRI_UNSPECIFIED:
        ଫେରନ୍ତୁ ଖାଲି;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(ଗଣନା AVColorTransferCharacteristic trc)
{

    ବାଛ (trc) {
    ସ୍ଥିତି AVCOL_TRC_SMPTE2084:
#ଯଦି HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        ଯଦି (__builtin_available(macOS 10.13, iOS 11, *))
            ଫେରନ୍ତୁ kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
#endif
        ଫେରନ୍ତୁ CFSTR("SMPTE_ST_2084_PQ");
    ସ୍ଥିତି AVCOL_TRC_BT2020_10:
    ସ୍ଥିତି AVCOL_TRC_BT2020_12:
#ଯଦି HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        ଯଦି (__builtin_available(macOS 10.11, iOS 9, *))
            ଫେରନ୍ତୁ kCVImageBufferTransferFunction_ITU_R_2020;
#endif
        ଫେରନ୍ତୁ CFSTR("ITU_R_2020");
    ସ୍ଥିତି AVCOL_TRC_BT709:
        ଫେରନ୍ତୁ kCVImageBufferTransferFunction_ITU_R_709_2;
    ସ୍ଥିତି AVCOL_TRC_SMPTE240M:
        ଫେରନ୍ତୁ kCVImageBufferTransferFunction_SMPTE_240M_1995;
    ସ୍ଥିତି AVCOL_TRC_SMPTE428:
#ଯଦି HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        ଯଦି (__builtin_available(macOS 10.12, iOS 10, *))
            ଫେରନ୍ତୁ kCVImageBufferTransferFunction_SMPTE_ST_428_1;
#endif
        ଫେରନ୍ତୁ CFSTR("SMPTE_ST_428_1");
    ସ୍ଥିତି AVCOL_TRC_ARIB_STD_B67:
#ଯଦି HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ଯଦି (__builtin_available(macOS 10.13, iOS 11, *))
            ଫେରନ୍ତୁ kCVImageBufferTransferFunction_ITU_R_2100_HLG;
#endif
        ଫେରନ୍ତୁ CFSTR("ITU_R_2100_HLG");
    ସ୍ଥିତି AVCOL_TRC_GAMMA22:
        ଫେରନ୍ତୁ kCVImageBufferTransferFunction_UseGamma;
    ସ୍ଥିତି AVCOL_TRC_GAMMA28:
        ଫେରନ୍ତୁ kCVImageBufferTransferFunction_UseGamma;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
#ଯଦି HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ଯଦି (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ଫେରନ୍ତୁ CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    ସ୍ଥିତି AVCOL_TRC_UNSPECIFIED:
        ଫେରନ୍ତୁ ଖାଲି;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
ସ୍ଥିର CFDictionaryRef vt_cv_buffer_copy_attachments(CVBufferRef buffer,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #ଯଦି (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        ଯଦି (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            ଫେରନ୍ତୁ CVBufferCopyAttachments(buffer, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #ଯଦି (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(buffer, attachment_mode);
        ଫେରନ୍ତୁ (dict) ? CFDictionaryCreateCopy(ଖାଲି, dict) : ଖାଲି;
    #ଅନ୍ୟଥା
        ଫେରନ୍ତୁ ଖାଲି; // Impossible, just make the compiler happy
    #endif
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_pixbuf_set_colorspace(ଶୂନ୍ୟ *log_ctx,
                                    CVPixelBufferRef pixbuf, ଅଚଳ AVFrame *src)
{
    CGColorSpaceRef colorspace = ଖାଲି;
    CFStringRef colormatrix = ଖାଲି, colorpri = ଖାଲି, colortrc = ଖାଲି;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    ଯଦି (colormatrix)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_ଚାବି,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    ଅନ୍ୟଥା {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_ଚାବି);
        ଯଦି (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    ଯଦି (colorpri)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_ଚାବି,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    ଅନ୍ୟଥା {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_ଚାବି);
        ଯଦି (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    ଯଦି (colortrc)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_ଚାବି,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    ଅନ୍ୟଥା {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_ଚାବି);
        ଯଦି (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    ଯଦି (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    ଅନ୍ୟଥା ଯଦି (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    ଯଦି (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(ଖାଲି, kCFNumberFloat32Type, &gamma);
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_ଚାବି,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } ଅନ୍ୟଥା
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_ଚାବି);

#ଯଦି (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    ଯଦି (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_buffer_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        ଯଦି (attachments) {
            colorspace =
                CVImageBufferCreateColorSpaceFromAttachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    ଯଦି (colorspace) {
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_ଚାବି,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } ଅନ୍ୟଥା
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_ଚାବି);

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_pixbuf_set_attachments(ଶୂନ୍ୟ *log_ctx,
                                     CVPixelBufferRef pixbuf, ଅଚଳ AVFrame *src)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_vt_pixbuf_set_attachments(ଶୂନ୍ୟ *log_ctx,
                                 CVPixelBufferRef pixbuf, ଅଚଳ AVFrame *src)
{
    ଫେରନ୍ତୁ vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, ଅଚଳ AVFrame *src,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)src->data[3];
    OSType pixel_format = CVPixelBufferGetPixelFormatType(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ଗଣନା AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    ଯଦି (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଯଦି (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଯଦି (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    ଯଦି (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଯଦି (CVPixelBufferIsPlanar(pixbuf)) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes = CVPixel_Buffer_Get_Plane_ଗଣନା(pixbuf);
        ପାଇଁ (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } ଅନ୍ୟଥା {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (ଶୂନ୍ୟ *)(uintptr_t)map_flags);
    ଯଦି (ret < 0)
        ଯାଅ unlock;

    ଫେରନ୍ତୁ 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, ଅଚଳ AVFrame *src)
{
    AVFrame *map;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    ଯଦି (dst->width > hwfc->width || dst->height > hwfc->height)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    map = av_frame_alloc();
    ଯଦି (!map)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ଯଦି (err)
        ଯାଅ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    ଯଦି (err)
        ଯାଅ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_transfer_data_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, ଅଚଳ AVFrame *src)
{
    AVFrame *map;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    ଯଦି (src->width > hwfc->width || src->height > hwfc->height)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    map = av_frame_alloc();
    ଯଦି (!map)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ଯଦି (err)
        ଯାଅ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    ଯଦି (err)
        ଯାଅ fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixelBufferRef)dst->data[3], src);
    ଯଦି (err)
        ଯାଅ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    ଯଦି (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ଅନ୍ୟଥା ଯଦି (dst->format != hwfc->sw_format)
        ଫେରନ୍ତୁ AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    ଯଦି (err)
        ଫେରନ୍ତୁ err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    ଯଦି (err)
        ଫେରନ୍ତୁ err;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vt_device_create(AVHWDeviceContext *ctx, ଅଚଳ ଅକ୍ଷର *device,
                            AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଯଦି (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଫେରନ୍ତୁ 0;
}

ଅଚଳ HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .frames_hwctx_size    = ଆକାର(VTFramesContext),

    .device_create        = vt_device_create,
    .frames_init          = vt_frames_init,
    .frames_get_buffer    = vt_get_buffer,
    .frames_get_constraints = vt_frames_get_constraints,
    .frames_uninit        = vt_frames_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_data_to     = vt_transfer_data_to,
    .transfer_data_from   = vt_transfer_data_from,
    .map_from             = vt_map_from,

    .pix_fmts = (ଅଚଳ ଗଣନା AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
