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

#ضمن <stdint.h>
#ضمن <stdio.h>

#ضمن "libavutil/md5.h"

ساكن فراغ print_md5(uint8_t *md5)
{
    صحيح i;
    لكل (i = 0; i < 16; i++)
        چاپ_کن("%02x", md5[i]);
    چاپ_کن("\n");
}

صحيح اصلی(فراغ)
{
    uint8_t md5val[16];
    صحيح i;

    uint8_t درون[1000];

    لكل (i = 0; i < 1000; i++)
        درون[i] = i * i;
    av_md5_جمع(md5val, درون, 1000);
    print_md5(md5val);
    av_md5_جمع(md5val, درون, 63);
    print_md5(md5val);
    av_md5_جمع(md5val, درون, 64);
    print_md5(md5val);
    av_md5_جمع(md5val, درون, 65);
    print_md5(md5val);
    لكل (i = 0; i < 1000; i++)
        درون[i] = i % 127;
    av_md5_جمع(md5val, درون, 999);
    print_md5(md5val);

    أرجع 0;
}
