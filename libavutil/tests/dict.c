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

#అన్తర్భావ "libavutil/mem.h"

#అన్తర్భావ "libavutil/dict.c"

స్థిర స్థిరరాశి AVDictionary_నమోదు *dict_iterate(స్థిరరాశి AVDictionary *m,
                                             స్థిరరాశి AVDictionary_నమోదు *prev)
{
    స్థిరరాశి AVDictionary_నమోదు *dict_get = av_dict_get(m, "", prev, AV_DICT_IGNORE_SUFFIX);
    స్థిరరాశి AVDictionary_నమోదు *dict_iterate = av_dict_iterate(m, prev);

    ఒకవేళ (dict_get != dict_iterate) {
#నిర్వచించు GET(నమోదు_2, mem) ((నమోదు_2) ? (నమోదు_2)->mem : "N/A")
        రాయి("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               prev, GET(prev, కీలకం),
               dict_iterate, GET(dict_iterate, కీలకం), GET(dict_iterate, విలువ),
               dict_get, GET(dict_get, కీలకం), GET(dict_get, విలువ));
#నిర్వచనం_రద్దు GET
    }
    తిరిగి dict_iterate;
}

స్థిర శూన్య print_dict(స్థిరరాశి AVDictionary *m)
{
    స్థిరరాశి AVDictionary_నమోదు *t = ఖాళీ;
    స్థిరరాశి అక్షరం *sep = "";
    అయితే ((t = dict_iterate(m, t))) {
        రాయి("%s%s %s", sep, t->కీలకం, t->విలువ);
        sep = "   ";
    }
    రాయి("\n");
}

స్థిర శూన్య test_separators(స్థిరరాశి AVDictionary *m, స్థిరరాశి అక్షరం pair, స్థిరరాశి అక్షరం val)
{
    AVDictionary *dict = ఖాళీ;
    అక్షరం జతలు[] = {pair , '\0'};
    అక్షరం vals[]  = {val, '\0'};

    అక్షరం *బఫరు = ఖాళీ;
    పూర్ణాంకం ret;

    av_dict_copy(&dict, m, 0);
    print_dict(dict);
    av_dict_get_string(dict, &బఫరు, val, pair);
    రాయి("%s\n", బఫరు);
    av_dict_free(&dict);
    ret = av_dict_parse_string(&dict, బఫరు, vals, జతలు, 0);
    రాయి("ret %d\n", ret);
    av_freep(&బఫరు);
    print_dict(dict);
    av_dict_free(&dict);
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVDictionary *dict = ఖాళీ;
    స్థిరరాశి AVDictionary_నమోదు *e;
    అక్షరం *బఫరు = ఖాళీ;

    రాయి("Testing av_dict_get_string() and av_dict_parse_string()\n");
    av_dict_get_string(dict, &బఫరు, '=', ',');
    రాయి("%s\n", బఫరు);
    av_freep(&బఫరు);
    av_dict_సమితి(&dict, "aaa", "aaa", 0);
    av_dict_సమితి(&dict, "b,b", "bbb", 0);
    av_dict_సమితి(&dict, "c=c", "ccc", 0);
    av_dict_సమితి(&dict, "ddd", "d,d", 0);
    av_dict_సమితి(&dict, "eee", "e=e", 0);
    av_dict_సమితి(&dict, "f,f", "f=f", 0);
    av_dict_సమితి(&dict, "g=g", "g,g", 0);
    test_separators(dict, ',', '=');
    av_dict_free(&dict);
    av_dict_సమితి(&dict, "aaa", "aaa", 0);
    av_dict_సమితి(&dict, "bbb", "bbb", 0);
    av_dict_సమితి(&dict, "ccc", "ccc", 0);
    av_dict_సమితి(&dict, "\\,=\'\"", "\\,=\'\"", 0);
    test_separators(dict, '"',  '=');
    test_separators(dict, '\'', '=');
    test_separators(dict, ',', '"');
    test_separators(dict, ',', '\'');
    test_separators(dict, '\'', '"');
    test_separators(dict, '"', '\'');
    av_dict_free(&dict);

    రాయి("\nTesting av_dict_set()\n");
    av_dict_సమితి(&dict, "a", "a", 0);
    av_dict_సమితి(&dict, "b", av_strdup("b"), AV_DICT_DONT_STRDUP_VAL);
    av_dict_సమితి(&dict, av_strdup("c"), "c", AV_DICT_DONT_STRDUP_కీలకం);
    av_dict_సమితి(&dict, av_strdup("d"), av_strdup("d"), AV_DICT_DONT_STRDUP_కీలకం | AV_DICT_DONT_STRDUP_VAL);
    av_dict_సమితి(&dict, "e", "e", AV_DICT_DONT_OVERWRITE);
    av_dict_సమితి(&dict, "e", "f", AV_DICT_DONT_OVERWRITE);
    av_dict_సమితి(&dict, "f", "f", 0);
    av_dict_సమితి(&dict, "f", ఖాళీ, 0);
    av_dict_సమితి(&dict, "ff", "f", 0);
    av_dict_సమితి(&dict, "ff", "f", AV_DICT_APPEND);
    ఒకవేళ (av_dict_get(dict, ఖాళీ, ఖాళీ, 0))
        రాయి("av_dict_get() does not correctly handle NULL key.\n");
    e = ఖాళీ;
    అయితే ((e = dict_iterate(dict, e)))
        రాయి("%s %s\n", e->కీలకం, e->విలువ);
    av_dict_free(&dict);

    ఒకవేళ (av_dict_సమితి(&dict, ఖాళీ, "a", 0) >= 0 ||
        av_dict_సమితి(&dict, ఖాళీ, "b", 0) >= 0 ||
        av_dict_సమితి(&dict, ఖాళీ, ఖాళీ, AV_DICT_DONT_STRDUP_కీలకం) >= 0 ||
        av_dict_సమితి(&dict, ఖాళీ, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_లెక్క(dict))
        రాయి("av_dict_set does not correctly handle NULL key\n");

    e = ఖాళీ;
    అయితే ((e = dict_iterate(dict, e)))
        రాయి("'%s' '%s'\n", e->కీలకం, e->విలువ);
    av_dict_free(&dict);


    //valgrind sensible test
    రాయి("\nTesting av_dict_set_int()\n");
    av_dict_సమితి_int(&dict, "1", 1, AV_DICT_DONT_STRDUP_VAL);
    av_dict_సమితి_int(&dict, av_strdup("2"), 2, AV_DICT_DONT_STRDUP_కీలకం);
    av_dict_సమితి_int(&dict, av_strdup("3"), 3, AV_DICT_DONT_STRDUP_కీలకం | AV_DICT_DONT_STRDUP_VAL);
    av_dict_సమితి_int(&dict, "4", 4, 0);
    av_dict_సమితి_int(&dict, "5", 5, AV_DICT_DONT_OVERWRITE);
    av_dict_సమితి_int(&dict, "5", 6, AV_DICT_DONT_OVERWRITE);
    av_dict_సమితి_int(&dict, "12", 1, 0);
    av_dict_సమితి_int(&dict, "12", 2, AV_DICT_APPEND);
    e = ఖాళీ;
    అయితే ((e = dict_iterate(dict, e)))
        రాయి("%s %s\n", e->కీలకం, e->విలువ);
    av_dict_free(&dict);

    //valgrind sensible test
    రాయి("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    ఒకవేళ (av_dict_సమితి(&dict, "key", "old", 0) < 0)
        తిరిగి 1;
    e = av_dict_get(dict, "key", ఖాళీ, 0);
    ఒకవేళ (av_dict_సమితి(&dict, e->కీలకం, "new val OK", 0) < 0)
        తిరిగి 1;
    e = av_dict_get(dict, "key", ఖాళీ, 0);
    రాయి("%s\n", e->విలువ);
    ఒకవేళ (av_dict_సమితి(&dict, e->కీలకం, e->విలువ, 0) < 0)
        తిరిగి 1;
    e = av_dict_get(dict, "key", ఖాళీ, 0);
    రాయి("%s\n", e->విలువ);
    av_dict_free(&dict);

    తిరిగి 0;
}
