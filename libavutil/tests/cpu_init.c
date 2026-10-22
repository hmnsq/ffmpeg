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

#شامل <stdio.h>
#شامل <string.h>

#شامل "libavutil/cpu.h"
#شامل "libavutil/thread.h"

ساکن خالی *thread_main(خالی *arg)
{
    صحیح *flags = arg;

    *flags = av_get_cpu_flags();
    واپس تہی;
}

صحیح مین(خالی)
{
    صحیح cpu_flags1;
    صحیح cpu_flags2;
    صحیح ret;
    pthread_t thread1;
    pthread_t thread2;

    اگر ((ret = pthread_create(&thread1, تہی, thread_main, &cpu_flags1))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        واپس 1;
    }
    اگر ((ret = pthread_create(&thread2, تہی, thread_main, &cpu_flags2))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        واپس 1;
    }
    pthread_join(thread1, تہی);
    pthread_join(thread2, تہی);

    اگر (cpu_flags1 < 0)
        واپس 2;
    اگر (cpu_flags2 < 0)
        واپس 2;
    اگر (cpu_flags1 != cpu_flags2)
        واپس 3;

    واپس 0;
}
