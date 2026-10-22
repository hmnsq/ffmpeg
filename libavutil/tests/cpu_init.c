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

#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "libavutil/cpu.h"
#அந்தர்பாவ "libavutil/thread.h"

நிலையான வெறுமை *thread_main(வெறுமை *arg)
{
    முழு *flags = arg;

    *flags = av_get_cpu_flags();
    திரும்பு வெற்று;
}

முழு முதன்மை(வெறுமை)
{
    முழு cpu_flags1;
    முழு cpu_flags2;
    முழு ret;
    pthread_t thread1;
    pthread_t thread2;

    எனில் ((ret = pthread_create(&thread1, வெற்று, thread_main, &cpu_flags1))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        திரும்பு 1;
    }
    எனில் ((ret = pthread_create(&thread2, வெற்று, thread_main, &cpu_flags2))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        திரும்பு 1;
    }
    pthread_join(thread1, வெற்று);
    pthread_join(thread2, வெற்று);

    எனில் (cpu_flags1 < 0)
        திரும்பு 2;
    எனில் (cpu_flags2 < 0)
        திரும்பு 2;
    எனில் (cpu_flags1 != cpu_flags2)
        திரும்பு 3;

    திரும்பு 0;
}
