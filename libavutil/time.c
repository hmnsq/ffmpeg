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

#அந்தர்பாவ "config.h"

#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <time.h>
#எனில் HAVE_GETTIMEOFDAY
#அந்தர்பாவ <sys/time.h>
#endif
#எனில் HAVE_UNISTD_H
#அந்தர்பாவ <unistd.h>
#endif
#எனில் HAVE_WINDOWS_H
#அந்தர்பாவ <windows.h>
#endif

#அந்தர்பாவ "time.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "mathematics.h"

int64_t av_gettime(வெறுமை)
{
#எனில் HAVE_GETTIMEOFDAY
    கட்டமைப்பு timeval tv;
    gettimeofday(&tv, வெற்று);
    திரும்பு (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#அல்லதெனில் HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    GetSystemTimeAsFileTime(&ft);
    t = (int64_t)ft.dw_உயர்வு_Date_Time << 32 | ft.dw_கீழ்_Date_Time;
    திரும்பு t / 10 - 11644473600000000; /* Jan 1, 1601 */
#இல்லையெனில்
    திரும்பு -1;
#endif
}

int64_t av_gettime_relative(வெறுமை)
{
#எனில் HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    எனில் (&clock_gettime)
#endif
    {
        கட்டமைப்பு timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        திரும்பு (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#அல்லதெனில் defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    திரும்பு av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#endif
    திரும்பு av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

முழு av_gettime_relative_is_monotonic(வெறுமை)
{
#எனில் HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    எனில் (!&clock_gettime)
        திரும்பு 0;
#endif
    திரும்பு 1;
#அல்லதெனில் defined(_WIN32)
    திரும்பு 1;
#இல்லையெனில்
    திரும்பு 0;
#endif
}

முழு av_usleep(unsigned usec)
{
#எனில் HAVE_NANOSLEEP
    கட்டமைப்பு timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    போது (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    திரும்பு 0;
#அல்லதெனில் HAVE_USLEEP
    திரும்பு usleep(usec);
#அல்லதெனில் HAVE_SLEEP
    Sleep(usec / 1000);
    திரும்பு 0;
#இல்லையெனில்
    திரும்பு AVERROR(ENOSYS);
#endif
}
