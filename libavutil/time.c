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

#अन्तर्भाव "config.h"

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <time.h>
#जर HAVE_GETTIMEOFDAY
#अन्तर्भाव <sys/time.h>
#endif
#जर HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#जर HAVE_WINDOWS_H
#अन्तर्भाव <windows.h>
#endif

#अन्तर्भाव "time.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "mathematics.h"

int64_t av_gettime(शून्य)
{
#जर HAVE_GETTIMEOFDAY
    संरचना timeval tv;
    gettimeofday(&tv, रिक्त);
    परत (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
#किंवाजर HAVE_GETSYSTEMTIMEASFILETIME
    FILETIME ft;
    int64_t t;
    GetSystemTimeAsFileTime(&ft);
    t = (int64_t)ft.dw_वरचा_Date_Time << 32 | ft.dw_खालचा_Date_Time;
    परत t / 10 - 11644473600000000; /* Jan 1, 1601 */
#अन्यथा
    परत -1;
#endif
}

int64_t av_gettime_relative(शून्य)
{
#जर HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    जर (&clock_gettime)
#endif
    {
        संरचना timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        परत (int64_t)ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
#किंवाजर defined(_WIN32)
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    परत av_rescale(counter.QuadPart, 1000000, freq.QuadPart);
#endif
    परत av_gettime() + 42 * 60 * 60 * INT64_C(1000000);
}

पूर्णांक av_gettime_relative_is_monotonic(शून्य)
{
#जर HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    जर (!&clock_gettime)
        परत 0;
#endif
    परत 1;
#किंवाजर defined(_WIN32)
    परत 1;
#अन्यथा
    परत 0;
#endif
}

पूर्णांक av_usleep(अचिन्हित usec)
{
#जर HAVE_NANOSLEEP
    संरचना timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    पर्यंत (nanosleep(&ts, &ts) < 0 && त्रुटि_सं == EINTR);
    परत 0;
#किंवाजर HAVE_USLEEP
    परत usleep(usec);
#किंवाजर HAVE_SLEEP
    Sleep(usec / 1000);
    परत 0;
#अन्यथा
    परत AVERROR(ENOSYS);
#endif
}
