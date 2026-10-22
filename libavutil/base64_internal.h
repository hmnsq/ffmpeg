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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_BASE64_اندروني_H
#وصف_ڪريو AVUTIL_BASE64_اندروني_H

#ضمن <stdint.h>
#ضمن "intreadwrite.h"

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

ساكن مضمن حرف *ff_base64_encode_c(حرف *ٻاهريون, ثابت uint8_t *اندريون, صحيح اندريون_سائيز, ثابت حرف *b64)
{
    حرف *ret, *dst;
    بنانشان i_بٽ = 0;
    صحيح i_سرڪايو = 0;
    صحيح بائيٽون_بچيل = اندريون_سائيز;

    ret = dst = ٻاهريون;
    طالما (بائيٽون_بچيل > 3) {
        i_بٽ = AV_RB32(اندريون);
        اندريون += 3; بائيٽون_بچيل -= 3;
        *dst++ = b64[ i_بٽ>>26        ];
        *dst++ = b64[(i_بٽ>>20) & 0x3F];
        *dst++ = b64[(i_بٽ>>14) & 0x3F];
        *dst++ = b64[(i_بٽ>>8 ) & 0x3F];
    }
    i_بٽ = 0;
    طالما (بائيٽون_بچيل) {
        i_بٽ = (i_بٽ << 8) + *اندريون++;
        بائيٽون_بچيل--;
        i_سرڪايو += 8;
    }
    طالما (i_سرڪايو > 0) {
        *dst++ = b64[(i_بٽ << 6 >> i_سرڪايو) & 0x3f];
        i_سرڪايو -= 6;
    }
    طالما ((dst - ret) & 3)
        *dst++ = '=';
    *dst = '\0';

    أرجع ret;
}

#جيڪڏهن_پورو /* AVUTIL_BASE64_INTERNAL_H */
