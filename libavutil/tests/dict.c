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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/dict.c"

ਸਥਿਰ ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *dict_iterate(ਅਚਲ AVDictionary *m,
                                             ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *prev)
{
    ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *dict_get = av_dict_get(m, "", prev, AV_DICT_IGNORE_SUFFIX);
    ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *dict_iterate = av_dict_iterate(m, prev);

    ਜੇ (dict_get != dict_iterate) {
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET(ਇੰਦਰਾਜ, mem) ((ਇੰਦਰਾਜ) ? (ਇੰਦਰਾਜ)->mem : "N/A")
        ਲਿਖੋ("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               prev, GET(prev, ਕੁੰਜੀ),
               dict_iterate, GET(dict_iterate, ਕੁੰਜੀ), GET(dict_iterate, ਮੁੱਲ),
               dict_get, GET(dict_get, ਕੁੰਜੀ), GET(dict_get, ਮੁੱਲ));
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ GET
    }
    ਵਾਪਸ dict_iterate;
}

ਸਥਿਰ ਖਾਲੀ print_dict(ਅਚਲ AVDictionary *m)
{
    ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *t = ਨਿਰਾ;
    ਅਚਲ ਅੱਖਰ *sep = "";
    ਜਦੋਂ ((t = dict_iterate(m, t))) {
        ਲਿਖੋ("%s%s %s", sep, t->ਕੁੰਜੀ, t->ਮੁੱਲ);
        sep = "   ";
    }
    ਲਿਖੋ("\n");
}

ਸਥਿਰ ਖਾਲੀ test_separators(ਅਚਲ AVDictionary *m, ਅਚਲ ਅੱਖਰ pair, ਅਚਲ ਅੱਖਰ val)
{
    AVDictionary *dict = ਨਿਰਾ;
    ਅੱਖਰ ਜੋੜੇ[] = {pair , '\0'};
    ਅੱਖਰ vals[]  = {val, '\0'};

    ਅੱਖਰ *ਬਫਰ = ਨਿਰਾ;
    ਪੂਰਨ ret;

    av_dict_copy(&dict, m, 0);
    print_dict(dict);
    av_dict_get_string(dict, &ਬਫਰ, val, pair);
    ਲਿਖੋ("%s\n", ਬਫਰ);
    av_dict_free(&dict);
    ret = av_dict_parse_string(&dict, ਬਫਰ, vals, ਜੋੜੇ, 0);
    ਲਿਖੋ("ret %d\n", ret);
    av_freep(&ਬਫਰ);
    print_dict(dict);
    av_dict_free(&dict);
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVDictionary *dict = ਨਿਰਾ;
    ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *e;
    ਅੱਖਰ *ਬਫਰ = ਨਿਰਾ;

    ਲਿਖੋ("Testing av_dict_get_string() and av_dict_parse_string()\n");
    av_dict_get_string(dict, &ਬਫਰ, '=', ',');
    ਲਿਖੋ("%s\n", ਬਫਰ);
    av_freep(&ਬਫਰ);
    av_dict_ਸੈੱਟ(&dict, "aaa", "aaa", 0);
    av_dict_ਸੈੱਟ(&dict, "b,b", "bbb", 0);
    av_dict_ਸੈੱਟ(&dict, "c=c", "ccc", 0);
    av_dict_ਸੈੱਟ(&dict, "ddd", "d,d", 0);
    av_dict_ਸੈੱਟ(&dict, "eee", "e=e", 0);
    av_dict_ਸੈੱਟ(&dict, "f,f", "f=f", 0);
    av_dict_ਸੈੱਟ(&dict, "g=g", "g,g", 0);
    test_separators(dict, ',', '=');
    av_dict_free(&dict);
    av_dict_ਸੈੱਟ(&dict, "aaa", "aaa", 0);
    av_dict_ਸੈੱਟ(&dict, "bbb", "bbb", 0);
    av_dict_ਸੈੱਟ(&dict, "ccc", "ccc", 0);
    av_dict_ਸੈੱਟ(&dict, "\\,=\'\"", "\\,=\'\"", 0);
    test_separators(dict, '"',  '=');
    test_separators(dict, '\'', '=');
    test_separators(dict, ',', '"');
    test_separators(dict, ',', '\'');
    test_separators(dict, '\'', '"');
    test_separators(dict, '"', '\'');
    av_dict_free(&dict);

    ਲਿਖੋ("\nTesting av_dict_set()\n");
    av_dict_ਸੈੱਟ(&dict, "a", "a", 0);
    av_dict_ਸੈੱਟ(&dict, "b", av_strdup("b"), AV_DICT_DONT_STRDUP_VAL);
    av_dict_ਸੈੱਟ(&dict, av_strdup("c"), "c", AV_DICT_DONT_STRDUP_ਕੁੰਜੀ);
    av_dict_ਸੈੱਟ(&dict, av_strdup("d"), av_strdup("d"), AV_DICT_DONT_STRDUP_ਕੁੰਜੀ | AV_DICT_DONT_STRDUP_VAL);
    av_dict_ਸੈੱਟ(&dict, "e", "e", AV_DICT_DONT_OVERWRITE);
    av_dict_ਸੈੱਟ(&dict, "e", "f", AV_DICT_DONT_OVERWRITE);
    av_dict_ਸੈੱਟ(&dict, "f", "f", 0);
    av_dict_ਸੈੱਟ(&dict, "f", ਨਿਰਾ, 0);
    av_dict_ਸੈੱਟ(&dict, "ff", "f", 0);
    av_dict_ਸੈੱਟ(&dict, "ff", "f", AV_DICT_APPEND);
    ਜੇ (av_dict_get(dict, ਨਿਰਾ, ਨਿਰਾ, 0))
        ਲਿਖੋ("av_dict_get() does not correctly handle NULL key.\n");
    e = ਨਿਰਾ;
    ਜਦੋਂ ((e = dict_iterate(dict, e)))
        ਲਿਖੋ("%s %s\n", e->ਕੁੰਜੀ, e->ਮੁੱਲ);
    av_dict_free(&dict);

    ਜੇ (av_dict_ਸੈੱਟ(&dict, ਨਿਰਾ, "a", 0) >= 0 ||
        av_dict_ਸੈੱਟ(&dict, ਨਿਰਾ, "b", 0) >= 0 ||
        av_dict_ਸੈੱਟ(&dict, ਨਿਰਾ, ਨਿਰਾ, AV_DICT_DONT_STRDUP_ਕੁੰਜੀ) >= 0 ||
        av_dict_ਸੈੱਟ(&dict, ਨਿਰਾ, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_ਗਿਣਤੀ(dict))
        ਲਿਖੋ("av_dict_set does not correctly handle NULL key\n");

    e = ਨਿਰਾ;
    ਜਦੋਂ ((e = dict_iterate(dict, e)))
        ਲਿਖੋ("'%s' '%s'\n", e->ਕੁੰਜੀ, e->ਮੁੱਲ);
    av_dict_free(&dict);


    //valgrind sensible test
    ਲਿਖੋ("\nTesting av_dict_set_int()\n");
    av_dict_ਸੈੱਟ_int(&dict, "1", 1, AV_DICT_DONT_STRDUP_VAL);
    av_dict_ਸੈੱਟ_int(&dict, av_strdup("2"), 2, AV_DICT_DONT_STRDUP_ਕੁੰਜੀ);
    av_dict_ਸੈੱਟ_int(&dict, av_strdup("3"), 3, AV_DICT_DONT_STRDUP_ਕੁੰਜੀ | AV_DICT_DONT_STRDUP_VAL);
    av_dict_ਸੈੱਟ_int(&dict, "4", 4, 0);
    av_dict_ਸੈੱਟ_int(&dict, "5", 5, AV_DICT_DONT_OVERWRITE);
    av_dict_ਸੈੱਟ_int(&dict, "5", 6, AV_DICT_DONT_OVERWRITE);
    av_dict_ਸੈੱਟ_int(&dict, "12", 1, 0);
    av_dict_ਸੈੱਟ_int(&dict, "12", 2, AV_DICT_APPEND);
    e = ਨਿਰਾ;
    ਜਦੋਂ ((e = dict_iterate(dict, e)))
        ਲਿਖੋ("%s %s\n", e->ਕੁੰਜੀ, e->ਮੁੱਲ);
    av_dict_free(&dict);

    //valgrind sensible test
    ਲਿਖੋ("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    ਜੇ (av_dict_ਸੈੱਟ(&dict, "key", "old", 0) < 0)
        ਵਾਪਸ 1;
    e = av_dict_get(dict, "key", ਨਿਰਾ, 0);
    ਜੇ (av_dict_ਸੈੱਟ(&dict, e->ਕੁੰਜੀ, "new val OK", 0) < 0)
        ਵਾਪਸ 1;
    e = av_dict_get(dict, "key", ਨਿਰਾ, 0);
    ਲਿਖੋ("%s\n", e->ਮੁੱਲ);
    ਜੇ (av_dict_ਸੈੱਟ(&dict, e->ਕੁੰਜੀ, e->ਮੁੱਲ, 0) < 0)
        ਵਾਪਸ 1;
    e = av_dict_get(dict, "key", ਨਿਰਾ, 0);
    ਲਿਖੋ("%s\n", e->ਮੁੱਲ);
    av_dict_free(&dict);

    ਵਾਪਸ 0;
}
