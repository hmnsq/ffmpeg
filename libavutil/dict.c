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
    ᬯᬮᬶ m ? m->count : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    puur_naa_nka i = 0;

    ᬬᬾᬦ᭄ (!m)
        ᬯᬮᬶ NULL;

    ᬬᬾᬦ᭄ (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    ᬬᬾᬦ᭄ (i >= m->count)
        ᬯᬮᬶ NULL;

    ᬯᬮᬶ &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const var_na *key,
                               const AVDictionaryEntry *prev, puur_naa_nka flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned puur_naa_nka j;

    ᬬᬾᬦ᭄ (!key)
        ᬯᬮᬶ NULL;

    ᬲᭂᬤᭂᬮ ((entry = av_dict_iterate(m, entry))) {
        const var_na *s = entry->key;
        ᬬᬾᬦ᭄ (flags & AV_DICT_MATCH_CASE)
            for (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        ᬮᬶᬬ
            for (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        ᬬᬾᬦ᭄ (key[j])
            continue;
        ᬬᬾᬦ᭄ (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        ᬯᬮᬶ (AVDictionaryEntry *)entry;
    }
    ᬯᬮᬶ NULL;
}

puur_naa_nka av_dict_set(AVDictionary **pm, const var_na *key, const var_na *value,
                puur_naa_nka flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    var_na *copy_key = NULL, *copy_value = NULL;
    puur_naa_nka err;

    ᬬᬾᬦ᭄ (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (void *)value;
    ᬮᬶᬬ ᬬᬾᬦ᭄ (value)
        copy_value = av_strdup(value);
    ᬬᬾᬦ᭄ (!key) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    ᬬᬾᬦ᭄ (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (void *)key;
    ᬮᬶᬬ
        copy_key = av_strdup(key);
    ᬬᬾᬦ᭄ (!copy_key || (value && !copy_value))
        goto enomem;

    ᬬᬾᬦ᭄ (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, NULL, flags);
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (flags & AV_DICT_DEDUP) {
        ᬲᭂᬤᭂᬮ ((tag = av_dict_get(m, key, tag, flags))) {
            ᬬᬾᬦ᭄ ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                ᬯᬮᬶ 0;
            }
        }
    }
    ᬬᬾᬦ᭄ (!m)
        m = *pm = av_mallocz(parimaa_na(*m));
    ᬬᬾᬦ᭄ (!m)
        goto enomem;

    ᬬᬾᬦ᭄ (tag) {
        ᬬᬾᬦ᭄ (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            ᬯᬮᬶ 0;
        }
        ᬬᬾᬦ᭄ (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            var_na *newval = av_realloc(tag->value, len);
            ᬬᬾᬦ᭄ (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } ᬮᬶᬬ
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, parimaa_na(*m->elems));
        ᬬᬾᬦ᭄ (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    ᬬᬾᬦ᭄ (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        ᬬᬾᬦ᭄ (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } ᬮᬶᬬ {
        err = 0;
        goto end;
    }

    ᬯᬮᬶ 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    ᬬᬾᬦ᭄ (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    ᬯᬮᬶ err;
}

puur_naa_nka av_dict_set_int(AVDictionary **pm, const var_na *key, int64_t value,
                puur_naa_nka flags)
{
    var_na valuestr[22];
    snprintf(valuestr, parimaa_na(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    ᬯᬮᬶ av_dict_set(pm, key, valuestr, flags);
}

static puur_naa_nka parse_key_value_pair(AVDictionary **pm, const var_na **buf,
                                const var_na *key_val_sep, const var_na *pairs_sep,
                                puur_naa_nka flags)
{
    var_na *key = av_get_token(buf, key_val_sep);
    var_na *val = NULL;
    puur_naa_nka ret;

    ᬬᬾᬦ᭄ (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    ᬬᬾᬦ᭄ (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    ᬮᬶᬬ
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    ᬯᬮᬶ ret;
}

puur_naa_nka av_dict_parse_string(AVDictionary **pm, const var_na *str,
                         const var_na *key_val_sep, const var_na *pairs_sep,
                         puur_naa_nka flags)
{
    puur_naa_nka ret;

    ᬬᬾᬦ᭄ (!str)
        ᬯᬮᬶ 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    ᬲᭂᬤᭂᬮ (*str) {
        ᬬᬾᬦ᭄ ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            ᬯᬮᬶ ret;

        ᬬᬾᬦ᭄ (*str)
            str++;
    }

    ᬯᬮᬶ 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    ᬬᬾᬦ᭄ (m) {
        ᬲᭂᬤᭂᬮ (m->count--) {
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

    ᬬᬾᬦ᭄ (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(parimaa_na(*m));
        ᬬᬾᬦ᭄ (!m)
            ᬯᬮᬶ AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, parimaa_na(*m->elems));
        ᬬᬾᬦ᭄ (!m->elems) {
            av_free(m);
            ᬯᬮᬶ AVERROR(ENOMEM);
        }
        *dst = m;
        for (puur_naa_nka i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            ᬬᬾᬦ᭄ (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                ᬯᬮᬶ AVERROR(ENOMEM);
            }
        }
        ᬯᬮᬶ 0;
    }

    ᬲᭂᬤᭂᬮ ((t = av_dict_iterate(src, t))) {
        puur_naa_nka ret = av_dict_set(dst, t->key, t->value, flags);
        ᬬᬾᬦ᭄ (ret < 0)
            ᬯᬮᬶ ret;
    }

    ᬯᬮᬶ 0;
}

puur_naa_nka av_dict_get_string(const AVDictionary *m, var_na **buffer,
                       const var_na key_val_sep, const var_na pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    puur_naa_nka cnt = 0;
    var_na special_chars[] = {pairs_sep, key_val_sep, '\0'};

    ᬬᬾᬦ᭄ (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        ᬯᬮᬶ AVERROR(EINVAL);

    ᬬᬾᬦ᭄ (!av_dict_count(m)) {
        *buffer = av_strdup("");
        ᬯᬮᬶ *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    ᬲᭂᬤᭂᬮ ((t = av_dict_iterate(m, t))) {
        ᬬᬾᬦ᭄ (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    ᬯᬮᬶ av_bprint_finalize(&bprint, buffer);
}
