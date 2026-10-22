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

#అన్తర్భావ <errno.h>
#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/error.h"
#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/samplefmt.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    అక్షరం buf[64];

    /* av_get_sample_fmt_name and av_get_sample_fmt round-trip */
    రాయి("Testing name/format round-trip\n");
    కొరకు (పూర్ణాంకం i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        స్థిరరాశి అక్షరం *name = av_get_sample_fmt_name(i);
        గణన AVSampleFormat fmt = av_get_sample_fmt(name);
        రాయి("%2d: name=%-5s roundtrip=%s\n", i, name, fmt == i ? "OK" : "FAIL");
    }

    /* boundary: NONE and out-of-range */
    రాయి("NONE name: %s\n", av_get_sample_fmt_name(AV_SAMPLE_FMT_NONE) == ఖాళీ ? "(null)" : "?");
    రాయి("NB name: %s\n", av_get_sample_fmt_name(AV_SAMPLE_FMT_NB) == ఖాళీ ? "(null)" : "?");
    రాయి("unknown: %d\n", av_get_sample_fmt("nonexistent"));

    /* av_get_bytes_per_sample */
    రాయి("\nTesting av_get_bytes_per_sample()\n");
    కొరకు (పూర్ణాంకం i = 0; i < AV_SAMPLE_FMT_NB; i++)
        రాయి("%s: %d\n", av_get_sample_fmt_name(i), av_get_బైట్లు_చొప్పున_sample(i));
    రాయి("NONE: %d\n", av_get_బైట్లు_చొప్పున_sample(AV_SAMPLE_FMT_NONE));

    /* av_sample_fmt_is_planar */
    రాయి("\nTesting av_sample_fmt_is_planar()\n");
    కొరకు (పూర్ణాంకం i = 0; i < AV_SAMPLE_FMT_NB; i++)
        రాయి("%s: %d\n", av_get_sample_fmt_name(i), av_sample_fmt_is_planar(i));
    రాయి("NONE: %d\n", av_sample_fmt_is_planar(AV_SAMPLE_FMT_NONE));

    /* av_get_packed_sample_fmt and av_get_planar_sample_fmt */
    రాయి("\nTesting packed/planar conversions\n");
    కొరకు (పూర్ణాంకం i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        గణన AVSampleFormat packed = av_get_packed_sample_fmt(i);
        గణన AVSampleFormat planar = av_get_planar_sample_fmt(i);
        రాయి("%s: packed=%-4s planar=%s\n",
               av_get_sample_fmt_name(i),
               av_get_sample_fmt_name(packed),
               av_get_sample_fmt_name(planar));
    }

    /* av_get_alt_sample_fmt */
    రాయి("\nTesting av_get_alt_sample_fmt()\n");
    కొరకు (పూర్ణాంకం i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        గణన AVSampleFormat alt_packed = av_get_alt_sample_fmt(i, 0);
        గణన AVSampleFormat alt_planar = av_get_alt_sample_fmt(i, 1);
        రాయి("%s: alt_packed=%-4s alt_planar=%s\n",
               av_get_sample_fmt_name(i),
               av_get_sample_fmt_name(alt_packed),
               av_get_sample_fmt_name(alt_planar));
    }

    /* av_get_sample_fmt_string */
    రాయి("\nTesting av_get_sample_fmt_string()\n");
    av_get_sample_fmt_string(buf, పరిమాణం(buf), -1);
    రాయి("header: %s\n", buf);
    కొరకు (పూర్ణాంకం i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        av_get_sample_fmt_string(buf, పరిమాణం(buf), i);
        రాయి("%s\n", buf);
    }

    /* av_samples_get_buffer_size */
    రాయి("\nTesting av_samples_get_buffer_size()\n");
    {
        పూర్ణాంకం linesize;
        రాయి("2ch 1024smp s16: %d\n",
               av_samples_get_బఫరు_కొలత(ఖాళీ, 2, 1024, AV_SAMPLE_FMT_S16, 1));
        రాయి("2ch 1024smp s16p: %d\n",
               av_samples_get_బఫరు_కొలత(ఖాళీ, 2, 1024, AV_SAMPLE_FMT_S16P, 1));
        రాయి("6ch 512smp s32: %d\n",
               av_samples_get_బఫరు_కొలత(ఖాళీ, 6, 512, AV_SAMPLE_FMT_S32, 1));
        av_samples_get_బఫరు_కొలత(&linesize, 2, 1024, AV_SAMPLE_FMT_S16, 0);
        రాయి("linesize (2ch 1024smp s16 align=0): %d\n", linesize);
        రాయి("0ch error: %d\n",
               av_samples_get_బఫరు_కొలత(ఖాళీ, 0, 1024, AV_SAMPLE_FMT_S16, 1) < 0);
    }

    /* av_samples_alloc and av_samples_fill_arrays */
    రాయి("\nTesting av_samples_alloc()\n");
    {
        uint8_t *దత్తాంశం[8] = { 0 };
        పూర్ణాంకం linesize, ret;

        ret = av_samples_alloc(దత్తాంశం, &linesize, 2, 1024, AV_SAMPLE_FMT_S16, 0);
        రాయి("alloc 2ch s16: ret=%d linesize=%d data[0]=%s\n",
               ret > 0, linesize, దత్తాంశం[0] ? "set" : "null");
        av_freep(&దత్తాంశం[0]);

        ret = av_samples_alloc(దత్తాంశం, &linesize, 2, 1024, AV_SAMPLE_FMT_S16P, 0);
        రాయి("alloc 2ch s16p: ret=%d linesize=%d data[0]=%s data[1]=%s\n",
               ret > 0, linesize,
               దత్తాంశం[0] ? "set" : "null", దత్తాంశం[1] ? "set" : "null");
        av_freep(&దత్తాంశం[0]);
    }

    /* av_samples_alloc_array_and_samples */
    రాయి("\nTesting av_samples_alloc_array_and_samples()\n");
    {
        uint8_t **దత్తాంశం = ఖాళీ;
        పూర్ణాంకం linesize, ret;

        ret = av_samples_alloc_array_and_samples(&దత్తాంశం, &linesize, 2, 1024,
                                                  AV_SAMPLE_FMT_S16P, 0);
        రాయి("alloc_array 2ch s16p: ret=%d linesize=%d data[0]=%s data[1]=%s\n",
               ret > 0, linesize,
               దత్తాంశం[0] ? "set" : "null", దత్తాంశం[1] ? "set" : "null");
        ఒకవేళ (దత్తాంశం)
            av_freep(&దత్తాంశం[0]);
        av_freep(&దత్తాంశం);
    }

    /* av_samples_copy */
    రాయి("\nTesting av_samples_copy()\n");
    {
        uint8_t *src[1] = { 0 }, *dst[1] = { 0 };
        పూర్ణాంకం linesize;

        av_samples_alloc(src, &linesize, 1, 4, AV_SAMPLE_FMT_S16, 1);
        av_samples_alloc(dst, &linesize, 1, 4, AV_SAMPLE_FMT_S16, 1);
        ఒకవేళ (src[0] && dst[0]) {
            memset(src[0], 0xAB, 8);
            av_samples_copy(dst, src, 0, 0, 4, 1, AV_SAMPLE_FMT_S16);
            రాయి("copy: %s\n", memcmp(src[0], dst[0], 8) == 0 ? "OK" : "FAIL");
        }
        av_freep(&src[0]);
        av_freep(&dst[0]);
    }

    /* OOM paths via av_max_alloc */
    రాయి("\nTesting OOM paths\n");
    {
        uint8_t *దత్తాంశం[8] = { 0 };
        uint8_t **array_దత్తాంశం = ఖాళీ;
        పూర్ణాంకం linesize, ret;

        av_max_alloc(1);

        ret = av_samples_alloc(దత్తాంశం, &linesize, 2, 1024, AV_SAMPLE_FMT_S16, 0);
        రాయి("alloc OOM: ret=%d data[0]=%s\n",
               ret == AVERROR(ENOMEM), దత్తాంశం[0] ? "set" : "null");

        ret = av_samples_alloc_array_and_samples(&array_దత్తాంశం, &linesize, 2, 1024,
                                                  AV_SAMPLE_FMT_S16P, 0);
        రాయి("alloc_array OOM: ret=%d data=%s\n",
               ret == AVERROR(ENOMEM), array_దత్తాంశం ? "set" : "null");

        av_max_alloc(గరిష్ఠ_పూర్ణాంకం);
    }

    /* av_samples_set_silence */
    రాయి("\nTesting av_samples_set_silence()\n");
    {
        uint8_t *దత్తాంశం[1] = { 0 };
        పూర్ణాంకం linesize;

        av_samples_alloc(దత్తాంశం, &linesize, 1, 4, AV_SAMPLE_FMT_S16, 1);
        ఒకవేళ (దత్తాంశం[0]) {
            memset(దత్తాంశం[0], 0xFF, 8);
            av_samples_సమితి_silence(దత్తాంశం, 0, 4, 1, AV_SAMPLE_FMT_S16);
            /* silence for s16 is zero */
            పూర్ణాంకం silent = 1;
            కొరకు (పూర్ణాంకం i = 0; i < 8; i++)
                ఒకవేళ (దత్తాంశం[0][i] != 0) silent = 0;
            రాయి("silence s16: %s\n", silent ? "OK" : "FAIL");
        }
        av_freep(&దత్తాంశం[0]);

        av_samples_alloc(దత్తాంశం, &linesize, 1, 4, AV_SAMPLE_FMT_U8, 1);
        ఒకవేళ (దత్తాంశం[0]) {
            memset(దత్తాంశం[0], 0xFF, 4);
            av_samples_సమితి_silence(దత్తాంశం, 0, 4, 1, AV_SAMPLE_FMT_U8);
            /* silence for u8 is 0x80 */
            పూర్ణాంకం silent = 1;
            కొరకు (పూర్ణాంకం i = 0; i < 4; i++)
                ఒకవేళ (దత్తాంశం[0][i] != 0x80) silent = 0;
            రాయి("silence u8: %s\n", silent ? "OK" : "FAIL");
        }
        av_freep(&దత్తాంశం[0]);
    }

    తిరిగి 0;
}
