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

#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <stdarg.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <time.h>
#അന്തര്ഭാവ "avstring.h"
#അന്തര്ഭാവ "bprint.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"

#define av_bprint_room(buf) ((buf)->size - FFMIN((buf)->len, (buf)->size))
#define av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_internal_buffer)

സ്ഥിതം പൂർണ്ണസംഖ്യ av_bprint_alloc(AVBPrint *buf, unsigned room)
{
    അക്ഷരം *old_str, *new_str;
    unsigned min_size, new_size;

    എങ്കിൽ (buf->size == buf->size_max)
        തിരികെ AVERROR(EIO);
    എങ്കിൽ (!av_bprint_is_complete(buf))
        തിരികെ AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_size = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, room);
    new_size = buf->size > buf->size_max / 2 ? buf->size_max : buf->size * 2;
    എങ്കിൽ (new_size < min_size)
        new_size = FFMIN(buf->size_max, min_size);
    old_str = av_bprint_is_allocated(buf) ? buf->str : ശൂന്യ;
    new_str = av_realloc(old_str, new_size);
    എങ്കിൽ (!new_str)
        തിരികെ AVERROR(ENOMEM);
    എങ്കിൽ (!old_str)
        memcpy(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->size = new_size;
    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം av_bprint_grow(AVBPrint *buf, unsigned extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    എങ്കിൽ (buf->size)
        buf->str[FFMIN(buf->len, buf->size - 1)] = 0;
}

ശൂന്യം av_bprint_init(AVBPrint *buf, unsigned size_init, unsigned size_max)
{
    unsigned size_auto = (അക്ഷരം *)buf + വലുപ്പം(*buf) -
                         buf->reserved_internal_buffer;

    എങ്കിൽ (size_max == AV_BPRINT_SIZE_AUTOMATIC)
        size_max = size_auto;
    buf->str      = buf->reserved_internal_buffer;
    buf->len      = 0;
    buf->size     = FFMIN(size_auto, size_max);
    buf->size_max = size_max;
    *buf->str = 0;
    എങ്കിൽ (size_init > buf->size)
        av_bprint_alloc(buf, size_init - 1);
}

ശൂന്യം av_bprint_init_for_buffer(AVBPrint *buf, അക്ഷരം *buffer, unsigned size)
{
    എങ്കിൽ (size == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_SIZE_എണ്ണം_ONLY);
        തിരികെ;
    }

    buf->str      = buffer;
    buf->len      = 0;
    buf->size     = size;
    buf->size_max = size;
    *buf->str = 0;
}

ശൂന്യം av_vbprintf(AVBPrint *buf, സ്ഥിരം അക്ഷരം *fmt, va_list vl_arg)
{
    unsigned room;
    അക്ഷരം *dst;
    പൂർണ്ണസംഖ്യ extra_len;
    va_list vl;

    ആകുമ്പോൾ (1) {
        room = av_bprint_room(buf);
        dst = room ? buf->str + buf->len : ശൂന്യ;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, room, fmt, vl);
        va_end(vl);
        എങ്കിൽ (extra_len <= 0)
            തിരികെ;
        എങ്കിൽ (extra_len < room)
            നിർത്തുക;
        എങ്കിൽ (av_bprint_alloc(buf, extra_len))
            നിർത്തുക;
    }
    av_bprint_grow(buf, extra_len);
}

ശൂന്യം av_bprintf(AVBPrint *buf, സ്ഥിരം അക്ഷരം *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

ശൂന്യം av_bprint_chars(AVBPrint *buf, അക്ഷരം c, unsigned n)
{
    unsigned room, real_n;

    ആകുമ്പോൾ (1) {
        room = av_bprint_room(buf);
        എങ്കിൽ (n < room)
            നിർത്തുക;
        എങ്കിൽ (av_bprint_alloc(buf, n))
            നിർത്തുക;
    }
    എങ്കിൽ (room) {
        real_n = FFMIN(n, room - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

ശൂന്യം av_bprint_append_data(AVBPrint *buf, സ്ഥിരം അക്ഷരം *data, unsigned size)
{
    unsigned room, real_n;

    ആകുമ്പോൾ (1) {
        room = av_bprint_room(buf);
        എങ്കിൽ (size < room)
            നിർത്തുക;
        എങ്കിൽ (av_bprint_alloc(buf, size))
            നിർത്തുക;
    }
    എങ്കിൽ (room) {
        real_n = FFMIN(size, room - 1);
        memcpy(buf->str + buf->len, data, real_n);
    }
    av_bprint_grow(buf, size);
}

ശൂന്യം av_bprint_strftime(AVBPrint *buf, സ്ഥിരം അക്ഷരം *fmt, സ്ഥിരം ഘടന tm *tm)
{
    unsigned room;
    size_t l;
    size_t fmt_len = strlen(fmt);

    എങ്കിൽ (!*fmt)
        തിരികെ;
    ആകുമ്പോൾ (1) {
        room = av_bprint_room(buf);
        എങ്കിൽ (room && (l = strftime(buf->str + buf->len, room, fmt, tm)))
            നിർത്തുക;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        എങ്കിൽ (room >> 8 > fmt_len)
            നിർത്തുക;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        room = !room ? fmt_len + 1 :
               room <= INT_MAX / 2 ? room * 2 : INT_MAX;
        എങ്കിൽ (av_bprint_alloc(buf, room)) {
            /* impossible to grow, try to manage something useful anyway */
            room = av_bprint_room(buf);
            എങ്കിൽ (room < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                അക്ഷരം buf2[1024];
                എങ്കിൽ ((l = strftime(buf2, വലുപ്പം(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    തിരികെ;
                }
            }
            എങ്കിൽ (room) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                സ്ഥിതം സ്ഥിരം അക്ഷരം txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', room);
                memcpy(buf->str + buf->len, txt, FFMIN(വലുപ്പം(txt) - 1, room));
                av_bprint_grow(buf, room); /* force truncation */
            }
            തിരികെ;
        }
    }
    av_bprint_grow(buf, l);
}

ശൂന്യം av_bprint_get_buffer(AVBPrint *buf, unsigned size,
                          unsigned അക്ഷരം **mem, unsigned *actual_size)
{
    എങ്കിൽ (size > av_bprint_room(buf))
        av_bprint_alloc(buf, size);
    *actual_size = av_bprint_room(buf);
    *mem = *actual_size ? (unsigned അക്ഷരം *) (buf->str + buf->len) : ശൂന്യ;
}

ശൂന്യം av_bprint_clear(AVBPrint *buf)
{
    എങ്കിൽ (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

പൂർണ്ണസംഖ്യ av_bprint_finalize(AVBPrint *buf, അക്ഷരം **ret_str)
{
    unsigned real_size = FFMIN(buf->len + 1, buf->size);
    അക്ഷരം *str;
    പൂർണ്ണസംഖ്യ ret = 0;

    എങ്കിൽ (ret_str) {
        എങ്കിൽ (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_size);
            എങ്കിൽ (!str)
                str = buf->str;
            buf->str = ശൂന്യ;
        } അല്ലെങ്കിൽ {
            str = av_memdup(buf->str, real_size);
            എങ്കിൽ (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->size = real_size;
    തിരികെ ret;
}

#define WHITESPACES " \n\t\r"

ശൂന്യം av_bprint_escape(AVBPrint *dstbuf, സ്ഥിരം അക്ഷരം *src, സ്ഥിരം അക്ഷരം *special_chars,
                      എണ്ണൽ AVEscapeMode mode, പൂർണ്ണസംഖ്യ flags)
{
    സ്ഥിരം അക്ഷരം *src0 = src;

    എങ്കിൽ (mode == AV_ESCAPE_MODE_AUTO)
        mode = AV_ESCAPE_MODE_BACKSLASH; /* TODO: implement a heuristic */

    തിരഞ്ഞെടുപ്പ് (mode) {
    അവസ്ഥ AV_ESCAPE_MODE_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        വേണ്ടി (; *src; src++) {
            എങ്കിൽ (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            അല്ലെങ്കിൽ
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        നിർത്തുക;

    അവസ്ഥ AV_ESCAPE_MODE_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        വേണ്ടി (; *src; src++) {
            തിരഞ്ഞെടുപ്പ് (*src) {
            അവസ്ഥ '&' : av_bprintf(dstbuf, "%s", "&amp;");  നിർത്തുക;
            അവസ്ഥ '<' : av_bprintf(dstbuf, "%s", "&lt;");   നിർത്തുക;
            അവസ്ഥ '>' : av_bprintf(dstbuf, "%s", "&gt;");   നിർത്തുക;
            അവസ്ഥ '\'':
                എങ്കിൽ (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    പോകുക XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                നിർത്തുക;
            അവസ്ഥ '"' :
                എങ്കിൽ (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    പോകുക XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                നിർത്തുക;
XML_DEFAULT_HANDLING:
            സ്ഥിരസ്ഥിതി: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        നിർത്തുക;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    സ്ഥിരസ്ഥിതി:
        /* \-escape characters */
        വേണ്ടി (; *src; src++) {
            പൂർണ്ണസംഖ്യ is_first_last       = src == src0 || !*(src+1);
            പൂർണ്ണസംഖ്യ is_ws               = !!strchr(WHITESPACES, *src);
            പൂർണ്ണസംഖ്യ is_strictly_special = special_chars && strchr(special_chars, *src);
            പൂർണ്ണസംഖ്യ is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            എങ്കിൽ (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_last))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        നിർത്തുക;
    }
}
