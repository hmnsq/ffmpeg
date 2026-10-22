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

صحيح اصلی(فراغ)
{
    صحيح i;
    حرف *fullpath, *ptr;
    ساكن ثابت حرف * ثابت رشتهها[] = {
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

    چاپ_کن("Testing av_get_token()\n");
    لكل (i = 0; i < FF_ARRAY_ELEMS(رشتهها); i++) {
        ثابت حرف *p = رشتهها[i];
        حرف *q;
        چاپ_کن("|%s|", p);
        q = av_get_token(&p, ":");
        چاپ_کن(" -> |%s|", q);
        چاپ_کن(" + |%s|\n", p);
        av_free(q);
    }

    چاپ_کن("Testing av_append_path_component()\n");
    #تعریف_کن TEST_APPEND_مسیر_COMPONENT(مسیر, component, expected) \
        fullpath = av_append_مسیر_component((مسیر), (component)); \
        چاپ_کن("%s = %s\n", fullpath ? fullpath : "(null)", expected); \
        av_free(fullpath);
    TEST_APPEND_مسیر_COMPONENT(عدم, عدم, "(null)")
    TEST_APPEND_مسیر_COMPONENT("path", عدم, "path");
    TEST_APPEND_مسیر_COMPONENT(عدم, "comp", "comp");
    TEST_APPEND_مسیر_COMPONENT("path", "comp", "path/comp");
    TEST_APPEND_مسیر_COMPONENT("path/", "comp", "path/comp");
    TEST_APPEND_مسیر_COMPONENT("path", "/comp", "path/comp");
    TEST_APPEND_مسیر_COMPONENT("path/", "/comp", "path/comp");
    TEST_APPEND_مسیر_COMPONENT("path/path2/", "/comp/comp2", "path/path2/comp/comp2");

    /*Testing av_strnstr()*/
    #تعریف_کن TEST_STRNSTR(haystack, needle, hay_درازی, expected) \
        ptr = av_strnstr(haystack, needle, hay_درازی); \
        إذا (ptr != expected){ \
            چاپ_کن("expected: %p, received %p\n", expected, ptr); \
        }
    TEST_STRNSTR(haystack, needle [0], طول_رشته(haystack), haystack+44);
    TEST_STRNSTR(haystack, needle [1], طول_رشته(haystack), haystack+42);
    TEST_STRNSTR(haystack, needle [2], طول_رشته(haystack), عدم       );
    TEST_STRNSTR(haystack, رشتهها[1], طول_رشته(haystack), haystack   );

    /*Testing av_strireplace()*/
    #تعریف_کن TEST_STRIREPLACE(haystack, needle, expected) \
        ptr = av_strireplace(haystack, needle, "instead"); \
        إذا (ptr == عدم) { \
            چاپ_کن("error, received null pointer!\n"); \
        } وإلا { \
            إذا (strcmp(ptr, expected) != 0) \
                چاپ_کن( "expected: %s, received: %s\n", expected, ptr); \
            av_free(ptr); \
        }

    TEST_STRIREPLACE(haystack, needle [0], "Education consists mainly in what we have uninstead");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");
    TEST_STRIREPLACE(haystack, needle [2], "Education consists mainly in what we have instead.");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");

    أرجع 0;
}
