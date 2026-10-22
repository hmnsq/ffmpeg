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

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/common.h"
#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/avstring.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    పూర్ణాంకం i;
    అక్షరం *fullpath, *ptr;
    స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి అక్షరశ్రేణులు[] = {
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
    స్థిరరాశి అక్షరం *haystack = "Education consists mainly in what we have unlearned.";
    స్థిరరాశి అక్షరం * స్థిరరాశి needle[] = {"learned.", "unlearned.", "Unlearned"};

    రాయి("Testing av_get_token()\n");
    కొరకు (i = 0; i < FF_ARRAY_ELEMS(అక్షరశ్రేణులు); i++) {
        స్థిరరాశి అక్షరం *p = అక్షరశ్రేణులు[i];
        అక్షరం *q;
        రాయి("|%s|", p);
        q = av_get_token(&p, ":");
        రాయి(" -> |%s|", q);
        రాయి(" + |%s|\n", p);
        av_free(q);
    }

    రాయి("Testing av_append_path_component()\n");
    #నిర్వచించు TEST_APPEND_మార్గం_COMPONENT(మార్గం, component, expected) \
        fullpath = av_append_మార్గం_component((మార్గం), (component)); \
        రాయి("%s = %s\n", fullpath ? fullpath : "(null)", expected); \
        av_free(fullpath);
    TEST_APPEND_మార్గం_COMPONENT(ఖాళీ, ఖాళీ, "(null)")
    TEST_APPEND_మార్గం_COMPONENT("path", ఖాళీ, "path");
    TEST_APPEND_మార్గం_COMPONENT(ఖాళీ, "comp", "comp");
    TEST_APPEND_మార్గం_COMPONENT("path", "comp", "path/comp");
    TEST_APPEND_మార్గం_COMPONENT("path/", "comp", "path/comp");
    TEST_APPEND_మార్గం_COMPONENT("path", "/comp", "path/comp");
    TEST_APPEND_మార్గం_COMPONENT("path/", "/comp", "path/comp");
    TEST_APPEND_మార్గం_COMPONENT("path/path2/", "/comp/comp2", "path/path2/comp/comp2");

    /*Testing av_strnstr()*/
    #నిర్వచించు TEST_STRNSTR(haystack, needle, hay_నిడివి, expected) \
        ptr = av_strnstr(haystack, needle, hay_నిడివి); \
        ఒకవేళ (ptr != expected){ \
            రాయి("expected: %p, received %p\n", expected, ptr); \
        }
    TEST_STRNSTR(haystack, needle [0], అక్షరశ్రేణి_పొడవు(haystack), haystack+44);
    TEST_STRNSTR(haystack, needle [1], అక్షరశ్రేణి_పొడవు(haystack), haystack+42);
    TEST_STRNSTR(haystack, needle [2], అక్షరశ్రేణి_పొడవు(haystack), ఖాళీ       );
    TEST_STRNSTR(haystack, అక్షరశ్రేణులు[1], అక్షరశ్రేణి_పొడవు(haystack), haystack   );

    /*Testing av_strireplace()*/
    #నిర్వచించు TEST_STRIREPLACE(haystack, needle, expected) \
        ptr = av_strireplace(haystack, needle, "instead"); \
        ఒకవేళ (ptr == ఖాళీ) { \
            రాయి("error, received null pointer!\n"); \
        } లేకపోతే { \
            ఒకవేళ (strcmp(ptr, expected) != 0) \
                రాయి( "expected: %s, received: %s\n", expected, ptr); \
            av_free(ptr); \
        }

    TEST_STRIREPLACE(haystack, needle [0], "Education consists mainly in what we have uninstead");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");
    TEST_STRIREPLACE(haystack, needle [2], "Education consists mainly in what we have instead.");
    TEST_STRIREPLACE(haystack, needle [1], "Education consists mainly in what we have instead");

    తిరిగి 0;
}
