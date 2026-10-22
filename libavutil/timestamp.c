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

#ಅನ್ತರ್ಭಾವ "timestamp.h"

ವರ್ಣ *av_ts_make_time_string2(ವರ್ಣ *buf, int64_t ts, AVRational tb)
{
    ಯದಿ (ts == AV_NOPTS_ಮೌಲ್ಯ) {
        snprintf(buf, AV_TS_MAX_STRING_SIZE, "NOPTS");
    } ಅನ್ಯಥಾ {
        ದ್ವಿಗುಣ val = av_q2d(tb) * ts;
        ದ್ವಿಗುಣ log = (fpclassify(val) == FP_ZERO ? -INFINITY : floor(log10(fabs(val))));
        ಪೂರ್ಣಾಙ್ಕ precision = (isfinite(log) && log < 0) ? -log + 5 : 6;
        ಪೂರ್ಣಾಙ್ಕ last = snprintf(buf, AV_TS_MAX_STRING_SIZE, "%.*f", precision, val);
        last = FFMIN(last, AV_TS_MAX_STRING_SIZE - 1) - 1;
        ಪ್ರತಿ (; last && buf[last] == '0'; last--);
        ಪ್ರತಿ (; last && buf[last] != 'f' && (buf[last] < '0' || buf[0] > '9'); last--);
        buf[last + 1] = '\0';
    }
    ಪ್ರತ್ಯಾಗಮ buf;
}
