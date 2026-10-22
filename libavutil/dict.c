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
    صحيح شمېر;
    AVDictionary_ثبت *elems;
    صحيح duplicate_کلیګانې;
};

صحيح av_dict_شمېر(ثابت AVDictionary *m)
{
    أرجع m ? m->شمېر : 0;
}

ثابت AVDictionary_ثبت *av_dict_iterate(ثابت AVDictionary *m,
                                         ثابت AVDictionary_ثبت *prev)
{
    صحيح i = 0;

    إذا (!m)
        أرجع عدم;

    إذا (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    إذا (i >= m->شمېر)
        أرجع عدم;

    أرجع &m->elems[i];
}

AVDictionary_ثبت *av_dict_get(ثابت AVDictionary *m, ثابت حرف *کلی,
                               ثابت AVDictionary_ثبت *prev, صحيح flags)
{
    ثابت AVDictionary_ثبت *ثبت = prev;
    بینښه صحيح j;

    إذا (!کلی)
        أرجع عدم;

    طالما ((ثبت = av_dict_iterate(m, ثبت))) {
        ثابت حرف *s = ثبت->کلی;
        إذا (flags & AV_DICT_سمون_CASE)
            لكل (j = 0; s[j] == کلی[j] && کلی[j]; j++)
                ;
        وإلا
            لكل (j = 0; av_toupper(s[j]) == av_toupper(کلی[j]) && کلی[j]; j++)
                ;
        إذا (کلی[j])
            استمر;
        إذا (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            استمر;
        أرجع (AVDictionary_ثبت *)ثبت;
    }
    أرجع عدم;
}

صحيح av_dict_سېټ(AVDictionary **pm, ثابت حرف *کلی, ثابت حرف *ارزښت,
                صحيح flags)
{
    AVDictionary *m = *pm;
    AVDictionary_ثبت *نښان = عدم;
    حرف *copy_کلی = عدم, *copy_ارزښت = عدم;
    صحيح err;

    إذا (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_ارزښت = (فراغ *)ارزښت;
    وإلا إذا (ارزښت)
        copy_ارزښت = av_strdup(ارزښت);
    إذا (!کلی) {
        err = AVERROR(EINVAL);
        اذهب err_بهر;
    }
    إذا (flags & AV_DICT_DONT_STRDUP_کلی)
        copy_کلی = (فراغ *)کلی;
    وإلا
        copy_کلی = av_strdup(کلی);
    إذا (!copy_کلی || (ارزښت && !copy_ارزښت))
        اذهب enomem;

    إذا (!(flags & AV_DICT_MULTIKEY)) {
        نښان = av_dict_get(m, کلی, عدم, flags);
    } وإلا إذا (flags & AV_DICT_DEDUP) {
        طالما ((نښان = av_dict_get(m, کلی, نښان, flags))) {
            إذا ((!ارزښت && !نښان->ارزښت) ||
                (ارزښت && نښان->ارزښت && !strcmp(ارزښت, نښان->ارزښت))) {
                av_free(copy_کلی);
                av_free(copy_ارزښت);
                أرجع 0;
            }
        }
    }
    إذا (!m)
        m = *pm = av_mallocz(حجم(*m));
    إذا (!m)
        اذهب enomem;

    إذا (نښان) {
        إذا (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_کلی);
            av_free(copy_ارزښت);
            أرجع 0;
        }
        إذا (copy_ارزښت && flags & AV_DICT_APPEND) {
            size_t oldlen = مزي_اوږدوالی(نښان->ارزښت);
            size_t new_part_len = مزي_اوږدوالی(copy_ارزښت);
            size_t len = oldlen + new_part_len + 1;
            حرف *newval = av_realloc(نښان->ارزښت, len);
            إذا (!newval)
                اذهب enomem;
            حافظه_نقل(newval + oldlen, copy_ارزښت, new_part_len + 1);
            av_freep(&copy_ارزښت);
            copy_ارزښت = newval;
        } وإلا
            av_free(نښان->ارزښت);
        av_free(نښان->کلی);
        *نښان = m->elems[--m->شمېر];
    } وإلا إذا (copy_ارزښت) {
        AVDictionary_ثبت *tmp = av_realloc_array(m->elems,
                                                  m->شمېر + 1, حجم(*m->elems));
        إذا (!tmp)
            اذهب enomem;
        m->elems = tmp;
    }
    إذا (copy_ارزښت) {
        m->elems[m->شمېر].کلی = copy_کلی;
        m->elems[m->شمېر].ارزښت = copy_ارزښت;
        m->شمېر++;
        إذا (flags & (AV_DICT_سمون_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_کلیګانې = 1;
    } وإلا {
        err = 0;
        اذهب پای_ټکی;
    }

    أرجع 0;

enomem:
    err = AVERROR(ENOMEM);
err_بهر:
    av_free(copy_ارزښت);
پای_ټکی:
    إذا (m && !m->شمېر) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_کلی);
    أرجع err;
}

صحيح av_dict_سېټ_int(AVDictionary **pm, ثابت حرف *کلی, int64_t ارزښت,
                صحيح flags)
{
    حرف valuestr[22];
    snprintf(valuestr, حجم(valuestr), "%"PRId64, ارزښت);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    أرجع av_dict_سېټ(pm, کلی, valuestr, flags);
}

ساكن صحيح parse_کلی_ارزښت_pair(AVDictionary **pm, ثابت حرف **buf,
                                ثابت حرف *کلی_val_sep, ثابت حرف *جوړې_sep,
                                صحيح flags)
{
    حرف *کلی = av_get_token(buf, کلی_val_sep);
    حرف *val = عدم;
    صحيح ret;

    إذا (کلی && *کلی && strspn(*buf, کلی_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, جوړې_sep);
    }

    إذا (کلی && *کلی && val && *val)
        ret = av_dict_سېټ(pm, کلی, val, flags);
    وإلا
        ret = AVERROR(EINVAL);

    av_freep(&کلی);
    av_freep(&val);

    أرجع ret;
}

صحيح av_dict_parse_string(AVDictionary **pm, ثابت حرف *str,
                         ثابت حرف *کلی_val_sep, ثابت حرف *جوړې_sep,
                         صحيح flags)
{
    صحيح ret;

    إذا (!str)
        أرجع 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_کلی | AV_DICT_DONT_STRDUP_VAL);

    طالما (*str) {
        إذا ((ret = parse_کلی_ارزښت_pair(pm, &str, کلی_val_sep, جوړې_sep, flags)) < 0)
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
        طالما (m->شمېر--) {
            av_freep(&m->elems[m->شمېر].کلی);
            av_freep(&m->elems[m->شمېر].ارزښت);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

صحيح av_dict_copy(AVDictionary **dst, ثابت AVDictionary *src, صحيح flags)
{
    ثابت AVDictionary_ثبت *t = عدم;

    إذا (!*dst && src && src->شمېر && !src->duplicate_کلیګانې &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(حجم(*m));
        إذا (!m)
            أرجع AVERROR(ENOMEM);
        m->elems = av_calloc(src->شمېر, حجم(*m->elems));
        إذا (!m->elems) {
            av_free(m);
            أرجع AVERROR(ENOMEM);
        }
        *dst = m;
        لكل (صحيح i = 0; i < src->شمېر; i++) {
            m->elems[i].کلی   = av_strdup(src->elems[i].کلی);
            m->elems[i].ارزښت = av_strdup(src->elems[i].ارزښت);
            m->شمېر++;
            إذا (!m->elems[i].کلی || !m->elems[i].ارزښت) {
                av_dict_free(dst);
                أرجع AVERROR(ENOMEM);
            }
        }
        أرجع 0;
    }

    طالما ((t = av_dict_iterate(src, t))) {
        صحيح ret = av_dict_سېټ(dst, t->کلی, t->ارزښت, flags);
        إذا (ret < 0)
            أرجع ret;
    }

    أرجع 0;
}

صحيح av_dict_get_string(ثابت AVDictionary *m, حرف **بفر,
                       ثابت حرف کلی_val_sep, ثابت حرف جوړې_sep)
{
    ثابت AVDictionary_ثبت *t = عدم;
    AVBPrint bprint;
    صحيح cnt = 0;
    حرف special_chars[] = {جوړې_sep, کلی_val_sep, '\0'};

    إذا (!بفر || جوړې_sep == '\0' || کلی_val_sep == '\0' || جوړې_sep == کلی_val_sep ||
        جوړې_sep == '\\' || کلی_val_sep == '\\')
        أرجع AVERROR(EINVAL);

    إذا (!av_dict_شمېر(m)) {
        *بفر = av_strdup("");
        أرجع *بفر ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_اندازه_UNLIMITED);
    طالما ((t = av_dict_iterate(m, t))) {
        إذا (cnt++)
            av_bprint_append_معلومات(&bprint, &جوړې_sep, 1);
        av_bprint_escape(&bprint, t->کلی, special_chars, AV_ESCAPE_ډېرپېښ_BACKSLASH, 0);
        av_bprint_append_معلومات(&bprint, &کلی_val_sep, 1);
        av_bprint_escape(&bprint, t->ارزښت, special_chars, AV_ESCAPE_ډېرپېښ_BACKSLASH, 0);
    }
    أرجع av_bprint_finalize(&bprint, بفر);
}
