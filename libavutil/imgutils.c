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

शून्य av_image_fill_max_pixsteps(पूर्णांक max_pixsteps[4], पूर्णांक max_pixstep_comps[4],
                                स्थिरांक AVPixFmtDescriptor *pixdesc)
{
    पूर्णांक i;
    स_रखो(max_pixsteps, 0, 4*आकार(max_pixsteps[0]));
    जर (max_pixstep_comps)
        स_रखो(max_pixstep_comps, 0, 4*आकार(max_pixstep_comps[0]));

    साठी (i = 0; i < 4; i++) {
        स्थिरांक AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        जर (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            जर (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

स्थिर ओळीत
पूर्णांक image_get_linesize(पूर्णांक width, पूर्णांक plane,
                       पूर्णांक max_step, पूर्णांक max_step_comp,
                       स्थिरांक AVPixFmtDescriptor *desc)
{
    पूर्णांक s, shifted_w, linesize;

    जर (!desc)
        परत AVERROR(EINVAL);

    जर (width < 0)
        परत AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    जर (shifted_w && max_step > पूर्णांक_उच्च / shifted_w)
        परत AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    जर (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    परत linesize;
}

पूर्णांक av_image_get_linesize(गणना AVPixelFormat pix_fmt, पूर्णांक width, पूर्णांक plane)
{
    स्थिरांक AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णांक max_step     [4];       /* max pixel step for each plane */
    पूर्णांक max_step_comp[4];       /* the component for each plane which has the max pixel step */

    जर (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        परत AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    परत image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

पूर्णांक av_image_fill_linesizes(पूर्णांक linesizes[4], गणना AVPixelFormat pix_fmt, पूर्णांक width)
{
    पूर्णांक i, ret;
    स्थिरांक AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णांक max_step     [4];       /* max pixel step for each plane */
    पूर्णांक max_step_comp[4];       /* the component for each plane which has the max pixel step */

    स_रखो(linesizes, 0, 4*आकार(linesizes[0]));

    जर (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        परत AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    साठी (i = 0; i < 4; i++) {
        जर ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            परत ret;
        linesizes[i] = ret;
    }

    परत 0;
}

पूर्णांक av_image_fill_plane_sizes(माप_प्रकार sizes[4], गणना AVPixelFormat pix_fmt,
                              पूर्णांक height, स्थिरांक सूचक_भेद_प्रकार linesizes[4])
{
    पूर्णांक i, has_plane[4] = { 0 };

    स्थिरांक AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    स_रखो(sizes    , 0, आकार(sizes[0])*4);

    जर (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        परत AVERROR(EINVAL);

    जर (linesizes[0] > SIZE_MAX / height)
        परत AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (माप_प्रकार)height;

    जर (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        परत 0;
    }

    साठी (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    साठी (i = 1; i < 4 && has_plane[i]; i++) {
        पूर्णांक h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        जर (linesizes[i] > SIZE_MAX / h)
            परत AVERROR(EINVAL);
        sizes[i] = (माप_प्रकार)h * linesizes[i];
    }

    परत 0;
}

पूर्णांक av_image_fill_pointers(uint8_t *data[4], गणना AVPixelFormat pix_fmt, पूर्णांक height,
                           uint8_t *ptr, स्थिरांक पूर्णांक linesizes[4])
{
    पूर्णांक i, ret;
    सूचक_भेद_प्रकार linesizes1[4];
    माप_प्रकार sizes[4];

    स_रखो(data     , 0, आकार(data[0])*4);

    साठी (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    जर (ret < 0)
        परत ret;

    ret = 0;
    साठी (i = 0; i < 4; i++) {
        जर (sizes[i] > पूर्णांक_उच्च - ret)
            परत AVERROR(EINVAL);
        ret += sizes[i];
    }

    जर (!ptr)
        परत ret;

    data[0] = ptr;
    साठी (i = 1; i < 4 && sizes[i]; i++)
        data[i] = data[i - 1] + sizes[i - 1];

    परत ret;
}

पूर्णांक avpriv_set_systematic_pal2(uint32_t pal[256], गणना AVPixelFormat pix_fmt)
{
    पूर्णांक i;

    साठी (i = 0; i < 256; i++) {
        पूर्णांक r, g, b;

        निवड (pix_fmt) {
        स्थिती AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            थांबा;
        स्थिती AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            थांबा;
        स्थिती AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            थांबा;
        स्थिती AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            थांबा;
        स्थिती AV_PIX_FMT_GRAY8:
            r = b = g = i;
            थांबा;
        पूर्वनिर्धारित:
            परत AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    परत 0;
}

पूर्णांक av_image_alloc(uint8_t *pointers[4], पूर्णांक linesizes[4],
                   पूर्णांक w, पूर्णांक h, गणना AVPixelFormat pix_fmt, पूर्णांक align)
{
    स्थिरांक AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णांक i, ret;
    सूचक_भेद_प्रकार linesizes1[4];
    माप_प्रकार total_size, sizes[4];
    uint8_t *buf;

    जर (!desc)
        परत AVERROR(EINVAL);

    जर ((ret = av_image_check_size(w, h, 0, रिक्त)) < 0)
        परत ret;
    जर ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        परत ret;

    साठी (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    जर ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        परत ret;
    total_size = align;
    साठी (i = 0; i < 4; i++) {
        जर (total_size > SIZE_MAX - sizes[i])
            परत AVERROR(EINVAL);
        total_size += sizes[i];
    }
    buf = av_malloc(total_size);
    जर (!buf)
        परत AVERROR(ENOMEM);
    जर ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        परत ret;
    }
    जर (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        जर (align < 4) {
            av_log(रिक्त, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            परत AVERROR(EINVAL);
        }
    }

    जर (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        स_रखो(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    परत ret;
}

प्रकारव्याख्या संरचना ImgUtils {
    स्थिरांक AVClass *class;
    पूर्णांक   log_offset;
    शून्य *log_ctx;
} ImgUtils;

स्थिर स्थिरांक AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = दुरत्व(ImgUtils, log_offset),
    .parent_log_context_offset = दुरत्व(ImgUtils, log_ctx),
};

पूर्णांक av_image_check_size2(अचिन्हित पूर्णांक w, अचिन्हित पूर्णांक h, int64_t max_pixels, गणना AVPixelFormat pix_fmt, पूर्णांक log_offset, शून्य *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    जर (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    जर (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= पूर्णांक_उच्च || stride*(h + 128ULL) >= पूर्णांक_उच्च) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        परत AVERROR(EINVAL);
    }

    जर (max_pixels < INT64_MAX) {
        जर (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            परत AVERROR(EINVAL);
        }
    }

    परत 0;
}

पूर्णांक av_image_check_size(अचिन्हित पूर्णांक w, अचिन्हित पूर्णांक h, पूर्णांक log_offset, शून्य *log_ctx)
{
    परत av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

पूर्णांक av_image_check_sar(अचिन्हित पूर्णांक w, अचिन्हित पूर्णांक h, AVRational sar)
{
    int64_t scaled_dim;

    जर (sar.den <= 0 || sar.अंक < 0)
        परत AVERROR(EINVAL);

    जर (!sar.अंक || sar.अंक == sar.den)
        परत 0;

    जर (sar.अंक < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.अंक, sar.den, AV_ROUND_ZERO);
    अन्यथा
        scaled_dim = av_rescale_rnd(h, sar.den, sar.अंक, AV_ROUND_ZERO);

    जर (scaled_dim > 0)
        परत 0;

    परत AVERROR(EINVAL);
}

स्थिर शून्य image_copy_plane(uint8_t       *dst, सूचक_भेद_प्रकार dst_linesize,
                             स्थिरांक uint8_t *src, सूचक_भेद_प्रकार src_linesize,
                             सूचक_भेद_प्रकार bytewidth, पूर्णांक height)
{
    जर (!dst || !src)
        परत;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    साठी (;height > 0; height--) {
        स_नकल(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

शून्य av_image_copy_plane_uc_from(uint8_t *dst, सूचक_भेद_प्रकार dst_linesize,
                                 स्थिरांक uint8_t *src, सूचक_भेद_प्रकार src_linesize,
                                 सूचक_भेद_प्रकार bytewidth, पूर्णांक height)
{
    पूर्णांक ret = -1;

#जर ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    जर (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

शून्य av_image_copy_plane(uint8_t       *dst, पूर्णांक dst_linesize,
                         स्थिरांक uint8_t *src, पूर्णांक src_linesize,
                         पूर्णांक bytewidth, पूर्णांक height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

स्थिर शून्य image_copy(uint8_t *स्थिरांक dst_data[4], स्थिरांक सूचक_भेद_प्रकार dst_linesizes[4],
                       स्थिरांक uint8_t *स्थिरांक src_data[4], स्थिरांक सूचक_भेद_प्रकार src_linesizes[4],
                       गणना AVPixelFormat pix_fmt, पूर्णांक width, पूर्णांक height,
                       शून्य (*copy_plane)(uint8_t *, सूचक_भेद_प्रकार, स्थिरांक uint8_t *,
                                          सूचक_भेद_प्रकार, सूचक_भेद_प्रकार, पूर्णांक))
{
    स्थिरांक AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    जर (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        परत;

    जर (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_data[0], dst_linesizes[0],
                   src_data[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        जर ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_data[1] && src_data[1]))
            स_नकल(dst_data[1], src_data[1], 4*256);
    } अन्यथा {
        पूर्णांक i, planes_nb = 0;

        साठी (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        साठी (i = 0; i < planes_nb; i++) {
            पूर्णांक h = height;
            सूचक_भेद_प्रकार bwidth = av_image_get_linesize(pix_fmt, width, i);
            जर (bwidth < 0) {
                av_log(रिक्त, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                परत;
            }
            जर (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_data[i], dst_linesizes[i],
                       src_data[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

शून्य av_image_copy(uint8_t *स्थिरांक dst_data[4], स्थिरांक पूर्णांक dst_linesizes[4],
                   स्थिरांक uint8_t * स्थिरांक src_data[4], स्थिरांक पूर्णांक src_linesizes[4],
                   गणना AVPixelFormat pix_fmt, पूर्णांक width, पूर्णांक height)
{
    सूचक_भेद_प्रकार dst_linesizes1[4], src_linesizes1[4];
    पूर्णांक i;

    साठी (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

शून्य av_image_copy_uc_from(uint8_t * स्थिरांक dst_data[4], स्थिरांक सूचक_भेद_प्रकार dst_linesizes[4],
                           स्थिरांक uint8_t * स्थिरांक src_data[4], स्थिरांक सूचक_भेद_प्रकार src_linesizes[4],
                           गणना AVPixelFormat pix_fmt, पूर्णांक width, पूर्णांक height)
{
    image_copy(dst_data, dst_linesizes, src_data, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

पूर्णांक av_image_fill_arrays(uint8_t *dst_data[4], पूर्णांक dst_linesize[4],
                         स्थिरांक uint8_t *src, गणना AVPixelFormat pix_fmt,
                         पूर्णांक width, पूर्णांक height, पूर्णांक align)
{
    पूर्णांक ret, i;

    ret = av_image_check_size(width, height, 0, रिक्त);
    जर (ret < 0)
        परत ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    जर (ret < 0)
        परत ret;

    साठी (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    परत av_image_fill_pointers(dst_data, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

पूर्णांक av_image_get_buffer_size(गणना AVPixelFormat pix_fmt,
                             पूर्णांक width, पूर्णांक height, पूर्णांक align)
{
    पूर्णांक ret, i;
    पूर्णांक linesize[4];
    सूचक_भेद_प्रकार aligned_linesize[4];
    माप_प्रकार sizes[4];
    स्थिरांक AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    जर (!desc)
        परत AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, रिक्त);
    जर (ret < 0)
        परत ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    जर (ret < 0)
        परत ret;

    साठी (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    जर (ret < 0)
        परत ret;

    ret = 0;
    साठी (i = 0; i < 4; i++) {
        जर (sizes[i] > पूर्णांक_उच्च - ret)
            परत AVERROR(EINVAL);
        ret += sizes[i];
    }
    परत ret;
}

पूर्णांक av_image_copy_to_buffer(uint8_t *dst, पूर्णांक dst_size,
                            स्थिरांक uint8_t * स्थिरांक src_data[4],
                            स्थिरांक पूर्णांक src_linesize[4],
                            गणना AVPixelFormat pix_fmt,
                            पूर्णांक width, पूर्णांक height, पूर्णांक align)
{
    पूर्णांक i, j, nb_planes = 0, linesize[4];
    पूर्णांक size = av_image_get_buffer_size(pix_fmt, width, height, align);
    स्थिरांक AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णांक ret;

    जर (size > dst_size || size < 0 || !desc)
        परत AVERROR(EINVAL);

    साठी (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    साठी (i = 0; i < nb_planes; i++) {
        पूर्णांक h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        स्थिरांक uint8_t *src = src_data[i];
        h = AV_CEIL_RSHIFT(height, shift);

        साठी (j = 0; j < h; j++) {
            स_नकल(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    जर (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        साठी (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_data[1] + 4*i));
    }

    परत size;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
स्थिर शून्य memset_bytes(uint8_t *dst, माप_प्रकार dst_size, uint8_t *clear,
                         माप_प्रकार clear_size)
{
    पूर्णांक same = 1;
    पूर्णांक i;

    जर (!clear_size)
        परत;

    // Reduce to memset() if possible.
    साठी (i = 0; i < clear_size; i++) {
        जर (clear[i] != clear[0]) {
            same = 0;
            थांबा;
        }
    }
    जर (same)
        clear_size = 1;

    जर (clear_size == 1) {
        स_रखो(dst, clear[0], dst_size);
    } अन्यथा {
        जर (clear_size > dst_size)
            clear_size = dst_size;
        स_नकल(dst, clear, clear_size);
        av_memcpy_backptr(dst + clear_size, clear_size, dst_size - clear_size);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_SIZE 32

पूर्णांक av_image_fill_color(uint8_t * स्थिरांक dst_data[4], स्थिरांक सूचक_भेद_प्रकार dst_linesize[4],
                        गणना AVPixelFormat pix_fmt, स्थिरांक uint32_t color[4],
                        पूर्णांक width, पूर्णांक height, पूर्णांक flags)
{
    स्थिरांक AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णांक nb_planes = av_pix_fmt_मोजणी_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_SIZE] = {{0}}; // clear padding with 0
    पूर्णांक clear_block_size[4] = {0};
    सूचक_भेद_प्रकार plane_ओळ_bytes[4] = {0};
    पूर्णांक bitstream;
    पूर्णांक plane, c;

    जर (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        परत AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    साठी (c = 0; c < desc->nb_components; c++) {
        स्थिरांक AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_size[comp.plane] = FFMAX(clear_block_size[comp.plane], comp.step);

        जर (clear_block_size[comp.plane] > MAX_BLOCK_SIZE)
            परत AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    साठी (c = 0; c < desc->nb_components; c++) {
        स्थिरांक AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        पूर्णांक w = (bitstream ? 8 : 1) * clear_block_size[comp.plane] / comp.step;
        uint8_t *c_data[4];
        स्थिरांक पूर्णांक c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_SIZE];
        पूर्णांक x;

        जर (comp.depth > 32)
            परत AVERROR(EINVAL);
        जर (w < 1)
            परत AVERROR(EINVAL);

        साठी (x = 0; x < w; x++)
            src_array[x] = color[c];

        साठी (x = 0; x < 4; x++)
            c_data[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_data, c_linesize, desc, 0, 0, c, w, 4);
    }

    साठी (plane = 0; plane < nb_planes; plane++) {
        plane_ओळ_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        जर (plane_ओळ_bytes[plane] < 0)
            परत AVERROR(EINVAL);
    }

    जर (!dst_data)
        परत 0;

    साठी (plane = 0; plane < nb_planes; plane++) {
        माप_प्रकार bytewidth = plane_ओळ_bytes[plane];
        uint8_t *data = dst_data[plane];
        पूर्णांक chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        पूर्णांक plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        साठी (; plane_h > 0; plane_h--) {
            memset_bytes(data, bytewidth, &clear_block[plane][0], clear_block_size[plane]);
            data += dst_linesize[plane];
        }
    }

    परत 0;
}

पूर्णांक av_image_fill_black(uint8_t * स्थिरांक dst_data[4], स्थिरांक सूचक_भेद_प्रकार dst_linesize[4],
                        गणना AVPixelFormat pix_fmt, गणना AVColorRange range,
                        पूर्णांक width, पूर्णांक height)
{
    स्थिरांक AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णांक nb_planes = av_pix_fmt_मोजणी_planes(pix_fmt);
    पूर्णांक rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    जर (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        परत AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    साठी (पूर्णांक c = 0; c < desc->nb_components; c++) {
        स्थिरांक AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        जर (comp.depth > 32)
            परत AVERROR(EINVAL);

        जर (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } अन्यथा जर (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            जर (fltp) {
                जर (comp.depth != 16 && comp.depth != 32)
                    परत AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } अन्यथा {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } अन्यथा जर (c == 0 && limited && comp.depth > 1) {
            जर (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                परत AVERROR(EINVAL);
            जर (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            अन्यथा
                color = 16 << (comp.depth - 8);
        } अन्यथा जर ((c == 1 || c == 2) && !rgb && !xyz) {
            जर (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                परत AVERROR(EINVAL);
            जर (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            अन्यथा
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    परत av_image_fill_color(dst_data, dst_linesize, pix_fmt, colors, width, height, 0);
}
