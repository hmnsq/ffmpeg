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
#ຖ້າ HAVE_GETTIMEOFDAY
#include <sys/time.h>
#endif
#ຖ້າ HAVE_UNISTD_H
#include <unistd.h>
#endif
#ຖ້າ HAVE_WINDOWS_H
#include <windows.h>
#endif

#include "time.h"
#include "error.h"
#include "mathematics.h"

int64_t av_gettime(void)
{
#ຖ້າ HAVE_GETTIMEOFDAY
    sa_nracanaa timeval tv;
    gettimeofday(&tv, NULL);
    ສົ່ງຄືນ (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#elif HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    GetSystemTimeAsFileTime(&ft);
    t = (int64_t)ft.dwHighDateTime << 32 | ft.dwLowDateTime;
    ສົ່ງຄືນ t / 10 - 11644473600000000; /* Jan 1, 1601 */
#ບໍ່ດັ່ງນັ້ນ
    ສົ່ງຄືນ -1;
#endif
}

int64_t av_gettime_relative(void)
{
#ຖ້າ HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    ຖ້າ (&clock_gettime)
#endif
    {
        sa_nracanaa timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        ສົ່ງຄືນ (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#elif defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    ສົ່ງຄືນ av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#endif
    ສົ່ງຄືນ av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

ຈຳນວນເຕັມ av_gettime_relative_is_monotonic(void)
{
#ຖ້າ HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    ຖ້າ (!&clock_gettime)
        ສົ່ງຄືນ 0;
#endif
    ສົ່ງຄືນ 1;
#elif defined(_WIN32)
    ສົ່ງຄືນ 1;
#ບໍ່ດັ່ງນັ້ນ
    ສົ່ງຄືນ 0;
#endif
}

ຈຳນວນເຕັມ av_usleep(unsigned usec)
{
#ຖ້າ HAVE_NANOSLEEP
    sa_nracanaa timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    ໃນຂະນະທີ່ (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    ສົ່ງຄືນ 0;
#elif HAVE_USLEEP
    ສົ່ງຄືນ usleep(usec);
#elif HAVE_SLEEP
    Sleep(usec / 1000);
    ສົ່ງຄືນ 0;
#ບໍ່ດັ່ງນັ້ນ
    ສົ່ງຄືນ AVERROR(ENOSYS);
#endif
}
