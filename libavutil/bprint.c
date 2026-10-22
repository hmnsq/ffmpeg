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

#define av_bprint_room(buf) ((buf)->size - FFMIN((buf)->len, (buf)->size))
#define av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_internal_buffer)

ایستا صحیح av_bprint_alloc(AVBPrint *buf, unsigned room)
{
    نویسه *old_str, *new_str;
    unsigned min_size, new_size;

    اگر (buf->size == buf->size_max)
        بازگشت AVERROR(EIO);
    اگر (!av_bprint_is_complete(buf))
        بازگشت AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_size = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, room);
    new_size = buf->size > buf->size_max / 2 ? buf->size_max : buf->size * 2;
    اگر (new_size < min_size)
        new_size = FFMIN(buf->size_max, min_size);
    old_str = av_bprint_is_allocated(buf) ? buf->str : پوچ;
    new_str = av_realloc(old_str, new_size);
    اگر (!new_str)
        بازگشت AVERROR(ENOMEM);
    اگر (!old_str)
        memcpy(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->size = new_size;
    بازگشت 0;
}

ایستا تهی av_bprint_grow(AVBPrint *buf, unsigned extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    اگر (buf->size)
        buf->str[FFMIN(buf->len, buf->size - 1)] = 0;
}

تهی av_bprint_init(AVBPrint *buf, unsigned size_init, unsigned size_max)
{
    unsigned size_auto = (نویسه *)buf + اندازه(*buf) -
                         buf->reserved_internal_buffer;

    اگر (size_max == AV_BPRINT_SIZE_AUTOMATIC)
        size_max = size_auto;
    buf->str      = buf->reserved_internal_buffer;
    buf->len      = 0;
    buf->size     = FFMIN(size_auto, size_max);
    buf->size_max = size_max;
    *buf->str = 0;
    اگر (size_init > buf->size)
        av_bprint_alloc(buf, size_init - 1);
}

تهی av_bprint_init_for_buffer(AVBPrint *buf, نویسه *buffer, unsigned size)
{
    اگر (size == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_SIZE_شمار_ONLY);
        بازگشت;
    }

    buf->str      = buffer;
    buf->len      = 0;
    buf->size     = size;
    buf->size_max = size;
    *buf->str = 0;
}

تهی av_vbprintf(AVBPrint *buf, ثابت نویسه *fmt, va_list vl_arg)
{
    unsigned room;
    نویسه *dst;
    صحیح extra_len;
    va_list vl;

    وقتی (1) {
        room = av_bprint_room(buf);
        dst = room ? buf->str + buf->len : پوچ;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, room, fmt, vl);
        va_end(vl);
        اگر (extra_len <= 0)
            بازگشت;
        اگر (extra_len < room)
            بشکن;
        اگر (av_bprint_alloc(buf, extra_len))
            بشکن;
    }
    av_bprint_grow(buf, extra_len);
}

تهی av_bprintf(AVBPrint *buf, ثابت نویسه *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

تهی av_bprint_chars(AVBPrint *buf, نویسه c, unsigned n)
{
    unsigned room, real_n;

    وقتی (1) {
        room = av_bprint_room(buf);
        اگر (n < room)
            بشکن;
        اگر (av_bprint_alloc(buf, n))
            بشکن;
    }
    اگر (room) {
        real_n = FFMIN(n, room - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

تهی av_bprint_append_data(AVBPrint *buf, ثابت نویسه *data, unsigned size)
{
    unsigned room, real_n;

    وقتی (1) {
        room = av_bprint_room(buf);
        اگر (size < room)
            بشکن;
        اگر (av_bprint_alloc(buf, size))
            بشکن;
    }
    اگر (room) {
        real_n = FFMIN(size, room - 1);
        memcpy(buf->str + buf->len, data, real_n);
    }
    av_bprint_grow(buf, size);
}

تهی av_bprint_strftime(AVBPrint *buf, ثابت نویسه *fmt, ثابت ساختار tm *tm)
{
    unsigned room;
    size_t l;
    size_t fmt_len = strlen(fmt);

    اگر (!*fmt)
        بازگشت;
    وقتی (1) {
        room = av_bprint_room(buf);
        اگر (room && (l = strftime(buf->str + buf->len, room, fmt, tm)))
            بشکن;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        اگر (room >> 8 > fmt_len)
            بشکن;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        room = !room ? fmt_len + 1 :
               room <= INT_MAX / 2 ? room * 2 : INT_MAX;
        اگر (av_bprint_alloc(buf, room)) {
            /* impossible to grow, try to manage something useful anyway */
            room = av_bprint_room(buf);
            اگر (room < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                نویسه buf2[1024];
                اگر ((l = strftime(buf2, اندازه(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    بازگشت;
                }
            }
            اگر (room) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                ایستا ثابت نویسه txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', room);
                memcpy(buf->str + buf->len, txt, FFMIN(اندازه(txt) - 1, room));
                av_bprint_grow(buf, room); /* force truncation */
            }
            بازگشت;
        }
    }
    av_bprint_grow(buf, l);
}

تهی av_bprint_get_buffer(AVBPrint *buf, unsigned size,
                          unsigned نویسه **mem, unsigned *actual_size)
{
    اگر (size > av_bprint_room(buf))
        av_bprint_alloc(buf, size);
    *actual_size = av_bprint_room(buf);
    *mem = *actual_size ? (unsigned نویسه *) (buf->str + buf->len) : پوچ;
}

تهی av_bprint_clear(AVBPrint *buf)
{
    اگر (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

صحیح av_bprint_finalize(AVBPrint *buf, نویسه **ret_str)
{
    unsigned real_size = FFMIN(buf->len + 1, buf->size);
    نویسه *str;
    صحیح ret = 0;

    اگر (ret_str) {
        اگر (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_size);
            اگر (!str)
                str = buf->str;
            buf->str = پوچ;
        } وگرنه {
            str = av_memdup(buf->str, real_size);
            اگر (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } وگرنه {
        اگر (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->size = real_size;
    بازگشت ret;
}

#define WHITESPACES " \n\t\r"

تهی av_bprint_escape(AVBPrint *dstbuf, ثابت نویسه *src, ثابت نویسه *special_chars,
                      شمارش AVEscapeMode mode, صحیح flags)
{
    ثابت نویسه *src0 = src;

    اگر (mode == AV_ESCAPE_MODE_AUTO)
        mode = AV_ESCAPE_MODE_BACKSLASH; /* TODO: implement a heuristic */

    انتخاب (mode) {
    حالت AV_ESCAPE_MODE_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        برای (; *src; src++) {
            اگر (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            وگرنه
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        بشکن;

    حالت AV_ESCAPE_MODE_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        برای (; *src; src++) {
            انتخاب (*src) {
            حالت '&' : av_bprintf(dstbuf, "%s", "&amp;");  بشکن;
            حالت '<' : av_bprintf(dstbuf, "%s", "&lt;");   بشکن;
            حالت '>' : av_bprintf(dstbuf, "%s", "&gt;");   بشکن;
            حالت '\'':
                اگر (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    برو XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                بشکن;
            حالت '"' :
                اگر (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    برو XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                بشکن;
XML_DEFAULT_HANDLING:
            پیشفرض: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        بشکن;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    پیشفرض:
        /* \-escape characters */
        برای (; *src; src++) {
            صحیح is_first_last       = src == src0 || !*(src+1);
            صحیح is_ws               = !!strchr(WHITESPACES, *src);
            صحیح is_strictly_special = special_chars && strchr(special_chars, *src);
            صحیح is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            اگر (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_last))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        بشکن;
    }
}
