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

#అన్తర్భావ "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
స్థిర స్థిరరాశి నిర్మాణం {
    పూర్ణాంకం అంకె;
    స్థిరరాశి అక్షరం *ట్యాగ్;
} ffmpeg_codes[] = {
#నిర్వచించు ERROR_ట్యాగ్(సంకేతం_3, DESC)         { AVERROR_ ## సంకేతం_3, #CODE },
#నిర్వచించు ERROR_TAG2(సంకేతం_3, CODE2, DESC) { AVERROR_ ## సంకేతం_3, #CODE },
    AVERROR_LIST(ERROR_ట్యాగ్, ERROR_TAG2)
};

స్థిర స్థిరరాశి పూర్ణాంకం errno_codes[] = {
#నిర్వచించు ERRNO_సంకేతం(సంకేతం_3, DESC) AVERROR(సంకేతం_3),
    STRERROR_LIST(ERRNO_సంకేతం)
};

పూర్ణాంకం ప్రధాన(శూన్య)
{
    అక్షరం buf[AV_ERROR_MAX_STRING_కొలత];
    పూర్ణాంకం ret = 0;

    కొరకు (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        పూర్ణాంకం అంకె = ffmpeg_codes[i].అంకె;

        ఒకవేళ (av_strerror(అంకె, buf, పరిమాణం(buf)) < 0) {
            రాయి("%d: lookup failed [%s]\n", అంకె, ffmpeg_codes[i].ట్యాగ్);
            ret = 1;
            కొనసాగు;
        }
        రాయి("%d: %s [%s]\n", అంకె, buf, ffmpeg_codes[i].ట్యాగ్);
    }

    కొరకు (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        ఒకవేళ (av_strerror(errno_codes[i], buf, పరిమాణం(buf)) < 0) {
            రాయి("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    తిరిగి ret;
}
