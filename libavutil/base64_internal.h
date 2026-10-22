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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_BASE64_ਅੰਦਰੂਨੀ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_BASE64_ਅੰਦਰੂਨੀ_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "intreadwrite.h"

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

ਸਥਿਰ ਸਤਰਅੰਦਰ ਅੱਖਰ *ff_base64_encode_c(ਅੱਖਰ *ਬਾਹਰਲਾ, ਅਚਲ uint8_t *ਵਿੱਚ_2, ਪੂਰਨ ਵਿੱਚ_ਮਾਪ, ਅਚਲ ਅੱਖਰ *b64)
{
    ਅੱਖਰ *ret, *dst;
    ਬਿਨਾਨਿਸ਼ਾਨੀ i_ਬਿੱਟ = 0;
    ਪੂਰਨ i_ਖਿਸਕਾਓ = 0;
    ਪੂਰਨ ਬਾਈਟਾਂ_ਬਚਿਆ = ਵਿੱਚ_ਮਾਪ;

    ret = dst = ਬਾਹਰਲਾ;
    ਜਦੋਂ (ਬਾਈਟਾਂ_ਬਚਿਆ > 3) {
        i_ਬਿੱਟ = AV_RB32(ਵਿੱਚ_2);
        ਵਿੱਚ_2 += 3; ਬਾਈਟਾਂ_ਬਚਿਆ -= 3;
        *dst++ = b64[ i_ਬਿੱਟ>>26        ];
        *dst++ = b64[(i_ਬਿੱਟ>>20) & 0x3F];
        *dst++ = b64[(i_ਬਿੱਟ>>14) & 0x3F];
        *dst++ = b64[(i_ਬਿੱਟ>>8 ) & 0x3F];
    }
    i_ਬਿੱਟ = 0;
    ਜਦੋਂ (ਬਾਈਟਾਂ_ਬਚਿਆ) {
        i_ਬਿੱਟ = (i_ਬਿੱਟ << 8) + *ਵਿੱਚ_2++;
        ਬਾਈਟਾਂ_ਬਚਿਆ--;
        i_ਖਿਸਕਾਓ += 8;
    }
    ਜਦੋਂ (i_ਖਿਸਕਾਓ > 0) {
        *dst++ = b64[(i_ਬਿੱਟ << 6 >> i_ਖਿਸਕਾਓ) & 0x3f];
        i_ਖਿਸਕਾਓ -= 6;
    }
    ਜਦੋਂ ((dst - ret) & 3)
        *dst++ = '=';
    *dst = '\0';

    ਵਾਪਸ ret;
}

#ਜੇ_ਅੰਤ /* AVUTIL_BASE64_INTERNAL_H */
