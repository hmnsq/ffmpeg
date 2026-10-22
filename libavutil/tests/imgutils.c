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

#अन्तर्भाव "libavutil/imgutils.c"
#अन्तर्भाव "libavutil/crc.h"
#अन्तर्भाव "libavutil/mem.h"

स्थिर पूर्णाङ्क check_image_fill(गणना AVPixelFormat pix_fmt, पूर्णाङ्क w, पूर्णाङ्क h) {
    uint8_t *data[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    पूर्णाङ्क i, total_size, linesizes[4];

    सचे (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        पटिनिवत्त -1;
    अत्थाय (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    सचे (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        पटिनिवत्त -1;
    total_size = av_image_fill_pointers(data, pix_fmt, h, (शून्य *)1, linesizes);
    सचे (total_size < 0)
        पटिनिवत्त -1;
    अत्थाय (i = 0; i < 4 && data[i]; i++);
    printf("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    printf(", linesizes:");
    अत्थाय (i = 0; i < 4; i++)
        printf(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    printf(", plane_sizes:");
    अत्थाय (i = 0; i < 4; i++)
        printf(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    अत्थाय (i = 0; i < 3 && data[i + 1]; i++)
        offsets[i] = data[i + 1] - data[i];
    printf(", plane_offsets:");
    अत्थाय (i = 0; i < 3; i++)
        printf(" %5td", offsets[i]);
    printf(", total_size: %d", total_size);

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क check_image_fill_black(ध्रुव AVPixFmtDescriptor *desc, गणना AVPixelFormat pix_fmt, पूर्णाङ्क w, पूर्णाङ्क h)
{
    uint8_t *data[4];
    ptrdiff_t linesizes1[4];
    पूर्णाङ्क ret, total_size, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    सचे (ret < 0)
        पटिनिवत्त ret;
    total_size = av_image_alloc(data, linesizes, w, h, pix_fmt, 4);
    सचे (total_size < 0) {
        printf("alloc failure");
        पटिनिवत्त total_size;
    }
    printf("total_size: %6d", total_size);
    सचे (desc->flags & AV_PIX_FMT_FLAG_PAL)
        total_size -= 256 * 4;
    // Make it non-black by default...
    memset(data[0], 0xA3, total_size);
    अत्थाय (पूर्णाङ्क i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    अत्थाय (गणना AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(data, linesizes1, pix_fmt, range, w, h);
        printf(",  black_%s_crc: ", av_color_range_name(range));
        सचे (ret < 0) {
            printf("----------");
        } अञ्ञथा {
            ध्रुव AVCRC *crc = av_crc_get_table(AV_CRC_32_IEEE_LE);
            printf("0x%08"PRIx32, av_crc(crc, 0, data[0], total_size));
        }
    }
    av_freep(&data[0]);

    पटिनिवत्त 0;
}

पूर्णाङ्क main(शून्य)
{
    int64_t x, y;

    अत्थाय (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        अत्थाय (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            पूर्णाङ्क ret = av_image_check_size(x, y, 0, रिक्त);
            printf("%d", ret >= 0);
        }
        printf("\n");
    }
    printf("\n");

    अत्थाय (पूर्णाङ्क i = 0; i < 2; i++) {
        printf(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        अत्थाय (ध्रुव AVPixFmtDescriptor *desc = रिक्त; desc = av_pix_fmt_desc_next(desc);) {
            पूर्णाङ्क w = 64, h = 48;
            गणना AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            सचे (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                अनुवर्त;

            printf("%-16s", desc->name);
            सचे (i == 0)
                check_image_fill(pix_fmt, w, h);
            अञ्ञथा
                check_image_fill_black(desc, pix_fmt, w, h);
            printf("\n");
        }
    }

    पटिनिवत्त 0;
}
