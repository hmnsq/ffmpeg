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

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/samplefmt.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਅੱਖਰ buf[64];

    /* av_get_sample_fmt_name and av_get_sample_fmt round-trip */
    ਲਿਖੋ("Testing name/format round-trip\n");
    ਲਈ (ਪੂਰਨ i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        ਅਚਲ ਅੱਖਰ *name = av_get_sample_fmt_name(i);
        ਗਿਣਤੀ AVSampleFormat fmt = av_get_sample_fmt(name);
        ਲਿਖੋ("%2d: name=%-5s roundtrip=%s\n", i, name, fmt == i ? "OK" : "FAIL");
    }

    /* boundary: NONE and out-of-range */
    ਲਿਖੋ("NONE name: %s\n", av_get_sample_fmt_name(AV_SAMPLE_FMT_NONE) == ਨਿਰਾ ? "(null)" : "?");
    ਲਿਖੋ("NB name: %s\n", av_get_sample_fmt_name(AV_SAMPLE_FMT_NB) == ਨਿਰਾ ? "(null)" : "?");
    ਲਿਖੋ("unknown: %d\n", av_get_sample_fmt("nonexistent"));

    /* av_get_bytes_per_sample */
    ਲਿਖੋ("\nTesting av_get_bytes_per_sample()\n");
    ਲਈ (ਪੂਰਨ i = 0; i < AV_SAMPLE_FMT_NB; i++)
        ਲਿਖੋ("%s: %d\n", av_get_sample_fmt_name(i), av_get_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_sample(i));
    ਲਿਖੋ("NONE: %d\n", av_get_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_sample(AV_SAMPLE_FMT_NONE));

    /* av_sample_fmt_is_planar */
    ਲਿਖੋ("\nTesting av_sample_fmt_is_planar()\n");
    ਲਈ (ਪੂਰਨ i = 0; i < AV_SAMPLE_FMT_NB; i++)
        ਲਿਖੋ("%s: %d\n", av_get_sample_fmt_name(i), av_sample_fmt_is_planar(i));
    ਲਿਖੋ("NONE: %d\n", av_sample_fmt_is_planar(AV_SAMPLE_FMT_NONE));

    /* av_get_packed_sample_fmt and av_get_planar_sample_fmt */
    ਲਿਖੋ("\nTesting packed/planar conversions\n");
    ਲਈ (ਪੂਰਨ i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        ਗਿਣਤੀ AVSampleFormat packed = av_get_packed_sample_fmt(i);
        ਗਿਣਤੀ AVSampleFormat planar = av_get_planar_sample_fmt(i);
        ਲਿਖੋ("%s: packed=%-4s planar=%s\n",
               av_get_sample_fmt_name(i),
               av_get_sample_fmt_name(packed),
               av_get_sample_fmt_name(planar));
    }

    /* av_get_alt_sample_fmt */
    ਲਿਖੋ("\nTesting av_get_alt_sample_fmt()\n");
    ਲਈ (ਪੂਰਨ i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        ਗਿਣਤੀ AVSampleFormat alt_packed = av_get_alt_sample_fmt(i, 0);
        ਗਿਣਤੀ AVSampleFormat alt_planar = av_get_alt_sample_fmt(i, 1);
        ਲਿਖੋ("%s: alt_packed=%-4s alt_planar=%s\n",
               av_get_sample_fmt_name(i),
               av_get_sample_fmt_name(alt_packed),
               av_get_sample_fmt_name(alt_planar));
    }

    /* av_get_sample_fmt_string */
    ਲਿਖੋ("\nTesting av_get_sample_fmt_string()\n");
    av_get_sample_fmt_string(buf, ਆਕਾਰ(buf), -1);
    ਲਿਖੋ("header: %s\n", buf);
    ਲਈ (ਪੂਰਨ i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        av_get_sample_fmt_string(buf, ਆਕਾਰ(buf), i);
        ਲਿਖੋ("%s\n", buf);
    }

    /* av_samples_get_buffer_size */
    ਲਿਖੋ("\nTesting av_samples_get_buffer_size()\n");
    {
        ਪੂਰਨ linesize;
        ਲਿਖੋ("2ch 1024smp s16: %d\n",
               av_samples_get_ਬਫਰ_ਮਾਪ(ਨਿਰਾ, 2, 1024, AV_SAMPLE_FMT_S16, 1));
        ਲਿਖੋ("2ch 1024smp s16p: %d\n",
               av_samples_get_ਬਫਰ_ਮਾਪ(ਨਿਰਾ, 2, 1024, AV_SAMPLE_FMT_S16P, 1));
        ਲਿਖੋ("6ch 512smp s32: %d\n",
               av_samples_get_ਬਫਰ_ਮਾਪ(ਨਿਰਾ, 6, 512, AV_SAMPLE_FMT_S32, 1));
        av_samples_get_ਬਫਰ_ਮਾਪ(&linesize, 2, 1024, AV_SAMPLE_FMT_S16, 0);
        ਲਿਖੋ("linesize (2ch 1024smp s16 align=0): %d\n", linesize);
        ਲਿਖੋ("0ch error: %d\n",
               av_samples_get_ਬਫਰ_ਮਾਪ(ਨਿਰਾ, 0, 1024, AV_SAMPLE_FMT_S16, 1) < 0);
    }

    /* av_samples_alloc and av_samples_fill_arrays */
    ਲਿਖੋ("\nTesting av_samples_alloc()\n");
    {
        uint8_t *ਅੰਕੜੇ[8] = { 0 };
        ਪੂਰਨ linesize, ret;

        ret = av_samples_alloc(ਅੰਕੜੇ, &linesize, 2, 1024, AV_SAMPLE_FMT_S16, 0);
        ਲਿਖੋ("alloc 2ch s16: ret=%d linesize=%d data[0]=%s\n",
               ret > 0, linesize, ਅੰਕੜੇ[0] ? "set" : "null");
        av_freep(&ਅੰਕੜੇ[0]);

        ret = av_samples_alloc(ਅੰਕੜੇ, &linesize, 2, 1024, AV_SAMPLE_FMT_S16P, 0);
        ਲਿਖੋ("alloc 2ch s16p: ret=%d linesize=%d data[0]=%s data[1]=%s\n",
               ret > 0, linesize,
               ਅੰਕੜੇ[0] ? "set" : "null", ਅੰਕੜੇ[1] ? "set" : "null");
        av_freep(&ਅੰਕੜੇ[0]);
    }

    /* av_samples_alloc_array_and_samples */
    ਲਿਖੋ("\nTesting av_samples_alloc_array_and_samples()\n");
    {
        uint8_t **ਅੰਕੜੇ = ਨਿਰਾ;
        ਪੂਰਨ linesize, ret;

        ret = av_samples_alloc_array_and_samples(&ਅੰਕੜੇ, &linesize, 2, 1024,
                                                  AV_SAMPLE_FMT_S16P, 0);
        ਲਿਖੋ("alloc_array 2ch s16p: ret=%d linesize=%d data[0]=%s data[1]=%s\n",
               ret > 0, linesize,
               ਅੰਕੜੇ[0] ? "set" : "null", ਅੰਕੜੇ[1] ? "set" : "null");
        ਜੇ (ਅੰਕੜੇ)
            av_freep(&ਅੰਕੜੇ[0]);
        av_freep(&ਅੰਕੜੇ);
    }

    /* av_samples_copy */
    ਲਿਖੋ("\nTesting av_samples_copy()\n");
    {
        uint8_t *src[1] = { 0 }, *dst[1] = { 0 };
        ਪੂਰਨ linesize;

        av_samples_alloc(src, &linesize, 1, 4, AV_SAMPLE_FMT_S16, 1);
        av_samples_alloc(dst, &linesize, 1, 4, AV_SAMPLE_FMT_S16, 1);
        ਜੇ (src[0] && dst[0]) {
            memset(src[0], 0xAB, 8);
            av_samples_copy(dst, src, 0, 0, 4, 1, AV_SAMPLE_FMT_S16);
            ਲਿਖੋ("copy: %s\n", memcmp(src[0], dst[0], 8) == 0 ? "OK" : "FAIL");
        }
        av_freep(&src[0]);
        av_freep(&dst[0]);
    }

    /* OOM paths via av_max_alloc */
    ਲਿਖੋ("\nTesting OOM paths\n");
    {
        uint8_t *ਅੰਕੜੇ[8] = { 0 };
        uint8_t **array_ਅੰਕੜੇ = ਨਿਰਾ;
        ਪੂਰਨ linesize, ret;

        av_max_alloc(1);

        ret = av_samples_alloc(ਅੰਕੜੇ, &linesize, 2, 1024, AV_SAMPLE_FMT_S16, 0);
        ਲਿਖੋ("alloc OOM: ret=%d data[0]=%s\n",
               ret == AVERROR(ENOMEM), ਅੰਕੜੇ[0] ? "set" : "null");

        ret = av_samples_alloc_array_and_samples(&array_ਅੰਕੜੇ, &linesize, 2, 1024,
                                                  AV_SAMPLE_FMT_S16P, 0);
        ਲਿਖੋ("alloc_array OOM: ret=%d data=%s\n",
               ret == AVERROR(ENOMEM), array_ਅੰਕੜੇ ? "set" : "null");

        av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
    }

    /* av_samples_set_silence */
    ਲਿਖੋ("\nTesting av_samples_set_silence()\n");
    {
        uint8_t *ਅੰਕੜੇ[1] = { 0 };
        ਪੂਰਨ linesize;

        av_samples_alloc(ਅੰਕੜੇ, &linesize, 1, 4, AV_SAMPLE_FMT_S16, 1);
        ਜੇ (ਅੰਕੜੇ[0]) {
            memset(ਅੰਕੜੇ[0], 0xFF, 8);
            av_samples_ਸੈੱਟ_silence(ਅੰਕੜੇ, 0, 4, 1, AV_SAMPLE_FMT_S16);
            /* silence for s16 is zero */
            ਪੂਰਨ silent = 1;
            ਲਈ (ਪੂਰਨ i = 0; i < 8; i++)
                ਜੇ (ਅੰਕੜੇ[0][i] != 0) silent = 0;
            ਲਿਖੋ("silence s16: %s\n", silent ? "OK" : "FAIL");
        }
        av_freep(&ਅੰਕੜੇ[0]);

        av_samples_alloc(ਅੰਕੜੇ, &linesize, 1, 4, AV_SAMPLE_FMT_U8, 1);
        ਜੇ (ਅੰਕੜੇ[0]) {
            memset(ਅੰਕੜੇ[0], 0xFF, 4);
            av_samples_ਸੈੱਟ_silence(ਅੰਕੜੇ, 0, 4, 1, AV_SAMPLE_FMT_U8);
            /* silence for u8 is 0x80 */
            ਪੂਰਨ silent = 1;
            ਲਈ (ਪੂਰਨ i = 0; i < 4; i++)
                ਜੇ (ਅੰਕੜੇ[0][i] != 0x80) silent = 0;
            ਲਿਖੋ("silence u8: %s\n", silent ? "OK" : "FAIL");
        }
        av_freep(&ਅੰਕੜੇ[0]);
    }

    ਵਾਪਸ 0;
}
