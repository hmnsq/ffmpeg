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
    صحيح کيراءن;
    AVDictionaryEntry *elems;
    صحيح duplicate_کونچي_سموا;
};

صحيح av_dict_کيراءن(ثابت AVDictionary *m)
{
    أرجع m ? m->کيراءن : 0;
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
    إذا (i >= m->کيراءن)
        أرجع عدم;

    أرجع &m->elems[i];
}

AVDictionaryEntry *av_dict_get(ثابت AVDictionary *m, ثابت حرف *کونچي,
                               ثابت AVDictionaryEntry *prev, صحيح flags)
{
    ثابت AVDictionaryEntry *entry = prev;
    unsigned صحيح j;

    إذا (!کونچي)
        أرجع عدم;

    طالما ((entry = av_dict_iterate(m, entry))) {
        ثابت حرف *s = entry->کونچي;
        إذا (flags & AV_DICT_MATCH_CASE)
            لكل (j = 0; s[j] == کونچي[j] && کونچي[j]; j++)
                ;
        وإلا
            لكل (j = 0; av_toupper(s[j]) == av_toupper(کونچي[j]) && کونچي[j]; j++)
                ;
        إذا (کونچي[j])
            استمر;
        إذا (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            استمر;
        أرجع (AVDictionaryEntry *)entry;
    }
    أرجع عدم;
}

صحيح av_dict_set(AVDictionary **pm, ثابت حرف *کونچي, ثابت حرف *نيلاي,
                صحيح flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = عدم;
    حرف *copy_کونچي = عدم, *copy_نيلاي = عدم;
    صحيح err;

    إذا (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_نيلاي = (فراغ *)نيلاي;
    وإلا إذا (نيلاي)
        copy_نيلاي = av_strdup(نيلاي);
    إذا (!کونچي) {
        err = AVERROR(EINVAL);
        اذهب err_out;
    }
    إذا (flags & AV_DICT_DONT_STRDUP_کونچي)
        copy_کونچي = (فراغ *)کونچي;
    وإلا
        copy_کونچي = av_strdup(کونچي);
    إذا (!copy_کونچي || (نيلاي && !copy_نيلاي))
        اذهب enomem;

    إذا (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, کونچي, عدم, flags);
    } وإلا إذا (flags & AV_DICT_DEDUP) {
        طالما ((tag = av_dict_get(m, کونچي, tag, flags))) {
            إذا ((!نيلاي && !tag->نيلاي) ||
                (نيلاي && tag->نيلاي && !strcmp(نيلاي, tag->نيلاي))) {
                av_free(copy_کونچي);
                av_free(copy_نيلاي);
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
            av_free(copy_کونچي);
            av_free(copy_نيلاي);
            أرجع 0;
        }
        إذا (copy_نيلاي && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->نيلاي);
            size_t new_part_len = strlen(copy_نيلاي);
            size_t len = oldlen + new_part_len + 1;
            حرف *newval = av_realloc(tag->نيلاي, len);
            إذا (!newval)
                اذهب enomem;
            memcpy(newval + oldlen, copy_نيلاي, new_part_len + 1);
            av_freep(&copy_نيلاي);
            copy_نيلاي = newval;
        } وإلا
            av_free(tag->نيلاي);
        av_free(tag->کونچي);
        *tag = m->elems[--m->کيراءن];
    } وإلا إذا (copy_نيلاي) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->کيراءن + 1, حجم(*m->elems));
        إذا (!tmp)
            اذهب enomem;
        m->elems = tmp;
    }
    إذا (copy_نيلاي) {
        m->elems[m->کيراءن].کونچي = copy_کونچي;
        m->elems[m->کيراءن].نيلاي = copy_نيلاي;
        m->کيراءن++;
        إذا (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_کونچي_سموا = 1;
    } وإلا {
        err = 0;
        اذهب end;
    }

    أرجع 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_نيلاي);
end:
    إذا (m && !m->کيراءن) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_کونچي);
    أرجع err;
}

صحيح av_dict_set_int(AVDictionary **pm, ثابت حرف *کونچي, int64_t نيلاي,
                صحيح flags)
{
    حرف valuestr[22];
    snprintf(valuestr, حجم(valuestr), "%"PRId64, نيلاي);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    أرجع av_dict_set(pm, کونچي, valuestr, flags);
}

ساكن صحيح parse_کونچي_نيلاي_pair(AVDictionary **pm, ثابت حرف **buf,
                                ثابت حرف *کونچي_val_sep, ثابت حرف *pairs_sep,
                                صحيح flags)
{
    حرف *کونچي = av_get_token(buf, کونچي_val_sep);
    حرف *val = عدم;
    صحيح ret;

    إذا (کونچي && *کونچي && strspn(*buf, کونچي_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    إذا (کونچي && *کونچي && val && *val)
        ret = av_dict_set(pm, کونچي, val, flags);
    وإلا
        ret = AVERROR(EINVAL);

    av_freep(&کونچي);
    av_freep(&val);

    أرجع ret;
}

صحيح av_dict_parse_string(AVDictionary **pm, ثابت حرف *str,
                         ثابت حرف *کونچي_val_sep, ثابت حرف *pairs_sep,
                         صحيح flags)
{
    صحيح ret;

    إذا (!str)
        أرجع 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_کونچي | AV_DICT_DONT_STRDUP_VAL);

    طالما (*str) {
        إذا ((ret = parse_کونچي_نيلاي_pair(pm, &str, کونچي_val_sep, pairs_sep, flags)) < 0)
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
        طالما (m->کيراءن--) {
            av_freep(&m->elems[m->کيراءن].کونچي);
            av_freep(&m->elems[m->کيراءن].نيلاي);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

صحيح av_dict_copy(AVDictionary **dst, ثابت AVDictionary *src, صحيح flags)
{
    ثابت AVDictionaryEntry *t = عدم;

    إذا (!*dst && src && src->کيراءن && !src->duplicate_کونچي_سموا &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(حجم(*m));
        إذا (!m)
            أرجع AVERROR(ENOMEM);
        m->elems = av_calloc(src->کيراءن, حجم(*m->elems));
        إذا (!m->elems) {
            av_free(m);
            أرجع AVERROR(ENOMEM);
        }
        *dst = m;
        لكل (صحيح i = 0; i < src->کيراءن; i++) {
            m->elems[i].کونچي   = av_strdup(src->elems[i].کونچي);
            m->elems[i].نيلاي = av_strdup(src->elems[i].نيلاي);
            m->کيراءن++;
            إذا (!m->elems[i].کونچي || !m->elems[i].نيلاي) {
                av_dict_free(dst);
                أرجع AVERROR(ENOMEM);
            }
        }
        أرجع 0;
    }

    طالما ((t = av_dict_iterate(src, t))) {
        صحيح ret = av_dict_set(dst, t->کونچي, t->نيلاي, flags);
        إذا (ret < 0)
            أرجع ret;
    }

    أرجع 0;
}

صحيح av_dict_get_string(ثابت AVDictionary *m, حرف **buffer,
                       ثابت حرف کونچي_val_sep, ثابت حرف pairs_sep)
{
    ثابت AVDictionaryEntry *t = عدم;
    AVBPrint bprint;
    صحيح cnt = 0;
    حرف special_chars[] = {pairs_sep, کونچي_val_sep, '\0'};

    إذا (!buffer || pairs_sep == '\0' || کونچي_val_sep == '\0' || pairs_sep == کونچي_val_sep ||
        pairs_sep == '\\' || کونچي_val_sep == '\\')
        أرجع AVERROR(EINVAL);

    إذا (!av_dict_کيراءن(m)) {
        *buffer = av_strdup("");
        أرجع *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    طالما ((t = av_dict_iterate(m, t))) {
        إذا (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->کونچي, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &کونچي_val_sep, 1);
        av_bprint_escape(&bprint, t->نيلاي, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    أرجع av_bprint_finalize(&bprint, buffer);
}
