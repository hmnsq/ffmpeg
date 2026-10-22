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

#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdio.h>

#അന്തര്ഭാവ "libavutil/md5.h"

സ്ഥിതം ശൂന്യം print_md5(uint8_t *md5)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < 16; i++)
        printf("%02x", md5[i]);
    printf("\n");
}

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    uint8_t md5val[16];
    പൂർണ്ണസംഖ്യ i;

    uint8_t in[1000];

    വേണ്ടി (i = 0; i < 1000; i++)
        in[i] = i * i;
    av_md5_sum(md5val, in, 1000);
    print_md5(md5val);
    av_md5_sum(md5val, in, 63);
    print_md5(md5val);
    av_md5_sum(md5val, in, 64);
    print_md5(md5val);
    av_md5_sum(md5val, in, 65);
    print_md5(md5val);
    വേണ്ടി (i = 0; i < 1000; i++)
        in[i] = i % 127;
    av_md5_sum(md5val, in, 999);
    print_md5(md5val);

    തിരികെ 0;
}
