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

static puur_naa_nka av_bprint_alloc(AVBPrint *buf, unsigned room)
{
    var_na *old_str, *new_str;
    unsigned min_size, new_size;

    ᯀᯮᯝ (buf->size == buf->size_max)
        ᯀᯮᯞ AVERROR(EIO);
    ᯀᯮᯝ (!av_bprint_is_complete(buf))
        ᯀᯮᯞ AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_size = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, room);
    new_size = buf->size > buf->size_max / 2 ? buf->size_max : buf->size * 2;
    ᯀᯮᯝ (new_size < min_size)
        new_size = FFMIN(buf->size_max, min_size);
    old_str = av_bprint_is_allocated(buf) ? buf->str : NULL;
    new_str = av_realloc(old_str, new_size);
    ᯀᯮᯝ (!new_str)
        ᯀᯮᯞ AVERROR(ENOMEM);
    ᯀᯮᯝ (!old_str)
        memcpy(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->size = new_size;
    ᯀᯮᯞ 0;
}

static void av_bprint_grow(AVBPrint *buf, unsigned extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    ᯀᯮᯝ (buf->size)
        buf->str[FFMIN(buf->len, buf->size - 1)] = 0;
}

void av_bprint_init(AVBPrint *buf, unsigned size_init, unsigned size_max)
{
    unsigned size_auto = (var_na *)buf + parimaa_na(*buf) -
                         buf->reserved_internal_buffer;

    ᯀᯮᯝ (size_max == AV_BPRINT_SIZE_AUTOMATIC)
        size_max = size_auto;
    buf->str      = buf->reserved_internal_buffer;
    buf->len      = 0;
    buf->size     = FFMIN(size_auto, size_max);
    buf->size_max = size_max;
    *buf->str = 0;
    ᯀᯮᯝ (size_init > buf->size)
        av_bprint_alloc(buf, size_init - 1);
}

void av_bprint_init_for_buffer(AVBPrint *buf, var_na *buffer, unsigned size)
{
    ᯀᯮᯝ (size == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_SIZE_COUNT_ONLY);
        ᯀᯮᯞ;
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
    puur_naa_nka extra_len;
    va_list vl;

    ᯀᯬᯝ (1) {
        room = av_bprint_room(buf);
        dst = room ? buf->str + buf->len : NULL;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, room, fmt, vl);
        va_end(vl);
        ᯀᯮᯝ (extra_len <= 0)
            ᯀᯮᯞ;
        ᯀᯮᯝ (extra_len < room)
            bha_nga;
        ᯀᯮᯝ (av_bprint_alloc(buf, extra_len))
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

    ᯀᯬᯝ (1) {
        room = av_bprint_room(buf);
        ᯀᯮᯝ (n < room)
            bha_nga;
        ᯀᯮᯝ (av_bprint_alloc(buf, n))
            bha_nga;
    }
    ᯀᯮᯝ (room) {
        real_n = FFMIN(n, room - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

void av_bprint_append_data(AVBPrint *buf, const var_na *data, unsigned size)
{
    unsigned room, real_n;

    ᯀᯬᯝ (1) {
        room = av_bprint_room(buf);
        ᯀᯮᯝ (size < room)
            bha_nga;
        ᯀᯮᯝ (av_bprint_alloc(buf, size))
            bha_nga;
    }
    ᯀᯮᯝ (room) {
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

    ᯀᯮᯝ (!*fmt)
        ᯀᯮᯞ;
    ᯀᯬᯝ (1) {
        room = av_bprint_room(buf);
        ᯀᯮᯝ (room && (l = strftime(buf->str + buf->len, room, fmt, tm)))
            bha_nga;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        ᯀᯮᯝ (room >> 8 > fmt_len)
            bha_nga;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        room = !room ? fmt_len + 1 :
               room <= INT_MAX / 2 ? room * 2 : INT_MAX;
        ᯀᯮᯝ (av_bprint_alloc(buf, room)) {
            /* impossible to grow, try to manage something useful anyway */
            room = av_bprint_room(buf);
            ᯀᯮᯝ (room < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                var_na buf2[1024];
                ᯀᯮᯝ ((l = strftime(buf2, parimaa_na(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    ᯀᯮᯞ;
                }
            }
            ᯀᯮᯝ (room) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                static const var_na txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', room);
                memcpy(buf->str + buf->len, txt, FFMIN(parimaa_na(txt) - 1, room));
                av_bprint_grow(buf, room); /* force truncation */
            }
            ᯀᯮᯞ;
        }
    }
    av_bprint_grow(buf, l);
}

void av_bprint_get_buffer(AVBPrint *buf, unsigned size,
                          unsigned var_na **mem, unsigned *actual_size)
{
    ᯀᯮᯝ (size > av_bprint_room(buf))
        av_bprint_alloc(buf, size);
    *actual_size = av_bprint_room(buf);
    *mem = *actual_size ? (unsigned var_na *) (buf->str + buf->len) : NULL;
}

void av_bprint_clear(AVBPrint *buf)
{
    ᯀᯮᯝ (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

puur_naa_nka av_bprint_finalize(AVBPrint *buf, var_na **ret_str)
{
    unsigned real_size = FFMIN(buf->len + 1, buf->size);
    var_na *str;
    puur_naa_nka ret = 0;

    ᯀᯮᯝ (ret_str) {
        ᯀᯮᯝ (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_size);
            ᯀᯮᯝ (!str)
                str = buf->str;
            buf->str = NULL;
        } ᯀᯮᯝᯂᯪ {
            str = av_memdup(buf->str, real_size);
            ᯀᯮᯝ (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } ᯀᯮᯝᯂᯪ {
        ᯀᯮᯝ (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->size = real_size;
    ᯀᯮᯞ ret;
}

#define WHITESPACES " \n\t\r"

void av_bprint_escape(AVBPrint *dstbuf, const var_na *src, const var_na *special_chars,
                      ga_nanaa AVEscapeMode mode, puur_naa_nka flags)
{
    const var_na *src0 = src;

    ᯀᯮᯝ (mode == AV_ESCAPE_MODE_AUTO)
        mode = AV_ESCAPE_MODE_BACKSLASH; /* TODO: implement a heuristic */

    switch (mode) {
    pak_sa AV_ESCAPE_MODE_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        for (; *src; src++) {
            ᯀᯮᯝ (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            ᯀᯮᯝᯂᯪ
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        bha_nga;

    pak_sa AV_ESCAPE_MODE_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        for (; *src; src++) {
            switch (*src) {
            pak_sa '&' : av_bprintf(dstbuf, "%s", "&amp;");  bha_nga;
            pak_sa '<' : av_bprintf(dstbuf, "%s", "&lt;");   bha_nga;
            pak_sa '>' : av_bprintf(dstbuf, "%s", "&gt;");   bha_nga;
            pak_sa '\'':
                ᯀᯮᯝ (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    goto XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                bha_nga;
            pak_sa '"' :
                ᯀᯮᯝ (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
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
        for (; *src; src++) {
            puur_naa_nka is_first_last       = src == src0 || !*(src+1);
            puur_naa_nka is_ws               = !!strchr(WHITESPACES, *src);
            puur_naa_nka is_strictly_special = special_chars && strchr(special_chars, *src);
            puur_naa_nka is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            ᯀᯮᯝ (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_last))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        bha_nga;
    }
}
