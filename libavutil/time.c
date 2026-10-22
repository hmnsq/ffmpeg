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
#اگر_ختم
#اگر HAVE_UNISTD_H
#شامل <unistd.h>
#اگر_ختم
#اگر HAVE_WINDOWS_H
#شامل <windows.h>
#اگر_ختم

#شامل "time.h"
#شامل "error.h"
#شامل "mathematics.h"

int64_t av_gettime(خالی)
{
#اگر HAVE_GETTIMEOFDAY
    ساخت timeval tv;
    gettimeofday(&tv, تہی);
    واپس (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#وگرنہ_اگر HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    Get_System_وقت_As_File_وقت(&ft);
    t = (int64_t)ft.dw_بلند_Date_وقت << 32 | ft.dw_کم_Date_وقت;
    واپس t / 10 - 11644473600000000; /* Jan 1, 1601 */
#ورنہ
    واپس -1;
#اگر_ختم
}

int64_t av_gettime_relative(خالی)
{
#اگر HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#اگر_تعریف_شدہ __APPLE__
    اگر (&clock_gettime)
#اگر_ختم
    {
        ساخت timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        واپس (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#وگرنہ_اگر defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER شمار_2;
    QueryPerformanceFrequency(&freq);
    Query_Performance_شمار(&شمار_2);
    واپس av_rescale(شمار_2.QuadPart, 1000000, freq.QuadPart);
#اگر_ختم
    واپس av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

صحیح av_gettime_relative_is_monotonic(خالی)
{
#اگر HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#اگر_تعریف_شدہ __APPLE__
    اگر (!&clock_gettime)
        واپس 0;
#اگر_ختم
    واپس 1;
#وگرنہ_اگر defined(_WIN32)
    واپس 1;
#ورنہ
    واپس 0;
#اگر_ختم
}

صحیح av_usleep(غیرعلامتی usec)
{
#اگر HAVE_NANOSLEEP
    ساخت timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    جب (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    واپس 0;
#وگرنہ_اگر HAVE_USLEEP
    واپس usleep(usec);
#وگرنہ_اگر HAVE_SLEEP
    Sleep(usec / 1000);
    واپس 0;
#ورنہ
    واپس AVERROR(ENOSYS);
#اگر_ختم
}
