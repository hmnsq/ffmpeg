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

void av_image_fill_max_pixsteps(ціле max_pixsteps[4], ціле max_pixstep_comps[4],
                                const AVPixFmtDescriptor *pixdesc)
{
    ціле i;
    memset(max_pixsteps, 0, 4*sizeof(max_pixsteps[0]));
    якщо (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*sizeof(max_pixstep_comps[0]));

    для (i = 0; i < 4; i++) {
        const AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        якщо (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            якщо (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

static inline
ціле image_get_linesize(ціле width, ціле plane,
                       ціле max_step, ціле max_step_comp,
                       const AVPixFmtDescriptor *desc)
{
    ціле s, shifted_w, linesize;

    якщо (!desc)
        повернути AVERROR(EINVAL);

    якщо (width < 0)
        повернути AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    якщо (shifted_w && max_step > INT_MAX / shifted_w)
        повернути AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    якщо (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    повернути linesize;
}

ціле av_image_get_linesize(enum AVPixelFormat pix_fmt, ціле width, ціле plane)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ціле max_step     [4];       /* max pixel step for each plane */
    ціле max_step_comp[4];       /* the component for each plane which has the max pixel step */

    якщо (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        повернути AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    повернути image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

ціле av_image_fill_linesizes(ціле linesizes[4], enum AVPixelFormat pix_fmt, ціле width)
{
    ціле i, ret;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ціле max_step     [4];       /* max pixel step for each plane */
    ціле max_step_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*sizeof(linesizes[0]));

    якщо (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        повернути AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    для (i = 0; i < 4; i++) {
        якщо ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            повернути ret;
        linesizes[i] = ret;
    }

    повернути 0;
}

ціле av_image_fill_plane_sizes(size_t sizes[4], enum AVPixelFormat pix_fmt,
                              ціле height, const ptrdiff_t linesizes[4])
{
    ціле i, has_plane[4] = { 0 };

    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, sizeof(sizes[0])*4);

    якщо (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        повернути AVERROR(EINVAL);

    якщо (linesizes[0] > SIZE_MAX / height)
        повернути AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)height;

    якщо (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        повернути 0;
    }

    для (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    для (i = 1; i < 4 && has_plane[i]; i++) {
        ціле h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        якщо (linesizes[i] > SIZE_MAX / h)
            повернути AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    повернути 0;
}

ціле av_image_fill_pointers(uint8_t *data[4], enum AVPixelFormat pix_fmt, ціле height,
                           uint8_t *ptr, const ціле linesizes[4])
{
    ціле i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(data     , 0, sizeof(data[0])*4);

    для (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    якщо (ret < 0)
        повернути ret;

    ret = 0;
    для (i = 0; i < 4; i++) {
        якщо (sizes[i] > INT_MAX - ret)
            повернути AVERROR(EINVAL);
        ret += sizes[i];
    }

    якщо (!ptr)
        повернути ret;

    data[0] = ptr;
    для (i = 1; i < 4 && sizes[i]; i++)
        data[i] = data[i - 1] + sizes[i - 1];

    повернути ret;
}

ціле avpriv_set_systematic_pal2(uint32_t pal[256], enum AVPixelFormat pix_fmt)
{
    ціле i;

    для (i = 0; i < 256; i++) {
        ціле r, g, b;

        switch (pix_fmt) {
        case AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            break;
        case AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            break;
        case AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            break;
        case AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            break;
        case AV_PIX_FMT_GRAY8:
            r = b = g = i;
            break;
        default:
            повернути AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    повернути 0;
}

ціле av_image_alloc(uint8_t *pointers[4], ціле linesizes[4],
                   ціле w, ціле h, enum AVPixelFormat pix_fmt, ціле align)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ціле i, ret;
    ptrdiff_t linesizes1[4];
    size_t total_size, sizes[4];
    uint8_t *buf;

    якщо (!desc)
        повернути AVERROR(EINVAL);

    якщо ((ret = av_image_check_size(w, h, 0, NULL)) < 0)
        повернути ret;
    якщо ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        повернути ret;

    для (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    якщо ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        повернути ret;
    total_size = align;
    для (i = 0; i < 4; i++) {
        якщо (total_size > SIZE_MAX - sizes[i])
            повернути AVERROR(EINVAL);
        total_size += sizes[i];
    }
    buf = av_malloc(total_size);
    якщо (!buf)
        повернути AVERROR(ENOMEM);
    якщо ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        повернути ret;
    }
    якщо (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        якщо (align < 4) {
            av_log(NULL, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            повернути AVERROR(EINVAL);
        }
    }

    якщо (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    повернути ret;
}

typedef struct ImgUtils {
    const AVClass *class;
    ціле   log_offset;
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

ціле av_image_check_size2(unsigned ціле w, unsigned ціле h, int64_t max_pixels, enum AVPixelFormat pix_fmt, ціле log_offset, void *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    якщо (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    якщо (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= INT_MAX || stride*(h + 128ULL) >= INT_MAX) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        повернути AVERROR(EINVAL);
    }

    якщо (max_pixels < INT64_MAX) {
        якщо (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            повернути AVERROR(EINVAL);
        }
    }

    повернути 0;
}

ціле av_image_check_size(unsigned ціле w, unsigned ціле h, ціле log_offset, void *log_ctx)
{
    повернути av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

ціле av_image_check_sar(unsigned ціле w, unsigned ціле h, AVRational sar)
{
    int64_t scaled_dim;

    якщо (sar.den <= 0 || sar.num < 0)
        повернути AVERROR(EINVAL);

    якщо (!sar.num || sar.num == sar.den)
        повернути 0;

    якщо (sar.num < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.num, sar.den, AV_ROUND_ZERO);
    інакше
        scaled_dim = av_rescale_rnd(h, sar.den, sar.num, AV_ROUND_ZERO);

    якщо (scaled_dim > 0)
        повернути 0;

    повернути AVERROR(EINVAL);
}

static void image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             const uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, ціле height)
{
    якщо (!dst || !src)
        повернути;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    для (;height > 0; height--) {
        memcpy(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

void av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 const uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, ціле height)
{
    ціле ret = -1;

#якщо ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    якщо (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

void av_image_copy_plane(uint8_t       *dst, ціле dst_linesize,
                         const uint8_t *src, ціле src_linesize,
                         ціле bytewidth, ціле height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

static void image_copy(uint8_t *const dst_data[4], const ptrdiff_t dst_linesizes[4],
                       const uint8_t *const src_data[4], const ptrdiff_t src_linesizes[4],
                       enum AVPixelFormat pix_fmt, ціле width, ціле height,
                       void (*copy_plane)(uint8_t *, ptrdiff_t, const uint8_t *,
                                          ptrdiff_t, ptrdiff_t, ціле))
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    якщо (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        повернути;

    якщо (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_data[0], dst_linesizes[0],
                   src_data[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        якщо ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_data[1] && src_data[1]))
            memcpy(dst_data[1], src_data[1], 4*256);
    } інакше {
        ціле i, planes_nb = 0;

        для (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        для (i = 0; i < planes_nb; i++) {
            ціле h = height;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, width, i);
            якщо (bwidth < 0) {
                av_log(NULL, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                повернути;
            }
            якщо (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_data[i], dst_linesizes[i],
                       src_data[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

void av_image_copy(uint8_t *const dst_data[4], const ціле dst_linesizes[4],
                   const uint8_t * const src_data[4], const ціле src_linesizes[4],
                   enum AVPixelFormat pix_fmt, ціле width, ціле height)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    ціле i;

    для (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

void av_image_copy_uc_from(uint8_t * const dst_data[4], const ptrdiff_t dst_linesizes[4],
                           const uint8_t * const src_data[4], const ptrdiff_t src_linesizes[4],
                           enum AVPixelFormat pix_fmt, ціле width, ціле height)
{
    image_copy(dst_data, dst_linesizes, src_data, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

ціле av_image_fill_arrays(uint8_t *dst_data[4], ціле dst_linesize[4],
                         const uint8_t *src, enum AVPixelFormat pix_fmt,
                         ціле width, ціле height, ціле align)
{
    ціле ret, i;

    ret = av_image_check_size(width, height, 0, NULL);
    якщо (ret < 0)
        повернути ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    якщо (ret < 0)
        повернути ret;

    для (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    повернути av_image_fill_pointers(dst_data, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

ціле av_image_get_buffer_size(enum AVPixelFormat pix_fmt,
                             ціле width, ціле height, ціле align)
{
    ціле ret, i;
    ціле linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    якщо (!desc)
        повернути AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, NULL);
    якщо (ret < 0)
        повернути ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    якщо (ret < 0)
        повернути ret;

    для (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    якщо (ret < 0)
        повернути ret;

    ret = 0;
    для (i = 0; i < 4; i++) {
        якщо (sizes[i] > INT_MAX - ret)
            повернути AVERROR(EINVAL);
        ret += sizes[i];
    }
    повернути ret;
}

ціле av_image_copy_to_buffer(uint8_t *dst, ціле dst_size,
                            const uint8_t * const src_data[4],
                            const ціле src_linesize[4],
                            enum AVPixelFormat pix_fmt,
                            ціле width, ціле height, ціле align)
{
    ціле i, j, nb_planes = 0, linesize[4];
    ціле size = av_image_get_buffer_size(pix_fmt, width, height, align);
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ціле ret;

    якщо (size > dst_size || size < 0 || !desc)
        повернути AVERROR(EINVAL);

    для (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    для (i = 0; i < nb_planes; i++) {
        ціле h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        const uint8_t *src = src_data[i];
        h = AV_CEIL_RSHIFT(height, shift);

        для (j = 0; j < h; j++) {
            memcpy(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    якщо (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        для (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_data[1] + 4*i));
    }

    повернути size;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
static void memset_bytes(uint8_t *dst, size_t dst_size, uint8_t *clear,
                         size_t clear_size)
{
    ціле same = 1;
    ціле i;

    якщо (!clear_size)
        повернути;

    // Reduce to memset() if possible.
    для (i = 0; i < clear_size; i++) {
        якщо (clear[i] != clear[0]) {
            same = 0;
            break;
        }
    }
    якщо (same)
        clear_size = 1;

    якщо (clear_size == 1) {
        memset(dst, clear[0], dst_size);
    } інакше {
        якщо (clear_size > dst_size)
            clear_size = dst_size;
        memcpy(dst, clear, clear_size);
        av_memcpy_backptr(dst + clear_size, clear_size, dst_size - clear_size);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_SIZE 32

ціле av_image_fill_color(uint8_t * const dst_data[4], const ptrdiff_t dst_linesize[4],
                        enum AVPixelFormat pix_fmt, const uint32_t color[4],
                        ціле width, ціле height, ціле flags)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ціле nb_planes = av_pix_fmt_count_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_SIZE] = {{0}}; // clear padding with 0
    ціле clear_block_size[4] = {0};
    ptrdiff_t plane_line_bytes[4] = {0};
    ціле bitstream;
    ціле plane, c;

    якщо (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        повернути AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    для (c = 0; c < desc->nb_components; c++) {
        const AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_size[comp.plane] = FFMAX(clear_block_size[comp.plane], comp.step);

        якщо (clear_block_size[comp.plane] > MAX_BLOCK_SIZE)
            повернути AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    для (c = 0; c < desc->nb_components; c++) {
        const AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        ціле w = (bitstream ? 8 : 1) * clear_block_size[comp.plane] / comp.step;
        uint8_t *c_data[4];
        const ціле c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_SIZE];
        ціле x;

        якщо (comp.depth > 32)
            повернути AVERROR(EINVAL);
        якщо (w < 1)
            повернути AVERROR(EINVAL);

        для (x = 0; x < w; x++)
            src_array[x] = color[c];

        для (x = 0; x < 4; x++)
            c_data[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_data, c_linesize, desc, 0, 0, c, w, 4);
    }

    для (plane = 0; plane < nb_planes; plane++) {
        plane_line_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        якщо (plane_line_bytes[plane] < 0)
            повернути AVERROR(EINVAL);
    }

    якщо (!dst_data)
        повернути 0;

    для (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_line_bytes[plane];
        uint8_t *data = dst_data[plane];
        ціле chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        ціле plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        для (; plane_h > 0; plane_h--) {
            memset_bytes(data, bytewidth, &clear_block[plane][0], clear_block_size[plane]);
            data += dst_linesize[plane];
        }
    }

    повернути 0;
}

ціле av_image_fill_black(uint8_t * const dst_data[4], const ptrdiff_t dst_linesize[4],
                        enum AVPixelFormat pix_fmt, enum AVColorRange range,
                        ціле width, ціле height)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ціле nb_planes = av_pix_fmt_count_planes(pix_fmt);
    ціле rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    якщо (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        повернути AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    для (ціле c = 0; c < desc->nb_components; c++) {
        const AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        якщо (comp.depth > 32)
            повернути AVERROR(EINVAL);

        якщо (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } інакше якщо (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            якщо (fltp) {
                якщо (comp.depth != 16 && comp.depth != 32)
                    повернути AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } інакше {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } інакше якщо (c == 0 && limited && comp.depth > 1) {
            якщо (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                повернути AVERROR(EINVAL);
            якщо (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            інакше
                color = 16 << (comp.depth - 8);
        } інакше якщо ((c == 1 || c == 2) && !rgb && !xyz) {
            якщо (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                повернути AVERROR(EINVAL);
            якщо (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            інакше
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    повернути av_image_fill_color(dst_data, dst_linesize, pix_fmt, colors, width, height, 0);
}
