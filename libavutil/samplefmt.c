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

#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "samplefmt.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SampleFmtInfo {
    ਅੱਖਰ name[8];
    ਪੂਰਨ ਬਿੱਟ;
    ਪੂਰਨ planar;
    ਗਿਣਤੀ AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
ਸਥਿਰ ਅਚਲ SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
    [AV_SAMPLE_FMT_U8]   = { .name =   "u8", .ਬਿੱਟ =  8, .planar = 0, .altform = AV_SAMPLE_FMT_U8P  },
    [AV_SAMPLE_FMT_S16]  = { .name =  "s16", .ਬਿੱਟ = 16, .planar = 0, .altform = AV_SAMPLE_FMT_S16P },
    [AV_SAMPLE_FMT_S32]  = { .name =  "s32", .ਬਿੱਟ = 32, .planar = 0, .altform = AV_SAMPLE_FMT_S32P },
    [AV_SAMPLE_FMT_S64]  = { .name =  "s64", .ਬਿੱਟ = 64, .planar = 0, .altform = AV_SAMPLE_FMT_S64P },
    [AV_SAMPLE_FMT_FLT]  = { .name =  "flt", .ਬਿੱਟ = 32, .planar = 0, .altform = AV_SAMPLE_FMT_FLTP },
    [AV_SAMPLE_FMT_DBL]  = { .name =  "dbl", .ਬਿੱਟ = 64, .planar = 0, .altform = AV_SAMPLE_FMT_DBLP },
    [AV_SAMPLE_FMT_U8P]  = { .name =  "u8p", .ਬਿੱਟ =  8, .planar = 1, .altform = AV_SAMPLE_FMT_U8   },
    [AV_SAMPLE_FMT_S16P] = { .name = "s16p", .ਬਿੱਟ = 16, .planar = 1, .altform = AV_SAMPLE_FMT_S16  },
    [AV_SAMPLE_FMT_S32P] = { .name = "s32p", .ਬਿੱਟ = 32, .planar = 1, .altform = AV_SAMPLE_FMT_S32  },
    [AV_SAMPLE_FMT_S64P] = { .name = "s64p", .ਬਿੱਟ = 64, .planar = 1, .altform = AV_SAMPLE_FMT_S64  },
    [AV_SAMPLE_FMT_FLTP] = { .name = "fltp", .ਬਿੱਟ = 32, .planar = 1, .altform = AV_SAMPLE_FMT_FLT  },
    [AV_SAMPLE_FMT_DBLP] = { .name = "dblp", .ਬਿੱਟ = 64, .planar = 1, .altform = AV_SAMPLE_FMT_DBL  },
    [AV_SAMPLE_FMT_DSD]  = { .name =  "dsd", .ਬਿੱਟ =  8, .planar = 0, .altform = AV_SAMPLE_FMT_DSD  },
};

ਅਚਲ ਅੱਖਰ *av_get_sample_fmt_name(ਗਿਣਤੀ AVSampleFormat sample_fmt)
{
    ਜੇ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ਵਾਪਸ ਨਿਰਾ;
    ਵਾਪਸ sample_fmt_info[sample_fmt].name;
}

ਗਿਣਤੀ AVSampleFormat av_get_sample_fmt(ਅਚਲ ਅੱਖਰ *name)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        ਜੇ (!strcmp(sample_fmt_info[i].name, name))
            ਵਾਪਸ i;
    ਵਾਪਸ AV_SAMPLE_FMT_NONE;
}

ਗਿਣਤੀ AVSampleFormat av_get_alt_sample_fmt(ਗਿਣਤੀ AVSampleFormat sample_fmt, ਪੂਰਨ planar)
{
    ਜੇ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ਵਾਪਸ AV_SAMPLE_FMT_NONE;
    ਜੇ (sample_fmt_info[sample_fmt].planar == planar)
        ਵਾਪਸ sample_fmt;
    ਵਾਪਸ sample_fmt_info[sample_fmt].altform;
}

ਗਿਣਤੀ AVSampleFormat av_get_packed_sample_fmt(ਗਿਣਤੀ AVSampleFormat sample_fmt)
{
    ਜੇ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ਵਾਪਸ AV_SAMPLE_FMT_NONE;
    ਜੇ (sample_fmt_info[sample_fmt].planar)
        ਵਾਪਸ sample_fmt_info[sample_fmt].altform;
    ਵਾਪਸ sample_fmt;
}

ਗਿਣਤੀ AVSampleFormat av_get_planar_sample_fmt(ਗਿਣਤੀ AVSampleFormat sample_fmt)
{
    ਜੇ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ਵਾਪਸ AV_SAMPLE_FMT_NONE;
    ਜੇ (sample_fmt_info[sample_fmt].planar)
        ਵਾਪਸ sample_fmt;
    ਵਾਪਸ sample_fmt_info[sample_fmt].altform;
}

ਅੱਖਰ *av_get_sample_fmt_string (ਅੱਖਰ *buf, ਪੂਰਨ buf_ਮਾਪ, ਗਿਣਤੀ AVSampleFormat sample_fmt)
{
    /* print header */
    ਜੇ (sample_fmt < 0)
        snprintf(buf, buf_ਮਾਪ, "name  " " depth");
    ਨਹੀਂਤਾਂ ਜੇ (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_ਮਾਪ, "%-6s" "   %2d ", info.name, info.ਬਿੱਟ);
    }

    ਵਾਪਸ buf;
}

ਪੂਰਨ av_get_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_sample(ਗਿਣਤੀ AVSampleFormat sample_fmt)
{
     ਵਾਪਸ sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].ਬਿੱਟ >> 3;
}

ਪੂਰਨ av_sample_fmt_is_planar(ਗਿਣਤੀ AVSampleFormat sample_fmt)
{
     ਜੇ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         ਵਾਪਸ 0;
     ਵਾਪਸ sample_fmt_info[sample_fmt].planar;
}

ਪੂਰਨ av_samples_get_ਬਫਰ_ਮਾਪ(ਪੂਰਨ *linesize, ਪੂਰਨ nb_channels, ਪੂਰਨ nb_samples,
                               ਗਿਣਤੀ AVSampleFormat sample_fmt, ਪੂਰਨ align)
{
    ਪੂਰਨ ਸਤਰ_ਮਾਪ;
    ਪੂਰਨ sample_ਮਾਪ = av_get_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_sample(sample_fmt);
    ਪੂਰਨ planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    ਜੇ (!sample_ਮਾਪ || nb_samples <= 0 || nb_channels <= 0)
        ਵਾਪਸ AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    ਜੇ (!align) {
        ਜੇ (nb_samples > ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ - 31)
            ਵਾਪਸ AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    ਜੇ (nb_channels > ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ / align ||
        (int64_t)nb_channels * nb_samples > (ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ - (align * nb_channels)) / sample_ਮਾਪ)
        ਵਾਪਸ AVERROR(EINVAL);

    ਸਤਰ_ਮਾਪ = planar ? FFALIGN(nb_samples * sample_ਮਾਪ,               align) :
                         FFALIGN(nb_samples * sample_ਮਾਪ * nb_channels, align);
    ਜੇ (linesize)
        *linesize = ਸਤਰ_ਮਾਪ;

    ਵਾਪਸ planar ? ਸਤਰ_ਮਾਪ * nb_channels : ਸਤਰ_ਮਾਪ;
}

ਪੂਰਨ av_samples_fill_arrays(uint8_t **audio_ਅੰਕੜੇ, ਪੂਰਨ *linesize,
                           ਅਚਲ uint8_t *buf, ਪੂਰਨ nb_channels, ਪੂਰਨ nb_samples,
                           ਗਿਣਤੀ AVSampleFormat sample_fmt, ਪੂਰਨ align)
{
    ਪੂਰਨ ch, planar, buf_ਮਾਪ, ਸਤਰ_ਮਾਪ;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_ਮਾਪ = av_samples_get_ਬਫਰ_ਮਾਪ(&ਸਤਰ_ਮਾਪ, nb_channels, nb_samples,
                                          sample_fmt, align);
    ਜੇ (buf_ਮਾਪ < 0)
        ਵਾਪਸ buf_ਮਾਪ;

    ਜੇ (linesize)
        *linesize = ਸਤਰ_ਮਾਪ;

    memset(audio_ਅੰਕੜੇ, 0, planar
                          ? ਆਕਾਰ(*audio_ਅੰਕੜੇ) * nb_channels
                          : ਆਕਾਰ(*audio_ਅੰਕੜੇ));

    ਜੇ (!buf)
        ਵਾਪਸ buf_ਮਾਪ;

    audio_ਅੰਕੜੇ[0] = (uint8_t *)buf;
    ਲਈ (ch = 1; planar && ch < nb_channels; ch++)
        audio_ਅੰਕੜੇ[ch] = audio_ਅੰਕੜੇ[ch-1] + ਸਤਰ_ਮਾਪ;

    ਵਾਪਸ buf_ਮਾਪ;
}

ਪੂਰਨ av_samples_alloc(uint8_t **audio_ਅੰਕੜੇ, ਪੂਰਨ *linesize, ਪੂਰਨ nb_channels,
                     ਪੂਰਨ nb_samples, ਗਿਣਤੀ AVSampleFormat sample_fmt, ਪੂਰਨ align)
{
    uint8_t *buf;
    ਪੂਰਨ ਮਾਪ = av_samples_get_ਬਫਰ_ਮਾਪ(ਨਿਰਾ, nb_channels, nb_samples,
                                          sample_fmt, align);
    ਜੇ (ਮਾਪ < 0)
        ਵਾਪਸ ਮਾਪ;

    buf = av_malloc(ਮਾਪ);
    ਜੇ (!buf)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਮਾਪ = av_samples_fill_arrays(audio_ਅੰਕੜੇ, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    ਜੇ (ਮਾਪ < 0) {
        av_free(buf);
        ਵਾਪਸ ਮਾਪ;
    }

    av_samples_ਸੈੱਟ_silence(audio_ਅੰਕੜੇ, 0, nb_samples, nb_channels, sample_fmt);

    ਵਾਪਸ ਮਾਪ;
}

ਪੂਰਨ av_samples_alloc_array_and_samples(uint8_t ***audio_ਅੰਕੜੇ, ਪੂਰਨ *linesize, ਪੂਰਨ nb_channels,
                                       ਪੂਰਨ nb_samples, ਗਿਣਤੀ AVSampleFormat sample_fmt, ਪੂਰਨ align)
{
    ਪੂਰਨ ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_ਅੰਕੜੇ = av_calloc(nb_planes, ਆਕਾਰ(**audio_ਅੰਕੜੇ));
    ਜੇ (!*audio_ਅੰਕੜੇ)
        ਵਾਪਸ AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_ਅੰਕੜੇ, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    ਜੇ (ret < 0)
        av_freep(audio_ਅੰਕੜੇ);
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_samples_copy(uint8_t * ਅਚਲ *dst, uint8_t * ਅਚਲ *src, ਪੂਰਨ dst_ਵਿੱਥ,
                    ਪੂਰਨ src_ਵਿੱਥ, ਪੂਰਨ nb_samples, ਪੂਰਨ nb_channels,
                    ਗਿਣਤੀ AVSampleFormat sample_fmt)
{
    ਪੂਰਨ planar      = av_sample_fmt_is_planar(sample_fmt);
    ਪੂਰਨ planes      = planar ? nb_channels : 1;
    ਪੂਰਨ ਖੰਡ_align = av_get_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ਪੂਰਨ ਅੰਕੜੇ_ਮਾਪ   = nb_samples * ਖੰਡ_align;
    ਪੂਰਨ i;

    dst_ਵਿੱਥ *= ਖੰਡ_align;
    src_ਵਿੱਥ *= ਖੰਡ_align;

    ਜੇ((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= ਅੰਕੜੇ_ਮਾਪ) {
        ਲਈ (i = 0; i < planes; i++)
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst[i] + dst_ਵਿੱਥ, src[i] + src_ਵਿੱਥ, ਅੰਕੜੇ_ਮਾਪ);
    } ਨਹੀਂਤਾਂ {
        ਲਈ (i = 0; i < planes; i++)
            memmove(dst[i] + dst_ਵਿੱਥ, src[i] + src_ਵਿੱਥ, ਅੰਕੜੇ_ਮਾਪ);
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_samples_ਸੈੱਟ_silence(uint8_t * ਅਚਲ *audio_ਅੰਕੜੇ, ਪੂਰਨ ਵਿੱਥ, ਪੂਰਨ nb_samples,
                           ਪੂਰਨ nb_channels, ਗਿਣਤੀ AVSampleFormat sample_fmt)
{
    ਪੂਰਨ planar      = av_sample_fmt_is_planar(sample_fmt);
    ਪੂਰਨ planes      = planar ? nb_channels : 1;
    ਪੂਰਨ ਖੰਡ_align = av_get_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ਪੂਰਨ ਅੰਕੜੇ_ਮਾਪ   = nb_samples * ਖੰਡ_align;
    ਪੂਰਨ fill_char, i;

    ਜੇ (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    ਨਹੀਂਤਾਂ ਜੇ (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    ਨਹੀਂਤਾਂ
        fill_char = 0x00;

    ਵਿੱਥ *= ਖੰਡ_align;

    ਲਈ (i = 0; i < planes; i++)
        memset(audio_ਅੰਕੜੇ[i] + ਵਿੱਥ, fill_char, ਅੰਕੜੇ_ਮਾਪ);

    ਵਾਪਸ 0;
}
