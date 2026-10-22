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

#અન્તર્ભાવ "config.h"

#અન્તર્ભાવ <stddef.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <time.h>
#જો HAVE_GETTIMEOFDAY
#અન્તર્ભાવ <sys/time.h>
#endif
#જો HAVE_UNISTD_H
#અન્તર્ભાવ <unistd.h>
#endif
#જો HAVE_WINDOWS_H
#અન્તર્ભાવ <windows.h>
#endif

#અન્તર્ભાવ "time.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "mathematics.h"

int64_t av_gettime(શૂન્ય)
{
#જો HAVE_GETTIMEOFDAY
    સંરચના timeval tv;
    gettimeofday(&tv, ખાલી);
    પાછા (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#અથવાજો HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    GetSystemTimeAsFileTime(&ft);
    t = (int64_t)ft.dw_ઉપલું_Date_Time << 32 | ft.dw_નીચલું_Date_Time;
    પાછા t / 10 - 11644473600000000; /* Jan 1, 1601 */
#નહીંતર
    પાછા -1;
#endif
}

int64_t av_gettime_relative(શૂન્ય)
{
#જો HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    જો (&clock_gettime)
#endif
    {
        સંરચના timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        પાછા (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#અથવાજો defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    પાછા av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#endif
    પાછા av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

પૂર્ણાંક av_gettime_relative_is_monotonic(શૂન્ય)
{
#જો HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    જો (!&clock_gettime)
        પાછા 0;
#endif
    પાછા 1;
#અથવાજો defined(_WIN32)
    પાછા 1;
#નહીંતર
    પાછા 0;
#endif
}

પૂર્ણાંક av_usleep(unsigned usec)
{
#જો HAVE_NANOSLEEP
    સંરચના timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    જ્યારે (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    પાછા 0;
#અથવાજો HAVE_USLEEP
    પાછા usleep(usec);
#અથવાજો HAVE_SLEEP
    Sleep(usec / 1000);
    પાછા 0;
#નહીંતર
    પાછા AVERROR(ENOSYS);
#endif
}
