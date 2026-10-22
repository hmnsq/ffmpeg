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

#شامل "libavutil/mem.h"

#شامل "libavutil/dict.c"

ساکن ثابت AVDictionary_اندراج *dict_iterate(ثابت AVDictionary *m,
                                             ثابت AVDictionary_اندراج *پچھلا)
{
    ثابت AVDictionary_اندراج *dict_get = av_dict_get(m, "", پچھلا, AV_DICT_IGNORE_SUFFIX);
    ثابت AVDictionary_اندراج *dict_iterate = av_dict_iterate(m, پچھلا);

    اگر (dict_get != dict_iterate) {
#تعریف_کرو GET(اندراج_2, mem) ((اندراج_2) ? (اندراج_2)->mem : "N/A")
        لکھو("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               پچھلا, GET(پچھلا, کلید),
               dict_iterate, GET(dict_iterate, کلید), GET(dict_iterate, قدر),
               dict_get, GET(dict_get, کلید), GET(dict_get, قدر));
#تعریف_منسوخ GET
    }
    واپس dict_iterate;
}

ساکن خالی print_dict(ثابت AVDictionary *m)
{
    ثابت AVDictionary_اندراج *t = تہی;
    ثابت حرف *sep = "";
    جب ((t = dict_iterate(m, t))) {
        لکھو("%s%s %s", sep, t->کلید, t->قدر);
        sep = "   ";
    }
    لکھو("\n");
}

ساکن خالی test_separators(ثابت AVDictionary *m, ثابت حرف pair, ثابت حرف val)
{
    AVDictionary *dict = تہی;
    حرف جوڑے[] = {pair , '\0'};
    حرف vals[]  = {val, '\0'};

    حرف *بفر = تہی;
    صحیح ret;

    av_dict_copy(&dict, m, 0);
    print_dict(dict);
    av_dict_get_string(dict, &بفر, val, pair);
    لکھو("%s\n", بفر);
    av_dict_free(&dict);
    ret = av_dict_parse_string(&dict, بفر, vals, جوڑے, 0);
    لکھو("ret %d\n", ret);
    av_freep(&بفر);
    print_dict(dict);
    av_dict_free(&dict);
}

صحیح مین(خالی)
{
    AVDictionary *dict = تہی;
    ثابت AVDictionary_اندراج *e;
    حرف *بفر = تہی;

    لکھو("Testing av_dict_get_string() and av_dict_parse_string()\n");
    av_dict_get_string(dict, &بفر, '=', ',');
    لکھو("%s\n", بفر);
    av_freep(&بفر);
    av_dict_سیٹ(&dict, "aaa", "aaa", 0);
    av_dict_سیٹ(&dict, "b,b", "bbb", 0);
    av_dict_سیٹ(&dict, "c=c", "ccc", 0);
    av_dict_سیٹ(&dict, "ddd", "d,d", 0);
    av_dict_سیٹ(&dict, "eee", "e=e", 0);
    av_dict_سیٹ(&dict, "f,f", "f=f", 0);
    av_dict_سیٹ(&dict, "g=g", "g,g", 0);
    test_separators(dict, ',', '=');
    av_dict_free(&dict);
    av_dict_سیٹ(&dict, "aaa", "aaa", 0);
    av_dict_سیٹ(&dict, "bbb", "bbb", 0);
    av_dict_سیٹ(&dict, "ccc", "ccc", 0);
    av_dict_سیٹ(&dict, "\\,=\'\"", "\\,=\'\"", 0);
    test_separators(dict, '"',  '=');
    test_separators(dict, '\'', '=');
    test_separators(dict, ',', '"');
    test_separators(dict, ',', '\'');
    test_separators(dict, '\'', '"');
    test_separators(dict, '"', '\'');
    av_dict_free(&dict);

    لکھو("\nTesting av_dict_set()\n");
    av_dict_سیٹ(&dict, "a", "a", 0);
    av_dict_سیٹ(&dict, "b", av_strdup("b"), AV_DICT_DONT_STRDUP_VAL);
    av_dict_سیٹ(&dict, av_strdup("c"), "c", AV_DICT_DONT_STRDUP_کلید);
    av_dict_سیٹ(&dict, av_strdup("d"), av_strdup("d"), AV_DICT_DONT_STRDUP_کلید | AV_DICT_DONT_STRDUP_VAL);
    av_dict_سیٹ(&dict, "e", "e", AV_DICT_DONT_OVERWRITE);
    av_dict_سیٹ(&dict, "e", "f", AV_DICT_DONT_OVERWRITE);
    av_dict_سیٹ(&dict, "f", "f", 0);
    av_dict_سیٹ(&dict, "f", تہی, 0);
    av_dict_سیٹ(&dict, "ff", "f", 0);
    av_dict_سیٹ(&dict, "ff", "f", AV_DICT_APPEND);
    اگر (av_dict_get(dict, تہی, تہی, 0))
        لکھو("av_dict_get() does not correctly handle NULL key.\n");
    e = تہی;
    جب ((e = dict_iterate(dict, e)))
        لکھو("%s %s\n", e->کلید, e->قدر);
    av_dict_free(&dict);

    اگر (av_dict_سیٹ(&dict, تہی, "a", 0) >= 0 ||
        av_dict_سیٹ(&dict, تہی, "b", 0) >= 0 ||
        av_dict_سیٹ(&dict, تہی, تہی, AV_DICT_DONT_STRDUP_کلید) >= 0 ||
        av_dict_سیٹ(&dict, تہی, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_گنتی(dict))
        لکھو("av_dict_set does not correctly handle NULL key\n");

    e = تہی;
    جب ((e = dict_iterate(dict, e)))
        لکھو("'%s' '%s'\n", e->کلید, e->قدر);
    av_dict_free(&dict);


    //valgrind sensible test
    لکھو("\nTesting av_dict_set_int()\n");
    av_dict_سیٹ_int(&dict, "1", 1, AV_DICT_DONT_STRDUP_VAL);
    av_dict_سیٹ_int(&dict, av_strdup("2"), 2, AV_DICT_DONT_STRDUP_کلید);
    av_dict_سیٹ_int(&dict, av_strdup("3"), 3, AV_DICT_DONT_STRDUP_کلید | AV_DICT_DONT_STRDUP_VAL);
    av_dict_سیٹ_int(&dict, "4", 4, 0);
    av_dict_سیٹ_int(&dict, "5", 5, AV_DICT_DONT_OVERWRITE);
    av_dict_سیٹ_int(&dict, "5", 6, AV_DICT_DONT_OVERWRITE);
    av_dict_سیٹ_int(&dict, "12", 1, 0);
    av_dict_سیٹ_int(&dict, "12", 2, AV_DICT_APPEND);
    e = تہی;
    جب ((e = dict_iterate(dict, e)))
        لکھو("%s %s\n", e->کلید, e->قدر);
    av_dict_free(&dict);

    //valgrind sensible test
    لکھو("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    اگر (av_dict_سیٹ(&dict, "key", "old", 0) < 0)
        واپس 1;
    e = av_dict_get(dict, "key", تہی, 0);
    اگر (av_dict_سیٹ(&dict, e->کلید, "new val OK", 0) < 0)
        واپس 1;
    e = av_dict_get(dict, "key", تہی, 0);
    لکھو("%s\n", e->قدر);
    اگر (av_dict_سیٹ(&dict, e->کلید, e->قدر, 0) < 0)
        واپس 1;
    e = av_dict_get(dict, "key", تہی, 0);
    لکھو("%s\n", e->قدر);
    av_dict_free(&dict);

    واپس 0;
}
