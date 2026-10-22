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

#અન્તર્ભાવ <limits.h>
#અન્તર્ભાવ <stdarg.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "avstring.h"
#અન્તર્ભાવ "bprint.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "macros.h"

પૂર્ણાંક av_strstart(અચલ અક્ષર *str, અચલ અક્ષર *pfx, અચલ અક્ષર **ptr)
{
    જ્યારે (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    જો (!*pfx && ptr)
        *ptr = str;
    પાછા !*pfx;
}

પૂર્ણાંક av_stristart(અચલ અક્ષર *str, અચલ અક્ષર *pfx, અચલ અક્ષર **ptr)
{
    જ્યારે (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    જો (!*pfx && ptr)
        *ptr = str;
    પાછા !*pfx;
}

અક્ષર *av_stristr(અચલ અક્ષર *s1, અચલ અક્ષર *s2)
{
    જો (!*s2)
        પાછા (અક્ષર*)(intptr_t)s1;

    કરો
        જો (av_stristart(s1, s2, ખાલી))
            પાછા (અક્ષર*)(intptr_t)s1;
    જ્યારે (*s1++);

    પાછા ખાલી;
}

અક્ષર *av_strnstr(અચલ અક્ષર *haystack, અચલ અક્ષર *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    જો (!needle_len)
        પાછા (અક્ષર*)haystack;
    જ્યારે (hay_length >= needle_len) {
        hay_length--;
        જો (!memcmp(haystack, needle, needle_len))
            પાછા (અક્ષર*)haystack;
        haystack++;
    }
    પાછા ખાલી;
}

size_t av_strlcpy(અક્ષર *dst, અચલ અક્ષર *src, size_t size)
{
    size_t len = 0;
    જ્યારે (++len < size && *src)
        *dst++ = *src++;
    જો (len <= size)
        *dst = 0;
    પાછા len + strlen(src) - 1;
}

size_t av_strlcat(અક્ષર *dst, અચલ અક્ષર *src, size_t size)
{
    size_t len = strlen(dst);
    જો (size <= len + 1)
        પાછા len + strlen(src);
    પાછા len + av_strlcpy(dst + len, src, size - len);
}

size_t av_strlcatf(અક્ષર *dst, size_t size, અચલ અક્ષર *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    va_end(vl);

    પાછા len;
}

અક્ષર *av_asprintf(અચલ અક્ષર *fmt, ...)
{
    અક્ષર *p = ખાલી;
    va_list va;
    પૂર્ણાંક len;

    va_start(va, fmt);
    len = vsnprintf(ખાલી, 0, fmt, va);
    va_end(va);
    જો (len < 0)
        જાઓ end;

    p = av_malloc(len + 1);
    જો (!p)
        જાઓ end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    જો (len < 0)
        av_freep(&p);

end:
    પાછા p;
}

#define WHITESPACES " \n\t\r"

અક્ષર *av_get_token(અચલ અક્ષર **buf, અચલ અક્ષર *term)
{
    અક્ષર *out     = av_realloc(ખાલી, strlen(*buf) + 1);
    અક્ષર *ret     = out, *end = out;
    અચલ અક્ષર *p = *buf;
    જો (!out)
        પાછા ખાલી;
    p += strspn(p, WHITESPACES);

    જ્યારે (*p && !strspn(p, term)) {
        અક્ષર c = *p++;
        જો (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } નહીંતર જો (c == '\'') {
            જ્યારે (*p && *p != '\'')
                *out++ = *p++;
            જો (*p) {
                p++;
                end = out;
            }
        } નહીંતર {
            *out++ = c;
        }
    }

    કરો
        *out-- = 0;
    જ્યારે (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    અક્ષર *small_ret = av_realloc(ret, out - ret + 2);
    પાછા small_ret ? small_ret : ret;
}

અક્ષર *av_strtok(અક્ષર *s, અચલ અક્ષર *delim, અક્ષર **saveptr)
{
    અક્ષર *tok;

    જો (!s && !(s = *saveptr))
        પાછા ખાલી;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    જો (!*s) {
        *saveptr = ખાલી;
        પાછા ખાલી;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    જો (*s) {
        *s = 0;
        *saveptr = s+1;
    } નહીંતર {
        *saveptr = ખાલી;
    }

    પાછા tok;
}

પૂર્ણાંક av_strcasecmp(અચલ અક્ષર *a, અચલ અક્ષર *b)
{
    uint8_t c1, c2;
    કરો {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } જ્યારે (c1 && c1 == c2);
    પાછા c1 - c2;
}

પૂર્ણાંક av_strncasecmp(અચલ અક્ષર *a, અચલ અક્ષર *b, size_t n)
{
    uint8_t c1, c2;
    જો (n <= 0)
        પાછા 0;
    કરો {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } જ્યારે (--n && c1 && c1 == c2);
    પાછા c1 - c2;
}

અક્ષર *av_strireplace(અચલ અક્ષર *str, અચલ અક્ષર *from, અચલ અક્ષર *to)
{
    અક્ષર *ret = ખાલી;
    અચલ અક્ષર *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    જો (!fromlen)
        પાછા av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    જ્યારે ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, strlen(pstr));
    જો (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, ખાલી);
    } નહીંતર {
        av_bprint_finalize(&pbuf, &ret);
    }

    પાછા ret;
}

અચલ અક્ષર *av_basename(અચલ અક્ષર *path)
{
    જો (!path || *path == '\0')
        પાછા ".";

    અચલ અક્ષર *p = strrchr(path, '/');
#જો HAVE_DOS_PATHS
    અચલ અક્ષર *q = strrchr(path, '\\');
    અચલ અક્ષર *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    જો (!p)
        પાછા path;

    પાછા p + 1;
}

અચલ અક્ષર *av_dirname(અક્ષર *path)
{
    અક્ષર *p = path ? strrchr(path, '/') : ખાલી;

#જો HAVE_DOS_PATHS
    અક્ષર *q = path ? strrchr(path, '\\') : ખાલી;
    અક્ષર *d = path ? strchr(path, ':')  : ખાલી;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    જો (!p)
        પાછા ".";

    *p = '\0';

    પાછા path;
}

અક્ષર *av_append_path_component(અચલ અક્ષર *path, અચલ અક્ષર *component)
{
    size_t p_len, c_len;
    અક્ષર *fullpath;

    જો (!path)
        પાછા av_strdup(component);
    જો (!component)
        પાછા av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    જો (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        પાછા ખાલી;
    fullpath = av_malloc(p_len + c_len + 2);
    જો (fullpath) {
        જો (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            જો (c_len) {
                જો (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                નહીંતર જો (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    પાછા fullpath;
}

પૂર્ણાંક av_escape(અક્ષર **dst, અચલ અક્ષર *src, અચલ અક્ષર *special_chars,
              ગણના AVEscapeMode mode, પૂર્ણાંક flags)
{
    AVBPrint dstbuf;
    પૂર્ણાંક ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    જો (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, ખાલી);
        પાછા AVERROR(ENOMEM);
    }
    જો ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        પાછા ret;
    પાછા dstbuf.len;
}

પૂર્ણાંક av_match_name(અચલ અક્ષર *name, અચલ અક્ષર *names)
{
    અચલ અક્ષર *p;
    size_t len, namelen;

    જો (!name || !names)
        પાછા 0;

    namelen = strlen(name);
    જ્યારે (*names) {
        પૂર્ણાંક negate = '-' == *names;
        p = strchr(names, ',');
        જો (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        જો (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            પાછા !negate;
        names = p + (*p == ',');
    }
    પાછા 0;
}

પૂર્ણાંક av_utf8_decode(int32_t *codep, અચલ uint8_t **bufp, અચલ uint8_t *buf_end,
                   unsigned પૂર્ણાંક flags)
{
    અચલ uint8_t *p = *bufp;
    uint32_t ટોચ;
    uint64_t code;
    પૂર્ણાંક ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    જો (p >= buf_end)
        પાછા 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    જો ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        જાઓ end;
    }
    ટોચ = (code & 128) >> 1;

    tail_len = 0;
    જ્યારે (code & ટોચ) {
        પૂર્ણાંક tmp;
        tail_len++;
        જો (p >= buf_end) {
            (*bufp) ++;
            પાછા AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        જો (tmp>>6) {
            (*bufp) ++;
            પાછા AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        ટોચ <<= 5;
    }
    code &= (ટોચ << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    જો (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        જાઓ end;
    }

    જો (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        જાઓ end;
    }

    *codep = code;

    જો (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    જો (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    જો (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    જો ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    પાછા ret;
}

પૂર્ણાંક av_match_list(અચલ અક્ષર *name, અચલ અક્ષર *list, અક્ષર separator)
{
    અચલ અક્ષર *p, *q;

    માટે (p = name; p && *p; ) {
        માટે (q = list; q && *q; ) {
            પૂર્ણાંક k;
            માટે (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                જો (k && (!p[k] || p[k] == separator))
                    પાછા 1;
            q = strchr(q, separator);
            જો(q)
                q++;
        }
        p = strchr(p, separator);
        જો (p)
            p++;
    }

    પાછા 0;
}
