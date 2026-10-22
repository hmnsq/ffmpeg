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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <time.h>
#ਜੇ HAVE_GETTIMEOFDAY
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/time.h>
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_UNISTD_H
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_WINDOWS_H
#ਅਨ੍ਤਰ੍ਭਾਵ <windows.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "time.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mathematics.h"

int64_t av_gettime(ਖਾਲੀ)
{
#ਜੇ HAVE_GETTIMEOFDAY
    ਬਣਤਰ timeval tv;
    gettimeofday(&tv, ਨਿਰਾ);
    ਵਾਪਸ (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#ਜਾਂਜੇ HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    Get_System_ਸਮਾਂ_As_File_ਸਮਾਂ(&ft);
    t = (int64_t)ft.dw_ਉੱਚਾ_Date_ਸਮਾਂ << 32 | ft.dw_ਨੀਵਾਂ_Date_ਸਮਾਂ;
    ਵਾਪਸ t / 10 - 11644473600000000; /* Jan 1, 1601 */
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ -1;
#ਜੇ_ਅੰਤ
}

int64_t av_gettime_relative(ਖਾਲੀ)
{
#ਜੇ HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __APPLE__
    ਜੇ (&clock_gettime)
#ਜੇ_ਅੰਤ
    {
        ਬਣਤਰ timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        ਵਾਪਸ (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#ਜਾਂਜੇ defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    ਵਾਪਸ av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#ਜੇ_ਅੰਤ
    ਵਾਪਸ av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

ਪੂਰਨ av_gettime_relative_is_monotonic(ਖਾਲੀ)
{
#ਜੇ HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __APPLE__
    ਜੇ (!&clock_gettime)
        ਵਾਪਸ 0;
#ਜੇ_ਅੰਤ
    ਵਾਪਸ 1;
#ਜਾਂਜੇ defined(_WIN32)
    ਵਾਪਸ 1;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ 0;
#ਜੇ_ਅੰਤ
}

ਪੂਰਨ av_usleep(ਬਿਨਾਨਿਸ਼ਾਨੀ usec)
{
#ਜੇ HAVE_NANOSLEEP
    ਬਣਤਰ timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    ਜਦੋਂ (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    ਵਾਪਸ 0;
#ਜਾਂਜੇ HAVE_USLEEP
    ਵਾਪਸ usleep(usec);
#ਜਾਂਜੇ HAVE_SLEEP
    Sleep(usec / 1000);
    ਵਾਪਸ 0;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ AVERROR(ENOSYS);
#ਜੇ_ਅੰਤ
}
