/*
 * Copyright (c) 2000, 2001, 2002 Fabrice Bellard
 * Copyright (c) 2007 Mans Rullgard
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

#ضمن <limits.h>
#ضمن <stdarg.h>
#ضمن <stdint.h>
#ضمن <stdio.h>
#ضمن <string.h>

#ضمن "config.h"
#ضمن "mem.h"
#ضمن "avassert.h"
#ضمن "avstring.h"
#ضمن "bprint.h"
#ضمن "error.h"
#ضمن "macros.h"

صحيح av_strstart(ثابت حرف *str, ثابت حرف *pfx, ثابت حرف **ptr)
{
    طالما (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    إذا (!*pfx && ptr)
        *ptr = str;
    أرجع !*pfx;
}

صحيح av_stristart(ثابت حرف *str, ثابت حرف *pfx, ثابت حرف **ptr)
{
    طالما (*pfx && av_toupper((بنانشان)*pfx) == av_toupper((بنانشان)*str)) {
        pfx++;
        str++;
    }
    إذا (!*pfx && ptr)
        *ptr = str;
    أرجع !*pfx;
}

حرف *av_stristr(ثابت حرف *s1, ثابت حرف *s2)
{
    إذا (!*s2)
        أرجع (حرف*)(intptr_t)s1;

    افعل
        إذا (av_stristart(s1, s2, عدم))
            أرجع (حرف*)(intptr_t)s1;
    طالما (*s1++);

    أرجع عدم;
}

حرف *av_strnstr(ثابت حرف *haystack, ثابت حرف *needle, size_t hay_ڊيگهائي)
{
    size_t needle_len = لڙي_ڊيگهه(needle);
    إذا (!needle_len)
        أرجع (حرف*)haystack;
    طالما (hay_ڊيگهائي >= needle_len) {
        hay_ڊيگهائي--;
        إذا (!memcmp(haystack, needle, needle_len))
            أرجع (حرف*)haystack;
        haystack++;
    }
    أرجع عدم;
}

size_t av_strlcpy(حرف *dst, ثابت حرف *src, size_t سائيز)
{
    size_t len = 0;
    طالما (++len < سائيز && *src)
        *dst++ = *src++;
    إذا (len <= سائيز)
        *dst = 0;
    أرجع len + لڙي_ڊيگهه(src) - 1;
}

size_t av_strlcat(حرف *dst, ثابت حرف *src, size_t سائيز)
{
    size_t len = لڙي_ڊيگهه(dst);
    إذا (سائيز <= len + 1)
        أرجع len + لڙي_ڊيگهه(src);
    أرجع len + av_strlcpy(dst + len, src, سائيز - len);
}

size_t av_strlcatf(حرف *dst, size_t سائيز, ثابت حرف *fmt, ...)
{
    size_t len = لڙي_ڊيگهه(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, سائيز > len ? سائيز - len : 0, fmt, vl);
    va_end(vl);

    أرجع len;
}

حرف *av_asprintf(ثابت حرف *fmt, ...)
{
    حرف *p = عدم;
    va_list va;
    صحيح len;

    va_start(va, fmt);
    len = vsnprintf(عدم, 0, fmt, va);
    va_end(va);
    إذا (len < 0)
        اذهب پڇاڙي;

    p = av_malloc(len + 1);
    إذا (!p)
        اذهب پڇاڙي;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    إذا (len < 0)
        av_freep(&p);

پڇاڙي:
    أرجع p;
}

#وصف_ڪريو WHITESPACES " \n\t\r"

حرف *av_get_token(ثابت حرف **buf, ثابت حرف *رڪن)
{
    حرف *ٻاهريون     = av_realloc(عدم, لڙي_ڊيگهه(*buf) + 1);
    حرف *ret     = ٻاهريون, *پڇاڙي = ٻاهريون;
    ثابت حرف *p = *buf;
    إذا (!ٻاهريون)
        أرجع عدم;
    p += strspn(p, WHITESPACES);

    طالما (*p && !strspn(p, رڪن)) {
        حرف c = *p++;
        إذا (c == '\\' && *p) {
            *ٻاهريون++ = *p++;
            پڇاڙي    = ٻاهريون;
        } وإلا إذا (c == '\'') {
            طالما (*p && *p != '\'')
                *ٻاهريون++ = *p++;
            إذا (*p) {
                p++;
                پڇاڙي = ٻاهريون;
            }
        } وإلا {
            *ٻاهريون++ = c;
        }
    }

    افعل
        *ٻاهريون-- = 0;
    طالما (ٻاهريون >= پڇاڙي && strspn(ٻاهريون, WHITESPACES));

    *buf = p;

    حرف *small_ret = av_realloc(ret, ٻاهريون - ret + 2);
    أرجع small_ret ? small_ret : ret;
}

حرف *av_strtok(حرف *s, ثابت حرف *delim, حرف **saveptr)
{
    حرف *tok;

    إذا (!s && !(s = *saveptr))
        أرجع عدم;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    إذا (!*s) {
        *saveptr = عدم;
        أرجع عدم;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    إذا (*s) {
        *s = 0;
        *saveptr = s+1;
    } وإلا {
        *saveptr = عدم;
    }

    أرجع tok;
}

صحيح av_strcasecmp(ثابت حرف *a, ثابت حرف *b)
{
    uint8_t c1, c2;
    افعل {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } طالما (c1 && c1 == c2);
    أرجع c1 - c2;
}

صحيح av_strncasecmp(ثابت حرف *a, ثابت حرف *b, size_t n)
{
    uint8_t c1, c2;
    إذا (n <= 0)
        أرجع 0;
    افعل {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } طالما (--n && c1 && c1 == c2);
    أرجع c1 - c2;
}

حرف *av_strireplace(ثابت حرف *str, ثابت حرف *from, ثابت حرف *منزل)
{
    حرف *ret = عدم;
    ثابت حرف *pstr2, *pstr = str;
    size_t tolen = لڙي_ڊيگهه(منزل), fromlen = لڙي_ڊيگهه(from);
    AVBPrint pbuf;

    إذا (!fromlen)
        أرجع av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_سائيز_UNLIMITED);
    طالما ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_معلومات(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_معلومات(&pbuf, منزل, tolen);
    }
    av_bprint_append_معلومات(&pbuf, pstr, لڙي_ڊيگهه(pstr));
    إذا (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, عدم);
    } وإلا {
        av_bprint_finalize(&pbuf, &ret);
    }

    أرجع ret;
}

ثابت حرف *av_basename(ثابت حرف *رستو)
{
    إذا (!رستو || *رستو == '\0')
        أرجع ".";

    ثابت حرف *p = strrchr(رستو, '/');
#إذا HAVE_DOS_PATHS
    ثابت حرف *q = strrchr(رستو, '\\');
    ثابت حرف *d = strchr(رستو, ':');
    p = FFMAX3(p, q, d);
#جيڪڏهن_پورو

    إذا (!p)
        أرجع رستو;

    أرجع p + 1;
}

ثابت حرف *av_dirname(حرف *رستو)
{
    حرف *p = رستو ? strrchr(رستو, '/') : عدم;

#إذا HAVE_DOS_PATHS
    حرف *q = رستو ? strrchr(رستو, '\\') : عدم;
    حرف *d = رستو ? strchr(رستو, ':')  : عدم;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#جيڪڏهن_پورو

    إذا (!p)
        أرجع ".";

    *p = '\0';

    أرجع رستو;
}

حرف *av_append_رستو_component(ثابت حرف *رستو, ثابت حرف *component)
{
    size_t p_len, c_len;
    حرف *fullpath;

    إذا (!رستو)
        أرجع av_strdup(component);
    إذا (!component)
        أرجع av_strdup(رستو);

    p_len = لڙي_ڊيگهه(رستو);
    c_len = لڙي_ڊيگهه(component);
    إذا (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        أرجع عدم;
    fullpath = av_malloc(p_len + c_len + 2);
    إذا (fullpath) {
        إذا (p_len) {
            av_strlcpy(fullpath, رستو, p_len + 1);
            إذا (c_len) {
                إذا (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                وإلا إذا (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    أرجع fullpath;
}

صحيح av_escape(حرف **dst, ثابت حرف *src, ثابت حرف *special_chars,
              تعداد AVEscape_گهڻائي گهڻائي, صحيح flags)
{
    AVBPrint dstbuf;
    صحيح ret;

    av_bprint_init(&dstbuf, 1, وڌ_کان_وڌ_عدد); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, گهڻائي, flags);

    إذا (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, عدم);
        أرجع AVERROR(ENOMEM);
    }
    إذا ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        أرجع ret;
    أرجع dstbuf.len;
}

صحيح av_ميلاپ_name(ثابت حرف *name, ثابت حرف *نالا)
{
    ثابت حرف *p;
    size_t len, namelen;

    إذا (!name || !نالا)
        أرجع 0;

    namelen = لڙي_ڊيگهه(name);
    طالما (*نالا) {
        صحيح negate = '-' == *نالا;
        p = strchr(نالا, ',');
        إذا (!p)
            p = نالا + لڙي_ڊيگهه(نالا);
        نالا += negate;
        len = FFMAX(p - نالا, namelen);
        إذا (!av_strncasecmp(name, نالا, len) || !لڙي_ڀيٽ("ALL", نالا, FFMAX(3, p - نالا)))
            أرجع !negate;
        نالا = p + (*p == ',');
    }
    أرجع 0;
}

صحيح av_utf8_decode(int32_t *codep, ثابت uint8_t **bufp, ثابت uint8_t *buf_پڇاڙي,
                   بنانشان صحيح flags)
{
    ثابت uint8_t *p = *bufp;
    uint32_t چوٽي;
    uint64_t ڪوڊ;
    صحيح ret = 0, پڇ_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    إذا (p >= buf_پڇاڙي)
        أرجع 0;

    ڪوڊ = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    إذا ((ڪوڊ & 0xc0) == 0x80 || ڪوڊ >= 0xFE) {
        ret = AVERROR(EILSEQ);
        اذهب پڇاڙي;
    }
    چوٽي = (ڪوڊ & 128) >> 1;

    پڇ_len = 0;
    طالما (ڪوڊ & چوٽي) {
        صحيح tmp;
        پڇ_len++;
        إذا (p >= buf_پڇاڙي) {
            (*bufp) ++;
            أرجع AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        إذا (tmp>>6) {
            (*bufp) ++;
            أرجع AVERROR(EILSEQ);
        }
        ڪوڊ = (ڪوڊ<<6) + tmp;
        چوٽي <<= 5;
    }
    ڪوڊ &= (چوٽي << 1) - 1;

    /* check for overlong encodings */
    av_assert0(پڇ_len <= 5);
    إذا (ڪوڊ < overlong_encoding_mins[پڇ_len]) {
        ret = AVERROR(EILSEQ);
        اذهب پڇاڙي;
    }

    إذا (ڪوڊ >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        اذهب پڇاڙي;
    }

    *codep = ڪوڊ;

    إذا (ڪوڊ > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    إذا (ڪوڊ < 0x20 && ڪوڊ != 0x9 && ڪوڊ != 0xA && ڪوڊ != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    إذا (ڪوڊ >= 0xD800 && ڪوڊ <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    إذا ((ڪوڊ == 0xFFFE || ڪوڊ == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

پڇاڙي:
    *bufp = p;
    أرجع ret;
}

صحيح av_ميلاپ_list(ثابت حرف *name, ثابت حرف *list, حرف separator)
{
    ثابت حرف *p, *q;

    لكل (p = name; p && *p; ) {
        لكل (q = list; q && *q; ) {
            صحيح k;
            لكل (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                إذا (k && (!p[k] || p[k] == separator))
                    أرجع 1;
            q = strchr(q, separator);
            إذا(q)
                q++;
        }
        p = strchr(p, separator);
        إذا (p)
            p++;
    }

    أرجع 0;
}
