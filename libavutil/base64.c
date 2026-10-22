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

/**
 * @file
 * @brief Base64 encode/decode
 * @author Ryan Martell <rdm4@martellventures.com> (with lots of Michael)
 */

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>

#ಅನ್ತರ್ಭಾವ "base64.h"
#ಅನ್ತರ್ಭಾವ "base64_internal.h"
#ಅನ್ತರ್ಭಾವ "error.h"

#ಆದರೆ ARCH_AARCH64
#ಅನ್ತರ್ಭಾವ "libavutil/aarch64/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/aarch64/base64.h"
#ಆದರೆ_ಅಂತ್ಯ

/* ---------------- private code */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t map2[256] =
{
    0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff,

    0x3e, 0xff, 0xff, 0xff, 0x3f, 0x34, 0x35, 0x36,
    0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0xff,
    0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0x00, 0x01,
    0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
    0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11,
    0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1a, 0x1b,
    0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23,
    0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b,
    0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33,

                      0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

#ವ್ಯಾಖ್ಯಾನಿಸು BASE64_DEC_ಹೆಜ್ಜೆ(i) ಮಾಡು { \
    ಬಿಟ್ಟುಗಳು = map2[ಒಳ[i]]; \
    ಆದರೆ (ಬಿಟ್ಟುಗಳು & 0x80) \
        ಹೋಗು ಹೊರಹೋಗು ## i; \
    v = i ? (v << 6) + ಬಿಟ್ಟುಗಳು : ಬಿಟ್ಟುಗಳು; \
} ಆಗ(0)

ಪೂರ್ಣಾಂಕ av_base64_decode(uint8_t *ಹೊರಹೋಗು, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಒಳ_str, ಪೂರ್ಣಾಂಕ ಹೊರಹೋಗು_ಗಾತ್ರ)
{
    uint8_t *dst = ಹೊರಹೋಗು;
    uint8_t *ಕೊನೆ;
    // no sign extension
    ಸ್ಥಿರಾಂಕ uint8_t *ಒಳ = ಒಳ_str;
    ಚಿಹ್ನೆರಹಿತ ಬಿಟ್ಟುಗಳು = 0xff;
    ಚಿಹ್ನೆರಹಿತ v;

    ಆದರೆ (!ಹೊರಹೋಗು)
        ಹೋಗು validity_check;

    ಕೊನೆ = ಹೊರಹೋಗು + ಹೊರಹೋಗು_ಗಾತ್ರ;
    ಆಗ (ಕೊನೆ - dst > 3) {
        BASE64_DEC_ಹೆಜ್ಜೆ(0);
        BASE64_DEC_ಹೆಜ್ಜೆ(1);
        BASE64_DEC_ಹೆಜ್ಜೆ(2);
        BASE64_DEC_ಹೆಜ್ಜೆ(3);
        // Using AV_WB32 directly confuses compiler
        v = av_be2ne32(v << 8);
        AV_WN32(dst, v);
        dst += 3;
        ಒಳ += 4;
    }
    ಆದರೆ (ಕೊನೆ - dst) {
        BASE64_DEC_ಹೆಜ್ಜೆ(0);
        BASE64_DEC_ಹೆಜ್ಜೆ(1);
        BASE64_DEC_ಹೆಜ್ಜೆ(2);
        BASE64_DEC_ಹೆಜ್ಜೆ(3);
        *dst++ = v >> 16;
        ಆದರೆ (ಕೊನೆ - dst)
            *dst++ = v >> 8;
        ಆದರೆ (ಕೊನೆ - dst)
            *dst++ = v;
        ಒಳ += 4;
    }
validity_check:
    ಆಗ (1) {
        BASE64_DEC_ಹೆಜ್ಜೆ(0);
        ಒಳ++;
        BASE64_DEC_ಹೆಜ್ಜೆ(0);
        ಒಳ++;
        BASE64_DEC_ಹೆಜ್ಜೆ(0);
        ಒಳ++;
        BASE64_DEC_ಹೆಜ್ಜೆ(0);
        ಒಳ++;
    }

out3:
    ಆದರೆ (ಕೊನೆ - dst)
        *dst++ = v >> 10;
    v <<= 2;
out2:
    ಆದರೆ (ಕೊನೆ - dst)
        *dst++ = v >> 4;
out1:
out0:
    ಹಿಂತಿರುಗಿ ಬಿಟ್ಟುಗಳು & 1 ? AVERROR_INVALIDDATA : ಹೊರಹೋಗು ? dst - ಹೊರಹೋಗು : 0;
}

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

ಅಕ್ಷರ *av_base64_encode(ಅಕ್ಷರ *ಹೊರಹೋಗು, ಪೂರ್ಣಾಂಕ ಹೊರಹೋಗು_ಗಾತ್ರ, ಸ್ಥಿರಾಂಕ uint8_t *ಒಳ, ಪೂರ್ಣಾಂಕ ಒಳ_ಗಾತ್ರ)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ b64[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    ಆದರೆ (ಒಳ_ಗಾತ್ರ >= UINT_MAX / 4 ||
        ಹೊರಹೋಗು_ಗಾತ್ರ < AV_BASE64_ಗಾತ್ರ(ಒಳ_ಗಾತ್ರ))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
#ಆದರೆ ARCH_AARCH64
    ಆದರೆ (ಒಳ_ಗಾತ್ರ >= 48 && have_neon(av_get_cpu_flags())) {
        ಹಿಂತಿರುಗಿ ff_base64_encode_neon(ಹೊರಹೋಗು, ಒಳ, ಒಳ_ಗಾತ್ರ, b64);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ ff_base64_encode_c(ಹೊರಹೋಗು, ಒಳ, ಒಳ_ಗಾತ್ರ, b64);
}
