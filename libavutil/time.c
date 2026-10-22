/*
 * Copyright (c) 2000-2003 Fabrice Bellard
 *
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

#അന്തര്ഭാവ "config.h"

#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <time.h>
#എങ്കിൽ HAVE_GETTIMEOFDAY
#അന്തര്ഭാവ <sys/time.h>
#endif
#എങ്കിൽ HAVE_UNISTD_H
#അന്തര്ഭാവ <unistd.h>
#endif
#എങ്കിൽ HAVE_WINDOWS_H
#അന്തര്ഭാവ <windows.h>
#endif

#അന്തര്ഭാവ "time.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "mathematics.h"

int64_t av_gettime(ശൂന്യം)
{
#എങ്കിൽ HAVE_GETTIMEOFDAY
    ഘടന timeval tv;
    gettimeofday(&tv, ശൂന്യ);
    തിരികെ (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#അല്ലെങ്കിലെങ്കിൽ HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    GetSystemTimeAsFileTime(&ft);
    t = (int64_t)ft.dw_മുകളിലെ_Date_Time << 32 | ft.dw_താഴെയുള്ള_Date_Time;
    തിരികെ t / 10 - 11644473600000000; /* Jan 1, 1601 */
#അല്ലെങ്കിൽ
    തിരികെ -1;
#endif
}

int64_t av_gettime_relative(ശൂന്യം)
{
#എങ്കിൽ HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    എങ്കിൽ (&clock_gettime)
#endif
    {
        ഘടന timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        തിരികെ (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#അല്ലെങ്കിലെങ്കിൽ defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    തിരികെ av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#endif
    തിരികെ av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

പൂർണ്ണസംഖ്യ av_gettime_relative_is_monotonic(ശൂന്യം)
{
#എങ്കിൽ HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    എങ്കിൽ (!&clock_gettime)
        തിരികെ 0;
#endif
    തിരികെ 1;
#അല്ലെങ്കിലെങ്കിൽ defined(_WIN32)
    തിരികെ 1;
#അല്ലെങ്കിൽ
    തിരികെ 0;
#endif
}

പൂർണ്ണസംഖ്യ av_usleep(unsigned usec)
{
#എങ്കിൽ HAVE_NANOSLEEP
    ഘടന timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    ആകുമ്പോൾ (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    തിരികെ 0;
#അല്ലെങ്കിലെങ്കിൽ HAVE_USLEEP
    തിരികെ usleep(usec);
#അല്ലെങ്കിലെങ്കിൽ HAVE_SLEEP
    Sleep(usec / 1000);
    തിരികെ 0;
#അല്ലെങ്കിൽ
    തിരികെ AVERROR(ENOSYS);
#endif
}
