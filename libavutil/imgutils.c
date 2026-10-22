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

ಶೂನ್ಯ av_image_fill_max_pixsteps(ಪೂರ್ಣಾಙ್ಕ max_pixsteps[4], ಪೂರ್ಣಾಙ್ಕ max_pixstep_comps[4],
                                ಧ್ರುವ AVPixFmtDescriptor *pixdesc)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    memset(max_pixsteps, 0, 4*ಪರಿಮಾಣ(max_pixsteps[0]));
    ಯದಿ (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*ಪರಿಮಾಣ(max_pixstep_comps[0]));

    ಪ್ರತಿ (i = 0; i < 4; i++) {
        ಧ್ರುವ AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        ಯದಿ (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            ಯದಿ (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ
ಪೂರ್ಣಾಙ್ಕ image_get_linesize(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ plane,
                       ಪೂರ್ಣಾಙ್ಕ max_step, ಪೂರ್ಣಾಙ್ಕ max_step_comp,
                       ಧ್ರುವ AVPixFmtDescriptor *desc)
{
    ಪೂರ್ಣಾಙ್ಕ s, shifted_w, linesize;

    ಯದಿ (!desc)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (width < 0)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    ಯದಿ (shifted_w && max_step > INT_MAX / shifted_w)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    ಯದಿ (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    ಪ್ರತ್ಯಾಗಮ linesize;
}

ಪೂರ್ಣಾಙ್ಕ av_image_get_linesize(ಗಣನಾ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ plane)
{
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಙ್ಕ max_step     [4];       /* max pixel step for each plane */
    ಪೂರ್ಣಾಙ್ಕ max_step_comp[4];       /* the component for each plane which has the max pixel step */

    ಯದಿ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    ಪ್ರತ್ಯಾಗಮ image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

ಪೂರ್ಣಾಙ್ಕ av_image_fill_linesizes(ಪೂರ್ಣಾಙ್ಕ linesizes[4], ಗಣನಾ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಙ್ಕ width)
{
    ಪೂರ್ಣಾಙ್ಕ i, ret;
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಙ್ಕ max_step     [4];       /* max pixel step for each plane */
    ಪೂರ್ಣಾಙ್ಕ max_step_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*ಪರಿಮಾಣ(linesizes[0]));

    ಯದಿ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    ಪ್ರತಿ (i = 0; i < 4; i++) {
        ಯದಿ ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
        linesizes[i] = ret;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_image_fill_plane_sizes(size_t sizes[4], ಗಣನಾ AVPixelFormat pix_fmt,
                              ಪೂರ್ಣಾಙ್ಕ height, ಧ್ರುವ ptrdiff_t linesizes[4])
{
    ಪೂರ್ಣಾಙ್ಕ i, has_plane[4] = { 0 };

    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, ಪರಿಮಾಣ(sizes[0])*4);

    ಯದಿ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (linesizes[0] > SIZE_MAX / height)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)height;

    ಯದಿ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಪ್ರತಿ (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    ಪ್ರತಿ (i = 1; i < 4 && has_plane[i]; i++) {
        ಪೂರ್ಣಾಙ್ಕ h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        ಯದಿ (linesizes[i] > SIZE_MAX / h)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_image_fill_pointers(uint8_t *data[4], ಗಣನಾ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಙ್ಕ height,
                           uint8_t *ptr, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ linesizes[4])
{
    ಪೂರ್ಣಾಙ್ಕ i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(data     , 0, ಪರಿಮಾಣ(data[0])*4);

    ಪ್ರತಿ (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ret = 0;
    ಪ್ರತಿ (i = 0; i < 4; i++) {
        ಯದಿ (sizes[i] > INT_MAX - ret)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        ret += sizes[i];
    }

    ಯದಿ (!ptr)
        ಪ್ರತ್ಯಾಗಮ ret;

    data[0] = ptr;
    ಪ್ರತಿ (i = 1; i < 4 && sizes[i]; i++)
        data[i] = data[i - 1] + sizes[i - 1];

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ avpriv_set_systematic_pal2(uint32_t pal[256], ಗಣನಾ AVPixelFormat pix_fmt)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < 256; i++) {
        ಪೂರ್ಣಾಙ್ಕ r, g, b;

        ವಿಕಲ್ಪ (pix_fmt) {
        ಪಕ್ಷ AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            ಭಙ್ಗ;
        ಪಕ್ಷ AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            ಭಙ್ಗ;
        ಪಕ್ಷ AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            ಭಙ್ಗ;
        ಪಕ್ಷ AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            ಭಙ್ಗ;
        ಪಕ್ಷ AV_PIX_FMT_GRAY8:
            r = b = g = i;
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_image_alloc(uint8_t *pointers[4], ಪೂರ್ಣಾಙ್ಕ linesizes[4],
                   ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, ಗಣನಾ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಙ್ಕ align)
{
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಙ್ಕ i, ret;
    ptrdiff_t linesizes1[4];
    size_t total_size, sizes[4];
    uint8_t *buf;

    ಯದಿ (!desc)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ ((ret = av_image_check_size(w, h, 0, ರಿಕ್ತ)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ಯದಿ ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಪ್ರತಿ (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    ಯದಿ ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    total_size = align;
    ಪ್ರತಿ (i = 0; i < 4; i++) {
        ಯದಿ (total_size > SIZE_MAX - sizes[i])
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        total_size += sizes[i];
    }
    buf = av_malloc(total_size);
    ಯದಿ (!buf)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    ಯದಿ ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        ಪ್ರತ್ಯಾಗಮ ret;
    }
    ಯದಿ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        ಯದಿ (align < 4) {
            av_log(ರಿಕ್ತ, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
    }

    ಯದಿ (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ImgUtils {
    ಧ್ರುವ AVClass *class;
    ಪೂರ್ಣಾಙ್ಕ   log_offset;
    ಶೂನ್ಯ *log_ctx;
} ImgUtils;

ಸ್ಥಿರ ಧ್ರುವ AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .item_name                 = av_default_item_name,
    .option                    = ರಿಕ್ತ,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(ImgUtils, log_offset),
    .parent_log_context_offset = offsetof(ImgUtils, log_ctx),
};

ಪೂರ್ಣಾಙ್ಕ av_image_check_size2(unsigned ಪೂರ್ಣಾಙ್ಕ w, unsigned ಪೂರ್ಣಾಙ್ಕ h, int64_t max_pixels, ಗಣನಾ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಙ್ಕ log_offset, ಶೂನ್ಯ *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    ಯದಿ (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    ಯದಿ (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= INT_MAX || stride*(h + 128ULL) >= INT_MAX) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    ಯದಿ (max_pixels < INT64_MAX) {
        ಯದಿ (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_image_check_size(unsigned ಪೂರ್ಣಾಙ್ಕ w, unsigned ಪೂರ್ಣಾಙ್ಕ h, ಪೂರ್ಣಾಙ್ಕ log_offset, ಶೂನ್ಯ *log_ctx)
{
    ಪ್ರತ್ಯಾಗಮ av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

ಪೂರ್ಣಾಙ್ಕ av_image_check_sar(unsigned ಪೂರ್ಣಾಙ್ಕ w, unsigned ಪೂರ್ಣಾಙ್ಕ h, AVRational sar)
{
    int64_t scaled_dim;

    ಯದಿ (sar.den <= 0 || sar.ಅಂಕೆ < 0)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (!sar.ಅಂಕೆ || sar.ಅಂಕೆ == sar.den)
        ಪ್ರತ್ಯಾಗಮ 0;

    ಯದಿ (sar.ಅಂಕೆ < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.ಅಂಕೆ, sar.den, AV_ROUND_ZERO);
    ಅನ್ಯಥಾ
        scaled_dim = av_rescale_rnd(h, sar.den, sar.ಅಂಕೆ, AV_ROUND_ZERO);

    ಯದಿ (scaled_dim > 0)
        ಪ್ರತ್ಯಾಗಮ 0;

    ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಶೂನ್ಯ image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             ಧ್ರುವ uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, ಪೂರ್ಣಾಙ್ಕ height)
{
    ಯದಿ (!dst || !src)
        ಪ್ರತ್ಯಾಗಮ;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    ಪ್ರತಿ (;height > 0; height--) {
        memcpy(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

ಶೂನ್ಯ av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 ಧ್ರುವ uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, ಪೂರ್ಣಾಙ್ಕ height)
{
    ಪೂರ್ಣಾಙ್ಕ ret = -1;

#ಯದಿ ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    ಯದಿ (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

ಶೂನ್ಯ av_image_copy_plane(uint8_t       *dst, ಪೂರ್ಣಾಙ್ಕ dst_linesize,
                         ಧ್ರುವ uint8_t *src, ಪೂರ್ಣಾಙ್ಕ src_linesize,
                         ಪೂರ್ಣಾಙ್ಕ bytewidth, ಪೂರ್ಣಾಙ್ಕ height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

ಸ್ಥಿರ ಶೂನ್ಯ image_copy(uint8_t *ಧ್ರುವ dst_data[4], ಧ್ರುವ ptrdiff_t dst_linesizes[4],
                       ಧ್ರುವ uint8_t *ಧ್ರುವ src_data[4], ಧ್ರುವ ptrdiff_t src_linesizes[4],
                       ಗಣನಾ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height,
                       ಶೂನ್ಯ (*copy_plane)(uint8_t *, ptrdiff_t, ಧ್ರುವ uint8_t *,
                                          ptrdiff_t, ptrdiff_t, ಪೂರ್ಣಾಙ್ಕ))
{
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    ಯದಿ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ಪ್ರತ್ಯಾಗಮ;

    ಯದಿ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_data[0], dst_linesizes[0],
                   src_data[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        ಯದಿ ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_data[1] && src_data[1]))
            memcpy(dst_data[1], src_data[1], 4*256);
    } ಅನ್ಯಥಾ {
        ಪೂರ್ಣಾಙ್ಕ i, planes_nb = 0;

        ಪ್ರತಿ (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        ಪ್ರತಿ (i = 0; i < planes_nb; i++) {
            ಪೂರ್ಣಾಙ್ಕ h = height;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, width, i);
            ಯದಿ (bwidth < 0) {
                av_log(ರಿಕ್ತ, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                ಪ್ರತ್ಯಾಗಮ;
            }
            ಯದಿ (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_data[i], dst_linesizes[i],
                       src_data[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

ಶೂನ್ಯ av_image_copy(uint8_t *ಧ್ರುವ dst_data[4], ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ dst_linesizes[4],
                   ಧ್ರುವ uint8_t * ಧ್ರುವ src_data[4], ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_linesizes[4],
                   ಗಣನಾ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

ಶೂನ್ಯ av_image_copy_uc_from(uint8_t * ಧ್ರುವ dst_data[4], ಧ್ರುವ ptrdiff_t dst_linesizes[4],
                           ಧ್ರುವ uint8_t * ಧ್ರುವ src_data[4], ಧ್ರುವ ptrdiff_t src_linesizes[4],
                           ಗಣನಾ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height)
{
    image_copy(dst_data, dst_linesizes, src_data, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

ಪೂರ್ಣಾಙ್ಕ av_image_fill_arrays(uint8_t *dst_data[4], ಪೂರ್ಣಾಙ್ಕ dst_linesize[4],
                         ಧ್ರುವ uint8_t *src, ಗಣನಾ AVPixelFormat pix_fmt,
                         ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಪೂರ್ಣಾಙ್ಕ align)
{
    ಪೂರ್ಣಾಙ್ಕ ret, i;

    ret = av_image_check_size(width, height, 0, ರಿಕ್ತ);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಪ್ರತಿ (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    ಪ್ರತ್ಯಾಗಮ av_image_fill_pointers(dst_data, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

ಪೂರ್ಣಾಙ್ಕ av_image_get_buffer_size(ಗಣನಾ AVPixelFormat pix_fmt,
                             ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಪೂರ್ಣಾಙ್ಕ align)
{
    ಪೂರ್ಣಾಙ್ಕ ret, i;
    ಪೂರ್ಣಾಙ್ಕ linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಯದಿ (!desc)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, ರಿಕ್ತ);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಪ್ರತಿ (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ret = 0;
    ಪ್ರತಿ (i = 0; i < 4; i++) {
        ಯದಿ (sizes[i] > INT_MAX - ret)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        ret += sizes[i];
    }
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_image_copy_to_buffer(uint8_t *dst, ಪೂರ್ಣಾಙ್ಕ dst_size,
                            ಧ್ರುವ uint8_t * ಧ್ರುವ src_data[4],
                            ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ src_linesize[4],
                            ಗಣನಾ AVPixelFormat pix_fmt,
                            ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಪೂರ್ಣಾಙ್ಕ align)
{
    ಪೂರ್ಣಾಙ್ಕ i, j, nb_planes = 0, linesize[4];
    ಪೂರ್ಣಾಙ್ಕ size = av_image_get_buffer_size(pix_fmt, width, height, align);
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (size > dst_size || size < 0 || !desc)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಪ್ರತಿ (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    ಪ್ರತಿ (i = 0; i < nb_planes; i++) {
        ಪೂರ್ಣಾಙ್ಕ h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        ಧ್ರುವ uint8_t *src = src_data[i];
        h = AV_CEIL_RSHIFT(height, shift);

        ಪ್ರತಿ (j = 0; j < h; j++) {
            memcpy(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    ಯದಿ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        ಪ್ರತಿ (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_data[1] + 4*i));
    }

    ಪ್ರತ್ಯಾಗಮ size;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
ಸ್ಥಿರ ಶೂನ್ಯ memset_bytes(uint8_t *dst, size_t dst_size, uint8_t *clear,
                         size_t clear_size)
{
    ಪೂರ್ಣಾಙ್ಕ same = 1;
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯದಿ (!clear_size)
        ಪ್ರತ್ಯಾಗಮ;

    // Reduce to memset() if possible.
    ಪ್ರತಿ (i = 0; i < clear_size; i++) {
        ಯದಿ (clear[i] != clear[0]) {
            same = 0;
            ಭಙ್ಗ;
        }
    }
    ಯದಿ (same)
        clear_size = 1;

    ಯದಿ (clear_size == 1) {
        memset(dst, clear[0], dst_size);
    } ಅನ್ಯಥಾ {
        ಯದಿ (clear_size > dst_size)
            clear_size = dst_size;
        memcpy(dst, clear, clear_size);
        av_memcpy_backptr(dst + clear_size, clear_size, dst_size - clear_size);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_SIZE 32

ಪೂರ್ಣಾಙ್ಕ av_image_fill_color(uint8_t * ಧ್ರುವ dst_data[4], ಧ್ರುವ ptrdiff_t dst_linesize[4],
                        ಗಣನಾ AVPixelFormat pix_fmt, ಧ್ರುವ uint32_t color[4],
                        ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಙ್ಕ nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_SIZE] = {{0}}; // clear padding with 0
    ಪೂರ್ಣಾಙ್ಕ clear_block_size[4] = {0};
    ptrdiff_t plane_ಸಾಲು_bytes[4] = {0};
    ಪೂರ್ಣಾಙ್ಕ bitstream;
    ಪೂರ್ಣಾಙ್ಕ plane, c;

    ಯದಿ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    ಪ್ರತಿ (c = 0; c < desc->nb_components; c++) {
        ಧ್ರುವ AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_size[comp.plane] = FFMAX(clear_block_size[comp.plane], comp.step);

        ಯದಿ (clear_block_size[comp.plane] > MAX_BLOCK_SIZE)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    ಪ್ರತಿ (c = 0; c < desc->nb_components; c++) {
        ಧ್ರುವ AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        ಪೂರ್ಣಾಙ್ಕ w = (bitstream ? 8 : 1) * clear_block_size[comp.plane] / comp.step;
        uint8_t *c_data[4];
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_SIZE];
        ಪೂರ್ಣಾಙ್ಕ x;

        ಯದಿ (comp.depth > 32)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        ಯದಿ (w < 1)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

        ಪ್ರತಿ (x = 0; x < w; x++)
            src_array[x] = color[c];

        ಪ್ರತಿ (x = 0; x < 4; x++)
            c_data[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_data, c_linesize, desc, 0, 0, c, w, 4);
    }

    ಪ್ರತಿ (plane = 0; plane < nb_planes; plane++) {
        plane_ಸಾಲು_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        ಯದಿ (plane_ಸಾಲು_bytes[plane] < 0)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    ಯದಿ (!dst_data)
        ಪ್ರತ್ಯಾಗಮ 0;

    ಪ್ರತಿ (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_ಸಾಲು_bytes[plane];
        uint8_t *data = dst_data[plane];
        ಪೂರ್ಣಾಙ್ಕ chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        ಪೂರ್ಣಾಙ್ಕ plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        ಪ್ರತಿ (; plane_h > 0; plane_h--) {
            memset_bytes(data, bytewidth, &clear_block[plane][0], clear_block_size[plane]);
            data += dst_linesize[plane];
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_image_fill_black(uint8_t * ಧ್ರುವ dst_data[4], ಧ್ರುವ ptrdiff_t dst_linesize[4],
                        ಗಣನಾ AVPixelFormat pix_fmt, ಗಣನಾ AVColorRange range,
                        ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height)
{
    ಧ್ರುವ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಙ್ಕ nb_planes = av_pix_fmt_ಎಣಿಕೆ_planes(pix_fmt);
    ಪೂರ್ಣಾಙ್ಕ rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    ಯದಿ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ c = 0; c < desc->nb_components; c++) {
        ಧ್ರುವ AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        ಯದಿ (comp.depth > 32)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

        ಯದಿ (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } ಅನ್ಯಥಾ ಯದಿ (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            ಯದಿ (fltp) {
                ಯದಿ (comp.depth != 16 && comp.depth != 32)
                    ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } ಅನ್ಯಥಾ {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } ಅನ್ಯಥಾ ಯದಿ (c == 0 && limited && comp.depth > 1) {
            ಯದಿ (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
            ಯದಿ (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            ಅನ್ಯಥಾ
                color = 16 << (comp.depth - 8);
        } ಅನ್ಯಥಾ ಯದಿ ((c == 1 || c == 2) && !rgb && !xyz) {
            ಯದಿ (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
            ಯದಿ (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            ಅನ್ಯಥಾ
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    ಪ್ರತ್ಯಾಗಮ av_image_fill_color(dst_data, dst_linesize, pix_fmt, colors, width, height, 0);
}
