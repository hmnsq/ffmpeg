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

#અન્તર્ભાવ <inttypes.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "avstring.h"
#અન્તર્ભાવ "dict.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "bprint.h"

સંરચના AVDictionary {
    પૂર્ણાંક ગણતરી;
    AVDictionaryEntry *elems;
    પૂર્ણાંક duplicate_ચાવીઓ;
};

પૂર્ણાંક av_dict_ગણતરી(અચલ AVDictionary *m)
{
    પાછા m ? m->ગણતરી : 0;
}

અચલ AVDictionaryEntry *av_dict_iterate(અચલ AVDictionary *m,
                                         અચલ AVDictionaryEntry *prev)
{
    પૂર્ણાંક i = 0;

    જો (!m)
        પાછા ખાલી;

    જો (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    જો (i >= m->ગણતરી)
        પાછા ખાલી;

    પાછા &m->elems[i];
}

AVDictionaryEntry *av_dict_get(અચલ AVDictionary *m, અચલ અક્ષર *ચાવી,
                               અચલ AVDictionaryEntry *prev, પૂર્ણાંક flags)
{
    અચલ AVDictionaryEntry *entry = prev;
    unsigned પૂર્ણાંક j;

    જો (!ચાવી)
        પાછા ખાલી;

    જ્યારે ((entry = av_dict_iterate(m, entry))) {
        અચલ અક્ષર *s = entry->ચાવી;
        જો (flags & AV_DICT_MATCH_CASE)
            માટે (j = 0; s[j] == ચાવી[j] && ચાવી[j]; j++)
                ;
        નહીંતર
            માટે (j = 0; av_toupper(s[j]) == av_toupper(ચાવી[j]) && ચાવી[j]; j++)
                ;
        જો (ચાવી[j])
            ચાલુ;
        જો (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            ચાલુ;
        પાછા (AVDictionaryEntry *)entry;
    }
    પાછા ખાલી;
}

પૂર્ણાંક av_dict_set(AVDictionary **pm, અચલ અક્ષર *ચાવી, અચલ અક્ષર *કિંમત,
                પૂર્ણાંક flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = ખાલી;
    અક્ષર *copy_ચાવી = ખાલી, *copy_કિંમત = ખાલી;
    પૂર્ણાંક err;

    જો (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_કિંમત = (શૂન્ય *)કિંમત;
    નહીંતર જો (કિંમત)
        copy_કિંમત = av_strdup(કિંમત);
    જો (!ચાવી) {
        err = AVERROR(EINVAL);
        જાઓ err_out;
    }
    જો (flags & AV_DICT_DONT_STRDUP_ચાવી)
        copy_ચાવી = (શૂન્ય *)ચાવી;
    નહીંતર
        copy_ચાવી = av_strdup(ચાવી);
    જો (!copy_ચાવી || (કિંમત && !copy_કિંમત))
        જાઓ enomem;

    જો (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, ચાવી, ખાલી, flags);
    } નહીંતર જો (flags & AV_DICT_DEDUP) {
        જ્યારે ((tag = av_dict_get(m, ચાવી, tag, flags))) {
            જો ((!કિંમત && !tag->કિંમત) ||
                (કિંમત && tag->કિંમત && !strcmp(કિંમત, tag->કિંમત))) {
                av_free(copy_ચાવી);
                av_free(copy_કિંમત);
                પાછા 0;
            }
        }
    }
    જો (!m)
        m = *pm = av_mallocz(કદ(*m));
    જો (!m)
        જાઓ enomem;

    જો (tag) {
        જો (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_ચાવી);
            av_free(copy_કિંમત);
            પાછા 0;
        }
        જો (copy_કિંમત && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->કિંમત);
            size_t new_part_len = strlen(copy_કિંમત);
            size_t len = oldlen + new_part_len + 1;
            અક્ષર *newval = av_realloc(tag->કિંમત, len);
            જો (!newval)
                જાઓ enomem;
            memcpy(newval + oldlen, copy_કિંમત, new_part_len + 1);
            av_freep(&copy_કિંમત);
            copy_કિંમત = newval;
        } નહીંતર
            av_free(tag->કિંમત);
        av_free(tag->ચાવી);
        *tag = m->elems[--m->ગણતરી];
    } નહીંતર જો (copy_કિંમત) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->ગણતરી + 1, કદ(*m->elems));
        જો (!tmp)
            જાઓ enomem;
        m->elems = tmp;
    }
    જો (copy_કિંમત) {
        m->elems[m->ગણતરી].ચાવી = copy_ચાવી;
        m->elems[m->ગણતરી].કિંમત = copy_કિંમત;
        m->ગણતરી++;
        જો (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_ચાવીઓ = 1;
    } નહીંતર {
        err = 0;
        જાઓ end;
    }

    પાછા 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_કિંમત);
end:
    જો (m && !m->ગણતરી) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_ચાવી);
    પાછા err;
}

પૂર્ણાંક av_dict_set_int(AVDictionary **pm, અચલ અક્ષર *ચાવી, int64_t કિંમત,
                પૂર્ણાંક flags)
{
    અક્ષર valuestr[22];
    snprintf(valuestr, કદ(valuestr), "%"PRId64, કિંમત);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    પાછા av_dict_set(pm, ચાવી, valuestr, flags);
}

સ્થિર પૂર્ણાંક parse_ચાવી_કિંમત_pair(AVDictionary **pm, અચલ અક્ષર **buf,
                                અચલ અક્ષર *ચાવી_val_sep, અચલ અક્ષર *pairs_sep,
                                પૂર્ણાંક flags)
{
    અક્ષર *ચાવી = av_get_token(buf, ચાવી_val_sep);
    અક્ષર *val = ખાલી;
    પૂર્ણાંક ret;

    જો (ચાવી && *ચાવી && strspn(*buf, ચાવી_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    જો (ચાવી && *ચાવી && val && *val)
        ret = av_dict_set(pm, ચાવી, val, flags);
    નહીંતર
        ret = AVERROR(EINVAL);

    av_freep(&ચાવી);
    av_freep(&val);

    પાછા ret;
}

પૂર્ણાંક av_dict_parse_string(AVDictionary **pm, અચલ અક્ષર *str,
                         અચલ અક્ષર *ચાવી_val_sep, અચલ અક્ષર *pairs_sep,
                         પૂર્ણાંક flags)
{
    પૂર્ણાંક ret;

    જો (!str)
        પાછા 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_ચાવી | AV_DICT_DONT_STRDUP_VAL);

    જ્યારે (*str) {
        જો ((ret = parse_ચાવી_કિંમત_pair(pm, &str, ચાવી_val_sep, pairs_sep, flags)) < 0)
            પાછા ret;

        જો (*str)
            str++;
    }

    પાછા 0;
}

શૂન્ય av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    જો (m) {
        જ્યારે (m->ગણતરી--) {
            av_freep(&m->elems[m->ગણતરી].ચાવી);
            av_freep(&m->elems[m->ગણતરી].કિંમત);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

પૂર્ણાંક av_dict_copy(AVDictionary **dst, અચલ AVDictionary *src, પૂર્ણાંક flags)
{
    અચલ AVDictionaryEntry *t = ખાલી;

    જો (!*dst && src && src->ગણતરી && !src->duplicate_ચાવીઓ &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(કદ(*m));
        જો (!m)
            પાછા AVERROR(ENOMEM);
        m->elems = av_calloc(src->ગણતરી, કદ(*m->elems));
        જો (!m->elems) {
            av_free(m);
            પાછા AVERROR(ENOMEM);
        }
        *dst = m;
        માટે (પૂર્ણાંક i = 0; i < src->ગણતરી; i++) {
            m->elems[i].ચાવી   = av_strdup(src->elems[i].ચાવી);
            m->elems[i].કિંમત = av_strdup(src->elems[i].કિંમત);
            m->ગણતરી++;
            જો (!m->elems[i].ચાવી || !m->elems[i].કિંમત) {
                av_dict_free(dst);
                પાછા AVERROR(ENOMEM);
            }
        }
        પાછા 0;
    }

    જ્યારે ((t = av_dict_iterate(src, t))) {
        પૂર્ણાંક ret = av_dict_set(dst, t->ચાવી, t->કિંમત, flags);
        જો (ret < 0)
            પાછા ret;
    }

    પાછા 0;
}

પૂર્ણાંક av_dict_get_string(અચલ AVDictionary *m, અક્ષર **buffer,
                       અચલ અક્ષર ચાવી_val_sep, અચલ અક્ષર pairs_sep)
{
    અચલ AVDictionaryEntry *t = ખાલી;
    AVBPrint bprint;
    પૂર્ણાંક cnt = 0;
    અક્ષર special_chars[] = {pairs_sep, ચાવી_val_sep, '\0'};

    જો (!buffer || pairs_sep == '\0' || ચાવી_val_sep == '\0' || pairs_sep == ચાવી_val_sep ||
        pairs_sep == '\\' || ચાવી_val_sep == '\\')
        પાછા AVERROR(EINVAL);

    જો (!av_dict_ગણતરી(m)) {
        *buffer = av_strdup("");
        પાછા *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    જ્યારે ((t = av_dict_iterate(m, t))) {
        જો (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->ચાવી, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &ચાવી_val_sep, 1);
        av_bprint_escape(&bprint, t->કિંમત, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    પાછા av_bprint_finalize(&bprint, buffer);
}
