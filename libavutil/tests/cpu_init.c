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

#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "libavutil/cpu.h"
#അന്തര്ഭാവ "libavutil/thread.h"

സ്ഥിതം ശൂന്യം *thread_main(ശൂന്യം *arg)
{
    പൂർണ്ണസംഖ്യ *flags = arg;

    *flags = av_get_cpu_flags();
    തിരികെ ശൂന്യ;
}

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    പൂർണ്ണസംഖ്യ cpu_flags1;
    പൂർണ്ണസംഖ്യ cpu_flags2;
    പൂർണ്ണസംഖ്യ ret;
    pthread_t thread1;
    pthread_t thread2;

    എങ്കിൽ ((ret = pthread_create(&thread1, ശൂന്യ, thread_main, &cpu_flags1))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        തിരികെ 1;
    }
    എങ്കിൽ ((ret = pthread_create(&thread2, ശൂന്യ, thread_main, &cpu_flags2))) {
        fprintf(stderr, "pthread_create failed: %s.\n", strerror(ret));
        തിരികെ 1;
    }
    pthread_join(thread1, ശൂന്യ);
    pthread_join(thread2, ശൂന്യ);

    എങ്കിൽ (cpu_flags1 < 0)
        തിരികെ 2;
    എങ്കിൽ (cpu_flags2 < 0)
        തിരികെ 2;
    എങ്കിൽ (cpu_flags1 != cpu_flags2)
        തിരികെ 3;

    തിരികെ 0;
}
