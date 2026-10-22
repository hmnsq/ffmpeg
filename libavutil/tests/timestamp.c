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

#अन्तर्भाव <inttypes.h>
#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/avutil.h"
#अन्तर्भाव "libavutil/macros.h"
#अन्तर्भाव "libavutil/rational.h"
#अन्तर्भाव "libavutil/timestamp.h"

पूर्णाङ्क मुख्यम्(शून्य)
{
    वर्ण buf[AV_TS_MAX_STRING_आकार];
    स्थिर ध्रुव संरचना { ध्रुव वर्ण *label; int64_t ts; } ts_vals[] = {
        { "NOPTS",       AV_NOPTS_मानम्  },
        { "0",           0               },
        { "90000",       90000           },
        { "-1",          -1              },
        { "INT64_MAX",   INT64_MAX       },
        { "INT64_MIN+1", INT64_MIN + 1   },
    };
    स्थिर ध्रुव संरचना { ध्रुव वर्ण *label; int64_t ts; AVRational tb; } time_vals[] = {
        { "NOPTS",             AV_NOPTS_मानम्, {1, 90000} },
        { "90000 at 1/90000",  90000,          {1, 90000} },
        { "0 at 1/1000",       0,              {1, 1000}  },
        { "48000 at 1/48000",  48000,          {1, 48000} },
        { "44100 at 1/44100",  44100,          {1, 44100} },
        { "-90000 at 1/90000", -90000,         {1, 90000} },
    };

    /* av_ts_make_string */
    प्रारूप_लिख("Testing av_ts_make_string()\n");
    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(ts_vals); i++)
        प्रारूप_लिख("%s: %s\n", ts_vals[i].label,
               av_ts_make_string(buf, ts_vals[i].ts));

    /* av_ts2str macro */
    प्रारूप_लिख("\nTesting av_ts2str()\n");
    प्रारूप_लिख("NOPTS: %s\n", av_ts2str(AV_NOPTS_मानम्));
    प्रारूप_लिख("48000: %s\n", av_ts2str(48000));

    /* av_ts_make_time_string2 */
    प्रारूप_लिख("\nTesting av_ts_make_time_string2()\n");
    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(time_vals); i++)
        प्रारूप_लिख("%s: %s\n", time_vals[i].label,
               av_ts_make_time_string2(buf, time_vals[i].ts, time_vals[i].tb));

    /* av_ts_make_time_string (AVRational pointer version) */
    प्रारूप_लिख("\nTesting av_ts_make_time_string()\n");
    {
        AVRational tb = {1, 1000};
        प्रारूप_लिख("5000 at 1/1000: %s\n",
               av_ts_make_time_string(buf, 5000, &tb));
        प्रारूप_लिख("NOPTS: %s\n",
               av_ts_make_time_string(buf, AV_NOPTS_मानम्, &tb));
    }

    प्रत्यागम 0;
}
