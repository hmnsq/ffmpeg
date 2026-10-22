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

#অন্তর্ভাব "libavutil/mem.h"

#অন্তর্ভাব "libavutil/dict.c"

স্থির ধ্রুবক AVDictionaryEntry *dict_iterate(ধ্রুবক AVDictionary *m,
                                             ধ্রুবক AVDictionaryEntry *পূর্ব)
{
    ধ্রুবক AVDictionaryEntry *dict_get = av_dict_get(m, "", পূর্ব, AV_DICT_IGNORE_SUFFIX);
    ধ্রুবক AVDictionaryEntry *dict_iterate = av_dict_iterate(m, পূর্ব);

    যদি (dict_get != dict_iterate) {
#define GET(entry, mem) ((entry) ? (entry)->mem : "N/A")
        printf("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               পূর্ব, GET(পূর্ব, চাবি),
               dict_iterate, GET(dict_iterate, চাবি), GET(dict_iterate, মান),
               dict_get, GET(dict_get, চাবি), GET(dict_get, মান));
#undef GET
    }
    ফেরত dict_iterate;
}

স্থির শূন্য print_dict(ধ্রুবক AVDictionary *m)
{
    ধ্রুবক AVDictionaryEntry *t = ফাঁকা;
    ধ্রুবক অক্ষর *sep = "";
    যখন ((t = dict_iterate(m, t))) {
        printf("%s%s %s", sep, t->চাবি, t->মান);
        sep = "   ";
    }
    printf("\n");
}

স্থির শূন্য test_separators(ধ্রুবক AVDictionary *m, ধ্রুবক অক্ষর pair, ধ্রুবক অক্ষর val)
{
    AVDictionary *dict = ফাঁকা;
    অক্ষর pairs[] = {pair , '\0'};
    অক্ষর vals[]  = {val, '\0'};

    অক্ষর *বাফার = ফাঁকা;
    পূর্ণসংখ্যা ret;

    av_dict_copy(&dict, m, 0);
    print_dict(dict);
    av_dict_get_string(dict, &বাফার, val, pair);
    printf("%s\n", বাফার);
    av_dict_free(&dict);
    ret = av_dict_parse_string(&dict, বাফার, vals, pairs, 0);
    printf("ret %d\n", ret);
    av_freep(&বাফার);
    print_dict(dict);
    av_dict_free(&dict);
}

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    AVDictionary *dict = ফাঁকা;
    ধ্রুবক AVDictionaryEntry *e;
    অক্ষর *বাফার = ফাঁকা;

    printf("Testing av_dict_get_string() and av_dict_parse_string()\n");
    av_dict_get_string(dict, &বাফার, '=', ',');
    printf("%s\n", বাফার);
    av_freep(&বাফার);
    av_dict_set(&dict, "aaa", "aaa", 0);
    av_dict_set(&dict, "b,b", "bbb", 0);
    av_dict_set(&dict, "c=c", "ccc", 0);
    av_dict_set(&dict, "ddd", "d,d", 0);
    av_dict_set(&dict, "eee", "e=e", 0);
    av_dict_set(&dict, "f,f", "f=f", 0);
    av_dict_set(&dict, "g=g", "g,g", 0);
    test_separators(dict, ',', '=');
    av_dict_free(&dict);
    av_dict_set(&dict, "aaa", "aaa", 0);
    av_dict_set(&dict, "bbb", "bbb", 0);
    av_dict_set(&dict, "ccc", "ccc", 0);
    av_dict_set(&dict, "\\,=\'\"", "\\,=\'\"", 0);
    test_separators(dict, '"',  '=');
    test_separators(dict, '\'', '=');
    test_separators(dict, ',', '"');
    test_separators(dict, ',', '\'');
    test_separators(dict, '\'', '"');
    test_separators(dict, '"', '\'');
    av_dict_free(&dict);

    printf("\nTesting av_dict_set()\n");
    av_dict_set(&dict, "a", "a", 0);
    av_dict_set(&dict, "b", av_strdup("b"), AV_DICT_DONT_STRDUP_VAL);
    av_dict_set(&dict, av_strdup("c"), "c", AV_DICT_DONT_STRDUP_চাবি);
    av_dict_set(&dict, av_strdup("d"), av_strdup("d"), AV_DICT_DONT_STRDUP_চাবি | AV_DICT_DONT_STRDUP_VAL);
    av_dict_set(&dict, "e", "e", AV_DICT_DONT_OVERWRITE);
    av_dict_set(&dict, "e", "f", AV_DICT_DONT_OVERWRITE);
    av_dict_set(&dict, "f", "f", 0);
    av_dict_set(&dict, "f", ফাঁকা, 0);
    av_dict_set(&dict, "ff", "f", 0);
    av_dict_set(&dict, "ff", "f", AV_DICT_APPEND);
    যদি (av_dict_get(dict, ফাঁকা, ফাঁকা, 0))
        printf("av_dict_get() does not correctly handle NULL key.\n");
    e = ফাঁকা;
    যখন ((e = dict_iterate(dict, e)))
        printf("%s %s\n", e->চাবি, e->মান);
    av_dict_free(&dict);

    যদি (av_dict_set(&dict, ফাঁকা, "a", 0) >= 0 ||
        av_dict_set(&dict, ফাঁকা, "b", 0) >= 0 ||
        av_dict_set(&dict, ফাঁকা, ফাঁকা, AV_DICT_DONT_STRDUP_চাবি) >= 0 ||
        av_dict_set(&dict, ফাঁকা, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_গুনতি(dict))
        printf("av_dict_set does not correctly handle NULL key\n");

    e = ফাঁকা;
    যখন ((e = dict_iterate(dict, e)))
        printf("'%s' '%s'\n", e->চাবি, e->মান);
    av_dict_free(&dict);


    //valgrind sensible test
    printf("\nTesting av_dict_set_int()\n");
    av_dict_set_int(&dict, "1", 1, AV_DICT_DONT_STRDUP_VAL);
    av_dict_set_int(&dict, av_strdup("2"), 2, AV_DICT_DONT_STRDUP_চাবি);
    av_dict_set_int(&dict, av_strdup("3"), 3, AV_DICT_DONT_STRDUP_চাবি | AV_DICT_DONT_STRDUP_VAL);
    av_dict_set_int(&dict, "4", 4, 0);
    av_dict_set_int(&dict, "5", 5, AV_DICT_DONT_OVERWRITE);
    av_dict_set_int(&dict, "5", 6, AV_DICT_DONT_OVERWRITE);
    av_dict_set_int(&dict, "12", 1, 0);
    av_dict_set_int(&dict, "12", 2, AV_DICT_APPEND);
    e = ফাঁকা;
    যখন ((e = dict_iterate(dict, e)))
        printf("%s %s\n", e->চাবি, e->মান);
    av_dict_free(&dict);

    //valgrind sensible test
    printf("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    যদি (av_dict_set(&dict, "key", "old", 0) < 0)
        ফেরত 1;
    e = av_dict_get(dict, "key", ফাঁকা, 0);
    যদি (av_dict_set(&dict, e->চাবি, "new val OK", 0) < 0)
        ফেরত 1;
    e = av_dict_get(dict, "key", ফাঁকা, 0);
    printf("%s\n", e->মান);
    যদি (av_dict_set(&dict, e->চাবি, e->মান, 0) < 0)
        ফেরত 1;
    e = av_dict_get(dict, "key", ফাঁকা, 0);
    printf("%s\n", e->মান);
    av_dict_free(&dict);

    ফেরত 0;
}
