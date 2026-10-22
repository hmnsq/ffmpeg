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

#অন্তর্ভাৱ "libavutil/imgutils.c"
#অন্তর্ভাৱ "libavutil/crc.h"
#অন্তর্ভাৱ "libavutil/mem.h"

স্থির পূর্ণাঙ্ক check_image_fill(গণনা AVPixelFormat pix_fmt, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h) {
    uint8_t *data[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    পূর্ণাঙ্ক i, total_size, linesizes[4];

    যদি (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        ঘূৰাই -1;
    বাবে (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    যদি (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        ঘূৰাই -1;
    total_size = av_image_fill_pointers(data, pix_fmt, h, (শূন্য *)1, linesizes);
    যদি (total_size < 0)
        ঘূৰাই -1;
    বাবে (i = 0; i < 4 && data[i]; i++);
    printf("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    printf(", linesizes:");
    বাবে (i = 0; i < 4; i++)
        printf(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    printf(", plane_sizes:");
    বাবে (i = 0; i < 4; i++)
        printf(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    বাবে (i = 0; i < 3 && data[i + 1]; i++)
        offsets[i] = data[i + 1] - data[i];
    printf(", plane_offsets:");
    বাবে (i = 0; i < 3; i++)
        printf(" %5td", offsets[i]);
    printf(", total_size: %d", total_size);

    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক check_image_fill_black(ধ্রুৱ AVPixFmtDescriptor *desc, গণনা AVPixelFormat pix_fmt, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h)
{
    uint8_t *data[4];
    ptrdiff_t linesizes1[4];
    পূর্ণাঙ্ক ret, total_size, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    যদি (ret < 0)
        ঘূৰাই ret;
    total_size = av_image_alloc(data, linesizes, w, h, pix_fmt, 4);
    যদি (total_size < 0) {
        printf("alloc failure");
        ঘূৰাই total_size;
    }
    printf("total_size: %6d", total_size);
    যদি (desc->flags & AV_PIX_FMT_FLAG_PAL)
        total_size -= 256 * 4;
    // Make it non-black by default...
    memset(data[0], 0xA3, total_size);
    বাবে (পূর্ণাঙ্ক i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    বাবে (গণনা AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(data, linesizes1, pix_fmt, range, w, h);
        printf(",  black_%s_crc: ", av_color_range_name(range));
        যদি (ret < 0) {
            printf("----------");
        } অন্যথা {
            ধ্রুৱ AVCRC *crc = av_crc_get_table(AV_CRC_32_IEEE_LE);
            printf("0x%08"PRIx32, av_crc(crc, 0, data[0], total_size));
        }
    }
    av_freep(&data[0]);

    ঘূৰাই 0;
}

পূর্ণাঙ্ক main(শূন্য)
{
    int64_t x, y;

    বাবে (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        বাবে (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            পূর্ণাঙ্ক ret = av_image_check_size(x, y, 0, রিক্ত);
            printf("%d", ret >= 0);
        }
        printf("\n");
    }
    printf("\n");

    বাবে (পূর্ণাঙ্ক i = 0; i < 2; i++) {
        printf(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        বাবে (ধ্রুৱ AVPixFmtDescriptor *desc = রিক্ত; desc = av_pix_fmt_desc_next(desc);) {
            পূর্ণাঙ্ক w = 64, h = 48;
            গণনা AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            যদি (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                অনুৱর্ত;

            printf("%-16s", desc->name);
            যদি (i == 0)
                check_image_fill(pix_fmt, w, h);
            অন্যথা
                check_image_fill_black(desc, pix_fmt, w, h);
            printf("\n");
        }
    }

    ঘূৰাই 0;
}
