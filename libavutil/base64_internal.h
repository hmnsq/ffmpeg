/*
 * Copyright (c) 2006 Ryan Martell. (rdm4@martellventures.com)
 *
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

#నిర్వచితం_కాకపోతే AVUTIL_BASE64_అంతర్గత_H
#నిర్వచించు AVUTIL_BASE64_అంతర్గత_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "intreadwrite.h"

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

స్థిర అంతఃవరుస అక్షరం *ff_base64_encode_c(అక్షరం *బహిర్గతం, స్థిరరాశి uint8_t *లోపల, పూర్ణాంకం లోపల_కొలత, స్థిరరాశి అక్షరం *b64)
{
    అక్షరం *ret, *dst;
    గుర్తులేని i_బిట్లు = 0;
    పూర్ణాంకం i_జరుపు = 0;
    పూర్ణాంకం బైట్లు_మిగిలిన = లోపల_కొలత;

    ret = dst = బహిర్గతం;
    అయితే (బైట్లు_మిగిలిన > 3) {
        i_బిట్లు = AV_RB32(లోపల);
        లోపల += 3; బైట్లు_మిగిలిన -= 3;
        *dst++ = b64[ i_బిట్లు>>26        ];
        *dst++ = b64[(i_బిట్లు>>20) & 0x3F];
        *dst++ = b64[(i_బిట్లు>>14) & 0x3F];
        *dst++ = b64[(i_బిట్లు>>8 ) & 0x3F];
    }
    i_బిట్లు = 0;
    అయితే (బైట్లు_మిగిలిన) {
        i_బిట్లు = (i_బిట్లు << 8) + *లోపల++;
        బైట్లు_మిగిలిన--;
        i_జరుపు += 8;
    }
    అయితే (i_జరుపు > 0) {
        *dst++ = b64[(i_బిట్లు << 6 >> i_జరుపు) & 0x3f];
        i_జరుపు -= 6;
    }
    అయితే ((dst - ret) & 3)
        *dst++ = '=';
    *dst = '\0';

    తిరిగి ret;
}

#అయితే_ముగింపు /* AVUTIL_BASE64_INTERNAL_H */
