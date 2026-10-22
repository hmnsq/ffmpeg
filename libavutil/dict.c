/*
 * copyright (c) 2009 Michael Niedermayer
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

#അന്തര്ഭാവ <inttypes.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "avstring.h"
#അന്തര്ഭാവ "dict.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "bprint.h"

ഘടന AVDictionary {
    പൂർണ്ണസംഖ്യ എണ്ണം;
    AVDictionaryEntry *elems;
    പൂർണ്ണസംഖ്യ duplicate_താക്കോലുകൾ;
};

പൂർണ്ണസംഖ്യ av_dict_എണ്ണം(സ്ഥിരം AVDictionary *m)
{
    തിരികെ m ? m->എണ്ണം : 0;
}

സ്ഥിരം AVDictionaryEntry *av_dict_iterate(സ്ഥിരം AVDictionary *m,
                                         സ്ഥിരം AVDictionaryEntry *prev)
{
    പൂർണ്ണസംഖ്യ i = 0;

    എങ്കിൽ (!m)
        തിരികെ ശൂന്യ;

    എങ്കിൽ (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    എങ്കിൽ (i >= m->എണ്ണം)
        തിരികെ ശൂന്യ;

    തിരികെ &m->elems[i];
}

AVDictionaryEntry *av_dict_get(സ്ഥിരം AVDictionary *m, സ്ഥിരം അക്ഷരം *താക്കോൽ,
                               സ്ഥിരം AVDictionaryEntry *prev, പൂർണ്ണസംഖ്യ flags)
{
    സ്ഥിരം AVDictionaryEntry *entry = prev;
    unsigned പൂർണ്ണസംഖ്യ j;

    എങ്കിൽ (!താക്കോൽ)
        തിരികെ ശൂന്യ;

    ആകുമ്പോൾ ((entry = av_dict_iterate(m, entry))) {
        സ്ഥിരം അക്ഷരം *s = entry->താക്കോൽ;
        എങ്കിൽ (flags & AV_DICT_MATCH_CASE)
            വേണ്ടി (j = 0; s[j] == താക്കോൽ[j] && താക്കോൽ[j]; j++)
                ;
        അല്ലെങ്കിൽ
            വേണ്ടി (j = 0; av_toupper(s[j]) == av_toupper(താക്കോൽ[j]) && താക്കോൽ[j]; j++)
                ;
        എങ്കിൽ (താക്കോൽ[j])
            തുടരുക;
        എങ്കിൽ (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            തുടരുക;
        തിരികെ (AVDictionaryEntry *)entry;
    }
    തിരികെ ശൂന്യ;
}

പൂർണ്ണസംഖ്യ av_dict_set(AVDictionary **pm, സ്ഥിരം അക്ഷരം *താക്കോൽ, സ്ഥിരം അക്ഷരം *മൂല്യം,
                പൂർണ്ണസംഖ്യ flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = ശൂന്യ;
    അക്ഷരം *copy_താക്കോൽ = ശൂന്യ, *copy_മൂല്യം = ശൂന്യ;
    പൂർണ്ണസംഖ്യ err;

    എങ്കിൽ (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_മൂല്യം = (ശൂന്യം *)മൂല്യം;
    അല്ലെങ്കിൽ എങ്കിൽ (മൂല്യം)
        copy_മൂല്യം = av_strdup(മൂല്യം);
    എങ്കിൽ (!താക്കോൽ) {
        err = AVERROR(EINVAL);
        പോകുക err_out;
    }
    എങ്കിൽ (flags & AV_DICT_DONT_STRDUP_താക്കോൽ)
        copy_താക്കോൽ = (ശൂന്യം *)താക്കോൽ;
    അല്ലെങ്കിൽ
        copy_താക്കോൽ = av_strdup(താക്കോൽ);
    എങ്കിൽ (!copy_താക്കോൽ || (മൂല്യം && !copy_മൂല്യം))
        പോകുക enomem;

    എങ്കിൽ (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, താക്കോൽ, ശൂന്യ, flags);
    } അല്ലെങ്കിൽ എങ്കിൽ (flags & AV_DICT_DEDUP) {
        ആകുമ്പോൾ ((tag = av_dict_get(m, താക്കോൽ, tag, flags))) {
            എങ്കിൽ ((!മൂല്യം && !tag->മൂല്യം) ||
                (മൂല്യം && tag->മൂല്യം && !strcmp(മൂല്യം, tag->മൂല്യം))) {
                av_free(copy_താക്കോൽ);
                av_free(copy_മൂല്യം);
                തിരികെ 0;
            }
        }
    }
    എങ്കിൽ (!m)
        m = *pm = av_mallocz(വലുപ്പം(*m));
    എങ്കിൽ (!m)
        പോകുക enomem;

    എങ്കിൽ (tag) {
        എങ്കിൽ (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_താക്കോൽ);
            av_free(copy_മൂല്യം);
            തിരികെ 0;
        }
        എങ്കിൽ (copy_മൂല്യം && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->മൂല്യം);
            size_t new_part_len = strlen(copy_മൂല്യം);
            size_t len = oldlen + new_part_len + 1;
            അക്ഷരം *newval = av_realloc(tag->മൂല്യം, len);
            എങ്കിൽ (!newval)
                പോകുക enomem;
            memcpy(newval + oldlen, copy_മൂല്യം, new_part_len + 1);
            av_freep(&copy_മൂല്യം);
            copy_മൂല്യം = newval;
        } അല്ലെങ്കിൽ
            av_free(tag->മൂല്യം);
        av_free(tag->താക്കോൽ);
        *tag = m->elems[--m->എണ്ണം];
    } അല്ലെങ്കിൽ എങ്കിൽ (copy_മൂല്യം) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->എണ്ണം + 1, വലുപ്പം(*m->elems));
        എങ്കിൽ (!tmp)
            പോകുക enomem;
        m->elems = tmp;
    }
    എങ്കിൽ (copy_മൂല്യം) {
        m->elems[m->എണ്ണം].താക്കോൽ = copy_താക്കോൽ;
        m->elems[m->എണ്ണം].മൂല്യം = copy_മൂല്യം;
        m->എണ്ണം++;
        എങ്കിൽ (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_താക്കോലുകൾ = 1;
    } അല്ലെങ്കിൽ {
        err = 0;
        പോകുക end;
    }

    തിരികെ 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_മൂല്യം);
end:
    എങ്കിൽ (m && !m->എണ്ണം) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_താക്കോൽ);
    തിരികെ err;
}

പൂർണ്ണസംഖ്യ av_dict_set_int(AVDictionary **pm, സ്ഥിരം അക്ഷരം *താക്കോൽ, int64_t മൂല്യം,
                പൂർണ്ണസംഖ്യ flags)
{
    അക്ഷരം valuestr[22];
    snprintf(valuestr, വലുപ്പം(valuestr), "%"PRId64, മൂല്യം);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    തിരികെ av_dict_set(pm, താക്കോൽ, valuestr, flags);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ parse_താക്കോൽ_മൂല്യം_pair(AVDictionary **pm, സ്ഥിരം അക്ഷരം **buf,
                                സ്ഥിരം അക്ഷരം *താക്കോൽ_val_sep, സ്ഥിരം അക്ഷരം *pairs_sep,
                                പൂർണ്ണസംഖ്യ flags)
{
    അക്ഷരം *താക്കോൽ = av_get_token(buf, താക്കോൽ_val_sep);
    അക്ഷരം *val = ശൂന്യ;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (താക്കോൽ && *താക്കോൽ && strspn(*buf, താക്കോൽ_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    എങ്കിൽ (താക്കോൽ && *താക്കോൽ && val && *val)
        ret = av_dict_set(pm, താക്കോൽ, val, flags);
    അല്ലെങ്കിൽ
        ret = AVERROR(EINVAL);

    av_freep(&താക്കോൽ);
    av_freep(&val);

    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_dict_parse_string(AVDictionary **pm, സ്ഥിരം അക്ഷരം *str,
                         സ്ഥിരം അക്ഷരം *താക്കോൽ_val_sep, സ്ഥിരം അക്ഷരം *pairs_sep,
                         പൂർണ്ണസംഖ്യ flags)
{
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (!str)
        തിരികെ 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_താക്കോൽ | AV_DICT_DONT_STRDUP_VAL);

    ആകുമ്പോൾ (*str) {
        എങ്കിൽ ((ret = parse_താക്കോൽ_മൂല്യം_pair(pm, &str, താക്കോൽ_val_sep, pairs_sep, flags)) < 0)
            തിരികെ ret;

        എങ്കിൽ (*str)
            str++;
    }

    തിരികെ 0;
}

ശൂന്യം av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    എങ്കിൽ (m) {
        ആകുമ്പോൾ (m->എണ്ണം--) {
            av_freep(&m->elems[m->എണ്ണം].താക്കോൽ);
            av_freep(&m->elems[m->എണ്ണം].മൂല്യം);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

പൂർണ്ണസംഖ്യ av_dict_copy(AVDictionary **dst, സ്ഥിരം AVDictionary *src, പൂർണ്ണസംഖ്യ flags)
{
    സ്ഥിരം AVDictionaryEntry *t = ശൂന്യ;

    എങ്കിൽ (!*dst && src && src->എണ്ണം && !src->duplicate_താക്കോലുകൾ &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(വലുപ്പം(*m));
        എങ്കിൽ (!m)
            തിരികെ AVERROR(ENOMEM);
        m->elems = av_calloc(src->എണ്ണം, വലുപ്പം(*m->elems));
        എങ്കിൽ (!m->elems) {
            av_free(m);
            തിരികെ AVERROR(ENOMEM);
        }
        *dst = m;
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < src->എണ്ണം; i++) {
            m->elems[i].താക്കോൽ   = av_strdup(src->elems[i].താക്കോൽ);
            m->elems[i].മൂല്യം = av_strdup(src->elems[i].മൂല്യം);
            m->എണ്ണം++;
            എങ്കിൽ (!m->elems[i].താക്കോൽ || !m->elems[i].മൂല്യം) {
                av_dict_free(dst);
                തിരികെ AVERROR(ENOMEM);
            }
        }
        തിരികെ 0;
    }

    ആകുമ്പോൾ ((t = av_dict_iterate(src, t))) {
        പൂർണ്ണസംഖ്യ ret = av_dict_set(dst, t->താക്കോൽ, t->മൂല്യം, flags);
        എങ്കിൽ (ret < 0)
            തിരികെ ret;
    }

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_dict_get_string(സ്ഥിരം AVDictionary *m, അക്ഷരം **buffer,
                       സ്ഥിരം അക്ഷരം താക്കോൽ_val_sep, സ്ഥിരം അക്ഷരം pairs_sep)
{
    സ്ഥിരം AVDictionaryEntry *t = ശൂന്യ;
    AVBPrint bprint;
    പൂർണ്ണസംഖ്യ cnt = 0;
    അക്ഷരം special_chars[] = {pairs_sep, താക്കോൽ_val_sep, '\0'};

    എങ്കിൽ (!buffer || pairs_sep == '\0' || താക്കോൽ_val_sep == '\0' || pairs_sep == താക്കോൽ_val_sep ||
        pairs_sep == '\\' || താക്കോൽ_val_sep == '\\')
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (!av_dict_എണ്ണം(m)) {
        *buffer = av_strdup("");
        തിരികെ *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    ആകുമ്പോൾ ((t = av_dict_iterate(m, t))) {
        എങ്കിൽ (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->താക്കോൽ, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &താക്കോൽ_val_sep, 1);
        av_bprint_escape(&bprint, t->മൂല്യം, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    തിരികെ av_bprint_finalize(&bprint, buffer);
}
