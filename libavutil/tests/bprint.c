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

#अन्तर्भाव "libavutil/avassert.h"
#अन्तर्भाव "libavutil/bprint.c"

स्थिर शून्य bprint_pascal(AVBPrint *b, अचिह्नित आकार)
{
    अचिह्नित i, j;
    अचिह्नित p[42];

    av_assert0(आकार < FF_ARRAY_ELEMS(p));

    p[0] = 1;
    av_bprintf(b, "%8d\n", 1);
    प्रति (i = 1; i <= आकार; i++) {
        p[i] = 1;
        प्रति (j = i - 1; j > 0; j--)
            p[j] = p[j] + p[j - 1];
        प्रति (j = 0; j <= i; j++)
            av_bprintf(b, "%8d", p[j]);
        av_bprintf(b, "\n");
    }
}

पूर्णाङ्क मुख्यम्(शून्य)
{
    AVBPrint b;
    वर्ण buf[256];
    संरचना tm testtime = { .tm_year = 100, .tm_mon = 11, .tm_mday = 20 };

    av_bprint_init(&b, 0, AV_BPRINT_आकार_UNLIMITED);
    bprint_pascal(&b, 5);
    प्रारूप_लिख("Short text in unlimited buffer: %u/%u\n", (अचिह्नित)वाक्यदैर्घ्यम्(b.str), b.len);
    प्रारूप_लिख("%s\n", b.str);
    av_bprint_finalize(&b, रिक्त);

    av_bprint_init(&b, 0, AV_BPRINT_आकार_UNLIMITED);
    bprint_pascal(&b, 25);
    प्रारूप_लिख("Long text in unlimited buffer: %u/%u\n", (अचिह्नित)वाक्यदैर्घ्यम्(b.str), b.len);
    av_bprint_finalize(&b, रिक्त);

    av_bprint_init(&b, 0, 2048);
    bprint_pascal(&b, 25);
    प्रारूप_लिख("Long text in limited buffer: %u/%u\n", (अचिह्नित)वाक्यदैर्घ्यम्(b.str), b.len);
    av_bprint_finalize(&b, रिक्त);

    av_bprint_init(&b, 0, AV_BPRINT_आकार_AUTOMATIC);
    bprint_pascal(&b, 5);
    प्रारूप_लिख("Short text in automatic buffer: %u/%u\n", (अचिह्नित)वाक्यदैर्घ्यम्(b.str), b.len);

    av_bprint_init(&b, 0, AV_BPRINT_आकार_AUTOMATIC);
    bprint_pascal(&b, 25);
    प्रारूप_लिख("Long text in automatic buffer: %u/%u\n", (अचिह्नित)वाक्यदैर्घ्यम्(b.str)/8*8, b.len);
    /* Note that the size of the automatic buffer is arch-dependent. */

    av_bprint_init(&b, 0, AV_BPRINT_आकार_गणनम्_ONLY);
    bprint_pascal(&b, 25);
    प्रारूप_लिख("Long text count only buffer: %u/%u\n", (अचिह्नित)वाक्यदैर्घ्यम्(b.str), b.len);

    av_bprint_init_for_बफर(&b, buf, परिमाण(buf));
    bprint_pascal(&b, 25);
    प्रारूप_लिख("Long text count only buffer: %u/%u\n", (अचिह्नित)वाक्यदैर्घ्यम्(buf), b.len);

    av_bprint_init(&b, 0, AV_BPRINT_आकार_UNLIMITED);
    av_bprint_strftime(&b, "%Y-%m-%d", &testtime);
    प्रारूप_लिख("strftime full: %u/%u \"%s\"\n", (अचिह्नित)वाक्यदैर्घ्यम्(buf), b.len, b.str);
    av_bprint_finalize(&b, रिक्त);

    av_bprint_init(&b, 0, 8);
    av_bprint_strftime(&b, "%Y-%m-%d", &testtime);
    प्रारूप_लिख("strftime truncated: %u/%u \"%s\"\n", (अचिह्नित)वाक्यदैर्घ्यम्(buf), b.len, b.str);

    प्रत्यागम 0;
}
