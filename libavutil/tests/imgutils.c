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

#അന്തര്ഭാവ "libavutil/imgutils.c"
#അന്തര്ഭാവ "libavutil/crc.h"
#അന്തര്ഭാവ "libavutil/mem.h"

സ്ഥിതം പൂർണ്ണസംഖ്യ check_image_fill(എണ്ണൽ AVPixelFormat pix_fmt, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h) {
    uint8_t *data[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    പൂർണ്ണസംഖ്യ i, total_size, linesizes[4];

    എങ്കിൽ (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        തിരികെ -1;
    വേണ്ടി (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    എങ്കിൽ (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        തിരികെ -1;
    total_size = av_image_fill_pointers(data, pix_fmt, h, (ശൂന്യം *)1, linesizes);
    എങ്കിൽ (total_size < 0)
        തിരികെ -1;
    വേണ്ടി (i = 0; i < 4 && data[i]; i++);
    printf("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    printf(", linesizes:");
    വേണ്ടി (i = 0; i < 4; i++)
        printf(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    printf(", plane_sizes:");
    വേണ്ടി (i = 0; i < 4; i++)
        printf(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    വേണ്ടി (i = 0; i < 3 && data[i + 1]; i++)
        offsets[i] = data[i + 1] - data[i];
    printf(", plane_offsets:");
    വേണ്ടി (i = 0; i < 3; i++)
        printf(" %5td", offsets[i]);
    printf(", total_size: %d", total_size);

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ check_image_fill_black(സ്ഥിരം AVPixFmtDescriptor *desc, എണ്ണൽ AVPixelFormat pix_fmt, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h)
{
    uint8_t *data[4];
    ptrdiff_t linesizes1[4];
    പൂർണ്ണസംഖ്യ ret, total_size, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;
    total_size = av_image_alloc(data, linesizes, w, h, pix_fmt, 4);
    എങ്കിൽ (total_size < 0) {
        printf("alloc failure");
        തിരികെ total_size;
    }
    printf("total_size: %6d", total_size);
    എങ്കിൽ (desc->flags & AV_PIX_FMT_FLAG_PAL)
        total_size -= 256 * 4;
    // Make it non-black by default...
    memset(data[0], 0xA3, total_size);
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    വേണ്ടി (എണ്ണൽ AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(data, linesizes1, pix_fmt, range, w, h);
        printf(",  black_%s_crc: ", av_color_range_name(range));
        എങ്കിൽ (ret < 0) {
            printf("----------");
        } അല്ലെങ്കിൽ {
            സ്ഥിരം AVCRC *crc = av_crc_get_table(AV_CRC_32_IEEE_LE);
            printf("0x%08"PRIx32, av_crc(crc, 0, data[0], total_size));
        }
    }
    av_freep(&data[0]);

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    int64_t x, y;

    വേണ്ടി (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        വേണ്ടി (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            പൂർണ്ണസംഖ്യ ret = av_image_check_size(x, y, 0, ശൂന്യ);
            printf("%d", ret >= 0);
        }
        printf("\n");
    }
    printf("\n");

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < 2; i++) {
        printf(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        വേണ്ടി (സ്ഥിരം AVPixFmtDescriptor *desc = ശൂന്യ; desc = av_pix_fmt_desc_next(desc);) {
            പൂർണ്ണസംഖ്യ w = 64, h = 48;
            എണ്ണൽ AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            എങ്കിൽ (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                തുടരുക;

            printf("%-16s", desc->name);
            എങ്കിൽ (i == 0)
                check_image_fill(pix_fmt, w, h);
            അല്ലെങ്കിൽ
                check_image_fill_black(desc, pix_fmt, w, h);
            printf("\n");
        }
    }

    തിരികെ 0;
}
