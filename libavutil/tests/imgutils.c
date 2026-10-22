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

#شامل "libavutil/imgutils.c"
#شامل "libavutil/crc.h"
#شامل "libavutil/mem.h"

ساکن صحیح check_image_fill(شمار AVPixelFormat pix_fmt, صحیح w, صحیح h) {
    uint8_t *ڈیٹا[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    صحیح i, کل_سائز, linesizes[4];

    اگر (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        واپس -1;
    برائے (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    اگر (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        واپس -1;
    کل_سائز = av_image_fill_اشارے(ڈیٹا, pix_fmt, h, (خالی *)1, linesizes);
    اگر (کل_سائز < 0)
        واپس -1;
    برائے (i = 0; i < 4 && ڈیٹا[i]; i++);
    لکھو("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    لکھو(", linesizes:");
    برائے (i = 0; i < 4; i++)
        لکھو(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    لکھو(", plane_sizes:");
    برائے (i = 0; i < 4; i++)
        لکھو(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    برائے (i = 0; i < 3 && ڈیٹا[i + 1]; i++)
        offsets[i] = ڈیٹا[i + 1] - ڈیٹا[i];
    لکھو(", plane_offsets:");
    برائے (i = 0; i < 3; i++)
        لکھو(" %5td", offsets[i]);
    لکھو(", total_size: %d", کل_سائز);

    واپس 0;
}

ساکن صحیح check_image_fill_black(ثابت AVPixFmtDescriptor *desc, شمار AVPixelFormat pix_fmt, صحیح w, صحیح h)
{
    uint8_t *ڈیٹا[4];
    ptrdiff_t linesizes1[4];
    صحیح ret, کل_سائز, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    اگر (ret < 0)
        واپس ret;
    کل_سائز = av_image_alloc(ڈیٹا, linesizes, w, h, pix_fmt, 4);
    اگر (کل_سائز < 0) {
        لکھو("alloc failure");
        واپس کل_سائز;
    }
    لکھو("total_size: %6d", کل_سائز);
    اگر (desc->flags & AV_PIX_FMT_FLAG_PAL)
        کل_سائز -= 256 * 4;
    // Make it non-black by default...
    memset(ڈیٹا[0], 0xA3, کل_سائز);
    برائے (صحیح i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    برائے (شمار AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(ڈیٹا, linesizes1, pix_fmt, range, w, h);
        لکھو(",  black_%s_crc: ", av_color_range_name(range));
        اگر (ret < 0) {
            لکھو("----------");
        } ورنہ {
            ثابت AVCRC *چکری_جانچ = av_چکری_جانچ_get_جدول(AV_چکری_جانچ_32_IEEE_LE);
            لکھو("0x%08"PRIx32, av_چکری_جانچ(چکری_جانچ, 0, ڈیٹا[0], کل_سائز));
        }
    }
    av_freep(&ڈیٹا[0]);

    واپس 0;
}

صحیح مین(خالی)
{
    int64_t x, y;

    برائے (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        برائے (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            صحیح ret = av_image_check_سائز(x, y, 0, تہی);
            لکھو("%d", ret >= 0);
        }
        لکھو("\n");
    }
    لکھو("\n");

    برائے (صحیح i = 0; i < 2; i++) {
        لکھو(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        برائے (ثابت AVPixFmtDescriptor *desc = تہی; desc = av_pix_fmt_desc_اگلا(desc);) {
            صحیح w = 64, h = 48;
            شمار AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            اگر (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                جاری;

            لکھو("%-16s", desc->name);
            اگر (i == 0)
                check_image_fill(pix_fmt, w, h);
            ورنہ
                check_image_fill_black(desc, pix_fmt, w, h);
            لکھو("\n");
        }
    }

    واپس 0;
}
