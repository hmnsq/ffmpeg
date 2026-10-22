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
    ціле count;
    AVDictionaryEntry *elems;
    ціле duplicate_keys;
};

ціле av_dict_count(const AVDictionary *m)
{
    повернути m ? m->count : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    ціле i = 0;

    якщо (!m)
        повернути NULL;

    якщо (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    якщо (i >= m->count)
        повернути NULL;

    повернути &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const char *key,
                               const AVDictionaryEntry *prev, ціле flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned ціле j;

    якщо (!key)
        повернути NULL;

    поки ((entry = av_dict_iterate(m, entry))) {
        const char *s = entry->key;
        якщо (flags & AV_DICT_MATCH_CASE)
            для (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        інакше
            для (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        якщо (key[j])
            continue;
        якщо (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        повернути (AVDictionaryEntry *)entry;
    }
    повернути NULL;
}

ціле av_dict_set(AVDictionary **pm, const char *key, const char *value,
                ціле flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    char *copy_key = NULL, *copy_value = NULL;
    ціле err;

    якщо (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (void *)value;
    інакше якщо (value)
        copy_value = av_strdup(value);
    якщо (!key) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    якщо (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (void *)key;
    інакше
        copy_key = av_strdup(key);
    якщо (!copy_key || (value && !copy_value))
        goto enomem;

    якщо (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, NULL, flags);
    } інакше якщо (flags & AV_DICT_DEDUP) {
        поки ((tag = av_dict_get(m, key, tag, flags))) {
            якщо ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                повернути 0;
            }
        }
    }
    якщо (!m)
        m = *pm = av_mallocz(sizeof(*m));
    якщо (!m)
        goto enomem;

    якщо (tag) {
        якщо (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            повернути 0;
        }
        якщо (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            char *newval = av_realloc(tag->value, len);
            якщо (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } інакше
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } інакше якщо (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, sizeof(*m->elems));
        якщо (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    якщо (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        якщо (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } інакше {
        err = 0;
        goto end;
    }

    повернути 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    якщо (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    повернути err;
}

ціле av_dict_set_int(AVDictionary **pm, const char *key, int64_t value,
                ціле flags)
{
    char valuestr[22];
    snprintf(valuestr, sizeof(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    повернути av_dict_set(pm, key, valuestr, flags);
}

static ціле parse_key_value_pair(AVDictionary **pm, const char **buf,
                                const char *key_val_sep, const char *pairs_sep,
                                ціле flags)
{
    char *key = av_get_token(buf, key_val_sep);
    char *val = NULL;
    ціле ret;

    якщо (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    якщо (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    інакше
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    повернути ret;
}

ціле av_dict_parse_string(AVDictionary **pm, const char *str,
                         const char *key_val_sep, const char *pairs_sep,
                         ціле flags)
{
    ціле ret;

    якщо (!str)
        повернути 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    поки (*str) {
        якщо ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            повернути ret;

        якщо (*str)
            str++;
    }

    повернути 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    якщо (m) {
        поки (m->count--) {
            av_freep(&m->elems[m->count].key);
            av_freep(&m->elems[m->count].value);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

ціле av_dict_copy(AVDictionary **dst, const AVDictionary *src, ціле flags)
{
    const AVDictionaryEntry *t = NULL;

    якщо (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(sizeof(*m));
        якщо (!m)
            повернути AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, sizeof(*m->elems));
        якщо (!m->elems) {
            av_free(m);
            повернути AVERROR(ENOMEM);
        }
        *dst = m;
        для (ціле i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            якщо (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                повернути AVERROR(ENOMEM);
            }
        }
        повернути 0;
    }

    поки ((t = av_dict_iterate(src, t))) {
        ціле ret = av_dict_set(dst, t->key, t->value, flags);
        якщо (ret < 0)
            повернути ret;
    }

    повернути 0;
}

ціле av_dict_get_string(const AVDictionary *m, char **buffer,
                       const char key_val_sep, const char pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    ціле cnt = 0;
    char special_chars[] = {pairs_sep, key_val_sep, '\0'};

    якщо (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        повернути AVERROR(EINVAL);

    якщо (!av_dict_count(m)) {
        *buffer = av_strdup("");
        повернути *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    поки ((t = av_dict_iterate(m, t))) {
        якщо (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    повернути av_bprint_finalize(&bprint, buffer);
}
