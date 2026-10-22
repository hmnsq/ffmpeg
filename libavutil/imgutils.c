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

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "imgutils.h"
#अन्तर्भाव "imgutils_internal.h"
#अन्तर्भाव "intreadwrite.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "mathematics.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "rational.h"

शून्य av_image_fill_max_pixsteps(पूर्णाङ्क max_pixsteps[4], पूर्णाङ्क max_pixstep_comps[4],
                                अचर AVPixFmtDescriptor *pixdesc)
{
    पूर्णाङ्क i;
    स_रखो(max_pixsteps, 0, 4*परिमाण(max_pixsteps[0]));
    यदि (max_pixstep_comps)
        स_रखो(max_pixstep_comps, 0, 4*परिमाण(max_pixstep_comps[0]));

    लागि (i = 0; i < 4; i++) {
        अचर AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        यदि (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            यदि (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

स्थिर अन्तःस्थ
पूर्णाङ्क image_get_linesize(पूर्णाङ्क width, पूर्णाङ्क plane,
                       पूर्णाङ्क max_step, पूर्णाङ्क max_step_comp,
                       अचर AVPixFmtDescriptor *desc)
{
    पूर्णाङ्क s, shifted_w, linesize;

    यदि (!desc)
        फर्काऊ AVERROR(EINVAL);

    यदि (width < 0)
        फर्काऊ AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    यदि (shifted_w && max_step > पूर्णांक_उच्च / shifted_w)
        फर्काऊ AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    यदि (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    फर्काऊ linesize;
}

पूर्णाङ्क av_image_get_linesize(गणना AVPixelFormat pix_fmt, पूर्णाङ्क width, पूर्णाङ्क plane)
{
    अचर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णाङ्क max_step     [4];       /* max pixel step for each plane */
    पूर्णाङ्क max_step_comp[4];       /* the component for each plane which has the max pixel step */

    यदि (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        फर्काऊ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    फर्काऊ image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

पूर्णाङ्क av_image_fill_linesizes(पूर्णाङ्क linesizes[4], गणना AVPixelFormat pix_fmt, पूर्णाङ्क width)
{
    पूर्णाङ्क i, ret;
    अचर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णाङ्क max_step     [4];       /* max pixel step for each plane */
    पूर्णाङ्क max_step_comp[4];       /* the component for each plane which has the max pixel step */

    स_रखो(linesizes, 0, 4*परिमाण(linesizes[0]));

    यदि (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        फर्काऊ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    लागि (i = 0; i < 4; i++) {
        यदि ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            फर्काऊ ret;
        linesizes[i] = ret;
    }

    फर्काऊ 0;
}

पूर्णाङ्क av_image_fill_plane_sizes(माप_प्रकार sizes[4], गणना AVPixelFormat pix_fmt,
                              पूर्णाङ्क height, अचर सूचक_भेद_प्रकार linesizes[4])
{
    पूर्णाङ्क i, has_plane[4] = { 0 };

    अचर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    स_रखो(sizes    , 0, परिमाण(sizes[0])*4);

    यदि (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        फर्काऊ AVERROR(EINVAL);

    यदि (linesizes[0] > SIZE_MAX / height)
        फर्काऊ AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (माप_प्रकार)height;

    यदि (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        फर्काऊ 0;
    }

    लागि (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    लागि (i = 1; i < 4 && has_plane[i]; i++) {
        पूर्णाङ्क h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        यदि (linesizes[i] > SIZE_MAX / h)
            फर्काऊ AVERROR(EINVAL);
        sizes[i] = (माप_प्रकार)h * linesizes[i];
    }

    फर्काऊ 0;
}

पूर्णाङ्क av_image_fill_pointers(uint8_t *data[4], गणना AVPixelFormat pix_fmt, पूर्णाङ्क height,
                           uint8_t *ptr, अचर पूर्णाङ्क linesizes[4])
{
    पूर्णाङ्क i, ret;
    सूचक_भेद_प्रकार linesizes1[4];
    माप_प्रकार sizes[4];

    स_रखो(data     , 0, परिमाण(data[0])*4);

    लागि (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    यदि (ret < 0)
        फर्काऊ ret;

    ret = 0;
    लागि (i = 0; i < 4; i++) {
        यदि (sizes[i] > पूर्णांक_उच्च - ret)
            फर्काऊ AVERROR(EINVAL);
        ret += sizes[i];
    }

    यदि (!ptr)
        फर्काऊ ret;

    data[0] = ptr;
    लागि (i = 1; i < 4 && sizes[i]; i++)
        data[i] = data[i - 1] + sizes[i - 1];

    फर्काऊ ret;
}

पूर्णाङ्क avpriv_set_systematic_pal2(uint32_t pal[256], गणना AVPixelFormat pix_fmt)
{
    पूर्णाङ्क i;

    लागि (i = 0; i < 256; i++) {
        पूर्णाङ्क r, g, b;

        विकल्प (pix_fmt) {
        पक्ष AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            रोक;
        पक्ष AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            रोक;
        पक्ष AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            रोक;
        पक्ष AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            रोक;
        पक्ष AV_PIX_FMT_GRAY8:
            r = b = g = i;
            रोक;
        स्वभाव:
            फर्काऊ AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    फर्काऊ 0;
}

पूर्णाङ्क av_image_alloc(uint8_t *pointers[4], पूर्णाङ्क linesizes[4],
                   पूर्णाङ्क w, पूर्णाङ्क h, गणना AVPixelFormat pix_fmt, पूर्णाङ्क align)
{
    अचर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णाङ्क i, ret;
    सूचक_भेद_प्रकार linesizes1[4];
    माप_प्रकार total_size, sizes[4];
    uint8_t *buf;

    यदि (!desc)
        फर्काऊ AVERROR(EINVAL);

    यदि ((ret = av_image_check_size(w, h, 0, रिक्त)) < 0)
        फर्काऊ ret;
    यदि ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        फर्काऊ ret;

    लागि (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    यदि ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        फर्काऊ ret;
    total_size = align;
    लागि (i = 0; i < 4; i++) {
        यदि (total_size > SIZE_MAX - sizes[i])
            फर्काऊ AVERROR(EINVAL);
        total_size += sizes[i];
    }
    buf = av_malloc(total_size);
    यदि (!buf)
        फर्काऊ AVERROR(ENOMEM);
    यदि ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        फर्काऊ ret;
    }
    यदि (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        यदि (align < 4) {
            av_log(रिक्त, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            फर्काऊ AVERROR(EINVAL);
        }
    }

    यदि (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        स_रखो(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    फर्काऊ ret;
}

प्रकारनिर्देश संरचना ImgUtils {
    अचर AVClass *class;
    पूर्णाङ्क   log_offset;
    शून्य *log_ctx;
} ImgUtils;

स्थिर अचर AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = दुरत्व(ImgUtils, log_offset),
    .parent_log_context_offset = दुरत्व(ImgUtils, log_ctx),
};

पूर्णाङ्क av_image_check_size2(अचिन्हित पूर्णाङ्क w, अचिन्हित पूर्णाङ्क h, int64_t max_pixels, गणना AVPixelFormat pix_fmt, पूर्णाङ्क log_offset, शून्य *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    यदि (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    यदि (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= पूर्णांक_उच्च || stride*(h + 128ULL) >= पूर्णांक_उच्च) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        फर्काऊ AVERROR(EINVAL);
    }

    यदि (max_pixels < INT64_MAX) {
        यदि (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            फर्काऊ AVERROR(EINVAL);
        }
    }

    फर्काऊ 0;
}

पूर्णाङ्क av_image_check_size(अचिन्हित पूर्णाङ्क w, अचिन्हित पूर्णाङ्क h, पूर्णाङ्क log_offset, शून्य *log_ctx)
{
    फर्काऊ av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

पूर्णाङ्क av_image_check_sar(अचिन्हित पूर्णाङ्क w, अचिन्हित पूर्णाङ्क h, AVRational sar)
{
    int64_t scaled_dim;

    यदि (sar.den <= 0 || sar.अङ्क < 0)
        फर्काऊ AVERROR(EINVAL);

    यदि (!sar.अङ्क || sar.अङ्क == sar.den)
        फर्काऊ 0;

    यदि (sar.अङ्क < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.अङ्क, sar.den, AV_ROUND_ZERO);
    अन्यथा
        scaled_dim = av_rescale_rnd(h, sar.den, sar.अङ्क, AV_ROUND_ZERO);

    यदि (scaled_dim > 0)
        फर्काऊ 0;

    फर्काऊ AVERROR(EINVAL);
}

स्थिर शून्य image_copy_plane(uint8_t       *dst, सूचक_भेद_प्रकार dst_linesize,
                             अचर uint8_t *src, सूचक_भेद_प्रकार src_linesize,
                             सूचक_भेद_प्रकार bytewidth, पूर्णाङ्क height)
{
    यदि (!dst || !src)
        फर्काऊ;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    लागि (;height > 0; height--) {
        स_नकल(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

शून्य av_image_copy_plane_uc_from(uint8_t *dst, सूचक_भेद_प्रकार dst_linesize,
                                 अचर uint8_t *src, सूचक_भेद_प्रकार src_linesize,
                                 सूचक_भेद_प्रकार bytewidth, पूर्णाङ्क height)
{
    पूर्णाङ्क ret = -1;

#यदि ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    यदि (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

शून्य av_image_copy_plane(uint8_t       *dst, पूर्णाङ्क dst_linesize,
                         अचर uint8_t *src, पूर्णाङ्क src_linesize,
                         पूर्णाङ्क bytewidth, पूर्णाङ्क height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

स्थिर शून्य image_copy(uint8_t *अचर dst_data[4], अचर सूचक_भेद_प्रकार dst_linesizes[4],
                       अचर uint8_t *अचर src_data[4], अचर सूचक_भेद_प्रकार src_linesizes[4],
                       गणना AVPixelFormat pix_fmt, पूर्णाङ्क width, पूर्णाङ्क height,
                       शून्य (*copy_plane)(uint8_t *, सूचक_भेद_प्रकार, अचर uint8_t *,
                                          सूचक_भेद_प्रकार, सूचक_भेद_प्रकार, पूर्णाङ्क))
{
    अचर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    यदि (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        फर्काऊ;

    यदि (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_data[0], dst_linesizes[0],
                   src_data[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        यदि ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_data[1] && src_data[1]))
            स_नकल(dst_data[1], src_data[1], 4*256);
    } अन्यथा {
        पूर्णाङ्क i, planes_nb = 0;

        लागि (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        लागि (i = 0; i < planes_nb; i++) {
            पूर्णाङ्क h = height;
            सूचक_भेद_प्रकार bwidth = av_image_get_linesize(pix_fmt, width, i);
            यदि (bwidth < 0) {
                av_log(रिक्त, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                फर्काऊ;
            }
            यदि (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_data[i], dst_linesizes[i],
                       src_data[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

शून्य av_image_copy(uint8_t *अचर dst_data[4], अचर पूर्णाङ्क dst_linesizes[4],
                   अचर uint8_t * अचर src_data[4], अचर पूर्णाङ्क src_linesizes[4],
                   गणना AVPixelFormat pix_fmt, पूर्णाङ्क width, पूर्णाङ्क height)
{
    सूचक_भेद_प्रकार dst_linesizes1[4], src_linesizes1[4];
    पूर्णाङ्क i;

    लागि (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

शून्य av_image_copy_uc_from(uint8_t * अचर dst_data[4], अचर सूचक_भेद_प्रकार dst_linesizes[4],
                           अचर uint8_t * अचर src_data[4], अचर सूचक_भेद_प्रकार src_linesizes[4],
                           गणना AVPixelFormat pix_fmt, पूर्णाङ्क width, पूर्णाङ्क height)
{
    image_copy(dst_data, dst_linesizes, src_data, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

पूर्णाङ्क av_image_fill_arrays(uint8_t *dst_data[4], पूर्णाङ्क dst_linesize[4],
                         अचर uint8_t *src, गणना AVPixelFormat pix_fmt,
                         पूर्णाङ्क width, पूर्णाङ्क height, पूर्णाङ्क align)
{
    पूर्णाङ्क ret, i;

    ret = av_image_check_size(width, height, 0, रिक्त);
    यदि (ret < 0)
        फर्काऊ ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    यदि (ret < 0)
        फर्काऊ ret;

    लागि (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    फर्काऊ av_image_fill_pointers(dst_data, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

पूर्णाङ्क av_image_get_buffer_size(गणना AVPixelFormat pix_fmt,
                             पूर्णाङ्क width, पूर्णाङ्क height, पूर्णाङ्क align)
{
    पूर्णाङ्क ret, i;
    पूर्णाङ्क linesize[4];
    सूचक_भेद_प्रकार aligned_linesize[4];
    माप_प्रकार sizes[4];
    अचर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    यदि (!desc)
        फर्काऊ AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, रिक्त);
    यदि (ret < 0)
        फर्काऊ ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    यदि (ret < 0)
        फर्काऊ ret;

    लागि (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    यदि (ret < 0)
        फर्काऊ ret;

    ret = 0;
    लागि (i = 0; i < 4; i++) {
        यदि (sizes[i] > पूर्णांक_उच्च - ret)
            फर्काऊ AVERROR(EINVAL);
        ret += sizes[i];
    }
    फर्काऊ ret;
}

पूर्णाङ्क av_image_copy_to_buffer(uint8_t *dst, पूर्णाङ्क dst_size,
                            अचर uint8_t * अचर src_data[4],
                            अचर पूर्णाङ्क src_linesize[4],
                            गणना AVPixelFormat pix_fmt,
                            पूर्णाङ्क width, पूर्णाङ्क height, पूर्णाङ्क align)
{
    पूर्णाङ्क i, j, nb_planes = 0, linesize[4];
    पूर्णाङ्क size = av_image_get_buffer_size(pix_fmt, width, height, align);
    अचर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णाङ्क ret;

    यदि (size > dst_size || size < 0 || !desc)
        फर्काऊ AVERROR(EINVAL);

    लागि (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    लागि (i = 0; i < nb_planes; i++) {
        पूर्णाङ्क h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        अचर uint8_t *src = src_data[i];
        h = AV_CEIL_RSHIFT(height, shift);

        लागि (j = 0; j < h; j++) {
            स_नकल(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    यदि (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        लागि (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_data[1] + 4*i));
    }

    फर्काऊ size;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
स्थिर शून्य memset_bytes(uint8_t *dst, माप_प्रकार dst_size, uint8_t *clear,
                         माप_प्रकार clear_size)
{
    पूर्णाङ्क same = 1;
    पूर्णाङ्क i;

    यदि (!clear_size)
        फर्काऊ;

    // Reduce to memset() if possible.
    लागि (i = 0; i < clear_size; i++) {
        यदि (clear[i] != clear[0]) {
            same = 0;
            रोक;
        }
    }
    यदि (same)
        clear_size = 1;

    यदि (clear_size == 1) {
        स_रखो(dst, clear[0], dst_size);
    } अन्यथा {
        यदि (clear_size > dst_size)
            clear_size = dst_size;
        स_नकल(dst, clear, clear_size);
        av_memcpy_backptr(dst + clear_size, clear_size, dst_size - clear_size);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_SIZE 32

पूर्णाङ्क av_image_fill_color(uint8_t * अचर dst_data[4], अचर सूचक_भेद_प्रकार dst_linesize[4],
                        गणना AVPixelFormat pix_fmt, अचर uint32_t color[4],
                        पूर्णाङ्क width, पूर्णाङ्क height, पूर्णाङ्क flags)
{
    अचर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णाङ्क nb_planes = av_pix_fmt_गन्ती_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_SIZE] = {{0}}; // clear padding with 0
    पूर्णाङ्क clear_block_size[4] = {0};
    सूचक_भेद_प्रकार plane_पङ्क्ति_bytes[4] = {0};
    पूर्णाङ्क bitstream;
    पूर्णाङ्क plane, c;

    यदि (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        फर्काऊ AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    लागि (c = 0; c < desc->nb_components; c++) {
        अचर AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_size[comp.plane] = FFMAX(clear_block_size[comp.plane], comp.step);

        यदि (clear_block_size[comp.plane] > MAX_BLOCK_SIZE)
            फर्काऊ AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    लागि (c = 0; c < desc->nb_components; c++) {
        अचर AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        पूर्णाङ्क w = (bitstream ? 8 : 1) * clear_block_size[comp.plane] / comp.step;
        uint8_t *c_data[4];
        अचर पूर्णाङ्क c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_SIZE];
        पूर्णाङ्क x;

        यदि (comp.depth > 32)
            फर्काऊ AVERROR(EINVAL);
        यदि (w < 1)
            फर्काऊ AVERROR(EINVAL);

        लागि (x = 0; x < w; x++)
            src_array[x] = color[c];

        लागि (x = 0; x < 4; x++)
            c_data[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_data, c_linesize, desc, 0, 0, c, w, 4);
    }

    लागि (plane = 0; plane < nb_planes; plane++) {
        plane_पङ्क्ति_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        यदि (plane_पङ्क्ति_bytes[plane] < 0)
            फर्काऊ AVERROR(EINVAL);
    }

    यदि (!dst_data)
        फर्काऊ 0;

    लागि (plane = 0; plane < nb_planes; plane++) {
        माप_प्रकार bytewidth = plane_पङ्क्ति_bytes[plane];
        uint8_t *data = dst_data[plane];
        पूर्णाङ्क chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        पूर्णाङ्क plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        लागि (; plane_h > 0; plane_h--) {
            memset_bytes(data, bytewidth, &clear_block[plane][0], clear_block_size[plane]);
            data += dst_linesize[plane];
        }
    }

    फर्काऊ 0;
}

पूर्णाङ्क av_image_fill_black(uint8_t * अचर dst_data[4], अचर सूचक_भेद_प्रकार dst_linesize[4],
                        गणना AVPixelFormat pix_fmt, गणना AVColorRange range,
                        पूर्णाङ्क width, पूर्णाङ्क height)
{
    अचर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णाङ्क nb_planes = av_pix_fmt_गन्ती_planes(pix_fmt);
    पूर्णाङ्क rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    यदि (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        फर्काऊ AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    लागि (पूर्णाङ्क c = 0; c < desc->nb_components; c++) {
        अचर AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        यदि (comp.depth > 32)
            फर्काऊ AVERROR(EINVAL);

        यदि (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } अन्यथा यदि (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            यदि (fltp) {
                यदि (comp.depth != 16 && comp.depth != 32)
                    फर्काऊ AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } अन्यथा {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } अन्यथा यदि (c == 0 && limited && comp.depth > 1) {
            यदि (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                फर्काऊ AVERROR(EINVAL);
            यदि (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            अन्यथा
                color = 16 << (comp.depth - 8);
        } अन्यथा यदि ((c == 1 || c == 2) && !rgb && !xyz) {
            यदि (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                फर्काऊ AVERROR(EINVAL);
            यदि (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            अन्यथा
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    फर्काऊ av_image_fill_color(dst_data, dst_linesize, pix_fmt, colors, width, height, 0);
}
