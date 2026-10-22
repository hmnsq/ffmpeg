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

#ضمن "libavutil/imgutils.c"
#ضمن "libavutil/crc.h"
#ضمن "libavutil/mem.h"

ساكن صحيح check_image_fill(تعداد AVPixelFormat pix_fmt, صحيح w, صحيح h) {
    uint8_t *انکڑے[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    صحيح i, کل_ناپ, linesizes[4];

    إذا (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        أرجع -1;
    لكل (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    إذا (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        أرجع -1;
    کل_ناپ = av_image_fill_سوچکاں(انکڑے, pix_fmt, h, (فراغ *)1, linesizes);
    إذا (کل_ناپ < 0)
        أرجع -1;
    لكل (i = 0; i < 4 && انکڑے[i]; i++);
    لکھو("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    لکھو(", linesizes:");
    لكل (i = 0; i < 4; i++)
        لکھو(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    لکھو(", plane_sizes:");
    لكل (i = 0; i < 4; i++)
        لکھو(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    لكل (i = 0; i < 3 && انکڑے[i + 1]; i++)
        offsets[i] = انکڑے[i + 1] - انکڑے[i];
    لکھو(", plane_offsets:");
    لكل (i = 0; i < 3; i++)
        لکھو(" %5td", offsets[i]);
    لکھو(", total_size: %d", کل_ناپ);

    أرجع 0;
}

ساكن صحيح check_image_fill_black(ثابت AVPixFmtDescriptor *desc, تعداد AVPixelFormat pix_fmt, صحيح w, صحيح h)
{
    uint8_t *انکڑے[4];
    ptrdiff_t linesizes1[4];
    صحيح ret, کل_ناپ, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    إذا (ret < 0)
        أرجع ret;
    کل_ناپ = av_image_alloc(انکڑے, linesizes, w, h, pix_fmt, 4);
    إذا (کل_ناپ < 0) {
        لکھو("alloc failure");
        أرجع کل_ناپ;
    }
    لکھو("total_size: %6d", کل_ناپ);
    إذا (desc->flags & AV_PIX_FMT_FLAG_PAL)
        کل_ناپ -= 256 * 4;
    // Make it non-black by default...
    memset(انکڑے[0], 0xA3, کل_ناپ);
    لكل (صحيح i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    لكل (تعداد AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(انکڑے, linesizes1, pix_fmt, range, w, h);
        لکھو(",  black_%s_crc: ", av_color_range_name(range));
        إذا (ret < 0) {
            لکھو("----------");
        } وإلا {
            ثابت AVCRC *چکری_جانچ = av_چکری_جانچ_get_جدول(AV_چکری_جانچ_32_IEEE_LE);
            لکھو("0x%08"PRIx32, av_چکری_جانچ(چکری_جانچ, 0, انکڑے[0], کل_ناپ));
        }
    }
    av_freep(&انکڑے[0]);

    أرجع 0;
}

صحيح مکھ(فراغ)
{
    int64_t x, y;

    لكل (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        لكل (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            صحيح ret = av_image_check_ناپ(x, y, 0, عدم);
            لکھو("%d", ret >= 0);
        }
        لکھو("\n");
    }
    لکھو("\n");

    لكل (صحيح i = 0; i < 2; i++) {
        لکھو(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        لكل (ثابت AVPixFmtDescriptor *desc = عدم; desc = av_pix_fmt_desc_اگلا(desc);) {
            صحيح w = 64, h = 48;
            تعداد AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            إذا (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                استمر;

            لکھو("%-16s", desc->name);
            إذا (i == 0)
                check_image_fill(pix_fmt, w, h);
            وإلا
                check_image_fill_black(desc, pix_fmt, w, h);
            لکھو("\n");
        }
    }

    أرجع 0;
}
