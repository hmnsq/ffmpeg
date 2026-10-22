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
    ಪೂರ್ಣಾಂಕ *flags = arg;

    *flags = av_get_cpu_flags();
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ cpu_flags1;
    ಪೂರ್ಣಾಂಕ cpu_flags2;
    ಪೂರ್ಣಾಂಕ ret;
    pthread_t thread1;
    pthread_t thread2;

    ಆದರೆ ((ret = pthread_create(&thread1, ಖಾಲಿ, thread_main, &cpu_flags1))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        ಹಿಂತಿರುಗಿ 1;
    }
    ಆದರೆ ((ret = pthread_create(&thread2, ಖಾಲಿ, thread_main, &cpu_flags2))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        ಹಿಂತಿರುಗಿ 1;
    }
    pthread_join(thread1, ಖಾಲಿ);
    pthread_join(thread2, ಖಾಲಿ);

    ಆದರೆ (cpu_flags1 < 0)
        ಹಿಂತಿರುಗಿ 2;
    ಆದರೆ (cpu_flags2 < 0)
        ಹಿಂತಿರುಗಿ 2;
    ಆದರೆ (cpu_flags1 != cpu_flags2)
        ಹಿಂತಿರುಗಿ 3;

    ಹಿಂತಿರುಗಿ 0;
}
