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

#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "libavutil/cpu.h"
#અન્તર્ભાવ "libavutil/thread.h"

સ્થિર શૂન્ય *thread_main(શૂન્ય *arg)
{
    પૂર્ણાંક *flags = arg;

    *flags = av_get_cpu_flags();
    પાછા ખાલી;
}

પૂર્ણાંક મુખ્ય(શૂન્ય)
{
    પૂર્ણાંક cpu_flags1;
    પૂર્ણાંક cpu_flags2;
    પૂર્ણાંક ret;
    pthread_t thread1;
    pthread_t thread2;

    જો ((ret = pthread_create(&thread1, ખાલી, thread_main, &cpu_flags1))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        પાછા 1;
    }
    જો ((ret = pthread_create(&thread2, ખાલી, thread_main, &cpu_flags2))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        પાછા 1;
    }
    pthread_join(thread1, ખાલી);
    pthread_join(thread2, ખાલી);

    જો (cpu_flags1 < 0)
        પાછા 2;
    જો (cpu_flags2 < 0)
        પાછા 2;
    જો (cpu_flags1 != cpu_flags2)
        પાછા 3;

    પાછા 0;
}
