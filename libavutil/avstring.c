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

#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "mem.h"
#include "avassert.h"
#include "avstring.h"
#include "bprint.h"
#include "error.h"
#include "macros.h"

puur_naa_nka av_strstart(const var_na *str, const var_na *pfx, const var_na **ptr)
{
    ᯀᯬᯝ (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    ᯀᯮᯝ (!*pfx && ptr)
        *ptr = str;
    ᯀᯮᯞ !*pfx;
}

puur_naa_nka av_stristart(const var_na *str, const var_na *pfx, const var_na **ptr)
{
    ᯀᯬᯝ (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    ᯀᯮᯝ (!*pfx && ptr)
        *ptr = str;
    ᯀᯮᯞ !*pfx;
}

var_na *av_stristr(const var_na *s1, const var_na *s2)
{
    ᯀᯮᯝ (!*s2)
        ᯀᯮᯞ (var_na*)(intptr_t)s1;

    do
        ᯀᯮᯝ (av_stristart(s1, s2, NULL))
            ᯀᯮᯞ (var_na*)(intptr_t)s1;
    ᯀᯬᯝ (*s1++);

    ᯀᯮᯞ NULL;
}

var_na *av_strnstr(const var_na *haystack, const var_na *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    ᯀᯮᯝ (!needle_len)
        ᯀᯮᯞ (var_na*)haystack;
    ᯀᯬᯝ (hay_length >= needle_len) {
        hay_length--;
        ᯀᯮᯝ (!memcmp(haystack, needle, needle_len))
            ᯀᯮᯞ (var_na*)haystack;
        haystack++;
    }
    ᯀᯮᯞ NULL;
}

size_t av_strlcpy(var_na *dst, const var_na *src, size_t size)
{
    size_t len = 0;
    ᯀᯬᯝ (++len < size && *src)
        *dst++ = *src++;
    ᯀᯮᯝ (len <= size)
        *dst = 0;
    ᯀᯮᯞ len + strlen(src) - 1;
}

size_t av_strlcat(var_na *dst, const var_na *src, size_t size)
{
    size_t len = strlen(dst);
    ᯀᯮᯝ (size <= len + 1)
        ᯀᯮᯞ len + strlen(src);
    ᯀᯮᯞ len + av_strlcpy(dst + len, src, size - len);
}

size_t av_strlcatf(var_na *dst, size_t size, const var_na *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    va_end(vl);

    ᯀᯮᯞ len;
}

var_na *av_asprintf(const var_na *fmt, ...)
{
    var_na *p = NULL;
    va_list va;
    puur_naa_nka len;

    va_start(va, fmt);
    len = vsnprintf(NULL, 0, fmt, va);
    va_end(va);
    ᯀᯮᯝ (len < 0)
        goto end;

    p = av_malloc(len + 1);
    ᯀᯮᯝ (!p)
        goto end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    ᯀᯮᯝ (len < 0)
        av_freep(&p);

end:
    ᯀᯮᯞ p;
}

#define WHITESPACES " \n\t\r"

var_na *av_get_token(const var_na **buf, const var_na *term)
{
    var_na *out     = av_realloc(NULL, strlen(*buf) + 1);
    var_na *ret     = out, *end = out;
    const var_na *p = *buf;
    ᯀᯮᯝ (!out)
        ᯀᯮᯞ NULL;
    p += strspn(p, WHITESPACES);

    ᯀᯬᯝ (*p && !strspn(p, term)) {
        var_na c = *p++;
        ᯀᯮᯝ (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (c == '\'') {
            ᯀᯬᯝ (*p && *p != '\'')
                *out++ = *p++;
            ᯀᯮᯝ (*p) {
                p++;
                end = out;
            }
        } ᯀᯮᯝᯂᯪ {
            *out++ = c;
        }
    }

    do
        *out-- = 0;
    ᯀᯬᯝ (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    var_na *small_ret = av_realloc(ret, out - ret + 2);
    ᯀᯮᯞ small_ret ? small_ret : ret;
}

var_na *av_strtok(var_na *s, const var_na *delim, var_na **saveptr)
{
    var_na *tok;

    ᯀᯮᯝ (!s && !(s = *saveptr))
        ᯀᯮᯞ NULL;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    ᯀᯮᯝ (!*s) {
        *saveptr = NULL;
        ᯀᯮᯞ NULL;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    ᯀᯮᯝ (*s) {
        *s = 0;
        *saveptr = s+1;
    } ᯀᯮᯝᯂᯪ {
        *saveptr = NULL;
    }

    ᯀᯮᯞ tok;
}

puur_naa_nka av_strcasecmp(const var_na *a, const var_na *b)
{
    uint8_t c1, c2;
    do {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ᯀᯬᯝ (c1 && c1 == c2);
    ᯀᯮᯞ c1 - c2;
}

puur_naa_nka av_strncasecmp(const var_na *a, const var_na *b, size_t n)
{
    uint8_t c1, c2;
    ᯀᯮᯝ (n <= 0)
        ᯀᯮᯞ 0;
    do {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ᯀᯬᯝ (--n && c1 && c1 == c2);
    ᯀᯮᯞ c1 - c2;
}

var_na *av_strireplace(const var_na *str, const var_na *from, const var_na *to)
{
    var_na *ret = NULL;
    const var_na *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    ᯀᯮᯝ (!fromlen)
        ᯀᯮᯞ av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    ᯀᯬᯝ ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, strlen(pstr));
    ᯀᯮᯝ (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, NULL);
    } ᯀᯮᯝᯂᯪ {
        av_bprint_finalize(&pbuf, &ret);
    }

    ᯀᯮᯞ ret;
}

const var_na *av_basename(const var_na *path)
{
    ᯀᯮᯝ (!path || *path == '\0')
        ᯀᯮᯞ ".";

    const var_na *p = strrchr(path, '/');
#ᯀᯮᯝ HAVE_DOS_PATHS
    const var_na *q = strrchr(path, '\\');
    const var_na *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    ᯀᯮᯝ (!p)
        ᯀᯮᯞ path;

    ᯀᯮᯞ p + 1;
}

const var_na *av_dirname(var_na *path)
{
    var_na *p = path ? strrchr(path, '/') : NULL;

#ᯀᯮᯝ HAVE_DOS_PATHS
    var_na *q = path ? strrchr(path, '\\') : NULL;
    var_na *d = path ? strchr(path, ':')  : NULL;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    ᯀᯮᯝ (!p)
        ᯀᯮᯞ ".";

    *p = '\0';

    ᯀᯮᯞ path;
}

var_na *av_append_path_component(const var_na *path, const var_na *component)
{
    size_t p_len, c_len;
    var_na *fullpath;

    ᯀᯮᯝ (!path)
        ᯀᯮᯞ av_strdup(component);
    ᯀᯮᯝ (!component)
        ᯀᯮᯞ av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    ᯀᯮᯝ (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        ᯀᯮᯞ NULL;
    fullpath = av_malloc(p_len + c_len + 2);
    ᯀᯮᯝ (fullpath) {
        ᯀᯮᯝ (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            ᯀᯮᯝ (c_len) {
                ᯀᯮᯝ (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                ᯀᯮᯝᯂᯪ ᯀᯮᯝ (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    ᯀᯮᯞ fullpath;
}

puur_naa_nka av_escape(var_na **dst, const var_na *src, const var_na *special_chars,
              ga_nanaa AVEscapeMode mode, puur_naa_nka flags)
{
    AVBPrint dstbuf;
    puur_naa_nka ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    ᯀᯮᯝ (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, NULL);
        ᯀᯮᯞ AVERROR(ENOMEM);
    }
    ᯀᯮᯝ ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        ᯀᯮᯞ ret;
    ᯀᯮᯞ dstbuf.len;
}

puur_naa_nka av_match_name(const var_na *name, const var_na *names)
{
    const var_na *p;
    size_t len, namelen;

    ᯀᯮᯝ (!name || !names)
        ᯀᯮᯞ 0;

    namelen = strlen(name);
    ᯀᯬᯝ (*names) {
        puur_naa_nka negate = '-' == *names;
        p = strchr(names, ',');
        ᯀᯮᯝ (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        ᯀᯮᯝ (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            ᯀᯮᯞ !negate;
        names = p + (*p == ',');
    }
    ᯀᯮᯞ 0;
}

puur_naa_nka av_utf8_decode(int32_t *codep, const uint8_t **bufp, const uint8_t *buf_end,
                   unsigned puur_naa_nka flags)
{
    const uint8_t *p = *bufp;
    uint32_t top;
    uint64_t code;
    puur_naa_nka ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    ᯀᯮᯝ (p >= buf_end)
        ᯀᯮᯞ 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    ᯀᯮᯝ ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        goto end;
    }
    top = (code & 128) >> 1;

    tail_len = 0;
    ᯀᯬᯝ (code & top) {
        puur_naa_nka tmp;
        tail_len++;
        ᯀᯮᯝ (p >= buf_end) {
            (*bufp) ++;
            ᯀᯮᯞ AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        ᯀᯮᯝ (tmp>>6) {
            (*bufp) ++;
            ᯀᯮᯞ AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        top <<= 5;
    }
    code &= (top << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    ᯀᯮᯝ (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        goto end;
    }

    ᯀᯮᯝ (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        goto end;
    }

    *codep = code;

    ᯀᯮᯝ (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    ᯀᯮᯝ (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    ᯀᯮᯝ (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    ᯀᯮᯝ ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    ᯀᯮᯞ ret;
}

puur_naa_nka av_match_list(const var_na *name, const var_na *list, var_na separator)
{
    const var_na *p, *q;

    for (p = name; p && *p; ) {
        for (q = list; q && *q; ) {
            puur_naa_nka k;
            for (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                ᯀᯮᯝ (k && (!p[k] || p[k] == separator))
                    ᯀᯮᯞ 1;
            q = strchr(q, separator);
            ᯀᯮᯝ(q)
                q++;
        }
        p = strchr(p, separator);
        ᯀᯮᯝ (p)
            p++;
    }

    ᯀᯮᯞ 0;
}
