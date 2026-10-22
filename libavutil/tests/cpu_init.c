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

#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "libavutil/cpu.h"
#समावेश "libavutil/thread.h"

अटल व्योम *thread_main(व्योम *arg)
{
    पूर्णांक *flags = arg;

    *flags = av_get_cpu_flags();
    वापस शून्य;
}

पूर्णांक मुख्य(व्योम)
{
    पूर्णांक cpu_flags1;
    पूर्णांक cpu_flags2;
    पूर्णांक ret;
    pthread_t thread1;
    pthread_t thread2;

    अगर ((ret = pthread_create(&thread1, शून्य, thread_main, &cpu_flags1))) {
        ख_लिखो(मानक_त्रुटि, "pthread_create failed: %s.\n", म_त्रुटि(ret));
        वापस 1;
    }
    अगर ((ret = pthread_create(&thread2, शून्य, thread_main, &cpu_flags2))) {
        ख_लिखो(मानक_त्रुटि, "pthread_create failed: %s.\n", म_त्रुटि(ret));
        वापस 1;
    }
    pthread_join(thread1, शून्य);
    pthread_join(thread2, शून्य);

    अगर (cpu_flags1 < 0)
        वापस 2;
    अगर (cpu_flags2 < 0)
        वापस 2;
    अगर (cpu_flags1 != cpu_flags2)
        वापस 3;

    वापस 0;
}
