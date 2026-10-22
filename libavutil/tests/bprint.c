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

#شامل "libavutil/avassert.h"
#شامل "libavutil/bprint.c"

ساکن خالی bprint_pascal(AVBPrint *b, غیرعلامتی سائز)
{
    غیرعلامتی i, j;
    غیرعلامتی p[42];

    av_assert0(سائز < FF_ARRAY_ELEMS(p));

    p[0] = 1;
    av_bprintf(b, "%8d\n", 1);
    برائے (i = 1; i <= سائز; i++) {
        p[i] = 1;
        برائے (j = i - 1; j > 0; j--)
            p[j] = p[j] + p[j - 1];
        برائے (j = 0; j <= i; j++)
            av_bprintf(b, "%8d", p[j]);
        av_bprintf(b, "\n");
    }
}

صحیح مین(خالی)
{
    AVBPrint b;
    حرف buf[256];
    ساخت tm testtime = { .tm_year = 100, .tm_mon = 11, .tm_mday = 20 };

    av_bprint_init(&b, 0, AV_BPRINT_سائز_UNLIMITED);
    bprint_pascal(&b, 5);
    لکھو("Short text in unlimited buffer: %u/%u\n", (غیرعلامتی)لڑی_لمبائی(b.str), b.len);
    لکھو("%s\n", b.str);
    av_bprint_finalize(&b, تہی);

    av_bprint_init(&b, 0, AV_BPRINT_سائز_UNLIMITED);
    bprint_pascal(&b, 25);
    لکھو("Long text in unlimited buffer: %u/%u\n", (غیرعلامتی)لڑی_لمبائی(b.str), b.len);
    av_bprint_finalize(&b, تہی);

    av_bprint_init(&b, 0, 2048);
    bprint_pascal(&b, 25);
    لکھو("Long text in limited buffer: %u/%u\n", (غیرعلامتی)لڑی_لمبائی(b.str), b.len);
    av_bprint_finalize(&b, تہی);

    av_bprint_init(&b, 0, AV_BPRINT_سائز_AUTOMATIC);
    bprint_pascal(&b, 5);
    لکھو("Short text in automatic buffer: %u/%u\n", (غیرعلامتی)لڑی_لمبائی(b.str), b.len);

    av_bprint_init(&b, 0, AV_BPRINT_سائز_AUTOMATIC);
    bprint_pascal(&b, 25);
    لکھو("Long text in automatic buffer: %u/%u\n", (غیرعلامتی)لڑی_لمبائی(b.str)/8*8, b.len);
    /* Note that the size of the automatic buffer is arch-dependent. */

    av_bprint_init(&b, 0, AV_BPRINT_سائز_گنتی_ONLY);
    bprint_pascal(&b, 25);
    لکھو("Long text count only buffer: %u/%u\n", (غیرعلامتی)لڑی_لمبائی(b.str), b.len);

    av_bprint_init_for_بفر(&b, buf, حجم(buf));
    bprint_pascal(&b, 25);
    لکھو("Long text count only buffer: %u/%u\n", (غیرعلامتی)لڑی_لمبائی(buf), b.len);

    av_bprint_init(&b, 0, AV_BPRINT_سائز_UNLIMITED);
    av_bprint_strftime(&b, "%Y-%m-%d", &testtime);
    لکھو("strftime full: %u/%u \"%s\"\n", (غیرعلامتی)لڑی_لمبائی(buf), b.len, b.str);
    av_bprint_finalize(&b, تہی);

    av_bprint_init(&b, 0, 8);
    av_bprint_strftime(&b, "%Y-%m-%d", &testtime);
    لکھو("strftime truncated: %u/%u \"%s\"\n", (غیرعلامتی)لڑی_لمبائی(buf), b.len, b.str);

    واپس 0;
}
