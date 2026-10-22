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

#ଅନ୍ତର୍ଭାଵ <stdio.h>

#ଅନ୍ତର୍ଭାଵ "libavutil/avstring.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/file.h"

ସ୍ଥିର ଅଚଳ uint8_t vectors[] =
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

ସ୍ଥିର ଶୂନ୍ୟ print_sequence(ଅଚଳ ଅକ୍ଷର *p, ପୂର୍ଣ୍ଣସଂଖ୍ୟା l, ପୂର୍ଣ୍ଣସଂଖ୍ୟା indent)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < l; i++)
        printf("%02X", (uint8_t)p[i]);
    printf("%*s", indent-l*2, "");
}

ସ୍ଥିର ଶୂନ୍ୟ decode(ଅଚଳ uint8_t *p, ଅଚଳ uint8_t *endp)
{
    uint32_t code;

    ଯେତେବେଳେ (p < endp) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା l, r;
        ଅଚଳ uint8_t *p0 = p;
        code = UINT32_MAX;
        r = av_utf8_decode(&code, &p, endp, 0);
        l = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(p-p0);
        print_sequence(p0, l, 20);
        ଯଦି (code != UINT32_MAX) {
            printf("%-10d 0x%-10X %-5d ", code, code, l);
            ଯଦି (r >= 0) {
                ଯଦି (*p0 == '\n') printf("\\n\n");
                ଅନ୍ୟଥା             printf ("%.*s\n", l, p0);
            } ଅନ୍ୟଥା {
                printf("invalid code range\n");
            }
        } ଅନ୍ୟଥା {
            printf("invalid sequence\n");
        }
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc, ଅକ୍ଷର **argv)
{
    ଯଦି (argc > 1) {
        uint8_t *file_buf;
        size_t file_buf_size;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = av_file_map(argv[1], &file_buf, &file_buf_size, 0, ଖାଲି);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ 1;
        decode(file_buf, file_buf + file_buf_size);
        av_file_unmap(file_buf, file_buf_size);
    } ଅନ୍ୟଥା {
        decode(vectors, vectors + ଆକାର(vectors) - 1);
    }

    ଫେରନ୍ତୁ 0;
}
