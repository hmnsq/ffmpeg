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

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "avassert.h"
#include "avstring.h"
#include "dict.h"
#include "error.h"
#include "mem.h"
#include "bprint.h"

sa_nracanaa AVDictionary {
    puur_naa_nka count;
    AVDictionaryEntry *elems;
    puur_naa_nka duplicate_keys;
};

puur_naa_nka av_dict_count(const AVDictionary *m)
{
    ᨀᨘᨒ m ? m->count : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    puur_naa_nka i = 0;

    ᨀᨘ (!m)
        ᨀᨘᨒ NULL;

    ᨀᨘ (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    ᨀᨘ (i >= m->count)
        ᨀᨘᨒ NULL;

    ᨀᨘᨒ &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const var_na *key,
                               const AVDictionaryEntry *prev, puur_naa_nka flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned puur_naa_nka j;

    ᨀᨘ (!key)
        ᨀᨘᨒ NULL;

    ᨀᨛ ((entry = av_dict_iterate(m, entry))) {
        const var_na *s = entry->key;
        ᨀᨘ (flags & AV_DICT_MATCH_CASE)
            for (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        ᨀᨘᨁ
            for (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        ᨀᨘ (key[j])
            continue;
        ᨀᨘ (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        ᨀᨘᨒ (AVDictionaryEntry *)entry;
    }
    ᨀᨘᨒ NULL;
}

puur_naa_nka av_dict_set(AVDictionary **pm, const var_na *key, const var_na *value,
                puur_naa_nka flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    var_na *copy_key = NULL, *copy_value = NULL;
    puur_naa_nka err;

    ᨀᨘ (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (void *)value;
    ᨀᨘᨁ ᨀᨘ (value)
        copy_value = av_strdup(value);
    ᨀᨘ (!key) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    ᨀᨘ (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (void *)key;
    ᨀᨘᨁ
        copy_key = av_strdup(key);
    ᨀᨘ (!copy_key || (value && !copy_value))
        goto enomem;

    ᨀᨘ (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, NULL, flags);
    } ᨀᨘᨁ ᨀᨘ (flags & AV_DICT_DEDUP) {
        ᨀᨛ ((tag = av_dict_get(m, key, tag, flags))) {
            ᨀᨘ ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                ᨀᨘᨒ 0;
            }
        }
    }
    ᨀᨘ (!m)
        m = *pm = av_mallocz(parimaa_na(*m));
    ᨀᨘ (!m)
        goto enomem;

    ᨀᨘ (tag) {
        ᨀᨘ (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            ᨀᨘᨒ 0;
        }
        ᨀᨘ (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            var_na *newval = av_realloc(tag->value, len);
            ᨀᨘ (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } ᨀᨘᨁ
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } ᨀᨘᨁ ᨀᨘ (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, parimaa_na(*m->elems));
        ᨀᨘ (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    ᨀᨘ (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        ᨀᨘ (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } ᨀᨘᨁ {
        err = 0;
        goto end;
    }

    ᨀᨘᨒ 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    ᨀᨘ (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    ᨀᨘᨒ err;
}

puur_naa_nka av_dict_set_int(AVDictionary **pm, const var_na *key, int64_t value,
                puur_naa_nka flags)
{
    var_na valuestr[22];
    snprintf(valuestr, parimaa_na(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    ᨀᨘᨒ av_dict_set(pm, key, valuestr, flags);
}

static puur_naa_nka parse_key_value_pair(AVDictionary **pm, const var_na **buf,
                                const var_na *key_val_sep, const var_na *pairs_sep,
                                puur_naa_nka flags)
{
    var_na *key = av_get_token(buf, key_val_sep);
    var_na *val = NULL;
    puur_naa_nka ret;

    ᨀᨘ (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    ᨀᨘ (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    ᨀᨘᨁ
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    ᨀᨘᨒ ret;
}

puur_naa_nka av_dict_parse_string(AVDictionary **pm, const var_na *str,
                         const var_na *key_val_sep, const var_na *pairs_sep,
                         puur_naa_nka flags)
{
    puur_naa_nka ret;

    ᨀᨘ (!str)
        ᨀᨘᨒ 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    ᨀᨛ (*str) {
        ᨀᨘ ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            ᨀᨘᨒ ret;

        ᨀᨘ (*str)
            str++;
    }

    ᨀᨘᨒ 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    ᨀᨘ (m) {
        ᨀᨛ (m->count--) {
            av_freep(&m->elems[m->count].key);
            av_freep(&m->elems[m->count].value);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

puur_naa_nka av_dict_copy(AVDictionary **dst, const AVDictionary *src, puur_naa_nka flags)
{
    const AVDictionaryEntry *t = NULL;

    ᨀᨘ (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(parimaa_na(*m));
        ᨀᨘ (!m)
            ᨀᨘᨒ AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, parimaa_na(*m->elems));
        ᨀᨘ (!m->elems) {
            av_free(m);
            ᨀᨘᨒ AVERROR(ENOMEM);
        }
        *dst = m;
        for (puur_naa_nka i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            ᨀᨘ (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                ᨀᨘᨒ AVERROR(ENOMEM);
            }
        }
        ᨀᨘᨒ 0;
    }

    ᨀᨛ ((t = av_dict_iterate(src, t))) {
        puur_naa_nka ret = av_dict_set(dst, t->key, t->value, flags);
        ᨀᨘ (ret < 0)
            ᨀᨘᨒ ret;
    }

    ᨀᨘᨒ 0;
}

puur_naa_nka av_dict_get_string(const AVDictionary *m, var_na **buffer,
                       const var_na key_val_sep, const var_na pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    puur_naa_nka cnt = 0;
    var_na special_chars[] = {pairs_sep, key_val_sep, '\0'};

    ᨀᨘ (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        ᨀᨘᨒ AVERROR(EINVAL);

    ᨀᨘ (!av_dict_count(m)) {
        *buffer = av_strdup("");
        ᨀᨘᨒ *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    ᨀᨛ ((t = av_dict_iterate(m, t))) {
        ᨀᨘ (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    ᨀᨘᨒ av_bprint_finalize(&bprint, buffer);
}
