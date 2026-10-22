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
    ຈຳນວນເຕັມ count;
    AVDictionaryEntry *elems;
    ຈຳນວນເຕັມ duplicate_keys;
};

ຈຳນວນເຕັມ av_dict_count(const AVDictionary *m)
{
    ສົ່ງຄືນ m ? m->count : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    ຈຳນວນເຕັມ i = 0;

    ຖ້າ (!m)
        ສົ່ງຄືນ NULL;

    ຖ້າ (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    ຖ້າ (i >= m->count)
        ສົ່ງຄືນ NULL;

    ສົ່ງຄືນ &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const var_na *key,
                               const AVDictionaryEntry *prev, ຈຳນວນເຕັມ flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned ຈຳນວນເຕັມ j;

    ຖ້າ (!key)
        ສົ່ງຄືນ NULL;

    ໃນຂະນະທີ່ ((entry = av_dict_iterate(m, entry))) {
        const var_na *s = entry->key;
        ຖ້າ (flags & AV_DICT_MATCH_CASE)
            ສຳລັບ (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        ບໍ່ດັ່ງນັ້ນ
            ສຳລັບ (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        ຖ້າ (key[j])
            continue;
        ຖ້າ (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        ສົ່ງຄືນ (AVDictionaryEntry *)entry;
    }
    ສົ່ງຄືນ NULL;
}

ຈຳນວນເຕັມ av_dict_set(AVDictionary **pm, const var_na *key, const var_na *value,
                ຈຳນວນເຕັມ flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    var_na *copy_key = NULL, *copy_value = NULL;
    ຈຳນວນເຕັມ err;

    ຖ້າ (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (void *)value;
    ບໍ່ດັ່ງນັ້ນ ຖ້າ (value)
        copy_value = av_strdup(value);
    ຖ້າ (!key) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    ຖ້າ (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (void *)key;
    ບໍ່ດັ່ງນັ້ນ
        copy_key = av_strdup(key);
    ຖ້າ (!copy_key || (value && !copy_value))
        goto enomem;

    ຖ້າ (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, NULL, flags);
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (flags & AV_DICT_DEDUP) {
        ໃນຂະນະທີ່ ((tag = av_dict_get(m, key, tag, flags))) {
            ຖ້າ ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                ສົ່ງຄືນ 0;
            }
        }
    }
    ຖ້າ (!m)
        m = *pm = av_mallocz(parimaa_na(*m));
    ຖ້າ (!m)
        goto enomem;

    ຖ້າ (tag) {
        ຖ້າ (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            ສົ່ງຄືນ 0;
        }
        ຖ້າ (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            var_na *newval = av_realloc(tag->value, len);
            ຖ້າ (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } ບໍ່ດັ່ງນັ້ນ
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, parimaa_na(*m->elems));
        ຖ້າ (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    ຖ້າ (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        ຖ້າ (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } ບໍ່ດັ່ງນັ້ນ {
        err = 0;
        goto end;
    }

    ສົ່ງຄືນ 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    ຖ້າ (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    ສົ່ງຄືນ err;
}

ຈຳນວນເຕັມ av_dict_set_int(AVDictionary **pm, const var_na *key, int64_t value,
                ຈຳນວນເຕັມ flags)
{
    var_na valuestr[22];
    snprintf(valuestr, parimaa_na(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    ສົ່ງຄືນ av_dict_set(pm, key, valuestr, flags);
}

static ຈຳນວນເຕັມ parse_key_value_pair(AVDictionary **pm, const var_na **buf,
                                const var_na *key_val_sep, const var_na *pairs_sep,
                                ຈຳນວນເຕັມ flags)
{
    var_na *key = av_get_token(buf, key_val_sep);
    var_na *val = NULL;
    ຈຳນວນເຕັມ ret;

    ຖ້າ (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    ຖ້າ (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    ບໍ່ດັ່ງນັ້ນ
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    ສົ່ງຄືນ ret;
}

ຈຳນວນເຕັມ av_dict_parse_string(AVDictionary **pm, const var_na *str,
                         const var_na *key_val_sep, const var_na *pairs_sep,
                         ຈຳນວນເຕັມ flags)
{
    ຈຳນວນເຕັມ ret;

    ຖ້າ (!str)
        ສົ່ງຄືນ 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    ໃນຂະນະທີ່ (*str) {
        ຖ້າ ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            ສົ່ງຄືນ ret;

        ຖ້າ (*str)
            str++;
    }

    ສົ່ງຄືນ 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    ຖ້າ (m) {
        ໃນຂະນະທີ່ (m->count--) {
            av_freep(&m->elems[m->count].key);
            av_freep(&m->elems[m->count].value);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

ຈຳນວນເຕັມ av_dict_copy(AVDictionary **dst, const AVDictionary *src, ຈຳນວນເຕັມ flags)
{
    const AVDictionaryEntry *t = NULL;

    ຖ້າ (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(parimaa_na(*m));
        ຖ້າ (!m)
            ສົ່ງຄືນ AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, parimaa_na(*m->elems));
        ຖ້າ (!m->elems) {
            av_free(m);
            ສົ່ງຄືນ AVERROR(ENOMEM);
        }
        *dst = m;
        ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            ຖ້າ (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                ສົ່ງຄືນ AVERROR(ENOMEM);
            }
        }
        ສົ່ງຄືນ 0;
    }

    ໃນຂະນະທີ່ ((t = av_dict_iterate(src, t))) {
        ຈຳນວນເຕັມ ret = av_dict_set(dst, t->key, t->value, flags);
        ຖ້າ (ret < 0)
            ສົ່ງຄືນ ret;
    }

    ສົ່ງຄືນ 0;
}

ຈຳນວນເຕັມ av_dict_get_string(const AVDictionary *m, var_na **buffer,
                       const var_na key_val_sep, const var_na pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    ຈຳນວນເຕັມ cnt = 0;
    var_na special_chars[] = {pairs_sep, key_val_sep, '\0'};

    ຖ້າ (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        ສົ່ງຄືນ AVERROR(EINVAL);

    ຖ້າ (!av_dict_count(m)) {
        *buffer = av_strdup("");
        ສົ່ງຄືນ *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    ໃນຂະນະທີ່ ((t = av_dict_iterate(m, t))) {
        ຖ້າ (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    ສົ່ງຄືນ av_bprint_finalize(&bprint, buffer);
}
