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

static ཧྲིལ check_image_fill(ga_nanaa AVPixelFormat pix_fmt, ཧྲིལ w, ཧྲིལ h) {
    uint8_t *data[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    ཧྲིལ i, total_size, linesizes[4];

    གལ་ཏེ (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        ཕྱིར -1;
    ཆེད་དུ (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    གལ་ཏེ (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        ཕྱིར -1;
    total_size = av_image_fill_pointers(data, pix_fmt, h, (void *)1, linesizes);
    གལ་ཏེ (total_size < 0)
        ཕྱིར -1;
    ཆེད་དུ (i = 0; i < 4 && data[i]; i++);
    printf("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    printf(", linesizes:");
    ཆེད་དུ (i = 0; i < 4; i++)
        printf(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    printf(", plane_sizes:");
    ཆེད་དུ (i = 0; i < 4; i++)
        printf(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    ཆེད་དུ (i = 0; i < 3 && data[i + 1]; i++)
        offsets[i] = data[i + 1] - data[i];
    printf(", plane_offsets:");
    ཆེད་དུ (i = 0; i < 3; i++)
        printf(" %5td", offsets[i]);
    printf(", total_size: %d", total_size);

    ཕྱིར 0;
}

static ཧྲིལ check_image_fill_black(const AVPixFmtDescriptor *desc, ga_nanaa AVPixelFormat pix_fmt, ཧྲིལ w, ཧྲིལ h)
{
    uint8_t *data[4];
    ptrdiff_t linesizes1[4];
    ཧྲིལ ret, total_size, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;
    total_size = av_image_alloc(data, linesizes, w, h, pix_fmt, 4);
    གལ་ཏེ (total_size < 0) {
        printf("alloc failure");
        ཕྱིར total_size;
    }
    printf("total_size: %6d", total_size);
    གལ་ཏེ (desc->flags & AV_PIX_FMT_FLAG_PAL)
        total_size -= 256 * 4;
    // Make it non-black by default...
    memset(data[0], 0xA3, total_size);
    ཆེད་དུ (ཧྲིལ i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    ཆེད་དུ (ga_nanaa AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(data, linesizes1, pix_fmt, range, w, h);
        printf(",  black_%s_crc: ", av_color_range_name(range));
        གལ་ཏེ (ret < 0) {
            printf("----------");
        } དེ་མིན {
            const AVCRC *crc = av_crc_get_table(AV_CRC_32_IEEE_LE);
            printf("0x%08"PRIx32, av_crc(crc, 0, data[0], total_size));
        }
    }
    av_freep(&data[0]);

    ཕྱིར 0;
}

ཧྲིལ གཙོ(void)
{
    int64_t x, y;

    ཆེད་དུ (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        ཆེད་དུ (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            ཧྲིལ ret = av_image_check_size(x, y, 0, NULL);
            printf("%d", ret >= 0);
        }
        printf("\n");
    }
    printf("\n");

    ཆེད་དུ (ཧྲིལ i = 0; i < 2; i++) {
        printf(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        ཆེད་དུ (const AVPixFmtDescriptor *desc = NULL; desc = av_pix_fmt_desc_next(desc);) {
            ཧྲིལ w = 64, h = 48;
            ga_nanaa AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            གལ་ཏེ (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                continue;

            printf("%-16s", desc->name);
            གལ་ཏེ (i == 0)
                check_image_fill(pix_fmt, w, h);
            དེ་མིན
                check_image_fill_black(desc, pix_fmt, w, h);
            printf("\n");
        }
    }

    ཕྱིར 0;
}
