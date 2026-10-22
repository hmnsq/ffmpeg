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

#অন্তর্ভাৱ "config.h"

#অন্তর্ভাৱ <stddef.h>
#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <time.h>
#যদি HAVE_GETTIMEOFDAY
#অন্তর্ভাৱ <sys/time.h>
#endif
#যদি HAVE_UNISTD_H
#অন্তর্ভাৱ <unistd.h>
#endif
#যদি HAVE_WINDOWS_H
#অন্তর্ভাৱ <windows.h>
#endif

#অন্তর্ভাৱ "time.h"
#অন্তর্ভাৱ "error.h"
#অন্তর্ভাৱ "mathematics.h"

int64_t av_gettime(শূন্য)
{
#যদি HAVE_GETTIMEOFDAY
    সংরচনা timeval tv;
    gettimeofday(&tv, রিক্ত);
    ঘূৰাই (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#নোচেদ্যদি HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    GetSystemTimeAsFileTime(&ft);
    t = (int64_t)ft.dw_উপৰেৰ_Date_Time << 32 | ft.dw_নিচেৰ_Date_Time;
    ঘূৰাই t / 10 - 11644473600000000; /* Jan 1, 1601 */
#অন্যথা
    ঘূৰাই -1;
#endif
}

int64_t av_gettime_relative(শূন্য)
{
#যদি HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    যদি (&clock_gettime)
#endif
    {
        সংরচনা timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        ঘূৰাই (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#নোচেদ্যদি defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    ঘূৰাই av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#endif
    ঘূৰাই av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

পূর্ণাঙ্ক av_gettime_relative_is_monotonic(শূন্য)
{
#যদি HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    যদি (!&clock_gettime)
        ঘূৰাই 0;
#endif
    ঘূৰাই 1;
#নোচেদ্যদি defined(_WIN32)
    ঘূৰাই 1;
#অন্যথা
    ঘূৰাই 0;
#endif
}

পূর্ণাঙ্ক av_usleep(unsigned usec)
{
#যদি HAVE_NANOSLEEP
    সংরচনা timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    যেতিয়ালৈ (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    ঘূৰাই 0;
#নোচেদ্যদি HAVE_USLEEP
    ঘূৰাই usleep(usec);
#নোচেদ্যদি HAVE_SLEEP
    Sleep(usec / 1000);
    ঘূৰাই 0;
#অন্যথা
    ঘূৰাই AVERROR(ENOSYS);
#endif
}
