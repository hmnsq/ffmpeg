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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdarg.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "config.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "avassert.h"
#अन्तर्भाव "avstring.h"
#अन्तर्भाव "bprint.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "macros.h"

पूर्णाङ्क av_strstart(ध्रुव वर्ण *str, ध्रुव वर्ण *pfx, ध्रुव वर्ण **ptr)
{
    यावत् (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    यदि (!*pfx && ptr)
        *ptr = str;
    प्रत्यागम !*pfx;
}

पूर्णाङ्क av_stristart(ध्रुव वर्ण *str, ध्रुव वर्ण *pfx, ध्रुव वर्ण **ptr)
{
    यावत् (*pfx && av_toupper((अचिह्नित)*pfx) == av_toupper((अचिह्नित)*str)) {
        pfx++;
        str++;
    }
    यदि (!*pfx && ptr)
        *ptr = str;
    प्रत्यागम !*pfx;
}

वर्ण *av_stristr(ध्रुव वर्ण *s1, ध्रुव वर्ण *s2)
{
    यदि (!*s2)
        प्रत्यागम (वर्ण*)(intptr_t)s1;

    कुरु
        यदि (av_stristart(s1, s2, रिक्त))
            प्रत्यागम (वर्ण*)(intptr_t)s1;
    यावत् (*s1++);

    प्रत्यागम रिक्त;
}

वर्ण *av_strnstr(ध्रुव वर्ण *haystack, ध्रुव वर्ण *needle, size_t hay_दीर्घता)
{
    size_t needle_len = वाक्यदैर्घ्यम्(needle);
    यदि (!needle_len)
        प्रत्यागम (वर्ण*)haystack;
    यावत् (hay_दीर्घता >= needle_len) {
        hay_दीर्घता--;
        यदि (!memcmp(haystack, needle, needle_len))
            प्रत्यागम (वर्ण*)haystack;
        haystack++;
    }
    प्रत्यागम रिक्त;
}

size_t av_strlcpy(वर्ण *dst, ध्रुव वर्ण *src, size_t आकार)
{
    size_t len = 0;
    यावत् (++len < आकार && *src)
        *dst++ = *src++;
    यदि (len <= आकार)
        *dst = 0;
    प्रत्यागम len + वाक्यदैर्घ्यम्(src) - 1;
}

size_t av_strlcat(वर्ण *dst, ध्रुव वर्ण *src, size_t आकार)
{
    size_t len = वाक्यदैर्घ्यम्(dst);
    यदि (आकार <= len + 1)
        प्रत्यागम len + वाक्यदैर्घ्यम्(src);
    प्रत्यागम len + av_strlcpy(dst + len, src, आकार - len);
}

size_t av_strlcatf(वर्ण *dst, size_t आकार, ध्रुव वर्ण *fmt, ...)
{
    size_t len = वाक्यदैर्घ्यम्(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, आकार > len ? आकार - len : 0, fmt, vl);
    va_end(vl);

    प्रत्यागम len;
}

वर्ण *av_asprintf(ध्रुव वर्ण *fmt, ...)
{
    वर्ण *p = रिक्त;
    va_list va;
    पूर्णाङ्क len;

    va_start(va, fmt);
    len = vsnprintf(रिक्त, 0, fmt, va);
    va_end(va);
    यदि (len < 0)
        गच्छ अन्तः_2;

    p = av_malloc(len + 1);
    यदि (!p)
        गच्छ अन्तः_2;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    यदि (len < 0)
        av_freep(&p);

अन्तः_2:
    प्रत्यागम p;
}

#परिभाषय WHITESPACES " \n\t\r"

वर्ण *av_get_token(ध्रुव वर्ण **buf, ध्रुव वर्ण *पदांशः)
{
    वर्ण *बहिर्गमनम्     = av_realloc(रिक्त, वाक्यदैर्घ्यम्(*buf) + 1);
    वर्ण *ret     = बहिर्गमनम्, *अन्तः_2 = बहिर्गमनम्;
    ध्रुव वर्ण *p = *buf;
    यदि (!बहिर्गमनम्)
        प्रत्यागम रिक्त;
    p += strspn(p, WHITESPACES);

    यावत् (*p && !strspn(p, पदांशः)) {
        वर्ण c = *p++;
        यदि (c == '\\' && *p) {
            *बहिर्गमनम्++ = *p++;
            अन्तः_2    = बहिर्गमनम्;
        } अन्यथा यदि (c == '\'') {
            यावत् (*p && *p != '\'')
                *बहिर्गमनम्++ = *p++;
            यदि (*p) {
                p++;
                अन्तः_2 = बहिर्गमनम्;
            }
        } अन्यथा {
            *बहिर्गमनम्++ = c;
        }
    }

    कुरु
        *बहिर्गमनम्-- = 0;
    यावत् (बहिर्गमनम् >= अन्तः_2 && strspn(बहिर्गमनम्, WHITESPACES));

    *buf = p;

    वर्ण *small_ret = av_realloc(ret, बहिर्गमनम् - ret + 2);
    प्रत्यागम small_ret ? small_ret : ret;
}

वर्ण *av_strtok(वर्ण *s, ध्रुव वर्ण *delim, वर्ण **saveptr)
{
    वर्ण *tok;

    यदि (!s && !(s = *saveptr))
        प्रत्यागम रिक्त;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    यदि (!*s) {
        *saveptr = रिक्त;
        प्रत्यागम रिक्त;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    यदि (*s) {
        *s = 0;
        *saveptr = s+1;
    } अन्यथा {
        *saveptr = रिक्त;
    }

    प्रत्यागम tok;
}

पूर्णाङ्क av_strcasecmp(ध्रुव वर्ण *a, ध्रुव वर्ण *b)
{
    uint8_t c1, c2;
    कुरु {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } यावत् (c1 && c1 == c2);
    प्रत्यागम c1 - c2;
}

पूर्णाङ्क av_strncasecmp(ध्रुव वर्ण *a, ध्रुव वर्ण *b, size_t n)
{
    uint8_t c1, c2;
    यदि (n <= 0)
        प्रत्यागम 0;
    कुरु {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } यावत् (--n && c1 && c1 == c2);
    प्रत्यागम c1 - c2;
}

वर्ण *av_strireplace(ध्रुव वर्ण *str, ध्रुव वर्ण *from, ध्रुव वर्ण *गन्तव्यम्)
{
    वर्ण *ret = रिक्त;
    ध्रुव वर्ण *pstr2, *pstr = str;
    size_t tolen = वाक्यदैर्घ्यम्(गन्तव्यम्), fromlen = वाक्यदैर्घ्यम्(from);
    AVBPrint pbuf;

    यदि (!fromlen)
        प्रत्यागम av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_आकार_UNLIMITED);
    यावत् ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_दत्त(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_दत्त(&pbuf, गन्तव्यम्, tolen);
    }
    av_bprint_append_दत्त(&pbuf, pstr, वाक्यदैर्घ्यम्(pstr));
    यदि (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, रिक्त);
    } अन्यथा {
        av_bprint_finalize(&pbuf, &ret);
    }

    प्रत्यागम ret;
}

ध्रुव वर्ण *av_basename(ध्रुव वर्ण *मार्गः)
{
    यदि (!मार्गः || *मार्गः == '\0')
        प्रत्यागम ".";

    ध्रुव वर्ण *p = strrchr(मार्गः, '/');
#यदि HAVE_DOS_PATHS
    ध्रुव वर्ण *q = strrchr(मार्गः, '\\');
    ध्रुव वर्ण *d = strchr(मार्गः, ':');
    p = FFMAX3(p, q, d);
#यदि_अन्तः

    यदि (!p)
        प्रत्यागम मार्गः;

    प्रत्यागम p + 1;
}

ध्रुव वर्ण *av_dirname(वर्ण *मार्गः)
{
    वर्ण *p = मार्गः ? strrchr(मार्गः, '/') : रिक्त;

#यदि HAVE_DOS_PATHS
    वर्ण *q = मार्गः ? strrchr(मार्गः, '\\') : रिक्त;
    वर्ण *d = मार्गः ? strchr(मार्गः, ':')  : रिक्त;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#यदि_अन्तः

    यदि (!p)
        प्रत्यागम ".";

    *p = '\0';

    प्रत्यागम मार्गः;
}

वर्ण *av_append_मार्गः_component(ध्रुव वर्ण *मार्गः, ध्रुव वर्ण *component)
{
    size_t p_len, c_len;
    वर्ण *fullpath;

    यदि (!मार्गः)
        प्रत्यागम av_strdup(component);
    यदि (!component)
        प्रत्यागम av_strdup(मार्गः);

    p_len = वाक्यदैर्घ्यम्(मार्गः);
    c_len = वाक्यदैर्घ्यम्(component);
    यदि (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        प्रत्यागम रिक्त;
    fullpath = av_malloc(p_len + c_len + 2);
    यदि (fullpath) {
        यदि (p_len) {
            av_strlcpy(fullpath, मार्गः, p_len + 1);
            यदि (c_len) {
                यदि (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                अन्यथा यदि (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    प्रत्यागम fullpath;
}

पूर्णाङ्क av_escape(वर्ण **dst, ध्रुव वर्ण *src, ध्रुव वर्ण *special_chars,
              गणना AVEscape_बहुलकम् बहुलकम्, पूर्णाङ्क flags)
{
    AVBPrint dstbuf;
    पूर्णाङ्क ret;

    av_bprint_init(&dstbuf, 1, अधिकतम_पूर्णाङ्कः); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, बहुलकम्, flags);

    यदि (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, रिक्त);
        प्रत्यागम AVERROR(ENOMEM);
    }
    यदि ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        प्रत्यागम ret;
    प्रत्यागम dstbuf.len;
}

पूर्णाङ्क av_मेलनम्_name(ध्रुव वर्ण *name, ध्रुव वर्ण *नामानि)
{
    ध्रुव वर्ण *p;
    size_t len, namelen;

    यदि (!name || !नामानि)
        प्रत्यागम 0;

    namelen = वाक्यदैर्घ्यम्(name);
    यावत् (*नामानि) {
        पूर्णाङ्क negate = '-' == *नामानि;
        p = strchr(नामानि, ',');
        यदि (!p)
            p = नामानि + वाक्यदैर्घ्यम्(नामानि);
        नामानि += negate;
        len = FFMAX(p - नामानि, namelen);
        यदि (!av_strncasecmp(name, नामानि, len) || !वाक्ये_तुलय("ALL", नामानि, FFMAX(3, p - नामानि)))
            प्रत्यागम !negate;
        नामानि = p + (*p == ',');
    }
    प्रत्यागम 0;
}

पूर्णाङ्क av_utf8_decode(int32_t *codep, ध्रुव uint8_t **bufp, ध्रुव uint8_t *buf_अन्तः,
                   अचिह्नित पूर्णाङ्क flags)
{
    ध्रुव uint8_t *p = *bufp;
    uint32_t शिखरम्;
    uint64_t संहिता;
    पूर्णाङ्क ret = 0, पुच्छ_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    यदि (p >= buf_अन्तः)
        प्रत्यागम 0;

    संहिता = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    यदि ((संहिता & 0xc0) == 0x80 || संहिता >= 0xFE) {
        ret = AVERROR(EILSEQ);
        गच्छ अन्तः_2;
    }
    शिखरम् = (संहिता & 128) >> 1;

    पुच्छ_len = 0;
    यावत् (संहिता & शिखरम्) {
        पूर्णाङ्क tmp;
        पुच्छ_len++;
        यदि (p >= buf_अन्तः) {
            (*bufp) ++;
            प्रत्यागम AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        यदि (tmp>>6) {
            (*bufp) ++;
            प्रत्यागम AVERROR(EILSEQ);
        }
        संहिता = (संहिता<<6) + tmp;
        शिखरम् <<= 5;
    }
    संहिता &= (शिखरम् << 1) - 1;

    /* check for overlong encodings */
    av_assert0(पुच्छ_len <= 5);
    यदि (संहिता < overlong_encoding_mins[पुच्छ_len]) {
        ret = AVERROR(EILSEQ);
        गच्छ अन्तः_2;
    }

    यदि (संहिता >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        गच्छ अन्तः_2;
    }

    *codep = संहिता;

    यदि (संहिता > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    यदि (संहिता < 0x20 && संहिता != 0x9 && संहिता != 0xA && संहिता != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    यदि (संहिता >= 0xD800 && संहिता <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    यदि ((संहिता == 0xFFFE || संहिता == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

अन्तः_2:
    *bufp = p;
    प्रत्यागम ret;
}

पूर्णाङ्क av_मेलनम्_list(ध्रुव वर्ण *name, ध्रुव वर्ण *list, वर्ण separator)
{
    ध्रुव वर्ण *p, *q;

    प्रति (p = name; p && *p; ) {
        प्रति (q = list; q && *q; ) {
            पूर्णाङ्क k;
            प्रति (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                यदि (k && (!p[k] || p[k] == separator))
                    प्रत्यागम 1;
            q = strchr(q, separator);
            यदि(q)
                q++;
        }
        p = strchr(p, separator);
        यदि (p)
            p++;
    }

    प्रत्यागम 0;
}
