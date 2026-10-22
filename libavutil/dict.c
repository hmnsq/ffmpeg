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
    पूर्णाङ्क मोजणी;
    AVDictionaryEntry *elems;
    पूर्णाङ्क duplicate_किल्ल्या;
};

पूर्णाङ्क av_dict_मोजणी(ध्रुव AVDictionary *m)
{
    प्रत्यागम m ? m->मोजणी : 0;
}

ध्रुव AVDictionaryEntry *av_dict_iterate(ध्रुव AVDictionary *m,
                                         ध्रुव AVDictionaryEntry *prev)
{
    पूर्णाङ्क i = 0;

    यदि (!m)
        प्रत्यागम रिक्त;

    यदि (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    यदि (i >= m->मोजणी)
        प्रत्यागम रिक्त;

    प्रत्यागम &m->elems[i];
}

AVDictionaryEntry *av_dict_get(ध्रुव AVDictionary *m, ध्रुव वर्ण *किल्ली,
                               ध्रुव AVDictionaryEntry *prev, पूर्णाङ्क flags)
{
    ध्रुव AVDictionaryEntry *entry = prev;
    unsigned पूर्णाङ्क j;

    यदि (!किल्ली)
        प्रत्यागम रिक्त;

    यावत् ((entry = av_dict_iterate(m, entry))) {
        ध्रुव वर्ण *s = entry->किल्ली;
        यदि (flags & AV_DICT_MATCH_CASE)
            प्रति (j = 0; s[j] == किल्ली[j] && किल्ली[j]; j++)
                ;
        अन्यथा
            प्रति (j = 0; av_toupper(s[j]) == av_toupper(किल्ली[j]) && किल्ली[j]; j++)
                ;
        यदि (किल्ली[j])
            अनुवर्त;
        यदि (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            अनुवर्त;
        प्रत्यागम (AVDictionaryEntry *)entry;
    }
    प्रत्यागम रिक्त;
}

पूर्णाङ्क av_dict_set(AVDictionary **pm, ध्रुव वर्ण *किल्ली, ध्रुव वर्ण *मूल्य,
                पूर्णाङ्क flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = रिक्त;
    वर्ण *copy_किल्ली = रिक्त, *copy_मूल्य = रिक्त;
    पूर्णाङ्क err;

    यदि (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_मूल्य = (शून्य *)मूल्य;
    अन्यथा यदि (मूल्य)
        copy_मूल्य = av_strdup(मूल्य);
    यदि (!किल्ली) {
        err = AVERROR(EINVAL);
        गच्छ err_out;
    }
    यदि (flags & AV_DICT_DONT_STRDUP_किल्ली)
        copy_किल्ली = (शून्य *)किल्ली;
    अन्यथा
        copy_किल्ली = av_strdup(किल्ली);
    यदि (!copy_किल्ली || (मूल्य && !copy_मूल्य))
        गच्छ enomem;

    यदि (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, किल्ली, रिक्त, flags);
    } अन्यथा यदि (flags & AV_DICT_DEDUP) {
        यावत् ((tag = av_dict_get(m, किल्ली, tag, flags))) {
            यदि ((!मूल्य && !tag->मूल्य) ||
                (मूल्य && tag->मूल्य && !strcmp(मूल्य, tag->मूल्य))) {
                av_free(copy_किल्ली);
                av_free(copy_मूल्य);
                प्रत्यागम 0;
            }
        }
    }
    यदि (!m)
        m = *pm = av_mallocz(परिमाण(*m));
    यदि (!m)
        गच्छ enomem;

    यदि (tag) {
        यदि (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_किल्ली);
            av_free(copy_मूल्य);
            प्रत्यागम 0;
        }
        यदि (copy_मूल्य && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->मूल्य);
            size_t new_part_len = strlen(copy_मूल्य);
            size_t len = oldlen + new_part_len + 1;
            वर्ण *newval = av_realloc(tag->मूल्य, len);
            यदि (!newval)
                गच्छ enomem;
            memcpy(newval + oldlen, copy_मूल्य, new_part_len + 1);
            av_freep(&copy_मूल्य);
            copy_मूल्य = newval;
        } अन्यथा
            av_free(tag->मूल्य);
        av_free(tag->किल्ली);
        *tag = m->elems[--m->मोजणी];
    } अन्यथा यदि (copy_मूल्य) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->मोजणी + 1, परिमाण(*m->elems));
        यदि (!tmp)
            गच्छ enomem;
        m->elems = tmp;
    }
    यदि (copy_मूल्य) {
        m->elems[m->मोजणी].किल्ली = copy_किल्ली;
        m->elems[m->मोजणी].मूल्य = copy_मूल्य;
        m->मोजणी++;
        यदि (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_किल्ल्या = 1;
    } अन्यथा {
        err = 0;
        गच्छ end;
    }

    प्रत्यागम 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_मूल्य);
end:
    यदि (m && !m->मोजणी) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_किल्ली);
    प्रत्यागम err;
}

पूर्णाङ्क av_dict_set_int(AVDictionary **pm, ध्रुव वर्ण *किल्ली, int64_t मूल्य,
                पूर्णाङ्क flags)
{
    वर्ण valuestr[22];
    snprintf(valuestr, परिमाण(valuestr), "%"PRId64, मूल्य);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    प्रत्यागम av_dict_set(pm, किल्ली, valuestr, flags);
}

स्थिर पूर्णाङ्क parse_किल्ली_मूल्य_pair(AVDictionary **pm, ध्रुव वर्ण **buf,
                                ध्रुव वर्ण *किल्ली_val_sep, ध्रुव वर्ण *pairs_sep,
                                पूर्णाङ्क flags)
{
    वर्ण *किल्ली = av_get_token(buf, किल्ली_val_sep);
    वर्ण *val = रिक्त;
    पूर्णाङ्क ret;

    यदि (किल्ली && *किल्ली && strspn(*buf, किल्ली_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    यदि (किल्ली && *किल्ली && val && *val)
        ret = av_dict_set(pm, किल्ली, val, flags);
    अन्यथा
        ret = AVERROR(EINVAL);

    av_freep(&किल्ली);
    av_freep(&val);

    प्रत्यागम ret;
}

पूर्णाङ्क av_dict_parse_string(AVDictionary **pm, ध्रुव वर्ण *str,
                         ध्रुव वर्ण *किल्ली_val_sep, ध्रुव वर्ण *pairs_sep,
                         पूर्णाङ्क flags)
{
    पूर्णाङ्क ret;

    यदि (!str)
        प्रत्यागम 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_किल्ली | AV_DICT_DONT_STRDUP_VAL);

    यावत् (*str) {
        यदि ((ret = parse_किल्ली_मूल्य_pair(pm, &str, किल्ली_val_sep, pairs_sep, flags)) < 0)
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
        यावत् (m->मोजणी--) {
            av_freep(&m->elems[m->मोजणी].किल्ली);
            av_freep(&m->elems[m->मोजणी].मूल्य);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

पूर्णाङ्क av_dict_copy(AVDictionary **dst, ध्रुव AVDictionary *src, पूर्णाङ्क flags)
{
    ध्रुव AVDictionaryEntry *t = रिक्त;

    यदि (!*dst && src && src->मोजणी && !src->duplicate_किल्ल्या &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(परिमाण(*m));
        यदि (!m)
            प्रत्यागम AVERROR(ENOMEM);
        m->elems = av_calloc(src->मोजणी, परिमाण(*m->elems));
        यदि (!m->elems) {
            av_free(m);
            प्रत्यागम AVERROR(ENOMEM);
        }
        *dst = m;
        प्रति (पूर्णाङ्क i = 0; i < src->मोजणी; i++) {
            m->elems[i].किल्ली   = av_strdup(src->elems[i].किल्ली);
            m->elems[i].मूल्य = av_strdup(src->elems[i].मूल्य);
            m->मोजणी++;
            यदि (!m->elems[i].किल्ली || !m->elems[i].मूल्य) {
                av_dict_free(dst);
                प्रत्यागम AVERROR(ENOMEM);
            }
        }
        प्रत्यागम 0;
    }

    यावत् ((t = av_dict_iterate(src, t))) {
        पूर्णाङ्क ret = av_dict_set(dst, t->किल्ली, t->मूल्य, flags);
        यदि (ret < 0)
            प्रत्यागम ret;
    }

    प्रत्यागम 0;
}

पूर्णाङ्क av_dict_get_string(ध्रुव AVDictionary *m, वर्ण **buffer,
                       ध्रुव वर्ण किल्ली_val_sep, ध्रुव वर्ण pairs_sep)
{
    ध्रुव AVDictionaryEntry *t = रिक्त;
    AVBPrint bprint;
    पूर्णाङ्क cnt = 0;
    वर्ण special_chars[] = {pairs_sep, किल्ली_val_sep, '\0'};

    यदि (!buffer || pairs_sep == '\0' || किल्ली_val_sep == '\0' || pairs_sep == किल्ली_val_sep ||
        pairs_sep == '\\' || किल्ली_val_sep == '\\')
        प्रत्यागम AVERROR(EINVAL);

    यदि (!av_dict_मोजणी(m)) {
        *buffer = av_strdup("");
        प्रत्यागम *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    यावत् ((t = av_dict_iterate(m, t))) {
        यदि (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->किल्ली, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &किल्ली_val_sep, 1);
        av_bprint_escape(&bprint, t->मूल्य, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    प्रत्यागम av_bprint_finalize(&bprint, buffer);
}
