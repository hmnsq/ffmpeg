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

#അന്തര്ഭാവ "config.h"

#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ <VideoToolbox/VideoToolbox.h>

#അന്തര്ഭാവ "buffer.h"
#അന്തര്ഭാവ "buffer_internal.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "hwcontext.h"
#അന്തര്ഭാവ "hwcontext_internal.h"
#അന്തര്ഭാവ "hwcontext_videotoolbox.h"
#അന്തര്ഭാവ "attributes.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "pixfmt.h"
#അന്തര്ഭാവ "pixdesc.h"

തരനിർവചനം ഘടന VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixelBufferPoolRef pool;
} VTFramesContext;

സ്ഥിതം സ്ഥിരം ഘടന {
    uint32_t cv_fmt;
    bool full_range;
    എണ്ണൽ AVPixelFormat pix_fmt;
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
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#endif
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

സ്ഥിതം സ്ഥിരം എണ്ണൽ AVPixelFormat supported_formats[] = {
#ifdef kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#endif
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#എങ്കിൽ HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#endif
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_frames_get_constraints(AVHWDeviceContext *ctx,
                                     സ്ഥിരം ശൂന്യം *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    പൂർണ്ണസംഖ്യ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    വലുപ്പം(*constraints->valid_sw_formats));
    എങ്കിൽ (!constraints->valid_sw_formats)
        തിരികെ AVERROR(ENOMEM);

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, വലുപ്പം(*constraints->valid_hw_formats));
    എങ്കിൽ (!constraints->valid_hw_formats)
        തിരികെ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    തിരികെ 0;
}

എണ്ണൽ AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        എങ്കിൽ (cv_pix_fmts[i].cv_fmt == cv_fmt)
            തിരികെ cv_pix_fmts[i].pix_fmt;
    }
    തിരികെ AV_PIX_FMT_NONE;
}

സ്ഥിതം uint32_t vt_format_from_pixfmt(എണ്ണൽ AVPixelFormat pix_fmt,
                                      എണ്ണൽ AVColorRange range)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        എങ്കിൽ (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            പൂർണ്ണസംഖ്യ full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            എങ്കിൽ (range == AVCOL_RANGE_UNSPECIFIED)
                തിരികെ cv_pix_fmts[i].cv_fmt;

            എങ്കിൽ (cv_pix_fmts[i].full_range == full_range)
                തിരികെ cv_pix_fmts[i].cv_fmt;
        }
    }

    തിരികെ 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(എണ്ണൽ AVPixelFormat pix_fmt)
{
    തിരികെ av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(എണ്ണൽ AVPixelFormat pix_fmt, bool full_range)
{
    തിരികെ vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef attributes, iosurface_properties;

    attributes = CFDictionaryCreateMutable(
        ശൂന്യ,
        2,
        &k_CFType_Dictionary_താക്കോൽ_Call_Backs,
        &k_CFType_Dictionary_മൂല്യം_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(ശൂന്യ, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_Set_മൂല്യം(
        attributes,
        k_CVPixel_Buffer_Pixel_Format_Type_താക്കോൽ,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        ശൂന്യ,
        0,
        &k_CFType_Dictionary_താക്കോൽ_Call_Backs,
        &k_CFType_Dictionary_മൂല്യം_Call_Backs);
    CFDictionary_Set_മൂല്യം(attributes, k_CVPixel_Buffer_IOSurface_Properties_താക്കോൽ, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(ശൂന്യ, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(ശൂന്യ, kCFNumberSInt32Type, &ctx->height);
    CFDictionary_Set_മൂല്യം(attributes, k_CVPixel_Buffer_Width_താക്കോൽ, w);
    CFDictionary_Set_മൂല്യം(attributes, k_CVPixel_Buffer_Height_താക്കോൽ, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixelBufferPoolCreate(
        ശൂന്യ,
        ശൂന്യ,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    എങ്കിൽ (err == kCVReturnSuccess)
        തിരികെ 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    തിരികെ AVERROR_EXTERNAL;
}

സ്ഥിതം ശൂന്യം videotoolbox_buffer_release(ശൂന്യം *opaque, uint8_t *data)
{
    CVPixelBufferRelease((CVPixelBufferRef)data);
}

സ്ഥിതം AVBufferRef *vt_pool_alloc_buffer(ശൂന്യം *opaque, size_t size)
{
    CVPixelBufferRef pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixelBufferPoolCreatePixelBuffer(
        ശൂന്യ,
        fctx->pool,
        &pixbuf
    );
    എങ്കിൽ (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        തിരികെ ശൂന്യ;
    }

    buf = av_buffer_create((uint8_t *)pixbuf, size,
                           videotoolbox_buffer_release, ശൂന്യ, 0);
    എങ്കിൽ (!buf) {
        CVPixelBufferRelease(pixbuf);
        തിരികെ ശൂന്യ;
    }
    തിരികെ buf;
}

സ്ഥിതം ശൂന്യം vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    എങ്കിൽ (fctx->pool) {
        CVPixelBufferPoolRelease(fctx->pool);
        fctx->pool = ശൂന്യ;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_frames_init(AVHWFramesContext *ctx)
{
    പൂർണ്ണസംഖ്യ i, ret;

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        എങ്കിൽ (ctx->sw_format == supported_formats[i])
            നിർത്തുക;
    }
    എങ്കിൽ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        തിരികെ AVERROR(ENOSYS);
    }

    എങ്കിൽ (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(
                വലുപ്പം(CVPixelBufferRef), ctx, vt_pool_alloc_buffer, ശൂന്യ);
        എങ്കിൽ (!ffhwframesctx(ctx)->pool_internal)
            തിരികെ AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    എങ്കിൽ (!frame->buf[0])
        തിരികെ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   എണ്ണൽ AVHWFrameTransferDirection dir,
                                   എണ്ണൽ AVPixelFormat **formats)
{
    എണ്ണൽ AVPixelFormat *fmts = av_malloc_array(2, വലുപ്പം(*fmts));
    എങ്കിൽ (!fmts)
        തിരികെ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)hwmap->source->data[3];

    CVPixelBufferUnlockBaseAddress(pixbuf, (uintptr_t)hwmap->priv);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_pixbuf_set_par(ശൂന്യം *log_ctx,
                             CVPixelBufferRef pixbuf, സ്ഥിരം AVFrame *src)
{
    CFMutableDictionaryRef par = ശൂന്യ;
    CFNumberRef അക്കം = ശൂന്യ, den = ശൂന്യ;
    AVRational avpar = src->sample_aspect_ratio;

    എങ്കിൽ (avpar.അക്കം == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Pixel_Aspect_Ratio_താക്കോൽ);
        തിരികെ 0;
    }

    av_reduce(&avpar.അക്കം, &avpar.den,
                avpar.അക്കം, avpar.den,
                0xFFFFFFFF);

    അക്കം = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.അക്കം);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_താക്കോൽ_Call_Backs,
                                    &k_CFType_Dictionary_മൂല്യം_Call_Backs);

    എങ്കിൽ (!par || !അക്കം || !den) {
        എങ്കിൽ (par) CFRelease(par);
        എങ്കിൽ (അക്കം) CFRelease(അക്കം);
        എങ്കിൽ (den) CFRelease(den);
        തിരികെ AVERROR(ENOMEM);
    }

    CFDictionary_Set_മൂല്യം(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Horizontal_Spacing_താക്കോൽ,
        അക്കം);
    CFDictionary_Set_മൂല്യം(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Vertical_Spacing_താക്കോൽ,
        den);

    CVBufferSetAttachment(
        pixbuf,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_താക്കോൽ,
        par,
        kCVAttachmentMode_ShouldPropagate
    );

    CFRelease(par);
    CFRelease(അക്കം);
    CFRelease(den);

    തിരികെ 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(എണ്ണൽ AVChromaLocation loc)
{
    തിരഞ്ഞെടുപ്പ് (loc) {
    അവസ്ഥ AVCHROMA_LOC_ഇടത്:
        തിരികെ k_CVImage_Buffer_Chroma_Location_ഇടത്;
    അവസ്ഥ AVCHROMA_LOC_CENTER:
        തിരികെ kCVImageBufferChromaLocation_Center;
    അവസ്ഥ AVCHROMA_LOC_മുകൾ:
        തിരികെ k_CVImage_Buffer_Chroma_Location_മുകൾ;
    അവസ്ഥ AVCHROMA_LOC_BOTTOM:
        തിരികെ kCVImageBufferChromaLocation_Bottom;
    അവസ്ഥ AVCHROMA_LOC_TOPLEFT:
        തിരികെ k_CVImage_Buffer_Chroma_Location_മുകൾ_ഇടത്;
    അവസ്ഥ AVCHROMA_LOC_BOTTOMLEFT:
        തിരികെ k_CVImage_Buffer_Chroma_Location_Bottom_ഇടത്;
    സ്ഥിരസ്ഥിതി:
        തിരികെ ശൂന്യ;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_pixbuf_set_chromaloc(ശൂന്യം *log_ctx,
                                   CVPixelBufferRef pixbuf, സ്ഥിരം AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    എങ്കിൽ (loc) {
        CVBufferSetAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_മുകൾ_Field_താക്കോൽ,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } അല്ലെങ്കിൽ
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_മുകൾ_Field_താക്കോൽ);

    തിരികെ 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(എണ്ണൽ AVColorSpace space)
{
    തിരഞ്ഞെടുപ്പ് (space) {
    അവസ്ഥ AVCOL_SPC_BT2020_CL:
    അവസ്ഥ AVCOL_SPC_BT2020_NCL:
#എങ്കിൽ HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        എങ്കിൽ (__builtin_available(macOS 10.11, iOS 9, *))
            തിരികെ kCVImageBufferYCbCrMatrix_ITU_R_2020;
#endif
        തിരികെ CFSTR("ITU_R_2020");
    അവസ്ഥ AVCOL_SPC_BT470BG:
    അവസ്ഥ AVCOL_SPC_SMPTE170M:
        തിരികെ kCVImageBufferYCbCrMatrix_ITU_R_601_4;
    അവസ്ഥ AVCOL_SPC_BT709:
        തിരികെ kCVImageBufferYCbCrMatrix_ITU_R_709_2;
    അവസ്ഥ AVCOL_SPC_SMPTE240M:
        തിരികെ kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
    സ്ഥിരസ്ഥിതി:
#എങ്കിൽ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        എങ്കിൽ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            തിരികെ CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
    അവസ്ഥ AVCOL_SPC_UNSPECIFIED:
        തിരികെ ശൂന്യ;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(എണ്ണൽ AVColorPrimaries pri)
{
    തിരഞ്ഞെടുപ്പ് (pri) {
    അവസ്ഥ AVCOL_PRI_BT2020:
#എങ്കിൽ HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        എങ്കിൽ (__builtin_available(macOS 10.11, iOS 9, *))
            തിരികെ kCVImageBufferColorPrimaries_ITU_R_2020;
#endif
        തിരികെ CFSTR("ITU_R_2020");
    അവസ്ഥ AVCOL_PRI_BT709:
        തിരികെ kCVImageBufferColorPrimaries_ITU_R_709_2;
    അവസ്ഥ AVCOL_PRI_SMPTE170M:
        തിരികെ kCVImageBufferColorPrimaries_SMPTE_C;
    അവസ്ഥ AVCOL_PRI_BT470BG:
        തിരികെ kCVImageBufferColorPrimaries_EBU_3213;
    സ്ഥിരസ്ഥിതി:
#എങ്കിൽ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        എങ്കിൽ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            തിരികെ CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
    അവസ്ഥ AVCOL_PRI_UNSPECIFIED:
        തിരികെ ശൂന്യ;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(എണ്ണൽ AVColorTransferCharacteristic trc)
{

    തിരഞ്ഞെടുപ്പ് (trc) {
    അവസ്ഥ AVCOL_TRC_SMPTE2084:
#എങ്കിൽ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        എങ്കിൽ (__builtin_available(macOS 10.13, iOS 11, *))
            തിരികെ kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
#endif
        തിരികെ CFSTR("SMPTE_ST_2084_PQ");
    അവസ്ഥ AVCOL_TRC_BT2020_10:
    അവസ്ഥ AVCOL_TRC_BT2020_12:
#എങ്കിൽ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        എങ്കിൽ (__builtin_available(macOS 10.11, iOS 9, *))
            തിരികെ kCVImageBufferTransferFunction_ITU_R_2020;
#endif
        തിരികെ CFSTR("ITU_R_2020");
    അവസ്ഥ AVCOL_TRC_BT709:
        തിരികെ kCVImageBufferTransferFunction_ITU_R_709_2;
    അവസ്ഥ AVCOL_TRC_SMPTE240M:
        തിരികെ kCVImageBufferTransferFunction_SMPTE_240M_1995;
    അവസ്ഥ AVCOL_TRC_SMPTE428:
#എങ്കിൽ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        എങ്കിൽ (__builtin_available(macOS 10.12, iOS 10, *))
            തിരികെ kCVImageBufferTransferFunction_SMPTE_ST_428_1;
#endif
        തിരികെ CFSTR("SMPTE_ST_428_1");
    അവസ്ഥ AVCOL_TRC_ARIB_STD_B67:
#എങ്കിൽ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        എങ്കിൽ (__builtin_available(macOS 10.13, iOS 11, *))
            തിരികെ kCVImageBufferTransferFunction_ITU_R_2100_HLG;
#endif
        തിരികെ CFSTR("ITU_R_2100_HLG");
    അവസ്ഥ AVCOL_TRC_GAMMA22:
        തിരികെ kCVImageBufferTransferFunction_UseGamma;
    അവസ്ഥ AVCOL_TRC_GAMMA28:
        തിരികെ kCVImageBufferTransferFunction_UseGamma;
    സ്ഥിരസ്ഥിതി:
#എങ്കിൽ HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        എങ്കിൽ (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            തിരികെ CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    അവസ്ഥ AVCOL_TRC_UNSPECIFIED:
        തിരികെ ശൂന്യ;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
സ്ഥിതം CFDictionaryRef vt_cv_buffer_copy_attachments(CVBufferRef buffer,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #എങ്കിൽ (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        എങ്കിൽ (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            തിരികെ CVBufferCopyAttachments(buffer, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #എങ്കിൽ (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(buffer, attachment_mode);
        തിരികെ (dict) ? CFDictionaryCreateCopy(ശൂന്യ, dict) : ശൂന്യ;
    #അല്ലെങ്കിൽ
        തിരികെ ശൂന്യ; // Impossible, just make the compiler happy
    #endif
}

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_pixbuf_set_colorspace(ശൂന്യം *log_ctx,
                                    CVPixelBufferRef pixbuf, സ്ഥിരം AVFrame *src)
{
    CGColorSpaceRef colorspace = ശൂന്യ;
    CFStringRef colormatrix = ശൂന്യ, colorpri = ശൂന്യ, colortrc = ശൂന്യ;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    എങ്കിൽ (colormatrix)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_താക്കോൽ,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    അല്ലെങ്കിൽ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_താക്കോൽ);
        എങ്കിൽ (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    എങ്കിൽ (colorpri)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_താക്കോൽ,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    അല്ലെങ്കിൽ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_താക്കോൽ);
        എങ്കിൽ (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    എങ്കിൽ (colortrc)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_താക്കോൽ,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    അല്ലെങ്കിൽ {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_താക്കോൽ);
        എങ്കിൽ (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    എങ്കിൽ (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    അല്ലെങ്കിൽ എങ്കിൽ (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    എങ്കിൽ (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(ശൂന്യ, kCFNumberFloat32Type, &gamma);
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_താക്കോൽ,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } അല്ലെങ്കിൽ
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_താക്കോൽ);

#എങ്കിൽ (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    എങ്കിൽ (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_buffer_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        എങ്കിൽ (attachments) {
            colorspace =
                CVImageBufferCreateColorSpaceFromAttachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    എങ്കിൽ (colorspace) {
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_താക്കോൽ,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } അല്ലെങ്കിൽ
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_താക്കോൽ);

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_pixbuf_set_attachments(ശൂന്യം *log_ctx,
                                     CVPixelBufferRef pixbuf, സ്ഥിരം AVFrame *src)
{
    പൂർണ്ണസംഖ്യ ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_vt_pixbuf_set_attachments(ശൂന്യം *log_ctx,
                                 CVPixelBufferRef pixbuf, സ്ഥിരം AVFrame *src)
{
    തിരികെ vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, സ്ഥിരം AVFrame *src,
                        പൂർണ്ണസംഖ്യ flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)src->data[3];
    OSType pixel_format = CVPixelBufferGetPixelFormatType(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    പൂർണ്ണസംഖ്യ ret;
    പൂർണ്ണസംഖ്യ i;
    എണ്ണൽ AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    എങ്കിൽ (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        തിരികെ AVERROR_UNKNOWN;
    }

    എങ്കിൽ (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    എങ്കിൽ (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    എങ്കിൽ (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    എങ്കിൽ (CVPixelBufferIsPlanar(pixbuf)) {
        പൂർണ്ണസംഖ്യ planes = CVPixel_Buffer_Get_Plane_എണ്ണം(pixbuf);
        വേണ്ടി (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } അല്ലെങ്കിൽ {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (ശൂന്യം *)(uintptr_t)map_flags);
    എങ്കിൽ (ret < 0)
        പോകുക unlock;

    തിരികെ 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, സ്ഥിരം AVFrame *src)
{
    AVFrame *map;
    പൂർണ്ണസംഖ്യ err;

    എങ്കിൽ (dst->width > hwfc->width || dst->height > hwfc->height)
        തിരികെ AVERROR(EINVAL);

    map = av_frame_alloc();
    എങ്കിൽ (!map)
        തിരികെ AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    എങ്കിൽ (err)
        പോകുക fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    എങ്കിൽ (err)
        പോകുക fail;

    err = 0;
fail:
    av_frame_free(&map);
    തിരികെ err;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_transfer_data_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, സ്ഥിരം AVFrame *src)
{
    AVFrame *map;
    പൂർണ്ണസംഖ്യ err;

    എങ്കിൽ (src->width > hwfc->width || src->height > hwfc->height)
        തിരികെ AVERROR(EINVAL);

    map = av_frame_alloc();
    എങ്കിൽ (!map)
        തിരികെ AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    എങ്കിൽ (err)
        പോകുക fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    എങ്കിൽ (err)
        പോകുക fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixelBufferRef)dst->data[3], src);
    എങ്കിൽ (err)
        പോകുക fail;

    err = 0;
fail:
    av_frame_free(&map);
    തിരികെ err;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    പൂർണ്ണസംഖ്യ err;

    എങ്കിൽ (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    അല്ലെങ്കിൽ എങ്കിൽ (dst->format != hwfc->sw_format)
        തിരികെ AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    എങ്കിൽ (err)
        തിരികെ err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    എങ്കിൽ (err)
        തിരികെ err;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ vt_device_create(AVHWDeviceContext *ctx, സ്ഥിരം അക്ഷരം *device,
                            AVDictionary *opts, പൂർണ്ണസംഖ്യ flags)
{
    എങ്കിൽ (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    തിരികെ 0;
}

സ്ഥിരം HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .frames_hwctx_size    = വലുപ്പം(VTFramesContext),

    .device_create        = vt_device_create,
    .frames_init          = vt_frames_init,
    .frames_get_buffer    = vt_get_buffer,
    .frames_get_constraints = vt_frames_get_constraints,
    .frames_uninit        = vt_frames_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_data_to     = vt_transfer_data_to,
    .transfer_data_from   = vt_transfer_data_from,
    .map_from             = vt_map_from,

    .pix_fmts = (സ്ഥിരം എണ്ണൽ AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
