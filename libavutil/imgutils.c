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

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "imgutils.h"
#ଅନ୍ତର୍ଭାଵ "imgutils_internal.h"
#ଅନ୍ତର୍ଭାଵ "intreadwrite.h"
#ଅନ୍ତର୍ଭାଵ "log.h"
#ଅନ୍ତର୍ଭାଵ "mathematics.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "pixdesc.h"
#ଅନ୍ତର୍ଭାଵ "rational.h"

ଶୂନ୍ୟ av_image_fill_max_pixsteps(ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_pixsteps[4], ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_pixstep_comps[4],
                                ଅଚଳ AVPixFmtDescriptor *pixdesc)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    memset(max_pixsteps, 0, 4*ଆକାର(max_pixsteps[0]));
    ଯଦି (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*ଆକାର(max_pixstep_comps[0]));

    ପାଇଁ (i = 0; i < 4; i++) {
        ଅଚଳ AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        ଯଦି (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            ଯଦି (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ
ପୂର୍ଣ୍ଣସଂଖ୍ୟା image_get_linesize(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane,
                       ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_step, ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_step_comp,
                       ଅଚଳ AVPixFmtDescriptor *desc)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା s, shifted_w, linesize;

    ଯଦି (!desc)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (width < 0)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    ଯଦି (shifted_w && max_step > INT_MAX / shifted_w)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    ଯଦି (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    ଫେରନ୍ତୁ linesize;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_image_get_linesize(ଗଣନା AVPixelFormat pix_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane)
{
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_step     [4];       /* max pixel step for each plane */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_step_comp[4];       /* the component for each plane which has the max pixel step */

    ଯଦି (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    ଫେରନ୍ତୁ image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_image_fill_linesizes(ପୂର୍ଣ୍ଣସଂଖ୍ୟା linesizes[4], ଗଣନା AVPixelFormat pix_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା width)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret;
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_step     [4];       /* max pixel step for each plane */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_step_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*ଆକାର(linesizes[0]));

    ଯଦି (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    ପାଇଁ (i = 0; i < 4; i++) {
        ଯଦି ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            ଫେରନ୍ତୁ ret;
        linesizes[i] = ret;
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_image_fill_plane_sizes(size_t sizes[4], ଗଣନା AVPixelFormat pix_fmt,
                              ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଅଚଳ ptrdiff_t linesizes[4])
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, has_plane[4] = { 0 };

    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, ଆକାର(sizes[0])*4);

    ଯଦି (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (linesizes[0] > SIZE_MAX / height)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)height;

    ଯଦି (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        ଫେରନ୍ତୁ 0;
    }

    ପାଇଁ (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    ପାଇଁ (i = 1; i < 4 && has_plane[i]; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        ଯଦି (linesizes[i] > SIZE_MAX / h)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_image_fill_pointers(uint8_t *data[4], ଗଣନା AVPixelFormat pix_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height,
                           uint8_t *ptr, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା linesizes[4])
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(data     , 0, ଆକାର(data[0])*4);

    ପାଇଁ (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ret = 0;
    ପାଇଁ (i = 0; i < 4; i++) {
        ଯଦି (sizes[i] > INT_MAX - ret)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        ret += sizes[i];
    }

    ଯଦି (!ptr)
        ଫେରନ୍ତୁ ret;

    data[0] = ptr;
    ପାଇଁ (i = 1; i < 4 && sizes[i]; i++)
        data[i] = data[i - 1] + sizes[i - 1];

    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା avpriv_set_systematic_pal2(uint32_t pal[256], ଗଣନା AVPixelFormat pix_fmt)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < 256; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା r, g, b;

        ବାଛ (pix_fmt) {
        ସ୍ଥିତି AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି AV_PIX_FMT_GRAY8:
            r = b = g = i;
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_image_alloc(uint8_t *pointers[4], ପୂର୍ଣ୍ଣସଂଖ୍ୟା linesizes[4],
                   ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, ଗଣନା AVPixelFormat pix_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା align)
{
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret;
    ptrdiff_t linesizes1[4];
    size_t total_size, sizes[4];
    uint8_t *buf;

    ଯଦି (!desc)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି ((ret = av_image_check_size(w, h, 0, ଖାଲି)) < 0)
        ଫେରନ୍ତୁ ret;
    ଯଦି ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        ଫେରନ୍ତୁ ret;

    ପାଇଁ (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    ଯଦି ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        ଫେରନ୍ତୁ ret;
    total_size = align;
    ପାଇଁ (i = 0; i < 4; i++) {
        ଯଦି (total_size > SIZE_MAX - sizes[i])
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        total_size += sizes[i];
    }
    buf = av_malloc(total_size);
    ଯଦି (!buf)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    ଯଦି ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        ଫେରନ୍ତୁ ret;
    }
    ଯଦି (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        ଯଦି (align < 4) {
            av_log(ଖାଲି, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
    }

    ଯଦି (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    ଫେରନ୍ତୁ ret;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ImgUtils {
    ଅଚଳ AVClass *class;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା   log_offset;
    ଶୂନ୍ୟ *log_ctx;
} ImgUtils;

ସ୍ଥିର ଅଚଳ AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .item_name                 = av_default_item_name,
    .option                    = ଖାଲି,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(ImgUtils, log_offset),
    .parent_log_context_offset = offsetof(ImgUtils, log_ctx),
};

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_image_check_size2(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, int64_t max_pixels, ଗଣନା AVPixelFormat pix_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା log_offset, ଶୂନ୍ୟ *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    ଯଦି (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    ଯଦି (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= INT_MAX || stride*(h + 128ULL) >= INT_MAX) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ଯଦି (max_pixels < INT64_MAX) {
        ଯଦି (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_image_check_size(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, ପୂର୍ଣ୍ଣସଂଖ୍ୟା log_offset, ଶୂନ୍ୟ *log_ctx)
{
    ଫେରନ୍ତୁ av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_image_check_sar(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, AVRational sar)
{
    int64_t scaled_dim;

    ଯଦି (sar.den <= 0 || sar.ଅଙ୍କ < 0)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (!sar.ଅଙ୍କ || sar.ଅଙ୍କ == sar.den)
        ଫେରନ୍ତୁ 0;

    ଯଦି (sar.ଅଙ୍କ < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.ଅଙ୍କ, sar.den, AV_ROUND_ZERO);
    ଅନ୍ୟଥା
        scaled_dim = av_rescale_rnd(h, sar.den, sar.ଅଙ୍କ, AV_ROUND_ZERO);

    ଯଦି (scaled_dim > 0)
        ଫେରନ୍ତୁ 0;

    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ସ୍ଥିର ଶୂନ୍ୟ image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             ଅଚଳ uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height)
{
    ଯଦି (!dst || !src)
        ଫେରନ୍ତୁ;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    ପାଇଁ (;height > 0; height--) {
        memcpy(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

ଶୂନ୍ୟ av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 ଅଚଳ uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = -1;

#ଯଦି ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    ଯଦି (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

ଶୂନ୍ୟ av_image_copy_plane(uint8_t       *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_linesize,
                         ଅଚଳ uint8_t *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_linesize,
                         ପୂର୍ଣ୍ଣସଂଖ୍ୟା bytewidth, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

ସ୍ଥିର ଶୂନ୍ୟ image_copy(uint8_t *ଅଚଳ dst_data[4], ଅଚଳ ptrdiff_t dst_linesizes[4],
                       ଅଚଳ uint8_t *ଅଚଳ src_data[4], ଅଚଳ ptrdiff_t src_linesizes[4],
                       ଗଣନା AVPixelFormat pix_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height,
                       ଶୂନ୍ୟ (*copy_plane)(uint8_t *, ptrdiff_t, ଅଚଳ uint8_t *,
                                          ptrdiff_t, ptrdiff_t, ପୂର୍ଣ୍ଣସଂଖ୍ୟା))
{
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    ଯଦି (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ଫେରନ୍ତୁ;

    ଯଦି (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_data[0], dst_linesizes[0],
                   src_data[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        ଯଦି ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_data[1] && src_data[1]))
            memcpy(dst_data[1], src_data[1], 4*256);
    } ଅନ୍ୟଥା {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, planes_nb = 0;

        ପାଇଁ (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        ପାଇଁ (i = 0; i < planes_nb; i++) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = height;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, width, i);
            ଯଦି (bwidth < 0) {
                av_log(ଖାଲି, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                ଫେରନ୍ତୁ;
            }
            ଯଦି (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_data[i], dst_linesizes[i],
                       src_data[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

ଶୂନ୍ୟ av_image_copy(uint8_t *ଅଚଳ dst_data[4], ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_linesizes[4],
                   ଅଚଳ uint8_t * ଅଚଳ src_data[4], ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_linesizes[4],
                   ଗଣନା AVPixelFormat pix_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

ଶୂନ୍ୟ av_image_copy_uc_from(uint8_t * ଅଚଳ dst_data[4], ଅଚଳ ptrdiff_t dst_linesizes[4],
                           ଅଚଳ uint8_t * ଅଚଳ src_data[4], ଅଚଳ ptrdiff_t src_linesizes[4],
                           ଗଣନା AVPixelFormat pix_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height)
{
    image_copy(dst_data, dst_linesizes, src_data, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_image_fill_arrays(uint8_t *dst_data[4], ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_linesize[4],
                         ଅଚଳ uint8_t *src, ଗଣନା AVPixelFormat pix_fmt,
                         ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ପୂର୍ଣ୍ଣସଂଖ୍ୟା align)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, i;

    ret = av_image_check_size(width, height, 0, ଖାଲି);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ପାଇଁ (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    ଫେରନ୍ତୁ av_image_fill_pointers(dst_data, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_image_get_buffer_size(ଗଣନା AVPixelFormat pix_fmt,
                             ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ପୂର୍ଣ୍ଣସଂଖ୍ୟା align)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, i;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ଯଦି (!desc)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, ଖାଲି);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ପାଇଁ (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ret = 0;
    ପାଇଁ (i = 0; i < 4; i++) {
        ଯଦି (sizes[i] > INT_MAX - ret)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        ret += sizes[i];
    }
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_image_copy_to_buffer(uint8_t *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_size,
                            ଅଚଳ uint8_t * ଅଚଳ src_data[4],
                            ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_linesize[4],
                            ଗଣନା AVPixelFormat pix_fmt,
                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ପୂର୍ଣ୍ଣସଂଖ୍ୟା align)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j, nb_planes = 0, linesize[4];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା size = av_image_get_buffer_size(pix_fmt, width, height, align);
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (size > dst_size || size < 0 || !desc)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ପାଇଁ (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    ପାଇଁ (i = 0; i < nb_planes; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        ଅଚଳ uint8_t *src = src_data[i];
        h = AV_CEIL_RSHIFT(height, shift);

        ପାଇଁ (j = 0; j < h; j++) {
            memcpy(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    ଯଦି (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        ପାଇଁ (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_data[1] + 4*i));
    }

    ଫେରନ୍ତୁ size;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
ସ୍ଥିର ଶୂନ୍ୟ memset_bytes(uint8_t *dst, size_t dst_size, uint8_t *clear,
                         size_t clear_size)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା same = 1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ଯଦି (!clear_size)
        ଫେରନ୍ତୁ;

    // Reduce to memset() if possible.
    ପାଇଁ (i = 0; i < clear_size; i++) {
        ଯଦି (clear[i] != clear[0]) {
            same = 0;
            ଭାଙ୍ଗ;
        }
    }
    ଯଦି (same)
        clear_size = 1;

    ଯଦି (clear_size == 1) {
        memset(dst, clear[0], dst_size);
    } ଅନ୍ୟଥା {
        ଯଦି (clear_size > dst_size)
            clear_size = dst_size;
        memcpy(dst, clear, clear_size);
        av_memcpy_backptr(dst + clear_size, clear_size, dst_size - clear_size);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_SIZE 32

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_image_fill_color(uint8_t * ଅଚଳ dst_data[4], ଅଚଳ ptrdiff_t dst_linesize[4],
                        ଗଣନା AVPixelFormat pix_fmt, ଅଚଳ uint32_t color[4],
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_planes = av_pix_fmt_ଗଣନା_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_SIZE] = {{0}}; // clear padding with 0
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା clear_block_size[4] = {0};
    ptrdiff_t plane_ଧାଡ଼ି_bytes[4] = {0};
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା bitstream;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane, c;

    ଯଦି (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    ପାଇଁ (c = 0; c < desc->nb_components; c++) {
        ଅଚଳ AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_size[comp.plane] = FFMAX(clear_block_size[comp.plane], comp.step);

        ଯଦି (clear_block_size[comp.plane] > MAX_BLOCK_SIZE)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    ପାଇଁ (c = 0; c < desc->nb_components; c++) {
        ଅଚଳ AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = (bitstream ? 8 : 1) * clear_block_size[comp.plane] / comp.step;
        uint8_t *c_data[4];
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_SIZE];
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା x;

        ଯଦି (comp.depth > 32)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        ଯଦି (w < 1)
            ଫେରନ୍ତୁ AVERROR(EINVAL);

        ପାଇଁ (x = 0; x < w; x++)
            src_array[x] = color[c];

        ପାଇଁ (x = 0; x < 4; x++)
            c_data[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_data, c_linesize, desc, 0, 0, c, w, 4);
    }

    ପାଇଁ (plane = 0; plane < nb_planes; plane++) {
        plane_ଧାଡ଼ି_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        ଯଦି (plane_ଧାଡ଼ି_bytes[plane] < 0)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ଯଦି (!dst_data)
        ଫେରନ୍ତୁ 0;

    ପାଇଁ (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_ଧାଡ଼ି_bytes[plane];
        uint8_t *data = dst_data[plane];
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        ପାଇଁ (; plane_h > 0; plane_h--) {
            memset_bytes(data, bytewidth, &clear_block[plane][0], clear_block_size[plane]);
            data += dst_linesize[plane];
        }
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_image_fill_black(uint8_t * ଅଚଳ dst_data[4], ଅଚଳ ptrdiff_t dst_linesize[4],
                        ଗଣନା AVPixelFormat pix_fmt, ଗଣନା AVColorRange range,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height)
{
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_planes = av_pix_fmt_ଗଣନା_planes(pix_fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    ଯଦି (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = 0; c < desc->nb_components; c++) {
        ଅଚଳ AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        ଯଦି (comp.depth > 32)
            ଫେରନ୍ତୁ AVERROR(EINVAL);

        ଯଦି (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } ଅନ୍ୟଥା ଯଦି (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            ଯଦି (fltp) {
                ଯଦି (comp.depth != 16 && comp.depth != 32)
                    ଫେରନ୍ତୁ AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } ଅନ୍ୟଥା {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } ଅନ୍ୟଥା ଯଦି (c == 0 && limited && comp.depth > 1) {
            ଯଦି (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                ଫେରନ୍ତୁ AVERROR(EINVAL);
            ଯଦି (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            ଅନ୍ୟଥା
                color = 16 << (comp.depth - 8);
        } ଅନ୍ୟଥା ଯଦି ((c == 1 || c == 2) && !rgb && !xyz) {
            ଯଦି (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                ଫେରନ୍ତୁ AVERROR(EINVAL);
            ଯଦି (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            ଅନ୍ୟଥା
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    ଫେରନ୍ତୁ av_image_fill_color(dst_data, dst_linesize, pix_fmt, colors, width, height, 0);
}
