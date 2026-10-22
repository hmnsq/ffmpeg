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
    صحيح ڳڻپ;
    AVDictionary_داخلا *elems;
    صحيح duplicate_ڪنجيون;
};

صحيح av_dict_ڳڻپ(ثابت AVDictionary *m)
{
    أرجع m ? m->ڳڻپ : 0;
}

ثابت AVDictionary_داخلا *av_dict_iterate(ثابت AVDictionary *m,
                                         ثابت AVDictionary_داخلا *prev)
{
    صحيح i = 0;

    إذا (!m)
        أرجع عدم;

    إذا (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    إذا (i >= m->ڳڻپ)
        أرجع عدم;

    أرجع &m->elems[i];
}

AVDictionary_داخلا *av_dict_get(ثابت AVDictionary *m, ثابت حرف *ڪنجي,
                               ثابت AVDictionary_داخلا *prev, صحيح flags)
{
    ثابت AVDictionary_داخلا *داخلا = prev;
    بنانشان صحيح j;

    إذا (!ڪنجي)
        أرجع عدم;

    طالما ((داخلا = av_dict_iterate(m, داخلا))) {
        ثابت حرف *s = داخلا->ڪنجي;
        إذا (flags & AV_DICT_ميلاپ_CASE)
            لكل (j = 0; s[j] == ڪنجي[j] && ڪنجي[j]; j++)
                ;
        وإلا
            لكل (j = 0; av_toupper(s[j]) == av_toupper(ڪنجي[j]) && ڪنجي[j]; j++)
                ;
        إذا (ڪنجي[j])
            استمر;
        إذا (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            استمر;
        أرجع (AVDictionary_داخلا *)داخلا;
    }
    أرجع عدم;
}

صحيح av_dict_سيٽ(AVDictionary **pm, ثابت حرف *ڪنجي, ثابت حرف *قدر,
                صحيح flags)
{
    AVDictionary *m = *pm;
    AVDictionary_داخلا *ٽيگ = عدم;
    حرف *copy_ڪنجي = عدم, *copy_قدر = عدم;
    صحيح err;

    إذا (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_قدر = (فراغ *)قدر;
    وإلا إذا (قدر)
        copy_قدر = av_strdup(قدر);
    إذا (!ڪنجي) {
        err = AVERROR(EINVAL);
        اذهب err_ٻاهريون;
    }
    إذا (flags & AV_DICT_DONT_STRDUP_ڪنجي)
        copy_ڪنجي = (فراغ *)ڪنجي;
    وإلا
        copy_ڪنجي = av_strdup(ڪنجي);
    إذا (!copy_ڪنجي || (قدر && !copy_قدر))
        اذهب enomem;

    إذا (!(flags & AV_DICT_MULTIKEY)) {
        ٽيگ = av_dict_get(m, ڪنجي, عدم, flags);
    } وإلا إذا (flags & AV_DICT_DEDUP) {
        طالما ((ٽيگ = av_dict_get(m, ڪنجي, ٽيگ, flags))) {
            إذا ((!قدر && !ٽيگ->قدر) ||
                (قدر && ٽيگ->قدر && !strcmp(قدر, ٽيگ->قدر))) {
                av_free(copy_ڪنجي);
                av_free(copy_قدر);
                أرجع 0;
            }
        }
    }
    إذا (!m)
        m = *pm = av_mallocz(حجم(*m));
    إذا (!m)
        اذهب enomem;

    إذا (ٽيگ) {
        إذا (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_ڪنجي);
            av_free(copy_قدر);
            أرجع 0;
        }
        إذا (copy_قدر && flags & AV_DICT_APPEND) {
            size_t oldlen = لڙي_ڊيگهه(ٽيگ->قدر);
            size_t new_part_len = لڙي_ڊيگهه(copy_قدر);
            size_t len = oldlen + new_part_len + 1;
            حرف *newval = av_realloc(ٽيگ->قدر, len);
            إذا (!newval)
                اذهب enomem;
            يادگيري_نقل(newval + oldlen, copy_قدر, new_part_len + 1);
            av_freep(&copy_قدر);
            copy_قدر = newval;
        } وإلا
            av_free(ٽيگ->قدر);
        av_free(ٽيگ->ڪنجي);
        *ٽيگ = m->elems[--m->ڳڻپ];
    } وإلا إذا (copy_قدر) {
        AVDictionary_داخلا *tmp = av_realloc_array(m->elems,
                                                  m->ڳڻپ + 1, حجم(*m->elems));
        إذا (!tmp)
            اذهب enomem;
        m->elems = tmp;
    }
    إذا (copy_قدر) {
        m->elems[m->ڳڻپ].ڪنجي = copy_ڪنجي;
        m->elems[m->ڳڻپ].قدر = copy_قدر;
        m->ڳڻپ++;
        إذا (flags & (AV_DICT_ميلاپ_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_ڪنجيون = 1;
    } وإلا {
        err = 0;
        اذهب پڇاڙي;
    }

    أرجع 0;

enomem:
    err = AVERROR(ENOMEM);
err_ٻاهريون:
    av_free(copy_قدر);
پڇاڙي:
    إذا (m && !m->ڳڻپ) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_ڪنجي);
    أرجع err;
}

صحيح av_dict_سيٽ_int(AVDictionary **pm, ثابت حرف *ڪنجي, int64_t قدر,
                صحيح flags)
{
    حرف valuestr[22];
    snprintf(valuestr, حجم(valuestr), "%"PRId64, قدر);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    أرجع av_dict_سيٽ(pm, ڪنجي, valuestr, flags);
}

ساكن صحيح parse_ڪنجي_قدر_pair(AVDictionary **pm, ثابت حرف **buf,
                                ثابت حرف *ڪنجي_val_sep, ثابت حرف *جوڙا_sep,
                                صحيح flags)
{
    حرف *ڪنجي = av_get_token(buf, ڪنجي_val_sep);
    حرف *val = عدم;
    صحيح ret;

    إذا (ڪنجي && *ڪنجي && strspn(*buf, ڪنجي_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, جوڙا_sep);
    }

    إذا (ڪنجي && *ڪنجي && val && *val)
        ret = av_dict_سيٽ(pm, ڪنجي, val, flags);
    وإلا
        ret = AVERROR(EINVAL);

    av_freep(&ڪنجي);
    av_freep(&val);

    أرجع ret;
}

صحيح av_dict_parse_string(AVDictionary **pm, ثابت حرف *str,
                         ثابت حرف *ڪنجي_val_sep, ثابت حرف *جوڙا_sep,
                         صحيح flags)
{
    صحيح ret;

    إذا (!str)
        أرجع 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_ڪنجي | AV_DICT_DONT_STRDUP_VAL);

    طالما (*str) {
        إذا ((ret = parse_ڪنجي_قدر_pair(pm, &str, ڪنجي_val_sep, جوڙا_sep, flags)) < 0)
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
        طالما (m->ڳڻپ--) {
            av_freep(&m->elems[m->ڳڻپ].ڪنجي);
            av_freep(&m->elems[m->ڳڻپ].قدر);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

صحيح av_dict_copy(AVDictionary **dst, ثابت AVDictionary *src, صحيح flags)
{
    ثابت AVDictionary_داخلا *t = عدم;

    إذا (!*dst && src && src->ڳڻپ && !src->duplicate_ڪنجيون &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(حجم(*m));
        إذا (!m)
            أرجع AVERROR(ENOMEM);
        m->elems = av_calloc(src->ڳڻپ, حجم(*m->elems));
        إذا (!m->elems) {
            av_free(m);
            أرجع AVERROR(ENOMEM);
        }
        *dst = m;
        لكل (صحيح i = 0; i < src->ڳڻپ; i++) {
            m->elems[i].ڪنجي   = av_strdup(src->elems[i].ڪنجي);
            m->elems[i].قدر = av_strdup(src->elems[i].قدر);
            m->ڳڻپ++;
            إذا (!m->elems[i].ڪنجي || !m->elems[i].قدر) {
                av_dict_free(dst);
                أرجع AVERROR(ENOMEM);
            }
        }
        أرجع 0;
    }

    طالما ((t = av_dict_iterate(src, t))) {
        صحيح ret = av_dict_سيٽ(dst, t->ڪنجي, t->قدر, flags);
        إذا (ret < 0)
            أرجع ret;
    }

    أرجع 0;
}

صحيح av_dict_get_string(ثابت AVDictionary *m, حرف **بفر,
                       ثابت حرف ڪنجي_val_sep, ثابت حرف جوڙا_sep)
{
    ثابت AVDictionary_داخلا *t = عدم;
    AVBPrint bprint;
    صحيح cnt = 0;
    حرف special_chars[] = {جوڙا_sep, ڪنجي_val_sep, '\0'};

    إذا (!بفر || جوڙا_sep == '\0' || ڪنجي_val_sep == '\0' || جوڙا_sep == ڪنجي_val_sep ||
        جوڙا_sep == '\\' || ڪنجي_val_sep == '\\')
        أرجع AVERROR(EINVAL);

    إذا (!av_dict_ڳڻپ(m)) {
        *بفر = av_strdup("");
        أرجع *بفر ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_سائيز_UNLIMITED);
    طالما ((t = av_dict_iterate(m, t))) {
        إذا (cnt++)
            av_bprint_append_معلومات(&bprint, &جوڙا_sep, 1);
        av_bprint_escape(&bprint, t->ڪنجي, special_chars, AV_ESCAPE_گهڻائي_BACKSLASH, 0);
        av_bprint_append_معلومات(&bprint, &ڪنجي_val_sep, 1);
        av_bprint_escape(&bprint, t->قدر, special_chars, AV_ESCAPE_گهڻائي_BACKSLASH, 0);
    }
    أرجع av_bprint_finalize(&bprint, بفر);
}
