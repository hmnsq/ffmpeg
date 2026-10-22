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
#جيڪڏهن_پورو
#إذا HAVE_UNISTD_H
#ضمن <unistd.h>
#جيڪڏهن_پورو
#إذا HAVE_WINDOWS_H
#ضمن <windows.h>
#جيڪڏهن_پورو

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
    Get_System_وقت_As_File_وقت(&ft);
    t = (int64_t)ft.dw_مٿاهون_Date_وقت << 32 | ft.dw_هيٺيون_Date_وقت;
    أرجع t / 10 - 11644473600000000; /* Jan 1, 1601 */
#وإلا
    أرجع -1;
#جيڪڏهن_پورو
}

int64_t av_gettime_relative(فراغ)
{
#إذا HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#جيڪڏهن_وصف_ٿيل __APPLE__
    إذا (&clock_gettime)
#جيڪڏهن_پورو
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
#جيڪڏهن_پورو
    أرجع av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

صحيح av_gettime_relative_is_monotonic(فراغ)
{
#إذا HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#جيڪڏهن_وصف_ٿيل __APPLE__
    إذا (!&clock_gettime)
        أرجع 0;
#جيڪڏهن_پورو
    أرجع 1;
#وإلاإذا defined(_WIN32)
    أرجع 1;
#وإلا
    أرجع 0;
#جيڪڏهن_پورو
}

صحيح av_usleep(بنانشان usec)
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
#جيڪڏهن_پورو
}
