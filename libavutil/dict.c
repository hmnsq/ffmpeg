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

#ଅନ୍ତର୍ଭାଵ <inttypes.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "avstring.h"
#ଅନ୍ତର୍ଭାଵ "dict.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "bprint.h"

ସଂରଚନା AVDictionary {
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2;
    AVDictionaryEntry *elems;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା duplicate_ଚାବିଗୁଡ଼ିକ;
};

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_dict_ଗଣନା(ଅଚଳ AVDictionary *m)
{
    ଫେରନ୍ତୁ m ? m->ଗଣନା_2 : 0;
}

ଅଚଳ AVDictionaryEntry *av_dict_iterate(ଅଚଳ AVDictionary *m,
                                         ଅଚଳ AVDictionaryEntry *prev)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0;

    ଯଦି (!m)
        ଫେରନ୍ତୁ ଖାଲି;

    ଯଦି (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    ଯଦି (i >= m->ଗଣନା_2)
        ଫେରନ୍ତୁ ଖାଲି;

    ଫେରନ୍ତୁ &m->elems[i];
}

AVDictionaryEntry *av_dict_get(ଅଚଳ AVDictionary *m, ଅଚଳ ଅକ୍ଷର *ଚାବି,
                               ଅଚଳ AVDictionaryEntry *prev, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଅଚଳ AVDictionaryEntry *entry = prev;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j;

    ଯଦି (!ଚାବି)
        ଫେରନ୍ତୁ ଖାଲି;

    ଯେତେବେଳେ ((entry = av_dict_iterate(m, entry))) {
        ଅଚଳ ଅକ୍ଷର *s = entry->ଚାବି;
        ଯଦି (flags & AV_DICT_MATCH_CASE)
            ପାଇଁ (j = 0; s[j] == ଚାବି[j] && ଚାବି[j]; j++)
                ;
        ଅନ୍ୟଥା
            ପାଇଁ (j = 0; av_toupper(s[j]) == av_toupper(ଚାବି[j]) && ଚାବି[j]; j++)
                ;
        ଯଦି (ଚାବି[j])
            ଜାରି;
        ଯଦି (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            ଜାରି;
        ଫେରନ୍ତୁ (AVDictionaryEntry *)entry;
    }
    ଫେରନ୍ତୁ ଖାଲି;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_dict_set(AVDictionary **pm, ଅଚଳ ଅକ୍ଷର *ଚାବି, ଅଚଳ ଅକ୍ଷର *ମୂଲ୍ୟ,
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = ଖାଲି;
    ଅକ୍ଷର *copy_ଚାବି = ଖାଲି, *copy_ମୂଲ୍ୟ = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    ଯଦି (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_ମୂଲ୍ୟ = (ଶୂନ୍ୟ *)ମୂଲ୍ୟ;
    ଅନ୍ୟଥା ଯଦି (ମୂଲ୍ୟ)
        copy_ମୂଲ୍ୟ = av_strdup(ମୂଲ୍ୟ);
    ଯଦି (!ଚାବି) {
        err = AVERROR(EINVAL);
        ଯାଅ err_out;
    }
    ଯଦି (flags & AV_DICT_DONT_STRDUP_ଚାବି)
        copy_ଚାବି = (ଶୂନ୍ୟ *)ଚାବି;
    ଅନ୍ୟଥା
        copy_ଚାବି = av_strdup(ଚାବି);
    ଯଦି (!copy_ଚାବି || (ମୂଲ୍ୟ && !copy_ମୂଲ୍ୟ))
        ଯାଅ enomem;

    ଯଦି (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, ଚାବି, ଖାଲି, flags);
    } ଅନ୍ୟଥା ଯଦି (flags & AV_DICT_DEDUP) {
        ଯେତେବେଳେ ((tag = av_dict_get(m, ଚାବି, tag, flags))) {
            ଯଦି ((!ମୂଲ୍ୟ && !tag->ମୂଲ୍ୟ) ||
                (ମୂଲ୍ୟ && tag->ମୂଲ୍ୟ && !strcmp(ମୂଲ୍ୟ, tag->ମୂଲ୍ୟ))) {
                av_free(copy_ଚାବି);
                av_free(copy_ମୂଲ୍ୟ);
                ଫେରନ୍ତୁ 0;
            }
        }
    }
    ଯଦି (!m)
        m = *pm = av_mallocz(ଆକାର(*m));
    ଯଦି (!m)
        ଯାଅ enomem;

    ଯଦି (tag) {
        ଯଦି (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_ଚାବି);
            av_free(copy_ମୂଲ୍ୟ);
            ଫେରନ୍ତୁ 0;
        }
        ଯଦି (copy_ମୂଲ୍ୟ && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->ମୂଲ୍ୟ);
            size_t new_part_len = strlen(copy_ମୂଲ୍ୟ);
            size_t len = oldlen + new_part_len + 1;
            ଅକ୍ଷର *newval = av_realloc(tag->ମୂଲ୍ୟ, len);
            ଯଦି (!newval)
                ଯାଅ enomem;
            memcpy(newval + oldlen, copy_ମୂଲ୍ୟ, new_part_len + 1);
            av_freep(&copy_ମୂଲ୍ୟ);
            copy_ମୂଲ୍ୟ = newval;
        } ଅନ୍ୟଥା
            av_free(tag->ମୂଲ୍ୟ);
        av_free(tag->ଚାବି);
        *tag = m->elems[--m->ଗଣନା_2];
    } ଅନ୍ୟଥା ଯଦି (copy_ମୂଲ୍ୟ) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->ଗଣନା_2 + 1, ଆକାର(*m->elems));
        ଯଦି (!tmp)
            ଯାଅ enomem;
        m->elems = tmp;
    }
    ଯଦି (copy_ମୂଲ୍ୟ) {
        m->elems[m->ଗଣନା_2].ଚାବି = copy_ଚାବି;
        m->elems[m->ଗଣନା_2].ମୂଲ୍ୟ = copy_ମୂଲ୍ୟ;
        m->ଗଣନା_2++;
        ଯଦି (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_ଚାବିଗୁଡ଼ିକ = 1;
    } ଅନ୍ୟଥା {
        err = 0;
        ଯାଅ end;
    }

    ଫେରନ୍ତୁ 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_ମୂଲ୍ୟ);
end:
    ଯଦି (m && !m->ଗଣନା_2) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_ଚାବି);
    ଫେରନ୍ତୁ err;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_dict_set_int(AVDictionary **pm, ଅଚଳ ଅକ୍ଷର *ଚାବି, int64_t ମୂଲ୍ୟ,
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଅକ୍ଷର valuestr[22];
    snprintf(valuestr, ଆକାର(valuestr), "%"PRId64, ମୂଲ୍ୟ);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    ଫେରନ୍ତୁ av_dict_set(pm, ଚାବି, valuestr, flags);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା parse_ଚାବି_ମୂଲ୍ୟ_pair(AVDictionary **pm, ଅଚଳ ଅକ୍ଷର **buf,
                                ଅଚଳ ଅକ୍ଷର *ଚାବି_val_sep, ଅଚଳ ଅକ୍ଷର *pairs_sep,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଅକ୍ଷର *ଚାବି = av_get_token(buf, ଚାବି_val_sep);
    ଅକ୍ଷର *val = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (ଚାବି && *ଚାବି && strspn(*buf, ଚାବି_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    ଯଦି (ଚାବି && *ଚାବି && val && *val)
        ret = av_dict_set(pm, ଚାବି, val, flags);
    ଅନ୍ୟଥା
        ret = AVERROR(EINVAL);

    av_freep(&ଚାବି);
    av_freep(&val);

    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_dict_parse_string(AVDictionary **pm, ଅଚଳ ଅକ୍ଷର *str,
                         ଅଚଳ ଅକ୍ଷର *ଚାବି_val_sep, ଅଚଳ ଅକ୍ଷର *pairs_sep,
                         ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!str)
        ଫେରନ୍ତୁ 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_ଚାବି | AV_DICT_DONT_STRDUP_VAL);

    ଯେତେବେଳେ (*str) {
        ଯଦି ((ret = parse_ଚାବି_ମୂଲ୍ୟ_pair(pm, &str, ଚାବି_val_sep, pairs_sep, flags)) < 0)
            ଫେରନ୍ତୁ ret;

        ଯଦି (*str)
            str++;
    }

    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    ଯଦି (m) {
        ଯେତେବେଳେ (m->ଗଣନା_2--) {
            av_freep(&m->elems[m->ଗଣନା_2].ଚାବି);
            av_freep(&m->elems[m->ଗଣନା_2].ମୂଲ୍ୟ);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_dict_copy(AVDictionary **dst, ଅଚଳ AVDictionary *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଅଚଳ AVDictionaryEntry *t = ଖାଲି;

    ଯଦି (!*dst && src && src->ଗଣନା_2 && !src->duplicate_ଚାବିଗୁଡ଼ିକ &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(ଆକାର(*m));
        ଯଦି (!m)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        m->elems = av_calloc(src->ଗଣନା_2, ଆକାର(*m->elems));
        ଯଦି (!m->elems) {
            av_free(m);
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }
        *dst = m;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < src->ଗଣନା_2; i++) {
            m->elems[i].ଚାବି   = av_strdup(src->elems[i].ଚାବି);
            m->elems[i].ମୂଲ୍ୟ = av_strdup(src->elems[i].ମୂଲ୍ୟ);
            m->ଗଣନା_2++;
            ଯଦି (!m->elems[i].ଚାବି || !m->elems[i].ମୂଲ୍ୟ) {
                av_dict_free(dst);
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            }
        }
        ଫେରନ୍ତୁ 0;
    }

    ଯେତେବେଳେ ((t = av_dict_iterate(src, t))) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = av_dict_set(dst, t->ଚାବି, t->ମୂଲ୍ୟ, flags);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_dict_get_string(ଅଚଳ AVDictionary *m, ଅକ୍ଷର **buffer,
                       ଅଚଳ ଅକ୍ଷର ଚାବି_val_sep, ଅଚଳ ଅକ୍ଷର pairs_sep)
{
    ଅଚଳ AVDictionaryEntry *t = ଖାଲି;
    AVBPrint bprint;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cnt = 0;
    ଅକ୍ଷର special_chars[] = {pairs_sep, ଚାବି_val_sep, '\0'};

    ଯଦି (!buffer || pairs_sep == '\0' || ଚାବି_val_sep == '\0' || pairs_sep == ଚାବି_val_sep ||
        pairs_sep == '\\' || ଚାବି_val_sep == '\\')
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (!av_dict_ଗଣନା(m)) {
        *buffer = av_strdup("");
        ଫେରନ୍ତୁ *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    ଯେତେବେଳେ ((t = av_dict_iterate(m, t))) {
        ଯଦି (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->ଚାବି, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &ଚାବି_val_sep, 1);
        av_bprint_escape(&bprint, t->ମୂଲ୍ୟ, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    ଫେରନ୍ତୁ av_bprint_finalize(&bprint, buffer);
}
