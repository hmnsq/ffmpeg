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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdarg.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "bprint.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"

ਪੂਰਨ av_strstart(ਅਚਲ ਅੱਖਰ *str, ਅਚਲ ਅੱਖਰ *pfx, ਅਚਲ ਅੱਖਰ **ptr)
{
    ਜਦੋਂ (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    ਜੇ (!*pfx && ptr)
        *ptr = str;
    ਵਾਪਸ !*pfx;
}

ਪੂਰਨ av_stristart(ਅਚਲ ਅੱਖਰ *str, ਅਚਲ ਅੱਖਰ *pfx, ਅਚਲ ਅੱਖਰ **ptr)
{
    ਜਦੋਂ (*pfx && av_toupper((ਬਿਨਾਨਿਸ਼ਾਨੀ)*pfx) == av_toupper((ਬਿਨਾਨਿਸ਼ਾਨੀ)*str)) {
        pfx++;
        str++;
    }
    ਜੇ (!*pfx && ptr)
        *ptr = str;
    ਵਾਪਸ !*pfx;
}

ਅੱਖਰ *av_stristr(ਅਚਲ ਅੱਖਰ *s1, ਅਚਲ ਅੱਖਰ *s2)
{
    ਜੇ (!*s2)
        ਵਾਪਸ (ਅੱਖਰ*)(intptr_t)s1;

    ਕਰੋ
        ਜੇ (av_stristart(s1, s2, ਨਿਰਾ))
            ਵਾਪਸ (ਅੱਖਰ*)(intptr_t)s1;
    ਜਦੋਂ (*s1++);

    ਵਾਪਸ ਨਿਰਾ;
}

ਅੱਖਰ *av_strnstr(ਅਚਲ ਅੱਖਰ *haystack, ਅਚਲ ਅੱਖਰ *needle, size_t hay_ਲੰਮਾਈ)
{
    size_t needle_len = ਲੜੀ_ਲੰਬਾਈ(needle);
    ਜੇ (!needle_len)
        ਵਾਪਸ (ਅੱਖਰ*)haystack;
    ਜਦੋਂ (hay_ਲੰਮਾਈ >= needle_len) {
        hay_ਲੰਮਾਈ--;
        ਜੇ (!memcmp(haystack, needle, needle_len))
            ਵਾਪਸ (ਅੱਖਰ*)haystack;
        haystack++;
    }
    ਵਾਪਸ ਨਿਰਾ;
}

size_t av_strlcpy(ਅੱਖਰ *dst, ਅਚਲ ਅੱਖਰ *src, size_t ਮਾਪ)
{
    size_t len = 0;
    ਜਦੋਂ (++len < ਮਾਪ && *src)
        *dst++ = *src++;
    ਜੇ (len <= ਮਾਪ)
        *dst = 0;
    ਵਾਪਸ len + ਲੜੀ_ਲੰਬਾਈ(src) - 1;
}

size_t av_strlcat(ਅੱਖਰ *dst, ਅਚਲ ਅੱਖਰ *src, size_t ਮਾਪ)
{
    size_t len = ਲੜੀ_ਲੰਬਾਈ(dst);
    ਜੇ (ਮਾਪ <= len + 1)
        ਵਾਪਸ len + ਲੜੀ_ਲੰਬਾਈ(src);
    ਵਾਪਸ len + av_strlcpy(dst + len, src, ਮਾਪ - len);
}

size_t av_strlcatf(ਅੱਖਰ *dst, size_t ਮਾਪ, ਅਚਲ ਅੱਖਰ *fmt, ...)
{
    size_t len = ਲੜੀ_ਲੰਬਾਈ(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, ਮਾਪ > len ? ਮਾਪ - len : 0, fmt, vl);
    va_end(vl);

    ਵਾਪਸ len;
}

ਅੱਖਰ *av_asprintf(ਅਚਲ ਅੱਖਰ *fmt, ...)
{
    ਅੱਖਰ *p = ਨਿਰਾ;
    va_list va;
    ਪੂਰਨ len;

    va_start(va, fmt);
    len = vsnprintf(ਨਿਰਾ, 0, fmt, va);
    va_end(va);
    ਜੇ (len < 0)
        ਜਾਓ ਸਿਰਾ;

    p = av_malloc(len + 1);
    ਜੇ (!p)
        ਜਾਓ ਸਿਰਾ;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    ਜੇ (len < 0)
        av_freep(&p);

ਸਿਰਾ:
    ਵਾਪਸ p;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WHITESPACES " \n\t\r"

ਅੱਖਰ *av_get_token(ਅਚਲ ਅੱਖਰ **buf, ਅਚਲ ਅੱਖਰ *ਪਦ)
{
    ਅੱਖਰ *ਬਾਹਰਲਾ     = av_realloc(ਨਿਰਾ, ਲੜੀ_ਲੰਬਾਈ(*buf) + 1);
    ਅੱਖਰ *ret     = ਬਾਹਰਲਾ, *ਸਿਰਾ = ਬਾਹਰਲਾ;
    ਅਚਲ ਅੱਖਰ *p = *buf;
    ਜੇ (!ਬਾਹਰਲਾ)
        ਵਾਪਸ ਨਿਰਾ;
    p += strspn(p, WHITESPACES);

    ਜਦੋਂ (*p && !strspn(p, ਪਦ)) {
        ਅੱਖਰ c = *p++;
        ਜੇ (c == '\\' && *p) {
            *ਬਾਹਰਲਾ++ = *p++;
            ਸਿਰਾ    = ਬਾਹਰਲਾ;
        } ਨਹੀਂਤਾਂ ਜੇ (c == '\'') {
            ਜਦੋਂ (*p && *p != '\'')
                *ਬਾਹਰਲਾ++ = *p++;
            ਜੇ (*p) {
                p++;
                ਸਿਰਾ = ਬਾਹਰਲਾ;
            }
        } ਨਹੀਂਤਾਂ {
            *ਬਾਹਰਲਾ++ = c;
        }
    }

    ਕਰੋ
        *ਬਾਹਰਲਾ-- = 0;
    ਜਦੋਂ (ਬਾਹਰਲਾ >= ਸਿਰਾ && strspn(ਬਾਹਰਲਾ, WHITESPACES));

    *buf = p;

    ਅੱਖਰ *small_ret = av_realloc(ret, ਬਾਹਰਲਾ - ret + 2);
    ਵਾਪਸ small_ret ? small_ret : ret;
}

ਅੱਖਰ *av_strtok(ਅੱਖਰ *s, ਅਚਲ ਅੱਖਰ *delim, ਅੱਖਰ **saveptr)
{
    ਅੱਖਰ *tok;

    ਜੇ (!s && !(s = *saveptr))
        ਵਾਪਸ ਨਿਰਾ;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    ਜੇ (!*s) {
        *saveptr = ਨਿਰਾ;
        ਵਾਪਸ ਨਿਰਾ;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    ਜੇ (*s) {
        *s = 0;
        *saveptr = s+1;
    } ਨਹੀਂਤਾਂ {
        *saveptr = ਨਿਰਾ;
    }

    ਵਾਪਸ tok;
}

ਪੂਰਨ av_strcasecmp(ਅਚਲ ਅੱਖਰ *a, ਅਚਲ ਅੱਖਰ *b)
{
    uint8_t c1, c2;
    ਕਰੋ {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ਜਦੋਂ (c1 && c1 == c2);
    ਵਾਪਸ c1 - c2;
}

ਪੂਰਨ av_strncasecmp(ਅਚਲ ਅੱਖਰ *a, ਅਚਲ ਅੱਖਰ *b, size_t n)
{
    uint8_t c1, c2;
    ਜੇ (n <= 0)
        ਵਾਪਸ 0;
    ਕਰੋ {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ਜਦੋਂ (--n && c1 && c1 == c2);
    ਵਾਪਸ c1 - c2;
}

ਅੱਖਰ *av_strireplace(ਅਚਲ ਅੱਖਰ *str, ਅਚਲ ਅੱਖਰ *from, ਅਚਲ ਅੱਖਰ *ਮੰਜ਼ਿਲ)
{
    ਅੱਖਰ *ret = ਨਿਰਾ;
    ਅਚਲ ਅੱਖਰ *pstr2, *pstr = str;
    size_t tolen = ਲੜੀ_ਲੰਬਾਈ(ਮੰਜ਼ਿਲ), fromlen = ਲੜੀ_ਲੰਬਾਈ(from);
    AVBPrint pbuf;

    ਜੇ (!fromlen)
        ਵਾਪਸ av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_ਮਾਪ_UNLIMITED);
    ਜਦੋਂ ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_ਅੰਕੜੇ(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_ਅੰਕੜੇ(&pbuf, ਮੰਜ਼ਿਲ, tolen);
    }
    av_bprint_append_ਅੰਕੜੇ(&pbuf, pstr, ਲੜੀ_ਲੰਬਾਈ(pstr));
    ਜੇ (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, ਨਿਰਾ);
    } ਨਹੀਂਤਾਂ {
        av_bprint_finalize(&pbuf, &ret);
    }

    ਵਾਪਸ ret;
}

ਅਚਲ ਅੱਖਰ *av_basename(ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    ਜੇ (!ਰਸਤਾ || *ਰਸਤਾ == '\0')
        ਵਾਪਸ ".";

    ਅਚਲ ਅੱਖਰ *p = strrchr(ਰਸਤਾ, '/');
#ਜੇ HAVE_DOS_PATHS
    ਅਚਲ ਅੱਖਰ *q = strrchr(ਰਸਤਾ, '\\');
    ਅਚਲ ਅੱਖਰ *d = strchr(ਰਸਤਾ, ':');
    p = FFMAX3(p, q, d);
#ਜੇ_ਅੰਤ

    ਜੇ (!p)
        ਵਾਪਸ ਰਸਤਾ;

    ਵਾਪਸ p + 1;
}

ਅਚਲ ਅੱਖਰ *av_dirname(ਅੱਖਰ *ਰਸਤਾ)
{
    ਅੱਖਰ *p = ਰਸਤਾ ? strrchr(ਰਸਤਾ, '/') : ਨਿਰਾ;

#ਜੇ HAVE_DOS_PATHS
    ਅੱਖਰ *q = ਰਸਤਾ ? strrchr(ਰਸਤਾ, '\\') : ਨਿਰਾ;
    ਅੱਖਰ *d = ਰਸਤਾ ? strchr(ਰਸਤਾ, ':')  : ਨਿਰਾ;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#ਜੇ_ਅੰਤ

    ਜੇ (!p)
        ਵਾਪਸ ".";

    *p = '\0';

    ਵਾਪਸ ਰਸਤਾ;
}

ਅੱਖਰ *av_append_ਰਸਤਾ_component(ਅਚਲ ਅੱਖਰ *ਰਸਤਾ, ਅਚਲ ਅੱਖਰ *component)
{
    size_t p_len, c_len;
    ਅੱਖਰ *fullpath;

    ਜੇ (!ਰਸਤਾ)
        ਵਾਪਸ av_strdup(component);
    ਜੇ (!component)
        ਵਾਪਸ av_strdup(ਰਸਤਾ);

    p_len = ਲੜੀ_ਲੰਬਾਈ(ਰਸਤਾ);
    c_len = ਲੜੀ_ਲੰਬਾਈ(component);
    ਜੇ (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        ਵਾਪਸ ਨਿਰਾ;
    fullpath = av_malloc(p_len + c_len + 2);
    ਜੇ (fullpath) {
        ਜੇ (p_len) {
            av_strlcpy(fullpath, ਰਸਤਾ, p_len + 1);
            ਜੇ (c_len) {
                ਜੇ (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                ਨਹੀਂਤਾਂ ਜੇ (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    ਵਾਪਸ fullpath;
}

ਪੂਰਨ av_escape(ਅੱਖਰ **dst, ਅਚਲ ਅੱਖਰ *src, ਅਚਲ ਅੱਖਰ *special_chars,
              ਗਿਣਤੀ AVEscape_ਬਹੁਲਕ ਬਹੁਲਕ, ਪੂਰਨ flags)
{
    AVBPrint dstbuf;
    ਪੂਰਨ ret;

    av_bprint_init(&dstbuf, 1, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, ਬਹੁਲਕ, flags);

    ਜੇ (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, ਨਿਰਾ);
        ਵਾਪਸ AVERROR(ENOMEM);
    }
    ਜੇ ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        ਵਾਪਸ ret;
    ਵਾਪਸ dstbuf.len;
}

ਪੂਰਨ av_ਮੇਲ_name(ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *ਨਾਂ)
{
    ਅਚਲ ਅੱਖਰ *p;
    size_t len, namelen;

    ਜੇ (!name || !ਨਾਂ)
        ਵਾਪਸ 0;

    namelen = ਲੜੀ_ਲੰਬਾਈ(name);
    ਜਦੋਂ (*ਨਾਂ) {
        ਪੂਰਨ negate = '-' == *ਨਾਂ;
        p = strchr(ਨਾਂ, ',');
        ਜੇ (!p)
            p = ਨਾਂ + ਲੜੀ_ਲੰਬਾਈ(ਨਾਂ);
        ਨਾਂ += negate;
        len = FFMAX(p - ਨਾਂ, namelen);
        ਜੇ (!av_strncasecmp(name, ਨਾਂ, len) || !ਲੜੀ_ਤੁਲਨਾ("ALL", ਨਾਂ, FFMAX(3, p - ਨਾਂ)))
            ਵਾਪਸ !negate;
        ਨਾਂ = p + (*p == ',');
    }
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_utf8_decode(int32_t *codep, ਅਚਲ uint8_t **bufp, ਅਚਲ uint8_t *buf_ਸਿਰਾ,
                   ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flags)
{
    ਅਚਲ uint8_t *p = *bufp;
    uint32_t ਸਿਖਰ;
    uint64_t ਕੋਡ;
    ਪੂਰਨ ret = 0, ਪੂਛ_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    ਜੇ (p >= buf_ਸਿਰਾ)
        ਵਾਪਸ 0;

    ਕੋਡ = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    ਜੇ ((ਕੋਡ & 0xc0) == 0x80 || ਕੋਡ >= 0xFE) {
        ret = AVERROR(EILSEQ);
        ਜਾਓ ਸਿਰਾ;
    }
    ਸਿਖਰ = (ਕੋਡ & 128) >> 1;

    ਪੂਛ_len = 0;
    ਜਦੋਂ (ਕੋਡ & ਸਿਖਰ) {
        ਪੂਰਨ tmp;
        ਪੂਛ_len++;
        ਜੇ (p >= buf_ਸਿਰਾ) {
            (*bufp) ++;
            ਵਾਪਸ AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        ਜੇ (tmp>>6) {
            (*bufp) ++;
            ਵਾਪਸ AVERROR(EILSEQ);
        }
        ਕੋਡ = (ਕੋਡ<<6) + tmp;
        ਸਿਖਰ <<= 5;
    }
    ਕੋਡ &= (ਸਿਖਰ << 1) - 1;

    /* check for overlong encodings */
    av_assert0(ਪੂਛ_len <= 5);
    ਜੇ (ਕੋਡ < overlong_encoding_mins[ਪੂਛ_len]) {
        ret = AVERROR(EILSEQ);
        ਜਾਓ ਸਿਰਾ;
    }

    ਜੇ (ਕੋਡ >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        ਜਾਓ ਸਿਰਾ;
    }

    *codep = ਕੋਡ;

    ਜੇ (ਕੋਡ > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    ਜੇ (ਕੋਡ < 0x20 && ਕੋਡ != 0x9 && ਕੋਡ != 0xA && ਕੋਡ != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    ਜੇ (ਕੋਡ >= 0xD800 && ਕੋਡ <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    ਜੇ ((ਕੋਡ == 0xFFFE || ਕੋਡ == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

ਸਿਰਾ:
    *bufp = p;
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_ਮੇਲ_list(ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *list, ਅੱਖਰ separator)
{
    ਅਚਲ ਅੱਖਰ *p, *q;

    ਲਈ (p = name; p && *p; ) {
        ਲਈ (q = list; q && *q; ) {
            ਪੂਰਨ k;
            ਲਈ (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                ਜੇ (k && (!p[k] || p[k] == separator))
                    ਵਾਪਸ 1;
            q = strchr(q, separator);
            ਜੇ(q)
                q++;
        }
        p = strchr(p, separator);
        ਜੇ (p)
            p++;
    }

    ਵਾਪਸ 0;
}
