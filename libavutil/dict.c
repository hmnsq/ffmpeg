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

ರಚನೆ AVDictionary {
    ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2;
    AVDictionary_ನಮೂದು *elems;
    ಪೂರ್ಣಾಂಕ duplicate_ಕೀಲಿಗಳು;
};

ಪೂರ್ಣಾಂಕ av_dict_ಎಣಿಕೆ(ಸ್ಥಿರಾಂಕ AVDictionary *m)
{
    ಹಿಂತಿರುಗಿ m ? m->ಎಣಿಕೆ_2 : 0;
}

ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *av_dict_iterate(ಸ್ಥಿರಾಂಕ AVDictionary *m,
                                         ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *prev)
{
    ಪೂರ್ಣಾಂಕ i = 0;

    ಆದರೆ (!m)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಆದರೆ (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    ಆದರೆ (i >= m->ಎಣಿಕೆ_2)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಹಿಂತಿರುಗಿ &m->elems[i];
}

AVDictionary_ನಮೂದು *av_dict_get(ಸ್ಥಿರಾಂಕ AVDictionary *m, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ,
                               ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *prev, ಪೂರ್ಣಾಂಕ flags)
{
    ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *ನಮೂದು = prev;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ j;

    ಆದರೆ (!ಕೀಲಿ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಆಗ ((ನಮೂದು = av_dict_iterate(m, ನಮೂದು))) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s = ನಮೂದು->ಕೀಲಿ;
        ಆದರೆ (flags & AV_DICT_ಹೊಂದಿಕೆ_CASE)
            ಗಾಗಿ (j = 0; s[j] == ಕೀಲಿ[j] && ಕೀಲಿ[j]; j++)
                ;
        ಇಲ್ಲದಿದ್ದರೆ
            ಗಾಗಿ (j = 0; av_toupper(s[j]) == av_toupper(ಕೀಲಿ[j]) && ಕೀಲಿ[j]; j++)
                ;
        ಆದರೆ (ಕೀಲಿ[j])
            ಮುಂದುವರಿ;
        ಆದರೆ (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            ಮುಂದುವರಿ;
        ಹಿಂತಿರುಗಿ (AVDictionary_ನಮೂದು *)ನಮೂದು;
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಪೂರ್ಣಾಂಕ av_dict_ಗಣ(AVDictionary **pm, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮೌಲ್ಯ,
                ಪೂರ್ಣಾಂಕ flags)
{
    AVDictionary *m = *pm;
    AVDictionary_ನಮೂದು *ಟ್ಯಾಗ್ = ಖಾಲಿ;
    ಅಕ್ಷರ *copy_ಕೀಲಿ = ಖಾಲಿ, *copy_ಮೌಲ್ಯ = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ err;

    ಆದರೆ (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_ಮೌಲ್ಯ = (ಶೂನ್ಯ *)ಮೌಲ್ಯ;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಮೌಲ್ಯ)
        copy_ಮೌಲ್ಯ = av_strdup(ಮೌಲ್ಯ);
    ಆದರೆ (!ಕೀಲಿ) {
        err = AVERROR(EINVAL);
        ಹೋಗು err_ಹೊರಹೋಗು;
    }
    ಆದರೆ (flags & AV_DICT_DONT_STRDUP_ಕೀಲಿ)
        copy_ಕೀಲಿ = (ಶೂನ್ಯ *)ಕೀಲಿ;
    ಇಲ್ಲದಿದ್ದರೆ
        copy_ಕೀಲಿ = av_strdup(ಕೀಲಿ);
    ಆದರೆ (!copy_ಕೀಲಿ || (ಮೌಲ್ಯ && !copy_ಮೌಲ್ಯ))
        ಹೋಗು enomem;

    ಆದರೆ (!(flags & AV_DICT_MULTIKEY)) {
        ಟ್ಯಾಗ್ = av_dict_get(m, ಕೀಲಿ, ಖಾಲಿ, flags);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (flags & AV_DICT_DEDUP) {
        ಆಗ ((ಟ್ಯಾಗ್ = av_dict_get(m, ಕೀಲಿ, ಟ್ಯಾಗ್, flags))) {
            ಆದರೆ ((!ಮೌಲ್ಯ && !ಟ್ಯಾಗ್->ಮೌಲ್ಯ) ||
                (ಮೌಲ್ಯ && ಟ್ಯಾಗ್->ಮೌಲ್ಯ && !strcmp(ಮೌಲ್ಯ, ಟ್ಯಾಗ್->ಮೌಲ್ಯ))) {
                av_free(copy_ಕೀಲಿ);
                av_free(copy_ಮೌಲ್ಯ);
                ಹಿಂತಿರುಗಿ 0;
            }
        }
    }
    ಆದರೆ (!m)
        m = *pm = av_mallocz(ಗಾತ್ರ(*m));
    ಆದರೆ (!m)
        ಹೋಗು enomem;

    ಆದರೆ (ಟ್ಯಾಗ್) {
        ಆದರೆ (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_ಕೀಲಿ);
            av_free(copy_ಮೌಲ್ಯ);
            ಹಿಂತಿರುಗಿ 0;
        }
        ಆದರೆ (copy_ಮೌಲ್ಯ && flags & AV_DICT_APPEND) {
            size_t oldlen = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(ಟ್ಯಾಗ್->ಮೌಲ್ಯ);
            size_t new_part_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(copy_ಮೌಲ್ಯ);
            size_t len = oldlen + new_part_len + 1;
            ಅಕ್ಷರ *newval = av_realloc(ಟ್ಯಾಗ್->ಮೌಲ್ಯ, len);
            ಆದರೆ (!newval)
                ಹೋಗು enomem;
            ಸ್ಮರಣೆ_ನಕಲು(newval + oldlen, copy_ಮೌಲ್ಯ, new_part_len + 1);
            av_freep(&copy_ಮೌಲ್ಯ);
            copy_ಮೌಲ್ಯ = newval;
        } ಇಲ್ಲದಿದ್ದರೆ
            av_free(ಟ್ಯಾಗ್->ಮೌಲ್ಯ);
        av_free(ಟ್ಯಾಗ್->ಕೀಲಿ);
        *ಟ್ಯಾಗ್ = m->elems[--m->ಎಣಿಕೆ_2];
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (copy_ಮೌಲ್ಯ) {
        AVDictionary_ನಮೂದು *tmp = av_realloc_array(m->elems,
                                                  m->ಎಣಿಕೆ_2 + 1, ಗಾತ್ರ(*m->elems));
        ಆದರೆ (!tmp)
            ಹೋಗು enomem;
        m->elems = tmp;
    }
    ಆದರೆ (copy_ಮೌಲ್ಯ) {
        m->elems[m->ಎಣಿಕೆ_2].ಕೀಲಿ = copy_ಕೀಲಿ;
        m->elems[m->ಎಣಿಕೆ_2].ಮೌಲ್ಯ = copy_ಮೌಲ್ಯ;
        m->ಎಣಿಕೆ_2++;
        ಆದರೆ (flags & (AV_DICT_ಹೊಂದಿಕೆ_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_ಕೀಲಿಗಳು = 1;
    } ಇಲ್ಲದಿದ್ದರೆ {
        err = 0;
        ಹೋಗು ಕೊನೆ;
    }

    ಹಿಂತಿರುಗಿ 0;

enomem:
    err = AVERROR(ENOMEM);
err_ಹೊರಹೋಗು:
    av_free(copy_ಮೌಲ್ಯ);
ಕೊನೆ:
    ಆದರೆ (m && !m->ಎಣಿಕೆ_2) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_ಕೀಲಿ);
    ಹಿಂತಿರುಗಿ err;
}

ಪೂರ್ಣಾಂಕ av_dict_ಗಣ_int(AVDictionary **pm, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ, int64_t ಮೌಲ್ಯ,
                ಪೂರ್ಣಾಂಕ flags)
{
    ಅಕ್ಷರ valuestr[22];
    snprintf(valuestr, ಗಾತ್ರ(valuestr), "%"PRId64, ಮೌಲ್ಯ);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    ಹಿಂತಿರುಗಿ av_dict_ಗಣ(pm, ಕೀಲಿ, valuestr, flags);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ parse_ಕೀಲಿ_ಮೌಲ್ಯ_pair(AVDictionary **pm, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **buf,
                                ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ_val_sep, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಜೋಡಿಗಳು_sep,
                                ಪೂರ್ಣಾಂಕ flags)
{
    ಅಕ್ಷರ *ಕೀಲಿ = av_get_token(buf, ಕೀಲಿ_val_sep);
    ಅಕ್ಷರ *val = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (ಕೀಲಿ && *ಕೀಲಿ && strspn(*buf, ಕೀಲಿ_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, ಜೋಡಿಗಳು_sep);
    }

    ಆದರೆ (ಕೀಲಿ && *ಕೀಲಿ && val && *val)
        ret = av_dict_ಗಣ(pm, ಕೀಲಿ, val, flags);
    ಇಲ್ಲದಿದ್ದರೆ
        ret = AVERROR(EINVAL);

    av_freep(&ಕೀಲಿ);
    av_freep(&val);

    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_dict_parse_string(AVDictionary **pm, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str,
                         ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ_val_sep, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಜೋಡಿಗಳು_sep,
                         ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!str)
        ಹಿಂತಿರುಗಿ 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_ಕೀಲಿ | AV_DICT_DONT_STRDUP_VAL);

    ಆಗ (*str) {
        ಆದರೆ ((ret = parse_ಕೀಲಿ_ಮೌಲ್ಯ_pair(pm, &str, ಕೀಲಿ_val_sep, ಜೋಡಿಗಳು_sep, flags)) < 0)
            ಹಿಂತಿರುಗಿ ret;

        ಆದರೆ (*str)
            str++;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    ಆದರೆ (m) {
        ಆಗ (m->ಎಣಿಕೆ_2--) {
            av_freep(&m->elems[m->ಎಣಿಕೆ_2].ಕೀಲಿ);
            av_freep(&m->elems[m->ಎಣಿಕೆ_2].ಮೌಲ್ಯ);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

ಪೂರ್ಣಾಂಕ av_dict_copy(AVDictionary **dst, ಸ್ಥಿರಾಂಕ AVDictionary *src, ಪೂರ್ಣಾಂಕ flags)
{
    ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *t = ಖಾಲಿ;

    ಆದರೆ (!*dst && src && src->ಎಣಿಕೆ_2 && !src->duplicate_ಕೀಲಿಗಳು &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(ಗಾತ್ರ(*m));
        ಆದರೆ (!m)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        m->elems = av_calloc(src->ಎಣಿಕೆ_2, ಗಾತ್ರ(*m->elems));
        ಆದರೆ (!m->elems) {
            av_free(m);
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
        *dst = m;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < src->ಎಣಿಕೆ_2; i++) {
            m->elems[i].ಕೀಲಿ   = av_strdup(src->elems[i].ಕೀಲಿ);
            m->elems[i].ಮೌಲ್ಯ = av_strdup(src->elems[i].ಮೌಲ್ಯ);
            m->ಎಣಿಕೆ_2++;
            ಆದರೆ (!m->elems[i].ಕೀಲಿ || !m->elems[i].ಮೌಲ್ಯ) {
                av_dict_free(dst);
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            }
        }
        ಹಿಂತಿರುಗಿ 0;
    }

    ಆಗ ((t = av_dict_iterate(src, t))) {
        ಪೂರ್ಣಾಂಕ ret = av_dict_ಗಣ(dst, t->ಕೀಲಿ, t->ಮೌಲ್ಯ, flags);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_dict_get_string(ಸ್ಥಿರಾಂಕ AVDictionary *m, ಅಕ್ಷರ **ಬಫರ್,
                       ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಕೀಲಿ_val_sep, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಜೋಡಿಗಳು_sep)
{
    ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *t = ಖಾಲಿ;
    AVBPrint bprint;
    ಪೂರ್ಣಾಂಕ cnt = 0;
    ಅಕ್ಷರ special_chars[] = {ಜೋಡಿಗಳು_sep, ಕೀಲಿ_val_sep, '\0'};

    ಆದರೆ (!ಬಫರ್ || ಜೋಡಿಗಳು_sep == '\0' || ಕೀಲಿ_val_sep == '\0' || ಜೋಡಿಗಳು_sep == ಕೀಲಿ_val_sep ||
        ಜೋಡಿಗಳು_sep == '\\' || ಕೀಲಿ_val_sep == '\\')
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (!av_dict_ಎಣಿಕೆ(m)) {
        *ಬಫರ್ = av_strdup("");
        ಹಿಂತಿರುಗಿ *ಬಫರ್ ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_ಗಾತ್ರ_UNLIMITED);
    ಆಗ ((t = av_dict_iterate(m, t))) {
        ಆದರೆ (cnt++)
            av_bprint_append_ದತ್ತಾಂಶ(&bprint, &ಜೋಡಿಗಳು_sep, 1);
        av_bprint_escape(&bprint, t->ಕೀಲಿ, special_chars, AV_ESCAPE_ಬಹುಲಕ_BACKSLASH, 0);
        av_bprint_append_ದತ್ತಾಂಶ(&bprint, &ಕೀಲಿ_val_sep, 1);
        av_bprint_escape(&bprint, t->ಮೌಲ್ಯ, special_chars, AV_ESCAPE_ಬಹುಲಕ_BACKSLASH, 0);
    }
    ಹಿಂತಿರುಗಿ av_bprint_finalize(&bprint, ಬಫರ್);
}
