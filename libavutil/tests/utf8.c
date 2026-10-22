/*
 * Copyright (c) 2013 Stefano Sabatini
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

#ضمن <stdio.h>

#ضمن "libavutil/avstring.h"
#ضمن "libavutil/file.h"

ساكن ثابت uint8_t vectors[] =
    "A\n"
    "\xC3\xA9\n"                /* U+00E9 */
    "\xE2\x82\xAC\n"            /* U+20AC */
    "\xF0\x9F\x98\x80\n"        /* U+1F600 */
    "\xF4\x8F\xBF\xBF\n"        /* U+10FFFF */
    "\xF4\x90\x80\x80\n"        /* U+110000 */
    "\xF8\x88\x80\x80\x80\n"    /* 5 byte form of U+200000 */
    "\xC0\x80\n"                /* overlong NUL */
    "\xE0\x80\x80\n"            /* overlong NUL */
    "\xED\xA0\x80\n"            /* U+D800 surrogate */
    "\xEF\xBF\xBF\n"            /* U+FFFF */
    "\x80\n"                    /* stray continuation */
    "\xFE\n"                    /* invalid lead byte */
    "\xC3" "A\n"                /* missing continuation */
    "\xE2\x82";                 /* truncated */

ساكن فراغ print_sequence(ثابت حرف *p, صحيح l, صحيح indent)
{
    صحيح i;
    لكل (i = 0; i < l; i++)
        چاپ_کړه("%02X", (uint8_t)p[i]);
    چاپ_کړه("%*s", indent-l*2, "");
}

ساكن فراغ decode(ثابت uint8_t *p, ثابت uint8_t *endp)
{
    uint32_t کوډ;

    طالما (p < endp) {
        صحيح l, r;
        ثابت uint8_t *p0 = p;
        کوډ = UINT32_MAX;
        r = av_utf8_decode(&کوډ, &p, endp, 0);
        l = (صحيح)(p-p0);
        print_sequence(p0, l, 20);
        إذا (کوډ != UINT32_MAX) {
            چاپ_کړه("%-10d 0x%-10X %-5d ", کوډ, کوډ, l);
            إذا (r >= 0) {
                إذا (*p0 == '\n') چاپ_کړه("\\n\n");
                وإلا             چاپ_کړه ("%.*s\n", l, p0);
            } وإلا {
                چاپ_کړه("invalid code range\n");
            }
        } وإلا {
            چاپ_کړه("invalid sequence\n");
        }
    }
}

صحيح اصلي(صحيح argc, حرف **argv)
{
    إذا (argc > 1) {
        uint8_t *file_buf;
        size_t file_buf_اندازه;
        صحيح ret = av_file_map(argv[1], &file_buf, &file_buf_اندازه, 0, عدم);
        إذا (ret < 0)
            أرجع 1;
        decode(file_buf, file_buf + file_buf_اندازه);
        av_file_unmap(file_buf, file_buf_اندازه);
    } وإلا {
        decode(vectors, vectors + حجم(vectors) - 1);
    }

    أرجع 0;
}
