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

#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <stdarg.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "avstring.h"
#അന്തര്ഭാവ "bprint.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "macros.h"

പൂർണ്ണസംഖ്യ av_strstart(സ്ഥിരം അക്ഷരം *str, സ്ഥിരം അക്ഷരം *pfx, സ്ഥിരം അക്ഷരം **ptr)
{
    ആകുമ്പോൾ (*pfx && *pfx == *str) {
        pfx++;
        str++;
    }
    എങ്കിൽ (!*pfx && ptr)
        *ptr = str;
    തിരികെ !*pfx;
}

പൂർണ്ണസംഖ്യ av_stristart(സ്ഥിരം അക്ഷരം *str, സ്ഥിരം അക്ഷരം *pfx, സ്ഥിരം അക്ഷരം **ptr)
{
    ആകുമ്പോൾ (*pfx && av_toupper((unsigned)*pfx) == av_toupper((unsigned)*str)) {
        pfx++;
        str++;
    }
    എങ്കിൽ (!*pfx && ptr)
        *ptr = str;
    തിരികെ !*pfx;
}

അക്ഷരം *av_stristr(സ്ഥിരം അക്ഷരം *s1, സ്ഥിരം അക്ഷരം *s2)
{
    എങ്കിൽ (!*s2)
        തിരികെ (അക്ഷരം*)(intptr_t)s1;

    ചെയ്യുക
        എങ്കിൽ (av_stristart(s1, s2, ശൂന്യ))
            തിരികെ (അക്ഷരം*)(intptr_t)s1;
    ആകുമ്പോൾ (*s1++);

    തിരികെ ശൂന്യ;
}

അക്ഷരം *av_strnstr(സ്ഥിരം അക്ഷരം *haystack, സ്ഥിരം അക്ഷരം *needle, size_t hay_length)
{
    size_t needle_len = strlen(needle);
    എങ്കിൽ (!needle_len)
        തിരികെ (അക്ഷരം*)haystack;
    ആകുമ്പോൾ (hay_length >= needle_len) {
        hay_length--;
        എങ്കിൽ (!memcmp(haystack, needle, needle_len))
            തിരികെ (അക്ഷരം*)haystack;
        haystack++;
    }
    തിരികെ ശൂന്യ;
}

size_t av_strlcpy(അക്ഷരം *dst, സ്ഥിരം അക്ഷരം *src, size_t size)
{
    size_t len = 0;
    ആകുമ്പോൾ (++len < size && *src)
        *dst++ = *src++;
    എങ്കിൽ (len <= size)
        *dst = 0;
    തിരികെ len + strlen(src) - 1;
}

size_t av_strlcat(അക്ഷരം *dst, സ്ഥിരം അക്ഷരം *src, size_t size)
{
    size_t len = strlen(dst);
    എങ്കിൽ (size <= len + 1)
        തിരികെ len + strlen(src);
    തിരികെ len + av_strlcpy(dst + len, src, size - len);
}

size_t av_strlcatf(അക്ഷരം *dst, size_t size, സ്ഥിരം അക്ഷരം *fmt, ...)
{
    size_t len = strlen(dst);
    va_list vl;

    va_start(vl, fmt);
    len += vsnprintf(dst + len, size > len ? size - len : 0, fmt, vl);
    va_end(vl);

    തിരികെ len;
}

അക്ഷരം *av_asprintf(സ്ഥിരം അക്ഷരം *fmt, ...)
{
    അക്ഷരം *p = ശൂന്യ;
    va_list va;
    പൂർണ്ണസംഖ്യ len;

    va_start(va, fmt);
    len = vsnprintf(ശൂന്യ, 0, fmt, va);
    va_end(va);
    എങ്കിൽ (len < 0)
        പോകുക end;

    p = av_malloc(len + 1);
    എങ്കിൽ (!p)
        പോകുക end;

    va_start(va, fmt);
    len = vsnprintf(p, len + 1, fmt, va);
    va_end(va);
    എങ്കിൽ (len < 0)
        av_freep(&p);

end:
    തിരികെ p;
}

#define WHITESPACES " \n\t\r"

അക്ഷരം *av_get_token(സ്ഥിരം അക്ഷരം **buf, സ്ഥിരം അക്ഷരം *term)
{
    അക്ഷരം *out     = av_realloc(ശൂന്യ, strlen(*buf) + 1);
    അക്ഷരം *ret     = out, *end = out;
    സ്ഥിരം അക്ഷരം *p = *buf;
    എങ്കിൽ (!out)
        തിരികെ ശൂന്യ;
    p += strspn(p, WHITESPACES);

    ആകുമ്പോൾ (*p && !strspn(p, term)) {
        അക്ഷരം c = *p++;
        എങ്കിൽ (c == '\\' && *p) {
            *out++ = *p++;
            end    = out;
        } അല്ലെങ്കിൽ എങ്കിൽ (c == '\'') {
            ആകുമ്പോൾ (*p && *p != '\'')
                *out++ = *p++;
            എങ്കിൽ (*p) {
                p++;
                end = out;
            }
        } അല്ലെങ്കിൽ {
            *out++ = c;
        }
    }

    ചെയ്യുക
        *out-- = 0;
    ആകുമ്പോൾ (out >= end && strspn(out, WHITESPACES));

    *buf = p;

    അക്ഷരം *small_ret = av_realloc(ret, out - ret + 2);
    തിരികെ small_ret ? small_ret : ret;
}

അക്ഷരം *av_strtok(അക്ഷരം *s, സ്ഥിരം അക്ഷരം *delim, അക്ഷരം **saveptr)
{
    അക്ഷരം *tok;

    എങ്കിൽ (!s && !(s = *saveptr))
        തിരികെ ശൂന്യ;

    /* skip leading delimiters */
    s += strspn(s, delim);

    /* s now points to the first non delimiter char, or to the end of the string */
    എങ്കിൽ (!*s) {
        *saveptr = ശൂന്യ;
        തിരികെ ശൂന്യ;
    }
    tok = s++;

    /* skip non delimiters */
    s += strcspn(s, delim);
    എങ്കിൽ (*s) {
        *s = 0;
        *saveptr = s+1;
    } അല്ലെങ്കിൽ {
        *saveptr = ശൂന്യ;
    }

    തിരികെ tok;
}

പൂർണ്ണസംഖ്യ av_strcasecmp(സ്ഥിരം അക്ഷരം *a, സ്ഥിരം അക്ഷരം *b)
{
    uint8_t c1, c2;
    ചെയ്യുക {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ആകുമ്പോൾ (c1 && c1 == c2);
    തിരികെ c1 - c2;
}

പൂർണ്ണസംഖ്യ av_strncasecmp(സ്ഥിരം അക്ഷരം *a, സ്ഥിരം അക്ഷരം *b, size_t n)
{
    uint8_t c1, c2;
    എങ്കിൽ (n <= 0)
        തിരികെ 0;
    ചെയ്യുക {
        c1 = av_tolower(*a++);
        c2 = av_tolower(*b++);
    } ആകുമ്പോൾ (--n && c1 && c1 == c2);
    തിരികെ c1 - c2;
}

അക്ഷരം *av_strireplace(സ്ഥിരം അക്ഷരം *str, സ്ഥിരം അക്ഷരം *from, സ്ഥിരം അക്ഷരം *to)
{
    അക്ഷരം *ret = ശൂന്യ;
    സ്ഥിരം അക്ഷരം *pstr2, *pstr = str;
    size_t tolen = strlen(to), fromlen = strlen(from);
    AVBPrint pbuf;

    എങ്കിൽ (!fromlen)
        തിരികെ av_strdup(str);

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    ആകുമ്പോൾ ((pstr2 = av_stristr(pstr, from))) {
        av_bprint_append_data(&pbuf, pstr, pstr2 - pstr);
        pstr = pstr2 + fromlen;
        av_bprint_append_data(&pbuf, to, tolen);
    }
    av_bprint_append_data(&pbuf, pstr, strlen(pstr));
    എങ്കിൽ (!av_bprint_is_complete(&pbuf)) {
        av_bprint_finalize(&pbuf, ശൂന്യ);
    } അല്ലെങ്കിൽ {
        av_bprint_finalize(&pbuf, &ret);
    }

    തിരികെ ret;
}

സ്ഥിരം അക്ഷരം *av_basename(സ്ഥിരം അക്ഷരം *path)
{
    എങ്കിൽ (!path || *path == '\0')
        തിരികെ ".";

    സ്ഥിരം അക്ഷരം *p = strrchr(path, '/');
#എങ്കിൽ HAVE_DOS_PATHS
    സ്ഥിരം അക്ഷരം *q = strrchr(path, '\\');
    സ്ഥിരം അക്ഷരം *d = strchr(path, ':');
    p = FFMAX3(p, q, d);
#endif

    എങ്കിൽ (!p)
        തിരികെ path;

    തിരികെ p + 1;
}

സ്ഥിരം അക്ഷരം *av_dirname(അക്ഷരം *path)
{
    അക്ഷരം *p = path ? strrchr(path, '/') : ശൂന്യ;

#എങ്കിൽ HAVE_DOS_PATHS
    അക്ഷരം *q = path ? strrchr(path, '\\') : ശൂന്യ;
    അക്ഷരം *d = path ? strchr(path, ':')  : ശൂന്യ;

    d = d ? d + 1 : d;

    p = FFMAX3(p, q, d);
#endif

    എങ്കിൽ (!p)
        തിരികെ ".";

    *p = '\0';

    തിരികെ path;
}

അക്ഷരം *av_append_path_component(സ്ഥിരം അക്ഷരം *path, സ്ഥിരം അക്ഷരം *component)
{
    size_t p_len, c_len;
    അക്ഷരം *fullpath;

    എങ്കിൽ (!path)
        തിരികെ av_strdup(component);
    എങ്കിൽ (!component)
        തിരികെ av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    എങ്കിൽ (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        തിരികെ ശൂന്യ;
    fullpath = av_malloc(p_len + c_len + 2);
    എങ്കിൽ (fullpath) {
        എങ്കിൽ (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            എങ്കിൽ (c_len) {
                എങ്കിൽ (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                അല്ലെങ്കിൽ എങ്കിൽ (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    തിരികെ fullpath;
}

പൂർണ്ണസംഖ്യ av_escape(അക്ഷരം **dst, സ്ഥിരം അക്ഷരം *src, സ്ഥിരം അക്ഷരം *special_chars,
              എണ്ണൽ AVEscapeMode mode, പൂർണ്ണസംഖ്യ flags)
{
    AVBPrint dstbuf;
    പൂർണ്ണസംഖ്യ ret;

    av_bprint_init(&dstbuf, 1, INT_MAX); /* (int)dstbuf.len must be >= 0 */
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    എങ്കിൽ (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, ശൂന്യ);
        തിരികെ AVERROR(ENOMEM);
    }
    എങ്കിൽ ((ret = av_bprint_finalize(&dstbuf, dst)) < 0)
        തിരികെ ret;
    തിരികെ dstbuf.len;
}

പൂർണ്ണസംഖ്യ av_match_name(സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *names)
{
    സ്ഥിരം അക്ഷരം *p;
    size_t len, namelen;

    എങ്കിൽ (!name || !names)
        തിരികെ 0;

    namelen = strlen(name);
    ആകുമ്പോൾ (*names) {
        പൂർണ്ണസംഖ്യ negate = '-' == *names;
        p = strchr(names, ',');
        എങ്കിൽ (!p)
            p = names + strlen(names);
        names += negate;
        len = FFMAX(p - names, namelen);
        എങ്കിൽ (!av_strncasecmp(name, names, len) || !strncmp("ALL", names, FFMAX(3, p - names)))
            തിരികെ !negate;
        names = p + (*p == ',');
    }
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_utf8_decode(int32_t *codep, സ്ഥിരം uint8_t **bufp, സ്ഥിരം uint8_t *buf_end,
                   unsigned പൂർണ്ണസംഖ്യ flags)
{
    സ്ഥിരം uint8_t *p = *bufp;
    uint32_t മുകൾ;
    uint64_t code;
    പൂർണ്ണസംഖ്യ ret = 0, tail_len;
    uint32_t overlong_encoding_mins[6] = {
        0x00000000, 0x00000080, 0x00000800, 0x00010000, 0x00200000, 0x04000000,
    };

    എങ്കിൽ (p >= buf_end)
        തിരികെ 0;

    code = *p++;

    /* first sequence byte starts with 10, or is 1111-1110 or 1111-1111,
       which is not admitted */
    എങ്കിൽ ((code & 0xc0) == 0x80 || code >= 0xFE) {
        ret = AVERROR(EILSEQ);
        പോകുക end;
    }
    മുകൾ = (code & 128) >> 1;

    tail_len = 0;
    ആകുമ്പോൾ (code & മുകൾ) {
        പൂർണ്ണസംഖ്യ tmp;
        tail_len++;
        എങ്കിൽ (p >= buf_end) {
            (*bufp) ++;
            തിരികെ AVERROR(EILSEQ); /* incomplete sequence */
        }

        /* we assume the byte to be in the form 10xx-xxxx */
        tmp = *p++ - 128;   /* strip leading 1 */
        എങ്കിൽ (tmp>>6) {
            (*bufp) ++;
            തിരികെ AVERROR(EILSEQ);
        }
        code = (code<<6) + tmp;
        മുകൾ <<= 5;
    }
    code &= (മുകൾ << 1) - 1;

    /* check for overlong encodings */
    av_assert0(tail_len <= 5);
    എങ്കിൽ (code < overlong_encoding_mins[tail_len]) {
        ret = AVERROR(EILSEQ);
        പോകുക end;
    }

    എങ്കിൽ (code >= 1U<<31) {
        ret = AVERROR(EILSEQ);  /* out-of-range value */
        പോകുക end;
    }

    *codep = code;

    എങ്കിൽ (code > 0x10FFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_INVALID_BIG_CODES))
        ret = AVERROR(EILSEQ);
    എങ്കിൽ (code < 0x20 && code != 0x9 && code != 0xA && code != 0xD &&
        flags & AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES)
        ret = AVERROR(EILSEQ);
    എങ്കിൽ (code >= 0xD800 && code <= 0xDFFF &&
        !(flags & AV_UTF8_FLAG_ACCEPT_SURROGATES))
        ret = AVERROR(EILSEQ);
    എങ്കിൽ ((code == 0xFFFE || code == 0xFFFF) &&
        !(flags & AV_UTF8_FLAG_ACCEPT_NON_CHARACTERS))
        ret = AVERROR(EILSEQ);

end:
    *bufp = p;
    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_match_list(സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *list, അക്ഷരം separator)
{
    സ്ഥിരം അക്ഷരം *p, *q;

    വേണ്ടി (p = name; p && *p; ) {
        വേണ്ടി (q = list; q && *q; ) {
            പൂർണ്ണസംഖ്യ k;
            വേണ്ടി (k = 0; p[k] == q[k] || (p[k]*q[k] == 0 && p[k]+q[k] == separator); k++)
                എങ്കിൽ (k && (!p[k] || p[k] == separator))
                    തിരികെ 1;
            q = strchr(q, separator);
            എങ്കിൽ(q)
                q++;
        }
        p = strchr(p, separator);
        എങ്കിൽ (p)
            p++;
    }

    തിരികെ 0;
}
