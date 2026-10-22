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

#समावेश <limits.h>
#समावेश <stdarg.h>
#समावेश <stdint.h>
#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "config.h"
#समावेश "mem.h"
#समावेश "avassert.h"
#समावेश "avstring.h"
#समावेश "bprint.h"
#समावेश "error.h"
#समावेश "macros.h"

पूर्णांक av_strstart(स्थिर अक्षर *str, स्थिर अक्षर *pfx, स्थिर अक्षर **ptr)
{
    जबतक (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    अगर (!*pfx && ptr)
        *ptr = str;
    वापस !*pfx;
}

पूर्णांक av_stristart(स्थिर अक्षर *str, स्थिर अक्षर *pfx, स्थिर अक्षर **ptr)
{
    जबतक (*pfx && av_toupper((अचिन्हित)*pfx) == av_toupper((अचिन्हित)*str)) {
        pfx++;
        str++;
    }
    अगर (!*pfx && ptr)
        *ptr = str;
    वापस !*pfx;
}

अक्षर *av_stristr(स्थिर अक्षर *s1, स्थिर अक्षर *s2)
{
    अगर (!*s2)
        वापस (अक्षर*)(intptr_t)s1;

    करो
        अगर (av_stristart(s1, s2, शून्य))
            वापस (अक्षर*)(intptr_t)s1;
    जबतक (*s1++);

    वापस शून्य;
}

अक्षर *av_strnstr(स्थिर अक्षर *haystack, स्थिर अक्षर *needle, माप_प्रकार hay_लंबाई)
{
    माप_प्रकार needle_len = म_माप(needle);
    अगर (!needle_len)
        वापस (अक्षर*)haystack;
    जबतक (hay_लंबाई >= needle_len) {
        hay_लंबाई--;
        अगर (!स_भेद(haystack, needle, needle_len))
            वापस (अक्षर*)haystack;
        haystack++;
    }
    वापस शून्य;
}

माप_प्रकार av_strlcpy(अक्षर *dst, स्थिर अक्षर *src, माप_प्रकार आकार)
{
    माप_प्रकार len = 0;
    जबतक (++len < आकार && *src)
        *dst++ = *src++;
    अगर (len <= आकार)
        *dst = 0;
    वापस len + म_माप(src) - 1;
}

माप_प्रकार av_strlcat(अक्षर *dst, स्थिर अक्षर *src, माप_प्रकार आकार)
{
    माप_प्रकार len = म_माप(dst);
    अगर (आकार <= len + 1)
        वापस len + म_माप(src);
    वापस len + av_strlcpy(dst + len, src, आकार - len);
}

माप_प्रकार av_strlcatf(अक्षर *dst, माप_प्रकार आकार, स्थिर अक्षर *fmt, ...)
{
    माप_प्रकार len = म_माप(dst);
    बहु_सूची vl;

    बहु_शुरू(vl, fmt);
    len += vsnprintf(dst + len, आकार > len ? आकार - len : 0, fmt, vl);
    बहु_पूर्ण(vl);

    वापस len;
}

अक्षर *av_asprintf(स्थिर अक्षर *fmt, ...)
{
    अक्षर *p = शून्य;
    बहु_सूची va;
    पूर्णांक len;

    बहु_शुरू(va, fmt);
    len = vsnprintf(शून्य, 0, fmt, va);
    बहु_पूर्ण(va);
    अगर (len < 0)
        जाओ end;

    p = av_malloc(len + 1);
    अगर (!p)
        जाओ end;

    बहु_शुरू(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    बहु_पूर्ण(va);
    अगर (len < 0)
        av_freep(&p);

end:
    वापस p;
}

#घोषणा WHITESPACES " \n\t\r"

अक्षर *av_get_token(स्थिर अक्षर **buf, स्थिर अक्षर *term)
{
    अक्षर *out     = av_realloc(शून्य, म_माप(*buf) + 1);
    अक्षर *ret     = out, *end = out;
    स्थिर अक्षर *p = *buf;
    अगर (!out)
        वापस शून्य;
    p += म_अखोज(p, WHITESPACES);

    जबतक (*p && !म_अखोज(p, term)) {
        अक्षर c = *p++;
        अगर (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } अन्यथा अगर (c == '\'') {
            जबतक (*p && *p != '\'')
                *out++ = *p++;
            अगर (*p) {
                p++;
                end = out;
            }
        } अन्यथा {
            *out++ = c;
        }
    }

    करो
        *out-- = 0;
    जबतक (out >= end && म_अखोज(out, WHITESPACES));

    *buf = p;

    अक्षर *small_ret = av_realloc(ret, out - ret + 2);
    वापस small_ret ? small_ret : ret;
}

अक्षर *av_strtok(अक्षर *s, स्थिर अक्षर *delim, अक्षर **saveptr)
{
    अक्षर *tok;

    अगर (!s && !(s = *saveptr))
        वापस शून्य;

    /* skip leading delimiters */
    s += म_अखोज(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    अगर (!*s) {
        *saveptr = शून्य;
        वापस शून्य;
    }
    tok = s++;

    /* skip non delimiters */
    s += म_खोज(s, delim);
    अगर (*s) {
        *s = 0;
        *saveptr = s+1;
    } अन्यथा {
        *saveptr = शून्य;
    }

    वापस tok;
}

पूर्णांक av_strcasecmp(स्थिर अक्षर *a, स्थिर अक्षर *b)
{
    uint8_t c1, c2;
    करो {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } जबतक (c1 && c1 == c2);
    वापस c1 - c2;
}

पूर्णांक av_strncasecmp(स्थिर अक्षर *a, स्थिर अक्षर *b, माप_प्रकार n)
{
    uint8_t c1, c2;
    अगर (n <= 0)
        वापस 0;
    करो {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } जबतक (--n && c1 && c1 == c2);
    वापस c1 - c2;
}

अक्षर *av_strireplace(स्थिर अक्षर *str, स्थिर अक्षर *from, स्थिर अक्षर *to)
{
    अक्षर *ret = शून्य;
    स्थिर अक्षर *pstr2, *pstr = str;
    माप_प्रकार tolen = म_माप(to), fromlen = म_माप(from);
    AVBPrint pbuf;

    अगर (!fromlen)
        वापस av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_आकार_UNLIMITED);
    जबतक ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_तथ्य(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_तथ्य(&pbuf, to, tolen);
    }
    av_bprint_append_तथ्य(&pbuf, pstr, म_माप(pstr));
    अगर (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, शून्य);
    } अन्यथा {
        av_bprint_finalize(&pbuf, &ret);
    }

    वापस ret;
}

स्थिर अक्षर *av_basename(स्थिर अक्षर *path)
{
    अगर (!path || *path == '\0')
        वापस ".";

    स्थिर अक्षर *p = म_खोजप(path, '/');
#अगर HAVE_DOS_PATHS
    स्थिर अक्षर *q = म_खोजप(path, '\\');
    स्थिर अक्षर *d = म_अक्षर(path, ':');
    p = FFMAX3(p, q, d);
#पूर्ण_अगर

    अगर (!p)
        वापस path;

    वापस p + 1;
}

स्थिर अक्षर *av_dirname(अक्षर *path)
{
    अक्षर *p = path ? म_खोजप(path, '/') : शून्य;

#अगर HAVE_DOS_PATHS
    अक्षर *q = path ? म_खोजप(path, '\\') : शून्य;
    अक्षर *d = path ? म_अक्षर(path, ':')  : शून्य;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#पूर्ण_अगर

    अगर (!p)
        वापस ".";

    *p = '\0';

    वापस path;
}

अक्षर *av_append_path_component(स्थिर अक्षर *path, स्थिर अक्षर *component)
{
    माप_प्रकार p_len, c_len;
    अक्षर *fullpath;

    अगर (!path)
        वापस av_strdup(component);
    अगर (!component)
        वापस av_strdup(path);

    p_len = म_माप(path);
    c_len = म_माप(component);
    अगर (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        वापस शून्य;
    fullpath = av_malloc(p_len + c_len + 2);
    अगर (fullpath) {
        अगर (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            अगर (c_len) {
                अगर (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                अन्यथा अगर (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    वापस fullpath;
}

पूर्णांक av_escape(अक्षर **dst, स्थिर अक्षर *src, स्थिर अक्षर *special_chars,
              क्रमागत AVEscapeMode mode, पूर्णांक flags)
{
    AVBPrint dstbuf;
    पूर्णांक ret;

    av_bprint_init(&dstbuf, 1, पूर्णांक_उच्च); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    अगर (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, शून्य);
        वापस AVERROR(ENOMEM);
    }
    अगर ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        वापस ret;
    वापस dstbuf.len;
}

पूर्णांक av_match_name(स्थिर अक्षर *name, स्थिर अक्षर *names)
{
    स्थिर अक्षर *p;
    माप_प्रकार len, namelen;

    अगर (!name || !names)
        वापस 0;

    namelen = म_माप(name);
    जबतक (*names) {
        पूर्णांक negate = '-' == *names;
        p = म_अक्षर(names, ',');
        अगर (!p)
            p = names + म_माप(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        अगर (!av_strncasecmp(name, names, len) || !म_भेदन("ALL", names, FFMAX(3, p - names)))
            वापस !negate;
        names = p + (*p == ',');
    }
    वापस 0;
}

पूर्णांक av_utf8_decode(int32_t *codep, स्थिर uint8_t **bufp, स्थिर uint8_t *buf_end,
                   अचिन्हित पूर्णांक flags)
{
    स्थिर uint8_t *p = *bufp;
    uint32_t शीर्ष;
    uint64_t code;
    पूर्णांक ret = 0, पुच्छ_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    अगर (p >= buf_end)
        वापस 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    अगर ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        जाओ end;
    }
    शीर्ष = (code & 128) >> 1;

    पुच्छ_len = 0;
    जबतक (code & शीर्ष) {
        पूर्णांक tmp;
        पुच्छ_len++;
        अगर (p >= buf_end) {
            (*bufp) ++;
            वापस AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        अगर (tmp>>6) {
            (*bufp) ++;
            वापस AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        शीर्ष <<= 5;
    }
    code &= (शीर्ष << 1) - 1;

    /* check for overlong encodings */
    av_assert0(पुच्छ_len <= 5);
    अगर (code < overlong_encoding_mins[पुच्छ_len]) {
        ret = AVERROR(EILSEQ);
        जाओ end;
    }

    अगर (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        जाओ end;
    }

    *codep = code;

    अगर (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    अगर (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    अगर (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    अगर ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    वापस ret;
}

पूर्णांक av_match_list(स्थिर अक्षर *name, स्थिर अक्षर *list, अक्षर separator)
{
    स्थिर अक्षर *p, *q;

    क्रम (p = name; p && *p; ) {
        क्रम (q = list; q && *q; ) {
            पूर्णांक k;
            क्रम (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                अगर (k && (!p[k] || p[k] == separator))
                    वापस 1;
            q = म_अक्षर(q, separator);
            अगर(q)
                q++;
        }
        p = म_अक्षर(p, separator);
        अगर (p)
            p++;
    }

    वापस 0;
}
