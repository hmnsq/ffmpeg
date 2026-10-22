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

स्थिर पूर्णांक check_image_fill(गणना AVPixelFormat pix_fmt, पूर्णांक w, पूर्णांक h) {
    uint8_t *data[4];
    माप_प्रकार sizes[4];
    सूचक_भेद_प्रकार linesizes1[4], offsets[3] = { 0 };
    पूर्णांक i, total_size, linesizes[4];

    जर (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        परत -1;
    साठी (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    जर (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        परत -1;
    total_size = av_image_fill_pointers(data, pix_fmt, h, (शून्य *)1, linesizes);
    जर (total_size < 0)
        परत -1;
    साठी (i = 0; i < 4 && data[i]; i++);
    म_लिखो("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    म_लिखो(", linesizes:");
    साठी (i = 0; i < 4; i++)
        म_लिखो(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    म_लिखो(", plane_sizes:");
    साठी (i = 0; i < 4; i++)
        म_लिखो(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    साठी (i = 0; i < 3 && data[i + 1]; i++)
        offsets[i] = data[i + 1] - data[i];
    म_लिखो(", plane_offsets:");
    साठी (i = 0; i < 3; i++)
        म_लिखो(" %5td", offsets[i]);
    म_लिखो(", total_size: %d", total_size);

    परत 0;
}

स्थिर पूर्णांक check_image_fill_black(स्थिरांक AVPixFmtDescriptor *desc, गणना AVPixelFormat pix_fmt, पूर्णांक w, पूर्णांक h)
{
    uint8_t *data[4];
    सूचक_भेद_प्रकार linesizes1[4];
    पूर्णांक ret, total_size, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    जर (ret < 0)
        परत ret;
    total_size = av_image_alloc(data, linesizes, w, h, pix_fmt, 4);
    जर (total_size < 0) {
        म_लिखो("alloc failure");
        परत total_size;
    }
    म_लिखो("total_size: %6d", total_size);
    जर (desc->flags & AV_PIX_FMT_FLAG_PAL)
        total_size -= 256 * 4;
    // Make it non-black by default...
    स_रखो(data[0], 0xA3, total_size);
    साठी (पूर्णांक i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    साठी (गणना AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(data, linesizes1, pix_fmt, range, w, h);
        म_लिखो(",  black_%s_crc: ", av_color_range_name(range));
        जर (ret < 0) {
            म_लिखो("----------");
        } अन्यथा {
            स्थिरांक AVCRC *crc = av_crc_get_table(AV_CRC_32_IEEE_LE);
            म_लिखो("0x%08"PRIx32, av_crc(crc, 0, data[0], total_size));
        }
    }
    av_freep(&data[0]);

    परत 0;
}

पूर्णांक main(शून्य)
{
    int64_t x, y;

    साठी (y = -1; y<अच_पूर्णांक_उच्च; y+= y/2 + 1) {
        साठी (x = -1; x<अच_पूर्णांक_उच्च; x+= x/2 + 1) {
            पूर्णांक ret = av_image_check_size(x, y, 0, रिक्त);
            म_लिखो("%d", ret >= 0);
        }
        म_लिखो("\n");
    }
    म_लिखो("\n");

    साठी (पूर्णांक i = 0; i < 2; i++) {
        म_लिखो(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        साठी (स्थिरांक AVPixFmtDescriptor *desc = रिक्त; desc = av_pix_fmt_desc_next(desc);) {
            पूर्णांक w = 64, h = 48;
            गणना AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            जर (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                सुरूठेवा;

            म_लिखो("%-16s", desc->name);
            जर (i == 0)
                check_image_fill(pix_fmt, w, h);
            अन्यथा
                check_image_fill_black(desc, pix_fmt, w, h);
            म_लिखो("\n");
        }
    }

    परत 0;
}
