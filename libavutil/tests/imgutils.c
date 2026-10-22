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

#અન્તર્ભાવ "libavutil/imgutils.c"
#અન્તર્ભાવ "libavutil/crc.h"
#અન્તર્ભાવ "libavutil/mem.h"

સ્થિર પૂર્ણાંક check_image_fill(ગણના AVPixelFormat pix_fmt, પૂર્ણાંક w, પૂર્ણાંક h) {
    uint8_t *data[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    પૂર્ણાંક i, total_size, linesizes[4];

    જો (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        પાછા -1;
    માટે (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    જો (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        પાછા -1;
    total_size = av_image_fill_pointers(data, pix_fmt, h, (શૂન્ય *)1, linesizes);
    જો (total_size < 0)
        પાછા -1;
    માટે (i = 0; i < 4 && data[i]; i++);
    printf("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    printf(", linesizes:");
    માટે (i = 0; i < 4; i++)
        printf(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    printf(", plane_sizes:");
    માટે (i = 0; i < 4; i++)
        printf(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    માટે (i = 0; i < 3 && data[i + 1]; i++)
        offsets[i] = data[i + 1] - data[i];
    printf(", plane_offsets:");
    માટે (i = 0; i < 3; i++)
        printf(" %5td", offsets[i]);
    printf(", total_size: %d", total_size);

    પાછા 0;
}

સ્થિર પૂર્ણાંક check_image_fill_black(અચલ AVPixFmtDescriptor *desc, ગણના AVPixelFormat pix_fmt, પૂર્ણાંક w, પૂર્ણાંક h)
{
    uint8_t *data[4];
    ptrdiff_t linesizes1[4];
    પૂર્ણાંક ret, total_size, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    જો (ret < 0)
        પાછા ret;
    total_size = av_image_alloc(data, linesizes, w, h, pix_fmt, 4);
    જો (total_size < 0) {
        printf("alloc failure");
        પાછા total_size;
    }
    printf("total_size: %6d", total_size);
    જો (desc->flags & AV_PIX_FMT_FLAG_PAL)
        total_size -= 256 * 4;
    // Make it non-black by default...
    memset(data[0], 0xA3, total_size);
    માટે (પૂર્ણાંક i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    માટે (ગણના AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(data, linesizes1, pix_fmt, range, w, h);
        printf(",  black_%s_crc: ", av_color_range_name(range));
        જો (ret < 0) {
            printf("----------");
        } નહીંતર {
            અચલ AVCRC *crc = av_crc_get_table(AV_CRC_32_IEEE_LE);
            printf("0x%08"PRIx32, av_crc(crc, 0, data[0], total_size));
        }
    }
    av_freep(&data[0]);

    પાછા 0;
}

પૂર્ણાંક મુખ્ય(શૂન્ય)
{
    int64_t x, y;

    માટે (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        માટે (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            પૂર્ણાંક ret = av_image_check_size(x, y, 0, ખાલી);
            printf("%d", ret >= 0);
        }
        printf("\n");
    }
    printf("\n");

    માટે (પૂર્ણાંક i = 0; i < 2; i++) {
        printf(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        માટે (અચલ AVPixFmtDescriptor *desc = ખાલી; desc = av_pix_fmt_desc_next(desc);) {
            પૂર્ણાંક w = 64, h = 48;
            ગણના AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            જો (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                ચાલુ;

            printf("%-16s", desc->name);
            જો (i == 0)
                check_image_fill(pix_fmt, w, h);
            નહીંતર
                check_image_fill_black(desc, pix_fmt, w, h);
            printf("\n");
        }
    }

    પાછા 0;
}
