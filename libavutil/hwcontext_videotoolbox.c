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

#অন্তর্ভাব "config.h"

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব <VideoToolbox/VideoToolbox.h>

#অন্তর্ভাব "buffer.h"
#অন্তর্ভাব "buffer_internal.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "hwcontext.h"
#অন্তর্ভাব "hwcontext_internal.h"
#অন্তর্ভাব "hwcontext_videotoolbox.h"
#অন্তর্ভাব "attributes.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "pixfmt.h"
#অন্তর্ভাব "pixdesc.h"

প্রকারলেখ কাঠামো VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixel_বাফার_Pool_Ref pool;
} VTFramesContext;

স্থির ধ্রুবক কাঠামো {
    uint32_t cv_fmt;
    bool full_range;
    গণনা AVPixelFormat pix_fmt;
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
#যদি HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#endif
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

স্থির ধ্রুবক গণনা AVPixelFormat supported_formats[] = {
#ifdef kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#endif
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#যদি HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#যদি HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#endif
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

স্থির পূর্ণসংখ্যা vt_frames_get_constraints(AVHWDeviceContext *ctx,
                                     ধ্রুবক শূন্য *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    পূর্ণসংখ্যা i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    আকার(*constraints->valid_sw_formats));
    যদি (!constraints->valid_sw_formats)
        ফেরত AVERROR(ENOMEM);

    জন্য (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, আকার(*constraints->valid_hw_formats));
    যদি (!constraints->valid_hw_formats)
        ফেরত AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ফেরত 0;
}

গণনা AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    পূর্ণসংখ্যা i;
    জন্য (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        যদি (cv_pix_fmts[i].cv_fmt == cv_fmt)
            ফেরত cv_pix_fmts[i].pix_fmt;
    }
    ফেরত AV_PIX_FMT_NONE;
}

স্থির uint32_t vt_format_from_pixfmt(গণনা AVPixelFormat pix_fmt,
                                      গণনা AVColorRange range)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        যদি (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            পূর্ণসংখ্যা full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            যদি (range == AVCOL_RANGE_UNSPECIFIED)
                ফেরত cv_pix_fmts[i].cv_fmt;

            যদি (cv_pix_fmts[i].full_range == full_range)
                ফেরত cv_pix_fmts[i].cv_fmt;
        }
    }

    ফেরত 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(গণনা AVPixelFormat pix_fmt)
{
    ফেরত av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(গণনা AVPixelFormat pix_fmt, bool full_range)
{
    ফেরত vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

স্থির পূর্ণসংখ্যা vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef attributes, iosurface_properties;

    attributes = CFDictionaryCreateMutable(
        ফাঁকা,
        2,
        &k_CFType_Dictionary_চাবি_Call_Backs,
        &k_CFType_Dictionary_মান_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(ফাঁকা, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_Set_মান(
        attributes,
        k_CVPixel_বাফার_Pixel_Format_Type_চাবি,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        ফাঁকা,
        0,
        &k_CFType_Dictionary_চাবি_Call_Backs,
        &k_CFType_Dictionary_মান_Call_Backs);
    CFDictionary_Set_মান(attributes, k_CVPixel_বাফার_IOSurface_Properties_চাবি, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(ফাঁকা, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(ফাঁকা, kCFNumberSInt32Type, &ctx->height);
    CFDictionary_Set_মান(attributes, k_CVPixel_বাফার_Width_চাবি, w);
    CFDictionary_Set_মান(attributes, k_CVPixel_বাফার_Height_চাবি, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixel_বাফার_Pool_Create(
        ফাঁকা,
        ফাঁকা,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    যদি (err == kCVReturnSuccess)
        ফেরত 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    ফেরত AVERROR_EXTERNAL;
}

স্থির শূন্য videotoolbox_বাফার_release(শূন্য *opaque, uint8_t *তথ্য)
{
    CVPixel_বাফার_Release((CVPixel_বাফার_Ref)তথ্য);
}

স্থির AVBufferRef *vt_pool_alloc_বাফার(শূন্য *opaque, size_t আকার_2)
{
    CVPixel_বাফার_Ref pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixel_বাফার_Pool_Create_Pixel_বাফার(
        ফাঁকা,
        fctx->pool,
        &pixbuf
    );
    যদি (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        ফেরত ফাঁকা;
    }

    buf = av_বাফার_create((uint8_t *)pixbuf, আকার_2,
                           videotoolbox_বাফার_release, ফাঁকা, 0);
    যদি (!buf) {
        CVPixel_বাফার_Release(pixbuf);
        ফেরত ফাঁকা;
    }
    ফেরত buf;
}

স্থির শূন্য vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    যদি (fctx->pool) {
        CVPixel_বাফার_Pool_Release(fctx->pool);
        fctx->pool = ফাঁকা;
    }
}

স্থির পূর্ণসংখ্যা vt_frames_init(AVHWFramesContext *ctx)
{
    পূর্ণসংখ্যা i, ret;

    জন্য (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        যদি (ctx->sw_format == supported_formats[i])
            বিরতি;
    }
    যদি (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ফেরত AVERROR(ENOSYS);
    }

    যদি (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_বাফার_pool_init2(
                আকার(CVPixel_বাফার_Ref), ctx, vt_pool_alloc_বাফার, ফাঁকা);
        যদি (!ffhwframesctx(ctx)->pool_internal)
            ফেরত AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    যদি (ret < 0)
        ফেরত ret;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা vt_get_বাফার(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_বাফার_pool_get(ctx->pool);
    যদি (!frame->buf[0])
        ফেরত AVERROR(ENOMEM);

    frame->তথ্য[3] = frame->buf[0]->তথ্য;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   গণনা AVHWFrameTransferDirection dir,
                                   গণনা AVPixelFormat **formats)
{
    গণনা AVPixelFormat *fmts = av_malloc_array(2, আকার(*fmts));
    যদি (!fmts)
        ফেরত AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    ফেরত 0;
}

স্থির শূন্য vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixel_বাফার_Ref pixbuf = (CVPixel_বাফার_Ref)hwmap->source->তথ্য[3];

    CVPixel_বাফার_Unlock_Base_Address(pixbuf, (uintptr_t)hwmap->priv);
}

স্থির পূর্ণসংখ্যা vt_pixbuf_set_par(শূন্য *log_ctx,
                             CVPixel_বাফার_Ref pixbuf, ধ্রুবক AVFrame *src)
{
    CFMutableDictionaryRef par = ফাঁকা;
    CFNumberRef অঙ্ক = ফাঁকা, den = ফাঁকা;
    AVRational avpar = src->sample_aspect_ratio;

    যদি (avpar.অঙ্ক == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_বাফার_Pixel_Aspect_Ratio_চাবি);
        ফেরত 0;
    }

    av_reduce(&avpar.অঙ্ক, &avpar.den,
                avpar.অঙ্ক, avpar.den,
                0xFFFFFFFF);

    অঙ্ক = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.অঙ্ক);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_চাবি_Call_Backs,
                                    &k_CFType_Dictionary_মান_Call_Backs);

    যদি (!par || !অঙ্ক || !den) {
        যদি (par) CFRelease(par);
        যদি (অঙ্ক) CFRelease(অঙ্ক);
        যদি (den) CFRelease(den);
        ফেরত AVERROR(ENOMEM);
    }

    CFDictionary_Set_মান(
        par,
        k_CVImage_বাফার_Pixel_Aspect_Ratio_Horizontal_Spacing_চাবি,
        অঙ্ক);
    CFDictionary_Set_মান(
        par,
        k_CVImage_বাফার_Pixel_Aspect_Ratio_Vertical_Spacing_চাবি,
        den);

    CVBufferSetAttachment(
        pixbuf,
        k_CVImage_বাফার_Pixel_Aspect_Ratio_চাবি,
        par,
        kCVAttachmentMode_ShouldPropagate
    );

    CFRelease(par);
    CFRelease(অঙ্ক);
    CFRelease(den);

    ফেরত 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(গণনা AVChromaLocation loc)
{
    নির্বাচন (loc) {
    ক্ষেত্র AVCHROMA_LOC_বাম:
        ফেরত k_CVImage_বাফার_Chroma_Location_বাম;
    ক্ষেত্র AVCHROMA_LOC_CENTER:
        ফেরত k_CVImage_বাফার_Chroma_Location_Center;
    ক্ষেত্র AVCHROMA_LOC_শীর্ষ:
        ফেরত k_CVImage_বাফার_Chroma_Location_শীর্ষ;
    ক্ষেত্র AVCHROMA_LOC_BOTTOM:
        ফেরত k_CVImage_বাফার_Chroma_Location_Bottom;
    ক্ষেত্র AVCHROMA_LOC_TOPLEFT:
        ফেরত k_CVImage_বাফার_Chroma_Location_শীর্ষ_বাম;
    ক্ষেত্র AVCHROMA_LOC_BOTTOMLEFT:
        ফেরত k_CVImage_বাফার_Chroma_Location_Bottom_বাম;
    পূর্বনির্ধারিত:
        ফেরত ফাঁকা;
    }
}

স্থির পূর্ণসংখ্যা vt_pixbuf_set_chromaloc(শূন্য *log_ctx,
                                   CVPixel_বাফার_Ref pixbuf, ধ্রুবক AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    যদি (loc) {
        CVBufferSetAttachment(
            pixbuf,
            k_CVImage_বাফার_Chroma_Location_শীর্ষ_Field_চাবি,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } অন্যথা
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_বাফার_Chroma_Location_শীর্ষ_Field_চাবি);

    ফেরত 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(গণনা AVColorSpace space)
{
    নির্বাচন (space) {
    ক্ষেত্র AVCOL_SPC_BT2020_CL:
    ক্ষেত্র AVCOL_SPC_BT2020_NCL:
#যদি HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        যদি (__builtin_available(macOS 10.11, iOS 9, *))
            ফেরত k_CVImage_বাফার_YCb_Cr_Matrix_ITU_R_2020;
#endif
        ফেরত CFSTR("ITU_R_2020");
    ক্ষেত্র AVCOL_SPC_BT470BG:
    ক্ষেত্র AVCOL_SPC_SMPTE170M:
        ফেরত k_CVImage_বাফার_YCb_Cr_Matrix_ITU_R_601_4;
    ক্ষেত্র AVCOL_SPC_BT709:
        ফেরত k_CVImage_বাফার_YCb_Cr_Matrix_ITU_R_709_2;
    ক্ষেত্র AVCOL_SPC_SMPTE240M:
        ফেরত k_CVImage_বাফার_YCb_Cr_Matrix_SMPTE_240_M_1995;
    পূর্বনির্ধারিত:
#যদি HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        যদি (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ফেরত CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
    ক্ষেত্র AVCOL_SPC_UNSPECIFIED:
        ফেরত ফাঁকা;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(গণনা AVColorPrimaries pri)
{
    নির্বাচন (pri) {
    ক্ষেত্র AVCOL_PRI_BT2020:
#যদি HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        যদি (__builtin_available(macOS 10.11, iOS 9, *))
            ফেরত k_CVImage_বাফার_Color_Primaries_ITU_R_2020;
#endif
        ফেরত CFSTR("ITU_R_2020");
    ক্ষেত্র AVCOL_PRI_BT709:
        ফেরত k_CVImage_বাফার_Color_Primaries_ITU_R_709_2;
    ক্ষেত্র AVCOL_PRI_SMPTE170M:
        ফেরত k_CVImage_বাফার_Color_Primaries_SMPTE_C;
    ক্ষেত্র AVCOL_PRI_BT470BG:
        ফেরত k_CVImage_বাফার_Color_Primaries_EBU_3213;
    পূর্বনির্ধারিত:
#যদি HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        যদি (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ফেরত CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
    ক্ষেত্র AVCOL_PRI_UNSPECIFIED:
        ফেরত ফাঁকা;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(গণনা AVColorTransferCharacteristic trc)
{

    নির্বাচন (trc) {
    ক্ষেত্র AVCOL_TRC_SMPTE2084:
#যদি HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        যদি (__builtin_available(macOS 10.13, iOS 11, *))
            ফেরত k_CVImage_বাফার_Transfer_Function_SMPTE_ST_2084_PQ;
#endif
        ফেরত CFSTR("SMPTE_ST_2084_PQ");
    ক্ষেত্র AVCOL_TRC_BT2020_10:
    ক্ষেত্র AVCOL_TRC_BT2020_12:
#যদি HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        যদি (__builtin_available(macOS 10.11, iOS 9, *))
            ফেরত k_CVImage_বাফার_Transfer_Function_ITU_R_2020;
#endif
        ফেরত CFSTR("ITU_R_2020");
    ক্ষেত্র AVCOL_TRC_BT709:
        ফেরত k_CVImage_বাফার_Transfer_Function_ITU_R_709_2;
    ক্ষেত্র AVCOL_TRC_SMPTE240M:
        ফেরত k_CVImage_বাফার_Transfer_Function_SMPTE_240_M_1995;
    ক্ষেত্র AVCOL_TRC_SMPTE428:
#যদি HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        যদি (__builtin_available(macOS 10.12, iOS 10, *))
            ফেরত k_CVImage_বাফার_Transfer_Function_SMPTE_ST_428_1;
#endif
        ফেরত CFSTR("SMPTE_ST_428_1");
    ক্ষেত্র AVCOL_TRC_ARIB_STD_B67:
#যদি HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        যদি (__builtin_available(macOS 10.13, iOS 11, *))
            ফেরত k_CVImage_বাফার_Transfer_Function_ITU_R_2100_HLG;
#endif
        ফেরত CFSTR("ITU_R_2100_HLG");
    ক্ষেত্র AVCOL_TRC_GAMMA22:
        ফেরত k_CVImage_বাফার_Transfer_Function_Use_Gamma;
    ক্ষেত্র AVCOL_TRC_GAMMA28:
        ফেরত k_CVImage_বাফার_Transfer_Function_Use_Gamma;
    পূর্বনির্ধারিত:
#যদি HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        যদি (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            ফেরত CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    ক্ষেত্র AVCOL_TRC_UNSPECIFIED:
        ফেরত ফাঁকা;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
স্থির CFDictionaryRef vt_cv_বাফার_copy_attachments(CVBufferRef বাফার,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #যদি (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        যদি (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            ফেরত CVBufferCopyAttachments(বাফার, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #যদি (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(বাফার, attachment_mode);
        ফেরত (dict) ? CFDictionaryCreateCopy(ফাঁকা, dict) : ফাঁকা;
    #অন্যথা
        ফেরত ফাঁকা; // Impossible, just make the compiler happy
    #endif
}

স্থির পূর্ণসংখ্যা vt_pixbuf_set_colorspace(শূন্য *log_ctx,
                                    CVPixel_বাফার_Ref pixbuf, ধ্রুবক AVFrame *src)
{
    CGColorSpaceRef colorspace = ফাঁকা;
    CFStringRef colormatrix = ফাঁকা, colorpri = ফাঁকা, colortrc = ফাঁকা;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    যদি (colormatrix)
        CVBufferSetAttachment(pixbuf, k_CVImage_বাফার_YCb_Cr_Matrix_চাবি,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    অন্যথা {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_বাফার_YCb_Cr_Matrix_চাবি);
        যদি (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    যদি (colorpri)
        CVBufferSetAttachment(pixbuf, k_CVImage_বাফার_Color_Primaries_চাবি,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    অন্যথা {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_বাফার_Color_Primaries_চাবি);
        যদি (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    যদি (colortrc)
        CVBufferSetAttachment(pixbuf, k_CVImage_বাফার_Transfer_Function_চাবি,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    অন্যথা {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_বাফার_Transfer_Function_চাবি);
        যদি (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    যদি (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    অন্যথা যদি (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    যদি (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(ফাঁকা, kCFNumberFloat32Type, &gamma);
        CVBufferSetAttachment(pixbuf, k_CVImage_বাফার_Gamma_Level_চাবি,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } অন্যথা
        CVBufferRemoveAttachment(pixbuf, k_CVImage_বাফার_Gamma_Level_চাবি);

#যদি (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    যদি (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_বাফার_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        যদি (attachments) {
            colorspace =
                CVImage_বাফার_Create_Color_Space_From_Attachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    যদি (colorspace) {
        CVBufferSetAttachment(pixbuf, k_CVImage_বাফার_CGColor_Space_চাবি,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } অন্যথা
        CVBufferRemoveAttachment(pixbuf, k_CVImage_বাফার_CGColor_Space_চাবি);

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা vt_pixbuf_set_attachments(শূন্য *log_ctx,
                                     CVPixel_বাফার_Ref pixbuf, ধ্রুবক AVFrame *src)
{
    পূর্ণসংখ্যা ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    যদি (ret < 0)
        ফেরত ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    যদি (ret < 0)
        ফেরত ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    যদি (ret < 0)
        ফেরত ret;
    ফেরত 0;
}

পূর্ণসংখ্যা av_vt_pixbuf_set_attachments(শূন্য *log_ctx,
                                 CVPixel_বাফার_Ref pixbuf, ধ্রুবক AVFrame *src)
{
    ফেরত vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

স্থির পূর্ণসংখ্যা vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, ধ্রুবক AVFrame *src,
                        পূর্ণসংখ্যা flags)
{
    CVPixel_বাফার_Ref pixbuf = (CVPixel_বাফার_Ref)src->তথ্য[3];
    OSType pixel_format = CVPixel_বাফার_Get_Pixel_Format_Type(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    পূর্ণসংখ্যা ret;
    পূর্ণসংখ্যা i;
    গণনা AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    যদি (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        ফেরত AVERROR_UNKNOWN;
    }

    যদি (CVPixel_বাফার_Get_Width(pixbuf) != ctx->width ||
        CVPixel_বাফার_Get_Height(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        ফেরত AVERROR_UNKNOWN;
    }

    যদি (flags == AV_HWFRAME_MAP_READ)
        map_flags = k_CVPixel_বাফার_Lock_Read_Only;

    err = CVPixel_বাফার_Lock_Base_Address(pixbuf, map_flags);
    যদি (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        ফেরত AVERROR_UNKNOWN;
    }

    যদি (CVPixel_বাফার_Is_Planar(pixbuf)) {
        পূর্ণসংখ্যা planes = CVPixel_বাফার_Get_Plane_গুনতি(pixbuf);
        জন্য (i = 0; i < planes; i++) {
            dst->তথ্য[i]     = CVPixel_বাফার_Get_Base_Address_Of_Plane(pixbuf, i);
            dst->linesize[i] = CVPixel_বাফার_Get_Bytes_Per_Row_Of_Plane(pixbuf, i);
        }
    } অন্যথা {
        dst->তথ্য[0]     = CVPixel_বাফার_Get_Base_Address(pixbuf);
        dst->linesize[0] = CVPixel_বাফার_Get_Bytes_Per_Row(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (শূন্য *)(uintptr_t)map_flags);
    যদি (ret < 0)
        যাও unlock;

    ফেরত 0;

unlock:
    CVPixel_বাফার_Unlock_Base_Address(pixbuf, map_flags);
    ফেরত ret;
}

স্থির পূর্ণসংখ্যা vt_transfer_তথ্য_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, ধ্রুবক AVFrame *src)
{
    AVFrame *map;
    পূর্ণসংখ্যা err;

    যদি (dst->width > hwfc->width || dst->height > hwfc->height)
        ফেরত AVERROR(EINVAL);

    map = av_frame_alloc();
    যদি (!map)
        ফেরত AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    যদি (err)
        যাও fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    যদি (err)
        যাও fail;

    err = 0;
fail:
    av_frame_free(&map);
    ফেরত err;
}

স্থির পূর্ণসংখ্যা vt_transfer_তথ্য_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, ধ্রুবক AVFrame *src)
{
    AVFrame *map;
    পূর্ণসংখ্যা err;

    যদি (src->width > hwfc->width || src->height > hwfc->height)
        ফেরত AVERROR(EINVAL);

    map = av_frame_alloc();
    যদি (!map)
        ফেরত AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    যদি (err)
        যাও fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    যদি (err)
        যাও fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixel_বাফার_Ref)dst->তথ্য[3], src);
    যদি (err)
        যাও fail;

    err = 0;
fail:
    av_frame_free(&map);
    ফেরত err;
}

স্থির পূর্ণসংখ্যা vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    পূর্ণসংখ্যা err;

    যদি (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    অন্যথা যদি (dst->format != hwfc->sw_format)
        ফেরত AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    যদি (err)
        ফেরত err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    যদি (err)
        ফেরত err;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা vt_device_create(AVHWDeviceContext *ctx, ধ্রুবক অক্ষর *device,
                            AVDictionary *opts, পূর্ণসংখ্যা flags)
{
    যদি (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        ফেরত AVERROR_UNKNOWN;
    }

    ফেরত 0;
}

ধ্রুবক HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .frames_hwctx_আকার    = আকার(VTFramesContext),

    .device_create        = vt_device_create,
    .frames_init          = vt_frames_init,
    .frames_get_বাফার    = vt_get_বাফার,
    .frames_get_constraints = vt_frames_get_constraints,
    .frames_uninit        = vt_frames_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_তথ্য_to     = vt_transfer_তথ্য_to,
    .transfer_তথ্য_from   = vt_transfer_তথ্য_from,
    .map_from             = vt_map_from,

    .pix_fmts = (ধ্রুবক গণনা AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
