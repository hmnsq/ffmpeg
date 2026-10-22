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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/thread.h"

ਸਥਿਰ ਖਾਲੀ *thread_main(ਖਾਲੀ *arg)
{
    ਪੂਰਨ *flags = arg;

    *flags = av_get_cpu_flags();
    ਵਾਪਸ ਨਿਰਾ;
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਪੂਰਨ cpu_flags1;
    ਪੂਰਨ cpu_flags2;
    ਪੂਰਨ ret;
    pthread_t thread1;
    pthread_t thread2;

    ਜੇ ((ret = pthread_create(&thread1, ਨਿਰਾ, thread_main, &cpu_flags1))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        ਵਾਪਸ 1;
    }
    ਜੇ ((ret = pthread_create(&thread2, ਨਿਰਾ, thread_main, &cpu_flags2))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        ਵਾਪਸ 1;
    }
    pthread_join(thread1, ਨਿਰਾ);
    pthread_join(thread2, ਨਿਰਾ);

    ਜੇ (cpu_flags1 < 0)
        ਵਾਪਸ 2;
    ਜੇ (cpu_flags2 < 0)
        ਵਾਪਸ 2;
    ਜੇ (cpu_flags1 != cpu_flags2)
        ਵਾਪਸ 3;

    ਵਾਪਸ 0;
}
