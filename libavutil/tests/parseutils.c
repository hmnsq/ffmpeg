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

#تعریف_کرو TEST
#ضمن "libavutil/parseutils.c"

#ضمن <stdint.h>
#ضمن <stdio.h>

#ضمن "libavutil/common.h"
#ضمن "libavutil/log.h"
#ضمن "libavutil/rational.h"

ساكن uint32_t randomv = MKTAG('L','A','V','U');

ساكن uint32_t av_get_random_بیج_deterministic(فراغ)
{
    أرجع randomv = randomv * 1664525 + 1013904223;
}

ساكن فراغ test_av_parse_video_شرح(فراغ)
{
    صحيح i;
    ساكن ثابت حرف *ثابت rates[] = {
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

    لكل (i = 0; i < FF_ARRAY_ELEMS(rates); i++) {
        صحيح ret;
        AVRational q = { 0, 0 };
        ret = av_parse_video_شرح(&q, rates[i]);
        لکھو("'%s' -> %d/%d %s\n",
               rates[i], q.عدد, q.den, ret ? "ERROR" : "OK");
    }
}

ساكن فراغ test_av_parse_color(فراغ)
{
    صحيح i;
    uint8_t rgba[4];
    ساكن ثابت حرف *ثابت color_ناں[] = {
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

    av_log_سیٹ_level(AV_LOG_DEBUG);

    لكل (i = 0;  i < FF_ARRAY_ELEMS(color_ناں); i++) {
        إذا (av_parse_color(rgba, color_ناں[i], -1, عدم) >= 0)
            لکھو("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                   color_ناں[i], rgba[0], rgba[1], rgba[2], rgba[3]);
        وإلا
            لکھو("%s -> error\n", color_ناں[i]);
    }
}

ساكن فراغ test_av_small_strptime(فراغ)
{
    صحيح i;
    بنية tm tm = { 0 };
    بنية fmt_timespec_اندراج {
        ثابت حرف *fmt, *timespec;
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

    av_log_سیٹ_level(AV_LOG_DEBUG);
    لكل (i = 0;  i < FF_ARRAY_ELEMS(fmt_timespec_entries); i++) {
        حرف *p;
        بنية fmt_timespec_اندراج *e = &fmt_timespec_entries[i];
        لکھو("fmt:'%s' spec:'%s' -> ", e->fmt, e->timespec);
        p = av_small_strptime(e->timespec, e->fmt, &tm);
        إذا (p) {
            لکھو("%04d-%02d-%2d %02d:%02d:%02d\n",
                   1900+tm.tm_year, tm.tm_mon+1, tm.tm_mday,
                   tm.tm_hour, tm.tm_min, tm.tm_sec);
        } وإلا {
            لکھو("error\n");
        }
    }
}

ساكن فراغ test_av_parse_ویلا(فراغ)
{
    صحيح i;
    int64_t tv;
    time_t tvi;
    بنية tm *tm;
    ساكن حرف tzstr[] = "TZ=CET-1";
    ساكن ثابت حرف * ثابت ویلا_string[] = {
        "now",
        "12:35:46",
        "2000-12-20 0:02:47.5z",
        "2012 - 02-22  17:44:07",
        "2000-12-20T010247.6",
        "2000-12-12 1:35:46+05:30",
        "2002-12-12 22:30:40-02",
    };
    ساكن ثابت حرف * ثابت duration_string[] = {
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

    av_log_سیٹ_level(AV_LOG_DEBUG);
    putenv(tzstr);
    لکھو("(now is 2012-03-17 09:14:13.2 +0100, local time is UTC+1)\n");
    لكل (i = 0;  i < FF_ARRAY_ELEMS(ویلا_string); i++) {
        لکھو("%-24s -> ", ویلا_string[i]);
        إذا (av_parse_ویلا(&tv, ویلا_string[i], 0)) {
            لکھو("error\n");
        } وإلا {
            tvi = tv / 1000000;
            tm = gmtime(&tvi);
            لکھو("%14"PRIi64".%06d = %04d-%02d-%02dT%02d:%02d:%02dZ\n",
                   tv / 1000000, (صحيح)(tv % 1000000),
                   tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                   tm->tm_hour, tm->tm_min, tm->tm_sec);
        }
    }
    لكل (i = 0;  i < FF_ARRAY_ELEMS(duration_string); i++) {
        لکھو("%-24s -> ", duration_string[i]);
        إذا (av_parse_ویلا(&tv, duration_string[i], 1)) {
            لکھو("error\n");
        } وإلا {
            لکھو("%+21"PRIi64"\n", tv);
        }
    }
}

ساكن فراغ test_av_get_معلوم_color_name(فراغ)
{
    صحيح i;
    ثابت uint8_t *rgba;
    ثابت حرف *color;

    لكل (i = 0; i < FF_ARRAY_ELEMS(color_جدول); ++i) {
        color = av_get_معلوم_color_name(i, &rgba);
        إذا (color)
            لکھو("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                    color, rgba[0], rgba[1], rgba[2], rgba[3]);
        وإلا
            لکھو("Color ID: %d not found\n", i);
    }
}

ساكن فراغ test_av_لبھو_info_ٹیگ(فراغ)
{
    ساكن ثابت حرف دلیلاں[] = "?tag1=val1&tag2=val2&tag3=val3&tag41=value 41&tag42=random1";
    ساكن ثابت حرف *ٹیگ_سوچی[] = {"tag1", "tag2", "tag3", "tag4", "tag41", "41", "random1"};
    حرف buff[16];
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(ٹیگ_سوچی); ++i) {
        إذا (av_لبھو_info_ٹیگ(buff, حجم(buff), ٹیگ_سوچی[i], دلیلاں))
            لکھو("%d. %s found: %s\n", i, ٹیگ_سوچی[i], buff);
        وإلا
            لکھو("%d. %s not found\n", i, ٹیگ_سوچی[i]);
    }
}

صحيح مکھ(فراغ)
{
    لکھو("Testing av_parse_video_rate()\n");
    test_av_parse_video_شرح();

    لکھو("\nTesting av_parse_color()\n");
    test_av_parse_color();

    لکھو("\nTesting av_small_strptime()\n");
    test_av_small_strptime();

    لکھو("\nTesting av_parse_time()\n");
    test_av_parse_ویلا();

    لکھو("\nTesting av_get_known_color_name()\n");
    test_av_get_معلوم_color_name();

    لکھو("\nTesting av_find_info_tag()\n");
    test_av_لبھو_info_ٹیگ();
    أرجع 0;
}
