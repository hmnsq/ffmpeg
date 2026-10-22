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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avstring.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/file.h"

ਸਥਿਰ ਅਚਲ uint8_t vectors[] =
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

ਸਥਿਰ ਖਾਲੀ print_sequence(ਅਚਲ ਅੱਖਰ *p, ਪੂਰਨ l, ਪੂਰਨ indent)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < l; i++)
        ਲਿਖੋ("%02X", (uint8_t)p[i]);
    ਲਿਖੋ("%*s", indent-l*2, "");
}

ਸਥਿਰ ਖਾਲੀ decode(ਅਚਲ uint8_t *p, ਅਚਲ uint8_t *endp)
{
    uint32_t ਕੋਡ;

    ਜਦੋਂ (p < endp) {
        ਪੂਰਨ l, r;
        ਅਚਲ uint8_t *p0 = p;
        ਕੋਡ = UINT32_MAX;
        r = av_utf8_decode(&ਕੋਡ, &p, endp, 0);
        l = (ਪੂਰਨ)(p-p0);
        print_sequence(p0, l, 20);
        ਜੇ (ਕੋਡ != UINT32_MAX) {
            ਲਿਖੋ("%-10d 0x%-10X %-5d ", ਕੋਡ, ਕੋਡ, l);
            ਜੇ (r >= 0) {
                ਜੇ (*p0 == '\n') ਲਿਖੋ("\\n\n");
                ਨਹੀਂਤਾਂ             ਲਿਖੋ ("%.*s\n", l, p0);
            } ਨਹੀਂਤਾਂ {
                ਲਿਖੋ("invalid code range\n");
            }
        } ਨਹੀਂਤਾਂ {
            ਲਿਖੋ("invalid sequence\n");
        }
    }
}

ਪੂਰਨ ਮੁੱਖ(ਪੂਰਨ argc, ਅੱਖਰ **argv)
{
    ਜੇ (argc > 1) {
        uint8_t *file_buf;
        size_t file_buf_ਮਾਪ;
        ਪੂਰਨ ret = av_file_map(argv[1], &file_buf, &file_buf_ਮਾਪ, 0, ਨਿਰਾ);
        ਜੇ (ret < 0)
            ਵਾਪਸ 1;
        decode(file_buf, file_buf + file_buf_ਮਾਪ);
        av_file_unmap(file_buf, file_buf_ਮਾਪ);
    } ਨਹੀਂਤਾਂ {
        decode(vectors, vectors + ਆਕਾਰ(vectors) - 1);
    }

    ਵਾਪਸ 0;
}
