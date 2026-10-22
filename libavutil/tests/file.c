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

स्थिर पूर्णाङ्क चरमः_log_level = -1;

स्थिर शून्य log_callback(शून्य *ctx, पूर्णाङ्क level, ध्रुव वर्ण *fmt, va_list तर्काः)
{
    (शून्य)ctx; (शून्य)fmt; (शून्य)तर्काः;
    चरमः_log_level = level;
}

पूर्णाङ्क मुख्यम्(पूर्णाङ्क argc, वर्ण **argv)
{
    ध्रुव वर्ण *मार्गः = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t आकार;

    av_log_समुच्चयः_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    यदि (av_file_map(मार्गः, &buf, &आकार, 0, रिक्त) < 0)
        प्रत्यागम 1;
    av_file_unmap(buf, आकार);
    यदि (आकार == 0)
        प्रत्यागम 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    प्रति (पूर्णाङ्क i = 0; i < 2; i++) {
        चरमः_log_level = -1;
        यदि (av_file_map("no_such_file_xyz", &buf, &आकार, i, रिक्त) >= 0) {
            av_file_unmap(buf, आकार);
            प्रत्यागम 2;
        }
        यदि (चरमः_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, चरमः_log_level);
            प्रत्यागम 3;
        }
    }

    प्रत्यागम 0;
}
