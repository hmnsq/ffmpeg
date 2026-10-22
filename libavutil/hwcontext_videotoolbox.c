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

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ <VideoToolbox/VideoToolbox.h>

#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "buffer_internal.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_videotoolbox.h"
#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixelBufferPoolRef pool;
} VTFramesContext;

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
    uint32_t cv_fmt;
    bool full_range;
    ಗಣನಾ AVPixelFormat pix_fmt;
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
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#endif
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

ಸ್ಥಿರ ಧ್ರುವ ಗಣನಾ AVPixelFormat supported_formats[] = {
#ifdef kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#endif
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#ಯದಿ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#endif
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_frames_get_constraints(AVHWDeviceContext *ctx,
                                     ಧ್ರುವ ಶೂನ್ಯ *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    ಪರಿಮಾಣ(*constraints->valid_sw_formats));
    ಯದಿ (!constraints->valid_sw_formats)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ಪರಿಮಾಣ(*constraints->valid_hw_formats));
    ಯದಿ (!constraints->valid_hw_formats)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಗಣನಾ AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        ಯದಿ (cv_pix_fmts[i].cv_fmt == cv_fmt)
            ಪ್ರತ್ಯಾಗಮ cv_pix_fmts[i].pix_fmt;
    }
    ಪ್ರತ್ಯಾಗಮ AV_PIX_FMT_NONE;
}

ಸ್ಥಿರ uint32_t vt_format_from_pixfmt(ಗಣನಾ AVPixelFormat pix_fmt,
                                      ಗಣನಾ AVColorRange range)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        ಯದಿ (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            ಪೂರ್ಣಾಙ್ಕ full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            ಯದಿ (range == AVCOL_RANGE_UNSPECIFIED)
                ಪ್ರತ್ಯಾಗಮ cv_pix_fmts[i].cv_fmt;

            ಯದಿ (cv_pix_fmts[i].full_range == full_range)
                ಪ್ರತ್ಯಾಗಮ cv_pix_fmts[i].cv_fmt;
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(ಗಣನಾ AVPixelFormat pix_fmt)
{
    ಪ್ರತ್ಯಾಗಮ av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(ಗಣನಾ AVPixelFormat pix_fmt, bool full_range)
{
    ಪ್ರತ್ಯಾಗಮ vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef attributes, iosurface_properties;

    attributes = CFDictionaryCreateMutable(
        ರಿಕ್ತ,
        2,
        &k_CFType_Dictionary_ಕೀಲಿ_Call_Backs,
        &k_CFType_Dictionary_ಮೌಲ್ಯ_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(ರಿಕ್ತ, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_Set_ಮೌಲ್ಯ(
        attributes,
        k_CVPixel_Buffer_Pixel_Format_Type_ಕೀಲಿ,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        ರಿಕ್ತ,
        0,
        &k_CFType_Dictionary_ಕೀಲಿ_Call_Backs,
        &k_CFType_Dictionary_ಮೌಲ್ಯ_Call_Backs);
    CFDictionary_Set_ಮೌಲ್ಯ(attributes, k_CVPixel_Buffer_IOSurface_Properties_ಕೀಲಿ, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(ರಿಕ್ತ, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(ರಿಕ್ತ, kCFNumberSInt32Type, &ctx->height);
    CFDictionary_Set_ಮೌಲ್ಯ(attributes, k_CVPixel_Buffer_Width_ಕೀಲಿ, w);
    CFDictionary_Set_ಮೌಲ್ಯ(attributes, k_CVPixel_Buffer_Height_ಕೀಲಿ, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixelBufferPoolCreate(
        ರಿಕ್ತ,
        ರಿಕ್ತ,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    ಯದಿ (err == kCVReturnSuccess)
        ಪ್ರತ್ಯಾಗಮ 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    ಪ್ರತ್ಯಾಗಮ AVERROR_EXTERNAL;
}

ಸ್ಥಿರ ಶೂನ್ಯ videotoolbox_buffer_release(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    CVPixelBufferRelease((CVPixelBufferRef)data);
}

ಸ್ಥಿರ AVBufferRef *vt_pool_alloc_buffer(ಶೂನ್ಯ *opaque, size_t size)
{
    CVPixelBufferRef pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixelBufferPoolCreatePixelBuffer(
        ರಿಕ್ತ,
        fctx->pool,
        &pixbuf
    );
    ಯದಿ (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    buf = av_buffer_create((uint8_t *)pixbuf, size,
                           videotoolbox_buffer_release, ರಿಕ್ತ, 0);
    ಯದಿ (!buf) {
        CVPixelBufferRelease(pixbuf);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ buf;
}

ಸ್ಥಿರ ಶೂನ್ಯ vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    ಯದಿ (fctx->pool) {
        CVPixelBufferPoolRelease(fctx->pool);
        fctx->pool = ರಿಕ್ತ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_frames_init(AVHWFramesContext *ctx)
{
    ಪೂರ್ಣಾಙ್ಕ i, ret;

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ಯದಿ (ctx->sw_format == supported_formats[i])
            ಭಙ್ಗ;
    }
    ಯದಿ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

    ಯದಿ (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(
                ಪರಿಮಾಣ(CVPixelBufferRef), ctx, vt_pool_alloc_buffer, ರಿಕ್ತ);
        ಯದಿ (!ffhwframesctx(ctx)->pool_internal)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ಯದಿ (!frame->buf[0])
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   ಗಣನಾ AVHWFrameTransferDirection dir,
                                   ಗಣನಾ AVPixelFormat **formats)
{
    ಗಣನಾ AVPixelFormat *fmts = av_malloc_array(2, ಪರಿಮಾಣ(*fmts));
    ಯದಿ (!fmts)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)hwmap->source->data[3];

    CVPixelBufferUnlockBaseAddress(pixbuf, (uintptr_t)hwmap->priv);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_pixbuf_set_par(ಶೂನ್ಯ *log_ctx,
                             CVPixelBufferRef pixbuf, ಧ್ರುವ AVFrame *src)
{
    CFMutableDictionaryRef par = ರಿಕ್ತ;
    CFNumberRef ಅಂಕೆ = ರಿಕ್ತ, den = ರಿಕ್ತ;
    AVRational avpar = src->sample_aspect_ratio;

    ಯದಿ (avpar.ಅಂಕೆ == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Pixel_Aspect_Ratio_ಕೀಲಿ);
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    av_reduce(&avpar.ಅಂಕೆ, &avpar.den,
                avpar.ಅಂಕೆ, avpar.den,
                0xFFFFFFFF);

    ಅಂಕೆ = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.ಅಂಕೆ);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_ಕೀಲಿ_Call_Backs,
                                    &k_CFType_Dictionary_ಮೌಲ್ಯ_Call_Backs);

    ಯದಿ (!par || !ಅಂಕೆ || !den) {
        ಯದಿ (par) CFRelease(par);
        ಯದಿ (ಅಂಕೆ) CFRelease(ಅಂಕೆ);
        ಯದಿ (den) CFRelease(den);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    CFDictionary_Set_ಮೌಲ್ಯ(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Horizontal_Spacing_ಕೀಲಿ,
        ಅಂಕೆ);
    CFDictionary_Set_ಮೌಲ್ಯ(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Vertical_Spacing_ಕೀಲಿ,
        den);

    CVBufferSetAttachment(
        pixbuf,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_ಕೀಲಿ,
        par,
        kCVAttachmentMode_ShouldPropagate
    );

    CFRelease(par);
    CFRelease(ಅಂಕೆ);
    CFRelease(den);

    ಪ್ರತ್ಯಾಗಮ 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(ಗಣನಾ AVChromaLocation loc)
{
    ವಿಕಲ್ಪ (loc) {
    ಪಕ್ಷ AVCHROMA_LOC_ಎಡ:
        ಪ್ರತ್ಯಾಗಮ k_CVImage_Buffer_Chroma_Location_ಎಡ;
    ಪಕ್ಷ AVCHROMA_LOC_CENTER:
        ಪ್ರತ್ಯಾಗಮ kCVImageBufferChromaLocation_Center;
    ಪಕ್ಷ AVCHROMA_LOC_ತುದಿ:
        ಪ್ರತ್ಯಾಗಮ k_CVImage_Buffer_Chroma_Location_ತುದಿ;
    ಪಕ್ಷ AVCHROMA_LOC_BOTTOM:
        ಪ್ರತ್ಯಾಗಮ kCVImageBufferChromaLocation_Bottom;
    ಪಕ್ಷ AVCHROMA_LOC_TOPLEFT:
        ಪ್ರತ್ಯಾಗಮ k_CVImage_Buffer_Chroma_Location_ತುದಿ_ಎಡ;
    ಪಕ್ಷ AVCHROMA_LOC_BOTTOMLEFT:
        ಪ್ರತ್ಯಾಗಮ k_CVImage_Buffer_Chroma_Location_Bottom_ಎಡ;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_pixbuf_set_chromaloc(ಶೂನ್ಯ *log_ctx,
                                   CVPixelBufferRef pixbuf, ಧ್ರುವ AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    ಯದಿ (loc) {
        CVBufferSetAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_ತುದಿ_Field_ಕೀಲಿ,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } ಅನ್ಯಥಾ
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_ತುದಿ_Field_ಕೀಲಿ);

    ಪ್ರತ್ಯಾಗಮ 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(ಗಣನಾ AVColorSpace space)
{
    ವಿಕಲ್ಪ (space) {
    ಪಕ್ಷ AVCOL_SPC_BT2020_CL:
    ಪಕ್ಷ AVCOL_SPC_BT2020_NCL:
#ಯದಿ HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        ಯದಿ (__builtin_available(macOS 10.11, iOS 9, *))
            ಪ್ರತ್ಯಾಗಮ kCVImageBufferYCbCrMatrix_ITU_R_2020;
#endif
        ಪ್ರತ್ಯಾಗಮ CFSTR("ITU_R_2020");
    ಪಕ್ಷ AVCOL_SPC_BT470BG:
    ಪಕ್ಷ AVCOL_SPC_SMPTE170M:
        ಪ್ರತ್ಯಾಗಮ kCVImageBufferYCbCrMatrix_ITU_R_601_4;
    ಪಕ್ಷ AVCOL_SPC_BT709:
        ಪ್ರತ್ಯಾಗಮ kCVImageBufferYCbCrMatrix_ITU_R_709_2;
    ಪಕ್ಷ AVCOL_SPC_SMPTE240M:
        ಪ್ರತ್ಯಾಗಮ kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
    ಸ್ವಭಾವ:
#ಯದಿ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ಯದಿ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ಪ್ರತ್ಯಾಗಮ CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
    ಪಕ್ಷ AVCOL_SPC_UNSPECIFIED:
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(ಗಣನಾ AVColorPrimaries pri)
{
    ವಿಕಲ್ಪ (pri) {
    ಪಕ್ಷ AVCOL_PRI_BT2020:
#ಯದಿ HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        ಯದಿ (__builtin_available(macOS 10.11, iOS 9, *))
            ಪ್ರತ್ಯಾಗಮ kCVImageBufferColorPrimaries_ITU_R_2020;
#endif
        ಪ್ರತ್ಯಾಗಮ CFSTR("ITU_R_2020");
    ಪಕ್ಷ AVCOL_PRI_BT709:
        ಪ್ರತ್ಯಾಗಮ kCVImageBufferColorPrimaries_ITU_R_709_2;
    ಪಕ್ಷ AVCOL_PRI_SMPTE170M:
        ಪ್ರತ್ಯಾಗಮ kCVImageBufferColorPrimaries_SMPTE_C;
    ಪಕ್ಷ AVCOL_PRI_BT470BG:
        ಪ್ರತ್ಯಾಗಮ kCVImageBufferColorPrimaries_EBU_3213;
    ಸ್ವಭಾವ:
#ಯದಿ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ಯದಿ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ಪ್ರತ್ಯಾಗಮ CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
    ಪಕ್ಷ AVCOL_PRI_UNSPECIFIED:
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(ಗಣನಾ AVColorTransferCharacteristic trc)
{

    ವಿಕಲ್ಪ (trc) {
    ಪಕ್ಷ AVCOL_TRC_SMPTE2084:
#ಯದಿ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        ಯದಿ (__builtin_available(macOS 10.13, iOS 11, *))
            ಪ್ರತ್ಯಾಗಮ kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
#endif
        ಪ್ರತ್ಯಾಗಮ CFSTR("SMPTE_ST_2084_PQ");
    ಪಕ್ಷ AVCOL_TRC_BT2020_10:
    ಪಕ್ಷ AVCOL_TRC_BT2020_12:
#ಯದಿ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        ಯದಿ (__builtin_available(macOS 10.11, iOS 9, *))
            ಪ್ರತ್ಯಾಗಮ kCVImageBufferTransferFunction_ITU_R_2020;
#endif
        ಪ್ರತ್ಯಾಗಮ CFSTR("ITU_R_2020");
    ಪಕ್ಷ AVCOL_TRC_BT709:
        ಪ್ರತ್ಯಾಗಮ kCVImageBufferTransferFunction_ITU_R_709_2;
    ಪಕ್ಷ AVCOL_TRC_SMPTE240M:
        ಪ್ರತ್ಯಾಗಮ kCVImageBufferTransferFunction_SMPTE_240M_1995;
    ಪಕ್ಷ AVCOL_TRC_SMPTE428:
#ಯದಿ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        ಯದಿ (__builtin_available(macOS 10.12, iOS 10, *))
            ಪ್ರತ್ಯಾಗಮ kCVImageBufferTransferFunction_SMPTE_ST_428_1;
#endif
        ಪ್ರತ್ಯಾಗಮ CFSTR("SMPTE_ST_428_1");
    ಪಕ್ಷ AVCOL_TRC_ARIB_STD_B67:
#ಯದಿ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ಯದಿ (__builtin_available(macOS 10.13, iOS 11, *))
            ಪ್ರತ್ಯಾಗಮ kCVImageBufferTransferFunction_ITU_R_2100_HLG;
#endif
        ಪ್ರತ್ಯಾಗಮ CFSTR("ITU_R_2100_HLG");
    ಪಕ್ಷ AVCOL_TRC_GAMMA22:
        ಪ್ರತ್ಯಾಗಮ kCVImageBufferTransferFunction_UseGamma;
    ಪಕ್ಷ AVCOL_TRC_GAMMA28:
        ಪ್ರತ್ಯಾಗಮ kCVImageBufferTransferFunction_UseGamma;
    ಸ್ವಭಾವ:
#ಯದಿ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        ಯದಿ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ಪ್ರತ್ಯಾಗಮ CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    ಪಕ್ಷ AVCOL_TRC_UNSPECIFIED:
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
ಸ್ಥಿರ CFDictionaryRef vt_cv_buffer_copy_attachments(CVBufferRef buffer,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #ಯದಿ (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        ಯದಿ (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            ಪ್ರತ್ಯಾಗಮ CVBufferCopyAttachments(buffer, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #ಯದಿ (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(buffer, attachment_mode);
        ಪ್ರತ್ಯಾಗಮ (dict) ? CFDictionaryCreateCopy(ರಿಕ್ತ, dict) : ರಿಕ್ತ;
    #ಅನ್ಯಥಾ
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ; // Impossible, just make the compiler happy
    #endif
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_pixbuf_set_colorspace(ಶೂನ್ಯ *log_ctx,
                                    CVPixelBufferRef pixbuf, ಧ್ರುವ AVFrame *src)
{
    CGColorSpaceRef colorspace = ರಿಕ್ತ;
    CFStringRef colormatrix = ರಿಕ್ತ, colorpri = ರಿಕ್ತ, colortrc = ರಿಕ್ತ;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    ಯದಿ (colormatrix)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_ಕೀಲಿ,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    ಅನ್ಯಥಾ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_ಕೀಲಿ);
        ಯದಿ (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    ಯದಿ (colorpri)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_ಕೀಲಿ,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    ಅನ್ಯಥಾ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_ಕೀಲಿ);
        ಯದಿ (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    ಯದಿ (colortrc)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_ಕೀಲಿ,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    ಅನ್ಯಥಾ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_ಕೀಲಿ);
        ಯದಿ (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    ಯದಿ (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    ಅನ್ಯಥಾ ಯದಿ (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    ಯದಿ (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(ರಿಕ್ತ, kCFNumberFloat32Type, &gamma);
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_ಕೀಲಿ,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } ಅನ್ಯಥಾ
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_ಕೀಲಿ);

#ಯದಿ (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    ಯದಿ (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_buffer_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        ಯದಿ (attachments) {
            colorspace =
                CVImageBufferCreateColorSpaceFromAttachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    ಯದಿ (colorspace) {
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_ಕೀಲಿ,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } ಅನ್ಯಥಾ
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_ಕೀಲಿ);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_pixbuf_set_attachments(ಶೂನ್ಯ *log_ctx,
                                     CVPixelBufferRef pixbuf, ಧ್ರುವ AVFrame *src)
{
    ಪೂರ್ಣಾಙ್ಕ ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_vt_pixbuf_set_attachments(ಶೂನ್ಯ *log_ctx,
                                 CVPixelBufferRef pixbuf, ಧ್ರುವ AVFrame *src)
{
    ಪ್ರತ್ಯಾಗಮ vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, ಧ್ರುವ AVFrame *src,
                        ಪೂರ್ಣಾಙ್ಕ flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)src->data[3];
    OSType pixel_format = CVPixelBufferGetPixelFormatType(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    ಪೂರ್ಣಾಙ್ಕ ret;
    ಪೂರ್ಣಾಙ್ಕ i;
    ಗಣನಾ AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    ಯದಿ (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಯದಿ (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಯದಿ (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    ಯದಿ (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಯದಿ (CVPixelBufferIsPlanar(pixbuf)) {
        ಪೂರ್ಣಾಙ್ಕ planes = CVPixel_Buffer_Get_Plane_ಎಣಿಕೆ(pixbuf);
        ಪ್ರತಿ (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } ಅನ್ಯಥಾ {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (ಶೂನ್ಯ *)(uintptr_t)map_flags);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ unlock;

    ಪ್ರತ್ಯಾಗಮ 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಙ್ಕ err;

    ಯದಿ (dst->width > hwfc->width || dst->height > hwfc->height)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    map = av_frame_alloc();
    ಯದಿ (!map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_transfer_data_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    AVFrame *map;
    ಪೂರ್ಣಾಙ್ಕ err;

    ಯದಿ (src->width > hwfc->width || src->height > hwfc->height)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    map = av_frame_alloc();
    ಯದಿ (!map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixelBufferRef)dst->data[3], src);
    ಯದಿ (err)
        ಗಚ್ಛ fail;

    err = 0;
fail:
    av_frame_free(&map);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ err;

    ಯದಿ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    ಅನ್ಯಥಾ ಯದಿ (dst->format != hwfc->sw_format)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    ಯದಿ (err)
        ಪ್ರತ್ಯಾಗಮ err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    ಯದಿ (err)
        ಪ್ರತ್ಯಾಗಮ err;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ vt_device_create(AVHWDeviceContext *ctx, ಧ್ರುವ ವರ್ಣ *device,
                            AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಯದಿ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಧ್ರುವ HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .frames_hwctx_size    = ಪರಿಮಾಣ(VTFramesContext),

    .device_create        = vt_device_create,
    .frames_init          = vt_frames_init,
    .frames_get_buffer    = vt_get_buffer,
    .frames_get_constraints = vt_frames_get_constraints,
    .frames_uninit        = vt_frames_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_data_to     = vt_transfer_data_to,
    .transfer_data_from   = vt_transfer_data_from,
    .map_from             = vt_map_from,

    .pix_fmts = (ಧ್ರುವ ಗಣನಾ AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
