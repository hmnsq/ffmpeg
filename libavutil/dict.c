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

#অন্তর্ভাব <inttypes.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "avstring.h"
#অন্তর্ভাব "dict.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "bprint.h"

কাঠামো AVDictionary {
    পূর্ণসংখ্যা গুনতি;
    AVDictionaryEntry *elems;
    পূর্ণসংখ্যা duplicate_চাবিগুলি;
};

পূর্ণসংখ্যা av_dict_গুনতি(ধ্রুবক AVDictionary *m)
{
    ফেরত m ? m->গুনতি : 0;
}

ধ্রুবক AVDictionaryEntry *av_dict_iterate(ধ্রুবক AVDictionary *m,
                                         ধ্রুবক AVDictionaryEntry *পূর্ব)
{
    পূর্ণসংখ্যা i = 0;

    যদি (!m)
        ফেরত ফাঁকা;

    যদি (পূর্ব)
        i = পূর্ব - m->elems + 1;

    av_assert2(i >= 0);
    যদি (i >= m->গুনতি)
        ফেরত ফাঁকা;

    ফেরত &m->elems[i];
}

AVDictionaryEntry *av_dict_get(ধ্রুবক AVDictionary *m, ধ্রুবক অক্ষর *চাবি,
                               ধ্রুবক AVDictionaryEntry *পূর্ব, পূর্ণসংখ্যা flags)
{
    ধ্রুবক AVDictionaryEntry *entry = পূর্ব;
    unsigned পূর্ণসংখ্যা j;

    যদি (!চাবি)
        ফেরত ফাঁকা;

    যখন ((entry = av_dict_iterate(m, entry))) {
        ধ্রুবক অক্ষর *s = entry->চাবি;
        যদি (flags & AV_DICT_MATCH_CASE)
            জন্য (j = 0; s[j] == চাবি[j] && চাবি[j]; j++)
                ;
        অন্যথা
            জন্য (j = 0; av_toupper(s[j]) == av_toupper(চাবি[j]) && চাবি[j]; j++)
                ;
        যদি (চাবি[j])
            চালু;
        যদি (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            চালু;
        ফেরত (AVDictionaryEntry *)entry;
    }
    ফেরত ফাঁকা;
}

পূর্ণসংখ্যা av_dict_set(AVDictionary **pm, ধ্রুবক অক্ষর *চাবি, ধ্রুবক অক্ষর *মান,
                পূর্ণসংখ্যা flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = ফাঁকা;
    অক্ষর *copy_চাবি = ফাঁকা, *copy_মান = ফাঁকা;
    পূর্ণসংখ্যা err;

    যদি (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_মান = (শূন্য *)মান;
    অন্যথা যদি (মান)
        copy_মান = av_strdup(মান);
    যদি (!চাবি) {
        err = AVERROR(EINVAL);
        যাও err_out;
    }
    যদি (flags & AV_DICT_DONT_STRDUP_চাবি)
        copy_চাবি = (শূন্য *)চাবি;
    অন্যথা
        copy_চাবি = av_strdup(চাবি);
    যদি (!copy_চাবি || (মান && !copy_মান))
        যাও enomem;

    যদি (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, চাবি, ফাঁকা, flags);
    } অন্যথা যদি (flags & AV_DICT_DEDUP) {
        যখন ((tag = av_dict_get(m, চাবি, tag, flags))) {
            যদি ((!মান && !tag->মান) ||
                (মান && tag->মান && !strcmp(মান, tag->মান))) {
                av_free(copy_চাবি);
                av_free(copy_মান);
                ফেরত 0;
            }
        }
    }
    যদি (!m)
        m = *pm = av_mallocz(আকার(*m));
    যদি (!m)
        যাও enomem;

    যদি (tag) {
        যদি (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_চাবি);
            av_free(copy_মান);
            ফেরত 0;
        }
        যদি (copy_মান && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->মান);
            size_t new_part_len = strlen(copy_মান);
            size_t len = oldlen + new_part_len + 1;
            অক্ষর *newval = av_realloc(tag->মান, len);
            যদি (!newval)
                যাও enomem;
            memcpy(newval + oldlen, copy_মান, new_part_len + 1);
            av_freep(&copy_মান);
            copy_মান = newval;
        } অন্যথা
            av_free(tag->মান);
        av_free(tag->চাবি);
        *tag = m->elems[--m->গুনতি];
    } অন্যথা যদি (copy_মান) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->গুনতি + 1, আকার(*m->elems));
        যদি (!tmp)
            যাও enomem;
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
        যাও end;
    }

    ফেরত 0;

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
    ফেরত err;
}

পূর্ণসংখ্যা av_dict_set_int(AVDictionary **pm, ধ্রুবক অক্ষর *চাবি, int64_t মান,
                পূর্ণসংখ্যা flags)
{
    অক্ষর valuestr[22];
    snprintf(valuestr, আকার(valuestr), "%"PRId64, মান);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    ফেরত av_dict_set(pm, চাবি, valuestr, flags);
}

স্থির পূর্ণসংখ্যা parse_চাবি_মান_pair(AVDictionary **pm, ধ্রুবক অক্ষর **buf,
                                ধ্রুবক অক্ষর *চাবি_val_sep, ধ্রুবক অক্ষর *pairs_sep,
                                পূর্ণসংখ্যা flags)
{
    অক্ষর *চাবি = av_get_token(buf, চাবি_val_sep);
    অক্ষর *val = ফাঁকা;
    পূর্ণসংখ্যা ret;

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

    ফেরত ret;
}

পূর্ণসংখ্যা av_dict_parse_string(AVDictionary **pm, ধ্রুবক অক্ষর *str,
                         ধ্রুবক অক্ষর *চাবি_val_sep, ধ্রুবক অক্ষর *pairs_sep,
                         পূর্ণসংখ্যা flags)
{
    পূর্ণসংখ্যা ret;

    যদি (!str)
        ফেরত 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_চাবি | AV_DICT_DONT_STRDUP_VAL);

    যখন (*str) {
        যদি ((ret = parse_চাবি_মান_pair(pm, &str, চাবি_val_sep, pairs_sep, flags)) < 0)
            ফেরত ret;

        যদি (*str)
            str++;
    }

    ফেরত 0;
}

শূন্য av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    যদি (m) {
        যখন (m->গুনতি--) {
            av_freep(&m->elems[m->গুনতি].চাবি);
            av_freep(&m->elems[m->গুনতি].মান);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

পূর্ণসংখ্যা av_dict_copy(AVDictionary **dst, ধ্রুবক AVDictionary *src, পূর্ণসংখ্যা flags)
{
    ধ্রুবক AVDictionaryEntry *t = ফাঁকা;

    যদি (!*dst && src && src->গুনতি && !src->duplicate_চাবিগুলি &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(আকার(*m));
        যদি (!m)
            ফেরত AVERROR(ENOMEM);
        m->elems = av_calloc(src->গুনতি, আকার(*m->elems));
        যদি (!m->elems) {
            av_free(m);
            ফেরত AVERROR(ENOMEM);
        }
        *dst = m;
        জন্য (পূর্ণসংখ্যা i = 0; i < src->গুনতি; i++) {
            m->elems[i].চাবি   = av_strdup(src->elems[i].চাবি);
            m->elems[i].মান = av_strdup(src->elems[i].মান);
            m->গুনতি++;
            যদি (!m->elems[i].চাবি || !m->elems[i].মান) {
                av_dict_free(dst);
                ফেরত AVERROR(ENOMEM);
            }
        }
        ফেরত 0;
    }

    যখন ((t = av_dict_iterate(src, t))) {
        পূর্ণসংখ্যা ret = av_dict_set(dst, t->চাবি, t->মান, flags);
        যদি (ret < 0)
            ফেরত ret;
    }

    ফেরত 0;
}

পূর্ণসংখ্যা av_dict_get_string(ধ্রুবক AVDictionary *m, অক্ষর **বাফার,
                       ধ্রুবক অক্ষর চাবি_val_sep, ধ্রুবক অক্ষর pairs_sep)
{
    ধ্রুবক AVDictionaryEntry *t = ফাঁকা;
    AVBPrint bprint;
    পূর্ণসংখ্যা cnt = 0;
    অক্ষর special_chars[] = {pairs_sep, চাবি_val_sep, '\0'};

    যদি (!বাফার || pairs_sep == '\0' || চাবি_val_sep == '\0' || pairs_sep == চাবি_val_sep ||
        pairs_sep == '\\' || চাবি_val_sep == '\\')
        ফেরত AVERROR(EINVAL);

    যদি (!av_dict_গুনতি(m)) {
        *বাফার = av_strdup("");
        ফেরত *বাফার ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_আকার_UNLIMITED);
    যখন ((t = av_dict_iterate(m, t))) {
        যদি (cnt++)
            av_bprint_append_তথ্য(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->চাবি, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_তথ্য(&bprint, &চাবি_val_sep, 1);
        av_bprint_escape(&bprint, t->মান, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    ফেরত av_bprint_finalize(&bprint, বাফার);
}
