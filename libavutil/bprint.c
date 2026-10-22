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

#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <stdarg.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <time.h>
#অন্তর্ভাব "avstring.h"
#অন্তর্ভাব "bprint.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "macros.h"
#অন্তর্ভাব "mem.h"

#define av_bprint_room(buf) ((buf)->আকার_2 - FFMIN((buf)->len, (buf)->আকার_2))
#define av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_internal_বাফার)

স্থির পূর্ণসংখ্যা av_bprint_alloc(AVBPrint *buf, unsigned room)
{
    অক্ষর *old_str, *new_str;
    unsigned min_আকার, new_আকার;

    যদি (buf->আকার_2 == buf->আকার_max)
        ফেরত AVERROR(EIO);
    যদি (!av_bprint_is_complete(buf))
        ফেরত AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_আকার = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, room);
    new_আকার = buf->আকার_2 > buf->আকার_max / 2 ? buf->আকার_max : buf->আকার_2 * 2;
    যদি (new_আকার < min_আকার)
        new_আকার = FFMIN(buf->আকার_max, min_আকার);
    old_str = av_bprint_is_allocated(buf) ? buf->str : ফাঁকা;
    new_str = av_realloc(old_str, new_আকার);
    যদি (!new_str)
        ফেরত AVERROR(ENOMEM);
    যদি (!old_str)
        memcpy(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->আকার_2 = new_আকার;
    ফেরত 0;
}

স্থির শূন্য av_bprint_grow(AVBPrint *buf, unsigned extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    যদি (buf->আকার_2)
        buf->str[FFMIN(buf->len, buf->আকার_2 - 1)] = 0;
}

শূন্য av_bprint_init(AVBPrint *buf, unsigned আকার_init, unsigned আকার_max)
{
    unsigned আকার_auto = (অক্ষর *)buf + আকার(*buf) -
                         buf->reserved_internal_বাফার;

    যদি (আকার_max == AV_BPRINT_আকার_AUTOMATIC)
        আকার_max = আকার_auto;
    buf->str      = buf->reserved_internal_বাফার;
    buf->len      = 0;
    buf->আকার_2     = FFMIN(আকার_auto, আকার_max);
    buf->আকার_max = আকার_max;
    *buf->str = 0;
    যদি (আকার_init > buf->আকার_2)
        av_bprint_alloc(buf, আকার_init - 1);
}

শূন্য av_bprint_init_for_বাফার(AVBPrint *buf, অক্ষর *বাফার, unsigned আকার_2)
{
    যদি (আকার_2 == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_আকার_গুনতি_ONLY);
        ফেরত;
    }

    buf->str      = বাফার;
    buf->len      = 0;
    buf->আকার_2     = আকার_2;
    buf->আকার_max = আকার_2;
    *buf->str = 0;
}

শূন্য av_vbprintf(AVBPrint *buf, ধ্রুবক অক্ষর *fmt, va_list vl_arg)
{
    unsigned room;
    অক্ষর *dst;
    পূর্ণসংখ্যা extra_len;
    va_list vl;

    যখন (1) {
        room = av_bprint_room(buf);
        dst = room ? buf->str + buf->len : ফাঁকা;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, room, fmt, vl);
        va_end(vl);
        যদি (extra_len <= 0)
            ফেরত;
        যদি (extra_len < room)
            বিরতি;
        যদি (av_bprint_alloc(buf, extra_len))
            বিরতি;
    }
    av_bprint_grow(buf, extra_len);
}

শূন্য av_bprintf(AVBPrint *buf, ধ্রুবক অক্ষর *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

শূন্য av_bprint_chars(AVBPrint *buf, অক্ষর c, unsigned n)
{
    unsigned room, real_n;

    যখন (1) {
        room = av_bprint_room(buf);
        যদি (n < room)
            বিরতি;
        যদি (av_bprint_alloc(buf, n))
            বিরতি;
    }
    যদি (room) {
        real_n = FFMIN(n, room - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

শূন্য av_bprint_append_তথ্য(AVBPrint *buf, ধ্রুবক অক্ষর *তথ্য, unsigned আকার_2)
{
    unsigned room, real_n;

    যখন (1) {
        room = av_bprint_room(buf);
        যদি (আকার_2 < room)
            বিরতি;
        যদি (av_bprint_alloc(buf, আকার_2))
            বিরতি;
    }
    যদি (room) {
        real_n = FFMIN(আকার_2, room - 1);
        memcpy(buf->str + buf->len, তথ্য, real_n);
    }
    av_bprint_grow(buf, আকার_2);
}

শূন্য av_bprint_strftime(AVBPrint *buf, ধ্রুবক অক্ষর *fmt, ধ্রুবক কাঠামো tm *tm)
{
    unsigned room;
    size_t l;
    size_t fmt_len = strlen(fmt);

    যদি (!*fmt)
        ফেরত;
    যখন (1) {
        room = av_bprint_room(buf);
        যদি (room && (l = strftime(buf->str + buf->len, room, fmt, tm)))
            বিরতি;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        যদি (room >> 8 > fmt_len)
            বিরতি;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        room = !room ? fmt_len + 1 :
               room <= INT_MAX / 2 ? room * 2 : INT_MAX;
        যদি (av_bprint_alloc(buf, room)) {
            /* impossible to grow, try to manage something useful anyway */
            room = av_bprint_room(buf);
            যদি (room < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                অক্ষর buf2[1024];
                যদি ((l = strftime(buf2, আকার(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    ফেরত;
                }
            }
            যদি (room) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                স্থির ধ্রুবক অক্ষর txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', room);
                memcpy(buf->str + buf->len, txt, FFMIN(আকার(txt) - 1, room));
                av_bprint_grow(buf, room); /* force truncation */
            }
            ফেরত;
        }
    }
    av_bprint_grow(buf, l);
}

শূন্য av_bprint_get_বাফার(AVBPrint *buf, unsigned আকার_2,
                          unsigned অক্ষর **mem, unsigned *actual_আকার)
{
    যদি (আকার_2 > av_bprint_room(buf))
        av_bprint_alloc(buf, আকার_2);
    *actual_আকার = av_bprint_room(buf);
    *mem = *actual_আকার ? (unsigned অক্ষর *) (buf->str + buf->len) : ফাঁকা;
}

শূন্য av_bprint_clear(AVBPrint *buf)
{
    যদি (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

পূর্ণসংখ্যা av_bprint_finalize(AVBPrint *buf, অক্ষর **ret_str)
{
    unsigned real_আকার = FFMIN(buf->len + 1, buf->আকার_2);
    অক্ষর *str;
    পূর্ণসংখ্যা ret = 0;

    যদি (ret_str) {
        যদি (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_আকার);
            যদি (!str)
                str = buf->str;
            buf->str = ফাঁকা;
        } অন্যথা {
            str = av_memdup(buf->str, real_আকার);
            যদি (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } অন্যথা {
        যদি (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->আকার_2 = real_আকার;
    ফেরত ret;
}

#define WHITESPACES " \n\t\r"

শূন্য av_bprint_escape(AVBPrint *dstbuf, ধ্রুবক অক্ষর *src, ধ্রুবক অক্ষর *special_chars,
                      গণনা AVEscapeMode mode, পূর্ণসংখ্যা flags)
{
    ধ্রুবক অক্ষর *src0 = src;

    যদি (mode == AV_ESCAPE_MODE_AUTO)
        mode = AV_ESCAPE_MODE_BACKSLASH; /* TODO: implement a heuristic */

    নির্বাচন (mode) {
    ক্ষেত্র AV_ESCAPE_MODE_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        জন্য (; *src; src++) {
            যদি (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            অন্যথা
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        বিরতি;

    ক্ষেত্র AV_ESCAPE_MODE_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        জন্য (; *src; src++) {
            নির্বাচন (*src) {
            ক্ষেত্র '&' : av_bprintf(dstbuf, "%s", "&amp;");  বিরতি;
            ক্ষেত্র '<' : av_bprintf(dstbuf, "%s", "&lt;");   বিরতি;
            ক্ষেত্র '>' : av_bprintf(dstbuf, "%s", "&gt;");   বিরতি;
            ক্ষেত্র '\'':
                যদি (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    যাও XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                বিরতি;
            ক্ষেত্র '"' :
                যদি (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    যাও XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                বিরতি;
XML_DEFAULT_HANDLING:
            পূর্বনির্ধারিত: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        বিরতি;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    পূর্বনির্ধারিত:
        /* \-escape characters */
        জন্য (; *src; src++) {
            পূর্ণসংখ্যা is_first_last       = src == src0 || !*(src+1);
            পূর্ণসংখ্যা is_ws               = !!strchr(WHITESPACES, *src);
            পূর্ণসংখ্যা is_strictly_special = special_chars && strchr(special_chars, *src);
            পূর্ণসংখ্যা is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            যদি (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_last))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        বিরতি;
    }
}
