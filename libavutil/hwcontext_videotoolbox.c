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

#شامل "config.h"

#شامل <stdint.h>
#شامل <string.h>

#شامل <VideoToolbox/VideoToolbox.h>

#شامل "buffer.h"
#شامل "buffer_internal.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_internal.h"
#شامل "hwcontext_videotoolbox.h"
#شامل "attributes.h"
#شامل "mem.h"
#شامل "pixfmt.h"
#شامل "pixdesc.h"

تعریفنوع ساختار VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixelBufferPoolRef pool;
} VTFramesContext;

ایستا ثابت ساختار {
    uint32_t cv_fmt;
    bool full_range;
    شمارش AVPixelFormat pix_fmt;
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
#اگر HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#endif
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

ایستا ثابت شمارش AVPixelFormat supported_formats[] = {
#ifdef kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#endif
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#اگر HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#اگر HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#endif
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

ایستا صحیح vt_frames_get_constraints(AVHWDeviceContext *ctx,
                                     ثابت تهی *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    صحیح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    اندازه(*constraints->valid_sw_formats));
    اگر (!constraints->valid_sw_formats)
        بازگشت AVERROR(ENOMEM);

    برای (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, اندازه(*constraints->valid_hw_formats));
    اگر (!constraints->valid_hw_formats)
        بازگشت AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    بازگشت 0;
}

شمارش AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    صحیح i;
    برای (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        اگر (cv_pix_fmts[i].cv_fmt == cv_fmt)
            بازگشت cv_pix_fmts[i].pix_fmt;
    }
    بازگشت AV_PIX_FMT_NONE;
}

ایستا uint32_t vt_format_from_pixfmt(شمارش AVPixelFormat pix_fmt,
                                      شمارش AVColorRange range)
{
    برای (صحیح i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        اگر (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            صحیح full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            اگر (range == AVCOL_RANGE_UNSPECIFIED)
                بازگشت cv_pix_fmts[i].cv_fmt;

            اگر (cv_pix_fmts[i].full_range == full_range)
                بازگشت cv_pix_fmts[i].cv_fmt;
        }
    }

    بازگشت 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(شمارش AVPixelFormat pix_fmt)
{
    بازگشت av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(شمارش AVPixelFormat pix_fmt, bool full_range)
{
    بازگشت vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

ایستا صحیح vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef attributes, iosurface_properties;

    attributes = CFDictionaryCreateMutable(
        پوچ,
        2,
        &k_CFType_Dictionary_کلید_Call_Backs,
        &k_CFType_Dictionary_مقدار_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(پوچ, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_Set_مقدار(
        attributes,
        k_CVPixel_Buffer_Pixel_Format_Type_کلید,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        پوچ,
        0,
        &k_CFType_Dictionary_کلید_Call_Backs,
        &k_CFType_Dictionary_مقدار_Call_Backs);
    CFDictionary_Set_مقدار(attributes, k_CVPixel_Buffer_IOSurface_Properties_کلید, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(پوچ, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(پوچ, kCFNumberSInt32Type, &ctx->height);
    CFDictionary_Set_مقدار(attributes, k_CVPixel_Buffer_Width_کلید, w);
    CFDictionary_Set_مقدار(attributes, k_CVPixel_Buffer_Height_کلید, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixelBufferPoolCreate(
        پوچ,
        پوچ,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    اگر (err == kCVReturnSuccess)
        بازگشت 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    بازگشت AVERROR_EXTERNAL;
}

ایستا تهی videotoolbox_buffer_release(تهی *opaque, uint8_t *data)
{
    CVPixelBufferRelease((CVPixelBufferRef)data);
}

ایستا AVBufferRef *vt_pool_alloc_buffer(تهی *opaque, size_t size)
{
    CVPixelBufferRef pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixelBufferPoolCreatePixelBuffer(
        پوچ,
        fctx->pool,
        &pixbuf
    );
    اگر (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        بازگشت پوچ;
    }

    buf = av_buffer_create((uint8_t *)pixbuf, size,
                           videotoolbox_buffer_release, پوچ, 0);
    اگر (!buf) {
        CVPixelBufferRelease(pixbuf);
        بازگشت پوچ;
    }
    بازگشت buf;
}

ایستا تهی vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    اگر (fctx->pool) {
        CVPixelBufferPoolRelease(fctx->pool);
        fctx->pool = پوچ;
    }
}

ایستا صحیح vt_frames_init(AVHWFramesContext *ctx)
{
    صحیح i, ret;

    برای (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        اگر (ctx->sw_format == supported_formats[i])
            بشکن;
    }
    اگر (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        بازگشت AVERROR(ENOSYS);
    }

    اگر (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(
                اندازه(CVPixelBufferRef), ctx, vt_pool_alloc_buffer, پوچ);
        اگر (!ffhwframesctx(ctx)->pool_internal)
            بازگشت AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    اگر (ret < 0)
        بازگشت ret;

    بازگشت 0;
}

ایستا صحیح vt_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    اگر (!frame->buf[0])
        بازگشت AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    بازگشت 0;
}

ایستا صحیح vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   شمارش AVHWFrameTransferDirection dir,
                                   شمارش AVPixelFormat **formats)
{
    شمارش AVPixelFormat *fmts = av_malloc_array(2, اندازه(*fmts));
    اگر (!fmts)
        بازگشت AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    بازگشت 0;
}

ایستا تهی vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)hwmap->source->data[3];

    CVPixelBufferUnlockBaseAddress(pixbuf, (uintptr_t)hwmap->priv);
}

ایستا صحیح vt_pixbuf_set_par(تهی *log_ctx,
                             CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    CFMutableDictionaryRef par = پوچ;
    CFNumberRef رقم = پوچ, den = پوچ;
    AVRational avpar = src->sample_aspect_ratio;

    اگر (avpar.رقم == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Pixel_Aspect_Ratio_کلید);
        بازگشت 0;
    }

    av_reduce(&avpar.رقم, &avpar.den,
                avpar.رقم, avpar.den,
                0xFFFFFFFF);

    رقم = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.رقم);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_کلید_Call_Backs,
                                    &k_CFType_Dictionary_مقدار_Call_Backs);

    اگر (!par || !رقم || !den) {
        اگر (par) CFRelease(par);
        اگر (رقم) CFRelease(رقم);
        اگر (den) CFRelease(den);
        بازگشت AVERROR(ENOMEM);
    }

    CFDictionary_Set_مقدار(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Horizontal_Spacing_کلید,
        رقم);
    CFDictionary_Set_مقدار(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Vertical_Spacing_کلید,
        den);

    CVBufferSetAttachment(
        pixbuf,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_کلید,
        par,
        kCVAttachmentMode_ShouldPropagate
    );

    CFRelease(par);
    CFRelease(رقم);
    CFRelease(den);

    بازگشت 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(شمارش AVChromaLocation loc)
{
    انتخاب (loc) {
    حالت AVCHROMA_LOC_چپ:
        بازگشت k_CVImage_Buffer_Chroma_Location_چپ;
    حالت AVCHROMA_LOC_CENTER:
        بازگشت kCVImageBufferChromaLocation_Center;
    حالت AVCHROMA_LOC_بالاترین:
        بازگشت k_CVImage_Buffer_Chroma_Location_بالاترین;
    حالت AVCHROMA_LOC_BOTTOM:
        بازگشت kCVImageBufferChromaLocation_Bottom;
    حالت AVCHROMA_LOC_TOPLEFT:
        بازگشت k_CVImage_Buffer_Chroma_Location_بالاترین_چپ;
    حالت AVCHROMA_LOC_BOTTOMLEFT:
        بازگشت k_CVImage_Buffer_Chroma_Location_Bottom_چپ;
    پیشفرض:
        بازگشت پوچ;
    }
}

ایستا صحیح vt_pixbuf_set_chromaloc(تهی *log_ctx,
                                   CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    اگر (loc) {
        CVBufferSetAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_بالاترین_Field_کلید,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } وگرنه
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_بالاترین_Field_کلید);

    بازگشت 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(شمارش AVColorSpace space)
{
    انتخاب (space) {
    حالت AVCOL_SPC_BT2020_CL:
    حالت AVCOL_SPC_BT2020_NCL:
#اگر HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        اگر (__builtin_available(macOS 10.11, iOS 9, *))
            بازگشت kCVImageBufferYCbCrMatrix_ITU_R_2020;
#endif
        بازگشت CFSTR("ITU_R_2020");
    حالت AVCOL_SPC_BT470BG:
    حالت AVCOL_SPC_SMPTE170M:
        بازگشت kCVImageBufferYCbCrMatrix_ITU_R_601_4;
    حالت AVCOL_SPC_BT709:
        بازگشت kCVImageBufferYCbCrMatrix_ITU_R_709_2;
    حالت AVCOL_SPC_SMPTE240M:
        بازگشت kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
    پیشفرض:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        اگر (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            بازگشت CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
    حالت AVCOL_SPC_UNSPECIFIED:
        بازگشت پوچ;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(شمارش AVColorPrimaries pri)
{
    انتخاب (pri) {
    حالت AVCOL_PRI_BT2020:
#اگر HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        اگر (__builtin_available(macOS 10.11, iOS 9, *))
            بازگشت kCVImageBufferColorPrimaries_ITU_R_2020;
#endif
        بازگشت CFSTR("ITU_R_2020");
    حالت AVCOL_PRI_BT709:
        بازگشت kCVImageBufferColorPrimaries_ITU_R_709_2;
    حالت AVCOL_PRI_SMPTE170M:
        بازگشت kCVImageBufferColorPrimaries_SMPTE_C;
    حالت AVCOL_PRI_BT470BG:
        بازگشت kCVImageBufferColorPrimaries_EBU_3213;
    پیشفرض:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        اگر (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            بازگشت CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
    حالت AVCOL_PRI_UNSPECIFIED:
        بازگشت پوچ;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(شمارش AVColorTransferCharacteristic trc)
{

    انتخاب (trc) {
    حالت AVCOL_TRC_SMPTE2084:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        اگر (__builtin_available(macOS 10.13, iOS 11, *))
            بازگشت kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
#endif
        بازگشت CFSTR("SMPTE_ST_2084_PQ");
    حالت AVCOL_TRC_BT2020_10:
    حالت AVCOL_TRC_BT2020_12:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        اگر (__builtin_available(macOS 10.11, iOS 9, *))
            بازگشت kCVImageBufferTransferFunction_ITU_R_2020;
#endif
        بازگشت CFSTR("ITU_R_2020");
    حالت AVCOL_TRC_BT709:
        بازگشت kCVImageBufferTransferFunction_ITU_R_709_2;
    حالت AVCOL_TRC_SMPTE240M:
        بازگشت kCVImageBufferTransferFunction_SMPTE_240M_1995;
    حالت AVCOL_TRC_SMPTE428:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        اگر (__builtin_available(macOS 10.12, iOS 10, *))
            بازگشت kCVImageBufferTransferFunction_SMPTE_ST_428_1;
#endif
        بازگشت CFSTR("SMPTE_ST_428_1");
    حالت AVCOL_TRC_ARIB_STD_B67:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        اگر (__builtin_available(macOS 10.13, iOS 11, *))
            بازگشت kCVImageBufferTransferFunction_ITU_R_2100_HLG;
#endif
        بازگشت CFSTR("ITU_R_2100_HLG");
    حالت AVCOL_TRC_GAMMA22:
        بازگشت kCVImageBufferTransferFunction_UseGamma;
    حالت AVCOL_TRC_GAMMA28:
        بازگشت kCVImageBufferTransferFunction_UseGamma;
    پیشفرض:
#اگر HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        اگر (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            بازگشت CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    حالت AVCOL_TRC_UNSPECIFIED:
        بازگشت پوچ;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
ایستا CFDictionaryRef vt_cv_buffer_copy_attachments(CVBufferRef buffer,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #اگر (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        اگر (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            بازگشت CVBufferCopyAttachments(buffer, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #اگر (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(buffer, attachment_mode);
        بازگشت (dict) ? CFDictionaryCreateCopy(پوچ, dict) : پوچ;
    #وگرنه
        بازگشت پوچ; // Impossible, just make the compiler happy
    #endif
}

ایستا صحیح vt_pixbuf_set_colorspace(تهی *log_ctx,
                                    CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    CGColorSpaceRef colorspace = پوچ;
    CFStringRef colormatrix = پوچ, colorpri = پوچ, colortrc = پوچ;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    اگر (colormatrix)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_کلید,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    وگرنه {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_کلید);
        اگر (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    اگر (colorpri)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_کلید,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    وگرنه {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_کلید);
        اگر (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    اگر (colortrc)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_کلید,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    وگرنه {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_کلید);
        اگر (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    اگر (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    وگرنه اگر (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    اگر (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(پوچ, kCFNumberFloat32Type, &gamma);
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_کلید,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } وگرنه
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_کلید);

#اگر (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    اگر (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_buffer_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        اگر (attachments) {
            colorspace =
                CVImageBufferCreateColorSpaceFromAttachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    اگر (colorspace) {
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_کلید,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } وگرنه
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_کلید);

    بازگشت 0;
}

ایستا صحیح vt_pixbuf_set_attachments(تهی *log_ctx,
                                     CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    صحیح ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    اگر (ret < 0)
        بازگشت ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    اگر (ret < 0)
        بازگشت ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    اگر (ret < 0)
        بازگشت ret;
    بازگشت 0;
}

صحیح av_vt_pixbuf_set_attachments(تهی *log_ctx,
                                 CVPixelBufferRef pixbuf, ثابت AVFrame *src)
{
    بازگشت vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

ایستا صحیح vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, ثابت AVFrame *src,
                        صحیح flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)src->data[3];
    OSType pixel_format = CVPixelBufferGetPixelFormatType(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    صحیح ret;
    صحیح i;
    شمارش AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    اگر (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        بازگشت AVERROR_UNKNOWN;
    }

    اگر (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        بازگشت AVERROR_UNKNOWN;
    }

    اگر (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    اگر (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        بازگشت AVERROR_UNKNOWN;
    }

    اگر (CVPixelBufferIsPlanar(pixbuf)) {
        صحیح planes = CVPixel_Buffer_Get_Plane_شمار(pixbuf);
        برای (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } وگرنه {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (تهی *)(uintptr_t)map_flags);
    اگر (ret < 0)
        برو unlock;

    بازگشت 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    بازگشت ret;
}

ایستا صحیح vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح err;

    اگر (dst->width > hwfc->width || dst->height > hwfc->height)
        بازگشت AVERROR(EINVAL);

    map = av_frame_alloc();
    اگر (!map)
        بازگشت AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    اگر (err)
        برو fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    اگر (err)
        برو fail;

    err = 0;
fail:
    av_frame_free(&map);
    بازگشت err;
}

ایستا صحیح vt_transfer_data_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح err;

    اگر (src->width > hwfc->width || src->height > hwfc->height)
        بازگشت AVERROR(EINVAL);

    map = av_frame_alloc();
    اگر (!map)
        بازگشت AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    اگر (err)
        برو fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    اگر (err)
        برو fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixelBufferRef)dst->data[3], src);
    اگر (err)
        برو fail;

    err = 0;
fail:
    av_frame_free(&map);
    بازگشت err;
}

ایستا صحیح vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       ثابت AVFrame *src, صحیح flags)
{
    صحیح err;

    اگر (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    وگرنه اگر (dst->format != hwfc->sw_format)
        بازگشت AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    اگر (err)
        بازگشت err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    اگر (err)
        بازگشت err;

    بازگشت 0;
}

ایستا صحیح vt_device_create(AVHWDeviceContext *ctx, ثابت نویسه *device,
                            AVDictionary *opts, صحیح flags)
{
    اگر (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        بازگشت AVERROR_UNKNOWN;
    }

    بازگشت 0;
}

ثابت HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .frames_hwctx_size    = اندازه(VTFramesContext),

    .device_create        = vt_device_create,
    .frames_init          = vt_frames_init,
    .frames_get_buffer    = vt_get_buffer,
    .frames_get_constraints = vt_frames_get_constraints,
    .frames_uninit        = vt_frames_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_data_to     = vt_transfer_data_to,
    .transfer_data_from   = vt_transfer_data_from,
    .map_from             = vt_map_from,

    .pix_fmts = (ثابت شمارش AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
