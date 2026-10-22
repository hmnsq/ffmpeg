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

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "imgutils.h"
#અન્તર્ભાવ "imgutils_internal.h"
#અન્તર્ભાવ "intreadwrite.h"
#અન્તર્ભાવ "log.h"
#અન્તર્ભાવ "mathematics.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "pixdesc.h"
#અન્તર્ભાવ "rational.h"

શૂન્ય av_image_fill_max_pixsteps(પૂર્ણાંક max_pixsteps[4], પૂર્ણાંક max_pixstep_comps[4],
                                અચલ AVPixFmtDescriptor *pixdesc)
{
    પૂર્ણાંક i;
    memset(max_pixsteps, 0, 4*કદ(max_pixsteps[0]));
    જો (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*કદ(max_pixstep_comps[0]));

    માટે (i = 0; i < 4; i++) {
        અચલ AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        જો (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            જો (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

સ્થિર અંતઃરેખ
પૂર્ણાંક image_get_linesize(પૂર્ણાંક width, પૂર્ણાંક plane,
                       પૂર્ણાંક max_step, પૂર્ણાંક max_step_comp,
                       અચલ AVPixFmtDescriptor *desc)
{
    પૂર્ણાંક s, shifted_w, linesize;

    જો (!desc)
        પાછા AVERROR(EINVAL);

    જો (width < 0)
        પાછા AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    જો (shifted_w && max_step > INT_MAX / shifted_w)
        પાછા AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    જો (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    પાછા linesize;
}

પૂર્ણાંક av_image_get_linesize(ગણના AVPixelFormat pix_fmt, પૂર્ણાંક width, પૂર્ણાંક plane)
{
    અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    પૂર્ણાંક max_step     [4];       /* max pixel step for each plane */
    પૂર્ણાંક max_step_comp[4];       /* the component for each plane which has the max pixel step */

    જો (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        પાછા AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    પાછા image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

પૂર્ણાંક av_image_fill_linesizes(પૂર્ણાંક linesizes[4], ગણના AVPixelFormat pix_fmt, પૂર્ણાંક width)
{
    પૂર્ણાંક i, ret;
    અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    પૂર્ણાંક max_step     [4];       /* max pixel step for each plane */
    પૂર્ણાંક max_step_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*કદ(linesizes[0]));

    જો (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        પાછા AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    માટે (i = 0; i < 4; i++) {
        જો ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            પાછા ret;
        linesizes[i] = ret;
    }

    પાછા 0;
}

પૂર્ણાંક av_image_fill_plane_sizes(size_t sizes[4], ગણના AVPixelFormat pix_fmt,
                              પૂર્ણાંક height, અચલ ptrdiff_t linesizes[4])
{
    પૂર્ણાંક i, has_plane[4] = { 0 };

    અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, કદ(sizes[0])*4);

    જો (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        પાછા AVERROR(EINVAL);

    જો (linesizes[0] > SIZE_MAX / height)
        પાછા AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)height;

    જો (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        પાછા 0;
    }

    માટે (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    માટે (i = 1; i < 4 && has_plane[i]; i++) {
        પૂર્ણાંક h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        જો (linesizes[i] > SIZE_MAX / h)
            પાછા AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    પાછા 0;
}

પૂર્ણાંક av_image_fill_pointers(uint8_t *data[4], ગણના AVPixelFormat pix_fmt, પૂર્ણાંક height,
                           uint8_t *ptr, અચલ પૂર્ણાંક linesizes[4])
{
    પૂર્ણાંક i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(data     , 0, કદ(data[0])*4);

    માટે (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    જો (ret < 0)
        પાછા ret;

    ret = 0;
    માટે (i = 0; i < 4; i++) {
        જો (sizes[i] > INT_MAX - ret)
            પાછા AVERROR(EINVAL);
        ret += sizes[i];
    }

    જો (!ptr)
        પાછા ret;

    data[0] = ptr;
    માટે (i = 1; i < 4 && sizes[i]; i++)
        data[i] = data[i - 1] + sizes[i - 1];

    પાછા ret;
}

પૂર્ણાંક avpriv_set_systematic_pal2(uint32_t pal[256], ગણના AVPixelFormat pix_fmt)
{
    પૂર્ણાંક i;

    માટે (i = 0; i < 256; i++) {
        પૂર્ણાંક r, g, b;

        પસંદગી (pix_fmt) {
        સ્થિતિ AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            તોડો;
        સ્થિતિ AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            તોડો;
        સ્થિતિ AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            તોડો;
        સ્થિતિ AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            તોડો;
        સ્થિતિ AV_PIX_FMT_GRAY8:
            r = b = g = i;
            તોડો;
        મૂળભૂત:
            પાછા AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    પાછા 0;
}

પૂર્ણાંક av_image_alloc(uint8_t *pointers[4], પૂર્ણાંક linesizes[4],
                   પૂર્ણાંક w, પૂર્ણાંક h, ગણના AVPixelFormat pix_fmt, પૂર્ણાંક align)
{
    અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    પૂર્ણાંક i, ret;
    ptrdiff_t linesizes1[4];
    size_t total_size, sizes[4];
    uint8_t *buf;

    જો (!desc)
        પાછા AVERROR(EINVAL);

    જો ((ret = av_image_check_size(w, h, 0, ખાલી)) < 0)
        પાછા ret;
    જો ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        પાછા ret;

    માટે (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    જો ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        પાછા ret;
    total_size = align;
    માટે (i = 0; i < 4; i++) {
        જો (total_size > SIZE_MAX - sizes[i])
            પાછા AVERROR(EINVAL);
        total_size += sizes[i];
    }
    buf = av_malloc(total_size);
    જો (!buf)
        પાછા AVERROR(ENOMEM);
    જો ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        પાછા ret;
    }
    જો (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        જો (align < 4) {
            av_log(ખાલી, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            પાછા AVERROR(EINVAL);
        }
    }

    જો (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    પાછા ret;
}

પ્રકારવ્યાખ્યા સંરચના ImgUtils {
    અચલ AVClass *class;
    પૂર્ણાંક   log_offset;
    શૂન્ય *log_ctx;
} ImgUtils;

સ્થિર અચલ AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .item_name                 = av_default_item_name,
    .option                    = ખાલી,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(ImgUtils, log_offset),
    .parent_log_context_offset = offsetof(ImgUtils, log_ctx),
};

પૂર્ણાંક av_image_check_size2(unsigned પૂર્ણાંક w, unsigned પૂર્ણાંક h, int64_t max_pixels, ગણના AVPixelFormat pix_fmt, પૂર્ણાંક log_offset, શૂન્ય *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    જો (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    જો (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= INT_MAX || stride*(h + 128ULL) >= INT_MAX) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        પાછા AVERROR(EINVAL);
    }

    જો (max_pixels < INT64_MAX) {
        જો (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            પાછા AVERROR(EINVAL);
        }
    }

    પાછા 0;
}

પૂર્ણાંક av_image_check_size(unsigned પૂર્ણાંક w, unsigned પૂર્ણાંક h, પૂર્ણાંક log_offset, શૂન્ય *log_ctx)
{
    પાછા av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

પૂર્ણાંક av_image_check_sar(unsigned પૂર્ણાંક w, unsigned પૂર્ણાંક h, AVRational sar)
{
    int64_t scaled_dim;

    જો (sar.den <= 0 || sar.અંક < 0)
        પાછા AVERROR(EINVAL);

    જો (!sar.અંક || sar.અંક == sar.den)
        પાછા 0;

    જો (sar.અંક < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.અંક, sar.den, AV_ROUND_ZERO);
    નહીંતર
        scaled_dim = av_rescale_rnd(h, sar.den, sar.અંક, AV_ROUND_ZERO);

    જો (scaled_dim > 0)
        પાછા 0;

    પાછા AVERROR(EINVAL);
}

સ્થિર શૂન્ય image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             અચલ uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, પૂર્ણાંક height)
{
    જો (!dst || !src)
        પાછા;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    માટે (;height > 0; height--) {
        memcpy(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

શૂન્ય av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 અચલ uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, પૂર્ણાંક height)
{
    પૂર્ણાંક ret = -1;

#જો ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    જો (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

શૂન્ય av_image_copy_plane(uint8_t       *dst, પૂર્ણાંક dst_linesize,
                         અચલ uint8_t *src, પૂર્ણાંક src_linesize,
                         પૂર્ણાંક bytewidth, પૂર્ણાંક height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

સ્થિર શૂન્ય image_copy(uint8_t *અચલ dst_data[4], અચલ ptrdiff_t dst_linesizes[4],
                       અચલ uint8_t *અચલ src_data[4], અચલ ptrdiff_t src_linesizes[4],
                       ગણના AVPixelFormat pix_fmt, પૂર્ણાંક width, પૂર્ણાંક height,
                       શૂન્ય (*copy_plane)(uint8_t *, ptrdiff_t, અચલ uint8_t *,
                                          ptrdiff_t, ptrdiff_t, પૂર્ણાંક))
{
    અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    જો (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        પાછા;

    જો (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_data[0], dst_linesizes[0],
                   src_data[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        જો ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_data[1] && src_data[1]))
            memcpy(dst_data[1], src_data[1], 4*256);
    } નહીંતર {
        પૂર્ણાંક i, planes_nb = 0;

        માટે (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        માટે (i = 0; i < planes_nb; i++) {
            પૂર્ણાંક h = height;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, width, i);
            જો (bwidth < 0) {
                av_log(ખાલી, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                પાછા;
            }
            જો (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_data[i], dst_linesizes[i],
                       src_data[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

શૂન્ય av_image_copy(uint8_t *અચલ dst_data[4], અચલ પૂર્ણાંક dst_linesizes[4],
                   અચલ uint8_t * અચલ src_data[4], અચલ પૂર્ણાંક src_linesizes[4],
                   ગણના AVPixelFormat pix_fmt, પૂર્ણાંક width, પૂર્ણાંક height)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    પૂર્ણાંક i;

    માટે (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

શૂન્ય av_image_copy_uc_from(uint8_t * અચલ dst_data[4], અચલ ptrdiff_t dst_linesizes[4],
                           અચલ uint8_t * અચલ src_data[4], અચલ ptrdiff_t src_linesizes[4],
                           ગણના AVPixelFormat pix_fmt, પૂર્ણાંક width, પૂર્ણાંક height)
{
    image_copy(dst_data, dst_linesizes, src_data, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

પૂર્ણાંક av_image_fill_arrays(uint8_t *dst_data[4], પૂર્ણાંક dst_linesize[4],
                         અચલ uint8_t *src, ગણના AVPixelFormat pix_fmt,
                         પૂર્ણાંક width, પૂર્ણાંક height, પૂર્ણાંક align)
{
    પૂર્ણાંક ret, i;

    ret = av_image_check_size(width, height, 0, ખાલી);
    જો (ret < 0)
        પાછા ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    જો (ret < 0)
        પાછા ret;

    માટે (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    પાછા av_image_fill_pointers(dst_data, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

પૂર્ણાંક av_image_get_buffer_size(ગણના AVPixelFormat pix_fmt,
                             પૂર્ણાંક width, પૂર્ણાંક height, પૂર્ણાંક align)
{
    પૂર્ણાંક ret, i;
    પૂર્ણાંક linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    જો (!desc)
        પાછા AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, ખાલી);
    જો (ret < 0)
        પાછા ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    જો (ret < 0)
        પાછા ret;

    માટે (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    જો (ret < 0)
        પાછા ret;

    ret = 0;
    માટે (i = 0; i < 4; i++) {
        જો (sizes[i] > INT_MAX - ret)
            પાછા AVERROR(EINVAL);
        ret += sizes[i];
    }
    પાછા ret;
}

પૂર્ણાંક av_image_copy_to_buffer(uint8_t *dst, પૂર્ણાંક dst_size,
                            અચલ uint8_t * અચલ src_data[4],
                            અચલ પૂર્ણાંક src_linesize[4],
                            ગણના AVPixelFormat pix_fmt,
                            પૂર્ણાંક width, પૂર્ણાંક height, પૂર્ણાંક align)
{
    પૂર્ણાંક i, j, nb_planes = 0, linesize[4];
    પૂર્ણાંક size = av_image_get_buffer_size(pix_fmt, width, height, align);
    અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    પૂર્ણાંક ret;

    જો (size > dst_size || size < 0 || !desc)
        પાછા AVERROR(EINVAL);

    માટે (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    માટે (i = 0; i < nb_planes; i++) {
        પૂર્ણાંક h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        અચલ uint8_t *src = src_data[i];
        h = AV_CEIL_RSHIFT(height, shift);

        માટે (j = 0; j < h; j++) {
            memcpy(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    જો (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        માટે (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_data[1] + 4*i));
    }

    પાછા size;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
સ્થિર શૂન્ય memset_bytes(uint8_t *dst, size_t dst_size, uint8_t *clear,
                         size_t clear_size)
{
    પૂર્ણાંક same = 1;
    પૂર્ણાંક i;

    જો (!clear_size)
        પાછા;

    // Reduce to memset() if possible.
    માટે (i = 0; i < clear_size; i++) {
        જો (clear[i] != clear[0]) {
            same = 0;
            તોડો;
        }
    }
    જો (same)
        clear_size = 1;

    જો (clear_size == 1) {
        memset(dst, clear[0], dst_size);
    } નહીંતર {
        જો (clear_size > dst_size)
            clear_size = dst_size;
        memcpy(dst, clear, clear_size);
        av_memcpy_backptr(dst + clear_size, clear_size, dst_size - clear_size);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_SIZE 32

પૂર્ણાંક av_image_fill_color(uint8_t * અચલ dst_data[4], અચલ ptrdiff_t dst_linesize[4],
                        ગણના AVPixelFormat pix_fmt, અચલ uint32_t color[4],
                        પૂર્ણાંક width, પૂર્ણાંક height, પૂર્ણાંક flags)
{
    અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    પૂર્ણાંક nb_planes = av_pix_fmt_ગણતરી_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_SIZE] = {{0}}; // clear padding with 0
    પૂર્ણાંક clear_block_size[4] = {0};
    ptrdiff_t plane_લીટી_bytes[4] = {0};
    પૂર્ણાંક bitstream;
    પૂર્ણાંક plane, c;

    જો (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        પાછા AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    માટે (c = 0; c < desc->nb_components; c++) {
        અચલ AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_size[comp.plane] = FFMAX(clear_block_size[comp.plane], comp.step);

        જો (clear_block_size[comp.plane] > MAX_BLOCK_SIZE)
            પાછા AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    માટે (c = 0; c < desc->nb_components; c++) {
        અચલ AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        પૂર્ણાંક w = (bitstream ? 8 : 1) * clear_block_size[comp.plane] / comp.step;
        uint8_t *c_data[4];
        અચલ પૂર્ણાંક c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_SIZE];
        પૂર્ણાંક x;

        જો (comp.depth > 32)
            પાછા AVERROR(EINVAL);
        જો (w < 1)
            પાછા AVERROR(EINVAL);

        માટે (x = 0; x < w; x++)
            src_array[x] = color[c];

        માટે (x = 0; x < 4; x++)
            c_data[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_data, c_linesize, desc, 0, 0, c, w, 4);
    }

    માટે (plane = 0; plane < nb_planes; plane++) {
        plane_લીટી_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        જો (plane_લીટી_bytes[plane] < 0)
            પાછા AVERROR(EINVAL);
    }

    જો (!dst_data)
        પાછા 0;

    માટે (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_લીટી_bytes[plane];
        uint8_t *data = dst_data[plane];
        પૂર્ણાંક chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        પૂર્ણાંક plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        માટે (; plane_h > 0; plane_h--) {
            memset_bytes(data, bytewidth, &clear_block[plane][0], clear_block_size[plane]);
            data += dst_linesize[plane];
        }
    }

    પાછા 0;
}

પૂર્ણાંક av_image_fill_black(uint8_t * અચલ dst_data[4], અચલ ptrdiff_t dst_linesize[4],
                        ગણના AVPixelFormat pix_fmt, ગણના AVColorRange range,
                        પૂર્ણાંક width, પૂર્ણાંક height)
{
    અચલ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    પૂર્ણાંક nb_planes = av_pix_fmt_ગણતરી_planes(pix_fmt);
    પૂર્ણાંક rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    જો (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        પાછા AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    માટે (પૂર્ણાંક c = 0; c < desc->nb_components; c++) {
        અચલ AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        જો (comp.depth > 32)
            પાછા AVERROR(EINVAL);

        જો (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } નહીંતર જો (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            જો (fltp) {
                જો (comp.depth != 16 && comp.depth != 32)
                    પાછા AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } નહીંતર {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } નહીંતર જો (c == 0 && limited && comp.depth > 1) {
            જો (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                પાછા AVERROR(EINVAL);
            જો (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            નહીંતર
                color = 16 << (comp.depth - 8);
        } નહીંતર જો ((c == 1 || c == 2) && !rgb && !xyz) {
            જો (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                પાછા AVERROR(EINVAL);
            જો (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            નહીંતર
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    પાછા av_image_fill_color(dst_data, dst_linesize, pix_fmt, colors, width, height, 0);
}
