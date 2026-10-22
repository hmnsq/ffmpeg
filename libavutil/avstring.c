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

ಪೂರ್ಣಾಂಕ av_strstart(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pfx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **ptr)
{
    ಆಗ (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    ಆದರೆ (!*pfx && ptr)
        *ptr = str;
    ಹಿಂತಿರುಗಿ !*pfx;
}

ಪೂರ್ಣಾಂಕ av_stristart(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pfx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **ptr)
{
    ಆಗ (*pfx && av_toupper((ಚಿಹ್ನೆರಹಿತ)*pfx) == av_toupper((ಚಿಹ್ನೆರಹಿತ)*str)) {
        pfx++;
        str++;
    }
    ಆದರೆ (!*pfx && ptr)
        *ptr = str;
    ಹಿಂತಿರುಗಿ !*pfx;
}

ಅಕ್ಷರ *av_stristr(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s2)
{
    ಆದರೆ (!*s2)
        ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ*)(intptr_t)s1;

    ಮಾಡು
        ಆದರೆ (av_stristart(s1, s2, ಖಾಲಿ))
            ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ*)(intptr_t)s1;
    ಆಗ (*s1++);

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಅಕ್ಷರ *av_strnstr(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *haystack, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *needle, size_t hay_ಉದ್ದಳತೆ)
{
    size_t needle_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(needle);
    ಆದರೆ (!needle_len)
        ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ*)haystack;
    ಆಗ (hay_ಉದ್ದಳತೆ >= needle_len) {
        hay_ಉದ್ದಳತೆ--;
        ಆದರೆ (!memcmp(haystack, needle, needle_len))
            ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ*)haystack;
        haystack++;
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

size_t av_strlcpy(ಅಕ್ಷರ *dst, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src, size_t ಗಾತ್ರ_2)
{
    size_t len = 0;
    ಆಗ (++len < ಗಾತ್ರ_2 && *src)
        *dst++ = *src++;
    ಆದರೆ (len <= ಗಾತ್ರ_2)
        *dst = 0;
    ಹಿಂತಿರುಗಿ len + ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(src) - 1;
}

size_t av_strlcat(ಅಕ್ಷರ *dst, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src, size_t ಗಾತ್ರ_2)
{
    size_t len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(dst);
    ಆದರೆ (ಗಾತ್ರ_2 <= len + 1)
        ಹಿಂತಿರುಗಿ len + ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(src);
    ಹಿಂತಿರುಗಿ len + av_strlcpy(dst + len, src, ಗಾತ್ರ_2 - len);
}

size_t av_strlcatf(ಅಕ್ಷರ *dst, size_t ಗಾತ್ರ_2, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ...)
{
    size_t len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, ಗಾತ್ರ_2 > len ? ಗಾತ್ರ_2 - len : 0, fmt, vl);
    va_end(vl);

    ಹಿಂತಿರುಗಿ len;
}

ಅಕ್ಷರ *av_asprintf(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ...)
{
    ಅಕ್ಷರ *p = ಖಾಲಿ;
    va_list va;
    ಪೂರ್ಣಾಂಕ len;

    va_start(va, fmt);
    len = vsnprintf(ಖಾಲಿ, 0, fmt, va);
    va_end(va);
    ಆದರೆ (len < 0)
        ಹೋಗು ಕೊನೆ;

    p = av_malloc(len + 1);
    ಆದರೆ (!p)
        ಹೋಗು ಕೊನೆ;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    ಆದರೆ (len < 0)
        av_freep(&p);

ಕೊನೆ:
    ಹಿಂತಿರುಗಿ p;
}

#ವ್ಯಾಖ್ಯಾನಿಸು WHITESPACES " \n\t\r"

ಅಕ್ಷರ *av_get_token(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **buf, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪದ)
{
    ಅಕ್ಷರ *ಹೊರಹೋಗು     = av_realloc(ಖಾಲಿ, ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(*buf) + 1);
    ಅಕ್ಷರ *ret     = ಹೊರಹೋಗು, *ಕೊನೆ = ಹೊರಹೋಗು;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p = *buf;
    ಆದರೆ (!ಹೊರಹೋಗು)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    p += strspn(p, WHITESPACES);

    ಆಗ (*p && !strspn(p, ಪದ)) {
        ಅಕ್ಷರ c = *p++;
        ಆದರೆ (c == '\\' && *p) {
            *ಹೊರಹೋಗು++ = *p++;
            ಕೊನೆ    = ಹೊರಹೋಗು;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (c == '\'') {
            ಆಗ (*p && *p != '\'')
                *ಹೊರಹೋಗು++ = *p++;
            ಆದರೆ (*p) {
                p++;
                ಕೊನೆ = ಹೊರಹೋಗು;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            *ಹೊರಹೋಗು++ = c;
        }
    }

    ಮಾಡು
        *ಹೊರಹೋಗು-- = 0;
    ಆಗ (ಹೊರಹೋಗು >= ಕೊನೆ && strspn(ಹೊರಹೋಗು, WHITESPACES));

    *buf = p;

    ಅಕ್ಷರ *small_ret = av_realloc(ret, ಹೊರಹೋಗು - ret + 2);
    ಹಿಂತಿರುಗಿ small_ret ? small_ret : ret;
}

ಅಕ್ಷರ *av_strtok(ಅಕ್ಷರ *s, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *delim, ಅಕ್ಷರ **saveptr)
{
    ಅಕ್ಷರ *tok;

    ಆದರೆ (!s && !(s = *saveptr))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    ಆದರೆ (!*s) {
        *saveptr = ಖಾಲಿ;
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    ಆದರೆ (*s) {
        *s = 0;
        *saveptr = s+1;
    } ಇಲ್ಲದಿದ್ದರೆ {
        *saveptr = ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ tok;
}

ಪೂರ್ಣಾಂಕ av_strcasecmp(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *a, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *b)
{
    uint8_t c1, c2;
    ಮಾಡು {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ಆಗ (c1 && c1 == c2);
    ಹಿಂತಿರುಗಿ c1 - c2;
}

ಪೂರ್ಣಾಂಕ av_strncasecmp(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *a, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *b, size_t n)
{
    uint8_t c1, c2;
    ಆದರೆ (n <= 0)
        ಹಿಂತಿರುಗಿ 0;
    ಮಾಡು {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ಆಗ (--n && c1 && c1 == c2);
    ಹಿಂತಿರುಗಿ c1 - c2;
}

ಅಕ್ಷರ *av_strireplace(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *from, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಗಮ್ಯ)
{
    ಅಕ್ಷರ *ret = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pstr2, *pstr = str;
    size_t tolen = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(ಗಮ್ಯ), fromlen = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(from);
    AVBPrint pbuf;

    ಆದರೆ (!fromlen)
        ಹಿಂತಿರುಗಿ av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_ಗಾತ್ರ_UNLIMITED);
    ಆಗ ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_ದತ್ತಾಂಶ(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_ದತ್ತಾಂಶ(&pbuf, ಗಮ್ಯ, tolen);
    }
    av_bprint_append_ದತ್ತಾಂಶ(&pbuf, pstr, ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(pstr));
    ಆದರೆ (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, ಖಾಲಿ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_bprint_finalize(&pbuf, &ret);
    }

    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_basename(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    ಆದರೆ (!ಮಾರ್ಗ || *ಮಾರ್ಗ == '\0')
        ಹಿಂತಿರುಗಿ ".";

    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p = strrchr(ಮಾರ್ಗ, '/');
#ಆದರೆ HAVE_DOS_PATHS
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *q = strrchr(ಮಾರ್ಗ, '\\');
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *d = strchr(ಮಾರ್ಗ, ':');
    p = FFMAX3(p, q, d);
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!p)
        ಹಿಂತಿರುಗಿ ಮಾರ್ಗ;

    ಹಿಂತಿರುಗಿ p + 1;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_dirname(ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    ಅಕ್ಷರ *p = ಮಾರ್ಗ ? strrchr(ಮಾರ್ಗ, '/') : ಖಾಲಿ;

#ಆದರೆ HAVE_DOS_PATHS
    ಅಕ್ಷರ *q = ಮಾರ್ಗ ? strrchr(ಮಾರ್ಗ, '\\') : ಖಾಲಿ;
    ಅಕ್ಷರ *d = ಮಾರ್ಗ ? strchr(ಮಾರ್ಗ, ':')  : ಖಾಲಿ;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!p)
        ಹಿಂತಿರುಗಿ ".";

    *p = '\0';

    ಹಿಂತಿರುಗಿ ಮಾರ್ಗ;
}

ಅಕ್ಷರ *av_append_ಮಾರ್ಗ_component(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *component)
{
    size_t p_len, c_len;
    ಅಕ್ಷರ *fullpath;

    ಆದರೆ (!ಮಾರ್ಗ)
        ಹಿಂತಿರುಗಿ av_strdup(component);
    ಆದರೆ (!component)
        ಹಿಂತಿರುಗಿ av_strdup(ಮಾರ್ಗ);

    p_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(ಮಾರ್ಗ);
    c_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(component);
    ಆದರೆ (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    fullpath = av_malloc(p_len + c_len + 2);
    ಆದರೆ (fullpath) {
        ಆದರೆ (p_len) {
            av_strlcpy(fullpath, ಮಾರ್ಗ, p_len + 1);
            ಆದರೆ (c_len) {
                ಆದರೆ (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    ಹಿಂತಿರುಗಿ fullpath;
}

ಪೂರ್ಣಾಂಕ av_escape(ಅಕ್ಷರ **dst, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *special_chars,
              ಎಣಿಕೆ AVEscape_ಬಹುಲಕ ಬಹುಲಕ, ಪೂರ್ಣಾಂಕ flags)
{
    AVBPrint dstbuf;
    ಪೂರ್ಣಾಂಕ ret;

    av_bprint_init(&dstbuf, 1, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, ಬಹುಲಕ, flags);

    ಆದರೆ (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, ಖಾಲಿ);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }
    ಆದರೆ ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಹಿಂತಿರುಗಿ dstbuf.len;
}

ಪೂರ್ಣಾಂಕ av_ಹೊಂದಿಕೆ_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಹೆಸರುಗಳು)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p;
    size_t len, namelen;

    ಆದರೆ (!name || !ಹೆಸರುಗಳು)
        ಹಿಂತಿರುಗಿ 0;

    namelen = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(name);
    ಆಗ (*ಹೆಸರುಗಳು) {
        ಪೂರ್ಣಾಂಕ negate = '-' == *ಹೆಸರುಗಳು;
        p = strchr(ಹೆಸರುಗಳು, ',');
        ಆದರೆ (!p)
            p = ಹೆಸರುಗಳು + ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(ಹೆಸರುಗಳು);
        ಹೆಸರುಗಳು += negate;
        len = FFMAX(p - ಹೆಸರುಗಳು, namelen);
        ಆದರೆ (!av_strncasecmp(name, ಹೆಸರುಗಳು, len) || !ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ("ALL", ಹೆಸರುಗಳು, FFMAX(3, p - ಹೆಸರುಗಳು)))
            ಹಿಂತಿರುಗಿ !negate;
        ಹೆಸರುಗಳು = p + (*p == ',');
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_utf8_decode(int32_t *codep, ಸ್ಥಿರಾಂಕ uint8_t **bufp, ಸ್ಥಿರಾಂಕ uint8_t *buf_ಕೊನೆ,
                   ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flags)
{
    ಸ್ಥಿರಾಂಕ uint8_t *p = *bufp;
    uint32_t ತುದಿ;
    uint64_t ಸಂಕೇತ_2;
    ಪೂರ್ಣಾಂಕ ret = 0, ಬಾಲ_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    ಆದರೆ (p >= buf_ಕೊನೆ)
        ಹಿಂತಿರುಗಿ 0;

    ಸಂಕೇತ_2 = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    ಆದರೆ ((ಸಂಕೇತ_2 & 0xc0) == 0x80 || ಸಂಕೇತ_2 >= 0xFE) {
        ret = AVERROR(EILSEQ);
        ಹೋಗು ಕೊನೆ;
    }
    ತುದಿ = (ಸಂಕೇತ_2 & 128) >> 1;

    ಬಾಲ_len = 0;
    ಆಗ (ಸಂಕೇತ_2 & ತುದಿ) {
        ಪೂರ್ಣಾಂಕ tmp;
        ಬಾಲ_len++;
        ಆದರೆ (p >= buf_ಕೊನೆ) {
            (*bufp) ++;
            ಹಿಂತಿರುಗಿ AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        ಆದರೆ (tmp>>6) {
            (*bufp) ++;
            ಹಿಂತಿರುಗಿ AVERROR(EILSEQ);
        }
        ಸಂಕೇತ_2 = (ಸಂಕೇತ_2<<6) + tmp;
        ತುದಿ <<= 5;
    }
    ಸಂಕೇತ_2 &= (ತುದಿ << 1) - 1;

    /* check for overlong encodings */
    av_assert0(ಬಾಲ_len <= 5);
    ಆದರೆ (ಸಂಕೇತ_2 < overlong_encoding_mins[ಬಾಲ_len]) {
        ret = AVERROR(EILSEQ);
        ಹೋಗು ಕೊನೆ;
    }

    ಆದರೆ (ಸಂಕೇತ_2 >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        ಹೋಗು ಕೊನೆ;
    }

    *codep = ಸಂಕೇತ_2;

    ಆದರೆ (ಸಂಕೇತ_2 > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    ಆದರೆ (ಸಂಕೇತ_2 < 0x20 && ಸಂಕೇತ_2 != 0x9 && ಸಂಕೇತ_2 != 0xA && ಸಂಕೇತ_2 != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    ಆದರೆ (ಸಂಕೇತ_2 >= 0xD800 && ಸಂಕೇತ_2 <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    ಆದರೆ ((ಸಂಕೇತ_2 == 0xFFFE || ಸಂಕೇತ_2 == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

ಕೊನೆ:
    *bufp = p;
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_ಹೊಂದಿಕೆ_list(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *list, ಅಕ್ಷರ separator)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p, *q;

    ಗಾಗಿ (p = name; p && *p; ) {
        ಗಾಗಿ (q = list; q && *q; ) {
            ಪೂರ್ಣಾಂಕ k;
            ಗಾಗಿ (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                ಆದರೆ (k && (!p[k] || p[k] == separator))
                    ಹಿಂತಿರುಗಿ 1;
            q = strchr(q, separator);
            ಆದರೆ(q)
                q++;
        }
        p = strchr(p, separator);
        ಆದರೆ (p)
            p++;
    }

    ಹಿಂತಿರುಗಿ 0;
}
