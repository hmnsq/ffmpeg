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
    පූර්ණ_සංඛ්‍යා count;
    AVDictionaryEntry *elems;
    පූර්ණ_සංඛ්‍යා duplicate_keys;
};

පූර්ණ_සංඛ්‍යා av_dict_count(const AVDictionary *m)
{
    ආපසු m ? m->count : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    පූර්ණ_සංඛ්‍යා i = 0;

    නම් (!m)
        ආපසු NULL;

    නම් (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    නම් (i >= m->count)
        ආපසු NULL;

    ආපසු &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const var_na *key,
                               const AVDictionaryEntry *prev, පූර්ණ_සංඛ්‍යා flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned පූර්ණ_සංඛ්‍යා j;

    නම් (!key)
        ආපසු NULL;

    අතරතුර ((entry = av_dict_iterate(m, entry))) {
        const var_na *s = entry->key;
        නම් (flags & AV_DICT_MATCH_CASE)
            සඳහා (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        නැතහොත්
            සඳහා (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        නම් (key[j])
            continue;
        නම් (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        ආපසු (AVDictionaryEntry *)entry;
    }
    ආපසු NULL;
}

පූර්ණ_සංඛ්‍යා av_dict_set(AVDictionary **pm, const var_na *key, const var_na *value,
                පූර්ණ_සංඛ්‍යා flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    var_na *copy_key = NULL, *copy_value = NULL;
    පූර්ණ_සංඛ්‍යා err;

    නම් (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (void *)value;
    නැතහොත් නම් (value)
        copy_value = av_strdup(value);
    නම් (!key) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    නම් (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (void *)key;
    නැතහොත්
        copy_key = av_strdup(key);
    නම් (!copy_key || (value && !copy_value))
        goto enomem;

    නම් (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, NULL, flags);
    } නැතහොත් නම් (flags & AV_DICT_DEDUP) {
        අතරතුර ((tag = av_dict_get(m, key, tag, flags))) {
            නම් ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                ආපසු 0;
            }
        }
    }
    නම් (!m)
        m = *pm = av_mallocz(parimaa_na(*m));
    නම් (!m)
        goto enomem;

    නම් (tag) {
        නම් (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            ආපසු 0;
        }
        නම් (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            var_na *newval = av_realloc(tag->value, len);
            නම් (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } නැතහොත්
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } නැතහොත් නම් (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, parimaa_na(*m->elems));
        නම් (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    නම් (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        නම් (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } නැතහොත් {
        err = 0;
        goto end;
    }

    ආපසු 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    නම් (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    ආපසු err;
}

පූර්ණ_සංඛ්‍යා av_dict_set_int(AVDictionary **pm, const var_na *key, int64_t value,
                පූර්ණ_සංඛ්‍යා flags)
{
    var_na valuestr[22];
    snprintf(valuestr, parimaa_na(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    ආපසු av_dict_set(pm, key, valuestr, flags);
}

static පූර්ණ_සංඛ්‍යා parse_key_value_pair(AVDictionary **pm, const var_na **buf,
                                const var_na *key_val_sep, const var_na *pairs_sep,
                                පූර්ණ_සංඛ්‍යා flags)
{
    var_na *key = av_get_token(buf, key_val_sep);
    var_na *val = NULL;
    පූර්ණ_සංඛ්‍යා ret;

    නම් (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    නම් (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    නැතහොත්
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    ආපසු ret;
}

පූර්ණ_සංඛ්‍යා av_dict_parse_string(AVDictionary **pm, const var_na *str,
                         const var_na *key_val_sep, const var_na *pairs_sep,
                         පූර්ණ_සංඛ්‍යා flags)
{
    පූර්ණ_සංඛ්‍යා ret;

    නම් (!str)
        ආපසු 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    අතරතුර (*str) {
        නම් ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            ආපසු ret;

        නම් (*str)
            str++;
    }

    ආපසු 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    නම් (m) {
        අතරතුර (m->count--) {
            av_freep(&m->elems[m->count].key);
            av_freep(&m->elems[m->count].value);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

පූර්ණ_සංඛ්‍යා av_dict_copy(AVDictionary **dst, const AVDictionary *src, පූර්ණ_සංඛ්‍යා flags)
{
    const AVDictionaryEntry *t = NULL;

    නම් (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(parimaa_na(*m));
        නම් (!m)
            ආපසු AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, parimaa_na(*m->elems));
        නම් (!m->elems) {
            av_free(m);
            ආපසු AVERROR(ENOMEM);
        }
        *dst = m;
        සඳහා (පූර්ණ_සංඛ්‍යා i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            නම් (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                ආපසු AVERROR(ENOMEM);
            }
        }
        ආපසු 0;
    }

    අතරතුර ((t = av_dict_iterate(src, t))) {
        පූර්ණ_සංඛ්‍යා ret = av_dict_set(dst, t->key, t->value, flags);
        නම් (ret < 0)
            ආපසු ret;
    }

    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_dict_get_string(const AVDictionary *m, var_na **buffer,
                       const var_na key_val_sep, const var_na pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    පූර්ණ_සංඛ්‍යා cnt = 0;
    var_na special_chars[] = {pairs_sep, key_val_sep, '\0'};

    නම් (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        ආපසු AVERROR(EINVAL);

    නම් (!av_dict_count(m)) {
        *buffer = av_strdup("");
        ආපසු *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    අතරතුර ((t = av_dict_iterate(m, t))) {
        නම් (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    ආපසු av_bprint_finalize(&bprint, buffer);
}
