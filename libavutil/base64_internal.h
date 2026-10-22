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

#جے_بنا_تعریف AVUTIL_BASE64_اندرونی_H
#تعریف_کرو AVUTIL_BASE64_اندرونی_H

#ضمن <stdint.h>
#ضمن "intreadwrite.h"

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

ساكن مضمن حرف *ff_base64_encode_c(حرف *باہرلا, ثابت uint8_t *وچ, صحيح وچ_ناپ, ثابت حرف *b64)
{
    حرف *ret, *dst;
    بنانشانی i_بٹ = 0;
    صحيح i_کھسکاؤ = 0;
    صحيح بائٹاں_بچیا = وچ_ناپ;

    ret = dst = باہرلا;
    طالما (بائٹاں_بچیا > 3) {
        i_بٹ = AV_RB32(وچ);
        وچ += 3; بائٹاں_بچیا -= 3;
        *dst++ = b64[ i_بٹ>>26        ];
        *dst++ = b64[(i_بٹ>>20) & 0x3F];
        *dst++ = b64[(i_بٹ>>14) & 0x3F];
        *dst++ = b64[(i_بٹ>>8 ) & 0x3F];
    }
    i_بٹ = 0;
    طالما (بائٹاں_بچیا) {
        i_بٹ = (i_بٹ << 8) + *وچ++;
        بائٹاں_بچیا--;
        i_کھسکاؤ += 8;
    }
    طالما (i_کھسکاؤ > 0) {
        *dst++ = b64[(i_بٹ << 6 >> i_کھسکاؤ) & 0x3f];
        i_کھسکاؤ -= 6;
    }
    طالما ((dst - ret) & 3)
        *dst++ = '=';
    *dst = '\0';

    أرجع ret;
}

#جے_انت /* AVUTIL_BASE64_INTERNAL_H */
