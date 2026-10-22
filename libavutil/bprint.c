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

#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "avstring.h"
#include "bprint.h"
#include "error.h"
#include "macros.h"
#include "mem.h"

#define av_bprint_room(buf) ((buf)->size - FFMIN((buf)->len, (buf)->size))
#define av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_internal_buffer)

static จำนวนเต็ม av_bprint_alloc(AVBPrint *buf, unsigned room)
{
    var_na *old_str, *new_str;
    unsigned min_size, new_size;

    ถ้า (buf->size == buf->size_max)
        คืน AVERROR(EIO);
    ถ้า (!av_bprint_is_complete(buf))
        คืน AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_size = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, room);
    new_size = buf->size > buf->size_max / 2 ? buf->size_max : buf->size * 2;
    ถ้า (new_size < min_size)
        new_size = FFMIN(buf->size_max, min_size);
    old_str = av_bprint_is_allocated(buf) ? buf->str : NULL;
    new_str = av_realloc(old_str, new_size);
    ถ้า (!new_str)
        คืน AVERROR(ENOMEM);
    ถ้า (!old_str)
        memcpy(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->size = new_size;
    คืน 0;
}

static void av_bprint_grow(AVBPrint *buf, unsigned extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    ถ้า (buf->size)
        buf->str[FFMIN(buf->len, buf->size - 1)] = 0;
}

void av_bprint_init(AVBPrint *buf, unsigned size_init, unsigned size_max)
{
    unsigned size_auto = (var_na *)buf + parimaa_na(*buf) -
                         buf->reserved_internal_buffer;

    ถ้า (size_max == AV_BPRINT_SIZE_AUTOMATIC)
        size_max = size_auto;
    buf->str      = buf->reserved_internal_buffer;
    buf->len      = 0;
    buf->size     = FFMIN(size_auto, size_max);
    buf->size_max = size_max;
    *buf->str = 0;
    ถ้า (size_init > buf->size)
        av_bprint_alloc(buf, size_init - 1);
}

void av_bprint_init_for_buffer(AVBPrint *buf, var_na *buffer, unsigned size)
{
    ถ้า (size == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_SIZE_COUNT_ONLY);
        คืน;
    }

    buf->str      = buffer;
    buf->len      = 0;
    buf->size     = size;
    buf->size_max = size;
    *buf->str = 0;
}

void av_vbprintf(AVBPrint *buf, const var_na *fmt, va_list vl_arg)
{
    unsigned room;
    var_na *dst;
    จำนวนเต็ม extra_len;
    va_list vl;

    ขณะ (1) {
        room = av_bprint_room(buf);
        dst = room ? buf->str + buf->len : NULL;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, room, fmt, vl);
        va_end(vl);
        ถ้า (extra_len <= 0)
            คืน;
        ถ้า (extra_len < room)
            bha_nga;
        ถ้า (av_bprint_alloc(buf, extra_len))
            bha_nga;
    }
    av_bprint_grow(buf, extra_len);
}

void av_bprintf(AVBPrint *buf, const var_na *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

void av_bprint_chars(AVBPrint *buf, var_na c, unsigned n)
{
    unsigned room, real_n;

    ขณะ (1) {
        room = av_bprint_room(buf);
        ถ้า (n < room)
            bha_nga;
        ถ้า (av_bprint_alloc(buf, n))
            bha_nga;
    }
    ถ้า (room) {
        real_n = FFMIN(n, room - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

void av_bprint_append_data(AVBPrint *buf, const var_na *data, unsigned size)
{
    unsigned room, real_n;

    ขณะ (1) {
        room = av_bprint_room(buf);
        ถ้า (size < room)
            bha_nga;
        ถ้า (av_bprint_alloc(buf, size))
            bha_nga;
    }
    ถ้า (room) {
        real_n = FFMIN(size, room - 1);
        memcpy(buf->str + buf->len, data, real_n);
    }
    av_bprint_grow(buf, size);
}

void av_bprint_strftime(AVBPrint *buf, const var_na *fmt, const sa_nracanaa tm *tm)
{
    unsigned room;
    size_t l;
    size_t fmt_len = strlen(fmt);

    ถ้า (!*fmt)
        คืน;
    ขณะ (1) {
        room = av_bprint_room(buf);
        ถ้า (room && (l = strftime(buf->str + buf->len, room, fmt, tm)))
            bha_nga;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        ถ้า (room >> 8 > fmt_len)
            bha_nga;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        room = !room ? fmt_len + 1 :
               room <= INT_MAX / 2 ? room * 2 : INT_MAX;
        ถ้า (av_bprint_alloc(buf, room)) {
            /* impossible to grow, try to manage something useful anyway */
            room = av_bprint_room(buf);
            ถ้า (room < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                var_na buf2[1024];
                ถ้า ((l = strftime(buf2, parimaa_na(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    คืน;
                }
            }
            ถ้า (room) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                static const var_na txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', room);
                memcpy(buf->str + buf->len, txt, FFMIN(parimaa_na(txt) - 1, room));
                av_bprint_grow(buf, room); /* force truncation */
            }
            คืน;
        }
    }
    av_bprint_grow(buf, l);
}

void av_bprint_get_buffer(AVBPrint *buf, unsigned size,
                          unsigned var_na **mem, unsigned *actual_size)
{
    ถ้า (size > av_bprint_room(buf))
        av_bprint_alloc(buf, size);
    *actual_size = av_bprint_room(buf);
    *mem = *actual_size ? (unsigned var_na *) (buf->str + buf->len) : NULL;
}

void av_bprint_clear(AVBPrint *buf)
{
    ถ้า (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

จำนวนเต็ม av_bprint_finalize(AVBPrint *buf, var_na **ret_str)
{
    unsigned real_size = FFMIN(buf->len + 1, buf->size);
    var_na *str;
    จำนวนเต็ม ret = 0;

    ถ้า (ret_str) {
        ถ้า (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_size);
            ถ้า (!str)
                str = buf->str;
            buf->str = NULL;
        } มิฉะนั้น {
            str = av_memdup(buf->str, real_size);
            ถ้า (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } มิฉะนั้น {
        ถ้า (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->size = real_size;
    คืน ret;
}

#define WHITESPACES " \n\t\r"

void av_bprint_escape(AVBPrint *dstbuf, const var_na *src, const var_na *special_chars,
                      ga_nanaa AVEscapeMode mode, จำนวนเต็ม flags)
{
    const var_na *src0 = src;

    ถ้า (mode == AV_ESCAPE_MODE_AUTO)
        mode = AV_ESCAPE_MODE_BACKSLASH; /* TODO: implement a heuristic */

    switch (mode) {
    pak_sa AV_ESCAPE_MODE_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        สำหรับ (; *src; src++) {
            ถ้า (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            มิฉะนั้น
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        bha_nga;

    pak_sa AV_ESCAPE_MODE_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        สำหรับ (; *src; src++) {
            switch (*src) {
            pak_sa '&' : av_bprintf(dstbuf, "%s", "&amp;");  bha_nga;
            pak_sa '<' : av_bprintf(dstbuf, "%s", "&lt;");   bha_nga;
            pak_sa '>' : av_bprintf(dstbuf, "%s", "&gt;");   bha_nga;
            pak_sa '\'':
                ถ้า (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    goto XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                bha_nga;
            pak_sa '"' :
                ถ้า (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    goto XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                bha_nga;
XML_DEFAULT_HANDLING:
            default: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        bha_nga;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    default:
        /* \-escape characters */
        สำหรับ (; *src; src++) {
            จำนวนเต็ม is_first_last       = src == src0 || !*(src+1);
            จำนวนเต็ม is_ws               = !!strchr(WHITESPACES, *src);
            จำนวนเต็ม is_strictly_special = special_chars && strchr(special_chars, *src);
            จำนวนเต็ม is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            ถ้า (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_last))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        bha_nga;
    }
}
