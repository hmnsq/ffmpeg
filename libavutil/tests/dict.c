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

#ଅନ୍ତର୍ଭାଵ "libavutil/mem.h"

#ଅନ୍ତର୍ଭାଵ "libavutil/dict.c"

ସ୍ଥିର ଅଚଳ AVDictionaryEntry *dict_iterate(ଅଚଳ AVDictionary *m,
                                             ଅଚଳ AVDictionaryEntry *prev)
{
    ଅଚଳ AVDictionaryEntry *dict_get = av_dict_get(m, "", prev, AV_DICT_IGNORE_SUFFIX);
    ଅଚଳ AVDictionaryEntry *dict_iterate = av_dict_iterate(m, prev);

    ଯଦି (dict_get != dict_iterate) {
#define GET(entry, mem) ((entry) ? (entry)->mem : "N/A")
        printf("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               prev, GET(prev, ଚାବି),
               dict_iterate, GET(dict_iterate, ଚାବି), GET(dict_iterate, ମୂଲ୍ୟ),
               dict_get, GET(dict_get, ଚାବି), GET(dict_get, ମୂଲ୍ୟ));
#undef GET
    }
    ଫେରନ୍ତୁ dict_iterate;
}

ସ୍ଥିର ଶୂନ୍ୟ print_dict(ଅଚଳ AVDictionary *m)
{
    ଅଚଳ AVDictionaryEntry *t = ଖାଲି;
    ଅଚଳ ଅକ୍ଷର *sep = "";
    ଯେତେବେଳେ ((t = dict_iterate(m, t))) {
        printf("%s%s %s", sep, t->ଚାବି, t->ମୂଲ୍ୟ);
        sep = "   ";
    }
    printf("\n");
}

ସ୍ଥିର ଶୂନ୍ୟ test_separators(ଅଚଳ AVDictionary *m, ଅଚଳ ଅକ୍ଷର pair, ଅଚଳ ଅକ୍ଷର val)
{
    AVDictionary *dict = ଖାଲି;
    ଅକ୍ଷର pairs[] = {pair , '\0'};
    ଅକ୍ଷର vals[]  = {val, '\0'};

    ଅକ୍ଷର *buffer = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

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

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ଶୂନ୍ୟ)
{
    AVDictionary *dict = ଖାଲି;
    ଅଚଳ AVDictionaryEntry *e;
    ଅକ୍ଷର *buffer = ଖାଲି;

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
    av_dict_set(&dict, av_strdup("c"), "c", AV_DICT_DONT_STRDUP_ଚାବି);
    av_dict_set(&dict, av_strdup("d"), av_strdup("d"), AV_DICT_DONT_STRDUP_ଚାବି | AV_DICT_DONT_STRDUP_VAL);
    av_dict_set(&dict, "e", "e", AV_DICT_DONT_OVERWRITE);
    av_dict_set(&dict, "e", "f", AV_DICT_DONT_OVERWRITE);
    av_dict_set(&dict, "f", "f", 0);
    av_dict_set(&dict, "f", ଖାଲି, 0);
    av_dict_set(&dict, "ff", "f", 0);
    av_dict_set(&dict, "ff", "f", AV_DICT_APPEND);
    ଯଦି (av_dict_get(dict, ଖାଲି, ଖାଲି, 0))
        printf("av_dict_get() does not correctly handle NULL key.\n");
    e = ଖାଲି;
    ଯେତେବେଳେ ((e = dict_iterate(dict, e)))
        printf("%s %s\n", e->ଚାବି, e->ମୂଲ୍ୟ);
    av_dict_free(&dict);

    ଯଦି (av_dict_set(&dict, ଖାଲି, "a", 0) >= 0 ||
        av_dict_set(&dict, ଖାଲି, "b", 0) >= 0 ||
        av_dict_set(&dict, ଖାଲି, ଖାଲି, AV_DICT_DONT_STRDUP_ଚାବି) >= 0 ||
        av_dict_set(&dict, ଖାଲି, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_ଗଣନା(dict))
        printf("av_dict_set does not correctly handle NULL key\n");

    e = ଖାଲି;
    ଯେତେବେଳେ ((e = dict_iterate(dict, e)))
        printf("'%s' '%s'\n", e->ଚାବି, e->ମୂଲ୍ୟ);
    av_dict_free(&dict);


    //valgrind sensible test
    printf("\nTesting av_dict_set_int()\n");
    av_dict_set_int(&dict, "1", 1, AV_DICT_DONT_STRDUP_VAL);
    av_dict_set_int(&dict, av_strdup("2"), 2, AV_DICT_DONT_STRDUP_ଚାବି);
    av_dict_set_int(&dict, av_strdup("3"), 3, AV_DICT_DONT_STRDUP_ଚାବି | AV_DICT_DONT_STRDUP_VAL);
    av_dict_set_int(&dict, "4", 4, 0);
    av_dict_set_int(&dict, "5", 5, AV_DICT_DONT_OVERWRITE);
    av_dict_set_int(&dict, "5", 6, AV_DICT_DONT_OVERWRITE);
    av_dict_set_int(&dict, "12", 1, 0);
    av_dict_set_int(&dict, "12", 2, AV_DICT_APPEND);
    e = ଖାଲି;
    ଯେତେବେଳେ ((e = dict_iterate(dict, e)))
        printf("%s %s\n", e->ଚାବି, e->ମୂଲ୍ୟ);
    av_dict_free(&dict);

    //valgrind sensible test
    printf("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    ଯଦି (av_dict_set(&dict, "key", "old", 0) < 0)
        ଫେରନ୍ତୁ 1;
    e = av_dict_get(dict, "key", ଖାଲି, 0);
    ଯଦି (av_dict_set(&dict, e->ଚାବି, "new val OK", 0) < 0)
        ଫେରନ୍ତୁ 1;
    e = av_dict_get(dict, "key", ଖାଲି, 0);
    printf("%s\n", e->ମୂଲ୍ୟ);
    ଯଦି (av_dict_set(&dict, e->ଚାବି, e->ମୂଲ୍ୟ, 0) < 0)
        ଫେରନ୍ତୁ 1;
    e = av_dict_get(dict, "key", ଖାଲି, 0);
    printf("%s\n", e->ମୂଲ୍ୟ);
    av_dict_free(&dict);

    ଫେରନ୍ତୁ 0;
}
