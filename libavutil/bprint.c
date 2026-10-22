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

स्थिर पूर्णाङ्क av_bprint_alloc(AVBPrint *buf, अचिन्हित room)
{
    वर्ण *old_str, *new_str;
    अचिन्हित min_size, new_size;

    यदि (buf->size == buf->size_max)
        फर्काऊ AVERROR(EIO);
    यदि (!av_bprint_is_complete(buf))
        फर्काऊ AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_size = buf->len + 1 + FFMIN(अच_पूर्णांक_उच्च - buf->len - 1, room);
    new_size = buf->size > buf->size_max / 2 ? buf->size_max : buf->size * 2;
    यदि (new_size < min_size)
        new_size = FFMIN(buf->size_max, min_size);
    old_str = av_bprint_is_allocated(buf) ? buf->str : रिक्त;
    new_str = av_realloc(old_str, new_size);
    यदि (!new_str)
        फर्काऊ AVERROR(ENOMEM);
    यदि (!old_str)
        स_नकल(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->size = new_size;
    फर्काऊ 0;
}

स्थिर शून्य av_bprint_grow(AVBPrint *buf, अचिन्हित extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, अच_पूर्णांक_उच्च - 5 - buf->len);
    buf->len += extra_len;
    यदि (buf->size)
        buf->str[FFMIN(buf->len, buf->size - 1)] = 0;
}

शून्य av_bprint_init(AVBPrint *buf, अचिन्हित size_init, अचिन्हित size_max)
{
    अचिन्हित size_auto = (वर्ण *)buf + परिमाण(*buf) -
                         buf->reserved_internal_buffer;

    यदि (size_max == AV_BPRINT_SIZE_AUTOMATIC)
        size_max = size_auto;
    buf->str      = buf->reserved_internal_buffer;
    buf->len      = 0;
    buf->size     = FFMIN(size_auto, size_max);
    buf->size_max = size_max;
    *buf->str = 0;
    यदि (size_init > buf->size)
        av_bprint_alloc(buf, size_init - 1);
}

शून्य av_bprint_init_for_buffer(AVBPrint *buf, वर्ण *buffer, अचिन्हित size)
{
    यदि (size == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_SIZE_गन्ती_ONLY);
        फर्काऊ;
    }

    buf->str      = buffer;
    buf->len      = 0;
    buf->size     = size;
    buf->size_max = size;
    *buf->str = 0;
}

शून्य av_vbprintf(AVBPrint *buf, अचर वर्ण *fmt, बहु_सूची vl_arg)
{
    अचिन्हित room;
    वर्ण *dst;
    पूर्णाङ्क extra_len;
    बहु_सूची vl;

    जबसम्म (1) {
        room = av_bprint_room(buf);
        dst = room ? buf->str + buf->len : रिक्त;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, room, fmt, vl);
        बहु_पूर्ण(vl);
        यदि (extra_len <= 0)
            फर्काऊ;
        यदि (extra_len < room)
            रोक;
        यदि (av_bprint_alloc(buf, extra_len))
            रोक;
    }
    av_bprint_grow(buf, extra_len);
}

शून्य av_bprintf(AVBPrint *buf, अचर वर्ण *fmt, ...)
{
    बहु_सूची vl;
    बहु_शुरू(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    बहु_पूर्ण(vl);
}

शून्य av_bprint_chars(AVBPrint *buf, वर्ण c, अचिन्हित n)
{
    अचिन्हित room, real_n;

    जबसम्म (1) {
        room = av_bprint_room(buf);
        यदि (n < room)
            रोक;
        यदि (av_bprint_alloc(buf, n))
            रोक;
    }
    यदि (room) {
        real_n = FFMIN(n, room - 1);
        स_रखो(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

शून्य av_bprint_append_data(AVBPrint *buf, अचर वर्ण *data, अचिन्हित size)
{
    अचिन्हित room, real_n;

    जबसम्म (1) {
        room = av_bprint_room(buf);
        यदि (size < room)
            रोक;
        यदि (av_bprint_alloc(buf, size))
            रोक;
    }
    यदि (room) {
        real_n = FFMIN(size, room - 1);
        स_नकल(buf->str + buf->len, data, real_n);
    }
    av_bprint_grow(buf, size);
}

शून्य av_bprint_strftime(AVBPrint *buf, अचर वर्ण *fmt, अचर संरचना पंचांग *पंचांग)
{
    अचिन्हित room;
    माप_प्रकार l;
    माप_प्रकार fmt_len = म_माप(fmt);

    यदि (!*fmt)
        फर्काऊ;
    जबसम्म (1) {
        room = av_bprint_room(buf);
        यदि (room && (l = स_माला(buf->str + buf->len, room, fmt, पंचांग)))
            रोक;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        यदि (room >> 8 > fmt_len)
            रोक;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        room = !room ? fmt_len + 1 :
               room <= पूर्णांक_उच्च / 2 ? room * 2 : पूर्णांक_उच्च;
        यदि (av_bprint_alloc(buf, room)) {
            /* impossible to grow, try to manage something useful anyway */
            room = av_bprint_room(buf);
            यदि (room < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                वर्ण buf2[1024];
                यदि ((l = स_माला(buf2, परिमाण(buf2), fmt, पंचांग))) {
                    av_bprintf(buf, "%s", buf2);
                    फर्काऊ;
                }
            }
            यदि (room) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                स्थिर अचर वर्ण txt[] = "[truncated strftime output]";
                स_रखो(buf->str + buf->len, '!', room);
                स_नकल(buf->str + buf->len, txt, FFMIN(परिमाण(txt) - 1, room));
                av_bprint_grow(buf, room); /* force truncation */
            }
            फर्काऊ;
        }
    }
    av_bprint_grow(buf, l);
}

शून्य av_bprint_get_buffer(AVBPrint *buf, अचिन्हित size,
                          अचिन्हित वर्ण **mem, अचिन्हित *actual_size)
{
    यदि (size > av_bprint_room(buf))
        av_bprint_alloc(buf, size);
    *actual_size = av_bprint_room(buf);
    *mem = *actual_size ? (अचिन्हित वर्ण *) (buf->str + buf->len) : रिक्त;
}

शून्य av_bprint_clear(AVBPrint *buf)
{
    यदि (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

पूर्णाङ्क av_bprint_finalize(AVBPrint *buf, वर्ण **ret_str)
{
    अचिन्हित real_size = FFMIN(buf->len + 1, buf->size);
    वर्ण *str;
    पूर्णाङ्क ret = 0;

    यदि (ret_str) {
        यदि (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_size);
            यदि (!str)
                str = buf->str;
            buf->str = रिक्त;
        } अन्यथा {
            str = av_memdup(buf->str, real_size);
            यदि (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } अन्यथा {
        यदि (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->size = real_size;
    फर्काऊ ret;
}

#define WHITESPACES " \n\t\r"

शून्य av_bprint_escape(AVBPrint *dstbuf, अचर वर्ण *src, अचर वर्ण *special_chars,
                      गणना AVEscapeMode mode, पूर्णाङ्क flags)
{
    अचर वर्ण *src0 = src;

    यदि (mode == AV_ESCAPE_MODE_AUTO)
        mode = AV_ESCAPE_MODE_BACKSLASH; /* TODO: implement a heuristic */

    विकल्प (mode) {
    पक्ष AV_ESCAPE_MODE_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        लागि (; *src; src++) {
            यदि (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            अन्यथा
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        रोक;

    पक्ष AV_ESCAPE_MODE_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        लागि (; *src; src++) {
            विकल्प (*src) {
            पक्ष '&' : av_bprintf(dstbuf, "%s", "&amp;");  रोक;
            पक्ष '<' : av_bprintf(dstbuf, "%s", "&lt;");   रोक;
            पक्ष '>' : av_bprintf(dstbuf, "%s", "&gt;");   रोक;
            पक्ष '\'':
                यदि (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    गच्छ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                रोक;
            पक्ष '"' :
                यदि (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    गच्छ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                रोक;
XML_DEFAULT_HANDLING:
            स्वभाव: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        रोक;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    स्वभाव:
        /* \-escape characters */
        लागि (; *src; src++) {
            पूर्णाङ्क is_first_last       = src == src0 || !*(src+1);
            पूर्णाङ्क is_ws               = !!म_अक्षर(WHITESPACES, *src);
            पूर्णाङ्क is_strictly_special = special_chars && म_अक्षर(special_chars, *src);
            पूर्णाङ्क is_special          =
                is_strictly_special || म_अक्षर("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            यदि (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_last))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        रोक;
    }
}
