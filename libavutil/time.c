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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଅନ୍ତର୍ଭାଵ <stddef.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <time.h>
#ଯଦି HAVE_GETTIMEOFDAY
#ଅନ୍ତର୍ଭାଵ <sys/time.h>
#endif
#ଯଦି HAVE_UNISTD_H
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#endif
#ଯଦି HAVE_WINDOWS_H
#ଅନ୍ତର୍ଭାଵ <windows.h>
#endif

#ଅନ୍ତର୍ଭାଵ "time.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "mathematics.h"

int64_t av_gettime(ଶୂନ୍ୟ)
{
#ଯଦି HAVE_GETTIMEOFDAY
    ସଂରଚନା timeval tv;
    gettimeofday(&tv, ଖାଲି);
    ଫେରନ୍ତୁ (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#ନଚେତଯଦି HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    GetSystemTimeAsFileTime(&ft);
    t = (int64_t)ft.dw_ଉପର_Date_Time << 32 | ft.dw_ତଳ_Date_Time;
    ଫେରନ୍ତୁ t / 10 - 11644473600000000; /* Jan 1, 1601 */
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ -1;
#endif
}

int64_t av_gettime_relative(ଶୂନ୍ୟ)
{
#ଯଦି HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    ଯଦି (&clock_gettime)
#endif
    {
        ସଂରଚନା timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        ଫେରନ୍ତୁ (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#ନଚେତଯଦି defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    ଫେରନ୍ତୁ av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#endif
    ଫେରନ୍ତୁ av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_gettime_relative_is_monotonic(ଶୂନ୍ୟ)
{
#ଯଦି HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    ଯଦି (!&clock_gettime)
        ଫେରନ୍ତୁ 0;
#endif
    ଫେରନ୍ତୁ 1;
#ନଚେତଯଦି defined(_WIN32)
    ଫେରନ୍ତୁ 1;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ 0;
#endif
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_usleep(unsigned usec)
{
#ଯଦି HAVE_NANOSLEEP
    ସଂରଚନା timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    ଯେତେବେଳେ (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    ଫେରନ୍ତୁ 0;
#ନଚେତଯଦି HAVE_USLEEP
    ଫେରନ୍ତୁ usleep(usec);
#ନଚେତଯଦି HAVE_SLEEP
    Sleep(usec / 1000);
    ଫେରନ୍ତୁ 0;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ AVERROR(ENOSYS);
#endif
}
