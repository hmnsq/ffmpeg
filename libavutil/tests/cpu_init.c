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

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/thread.h"

స్థిర శూన్య *thread_main(శూన్య *arg)
{
    పూర్ణాంకం *flags = arg;

    *flags = av_get_cpu_flags();
    తిరిగి ఖాళీ;
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    పూర్ణాంకం cpu_flags1;
    పూర్ణాంకం cpu_flags2;
    పూర్ణాంకం ret;
    pthread_t thread1;
    pthread_t thread2;

    ఒకవేళ ((ret = pthread_create(&thread1, ఖాళీ, thread_main, &cpu_flags1))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        తిరిగి 1;
    }
    ఒకవేళ ((ret = pthread_create(&thread2, ఖాళీ, thread_main, &cpu_flags2))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        తిరిగి 1;
    }
    pthread_join(thread1, ఖాళీ);
    pthread_join(thread2, ఖాళీ);

    ఒకవేళ (cpu_flags1 < 0)
        తిరిగి 2;
    ఒకవేళ (cpu_flags2 < 0)
        తిరిగి 2;
    ఒకవేళ (cpu_flags1 != cpu_flags2)
        తిరిగి 3;

    తిరిగి 0;
}
