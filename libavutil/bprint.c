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

#समावेश <limits.h>
#समावेश <stdarg.h>
#समावेश <stdio.h>
#समावेश <string.h>
#समावेश <time.h>
#समावेश "avstring.h"
#समावेश "bprint.h"
#समावेश "error.h"
#समावेश "macros.h"
#समावेश "mem.h"

#घोषणा av_bprint_room(buf) ((buf)->आकार - FFMIN((buf)->len, (buf)->आकार))
#घोषणा av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_internal_बफर)

अटल पूर्णांक av_bprint_alloc(AVBPrint *buf, अचिन्हित room)
{
    अक्षर *old_str, *new_str;
    अचिन्हित min_आकार, new_आकार;

    अगर (buf->आकार == buf->आकार_max)
        वापस AVERROR(EIO);
    अगर (!av_bprint_is_complete(buf))
        वापस AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_आकार = buf->len + 1 + FFMIN(अच_पूर्णांक_उच्च - buf->len - 1, room);
    new_आकार = buf->आकार > buf->आकार_max / 2 ? buf->आकार_max : buf->आकार * 2;
    अगर (new_आकार < min_आकार)
        new_आकार = FFMIN(buf->आकार_max, min_आकार);
    old_str = av_bprint_is_allocated(buf) ? buf->str : शून्य;
    new_str = av_realloc(old_str, new_आकार);
    अगर (!new_str)
        वापस AVERROR(ENOMEM);
    अगर (!old_str)
        स_नकल(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->आकार = new_आकार;
    वापस 0;
}

अटल व्योम av_bprint_grow(AVBPrint *buf, अचिन्हित extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, अच_पूर्णांक_उच्च - 5 - buf->len);
    buf->len += extra_len;
    अगर (buf->आकार)
        buf->str[FFMIN(buf->len, buf->आकार - 1)] = 0;
}

व्योम av_bprint_init(AVBPrint *buf, अचिन्हित आकार_init, अचिन्हित आकार_max)
{
    अचिन्हित आकार_auto = (अक्षर *)buf + माप(*buf) -
                         buf->reserved_internal_बफर;

    अगर (आकार_max == AV_BPRINT_आकार_AUTOMATIC)
        आकार_max = आकार_auto;
    buf->str      = buf->reserved_internal_बफर;
    buf->len      = 0;
    buf->आकार     = FFMIN(आकार_auto, आकार_max);
    buf->आकार_max = आकार_max;
    *buf->str = 0;
    अगर (आकार_init > buf->आकार)
        av_bprint_alloc(buf, आकार_init - 1);
}

व्योम av_bprint_init_for_बफर(AVBPrint *buf, अक्षर *बफर, अचिन्हित आकार)
{
    अगर (आकार == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_आकार_गिनती_ONLY);
        वापस;
    }

    buf->str      = बफर;
    buf->len      = 0;
    buf->आकार     = आकार;
    buf->आकार_max = आकार;
    *buf->str = 0;
}

व्योम av_vbprintf(AVBPrint *buf, स्थिर अक्षर *fmt, बहु_सूची vl_arg)
{
    अचिन्हित room;
    अक्षर *dst;
    पूर्णांक extra_len;
    बहु_सूची vl;

    जबतक (1) {
        room = av_bprint_room(buf);
        dst = room ? buf->str + buf->len : शून्य;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, room, fmt, vl);
        बहु_पूर्ण(vl);
        अगर (extra_len <= 0)
            वापस;
        अगर (extra_len < room)
            अवरोध;
        अगर (av_bprint_alloc(buf, extra_len))
            अवरोध;
    }
    av_bprint_grow(buf, extra_len);
}

व्योम av_bprintf(AVBPrint *buf, स्थिर अक्षर *fmt, ...)
{
    बहु_सूची vl;
    बहु_शुरू(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    बहु_पूर्ण(vl);
}

व्योम av_bprint_chars(AVBPrint *buf, अक्षर c, अचिन्हित n)
{
    अचिन्हित room, real_n;

    जबतक (1) {
        room = av_bprint_room(buf);
        अगर (n < room)
            अवरोध;
        अगर (av_bprint_alloc(buf, n))
            अवरोध;
    }
    अगर (room) {
        real_n = FFMIN(n, room - 1);
        स_रखो(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

व्योम av_bprint_append_तथ्य(AVBPrint *buf, स्थिर अक्षर *तथ्य, अचिन्हित आकार)
{
    अचिन्हित room, real_n;

    जबतक (1) {
        room = av_bprint_room(buf);
        अगर (आकार < room)
            अवरोध;
        अगर (av_bprint_alloc(buf, आकार))
            अवरोध;
    }
    अगर (room) {
        real_n = FFMIN(आकार, room - 1);
        स_नकल(buf->str + buf->len, तथ्य, real_n);
    }
    av_bprint_grow(buf, आकार);
}

व्योम av_bprint_strftime(AVBPrint *buf, स्थिर अक्षर *fmt, स्थिर काष्ठा पंचांग *पंचांग)
{
    अचिन्हित room;
    माप_प्रकार l;
    माप_प्रकार fmt_len = म_माप(fmt);

    अगर (!*fmt)
        वापस;
    जबतक (1) {
        room = av_bprint_room(buf);
        अगर (room && (l = स_माला(buf->str + buf->len, room, fmt, पंचांग)))
            अवरोध;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        अगर (room >> 8 > fmt_len)
            अवरोध;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        room = !room ? fmt_len + 1 :
               room <= पूर्णांक_उच्च / 2 ? room * 2 : पूर्णांक_उच्च;
        अगर (av_bprint_alloc(buf, room)) {
            /* impossible to grow, try to manage something useful anyway */
            room = av_bprint_room(buf);
            अगर (room < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                अक्षर buf2[1024];
                अगर ((l = स_माला(buf2, माप(buf2), fmt, पंचांग))) {
                    av_bprintf(buf, "%s", buf2);
                    वापस;
                }
            }
            अगर (room) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                अटल स्थिर अक्षर txt[] = "[truncated strftime output]";
                स_रखो(buf->str + buf->len, '!', room);
                स_नकल(buf->str + buf->len, txt, FFMIN(माप(txt) - 1, room));
                av_bprint_grow(buf, room); /* force truncation */
            }
            वापस;
        }
    }
    av_bprint_grow(buf, l);
}

व्योम av_bprint_get_बफर(AVBPrint *buf, अचिन्हित आकार,
                          अचिन्हित अक्षर **mem, अचिन्हित *actual_आकार)
{
    अगर (आकार > av_bprint_room(buf))
        av_bprint_alloc(buf, आकार);
    *actual_आकार = av_bprint_room(buf);
    *mem = *actual_आकार ? (अचिन्हित अक्षर *) (buf->str + buf->len) : शून्य;
}

व्योम av_bprint_clear(AVBPrint *buf)
{
    अगर (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

पूर्णांक av_bprint_finalize(AVBPrint *buf, अक्षर **ret_str)
{
    अचिन्हित real_आकार = FFMIN(buf->len + 1, buf->आकार);
    अक्षर *str;
    पूर्णांक ret = 0;

    अगर (ret_str) {
        अगर (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_आकार);
            अगर (!str)
                str = buf->str;
            buf->str = शून्य;
        } अन्यथा {
            str = av_memdup(buf->str, real_आकार);
            अगर (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } अन्यथा {
        अगर (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->आकार = real_आकार;
    वापस ret;
}

#घोषणा WHITESPACES " \n\t\r"

व्योम av_bprint_escape(AVBPrint *dstbuf, स्थिर अक्षर *src, स्थिर अक्षर *special_chars,
                      क्रमागत AVEscapeMode mode, पूर्णांक flags)
{
    स्थिर अक्षर *src0 = src;

    अगर (mode == AV_ESCAPE_MODE_AUTO)
        mode = AV_ESCAPE_MODE_BACKSLASH; /* TODO: implement a heuristic */

    चयन (mode) {
    हाल AV_ESCAPE_MODE_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        क्रम (; *src; src++) {
            अगर (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            अन्यथा
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        अवरोध;

    हाल AV_ESCAPE_MODE_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        क्रम (; *src; src++) {
            चयन (*src) {
            हाल '&' : av_bprintf(dstbuf, "%s", "&amp;");  अवरोध;
            हाल '<' : av_bprintf(dstbuf, "%s", "&lt;");   अवरोध;
            हाल '>' : av_bprintf(dstbuf, "%s", "&gt;");   अवरोध;
            हाल '\'':
                अगर (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    जाओ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                अवरोध;
            हाल '"' :
                अगर (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    जाओ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                अवरोध;
XML_DEFAULT_HANDLING:
            शेष: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        अवरोध;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    शेष:
        /* \-escape characters */
        क्रम (; *src; src++) {
            पूर्णांक is_first_last       = src == src0 || !*(src+1);
            पूर्णांक is_ws               = !!म_अक्षर(WHITESPACES, *src);
            पूर्णांक is_strictly_special = special_chars && म_अक्षर(special_chars, *src);
            पूर्णांक is_special          =
                is_strictly_special || म_अक्षर("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            अगर (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_last))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        अवरोध;
    }
}
