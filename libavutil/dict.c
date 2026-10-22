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
    صحيح سانى;
    AVDictionaryEntry *elems;
    صحيح duplicate_ئاچقۇچلار;
};

صحيح av_dict_سانى(ثابت AVDictionary *m)
{
    أرجع m ? m->سانى : 0;
}

ثابت AVDictionaryEntry *av_dict_iterate(ثابت AVDictionary *m,
                                         ثابت AVDictionaryEntry *prev)
{
    صحيح i = 0;

    إذا (!m)
        أرجع عدم;

    إذا (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    إذا (i >= m->سانى)
        أرجع عدم;

    أرجع &m->elems[i];
}

AVDictionaryEntry *av_dict_get(ثابت AVDictionary *m, ثابت حرف *ئاچقۇچ,
                               ثابت AVDictionaryEntry *prev, صحيح flags)
{
    ثابت AVDictionaryEntry *entry = prev;
    unsigned صحيح j;

    إذا (!ئاچقۇچ)
        أرجع عدم;

    طالما ((entry = av_dict_iterate(m, entry))) {
        ثابت حرف *s = entry->ئاچقۇچ;
        إذا (flags & AV_DICT_MATCH_CASE)
            لكل (j = 0; s[j] == ئاچقۇچ[j] && ئاچقۇچ[j]; j++)
                ;
        وإلا
            لكل (j = 0; av_toupper(s[j]) == av_toupper(ئاچقۇچ[j]) && ئاچقۇچ[j]; j++)
                ;
        إذا (ئاچقۇچ[j])
            استمر;
        إذا (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            استمر;
        أرجع (AVDictionaryEntry *)entry;
    }
    أرجع عدم;
}

صحيح av_dict_set(AVDictionary **pm, ثابت حرف *ئاچقۇچ, ثابت حرف *قىممەت,
                صحيح flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = عدم;
    حرف *copy_ئاچقۇچ = عدم, *copy_قىممەت = عدم;
    صحيح err;

    إذا (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_قىممەت = (فراغ *)قىممەت;
    وإلا إذا (قىممەت)
        copy_قىممەت = av_strdup(قىممەت);
    إذا (!ئاچقۇچ) {
        err = AVERROR(EINVAL);
        اذهب err_out;
    }
    إذا (flags & AV_DICT_DONT_STRDUP_ئاچقۇچ)
        copy_ئاچقۇچ = (فراغ *)ئاچقۇچ;
    وإلا
        copy_ئاچقۇچ = av_strdup(ئاچقۇچ);
    إذا (!copy_ئاچقۇچ || (قىممەت && !copy_قىممەت))
        اذهب enomem;

    إذا (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, ئاچقۇچ, عدم, flags);
    } وإلا إذا (flags & AV_DICT_DEDUP) {
        طالما ((tag = av_dict_get(m, ئاچقۇچ, tag, flags))) {
            إذا ((!قىممەت && !tag->قىممەت) ||
                (قىممەت && tag->قىممەت && !strcmp(قىممەت, tag->قىممەت))) {
                av_free(copy_ئاچقۇچ);
                av_free(copy_قىممەت);
                أرجع 0;
            }
        }
    }
    إذا (!m)
        m = *pm = av_mallocz(حجم(*m));
    إذا (!m)
        اذهب enomem;

    إذا (tag) {
        إذا (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_ئاچقۇچ);
            av_free(copy_قىممەت);
            أرجع 0;
        }
        إذا (copy_قىممەت && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->قىممەت);
            size_t new_part_len = strlen(copy_قىممەت);
            size_t len = oldlen + new_part_len + 1;
            حرف *newval = av_realloc(tag->قىممەت, len);
            إذا (!newval)
                اذهب enomem;
            memcpy(newval + oldlen, copy_قىممەت, new_part_len + 1);
            av_freep(&copy_قىممەت);
            copy_قىممەت = newval;
        } وإلا
            av_free(tag->قىممەت);
        av_free(tag->ئاچقۇچ);
        *tag = m->elems[--m->سانى];
    } وإلا إذا (copy_قىممەت) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->سانى + 1, حجم(*m->elems));
        إذا (!tmp)
            اذهب enomem;
        m->elems = tmp;
    }
    إذا (copy_قىممەت) {
        m->elems[m->سانى].ئاچقۇچ = copy_ئاچقۇچ;
        m->elems[m->سانى].قىممەت = copy_قىممەت;
        m->سانى++;
        إذا (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_ئاچقۇچلار = 1;
    } وإلا {
        err = 0;
        اذهب end;
    }

    أرجع 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_قىممەت);
end:
    إذا (m && !m->سانى) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_ئاچقۇچ);
    أرجع err;
}

صحيح av_dict_set_int(AVDictionary **pm, ثابت حرف *ئاچقۇچ, int64_t قىممەت,
                صحيح flags)
{
    حرف valuestr[22];
    snprintf(valuestr, حجم(valuestr), "%"PRId64, قىممەت);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    أرجع av_dict_set(pm, ئاچقۇچ, valuestr, flags);
}

ساكن صحيح parse_ئاچقۇچ_قىممەت_pair(AVDictionary **pm, ثابت حرف **buf,
                                ثابت حرف *ئاچقۇچ_val_sep, ثابت حرف *pairs_sep,
                                صحيح flags)
{
    حرف *ئاچقۇچ = av_get_token(buf, ئاچقۇچ_val_sep);
    حرف *val = عدم;
    صحيح ret;

    إذا (ئاچقۇچ && *ئاچقۇچ && strspn(*buf, ئاچقۇچ_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    إذا (ئاچقۇچ && *ئاچقۇچ && val && *val)
        ret = av_dict_set(pm, ئاچقۇچ, val, flags);
    وإلا
        ret = AVERROR(EINVAL);

    av_freep(&ئاچقۇچ);
    av_freep(&val);

    أرجع ret;
}

صحيح av_dict_parse_string(AVDictionary **pm, ثابت حرف *str,
                         ثابت حرف *ئاچقۇچ_val_sep, ثابت حرف *pairs_sep,
                         صحيح flags)
{
    صحيح ret;

    إذا (!str)
        أرجع 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_ئاچقۇچ | AV_DICT_DONT_STRDUP_VAL);

    طالما (*str) {
        إذا ((ret = parse_ئاچقۇچ_قىممەت_pair(pm, &str, ئاچقۇچ_val_sep, pairs_sep, flags)) < 0)
            أرجع ret;

        إذا (*str)
            str++;
    }

    أرجع 0;
}

فراغ av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    إذا (m) {
        طالما (m->سانى--) {
            av_freep(&m->elems[m->سانى].ئاچقۇچ);
            av_freep(&m->elems[m->سانى].قىممەت);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

صحيح av_dict_copy(AVDictionary **dst, ثابت AVDictionary *src, صحيح flags)
{
    ثابت AVDictionaryEntry *t = عدم;

    إذا (!*dst && src && src->سانى && !src->duplicate_ئاچقۇچلار &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(حجم(*m));
        إذا (!m)
            أرجع AVERROR(ENOMEM);
        m->elems = av_calloc(src->سانى, حجم(*m->elems));
        إذا (!m->elems) {
            av_free(m);
            أرجع AVERROR(ENOMEM);
        }
        *dst = m;
        لكل (صحيح i = 0; i < src->سانى; i++) {
            m->elems[i].ئاچقۇچ   = av_strdup(src->elems[i].ئاچقۇچ);
            m->elems[i].قىممەت = av_strdup(src->elems[i].قىممەت);
            m->سانى++;
            إذا (!m->elems[i].ئاچقۇچ || !m->elems[i].قىممەت) {
                av_dict_free(dst);
                أرجع AVERROR(ENOMEM);
            }
        }
        أرجع 0;
    }

    طالما ((t = av_dict_iterate(src, t))) {
        صحيح ret = av_dict_set(dst, t->ئاچقۇچ, t->قىممەت, flags);
        إذا (ret < 0)
            أرجع ret;
    }

    أرجع 0;
}

صحيح av_dict_get_string(ثابت AVDictionary *m, حرف **buffer,
                       ثابت حرف ئاچقۇچ_val_sep, ثابت حرف pairs_sep)
{
    ثابت AVDictionaryEntry *t = عدم;
    AVBPrint bprint;
    صحيح cnt = 0;
    حرف special_chars[] = {pairs_sep, ئاچقۇچ_val_sep, '\0'};

    إذا (!buffer || pairs_sep == '\0' || ئاچقۇچ_val_sep == '\0' || pairs_sep == ئاچقۇچ_val_sep ||
        pairs_sep == '\\' || ئاچقۇچ_val_sep == '\\')
        أرجع AVERROR(EINVAL);

    إذا (!av_dict_سانى(m)) {
        *buffer = av_strdup("");
        أرجع *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    طالما ((t = av_dict_iterate(m, t))) {
        إذا (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->ئاچقۇچ, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &ئاچقۇچ_val_sep, 1);
        av_bprint_escape(&bprint, t->قىممەت, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    أرجع av_bprint_finalize(&bprint, buffer);
}
