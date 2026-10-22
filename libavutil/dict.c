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

#অন্তর্ভাৱ <inttypes.h>
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <string.h>

#অন্তর্ভাৱ "avassert.h"
#অন্তর্ভাৱ "avstring.h"
#অন্তর্ভাৱ "dict.h"
#অন্তর্ভাৱ "error.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "bprint.h"

সংরচনা AVDictionary {
    পূর্ণাঙ্ক গুনতি;
    AVDictionaryEntry *elems;
    পূর্ণাঙ্ক duplicate_চাবিগুলি;
};

পূর্ণাঙ্ক av_dict_গুনতি(ধ্রুৱ AVDictionary *m)
{
    ঘূৰাই m ? m->গুনতি : 0;
}

ধ্রুৱ AVDictionaryEntry *av_dict_iterate(ধ্রুৱ AVDictionary *m,
                                         ধ্রুৱ AVDictionaryEntry *prev)
{
    পূর্ণাঙ্ক i = 0;

    যদি (!m)
        ঘূৰাই রিক্ত;

    যদি (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    যদি (i >= m->গুনতি)
        ঘূৰাই রিক্ত;

    ঘূৰাই &m->elems[i];
}

AVDictionaryEntry *av_dict_get(ধ্রুৱ AVDictionary *m, ধ্রুৱ ৱর্ণ *চাবি,
                               ধ্রুৱ AVDictionaryEntry *prev, পূর্ণাঙ্ক flags)
{
    ধ্রুৱ AVDictionaryEntry *entry = prev;
    unsigned পূর্ণাঙ্ক j;

    যদি (!চাবি)
        ঘূৰাই রিক্ত;

    যেতিয়ালৈ ((entry = av_dict_iterate(m, entry))) {
        ধ্রুৱ ৱর্ণ *s = entry->চাবি;
        যদি (flags & AV_DICT_MATCH_CASE)
            বাবে (j = 0; s[j] == চাবি[j] && চাবি[j]; j++)
                ;
        অন্যথা
            বাবে (j = 0; av_toupper(s[j]) == av_toupper(চাবি[j]) && চাবি[j]; j++)
                ;
        যদি (চাবি[j])
            অনুৱর্ত;
        যদি (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            অনুৱর্ত;
        ঘূৰাই (AVDictionaryEntry *)entry;
    }
    ঘূৰাই রিক্ত;
}

পূর্ণাঙ্ক av_dict_set(AVDictionary **pm, ধ্রুৱ ৱর্ণ *চাবি, ধ্রুৱ ৱর্ণ *মান,
                পূর্ণাঙ্ক flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = রিক্ত;
    ৱর্ণ *copy_চাবি = রিক্ত, *copy_মান = রিক্ত;
    পূর্ণাঙ্ক err;

    যদি (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_মান = (শূন্য *)মান;
    অন্যথা যদি (মান)
        copy_মান = av_strdup(মান);
    যদি (!চাবি) {
        err = AVERROR(EINVAL);
        গচ্ছ err_out;
    }
    যদি (flags & AV_DICT_DONT_STRDUP_চাবি)
        copy_চাবি = (শূন্য *)চাবি;
    অন্যথা
        copy_চাবি = av_strdup(চাবি);
    যদি (!copy_চাবি || (মান && !copy_মান))
        গচ্ছ enomem;

    যদি (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, চাবি, রিক্ত, flags);
    } অন্যথা যদি (flags & AV_DICT_DEDUP) {
        যেতিয়ালৈ ((tag = av_dict_get(m, চাবি, tag, flags))) {
            যদি ((!মান && !tag->মান) ||
                (মান && tag->মান && !strcmp(মান, tag->মান))) {
                av_free(copy_চাবি);
                av_free(copy_মান);
                ঘূৰাই 0;
            }
        }
    }
    যদি (!m)
        m = *pm = av_mallocz(পরিমাণ(*m));
    যদি (!m)
        গচ্ছ enomem;

    যদি (tag) {
        যদি (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_চাবি);
            av_free(copy_মান);
            ঘূৰাই 0;
        }
        যদি (copy_মান && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->মান);
            size_t new_part_len = strlen(copy_মান);
            size_t len = oldlen + new_part_len + 1;
            ৱর্ণ *newval = av_realloc(tag->মান, len);
            যদি (!newval)
                গচ্ছ enomem;
            memcpy(newval + oldlen, copy_মান, new_part_len + 1);
            av_freep(&copy_মান);
            copy_মান = newval;
        } অন্যথা
            av_free(tag->মান);
        av_free(tag->চাবি);
        *tag = m->elems[--m->গুনতি];
    } অন্যথা যদি (copy_মান) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->গুনতি + 1, পরিমাণ(*m->elems));
        যদি (!tmp)
            গচ্ছ enomem;
        m->elems = tmp;
    }
    যদি (copy_মান) {
        m->elems[m->গুনতি].চাবি = copy_চাবি;
        m->elems[m->গুনতি].মান = copy_মান;
        m->গুনতি++;
        যদি (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_চাবিগুলি = 1;
    } অন্যথা {
        err = 0;
        গচ্ছ end;
    }

    ঘূৰাই 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_মান);
end:
    যদি (m && !m->গুনতি) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_চাবি);
    ঘূৰাই err;
}

পূর্ণাঙ্ক av_dict_set_int(AVDictionary **pm, ধ্রুৱ ৱর্ণ *চাবি, int64_t মান,
                পূর্ণাঙ্ক flags)
{
    ৱর্ণ valuestr[22];
    snprintf(valuestr, পরিমাণ(valuestr), "%"PRId64, মান);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    ঘূৰাই av_dict_set(pm, চাবি, valuestr, flags);
}

স্থির পূর্ণাঙ্ক parse_চাবি_মান_pair(AVDictionary **pm, ধ্রুৱ ৱর্ণ **buf,
                                ধ্রুৱ ৱর্ণ *চাবি_val_sep, ধ্রুৱ ৱর্ণ *pairs_sep,
                                পূর্ণাঙ্ক flags)
{
    ৱর্ণ *চাবি = av_get_token(buf, চাবি_val_sep);
    ৱর্ণ *val = রিক্ত;
    পূর্ণাঙ্ক ret;

    যদি (চাবি && *চাবি && strspn(*buf, চাবি_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    যদি (চাবি && *চাবি && val && *val)
        ret = av_dict_set(pm, চাবি, val, flags);
    অন্যথা
        ret = AVERROR(EINVAL);

    av_freep(&চাবি);
    av_freep(&val);

    ঘূৰাই ret;
}

পূর্ণাঙ্ক av_dict_parse_string(AVDictionary **pm, ধ্রুৱ ৱর্ণ *str,
                         ধ্রুৱ ৱর্ণ *চাবি_val_sep, ধ্রুৱ ৱর্ণ *pairs_sep,
                         পূর্ণাঙ্ক flags)
{
    পূর্ণাঙ্ক ret;

    যদি (!str)
        ঘূৰাই 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_চাবি | AV_DICT_DONT_STRDUP_VAL);

    যেতিয়ালৈ (*str) {
        যদি ((ret = parse_চাবি_মান_pair(pm, &str, চাবি_val_sep, pairs_sep, flags)) < 0)
            ঘূৰাই ret;

        যদি (*str)
            str++;
    }

    ঘূৰাই 0;
}

শূন্য av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    যদি (m) {
        যেতিয়ালৈ (m->গুনতি--) {
            av_freep(&m->elems[m->গুনতি].চাবি);
            av_freep(&m->elems[m->গুনতি].মান);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

পূর্ণাঙ্ক av_dict_copy(AVDictionary **dst, ধ্রুৱ AVDictionary *src, পূর্ণাঙ্ক flags)
{
    ধ্রুৱ AVDictionaryEntry *t = রিক্ত;

    যদি (!*dst && src && src->গুনতি && !src->duplicate_চাবিগুলি &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(পরিমাণ(*m));
        যদি (!m)
            ঘূৰাই AVERROR(ENOMEM);
        m->elems = av_calloc(src->গুনতি, পরিমাণ(*m->elems));
        যদি (!m->elems) {
            av_free(m);
            ঘূৰাই AVERROR(ENOMEM);
        }
        *dst = m;
        বাবে (পূর্ণাঙ্ক i = 0; i < src->গুনতি; i++) {
            m->elems[i].চাবি   = av_strdup(src->elems[i].চাবি);
            m->elems[i].মান = av_strdup(src->elems[i].মান);
            m->গুনতি++;
            যদি (!m->elems[i].চাবি || !m->elems[i].মান) {
                av_dict_free(dst);
                ঘূৰাই AVERROR(ENOMEM);
            }
        }
        ঘূৰাই 0;
    }

    যেতিয়ালৈ ((t = av_dict_iterate(src, t))) {
        পূর্ণাঙ্ক ret = av_dict_set(dst, t->চাবি, t->মান, flags);
        যদি (ret < 0)
            ঘূৰাই ret;
    }

    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_dict_get_string(ধ্রুৱ AVDictionary *m, ৱর্ণ **buffer,
                       ধ্রুৱ ৱর্ণ চাবি_val_sep, ধ্রুৱ ৱর্ণ pairs_sep)
{
    ধ্রুৱ AVDictionaryEntry *t = রিক্ত;
    AVBPrint bprint;
    পূর্ণাঙ্ক cnt = 0;
    ৱর্ণ special_chars[] = {pairs_sep, চাবি_val_sep, '\0'};

    যদি (!buffer || pairs_sep == '\0' || চাবি_val_sep == '\0' || pairs_sep == চাবি_val_sep ||
        pairs_sep == '\\' || চাবি_val_sep == '\\')
        ঘূৰাই AVERROR(EINVAL);

    যদি (!av_dict_গুনতি(m)) {
        *buffer = av_strdup("");
        ঘূৰাই *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    যেতিয়ালৈ ((t = av_dict_iterate(m, t))) {
        যদি (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->চাবি, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &চাবি_val_sep, 1);
        av_bprint_escape(&bprint, t->মান, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    ঘূৰাই av_bprint_finalize(&bprint, buffer);
}
