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

#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

#ಅನ್ತರ್ಭಾವ "libavutil/dict.c"

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *dict_iterate(ಸ್ಥಿರಾಂಕ AVDictionary *m,
                                             ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *prev)
{
    ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *dict_get = av_dict_get(m, "", prev, AV_DICT_IGNORE_SUFFIX);
    ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *dict_iterate = av_dict_iterate(m, prev);

    ಆದರೆ (dict_get != dict_iterate) {
#ವ್ಯಾಖ್ಯಾನಿಸು GET(ನಮೂದು, mem) ((ನಮೂದು) ? (ನಮೂದು)->mem : "N/A")
        ಬರೆ("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               prev, GET(prev, ಕೀಲಿ),
               dict_iterate, GET(dict_iterate, ಕೀಲಿ), GET(dict_iterate, ಮೌಲ್ಯ),
               dict_get, GET(dict_get, ಕೀಲಿ), GET(dict_get, ಮೌಲ್ಯ));
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು GET
    }
    ಹಿಂತಿರುಗಿ dict_iterate;
}

ಸ್ಥಿರ ಶೂನ್ಯ print_dict(ಸ್ಥಿರಾಂಕ AVDictionary *m)
{
    ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *t = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *sep = "";
    ಆಗ ((t = dict_iterate(m, t))) {
        ಬರೆ("%s%s %s", sep, t->ಕೀಲಿ, t->ಮೌಲ್ಯ);
        sep = "   ";
    }
    ಬರೆ("\n");
}

ಸ್ಥಿರ ಶೂನ್ಯ test_separators(ಸ್ಥಿರಾಂಕ AVDictionary *m, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ pair, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ val)
{
    AVDictionary *dict = ಖಾಲಿ;
    ಅಕ್ಷರ ಜೋಡಿಗಳು[] = {pair , '\0'};
    ಅಕ್ಷರ vals[]  = {val, '\0'};

    ಅಕ್ಷರ *ಬಫರ್ = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ ret;

    av_dict_copy(&dict, m, 0);
    print_dict(dict);
    av_dict_get_string(dict, &ಬಫರ್, val, pair);
    ಬರೆ("%s\n", ಬಫರ್);
    av_dict_free(&dict);
    ret = av_dict_parse_string(&dict, ಬಫರ್, vals, ಜೋಡಿಗಳು, 0);
    ಬರೆ("ret %d\n", ret);
    av_freep(&ಬಫರ್);
    print_dict(dict);
    av_dict_free(&dict);
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVDictionary *dict = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *e;
    ಅಕ್ಷರ *ಬಫರ್ = ಖಾಲಿ;

    ಬರೆ("Testing av_dict_get_string() and av_dict_parse_string()\n");
    av_dict_get_string(dict, &ಬಫರ್, '=', ',');
    ಬರೆ("%s\n", ಬಫರ್);
    av_freep(&ಬಫರ್);
    av_dict_ಗಣ(&dict, "aaa", "aaa", 0);
    av_dict_ಗಣ(&dict, "b,b", "bbb", 0);
    av_dict_ಗಣ(&dict, "c=c", "ccc", 0);
    av_dict_ಗಣ(&dict, "ddd", "d,d", 0);
    av_dict_ಗಣ(&dict, "eee", "e=e", 0);
    av_dict_ಗಣ(&dict, "f,f", "f=f", 0);
    av_dict_ಗಣ(&dict, "g=g", "g,g", 0);
    test_separators(dict, ',', '=');
    av_dict_free(&dict);
    av_dict_ಗಣ(&dict, "aaa", "aaa", 0);
    av_dict_ಗಣ(&dict, "bbb", "bbb", 0);
    av_dict_ಗಣ(&dict, "ccc", "ccc", 0);
    av_dict_ಗಣ(&dict, "\\,=\'\"", "\\,=\'\"", 0);
    test_separators(dict, '"',  '=');
    test_separators(dict, '\'', '=');
    test_separators(dict, ',', '"');
    test_separators(dict, ',', '\'');
    test_separators(dict, '\'', '"');
    test_separators(dict, '"', '\'');
    av_dict_free(&dict);

    ಬರೆ("\nTesting av_dict_set()\n");
    av_dict_ಗಣ(&dict, "a", "a", 0);
    av_dict_ಗಣ(&dict, "b", av_strdup("b"), AV_DICT_DONT_STRDUP_VAL);
    av_dict_ಗಣ(&dict, av_strdup("c"), "c", AV_DICT_DONT_STRDUP_ಕೀಲಿ);
    av_dict_ಗಣ(&dict, av_strdup("d"), av_strdup("d"), AV_DICT_DONT_STRDUP_ಕೀಲಿ | AV_DICT_DONT_STRDUP_VAL);
    av_dict_ಗಣ(&dict, "e", "e", AV_DICT_DONT_OVERWRITE);
    av_dict_ಗಣ(&dict, "e", "f", AV_DICT_DONT_OVERWRITE);
    av_dict_ಗಣ(&dict, "f", "f", 0);
    av_dict_ಗಣ(&dict, "f", ಖಾಲಿ, 0);
    av_dict_ಗಣ(&dict, "ff", "f", 0);
    av_dict_ಗಣ(&dict, "ff", "f", AV_DICT_APPEND);
    ಆದರೆ (av_dict_get(dict, ಖಾಲಿ, ಖಾಲಿ, 0))
        ಬರೆ("av_dict_get() does not correctly handle NULL key.\n");
    e = ಖಾಲಿ;
    ಆಗ ((e = dict_iterate(dict, e)))
        ಬರೆ("%s %s\n", e->ಕೀಲಿ, e->ಮೌಲ್ಯ);
    av_dict_free(&dict);

    ಆದರೆ (av_dict_ಗಣ(&dict, ಖಾಲಿ, "a", 0) >= 0 ||
        av_dict_ಗಣ(&dict, ಖಾಲಿ, "b", 0) >= 0 ||
        av_dict_ಗಣ(&dict, ಖಾಲಿ, ಖಾಲಿ, AV_DICT_DONT_STRDUP_ಕೀಲಿ) >= 0 ||
        av_dict_ಗಣ(&dict, ಖಾಲಿ, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_ಎಣಿಕೆ(dict))
        ಬರೆ("av_dict_set does not correctly handle NULL key\n");

    e = ಖಾಲಿ;
    ಆಗ ((e = dict_iterate(dict, e)))
        ಬರೆ("'%s' '%s'\n", e->ಕೀಲಿ, e->ಮೌಲ್ಯ);
    av_dict_free(&dict);


    //valgrind sensible test
    ಬರೆ("\nTesting av_dict_set_int()\n");
    av_dict_ಗಣ_int(&dict, "1", 1, AV_DICT_DONT_STRDUP_VAL);
    av_dict_ಗಣ_int(&dict, av_strdup("2"), 2, AV_DICT_DONT_STRDUP_ಕೀಲಿ);
    av_dict_ಗಣ_int(&dict, av_strdup("3"), 3, AV_DICT_DONT_STRDUP_ಕೀಲಿ | AV_DICT_DONT_STRDUP_VAL);
    av_dict_ಗಣ_int(&dict, "4", 4, 0);
    av_dict_ಗಣ_int(&dict, "5", 5, AV_DICT_DONT_OVERWRITE);
    av_dict_ಗಣ_int(&dict, "5", 6, AV_DICT_DONT_OVERWRITE);
    av_dict_ಗಣ_int(&dict, "12", 1, 0);
    av_dict_ಗಣ_int(&dict, "12", 2, AV_DICT_APPEND);
    e = ಖಾಲಿ;
    ಆಗ ((e = dict_iterate(dict, e)))
        ಬರೆ("%s %s\n", e->ಕೀಲಿ, e->ಮೌಲ್ಯ);
    av_dict_free(&dict);

    //valgrind sensible test
    ಬರೆ("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    ಆದರೆ (av_dict_ಗಣ(&dict, "key", "old", 0) < 0)
        ಹಿಂತಿರುಗಿ 1;
    e = av_dict_get(dict, "key", ಖಾಲಿ, 0);
    ಆದರೆ (av_dict_ಗಣ(&dict, e->ಕೀಲಿ, "new val OK", 0) < 0)
        ಹಿಂತಿರುಗಿ 1;
    e = av_dict_get(dict, "key", ಖಾಲಿ, 0);
    ಬರೆ("%s\n", e->ಮೌಲ್ಯ);
    ಆದರೆ (av_dict_ಗಣ(&dict, e->ಕೀಲಿ, e->ಮೌಲ್ಯ, 0) < 0)
        ಹಿಂತಿರುಗಿ 1;
    e = av_dict_get(dict, "key", ಖಾಲಿ, 0);
    ಬರೆ("%s\n", e->ಮೌಲ್ಯ);
    av_dict_free(&dict);

    ಹಿಂತಿರುಗಿ 0;
}
