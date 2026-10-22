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

#నిర్వచించు TEST
#అన్తర్భావ "libavutil/parseutils.c"

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/common.h"
#అన్తర్భావ "libavutil/log.h"
#అన్తర్భావ "libavutil/rational.h"

స్థిర uint32_t randomv = MKTAG('L','A','V','U');

స్థిర uint32_t av_get_random_విత్తనం_deterministic(శూన్య)
{
    తిరిగి randomv = randomv * 1664525 + 1013904223;
}

స్థిర శూన్య test_av_parse_video_రేటు(శూన్య)
{
    పూర్ణాంకం i;
    స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి rates[] = {
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

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(rates); i++) {
        పూర్ణాంకం ret;
        AVRational q = { 0, 0 };
        ret = av_parse_video_రేటు(&q, rates[i]);
        రాయి("'%s' -> %d/%d %s\n",
               rates[i], q.అంకె, q.den, ret ? "ERROR" : "OK");
    }
}

స్థిర శూన్య test_av_parse_color(శూన్య)
{
    పూర్ణాంకం i;
    uint8_t rgba[4];
    స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి color_పేర్లు[] = {
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

    av_log_సమితి_level(AV_LOG_DEBUG);

    కొరకు (i = 0;  i < FF_ARRAY_ELEMS(color_పేర్లు); i++) {
        ఒకవేళ (av_parse_color(rgba, color_పేర్లు[i], -1, ఖాళీ) >= 0)
            రాయి("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                   color_పేర్లు[i], rgba[0], rgba[1], rgba[2], rgba[3]);
        లేకపోతే
            రాయి("%s -> error\n", color_పేర్లు[i]);
    }
}

స్థిర శూన్య test_av_small_strptime(శూన్య)
{
    పూర్ణాంకం i;
    నిర్మాణం tm tm = { 0 };
    నిర్మాణం fmt_timespec_నమోదు {
        స్థిరరాశి అక్షరం *fmt, *timespec;
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

    av_log_సమితి_level(AV_LOG_DEBUG);
    కొరకు (i = 0;  i < FF_ARRAY_ELEMS(fmt_timespec_entries); i++) {
        అక్షరం *p;
        నిర్మాణం fmt_timespec_నమోదు *e = &fmt_timespec_entries[i];
        రాయి("fmt:'%s' spec:'%s' -> ", e->fmt, e->timespec);
        p = av_small_strptime(e->timespec, e->fmt, &tm);
        ఒకవేళ (p) {
            రాయి("%04d-%02d-%2d %02d:%02d:%02d\n",
                   1900+tm.tm_year, tm.tm_mon+1, tm.tm_mday,
                   tm.tm_hour, tm.tm_min, tm.tm_sec);
        } లేకపోతే {
            రాయి("error\n");
        }
    }
}

స్థిర శూన్య test_av_parse_సమయం(శూన్య)
{
    పూర్ణాంకం i;
    int64_t tv;
    time_t tvi;
    నిర్మాణం tm *tm;
    స్థిర అక్షరం tzstr[] = "TZ=CET-1";
    స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి సమయం_string[] = {
        "now",
        "12:35:46",
        "2000-12-20 0:02:47.5z",
        "2012 - 02-22  17:44:07",
        "2000-12-20T010247.6",
        "2000-12-12 1:35:46+05:30",
        "2002-12-12 22:30:40-02",
    };
    స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి duration_string[] = {
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

    av_log_సమితి_level(AV_LOG_DEBUG);
    putenv(tzstr);
    రాయి("(now is 2012-03-17 09:14:13.2 +0100, local time is UTC+1)\n");
    కొరకు (i = 0;  i < FF_ARRAY_ELEMS(సమయం_string); i++) {
        రాయి("%-24s -> ", సమయం_string[i]);
        ఒకవేళ (av_parse_సమయం(&tv, సమయం_string[i], 0)) {
            రాయి("error\n");
        } లేకపోతే {
            tvi = tv / 1000000;
            tm = gmtime(&tvi);
            రాయి("%14"PRIi64".%06d = %04d-%02d-%02dT%02d:%02d:%02dZ\n",
                   tv / 1000000, (పూర్ణాంకం)(tv % 1000000),
                   tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                   tm->tm_hour, tm->tm_min, tm->tm_sec);
        }
    }
    కొరకు (i = 0;  i < FF_ARRAY_ELEMS(duration_string); i++) {
        రాయి("%-24s -> ", duration_string[i]);
        ఒకవేళ (av_parse_సమయం(&tv, duration_string[i], 1)) {
            రాయి("error\n");
        } లేకపోతే {
            రాయి("%+21"PRIi64"\n", tv);
        }
    }
}

స్థిర శూన్య test_av_get_తెలిసిన_color_name(శూన్య)
{
    పూర్ణాంకం i;
    స్థిరరాశి uint8_t *rgba;
    స్థిరరాశి అక్షరం *color;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(color_పట్టిక); ++i) {
        color = av_get_తెలిసిన_color_name(i, &rgba);
        ఒకవేళ (color)
            రాయి("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                    color, rgba[0], rgba[1], rgba[2], rgba[3]);
        లేకపోతే
            రాయి("Color ID: %d not found\n", i);
    }
}

స్థిర శూన్య test_av_కనుగొను_info_ట్యాగ్(శూన్య)
{
    స్థిర స్థిరరాశి అక్షరం వాదనలు[] = "?tag1=val1&tag2=val2&tag3=val3&tag41=value 41&tag42=random1";
    స్థిర స్థిరరాశి అక్షరం *ట్యాగులు[] = {"tag1", "tag2", "tag3", "tag4", "tag41", "41", "random1"};
    అక్షరం buff[16];
    పూర్ణాంకం i;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(ట్యాగులు); ++i) {
        ఒకవేళ (av_కనుగొను_info_ట్యాగ్(buff, పరిమాణం(buff), ట్యాగులు[i], వాదనలు))
            రాయి("%d. %s found: %s\n", i, ట్యాగులు[i], buff);
        లేకపోతే
            రాయి("%d. %s not found\n", i, ట్యాగులు[i]);
    }
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    రాయి("Testing av_parse_video_rate()\n");
    test_av_parse_video_రేటు();

    రాయి("\nTesting av_parse_color()\n");
    test_av_parse_color();

    రాయి("\nTesting av_small_strptime()\n");
    test_av_small_strptime();

    రాయి("\nTesting av_parse_time()\n");
    test_av_parse_సమయం();

    రాయి("\nTesting av_get_known_color_name()\n");
    test_av_get_తెలిసిన_color_name();

    రాయి("\nTesting av_find_info_tag()\n");
    test_av_కనుగొను_info_ట్యాగ్();
    తిరిగి 0;
}
