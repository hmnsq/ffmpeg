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

শূন্য av_image_fill_max_pixsteps(পূর্ণাঙ্ক max_pixsteps[4], পূর্ণাঙ্ক max_pixstep_comps[4],
                                ধ্রুব AVPixFmtDescriptor *pixdesc)
{
    পূর্ণাঙ্ক i;
    memset(max_pixsteps, 0, 4*পরিমাণ(max_pixsteps[0]));
    যদি (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*পরিমাণ(max_pixstep_comps[0]));

    প্রতি (i = 0; i < 4; i++) {
        ধ্রুব AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        যদি (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            যদি (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

স্থির অন্তঃস্থ
পূর্ণাঙ্ক image_get_linesize(পূর্ণাঙ্ক width, পূর্ণাঙ্ক plane,
                       পূর্ণাঙ্ক max_step, পূর্ণাঙ্ক max_step_comp,
                       ধ্রুব AVPixFmtDescriptor *desc)
{
    পূর্ণাঙ্ক s, shifted_w, linesize;

    যদি (!desc)
        প্রত্যাগম AVERROR(EINVAL);

    যদি (width < 0)
        প্রত্যাগম AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    যদি (shifted_w && max_step > INT_MAX / shifted_w)
        প্রত্যাগম AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    যদি (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    প্রত্যাগম linesize;
}

পূর্ণাঙ্ক av_image_get_linesize(গণনা AVPixelFormat pix_fmt, পূর্ণাঙ্ক width, পূর্ণাঙ্ক plane)
{
    ধ্রুব AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    পূর্ণাঙ্ক max_step     [4];       /* max pixel step for each plane */
    পূর্ণাঙ্ক max_step_comp[4];       /* the component for each plane which has the max pixel step */

    যদি (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        প্রত্যাগম AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    প্রত্যাগম image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

পূর্ণাঙ্ক av_image_fill_linesizes(পূর্ণাঙ্ক linesizes[4], গণনা AVPixelFormat pix_fmt, পূর্ণাঙ্ক width)
{
    পূর্ণাঙ্ক i, ret;
    ধ্রুব AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    পূর্ণাঙ্ক max_step     [4];       /* max pixel step for each plane */
    পূর্ণাঙ্ক max_step_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*পরিমাণ(linesizes[0]));

    যদি (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        প্রত্যাগম AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    প্রতি (i = 0; i < 4; i++) {
        যদি ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            প্রত্যাগম ret;
        linesizes[i] = ret;
    }

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_image_fill_plane_sizes(size_t sizes[4], গণনা AVPixelFormat pix_fmt,
                              পূর্ণাঙ্ক height, ধ্রুব ptrdiff_t linesizes[4])
{
    পূর্ণাঙ্ক i, has_plane[4] = { 0 };

    ধ্রুব AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, পরিমাণ(sizes[0])*4);

    যদি (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        প্রত্যাগম AVERROR(EINVAL);

    যদি (linesizes[0] > SIZE_MAX / height)
        প্রত্যাগম AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)height;

    যদি (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        প্রত্যাগম 0;
    }

    প্রতি (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    প্রতি (i = 1; i < 4 && has_plane[i]; i++) {
        পূর্ণাঙ্ক h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        যদি (linesizes[i] > SIZE_MAX / h)
            প্রত্যাগম AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_image_fill_pointers(uint8_t *data[4], গণনা AVPixelFormat pix_fmt, পূর্ণাঙ্ক height,
                           uint8_t *ptr, ধ্রুব পূর্ণাঙ্ক linesizes[4])
{
    পূর্ণাঙ্ক i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(data     , 0, পরিমাণ(data[0])*4);

    প্রতি (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    যদি (ret < 0)
        প্রত্যাগম ret;

    ret = 0;
    প্রতি (i = 0; i < 4; i++) {
        যদি (sizes[i] > INT_MAX - ret)
            প্রত্যাগম AVERROR(EINVAL);
        ret += sizes[i];
    }

    যদি (!ptr)
        প্রত্যাগম ret;

    data[0] = ptr;
    প্রতি (i = 1; i < 4 && sizes[i]; i++)
        data[i] = data[i - 1] + sizes[i - 1];

    প্রত্যাগম ret;
}

পূর্ণাঙ্ক avpriv_set_systematic_pal2(uint32_t pal[256], গণনা AVPixelFormat pix_fmt)
{
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; i < 256; i++) {
        পূর্ণাঙ্ক r, g, b;

        বিকল্প (pix_fmt) {
        পক্ষ AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            ভঙ্গ;
        পক্ষ AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            ভঙ্গ;
        পক্ষ AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            ভঙ্গ;
        পক্ষ AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            ভঙ্গ;
        পক্ষ AV_PIX_FMT_GRAY8:
            r = b = g = i;
            ভঙ্গ;
        স্বভাব:
            প্রত্যাগম AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_image_alloc(uint8_t *pointers[4], পূর্ণাঙ্ক linesizes[4],
                   পূর্ণাঙ্ক w, পূর্ণাঙ্ক h, গণনা AVPixelFormat pix_fmt, পূর্ণাঙ্ক align)
{
    ধ্রুব AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    পূর্ণাঙ্ক i, ret;
    ptrdiff_t linesizes1[4];
    size_t total_size, sizes[4];
    uint8_t *buf;

    যদি (!desc)
        প্রত্যাগম AVERROR(EINVAL);

    যদি ((ret = av_image_check_size(w, h, 0, রিক্ত)) < 0)
        প্রত্যাগম ret;
    যদি ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        প্রত্যাগম ret;

    প্রতি (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    যদি ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        প্রত্যাগম ret;
    total_size = align;
    প্রতি (i = 0; i < 4; i++) {
        যদি (total_size > SIZE_MAX - sizes[i])
            প্রত্যাগম AVERROR(EINVAL);
        total_size += sizes[i];
    }
    buf = av_malloc(total_size);
    যদি (!buf)
        প্রত্যাগম AVERROR(ENOMEM);
    যদি ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        প্রত্যাগম ret;
    }
    যদি (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        যদি (align < 4) {
            av_log(রিক্ত, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            প্রত্যাগম AVERROR(EINVAL);
        }
    }

    যদি (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    প্রত্যাগম ret;
}

প্রকারনির্দেশ সংরচনা ImgUtils {
    ধ্রুব AVClass *class;
    পূর্ণাঙ্ক   log_offset;
    শূন্য *log_ctx;
} ImgUtils;

স্থির ধ্রুব AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .item_name                 = av_default_item_name,
    .option                    = রিক্ত,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(ImgUtils, log_offset),
    .parent_log_context_offset = offsetof(ImgUtils, log_ctx),
};

পূর্ণাঙ্ক av_image_check_size2(unsigned পূর্ণাঙ্ক w, unsigned পূর্ণাঙ্ক h, int64_t max_pixels, গণনা AVPixelFormat pix_fmt, পূর্ণাঙ্ক log_offset, শূন্য *log_ctx)
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
        প্রত্যাগম AVERROR(EINVAL);
    }

    যদি (max_pixels < INT64_MAX) {
        যদি (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            প্রত্যাগম AVERROR(EINVAL);
        }
    }

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_image_check_size(unsigned পূর্ণাঙ্ক w, unsigned পূর্ণাঙ্ক h, পূর্ণাঙ্ক log_offset, শূন্য *log_ctx)
{
    প্রত্যাগম av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

পূর্ণাঙ্ক av_image_check_sar(unsigned পূর্ণাঙ্ক w, unsigned পূর্ণাঙ্ক h, AVRational sar)
{
    int64_t scaled_dim;

    যদি (sar.den <= 0 || sar.অঙ্ক < 0)
        প্রত্যাগম AVERROR(EINVAL);

    যদি (!sar.অঙ্ক || sar.অঙ্ক == sar.den)
        প্রত্যাগম 0;

    যদি (sar.অঙ্ক < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.অঙ্ক, sar.den, AV_ROUND_ZERO);
    অন্যথা
        scaled_dim = av_rescale_rnd(h, sar.den, sar.অঙ্ক, AV_ROUND_ZERO);

    যদি (scaled_dim > 0)
        প্রত্যাগম 0;

    প্রত্যাগম AVERROR(EINVAL);
}

স্থির শূন্য image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             ধ্রুব uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, পূর্ণাঙ্ক height)
{
    যদি (!dst || !src)
        প্রত্যাগম;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    প্রতি (;height > 0; height--) {
        memcpy(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

শূন্য av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 ধ্রুব uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, পূর্ণাঙ্ক height)
{
    পূর্ণাঙ্ক ret = -1;

#যদি ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    যদি (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

শূন্য av_image_copy_plane(uint8_t       *dst, পূর্ণাঙ্ক dst_linesize,
                         ধ্রুব uint8_t *src, পূর্ণাঙ্ক src_linesize,
                         পূর্ণাঙ্ক bytewidth, পূর্ণাঙ্ক height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

স্থির শূন্য image_copy(uint8_t *ধ্রুব dst_data[4], ধ্রুব ptrdiff_t dst_linesizes[4],
                       ধ্রুব uint8_t *ধ্রুব src_data[4], ধ্রুব ptrdiff_t src_linesizes[4],
                       গণনা AVPixelFormat pix_fmt, পূর্ণাঙ্ক width, পূর্ণাঙ্ক height,
                       শূন্য (*copy_plane)(uint8_t *, ptrdiff_t, ধ্রুব uint8_t *,
                                          ptrdiff_t, ptrdiff_t, পূর্ণাঙ্ক))
{
    ধ্রুব AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    যদি (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        প্রত্যাগম;

    যদি (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_data[0], dst_linesizes[0],
                   src_data[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        যদি ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_data[1] && src_data[1]))
            memcpy(dst_data[1], src_data[1], 4*256);
    } অন্যথা {
        পূর্ণাঙ্ক i, planes_nb = 0;

        প্রতি (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        প্রতি (i = 0; i < planes_nb; i++) {
            পূর্ণাঙ্ক h = height;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, width, i);
            যদি (bwidth < 0) {
                av_log(রিক্ত, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                প্রত্যাগম;
            }
            যদি (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_data[i], dst_linesizes[i],
                       src_data[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

শূন্য av_image_copy(uint8_t *ধ্রুব dst_data[4], ধ্রুব পূর্ণাঙ্ক dst_linesizes[4],
                   ধ্রুব uint8_t * ধ্রুব src_data[4], ধ্রুব পূর্ণাঙ্ক src_linesizes[4],
                   গণনা AVPixelFormat pix_fmt, পূর্ণাঙ্ক width, পূর্ণাঙ্ক height)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

শূন্য av_image_copy_uc_from(uint8_t * ধ্রুব dst_data[4], ধ্রুব ptrdiff_t dst_linesizes[4],
                           ধ্রুব uint8_t * ধ্রুব src_data[4], ধ্রুব ptrdiff_t src_linesizes[4],
                           গণনা AVPixelFormat pix_fmt, পূর্ণাঙ্ক width, পূর্ণাঙ্ক height)
{
    image_copy(dst_data, dst_linesizes, src_data, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

পূর্ণাঙ্ক av_image_fill_arrays(uint8_t *dst_data[4], পূর্ণাঙ্ক dst_linesize[4],
                         ধ্রুব uint8_t *src, গণনা AVPixelFormat pix_fmt,
                         পূর্ণাঙ্ক width, পূর্ণাঙ্ক height, পূর্ণাঙ্ক align)
{
    পূর্ণাঙ্ক ret, i;

    ret = av_image_check_size(width, height, 0, রিক্ত);
    যদি (ret < 0)
        প্রত্যাগম ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    যদি (ret < 0)
        প্রত্যাগম ret;

    প্রতি (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    প্রত্যাগম av_image_fill_pointers(dst_data, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

পূর্ণাঙ্ক av_image_get_buffer_size(গণনা AVPixelFormat pix_fmt,
                             পূর্ণাঙ্ক width, পূর্ণাঙ্ক height, পূর্ণাঙ্ক align)
{
    পূর্ণাঙ্ক ret, i;
    পূর্ণাঙ্ক linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    ধ্রুব AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    যদি (!desc)
        প্রত্যাগম AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, রিক্ত);
    যদি (ret < 0)
        প্রত্যাগম ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    যদি (ret < 0)
        প্রত্যাগম ret;

    প্রতি (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    যদি (ret < 0)
        প্রত্যাগম ret;

    ret = 0;
    প্রতি (i = 0; i < 4; i++) {
        যদি (sizes[i] > INT_MAX - ret)
            প্রত্যাগম AVERROR(EINVAL);
        ret += sizes[i];
    }
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_image_copy_to_buffer(uint8_t *dst, পূর্ণাঙ্ক dst_size,
                            ধ্রুব uint8_t * ধ্রুব src_data[4],
                            ধ্রুব পূর্ণাঙ্ক src_linesize[4],
                            গণনা AVPixelFormat pix_fmt,
                            পূর্ণাঙ্ক width, পূর্ণাঙ্ক height, পূর্ণাঙ্ক align)
{
    পূর্ণাঙ্ক i, j, nb_planes = 0, linesize[4];
    পূর্ণাঙ্ক size = av_image_get_buffer_size(pix_fmt, width, height, align);
    ধ্রুব AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    পূর্ণাঙ্ক ret;

    যদি (size > dst_size || size < 0 || !desc)
        প্রত্যাগম AVERROR(EINVAL);

    প্রতি (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    প্রতি (i = 0; i < nb_planes; i++) {
        পূর্ণাঙ্ক h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        ধ্রুব uint8_t *src = src_data[i];
        h = AV_CEIL_RSHIFT(height, shift);

        প্রতি (j = 0; j < h; j++) {
            memcpy(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    যদি (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        প্রতি (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_data[1] + 4*i));
    }

    প্রত্যাগম size;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
স্থির শূন্য memset_bytes(uint8_t *dst, size_t dst_size, uint8_t *clear,
                         size_t clear_size)
{
    পূর্ণাঙ্ক same = 1;
    পূর্ণাঙ্ক i;

    যদি (!clear_size)
        প্রত্যাগম;

    // Reduce to memset() if possible.
    প্রতি (i = 0; i < clear_size; i++) {
        যদি (clear[i] != clear[0]) {
            same = 0;
            ভঙ্গ;
        }
    }
    যদি (same)
        clear_size = 1;

    যদি (clear_size == 1) {
        memset(dst, clear[0], dst_size);
    } অন্যথা {
        যদি (clear_size > dst_size)
            clear_size = dst_size;
        memcpy(dst, clear, clear_size);
        av_memcpy_backptr(dst + clear_size, clear_size, dst_size - clear_size);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_SIZE 32

পূর্ণাঙ্ক av_image_fill_color(uint8_t * ধ্রুব dst_data[4], ধ্রুব ptrdiff_t dst_linesize[4],
                        গণনা AVPixelFormat pix_fmt, ধ্রুব uint32_t color[4],
                        পূর্ণাঙ্ক width, পূর্ণাঙ্ক height, পূর্ণাঙ্ক flags)
{
    ধ্রুব AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    পূর্ণাঙ্ক nb_planes = av_pix_fmt_গুনতি_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_SIZE] = {{0}}; // clear padding with 0
    পূর্ণাঙ্ক clear_block_size[4] = {0};
    ptrdiff_t plane_সারি_bytes[4] = {0};
    পূর্ণাঙ্ক bitstream;
    পূর্ণাঙ্ক plane, c;

    যদি (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        প্রত্যাগম AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    প্রতি (c = 0; c < desc->nb_components; c++) {
        ধ্রুব AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_size[comp.plane] = FFMAX(clear_block_size[comp.plane], comp.step);

        যদি (clear_block_size[comp.plane] > MAX_BLOCK_SIZE)
            প্রত্যাগম AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    প্রতি (c = 0; c < desc->nb_components; c++) {
        ধ্রুব AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        পূর্ণাঙ্ক w = (bitstream ? 8 : 1) * clear_block_size[comp.plane] / comp.step;
        uint8_t *c_data[4];
        ধ্রুব পূর্ণাঙ্ক c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_SIZE];
        পূর্ণাঙ্ক x;

        যদি (comp.depth > 32)
            প্রত্যাগম AVERROR(EINVAL);
        যদি (w < 1)
            প্রত্যাগম AVERROR(EINVAL);

        প্রতি (x = 0; x < w; x++)
            src_array[x] = color[c];

        প্রতি (x = 0; x < 4; x++)
            c_data[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_data, c_linesize, desc, 0, 0, c, w, 4);
    }

    প্রতি (plane = 0; plane < nb_planes; plane++) {
        plane_সারি_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        যদি (plane_সারি_bytes[plane] < 0)
            প্রত্যাগম AVERROR(EINVAL);
    }

    যদি (!dst_data)
        প্রত্যাগম 0;

    প্রতি (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_সারি_bytes[plane];
        uint8_t *data = dst_data[plane];
        পূর্ণাঙ্ক chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        পূর্ণাঙ্ক plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        প্রতি (; plane_h > 0; plane_h--) {
            memset_bytes(data, bytewidth, &clear_block[plane][0], clear_block_size[plane]);
            data += dst_linesize[plane];
        }
    }

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_image_fill_black(uint8_t * ধ্রুব dst_data[4], ধ্রুব ptrdiff_t dst_linesize[4],
                        গণনা AVPixelFormat pix_fmt, গণনা AVColorRange range,
                        পূর্ণাঙ্ক width, পূর্ণাঙ্ক height)
{
    ধ্রুব AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    পূর্ণাঙ্ক nb_planes = av_pix_fmt_গুনতি_planes(pix_fmt);
    পূর্ণাঙ্ক rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    যদি (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        প্রত্যাগম AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    প্রতি (পূর্ণাঙ্ক c = 0; c < desc->nb_components; c++) {
        ধ্রুব AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        যদি (comp.depth > 32)
            প্রত্যাগম AVERROR(EINVAL);

        যদি (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } অন্যথা যদি (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            যদি (fltp) {
                যদি (comp.depth != 16 && comp.depth != 32)
                    প্রত্যাগম AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } অন্যথা {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } অন্যথা যদি (c == 0 && limited && comp.depth > 1) {
            যদি (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                প্রত্যাগম AVERROR(EINVAL);
            যদি (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            অন্যথা
                color = 16 << (comp.depth - 8);
        } অন্যথা যদি ((c == 1 || c == 2) && !rgb && !xyz) {
            যদি (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                প্রত্যাগম AVERROR(EINVAL);
            যদি (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            অন্যথা
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    প্রত্যাগম av_image_fill_color(dst_data, dst_linesize, pix_fmt, colors, width, height, 0);
}
