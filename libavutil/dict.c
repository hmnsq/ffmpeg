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
    पूर्णाङ्क गणनम्;
    AVDictionaryEntry *elems;
    पूर्णाङ्क duplicate_कुञ्चिकाः;
};

पूर्णाङ्क av_dict_गणनम्(ध्रुव AVDictionary *m)
{
    प्रत्यागम m ? m->गणनम् : 0;
}

ध्रुव AVDictionaryEntry *av_dict_iterate(ध्रुव AVDictionary *m,
                                         ध्रुव AVDictionaryEntry *prev)
{
    पूर्णाङ्क i = 0;

    जइ (!m)
        प्रत्यागम रिक्त;

    जइ (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    जइ (i >= m->गणनम्)
        प्रत्यागम रिक्त;

    प्रत्यागम &m->elems[i];
}

AVDictionaryEntry *av_dict_get(ध्रुव AVDictionary *m, ध्रुव वर्ण *कुञ्चिका,
                               ध्रुव AVDictionaryEntry *prev, पूर्णाङ्क flags)
{
    ध्रुव AVDictionaryEntry *entry = prev;
    unsigned पूर्णाङ्क j;

    जइ (!कुञ्चिका)
        प्रत्यागम रिक्त;

    जाव ((entry = av_dict_iterate(m, entry))) {
        ध्रुव वर्ण *s = entry->कुञ्चिका;
        जइ (flags & AV_DICT_MATCH_CASE)
            प्रति (j = 0; s[j] == कुञ्चिका[j] && कुञ्चिका[j]; j++)
                ;
        अण्णहा
            प्रति (j = 0; av_toupper(s[j]) == av_toupper(कुञ्चिका[j]) && कुञ्चिका[j]; j++)
                ;
        जइ (कुञ्चिका[j])
            अनुवर्त;
        जइ (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            अनुवर्त;
        प्रत्यागम (AVDictionaryEntry *)entry;
    }
    प्रत्यागम रिक्त;
}

पूर्णाङ्क av_dict_set(AVDictionary **pm, ध्रुव वर्ण *कुञ्चिका, ध्रुव वर्ण *मानम्,
                पूर्णाङ्क flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = रिक्त;
    वर्ण *copy_कुञ्चिका = रिक्त, *copy_मानम् = रिक्त;
    पूर्णाङ्क err;

    जइ (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_मानम् = (शून्य *)मानम्;
    अण्णहा जइ (मानम्)
        copy_मानम् = av_strdup(मानम्);
    जइ (!कुञ्चिका) {
        err = AVERROR(EINVAL);
        गच्छ err_out;
    }
    जइ (flags & AV_DICT_DONT_STRDUP_कुञ्चिका)
        copy_कुञ्चिका = (शून्य *)कुञ्चिका;
    अण्णहा
        copy_कुञ्चिका = av_strdup(कुञ्चिका);
    जइ (!copy_कुञ्चिका || (मानम् && !copy_मानम्))
        गच्छ enomem;

    जइ (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, कुञ्चिका, रिक्त, flags);
    } अण्णहा जइ (flags & AV_DICT_DEDUP) {
        जाव ((tag = av_dict_get(m, कुञ्चिका, tag, flags))) {
            जइ ((!मानम् && !tag->मानम्) ||
                (मानम् && tag->मानम् && !strcmp(मानम्, tag->मानम्))) {
                av_free(copy_कुञ्चिका);
                av_free(copy_मानम्);
                प्रत्यागम 0;
            }
        }
    }
    जइ (!m)
        m = *pm = av_mallocz(परिमाण(*m));
    जइ (!m)
        गच्छ enomem;

    जइ (tag) {
        जइ (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_कुञ्चिका);
            av_free(copy_मानम्);
            प्रत्यागम 0;
        }
        जइ (copy_मानम् && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->मानम्);
            size_t new_part_len = strlen(copy_मानम्);
            size_t len = oldlen + new_part_len + 1;
            वर्ण *newval = av_realloc(tag->मानम्, len);
            जइ (!newval)
                गच्छ enomem;
            memcpy(newval + oldlen, copy_मानम्, new_part_len + 1);
            av_freep(&copy_मानम्);
            copy_मानम् = newval;
        } अण्णहा
            av_free(tag->मानम्);
        av_free(tag->कुञ्चिका);
        *tag = m->elems[--m->गणनम्];
    } अण्णहा जइ (copy_मानम्) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->गणनम् + 1, परिमाण(*m->elems));
        जइ (!tmp)
            गच्छ enomem;
        m->elems = tmp;
    }
    जइ (copy_मानम्) {
        m->elems[m->गणनम्].कुञ्चिका = copy_कुञ्चिका;
        m->elems[m->गणनम्].मानम् = copy_मानम्;
        m->गणनम्++;
        जइ (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_कुञ्चिकाः = 1;
    } अण्णहा {
        err = 0;
        गच्छ end;
    }

    प्रत्यागम 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_मानम्);
end:
    जइ (m && !m->गणनम्) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_कुञ्चिका);
    प्रत्यागम err;
}

पूर्णाङ्क av_dict_set_int(AVDictionary **pm, ध्रुव वर्ण *कुञ्चिका, int64_t मानम्,
                पूर्णाङ्क flags)
{
    वर्ण valuestr[22];
    snprintf(valuestr, परिमाण(valuestr), "%"PRId64, मानम्);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    प्रत्यागम av_dict_set(pm, कुञ्चिका, valuestr, flags);
}

स्थिर पूर्णाङ्क parse_कुञ्चिका_मानम्_pair(AVDictionary **pm, ध्रुव वर्ण **buf,
                                ध्रुव वर्ण *कुञ्चिका_val_sep, ध्रुव वर्ण *pairs_sep,
                                पूर्णाङ्क flags)
{
    वर्ण *कुञ्चिका = av_get_token(buf, कुञ्चिका_val_sep);
    वर्ण *val = रिक्त;
    पूर्णाङ्क ret;

    जइ (कुञ्चिका && *कुञ्चिका && strspn(*buf, कुञ्चिका_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    जइ (कुञ्चिका && *कुञ्चिका && val && *val)
        ret = av_dict_set(pm, कुञ्चिका, val, flags);
    अण्णहा
        ret = AVERROR(EINVAL);

    av_freep(&कुञ्चिका);
    av_freep(&val);

    प्रत्यागम ret;
}

पूर्णाङ्क av_dict_parse_string(AVDictionary **pm, ध्रुव वर्ण *str,
                         ध्रुव वर्ण *कुञ्चिका_val_sep, ध्रुव वर्ण *pairs_sep,
                         पूर्णाङ्क flags)
{
    पूर्णाङ्क ret;

    जइ (!str)
        प्रत्यागम 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_कुञ्चिका | AV_DICT_DONT_STRDUP_VAL);

    जाव (*str) {
        जइ ((ret = parse_कुञ्चिका_मानम्_pair(pm, &str, कुञ्चिका_val_sep, pairs_sep, flags)) < 0)
            प्रत्यागम ret;

        जइ (*str)
            str++;
    }

    प्रत्यागम 0;
}

शून्य av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    जइ (m) {
        जाव (m->गणनम्--) {
            av_freep(&m->elems[m->गणनम्].कुञ्चिका);
            av_freep(&m->elems[m->गणनम्].मानम्);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

पूर्णाङ्क av_dict_copy(AVDictionary **dst, ध्रुव AVDictionary *src, पूर्णाङ्क flags)
{
    ध्रुव AVDictionaryEntry *t = रिक्त;

    जइ (!*dst && src && src->गणनम् && !src->duplicate_कुञ्चिकाः &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(परिमाण(*m));
        जइ (!m)
            प्रत्यागम AVERROR(ENOMEM);
        m->elems = av_calloc(src->गणनम्, परिमाण(*m->elems));
        जइ (!m->elems) {
            av_free(m);
            प्रत्यागम AVERROR(ENOMEM);
        }
        *dst = m;
        प्रति (पूर्णाङ्क i = 0; i < src->गणनम्; i++) {
            m->elems[i].कुञ्चिका   = av_strdup(src->elems[i].कुञ्चिका);
            m->elems[i].मानम् = av_strdup(src->elems[i].मानम्);
            m->गणनम्++;
            जइ (!m->elems[i].कुञ्चिका || !m->elems[i].मानम्) {
                av_dict_free(dst);
                प्रत्यागम AVERROR(ENOMEM);
            }
        }
        प्रत्यागम 0;
    }

    जाव ((t = av_dict_iterate(src, t))) {
        पूर्णाङ्क ret = av_dict_set(dst, t->कुञ्चिका, t->मानम्, flags);
        जइ (ret < 0)
            प्रत्यागम ret;
    }

    प्रत्यागम 0;
}

पूर्णाङ्क av_dict_get_string(ध्रुव AVDictionary *m, वर्ण **buffer,
                       ध्रुव वर्ण कुञ्चिका_val_sep, ध्रुव वर्ण pairs_sep)
{
    ध्रुव AVDictionaryEntry *t = रिक्त;
    AVBPrint bprint;
    पूर्णाङ्क cnt = 0;
    वर्ण special_chars[] = {pairs_sep, कुञ्चिका_val_sep, '\0'};

    जइ (!buffer || pairs_sep == '\0' || कुञ्चिका_val_sep == '\0' || pairs_sep == कुञ्चिका_val_sep ||
        pairs_sep == '\\' || कुञ्चिका_val_sep == '\\')
        प्रत्यागम AVERROR(EINVAL);

    जइ (!av_dict_गणनम्(m)) {
        *buffer = av_strdup("");
        प्रत्यागम *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    जाव ((t = av_dict_iterate(m, t))) {
        जइ (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->कुञ्चिका, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &कुञ्चिका_val_sep, 1);
        av_bprint_escape(&bprint, t->मानम्, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    प्रत्यागम av_bprint_finalize(&bprint, buffer);
}
