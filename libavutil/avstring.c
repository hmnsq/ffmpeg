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

#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <stdarg.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "avstring.h"
#அந்தர்பாவ "bprint.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "macros.h"

முழு av_strstart(மாறிலி எழுத்து *str, மாறிலி எழுத்து *pfx, மாறிலி எழுத்து **ptr)
{
    போது (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    எனில் (!*pfx && ptr)
        *ptr = str;
    திரும்பு !*pfx;
}

முழு av_stristart(மாறிலி எழுத்து *str, மாறிலி எழுத்து *pfx, மாறிலி எழுத்து **ptr)
{
    போது (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    எனில் (!*pfx && ptr)
        *ptr = str;
    திரும்பு !*pfx;
}

எழுத்து *av_stristr(மாறிலி எழுத்து *s1, மாறிலி எழுத்து *s2)
{
    எனில் (!*s2)
        திரும்பு (எழுத்து*)(intptr_t)s1;

    செய்
        எனில் (av_stristart(s1, s2, வெற்று))
            திரும்பு (எழுத்து*)(intptr_t)s1;
    போது (*s1++);

    திரும்பு வெற்று;
}

எழுத்து *av_strnstr(மாறிலி எழுத்து *haystack, மாறிலி எழுத்து *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    எனில் (!needle_len)
        திரும்பு (எழுத்து*)haystack;
    போது (hay_length >= needle_len) {
        hay_length--;
        எனில் (!memcmp(haystack, needle, needle_len))
            திரும்பு (எழுத்து*)haystack;
        haystack++;
    }
    திரும்பு வெற்று;
}

size_t av_strlcpy(எழுத்து *dst, மாறிலி எழுத்து *src, size_t size)
{
    size_t len = 0;
    போது (++len < size && *src)
        *dst++ = *src++;
    எனில் (len <= size)
        *dst = 0;
    திரும்பு len + strlen(src) - 1;
}

size_t av_strlcat(எழுத்து *dst, மாறிலி எழுத்து *src, size_t size)
{
    size_t len = strlen(dst);
    எனில் (size <= len + 1)
        திரும்பு len + strlen(src);
    திரும்பு len + av_strlcpy(dst + len, src, size - len);
}

size_t av_strlcatf(எழுத்து *dst, size_t size, மாறிலி எழுத்து *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    va_end(vl);

    திரும்பு len;
}

எழுத்து *av_asprintf(மாறிலி எழுத்து *fmt, ...)
{
    எழுத்து *p = வெற்று;
    va_list va;
    முழு len;

    va_start(va, fmt);
    len = vsnprintf(வெற்று, 0, fmt, va);
    va_end(va);
    எனில் (len < 0)
        செல் end;

    p = av_malloc(len + 1);
    எனில் (!p)
        செல் end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    எனில் (len < 0)
        av_freep(&p);

end:
    திரும்பு p;
}

#define WHITESPACES " \n\t\r"

எழுத்து *av_get_token(மாறிலி எழுத்து **buf, மாறிலி எழுத்து *term)
{
    எழுத்து *out     = av_realloc(வெற்று, strlen(*buf) + 1);
    எழுத்து *ret     = out, *end = out;
    மாறிலி எழுத்து *p = *buf;
    எனில் (!out)
        திரும்பு வெற்று;
    p += strspn(p, WHITESPACES);

    போது (*p && !strspn(p, term)) {
        எழுத்து c = *p++;
        எனில் (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } இல்லையெனில் எனில் (c == '\'') {
            போது (*p && *p != '\'')
                *out++ = *p++;
            எனில் (*p) {
                p++;
                end = out;
            }
        } இல்லையெனில் {
            *out++ = c;
        }
    }

    செய்
        *out-- = 0;
    போது (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    எழுத்து *small_ret = av_realloc(ret, out - ret + 2);
    திரும்பு small_ret ? small_ret : ret;
}

எழுத்து *av_strtok(எழுத்து *s, மாறிலி எழுத்து *delim, எழுத்து **saveptr)
{
    எழுத்து *tok;

    எனில் (!s && !(s = *saveptr))
        திரும்பு வெற்று;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    எனில் (!*s) {
        *saveptr = வெற்று;
        திரும்பு வெற்று;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    எனில் (*s) {
        *s = 0;
        *saveptr = s+1;
    } இல்லையெனில் {
        *saveptr = வெற்று;
    }

    திரும்பு tok;
}

முழு av_strcasecmp(மாறிலி எழுத்து *a, மாறிலி எழுத்து *b)
{
    uint8_t c1, c2;
    செய் {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } போது (c1 && c1 == c2);
    திரும்பு c1 - c2;
}

முழு av_strncasecmp(மாறிலி எழுத்து *a, மாறிலி எழுத்து *b, size_t n)
{
    uint8_t c1, c2;
    எனில் (n <= 0)
        திரும்பு 0;
    செய் {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } போது (--n && c1 && c1 == c2);
    திரும்பு c1 - c2;
}

எழுத்து *av_strireplace(மாறிலி எழுத்து *str, மாறிலி எழுத்து *from, மாறிலி எழுத்து *to)
{
    எழுத்து *ret = வெற்று;
    மாறிலி எழுத்து *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    எனில் (!fromlen)
        திரும்பு av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    போது ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, strlen(pstr));
    எனில் (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, வெற்று);
    } இல்லையெனில் {
        av_bprint_finalize(&pbuf, &ret);
    }

    திரும்பு ret;
}

மாறிலி எழுத்து *av_basename(மாறிலி எழுத்து *path)
{
    எனில் (!path || *path == '\0')
        திரும்பு ".";

    மாறிலி எழுத்து *p = strrchr(path, '/');
#எனில் HAVE_DOS_PATHS
    மாறிலி எழுத்து *q = strrchr(path, '\\');
    மாறிலி எழுத்து *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    எனில் (!p)
        திரும்பு path;

    திரும்பு p + 1;
}

மாறிலி எழுத்து *av_dirname(எழுத்து *path)
{
    எழுத்து *p = path ? strrchr(path, '/') : வெற்று;

#எனில் HAVE_DOS_PATHS
    எழுத்து *q = path ? strrchr(path, '\\') : வெற்று;
    எழுத்து *d = path ? strchr(path, ':')  : வெற்று;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    எனில் (!p)
        திரும்பு ".";

    *p = '\0';

    திரும்பு path;
}

எழுத்து *av_append_path_component(மாறிலி எழுத்து *path, மாறிலி எழுத்து *component)
{
    size_t p_len, c_len;
    எழுத்து *fullpath;

    எனில் (!path)
        திரும்பு av_strdup(component);
    எனில் (!component)
        திரும்பு av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    எனில் (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        திரும்பு வெற்று;
    fullpath = av_malloc(p_len + c_len + 2);
    எனில் (fullpath) {
        எனில் (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            எனில் (c_len) {
                எனில் (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                இல்லையெனில் எனில் (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    திரும்பு fullpath;
}

முழு av_escape(எழுத்து **dst, மாறிலி எழுத்து *src, மாறிலி எழுத்து *special_chars,
              எண்ணிக்கை AVEscapeMode mode, முழு flags)
{
    AVBPrint dstbuf;
    முழு ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    எனில் (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, வெற்று);
        திரும்பு AVERROR(ENOMEM);
    }
    எனில் ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        திரும்பு ret;
    திரும்பு dstbuf.len;
}

முழு av_match_name(மாறிலி எழுத்து *name, மாறிலி எழுத்து *names)
{
    மாறிலி எழுத்து *p;
    size_t len, namelen;

    எனில் (!name || !names)
        திரும்பு 0;

    namelen = strlen(name);
    போது (*names) {
        முழு negate = '-' == *names;
        p = strchr(names, ',');
        எனில் (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        எனில் (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            திரும்பு !negate;
        names = p + (*p == ',');
    }
    திரும்பு 0;
}

முழு av_utf8_decode(int32_t *codep, மாறிலி uint8_t **bufp, மாறிலி uint8_t *buf_end,
                   unsigned முழு flags)
{
    மாறிலி uint8_t *p = *bufp;
    uint32_t உச்சி;
    uint64_t code;
    முழு ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    எனில் (p >= buf_end)
        திரும்பு 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    எனில் ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        செல் end;
    }
    உச்சி = (code & 128) >> 1;

    tail_len = 0;
    போது (code & உச்சி) {
        முழு tmp;
        tail_len++;
        எனில் (p >= buf_end) {
            (*bufp) ++;
            திரும்பு AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        எனில் (tmp>>6) {
            (*bufp) ++;
            திரும்பு AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        உச்சி <<= 5;
    }
    code &= (உச்சி << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    எனில் (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        செல் end;
    }

    எனில் (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        செல் end;
    }

    *codep = code;

    எனில் (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    எனில் (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    எனில் (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    எனில் ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    திரும்பு ret;
}

முழு av_match_list(மாறிலி எழுத்து *name, மாறிலி எழுத்து *list, எழுத்து separator)
{
    மாறிலி எழுத்து *p, *q;

    க்கு (p = name; p && *p; ) {
        க்கு (q = list; q && *q; ) {
            முழு k;
            க்கு (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                எனில் (k && (!p[k] || p[k] == separator))
                    திரும்பு 1;
            q = strchr(q, separator);
            எனில்(q)
                q++;
        }
        p = strchr(p, separator);
        எனில் (p)
            p++;
    }

    திரும்பு 0;
}
