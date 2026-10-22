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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "bprint.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "macros.h"

ಪೂರ್ಣಾಙ್ಕ av_strstart(ಧ್ರುವ ವರ್ಣ *str, ಧ್ರುವ ವರ್ಣ *pfx, ಧ್ರುವ ವರ್ಣ **ptr)
{
    ಯಾವತ್ (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    ಯದಿ (!*pfx && ptr)
        *ptr = str;
    ಪ್ರತ್ಯಾಗಮ !*pfx;
}

ಪೂರ್ಣಾಙ್ಕ av_stristart(ಧ್ರುವ ವರ್ಣ *str, ಧ್ರುವ ವರ್ಣ *pfx, ಧ್ರುವ ವರ್ಣ **ptr)
{
    ಯಾವತ್ (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    ಯದಿ (!*pfx && ptr)
        *ptr = str;
    ಪ್ರತ್ಯಾಗಮ !*pfx;
}

ವರ್ಣ *av_stristr(ಧ್ರುವ ವರ್ಣ *s1, ಧ್ರುವ ವರ್ಣ *s2)
{
    ಯದಿ (!*s2)
        ಪ್ರತ್ಯಾಗಮ (ವರ್ಣ*)(intptr_t)s1;

    ಕುರು
        ಯದಿ (av_stristart(s1, s2, ರಿಕ್ತ))
            ಪ್ರತ್ಯಾಗಮ (ವರ್ಣ*)(intptr_t)s1;
    ಯಾವತ್ (*s1++);

    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ವರ್ಣ *av_strnstr(ಧ್ರುವ ವರ್ಣ *haystack, ಧ್ರುವ ವರ್ಣ *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    ಯದಿ (!needle_len)
        ಪ್ರತ್ಯಾಗಮ (ವರ್ಣ*)haystack;
    ಯಾವತ್ (hay_length >= needle_len) {
        hay_length--;
        ಯದಿ (!memcmp(haystack, needle, needle_len))
            ಪ್ರತ್ಯಾಗಮ (ವರ್ಣ*)haystack;
        haystack++;
    }
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

size_t av_strlcpy(ವರ್ಣ *dst, ಧ್ರುವ ವರ್ಣ *src, size_t size)
{
    size_t len = 0;
    ಯಾವತ್ (++len < size && *src)
        *dst++ = *src++;
    ಯದಿ (len <= size)
        *dst = 0;
    ಪ್ರತ್ಯಾಗಮ len + strlen(src) - 1;
}

size_t av_strlcat(ವರ್ಣ *dst, ಧ್ರುವ ವರ್ಣ *src, size_t size)
{
    size_t len = strlen(dst);
    ಯದಿ (size <= len + 1)
        ಪ್ರತ್ಯಾಗಮ len + strlen(src);
    ಪ್ರತ್ಯಾಗಮ len + av_strlcpy(dst + len, src, size - len);
}

size_t av_strlcatf(ವರ್ಣ *dst, size_t size, ಧ್ರುವ ವರ್ಣ *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    va_end(vl);

    ಪ್ರತ್ಯಾಗಮ len;
}

ವರ್ಣ *av_asprintf(ಧ್ರುವ ವರ್ಣ *fmt, ...)
{
    ವರ್ಣ *p = ರಿಕ್ತ;
    va_list va;
    ಪೂರ್ಣಾಙ್ಕ len;

    va_start(va, fmt);
    len = vsnprintf(ರಿಕ್ತ, 0, fmt, va);
    va_end(va);
    ಯದಿ (len < 0)
        ಗಚ್ಛ end;

    p = av_malloc(len + 1);
    ಯದಿ (!p)
        ಗಚ್ಛ end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    ಯದಿ (len < 0)
        av_freep(&p);

end:
    ಪ್ರತ್ಯಾಗಮ p;
}

#define WHITESPACES " \n\t\r"

ವರ್ಣ *av_get_token(ಧ್ರುವ ವರ್ಣ **buf, ಧ್ರುವ ವರ್ಣ *term)
{
    ವರ್ಣ *out     = av_realloc(ರಿಕ್ತ, strlen(*buf) + 1);
    ವರ್ಣ *ret     = out, *end = out;
    ಧ್ರುವ ವರ್ಣ *p = *buf;
    ಯದಿ (!out)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    p += strspn(p, WHITESPACES);

    ಯಾವತ್ (*p && !strspn(p, term)) {
        ವರ್ಣ c = *p++;
        ಯದಿ (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } ಅನ್ಯಥಾ ಯದಿ (c == '\'') {
            ಯಾವತ್ (*p && *p != '\'')
                *out++ = *p++;
            ಯದಿ (*p) {
                p++;
                end = out;
            }
        } ಅನ್ಯಥಾ {
            *out++ = c;
        }
    }

    ಕುರು
        *out-- = 0;
    ಯಾವತ್ (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    ವರ್ಣ *small_ret = av_realloc(ret, out - ret + 2);
    ಪ್ರತ್ಯಾಗಮ small_ret ? small_ret : ret;
}

ವರ್ಣ *av_strtok(ವರ್ಣ *s, ಧ್ರುವ ವರ್ಣ *delim, ವರ್ಣ **saveptr)
{
    ವರ್ಣ *tok;

    ಯದಿ (!s && !(s = *saveptr))
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    ಯದಿ (!*s) {
        *saveptr = ರಿಕ್ತ;
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    ಯದಿ (*s) {
        *s = 0;
        *saveptr = s+1;
    } ಅನ್ಯಥಾ {
        *saveptr = ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ tok;
}

ಪೂರ್ಣಾಙ್ಕ av_strcasecmp(ಧ್ರುವ ವರ್ಣ *a, ಧ್ರುವ ವರ್ಣ *b)
{
    uint8_t c1, c2;
    ಕುರು {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ಯಾವತ್ (c1 && c1 == c2);
    ಪ್ರತ್ಯಾಗಮ c1 - c2;
}

ಪೂರ್ಣಾಙ್ಕ av_strncasecmp(ಧ್ರುವ ವರ್ಣ *a, ಧ್ರುವ ವರ್ಣ *b, size_t n)
{
    uint8_t c1, c2;
    ಯದಿ (n <= 0)
        ಪ್ರತ್ಯಾಗಮ 0;
    ಕುರು {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ಯಾವತ್ (--n && c1 && c1 == c2);
    ಪ್ರತ್ಯಾಗಮ c1 - c2;
}

ವರ್ಣ *av_strireplace(ಧ್ರುವ ವರ್ಣ *str, ಧ್ರುವ ವರ್ಣ *from, ಧ್ರುವ ವರ್ಣ *to)
{
    ವರ್ಣ *ret = ರಿಕ್ತ;
    ಧ್ರುವ ವರ್ಣ *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    ಯದಿ (!fromlen)
        ಪ್ರತ್ಯಾಗಮ av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    ಯಾವತ್ ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, strlen(pstr));
    ಯದಿ (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, ರಿಕ್ತ);
    } ಅನ್ಯಥಾ {
        av_bprint_finalize(&pbuf, &ret);
    }

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಧ್ರುವ ವರ್ಣ *av_basename(ಧ್ರುವ ವರ್ಣ *path)
{
    ಯದಿ (!path || *path == '\0')
        ಪ್ರತ್ಯಾಗಮ ".";

    ಧ್ರುವ ವರ್ಣ *p = strrchr(path, '/');
#ಯದಿ HAVE_DOS_PATHS
    ಧ್ರುವ ವರ್ಣ *q = strrchr(path, '\\');
    ಧ್ರುವ ವರ್ಣ *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    ಯದಿ (!p)
        ಪ್ರತ್ಯಾಗಮ path;

    ಪ್ರತ್ಯಾಗಮ p + 1;
}

ಧ್ರುವ ವರ್ಣ *av_dirname(ವರ್ಣ *path)
{
    ವರ್ಣ *p = path ? strrchr(path, '/') : ರಿಕ್ತ;

#ಯದಿ HAVE_DOS_PATHS
    ವರ್ಣ *q = path ? strrchr(path, '\\') : ರಿಕ್ತ;
    ವರ್ಣ *d = path ? strchr(path, ':')  : ರಿಕ್ತ;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    ಯದಿ (!p)
        ಪ್ರತ್ಯಾಗಮ ".";

    *p = '\0';

    ಪ್ರತ್ಯಾಗಮ path;
}

ವರ್ಣ *av_append_path_component(ಧ್ರುವ ವರ್ಣ *path, ಧ್ರುವ ವರ್ಣ *component)
{
    size_t p_len, c_len;
    ವರ್ಣ *fullpath;

    ಯದಿ (!path)
        ಪ್ರತ್ಯಾಗಮ av_strdup(component);
    ಯದಿ (!component)
        ಪ್ರತ್ಯಾಗಮ av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    ಯದಿ (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    fullpath = av_malloc(p_len + c_len + 2);
    ಯದಿ (fullpath) {
        ಯದಿ (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            ಯದಿ (c_len) {
                ಯದಿ (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                ಅನ್ಯಥಾ ಯದಿ (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    ಪ್ರತ್ಯಾಗಮ fullpath;
}

ಪೂರ್ಣಾಙ್ಕ av_escape(ವರ್ಣ **dst, ಧ್ರುವ ವರ್ಣ *src, ಧ್ರುವ ವರ್ಣ *special_chars,
              ಗಣನಾ AVEscapeMode mode, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVBPrint dstbuf;
    ಪೂರ್ಣಾಙ್ಕ ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    ಯದಿ (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, ರಿಕ್ತ);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }
    ಯದಿ ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ಪ್ರತ್ಯಾಗಮ dstbuf.len;
}

ಪೂರ್ಣಾಙ್ಕ av_match_name(ಧ್ರುವ ವರ್ಣ *name, ಧ್ರುವ ವರ್ಣ *names)
{
    ಧ್ರುವ ವರ್ಣ *p;
    size_t len, namelen;

    ಯದಿ (!name || !names)
        ಪ್ರತ್ಯಾಗಮ 0;

    namelen = strlen(name);
    ಯಾವತ್ (*names) {
        ಪೂರ್ಣಾಙ್ಕ negate = '-' == *names;
        p = strchr(names, ',');
        ಯದಿ (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        ಯದಿ (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            ಪ್ರತ್ಯಾಗಮ !negate;
        names = p + (*p == ',');
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_utf8_decode(int32_t *codep, ಧ್ರುವ uint8_t **bufp, ಧ್ರುವ uint8_t *buf_end,
                   unsigned ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಧ್ರುವ uint8_t *p = *bufp;
    uint32_t ತುದಿ;
    uint64_t code;
    ಪೂರ್ಣಾಙ್ಕ ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    ಯದಿ (p >= buf_end)
        ಪ್ರತ್ಯಾಗಮ 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    ಯದಿ ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        ಗಚ್ಛ end;
    }
    ತುದಿ = (code & 128) >> 1;

    tail_len = 0;
    ಯಾವತ್ (code & ತುದಿ) {
        ಪೂರ್ಣಾಙ್ಕ tmp;
        tail_len++;
        ಯದಿ (p >= buf_end) {
            (*bufp) ++;
            ಪ್ರತ್ಯಾಗಮ AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        ಯದಿ (tmp>>6) {
            (*bufp) ++;
            ಪ್ರತ್ಯಾಗಮ AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        ತುದಿ <<= 5;
    }
    code &= (ತುದಿ << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    ಯದಿ (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        ಗಚ್ಛ end;
    }

    ಯದಿ (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        ಗಚ್ಛ end;
    }

    *codep = code;

    ಯದಿ (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    ಯದಿ (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    ಯದಿ (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    ಯದಿ ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_match_list(ಧ್ರುವ ವರ್ಣ *name, ಧ್ರುವ ವರ್ಣ *list, ವರ್ಣ separator)
{
    ಧ್ರುವ ವರ್ಣ *p, *q;

    ಪ್ರತಿ (p = name; p && *p; ) {
        ಪ್ರತಿ (q = list; q && *q; ) {
            ಪೂರ್ಣಾಙ್ಕ k;
            ಪ್ರತಿ (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                ಯದಿ (k && (!p[k] || p[k] == separator))
                    ಪ್ರತ್ಯಾಗಮ 1;
            q = strchr(q, separator);
            ಯದಿ(q)
                q++;
        }
        p = strchr(p, separator);
        ಯದಿ (p)
            p++;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}
