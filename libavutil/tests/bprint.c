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

#ضمن "libavutil/avassert.h"
#ضمن "libavutil/bprint.c"

ساكن فراغ bprint_pascal(AVBPrint *b, بینښه اندازه)
{
    بینښه i, j;
    بینښه p[42];

    av_assert0(اندازه < FF_ARRAY_ELEMS(p));

    p[0] = 1;
    av_bprintf(b, "%8d\n", 1);
    لكل (i = 1; i <= اندازه; i++) {
        p[i] = 1;
        لكل (j = i - 1; j > 0; j--)
            p[j] = p[j] + p[j - 1];
        لكل (j = 0; j <= i; j++)
            av_bprintf(b, "%8d", p[j]);
        av_bprintf(b, "\n");
    }
}

صحيح اصلي(فراغ)
{
    AVBPrint b;
    حرف buf[256];
    بنية tm testtime = { .tm_year = 100, .tm_mon = 11, .tm_mday = 20 };

    av_bprint_init(&b, 0, AV_BPRINT_اندازه_UNLIMITED);
    bprint_pascal(&b, 5);
    چاپ_کړه("Short text in unlimited buffer: %u/%u\n", (بینښه)مزي_اوږدوالی(b.str), b.len);
    چاپ_کړه("%s\n", b.str);
    av_bprint_finalize(&b, عدم);

    av_bprint_init(&b, 0, AV_BPRINT_اندازه_UNLIMITED);
    bprint_pascal(&b, 25);
    چاپ_کړه("Long text in unlimited buffer: %u/%u\n", (بینښه)مزي_اوږدوالی(b.str), b.len);
    av_bprint_finalize(&b, عدم);

    av_bprint_init(&b, 0, 2048);
    bprint_pascal(&b, 25);
    چاپ_کړه("Long text in limited buffer: %u/%u\n", (بینښه)مزي_اوږدوالی(b.str), b.len);
    av_bprint_finalize(&b, عدم);

    av_bprint_init(&b, 0, AV_BPRINT_اندازه_AUTOMATIC);
    bprint_pascal(&b, 5);
    چاپ_کړه("Short text in automatic buffer: %u/%u\n", (بینښه)مزي_اوږدوالی(b.str), b.len);

    av_bprint_init(&b, 0, AV_BPRINT_اندازه_AUTOMATIC);
    bprint_pascal(&b, 25);
    چاپ_کړه("Long text in automatic buffer: %u/%u\n", (بینښه)مزي_اوږدوالی(b.str)/8*8, b.len);
    /* Note that the size of the automatic buffer is arch-dependent. */

    av_bprint_init(&b, 0, AV_BPRINT_اندازه_شمېر_ONLY);
    bprint_pascal(&b, 25);
    چاپ_کړه("Long text count only buffer: %u/%u\n", (بینښه)مزي_اوږدوالی(b.str), b.len);

    av_bprint_init_for_بفر(&b, buf, حجم(buf));
    bprint_pascal(&b, 25);
    چاپ_کړه("Long text count only buffer: %u/%u\n", (بینښه)مزي_اوږدوالی(buf), b.len);

    av_bprint_init(&b, 0, AV_BPRINT_اندازه_UNLIMITED);
    av_bprint_strftime(&b, "%Y-%m-%d", &testtime);
    چاپ_کړه("strftime full: %u/%u \"%s\"\n", (بینښه)مزي_اوږدوالی(buf), b.len, b.str);
    av_bprint_finalize(&b, عدم);

    av_bprint_init(&b, 0, 8);
    av_bprint_strftime(&b, "%Y-%m-%d", &testtime);
    چاپ_کړه("strftime truncated: %u/%u \"%s\"\n", (بینښه)مزي_اوږدوالی(buf), b.len, b.str);

    أرجع 0;
}
