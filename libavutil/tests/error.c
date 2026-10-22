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

#समावेश "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
अटल स्थिर काष्ठा {
    पूर्णांक अंक;
    स्थिर अक्षर *tag;
} ffmpeg_codes[] = {
#घोषणा ERROR_TAG(CODE, DESC)         { AVERROR_ ## CODE, #CODE },
#घोषणा ERROR_TAG2(CODE, CODE2, DESC) { AVERROR_ ## CODE, #CODE },
    AVERROR_LIST(ERROR_TAG, ERROR_TAG2)
};

अटल स्थिर पूर्णांक errno_codes[] = {
#घोषणा ERRNO_CODE(CODE, DESC) AVERROR(CODE),
    STRERROR_LIST(ERRNO_CODE)
};

पूर्णांक मुख्य(व्योम)
{
    अक्षर buf[AV_ERROR_MAX_STRING_आकार];
    पूर्णांक ret = 0;

    क्रम (माप_प्रकार i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        पूर्णांक अंक = ffmpeg_codes[i].अंक;

        अगर (av_strerror(अंक, buf, माप(buf)) < 0) {
            म_लिखो("%d: lookup failed [%s]\n", अंक, ffmpeg_codes[i].tag);
            ret = 1;
            जारी;
        }
        म_लिखो("%d: %s [%s]\n", अंक, buf, ffmpeg_codes[i].tag);
    }

    क्रम (माप_प्रकार i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        अगर (av_strerror(errno_codes[i], buf, माप(buf)) < 0) {
            म_लिखो("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    वापस ret;
}
