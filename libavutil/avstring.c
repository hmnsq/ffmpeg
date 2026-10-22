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
    طالما (*pfx && av_toupper((بنانشانی)*pfx) == av_toupper((بنانشانی)*str)) {
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

حرف *av_strnstr(ثابت حرف *haystack, ثابت حرف *needle, size_t hay_لمائی)
{
    size_t needle_len = لڑی_لمبائی(needle);
    إذا (!needle_len)
        أرجع (حرف*)haystack;
    طالما (hay_لمائی >= needle_len) {
        hay_لمائی--;
        إذا (!memcmp(haystack, needle, needle_len))
            أرجع (حرف*)haystack;
        haystack++;
    }
    أرجع عدم;
}

size_t av_strlcpy(حرف *dst, ثابت حرف *src, size_t ناپ)
{
    size_t len = 0;
    طالما (++len < ناپ && *src)
        *dst++ = *src++;
    إذا (len <= ناپ)
        *dst = 0;
    أرجع len + لڑی_لمبائی(src) - 1;
}

size_t av_strlcat(حرف *dst, ثابت حرف *src, size_t ناپ)
{
    size_t len = لڑی_لمبائی(dst);
    إذا (ناپ <= len + 1)
        أرجع len + لڑی_لمبائی(src);
    أرجع len + av_strlcpy(dst + len, src, ناپ - len);
}

size_t av_strlcatf(حرف *dst, size_t ناپ, ثابت حرف *fmt, ...)
{
    size_t len = لڑی_لمبائی(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, ناپ > len ? ناپ - len : 0, fmt, vl);
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
        اذهب سرا;

    p = av_malloc(len + 1);
    إذا (!p)
        اذهب سرا;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    إذا (len < 0)
        av_freep(&p);

سرا:
    أرجع p;
}

#تعریف_کرو WHITESPACES " \n\t\r"

حرف *av_get_token(ثابت حرف **buf, ثابت حرف *رکن)
{
    حرف *باہرلا     = av_realloc(عدم, لڑی_لمبائی(*buf) + 1);
    حرف *ret     = باہرلا, *سرا = باہرلا;
    ثابت حرف *p = *buf;
    إذا (!باہرلا)
        أرجع عدم;
    p += strspn(p, WHITESPACES);

    طالما (*p && !strspn(p, رکن)) {
        حرف c = *p++;
        إذا (c == '\\' && *p) {
            *باہرلا++ = *p++;
            سرا    = باہرلا;
        } وإلا إذا (c == '\'') {
            طالما (*p && *p != '\'')
                *باہرلا++ = *p++;
            إذا (*p) {
                p++;
                سرا = باہرلا;
            }
        } وإلا {
            *باہرلا++ = c;
        }
    }

    افعل
        *باہرلا-- = 0;
    طالما (باہرلا >= سرا && strspn(باہرلا, WHITESPACES));

    *buf = p;

    حرف *small_ret = av_realloc(ret, باہرلا - ret + 2);
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
    size_t tolen = لڑی_لمبائی(منزل), fromlen = لڑی_لمبائی(from);
    AVBPrint pbuf;

    إذا (!fromlen)
        أرجع av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_ناپ_UNLIMITED);
    طالما ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_انکڑے(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_انکڑے(&pbuf, منزل, tolen);
    }
    av_bprint_append_انکڑے(&pbuf, pstr, لڑی_لمبائی(pstr));
    إذا (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, عدم);
    } وإلا {
        av_bprint_finalize(&pbuf, &ret);
    }

    أرجع ret;
}

ثابت حرف *av_basename(ثابت حرف *رستہ)
{
    إذا (!رستہ || *رستہ == '\0')
        أرجع ".";

    ثابت حرف *p = strrchr(رستہ, '/');
#إذا HAVE_DOS_PATHS
    ثابت حرف *q = strrchr(رستہ, '\\');
    ثابت حرف *d = strchr(رستہ, ':');
    p = FFMAX3(p, q, d);
#جے_انت

    إذا (!p)
        أرجع رستہ;

    أرجع p + 1;
}

ثابت حرف *av_dirname(حرف *رستہ)
{
    حرف *p = رستہ ? strrchr(رستہ, '/') : عدم;

#إذا HAVE_DOS_PATHS
    حرف *q = رستہ ? strrchr(رستہ, '\\') : عدم;
    حرف *d = رستہ ? strchr(رستہ, ':')  : عدم;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#جے_انت

    إذا (!p)
        أرجع ".";

    *p = '\0';

    أرجع رستہ;
}

حرف *av_append_رستہ_component(ثابت حرف *رستہ, ثابت حرف *component)
{
    size_t p_len, c_len;
    حرف *fullpath;

    إذا (!رستہ)
        أرجع av_strdup(component);
    إذا (!component)
        أرجع av_strdup(رستہ);

    p_len = لڑی_لمبائی(رستہ);
    c_len = لڑی_لمبائی(component);
    إذا (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        أرجع عدم;
    fullpath = av_malloc(p_len + c_len + 2);
    إذا (fullpath) {
        إذا (p_len) {
            av_strlcpy(fullpath, رستہ, p_len + 1);
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
              تعداد AVEscape_منوال منوال, صحيح flags)
{
    AVBPrint dstbuf;
    صحيح ret;

    av_bprint_init(&dstbuf, 1, ودھ_توں_ودھ_عدد); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, منوال, flags);

    إذا (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, عدم);
        أرجع AVERROR(ENOMEM);
    }
    إذا ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        أرجع ret;
    أرجع dstbuf.len;
}

صحيح av_میل_name(ثابت حرف *name, ثابت حرف *ناں)
{
    ثابت حرف *p;
    size_t len, namelen;

    إذا (!name || !ناں)
        أرجع 0;

    namelen = لڑی_لمبائی(name);
    طالما (*ناں) {
        صحيح negate = '-' == *ناں;
        p = strchr(ناں, ',');
        إذا (!p)
            p = ناں + لڑی_لمبائی(ناں);
        ناں += negate;
        len = FFMAX(p - ناں, namelen);
        إذا (!av_strncasecmp(name, ناں, len) || !لڑی_مقابلہ("ALL", ناں, FFMAX(3, p - ناں)))
            أرجع !negate;
        ناں = p + (*p == ',');
    }
    أرجع 0;
}

صحيح av_utf8_decode(int32_t *codep, ثابت uint8_t **bufp, ثابت uint8_t *buf_سرا,
                   بنانشانی صحيح flags)
{
    ثابت uint8_t *p = *bufp;
    uint32_t چوٹی;
    uint64_t کوڈ;
    صحيح ret = 0, پوچھ_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    إذا (p >= buf_سرا)
        أرجع 0;

    کوڈ = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    إذا ((کوڈ & 0xc0) == 0x80 || کوڈ >= 0xFE) {
        ret = AVERROR(EILSEQ);
        اذهب سرا;
    }
    چوٹی = (کوڈ & 128) >> 1;

    پوچھ_len = 0;
    طالما (کوڈ & چوٹی) {
        صحيح tmp;
        پوچھ_len++;
        إذا (p >= buf_سرا) {
            (*bufp) ++;
            أرجع AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        إذا (tmp>>6) {
            (*bufp) ++;
            أرجع AVERROR(EILSEQ);
        }
        کوڈ = (کوڈ<<6) + tmp;
        چوٹی <<= 5;
    }
    کوڈ &= (چوٹی << 1) - 1;

    /* check for overlong encodings */
    av_assert0(پوچھ_len <= 5);
    إذا (کوڈ < overlong_encoding_mins[پوچھ_len]) {
        ret = AVERROR(EILSEQ);
        اذهب سرا;
    }

    إذا (کوڈ >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        اذهب سرا;
    }

    *codep = کوڈ;

    إذا (کوڈ > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    إذا (کوڈ < 0x20 && کوڈ != 0x9 && کوڈ != 0xA && کوڈ != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    إذا (کوڈ >= 0xD800 && کوڈ <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    إذا ((کوڈ == 0xFFFE || کوڈ == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

سرا:
    *bufp = p;
    أرجع ret;
}

صحيح av_میل_list(ثابت حرف *name, ثابت حرف *list, حرف separator)
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
