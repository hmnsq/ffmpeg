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

#அந்தர்பாவ <inttypes.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "avstring.h"
#அந்தர்பாவ "dict.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "bprint.h"

கட்டமைப்பு AVDictionary {
    முழு மொத்தம்;
    AVDictionaryEntry *elems;
    முழு duplicate_சாவிகள்;
};

முழு av_dict_மொத்தம்(மாறிலி AVDictionary *m)
{
    திரும்பு m ? m->மொத்தம் : 0;
}

மாறிலி AVDictionaryEntry *av_dict_iterate(மாறிலி AVDictionary *m,
                                         மாறிலி AVDictionaryEntry *prev)
{
    முழு i = 0;

    எனில் (!m)
        திரும்பு வெற்று;

    எனில் (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    எனில் (i >= m->மொத்தம்)
        திரும்பு வெற்று;

    திரும்பு &m->elems[i];
}

AVDictionaryEntry *av_dict_get(மாறிலி AVDictionary *m, மாறிலி எழுத்து *சாவி,
                               மாறிலி AVDictionaryEntry *prev, முழு flags)
{
    மாறிலி AVDictionaryEntry *entry = prev;
    unsigned முழு j;

    எனில் (!சாவி)
        திரும்பு வெற்று;

    போது ((entry = av_dict_iterate(m, entry))) {
        மாறிலி எழுத்து *s = entry->சாவி;
        எனில் (flags & AV_DICT_MATCH_CASE)
            க்கு (j = 0; s[j] == சாவி[j] && சாவி[j]; j++)
                ;
        இல்லையெனில்
            க்கு (j = 0; av_toupper(s[j]) == av_toupper(சாவி[j]) && சாவி[j]; j++)
                ;
        எனில் (சாவி[j])
            தொடர்;
        எனில் (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            தொடர்;
        திரும்பு (AVDictionaryEntry *)entry;
    }
    திரும்பு வெற்று;
}

முழு av_dict_set(AVDictionary **pm, மாறிலி எழுத்து *சாவி, மாறிலி எழுத்து *மதிப்பு,
                முழு flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = வெற்று;
    எழுத்து *copy_சாவி = வெற்று, *copy_மதிப்பு = வெற்று;
    முழு err;

    எனில் (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_மதிப்பு = (வெறுமை *)மதிப்பு;
    இல்லையெனில் எனில் (மதிப்பு)
        copy_மதிப்பு = av_strdup(மதிப்பு);
    எனில் (!சாவி) {
        err = AVERROR(EINVAL);
        செல் err_out;
    }
    எனில் (flags & AV_DICT_DONT_STRDUP_சாவி)
        copy_சாவி = (வெறுமை *)சாவி;
    இல்லையெனில்
        copy_சாவி = av_strdup(சாவி);
    எனில் (!copy_சாவி || (மதிப்பு && !copy_மதிப்பு))
        செல் enomem;

    எனில் (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, சாவி, வெற்று, flags);
    } இல்லையெனில் எனில் (flags & AV_DICT_DEDUP) {
        போது ((tag = av_dict_get(m, சாவி, tag, flags))) {
            எனில் ((!மதிப்பு && !tag->மதிப்பு) ||
                (மதிப்பு && tag->மதிப்பு && !strcmp(மதிப்பு, tag->மதிப்பு))) {
                av_free(copy_சாவி);
                av_free(copy_மதிப்பு);
                திரும்பு 0;
            }
        }
    }
    எனில் (!m)
        m = *pm = av_mallocz(அளவு(*m));
    எனில் (!m)
        செல் enomem;

    எனில் (tag) {
        எனில் (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_சாவி);
            av_free(copy_மதிப்பு);
            திரும்பு 0;
        }
        எனில் (copy_மதிப்பு && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->மதிப்பு);
            size_t new_part_len = strlen(copy_மதிப்பு);
            size_t len = oldlen + new_part_len + 1;
            எழுத்து *newval = av_realloc(tag->மதிப்பு, len);
            எனில் (!newval)
                செல் enomem;
            memcpy(newval + oldlen, copy_மதிப்பு, new_part_len + 1);
            av_freep(&copy_மதிப்பு);
            copy_மதிப்பு = newval;
        } இல்லையெனில்
            av_free(tag->மதிப்பு);
        av_free(tag->சாவி);
        *tag = m->elems[--m->மொத்தம்];
    } இல்லையெனில் எனில் (copy_மதிப்பு) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->மொத்தம் + 1, அளவு(*m->elems));
        எனில் (!tmp)
            செல் enomem;
        m->elems = tmp;
    }
    எனில் (copy_மதிப்பு) {
        m->elems[m->மொத்தம்].சாவி = copy_சாவி;
        m->elems[m->மொத்தம்].மதிப்பு = copy_மதிப்பு;
        m->மொத்தம்++;
        எனில் (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_சாவிகள் = 1;
    } இல்லையெனில் {
        err = 0;
        செல் end;
    }

    திரும்பு 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_மதிப்பு);
end:
    எனில் (m && !m->மொத்தம்) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_சாவி);
    திரும்பு err;
}

முழு av_dict_set_int(AVDictionary **pm, மாறிலி எழுத்து *சாவி, int64_t மதிப்பு,
                முழு flags)
{
    எழுத்து valuestr[22];
    snprintf(valuestr, அளவு(valuestr), "%"PRId64, மதிப்பு);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    திரும்பு av_dict_set(pm, சாவி, valuestr, flags);
}

நிலையான முழு parse_சாவி_மதிப்பு_pair(AVDictionary **pm, மாறிலி எழுத்து **buf,
                                மாறிலி எழுத்து *சாவி_val_sep, மாறிலி எழுத்து *pairs_sep,
                                முழு flags)
{
    எழுத்து *சாவி = av_get_token(buf, சாவி_val_sep);
    எழுத்து *val = வெற்று;
    முழு ret;

    எனில் (சாவி && *சாவி && strspn(*buf, சாவி_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    எனில் (சாவி && *சாவி && val && *val)
        ret = av_dict_set(pm, சாவி, val, flags);
    இல்லையெனில்
        ret = AVERROR(EINVAL);

    av_freep(&சாவி);
    av_freep(&val);

    திரும்பு ret;
}

முழு av_dict_parse_string(AVDictionary **pm, மாறிலி எழுத்து *str,
                         மாறிலி எழுத்து *சாவி_val_sep, மாறிலி எழுத்து *pairs_sep,
                         முழு flags)
{
    முழு ret;

    எனில் (!str)
        திரும்பு 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_சாவி | AV_DICT_DONT_STRDUP_VAL);

    போது (*str) {
        எனில் ((ret = parse_சாவி_மதிப்பு_pair(pm, &str, சாவி_val_sep, pairs_sep, flags)) < 0)
            திரும்பு ret;

        எனில் (*str)
            str++;
    }

    திரும்பு 0;
}

வெறுமை av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    எனில் (m) {
        போது (m->மொத்தம்--) {
            av_freep(&m->elems[m->மொத்தம்].சாவி);
            av_freep(&m->elems[m->மொத்தம்].மதிப்பு);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

முழு av_dict_copy(AVDictionary **dst, மாறிலி AVDictionary *src, முழு flags)
{
    மாறிலி AVDictionaryEntry *t = வெற்று;

    எனில் (!*dst && src && src->மொத்தம் && !src->duplicate_சாவிகள் &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(அளவு(*m));
        எனில் (!m)
            திரும்பு AVERROR(ENOMEM);
        m->elems = av_calloc(src->மொத்தம், அளவு(*m->elems));
        எனில் (!m->elems) {
            av_free(m);
            திரும்பு AVERROR(ENOMEM);
        }
        *dst = m;
        க்கு (முழு i = 0; i < src->மொத்தம்; i++) {
            m->elems[i].சாவி   = av_strdup(src->elems[i].சாவி);
            m->elems[i].மதிப்பு = av_strdup(src->elems[i].மதிப்பு);
            m->மொத்தம்++;
            எனில் (!m->elems[i].சாவி || !m->elems[i].மதிப்பு) {
                av_dict_free(dst);
                திரும்பு AVERROR(ENOMEM);
            }
        }
        திரும்பு 0;
    }

    போது ((t = av_dict_iterate(src, t))) {
        முழு ret = av_dict_set(dst, t->சாவி, t->மதிப்பு, flags);
        எனில் (ret < 0)
            திரும்பு ret;
    }

    திரும்பு 0;
}

முழு av_dict_get_string(மாறிலி AVDictionary *m, எழுத்து **buffer,
                       மாறிலி எழுத்து சாவி_val_sep, மாறிலி எழுத்து pairs_sep)
{
    மாறிலி AVDictionaryEntry *t = வெற்று;
    AVBPrint bprint;
    முழு cnt = 0;
    எழுத்து special_chars[] = {pairs_sep, சாவி_val_sep, '\0'};

    எனில் (!buffer || pairs_sep == '\0' || சாவி_val_sep == '\0' || pairs_sep == சாவி_val_sep ||
        pairs_sep == '\\' || சாவி_val_sep == '\\')
        திரும்பு AVERROR(EINVAL);

    எனில் (!av_dict_மொத்தம்(m)) {
        *buffer = av_strdup("");
        திரும்பு *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    போது ((t = av_dict_iterate(m, t))) {
        எனில் (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->சாவி, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &சாவி_val_sep, 1);
        av_bprint_escape(&bprint, t->மதிப்பு, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    திரும்பு av_bprint_finalize(&bprint, buffer);
}
