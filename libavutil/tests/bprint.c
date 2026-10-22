/*
 * Copyright (c) 2012 Nicolas George
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

#ಅನ್ತರ್ಭಾವ "libavutil/avassert.h"
#ಅನ್ತರ್ಭಾವ "libavutil/bprint.c"

ಸ್ಥಿರ ಶೂನ್ಯ bprint_pascal(AVBPrint *b, ಚಿಹ್ನೆರಹಿತ ಗಾತ್ರ_2)
{
    ಚಿಹ್ನೆರಹಿತ i, j;
    ಚಿಹ್ನೆರಹಿತ p[42];

    av_assert0(ಗಾತ್ರ_2 < FF_ARRAY_ELEMS(p));

    p[0] = 1;
    av_bprintf(b, "%8d\n", 1);
    ಗಾಗಿ (i = 1; i <= ಗಾತ್ರ_2; i++) {
        p[i] = 1;
        ಗಾಗಿ (j = i - 1; j > 0; j--)
            p[j] = p[j] + p[j - 1];
        ಗಾಗಿ (j = 0; j <= i; j++)
            av_bprintf(b, "%8d", p[j]);
        av_bprintf(b, "\n");
    }
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVBPrint b;
    ಅಕ್ಷರ buf[256];
    ರಚನೆ tm testtime = { .tm_year = 100, .tm_mon = 11, .tm_mday = 20 };

    av_bprint_init(&b, 0, AV_BPRINT_ಗಾತ್ರ_UNLIMITED);
    bprint_pascal(&b, 5);
    ಬರೆ("Short text in unlimited buffer: %u/%u\n", (ಚಿಹ್ನೆರಹಿತ)ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(b.str), b.len);
    ಬರೆ("%s\n", b.str);
    av_bprint_finalize(&b, ಖಾಲಿ);

    av_bprint_init(&b, 0, AV_BPRINT_ಗಾತ್ರ_UNLIMITED);
    bprint_pascal(&b, 25);
    ಬರೆ("Long text in unlimited buffer: %u/%u\n", (ಚಿಹ್ನೆರಹಿತ)ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(b.str), b.len);
    av_bprint_finalize(&b, ಖಾಲಿ);

    av_bprint_init(&b, 0, 2048);
    bprint_pascal(&b, 25);
    ಬರೆ("Long text in limited buffer: %u/%u\n", (ಚಿಹ್ನೆರಹಿತ)ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(b.str), b.len);
    av_bprint_finalize(&b, ಖಾಲಿ);

    av_bprint_init(&b, 0, AV_BPRINT_ಗಾತ್ರ_AUTOMATIC);
    bprint_pascal(&b, 5);
    ಬರೆ("Short text in automatic buffer: %u/%u\n", (ಚಿಹ್ನೆರಹಿತ)ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(b.str), b.len);

    av_bprint_init(&b, 0, AV_BPRINT_ಗಾತ್ರ_AUTOMATIC);
    bprint_pascal(&b, 25);
    ಬರೆ("Long text in automatic buffer: %u/%u\n", (ಚಿಹ್ನೆರಹಿತ)ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(b.str)/8*8, b.len);
    /* Note that the size of the automatic buffer is arch-dependent. */

    av_bprint_init(&b, 0, AV_BPRINT_ಗಾತ್ರ_ಎಣಿಕೆ_ONLY);
    bprint_pascal(&b, 25);
    ಬರೆ("Long text count only buffer: %u/%u\n", (ಚಿಹ್ನೆರಹಿತ)ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(b.str), b.len);

    av_bprint_init_for_ಬಫರ್(&b, buf, ಗಾತ್ರ(buf));
    bprint_pascal(&b, 25);
    ಬರೆ("Long text count only buffer: %u/%u\n", (ಚಿಹ್ನೆರಹಿತ)ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(buf), b.len);

    av_bprint_init(&b, 0, AV_BPRINT_ಗಾತ್ರ_UNLIMITED);
    av_bprint_strftime(&b, "%Y-%m-%d", &testtime);
    ಬರೆ("strftime full: %u/%u \"%s\"\n", (ಚಿಹ್ನೆರಹಿತ)ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(buf), b.len, b.str);
    av_bprint_finalize(&b, ಖಾಲಿ);

    av_bprint_init(&b, 0, 8);
    av_bprint_strftime(&b, "%Y-%m-%d", &testtime);
    ಬರೆ("strftime truncated: %u/%u \"%s\"\n", (ಚಿಹ್ನೆರಹಿತ)ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(buf), b.len, b.str);

    ಹಿಂತಿರುಗಿ 0;
}
