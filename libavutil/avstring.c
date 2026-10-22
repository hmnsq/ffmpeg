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

số_nguyên av_strstart(const char *str, const char *pfx, const char **ptr)
{
    trong_khi (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    nếu (!*pfx && ptr)
        *ptr = str;
    trả_về !*pfx;
}

số_nguyên av_stristart(const char *str, const char *pfx, const char **ptr)
{
    trong_khi (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    nếu (!*pfx && ptr)
        *ptr = str;
    trả_về !*pfx;
}

char *av_stristr(const char *s1, const char *s2)
{
    nếu (!*s2)
        trả_về (char*)(intptr_t)s1;

    do
        nếu (av_stristart(s1, s2, NULL))
            trả_về (char*)(intptr_t)s1;
    trong_khi (*s1++);

    trả_về NULL;
}

char *av_strnstr(const char *haystack, const char *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    nếu (!needle_len)
        trả_về (char*)haystack;
    trong_khi (hay_length >= needle_len) {
        hay_length--;
        nếu (!memcmp(haystack, needle, needle_len))
            trả_về (char*)haystack;
        haystack++;
    }
    trả_về NULL;
}

size_t av_strlcpy(char *dst, const char *src, size_t size)
{
    size_t len = 0;
    trong_khi (++len < size && *src)
        *dst++ = *src++;
    nếu (len <= size)
        *dst = 0;
    trả_về len + strlen(src) - 1;
}

size_t av_strlcat(char *dst, const char *src, size_t size)
{
    size_t len = strlen(dst);
    nếu (size <= len + 1)
        trả_về len + strlen(src);
    trả_về len + av_strlcpy(dst + len, src, size - len);
}

size_t av_strlcatf(char *dst, size_t size, const char *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    va_end(vl);

    trả_về len;
}

char *av_asprintf(const char *fmt, ...)
{
    char *p = NULL;
    va_list va;
    số_nguyên len;

    va_start(va, fmt);
    len = vsnprintf(NULL, 0, fmt, va);
    va_end(va);
    nếu (len < 0)
        goto end;

    p = av_malloc(len + 1);
    nếu (!p)
        goto end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    nếu (len < 0)
        av_freep(&p);

end:
    trả_về p;
}

#define WHITESPACES " \n\t\r"

char *av_get_token(const char **buf, const char *term)
{
    char *out     = av_realloc(NULL, strlen(*buf) + 1);
    char *ret     = out, *end = out;
    const char *p = *buf;
    nếu (!out)
        trả_về NULL;
    p += strspn(p, WHITESPACES);

    trong_khi (*p && !strspn(p, term)) {
        char c = *p++;
        nếu (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } không_thì nếu (c == '\'') {
            trong_khi (*p && *p != '\'')
                *out++ = *p++;
            nếu (*p) {
                p++;
                end = out;
            }
        } không_thì {
            *out++ = c;
        }
    }

    do
        *out-- = 0;
    trong_khi (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    char *small_ret = av_realloc(ret, out - ret + 2);
    trả_về small_ret ? small_ret : ret;
}

char *av_strtok(char *s, const char *delim, char **saveptr)
{
    char *tok;

    nếu (!s && !(s = *saveptr))
        trả_về NULL;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    nếu (!*s) {
        *saveptr = NULL;
        trả_về NULL;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    nếu (*s) {
        *s = 0;
        *saveptr = s+1;
    } không_thì {
        *saveptr = NULL;
    }

    trả_về tok;
}

số_nguyên av_strcasecmp(const char *a, const char *b)
{
    uint8_t c1, c2;
    do {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } trong_khi (c1 && c1 == c2);
    trả_về c1 - c2;
}

số_nguyên av_strncasecmp(const char *a, const char *b, size_t n)
{
    uint8_t c1, c2;
    nếu (n <= 0)
        trả_về 0;
    do {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } trong_khi (--n && c1 && c1 == c2);
    trả_về c1 - c2;
}

char *av_strireplace(const char *str, const char *from, const char *to)
{
    char *ret = NULL;
    const char *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    nếu (!fromlen)
        trả_về av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    trong_khi ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, strlen(pstr));
    nếu (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, NULL);
    } không_thì {
        av_bprint_finalize(&pbuf, &ret);
    }

    trả_về ret;
}

const char *av_basename(const char *path)
{
    nếu (!path || *path == '\0')
        trả_về ".";

    const char *p = strrchr(path, '/');
#nếu HAVE_DOS_PATHS
    const char *q = strrchr(path, '\\');
    const char *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    nếu (!p)
        trả_về path;

    trả_về p + 1;
}

const char *av_dirname(char *path)
{
    char *p = path ? strrchr(path, '/') : NULL;

#nếu HAVE_DOS_PATHS
    char *q = path ? strrchr(path, '\\') : NULL;
    char *d = path ? strchr(path, ':')  : NULL;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    nếu (!p)
        trả_về ".";

    *p = '\0';

    trả_về path;
}

char *av_append_path_component(const char *path, const char *component)
{
    size_t p_len, c_len;
    char *fullpath;

    nếu (!path)
        trả_về av_strdup(component);
    nếu (!component)
        trả_về av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    nếu (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        trả_về NULL;
    fullpath = av_malloc(p_len + c_len + 2);
    nếu (fullpath) {
        nếu (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            nếu (c_len) {
                nếu (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                không_thì nếu (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    trả_về fullpath;
}

số_nguyên av_escape(char **dst, const char *src, const char *special_chars,
              enum AVEscapeMode mode, số_nguyên flags)
{
    AVBPrint dstbuf;
    số_nguyên ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    nếu (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, NULL);
        trả_về AVERROR(ENOMEM);
    }
    nếu ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        trả_về ret;
    trả_về dstbuf.len;
}

số_nguyên av_match_name(const char *name, const char *names)
{
    const char *p;
    size_t len, namelen;

    nếu (!name || !names)
        trả_về 0;

    namelen = strlen(name);
    trong_khi (*names) {
        số_nguyên negate = '-' == *names;
        p = strchr(names, ',');
        nếu (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        nếu (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            trả_về !negate;
        names = p + (*p == ',');
    }
    trả_về 0;
}

số_nguyên av_utf8_decode(int32_t *codep, const uint8_t **bufp, const uint8_t *buf_end,
                   unsigned số_nguyên flags)
{
    const uint8_t *p = *bufp;
    uint32_t top;
    uint64_t code;
    số_nguyên ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    nếu (p >= buf_end)
        trả_về 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    nếu ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        goto end;
    }
    top = (code & 128) >> 1;

    tail_len = 0;
    trong_khi (code & top) {
        số_nguyên tmp;
        tail_len++;
        nếu (p >= buf_end) {
            (*bufp) ++;
            trả_về AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        nếu (tmp>>6) {
            (*bufp) ++;
            trả_về AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        top <<= 5;
    }
    code &= (top << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    nếu (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        goto end;
    }

    nếu (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        goto end;
    }

    *codep = code;

    nếu (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    nếu (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    nếu (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    nếu ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    trả_về ret;
}

số_nguyên av_match_list(const char *name, const char *list, char separator)
{
    const char *p, *q;

    cho (p = name; p && *p; ) {
        cho (q = list; q && *q; ) {
            số_nguyên k;
            cho (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                nếu (k && (!p[k] || p[k] == separator))
                    trả_về 1;
            q = strchr(q, separator);
            nếu(q)
                q++;
        }
        p = strchr(p, separator);
        nếu (p)
            p++;
    }

    trả_về 0;
}
