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

#અન્તર્ભાવ "config.h"

#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ <VideoToolbox/VideoToolbox.h>

#અન્તર્ભાવ "buffer.h"
#અન્તર્ભાવ "buffer_internal.h"
#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "hwcontext.h"
#અન્તર્ભાવ "hwcontext_internal.h"
#અન્તર્ભાવ "hwcontext_videotoolbox.h"
#અન્તર્ભાવ "attributes.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "pixfmt.h"
#અન્તર્ભાવ "pixdesc.h"

પ્રકારવ્યાખ્યા સંરચના VTFramesContext {
    /**
     * The public AVVTFramesContext. See hwcontext_videotoolbox.h for it.
     */
    AVVTFramesContext p;
    CVPixelBufferPoolRef pool;
} VTFramesContext;

સ્થિર અચલ સંરચના {
    uint32_t cv_fmt;
    bool full_range;
    ગણના AVPixelFormat pix_fmt;
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
#જો HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P010 },
    { kCVPixelFormatType_420YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P010 },
#endif
#જો HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV16 },
    { kCVPixelFormatType_422YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV16 },
#endif
#જો HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P210 },
    { kCVPixelFormatType_422YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P210 },
#endif
#જો HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_422YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P216 },
#endif
#જો HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr8BiPlanarVideoRange,  false, AV_PIX_FMT_NV24 },
    { kCVPixelFormatType_444YpCbCr8BiPlanarFullRange,   true,  AV_PIX_FMT_NV24 },
#endif
#જો HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr10BiPlanarVideoRange, false, AV_PIX_FMT_P410 },
    { kCVPixelFormatType_444YpCbCr10BiPlanarFullRange,  true,  AV_PIX_FMT_P410 },
#endif
#જો HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    { kCVPixelFormatType_444YpCbCr16BiPlanarVideoRange, false, AV_PIX_FMT_P416 },
#endif
#જો HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    { kCVPixelFormatType_422YpCbCr8_yuvs,               false, AV_PIX_FMT_YUYV422 },
#endif
    { 'bp16'/*kCVPixelFormatType_16VersatileBayer*/,    false, AV_PIX_FMT_BAYER_RGGB16},
};

સ્થિર અચલ ગણના AVPixelFormat supported_formats[] = {
#ifdef kCFCoreFoundationVersionNumber10_7
    AV_PIX_FMT_NV12,
    AV_PIX_FMT_AYUV,
    AV_PIX_FMT_AYUV64,
#endif
    AV_PIX_FMT_YUV420P,
    AV_PIX_FMT_UYVY422,
#જો HAVE_KCVPIXELFORMATTYPE_420YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P010,
#endif
#જો HAVE_KCVPIXELFORMATTYPE_422YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV16,
#endif
#જો HAVE_KCVPIXELFORMATTYPE_422YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P210,
#endif
#જો HAVE_KCVPIXELFORMATTYPE_422YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P216,
#endif
#જો HAVE_KCVPIXELFORMATTYPE_444YPCBCR8BIPLANARVIDEORANGE
    AV_PIX_FMT_NV24,
#endif
#જો HAVE_KCVPIXELFORMATTYPE_444YPCBCR10BIPLANARVIDEORANGE
    AV_PIX_FMT_P410,
#endif
#જો HAVE_KCVPIXELFORMATTYPE_444YPCBCR16BIPLANARVIDEORANGE
    AV_PIX_FMT_P416,
#endif
#જો HAVE_KCVPIXELFORMATTYPE_422YPCBCR8_YUVS
    AV_PIX_FMT_YUYV422,
#endif
    AV_PIX_FMT_BGRA,
    AV_PIX_FMT_BAYER_RGGB16,
};

સ્થિર પૂર્ણાંક vt_frames_get_constraints(AVHWDeviceContext *ctx,
                                     અચલ શૂન્ય *hwconfig,
                                     AVHWFramesConstraints *constraints)
{
    પૂર્ણાંક i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_formats) + 1,
                                                    કદ(*constraints->valid_sw_formats));
    જો (!constraints->valid_sw_formats)
        પાછા AVERROR(ENOMEM);

    માટે (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++)
        constraints->valid_sw_formats[i] = supported_formats[i];
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, કદ(*constraints->valid_hw_formats));
    જો (!constraints->valid_hw_formats)
        પાછા AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VIDEOTOOLBOX;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    પાછા 0;
}

ગણના AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        જો (cv_pix_fmts[i].cv_fmt == cv_fmt)
            પાછા cv_pix_fmts[i].pix_fmt;
    }
    પાછા AV_PIX_FMT_NONE;
}

સ્થિર uint32_t vt_format_from_pixfmt(ગણના AVPixelFormat pix_fmt,
                                      ગણના AVColorRange range)
{
    માટે (પૂર્ણાંક i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        જો (cv_pix_fmts[i].pix_fmt == pix_fmt) {
            પૂર્ણાંક full_range = (range == AVCOL_RANGE_JPEG);

            // Don't care if unspecified
            જો (range == AVCOL_RANGE_UNSPECIFIED)
                પાછા cv_pix_fmts[i].cv_fmt;

            જો (cv_pix_fmts[i].full_range == full_range)
                પાછા cv_pix_fmts[i].cv_fmt;
        }
    }

    પાછા 0;
}

uint32_t av_map_videotoolbox_format_from_pixfmt(ગણના AVPixelFormat pix_fmt)
{
    પાછા av_map_videotoolbox_format_from_pixfmt2(pix_fmt, false);
}

uint32_t av_map_videotoolbox_format_from_pixfmt2(ગણના AVPixelFormat pix_fmt, bool full_range)
{
    પાછા vt_format_from_pixfmt(pix_fmt, full_range ? AVCOL_RANGE_JPEG : AVCOL_RANGE_MPEG);
}

સ્થિર પૂર્ણાંક vt_pool_alloc(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    AVVTFramesContext *hw_ctx = &fctx->p;
    CVReturn err;
    CFNumberRef w, h, pixfmt;
    uint32_t cv_pixfmt;
    CFMutableDictionaryRef attributes, iosurface_properties;

    attributes = CFDictionaryCreateMutable(
        ખાલી,
        2,
        &k_CFType_Dictionary_ચાવી_Call_Backs,
        &k_CFType_Dictionary_કિંમત_Call_Backs);

    cv_pixfmt = vt_format_from_pixfmt(ctx->sw_format, hw_ctx->color_range);
    pixfmt = CFNumberCreate(ખાલી, kCFNumberSInt32Type, &cv_pixfmt);
    CFDictionary_Set_કિંમત(
        attributes,
        k_CVPixel_Buffer_Pixel_Format_Type_ચાવી,
        pixfmt);
    CFRelease(pixfmt);

    iosurface_properties = CFDictionaryCreateMutable(
        ખાલી,
        0,
        &k_CFType_Dictionary_ચાવી_Call_Backs,
        &k_CFType_Dictionary_કિંમત_Call_Backs);
    CFDictionary_Set_કિંમત(attributes, k_CVPixel_Buffer_IOSurface_Properties_ચાવી, iosurface_properties);
    CFRelease(iosurface_properties);

    w = CFNumberCreate(ખાલી, kCFNumberSInt32Type, &ctx->width);
    h = CFNumberCreate(ખાલી, kCFNumberSInt32Type, &ctx->height);
    CFDictionary_Set_કિંમત(attributes, k_CVPixel_Buffer_Width_ચાવી, w);
    CFDictionary_Set_કિંમત(attributes, k_CVPixel_Buffer_Height_ચાવી, h);
    CFRelease(w);
    CFRelease(h);

    err = CVPixelBufferPoolCreate(
        ખાલી,
        ખાલી,
        attributes,
        &fctx->pool);
    CFRelease(attributes);

    જો (err == kCVReturnSuccess)
        પાછા 0;

    av_log(ctx, AV_LOG_ERROR, "Error creating CVPixelBufferPool: %d\n", err);
    પાછા AVERROR_EXTERNAL;
}

સ્થિર શૂન્ય videotoolbox_buffer_release(શૂન્ય *opaque, uint8_t *data)
{
    CVPixelBufferRelease((CVPixelBufferRef)data);
}

સ્થિર AVBufferRef *vt_pool_alloc_buffer(શૂન્ય *opaque, size_t size)
{
    CVPixelBufferRef pixbuf;
    AVBufferRef *buf;
    CVReturn err;
    AVHWFramesContext *ctx = opaque;
    VTFramesContext *fctx = ctx->hwctx;

    err = CVPixelBufferPoolCreatePixelBuffer(
        ખાલી,
        fctx->pool,
        &pixbuf
    );
    જો (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create pixel buffer from pool: %d\n", err);
        પાછા ખાલી;
    }

    buf = av_buffer_create((uint8_t *)pixbuf, size,
                           videotoolbox_buffer_release, ખાલી, 0);
    જો (!buf) {
        CVPixelBufferRelease(pixbuf);
        પાછા ખાલી;
    }
    પાછા buf;
}

સ્થિર શૂન્ય vt_frames_uninit(AVHWFramesContext *ctx)
{
    VTFramesContext *fctx = ctx->hwctx;
    જો (fctx->pool) {
        CVPixelBufferPoolRelease(fctx->pool);
        fctx->pool = ખાલી;
    }
}

સ્થિર પૂર્ણાંક vt_frames_init(AVHWFramesContext *ctx)
{
    પૂર્ણાંક i, ret;

    માટે (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        જો (ctx->sw_format == supported_formats[i])
            તોડો;
    }
    જો (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(ctx->sw_format));
        પાછા AVERROR(ENOSYS);
    }

    જો (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(
                કદ(CVPixelBufferRef), ctx, vt_pool_alloc_buffer, ખાલી);
        જો (!ffhwframesctx(ctx)->pool_internal)
            પાછા AVERROR(ENOMEM);
    }

    ret = vt_pool_alloc(ctx);
    જો (ret < 0)
        પાછા ret;

    પાછા 0;
}

સ્થિર પૂર્ણાંક vt_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    જો (!frame->buf[0])
        પાછા AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VIDEOTOOLBOX;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    પાછા 0;
}

સ્થિર પૂર્ણાંક vt_transfer_get_formats(AVHWFramesContext *ctx,
                                   ગણના AVHWFrameTransferDirection dir,
                                   ગણના AVPixelFormat **formats)
{
    ગણના AVPixelFormat *fmts = av_malloc_array(2, કદ(*fmts));
    જો (!fmts)
        પાછા AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;
    પાછા 0;
}

સ્થિર શૂન્ય vt_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)hwmap->source->data[3];

    CVPixelBufferUnlockBaseAddress(pixbuf, (uintptr_t)hwmap->priv);
}

સ્થિર પૂર્ણાંક vt_pixbuf_set_par(શૂન્ય *log_ctx,
                             CVPixelBufferRef pixbuf, અચલ AVFrame *src)
{
    CFMutableDictionaryRef par = ખાલી;
    CFNumberRef અંક = ખાલી, den = ખાલી;
    AVRational avpar = src->sample_aspect_ratio;

    જો (avpar.અંક == 0) {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Pixel_Aspect_Ratio_ચાવી);
        પાછા 0;
    }

    av_reduce(&avpar.અંક, &avpar.den,
                avpar.અંક, avpar.den,
                0xFFFFFFFF);

    અંક = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.અંક);

    den = CFNumberCreate(kCFAllocatorDefault,
                            kCFNumberIntType,
                            &avpar.den);

    par = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                    2,
                                    &k_CFCopy_String_Dictionary_ચાવી_Call_Backs,
                                    &k_CFType_Dictionary_કિંમત_Call_Backs);

    જો (!par || !અંક || !den) {
        જો (par) CFRelease(par);
        જો (અંક) CFRelease(અંક);
        જો (den) CFRelease(den);
        પાછા AVERROR(ENOMEM);
    }

    CFDictionary_Set_કિંમત(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Horizontal_Spacing_ચાવી,
        અંક);
    CFDictionary_Set_કિંમત(
        par,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_Vertical_Spacing_ચાવી,
        den);

    CVBufferSetAttachment(
        pixbuf,
        k_CVImage_Buffer_Pixel_Aspect_Ratio_ચાવી,
        par,
        kCVAttachmentMode_ShouldPropagate
    );

    CFRelease(par);
    CFRelease(અંક);
    CFRelease(den);

    પાછા 0;
}

CFStringRef av_map_videotoolbox_chroma_loc_from_av(ગણના AVChromaLocation loc)
{
    પસંદગી (loc) {
    સ્થિતિ AVCHROMA_LOC_ડાબું:
        પાછા k_CVImage_Buffer_Chroma_Location_ડાબું;
    સ્થિતિ AVCHROMA_LOC_CENTER:
        પાછા kCVImageBufferChromaLocation_Center;
    સ્થિતિ AVCHROMA_LOC_ટોચ:
        પાછા k_CVImage_Buffer_Chroma_Location_ટોચ;
    સ્થિતિ AVCHROMA_LOC_BOTTOM:
        પાછા kCVImageBufferChromaLocation_Bottom;
    સ્થિતિ AVCHROMA_LOC_TOPLEFT:
        પાછા k_CVImage_Buffer_Chroma_Location_ટોચ_ડાબું;
    સ્થિતિ AVCHROMA_LOC_BOTTOMLEFT:
        પાછા k_CVImage_Buffer_Chroma_Location_Bottom_ડાબું;
    મૂળભૂત:
        પાછા ખાલી;
    }
}

સ્થિર પૂર્ણાંક vt_pixbuf_set_chromaloc(શૂન્ય *log_ctx,
                                   CVPixelBufferRef pixbuf, અચલ AVFrame *src)
{
    CFStringRef loc = av_map_videotoolbox_chroma_loc_from_av(src->chroma_location);

    જો (loc) {
        CVBufferSetAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_ટોચ_Field_ચાવી,
            loc,
            kCVAttachmentMode_ShouldPropagate);
    } નહીંતર
        CVBufferRemoveAttachment(
            pixbuf,
            k_CVImage_Buffer_Chroma_Location_ટોચ_Field_ચાવી);

    પાછા 0;
}

CFStringRef av_map_videotoolbox_color_matrix_from_av(ગણના AVColorSpace space)
{
    પસંદગી (space) {
    સ્થિતિ AVCOL_SPC_BT2020_CL:
    સ્થિતિ AVCOL_SPC_BT2020_NCL:
#જો HAVE_KCVIMAGEBUFFERYCBCRMATRIX_ITU_R_2020
        જો (__builtin_available(macOS 10.11, iOS 9, *))
            પાછા kCVImageBufferYCbCrMatrix_ITU_R_2020;
#endif
        પાછા CFSTR("ITU_R_2020");
    સ્થિતિ AVCOL_SPC_BT470BG:
    સ્થિતિ AVCOL_SPC_SMPTE170M:
        પાછા kCVImageBufferYCbCrMatrix_ITU_R_601_4;
    સ્થિતિ AVCOL_SPC_BT709:
        પાછા kCVImageBufferYCbCrMatrix_ITU_R_709_2;
    સ્થિતિ AVCOL_SPC_SMPTE240M:
        પાછા kCVImageBufferYCbCrMatrix_SMPTE_240M_1995;
    મૂળભૂત:
#જો HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        જો (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            પાછા CVYCbCrMatrixGetStringForIntegerCodePoint(space);
        av_fallthrough;
#endif
    સ્થિતિ AVCOL_SPC_UNSPECIFIED:
        પાછા ખાલી;
    }
}

CFStringRef av_map_videotoolbox_color_primaries_from_av(ગણના AVColorPrimaries pri)
{
    પસંદગી (pri) {
    સ્થિતિ AVCOL_PRI_BT2020:
#જો HAVE_KCVIMAGEBUFFERCOLORPRIMARIES_ITU_R_2020
        જો (__builtin_available(macOS 10.11, iOS 9, *))
            પાછા kCVImageBufferColorPrimaries_ITU_R_2020;
#endif
        પાછા CFSTR("ITU_R_2020");
    સ્થિતિ AVCOL_PRI_BT709:
        પાછા kCVImageBufferColorPrimaries_ITU_R_709_2;
    સ્થિતિ AVCOL_PRI_SMPTE170M:
        પાછા kCVImageBufferColorPrimaries_SMPTE_C;
    સ્થિતિ AVCOL_PRI_BT470BG:
        પાછા kCVImageBufferColorPrimaries_EBU_3213;
    મૂળભૂત:
#જો HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        જો (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            પાછા CVColorPrimariesGetStringForIntegerCodePoint(pri);
        av_fallthrough;
#endif
    સ્થિતિ AVCOL_PRI_UNSPECIFIED:
        પાછા ખાલી;
    }
}

CFStringRef av_map_videotoolbox_color_trc_from_av(ગણના AVColorTransferCharacteristic trc)
{

    પસંદગી (trc) {
    સ્થિતિ AVCOL_TRC_SMPTE2084:
#જો HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_2084_PQ
        જો (__builtin_available(macOS 10.13, iOS 11, *))
            પાછા kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ;
#endif
        પાછા CFSTR("SMPTE_ST_2084_PQ");
    સ્થિતિ AVCOL_TRC_BT2020_10:
    સ્થિતિ AVCOL_TRC_BT2020_12:
#જો HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2020
        જો (__builtin_available(macOS 10.11, iOS 9, *))
            પાછા kCVImageBufferTransferFunction_ITU_R_2020;
#endif
        પાછા CFSTR("ITU_R_2020");
    સ્થિતિ AVCOL_TRC_BT709:
        પાછા kCVImageBufferTransferFunction_ITU_R_709_2;
    સ્થિતિ AVCOL_TRC_SMPTE240M:
        પાછા kCVImageBufferTransferFunction_SMPTE_240M_1995;
    સ્થિતિ AVCOL_TRC_SMPTE428:
#જો HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_SMPTE_ST_428_1
        જો (__builtin_available(macOS 10.12, iOS 10, *))
            પાછા kCVImageBufferTransferFunction_SMPTE_ST_428_1;
#endif
        પાછા CFSTR("SMPTE_ST_428_1");
    સ્થિતિ AVCOL_TRC_ARIB_STD_B67:
#જો HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        જો (__builtin_available(macOS 10.13, iOS 11, *))
            પાછા kCVImageBufferTransferFunction_ITU_R_2100_HLG;
#endif
        પાછા CFSTR("ITU_R_2100_HLG");
    સ્થિતિ AVCOL_TRC_GAMMA22:
        પાછા kCVImageBufferTransferFunction_UseGamma;
    સ્થિતિ AVCOL_TRC_GAMMA28:
        પાછા kCVImageBufferTransferFunction_UseGamma;
    મૂળભૂત:
#જો HAVE_KCVIMAGEBUFFERTRANSFERFUNCTION_ITU_R_2100_HLG
        જો (__builtin_available(macOS 10.13, iOS 11, tvOS 11, watchOS 4, *))
            પાછા CVTransferFunctionGetStringForIntegerCodePoint(trc);
        av_fallthrough;
#endif
    સ્થિતિ AVCOL_TRC_UNSPECIFIED:
        પાછા ખાલી;
    }
}

/**
 * Copy all attachments for the specified mode from the given buffer.
 */
સ્થિર CFDictionaryRef vt_cv_buffer_copy_attachments(CVBufferRef buffer,
                                                     CVAttachmentMode attachment_mode)
{
    // Check that our SDK is at least macOS 12 / iOS 15 / tvOS 15
    #જો (TARGET_OS_OSX  && defined(__MAC_12_0)    && __MAC_OS_X_VERSION_MAX_ALLOWED  >= __MAC_12_0)     || \
        (TARGET_OS_IOS  && defined(__IPHONE_15_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_15_0)  || \
        (TARGET_OS_TV   && defined(__TVOS_15_0)   && __TV_OS_VERSION_MAX_ALLOWED     >= __TVOS_15_0)
        // On recent enough versions, just use the respective API
        જો (__builtin_available(macOS 12.0, iOS 15.0, tvOS 15.0, *))
            પાછા CVBufferCopyAttachments(buffer, attachment_mode);
    #endif

    // Check that the target is lower than macOS 12 / iOS 15 / tvOS 15
    // else this would generate a deprecation warning and anyway never run because
    // the runtime availability check above would be always true.
    #જો (TARGET_OS_OSX  && (!defined(__MAC_12_0)    || __MAC_OS_X_VERSION_MIN_REQUIRED  < __MAC_12_0))     || \
        (TARGET_OS_IOS  && (!defined(__IPHONE_15_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_15_0))  || \
        (TARGET_OS_TV   && (!defined(__TVOS_15_0)   || __TV_OS_VERSION_MIN_REQUIRED     < __TVOS_15_0))
        // Fallback on SDKs or runtime versions < macOS 12 / iOS 15 / tvOS 15
        CFDictionaryRef dict = CVBufferGetAttachments(buffer, attachment_mode);
        પાછા (dict) ? CFDictionaryCreateCopy(ખાલી, dict) : ખાલી;
    #નહીંતર
        પાછા ખાલી; // Impossible, just make the compiler happy
    #endif
}

સ્થિર પૂર્ણાંક vt_pixbuf_set_colorspace(શૂન્ય *log_ctx,
                                    CVPixelBufferRef pixbuf, અચલ AVFrame *src)
{
    CGColorSpaceRef colorspace = ખાલી;
    CFStringRef colormatrix = ખાલી, colorpri = ખાલી, colortrc = ખાલી;
    Float32 gamma = 0;

    colormatrix = av_map_videotoolbox_color_matrix_from_av(src->colorspace);
    જો (colormatrix)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_ચાવી,
            colormatrix, kCVAttachmentMode_ShouldPropagate);
    નહીંતર {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_YCb_Cr_Matrix_ચાવી);
        જો (src->colorspace != AVCOL_SPC_UNSPECIFIED && src->colorspace != AVCOL_SPC_RGB)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color space %s is not supported.\n",
                av_color_space_name(src->colorspace));
    }

    colorpri = av_map_videotoolbox_color_primaries_from_av(src->color_primaries);
    જો (colorpri)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_ચાવી,
            colorpri, kCVAttachmentMode_ShouldPropagate);
    નહીંતર {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Color_Primaries_ચાવી);
        જો (src->color_primaries != AVCOL_PRI_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color primaries %s is not supported.\n",
                av_color_primaries_name(src->color_primaries));
    }

    colortrc = av_map_videotoolbox_color_trc_from_av(src->color_trc);
    જો (colortrc)
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_ચાવી,
            colortrc, kCVAttachmentMode_ShouldPropagate);
    નહીંતર {
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Transfer_Function_ચાવી);
        જો (src->color_trc != AVCOL_TRC_UNSPECIFIED)
            av_log(log_ctx, AV_LOG_WARNING,
                "Color transfer function %s is not supported.\n",
                av_color_transfer_name(src->color_trc));
    }

    જો (src->color_trc == AVCOL_TRC_GAMMA22)
        gamma = 2.2;
    નહીંતર જો (src->color_trc == AVCOL_TRC_GAMMA28)
        gamma = 2.8;

    જો (gamma != 0) {
        CFNumberRef gamma_level = CFNumberCreate(ખાલી, kCFNumberFloat32Type, &gamma);
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_ચાવી,
            gamma_level, kCVAttachmentMode_ShouldPropagate);
        CFRelease(gamma_level);
    } નહીંતર
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_Gamma_Level_ચાવી);

#જો (TARGET_OS_OSX && __MAC_OS_X_VERSION_MAX_ALLOWED >= 100800) || \
    (TARGET_OS_IOS && __IPHONE_OS_VERSION_MAX_ALLOWED >= 100000)
    જો (__builtin_available(macOS 10.8, iOS 10, *)) {
        CFDictionaryRef attachments =
            vt_cv_buffer_copy_attachments(pixbuf, kCVAttachmentMode_ShouldPropagate);

        જો (attachments) {
            colorspace =
                CVImageBufferCreateColorSpaceFromAttachments(attachments);
            CFRelease(attachments);
        }
    }
#endif

    // Done outside the above preprocessor code and if's so that
    // in any case a wrong kCVImageBufferCGColorSpaceKey is removed
    // if the above code is not used or fails.
    જો (colorspace) {
        CVBufferSetAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_ચાવી,
            colorspace, kCVAttachmentMode_ShouldPropagate);
        CFRelease(colorspace);
    } નહીંતર
        CVBufferRemoveAttachment(pixbuf, k_CVImage_Buffer_CGColor_Space_ચાવી);

    પાછા 0;
}

સ્થિર પૂર્ણાંક vt_pixbuf_set_attachments(શૂન્ય *log_ctx,
                                     CVPixelBufferRef pixbuf, અચલ AVFrame *src)
{
    પૂર્ણાંક ret;
    ret = vt_pixbuf_set_par(log_ctx, pixbuf, src);
    જો (ret < 0)
        પાછા ret;
    ret = vt_pixbuf_set_colorspace(log_ctx, pixbuf, src);
    જો (ret < 0)
        પાછા ret;
    ret = vt_pixbuf_set_chromaloc(log_ctx, pixbuf, src);
    જો (ret < 0)
        પાછા ret;
    પાછા 0;
}

પૂર્ણાંક av_vt_pixbuf_set_attachments(શૂન્ય *log_ctx,
                                 CVPixelBufferRef pixbuf, અચલ AVFrame *src)
{
    પાછા vt_pixbuf_set_attachments(log_ctx, pixbuf, src);
}

સ્થિર પૂર્ણાંક vt_map_frame(AVHWFramesContext *ctx, AVFrame *dst, અચલ AVFrame *src,
                        પૂર્ણાંક flags)
{
    CVPixelBufferRef pixbuf = (CVPixelBufferRef)src->data[3];
    OSType pixel_format = CVPixelBufferGetPixelFormatType(pixbuf);
    CVReturn err;
    uint32_t map_flags = 0;
    પૂર્ણાંક ret;
    પૂર્ણાંક i;
    ગણના AVPixelFormat format;

    format = av_map_videotoolbox_format_to_pixfmt(pixel_format);
    જો (dst->format != format) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported or mismatching pixel format: %s\n",
               av_fourcc2str(pixel_format));
        પાછા AVERROR_UNKNOWN;
    }

    જો (CVPixelBufferGetWidth(pixbuf) != ctx->width ||
        CVPixelBufferGetHeight(pixbuf) != ctx->height) {
        av_log(ctx, AV_LOG_ERROR, "Inconsistent frame dimensions.\n");
        પાછા AVERROR_UNKNOWN;
    }

    જો (flags == AV_HWFRAME_MAP_READ)
        map_flags = kCVPixelBufferLock_ReadOnly;

    err = CVPixelBufferLockBaseAddress(pixbuf, map_flags);
    જો (err != kCVReturnSuccess) {
        av_log(ctx, AV_LOG_ERROR, "Error locking the pixel buffer.\n");
        પાછા AVERROR_UNKNOWN;
    }

    જો (CVPixelBufferIsPlanar(pixbuf)) {
        પૂર્ણાંક planes = CVPixel_Buffer_Get_Plane_ગણતરી(pixbuf);
        માટે (i = 0; i < planes; i++) {
            dst->data[i]     = CVPixelBufferGetBaseAddressOfPlane(pixbuf, i);
            dst->linesize[i] = CVPixelBufferGetBytesPerRowOfPlane(pixbuf, i);
        }
    } નહીંતર {
        dst->data[0]     = CVPixelBufferGetBaseAddress(pixbuf);
        dst->linesize[0] = CVPixelBufferGetBytesPerRow(pixbuf);
    }

    ret = ff_hwframe_map_create(src->hw_frames_ctx, dst, src, vt_unmap,
                                (શૂન્ય *)(uintptr_t)map_flags);
    જો (ret < 0)
        જાઓ unlock;

    પાછા 0;

unlock:
    CVPixelBufferUnlockBaseAddress(pixbuf, map_flags);
    પાછા ret;
}

સ્થિર પૂર્ણાંક vt_transfer_data_from(AVHWFramesContext *hwfc,
                                 AVFrame *dst, અચલ AVFrame *src)
{
    AVFrame *map;
    પૂર્ણાંક err;

    જો (dst->width > hwfc->width || dst->height > hwfc->height)
        પાછા AVERROR(EINVAL);

    map = av_frame_alloc();
    જો (!map)
        પાછા AVERROR(ENOMEM);
    map->format = dst->format;

    err = vt_map_frame(hwfc, map, src, AV_HWFRAME_MAP_READ);
    જો (err)
        જાઓ fail;

    map->width  = dst->width;
    map->height = dst->height;

    err = av_frame_copy(dst, map);
    જો (err)
        જાઓ fail;

    err = 0;
fail:
    av_frame_free(&map);
    પાછા err;
}

સ્થિર પૂર્ણાંક vt_transfer_data_to(AVHWFramesContext *hwfc,
                               AVFrame *dst, અચલ AVFrame *src)
{
    AVFrame *map;
    પૂર્ણાંક err;

    જો (src->width > hwfc->width || src->height > hwfc->height)
        પાછા AVERROR(EINVAL);

    map = av_frame_alloc();
    જો (!map)
        પાછા AVERROR(ENOMEM);
    map->format = src->format;

    err = vt_map_frame(hwfc, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    જો (err)
        જાઓ fail;

    map->width  = src->width;
    map->height = src->height;

    err = av_frame_copy(map, src);
    જો (err)
        જાઓ fail;

    err = vt_pixbuf_set_attachments(hwfc, (CVPixelBufferRef)dst->data[3], src);
    જો (err)
        જાઓ fail;

    err = 0;
fail:
    av_frame_free(&map);
    પાછા err;
}

સ્થિર પૂર્ણાંક vt_map_from(AVHWFramesContext *hwfc, AVFrame *dst,
                       અચલ AVFrame *src, પૂર્ણાંક flags)
{
    પૂર્ણાંક err;

    જો (dst->format == AV_PIX_FMT_NONE)
        dst->format = hwfc->sw_format;
    નહીંતર જો (dst->format != hwfc->sw_format)
        પાછા AVERROR(ENOSYS);

    err = vt_map_frame(hwfc, dst, src, flags);
    જો (err)
        પાછા err;

    dst->width  = src->width;
    dst->height = src->height;

    err = av_frame_copy_props(dst, src);
    જો (err)
        પાછા err;

    પાછા 0;
}

સ્થિર પૂર્ણાંક vt_device_create(AVHWDeviceContext *ctx, અચલ અક્ષર *device,
                            AVDictionary *opts, પૂર્ણાંક flags)
{
    જો (device && device[0]) {
        av_log(ctx, AV_LOG_ERROR, "Device selection unsupported.\n");
        પાછા AVERROR_UNKNOWN;
    }

    પાછા 0;
}

અચલ HWContextType ff_hwcontext_type_videotoolbox = {
    .type                 = AV_HWDEVICE_TYPE_VIDEOTOOLBOX,
    .name                 = "videotoolbox",

    .frames_hwctx_size    = કદ(VTFramesContext),

    .device_create        = vt_device_create,
    .frames_init          = vt_frames_init,
    .frames_get_buffer    = vt_get_buffer,
    .frames_get_constraints = vt_frames_get_constraints,
    .frames_uninit        = vt_frames_uninit,
    .transfer_get_formats = vt_transfer_get_formats,
    .transfer_data_to     = vt_transfer_data_to,
    .transfer_data_from   = vt_transfer_data_from,
    .map_from             = vt_map_from,

    .pix_fmts = (અચલ ગણના AVPixelFormat[]){ AV_PIX_FMT_VIDEOTOOLBOX, AV_PIX_FMT_NONE },
};
