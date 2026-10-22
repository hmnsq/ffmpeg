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
#شامل "libavutil/parseutils.c"

#شامل <stdint.h>
#شامل <stdio.h>

#شامل "libavutil/common.h"
#شامل "libavutil/log.h"
#شامل "libavutil/rational.h"

ساکن uint32_t randomv = MKTAG('L','A','V','U');

ساکن uint32_t av_get_random_بیج_deterministic(خالی)
{
    واپس randomv = randomv * 1664525 + 1013904223;
}

ساکن خالی test_av_parse_video_شرح(خالی)
{
    صحیح i;
    ساکن ثابت حرف *ثابت rates[] = {
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

    برائے (i = 0; i < FF_ARRAY_ELEMS(rates); i++) {
        صحیح ret;
        AVRational q = { 0, 0 };
        ret = av_parse_video_شرح(&q, rates[i]);
        لکھو("'%s' -> %d/%d %s\n",
               rates[i], q.عدد, q.den, ret ? "ERROR" : "OK");
    }
}

ساکن خالی test_av_parse_color(خالی)
{
    صحیح i;
    uint8_t rgba[4];
    ساکن ثابت حرف *ثابت color_نام[] = {
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

    برائے (i = 0;  i < FF_ARRAY_ELEMS(color_نام); i++) {
        اگر (av_parse_color(rgba, color_نام[i], -1, تہی) >= 0)
            لکھو("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                   color_نام[i], rgba[0], rgba[1], rgba[2], rgba[3]);
        ورنہ
            لکھو("%s -> error\n", color_نام[i]);
    }
}

ساکن خالی test_av_small_strptime(خالی)
{
    صحیح i;
    ساخت tm tm = { 0 };
    ساخت fmt_timespec_اندراج {
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
    برائے (i = 0;  i < FF_ARRAY_ELEMS(fmt_timespec_entries); i++) {
        حرف *p;
        ساخت fmt_timespec_اندراج *e = &fmt_timespec_entries[i];
        لکھو("fmt:'%s' spec:'%s' -> ", e->fmt, e->timespec);
        p = av_small_strptime(e->timespec, e->fmt, &tm);
        اگر (p) {
            لکھو("%04d-%02d-%2d %02d:%02d:%02d\n",
                   1900+tm.tm_year, tm.tm_mon+1, tm.tm_mday,
                   tm.tm_hour, tm.tm_min, tm.tm_sec);
        } ورنہ {
            لکھو("error\n");
        }
    }
}

ساکن خالی test_av_parse_وقت(خالی)
{
    صحیح i;
    int64_t tv;
    time_t tvi;
    ساخت tm *tm;
    ساکن حرف tzstr[] = "TZ=CET-1";
    ساکن ثابت حرف * ثابت وقت_string[] = {
        "now",
        "12:35:46",
        "2000-12-20 0:02:47.5z",
        "2012 - 02-22  17:44:07",
        "2000-12-20T010247.6",
        "2000-12-12 1:35:46+05:30",
        "2002-12-12 22:30:40-02",
    };
    ساکن ثابت حرف * ثابت duration_string[] = {
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
    برائے (i = 0;  i < FF_ARRAY_ELEMS(وقت_string); i++) {
        لکھو("%-24s -> ", وقت_string[i]);
        اگر (av_parse_وقت(&tv, وقت_string[i], 0)) {
            لکھو("error\n");
        } ورنہ {
            tvi = tv / 1000000;
            tm = gmtime(&tvi);
            لکھو("%14"PRIi64".%06d = %04d-%02d-%02dT%02d:%02d:%02dZ\n",
                   tv / 1000000, (صحیح)(tv % 1000000),
                   tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                   tm->tm_hour, tm->tm_min, tm->tm_sec);
        }
    }
    برائے (i = 0;  i < FF_ARRAY_ELEMS(duration_string); i++) {
        لکھو("%-24s -> ", duration_string[i]);
        اگر (av_parse_وقت(&tv, duration_string[i], 1)) {
            لکھو("error\n");
        } ورنہ {
            لکھو("%+21"PRIi64"\n", tv);
        }
    }
}

ساکن خالی test_av_get_معلوم_color_name(خالی)
{
    صحیح i;
    ثابت uint8_t *rgba;
    ثابت حرف *color;

    برائے (i = 0; i < FF_ARRAY_ELEMS(color_جدول); ++i) {
        color = av_get_معلوم_color_name(i, &rgba);
        اگر (color)
            لکھو("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                    color, rgba[0], rgba[1], rgba[2], rgba[3]);
        ورنہ
            لکھو("Color ID: %d not found\n", i);
    }
}

ساکن خالی test_av_ڈھونڈو_info_لیبل(خالی)
{
    ساکن ثابت حرف دلائل[] = "?tag1=val1&tag2=val2&tag3=val3&tag41=value 41&tag42=random1";
    ساکن ثابت حرف *لیبل_فہرست[] = {"tag1", "tag2", "tag3", "tag4", "tag41", "41", "random1"};
    حرف buff[16];
    صحیح i;

    برائے (i = 0; i < FF_ARRAY_ELEMS(لیبل_فہرست); ++i) {
        اگر (av_ڈھونڈو_info_لیبل(buff, حجم(buff), لیبل_فہرست[i], دلائل))
            لکھو("%d. %s found: %s\n", i, لیبل_فہرست[i], buff);
        ورنہ
            لکھو("%d. %s not found\n", i, لیبل_فہرست[i]);
    }
}

صحیح مین(خالی)
{
    لکھو("Testing av_parse_video_rate()\n");
    test_av_parse_video_شرح();

    لکھو("\nTesting av_parse_color()\n");
    test_av_parse_color();

    لکھو("\nTesting av_small_strptime()\n");
    test_av_small_strptime();

    لکھو("\nTesting av_parse_time()\n");
    test_av_parse_وقت();

    لکھو("\nTesting av_get_known_color_name()\n");
    test_av_get_معلوم_color_name();

    لکھو("\nTesting av_find_info_tag()\n");
    test_av_ڈھونڈو_info_لیبل();
    واپس 0;
}
