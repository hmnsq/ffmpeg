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

цео av_strstart(const char *str, const char *pfx, const char **ptr)
{
    док (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    ако (!*pfx && ptr)
        *ptr = str;
    врати !*pfx;
}

цео av_stristart(const char *str, const char *pfx, const char **ptr)
{
    док (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    ако (!*pfx && ptr)
        *ptr = str;
    врати !*pfx;
}

char *av_stristr(const char *s1, const char *s2)
{
    ако (!*s2)
        врати (char*)(intptr_t)s1;

    do
        ако (av_stristart(s1, s2, NULL))
            врати (char*)(intptr_t)s1;
    док (*s1++);

    врати NULL;
}

char *av_strnstr(const char *haystack, const char *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    ако (!needle_len)
        врати (char*)haystack;
    док (hay_length >= needle_len) {
        hay_length--;
        ако (!memcmp(haystack, needle, needle_len))
            врати (char*)haystack;
        haystack++;
    }
    врати NULL;
}

size_t av_strlcpy(char *dst, const char *src, size_t size)
{
    size_t len = 0;
    док (++len < size && *src)
        *dst++ = *src++;
    ако (len <= size)
        *dst = 0;
    врати len + strlen(src) - 1;
}

size_t av_strlcat(char *dst, const char *src, size_t size)
{
    size_t len = strlen(dst);
    ако (size <= len + 1)
        врати len + strlen(src);
    врати len + av_strlcpy(dst + len, src, size - len);
}

size_t av_strlcatf(char *dst, size_t size, const char *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    va_end(vl);

    врати len;
}

char *av_asprintf(const char *fmt, ...)
{
    char *p = NULL;
    va_list va;
    цео len;

    va_start(va, fmt);
    len = vsnprintf(NULL, 0, fmt, va);
    va_end(va);
    ако (len < 0)
        goto end;

    p = av_malloc(len + 1);
    ако (!p)
        goto end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    ако (len < 0)
        av_freep(&p);

end:
    врати p;
}

#define WHITESPACES " \n\t\r"

char *av_get_token(const char **buf, const char *term)
{
    char *out     = av_realloc(NULL, strlen(*buf) + 1);
    char *ret     = out, *end = out;
    const char *p = *buf;
    ако (!out)
        врати NULL;
    p += strspn(p, WHITESPACES);

    док (*p && !strspn(p, term)) {
        char c = *p++;
        ако (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } инако ако (c == '\'') {
            док (*p && *p != '\'')
                *out++ = *p++;
            ако (*p) {
                p++;
                end = out;
            }
        } инако {
            *out++ = c;
        }
    }

    do
        *out-- = 0;
    док (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    char *small_ret = av_realloc(ret, out - ret + 2);
    врати small_ret ? small_ret : ret;
}

char *av_strtok(char *s, const char *delim, char **saveptr)
{
    char *tok;

    ако (!s && !(s = *saveptr))
        врати NULL;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    ако (!*s) {
        *saveptr = NULL;
        врати NULL;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    ако (*s) {
        *s = 0;
        *saveptr = s+1;
    } инако {
        *saveptr = NULL;
    }

    врати tok;
}

цео av_strcasecmp(const char *a, const char *b)
{
    uint8_t c1, c2;
    do {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } док (c1 && c1 == c2);
    врати c1 - c2;
}

цео av_strncasecmp(const char *a, const char *b, size_t n)
{
    uint8_t c1, c2;
    ако (n <= 0)
        врати 0;
    do {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } док (--n && c1 && c1 == c2);
    врати c1 - c2;
}

char *av_strireplace(const char *str, const char *from, const char *to)
{
    char *ret = NULL;
    const char *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    ако (!fromlen)
        врати av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    док ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, strlen(pstr));
    ако (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, NULL);
    } инако {
        av_bprint_finalize(&pbuf, &ret);
    }

    врати ret;
}

const char *av_basename(const char *path)
{
    ако (!path || *path == '\0')
        врати ".";

    const char *p = strrchr(path, '/');
#ако HAVE_DOS_PATHS
    const char *q = strrchr(path, '\\');
    const char *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    ако (!p)
        врати path;

    врати p + 1;
}

const char *av_dirname(char *path)
{
    char *p = path ? strrchr(path, '/') : NULL;

#ако HAVE_DOS_PATHS
    char *q = path ? strrchr(path, '\\') : NULL;
    char *d = path ? strchr(path, ':')  : NULL;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    ако (!p)
        врати ".";

    *p = '\0';

    врати path;
}

char *av_append_path_component(const char *path, const char *component)
{
    size_t p_len, c_len;
    char *fullpath;

    ако (!path)
        врати av_strdup(component);
    ако (!component)
        врати av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    ако (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        врати NULL;
    fullpath = av_malloc(p_len + c_len + 2);
    ако (fullpath) {
        ако (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            ако (c_len) {
                ако (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                инако ако (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    врати fullpath;
}

цео av_escape(char **dst, const char *src, const char *special_chars,
              enum AVEscapeMode mode, цео flags)
{
    AVBPrint dstbuf;
    цео ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    ако (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, NULL);
        врати AVERROR(ENOMEM);
    }
    ако ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        врати ret;
    врати dstbuf.len;
}

цео av_match_name(const char *name, const char *names)
{
    const char *p;
    size_t len, namelen;

    ако (!name || !names)
        врати 0;

    namelen = strlen(name);
    док (*names) {
        цео negate = '-' == *names;
        p = strchr(names, ',');
        ако (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        ако (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            врати !negate;
        names = p + (*p == ',');
    }
    врати 0;
}

цео av_utf8_decode(int32_t *codep, const uint8_t **bufp, const uint8_t *buf_end,
                   unsigned цео flags)
{
    const uint8_t *p = *bufp;
    uint32_t top;
    uint64_t code;
    цео ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    ако (p >= buf_end)
        врати 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    ако ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        goto end;
    }
    top = (code & 128) >> 1;

    tail_len = 0;
    док (code & top) {
        цео tmp;
        tail_len++;
        ако (p >= buf_end) {
            (*bufp) ++;
            врати AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        ако (tmp>>6) {
            (*bufp) ++;
            врати AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        top <<= 5;
    }
    code &= (top << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    ако (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        goto end;
    }

    ако (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        goto end;
    }

    *codep = code;

    ако (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    ако (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    ако (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    ако ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    врати ret;
}

цео av_match_list(const char *name, const char *list, char separator)
{
    const char *p, *q;

    за (p = name; p && *p; ) {
        за (q = list; q && *q; ) {
            цео k;
            за (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                ако (k && (!p[k] || p[k] == separator))
                    врати 1;
            q = strchr(q, separator);
            ако(q)
                q++;
        }
        p = strchr(p, separator);
        ако (p)
            p++;
    }

    врати 0;
}
