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

void av_image_fill_max_pixsteps(цео max_pixsteps[4], цео max_pixstep_comps[4],
                                const AVPixFmtDescriptor *pixdesc)
{
    цео i;
    memset(max_pixsteps, 0, 4*sizeof(max_pixsteps[0]));
    ако (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*sizeof(max_pixstep_comps[0]));

    за (i = 0; i < 4; i++) {
        const AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        ако (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            ако (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

static inline
цео image_get_linesize(цео width, цео plane,
                       цео max_step, цео max_step_comp,
                       const AVPixFmtDescriptor *desc)
{
    цео s, shifted_w, linesize;

    ако (!desc)
        врати AVERROR(EINVAL);

    ако (width < 0)
        врати AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    ако (shifted_w && max_step > INT_MAX / shifted_w)
        врати AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    ако (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    врати linesize;
}

цео av_image_get_linesize(enum AVPixelFormat pix_fmt, цео width, цео plane)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    цео max_step     [4];       /* max pixel step for each plane */
    цео max_step_comp[4];       /* the component for each plane which has the max pixel step */

    ако (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        врати AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    врати image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

цео av_image_fill_linesizes(цео linesizes[4], enum AVPixelFormat pix_fmt, цео width)
{
    цео i, ret;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    цео max_step     [4];       /* max pixel step for each plane */
    цео max_step_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*sizeof(linesizes[0]));

    ако (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        врати AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    за (i = 0; i < 4; i++) {
        ако ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            врати ret;
        linesizes[i] = ret;
    }

    врати 0;
}

цео av_image_fill_plane_sizes(size_t sizes[4], enum AVPixelFormat pix_fmt,
                              цео height, const ptrdiff_t linesizes[4])
{
    цео i, has_plane[4] = { 0 };

    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, sizeof(sizes[0])*4);

    ако (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        врати AVERROR(EINVAL);

    ако (linesizes[0] > SIZE_MAX / height)
        врати AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)height;

    ако (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        врати 0;
    }

    за (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    за (i = 1; i < 4 && has_plane[i]; i++) {
        цео h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        ако (linesizes[i] > SIZE_MAX / h)
            врати AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    врати 0;
}

цео av_image_fill_pointers(uint8_t *data[4], enum AVPixelFormat pix_fmt, цео height,
                           uint8_t *ptr, const цео linesizes[4])
{
    цео i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(data     , 0, sizeof(data[0])*4);

    за (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    ако (ret < 0)
        врати ret;

    ret = 0;
    за (i = 0; i < 4; i++) {
        ако (sizes[i] > INT_MAX - ret)
            врати AVERROR(EINVAL);
        ret += sizes[i];
    }

    ако (!ptr)
        врати ret;

    data[0] = ptr;
    за (i = 1; i < 4 && sizes[i]; i++)
        data[i] = data[i - 1] + sizes[i - 1];

    врати ret;
}

цео avpriv_set_systematic_pal2(uint32_t pal[256], enum AVPixelFormat pix_fmt)
{
    цео i;

    за (i = 0; i < 256; i++) {
        цео r, g, b;

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
            врати AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    врати 0;
}

цео av_image_alloc(uint8_t *pointers[4], цео linesizes[4],
                   цео w, цео h, enum AVPixelFormat pix_fmt, цео align)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    цео i, ret;
    ptrdiff_t linesizes1[4];
    size_t total_size, sizes[4];
    uint8_t *buf;

    ако (!desc)
        врати AVERROR(EINVAL);

    ако ((ret = av_image_check_size(w, h, 0, NULL)) < 0)
        врати ret;
    ако ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        врати ret;

    за (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    ако ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        врати ret;
    total_size = align;
    за (i = 0; i < 4; i++) {
        ако (total_size > SIZE_MAX - sizes[i])
            врати AVERROR(EINVAL);
        total_size += sizes[i];
    }
    buf = av_malloc(total_size);
    ако (!buf)
        врати AVERROR(ENOMEM);
    ако ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        врати ret;
    }
    ако (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        ако (align < 4) {
            av_log(NULL, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            врати AVERROR(EINVAL);
        }
    }

    ако (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    врати ret;
}

typedef struct ImgUtils {
    const AVClass *class;
    цео   log_offset;
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

цео av_image_check_size2(unsigned цео w, unsigned цео h, int64_t max_pixels, enum AVPixelFormat pix_fmt, цео log_offset, void *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    ако (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    ако (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= INT_MAX || stride*(h + 128ULL) >= INT_MAX) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        врати AVERROR(EINVAL);
    }

    ако (max_pixels < INT64_MAX) {
        ако (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            врати AVERROR(EINVAL);
        }
    }

    врати 0;
}

цео av_image_check_size(unsigned цео w, unsigned цео h, цео log_offset, void *log_ctx)
{
    врати av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

цео av_image_check_sar(unsigned цео w, unsigned цео h, AVRational sar)
{
    int64_t scaled_dim;

    ако (sar.den <= 0 || sar.num < 0)
        врати AVERROR(EINVAL);

    ако (!sar.num || sar.num == sar.den)
        врати 0;

    ако (sar.num < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.num, sar.den, AV_ROUND_ZERO);
    инако
        scaled_dim = av_rescale_rnd(h, sar.den, sar.num, AV_ROUND_ZERO);

    ако (scaled_dim > 0)
        врати 0;

    врати AVERROR(EINVAL);
}

static void image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             const uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, цео height)
{
    ако (!dst || !src)
        врати;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    за (;height > 0; height--) {
        memcpy(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

void av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 const uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, цео height)
{
    цео ret = -1;

#ако ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    ако (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

void av_image_copy_plane(uint8_t       *dst, цео dst_linesize,
                         const uint8_t *src, цео src_linesize,
                         цео bytewidth, цео height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

static void image_copy(uint8_t *const dst_data[4], const ptrdiff_t dst_linesizes[4],
                       const uint8_t *const src_data[4], const ptrdiff_t src_linesizes[4],
                       enum AVPixelFormat pix_fmt, цео width, цео height,
                       void (*copy_plane)(uint8_t *, ptrdiff_t, const uint8_t *,
                                          ptrdiff_t, ptrdiff_t, цео))
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    ако (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        врати;

    ако (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_data[0], dst_linesizes[0],
                   src_data[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        ако ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_data[1] && src_data[1]))
            memcpy(dst_data[1], src_data[1], 4*256);
    } инако {
        цео i, planes_nb = 0;

        за (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        за (i = 0; i < planes_nb; i++) {
            цео h = height;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, width, i);
            ако (bwidth < 0) {
                av_log(NULL, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                врати;
            }
            ако (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_data[i], dst_linesizes[i],
                       src_data[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

void av_image_copy(uint8_t *const dst_data[4], const цео dst_linesizes[4],
                   const uint8_t * const src_data[4], const цео src_linesizes[4],
                   enum AVPixelFormat pix_fmt, цео width, цео height)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    цео i;

    за (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

void av_image_copy_uc_from(uint8_t * const dst_data[4], const ptrdiff_t dst_linesizes[4],
                           const uint8_t * const src_data[4], const ptrdiff_t src_linesizes[4],
                           enum AVPixelFormat pix_fmt, цео width, цео height)
{
    image_copy(dst_data, dst_linesizes, src_data, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

цео av_image_fill_arrays(uint8_t *dst_data[4], цео dst_linesize[4],
                         const uint8_t *src, enum AVPixelFormat pix_fmt,
                         цео width, цео height, цео align)
{
    цео ret, i;

    ret = av_image_check_size(width, height, 0, NULL);
    ако (ret < 0)
        врати ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    ако (ret < 0)
        врати ret;

    за (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    врати av_image_fill_pointers(dst_data, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

цео av_image_get_buffer_size(enum AVPixelFormat pix_fmt,
                             цео width, цео height, цео align)
{
    цео ret, i;
    цео linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ако (!desc)
        врати AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, NULL);
    ако (ret < 0)
        врати ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    ако (ret < 0)
        врати ret;

    за (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    ако (ret < 0)
        врати ret;

    ret = 0;
    за (i = 0; i < 4; i++) {
        ако (sizes[i] > INT_MAX - ret)
            врати AVERROR(EINVAL);
        ret += sizes[i];
    }
    врати ret;
}

цео av_image_copy_to_buffer(uint8_t *dst, цео dst_size,
                            const uint8_t * const src_data[4],
                            const цео src_linesize[4],
                            enum AVPixelFormat pix_fmt,
                            цео width, цео height, цео align)
{
    цео i, j, nb_planes = 0, linesize[4];
    цео size = av_image_get_buffer_size(pix_fmt, width, height, align);
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    цео ret;

    ако (size > dst_size || size < 0 || !desc)
        врати AVERROR(EINVAL);

    за (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    за (i = 0; i < nb_planes; i++) {
        цео h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        const uint8_t *src = src_data[i];
        h = AV_CEIL_RSHIFT(height, shift);

        за (j = 0; j < h; j++) {
            memcpy(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    ако (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        за (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_data[1] + 4*i));
    }

    врати size;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
static void memset_bytes(uint8_t *dst, size_t dst_size, uint8_t *clear,
                         size_t clear_size)
{
    цео same = 1;
    цео i;

    ако (!clear_size)
        врати;

    // Reduce to memset() if possible.
    за (i = 0; i < clear_size; i++) {
        ако (clear[i] != clear[0]) {
            same = 0;
            break;
        }
    }
    ако (same)
        clear_size = 1;

    ако (clear_size == 1) {
        memset(dst, clear[0], dst_size);
    } инако {
        ако (clear_size > dst_size)
            clear_size = dst_size;
        memcpy(dst, clear, clear_size);
        av_memcpy_backptr(dst + clear_size, clear_size, dst_size - clear_size);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_SIZE 32

цео av_image_fill_color(uint8_t * const dst_data[4], const ptrdiff_t dst_linesize[4],
                        enum AVPixelFormat pix_fmt, const uint32_t color[4],
                        цео width, цео height, цео flags)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    цео nb_planes = av_pix_fmt_count_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_SIZE] = {{0}}; // clear padding with 0
    цео clear_block_size[4] = {0};
    ptrdiff_t plane_line_bytes[4] = {0};
    цео bitstream;
    цео plane, c;

    ако (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        врати AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    за (c = 0; c < desc->nb_components; c++) {
        const AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_size[comp.plane] = FFMAX(clear_block_size[comp.plane], comp.step);

        ако (clear_block_size[comp.plane] > MAX_BLOCK_SIZE)
            врати AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    за (c = 0; c < desc->nb_components; c++) {
        const AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        цео w = (bitstream ? 8 : 1) * clear_block_size[comp.plane] / comp.step;
        uint8_t *c_data[4];
        const цео c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_SIZE];
        цео x;

        ако (comp.depth > 32)
            врати AVERROR(EINVAL);
        ако (w < 1)
            врати AVERROR(EINVAL);

        за (x = 0; x < w; x++)
            src_array[x] = color[c];

        за (x = 0; x < 4; x++)
            c_data[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_data, c_linesize, desc, 0, 0, c, w, 4);
    }

    за (plane = 0; plane < nb_planes; plane++) {
        plane_line_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        ако (plane_line_bytes[plane] < 0)
            врати AVERROR(EINVAL);
    }

    ако (!dst_data)
        врати 0;

    за (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_line_bytes[plane];
        uint8_t *data = dst_data[plane];
        цео chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        цео plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        за (; plane_h > 0; plane_h--) {
            memset_bytes(data, bytewidth, &clear_block[plane][0], clear_block_size[plane]);
            data += dst_linesize[plane];
        }
    }

    врати 0;
}

цео av_image_fill_black(uint8_t * const dst_data[4], const ptrdiff_t dst_linesize[4],
                        enum AVPixelFormat pix_fmt, enum AVColorRange range,
                        цео width, цео height)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    цео nb_planes = av_pix_fmt_count_planes(pix_fmt);
    цео rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    ако (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        врати AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    за (цео c = 0; c < desc->nb_components; c++) {
        const AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        ако (comp.depth > 32)
            врати AVERROR(EINVAL);

        ако (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } инако ако (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            ако (fltp) {
                ако (comp.depth != 16 && comp.depth != 32)
                    врати AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } инако {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } инако ако (c == 0 && limited && comp.depth > 1) {
            ако (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                врати AVERROR(EINVAL);
            ако (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            инако
                color = 16 << (comp.depth - 8);
        } инако ако ((c == 1 || c == 2) && !rgb && !xyz) {
            ако (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                врати AVERROR(EINVAL);
            ако (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            инако
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    врати av_image_fill_color(dst_data, dst_linesize, pix_fmt, colors, width, height, 0);
}
