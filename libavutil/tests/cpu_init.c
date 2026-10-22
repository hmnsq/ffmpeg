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

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "libavutil/cpu.h"
#অন্তর্ভাব "libavutil/thread.h"

স্থির শূন্য *thread_main(শূন্য *arg)
{
    পূর্ণসংখ্যা *flags = arg;

    *flags = av_get_cpu_flags();
    ফেরত ফাঁকা;
}

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    পূর্ণসংখ্যা cpu_flags1;
    পূর্ণসংখ্যা cpu_flags2;
    পূর্ণসংখ্যা ret;
    pthread_t thread1;
    pthread_t thread2;

    যদি ((ret = pthread_create(&thread1, ফাঁকা, thread_main, &cpu_flags1))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        ফেরত 1;
    }
    যদি ((ret = pthread_create(&thread2, ফাঁকা, thread_main, &cpu_flags2))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        ফেরত 1;
    }
    pthread_join(thread1, ফাঁকা);
    pthread_join(thread2, ফাঁকা);

    যদি (cpu_flags1 < 0)
        ফেরত 2;
    যদি (cpu_flags2 < 0)
        ফেরত 2;
    যদি (cpu_flags1 != cpu_flags2)
        ফেরত 3;

    ফেরত 0;
}
