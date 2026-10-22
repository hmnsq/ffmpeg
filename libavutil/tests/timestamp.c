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

#ضمن <inttypes.h>
#ضمن <stdio.h>

#ضمن "libavutil/avutil.h"
#ضمن "libavutil/macros.h"
#ضمن "libavutil/rational.h"
#ضمن "libavutil/timestamp.h"

صحيح اصلي(فراغ)
{
    حرف buf[AV_TS_MAX_STRING_اندازه];
    ساكن ثابت بنية { ثابت حرف *label; int64_t ts; } ts_vals[] = {
        { "NOPTS",       AV_NOPTS_ارزښت  },
        { "0",           0               },
        { "90000",       90000           },
        { "-1",          -1              },
        { "INT64_MAX",   INT64_MAX       },
        { "INT64_MIN+1", INT64_MIN + 1   },
    };
    ساكن ثابت بنية { ثابت حرف *label; int64_t ts; AVRational tb; } وخت_vals[] = {
        { "NOPTS",             AV_NOPTS_ارزښت, {1, 90000} },
        { "90000 at 1/90000",  90000,          {1, 90000} },
        { "0 at 1/1000",       0,              {1, 1000}  },
        { "48000 at 1/48000",  48000,          {1, 48000} },
        { "44100 at 1/44100",  44100,          {1, 44100} },
        { "-90000 at 1/90000", -90000,         {1, 90000} },
    };

    /* av_ts_make_string */
    چاپ_کړه("Testing av_ts_make_string()\n");
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(ts_vals); i++)
        چاپ_کړه("%s: %s\n", ts_vals[i].label,
               av_ts_make_string(buf, ts_vals[i].ts));

    /* av_ts2str macro */
    چاپ_کړه("\nTesting av_ts2str()\n");
    چاپ_کړه("NOPTS: %s\n", av_ts2str(AV_NOPTS_ارزښت));
    چاپ_کړه("48000: %s\n", av_ts2str(48000));

    /* av_ts_make_time_string2 */
    چاپ_کړه("\nTesting av_ts_make_time_string2()\n");
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(وخت_vals); i++)
        چاپ_کړه("%s: %s\n", وخت_vals[i].label,
               av_ts_make_وخت_string2(buf, وخت_vals[i].ts, وخت_vals[i].tb));

    /* av_ts_make_time_string (AVRational pointer version) */
    چاپ_کړه("\nTesting av_ts_make_time_string()\n");
    {
        AVRational tb = {1, 1000};
        چاپ_کړه("5000 at 1/1000: %s\n",
               av_ts_make_وخت_string(buf, 5000, &tb));
        چاپ_کړه("NOPTS: %s\n",
               av_ts_make_وخت_string(buf, AV_NOPTS_ارزښت, &tb));
    }

    أرجع 0;
}
