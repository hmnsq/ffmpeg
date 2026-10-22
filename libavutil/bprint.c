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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdarg.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <time.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "bprint.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_bprint_ਗੁੰਜਾਇਸ਼(buf) ((buf)->ਮਾਪ - FFMIN((buf)->len, (buf)->ਮਾਪ))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_ਅੰਦਰੂਨੀ_ਬਫਰ)

ਸਥਿਰ ਪੂਰਨ av_bprint_alloc(AVBPrint *buf, ਬਿਨਾਨਿਸ਼ਾਨੀ ਗੁੰਜਾਇਸ਼)
{
    ਅੱਖਰ *old_str, *new_str;
    ਬਿਨਾਨਿਸ਼ਾਨੀ min_ਮਾਪ, new_ਮਾਪ;

    ਜੇ (buf->ਮਾਪ == buf->ਮਾਪ_max)
        ਵਾਪਸ AVERROR(EIO);
    ਜੇ (!av_bprint_is_complete(buf))
        ਵਾਪਸ AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_ਮਾਪ = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, ਗੁੰਜਾਇਸ਼);
    new_ਮਾਪ = buf->ਮਾਪ > buf->ਮਾਪ_max / 2 ? buf->ਮਾਪ_max : buf->ਮਾਪ * 2;
    ਜੇ (new_ਮਾਪ < min_ਮਾਪ)
        new_ਮਾਪ = FFMIN(buf->ਮਾਪ_max, min_ਮਾਪ);
    old_str = av_bprint_is_allocated(buf) ? buf->str : ਨਿਰਾ;
    new_str = av_realloc(old_str, new_ਮਾਪ);
    ਜੇ (!new_str)
        ਵਾਪਸ AVERROR(ENOMEM);
    ਜੇ (!old_str)
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->ਮਾਪ = new_ਮਾਪ;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ av_bprint_grow(AVBPrint *buf, ਬਿਨਾਨਿਸ਼ਾਨੀ extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    ਜੇ (buf->ਮਾਪ)
        buf->str[FFMIN(buf->len, buf->ਮਾਪ - 1)] = 0;
}

ਖਾਲੀ av_bprint_init(AVBPrint *buf, ਬਿਨਾਨਿਸ਼ਾਨੀ ਮਾਪ_init, ਬਿਨਾਨਿਸ਼ਾਨੀ ਮਾਪ_max)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਮਾਪ_auto = (ਅੱਖਰ *)buf + ਆਕਾਰ(*buf) -
                         buf->reserved_ਅੰਦਰੂਨੀ_ਬਫਰ;

    ਜੇ (ਮਾਪ_max == AV_BPRINT_ਮਾਪ_AUTOMATIC)
        ਮਾਪ_max = ਮਾਪ_auto;
    buf->str      = buf->reserved_ਅੰਦਰੂਨੀ_ਬਫਰ;
    buf->len      = 0;
    buf->ਮਾਪ     = FFMIN(ਮਾਪ_auto, ਮਾਪ_max);
    buf->ਮਾਪ_max = ਮਾਪ_max;
    *buf->str = 0;
    ਜੇ (ਮਾਪ_init > buf->ਮਾਪ)
        av_bprint_alloc(buf, ਮਾਪ_init - 1);
}

ਖਾਲੀ av_bprint_init_for_ਬਫਰ(AVBPrint *buf, ਅੱਖਰ *ਬਫਰ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਮਾਪ)
{
    ਜੇ (ਮਾਪ == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_ਮਾਪ_ਗਿਣਤੀ_ONLY);
        ਵਾਪਸ;
    }

    buf->str      = ਬਫਰ;
    buf->len      = 0;
    buf->ਮਾਪ     = ਮਾਪ;
    buf->ਮਾਪ_max = ਮਾਪ;
    *buf->str = 0;
}

ਖਾਲੀ av_vbprintf(AVBPrint *buf, ਅਚਲ ਅੱਖਰ *fmt, va_list vl_arg)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਗੁੰਜਾਇਸ਼;
    ਅੱਖਰ *dst;
    ਪੂਰਨ extra_len;
    va_list vl;

    ਜਦੋਂ (1) {
        ਗੁੰਜਾਇਸ਼ = av_bprint_ਗੁੰਜਾਇਸ਼(buf);
        dst = ਗੁੰਜਾਇਸ਼ ? buf->str + buf->len : ਨਿਰਾ;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, ਗੁੰਜਾਇਸ਼, fmt, vl);
        va_end(vl);
        ਜੇ (extra_len <= 0)
            ਵਾਪਸ;
        ਜੇ (extra_len < ਗੁੰਜਾਇਸ਼)
            ਰੋਕੋ;
        ਜੇ (av_bprint_alloc(buf, extra_len))
            ਰੋਕੋ;
    }
    av_bprint_grow(buf, extra_len);
}

ਖਾਲੀ av_bprintf(AVBPrint *buf, ਅਚਲ ਅੱਖਰ *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

ਖਾਲੀ av_bprint_chars(AVBPrint *buf, ਅੱਖਰ c, ਬਿਨਾਨਿਸ਼ਾਨੀ n)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਗੁੰਜਾਇਸ਼, real_n;

    ਜਦੋਂ (1) {
        ਗੁੰਜਾਇਸ਼ = av_bprint_ਗੁੰਜਾਇਸ਼(buf);
        ਜੇ (n < ਗੁੰਜਾਇਸ਼)
            ਰੋਕੋ;
        ਜੇ (av_bprint_alloc(buf, n))
            ਰੋਕੋ;
    }
    ਜੇ (ਗੁੰਜਾਇਸ਼) {
        real_n = FFMIN(n, ਗੁੰਜਾਇਸ਼ - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

ਖਾਲੀ av_bprint_append_ਅੰਕੜੇ(AVBPrint *buf, ਅਚਲ ਅੱਖਰ *ਅੰਕੜੇ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਮਾਪ)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਗੁੰਜਾਇਸ਼, real_n;

    ਜਦੋਂ (1) {
        ਗੁੰਜਾਇਸ਼ = av_bprint_ਗੁੰਜਾਇਸ਼(buf);
        ਜੇ (ਮਾਪ < ਗੁੰਜਾਇਸ਼)
            ਰੋਕੋ;
        ਜੇ (av_bprint_alloc(buf, ਮਾਪ))
            ਰੋਕੋ;
    }
    ਜੇ (ਗੁੰਜਾਇਸ਼) {
        real_n = FFMIN(ਮਾਪ, ਗੁੰਜਾਇਸ਼ - 1);
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(buf->str + buf->len, ਅੰਕੜੇ, real_n);
    }
    av_bprint_grow(buf, ਮਾਪ);
}

ਖਾਲੀ av_bprint_strftime(AVBPrint *buf, ਅਚਲ ਅੱਖਰ *fmt, ਅਚਲ ਬਣਤਰ tm *tm)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਗੁੰਜਾਇਸ਼;
    size_t l;
    size_t fmt_len = ਲੜੀ_ਲੰਬਾਈ(fmt);

    ਜੇ (!*fmt)
        ਵਾਪਸ;
    ਜਦੋਂ (1) {
        ਗੁੰਜਾਇਸ਼ = av_bprint_ਗੁੰਜਾਇਸ਼(buf);
        ਜੇ (ਗੁੰਜਾਇਸ਼ && (l = strftime(buf->str + buf->len, ਗੁੰਜਾਇਸ਼, fmt, tm)))
            ਰੋਕੋ;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        ਜੇ (ਗੁੰਜਾਇਸ਼ >> 8 > fmt_len)
            ਰੋਕੋ;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        ਗੁੰਜਾਇਸ਼ = !ਗੁੰਜਾਇਸ਼ ? fmt_len + 1 :
               ਗੁੰਜਾਇਸ਼ <= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ / 2 ? ਗੁੰਜਾਇਸ਼ * 2 : ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ;
        ਜੇ (av_bprint_alloc(buf, ਗੁੰਜਾਇਸ਼)) {
            /* impossible to grow, try to manage something useful anyway */
            ਗੁੰਜਾਇਸ਼ = av_bprint_ਗੁੰਜਾਇਸ਼(buf);
            ਜੇ (ਗੁੰਜਾਇਸ਼ < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                ਅੱਖਰ buf2[1024];
                ਜੇ ((l = strftime(buf2, ਆਕਾਰ(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    ਵਾਪਸ;
                }
            }
            ਜੇ (ਗੁੰਜਾਇਸ਼) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                ਸਥਿਰ ਅਚਲ ਅੱਖਰ txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', ਗੁੰਜਾਇਸ਼);
                ਸਮ੍ਰਿਤੀ_ਨਕਲ(buf->str + buf->len, txt, FFMIN(ਆਕਾਰ(txt) - 1, ਗੁੰਜਾਇਸ਼));
                av_bprint_grow(buf, ਗੁੰਜਾਇਸ਼); /* force truncation */
            }
            ਵਾਪਸ;
        }
    }
    av_bprint_grow(buf, l);
}

ਖਾਲੀ av_bprint_get_ਬਫਰ(AVBPrint *buf, ਬਿਨਾਨਿਸ਼ਾਨੀ ਮਾਪ,
                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ **mem, ਬਿਨਾਨਿਸ਼ਾਨੀ *actual_ਮਾਪ)
{
    ਜੇ (ਮਾਪ > av_bprint_ਗੁੰਜਾਇਸ਼(buf))
        av_bprint_alloc(buf, ਮਾਪ);
    *actual_ਮਾਪ = av_bprint_ਗੁੰਜਾਇਸ਼(buf);
    *mem = *actual_ਮਾਪ ? (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) (buf->str + buf->len) : ਨਿਰਾ;
}

ਖਾਲੀ av_bprint_clear(AVBPrint *buf)
{
    ਜੇ (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

ਪੂਰਨ av_bprint_finalize(AVBPrint *buf, ਅੱਖਰ **ret_str)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ real_ਮਾਪ = FFMIN(buf->len + 1, buf->ਮਾਪ);
    ਅੱਖਰ *str;
    ਪੂਰਨ ret = 0;

    ਜੇ (ret_str) {
        ਜੇ (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_ਮਾਪ);
            ਜੇ (!str)
                str = buf->str;
            buf->str = ਨਿਰਾ;
        } ਨਹੀਂਤਾਂ {
            str = av_memdup(buf->str, real_ਮਾਪ);
            ਜੇ (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->ਮਾਪ = real_ਮਾਪ;
    ਵਾਪਸ ret;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WHITESPACES " \n\t\r"

ਖਾਲੀ av_bprint_escape(AVBPrint *dstbuf, ਅਚਲ ਅੱਖਰ *src, ਅਚਲ ਅੱਖਰ *special_chars,
                      ਗਿਣਤੀ AVEscape_ਬਹੁਲਕ ਬਹੁਲਕ, ਪੂਰਨ flags)
{
    ਅਚਲ ਅੱਖਰ *src0 = src;

    ਜੇ (ਬਹੁਲਕ == AV_ESCAPE_ਬਹੁਲਕ_AUTO)
        ਬਹੁਲਕ = AV_ESCAPE_ਬਹੁਲਕ_BACKSLASH; /* TODO: implement a heuristic */

    ਚੋਣ (ਬਹੁਲਕ) {
    ਹਾਲਤ AV_ESCAPE_ਬਹੁਲਕ_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        ਲਈ (; *src; src++) {
            ਜੇ (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            ਨਹੀਂਤਾਂ
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        ਰੋਕੋ;

    ਹਾਲਤ AV_ESCAPE_ਬਹੁਲਕ_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        ਲਈ (; *src; src++) {
            ਚੋਣ (*src) {
            ਹਾਲਤ '&' : av_bprintf(dstbuf, "%s", "&amp;");  ਰੋਕੋ;
            ਹਾਲਤ '<' : av_bprintf(dstbuf, "%s", "&lt;");   ਰੋਕੋ;
            ਹਾਲਤ '>' : av_bprintf(dstbuf, "%s", "&gt;");   ਰੋਕੋ;
            ਹਾਲਤ '\'':
                ਜੇ (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    ਜਾਓ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                ਰੋਕੋ;
            ਹਾਲਤ '"' :
                ਜੇ (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    ਜਾਓ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                ਰੋਕੋ;
XML_DEFAULT_HANDLING:
            ਮੂਲ: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        ਰੋਕੋ;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    ਮੂਲ:
        /* \-escape characters */
        ਲਈ (; *src; src++) {
            ਪੂਰਨ is_ਪਹਿਲਾ_ਆਖਰੀ       = src == src0 || !*(src+1);
            ਪੂਰਨ is_ws               = !!strchr(WHITESPACES, *src);
            ਪੂਰਨ is_strictly_special = special_chars && strchr(special_chars, *src);
            ਪੂਰਨ is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            ਜੇ (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_ਪਹਿਲਾ_ਆਖਰੀ))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        ਰੋਕੋ;
    }
}
