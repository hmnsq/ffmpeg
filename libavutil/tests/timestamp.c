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

#అన్తర్భావ <inttypes.h>
#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/avutil.h"
#అన్తర్భావ "libavutil/macros.h"
#అన్తర్భావ "libavutil/rational.h"
#అన్తర్భావ "libavutil/timestamp.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    అక్షరం buf[AV_TS_MAX_STRING_కొలత];
    స్థిర స్థిరరాశి నిర్మాణం { స్థిరరాశి అక్షరం *label; int64_t ts; } ts_vals[] = {
        { "NOPTS",       AV_NOPTS_విలువ  },
        { "0",           0               },
        { "90000",       90000           },
        { "-1",          -1              },
        { "INT64_MAX",   INT64_MAX       },
        { "INT64_MIN+1", INT64_MIN + 1   },
    };
    స్థిర స్థిరరాశి నిర్మాణం { స్థిరరాశి అక్షరం *label; int64_t ts; AVRational tb; } సమయం_vals[] = {
        { "NOPTS",             AV_NOPTS_విలువ, {1, 90000} },
        { "90000 at 1/90000",  90000,          {1, 90000} },
        { "0 at 1/1000",       0,              {1, 1000}  },
        { "48000 at 1/48000",  48000,          {1, 48000} },
        { "44100 at 1/44100",  44100,          {1, 44100} },
        { "-90000 at 1/90000", -90000,         {1, 90000} },
    };

    /* av_ts_make_string */
    రాయి("Testing av_ts_make_string()\n");
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(ts_vals); i++)
        రాయి("%s: %s\n", ts_vals[i].label,
               av_ts_make_string(buf, ts_vals[i].ts));

    /* av_ts2str macro */
    రాయి("\nTesting av_ts2str()\n");
    రాయి("NOPTS: %s\n", av_ts2str(AV_NOPTS_విలువ));
    రాయి("48000: %s\n", av_ts2str(48000));

    /* av_ts_make_time_string2 */
    రాయి("\nTesting av_ts_make_time_string2()\n");
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(సమయం_vals); i++)
        రాయి("%s: %s\n", సమయం_vals[i].label,
               av_ts_make_సమయం_string2(buf, సమయం_vals[i].ts, సమయం_vals[i].tb));

    /* av_ts_make_time_string (AVRational pointer version) */
    రాయి("\nTesting av_ts_make_time_string()\n");
    {
        AVRational tb = {1, 1000};
        రాయి("5000 at 1/1000: %s\n",
               av_ts_make_సమయం_string(buf, 5000, &tb));
        రాయి("NOPTS: %s\n",
               av_ts_make_సమయం_string(buf, AV_NOPTS_విలువ, &tb));
    }

    తిరిగి 0;
}
