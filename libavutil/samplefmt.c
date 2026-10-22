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

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SampleFmtInfo {
    ವರ್ಣ name[8];
    ಪೂರ್ಣಾಙ್ಕ bits;
    ಪೂರ್ಣಾಙ್ಕ planar;
    ಗಣನಾ AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
ಸ್ಥಿರ ಧ್ರುವ SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
    [AV_SAMPLE_FMT_U8]   = { .name =   "u8", .bits =  8, .planar = 0, .altform = AV_SAMPLE_FMT_U8P  },
    [AV_SAMPLE_FMT_S16]  = { .name =  "s16", .bits = 16, .planar = 0, .altform = AV_SAMPLE_FMT_S16P },
    [AV_SAMPLE_FMT_S32]  = { .name =  "s32", .bits = 32, .planar = 0, .altform = AV_SAMPLE_FMT_S32P },
    [AV_SAMPLE_FMT_S64]  = { .name =  "s64", .bits = 64, .planar = 0, .altform = AV_SAMPLE_FMT_S64P },
    [AV_SAMPLE_FMT_FLT]  = { .name =  "flt", .bits = 32, .planar = 0, .altform = AV_SAMPLE_FMT_FLTP },
    [AV_SAMPLE_FMT_DBL]  = { .name =  "dbl", .bits = 64, .planar = 0, .altform = AV_SAMPLE_FMT_DBLP },
    [AV_SAMPLE_FMT_U8P]  = { .name =  "u8p", .bits =  8, .planar = 1, .altform = AV_SAMPLE_FMT_U8   },
    [AV_SAMPLE_FMT_S16P] = { .name = "s16p", .bits = 16, .planar = 1, .altform = AV_SAMPLE_FMT_S16  },
    [AV_SAMPLE_FMT_S32P] = { .name = "s32p", .bits = 32, .planar = 1, .altform = AV_SAMPLE_FMT_S32  },
    [AV_SAMPLE_FMT_S64P] = { .name = "s64p", .bits = 64, .planar = 1, .altform = AV_SAMPLE_FMT_S64  },
    [AV_SAMPLE_FMT_FLTP] = { .name = "fltp", .bits = 32, .planar = 1, .altform = AV_SAMPLE_FMT_FLT  },
    [AV_SAMPLE_FMT_DBLP] = { .name = "dblp", .bits = 64, .planar = 1, .altform = AV_SAMPLE_FMT_DBL  },
    [AV_SAMPLE_FMT_DSD]  = { .name =  "dsd", .bits =  8, .planar = 0, .altform = AV_SAMPLE_FMT_DSD  },
};

ಧ್ರುವ ವರ್ಣ *av_get_sample_fmt_name(ಗಣನಾ AVSampleFormat sample_fmt)
{
    ಯದಿ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ sample_fmt_info[sample_fmt].name;
}

ಗಣನಾ AVSampleFormat av_get_sample_fmt(ಧ್ರುವ ವರ್ಣ *name)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        ಯದಿ (!strcmp(sample_fmt_info[i].name, name))
            ಪ್ರತ್ಯಾಗಮ i;
    ಪ್ರತ್ಯಾಗಮ AV_SAMPLE_FMT_NONE;
}

ಗಣನಾ AVSampleFormat av_get_alt_sample_fmt(ಗಣನಾ AVSampleFormat sample_fmt, ಪೂರ್ಣಾಙ್ಕ planar)
{
    ಯದಿ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ಪ್ರತ್ಯಾಗಮ AV_SAMPLE_FMT_NONE;
    ಯದಿ (sample_fmt_info[sample_fmt].planar == planar)
        ಪ್ರತ್ಯಾಗಮ sample_fmt;
    ಪ್ರತ್ಯಾಗಮ sample_fmt_info[sample_fmt].altform;
}

ಗಣನಾ AVSampleFormat av_get_packed_sample_fmt(ಗಣನಾ AVSampleFormat sample_fmt)
{
    ಯದಿ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ಪ್ರತ್ಯಾಗಮ AV_SAMPLE_FMT_NONE;
    ಯದಿ (sample_fmt_info[sample_fmt].planar)
        ಪ್ರತ್ಯಾಗಮ sample_fmt_info[sample_fmt].altform;
    ಪ್ರತ್ಯಾಗಮ sample_fmt;
}

ಗಣನಾ AVSampleFormat av_get_planar_sample_fmt(ಗಣನಾ AVSampleFormat sample_fmt)
{
    ಯದಿ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ಪ್ರತ್ಯಾಗಮ AV_SAMPLE_FMT_NONE;
    ಯದಿ (sample_fmt_info[sample_fmt].planar)
        ಪ್ರತ್ಯಾಗಮ sample_fmt;
    ಪ್ರತ್ಯಾಗಮ sample_fmt_info[sample_fmt].altform;
}

ವರ್ಣ *av_get_sample_fmt_string (ವರ್ಣ *buf, ಪೂರ್ಣಾಙ್ಕ buf_size, ಗಣನಾ AVSampleFormat sample_fmt)
{
    /* print header */
    ಯದಿ (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    ಅನ್ಯಥಾ ಯದಿ (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    ಪ್ರತ್ಯಾಗಮ buf;
}

ಪೂರ್ಣಾಙ್ಕ av_get_bytes_per_sample(ಗಣನಾ AVSampleFormat sample_fmt)
{
     ಪ್ರತ್ಯಾಗಮ sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

ಪೂರ್ಣಾಙ್ಕ av_sample_fmt_is_planar(ಗಣನಾ AVSampleFormat sample_fmt)
{
     ಯದಿ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         ಪ್ರತ್ಯಾಗಮ 0;
     ಪ್ರತ್ಯಾಗಮ sample_fmt_info[sample_fmt].planar;
}

ಪೂರ್ಣಾಙ್ಕ av_samples_get_buffer_size(ಪೂರ್ಣಾಙ್ಕ *linesize, ಪೂರ್ಣಾಙ್ಕ nb_channels, ಪೂರ್ಣಾಙ್ಕ nb_samples,
                               ಗಣನಾ AVSampleFormat sample_fmt, ಪೂರ್ಣಾಙ್ಕ align)
{
    ಪೂರ್ಣಾಙ್ಕ ಸಾಲು_size;
    ಪೂರ್ಣಾಙ್ಕ sample_size = av_get_bytes_per_sample(sample_fmt);
    ಪೂರ್ಣಾಙ್ಕ planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    ಯದಿ (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    ಯದಿ (!align) {
        ಯದಿ (nb_samples > INT_MAX - 31)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    ಯದಿ (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಸಾಲು_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    ಯದಿ (linesize)
        *linesize = ಸಾಲು_size;

    ಪ್ರತ್ಯಾಗಮ planar ? ಸಾಲು_size * nb_channels : ಸಾಲು_size;
}

ಪೂರ್ಣಾಙ್ಕ av_samples_fill_arrays(uint8_t **audio_data, ಪೂರ್ಣಾಙ್ಕ *linesize,
                           ಧ್ರುವ uint8_t *buf, ಪೂರ್ಣಾಙ್ಕ nb_channels, ಪೂರ್ಣಾಙ್ಕ nb_samples,
                           ಗಣನಾ AVSampleFormat sample_fmt, ಪೂರ್ಣಾಙ್ಕ align)
{
    ಪೂರ್ಣಾಙ್ಕ ch, planar, buf_size, ಸಾಲು_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&ಸಾಲು_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    ಯದಿ (buf_size < 0)
        ಪ್ರತ್ಯಾಗಮ buf_size;

    ಯದಿ (linesize)
        *linesize = ಸಾಲು_size;

    memset(audio_data, 0, planar
                          ? ಪರಿಮಾಣ(*audio_data) * nb_channels
                          : ಪರಿಮಾಣ(*audio_data));

    ಯದಿ (!buf)
        ಪ್ರತ್ಯಾಗಮ buf_size;

    audio_data[0] = (uint8_t *)buf;
    ಪ್ರತಿ (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + ಸಾಲು_size;

    ಪ್ರತ್ಯಾಗಮ buf_size;
}

ಪೂರ್ಣಾಙ್ಕ av_samples_alloc(uint8_t **audio_data, ಪೂರ್ಣಾಙ್ಕ *linesize, ಪೂರ್ಣಾಙ್ಕ nb_channels,
                     ಪೂರ್ಣಾಙ್ಕ nb_samples, ಗಣನಾ AVSampleFormat sample_fmt, ಪೂರ್ಣಾಙ್ಕ align)
{
    uint8_t *buf;
    ಪೂರ್ಣಾಙ್ಕ size = av_samples_get_buffer_size(ರಿಕ್ತ, nb_channels, nb_samples,
                                          sample_fmt, align);
    ಯದಿ (size < 0)
        ಪ್ರತ್ಯಾಗಮ size;

    buf = av_malloc(size);
    ಯದಿ (!buf)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    ಯದಿ (size < 0) {
        av_free(buf);
        ಪ್ರತ್ಯಾಗಮ size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    ಪ್ರತ್ಯಾಗಮ size;
}

ಪೂರ್ಣಾಙ್ಕ av_samples_alloc_array_and_samples(uint8_t ***audio_data, ಪೂರ್ಣಾಙ್ಕ *linesize, ಪೂರ್ಣಾಙ್ಕ nb_channels,
                                       ಪೂರ್ಣಾಙ್ಕ nb_samples, ಗಣನಾ AVSampleFormat sample_fmt, ಪೂರ್ಣಾಙ್ಕ align)
{
    ಪೂರ್ಣಾಙ್ಕ ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, ಪರಿಮಾಣ(**audio_data));
    ಯದಿ (!*audio_data)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    ಯದಿ (ret < 0)
        av_freep(audio_data);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_samples_copy(uint8_t * ಧ್ರುವ *dst, uint8_t * ಧ್ರುವ *src, ಪೂರ್ಣಾಙ್ಕ dst_offset,
                    ಪೂರ್ಣಾಙ್ಕ src_offset, ಪೂರ್ಣಾಙ್ಕ nb_samples, ಪೂರ್ಣಾಙ್ಕ nb_channels,
                    ಗಣನಾ AVSampleFormat sample_fmt)
{
    ಪೂರ್ಣಾಙ್ಕ planar      = av_sample_fmt_is_planar(sample_fmt);
    ಪೂರ್ಣಾಙ್ಕ planes      = planar ? nb_channels : 1;
    ಪೂರ್ಣಾಙ್ಕ block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ಪೂರ್ಣಾಙ್ಕ data_size   = nb_samples * block_align;
    ಪೂರ್ಣಾಙ್ಕ i;

    dst_offset *= block_align;
    src_offset *= block_align;

    ಯದಿ((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        ಪ್ರತಿ (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } ಅನ್ಯಥಾ {
        ಪ್ರತಿ (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_samples_set_silence(uint8_t * ಧ್ರುವ *audio_data, ಪೂರ್ಣಾಙ್ಕ offset, ಪೂರ್ಣಾಙ್ಕ nb_samples,
                           ಪೂರ್ಣಾಙ್ಕ nb_channels, ಗಣನಾ AVSampleFormat sample_fmt)
{
    ಪೂರ್ಣಾಙ್ಕ planar      = av_sample_fmt_is_planar(sample_fmt);
    ಪೂರ್ಣಾಙ್ಕ planes      = planar ? nb_channels : 1;
    ಪೂರ್ಣಾಙ್ಕ block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ಪೂರ್ಣಾಙ್ಕ data_size   = nb_samples * block_align;
    ಪೂರ್ಣಾಙ್ಕ fill_char, i;

    ಯದಿ (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    ಅನ್ಯಥಾ ಯದಿ (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    ಅನ್ಯಥಾ
        fill_char = 0x00;

    offset *= block_align;

    ಪ್ರತಿ (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    ಪ್ರತ್ಯಾಗಮ 0;
}
