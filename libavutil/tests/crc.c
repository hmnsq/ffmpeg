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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/crc.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    uint8_t buf[1999];
    ਪੂਰਨ i;
    ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ p[7][3] = {
        { AV_ਚੱਕਰੀ_ਜਾਂਚ_32_IEEE_LE, 0xEDB88320, 0x3D5CDD04 },
        { AV_ਚੱਕਰੀ_ਜਾਂਚ_32_IEEE   , 0x04C11DB7, 0xC0F5BAE0 },
        { AV_ਚੱਕਰੀ_ਜਾਂਚ_24_IEEE   , 0x864CFB  , 0xB704CE   },
        { AV_ਚੱਕਰੀ_ਜਾਂਚ_16_ANSI_LE, 0xA001    , 0xBFD8     },
        { AV_ਚੱਕਰੀ_ਜਾਂਚ_16_ANSI   , 0x8005    , 0x1FBB     },
        { AV_ਚੱਕਰੀ_ਜਾਂਚ_8_ATM     , 0x07      , 0xE3       },
        { AV_ਚੱਕਰੀ_ਜਾਂਚ_8_EBU     , 0x1D      , 0xD6       },
    };
    ਅਚਲ AVCRC *ctx;

    ਲਈ (i = 0; i < ਆਕਾਰ(buf); i++)
        buf[i] = i + i * i;

    ਲਈ (i = 0; i < 7; i++) {
        ctx = av_ਚੱਕਰੀ_ਜਾਂਚ_get_ਸਾਰਣੀ(p[i][0]);
        ਲਿਖੋ("crc %08X = %X\n", p[i][1], av_ਚੱਕਰੀ_ਜਾਂਚ(ctx, 0, buf, ਆਕਾਰ(buf)));
    }
    ਵਾਪਸ 0;
}
