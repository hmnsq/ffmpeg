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
#અન્તર્ભાવ "libavutil/parseutils.c"

#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <stdio.h>

#અન્તર્ભાવ "libavutil/common.h"
#અન્તર્ભાવ "libavutil/log.h"
#અન્તર્ભાવ "libavutil/rational.h"

સ્થિર uint32_t randomv = MKTAG('L','A','V','U');

સ્થિર uint32_t av_get_random_seed_deterministic(શૂન્ય)
{
    પાછા randomv = randomv * 1664525 + 1013904223;
}

સ્થિર શૂન્ય test_av_parse_video_rate(શૂન્ય)
{
    પૂર્ણાંક i;
    સ્થિર અચલ અક્ષર *અચલ rates[] = {
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

    માટે (i = 0; i < FF_ARRAY_ELEMS(rates); i++) {
        પૂર્ણાંક ret;
        AVRational q = { 0, 0 };
        ret = av_parse_video_rate(&q, rates[i]);
        printf("'%s' -> %d/%d %s\n",
               rates[i], q.અંક, q.den, ret ? "ERROR" : "OK");
    }
}

સ્થિર શૂન્ય test_av_parse_color(શૂન્ય)
{
    પૂર્ણાંક i;
    uint8_t rgba[4];
    સ્થિર અચલ અક્ષર *અચલ color_names[] = {
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

    માટે (i = 0;  i < FF_ARRAY_ELEMS(color_names); i++) {
        જો (av_parse_color(rgba, color_names[i], -1, ખાલી) >= 0)
            printf("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                   color_names[i], rgba[0], rgba[1], rgba[2], rgba[3]);
        નહીંતર
            printf("%s -> error\n", color_names[i]);
    }
}

સ્થિર શૂન્ય test_av_small_strptime(શૂન્ય)
{
    પૂર્ણાંક i;
    સંરચના tm tm = { 0 };
    સંરચના fmt_timespec_entry {
        અચલ અક્ષર *fmt, *timespec;
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
    માટે (i = 0;  i < FF_ARRAY_ELEMS(fmt_timespec_entries); i++) {
        અક્ષર *p;
        સંરચના fmt_timespec_entry *e = &fmt_timespec_entries[i];
        printf("fmt:'%s' spec:'%s' -> ", e->fmt, e->timespec);
        p = av_small_strptime(e->timespec, e->fmt, &tm);
        જો (p) {
            printf("%04d-%02d-%2d %02d:%02d:%02d\n",
                   1900+tm.tm_year, tm.tm_mon+1, tm.tm_mday,
                   tm.tm_hour, tm.tm_min, tm.tm_sec);
        } નહીંતર {
            printf("error\n");
        }
    }
}

સ્થિર શૂન્ય test_av_parse_time(શૂન્ય)
{
    પૂર્ણાંક i;
    int64_t tv;
    time_t tvi;
    સંરચના tm *tm;
    સ્થિર અક્ષર tzstr[] = "TZ=CET-1";
    સ્થિર અચલ અક્ષર * અચલ time_string[] = {
        "now",
        "12:35:46",
        "2000-12-20 0:02:47.5z",
        "2012 - 02-22  17:44:07",
        "2000-12-20T010247.6",
        "2000-12-12 1:35:46+05:30",
        "2002-12-12 22:30:40-02",
    };
    સ્થિર અચલ અક્ષર * અચલ duration_string[] = {
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
    માટે (i = 0;  i < FF_ARRAY_ELEMS(time_string); i++) {
        printf("%-24s -> ", time_string[i]);
        જો (av_parse_time(&tv, time_string[i], 0)) {
            printf("error\n");
        } નહીંતર {
            tvi = tv / 1000000;
            tm = gmtime(&tvi);
            printf("%14"PRIi64".%06d = %04d-%02d-%02dT%02d:%02d:%02dZ\n",
                   tv / 1000000, (પૂર્ણાંક)(tv % 1000000),
                   tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                   tm->tm_hour, tm->tm_min, tm->tm_sec);
        }
    }
    માટે (i = 0;  i < FF_ARRAY_ELEMS(duration_string); i++) {
        printf("%-24s -> ", duration_string[i]);
        જો (av_parse_time(&tv, duration_string[i], 1)) {
            printf("error\n");
        } નહીંતર {
            printf("%+21"PRIi64"\n", tv);
        }
    }
}

સ્થિર શૂન્ય test_av_get_known_color_name(શૂન્ય)
{
    પૂર્ણાંક i;
    અચલ uint8_t *rgba;
    અચલ અક્ષર *color;

    માટે (i = 0; i < FF_ARRAY_ELEMS(color_table); ++i) {
        color = av_get_known_color_name(i, &rgba);
        જો (color)
            printf("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                    color, rgba[0], rgba[1], rgba[2], rgba[3]);
        નહીંતર
            printf("Color ID: %d not found\n", i);
    }
}

સ્થિર શૂન્ય test_av_find_info_tag(શૂન્ય)
{
    સ્થિર અચલ અક્ષર args[] = "?tag1=val1&tag2=val2&tag3=val3&tag41=value 41&tag42=random1";
    સ્થિર અચલ અક્ષર *tags[] = {"tag1", "tag2", "tag3", "tag4", "tag41", "41", "random1"};
    અક્ષર buff[16];
    પૂર્ણાંક i;

    માટે (i = 0; i < FF_ARRAY_ELEMS(tags); ++i) {
        જો (av_find_info_tag(buff, કદ(buff), tags[i], args))
            printf("%d. %s found: %s\n", i, tags[i], buff);
        નહીંતર
            printf("%d. %s not found\n", i, tags[i]);
    }
}

પૂર્ણાંક મુખ્ય(શૂન્ય)
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
    પાછા 0;
}
