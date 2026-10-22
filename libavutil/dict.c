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

struct AVDictionary {
    số_nguyên count;
    AVDictionaryEntry *elems;
    số_nguyên duplicate_keys;
};

số_nguyên av_dict_count(const AVDictionary *m)
{
    trả_về m ? m->count : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    số_nguyên i = 0;

    nếu (!m)
        trả_về NULL;

    nếu (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    nếu (i >= m->count)
        trả_về NULL;

    trả_về &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const char *key,
                               const AVDictionaryEntry *prev, số_nguyên flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned số_nguyên j;

    nếu (!key)
        trả_về NULL;

    trong_khi ((entry = av_dict_iterate(m, entry))) {
        const char *s = entry->key;
        nếu (flags & AV_DICT_MATCH_CASE)
            cho (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        không_thì
            cho (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        nếu (key[j])
            continue;
        nếu (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        trả_về (AVDictionaryEntry *)entry;
    }
    trả_về NULL;
}

số_nguyên av_dict_set(AVDictionary **pm, const char *key, const char *value,
                số_nguyên flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    char *copy_key = NULL, *copy_value = NULL;
    số_nguyên err;

    nếu (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (void *)value;
    không_thì nếu (value)
        copy_value = av_strdup(value);
    nếu (!key) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    nếu (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (void *)key;
    không_thì
        copy_key = av_strdup(key);
    nếu (!copy_key || (value && !copy_value))
        goto enomem;

    nếu (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, NULL, flags);
    } không_thì nếu (flags & AV_DICT_DEDUP) {
        trong_khi ((tag = av_dict_get(m, key, tag, flags))) {
            nếu ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                trả_về 0;
            }
        }
    }
    nếu (!m)
        m = *pm = av_mallocz(sizeof(*m));
    nếu (!m)
        goto enomem;

    nếu (tag) {
        nếu (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            trả_về 0;
        }
        nếu (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            char *newval = av_realloc(tag->value, len);
            nếu (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } không_thì
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } không_thì nếu (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, sizeof(*m->elems));
        nếu (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    nếu (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        nếu (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } không_thì {
        err = 0;
        goto end;
    }

    trả_về 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    nếu (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    trả_về err;
}

số_nguyên av_dict_set_int(AVDictionary **pm, const char *key, int64_t value,
                số_nguyên flags)
{
    char valuestr[22];
    snprintf(valuestr, sizeof(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    trả_về av_dict_set(pm, key, valuestr, flags);
}

static số_nguyên parse_key_value_pair(AVDictionary **pm, const char **buf,
                                const char *key_val_sep, const char *pairs_sep,
                                số_nguyên flags)
{
    char *key = av_get_token(buf, key_val_sep);
    char *val = NULL;
    số_nguyên ret;

    nếu (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    nếu (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    không_thì
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    trả_về ret;
}

số_nguyên av_dict_parse_string(AVDictionary **pm, const char *str,
                         const char *key_val_sep, const char *pairs_sep,
                         số_nguyên flags)
{
    số_nguyên ret;

    nếu (!str)
        trả_về 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    trong_khi (*str) {
        nếu ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            trả_về ret;

        nếu (*str)
            str++;
    }

    trả_về 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    nếu (m) {
        trong_khi (m->count--) {
            av_freep(&m->elems[m->count].key);
            av_freep(&m->elems[m->count].value);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

số_nguyên av_dict_copy(AVDictionary **dst, const AVDictionary *src, số_nguyên flags)
{
    const AVDictionaryEntry *t = NULL;

    nếu (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(sizeof(*m));
        nếu (!m)
            trả_về AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, sizeof(*m->elems));
        nếu (!m->elems) {
            av_free(m);
            trả_về AVERROR(ENOMEM);
        }
        *dst = m;
        cho (số_nguyên i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            nếu (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                trả_về AVERROR(ENOMEM);
            }
        }
        trả_về 0;
    }

    trong_khi ((t = av_dict_iterate(src, t))) {
        số_nguyên ret = av_dict_set(dst, t->key, t->value, flags);
        nếu (ret < 0)
            trả_về ret;
    }

    trả_về 0;
}

số_nguyên av_dict_get_string(const AVDictionary *m, char **buffer,
                       const char key_val_sep, const char pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    số_nguyên cnt = 0;
    char special_chars[] = {pairs_sep, key_val_sep, '\0'};

    nếu (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        trả_về AVERROR(EINVAL);

    nếu (!av_dict_count(m)) {
        *buffer = av_strdup("");
        trả_về *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    trong_khi ((t = av_dict_iterate(m, t))) {
        nếu (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    trả_về av_bprint_finalize(&bprint, buffer);
}
