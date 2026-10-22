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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <time.h>
#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "bprint.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

#ವ್ಯಾಖ್ಯಾನಿಸು av_bprint_ಸ್ಥಳ(buf) ((buf)->ಗಾತ್ರ_2 - FFMIN((buf)->len, (buf)->ಗಾತ್ರ_2))
#ವ್ಯಾಖ್ಯಾನಿಸು av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_ಆಂತರಿಕ_ಬಫರ್)

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ av_bprint_alloc(AVBPrint *buf, ಚಿಹ್ನೆರಹಿತ ಸ್ಥಳ)
{
    ಅಕ್ಷರ *old_str, *new_str;
    ಚಿಹ್ನೆರಹಿತ min_ಗಾತ್ರ, new_ಗಾತ್ರ;

    ಆದರೆ (buf->ಗಾತ್ರ_2 == buf->ಗಾತ್ರ_max)
        ಹಿಂತಿರುಗಿ AVERROR(EIO);
    ಆದರೆ (!av_bprint_is_complete(buf))
        ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_ಗಾತ್ರ = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, ಸ್ಥಳ);
    new_ಗಾತ್ರ = buf->ಗಾತ್ರ_2 > buf->ಗಾತ್ರ_max / 2 ? buf->ಗಾತ್ರ_max : buf->ಗಾತ್ರ_2 * 2;
    ಆದರೆ (new_ಗಾತ್ರ < min_ಗಾತ್ರ)
        new_ಗಾತ್ರ = FFMIN(buf->ಗಾತ್ರ_max, min_ಗಾತ್ರ);
    old_str = av_bprint_is_allocated(buf) ? buf->str : ಖಾಲಿ;
    new_str = av_realloc(old_str, new_ಗಾತ್ರ);
    ಆದರೆ (!new_str)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    ಆದರೆ (!old_str)
        ಸ್ಮರಣೆ_ನಕಲು(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->ಗಾತ್ರ_2 = new_ಗಾತ್ರ;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ av_bprint_grow(AVBPrint *buf, ಚಿಹ್ನೆರಹಿತ extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    ಆದರೆ (buf->ಗಾತ್ರ_2)
        buf->str[FFMIN(buf->len, buf->ಗಾತ್ರ_2 - 1)] = 0;
}

ಶೂನ್ಯ av_bprint_init(AVBPrint *buf, ಚಿಹ್ನೆರಹಿತ ಗಾತ್ರ_init, ಚಿಹ್ನೆರಹಿತ ಗಾತ್ರ_max)
{
    ಚಿಹ್ನೆರಹಿತ ಗಾತ್ರ_auto = (ಅಕ್ಷರ *)buf + ಗಾತ್ರ(*buf) -
                         buf->reserved_ಆಂತರಿಕ_ಬಫರ್;

    ಆದರೆ (ಗಾತ್ರ_max == AV_BPRINT_ಗಾತ್ರ_AUTOMATIC)
        ಗಾತ್ರ_max = ಗಾತ್ರ_auto;
    buf->str      = buf->reserved_ಆಂತರಿಕ_ಬಫರ್;
    buf->len      = 0;
    buf->ಗಾತ್ರ_2     = FFMIN(ಗಾತ್ರ_auto, ಗಾತ್ರ_max);
    buf->ಗಾತ್ರ_max = ಗಾತ್ರ_max;
    *buf->str = 0;
    ಆದರೆ (ಗಾತ್ರ_init > buf->ಗಾತ್ರ_2)
        av_bprint_alloc(buf, ಗಾತ್ರ_init - 1);
}

ಶೂನ್ಯ av_bprint_init_for_ಬಫರ್(AVBPrint *buf, ಅಕ್ಷರ *ಬಫರ್, ಚಿಹ್ನೆರಹಿತ ಗಾತ್ರ_2)
{
    ಆದರೆ (ಗಾತ್ರ_2 == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_ಗಾತ್ರ_ಎಣಿಕೆ_ONLY);
        ಹಿಂತಿರುಗಿ;
    }

    buf->str      = ಬಫರ್;
    buf->len      = 0;
    buf->ಗಾತ್ರ_2     = ಗಾತ್ರ_2;
    buf->ಗಾತ್ರ_max = ಗಾತ್ರ_2;
    *buf->str = 0;
}

ಶೂನ್ಯ av_vbprintf(AVBPrint *buf, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list vl_arg)
{
    ಚಿಹ್ನೆರಹಿತ ಸ್ಥಳ;
    ಅಕ್ಷರ *dst;
    ಪೂರ್ಣಾಂಕ extra_len;
    va_list vl;

    ಆಗ (1) {
        ಸ್ಥಳ = av_bprint_ಸ್ಥಳ(buf);
        dst = ಸ್ಥಳ ? buf->str + buf->len : ಖಾಲಿ;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, ಸ್ಥಳ, fmt, vl);
        va_end(vl);
        ಆದರೆ (extra_len <= 0)
            ಹಿಂತಿರುಗಿ;
        ಆದರೆ (extra_len < ಸ್ಥಳ)
            ನಿಲ್ಲಿಸು;
        ಆದರೆ (av_bprint_alloc(buf, extra_len))
            ನಿಲ್ಲಿಸು;
    }
    av_bprint_grow(buf, extra_len);
}

ಶೂನ್ಯ av_bprintf(AVBPrint *buf, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

ಶೂನ್ಯ av_bprint_chars(AVBPrint *buf, ಅಕ್ಷರ c, ಚಿಹ್ನೆರಹಿತ n)
{
    ಚಿಹ್ನೆರಹಿತ ಸ್ಥಳ, real_n;

    ಆಗ (1) {
        ಸ್ಥಳ = av_bprint_ಸ್ಥಳ(buf);
        ಆದರೆ (n < ಸ್ಥಳ)
            ನಿಲ್ಲಿಸು;
        ಆದರೆ (av_bprint_alloc(buf, n))
            ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (ಸ್ಥಳ) {
        real_n = FFMIN(n, ಸ್ಥಳ - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

ಶೂನ್ಯ av_bprint_append_ದತ್ತಾಂಶ(AVBPrint *buf, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ದತ್ತಾಂಶ, ಚಿಹ್ನೆರಹಿತ ಗಾತ್ರ_2)
{
    ಚಿಹ್ನೆರಹಿತ ಸ್ಥಳ, real_n;

    ಆಗ (1) {
        ಸ್ಥಳ = av_bprint_ಸ್ಥಳ(buf);
        ಆದರೆ (ಗಾತ್ರ_2 < ಸ್ಥಳ)
            ನಿಲ್ಲಿಸು;
        ಆದರೆ (av_bprint_alloc(buf, ಗಾತ್ರ_2))
            ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (ಸ್ಥಳ) {
        real_n = FFMIN(ಗಾತ್ರ_2, ಸ್ಥಳ - 1);
        ಸ್ಮರಣೆ_ನಕಲು(buf->str + buf->len, ದತ್ತಾಂಶ, real_n);
    }
    av_bprint_grow(buf, ಗಾತ್ರ_2);
}

ಶೂನ್ಯ av_bprint_strftime(AVBPrint *buf, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ಸ್ಥಿರಾಂಕ ರಚನೆ tm *tm)
{
    ಚಿಹ್ನೆರಹಿತ ಸ್ಥಳ;
    size_t l;
    size_t fmt_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(fmt);

    ಆದರೆ (!*fmt)
        ಹಿಂತಿರುಗಿ;
    ಆಗ (1) {
        ಸ್ಥಳ = av_bprint_ಸ್ಥಳ(buf);
        ಆದರೆ (ಸ್ಥಳ && (l = strftime(buf->str + buf->len, ಸ್ಥಳ, fmt, tm)))
            ನಿಲ್ಲಿಸು;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        ಆದರೆ (ಸ್ಥಳ >> 8 > fmt_len)
            ನಿಲ್ಲಿಸು;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        ಸ್ಥಳ = !ಸ್ಥಳ ? fmt_len + 1 :
               ಸ್ಥಳ <= ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ / 2 ? ಸ್ಥಳ * 2 : ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;
        ಆದರೆ (av_bprint_alloc(buf, ಸ್ಥಳ)) {
            /* impossible to grow, try to manage something useful anyway */
            ಸ್ಥಳ = av_bprint_ಸ್ಥಳ(buf);
            ಆದರೆ (ಸ್ಥಳ < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                ಅಕ್ಷರ buf2[1024];
                ಆದರೆ ((l = strftime(buf2, ಗಾತ್ರ(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    ಹಿಂತಿರುಗಿ;
                }
            }
            ಆದರೆ (ಸ್ಥಳ) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', ಸ್ಥಳ);
                ಸ್ಮರಣೆ_ನಕಲು(buf->str + buf->len, txt, FFMIN(ಗಾತ್ರ(txt) - 1, ಸ್ಥಳ));
                av_bprint_grow(buf, ಸ್ಥಳ); /* force truncation */
            }
            ಹಿಂತಿರುಗಿ;
        }
    }
    av_bprint_grow(buf, l);
}

ಶೂನ್ಯ av_bprint_get_ಬಫರ್(AVBPrint *buf, ಚಿಹ್ನೆರಹಿತ ಗಾತ್ರ_2,
                          ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ **mem, ಚಿಹ್ನೆರಹಿತ *actual_ಗಾತ್ರ)
{
    ಆದರೆ (ಗಾತ್ರ_2 > av_bprint_ಸ್ಥಳ(buf))
        av_bprint_alloc(buf, ಗಾತ್ರ_2);
    *actual_ಗಾತ್ರ = av_bprint_ಸ್ಥಳ(buf);
    *mem = *actual_ಗಾತ್ರ ? (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) (buf->str + buf->len) : ಖಾಲಿ;
}

ಶೂನ್ಯ av_bprint_clear(AVBPrint *buf)
{
    ಆದರೆ (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

ಪೂರ್ಣಾಂಕ av_bprint_finalize(AVBPrint *buf, ಅಕ್ಷರ **ret_str)
{
    ಚಿಹ್ನೆರಹಿತ real_ಗಾತ್ರ = FFMIN(buf->len + 1, buf->ಗಾತ್ರ_2);
    ಅಕ್ಷರ *str;
    ಪೂರ್ಣಾಂಕ ret = 0;

    ಆದರೆ (ret_str) {
        ಆದರೆ (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_ಗಾತ್ರ);
            ಆದರೆ (!str)
                str = buf->str;
            buf->str = ಖಾಲಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            str = av_memdup(buf->str, real_ಗಾತ್ರ);
            ಆದರೆ (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->ಗಾತ್ರ_2 = real_ಗಾತ್ರ;
    ಹಿಂತಿರುಗಿ ret;
}

#ವ್ಯಾಖ್ಯಾನಿಸು WHITESPACES " \n\t\r"

ಶೂನ್ಯ av_bprint_escape(AVBPrint *dstbuf, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *special_chars,
                      ಎಣಿಕೆ AVEscape_ಬಹುಲಕ ಬಹುಲಕ, ಪೂರ್ಣಾಂಕ flags)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src0 = src;

    ಆದರೆ (ಬಹುಲಕ == AV_ESCAPE_ಬಹುಲಕ_AUTO)
        ಬಹುಲಕ = AV_ESCAPE_ಬಹುಲಕ_BACKSLASH; /* TODO: implement a heuristic */

    ಆಯ್ಕೆ (ಬಹುಲಕ) {
    ಸ್ಥಿತಿ AV_ESCAPE_ಬಹುಲಕ_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        ಗಾಗಿ (; *src; src++) {
            ಆದರೆ (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            ಇಲ್ಲದಿದ್ದರೆ
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ AV_ESCAPE_ಬಹುಲಕ_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        ಗಾಗಿ (; *src; src++) {
            ಆಯ್ಕೆ (*src) {
            ಸ್ಥಿತಿ '&' : av_bprintf(dstbuf, "%s", "&amp;");  ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ '<' : av_bprintf(dstbuf, "%s", "&lt;");   ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ '>' : av_bprintf(dstbuf, "%s", "&gt;");   ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ '\'':
                ಆದರೆ (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    ಹೋಗು XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ '"' :
                ಆದರೆ (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    ಹೋಗು XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                ನಿಲ್ಲಿಸು;
XML_DEFAULT_HANDLING:
            ಪೂರ್ವನಿಯೋಜಿತ: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        ನಿಲ್ಲಿಸು;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    ಪೂರ್ವನಿಯೋಜಿತ:
        /* \-escape characters */
        ಗಾಗಿ (; *src; src++) {
            ಪೂರ್ಣಾಂಕ is_ಮೊದಲ_ಕೊನೆಯ       = src == src0 || !*(src+1);
            ಪೂರ್ಣಾಂಕ is_ws               = !!strchr(WHITESPACES, *src);
            ಪೂರ್ಣಾಂಕ is_strictly_special = special_chars && strchr(special_chars, *src);
            ಪೂರ್ಣಾಂಕ is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            ಆದರೆ (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_ಮೊದಲ_ಕೊನೆಯ))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        ನಿಲ್ಲಿಸು;
    }
}
