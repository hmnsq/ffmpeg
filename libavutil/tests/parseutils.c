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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/parseutils.c"

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/rational.h"

ਸਥਿਰ uint32_t randomv = MKTAG('L','A','V','U');

ਸਥਿਰ uint32_t av_get_random_ਬੀਜ_deterministic(ਖਾਲੀ)
{
    ਵਾਪਸ randomv = randomv * 1664525 + 1013904223;
}

ਸਥਿਰ ਖਾਲੀ test_av_parse_video_ਦਰ(ਖਾਲੀ)
{
    ਪੂਰਨ i;
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ rates[] = {
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

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(rates); i++) {
        ਪੂਰਨ ret;
        AVRational q = { 0, 0 };
        ret = av_parse_video_ਦਰ(&q, rates[i]);
        ਲਿਖੋ("'%s' -> %d/%d %s\n",
               rates[i], q.ਅੰਕ, q.den, ret ? "ERROR" : "OK");
    }
}

ਸਥਿਰ ਖਾਲੀ test_av_parse_color(ਖਾਲੀ)
{
    ਪੂਰਨ i;
    uint8_t rgba[4];
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ color_ਨਾਂ[] = {
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

    av_log_ਸੈੱਟ_level(AV_LOG_DEBUG);

    ਲਈ (i = 0;  i < FF_ARRAY_ELEMS(color_ਨਾਂ); i++) {
        ਜੇ (av_parse_color(rgba, color_ਨਾਂ[i], -1, ਨਿਰਾ) >= 0)
            ਲਿਖੋ("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                   color_ਨਾਂ[i], rgba[0], rgba[1], rgba[2], rgba[3]);
        ਨਹੀਂਤਾਂ
            ਲਿਖੋ("%s -> error\n", color_ਨਾਂ[i]);
    }
}

ਸਥਿਰ ਖਾਲੀ test_av_small_strptime(ਖਾਲੀ)
{
    ਪੂਰਨ i;
    ਬਣਤਰ tm tm = { 0 };
    ਬਣਤਰ fmt_timespec_ਇੰਦਰਾਜ {
        ਅਚਲ ਅੱਖਰ *fmt, *timespec;
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

    av_log_ਸੈੱਟ_level(AV_LOG_DEBUG);
    ਲਈ (i = 0;  i < FF_ARRAY_ELEMS(fmt_timespec_entries); i++) {
        ਅੱਖਰ *p;
        ਬਣਤਰ fmt_timespec_ਇੰਦਰਾਜ *e = &fmt_timespec_entries[i];
        ਲਿਖੋ("fmt:'%s' spec:'%s' -> ", e->fmt, e->timespec);
        p = av_small_strptime(e->timespec, e->fmt, &tm);
        ਜੇ (p) {
            ਲਿਖੋ("%04d-%02d-%2d %02d:%02d:%02d\n",
                   1900+tm.tm_year, tm.tm_mon+1, tm.tm_mday,
                   tm.tm_hour, tm.tm_min, tm.tm_sec);
        } ਨਹੀਂਤਾਂ {
            ਲਿਖੋ("error\n");
        }
    }
}

ਸਥਿਰ ਖਾਲੀ test_av_parse_ਸਮਾਂ(ਖਾਲੀ)
{
    ਪੂਰਨ i;
    int64_t tv;
    time_t tvi;
    ਬਣਤਰ tm *tm;
    ਸਥਿਰ ਅੱਖਰ tzstr[] = "TZ=CET-1";
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ ਸਮਾਂ_string[] = {
        "now",
        "12:35:46",
        "2000-12-20 0:02:47.5z",
        "2012 - 02-22  17:44:07",
        "2000-12-20T010247.6",
        "2000-12-12 1:35:46+05:30",
        "2002-12-12 22:30:40-02",
    };
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ duration_string[] = {
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

    av_log_ਸੈੱਟ_level(AV_LOG_DEBUG);
    putenv(tzstr);
    ਲਿਖੋ("(now is 2012-03-17 09:14:13.2 +0100, local time is UTC+1)\n");
    ਲਈ (i = 0;  i < FF_ARRAY_ELEMS(ਸਮਾਂ_string); i++) {
        ਲਿਖੋ("%-24s -> ", ਸਮਾਂ_string[i]);
        ਜੇ (av_parse_ਸਮਾਂ(&tv, ਸਮਾਂ_string[i], 0)) {
            ਲਿਖੋ("error\n");
        } ਨਹੀਂਤਾਂ {
            tvi = tv / 1000000;
            tm = gmtime(&tvi);
            ਲਿਖੋ("%14"PRIi64".%06d = %04d-%02d-%02dT%02d:%02d:%02dZ\n",
                   tv / 1000000, (ਪੂਰਨ)(tv % 1000000),
                   tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                   tm->tm_hour, tm->tm_min, tm->tm_sec);
        }
    }
    ਲਈ (i = 0;  i < FF_ARRAY_ELEMS(duration_string); i++) {
        ਲਿਖੋ("%-24s -> ", duration_string[i]);
        ਜੇ (av_parse_ਸਮਾਂ(&tv, duration_string[i], 1)) {
            ਲਿਖੋ("error\n");
        } ਨਹੀਂਤਾਂ {
            ਲਿਖੋ("%+21"PRIi64"\n", tv);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ test_av_get_ਗਿਆਤ_color_name(ਖਾਲੀ)
{
    ਪੂਰਨ i;
    ਅਚਲ uint8_t *rgba;
    ਅਚਲ ਅੱਖਰ *color;

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(color_ਸਾਰਣੀ); ++i) {
        color = av_get_ਗਿਆਤ_color_name(i, &rgba);
        ਜੇ (color)
            ਲਿਖੋ("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                    color, rgba[0], rgba[1], rgba[2], rgba[3]);
        ਨਹੀਂਤਾਂ
            ਲਿਖੋ("Color ID: %d not found\n", i);
    }
}

ਸਥਿਰ ਖਾਲੀ test_av_ਲੱਭੋ_info_ਟੈਗ(ਖਾਲੀ)
{
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ ਦਲੀਲਾਂ[] = "?tag1=val1&tag2=val2&tag3=val3&tag41=value 41&tag42=random1";
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਟੈਗ_ਸੂਚੀ[] = {"tag1", "tag2", "tag3", "tag4", "tag41", "41", "random1"};
    ਅੱਖਰ buff[16];
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(ਟੈਗ_ਸੂਚੀ); ++i) {
        ਜੇ (av_ਲੱਭੋ_info_ਟੈਗ(buff, ਆਕਾਰ(buff), ਟੈਗ_ਸੂਚੀ[i], ਦਲੀਲਾਂ))
            ਲਿਖੋ("%d. %s found: %s\n", i, ਟੈਗ_ਸੂਚੀ[i], buff);
        ਨਹੀਂਤਾਂ
            ਲਿਖੋ("%d. %s not found\n", i, ਟੈਗ_ਸੂਚੀ[i]);
    }
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਲਿਖੋ("Testing av_parse_video_rate()\n");
    test_av_parse_video_ਦਰ();

    ਲਿਖੋ("\nTesting av_parse_color()\n");
    test_av_parse_color();

    ਲਿਖੋ("\nTesting av_small_strptime()\n");
    test_av_small_strptime();

    ਲਿਖੋ("\nTesting av_parse_time()\n");
    test_av_parse_ਸਮਾਂ();

    ਲਿਖੋ("\nTesting av_get_known_color_name()\n");
    test_av_get_ਗਿਆਤ_color_name();

    ਲਿਖੋ("\nTesting av_find_info_tag()\n");
    test_av_ਲੱਭੋ_info_ਟੈਗ();
    ਵਾਪਸ 0;
}
