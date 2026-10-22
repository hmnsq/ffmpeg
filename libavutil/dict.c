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

#అన్తర్భావ <inttypes.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "avstring.h"
#అన్తర్భావ "dict.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "bprint.h"

నిర్మాణం AVDictionary {
    పూర్ణాంకం లెక్క;
    AVDictionary_నమోదు *elems;
    పూర్ణాంకం duplicate_కీలకాలు;
};

పూర్ణాంకం av_dict_లెక్క(స్థిరరాశి AVDictionary *m)
{
    తిరిగి m ? m->లెక్క : 0;
}

స్థిరరాశి AVDictionary_నమోదు *av_dict_iterate(స్థిరరాశి AVDictionary *m,
                                         స్థిరరాశి AVDictionary_నమోదు *prev)
{
    పూర్ణాంకం i = 0;

    ఒకవేళ (!m)
        తిరిగి ఖాళీ;

    ఒకవేళ (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    ఒకవేళ (i >= m->లెక్క)
        తిరిగి ఖాళీ;

    తిరిగి &m->elems[i];
}

AVDictionary_నమోదు *av_dict_get(స్థిరరాశి AVDictionary *m, స్థిరరాశి అక్షరం *కీలకం,
                               స్థిరరాశి AVDictionary_నమోదు *prev, పూర్ణాంకం flags)
{
    స్థిరరాశి AVDictionary_నమోదు *నమోదు_2 = prev;
    గుర్తులేని పూర్ణాంకం j;

    ఒకవేళ (!కీలకం)
        తిరిగి ఖాళీ;

    అయితే ((నమోదు_2 = av_dict_iterate(m, నమోదు_2))) {
        స్థిరరాశి అక్షరం *s = నమోదు_2->కీలకం;
        ఒకవేళ (flags & AV_DICT_సరిపోలిక_CASE)
            కొరకు (j = 0; s[j] == కీలకం[j] && కీలకం[j]; j++)
                ;
        లేకపోతే
            కొరకు (j = 0; av_toupper(s[j]) == av_toupper(కీలకం[j]) && కీలకం[j]; j++)
                ;
        ఒకవేళ (కీలకం[j])
            కొనసాగు;
        ఒకవేళ (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            కొనసాగు;
        తిరిగి (AVDictionary_నమోదు *)నమోదు_2;
    }
    తిరిగి ఖాళీ;
}

పూర్ణాంకం av_dict_సమితి(AVDictionary **pm, స్థిరరాశి అక్షరం *కీలకం, స్థిరరాశి అక్షరం *విలువ,
                పూర్ణాంకం flags)
{
    AVDictionary *m = *pm;
    AVDictionary_నమోదు *ట్యాగ్ = ఖాళీ;
    అక్షరం *copy_కీలకం = ఖాళీ, *copy_విలువ = ఖాళీ;
    పూర్ణాంకం err;

    ఒకవేళ (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_విలువ = (శూన్య *)విలువ;
    లేకపోతే ఒకవేళ (విలువ)
        copy_విలువ = av_strdup(విలువ);
    ఒకవేళ (!కీలకం) {
        err = AVERROR(EINVAL);
        వెళ్ళు err_బహిర్గతం;
    }
    ఒకవేళ (flags & AV_DICT_DONT_STRDUP_కీలకం)
        copy_కీలకం = (శూన్య *)కీలకం;
    లేకపోతే
        copy_కీలకం = av_strdup(కీలకం);
    ఒకవేళ (!copy_కీలకం || (విలువ && !copy_విలువ))
        వెళ్ళు enomem;

    ఒకవేళ (!(flags & AV_DICT_MULTIKEY)) {
        ట్యాగ్ = av_dict_get(m, కీలకం, ఖాళీ, flags);
    } లేకపోతే ఒకవేళ (flags & AV_DICT_DEDUP) {
        అయితే ((ట్యాగ్ = av_dict_get(m, కీలకం, ట్యాగ్, flags))) {
            ఒకవేళ ((!విలువ && !ట్యాగ్->విలువ) ||
                (విలువ && ట్యాగ్->విలువ && !strcmp(విలువ, ట్యాగ్->విలువ))) {
                av_free(copy_కీలకం);
                av_free(copy_విలువ);
                తిరిగి 0;
            }
        }
    }
    ఒకవేళ (!m)
        m = *pm = av_mallocz(పరిమాణం(*m));
    ఒకవేళ (!m)
        వెళ్ళు enomem;

    ఒకవేళ (ట్యాగ్) {
        ఒకవేళ (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_కీలకం);
            av_free(copy_విలువ);
            తిరిగి 0;
        }
        ఒకవేళ (copy_విలువ && flags & AV_DICT_APPEND) {
            size_t oldlen = అక్షరశ్రేణి_పొడవు(ట్యాగ్->విలువ);
            size_t new_part_len = అక్షరశ్రేణి_పొడవు(copy_విలువ);
            size_t len = oldlen + new_part_len + 1;
            అక్షరం *newval = av_realloc(ట్యాగ్->విలువ, len);
            ఒకవేళ (!newval)
                వెళ్ళు enomem;
            జ్ఞాపకం_నకలు(newval + oldlen, copy_విలువ, new_part_len + 1);
            av_freep(&copy_విలువ);
            copy_విలువ = newval;
        } లేకపోతే
            av_free(ట్యాగ్->విలువ);
        av_free(ట్యాగ్->కీలకం);
        *ట్యాగ్ = m->elems[--m->లెక్క];
    } లేకపోతే ఒకవేళ (copy_విలువ) {
        AVDictionary_నమోదు *tmp = av_realloc_array(m->elems,
                                                  m->లెక్క + 1, పరిమాణం(*m->elems));
        ఒకవేళ (!tmp)
            వెళ్ళు enomem;
        m->elems = tmp;
    }
    ఒకవేళ (copy_విలువ) {
        m->elems[m->లెక్క].కీలకం = copy_కీలకం;
        m->elems[m->లెక్క].విలువ = copy_విలువ;
        m->లెక్క++;
        ఒకవేళ (flags & (AV_DICT_సరిపోలిక_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_కీలకాలు = 1;
    } లేకపోతే {
        err = 0;
        వెళ్ళు చివర;
    }

    తిరిగి 0;

enomem:
    err = AVERROR(ENOMEM);
err_బహిర్గతం:
    av_free(copy_విలువ);
చివర:
    ఒకవేళ (m && !m->లెక్క) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_కీలకం);
    తిరిగి err;
}

పూర్ణాంకం av_dict_సమితి_int(AVDictionary **pm, స్థిరరాశి అక్షరం *కీలకం, int64_t విలువ,
                పూర్ణాంకం flags)
{
    అక్షరం valuestr[22];
    snprintf(valuestr, పరిమాణం(valuestr), "%"PRId64, విలువ);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    తిరిగి av_dict_సమితి(pm, కీలకం, valuestr, flags);
}

స్థిర పూర్ణాంకం parse_కీలకం_విలువ_pair(AVDictionary **pm, స్థిరరాశి అక్షరం **buf,
                                స్థిరరాశి అక్షరం *కీలకం_val_sep, స్థిరరాశి అక్షరం *జతలు_sep,
                                పూర్ణాంకం flags)
{
    అక్షరం *కీలకం = av_get_token(buf, కీలకం_val_sep);
    అక్షరం *val = ఖాళీ;
    పూర్ణాంకం ret;

    ఒకవేళ (కీలకం && *కీలకం && strspn(*buf, కీలకం_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, జతలు_sep);
    }

    ఒకవేళ (కీలకం && *కీలకం && val && *val)
        ret = av_dict_సమితి(pm, కీలకం, val, flags);
    లేకపోతే
        ret = AVERROR(EINVAL);

    av_freep(&కీలకం);
    av_freep(&val);

    తిరిగి ret;
}

పూర్ణాంకం av_dict_parse_string(AVDictionary **pm, స్థిరరాశి అక్షరం *str,
                         స్థిరరాశి అక్షరం *కీలకం_val_sep, స్థిరరాశి అక్షరం *జతలు_sep,
                         పూర్ణాంకం flags)
{
    పూర్ణాంకం ret;

    ఒకవేళ (!str)
        తిరిగి 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_కీలకం | AV_DICT_DONT_STRDUP_VAL);

    అయితే (*str) {
        ఒకవేళ ((ret = parse_కీలకం_విలువ_pair(pm, &str, కీలకం_val_sep, జతలు_sep, flags)) < 0)
            తిరిగి ret;

        ఒకవేళ (*str)
            str++;
    }

    తిరిగి 0;
}

శూన్య av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    ఒకవేళ (m) {
        అయితే (m->లెక్క--) {
            av_freep(&m->elems[m->లెక్క].కీలకం);
            av_freep(&m->elems[m->లెక్క].విలువ);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

పూర్ణాంకం av_dict_copy(AVDictionary **dst, స్థిరరాశి AVDictionary *src, పూర్ణాంకం flags)
{
    స్థిరరాశి AVDictionary_నమోదు *t = ఖాళీ;

    ఒకవేళ (!*dst && src && src->లెక్క && !src->duplicate_కీలకాలు &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(పరిమాణం(*m));
        ఒకవేళ (!m)
            తిరిగి AVERROR(ENOMEM);
        m->elems = av_calloc(src->లెక్క, పరిమాణం(*m->elems));
        ఒకవేళ (!m->elems) {
            av_free(m);
            తిరిగి AVERROR(ENOMEM);
        }
        *dst = m;
        కొరకు (పూర్ణాంకం i = 0; i < src->లెక్క; i++) {
            m->elems[i].కీలకం   = av_strdup(src->elems[i].కీలకం);
            m->elems[i].విలువ = av_strdup(src->elems[i].విలువ);
            m->లెక్క++;
            ఒకవేళ (!m->elems[i].కీలకం || !m->elems[i].విలువ) {
                av_dict_free(dst);
                తిరిగి AVERROR(ENOMEM);
            }
        }
        తిరిగి 0;
    }

    అయితే ((t = av_dict_iterate(src, t))) {
        పూర్ణాంకం ret = av_dict_సమితి(dst, t->కీలకం, t->విలువ, flags);
        ఒకవేళ (ret < 0)
            తిరిగి ret;
    }

    తిరిగి 0;
}

పూర్ణాంకం av_dict_get_string(స్థిరరాశి AVDictionary *m, అక్షరం **బఫరు,
                       స్థిరరాశి అక్షరం కీలకం_val_sep, స్థిరరాశి అక్షరం జతలు_sep)
{
    స్థిరరాశి AVDictionary_నమోదు *t = ఖాళీ;
    AVBPrint bprint;
    పూర్ణాంకం cnt = 0;
    అక్షరం special_chars[] = {జతలు_sep, కీలకం_val_sep, '\0'};

    ఒకవేళ (!బఫరు || జతలు_sep == '\0' || కీలకం_val_sep == '\0' || జతలు_sep == కీలకం_val_sep ||
        జతలు_sep == '\\' || కీలకం_val_sep == '\\')
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (!av_dict_లెక్క(m)) {
        *బఫరు = av_strdup("");
        తిరిగి *బఫరు ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_కొలత_UNLIMITED);
    అయితే ((t = av_dict_iterate(m, t))) {
        ఒకవేళ (cnt++)
            av_bprint_append_దత్తాంశం(&bprint, &జతలు_sep, 1);
        av_bprint_escape(&bprint, t->కీలకం, special_chars, AV_ESCAPE_బహుళకం_BACKSLASH, 0);
        av_bprint_append_దత్తాంశం(&bprint, &కీలకం_val_sep, 1);
        av_bprint_escape(&bprint, t->విలువ, special_chars, AV_ESCAPE_బహుళకం_BACKSLASH, 0);
    }
    తిరిగి av_bprint_finalize(&bprint, బఫరు);
}
