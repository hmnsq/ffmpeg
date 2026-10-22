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

#परिभाषय av_bprint_अवकाशः(buf) ((buf)->आकार - FFMIN((buf)->len, (buf)->आकार))
#परिभाषय av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_आन्तरिकम्_बफर)

स्थिर पूर्णाङ्क av_bprint_alloc(AVBPrint *buf, अचिह्नित अवकाशः)
{
    वर्ण *old_str, *new_str;
    अचिह्नित min_आकार, new_आकार;

    यदि (buf->आकार == buf->आकार_max)
        प्रत्यागम AVERROR(EIO);
    यदि (!av_bprint_is_complete(buf))
        प्रत्यागम AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_आकार = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, अवकाशः);
    new_आकार = buf->आकार > buf->आकार_max / 2 ? buf->आकार_max : buf->आकार * 2;
    यदि (new_आकार < min_आकार)
        new_आकार = FFMIN(buf->आकार_max, min_आकार);
    old_str = av_bprint_is_allocated(buf) ? buf->str : रिक्त;
    new_str = av_realloc(old_str, new_आकार);
    यदि (!new_str)
        प्रत्यागम AVERROR(ENOMEM);
    यदि (!old_str)
        स्मृतिं_प्रतिलिख(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->आकार = new_आकार;
    प्रत्यागम 0;
}

स्थिर शून्य av_bprint_grow(AVBPrint *buf, अचिह्नित extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    यदि (buf->आकार)
        buf->str[FFMIN(buf->len, buf->आकार - 1)] = 0;
}

शून्य av_bprint_init(AVBPrint *buf, अचिह्नित आकार_init, अचिह्नित आकार_max)
{
    अचिह्नित आकार_auto = (वर्ण *)buf + परिमाण(*buf) -
                         buf->reserved_आन्तरिकम्_बफर;

    यदि (आकार_max == AV_BPRINT_आकार_AUTOMATIC)
        आकार_max = आकार_auto;
    buf->str      = buf->reserved_आन्तरिकम्_बफर;
    buf->len      = 0;
    buf->आकार     = FFMIN(आकार_auto, आकार_max);
    buf->आकार_max = आकार_max;
    *buf->str = 0;
    यदि (आकार_init > buf->आकार)
        av_bprint_alloc(buf, आकार_init - 1);
}

शून्य av_bprint_init_for_बफर(AVBPrint *buf, वर्ण *बफर, अचिह्नित आकार)
{
    यदि (आकार == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_आकार_गणनम्_ONLY);
        प्रत्यागम;
    }

    buf->str      = बफर;
    buf->len      = 0;
    buf->आकार     = आकार;
    buf->आकार_max = आकार;
    *buf->str = 0;
}

शून्य av_vbprintf(AVBPrint *buf, ध्रुव वर्ण *fmt, va_list vl_arg)
{
    अचिह्नित अवकाशः;
    वर्ण *dst;
    पूर्णाङ्क extra_len;
    va_list vl;

    यावत् (1) {
        अवकाशः = av_bprint_अवकाशः(buf);
        dst = अवकाशः ? buf->str + buf->len : रिक्त;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, अवकाशः, fmt, vl);
        va_end(vl);
        यदि (extra_len <= 0)
            प्रत्यागम;
        यदि (extra_len < अवकाशः)
            भङ्ग;
        यदि (av_bprint_alloc(buf, extra_len))
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

शून्य av_bprint_chars(AVBPrint *buf, वर्ण c, अचिह्नित n)
{
    अचिह्नित अवकाशः, real_n;

    यावत् (1) {
        अवकाशः = av_bprint_अवकाशः(buf);
        यदि (n < अवकाशः)
            भङ्ग;
        यदि (av_bprint_alloc(buf, n))
            भङ्ग;
    }
    यदि (अवकाशः) {
        real_n = FFMIN(n, अवकाशः - 1);
        स्मृतिं_पूरय(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

शून्य av_bprint_append_दत्त(AVBPrint *buf, ध्रुव वर्ण *दत्त, अचिह्नित आकार)
{
    अचिह्नित अवकाशः, real_n;

    यावत् (1) {
        अवकाशः = av_bprint_अवकाशः(buf);
        यदि (आकार < अवकाशः)
            भङ्ग;
        यदि (av_bprint_alloc(buf, आकार))
            भङ्ग;
    }
    यदि (अवकाशः) {
        real_n = FFMIN(आकार, अवकाशः - 1);
        स्मृतिं_प्रतिलिख(buf->str + buf->len, दत्त, real_n);
    }
    av_bprint_grow(buf, आकार);
}

शून्य av_bprint_strftime(AVBPrint *buf, ध्रुव वर्ण *fmt, ध्रुव संरचना tm *tm)
{
    अचिह्नित अवकाशः;
    size_t l;
    size_t fmt_len = वाक्यदैर्घ्यम्(fmt);

    यदि (!*fmt)
        प्रत्यागम;
    यावत् (1) {
        अवकाशः = av_bprint_अवकाशः(buf);
        यदि (अवकाशः && (l = strftime(buf->str + buf->len, अवकाशः, fmt, tm)))
            भङ्ग;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        यदि (अवकाशः >> 8 > fmt_len)
            भङ्ग;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        अवकाशः = !अवकाशः ? fmt_len + 1 :
               अवकाशः <= अधिकतम_पूर्णाङ्कः / 2 ? अवकाशः * 2 : अधिकतम_पूर्णाङ्कः;
        यदि (av_bprint_alloc(buf, अवकाशः)) {
            /* impossible to grow, try to manage something useful anyway */
            अवकाशः = av_bprint_अवकाशः(buf);
            यदि (अवकाशः < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                वर्ण buf2[1024];
                यदि ((l = strftime(buf2, परिमाण(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    प्रत्यागम;
                }
            }
            यदि (अवकाशः) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                स्थिर ध्रुव वर्ण txt[] = "[truncated strftime output]";
                स्मृतिं_पूरय(buf->str + buf->len, '!', अवकाशः);
                स्मृतिं_प्रतिलिख(buf->str + buf->len, txt, FFMIN(परिमाण(txt) - 1, अवकाशः));
                av_bprint_grow(buf, अवकाशः); /* force truncation */
            }
            प्रत्यागम;
        }
    }
    av_bprint_grow(buf, l);
}

शून्य av_bprint_get_बफर(AVBPrint *buf, अचिह्नित आकार,
                          अचिह्नित वर्ण **mem, अचिह्नित *actual_आकार)
{
    यदि (आकार > av_bprint_अवकाशः(buf))
        av_bprint_alloc(buf, आकार);
    *actual_आकार = av_bprint_अवकाशः(buf);
    *mem = *actual_आकार ? (अचिह्नित वर्ण *) (buf->str + buf->len) : रिक्त;
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
    अचिह्नित real_आकार = FFMIN(buf->len + 1, buf->आकार);
    वर्ण *str;
    पूर्णाङ्क ret = 0;

    यदि (ret_str) {
        यदि (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_आकार);
            यदि (!str)
                str = buf->str;
            buf->str = रिक्त;
        } अन्यथा {
            str = av_memdup(buf->str, real_आकार);
            यदि (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } अन्यथा {
        यदि (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->आकार = real_आकार;
    प्रत्यागम ret;
}

#परिभाषय WHITESPACES " \n\t\r"

शून्य av_bprint_escape(AVBPrint *dstbuf, ध्रुव वर्ण *src, ध्रुव वर्ण *special_chars,
                      गणना AVEscape_बहुलकम् बहुलकम्, पूर्णाङ्क flags)
{
    ध्रुव वर्ण *src0 = src;

    यदि (बहुलकम् == AV_ESCAPE_बहुलकम्_AUTO)
        बहुलकम् = AV_ESCAPE_बहुलकम्_BACKSLASH; /* TODO: implement a heuristic */

    विकल्प (बहुलकम्) {
    पक्ष AV_ESCAPE_बहुलकम्_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        प्रति (; *src; src++) {
            यदि (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            अन्यथा
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        भङ्ग;

    पक्ष AV_ESCAPE_बहुलकम्_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        प्रति (; *src; src++) {
            विकल्प (*src) {
            पक्ष '&' : av_bprintf(dstbuf, "%s", "&amp;");  भङ्ग;
            पक्ष '<' : av_bprintf(dstbuf, "%s", "&lt;");   भङ्ग;
            पक्ष '>' : av_bprintf(dstbuf, "%s", "&gt;");   भङ्ग;
            पक्ष '\'':
                यदि (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    गच्छ XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                भङ्ग;
            पक्ष '"' :
                यदि (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
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
        प्रति (; *src; src++) {
            पूर्णाङ्क is_first_चरमः       = src == src0 || !*(src+1);
            पूर्णाङ्क is_ws               = !!strchr(WHITESPACES, *src);
            पूर्णाङ्क is_strictly_special = special_chars && strchr(special_chars, *src);
            पूर्णाङ्क is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            यदि (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_first_चरमः))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        भङ्ग;
    }
}
