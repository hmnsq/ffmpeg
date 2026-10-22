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

#ضمن "avassert.h"
#ضمن "common.h"
#ضمن "imgutils.h"
#ضمن "imgutils_internal.h"
#ضمن "intreadwrite.h"
#ضمن "log.h"
#ضمن "mathematics.h"
#ضمن "mem.h"
#ضمن "pixdesc.h"
#ضمن "rational.h"

فراغ av_image_fill_max_pixsteps(صحيح max_pixsteps[4], صحيح max_pixstep_comps[4],
                                ثابت AVPixFmtDescriptor *pixdesc)
{
    صحيح i;
    memset(max_pixsteps, 0, 4*حجم(max_pixsteps[0]));
    إذا (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*حجم(max_pixstep_comps[0]));

    لكل (i = 0; i < 4; i++) {
        ثابت AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        إذا (comp->ګام > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->ګام;
            إذا (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

ساكن مضمن
صحيح image_get_linesize(صحيح پلنوالی, صحيح plane,
                       صحيح max_ګام, صحيح max_ګام_comp,
                       ثابت AVPixFmtDescriptor *desc)
{
    صحيح s, shifted_w, linesize;

    إذا (!desc)
        أرجع AVERROR(EINVAL);

    إذا (پلنوالی < 0)
        أرجع AVERROR(EINVAL);
    s = (max_ګام_comp == 1 || max_ګام_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(پلنوالی, s);
    إذا (shifted_w && max_ګام > لوی_عدد / shifted_w)
        أرجع AVERROR(EINVAL);
    linesize = max_ګام * shifted_w;

    إذا (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    أرجع linesize;
}

صحيح av_image_get_linesize(تعداد AVPixelFormat pix_fmt, صحيح پلنوالی, صحيح plane)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحيح max_ګام     [4];       /* max pixel step for each plane */
    صحيح max_ګام_comp[4];       /* the component for each plane which has the max pixel step */

    إذا (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        أرجع AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_ګام, max_ګام_comp, desc);
    أرجع image_get_linesize(پلنوالی, plane, max_ګام[plane], max_ګام_comp[plane], desc);
}

صحيح av_image_fill_linesizes(صحيح linesizes[4], تعداد AVPixelFormat pix_fmt, صحيح پلنوالی)
{
    صحيح i, ret;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحيح max_ګام     [4];       /* max pixel step for each plane */
    صحيح max_ګام_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*حجم(linesizes[0]));

    إذا (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        أرجع AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_ګام, max_ګام_comp, desc);
    لكل (i = 0; i < 4; i++) {
        إذا ((ret = image_get_linesize(پلنوالی, i, max_ګام[i], max_ګام_comp[i], desc)) < 0)
            أرجع ret;
        linesizes[i] = ret;
    }

    أرجع 0;
}

صحيح av_image_fill_plane_sizes(size_t sizes[4], تعداد AVPixelFormat pix_fmt,
                              صحيح لوړوالی, ثابت ptrdiff_t linesizes[4])
{
    صحيح i, has_plane[4] = { 0 };

    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, حجم(sizes[0])*4);

    إذا (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        أرجع AVERROR(EINVAL);

    إذا (linesizes[0] > SIZE_MAX / لوړوالی)
        أرجع AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)لوړوالی;

    إذا (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        أرجع 0;
    }

    لكل (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    لكل (i = 1; i < 4 && has_plane[i]; i++) {
        صحيح h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(لوړوالی, s);
        إذا (linesizes[i] > SIZE_MAX / h)
            أرجع AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    أرجع 0;
}

صحيح av_image_fill_اشارې(uint8_t *معلومات[4], تعداد AVPixelFormat pix_fmt, صحيح لوړوالی,
                           uint8_t *ptr, ثابت صحيح linesizes[4])
{
    صحيح i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(معلومات     , 0, حجم(معلومات[0])*4);

    لكل (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, لوړوالی, linesizes1);
    إذا (ret < 0)
        أرجع ret;

    ret = 0;
    لكل (i = 0; i < 4; i++) {
        إذا (sizes[i] > لوی_عدد - ret)
            أرجع AVERROR(EINVAL);
        ret += sizes[i];
    }

    إذا (!ptr)
        أرجع ret;

    معلومات[0] = ptr;
    لكل (i = 1; i < 4 && sizes[i]; i++)
        معلومات[i] = معلومات[i - 1] + sizes[i - 1];

    أرجع ret;
}

صحيح avpriv_سېټ_systematic_pal2(uint32_t pal[256], تعداد AVPixelFormat pix_fmt)
{
    صحيح i;

    لكل (i = 0; i < 256; i++) {
        صحيح r, g, b;

        بدل (pix_fmt) {
        حالة AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            اكسر;
        حالة AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            اكسر;
        حالة AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            اكسر;
        حالة AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            اكسر;
        حالة AV_PIX_FMT_GRAY8:
            r = b = g = i;
            اكسر;
        افتراضي:
            أرجع AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    أرجع 0;
}

صحيح av_image_alloc(uint8_t *اشارې[4], صحيح linesizes[4],
                   صحيح w, صحيح h, تعداد AVPixelFormat pix_fmt, صحيح align)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحيح i, ret;
    ptrdiff_t linesizes1[4];
    size_t ټول_اندازه, sizes[4];
    uint8_t *buf;

    إذا (!desc)
        أرجع AVERROR(EINVAL);

    إذا ((ret = av_image_check_اندازه(w, h, 0, عدم)) < 0)
        أرجع ret;
    إذا ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        أرجع ret;

    لكل (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    إذا ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        أرجع ret;
    ټول_اندازه = align;
    لكل (i = 0; i < 4; i++) {
        إذا (ټول_اندازه > SIZE_MAX - sizes[i])
            أرجع AVERROR(EINVAL);
        ټول_اندازه += sizes[i];
    }
    buf = av_malloc(ټول_اندازه);
    إذا (!buf)
        أرجع AVERROR(ENOMEM);
    إذا ((ret = av_image_fill_اشارې(اشارې, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        أرجع ret;
    }
    إذا (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_سېټ_systematic_pal2((uint32_t*)اشارې[1], pix_fmt);
        إذا (align < 4) {
            av_log(عدم, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            أرجع AVERROR(EINVAL);
        }
    }

    إذا (desc->flags & AV_PIX_FMT_FLAG_PAL && اشارې[1] &&
        اشارې[1] - اشارې[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(اشارې[0] + linesizes[0] * h, 0,
               اشارې[1] - اشارې[0] - linesizes[0] * h);
    }

    أرجع ret;
}

تعريفنوع بنية ImgUtils {
    ثابت AVClass *class;
    صحيح   log_دننه_واټن;
    فراغ *log_ctx;
} ImgUtils;

ساكن ثابت AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .توکی_name                 = av_default_توکی_name,
    .option                    = عدم,
    .نسخه                   = LIBAVUTIL_نسخه_INT,
    .log_level_دننه_واټن_دننه_واټن   = offsetof(ImgUtils, log_دننه_واټن),
    .پلار_log_context_دننه_واټن = offsetof(ImgUtils, log_ctx),
};

صحيح av_image_check_size2(بینښه صحيح w, بینښه صحيح h, int64_t max_pixels, تعداد AVPixelFormat pix_fmt, صحيح log_دننه_واټن, فراغ *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_دننه_واټن = log_دننه_واټن,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    إذا (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    إذا (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= لوی_عدد || stride*(h + 128ULL) >= لوی_عدد) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        أرجع AVERROR(EINVAL);
    }

    إذا (max_pixels < INT64_MAX) {
        إذا (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            أرجع AVERROR(EINVAL);
        }
    }

    أرجع 0;
}

صحيح av_image_check_اندازه(بینښه صحيح w, بینښه صحيح h, صحيح log_دننه_واټن, فراغ *log_ctx)
{
    أرجع av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_دننه_واټن, log_ctx);
}

صحيح av_image_check_sar(بینښه صحيح w, بینښه صحيح h, AVRational sar)
{
    int64_t scaled_dim;

    إذا (sar.den <= 0 || sar.عدد < 0)
        أرجع AVERROR(EINVAL);

    إذا (!sar.عدد || sar.عدد == sar.den)
        أرجع 0;

    إذا (sar.عدد < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.عدد, sar.den, AV_پړاو_ZERO);
    وإلا
        scaled_dim = av_rescale_rnd(h, sar.den, sar.عدد, AV_پړاو_ZERO);

    إذا (scaled_dim > 0)
        أرجع 0;

    أرجع AVERROR(EINVAL);
}

ساكن فراغ image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             ثابت uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, صحيح لوړوالی)
{
    إذا (!dst || !src)
        أرجع;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    لكل (;لوړوالی > 0; لوړوالی--) {
        حافظه_نقل(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

فراغ av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 ثابت uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, صحيح لوړوالی)
{
    صحيح ret = -1;

#إذا ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, لوړوالی);
#د_که_پای

    إذا (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, لوړوالی);
}

فراغ av_image_copy_plane(uint8_t       *dst, صحيح dst_linesize,
                         ثابت uint8_t *src, صحيح src_linesize,
                         صحيح bytewidth, صحيح لوړوالی)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, لوړوالی);
}

ساكن فراغ image_copy(uint8_t *ثابت dst_معلومات[4], ثابت ptrdiff_t dst_linesizes[4],
                       ثابت uint8_t *ثابت src_معلومات[4], ثابت ptrdiff_t src_linesizes[4],
                       تعداد AVPixelFormat pix_fmt, صحيح پلنوالی, صحيح لوړوالی,
                       فراغ (*copy_plane)(uint8_t *, ptrdiff_t, ثابت uint8_t *,
                                          ptrdiff_t, ptrdiff_t, صحيح))
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    إذا (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        أرجع;

    إذا (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_معلومات[0], dst_linesizes[0],
                   src_معلومات[0], src_linesizes[0],
                   پلنوالی, لوړوالی);
        /* copy the palette */
        إذا ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_معلومات[1] && src_معلومات[1]))
            حافظه_نقل(dst_معلومات[1], src_معلومات[1], 4*256);
    } وإلا {
        صحيح i, planes_nb = 0;

        لكل (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        لكل (i = 0; i < planes_nb; i++) {
            صحيح h = لوړوالی;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, پلنوالی, i);
            إذا (bwidth < 0) {
                av_log(عدم, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                أرجع;
            }
            إذا (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(لوړوالی, desc->log2_chroma_h);
            }
            copy_plane(dst_معلومات[i], dst_linesizes[i],
                       src_معلومات[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

فراغ av_image_copy(uint8_t *ثابت dst_معلومات[4], ثابت صحيح dst_linesizes[4],
                   ثابت uint8_t * ثابت src_معلومات[4], ثابت صحيح src_linesizes[4],
                   تعداد AVPixelFormat pix_fmt, صحيح پلنوالی, صحيح لوړوالی)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    صحيح i;

    لكل (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_معلومات, dst_linesizes1, src_معلومات, src_linesizes1, pix_fmt,
               پلنوالی, لوړوالی, image_copy_plane);
}

فراغ av_image_copy_uc_from(uint8_t * ثابت dst_معلومات[4], ثابت ptrdiff_t dst_linesizes[4],
                           ثابت uint8_t * ثابت src_معلومات[4], ثابت ptrdiff_t src_linesizes[4],
                           تعداد AVPixelFormat pix_fmt, صحيح پلنوالی, صحيح لوړوالی)
{
    image_copy(dst_معلومات, dst_linesizes, src_معلومات, src_linesizes, pix_fmt,
               پلنوالی, لوړوالی, av_image_copy_plane_uc_from);
}

صحيح av_image_fill_arrays(uint8_t *dst_معلومات[4], صحيح dst_linesize[4],
                         ثابت uint8_t *src, تعداد AVPixelFormat pix_fmt,
                         صحيح پلنوالی, صحيح لوړوالی, صحيح align)
{
    صحيح ret, i;

    ret = av_image_check_اندازه(پلنوالی, لوړوالی, 0, عدم);
    إذا (ret < 0)
        أرجع ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, پلنوالی);
    إذا (ret < 0)
        أرجع ret;

    لكل (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    أرجع av_image_fill_اشارې(dst_معلومات, pix_fmt, لوړوالی, (uint8_t *)src, dst_linesize);
}

صحيح av_image_get_بفر_اندازه(تعداد AVPixelFormat pix_fmt,
                             صحيح پلنوالی, صحيح لوړوالی, صحيح align)
{
    صحيح ret, i;
    صحيح linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    إذا (!desc)
        أرجع AVERROR(EINVAL);

    ret = av_image_check_اندازه(پلنوالی, لوړوالی, 0, عدم);
    إذا (ret < 0)
        أرجع ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, پلنوالی);
    إذا (ret < 0)
        أرجع ret;

    لكل (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, لوړوالی, aligned_linesize);
    إذا (ret < 0)
        أرجع ret;

    ret = 0;
    لكل (i = 0; i < 4; i++) {
        إذا (sizes[i] > لوی_عدد - ret)
            أرجع AVERROR(EINVAL);
        ret += sizes[i];
    }
    أرجع ret;
}

صحيح av_image_copy_منزل_بفر(uint8_t *dst, صحيح dst_اندازه,
                            ثابت uint8_t * ثابت src_معلومات[4],
                            ثابت صحيح src_linesize[4],
                            تعداد AVPixelFormat pix_fmt,
                            صحيح پلنوالی, صحيح لوړوالی, صحيح align)
{
    صحيح i, j, nb_planes = 0, linesize[4];
    صحيح اندازه = av_image_get_بفر_اندازه(pix_fmt, پلنوالی, لوړوالی, align);
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحيح ret;

    إذا (اندازه > dst_اندازه || اندازه < 0 || !desc)
        أرجع AVERROR(EINVAL);

    لكل (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, پلنوالی);
    av_assert0(ret >= 0); // was checked previously

    لكل (i = 0; i < nb_planes; i++) {
        صحيح h, ښويدنه = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        ثابت uint8_t *src = src_معلومات[i];
        h = AV_CEIL_RSHIFT(لوړوالی, ښويدنه);

        لكل (j = 0; j < h; j++) {
            حافظه_نقل(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    إذا (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        لكل (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_معلومات[1] + 4*i));
    }

    أرجع اندازه;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
ساكن فراغ memset_بایټونه(uint8_t *dst, size_t dst_اندازه, uint8_t *clear,
                         size_t clear_اندازه)
{
    صحيح same = 1;
    صحيح i;

    إذا (!clear_اندازه)
        أرجع;

    // Reduce to memset() if possible.
    لكل (i = 0; i < clear_اندازه; i++) {
        إذا (clear[i] != clear[0]) {
            same = 0;
            اكسر;
        }
    }
    إذا (same)
        clear_اندازه = 1;

    إذا (clear_اندازه == 1) {
        memset(dst, clear[0], dst_اندازه);
    } وإلا {
        إذا (clear_اندازه > dst_اندازه)
            clear_اندازه = dst_اندازه;
        حافظه_نقل(dst, clear, clear_اندازه);
        av_memcpy_backptr(dst + clear_اندازه, clear_اندازه, dst_اندازه - clear_اندازه);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#تعریف_کړه MAX_بلاک_اندازه 32

صحيح av_image_fill_color(uint8_t * ثابت dst_معلومات[4], ثابت ptrdiff_t dst_linesize[4],
                        تعداد AVPixelFormat pix_fmt, ثابت uint32_t color[4],
                        صحيح پلنوالی, صحيح لوړوالی, صحيح flags)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحيح nb_planes = av_pix_fmt_شمېر_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_بلاک[4][MAX_بلاک_اندازه] = {{0}}; // clear padding with 0
    صحيح clear_بلاک_اندازه[4] = {0};
    ptrdiff_t plane_کرښه_بایټونه[4] = {0};
    صحيح bitstream;
    صحيح plane, c;

    إذا (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        أرجع AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    لكل (c = 0; c < desc->nb_components; c++) {
        ثابت AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_بلاک_اندازه[comp.plane] = FFMAX(clear_بلاک_اندازه[comp.plane], comp.ګام);

        إذا (clear_بلاک_اندازه[comp.plane] > MAX_بلاک_اندازه)
            أرجع AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    لكل (c = 0; c < desc->nb_components; c++) {
        ثابت AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        صحيح w = (bitstream ? 8 : 1) * clear_بلاک_اندازه[comp.plane] / comp.ګام;
        uint8_t *c_معلومات[4];
        ثابت صحيح c_linesize[4] = {0};
        uint32_t src_array[MAX_بلاک_اندازه];
        صحيح x;

        إذا (comp.ژوروالی > 32)
            أرجع AVERROR(EINVAL);
        إذا (w < 1)
            أرجع AVERROR(EINVAL);

        لكل (x = 0; x < w; x++)
            src_array[x] = color[c];

        لكل (x = 0; x < 4; x++)
            c_معلومات[x] = &clear_بلاک[x][0];

        av_write_image_line2(src_array, c_معلومات, c_linesize, desc, 0, 0, c, w, 4);
    }

    لكل (plane = 0; plane < nb_planes; plane++) {
        plane_کرښه_بایټونه[plane] = av_image_get_linesize(pix_fmt, پلنوالی, plane);
        إذا (plane_کرښه_بایټونه[plane] < 0)
            أرجع AVERROR(EINVAL);
    }

    إذا (!dst_معلومات)
        أرجع 0;

    لكل (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_کرښه_بایټونه[plane];
        uint8_t *معلومات = dst_معلومات[plane];
        صحيح chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        صحيح plane_h = AV_CEIL_RSHIFT(لوړوالی, chroma_div);

        لكل (; plane_h > 0; plane_h--) {
            memset_بایټونه(معلومات, bytewidth, &clear_بلاک[plane][0], clear_بلاک_اندازه[plane]);
            معلومات += dst_linesize[plane];
        }
    }

    أرجع 0;
}

صحيح av_image_fill_black(uint8_t * ثابت dst_معلومات[4], ثابت ptrdiff_t dst_linesize[4],
                        تعداد AVPixelFormat pix_fmt, تعداد AVColorRange range,
                        صحيح پلنوالی, صحيح لوړوالی)
{
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    صحيح nb_planes = av_pix_fmt_شمېر_planes(pix_fmt);
    صحيح rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    إذا (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        أرجع AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    لكل (صحيح c = 0; c < desc->nb_components; c++) {
        ثابت AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        إذا (comp.ژوروالی > 32)
            أرجع AVERROR(EINVAL);

        إذا (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } وإلا إذا (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            إذا (fltp) {
                إذا (comp.ژوروالی != 16 && comp.ژوروالی != 32)
                    أرجع AVERROR(EINVAL);
                color = (comp.ژوروالی == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } وإلا {
                color = (comp.ژوروالی == 32 ? 0 : (1 << comp.ژوروالی)) - 1;
             }
        } وإلا إذا (c == 0 && limited && comp.ژوروالی > 1) {
            إذا (comp.ژوروالی < 8 || (fltp && comp.ژوروالی != 16 && comp.ژوروالی != 32))
                أرجع AVERROR(EINVAL);
            إذا (fltp)
                color = (comp.ژوروالی == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            وإلا
                color = 16 << (comp.ژوروالی - 8);
        } وإلا إذا ((c == 1 || c == 2) && !rgb && !xyz) {
            إذا (comp.ژوروالی < 8 || fltp && comp.ژوروالی != 16 && comp.ژوروالی != 32)
                أرجع AVERROR(EINVAL);
            إذا (fltp)
                color = (comp.ژوروالی == 16 ? 0x3800 : 0x3F000000); // 0.5
            وإلا
                color = 128 << (comp.ژوروالی - 8);
        }

        colors[c] = color;
    }

    أرجع av_image_fill_color(dst_معلومات, dst_linesize, pix_fmt, colors, پلنوالی, لوړوالی, 0);
}
