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
    صحيح تعداد_2;
    AVDictionaryEntry *elems;
    صحيح duplicate_مفاتيح;
};

صحيح av_dict_تعداد(ثابت AVDictionary *m)
{
    إرجاع m ? m->تعداد_2 : 0;
}

ثابت AVDictionaryEntry *av_dict_iterate(ثابت AVDictionary *m,
                                         ثابت AVDictionaryEntry *prev)
{
    صحيح i = 0;

    إذا (!m)
        إرجاع عدم;

    إذا (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    إذا (i >= m->تعداد_2)
        إرجاع عدم;

    إرجاع &m->elems[i];
}

AVDictionaryEntry *av_dict_get(ثابت AVDictionary *m, ثابت حرف *مفتاح,
                               ثابت AVDictionaryEntry *prev, صحيح flags)
{
    ثابت AVDictionaryEntry *entry = prev;
    unsigned صحيح j;

    إذا (!مفتاح)
        إرجاع عدم;

    بينما ((entry = av_dict_iterate(m, entry))) {
        ثابت حرف *s = entry->مفتاح;
        إذا (flags & AV_DICT_MATCH_CASE)
            لكل (j = 0; s[j] == مفتاح[j] && مفتاح[j]; j++)
                ;
        وإلا
            لكل (j = 0; av_toupper(s[j]) == av_toupper(مفتاح[j]) && مفتاح[j]; j++)
                ;
        إذا (مفتاح[j])
            استمر;
        إذا (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            استمر;
        إرجاع (AVDictionaryEntry *)entry;
    }
    إرجاع عدم;
}

صحيح av_dict_set(AVDictionary **pm, ثابت حرف *مفتاح, ثابت حرف *قيمة,
                صحيح flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = عدم;
    حرف *copy_مفتاح = عدم, *copy_قيمة = عدم;
    صحيح err;

    إذا (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_قيمة = (فراغ *)قيمة;
    وإلا إذا (قيمة)
        copy_قيمة = av_strdup(قيمة);
    إذا (!مفتاح) {
        err = AVERROR(EINVAL);
        اذهب err_out;
    }
    إذا (flags & AV_DICT_DONT_STRDUP_مفتاح)
        copy_مفتاح = (فراغ *)مفتاح;
    وإلا
        copy_مفتاح = av_strdup(مفتاح);
    إذا (!copy_مفتاح || (قيمة && !copy_قيمة))
        اذهب enomem;

    إذا (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, مفتاح, عدم, flags);
    } وإلا إذا (flags & AV_DICT_DEDUP) {
        بينما ((tag = av_dict_get(m, مفتاح, tag, flags))) {
            إذا ((!قيمة && !tag->قيمة) ||
                (قيمة && tag->قيمة && !strcmp(قيمة, tag->قيمة))) {
                av_free(copy_مفتاح);
                av_free(copy_قيمة);
                إرجاع 0;
            }
        }
    }
    إذا (!m)
        m = *pm = av_mallocz(حجم(*m));
    إذا (!m)
        اذهب enomem;

    إذا (tag) {
        إذا (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_مفتاح);
            av_free(copy_قيمة);
            إرجاع 0;
        }
        إذا (copy_قيمة && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->قيمة);
            size_t new_part_len = strlen(copy_قيمة);
            size_t len = oldlen + new_part_len + 1;
            حرف *newval = av_realloc(tag->قيمة, len);
            إذا (!newval)
                اذهب enomem;
            memcpy(newval + oldlen, copy_قيمة, new_part_len + 1);
            av_freep(&copy_قيمة);
            copy_قيمة = newval;
        } وإلا
            av_free(tag->قيمة);
        av_free(tag->مفتاح);
        *tag = m->elems[--m->تعداد_2];
    } وإلا إذا (copy_قيمة) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->تعداد_2 + 1, حجم(*m->elems));
        إذا (!tmp)
            اذهب enomem;
        m->elems = tmp;
    }
    إذا (copy_قيمة) {
        m->elems[m->تعداد_2].مفتاح = copy_مفتاح;
        m->elems[m->تعداد_2].قيمة = copy_قيمة;
        m->تعداد_2++;
        إذا (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_مفاتيح = 1;
    } وإلا {
        err = 0;
        اذهب end;
    }

    إرجاع 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_قيمة);
end:
    إذا (m && !m->تعداد_2) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_مفتاح);
    إرجاع err;
}

صحيح av_dict_set_int(AVDictionary **pm, ثابت حرف *مفتاح, int64_t قيمة,
                صحيح flags)
{
    حرف valuestr[22];
    snprintf(valuestr, حجم(valuestr), "%"PRId64, قيمة);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    إرجاع av_dict_set(pm, مفتاح, valuestr, flags);
}

ساكن صحيح parse_مفتاح_قيمة_pair(AVDictionary **pm, ثابت حرف **buf,
                                ثابت حرف *مفتاح_val_sep, ثابت حرف *pairs_sep,
                                صحيح flags)
{
    حرف *مفتاح = av_get_token(buf, مفتاح_val_sep);
    حرف *val = عدم;
    صحيح ret;

    إذا (مفتاح && *مفتاح && strspn(*buf, مفتاح_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    إذا (مفتاح && *مفتاح && val && *val)
        ret = av_dict_set(pm, مفتاح, val, flags);
    وإلا
        ret = AVERROR(EINVAL);

    av_freep(&مفتاح);
    av_freep(&val);

    إرجاع ret;
}

صحيح av_dict_parse_string(AVDictionary **pm, ثابت حرف *str,
                         ثابت حرف *مفتاح_val_sep, ثابت حرف *pairs_sep,
                         صحيح flags)
{
    صحيح ret;

    إذا (!str)
        إرجاع 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_مفتاح | AV_DICT_DONT_STRDUP_VAL);

    بينما (*str) {
        إذا ((ret = parse_مفتاح_قيمة_pair(pm, &str, مفتاح_val_sep, pairs_sep, flags)) < 0)
            إرجاع ret;

        إذا (*str)
            str++;
    }

    إرجاع 0;
}

فراغ av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    إذا (m) {
        بينما (m->تعداد_2--) {
            av_freep(&m->elems[m->تعداد_2].مفتاح);
            av_freep(&m->elems[m->تعداد_2].قيمة);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

صحيح av_dict_copy(AVDictionary **dst, ثابت AVDictionary *src, صحيح flags)
{
    ثابت AVDictionaryEntry *t = عدم;

    إذا (!*dst && src && src->تعداد_2 && !src->duplicate_مفاتيح &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(حجم(*m));
        إذا (!m)
            إرجاع AVERROR(ENOMEM);
        m->elems = av_calloc(src->تعداد_2, حجم(*m->elems));
        إذا (!m->elems) {
            av_free(m);
            إرجاع AVERROR(ENOMEM);
        }
        *dst = m;
        لكل (صحيح i = 0; i < src->تعداد_2; i++) {
            m->elems[i].مفتاح   = av_strdup(src->elems[i].مفتاح);
            m->elems[i].قيمة = av_strdup(src->elems[i].قيمة);
            m->تعداد_2++;
            إذا (!m->elems[i].مفتاح || !m->elems[i].قيمة) {
                av_dict_free(dst);
                إرجاع AVERROR(ENOMEM);
            }
        }
        إرجاع 0;
    }

    بينما ((t = av_dict_iterate(src, t))) {
        صحيح ret = av_dict_set(dst, t->مفتاح, t->قيمة, flags);
        إذا (ret < 0)
            إرجاع ret;
    }

    إرجاع 0;
}

صحيح av_dict_get_string(ثابت AVDictionary *m, حرف **buffer,
                       ثابت حرف مفتاح_val_sep, ثابت حرف pairs_sep)
{
    ثابت AVDictionaryEntry *t = عدم;
    AVBPrint bprint;
    صحيح cnt = 0;
    حرف special_chars[] = {pairs_sep, مفتاح_val_sep, '\0'};

    إذا (!buffer || pairs_sep == '\0' || مفتاح_val_sep == '\0' || pairs_sep == مفتاح_val_sep ||
        pairs_sep == '\\' || مفتاح_val_sep == '\\')
        إرجاع AVERROR(EINVAL);

    إذا (!av_dict_تعداد(m)) {
        *buffer = av_strdup("");
        إرجاع *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    بينما ((t = av_dict_iterate(m, t))) {
        إذا (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->مفتاح, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &مفتاح_val_sep, 1);
        av_bprint_escape(&bprint, t->قيمة, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    إرجاع av_bprint_finalize(&bprint, buffer);
}
