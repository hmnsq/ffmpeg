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

#అన్తర్భావ "config.h"

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <time.h>
#ఒకవేళ HAVE_GETTIMEOFDAY
#అన్తర్భావ <sys/time.h>
#అయితే_ముగింపు
#ఒకవేళ HAVE_UNISTD_H
#అన్తర్భావ <unistd.h>
#అయితే_ముగింపు
#ఒకవేళ HAVE_WINDOWS_H
#అన్తర్భావ <windows.h>
#అయితే_ముగింపు

#అన్తర్భావ "time.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "mathematics.h"

int64_t av_gettime(శూన్య)
{
#ఒకవేళ HAVE_GETTIMEOFDAY
    నిర్మాణం timeval tv;
    gettimeofday(&tv, ఖాళీ);
    తిరిగి (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#లేదావేళ HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    Get_System_సమయం_As_File_సమయం(&ft);
    t = (int64_t)ft.dw_ఎగువ_Date_సమయం << 32 | ft.dw_దిగువ_Date_సమయం;
    తిరిగి t / 10 - 11644473600000000; /* Jan 1, 1601 */
#లేకపోతే
    తిరిగి -1;
#అయితే_ముగింపు
}

int64_t av_gettime_relative(శూన్య)
{
#ఒకవేళ HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#నిర్వచితమైతే __APPLE__
    ఒకవేళ (&clock_gettime)
#అయితే_ముగింపు
    {
        నిర్మాణం timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        తిరిగి (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#లేదావేళ defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    తిరిగి av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#అయితే_ముగింపు
    తిరిగి av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

పూర్ణాంకం av_gettime_relative_is_monotonic(శూన్య)
{
#ఒకవేళ HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#నిర్వచితమైతే __APPLE__
    ఒకవేళ (!&clock_gettime)
        తిరిగి 0;
#అయితే_ముగింపు
    తిరిగి 1;
#లేదావేళ defined(_WIN32)
    తిరిగి 1;
#లేకపోతే
    తిరిగి 0;
#అయితే_ముగింపు
}

పూర్ణాంకం av_usleep(గుర్తులేని usec)
{
#ఒకవేళ HAVE_NANOSLEEP
    నిర్మాణం timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    అయితే (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    తిరిగి 0;
#లేదావేళ HAVE_USLEEP
    తిరిగి usleep(usec);
#లేదావేళ HAVE_SLEEP
    Sleep(usec / 1000);
    తిరిగి 0;
#లేకపోతే
    తిరిగి AVERROR(ENOSYS);
#అయితే_ముగింపు
}
