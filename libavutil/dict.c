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
    정수 count;
    AVDictionaryEntry *elems;
    정수 duplicate_keys;
};

정수 av_dict_count(const AVDictionary *m)
{
    반환 m ? m->count : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    정수 i = 0;

    만약 (!m)
        반환 NULL;

    만약 (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    만약 (i >= m->count)
        반환 NULL;

    반환 &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const char *key,
                               const AVDictionaryEntry *prev, 정수 flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned 정수 j;

    만약 (!key)
        반환 NULL;

    동안 ((entry = av_dict_iterate(m, entry))) {
        const char *s = entry->key;
        만약 (flags & AV_DICT_MATCH_CASE)
            위해 (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        아니면
            위해 (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        만약 (key[j])
            continue;
        만약 (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        반환 (AVDictionaryEntry *)entry;
    }
    반환 NULL;
}

정수 av_dict_set(AVDictionary **pm, const char *key, const char *value,
                정수 flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    char *copy_key = NULL, *copy_value = NULL;
    정수 err;

    만약 (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (void *)value;
    아니면 만약 (value)
        copy_value = av_strdup(value);
    만약 (!key) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    만약 (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (void *)key;
    아니면
        copy_key = av_strdup(key);
    만약 (!copy_key || (value && !copy_value))
        goto enomem;

    만약 (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, NULL, flags);
    } 아니면 만약 (flags & AV_DICT_DEDUP) {
        동안 ((tag = av_dict_get(m, key, tag, flags))) {
            만약 ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                반환 0;
            }
        }
    }
    만약 (!m)
        m = *pm = av_mallocz(sizeof(*m));
    만약 (!m)
        goto enomem;

    만약 (tag) {
        만약 (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            반환 0;
        }
        만약 (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            char *newval = av_realloc(tag->value, len);
            만약 (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } 아니면
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } 아니면 만약 (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, sizeof(*m->elems));
        만약 (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    만약 (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        만약 (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } 아니면 {
        err = 0;
        goto end;
    }

    반환 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    만약 (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    반환 err;
}

정수 av_dict_set_int(AVDictionary **pm, const char *key, int64_t value,
                정수 flags)
{
    char valuestr[22];
    snprintf(valuestr, sizeof(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    반환 av_dict_set(pm, key, valuestr, flags);
}

static 정수 parse_key_value_pair(AVDictionary **pm, const char **buf,
                                const char *key_val_sep, const char *pairs_sep,
                                정수 flags)
{
    char *key = av_get_token(buf, key_val_sep);
    char *val = NULL;
    정수 ret;

    만약 (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    만약 (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    아니면
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    반환 ret;
}

정수 av_dict_parse_string(AVDictionary **pm, const char *str,
                         const char *key_val_sep, const char *pairs_sep,
                         정수 flags)
{
    정수 ret;

    만약 (!str)
        반환 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    동안 (*str) {
        만약 ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            반환 ret;

        만약 (*str)
            str++;
    }

    반환 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    만약 (m) {
        동안 (m->count--) {
            av_freep(&m->elems[m->count].key);
            av_freep(&m->elems[m->count].value);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

정수 av_dict_copy(AVDictionary **dst, const AVDictionary *src, 정수 flags)
{
    const AVDictionaryEntry *t = NULL;

    만약 (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(sizeof(*m));
        만약 (!m)
            반환 AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, sizeof(*m->elems));
        만약 (!m->elems) {
            av_free(m);
            반환 AVERROR(ENOMEM);
        }
        *dst = m;
        위해 (정수 i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            만약 (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                반환 AVERROR(ENOMEM);
            }
        }
        반환 0;
    }

    동안 ((t = av_dict_iterate(src, t))) {
        정수 ret = av_dict_set(dst, t->key, t->value, flags);
        만약 (ret < 0)
            반환 ret;
    }

    반환 0;
}

정수 av_dict_get_string(const AVDictionary *m, char **buffer,
                       const char key_val_sep, const char pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    정수 cnt = 0;
    char special_chars[] = {pairs_sep, key_val_sep, '\0'};

    만약 (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        반환 AVERROR(EINVAL);

    만약 (!av_dict_count(m)) {
        *buffer = av_strdup("");
        반환 *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    동안 ((t = av_dict_iterate(m, t))) {
        만약 (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    반환 av_bprint_finalize(&bprint, buffer);
}
