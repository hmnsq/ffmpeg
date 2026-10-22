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

#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "samplefmt.h"

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SampleFmtInfo {
    ಅಕ್ಷರ name[8];
    ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು;
    ಪೂರ್ಣಾಂಕ planar;
    ಎಣಿಕೆ AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
    [AV_SAMPLE_FMT_U8]   = { .name =   "u8", .ಬಿಟ್ಟುಗಳು =  8, .planar = 0, .altform = AV_SAMPLE_FMT_U8P  },
    [AV_SAMPLE_FMT_S16]  = { .name =  "s16", .ಬಿಟ್ಟುಗಳು = 16, .planar = 0, .altform = AV_SAMPLE_FMT_S16P },
    [AV_SAMPLE_FMT_S32]  = { .name =  "s32", .ಬಿಟ್ಟುಗಳು = 32, .planar = 0, .altform = AV_SAMPLE_FMT_S32P },
    [AV_SAMPLE_FMT_S64]  = { .name =  "s64", .ಬಿಟ್ಟುಗಳು = 64, .planar = 0, .altform = AV_SAMPLE_FMT_S64P },
    [AV_SAMPLE_FMT_FLT]  = { .name =  "flt", .ಬಿಟ್ಟುಗಳು = 32, .planar = 0, .altform = AV_SAMPLE_FMT_FLTP },
    [AV_SAMPLE_FMT_DBL]  = { .name =  "dbl", .ಬಿಟ್ಟುಗಳು = 64, .planar = 0, .altform = AV_SAMPLE_FMT_DBLP },
    [AV_SAMPLE_FMT_U8P]  = { .name =  "u8p", .ಬಿಟ್ಟುಗಳು =  8, .planar = 1, .altform = AV_SAMPLE_FMT_U8   },
    [AV_SAMPLE_FMT_S16P] = { .name = "s16p", .ಬಿಟ್ಟುಗಳು = 16, .planar = 1, .altform = AV_SAMPLE_FMT_S16  },
    [AV_SAMPLE_FMT_S32P] = { .name = "s32p", .ಬಿಟ್ಟುಗಳು = 32, .planar = 1, .altform = AV_SAMPLE_FMT_S32  },
    [AV_SAMPLE_FMT_S64P] = { .name = "s64p", .ಬಿಟ್ಟುಗಳು = 64, .planar = 1, .altform = AV_SAMPLE_FMT_S64  },
    [AV_SAMPLE_FMT_FLTP] = { .name = "fltp", .ಬಿಟ್ಟುಗಳು = 32, .planar = 1, .altform = AV_SAMPLE_FMT_FLT  },
    [AV_SAMPLE_FMT_DBLP] = { .name = "dblp", .ಬಿಟ್ಟುಗಳು = 64, .planar = 1, .altform = AV_SAMPLE_FMT_DBL  },
    [AV_SAMPLE_FMT_DSD]  = { .name =  "dsd", .ಬಿಟ್ಟುಗಳು =  8, .planar = 0, .altform = AV_SAMPLE_FMT_DSD  },
};

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_get_sample_fmt_name(ಎಣಿಕೆ AVSampleFormat sample_fmt)
{
    ಆದರೆ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ sample_fmt_info[sample_fmt].name;
}

ಎಣಿಕೆ AVSampleFormat av_get_sample_fmt(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        ಆದರೆ (!strcmp(sample_fmt_info[i].name, name))
            ಹಿಂತಿರುಗಿ i;
    ಹಿಂತಿರುಗಿ AV_SAMPLE_FMT_NONE;
}

ಎಣಿಕೆ AVSampleFormat av_get_alt_sample_fmt(ಎಣಿಕೆ AVSampleFormat sample_fmt, ಪೂರ್ಣಾಂಕ planar)
{
    ಆದರೆ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ಹಿಂತಿರುಗಿ AV_SAMPLE_FMT_NONE;
    ಆದರೆ (sample_fmt_info[sample_fmt].planar == planar)
        ಹಿಂತಿರುಗಿ sample_fmt;
    ಹಿಂತಿರುಗಿ sample_fmt_info[sample_fmt].altform;
}

ಎಣಿಕೆ AVSampleFormat av_get_packed_sample_fmt(ಎಣಿಕೆ AVSampleFormat sample_fmt)
{
    ಆದರೆ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ಹಿಂತಿರುಗಿ AV_SAMPLE_FMT_NONE;
    ಆದರೆ (sample_fmt_info[sample_fmt].planar)
        ಹಿಂತಿರುಗಿ sample_fmt_info[sample_fmt].altform;
    ಹಿಂತಿರುಗಿ sample_fmt;
}

ಎಣಿಕೆ AVSampleFormat av_get_planar_sample_fmt(ಎಣಿಕೆ AVSampleFormat sample_fmt)
{
    ಆದರೆ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ಹಿಂತಿರುಗಿ AV_SAMPLE_FMT_NONE;
    ಆದರೆ (sample_fmt_info[sample_fmt].planar)
        ಹಿಂತಿರುಗಿ sample_fmt;
    ಹಿಂತಿರುಗಿ sample_fmt_info[sample_fmt].altform;
}

ಅಕ್ಷರ *av_get_sample_fmt_string (ಅಕ್ಷರ *buf, ಪೂರ್ಣಾಂಕ buf_ಗಾತ್ರ, ಎಣಿಕೆ AVSampleFormat sample_fmt)
{
    /* print header */
    ಆದರೆ (sample_fmt < 0)
        snprintf(buf, buf_ಗಾತ್ರ, "name  " " depth");
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_ಗಾತ್ರ, "%-6s" "   %2d ", info.name, info.ಬಿಟ್ಟುಗಳು);
    }

    ಹಿಂತಿರುಗಿ buf;
}

ಪೂರ್ಣಾಂಕ av_get_ಬೈಟುಗಳು_ಪ್ರತಿ_sample(ಎಣಿಕೆ AVSampleFormat sample_fmt)
{
     ಹಿಂತಿರುಗಿ sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].ಬಿಟ್ಟುಗಳು >> 3;
}

ಪೂರ್ಣಾಂಕ av_sample_fmt_is_planar(ಎಣಿಕೆ AVSampleFormat sample_fmt)
{
     ಆದರೆ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         ಹಿಂತಿರುಗಿ 0;
     ಹಿಂತಿರುಗಿ sample_fmt_info[sample_fmt].planar;
}

ಪೂರ್ಣಾಂಕ av_samples_get_ಬಫರ್_ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ *linesize, ಪೂರ್ಣಾಂಕ nb_channels, ಪೂರ್ಣಾಂಕ nb_samples,
                               ಎಣಿಕೆ AVSampleFormat sample_fmt, ಪೂರ್ಣಾಂಕ align)
{
    ಪೂರ್ಣಾಂಕ ಸಾಲು_ಗಾತ್ರ;
    ಪೂರ್ಣಾಂಕ sample_ಗಾತ್ರ = av_get_ಬೈಟುಗಳು_ಪ್ರತಿ_sample(sample_fmt);
    ಪೂರ್ಣಾಂಕ planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    ಆದರೆ (!sample_ಗಾತ್ರ || nb_samples <= 0 || nb_channels <= 0)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    ಆದರೆ (!align) {
        ಆದರೆ (nb_samples > ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ - 31)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    ಆದರೆ (nb_channels > ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ / align ||
        (int64_t)nb_channels * nb_samples > (ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ - (align * nb_channels)) / sample_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಸಾಲು_ಗಾತ್ರ = planar ? FFALIGN(nb_samples * sample_ಗಾತ್ರ,               align) :
                         FFALIGN(nb_samples * sample_ಗಾತ್ರ * nb_channels, align);
    ಆದರೆ (linesize)
        *linesize = ಸಾಲು_ಗಾತ್ರ;

    ಹಿಂತಿರುಗಿ planar ? ಸಾಲು_ಗಾತ್ರ * nb_channels : ಸಾಲು_ಗಾತ್ರ;
}

ಪೂರ್ಣಾಂಕ av_samples_fill_arrays(uint8_t **audio_ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ *linesize,
                           ಸ್ಥಿರಾಂಕ uint8_t *buf, ಪೂರ್ಣಾಂಕ nb_channels, ಪೂರ್ಣಾಂಕ nb_samples,
                           ಎಣಿಕೆ AVSampleFormat sample_fmt, ಪೂರ್ಣಾಂಕ align)
{
    ಪೂರ್ಣಾಂಕ ch, planar, buf_ಗಾತ್ರ, ಸಾಲು_ಗಾತ್ರ;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_ಗಾತ್ರ = av_samples_get_ಬಫರ್_ಗಾತ್ರ(&ಸಾಲು_ಗಾತ್ರ, nb_channels, nb_samples,
                                          sample_fmt, align);
    ಆದರೆ (buf_ಗಾತ್ರ < 0)
        ಹಿಂತಿರುಗಿ buf_ಗಾತ್ರ;

    ಆದರೆ (linesize)
        *linesize = ಸಾಲು_ಗಾತ್ರ;

    memset(audio_ದತ್ತಾಂಶ, 0, planar
                          ? ಗಾತ್ರ(*audio_ದತ್ತಾಂಶ) * nb_channels
                          : ಗಾತ್ರ(*audio_ದತ್ತಾಂಶ));

    ಆದರೆ (!buf)
        ಹಿಂತಿರುಗಿ buf_ಗಾತ್ರ;

    audio_ದತ್ತಾಂಶ[0] = (uint8_t *)buf;
    ಗಾಗಿ (ch = 1; planar && ch < nb_channels; ch++)
        audio_ದತ್ತಾಂಶ[ch] = audio_ದತ್ತಾಂಶ[ch-1] + ಸಾಲು_ಗಾತ್ರ;

    ಹಿಂತಿರುಗಿ buf_ಗಾತ್ರ;
}

ಪೂರ್ಣಾಂಕ av_samples_alloc(uint8_t **audio_ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ *linesize, ಪೂರ್ಣಾಂಕ nb_channels,
                     ಪೂರ್ಣಾಂಕ nb_samples, ಎಣಿಕೆ AVSampleFormat sample_fmt, ಪೂರ್ಣಾಂಕ align)
{
    uint8_t *buf;
    ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 = av_samples_get_ಬಫರ್_ಗಾತ್ರ(ಖಾಲಿ, nb_channels, nb_samples,
                                          sample_fmt, align);
    ಆದರೆ (ಗಾತ್ರ_2 < 0)
        ಹಿಂತಿರುಗಿ ಗಾತ್ರ_2;

    buf = av_malloc(ಗಾತ್ರ_2);
    ಆದರೆ (!buf)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾತ್ರ_2 = av_samples_fill_arrays(audio_ದತ್ತಾಂಶ, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    ಆದರೆ (ಗಾತ್ರ_2 < 0) {
        av_free(buf);
        ಹಿಂತಿರುಗಿ ಗಾತ್ರ_2;
    }

    av_samples_ಗಣ_silence(audio_ದತ್ತಾಂಶ, 0, nb_samples, nb_channels, sample_fmt);

    ಹಿಂತಿರುಗಿ ಗಾತ್ರ_2;
}

ಪೂರ್ಣಾಂಕ av_samples_alloc_array_and_samples(uint8_t ***audio_ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ *linesize, ಪೂರ್ಣಾಂಕ nb_channels,
                                       ಪೂರ್ಣಾಂಕ nb_samples, ಎಣಿಕೆ AVSampleFormat sample_fmt, ಪೂರ್ಣಾಂಕ align)
{
    ಪೂರ್ಣಾಂಕ ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_ದತ್ತಾಂಶ = av_calloc(nb_planes, ಗಾತ್ರ(**audio_ದತ್ತಾಂಶ));
    ಆದರೆ (!*audio_ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_ದತ್ತಾಂಶ, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    ಆದರೆ (ret < 0)
        av_freep(audio_ದತ್ತಾಂಶ);
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_samples_copy(uint8_t * ಸ್ಥಿರಾಂಕ *dst, uint8_t * ಸ್ಥಿರಾಂಕ *src, ಪೂರ್ಣಾಂಕ dst_ಸ್ಥಾನಾಂತರ,
                    ಪೂರ್ಣಾಂಕ src_ಸ್ಥಾನಾಂತರ, ಪೂರ್ಣಾಂಕ nb_samples, ಪೂರ್ಣಾಂಕ nb_channels,
                    ಎಣಿಕೆ AVSampleFormat sample_fmt)
{
    ಪೂರ್ಣಾಂಕ planar      = av_sample_fmt_is_planar(sample_fmt);
    ಪೂರ್ಣಾಂಕ planes      = planar ? nb_channels : 1;
    ಪೂರ್ಣಾಂಕ ಖಂಡ_align = av_get_ಬೈಟುಗಳು_ಪ್ರತಿ_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_ಗಾತ್ರ   = nb_samples * ಖಂಡ_align;
    ಪೂರ್ಣಾಂಕ i;

    dst_ಸ್ಥಾನಾಂತರ *= ಖಂಡ_align;
    src_ಸ್ಥಾನಾಂತರ *= ಖಂಡ_align;

    ಆದರೆ((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= ದತ್ತಾಂಶ_ಗಾತ್ರ) {
        ಗಾಗಿ (i = 0; i < planes; i++)
            ಸ್ಮರಣೆ_ನಕಲು(dst[i] + dst_ಸ್ಥಾನಾಂತರ, src[i] + src_ಸ್ಥಾನಾಂತರ, ದತ್ತಾಂಶ_ಗಾತ್ರ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾಗಿ (i = 0; i < planes; i++)
            memmove(dst[i] + dst_ಸ್ಥಾನಾಂತರ, src[i] + src_ಸ್ಥಾನಾಂತರ, ದತ್ತಾಂಶ_ಗಾತ್ರ);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_samples_ಗಣ_silence(uint8_t * ಸ್ಥಿರಾಂಕ *audio_ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ, ಪೂರ್ಣಾಂಕ nb_samples,
                           ಪೂರ್ಣಾಂಕ nb_channels, ಎಣಿಕೆ AVSampleFormat sample_fmt)
{
    ಪೂರ್ಣಾಂಕ planar      = av_sample_fmt_is_planar(sample_fmt);
    ಪೂರ್ಣಾಂಕ planes      = planar ? nb_channels : 1;
    ಪೂರ್ಣಾಂಕ ಖಂಡ_align = av_get_ಬೈಟುಗಳು_ಪ್ರತಿ_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_ಗಾತ್ರ   = nb_samples * ಖಂಡ_align;
    ಪೂರ್ಣಾಂಕ fill_char, i;

    ಆದರೆ (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    ಇಲ್ಲದಿದ್ದರೆ
        fill_char = 0x00;

    ಸ್ಥಾನಾಂತರ *= ಖಂಡ_align;

    ಗಾಗಿ (i = 0; i < planes; i++)
        memset(audio_ದತ್ತಾಂಶ[i] + ಸ್ಥಾನಾಂತರ, fill_char, ದತ್ತಾಂಶ_ಗಾತ್ರ);

    ಹಿಂತಿರುಗಿ 0;
}
