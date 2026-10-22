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

/**
 * @file
 * timestamp utils, mostly useful for debugging/logging purposes
 */

#که_نه_تعریف_شوی AVUTIL_TIMESTAMP_H
#تعریف_کړه AVUTIL_TIMESTAMP_H

#ضمن "avutil.h"

#إذا defined(__cplusplus) && !defined(__STDC_FORMAT_MACROS) && !defined(PRId64)
#تېروتنه missing -D__STDC_FORMAT_MACROS / #تعریف_کړه __STDC_FORMAT_MACROS
#د_که_پای

#تعریف_کړه AV_TS_MAX_STRING_اندازه 32

/**
 * Fill the provided buffer with a string containing a timestamp
 * representation.
 *
 * @param buf a buffer with size in bytes of at least AV_TS_MAX_STRING_SIZE
 * @param ts the timestamp to represent
 * @return the buffer in input
 */
ساكن مضمن حرف *av_ts_make_string(حرف *buf, int64_t ts)
{
    إذا (ts == AV_NOPTS_ارزښت) snprintf(buf, AV_TS_MAX_STRING_اندازه, "NOPTS");
    وإلا                      snprintf(buf, AV_TS_MAX_STRING_اندازه, "%" PRId64, ts);
    أرجع buf;
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#تعریف_کړه av_ts2str(ts) av_ts_make_string((حرف[AV_TS_MAX_STRING_اندازه]){0}, ts)

/**
 * Fill the provided buffer with a string containing a timestamp time
 * representation.
 *
 * @param buf a buffer with size in bytes of at least AV_TS_MAX_STRING_SIZE
 * @param ts the timestamp to represent
 * @param tb the timebase of the timestamp
 * @return the buffer in input
 */
حرف *av_ts_make_وخت_string2(حرف *buf, int64_t ts, AVRational tb);

/**
 * Fill the provided buffer with a string containing a timestamp
 * representation.
 *
 * @see av_ts_make_time_string2
 */
ساكن مضمن حرف *av_ts_make_وخت_string(حرف *buf, int64_t ts,
                                           ثابت AVRational *tb)
{
    أرجع av_ts_make_وخت_string2(buf, ts, *tb);
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#تعریف_کړه av_ts2timestr(ts, tb) av_ts_make_وخت_string((حرف[AV_TS_MAX_STRING_اندازه]){0}, ts, tb)

#د_که_پای /* AVUTIL_TIMESTAMP_H */
