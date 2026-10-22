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
    صحيح ژماردن;
    AVDictionaryEntry *elems;
    صحيح duplicate_کلیلەکان;
};

صحيح av_dict_ژماردن(ثابت AVDictionary *m)
{
    أرجع m ? m->ژماردن : 0;
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
    إذا (i >= m->ژماردن)
        أرجع عدم;

    أرجع &m->elems[i];
}

AVDictionaryEntry *av_dict_get(ثابت AVDictionary *m, ثابت حرف *کلیل,
                               ثابت AVDictionaryEntry *prev, صحيح flags)
{
    ثابت AVDictionaryEntry *entry = prev;
    unsigned صحيح j;

    إذا (!کلیل)
        أرجع عدم;

    طالما ((entry = av_dict_iterate(m, entry))) {
        ثابت حرف *s = entry->کلیل;
        إذا (flags & AV_DICT_MATCH_CASE)
            لكل (j = 0; s[j] == کلیل[j] && کلیل[j]; j++)
                ;
        وإلا
            لكل (j = 0; av_toupper(s[j]) == av_toupper(کلیل[j]) && کلیل[j]; j++)
                ;
        إذا (کلیل[j])
            استمر;
        إذا (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            استمر;
        أرجع (AVDictionaryEntry *)entry;
    }
    أرجع عدم;
}

صحيح av_dict_set(AVDictionary **pm, ثابت حرف *کلیل, ثابت حرف *بەها,
                صحيح flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = عدم;
    حرف *copy_کلیل = عدم, *copy_بەها = عدم;
    صحيح err;

    إذا (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_بەها = (فراغ *)بەها;
    وإلا إذا (بەها)
        copy_بەها = av_strdup(بەها);
    إذا (!کلیل) {
        err = AVERROR(EINVAL);
        اذهب err_out;
    }
    إذا (flags & AV_DICT_DONT_STRDUP_کلیل)
        copy_کلیل = (فراغ *)کلیل;
    وإلا
        copy_کلیل = av_strdup(کلیل);
    إذا (!copy_کلیل || (بەها && !copy_بەها))
        اذهب enomem;

    إذا (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, کلیل, عدم, flags);
    } وإلا إذا (flags & AV_DICT_DEDUP) {
        طالما ((tag = av_dict_get(m, کلیل, tag, flags))) {
            إذا ((!بەها && !tag->بەها) ||
                (بەها && tag->بەها && !strcmp(بەها, tag->بەها))) {
                av_free(copy_کلیل);
                av_free(copy_بەها);
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
            av_free(copy_کلیل);
            av_free(copy_بەها);
            أرجع 0;
        }
        إذا (copy_بەها && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->بەها);
            size_t new_part_len = strlen(copy_بەها);
            size_t len = oldlen + new_part_len + 1;
            حرف *newval = av_realloc(tag->بەها, len);
            إذا (!newval)
                اذهب enomem;
            memcpy(newval + oldlen, copy_بەها, new_part_len + 1);
            av_freep(&copy_بەها);
            copy_بەها = newval;
        } وإلا
            av_free(tag->بەها);
        av_free(tag->کلیل);
        *tag = m->elems[--m->ژماردن];
    } وإلا إذا (copy_بەها) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->ژماردن + 1, حجم(*m->elems));
        إذا (!tmp)
            اذهب enomem;
        m->elems = tmp;
    }
    إذا (copy_بەها) {
        m->elems[m->ژماردن].کلیل = copy_کلیل;
        m->elems[m->ژماردن].بەها = copy_بەها;
        m->ژماردن++;
        إذا (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_کلیلەکان = 1;
    } وإلا {
        err = 0;
        اذهب end;
    }

    أرجع 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_بەها);
end:
    إذا (m && !m->ژماردن) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_کلیل);
    أرجع err;
}

صحيح av_dict_set_int(AVDictionary **pm, ثابت حرف *کلیل, int64_t بەها,
                صحيح flags)
{
    حرف valuestr[22];
    snprintf(valuestr, حجم(valuestr), "%"PRId64, بەها);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    أرجع av_dict_set(pm, کلیل, valuestr, flags);
}

ساكن صحيح parse_کلیل_بەها_pair(AVDictionary **pm, ثابت حرف **buf,
                                ثابت حرف *کلیل_val_sep, ثابت حرف *pairs_sep,
                                صحيح flags)
{
    حرف *کلیل = av_get_token(buf, کلیل_val_sep);
    حرف *val = عدم;
    صحيح ret;

    إذا (کلیل && *کلیل && strspn(*buf, کلیل_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    إذا (کلیل && *کلیل && val && *val)
        ret = av_dict_set(pm, کلیل, val, flags);
    وإلا
        ret = AVERROR(EINVAL);

    av_freep(&کلیل);
    av_freep(&val);

    أرجع ret;
}

صحيح av_dict_parse_string(AVDictionary **pm, ثابت حرف *str,
                         ثابت حرف *کلیل_val_sep, ثابت حرف *pairs_sep,
                         صحيح flags)
{
    صحيح ret;

    إذا (!str)
        أرجع 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_کلیل | AV_DICT_DONT_STRDUP_VAL);

    طالما (*str) {
        إذا ((ret = parse_کلیل_بەها_pair(pm, &str, کلیل_val_sep, pairs_sep, flags)) < 0)
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
        طالما (m->ژماردن--) {
            av_freep(&m->elems[m->ژماردن].کلیل);
            av_freep(&m->elems[m->ژماردن].بەها);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

صحيح av_dict_copy(AVDictionary **dst, ثابت AVDictionary *src, صحيح flags)
{
    ثابت AVDictionaryEntry *t = عدم;

    إذا (!*dst && src && src->ژماردن && !src->duplicate_کلیلەکان &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(حجم(*m));
        إذا (!m)
            أرجع AVERROR(ENOMEM);
        m->elems = av_calloc(src->ژماردن, حجم(*m->elems));
        إذا (!m->elems) {
            av_free(m);
            أرجع AVERROR(ENOMEM);
        }
        *dst = m;
        لكل (صحيح i = 0; i < src->ژماردن; i++) {
            m->elems[i].کلیل   = av_strdup(src->elems[i].کلیل);
            m->elems[i].بەها = av_strdup(src->elems[i].بەها);
            m->ژماردن++;
            إذا (!m->elems[i].کلیل || !m->elems[i].بەها) {
                av_dict_free(dst);
                أرجع AVERROR(ENOMEM);
            }
        }
        أرجع 0;
    }

    طالما ((t = av_dict_iterate(src, t))) {
        صحيح ret = av_dict_set(dst, t->کلیل, t->بەها, flags);
        إذا (ret < 0)
            أرجع ret;
    }

    أرجع 0;
}

صحيح av_dict_get_string(ثابت AVDictionary *m, حرف **buffer,
                       ثابت حرف کلیل_val_sep, ثابت حرف pairs_sep)
{
    ثابت AVDictionaryEntry *t = عدم;
    AVBPrint bprint;
    صحيح cnt = 0;
    حرف special_chars[] = {pairs_sep, کلیل_val_sep, '\0'};

    إذا (!buffer || pairs_sep == '\0' || کلیل_val_sep == '\0' || pairs_sep == کلیل_val_sep ||
        pairs_sep == '\\' || کلیل_val_sep == '\\')
        أرجع AVERROR(EINVAL);

    إذا (!av_dict_ژماردن(m)) {
        *buffer = av_strdup("");
        أرجع *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    طالما ((t = av_dict_iterate(m, t))) {
        إذا (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->کلیل, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &کلیل_val_sep, 1);
        av_bprint_escape(&bprint, t->بەها, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    أرجع av_bprint_finalize(&bprint, buffer);
}
