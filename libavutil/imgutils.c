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

#include "avassert.h"
#include "common.h"
#include "imgutils.h"
#include "imgutils_internal.h"
#include "intreadwrite.h"
#include "log.h"
#include "mathematics.h"
#include "mem.h"
#include "pixdesc.h"
#include "rational.h"

void av_image_fill_max_pixsteps(puur_naa_nka max_pixsteps[4], puur_naa_nka max_pixstep_comps[4],
                                const AVPixFmtDescriptor *pixdesc)
{
    puur_naa_nka i;
    memset(max_pixsteps, 0, 4*parimaa_na(max_pixsteps[0]));
    ꦪꦼꦤ꧀ (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*parimaa_na(max_pixstep_comps[0]));

    ꦏꦁꦒꦺꦴ (i = 0; i < 4; i++) {
        const AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        ꦪꦼꦤ꧀ (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            ꦪꦼꦤ꧀ (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

static anta_hstha
puur_naa_nka image_get_linesize(puur_naa_nka width, puur_naa_nka plane,
                       puur_naa_nka max_step, puur_naa_nka max_step_comp,
                       const AVPixFmtDescriptor *desc)
{
    puur_naa_nka s, shifted_w, linesize;

    ꦪꦼꦤ꧀ (!desc)
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦪꦼꦤ꧀ (width < 0)
        ꦮꦭꦶ AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    ꦪꦼꦤ꧀ (shifted_w && max_step > INT_MAX / shifted_w)
        ꦮꦭꦶ AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    ꦪꦼꦤ꧀ (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    ꦮꦭꦶ linesize;
}

puur_naa_nka av_image_get_linesize(ga_nanaa AVPixelFormat pix_fmt, puur_naa_nka width, puur_naa_nka plane)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    puur_naa_nka max_step     [4];       /* max pixel step for each plane */
    puur_naa_nka max_step_comp[4];       /* the component for each plane which has the max pixel step */

    ꦪꦼꦤ꧀ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ꦮꦭꦶ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    ꦮꦭꦶ image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

puur_naa_nka av_image_fill_linesizes(puur_naa_nka linesizes[4], ga_nanaa AVPixelFormat pix_fmt, puur_naa_nka width)
{
    puur_naa_nka i, ret;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    puur_naa_nka max_step     [4];       /* max pixel step for each plane */
    puur_naa_nka max_step_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*parimaa_na(linesizes[0]));

    ꦪꦼꦤ꧀ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ꦮꦭꦶ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    ꦏꦁꦒꦺꦴ (i = 0; i < 4; i++) {
        ꦪꦼꦤ꧀ ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            ꦮꦭꦶ ret;
        linesizes[i] = ret;
    }

    ꦮꦭꦶ 0;
}

puur_naa_nka av_image_fill_plane_sizes(size_t sizes[4], ga_nanaa AVPixelFormat pix_fmt,
                              puur_naa_nka height, const ptrdiff_t linesizes[4])
{
    puur_naa_nka i, has_plane[4] = { 0 };

    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, parimaa_na(sizes[0])*4);

    ꦪꦼꦤ꧀ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦪꦼꦤ꧀ (linesizes[0] > SIZE_MAX / height)
        ꦮꦭꦶ AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)height;

    ꦪꦼꦤ꧀ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        ꦮꦭꦶ 0;
    }

    ꦏꦁꦒꦺꦴ (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    ꦏꦁꦒꦺꦴ (i = 1; i < 4 && has_plane[i]; i++) {
        puur_naa_nka h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        ꦪꦼꦤ꧀ (linesizes[i] > SIZE_MAX / h)
            ꦮꦭꦶ AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    ꦮꦭꦶ 0;
}

puur_naa_nka av_image_fill_pointers(uint8_t *data[4], ga_nanaa AVPixelFormat pix_fmt, puur_naa_nka height,
                           uint8_t *ptr, const puur_naa_nka linesizes[4])
{
    puur_naa_nka i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(data     , 0, parimaa_na(data[0])*4);

    ꦏꦁꦒꦺꦴ (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    ꦪꦼꦤ꧀ (ret < 0)
        ꦮꦭꦶ ret;

    ret = 0;
    ꦏꦁꦒꦺꦴ (i = 0; i < 4; i++) {
        ꦪꦼꦤ꧀ (sizes[i] > INT_MAX - ret)
            ꦮꦭꦶ AVERROR(EINVAL);
        ret += sizes[i];
    }

    ꦪꦼꦤ꧀ (!ptr)
        ꦮꦭꦶ ret;

    data[0] = ptr;
    ꦏꦁꦒꦺꦴ (i = 1; i < 4 && sizes[i]; i++)
        data[i] = data[i - 1] + sizes[i - 1];

    ꦮꦭꦶ ret;
}

puur_naa_nka avpriv_set_systematic_pal2(uint32_t pal[256], ga_nanaa AVPixelFormat pix_fmt)
{
    puur_naa_nka i;

    ꦏꦁꦒꦺꦴ (i = 0; i < 256; i++) {
        puur_naa_nka r, g, b;

        switch (pix_fmt) {
        pak_sa AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            bha_nga;
        pak_sa AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            bha_nga;
        pak_sa AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            bha_nga;
        pak_sa AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            bha_nga;
        pak_sa AV_PIX_FMT_GRAY8:
            r = b = g = i;
            bha_nga;
        default:
            ꦮꦭꦶ AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    ꦮꦭꦶ 0;
}

puur_naa_nka av_image_alloc(uint8_t *pointers[4], puur_naa_nka linesizes[4],
                   puur_naa_nka w, puur_naa_nka h, ga_nanaa AVPixelFormat pix_fmt, puur_naa_nka align)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    puur_naa_nka i, ret;
    ptrdiff_t linesizes1[4];
    size_t total_size, sizes[4];
    uint8_t *buf;

    ꦪꦼꦤ꧀ (!desc)
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦪꦼꦤ꧀ ((ret = av_image_check_size(w, h, 0, NULL)) < 0)
        ꦮꦭꦶ ret;
    ꦪꦼꦤ꧀ ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        ꦮꦭꦶ ret;

    ꦏꦁꦒꦺꦴ (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    ꦪꦼꦤ꧀ ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        ꦮꦭꦶ ret;
    total_size = align;
    ꦏꦁꦒꦺꦴ (i = 0; i < 4; i++) {
        ꦪꦼꦤ꧀ (total_size > SIZE_MAX - sizes[i])
            ꦮꦭꦶ AVERROR(EINVAL);
        total_size += sizes[i];
    }
    buf = av_malloc(total_size);
    ꦪꦼꦤ꧀ (!buf)
        ꦮꦭꦶ AVERROR(ENOMEM);
    ꦪꦼꦤ꧀ ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        ꦮꦭꦶ ret;
    }
    ꦪꦼꦤ꧀ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        ꦪꦼꦤ꧀ (align < 4) {
            av_log(NULL, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            ꦮꦭꦶ AVERROR(EINVAL);
        }
    }

    ꦪꦼꦤ꧀ (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    ꦮꦭꦶ ret;
}

typedef sa_nracanaa ImgUtils {
    const AVClass *class;
    puur_naa_nka   log_offset;
    void *log_ctx;
} ImgUtils;

static const AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .item_name                 = av_default_item_name,
    .option                    = NULL,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(ImgUtils, log_offset),
    .parent_log_context_offset = offsetof(ImgUtils, log_ctx),
};

puur_naa_nka av_image_check_size2(unsigned puur_naa_nka w, unsigned puur_naa_nka h, int64_t max_pixels, ga_nanaa AVPixelFormat pix_fmt, puur_naa_nka log_offset, void *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    ꦪꦼꦤ꧀ (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    ꦪꦼꦤ꧀ (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= INT_MAX || stride*(h + 128ULL) >= INT_MAX) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        ꦮꦭꦶ AVERROR(EINVAL);
    }

    ꦪꦼꦤ꧀ (max_pixels < INT64_MAX) {
        ꦪꦼꦤ꧀ (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            ꦮꦭꦶ AVERROR(EINVAL);
        }
    }

    ꦮꦭꦶ 0;
}

puur_naa_nka av_image_check_size(unsigned puur_naa_nka w, unsigned puur_naa_nka h, puur_naa_nka log_offset, void *log_ctx)
{
    ꦮꦭꦶ av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

puur_naa_nka av_image_check_sar(unsigned puur_naa_nka w, unsigned puur_naa_nka h, AVRational sar)
{
    int64_t scaled_dim;

    ꦪꦼꦤ꧀ (sar.den <= 0 || sar.num < 0)
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦪꦼꦤ꧀ (!sar.num || sar.num == sar.den)
        ꦮꦭꦶ 0;

    ꦪꦼꦤ꧀ (sar.num < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.num, sar.den, AV_ROUND_ZERO);
    ꦭꦶꦪ
        scaled_dim = av_rescale_rnd(h, sar.den, sar.num, AV_ROUND_ZERO);

    ꦪꦼꦤ꧀ (scaled_dim > 0)
        ꦮꦭꦶ 0;

    ꦮꦭꦶ AVERROR(EINVAL);
}

static void image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             const uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, puur_naa_nka height)
{
    ꦪꦼꦤ꧀ (!dst || !src)
        ꦮꦭꦶ;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    ꦏꦁꦒꦺꦴ (;height > 0; height--) {
        memcpy(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

void av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 const uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, puur_naa_nka height)
{
    puur_naa_nka ret = -1;

#ꦪꦼꦤ꧀ ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    ꦪꦼꦤ꧀ (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

void av_image_copy_plane(uint8_t       *dst, puur_naa_nka dst_linesize,
                         const uint8_t *src, puur_naa_nka src_linesize,
                         puur_naa_nka bytewidth, puur_naa_nka height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

static void image_copy(uint8_t *const dst_data[4], const ptrdiff_t dst_linesizes[4],
                       const uint8_t *const src_data[4], const ptrdiff_t src_linesizes[4],
                       ga_nanaa AVPixelFormat pix_fmt, puur_naa_nka width, puur_naa_nka height,
                       void (*copy_plane)(uint8_t *, ptrdiff_t, const uint8_t *,
                                          ptrdiff_t, ptrdiff_t, puur_naa_nka))
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    ꦪꦼꦤ꧀ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ꦮꦭꦶ;

    ꦪꦼꦤ꧀ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_data[0], dst_linesizes[0],
                   src_data[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        ꦪꦼꦤ꧀ ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_data[1] && src_data[1]))
            memcpy(dst_data[1], src_data[1], 4*256);
    } ꦭꦶꦪ {
        puur_naa_nka i, planes_nb = 0;

        ꦏꦁꦒꦺꦴ (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        ꦏꦁꦒꦺꦴ (i = 0; i < planes_nb; i++) {
            puur_naa_nka h = height;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, width, i);
            ꦪꦼꦤ꧀ (bwidth < 0) {
                av_log(NULL, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                ꦮꦭꦶ;
            }
            ꦪꦼꦤ꧀ (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_data[i], dst_linesizes[i],
                       src_data[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

void av_image_copy(uint8_t *const dst_data[4], const puur_naa_nka dst_linesizes[4],
                   const uint8_t * const src_data[4], const puur_naa_nka src_linesizes[4],
                   ga_nanaa AVPixelFormat pix_fmt, puur_naa_nka width, puur_naa_nka height)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    puur_naa_nka i;

    ꦏꦁꦒꦺꦴ (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

void av_image_copy_uc_from(uint8_t * const dst_data[4], const ptrdiff_t dst_linesizes[4],
                           const uint8_t * const src_data[4], const ptrdiff_t src_linesizes[4],
                           ga_nanaa AVPixelFormat pix_fmt, puur_naa_nka width, puur_naa_nka height)
{
    image_copy(dst_data, dst_linesizes, src_data, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

puur_naa_nka av_image_fill_arrays(uint8_t *dst_data[4], puur_naa_nka dst_linesize[4],
                         const uint8_t *src, ga_nanaa AVPixelFormat pix_fmt,
                         puur_naa_nka width, puur_naa_nka height, puur_naa_nka align)
{
    puur_naa_nka ret, i;

    ret = av_image_check_size(width, height, 0, NULL);
    ꦪꦼꦤ꧀ (ret < 0)
        ꦮꦭꦶ ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    ꦪꦼꦤ꧀ (ret < 0)
        ꦮꦭꦶ ret;

    ꦏꦁꦒꦺꦴ (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    ꦮꦭꦶ av_image_fill_pointers(dst_data, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

puur_naa_nka av_image_get_buffer_size(ga_nanaa AVPixelFormat pix_fmt,
                             puur_naa_nka width, puur_naa_nka height, puur_naa_nka align)
{
    puur_naa_nka ret, i;
    puur_naa_nka linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ꦪꦼꦤ꧀ (!desc)
        ꦮꦭꦶ AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, NULL);
    ꦪꦼꦤ꧀ (ret < 0)
        ꦮꦭꦶ ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    ꦪꦼꦤ꧀ (ret < 0)
        ꦮꦭꦶ ret;

    ꦏꦁꦒꦺꦴ (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    ꦪꦼꦤ꧀ (ret < 0)
        ꦮꦭꦶ ret;

    ret = 0;
    ꦏꦁꦒꦺꦴ (i = 0; i < 4; i++) {
        ꦪꦼꦤ꧀ (sizes[i] > INT_MAX - ret)
            ꦮꦭꦶ AVERROR(EINVAL);
        ret += sizes[i];
    }
    ꦮꦭꦶ ret;
}

puur_naa_nka av_image_copy_to_buffer(uint8_t *dst, puur_naa_nka dst_size,
                            const uint8_t * const src_data[4],
                            const puur_naa_nka src_linesize[4],
                            ga_nanaa AVPixelFormat pix_fmt,
                            puur_naa_nka width, puur_naa_nka height, puur_naa_nka align)
{
    puur_naa_nka i, j, nb_planes = 0, linesize[4];
    puur_naa_nka size = av_image_get_buffer_size(pix_fmt, width, height, align);
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    puur_naa_nka ret;

    ꦪꦼꦤ꧀ (size > dst_size || size < 0 || !desc)
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦏꦁꦒꦺꦴ (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    ꦏꦁꦒꦺꦴ (i = 0; i < nb_planes; i++) {
        puur_naa_nka h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        const uint8_t *src = src_data[i];
        h = AV_CEIL_RSHIFT(height, shift);

        ꦏꦁꦒꦺꦴ (j = 0; j < h; j++) {
            memcpy(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    ꦪꦼꦤ꧀ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        ꦏꦁꦒꦺꦴ (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_data[1] + 4*i));
    }

    ꦮꦭꦶ size;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
static void memset_bytes(uint8_t *dst, size_t dst_size, uint8_t *clear,
                         size_t clear_size)
{
    puur_naa_nka same = 1;
    puur_naa_nka i;

    ꦪꦼꦤ꧀ (!clear_size)
        ꦮꦭꦶ;

    // Reduce to memset() if possible.
    ꦏꦁꦒꦺꦴ (i = 0; i < clear_size; i++) {
        ꦪꦼꦤ꧀ (clear[i] != clear[0]) {
            same = 0;
            bha_nga;
        }
    }
    ꦪꦼꦤ꧀ (same)
        clear_size = 1;

    ꦪꦼꦤ꧀ (clear_size == 1) {
        memset(dst, clear[0], dst_size);
    } ꦭꦶꦪ {
        ꦪꦼꦤ꧀ (clear_size > dst_size)
            clear_size = dst_size;
        memcpy(dst, clear, clear_size);
        av_memcpy_backptr(dst + clear_size, clear_size, dst_size - clear_size);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_SIZE 32

puur_naa_nka av_image_fill_color(uint8_t * const dst_data[4], const ptrdiff_t dst_linesize[4],
                        ga_nanaa AVPixelFormat pix_fmt, const uint32_t color[4],
                        puur_naa_nka width, puur_naa_nka height, puur_naa_nka flags)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    puur_naa_nka nb_planes = av_pix_fmt_count_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_SIZE] = {{0}}; // clear padding with 0
    puur_naa_nka clear_block_size[4] = {0};
    ptrdiff_t plane_line_bytes[4] = {0};
    puur_naa_nka bitstream;
    puur_naa_nka plane, c;

    ꦪꦼꦤ꧀ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ꦮꦭꦶ AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    ꦏꦁꦒꦺꦴ (c = 0; c < desc->nb_components; c++) {
        const AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_size[comp.plane] = FFMAX(clear_block_size[comp.plane], comp.step);

        ꦪꦼꦤ꧀ (clear_block_size[comp.plane] > MAX_BLOCK_SIZE)
            ꦮꦭꦶ AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    ꦏꦁꦒꦺꦴ (c = 0; c < desc->nb_components; c++) {
        const AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        puur_naa_nka w = (bitstream ? 8 : 1) * clear_block_size[comp.plane] / comp.step;
        uint8_t *c_data[4];
        const puur_naa_nka c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_SIZE];
        puur_naa_nka x;

        ꦪꦼꦤ꧀ (comp.depth > 32)
            ꦮꦭꦶ AVERROR(EINVAL);
        ꦪꦼꦤ꧀ (w < 1)
            ꦮꦭꦶ AVERROR(EINVAL);

        ꦏꦁꦒꦺꦴ (x = 0; x < w; x++)
            src_array[x] = color[c];

        ꦏꦁꦒꦺꦴ (x = 0; x < 4; x++)
            c_data[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_data, c_linesize, desc, 0, 0, c, w, 4);
    }

    ꦏꦁꦒꦺꦴ (plane = 0; plane < nb_planes; plane++) {
        plane_line_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        ꦪꦼꦤ꧀ (plane_line_bytes[plane] < 0)
            ꦮꦭꦶ AVERROR(EINVAL);
    }

    ꦪꦼꦤ꧀ (!dst_data)
        ꦮꦭꦶ 0;

    ꦏꦁꦒꦺꦴ (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_line_bytes[plane];
        uint8_t *data = dst_data[plane];
        puur_naa_nka chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        puur_naa_nka plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        ꦏꦁꦒꦺꦴ (; plane_h > 0; plane_h--) {
            memset_bytes(data, bytewidth, &clear_block[plane][0], clear_block_size[plane]);
            data += dst_linesize[plane];
        }
    }

    ꦮꦭꦶ 0;
}

puur_naa_nka av_image_fill_black(uint8_t * const dst_data[4], const ptrdiff_t dst_linesize[4],
                        ga_nanaa AVPixelFormat pix_fmt, ga_nanaa AVColorRange range,
                        puur_naa_nka width, puur_naa_nka height)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    puur_naa_nka nb_planes = av_pix_fmt_count_planes(pix_fmt);
    puur_naa_nka rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    ꦪꦼꦤ꧀ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ꦮꦭꦶ AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    ꦏꦁꦒꦺꦴ (puur_naa_nka c = 0; c < desc->nb_components; c++) {
        const AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        ꦪꦼꦤ꧀ (comp.depth > 32)
            ꦮꦭꦶ AVERROR(EINVAL);

        ꦪꦼꦤ꧀ (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } ꦭꦶꦪ ꦪꦼꦤ꧀ (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            ꦪꦼꦤ꧀ (fltp) {
                ꦪꦼꦤ꧀ (comp.depth != 16 && comp.depth != 32)
                    ꦮꦭꦶ AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } ꦭꦶꦪ {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } ꦭꦶꦪ ꦪꦼꦤ꧀ (c == 0 && limited && comp.depth > 1) {
            ꦪꦼꦤ꧀ (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                ꦮꦭꦶ AVERROR(EINVAL);
            ꦪꦼꦤ꧀ (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            ꦭꦶꦪ
                color = 16 << (comp.depth - 8);
        } ꦭꦶꦪ ꦪꦼꦤ꧀ ((c == 1 || c == 2) && !rgb && !xyz) {
            ꦪꦼꦤ꧀ (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                ꦮꦭꦶ AVERROR(EINVAL);
            ꦪꦼꦤ꧀ (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            ꦭꦶꦪ
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    ꦮꦭꦶ av_image_fill_color(dst_data, dst_linesize, pix_fmt, colors, width, height, 0);
}
