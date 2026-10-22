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

#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <stdio.h>

#অন্তর্ভাৱ "libavutil/crc.h"

পূর্ণাঙ্ক main(শূন্য)
{
    uint8_t buf[1999];
    পূর্ণাঙ্ক i;
    স্থির ধ্রুৱ unsigned p[7][3] = {
        { AV_CRC_32_IEEE_LE, 0xEDB88320, 0x3D5CDD04 },
        { AV_CRC_32_IEEE   , 0x04C11DB7, 0xC0F5BAE0 },
        { AV_CRC_24_IEEE   , 0x864CFB  , 0xB704CE   },
        { AV_CRC_16_ANSI_LE, 0xA001    , 0xBFD8     },
        { AV_CRC_16_ANSI   , 0x8005    , 0x1FBB     },
        { AV_CRC_8_ATM     , 0x07      , 0xE3       },
        { AV_CRC_8_EBU     , 0x1D      , 0xD6       },
    };
    ধ্রুৱ AVCRC *ctx;

    বাবে (i = 0; i < পরিমাণ(buf); i++)
        buf[i] = i + i * i;

    বাবে (i = 0; i < 7; i++) {
        ctx = av_crc_get_table(p[i][0]);
        printf("crc %08X = %X\n", p[i][1], av_crc(ctx, 0, buf, পরিমাণ(buf)));
    }
    ঘূৰাই 0;
}
