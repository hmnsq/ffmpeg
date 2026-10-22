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

#define av_bprint_room(buf) ((buf)->size - FFMIN((buf)->len, (buf)->size))
#define av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_internal_buffer)

স্থির পূর্ণাঙ্ক av_bprint_alloc(AVBPrint *buf, unsigned room)
{
    বর্ণ *old_str, *new_str;
    unsigned min_size, new_size;

    যদি (buf->size == buf->size_max)
        প্রত্যাগম AVERROR(EIO);
    যদি (!av_bprint_is_complete(buf))
        প্রত্যাগম AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_size = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, room);
    new_size = buf->size > buf->size_max / 2 ? buf->size_max : buf->size * 2;
    যদি (new_size < min_size)
        new_size = FFMIN(buf->size_max, min_size);
    old_str = av_bprint_is_allocated(buf) ? buf->str : রিক্ত;
    new_str = av_realloc(old_str, new_size);
    যদি (!new_str)
        প্রত্যাগম AVERROR(ENOMEM);
    যদি (!old_str)
        memcpy(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->size = new_size;
    প্রত্যাগম 0;
}

স্থির শূন্য av_bprint_grow(AVBPrint *buf, unsigned extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    যদি (buf->size)
        buf->str[FFMIN(buf->len, buf->size - 1)] = 0;
}

শূন্য av_bprint_init(AVBPrint *buf, unsigned size_init, unsigned size_max)
{
    unsigned size_auto = (বর্ণ *)buf + পরিমাণ(*buf) -
                         buf->reserved_internal_buffer;

    যদি (size_max == AV_BPRINT_SIZE_AUTOMATIC)
        size_max = size_auto;
    buf->str      = buf->reserved_internal_buffer;
    buf->len      = 0;
    buf->size     = FFMIN(size_auto, size_max);
    buf->size_max = size_max;
    *buf->str = 0;
    যদি (size_init > buf->size)
        av_bprint_alloc(buf, size_init - 1);
}

শূন্য av_bprint_init_for_buffer(AVBPrint *buf, বর্ণ *buffer, unsigned size)
{
    যদি (size == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_SIZE_গুনতি_ONLY);
        প্রত্যাগম;
    }

    buf->str      = buffer;
    buf->len      = 0;
    buf->size     = size;
    buf->size_max = size;
    *buf->str = 0;
}

শূন্য av_vbprintf(AVBPrint *buf, ধ্রুব বর্ণ *fmt, va_list vl_arg)
{
    unsigned room;
    বর্ণ *dst;
    পূর্ণাঙ্ক extra_len;
    va_list vl;

    যাবত্ (1) {
        room = av_bprint_room(buf);
        dst = room ? buf->str + buf->len : রিক্ত;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, room, fmt, vl);
        va_end(vl);
        যদি (extra_len <= 0)
            প্রত্যাগম;
        যদি (extra_len < room)
            ভঙ্গ;
        যদি (av_bprint_alloc(buf, extra_len))
            ভঙ্গ;
    }
    av_bprint_grow(buf, extra_len);
}

শূন্য av_bprintf(AVBPrint *buf, ধ্রুব বর্ণ *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

শূন্য av_bprint_chars(AVBPrint *buf, বর্ণ c, unsigned n)
{
    unsigned room, real_n;

    যাবত্ (1) {
        room = av_bprint_room(buf);
        যদি (n < room)
            ভঙ্গ;
        যদি (av_bprint_alloc(buf, n))
            ভঙ্গ;
    }
    যদি (room) {
        real_n = FFMIN(n, room - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

শূন্য av_bprint_append_data(AVBPrint *buf, ধ্রুব বর্ণ *data, unsigned size)
{
    unsigned room, real_n;

    যাবত্ (1) {
        room = av_bprint_room(buf);
        যদি (size < room)
            ভঙ্গ;
        যদি (av_bprint_alloc(buf, size))
            ভঙ্গ;
    }
    যদি (room) {
        real_n = FFMIN(size, room - 1);
        memcpy(buf->str + buf->len, data, real_n);
    }
    av_bprint_grow(buf, size);
}

শূন্য av_bprint_strftime(AVBPrint *buf, ধ্রুব বর্ণ *fmt, ধ্রুব সংরচনা tm *tm)
{
    unsigned room;
    size_t l;
    size_t fmt_len = strlen(fmt);

    যদি (!*fmt)
        প্রত্যাগম;
    যাবত্ (1) {
        room = av_bprint_room(buf);
        যদি (room && (l = strftime(buf->str + buf->len, room, fmt, tm)))
            ভঙ্গ;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        যদি (room >> 8 > fmt_len)
            ভঙ্গ;

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
                বর্ণ buf2[1024];
                যদি ((l = strftime(buf2, পরিমাণ(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    প্রত্যাগম;
                }
            }
            যদি (room) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                স্থির ধ্রুব বর্ণ txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', room);
                memcpy(buf->str + buf->len, txt, FFMIN(পরিমাণ(txt) - 1, room));
                av_bprint_grow(buf, room); /* force truncation */
            }
            প্রত্যাগম;
        }
    }
    av_bprint_grow(buf, l);
}

শূন্য av_bprint_get_buffer(AVBPrint *buf, unsigned size,
                          unsigned বর্ণ **mem, unsigned *actual_size)
{
    যদি (size > av_bprint_room(buf))
        av_bprint_alloc(buf, size);
    *actual_size = av_bprint_room(buf);
    *mem = *actual_size ? (unsigned বর্ণ *) (buf->str + buf->len) : রিক্ত;
}

শূন্য av_bprint_clear(AVBPrint *buf)
{
    যদি (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

পূর্ণাঙ্ক av_bprint_finalize(AVBPrint *buf, বর্ণ **ret_str)
{
    unsigned real_size = FFMIN(buf->len + 1, buf->size);
    বর্ণ *str;
    পূর্ণাঙ্ক ret = 0;

    যদি (ret_str) {
        যদি (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_size);
            যদি (!str)
                str = buf->str;
            buf->str = রিক্ত;
        } অন্যথা {
            str = av_memdup(buf->str, real_size);
            যদি (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } অন্যথা {
        যদি (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->size = real_size;
    প্রত্যাগম ret;
}

#define WHITESPACES " \n\t\r"

শূন্য av_bprint_escape(AVBPrint *dstbuf, ধ্রুব বর্ণ *src, ধ্রুব বর্ণ *special_chars,
                      গণনা AVEscapeMode mode, পূর্ণাঙ্ক flags)
{
    ধ্রুব বর্ণ *src0 = src;

    যদি (mode == AV_ESCAPE_MODE_AUTO)
        mode = AV_ESCAPE_MODE_BACKSLASH; /* TODO: implement a heuristic */

    বিকল্প (mode) {
    পক্ষ AV_ESCAPE_MODE_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        প্রতি (; *src; src++) {
            যদি (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            অন্যথা
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        ভঙ্গ;

    পক্ষ AV_ESCAPE_MODE_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        প্রতি (; *src; src++) {
            বিকল্প (*src) {
            পক্ষ '&' : av_bprintf(dstbuf, "%s", "&amp;");  ভঙ্গ;
            পক্ষ '<' : av_bprintf(dstbuf, "%s", "&lt;");   ভঙ্গ;
            পক্ষ '>' : av_bprintf(dstbuf, "%s", "&gt;");   ভঙ্গ;
            পক্ষ '\'':
                যদি (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    গচ্ছ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                ভঙ্গ;
            পক্ষ '"' :
                যদি (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    গচ্ছ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                ভঙ্গ;
XML_DEFAULT_HANDLING:
            স্বভাব: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        ভঙ্গ;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    স্বভাব:
        /* \-escape characters */
        প্রতি (; *src; src++) {
            পূর্ণাঙ্ক is_first_last       = src == src0 || !*(src+1);
            পূর্ণাঙ্ক is_ws               = !!strchr(WHITESPACES, *src);
            পূর্ণাঙ্ক is_strictly_special = special_chars && strchr(special_chars, *src);
            পূর্ণাঙ্ক is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            যদি (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_last))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        ভঙ্গ;
    }
}
