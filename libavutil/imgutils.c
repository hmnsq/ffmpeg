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

خالی av_image_fill_max_pixsteps(صحیح max_pixsteps[4], صحیح max_pixstep_comps[4],
                                ثابت AVPixFmtDescriptor *pixdesc)
{
    صحیح i;
    memset(max_pixsteps, 0, 4*حجم(max_pixsteps[0]));
    اگر (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*حجم(max_pixstep_comps[0]));

    برائے (i = 0; i < 4; i++) {
        ثابت AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        اگر (comp->قدم > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->قدم;
            اگر (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

ساکن اندرونی
صحیح image_get_linesize(صحیح چوڑائی, صحیح plane,
                       صحیح max_قدم, صحیح max_قدم_comp,
                       ثابت AVPixFmtDescriptor *desc)
{
    صحیح s, shifted_w, linesize;

    اگر (!desc)
        واپس AVERROR(EINVAL);

    اگر (چوڑائی < 0)
        واپس AVERROR(EINVAL);
    s = (max_قدم_comp == 1 || max_قدم_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(چوڑائی, s);
    اگر (shifted_w && max_قدم > زیادہ_سے_زیادہ_عدد / shifted_w)
        واپس AVERROR(EINVAL);
    linesize = max_قدم * shifted_w;

    اگر (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    واپس linesize;
}

صحیح av_image_get_linesize(شمار AVPixelFormat pix_fmt, صحیح چوڑائی, صحیح plane)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحیح max_قدم     [4];       /* max pixel step for each plane */
    صحیح max_قدم_comp[4];       /* the component for each plane which has the max pixel step */

    اگر (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        واپس AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_قدم, max_قدم_comp, desc);
    واپس image_get_linesize(چوڑائی, plane, max_قدم[plane], max_قدم_comp[plane], desc);
}

صحیح av_image_fill_linesizes(صحیح linesizes[4], شمار AVPixelFormat pix_fmt, صحیح چوڑائی)
{
    صحیح i, ret;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحیح max_قدم     [4];       /* max pixel step for each plane */
    صحیح max_قدم_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*حجم(linesizes[0]));

    اگر (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        واپس AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_قدم, max_قدم_comp, desc);
    برائے (i = 0; i < 4; i++) {
        اگر ((ret = image_get_linesize(چوڑائی, i, max_قدم[i], max_قدم_comp[i], desc)) < 0)
            واپس ret;
        linesizes[i] = ret;
    }

    واپس 0;
}

صحیح av_image_fill_plane_sizes(size_t sizes[4], شمار AVPixelFormat pix_fmt,
                              صحیح اونچائی, ثابت ptrdiff_t linesizes[4])
{
    صحیح i, has_plane[4] = { 0 };

    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, حجم(sizes[0])*4);

    اگر (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        واپس AVERROR(EINVAL);

    اگر (linesizes[0] > SIZE_MAX / اونچائی)
        واپس AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)اونچائی;

    اگر (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        واپس 0;
    }

    برائے (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    برائے (i = 1; i < 4 && has_plane[i]; i++) {
        صحیح h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(اونچائی, s);
        اگر (linesizes[i] > SIZE_MAX / h)
            واپس AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    واپس 0;
}

صحیح av_image_fill_اشارے(uint8_t *ڈیٹا[4], شمار AVPixelFormat pix_fmt, صحیح اونچائی,
                           uint8_t *ptr, ثابت صحیح linesizes[4])
{
    صحیح i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(ڈیٹا     , 0, حجم(ڈیٹا[0])*4);

    برائے (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, اونچائی, linesizes1);
    اگر (ret < 0)
        واپس ret;

    ret = 0;
    برائے (i = 0; i < 4; i++) {
        اگر (sizes[i] > زیادہ_سے_زیادہ_عدد - ret)
            واپس AVERROR(EINVAL);
        ret += sizes[i];
    }

    اگر (!ptr)
        واپس ret;

    ڈیٹا[0] = ptr;
    برائے (i = 1; i < 4 && sizes[i]; i++)
        ڈیٹا[i] = ڈیٹا[i - 1] + sizes[i - 1];

    واپس ret;
}

صحیح avpriv_سیٹ_systematic_pal2(uint32_t pal[256], شمار AVPixelFormat pix_fmt)
{
    صحیح i;

    برائے (i = 0; i < 256; i++) {
        صحیح r, g, b;

        انتخاب (pix_fmt) {
        حالت AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            توڑو;
        حالت AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            توڑو;
        حالت AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            توڑو;
        حالت AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            توڑو;
        حالت AV_PIX_FMT_GRAY8:
            r = b = g = i;
            توڑو;
        طےشدہ:
            واپس AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    واپس 0;
}

صحیح av_image_alloc(uint8_t *اشارے[4], صحیح linesizes[4],
                   صحیح w, صحیح h, شمار AVPixelFormat pix_fmt, صحیح align)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحیح i, ret;
    ptrdiff_t linesizes1[4];
    size_t کل_سائز, sizes[4];
    uint8_t *buf;

    اگر (!desc)
        واپس AVERROR(EINVAL);

    اگر ((ret = av_image_check_سائز(w, h, 0, تہی)) < 0)
        واپس ret;
    اگر ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        واپس ret;

    برائے (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    اگر ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        واپس ret;
    کل_سائز = align;
    برائے (i = 0; i < 4; i++) {
        اگر (کل_سائز > SIZE_MAX - sizes[i])
            واپس AVERROR(EINVAL);
        کل_سائز += sizes[i];
    }
    buf = av_malloc(کل_سائز);
    اگر (!buf)
        واپس AVERROR(ENOMEM);
    اگر ((ret = av_image_fill_اشارے(اشارے, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        واپس ret;
    }
    اگر (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_سیٹ_systematic_pal2((uint32_t*)اشارے[1], pix_fmt);
        اگر (align < 4) {
            av_log(تہی, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            واپس AVERROR(EINVAL);
        }
    }

    اگر (desc->flags & AV_PIX_FMT_FLAG_PAL && اشارے[1] &&
        اشارے[1] - اشارے[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(اشارے[0] + linesizes[0] * h, 0,
               اشارے[1] - اشارے[0] - linesizes[0] * h);
    }

    واپس ret;
}

قسمتعریف ساخت ImgUtils {
    ثابت AVClass *class;
    صحیح   log_انحراف;
    خالی *log_ctx;
} ImgUtils;

ساکن ثابت AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .شے_name                 = av_default_شے_name,
    .option                    = تہی,
    .نسخہ                   = LIBAVUTIL_نسخہ_INT,
    .log_level_انحراف_انحراف   = offsetof(ImgUtils, log_انحراف),
    .والد_log_context_انحراف = offsetof(ImgUtils, log_ctx),
};

صحیح av_image_check_size2(غیرعلامتی صحیح w, غیرعلامتی صحیح h, int64_t max_pixels, شمار AVPixelFormat pix_fmt, صحیح log_انحراف, خالی *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_انحراف = log_انحراف,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    اگر (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    اگر (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= زیادہ_سے_زیادہ_عدد || stride*(h + 128ULL) >= زیادہ_سے_زیادہ_عدد) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        واپس AVERROR(EINVAL);
    }

    اگر (max_pixels < INT64_MAX) {
        اگر (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            واپس AVERROR(EINVAL);
        }
    }

    واپس 0;
}

صحیح av_image_check_سائز(غیرعلامتی صحیح w, غیرعلامتی صحیح h, صحیح log_انحراف, خالی *log_ctx)
{
    واپس av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_انحراف, log_ctx);
}

صحیح av_image_check_sar(غیرعلامتی صحیح w, غیرعلامتی صحیح h, AVRational sar)
{
    int64_t scaled_dim;

    اگر (sar.den <= 0 || sar.عدد < 0)
        واپس AVERROR(EINVAL);

    اگر (!sar.عدد || sar.عدد == sar.den)
        واپس 0;

    اگر (sar.عدد < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.عدد, sar.den, AV_باری_ZERO);
    ورنہ
        scaled_dim = av_rescale_rnd(h, sar.den, sar.عدد, AV_باری_ZERO);

    اگر (scaled_dim > 0)
        واپس 0;

    واپس AVERROR(EINVAL);
}

ساکن خالی image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             ثابت uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, صحیح اونچائی)
{
    اگر (!dst || !src)
        واپس;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    برائے (;اونچائی > 0; اونچائی--) {
        حافظہ_نقل(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

خالی av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 ثابت uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, صحیح اونچائی)
{
    صحیح ret = -1;

#اگر ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, اونچائی);
#اگر_ختم

    اگر (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, اونچائی);
}

خالی av_image_copy_plane(uint8_t       *dst, صحیح dst_linesize,
                         ثابت uint8_t *src, صحیح src_linesize,
                         صحیح bytewidth, صحیح اونچائی)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, اونچائی);
}

ساکن خالی image_copy(uint8_t *ثابت dst_ڈیٹا[4], ثابت ptrdiff_t dst_linesizes[4],
                       ثابت uint8_t *ثابت src_ڈیٹا[4], ثابت ptrdiff_t src_linesizes[4],
                       شمار AVPixelFormat pix_fmt, صحیح چوڑائی, صحیح اونچائی,
                       خالی (*copy_plane)(uint8_t *, ptrdiff_t, ثابت uint8_t *,
                                          ptrdiff_t, ptrdiff_t, صحیح))
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    اگر (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        واپس;

    اگر (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_ڈیٹا[0], dst_linesizes[0],
                   src_ڈیٹا[0], src_linesizes[0],
                   چوڑائی, اونچائی);
        /* copy the palette */
        اگر ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_ڈیٹا[1] && src_ڈیٹا[1]))
            حافظہ_نقل(dst_ڈیٹا[1], src_ڈیٹا[1], 4*256);
    } ورنہ {
        صحیح i, planes_nb = 0;

        برائے (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        برائے (i = 0; i < planes_nb; i++) {
            صحیح h = اونچائی;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, چوڑائی, i);
            اگر (bwidth < 0) {
                av_log(تہی, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                واپس;
            }
            اگر (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(اونچائی, desc->log2_chroma_h);
            }
            copy_plane(dst_ڈیٹا[i], dst_linesizes[i],
                       src_ڈیٹا[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

خالی av_image_copy(uint8_t *ثابت dst_ڈیٹا[4], ثابت صحیح dst_linesizes[4],
                   ثابت uint8_t * ثابت src_ڈیٹا[4], ثابت صحیح src_linesizes[4],
                   شمار AVPixelFormat pix_fmt, صحیح چوڑائی, صحیح اونچائی)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    صحیح i;

    برائے (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_ڈیٹا, dst_linesizes1, src_ڈیٹا, src_linesizes1, pix_fmt,
               چوڑائی, اونچائی, image_copy_plane);
}

خالی av_image_copy_uc_from(uint8_t * ثابت dst_ڈیٹا[4], ثابت ptrdiff_t dst_linesizes[4],
                           ثابت uint8_t * ثابت src_ڈیٹا[4], ثابت ptrdiff_t src_linesizes[4],
                           شمار AVPixelFormat pix_fmt, صحیح چوڑائی, صحیح اونچائی)
{
    image_copy(dst_ڈیٹا, dst_linesizes, src_ڈیٹا, src_linesizes, pix_fmt,
               چوڑائی, اونچائی, av_image_copy_plane_uc_from);
}

صحیح av_image_fill_arrays(uint8_t *dst_ڈیٹا[4], صحیح dst_linesize[4],
                         ثابت uint8_t *src, شمار AVPixelFormat pix_fmt,
                         صحیح چوڑائی, صحیح اونچائی, صحیح align)
{
    صحیح ret, i;

    ret = av_image_check_سائز(چوڑائی, اونچائی, 0, تہی);
    اگر (ret < 0)
        واپس ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, چوڑائی);
    اگر (ret < 0)
        واپس ret;

    برائے (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    واپس av_image_fill_اشارے(dst_ڈیٹا, pix_fmt, اونچائی, (uint8_t *)src, dst_linesize);
}

صحیح av_image_get_بفر_سائز(شمار AVPixelFormat pix_fmt,
                             صحیح چوڑائی, صحیح اونچائی, صحیح align)
{
    صحیح ret, i;
    صحیح linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    اگر (!desc)
        واپس AVERROR(EINVAL);

    ret = av_image_check_سائز(چوڑائی, اونچائی, 0, تہی);
    اگر (ret < 0)
        واپس ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, چوڑائی);
    اگر (ret < 0)
        واپس ret;

    برائے (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, اونچائی, aligned_linesize);
    اگر (ret < 0)
        واپس ret;

    ret = 0;
    برائے (i = 0; i < 4; i++) {
        اگر (sizes[i] > زیادہ_سے_زیادہ_عدد - ret)
            واپس AVERROR(EINVAL);
        ret += sizes[i];
    }
    واپس ret;
}

صحیح av_image_copy_مقصد_بفر(uint8_t *dst, صحیح dst_سائز,
                            ثابت uint8_t * ثابت src_ڈیٹا[4],
                            ثابت صحیح src_linesize[4],
                            شمار AVPixelFormat pix_fmt,
                            صحیح چوڑائی, صحیح اونچائی, صحیح align)
{
    صحیح i, j, nb_planes = 0, linesize[4];
    صحیح سائز = av_image_get_بفر_سائز(pix_fmt, چوڑائی, اونچائی, align);
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحیح ret;

    اگر (سائز > dst_سائز || سائز < 0 || !desc)
        واپس AVERROR(EINVAL);

    برائے (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, چوڑائی);
    av_assert0(ret >= 0); // was checked previously

    برائے (i = 0; i < nb_planes; i++) {
        صحیح h, سرکاؤ = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        ثابت uint8_t *src = src_ڈیٹا[i];
        h = AV_CEIL_RSHIFT(اونچائی, سرکاؤ);

        برائے (j = 0; j < h; j++) {
            حافظہ_نقل(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    اگر (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        برائے (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_ڈیٹا[1] + 4*i));
    }

    واپس سائز;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
ساکن خالی memset_بائٹیں(uint8_t *dst, size_t dst_سائز, uint8_t *clear,
                         size_t clear_سائز)
{
    صحیح same = 1;
    صحیح i;

    اگر (!clear_سائز)
        واپس;

    // Reduce to memset() if possible.
    برائے (i = 0; i < clear_سائز; i++) {
        اگر (clear[i] != clear[0]) {
            same = 0;
            توڑو;
        }
    }
    اگر (same)
        clear_سائز = 1;

    اگر (clear_سائز == 1) {
        memset(dst, clear[0], dst_سائز);
    } ورنہ {
        اگر (clear_سائز > dst_سائز)
            clear_سائز = dst_سائز;
        حافظہ_نقل(dst, clear, clear_سائز);
        av_memcpy_backptr(dst + clear_سائز, clear_سائز, dst_سائز - clear_سائز);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#تعریف_کرو MAX_بلاک_سائز 32

صحیح av_image_fill_color(uint8_t * ثابت dst_ڈیٹا[4], ثابت ptrdiff_t dst_linesize[4],
                        شمار AVPixelFormat pix_fmt, ثابت uint32_t color[4],
                        صحیح چوڑائی, صحیح اونچائی, صحیح flags)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحیح nb_planes = av_pix_fmt_گنتی_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_بلاک[4][MAX_بلاک_سائز] = {{0}}; // clear padding with 0
    صحیح clear_بلاک_سائز[4] = {0};
    ptrdiff_t plane_سطر_بائٹیں[4] = {0};
    صحیح bitstream;
    صحیح plane, c;

    اگر (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        واپس AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    برائے (c = 0; c < desc->nb_components; c++) {
        ثابت AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_بلاک_سائز[comp.plane] = FFMAX(clear_بلاک_سائز[comp.plane], comp.قدم);

        اگر (clear_بلاک_سائز[comp.plane] > MAX_بلاک_سائز)
            واپس AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    برائے (c = 0; c < desc->nb_components; c++) {
        ثابت AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        صحیح w = (bitstream ? 8 : 1) * clear_بلاک_سائز[comp.plane] / comp.قدم;
        uint8_t *c_ڈیٹا[4];
        ثابت صحیح c_linesize[4] = {0};
        uint32_t src_array[MAX_بلاک_سائز];
        صحیح x;

        اگر (comp.گہرائی > 32)
            واپس AVERROR(EINVAL);
        اگر (w < 1)
            واپس AVERROR(EINVAL);

        برائے (x = 0; x < w; x++)
            src_array[x] = color[c];

        برائے (x = 0; x < 4; x++)
            c_ڈیٹا[x] = &clear_بلاک[x][0];

        av_write_image_line2(src_array, c_ڈیٹا, c_linesize, desc, 0, 0, c, w, 4);
    }

    برائے (plane = 0; plane < nb_planes; plane++) {
        plane_سطر_بائٹیں[plane] = av_image_get_linesize(pix_fmt, چوڑائی, plane);
        اگر (plane_سطر_بائٹیں[plane] < 0)
            واپس AVERROR(EINVAL);
    }

    اگر (!dst_ڈیٹا)
        واپس 0;

    برائے (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_سطر_بائٹیں[plane];
        uint8_t *ڈیٹا = dst_ڈیٹا[plane];
        صحیح chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        صحیح plane_h = AV_CEIL_RSHIFT(اونچائی, chroma_div);

        برائے (; plane_h > 0; plane_h--) {
            memset_بائٹیں(ڈیٹا, bytewidth, &clear_بلاک[plane][0], clear_بلاک_سائز[plane]);
            ڈیٹا += dst_linesize[plane];
        }
    }

    واپس 0;
}

صحیح av_image_fill_black(uint8_t * ثابت dst_ڈیٹا[4], ثابت ptrdiff_t dst_linesize[4],
                        شمار AVPixelFormat pix_fmt, شمار AVColorRange range,
                        صحیح چوڑائی, صحیح اونچائی)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحیح nb_planes = av_pix_fmt_گنتی_planes(pix_fmt);
    صحیح rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    اگر (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        واپس AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    برائے (صحیح c = 0; c < desc->nb_components; c++) {
        ثابت AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        اگر (comp.گہرائی > 32)
            واپس AVERROR(EINVAL);

        اگر (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } ورنہ اگر (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            اگر (fltp) {
                اگر (comp.گہرائی != 16 && comp.گہرائی != 32)
                    واپس AVERROR(EINVAL);
                color = (comp.گہرائی == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } ورنہ {
                color = (comp.گہرائی == 32 ? 0 : (1 << comp.گہرائی)) - 1;
             }
        } ورنہ اگر (c == 0 && limited && comp.گہرائی > 1) {
            اگر (comp.گہرائی < 8 || (fltp && comp.گہرائی != 16 && comp.گہرائی != 32))
                واپس AVERROR(EINVAL);
            اگر (fltp)
                color = (comp.گہرائی == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            ورنہ
                color = 16 << (comp.گہرائی - 8);
        } ورنہ اگر ((c == 1 || c == 2) && !rgb && !xyz) {
            اگر (comp.گہرائی < 8 || fltp && comp.گہرائی != 16 && comp.گہرائی != 32)
                واپس AVERROR(EINVAL);
            اگر (fltp)
                color = (comp.گہرائی == 16 ? 0x3800 : 0x3F000000); // 0.5
            ورنہ
                color = 128 << (comp.گہرائی - 8);
        }

        colors[c] = color;
    }

    واپس av_image_fill_color(dst_ڈیٹا, dst_linesize, pix_fmt, colors, چوڑائی, اونچائی, 0);
}
