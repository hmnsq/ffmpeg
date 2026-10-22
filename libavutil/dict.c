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

#شامل <inttypes.h>
#شامل <stdio.h>
#شامل <string.h>

#شامل "avassert.h"
#شامل "avstring.h"
#شامل "dict.h"
#شامل "error.h"
#شامل "mem.h"
#شامل "bprint.h"

ساخت AVDictionary {
    صحیح گنتی;
    AVDictionary_اندراج *elems;
    صحیح duplicate_کلیدیں;
};

صحیح av_dict_گنتی(ثابت AVDictionary *m)
{
    واپس m ? m->گنتی : 0;
}

ثابت AVDictionary_اندراج *av_dict_iterate(ثابت AVDictionary *m,
                                         ثابت AVDictionary_اندراج *پچھلا)
{
    صحیح i = 0;

    اگر (!m)
        واپس تہی;

    اگر (پچھلا)
        i = پچھلا - m->elems + 1;

    av_assert2(i >= 0);
    اگر (i >= m->گنتی)
        واپس تہی;

    واپس &m->elems[i];
}

AVDictionary_اندراج *av_dict_get(ثابت AVDictionary *m, ثابت حرف *کلید,
                               ثابت AVDictionary_اندراج *پچھلا, صحیح flags)
{
    ثابت AVDictionary_اندراج *اندراج_2 = پچھلا;
    غیرعلامتی صحیح j;

    اگر (!کلید)
        واپس تہی;

    جب ((اندراج_2 = av_dict_iterate(m, اندراج_2))) {
        ثابت حرف *s = اندراج_2->کلید;
        اگر (flags & AV_DICT_مطابقت_CASE)
            برائے (j = 0; s[j] == کلید[j] && کلید[j]; j++)
                ;
        ورنہ
            برائے (j = 0; av_toupper(s[j]) == av_toupper(کلید[j]) && کلید[j]; j++)
                ;
        اگر (کلید[j])
            جاری;
        اگر (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            جاری;
        واپس (AVDictionary_اندراج *)اندراج_2;
    }
    واپس تہی;
}

صحیح av_dict_سیٹ(AVDictionary **pm, ثابت حرف *کلید, ثابت حرف *قدر,
                صحیح flags)
{
    AVDictionary *m = *pm;
    AVDictionary_اندراج *لیبل = تہی;
    حرف *copy_کلید = تہی, *copy_قدر = تہی;
    صحیح err;

    اگر (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_قدر = (خالی *)قدر;
    ورنہ اگر (قدر)
        copy_قدر = av_strdup(قدر);
    اگر (!کلید) {
        err = AVERROR(EINVAL);
        جاؤ err_برآمد;
    }
    اگر (flags & AV_DICT_DONT_STRDUP_کلید)
        copy_کلید = (خالی *)کلید;
    ورنہ
        copy_کلید = av_strdup(کلید);
    اگر (!copy_کلید || (قدر && !copy_قدر))
        جاؤ enomem;

    اگر (!(flags & AV_DICT_MULTIKEY)) {
        لیبل = av_dict_get(m, کلید, تہی, flags);
    } ورنہ اگر (flags & AV_DICT_DEDUP) {
        جب ((لیبل = av_dict_get(m, کلید, لیبل, flags))) {
            اگر ((!قدر && !لیبل->قدر) ||
                (قدر && لیبل->قدر && !strcmp(قدر, لیبل->قدر))) {
                av_free(copy_کلید);
                av_free(copy_قدر);
                واپس 0;
            }
        }
    }
    اگر (!m)
        m = *pm = av_mallocz(حجم(*m));
    اگر (!m)
        جاؤ enomem;

    اگر (لیبل) {
        اگر (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_کلید);
            av_free(copy_قدر);
            واپس 0;
        }
        اگر (copy_قدر && flags & AV_DICT_APPEND) {
            size_t oldlen = لڑی_لمبائی(لیبل->قدر);
            size_t new_part_len = لڑی_لمبائی(copy_قدر);
            size_t len = oldlen + new_part_len + 1;
            حرف *newval = av_realloc(لیبل->قدر, len);
            اگر (!newval)
                جاؤ enomem;
            حافظہ_نقل(newval + oldlen, copy_قدر, new_part_len + 1);
            av_freep(&copy_قدر);
            copy_قدر = newval;
        } ورنہ
            av_free(لیبل->قدر);
        av_free(لیبل->کلید);
        *لیبل = m->elems[--m->گنتی];
    } ورنہ اگر (copy_قدر) {
        AVDictionary_اندراج *tmp = av_realloc_array(m->elems,
                                                  m->گنتی + 1, حجم(*m->elems));
        اگر (!tmp)
            جاؤ enomem;
        m->elems = tmp;
    }
    اگر (copy_قدر) {
        m->elems[m->گنتی].کلید = copy_کلید;
        m->elems[m->گنتی].قدر = copy_قدر;
        m->گنتی++;
        اگر (flags & (AV_DICT_مطابقت_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_کلیدیں = 1;
    } ورنہ {
        err = 0;
        جاؤ انتہا;
    }

    واپس 0;

enomem:
    err = AVERROR(ENOMEM);
err_برآمد:
    av_free(copy_قدر);
انتہا:
    اگر (m && !m->گنتی) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_کلید);
    واپس err;
}

صحیح av_dict_سیٹ_int(AVDictionary **pm, ثابت حرف *کلید, int64_t قدر,
                صحیح flags)
{
    حرف valuestr[22];
    snprintf(valuestr, حجم(valuestr), "%"PRId64, قدر);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    واپس av_dict_سیٹ(pm, کلید, valuestr, flags);
}

ساکن صحیح parse_کلید_قدر_pair(AVDictionary **pm, ثابت حرف **buf,
                                ثابت حرف *کلید_val_sep, ثابت حرف *جوڑے_sep,
                                صحیح flags)
{
    حرف *کلید = av_get_token(buf, کلید_val_sep);
    حرف *val = تہی;
    صحیح ret;

    اگر (کلید && *کلید && strspn(*buf, کلید_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, جوڑے_sep);
    }

    اگر (کلید && *کلید && val && *val)
        ret = av_dict_سیٹ(pm, کلید, val, flags);
    ورنہ
        ret = AVERROR(EINVAL);

    av_freep(&کلید);
    av_freep(&val);

    واپس ret;
}

صحیح av_dict_parse_string(AVDictionary **pm, ثابت حرف *str,
                         ثابت حرف *کلید_val_sep, ثابت حرف *جوڑے_sep,
                         صحیح flags)
{
    صحیح ret;

    اگر (!str)
        واپس 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_کلید | AV_DICT_DONT_STRDUP_VAL);

    جب (*str) {
        اگر ((ret = parse_کلید_قدر_pair(pm, &str, کلید_val_sep, جوڑے_sep, flags)) < 0)
            واپس ret;

        اگر (*str)
            str++;
    }

    واپس 0;
}

خالی av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    اگر (m) {
        جب (m->گنتی--) {
            av_freep(&m->elems[m->گنتی].کلید);
            av_freep(&m->elems[m->گنتی].قدر);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

صحیح av_dict_copy(AVDictionary **dst, ثابت AVDictionary *src, صحیح flags)
{
    ثابت AVDictionary_اندراج *t = تہی;

    اگر (!*dst && src && src->گنتی && !src->duplicate_کلیدیں &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(حجم(*m));
        اگر (!m)
            واپس AVERROR(ENOMEM);
        m->elems = av_calloc(src->گنتی, حجم(*m->elems));
        اگر (!m->elems) {
            av_free(m);
            واپس AVERROR(ENOMEM);
        }
        *dst = m;
        برائے (صحیح i = 0; i < src->گنتی; i++) {
            m->elems[i].کلید   = av_strdup(src->elems[i].کلید);
            m->elems[i].قدر = av_strdup(src->elems[i].قدر);
            m->گنتی++;
            اگر (!m->elems[i].کلید || !m->elems[i].قدر) {
                av_dict_free(dst);
                واپس AVERROR(ENOMEM);
            }
        }
        واپس 0;
    }

    جب ((t = av_dict_iterate(src, t))) {
        صحیح ret = av_dict_سیٹ(dst, t->کلید, t->قدر, flags);
        اگر (ret < 0)
            واپس ret;
    }

    واپس 0;
}

صحیح av_dict_get_string(ثابت AVDictionary *m, حرف **بفر,
                       ثابت حرف کلید_val_sep, ثابت حرف جوڑے_sep)
{
    ثابت AVDictionary_اندراج *t = تہی;
    AVBPrint bprint;
    صحیح cnt = 0;
    حرف special_chars[] = {جوڑے_sep, کلید_val_sep, '\0'};

    اگر (!بفر || جوڑے_sep == '\0' || کلید_val_sep == '\0' || جوڑے_sep == کلید_val_sep ||
        جوڑے_sep == '\\' || کلید_val_sep == '\\')
        واپس AVERROR(EINVAL);

    اگر (!av_dict_گنتی(m)) {
        *بفر = av_strdup("");
        واپس *بفر ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_سائز_UNLIMITED);
    جب ((t = av_dict_iterate(m, t))) {
        اگر (cnt++)
            av_bprint_append_ڈیٹا(&bprint, &جوڑے_sep, 1);
        av_bprint_escape(&bprint, t->کلید, special_chars, AV_ESCAPE_منوال_BACKSLASH, 0);
        av_bprint_append_ڈیٹا(&bprint, &کلید_val_sep, 1);
        av_bprint_escape(&bprint, t->قدر, special_chars, AV_ESCAPE_منوال_BACKSLASH, 0);
    }
    واپس av_bprint_finalize(&bprint, بفر);
}
