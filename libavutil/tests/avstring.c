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

#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/common.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"
#ಅನ್ತರ್ಭಾವ "libavutil/avstring.h"

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ i;
    ಅಕ್ಷರ *fullpath, *ptr;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ ಅಕ್ಷರಸರಣಿಗಳು[] = {
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
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *haystack = "Education consists mainly in what we have unlearned.";
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ needle[] = {"learned.", "unlearned.", "Unlearned"};

    ಬರೆ("Testing av_get_token()\n");
    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(ಅಕ್ಷರಸರಣಿಗಳು); i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p = ಅಕ್ಷರಸರಣಿಗಳು[i];
        ಅಕ್ಷರ *q;
        ಬರೆ("|%s|", p);
        q = av_get_token(&p, ":");
        ಬರೆ(" -> |%s|", q);
        ಬರೆ(" + |%s|\n", p);
        av_free(q);
    }

    ಬರೆ("Testing av_append_path_component()\n");
    #ವ್ಯಾಖ್ಯಾನಿಸು TEST_APPEND_ಮಾರ್ಗ_COMPONENT(ಮಾರ್ಗ, component, expected) \
        fullpath = av_append_ಮಾರ್ಗ_component((ಮಾರ್ಗ), (component)); \
        ಬರೆ("%s = %s\n", fullpath ? fullpath : "(null)", expected); \
        av_free(fullpath);
    TEST_APPEND_ಮಾರ್ಗ_COMPONENT(ಖಾಲಿ, ಖಾಲಿ, "(null)")
    TEST_APPEND_ಮಾರ್ಗ_COMPONENT("path", ಖಾಲಿ, "path");
    TEST_APPEND_ಮಾರ್ಗ_COMPONENT(ಖಾಲಿ, "comp", "comp");
    TEST_APPEND_ಮಾರ್ಗ_COMPONENT("path", "comp", "path/comp");
    TEST_APPEND_ಮಾರ್ಗ_COMPONENT("path/", "comp", "path/comp");
    TEST_APPEND_ಮಾರ್ಗ_COMPONENT("path", "/comp", "path/comp");
    TEST_APPEND_ಮಾರ್ಗ_COMPONENT("path/", "/comp", "path/comp");
    TEST_APPEND_ಮಾರ್ಗ_COMPONENT("path/path2/", "/comp/comp2", "path/path2/comp/comp2");

    /*Testing av_strnstr()*/
    #ವ್ಯಾಖ್ಯಾನಿಸು TEST_STRNSTR(haystack, needle, hay_ಉದ್ದಳತೆ, expected) \
        ptr = av_strnstr(haystack, needle, hay_ಉದ್ದಳತೆ); \
        ಆದರೆ (ptr != expected){ \
            ಬರೆ("expected: %p, received %p\n", expected, ptr); \
        }
    TEST_STRNSTR(haystack, needle [0], ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(haystack), haystack+44);
    TEST_STRNSTR(haystack, needle [1], ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(haystack), haystack+42);
    TEST_STRNSTR(haystack, needle [2], ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(haystack), ಖಾಲಿ       );
    TEST_STRNSTR(haystack, ಅಕ್ಷರಸರಣಿಗಳು[1], ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(haystack), haystack   );

    /*Testing av_strireplace()*/
    #ವ್ಯಾಖ್ಯಾನಿಸು TEST_STRIREPLACE(haystack, needle, expected) \
        ptr = av_strireplace(haystack, needle, "instead"); \
        ಆದರೆ (ptr == ಖಾಲಿ) { \
            ಬರೆ("error, received null pointer!\n"); \
        } ಇಲ್ಲದಿದ್ದರೆ { \
            ಆದರೆ (strcmp(ptr, expected) != 0) \
                ಬರೆ( "expected: %s, received: %s\n", expected, ptr); \
            av_free(ptr); \
        }

    TEST_STRIREPLACE(haystack, needle [0], "Education consists mainly in what we have uninstead");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");
    TEST_STRIREPLACE(haystack, needle [2], "Education consists mainly in what we have instead.");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");

    ಹಿಂತಿರುಗಿ 0;
}
