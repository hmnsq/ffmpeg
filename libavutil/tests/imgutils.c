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

#include "libavutil/imgutils.c"
#include "libavutil/crc.h"
#include "libavutil/mem.h"

static целое check_image_fill(enum AVPixelFormat pix_fmt, целое w, целое h) {
    uint8_t *data[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    целое i, total_size, linesizes[4];

    если (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        вернуть -1;
    для (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    если (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        вернуть -1;
    total_size = av_image_fill_pointers(data, pix_fmt, h, (void *)1, linesizes);
    если (total_size < 0)
        вернуть -1;
    для (i = 0; i < 4 && data[i]; i++);
    printf("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    printf(", linesizes:");
    для (i = 0; i < 4; i++)
        printf(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    printf(", plane_sizes:");
    для (i = 0; i < 4; i++)
        printf(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    для (i = 0; i < 3 && data[i + 1]; i++)
        offsets[i] = data[i + 1] - data[i];
    printf(", plane_offsets:");
    для (i = 0; i < 3; i++)
        printf(" %5td", offsets[i]);
    printf(", total_size: %d", total_size);

    вернуть 0;
}

static целое check_image_fill_black(const AVPixFmtDescriptor *desc, enum AVPixelFormat pix_fmt, целое w, целое h)
{
    uint8_t *data[4];
    ptrdiff_t linesizes1[4];
    целое ret, total_size, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    если (ret < 0)
        вернуть ret;
    total_size = av_image_alloc(data, linesizes, w, h, pix_fmt, 4);
    если (total_size < 0) {
        printf("alloc failure");
        вернуть total_size;
    }
    printf("total_size: %6d", total_size);
    если (desc->flags & AV_PIX_FMT_FLAG_PAL)
        total_size -= 256 * 4;
    // Make it non-black by default...
    memset(data[0], 0xA3, total_size);
    для (целое i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    для (enum AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(data, linesizes1, pix_fmt, range, w, h);
        printf(",  black_%s_crc: ", av_color_range_name(range));
        если (ret < 0) {
            printf("----------");
        } иначе {
            const AVCRC *crc = av_crc_get_table(AV_CRC_32_IEEE_LE);
            printf("0x%08"PRIx32, av_crc(crc, 0, data[0], total_size));
        }
    }
    av_freep(&data[0]);

    вернуть 0;
}

целое основной(void)
{
    int64_t x, y;

    для (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        для (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            целое ret = av_image_check_size(x, y, 0, NULL);
            printf("%d", ret >= 0);
        }
        printf("\n");
    }
    printf("\n");

    для (целое i = 0; i < 2; i++) {
        printf(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        для (const AVPixFmtDescriptor *desc = NULL; desc = av_pix_fmt_desc_next(desc);) {
            целое w = 64, h = 48;
            enum AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            если (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                continue;

            printf("%-16s", desc->name);
            если (i == 0)
                check_image_fill(pix_fmt, w, h);
            иначе
                check_image_fill_black(desc, pix_fmt, w, h);
            printf("\n");
        }
    }

    вернуть 0;
}
