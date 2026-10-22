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

static 정수 check_image_fill(enum AVPixelFormat pix_fmt, 정수 w, 정수 h) {
    uint8_t *data[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    정수 i, total_size, linesizes[4];

    만약 (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        반환 -1;
    위해 (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    만약 (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        반환 -1;
    total_size = av_image_fill_pointers(data, pix_fmt, h, (void *)1, linesizes);
    만약 (total_size < 0)
        반환 -1;
    위해 (i = 0; i < 4 && data[i]; i++);
    printf("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    printf(", linesizes:");
    위해 (i = 0; i < 4; i++)
        printf(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    printf(", plane_sizes:");
    위해 (i = 0; i < 4; i++)
        printf(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    위해 (i = 0; i < 3 && data[i + 1]; i++)
        offsets[i] = data[i + 1] - data[i];
    printf(", plane_offsets:");
    위해 (i = 0; i < 3; i++)
        printf(" %5td", offsets[i]);
    printf(", total_size: %d", total_size);

    반환 0;
}

static 정수 check_image_fill_black(const AVPixFmtDescriptor *desc, enum AVPixelFormat pix_fmt, 정수 w, 정수 h)
{
    uint8_t *data[4];
    ptrdiff_t linesizes1[4];
    정수 ret, total_size, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    만약 (ret < 0)
        반환 ret;
    total_size = av_image_alloc(data, linesizes, w, h, pix_fmt, 4);
    만약 (total_size < 0) {
        printf("alloc failure");
        반환 total_size;
    }
    printf("total_size: %6d", total_size);
    만약 (desc->flags & AV_PIX_FMT_FLAG_PAL)
        total_size -= 256 * 4;
    // Make it non-black by default...
    memset(data[0], 0xA3, total_size);
    위해 (정수 i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    위해 (enum AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(data, linesizes1, pix_fmt, range, w, h);
        printf(",  black_%s_crc: ", av_color_range_name(range));
        만약 (ret < 0) {
            printf("----------");
        } 아니면 {
            const AVCRC *crc = av_crc_get_table(AV_CRC_32_IEEE_LE);
            printf("0x%08"PRIx32, av_crc(crc, 0, data[0], total_size));
        }
    }
    av_freep(&data[0]);

    반환 0;
}

정수 main(void)
{
    int64_t x, y;

    위해 (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        위해 (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            정수 ret = av_image_check_size(x, y, 0, NULL);
            printf("%d", ret >= 0);
        }
        printf("\n");
    }
    printf("\n");

    위해 (정수 i = 0; i < 2; i++) {
        printf(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        위해 (const AVPixFmtDescriptor *desc = NULL; desc = av_pix_fmt_desc_next(desc);) {
            정수 w = 64, h = 48;
            enum AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            만약 (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                continue;

            printf("%-16s", desc->name);
            만약 (i == 0)
                check_image_fill(pix_fmt, w, h);
            아니면
                check_image_fill_black(desc, pix_fmt, w, h);
            printf("\n");
        }
    }

    반환 0;
}
