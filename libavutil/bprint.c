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

#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <stdarg.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <time.h>
#அந்தர்பாவ "avstring.h"
#அந்தர்பாவ "bprint.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "mem.h"

#define av_bprint_room(buf) ((buf)->size - FFMIN((buf)->len, (buf)->size))
#define av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_internal_buffer)

நிலையான முழு av_bprint_alloc(AVBPrint *buf, unsigned room)
{
    எழுத்து *old_str, *new_str;
    unsigned min_size, new_size;

    எனில் (buf->size == buf->size_max)
        திரும்பு AVERROR(EIO);
    எனில் (!av_bprint_is_complete(buf))
        திரும்பு AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_size = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, room);
    new_size = buf->size > buf->size_max / 2 ? buf->size_max : buf->size * 2;
    எனில் (new_size < min_size)
        new_size = FFMIN(buf->size_max, min_size);
    old_str = av_bprint_is_allocated(buf) ? buf->str : வெற்று;
    new_str = av_realloc(old_str, new_size);
    எனில் (!new_str)
        திரும்பு AVERROR(ENOMEM);
    எனில் (!old_str)
        memcpy(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->size = new_size;
    திரும்பு 0;
}

நிலையான வெறுமை av_bprint_grow(AVBPrint *buf, unsigned extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    எனில் (buf->size)
        buf->str[FFMIN(buf->len, buf->size - 1)] = 0;
}

வெறுமை av_bprint_init(AVBPrint *buf, unsigned size_init, unsigned size_max)
{
    unsigned size_auto = (எழுத்து *)buf + அளவு(*buf) -
                         buf->reserved_internal_buffer;

    எனில் (size_max == AV_BPRINT_SIZE_AUTOMATIC)
        size_max = size_auto;
    buf->str      = buf->reserved_internal_buffer;
    buf->len      = 0;
    buf->size     = FFMIN(size_auto, size_max);
    buf->size_max = size_max;
    *buf->str = 0;
    எனில் (size_init > buf->size)
        av_bprint_alloc(buf, size_init - 1);
}

வெறுமை av_bprint_init_for_buffer(AVBPrint *buf, எழுத்து *buffer, unsigned size)
{
    எனில் (size == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_SIZE_மொத்தம்_ONLY);
        திரும்பு;
    }

    buf->str      = buffer;
    buf->len      = 0;
    buf->size     = size;
    buf->size_max = size;
    *buf->str = 0;
}

வெறுமை av_vbprintf(AVBPrint *buf, மாறிலி எழுத்து *fmt, va_list vl_arg)
{
    unsigned room;
    எழுத்து *dst;
    முழு extra_len;
    va_list vl;

    போது (1) {
        room = av_bprint_room(buf);
        dst = room ? buf->str + buf->len : வெற்று;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, room, fmt, vl);
        va_end(vl);
        எனில் (extra_len <= 0)
            திரும்பு;
        எனில் (extra_len < room)
            நிறுத்து;
        எனில் (av_bprint_alloc(buf, extra_len))
            நிறுத்து;
    }
    av_bprint_grow(buf, extra_len);
}

வெறுமை av_bprintf(AVBPrint *buf, மாறிலி எழுத்து *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

வெறுமை av_bprint_chars(AVBPrint *buf, எழுத்து c, unsigned n)
{
    unsigned room, real_n;

    போது (1) {
        room = av_bprint_room(buf);
        எனில் (n < room)
            நிறுத்து;
        எனில் (av_bprint_alloc(buf, n))
            நிறுத்து;
    }
    எனில் (room) {
        real_n = FFMIN(n, room - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

வெறுமை av_bprint_append_data(AVBPrint *buf, மாறிலி எழுத்து *data, unsigned size)
{
    unsigned room, real_n;

    போது (1) {
        room = av_bprint_room(buf);
        எனில் (size < room)
            நிறுத்து;
        எனில் (av_bprint_alloc(buf, size))
            நிறுத்து;
    }
    எனில் (room) {
        real_n = FFMIN(size, room - 1);
        memcpy(buf->str + buf->len, data, real_n);
    }
    av_bprint_grow(buf, size);
}

வெறுமை av_bprint_strftime(AVBPrint *buf, மாறிலி எழுத்து *fmt, மாறிலி கட்டமைப்பு tm *tm)
{
    unsigned room;
    size_t l;
    size_t fmt_len = strlen(fmt);

    எனில் (!*fmt)
        திரும்பு;
    போது (1) {
        room = av_bprint_room(buf);
        எனில் (room && (l = strftime(buf->str + buf->len, room, fmt, tm)))
            நிறுத்து;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        எனில் (room >> 8 > fmt_len)
            நிறுத்து;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        room = !room ? fmt_len + 1 :
               room <= INT_MAX / 2 ? room * 2 : INT_MAX;
        எனில் (av_bprint_alloc(buf, room)) {
            /* impossible to grow, try to manage something useful anyway */
            room = av_bprint_room(buf);
            எனில் (room < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                எழுத்து buf2[1024];
                எனில் ((l = strftime(buf2, அளவு(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    திரும்பு;
                }
            }
            எனில் (room) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                நிலையான மாறிலி எழுத்து txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', room);
                memcpy(buf->str + buf->len, txt, FFMIN(அளவு(txt) - 1, room));
                av_bprint_grow(buf, room); /* force truncation */
            }
            திரும்பு;
        }
    }
    av_bprint_grow(buf, l);
}

வெறுமை av_bprint_get_buffer(AVBPrint *buf, unsigned size,
                          unsigned எழுத்து **mem, unsigned *actual_size)
{
    எனில் (size > av_bprint_room(buf))
        av_bprint_alloc(buf, size);
    *actual_size = av_bprint_room(buf);
    *mem = *actual_size ? (unsigned எழுத்து *) (buf->str + buf->len) : வெற்று;
}

வெறுமை av_bprint_clear(AVBPrint *buf)
{
    எனில் (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

முழு av_bprint_finalize(AVBPrint *buf, எழுத்து **ret_str)
{
    unsigned real_size = FFMIN(buf->len + 1, buf->size);
    எழுத்து *str;
    முழு ret = 0;

    எனில் (ret_str) {
        எனில் (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_size);
            எனில் (!str)
                str = buf->str;
            buf->str = வெற்று;
        } இல்லையெனில் {
            str = av_memdup(buf->str, real_size);
            எனில் (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } இல்லையெனில் {
        எனில் (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->size = real_size;
    திரும்பு ret;
}

#define WHITESPACES " \n\t\r"

வெறுமை av_bprint_escape(AVBPrint *dstbuf, மாறிலி எழுத்து *src, மாறிலி எழுத்து *special_chars,
                      எண்ணிக்கை AVEscapeMode mode, முழு flags)
{
    மாறிலி எழுத்து *src0 = src;

    எனில் (mode == AV_ESCAPE_MODE_AUTO)
        mode = AV_ESCAPE_MODE_BACKSLASH; /* TODO: implement a heuristic */

    தேர்வு (mode) {
    நிலை AV_ESCAPE_MODE_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        க்கு (; *src; src++) {
            எனில் (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            இல்லையெனில்
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        நிறுத்து;

    நிலை AV_ESCAPE_MODE_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        க்கு (; *src; src++) {
            தேர்வு (*src) {
            நிலை '&' : av_bprintf(dstbuf, "%s", "&amp;");  நிறுத்து;
            நிலை '<' : av_bprintf(dstbuf, "%s", "&lt;");   நிறுத்து;
            நிலை '>' : av_bprintf(dstbuf, "%s", "&gt;");   நிறுத்து;
            நிலை '\'':
                எனில் (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    செல் XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                நிறுத்து;
            நிலை '"' :
                எனில் (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    செல் XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                நிறுத்து;
XML_DEFAULT_HANDLING:
            இயல்பு: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        நிறுத்து;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    இயல்பு:
        /* \-escape characters */
        க்கு (; *src; src++) {
            முழு is_first_last       = src == src0 || !*(src+1);
            முழு is_ws               = !!strchr(WHITESPACES, *src);
            முழு is_strictly_special = special_chars && strchr(special_chars, *src);
            முழு is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            எனில் (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_last))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        நிறுத்து;
    }
}
