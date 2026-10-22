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

#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "libavutil/cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/thread.h"

ସ୍ଥିର ଶୂନ୍ୟ *thread_main(ଶୂନ୍ୟ *arg)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା *flags = arg;

    *flags = av_get_cpu_flags();
    ଫେରନ୍ତୁ ଖାଲି;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags2;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    pthread_t thread1;
    pthread_t thread2;

    ଯଦି ((ret = pthread_create(&thread1, ଖାଲି, thread_main, &cpu_flags1))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        ଫେରନ୍ତୁ 1;
    }
    ଯଦି ((ret = pthread_create(&thread2, ଖାଲି, thread_main, &cpu_flags2))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        ଫେରନ୍ତୁ 1;
    }
    pthread_join(thread1, ଖାଲି);
    pthread_join(thread2, ଖାଲି);

    ଯଦି (cpu_flags1 < 0)
        ଫେରନ୍ତୁ 2;
    ଯଦି (cpu_flags2 < 0)
        ଫେରନ୍ତୁ 2;
    ଯଦି (cpu_flags1 != cpu_flags2)
        ଫେରନ୍ତୁ 3;

    ଫେରନ୍ତୁ 0;
}
