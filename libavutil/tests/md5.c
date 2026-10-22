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

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdio.h>

#অন্তর্ভাব "libavutil/md5.h"

স্থির শূন্য print_md5(uint8_t *md5)
{
    পূর্ণসংখ্যা i;
    জন্য (i = 0; i < 16; i++)
        printf("%02x", md5[i]);
    printf("\n");
}

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    uint8_t md5val[16];
    পূর্ণসংখ্যা i;

    uint8_t in[1000];

    জন্য (i = 0; i < 1000; i++)
        in[i] = i * i;
    av_md5_যোগ(md5val, in, 1000);
    print_md5(md5val);
    av_md5_যোগ(md5val, in, 63);
    print_md5(md5val);
    av_md5_যোগ(md5val, in, 64);
    print_md5(md5val);
    av_md5_যোগ(md5val, in, 65);
    print_md5(md5val);
    জন্য (i = 0; i < 1000; i++)
        in[i] = i % 127;
    av_md5_যোগ(md5val, in, 999);
    print_md5(md5val);

    ফেরত 0;
}
