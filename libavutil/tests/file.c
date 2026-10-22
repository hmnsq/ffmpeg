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

#समावेश <stdarg.h>
#समावेश <stdio.h>

#समावेश "libavutil/file.c"
#समावेश "libavutil/log.h"

अटल पूर्णांक last_log_level = -1;

अटल व्योम log_callback(व्योम *ctx, पूर्णांक level, स्थिर अक्षर *fmt, बहु_सूची args)
{
    (व्योम)ctx; (व्योम)fmt; (व्योम)args;
    last_log_level = level;
}

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
{
    स्थिर अक्षर *path = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    माप_प्रकार आकार;

    av_log_set_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    अगर (av_file_map(path, &buf, &आकार, 0, शून्य) < 0)
        वापस 1;
    av_file_unmap(buf, आकार);
    अगर (आकार == 0)
        वापस 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    क्रम (पूर्णांक i = 0; i < 2; i++) {
        last_log_level = -1;
        अगर (av_file_map("no_such_file_xyz", &buf, &आकार, i, शून्य) >= 0) {
            av_file_unmap(buf, आकार);
            वापस 2;
        }
        अगर (last_log_level != AV_LOG_ERROR + i) {
            ख_लिखो(मानक_त्रुटि, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, last_log_level);
            वापस 3;
        }
    }

    वापस 0;
}
