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

#నిర్వచితం_కాకపోతే AVUTIL_TIMESTAMP_H
#నిర్వచించు AVUTIL_TIMESTAMP_H

#అన్తర్భావ "avutil.h"

#ఒకవేళ defined(__cplusplus) && !defined(__STDC_FORMAT_MACROS) && !defined(PRId64)
#దోషం missing -D__STDC_FORMAT_MACROS / #నిర్వచించు __STDC_FORMAT_MACROS
#అయితే_ముగింపు

#నిర్వచించు AV_TS_MAX_STRING_కొలత 32

/**
 * Fill the provided buffer with a string containing a timestamp
 * representation.
 *
 * @param buf a buffer with size in bytes of at least AV_TS_MAX_STRING_SIZE
 * @param ts the timestamp to represent
 * @return the buffer in input
 */
స్థిర అంతఃవరుస అక్షరం *av_ts_make_string(అక్షరం *buf, int64_t ts)
{
    ఒకవేళ (ts == AV_NOPTS_విలువ) snprintf(buf, AV_TS_MAX_STRING_కొలత, "NOPTS");
    లేకపోతే                      snprintf(buf, AV_TS_MAX_STRING_కొలత, "%" PRId64, ts);
    తిరిగి buf;
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#నిర్వచించు av_ts2str(ts) av_ts_make_string((అక్షరం[AV_TS_MAX_STRING_కొలత]){0}, ts)

/**
 * Fill the provided buffer with a string containing a timestamp time
 * representation.
 *
 * @param buf a buffer with size in bytes of at least AV_TS_MAX_STRING_SIZE
 * @param ts the timestamp to represent
 * @param tb the timebase of the timestamp
 * @return the buffer in input
 */
అక్షరం *av_ts_make_సమయం_string2(అక్షరం *buf, int64_t ts, AVRational tb);

/**
 * Fill the provided buffer with a string containing a timestamp
 * representation.
 *
 * @see av_ts_make_time_string2
 */
స్థిర అంతఃవరుస అక్షరం *av_ts_make_సమయం_string(అక్షరం *buf, int64_t ts,
                                           స్థిరరాశి AVRational *tb)
{
    తిరిగి av_ts_make_సమయం_string2(buf, ts, *tb);
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#నిర్వచించు av_ts2timestr(ts, tb) av_ts_make_సమయం_string((అక్షరం[AV_TS_MAX_STRING_కొలత]){0}, ts, tb)

#అయితే_ముగింపు /* AVUTIL_TIMESTAMP_H */
