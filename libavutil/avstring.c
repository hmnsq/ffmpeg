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

صحیح av_strstart(ثابت نویسه *str, ثابت نویسه *pfx, ثابت نویسه **ptr)
{
    وقتی (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    اگر (!*pfx && ptr)
        *ptr = str;
    بازگشت !*pfx;
}

صحیح av_stristart(ثابت نویسه *str, ثابت نویسه *pfx, ثابت نویسه **ptr)
{
    وقتی (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    اگر (!*pfx && ptr)
        *ptr = str;
    بازگشت !*pfx;
}

نویسه *av_stristr(ثابت نویسه *s1, ثابت نویسه *s2)
{
    اگر (!*s2)
        بازگشت (نویسه*)(intptr_t)s1;

    انجامبده
        اگر (av_stristart(s1, s2, پوچ))
            بازگشت (نویسه*)(intptr_t)s1;
    وقتی (*s1++);

    بازگشت پوچ;
}

نویسه *av_strnstr(ثابت نویسه *haystack, ثابت نویسه *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    اگر (!needle_len)
        بازگشت (نویسه*)haystack;
    وقتی (hay_length >= needle_len) {
        hay_length--;
        اگر (!memcmp(haystack, needle, needle_len))
            بازگشت (نویسه*)haystack;
        haystack++;
    }
    بازگشت پوچ;
}

size_t av_strlcpy(نویسه *dst, ثابت نویسه *src, size_t size)
{
    size_t len = 0;
    وقتی (++len < size && *src)
        *dst++ = *src++;
    اگر (len <= size)
        *dst = 0;
    بازگشت len + strlen(src) - 1;
}

size_t av_strlcat(نویسه *dst, ثابت نویسه *src, size_t size)
{
    size_t len = strlen(dst);
    اگر (size <= len + 1)
        بازگشت len + strlen(src);
    بازگشت len + av_strlcpy(dst + len, src, size - len);
}

size_t av_strlcatf(نویسه *dst, size_t size, ثابت نویسه *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    va_end(vl);

    بازگشت len;
}

نویسه *av_asprintf(ثابت نویسه *fmt, ...)
{
    نویسه *p = پوچ;
    va_list va;
    صحیح len;

    va_start(va, fmt);
    len = vsnprintf(پوچ, 0, fmt, va);
    va_end(va);
    اگر (len < 0)
        برو end;

    p = av_malloc(len + 1);
    اگر (!p)
        برو end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    اگر (len < 0)
        av_freep(&p);

end:
    بازگشت p;
}

#define WHITESPACES " \n\t\r"

نویسه *av_get_token(ثابت نویسه **buf, ثابت نویسه *term)
{
    نویسه *out     = av_realloc(پوچ, strlen(*buf) + 1);
    نویسه *ret     = out, *end = out;
    ثابت نویسه *p = *buf;
    اگر (!out)
        بازگشت پوچ;
    p += strspn(p, WHITESPACES);

    وقتی (*p && !strspn(p, term)) {
        نویسه c = *p++;
        اگر (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } وگرنه اگر (c == '\'') {
            وقتی (*p && *p != '\'')
                *out++ = *p++;
            اگر (*p) {
                p++;
                end = out;
            }
        } وگرنه {
            *out++ = c;
        }
    }

    انجامبده
        *out-- = 0;
    وقتی (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    نویسه *small_ret = av_realloc(ret, out - ret + 2);
    بازگشت small_ret ? small_ret : ret;
}

نویسه *av_strtok(نویسه *s, ثابت نویسه *delim, نویسه **saveptr)
{
    نویسه *tok;

    اگر (!s && !(s = *saveptr))
        بازگشت پوچ;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    اگر (!*s) {
        *saveptr = پوچ;
        بازگشت پوچ;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    اگر (*s) {
        *s = 0;
        *saveptr = s+1;
    } وگرنه {
        *saveptr = پوچ;
    }

    بازگشت tok;
}

صحیح av_strcasecmp(ثابت نویسه *a, ثابت نویسه *b)
{
    uint8_t c1, c2;
    انجامبده {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } وقتی (c1 && c1 == c2);
    بازگشت c1 - c2;
}

صحیح av_strncasecmp(ثابت نویسه *a, ثابت نویسه *b, size_t n)
{
    uint8_t c1, c2;
    اگر (n <= 0)
        بازگشت 0;
    انجامبده {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } وقتی (--n && c1 && c1 == c2);
    بازگشت c1 - c2;
}

نویسه *av_strireplace(ثابت نویسه *str, ثابت نویسه *from, ثابت نویسه *to)
{
    نویسه *ret = پوچ;
    ثابت نویسه *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    اگر (!fromlen)
        بازگشت av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    وقتی ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, strlen(pstr));
    اگر (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, پوچ);
    } وگرنه {
        av_bprint_finalize(&pbuf, &ret);
    }

    بازگشت ret;
}

ثابت نویسه *av_basename(ثابت نویسه *path)
{
    اگر (!path || *path == '\0')
        بازگشت ".";

    ثابت نویسه *p = strrchr(path, '/');
#اگر HAVE_DOS_PATHS
    ثابت نویسه *q = strrchr(path, '\\');
    ثابت نویسه *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    اگر (!p)
        بازگشت path;

    بازگشت p + 1;
}

ثابت نویسه *av_dirname(نویسه *path)
{
    نویسه *p = path ? strrchr(path, '/') : پوچ;

#اگر HAVE_DOS_PATHS
    نویسه *q = path ? strrchr(path, '\\') : پوچ;
    نویسه *d = path ? strchr(path, ':')  : پوچ;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    اگر (!p)
        بازگشت ".";

    *p = '\0';

    بازگشت path;
}

نویسه *av_append_path_component(ثابت نویسه *path, ثابت نویسه *component)
{
    size_t p_len, c_len;
    نویسه *fullpath;

    اگر (!path)
        بازگشت av_strdup(component);
    اگر (!component)
        بازگشت av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    اگر (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        بازگشت پوچ;
    fullpath = av_malloc(p_len + c_len + 2);
    اگر (fullpath) {
        اگر (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            اگر (c_len) {
                اگر (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                وگرنه اگر (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    بازگشت fullpath;
}

صحیح av_escape(نویسه **dst, ثابت نویسه *src, ثابت نویسه *special_chars,
              شمارش AVEscapeMode mode, صحیح flags)
{
    AVBPrint dstbuf;
    صحیح ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    اگر (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, پوچ);
        بازگشت AVERROR(ENOMEM);
    }
    اگر ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        بازگشت ret;
    بازگشت dstbuf.len;
}

صحیح av_match_name(ثابت نویسه *name, ثابت نویسه *names)
{
    ثابت نویسه *p;
    size_t len, namelen;

    اگر (!name || !names)
        بازگشت 0;

    namelen = strlen(name);
    وقتی (*names) {
        صحیح negate = '-' == *names;
        p = strchr(names, ',');
        اگر (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        اگر (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            بازگشت !negate;
        names = p + (*p == ',');
    }
    بازگشت 0;
}

صحیح av_utf8_decode(int32_t *codep, ثابت uint8_t **bufp, ثابت uint8_t *buf_end,
                   unsigned صحیح flags)
{
    ثابت uint8_t *p = *bufp;
    uint32_t بالاترین;
    uint64_t code;
    صحیح ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    اگر (p >= buf_end)
        بازگشت 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    اگر ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        برو end;
    }
    بالاترین = (code & 128) >> 1;

    tail_len = 0;
    وقتی (code & بالاترین) {
        صحیح tmp;
        tail_len++;
        اگر (p >= buf_end) {
            (*bufp) ++;
            بازگشت AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        اگر (tmp>>6) {
            (*bufp) ++;
            بازگشت AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        بالاترین <<= 5;
    }
    code &= (بالاترین << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    اگر (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        برو end;
    }

    اگر (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        برو end;
    }

    *codep = code;

    اگر (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    اگر (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    اگر (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    اگر ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    بازگشت ret;
}

صحیح av_match_list(ثابت نویسه *name, ثابت نویسه *list, نویسه separator)
{
    ثابت نویسه *p, *q;

    برای (p = name; p && *p; ) {
        برای (q = list; q && *q; ) {
            صحیح k;
            برای (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                اگر (k && (!p[k] || p[k] == separator))
                    بازگشت 1;
            q = strchr(q, separator);
            اگر(q)
                q++;
        }
        p = strchr(p, separator);
        اگر (p)
            p++;
    }

    بازگشت 0;
}
