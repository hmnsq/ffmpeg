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

#ضمن <inttypes.h>
#ضمن <stdio.h>
#ضمن <string.h>

#ضمن "avassert.h"
#ضمن "avstring.h"
#ضمن "dict.h"
#ضمن "error.h"
#ضمن "mem.h"
#ضمن "bprint.h"

بنية AVDictionary {
    صحيح count;
    AVDictionaryEntry *elems;
    صحيح duplicate_keys;
};

صحيح av_dict_count(ثابت AVDictionary *m)
{
    أرجع m ? m->count : 0;
}

ثابت AVDictionaryEntry *av_dict_iterate(ثابت AVDictionary *m,
                                         ثابت AVDictionaryEntry *prev)
{
    صحيح i = 0;

    𐡄𐡍 (!m)
        أرجع عدم;

    𐡄𐡍 (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    𐡄𐡍 (i >= m->count)
        أرجع عدم;

    أرجع &m->elems[i];
}

AVDictionaryEntry *av_dict_get(ثابت AVDictionary *m, ثابت حرف *key,
                               ثابت AVDictionaryEntry *prev, صحيح flags)
{
    ثابت AVDictionaryEntry *entry = prev;
    unsigned صحيح j;

    𐡄𐡍 (!key)
        أرجع عدم;

    طالما ((entry = av_dict_iterate(m, entry))) {
        ثابت حرف *s = entry->key;
        𐡄𐡍 (flags & AV_DICT_MATCH_CASE)
            لكل (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        وإلا
            لكل (j = 0; av_toupper(s[j]) == av_toupper(key[j]) && key[j]; j++)
                ;
        𐡄𐡍 (key[j])
            استمر;
        𐡄𐡍 (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            استمر;
        أرجع (AVDictionaryEntry *)entry;
    }
    أرجع عدم;
}

صحيح av_dict_set(AVDictionary **pm, ثابت حرف *key, ثابت حرف *value,
                صحيح flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = عدم;
    حرف *copy_key = عدم, *copy_value = عدم;
    صحيح err;

    𐡄𐡍 (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_value = (فراغ *)value;
    وإلا 𐡄𐡍 (value)
        copy_value = av_strdup(value);
    𐡄𐡍 (!key) {
        err = AVERROR(EINVAL);
        اذهب err_out;
    }
    𐡄𐡍 (flags & AV_DICT_DONT_STRDUP_KEY)
        copy_key = (فراغ *)key;
    وإلا
        copy_key = av_strdup(key);
    𐡄𐡍 (!copy_key || (value && !copy_value))
        اذهب enomem;

    𐡄𐡍 (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, key, عدم, flags);
    } وإلا 𐡄𐡍 (flags & AV_DICT_DEDUP) {
        طالما ((tag = av_dict_get(m, key, tag, flags))) {
            𐡄𐡍 ((!value && !tag->value) ||
                (value && tag->value && !strcmp(value, tag->value))) {
                av_free(copy_key);
                av_free(copy_value);
                أرجع 0;
            }
        }
    }
    𐡄𐡍 (!m)
        m = *pm = av_mallocz(حجم(*m));
    𐡄𐡍 (!m)
        اذهب enomem;

    𐡄𐡍 (tag) {
        𐡄𐡍 (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_key);
            av_free(copy_value);
            أرجع 0;
        }
        𐡄𐡍 (copy_value && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->value);
            size_t new_part_len = strlen(copy_value);
            size_t len = oldlen + new_part_len + 1;
            حرف *newval = av_realloc(tag->value, len);
            𐡄𐡍 (!newval)
                اذهب enomem;
            memcpy(newval + oldlen, copy_value, new_part_len + 1);
            av_freep(&copy_value);
            copy_value = newval;
        } وإلا
            av_free(tag->value);
        av_free(tag->key);
        *tag = m->elems[--m->count];
    } وإلا 𐡄𐡍 (copy_value) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->count + 1, حجم(*m->elems));
        𐡄𐡍 (!tmp)
            اذهب enomem;
        m->elems = tmp;
    }
    𐡄𐡍 (copy_value) {
        m->elems[m->count].key = copy_key;
        m->elems[m->count].value = copy_value;
        m->count++;
        𐡄𐡍 (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_keys = 1;
    } وإلا {
        err = 0;
        اذهب end;
    }

    أرجع 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_value);
end:
    𐡄𐡍 (m && !m->count) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_key);
    أرجع err;
}

صحيح av_dict_set_int(AVDictionary **pm, ثابت حرف *key, int64_t value,
                صحيح flags)
{
    حرف valuestr[22];
    snprintf(valuestr, حجم(valuestr), "%"PRId64, value);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    أرجع av_dict_set(pm, key, valuestr, flags);
}

ساكن صحيح parse_key_value_pair(AVDictionary **pm, ثابت حرف **buf,
                                ثابت حرف *key_val_sep, ثابت حرف *pairs_sep,
                                صحيح flags)
{
    حرف *key = av_get_token(buf, key_val_sep);
    حرف *val = عدم;
    صحيح ret;

    𐡄𐡍 (key && *key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    𐡄𐡍 (key && *key && val && *val)
        ret = av_dict_set(pm, key, val, flags);
    وإلا
        ret = AVERROR(EINVAL);

    av_freep(&key);
    av_freep(&val);

    أرجع ret;
}

صحيح av_dict_parse_string(AVDictionary **pm, ثابت حرف *str,
                         ثابت حرف *key_val_sep, ثابت حرف *pairs_sep,
                         صحيح flags)
{
    صحيح ret;

    𐡄𐡍 (!str)
        أرجع 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);

    طالما (*str) {
        𐡄𐡍 ((ret = parse_key_value_pair(pm, &str, key_val_sep, pairs_sep, flags)) < 0)
            أرجع ret;

        𐡄𐡍 (*str)
            str++;
    }

    أرجع 0;
}

فراغ av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    𐡄𐡍 (m) {
        طالما (m->count--) {
            av_freep(&m->elems[m->count].key);
            av_freep(&m->elems[m->count].value);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

صحيح av_dict_copy(AVDictionary **dst, ثابت AVDictionary *src, صحيح flags)
{
    ثابت AVDictionaryEntry *t = عدم;

    𐡄𐡍 (!*dst && src && src->count && !src->duplicate_keys &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(حجم(*m));
        𐡄𐡍 (!m)
            أرجع AVERROR(ENOMEM);
        m->elems = av_calloc(src->count, حجم(*m->elems));
        𐡄𐡍 (!m->elems) {
            av_free(m);
            أرجع AVERROR(ENOMEM);
        }
        *dst = m;
        لكل (صحيح i = 0; i < src->count; i++) {
            m->elems[i].key   = av_strdup(src->elems[i].key);
            m->elems[i].value = av_strdup(src->elems[i].value);
            m->count++;
            𐡄𐡍 (!m->elems[i].key || !m->elems[i].value) {
                av_dict_free(dst);
                أرجع AVERROR(ENOMEM);
            }
        }
        أرجع 0;
    }

    طالما ((t = av_dict_iterate(src, t))) {
        صحيح ret = av_dict_set(dst, t->key, t->value, flags);
        𐡄𐡍 (ret < 0)
            أرجع ret;
    }

    أرجع 0;
}

صحيح av_dict_get_string(ثابت AVDictionary *m, حرف **buffer,
                       ثابت حرف key_val_sep, ثابت حرف pairs_sep)
{
    ثابت AVDictionaryEntry *t = عدم;
    AVBPrint bprint;
    صحيح cnt = 0;
    حرف special_chars[] = {pairs_sep, key_val_sep, '\0'};

    𐡄𐡍 (!buffer || pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\')
        أرجع AVERROR(EINVAL);

    𐡄𐡍 (!av_dict_count(m)) {
        *buffer = av_strdup("");
        أرجع *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    طالما ((t = av_dict_iterate(m, t))) {
        𐡄𐡍 (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->key, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &key_val_sep, 1);
        av_bprint_escape(&bprint, t->value, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    أرجع av_bprint_finalize(&bprint, buffer);
}
