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

स्थिर ध्रुव AVDictionary_प्रविष्टिः *dict_iterate(ध्रुव AVDictionary *m,
                                             ध्रुव AVDictionary_प्रविष्टिः *पूर्व)
{
    ध्रुव AVDictionary_प्रविष्टिः *dict_get = av_dict_get(m, "", पूर्व, AV_DICT_IGNORE_SUFFIX);
    ध्रुव AVDictionary_प्रविष्टिः *dict_iterate = av_dict_iterate(m, पूर्व);

    यदि (dict_get != dict_iterate) {
#परिभाषय GET(प्रविष्टिः, mem) ((प्रविष्टिः) ? (प्रविष्टिः)->mem : "N/A")
        प्रारूप_लिख("Iterating with av_dict_iterate() yields a different result "
               "than iterating with av_dict_get() and AV_DICT_IGNORE_SUFFIX "
               "(prev: %p, key %s; av_dict_iterate() %p, key %s, value %s; "
               "av_dict_get() %p, key %s, value %s)\n",
               पूर्व, GET(पूर्व, कुञ्चिका),
               dict_iterate, GET(dict_iterate, कुञ्चिका), GET(dict_iterate, मानम्),
               dict_get, GET(dict_get, कुञ्चिका), GET(dict_get, मानम्));
#अपरिभाषय GET
    }
    प्रत्यागम dict_iterate;
}

स्थिर शून्य print_dict(ध्रुव AVDictionary *m)
{
    ध्रुव AVDictionary_प्रविष्टिः *t = रिक्त;
    ध्रुव वर्ण *sep = "";
    यावत् ((t = dict_iterate(m, t))) {
        प्रारूप_लिख("%s%s %s", sep, t->कुञ्चिका, t->मानम्);
        sep = "   ";
    }
    प्रारूप_लिख("\n");
}

स्थिर शून्य test_separators(ध्रुव AVDictionary *m, ध्रुव वर्ण pair, ध्रुव वर्ण val)
{
    AVDictionary *dict = रिक्त;
    वर्ण युग्मानि[] = {pair , '\0'};
    वर्ण vals[]  = {val, '\0'};

    वर्ण *बफर = रिक्त;
    पूर्णाङ्क ret;

    av_dict_copy(&dict, m, 0);
    print_dict(dict);
    av_dict_get_string(dict, &बफर, val, pair);
    प्रारूप_लिख("%s\n", बफर);
    av_dict_free(&dict);
    ret = av_dict_parse_string(&dict, बफर, vals, युग्मानि, 0);
    प्रारूप_लिख("ret %d\n", ret);
    av_freep(&बफर);
    print_dict(dict);
    av_dict_free(&dict);
}

पूर्णाङ्क मुख्यम्(शून्य)
{
    AVDictionary *dict = रिक्त;
    ध्रुव AVDictionary_प्रविष्टिः *e;
    वर्ण *बफर = रिक्त;

    प्रारूप_लिख("Testing av_dict_get_string() and av_dict_parse_string()\n");
    av_dict_get_string(dict, &बफर, '=', ',');
    प्रारूप_लिख("%s\n", बफर);
    av_freep(&बफर);
    av_dict_समुच्चयः(&dict, "aaa", "aaa", 0);
    av_dict_समुच्चयः(&dict, "b,b", "bbb", 0);
    av_dict_समुच्चयः(&dict, "c=c", "ccc", 0);
    av_dict_समुच्चयः(&dict, "ddd", "d,d", 0);
    av_dict_समुच्चयः(&dict, "eee", "e=e", 0);
    av_dict_समुच्चयः(&dict, "f,f", "f=f", 0);
    av_dict_समुच्चयः(&dict, "g=g", "g,g", 0);
    test_separators(dict, ',', '=');
    av_dict_free(&dict);
    av_dict_समुच्चयः(&dict, "aaa", "aaa", 0);
    av_dict_समुच्चयः(&dict, "bbb", "bbb", 0);
    av_dict_समुच्चयः(&dict, "ccc", "ccc", 0);
    av_dict_समुच्चयः(&dict, "\\,=\'\"", "\\,=\'\"", 0);
    test_separators(dict, '"',  '=');
    test_separators(dict, '\'', '=');
    test_separators(dict, ',', '"');
    test_separators(dict, ',', '\'');
    test_separators(dict, '\'', '"');
    test_separators(dict, '"', '\'');
    av_dict_free(&dict);

    प्रारूप_लिख("\nTesting av_dict_set()\n");
    av_dict_समुच्चयः(&dict, "a", "a", 0);
    av_dict_समुच्चयः(&dict, "b", av_strdup("b"), AV_DICT_DONT_STRDUP_VAL);
    av_dict_समुच्चयः(&dict, av_strdup("c"), "c", AV_DICT_DONT_STRDUP_कुञ्चिका);
    av_dict_समुच्चयः(&dict, av_strdup("d"), av_strdup("d"), AV_DICT_DONT_STRDUP_कुञ्चिका | AV_DICT_DONT_STRDUP_VAL);
    av_dict_समुच्चयः(&dict, "e", "e", AV_DICT_DONT_OVERWRITE);
    av_dict_समुच्चयः(&dict, "e", "f", AV_DICT_DONT_OVERWRITE);
    av_dict_समुच्चयः(&dict, "f", "f", 0);
    av_dict_समुच्चयः(&dict, "f", रिक्त, 0);
    av_dict_समुच्चयः(&dict, "ff", "f", 0);
    av_dict_समुच्चयः(&dict, "ff", "f", AV_DICT_APPEND);
    यदि (av_dict_get(dict, रिक्त, रिक्त, 0))
        प्रारूप_लिख("av_dict_get() does not correctly handle NULL key.\n");
    e = रिक्त;
    यावत् ((e = dict_iterate(dict, e)))
        प्रारूप_लिख("%s %s\n", e->कुञ्चिका, e->मानम्);
    av_dict_free(&dict);

    यदि (av_dict_समुच्चयः(&dict, रिक्त, "a", 0) >= 0 ||
        av_dict_समुच्चयः(&dict, रिक्त, "b", 0) >= 0 ||
        av_dict_समुच्चयः(&dict, रिक्त, रिक्त, AV_DICT_DONT_STRDUP_कुञ्चिका) >= 0 ||
        av_dict_समुच्चयः(&dict, रिक्त, av_strdup("b"), AV_DICT_DONT_STRDUP_VAL) >= 0 ||
        av_dict_गणनम्(dict))
        प्रारूप_लिख("av_dict_set does not correctly handle NULL key\n");

    e = रिक्त;
    यावत् ((e = dict_iterate(dict, e)))
        प्रारूप_लिख("'%s' '%s'\n", e->कुञ्चिका, e->मानम्);
    av_dict_free(&dict);


    //valgrind sensible test
    प्रारूप_लिख("\nTesting av_dict_set_int()\n");
    av_dict_समुच्चयः_int(&dict, "1", 1, AV_DICT_DONT_STRDUP_VAL);
    av_dict_समुच्चयः_int(&dict, av_strdup("2"), 2, AV_DICT_DONT_STRDUP_कुञ्चिका);
    av_dict_समुच्चयः_int(&dict, av_strdup("3"), 3, AV_DICT_DONT_STRDUP_कुञ्चिका | AV_DICT_DONT_STRDUP_VAL);
    av_dict_समुच्चयः_int(&dict, "4", 4, 0);
    av_dict_समुच्चयः_int(&dict, "5", 5, AV_DICT_DONT_OVERWRITE);
    av_dict_समुच्चयः_int(&dict, "5", 6, AV_DICT_DONT_OVERWRITE);
    av_dict_समुच्चयः_int(&dict, "12", 1, 0);
    av_dict_समुच्चयः_int(&dict, "12", 2, AV_DICT_APPEND);
    e = रिक्त;
    यावत् ((e = dict_iterate(dict, e)))
        प्रारूप_लिख("%s %s\n", e->कुञ्चिका, e->मानम्);
    av_dict_free(&dict);

    //valgrind sensible test
    प्रारूप_लिख("\nTesting av_dict_set() with existing AVDictionaryEntry.key as key\n");
    यदि (av_dict_समुच्चयः(&dict, "key", "old", 0) < 0)
        प्रत्यागम 1;
    e = av_dict_get(dict, "key", रिक्त, 0);
    यदि (av_dict_समुच्चयः(&dict, e->कुञ्चिका, "new val OK", 0) < 0)
        प्रत्यागम 1;
    e = av_dict_get(dict, "key", रिक्त, 0);
    प्रारूप_लिख("%s\n", e->मानम्);
    यदि (av_dict_समुच्चयः(&dict, e->कुञ्चिका, e->मानम्, 0) < 0)
        प्रत्यागम 1;
    e = av_dict_get(dict, "key", रिक्त, 0);
    प्रारूप_लिख("%s\n", e->मानम्);
    av_dict_free(&dict);

    प्रत्यागम 0;
}
