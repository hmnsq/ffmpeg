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

#ضمن "config.h"

#ضمن <stddef.h>
#ضمن <stdint.h>
#ضمن <time.h>
#إذا HAVE_GETTIMEOFDAY
#ضمن <sys/time.h>
#د_که_پای
#إذا HAVE_UNISTD_H
#ضمن <unistd.h>
#د_که_پای
#إذا HAVE_WINDOWS_H
#ضمن <windows.h>
#د_که_پای

#ضمن "time.h"
#ضمن "error.h"
#ضمن "mathematics.h"

int64_t av_gettime(فراغ)
{
#إذا HAVE_GETTIMEOFDAY
    بنية timeval tv;
    gettimeofday(&tv, عدم);
    أرجع (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#وإلاإذا HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    Get_System_وخت_As_File_وخت(&ft);
    t = (int64_t)ft.dw_لوړ_Date_وخت << 32 | ft.dw_ټیټ_Date_وخت;
    أرجع t / 10 - 11644473600000000; /* Jan 1, 1601 */
#وإلا
    أرجع -1;
#د_که_پای
}

int64_t av_gettime_relative(فراغ)
{
#إذا HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#که_تعریف_شوی __APPLE__
    إذا (&clock_gettime)
#د_که_پای
    {
        بنية timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        أرجع (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#وإلاإذا defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    أرجع av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#د_که_پای
    أرجع av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

صحيح av_gettime_relative_is_monotonic(فراغ)
{
#إذا HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#که_تعریف_شوی __APPLE__
    إذا (!&clock_gettime)
        أرجع 0;
#د_که_پای
    أرجع 1;
#وإلاإذا defined(_WIN32)
    أرجع 1;
#وإلا
    أرجع 0;
#د_که_پای
}

صحيح av_usleep(بینښه usec)
{
#إذا HAVE_NANOSLEEP
    بنية timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    طالما (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    أرجع 0;
#وإلاإذا HAVE_USLEEP
    أرجع usleep(usec);
#وإلاإذا HAVE_SLEEP
    Sleep(usec / 1000);
    أرجع 0;
#وإلا
    أرجع AVERROR(ENOSYS);
#د_که_پای
}
