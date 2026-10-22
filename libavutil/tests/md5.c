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

#समावेश <stdint.h>
#समावेश <stdio.h>

#समावेश "libavutil/md5.h"

अटल व्योम print_md5(uint8_t *md5)
{
    पूर्णांक i;
    क्रम (i = 0; i < 16; i++)
        म_लिखो("%02x", md5[i]);
    म_लिखो("\n");
}

पूर्णांक मुख्य(व्योम)
{
    uint8_t md5val[16];
    पूर्णांक i;

    uint8_t in[1000];

    क्रम (i = 0; i < 1000; i++)
        in[i] = i * i;
    av_md5_योग(md5val, in, 1000);
    print_md5(md5val);
    av_md5_योग(md5val, in, 63);
    print_md5(md5val);
    av_md5_योग(md5val, in, 64);
    print_md5(md5val);
    av_md5_योग(md5val, in, 65);
    print_md5(md5val);
    क्रम (i = 0; i < 1000; i++)
        in[i] = i % 127;
    av_md5_योग(md5val, in, 999);
    print_md5(md5val);

    वापस 0;
}
