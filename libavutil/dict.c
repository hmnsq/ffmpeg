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

ساختار AVDictionary {
    صحیح شمار;
    AVDictionaryEntry *elems;
    صحیح duplicate_کلیدها;
};

صحیح av_dict_شمار(ثابت AVDictionary *m)
{
    بازگشت m ? m->شمار : 0;
}

ثابت AVDictionaryEntry *av_dict_iterate(ثابت AVDictionary *m,
                                         ثابت AVDictionaryEntry *prev)
{
    صحیح i = 0;

    اگر (!m)
        بازگشت پوچ;

    اگر (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    اگر (i >= m->شمار)
        بازگشت پوچ;

    بازگشت &m->elems[i];
}

AVDictionaryEntry *av_dict_get(ثابت AVDictionary *m, ثابت نویسه *کلید,
                               ثابت AVDictionaryEntry *prev, صحیح flags)
{
    ثابت AVDictionaryEntry *entry = prev;
    unsigned صحیح j;

    اگر (!کلید)
        بازگشت پوچ;

    وقتی ((entry = av_dict_iterate(m, entry))) {
        ثابت نویسه *s = entry->کلید;
        اگر (flags & AV_DICT_MATCH_CASE)
            برای (j = 0; s[j] == کلید[j] && کلید[j]; j++)
                ;
        وگرنه
            برای (j = 0; av_toupper(s[j]) == av_toupper(کلید[j]) && کلید[j]; j++)
                ;
        اگر (کلید[j])
            ادامه;
        اگر (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            ادامه;
        بازگشت (AVDictionaryEntry *)entry;
    }
    بازگشت پوچ;
}

صحیح av_dict_set(AVDictionary **pm, ثابت نویسه *کلید, ثابت نویسه *مقدار,
                صحیح flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = پوچ;
    نویسه *copy_کلید = پوچ, *copy_مقدار = پوچ;
    صحیح err;

    اگر (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_مقدار = (تهی *)مقدار;
    وگرنه اگر (مقدار)
        copy_مقدار = av_strdup(مقدار);
    اگر (!کلید) {
        err = AVERROR(EINVAL);
        برو err_out;
    }
    اگر (flags & AV_DICT_DONT_STRDUP_کلید)
        copy_کلید = (تهی *)کلید;
    وگرنه
        copy_کلید = av_strdup(کلید);
    اگر (!copy_کلید || (مقدار && !copy_مقدار))
        برو enomem;

    اگر (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, کلید, پوچ, flags);
    } وگرنه اگر (flags & AV_DICT_DEDUP) {
        وقتی ((tag = av_dict_get(m, کلید, tag, flags))) {
            اگر ((!مقدار && !tag->مقدار) ||
                (مقدار && tag->مقدار && !strcmp(مقدار, tag->مقدار))) {
                av_free(copy_کلید);
                av_free(copy_مقدار);
                بازگشت 0;
            }
        }
    }
    اگر (!m)
        m = *pm = av_mallocz(اندازه(*m));
    اگر (!m)
        برو enomem;

    اگر (tag) {
        اگر (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_کلید);
            av_free(copy_مقدار);
            بازگشت 0;
        }
        اگر (copy_مقدار && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->مقدار);
            size_t new_part_len = strlen(copy_مقدار);
            size_t len = oldlen + new_part_len + 1;
            نویسه *newval = av_realloc(tag->مقدار, len);
            اگر (!newval)
                برو enomem;
            memcpy(newval + oldlen, copy_مقدار, new_part_len + 1);
            av_freep(&copy_مقدار);
            copy_مقدار = newval;
        } وگرنه
            av_free(tag->مقدار);
        av_free(tag->کلید);
        *tag = m->elems[--m->شمار];
    } وگرنه اگر (copy_مقدار) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->شمار + 1, اندازه(*m->elems));
        اگر (!tmp)
            برو enomem;
        m->elems = tmp;
    }
    اگر (copy_مقدار) {
        m->elems[m->شمار].کلید = copy_کلید;
        m->elems[m->شمار].مقدار = copy_مقدار;
        m->شمار++;
        اگر (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_کلیدها = 1;
    } وگرنه {
        err = 0;
        برو end;
    }

    بازگشت 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_مقدار);
end:
    اگر (m && !m->شمار) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_کلید);
    بازگشت err;
}

صحیح av_dict_set_int(AVDictionary **pm, ثابت نویسه *کلید, int64_t مقدار,
                صحیح flags)
{
    نویسه valuestr[22];
    snprintf(valuestr, اندازه(valuestr), "%"PRId64, مقدار);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    بازگشت av_dict_set(pm, کلید, valuestr, flags);
}

ایستا صحیح parse_کلید_مقدار_pair(AVDictionary **pm, ثابت نویسه **buf,
                                ثابت نویسه *کلید_val_sep, ثابت نویسه *pairs_sep,
                                صحیح flags)
{
    نویسه *کلید = av_get_token(buf, کلید_val_sep);
    نویسه *val = پوچ;
    صحیح ret;

    اگر (کلید && *کلید && strspn(*buf, کلید_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    اگر (کلید && *کلید && val && *val)
        ret = av_dict_set(pm, کلید, val, flags);
    وگرنه
        ret = AVERROR(EINVAL);

    av_freep(&کلید);
    av_freep(&val);

    بازگشت ret;
}

صحیح av_dict_parse_string(AVDictionary **pm, ثابت نویسه *str,
                         ثابت نویسه *کلید_val_sep, ثابت نویسه *pairs_sep,
                         صحیح flags)
{
    صحیح ret;

    اگر (!str)
        بازگشت 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_کلید | AV_DICT_DONT_STRDUP_VAL);

    وقتی (*str) {
        اگر ((ret = parse_کلید_مقدار_pair(pm, &str, کلید_val_sep, pairs_sep, flags)) < 0)
            بازگشت ret;

        اگر (*str)
            str++;
    }

    بازگشت 0;
}

تهی av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    اگر (m) {
        وقتی (m->شمار--) {
            av_freep(&m->elems[m->شمار].کلید);
            av_freep(&m->elems[m->شمار].مقدار);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

صحیح av_dict_copy(AVDictionary **dst, ثابت AVDictionary *src, صحیح flags)
{
    ثابت AVDictionaryEntry *t = پوچ;

    اگر (!*dst && src && src->شمار && !src->duplicate_کلیدها &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(اندازه(*m));
        اگر (!m)
            بازگشت AVERROR(ENOMEM);
        m->elems = av_calloc(src->شمار, اندازه(*m->elems));
        اگر (!m->elems) {
            av_free(m);
            بازگشت AVERROR(ENOMEM);
        }
        *dst = m;
        برای (صحیح i = 0; i < src->شمار; i++) {
            m->elems[i].کلید   = av_strdup(src->elems[i].کلید);
            m->elems[i].مقدار = av_strdup(src->elems[i].مقدار);
            m->شمار++;
            اگر (!m->elems[i].کلید || !m->elems[i].مقدار) {
                av_dict_free(dst);
                بازگشت AVERROR(ENOMEM);
            }
        }
        بازگشت 0;
    }

    وقتی ((t = av_dict_iterate(src, t))) {
        صحیح ret = av_dict_set(dst, t->کلید, t->مقدار, flags);
        اگر (ret < 0)
            بازگشت ret;
    }

    بازگشت 0;
}

صحیح av_dict_get_string(ثابت AVDictionary *m, نویسه **buffer,
                       ثابت نویسه کلید_val_sep, ثابت نویسه pairs_sep)
{
    ثابت AVDictionaryEntry *t = پوچ;
    AVBPrint bprint;
    صحیح cnt = 0;
    نویسه special_chars[] = {pairs_sep, کلید_val_sep, '\0'};

    اگر (!buffer || pairs_sep == '\0' || کلید_val_sep == '\0' || pairs_sep == کلید_val_sep ||
        pairs_sep == '\\' || کلید_val_sep == '\\')
        بازگشت AVERROR(EINVAL);

    اگر (!av_dict_شمار(m)) {
        *buffer = av_strdup("");
        بازگشت *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    وقتی ((t = av_dict_iterate(m, t))) {
        اگر (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->کلید, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &کلید_val_sep, 1);
        av_bprint_escape(&bprint, t->مقدار, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    بازگشت av_bprint_finalize(&bprint, buffer);
}
