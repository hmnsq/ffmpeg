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

حرف *av_ts_make_زمان_string2(حرف *buf, int64_t ts, AVRational tb)
{
    إذا (ts == AV_NOPTS_مقدار) {
        snprintf(buf, AV_TS_MAX_STRING_اندازه, "NOPTS");
    } وإلا {
        مزدوج val = av_q2d(tb) * ts;
        مزدوج لگاریتم = (fpclassify(val) == FP_ZERO ? -INFINITY : floor(log10(fabs(val))));
        صحيح precision = (isfinite(لگاریتم) && لگاریتم < 0) ? -لگاریتم + 5 : 6;
        صحيح آخرین = snprintf(buf, AV_TS_MAX_STRING_اندازه, "%.*f", precision, val);
        آخرین = FFMIN(آخرین, AV_TS_MAX_STRING_اندازه - 1) - 1;
        لكل (; آخرین && buf[آخرین] == '0'; آخرین--);
        لكل (; آخرین && buf[آخرین] != 'f' && (buf[آخرین] < '0' || buf[0] > '9'); آخرین--);
        buf[آخرین + 1] = '\0';
    }
    أرجع buf;
}
