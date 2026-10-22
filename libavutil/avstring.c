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

#ଅନ୍ତର୍ଭାଵ <limits.h>
#ଅନ୍ତର୍ଭାଵ <stdarg.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "avstring.h"
#ଅନ୍ତର୍ଭାଵ "bprint.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_strstart(ଅଚଳ ଅକ୍ଷର *str, ଅଚଳ ଅକ୍ଷର *pfx, ଅଚଳ ଅକ୍ଷର **ptr)
{
    ଯେତେବେଳେ (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    ଯଦି (!*pfx && ptr)
        *ptr = str;
    ଫେରନ୍ତୁ !*pfx;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_stristart(ଅଚଳ ଅକ୍ଷର *str, ଅଚଳ ଅକ୍ଷର *pfx, ଅଚଳ ଅକ୍ଷର **ptr)
{
    ଯେତେବେଳେ (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    ଯଦି (!*pfx && ptr)
        *ptr = str;
    ଫେରନ୍ତୁ !*pfx;
}

ଅକ୍ଷର *av_stristr(ଅଚଳ ଅକ୍ଷର *s1, ଅଚଳ ଅକ୍ଷର *s2)
{
    ଯଦି (!*s2)
        ଫେରନ୍ତୁ (ଅକ୍ଷର*)(intptr_t)s1;

    କର
        ଯଦି (av_stristart(s1, s2, ଖାଲି))
            ଫେରନ୍ତୁ (ଅକ୍ଷର*)(intptr_t)s1;
    ଯେତେବେଳେ (*s1++);

    ଫେରନ୍ତୁ ଖାଲି;
}

ଅକ୍ଷର *av_strnstr(ଅଚଳ ଅକ୍ଷର *haystack, ଅଚଳ ଅକ୍ଷର *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    ଯଦି (!needle_len)
        ଫେରନ୍ତୁ (ଅକ୍ଷର*)haystack;
    ଯେତେବେଳେ (hay_length >= needle_len) {
        hay_length--;
        ଯଦି (!memcmp(haystack, needle, needle_len))
            ଫେରନ୍ତୁ (ଅକ୍ଷର*)haystack;
        haystack++;
    }
    ଫେରନ୍ତୁ ଖାଲି;
}

size_t av_strlcpy(ଅକ୍ଷର *dst, ଅଚଳ ଅକ୍ଷର *src, size_t size)
{
    size_t len = 0;
    ଯେତେବେଳେ (++len < size && *src)
        *dst++ = *src++;
    ଯଦି (len <= size)
        *dst = 0;
    ଫେରନ୍ତୁ len + strlen(src) - 1;
}

size_t av_strlcat(ଅକ୍ଷର *dst, ଅଚଳ ଅକ୍ଷର *src, size_t size)
{
    size_t len = strlen(dst);
    ଯଦି (size <= len + 1)
        ଫେରନ୍ତୁ len + strlen(src);
    ଫେରନ୍ତୁ len + av_strlcpy(dst + len, src, size - len);
}

size_t av_strlcatf(ଅକ୍ଷର *dst, size_t size, ଅଚଳ ଅକ୍ଷର *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    va_end(vl);

    ଫେରନ୍ତୁ len;
}

ଅକ୍ଷର *av_asprintf(ଅଚଳ ଅକ୍ଷର *fmt, ...)
{
    ଅକ୍ଷର *p = ଖାଲି;
    va_list va;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା len;

    va_start(va, fmt);
    len = vsnprintf(ଖାଲି, 0, fmt, va);
    va_end(va);
    ଯଦି (len < 0)
        ଯାଅ end;

    p = av_malloc(len + 1);
    ଯଦି (!p)
        ଯାଅ end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    ଯଦି (len < 0)
        av_freep(&p);

end:
    ଫେରନ୍ତୁ p;
}

#define WHITESPACES " \n\t\r"

ଅକ୍ଷର *av_get_token(ଅଚଳ ଅକ୍ଷର **buf, ଅଚଳ ଅକ୍ଷର *term)
{
    ଅକ୍ଷର *out     = av_realloc(ଖାଲି, strlen(*buf) + 1);
    ଅକ୍ଷର *ret     = out, *end = out;
    ଅଚଳ ଅକ୍ଷର *p = *buf;
    ଯଦି (!out)
        ଫେରନ୍ତୁ ଖାଲି;
    p += strspn(p, WHITESPACES);

    ଯେତେବେଳେ (*p && !strspn(p, term)) {
        ଅକ୍ଷର c = *p++;
        ଯଦି (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } ଅନ୍ୟଥା ଯଦି (c == '\'') {
            ଯେତେବେଳେ (*p && *p != '\'')
                *out++ = *p++;
            ଯଦି (*p) {
                p++;
                end = out;
            }
        } ଅନ୍ୟଥା {
            *out++ = c;
        }
    }

    କର
        *out-- = 0;
    ଯେତେବେଳେ (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    ଅକ୍ଷର *small_ret = av_realloc(ret, out - ret + 2);
    ଫେରନ୍ତୁ small_ret ? small_ret : ret;
}

ଅକ୍ଷର *av_strtok(ଅକ୍ଷର *s, ଅଚଳ ଅକ୍ଷର *delim, ଅକ୍ଷର **saveptr)
{
    ଅକ୍ଷର *tok;

    ଯଦି (!s && !(s = *saveptr))
        ଫେରନ୍ତୁ ଖାଲି;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    ଯଦି (!*s) {
        *saveptr = ଖାଲି;
        ଫେରନ୍ତୁ ଖାଲି;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    ଯଦି (*s) {
        *s = 0;
        *saveptr = s+1;
    } ଅନ୍ୟଥା {
        *saveptr = ଖାଲି;
    }

    ଫେରନ୍ତୁ tok;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_strcasecmp(ଅଚଳ ଅକ୍ଷର *a, ଅଚଳ ଅକ୍ଷର *b)
{
    uint8_t c1, c2;
    କର {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ଯେତେବେଳେ (c1 && c1 == c2);
    ଫେରନ୍ତୁ c1 - c2;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_strncasecmp(ଅଚଳ ଅକ୍ଷର *a, ଅଚଳ ଅକ୍ଷର *b, size_t n)
{
    uint8_t c1, c2;
    ଯଦି (n <= 0)
        ଫେରନ୍ତୁ 0;
    କର {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ଯେତେବେଳେ (--n && c1 && c1 == c2);
    ଫେରନ୍ତୁ c1 - c2;
}

ଅକ୍ଷର *av_strireplace(ଅଚଳ ଅକ୍ଷର *str, ଅଚଳ ଅକ୍ଷର *from, ଅଚଳ ଅକ୍ଷର *to)
{
    ଅକ୍ଷର *ret = ଖାଲି;
    ଅଚଳ ଅକ୍ଷର *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    ଯଦି (!fromlen)
        ଫେରନ୍ତୁ av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    ଯେତେବେଳେ ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, strlen(pstr));
    ଯଦି (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, ଖାଲି);
    } ଅନ୍ୟଥା {
        av_bprint_finalize(&pbuf, &ret);
    }

    ଫେରନ୍ତୁ ret;
}

ଅଚଳ ଅକ୍ଷର *av_basename(ଅଚଳ ଅକ୍ଷର *path)
{
    ଯଦି (!path || *path == '\0')
        ଫେରନ୍ତୁ ".";

    ଅଚଳ ଅକ୍ଷର *p = strrchr(path, '/');
#ଯଦି HAVE_DOS_PATHS
    ଅଚଳ ଅକ୍ଷର *q = strrchr(path, '\\');
    ଅଚଳ ଅକ୍ଷର *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    ଯଦି (!p)
        ଫେରନ୍ତୁ path;

    ଫେରନ୍ତୁ p + 1;
}

ଅଚଳ ଅକ୍ଷର *av_dirname(ଅକ୍ଷର *path)
{
    ଅକ୍ଷର *p = path ? strrchr(path, '/') : ଖାଲି;

#ଯଦି HAVE_DOS_PATHS
    ଅକ୍ଷର *q = path ? strrchr(path, '\\') : ଖାଲି;
    ଅକ୍ଷର *d = path ? strchr(path, ':')  : ଖାଲି;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    ଯଦି (!p)
        ଫେରନ୍ତୁ ".";

    *p = '\0';

    ଫେରନ୍ତୁ path;
}

ଅକ୍ଷର *av_append_path_component(ଅଚଳ ଅକ୍ଷର *path, ଅଚଳ ଅକ୍ଷର *component)
{
    size_t p_len, c_len;
    ଅକ୍ଷର *fullpath;

    ଯଦି (!path)
        ଫେରନ୍ତୁ av_strdup(component);
    ଯଦି (!component)
        ଫେରନ୍ତୁ av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    ଯଦି (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        ଫେରନ୍ତୁ ଖାଲି;
    fullpath = av_malloc(p_len + c_len + 2);
    ଯଦି (fullpath) {
        ଯଦି (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            ଯଦି (c_len) {
                ଯଦି (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                ଅନ୍ୟଥା ଯଦି (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    ଫେରନ୍ତୁ fullpath;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_escape(ଅକ୍ଷର **dst, ଅଚଳ ଅକ୍ଷର *src, ଅଚଳ ଅକ୍ଷର *special_chars,
              ଗଣନା AVEscapeMode mode, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVBPrint dstbuf;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    ଯଦି (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, ଖାଲି);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }
    ଯଦି ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        ଫେରନ୍ତୁ ret;
    ଫେରନ୍ତୁ dstbuf.len;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_match_name(ଅଚଳ ଅକ୍ଷର *name, ଅଚଳ ଅକ୍ଷର *names)
{
    ଅଚଳ ଅକ୍ଷର *p;
    size_t len, namelen;

    ଯଦି (!name || !names)
        ଫେରନ୍ତୁ 0;

    namelen = strlen(name);
    ଯେତେବେଳେ (*names) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା negate = '-' == *names;
        p = strchr(names, ',');
        ଯଦି (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        ଯଦି (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            ଫେରନ୍ତୁ !negate;
        names = p + (*p == ',');
    }
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_utf8_decode(int32_t *codep, ଅଚଳ uint8_t **bufp, ଅଚଳ uint8_t *buf_end,
                   unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଅଚଳ uint8_t *p = *bufp;
    uint32_t ଶୀର୍ଷ;
    uint64_t code;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    ଯଦି (p >= buf_end)
        ଫେରନ୍ତୁ 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    ଯଦି ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        ଯାଅ end;
    }
    ଶୀର୍ଷ = (code & 128) >> 1;

    tail_len = 0;
    ଯେତେବେଳେ (code & ଶୀର୍ଷ) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା tmp;
        tail_len++;
        ଯଦି (p >= buf_end) {
            (*bufp) ++;
            ଫେରନ୍ତୁ AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        ଯଦି (tmp>>6) {
            (*bufp) ++;
            ଫେରନ୍ତୁ AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        ଶୀର୍ଷ <<= 5;
    }
    code &= (ଶୀର୍ଷ << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    ଯଦି (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        ଯାଅ end;
    }

    ଯଦି (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        ଯାଅ end;
    }

    *codep = code;

    ଯଦି (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    ଯଦି (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    ଯଦି (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    ଯଦି ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_match_list(ଅଚଳ ଅକ୍ଷର *name, ଅଚଳ ଅକ୍ଷର *list, ଅକ୍ଷର separator)
{
    ଅଚଳ ଅକ୍ଷର *p, *q;

    ପାଇଁ (p = name; p && *p; ) {
        ପାଇଁ (q = list; q && *q; ) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା k;
            ପାଇଁ (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                ଯଦି (k && (!p[k] || p[k] == separator))
                    ଫେରନ୍ତୁ 1;
            q = strchr(q, separator);
            ଯଦି(q)
                q++;
        }
        p = strchr(p, separator);
        ଯଦି (p)
            p++;
    }

    ଫେରନ୍ତୁ 0;
}
