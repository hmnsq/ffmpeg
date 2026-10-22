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

পূর্ণসংখ্যা av_strstart(ধ্রুবক অক্ষর *str, ধ্রুবক অক্ষর *pfx, ধ্রুবক অক্ষর **ptr)
{
    যখন (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    যদি (!*pfx && ptr)
        *ptr = str;
    ফেরত !*pfx;
}

পূর্ণসংখ্যা av_stristart(ধ্রুবক অক্ষর *str, ধ্রুবক অক্ষর *pfx, ধ্রুবক অক্ষর **ptr)
{
    যখন (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    যদি (!*pfx && ptr)
        *ptr = str;
    ফেরত !*pfx;
}

অক্ষর *av_stristr(ধ্রুবক অক্ষর *s1, ধ্রুবক অক্ষর *s2)
{
    যদি (!*s2)
        ফেরত (অক্ষর*)(intptr_t)s1;

    করো
        যদি (av_stristart(s1, s2, ফাঁকা))
            ফেরত (অক্ষর*)(intptr_t)s1;
    যখন (*s1++);

    ফেরত ফাঁকা;
}

অক্ষর *av_strnstr(ধ্রুবক অক্ষর *haystack, ধ্রুবক অক্ষর *needle, size_t hay_দৈর্ঘ্য)
{
    size_t needle_len = strlen(needle);
    যদি (!needle_len)
        ফেরত (অক্ষর*)haystack;
    যখন (hay_দৈর্ঘ্য >= needle_len) {
        hay_দৈর্ঘ্য--;
        যদি (!memcmp(haystack, needle, needle_len))
            ফেরত (অক্ষর*)haystack;
        haystack++;
    }
    ফেরত ফাঁকা;
}

size_t av_strlcpy(অক্ষর *dst, ধ্রুবক অক্ষর *src, size_t আকার_2)
{
    size_t len = 0;
    যখন (++len < আকার_2 && *src)
        *dst++ = *src++;
    যদি (len <= আকার_2)
        *dst = 0;
    ফেরত len + strlen(src) - 1;
}

size_t av_strlcat(অক্ষর *dst, ধ্রুবক অক্ষর *src, size_t আকার_2)
{
    size_t len = strlen(dst);
    যদি (আকার_2 <= len + 1)
        ফেরত len + strlen(src);
    ফেরত len + av_strlcpy(dst + len, src, আকার_2 - len);
}

size_t av_strlcatf(অক্ষর *dst, size_t আকার_2, ধ্রুবক অক্ষর *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, আকার_2 > len ? আকার_2 - len : 0, fmt, vl);
    va_end(vl);

    ফেরত len;
}

অক্ষর *av_asprintf(ধ্রুবক অক্ষর *fmt, ...)
{
    অক্ষর *p = ফাঁকা;
    va_list va;
    পূর্ণসংখ্যা len;

    va_start(va, fmt);
    len = vsnprintf(ফাঁকা, 0, fmt, va);
    va_end(va);
    যদি (len < 0)
        যাও end;

    p = av_malloc(len + 1);
    যদি (!p)
        যাও end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    যদি (len < 0)
        av_freep(&p);

end:
    ফেরত p;
}

#define WHITESPACES " \n\t\r"

অক্ষর *av_get_token(ধ্রুবক অক্ষর **buf, ধ্রুবক অক্ষর *term)
{
    অক্ষর *out     = av_realloc(ফাঁকা, strlen(*buf) + 1);
    অক্ষর *ret     = out, *end = out;
    ধ্রুবক অক্ষর *p = *buf;
    যদি (!out)
        ফেরত ফাঁকা;
    p += strspn(p, WHITESPACES);

    যখন (*p && !strspn(p, term)) {
        অক্ষর c = *p++;
        যদি (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } অন্যথা যদি (c == '\'') {
            যখন (*p && *p != '\'')
                *out++ = *p++;
            যদি (*p) {
                p++;
                end = out;
            }
        } অন্যথা {
            *out++ = c;
        }
    }

    করো
        *out-- = 0;
    যখন (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    অক্ষর *small_ret = av_realloc(ret, out - ret + 2);
    ফেরত small_ret ? small_ret : ret;
}

অক্ষর *av_strtok(অক্ষর *s, ধ্রুবক অক্ষর *delim, অক্ষর **saveptr)
{
    অক্ষর *tok;

    যদি (!s && !(s = *saveptr))
        ফেরত ফাঁকা;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    যদি (!*s) {
        *saveptr = ফাঁকা;
        ফেরত ফাঁকা;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    যদি (*s) {
        *s = 0;
        *saveptr = s+1;
    } অন্যথা {
        *saveptr = ফাঁকা;
    }

    ফেরত tok;
}

পূর্ণসংখ্যা av_strcasecmp(ধ্রুবক অক্ষর *a, ধ্রুবক অক্ষর *b)
{
    uint8_t c1, c2;
    করো {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } যখন (c1 && c1 == c2);
    ফেরত c1 - c2;
}

পূর্ণসংখ্যা av_strncasecmp(ধ্রুবক অক্ষর *a, ধ্রুবক অক্ষর *b, size_t n)
{
    uint8_t c1, c2;
    যদি (n <= 0)
        ফেরত 0;
    করো {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } যখন (--n && c1 && c1 == c2);
    ফেরত c1 - c2;
}

অক্ষর *av_strireplace(ধ্রুবক অক্ষর *str, ধ্রুবক অক্ষর *from, ধ্রুবক অক্ষর *to)
{
    অক্ষর *ret = ফাঁকা;
    ধ্রুবক অক্ষর *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    যদি (!fromlen)
        ফেরত av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_আকার_UNLIMITED);
    যখন ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_তথ্য(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_তথ্য(&pbuf, to, tolen);
    }
    av_bprint_append_তথ্য(&pbuf, pstr, strlen(pstr));
    যদি (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, ফাঁকা);
    } অন্যথা {
        av_bprint_finalize(&pbuf, &ret);
    }

    ফেরত ret;
}

ধ্রুবক অক্ষর *av_basename(ধ্রুবক অক্ষর *path)
{
    যদি (!path || *path == '\0')
        ফেরত ".";

    ধ্রুবক অক্ষর *p = strrchr(path, '/');
#যদি HAVE_DOS_PATHS
    ধ্রুবক অক্ষর *q = strrchr(path, '\\');
    ধ্রুবক অক্ষর *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    যদি (!p)
        ফেরত path;

    ফেরত p + 1;
}

ধ্রুবক অক্ষর *av_dirname(অক্ষর *path)
{
    অক্ষর *p = path ? strrchr(path, '/') : ফাঁকা;

#যদি HAVE_DOS_PATHS
    অক্ষর *q = path ? strrchr(path, '\\') : ফাঁকা;
    অক্ষর *d = path ? strchr(path, ':')  : ফাঁকা;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    যদি (!p)
        ফেরত ".";

    *p = '\0';

    ফেরত path;
}

অক্ষর *av_append_path_component(ধ্রুবক অক্ষর *path, ধ্রুবক অক্ষর *component)
{
    size_t p_len, c_len;
    অক্ষর *fullpath;

    যদি (!path)
        ফেরত av_strdup(component);
    যদি (!component)
        ফেরত av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    যদি (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        ফেরত ফাঁকা;
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
    ফেরত fullpath;
}

পূর্ণসংখ্যা av_escape(অক্ষর **dst, ধ্রুবক অক্ষর *src, ধ্রুবক অক্ষর *special_chars,
              গণনা AVEscapeMode mode, পূর্ণসংখ্যা flags)
{
    AVBPrint dstbuf;
    পূর্ণসংখ্যা ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    যদি (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, ফাঁকা);
        ফেরত AVERROR(ENOMEM);
    }
    যদি ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        ফেরত ret;
    ফেরত dstbuf.len;
}

পূর্ণসংখ্যা av_match_name(ধ্রুবক অক্ষর *name, ধ্রুবক অক্ষর *names)
{
    ধ্রুবক অক্ষর *p;
    size_t len, namelen;

    যদি (!name || !names)
        ফেরত 0;

    namelen = strlen(name);
    যখন (*names) {
        পূর্ণসংখ্যা negate = '-' == *names;
        p = strchr(names, ',');
        যদি (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        যদি (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            ফেরত !negate;
        names = p + (*p == ',');
    }
    ফেরত 0;
}

পূর্ণসংখ্যা av_utf8_decode(int32_t *codep, ধ্রুবক uint8_t **bufp, ধ্রুবক uint8_t *buf_end,
                   unsigned পূর্ণসংখ্যা flags)
{
    ধ্রুবক uint8_t *p = *bufp;
    uint32_t শীর্ষ;
    uint64_t code;
    পূর্ণসংখ্যা ret = 0, লেজ_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    যদি (p >= buf_end)
        ফেরত 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    যদি ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        যাও end;
    }
    শীর্ষ = (code & 128) >> 1;

    লেজ_len = 0;
    যখন (code & শীর্ষ) {
        পূর্ণসংখ্যা tmp;
        লেজ_len++;
        যদি (p >= buf_end) {
            (*bufp) ++;
            ফেরত AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        যদি (tmp>>6) {
            (*bufp) ++;
            ফেরত AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        শীর্ষ <<= 5;
    }
    code &= (শীর্ষ << 1) - 1;

    /* check for overlong encodings */
    av_assert0(লেজ_len <= 5);
    যদি (code < overlong_encoding_mins[লেজ_len]) {
        ret = AVERROR(EILSEQ);
        যাও end;
    }

    যদি (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        যাও end;
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
    ফেরত ret;
}

পূর্ণসংখ্যা av_match_list(ধ্রুবক অক্ষর *name, ধ্রুবক অক্ষর *list, অক্ষর separator)
{
    ধ্রুবক অক্ষর *p, *q;

    জন্য (p = name; p && *p; ) {
        জন্য (q = list; q && *q; ) {
            পূর্ণসংখ্যা k;
            জন্য (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                যদি (k && (!p[k] || p[k] == separator))
                    ফেরত 1;
            q = strchr(q, separator);
            যদি(q)
                q++;
        }
        p = strchr(p, separator);
        যদি (p)
            p++;
    }

    ফেরত 0;
}
