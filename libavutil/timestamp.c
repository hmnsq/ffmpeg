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

#అన్తర్భావ "timestamp.h"

అక్షరం *av_ts_make_సమయం_string2(అక్షరం *buf, int64_t ts, AVRational tb)
{
    ఒకవేళ (ts == AV_NOPTS_విలువ) {
        snprintf(buf, AV_TS_MAX_STRING_కొలత, "NOPTS");
    } లేకపోతే {
        ద్విగుణ val = av_q2d(tb) * ts;
        ద్విగుణ సంవర్గమానం = (fpclassify(val) == FP_ZERO ? -INFINITY : floor(log10(fabs(val))));
        పూర్ణాంకం precision = (isfinite(సంవర్గమానం) && సంవర్గమానం < 0) ? -సంవర్గమానం + 5 : 6;
        పూర్ణాంకం చివరి = snprintf(buf, AV_TS_MAX_STRING_కొలత, "%.*f", precision, val);
        చివరి = FFMIN(చివరి, AV_TS_MAX_STRING_కొలత - 1) - 1;
        కొరకు (; చివరి && buf[చివరి] == '0'; చివరి--);
        కొరకు (; చివరి && buf[చివరి] != 'f' && (buf[చివరి] < '0' || buf[0] > '9'); చివరి--);
        buf[చివరి + 1] = '\0';
    }
    తిరిగి buf;
}
