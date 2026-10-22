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

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "imgutils.h"
#அந்தர்பாவ "imgutils_internal.h"
#அந்தர்பாவ "intreadwrite.h"
#அந்தர்பாவ "log.h"
#அந்தர்பாவ "mathematics.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "pixdesc.h"
#அந்தர்பாவ "rational.h"

வெறுமை av_image_fill_max_pixsteps(முழு max_pixsteps[4], முழு max_pixstep_comps[4],
                                மாறிலி AVPixFmtDescriptor *pixdesc)
{
    முழு i;
    memset(max_pixsteps, 0, 4*அளவு(max_pixsteps[0]));
    எனில் (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*அளவு(max_pixstep_comps[0]));

    க்கு (i = 0; i < 4; i++) {
        மாறிலி AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        எனில் (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            எனில் (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

நிலையான உள்வரி
முழு image_get_linesize(முழு width, முழு plane,
                       முழு max_step, முழு max_step_comp,
                       மாறிலி AVPixFmtDescriptor *desc)
{
    முழு s, shifted_w, linesize;

    எனில் (!desc)
        திரும்பு AVERROR(EINVAL);

    எனில் (width < 0)
        திரும்பு AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    எனில் (shifted_w && max_step > INT_MAX / shifted_w)
        திரும்பு AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    எனில் (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    திரும்பு linesize;
}

முழு av_image_get_linesize(எண்ணிக்கை AVPixelFormat pix_fmt, முழு width, முழு plane)
{
    மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    முழு max_step     [4];       /* max pixel step for each plane */
    முழு max_step_comp[4];       /* the component for each plane which has the max pixel step */

    எனில் (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        திரும்பு AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    திரும்பு image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

முழு av_image_fill_linesizes(முழு linesizes[4], எண்ணிக்கை AVPixelFormat pix_fmt, முழு width)
{
    முழு i, ret;
    மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    முழு max_step     [4];       /* max pixel step for each plane */
    முழு max_step_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*அளவு(linesizes[0]));

    எனில் (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        திரும்பு AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    க்கு (i = 0; i < 4; i++) {
        எனில் ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            திரும்பு ret;
        linesizes[i] = ret;
    }

    திரும்பு 0;
}

முழு av_image_fill_plane_sizes(size_t sizes[4], எண்ணிக்கை AVPixelFormat pix_fmt,
                              முழு height, மாறிலி ptrdiff_t linesizes[4])
{
    முழு i, has_plane[4] = { 0 };

    மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, அளவு(sizes[0])*4);

    எனில் (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        திரும்பு AVERROR(EINVAL);

    எனில் (linesizes[0] > SIZE_MAX / height)
        திரும்பு AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)height;

    எனில் (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        திரும்பு 0;
    }

    க்கு (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    க்கு (i = 1; i < 4 && has_plane[i]; i++) {
        முழு h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        எனில் (linesizes[i] > SIZE_MAX / h)
            திரும்பு AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    திரும்பு 0;
}

முழு av_image_fill_pointers(uint8_t *data[4], எண்ணிக்கை AVPixelFormat pix_fmt, முழு height,
                           uint8_t *ptr, மாறிலி முழு linesizes[4])
{
    முழு i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(data     , 0, அளவு(data[0])*4);

    க்கு (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    எனில் (ret < 0)
        திரும்பு ret;

    ret = 0;
    க்கு (i = 0; i < 4; i++) {
        எனில் (sizes[i] > INT_MAX - ret)
            திரும்பு AVERROR(EINVAL);
        ret += sizes[i];
    }

    எனில் (!ptr)
        திரும்பு ret;

    data[0] = ptr;
    க்கு (i = 1; i < 4 && sizes[i]; i++)
        data[i] = data[i - 1] + sizes[i - 1];

    திரும்பு ret;
}

முழு avpriv_set_systematic_pal2(uint32_t pal[256], எண்ணிக்கை AVPixelFormat pix_fmt)
{
    முழு i;

    க்கு (i = 0; i < 256; i++) {
        முழு r, g, b;

        தேர்வு (pix_fmt) {
        நிலை AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            நிறுத்து;
        நிலை AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            நிறுத்து;
        நிலை AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            நிறுத்து;
        நிலை AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            நிறுத்து;
        நிலை AV_PIX_FMT_GRAY8:
            r = b = g = i;
            நிறுத்து;
        இயல்பு:
            திரும்பு AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    திரும்பு 0;
}

முழு av_image_alloc(uint8_t *pointers[4], முழு linesizes[4],
                   முழு w, முழு h, எண்ணிக்கை AVPixelFormat pix_fmt, முழு align)
{
    மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    முழு i, ret;
    ptrdiff_t linesizes1[4];
    size_t total_size, sizes[4];
    uint8_t *buf;

    எனில் (!desc)
        திரும்பு AVERROR(EINVAL);

    எனில் ((ret = av_image_check_size(w, h, 0, வெற்று)) < 0)
        திரும்பு ret;
    எனில் ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        திரும்பு ret;

    க்கு (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    எனில் ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        திரும்பு ret;
    total_size = align;
    க்கு (i = 0; i < 4; i++) {
        எனில் (total_size > SIZE_MAX - sizes[i])
            திரும்பு AVERROR(EINVAL);
        total_size += sizes[i];
    }
    buf = av_malloc(total_size);
    எனில் (!buf)
        திரும்பு AVERROR(ENOMEM);
    எனில் ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        திரும்பு ret;
    }
    எனில் (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        எனில் (align < 4) {
            av_log(வெற்று, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            திரும்பு AVERROR(EINVAL);
        }
    }

    எனில் (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    திரும்பு ret;
}

வகைவரை கட்டமைப்பு ImgUtils {
    மாறிலி AVClass *class;
    முழு   log_offset;
    வெறுமை *log_ctx;
} ImgUtils;

நிலையான மாறிலி AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .item_name                 = av_default_item_name,
    .option                    = வெற்று,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(ImgUtils, log_offset),
    .parent_log_context_offset = offsetof(ImgUtils, log_ctx),
};

முழு av_image_check_size2(unsigned முழு w, unsigned முழு h, int64_t max_pixels, எண்ணிக்கை AVPixelFormat pix_fmt, முழு log_offset, வெறுமை *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    எனில் (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    எனில் (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= INT_MAX || stride*(h + 128ULL) >= INT_MAX) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        திரும்பு AVERROR(EINVAL);
    }

    எனில் (max_pixels < INT64_MAX) {
        எனில் (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            திரும்பு AVERROR(EINVAL);
        }
    }

    திரும்பு 0;
}

முழு av_image_check_size(unsigned முழு w, unsigned முழு h, முழு log_offset, வெறுமை *log_ctx)
{
    திரும்பு av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

முழு av_image_check_sar(unsigned முழு w, unsigned முழு h, AVRational sar)
{
    int64_t scaled_dim;

    எனில் (sar.den <= 0 || sar.இலக்கம் < 0)
        திரும்பு AVERROR(EINVAL);

    எனில் (!sar.இலக்கம் || sar.இலக்கம் == sar.den)
        திரும்பு 0;

    எனில் (sar.இலக்கம் < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.இலக்கம், sar.den, AV_ROUND_ZERO);
    இல்லையெனில்
        scaled_dim = av_rescale_rnd(h, sar.den, sar.இலக்கம், AV_ROUND_ZERO);

    எனில் (scaled_dim > 0)
        திரும்பு 0;

    திரும்பு AVERROR(EINVAL);
}

நிலையான வெறுமை image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             மாறிலி uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, முழு height)
{
    எனில் (!dst || !src)
        திரும்பு;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    க்கு (;height > 0; height--) {
        memcpy(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

வெறுமை av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 மாறிலி uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, முழு height)
{
    முழு ret = -1;

#எனில் ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    எனில் (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

வெறுமை av_image_copy_plane(uint8_t       *dst, முழு dst_linesize,
                         மாறிலி uint8_t *src, முழு src_linesize,
                         முழு bytewidth, முழு height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

நிலையான வெறுமை image_copy(uint8_t *மாறிலி dst_data[4], மாறிலி ptrdiff_t dst_linesizes[4],
                       மாறிலி uint8_t *மாறிலி src_data[4], மாறிலி ptrdiff_t src_linesizes[4],
                       எண்ணிக்கை AVPixelFormat pix_fmt, முழு width, முழு height,
                       வெறுமை (*copy_plane)(uint8_t *, ptrdiff_t, மாறிலி uint8_t *,
                                          ptrdiff_t, ptrdiff_t, முழு))
{
    மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    எனில் (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        திரும்பு;

    எனில் (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_data[0], dst_linesizes[0],
                   src_data[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        எனில் ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_data[1] && src_data[1]))
            memcpy(dst_data[1], src_data[1], 4*256);
    } இல்லையெனில் {
        முழு i, planes_nb = 0;

        க்கு (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        க்கு (i = 0; i < planes_nb; i++) {
            முழு h = height;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, width, i);
            எனில் (bwidth < 0) {
                av_log(வெற்று, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                திரும்பு;
            }
            எனில் (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_data[i], dst_linesizes[i],
                       src_data[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

வெறுமை av_image_copy(uint8_t *மாறிலி dst_data[4], மாறிலி முழு dst_linesizes[4],
                   மாறிலி uint8_t * மாறிலி src_data[4], மாறிலி முழு src_linesizes[4],
                   எண்ணிக்கை AVPixelFormat pix_fmt, முழு width, முழு height)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    முழு i;

    க்கு (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

வெறுமை av_image_copy_uc_from(uint8_t * மாறிலி dst_data[4], மாறிலி ptrdiff_t dst_linesizes[4],
                           மாறிலி uint8_t * மாறிலி src_data[4], மாறிலி ptrdiff_t src_linesizes[4],
                           எண்ணிக்கை AVPixelFormat pix_fmt, முழு width, முழு height)
{
    image_copy(dst_data, dst_linesizes, src_data, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

முழு av_image_fill_arrays(uint8_t *dst_data[4], முழு dst_linesize[4],
                         மாறிலி uint8_t *src, எண்ணிக்கை AVPixelFormat pix_fmt,
                         முழு width, முழு height, முழு align)
{
    முழு ret, i;

    ret = av_image_check_size(width, height, 0, வெற்று);
    எனில் (ret < 0)
        திரும்பு ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    எனில் (ret < 0)
        திரும்பு ret;

    க்கு (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    திரும்பு av_image_fill_pointers(dst_data, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

முழு av_image_get_buffer_size(எண்ணிக்கை AVPixelFormat pix_fmt,
                             முழு width, முழு height, முழு align)
{
    முழு ret, i;
    முழு linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    எனில் (!desc)
        திரும்பு AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, வெற்று);
    எனில் (ret < 0)
        திரும்பு ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    எனில் (ret < 0)
        திரும்பு ret;

    க்கு (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    எனில் (ret < 0)
        திரும்பு ret;

    ret = 0;
    க்கு (i = 0; i < 4; i++) {
        எனில் (sizes[i] > INT_MAX - ret)
            திரும்பு AVERROR(EINVAL);
        ret += sizes[i];
    }
    திரும்பு ret;
}

முழு av_image_copy_to_buffer(uint8_t *dst, முழு dst_size,
                            மாறிலி uint8_t * மாறிலி src_data[4],
                            மாறிலி முழு src_linesize[4],
                            எண்ணிக்கை AVPixelFormat pix_fmt,
                            முழு width, முழு height, முழு align)
{
    முழு i, j, nb_planes = 0, linesize[4];
    முழு size = av_image_get_buffer_size(pix_fmt, width, height, align);
    மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    முழு ret;

    எனில் (size > dst_size || size < 0 || !desc)
        திரும்பு AVERROR(EINVAL);

    க்கு (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    க்கு (i = 0; i < nb_planes; i++) {
        முழு h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        மாறிலி uint8_t *src = src_data[i];
        h = AV_CEIL_RSHIFT(height, shift);

        க்கு (j = 0; j < h; j++) {
            memcpy(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    எனில் (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        க்கு (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_data[1] + 4*i));
    }

    திரும்பு size;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
நிலையான வெறுமை memset_bytes(uint8_t *dst, size_t dst_size, uint8_t *clear,
                         size_t clear_size)
{
    முழு same = 1;
    முழு i;

    எனில் (!clear_size)
        திரும்பு;

    // Reduce to memset() if possible.
    க்கு (i = 0; i < clear_size; i++) {
        எனில் (clear[i] != clear[0]) {
            same = 0;
            நிறுத்து;
        }
    }
    எனில் (same)
        clear_size = 1;

    எனில் (clear_size == 1) {
        memset(dst, clear[0], dst_size);
    } இல்லையெனில் {
        எனில் (clear_size > dst_size)
            clear_size = dst_size;
        memcpy(dst, clear, clear_size);
        av_memcpy_backptr(dst + clear_size, clear_size, dst_size - clear_size);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_SIZE 32

முழு av_image_fill_color(uint8_t * மாறிலி dst_data[4], மாறிலி ptrdiff_t dst_linesize[4],
                        எண்ணிக்கை AVPixelFormat pix_fmt, மாறிலி uint32_t color[4],
                        முழு width, முழு height, முழு flags)
{
    மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    முழு nb_planes = av_pix_fmt_மொத்தம்_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_SIZE] = {{0}}; // clear padding with 0
    முழு clear_block_size[4] = {0};
    ptrdiff_t plane_வரி_bytes[4] = {0};
    முழு bitstream;
    முழு plane, c;

    எனில் (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        திரும்பு AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    க்கு (c = 0; c < desc->nb_components; c++) {
        மாறிலி AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_size[comp.plane] = FFMAX(clear_block_size[comp.plane], comp.step);

        எனில் (clear_block_size[comp.plane] > MAX_BLOCK_SIZE)
            திரும்பு AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    க்கு (c = 0; c < desc->nb_components; c++) {
        மாறிலி AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        முழு w = (bitstream ? 8 : 1) * clear_block_size[comp.plane] / comp.step;
        uint8_t *c_data[4];
        மாறிலி முழு c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_SIZE];
        முழு x;

        எனில் (comp.depth > 32)
            திரும்பு AVERROR(EINVAL);
        எனில் (w < 1)
            திரும்பு AVERROR(EINVAL);

        க்கு (x = 0; x < w; x++)
            src_array[x] = color[c];

        க்கு (x = 0; x < 4; x++)
            c_data[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_data, c_linesize, desc, 0, 0, c, w, 4);
    }

    க்கு (plane = 0; plane < nb_planes; plane++) {
        plane_வரி_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        எனில் (plane_வரி_bytes[plane] < 0)
            திரும்பு AVERROR(EINVAL);
    }

    எனில் (!dst_data)
        திரும்பு 0;

    க்கு (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_வரி_bytes[plane];
        uint8_t *data = dst_data[plane];
        முழு chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        முழு plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        க்கு (; plane_h > 0; plane_h--) {
            memset_bytes(data, bytewidth, &clear_block[plane][0], clear_block_size[plane]);
            data += dst_linesize[plane];
        }
    }

    திரும்பு 0;
}

முழு av_image_fill_black(uint8_t * மாறிலி dst_data[4], மாறிலி ptrdiff_t dst_linesize[4],
                        எண்ணிக்கை AVPixelFormat pix_fmt, எண்ணிக்கை AVColorRange range,
                        முழு width, முழு height)
{
    மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    முழு nb_planes = av_pix_fmt_மொத்தம்_planes(pix_fmt);
    முழு rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    எனில் (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        திரும்பு AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    க்கு (முழு c = 0; c < desc->nb_components; c++) {
        மாறிலி AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        எனில் (comp.depth > 32)
            திரும்பு AVERROR(EINVAL);

        எனில் (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } இல்லையெனில் எனில் (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            எனில் (fltp) {
                எனில் (comp.depth != 16 && comp.depth != 32)
                    திரும்பு AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } இல்லையெனில் {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } இல்லையெனில் எனில் (c == 0 && limited && comp.depth > 1) {
            எனில் (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                திரும்பு AVERROR(EINVAL);
            எனில் (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            இல்லையெனில்
                color = 16 << (comp.depth - 8);
        } இல்லையெனில் எனில் ((c == 1 || c == 2) && !rgb && !xyz) {
            எனில் (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                திரும்பு AVERROR(EINVAL);
            எனில் (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            இல்லையெனில்
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    திரும்பு av_image_fill_color(dst_data, dst_linesize, pix_fmt, colors, width, height, 0);
}
