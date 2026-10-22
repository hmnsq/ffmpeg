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

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <time.h>
#ಆದರೆ HAVE_GETTIMEOFDAY
#ಅನ್ತರ್ಭಾವ <sys/time.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_UNISTD_H
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_WINDOWS_H
#ಅನ್ತರ್ಭಾವ <windows.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "time.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "mathematics.h"

int64_t av_gettime(ಶೂನ್ಯ)
{
#ಆದರೆ HAVE_GETTIMEOFDAY
    ರಚನೆ timeval tv;
    gettimeofday(&tv, ಖಾಲಿ);
    ಹಿಂತಿರುಗಿ (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#ಅಥವಾಆದರೆ HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    Get_System_ಸಮಯ_As_File_ಸಮಯ(&ft);
    t = (int64_t)ft.dw_ಮೇಲಿನ_Date_ಸಮಯ << 32 | ft.dw_ಕೆಳಗಿನ_Date_ಸಮಯ;
    ಹಿಂತಿರುಗಿ t / 10 - 11644473600000000; /* Jan 1, 1601 */
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ -1;
#ಆದರೆ_ಅಂತ್ಯ
}

int64_t av_gettime_relative(ಶೂನ್ಯ)
{
#ಆದರೆ HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __APPLE__
    ಆದರೆ (&clock_gettime)
#ಆದರೆ_ಅಂತ್ಯ
    {
        ರಚನೆ timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        ಹಿಂತಿರುಗಿ (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#ಅಥವಾಆದರೆ defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    ಹಿಂತಿರುಗಿ av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

ಪೂರ್ಣಾಂಕ av_gettime_relative_is_monotonic(ಶೂನ್ಯ)
{
#ಆದರೆ HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __APPLE__
    ಆದರೆ (!&clock_gettime)
        ಹಿಂತಿರುಗಿ 0;
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ 1;
#ಅಥವಾಆದರೆ defined(_WIN32)
    ಹಿಂತಿರುಗಿ 1;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ 0;
#ಆದರೆ_ಅಂತ್ಯ
}

ಪೂರ್ಣಾಂಕ av_usleep(ಚಿಹ್ನೆರಹಿತ usec)
{
#ಆದರೆ HAVE_NANOSLEEP
    ರಚನೆ timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    ಆಗ (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    ಹಿಂತಿರುಗಿ 0;
#ಅಥವಾಆದರೆ HAVE_USLEEP
    ಹಿಂತಿರುಗಿ usleep(usec);
#ಅಥವಾಆದರೆ HAVE_SLEEP
    Sleep(usec / 1000);
    ಹಿಂತಿರುಗಿ 0;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
#ಆದರೆ_ಅಂತ್ಯ
}
