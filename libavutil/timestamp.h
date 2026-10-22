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

#ifndef AVUTIL_TIMESTAMP_H
#define AVUTIL_TIMESTAMP_H

#ଅନ୍ତର୍ଭାଵ "avutil.h"

#ଯଦି defined(__cplusplus) && !defined(__STDC_FORMAT_MACROS) && !defined(PRId64)
#error missing -D__STDC_FORMAT_MACROS / #define __STDC_FORMAT_MACROS
#endif

#define AV_TS_MAX_STRING_SIZE 32

/**
 * Fill the provided buffer with a string containing a timestamp
 * representation.
 *
 * @param buf a buffer with size in bytes of at least AV_TS_MAX_STRING_SIZE
 * @param ts the timestamp to represent
 * @return the buffer in input
 */
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଅକ୍ଷର *av_ts_make_string(ଅକ୍ଷର *buf, int64_t ts)
{
    ଯଦି (ts == AV_NOPTS_ମୂଲ୍ୟ) snprintf(buf, AV_TS_MAX_STRING_SIZE, "NOPTS");
    ଅନ୍ୟଥା                      snprintf(buf, AV_TS_MAX_STRING_SIZE, "%" PRId64, ts);
    ଫେରନ୍ତୁ buf;
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#define av_ts2str(ts) av_ts_make_string((ଅକ୍ଷର[AV_TS_MAX_STRING_SIZE]){0}, ts)

/**
 * Fill the provided buffer with a string containing a timestamp time
 * representation.
 *
 * @param buf a buffer with size in bytes of at least AV_TS_MAX_STRING_SIZE
 * @param ts the timestamp to represent
 * @param tb the timebase of the timestamp
 * @return the buffer in input
 */
ଅକ୍ଷର *av_ts_make_time_string2(ଅକ୍ଷର *buf, int64_t ts, AVRational tb);

/**
 * Fill the provided buffer with a string containing a timestamp
 * representation.
 *
 * @see av_ts_make_time_string2
 */
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଅକ୍ଷର *av_ts_make_time_string(ଅକ୍ଷର *buf, int64_t ts,
                                           ଅଚଳ AVRational *tb)
{
    ଫେରନ୍ତୁ av_ts_make_time_string2(buf, ts, *tb);
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#define av_ts2timestr(ts, tb) av_ts_make_time_string((ଅକ୍ଷର[AV_TS_MAX_STRING_SIZE]){0}, ts, tb)

#endif /* AVUTIL_TIMESTAMP_H */
