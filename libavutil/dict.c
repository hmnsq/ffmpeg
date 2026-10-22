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

#ਅਨ੍ਤਰ੍ਭਾਵ <inttypes.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "dict.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "bprint.h"

ਬਣਤਰ AVDictionary {
    ਪੂਰਨ ਗਿਣਤੀ_2;
    AVDictionary_ਇੰਦਰਾਜ *elems;
    ਪੂਰਨ duplicate_ਕੁੰਜੀਆਂ;
};

ਪੂਰਨ av_dict_ਗਿਣਤੀ(ਅਚਲ AVDictionary *m)
{
    ਵਾਪਸ m ? m->ਗਿਣਤੀ_2 : 0;
}

ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *av_dict_iterate(ਅਚਲ AVDictionary *m,
                                         ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *prev)
{
    ਪੂਰਨ i = 0;

    ਜੇ (!m)
        ਵਾਪਸ ਨਿਰਾ;

    ਜੇ (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    ਜੇ (i >= m->ਗਿਣਤੀ_2)
        ਵਾਪਸ ਨਿਰਾ;

    ਵਾਪਸ &m->elems[i];
}

AVDictionary_ਇੰਦਰਾਜ *av_dict_get(ਅਚਲ AVDictionary *m, ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ,
                               ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *prev, ਪੂਰਨ flags)
{
    ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *ਇੰਦਰਾਜ = prev;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j;

    ਜੇ (!ਕੁੰਜੀ)
        ਵਾਪਸ ਨਿਰਾ;

    ਜਦੋਂ ((ਇੰਦਰਾਜ = av_dict_iterate(m, ਇੰਦਰਾਜ))) {
        ਅਚਲ ਅੱਖਰ *s = ਇੰਦਰਾਜ->ਕੁੰਜੀ;
        ਜੇ (flags & AV_DICT_ਮੇਲ_CASE)
            ਲਈ (j = 0; s[j] == ਕੁੰਜੀ[j] && ਕੁੰਜੀ[j]; j++)
                ;
        ਨਹੀਂਤਾਂ
            ਲਈ (j = 0; av_toupper(s[j]) == av_toupper(ਕੁੰਜੀ[j]) && ਕੁੰਜੀ[j]; j++)
                ;
        ਜੇ (ਕੁੰਜੀ[j])
            ਜਾਰੀ;
        ਜੇ (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            ਜਾਰੀ;
        ਵਾਪਸ (AVDictionary_ਇੰਦਰਾਜ *)ਇੰਦਰਾਜ;
    }
    ਵਾਪਸ ਨਿਰਾ;
}

ਪੂਰਨ av_dict_ਸੈੱਟ(AVDictionary **pm, ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ, ਅਚਲ ਅੱਖਰ *ਮੁੱਲ,
                ਪੂਰਨ flags)
{
    AVDictionary *m = *pm;
    AVDictionary_ਇੰਦਰਾਜ *ਟੈਗ = ਨਿਰਾ;
    ਅੱਖਰ *copy_ਕੁੰਜੀ = ਨਿਰਾ, *copy_ਮੁੱਲ = ਨਿਰਾ;
    ਪੂਰਨ err;

    ਜੇ (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_ਮੁੱਲ = (ਖਾਲੀ *)ਮੁੱਲ;
    ਨਹੀਂਤਾਂ ਜੇ (ਮੁੱਲ)
        copy_ਮੁੱਲ = av_strdup(ਮੁੱਲ);
    ਜੇ (!ਕੁੰਜੀ) {
        err = AVERROR(EINVAL);
        ਜਾਓ err_ਬਾਹਰਲਾ;
    }
    ਜੇ (flags & AV_DICT_DONT_STRDUP_ਕੁੰਜੀ)
        copy_ਕੁੰਜੀ = (ਖਾਲੀ *)ਕੁੰਜੀ;
    ਨਹੀਂਤਾਂ
        copy_ਕੁੰਜੀ = av_strdup(ਕੁੰਜੀ);
    ਜੇ (!copy_ਕੁੰਜੀ || (ਮੁੱਲ && !copy_ਮੁੱਲ))
        ਜਾਓ enomem;

    ਜੇ (!(flags & AV_DICT_MULTIKEY)) {
        ਟੈਗ = av_dict_get(m, ਕੁੰਜੀ, ਨਿਰਾ, flags);
    } ਨਹੀਂਤਾਂ ਜੇ (flags & AV_DICT_DEDUP) {
        ਜਦੋਂ ((ਟੈਗ = av_dict_get(m, ਕੁੰਜੀ, ਟੈਗ, flags))) {
            ਜੇ ((!ਮੁੱਲ && !ਟੈਗ->ਮੁੱਲ) ||
                (ਮੁੱਲ && ਟੈਗ->ਮੁੱਲ && !strcmp(ਮੁੱਲ, ਟੈਗ->ਮੁੱਲ))) {
                av_free(copy_ਕੁੰਜੀ);
                av_free(copy_ਮੁੱਲ);
                ਵਾਪਸ 0;
            }
        }
    }
    ਜੇ (!m)
        m = *pm = av_mallocz(ਆਕਾਰ(*m));
    ਜੇ (!m)
        ਜਾਓ enomem;

    ਜੇ (ਟੈਗ) {
        ਜੇ (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_ਕੁੰਜੀ);
            av_free(copy_ਮੁੱਲ);
            ਵਾਪਸ 0;
        }
        ਜੇ (copy_ਮੁੱਲ && flags & AV_DICT_APPEND) {
            size_t oldlen = ਲੜੀ_ਲੰਬਾਈ(ਟੈਗ->ਮੁੱਲ);
            size_t new_part_len = ਲੜੀ_ਲੰਬਾਈ(copy_ਮੁੱਲ);
            size_t len = oldlen + new_part_len + 1;
            ਅੱਖਰ *newval = av_realloc(ਟੈਗ->ਮੁੱਲ, len);
            ਜੇ (!newval)
                ਜਾਓ enomem;
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(newval + oldlen, copy_ਮੁੱਲ, new_part_len + 1);
            av_freep(&copy_ਮੁੱਲ);
            copy_ਮੁੱਲ = newval;
        } ਨਹੀਂਤਾਂ
            av_free(ਟੈਗ->ਮੁੱਲ);
        av_free(ਟੈਗ->ਕੁੰਜੀ);
        *ਟੈਗ = m->elems[--m->ਗਿਣਤੀ_2];
    } ਨਹੀਂਤਾਂ ਜੇ (copy_ਮੁੱਲ) {
        AVDictionary_ਇੰਦਰਾਜ *tmp = av_realloc_array(m->elems,
                                                  m->ਗਿਣਤੀ_2 + 1, ਆਕਾਰ(*m->elems));
        ਜੇ (!tmp)
            ਜਾਓ enomem;
        m->elems = tmp;
    }
    ਜੇ (copy_ਮੁੱਲ) {
        m->elems[m->ਗਿਣਤੀ_2].ਕੁੰਜੀ = copy_ਕੁੰਜੀ;
        m->elems[m->ਗਿਣਤੀ_2].ਮੁੱਲ = copy_ਮੁੱਲ;
        m->ਗਿਣਤੀ_2++;
        ਜੇ (flags & (AV_DICT_ਮੇਲ_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_ਕੁੰਜੀਆਂ = 1;
    } ਨਹੀਂਤਾਂ {
        err = 0;
        ਜਾਓ ਸਿਰਾ;
    }

    ਵਾਪਸ 0;

enomem:
    err = AVERROR(ENOMEM);
err_ਬਾਹਰਲਾ:
    av_free(copy_ਮੁੱਲ);
ਸਿਰਾ:
    ਜੇ (m && !m->ਗਿਣਤੀ_2) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_ਕੁੰਜੀ);
    ਵਾਪਸ err;
}

ਪੂਰਨ av_dict_ਸੈੱਟ_int(AVDictionary **pm, ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ, int64_t ਮੁੱਲ,
                ਪੂਰਨ flags)
{
    ਅੱਖਰ valuestr[22];
    snprintf(valuestr, ਆਕਾਰ(valuestr), "%"PRId64, ਮੁੱਲ);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    ਵਾਪਸ av_dict_ਸੈੱਟ(pm, ਕੁੰਜੀ, valuestr, flags);
}

ਸਥਿਰ ਪੂਰਨ parse_ਕੁੰਜੀ_ਮੁੱਲ_pair(AVDictionary **pm, ਅਚਲ ਅੱਖਰ **buf,
                                ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ_val_sep, ਅਚਲ ਅੱਖਰ *ਜੋੜੇ_sep,
                                ਪੂਰਨ flags)
{
    ਅੱਖਰ *ਕੁੰਜੀ = av_get_token(buf, ਕੁੰਜੀ_val_sep);
    ਅੱਖਰ *val = ਨਿਰਾ;
    ਪੂਰਨ ret;

    ਜੇ (ਕੁੰਜੀ && *ਕੁੰਜੀ && strspn(*buf, ਕੁੰਜੀ_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, ਜੋੜੇ_sep);
    }

    ਜੇ (ਕੁੰਜੀ && *ਕੁੰਜੀ && val && *val)
        ret = av_dict_ਸੈੱਟ(pm, ਕੁੰਜੀ, val, flags);
    ਨਹੀਂਤਾਂ
        ret = AVERROR(EINVAL);

    av_freep(&ਕੁੰਜੀ);
    av_freep(&val);

    ਵਾਪਸ ret;
}

ਪੂਰਨ av_dict_parse_string(AVDictionary **pm, ਅਚਲ ਅੱਖਰ *str,
                         ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ_val_sep, ਅਚਲ ਅੱਖਰ *ਜੋੜੇ_sep,
                         ਪੂਰਨ flags)
{
    ਪੂਰਨ ret;

    ਜੇ (!str)
        ਵਾਪਸ 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_ਕੁੰਜੀ | AV_DICT_DONT_STRDUP_VAL);

    ਜਦੋਂ (*str) {
        ਜੇ ((ret = parse_ਕੁੰਜੀ_ਮੁੱਲ_pair(pm, &str, ਕੁੰਜੀ_val_sep, ਜੋੜੇ_sep, flags)) < 0)
            ਵਾਪਸ ret;

        ਜੇ (*str)
            str++;
    }

    ਵਾਪਸ 0;
}

ਖਾਲੀ av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    ਜੇ (m) {
        ਜਦੋਂ (m->ਗਿਣਤੀ_2--) {
            av_freep(&m->elems[m->ਗਿਣਤੀ_2].ਕੁੰਜੀ);
            av_freep(&m->elems[m->ਗਿਣਤੀ_2].ਮੁੱਲ);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

ਪੂਰਨ av_dict_copy(AVDictionary **dst, ਅਚਲ AVDictionary *src, ਪੂਰਨ flags)
{
    ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *t = ਨਿਰਾ;

    ਜੇ (!*dst && src && src->ਗਿਣਤੀ_2 && !src->duplicate_ਕੁੰਜੀਆਂ &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(ਆਕਾਰ(*m));
        ਜੇ (!m)
            ਵਾਪਸ AVERROR(ENOMEM);
        m->elems = av_calloc(src->ਗਿਣਤੀ_2, ਆਕਾਰ(*m->elems));
        ਜੇ (!m->elems) {
            av_free(m);
            ਵਾਪਸ AVERROR(ENOMEM);
        }
        *dst = m;
        ਲਈ (ਪੂਰਨ i = 0; i < src->ਗਿਣਤੀ_2; i++) {
            m->elems[i].ਕੁੰਜੀ   = av_strdup(src->elems[i].ਕੁੰਜੀ);
            m->elems[i].ਮੁੱਲ = av_strdup(src->elems[i].ਮੁੱਲ);
            m->ਗਿਣਤੀ_2++;
            ਜੇ (!m->elems[i].ਕੁੰਜੀ || !m->elems[i].ਮੁੱਲ) {
                av_dict_free(dst);
                ਵਾਪਸ AVERROR(ENOMEM);
            }
        }
        ਵਾਪਸ 0;
    }

    ਜਦੋਂ ((t = av_dict_iterate(src, t))) {
        ਪੂਰਨ ret = av_dict_ਸੈੱਟ(dst, t->ਕੁੰਜੀ, t->ਮੁੱਲ, flags);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_dict_get_string(ਅਚਲ AVDictionary *m, ਅੱਖਰ **ਬਫਰ,
                       ਅਚਲ ਅੱਖਰ ਕੁੰਜੀ_val_sep, ਅਚਲ ਅੱਖਰ ਜੋੜੇ_sep)
{
    ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *t = ਨਿਰਾ;
    AVBPrint bprint;
    ਪੂਰਨ cnt = 0;
    ਅੱਖਰ special_chars[] = {ਜੋੜੇ_sep, ਕੁੰਜੀ_val_sep, '\0'};

    ਜੇ (!ਬਫਰ || ਜੋੜੇ_sep == '\0' || ਕੁੰਜੀ_val_sep == '\0' || ਜੋੜੇ_sep == ਕੁੰਜੀ_val_sep ||
        ਜੋੜੇ_sep == '\\' || ਕੁੰਜੀ_val_sep == '\\')
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (!av_dict_ਗਿਣਤੀ(m)) {
        *ਬਫਰ = av_strdup("");
        ਵਾਪਸ *ਬਫਰ ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_ਮਾਪ_UNLIMITED);
    ਜਦੋਂ ((t = av_dict_iterate(m, t))) {
        ਜੇ (cnt++)
            av_bprint_append_ਅੰਕੜੇ(&bprint, &ਜੋੜੇ_sep, 1);
        av_bprint_escape(&bprint, t->ਕੁੰਜੀ, special_chars, AV_ESCAPE_ਬਹੁਲਕ_BACKSLASH, 0);
        av_bprint_append_ਅੰਕੜੇ(&bprint, &ਕੁੰਜੀ_val_sep, 1);
        av_bprint_escape(&bprint, t->ਮੁੱਲ, special_chars, AV_ESCAPE_ਬਹੁਲਕ_BACKSLASH, 0);
    }
    ਵਾਪਸ av_bprint_finalize(&bprint, ਬਫਰ);
}
