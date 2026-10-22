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

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/thread.h"

ಸ್ಥಿರ ಶೂನ್ಯ *thread_main(ಶೂನ್ಯ *arg)
{
    ಪೂರ್ಣಾಙ್ಕ *flags = arg;

    *flags = av_get_cpu_flags();
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ cpu_flags1;
    ಪೂರ್ಣಾಙ್ಕ cpu_flags2;
    ಪೂರ್ಣಾಙ್ಕ ret;
    pthread_t thread1;
    pthread_t thread2;

    ಯದಿ ((ret = pthread_create(&thread1, ರಿಕ್ತ, thread_main, &cpu_flags1))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        ಪ್ರತ್ಯಾಗಮ 1;
    }
    ಯದಿ ((ret = pthread_create(&thread2, ರಿಕ್ತ, thread_main, &cpu_flags2))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        ಪ್ರತ್ಯಾಗಮ 1;
    }
    pthread_join(thread1, ರಿಕ್ತ);
    pthread_join(thread2, ರಿಕ್ತ);

    ಯದಿ (cpu_flags1 < 0)
        ಪ್ರತ್ಯಾಗಮ 2;
    ಯದಿ (cpu_flags2 < 0)
        ಪ್ರತ್ಯಾಗಮ 2;
    ಯದಿ (cpu_flags1 != cpu_flags2)
        ಪ್ರತ್ಯಾಗಮ 3;

    ಪ್ರತ್ಯಾಗಮ 0;
}
