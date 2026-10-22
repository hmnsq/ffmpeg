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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdarg.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <time.h>
#అన్తర్భావ "avstring.h"
#అన్తర్భావ "bprint.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"

#నిర్వచించు av_bprint_స్థలం(buf) ((buf)->కొలత - FFMIN((buf)->len, (buf)->కొలత))
#నిర్వచించు av_bprint_is_allocated(buf) ((buf)->str != (buf)->reserved_అంతర్గత_బఫరు)

స్థిర పూర్ణాంకం av_bprint_alloc(AVBPrint *buf, గుర్తులేని స్థలం)
{
    అక్షరం *old_str, *new_str;
    గుర్తులేని min_కొలత, new_కొలత;

    ఒకవేళ (buf->కొలత == buf->కొలత_max)
        తిరిగి AVERROR(EIO);
    ఒకవేళ (!av_bprint_is_complete(buf))
        తిరిగి AVERROR_INVALIDDATA; /* it is already truncated anyway */
    min_కొలత = buf->len + 1 + FFMIN(UINT_MAX - buf->len - 1, స్థలం);
    new_కొలత = buf->కొలత > buf->కొలత_max / 2 ? buf->కొలత_max : buf->కొలత * 2;
    ఒకవేళ (new_కొలత < min_కొలత)
        new_కొలత = FFMIN(buf->కొలత_max, min_కొలత);
    old_str = av_bprint_is_allocated(buf) ? buf->str : ఖాళీ;
    new_str = av_realloc(old_str, new_కొలత);
    ఒకవేళ (!new_str)
        తిరిగి AVERROR(ENOMEM);
    ఒకవేళ (!old_str)
        జ్ఞాపకం_నకలు(new_str, buf->str, buf->len + 1);
    buf->str  = new_str;
    buf->కొలత = new_కొలత;
    తిరిగి 0;
}

స్థిర శూన్య av_bprint_grow(AVBPrint *buf, గుర్తులేని extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    ఒకవేళ (buf->కొలత)
        buf->str[FFMIN(buf->len, buf->కొలత - 1)] = 0;
}

శూన్య av_bprint_init(AVBPrint *buf, గుర్తులేని కొలత_init, గుర్తులేని కొలత_max)
{
    గుర్తులేని కొలత_auto = (అక్షరం *)buf + పరిమాణం(*buf) -
                         buf->reserved_అంతర్గత_బఫరు;

    ఒకవేళ (కొలత_max == AV_BPRINT_కొలత_AUTOMATIC)
        కొలత_max = కొలత_auto;
    buf->str      = buf->reserved_అంతర్గత_బఫరు;
    buf->len      = 0;
    buf->కొలత     = FFMIN(కొలత_auto, కొలత_max);
    buf->కొలత_max = కొలత_max;
    *buf->str = 0;
    ఒకవేళ (కొలత_init > buf->కొలత)
        av_bprint_alloc(buf, కొలత_init - 1);
}

శూన్య av_bprint_init_for_బఫరు(AVBPrint *buf, అక్షరం *బఫరు, గుర్తులేని కొలత)
{
    ఒకవేళ (కొలత == 0) {
        av_bprint_init(buf, 0, AV_BPRINT_కొలత_లెక్క_ONLY);
        తిరిగి;
    }

    buf->str      = బఫరు;
    buf->len      = 0;
    buf->కొలత     = కొలత;
    buf->కొలత_max = కొలత;
    *buf->str = 0;
}

శూన్య av_vbprintf(AVBPrint *buf, స్థిరరాశి అక్షరం *fmt, va_list vl_arg)
{
    గుర్తులేని స్థలం;
    అక్షరం *dst;
    పూర్ణాంకం extra_len;
    va_list vl;

    అయితే (1) {
        స్థలం = av_bprint_స్థలం(buf);
        dst = స్థలం ? buf->str + buf->len : ఖాళీ;
        va_copy(vl, vl_arg);
        extra_len = vsnprintf(dst, స్థలం, fmt, vl);
        va_end(vl);
        ఒకవేళ (extra_len <= 0)
            తిరిగి;
        ఒకవేళ (extra_len < స్థలం)
            ఆపు;
        ఒకవేళ (av_bprint_alloc(buf, extra_len))
            ఆపు;
    }
    av_bprint_grow(buf, extra_len);
}

శూన్య av_bprintf(AVBPrint *buf, స్థిరరాశి అక్షరం *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    av_vbprintf(buf, fmt, vl);
    va_end(vl);
}

శూన్య av_bprint_chars(AVBPrint *buf, అక్షరం c, గుర్తులేని n)
{
    గుర్తులేని స్థలం, real_n;

    అయితే (1) {
        స్థలం = av_bprint_స్థలం(buf);
        ఒకవేళ (n < స్థలం)
            ఆపు;
        ఒకవేళ (av_bprint_alloc(buf, n))
            ఆపు;
    }
    ఒకవేళ (స్థలం) {
        real_n = FFMIN(n, స్థలం - 1);
        memset(buf->str + buf->len, c, real_n);
    }
    av_bprint_grow(buf, n);
}

శూన్య av_bprint_append_దత్తాంశం(AVBPrint *buf, స్థిరరాశి అక్షరం *దత్తాంశం, గుర్తులేని కొలత)
{
    గుర్తులేని స్థలం, real_n;

    అయితే (1) {
        స్థలం = av_bprint_స్థలం(buf);
        ఒకవేళ (కొలత < స్థలం)
            ఆపు;
        ఒకవేళ (av_bprint_alloc(buf, కొలత))
            ఆపు;
    }
    ఒకవేళ (స్థలం) {
        real_n = FFMIN(కొలత, స్థలం - 1);
        జ్ఞాపకం_నకలు(buf->str + buf->len, దత్తాంశం, real_n);
    }
    av_bprint_grow(buf, కొలత);
}

శూన్య av_bprint_strftime(AVBPrint *buf, స్థిరరాశి అక్షరం *fmt, స్థిరరాశి నిర్మాణం tm *tm)
{
    గుర్తులేని స్థలం;
    size_t l;
    size_t fmt_len = అక్షరశ్రేణి_పొడవు(fmt);

    ఒకవేళ (!*fmt)
        తిరిగి;
    అయితే (1) {
        స్థలం = av_bprint_స్థలం(buf);
        ఒకవేళ (స్థలం && (l = strftime(buf->str + buf->len, స్థలం, fmt, tm)))
            ఆపు;

        /* Due to the limitations of strftime() it is not possible to know if
         * the output buffer is too small or the output is empty.
         * However, a 256x output space requirement compared to the format
         * string length is so unlikely we can safely assume empty output. This
         * allows supporting possibly empty format strings like "%p". */
        ఒకవేళ (స్థలం >> 8 > fmt_len)
            ఆపు;

        /* strftime does not tell us how much room it would need: let us
           retry with twice as much until the buffer is large enough */
        స్థలం = !స్థలం ? fmt_len + 1 :
               స్థలం <= గరిష్ఠ_పూర్ణాంకం / 2 ? స్థలం * 2 : గరిష్ఠ_పూర్ణాంకం;
        ఒకవేళ (av_bprint_alloc(buf, స్థలం)) {
            /* impossible to grow, try to manage something useful anyway */
            స్థలం = av_bprint_స్థలం(buf);
            ఒకవేళ (స్థలం < 1024) {
                /* if strftime fails because the buffer has (almost) reached
                   its maximum size, let us try in a local buffer; 1k should
                   be enough to format any real date+time string */
                అక్షరం buf2[1024];
                ఒకవేళ ((l = strftime(buf2, పరిమాణం(buf2), fmt, tm))) {
                    av_bprintf(buf, "%s", buf2);
                    తిరిగి;
                }
            }
            ఒకవేళ (స్థలం) {
                /* if anything else failed and the buffer is not already
                   truncated, let us add a stock string and force truncation */
                స్థిర స్థిరరాశి అక్షరం txt[] = "[truncated strftime output]";
                memset(buf->str + buf->len, '!', స్థలం);
                జ్ఞాపకం_నకలు(buf->str + buf->len, txt, FFMIN(పరిమాణం(txt) - 1, స్థలం));
                av_bprint_grow(buf, స్థలం); /* force truncation */
            }
            తిరిగి;
        }
    }
    av_bprint_grow(buf, l);
}

శూన్య av_bprint_get_బఫరు(AVBPrint *buf, గుర్తులేని కొలత,
                          గుర్తులేని అక్షరం **mem, గుర్తులేని *actual_కొలత)
{
    ఒకవేళ (కొలత > av_bprint_స్థలం(buf))
        av_bprint_alloc(buf, కొలత);
    *actual_కొలత = av_bprint_స్థలం(buf);
    *mem = *actual_కొలత ? (గుర్తులేని అక్షరం *) (buf->str + buf->len) : ఖాళీ;
}

శూన్య av_bprint_clear(AVBPrint *buf)
{
    ఒకవేళ (buf->len) {
        *buf->str = 0;
        buf->len  = 0;
    }
}

పూర్ణాంకం av_bprint_finalize(AVBPrint *buf, అక్షరం **ret_str)
{
    గుర్తులేని real_కొలత = FFMIN(buf->len + 1, buf->కొలత);
    అక్షరం *str;
    పూర్ణాంకం ret = 0;

    ఒకవేళ (ret_str) {
        ఒకవేళ (av_bprint_is_allocated(buf)) {
            str = av_realloc(buf->str, real_కొలత);
            ఒకవేళ (!str)
                str = buf->str;
            buf->str = ఖాళీ;
        } లేకపోతే {
            str = av_memdup(buf->str, real_కొలత);
            ఒకవేళ (!str)
                ret = AVERROR(ENOMEM);
        }
        *ret_str = str;
    } లేకపోతే {
        ఒకవేళ (av_bprint_is_allocated(buf))
            av_freep(&buf->str);
    }
    buf->కొలత = real_కొలత;
    తిరిగి ret;
}

#నిర్వచించు WHITESPACES " \n\t\r"

శూన్య av_bprint_escape(AVBPrint *dstbuf, స్థిరరాశి అక్షరం *src, స్థిరరాశి అక్షరం *special_chars,
                      గణన AVEscape_బహుళకం బహుళకం, పూర్ణాంకం flags)
{
    స్థిరరాశి అక్షరం *src0 = src;

    ఒకవేళ (బహుళకం == AV_ESCAPE_బహుళకం_AUTO)
        బహుళకం = AV_ESCAPE_బహుళకం_BACKSLASH; /* TODO: implement a heuristic */

    ఎంపిక (బహుళకం) {
    స్థితి AV_ESCAPE_బహుళకం_QUOTE:
        /* enclose the string between '' */
        av_bprint_chars(dstbuf, '\'', 1);
        కొరకు (; *src; src++) {
            ఒకవేళ (*src == '\'')
                av_bprintf(dstbuf, "'\\''");
            లేకపోతే
                av_bprint_chars(dstbuf, *src, 1);
        }
        av_bprint_chars(dstbuf, '\'', 1);
        ఆపు;

    స్థితి AV_ESCAPE_బహుళకం_XML:
        /* escape XML non-markup character data as per 2.4 by default: */
        /*  [^<&]* - ([^<&]* ']]>' [^<&]*) */

        /* additionally, given one of the AV_ESCAPE_FLAG_XML_* flags, */
        /* escape those specific characters as required. */
        కొరకు (; *src; src++) {
            ఎంపిక (*src) {
            స్థితి '&' : av_bprintf(dstbuf, "%s", "&amp;");  ఆపు;
            స్థితి '<' : av_bprintf(dstbuf, "%s", "&lt;");   ఆపు;
            స్థితి '>' : av_bprintf(dstbuf, "%s", "&gt;");   ఆపు;
            స్థితి '\'':
                ఒకవేళ (!(flags & AV_ESCAPE_FLAG_XML_SINGLE_QUOTES))
                    వెళ్ళు XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&apos;");
                ఆపు;
            స్థితి '"' :
                ఒకవేళ (!(flags & AV_ESCAPE_FLAG_XML_DOUBLE_QUOTES))
                    వెళ్ళు XML_DEFAULT_HANDLING;

                av_bprintf(dstbuf, "%s", "&quot;");
                ఆపు;
XML_DEFAULT_HANDLING:
            అప్రమేయ: av_bprint_chars(dstbuf, *src, 1);
            }
        }
        ఆపు;

    /* case AV_ESCAPE_MODE_BACKSLASH or unknown mode */
    అప్రమేయ:
        /* \-escape characters */
        కొరకు (; *src; src++) {
            పూర్ణాంకం is_మొదటి_చివరి       = src == src0 || !*(src+1);
            పూర్ణాంకం is_ws               = !!strchr(WHITESPACES, *src);
            పూర్ణాంకం is_strictly_special = special_chars && strchr(special_chars, *src);
            పూర్ణాంకం is_special          =
                is_strictly_special || strchr("'\\", *src) ||
                (is_ws && (flags & AV_ESCAPE_FLAG_WHITESPACE));

            ఒకవేళ (is_strictly_special ||
                (!(flags & AV_ESCAPE_FLAG_STRICT) &&
                 (is_special || (is_ws && is_మొదటి_చివరి))))
                av_bprint_chars(dstbuf, '\\', 1);
            av_bprint_chars(dstbuf, *src, 1);
        }
        ఆపు;
    }
}
