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

#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/common.h"
#अन्तर्भाव "libavutil/mem.h"
#अन्तर्भाव "libavutil/avstring.h"

पूर्णाङ्क मुख्यम्(शून्य)
{
    पूर्णाङ्क i;
    वर्ण *fullpath, *ptr;
    स्थिर ध्रुव वर्ण * ध्रुव वाक्यानि[] = {
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
    ध्रुव वर्ण *haystack = "Education consists mainly in what we have unlearned.";
    ध्रुव वर्ण * ध्रुव needle[] = {"learned.", "unlearned.", "Unlearned"};

    प्रारूप_लिख("Testing av_get_token()\n");
    प्रति (i = 0; i < FF_ARRAY_ELEMS(वाक्यानि); i++) {
        ध्रुव वर्ण *p = वाक्यानि[i];
        वर्ण *q;
        प्रारूप_लिख("|%s|", p);
        q = av_get_token(&p, ":");
        प्रारूप_लिख(" -> |%s|", q);
        प्रारूप_लिख(" + |%s|\n", p);
        av_free(q);
    }

    प्रारूप_लिख("Testing av_append_path_component()\n");
    #परिभाषय TEST_APPEND_मार्गः_COMPONENT(मार्गः, component, expected) \
        fullpath = av_append_मार्गः_component((मार्गः), (component)); \
        प्रारूप_लिख("%s = %s\n", fullpath ? fullpath : "(null)", expected); \
        av_free(fullpath);
    TEST_APPEND_मार्गः_COMPONENT(रिक्त, रिक्त, "(null)")
    TEST_APPEND_मार्गः_COMPONENT("path", रिक्त, "path");
    TEST_APPEND_मार्गः_COMPONENT(रिक्त, "comp", "comp");
    TEST_APPEND_मार्गः_COMPONENT("path", "comp", "path/comp");
    TEST_APPEND_मार्गः_COMPONENT("path/", "comp", "path/comp");
    TEST_APPEND_मार्गः_COMPONENT("path", "/comp", "path/comp");
    TEST_APPEND_मार्गः_COMPONENT("path/", "/comp", "path/comp");
    TEST_APPEND_मार्गः_COMPONENT("path/path2/", "/comp/comp2", "path/path2/comp/comp2");

    /*Testing av_strnstr()*/
    #परिभाषय TEST_STRNSTR(haystack, needle, hay_दीर्घता, expected) \
        ptr = av_strnstr(haystack, needle, hay_दीर्घता); \
        यदि (ptr != expected){ \
            प्रारूप_लिख("expected: %p, received %p\n", expected, ptr); \
        }
    TEST_STRNSTR(haystack, needle [0], वाक्यदैर्घ्यम्(haystack), haystack+44);
    TEST_STRNSTR(haystack, needle [1], वाक्यदैर्घ्यम्(haystack), haystack+42);
    TEST_STRNSTR(haystack, needle [2], वाक्यदैर्घ्यम्(haystack), रिक्त       );
    TEST_STRNSTR(haystack, वाक्यानि[1], वाक्यदैर्घ्यम्(haystack), haystack   );

    /*Testing av_strireplace()*/
    #परिभाषय TEST_STRIREPLACE(haystack, needle, expected) \
        ptr = av_strireplace(haystack, needle, "instead"); \
        यदि (ptr == रिक्त) { \
            प्रारूप_लिख("error, received null pointer!\n"); \
        } अन्यथा { \
            यदि (वाक्यं_तुलय(ptr, expected) != 0) \
                प्रारूप_लिख( "expected: %s, received: %s\n", expected, ptr); \
            av_free(ptr); \
        }

    TEST_STRIREPLACE(haystack, needle [0], "Education consists mainly in what we have uninstead");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");
    TEST_STRIREPLACE(haystack, needle [2], "Education consists mainly in what we have instead.");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");

    प्रत्यागम 0;
}
