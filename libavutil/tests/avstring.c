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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avstring.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਪੂਰਨ i;
    ਅੱਖਰ *fullpath, *ptr;
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ ਲੜੀਆਂ[] = {
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
    ਅਚਲ ਅੱਖਰ *haystack = "Education consists mainly in what we have unlearned.";
    ਅਚਲ ਅੱਖਰ * ਅਚਲ needle[] = {"learned.", "unlearned.", "Unlearned"};

    ਲਿਖੋ("Testing av_get_token()\n");
    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(ਲੜੀਆਂ); i++) {
        ਅਚਲ ਅੱਖਰ *p = ਲੜੀਆਂ[i];
        ਅੱਖਰ *q;
        ਲਿਖੋ("|%s|", p);
        q = av_get_token(&p, ":");
        ਲਿਖੋ(" -> |%s|", q);
        ਲਿਖੋ(" + |%s|\n", p);
        av_free(q);
    }

    ਲਿਖੋ("Testing av_append_path_component()\n");
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_APPEND_ਰਸਤਾ_COMPONENT(ਰਸਤਾ, component, expected) \
        fullpath = av_append_ਰਸਤਾ_component((ਰਸਤਾ), (component)); \
        ਲਿਖੋ("%s = %s\n", fullpath ? fullpath : "(null)", expected); \
        av_free(fullpath);
    TEST_APPEND_ਰਸਤਾ_COMPONENT(ਨਿਰਾ, ਨਿਰਾ, "(null)")
    TEST_APPEND_ਰਸਤਾ_COMPONENT("path", ਨਿਰਾ, "path");
    TEST_APPEND_ਰਸਤਾ_COMPONENT(ਨਿਰਾ, "comp", "comp");
    TEST_APPEND_ਰਸਤਾ_COMPONENT("path", "comp", "path/comp");
    TEST_APPEND_ਰਸਤਾ_COMPONENT("path/", "comp", "path/comp");
    TEST_APPEND_ਰਸਤਾ_COMPONENT("path", "/comp", "path/comp");
    TEST_APPEND_ਰਸਤਾ_COMPONENT("path/", "/comp", "path/comp");
    TEST_APPEND_ਰਸਤਾ_COMPONENT("path/path2/", "/comp/comp2", "path/path2/comp/comp2");

    /*Testing av_strnstr()*/
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_STRNSTR(haystack, needle, hay_ਲੰਮਾਈ, expected) \
        ptr = av_strnstr(haystack, needle, hay_ਲੰਮਾਈ); \
        ਜੇ (ptr != expected){ \
            ਲਿਖੋ("expected: %p, received %p\n", expected, ptr); \
        }
    TEST_STRNSTR(haystack, needle [0], ਲੜੀ_ਲੰਬਾਈ(haystack), haystack+44);
    TEST_STRNSTR(haystack, needle [1], ਲੜੀ_ਲੰਬਾਈ(haystack), haystack+42);
    TEST_STRNSTR(haystack, needle [2], ਲੜੀ_ਲੰਬਾਈ(haystack), ਨਿਰਾ       );
    TEST_STRNSTR(haystack, ਲੜੀਆਂ[1], ਲੜੀ_ਲੰਬਾਈ(haystack), haystack   );

    /*Testing av_strireplace()*/
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_STRIREPLACE(haystack, needle, expected) \
        ptr = av_strireplace(haystack, needle, "instead"); \
        ਜੇ (ptr == ਨਿਰਾ) { \
            ਲਿਖੋ("error, received null pointer!\n"); \
        } ਨਹੀਂਤਾਂ { \
            ਜੇ (strcmp(ptr, expected) != 0) \
                ਲਿਖੋ( "expected: %s, received: %s\n", expected, ptr); \
            av_free(ptr); \
        }

    TEST_STRIREPLACE(haystack, needle [0], "Education consists mainly in what we have uninstead");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");
    TEST_STRIREPLACE(haystack, needle [2], "Education consists mainly in what we have instead.");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");

    ਵਾਪਸ 0;
}
