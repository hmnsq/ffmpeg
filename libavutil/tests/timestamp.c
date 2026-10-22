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

#ಅನ್ತರ್ಭಾವ <inttypes.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/avutil.h"
#ಅನ್ತರ್ಭಾವ "libavutil/macros.h"
#ಅನ್ತರ್ಭಾವ "libavutil/rational.h"
#ಅನ್ತರ್ಭಾವ "libavutil/timestamp.h"

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಅಕ್ಷರ buf[AV_TS_MAX_STRING_ಗಾತ್ರ];
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ { ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *label; int64_t ts; } ts_vals[] = {
        { "NOPTS",       AV_NOPTS_ಮೌಲ್ಯ  },
        { "0",           0               },
        { "90000",       90000           },
        { "-1",          -1              },
        { "INT64_MAX",   INT64_MAX       },
        { "INT64_MIN+1", INT64_MIN + 1   },
    };
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ { ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *label; int64_t ts; AVRational tb; } ಸಮಯ_vals[] = {
        { "NOPTS",             AV_NOPTS_ಮೌಲ್ಯ, {1, 90000} },
        { "90000 at 1/90000",  90000,          {1, 90000} },
        { "0 at 1/1000",       0,              {1, 1000}  },
        { "48000 at 1/48000",  48000,          {1, 48000} },
        { "44100 at 1/44100",  44100,          {1, 44100} },
        { "-90000 at 1/90000", -90000,         {1, 90000} },
    };

    /* av_ts_make_string */
    ಬರೆ("Testing av_ts_make_string()\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(ts_vals); i++)
        ಬರೆ("%s: %s\n", ts_vals[i].label,
               av_ts_make_string(buf, ts_vals[i].ts));

    /* av_ts2str macro */
    ಬರೆ("\nTesting av_ts2str()\n");
    ಬರೆ("NOPTS: %s\n", av_ts2str(AV_NOPTS_ಮೌಲ್ಯ));
    ಬರೆ("48000: %s\n", av_ts2str(48000));

    /* av_ts_make_time_string2 */
    ಬರೆ("\nTesting av_ts_make_time_string2()\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(ಸಮಯ_vals); i++)
        ಬರೆ("%s: %s\n", ಸಮಯ_vals[i].label,
               av_ts_make_ಸಮಯ_string2(buf, ಸಮಯ_vals[i].ts, ಸಮಯ_vals[i].tb));

    /* av_ts_make_time_string (AVRational pointer version) */
    ಬರೆ("\nTesting av_ts_make_time_string()\n");
    {
        AVRational tb = {1, 1000};
        ಬರೆ("5000 at 1/1000: %s\n",
               av_ts_make_ಸಮಯ_string(buf, 5000, &tb));
        ಬರೆ("NOPTS: %s\n",
               av_ts_make_ಸಮಯ_string(buf, AV_NOPTS_ಮೌಲ್ಯ, &tb));
    }

    ಹಿಂತಿರುಗಿ 0;
}
