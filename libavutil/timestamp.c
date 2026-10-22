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

ಅಕ್ಷರ *av_ts_make_ಸಮಯ_string2(ಅಕ್ಷರ *buf, int64_t ts, AVRational tb)
{
    ಆದರೆ (ts == AV_NOPTS_ಮೌಲ್ಯ) {
        snprintf(buf, AV_TS_MAX_STRING_ಗಾತ್ರ, "NOPTS");
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದ್ವಿಗುಣ val = av_q2d(tb) * ts;
        ದ್ವಿಗುಣ ಲಘುಗಣಕ = (fpclassify(val) == FP_ZERO ? -INFINITY : floor(log10(fabs(val))));
        ಪೂರ್ಣಾಂಕ precision = (isfinite(ಲಘುಗಣಕ) && ಲಘುಗಣಕ < 0) ? -ಲಘುಗಣಕ + 5 : 6;
        ಪೂರ್ಣಾಂಕ ಕೊನೆಯ = snprintf(buf, AV_TS_MAX_STRING_ಗಾತ್ರ, "%.*f", precision, val);
        ಕೊನೆಯ = FFMIN(ಕೊನೆಯ, AV_TS_MAX_STRING_ಗಾತ್ರ - 1) - 1;
        ಗಾಗಿ (; ಕೊನೆಯ && buf[ಕೊನೆಯ] == '0'; ಕೊನೆಯ--);
        ಗಾಗಿ (; ಕೊನೆಯ && buf[ಕೊನೆಯ] != 'f' && (buf[ಕೊನೆಯ] < '0' || buf[0] > '9'); ಕೊನೆಯ--);
        buf[ಕೊನೆಯ + 1] = '\0';
    }
    ಹಿಂತಿರುಗಿ buf;
}
