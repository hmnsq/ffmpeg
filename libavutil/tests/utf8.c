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

#અન્તર્ભાવ <stdio.h>

#અન્તર્ભાવ "libavutil/avstring.h"
#અન્તર્ભાવ "libavutil/file.h"

સ્થિર અચલ uint8_t vectors[] =
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

સ્થિર શૂન્ય print_sequence(અચલ અક્ષર *p, પૂર્ણાંક l, પૂર્ણાંક indent)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < l; i++)
        printf("%02X", (uint8_t)p[i]);
    printf("%*s", indent-l*2, "");
}

સ્થિર શૂન્ય decode(અચલ uint8_t *p, અચલ uint8_t *endp)
{
    uint32_t code;

    જ્યારે (p < endp) {
        પૂર્ણાંક l, r;
        અચલ uint8_t *p0 = p;
        code = UINT32_MAX;
        r = av_utf8_decode(&code, &p, endp, 0);
        l = (પૂર્ણાંક)(p-p0);
        print_sequence(p0, l, 20);
        જો (code != UINT32_MAX) {
            printf("%-10d 0x%-10X %-5d ", code, code, l);
            જો (r >= 0) {
                જો (*p0 == '\n') printf("\\n\n");
                નહીંતર             printf ("%.*s\n", l, p0);
            } નહીંતર {
                printf("invalid code range\n");
            }
        } નહીંતર {
            printf("invalid sequence\n");
        }
    }
}

પૂર્ણાંક મુખ્ય(પૂર્ણાંક argc, અક્ષર **argv)
{
    જો (argc > 1) {
        uint8_t *file_buf;
        size_t file_buf_size;
        પૂર્ણાંક ret = av_file_map(argv[1], &file_buf, &file_buf_size, 0, ખાલી);
        જો (ret < 0)
            પાછા 1;
        decode(file_buf, file_buf + file_buf_size);
        av_file_unmap(file_buf, file_buf_size);
    } નહીંતર {
        decode(vectors, vectors + કદ(vectors) - 1);
    }

    પાછા 0;
}
