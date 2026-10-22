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

#समावेश <inttypes.h>
#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "avassert.h"
#समावेश "avstring.h"
#समावेश "dict.h"
#समावेश "error.h"
#समावेश "mem.h"
#समावेश "bprint.h"

काष्ठा AVDictionary {
    पूर्णांक गिनती;
    AVDictionaryEntry *elems;
    पूर्णांक duplicate_कुंजियाँ;
};

पूर्णांक av_dict_गिनती(स्थिर AVDictionary *m)
{
    वापस m ? m->गिनती : 0;
}

स्थिर AVDictionaryEntry *av_dict_iterate(स्थिर AVDictionary *m,
                                         स्थिर AVDictionaryEntry *पूर्व)
{
    पूर्णांक i = 0;

    अगर (!m)
        वापस शून्य;

    अगर (पूर्व)
        i = पूर्व - m->elems + 1;

    av_assert2(i >= 0);
    अगर (i >= m->गिनती)
        वापस शून्य;

    वापस &m->elems[i];
}

AVDictionaryEntry *av_dict_get(स्थिर AVDictionary *m, स्थिर अक्षर *कुंजी,
                               स्थिर AVDictionaryEntry *पूर्व, पूर्णांक flags)
{
    स्थिर AVDictionaryEntry *entry = पूर्व;
    अचिन्हित पूर्णांक j;

    अगर (!कुंजी)
        वापस शून्य;

    जबतक ((entry = av_dict_iterate(m, entry))) {
        स्थिर अक्षर *s = entry->कुंजी;
        अगर (flags & AV_DICT_MATCH_CASE)
            क्रम (j = 0; s[j] == कुंजी[j] && कुंजी[j]; j++)
                ;
        अन्यथा
            क्रम (j = 0; av_toupper(s[j]) == av_toupper(कुंजी[j]) && कुंजी[j]; j++)
                ;
        अगर (कुंजी[j])
            जारी;
        अगर (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            जारी;
        वापस (AVDictionaryEntry *)entry;
    }
    वापस शून्य;
}

पूर्णांक av_dict_set(AVDictionary **pm, स्थिर अक्षर *कुंजी, स्थिर अक्षर *मूल्य,
                पूर्णांक flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = शून्य;
    अक्षर *copy_कुंजी = शून्य, *copy_मूल्य = शून्य;
    पूर्णांक err;

    अगर (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_मूल्य = (व्योम *)मूल्य;
    अन्यथा अगर (मूल्य)
        copy_मूल्य = av_strdup(मूल्य);
    अगर (!कुंजी) {
        err = AVERROR(EINVAL);
        जाओ err_out;
    }
    अगर (flags & AV_DICT_DONT_STRDUP_कुंजी)
        copy_कुंजी = (व्योम *)कुंजी;
    अन्यथा
        copy_कुंजी = av_strdup(कुंजी);
    अगर (!copy_कुंजी || (मूल्य && !copy_मूल्य))
        जाओ enomem;

    अगर (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, कुंजी, शून्य, flags);
    } अन्यथा अगर (flags & AV_DICT_DEDUP) {
        जबतक ((tag = av_dict_get(m, कुंजी, tag, flags))) {
            अगर ((!मूल्य && !tag->मूल्य) ||
                (मूल्य && tag->मूल्य && !म_भेद(मूल्य, tag->मूल्य))) {
                av_free(copy_कुंजी);
                av_free(copy_मूल्य);
                वापस 0;
            }
        }
    }
    अगर (!m)
        m = *pm = av_mallocz(माप(*m));
    अगर (!m)
        जाओ enomem;

    अगर (tag) {
        अगर (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_कुंजी);
            av_free(copy_मूल्य);
            वापस 0;
        }
        अगर (copy_मूल्य && flags & AV_DICT_APPEND) {
            माप_प्रकार oldlen = म_माप(tag->मूल्य);
            माप_प्रकार new_part_len = म_माप(copy_मूल्य);
            माप_प्रकार len = oldlen + new_part_len + 1;
            अक्षर *newval = av_realloc(tag->मूल्य, len);
            अगर (!newval)
                जाओ enomem;
            स_नकल(newval + oldlen, copy_मूल्य, new_part_len + 1);
            av_freep(&copy_मूल्य);
            copy_मूल्य = newval;
        } अन्यथा
            av_free(tag->मूल्य);
        av_free(tag->कुंजी);
        *tag = m->elems[--m->गिनती];
    } अन्यथा अगर (copy_मूल्य) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->गिनती + 1, माप(*m->elems));
        अगर (!tmp)
            जाओ enomem;
        m->elems = tmp;
    }
    अगर (copy_मूल्य) {
        m->elems[m->गिनती].कुंजी = copy_कुंजी;
        m->elems[m->गिनती].मूल्य = copy_मूल्य;
        m->गिनती++;
        अगर (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_कुंजियाँ = 1;
    } अन्यथा {
        err = 0;
        जाओ end;
    }

    वापस 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_मूल्य);
end:
    अगर (m && !m->गिनती) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_कुंजी);
    वापस err;
}

पूर्णांक av_dict_set_int(AVDictionary **pm, स्थिर अक्षर *कुंजी, int64_t मूल्य,
                पूर्णांक flags)
{
    अक्षर valuestr[22];
    snprintf(valuestr, माप(valuestr), "%"PRId64, मूल्य);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    वापस av_dict_set(pm, कुंजी, valuestr, flags);
}

अटल पूर्णांक parse_कुंजी_मूल्य_pair(AVDictionary **pm, स्थिर अक्षर **buf,
                                स्थिर अक्षर *कुंजी_val_sep, स्थिर अक्षर *pairs_sep,
                                पूर्णांक flags)
{
    अक्षर *कुंजी = av_get_token(buf, कुंजी_val_sep);
    अक्षर *val = शून्य;
    पूर्णांक ret;

    अगर (कुंजी && *कुंजी && म_अखोज(*buf, कुंजी_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    अगर (कुंजी && *कुंजी && val && *val)
        ret = av_dict_set(pm, कुंजी, val, flags);
    अन्यथा
        ret = AVERROR(EINVAL);

    av_freep(&कुंजी);
    av_freep(&val);

    वापस ret;
}

पूर्णांक av_dict_parse_string(AVDictionary **pm, स्थिर अक्षर *str,
                         स्थिर अक्षर *कुंजी_val_sep, स्थिर अक्षर *pairs_sep,
                         पूर्णांक flags)
{
    पूर्णांक ret;

    अगर (!str)
        वापस 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_कुंजी | AV_DICT_DONT_STRDUP_VAL);

    जबतक (*str) {
        अगर ((ret = parse_कुंजी_मूल्य_pair(pm, &str, कुंजी_val_sep, pairs_sep, flags)) < 0)
            वापस ret;

        अगर (*str)
            str++;
    }

    वापस 0;
}

व्योम av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    अगर (m) {
        जबतक (m->गिनती--) {
            av_freep(&m->elems[m->गिनती].कुंजी);
            av_freep(&m->elems[m->गिनती].मूल्य);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

पूर्णांक av_dict_copy(AVDictionary **dst, स्थिर AVDictionary *src, पूर्णांक flags)
{
    स्थिर AVDictionaryEntry *t = शून्य;

    अगर (!*dst && src && src->गिनती && !src->duplicate_कुंजियाँ &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(माप(*m));
        अगर (!m)
            वापस AVERROR(ENOMEM);
        m->elems = av_calloc(src->गिनती, माप(*m->elems));
        अगर (!m->elems) {
            av_free(m);
            वापस AVERROR(ENOMEM);
        }
        *dst = m;
        क्रम (पूर्णांक i = 0; i < src->गिनती; i++) {
            m->elems[i].कुंजी   = av_strdup(src->elems[i].कुंजी);
            m->elems[i].मूल्य = av_strdup(src->elems[i].मूल्य);
            m->गिनती++;
            अगर (!m->elems[i].कुंजी || !m->elems[i].मूल्य) {
                av_dict_free(dst);
                वापस AVERROR(ENOMEM);
            }
        }
        वापस 0;
    }

    जबतक ((t = av_dict_iterate(src, t))) {
        पूर्णांक ret = av_dict_set(dst, t->कुंजी, t->मूल्य, flags);
        अगर (ret < 0)
            वापस ret;
    }

    वापस 0;
}

पूर्णांक av_dict_get_string(स्थिर AVDictionary *m, अक्षर **बफर,
                       स्थिर अक्षर कुंजी_val_sep, स्थिर अक्षर pairs_sep)
{
    स्थिर AVDictionaryEntry *t = शून्य;
    AVBPrint bprint;
    पूर्णांक cnt = 0;
    अक्षर special_chars[] = {pairs_sep, कुंजी_val_sep, '\0'};

    अगर (!बफर || pairs_sep == '\0' || कुंजी_val_sep == '\0' || pairs_sep == कुंजी_val_sep ||
        pairs_sep == '\\' || कुंजी_val_sep == '\\')
        वापस AVERROR(EINVAL);

    अगर (!av_dict_गिनती(m)) {
        *बफर = av_strdup("");
        वापस *बफर ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_आकार_UNLIMITED);
    जबतक ((t = av_dict_iterate(m, t))) {
        अगर (cnt++)
            av_bprint_append_तथ्य(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->कुंजी, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_तथ्य(&bprint, &कुंजी_val_sep, 1);
        av_bprint_escape(&bprint, t->मूल्य, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    वापस av_bprint_finalize(&bprint, बफर);
}
