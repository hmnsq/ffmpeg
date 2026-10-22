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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_BASE64_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_BASE64_ಆಂತರಿಕ_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಅಕ್ಷರ *ff_base64_encode_c(ಅಕ್ಷರ *ಹೊರಹೋಗು, ಸ್ಥಿರಾಂಕ uint8_t *ಒಳ, ಪೂರ್ಣಾಂಕ ಒಳ_ಗಾತ್ರ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *b64)
{
    ಅಕ್ಷರ *ret, *dst;
    ಚಿಹ್ನೆರಹಿತ i_ಬಿಟ್ಟುಗಳು = 0;
    ಪೂರ್ಣಾಂಕ i_ಸರಿಸು = 0;
    ಪೂರ್ಣಾಂಕ ಬೈಟುಗಳು_ಉಳಿದ = ಒಳ_ಗಾತ್ರ;

    ret = dst = ಹೊರಹೋಗು;
    ಆಗ (ಬೈಟುಗಳು_ಉಳಿದ > 3) {
        i_ಬಿಟ್ಟುಗಳು = AV_RB32(ಒಳ);
        ಒಳ += 3; ಬೈಟುಗಳು_ಉಳಿದ -= 3;
        *dst++ = b64[ i_ಬಿಟ್ಟುಗಳು>>26        ];
        *dst++ = b64[(i_ಬಿಟ್ಟುಗಳು>>20) & 0x3F];
        *dst++ = b64[(i_ಬಿಟ್ಟುಗಳು>>14) & 0x3F];
        *dst++ = b64[(i_ಬಿಟ್ಟುಗಳು>>8 ) & 0x3F];
    }
    i_ಬಿಟ್ಟುಗಳು = 0;
    ಆಗ (ಬೈಟುಗಳು_ಉಳಿದ) {
        i_ಬಿಟ್ಟುಗಳು = (i_ಬಿಟ್ಟುಗಳು << 8) + *ಒಳ++;
        ಬೈಟುಗಳು_ಉಳಿದ--;
        i_ಸರಿಸು += 8;
    }
    ಆಗ (i_ಸರಿಸು > 0) {
        *dst++ = b64[(i_ಬಿಟ್ಟುಗಳು << 6 >> i_ಸರಿಸು) & 0x3f];
        i_ಸರಿಸು -= 6;
    }
    ಆಗ ((dst - ret) & 3)
        *dst++ = '=';
    *dst = '\0';

    ಹಿಂತಿರುಗಿ ret;
}

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_BASE64_INTERNAL_H */
