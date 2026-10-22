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

#समावेश "libavutil/mem.h"

#समावेश "libavutil/dict.c"

अटल स्थिर AVDictionaryEntry *dict_iterate(स्थिर AVDictionary *m,
                                             स्थिर AVDictionaryEntry *पूर्व)
{
    स्थिर AVDictionaryEntry *dict_get = av_dict_get(m, "", पूर्व, AV_DICT_IGNORE_SUFFIX);
    स्थिर AVDictionaryEntry *dict_iterate = av_dict_iterate(m, पूर्व);

    अगर (dict_get != dict_iterate) {
#घोषणा GET(entry, mem) ((entry) ? (entry)->mem : "N/A")
        म_लिखो("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               पूर्व, GET(पूर्व, कुंजी),
               dict_iterate, GET(dict_iterate, कुंजी), GET(dict_iterate, मूल्य),
               dict_get, GET(dict_get, कुंजी), GET(dict_get, मूल्य));
#अघोषित GET
    }
    वापस dict_iterate;
}

अटल व्योम print_dict(स्थिर AVDictionary *m)
{
    स्थिर AVDictionaryEntry *t = शून्य;
    स्थिर अक्षर *sep = "";
    जबतक ((t = dict_iterate(m, t))) {
        म_लिखो("%s%s %s", sep, t->कुंजी, t->मूल्य);
        sep = "   ";
    }
    म_लिखो("\n");
}

अटल व्योम test_separators(स्थिर AVDictionary *m, स्थिर अक्षर pair, स्थिर अक्षर val)
{
    AVDictionary *dict = शून्य;
    अक्षर pairs[] = {pair , '\0'};
    अक्षर vals[]  = {val, '\0'};

    अक्षर *बफर = शून्य;
    पूर्णांक ret;

    av_dict_copy(&dict, m, 0);
    print_dict(dict);
    av_dict_get_string(dict, &बफर, val, pair);
    म_लिखो("%s\n", बफर);
    av_dict_free(&dict);
    ret = av_dict_parse_string(&dict, बफर, vals, pairs, 0);
    म_लिखो("ret %d\n", ret);
    av_freep(&बफर);
    print_dict(dict);
    av_dict_free(&dict);
}

पूर्णांक मुख्य(व्योम)
{
    AVDictionary *dict = शून्य;
    स्थिर AVDictionaryEntry *e;
    अक्षर *बफर = शून्य;

    म_लिखो("Testing av_dict_get_string() and av_dict_parse_string()\n");
    av_dict_get_string(dict, &बफर, '=', ',');
    म_लिखो("%s\n", बफर);
    av_freep(&बफर);
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

    म_लिखो("\nTesting av_dict_set()\n");
    av_dict_set(&dict, "a", "a", 0);
    av_dict_set(&dict, "b", av_strdup("b"), AV_DICT_DONT_STRDUP_VAL);
    av_dict_set(&dict, av_strdup("c"), "c", AV_DICT_DONT_STRDUP_कुंजी);
    av_dict_set(&dict, av_strdup("d"), av_strdup("d"), AV_DICT_DONT_STRDUP_कुंजी | AV_DICT_DONT_STRDUP_VAL);
    av_dict_set(&dict, "e", "e", AV_DICT_DONT_OVERWRITE);
    av_dict_set(&dict, "e", "f", AV_DICT_DONT_OVERWRITE);
    av_dict_set(&dict, "f", "f", 0);
    av_dict_set(&dict, "f", शून्य, 0);
    av_dict_set(&dict, "ff", "f", 0);
    av_dict_set(&dict, "ff", "f", AV_DICT_APPEND);
    अगर (av_dict_get(dict, शून्य, शून्य, 0))
        म_लिखो("av_dict_get() does not correctly handle NULL key.\n");
    e = शून्य;
    जबतक ((e = dict_iterate(dict, e)))
        म_लिखो("%s %s\n", e->कुंजी, e->मूल्य);
    av_dict_free(&dict);

    अगर (av_dict_set(&dict, शून्य, "a", 0) >= 0 ||
        av_dict_set(&dict, शून्य, "b", 0) >= 0 ||
        av_dict_set(&dict, शून्य, शून्य, AV_DICT_DONT_STRDUP_कुंजी) >= 0 ||
        av_dict_set(&dict, शून्य, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_गिनती(dict))
        म_लिखो("av_dict_set does not correctly handle NULL key\n");

    e = शून्य;
    जबतक ((e = dict_iterate(dict, e)))
        म_लिखो("'%s' '%s'\n", e->कुंजी, e->मूल्य);
    av_dict_free(&dict);


    //valgrind sensible test
    म_लिखो("\nTesting av_dict_set_int()\n");
    av_dict_set_int(&dict, "1", 1, AV_DICT_DONT_STRDUP_VAL);
    av_dict_set_int(&dict, av_strdup("2"), 2, AV_DICT_DONT_STRDUP_कुंजी);
    av_dict_set_int(&dict, av_strdup("3"), 3, AV_DICT_DONT_STRDUP_कुंजी | AV_DICT_DONT_STRDUP_VAL);
    av_dict_set_int(&dict, "4", 4, 0);
    av_dict_set_int(&dict, "5", 5, AV_DICT_DONT_OVERWRITE);
    av_dict_set_int(&dict, "5", 6, AV_DICT_DONT_OVERWRITE);
    av_dict_set_int(&dict, "12", 1, 0);
    av_dict_set_int(&dict, "12", 2, AV_DICT_APPEND);
    e = शून्य;
    जबतक ((e = dict_iterate(dict, e)))
        म_लिखो("%s %s\n", e->कुंजी, e->मूल्य);
    av_dict_free(&dict);

    //valgrind sensible test
    म_लिखो("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    अगर (av_dict_set(&dict, "key", "old", 0) < 0)
        वापस 1;
    e = av_dict_get(dict, "key", शून्य, 0);
    अगर (av_dict_set(&dict, e->कुंजी, "new val OK", 0) < 0)
        वापस 1;
    e = av_dict_get(dict, "key", शून्य, 0);
    म_लिखो("%s\n", e->मूल्य);
    अगर (av_dict_set(&dict, e->कुंजी, e->मूल्य, 0) < 0)
        वापस 1;
    e = av_dict_get(dict, "key", शून्य, 0);
    म_लिखो("%s\n", e->मूल्य);
    av_dict_free(&dict);

    वापस 0;
}
