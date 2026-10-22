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

#تعریف_کن av_bprint_جا(buf) ((buf)->اندازه - FFMIN((buf)->len, (buf)->اندازه))
#تعریف_کن av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_داخلی_میانگیر)

ساكن صحيح av_bprint_alloc(AVBPrint *buf, بیعلامت جا)
{
    حرف *old_str, *new_str;
    بیعلامت min_اندازه, new_اندازه;

    إذا (buf->اندازه == buf->اندازه_max)
        أرجع AVERROR(EIO);
    إذا (!av_bprint_is_complete(buf))
        أرجع AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_اندازه = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, جا);
    new_اندازه = buf->اندازه > buf->اندازه_max / 2 ? buf->اندازه_max : buf->اندازه * 2;
    إذا (new_اندازه < min_اندازه)
        new_اندازه = FFMIN(buf->اندازه_max, min_اندازه);
    old_str = av_bprint_is_allocated(buf) ? buf->str : عدم;
    new_str = av_realloc(old_str, new_اندازه);
    إذا (!new_str)
        أرجع AVERROR(ENOMEM);
    إذا (!old_str)
        کپی_حافظه(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->اندازه = new_اندازه;
    أرجع 0;
}

ساكن فراغ av_bprint_grow(AVBPrint *buf, بیعلامت extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    إذا (buf->اندازه)
        buf->str[FFMIN(buf->len, buf->اندازه - 1)] = 0;
}

فراغ av_bprint_init(AVBPrint *buf, بیعلامت اندازه_init, بیعلامت اندازه_max)
{
    بیعلامت اندازه_auto = (حرف *)buf + حجم(*buf) -
                         buf->reserved_داخلی_میانگیر;

    إذا (اندازه_max == AV_BPRINT_اندازه_AUTOMATIC)
        اندازه_max = اندازه_auto;
    buf->str      = buf->reserved_داخلی_میانگیر;
    buf->len      = 0;
    buf->اندازه     = FFMIN(اندازه_auto, اندازه_max);
    buf->اندازه_max = اندازه_max;
    *buf->str = 0;
    إذا (اندازه_init > buf->اندازه)
        av_bprint_alloc(buf, اندازه_init - 1);
}

فراغ av_bprint_init_for_میانگیر(AVBPrint *buf, حرف *میانگیر, بیعلامت اندازه)
{
    إذا (اندازه == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_اندازه_شمار_ONLY);
        أرجع;
    }

    buf->str      = میانگیر;
    buf->len      = 0;
    buf->اندازه     = اندازه;
    buf->اندازه_max = اندازه;
    *buf->str = 0;
}

فراغ av_vbprintf(AVBPrint *buf, ثابت حرف *fmt, va_list vl_arg)
{
    بیعلامت جا;
    حرف *dst;
    صحيح extra_len;
    va_list vl;

    طالما (1) {
        جا = av_bprint_جا(buf);
        dst = جا ? buf->str + buf->len : عدم;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, جا, fmt, vl);
        va_end(vl);
        إذا (extra_len <= 0)
            أرجع;
        إذا (extra_len < جا)
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

فراغ av_bprint_chars(AVBPrint *buf, حرف c, بیعلامت n)
{
    بیعلامت جا, real_n;

    طالما (1) {
        جا = av_bprint_جا(buf);
        إذا (n < جا)
            اكسر;
        إذا (av_bprint_alloc(buf, n))
            اكسر;
    }
    إذا (جا) {
        real_n = FFMIN(n, جا - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

فراغ av_bprint_append_داده(AVBPrint *buf, ثابت حرف *داده, بیعلامت اندازه)
{
    بیعلامت جا, real_n;

    طالما (1) {
        جا = av_bprint_جا(buf);
        إذا (اندازه < جا)
            اكسر;
        إذا (av_bprint_alloc(buf, اندازه))
            اكسر;
    }
    إذا (جا) {
        real_n = FFMIN(اندازه, جا - 1);
        کپی_حافظه(buf->str + buf->len, داده, real_n);
    }
    av_bprint_grow(buf, اندازه);
}

فراغ av_bprint_strftime(AVBPrint *buf, ثابت حرف *fmt, ثابت بنية tm *tm)
{
    بیعلامت جا;
    size_t l;
    size_t fmt_len = طول_رشته(fmt);

    إذا (!*fmt)
        أرجع;
    طالما (1) {
        جا = av_bprint_جا(buf);
        إذا (جا && (l = strftime(buf->str + buf->len, جا, fmt, tm)))
            اكسر;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        إذا (جا >> 8 > fmt_len)
            اكسر;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        جا = !جا ? fmt_len + 1 :
               جا <= بیشترین_صحیح / 2 ? جا * 2 : بیشترین_صحیح;
        إذا (av_bprint_alloc(buf, جا)) {
            /* impossible to grow, try to manage something useful anyway */
            جا = av_bprint_جا(buf);
            إذا (جا < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                حرف buf2[1024];
                إذا ((l = strftime(buf2, حجم(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    أرجع;
                }
            }
            إذا (جا) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                ساكن ثابت حرف txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', جا);
                کپی_حافظه(buf->str + buf->len, txt, FFMIN(حجم(txt) - 1, جا));
                av_bprint_grow(buf, جا); /* force truncation */
            }
            أرجع;
        }
    }
    av_bprint_grow(buf, l);
}

فراغ av_bprint_get_میانگیر(AVBPrint *buf, بیعلامت اندازه,
                          بیعلامت حرف **mem, بیعلامت *actual_اندازه)
{
    إذا (اندازه > av_bprint_جا(buf))
        av_bprint_alloc(buf, اندازه);
    *actual_اندازه = av_bprint_جا(buf);
    *mem = *actual_اندازه ? (بیعلامت حرف *) (buf->str + buf->len) : عدم;
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
    بیعلامت real_اندازه = FFMIN(buf->len + 1, buf->اندازه);
    حرف *str;
    صحيح ret = 0;

    إذا (ret_str) {
        إذا (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_اندازه);
            إذا (!str)
                str = buf->str;
            buf->str = عدم;
        } وإلا {
            str = av_memdup(buf->str, real_اندازه);
            إذا (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } وإلا {
        إذا (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->اندازه = real_اندازه;
    أرجع ret;
}

#تعریف_کن WHITESPACES " \n\t\r"

فراغ av_bprint_escape(AVBPrint *dstbuf, ثابت حرف *src, ثابت حرف *special_chars,
                      تعداد AVEscape_نما نما, صحيح flags)
{
    ثابت حرف *src0 = src;

    إذا (نما == AV_ESCAPE_نما_AUTO)
        نما = AV_ESCAPE_نما_BACKSLASH; /* TODO: implement a heuristic */

    بدل (نما) {
    حالة AV_ESCAPE_نما_QUOTE:
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

    حالة AV_ESCAPE_نما_XML:
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
            صحيح is_اولی_آخرین       = src == src0 || !*(src+1);
            صحيح is_ws               = !!strchr(WHITESPACES, *src);
            صحيح is_strictly_special = special_chars && strchr(special_chars, *src);
            صحيح is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            إذا (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_اولی_آخرین))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        اكسر;
    }
}
