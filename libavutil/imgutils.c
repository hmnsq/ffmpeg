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

#شامل "avassert.h"
#شامل "common.h"
#شامل "imgutils.h"
#شامل "imgutils_internal.h"
#شامل "intreadwrite.h"
#شامل "log.h"
#شامل "mathematics.h"
#شامل "mem.h"
#شامل "pixdesc.h"
#شامل "rational.h"

تهی av_image_fill_max_pixsteps(صحیح max_pixsteps[4], صحیح max_pixstep_comps[4],
                                ثابت AVPixFmtDescriptor *pixdesc)
{
    صحیح i;
    memset(max_pixsteps, 0, 4*اندازه(max_pixsteps[0]));
    اگر (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*اندازه(max_pixstep_comps[0]));

    برای (i = 0; i < 4; i++) {
        ثابت AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        اگر (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            اگر (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

ایستا درونخطی
صحیح image_get_linesize(صحیح width, صحیح plane,
                       صحیح max_step, صحیح max_step_comp,
                       ثابت AVPixFmtDescriptor *desc)
{
    صحیح s, shifted_w, linesize;

    اگر (!desc)
        بازگشت AVERROR(EINVAL);

    اگر (width < 0)
        بازگشت AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    اگر (shifted_w && max_step > INT_MAX / shifted_w)
        بازگشت AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    اگر (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    بازگشت linesize;
}

صحیح av_image_get_linesize(شمارش AVPixelFormat pix_fmt, صحیح width, صحیح plane)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحیح max_step     [4];       /* max pixel step for each plane */
    صحیح max_step_comp[4];       /* the component for each plane which has the max pixel step */

    اگر (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        بازگشت AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    بازگشت image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

صحیح av_image_fill_linesizes(صحیح linesizes[4], شمارش AVPixelFormat pix_fmt, صحیح width)
{
    صحیح i, ret;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحیح max_step     [4];       /* max pixel step for each plane */
    صحیح max_step_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*اندازه(linesizes[0]));

    اگر (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        بازگشت AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    برای (i = 0; i < 4; i++) {
        اگر ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            بازگشت ret;
        linesizes[i] = ret;
    }

    بازگشت 0;
}

صحیح av_image_fill_plane_sizes(size_t sizes[4], شمارش AVPixelFormat pix_fmt,
                              صحیح height, ثابت ptrdiff_t linesizes[4])
{
    صحیح i, has_plane[4] = { 0 };

    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, اندازه(sizes[0])*4);

    اگر (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        بازگشت AVERROR(EINVAL);

    اگر (linesizes[0] > SIZE_MAX / height)
        بازگشت AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)height;

    اگر (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        بازگشت 0;
    }

    برای (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    برای (i = 1; i < 4 && has_plane[i]; i++) {
        صحیح h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        اگر (linesizes[i] > SIZE_MAX / h)
            بازگشت AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    بازگشت 0;
}

صحیح av_image_fill_pointers(uint8_t *data[4], شمارش AVPixelFormat pix_fmt, صحیح height,
                           uint8_t *ptr, ثابت صحیح linesizes[4])
{
    صحیح i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(data     , 0, اندازه(data[0])*4);

    برای (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    اگر (ret < 0)
        بازگشت ret;

    ret = 0;
    برای (i = 0; i < 4; i++) {
        اگر (sizes[i] > INT_MAX - ret)
            بازگشت AVERROR(EINVAL);
        ret += sizes[i];
    }

    اگر (!ptr)
        بازگشت ret;

    data[0] = ptr;
    برای (i = 1; i < 4 && sizes[i]; i++)
        data[i] = data[i - 1] + sizes[i - 1];

    بازگشت ret;
}

صحیح avpriv_set_systematic_pal2(uint32_t pal[256], شمارش AVPixelFormat pix_fmt)
{
    صحیح i;

    برای (i = 0; i < 256; i++) {
        صحیح r, g, b;

        انتخاب (pix_fmt) {
        حالت AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            بشکن;
        حالت AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            بشکن;
        حالت AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            بشکن;
        حالت AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            بشکن;
        حالت AV_PIX_FMT_GRAY8:
            r = b = g = i;
            بشکن;
        پیشفرض:
            بازگشت AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    بازگشت 0;
}

صحیح av_image_alloc(uint8_t *pointers[4], صحیح linesizes[4],
                   صحیح w, صحیح h, شمارش AVPixelFormat pix_fmt, صحیح align)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحیح i, ret;
    ptrdiff_t linesizes1[4];
    size_t total_size, sizes[4];
    uint8_t *buf;

    اگر (!desc)
        بازگشت AVERROR(EINVAL);

    اگر ((ret = av_image_check_size(w, h, 0, پوچ)) < 0)
        بازگشت ret;
    اگر ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        بازگشت ret;

    برای (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    اگر ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        بازگشت ret;
    total_size = align;
    برای (i = 0; i < 4; i++) {
        اگر (total_size > SIZE_MAX - sizes[i])
            بازگشت AVERROR(EINVAL);
        total_size += sizes[i];
    }
    buf = av_malloc(total_size);
    اگر (!buf)
        بازگشت AVERROR(ENOMEM);
    اگر ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        بازگشت ret;
    }
    اگر (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        اگر (align < 4) {
            av_log(پوچ, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            بازگشت AVERROR(EINVAL);
        }
    }

    اگر (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    بازگشت ret;
}

تعریفنوع ساختار ImgUtils {
    ثابت AVClass *class;
    صحیح   log_offset;
    تهی *log_ctx;
} ImgUtils;

ایستا ثابت AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .item_name                 = av_default_item_name,
    .option                    = پوچ,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(ImgUtils, log_offset),
    .parent_log_context_offset = offsetof(ImgUtils, log_ctx),
};

صحیح av_image_check_size2(unsigned صحیح w, unsigned صحیح h, int64_t max_pixels, شمارش AVPixelFormat pix_fmt, صحیح log_offset, تهی *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    اگر (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    اگر (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= INT_MAX || stride*(h + 128ULL) >= INT_MAX) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        بازگشت AVERROR(EINVAL);
    }

    اگر (max_pixels < INT64_MAX) {
        اگر (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            بازگشت AVERROR(EINVAL);
        }
    }

    بازگشت 0;
}

صحیح av_image_check_size(unsigned صحیح w, unsigned صحیح h, صحیح log_offset, تهی *log_ctx)
{
    بازگشت av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

صحیح av_image_check_sar(unsigned صحیح w, unsigned صحیح h, AVRational sar)
{
    int64_t scaled_dim;

    اگر (sar.den <= 0 || sar.رقم < 0)
        بازگشت AVERROR(EINVAL);

    اگر (!sar.رقم || sar.رقم == sar.den)
        بازگشت 0;

    اگر (sar.رقم < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.رقم, sar.den, AV_ROUND_ZERO);
    وگرنه
        scaled_dim = av_rescale_rnd(h, sar.den, sar.رقم, AV_ROUND_ZERO);

    اگر (scaled_dim > 0)
        بازگشت 0;

    بازگشت AVERROR(EINVAL);
}

ایستا تهی image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             ثابت uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, صحیح height)
{
    اگر (!dst || !src)
        بازگشت;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    برای (;height > 0; height--) {
        memcpy(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

تهی av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 ثابت uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, صحیح height)
{
    صحیح ret = -1;

#اگر ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    اگر (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

تهی av_image_copy_plane(uint8_t       *dst, صحیح dst_linesize,
                         ثابت uint8_t *src, صحیح src_linesize,
                         صحیح bytewidth, صحیح height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

ایستا تهی image_copy(uint8_t *ثابت dst_data[4], ثابت ptrdiff_t dst_linesizes[4],
                       ثابت uint8_t *ثابت src_data[4], ثابت ptrdiff_t src_linesizes[4],
                       شمارش AVPixelFormat pix_fmt, صحیح width, صحیح height,
                       تهی (*copy_plane)(uint8_t *, ptrdiff_t, ثابت uint8_t *,
                                          ptrdiff_t, ptrdiff_t, صحیح))
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    اگر (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        بازگشت;

    اگر (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_data[0], dst_linesizes[0],
                   src_data[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        اگر ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_data[1] && src_data[1]))
            memcpy(dst_data[1], src_data[1], 4*256);
    } وگرنه {
        صحیح i, planes_nb = 0;

        برای (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        برای (i = 0; i < planes_nb; i++) {
            صحیح h = height;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, width, i);
            اگر (bwidth < 0) {
                av_log(پوچ, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                بازگشت;
            }
            اگر (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_data[i], dst_linesizes[i],
                       src_data[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

تهی av_image_copy(uint8_t *ثابت dst_data[4], ثابت صحیح dst_linesizes[4],
                   ثابت uint8_t * ثابت src_data[4], ثابت صحیح src_linesizes[4],
                   شمارش AVPixelFormat pix_fmt, صحیح width, صحیح height)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    صحیح i;

    برای (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

تهی av_image_copy_uc_from(uint8_t * ثابت dst_data[4], ثابت ptrdiff_t dst_linesizes[4],
                           ثابت uint8_t * ثابت src_data[4], ثابت ptrdiff_t src_linesizes[4],
                           شمارش AVPixelFormat pix_fmt, صحیح width, صحیح height)
{
    image_copy(dst_data, dst_linesizes, src_data, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

صحیح av_image_fill_arrays(uint8_t *dst_data[4], صحیح dst_linesize[4],
                         ثابت uint8_t *src, شمارش AVPixelFormat pix_fmt,
                         صحیح width, صحیح height, صحیح align)
{
    صحیح ret, i;

    ret = av_image_check_size(width, height, 0, پوچ);
    اگر (ret < 0)
        بازگشت ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    اگر (ret < 0)
        بازگشت ret;

    برای (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    بازگشت av_image_fill_pointers(dst_data, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

صحیح av_image_get_buffer_size(شمارش AVPixelFormat pix_fmt,
                             صحیح width, صحیح height, صحیح align)
{
    صحیح ret, i;
    صحیح linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    اگر (!desc)
        بازگشت AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, پوچ);
    اگر (ret < 0)
        بازگشت ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    اگر (ret < 0)
        بازگشت ret;

    برای (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    اگر (ret < 0)
        بازگشت ret;

    ret = 0;
    برای (i = 0; i < 4; i++) {
        اگر (sizes[i] > INT_MAX - ret)
            بازگشت AVERROR(EINVAL);
        ret += sizes[i];
    }
    بازگشت ret;
}

صحیح av_image_copy_to_buffer(uint8_t *dst, صحیح dst_size,
                            ثابت uint8_t * ثابت src_data[4],
                            ثابت صحیح src_linesize[4],
                            شمارش AVPixelFormat pix_fmt,
                            صحیح width, صحیح height, صحیح align)
{
    صحیح i, j, nb_planes = 0, linesize[4];
    صحیح size = av_image_get_buffer_size(pix_fmt, width, height, align);
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحیح ret;

    اگر (size > dst_size || size < 0 || !desc)
        بازگشت AVERROR(EINVAL);

    برای (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    برای (i = 0; i < nb_planes; i++) {
        صحیح h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        ثابت uint8_t *src = src_data[i];
        h = AV_CEIL_RSHIFT(height, shift);

        برای (j = 0; j < h; j++) {
            memcpy(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    اگر (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        برای (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_data[1] + 4*i));
    }

    بازگشت size;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
ایستا تهی memset_bytes(uint8_t *dst, size_t dst_size, uint8_t *clear,
                         size_t clear_size)
{
    صحیح same = 1;
    صحیح i;

    اگر (!clear_size)
        بازگشت;

    // Reduce to memset() if possible.
    برای (i = 0; i < clear_size; i++) {
        اگر (clear[i] != clear[0]) {
            same = 0;
            بشکن;
        }
    }
    اگر (same)
        clear_size = 1;

    اگر (clear_size == 1) {
        memset(dst, clear[0], dst_size);
    } وگرنه {
        اگر (clear_size > dst_size)
            clear_size = dst_size;
        memcpy(dst, clear, clear_size);
        av_memcpy_backptr(dst + clear_size, clear_size, dst_size - clear_size);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_SIZE 32

صحیح av_image_fill_color(uint8_t * ثابت dst_data[4], ثابت ptrdiff_t dst_linesize[4],
                        شمارش AVPixelFormat pix_fmt, ثابت uint32_t color[4],
                        صحیح width, صحیح height, صحیح flags)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحیح nb_planes = av_pix_fmt_شمار_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_SIZE] = {{0}}; // clear padding with 0
    صحیح clear_block_size[4] = {0};
    ptrdiff_t plane_سطر_bytes[4] = {0};
    صحیح bitstream;
    صحیح plane, c;

    اگر (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        بازگشت AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    برای (c = 0; c < desc->nb_components; c++) {
        ثابت AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_size[comp.plane] = FFMAX(clear_block_size[comp.plane], comp.step);

        اگر (clear_block_size[comp.plane] > MAX_BLOCK_SIZE)
            بازگشت AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    برای (c = 0; c < desc->nb_components; c++) {
        ثابت AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        صحیح w = (bitstream ? 8 : 1) * clear_block_size[comp.plane] / comp.step;
        uint8_t *c_data[4];
        ثابت صحیح c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_SIZE];
        صحیح x;

        اگر (comp.depth > 32)
            بازگشت AVERROR(EINVAL);
        اگر (w < 1)
            بازگشت AVERROR(EINVAL);

        برای (x = 0; x < w; x++)
            src_array[x] = color[c];

        برای (x = 0; x < 4; x++)
            c_data[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_data, c_linesize, desc, 0, 0, c, w, 4);
    }

    برای (plane = 0; plane < nb_planes; plane++) {
        plane_سطر_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        اگر (plane_سطر_bytes[plane] < 0)
            بازگشت AVERROR(EINVAL);
    }

    اگر (!dst_data)
        بازگشت 0;

    برای (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_سطر_bytes[plane];
        uint8_t *data = dst_data[plane];
        صحیح chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        صحیح plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        برای (; plane_h > 0; plane_h--) {
            memset_bytes(data, bytewidth, &clear_block[plane][0], clear_block_size[plane]);
            data += dst_linesize[plane];
        }
    }

    بازگشت 0;
}

صحیح av_image_fill_black(uint8_t * ثابت dst_data[4], ثابت ptrdiff_t dst_linesize[4],
                        شمارش AVPixelFormat pix_fmt, شمارش AVColorRange range,
                        صحیح width, صحیح height)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحیح nb_planes = av_pix_fmt_شمار_planes(pix_fmt);
    صحیح rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    اگر (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        بازگشت AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    برای (صحیح c = 0; c < desc->nb_components; c++) {
        ثابت AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        اگر (comp.depth > 32)
            بازگشت AVERROR(EINVAL);

        اگر (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } وگرنه اگر (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            اگر (fltp) {
                اگر (comp.depth != 16 && comp.depth != 32)
                    بازگشت AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } وگرنه {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } وگرنه اگر (c == 0 && limited && comp.depth > 1) {
            اگر (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                بازگشت AVERROR(EINVAL);
            اگر (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            وگرنه
                color = 16 << (comp.depth - 8);
        } وگرنه اگر ((c == 1 || c == 2) && !rgb && !xyz) {
            اگر (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                بازگشت AVERROR(EINVAL);
            اگر (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            وگرنه
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    بازگشت av_image_fill_color(dst_data, dst_linesize, pix_fmt, colors, width, height, 0);
}
