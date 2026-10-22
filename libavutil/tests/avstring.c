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

#समावेश <stdio.h>

#समावेश "libavutil/common.h"
#समावेश "libavutil/mem.h"
#समावेश "libavutil/avstring.h"

पूर्णांक मुख्य(व्योम)
{
    पूर्णांक i;
    अक्षर *fullpath, *ptr;
    अटल स्थिर अक्षर * स्थिर strings[] = {
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
    स्थिर अक्षर *haystack = "Education consists mainly in what we have unlearned.";
    स्थिर अक्षर * स्थिर needle[] = {"learned.", "unlearned.", "Unlearned"};

    म_लिखो("Testing av_get_token()\n");
    क्रम (i = 0; i < FF_ARRAY_ELEMS(strings); i++) {
        स्थिर अक्षर *p = strings[i];
        अक्षर *q;
        म_लिखो("|%s|", p);
        q = av_get_token(&p, ":");
        म_लिखो(" -> |%s|", q);
        म_लिखो(" + |%s|\n", p);
        av_free(q);
    }

    म_लिखो("Testing av_append_path_component()\n");
    #घोषणा TEST_APPEND_PATH_COMPONENT(path, component, expected) \
        fullpath = av_append_path_component((path), (component)); \
        म_लिखो("%s = %s\n", fullpath ? fullpath : "(null)", expected); \
        av_free(fullpath);
    TEST_APPEND_PATH_COMPONENT(शून्य, शून्य, "(null)")
    TEST_APPEND_PATH_COMPONENT("path", शून्य, "path");
    TEST_APPEND_PATH_COMPONENT(शून्य, "comp", "comp");
    TEST_APPEND_PATH_COMPONENT("path", "comp", "path/comp");
    TEST_APPEND_PATH_COMPONENT("path/", "comp", "path/comp");
    TEST_APPEND_PATH_COMPONENT("path", "/comp", "path/comp");
    TEST_APPEND_PATH_COMPONENT("path/", "/comp", "path/comp");
    TEST_APPEND_PATH_COMPONENT("path/path2/", "/comp/comp2", "path/path2/comp/comp2");

    /*Testing av_strnstr()*/
    #घोषणा TEST_STRNSTR(haystack, needle, hay_लंबाई, expected) \
        ptr = av_strnstr(haystack, needle, hay_लंबाई); \
        अगर (ptr != expected){ \
            म_लिखो("expected: %p, received %p\n", expected, ptr); \
        }
    TEST_STRNSTR(haystack, needle [0], म_माप(haystack), haystack+44);
    TEST_STRNSTR(haystack, needle [1], म_माप(haystack), haystack+42);
    TEST_STRNSTR(haystack, needle [2], म_माप(haystack), शून्य       );
    TEST_STRNSTR(haystack, strings[1], म_माप(haystack), haystack   );

    /*Testing av_strireplace()*/
    #घोषणा TEST_STRIREPLACE(haystack, needle, expected) \
        ptr = av_strireplace(haystack, needle, "instead"); \
        अगर (ptr == शून्य) { \
            म_लिखो("error, received null pointer!\n"); \
        } अन्यथा { \
            अगर (म_भेद(ptr, expected) != 0) \
                म_लिखो( "expected: %s, received: %s\n", expected, ptr); \
            av_free(ptr); \
        }

    TEST_STRIREPLACE(haystack, needle [0], "Education consists mainly in what we have uninstead");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");
    TEST_STRIREPLACE(haystack, needle [2], "Education consists mainly in what we have instead.");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");

    वापस 0;
}
