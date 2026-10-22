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

#define TEST
#अन्तर्भाव "libavutil/parseutils.c"

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/common.h"
#अन्तर्भाव "libavutil/log.h"
#अन्तर्भाव "libavutil/rational.h"

स्थिर uint32_t randomv = MKTAG('L','A','V','U');

स्थिर uint32_t av_get_random_seed_deterministic(शून्य)
{
    पटिनिवत्त randomv = randomv * 1664525 + 1013904223;
}

स्थिर शून्य test_av_parse_video_rate(शून्य)
{
    पूर्णाङ्क i;
    स्थिर ध्रुव वर्ण *ध्रुव rates[] = {
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

    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(rates); i++) {
        पूर्णाङ्क ret;
        AVRational q = { 0, 0 };
        ret = av_parse_video_rate(&q, rates[i]);
        printf("'%s' -> %d/%d %s\n",
               rates[i], q.अङ्कः, q.den, ret ? "ERROR" : "OK");
    }
}

स्थिर शून्य test_av_parse_color(शून्य)
{
    पूर्णाङ्क i;
    uint8_t rgba[4];
    स्थिर ध्रुव वर्ण *ध्रुव color_names[] = {
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

    अत्थाय (i = 0;  i < FF_ARRAY_ELEMS(color_names); i++) {
        सचे (av_parse_color(rgba, color_names[i], -1, रिक्त) >= 0)
            printf("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                   color_names[i], rgba[0], rgba[1], rgba[2], rgba[3]);
        अञ्ञथा
            printf("%s -> error\n", color_names[i]);
    }
}

स्थिर शून्य test_av_small_strptime(शून्य)
{
    पूर्णाङ्क i;
    संरचना tm tm = { 0 };
    संरचना fmt_timespec_entry {
        ध्रुव वर्ण *fmt, *timespec;
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
    अत्थाय (i = 0;  i < FF_ARRAY_ELEMS(fmt_timespec_entries); i++) {
        वर्ण *p;
        संरचना fmt_timespec_entry *e = &fmt_timespec_entries[i];
        printf("fmt:'%s' spec:'%s' -> ", e->fmt, e->timespec);
        p = av_small_strptime(e->timespec, e->fmt, &tm);
        सचे (p) {
            printf("%04d-%02d-%2d %02d:%02d:%02d\n",
                   1900+tm.tm_year, tm.tm_mon+1, tm.tm_mday,
                   tm.tm_hour, tm.tm_min, tm.tm_sec);
        } अञ्ञथा {
            printf("error\n");
        }
    }
}

स्थिर शून्य test_av_parse_time(शून्य)
{
    पूर्णाङ्क i;
    int64_t tv;
    time_t tvi;
    संरचना tm *tm;
    स्थिर वर्ण tzstr[] = "TZ=CET-1";
    स्थिर ध्रुव वर्ण * ध्रुव time_string[] = {
        "now",
        "12:35:46",
        "2000-12-20 0:02:47.5z",
        "2012 - 02-22  17:44:07",
        "2000-12-20T010247.6",
        "2000-12-12 1:35:46+05:30",
        "2002-12-12 22:30:40-02",
    };
    स्थिर ध्रुव वर्ण * ध्रुव duration_string[] = {
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
    printf("(now is 2012-03-17 09:14:13.2 +0100, local time is UTC+1)\n");
    अत्थाय (i = 0;  i < FF_ARRAY_ELEMS(time_string); i++) {
        printf("%-24s -> ", time_string[i]);
        सचे (av_parse_time(&tv, time_string[i], 0)) {
            printf("error\n");
        } अञ्ञथा {
            tvi = tv / 1000000;
            tm = gmtime(&tvi);
            printf("%14"PRIi64".%06d = %04d-%02d-%02dT%02d:%02d:%02dZ\n",
                   tv / 1000000, (पूर्णाङ्क)(tv % 1000000),
                   tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                   tm->tm_hour, tm->tm_min, tm->tm_sec);
        }
    }
    अत्थाय (i = 0;  i < FF_ARRAY_ELEMS(duration_string); i++) {
        printf("%-24s -> ", duration_string[i]);
        सचे (av_parse_time(&tv, duration_string[i], 1)) {
            printf("error\n");
        } अञ्ञथा {
            printf("%+21"PRIi64"\n", tv);
        }
    }
}

स्थिर शून्य test_av_get_known_color_name(शून्य)
{
    पूर्णाङ्क i;
    ध्रुव uint8_t *rgba;
    ध्रुव वर्ण *color;

    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(color_table); ++i) {
        color = av_get_known_color_name(i, &rgba);
        सचे (color)
            printf("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                    color, rgba[0], rgba[1], rgba[2], rgba[3]);
        अञ्ञथा
            printf("Color ID: %d not found\n", i);
    }
}

स्थिर शून्य test_av_find_info_tag(शून्य)
{
    स्थिर ध्रुव वर्ण args[] = "?tag1=val1&tag2=val2&tag3=val3&tag41=value 41&tag42=random1";
    स्थिर ध्रुव वर्ण *tags[] = {"tag1", "tag2", "tag3", "tag4", "tag41", "41", "random1"};
    वर्ण buff[16];
    पूर्णाङ्क i;

    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(tags); ++i) {
        सचे (av_find_info_tag(buff, परिमाण(buff), tags[i], args))
            printf("%d. %s found: %s\n", i, tags[i], buff);
        अञ्ञथा
            printf("%d. %s not found\n", i, tags[i]);
    }
}

पूर्णाङ्क main(शून्य)
{
    printf("Testing av_parse_video_rate()\n");
    test_av_parse_video_rate();

    printf("\nTesting av_parse_color()\n");
    test_av_parse_color();

    printf("\nTesting av_small_strptime()\n");
    test_av_small_strptime();

    printf("\nTesting av_parse_time()\n");
    test_av_parse_time();

    printf("\nTesting av_get_known_color_name()\n");
    test_av_get_known_color_name();

    printf("\nTesting av_find_info_tag()\n");
    test_av_find_info_tag();
    पटिनिवत्त 0;
}
