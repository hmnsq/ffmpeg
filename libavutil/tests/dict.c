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

#அந்தர்பாவ "libavutil/mem.h"

#அந்தர்பாவ "libavutil/dict.c"

நிலையான மாறிலி AVDictionaryEntry *dict_iterate(மாறிலி AVDictionary *m,
                                             மாறிலி AVDictionaryEntry *prev)
{
    மாறிலி AVDictionaryEntry *dict_get = av_dict_get(m, "", prev, AV_DICT_IGNORE_SUFFIX);
    மாறிலி AVDictionaryEntry *dict_iterate = av_dict_iterate(m, prev);

    எனில் (dict_get != dict_iterate) {
#define GET(entry, mem) ((entry) ? (entry)->mem : "N/A")
        printf("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               prev, GET(prev, சாவி),
               dict_iterate, GET(dict_iterate, சாவி), GET(dict_iterate, மதிப்பு),
               dict_get, GET(dict_get, சாவி), GET(dict_get, மதிப்பு));
#undef GET
    }
    திரும்பு dict_iterate;
}

நிலையான வெறுமை print_dict(மாறிலி AVDictionary *m)
{
    மாறிலி AVDictionaryEntry *t = வெற்று;
    மாறிலி எழுத்து *sep = "";
    போது ((t = dict_iterate(m, t))) {
        printf("%s%s %s", sep, t->சாவி, t->மதிப்பு);
        sep = "   ";
    }
    printf("\n");
}

நிலையான வெறுமை test_separators(மாறிலி AVDictionary *m, மாறிலி எழுத்து pair, மாறிலி எழுத்து val)
{
    AVDictionary *dict = வெற்று;
    எழுத்து pairs[] = {pair , '\0'};
    எழுத்து vals[]  = {val, '\0'};

    எழுத்து *buffer = வெற்று;
    முழு ret;

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

முழு முதன்மை(வெறுமை)
{
    AVDictionary *dict = வெற்று;
    மாறிலி AVDictionaryEntry *e;
    எழுத்து *buffer = வெற்று;

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
    av_dict_set(&dict, av_strdup("c"), "c", AV_DICT_DONT_STRDUP_சாவி);
    av_dict_set(&dict, av_strdup("d"), av_strdup("d"), AV_DICT_DONT_STRDUP_சாவி | AV_DICT_DONT_STRDUP_VAL);
    av_dict_set(&dict, "e", "e", AV_DICT_DONT_OVERWRITE);
    av_dict_set(&dict, "e", "f", AV_DICT_DONT_OVERWRITE);
    av_dict_set(&dict, "f", "f", 0);
    av_dict_set(&dict, "f", வெற்று, 0);
    av_dict_set(&dict, "ff", "f", 0);
    av_dict_set(&dict, "ff", "f", AV_DICT_APPEND);
    எனில் (av_dict_get(dict, வெற்று, வெற்று, 0))
        printf("av_dict_get() does not correctly handle NULL key.\n");
    e = வெற்று;
    போது ((e = dict_iterate(dict, e)))
        printf("%s %s\n", e->சாவி, e->மதிப்பு);
    av_dict_free(&dict);

    எனில் (av_dict_set(&dict, வெற்று, "a", 0) >= 0 ||
        av_dict_set(&dict, வெற்று, "b", 0) >= 0 ||
        av_dict_set(&dict, வெற்று, வெற்று, AV_DICT_DONT_STRDUP_சாவி) >= 0 ||
        av_dict_set(&dict, வெற்று, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_மொத்தம்(dict))
        printf("av_dict_set does not correctly handle NULL key\n");

    e = வெற்று;
    போது ((e = dict_iterate(dict, e)))
        printf("'%s' '%s'\n", e->சாவி, e->மதிப்பு);
    av_dict_free(&dict);


    //valgrind sensible test
    printf("\nTesting av_dict_set_int()\n");
    av_dict_set_int(&dict, "1", 1, AV_DICT_DONT_STRDUP_VAL);
    av_dict_set_int(&dict, av_strdup("2"), 2, AV_DICT_DONT_STRDUP_சாவி);
    av_dict_set_int(&dict, av_strdup("3"), 3, AV_DICT_DONT_STRDUP_சாவி | AV_DICT_DONT_STRDUP_VAL);
    av_dict_set_int(&dict, "4", 4, 0);
    av_dict_set_int(&dict, "5", 5, AV_DICT_DONT_OVERWRITE);
    av_dict_set_int(&dict, "5", 6, AV_DICT_DONT_OVERWRITE);
    av_dict_set_int(&dict, "12", 1, 0);
    av_dict_set_int(&dict, "12", 2, AV_DICT_APPEND);
    e = வெற்று;
    போது ((e = dict_iterate(dict, e)))
        printf("%s %s\n", e->சாவி, e->மதிப்பு);
    av_dict_free(&dict);

    //valgrind sensible test
    printf("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    எனில் (av_dict_set(&dict, "key", "old", 0) < 0)
        திரும்பு 1;
    e = av_dict_get(dict, "key", வெற்று, 0);
    எனில் (av_dict_set(&dict, e->சாவி, "new val OK", 0) < 0)
        திரும்பு 1;
    e = av_dict_get(dict, "key", வெற்று, 0);
    printf("%s\n", e->மதிப்பு);
    எனில் (av_dict_set(&dict, e->சாவி, e->மதிப்பு, 0) < 0)
        திரும்பு 1;
    e = av_dict_get(dict, "key", வெற்று, 0);
    printf("%s\n", e->மதிப்பு);
    av_dict_free(&dict);

    திரும்பு 0;
}
