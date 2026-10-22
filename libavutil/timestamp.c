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

#ਅਨ੍ਤਰ੍ਭਾਵ "timestamp.h"

ਅੱਖਰ *av_ts_make_ਸਮਾਂ_string2(ਅੱਖਰ *buf, int64_t ts, AVRational tb)
{
    ਜੇ (ts == AV_NOPTS_ਮੁੱਲ) {
        snprintf(buf, AV_TS_MAX_STRING_ਮਾਪ, "NOPTS");
    } ਨਹੀਂਤਾਂ {
        ਦੁੱਗਣਾ val = av_q2d(tb) * ts;
        ਦੁੱਗਣਾ ਲਘੂਗਣਕ = (fpclassify(val) == FP_ZERO ? -INFINITY : floor(log10(fabs(val))));
        ਪੂਰਨ precision = (isfinite(ਲਘੂਗਣਕ) && ਲਘੂਗਣਕ < 0) ? -ਲਘੂਗਣਕ + 5 : 6;
        ਪੂਰਨ ਆਖਰੀ = snprintf(buf, AV_TS_MAX_STRING_ਮਾਪ, "%.*f", precision, val);
        ਆਖਰੀ = FFMIN(ਆਖਰੀ, AV_TS_MAX_STRING_ਮਾਪ - 1) - 1;
        ਲਈ (; ਆਖਰੀ && buf[ਆਖਰੀ] == '0'; ਆਖਰੀ--);
        ਲਈ (; ਆਖਰੀ && buf[ਆਖਰੀ] != 'f' && (buf[ਆਖਰੀ] < '0' || buf[0] > '9'); ਆਖਰੀ--);
        buf[ਆਖਰੀ + 1] = '\0';
    }
    ਵਾਪਸ buf;
}
