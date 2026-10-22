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
    ចំនួនគត់ count;
    AVDictionaryEntry *elems;
    ចំនួនគត់ duplicate_keys;
};

ចំនួនគត់ av_dict_count(const AVDictionary *m)
{
    ត្រឡប់ m ? m->count : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    ចំនួនគត់ i = 0;

    ប្រសិនបើ (!m)
        ត្រឡប់ NULL;

    ប្រសិនបើ (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    ប្រសិនបើ (i >= m->count)
        ត្រឡប់ NULL;

    ត្រឡប់ &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const var_na *key,
                               const AVDictionaryEntry *prev, ចំនួនគត់ flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned ចំនួនគត់ j;

    ប្រសិនបើ (!key)
        ត្រឡប់ NULL;

    ខណៈពេល ((entry = av_dict_iterate(m, entry))) {
        const var_na *s = entry->key;
        ប្រសិនបើ (flags & AV_DICT_MATCH_CASE)
            សម្រាប់ (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        បើមិនដូច្នេះ
            សម្រាប់ (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        ប្រសិនបើ (key[j])
            continue;
        ប្រសិនបើ (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        ត្រឡប់ (AVDictionaryEntry *)entry;
    }
    ត្រឡប់ NULL;
}

ចំនួនគត់ av_dict_set(AVDictionary **pm, const var_na *key, const var_na *value,
                ចំនួនគត់ flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    var_na *copy_key = NULL, *copy_value = NULL;
    ចំនួនគត់ err;

    ប្រសិនបើ (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (void *)value;
    បើមិនដូច្នេះ ប្រសិនបើ (value)
        copy_value = av_strdup(value);
    ប្រសិនបើ (!key) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    ប្រសិនបើ (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (void *)key;
    បើមិនដូច្នេះ
        copy_key = av_strdup(key);
    ប្រសិនបើ (!copy_key || (value && !copy_value))
        goto enomem;

    ប្រសិនបើ (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, NULL, flags);
    } បើមិនដូច្នេះ ប្រសិនបើ (flags & AV_DICT_DEDUP) {
        ខណៈពេល ((tag = av_dict_get(m, key, tag, flags))) {
            ប្រសិនបើ ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                ត្រឡប់ 0;
            }
        }
    }
    ប្រសិនបើ (!m)
        m = *pm = av_mallocz(parimaa_na(*m));
    ប្រសិនបើ (!m)
        goto enomem;

    ប្រសិនបើ (tag) {
        ប្រសិនបើ (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            ត្រឡប់ 0;
        }
        ប្រសិនបើ (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            var_na *newval = av_realloc(tag->value, len);
            ប្រសិនបើ (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } បើមិនដូច្នេះ
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } បើមិនដូច្នេះ ប្រសិនបើ (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, parimaa_na(*m->elems));
        ប្រសិនបើ (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    ប្រសិនបើ (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        ប្រសិនបើ (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } បើមិនដូច្នេះ {
        err = 0;
        goto end;
    }

    ត្រឡប់ 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    ប្រសិនបើ (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    ត្រឡប់ err;
}

ចំនួនគត់ av_dict_set_int(AVDictionary **pm, const var_na *key, int64_t value,
                ចំនួនគត់ flags)
{
    var_na valuestr[22];
    snprintf(valuestr, parimaa_na(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    ត្រឡប់ av_dict_set(pm, key, valuestr, flags);
}

static ចំនួនគត់ parse_key_value_pair(AVDictionary **pm, const var_na **buf,
                                const var_na *key_val_sep, const var_na *pairs_sep,
                                ចំនួនគត់ flags)
{
    var_na *key = av_get_token(buf, key_val_sep);
    var_na *val = NULL;
    ចំនួនគត់ ret;

    ប្រសិនបើ (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    ប្រសិនបើ (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    បើមិនដូច្នេះ
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    ត្រឡប់ ret;
}

ចំនួនគត់ av_dict_parse_string(AVDictionary **pm, const var_na *str,
                         const var_na *key_val_sep, const var_na *pairs_sep,
                         ចំនួនគត់ flags)
{
    ចំនួនគត់ ret;

    ប្រសិនបើ (!str)
        ត្រឡប់ 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    ខណៈពេល (*str) {
        ប្រសិនបើ ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            ត្រឡប់ ret;

        ប្រសិនបើ (*str)
            str++;
    }

    ត្រឡប់ 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    ប្រសិនបើ (m) {
        ខណៈពេល (m->count--) {
            av_freep(&m->elems[m->count].key);
            av_freep(&m->elems[m->count].value);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

ចំនួនគត់ av_dict_copy(AVDictionary **dst, const AVDictionary *src, ចំនួនគត់ flags)
{
    const AVDictionaryEntry *t = NULL;

    ប្រសិនបើ (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(parimaa_na(*m));
        ប្រសិនបើ (!m)
            ត្រឡប់ AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, parimaa_na(*m->elems));
        ប្រសិនបើ (!m->elems) {
            av_free(m);
            ត្រឡប់ AVERROR(ENOMEM);
        }
        *dst = m;
        សម្រាប់ (ចំនួនគត់ i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            ប្រសិនបើ (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                ត្រឡប់ AVERROR(ENOMEM);
            }
        }
        ត្រឡប់ 0;
    }

    ខណៈពេល ((t = av_dict_iterate(src, t))) {
        ចំនួនគត់ ret = av_dict_set(dst, t->key, t->value, flags);
        ប្រសិនបើ (ret < 0)
            ត្រឡប់ ret;
    }

    ត្រឡប់ 0;
}

ចំនួនគត់ av_dict_get_string(const AVDictionary *m, var_na **buffer,
                       const var_na key_val_sep, const var_na pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    ចំនួនគត់ cnt = 0;
    var_na special_chars[] = {pairs_sep, key_val_sep, '\0'};

    ប្រសិនបើ (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        ត្រឡប់ AVERROR(EINVAL);

    ប្រសិនបើ (!av_dict_count(m)) {
        *buffer = av_strdup("");
        ត្រឡប់ *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    ខណៈពេល ((t = av_dict_iterate(m, t))) {
        ប្រសិនបើ (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    ត្រឡប់ av_bprint_finalize(&bprint, buffer);
}
