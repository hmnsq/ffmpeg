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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdarg.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <time.h>
#अन्तर्भाव "avstring.h"
#अन्तर्भाव "bprint.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"

#define av_bprint_room(buf) ((buf)->size - FFMIN((buf)->len, (buf)->size))
#define av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_internal_buffer)

स्थिर पूर्णाङ्क av_bprint_alloc(AVBPrint *buf, unsigned room)
{
    वर्ण *old_str, *new_str;
    unsigned min_size, new_size;

    सचे (buf->size == buf->size_max)
        पटिनिवत्त AVERROR(EIO);
    सचे (!av_bprint_is_complete(buf))
        पटिनिवत्त AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_size = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, room);
    new_size = buf->size > buf->size_max / 2 ? buf->size_max : buf->size * 2;
    सचे (new_size < min_size)
        new_size = FFMIN(buf->size_max, min_size);
    old_str = av_bprint_is_allocated(buf) ? buf->str : रिक्त;
    new_str = av_realloc(old_str, new_size);
    सचे (!new_str)
        पटिनिवत्त AVERROR(ENOMEM);
    सचे (!old_str)
        memcpy(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->size = new_size;
    पटिनिवत्त 0;
}

स्थिर शून्य av_bprint_grow(AVBPrint *buf, unsigned extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    सचे (buf->size)
        buf->str[FFMIN(buf->len, buf->size - 1)] = 0;
}

शून्य av_bprint_init(AVBPrint *buf, unsigned size_init, unsigned size_max)
{
    unsigned size_auto = (वर्ण *)buf + परिमाण(*buf) -
                         buf->reserved_internal_buffer;

    सचे (size_max == AV_BPRINT_SIZE_AUTOMATIC)
        size_max = size_auto;
    buf->str      = buf->reserved_internal_buffer;
    buf->len      = 0;
    buf->size     = FFMIN(size_auto, size_max);
    buf->size_max = size_max;
    *buf->str = 0;
    सचे (size_init > buf->size)
        av_bprint_alloc(buf, size_init - 1);
}

शून्य av_bprint_init_for_buffer(AVBPrint *buf, वर्ण *buffer, unsigned size)
{
    सचे (size == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_SIZE_गणनम्_ONLY);
        पटिनिवत्त;
    }

    buf->str      = buffer;
    buf->len      = 0;
    buf->size     = size;
    buf->size_max = size;
    *buf->str = 0;
}

शून्य av_vbprintf(AVBPrint *buf, ध्रुव वर्ण *fmt, va_list vl_arg)
{
    unsigned room;
    वर्ण *dst;
    पूर्णाङ्क extra_len;
    va_list vl;

    याव (1) {
        room = av_bprint_room(buf);
        dst = room ? buf->str + buf->len : रिक्त;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, room, fmt, vl);
        va_end(vl);
        सचे (extra_len <= 0)
            पटिनिवत्त;
        सचे (extra_len < room)
            भङ्ग;
        सचे (av_bprint_alloc(buf, extra_len))
            भङ्ग;
    }
    av_bprint_grow(buf, extra_len);
}

शून्य av_bprintf(AVBPrint *buf, ध्रुव वर्ण *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

शून्य av_bprint_chars(AVBPrint *buf, वर्ण c, unsigned n)
{
    unsigned room, real_n;

    याव (1) {
        room = av_bprint_room(buf);
        सचे (n < room)
            भङ्ग;
        सचे (av_bprint_alloc(buf, n))
            भङ्ग;
    }
    सचे (room) {
        real_n = FFMIN(n, room - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

शून्य av_bprint_append_data(AVBPrint *buf, ध्रुव वर्ण *data, unsigned size)
{
    unsigned room, real_n;

    याव (1) {
        room = av_bprint_room(buf);
        सचे (size < room)
            भङ्ग;
        सचे (av_bprint_alloc(buf, size))
            भङ्ग;
    }
    सचे (room) {
        real_n = FFMIN(size, room - 1);
        memcpy(buf->str + buf->len, data, real_n);
    }
    av_bprint_grow(buf, size);
}

शून्य av_bprint_strftime(AVBPrint *buf, ध्रुव वर्ण *fmt, ध्रुव संरचना tm *tm)
{
    unsigned room;
    size_t l;
    size_t fmt_len = strlen(fmt);

    सचे (!*fmt)
        पटिनिवत्त;
    याव (1) {
        room = av_bprint_room(buf);
        सचे (room && (l = strftime(buf->str + buf->len, room, fmt, tm)))
            भङ्ग;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        सचे (room >> 8 > fmt_len)
            भङ्ग;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        room = !room ? fmt_len + 1 :
               room <= INT_MAX / 2 ? room * 2 : INT_MAX;
        सचे (av_bprint_alloc(buf, room)) {
            /* impossible to grow, try to manage something useful anyway */
            room = av_bprint_room(buf);
            सचे (room < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                वर्ण buf2[1024];
                सचे ((l = strftime(buf2, परिमाण(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    पटिनिवत्त;
                }
            }
            सचे (room) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                स्थिर ध्रुव वर्ण txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', room);
                memcpy(buf->str + buf->len, txt, FFMIN(परिमाण(txt) - 1, room));
                av_bprint_grow(buf, room); /* force truncation */
            }
            पटिनिवत्त;
        }
    }
    av_bprint_grow(buf, l);
}

शून्य av_bprint_get_buffer(AVBPrint *buf, unsigned size,
                          unsigned वर्ण **mem, unsigned *actual_size)
{
    सचे (size > av_bprint_room(buf))
        av_bprint_alloc(buf, size);
    *actual_size = av_bprint_room(buf);
    *mem = *actual_size ? (unsigned वर्ण *) (buf->str + buf->len) : रिक्त;
}

शून्य av_bprint_clear(AVBPrint *buf)
{
    सचे (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

पूर्णाङ्क av_bprint_finalize(AVBPrint *buf, वर्ण **ret_str)
{
    unsigned real_size = FFMIN(buf->len + 1, buf->size);
    वर्ण *str;
    पूर्णाङ्क ret = 0;

    सचे (ret_str) {
        सचे (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_size);
            सचे (!str)
                str = buf->str;
            buf->str = रिक्त;
        } अञ्ञथा {
            str = av_memdup(buf->str, real_size);
            सचे (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } अञ्ञथा {
        सचे (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->size = real_size;
    पटिनिवत्त ret;
}

#define WHITESPACES " \n\t\r"

शून्य av_bprint_escape(AVBPrint *dstbuf, ध्रुव वर्ण *src, ध्रुव वर्ण *special_chars,
                      गणना AVEscapeMode mode, पूर्णाङ्क flags)
{
    ध्रुव वर्ण *src0 = src;

    सचे (mode == AV_ESCAPE_MODE_AUTO)
        mode = AV_ESCAPE_MODE_BACKSLASH; /* TODO: implement a heuristic */

    विकल्प (mode) {
    पक्ष AV_ESCAPE_MODE_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        अत्थाय (; *src; src++) {
            सचे (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            अञ्ञथा
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        भङ्ग;

    पक्ष AV_ESCAPE_MODE_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        अत्थाय (; *src; src++) {
            विकल्प (*src) {
            पक्ष '&' : av_bprintf(dstbuf, "%s", "&amp;");  भङ्ग;
            पक्ष '<' : av_bprintf(dstbuf, "%s", "&lt;");   भङ्ग;
            पक्ष '>' : av_bprintf(dstbuf, "%s", "&gt;");   भङ्ग;
            पक्ष '\'':
                सचे (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    गच्छ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                भङ्ग;
            पक्ष '"' :
                सचे (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    गच्छ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                भङ्ग;
XML_DEFAULT_HANDLING:
            स्वभाव: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        भङ्ग;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    स्वभाव:
        /* \-escape characters */
        अत्थाय (; *src; src++) {
            पूर्णाङ्क is_first_last       = src == src0 || !*(src+1);
            पूर्णाङ्क is_ws               = !!strchr(WHITESPACES, *src);
            पूर्णाङ्क is_strictly_special = special_chars && strchr(special_chars, *src);
            पूर्णाङ्क is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            सचे (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_last))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        भङ्ग;
    }
}
