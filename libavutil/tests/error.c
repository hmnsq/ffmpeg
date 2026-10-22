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

#अन्तर्भाव "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
स्थिर ध्रुव संरचना {
    पूर्णाङ्क अङ्कः;
    ध्रुव वर्ण *चिह्नकम्;
} ffmpeg_codes[] = {
#परिभाषय ERROR_चिह्नकम्(संहिता_2, DESC)         { AVERROR_ ## संहिता_2, #CODE },
#परिभाषय ERROR_TAG2(संहिता_2, CODE2, DESC) { AVERROR_ ## संहिता_2, #CODE },
    AVERROR_LIST(ERROR_चिह्नकम्, ERROR_TAG2)
};

स्थिर ध्रुव पूर्णाङ्क errno_codes[] = {
#परिभाषय ERRNO_संहिता(संहिता_2, DESC) AVERROR(संहिता_2),
    STRERROR_LIST(ERRNO_संहिता)
};

पूर्णाङ्क मुख्यम्(शून्य)
{
    वर्ण buf[AV_ERROR_MAX_STRING_आकार];
    पूर्णाङ्क ret = 0;

    प्रति (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        पूर्णाङ्क अङ्कः = ffmpeg_codes[i].अङ्कः;

        यदि (av_strerror(अङ्कः, buf, परिमाण(buf)) < 0) {
            प्रारूप_लिख("%d: lookup failed [%s]\n", अङ्कः, ffmpeg_codes[i].चिह्नकम्);
            ret = 1;
            अनुवर्त;
        }
        प्रारूप_लिख("%d: %s [%s]\n", अङ्कः, buf, ffmpeg_codes[i].चिह्नकम्);
    }

    प्रति (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        यदि (av_strerror(errno_codes[i], buf, परिमाण(buf)) < 0) {
            प्रारूप_लिख("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    प्रत्यागम ret;
}
