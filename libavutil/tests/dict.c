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

ساكن ثابت AVDictionary_مدخل *dict_iterate(ثابت AVDictionary *m,
                                             ثابت AVDictionary_مدخل *prev)
{
    ثابت AVDictionary_مدخل *dict_get = av_dict_get(m, "", prev, AV_DICT_IGNORE_SUFFIX);
    ثابت AVDictionary_مدخل *dict_iterate = av_dict_iterate(m, prev);

    إذا (dict_get != dict_iterate) {
#تعریف_کن GET(مدخل, mem) ((مدخل) ? (مدخل)->mem : "N/A")
        چاپ_کن("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               prev, GET(prev, کلید),
               dict_iterate, GET(dict_iterate, کلید), GET(dict_iterate, مقدار),
               dict_get, GET(dict_get, کلید), GET(dict_get, مقدار));
#لغو_تعریف GET
    }
    أرجع dict_iterate;
}

ساكن فراغ print_dict(ثابت AVDictionary *m)
{
    ثابت AVDictionary_مدخل *t = عدم;
    ثابت حرف *sep = "";
    طالما ((t = dict_iterate(m, t))) {
        چاپ_کن("%s%s %s", sep, t->کلید, t->مقدار);
        sep = "   ";
    }
    چاپ_کن("\n");
}

ساكن فراغ test_separators(ثابت AVDictionary *m, ثابت حرف pair, ثابت حرف val)
{
    AVDictionary *dict = عدم;
    حرف جفتها[] = {pair , '\0'};
    حرف vals[]  = {val, '\0'};

    حرف *میانگیر = عدم;
    صحيح ret;

    av_dict_copy(&dict, m, 0);
    print_dict(dict);
    av_dict_get_string(dict, &میانگیر, val, pair);
    چاپ_کن("%s\n", میانگیر);
    av_dict_free(&dict);
    ret = av_dict_parse_string(&dict, میانگیر, vals, جفتها, 0);
    چاپ_کن("ret %d\n", ret);
    av_freep(&میانگیر);
    print_dict(dict);
    av_dict_free(&dict);
}

صحيح اصلی(فراغ)
{
    AVDictionary *dict = عدم;
    ثابت AVDictionary_مدخل *e;
    حرف *میانگیر = عدم;

    چاپ_کن("Testing av_dict_get_string() and av_dict_parse_string()\n");
    av_dict_get_string(dict, &میانگیر, '=', ',');
    چاپ_کن("%s\n", میانگیر);
    av_freep(&میانگیر);
    av_dict_مجموعه(&dict, "aaa", "aaa", 0);
    av_dict_مجموعه(&dict, "b,b", "bbb", 0);
    av_dict_مجموعه(&dict, "c=c", "ccc", 0);
    av_dict_مجموعه(&dict, "ddd", "d,d", 0);
    av_dict_مجموعه(&dict, "eee", "e=e", 0);
    av_dict_مجموعه(&dict, "f,f", "f=f", 0);
    av_dict_مجموعه(&dict, "g=g", "g,g", 0);
    test_separators(dict, ',', '=');
    av_dict_free(&dict);
    av_dict_مجموعه(&dict, "aaa", "aaa", 0);
    av_dict_مجموعه(&dict, "bbb", "bbb", 0);
    av_dict_مجموعه(&dict, "ccc", "ccc", 0);
    av_dict_مجموعه(&dict, "\\,=\'\"", "\\,=\'\"", 0);
    test_separators(dict, '"',  '=');
    test_separators(dict, '\'', '=');
    test_separators(dict, ',', '"');
    test_separators(dict, ',', '\'');
    test_separators(dict, '\'', '"');
    test_separators(dict, '"', '\'');
    av_dict_free(&dict);

    چاپ_کن("\nTesting av_dict_set()\n");
    av_dict_مجموعه(&dict, "a", "a", 0);
    av_dict_مجموعه(&dict, "b", av_strdup("b"), AV_DICT_DONT_STRDUP_VAL);
    av_dict_مجموعه(&dict, av_strdup("c"), "c", AV_DICT_DONT_STRDUP_کلید);
    av_dict_مجموعه(&dict, av_strdup("d"), av_strdup("d"), AV_DICT_DONT_STRDUP_کلید | AV_DICT_DONT_STRDUP_VAL);
    av_dict_مجموعه(&dict, "e", "e", AV_DICT_DONT_OVERWRITE);
    av_dict_مجموعه(&dict, "e", "f", AV_DICT_DONT_OVERWRITE);
    av_dict_مجموعه(&dict, "f", "f", 0);
    av_dict_مجموعه(&dict, "f", عدم, 0);
    av_dict_مجموعه(&dict, "ff", "f", 0);
    av_dict_مجموعه(&dict, "ff", "f", AV_DICT_APPEND);
    إذا (av_dict_get(dict, عدم, عدم, 0))
        چاپ_کن("av_dict_get() does not correctly handle NULL key.\n");
    e = عدم;
    طالما ((e = dict_iterate(dict, e)))
        چاپ_کن("%s %s\n", e->کلید, e->مقدار);
    av_dict_free(&dict);

    إذا (av_dict_مجموعه(&dict, عدم, "a", 0) >= 0 ||
        av_dict_مجموعه(&dict, عدم, "b", 0) >= 0 ||
        av_dict_مجموعه(&dict, عدم, عدم, AV_DICT_DONT_STRDUP_کلید) >= 0 ||
        av_dict_مجموعه(&dict, عدم, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_شمار(dict))
        چاپ_کن("av_dict_set does not correctly handle NULL key\n");

    e = عدم;
    طالما ((e = dict_iterate(dict, e)))
        چاپ_کن("'%s' '%s'\n", e->کلید, e->مقدار);
    av_dict_free(&dict);


    //valgrind sensible test
    چاپ_کن("\nTesting av_dict_set_int()\n");
    av_dict_مجموعه_int(&dict, "1", 1, AV_DICT_DONT_STRDUP_VAL);
    av_dict_مجموعه_int(&dict, av_strdup("2"), 2, AV_DICT_DONT_STRDUP_کلید);
    av_dict_مجموعه_int(&dict, av_strdup("3"), 3, AV_DICT_DONT_STRDUP_کلید | AV_DICT_DONT_STRDUP_VAL);
    av_dict_مجموعه_int(&dict, "4", 4, 0);
    av_dict_مجموعه_int(&dict, "5", 5, AV_DICT_DONT_OVERWRITE);
    av_dict_مجموعه_int(&dict, "5", 6, AV_DICT_DONT_OVERWRITE);
    av_dict_مجموعه_int(&dict, "12", 1, 0);
    av_dict_مجموعه_int(&dict, "12", 2, AV_DICT_APPEND);
    e = عدم;
    طالما ((e = dict_iterate(dict, e)))
        چاپ_کن("%s %s\n", e->کلید, e->مقدار);
    av_dict_free(&dict);

    //valgrind sensible test
    چاپ_کن("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    إذا (av_dict_مجموعه(&dict, "key", "old", 0) < 0)
        أرجع 1;
    e = av_dict_get(dict, "key", عدم, 0);
    إذا (av_dict_مجموعه(&dict, e->کلید, "new val OK", 0) < 0)
        أرجع 1;
    e = av_dict_get(dict, "key", عدم, 0);
    چاپ_کن("%s\n", e->مقدار);
    إذا (av_dict_مجموعه(&dict, e->کلید, e->مقدار, 0) < 0)
        أرجع 1;
    e = av_dict_get(dict, "key", عدم, 0);
    چاپ_کن("%s\n", e->مقدار);
    av_dict_free(&dict);

    أرجع 0;
}
