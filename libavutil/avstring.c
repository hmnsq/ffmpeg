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

整数 av_strstart(const char *str, const char *pfx, const char **ptr)
{
    当 (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    如果 (!*pfx && ptr)
        *ptr = str;
    返回 !*pfx;
}

整数 av_stristart(const char *str, const char *pfx, const char **ptr)
{
    当 (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    如果 (!*pfx && ptr)
        *ptr = str;
    返回 !*pfx;
}

char *av_stristr(const char *s1, const char *s2)
{
    如果 (!*s2)
        返回 (char*)(intptr_t)s1;

    do
        如果 (av_stristart(s1, s2, NULL))
            返回 (char*)(intptr_t)s1;
    当 (*s1++);

    返回 NULL;
}

char *av_strnstr(const char *haystack, const char *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    如果 (!needle_len)
        返回 (char*)haystack;
    当 (hay_length >= needle_len) {
        hay_length--;
        如果 (!memcmp(haystack, needle, needle_len))
            返回 (char*)haystack;
        haystack++;
    }
    返回 NULL;
}

size_t av_strlcpy(char *dst, const char *src, size_t size)
{
    size_t len = 0;
    当 (++len < size && *src)
        *dst++ = *src++;
    如果 (len <= size)
        *dst = 0;
    返回 len + strlen(src) - 1;
}

size_t av_strlcat(char *dst, const char *src, size_t size)
{
    size_t len = strlen(dst);
    如果 (size <= len + 1)
        返回 len + strlen(src);
    返回 len + av_strlcpy(dst + len, src, size - len);
}

size_t av_strlcatf(char *dst, size_t size, const char *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    va_end(vl);

    返回 len;
}

char *av_asprintf(const char *fmt, ...)
{
    char *p = NULL;
    va_list va;
    整数 len;

    va_start(va, fmt);
    len = vsnprintf(NULL, 0, fmt, va);
    va_end(va);
    如果 (len < 0)
        goto end;

    p = av_malloc(len + 1);
    如果 (!p)
        goto end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    如果 (len < 0)
        av_freep(&p);

end:
    返回 p;
}

#define WHITESPACES " \n\t\r"

char *av_get_token(const char **buf, const char *term)
{
    char *out     = av_realloc(NULL, strlen(*buf) + 1);
    char *ret     = out, *end = out;
    const char *p = *buf;
    如果 (!out)
        返回 NULL;
    p += strspn(p, WHITESPACES);

    当 (*p && !strspn(p, term)) {
        char c = *p++;
        如果 (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } 否则 如果 (c == '\'') {
            当 (*p && *p != '\'')
                *out++ = *p++;
            如果 (*p) {
                p++;
                end = out;
            }
        } 否则 {
            *out++ = c;
        }
    }

    do
        *out-- = 0;
    当 (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    char *small_ret = av_realloc(ret, out - ret + 2);
    返回 small_ret ? small_ret : ret;
}

char *av_strtok(char *s, const char *delim, char **saveptr)
{
    char *tok;

    如果 (!s && !(s = *saveptr))
        返回 NULL;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    如果 (!*s) {
        *saveptr = NULL;
        返回 NULL;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    如果 (*s) {
        *s = 0;
        *saveptr = s+1;
    } 否则 {
        *saveptr = NULL;
    }

    返回 tok;
}

整数 av_strcasecmp(const char *a, const char *b)
{
    uint8_t c1, c2;
    do {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } 当 (c1 && c1 == c2);
    返回 c1 - c2;
}

整数 av_strncasecmp(const char *a, const char *b, size_t n)
{
    uint8_t c1, c2;
    如果 (n <= 0)
        返回 0;
    do {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } 当 (--n && c1 && c1 == c2);
    返回 c1 - c2;
}

char *av_strireplace(const char *str, const char *from, const char *to)
{
    char *ret = NULL;
    const char *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    如果 (!fromlen)
        返回 av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    当 ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, strlen(pstr));
    如果 (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, NULL);
    } 否则 {
        av_bprint_finalize(&pbuf, &ret);
    }

    返回 ret;
}

const char *av_basename(const char *path)
{
    如果 (!path || *path == '\0')
        返回 ".";

    const char *p = strrchr(path, '/');
#如果 HAVE_DOS_PATHS
    const char *q = strrchr(path, '\\');
    const char *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    如果 (!p)
        返回 path;

    返回 p + 1;
}

const char *av_dirname(char *path)
{
    char *p = path ? strrchr(path, '/') : NULL;

#如果 HAVE_DOS_PATHS
    char *q = path ? strrchr(path, '\\') : NULL;
    char *d = path ? strchr(path, ':')  : NULL;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    如果 (!p)
        返回 ".";

    *p = '\0';

    返回 path;
}

char *av_append_path_component(const char *path, const char *component)
{
    size_t p_len, c_len;
    char *fullpath;

    如果 (!path)
        返回 av_strdup(component);
    如果 (!component)
        返回 av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    如果 (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        返回 NULL;
    fullpath = av_malloc(p_len + c_len + 2);
    如果 (fullpath) {
        如果 (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            如果 (c_len) {
                如果 (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                否则 如果 (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    返回 fullpath;
}

整数 av_escape(char **dst, const char *src, const char *special_chars,
              enum AVEscapeMode mode, 整数 flags)
{
    AVBPrint dstbuf;
    整数 ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    如果 (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, NULL);
        返回 AVERROR(ENOMEM);
    }
    如果 ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        返回 ret;
    返回 dstbuf.len;
}

整数 av_match_name(const char *name, const char *names)
{
    const char *p;
    size_t len, namelen;

    如果 (!name || !names)
        返回 0;

    namelen = strlen(name);
    当 (*names) {
        整数 negate = '-' == *names;
        p = strchr(names, ',');
        如果 (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        如果 (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            返回 !negate;
        names = p + (*p == ',');
    }
    返回 0;
}

整数 av_utf8_decode(int32_t *codep, const uint8_t **bufp, const uint8_t *buf_end,
                   unsigned 整数 flags)
{
    const uint8_t *p = *bufp;
    uint32_t top;
    uint64_t code;
    整数 ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    如果 (p >= buf_end)
        返回 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    如果 ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        goto end;
    }
    top = (code & 128) >> 1;

    tail_len = 0;
    当 (code & top) {
        整数 tmp;
        tail_len++;
        如果 (p >= buf_end) {
            (*bufp) ++;
            返回 AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        如果 (tmp>>6) {
            (*bufp) ++;
            返回 AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        top <<= 5;
    }
    code &= (top << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    如果 (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        goto end;
    }

    如果 (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        goto end;
    }

    *codep = code;

    如果 (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    如果 (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    如果 (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    如果 ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    返回 ret;
}

整数 av_match_list(const char *name, const char *list, char separator)
{
    const char *p, *q;

    为 (p = name; p && *p; ) {
        为 (q = list; q && *q; ) {
            整数 k;
            为 (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                如果 (k && (!p[k] || p[k] == separator))
                    返回 1;
            q = strchr(q, separator);
            如果(q)
                q++;
        }
        p = strchr(p, separator);
        如果 (p)
            p++;
    }

    返回 0;
}
