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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/crc.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    uint8_t buf[1999];
    పూర్ణాంకం i;
    స్థిర స్థిరరాశి గుర్తులేని p[7][3] = {
        { AV_చక్రీయ_తనిఖీ_32_IEEE_LE, 0xEDB88320, 0x3D5CDD04 },
        { AV_చక్రీయ_తనిఖీ_32_IEEE   , 0x04C11DB7, 0xC0F5BAE0 },
        { AV_చక్రీయ_తనిఖీ_24_IEEE   , 0x864CFB  , 0xB704CE   },
        { AV_చక్రీయ_తనిఖీ_16_ANSI_LE, 0xA001    , 0xBFD8     },
        { AV_చక్రీయ_తనిఖీ_16_ANSI   , 0x8005    , 0x1FBB     },
        { AV_చక్రీయ_తనిఖీ_8_ATM     , 0x07      , 0xE3       },
        { AV_చక్రీయ_తనిఖీ_8_EBU     , 0x1D      , 0xD6       },
    };
    స్థిరరాశి AVCRC *ctx;

    కొరకు (i = 0; i < పరిమాణం(buf); i++)
        buf[i] = i + i * i;

    కొరకు (i = 0; i < 7; i++) {
        ctx = av_చక్రీయ_తనిఖీ_get_పట్టిక(p[i][0]);
        రాయి("crc %08X = %X\n", p[i][1], av_చక్రీయ_తనిఖీ(ctx, 0, buf, పరిమాణం(buf)));
    }
    తిరిగి 0;
}
