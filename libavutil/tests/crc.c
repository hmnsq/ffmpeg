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

#ضمن "libavutil/crc.h"

صحيح اصلي(فراغ)
{
    uint8_t buf[1999];
    صحيح i;
    ساكن ثابت بینښه p[7][3] = {
        { AV_دوراني_ازموینه_32_IEEE_LE, 0xEDB88320, 0x3D5CDD04 },
        { AV_دوراني_ازموینه_32_IEEE   , 0x04C11DB7, 0xC0F5BAE0 },
        { AV_دوراني_ازموینه_24_IEEE   , 0x864CFB  , 0xB704CE   },
        { AV_دوراني_ازموینه_16_ANSI_LE, 0xA001    , 0xBFD8     },
        { AV_دوراني_ازموینه_16_ANSI   , 0x8005    , 0x1FBB     },
        { AV_دوراني_ازموینه_8_ATM     , 0x07      , 0xE3       },
        { AV_دوراني_ازموینه_8_EBU     , 0x1D      , 0xD6       },
    };
    ثابت AVCRC *ctx;

    لكل (i = 0; i < حجم(buf); i++)
        buf[i] = i + i * i;

    لكل (i = 0; i < 7; i++) {
        ctx = av_دوراني_ازموینه_get_جدول(p[i][0]);
        چاپ_کړه("crc %08X = %X\n", p[i][1], av_دوراني_ازموینه(ctx, 0, buf, حجم(buf)));
    }
    أرجع 0;
}
