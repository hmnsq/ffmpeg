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

#समावेश "libavutil/imgutils.c"
#समावेश "libavutil/crc.h"
#समावेश "libavutil/mem.h"

अटल पूर्णांक check_image_fill(क्रमागत AVPixelFormat pix_fmt, पूर्णांक w, पूर्णांक h) {
    uint8_t *तथ्य[4];
    माप_प्रकार sizes[4];
    सूचक_भेद_प्रकार linesizes1[4], offsets[3] = { 0 };
    पूर्णांक i, योग_आकार, linesizes[4];

    अगर (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        वापस -1;
    क्रम (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    अगर (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        वापस -1;
    योग_आकार = av_image_fill_pointers(तथ्य, pix_fmt, h, (व्योम *)1, linesizes);
    अगर (योग_आकार < 0)
        वापस -1;
    क्रम (i = 0; i < 4 && तथ्य[i]; i++);
    म_लिखो("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    म_लिखो(", linesizes:");
    क्रम (i = 0; i < 4; i++)
        म_लिखो(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    म_लिखो(", plane_sizes:");
    क्रम (i = 0; i < 4; i++)
        म_लिखो(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    क्रम (i = 0; i < 3 && तथ्य[i + 1]; i++)
        offsets[i] = तथ्य[i + 1] - तथ्य[i];
    म_लिखो(", plane_offsets:");
    क्रम (i = 0; i < 3; i++)
        म_लिखो(" %5td", offsets[i]);
    म_लिखो(", total_size: %d", योग_आकार);

    वापस 0;
}

अटल पूर्णांक check_image_fill_black(स्थिर AVPixFmtDescriptor *desc, क्रमागत AVPixelFormat pix_fmt, पूर्णांक w, पूर्णांक h)
{
    uint8_t *तथ्य[4];
    सूचक_भेद_प्रकार linesizes1[4];
    पूर्णांक ret, योग_आकार, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    अगर (ret < 0)
        वापस ret;
    योग_आकार = av_image_alloc(तथ्य, linesizes, w, h, pix_fmt, 4);
    अगर (योग_आकार < 0) {
        म_लिखो("alloc failure");
        वापस योग_आकार;
    }
    म_लिखो("total_size: %6d", योग_आकार);
    अगर (desc->flags & AV_PIX_FMT_FLAG_PAL)
        योग_आकार -= 256 * 4;
    // Make it non-black by default...
    स_रखो(तथ्य[0], 0xA3, योग_आकार);
    क्रम (पूर्णांक i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    क्रम (क्रमागत AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(तथ्य, linesizes1, pix_fmt, range, w, h);
        म_लिखो(",  black_%s_crc: ", av_color_range_name(range));
        अगर (ret < 0) {
            म_लिखो("----------");
        } अन्यथा {
            स्थिर AVCRC *crc = av_crc_get_table(AV_CRC_32_IEEE_LE);
            म_लिखो("0x%08"PRIx32, av_crc(crc, 0, तथ्य[0], योग_आकार));
        }
    }
    av_freep(&तथ्य[0]);

    वापस 0;
}

पूर्णांक मुख्य(व्योम)
{
    int64_t x, y;

    क्रम (y = -1; y<अच_पूर्णांक_उच्च; y+= y/2 + 1) {
        क्रम (x = -1; x<अच_पूर्णांक_उच्च; x+= x/2 + 1) {
            पूर्णांक ret = av_image_check_आकार(x, y, 0, शून्य);
            म_लिखो("%d", ret >= 0);
        }
        म_लिखो("\n");
    }
    म_लिखो("\n");

    क्रम (पूर्णांक i = 0; i < 2; i++) {
        म_लिखो(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        क्रम (स्थिर AVPixFmtDescriptor *desc = शून्य; desc = av_pix_fmt_desc_अग्र(desc);) {
            पूर्णांक w = 64, h = 48;
            क्रमागत AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            अगर (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                जारी;

            म_लिखो("%-16s", desc->name);
            अगर (i == 0)
                check_image_fill(pix_fmt, w, h);
            अन्यथा
                check_image_fill_black(desc, pix_fmt, w, h);
            म_लिखो("\n");
        }
    }

    वापस 0;
}
