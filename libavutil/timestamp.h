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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_TIMESTAMP_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_TIMESTAMP_H

#ਅਨ੍ਤਰ੍ਭਾਵ "avutil.h"

#ਜੇ defined(__cplusplus) && !defined(__STDC_FORMAT_MACROS) && !defined(PRId64)
#ਗਲਤੀ missing -D__STDC_FORMAT_MACROS / #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __STDC_FORMAT_MACROS
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_TS_MAX_STRING_ਮਾਪ 32

/**
 * Fill the provided buffer with a string containing a timestamp
 * representation.
 *
 * @param buf a buffer with size in bytes of at least AV_TS_MAX_STRING_SIZE
 * @param ts the timestamp to represent
 * @return the buffer in input
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਅੱਖਰ *av_ts_make_string(ਅੱਖਰ *buf, int64_t ts)
{
    ਜੇ (ts == AV_NOPTS_ਮੁੱਲ) snprintf(buf, AV_TS_MAX_STRING_ਮਾਪ, "NOPTS");
    ਨਹੀਂਤਾਂ                      snprintf(buf, AV_TS_MAX_STRING_ਮਾਪ, "%" PRId64, ts);
    ਵਾਪਸ buf;
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_ts2str(ts) av_ts_make_string((ਅੱਖਰ[AV_TS_MAX_STRING_ਮਾਪ]){0}, ts)

/**
 * Fill the provided buffer with a string containing a timestamp time
 * representation.
 *
 * @param buf a buffer with size in bytes of at least AV_TS_MAX_STRING_SIZE
 * @param ts the timestamp to represent
 * @param tb the timebase of the timestamp
 * @return the buffer in input
 */
ਅੱਖਰ *av_ts_make_ਸਮਾਂ_string2(ਅੱਖਰ *buf, int64_t ts, AVRational tb);

/**
 * Fill the provided buffer with a string containing a timestamp
 * representation.
 *
 * @see av_ts_make_time_string2
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਅੱਖਰ *av_ts_make_ਸਮਾਂ_string(ਅੱਖਰ *buf, int64_t ts,
                                           ਅਚਲ AVRational *tb)
{
    ਵਾਪਸ av_ts_make_ਸਮਾਂ_string2(buf, ts, *tb);
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_ts2timestr(ts, tb) av_ts_make_ਸਮਾਂ_string((ਅੱਖਰ[AV_TS_MAX_STRING_ਮਾਪ]){0}, ts, tb)

#ਜੇ_ਅੰਤ /* AVUTIL_TIMESTAMP_H */
