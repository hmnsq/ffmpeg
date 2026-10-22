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

#अन्तर्भाव <stdarg.h>
#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/file.c"
#अन्तर्भाव "libavutil/log.h"

स्थिर पूर्णांक last_log_level = -1;

स्थिर शून्य log_callback(शून्य *ctx, पूर्णांक level, स्थिरांक अक्षर *fmt, बहु_सूची args)
{
    (शून्य)ctx; (शून्य)fmt; (शून्य)args;
    last_log_level = level;
}

पूर्णांक main(पूर्णांक argc, अक्षर **argv)
{
    स्थिरांक अक्षर *path = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    माप_प्रकार size;

    av_log_set_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    जर (av_file_map(path, &buf, &size, 0, रिक्त) < 0)
        परत 1;
    av_file_unmap(buf, size);
    जर (size == 0)
        परत 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    साठी (पूर्णांक i = 0; i < 2; i++) {
        last_log_level = -1;
        जर (av_file_map("no_such_file_xyz", &buf, &size, i, रिक्त) >= 0) {
            av_file_unmap(buf, size);
            परत 2;
        }
        जर (last_log_level != AV_LOG_ERROR + i) {
            ख_लिखो(मानक_त्रुटि, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, last_log_level);
            परत 3;
        }
    }

    परत 0;
}
