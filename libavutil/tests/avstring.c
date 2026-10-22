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

صحيح اصلي(فراغ)
{
    صحيح i;
    حرف *fullpath, *ptr;
    ساكن ثابت حرف * ثابت مزي_ګانې[] = {
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

    چاپ_کړه("Testing av_get_token()\n");
    لكل (i = 0; i < FF_ARRAY_ELEMS(مزي_ګانې); i++) {
        ثابت حرف *p = مزي_ګانې[i];
        حرف *q;
        چاپ_کړه("|%s|", p);
        q = av_get_token(&p, ":");
        چاپ_کړه(" -> |%s|", q);
        چاپ_کړه(" + |%s|\n", p);
        av_free(q);
    }

    چاپ_کړه("Testing av_append_path_component()\n");
    #تعریف_کړه TEST_APPEND_لار_COMPONENT(لار, component, expected) \
        fullpath = av_append_لار_component((لار), (component)); \
        چاپ_کړه("%s = %s\n", fullpath ? fullpath : "(null)", expected); \
        av_free(fullpath);
    TEST_APPEND_لار_COMPONENT(عدم, عدم, "(null)")
    TEST_APPEND_لار_COMPONENT("path", عدم, "path");
    TEST_APPEND_لار_COMPONENT(عدم, "comp", "comp");
    TEST_APPEND_لار_COMPONENT("path", "comp", "path/comp");
    TEST_APPEND_لار_COMPONENT("path/", "comp", "path/comp");
    TEST_APPEND_لار_COMPONENT("path", "/comp", "path/comp");
    TEST_APPEND_لار_COMPONENT("path/", "/comp", "path/comp");
    TEST_APPEND_لار_COMPONENT("path/path2/", "/comp/comp2", "path/path2/comp/comp2");

    /*Testing av_strnstr()*/
    #تعریف_کړه TEST_STRNSTR(haystack, needle, hay_اوږدتیا, expected) \
        ptr = av_strnstr(haystack, needle, hay_اوږدتیا); \
        إذا (ptr != expected){ \
            چاپ_کړه("expected: %p, received %p\n", expected, ptr); \
        }
    TEST_STRNSTR(haystack, needle [0], مزي_اوږدوالی(haystack), haystack+44);
    TEST_STRNSTR(haystack, needle [1], مزي_اوږدوالی(haystack), haystack+42);
    TEST_STRNSTR(haystack, needle [2], مزي_اوږدوالی(haystack), عدم       );
    TEST_STRNSTR(haystack, مزي_ګانې[1], مزي_اوږدوالی(haystack), haystack   );

    /*Testing av_strireplace()*/
    #تعریف_کړه TEST_STRIREPLACE(haystack, needle, expected) \
        ptr = av_strireplace(haystack, needle, "instead"); \
        إذا (ptr == عدم) { \
            چاپ_کړه("error, received null pointer!\n"); \
        } وإلا { \
            إذا (strcmp(ptr, expected) != 0) \
                چاپ_کړه( "expected: %s, received: %s\n", expected, ptr); \
            av_free(ptr); \
        }

    TEST_STRIREPLACE(haystack, needle [0], "Education consists mainly in what we have uninstead");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");
    TEST_STRIREPLACE(haystack, needle [2], "Education consists mainly in what we have instead.");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");

    أرجع 0;
}
