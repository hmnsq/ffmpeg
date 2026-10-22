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

#ಅನ್ತರ್ಭಾವ "libavutil/imgutils.c"
#ಅನ್ತರ್ಭಾವ "libavutil/crc.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ check_image_fill(ಗಣನಾ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h) {
    uint8_t *data[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    ಪೂರ್ಣಾಙ್ಕ i, total_size, linesizes[4];

    ಯದಿ (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        ಪ್ರತ್ಯಾಗಮ -1;
    ಪ್ರತಿ (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    ಯದಿ (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        ಪ್ರತ್ಯಾಗಮ -1;
    total_size = av_image_fill_pointers(data, pix_fmt, h, (ಶೂನ್ಯ *)1, linesizes);
    ಯದಿ (total_size < 0)
        ಪ್ರತ್ಯಾಗಮ -1;
    ಪ್ರತಿ (i = 0; i < 4 && data[i]; i++);
    printf("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    printf(", linesizes:");
    ಪ್ರತಿ (i = 0; i < 4; i++)
        printf(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    printf(", plane_sizes:");
    ಪ್ರತಿ (i = 0; i < 4; i++)
        printf(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    ಪ್ರತಿ (i = 0; i < 3 && data[i + 1]; i++)
        offsets[i] = data[i + 1] - data[i];
    printf(", plane_offsets:");
    ಪ್ರತಿ (i = 0; i < 3; i++)
        printf(" %5td", offsets[i]);
    printf(", total_size: %d", total_size);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ check_image_fill_black(ಧ್ರುವ AVPixFmtDescriptor *desc, ಗಣನಾ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h)
{
    uint8_t *data[4];
    ptrdiff_t linesizes1[4];
    ಪೂರ್ಣಾಙ್ಕ ret, total_size, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    total_size = av_image_alloc(data, linesizes, w, h, pix_fmt, 4);
    ಯದಿ (total_size < 0) {
        printf("alloc failure");
        ಪ್ರತ್ಯಾಗಮ total_size;
    }
    printf("total_size: %6d", total_size);
    ಯದಿ (desc->flags & AV_PIX_FMT_FLAG_PAL)
        total_size -= 256 * 4;
    // Make it non-black by default...
    memset(data[0], 0xA3, total_size);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    ಪ್ರತಿ (ಗಣನಾ AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(data, linesizes1, pix_fmt, range, w, h);
        printf(",  black_%s_crc: ", av_color_range_name(range));
        ಯದಿ (ret < 0) {
            printf("----------");
        } ಅನ್ಯಥಾ {
            ಧ್ರುವ AVCRC *crc = av_crc_get_table(AV_CRC_32_IEEE_LE);
            printf("0x%08"PRIx32, av_crc(crc, 0, data[0], total_size));
        }
    }
    av_freep(&data[0]);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    int64_t x, y;

    ಪ್ರತಿ (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        ಪ್ರತಿ (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            ಪೂರ್ಣಾಙ್ಕ ret = av_image_check_size(x, y, 0, ರಿಕ್ತ);
            printf("%d", ret >= 0);
        }
        printf("\n");
    }
    printf("\n");

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 2; i++) {
        printf(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        ಪ್ರತಿ (ಧ್ರುವ AVPixFmtDescriptor *desc = ರಿಕ್ತ; desc = av_pix_fmt_desc_next(desc);) {
            ಪೂರ್ಣಾಙ್ಕ w = 64, h = 48;
            ಗಣನಾ AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            ಯದಿ (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                ಅನುವರ್ತ;

            printf("%-16s", desc->name);
            ಯದಿ (i == 0)
                check_image_fill(pix_fmt, w, h);
            ಅನ್ಯಥಾ
                check_image_fill_black(desc, pix_fmt, w, h);
            printf("\n");
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}
