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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_TIMESTAMP_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_TIMESTAMP_H

#ಅನ್ತರ್ಭಾವ "avutil.h"

#ಆದರೆ defined(__cplusplus) && !defined(__STDC_FORMAT_MACROS) && !defined(PRId64)
#ದೋಷ missing -D__STDC_FORMAT_MACROS / #ವ್ಯಾಖ್ಯಾನಿಸು __STDC_FORMAT_MACROS
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು AV_TS_MAX_STRING_ಗಾತ್ರ 32

/**
 * Fill the provided buffer with a string containing a timestamp
 * representation.
 *
 * @param buf a buffer with size in bytes of at least AV_TS_MAX_STRING_SIZE
 * @param ts the timestamp to represent
 * @return the buffer in input
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಅಕ್ಷರ *av_ts_make_string(ಅಕ್ಷರ *buf, int64_t ts)
{
    ಆದರೆ (ts == AV_NOPTS_ಮೌಲ್ಯ) snprintf(buf, AV_TS_MAX_STRING_ಗಾತ್ರ, "NOPTS");
    ಇಲ್ಲದಿದ್ದರೆ                      snprintf(buf, AV_TS_MAX_STRING_ಗಾತ್ರ, "%" PRId64, ts);
    ಹಿಂತಿರುಗಿ buf;
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು av_ts2str(ts) av_ts_make_string((ಅಕ್ಷರ[AV_TS_MAX_STRING_ಗಾತ್ರ]){0}, ts)

/**
 * Fill the provided buffer with a string containing a timestamp time
 * representation.
 *
 * @param buf a buffer with size in bytes of at least AV_TS_MAX_STRING_SIZE
 * @param ts the timestamp to represent
 * @param tb the timebase of the timestamp
 * @return the buffer in input
 */
ಅಕ್ಷರ *av_ts_make_ಸಮಯ_string2(ಅಕ್ಷರ *buf, int64_t ts, AVRational tb);

/**
 * Fill the provided buffer with a string containing a timestamp
 * representation.
 *
 * @see av_ts_make_time_string2
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಅಕ್ಷರ *av_ts_make_ಸಮಯ_string(ಅಕ್ಷರ *buf, int64_t ts,
                                           ಸ್ಥಿರಾಂಕ AVRational *tb)
{
    ಹಿಂತಿರುಗಿ av_ts_make_ಸಮಯ_string2(buf, ts, *tb);
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು av_ts2timestr(ts, tb) av_ts_make_ಸಮಯ_string((ಅಕ್ಷರ[AV_TS_MAX_STRING_ಗಾತ್ರ]){0}, ts, tb)

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_TIMESTAMP_H */
