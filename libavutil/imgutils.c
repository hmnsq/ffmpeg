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

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "imgutils.h"
#അന്തര്ഭാവ "imgutils_internal.h"
#അന്തര്ഭാവ "intreadwrite.h"
#അന്തര്ഭാവ "log.h"
#അന്തര്ഭാവ "mathematics.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "pixdesc.h"
#അന്തര്ഭാവ "rational.h"

ശൂന്യം av_image_fill_max_pixsteps(പൂർണ്ണസംഖ്യ max_pixsteps[4], പൂർണ്ണസംഖ്യ max_pixstep_comps[4],
                                സ്ഥിരം AVPixFmtDescriptor *pixdesc)
{
    പൂർണ്ണസംഖ്യ i;
    memset(max_pixsteps, 0, 4*വലുപ്പം(max_pixsteps[0]));
    എങ്കിൽ (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*വലുപ്പം(max_pixstep_comps[0]));

    വേണ്ടി (i = 0; i < 4; i++) {
        സ്ഥിരം AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        എങ്കിൽ (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            എങ്കിൽ (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

സ്ഥിതം വരിയിൽ
പൂർണ്ണസംഖ്യ image_get_linesize(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ plane,
                       പൂർണ്ണസംഖ്യ max_step, പൂർണ്ണസംഖ്യ max_step_comp,
                       സ്ഥിരം AVPixFmtDescriptor *desc)
{
    പൂർണ്ണസംഖ്യ s, shifted_w, linesize;

    എങ്കിൽ (!desc)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (width < 0)
        തിരികെ AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    എങ്കിൽ (shifted_w && max_step > INT_MAX / shifted_w)
        തിരികെ AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    എങ്കിൽ (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    തിരികെ linesize;
}

പൂർണ്ണസംഖ്യ av_image_get_linesize(എണ്ണൽ AVPixelFormat pix_fmt, പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ plane)
{
    സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    പൂർണ്ണസംഖ്യ max_step     [4];       /* max pixel step for each plane */
    പൂർണ്ണസംഖ്യ max_step_comp[4];       /* the component for each plane which has the max pixel step */

    എങ്കിൽ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        തിരികെ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    തിരികെ image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

പൂർണ്ണസംഖ്യ av_image_fill_linesizes(പൂർണ്ണസംഖ്യ linesizes[4], എണ്ണൽ AVPixelFormat pix_fmt, പൂർണ്ണസംഖ്യ width)
{
    പൂർണ്ണസംഖ്യ i, ret;
    സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    പൂർണ്ണസംഖ്യ max_step     [4];       /* max pixel step for each plane */
    പൂർണ്ണസംഖ്യ max_step_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*വലുപ്പം(linesizes[0]));

    എങ്കിൽ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        തിരികെ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    വേണ്ടി (i = 0; i < 4; i++) {
        എങ്കിൽ ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            തിരികെ ret;
        linesizes[i] = ret;
    }

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_image_fill_plane_sizes(size_t sizes[4], എണ്ണൽ AVPixelFormat pix_fmt,
                              പൂർണ്ണസംഖ്യ height, സ്ഥിരം ptrdiff_t linesizes[4])
{
    പൂർണ്ണസംഖ്യ i, has_plane[4] = { 0 };

    സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, വലുപ്പം(sizes[0])*4);

    എങ്കിൽ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (linesizes[0] > SIZE_MAX / height)
        തിരികെ AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)height;

    എങ്കിൽ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        തിരികെ 0;
    }

    വേണ്ടി (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    വേണ്ടി (i = 1; i < 4 && has_plane[i]; i++) {
        പൂർണ്ണസംഖ്യ h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        എങ്കിൽ (linesizes[i] > SIZE_MAX / h)
            തിരികെ AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_image_fill_pointers(uint8_t *data[4], എണ്ണൽ AVPixelFormat pix_fmt, പൂർണ്ണസംഖ്യ height,
                           uint8_t *ptr, സ്ഥിരം പൂർണ്ണസംഖ്യ linesizes[4])
{
    പൂർണ്ണസംഖ്യ i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(data     , 0, വലുപ്പം(data[0])*4);

    വേണ്ടി (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    ret = 0;
    വേണ്ടി (i = 0; i < 4; i++) {
        എങ്കിൽ (sizes[i] > INT_MAX - ret)
            തിരികെ AVERROR(EINVAL);
        ret += sizes[i];
    }

    എങ്കിൽ (!ptr)
        തിരികെ ret;

    data[0] = ptr;
    വേണ്ടി (i = 1; i < 4 && sizes[i]; i++)
        data[i] = data[i - 1] + sizes[i - 1];

    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ avpriv_set_systematic_pal2(uint32_t pal[256], എണ്ണൽ AVPixelFormat pix_fmt)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < 256; i++) {
        പൂർണ്ണസംഖ്യ r, g, b;

        തിരഞ്ഞെടുപ്പ് (pix_fmt) {
        അവസ്ഥ AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            നിർത്തുക;
        അവസ്ഥ AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            നിർത്തുക;
        അവസ്ഥ AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            നിർത്തുക;
        അവസ്ഥ AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            നിർത്തുക;
        അവസ്ഥ AV_PIX_FMT_GRAY8:
            r = b = g = i;
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            തിരികെ AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_image_alloc(uint8_t *pointers[4], പൂർണ്ണസംഖ്യ linesizes[4],
                   പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h, എണ്ണൽ AVPixelFormat pix_fmt, പൂർണ്ണസംഖ്യ align)
{
    സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    പൂർണ്ണസംഖ്യ i, ret;
    ptrdiff_t linesizes1[4];
    size_t total_size, sizes[4];
    uint8_t *buf;

    എങ്കിൽ (!desc)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ ((ret = av_image_check_size(w, h, 0, ശൂന്യ)) < 0)
        തിരികെ ret;
    എങ്കിൽ ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        തിരികെ ret;

    വേണ്ടി (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    എങ്കിൽ ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        തിരികെ ret;
    total_size = align;
    വേണ്ടി (i = 0; i < 4; i++) {
        എങ്കിൽ (total_size > SIZE_MAX - sizes[i])
            തിരികെ AVERROR(EINVAL);
        total_size += sizes[i];
    }
    buf = av_malloc(total_size);
    എങ്കിൽ (!buf)
        തിരികെ AVERROR(ENOMEM);
    എങ്കിൽ ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        തിരികെ ret;
    }
    എങ്കിൽ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        എങ്കിൽ (align < 4) {
            av_log(ശൂന്യ, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            തിരികെ AVERROR(EINVAL);
        }
    }

    എങ്കിൽ (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    തിരികെ ret;
}

തരനിർവചനം ഘടന ImgUtils {
    സ്ഥിരം AVClass *class;
    പൂർണ്ണസംഖ്യ   log_offset;
    ശൂന്യം *log_ctx;
} ImgUtils;

സ്ഥിതം സ്ഥിരം AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .item_name                 = av_default_item_name,
    .option                    = ശൂന്യ,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(ImgUtils, log_offset),
    .parent_log_context_offset = offsetof(ImgUtils, log_ctx),
};

പൂർണ്ണസംഖ്യ av_image_check_size2(unsigned പൂർണ്ണസംഖ്യ w, unsigned പൂർണ്ണസംഖ്യ h, int64_t max_pixels, എണ്ണൽ AVPixelFormat pix_fmt, പൂർണ്ണസംഖ്യ log_offset, ശൂന്യം *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    എങ്കിൽ (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    എങ്കിൽ (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= INT_MAX || stride*(h + 128ULL) >= INT_MAX) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        തിരികെ AVERROR(EINVAL);
    }

    എങ്കിൽ (max_pixels < INT64_MAX) {
        എങ്കിൽ (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            തിരികെ AVERROR(EINVAL);
        }
    }

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_image_check_size(unsigned പൂർണ്ണസംഖ്യ w, unsigned പൂർണ്ണസംഖ്യ h, പൂർണ്ണസംഖ്യ log_offset, ശൂന്യം *log_ctx)
{
    തിരികെ av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

പൂർണ്ണസംഖ്യ av_image_check_sar(unsigned പൂർണ്ണസംഖ്യ w, unsigned പൂർണ്ണസംഖ്യ h, AVRational sar)
{
    int64_t scaled_dim;

    എങ്കിൽ (sar.den <= 0 || sar.അക്കം < 0)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (!sar.അക്കം || sar.അക്കം == sar.den)
        തിരികെ 0;

    എങ്കിൽ (sar.അക്കം < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.അക്കം, sar.den, AV_ROUND_ZERO);
    അല്ലെങ്കിൽ
        scaled_dim = av_rescale_rnd(h, sar.den, sar.അക്കം, AV_ROUND_ZERO);

    എങ്കിൽ (scaled_dim > 0)
        തിരികെ 0;

    തിരികെ AVERROR(EINVAL);
}

സ്ഥിതം ശൂന്യം image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             സ്ഥിരം uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, പൂർണ്ണസംഖ്യ height)
{
    എങ്കിൽ (!dst || !src)
        തിരികെ;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    വേണ്ടി (;height > 0; height--) {
        memcpy(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

ശൂന്യം av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 സ്ഥിരം uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, പൂർണ്ണസംഖ്യ height)
{
    പൂർണ്ണസംഖ്യ ret = -1;

#എങ്കിൽ ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#endif

    എങ്കിൽ (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

ശൂന്യം av_image_copy_plane(uint8_t       *dst, പൂർണ്ണസംഖ്യ dst_linesize,
                         സ്ഥിരം uint8_t *src, പൂർണ്ണസംഖ്യ src_linesize,
                         പൂർണ്ണസംഖ്യ bytewidth, പൂർണ്ണസംഖ്യ height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

സ്ഥിതം ശൂന്യം image_copy(uint8_t *സ്ഥിരം dst_data[4], സ്ഥിരം ptrdiff_t dst_linesizes[4],
                       സ്ഥിരം uint8_t *സ്ഥിരം src_data[4], സ്ഥിരം ptrdiff_t src_linesizes[4],
                       എണ്ണൽ AVPixelFormat pix_fmt, പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height,
                       ശൂന്യം (*copy_plane)(uint8_t *, ptrdiff_t, സ്ഥിരം uint8_t *,
                                          ptrdiff_t, ptrdiff_t, പൂർണ്ണസംഖ്യ))
{
    സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    എങ്കിൽ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        തിരികെ;

    എങ്കിൽ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_data[0], dst_linesizes[0],
                   src_data[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        എങ്കിൽ ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_data[1] && src_data[1]))
            memcpy(dst_data[1], src_data[1], 4*256);
    } അല്ലെങ്കിൽ {
        പൂർണ്ണസംഖ്യ i, planes_nb = 0;

        വേണ്ടി (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        വേണ്ടി (i = 0; i < planes_nb; i++) {
            പൂർണ്ണസംഖ്യ h = height;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, width, i);
            എങ്കിൽ (bwidth < 0) {
                av_log(ശൂന്യ, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                തിരികെ;
            }
            എങ്കിൽ (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_data[i], dst_linesizes[i],
                       src_data[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

ശൂന്യം av_image_copy(uint8_t *സ്ഥിരം dst_data[4], സ്ഥിരം പൂർണ്ണസംഖ്യ dst_linesizes[4],
                   സ്ഥിരം uint8_t * സ്ഥിരം src_data[4], സ്ഥിരം പൂർണ്ണസംഖ്യ src_linesizes[4],
                   എണ്ണൽ AVPixelFormat pix_fmt, പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

ശൂന്യം av_image_copy_uc_from(uint8_t * സ്ഥിരം dst_data[4], സ്ഥിരം ptrdiff_t dst_linesizes[4],
                           സ്ഥിരം uint8_t * സ്ഥിരം src_data[4], സ്ഥിരം ptrdiff_t src_linesizes[4],
                           എണ്ണൽ AVPixelFormat pix_fmt, പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height)
{
    image_copy(dst_data, dst_linesizes, src_data, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

പൂർണ്ണസംഖ്യ av_image_fill_arrays(uint8_t *dst_data[4], പൂർണ്ണസംഖ്യ dst_linesize[4],
                         സ്ഥിരം uint8_t *src, എണ്ണൽ AVPixelFormat pix_fmt,
                         പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, പൂർണ്ണസംഖ്യ align)
{
    പൂർണ്ണസംഖ്യ ret, i;

    ret = av_image_check_size(width, height, 0, ശൂന്യ);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    വേണ്ടി (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    തിരികെ av_image_fill_pointers(dst_data, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

പൂർണ്ണസംഖ്യ av_image_get_buffer_size(എണ്ണൽ AVPixelFormat pix_fmt,
                             പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, പൂർണ്ണസംഖ്യ align)
{
    പൂർണ്ണസംഖ്യ ret, i;
    പൂർണ്ണസംഖ്യ linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    എങ്കിൽ (!desc)
        തിരികെ AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, ശൂന്യ);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    വേണ്ടി (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    ret = 0;
    വേണ്ടി (i = 0; i < 4; i++) {
        എങ്കിൽ (sizes[i] > INT_MAX - ret)
            തിരികെ AVERROR(EINVAL);
        ret += sizes[i];
    }
    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_image_copy_to_buffer(uint8_t *dst, പൂർണ്ണസംഖ്യ dst_size,
                            സ്ഥിരം uint8_t * സ്ഥിരം src_data[4],
                            സ്ഥിരം പൂർണ്ണസംഖ്യ src_linesize[4],
                            എണ്ണൽ AVPixelFormat pix_fmt,
                            പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, പൂർണ്ണസംഖ്യ align)
{
    പൂർണ്ണസംഖ്യ i, j, nb_planes = 0, linesize[4];
    പൂർണ്ണസംഖ്യ size = av_image_get_buffer_size(pix_fmt, width, height, align);
    സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (size > dst_size || size < 0 || !desc)
        തിരികെ AVERROR(EINVAL);

    വേണ്ടി (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    വേണ്ടി (i = 0; i < nb_planes; i++) {
        പൂർണ്ണസംഖ്യ h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        സ്ഥിരം uint8_t *src = src_data[i];
        h = AV_CEIL_RSHIFT(height, shift);

        വേണ്ടി (j = 0; j < h; j++) {
            memcpy(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    എങ്കിൽ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        വേണ്ടി (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_data[1] + 4*i));
    }

    തിരികെ size;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
സ്ഥിതം ശൂന്യം memset_bytes(uint8_t *dst, size_t dst_size, uint8_t *clear,
                         size_t clear_size)
{
    പൂർണ്ണസംഖ്യ same = 1;
    പൂർണ്ണസംഖ്യ i;

    എങ്കിൽ (!clear_size)
        തിരികെ;

    // Reduce to memset() if possible.
    വേണ്ടി (i = 0; i < clear_size; i++) {
        എങ്കിൽ (clear[i] != clear[0]) {
            same = 0;
            നിർത്തുക;
        }
    }
    എങ്കിൽ (same)
        clear_size = 1;

    എങ്കിൽ (clear_size == 1) {
        memset(dst, clear[0], dst_size);
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (clear_size > dst_size)
            clear_size = dst_size;
        memcpy(dst, clear, clear_size);
        av_memcpy_backptr(dst + clear_size, clear_size, dst_size - clear_size);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#define MAX_BLOCK_SIZE 32

പൂർണ്ണസംഖ്യ av_image_fill_color(uint8_t * സ്ഥിരം dst_data[4], സ്ഥിരം ptrdiff_t dst_linesize[4],
                        എണ്ണൽ AVPixelFormat pix_fmt, സ്ഥിരം uint32_t color[4],
                        പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, പൂർണ്ണസംഖ്യ flags)
{
    സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    പൂർണ്ണസംഖ്യ nb_planes = av_pix_fmt_എണ്ണം_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_SIZE] = {{0}}; // clear padding with 0
    പൂർണ്ണസംഖ്യ clear_block_size[4] = {0};
    ptrdiff_t plane_വരി_bytes[4] = {0};
    പൂർണ്ണസംഖ്യ bitstream;
    പൂർണ്ണസംഖ്യ plane, c;

    എങ്കിൽ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        തിരികെ AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    വേണ്ടി (c = 0; c < desc->nb_components; c++) {
        സ്ഥിരം AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_size[comp.plane] = FFMAX(clear_block_size[comp.plane], comp.step);

        എങ്കിൽ (clear_block_size[comp.plane] > MAX_BLOCK_SIZE)
            തിരികെ AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    വേണ്ടി (c = 0; c < desc->nb_components; c++) {
        സ്ഥിരം AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        പൂർണ്ണസംഖ്യ w = (bitstream ? 8 : 1) * clear_block_size[comp.plane] / comp.step;
        uint8_t *c_data[4];
        സ്ഥിരം പൂർണ്ണസംഖ്യ c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_SIZE];
        പൂർണ്ണസംഖ്യ x;

        എങ്കിൽ (comp.depth > 32)
            തിരികെ AVERROR(EINVAL);
        എങ്കിൽ (w < 1)
            തിരികെ AVERROR(EINVAL);

        വേണ്ടി (x = 0; x < w; x++)
            src_array[x] = color[c];

        വേണ്ടി (x = 0; x < 4; x++)
            c_data[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_data, c_linesize, desc, 0, 0, c, w, 4);
    }

    വേണ്ടി (plane = 0; plane < nb_planes; plane++) {
        plane_വരി_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        എങ്കിൽ (plane_വരി_bytes[plane] < 0)
            തിരികെ AVERROR(EINVAL);
    }

    എങ്കിൽ (!dst_data)
        തിരികെ 0;

    വേണ്ടി (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_വരി_bytes[plane];
        uint8_t *data = dst_data[plane];
        പൂർണ്ണസംഖ്യ chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        പൂർണ്ണസംഖ്യ plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        വേണ്ടി (; plane_h > 0; plane_h--) {
            memset_bytes(data, bytewidth, &clear_block[plane][0], clear_block_size[plane]);
            data += dst_linesize[plane];
        }
    }

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_image_fill_black(uint8_t * സ്ഥിരം dst_data[4], സ്ഥിരം ptrdiff_t dst_linesize[4],
                        എണ്ണൽ AVPixelFormat pix_fmt, എണ്ണൽ AVColorRange range,
                        പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height)
{
    സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    പൂർണ്ണസംഖ്യ nb_planes = av_pix_fmt_എണ്ണം_planes(pix_fmt);
    പൂർണ്ണസംഖ്യ rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    എങ്കിൽ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        തിരികെ AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    വേണ്ടി (പൂർണ്ണസംഖ്യ c = 0; c < desc->nb_components; c++) {
        സ്ഥിരം AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        എങ്കിൽ (comp.depth > 32)
            തിരികെ AVERROR(EINVAL);

        എങ്കിൽ (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } അല്ലെങ്കിൽ എങ്കിൽ (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            എങ്കിൽ (fltp) {
                എങ്കിൽ (comp.depth != 16 && comp.depth != 32)
                    തിരികെ AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } അല്ലെങ്കിൽ {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } അല്ലെങ്കിൽ എങ്കിൽ (c == 0 && limited && comp.depth > 1) {
            എങ്കിൽ (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                തിരികെ AVERROR(EINVAL);
            എങ്കിൽ (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            അല്ലെങ്കിൽ
                color = 16 << (comp.depth - 8);
        } അല്ലെങ്കിൽ എങ്കിൽ ((c == 1 || c == 2) && !rgb && !xyz) {
            എങ്കിൽ (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                തിരികെ AVERROR(EINVAL);
            എങ്കിൽ (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            അല്ലെങ്കിൽ
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    തിരികെ av_image_fill_color(dst_data, dst_linesize, pix_fmt, colors, width, height, 0);
}
