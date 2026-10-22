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

#ଅନ୍ତର୍ଭାଵ "libavutil/imgutils.c"
#ଅନ୍ତର୍ଭାଵ "libavutil/crc.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/mem.h"

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା check_image_fill(ଗଣନା AVPixelFormat pix_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h) {
    uint8_t *data[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, total_size, linesizes[4];

    ଯଦି (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        ଫେରନ୍ତୁ -1;
    ପାଇଁ (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    ଯଦି (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        ଫେରନ୍ତୁ -1;
    total_size = av_image_fill_pointers(data, pix_fmt, h, (ଶୂନ୍ୟ *)1, linesizes);
    ଯଦି (total_size < 0)
        ଫେରନ୍ତୁ -1;
    ପାଇଁ (i = 0; i < 4 && data[i]; i++);
    printf("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    printf(", linesizes:");
    ପାଇଁ (i = 0; i < 4; i++)
        printf(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    printf(", plane_sizes:");
    ପାଇଁ (i = 0; i < 4; i++)
        printf(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    ପାଇଁ (i = 0; i < 3 && data[i + 1]; i++)
        offsets[i] = data[i + 1] - data[i];
    printf(", plane_offsets:");
    ପାଇଁ (i = 0; i < 3; i++)
        printf(" %5td", offsets[i]);
    printf(", total_size: %d", total_size);

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା check_image_fill_black(ଅଚଳ AVPixFmtDescriptor *desc, ଗଣନା AVPixelFormat pix_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h)
{
    uint8_t *data[4];
    ptrdiff_t linesizes1[4];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, total_size, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;
    total_size = av_image_alloc(data, linesizes, w, h, pix_fmt, 4);
    ଯଦି (total_size < 0) {
        printf("alloc failure");
        ଫେରନ୍ତୁ total_size;
    }
    printf("total_size: %6d", total_size);
    ଯଦି (desc->flags & AV_PIX_FMT_FLAG_PAL)
        total_size -= 256 * 4;
    // Make it non-black by default...
    memset(data[0], 0xA3, total_size);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    ପାଇଁ (ଗଣନା AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(data, linesizes1, pix_fmt, range, w, h);
        printf(",  black_%s_crc: ", av_color_range_name(range));
        ଯଦି (ret < 0) {
            printf("----------");
        } ଅନ୍ୟଥା {
            ଅଚଳ AVCRC *crc = av_crc_get_table(AV_CRC_32_IEEE_LE);
            printf("0x%08"PRIx32, av_crc(crc, 0, data[0], total_size));
        }
    }
    av_freep(&data[0]);

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ଶୂନ୍ୟ)
{
    int64_t x, y;

    ପାଇଁ (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        ପାଇଁ (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = av_image_check_size(x, y, 0, ଖାଲି);
            printf("%d", ret >= 0);
        }
        printf("\n");
    }
    printf("\n");

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 2; i++) {
        printf(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        ପାଇଁ (ଅଚଳ AVPixFmtDescriptor *desc = ଖାଲି; desc = av_pix_fmt_desc_next(desc);) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = 64, h = 48;
            ଗଣନା AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            ଯଦି (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                ଜାରି;

            printf("%-16s", desc->name);
            ଯଦି (i == 0)
                check_image_fill(pix_fmt, w, h);
            ଅନ୍ୟଥା
                check_image_fill_black(desc, pix_fmt, w, h);
            printf("\n");
        }
    }

    ଫେରନ୍ତୁ 0;
}
