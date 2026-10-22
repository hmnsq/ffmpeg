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
#если HAVE_GETTIMEOFDAY
#include <sys/time.h>
#endif
#если HAVE_UNISTD_H
#include <unistd.h>
#endif
#если HAVE_WINDOWS_H
#include <windows.h>
#endif

#include "time.h"
#include "error.h"
#include "mathematics.h"

int64_t av_gettime(void)
{
#если HAVE_GETTIMEOFDAY
    struct timeval tv;
    gettimeofday(&tv, NULL);
    вернуть (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#elif HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    GetSystemTimeAsFileTime(&ft);
    t = (int64_t)ft.dwHighDateTime << 32 | ft.dwLowDateTime;
    вернуть t / 10 - 11644473600000000; /* Jan 1, 1601 */
#иначе
    вернуть -1;
#endif
}

int64_t av_gettime_relative(void)
{
#если HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    если (&clock_gettime)
#endif
    {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        вернуть (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#elif defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    вернуть av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#endif
    вернуть av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

целое av_gettime_relative_is_monotonic(void)
{
#если HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    если (!&clock_gettime)
        вернуть 0;
#endif
    вернуть 1;
#elif defined(_WIN32)
    вернуть 1;
#иначе
    вернуть 0;
#endif
}

целое av_usleep(unsigned usec)
{
#если HAVE_NANOSLEEP
    struct timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    пока (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    вернуть 0;
#elif HAVE_USLEEP
    вернуть usleep(usec);
#elif HAVE_SLEEP
    Sleep(usec / 1000);
    вернуть 0;
#иначе
    вернуть AVERROR(ENOSYS);
#endif
}
