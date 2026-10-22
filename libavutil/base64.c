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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stddef.h>

#అన్తర్భావ "base64.h"
#అన్తర్భావ "base64_internal.h"
#అన్తర్భావ "error.h"

#ఒకవేళ ARCH_AARCH64
#అన్తర్భావ "libavutil/aarch64/cpu.h"
#అన్తర్భావ "libavutil/aarch64/base64.h"
#అయితే_ముగింపు

/* ---------------- private code */
స్థిర స్థిరరాశి uint8_t map2[256] =
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

#నిర్వచించు BASE64_DEC_అడుగు(i) చేయి { \
    బిట్లు = map2[లోపల[i]]; \
    ఒకవేళ (బిట్లు & 0x80) \
        వెళ్ళు బహిర్గతం ## i; \
    v = i ? (v << 6) + బిట్లు : బిట్లు; \
} అయితే(0)

పూర్ణాంకం av_base64_decode(uint8_t *బహిర్గతం, స్థిరరాశి అక్షరం *లోపల_str, పూర్ణాంకం బహిర్గతం_కొలత)
{
    uint8_t *dst = బహిర్గతం;
    uint8_t *చివర;
    // no sign extension
    స్థిరరాశి uint8_t *లోపల = లోపల_str;
    గుర్తులేని బిట్లు = 0xff;
    గుర్తులేని v;

    ఒకవేళ (!బహిర్గతం)
        వెళ్ళు validity_check;

    చివర = బహిర్గతం + బహిర్గతం_కొలత;
    అయితే (చివర - dst > 3) {
        BASE64_DEC_అడుగు(0);
        BASE64_DEC_అడుగు(1);
        BASE64_DEC_అడుగు(2);
        BASE64_DEC_అడుగు(3);
        // Using AV_WB32 directly confuses compiler
        v = av_be2ne32(v << 8);
        AV_WN32(dst, v);
        dst += 3;
        లోపల += 4;
    }
    ఒకవేళ (చివర - dst) {
        BASE64_DEC_అడుగు(0);
        BASE64_DEC_అడుగు(1);
        BASE64_DEC_అడుగు(2);
        BASE64_DEC_అడుగు(3);
        *dst++ = v >> 16;
        ఒకవేళ (చివర - dst)
            *dst++ = v >> 8;
        ఒకవేళ (చివర - dst)
            *dst++ = v;
        లోపల += 4;
    }
validity_check:
    అయితే (1) {
        BASE64_DEC_అడుగు(0);
        లోపల++;
        BASE64_DEC_అడుగు(0);
        లోపల++;
        BASE64_DEC_అడుగు(0);
        లోపల++;
        BASE64_DEC_అడుగు(0);
        లోపల++;
    }

out3:
    ఒకవేళ (చివర - dst)
        *dst++ = v >> 10;
    v <<= 2;
out2:
    ఒకవేళ (చివర - dst)
        *dst++ = v >> 4;
out1:
out0:
    తిరిగి బిట్లు & 1 ? AVERROR_INVALIDDATA : బహిర్గతం ? dst - బహిర్గతం : 0;
}

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

అక్షరం *av_base64_encode(అక్షరం *బహిర్గతం, పూర్ణాంకం బహిర్గతం_కొలత, స్థిరరాశి uint8_t *లోపల, పూర్ణాంకం లోపల_కొలత)
{
    స్థిర స్థిరరాశి అక్షరం b64[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    ఒకవేళ (లోపల_కొలత >= UINT_MAX / 4 ||
        బహిర్గతం_కొలత < AV_BASE64_కొలత(లోపల_కొలత))
        తిరిగి ఖాళీ;
#ఒకవేళ ARCH_AARCH64
    ఒకవేళ (లోపల_కొలత >= 48 && have_neon(av_get_cpu_flags())) {
        తిరిగి ff_base64_encode_neon(బహిర్గతం, లోపల, లోపల_కొలత, b64);
    }
#అయితే_ముగింపు
    తిరిగి ff_base64_encode_c(బహిర్గతం, లోపల, లోపల_కొలత, b64);
}
