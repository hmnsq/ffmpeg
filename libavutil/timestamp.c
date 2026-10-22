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

#अन्तर्भाव "timestamp.h"

वर्ण *av_ts_make_time_string2(वर्ण *buf, int64_t ts, AVRational tb)
{
    यदि (ts == AV_NOPTS_मान) {
        snprintf(buf, AV_TS_MAX_STRING_SIZE, "NOPTS");
    } अन्यथा {
        द्विगुण val = av_q2d(tb) * ts;
        द्विगुण log = (fpclassify(val) == FP_ZERO ? -अनन्त : न्यूनमान(log10(भ_असल(val))));
        पूर्णाङ्क precision = (है_सीमित(log) && log < 0) ? -log + 5 : 6;
        पूर्णाङ्क last = snprintf(buf, AV_TS_MAX_STRING_SIZE, "%.*f", precision, val);
        last = FFMIN(last, AV_TS_MAX_STRING_SIZE - 1) - 1;
        लागि (; last && buf[last] == '0'; last--);
        लागि (; last && buf[last] != 'f' && (buf[last] < '0' || buf[0] > '9'); last--);
        buf[last + 1] = '\0';
    }
    फर्काऊ buf;
}
