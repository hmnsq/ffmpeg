/*
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

#অন্তর্ভাব <stdio.h>

#অন্তর্ভাব "libavutil/common.h"
#অন্তর্ভাব "libavutil/mem.h"
#অন্তর্ভাব "libavutil/avstring.h"

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    পূর্ণসংখ্যা i;
    অক্ষর *fullpath, *ptr;
    স্থির ধ্রুবক অক্ষর * ধ্রুবক strings[] = {
        "''",
        "",
        ":",
        "\\",
        "'",
        "    ''    :",
        "    ''  ''  :",
        "foo   '' :",
        "'foo'",
        "foo     ",
        "  '  foo  '  ",
        "foo\\",
        "foo':  blah:blah",
        "foo\\:  blah:blah",
        "foo\'",
        "'foo :  '  :blahblah",
        "\\ :blah",
        "     foo",
        "      foo       ",
        "      foo     \\ ",
        "foo ':blah",
        " foo   bar    :   blahblah",
        "\\f\\o\\o",
        "'foo : \\ \\  '   : blahblah",
        "'\\fo\\o:': blahblah",
        "\\'fo\\o\\:':  foo  '  :blahblah"
    };
    ধ্রুবক অক্ষর *haystack = "Education consists mainly in what we have unlearned.";
    ধ্রুবক অক্ষর * ধ্রুবক needle[] = {"learned.", "unlearned.", "Unlearned"};

    printf("Testing av_get_token()\n");
    জন্য (i = 0; i < FF_ARRAY_ELEMS(strings); i++) {
        ধ্রুবক অক্ষর *p = strings[i];
        অক্ষর *q;
        printf("|%s|", p);
        q = av_get_token(&p, ":");
        printf(" -> |%s|", q);
        printf(" + |%s|\n", p);
        av_free(q);
    }

    printf("Testing av_append_path_component()\n");
    #define TEST_APPEND_PATH_COMPONENT(path, component, expected) \
        fullpath = av_append_path_component((path), (component)); \
        printf("%s = %s\n", fullpath ? fullpath : "(null)", expected); \
        av_free(fullpath);
    TEST_APPEND_PATH_COMPONENT(ফাঁকা, ফাঁকা, "(null)")
    TEST_APPEND_PATH_COMPONENT("path", ফাঁকা, "path");
    TEST_APPEND_PATH_COMPONENT(ফাঁকা, "comp", "comp");
    TEST_APPEND_PATH_COMPONENT("path", "comp", "path/comp");
    TEST_APPEND_PATH_COMPONENT("path/", "comp", "path/comp");
    TEST_APPEND_PATH_COMPONENT("path", "/comp", "path/comp");
    TEST_APPEND_PATH_COMPONENT("path/", "/comp", "path/comp");
    TEST_APPEND_PATH_COMPONENT("path/path2/", "/comp/comp2", "path/path2/comp/comp2");

    /*Testing av_strnstr()*/
    #define TEST_STRNSTR(haystack, needle, hay_দৈর্ঘ্য, expected) \
        ptr = av_strnstr(haystack, needle, hay_দৈর্ঘ্য); \
        যদি (ptr != expected){ \
            printf("expected: %p, received %p\n", expected, ptr); \
        }
    TEST_STRNSTR(haystack, needle [0], strlen(haystack), haystack+44);
    TEST_STRNSTR(haystack, needle [1], strlen(haystack), haystack+42);
    TEST_STRNSTR(haystack, needle [2], strlen(haystack), ফাঁকা       );
    TEST_STRNSTR(haystack, strings[1], strlen(haystack), haystack   );

    /*Testing av_strireplace()*/
    #define TEST_STRIREPLACE(haystack, needle, expected) \
        ptr = av_strireplace(haystack, needle, "instead"); \
        যদি (ptr == ফাঁকা) { \
            printf("error, received null pointer!\n"); \
        } অন্যথা { \
            যদি (strcmp(ptr, expected) != 0) \
                printf( "expected: %s, received: %s\n", expected, ptr); \
            av_free(ptr); \
        }

    TEST_STRIREPLACE(haystack, needle [0], "Education consists mainly in what we have uninstead");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");
    TEST_STRIREPLACE(haystack, needle [2], "Education consists mainly in what we have instead.");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");

    ফেরত 0;
}
