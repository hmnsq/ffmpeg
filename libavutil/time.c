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

#include "config.h"

#include <stddef.h>
#include <stdint.h>
#include <time.h>
#གལ་ཏེ HAVE_GETTIMEOFDAY
#include <sys/time.h>
#endif
#གལ་ཏེ HAVE_UNISTD_H
#include <unistd.h>
#endif
#གལ་ཏེ HAVE_WINDOWS_H
#include <windows.h>
#endif

#include "time.h"
#include "error.h"
#include "mathematics.h"

int64_t av_gettime(void)
{
#གལ་ཏེ HAVE_GETTIMEOFDAY
    sa_nracanaa timeval tv;
    gettimeofday(&tv, NULL);
    ཕྱིར (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#elif HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    GetSystemTimeAsFileTime(&ft);
    t = (int64_t)ft.dwHighDateTime << 32 | ft.dwLowDateTime;
    ཕྱིར t / 10 - 11644473600000000; /* Jan 1, 1601 */
#དེ་མིན
    ཕྱིར -1;
#endif
}

int64_t av_gettime_relative(void)
{
#གལ་ཏེ HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    གལ་ཏེ (&clock_gettime)
#endif
    {
        sa_nracanaa timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        ཕྱིར (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#elif defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    ཕྱིར av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#endif
    ཕྱིར av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

ཧྲིལ av_gettime_relative_is_monotonic(void)
{
#གལ་ཏེ HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    གལ་ཏེ (!&clock_gettime)
        ཕྱིར 0;
#endif
    ཕྱིར 1;
#elif defined(_WIN32)
    ཕྱིར 1;
#དེ་མིན
    ཕྱིར 0;
#endif
}

ཧྲིལ av_usleep(unsigned usec)
{
#གལ་ཏེ HAVE_NANOSLEEP
    sa_nracanaa timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    སྐབས (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    ཕྱིར 0;
#elif HAVE_USLEEP
    ཕྱིར usleep(usec);
#elif HAVE_SLEEP
    Sleep(usec / 1000);
    ཕྱིར 0;
#དེ་མིན
    ཕྱིར AVERROR(ENOSYS);
#endif
}
