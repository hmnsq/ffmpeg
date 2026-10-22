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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/md5.h"

स्थिर शून्य print_md5(uint8_t *md5)
{
    पूर्णाङ्क i;
    प्रति (i = 0; i < 16; i++)
        प्रारूप_लिख("%02x", md5[i]);
    प्रारूप_लिख("\n");
}

पूर्णाङ्क मुख्यम्(शून्य)
{
    uint8_t md5val[16];
    पूर्णाङ्क i;

    uint8_t अन्तर्[1000];

    प्रति (i = 0; i < 1000; i++)
        अन्तर्[i] = i * i;
    av_md5_योग(md5val, अन्तर्, 1000);
    print_md5(md5val);
    av_md5_योग(md5val, अन्तर्, 63);
    print_md5(md5val);
    av_md5_योग(md5val, अन्तर्, 64);
    print_md5(md5val);
    av_md5_योग(md5val, अन्तर्, 65);
    print_md5(md5val);
    प्रति (i = 0; i < 1000; i++)
        अन्तर्[i] = i % 127;
    av_md5_योग(md5val, अन्तर्, 999);
    print_md5(md5val);

    प्रत्यागम 0;
}
