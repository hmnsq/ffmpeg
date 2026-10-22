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

স্থির ধ্রুব AVDictionaryEntry *dict_iterate(ধ্রুব AVDictionary *m,
                                             ধ্রুব AVDictionaryEntry *prev)
{
    ধ্রুব AVDictionaryEntry *dict_get = av_dict_get(m, "", prev, AV_DICT_IGNORE_SUFFIX);
    ধ্রুব AVDictionaryEntry *dict_iterate = av_dict_iterate(m, prev);

    যদি (dict_get != dict_iterate) {
#define GET(entry, mem) ((entry) ? (entry)->mem : "N/A")
        printf("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               prev, GET(prev, চাবি),
               dict_iterate, GET(dict_iterate, চাবি), GET(dict_iterate, মান),
               dict_get, GET(dict_get, চাবি), GET(dict_get, মান));
#undef GET
    }
    প্রত্যাগম dict_iterate;
}

স্থির শূন্য print_dict(ধ্রুব AVDictionary *m)
{
    ধ্রুব AVDictionaryEntry *t = রিক্ত;
    ধ্রুব বর্ণ *sep = "";
    যাবত্ ((t = dict_iterate(m, t))) {
        printf("%s%s %s", sep, t->চাবি, t->মান);
        sep = "   ";
    }
    printf("\n");
}

স্থির শূন্য test_separators(ধ্রুব AVDictionary *m, ধ্রুব বর্ণ pair, ধ্রুব বর্ণ val)
{
    AVDictionary *dict = রিক্ত;
    বর্ণ pairs[] = {pair , '\0'};
    বর্ণ vals[]  = {val, '\0'};

    বর্ণ *buffer = রিক্ত;
    পূর্ণাঙ্ক ret;

    av_dict_copy(&dict, m, 0);
    print_dict(dict);
    av_dict_get_string(dict, &buffer, val, pair);
    printf("%s\n", buffer);
    av_dict_free(&dict);
    ret = av_dict_parse_string(&dict, buffer, vals, pairs, 0);
    printf("ret %d\n", ret);
    av_freep(&buffer);
    print_dict(dict);
    av_dict_free(&dict);
}

পূর্ণাঙ্ক main(শূন্য)
{
    AVDictionary *dict = রিক্ত;
    ধ্রুব AVDictionaryEntry *e;
    বর্ণ *buffer = রিক্ত;

    printf("Testing av_dict_get_string() and av_dict_parse_string()\n");
    av_dict_get_string(dict, &buffer, '=', ',');
    printf("%s\n", buffer);
    av_freep(&buffer);
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
    av_dict_set(&dict, "f", রিক্ত, 0);
    av_dict_set(&dict, "ff", "f", 0);
    av_dict_set(&dict, "ff", "f", AV_DICT_APPEND);
    যদি (av_dict_get(dict, রিক্ত, রিক্ত, 0))
        printf("av_dict_get() does not correctly handle NULL key.\n");
    e = রিক্ত;
    যাবত্ ((e = dict_iterate(dict, e)))
        printf("%s %s\n", e->চাবি, e->মান);
    av_dict_free(&dict);

    যদি (av_dict_set(&dict, রিক্ত, "a", 0) >= 0 ||
        av_dict_set(&dict, রিক্ত, "b", 0) >= 0 ||
        av_dict_set(&dict, রিক্ত, রিক্ত, AV_DICT_DONT_STRDUP_চাবি) >= 0 ||
        av_dict_set(&dict, রিক্ত, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_গুনতি(dict))
        printf("av_dict_set does not correctly handle NULL key\n");

    e = রিক্ত;
    যাবত্ ((e = dict_iterate(dict, e)))
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
    e = রিক্ত;
    যাবত্ ((e = dict_iterate(dict, e)))
        printf("%s %s\n", e->চাবি, e->মান);
    av_dict_free(&dict);

    //valgrind sensible test
    printf("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    যদি (av_dict_set(&dict, "key", "old", 0) < 0)
        প্রত্যাগম 1;
    e = av_dict_get(dict, "key", রিক্ত, 0);
    যদি (av_dict_set(&dict, e->চাবি, "new val OK", 0) < 0)
        প্রত্যাগম 1;
    e = av_dict_get(dict, "key", রিক্ত, 0);
    printf("%s\n", e->মান);
    যদি (av_dict_set(&dict, e->চাবি, e->মান, 0) < 0)
        প্রত্যাগম 1;
    e = av_dict_get(dict, "key", রিক্ত, 0);
    printf("%s\n", e->মান);
    av_dict_free(&dict);

    প্রত্যাগম 0;
}
