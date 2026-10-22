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

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "imgutils.h"
#অন্তর্ভাব "imgutils_internal.h"
#অন্তর্ভাব "intreadwrite.h"
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "mathematics.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "pixdesc.h"
#অন্তর্ভাব "rational.h"

শূন্য av_image_fill_max_pixsteps(পূর্ণসংখ্যা max_pixsteps[4], পূর্ণসংখ্যা max_pixstep_comps[4],
                                ধ্রুবক AVPixFmtDescriptor *pixdesc)
{
    পূর্ণসংখ্যা i;
    memset(max_pixsteps, 0, 4*আকার(max_pixsteps[0]));
    যদি (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*আকার(max_pixstep_comps[0]));

    জন্য (i = 0; i < 4; i++) {
        ধ্রুবক AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        যদি (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            যদি (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

স্থির অন্তঃরেখ
পূর্ণসংখ্যা image_get_linesize(পূর্ণসংখ্যা width, পূর্ণসংখ্যা plane,
                       পূর্ণসংখ্যা max_step, পূর্ণসংখ্যা max_step_comp,
                       ধ্রুবক AVPixFmtDescriptor *desc)
{
    পূর্ণসংখ্যা s, shifted_w, linesize;

    যদি (!desc)
        ফেরত AVERROR(EINVAL);

    যদি (width < 0)
        ফেরত AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    যদি (shifted_w && max_step > INT_MAX / shifted_w)
        ফেরত AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    যদি (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    ফেরত linesize;
}

পূর্ণসংখ্যা av_image_get_linesize(গণনা AVPixelFormat pix_fmt, পূর্ণসংখ্যা width, পূর্ণসংখ্যা plane)
{
    ধ্রুবক AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    পূর্ণসংখ্যা max_step     [4];       /* max pixel step for each plane */
    পূর্ণসংখ্যা max_step_comp[4];       /* the component for each plane which has the max pixel step */

    যদি (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ফেরত AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    ফেরত image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

পূর্ণসংখ্যা av_image_fill_linesizes(পূর্ণসংখ্যা linesizes[4], গণনা AVPixelFormat pix_fmt, পূর্ণসংখ্যা width)
{
    পূর্ণসংখ্যা i, ret;
    ধ্রুবক AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    পূর্ণসংখ্যা max_step     [4];       /* max pixel step for each plane */
    পূর্ণসংখ্যা max_step_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*আকার(linesizes[0]));

    যদি (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ফেরত AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    জন্য (i = 0; i < 4; i++) {
        যদি ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            ফেরত ret;
        linesizes[i] = ret;
    }

    ফেরত 0;
}

পূর্ণসংখ্যা av_image_fill_plane_sizes(size_t sizes[4], গণনা AVPixelFormat pix_fmt,
                              পূর্ণসংখ্যা height, ধ্রুবক ptrdiff_t linesizes[4])
{
    পূর্ণসংখ্যা i, has_plane[4] = { 0 };

    ধ্রুবক AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, আকার(sizes[0])*4);

    যদি (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ফেরত AVERROR(EINVAL);

    যদি (linesizes[0] > SIZE_MAX / height)
        ফেরত AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)height;

    যদি (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        ফেরত 0;
    }

    জন্য (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    জন্য (i = 1; i < 4 && has_plane[i]; i++) {
        পূর্ণসংখ্যা h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        যদি (linesizes[i] > SIZE_MAX / h)
            ফেরত AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    ফেরত 0;
}

পূর্ণসংখ্যা av_image_fill_pointers(uint8_t *তথ্য[4], গণনা AVPixelFormat pix_fmt, পূর্ণসংখ্যা height,
                           uint8_t *ptr, ধ্রুবক পূর্ণসংখ্যা linesizes[4])
{
    পূর্ণসংখ্যা i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(তথ্য     , 0, আকার(তথ্য[0])*4);

    জন্য (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    যদি (ret < 0)
        ফেরত ret;

    ret = 0;
    জন্য (i = 0; i < 4; i++) {
        যদি (sizes[i] > INT_MAX - ret)
            ফেরত AVERROR(EINVAL);
        ret += sizes[i];
    }

    যদি (!ptr)
        ফেরত ret;

    তথ্য[0] = ptr;
    জন্য (i = 1; i < 4 && sizes[i]; i++)
        তথ্য[i] = তথ্য[i - 1] + sizes[i - 1];

    ফেরত ret;
}

পূর্ণসংখ্যা avpriv_set_systematic_pal2(uint32_t pal[256], গণনা AVPixelFormat pix_fmt)
{
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < 256; i++) {
        পূর্ণসংখ্যা r, g, b;

        নির্বাচন (pix_fmt) {
        ক্ষেত্র AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            বিরতি;
        ক্ষেত্র AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            বিরতি;
        ক্ষেত্র AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            বিরতি;
        ক্ষেত্র AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            বিরতি;
        ক্ষেত্র AV_PIX_FMT_GRAY8:
            r = b = g = i;
            বিরতি;
        পূর্বনির্ধারিত:
            ফেরত AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    ফেরত 0;
}

পূর্ণসংখ্যা av_image_alloc(uint8_t *pointers[4], পূর্ণসংখ্যা linesizes[4],
                   পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, গণনা AVPixelFormat pix_fmt, পূর্ণসংখ্যা align)
{
    ধ্রুবক AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    পূর্ণসংখ্যা i, ret;
    ptrdiff_t linesizes1[4];
    size_t যোগ_আকার, sizes[4];
    uint8_t *buf;

    যদি (!desc)
        ফেরত AVERROR(EINVAL);

    যদি ((ret = av_image_check_আকার(w, h, 0, ফাঁকা)) < 0)
        ফেরত ret;
    যদি ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        ফেরত ret;

    জন্য (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    যদি ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        ফেরত ret;
    যোগ_আকার = align;
    জন্য (i = 0; i < 4; i++) {
        যদি (যোগ_আকার > SIZE_MAX - sizes[i])
            ফেরত AVERROR(EINVAL);
        যোগ_আকার += sizes[i];
    }
    buf = av_malloc(যোগ_আকার);
    যদি (!buf)
        ফেরত AVERROR(ENOMEM);
    যদি ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        ফেরত ret;
    }
    যদি (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        যদি (align < 4) {
            av_log(ফাঁকা, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            ফেরত AVERROR(EINVAL);
        }
    }

    যদি (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    ফেরত ret;
}

প্রকারলেখ কাঠামো ImgUtils {
    ধ্রুবক AVClass *class;
    পূর্ণসংখ্যা   log_offset;
    শূন্য *log_ctx;
} ImgUtils;

স্থির ধ্রুবক AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .item_name                 = av_default_item_name,
    .option                    = ফাঁকা,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(ImgUtils, log_offset),
    .parent_log_context_offset = offsetof(ImgUtils, log_ctx),
};

পূর্ণসংখ্যা av_image_check_size2(unsigned পূর্ণসংখ্যা w, unsigned পূর্ণসংখ্যা h, int64_t max_pixels, গণনা AVPixelFormat pix_fmt, পূর্ণসংখ্যা log_offset, শূন্য *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    যদি (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    যদি (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= INT_MAX || stride*(h + 128ULL) >= INT_MAX) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        ফেরত AVERROR(EINVAL);
    }

    যদি (max_pixels < INT64_MAX) {
        যদি (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            ফেরত AVERROR(EINVAL);
        }
    }

    ফেরত 0;
}

পূর্ণসংখ্যা av_image_check_আকার(unsigned পূর্ণসংখ্যা w, unsigned পূর্ণসংখ্যা h, পূর্ণসংখ্যা log_offset, শূন্য *log_ctx)
{
    ফেরত av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

পূর্ণসংখ্যা av_image_check_sar(unsigned পূর্ণসংখ্যা w, unsigned পূর্ণসংখ্যা h, AVRational sar)
{
    int64_t scaled_dim;

    যদি (sar.den <= 0 || sar.অঙ্ক < 0)
        ফেরত AVERROR(EINVAL);

    যদি (!sar.অঙ্ক || sar.অঙ্ক == sar.den)
        ফেরত 0;

    যদি (sar.অঙ্ক < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.অঙ্ক, sar.den, AV_ROUND_ZERO);
    অন্যথা
        scaled_dim = av_rescale_rnd(h, sar.den, sar.অঙ্ক, AV_ROUND_ZERO);

    যদি (scaled_dim > 0)
        ফেরত 0;

    ফেরত AVERROR(EINVAL);
}

স্থির শূন্য image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             ধ্রুবক uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, পূর্ণসংখ্যা height)
{
    যদি (!dst || !src)
        ফেরত;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    জন্য (;height > 0; height--) {
        memcpy(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

শূন্য av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 ধ্রুবক uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, পূর্ণসংখ্যা height)
{
    পূর্ণসংখ্যা ret = -1;

#যদি ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    যদি (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

শূন্য av_image_copy_plane(uint8_t       *dst, পূর্ণসংখ্যা dst_linesize,
                         ধ্রুবক uint8_t *src, পূর্ণসংখ্যা src_linesize,
                         পূর্ণসংখ্যা bytewidth, পূর্ণসংখ্যা height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

স্থির শূন্য image_copy(uint8_t *ধ্রুবক dst_তথ্য[4], ধ্রুবক ptrdiff_t dst_linesizes[4],
                       ধ্রুবক uint8_t *ধ্রুবক src_তথ্য[4], ধ্রুবক ptrdiff_t src_linesizes[4],
                       গণনা AVPixelFormat pix_fmt, পূর্ণসংখ্যা width, পূর্ণসংখ্যা height,
                       শূন্য (*copy_plane)(uint8_t *, ptrdiff_t, ধ্রুবক uint8_t *,
                                          ptrdiff_t, ptrdiff_t, পূর্ণসংখ্যা))
{
    ধ্রুবক AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    যদি (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ফেরত;

    যদি (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_তথ্য[0], dst_linesizes[0],
                   src_তথ্য[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        যদি ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_তথ্য[1] && src_তথ্য[1]))
            memcpy(dst_তথ্য[1], src_তথ্য[1], 4*256);
    } অন্যথা {
        পূর্ণসংখ্যা i, planes_nb = 0;

        জন্য (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        জন্য (i = 0; i < planes_nb; i++) {
            পূর্ণসংখ্যা h = height;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, width, i);
            যদি (bwidth < 0) {
                av_log(ফাঁকা, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                ফেরত;
            }
            যদি (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_তথ্য[i], dst_linesizes[i],
                       src_তথ্য[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

শূন্য av_image_copy(uint8_t *ধ্রুবক dst_তথ্য[4], ধ্রুবক পূর্ণসংখ্যা dst_linesizes[4],
                   ধ্রুবক uint8_t * ধ্রুবক src_তথ্য[4], ধ্রুবক পূর্ণসংখ্যা src_linesizes[4],
                   গণনা AVPixelFormat pix_fmt, পূর্ণসংখ্যা width, পূর্ণসংখ্যা height)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_তথ্য, dst_linesizes1, src_তথ্য, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

শূন্য av_image_copy_uc_from(uint8_t * ধ্রুবক dst_তথ্য[4], ধ্রুবক ptrdiff_t dst_linesizes[4],
                           ধ্রুবক uint8_t * ধ্রুবক src_তথ্য[4], ধ্রুবক ptrdiff_t src_linesizes[4],
                           গণনা AVPixelFormat pix_fmt, পূর্ণসংখ্যা width, পূর্ণসংখ্যা height)
{
    image_copy(dst_তথ্য, dst_linesizes, src_তথ্য, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

পূর্ণসংখ্যা av_image_fill_arrays(uint8_t *dst_তথ্য[4], পূর্ণসংখ্যা dst_linesize[4],
                         ধ্রুবক uint8_t *src, গণনা AVPixelFormat pix_fmt,
                         পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, পূর্ণসংখ্যা align)
{
    পূর্ণসংখ্যা ret, i;

    ret = av_image_check_আকার(width, height, 0, ফাঁকা);
    যদি (ret < 0)
        ফেরত ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    যদি (ret < 0)
        ফেরত ret;

    জন্য (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    ফেরত av_image_fill_pointers(dst_তথ্য, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

পূর্ণসংখ্যা av_image_get_বাফার_আকার(গণনা AVPixelFormat pix_fmt,
                             পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, পূর্ণসংখ্যা align)
{
    পূর্ণসংখ্যা ret, i;
    পূর্ণসংখ্যা linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    ধ্রুবক AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    যদি (!desc)
        ফেরত AVERROR(EINVAL);

    ret = av_image_check_আকার(width, height, 0, ফাঁকা);
    যদি (ret < 0)
        ফেরত ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    যদি (ret < 0)
        ফেরত ret;

    জন্য (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    যদি (ret < 0)
        ফেরত ret;

    ret = 0;
    জন্য (i = 0; i < 4; i++) {
        যদি (sizes[i] > INT_MAX - ret)
            ফেরত AVERROR(EINVAL);
        ret += sizes[i];
    }
    ফেরত ret;
}

পূর্ণসংখ্যা av_image_copy_to_বাফার(uint8_t *dst, পূর্ণসংখ্যা dst_আকার,
                            ধ্রুবক uint8_t * ধ্রুবক src_তথ্য[4],
                            ধ্রুবক পূর্ণসংখ্যা src_linesize[4],
                            গণনা AVPixelFormat pix_fmt,
                            পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, পূর্ণসংখ্যা align)
{
    পূর্ণসংখ্যা i, j, nb_planes = 0, linesize[4];
    পূর্ণসংখ্যা আকার_2 = av_image_get_বাফার_আকার(pix_fmt, width, height, align);
    ধ্রুবক AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    পূর্ণসংখ্যা ret;

    যদি (আকার_2 > dst_আকার || আকার_2 < 0 || !desc)
        ফেরত AVERROR(EINVAL);

    জন্য (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    জন্য (i = 0; i < nb_planes; i++) {
        পূর্ণসংখ্যা h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        ধ্রুবক uint8_t *src = src_তথ্য[i];
        h = AV_CEIL_RSHIFT(height, shift);

        জন্য (j = 0; j < h; j++) {
            memcpy(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    যদি (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        জন্য (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_তথ্য[1] + 4*i));
    }

    ফেরত আকার_2;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
স্থির শূন্য memset_bytes(uint8_t *dst, size_t dst_আকার, uint8_t *clear,
                         size_t clear_আকার)
{
    পূর্ণসংখ্যা same = 1;
    পূর্ণসংখ্যা i;

    যদি (!clear_আকার)
        ফেরত;

    // Reduce to memset() if possible.
    জন্য (i = 0; i < clear_আকার; i++) {
        যদি (clear[i] != clear[0]) {
            same = 0;
            বিরতি;
        }
    }
    যদি (same)
        clear_আকার = 1;

    যদি (clear_আকার == 1) {
        memset(dst, clear[0], dst_আকার);
    } অন্যথা {
        যদি (clear_আকার > dst_আকার)
            clear_আকার = dst_আকার;
        memcpy(dst, clear, clear_আকার);
        av_memcpy_backptr(dst + clear_আকার, clear_আকার, dst_আকার - clear_আকার);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_আকার 32

পূর্ণসংখ্যা av_image_fill_color(uint8_t * ধ্রুবক dst_তথ্য[4], ধ্রুবক ptrdiff_t dst_linesize[4],
                        গণনা AVPixelFormat pix_fmt, ধ্রুবক uint32_t color[4],
                        পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, পূর্ণসংখ্যা flags)
{
    ধ্রুবক AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    পূর্ণসংখ্যা nb_planes = av_pix_fmt_গুনতি_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_আকার] = {{0}}; // clear padding with 0
    পূর্ণসংখ্যা clear_block_আকার[4] = {0};
    ptrdiff_t plane_সারি_bytes[4] = {0};
    পূর্ণসংখ্যা bitstream;
    পূর্ণসংখ্যা plane, c;

    যদি (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ফেরত AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    জন্য (c = 0; c < desc->nb_components; c++) {
        ধ্রুবক AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_আকার[comp.plane] = FFMAX(clear_block_আকার[comp.plane], comp.step);

        যদি (clear_block_আকার[comp.plane] > MAX_BLOCK_আকার)
            ফেরত AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    জন্য (c = 0; c < desc->nb_components; c++) {
        ধ্রুবক AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        পূর্ণসংখ্যা w = (bitstream ? 8 : 1) * clear_block_আকার[comp.plane] / comp.step;
        uint8_t *c_তথ্য[4];
        ধ্রুবক পূর্ণসংখ্যা c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_আকার];
        পূর্ণসংখ্যা x;

        যদি (comp.depth > 32)
            ফেরত AVERROR(EINVAL);
        যদি (w < 1)
            ফেরত AVERROR(EINVAL);

        জন্য (x = 0; x < w; x++)
            src_array[x] = color[c];

        জন্য (x = 0; x < 4; x++)
            c_তথ্য[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_তথ্য, c_linesize, desc, 0, 0, c, w, 4);
    }

    জন্য (plane = 0; plane < nb_planes; plane++) {
        plane_সারি_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        যদি (plane_সারি_bytes[plane] < 0)
            ফেরত AVERROR(EINVAL);
    }

    যদি (!dst_তথ্য)
        ফেরত 0;

    জন্য (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_সারি_bytes[plane];
        uint8_t *তথ্য = dst_তথ্য[plane];
        পূর্ণসংখ্যা chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        পূর্ণসংখ্যা plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        জন্য (; plane_h > 0; plane_h--) {
            memset_bytes(তথ্য, bytewidth, &clear_block[plane][0], clear_block_আকার[plane]);
            তথ্য += dst_linesize[plane];
        }
    }

    ফেরত 0;
}

পূর্ণসংখ্যা av_image_fill_black(uint8_t * ধ্রুবক dst_তথ্য[4], ধ্রুবক ptrdiff_t dst_linesize[4],
                        গণনা AVPixelFormat pix_fmt, গণনা AVColorRange range,
                        পূর্ণসংখ্যা width, পূর্ণসংখ্যা height)
{
    ধ্রুবক AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    পূর্ণসংখ্যা nb_planes = av_pix_fmt_গুনতি_planes(pix_fmt);
    পূর্ণসংখ্যা rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    যদি (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ফেরত AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    জন্য (পূর্ণসংখ্যা c = 0; c < desc->nb_components; c++) {
        ধ্রুবক AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        যদি (comp.depth > 32)
            ফেরত AVERROR(EINVAL);

        যদি (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } অন্যথা যদি (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            যদি (fltp) {
                যদি (comp.depth != 16 && comp.depth != 32)
                    ফেরত AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } অন্যথা {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } অন্যথা যদি (c == 0 && limited && comp.depth > 1) {
            যদি (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                ফেরত AVERROR(EINVAL);
            যদি (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            অন্যথা
                color = 16 << (comp.depth - 8);
        } অন্যথা যদি ((c == 1 || c == 2) && !rgb && !xyz) {
            যদি (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                ফেরত AVERROR(EINVAL);
            যদি (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            অন্যথা
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    ফেরত av_image_fill_color(dst_তথ্য, dst_linesize, pix_fmt, colors, width, height, 0);
}
