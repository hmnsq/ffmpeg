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

#شامل <stdint.h>
#شامل <stdio.h>

#شامل "libavutil/md5.h"

ساکن خالی print_md5(uint8_t *md5)
{
    صحیح i;
    برائے (i = 0; i < 16; i++)
        لکھو("%02x", md5[i]);
    لکھو("\n");
}

صحیح مین(خالی)
{
    uint8_t md5val[16];
    صحیح i;

    uint8_t اندر[1000];

    برائے (i = 0; i < 1000; i++)
        اندر[i] = i * i;
    av_md5_مجموع(md5val, اندر, 1000);
    print_md5(md5val);
    av_md5_مجموع(md5val, اندر, 63);
    print_md5(md5val);
    av_md5_مجموع(md5val, اندر, 64);
    print_md5(md5val);
    av_md5_مجموع(md5val, اندر, 65);
    print_md5(md5val);
    برائے (i = 0; i < 1000; i++)
        اندر[i] = i % 127;
    av_md5_مجموع(md5val, اندر, 999);
    print_md5(md5val);

    واپس 0;
}
