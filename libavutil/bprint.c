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

#define av_bprint_room(buf) ((buf)->size - FFMIN((buf)->len, (buf)->size))
#define av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_internal_buffer)

ساكن صحيح av_bprint_alloc(AVBPrint *buf, unsigned room)
{
    حرف *old_str, *new_str;
    unsigned min_size, new_size;

    ܐܢ (buf->size == buf->size_max)
        ܦܢܐ AVERROR(EIO);
    ܐܢ (!av_bprint_is_complete(buf))
        ܦܢܐ AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_size = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, room);
    new_size = buf->size > buf->size_max / 2 ? buf->size_max : buf->size * 2;
    ܐܢ (new_size < min_size)
        new_size = FFMIN(buf->size_max, min_size);
    old_str = av_bprint_is_allocated(buf) ? buf->str : عدم;
    new_str = av_realloc(old_str, new_size);
    ܐܢ (!new_str)
        ܦܢܐ AVERROR(ENOMEM);
    ܐܢ (!old_str)
        memcpy(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->size = new_size;
    ܦܢܐ 0;
}

ساكن فراغ av_bprint_grow(AVBPrint *buf, unsigned extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    ܐܢ (buf->size)
        buf->str[FFMIN(buf->len, buf->size - 1)] = 0;
}

فراغ av_bprint_init(AVBPrint *buf, unsigned size_init, unsigned size_max)
{
    unsigned size_auto = (حرف *)buf + حجم(*buf) -
                         buf->reserved_internal_buffer;

    ܐܢ (size_max == AV_BPRINT_SIZE_AUTOMATIC)
        size_max = size_auto;
    buf->str      = buf->reserved_internal_buffer;
    buf->len      = 0;
    buf->size     = FFMIN(size_auto, size_max);
    buf->size_max = size_max;
    *buf->str = 0;
    ܐܢ (size_init > buf->size)
        av_bprint_alloc(buf, size_init - 1);
}

فراغ av_bprint_init_for_buffer(AVBPrint *buf, حرف *buffer, unsigned size)
{
    ܐܢ (size == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_SIZE_COUNT_ONLY);
        ܦܢܐ;
    }

    buf->str      = buffer;
    buf->len      = 0;
    buf->size     = size;
    buf->size_max = size;
    *buf->str = 0;
}

فراغ av_vbprintf(AVBPrint *buf, ثابت حرف *fmt, va_list vl_arg)
{
    unsigned room;
    حرف *dst;
    صحيح extra_len;
    va_list vl;

    ܟܡܐ (1) {
        room = av_bprint_room(buf);
        dst = room ? buf->str + buf->len : عدم;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, room, fmt, vl);
        va_end(vl);
        ܐܢ (extra_len <= 0)
            ܦܢܐ;
        ܐܢ (extra_len < room)
            اكسر;
        ܐܢ (av_bprint_alloc(buf, extra_len))
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

فراغ av_bprint_chars(AVBPrint *buf, حرف c, unsigned n)
{
    unsigned room, real_n;

    ܟܡܐ (1) {
        room = av_bprint_room(buf);
        ܐܢ (n < room)
            اكسر;
        ܐܢ (av_bprint_alloc(buf, n))
            اكسر;
    }
    ܐܢ (room) {
        real_n = FFMIN(n, room - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

فراغ av_bprint_append_data(AVBPrint *buf, ثابت حرف *data, unsigned size)
{
    unsigned room, real_n;

    ܟܡܐ (1) {
        room = av_bprint_room(buf);
        ܐܢ (size < room)
            اكسر;
        ܐܢ (av_bprint_alloc(buf, size))
            اكسر;
    }
    ܐܢ (room) {
        real_n = FFMIN(size, room - 1);
        memcpy(buf->str + buf->len, data, real_n);
    }
    av_bprint_grow(buf, size);
}

فراغ av_bprint_strftime(AVBPrint *buf, ثابت حرف *fmt, ثابت بنية tm *tm)
{
    unsigned room;
    size_t l;
    size_t fmt_len = strlen(fmt);

    ܐܢ (!*fmt)
        ܦܢܐ;
    ܟܡܐ (1) {
        room = av_bprint_room(buf);
        ܐܢ (room && (l = strftime(buf->str + buf->len, room, fmt, tm)))
            اكسر;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        ܐܢ (room >> 8 > fmt_len)
            اكسر;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        room = !room ? fmt_len + 1 :
               room <= INT_MAX / 2 ? room * 2 : INT_MAX;
        ܐܢ (av_bprint_alloc(buf, room)) {
            /* impossible to grow, try to manage something useful anyway */
            room = av_bprint_room(buf);
            ܐܢ (room < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                حرف buf2[1024];
                ܐܢ ((l = strftime(buf2, حجم(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    ܦܢܐ;
                }
            }
            ܐܢ (room) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                ساكن ثابت حرف txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', room);
                memcpy(buf->str + buf->len, txt, FFMIN(حجم(txt) - 1, room));
                av_bprint_grow(buf, room); /* force truncation */
            }
            ܦܢܐ;
        }
    }
    av_bprint_grow(buf, l);
}

فراغ av_bprint_get_buffer(AVBPrint *buf, unsigned size,
                          unsigned حرف **mem, unsigned *actual_size)
{
    ܐܢ (size > av_bprint_room(buf))
        av_bprint_alloc(buf, size);
    *actual_size = av_bprint_room(buf);
    *mem = *actual_size ? (unsigned حرف *) (buf->str + buf->len) : عدم;
}

فراغ av_bprint_clear(AVBPrint *buf)
{
    ܐܢ (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

صحيح av_bprint_finalize(AVBPrint *buf, حرف **ret_str)
{
    unsigned real_size = FFMIN(buf->len + 1, buf->size);
    حرف *str;
    صحيح ret = 0;

    ܐܢ (ret_str) {
        ܐܢ (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_size);
            ܐܢ (!str)
                str = buf->str;
            buf->str = عدم;
        } ܐܚܪܢܐ {
            str = av_memdup(buf->str, real_size);
            ܐܢ (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } ܐܚܪܢܐ {
        ܐܢ (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->size = real_size;
    ܦܢܐ ret;
}

#define WHITESPACES " \n\t\r"

فراغ av_bprint_escape(AVBPrint *dstbuf, ثابت حرف *src, ثابت حرف *special_chars,
                      تعداد AVEscapeMode mode, صحيح flags)
{
    ثابت حرف *src0 = src;

    ܐܢ (mode == AV_ESCAPE_MODE_AUTO)
        mode = AV_ESCAPE_MODE_BACKSLASH; /* TODO: implement a heuristic */

    بدل (mode) {
    حالة AV_ESCAPE_MODE_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        لكل (; *src; src++) {
            ܐܢ (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            ܐܚܪܢܐ
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        اكسر;

    حالة AV_ESCAPE_MODE_XML:
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
                ܐܢ (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    اذهب XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                اكسر;
            حالة '"' :
                ܐܢ (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
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
            صحيح is_first_last       = src == src0 || !*(src+1);
            صحيح is_ws               = !!strchr(WHITESPACES, *src);
            صحيح is_strictly_special = special_chars && strchr(special_chars, *src);
            صحيح is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            ܐܢ (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_last))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        اكسر;
    }
}
