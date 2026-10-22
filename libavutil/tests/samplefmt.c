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

#ضمن <errno.h>
#ضمن <limits.h>
#ضمن <stdio.h>
#ضمن <string.h>

#ضمن "libavutil/error.h"
#ضمن "libavutil/mem.h"
#ضمن "libavutil/samplefmt.h"

صحيح مکيه(فراغ)
{
    حرف buf[64];

    /* av_get_sample_fmt_name and av_get_sample_fmt round-trip */
    لکو("Testing name/format round-trip\n");
    لكل (صحيح i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        ثابت حرف *name = av_get_sample_fmt_name(i);
        تعداد AVSampleFormat fmt = av_get_sample_fmt(name);
        لکو("%2d: name=%-5s roundtrip=%s\n", i, name, fmt == i ? "OK" : "FAIL");
    }

    /* boundary: NONE and out-of-range */
    لکو("NONE name: %s\n", av_get_sample_fmt_name(AV_SAMPLE_FMT_NONE) == عدم ? "(null)" : "?");
    لکو("NB name: %s\n", av_get_sample_fmt_name(AV_SAMPLE_FMT_NB) == عدم ? "(null)" : "?");
    لکو("unknown: %d\n", av_get_sample_fmt("nonexistent"));

    /* av_get_bytes_per_sample */
    لکو("\nTesting av_get_bytes_per_sample()\n");
    لكل (صحيح i = 0; i < AV_SAMPLE_FMT_NB; i++)
        لکو("%s: %d\n", av_get_sample_fmt_name(i), av_get_بائيٽون_في_sample(i));
    لکو("NONE: %d\n", av_get_بائيٽون_في_sample(AV_SAMPLE_FMT_NONE));

    /* av_sample_fmt_is_planar */
    لکو("\nTesting av_sample_fmt_is_planar()\n");
    لكل (صحيح i = 0; i < AV_SAMPLE_FMT_NB; i++)
        لکو("%s: %d\n", av_get_sample_fmt_name(i), av_sample_fmt_is_planar(i));
    لکو("NONE: %d\n", av_sample_fmt_is_planar(AV_SAMPLE_FMT_NONE));

    /* av_get_packed_sample_fmt and av_get_planar_sample_fmt */
    لکو("\nTesting packed/planar conversions\n");
    لكل (صحيح i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        تعداد AVSampleFormat packed = av_get_packed_sample_fmt(i);
        تعداد AVSampleFormat planar = av_get_planar_sample_fmt(i);
        لکو("%s: packed=%-4s planar=%s\n",
               av_get_sample_fmt_name(i),
               av_get_sample_fmt_name(packed),
               av_get_sample_fmt_name(planar));
    }

    /* av_get_alt_sample_fmt */
    لکو("\nTesting av_get_alt_sample_fmt()\n");
    لكل (صحيح i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        تعداد AVSampleFormat alt_packed = av_get_alt_sample_fmt(i, 0);
        تعداد AVSampleFormat alt_planar = av_get_alt_sample_fmt(i, 1);
        لکو("%s: alt_packed=%-4s alt_planar=%s\n",
               av_get_sample_fmt_name(i),
               av_get_sample_fmt_name(alt_packed),
               av_get_sample_fmt_name(alt_planar));
    }

    /* av_get_sample_fmt_string */
    لکو("\nTesting av_get_sample_fmt_string()\n");
    av_get_sample_fmt_string(buf, حجم(buf), -1);
    لکو("header: %s\n", buf);
    لكل (صحيح i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        av_get_sample_fmt_string(buf, حجم(buf), i);
        لکو("%s\n", buf);
    }

    /* av_samples_get_buffer_size */
    لکو("\nTesting av_samples_get_buffer_size()\n");
    {
        صحيح linesize;
        لکو("2ch 1024smp s16: %d\n",
               av_samples_get_بفر_سائيز(عدم, 2, 1024, AV_SAMPLE_FMT_S16, 1));
        لکو("2ch 1024smp s16p: %d\n",
               av_samples_get_بفر_سائيز(عدم, 2, 1024, AV_SAMPLE_FMT_S16P, 1));
        لکو("6ch 512smp s32: %d\n",
               av_samples_get_بفر_سائيز(عدم, 6, 512, AV_SAMPLE_FMT_S32, 1));
        av_samples_get_بفر_سائيز(&linesize, 2, 1024, AV_SAMPLE_FMT_S16, 0);
        لکو("linesize (2ch 1024smp s16 align=0): %d\n", linesize);
        لکو("0ch error: %d\n",
               av_samples_get_بفر_سائيز(عدم, 0, 1024, AV_SAMPLE_FMT_S16, 1) < 0);
    }

    /* av_samples_alloc and av_samples_fill_arrays */
    لکو("\nTesting av_samples_alloc()\n");
    {
        uint8_t *معلومات[8] = { 0 };
        صحيح linesize, ret;

        ret = av_samples_alloc(معلومات, &linesize, 2, 1024, AV_SAMPLE_FMT_S16, 0);
        لکو("alloc 2ch s16: ret=%d linesize=%d data[0]=%s\n",
               ret > 0, linesize, معلومات[0] ? "set" : "null");
        av_freep(&معلومات[0]);

        ret = av_samples_alloc(معلومات, &linesize, 2, 1024, AV_SAMPLE_FMT_S16P, 0);
        لکو("alloc 2ch s16p: ret=%d linesize=%d data[0]=%s data[1]=%s\n",
               ret > 0, linesize,
               معلومات[0] ? "set" : "null", معلومات[1] ? "set" : "null");
        av_freep(&معلومات[0]);
    }

    /* av_samples_alloc_array_and_samples */
    لکو("\nTesting av_samples_alloc_array_and_samples()\n");
    {
        uint8_t **معلومات = عدم;
        صحيح linesize, ret;

        ret = av_samples_alloc_array_and_samples(&معلومات, &linesize, 2, 1024,
                                                  AV_SAMPLE_FMT_S16P, 0);
        لکو("alloc_array 2ch s16p: ret=%d linesize=%d data[0]=%s data[1]=%s\n",
               ret > 0, linesize,
               معلومات[0] ? "set" : "null", معلومات[1] ? "set" : "null");
        إذا (معلومات)
            av_freep(&معلومات[0]);
        av_freep(&معلومات);
    }

    /* av_samples_copy */
    لکو("\nTesting av_samples_copy()\n");
    {
        uint8_t *src[1] = { 0 }, *dst[1] = { 0 };
        صحيح linesize;

        av_samples_alloc(src, &linesize, 1, 4, AV_SAMPLE_FMT_S16, 1);
        av_samples_alloc(dst, &linesize, 1, 4, AV_SAMPLE_FMT_S16, 1);
        إذا (src[0] && dst[0]) {
            memset(src[0], 0xAB, 8);
            av_samples_copy(dst, src, 0, 0, 4, 1, AV_SAMPLE_FMT_S16);
            لکو("copy: %s\n", memcmp(src[0], dst[0], 8) == 0 ? "OK" : "FAIL");
        }
        av_freep(&src[0]);
        av_freep(&dst[0]);
    }

    /* OOM paths via av_max_alloc */
    لکو("\nTesting OOM paths\n");
    {
        uint8_t *معلومات[8] = { 0 };
        uint8_t **array_معلومات = عدم;
        صحيح linesize, ret;

        av_max_alloc(1);

        ret = av_samples_alloc(معلومات, &linesize, 2, 1024, AV_SAMPLE_FMT_S16, 0);
        لکو("alloc OOM: ret=%d data[0]=%s\n",
               ret == AVERROR(ENOMEM), معلومات[0] ? "set" : "null");

        ret = av_samples_alloc_array_and_samples(&array_معلومات, &linesize, 2, 1024,
                                                  AV_SAMPLE_FMT_S16P, 0);
        لکو("alloc_array OOM: ret=%d data=%s\n",
               ret == AVERROR(ENOMEM), array_معلومات ? "set" : "null");

        av_max_alloc(وڌ_کان_وڌ_عدد);
    }

    /* av_samples_set_silence */
    لکو("\nTesting av_samples_set_silence()\n");
    {
        uint8_t *معلومات[1] = { 0 };
        صحيح linesize;

        av_samples_alloc(معلومات, &linesize, 1, 4, AV_SAMPLE_FMT_S16, 1);
        إذا (معلومات[0]) {
            memset(معلومات[0], 0xFF, 8);
            av_samples_سيٽ_silence(معلومات, 0, 4, 1, AV_SAMPLE_FMT_S16);
            /* silence for s16 is zero */
            صحيح silent = 1;
            لكل (صحيح i = 0; i < 8; i++)
                إذا (معلومات[0][i] != 0) silent = 0;
            لکو("silence s16: %s\n", silent ? "OK" : "FAIL");
        }
        av_freep(&معلومات[0]);

        av_samples_alloc(معلومات, &linesize, 1, 4, AV_SAMPLE_FMT_U8, 1);
        إذا (معلومات[0]) {
            memset(معلومات[0], 0xFF, 4);
            av_samples_سيٽ_silence(معلومات, 0, 4, 1, AV_SAMPLE_FMT_U8);
            /* silence for u8 is 0x80 */
            صحيح silent = 1;
            لكل (صحيح i = 0; i < 4; i++)
                إذا (معلومات[0][i] != 0x80) silent = 0;
            لکو("silence u8: %s\n", silent ? "OK" : "FAIL");
        }
        av_freep(&معلومات[0]);
    }

    أرجع 0;
}
