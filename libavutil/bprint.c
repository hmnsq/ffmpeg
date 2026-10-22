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

#ضمن <limits.h>
#ضمن <stdarg.h>
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن <time.h>
#ضمن "avstring.h"
#ضمن "bprint.h"
#ضمن "error.h"
#ضمن "macros.h"
#ضمن "mem.h"

#تعریف_کرو av_bprint_گنجائش(buf) ((buf)->ناپ - FFMIN((buf)->len, (buf)->ناپ))
#تعریف_کرو av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_اندرونی_بفر)

ساكن صحيح av_bprint_alloc(AVBPrint *buf, بنانشانی گنجائش)
{
    حرف *old_str, *new_str;
    بنانشانی min_ناپ, new_ناپ;

    إذا (buf->ناپ == buf->ناپ_max)
        أرجع AVERROR(EIO);
    إذا (!av_bprint_is_complete(buf))
        أرجع AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_ناپ = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, گنجائش);
    new_ناپ = buf->ناپ > buf->ناپ_max / 2 ? buf->ناپ_max : buf->ناپ * 2;
    إذا (new_ناپ < min_ناپ)
        new_ناپ = FFMIN(buf->ناپ_max, min_ناپ);
    old_str = av_bprint_is_allocated(buf) ? buf->str : عدم;
    new_str = av_realloc(old_str, new_ناپ);
    إذا (!new_str)
        أرجع AVERROR(ENOMEM);
    إذا (!old_str)
        حافظہ_نقل(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->ناپ = new_ناپ;
    أرجع 0;
}

ساكن فراغ av_bprint_grow(AVBPrint *buf, بنانشانی extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    إذا (buf->ناپ)
        buf->str[FFMIN(buf->len, buf->ناپ - 1)] = 0;
}

فراغ av_bprint_init(AVBPrint *buf, بنانشانی ناپ_init, بنانشانی ناپ_max)
{
    بنانشانی ناپ_auto = (حرف *)buf + حجم(*buf) -
                         buf->reserved_اندرونی_بفر;

    إذا (ناپ_max == AV_BPRINT_ناپ_AUTOMATIC)
        ناپ_max = ناپ_auto;
    buf->str      = buf->reserved_اندرونی_بفر;
    buf->len      = 0;
    buf->ناپ     = FFMIN(ناپ_auto, ناپ_max);
    buf->ناپ_max = ناپ_max;
    *buf->str = 0;
    إذا (ناپ_init > buf->ناپ)
        av_bprint_alloc(buf, ناپ_init - 1);
}

فراغ av_bprint_init_for_بفر(AVBPrint *buf, حرف *بفر, بنانشانی ناپ)
{
    إذا (ناپ == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_ناپ_گنتی_ONLY);
        أرجع;
    }

    buf->str      = بفر;
    buf->len      = 0;
    buf->ناپ     = ناپ;
    buf->ناپ_max = ناپ;
    *buf->str = 0;
}

فراغ av_vbprintf(AVBPrint *buf, ثابت حرف *fmt, va_list vl_arg)
{
    بنانشانی گنجائش;
    حرف *dst;
    صحيح extra_len;
    va_list vl;

    طالما (1) {
        گنجائش = av_bprint_گنجائش(buf);
        dst = گنجائش ? buf->str + buf->len : عدم;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, گنجائش, fmt, vl);
        va_end(vl);
        إذا (extra_len <= 0)
            أرجع;
        إذا (extra_len < گنجائش)
            اكسر;
        إذا (av_bprint_alloc(buf, extra_len))
            اكسر;
    }
    av_bprint_grow(buf, extra_len);
}

فراغ av_bprintf(AVBPrint *buf, ثابت حرف *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

فراغ av_bprint_chars(AVBPrint *buf, حرف c, بنانشانی n)
{
    بنانشانی گنجائش, real_n;

    طالما (1) {
        گنجائش = av_bprint_گنجائش(buf);
        إذا (n < گنجائش)
            اكسر;
        إذا (av_bprint_alloc(buf, n))
            اكسر;
    }
    إذا (گنجائش) {
        real_n = FFMIN(n, گنجائش - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

فراغ av_bprint_append_انکڑے(AVBPrint *buf, ثابت حرف *انکڑے, بنانشانی ناپ)
{
    بنانشانی گنجائش, real_n;

    طالما (1) {
        گنجائش = av_bprint_گنجائش(buf);
        إذا (ناپ < گنجائش)
            اكسر;
        إذا (av_bprint_alloc(buf, ناپ))
            اكسر;
    }
    إذا (گنجائش) {
        real_n = FFMIN(ناپ, گنجائش - 1);
        حافظہ_نقل(buf->str + buf->len, انکڑے, real_n);
    }
    av_bprint_grow(buf, ناپ);
}

فراغ av_bprint_strftime(AVBPrint *buf, ثابت حرف *fmt, ثابت بنية tm *tm)
{
    بنانشانی گنجائش;
    size_t l;
    size_t fmt_len = لڑی_لمبائی(fmt);

    إذا (!*fmt)
        أرجع;
    طالما (1) {
        گنجائش = av_bprint_گنجائش(buf);
        إذا (گنجائش && (l = strftime(buf->str + buf->len, گنجائش, fmt, tm)))
            اكسر;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        إذا (گنجائش >> 8 > fmt_len)
            اكسر;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        گنجائش = !گنجائش ? fmt_len + 1 :
               گنجائش <= ودھ_توں_ودھ_عدد / 2 ? گنجائش * 2 : ودھ_توں_ودھ_عدد;
        إذا (av_bprint_alloc(buf, گنجائش)) {
            /* impossible to grow, try to manage something useful anyway */
            گنجائش = av_bprint_گنجائش(buf);
            إذا (گنجائش < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                حرف buf2[1024];
                إذا ((l = strftime(buf2, حجم(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    أرجع;
                }
            }
            إذا (گنجائش) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                ساكن ثابت حرف txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', گنجائش);
                حافظہ_نقل(buf->str + buf->len, txt, FFMIN(حجم(txt) - 1, گنجائش));
                av_bprint_grow(buf, گنجائش); /* force truncation */
            }
            أرجع;
        }
    }
    av_bprint_grow(buf, l);
}

فراغ av_bprint_get_بفر(AVBPrint *buf, بنانشانی ناپ,
                          بنانشانی حرف **mem, بنانشانی *actual_ناپ)
{
    إذا (ناپ > av_bprint_گنجائش(buf))
        av_bprint_alloc(buf, ناپ);
    *actual_ناپ = av_bprint_گنجائش(buf);
    *mem = *actual_ناپ ? (بنانشانی حرف *) (buf->str + buf->len) : عدم;
}

فراغ av_bprint_clear(AVBPrint *buf)
{
    إذا (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

صحيح av_bprint_finalize(AVBPrint *buf, حرف **ret_str)
{
    بنانشانی real_ناپ = FFMIN(buf->len + 1, buf->ناپ);
    حرف *str;
    صحيح ret = 0;

    إذا (ret_str) {
        إذا (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_ناپ);
            إذا (!str)
                str = buf->str;
            buf->str = عدم;
        } وإلا {
            str = av_memdup(buf->str, real_ناپ);
            إذا (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } وإلا {
        إذا (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->ناپ = real_ناپ;
    أرجع ret;
}

#تعریف_کرو WHITESPACES " \n\t\r"

فراغ av_bprint_escape(AVBPrint *dstbuf, ثابت حرف *src, ثابت حرف *special_chars,
                      تعداد AVEscape_منوال منوال, صحيح flags)
{
    ثابت حرف *src0 = src;

    إذا (منوال == AV_ESCAPE_منوال_AUTO)
        منوال = AV_ESCAPE_منوال_BACKSLASH; /* TODO: implement a heuristic */

    بدل (منوال) {
    حالة AV_ESCAPE_منوال_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        لكل (; *src; src++) {
            إذا (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            وإلا
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        اكسر;

    حالة AV_ESCAPE_منوال_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        لكل (; *src; src++) {
            بدل (*src) {
            حالة '&' : av_bprintf(dstbuf, "%s", "&amp;");  اكسر;
            حالة '<' : av_bprintf(dstbuf, "%s", "&lt;");   اكسر;
            حالة '>' : av_bprintf(dstbuf, "%s", "&gt;");   اكسر;
            حالة '\'':
                إذا (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    اذهب XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                اكسر;
            حالة '"' :
                إذا (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    اذهب XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                اكسر;
XML_DEFAULT_HANDLING:
            افتراضي: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        اكسر;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    افتراضي:
        /* \-escape characters */
        لكل (; *src; src++) {
            صحيح is_پہلا_آخری       = src == src0 || !*(src+1);
            صحيح is_ws               = !!strchr(WHITESPACES, *src);
            صحيح is_strictly_special = special_chars && strchr(special_chars, *src);
            صحيح is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            إذا (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_پہلا_آخری))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        اكسر;
    }
}
