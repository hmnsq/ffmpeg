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

#अन्तर्भाव <inttypes.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "avstring.h"
#अन्तर्भाव "dict.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "bprint.h"

संरचना AVDictionary {
    पूर्णांक मोजणी;
    AVDictionaryEntry *elems;
    पूर्णांक duplicate_किल्ल्या;
};

पूर्णांक av_dict_मोजणी(स्थिरांक AVDictionary *m)
{
    परत m ? m->मोजणी : 0;
}

स्थिरांक AVDictionaryEntry *av_dict_iterate(स्थिरांक AVDictionary *m,
                                         स्थिरांक AVDictionaryEntry *prev)
{
    पूर्णांक i = 0;

    जर (!m)
        परत रिक्त;

    जर (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    जर (i >= m->मोजणी)
        परत रिक्त;

    परत &m->elems[i];
}

AVDictionaryEntry *av_dict_get(स्थिरांक AVDictionary *m, स्थिरांक अक्षर *किल्ली,
                               स्थिरांक AVDictionaryEntry *prev, पूर्णांक flags)
{
    स्थिरांक AVDictionaryEntry *entry = prev;
    अचिन्हित पूर्णांक j;

    जर (!किल्ली)
        परत रिक्त;

    पर्यंत ((entry = av_dict_iterate(m, entry))) {
        स्थिरांक अक्षर *s = entry->किल्ली;
        जर (flags & AV_DICT_MATCH_CASE)
            साठी (j = 0; s[j] == किल्ली[j] && किल्ली[j]; j++)
                ;
        अन्यथा
            साठी (j = 0; av_toupper(s[j]) == av_toupper(किल्ली[j]) && किल्ली[j]; j++)
                ;
        जर (किल्ली[j])
            सुरूठेवा;
        जर (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            सुरूठेवा;
        परत (AVDictionaryEntry *)entry;
    }
    परत रिक्त;
}

पूर्णांक av_dict_set(AVDictionary **pm, स्थिरांक अक्षर *किल्ली, स्थिरांक अक्षर *मूल्य,
                पूर्णांक flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = रिक्त;
    अक्षर *copy_किल्ली = रिक्त, *copy_मूल्य = रिक्त;
    पूर्णांक err;

    जर (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_मूल्य = (शून्य *)मूल्य;
    अन्यथा जर (मूल्य)
        copy_मूल्य = av_strdup(मूल्य);
    जर (!किल्ली) {
        err = AVERROR(EINVAL);
        जा err_out;
    }
    जर (flags & AV_DICT_DONT_STRDUP_किल्ली)
        copy_किल्ली = (शून्य *)किल्ली;
    अन्यथा
        copy_किल्ली = av_strdup(किल्ली);
    जर (!copy_किल्ली || (मूल्य && !copy_मूल्य))
        जा enomem;

    जर (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, किल्ली, रिक्त, flags);
    } अन्यथा जर (flags & AV_DICT_DEDUP) {
        पर्यंत ((tag = av_dict_get(m, किल्ली, tag, flags))) {
            जर ((!मूल्य && !tag->मूल्य) ||
                (मूल्य && tag->मूल्य && !म_भेद(मूल्य, tag->मूल्य))) {
                av_free(copy_किल्ली);
                av_free(copy_मूल्य);
                परत 0;
            }
        }
    }
    जर (!m)
        m = *pm = av_mallocz(आकार(*m));
    जर (!m)
        जा enomem;

    जर (tag) {
        जर (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_किल्ली);
            av_free(copy_मूल्य);
            परत 0;
        }
        जर (copy_मूल्य && flags & AV_DICT_APPEND) {
            माप_प्रकार oldlen = म_माप(tag->मूल्य);
            माप_प्रकार new_part_len = म_माप(copy_मूल्य);
            माप_प्रकार len = oldlen + new_part_len + 1;
            अक्षर *newval = av_realloc(tag->मूल्य, len);
            जर (!newval)
                जा enomem;
            स_नकल(newval + oldlen, copy_मूल्य, new_part_len + 1);
            av_freep(&copy_मूल्य);
            copy_मूल्य = newval;
        } अन्यथा
            av_free(tag->मूल्य);
        av_free(tag->किल्ली);
        *tag = m->elems[--m->मोजणी];
    } अन्यथा जर (copy_मूल्य) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->मोजणी + 1, आकार(*m->elems));
        जर (!tmp)
            जा enomem;
        m->elems = tmp;
    }
    जर (copy_मूल्य) {
        m->elems[m->मोजणी].किल्ली = copy_किल्ली;
        m->elems[m->मोजणी].मूल्य = copy_मूल्य;
        m->मोजणी++;
        जर (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_किल्ल्या = 1;
    } अन्यथा {
        err = 0;
        जा end;
    }

    परत 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_मूल्य);
end:
    जर (m && !m->मोजणी) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_किल्ली);
    परत err;
}

पूर्णांक av_dict_set_int(AVDictionary **pm, स्थिरांक अक्षर *किल्ली, int64_t मूल्य,
                पूर्णांक flags)
{
    अक्षर valuestr[22];
    snprintf(valuestr, आकार(valuestr), "%"PRId64, मूल्य);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    परत av_dict_set(pm, किल्ली, valuestr, flags);
}

स्थिर पूर्णांक parse_किल्ली_मूल्य_pair(AVDictionary **pm, स्थिरांक अक्षर **buf,
                                स्थिरांक अक्षर *किल्ली_val_sep, स्थिरांक अक्षर *pairs_sep,
                                पूर्णांक flags)
{
    अक्षर *किल्ली = av_get_token(buf, किल्ली_val_sep);
    अक्षर *val = रिक्त;
    पूर्णांक ret;

    जर (किल्ली && *किल्ली && म_अखोज(*buf, किल्ली_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    जर (किल्ली && *किल्ली && val && *val)
        ret = av_dict_set(pm, किल्ली, val, flags);
    अन्यथा
        ret = AVERROR(EINVAL);

    av_freep(&किल्ली);
    av_freep(&val);

    परत ret;
}

पूर्णांक av_dict_parse_string(AVDictionary **pm, स्थिरांक अक्षर *str,
                         स्थिरांक अक्षर *किल्ली_val_sep, स्थिरांक अक्षर *pairs_sep,
                         पूर्णांक flags)
{
    पूर्णांक ret;

    जर (!str)
        परत 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_किल्ली | AV_DICT_DONT_STRDUP_VAL);

    पर्यंत (*str) {
        जर ((ret = parse_किल्ली_मूल्य_pair(pm, &str, किल्ली_val_sep, pairs_sep, flags)) < 0)
            परत ret;

        जर (*str)
            str++;
    }

    परत 0;
}

शून्य av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    जर (m) {
        पर्यंत (m->मोजणी--) {
            av_freep(&m->elems[m->मोजणी].किल्ली);
            av_freep(&m->elems[m->मोजणी].मूल्य);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

पूर्णांक av_dict_copy(AVDictionary **dst, स्थिरांक AVDictionary *src, पूर्णांक flags)
{
    स्थिरांक AVDictionaryEntry *t = रिक्त;

    जर (!*dst && src && src->मोजणी && !src->duplicate_किल्ल्या &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(आकार(*m));
        जर (!m)
            परत AVERROR(ENOMEM);
        m->elems = av_calloc(src->मोजणी, आकार(*m->elems));
        जर (!m->elems) {
            av_free(m);
            परत AVERROR(ENOMEM);
        }
        *dst = m;
        साठी (पूर्णांक i = 0; i < src->मोजणी; i++) {
            m->elems[i].किल्ली   = av_strdup(src->elems[i].किल्ली);
            m->elems[i].मूल्य = av_strdup(src->elems[i].मूल्य);
            m->मोजणी++;
            जर (!m->elems[i].किल्ली || !m->elems[i].मूल्य) {
                av_dict_free(dst);
                परत AVERROR(ENOMEM);
            }
        }
        परत 0;
    }

    पर्यंत ((t = av_dict_iterate(src, t))) {
        पूर्णांक ret = av_dict_set(dst, t->किल्ली, t->मूल्य, flags);
        जर (ret < 0)
            परत ret;
    }

    परत 0;
}

पूर्णांक av_dict_get_string(स्थिरांक AVDictionary *m, अक्षर **buffer,
                       स्थिरांक अक्षर किल्ली_val_sep, स्थिरांक अक्षर pairs_sep)
{
    स्थिरांक AVDictionaryEntry *t = रिक्त;
    AVBPrint bprint;
    पूर्णांक cnt = 0;
    अक्षर special_chars[] = {pairs_sep, किल्ली_val_sep, '\0'};

    जर (!buffer || pairs_sep == '\0' || किल्ली_val_sep == '\0' || pairs_sep == किल्ली_val_sep ||
        pairs_sep == '\\' || किल्ली_val_sep == '\\')
        परत AVERROR(EINVAL);

    जर (!av_dict_मोजणी(m)) {
        *buffer = av_strdup("");
        परत *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    पर्यंत ((t = av_dict_iterate(m, t))) {
        जर (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->किल्ली, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &किल्ली_val_sep, 1);
        av_bprint_escape(&bprint, t->मूल्य, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    परत av_bprint_finalize(&bprint, buffer);
}
