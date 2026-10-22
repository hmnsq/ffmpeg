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

पूर्णाङ्क av_strstart(अचर वर्ण *str, अचर वर्ण *pfx, अचर वर्ण **ptr)
{
    जबसम्म (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    यदि (!*pfx && ptr)
        *ptr = str;
    फर्काऊ !*pfx;
}

पूर्णाङ्क av_stristart(अचर वर्ण *str, अचर वर्ण *pfx, अचर वर्ण **ptr)
{
    जबसम्म (*pfx && av_toupper((अचिन्हित)*pfx) == av_toupper((अचिन्हित)*str)) {
        pfx++;
        str++;
    }
    यदि (!*pfx && ptr)
        *ptr = str;
    फर्काऊ !*pfx;
}

वर्ण *av_stristr(अचर वर्ण *s1, अचर वर्ण *s2)
{
    यदि (!*s2)
        फर्काऊ (वर्ण*)(intptr_t)s1;

    गर
        यदि (av_stristart(s1, s2, रिक्त))
            फर्काऊ (वर्ण*)(intptr_t)s1;
    जबसम्म (*s1++);

    फर्काऊ रिक्त;
}

वर्ण *av_strnstr(अचर वर्ण *haystack, अचर वर्ण *needle, माप_प्रकार hay_length)
{
    माप_प्रकार needle_len = म_माप(needle);
    यदि (!needle_len)
        फर्काऊ (वर्ण*)haystack;
    जबसम्म (hay_length >= needle_len) {
        hay_length--;
        यदि (!स_भेद(haystack, needle, needle_len))
            फर्काऊ (वर्ण*)haystack;
        haystack++;
    }
    फर्काऊ रिक्त;
}

माप_प्रकार av_strlcpy(वर्ण *dst, अचर वर्ण *src, माप_प्रकार size)
{
    माप_प्रकार len = 0;
    जबसम्म (++len < size && *src)
        *dst++ = *src++;
    यदि (len <= size)
        *dst = 0;
    फर्काऊ len + म_माप(src) - 1;
}

माप_प्रकार av_strlcat(वर्ण *dst, अचर वर्ण *src, माप_प्रकार size)
{
    माप_प्रकार len = म_माप(dst);
    यदि (size <= len + 1)
        फर्काऊ len + म_माप(src);
    फर्काऊ len + av_strlcpy(dst + len, src, size - len);
}

माप_प्रकार av_strlcatf(वर्ण *dst, माप_प्रकार size, अचर वर्ण *fmt, ...)
{
    माप_प्रकार len = म_माप(dst);
    बहु_सूची vl;

    बहु_शुरू(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    बहु_पूर्ण(vl);

    फर्काऊ len;
}

वर्ण *av_asprintf(अचर वर्ण *fmt, ...)
{
    वर्ण *p = रिक्त;
    बहु_सूची va;
    पूर्णाङ्क len;

    बहु_शुरू(va, fmt);
    len = vsnprintf(रिक्त, 0, fmt, va);
    बहु_पूर्ण(va);
    यदि (len < 0)
        गच्छ end;

    p = av_malloc(len + 1);
    यदि (!p)
        गच्छ end;

    बहु_शुरू(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    बहु_पूर्ण(va);
    यदि (len < 0)
        av_freep(&p);

end:
    फर्काऊ p;
}

#define WHITESPACES " \n\t\r"

वर्ण *av_get_token(अचर वर्ण **buf, अचर वर्ण *term)
{
    वर्ण *out     = av_realloc(रिक्त, म_माप(*buf) + 1);
    वर्ण *ret     = out, *end = out;
    अचर वर्ण *p = *buf;
    यदि (!out)
        फर्काऊ रिक्त;
    p += म_अखोज(p, WHITESPACES);

    जबसम्म (*p && !म_अखोज(p, term)) {
        वर्ण c = *p++;
        यदि (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } अन्यथा यदि (c == '\'') {
            जबसम्म (*p && *p != '\'')
                *out++ = *p++;
            यदि (*p) {
                p++;
                end = out;
            }
        } अन्यथा {
            *out++ = c;
        }
    }

    गर
        *out-- = 0;
    जबसम्म (out >= end && म_अखोज(out, WHITESPACES));

    *buf = p;

    वर्ण *small_ret = av_realloc(ret, out - ret + 2);
    फर्काऊ small_ret ? small_ret : ret;
}

वर्ण *av_strtok(वर्ण *s, अचर वर्ण *delim, वर्ण **saveptr)
{
    वर्ण *tok;

    यदि (!s && !(s = *saveptr))
        फर्काऊ रिक्त;

    /* skip leading delimiters */
    s += म_अखोज(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    यदि (!*s) {
        *saveptr = रिक्त;
        फर्काऊ रिक्त;
    }
    tok = s++;

    /* skip non delimiters */
    s += म_खोज(s, delim);
    यदि (*s) {
        *s = 0;
        *saveptr = s+1;
    } अन्यथा {
        *saveptr = रिक्त;
    }

    फर्काऊ tok;
}

पूर्णाङ्क av_strcasecmp(अचर वर्ण *a, अचर वर्ण *b)
{
    uint8_t c1, c2;
    गर {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } जबसम्म (c1 && c1 == c2);
    फर्काऊ c1 - c2;
}

पूर्णाङ्क av_strncasecmp(अचर वर्ण *a, अचर वर्ण *b, माप_प्रकार n)
{
    uint8_t c1, c2;
    यदि (n <= 0)
        फर्काऊ 0;
    गर {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } जबसम्म (--n && c1 && c1 == c2);
    फर्काऊ c1 - c2;
}

वर्ण *av_strireplace(अचर वर्ण *str, अचर वर्ण *from, अचर वर्ण *to)
{
    वर्ण *ret = रिक्त;
    अचर वर्ण *pstr2, *pstr = str;
    माप_प्रकार tolen = म_माप(to), fromlen = म_माप(from);
    AVBPrint pbuf;

    यदि (!fromlen)
        फर्काऊ av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    जबसम्म ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, म_माप(pstr));
    यदि (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, रिक्त);
    } अन्यथा {
        av_bprint_finalize(&pbuf, &ret);
    }

    फर्काऊ ret;
}

अचर वर्ण *av_basename(अचर वर्ण *path)
{
    यदि (!path || *path == '\0')
        फर्काऊ ".";

    अचर वर्ण *p = म_खोजप(path, '/');
#यदि HAVE_DOS_PATHS
    अचर वर्ण *q = म_खोजप(path, '\\');
    अचर वर्ण *d = म_अक्षर(path, ':');
    p = FFMAX3(p, q, d);
#endif

    यदि (!p)
        फर्काऊ path;

    फर्काऊ p + 1;
}

अचर वर्ण *av_dirname(वर्ण *path)
{
    वर्ण *p = path ? म_खोजप(path, '/') : रिक्त;

#यदि HAVE_DOS_PATHS
    वर्ण *q = path ? म_खोजप(path, '\\') : रिक्त;
    वर्ण *d = path ? म_अक्षर(path, ':')  : रिक्त;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    यदि (!p)
        फर्काऊ ".";

    *p = '\0';

    फर्काऊ path;
}

वर्ण *av_append_path_component(अचर वर्ण *path, अचर वर्ण *component)
{
    माप_प्रकार p_len, c_len;
    वर्ण *fullpath;

    यदि (!path)
        फर्काऊ av_strdup(component);
    यदि (!component)
        फर्काऊ av_strdup(path);

    p_len = म_माप(path);
    c_len = म_माप(component);
    यदि (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        फर्काऊ रिक्त;
    fullpath = av_malloc(p_len + c_len + 2);
    यदि (fullpath) {
        यदि (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
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
    फर्काऊ fullpath;
}

पूर्णाङ्क av_escape(वर्ण **dst, अचर वर्ण *src, अचर वर्ण *special_chars,
              गणना AVEscapeMode mode, पूर्णाङ्क flags)
{
    AVBPrint dstbuf;
    पूर्णाङ्क ret;

    av_bprint_init(&dstbuf, 1, पूर्णांक_उच्च); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    यदि (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, रिक्त);
        फर्काऊ AVERROR(ENOMEM);
    }
    यदि ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        फर्काऊ ret;
    फर्काऊ dstbuf.len;
}

पूर्णाङ्क av_match_name(अचर वर्ण *name, अचर वर्ण *names)
{
    अचर वर्ण *p;
    माप_प्रकार len, namelen;

    यदि (!name || !names)
        फर्काऊ 0;

    namelen = म_माप(name);
    जबसम्म (*names) {
        पूर्णाङ्क negate = '-' == *names;
        p = म_अक्षर(names, ',');
        यदि (!p)
            p = names + म_माप(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        यदि (!av_strncasecmp(name, names, len) || !म_भेदन("ALL", names, FFMAX(3, p - names)))
            फर्काऊ !negate;
        names = p + (*p == ',');
    }
    फर्काऊ 0;
}

पूर्णाङ्क av_utf8_decode(int32_t *codep, अचर uint8_t **bufp, अचर uint8_t *buf_end,
                   अचिन्हित पूर्णाङ्क flags)
{
    अचर uint8_t *p = *bufp;
    uint32_t शीर्ष;
    uint64_t code;
    पूर्णाङ्क ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    यदि (p >= buf_end)
        फर्काऊ 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    यदि ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        गच्छ end;
    }
    शीर्ष = (code & 128) >> 1;

    tail_len = 0;
    जबसम्म (code & शीर्ष) {
        पूर्णाङ्क tmp;
        tail_len++;
        यदि (p >= buf_end) {
            (*bufp) ++;
            फर्काऊ AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        यदि (tmp>>6) {
            (*bufp) ++;
            फर्काऊ AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        शीर्ष <<= 5;
    }
    code &= (शीर्ष << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    यदि (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        गच्छ end;
    }

    यदि (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        गच्छ end;
    }

    *codep = code;

    यदि (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    यदि (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    यदि (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    यदि ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    फर्काऊ ret;
}

पूर्णाङ्क av_match_list(अचर वर्ण *name, अचर वर्ण *list, वर्ण separator)
{
    अचर वर्ण *p, *q;

    लागि (p = name; p && *p; ) {
        लागि (q = list; q && *q; ) {
            पूर्णाङ्क k;
            लागि (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                यदि (k && (!p[k] || p[k] == separator))
                    फर्काऊ 1;
            q = म_अक्षर(q, separator);
            यदि(q)
                q++;
        }
        p = म_अक्षर(p, separator);
        यदि (p)
            p++;
    }

    फर्काऊ 0;
}
