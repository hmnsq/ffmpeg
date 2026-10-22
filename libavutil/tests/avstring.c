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

#ضمن <stdio.h>

#ضمن "libavutil/common.h"
#ضمن "libavutil/mem.h"
#ضمن "libavutil/avstring.h"

صحيح مکيه(فراغ)
{
    صحيح i;
    حرف *fullpath, *ptr;
    ساكن ثابت حرف * ثابت لڙيون[] = {
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

    لکو("Testing av_get_token()\n");
    لكل (i = 0; i < FF_ARRAY_ELEMS(لڙيون); i++) {
        ثابت حرف *p = لڙيون[i];
        حرف *q;
        لکو("|%s|", p);
        q = av_get_token(&p, ":");
        لکو(" -> |%s|", q);
        لکو(" + |%s|\n", p);
        av_free(q);
    }

    لکو("Testing av_append_path_component()\n");
    #وصف_ڪريو TEST_APPEND_رستو_COMPONENT(رستو, component, expected) \
        fullpath = av_append_رستو_component((رستو), (component)); \
        لکو("%s = %s\n", fullpath ? fullpath : "(null)", expected); \
        av_free(fullpath);
    TEST_APPEND_رستو_COMPONENT(عدم, عدم, "(null)")
    TEST_APPEND_رستو_COMPONENT("path", عدم, "path");
    TEST_APPEND_رستو_COMPONENT(عدم, "comp", "comp");
    TEST_APPEND_رستو_COMPONENT("path", "comp", "path/comp");
    TEST_APPEND_رستو_COMPONENT("path/", "comp", "path/comp");
    TEST_APPEND_رستو_COMPONENT("path", "/comp", "path/comp");
    TEST_APPEND_رستو_COMPONENT("path/", "/comp", "path/comp");
    TEST_APPEND_رستو_COMPONENT("path/path2/", "/comp/comp2", "path/path2/comp/comp2");

    /*Testing av_strnstr()*/
    #وصف_ڪريو TEST_STRNSTR(haystack, needle, hay_ڊيگهائي, expected) \
        ptr = av_strnstr(haystack, needle, hay_ڊيگهائي); \
        إذا (ptr != expected){ \
            لکو("expected: %p, received %p\n", expected, ptr); \
        }
    TEST_STRNSTR(haystack, needle [0], لڙي_ڊيگهه(haystack), haystack+44);
    TEST_STRNSTR(haystack, needle [1], لڙي_ڊيگهه(haystack), haystack+42);
    TEST_STRNSTR(haystack, needle [2], لڙي_ڊيگهه(haystack), عدم       );
    TEST_STRNSTR(haystack, لڙيون[1], لڙي_ڊيگهه(haystack), haystack   );

    /*Testing av_strireplace()*/
    #وصف_ڪريو TEST_STRIREPLACE(haystack, needle, expected) \
        ptr = av_strireplace(haystack, needle, "instead"); \
        إذا (ptr == عدم) { \
            لکو("error, received null pointer!\n"); \
        } وإلا { \
            إذا (strcmp(ptr, expected) != 0) \
                لکو( "expected: %s, received: %s\n", expected, ptr); \
            av_free(ptr); \
        }

    TEST_STRIREPLACE(haystack, needle [0], "Education consists mainly in what we have uninstead");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");
    TEST_STRIREPLACE(haystack, needle [2], "Education consists mainly in what we have instead.");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");

    أرجع 0;
}
