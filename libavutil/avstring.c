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
    जाव (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    जइ (!*pfx && ptr)
        *ptr = str;
    प्रत्यागम !*pfx;
}

पूर्णाङ्क av_stristart(ध्रुव वर्ण *str, ध्रुव वर्ण *pfx, ध्रुव वर्ण **ptr)
{
    जाव (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    जइ (!*pfx && ptr)
        *ptr = str;
    प्रत्यागम !*pfx;
}

वर्ण *av_stristr(ध्रुव वर्ण *s1, ध्रुव वर्ण *s2)
{
    जइ (!*s2)
        प्रत्यागम (वर्ण*)(intptr_t)s1;

    करेहि
        जइ (av_stristart(s1, s2, रिक्त))
            प्रत्यागम (वर्ण*)(intptr_t)s1;
    जाव (*s1++);

    प्रत्यागम रिक्त;
}

वर्ण *av_strnstr(ध्रुव वर्ण *haystack, ध्रुव वर्ण *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    जइ (!needle_len)
        प्रत्यागम (वर्ण*)haystack;
    जाव (hay_length >= needle_len) {
        hay_length--;
        जइ (!memcmp(haystack, needle, needle_len))
            प्रत्यागम (वर्ण*)haystack;
        haystack++;
    }
    प्रत्यागम रिक्त;
}

size_t av_strlcpy(वर्ण *dst, ध्रुव वर्ण *src, size_t size)
{
    size_t len = 0;
    जाव (++len < size && *src)
        *dst++ = *src++;
    जइ (len <= size)
        *dst = 0;
    प्रत्यागम len + strlen(src) - 1;
}

size_t av_strlcat(वर्ण *dst, ध्रुव वर्ण *src, size_t size)
{
    size_t len = strlen(dst);
    जइ (size <= len + 1)
        प्रत्यागम len + strlen(src);
    प्रत्यागम len + av_strlcpy(dst + len, src, size - len);
}

size_t av_strlcatf(वर्ण *dst, size_t size, ध्रुव वर्ण *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
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
    जइ (len < 0)
        गच्छ end;

    p = av_malloc(len + 1);
    जइ (!p)
        गच्छ end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    जइ (len < 0)
        av_freep(&p);

end:
    प्रत्यागम p;
}

#define WHITESPACES " \n\t\r"

वर्ण *av_get_token(ध्रुव वर्ण **buf, ध्रुव वर्ण *term)
{
    वर्ण *out     = av_realloc(रिक्त, strlen(*buf) + 1);
    वर्ण *ret     = out, *end = out;
    ध्रुव वर्ण *p = *buf;
    जइ (!out)
        प्रत्यागम रिक्त;
    p += strspn(p, WHITESPACES);

    जाव (*p && !strspn(p, term)) {
        वर्ण c = *p++;
        जइ (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } अण्णहा जइ (c == '\'') {
            जाव (*p && *p != '\'')
                *out++ = *p++;
            जइ (*p) {
                p++;
                end = out;
            }
        } अण्णहा {
            *out++ = c;
        }
    }

    करेहि
        *out-- = 0;
    जाव (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    वर्ण *small_ret = av_realloc(ret, out - ret + 2);
    प्रत्यागम small_ret ? small_ret : ret;
}

वर्ण *av_strtok(वर्ण *s, ध्रुव वर्ण *delim, वर्ण **saveptr)
{
    वर्ण *tok;

    जइ (!s && !(s = *saveptr))
        प्रत्यागम रिक्त;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    जइ (!*s) {
        *saveptr = रिक्त;
        प्रत्यागम रिक्त;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    जइ (*s) {
        *s = 0;
        *saveptr = s+1;
    } अण्णहा {
        *saveptr = रिक्त;
    }

    प्रत्यागम tok;
}

पूर्णाङ्क av_strcasecmp(ध्रुव वर्ण *a, ध्रुव वर्ण *b)
{
    uint8_t c1, c2;
    करेहि {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } जाव (c1 && c1 == c2);
    प्रत्यागम c1 - c2;
}

पूर्णाङ्क av_strncasecmp(ध्रुव वर्ण *a, ध्रुव वर्ण *b, size_t n)
{
    uint8_t c1, c2;
    जइ (n <= 0)
        प्रत्यागम 0;
    करेहि {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } जाव (--n && c1 && c1 == c2);
    प्रत्यागम c1 - c2;
}

वर्ण *av_strireplace(ध्रुव वर्ण *str, ध्रुव वर्ण *from, ध्रुव वर्ण *to)
{
    वर्ण *ret = रिक्त;
    ध्रुव वर्ण *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    जइ (!fromlen)
        प्रत्यागम av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    जाव ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, strlen(pstr));
    जइ (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, रिक्त);
    } अण्णहा {
        av_bprint_finalize(&pbuf, &ret);
    }

    प्रत्यागम ret;
}

ध्रुव वर्ण *av_basename(ध्रुव वर्ण *path)
{
    जइ (!path || *path == '\0')
        प्रत्यागम ".";

    ध्रुव वर्ण *p = strrchr(path, '/');
#जइ HAVE_DOS_PATHS
    ध्रुव वर्ण *q = strrchr(path, '\\');
    ध्रुव वर्ण *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    जइ (!p)
        प्रत्यागम path;

    प्रत्यागम p + 1;
}

ध्रुव वर्ण *av_dirname(वर्ण *path)
{
    वर्ण *p = path ? strrchr(path, '/') : रिक्त;

#जइ HAVE_DOS_PATHS
    वर्ण *q = path ? strrchr(path, '\\') : रिक्त;
    वर्ण *d = path ? strchr(path, ':')  : रिक्त;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    जइ (!p)
        प्रत्यागम ".";

    *p = '\0';

    प्रत्यागम path;
}

वर्ण *av_append_path_component(ध्रुव वर्ण *path, ध्रुव वर्ण *component)
{
    size_t p_len, c_len;
    वर्ण *fullpath;

    जइ (!path)
        प्रत्यागम av_strdup(component);
    जइ (!component)
        प्रत्यागम av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    जइ (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        प्रत्यागम रिक्त;
    fullpath = av_malloc(p_len + c_len + 2);
    जइ (fullpath) {
        जइ (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            जइ (c_len) {
                जइ (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                अण्णहा जइ (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    प्रत्यागम fullpath;
}

पूर्णाङ्क av_escape(वर्ण **dst, ध्रुव वर्ण *src, ध्रुव वर्ण *special_chars,
              गणना AVEscapeMode mode, पूर्णाङ्क flags)
{
    AVBPrint dstbuf;
    पूर्णाङ्क ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    जइ (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, रिक्त);
        प्रत्यागम AVERROR(ENOMEM);
    }
    जइ ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        प्रत्यागम ret;
    प्रत्यागम dstbuf.len;
}

पूर्णाङ्क av_match_name(ध्रुव वर्ण *name, ध्रुव वर्ण *names)
{
    ध्रुव वर्ण *p;
    size_t len, namelen;

    जइ (!name || !names)
        प्रत्यागम 0;

    namelen = strlen(name);
    जाव (*names) {
        पूर्णाङ्क negate = '-' == *names;
        p = strchr(names, ',');
        जइ (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        जइ (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            प्रत्यागम !negate;
        names = p + (*p == ',');
    }
    प्रत्यागम 0;
}

पूर्णाङ्क av_utf8_decode(int32_t *codep, ध्रुव uint8_t **bufp, ध्रुव uint8_t *buf_end,
                   unsigned पूर्णाङ्क flags)
{
    ध्रुव uint8_t *p = *bufp;
    uint32_t शिखरम्;
    uint64_t code;
    पूर्णाङ्क ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    जइ (p >= buf_end)
        प्रत्यागम 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    जइ ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        गच्छ end;
    }
    शिखरम् = (code & 128) >> 1;

    tail_len = 0;
    जाव (code & शिखरम्) {
        पूर्णाङ्क tmp;
        tail_len++;
        जइ (p >= buf_end) {
            (*bufp) ++;
            प्रत्यागम AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        जइ (tmp>>6) {
            (*bufp) ++;
            प्रत्यागम AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        शिखरम् <<= 5;
    }
    code &= (शिखरम् << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    जइ (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        गच्छ end;
    }

    जइ (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        गच्छ end;
    }

    *codep = code;

    जइ (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    जइ (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    जइ (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    जइ ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    प्रत्यागम ret;
}

पूर्णाङ्क av_match_list(ध्रुव वर्ण *name, ध्रुव वर्ण *list, वर्ण separator)
{
    ध्रुव वर्ण *p, *q;

    प्रति (p = name; p && *p; ) {
        प्रति (q = list; q && *q; ) {
            पूर्णाङ्क k;
            प्रति (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                जइ (k && (!p[k] || p[k] == separator))
                    प्रत्यागम 1;
            q = strchr(q, separator);
            जइ(q)
                q++;
        }
        p = strchr(p, separator);
        जइ (p)
            p++;
    }

    प्रत्यागम 0;
}
