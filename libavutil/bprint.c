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

#અન્તર્ભાવ <limits.h>
#અન્તર્ભાવ <stdarg.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <time.h>
#અન્તર્ભાવ "avstring.h"
#અન્તર્ભાવ "bprint.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "macros.h"
#અન્તર્ભાવ "mem.h"

#define av_bprint_room(buf) ((buf)->size - FFMIN((buf)->len, (buf)->size))
#define av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_internal_buffer)

સ્થિર પૂર્ણાંક av_bprint_alloc(AVBPrint *buf, unsigned room)
{
    અક્ષર *old_str, *new_str;
    unsigned min_size, new_size;

    જો (buf->size == buf->size_max)
        પાછા AVERROR(EIO);
    જો (!av_bprint_is_complete(buf))
        પાછા AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_size = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, room);
    new_size = buf->size > buf->size_max / 2 ? buf->size_max : buf->size * 2;
    જો (new_size < min_size)
        new_size = FFMIN(buf->size_max, min_size);
    old_str = av_bprint_is_allocated(buf) ? buf->str : ખાલી;
    new_str = av_realloc(old_str, new_size);
    જો (!new_str)
        પાછા AVERROR(ENOMEM);
    જો (!old_str)
        memcpy(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->size = new_size;
    પાછા 0;
}

સ્થિર શૂન્ય av_bprint_grow(AVBPrint *buf, unsigned extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    જો (buf->size)
        buf->str[FFMIN(buf->len, buf->size - 1)] = 0;
}

શૂન્ય av_bprint_init(AVBPrint *buf, unsigned size_init, unsigned size_max)
{
    unsigned size_auto = (અક્ષર *)buf + કદ(*buf) -
                         buf->reserved_internal_buffer;

    જો (size_max == AV_BPRINT_SIZE_AUTOMATIC)
        size_max = size_auto;
    buf->str      = buf->reserved_internal_buffer;
    buf->len      = 0;
    buf->size     = FFMIN(size_auto, size_max);
    buf->size_max = size_max;
    *buf->str = 0;
    જો (size_init > buf->size)
        av_bprint_alloc(buf, size_init - 1);
}

શૂન્ય av_bprint_init_for_buffer(AVBPrint *buf, અક્ષર *buffer, unsigned size)
{
    જો (size == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_SIZE_ગણતરી_ONLY);
        પાછા;
    }

    buf->str      = buffer;
    buf->len      = 0;
    buf->size     = size;
    buf->size_max = size;
    *buf->str = 0;
}

શૂન્ય av_vbprintf(AVBPrint *buf, અચલ અક્ષર *fmt, va_list vl_arg)
{
    unsigned room;
    અક્ષર *dst;
    પૂર્ણાંક extra_len;
    va_list vl;

    જ્યારે (1) {
        room = av_bprint_room(buf);
        dst = room ? buf->str + buf->len : ખાલી;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, room, fmt, vl);
        va_end(vl);
        જો (extra_len <= 0)
            પાછા;
        જો (extra_len < room)
            તોડો;
        જો (av_bprint_alloc(buf, extra_len))
            તોડો;
    }
    av_bprint_grow(buf, extra_len);
}

શૂન્ય av_bprintf(AVBPrint *buf, અચલ અક્ષર *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

શૂન્ય av_bprint_chars(AVBPrint *buf, અક્ષર c, unsigned n)
{
    unsigned room, real_n;

    જ્યારે (1) {
        room = av_bprint_room(buf);
        જો (n < room)
            તોડો;
        જો (av_bprint_alloc(buf, n))
            તોડો;
    }
    જો (room) {
        real_n = FFMIN(n, room - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

શૂન્ય av_bprint_append_data(AVBPrint *buf, અચલ અક્ષર *data, unsigned size)
{
    unsigned room, real_n;

    જ્યારે (1) {
        room = av_bprint_room(buf);
        જો (size < room)
            તોડો;
        જો (av_bprint_alloc(buf, size))
            તોડો;
    }
    જો (room) {
        real_n = FFMIN(size, room - 1);
        memcpy(buf->str + buf->len, data, real_n);
    }
    av_bprint_grow(buf, size);
}

શૂન્ય av_bprint_strftime(AVBPrint *buf, અચલ અક્ષર *fmt, અચલ સંરચના tm *tm)
{
    unsigned room;
    size_t l;
    size_t fmt_len = strlen(fmt);

    જો (!*fmt)
        પાછા;
    જ્યારે (1) {
        room = av_bprint_room(buf);
        જો (room && (l = strftime(buf->str + buf->len, room, fmt, tm)))
            તોડો;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        જો (room >> 8 > fmt_len)
            તોડો;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        room = !room ? fmt_len + 1 :
               room <= INT_MAX / 2 ? room * 2 : INT_MAX;
        જો (av_bprint_alloc(buf, room)) {
            /* impossible to grow, try to manage something useful anyway */
            room = av_bprint_room(buf);
            જો (room < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                અક્ષર buf2[1024];
                જો ((l = strftime(buf2, કદ(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    પાછા;
                }
            }
            જો (room) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                સ્થિર અચલ અક્ષર txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', room);
                memcpy(buf->str + buf->len, txt, FFMIN(કદ(txt) - 1, room));
                av_bprint_grow(buf, room); /* force truncation */
            }
            પાછા;
        }
    }
    av_bprint_grow(buf, l);
}

શૂન્ય av_bprint_get_buffer(AVBPrint *buf, unsigned size,
                          unsigned અક્ષર **mem, unsigned *actual_size)
{
    જો (size > av_bprint_room(buf))
        av_bprint_alloc(buf, size);
    *actual_size = av_bprint_room(buf);
    *mem = *actual_size ? (unsigned અક્ષર *) (buf->str + buf->len) : ખાલી;
}

શૂન્ય av_bprint_clear(AVBPrint *buf)
{
    જો (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

પૂર્ણાંક av_bprint_finalize(AVBPrint *buf, અક્ષર **ret_str)
{
    unsigned real_size = FFMIN(buf->len + 1, buf->size);
    અક્ષર *str;
    પૂર્ણાંક ret = 0;

    જો (ret_str) {
        જો (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_size);
            જો (!str)
                str = buf->str;
            buf->str = ખાલી;
        } નહીંતર {
            str = av_memdup(buf->str, real_size);
            જો (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } નહીંતર {
        જો (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->size = real_size;
    પાછા ret;
}

#define WHITESPACES " \n\t\r"

શૂન્ય av_bprint_escape(AVBPrint *dstbuf, અચલ અક્ષર *src, અચલ અક્ષર *special_chars,
                      ગણના AVEscapeMode mode, પૂર્ણાંક flags)
{
    અચલ અક્ષર *src0 = src;

    જો (mode == AV_ESCAPE_MODE_AUTO)
        mode = AV_ESCAPE_MODE_BACKSLASH; /* TODO: implement a heuristic */

    પસંદગી (mode) {
    સ્થિતિ AV_ESCAPE_MODE_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        માટે (; *src; src++) {
            જો (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            નહીંતર
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        તોડો;

    સ્થિતિ AV_ESCAPE_MODE_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        માટે (; *src; src++) {
            પસંદગી (*src) {
            સ્થિતિ '&' : av_bprintf(dstbuf, "%s", "&amp;");  તોડો;
            સ્થિતિ '<' : av_bprintf(dstbuf, "%s", "&lt;");   તોડો;
            સ્થિતિ '>' : av_bprintf(dstbuf, "%s", "&gt;");   તોડો;
            સ્થિતિ '\'':
                જો (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    જાઓ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                તોડો;
            સ્થિતિ '"' :
                જો (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    જાઓ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                તોડો;
XML_DEFAULT_HANDLING:
            મૂળભૂત: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        તોડો;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    મૂળભૂત:
        /* \-escape characters */
        માટે (; *src; src++) {
            પૂર્ણાંક is_first_last       = src == src0 || !*(src+1);
            પૂર્ણાંક is_ws               = !!strchr(WHITESPACES, *src);
            પૂર્ણાંક is_strictly_special = special_chars && strchr(special_chars, *src);
            પૂર્ણાંક is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            જો (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_last))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        તોડો;
    }
}
