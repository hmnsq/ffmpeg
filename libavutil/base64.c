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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stddef.h>

#अन्तर्भाव "base64.h"
#अन्तर्भाव "base64_internal.h"
#अन्तर्भाव "error.h"

#यदि ARCH_AARCH64
#अन्तर्भाव "libavutil/aarch64/cpu.h"
#अन्तर्भाव "libavutil/aarch64/base64.h"
#यदि_अन्तः

/* ---------------- private code */
स्थिर ध्रुव uint8_t map2[256] =
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

#परिभाषय BASE64_DEC_चरणः(i) कुरु { \
    द्वयङ्काः = map2[अन्तर्[i]]; \
    यदि (द्वयङ्काः & 0x80) \
        गच्छ बहिर्गमनम् ## i; \
    v = i ? (v << 6) + द्वयङ्काः : द्वयङ्काः; \
} यावत्(0)

पूर्णाङ्क av_base64_decode(uint8_t *बहिर्गमनम्, ध्रुव वर्ण *अन्तर्_str, पूर्णाङ्क बहिर्गमनम्_आकार)
{
    uint8_t *dst = बहिर्गमनम्;
    uint8_t *अन्तः_2;
    // no sign extension
    ध्रुव uint8_t *अन्तर् = अन्तर्_str;
    अचिह्नित द्वयङ्काः = 0xff;
    अचिह्नित v;

    यदि (!बहिर्गमनम्)
        गच्छ validity_check;

    अन्तः_2 = बहिर्गमनम् + बहिर्गमनम्_आकार;
    यावत् (अन्तः_2 - dst > 3) {
        BASE64_DEC_चरणः(0);
        BASE64_DEC_चरणः(1);
        BASE64_DEC_चरणः(2);
        BASE64_DEC_चरणः(3);
        // Using AV_WB32 directly confuses compiler
        v = av_be2ne32(v << 8);
        AV_WN32(dst, v);
        dst += 3;
        अन्तर् += 4;
    }
    यदि (अन्तः_2 - dst) {
        BASE64_DEC_चरणः(0);
        BASE64_DEC_चरणः(1);
        BASE64_DEC_चरणः(2);
        BASE64_DEC_चरणः(3);
        *dst++ = v >> 16;
        यदि (अन्तः_2 - dst)
            *dst++ = v >> 8;
        यदि (अन्तः_2 - dst)
            *dst++ = v;
        अन्तर् += 4;
    }
validity_check:
    यावत् (1) {
        BASE64_DEC_चरणः(0);
        अन्तर्++;
        BASE64_DEC_चरणः(0);
        अन्तर्++;
        BASE64_DEC_चरणः(0);
        अन्तर्++;
        BASE64_DEC_चरणः(0);
        अन्तर्++;
    }

out3:
    यदि (अन्तः_2 - dst)
        *dst++ = v >> 10;
    v <<= 2;
out2:
    यदि (अन्तः_2 - dst)
        *dst++ = v >> 4;
out1:
out0:
    प्रत्यागम द्वयङ्काः & 1 ? AVERROR_INVALIDDATA : बहिर्गमनम् ? dst - बहिर्गमनम् : 0;
}

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

वर्ण *av_base64_encode(वर्ण *बहिर्गमनम्, पूर्णाङ्क बहिर्गमनम्_आकार, ध्रुव uint8_t *अन्तर्, पूर्णाङ्क अन्तर्_आकार)
{
    स्थिर ध्रुव वर्ण b64[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    यदि (अन्तर्_आकार >= UINT_MAX / 4 ||
        बहिर्गमनम्_आकार < AV_BASE64_आकार(अन्तर्_आकार))
        प्रत्यागम रिक्त;
#यदि ARCH_AARCH64
    यदि (अन्तर्_आकार >= 48 && have_neon(av_get_cpu_flags())) {
        प्रत्यागम ff_base64_encode_neon(बहिर्गमनम्, अन्तर्, अन्तर्_आकार, b64);
    }
#यदि_अन्तः
    प्रत्यागम ff_base64_encode_c(बहिर्गमनम्, अन्तर्, अन्तर्_आकार, b64);
}
