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

#अगर_अघोषित AVUTIL_TIMESTAMP_H
#घोषणा AVUTIL_TIMESTAMP_H

#समावेश "avutil.h"

#अगर defined(__cplusplus) && !defined(__STDC_FORMAT_MACROS) && !defined(PRId64)
#त्रुटि missing -D__STDC_FORMAT_MACROS / #घोषणा __STDC_FORMAT_MACROS
#पूर्ण_अगर

#घोषणा AV_TS_MAX_STRING_आकार 32

/**
 * Fill the provided buffer with a string containing a timestamp
 * representation.
 *
 * @param buf a buffer with size in bytes of at least AV_TS_MAX_STRING_SIZE
 * @param ts the timestamp to represent
 * @return the buffer in input
 */
अटल अंतरभूत अक्षर *av_ts_make_string(अक्षर *buf, int64_t ts)
{
    अगर (ts == AV_NOPTS_मूल्य) snprintf(buf, AV_TS_MAX_STRING_आकार, "NOPTS");
    अन्यथा                      snprintf(buf, AV_TS_MAX_STRING_आकार, "%" PRId64, ts);
    वापस buf;
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#घोषणा av_ts2str(ts) av_ts_make_string((अक्षर[AV_TS_MAX_STRING_आकार]){0}, ts)

/**
 * Fill the provided buffer with a string containing a timestamp time
 * representation.
 *
 * @param buf a buffer with size in bytes of at least AV_TS_MAX_STRING_SIZE
 * @param ts the timestamp to represent
 * @param tb the timebase of the timestamp
 * @return the buffer in input
 */
अक्षर *av_ts_make_time_string2(अक्षर *buf, int64_t ts, AVRational tb);

/**
 * Fill the provided buffer with a string containing a timestamp
 * representation.
 *
 * @see av_ts_make_time_string2
 */
अटल अंतरभूत अक्षर *av_ts_make_time_string(अक्षर *buf, int64_t ts,
                                           स्थिर AVRational *tb)
{
    वापस av_ts_make_time_string2(buf, ts, *tb);
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#घोषणा av_ts2timestr(ts, tb) av_ts_make_time_string((अक्षर[AV_TS_MAX_STRING_आकार]){0}, ts, tb)

#पूर्ण_अगर /* AVUTIL_TIMESTAMP_H */
