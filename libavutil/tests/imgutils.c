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
    uint8_t *दत्त[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    पूर्णाङ्क i, योग_आकार, linesizes[4];

    यदि (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        प्रत्यागम -1;
    प्रति (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    यदि (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        प्रत्यागम -1;
    योग_आकार = av_image_fill_सूचकाः(दत्त, pix_fmt, h, (शून्य *)1, linesizes);
    यदि (योग_आकार < 0)
        प्रत्यागम -1;
    प्रति (i = 0; i < 4 && दत्त[i]; i++);
    प्रारूप_लिख("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    प्रारूप_लिख(", linesizes:");
    प्रति (i = 0; i < 4; i++)
        प्रारूप_लिख(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    प्रारूप_लिख(", plane_sizes:");
    प्रति (i = 0; i < 4; i++)
        प्रारूप_लिख(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    प्रति (i = 0; i < 3 && दत्त[i + 1]; i++)
        offsets[i] = दत्त[i + 1] - दत्त[i];
    प्रारूप_लिख(", plane_offsets:");
    प्रति (i = 0; i < 3; i++)
        प्रारूप_लिख(" %5td", offsets[i]);
    प्रारूप_लिख(", total_size: %d", योग_आकार);

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क check_image_fill_black(ध्रुव AVPixFmtDescriptor *desc, गणना AVPixelFormat pix_fmt, पूर्णाङ्क w, पूर्णाङ्क h)
{
    uint8_t *दत्त[4];
    ptrdiff_t linesizes1[4];
    पूर्णाङ्क ret, योग_आकार, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    यदि (ret < 0)
        प्रत्यागम ret;
    योग_आकार = av_image_alloc(दत्त, linesizes, w, h, pix_fmt, 4);
    यदि (योग_आकार < 0) {
        प्रारूप_लिख("alloc failure");
        प्रत्यागम योग_आकार;
    }
    प्रारूप_लिख("total_size: %6d", योग_आकार);
    यदि (desc->flags & AV_PIX_FMT_FLAG_PAL)
        योग_आकार -= 256 * 4;
    // Make it non-black by default...
    स्मृतिं_पूरय(दत्त[0], 0xA3, योग_आकार);
    प्रति (पूर्णाङ्क i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    प्रति (गणना AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(दत्त, linesizes1, pix_fmt, range, w, h);
        प्रारूप_लिख(",  black_%s_crc: ", av_color_range_name(range));
        यदि (ret < 0) {
            प्रारूप_लिख("----------");
        } अन्यथा {
            ध्रुव AVCRC *crc = av_crc_get_सारणी(AV_CRC_32_IEEE_LE);
            प्रारूप_लिख("0x%08"PRIx32, av_crc(crc, 0, दत्त[0], योग_आकार));
        }
    }
    av_freep(&दत्त[0]);

    प्रत्यागम 0;
}

पूर्णाङ्क मुख्यम्(शून्य)
{
    int64_t x, y;

    प्रति (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        प्रति (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            पूर्णाङ्क ret = av_image_check_आकार(x, y, 0, रिक्त);
            प्रारूप_लिख("%d", ret >= 0);
        }
        प्रारूप_लिख("\n");
    }
    प्रारूप_लिख("\n");

    प्रति (पूर्णाङ्क i = 0; i < 2; i++) {
        प्रारूप_लिख(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        प्रति (ध्रुव AVPixFmtDescriptor *desc = रिक्त; desc = av_pix_fmt_desc_अग्र(desc);) {
            पूर्णाङ्क w = 64, h = 48;
            गणना AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            यदि (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                अनुवर्त;

            प्रारूप_लिख("%-16s", desc->name);
            यदि (i == 0)
                check_image_fill(pix_fmt, w, h);
            अन्यथा
                check_image_fill_black(desc, pix_fmt, w, h);
            प्रारूप_लिख("\n");
        }
    }

    प्रत्यागम 0;
}
