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

#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/error.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"
#ಅನ್ತರ್ಭಾವ "libavutil/samplefmt.h"

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಅಕ್ಷರ buf[64];

    /* av_get_sample_fmt_name and av_get_sample_fmt round-trip */
    ಬರೆ("Testing name/format round-trip\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = av_get_sample_fmt_name(i);
        ಎಣಿಕೆ AVSampleFormat fmt = av_get_sample_fmt(name);
        ಬರೆ("%2d: name=%-5s roundtrip=%s\n", i, name, fmt == i ? "OK" : "FAIL");
    }

    /* boundary: NONE and out-of-range */
    ಬರೆ("NONE name: %s\n", av_get_sample_fmt_name(AV_SAMPLE_FMT_NONE) == ಖಾಲಿ ? "(null)" : "?");
    ಬರೆ("NB name: %s\n", av_get_sample_fmt_name(AV_SAMPLE_FMT_NB) == ಖಾಲಿ ? "(null)" : "?");
    ಬರೆ("unknown: %d\n", av_get_sample_fmt("nonexistent"));

    /* av_get_bytes_per_sample */
    ಬರೆ("\nTesting av_get_bytes_per_sample()\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AV_SAMPLE_FMT_NB; i++)
        ಬರೆ("%s: %d\n", av_get_sample_fmt_name(i), av_get_ಬೈಟುಗಳು_ಪ್ರತಿ_sample(i));
    ಬರೆ("NONE: %d\n", av_get_ಬೈಟುಗಳು_ಪ್ರತಿ_sample(AV_SAMPLE_FMT_NONE));

    /* av_sample_fmt_is_planar */
    ಬರೆ("\nTesting av_sample_fmt_is_planar()\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AV_SAMPLE_FMT_NB; i++)
        ಬರೆ("%s: %d\n", av_get_sample_fmt_name(i), av_sample_fmt_is_planar(i));
    ಬರೆ("NONE: %d\n", av_sample_fmt_is_planar(AV_SAMPLE_FMT_NONE));

    /* av_get_packed_sample_fmt and av_get_planar_sample_fmt */
    ಬರೆ("\nTesting packed/planar conversions\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        ಎಣಿಕೆ AVSampleFormat packed = av_get_packed_sample_fmt(i);
        ಎಣಿಕೆ AVSampleFormat planar = av_get_planar_sample_fmt(i);
        ಬರೆ("%s: packed=%-4s planar=%s\n",
               av_get_sample_fmt_name(i),
               av_get_sample_fmt_name(packed),
               av_get_sample_fmt_name(planar));
    }

    /* av_get_alt_sample_fmt */
    ಬರೆ("\nTesting av_get_alt_sample_fmt()\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        ಎಣಿಕೆ AVSampleFormat alt_packed = av_get_alt_sample_fmt(i, 0);
        ಎಣಿಕೆ AVSampleFormat alt_planar = av_get_alt_sample_fmt(i, 1);
        ಬರೆ("%s: alt_packed=%-4s alt_planar=%s\n",
               av_get_sample_fmt_name(i),
               av_get_sample_fmt_name(alt_packed),
               av_get_sample_fmt_name(alt_planar));
    }

    /* av_get_sample_fmt_string */
    ಬರೆ("\nTesting av_get_sample_fmt_string()\n");
    av_get_sample_fmt_string(buf, ಗಾತ್ರ(buf), -1);
    ಬರೆ("header: %s\n", buf);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < AV_SAMPLE_FMT_NB; i++) {
        av_get_sample_fmt_string(buf, ಗಾತ್ರ(buf), i);
        ಬರೆ("%s\n", buf);
    }

    /* av_samples_get_buffer_size */
    ಬರೆ("\nTesting av_samples_get_buffer_size()\n");
    {
        ಪೂರ್ಣಾಂಕ linesize;
        ಬರೆ("2ch 1024smp s16: %d\n",
               av_samples_get_ಬಫರ್_ಗಾತ್ರ(ಖಾಲಿ, 2, 1024, AV_SAMPLE_FMT_S16, 1));
        ಬರೆ("2ch 1024smp s16p: %d\n",
               av_samples_get_ಬಫರ್_ಗಾತ್ರ(ಖಾಲಿ, 2, 1024, AV_SAMPLE_FMT_S16P, 1));
        ಬರೆ("6ch 512smp s32: %d\n",
               av_samples_get_ಬಫರ್_ಗಾತ್ರ(ಖಾಲಿ, 6, 512, AV_SAMPLE_FMT_S32, 1));
        av_samples_get_ಬಫರ್_ಗಾತ್ರ(&linesize, 2, 1024, AV_SAMPLE_FMT_S16, 0);
        ಬರೆ("linesize (2ch 1024smp s16 align=0): %d\n", linesize);
        ಬರೆ("0ch error: %d\n",
               av_samples_get_ಬಫರ್_ಗಾತ್ರ(ಖಾಲಿ, 0, 1024, AV_SAMPLE_FMT_S16, 1) < 0);
    }

    /* av_samples_alloc and av_samples_fill_arrays */
    ಬರೆ("\nTesting av_samples_alloc()\n");
    {
        uint8_t *ದತ್ತಾಂಶ[8] = { 0 };
        ಪೂರ್ಣಾಂಕ linesize, ret;

        ret = av_samples_alloc(ದತ್ತಾಂಶ, &linesize, 2, 1024, AV_SAMPLE_FMT_S16, 0);
        ಬರೆ("alloc 2ch s16: ret=%d linesize=%d data[0]=%s\n",
               ret > 0, linesize, ದತ್ತಾಂಶ[0] ? "set" : "null");
        av_freep(&ದತ್ತಾಂಶ[0]);

        ret = av_samples_alloc(ದತ್ತಾಂಶ, &linesize, 2, 1024, AV_SAMPLE_FMT_S16P, 0);
        ಬರೆ("alloc 2ch s16p: ret=%d linesize=%d data[0]=%s data[1]=%s\n",
               ret > 0, linesize,
               ದತ್ತಾಂಶ[0] ? "set" : "null", ದತ್ತಾಂಶ[1] ? "set" : "null");
        av_freep(&ದತ್ತಾಂಶ[0]);
    }

    /* av_samples_alloc_array_and_samples */
    ಬರೆ("\nTesting av_samples_alloc_array_and_samples()\n");
    {
        uint8_t **ದತ್ತಾಂಶ = ಖಾಲಿ;
        ಪೂರ್ಣಾಂಕ linesize, ret;

        ret = av_samples_alloc_array_and_samples(&ದತ್ತಾಂಶ, &linesize, 2, 1024,
                                                  AV_SAMPLE_FMT_S16P, 0);
        ಬರೆ("alloc_array 2ch s16p: ret=%d linesize=%d data[0]=%s data[1]=%s\n",
               ret > 0, linesize,
               ದತ್ತಾಂಶ[0] ? "set" : "null", ದತ್ತಾಂಶ[1] ? "set" : "null");
        ಆದರೆ (ದತ್ತಾಂಶ)
            av_freep(&ದತ್ತಾಂಶ[0]);
        av_freep(&ದತ್ತಾಂಶ);
    }

    /* av_samples_copy */
    ಬರೆ("\nTesting av_samples_copy()\n");
    {
        uint8_t *src[1] = { 0 }, *dst[1] = { 0 };
        ಪೂರ್ಣಾಂಕ linesize;

        av_samples_alloc(src, &linesize, 1, 4, AV_SAMPLE_FMT_S16, 1);
        av_samples_alloc(dst, &linesize, 1, 4, AV_SAMPLE_FMT_S16, 1);
        ಆದರೆ (src[0] && dst[0]) {
            memset(src[0], 0xAB, 8);
            av_samples_copy(dst, src, 0, 0, 4, 1, AV_SAMPLE_FMT_S16);
            ಬರೆ("copy: %s\n", memcmp(src[0], dst[0], 8) == 0 ? "OK" : "FAIL");
        }
        av_freep(&src[0]);
        av_freep(&dst[0]);
    }

    /* OOM paths via av_max_alloc */
    ಬರೆ("\nTesting OOM paths\n");
    {
        uint8_t *ದತ್ತಾಂಶ[8] = { 0 };
        uint8_t **array_ದತ್ತಾಂಶ = ಖಾಲಿ;
        ಪೂರ್ಣಾಂಕ linesize, ret;

        av_max_alloc(1);

        ret = av_samples_alloc(ದತ್ತಾಂಶ, &linesize, 2, 1024, AV_SAMPLE_FMT_S16, 0);
        ಬರೆ("alloc OOM: ret=%d data[0]=%s\n",
               ret == AVERROR(ENOMEM), ದತ್ತಾಂಶ[0] ? "set" : "null");

        ret = av_samples_alloc_array_and_samples(&array_ದತ್ತಾಂಶ, &linesize, 2, 1024,
                                                  AV_SAMPLE_FMT_S16P, 0);
        ಬರೆ("alloc_array OOM: ret=%d data=%s\n",
               ret == AVERROR(ENOMEM), array_ದತ್ತಾಂಶ ? "set" : "null");

        av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
    }

    /* av_samples_set_silence */
    ಬರೆ("\nTesting av_samples_set_silence()\n");
    {
        uint8_t *ದತ್ತಾಂಶ[1] = { 0 };
        ಪೂರ್ಣಾಂಕ linesize;

        av_samples_alloc(ದತ್ತಾಂಶ, &linesize, 1, 4, AV_SAMPLE_FMT_S16, 1);
        ಆದರೆ (ದತ್ತಾಂಶ[0]) {
            memset(ದತ್ತಾಂಶ[0], 0xFF, 8);
            av_samples_ಗಣ_silence(ದತ್ತಾಂಶ, 0, 4, 1, AV_SAMPLE_FMT_S16);
            /* silence for s16 is zero */
            ಪೂರ್ಣಾಂಕ silent = 1;
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 8; i++)
                ಆದರೆ (ದತ್ತಾಂಶ[0][i] != 0) silent = 0;
            ಬರೆ("silence s16: %s\n", silent ? "OK" : "FAIL");
        }
        av_freep(&ದತ್ತಾಂಶ[0]);

        av_samples_alloc(ದತ್ತಾಂಶ, &linesize, 1, 4, AV_SAMPLE_FMT_U8, 1);
        ಆದರೆ (ದತ್ತಾಂಶ[0]) {
            memset(ದತ್ತಾಂಶ[0], 0xFF, 4);
            av_samples_ಗಣ_silence(ದತ್ತಾಂಶ, 0, 4, 1, AV_SAMPLE_FMT_U8);
            /* silence for u8 is 0x80 */
            ಪೂರ್ಣಾಂಕ silent = 1;
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 4; i++)
                ಆದರೆ (ದತ್ತಾಂಶ[0][i] != 0x80) silent = 0;
            ಬರೆ("silence u8: %s\n", silent ? "OK" : "FAIL");
        }
        av_freep(&ದತ್ತಾಂಶ[0]);
    }

    ಹಿಂತಿರುಗಿ 0;
}
