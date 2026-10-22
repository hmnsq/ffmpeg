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

#شامل <stdio.h>

#شامل "libavutil/common.h"
#شامل "libavutil/mem.h"
#شامل "libavutil/avstring.h"

صحیح مین(خالی)
{
    صحیح i;
    حرف *fullpath, *ptr;
    ساکن ثابت حرف * ثابت لڑیاں[] = {
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
    ثابت حرف *haystack = "Education consists mainly in what we have unlearned.";
    ثابت حرف * ثابت needle[] = {"learned.", "unlearned.", "Unlearned"};

    لکھو("Testing av_get_token()\n");
    برائے (i = 0; i < FF_ARRAY_ELEMS(لڑیاں); i++) {
        ثابت حرف *p = لڑیاں[i];
        حرف *q;
        لکھو("|%s|", p);
        q = av_get_token(&p, ":");
        لکھو(" -> |%s|", q);
        لکھو(" + |%s|\n", p);
        av_free(q);
    }

    لکھو("Testing av_append_path_component()\n");
    #تعریف_کرو TEST_APPEND_راستہ_COMPONENT(راستہ, component, expected) \
        fullpath = av_append_راستہ_component((راستہ), (component)); \
        لکھو("%s = %s\n", fullpath ? fullpath : "(null)", expected); \
        av_free(fullpath);
    TEST_APPEND_راستہ_COMPONENT(تہی, تہی, "(null)")
    TEST_APPEND_راستہ_COMPONENT("path", تہی, "path");
    TEST_APPEND_راستہ_COMPONENT(تہی, "comp", "comp");
    TEST_APPEND_راستہ_COMPONENT("path", "comp", "path/comp");
    TEST_APPEND_راستہ_COMPONENT("path/", "comp", "path/comp");
    TEST_APPEND_راستہ_COMPONENT("path", "/comp", "path/comp");
    TEST_APPEND_راستہ_COMPONENT("path/", "/comp", "path/comp");
    TEST_APPEND_راستہ_COMPONENT("path/path2/", "/comp/comp2", "path/path2/comp/comp2");

    /*Testing av_strnstr()*/
    #تعریف_کرو TEST_STRNSTR(haystack, needle, hay_لمبائی, expected) \
        ptr = av_strnstr(haystack, needle, hay_لمبائی); \
        اگر (ptr != expected){ \
            لکھو("expected: %p, received %p\n", expected, ptr); \
        }
    TEST_STRNSTR(haystack, needle [0], لڑی_لمبائی(haystack), haystack+44);
    TEST_STRNSTR(haystack, needle [1], لڑی_لمبائی(haystack), haystack+42);
    TEST_STRNSTR(haystack, needle [2], لڑی_لمبائی(haystack), تہی       );
    TEST_STRNSTR(haystack, لڑیاں[1], لڑی_لمبائی(haystack), haystack   );

    /*Testing av_strireplace()*/
    #تعریف_کرو TEST_STRIREPLACE(haystack, needle, expected) \
        ptr = av_strireplace(haystack, needle, "instead"); \
        اگر (ptr == تہی) { \
            لکھو("error, received null pointer!\n"); \
        } ورنہ { \
            اگر (strcmp(ptr, expected) != 0) \
                لکھو( "expected: %s, received: %s\n", expected, ptr); \
            av_free(ptr); \
        }

    TEST_STRIREPLACE(haystack, needle [0], "Education consists mainly in what we have uninstead");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");
    TEST_STRIREPLACE(haystack, needle [2], "Education consists mainly in what we have instead.");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");

    واپس 0;
}
