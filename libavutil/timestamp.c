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

#অন্তর্ভাব "timestamp.h"

অক্ষর *av_ts_make_time_string2(অক্ষর *buf, int64_t ts, AVRational tb)
{
    যদি (ts == AV_NOPTS_মান) {
        snprintf(buf, AV_TS_MAX_STRING_আকার, "NOPTS");
    } অন্যথা {
        দ্বিগুণ val = av_q2d(tb) * ts;
        দ্বিগুণ log = (fpclassify(val) == FP_ZERO ? -INFINITY : floor(log10(fabs(val))));
        পূর্ণসংখ্যা precision = (isfinite(log) && log < 0) ? -log + 5 : 6;
        পূর্ণসংখ্যা last = snprintf(buf, AV_TS_MAX_STRING_আকার, "%.*f", precision, val);
        last = FFMIN(last, AV_TS_MAX_STRING_আকার - 1) - 1;
        জন্য (; last && buf[last] == '0'; last--);
        জন্য (; last && buf[last] != 'f' && (buf[last] < '0' || buf[0] > '9'); last--);
        buf[last + 1] = '\0';
    }
    ফেরত buf;
}
