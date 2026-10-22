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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/crc.h"

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    uint8_t buf[1999];
    ಪೂರ್ಣಾಂಕ i;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ p[7][3] = {
        { AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_IEEE_LE, 0xEDB88320, 0x3D5CDD04 },
        { AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_IEEE   , 0x04C11DB7, 0xC0F5BAE0 },
        { AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_24_IEEE   , 0x864CFB  , 0xB704CE   },
        { AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_16_ANSI_LE, 0xA001    , 0xBFD8     },
        { AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_16_ANSI   , 0x8005    , 0x1FBB     },
        { AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_8_ATM     , 0x07      , 0xE3       },
        { AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_8_EBU     , 0x1D      , 0xD6       },
    };
    ಸ್ಥಿರಾಂಕ AVCRC *ctx;

    ಗಾಗಿ (i = 0; i < ಗಾತ್ರ(buf); i++)
        buf[i] = i + i * i;

    ಗಾಗಿ (i = 0; i < 7; i++) {
        ctx = av_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_get_ಕೋಷ್ಟಕ(p[i][0]);
        ಬರೆ("crc %08X = %X\n", p[i][1], av_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ(ctx, 0, buf, ಗಾತ್ರ(buf)));
    }
    ಹಿಂತಿರುಗಿ 0;
}
