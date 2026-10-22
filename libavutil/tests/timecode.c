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

/**
 * Unit tests for libavutil/timecode.c:
 *   av_timecode_init, av_timecode_init_from_components,
 *   av_timecode_init_from_string, av_timecode_make_string,
 *   av_timecode_get_smpte_from_framenum, av_timecode_get_smpte,
 *   av_timecode_make_smpte_tc_string, av_timecode_make_smpte_tc_string2,
 *   av_timecode_make_mpeg_tc_string, av_timecode_adjust_ntsc_framenum2,
 *   av_timecode_check_frame_rate
 */

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/macros.h"
#అన్తర్భావ "libavutil/rational.h"
#అన్తర్భావ "libavutil/timecode.h"

స్థిర శూన్య test_check_చట్రం_రేటు(శూన్య)
{
    స్థిర స్థిరరాశి AVRational rates[] = {
        {24, 1}, {25, 1}, {30, 1}, {48, 1}, {50, 1}, {60, 1},
        {100, 1}, {120, 1}, {150, 1},
        {30000, 1001}, {15, 1}, {12, 1},
        {0, 0}, {30, 0},
    };
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(rates); i++)
        రాయి("check_frame_rate %d/%d: %d\n",
               rates[i].అంకె, rates[i].den,
               av_timecode_check_చట్రం_రేటు(rates[i]));
}

స్థిర శూన్య test_init(శూన్య)
{
    AVTimecode tc;
    స్థిర స్థిరరాశి నిర్మాణం {
        AVRational రేటు;
        పూర్ణాంకం flags;
        పూర్ణాంకం ప్రారంభం;
    } cases[] = {
        { {25, 1}, 0, 0 },
        { {30, 1}, AV_TIMECODE_FLAG_DROPFRAME, 0 },
        { {24, 1}, 0, 100 },
        { {0, 1}, 0, 0 },
        { {25, 1}, AV_TIMECODE_FLAG_DROPFRAME, 0 },
        { {30000, 1001}, AV_TIMECODE_FLAG_DROPFRAME, 0 },
        { {25, 1}, AV_TIMECODE_FLAG_ALLOWNEGATIVE, -100 },
    };

    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(cases); i++) {
        పూర్ణాంకం ret = av_timecode_init(&tc, cases[i].రేటు, cases[i].flags, cases[i].ప్రారంభం, ఖాళీ);
        రాయి("init %d/%d flags:%d start:%d: ",
               cases[i].రేటు.అంకె, cases[i].రేటు.den, cases[i].flags, cases[i].ప్రారంభం);
        ఒకవేళ (ret < 0) {
            రాయి("error\n");
        } లేకపోతే {
            రాయి("ok fps=%d start=%d rate=%d/%d\n",
                   tc.fps, tc.ప్రారంభం, tc.రేటు.అంకె, tc.రేటు.den);
        }
    }
}

స్థిర శూన్య test_init_from_components(శూన్య)
{
    AVTimecode tc;
    పూర్ణాంకం ret;

    ret = av_timecode_init_from_components(&tc, (AVRational){25, 1},
                                           0, 0, 0, 0, 0, ఖాళీ);
    రాయి("from_components 25/1 00:00:00:00: %d start=%d\n", ret, tc.ప్రారంభం);

    ret = av_timecode_init_from_components(&tc, (AVRational){25, 1},
                                           0, 1, 0, 0, 0, ఖాళీ);
    రాయి("from_components 25/1 01:00:00:00: %d start=%d\n", ret, tc.ప్రారంభం);

    ret = av_timecode_init_from_components(&tc, (AVRational){30, 1},
                                           0, 1, 2, 3, 4, ఖాళీ);
    రాయి("from_components 30/1 01:02:03:04: %d start=%d\n", ret, tc.ప్రారంభం);

    ret = av_timecode_init_from_components(&tc, (AVRational){30000, 1001},
                                           AV_TIMECODE_FLAG_DROPFRAME,
                                           1, 0, 0, 0, ఖాళీ);
    రాయి("from_components 30000/1001 drop 01:00:00;00: %d start=%d\n",
           ret, tc.ప్రారంభం);
}

స్థిర శూన్య test_init_from_string(శూన్య)
{
    AVTimecode tc;
    పూర్ణాంకం ret;

    ret = av_timecode_init_from_string(&tc, (AVRational){30, 1},
                                       "00:01:02:03", ఖాళీ);
    రాయి("from_string 30/1 00:01:02:03: %d drop=%d start=%d\n",
           ret, !!(tc.flags & AV_TIMECODE_FLAG_DROPFRAME), tc.ప్రారంభం);

    ret = av_timecode_init_from_string(&tc, (AVRational){30000, 1001},
                                       "00:01:00;02", ఖాళీ);
    రాయి("from_string 30000/1001 00:01:00;02: %d drop=%d\n",
           ret, !!(tc.flags & AV_TIMECODE_FLAG_DROPFRAME));

    ret = av_timecode_init_from_string(&tc, (AVRational){30000, 1001},
                                       "01:00:00.00", ఖాళీ);
    రాయి("from_string 30000/1001 01:00:00.00: %d drop=%d\n",
           ret, !!(tc.flags & AV_TIMECODE_FLAG_DROPFRAME));

    ret = av_timecode_init_from_string(&tc, (AVRational){25, 1},
                                       "notvalid", ఖాళీ);
    రాయి("from_string 25/1 notvalid: %s\n", ret < 0 ? "error" : "ok");
}

స్థిర శూన్య test_make_string(శూన్య)
{
    AVTimecode tc;
    అక్షరం buf[AV_TIMECODE_STR_కొలత];

    av_timecode_init(&tc, (AVRational){25, 1}, 0, 0, ఖాళీ);
    రాయి("make_string 25/1 35: %s\n", av_timecode_make_string(&tc, buf, 35));
    రాయి("make_string 25/1 0: %s\n", av_timecode_make_string(&tc, buf, 0));

    av_timecode_init(&tc, (AVRational){30, 1}, 0, 0, ఖాళీ);
    రాయి("make_string 30/1 30: %s\n", av_timecode_make_string(&tc, buf, 30));

    av_timecode_init(&tc, (AVRational){25, 1},
                     AV_TIMECODE_FLAG_24HOURSMAX, 0, ఖాళీ);
    రాయి("make_string 25/1 24hwrap %d: %s\n",
           25 * 3600 * 25, av_timecode_make_string(&tc, buf, 25 * 3600 * 25));

    av_timecode_init(&tc, (AVRational){30000, 1001},
                     AV_TIMECODE_FLAG_DROPFRAME, 0, ఖాళీ);
    రాయి("make_string 30000/1001 drop 0: %s\n",
           av_timecode_make_string(&tc, buf, 0));

    av_timecode_init(&tc, (AVRational){25, 1},
                     AV_TIMECODE_FLAG_ALLOWNEGATIVE, -100, ఖాళీ);
    రాయి("make_string 25/1 negative start -100 frame 0: %s\n",
           av_timecode_make_string(&tc, buf, 0));
}

స్థిర శూన్య test_make_smpte_tc_string(శూన్య)
{
    అక్షరం buf[AV_TIMECODE_STR_కొలత];
    AVTimecode tc;
    uint32_t smpte;

    smpte = av_timecode_get_smpte((AVRational){30, 1}, 0, 1, 2, 3, 4);
    రాయి("smpte_tc 30/1 01:02:03:04: %s\n",
           av_timecode_make_smpte_tc_string(buf, smpte, 1));

    av_timecode_init(&tc, (AVRational){25, 1}, 0, 0, ఖాళీ);
    smpte = av_timecode_get_smpte_from_framenum(&tc,
                                                 25 * 3600 + 25 * 60 + 25 + 5);
    రాయి("smpte_from_framenum 25/1 91530: %s\n",
           av_timecode_make_smpte_tc_string(buf, smpte, 1));
}

స్థిర శూన్య test_make_smpte_tc_string2(శూన్య)
{
    అక్షరం buf[AV_TIMECODE_STR_కొలత];
    uint32_t smpte;

    smpte = av_timecode_get_smpte((AVRational){50, 1}, 0, 0, 0, 0, 0);
    రాయి("smpte_tc2 50/1 00:00:00:00: %s\n",
           av_timecode_make_smpte_tc_string2(buf, (AVRational){50, 1},
                                             smpte, 1, 0));

    smpte = av_timecode_get_smpte((AVRational){60, 1}, 0, 1, 0, 0, 0);
    రాయి("smpte_tc2 60/1 01:00:00:00: %s\n",
           av_timecode_make_smpte_tc_string2(buf, (AVRational){60, 1},
                                             smpte, 1, 0));
}

స్థిర శూన్య test_make_mpeg_tc_string(శూన్య)
{
    అక్షరం buf[AV_TIMECODE_STR_కొలత];

    uint32_t tc25 = (1u << 19) | (2u << 13) | (3u << 6) | 4u;
    రాయి("mpeg_tc 01:02:03:04: %s\n",
           av_timecode_make_mpeg_tc_string(buf, tc25));

    uint32_t tc25_drop = tc25 | (1u << 24);
    రాయి("mpeg_tc drop 01:02:03:04: %s\n",
           av_timecode_make_mpeg_tc_string(buf, tc25_drop));
}

స్థిర శూన్య test_adjust_ntsc(శూన్య)
{
    స్థిర స్థిరరాశి నిర్మాణం {
        పూర్ణాంకం framenum;
        పూర్ణాంకం fps;
    } cases[] = {
        { 0, 30 },
        { 1800, 30 },
        { 1000, 25 },
        { 1000, 0 },
        { 3600, 60 },
    };

    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(cases); i++) {
        రాయి("adjust_ntsc %d %d: %d\n",
               cases[i].framenum, cases[i].fps,
               av_timecode_adjust_ntsc_framenum2(cases[i].framenum,
                                                 cases[i].fps));
    }
}

స్థిర శూన్య test_get_smpte_roundtrip(శూన్య)
{
    అక్షరం buf[AV_TIMECODE_STR_కొలత];
    అక్షరం buf2[AV_TIMECODE_STR_కొలత];
    uint32_t smpte;

    smpte = av_timecode_get_smpte((AVRational){30, 1}, 0, 12, 34, 56, 7);
    రాయి("smpte_roundtrip 30/1 12:34:56:07: %s / %s\n",
           av_timecode_make_smpte_tc_string(buf, smpte, 1),
           av_timecode_make_smpte_tc_string2(buf2, (AVRational){30, 1},
                                             smpte, 1, 0));

    smpte = av_timecode_get_smpte((AVRational){30, 1}, 0, 0, 0, 0, 0);
    రాయి("smpte_roundtrip 30/1 00:00:00:00: %s / %s\n",
           av_timecode_make_smpte_tc_string(buf, smpte, 1),
           av_timecode_make_smpte_tc_string2(buf2, (AVRational){30, 1},
                                             smpte, 1, 0));

    smpte = av_timecode_get_smpte((AVRational){30000, 1001}, 1, 0, 1, 0, 2);
    రాయి("smpte_roundtrip 30000/1001 drop bit30=%d: %s / %s\n",
           !!(smpte & (1u << 30)),
           av_timecode_make_smpte_tc_string(buf, smpte, 0),
           av_timecode_make_smpte_tc_string2(buf2, (AVRational){30000, 1001},
                                             smpte, 0, 0));

    /* >30 fps SMPTE field bit handling test */
    smpte = av_timecode_get_smpte((AVRational){50, 1}, 0, 0, 0, 0, 49);
    రాయి("smpte_roundtrip 50/1 field bit7=%d: %s / %s\n",
           !!(smpte & (1u << 7)),
           av_timecode_make_smpte_tc_string(buf, smpte, 0),
           av_timecode_make_smpte_tc_string2(buf2, (AVRational){50, 1},
                                             smpte, 0, 0));

    smpte = av_timecode_get_smpte((AVRational){60000, 1001}, 0, 0, 0, 0, 59);
    రాయి("smpte_roundtrip 60000/1001 field bit23=%d: %s / %s\n",
           !!(smpte & (1u << 23)),
           av_timecode_make_smpte_tc_string(buf, smpte, 0),
           av_timecode_make_smpte_tc_string2(buf2, (AVRational){60000, 1001},
                                             smpte, 0, 0));
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    test_check_చట్రం_రేటు();
    test_init();
    test_init_from_components();
    test_init_from_string();
    test_make_string();
    test_make_smpte_tc_string();
    test_make_smpte_tc_string2();
    test_make_mpeg_tc_string();
    test_adjust_ntsc();
    test_get_smpte_roundtrip();
    తిరిగి 0;
}
