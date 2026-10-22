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

#ضمن "libavutil/mem.h"

#ضمن "libavutil/dict.c"

ساكن ثابت AVDictionary_ثبت *dict_iterate(ثابت AVDictionary *m,
                                             ثابت AVDictionary_ثبت *prev)
{
    ثابت AVDictionary_ثبت *dict_get = av_dict_get(m, "", prev, AV_DICT_IGNORE_SUFFIX);
    ثابت AVDictionary_ثبت *dict_iterate = av_dict_iterate(m, prev);

    إذا (dict_get != dict_iterate) {
#تعریف_کړه GET(ثبت, mem) ((ثبت) ? (ثبت)->mem : "N/A")
        چاپ_کړه("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               prev, GET(prev, کلی),
               dict_iterate, GET(dict_iterate, کلی), GET(dict_iterate, ارزښت),
               dict_get, GET(dict_get, کلی), GET(dict_get, ارزښت));
#تعریف_لغوه GET
    }
    أرجع dict_iterate;
}

ساكن فراغ print_dict(ثابت AVDictionary *m)
{
    ثابت AVDictionary_ثبت *t = عدم;
    ثابت حرف *sep = "";
    طالما ((t = dict_iterate(m, t))) {
        چاپ_کړه("%s%s %s", sep, t->کلی, t->ارزښت);
        sep = "   ";
    }
    چاپ_کړه("\n");
}

ساكن فراغ test_separators(ثابت AVDictionary *m, ثابت حرف pair, ثابت حرف val)
{
    AVDictionary *dict = عدم;
    حرف جوړې[] = {pair , '\0'};
    حرف vals[]  = {val, '\0'};

    حرف *بفر = عدم;
    صحيح ret;

    av_dict_copy(&dict, m, 0);
    print_dict(dict);
    av_dict_get_string(dict, &بفر, val, pair);
    چاپ_کړه("%s\n", بفر);
    av_dict_free(&dict);
    ret = av_dict_parse_string(&dict, بفر, vals, جوړې, 0);
    چاپ_کړه("ret %d\n", ret);
    av_freep(&بفر);
    print_dict(dict);
    av_dict_free(&dict);
}

صحيح اصلي(فراغ)
{
    AVDictionary *dict = عدم;
    ثابت AVDictionary_ثبت *e;
    حرف *بفر = عدم;

    چاپ_کړه("Testing av_dict_get_string() and av_dict_parse_string()\n");
    av_dict_get_string(dict, &بفر, '=', ',');
    چاپ_کړه("%s\n", بفر);
    av_freep(&بفر);
    av_dict_سېټ(&dict, "aaa", "aaa", 0);
    av_dict_سېټ(&dict, "b,b", "bbb", 0);
    av_dict_سېټ(&dict, "c=c", "ccc", 0);
    av_dict_سېټ(&dict, "ddd", "d,d", 0);
    av_dict_سېټ(&dict, "eee", "e=e", 0);
    av_dict_سېټ(&dict, "f,f", "f=f", 0);
    av_dict_سېټ(&dict, "g=g", "g,g", 0);
    test_separators(dict, ',', '=');
    av_dict_free(&dict);
    av_dict_سېټ(&dict, "aaa", "aaa", 0);
    av_dict_سېټ(&dict, "bbb", "bbb", 0);
    av_dict_سېټ(&dict, "ccc", "ccc", 0);
    av_dict_سېټ(&dict, "\\,=\'\"", "\\,=\'\"", 0);
    test_separators(dict, '"',  '=');
    test_separators(dict, '\'', '=');
    test_separators(dict, ',', '"');
    test_separators(dict, ',', '\'');
    test_separators(dict, '\'', '"');
    test_separators(dict, '"', '\'');
    av_dict_free(&dict);

    چاپ_کړه("\nTesting av_dict_set()\n");
    av_dict_سېټ(&dict, "a", "a", 0);
    av_dict_سېټ(&dict, "b", av_strdup("b"), AV_DICT_DONT_STRDUP_VAL);
    av_dict_سېټ(&dict, av_strdup("c"), "c", AV_DICT_DONT_STRDUP_کلی);
    av_dict_سېټ(&dict, av_strdup("d"), av_strdup("d"), AV_DICT_DONT_STRDUP_کلی | AV_DICT_DONT_STRDUP_VAL);
    av_dict_سېټ(&dict, "e", "e", AV_DICT_DONT_OVERWRITE);
    av_dict_سېټ(&dict, "e", "f", AV_DICT_DONT_OVERWRITE);
    av_dict_سېټ(&dict, "f", "f", 0);
    av_dict_سېټ(&dict, "f", عدم, 0);
    av_dict_سېټ(&dict, "ff", "f", 0);
    av_dict_سېټ(&dict, "ff", "f", AV_DICT_APPEND);
    إذا (av_dict_get(dict, عدم, عدم, 0))
        چاپ_کړه("av_dict_get() does not correctly handle NULL key.\n");
    e = عدم;
    طالما ((e = dict_iterate(dict, e)))
        چاپ_کړه("%s %s\n", e->کلی, e->ارزښت);
    av_dict_free(&dict);

    إذا (av_dict_سېټ(&dict, عدم, "a", 0) >= 0 ||
        av_dict_سېټ(&dict, عدم, "b", 0) >= 0 ||
        av_dict_سېټ(&dict, عدم, عدم, AV_DICT_DONT_STRDUP_کلی) >= 0 ||
        av_dict_سېټ(&dict, عدم, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_شمېر(dict))
        چاپ_کړه("av_dict_set does not correctly handle NULL key\n");

    e = عدم;
    طالما ((e = dict_iterate(dict, e)))
        چاپ_کړه("'%s' '%s'\n", e->کلی, e->ارزښت);
    av_dict_free(&dict);


    //valgrind sensible test
    چاپ_کړه("\nTesting av_dict_set_int()\n");
    av_dict_سېټ_int(&dict, "1", 1, AV_DICT_DONT_STRDUP_VAL);
    av_dict_سېټ_int(&dict, av_strdup("2"), 2, AV_DICT_DONT_STRDUP_کلی);
    av_dict_سېټ_int(&dict, av_strdup("3"), 3, AV_DICT_DONT_STRDUP_کلی | AV_DICT_DONT_STRDUP_VAL);
    av_dict_سېټ_int(&dict, "4", 4, 0);
    av_dict_سېټ_int(&dict, "5", 5, AV_DICT_DONT_OVERWRITE);
    av_dict_سېټ_int(&dict, "5", 6, AV_DICT_DONT_OVERWRITE);
    av_dict_سېټ_int(&dict, "12", 1, 0);
    av_dict_سېټ_int(&dict, "12", 2, AV_DICT_APPEND);
    e = عدم;
    طالما ((e = dict_iterate(dict, e)))
        چاپ_کړه("%s %s\n", e->کلی, e->ارزښت);
    av_dict_free(&dict);

    //valgrind sensible test
    چاپ_کړه("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    إذا (av_dict_سېټ(&dict, "key", "old", 0) < 0)
        أرجع 1;
    e = av_dict_get(dict, "key", عدم, 0);
    إذا (av_dict_سېټ(&dict, e->کلی, "new val OK", 0) < 0)
        أرجع 1;
    e = av_dict_get(dict, "key", عدم, 0);
    چاپ_کړه("%s\n", e->ارزښت);
    إذا (av_dict_سېټ(&dict, e->کلی, e->ارزښت, 0) < 0)
        أرجع 1;
    e = av_dict_get(dict, "key", عدم, 0);
    چاپ_کړه("%s\n", e->ارزښت);
    av_dict_free(&dict);

    أرجع 0;
}
