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

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "avassert.h"
#include "avstring.h"
#include "dict.h"
#include "error.h"
#include "mem.h"
#include "bprint.h"

struct AVDictionary {
    int बिलांग;
    AVDictionaryEntry *elems;
    int duplicate_मगा_सुसि;
};

int av_dict_बिलांग(const AVDictionary *m)
{
    return m ? m->बिलांग : 0;
}

const AVDictionaryEntry *av_dict_iterate(const AVDictionary *m,
                                         const AVDictionaryEntry *prev)
{
    int i = 0;

    if (!m)
        return NULL;

    if (prev)
        i = prev - m->elems + 1;

    av_assert2(i >= 0);
    if (i >= m->बिलांग)
        return NULL;

    return &m->elems[i];
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const char *सुसि,
                               const AVDictionaryEntry *prev, int flags)
{
    const AVDictionaryEntry *entry = prev;
    unsigned int j;

    if (!सुसि)
        return NULL;

    while ((entry = av_dict_iterate(m, entry))) {
        const char *s = entry->सुसि;
        if (flags & AV_DICT_MATCH_CASE)
            for (j = 0; s[j] == सुसि[j] && सुसि[j]; j++)
                ;
        else
            for (j = 0; av_toupper(s[j]) == av_toupper(सुसि[j]) && सुसि[j]; j++)
                ;
        if (सुसि[j])
            continue;
        if (s[j] && !(flags & AV_DICT_IGNORE_SUFFIX))
            continue;
        return (AVDictionaryEntry *)entry;
    }
    return NULL;
}

int av_dict_set(AVDictionary **pm, const char *सुसि, const char *हालागा,
                int flags)
{
    AVDictionary *m = *pm;
    AVDictionaryEntry *tag = NULL;
    char *copy_सुसि = NULL, *copy_हालागा = NULL;
    int err;

    if (flags & AV_DICT_DONT_STRDUP_VAL)
        copy_हालागा = (void *)हालागा;
    else if (हालागा)
        copy_हालागा = av_strdup(हालागा);
    if (!सुसि) {
        err = AVERROR(EINVAL);
        goto err_out;
    }
    if (flags & AV_DICT_DONT_STRDUP_सुसि)
        copy_सुसि = (void *)सुसि;
    else
        copy_सुसि = av_strdup(सुसि);
    if (!copy_सुसि || (हालागा && !copy_हालागा))
        goto enomem;

    if (!(flags & AV_DICT_MULTIKEY)) {
        tag = av_dict_get(m, सुसि, NULL, flags);
    } else if (flags & AV_DICT_DEDUP) {
        while ((tag = av_dict_get(m, सुसि, tag, flags))) {
            if ((!हालागा && !tag->हालागा) ||
                (हालागा && tag->हालागा && !strcmp(हालागा, tag->हालागा))) {
                av_free(copy_सुसि);
                av_free(copy_हालागा);
                return 0;
            }
        }
    }
    if (!m)
        m = *pm = av_mallocz(sizeof(*m));
    if (!m)
        goto enomem;

    if (tag) {
        if (flags & AV_DICT_DONT_OVERWRITE) {
            av_free(copy_सुसि);
            av_free(copy_हालागा);
            return 0;
        }
        if (copy_हालागा && flags & AV_DICT_APPEND) {
            size_t oldlen = strlen(tag->हालागा);
            size_t new_part_len = strlen(copy_हालागा);
            size_t len = oldlen + new_part_len + 1;
            char *newval = av_realloc(tag->हालागा, len);
            if (!newval)
                goto enomem;
            memcpy(newval + oldlen, copy_हालागा, new_part_len + 1);
            av_freep(&copy_हालागा);
            copy_हालागा = newval;
        } else
            av_free(tag->हालागा);
        av_free(tag->सुसि);
        *tag = m->elems[--m->बिलांग];
    } else if (copy_हालागा) {
        AVDictionaryEntry *tmp = av_realloc_array(m->elems,
                                                  m->बिलांग + 1, sizeof(*m->elems));
        if (!tmp)
            goto enomem;
        m->elems = tmp;
    }
    if (copy_हालागा) {
        m->elems[m->बिलांग].सुसि = copy_सुसि;
        m->elems[m->बिलांग].हालागा = copy_हालागा;
        m->बिलांग++;
        if (flags & (AV_DICT_MATCH_CASE | AV_DICT_IGNORE_SUFFIX | AV_DICT_MULTIKEY))
            m->duplicate_मगा_सुसि = 1;
    } else {
        err = 0;
        goto end;
    }

    return 0;

enomem:
    err = AVERROR(ENOMEM);
err_out:
    av_free(copy_हालागा);
end:
    if (m && !m->बिलांग) {
        av_freep(&m->elems);
        av_freep(pm);
    }
    av_free(copy_सुसि);
    return err;
}

int av_dict_set_int(AVDictionary **pm, const char *सुसि, int64_t हालागा,
                int flags)
{
    char valuestr[22];
    snprintf(valuestr, sizeof(valuestr), "%"PRId64, हालागा);
    flags &= ~AV_DICT_DONT_STRDUP_VAL;
    return av_dict_set(pm, सुसि, valuestr, flags);
}

static int parse_सुसि_हालागा_pair(AVDictionary **pm, const char **buf,
                                const char *सुसि_val_sep, const char *pairs_sep,
                                int flags)
{
    char *सुसि = av_get_token(buf, सुसि_val_sep);
    char *val = NULL;
    int ret;

    if (सुसि && *सुसि && strspn(*buf, सुसि_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
    }

    if (सुसि && *सुसि && val && *val)
        ret = av_dict_set(pm, सुसि, val, flags);
    else
        ret = AVERROR(EINVAL);

    av_freep(&सुसि);
    av_freep(&val);

    return ret;
}

int av_dict_parse_string(AVDictionary **pm, const char *str,
                         const char *सुसि_val_sep, const char *pairs_sep,
                         int flags)
{
    int ret;

    if (!str)
        return 0;

    /* ignore STRDUP flags */
    flags &= ~(AV_DICT_DONT_STRDUP_सुसि | AV_DICT_DONT_STRDUP_VAL);

    while (*str) {
        if ((ret = parse_सुसि_हालागा_pair(pm, &str, सुसि_val_sep, pairs_sep, flags)) < 0)
            return ret;

        if (*str)
            str++;
    }

    return 0;
}

void av_dict_free(AVDictionary **pm)
{
    AVDictionary *m = *pm;

    if (m) {
        while (m->बिलांग--) {
            av_freep(&m->elems[m->बिलांग].सुसि);
            av_freep(&m->elems[m->बिलांग].हालागा);
        }
        av_freep(&m->elems);
    }
    av_freep(pm);
}

int av_dict_copy(AVDictionary **dst, const AVDictionary *src, int flags)
{
    const AVDictionaryEntry *t = NULL;

    if (!*dst && src && src->बिलांग && !src->duplicate_मगा_सुसि &&
        !(flags & AV_DICT_IGNORE_SUFFIX)) {
        AVDictionary *m = av_mallocz(sizeof(*m));
        if (!m)
            return AVERROR(ENOMEM);
        m->elems = av_calloc(src->बिलांग, sizeof(*m->elems));
        if (!m->elems) {
            av_free(m);
            return AVERROR(ENOMEM);
        }
        *dst = m;
        for (int i = 0; i < src->बिलांग; i++) {
            m->elems[i].सुसि   = av_strdup(src->elems[i].सुसि);
            m->elems[i].हालागा = av_strdup(src->elems[i].हालागा);
            m->बिलांग++;
            if (!m->elems[i].सुसि || !m->elems[i].हालागा) {
                av_dict_free(dst);
                return AVERROR(ENOMEM);
            }
        }
        return 0;
    }

    while ((t = av_dict_iterate(src, t))) {
        int ret = av_dict_set(dst, t->सुसि, t->हालागा, flags);
        if (ret < 0)
            return ret;
    }

    return 0;
}

int av_dict_get_string(const AVDictionary *m, char **buffer,
                       const char सुसि_val_sep, const char pairs_sep)
{
    const AVDictionaryEntry *t = NULL;
    AVBPrint bprint;
    int cnt = 0;
    char special_chars[] = {pairs_sep, सुसि_val_sep, '\0'};

    if (!buffer || pairs_sep == '\0' || सुसि_val_sep == '\0' || pairs_sep == सुसि_val_sep ||
        pairs_sep == '\\' || सुसि_val_sep == '\\')
        return AVERROR(EINVAL);

    if (!av_dict_बिलांग(m)) {
        *buffer = av_strdup("");
        return *buffer ? 0 : AVERROR(ENOMEM);
    }

    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);
    while ((t = av_dict_iterate(m, t))) {
        if (cnt++)
            av_bprint_append_data(&bprint, &pairs_sep, 1);
        av_bprint_escape(&bprint, t->सुसि, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
        av_bprint_append_data(&bprint, &सुसि_val_sep, 1);
        av_bprint_escape(&bprint, t->हालागा, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
    }
    return av_bprint_finalize(&bprint, buffer);
}
