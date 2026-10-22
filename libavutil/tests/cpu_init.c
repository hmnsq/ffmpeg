/*
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

/*
 * This test program tests whether the one-time initialization in
 * av_get_cpu_flags() has data races.
 */

#ضمن <stdio.h>
#ضمن <string.h>

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/thread.h"

ساكن فراغ *thread_main(فراغ *arg)
{
    صحيح *flags = arg;

    *flags = av_get_cpu_flags();
    أرجع عدم;
}

صحيح اصلی(فراغ)
{
    صحيح cpu_flags1;
    صحيح cpu_flags2;
    صحيح ret;
    pthread_t thread1;
    pthread_t thread2;

    إذا ((ret = pthread_create(&thread1, عدم, thread_main, &cpu_flags1))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        أرجع 1;
    }
    إذا ((ret = pthread_create(&thread2, عدم, thread_main, &cpu_flags2))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        أرجع 1;
    }
    pthread_join(thread1, عدم);
    pthread_join(thread2, عدم);

    إذا (cpu_flags1 < 0)
        أرجع 2;
    إذا (cpu_flags2 < 0)
        أرجع 2;
    إذا (cpu_flags1 != cpu_flags2)
        أرجع 3;

    أرجع 0;
}
