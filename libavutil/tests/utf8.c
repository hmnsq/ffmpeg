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

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/avstring.h"
#అన్తర్భావ "libavutil/file.h"

స్థిర స్థిరరాశి uint8_t vectors[] =
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

స్థిర శూన్య print_sequence(స్థిరరాశి అక్షరం *p, పూర్ణాంకం l, పూర్ణాంకం indent)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < l; i++)
        రాయి("%02X", (uint8_t)p[i]);
    రాయి("%*s", indent-l*2, "");
}

స్థిర శూన్య decode(స్థిరరాశి uint8_t *p, స్థిరరాశి uint8_t *endp)
{
    uint32_t సంకేతం_2;

    అయితే (p < endp) {
        పూర్ణాంకం l, r;
        స్థిరరాశి uint8_t *p0 = p;
        సంకేతం_2 = UINT32_MAX;
        r = av_utf8_decode(&సంకేతం_2, &p, endp, 0);
        l = (పూర్ణాంకం)(p-p0);
        print_sequence(p0, l, 20);
        ఒకవేళ (సంకేతం_2 != UINT32_MAX) {
            రాయి("%-10d 0x%-10X %-5d ", సంకేతం_2, సంకేతం_2, l);
            ఒకవేళ (r >= 0) {
                ఒకవేళ (*p0 == '\n') రాయి("\\n\n");
                లేకపోతే             రాయి ("%.*s\n", l, p0);
            } లేకపోతే {
                రాయి("invalid code range\n");
            }
        } లేకపోతే {
            రాయి("invalid sequence\n");
        }
    }
}

పూర్ణాంకం ప్రధాన(పూర్ణాంకం argc, అక్షరం **argv)
{
    ఒకవేళ (argc > 1) {
        uint8_t *file_buf;
        size_t file_buf_కొలత;
        పూర్ణాంకం ret = av_file_map(argv[1], &file_buf, &file_buf_కొలత, 0, ఖాళీ);
        ఒకవేళ (ret < 0)
            తిరిగి 1;
        decode(file_buf, file_buf + file_buf_కొలత);
        av_file_unmap(file_buf, file_buf_కొలత);
    } లేకపోతే {
        decode(vectors, vectors + పరిమాణం(vectors) - 1);
    }

    తిరిగి 0;
}
