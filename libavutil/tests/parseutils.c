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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST
#ಅನ್ತರ್ಭಾವ "libavutil/parseutils.c"

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/common.h"
#ಅನ್ತರ್ಭಾವ "libavutil/log.h"
#ಅನ್ತರ್ಭಾವ "libavutil/rational.h"

ಸ್ಥಿರ uint32_t randomv = MKTAG('L','A','V','U');

ಸ್ಥಿರ uint32_t av_get_random_ಬೀಜ_deterministic(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ randomv = randomv * 1664525 + 1013904223;
}

ಸ್ಥಿರ ಶೂನ್ಯ test_av_parse_video_ದರ(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ i;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ rates[] = {
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

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(rates); i++) {
        ಪೂರ್ಣಾಂಕ ret;
        AVRational q = { 0, 0 };
        ret = av_parse_video_ದರ(&q, rates[i]);
        ಬರೆ("'%s' -> %d/%d %s\n",
               rates[i], q.ಅಂಕೆ, q.den, ret ? "ERROR" : "OK");
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ test_av_parse_color(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ i;
    uint8_t rgba[4];
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ color_ಹೆಸರುಗಳು[] = {
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

    av_log_ಗಣ_level(AV_LOG_DEBUG);

    ಗಾಗಿ (i = 0;  i < FF_ARRAY_ELEMS(color_ಹೆಸರುಗಳು); i++) {
        ಆದರೆ (av_parse_color(rgba, color_ಹೆಸರುಗಳು[i], -1, ಖಾಲಿ) >= 0)
            ಬರೆ("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                   color_ಹೆಸರುಗಳು[i], rgba[0], rgba[1], rgba[2], rgba[3]);
        ಇಲ್ಲದಿದ್ದರೆ
            ಬರೆ("%s -> error\n", color_ಹೆಸರುಗಳು[i]);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ test_av_small_strptime(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ i;
    ರಚನೆ tm tm = { 0 };
    ರಚನೆ fmt_timespec_ನಮೂದು {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, *timespec;
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

    av_log_ಗಣ_level(AV_LOG_DEBUG);
    ಗಾಗಿ (i = 0;  i < FF_ARRAY_ELEMS(fmt_timespec_entries); i++) {
        ಅಕ್ಷರ *p;
        ರಚನೆ fmt_timespec_ನಮೂದು *e = &fmt_timespec_entries[i];
        ಬರೆ("fmt:'%s' spec:'%s' -> ", e->fmt, e->timespec);
        p = av_small_strptime(e->timespec, e->fmt, &tm);
        ಆದರೆ (p) {
            ಬರೆ("%04d-%02d-%2d %02d:%02d:%02d\n",
                   1900+tm.tm_year, tm.tm_mon+1, tm.tm_mday,
                   tm.tm_hour, tm.tm_min, tm.tm_sec);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬರೆ("error\n");
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ test_av_parse_ಸಮಯ(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ i;
    int64_t tv;
    time_t tvi;
    ರಚನೆ tm *tm;
    ಸ್ಥಿರ ಅಕ್ಷರ tzstr[] = "TZ=CET-1";
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ ಸಮಯ_string[] = {
        "now",
        "12:35:46",
        "2000-12-20 0:02:47.5z",
        "2012 - 02-22  17:44:07",
        "2000-12-20T010247.6",
        "2000-12-12 1:35:46+05:30",
        "2002-12-12 22:30:40-02",
    };
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ duration_string[] = {
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

    av_log_ಗಣ_level(AV_LOG_DEBUG);
    putenv(tzstr);
    ಬರೆ("(now is 2012-03-17 09:14:13.2 +0100, local time is UTC+1)\n");
    ಗಾಗಿ (i = 0;  i < FF_ARRAY_ELEMS(ಸಮಯ_string); i++) {
        ಬರೆ("%-24s -> ", ಸಮಯ_string[i]);
        ಆದರೆ (av_parse_ಸಮಯ(&tv, ಸಮಯ_string[i], 0)) {
            ಬರೆ("error\n");
        } ಇಲ್ಲದಿದ್ದರೆ {
            tvi = tv / 1000000;
            tm = gmtime(&tvi);
            ಬರೆ("%14"PRIi64".%06d = %04d-%02d-%02dT%02d:%02d:%02dZ\n",
                   tv / 1000000, (ಪೂರ್ಣಾಂಕ)(tv % 1000000),
                   tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                   tm->tm_hour, tm->tm_min, tm->tm_sec);
        }
    }
    ಗಾಗಿ (i = 0;  i < FF_ARRAY_ELEMS(duration_string); i++) {
        ಬರೆ("%-24s -> ", duration_string[i]);
        ಆದರೆ (av_parse_ಸಮಯ(&tv, duration_string[i], 1)) {
            ಬರೆ("error\n");
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬರೆ("%+21"PRIi64"\n", tv);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ test_av_get_ತಿಳಿದ_color_name(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ i;
    ಸ್ಥಿರಾಂಕ uint8_t *rgba;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *color;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(color_ಕೋಷ್ಟಕ); ++i) {
        color = av_get_ತಿಳಿದ_color_name(i, &rgba);
        ಆದರೆ (color)
            ಬರೆ("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                    color, rgba[0], rgba[1], rgba[2], rgba[3]);
        ಇಲ್ಲದಿದ್ದರೆ
            ಬರೆ("Color ID: %d not found\n", i);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ test_av_ಕಂಡುಹಿಡಿ_info_ಟ್ಯಾಗ್(ಶೂನ್ಯ)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ವಾದಗಳು[] = "?tag1=val1&tag2=val2&tag3=val3&tag41=value 41&tag42=random1";
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಟ್ಯಾಗುಗಳು[] = {"tag1", "tag2", "tag3", "tag4", "tag41", "41", "random1"};
    ಅಕ್ಷರ buff[16];
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(ಟ್ಯಾಗುಗಳು); ++i) {
        ಆದರೆ (av_ಕಂಡುಹಿಡಿ_info_ಟ್ಯಾಗ್(buff, ಗಾತ್ರ(buff), ಟ್ಯಾಗುಗಳು[i], ವಾದಗಳು))
            ಬರೆ("%d. %s found: %s\n", i, ಟ್ಯಾಗುಗಳು[i], buff);
        ಇಲ್ಲದಿದ್ದರೆ
            ಬರೆ("%d. %s not found\n", i, ಟ್ಯಾಗುಗಳು[i]);
    }
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಬರೆ("Testing av_parse_video_rate()\n");
    test_av_parse_video_ದರ();

    ಬರೆ("\nTesting av_parse_color()\n");
    test_av_parse_color();

    ಬರೆ("\nTesting av_small_strptime()\n");
    test_av_small_strptime();

    ಬರೆ("\nTesting av_parse_time()\n");
    test_av_parse_ಸಮಯ();

    ಬರೆ("\nTesting av_get_known_color_name()\n");
    test_av_get_ತಿಳಿದ_color_name();

    ಬರೆ("\nTesting av_find_info_tag()\n");
    test_av_ಕಂಡುಹಿಡಿ_info_ಟ್ಯಾಗ್();
    ಹಿಂತಿರುಗಿ 0;
}
