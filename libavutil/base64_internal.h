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

#यदि_अपरिभाषितम् AVUTIL_BASE64_आन्तरिकम्_H
#परिभाषय AVUTIL_BASE64_आन्तरिकम्_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "intreadwrite.h"

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

स्थिर अन्तःस्थ वर्ण *ff_base64_encode_c(वर्ण *बहिर्गमनम्, ध्रुव uint8_t *अन्तर्, पूर्णाङ्क अन्तर्_आकार, ध्रुव वर्ण *b64)
{
    वर्ण *ret, *dst;
    अचिह्नित i_द्वयङ्काः = 0;
    पूर्णाङ्क i_सरणम् = 0;
    पूर्णाङ्क अष्टकानि_remaining = अन्तर्_आकार;

    ret = dst = बहिर्गमनम्;
    यावत् (अष्टकानि_remaining > 3) {
        i_द्वयङ्काः = AV_RB32(अन्तर्);
        अन्तर् += 3; अष्टकानि_remaining -= 3;
        *dst++ = b64[ i_द्वयङ्काः>>26        ];
        *dst++ = b64[(i_द्वयङ्काः>>20) & 0x3F];
        *dst++ = b64[(i_द्वयङ्काः>>14) & 0x3F];
        *dst++ = b64[(i_द्वयङ्काः>>8 ) & 0x3F];
    }
    i_द्वयङ्काः = 0;
    यावत् (अष्टकानि_remaining) {
        i_द्वयङ्काः = (i_द्वयङ्काः << 8) + *अन्तर्++;
        अष्टकानि_remaining--;
        i_सरणम् += 8;
    }
    यावत् (i_सरणम् > 0) {
        *dst++ = b64[(i_द्वयङ्काः << 6 >> i_सरणम्) & 0x3f];
        i_सरणम् -= 6;
    }
    यावत् ((dst - ret) & 3)
        *dst++ = '=';
    *dst = '\0';

    प्रत्यागम ret;
}

#यदि_अन्तः /* AVUTIL_BASE64_INTERNAL_H */
