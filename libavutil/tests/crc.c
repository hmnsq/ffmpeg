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

#समावेश "libavutil/crc.h"

पूर्णांक मुख्य(व्योम)
{
    uint8_t buf[1999];
    पूर्णांक i;
    अटल स्थिर अचिन्हित p[7][3] = {
        { AV_CRC_32_IEEE_LE, 0xEDB88320, 0x3D5CDD04 },
        { AV_CRC_32_IEEE   , 0x04C11DB7, 0xC0F5BAE0 },
        { AV_CRC_24_IEEE   , 0x864CFB  , 0xB704CE   },
        { AV_CRC_16_ANSI_LE, 0xA001    , 0xBFD8     },
        { AV_CRC_16_ANSI   , 0x8005    , 0x1FBB     },
        { AV_CRC_8_ATM     , 0x07      , 0xE3       },
        { AV_CRC_8_EBU     , 0x1D      , 0xD6       },
    };
    स्थिर AVCRC *ctx;

    क्रम (i = 0; i < माप(buf); i++)
        buf[i] = i + i * i;

    क्रम (i = 0; i < 7; i++) {
        ctx = av_crc_get_table(p[i][0]);
        म_लिखो("crc %08X = %X\n", p[i][1], av_crc(ctx, 0, buf, माप(buf)));
    }
    वापस 0;
}
