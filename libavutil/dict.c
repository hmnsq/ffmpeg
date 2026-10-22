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
    จำนวนเต็ม count;
    AVDictionaryEntry *elems;
    จำนวนเต็ม duplicate_keys;
};

จำนวนเต็ม av_dict_count(const AVDictionary *m)
{
    คืน m ? m->count : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    จำนวนเต็ม i = 0;

    ถ้า (!m)
        คืน NULL;

    ถ้า (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    ถ้า (i >= m->count)
        คืน NULL;

    คืน &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const var_na *key,
                               const AVDictionaryEntry *prev, จำนวนเต็ม flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned จำนวนเต็ม j;

    ถ้า (!key)
        คืน NULL;

    ขณะ ((entry = av_dict_iterate(m, entry))) {
        const var_na *s = entry->key;
        ถ้า (flags & AV_DICT_MATCH_CASE)
            สำหรับ (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        มิฉะนั้น
            สำหรับ (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        ถ้า (key[j])
            continue;
        ถ้า (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        คืน (AVDictionaryEntry *)entry;
    }
    คืน NULL;
}

จำนวนเต็ม av_dict_set(AVDictionary **pm, const var_na *key, const var_na *value,
                จำนวนเต็ม flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    var_na *copy_key = NULL, *copy_value = NULL;
    จำนวนเต็ม err;

    ถ้า (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (void *)value;
    มิฉะนั้น ถ้า (value)
        copy_value = av_strdup(value);
    ถ้า (!key) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    ถ้า (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (void *)key;
    มิฉะนั้น
        copy_key = av_strdup(key);
    ถ้า (!copy_key || (value && !copy_value))
        goto enomem;

    ถ้า (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, NULL, flags);
    } มิฉะนั้น ถ้า (flags & AV_DICT_DEDUP) {
        ขณะ ((tag = av_dict_get(m, key, tag, flags))) {
            ถ้า ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                คืน 0;
            }
        }
    }
    ถ้า (!m)
        m = *pm = av_mallocz(parimaa_na(*m));
    ถ้า (!m)
        goto enomem;

    ถ้า (tag) {
        ถ้า (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            คืน 0;
        }
        ถ้า (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            var_na *newval = av_realloc(tag->value, len);
            ถ้า (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } มิฉะนั้น
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } มิฉะนั้น ถ้า (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, parimaa_na(*m->elems));
        ถ้า (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    ถ้า (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        ถ้า (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } มิฉะนั้น {
        err = 0;
        goto end;
    }

    คืน 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    ถ้า (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    คืน err;
}

จำนวนเต็ม av_dict_set_int(AVDictionary **pm, const var_na *key, int64_t value,
                จำนวนเต็ม flags)
{
    var_na valuestr[22];
    snprintf(valuestr, parimaa_na(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    คืน av_dict_set(pm, key, valuestr, flags);
}

static จำนวนเต็ม parse_key_value_pair(AVDictionary **pm, const var_na **buf,
                                const var_na *key_val_sep, const var_na *pairs_sep,
                                จำนวนเต็ม flags)
{
    var_na *key = av_get_token(buf, key_val_sep);
    var_na *val = NULL;
    จำนวนเต็ม ret;

    ถ้า (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    ถ้า (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    มิฉะนั้น
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    คืน ret;
}

จำนวนเต็ม av_dict_parse_string(AVDictionary **pm, const var_na *str,
                         const var_na *key_val_sep, const var_na *pairs_sep,
                         จำนวนเต็ม flags)
{
    จำนวนเต็ม ret;

    ถ้า (!str)
        คืน 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    ขณะ (*str) {
        ถ้า ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            คืน ret;

        ถ้า (*str)
            str++;
    }

    คืน 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    ถ้า (m) {
        ขณะ (m->count--) {
            av_freep(&m->elems[m->count].key);
            av_freep(&m->elems[m->count].value);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

จำนวนเต็ม av_dict_copy(AVDictionary **dst, const AVDictionary *src, จำนวนเต็ม flags)
{
    const AVDictionaryEntry *t = NULL;

    ถ้า (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(parimaa_na(*m));
        ถ้า (!m)
            คืน AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, parimaa_na(*m->elems));
        ถ้า (!m->elems) {
            av_free(m);
            คืน AVERROR(ENOMEM);
        }
        *dst = m;
        สำหรับ (จำนวนเต็ม i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            ถ้า (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                คืน AVERROR(ENOMEM);
            }
        }
        คืน 0;
    }

    ขณะ ((t = av_dict_iterate(src, t))) {
        จำนวนเต็ม ret = av_dict_set(dst, t->key, t->value, flags);
        ถ้า (ret < 0)
            คืน ret;
    }

    คืน 0;
}

จำนวนเต็ม av_dict_get_string(const AVDictionary *m, var_na **buffer,
                       const var_na key_val_sep, const var_na pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    จำนวนเต็ม cnt = 0;
    var_na special_chars[] = {pairs_sep, key_val_sep, '\0'};

    ถ้า (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        คืน AVERROR(EINVAL);

    ถ้า (!av_dict_count(m)) {
        *buffer = av_strdup("");
        คืน *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    ขณะ ((t = av_dict_iterate(m, t))) {
        ถ้า (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    คืน av_bprint_finalize(&bprint, buffer);
}
