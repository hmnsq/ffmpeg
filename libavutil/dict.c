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
    ཧྲིལ count;
    AVDictionaryEntry *elems;
    ཧྲིལ duplicate_keys;
};

ཧྲིལ av_dict_count(const AVDictionary *m)
{
    ཕྱིར m ? m->count : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    ཧྲིལ i = 0;

    གལ་ཏེ (!m)
        ཕྱིར NULL;

    གལ་ཏེ (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    གལ་ཏེ (i >= m->count)
        ཕྱིར NULL;

    ཕྱིར &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const var_na *key,
                               const AVDictionaryEntry *prev, ཧྲིལ flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned ཧྲིལ j;

    གལ་ཏེ (!key)
        ཕྱིར NULL;

    སྐབས ((entry = av_dict_iterate(m, entry))) {
        const var_na *s = entry->key;
        གལ་ཏེ (flags & AV_DICT_MATCH_CASE)
            ཆེད་དུ (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        དེ་མིན
            ཆེད་དུ (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        གལ་ཏེ (key[j])
            continue;
        གལ་ཏེ (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        ཕྱིར (AVDictionaryEntry *)entry;
    }
    ཕྱིར NULL;
}

ཧྲིལ av_dict_set(AVDictionary **pm, const var_na *key, const var_na *value,
                ཧྲིལ flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    var_na *copy_key = NULL, *copy_value = NULL;
    ཧྲིལ err;

    གལ་ཏེ (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (void *)value;
    དེ་མིན གལ་ཏེ (value)
        copy_value = av_strdup(value);
    གལ་ཏེ (!key) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    གལ་ཏེ (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (void *)key;
    དེ་མིན
        copy_key = av_strdup(key);
    གལ་ཏེ (!copy_key || (value && !copy_value))
        goto enomem;

    གལ་ཏེ (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, NULL, flags);
    } དེ་མིན གལ་ཏེ (flags & AV_DICT_DEDUP) {
        སྐབས ((tag = av_dict_get(m, key, tag, flags))) {
            གལ་ཏེ ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                ཕྱིར 0;
            }
        }
    }
    གལ་ཏེ (!m)
        m = *pm = av_mallocz(parimaa_na(*m));
    གལ་ཏེ (!m)
        goto enomem;

    གལ་ཏེ (tag) {
        གལ་ཏེ (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            ཕྱིར 0;
        }
        གལ་ཏེ (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            var_na *newval = av_realloc(tag->value, len);
            གལ་ཏེ (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } དེ་མིན
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } དེ་མིན གལ་ཏེ (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, parimaa_na(*m->elems));
        གལ་ཏེ (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    གལ་ཏེ (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        གལ་ཏེ (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } དེ་མིན {
        err = 0;
        goto end;
    }

    ཕྱིར 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    གལ་ཏེ (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    ཕྱིར err;
}

ཧྲིལ av_dict_set_int(AVDictionary **pm, const var_na *key, int64_t value,
                ཧྲིལ flags)
{
    var_na valuestr[22];
    snprintf(valuestr, parimaa_na(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    ཕྱིར av_dict_set(pm, key, valuestr, flags);
}

static ཧྲིལ parse_key_value_pair(AVDictionary **pm, const var_na **buf,
                                const var_na *key_val_sep, const var_na *pairs_sep,
                                ཧྲིལ flags)
{
    var_na *key = av_get_token(buf, key_val_sep);
    var_na *val = NULL;
    ཧྲིལ ret;

    གལ་ཏེ (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    གལ་ཏེ (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    དེ་མིན
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    ཕྱིར ret;
}

ཧྲིལ av_dict_parse_string(AVDictionary **pm, const var_na *str,
                         const var_na *key_val_sep, const var_na *pairs_sep,
                         ཧྲིལ flags)
{
    ཧྲིལ ret;

    གལ་ཏེ (!str)
        ཕྱིར 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    སྐབས (*str) {
        གལ་ཏེ ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            ཕྱིར ret;

        གལ་ཏེ (*str)
            str++;
    }

    ཕྱིར 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    གལ་ཏེ (m) {
        སྐབས (m->count--) {
            av_freep(&m->elems[m->count].key);
            av_freep(&m->elems[m->count].value);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

ཧྲིལ av_dict_copy(AVDictionary **dst, const AVDictionary *src, ཧྲིལ flags)
{
    const AVDictionaryEntry *t = NULL;

    གལ་ཏེ (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(parimaa_na(*m));
        གལ་ཏེ (!m)
            ཕྱིར AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, parimaa_na(*m->elems));
        གལ་ཏེ (!m->elems) {
            av_free(m);
            ཕྱིར AVERROR(ENOMEM);
        }
        *dst = m;
        ཆེད་དུ (ཧྲིལ i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            གལ་ཏེ (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                ཕྱིར AVERROR(ENOMEM);
            }
        }
        ཕྱིར 0;
    }

    སྐབས ((t = av_dict_iterate(src, t))) {
        ཧྲིལ ret = av_dict_set(dst, t->key, t->value, flags);
        གལ་ཏེ (ret < 0)
            ཕྱིར ret;
    }

    ཕྱིར 0;
}

ཧྲིལ av_dict_get_string(const AVDictionary *m, var_na **buffer,
                       const var_na key_val_sep, const var_na pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    ཧྲིལ cnt = 0;
    var_na special_chars[] = {pairs_sep, key_val_sep, '\0'};

    གལ་ཏེ (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        ཕྱིར AVERROR(EINVAL);

    གལ་ཏེ (!av_dict_count(m)) {
        *buffer = av_strdup("");
        ཕྱིར *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    སྐབས ((t = av_dict_iterate(m, t))) {
        གལ་ཏེ (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    ཕྱིར av_bprint_finalize(&bprint, buffer);
}
