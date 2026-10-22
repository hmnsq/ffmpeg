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

#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/avstring.h"
#अन्तर्भाव "libavutil/file.h"

स्थिर ध्रुव uint8_t vectors[] =
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

स्थिर शून्य print_sequence(ध्रुव वर्ण *p, पूर्णाङ्क l, पूर्णाङ्क indent)
{
    पूर्णाङ्क i;
    प्रति (i = 0; i < l; i++)
        म_लिखो("%02X", (uint8_t)p[i]);
    म_लिखो("%*s", indent-l*2, "");
}

स्थिर शून्य decode(ध्रुव uint8_t *p, ध्रुव uint8_t *endp)
{
    uint32_t code;

    यावत् (p < endp) {
        पूर्णाङ्क l, r;
        ध्रुव uint8_t *p0 = p;
        code = UINT32_MAX;
        r = av_utf8_decode(&code, &p, endp, 0);
        l = (पूर्णाङ्क)(p-p0);
        print_sequence(p0, l, 20);
        यदि (code != UINT32_MAX) {
            म_लिखो("%-10d 0x%-10X %-5d ", code, code, l);
            यदि (r >= 0) {
                यदि (*p0 == '\n') म_लिखो("\\n\n");
                अन्यथा             म_लिखो ("%.*s\n", l, p0);
            } अन्यथा {
                म_लिखो("invalid code range\n");
            }
        } अन्यथा {
            म_लिखो("invalid sequence\n");
        }
    }
}

पूर्णाङ्क main(पूर्णाङ्क argc, वर्ण **argv)
{
    यदि (argc > 1) {
        uint8_t *file_buf;
        माप_प्रकार file_buf_size;
        पूर्णाङ्क ret = av_file_map(argv[1], &file_buf, &file_buf_size, 0, रिक्त);
        यदि (ret < 0)
            प्रत्यागम 1;
        decode(file_buf, file_buf + file_buf_size);
        av_file_unmap(file_buf, file_buf_size);
    } अन्यथा {
        decode(vectors, vectors + परिमाण(vectors) - 1);
    }

    प्रत्यागम 0;
}
