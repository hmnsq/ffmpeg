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
    पूर्णाङ्क गन्ती;
    AVDictionaryEntry *elems;
    पूर्णाङ्क duplicate_साँचोहरू;
};

पूर्णाङ्क av_dict_गन्ती(अचर AVDictionary *m)
{
    फर्काऊ m ? m->गन्ती : 0;
}

अचर AVDictionaryEntry *av_dict_iterate(अचर AVDictionary *m,
                                         अचर AVDictionaryEntry *prev)
{
    पूर्णाङ्क i = 0;

    यदि (!m)
        फर्काऊ रिक्त;

    यदि (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    यदि (i >= m->गन्ती)
        फर्काऊ रिक्त;

    फर्काऊ &m->elems[i];
}

AVDictionaryEntry *av_dict_get(अचर AVDictionary *m, अचर वर्ण *साँचो,
                               अचर AVDictionaryEntry *prev, पूर्णाङ्क flags)
{
    अचर AVDictionaryEntry *entry = prev;
    अचिन्हित पूर्णाङ्क j;

    यदि (!साँचो)
        फर्काऊ रिक्त;

    जबसम्म ((entry = av_dict_iterate(m, entry))) {
        अचर वर्ण *s = entry->साँचो;
        यदि (flags & AV_DICT_MATCH_CASE)
            लागि (j = 0; s[j] == साँचो[j] && साँचो[j]; j++)
                ;
        अन्यथा
            लागि (j = 0; av_toupper(s[j]) == av_toupper(साँचो[j]) && साँचो[j]; j++)
                ;
        यदि (साँचो[j])
            जारी;
        यदि (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            जारी;
        फर्काऊ (AVDictionaryEntry *)entry;
    }
    फर्काऊ रिक्त;
}

पूर्णाङ्क av_dict_set(AVDictionary **pm, अचर वर्ण *साँचो, अचर वर्ण *मान,
                पूर्णाङ्क flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = रिक्त;
    वर्ण *copy_साँचो = रिक्त, *copy_मान = रिक्त;
    पूर्णाङ्क err;

    यदि (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_मान = (शून्य *)मान;
    अन्यथा यदि (मान)
        copy_मान = av_strdup(मान);
    यदि (!साँचो) {
        err = AVERROR(EINVAL);
        गच्छ err_out;
    }
    यदि (flags & AV_DICT_DONT_STRDUP_साँचो)
        copy_साँचो = (शून्य *)साँचो;
    अन्यथा
        copy_साँचो = av_strdup(साँचो);
    यदि (!copy_साँचो || (मान && !copy_मान))
        गच्छ enomem;

    यदि (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, साँचो, रिक्त, flags);
    } अन्यथा यदि (flags & AV_DICT_DEDUP) {
        जबसम्म ((tag = av_dict_get(m, साँचो, tag, flags))) {
            यदि ((!मान && !tag->मान) ||
                (मान && tag->मान && !म_भेद(मान, tag->मान))) {
                av_free(copy_साँचो);
                av_free(copy_मान);
                फर्काऊ 0;
            }
        }
    }
    यदि (!m)
        m = *pm = av_mallocz(परिमाण(*m));
    यदि (!m)
        गच्छ enomem;

    यदि (tag) {
        यदि (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_साँचो);
            av_free(copy_मान);
            फर्काऊ 0;
        }
        यदि (copy_मान && flags & AV_DICT_APPEND) {
            माप_प्रकार oldlen = म_माप(tag->मान);
            माप_प्रकार new_part_len = म_माप(copy_मान);
            माप_प्रकार len = oldlen + new_part_len + 1;
            वर्ण *newval = av_realloc(tag->मान, len);
            यदि (!newval)
                गच्छ enomem;
            स_नकल(newval + oldlen, copy_मान, new_part_len + 1);
            av_freep(&copy_मान);
            copy_मान = newval;
        } अन्यथा
            av_free(tag->मान);
        av_free(tag->साँचो);
        *tag = m->elems[--m->गन्ती];
    } अन्यथा यदि (copy_मान) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->गन्ती + 1, परिमाण(*m->elems));
        यदि (!tmp)
            गच्छ enomem;
        m->elems = tmp;
    }
    यदि (copy_मान) {
        m->elems[m->गन्ती].साँचो = copy_साँचो;
        m->elems[m->गन्ती].मान = copy_मान;
        m->गन्ती++;
        यदि (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_साँचोहरू = 1;
    } अन्यथा {
        err = 0;
        गच्छ end;
    }

    फर्काऊ 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_मान);
end:
    यदि (m && !m->गन्ती) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_साँचो);
    फर्काऊ err;
}

पूर्णाङ्क av_dict_set_int(AVDictionary **pm, अचर वर्ण *साँचो, int64_t मान,
                पूर्णाङ्क flags)
{
    वर्ण valuestr[22];
    snprintf(valuestr, परिमाण(valuestr), "%"PRId64, मान);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    फर्काऊ av_dict_set(pm, साँचो, valuestr, flags);
}

स्थिर पूर्णाङ्क parse_साँचो_मान_pair(AVDictionary **pm, अचर वर्ण **buf,
                                अचर वर्ण *साँचो_val_sep, अचर वर्ण *pairs_sep,
                                पूर्णाङ्क flags)
{
    वर्ण *साँचो = av_get_token(buf, साँचो_val_sep);
    वर्ण *val = रिक्त;
    पूर्णाङ्क ret;

    यदि (साँचो && *साँचो && म_अखोज(*buf, साँचो_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    यदि (साँचो && *साँचो && val && *val)
        ret = av_dict_set(pm, साँचो, val, flags);
    अन्यथा
        ret = AVERROR(EINVAL);

    av_freep(&साँचो);
    av_freep(&val);

    फर्काऊ ret;
}

पूर्णाङ्क av_dict_parse_string(AVDictionary **pm, अचर वर्ण *str,
                         अचर वर्ण *साँचो_val_sep, अचर वर्ण *pairs_sep,
                         पूर्णाङ्क flags)
{
    पूर्णाङ्क ret;

    यदि (!str)
        फर्काऊ 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_साँचो | AV_DICT_DONT_STRDUP_VAL);

    जबसम्म (*str) {
        यदि ((ret = parse_साँचो_मान_pair(pm, &str, साँचो_val_sep, pairs_sep, flags)) < 0)
            फर्काऊ ret;

        यदि (*str)
            str++;
    }

    फर्काऊ 0;
}

शून्य av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    यदि (m) {
        जबसम्म (m->गन्ती--) {
            av_freep(&m->elems[m->गन्ती].साँचो);
            av_freep(&m->elems[m->गन्ती].मान);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

पूर्णाङ्क av_dict_copy(AVDictionary **dst, अचर AVDictionary *src, पूर्णाङ्क flags)
{
    अचर AVDictionaryEntry *t = रिक्त;

    यदि (!*dst && src && src->गन्ती && !src->duplicate_साँचोहरू &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(परिमाण(*m));
        यदि (!m)
            फर्काऊ AVERROR(ENOMEM);
        m->elems = av_calloc(src->गन्ती, परिमाण(*m->elems));
        यदि (!m->elems) {
            av_free(m);
            फर्काऊ AVERROR(ENOMEM);
        }
        *dst = m;
        लागि (पूर्णाङ्क i = 0; i < src->गन्ती; i++) {
            m->elems[i].साँचो   = av_strdup(src->elems[i].साँचो);
            m->elems[i].मान = av_strdup(src->elems[i].मान);
            m->गन्ती++;
            यदि (!m->elems[i].साँचो || !m->elems[i].मान) {
                av_dict_free(dst);
                फर्काऊ AVERROR(ENOMEM);
            }
        }
        फर्काऊ 0;
    }

    जबसम्म ((t = av_dict_iterate(src, t))) {
        पूर्णाङ्क ret = av_dict_set(dst, t->साँचो, t->मान, flags);
        यदि (ret < 0)
            फर्काऊ ret;
    }

    फर्काऊ 0;
}

पूर्णाङ्क av_dict_get_string(अचर AVDictionary *m, वर्ण **buffer,
                       अचर वर्ण साँचो_val_sep, अचर वर्ण pairs_sep)
{
    अचर AVDictionaryEntry *t = रिक्त;
    AVBPrint bprint;
    पूर्णाङ्क cnt = 0;
    वर्ण special_chars[] = {pairs_sep, साँचो_val_sep, '\0'};

    यदि (!buffer || pairs_sep == '\0' || साँचो_val_sep == '\0' || pairs_sep == साँचो_val_sep ||
        pairs_sep == '\\' || साँचो_val_sep == '\\')
        फर्काऊ AVERROR(EINVAL);

    यदि (!av_dict_गन्ती(m)) {
        *buffer = av_strdup("");
        फर्काऊ *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    जबसम्म ((t = av_dict_iterate(m, t))) {
        यदि (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->साँचो, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &साँचो_val_sep, 1);
        av_bprint_escape(&bprint, t->मान, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    फर्काऊ av_bprint_finalize(&bprint, buffer);
}
