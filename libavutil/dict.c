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
    صحيح گنتی;
    AVDictionary_اندراج *elems;
    صحيح duplicate_کلیدیں;
};

صحيح av_dict_گنتی(ثابت AVDictionary *m)
{
    أرجع m ? m->گنتی : 0;
}

ثابت AVDictionary_اندراج *av_dict_iterate(ثابت AVDictionary *m,
                                         ثابت AVDictionary_اندراج *prev)
{
    صحيح i = 0;

    إذا (!m)
        أرجع عدم;

    إذا (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    إذا (i >= m->گنتی)
        أرجع عدم;

    أرجع &m->elems[i];
}

AVDictionary_اندراج *av_dict_get(ثابت AVDictionary *m, ثابت حرف *کلید,
                               ثابت AVDictionary_اندراج *prev, صحيح flags)
{
    ثابت AVDictionary_اندراج *اندراج = prev;
    بنانشانی صحيح j;

    إذا (!کلید)
        أرجع عدم;

    طالما ((اندراج = av_dict_iterate(m, اندراج))) {
        ثابت حرف *s = اندراج->کلید;
        إذا (flags & AV_DICT_میل_CASE)
            لكل (j = 0; s[j] == کلید[j] && کلید[j]; j++)
                ;
        وإلا
            لكل (j = 0; av_toupper(s[j]) == av_toupper(کلید[j]) && کلید[j]; j++)
                ;
        إذا (کلید[j])
            استمر;
        إذا (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            استمر;
        أرجع (AVDictionary_اندراج *)اندراج;
    }
    أرجع عدم;
}

صحيح av_dict_سیٹ(AVDictionary **pm, ثابت حرف *کلید, ثابت حرف *قدر,
                صحيح flags)
{
    AVDictionary *m = *pm;
    AVDictionary_اندراج *ٹیگ = عدم;
    حرف *copy_کلید = عدم, *copy_قدر = عدم;
    صحيح err;

    إذا (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_قدر = (فراغ *)قدر;
    وإلا إذا (قدر)
        copy_قدر = av_strdup(قدر);
    إذا (!کلید) {
        err = AVERROR(EINVAL);
        اذهب err_باہرلا;
    }
    إذا (flags & AV_DICT_DONT_STRDUP_کلید)
        copy_کلید = (فراغ *)کلید;
    وإلا
        copy_کلید = av_strdup(کلید);
    إذا (!copy_کلید || (قدر && !copy_قدر))
        اذهب enomem;

    إذا (!(flags & AV_DICT_MULTIKEY)) {
        ٹیگ = av_dict_get(m, کلید, عدم, flags);
    } وإلا إذا (flags & AV_DICT_DEDUP) {
        طالما ((ٹیگ = av_dict_get(m, کلید, ٹیگ, flags))) {
            إذا ((!قدر && !ٹیگ->قدر) ||
                (قدر && ٹیگ->قدر && !strcmp(قدر, ٹیگ->قدر))) {
                av_free(copy_کلید);
                av_free(copy_قدر);
                أرجع 0;
            }
        }
    }
    إذا (!m)
        m = *pm = av_mallocz(حجم(*m));
    إذا (!m)
        اذهب enomem;

    إذا (ٹیگ) {
        إذا (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_کلید);
            av_free(copy_قدر);
            أرجع 0;
        }
        إذا (copy_قدر && flags & AV_DICT_APPEND) {
            size_t oldlen = لڑی_لمبائی(ٹیگ->قدر);
            size_t new_part_len = لڑی_لمبائی(copy_قدر);
            size_t len = oldlen + new_part_len + 1;
            حرف *newval = av_realloc(ٹیگ->قدر, len);
            إذا (!newval)
                اذهب enomem;
            حافظہ_نقل(newval + oldlen, copy_قدر, new_part_len + 1);
            av_freep(&copy_قدر);
            copy_قدر = newval;
        } وإلا
            av_free(ٹیگ->قدر);
        av_free(ٹیگ->کلید);
        *ٹیگ = m->elems[--m->گنتی];
    } وإلا إذا (copy_قدر) {
        AVDictionary_اندراج *tmp = av_realloc_array(m->elems,
                                                  m->گنتی + 1, حجم(*m->elems));
        إذا (!tmp)
            اذهب enomem;
        m->elems = tmp;
    }
    إذا (copy_قدر) {
        m->elems[m->گنتی].کلید = copy_کلید;
        m->elems[m->گنتی].قدر = copy_قدر;
        m->گنتی++;
        إذا (flags & (AV_DICT_میل_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_کلیدیں = 1;
    } وإلا {
        err = 0;
        اذهب سرا;
    }

    أرجع 0;

enomem:
    err = AVERROR(ENOMEM);
err_باہرلا:
    av_free(copy_قدر);
سرا:
    إذا (m && !m->گنتی) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_کلید);
    أرجع err;
}

صحيح av_dict_سیٹ_int(AVDictionary **pm, ثابت حرف *کلید, int64_t قدر,
                صحيح flags)
{
    حرف valuestr[22];
    snprintf(valuestr, حجم(valuestr), "%"PRId64, قدر);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    أرجع av_dict_سیٹ(pm, کلید, valuestr, flags);
}

ساكن صحيح parse_کلید_قدر_pair(AVDictionary **pm, ثابت حرف **buf,
                                ثابت حرف *کلید_val_sep, ثابت حرف *جوڑے_sep,
                                صحيح flags)
{
    حرف *کلید = av_get_token(buf, کلید_val_sep);
    حرف *val = عدم;
    صحيح ret;

    إذا (کلید && *کلید && strspn(*buf, کلید_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, جوڑے_sep);
    }

    إذا (کلید && *کلید && val && *val)
        ret = av_dict_سیٹ(pm, کلید, val, flags);
    وإلا
        ret = AVERROR(EINVAL);

    av_freep(&کلید);
    av_freep(&val);

    أرجع ret;
}

صحيح av_dict_parse_string(AVDictionary **pm, ثابت حرف *str,
                         ثابت حرف *کلید_val_sep, ثابت حرف *جوڑے_sep,
                         صحيح flags)
{
    صحيح ret;

    إذا (!str)
        أرجع 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_کلید | AV_DICT_DONT_STRDUP_VAL);

    طالما (*str) {
        إذا ((ret = parse_کلید_قدر_pair(pm, &str, کلید_val_sep, جوڑے_sep, flags)) < 0)
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
        طالما (m->گنتی--) {
            av_freep(&m->elems[m->گنتی].کلید);
            av_freep(&m->elems[m->گنتی].قدر);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

صحيح av_dict_copy(AVDictionary **dst, ثابت AVDictionary *src, صحيح flags)
{
    ثابت AVDictionary_اندراج *t = عدم;

    إذا (!*dst && src && src->گنتی && !src->duplicate_کلیدیں &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(حجم(*m));
        إذا (!m)
            أرجع AVERROR(ENOMEM);
        m->elems = av_calloc(src->گنتی, حجم(*m->elems));
        إذا (!m->elems) {
            av_free(m);
            أرجع AVERROR(ENOMEM);
        }
        *dst = m;
        لكل (صحيح i = 0; i < src->گنتی; i++) {
            m->elems[i].کلید   = av_strdup(src->elems[i].کلید);
            m->elems[i].قدر = av_strdup(src->elems[i].قدر);
            m->گنتی++;
            إذا (!m->elems[i].کلید || !m->elems[i].قدر) {
                av_dict_free(dst);
                أرجع AVERROR(ENOMEM);
            }
        }
        أرجع 0;
    }

    طالما ((t = av_dict_iterate(src, t))) {
        صحيح ret = av_dict_سیٹ(dst, t->کلید, t->قدر, flags);
        إذا (ret < 0)
            أرجع ret;
    }

    أرجع 0;
}

صحيح av_dict_get_string(ثابت AVDictionary *m, حرف **بفر,
                       ثابت حرف کلید_val_sep, ثابت حرف جوڑے_sep)
{
    ثابت AVDictionary_اندراج *t = عدم;
    AVBPrint bprint;
    صحيح cnt = 0;
    حرف special_chars[] = {جوڑے_sep, کلید_val_sep, '\0'};

    إذا (!بفر || جوڑے_sep == '\0' || کلید_val_sep == '\0' || جوڑے_sep == کلید_val_sep ||
        جوڑے_sep == '\\' || کلید_val_sep == '\\')
        أرجع AVERROR(EINVAL);

    إذا (!av_dict_گنتی(m)) {
        *بفر = av_strdup("");
        أرجع *بفر ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_ناپ_UNLIMITED);
    طالما ((t = av_dict_iterate(m, t))) {
        إذا (cnt++)
            av_bprint_append_انکڑے(&bprint, &جوڑے_sep, 1);
        av_bprint_escape(&bprint, t->کلید, special_chars, AV_ESCAPE_منوال_BACKSLASH, 0);
        av_bprint_append_انکڑے(&bprint, &کلید_val_sep, 1);
        av_bprint_escape(&bprint, t->قدر, special_chars, AV_ESCAPE_منوال_BACKSLASH, 0);
    }
    أرجع av_bprint_finalize(&bprint, بفر);
}
