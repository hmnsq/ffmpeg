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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <time.h>
#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "bprint.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

#define av_bprint_room(buf) ((buf)->size - FFMIN((buf)->len, (buf)->size))
#define av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_internal_buffer)

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ av_bprint_alloc(AVBPrint *buf, unsigned room)
{
    ವರ್ಣ *old_str, *new_str;
    unsigned min_size, new_size;

    ಯದಿ (buf->size == buf->size_max)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
    ಯದಿ (!av_bprint_is_complete(buf))
        ಪ್ರತ್ಯಾಗಮ AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_size = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, room);
    new_size = buf->size > buf->size_max / 2 ? buf->size_max : buf->size * 2;
    ಯದಿ (new_size < min_size)
        new_size = FFMIN(buf->size_max, min_size);
    old_str = av_bprint_is_allocated(buf) ? buf->str : ರಿಕ್ತ;
    new_str = av_realloc(old_str, new_size);
    ಯದಿ (!new_str)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    ಯದಿ (!old_str)
        memcpy(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->size = new_size;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ av_bprint_grow(AVBPrint *buf, unsigned extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    ಯದಿ (buf->size)
        buf->str[FFMIN(buf->len, buf->size - 1)] = 0;
}

ಶೂನ್ಯ av_bprint_init(AVBPrint *buf, unsigned size_init, unsigned size_max)
{
    unsigned size_auto = (ವರ್ಣ *)buf + ಪರಿಮಾಣ(*buf) -
                         buf->reserved_internal_buffer;

    ಯದಿ (size_max == AV_BPRINT_SIZE_AUTOMATIC)
        size_max = size_auto;
    buf->str      = buf->reserved_internal_buffer;
    buf->len      = 0;
    buf->size     = FFMIN(size_auto, size_max);
    buf->size_max = size_max;
    *buf->str = 0;
    ಯದಿ (size_init > buf->size)
        av_bprint_alloc(buf, size_init - 1);
}

ಶೂನ್ಯ av_bprint_init_for_buffer(AVBPrint *buf, ವರ್ಣ *buffer, unsigned size)
{
    ಯದಿ (size == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_SIZE_ಎಣಿಕೆ_ONLY);
        ಪ್ರತ್ಯಾಗಮ;
    }

    buf->str      = buffer;
    buf->len      = 0;
    buf->size     = size;
    buf->size_max = size;
    *buf->str = 0;
}

ಶೂನ್ಯ av_vbprintf(AVBPrint *buf, ಧ್ರುವ ವರ್ಣ *fmt, va_list vl_arg)
{
    unsigned room;
    ವರ್ಣ *dst;
    ಪೂರ್ಣಾಙ್ಕ extra_len;
    va_list vl;

    ಯಾವತ್ (1) {
        room = av_bprint_room(buf);
        dst = room ? buf->str + buf->len : ರಿಕ್ತ;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, room, fmt, vl);
        va_end(vl);
        ಯದಿ (extra_len <= 0)
            ಪ್ರತ್ಯಾಗಮ;
        ಯದಿ (extra_len < room)
            ಭಙ್ಗ;
        ಯದಿ (av_bprint_alloc(buf, extra_len))
            ಭಙ್ಗ;
    }
    av_bprint_grow(buf, extra_len);
}

ಶೂನ್ಯ av_bprintf(AVBPrint *buf, ಧ್ರುವ ವರ್ಣ *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

ಶೂನ್ಯ av_bprint_chars(AVBPrint *buf, ವರ್ಣ c, unsigned n)
{
    unsigned room, real_n;

    ಯಾವತ್ (1) {
        room = av_bprint_room(buf);
        ಯದಿ (n < room)
            ಭಙ್ಗ;
        ಯದಿ (av_bprint_alloc(buf, n))
            ಭಙ್ಗ;
    }
    ಯದಿ (room) {
        real_n = FFMIN(n, room - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

ಶೂನ್ಯ av_bprint_append_data(AVBPrint *buf, ಧ್ರುವ ವರ್ಣ *data, unsigned size)
{
    unsigned room, real_n;

    ಯಾವತ್ (1) {
        room = av_bprint_room(buf);
        ಯದಿ (size < room)
            ಭಙ್ಗ;
        ಯದಿ (av_bprint_alloc(buf, size))
            ಭಙ್ಗ;
    }
    ಯದಿ (room) {
        real_n = FFMIN(size, room - 1);
        memcpy(buf->str + buf->len, data, real_n);
    }
    av_bprint_grow(buf, size);
}

ಶೂನ್ಯ av_bprint_strftime(AVBPrint *buf, ಧ್ರುವ ವರ್ಣ *fmt, ಧ್ರುವ ಸಂರಚನಾ tm *tm)
{
    unsigned room;
    size_t l;
    size_t fmt_len = strlen(fmt);

    ಯದಿ (!*fmt)
        ಪ್ರತ್ಯಾಗಮ;
    ಯಾವತ್ (1) {
        room = av_bprint_room(buf);
        ಯದಿ (room && (l = strftime(buf->str + buf->len, room, fmt, tm)))
            ಭಙ್ಗ;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        ಯದಿ (room >> 8 > fmt_len)
            ಭಙ್ಗ;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        room = !room ? fmt_len + 1 :
               room <= INT_MAX / 2 ? room * 2 : INT_MAX;
        ಯದಿ (av_bprint_alloc(buf, room)) {
            /* impossible to grow, try to manage something useful anyway */
            room = av_bprint_room(buf);
            ಯದಿ (room < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                ವರ್ಣ buf2[1024];
                ಯದಿ ((l = strftime(buf2, ಪರಿಮಾಣ(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    ಪ್ರತ್ಯಾಗಮ;
                }
            }
            ಯದಿ (room) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', room);
                memcpy(buf->str + buf->len, txt, FFMIN(ಪರಿಮಾಣ(txt) - 1, room));
                av_bprint_grow(buf, room); /* force truncation */
            }
            ಪ್ರತ್ಯಾಗಮ;
        }
    }
    av_bprint_grow(buf, l);
}

ಶೂನ್ಯ av_bprint_get_buffer(AVBPrint *buf, unsigned size,
                          unsigned ವರ್ಣ **mem, unsigned *actual_size)
{
    ಯದಿ (size > av_bprint_room(buf))
        av_bprint_alloc(buf, size);
    *actual_size = av_bprint_room(buf);
    *mem = *actual_size ? (unsigned ವರ್ಣ *) (buf->str + buf->len) : ರಿಕ್ತ;
}

ಶೂನ್ಯ av_bprint_clear(AVBPrint *buf)
{
    ಯದಿ (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

ಪೂರ್ಣಾಙ್ಕ av_bprint_finalize(AVBPrint *buf, ವರ್ಣ **ret_str)
{
    unsigned real_size = FFMIN(buf->len + 1, buf->size);
    ವರ್ಣ *str;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    ಯದಿ (ret_str) {
        ಯದಿ (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_size);
            ಯದಿ (!str)
                str = buf->str;
            buf->str = ರಿಕ್ತ;
        } ಅನ್ಯಥಾ {
            str = av_memdup(buf->str, real_size);
            ಯದಿ (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } ಅನ್ಯಥಾ {
        ಯದಿ (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->size = real_size;
    ಪ್ರತ್ಯಾಗಮ ret;
}

#define WHITESPACES " \n\t\r"

ಶೂನ್ಯ av_bprint_escape(AVBPrint *dstbuf, ಧ್ರುವ ವರ್ಣ *src, ಧ್ರುವ ವರ್ಣ *special_chars,
                      ಗಣನಾ AVEscapeMode mode, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಧ್ರುವ ವರ್ಣ *src0 = src;

    ಯದಿ (mode == AV_ESCAPE_MODE_AUTO)
        mode = AV_ESCAPE_MODE_BACKSLASH; /* TODO: implement a heuristic */

    ವಿಕಲ್ಪ (mode) {
    ಪಕ್ಷ AV_ESCAPE_MODE_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        ಪ್ರತಿ (; *src; src++) {
            ಯದಿ (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            ಅನ್ಯಥಾ
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        ಭಙ್ಗ;

    ಪಕ್ಷ AV_ESCAPE_MODE_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        ಪ್ರತಿ (; *src; src++) {
            ವಿಕಲ್ಪ (*src) {
            ಪಕ್ಷ '&' : av_bprintf(dstbuf, "%s", "&amp;");  ಭಙ್ಗ;
            ಪಕ್ಷ '<' : av_bprintf(dstbuf, "%s", "&lt;");   ಭಙ್ಗ;
            ಪಕ್ಷ '>' : av_bprintf(dstbuf, "%s", "&gt;");   ಭಙ್ಗ;
            ಪಕ್ಷ '\'':
                ಯದಿ (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    ಗಚ್ಛ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                ಭಙ್ಗ;
            ಪಕ್ಷ '"' :
                ಯದಿ (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    ಗಚ್ಛ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                ಭಙ್ಗ;
XML_DEFAULT_HANDLING:
            ಸ್ವಭಾವ: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        ಭಙ್ಗ;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    ಸ್ವಭಾವ:
        /* \-escape characters */
        ಪ್ರತಿ (; *src; src++) {
            ಪೂರ್ಣಾಙ್ಕ is_first_last       = src == src0 || !*(src+1);
            ಪೂರ್ಣಾಙ್ಕ is_ws               = !!strchr(WHITESPACES, *src);
            ಪೂರ್ಣಾಙ್ಕ is_strictly_special = special_chars && strchr(special_chars, *src);
            ಪೂರ್ಣಾಙ್ಕ is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            ಯದಿ (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_last))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        ಭಙ್ಗ;
    }
}
