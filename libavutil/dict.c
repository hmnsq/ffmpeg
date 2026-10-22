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
    цяло count;
    AVDictionaryEntry *elems;
    цяло duplicate_keys;
};

цяло av_dict_count(const AVDictionary *m)
{
    върни m ? m->count : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    цяло i = 0;

    ако (!m)
        върни NULL;

    ако (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    ако (i >= m->count)
        върни NULL;

    върни &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const char *key,
                               const AVDictionaryEntry *prev, цяло flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned цяло j;

    ако (!key)
        върни NULL;

    докато ((entry = av_dict_iterate(m, entry))) {
        const char *s = entry->key;
        ако (flags & AV_DICT_MATCH_CASE)
            за (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        иначе
            за (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        ако (key[j])
            continue;
        ако (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        върни (AVDictionaryEntry *)entry;
    }
    върни NULL;
}

цяло av_dict_set(AVDictionary **pm, const char *key, const char *value,
                цяло flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    char *copy_key = NULL, *copy_value = NULL;
    цяло err;

    ако (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (void *)value;
    иначе ако (value)
        copy_value = av_strdup(value);
    ако (!key) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    ако (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (void *)key;
    иначе
        copy_key = av_strdup(key);
    ако (!copy_key || (value && !copy_value))
        goto enomem;

    ако (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, NULL, flags);
    } иначе ако (flags & AV_DICT_DEDUP) {
        докато ((tag = av_dict_get(m, key, tag, flags))) {
            ако ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                върни 0;
            }
        }
    }
    ако (!m)
        m = *pm = av_mallocz(sizeof(*m));
    ако (!m)
        goto enomem;

    ако (tag) {
        ако (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            върни 0;
        }
        ако (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            char *newval = av_realloc(tag->value, len);
            ако (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } иначе
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } иначе ако (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, sizeof(*m->elems));
        ако (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    ако (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        ако (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } иначе {
        err = 0;
        goto end;
    }

    върни 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    ако (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    върни err;
}

цяло av_dict_set_int(AVDictionary **pm, const char *key, int64_t value,
                цяло flags)
{
    char valuestr[22];
    snprintf(valuestr, sizeof(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    върни av_dict_set(pm, key, valuestr, flags);
}

static цяло parse_key_value_pair(AVDictionary **pm, const char **buf,
                                const char *key_val_sep, const char *pairs_sep,
                                цяло flags)
{
    char *key = av_get_token(buf, key_val_sep);
    char *val = NULL;
    цяло ret;

    ако (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    ако (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    иначе
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    върни ret;
}

цяло av_dict_parse_string(AVDictionary **pm, const char *str,
                         const char *key_val_sep, const char *pairs_sep,
                         цяло flags)
{
    цяло ret;

    ако (!str)
        върни 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    докато (*str) {
        ако ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            върни ret;

        ако (*str)
            str++;
    }

    върни 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    ако (m) {
        докато (m->count--) {
            av_freep(&m->elems[m->count].key);
            av_freep(&m->elems[m->count].value);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

цяло av_dict_copy(AVDictionary **dst, const AVDictionary *src, цяло flags)
{
    const AVDictionaryEntry *t = NULL;

    ако (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(sizeof(*m));
        ако (!m)
            върни AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, sizeof(*m->elems));
        ако (!m->elems) {
            av_free(m);
            върни AVERROR(ENOMEM);
        }
        *dst = m;
        за (цяло i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            ако (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                върни AVERROR(ENOMEM);
            }
        }
        върни 0;
    }

    докато ((t = av_dict_iterate(src, t))) {
        цяло ret = av_dict_set(dst, t->key, t->value, flags);
        ако (ret < 0)
            върни ret;
    }

    върни 0;
}

цяло av_dict_get_string(const AVDictionary *m, char **buffer,
                       const char key_val_sep, const char pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    цяло cnt = 0;
    char special_chars[] = {pairs_sep, key_val_sep, '\0'};

    ако (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        върни AVERROR(EINVAL);

    ако (!av_dict_count(m)) {
        *buffer = av_strdup("");
        върни *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    докато ((t = av_dict_iterate(m, t))) {
        ако (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    върни av_bprint_finalize(&bprint, buffer);
}
