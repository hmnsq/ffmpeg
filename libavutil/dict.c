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
    ကိန်းပြည့် count;
    AVDictionaryEntry *elems;
    ကိန်းပြည့် duplicate_keys;
};

ကိန်းပြည့် av_dict_count(const AVDictionary *m)
{
    ပြန်ပေး m ? m->count : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    ကိန်းပြည့် i = 0;

    အကယ်၍ (!m)
        ပြန်ပေး NULL;

    အကယ်၍ (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    အကယ်၍ (i >= m->count)
        ပြန်ပေး NULL;

    ပြန်ပေး &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const var_na *key,
                               const AVDictionaryEntry *prev, ကိန်းပြည့် flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned ကိန်းပြည့် j;

    အကယ်၍ (!key)
        ပြန်ပေး NULL;

    နေစဉ် ((entry = av_dict_iterate(m, entry))) {
        const var_na *s = entry->key;
        အကယ်၍ (flags & AV_DICT_MATCH_CASE)
            အတွက် (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        မဟုတ်ပါက
            အတွက် (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        အကယ်၍ (key[j])
            continue;
        အကယ်၍ (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        ပြန်ပေး (AVDictionaryEntry *)entry;
    }
    ပြန်ပေး NULL;
}

ကိန်းပြည့် av_dict_set(AVDictionary **pm, const var_na *key, const var_na *value,
                ကိန်းပြည့် flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    var_na *copy_key = NULL, *copy_value = NULL;
    ကိန်းပြည့် err;

    အကယ်၍ (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (void *)value;
    မဟုတ်ပါက အကယ်၍ (value)
        copy_value = av_strdup(value);
    အကယ်၍ (!key) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    အကယ်၍ (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (void *)key;
    မဟုတ်ပါက
        copy_key = av_strdup(key);
    အကယ်၍ (!copy_key || (value && !copy_value))
        goto enomem;

    အကယ်၍ (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, NULL, flags);
    } မဟုတ်ပါက အကယ်၍ (flags & AV_DICT_DEDUP) {
        နေစဉ် ((tag = av_dict_get(m, key, tag, flags))) {
            အကယ်၍ ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                ပြန်ပေး 0;
            }
        }
    }
    အကယ်၍ (!m)
        m = *pm = av_mallocz(parimaa_na(*m));
    အကယ်၍ (!m)
        goto enomem;

    အကယ်၍ (tag) {
        အကယ်၍ (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            ပြန်ပေး 0;
        }
        အကယ်၍ (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            var_na *newval = av_realloc(tag->value, len);
            အကယ်၍ (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } မဟုတ်ပါက
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } မဟုတ်ပါက အကယ်၍ (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, parimaa_na(*m->elems));
        အကယ်၍ (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    အကယ်၍ (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        အကယ်၍ (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } မဟုတ်ပါက {
        err = 0;
        goto end;
    }

    ပြန်ပေး 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    အကယ်၍ (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    ပြန်ပေး err;
}

ကိန်းပြည့် av_dict_set_int(AVDictionary **pm, const var_na *key, int64_t value,
                ကိန်းပြည့် flags)
{
    var_na valuestr[22];
    snprintf(valuestr, parimaa_na(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    ပြန်ပေး av_dict_set(pm, key, valuestr, flags);
}

static ကိန်းပြည့် parse_key_value_pair(AVDictionary **pm, const var_na **buf,
                                const var_na *key_val_sep, const var_na *pairs_sep,
                                ကိန်းပြည့် flags)
{
    var_na *key = av_get_token(buf, key_val_sep);
    var_na *val = NULL;
    ကိန်းပြည့် ret;

    အကယ်၍ (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    အကယ်၍ (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    မဟုတ်ပါက
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    ပြန်ပေး ret;
}

ကိန်းပြည့် av_dict_parse_string(AVDictionary **pm, const var_na *str,
                         const var_na *key_val_sep, const var_na *pairs_sep,
                         ကိန်းပြည့် flags)
{
    ကိန်းပြည့် ret;

    အကယ်၍ (!str)
        ပြန်ပေး 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    နေစဉ် (*str) {
        အကယ်၍ ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            ပြန်ပေး ret;

        အကယ်၍ (*str)
            str++;
    }

    ပြန်ပေး 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    အကယ်၍ (m) {
        နေစဉ် (m->count--) {
            av_freep(&m->elems[m->count].key);
            av_freep(&m->elems[m->count].value);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

ကိန်းပြည့် av_dict_copy(AVDictionary **dst, const AVDictionary *src, ကိန်းပြည့် flags)
{
    const AVDictionaryEntry *t = NULL;

    အကယ်၍ (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(parimaa_na(*m));
        အကယ်၍ (!m)
            ပြန်ပေး AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, parimaa_na(*m->elems));
        အကယ်၍ (!m->elems) {
            av_free(m);
            ပြန်ပေး AVERROR(ENOMEM);
        }
        *dst = m;
        အတွက် (ကိန်းပြည့် i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            အကယ်၍ (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                ပြန်ပေး AVERROR(ENOMEM);
            }
        }
        ပြန်ပေး 0;
    }

    နေစဉ် ((t = av_dict_iterate(src, t))) {
        ကိန်းပြည့် ret = av_dict_set(dst, t->key, t->value, flags);
        အကယ်၍ (ret < 0)
            ပြန်ပေး ret;
    }

    ပြန်ပေး 0;
}

ကိန်းပြည့် av_dict_get_string(const AVDictionary *m, var_na **buffer,
                       const var_na key_val_sep, const var_na pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    ကိန်းပြည့် cnt = 0;
    var_na special_chars[] = {pairs_sep, key_val_sep, '\0'};

    အကယ်၍ (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        ပြန်ပေး AVERROR(EINVAL);

    အကယ်၍ (!av_dict_count(m)) {
        *buffer = av_strdup("");
        ပြန်ပေး *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    နေစဉ် ((t = av_dict_iterate(m, t))) {
        အကယ်၍ (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    ပြန်ပေး av_bprint_finalize(&bprint, buffer);
}
