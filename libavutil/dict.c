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
    صحيح شمار;
    AVDictionary_مدخل *elems;
    صحيح duplicate_کلیدها;
};

صحيح av_dict_شمار(ثابت AVDictionary *m)
{
    أرجع m ? m->شمار : 0;
}

ثابت AVDictionary_مدخل *av_dict_iterate(ثابت AVDictionary *m,
                                         ثابت AVDictionary_مدخل *prev)
{
    صحيح i = 0;

    إذا (!m)
        أرجع عدم;

    إذا (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    إذا (i >= m->شمار)
        أرجع عدم;

    أرجع &m->elems[i];
}

AVDictionary_مدخل *av_dict_get(ثابت AVDictionary *m, ثابت حرف *کلید,
                               ثابت AVDictionary_مدخل *prev, صحيح flags)
{
    ثابت AVDictionary_مدخل *مدخل = prev;
    بیعلامت صحيح j;

    إذا (!کلید)
        أرجع عدم;

    طالما ((مدخل = av_dict_iterate(m, مدخل))) {
        ثابت حرف *s = مدخل->کلید;
        إذا (flags & AV_DICT_تطابق_CASE)
            لكل (j = 0; s[j] == کلید[j] && کلید[j]; j++)
                ;
        وإلا
            لكل (j = 0; av_toupper(s[j]) == av_toupper(کلید[j]) && کلید[j]; j++)
                ;
        إذا (کلید[j])
            استمر;
        إذا (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            استمر;
        أرجع (AVDictionary_مدخل *)مدخل;
    }
    أرجع عدم;
}

صحيح av_dict_مجموعه(AVDictionary **pm, ثابت حرف *کلید, ثابت حرف *مقدار,
                صحيح flags)
{
    AVDictionary *m = *pm;
    AVDictionary_مدخل *برچسب = عدم;
    حرف *copy_کلید = عدم, *copy_مقدار = عدم;
    صحيح err;

    إذا (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_مقدار = (فراغ *)مقدار;
    وإلا إذا (مقدار)
        copy_مقدار = av_strdup(مقدار);
    إذا (!کلید) {
        err = AVERROR(EINVAL);
        اذهب err_بیرون;
    }
    إذا (flags & AV_DICT_DONT_STRDUP_کلید)
        copy_کلید = (فراغ *)کلید;
    وإلا
        copy_کلید = av_strdup(کلید);
    إذا (!copy_کلید || (مقدار && !copy_مقدار))
        اذهب enomem;

    إذا (!(flags & AV_DICT_MULTIKEY)) {
        برچسب = av_dict_get(m, کلید, عدم, flags);
    } وإلا إذا (flags & AV_DICT_DEDUP) {
        طالما ((برچسب = av_dict_get(m, کلید, برچسب, flags))) {
            إذا ((!مقدار && !برچسب->مقدار) ||
                (مقدار && برچسب->مقدار && !strcmp(مقدار, برچسب->مقدار))) {
                av_free(copy_کلید);
                av_free(copy_مقدار);
                أرجع 0;
            }
        }
    }
    إذا (!m)
        m = *pm = av_mallocz(حجم(*m));
    إذا (!m)
        اذهب enomem;

    إذا (برچسب) {
        إذا (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_کلید);
            av_free(copy_مقدار);
            أرجع 0;
        }
        إذا (copy_مقدار && flags & AV_DICT_APPEND) {
            size_t oldlen = طول_رشته(برچسب->مقدار);
            size_t new_part_len = طول_رشته(copy_مقدار);
            size_t len = oldlen + new_part_len + 1;
            حرف *newval = av_realloc(برچسب->مقدار, len);
            إذا (!newval)
                اذهب enomem;
            کپی_حافظه(newval + oldlen, copy_مقدار, new_part_len + 1);
            av_freep(&copy_مقدار);
            copy_مقدار = newval;
        } وإلا
            av_free(برچسب->مقدار);
        av_free(برچسب->کلید);
        *برچسب = m->elems[--m->شمار];
    } وإلا إذا (copy_مقدار) {
        AVDictionary_مدخل *tmp = av_realloc_array(m->elems,
                                                  m->شمار + 1, حجم(*m->elems));
        إذا (!tmp)
            اذهب enomem;
        m->elems = tmp;
    }
    إذا (copy_مقدار) {
        m->elems[m->شمار].کلید = copy_کلید;
        m->elems[m->شمار].مقدار = copy_مقدار;
        m->شمار++;
        إذا (flags & (AV_DICT_تطابق_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_کلیدها = 1;
    } وإلا {
        err = 0;
        اذهب انتها;
    }

    أرجع 0;

enomem:
    err = AVERROR(ENOMEM);
err_بیرون:
    av_free(copy_مقدار);
انتها:
    إذا (m && !m->شمار) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_کلید);
    أرجع err;
}

صحيح av_dict_مجموعه_int(AVDictionary **pm, ثابت حرف *کلید, int64_t مقدار,
                صحيح flags)
{
    حرف valuestr[22];
    snprintf(valuestr, حجم(valuestr), "%"PRId64, مقدار);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    أرجع av_dict_مجموعه(pm, کلید, valuestr, flags);
}

ساكن صحيح parse_کلید_مقدار_pair(AVDictionary **pm, ثابت حرف **buf,
                                ثابت حرف *کلید_val_sep, ثابت حرف *جفتها_sep,
                                صحيح flags)
{
    حرف *کلید = av_get_token(buf, کلید_val_sep);
    حرف *val = عدم;
    صحيح ret;

    إذا (کلید && *کلید && strspn(*buf, کلید_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, جفتها_sep);
    }

    إذا (کلید && *کلید && val && *val)
        ret = av_dict_مجموعه(pm, کلید, val, flags);
    وإلا
        ret = AVERROR(EINVAL);

    av_freep(&کلید);
    av_freep(&val);

    أرجع ret;
}

صحيح av_dict_parse_string(AVDictionary **pm, ثابت حرف *str,
                         ثابت حرف *کلید_val_sep, ثابت حرف *جفتها_sep,
                         صحيح flags)
{
    صحيح ret;

    إذا (!str)
        أرجع 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_کلید | AV_DICT_DONT_STRDUP_VAL);

    طالما (*str) {
        إذا ((ret = parse_کلید_مقدار_pair(pm, &str, کلید_val_sep, جفتها_sep, flags)) < 0)
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
        طالما (m->شمار--) {
            av_freep(&m->elems[m->شمار].کلید);
            av_freep(&m->elems[m->شمار].مقدار);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

صحيح av_dict_copy(AVDictionary **dst, ثابت AVDictionary *src, صحيح flags)
{
    ثابت AVDictionary_مدخل *t = عدم;

    إذا (!*dst && src && src->شمار && !src->duplicate_کلیدها &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(حجم(*m));
        إذا (!m)
            أرجع AVERROR(ENOMEM);
        m->elems = av_calloc(src->شمار, حجم(*m->elems));
        إذا (!m->elems) {
            av_free(m);
            أرجع AVERROR(ENOMEM);
        }
        *dst = m;
        لكل (صحيح i = 0; i < src->شمار; i++) {
            m->elems[i].کلید   = av_strdup(src->elems[i].کلید);
            m->elems[i].مقدار = av_strdup(src->elems[i].مقدار);
            m->شمار++;
            إذا (!m->elems[i].کلید || !m->elems[i].مقدار) {
                av_dict_free(dst);
                أرجع AVERROR(ENOMEM);
            }
        }
        أرجع 0;
    }

    طالما ((t = av_dict_iterate(src, t))) {
        صحيح ret = av_dict_مجموعه(dst, t->کلید, t->مقدار, flags);
        إذا (ret < 0)
            أرجع ret;
    }

    أرجع 0;
}

صحيح av_dict_get_string(ثابت AVDictionary *m, حرف **میانگیر,
                       ثابت حرف کلید_val_sep, ثابت حرف جفتها_sep)
{
    ثابت AVDictionary_مدخل *t = عدم;
    AVBPrint bprint;
    صحيح cnt = 0;
    حرف special_chars[] = {جفتها_sep, کلید_val_sep, '\0'};

    إذا (!میانگیر || جفتها_sep == '\0' || کلید_val_sep == '\0' || جفتها_sep == کلید_val_sep ||
        جفتها_sep == '\\' || کلید_val_sep == '\\')
        أرجع AVERROR(EINVAL);

    إذا (!av_dict_شمار(m)) {
        *میانگیر = av_strdup("");
        أرجع *میانگیر ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_اندازه_UNLIMITED);
    طالما ((t = av_dict_iterate(m, t))) {
        إذا (cnt++)
            av_bprint_append_داده(&bprint, &جفتها_sep, 1);
        av_bprint_escape(&bprint, t->کلید, special_chars, AV_ESCAPE_نما_BACKSLASH, 0);
        av_bprint_append_داده(&bprint, &کلید_val_sep, 1);
        av_bprint_escape(&bprint, t->مقدار, special_chars, AV_ESCAPE_نما_BACKSLASH, 0);
    }
    أرجع av_bprint_finalize(&bprint, میانگیر);
}
