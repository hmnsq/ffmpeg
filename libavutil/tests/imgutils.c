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

#அந்தர்பாவ "libavutil/imgutils.c"
#அந்தர்பாவ "libavutil/crc.h"
#அந்தர்பாவ "libavutil/mem.h"

நிலையான முழு check_image_fill(எண்ணிக்கை AVPixelFormat pix_fmt, முழு w, முழு h) {
    uint8_t *data[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    முழு i, total_size, linesizes[4];

    எனில் (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        திரும்பு -1;
    க்கு (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    எனில் (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        திரும்பு -1;
    total_size = av_image_fill_pointers(data, pix_fmt, h, (வெறுமை *)1, linesizes);
    எனில் (total_size < 0)
        திரும்பு -1;
    க்கு (i = 0; i < 4 && data[i]; i++);
    printf("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    printf(", linesizes:");
    க்கு (i = 0; i < 4; i++)
        printf(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    printf(", plane_sizes:");
    க்கு (i = 0; i < 4; i++)
        printf(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    க்கு (i = 0; i < 3 && data[i + 1]; i++)
        offsets[i] = data[i + 1] - data[i];
    printf(", plane_offsets:");
    க்கு (i = 0; i < 3; i++)
        printf(" %5td", offsets[i]);
    printf(", total_size: %d", total_size);

    திரும்பு 0;
}

நிலையான முழு check_image_fill_black(மாறிலி AVPixFmtDescriptor *desc, எண்ணிக்கை AVPixelFormat pix_fmt, முழு w, முழு h)
{
    uint8_t *data[4];
    ptrdiff_t linesizes1[4];
    முழு ret, total_size, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    எனில் (ret < 0)
        திரும்பு ret;
    total_size = av_image_alloc(data, linesizes, w, h, pix_fmt, 4);
    எனில் (total_size < 0) {
        printf("alloc failure");
        திரும்பு total_size;
    }
    printf("total_size: %6d", total_size);
    எனில் (desc->flags & AV_PIX_FMT_FLAG_PAL)
        total_size -= 256 * 4;
    // Make it non-black by default...
    memset(data[0], 0xA3, total_size);
    க்கு (முழு i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    க்கு (எண்ணிக்கை AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(data, linesizes1, pix_fmt, range, w, h);
        printf(",  black_%s_crc: ", av_color_range_name(range));
        எனில் (ret < 0) {
            printf("----------");
        } இல்லையெனில் {
            மாறிலி AVCRC *crc = av_crc_get_table(AV_CRC_32_IEEE_LE);
            printf("0x%08"PRIx32, av_crc(crc, 0, data[0], total_size));
        }
    }
    av_freep(&data[0]);

    திரும்பு 0;
}

முழு முதன்மை(வெறுமை)
{
    int64_t x, y;

    க்கு (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        க்கு (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            முழு ret = av_image_check_size(x, y, 0, வெற்று);
            printf("%d", ret >= 0);
        }
        printf("\n");
    }
    printf("\n");

    க்கு (முழு i = 0; i < 2; i++) {
        printf(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        க்கு (மாறிலி AVPixFmtDescriptor *desc = வெற்று; desc = av_pix_fmt_desc_next(desc);) {
            முழு w = 64, h = 48;
            எண்ணிக்கை AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            எனில் (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                தொடர்;

            printf("%-16s", desc->name);
            எனில் (i == 0)
                check_image_fill(pix_fmt, w, h);
            இல்லையெனில்
                check_image_fill_black(desc, pix_fmt, w, h);
            printf("\n");
        }
    }

    திரும்பு 0;
}
