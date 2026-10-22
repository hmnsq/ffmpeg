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
    ܟܡܐ (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    ܐܢ (!*pfx && ptr)
        *ptr = str;
    ܦܢܐ !*pfx;
}

صحيح av_stristart(ثابت حرف *str, ثابت حرف *pfx, ثابت حرف **ptr)
{
    ܟܡܐ (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    ܐܢ (!*pfx && ptr)
        *ptr = str;
    ܦܢܐ !*pfx;
}

حرف *av_stristr(ثابت حرف *s1, ثابت حرف *s2)
{
    ܐܢ (!*s2)
        ܦܢܐ (حرف*)(intptr_t)s1;

    ܥܒܕ
        ܐܢ (av_stristart(s1, s2, عدم))
            ܦܢܐ (حرف*)(intptr_t)s1;
    ܟܡܐ (*s1++);

    ܦܢܐ عدم;
}

حرف *av_strnstr(ثابت حرف *haystack, ثابت حرف *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    ܐܢ (!needle_len)
        ܦܢܐ (حرف*)haystack;
    ܟܡܐ (hay_length >= needle_len) {
        hay_length--;
        ܐܢ (!memcmp(haystack, needle, needle_len))
            ܦܢܐ (حرف*)haystack;
        haystack++;
    }
    ܦܢܐ عدم;
}

size_t av_strlcpy(حرف *dst, ثابت حرف *src, size_t size)
{
    size_t len = 0;
    ܟܡܐ (++len < size && *src)
        *dst++ = *src++;
    ܐܢ (len <= size)
        *dst = 0;
    ܦܢܐ len + strlen(src) - 1;
}

size_t av_strlcat(حرف *dst, ثابت حرف *src, size_t size)
{
    size_t len = strlen(dst);
    ܐܢ (size <= len + 1)
        ܦܢܐ len + strlen(src);
    ܦܢܐ len + av_strlcpy(dst + len, src, size - len);
}

size_t av_strlcatf(حرف *dst, size_t size, ثابت حرف *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    va_end(vl);

    ܦܢܐ len;
}

حرف *av_asprintf(ثابت حرف *fmt, ...)
{
    حرف *p = عدم;
    va_list va;
    صحيح len;

    va_start(va, fmt);
    len = vsnprintf(عدم, 0, fmt, va);
    va_end(va);
    ܐܢ (len < 0)
        اذهب end;

    p = av_malloc(len + 1);
    ܐܢ (!p)
        اذهب end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    ܐܢ (len < 0)
        av_freep(&p);

end:
    ܦܢܐ p;
}

#define WHITESPACES " \n\t\r"

حرف *av_get_token(ثابت حرف **buf, ثابت حرف *term)
{
    حرف *out     = av_realloc(عدم, strlen(*buf) + 1);
    حرف *ret     = out, *end = out;
    ثابت حرف *p = *buf;
    ܐܢ (!out)
        ܦܢܐ عدم;
    p += strspn(p, WHITESPACES);

    ܟܡܐ (*p && !strspn(p, term)) {
        حرف c = *p++;
        ܐܢ (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } ܐܚܪܢܐ ܐܢ (c == '\'') {
            ܟܡܐ (*p && *p != '\'')
                *out++ = *p++;
            ܐܢ (*p) {
                p++;
                end = out;
            }
        } ܐܚܪܢܐ {
            *out++ = c;
        }
    }

    ܥܒܕ
        *out-- = 0;
    ܟܡܐ (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    حرف *small_ret = av_realloc(ret, out - ret + 2);
    ܦܢܐ small_ret ? small_ret : ret;
}

حرف *av_strtok(حرف *s, ثابت حرف *delim, حرف **saveptr)
{
    حرف *tok;

    ܐܢ (!s && !(s = *saveptr))
        ܦܢܐ عدم;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    ܐܢ (!*s) {
        *saveptr = عدم;
        ܦܢܐ عدم;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    ܐܢ (*s) {
        *s = 0;
        *saveptr = s+1;
    } ܐܚܪܢܐ {
        *saveptr = عدم;
    }

    ܦܢܐ tok;
}

صحيح av_strcasecmp(ثابت حرف *a, ثابت حرف *b)
{
    uint8_t c1, c2;
    ܥܒܕ {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ܟܡܐ (c1 && c1 == c2);
    ܦܢܐ c1 - c2;
}

صحيح av_strncasecmp(ثابت حرف *a, ثابت حرف *b, size_t n)
{
    uint8_t c1, c2;
    ܐܢ (n <= 0)
        ܦܢܐ 0;
    ܥܒܕ {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ܟܡܐ (--n && c1 && c1 == c2);
    ܦܢܐ c1 - c2;
}

حرف *av_strireplace(ثابت حرف *str, ثابت حرف *from, ثابت حرف *to)
{
    حرف *ret = عدم;
    ثابت حرف *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    ܐܢ (!fromlen)
        ܦܢܐ av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    ܟܡܐ ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, strlen(pstr));
    ܐܢ (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, عدم);
    } ܐܚܪܢܐ {
        av_bprint_finalize(&pbuf, &ret);
    }

    ܦܢܐ ret;
}

ثابت حرف *av_basename(ثابت حرف *path)
{
    ܐܢ (!path || *path == '\0')
        ܦܢܐ ".";

    ثابت حرف *p = strrchr(path, '/');
#ܐܢ HAVE_DOS_PATHS
    ثابت حرف *q = strrchr(path, '\\');
    ثابت حرف *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    ܐܢ (!p)
        ܦܢܐ path;

    ܦܢܐ p + 1;
}

ثابت حرف *av_dirname(حرف *path)
{
    حرف *p = path ? strrchr(path, '/') : عدم;

#ܐܢ HAVE_DOS_PATHS
    حرف *q = path ? strrchr(path, '\\') : عدم;
    حرف *d = path ? strchr(path, ':')  : عدم;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    ܐܢ (!p)
        ܦܢܐ ".";

    *p = '\0';

    ܦܢܐ path;
}

حرف *av_append_path_component(ثابت حرف *path, ثابت حرف *component)
{
    size_t p_len, c_len;
    حرف *fullpath;

    ܐܢ (!path)
        ܦܢܐ av_strdup(component);
    ܐܢ (!component)
        ܦܢܐ av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    ܐܢ (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        ܦܢܐ عدم;
    fullpath = av_malloc(p_len + c_len + 2);
    ܐܢ (fullpath) {
        ܐܢ (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            ܐܢ (c_len) {
                ܐܢ (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                ܐܚܪܢܐ ܐܢ (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    ܦܢܐ fullpath;
}

صحيح av_escape(حرف **dst, ثابت حرف *src, ثابت حرف *special_chars,
              تعداد AVEscapeMode mode, صحيح flags)
{
    AVBPrint dstbuf;
    صحيح ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    ܐܢ (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, عدم);
        ܦܢܐ AVERROR(ENOMEM);
    }
    ܐܢ ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        ܦܢܐ ret;
    ܦܢܐ dstbuf.len;
}

صحيح av_match_name(ثابت حرف *name, ثابت حرف *names)
{
    ثابت حرف *p;
    size_t len, namelen;

    ܐܢ (!name || !names)
        ܦܢܐ 0;

    namelen = strlen(name);
    ܟܡܐ (*names) {
        صحيح negate = '-' == *names;
        p = strchr(names, ',');
        ܐܢ (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        ܐܢ (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            ܦܢܐ !negate;
        names = p + (*p == ',');
    }
    ܦܢܐ 0;
}

صحيح av_utf8_decode(int32_t *codep, ثابت uint8_t **bufp, ثابت uint8_t *buf_end,
                   unsigned صحيح flags)
{
    ثابت uint8_t *p = *bufp;
    uint32_t top;
    uint64_t code;
    صحيح ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    ܐܢ (p >= buf_end)
        ܦܢܐ 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    ܐܢ ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        اذهب end;
    }
    top = (code & 128) >> 1;

    tail_len = 0;
    ܟܡܐ (code & top) {
        صحيح tmp;
        tail_len++;
        ܐܢ (p >= buf_end) {
            (*bufp) ++;
            ܦܢܐ AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        ܐܢ (tmp>>6) {
            (*bufp) ++;
            ܦܢܐ AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        top <<= 5;
    }
    code &= (top << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    ܐܢ (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        اذهب end;
    }

    ܐܢ (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        اذهب end;
    }

    *codep = code;

    ܐܢ (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    ܐܢ (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    ܐܢ (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    ܐܢ ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    ܦܢܐ ret;
}

صحيح av_match_list(ثابت حرف *name, ثابت حرف *list, حرف separator)
{
    ثابت حرف *p, *q;

    لكل (p = name; p && *p; ) {
        لكل (q = list; q && *q; ) {
            صحيح k;
            لكل (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                ܐܢ (k && (!p[k] || p[k] == separator))
                    ܦܢܐ 1;
            q = strchr(q, separator);
            ܐܢ(q)
                q++;
        }
        p = strchr(p, separator);
        ܐܢ (p)
            p++;
    }

    ܦܢܐ 0;
}
