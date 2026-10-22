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

#অন্তর্ভাব "config.h"

#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <time.h>
#যদি HAVE_GETTIMEOFDAY
#অন্তর্ভাব <sys/time.h>
#endif
#যদি HAVE_UNISTD_H
#অন্তর্ভাব <unistd.h>
#endif
#যদি HAVE_WINDOWS_H
#অন্তর্ভাব <windows.h>
#endif

#অন্তর্ভাব "time.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "mathematics.h"

int64_t av_gettime(শূন্য)
{
#যদি HAVE_GETTIMEOFDAY
    কাঠামো timeval tv;
    gettimeofday(&tv, ফাঁকা);
    ফেরত (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#নতুবা_যদি HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    GetSystemTimeAsFileTime(&ft);
    t = (int64_t)ft.dw_উপরের_Date_Time << 32 | ft.dw_নিচের_Date_Time;
    ফেরত t / 10 - 11644473600000000; /* Jan 1, 1601 */
#অন্যথা
    ফেরত -1;
#endif
}

int64_t av_gettime_relative(শূন্য)
{
#যদি HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    যদি (&clock_gettime)
#endif
    {
        কাঠামো timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        ফেরত (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#নতুবা_যদি defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER গণক;
    QueryPerformanceFrequency(&freq);
    Query_Performance_গণক(&গণক);
    ফেরত av_rescale(গণক.QuadPart, 1000000, freq.QuadPart);
#endif
    ফেরত av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

পূর্ণসংখ্যা av_gettime_relative_is_monotonic(শূন্য)
{
#যদি HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    যদি (!&clock_gettime)
        ফেরত 0;
#endif
    ফেরত 1;
#নতুবা_যদি defined(_WIN32)
    ফেরত 1;
#অন্যথা
    ফেরত 0;
#endif
}

পূর্ণসংখ্যা av_usleep(unsigned usec)
{
#যদি HAVE_NANOSLEEP
    কাঠামো timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    যখন (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    ফেরত 0;
#নতুবা_যদি HAVE_USLEEP
    ফেরত usleep(usec);
#নতুবা_যদি HAVE_SLEEP
    Sleep(usec / 1000);
    ফেরত 0;
#অন্যথা
    ফেরত AVERROR(ENOSYS);
#endif
}
