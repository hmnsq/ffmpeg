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
    صحيح كدي;
    AVDictionaryEntry *elems;
    صحيح duplicate_مبوداي;
};

صحيح av_dict_كدي(ثابت AVDictionary *m)
{
    أرجع m ? m->كدي : 0;
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
    إذا (i >= m->كدي)
        أرجع عدم;

    أرجع &m->elems[i];
}

AVDictionaryEntry *av_dict_get(ثابت AVDictionary *m, ثابت حرف *مبودي,
                               ثابت AVDictionaryEntry *prev, صحيح flags)
{
    ثابت AVDictionaryEntry *entry = prev;
    unsigned صحيح j;

    إذا (!مبودي)
        أرجع عدم;

    طالما ((entry = av_dict_iterate(m, entry))) {
        ثابت حرف *s = entry->مبودي;
        إذا (flags & AV_DICT_MATCH_CASE)
            لكل (j = 0; s[j] == مبودي[j] && مبودي[j]; j++)
                ;
        وإلا
            لكل (j = 0; av_toupper(s[j]) == av_toupper(مبودي[j]) && مبودي[j]; j++)
                ;
        إذا (مبودي[j])
            استمر;
        إذا (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            استمر;
        أرجع (AVDictionaryEntry *)entry;
    }
    أرجع عدم;
}

صحيح av_dict_set(AVDictionary **pm, ثابت حرف *مبودي, ثابت حرف *درج,
                صحيح flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = عدم;
    حرف *copy_مبودي = عدم, *copy_درج = عدم;
    صحيح err;

    إذا (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_درج = (فراغ *)درج;
    وإلا إذا (درج)
        copy_درج = av_strdup(درج);
    إذا (!مبودي) {
        err = AVERROR(EINVAL);
        اذهب err_out;
    }
    إذا (flags & AV_DICT_DONT_STRDUP_مبودي)
        copy_مبودي = (فراغ *)مبودي;
    وإلا
        copy_مبودي = av_strdup(مبودي);
    إذا (!copy_مبودي || (درج && !copy_درج))
        اذهب enomem;

    إذا (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, مبودي, عدم, flags);
    } وإلا إذا (flags & AV_DICT_DEDUP) {
        طالما ((tag = av_dict_get(m, مبودي, tag, flags))) {
            إذا ((!درج && !tag->درج) ||
                (درج && tag->درج && !strcmp(درج, tag->درج))) {
                av_free(copy_مبودي);
                av_free(copy_درج);
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
            av_free(copy_مبودي);
            av_free(copy_درج);
            أرجع 0;
        }
        إذا (copy_درج && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->درج);
            size_t new_part_len = strlen(copy_درج);
            size_t len = oldlen + new_part_len + 1;
            حرف *newval = av_realloc(tag->درج, len);
            إذا (!newval)
                اذهب enomem;
            memcpy(newval + oldlen, copy_درج, new_part_len + 1);
            av_freep(&copy_درج);
            copy_درج = newval;
        } وإلا
            av_free(tag->درج);
        av_free(tag->مبودي);
        *tag = m->elems[--m->كدي];
    } وإلا إذا (copy_درج) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->كدي + 1, حجم(*m->elems));
        إذا (!tmp)
            اذهب enomem;
        m->elems = tmp;
    }
    إذا (copy_درج) {
        m->elems[m->كدي].مبودي = copy_مبودي;
        m->elems[m->كدي].درج = copy_درج;
        m->كدي++;
        إذا (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_مبوداي = 1;
    } وإلا {
        err = 0;
        اذهب end;
    }

    أرجع 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_درج);
end:
    إذا (m && !m->كدي) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_مبودي);
    أرجع err;
}

صحيح av_dict_set_int(AVDictionary **pm, ثابت حرف *مبودي, int64_t درج,
                صحيح flags)
{
    حرف valuestr[22];
    snprintf(valuestr, حجم(valuestr), "%"PRId64, درج);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    أرجع av_dict_set(pm, مبودي, valuestr, flags);
}

ساكن صحيح parse_مبودي_درج_pair(AVDictionary **pm, ثابت حرف **buf,
                                ثابت حرف *مبودي_val_sep, ثابت حرف *pairs_sep,
                                صحيح flags)
{
    حرف *مبودي = av_get_token(buf, مبودي_val_sep);
    حرف *val = عدم;
    صحيح ret;

    إذا (مبودي && *مبودي && strspn(*buf, مبودي_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    إذا (مبودي && *مبودي && val && *val)
        ret = av_dict_set(pm, مبودي, val, flags);
    وإلا
        ret = AVERROR(EINVAL);

    av_freep(&مبودي);
    av_freep(&val);

    أرجع ret;
}

صحيح av_dict_parse_string(AVDictionary **pm, ثابت حرف *str,
                         ثابت حرف *مبودي_val_sep, ثابت حرف *pairs_sep,
                         صحيح flags)
{
    صحيح ret;

    إذا (!str)
        أرجع 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_مبودي | AV_DICT_DONT_STRDUP_VAL);

    طالما (*str) {
        إذا ((ret = parse_مبودي_درج_pair(pm, &str, مبودي_val_sep, pairs_sep, flags)) < 0)
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
        طالما (m->كدي--) {
            av_freep(&m->elems[m->كدي].مبودي);
            av_freep(&m->elems[m->كدي].درج);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

صحيح av_dict_copy(AVDictionary **dst, ثابت AVDictionary *src, صحيح flags)
{
    ثابت AVDictionaryEntry *t = عدم;

    إذا (!*dst && src && src->كدي && !src->duplicate_مبوداي &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(حجم(*m));
        إذا (!m)
            أرجع AVERROR(ENOMEM);
        m->elems = av_calloc(src->كدي, حجم(*m->elems));
        إذا (!m->elems) {
            av_free(m);
            أرجع AVERROR(ENOMEM);
        }
        *dst = m;
        لكل (صحيح i = 0; i < src->كدي; i++) {
            m->elems[i].مبودي   = av_strdup(src->elems[i].مبودي);
            m->elems[i].درج = av_strdup(src->elems[i].درج);
            m->كدي++;
            إذا (!m->elems[i].مبودي || !m->elems[i].درج) {
                av_dict_free(dst);
                أرجع AVERROR(ENOMEM);
            }
        }
        أرجع 0;
    }

    طالما ((t = av_dict_iterate(src, t))) {
        صحيح ret = av_dict_set(dst, t->مبودي, t->درج, flags);
        إذا (ret < 0)
            أرجع ret;
    }

    أرجع 0;
}

صحيح av_dict_get_string(ثابت AVDictionary *m, حرف **buffer,
                       ثابت حرف مبودي_val_sep, ثابت حرف pairs_sep)
{
    ثابت AVDictionaryEntry *t = عدم;
    AVBPrint bprint;
    صحيح cnt = 0;
    حرف special_chars[] = {pairs_sep, مبودي_val_sep, '\0'};

    إذا (!buffer || pairs_sep == '\0' || مبودي_val_sep == '\0' || pairs_sep == مبودي_val_sep ||
        pairs_sep == '\\' || مبودي_val_sep == '\\')
        أرجع AVERROR(EINVAL);

    إذا (!av_dict_كدي(m)) {
        *buffer = av_strdup("");
        أرجع *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    طالما ((t = av_dict_iterate(m, t))) {
        إذا (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->مبودي, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &مبودي_val_sep, 1);
        av_bprint_escape(&bprint, t->درج, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    أرجع av_bprint_finalize(&bprint, buffer);
}
