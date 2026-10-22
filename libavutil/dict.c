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
    AVDictionary_प्रविष्टिः *elems;
    पूर्णाङ्क duplicate_कुञ्चिकाः;
};

पूर्णाङ्क av_dict_गणनम्(ध्रुव AVDictionary *m)
{
    प्रत्यागम m ? m->गणनम् : 0;
}

ध्रुव AVDictionary_प्रविष्टिः *av_dict_iterate(ध्रुव AVDictionary *m,
                                         ध्रुव AVDictionary_प्रविष्टिः *पूर्व)
{
    पूर्णाङ्क i = 0;

    यदि (!m)
        प्रत्यागम रिक्त;

    यदि (पूर्व)
        i = पूर्व - m->elems + 1;

    av_assert2(i >= 0);
    यदि (i >= m->गणनम्)
        प्रत्यागम रिक्त;

    प्रत्यागम &m->elems[i];
}

AVDictionary_प्रविष्टिः *av_dict_get(ध्रुव AVDictionary *m, ध्रुव वर्ण *कुञ्चिका,
                               ध्रुव AVDictionary_प्रविष्टिः *पूर्व, पूर्णाङ्क flags)
{
    ध्रुव AVDictionary_प्रविष्टिः *प्रविष्टिः = पूर्व;
    अचिह्नित पूर्णाङ्क j;

    यदि (!कुञ्चिका)
        प्रत्यागम रिक्त;

    यावत् ((प्रविष्टिः = av_dict_iterate(m, प्रविष्टिः))) {
        ध्रुव वर्ण *s = प्रविष्टिः->कुञ्चिका;
        यदि (flags & AV_DICT_मेलनम्_CASE)
            प्रति (j = 0; s[j] == कुञ्चिका[j] && कुञ्चिका[j]; j++)
                ;
        अन्यथा
            प्रति (j = 0; av_toupper(s[j]) == av_toupper(कुञ्चिका[j]) && कुञ्चिका[j]; j++)
                ;
        यदि (कुञ्चिका[j])
            अनुवर्त;
        यदि (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            अनुवर्त;
        प्रत्यागम (AVDictionary_प्रविष्टिः *)प्रविष्टिः;
    }
    प्रत्यागम रिक्त;
}

पूर्णाङ्क av_dict_समुच्चयः(AVDictionary **pm, ध्रुव वर्ण *कुञ्चिका, ध्रुव वर्ण *मानम्,
                पूर्णाङ्क flags)
{
    AVDictionary *m = *pm;
    AVDictionary_प्रविष्टिः *चिह्नकम् = रिक्त;
    वर्ण *copy_कुञ्चिका = रिक्त, *copy_मानम् = रिक्त;
    पूर्णाङ्क err;

    यदि (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_मानम् = (शून्य *)मानम्;
    अन्यथा यदि (मानम्)
        copy_मानम् = av_strdup(मानम्);
    यदि (!कुञ्चिका) {
        err = AVERROR(EINVAL);
        गच्छ err_बहिर्गमनम्;
    }
    यदि (flags & AV_DICT_DONT_STRDUP_कुञ्चिका)
        copy_कुञ्चिका = (शून्य *)कुञ्चिका;
    अन्यथा
        copy_कुञ्चिका = av_strdup(कुञ्चिका);
    यदि (!copy_कुञ्चिका || (मानम् && !copy_मानम्))
        गच्छ enomem;

    यदि (!(flags & AV_DICT_MULTIKEY)) {
        चिह्नकम् = av_dict_get(m, कुञ्चिका, रिक्त, flags);
    } अन्यथा यदि (flags & AV_DICT_DEDUP) {
        यावत् ((चिह्नकम् = av_dict_get(m, कुञ्चिका, चिह्नकम्, flags))) {
            यदि ((!मानम् && !चिह्नकम्->मानम्) ||
                (मानम् && चिह्नकम्->मानम् && !वाक्यं_तुलय(मानम्, चिह्नकम्->मानम्))) {
                av_free(copy_कुञ्चिका);
                av_free(copy_मानम्);
                प्रत्यागम 0;
            }
        }
    }
    यदि (!m)
        m = *pm = av_mallocz(परिमाण(*m));
    यदि (!m)
        गच्छ enomem;

    यदि (चिह्नकम्) {
        यदि (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_कुञ्चिका);
            av_free(copy_मानम्);
            प्रत्यागम 0;
        }
        यदि (copy_मानम् && flags & AV_DICT_APPEND) {
            size_t oldlen = वाक्यदैर्घ्यम्(चिह्नकम्->मानम्);
            size_t new_part_len = वाक्यदैर्घ्यम्(copy_मानम्);
            size_t len = oldlen + new_part_len + 1;
            वर्ण *newval = av_realloc(चिह्नकम्->मानम्, len);
            यदि (!newval)
                गच्छ enomem;
            स्मृतिं_प्रतिलिख(newval + oldlen, copy_मानम्, new_part_len + 1);
            av_freep(&copy_मानम्);
            copy_मानम् = newval;
        } अन्यथा
            av_free(चिह्नकम्->मानम्);
        av_free(चिह्नकम्->कुञ्चिका);
        *चिह्नकम् = m->elems[--m->गणनम्];
    } अन्यथा यदि (copy_मानम्) {
        AVDictionary_प्रविष्टिः *tmp = av_realloc_array(m->elems,
                                                  m->गणनम् + 1, परिमाण(*m->elems));
        यदि (!tmp)
            गच्छ enomem;
        m->elems = tmp;
    }
    यदि (copy_मानम्) {
        m->elems[m->गणनम्].कुञ्चिका = copy_कुञ्चिका;
        m->elems[m->गणनम्].मानम् = copy_मानम्;
        m->गणनम्++;
        यदि (flags & (AV_DICT_मेलनम्_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_कुञ्चिकाः = 1;
    } अन्यथा {
        err = 0;
        गच्छ अन्तः_2;
    }

    प्रत्यागम 0;

enomem:
    err = AVERROR(ENOMEM);
err_बहिर्गमनम्:
    av_free(copy_मानम्);
अन्तः_2:
    यदि (m && !m->गणनम्) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_कुञ्चिका);
    प्रत्यागम err;
}

पूर्णाङ्क av_dict_समुच्चयः_int(AVDictionary **pm, ध्रुव वर्ण *कुञ्चिका, int64_t मानम्,
                पूर्णाङ्क flags)
{
    वर्ण valuestr[22];
    snprintf(valuestr, परिमाण(valuestr), "%"PRId64, मानम्);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    प्रत्यागम av_dict_समुच्चयः(pm, कुञ्चिका, valuestr, flags);
}

स्थिर पूर्णाङ्क parse_कुञ्चिका_मानम्_pair(AVDictionary **pm, ध्रुव वर्ण **buf,
                                ध्रुव वर्ण *कुञ्चिका_val_sep, ध्रुव वर्ण *युग्मानि_sep,
                                पूर्णाङ्क flags)
{
    वर्ण *कुञ्चिका = av_get_token(buf, कुञ्चिका_val_sep);
    वर्ण *val = रिक्त;
    पूर्णाङ्क ret;

    यदि (कुञ्चिका && *कुञ्चिका && strspn(*buf, कुञ्चिका_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, युग्मानि_sep);
    }

    यदि (कुञ्चिका && *कुञ्चिका && val && *val)
        ret = av_dict_समुच्चयः(pm, कुञ्चिका, val, flags);
    अन्यथा
        ret = AVERROR(EINVAL);

    av_freep(&कुञ्चिका);
    av_freep(&val);

    प्रत्यागम ret;
}

पूर्णाङ्क av_dict_parse_string(AVDictionary **pm, ध्रुव वर्ण *str,
                         ध्रुव वर्ण *कुञ्चिका_val_sep, ध्रुव वर्ण *युग्मानि_sep,
                         पूर्णाङ्क flags)
{
    पूर्णाङ्क ret;

    यदि (!str)
        प्रत्यागम 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_कुञ्चिका | AV_DICT_DONT_STRDUP_VAL);

    यावत् (*str) {
        यदि ((ret = parse_कुञ्चिका_मानम्_pair(pm, &str, कुञ्चिका_val_sep, युग्मानि_sep, flags)) < 0)
            प्रत्यागम ret;

        यदि (*str)
            str++;
    }

    प्रत्यागम 0;
}

शून्य av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    यदि (m) {
        यावत् (m->गणनम्--) {
            av_freep(&m->elems[m->गणनम्].कुञ्चिका);
            av_freep(&m->elems[m->गणनम्].मानम्);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

पूर्णाङ्क av_dict_copy(AVDictionary **dst, ध्रुव AVDictionary *src, पूर्णाङ्क flags)
{
    ध्रुव AVDictionary_प्रविष्टिः *t = रिक्त;

    यदि (!*dst && src && src->गणनम् && !src->duplicate_कुञ्चिकाः &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(परिमाण(*m));
        यदि (!m)
            प्रत्यागम AVERROR(ENOMEM);
        m->elems = av_calloc(src->गणनम्, परिमाण(*m->elems));
        यदि (!m->elems) {
            av_free(m);
            प्रत्यागम AVERROR(ENOMEM);
        }
        *dst = m;
        प्रति (पूर्णाङ्क i = 0; i < src->गणनम्; i++) {
            m->elems[i].कुञ्चिका   = av_strdup(src->elems[i].कुञ्चिका);
            m->elems[i].मानम् = av_strdup(src->elems[i].मानम्);
            m->गणनम्++;
            यदि (!m->elems[i].कुञ्चिका || !m->elems[i].मानम्) {
                av_dict_free(dst);
                प्रत्यागम AVERROR(ENOMEM);
            }
        }
        प्रत्यागम 0;
    }

    यावत् ((t = av_dict_iterate(src, t))) {
        पूर्णाङ्क ret = av_dict_समुच्चयः(dst, t->कुञ्चिका, t->मानम्, flags);
        यदि (ret < 0)
            प्रत्यागम ret;
    }

    प्रत्यागम 0;
}

पूर्णाङ्क av_dict_get_string(ध्रुव AVDictionary *m, वर्ण **बफर,
                       ध्रुव वर्ण कुञ्चिका_val_sep, ध्रुव वर्ण युग्मानि_sep)
{
    ध्रुव AVDictionary_प्रविष्टिः *t = रिक्त;
    AVBPrint bprint;
    पूर्णाङ्क cnt = 0;
    वर्ण special_chars[] = {युग्मानि_sep, कुञ्चिका_val_sep, '\0'};

    यदि (!बफर || युग्मानि_sep == '\0' || कुञ्चिका_val_sep == '\0' || युग्मानि_sep == कुञ्चिका_val_sep ||
        युग्मानि_sep == '\\' || कुञ्चिका_val_sep == '\\')
        प्रत्यागम AVERROR(EINVAL);

    यदि (!av_dict_गणनम्(m)) {
        *बफर = av_strdup("");
        प्रत्यागम *बफर ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_आकार_UNLIMITED);
    यावत् ((t = av_dict_iterate(m, t))) {
        यदि (cnt++)
            av_bprint_append_दत्त(&bprint, &युग्मानि_sep, 1);
        av_bprint_escape(&bprint, t->कुञ्चिका, special_chars, AV_ESCAPE_बहुलकम्_BACKSLASH, 0);
        av_bprint_append_दत्त(&bprint, &कुञ्चिका_val_sep, 1);
        av_bprint_escape(&bprint, t->मानम्, special_chars, AV_ESCAPE_बहुलकम्_BACKSLASH, 0);
    }
    प्रत्यागम av_bprint_finalize(&bprint, बफर);
}
