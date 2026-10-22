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

पूर्णांक av_strstart(स्थिरांक अक्षर *str, स्थिरांक अक्षर *pfx, स्थिरांक अक्षर **ptr)
{
    पर्यंत (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    जर (!*pfx && ptr)
        *ptr = str;
    परत !*pfx;
}

पूर्णांक av_stristart(स्थिरांक अक्षर *str, स्थिरांक अक्षर *pfx, स्थिरांक अक्षर **ptr)
{
    पर्यंत (*pfx && av_toupper((अचिन्हित)*pfx) == av_toupper((अचिन्हित)*str)) {
        pfx++;
        str++;
    }
    जर (!*pfx && ptr)
        *ptr = str;
    परत !*pfx;
}

अक्षर *av_stristr(स्थिरांक अक्षर *s1, स्थिरांक अक्षर *s2)
{
    जर (!*s2)
        परत (अक्षर*)(intptr_t)s1;

    करा
        जर (av_stristart(s1, s2, रिक्त))
            परत (अक्षर*)(intptr_t)s1;
    पर्यंत (*s1++);

    परत रिक्त;
}

अक्षर *av_strnstr(स्थिरांक अक्षर *haystack, स्थिरांक अक्षर *needle, माप_प्रकार hay_length)
{
    माप_प्रकार needle_len = म_माप(needle);
    जर (!needle_len)
        परत (अक्षर*)haystack;
    पर्यंत (hay_length >= needle_len) {
        hay_length--;
        जर (!स_भेद(haystack, needle, needle_len))
            परत (अक्षर*)haystack;
        haystack++;
    }
    परत रिक्त;
}

माप_प्रकार av_strlcpy(अक्षर *dst, स्थिरांक अक्षर *src, माप_प्रकार size)
{
    माप_प्रकार len = 0;
    पर्यंत (++len < size && *src)
        *dst++ = *src++;
    जर (len <= size)
        *dst = 0;
    परत len + म_माप(src) - 1;
}

माप_प्रकार av_strlcat(अक्षर *dst, स्थिरांक अक्षर *src, माप_प्रकार size)
{
    माप_प्रकार len = म_माप(dst);
    जर (size <= len + 1)
        परत len + म_माप(src);
    परत len + av_strlcpy(dst + len, src, size - len);
}

माप_प्रकार av_strlcatf(अक्षर *dst, माप_प्रकार size, स्थिरांक अक्षर *fmt, ...)
{
    माप_प्रकार len = म_माप(dst);
    बहु_सूची vl;

    बहु_शुरू(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    बहु_पूर्ण(vl);

    परत len;
}

अक्षर *av_asprintf(स्थिरांक अक्षर *fmt, ...)
{
    अक्षर *p = रिक्त;
    बहु_सूची va;
    पूर्णांक len;

    बहु_शुरू(va, fmt);
    len = vsnprintf(रिक्त, 0, fmt, va);
    बहु_पूर्ण(va);
    जर (len < 0)
        जा end;

    p = av_malloc(len + 1);
    जर (!p)
        जा end;

    बहु_शुरू(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    बहु_पूर्ण(va);
    जर (len < 0)
        av_freep(&p);

end:
    परत p;
}

#define WHITESPACES " \n\t\r"

अक्षर *av_get_token(स्थिरांक अक्षर **buf, स्थिरांक अक्षर *term)
{
    अक्षर *out     = av_realloc(रिक्त, म_माप(*buf) + 1);
    अक्षर *ret     = out, *end = out;
    स्थिरांक अक्षर *p = *buf;
    जर (!out)
        परत रिक्त;
    p += म_अखोज(p, WHITESPACES);

    पर्यंत (*p && !म_अखोज(p, term)) {
        अक्षर c = *p++;
        जर (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } अन्यथा जर (c == '\'') {
            पर्यंत (*p && *p != '\'')
                *out++ = *p++;
            जर (*p) {
                p++;
                end = out;
            }
        } अन्यथा {
            *out++ = c;
        }
    }

    करा
        *out-- = 0;
    पर्यंत (out >= end && म_अखोज(out, WHITESPACES));

    *buf = p;

    अक्षर *small_ret = av_realloc(ret, out - ret + 2);
    परत small_ret ? small_ret : ret;
}

अक्षर *av_strtok(अक्षर *s, स्थिरांक अक्षर *delim, अक्षर **saveptr)
{
    अक्षर *tok;

    जर (!s && !(s = *saveptr))
        परत रिक्त;

    /* skip leading delimiters */
    s += म_अखोज(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    जर (!*s) {
        *saveptr = रिक्त;
        परत रिक्त;
    }
    tok = s++;

    /* skip non delimiters */
    s += म_खोज(s, delim);
    जर (*s) {
        *s = 0;
        *saveptr = s+1;
    } अन्यथा {
        *saveptr = रिक्त;
    }

    परत tok;
}

पूर्णांक av_strcasecmp(स्थिरांक अक्षर *a, स्थिरांक अक्षर *b)
{
    uint8_t c1, c2;
    करा {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } पर्यंत (c1 && c1 == c2);
    परत c1 - c2;
}

पूर्णांक av_strncasecmp(स्थिरांक अक्षर *a, स्थिरांक अक्षर *b, माप_प्रकार n)
{
    uint8_t c1, c2;
    जर (n <= 0)
        परत 0;
    करा {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } पर्यंत (--n && c1 && c1 == c2);
    परत c1 - c2;
}

अक्षर *av_strireplace(स्थिरांक अक्षर *str, स्थिरांक अक्षर *from, स्थिरांक अक्षर *to)
{
    अक्षर *ret = रिक्त;
    स्थिरांक अक्षर *pstr2, *pstr = str;
    माप_प्रकार tolen = म_माप(to), fromlen = म_माप(from);
    AVBPrint pbuf;

    जर (!fromlen)
        परत av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    पर्यंत ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, म_माप(pstr));
    जर (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, रिक्त);
    } अन्यथा {
        av_bprint_finalize(&pbuf, &ret);
    }

    परत ret;
}

स्थिरांक अक्षर *av_basename(स्थिरांक अक्षर *path)
{
    जर (!path || *path == '\0')
        परत ".";

    स्थिरांक अक्षर *p = म_खोजप(path, '/');
#जर HAVE_DOS_PATHS
    स्थिरांक अक्षर *q = म_खोजप(path, '\\');
    स्थिरांक अक्षर *d = म_अक्षर(path, ':');
    p = FFMAX3(p, q, d);
#endif

    जर (!p)
        परत path;

    परत p + 1;
}

स्थिरांक अक्षर *av_dirname(अक्षर *path)
{
    अक्षर *p = path ? म_खोजप(path, '/') : रिक्त;

#जर HAVE_DOS_PATHS
    अक्षर *q = path ? म_खोजप(path, '\\') : रिक्त;
    अक्षर *d = path ? म_अक्षर(path, ':')  : रिक्त;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    जर (!p)
        परत ".";

    *p = '\0';

    परत path;
}

अक्षर *av_append_path_component(स्थिरांक अक्षर *path, स्थिरांक अक्षर *component)
{
    माप_प्रकार p_len, c_len;
    अक्षर *fullpath;

    जर (!path)
        परत av_strdup(component);
    जर (!component)
        परत av_strdup(path);

    p_len = म_माप(path);
    c_len = म_माप(component);
    जर (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        परत रिक्त;
    fullpath = av_malloc(p_len + c_len + 2);
    जर (fullpath) {
        जर (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            जर (c_len) {
                जर (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                अन्यथा जर (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    परत fullpath;
}

पूर्णांक av_escape(अक्षर **dst, स्थिरांक अक्षर *src, स्थिरांक अक्षर *special_chars,
              गणना AVEscapeMode mode, पूर्णांक flags)
{
    AVBPrint dstbuf;
    पूर्णांक ret;

    av_bprint_init(&dstbuf, 1, पूर्णांक_उच्च); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    जर (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, रिक्त);
        परत AVERROR(ENOMEM);
    }
    जर ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        परत ret;
    परत dstbuf.len;
}

पूर्णांक av_match_name(स्थिरांक अक्षर *name, स्थिरांक अक्षर *names)
{
    स्थिरांक अक्षर *p;
    माप_प्रकार len, namelen;

    जर (!name || !names)
        परत 0;

    namelen = म_माप(name);
    पर्यंत (*names) {
        पूर्णांक negate = '-' == *names;
        p = म_अक्षर(names, ',');
        जर (!p)
            p = names + म_माप(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        जर (!av_strncasecmp(name, names, len) || !म_भेदन("ALL", names, FFMAX(3, p - names)))
            परत !negate;
        names = p + (*p == ',');
    }
    परत 0;
}

पूर्णांक av_utf8_decode(int32_t *codep, स्थिरांक uint8_t **bufp, स्थिरांक uint8_t *buf_end,
                   अचिन्हित पूर्णांक flags)
{
    स्थिरांक uint8_t *p = *bufp;
    uint32_t शीर्ष;
    uint64_t code;
    पूर्णांक ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    जर (p >= buf_end)
        परत 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    जर ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        जा end;
    }
    शीर्ष = (code & 128) >> 1;

    tail_len = 0;
    पर्यंत (code & शीर्ष) {
        पूर्णांक tmp;
        tail_len++;
        जर (p >= buf_end) {
            (*bufp) ++;
            परत AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        जर (tmp>>6) {
            (*bufp) ++;
            परत AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        शीर्ष <<= 5;
    }
    code &= (शीर्ष << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    जर (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        जा end;
    }

    जर (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        जा end;
    }

    *codep = code;

    जर (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    जर (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    जर (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    जर ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    परत ret;
}

पूर्णांक av_match_list(स्थिरांक अक्षर *name, स्थिरांक अक्षर *list, अक्षर separator)
{
    स्थिरांक अक्षर *p, *q;

    साठी (p = name; p && *p; ) {
        साठी (q = list; q && *q; ) {
            पूर्णांक k;
            साठी (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                जर (k && (!p[k] || p[k] == separator))
                    परत 1;
            q = म_अक्षर(q, separator);
            जर(q)
                q++;
        }
        p = म_अक्षर(p, separator);
        जर (p)
            p++;
    }

    परत 0;
}
