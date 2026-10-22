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
    uint8_t *داده[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    صحيح i, مجموع_اندازه, linesizes[4];

    إذا (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        أرجع -1;
    لكل (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    إذا (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        أرجع -1;
    مجموع_اندازه = av_image_fill_اشارهگرها(داده, pix_fmt, h, (فراغ *)1, linesizes);
    إذا (مجموع_اندازه < 0)
        أرجع -1;
    لكل (i = 0; i < 4 && داده[i]; i++);
    چاپ_کن("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    چاپ_کن(", linesizes:");
    لكل (i = 0; i < 4; i++)
        چاپ_کن(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    چاپ_کن(", plane_sizes:");
    لكل (i = 0; i < 4; i++)
        چاپ_کن(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    لكل (i = 0; i < 3 && داده[i + 1]; i++)
        offsets[i] = داده[i + 1] - داده[i];
    چاپ_کن(", plane_offsets:");
    لكل (i = 0; i < 3; i++)
        چاپ_کن(" %5td", offsets[i]);
    چاپ_کن(", total_size: %d", مجموع_اندازه);

    أرجع 0;
}

ساكن صحيح check_image_fill_black(ثابت AVPixFmtDescriptor *desc, تعداد AVPixelFormat pix_fmt, صحيح w, صحيح h)
{
    uint8_t *داده[4];
    ptrdiff_t linesizes1[4];
    صحيح ret, مجموع_اندازه, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    إذا (ret < 0)
        أرجع ret;
    مجموع_اندازه = av_image_alloc(داده, linesizes, w, h, pix_fmt, 4);
    إذا (مجموع_اندازه < 0) {
        چاپ_کن("alloc failure");
        أرجع مجموع_اندازه;
    }
    چاپ_کن("total_size: %6d", مجموع_اندازه);
    إذا (desc->flags & AV_PIX_FMT_FLAG_PAL)
        مجموع_اندازه -= 256 * 4;
    // Make it non-black by default...
    memset(داده[0], 0xA3, مجموع_اندازه);
    لكل (صحيح i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    لكل (تعداد AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(داده, linesizes1, pix_fmt, range, w, h);
        چاپ_کن(",  black_%s_crc: ", av_color_range_name(range));
        إذا (ret < 0) {
            چاپ_کن("----------");
        } وإلا {
            ثابت AVCRC *بررسی_چرخهای = av_بررسی_چرخهای_get_جدول(AV_بررسی_چرخهای_32_IEEE_LE);
            چاپ_کن("0x%08"PRIx32, av_بررسی_چرخهای(بررسی_چرخهای, 0, داده[0], مجموع_اندازه));
        }
    }
    av_freep(&داده[0]);

    أرجع 0;
}

صحيح اصلی(فراغ)
{
    int64_t x, y;

    لكل (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        لكل (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            صحيح ret = av_image_check_اندازه(x, y, 0, عدم);
            چاپ_کن("%d", ret >= 0);
        }
        چاپ_کن("\n");
    }
    چاپ_کن("\n");

    لكل (صحيح i = 0; i < 2; i++) {
        چاپ_کن(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        لكل (ثابت AVPixFmtDescriptor *desc = عدم; desc = av_pix_fmt_desc_بعدی(desc);) {
            صحيح w = 64, h = 48;
            تعداد AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            إذا (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                استمر;

            چاپ_کن("%-16s", desc->name);
            إذا (i == 0)
                check_image_fill(pix_fmt, w, h);
            وإلا
                check_image_fill_black(desc, pix_fmt, w, h);
            چاپ_کن("\n");
        }
    }

    أرجع 0;
}
