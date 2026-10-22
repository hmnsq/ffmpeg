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

#समावेश "libavutil/avassert.h"
#समावेश "libavutil/bprint.c"

अटल व्योम bprint_pascal(AVBPrint *b, अचिन्हित आकार)
{
    अचिन्हित i, j;
    अचिन्हित p[42];

    av_assert0(आकार < FF_ARRAY_ELEMS(p));

    p[0] = 1;
    av_bprintf(b, "%8d\n", 1);
    क्रम (i = 1; i <= आकार; i++) {
        p[i] = 1;
        क्रम (j = i - 1; j > 0; j--)
            p[j] = p[j] + p[j - 1];
        क्रम (j = 0; j <= i; j++)
            av_bprintf(b, "%8d", p[j]);
        av_bprintf(b, "\n");
    }
}

पूर्णांक मुख्य(व्योम)
{
    AVBPrint b;
    अक्षर buf[256];
    काष्ठा पंचांग testtime = { .tm_year = 100, .tm_mon = 11, .tm_mday = 20 };

    av_bprint_init(&b, 0, AV_BPRINT_आकार_UNLIMITED);
    bprint_pascal(&b, 5);
    म_लिखो("Short text in unlimited buffer: %u/%u\n", (अचिन्हित)म_माप(b.str), b.len);
    म_लिखो("%s\n", b.str);
    av_bprint_finalize(&b, शून्य);

    av_bprint_init(&b, 0, AV_BPRINT_आकार_UNLIMITED);
    bprint_pascal(&b, 25);
    म_लिखो("Long text in unlimited buffer: %u/%u\n", (अचिन्हित)म_माप(b.str), b.len);
    av_bprint_finalize(&b, शून्य);

    av_bprint_init(&b, 0, 2048);
    bprint_pascal(&b, 25);
    म_लिखो("Long text in limited buffer: %u/%u\n", (अचिन्हित)म_माप(b.str), b.len);
    av_bprint_finalize(&b, शून्य);

    av_bprint_init(&b, 0, AV_BPRINT_आकार_AUTOMATIC);
    bprint_pascal(&b, 5);
    म_लिखो("Short text in automatic buffer: %u/%u\n", (अचिन्हित)म_माप(b.str), b.len);

    av_bprint_init(&b, 0, AV_BPRINT_आकार_AUTOMATIC);
    bprint_pascal(&b, 25);
    म_लिखो("Long text in automatic buffer: %u/%u\n", (अचिन्हित)म_माप(b.str)/8*8, b.len);
    /* Note that the size of the automatic buffer is arch-dependent. */

    av_bprint_init(&b, 0, AV_BPRINT_आकार_गिनती_ONLY);
    bprint_pascal(&b, 25);
    म_लिखो("Long text count only buffer: %u/%u\n", (अचिन्हित)म_माप(b.str), b.len);

    av_bprint_init_for_बफर(&b, buf, माप(buf));
    bprint_pascal(&b, 25);
    म_लिखो("Long text count only buffer: %u/%u\n", (अचिन्हित)म_माप(buf), b.len);

    av_bprint_init(&b, 0, AV_BPRINT_आकार_UNLIMITED);
    av_bprint_strftime(&b, "%Y-%m-%d", &testtime);
    म_लिखो("strftime full: %u/%u \"%s\"\n", (अचिन्हित)म_माप(buf), b.len, b.str);
    av_bprint_finalize(&b, शून्य);

    av_bprint_init(&b, 0, 8);
    av_bprint_strftime(&b, "%Y-%m-%d", &testtime);
    म_लिखो("strftime truncated: %u/%u \"%s\"\n", (अचिन्हित)म_माप(buf), b.len, b.str);

    वापस 0;
}
