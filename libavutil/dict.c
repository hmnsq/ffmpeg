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

#ಅನ್ತರ್ಭಾವ <inttypes.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "dict.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "bprint.h"

ಸಂರಚನಾ AVDictionary {
    ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ;
    AVDictionaryEntry *elems;
    ಪೂರ್ಣಾಙ್ಕ duplicate_ಕೀಲಿಗಳು;
};

ಪೂರ್ಣಾಙ್ಕ av_dict_ಎಣಿಕೆ(ಧ್ರುವ AVDictionary *m)
{
    ಪ್ರತ್ಯಾಗಮ m ? m->ಎಣಿಕೆ : 0;
}

ಧ್ರುವ AVDictionaryEntry *av_dict_iterate(ಧ್ರುವ AVDictionary *m,
                                         ಧ್ರುವ AVDictionaryEntry *prev)
{
    ಪೂರ್ಣಾಙ್ಕ i = 0;

    ಯದಿ (!m)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಯದಿ (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    ಯದಿ (i >= m->ಎಣಿಕೆ)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಪ್ರತ್ಯಾಗಮ &m->elems[i];
}

AVDictionaryEntry *av_dict_get(ಧ್ರುವ AVDictionary *m, ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ,
                               ಧ್ರುವ AVDictionaryEntry *prev, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಧ್ರುವ AVDictionaryEntry *entry = prev;
    unsigned ಪೂರ್ಣಾಙ್ಕ j;

    ಯದಿ (!ಕೀಲಿ)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಯಾವತ್ ((entry = av_dict_iterate(m, entry))) {
        ಧ್ರುವ ವರ್ಣ *s = entry->ಕೀಲಿ;
        ಯದಿ (flags & AV_DICT_MATCH_CASE)
            ಪ್ರತಿ (j = 0; s[j] == ಕೀಲಿ[j] && ಕೀಲಿ[j]; j++)
                ;
        ಅನ್ಯಥಾ
            ಪ್ರತಿ (j = 0; av_toupper(s[j]) == av_toupper(ಕೀಲಿ[j]) && ಕೀಲಿ[j]; j++)
                ;
        ಯದಿ (ಕೀಲಿ[j])
            ಅನುವರ್ತ;
        ಯದಿ (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            ಅನುವರ್ತ;
        ಪ್ರತ್ಯಾಗಮ (AVDictionaryEntry *)entry;
    }
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಪೂರ್ಣಾಙ್ಕ av_dict_set(AVDictionary **pm, ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ, ಧ್ರುವ ವರ್ಣ *ಮೌಲ್ಯ,
                ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = ರಿಕ್ತ;
    ವರ್ಣ *copy_ಕೀಲಿ = ರಿಕ್ತ, *copy_ಮೌಲ್ಯ = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ err;

    ಯದಿ (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_ಮೌಲ್ಯ = (ಶೂನ್ಯ *)ಮೌಲ್ಯ;
    ಅನ್ಯಥಾ ಯದಿ (ಮೌಲ್ಯ)
        copy_ಮೌಲ್ಯ = av_strdup(ಮೌಲ್ಯ);
    ಯದಿ (!ಕೀಲಿ) {
        err = AVERROR(EINVAL);
        ಗಚ್ಛ err_out;
    }
    ಯದಿ (flags & AV_DICT_DONT_STRDUP_ಕೀಲಿ)
        copy_ಕೀಲಿ = (ಶೂನ್ಯ *)ಕೀಲಿ;
    ಅನ್ಯಥಾ
        copy_ಕೀಲಿ = av_strdup(ಕೀಲಿ);
    ಯದಿ (!copy_ಕೀಲಿ || (ಮೌಲ್ಯ && !copy_ಮೌಲ್ಯ))
        ಗಚ್ಛ enomem;

    ಯದಿ (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, ಕೀಲಿ, ರಿಕ್ತ, flags);
    } ಅನ್ಯಥಾ ಯದಿ (flags & AV_DICT_DEDUP) {
        ಯಾವತ್ ((tag = av_dict_get(m, ಕೀಲಿ, tag, flags))) {
            ಯದಿ ((!ಮೌಲ್ಯ && !tag->ಮೌಲ್ಯ) ||
                (ಮೌಲ್ಯ && tag->ಮೌಲ್ಯ && !strcmp(ಮೌಲ್ಯ, tag->ಮೌಲ್ಯ))) {
                av_free(copy_ಕೀಲಿ);
                av_free(copy_ಮೌಲ್ಯ);
                ಪ್ರತ್ಯಾಗಮ 0;
            }
        }
    }
    ಯದಿ (!m)
        m = *pm = av_mallocz(ಪರಿಮಾಣ(*m));
    ಯದಿ (!m)
        ಗಚ್ಛ enomem;

    ಯದಿ (tag) {
        ಯದಿ (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_ಕೀಲಿ);
            av_free(copy_ಮೌಲ್ಯ);
            ಪ್ರತ್ಯಾಗಮ 0;
        }
        ಯದಿ (copy_ಮೌಲ್ಯ && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->ಮೌಲ್ಯ);
            size_t new_part_len = strlen(copy_ಮೌಲ್ಯ);
            size_t len = oldlen + new_part_len + 1;
            ವರ್ಣ *newval = av_realloc(tag->ಮೌಲ್ಯ, len);
            ಯದಿ (!newval)
                ಗಚ್ಛ enomem;
            memcpy(newval + oldlen, copy_ಮೌಲ್ಯ, new_part_len + 1);
            av_freep(&copy_ಮೌಲ್ಯ);
            copy_ಮೌಲ್ಯ = newval;
        } ಅನ್ಯಥಾ
            av_free(tag->ಮೌಲ್ಯ);
        av_free(tag->ಕೀಲಿ);
        *tag = m->elems[--m->ಎಣಿಕೆ];
    } ಅನ್ಯಥಾ ಯದಿ (copy_ಮೌಲ್ಯ) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->ಎಣಿಕೆ + 1, ಪರಿಮಾಣ(*m->elems));
        ಯದಿ (!tmp)
            ಗಚ್ಛ enomem;
        m->elems = tmp;
    }
    ಯದಿ (copy_ಮೌಲ್ಯ) {
        m->elems[m->ಎಣಿಕೆ].ಕೀಲಿ = copy_ಕೀಲಿ;
        m->elems[m->ಎಣಿಕೆ].ಮೌಲ್ಯ = copy_ಮೌಲ್ಯ;
        m->ಎಣಿಕೆ++;
        ಯದಿ (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_ಕೀಲಿಗಳು = 1;
    } ಅನ್ಯಥಾ {
        err = 0;
        ಗಚ್ಛ end;
    }

    ಪ್ರತ್ಯಾಗಮ 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_ಮೌಲ್ಯ);
end:
    ಯದಿ (m && !m->ಎಣಿಕೆ) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_ಕೀಲಿ);
    ಪ್ರತ್ಯಾಗಮ err;
}

ಪೂರ್ಣಾಙ್ಕ av_dict_set_int(AVDictionary **pm, ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ, int64_t ಮೌಲ್ಯ,
                ಪೂರ್ಣಾಙ್ಕ flags)
{
    ವರ್ಣ valuestr[22];
    snprintf(valuestr, ಪರಿಮಾಣ(valuestr), "%"PRId64, ಮೌಲ್ಯ);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    ಪ್ರತ್ಯಾಗಮ av_dict_set(pm, ಕೀಲಿ, valuestr, flags);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ parse_ಕೀಲಿ_ಮೌಲ್ಯ_pair(AVDictionary **pm, ಧ್ರುವ ವರ್ಣ **buf,
                                ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ_val_sep, ಧ್ರುವ ವರ್ಣ *pairs_sep,
                                ಪೂರ್ಣಾಙ್ಕ flags)
{
    ವರ್ಣ *ಕೀಲಿ = av_get_token(buf, ಕೀಲಿ_val_sep);
    ವರ್ಣ *val = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (ಕೀಲಿ && *ಕೀಲಿ && strspn(*buf, ಕೀಲಿ_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    ಯದಿ (ಕೀಲಿ && *ಕೀಲಿ && val && *val)
        ret = av_dict_set(pm, ಕೀಲಿ, val, flags);
    ಅನ್ಯಥಾ
        ret = AVERROR(EINVAL);

    av_freep(&ಕೀಲಿ);
    av_freep(&val);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_dict_parse_string(AVDictionary **pm, ಧ್ರುವ ವರ್ಣ *str,
                         ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ_val_sep, ಧ್ರುವ ವರ್ಣ *pairs_sep,
                         ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (!str)
        ಪ್ರತ್ಯಾಗಮ 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_ಕೀಲಿ | AV_DICT_DONT_STRDUP_VAL);

    ಯಾವತ್ (*str) {
        ಯದಿ ((ret = parse_ಕೀಲಿ_ಮೌಲ್ಯ_pair(pm, &str, ಕೀಲಿ_val_sep, pairs_sep, flags)) < 0)
            ಪ್ರತ್ಯಾಗಮ ret;

        ಯದಿ (*str)
            str++;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    ಯದಿ (m) {
        ಯಾವತ್ (m->ಎಣಿಕೆ--) {
            av_freep(&m->elems[m->ಎಣಿಕೆ].ಕೀಲಿ);
            av_freep(&m->elems[m->ಎಣಿಕೆ].ಮೌಲ್ಯ);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

ಪೂರ್ಣಾಙ್ಕ av_dict_copy(AVDictionary **dst, ಧ್ರುವ AVDictionary *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಧ್ರುವ AVDictionaryEntry *t = ರಿಕ್ತ;

    ಯದಿ (!*dst && src && src->ಎಣಿಕೆ && !src->duplicate_ಕೀಲಿಗಳು &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(ಪರಿಮಾಣ(*m));
        ಯದಿ (!m)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        m->elems = av_calloc(src->ಎಣಿಕೆ, ಪರಿಮಾಣ(*m->elems));
        ಯದಿ (!m->elems) {
            av_free(m);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }
        *dst = m;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < src->ಎಣಿಕೆ; i++) {
            m->elems[i].ಕೀಲಿ   = av_strdup(src->elems[i].ಕೀಲಿ);
            m->elems[i].ಮೌಲ್ಯ = av_strdup(src->elems[i].ಮೌಲ್ಯ);
            m->ಎಣಿಕೆ++;
            ಯದಿ (!m->elems[i].ಕೀಲಿ || !m->elems[i].ಮೌಲ್ಯ) {
                av_dict_free(dst);
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            }
        }
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಯಾವತ್ ((t = av_dict_iterate(src, t))) {
        ಪೂರ್ಣಾಙ್ಕ ret = av_dict_set(dst, t->ಕೀಲಿ, t->ಮೌಲ್ಯ, flags);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_dict_get_string(ಧ್ರುವ AVDictionary *m, ವರ್ಣ **buffer,
                       ಧ್ರುವ ವರ್ಣ ಕೀಲಿ_val_sep, ಧ್ರುವ ವರ್ಣ pairs_sep)
{
    ಧ್ರುವ AVDictionaryEntry *t = ರಿಕ್ತ;
    AVBPrint bprint;
    ಪೂರ್ಣಾಙ್ಕ cnt = 0;
    ವರ್ಣ special_chars[] = {pairs_sep, ಕೀಲಿ_val_sep, '\0'};

    ಯದಿ (!buffer || pairs_sep == '\0' || ಕೀಲಿ_val_sep == '\0' || pairs_sep == ಕೀಲಿ_val_sep ||
        pairs_sep == '\\' || ಕೀಲಿ_val_sep == '\\')
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (!av_dict_ಎಣಿಕೆ(m)) {
        *buffer = av_strdup("");
        ಪ್ರತ್ಯಾಗಮ *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    ಯಾವತ್ ((t = av_dict_iterate(m, t))) {
        ಯದಿ (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->ಕೀಲಿ, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &ಕೀಲಿ_val_sep, 1);
        av_bprint_escape(&bprint, t->ಮೌಲ್ಯ, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    ಪ್ರತ್ಯಾಗಮ av_bprint_finalize(&bprint, buffer);
}
