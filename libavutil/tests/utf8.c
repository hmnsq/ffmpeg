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

#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/avstring.h"
#ಅನ್ತರ್ಭಾವ "libavutil/file.h"

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t vectors[] =
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

ಸ್ಥಿರ ಶೂನ್ಯ print_sequence(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p, ಪೂರ್ಣಾಂಕ l, ಪೂರ್ಣಾಂಕ indent)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < l; i++)
        ಬರೆ("%02X", (uint8_t)p[i]);
    ಬರೆ("%*s", indent-l*2, "");
}

ಸ್ಥಿರ ಶೂನ್ಯ decode(ಸ್ಥಿರಾಂಕ uint8_t *p, ಸ್ಥಿರಾಂಕ uint8_t *endp)
{
    uint32_t ಸಂಕೇತ_2;

    ಆಗ (p < endp) {
        ಪೂರ್ಣಾಂಕ l, r;
        ಸ್ಥಿರಾಂಕ uint8_t *p0 = p;
        ಸಂಕೇತ_2 = UINT32_MAX;
        r = av_utf8_decode(&ಸಂಕೇತ_2, &p, endp, 0);
        l = (ಪೂರ್ಣಾಂಕ)(p-p0);
        print_sequence(p0, l, 20);
        ಆದರೆ (ಸಂಕೇತ_2 != UINT32_MAX) {
            ಬರೆ("%-10d 0x%-10X %-5d ", ಸಂಕೇತ_2, ಸಂಕೇತ_2, l);
            ಆದರೆ (r >= 0) {
                ಆದರೆ (*p0 == '\n') ಬರೆ("\\n\n");
                ಇಲ್ಲದಿದ್ದರೆ             ಬರೆ ("%.*s\n", l, p0);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಬರೆ("invalid code range\n");
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬರೆ("invalid sequence\n");
        }
    }
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ **argv)
{
    ಆದರೆ (argc > 1) {
        uint8_t *file_buf;
        size_t file_buf_ಗಾತ್ರ;
        ಪೂರ್ಣಾಂಕ ret = av_file_map(argv[1], &file_buf, &file_buf_ಗಾತ್ರ, 0, ಖಾಲಿ);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ 1;
        decode(file_buf, file_buf + file_buf_ಗಾತ್ರ);
        av_file_unmap(file_buf, file_buf_ಗಾತ್ರ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        decode(vectors, vectors + ಗಾತ್ರ(vectors) - 1);
    }

    ಹಿಂತಿರುಗಿ 0;
}
