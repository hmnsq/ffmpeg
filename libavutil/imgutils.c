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

/**
 * @file
 * misc image utilities
 */

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "imgutils.h"
#ಅನ್ತರ್ಭಾವ "imgutils_internal.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "mathematics.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "rational.h"

ಶೂನ್ಯ av_image_fill_max_pixsteps(ಪೂರ್ಣಾಂಕ max_pixsteps[4], ಪೂರ್ಣಾಂಕ max_pixstep_comps[4],
                                ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *pixdesc)
{
    ಪೂರ್ಣಾಂಕ i;
    memset(max_pixsteps, 0, 4*ಗಾತ್ರ(max_pixsteps[0]));
    ಆದರೆ (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*ಗಾತ್ರ(max_pixstep_comps[0]));

    ಗಾಗಿ (i = 0; i < 4; i++) {
        ಸ್ಥಿರಾಂಕ AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        ಆದರೆ (comp->ಹೆಜ್ಜೆ > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->ಹೆಜ್ಜೆ;
            ಆದರೆ (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ
ಪೂರ್ಣಾಂಕ image_get_linesize(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ plane,
                       ಪೂರ್ಣಾಂಕ max_ಹೆಜ್ಜೆ, ಪೂರ್ಣಾಂಕ max_ಹೆಜ್ಜೆ_comp,
                       ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc)
{
    ಪೂರ್ಣಾಂಕ s, shifted_w, linesize;

    ಆದರೆ (!desc)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (ಅಗಲ < 0)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    s = (max_ಹೆಜ್ಜೆ_comp == 1 || max_ಹೆಜ್ಜೆ_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(ಅಗಲ, s);
    ಆದರೆ (shifted_w && max_ಹೆಜ್ಜೆ > ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ / shifted_w)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    linesize = max_ಹೆಜ್ಜೆ * shifted_w;

    ಆದರೆ (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    ಹಿಂತಿರುಗಿ linesize;
}

ಪೂರ್ಣಾಂಕ av_image_get_linesize(ಎಣಿಕೆ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ plane)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಂಕ max_ಹೆಜ್ಜೆ     [4];       /* max pixel step for each plane */
    ಪೂರ್ಣಾಂಕ max_ಹೆಜ್ಜೆ_comp[4];       /* the component for each plane which has the max pixel step */

    ಆದರೆ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_ಹೆಜ್ಜೆ, max_ಹೆಜ್ಜೆ_comp, desc);
    ಹಿಂತಿರುಗಿ image_get_linesize(ಅಗಲ, plane, max_ಹೆಜ್ಜೆ[plane], max_ಹೆಜ್ಜೆ_comp[plane], desc);
}

ಪೂರ್ಣಾಂಕ av_image_fill_linesizes(ಪೂರ್ಣಾಂಕ linesizes[4], ಎಣಿಕೆ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಂಕ ಅಗಲ)
{
    ಪೂರ್ಣಾಂಕ i, ret;
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಂಕ max_ಹೆಜ್ಜೆ     [4];       /* max pixel step for each plane */
    ಪೂರ್ಣಾಂಕ max_ಹೆಜ್ಜೆ_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*ಗಾತ್ರ(linesizes[0]));

    ಆದರೆ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_ಹೆಜ್ಜೆ, max_ಹೆಜ್ಜೆ_comp, desc);
    ಗಾಗಿ (i = 0; i < 4; i++) {
        ಆದರೆ ((ret = image_get_linesize(ಅಗಲ, i, max_ಹೆಜ್ಜೆ[i], max_ಹೆಜ್ಜೆ_comp[i], desc)) < 0)
            ಹಿಂತಿರುಗಿ ret;
        linesizes[i] = ret;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_image_fill_plane_sizes(size_t sizes[4], ಎಣಿಕೆ AVPixelFormat pix_fmt,
                              ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಸ್ಥಿರಾಂಕ ptrdiff_t linesizes[4])
{
    ಪೂರ್ಣಾಂಕ i, has_plane[4] = { 0 };

    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, ಗಾತ್ರ(sizes[0])*4);

    ಆದರೆ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (linesizes[0] > SIZE_MAX / ಎತ್ತರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)ಎತ್ತರ;

    ಆದರೆ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        ಹಿಂತಿರುಗಿ 0;
    }

    ಗಾಗಿ (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    ಗಾಗಿ (i = 1; i < 4 && has_plane[i]; i++) {
        ಪೂರ್ಣಾಂಕ h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(ಎತ್ತರ, s);
        ಆದರೆ (linesizes[i] > SIZE_MAX / h)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_image_fill_ಸೂಚಕಗಳು(uint8_t *ದತ್ತಾಂಶ[4], ಎಣಿಕೆ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                           uint8_t *ptr, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ linesizes[4])
{
    ಪೂರ್ಣಾಂಕ i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(ದತ್ತಾಂಶ     , 0, ಗಾತ್ರ(ದತ್ತಾಂಶ[0])*4);

    ಗಾಗಿ (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, ಎತ್ತರ, linesizes1);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ret = 0;
    ಗಾಗಿ (i = 0; i < 4; i++) {
        ಆದರೆ (sizes[i] > ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ - ret)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        ret += sizes[i];
    }

    ಆದರೆ (!ptr)
        ಹಿಂತಿರುಗಿ ret;

    ದತ್ತಾಂಶ[0] = ptr;
    ಗಾಗಿ (i = 1; i < 4 && sizes[i]; i++)
        ದತ್ತಾಂಶ[i] = ದತ್ತಾಂಶ[i - 1] + sizes[i - 1];

    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ avpriv_ಗಣ_systematic_pal2(uint32_t pal[256], ಎಣಿಕೆ AVPixelFormat pix_fmt)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < 256; i++) {
        ಪೂರ್ಣಾಂಕ r, g, b;

        ಆಯ್ಕೆ (pix_fmt) {
        ಸ್ಥಿತಿ AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ AV_PIX_FMT_GRAY8:
            r = b = g = i;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_image_alloc(uint8_t *ಸೂಚಕಗಳು[4], ಪೂರ್ಣಾಂಕ linesizes[4],
                   ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಎಣಿಕೆ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಂಕ align)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಂಕ i, ret;
    ptrdiff_t linesizes1[4];
    size_t ಒಟ್ಟು_ಗಾತ್ರ, sizes[4];
    uint8_t *buf;

    ಆದರೆ (!desc)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ ((ret = av_image_check_ಗಾತ್ರ(w, h, 0, ಖಾಲಿ)) < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಆದರೆ ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಗಾಗಿ (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    ಆದರೆ ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಒಟ್ಟು_ಗಾತ್ರ = align;
    ಗಾಗಿ (i = 0; i < 4; i++) {
        ಆದರೆ (ಒಟ್ಟು_ಗಾತ್ರ > SIZE_MAX - sizes[i])
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        ಒಟ್ಟು_ಗಾತ್ರ += sizes[i];
    }
    buf = av_malloc(ಒಟ್ಟು_ಗಾತ್ರ);
    ಆದರೆ (!buf)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    ಆದರೆ ((ret = av_image_fill_ಸೂಚಕಗಳು(ಸೂಚಕಗಳು, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        ಹಿಂತಿರುಗಿ ret;
    }
    ಆದರೆ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_ಗಣ_systematic_pal2((uint32_t*)ಸೂಚಕಗಳು[1], pix_fmt);
        ಆದರೆ (align < 4) {
            av_log(ಖಾಲಿ, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
    }

    ಆದರೆ (desc->flags & AV_PIX_FMT_FLAG_PAL && ಸೂಚಕಗಳು[1] &&
        ಸೂಚಕಗಳು[1] - ಸೂಚಕಗಳು[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(ಸೂಚಕಗಳು[0] + linesizes[0] * h, 0,
               ಸೂಚಕಗಳು[1] - ಸೂಚಕಗಳು[0] - linesizes[0] * h);
    }

    ಹಿಂತಿರುಗಿ ret;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ImgUtils {
    ಸ್ಥಿರಾಂಕ AVClass *class;
    ಪೂರ್ಣಾಂಕ   log_ಸ್ಥಾನಾಂತರ;
    ಶೂನ್ಯ *log_ctx;
} ImgUtils;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .ಅಂಶ_name                 = av_default_ಅಂಶ_name,
    .option                    = ಖಾಲಿ,
    .ಆವೃತ್ತಿ                   = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .log_level_ಸ್ಥಾನಾಂತರ_ಸ್ಥಾನಾಂತರ   = offsetof(ImgUtils, log_ಸ್ಥಾನಾಂತರ),
    .ಪೋಷಕ_log_context_ಸ್ಥಾನಾಂತರ = offsetof(ImgUtils, log_ctx),
};

ಪೂರ್ಣಾಂಕ av_image_check_size2(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ w, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ h, int64_t max_pixels, ಎಣಿಕೆ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಂಕ log_ಸ್ಥಾನಾಂತರ, ಶೂನ್ಯ *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_ಸ್ಥಾನಾಂತರ = log_ಸ್ಥಾನಾಂತರ,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    ಆದರೆ (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    ಆದರೆ (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ || stride*(h + 128ULL) >= ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ಆದರೆ (max_pixels < INT64_MAX) {
        ಆದರೆ (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_image_check_ಗಾತ್ರ(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ w, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ log_ಸ್ಥಾನಾಂತರ, ಶೂನ್ಯ *log_ctx)
{
    ಹಿಂತಿರುಗಿ av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_ಸ್ಥಾನಾಂತರ, log_ctx);
}

ಪೂರ್ಣಾಂಕ av_image_check_sar(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ w, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ h, AVRational sar)
{
    int64_t scaled_dim;

    ಆದರೆ (sar.den <= 0 || sar.ಅಂಕೆ < 0)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (!sar.ಅಂಕೆ || sar.ಅಂಕೆ == sar.den)
        ಹಿಂತಿರುಗಿ 0;

    ಆದರೆ (sar.ಅಂಕೆ < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.ಅಂಕೆ, sar.den, AV_ಸುತ್ತು_ZERO);
    ಇಲ್ಲದಿದ್ದರೆ
        scaled_dim = av_rescale_rnd(h, sar.den, sar.ಅಂಕೆ, AV_ಸುತ್ತು_ZERO);

    ಆದರೆ (scaled_dim > 0)
        ಹಿಂತಿರುಗಿ 0;

    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಶೂನ್ಯ image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             ಸ್ಥಿರಾಂಕ uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, ಪೂರ್ಣಾಂಕ ಎತ್ತರ)
{
    ಆದರೆ (!dst || !src)
        ಹಿಂತಿರುಗಿ;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    ಗಾಗಿ (;ಎತ್ತರ > 0; ಎತ್ತರ--) {
        ಸ್ಮರಣೆ_ನಕಲು(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

ಶೂನ್ಯ av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 ಸ್ಥಿರಾಂಕ uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, ಪೂರ್ಣಾಂಕ ಎತ್ತರ)
{
    ಪೂರ್ಣಾಂಕ ret = -1;

#ಆದರೆ ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, ಎತ್ತರ);
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, ಎತ್ತರ);
}

ಶೂನ್ಯ av_image_copy_plane(uint8_t       *dst, ಪೂರ್ಣಾಂಕ dst_linesize,
                         ಸ್ಥಿರಾಂಕ uint8_t *src, ಪೂರ್ಣಾಂಕ src_linesize,
                         ಪೂರ್ಣಾಂಕ bytewidth, ಪೂರ್ಣಾಂಕ ಎತ್ತರ)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, ಎತ್ತರ);
}

ಸ್ಥಿರ ಶೂನ್ಯ image_copy(uint8_t *ಸ್ಥಿರಾಂಕ dst_ದತ್ತಾಂಶ[4], ಸ್ಥಿರಾಂಕ ptrdiff_t dst_linesizes[4],
                       ಸ್ಥಿರಾಂಕ uint8_t *ಸ್ಥಿರಾಂಕ src_ದತ್ತಾಂಶ[4], ಸ್ಥಿರಾಂಕ ptrdiff_t src_linesizes[4],
                       ಎಣಿಕೆ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                       ಶೂನ್ಯ (*copy_plane)(uint8_t *, ptrdiff_t, ಸ್ಥಿರಾಂಕ uint8_t *,
                                          ptrdiff_t, ptrdiff_t, ಪೂರ್ಣಾಂಕ))
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    ಆದರೆ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ಹಿಂತಿರುಗಿ;

    ಆದರೆ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_ದತ್ತಾಂಶ[0], dst_linesizes[0],
                   src_ದತ್ತಾಂಶ[0], src_linesizes[0],
                   ಅಗಲ, ಎತ್ತರ);
        /* copy the palette */
        ಆದರೆ ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_ದತ್ತಾಂಶ[1] && src_ದತ್ತಾಂಶ[1]))
            ಸ್ಮರಣೆ_ನಕಲು(dst_ದತ್ತಾಂಶ[1], src_ದತ್ತಾಂಶ[1], 4*256);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಪೂರ್ಣಾಂಕ i, planes_nb = 0;

        ಗಾಗಿ (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        ಗಾಗಿ (i = 0; i < planes_nb; i++) {
            ಪೂರ್ಣಾಂಕ h = ಎತ್ತರ;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, ಅಗಲ, i);
            ಆದರೆ (bwidth < 0) {
                av_log(ಖಾಲಿ, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                ಹಿಂತಿರುಗಿ;
            }
            ಆದರೆ (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(ಎತ್ತರ, desc->log2_chroma_h);
            }
            copy_plane(dst_ದತ್ತಾಂಶ[i], dst_linesizes[i],
                       src_ದತ್ತಾಂಶ[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

ಶೂನ್ಯ av_image_copy(uint8_t *ಸ್ಥಿರಾಂಕ dst_ದತ್ತಾಂಶ[4], ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_linesizes[4],
                   ಸ್ಥಿರಾಂಕ uint8_t * ಸ್ಥಿರಾಂಕ src_ದತ್ತಾಂಶ[4], ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_linesizes[4],
                   ಎಣಿಕೆ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_ದತ್ತಾಂಶ, dst_linesizes1, src_ದತ್ತಾಂಶ, src_linesizes1, pix_fmt,
               ಅಗಲ, ಎತ್ತರ, image_copy_plane);
}

ಶೂನ್ಯ av_image_copy_uc_from(uint8_t * ಸ್ಥಿರಾಂಕ dst_ದತ್ತಾಂಶ[4], ಸ್ಥಿರಾಂಕ ptrdiff_t dst_linesizes[4],
                           ಸ್ಥಿರಾಂಕ uint8_t * ಸ್ಥಿರಾಂಕ src_ದತ್ತಾಂಶ[4], ಸ್ಥಿರಾಂಕ ptrdiff_t src_linesizes[4],
                           ಎಣಿಕೆ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ)
{
    image_copy(dst_ದತ್ತಾಂಶ, dst_linesizes, src_ದತ್ತಾಂಶ, src_linesizes, pix_fmt,
               ಅಗಲ, ಎತ್ತರ, av_image_copy_plane_uc_from);
}

ಪೂರ್ಣಾಂಕ av_image_fill_arrays(uint8_t *dst_ದತ್ತಾಂಶ[4], ಪೂರ್ಣಾಂಕ dst_linesize[4],
                         ಸ್ಥಿರಾಂಕ uint8_t *src, ಎಣಿಕೆ AVPixelFormat pix_fmt,
                         ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಪೂರ್ಣಾಂಕ align)
{
    ಪೂರ್ಣಾಂಕ ret, i;

    ret = av_image_check_ಗಾತ್ರ(ಅಗಲ, ಎತ್ತರ, 0, ಖಾಲಿ);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, ಅಗಲ);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಗಾಗಿ (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    ಹಿಂತಿರುಗಿ av_image_fill_ಸೂಚಕಗಳು(dst_ದತ್ತಾಂಶ, pix_fmt, ಎತ್ತರ, (uint8_t *)src, dst_linesize);
}

ಪೂರ್ಣಾಂಕ av_image_get_ಬಫರ್_ಗಾತ್ರ(ಎಣಿಕೆ AVPixelFormat pix_fmt,
                             ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಪೂರ್ಣಾಂಕ align)
{
    ಪೂರ್ಣಾಂಕ ret, i;
    ಪೂರ್ಣಾಂಕ linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಆದರೆ (!desc)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ret = av_image_check_ಗಾತ್ರ(ಅಗಲ, ಎತ್ತರ, 0, ಖಾಲಿ);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, ಅಗಲ);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಗಾಗಿ (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, ಎತ್ತರ, aligned_linesize);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ret = 0;
    ಗಾಗಿ (i = 0; i < 4; i++) {
        ಆದರೆ (sizes[i] > ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ - ret)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        ret += sizes[i];
    }
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_image_copy_ಗಮ್ಯ_ಬಫರ್(uint8_t *dst, ಪೂರ್ಣಾಂಕ dst_ಗಾತ್ರ,
                            ಸ್ಥಿರಾಂಕ uint8_t * ಸ್ಥಿರಾಂಕ src_ದತ್ತಾಂಶ[4],
                            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_linesize[4],
                            ಎಣಿಕೆ AVPixelFormat pix_fmt,
                            ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಪೂರ್ಣಾಂಕ align)
{
    ಪೂರ್ಣಾಂಕ i, j, nb_planes = 0, linesize[4];
    ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 = av_image_get_ಬಫರ್_ಗಾತ್ರ(pix_fmt, ಅಗಲ, ಎತ್ತರ, align);
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (ಗಾತ್ರ_2 > dst_ಗಾತ್ರ || ಗಾತ್ರ_2 < 0 || !desc)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಗಾಗಿ (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, ಅಗಲ);
    av_assert0(ret >= 0); // was checked previously

    ಗಾಗಿ (i = 0; i < nb_planes; i++) {
        ಪೂರ್ಣಾಂಕ h, ಸರಿಸು = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        ಸ್ಥಿರಾಂಕ uint8_t *src = src_ದತ್ತಾಂಶ[i];
        h = AV_CEIL_RSHIFT(ಎತ್ತರ, ಸರಿಸು);

        ಗಾಗಿ (j = 0; j < h; j++) {
            ಸ್ಮರಣೆ_ನಕಲು(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    ಆದರೆ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        ಗಾಗಿ (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_ದತ್ತಾಂಶ[1] + 4*i));
    }

    ಹಿಂತಿರುಗಿ ಗಾತ್ರ_2;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
ಸ್ಥಿರ ಶೂನ್ಯ memset_ಬೈಟುಗಳು(uint8_t *dst, size_t dst_ಗಾತ್ರ, uint8_t *clear,
                         size_t clear_ಗಾತ್ರ)
{
    ಪೂರ್ಣಾಂಕ same = 1;
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (!clear_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ;

    // Reduce to memset() if possible.
    ಗಾಗಿ (i = 0; i < clear_ಗಾತ್ರ; i++) {
        ಆದರೆ (clear[i] != clear[0]) {
            same = 0;
            ನಿಲ್ಲಿಸು;
        }
    }
    ಆದರೆ (same)
        clear_ಗಾತ್ರ = 1;

    ಆದರೆ (clear_ಗಾತ್ರ == 1) {
        memset(dst, clear[0], dst_ಗಾತ್ರ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (clear_ಗಾತ್ರ > dst_ಗಾತ್ರ)
            clear_ಗಾತ್ರ = dst_ಗಾತ್ರ;
        ಸ್ಮರಣೆ_ನಕಲು(dst, clear, clear_ಗಾತ್ರ);
        av_memcpy_backptr(dst + clear_ಗಾತ್ರ, clear_ಗಾತ್ರ, dst_ಗಾತ್ರ - clear_ಗಾತ್ರ);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_ಖಂಡ_ಗಾತ್ರ 32

ಪೂರ್ಣಾಂಕ av_image_fill_color(uint8_t * ಸ್ಥಿರಾಂಕ dst_ದತ್ತಾಂಶ[4], ಸ್ಥಿರಾಂಕ ptrdiff_t dst_linesize[4],
                        ಎಣಿಕೆ AVPixelFormat pix_fmt, ಸ್ಥಿರಾಂಕ uint32_t color[4],
                        ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಪೂರ್ಣಾಂಕ flags)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಂಕ nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_ಖಂಡ[4][MAX_ಖಂಡ_ಗಾತ್ರ] = {{0}}; // clear padding with 0
    ಪೂರ್ಣಾಂಕ clear_ಖಂಡ_ಗಾತ್ರ[4] = {0};
    ptrdiff_t plane_ಸಾಲು_ಬೈಟುಗಳು[4] = {0};
    ಪೂರ್ಣಾಂಕ bitstream;
    ಪೂರ್ಣಾಂಕ plane, c;

    ಆದರೆ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    ಗಾಗಿ (c = 0; c < desc->nb_components; c++) {
        ಸ್ಥಿರಾಂಕ AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_ಖಂಡ_ಗಾತ್ರ[comp.plane] = FFMAX(clear_ಖಂಡ_ಗಾತ್ರ[comp.plane], comp.ಹೆಜ್ಜೆ);

        ಆದರೆ (clear_ಖಂಡ_ಗಾತ್ರ[comp.plane] > MAX_ಖಂಡ_ಗಾತ್ರ)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    ಗಾಗಿ (c = 0; c < desc->nb_components; c++) {
        ಸ್ಥಿರಾಂಕ AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        ಪೂರ್ಣಾಂಕ w = (bitstream ? 8 : 1) * clear_ಖಂಡ_ಗಾತ್ರ[comp.plane] / comp.ಹೆಜ್ಜೆ;
        uint8_t *c_ದತ್ತಾಂಶ[4];
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ c_linesize[4] = {0};
        uint32_t src_array[MAX_ಖಂಡ_ಗಾತ್ರ];
        ಪೂರ್ಣಾಂಕ x;

        ಆದರೆ (comp.ಆಳ > 32)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        ಆದರೆ (w < 1)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

        ಗಾಗಿ (x = 0; x < w; x++)
            src_array[x] = color[c];

        ಗಾಗಿ (x = 0; x < 4; x++)
            c_ದತ್ತಾಂಶ[x] = &clear_ಖಂಡ[x][0];

        av_write_image_line2(src_array, c_ದತ್ತಾಂಶ, c_linesize, desc, 0, 0, c, w, 4);
    }

    ಗಾಗಿ (plane = 0; plane < nb_planes; plane++) {
        plane_ಸಾಲು_ಬೈಟುಗಳು[plane] = av_image_get_linesize(pix_fmt, ಅಗಲ, plane);
        ಆದರೆ (plane_ಸಾಲು_ಬೈಟುಗಳು[plane] < 0)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ಆದರೆ (!dst_ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ 0;

    ಗಾಗಿ (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_ಸಾಲು_ಬೈಟುಗಳು[plane];
        uint8_t *ದತ್ತಾಂಶ = dst_ದತ್ತಾಂಶ[plane];
        ಪೂರ್ಣಾಂಕ chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        ಪೂರ್ಣಾಂಕ plane_h = AV_CEIL_RSHIFT(ಎತ್ತರ, chroma_div);

        ಗಾಗಿ (; plane_h > 0; plane_h--) {
            memset_ಬೈಟುಗಳು(ದತ್ತಾಂಶ, bytewidth, &clear_ಖಂಡ[plane][0], clear_ಖಂಡ_ಗಾತ್ರ[plane]);
            ದತ್ತಾಂಶ += dst_linesize[plane];
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_image_fill_black(uint8_t * ಸ್ಥಿರಾಂಕ dst_ದತ್ತಾಂಶ[4], ಸ್ಥಿರಾಂಕ ptrdiff_t dst_linesize[4],
                        ಎಣಿಕೆ AVPixelFormat pix_fmt, ಎಣಿಕೆ AVColorRange range,
                        ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಂಕ nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(pix_fmt);
    ಪೂರ್ಣಾಂಕ rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    ಆದರೆ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c < desc->nb_components; c++) {
        ಸ್ಥಿರಾಂಕ AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        ಆದರೆ (comp.ಆಳ > 32)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

        ಆದರೆ (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            ಆದರೆ (fltp) {
                ಆದರೆ (comp.ಆಳ != 16 && comp.ಆಳ != 32)
                    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
                color = (comp.ಆಳ == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } ಇಲ್ಲದಿದ್ದರೆ {
                color = (comp.ಆಳ == 32 ? 0 : (1 << comp.ಆಳ)) - 1;
             }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (c == 0 && limited && comp.ಆಳ > 1) {
            ಆದರೆ (comp.ಆಳ < 8 || (fltp && comp.ಆಳ != 16 && comp.ಆಳ != 32))
                ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
            ಆದರೆ (fltp)
                color = (comp.ಆಳ == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            ಇಲ್ಲದಿದ್ದರೆ
                color = 16 << (comp.ಆಳ - 8);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((c == 1 || c == 2) && !rgb && !xyz) {
            ಆದರೆ (comp.ಆಳ < 8 || fltp && comp.ಆಳ != 16 && comp.ಆಳ != 32)
                ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
            ಆದರೆ (fltp)
                color = (comp.ಆಳ == 16 ? 0x3800 : 0x3F000000); // 0.5
            ಇಲ್ಲದಿದ್ದರೆ
                color = 128 << (comp.ಆಳ - 8);
        }

        colors[c] = color;
    }

    ಹಿಂತಿರುಗಿ av_image_fill_color(dst_ದತ್ತಾಂಶ, dst_linesize, pix_fmt, colors, ಅಗಲ, ಎತ್ತರ, 0);
}
