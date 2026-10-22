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

#شامل <limits.h>
#شامل <stdarg.h>
#شامل <stdint.h>
#شامل <stdio.h>
#شامل <string.h>

#شامل "config.h"
#شامل "mem.h"
#شامل "avassert.h"
#شامل "avstring.h"
#شامل "bprint.h"
#شامل "error.h"
#شامل "macros.h"

صحیح av_strstart(ثابت حرف *str, ثابت حرف *pfx, ثابت حرف **ptr)
{
    جب (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    اگر (!*pfx && ptr)
        *ptr = str;
    واپس !*pfx;
}

صحیح av_stristart(ثابت حرف *str, ثابت حرف *pfx, ثابت حرف **ptr)
{
    جب (*pfx && av_toupper((غیرعلامتی)*pfx) == av_toupper((غیرعلامتی)*str)) {
        pfx++;
        str++;
    }
    اگر (!*pfx && ptr)
        *ptr = str;
    واپس !*pfx;
}

حرف *av_stristr(ثابت حرف *s1, ثابت حرف *s2)
{
    اگر (!*s2)
        واپس (حرف*)(intptr_t)s1;

    کرو
        اگر (av_stristart(s1, s2, تہی))
            واپس (حرف*)(intptr_t)s1;
    جب (*s1++);

    واپس تہی;
}

حرف *av_strnstr(ثابت حرف *haystack, ثابت حرف *needle, size_t hay_لمبائی)
{
    size_t needle_len = لڑی_لمبائی(needle);
    اگر (!needle_len)
        واپس (حرف*)haystack;
    جب (hay_لمبائی >= needle_len) {
        hay_لمبائی--;
        اگر (!memcmp(haystack, needle, needle_len))
            واپس (حرف*)haystack;
        haystack++;
    }
    واپس تہی;
}

size_t av_strlcpy(حرف *dst, ثابت حرف *src, size_t سائز)
{
    size_t len = 0;
    جب (++len < سائز && *src)
        *dst++ = *src++;
    اگر (len <= سائز)
        *dst = 0;
    واپس len + لڑی_لمبائی(src) - 1;
}

size_t av_strlcat(حرف *dst, ثابت حرف *src, size_t سائز)
{
    size_t len = لڑی_لمبائی(dst);
    اگر (سائز <= len + 1)
        واپس len + لڑی_لمبائی(src);
    واپس len + av_strlcpy(dst + len, src, سائز - len);
}

size_t av_strlcatf(حرف *dst, size_t سائز, ثابت حرف *fmt, ...)
{
    size_t len = لڑی_لمبائی(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, سائز > len ? سائز - len : 0, fmt, vl);
    va_end(vl);

    واپس len;
}

حرف *av_asprintf(ثابت حرف *fmt, ...)
{
    حرف *p = تہی;
    va_list va;
    صحیح len;

    va_start(va, fmt);
    len = vsnprintf(تہی, 0, fmt, va);
    va_end(va);
    اگر (len < 0)
        جاؤ انتہا;

    p = av_malloc(len + 1);
    اگر (!p)
        جاؤ انتہا;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    اگر (len < 0)
        av_freep(&p);

انتہا:
    واپس p;
}

#تعریف_کرو WHITESPACES " \n\t\r"

حرف *av_get_token(ثابت حرف **buf, ثابت حرف *رکن)
{
    حرف *برآمد     = av_realloc(تہی, لڑی_لمبائی(*buf) + 1);
    حرف *ret     = برآمد, *انتہا = برآمد;
    ثابت حرف *p = *buf;
    اگر (!برآمد)
        واپس تہی;
    p += strspn(p, WHITESPACES);

    جب (*p && !strspn(p, رکن)) {
        حرف c = *p++;
        اگر (c == '\\' && *p) {
            *برآمد++ = *p++;
            انتہا    = برآمد;
        } ورنہ اگر (c == '\'') {
            جب (*p && *p != '\'')
                *برآمد++ = *p++;
            اگر (*p) {
                p++;
                انتہا = برآمد;
            }
        } ورنہ {
            *برآمد++ = c;
        }
    }

    کرو
        *برآمد-- = 0;
    جب (برآمد >= انتہا && strspn(برآمد, WHITESPACES));

    *buf = p;

    حرف *small_ret = av_realloc(ret, برآمد - ret + 2);
    واپس small_ret ? small_ret : ret;
}

حرف *av_strtok(حرف *s, ثابت حرف *delim, حرف **saveptr)
{
    حرف *tok;

    اگر (!s && !(s = *saveptr))
        واپس تہی;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    اگر (!*s) {
        *saveptr = تہی;
        واپس تہی;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    اگر (*s) {
        *s = 0;
        *saveptr = s+1;
    } ورنہ {
        *saveptr = تہی;
    }

    واپس tok;
}

صحیح av_strcasecmp(ثابت حرف *a, ثابت حرف *b)
{
    uint8_t c1, c2;
    کرو {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } جب (c1 && c1 == c2);
    واپس c1 - c2;
}

صحیح av_strncasecmp(ثابت حرف *a, ثابت حرف *b, size_t n)
{
    uint8_t c1, c2;
    اگر (n <= 0)
        واپس 0;
    کرو {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } جب (--n && c1 && c1 == c2);
    واپس c1 - c2;
}

حرف *av_strireplace(ثابت حرف *str, ثابت حرف *from, ثابت حرف *مقصد)
{
    حرف *ret = تہی;
    ثابت حرف *pstr2, *pstr = str;
    size_t tolen = لڑی_لمبائی(مقصد), fromlen = لڑی_لمبائی(from);
    AVBPrint pbuf;

    اگر (!fromlen)
        واپس av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_سائز_UNLIMITED);
    جب ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_ڈیٹا(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_ڈیٹا(&pbuf, مقصد, tolen);
    }
    av_bprint_append_ڈیٹا(&pbuf, pstr, لڑی_لمبائی(pstr));
    اگر (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, تہی);
    } ورنہ {
        av_bprint_finalize(&pbuf, &ret);
    }

    واپس ret;
}

ثابت حرف *av_basename(ثابت حرف *راستہ)
{
    اگر (!راستہ || *راستہ == '\0')
        واپس ".";

    ثابت حرف *p = strrchr(راستہ, '/');
#اگر HAVE_DOS_PATHS
    ثابت حرف *q = strrchr(راستہ, '\\');
    ثابت حرف *d = strchr(راستہ, ':');
    p = FFMAX3(p, q, d);
#اگر_ختم

    اگر (!p)
        واپس راستہ;

    واپس p + 1;
}

ثابت حرف *av_dirname(حرف *راستہ)
{
    حرف *p = راستہ ? strrchr(راستہ, '/') : تہی;

#اگر HAVE_DOS_PATHS
    حرف *q = راستہ ? strrchr(راستہ, '\\') : تہی;
    حرف *d = راستہ ? strchr(راستہ, ':')  : تہی;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#اگر_ختم

    اگر (!p)
        واپس ".";

    *p = '\0';

    واپس راستہ;
}

حرف *av_append_راستہ_component(ثابت حرف *راستہ, ثابت حرف *component)
{
    size_t p_len, c_len;
    حرف *fullpath;

    اگر (!راستہ)
        واپس av_strdup(component);
    اگر (!component)
        واپس av_strdup(راستہ);

    p_len = لڑی_لمبائی(راستہ);
    c_len = لڑی_لمبائی(component);
    اگر (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        واپس تہی;
    fullpath = av_malloc(p_len + c_len + 2);
    اگر (fullpath) {
        اگر (p_len) {
            av_strlcpy(fullpath, راستہ, p_len + 1);
            اگر (c_len) {
                اگر (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                ورنہ اگر (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    واپس fullpath;
}

صحیح av_escape(حرف **dst, ثابت حرف *src, ثابت حرف *special_chars,
              شمار AVEscape_منوال منوال, صحیح flags)
{
    AVBPrint dstbuf;
    صحیح ret;

    av_bprint_init(&dstbuf, 1, زیادہ_سے_زیادہ_عدد); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, منوال, flags);

    اگر (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, تہی);
        واپس AVERROR(ENOMEM);
    }
    اگر ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        واپس ret;
    واپس dstbuf.len;
}

صحیح av_مطابقت_name(ثابت حرف *name, ثابت حرف *نام)
{
    ثابت حرف *p;
    size_t len, namelen;

    اگر (!name || !نام)
        واپس 0;

    namelen = لڑی_لمبائی(name);
    جب (*نام) {
        صحیح negate = '-' == *نام;
        p = strchr(نام, ',');
        اگر (!p)
            p = نام + لڑی_لمبائی(نام);
        نام += negate;
        len = FFMAX(p - نام, namelen);
        اگر (!av_strncasecmp(name, نام, len) || !لڑی_موازنہ("ALL", نام, FFMAX(3, p - نام)))
            واپس !negate;
        نام = p + (*p == ',');
    }
    واپس 0;
}

صحیح av_utf8_decode(int32_t *codep, ثابت uint8_t **bufp, ثابت uint8_t *buf_انتہا,
                   غیرعلامتی صحیح flags)
{
    ثابت uint8_t *p = *bufp;
    uint32_t چوٹی;
    uint64_t رمز;
    صحیح ret = 0, دم_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    اگر (p >= buf_انتہا)
        واپس 0;

    رمز = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    اگر ((رمز & 0xc0) == 0x80 || رمز >= 0xFE) {
        ret = AVERROR(EILSEQ);
        جاؤ انتہا;
    }
    چوٹی = (رمز & 128) >> 1;

    دم_len = 0;
    جب (رمز & چوٹی) {
        صحیح tmp;
        دم_len++;
        اگر (p >= buf_انتہا) {
            (*bufp) ++;
            واپس AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        اگر (tmp>>6) {
            (*bufp) ++;
            واپس AVERROR(EILSEQ);
        }
        رمز = (رمز<<6) + tmp;
        چوٹی <<= 5;
    }
    رمز &= (چوٹی << 1) - 1;

    /* check for overlong encodings */
    av_assert0(دم_len <= 5);
    اگر (رمز < overlong_encoding_mins[دم_len]) {
        ret = AVERROR(EILSEQ);
        جاؤ انتہا;
    }

    اگر (رمز >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        جاؤ انتہا;
    }

    *codep = رمز;

    اگر (رمز > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    اگر (رمز < 0x20 && رمز != 0x9 && رمز != 0xA && رمز != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    اگر (رمز >= 0xD800 && رمز <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    اگر ((رمز == 0xFFFE || رمز == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

انتہا:
    *bufp = p;
    واپس ret;
}

صحیح av_مطابقت_list(ثابت حرف *name, ثابت حرف *list, حرف separator)
{
    ثابت حرف *p, *q;

    برائے (p = name; p && *p; ) {
        برائے (q = list; q && *q; ) {
            صحیح k;
            برائے (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                اگر (k && (!p[k] || p[k] == separator))
                    واپس 1;
            q = strchr(q, separator);
            اگر(q)
                q++;
        }
        p = strchr(p, separator);
        اگر (p)
            p++;
    }

    واپس 0;
}
