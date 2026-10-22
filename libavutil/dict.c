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
    整数 count;
    AVDictionaryEntry *elems;
    整数 duplicate_keys;
};

整数 av_dict_count(const AVDictionary *m)
{
    返回 m ? m->count : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    整数 i = 0;

    如果 (!m)
        返回 NULL;

    如果 (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    如果 (i >= m->count)
        返回 NULL;

    返回 &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const char *key,
                               const AVDictionaryEntry *prev, 整数 flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned 整数 j;

    如果 (!key)
        返回 NULL;

    当 ((entry = av_dict_iterate(m, entry))) {
        const char *s = entry->key;
        如果 (flags & AV_DICT_MATCH_CASE)
            为 (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        否则
            为 (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        如果 (key[j])
            continue;
        如果 (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        返回 (AVDictionaryEntry *)entry;
    }
    返回 NULL;
}

整数 av_dict_set(AVDictionary **pm, const char *key, const char *value,
                整数 flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    char *copy_key = NULL, *copy_value = NULL;
    整数 err;

    如果 (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (void *)value;
    否则 如果 (value)
        copy_value = av_strdup(value);
    如果 (!key) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    如果 (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (void *)key;
    否则
        copy_key = av_strdup(key);
    如果 (!copy_key || (value && !copy_value))
        goto enomem;

    如果 (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, NULL, flags);
    } 否则 如果 (flags & AV_DICT_DEDUP) {
        当 ((tag = av_dict_get(m, key, tag, flags))) {
            如果 ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                返回 0;
            }
        }
    }
    如果 (!m)
        m = *pm = av_mallocz(sizeof(*m));
    如果 (!m)
        goto enomem;

    如果 (tag) {
        如果 (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            返回 0;
        }
        如果 (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            char *newval = av_realloc(tag->value, len);
            如果 (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } 否则
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } 否则 如果 (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, sizeof(*m->elems));
        如果 (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    如果 (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        如果 (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } 否则 {
        err = 0;
        goto end;
    }

    返回 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    如果 (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    返回 err;
}

整数 av_dict_set_int(AVDictionary **pm, const char *key, int64_t value,
                整数 flags)
{
    char valuestr[22];
    snprintf(valuestr, sizeof(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    返回 av_dict_set(pm, key, valuestr, flags);
}

static 整数 parse_key_value_pair(AVDictionary **pm, const char **buf,
                                const char *key_val_sep, const char *pairs_sep,
                                整数 flags)
{
    char *key = av_get_token(buf, key_val_sep);
    char *val = NULL;
    整数 ret;

    如果 (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    如果 (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    否则
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    返回 ret;
}

整数 av_dict_parse_string(AVDictionary **pm, const char *str,
                         const char *key_val_sep, const char *pairs_sep,
                         整数 flags)
{
    整数 ret;

    如果 (!str)
        返回 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    当 (*str) {
        如果 ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            返回 ret;

        如果 (*str)
            str++;
    }

    返回 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    如果 (m) {
        当 (m->count--) {
            av_freep(&m->elems[m->count].key);
            av_freep(&m->elems[m->count].value);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

整数 av_dict_copy(AVDictionary **dst, const AVDictionary *src, 整数 flags)
{
    const AVDictionaryEntry *t = NULL;

    如果 (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(sizeof(*m));
        如果 (!m)
            返回 AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, sizeof(*m->elems));
        如果 (!m->elems) {
            av_free(m);
            返回 AVERROR(ENOMEM);
        }
        *dst = m;
        为 (整数 i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            如果 (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                返回 AVERROR(ENOMEM);
            }
        }
        返回 0;
    }

    当 ((t = av_dict_iterate(src, t))) {
        整数 ret = av_dict_set(dst, t->key, t->value, flags);
        如果 (ret < 0)
            返回 ret;
    }

    返回 0;
}

整数 av_dict_get_string(const AVDictionary *m, char **buffer,
                       const char key_val_sep, const char pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    整数 cnt = 0;
    char special_chars[] = {pairs_sep, key_val_sep, '\0'};

    如果 (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        返回 AVERROR(EINVAL);

    如果 (!av_dict_count(m)) {
        *buffer = av_strdup("");
        返回 *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    当 ((t = av_dict_iterate(m, t))) {
        如果 (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    返回 av_bprint_finalize(&bprint, buffer);
}
