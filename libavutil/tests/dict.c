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

#അന്തര്ഭാവ "libavutil/mem.h"

#അന്തര്ഭാവ "libavutil/dict.c"

സ്ഥിതം സ്ഥിരം AVDictionaryEntry *dict_iterate(സ്ഥിരം AVDictionary *m,
                                             സ്ഥിരം AVDictionaryEntry *prev)
{
    സ്ഥിരം AVDictionaryEntry *dict_get = av_dict_get(m, "", prev, AV_DICT_IGNORE_SUFFIX);
    സ്ഥിരം AVDictionaryEntry *dict_iterate = av_dict_iterate(m, prev);

    എങ്കിൽ (dict_get != dict_iterate) {
#define GET(entry, mem) ((entry) ? (entry)->mem : "N/A")
        printf("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               prev, GET(prev, താക്കോൽ),
               dict_iterate, GET(dict_iterate, താക്കോൽ), GET(dict_iterate, മൂല്യം),
               dict_get, GET(dict_get, താക്കോൽ), GET(dict_get, മൂല്യം));
#undef GET
    }
    തിരികെ dict_iterate;
}

സ്ഥിതം ശൂന്യം print_dict(സ്ഥിരം AVDictionary *m)
{
    സ്ഥിരം AVDictionaryEntry *t = ശൂന്യ;
    സ്ഥിരം അക്ഷരം *sep = "";
    ആകുമ്പോൾ ((t = dict_iterate(m, t))) {
        printf("%s%s %s", sep, t->താക്കോൽ, t->മൂല്യം);
        sep = "   ";
    }
    printf("\n");
}

സ്ഥിതം ശൂന്യം test_separators(സ്ഥിരം AVDictionary *m, സ്ഥിരം അക്ഷരം pair, സ്ഥിരം അക്ഷരം val)
{
    AVDictionary *dict = ശൂന്യ;
    അക്ഷരം pairs[] = {pair , '\0'};
    അക്ഷരം vals[]  = {val, '\0'};

    അക്ഷരം *buffer = ശൂന്യ;
    പൂർണ്ണസംഖ്യ ret;

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

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    AVDictionary *dict = ശൂന്യ;
    സ്ഥിരം AVDictionaryEntry *e;
    അക്ഷരം *buffer = ശൂന്യ;

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
    av_dict_set(&dict, av_strdup("c"), "c", AV_DICT_DONT_STRDUP_താക്കോൽ);
    av_dict_set(&dict, av_strdup("d"), av_strdup("d"), AV_DICT_DONT_STRDUP_താക്കോൽ | AV_DICT_DONT_STRDUP_VAL);
    av_dict_set(&dict, "e", "e", AV_DICT_DONT_OVERWRITE);
    av_dict_set(&dict, "e", "f", AV_DICT_DONT_OVERWRITE);
    av_dict_set(&dict, "f", "f", 0);
    av_dict_set(&dict, "f", ശൂന്യ, 0);
    av_dict_set(&dict, "ff", "f", 0);
    av_dict_set(&dict, "ff", "f", AV_DICT_APPEND);
    എങ്കിൽ (av_dict_get(dict, ശൂന്യ, ശൂന്യ, 0))
        printf("av_dict_get() does not correctly handle NULL key.\n");
    e = ശൂന്യ;
    ആകുമ്പോൾ ((e = dict_iterate(dict, e)))
        printf("%s %s\n", e->താക്കോൽ, e->മൂല്യം);
    av_dict_free(&dict);

    എങ്കിൽ (av_dict_set(&dict, ശൂന്യ, "a", 0) >= 0 ||
        av_dict_set(&dict, ശൂന്യ, "b", 0) >= 0 ||
        av_dict_set(&dict, ശൂന്യ, ശൂന്യ, AV_DICT_DONT_STRDUP_താക്കോൽ) >= 0 ||
        av_dict_set(&dict, ശൂന്യ, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_എണ്ണം(dict))
        printf("av_dict_set does not correctly handle NULL key\n");

    e = ശൂന്യ;
    ആകുമ്പോൾ ((e = dict_iterate(dict, e)))
        printf("'%s' '%s'\n", e->താക്കോൽ, e->മൂല്യം);
    av_dict_free(&dict);


    //valgrind sensible test
    printf("\nTesting av_dict_set_int()\n");
    av_dict_set_int(&dict, "1", 1, AV_DICT_DONT_STRDUP_VAL);
    av_dict_set_int(&dict, av_strdup("2"), 2, AV_DICT_DONT_STRDUP_താക്കോൽ);
    av_dict_set_int(&dict, av_strdup("3"), 3, AV_DICT_DONT_STRDUP_താക്കോൽ | AV_DICT_DONT_STRDUP_VAL);
    av_dict_set_int(&dict, "4", 4, 0);
    av_dict_set_int(&dict, "5", 5, AV_DICT_DONT_OVERWRITE);
    av_dict_set_int(&dict, "5", 6, AV_DICT_DONT_OVERWRITE);
    av_dict_set_int(&dict, "12", 1, 0);
    av_dict_set_int(&dict, "12", 2, AV_DICT_APPEND);
    e = ശൂന്യ;
    ആകുമ്പോൾ ((e = dict_iterate(dict, e)))
        printf("%s %s\n", e->താക്കോൽ, e->മൂല്യം);
    av_dict_free(&dict);

    //valgrind sensible test
    printf("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    എങ്കിൽ (av_dict_set(&dict, "key", "old", 0) < 0)
        തിരികെ 1;
    e = av_dict_get(dict, "key", ശൂന്യ, 0);
    എങ്കിൽ (av_dict_set(&dict, e->താക്കോൽ, "new val OK", 0) < 0)
        തിരികെ 1;
    e = av_dict_get(dict, "key", ശൂന്യ, 0);
    printf("%s\n", e->മൂല്യം);
    എങ്കിൽ (av_dict_set(&dict, e->താക്കോൽ, e->മൂല്യം, 0) < 0)
        തിരികെ 1;
    e = av_dict_get(dict, "key", ശൂന്യ, 0);
    printf("%s\n", e->മൂല്യം);
    av_dict_free(&dict);

    തിരികെ 0;
}
