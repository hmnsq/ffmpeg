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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/md5.h"

ਸਥਿਰ ਖਾਲੀ print_md5(uint8_t *md5)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < 16; i++)
        ਲਿਖੋ("%02x", md5[i]);
    ਲਿਖੋ("\n");
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    uint8_t md5val[16];
    ਪੂਰਨ i;

    uint8_t ਵਿੱਚ_2[1000];

    ਲਈ (i = 0; i < 1000; i++)
        ਵਿੱਚ_2[i] = i * i;
    av_md5_ਜੋੜ(md5val, ਵਿੱਚ_2, 1000);
    print_md5(md5val);
    av_md5_ਜੋੜ(md5val, ਵਿੱਚ_2, 63);
    print_md5(md5val);
    av_md5_ਜੋੜ(md5val, ਵਿੱਚ_2, 64);
    print_md5(md5val);
    av_md5_ਜੋੜ(md5val, ਵਿੱਚ_2, 65);
    print_md5(md5val);
    ਲਈ (i = 0; i < 1000; i++)
        ਵਿੱਚ_2[i] = i % 127;
    av_md5_ਜੋੜ(md5val, ਵਿੱਚ_2, 999);
    print_md5(md5val);

    ਵਾਪਸ 0;
}
