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

#समावेश "config.h"

#समावेश <stddef.h>
#समावेश <stdint.h>
#समावेश <time.h>
#अगर HAVE_GETTIMEOFDAY
#समावेश <sys/time.h>
#पूर्ण_अगर
#अगर HAVE_UNISTD_H
#समावेश <unistd.h>
#पूर्ण_अगर
#अगर HAVE_WINDOWS_H
#समावेश <windows.h>
#पूर्ण_अगर

#समावेश "time.h"
#समावेश "error.h"
#समावेश "mathematics.h"

int64_t av_gettime(व्योम)
{
#अगर HAVE_GETTIMEOFDAY
    काष्ठा timeval tv;
    gettimeofday(&tv, शून्य);
    वापस (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#या_अगर HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    GetSystemTimeAsFileTime(&ft);
    t = (int64_t)ft.dw_ऊपरी_Date_Time << 32 | ft.dw_निचला_Date_Time;
    वापस t / 10 - 11644473600000000; /* Jan 1, 1601 */
#अन्यथा
    वापस -1;
#पूर्ण_अगर
}

int64_t av_gettime_relative(व्योम)
{
#अगर HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#अगर_घोषित __APPLE__
    अगर (&clock_gettime)
#पूर्ण_अगर
    {
        काष्ठा timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        वापस (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#या_अगर defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER गणक;
    QueryPerformanceFrequency(&freq);
    Query_Performance_गणक(&गणक);
    वापस av_rescale(गणक.QuadPart, 1000000, freq.QuadPart);
#पूर्ण_अगर
    वापस av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

पूर्णांक av_gettime_relative_is_monotonic(व्योम)
{
#अगर HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#अगर_घोषित __APPLE__
    अगर (!&clock_gettime)
        वापस 0;
#पूर्ण_अगर
    वापस 1;
#या_अगर defined(_WIN32)
    वापस 1;
#अन्यथा
    वापस 0;
#पूर्ण_अगर
}

पूर्णांक av_usleep(अचिन्हित usec)
{
#अगर HAVE_NANOSLEEP
    काष्ठा timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    जबतक (nanosleep(&ts, &ts) < 0 && त्रुटि_सं == EINTR);
    वापस 0;
#या_अगर HAVE_USLEEP
    वापस usleep(usec);
#या_अगर HAVE_SLEEP
    Sleep(usec / 1000);
    वापस 0;
#अन्यथा
    वापस AVERROR(ENOSYS);
#पूर्ण_अगर
}
