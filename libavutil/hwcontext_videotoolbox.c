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

#அந்தர்பாவ "config.h"

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ <VideoToolbox/VideoToolbox.h>

#அந்தர்பாவ "buffer.h"
#அந்தர்பாவ "buffer_internal.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "hwcontext.h"
#அந்தர்பாவ "hwcontext_internal.h"
#அந்தர்பாவ "hwcontext_videotoolbox.h"
#அந்தர்பாவ "attributes.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "pixfmt.h"
#அந்தர்பாவ "pixdesc.h"

வகைவரை கட்டமைப்பு VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixelBufferPoolRef pool;
} VTFramesContext;

நிலையான மாறிலி கட்டமைப்பு {
    uint32_t cv_fmt;
    bool full_range;
    எண்ணிக்கை AVPixelFormat pix_fmt;
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
#எனில் HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#endif
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

நிலையான மாறிலி எண்ணிக்கை AVPixelFormat supported_formats[] = {
#ifdef kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#endif
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#எனில் HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#எனில் HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#endif
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

நிலையான முழு vt_frames_get_constraints(AVHWDeviceContext *ctx,
                                     மாறிலி வெறுமை *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    முழு i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    அளவு(*constraints->valid_sw_formats));
    எனில் (!constraints->valid_sw_formats)
        திரும்பு AVERROR(ENOMEM);

    க்கு (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, அளவு(*constraints->valid_hw_formats));
    எனில் (!constraints->valid_hw_formats)
        திரும்பு AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    திரும்பு 0;
}

எண்ணிக்கை AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    முழு i;
    க்கு (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        எனில் (cv_pix_fmts[i].cv_fmt == cv_fmt)
            திரும்பு cv_pix_fmts[i].pix_fmt;
    }
    திரும்பு AV_PIX_FMT_NONE;
}

நிலையான uint32_t vt_format_from_pixfmt(எண்ணிக்கை AVPixelFormat pix_fmt,
                                      எண்ணிக்கை AVColorRange range)
{
    க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        எனில் (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            முழு full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            எனில் (range == AVCOL_RANGE_UNSPECIFIED)
                திரும்பு cv_pix_fmts[i].cv_fmt;

            எனில் (cv_pix_fmts[i].full_range == full_range)
                திரும்பு cv_pix_fmts[i].cv_fmt;
        }
    }

    திரும்பு 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(எண்ணிக்கை AVPixelFormat pix_fmt)
{
    திரும்பு av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(எண்ணிக்கை AVPixelFormat pix_fmt, bool full_range)
{
    திரும்பு vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

நிலையான முழு vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef attributes, iosurface_properties;

    attributes = CFDictionaryCreateMutable(
        வெற்று,
        2,
        &k_CFType_Dictionary_சாவி_Call_Backs,
        &k_CFType_Dictionary_மதிப்பு_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(வெற்று, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_Set_மதிப்பு(
        attributes,
        k_CVPixel_Buffer_Pixel_Format_Type_சாவி,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        வெற்று,
        0,
        &k_CFType_Dictionary_சாவி_Call_Backs,
        &k_CFType_Dictionary_மதிப்பு_Call_Backs);
    CFDictionary_Set_மதிப்பு(attributes, k_CVPixel_Buffer_IOSurface_Properties_சாவி, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(வெற்று, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(வெற்று, kCFNumberSInt32Type, &ctx->height);
    CFDictionary_Set_மதிப்பு(attributes, k_CVPixel_Buffer_Width_சாவி, w);
    CFDictionary_Set_மதிப்பு(attributes, k_CVPixel_Buffer_Height_சாவி, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixelBufferPoolCreate(
        வெற்று,
        வெற்று,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    எனில் (err == kCVReturnSuccess)
        திரும்பு 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    திரும்பு AVERROR_EXTERNAL;
}

நிலையான வெறுமை videotoolbox_buffer_release(வெறுமை *opaque, uint8_t *data)
{
    CVPixelBufferRelease((CVPixelBufferRef)data);
}

நிலையான AVBufferRef *vt_pool_alloc_buffer(வெறுமை *opaque, size_t size)
{
    CVPixelBufferRef pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixelBufferPoolCreatePixelBuffer(
        வெற்று,
        fctx->pool,
        &pixbuf
    );
    எனில் (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        திரும்பு வெற்று;
    }

    buf = av_buffer_create((uint8_t *)pixbuf, size,
                           videotoolbox_buffer_release, வெற்று, 0);
    எனில் (!buf) {
        CVPixelBufferRelease(pixbuf);
        திரும்பு வெற்று;
    }
    திரும்பு buf;
}

நிலையான வெறுமை vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    எனில் (fctx->pool) {
        CVPixelBufferPoolRelease(fctx->pool);
        fctx->pool = வெற்று;
    }
}

நிலையான முழு vt_frames_init(AVHWFramesContext *ctx)
{
    முழு i, ret;

    க்கு (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        எனில் (ctx->sw_format == supported_formats[i])
            நிறுத்து;
    }
    எனில் (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        திரும்பு AVERROR(ENOSYS);
    }

    எனில் (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(
                அளவு(CVPixelBufferRef), ctx, vt_pool_alloc_buffer, வெற்று);
        எனில் (!ffhwframesctx(ctx)->pool_internal)
            திரும்பு AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    எனில் (ret < 0)
        திரும்பு ret;

    திரும்பு 0;
}

நிலையான முழு vt_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    எனில் (!frame->buf[0])
        திரும்பு AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    திரும்பு 0;
}

நிலையான முழு vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   எண்ணிக்கை AVHWFrameTransferDirection dir,
                                   எண்ணிக்கை AVPixelFormat **formats)
{
    எண்ணிக்கை AVPixelFormat *fmts = av_malloc_array(2, அளவு(*fmts));
    எனில் (!fmts)
        திரும்பு AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    திரும்பு 0;
}

நிலையான வெறுமை vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)hwmap->source->data[3];

    CVPixelBufferUnlockBaseAddress(pixbuf, (uintptr_t)hwmap->priv);
}

நிலையான முழு vt_pixbuf_set_par(வெறுமை *log_ctx,
                             CVPixelBufferRef pixbuf, மாறிலி AVFrame *src)
{
    CFMutableDictionaryRef par = வெற்று;
    CFNumberRef இலக்கம் = வெற்று, den = வெற்று;
    AVRational avpar = src->sample_aspect_ratio;

    எனில் (avpar.இலக்கம் == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Pixel_Aspect_Ratio_சாவி);
        திரும்பு 0;
    }

    av_reduce(&avpar.இலக்கம், &avpar.den,
                avpar.இலக்கம், avpar.den,
                0xFFFFFFFF);

    இலக்கம் = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.இலக்கம்);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_சாவி_Call_Backs,
                                    &k_CFType_Dictionary_மதிப்பு_Call_Backs);

    எனில் (!par || !இலக்கம் || !den) {
        எனில் (par) CFRelease(par);
        எனில் (இலக்கம்) CFRelease(இலக்கம்);
        எனில் (den) CFRelease(den);
        திரும்பு AVERROR(ENOMEM);
    }

    CFDictionary_Set_மதிப்பு(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Horizontal_Spacing_சாவி,
        இலக்கம்);
    CFDictionary_Set_மதிப்பு(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Vertical_Spacing_சாவி,
        den);

    CVBufferSetAttachment(
        pixbuf,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_சாவி,
        par,
        kCVAttachmentMode_ShouldPropagate
    );

    CFRelease(par);
    CFRelease(இலக்கம்);
    CFRelease(den);

    திரும்பு 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(எண்ணிக்கை AVChromaLocation loc)
{
    தேர்வு (loc) {
    நிலை AVCHROMA_LOC_இடது:
        திரும்பு k_CVImage_Buffer_Chroma_Location_இடது;
    நிலை AVCHROMA_LOC_CENTER:
        திரும்பு kCVImageBufferChromaLocation_Center;
    நிலை AVCHROMA_LOC_உச்சி:
        திரும்பு k_CVImage_Buffer_Chroma_Location_உச்சி;
    நிலை AVCHROMA_LOC_BOTTOM:
        திரும்பு kCVImageBufferChromaLocation_Bottom;
    நிலை AVCHROMA_LOC_TOPLEFT:
        திரும்பு k_CVImage_Buffer_Chroma_Location_உச்சி_இடது;
    நிலை AVCHROMA_LOC_BOTTOMLEFT:
        திரும்பு k_CVImage_Buffer_Chroma_Location_Bottom_இடது;
    இயல்பு:
        திரும்பு வெற்று;
    }
}

நிலையான முழு vt_pixbuf_set_chromaloc(வெறுமை *log_ctx,
                                   CVPixelBufferRef pixbuf, மாறிலி AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    எனில் (loc) {
        CVBufferSetAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_உச்சி_Field_சாவி,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } இல்லையெனில்
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_உச்சி_Field_சாவி);

    திரும்பு 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(எண்ணிக்கை AVColorSpace space)
{
    தேர்வு (space) {
    நிலை AVCOL_SPC_BT2020_CL:
    நிலை AVCOL_SPC_BT2020_NCL:
#எனில் HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        எனில் (__builtin_available(macOS 10.11, iOS 9, *))
            திரும்பு kCVImageBufferYCbCrMatrix_ITU_R_2020;
#endif
        திரும்பு CFSTR("ITU_R_2020");
    நிலை AVCOL_SPC_BT470BG:
    நிலை AVCOL_SPC_SMPTE170M:
        திரும்பு kCVImageBufferYCbCrMatrix_ITU_R_601_4;
    நிலை AVCOL_SPC_BT709:
        திரும்பு kCVImageBufferYCbCrMatrix_ITU_R_709_2;
    நிலை AVCOL_SPC_SMPTE240M:
        திரும்பு kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
    இயல்பு:
#எனில் HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        எனில் (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            திரும்பு CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
    நிலை AVCOL_SPC_UNSPECIFIED:
        திரும்பு வெற்று;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(எண்ணிக்கை AVColorPrimaries pri)
{
    தேர்வு (pri) {
    நிலை AVCOL_PRI_BT2020:
#எனில் HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        எனில் (__builtin_available(macOS 10.11, iOS 9, *))
            திரும்பு kCVImageBufferColorPrimaries_ITU_R_2020;
#endif
        திரும்பு CFSTR("ITU_R_2020");
    நிலை AVCOL_PRI_BT709:
        திரும்பு kCVImageBufferColorPrimaries_ITU_R_709_2;
    நிலை AVCOL_PRI_SMPTE170M:
        திரும்பு kCVImageBufferColorPrimaries_SMPTE_C;
    நிலை AVCOL_PRI_BT470BG:
        திரும்பு kCVImageBufferColorPrimaries_EBU_3213;
    இயல்பு:
#எனில் HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        எனில் (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            திரும்பு CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
    நிலை AVCOL_PRI_UNSPECIFIED:
        திரும்பு வெற்று;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(எண்ணிக்கை AVColorTransferCharacteristic trc)
{

    தேர்வு (trc) {
    நிலை AVCOL_TRC_SMPTE2084:
#எனில் HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        எனில் (__builtin_available(macOS 10.13, iOS 11, *))
            திரும்பு kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
#endif
        திரும்பு CFSTR("SMPTE_ST_2084_PQ");
    நிலை AVCOL_TRC_BT2020_10:
    நிலை AVCOL_TRC_BT2020_12:
#எனில் HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        எனில் (__builtin_available(macOS 10.11, iOS 9, *))
            திரும்பு kCVImageBufferTransferFunction_ITU_R_2020;
#endif
        திரும்பு CFSTR("ITU_R_2020");
    நிலை AVCOL_TRC_BT709:
        திரும்பு kCVImageBufferTransferFunction_ITU_R_709_2;
    நிலை AVCOL_TRC_SMPTE240M:
        திரும்பு kCVImageBufferTransferFunction_SMPTE_240M_1995;
    நிலை AVCOL_TRC_SMPTE428:
#எனில் HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        எனில் (__builtin_available(macOS 10.12, iOS 10, *))
            திரும்பு kCVImageBufferTransferFunction_SMPTE_ST_428_1;
#endif
        திரும்பு CFSTR("SMPTE_ST_428_1");
    நிலை AVCOL_TRC_ARIB_STD_B67:
#எனில் HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        எனில் (__builtin_available(macOS 10.13, iOS 11, *))
            திரும்பு kCVImageBufferTransferFunction_ITU_R_2100_HLG;
#endif
        திரும்பு CFSTR("ITU_R_2100_HLG");
    நிலை AVCOL_TRC_GAMMA22:
        திரும்பு kCVImageBufferTransferFunction_UseGamma;
    நிலை AVCOL_TRC_GAMMA28:
        திரும்பு kCVImageBufferTransferFunction_UseGamma;
    இயல்பு:
#எனில் HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        எனில் (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            திரும்பு CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    நிலை AVCOL_TRC_UNSPECIFIED:
        திரும்பு வெற்று;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
நிலையான CFDictionaryRef vt_cv_buffer_copy_attachments(CVBufferRef buffer,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #எனில் (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        எனில் (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            திரும்பு CVBufferCopyAttachments(buffer, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #எனில் (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(buffer, attachment_mode);
        திரும்பு (dict) ? CFDictionaryCreateCopy(வெற்று, dict) : வெற்று;
    #இல்லையெனில்
        திரும்பு வெற்று; // Impossible, just make the compiler happy
    #endif
}

நிலையான முழு vt_pixbuf_set_colorspace(வெறுமை *log_ctx,
                                    CVPixelBufferRef pixbuf, மாறிலி AVFrame *src)
{
    CGColorSpaceRef colorspace = வெற்று;
    CFStringRef colormatrix = வெற்று, colorpri = வெற்று, colortrc = வெற்று;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    எனில் (colormatrix)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_சாவி,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    இல்லையெனில் {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_சாவி);
        எனில் (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    எனில் (colorpri)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_சாவி,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    இல்லையெனில் {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_சாவி);
        எனில் (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    எனில் (colortrc)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_சாவி,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    இல்லையெனில் {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_சாவி);
        எனில் (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    எனில் (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    இல்லையெனில் எனில் (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    எனில் (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(வெற்று, kCFNumberFloat32Type, &gamma);
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_சாவி,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } இல்லையெனில்
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_சாவி);

#எனில் (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    எனில் (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_buffer_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        எனில் (attachments) {
            colorspace =
                CVImageBufferCreateColorSpaceFromAttachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    எனில் (colorspace) {
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_சாவி,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } இல்லையெனில்
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_சாவி);

    திரும்பு 0;
}

நிலையான முழு vt_pixbuf_set_attachments(வெறுமை *log_ctx,
                                     CVPixelBufferRef pixbuf, மாறிலி AVFrame *src)
{
    முழு ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    எனில் (ret < 0)
        திரும்பு ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    எனில் (ret < 0)
        திரும்பு ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    எனில் (ret < 0)
        திரும்பு ret;
    திரும்பு 0;
}

முழு av_vt_pixbuf_set_attachments(வெறுமை *log_ctx,
                                 CVPixelBufferRef pixbuf, மாறிலி AVFrame *src)
{
    திரும்பு vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

நிலையான முழு vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, மாறிலி AVFrame *src,
                        முழு flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)src->data[3];
    OSType pixel_format = CVPixelBufferGetPixelFormatType(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    முழு ret;
    முழு i;
    எண்ணிக்கை AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    எனில் (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        திரும்பு AVERROR_UNKNOWN;
    }

    எனில் (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    எனில் (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    எனில் (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    எனில் (CVPixelBufferIsPlanar(pixbuf)) {
        முழு planes = CVPixel_Buffer_Get_Plane_மொத்தம்(pixbuf);
        க்கு (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } இல்லையெனில் {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (வெறுமை *)(uintptr_t)map_flags);
    எனில் (ret < 0)
        செல் unlock;

    திரும்பு 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    திரும்பு ret;
}

நிலையான முழு vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, மாறிலி AVFrame *src)
{
    AVFrame *map;
    முழு err;

    எனில் (dst->width > hwfc->width || dst->height > hwfc->height)
        திரும்பு AVERROR(EINVAL);

    map = av_frame_alloc();
    எனில் (!map)
        திரும்பு AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    எனில் (err)
        செல் fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    எனில் (err)
        செல் fail;

    err = 0;
fail:
    av_frame_free(&map);
    திரும்பு err;
}

நிலையான முழு vt_transfer_data_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, மாறிலி AVFrame *src)
{
    AVFrame *map;
    முழு err;

    எனில் (src->width > hwfc->width || src->height > hwfc->height)
        திரும்பு AVERROR(EINVAL);

    map = av_frame_alloc();
    எனில் (!map)
        திரும்பு AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    எனில் (err)
        செல் fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    எனில் (err)
        செல் fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixelBufferRef)dst->data[3], src);
    எனில் (err)
        செல் fail;

    err = 0;
fail:
    av_frame_free(&map);
    திரும்பு err;
}

நிலையான முழு vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       மாறிலி AVFrame *src, முழு flags)
{
    முழு err;

    எனில் (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    இல்லையெனில் எனில் (dst->format != hwfc->sw_format)
        திரும்பு AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    எனில் (err)
        திரும்பு err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    எனில் (err)
        திரும்பு err;

    திரும்பு 0;
}

நிலையான முழு vt_device_create(AVHWDeviceContext *ctx, மாறிலி எழுத்து *device,
                            AVDictionary *opts, முழு flags)
{
    எனில் (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    திரும்பு 0;
}

மாறிலி HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .frames_hwctx_size    = அளவு(VTFramesContext),

    .device_create        = vt_device_create,
    .frames_init          = vt_frames_init,
    .frames_get_buffer    = vt_get_buffer,
    .frames_get_constraints = vt_frames_get_constraints,
    .frames_uninit        = vt_frames_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_data_to     = vt_transfer_data_to,
    .transfer_data_from   = vt_transfer_data_from,
    .map_from             = vt_map_from,

    .pix_fmts = (மாறிலி எண்ணிக்கை AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
