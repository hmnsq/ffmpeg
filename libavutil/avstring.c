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

#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <stdarg.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "avstring.h"
#অন্তর্ভাব "bprint.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "macros.h"

পূর্ণাঙ্ক av_strstart(ধ্রুব বর্ণ *str, ধ্রুব বর্ণ *pfx, ধ্রুব বর্ণ **ptr)
{
    যাবত্ (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    যদি (!*pfx && ptr)
        *ptr = str;
    প্রত্যাগম !*pfx;
}

পূর্ণাঙ্ক av_stristart(ধ্রুব বর্ণ *str, ধ্রুব বর্ণ *pfx, ধ্রুব বর্ণ **ptr)
{
    যাবত্ (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    যদি (!*pfx && ptr)
        *ptr = str;
    প্রত্যাগম !*pfx;
}

বর্ণ *av_stristr(ধ্রুব বর্ণ *s1, ধ্রুব বর্ণ *s2)
{
    যদি (!*s2)
        প্রত্যাগম (বর্ণ*)(intptr_t)s1;

    কুরু
        যদি (av_stristart(s1, s2, রিক্ত))
            প্রত্যাগম (বর্ণ*)(intptr_t)s1;
    যাবত্ (*s1++);

    প্রত্যাগম রিক্ত;
}

বর্ণ *av_strnstr(ধ্রুব বর্ণ *haystack, ধ্রুব বর্ণ *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    যদি (!needle_len)
        প্রত্যাগম (বর্ণ*)haystack;
    যাবত্ (hay_length >= needle_len) {
        hay_length--;
        যদি (!memcmp(haystack, needle, needle_len))
            প্রত্যাগম (বর্ণ*)haystack;
        haystack++;
    }
    প্রত্যাগম রিক্ত;
}

size_t av_strlcpy(বর্ণ *dst, ধ্রুব বর্ণ *src, size_t size)
{
    size_t len = 0;
    যাবত্ (++len < size && *src)
        *dst++ = *src++;
    যদি (len <= size)
        *dst = 0;
    প্রত্যাগম len + strlen(src) - 1;
}

size_t av_strlcat(বর্ণ *dst, ধ্রুব বর্ণ *src, size_t size)
{
    size_t len = strlen(dst);
    যদি (size <= len + 1)
        প্রত্যাগম len + strlen(src);
    প্রত্যাগম len + av_strlcpy(dst + len, src, size - len);
}

size_t av_strlcatf(বর্ণ *dst, size_t size, ধ্রুব বর্ণ *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    va_end(vl);

    প্রত্যাগম len;
}

বর্ণ *av_asprintf(ধ্রুব বর্ণ *fmt, ...)
{
    বর্ণ *p = রিক্ত;
    va_list va;
    পূর্ণাঙ্ক len;

    va_start(va, fmt);
    len = vsnprintf(রিক্ত, 0, fmt, va);
    va_end(va);
    যদি (len < 0)
        গচ্ছ end;

    p = av_malloc(len + 1);
    যদি (!p)
        গচ্ছ end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    যদি (len < 0)
        av_freep(&p);

end:
    প্রত্যাগম p;
}

#define WHITESPACES " \n\t\r"

বর্ণ *av_get_token(ধ্রুব বর্ণ **buf, ধ্রুব বর্ণ *term)
{
    বর্ণ *out     = av_realloc(রিক্ত, strlen(*buf) + 1);
    বর্ণ *ret     = out, *end = out;
    ধ্রুব বর্ণ *p = *buf;
    যদি (!out)
        প্রত্যাগম রিক্ত;
    p += strspn(p, WHITESPACES);

    যাবত্ (*p && !strspn(p, term)) {
        বর্ণ c = *p++;
        যদি (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } অন্যথা যদি (c == '\'') {
            যাবত্ (*p && *p != '\'')
                *out++ = *p++;
            যদি (*p) {
                p++;
                end = out;
            }
        } অন্যথা {
            *out++ = c;
        }
    }

    কুরু
        *out-- = 0;
    যাবত্ (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    বর্ণ *small_ret = av_realloc(ret, out - ret + 2);
    প্রত্যাগম small_ret ? small_ret : ret;
}

বর্ণ *av_strtok(বর্ণ *s, ধ্রুব বর্ণ *delim, বর্ণ **saveptr)
{
    বর্ণ *tok;

    যদি (!s && !(s = *saveptr))
        প্রত্যাগম রিক্ত;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    যদি (!*s) {
        *saveptr = রিক্ত;
        প্রত্যাগম রিক্ত;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    যদি (*s) {
        *s = 0;
        *saveptr = s+1;
    } অন্যথা {
        *saveptr = রিক্ত;
    }

    প্রত্যাগম tok;
}

পূর্ণাঙ্ক av_strcasecmp(ধ্রুব বর্ণ *a, ধ্রুব বর্ণ *b)
{
    uint8_t c1, c2;
    কুরু {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } যাবত্ (c1 && c1 == c2);
    প্রত্যাগম c1 - c2;
}

পূর্ণাঙ্ক av_strncasecmp(ধ্রুব বর্ণ *a, ধ্রুব বর্ণ *b, size_t n)
{
    uint8_t c1, c2;
    যদি (n <= 0)
        প্রত্যাগম 0;
    কুরু {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } যাবত্ (--n && c1 && c1 == c2);
    প্রত্যাগম c1 - c2;
}

বর্ণ *av_strireplace(ধ্রুব বর্ণ *str, ধ্রুব বর্ণ *from, ধ্রুব বর্ণ *to)
{
    বর্ণ *ret = রিক্ত;
    ধ্রুব বর্ণ *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    যদি (!fromlen)
        প্রত্যাগম av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    যাবত্ ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, strlen(pstr));
    যদি (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, রিক্ত);
    } অন্যথা {
        av_bprint_finalize(&pbuf, &ret);
    }

    প্রত্যাগম ret;
}

ধ্রুব বর্ণ *av_basename(ধ্রুব বর্ণ *path)
{
    যদি (!path || *path == '\0')
        প্রত্যাগম ".";

    ধ্রুব বর্ণ *p = strrchr(path, '/');
#যদি HAVE_DOS_PATHS
    ধ্রুব বর্ণ *q = strrchr(path, '\\');
    ধ্রুব বর্ণ *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    যদি (!p)
        প্রত্যাগম path;

    প্রত্যাগম p + 1;
}

ধ্রুব বর্ণ *av_dirname(বর্ণ *path)
{
    বর্ণ *p = path ? strrchr(path, '/') : রিক্ত;

#যদি HAVE_DOS_PATHS
    বর্ণ *q = path ? strrchr(path, '\\') : রিক্ত;
    বর্ণ *d = path ? strchr(path, ':')  : রিক্ত;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    যদি (!p)
        প্রত্যাগম ".";

    *p = '\0';

    প্রত্যাগম path;
}

বর্ণ *av_append_path_component(ধ্রুব বর্ণ *path, ধ্রুব বর্ণ *component)
{
    size_t p_len, c_len;
    বর্ণ *fullpath;

    যদি (!path)
        প্রত্যাগম av_strdup(component);
    যদি (!component)
        প্রত্যাগম av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    যদি (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        প্রত্যাগম রিক্ত;
    fullpath = av_malloc(p_len + c_len + 2);
    যদি (fullpath) {
        যদি (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            যদি (c_len) {
                যদি (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                অন্যথা যদি (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    প্রত্যাগম fullpath;
}

পূর্ণাঙ্ক av_escape(বর্ণ **dst, ধ্রুব বর্ণ *src, ধ্রুব বর্ণ *special_chars,
              গণনা AVEscapeMode mode, পূর্ণাঙ্ক flags)
{
    AVBPrint dstbuf;
    পূর্ণাঙ্ক ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    যদি (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, রিক্ত);
        প্রত্যাগম AVERROR(ENOMEM);
    }
    যদি ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        প্রত্যাগম ret;
    প্রত্যাগম dstbuf.len;
}

পূর্ণাঙ্ক av_match_name(ধ্রুব বর্ণ *name, ধ্রুব বর্ণ *names)
{
    ধ্রুব বর্ণ *p;
    size_t len, namelen;

    যদি (!name || !names)
        প্রত্যাগম 0;

    namelen = strlen(name);
    যাবত্ (*names) {
        পূর্ণাঙ্ক negate = '-' == *names;
        p = strchr(names, ',');
        যদি (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        যদি (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            প্রত্যাগম !negate;
        names = p + (*p == ',');
    }
    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_utf8_decode(int32_t *codep, ধ্রুব uint8_t **bufp, ধ্রুব uint8_t *buf_end,
                   unsigned পূর্ণাঙ্ক flags)
{
    ধ্রুব uint8_t *p = *bufp;
    uint32_t শীর্ষ;
    uint64_t code;
    পূর্ণাঙ্ক ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    যদি (p >= buf_end)
        প্রত্যাগম 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    যদি ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        গচ্ছ end;
    }
    শীর্ষ = (code & 128) >> 1;

    tail_len = 0;
    যাবত্ (code & শীর্ষ) {
        পূর্ণাঙ্ক tmp;
        tail_len++;
        যদি (p >= buf_end) {
            (*bufp) ++;
            প্রত্যাগম AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        যদি (tmp>>6) {
            (*bufp) ++;
            প্রত্যাগম AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        শীর্ষ <<= 5;
    }
    code &= (শীর্ষ << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    যদি (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        গচ্ছ end;
    }

    যদি (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        গচ্ছ end;
    }

    *codep = code;

    যদি (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    যদি (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    যদি (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    যদি ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_match_list(ধ্রুব বর্ণ *name, ধ্রুব বর্ণ *list, বর্ণ separator)
{
    ধ্রুব বর্ণ *p, *q;

    প্রতি (p = name; p && *p; ) {
        প্রতি (q = list; q && *q; ) {
            পূর্ণাঙ্ক k;
            প্রতি (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                যদি (k && (!p[k] || p[k] == separator))
                    প্রত্যাগম 1;
            q = strchr(q, separator);
            যদি(q)
                q++;
        }
        p = strchr(p, separator);
        যদি (p)
            p++;
    }

    প্রত্যাগম 0;
}
