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

#ifndef AVUTIL_BASE64_INTERNAL_H
#define AVUTIL_BASE64_INTERNAL_H

#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ "intreadwrite.h"

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

স্থির অন্তঃস্থ ৱর্ণ *ff_base64_encode_c(ৱর্ণ *out, ধ্রুৱ uint8_t *in, পূর্ণাঙ্ক in_size, ধ্রুৱ ৱর্ণ *b64)
{
    ৱর্ণ *ret, *dst;
    unsigned i_bits = 0;
    পূর্ণাঙ্ক i_shift = 0;
    পূর্ণাঙ্ক bytes_remaining = in_size;

    ret = dst = out;
    যেতিয়ালৈ (bytes_remaining > 3) {
        i_bits = AV_RB32(in);
        in += 3; bytes_remaining -= 3;
        *dst++ = b64[ i_bits>>26        ];
        *dst++ = b64[(i_bits>>20) & 0x3F];
        *dst++ = b64[(i_bits>>14) & 0x3F];
        *dst++ = b64[(i_bits>>8 ) & 0x3F];
    }
    i_bits = 0;
    যেতিয়ালৈ (bytes_remaining) {
        i_bits = (i_bits << 8) + *in++;
        bytes_remaining--;
        i_shift += 8;
    }
    যেতিয়ালৈ (i_shift > 0) {
        *dst++ = b64[(i_bits << 6 >> i_shift) & 0x3f];
        i_shift -= 6;
    }
    যেতিয়ালৈ ((dst - ret) & 3)
        *dst++ = '=';
    *dst = '\0';

    ঘূৰাই ret;
}

#endif /* AVUTIL_BASE64_INTERNAL_H */
