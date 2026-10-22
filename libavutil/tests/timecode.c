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

#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "libavutil/macros.h"
#समावेश "libavutil/rational.h"
#समावेश "libavutil/timecode.h"

अटल व्योम test_check_frame_rate(व्योम)
{
    अटल स्थिर AVRational rates[] = {
        {24, 1}, {25, 1}, {30, 1}, {48, 1}, {50, 1}, {60, 1},
        {100, 1}, {120, 1}, {150, 1},
        {30000, 1001}, {15, 1}, {12, 1},
        {0, 0}, {30, 0},
    };
    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(rates); i++)
        म_लिखो("check_frame_rate %d/%d: %d\n",
               rates[i].अंक, rates[i].den,
               av_timecode_check_frame_rate(rates[i]));
}

अटल व्योम test_init(व्योम)
{
    AVTimecode tc;
    अटल स्थिर काष्ठा {
        AVRational rate;
        पूर्णांक flags;
        पूर्णांक start;
    } cases[] = {
        { {25, 1}, 0, 0 },
        { {30, 1}, AV_TIMECODE_FLAG_DROPFRAME, 0 },
        { {24, 1}, 0, 100 },
        { {0, 1}, 0, 0 },
        { {25, 1}, AV_TIMECODE_FLAG_DROPFRAME, 0 },
        { {30000, 1001}, AV_TIMECODE_FLAG_DROPFRAME, 0 },
        { {25, 1}, AV_TIMECODE_FLAG_ALLOWNEGATIVE, -100 },
    };

    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(cases); i++) {
        पूर्णांक ret = av_timecode_init(&tc, cases[i].rate, cases[i].flags, cases[i].start, शून्य);
        म_लिखो("init %d/%d flags:%d start:%d: ",
               cases[i].rate.अंक, cases[i].rate.den, cases[i].flags, cases[i].start);
        अगर (ret < 0) {
            म_लिखो("error\n");
        } अन्यथा {
            म_लिखो("ok fps=%d start=%d rate=%d/%d\n",
                   tc.fps, tc.start, tc.rate.अंक, tc.rate.den);
        }
    }
}

अटल व्योम test_init_from_components(व्योम)
{
    AVTimecode tc;
    पूर्णांक ret;

    ret = av_timecode_init_from_components(&tc, (AVRational){25, 1},
                                           0, 0, 0, 0, 0, शून्य);
    म_लिखो("from_components 25/1 00:00:00:00: %d start=%d\n", ret, tc.start);

    ret = av_timecode_init_from_components(&tc, (AVRational){25, 1},
                                           0, 1, 0, 0, 0, शून्य);
    म_लिखो("from_components 25/1 01:00:00:00: %d start=%d\n", ret, tc.start);

    ret = av_timecode_init_from_components(&tc, (AVRational){30, 1},
                                           0, 1, 2, 3, 4, शून्य);
    म_लिखो("from_components 30/1 01:02:03:04: %d start=%d\n", ret, tc.start);

    ret = av_timecode_init_from_components(&tc, (AVRational){30000, 1001},
                                           AV_TIMECODE_FLAG_DROPFRAME,
                                           1, 0, 0, 0, शून्य);
    म_लिखो("from_components 30000/1001 drop 01:00:00;00: %d start=%d\n",
           ret, tc.start);
}

अटल व्योम test_init_from_string(व्योम)
{
    AVTimecode tc;
    पूर्णांक ret;

    ret = av_timecode_init_from_string(&tc, (AVRational){30, 1},
                                       "00:01:02:03", शून्य);
    म_लिखो("from_string 30/1 00:01:02:03: %d drop=%d start=%d\n",
           ret, !!(tc.flags & AV_TIMECODE_FLAG_DROPFRAME), tc.start);

    ret = av_timecode_init_from_string(&tc, (AVRational){30000, 1001},
                                       "00:01:00;02", शून्य);
    म_लिखो("from_string 30000/1001 00:01:00;02: %d drop=%d\n",
           ret, !!(tc.flags & AV_TIMECODE_FLAG_DROPFRAME));

    ret = av_timecode_init_from_string(&tc, (AVRational){30000, 1001},
                                       "01:00:00.00", शून्य);
    म_लिखो("from_string 30000/1001 01:00:00.00: %d drop=%d\n",
           ret, !!(tc.flags & AV_TIMECODE_FLAG_DROPFRAME));

    ret = av_timecode_init_from_string(&tc, (AVRational){25, 1},
                                       "notvalid", शून्य);
    म_लिखो("from_string 25/1 notvalid: %s\n", ret < 0 ? "error" : "ok");
}

अटल व्योम test_make_string(व्योम)
{
    AVTimecode tc;
    अक्षर buf[AV_TIMECODE_STR_आकार];

    av_timecode_init(&tc, (AVRational){25, 1}, 0, 0, शून्य);
    म_लिखो("make_string 25/1 35: %s\n", av_timecode_make_string(&tc, buf, 35));
    म_लिखो("make_string 25/1 0: %s\n", av_timecode_make_string(&tc, buf, 0));

    av_timecode_init(&tc, (AVRational){30, 1}, 0, 0, शून्य);
    म_लिखो("make_string 30/1 30: %s\n", av_timecode_make_string(&tc, buf, 30));

    av_timecode_init(&tc, (AVRational){25, 1},
                     AV_TIMECODE_FLAG_24HOURSMAX, 0, शून्य);
    म_लिखो("make_string 25/1 24hwrap %d: %s\n",
           25 * 3600 * 25, av_timecode_make_string(&tc, buf, 25 * 3600 * 25));

    av_timecode_init(&tc, (AVRational){30000, 1001},
                     AV_TIMECODE_FLAG_DROPFRAME, 0, शून्य);
    म_लिखो("make_string 30000/1001 drop 0: %s\n",
           av_timecode_make_string(&tc, buf, 0));

    av_timecode_init(&tc, (AVRational){25, 1},
                     AV_TIMECODE_FLAG_ALLOWNEGATIVE, -100, शून्य);
    म_लिखो("make_string 25/1 negative start -100 frame 0: %s\n",
           av_timecode_make_string(&tc, buf, 0));
}

अटल व्योम test_make_smpte_tc_string(व्योम)
{
    अक्षर buf[AV_TIMECODE_STR_आकार];
    AVTimecode tc;
    uint32_t smpte;

    smpte = av_timecode_get_smpte((AVRational){30, 1}, 0, 1, 2, 3, 4);
    म_लिखो("smpte_tc 30/1 01:02:03:04: %s\n",
           av_timecode_make_smpte_tc_string(buf, smpte, 1));

    av_timecode_init(&tc, (AVRational){25, 1}, 0, 0, शून्य);
    smpte = av_timecode_get_smpte_from_framenum(&tc,
                                                 25 * 3600 + 25 * 60 + 25 + 5);
    म_लिखो("smpte_from_framenum 25/1 91530: %s\n",
           av_timecode_make_smpte_tc_string(buf, smpte, 1));
}

अटल व्योम test_make_smpte_tc_string2(व्योम)
{
    अक्षर buf[AV_TIMECODE_STR_आकार];
    uint32_t smpte;

    smpte = av_timecode_get_smpte((AVRational){50, 1}, 0, 0, 0, 0, 0);
    म_लिखो("smpte_tc2 50/1 00:00:00:00: %s\n",
           av_timecode_make_smpte_tc_string2(buf, (AVRational){50, 1},
                                             smpte, 1, 0));

    smpte = av_timecode_get_smpte((AVRational){60, 1}, 0, 1, 0, 0, 0);
    म_लिखो("smpte_tc2 60/1 01:00:00:00: %s\n",
           av_timecode_make_smpte_tc_string2(buf, (AVRational){60, 1},
                                             smpte, 1, 0));
}

अटल व्योम test_make_mpeg_tc_string(व्योम)
{
    अक्षर buf[AV_TIMECODE_STR_आकार];

    uint32_t tc25 = (1u << 19) | (2u << 13) | (3u << 6) | 4u;
    म_लिखो("mpeg_tc 01:02:03:04: %s\n",
           av_timecode_make_mpeg_tc_string(buf, tc25));

    uint32_t tc25_drop = tc25 | (1u << 24);
    म_लिखो("mpeg_tc drop 01:02:03:04: %s\n",
           av_timecode_make_mpeg_tc_string(buf, tc25_drop));
}

अटल व्योम test_adjust_ntsc(व्योम)
{
    अटल स्थिर काष्ठा {
        पूर्णांक framenum;
        पूर्णांक fps;
    } cases[] = {
        { 0, 30 },
        { 1800, 30 },
        { 1000, 25 },
        { 1000, 0 },
        { 3600, 60 },
    };

    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(cases); i++) {
        म_लिखो("adjust_ntsc %d %d: %d\n",
               cases[i].framenum, cases[i].fps,
               av_timecode_adjust_ntsc_framenum2(cases[i].framenum,
                                                 cases[i].fps));
    }
}

अटल व्योम test_get_smpte_roundtrip(व्योम)
{
    अक्षर buf[AV_TIMECODE_STR_आकार];
    अक्षर buf2[AV_TIMECODE_STR_आकार];
    uint32_t smpte;

    smpte = av_timecode_get_smpte((AVRational){30, 1}, 0, 12, 34, 56, 7);
    म_लिखो("smpte_roundtrip 30/1 12:34:56:07: %s / %s\n",
           av_timecode_make_smpte_tc_string(buf, smpte, 1),
           av_timecode_make_smpte_tc_string2(buf2, (AVRational){30, 1},
                                             smpte, 1, 0));

    smpte = av_timecode_get_smpte((AVRational){30, 1}, 0, 0, 0, 0, 0);
    म_लिखो("smpte_roundtrip 30/1 00:00:00:00: %s / %s\n",
           av_timecode_make_smpte_tc_string(buf, smpte, 1),
           av_timecode_make_smpte_tc_string2(buf2, (AVRational){30, 1},
                                             smpte, 1, 0));

    smpte = av_timecode_get_smpte((AVRational){30000, 1001}, 1, 0, 1, 0, 2);
    म_लिखो("smpte_roundtrip 30000/1001 drop bit30=%d: %s / %s\n",
           !!(smpte & (1u << 30)),
           av_timecode_make_smpte_tc_string(buf, smpte, 0),
           av_timecode_make_smpte_tc_string2(buf2, (AVRational){30000, 1001},
                                             smpte, 0, 0));

    /* >30 fps SMPTE field bit handling test */
    smpte = av_timecode_get_smpte((AVRational){50, 1}, 0, 0, 0, 0, 49);
    म_लिखो("smpte_roundtrip 50/1 field bit7=%d: %s / %s\n",
           !!(smpte & (1u << 7)),
           av_timecode_make_smpte_tc_string(buf, smpte, 0),
           av_timecode_make_smpte_tc_string2(buf2, (AVRational){50, 1},
                                             smpte, 0, 0));

    smpte = av_timecode_get_smpte((AVRational){60000, 1001}, 0, 0, 0, 0, 59);
    म_लिखो("smpte_roundtrip 60000/1001 field bit23=%d: %s / %s\n",
           !!(smpte & (1u << 23)),
           av_timecode_make_smpte_tc_string(buf, smpte, 0),
           av_timecode_make_smpte_tc_string2(buf2, (AVRational){60000, 1001},
                                             smpte, 0, 0));
}

पूर्णांक मुख्य(व्योम)
{
    test_check_frame_rate();
    test_init();
    test_init_from_components();
    test_init_from_string();
    test_make_string();
    test_make_smpte_tc_string();
    test_make_smpte_tc_string2();
    test_make_mpeg_tc_string();
    test_adjust_ntsc();
    test_get_smpte_roundtrip();
    वापस 0;
}
