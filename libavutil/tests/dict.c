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

#अन्तर्भाव "libavutil/mem.h"

#अन्तर्भाव "libavutil/dict.c"

स्थिर ध्रुव AVDictionaryEntry *dict_iterate(ध्रुव AVDictionary *m,
                                             ध्रुव AVDictionaryEntry *prev)
{
    ध्रुव AVDictionaryEntry *dict_get = av_dict_get(m, "", prev, AV_DICT_IGNORE_SUFFIX);
    ध्रुव AVDictionaryEntry *dict_iterate = av_dict_iterate(m, prev);

    सचे (dict_get != dict_iterate) {
#define GET(entry, mem) ((entry) ? (entry)->mem : "N/A")
        printf("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               prev, GET(prev, कुञ्चिका),
               dict_iterate, GET(dict_iterate, कुञ्चिका), GET(dict_iterate, मानम्),
               dict_get, GET(dict_get, कुञ्चिका), GET(dict_get, मानम्));
#undef GET
    }
    पटिनिवत्त dict_iterate;
}

स्थिर शून्य print_dict(ध्रुव AVDictionary *m)
{
    ध्रुव AVDictionaryEntry *t = रिक्त;
    ध्रुव वर्ण *sep = "";
    याव ((t = dict_iterate(m, t))) {
        printf("%s%s %s", sep, t->कुञ्चिका, t->मानम्);
        sep = "   ";
    }
    printf("\n");
}

स्थिर शून्य test_separators(ध्रुव AVDictionary *m, ध्रुव वर्ण pair, ध्रुव वर्ण val)
{
    AVDictionary *dict = रिक्त;
    वर्ण pairs[] = {pair , '\0'};
    वर्ण vals[]  = {val, '\0'};

    वर्ण *buffer = रिक्त;
    पूर्णाङ्क ret;

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

पूर्णाङ्क main(शून्य)
{
    AVDictionary *dict = रिक्त;
    ध्रुव AVDictionaryEntry *e;
    वर्ण *buffer = रिक्त;

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
    av_dict_set(&dict, av_strdup("c"), "c", AV_DICT_DONT_STRDUP_कुञ्चिका);
    av_dict_set(&dict, av_strdup("d"), av_strdup("d"), AV_DICT_DONT_STRDUP_कुञ्चिका | AV_DICT_DONT_STRDUP_VAL);
    av_dict_set(&dict, "e", "e", AV_DICT_DONT_OVERWRITE);
    av_dict_set(&dict, "e", "f", AV_DICT_DONT_OVERWRITE);
    av_dict_set(&dict, "f", "f", 0);
    av_dict_set(&dict, "f", रिक्त, 0);
    av_dict_set(&dict, "ff", "f", 0);
    av_dict_set(&dict, "ff", "f", AV_DICT_APPEND);
    सचे (av_dict_get(dict, रिक्त, रिक्त, 0))
        printf("av_dict_get() does not correctly handle NULL key.\n");
    e = रिक्त;
    याव ((e = dict_iterate(dict, e)))
        printf("%s %s\n", e->कुञ्चिका, e->मानम्);
    av_dict_free(&dict);

    सचे (av_dict_set(&dict, रिक्त, "a", 0) >= 0 ||
        av_dict_set(&dict, रिक्त, "b", 0) >= 0 ||
        av_dict_set(&dict, रिक्त, रिक्त, AV_DICT_DONT_STRDUP_कुञ्चिका) >= 0 ||
        av_dict_set(&dict, रिक्त, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_गणनम्(dict))
        printf("av_dict_set does not correctly handle NULL key\n");

    e = रिक्त;
    याव ((e = dict_iterate(dict, e)))
        printf("'%s' '%s'\n", e->कुञ्चिका, e->मानम्);
    av_dict_free(&dict);


    //valgrind sensible test
    printf("\nTesting av_dict_set_int()\n");
    av_dict_set_int(&dict, "1", 1, AV_DICT_DONT_STRDUP_VAL);
    av_dict_set_int(&dict, av_strdup("2"), 2, AV_DICT_DONT_STRDUP_कुञ्चिका);
    av_dict_set_int(&dict, av_strdup("3"), 3, AV_DICT_DONT_STRDUP_कुञ्चिका | AV_DICT_DONT_STRDUP_VAL);
    av_dict_set_int(&dict, "4", 4, 0);
    av_dict_set_int(&dict, "5", 5, AV_DICT_DONT_OVERWRITE);
    av_dict_set_int(&dict, "5", 6, AV_DICT_DONT_OVERWRITE);
    av_dict_set_int(&dict, "12", 1, 0);
    av_dict_set_int(&dict, "12", 2, AV_DICT_APPEND);
    e = रिक्त;
    याव ((e = dict_iterate(dict, e)))
        printf("%s %s\n", e->कुञ्चिका, e->मानम्);
    av_dict_free(&dict);

    //valgrind sensible test
    printf("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    सचे (av_dict_set(&dict, "key", "old", 0) < 0)
        पटिनिवत्त 1;
    e = av_dict_get(dict, "key", रिक्त, 0);
    सचे (av_dict_set(&dict, e->कुञ्चिका, "new val OK", 0) < 0)
        पटिनिवत्त 1;
    e = av_dict_get(dict, "key", रिक्त, 0);
    printf("%s\n", e->मानम्);
    सचे (av_dict_set(&dict, e->कुञ्चिका, e->मानम्, 0) < 0)
        पटिनिवत्त 1;
    e = av_dict_get(dict, "key", रिक्त, 0);
    printf("%s\n", e->मानम्);
    av_dict_free(&dict);

    पटिनिवत्त 0;
}
