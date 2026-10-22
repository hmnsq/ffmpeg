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

#شامل "config.h"

#شامل <stddef.h>
#شامل <stdint.h>
#شامل <time.h>
#اگر HAVE_GETTIMEOFDAY
#شامل <sys/time.h>
#endif
#اگر HAVE_UNISTD_H
#شامل <unistd.h>
#endif
#اگر HAVE_WINDOWS_H
#شامل <windows.h>
#endif

#شامل "time.h"
#شامل "error.h"
#شامل "mathematics.h"

int64_t av_gettime(تهی)
{
#اگر HAVE_GETTIMEOFDAY
    ساختار timeval tv;
    gettimeofday(&tv, پوچ);
    بازگشت (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#وگرنهاگر HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    GetSystemTimeAsFileTime(&ft);
    t = (int64_t)ft.dw_بالا_Date_Time << 32 | ft.dw_کم_Date_Time;
    بازگشت t / 10 - 11644473600000000; /* Jan 1, 1601 */
#وگرنه
    بازگشت -1;
#endif
}

int64_t av_gettime_relative(تهی)
{
#اگر HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    اگر (&clock_gettime)
#endif
    {
        ساختار timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        بازگشت (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#وگرنهاگر defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    بازگشت av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#endif
    بازگشت av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

صحیح av_gettime_relative_is_monotonic(تهی)
{
#اگر HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    اگر (!&clock_gettime)
        بازگشت 0;
#endif
    بازگشت 1;
#وگرنهاگر defined(_WIN32)
    بازگشت 1;
#وگرنه
    بازگشت 0;
#endif
}

صحیح av_usleep(unsigned usec)
{
#اگر HAVE_NANOSLEEP
    ساختار timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    وقتی (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    بازگشت 0;
#وگرنهاگر HAVE_USLEEP
    بازگشت usleep(usec);
#وگرنهاگر HAVE_SLEEP
    Sleep(usec / 1000);
    بازگشت 0;
#وگرنه
    بازگشت AVERROR(ENOSYS);
#endif
}
