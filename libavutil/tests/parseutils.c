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

#घोषणा TEST
#समावेश "libavutil/parseutils.c"

#समावेश <stdint.h>
#समावेश <stdio.h>

#समावेश "libavutil/common.h"
#समावेश "libavutil/log.h"
#समावेश "libavutil/rational.h"

अटल uint32_t randomv = MKTAG('L','A','V','U');

अटल uint32_t av_get_random_seed_deterministic(व्योम)
{
    वापस randomv = randomv * 1664525 + 1013904223;
}

अटल व्योम test_av_parse_video_rate(व्योम)
{
    पूर्णांक i;
    अटल स्थिर अक्षर *स्थिर rates[] = {
        "-inf",
        "inf",
        "nan",
        "123/0",
        "-123 / 0",
        "",
        "/",
        " 123  /  321",
        "foo/foo",
        "foo/1",
        "1/foo",
        "0/0",
        "/0",
        "1/",
        "1",
        "0",
        "-123/123",
        "-foo",
        "123.23",
        ".23",
        "-.23",
        "-0.234",
        "-0.0000001",
        "  21332.2324   ",
        " -21332.2324   ",
    };

    क्रम (i = 0; i < FF_ARRAY_ELEMS(rates); i++) {
        पूर्णांक ret;
        AVRational q = { 0, 0 };
        ret = av_parse_video_rate(&q, rates[i]);
        म_लिखो("'%s' -> %d/%d %s\n",
               rates[i], q.अंक, q.den, ret ? "ERROR" : "OK");
    }
}

अटल व्योम test_av_parse_color(व्योम)
{
    पूर्णांक i;
    uint8_t rgba[4];
    अटल स्थिर अक्षर *स्थिर color_names[] = {
        "bikeshed",
        "RaNdOm",
        "foo",
        "red",
        "Red ",
        "RED",
        "Violet",
        "Yellow",
        "Red",
        "0x000000",
        "0x0000000",
        "0xff000000",
        "0x3e34ff",
        "0x3e34ffaa",
        "0xffXXee",
        "0xfoobar",
        "0xffffeeeeeeee",
        "#ff0000",
        "#ffXX00",
        "ff0000",
        "ffXX00",
        "red@foo",
        "random@10",
        "0xff0000@1.0",
        "red@",
        "red@0xfff",
        "red@0xf",
        "red@2",
        "red@0.1",
        "red@-1",
        "red@0.5",
        "red@1.0",
        "red@256",
        "red@10foo",
        "red@-1.0",
        "red@-0.0",
    };

    av_log_set_level(AV_LOG_DEBUG);

    क्रम (i = 0;  i < FF_ARRAY_ELEMS(color_names); i++) {
        अगर (av_parse_color(rgba, color_names[i], -1, शून्य) >= 0)
            म_लिखो("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                   color_names[i], rgba[0], rgba[1], rgba[2], rgba[3]);
        अन्यथा
            म_लिखो("%s -> error\n", color_names[i]);
    }
}

अटल व्योम test_av_small_strptime(व्योम)
{
    पूर्णांक i;
    काष्ठा पंचांग पंचांग = { 0 };
    काष्ठा fmt_timespec_entry {
        स्थिर अक्षर *fmt, *timespec;
    } fmt_timespec_entries[] = {
        { "%Y-%m-%d",                    "2012-12-21" },
        { "%Y - %m - %d",                "2012-12-21" },
        { "%Y-%m-%d %H:%M:%S",           "2012-12-21 20:12:21" },
        { "  %Y - %m - %d %H : %M : %S", "   2012 - 12 -  21   20 : 12 : 21" },
        { "  %Y - %b - %d %H : %M : %S", "   2012 - nOV -  21   20 : 12 : 21" },
        { "  %Y - %B - %d %H : %M : %S", "   2012 - nOVemBeR -  21   20 : 12 : 21" },
        { "  %Y - %B%d %H : %M : %S", "   2012 - may21   20 : 12 : 21" },
        { "  %Y - %B%d %H : %M : %S", "   2012 - mby21   20 : 12 : 21" },
        { "  %Y - %B - %d %H : %M : %S", "   2012 - JunE -  21   20 : 12 : 21" },
        { "  %Y - %B - %d %H : %M : %S", "   2012 - Jane -  21   20 : 12 : 21" },
        { "  %Y - %B - %d %H : %M : %S", "   2012 - January -  21   20 : 12 : 21" },
    };

    av_log_set_level(AV_LOG_DEBUG);
    क्रम (i = 0;  i < FF_ARRAY_ELEMS(fmt_timespec_entries); i++) {
        अक्षर *p;
        काष्ठा fmt_timespec_entry *e = &fmt_timespec_entries[i];
        म_लिखो("fmt:'%s' spec:'%s' -> ", e->fmt, e->timespec);
        p = av_small_strptime(e->timespec, e->fmt, &पंचांग);
        अगर (p) {
            म_लिखो("%04d-%02d-%2d %02d:%02d:%02d\n",
                   1900+पंचांग.tm_year, पंचांग.tm_mon+1, पंचांग.tm_mday,
                   पंचांग.tm_hour, पंचांग.tm_min, पंचांग.tm_sec);
        } अन्यथा {
            म_लिखो("error\n");
        }
    }
}

अटल व्योम test_av_parse_time(व्योम)
{
    पूर्णांक i;
    int64_t tv;
    समय_प्रकार tvi;
    काष्ठा पंचांग *पंचांग;
    अटल अक्षर tzstr[] = "TZ=CET-1";
    अटल स्थिर अक्षर * स्थिर time_string[] = {
        "now",
        "12:35:46",
        "2000-12-20 0:02:47.5z",
        "2012 - 02-22  17:44:07",
        "2000-12-20T010247.6",
        "2000-12-12 1:35:46+05:30",
        "2002-12-12 22:30:40-02",
    };
    अटल स्थिर अक्षर * स्थिर duration_string[] = {
        "2:34:56.79",
        "-1:23:45.67",
        "42.1729",
        "-1729.42",
        "12:34",
        "2147483648s",
        "4294967296ms",
        "8589934592us",
        "9223372036854775808us",
    };

    av_log_set_level(AV_LOG_DEBUG);
    putenv(tzstr);
    म_लिखो("(now is 2012-03-17 09:14:13.2 +0100, local time is UTC+1)\n");
    क्रम (i = 0;  i < FF_ARRAY_ELEMS(time_string); i++) {
        म_लिखो("%-24s -> ", time_string[i]);
        अगर (av_parse_time(&tv, time_string[i], 0)) {
            म_लिखो("error\n");
        } अन्यथा {
            tvi = tv / 1000000;
            पंचांग = स_जमट(&tvi);
            म_लिखो("%14"PRIi64".%06d = %04d-%02d-%02dT%02d:%02d:%02dZ\n",
                   tv / 1000000, (पूर्णांक)(tv % 1000000),
                   पंचांग->tm_year + 1900, पंचांग->tm_mon + 1, पंचांग->tm_mday,
                   पंचांग->tm_hour, पंचांग->tm_min, पंचांग->tm_sec);
        }
    }
    क्रम (i = 0;  i < FF_ARRAY_ELEMS(duration_string); i++) {
        म_लिखो("%-24s -> ", duration_string[i]);
        अगर (av_parse_time(&tv, duration_string[i], 1)) {
            म_लिखो("error\n");
        } अन्यथा {
            म_लिखो("%+21"PRIi64"\n", tv);
        }
    }
}

अटल व्योम test_av_get_known_color_name(व्योम)
{
    पूर्णांक i;
    स्थिर uint8_t *rgba;
    स्थिर अक्षर *color;

    क्रम (i = 0; i < FF_ARRAY_ELEMS(color_table); ++i) {
        color = av_get_known_color_name(i, &rgba);
        अगर (color)
            म_लिखो("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                    color, rgba[0], rgba[1], rgba[2], rgba[3]);
        अन्यथा
            म_लिखो("Color ID: %d not found\n", i);
    }
}

अटल व्योम test_av_find_info_tag(व्योम)
{
    अटल स्थिर अक्षर args[] = "?tag1=val1&tag2=val2&tag3=val3&tag41=value 41&tag42=random1";
    अटल स्थिर अक्षर *tags[] = {"tag1", "tag2", "tag3", "tag4", "tag41", "41", "random1"};
    अक्षर buff[16];
    पूर्णांक i;

    क्रम (i = 0; i < FF_ARRAY_ELEMS(tags); ++i) {
        अगर (av_find_info_tag(buff, माप(buff), tags[i], args))
            म_लिखो("%d. %s found: %s\n", i, tags[i], buff);
        अन्यथा
            म_लिखो("%d. %s not found\n", i, tags[i]);
    }
}

पूर्णांक मुख्य(व्योम)
{
    म_लिखो("Testing av_parse_video_rate()\n");
    test_av_parse_video_rate();

    म_लिखो("\nTesting av_parse_color()\n");
    test_av_parse_color();

    म_लिखो("\nTesting av_small_strptime()\n");
    test_av_small_strptime();

    म_लिखो("\nTesting av_parse_time()\n");
    test_av_parse_time();

    म_लिखो("\nTesting av_get_known_color_name()\n");
    test_av_get_known_color_name();

    म_लिखो("\nTesting av_find_info_tag()\n");
    test_av_find_info_tag();
    वापस 0;
}
