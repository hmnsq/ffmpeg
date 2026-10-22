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

#ضمن "timestamp.h"

حرف *av_ts_make_time_string2(حرف *buf, int64_t ts, AVRational tb)
{
    אם (ts == AV_NOPTS_VALUE) {
        snprintf(buf, AV_TS_MAX_STRING_SIZE, "NOPTS");
    } אחרת {
        مزدوج val = av_q2d(tb) * ts;
        مزدوج log = (fpclassify(val) == FP_ZERO ? -INFINITY : floor(log10(fabs(val))));
        صحيح precision = (isfinite(log) && log < 0) ? -log + 5 : 6;
        صحيح last = snprintf(buf, AV_TS_MAX_STRING_SIZE, "%.*f", precision, val);
        last = FFMIN(last, AV_TS_MAX_STRING_SIZE - 1) - 1;
        עבור (; last && buf[last] == '0'; last--);
        עבור (; last && buf[last] != 'f' && (buf[last] < '0' || buf[0] > '9'); last--);
        buf[last + 1] = '\0';
    }
    החזר buf;
}
