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

void av_image_fill_max_pixsteps(ចំនួនគត់ max_pixsteps[4], ចំនួនគត់ max_pixstep_comps[4],
                                const AVPixFmtDescriptor *pixdesc)
{
    ចំនួនគត់ i;
    memset(max_pixsteps, 0, 4*parimaa_na(max_pixsteps[0]));
    ប្រសិនបើ (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*parimaa_na(max_pixstep_comps[0]));

    សម្រាប់ (i = 0; i < 4; i++) {
        const AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        ប្រសិនបើ (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            ប្រសិនបើ (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

static anta_hstha
ចំនួនគត់ image_get_linesize(ចំនួនគត់ width, ចំនួនគត់ plane,
                       ចំនួនគត់ max_step, ចំនួនគត់ max_step_comp,
                       const AVPixFmtDescriptor *desc)
{
    ចំនួនគត់ s, shifted_w, linesize;

    ប្រសិនបើ (!desc)
        ត្រឡប់ AVERROR(EINVAL);

    ប្រសិនបើ (width < 0)
        ត្រឡប់ AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    ប្រសិនបើ (shifted_w && max_step > INT_MAX / shifted_w)
        ត្រឡប់ AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    ប្រសិនបើ (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    ត្រឡប់ linesize;
}

ចំនួនគត់ av_image_get_linesize(ga_nanaa AVPixelFormat pix_fmt, ចំនួនគត់ width, ចំនួនគត់ plane)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ចំនួនគត់ max_step     [4];       /* max pixel step for each plane */
    ចំនួនគត់ max_step_comp[4];       /* the component for each plane which has the max pixel step */

    ប្រសិនបើ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ត្រឡប់ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    ត្រឡប់ image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

ចំនួនគត់ av_image_fill_linesizes(ចំនួនគត់ linesizes[4], ga_nanaa AVPixelFormat pix_fmt, ចំនួនគត់ width)
{
    ចំនួនគត់ i, ret;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ចំនួនគត់ max_step     [4];       /* max pixel step for each plane */
    ចំនួនគត់ max_step_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*parimaa_na(linesizes[0]));

    ប្រសិនបើ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ត្រឡប់ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    សម្រាប់ (i = 0; i < 4; i++) {
        ប្រសិនបើ ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            ត្រឡប់ ret;
        linesizes[i] = ret;
    }

    ត្រឡប់ 0;
}

ចំនួនគត់ av_image_fill_plane_sizes(size_t sizes[4], ga_nanaa AVPixelFormat pix_fmt,
                              ចំនួនគត់ height, const ptrdiff_t linesizes[4])
{
    ចំនួនគត់ i, has_plane[4] = { 0 };

    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, parimaa_na(sizes[0])*4);

    ប្រសិនបើ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ត្រឡប់ AVERROR(EINVAL);

    ប្រសិនបើ (linesizes[0] > SIZE_MAX / height)
        ត្រឡប់ AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)height;

    ប្រសិនបើ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        ត្រឡប់ 0;
    }

    សម្រាប់ (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    សម្រាប់ (i = 1; i < 4 && has_plane[i]; i++) {
        ចំនួនគត់ h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        ប្រសិនបើ (linesizes[i] > SIZE_MAX / h)
            ត្រឡប់ AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    ត្រឡប់ 0;
}

ចំនួនគត់ av_image_fill_pointers(uint8_t *data[4], ga_nanaa AVPixelFormat pix_fmt, ចំនួនគត់ height,
                           uint8_t *ptr, const ចំនួនគត់ linesizes[4])
{
    ចំនួនគត់ i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(data     , 0, parimaa_na(data[0])*4);

    សម្រាប់ (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    ret = 0;
    សម្រាប់ (i = 0; i < 4; i++) {
        ប្រសិនបើ (sizes[i] > INT_MAX - ret)
            ត្រឡប់ AVERROR(EINVAL);
        ret += sizes[i];
    }

    ប្រសិនបើ (!ptr)
        ត្រឡប់ ret;

    data[0] = ptr;
    សម្រាប់ (i = 1; i < 4 && sizes[i]; i++)
        data[i] = data[i - 1] + sizes[i - 1];

    ត្រឡប់ ret;
}

ចំនួនគត់ avpriv_set_systematic_pal2(uint32_t pal[256], ga_nanaa AVPixelFormat pix_fmt)
{
    ចំនួនគត់ i;

    សម្រាប់ (i = 0; i < 256; i++) {
        ចំនួនគត់ r, g, b;

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
            ត្រឡប់ AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    ត្រឡប់ 0;
}

ចំនួនគត់ av_image_alloc(uint8_t *pointers[4], ចំនួនគត់ linesizes[4],
                   ចំនួនគត់ w, ចំនួនគត់ h, ga_nanaa AVPixelFormat pix_fmt, ចំនួនគត់ align)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ចំនួនគត់ i, ret;
    ptrdiff_t linesizes1[4];
    size_t total_size, sizes[4];
    uint8_t *buf;

    ប្រសិនបើ (!desc)
        ត្រឡប់ AVERROR(EINVAL);

    ប្រសិនបើ ((ret = av_image_check_size(w, h, 0, NULL)) < 0)
        ត្រឡប់ ret;
    ប្រសិនបើ ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        ត្រឡប់ ret;

    សម្រាប់ (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    ប្រសិនបើ ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        ត្រឡប់ ret;
    total_size = align;
    សម្រាប់ (i = 0; i < 4; i++) {
        ប្រសិនបើ (total_size > SIZE_MAX - sizes[i])
            ត្រឡប់ AVERROR(EINVAL);
        total_size += sizes[i];
    }
    buf = av_malloc(total_size);
    ប្រសិនបើ (!buf)
        ត្រឡប់ AVERROR(ENOMEM);
    ប្រសិនបើ ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        ត្រឡប់ ret;
    }
    ប្រសិនបើ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        ប្រសិនបើ (align < 4) {
            av_log(NULL, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            ត្រឡប់ AVERROR(EINVAL);
        }
    }

    ប្រសិនបើ (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    ត្រឡប់ ret;
}

typedef sa_nracanaa ImgUtils {
    const AVClass *class;
    ចំនួនគត់   log_offset;
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

ចំនួនគត់ av_image_check_size2(unsigned ចំនួនគត់ w, unsigned ចំនួនគត់ h, int64_t max_pixels, ga_nanaa AVPixelFormat pix_fmt, ចំនួនគត់ log_offset, void *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    ប្រសិនបើ (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    ប្រសិនបើ (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= INT_MAX || stride*(h + 128ULL) >= INT_MAX) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        ត្រឡប់ AVERROR(EINVAL);
    }

    ប្រសិនបើ (max_pixels < INT64_MAX) {
        ប្រសិនបើ (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            ត្រឡប់ AVERROR(EINVAL);
        }
    }

    ត្រឡប់ 0;
}

ចំនួនគត់ av_image_check_size(unsigned ចំនួនគត់ w, unsigned ចំនួនគត់ h, ចំនួនគត់ log_offset, void *log_ctx)
{
    ត្រឡប់ av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

ចំនួនគត់ av_image_check_sar(unsigned ចំនួនគត់ w, unsigned ចំនួនគត់ h, AVRational sar)
{
    int64_t scaled_dim;

    ប្រសិនបើ (sar.den <= 0 || sar.num < 0)
        ត្រឡប់ AVERROR(EINVAL);

    ប្រសិនបើ (!sar.num || sar.num == sar.den)
        ត្រឡប់ 0;

    ប្រសិនបើ (sar.num < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.num, sar.den, AV_ROUND_ZERO);
    បើមិនដូច្នេះ
        scaled_dim = av_rescale_rnd(h, sar.den, sar.num, AV_ROUND_ZERO);

    ប្រសិនបើ (scaled_dim > 0)
        ត្រឡប់ 0;

    ត្រឡប់ AVERROR(EINVAL);
}

static void image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             const uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, ចំនួនគត់ height)
{
    ប្រសិនបើ (!dst || !src)
        ត្រឡប់;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    សម្រាប់ (;height > 0; height--) {
        memcpy(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

void av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 const uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, ចំនួនគត់ height)
{
    ចំនួនគត់ ret = -1;

#ប្រសិនបើ ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    ប្រសិនបើ (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

void av_image_copy_plane(uint8_t       *dst, ចំនួនគត់ dst_linesize,
                         const uint8_t *src, ចំនួនគត់ src_linesize,
                         ចំនួនគត់ bytewidth, ចំនួនគត់ height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

static void image_copy(uint8_t *const dst_data[4], const ptrdiff_t dst_linesizes[4],
                       const uint8_t *const src_data[4], const ptrdiff_t src_linesizes[4],
                       ga_nanaa AVPixelFormat pix_fmt, ចំនួនគត់ width, ចំនួនគត់ height,
                       void (*copy_plane)(uint8_t *, ptrdiff_t, const uint8_t *,
                                          ptrdiff_t, ptrdiff_t, ចំនួនគត់))
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    ប្រសិនបើ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ត្រឡប់;

    ប្រសិនបើ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_data[0], dst_linesizes[0],
                   src_data[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        ប្រសិនបើ ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_data[1] && src_data[1]))
            memcpy(dst_data[1], src_data[1], 4*256);
    } បើមិនដូច្នេះ {
        ចំនួនគត់ i, planes_nb = 0;

        សម្រាប់ (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        សម្រាប់ (i = 0; i < planes_nb; i++) {
            ចំនួនគត់ h = height;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, width, i);
            ប្រសិនបើ (bwidth < 0) {
                av_log(NULL, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                ត្រឡប់;
            }
            ប្រសិនបើ (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_data[i], dst_linesizes[i],
                       src_data[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

void av_image_copy(uint8_t *const dst_data[4], const ចំនួនគត់ dst_linesizes[4],
                   const uint8_t * const src_data[4], const ចំនួនគត់ src_linesizes[4],
                   ga_nanaa AVPixelFormat pix_fmt, ចំនួនគត់ width, ចំនួនគត់ height)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    ចំនួនគត់ i;

    សម្រាប់ (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

void av_image_copy_uc_from(uint8_t * const dst_data[4], const ptrdiff_t dst_linesizes[4],
                           const uint8_t * const src_data[4], const ptrdiff_t src_linesizes[4],
                           ga_nanaa AVPixelFormat pix_fmt, ចំនួនគត់ width, ចំនួនគត់ height)
{
    image_copy(dst_data, dst_linesizes, src_data, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

ចំនួនគត់ av_image_fill_arrays(uint8_t *dst_data[4], ចំនួនគត់ dst_linesize[4],
                         const uint8_t *src, ga_nanaa AVPixelFormat pix_fmt,
                         ចំនួនគត់ width, ចំនួនគត់ height, ចំនួនគត់ align)
{
    ចំនួនគត់ ret, i;

    ret = av_image_check_size(width, height, 0, NULL);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    សម្រាប់ (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    ត្រឡប់ av_image_fill_pointers(dst_data, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

ចំនួនគត់ av_image_get_buffer_size(ga_nanaa AVPixelFormat pix_fmt,
                             ចំនួនគត់ width, ចំនួនគត់ height, ចំនួនគត់ align)
{
    ចំនួនគត់ ret, i;
    ចំនួនគត់ linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ប្រសិនបើ (!desc)
        ត្រឡប់ AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, NULL);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    សម្រាប់ (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    ret = 0;
    សម្រាប់ (i = 0; i < 4; i++) {
        ប្រសិនបើ (sizes[i] > INT_MAX - ret)
            ត្រឡប់ AVERROR(EINVAL);
        ret += sizes[i];
    }
    ត្រឡប់ ret;
}

ចំនួនគត់ av_image_copy_to_buffer(uint8_t *dst, ចំនួនគត់ dst_size,
                            const uint8_t * const src_data[4],
                            const ចំនួនគត់ src_linesize[4],
                            ga_nanaa AVPixelFormat pix_fmt,
                            ចំនួនគត់ width, ចំនួនគត់ height, ចំនួនគត់ align)
{
    ចំនួនគត់ i, j, nb_planes = 0, linesize[4];
    ចំនួនគត់ size = av_image_get_buffer_size(pix_fmt, width, height, align);
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ចំនួនគត់ ret;

    ប្រសិនបើ (size > dst_size || size < 0 || !desc)
        ត្រឡប់ AVERROR(EINVAL);

    សម្រាប់ (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    សម្រាប់ (i = 0; i < nb_planes; i++) {
        ចំនួនគត់ h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        const uint8_t *src = src_data[i];
        h = AV_CEIL_RSHIFT(height, shift);

        សម្រាប់ (j = 0; j < h; j++) {
            memcpy(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    ប្រសិនបើ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        សម្រាប់ (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_data[1] + 4*i));
    }

    ត្រឡប់ size;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
static void memset_bytes(uint8_t *dst, size_t dst_size, uint8_t *clear,
                         size_t clear_size)
{
    ចំនួនគត់ same = 1;
    ចំនួនគត់ i;

    ប្រសិនបើ (!clear_size)
        ត្រឡប់;

    // Reduce to memset() if possible.
    សម្រាប់ (i = 0; i < clear_size; i++) {
        ប្រសិនបើ (clear[i] != clear[0]) {
            same = 0;
            bha_nga;
        }
    }
    ប្រសិនបើ (same)
        clear_size = 1;

    ប្រសិនបើ (clear_size == 1) {
        memset(dst, clear[0], dst_size);
    } បើមិនដូច្នេះ {
        ប្រសិនបើ (clear_size > dst_size)
            clear_size = dst_size;
        memcpy(dst, clear, clear_size);
        av_memcpy_backptr(dst + clear_size, clear_size, dst_size - clear_size);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_SIZE 32

ចំនួនគត់ av_image_fill_color(uint8_t * const dst_data[4], const ptrdiff_t dst_linesize[4],
                        ga_nanaa AVPixelFormat pix_fmt, const uint32_t color[4],
                        ចំនួនគត់ width, ចំនួនគត់ height, ចំនួនគត់ flags)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ចំនួនគត់ nb_planes = av_pix_fmt_count_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_SIZE] = {{0}}; // clear padding with 0
    ចំនួនគត់ clear_block_size[4] = {0};
    ptrdiff_t plane_line_bytes[4] = {0};
    ចំនួនគត់ bitstream;
    ចំនួនគត់ plane, c;

    ប្រសិនបើ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ត្រឡប់ AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    សម្រាប់ (c = 0; c < desc->nb_components; c++) {
        const AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_size[comp.plane] = FFMAX(clear_block_size[comp.plane], comp.step);

        ប្រសិនបើ (clear_block_size[comp.plane] > MAX_BLOCK_SIZE)
            ត្រឡប់ AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    សម្រាប់ (c = 0; c < desc->nb_components; c++) {
        const AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        ចំនួនគត់ w = (bitstream ? 8 : 1) * clear_block_size[comp.plane] / comp.step;
        uint8_t *c_data[4];
        const ចំនួនគត់ c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_SIZE];
        ចំនួនគត់ x;

        ប្រសិនបើ (comp.depth > 32)
            ត្រឡប់ AVERROR(EINVAL);
        ប្រសិនបើ (w < 1)
            ត្រឡប់ AVERROR(EINVAL);

        សម្រាប់ (x = 0; x < w; x++)
            src_array[x] = color[c];

        សម្រាប់ (x = 0; x < 4; x++)
            c_data[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_data, c_linesize, desc, 0, 0, c, w, 4);
    }

    សម្រាប់ (plane = 0; plane < nb_planes; plane++) {
        plane_line_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        ប្រសិនបើ (plane_line_bytes[plane] < 0)
            ត្រឡប់ AVERROR(EINVAL);
    }

    ប្រសិនបើ (!dst_data)
        ត្រឡប់ 0;

    សម្រាប់ (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_line_bytes[plane];
        uint8_t *data = dst_data[plane];
        ចំនួនគត់ chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        ចំនួនគត់ plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        សម្រាប់ (; plane_h > 0; plane_h--) {
            memset_bytes(data, bytewidth, &clear_block[plane][0], clear_block_size[plane]);
            data += dst_linesize[plane];
        }
    }

    ត្រឡប់ 0;
}

ចំនួនគត់ av_image_fill_black(uint8_t * const dst_data[4], const ptrdiff_t dst_linesize[4],
                        ga_nanaa AVPixelFormat pix_fmt, ga_nanaa AVColorRange range,
                        ចំនួនគត់ width, ចំនួនគត់ height)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ចំនួនគត់ nb_planes = av_pix_fmt_count_planes(pix_fmt);
    ចំនួនគត់ rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    ប្រសិនបើ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ត្រឡប់ AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    សម្រាប់ (ចំនួនគត់ c = 0; c < desc->nb_components; c++) {
        const AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        ប្រសិនបើ (comp.depth > 32)
            ត្រឡប់ AVERROR(EINVAL);

        ប្រសិនបើ (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } បើមិនដូច្នេះ ប្រសិនបើ (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            ប្រសិនបើ (fltp) {
                ប្រសិនបើ (comp.depth != 16 && comp.depth != 32)
                    ត្រឡប់ AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } បើមិនដូច្នេះ {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } បើមិនដូច្នេះ ប្រសិនបើ (c == 0 && limited && comp.depth > 1) {
            ប្រសិនបើ (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                ត្រឡប់ AVERROR(EINVAL);
            ប្រសិនបើ (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            បើមិនដូច្នេះ
                color = 16 << (comp.depth - 8);
        } បើមិនដូច្នេះ ប្រសិនបើ ((c == 1 || c == 2) && !rgb && !xyz) {
            ប្រសិនបើ (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                ត្រឡប់ AVERROR(EINVAL);
            ប្រសិនបើ (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            បើមិនដូច្នេះ
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    ត្រឡប់ av_image_fill_color(dst_data, dst_linesize, pix_fmt, colors, width, height, 0);
}
