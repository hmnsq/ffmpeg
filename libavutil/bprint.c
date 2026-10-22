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

#شامل <limits.h>
#شامل <stdarg.h>
#شامل <stdio.h>
#شامل <string.h>
#شامل <time.h>
#شامل "avstring.h"
#شامل "bprint.h"
#شامل "error.h"
#شامل "macros.h"
#شامل "mem.h"

#تعریف_کرو av_bprint_گنجائش(buf) ((buf)->سائز - FFMIN((buf)->len, (buf)->سائز))
#تعریف_کرو av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_اندرونی_بفر)

ساکن صحیح av_bprint_alloc(AVBPrint *buf, غیرعلامتی گنجائش)
{
    حرف *old_str, *new_str;
    غیرعلامتی min_سائز, new_سائز;

    اگر (buf->سائز == buf->سائز_max)
        واپس AVERROR(EIO);
    اگر (!av_bprint_is_complete(buf))
        واپس AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_سائز = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, گنجائش);
    new_سائز = buf->سائز > buf->سائز_max / 2 ? buf->سائز_max : buf->سائز * 2;
    اگر (new_سائز < min_سائز)
        new_سائز = FFMIN(buf->سائز_max, min_سائز);
    old_str = av_bprint_is_allocated(buf) ? buf->str : تہی;
    new_str = av_realloc(old_str, new_سائز);
    اگر (!new_str)
        واپس AVERROR(ENOMEM);
    اگر (!old_str)
        حافظہ_نقل(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->سائز = new_سائز;
    واپس 0;
}

ساکن خالی av_bprint_grow(AVBPrint *buf, غیرعلامتی extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    اگر (buf->سائز)
        buf->str[FFMIN(buf->len, buf->سائز - 1)] = 0;
}

خالی av_bprint_init(AVBPrint *buf, غیرعلامتی سائز_init, غیرعلامتی سائز_max)
{
    غیرعلامتی سائز_auto = (حرف *)buf + حجم(*buf) -
                         buf->reserved_اندرونی_بفر;

    اگر (سائز_max == AV_BPRINT_سائز_AUTOMATIC)
        سائز_max = سائز_auto;
    buf->str      = buf->reserved_اندرونی_بفر;
    buf->len      = 0;
    buf->سائز     = FFMIN(سائز_auto, سائز_max);
    buf->سائز_max = سائز_max;
    *buf->str = 0;
    اگر (سائز_init > buf->سائز)
        av_bprint_alloc(buf, سائز_init - 1);
}

خالی av_bprint_init_for_بفر(AVBPrint *buf, حرف *بفر, غیرعلامتی سائز)
{
    اگر (سائز == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_سائز_گنتی_ONLY);
        واپس;
    }

    buf->str      = بفر;
    buf->len      = 0;
    buf->سائز     = سائز;
    buf->سائز_max = سائز;
    *buf->str = 0;
}

خالی av_vbprintf(AVBPrint *buf, ثابت حرف *fmt, va_list vl_arg)
{
    غیرعلامتی گنجائش;
    حرف *dst;
    صحیح extra_len;
    va_list vl;

    جب (1) {
        گنجائش = av_bprint_گنجائش(buf);
        dst = گنجائش ? buf->str + buf->len : تہی;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, گنجائش, fmt, vl);
        va_end(vl);
        اگر (extra_len <= 0)
            واپس;
        اگر (extra_len < گنجائش)
            توڑو;
        اگر (av_bprint_alloc(buf, extra_len))
            توڑو;
    }
    av_bprint_grow(buf, extra_len);
}

خالی av_bprintf(AVBPrint *buf, ثابت حرف *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

خالی av_bprint_chars(AVBPrint *buf, حرف c, غیرعلامتی n)
{
    غیرعلامتی گنجائش, real_n;

    جب (1) {
        گنجائش = av_bprint_گنجائش(buf);
        اگر (n < گنجائش)
            توڑو;
        اگر (av_bprint_alloc(buf, n))
            توڑو;
    }
    اگر (گنجائش) {
        real_n = FFMIN(n, گنجائش - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

خالی av_bprint_append_ڈیٹا(AVBPrint *buf, ثابت حرف *ڈیٹا, غیرعلامتی سائز)
{
    غیرعلامتی گنجائش, real_n;

    جب (1) {
        گنجائش = av_bprint_گنجائش(buf);
        اگر (سائز < گنجائش)
            توڑو;
        اگر (av_bprint_alloc(buf, سائز))
            توڑو;
    }
    اگر (گنجائش) {
        real_n = FFMIN(سائز, گنجائش - 1);
        حافظہ_نقل(buf->str + buf->len, ڈیٹا, real_n);
    }
    av_bprint_grow(buf, سائز);
}

خالی av_bprint_strftime(AVBPrint *buf, ثابت حرف *fmt, ثابت ساخت tm *tm)
{
    غیرعلامتی گنجائش;
    size_t l;
    size_t fmt_len = لڑی_لمبائی(fmt);

    اگر (!*fmt)
        واپس;
    جب (1) {
        گنجائش = av_bprint_گنجائش(buf);
        اگر (گنجائش && (l = strftime(buf->str + buf->len, گنجائش, fmt, tm)))
            توڑو;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        اگر (گنجائش >> 8 > fmt_len)
            توڑو;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        گنجائش = !گنجائش ? fmt_len + 1 :
               گنجائش <= زیادہ_سے_زیادہ_عدد / 2 ? گنجائش * 2 : زیادہ_سے_زیادہ_عدد;
        اگر (av_bprint_alloc(buf, گنجائش)) {
            /* impossible to grow, try to manage something useful anyway */
            گنجائش = av_bprint_گنجائش(buf);
            اگر (گنجائش < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                حرف buf2[1024];
                اگر ((l = strftime(buf2, حجم(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    واپس;
                }
            }
            اگر (گنجائش) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                ساکن ثابت حرف txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', گنجائش);
                حافظہ_نقل(buf->str + buf->len, txt, FFMIN(حجم(txt) - 1, گنجائش));
                av_bprint_grow(buf, گنجائش); /* force truncation */
            }
            واپس;
        }
    }
    av_bprint_grow(buf, l);
}

خالی av_bprint_get_بفر(AVBPrint *buf, غیرعلامتی سائز,
                          غیرعلامتی حرف **mem, غیرعلامتی *actual_سائز)
{
    اگر (سائز > av_bprint_گنجائش(buf))
        av_bprint_alloc(buf, سائز);
    *actual_سائز = av_bprint_گنجائش(buf);
    *mem = *actual_سائز ? (غیرعلامتی حرف *) (buf->str + buf->len) : تہی;
}

خالی av_bprint_clear(AVBPrint *buf)
{
    اگر (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

صحیح av_bprint_finalize(AVBPrint *buf, حرف **ret_str)
{
    غیرعلامتی real_سائز = FFMIN(buf->len + 1, buf->سائز);
    حرف *str;
    صحیح ret = 0;

    اگر (ret_str) {
        اگر (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_سائز);
            اگر (!str)
                str = buf->str;
            buf->str = تہی;
        } ورنہ {
            str = av_memdup(buf->str, real_سائز);
            اگر (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } ورنہ {
        اگر (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->سائز = real_سائز;
    واپس ret;
}

#تعریف_کرو WHITESPACES " \n\t\r"

خالی av_bprint_escape(AVBPrint *dstbuf, ثابت حرف *src, ثابت حرف *special_chars,
                      شمار AVEscape_منوال منوال, صحیح flags)
{
    ثابت حرف *src0 = src;

    اگر (منوال == AV_ESCAPE_منوال_AUTO)
        منوال = AV_ESCAPE_منوال_BACKSLASH; /* TODO: implement a heuristic */

    انتخاب (منوال) {
    حالت AV_ESCAPE_منوال_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        برائے (; *src; src++) {
            اگر (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            ورنہ
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        توڑو;

    حالت AV_ESCAPE_منوال_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        برائے (; *src; src++) {
            انتخاب (*src) {
            حالت '&' : av_bprintf(dstbuf, "%s", "&amp;");  توڑو;
            حالت '<' : av_bprintf(dstbuf, "%s", "&lt;");   توڑو;
            حالت '>' : av_bprintf(dstbuf, "%s", "&gt;");   توڑو;
            حالت '\'':
                اگر (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    جاؤ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                توڑو;
            حالت '"' :
                اگر (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    جاؤ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                توڑو;
XML_DEFAULT_HANDLING:
            طےشدہ: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        توڑو;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    طےشدہ:
        /* \-escape characters */
        برائے (; *src; src++) {
            صحیح is_پہلا_آخری       = src == src0 || !*(src+1);
            صحیح is_ws               = !!strchr(WHITESPACES, *src);
            صحیح is_strictly_special = special_chars && strchr(special_chars, *src);
            صحیح is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            اگر (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_پہلا_آخری))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        توڑو;
    }
}
