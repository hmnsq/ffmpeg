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

#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <string.h>

#অন্তর্ভাৱ "libavutil/cpu.h"
#অন্তর্ভাৱ "libavutil/thread.h"

স্থির শূন্য *thread_main(শূন্য *arg)
{
    পূর্ণাঙ্ক *flags = arg;

    *flags = av_get_cpu_flags();
    ঘূৰাই রিক্ত;
}

পূর্ণাঙ্ক main(শূন্য)
{
    পূর্ণাঙ্ক cpu_flags1;
    পূর্ণাঙ্ক cpu_flags2;
    পূর্ণাঙ্ক ret;
    pthread_t thread1;
    pthread_t thread2;

    যদি ((ret = pthread_create(&thread1, রিক্ত, thread_main, &cpu_flags1))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        ঘূৰাই 1;
    }
    যদি ((ret = pthread_create(&thread2, রিক্ত, thread_main, &cpu_flags2))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        ঘূৰাই 1;
    }
    pthread_join(thread1, রিক্ত);
    pthread_join(thread2, রিক্ত);

    যদি (cpu_flags1 < 0)
        ঘূৰাই 2;
    যদি (cpu_flags2 < 0)
        ঘূৰাই 2;
    যদি (cpu_flags1 != cpu_flags2)
        ঘূৰাই 3;

    ঘূৰাই 0;
}
