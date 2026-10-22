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

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/cpu.h"
#अन्तर्भाव "libavutil/thread.h"

स्थिर शून्य *thread_main(शून्य *arg)
{
    पूर्णांक *flags = arg;

    *flags = av_get_cpu_flags();
    परत रिक्त;
}

पूर्णांक main(शून्य)
{
    पूर्णांक cpu_flags1;
    पूर्णांक cpu_flags2;
    पूर्णांक ret;
    pthread_t thread1;
    pthread_t thread2;

    जर ((ret = pthread_create(&thread1, रिक्त, thread_main, &cpu_flags1))) {
        ख_लिखो(मानक_त्रुटि, "pthread_create failed: %s.\n", म_त्रुटि(ret));
        परत 1;
    }
    जर ((ret = pthread_create(&thread2, रिक्त, thread_main, &cpu_flags2))) {
        ख_लिखो(मानक_त्रुटि, "pthread_create failed: %s.\n", म_त्रुटि(ret));
        परत 1;
    }
    pthread_join(thread1, रिक्त);
    pthread_join(thread2, रिक्त);

    जर (cpu_flags1 < 0)
        परत 2;
    जर (cpu_flags2 < 0)
        परत 2;
    जर (cpu_flags1 != cpu_flags2)
        परत 3;

    परत 0;
}
