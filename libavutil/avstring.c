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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdarg.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "config.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "avassert.h"
#అన్తర్భావ "avstring.h"
#అన్తర్భావ "bprint.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "macros.h"

పూర్ణాంకం av_strstart(స్థిరరాశి అక్షరం *str, స్థిరరాశి అక్షరం *pfx, స్థిరరాశి అక్షరం **ptr)
{
    అయితే (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    ఒకవేళ (!*pfx && ptr)
        *ptr = str;
    తిరిగి !*pfx;
}

పూర్ణాంకం av_stristart(స్థిరరాశి అక్షరం *str, స్థిరరాశి అక్షరం *pfx, స్థిరరాశి అక్షరం **ptr)
{
    అయితే (*pfx && av_toupper((గుర్తులేని)*pfx) == av_toupper((గుర్తులేని)*str)) {
        pfx++;
        str++;
    }
    ఒకవేళ (!*pfx && ptr)
        *ptr = str;
    తిరిగి !*pfx;
}

అక్షరం *av_stristr(స్థిరరాశి అక్షరం *s1, స్థిరరాశి అక్షరం *s2)
{
    ఒకవేళ (!*s2)
        తిరిగి (అక్షరం*)(intptr_t)s1;

    చేయి
        ఒకవేళ (av_stristart(s1, s2, ఖాళీ))
            తిరిగి (అక్షరం*)(intptr_t)s1;
    అయితే (*s1++);

    తిరిగి ఖాళీ;
}

అక్షరం *av_strnstr(స్థిరరాశి అక్షరం *haystack, స్థిరరాశి అక్షరం *needle, size_t hay_నిడివి)
{
    size_t needle_len = అక్షరశ్రేణి_పొడవు(needle);
    ఒకవేళ (!needle_len)
        తిరిగి (అక్షరం*)haystack;
    అయితే (hay_నిడివి >= needle_len) {
        hay_నిడివి--;
        ఒకవేళ (!memcmp(haystack, needle, needle_len))
            తిరిగి (అక్షరం*)haystack;
        haystack++;
    }
    తిరిగి ఖాళీ;
}

size_t av_strlcpy(అక్షరం *dst, స్థిరరాశి అక్షరం *src, size_t కొలత)
{
    size_t len = 0;
    అయితే (++len < కొలత && *src)
        *dst++ = *src++;
    ఒకవేళ (len <= కొలత)
        *dst = 0;
    తిరిగి len + అక్షరశ్రేణి_పొడవు(src) - 1;
}

size_t av_strlcat(అక్షరం *dst, స్థిరరాశి అక్షరం *src, size_t కొలత)
{
    size_t len = అక్షరశ్రేణి_పొడవు(dst);
    ఒకవేళ (కొలత <= len + 1)
        తిరిగి len + అక్షరశ్రేణి_పొడవు(src);
    తిరిగి len + av_strlcpy(dst + len, src, కొలత - len);
}

size_t av_strlcatf(అక్షరం *dst, size_t కొలత, స్థిరరాశి అక్షరం *fmt, ...)
{
    size_t len = అక్షరశ్రేణి_పొడవు(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, కొలత > len ? కొలత - len : 0, fmt, vl);
    va_end(vl);

    తిరిగి len;
}

అక్షరం *av_asprintf(స్థిరరాశి అక్షరం *fmt, ...)
{
    అక్షరం *p = ఖాళీ;
    va_list va;
    పూర్ణాంకం len;

    va_start(va, fmt);
    len = vsnprintf(ఖాళీ, 0, fmt, va);
    va_end(va);
    ఒకవేళ (len < 0)
        వెళ్ళు చివర;

    p = av_malloc(len + 1);
    ఒకవేళ (!p)
        వెళ్ళు చివర;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    ఒకవేళ (len < 0)
        av_freep(&p);

చివర:
    తిరిగి p;
}

#నిర్వచించు WHITESPACES " \n\t\r"

అక్షరం *av_get_token(స్థిరరాశి అక్షరం **buf, స్థిరరాశి అక్షరం *పదం)
{
    అక్షరం *బహిర్గతం     = av_realloc(ఖాళీ, అక్షరశ్రేణి_పొడవు(*buf) + 1);
    అక్షరం *ret     = బహిర్గతం, *చివర = బహిర్గతం;
    స్థిరరాశి అక్షరం *p = *buf;
    ఒకవేళ (!బహిర్గతం)
        తిరిగి ఖాళీ;
    p += strspn(p, WHITESPACES);

    అయితే (*p && !strspn(p, పదం)) {
        అక్షరం c = *p++;
        ఒకవేళ (c == '\\' && *p) {
            *బహిర్గతం++ = *p++;
            చివర    = బహిర్గతం;
        } లేకపోతే ఒకవేళ (c == '\'') {
            అయితే (*p && *p != '\'')
                *బహిర్గతం++ = *p++;
            ఒకవేళ (*p) {
                p++;
                చివర = బహిర్గతం;
            }
        } లేకపోతే {
            *బహిర్గతం++ = c;
        }
    }

    చేయి
        *బహిర్గతం-- = 0;
    అయితే (బహిర్గతం >= చివర && strspn(బహిర్గతం, WHITESPACES));

    *buf = p;

    అక్షరం *small_ret = av_realloc(ret, బహిర్గతం - ret + 2);
    తిరిగి small_ret ? small_ret : ret;
}

అక్షరం *av_strtok(అక్షరం *s, స్థిరరాశి అక్షరం *delim, అక్షరం **saveptr)
{
    అక్షరం *tok;

    ఒకవేళ (!s && !(s = *saveptr))
        తిరిగి ఖాళీ;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    ఒకవేళ (!*s) {
        *saveptr = ఖాళీ;
        తిరిగి ఖాళీ;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    ఒకవేళ (*s) {
        *s = 0;
        *saveptr = s+1;
    } లేకపోతే {
        *saveptr = ఖాళీ;
    }

    తిరిగి tok;
}

పూర్ణాంకం av_strcasecmp(స్థిరరాశి అక్షరం *a, స్థిరరాశి అక్షరం *b)
{
    uint8_t c1, c2;
    చేయి {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } అయితే (c1 && c1 == c2);
    తిరిగి c1 - c2;
}

పూర్ణాంకం av_strncasecmp(స్థిరరాశి అక్షరం *a, స్థిరరాశి అక్షరం *b, size_t n)
{
    uint8_t c1, c2;
    ఒకవేళ (n <= 0)
        తిరిగి 0;
    చేయి {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } అయితే (--n && c1 && c1 == c2);
    తిరిగి c1 - c2;
}

అక్షరం *av_strireplace(స్థిరరాశి అక్షరం *str, స్థిరరాశి అక్షరం *from, స్థిరరాశి అక్షరం *గమ్యం)
{
    అక్షరం *ret = ఖాళీ;
    స్థిరరాశి అక్షరం *pstr2, *pstr = str;
    size_t tolen = అక్షరశ్రేణి_పొడవు(గమ్యం), fromlen = అక్షరశ్రేణి_పొడవు(from);
    AVBPrint pbuf;

    ఒకవేళ (!fromlen)
        తిరిగి av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_కొలత_UNLIMITED);
    అయితే ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_దత్తాంశం(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_దత్తాంశం(&pbuf, గమ్యం, tolen);
    }
    av_bprint_append_దత్తాంశం(&pbuf, pstr, అక్షరశ్రేణి_పొడవు(pstr));
    ఒకవేళ (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, ఖాళీ);
    } లేకపోతే {
        av_bprint_finalize(&pbuf, &ret);
    }

    తిరిగి ret;
}

స్థిరరాశి అక్షరం *av_basename(స్థిరరాశి అక్షరం *మార్గం)
{
    ఒకవేళ (!మార్గం || *మార్గం == '\0')
        తిరిగి ".";

    స్థిరరాశి అక్షరం *p = strrchr(మార్గం, '/');
#ఒకవేళ HAVE_DOS_PATHS
    స్థిరరాశి అక్షరం *q = strrchr(మార్గం, '\\');
    స్థిరరాశి అక్షరం *d = strchr(మార్గం, ':');
    p = FFMAX3(p, q, d);
#అయితే_ముగింపు

    ఒకవేళ (!p)
        తిరిగి మార్గం;

    తిరిగి p + 1;
}

స్థిరరాశి అక్షరం *av_dirname(అక్షరం *మార్గం)
{
    అక్షరం *p = మార్గం ? strrchr(మార్గం, '/') : ఖాళీ;

#ఒకవేళ HAVE_DOS_PATHS
    అక్షరం *q = మార్గం ? strrchr(మార్గం, '\\') : ఖాళీ;
    అక్షరం *d = మార్గం ? strchr(మార్గం, ':')  : ఖాళీ;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#అయితే_ముగింపు

    ఒకవేళ (!p)
        తిరిగి ".";

    *p = '\0';

    తిరిగి మార్గం;
}

అక్షరం *av_append_మార్గం_component(స్థిరరాశి అక్షరం *మార్గం, స్థిరరాశి అక్షరం *component)
{
    size_t p_len, c_len;
    అక్షరం *fullpath;

    ఒకవేళ (!మార్గం)
        తిరిగి av_strdup(component);
    ఒకవేళ (!component)
        తిరిగి av_strdup(మార్గం);

    p_len = అక్షరశ్రేణి_పొడవు(మార్గం);
    c_len = అక్షరశ్రేణి_పొడవు(component);
    ఒకవేళ (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        తిరిగి ఖాళీ;
    fullpath = av_malloc(p_len + c_len + 2);
    ఒకవేళ (fullpath) {
        ఒకవేళ (p_len) {
            av_strlcpy(fullpath, మార్గం, p_len + 1);
            ఒకవేళ (c_len) {
                ఒకవేళ (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                లేకపోతే ఒకవేళ (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    తిరిగి fullpath;
}

పూర్ణాంకం av_escape(అక్షరం **dst, స్థిరరాశి అక్షరం *src, స్థిరరాశి అక్షరం *special_chars,
              గణన AVEscape_బహుళకం బహుళకం, పూర్ణాంకం flags)
{
    AVBPrint dstbuf;
    పూర్ణాంకం ret;

    av_bprint_init(&dstbuf, 1, గరిష్ఠ_పూర్ణాంకం); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, బహుళకం, flags);

    ఒకవేళ (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, ఖాళీ);
        తిరిగి AVERROR(ENOMEM);
    }
    ఒకవేళ ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        తిరిగి ret;
    తిరిగి dstbuf.len;
}

పూర్ణాంకం av_సరిపోలిక_name(స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *పేర్లు)
{
    స్థిరరాశి అక్షరం *p;
    size_t len, namelen;

    ఒకవేళ (!name || !పేర్లు)
        తిరిగి 0;

    namelen = అక్షరశ్రేణి_పొడవు(name);
    అయితే (*పేర్లు) {
        పూర్ణాంకం negate = '-' == *పేర్లు;
        p = strchr(పేర్లు, ',');
        ఒకవేళ (!p)
            p = పేర్లు + అక్షరశ్రేణి_పొడవు(పేర్లు);
        పేర్లు += negate;
        len = FFMAX(p - పేర్లు, namelen);
        ఒకవేళ (!av_strncasecmp(name, పేర్లు, len) || !అక్షరశ్రేణి_పోలిక("ALL", పేర్లు, FFMAX(3, p - పేర్లు)))
            తిరిగి !negate;
        పేర్లు = p + (*p == ',');
    }
    తిరిగి 0;
}

పూర్ణాంకం av_utf8_decode(int32_t *codep, స్థిరరాశి uint8_t **bufp, స్థిరరాశి uint8_t *buf_చివర,
                   గుర్తులేని పూర్ణాంకం flags)
{
    స్థిరరాశి uint8_t *p = *bufp;
    uint32_t శిఖరం;
    uint64_t సంకేతం_2;
    పూర్ణాంకం ret = 0, తోక_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    ఒకవేళ (p >= buf_చివర)
        తిరిగి 0;

    సంకేతం_2 = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    ఒకవేళ ((సంకేతం_2 & 0xc0) == 0x80 || సంకేతం_2 >= 0xFE) {
        ret = AVERROR(EILSEQ);
        వెళ్ళు చివర;
    }
    శిఖరం = (సంకేతం_2 & 128) >> 1;

    తోక_len = 0;
    అయితే (సంకేతం_2 & శిఖరం) {
        పూర్ణాంకం tmp;
        తోక_len++;
        ఒకవేళ (p >= buf_చివర) {
            (*bufp) ++;
            తిరిగి AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        ఒకవేళ (tmp>>6) {
            (*bufp) ++;
            తిరిగి AVERROR(EILSEQ);
        }
        సంకేతం_2 = (సంకేతం_2<<6) + tmp;
        శిఖరం <<= 5;
    }
    సంకేతం_2 &= (శిఖరం << 1) - 1;

    /* check for overlong encodings */
    av_assert0(తోక_len <= 5);
    ఒకవేళ (సంకేతం_2 < overlong_encoding_mins[తోక_len]) {
        ret = AVERROR(EILSEQ);
        వెళ్ళు చివర;
    }

    ఒకవేళ (సంకేతం_2 >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        వెళ్ళు చివర;
    }

    *codep = సంకేతం_2;

    ఒకవేళ (సంకేతం_2 > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    ఒకవేళ (సంకేతం_2 < 0x20 && సంకేతం_2 != 0x9 && సంకేతం_2 != 0xA && సంకేతం_2 != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    ఒకవేళ (సంకేతం_2 >= 0xD800 && సంకేతం_2 <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    ఒకవేళ ((సంకేతం_2 == 0xFFFE || సంకేతం_2 == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

చివర:
    *bufp = p;
    తిరిగి ret;
}

పూర్ణాంకం av_సరిపోలిక_list(స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *list, అక్షరం separator)
{
    స్థిరరాశి అక్షరం *p, *q;

    కొరకు (p = name; p && *p; ) {
        కొరకు (q = list; q && *q; ) {
            పూర్ణాంకం k;
            కొరకు (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                ఒకవేళ (k && (!p[k] || p[k] == separator))
                    తిరిగి 1;
            q = strchr(q, separator);
            ఒకవేళ(q)
                q++;
        }
        p = strchr(p, separator);
        ఒకవేళ (p)
            p++;
    }

    తిరిగి 0;
}
