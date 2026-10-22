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
    uint8_t *data[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    صحيح i, total_size, linesizes[4];

    אם (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        החזר -1;
    עבור (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    אם (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        החזר -1;
    total_size = av_image_fill_pointers(data, pix_fmt, h, (فراغ *)1, linesizes);
    אם (total_size < 0)
        החזר -1;
    עבור (i = 0; i < 4 && data[i]; i++);
    printf("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    printf(", linesizes:");
    עבור (i = 0; i < 4; i++)
        printf(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    printf(", plane_sizes:");
    עבור (i = 0; i < 4; i++)
        printf(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    עבור (i = 0; i < 3 && data[i + 1]; i++)
        offsets[i] = data[i + 1] - data[i];
    printf(", plane_offsets:");
    עבור (i = 0; i < 3; i++)
        printf(" %5td", offsets[i]);
    printf(", total_size: %d", total_size);

    החזר 0;
}

ساكن صحيح check_image_fill_black(ثابت AVPixFmtDescriptor *desc, تعداد AVPixelFormat pix_fmt, صحيح w, صحيح h)
{
    uint8_t *data[4];
    ptrdiff_t linesizes1[4];
    صحيح ret, total_size, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    אם (ret < 0)
        החזר ret;
    total_size = av_image_alloc(data, linesizes, w, h, pix_fmt, 4);
    אם (total_size < 0) {
        printf("alloc failure");
        החזר total_size;
    }
    printf("total_size: %6d", total_size);
    אם (desc->flags & AV_PIX_FMT_FLAG_PAL)
        total_size -= 256 * 4;
    // Make it non-black by default...
    memset(data[0], 0xA3, total_size);
    עבור (صحيح i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    עבור (تعداد AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(data, linesizes1, pix_fmt, range, w, h);
        printf(",  black_%s_crc: ", av_color_range_name(range));
        אם (ret < 0) {
            printf("----------");
        } אחרת {
            ثابت AVCRC *crc = av_crc_get_table(AV_CRC_32_IEEE_LE);
            printf("0x%08"PRIx32, av_crc(crc, 0, data[0], total_size));
        }
    }
    av_freep(&data[0]);

    החזר 0;
}

صحيح main(فراغ)
{
    int64_t x, y;

    עבור (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        עבור (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            صحيح ret = av_image_check_size(x, y, 0, عدم);
            printf("%d", ret >= 0);
        }
        printf("\n");
    }
    printf("\n");

    עבור (صحيح i = 0; i < 2; i++) {
        printf(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        עבור (ثابت AVPixFmtDescriptor *desc = عدم; desc = av_pix_fmt_desc_next(desc);) {
            صحيح w = 64, h = 48;
            تعداد AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            אם (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                استمر;

            printf("%-16s", desc->name);
            אם (i == 0)
                check_image_fill(pix_fmt, w, h);
            אחרת
                check_image_fill_black(desc, pix_fmt, w, h);
            printf("\n");
        }
    }

    החזר 0;
}
