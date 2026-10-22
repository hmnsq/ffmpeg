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

#include "error.h"
#include "macros.h"
#include "mem.h"
#include "samplefmt.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

typedef sa_nracanaa SampleFmtInfo {
    var_na name[8];
    ཧྲིལ bits;
    ཧྲིལ planar;
    ga_nanaa AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
static const SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
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

const var_na *av_get_sample_fmt_name(ga_nanaa AVSampleFormat sample_fmt)
{
    གལ་ཏེ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ཕྱིར NULL;
    ཕྱིར sample_fmt_info[sample_fmt].name;
}

ga_nanaa AVSampleFormat av_get_sample_fmt(const var_na *name)
{
    ཧྲིལ i;

    ཆེད་དུ (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        གལ་ཏེ (!strcmp(sample_fmt_info[i].name, name))
            ཕྱིར i;
    ཕྱིར AV_SAMPLE_FMT_NONE;
}

ga_nanaa AVSampleFormat av_get_alt_sample_fmt(ga_nanaa AVSampleFormat sample_fmt, ཧྲིལ planar)
{
    གལ་ཏེ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ཕྱིར AV_SAMPLE_FMT_NONE;
    གལ་ཏེ (sample_fmt_info[sample_fmt].planar == planar)
        ཕྱིར sample_fmt;
    ཕྱིར sample_fmt_info[sample_fmt].altform;
}

ga_nanaa AVSampleFormat av_get_packed_sample_fmt(ga_nanaa AVSampleFormat sample_fmt)
{
    གལ་ཏེ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ཕྱིར AV_SAMPLE_FMT_NONE;
    གལ་ཏེ (sample_fmt_info[sample_fmt].planar)
        ཕྱིར sample_fmt_info[sample_fmt].altform;
    ཕྱིར sample_fmt;
}

ga_nanaa AVSampleFormat av_get_planar_sample_fmt(ga_nanaa AVSampleFormat sample_fmt)
{
    གལ་ཏེ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ཕྱིར AV_SAMPLE_FMT_NONE;
    གལ་ཏེ (sample_fmt_info[sample_fmt].planar)
        ཕྱིར sample_fmt;
    ཕྱིར sample_fmt_info[sample_fmt].altform;
}

var_na *av_get_sample_fmt_string (var_na *buf, ཧྲིལ buf_size, ga_nanaa AVSampleFormat sample_fmt)
{
    /* print header */
    གལ་ཏེ (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    དེ་མིན གལ་ཏེ (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    ཕྱིར buf;
}

ཧྲིལ av_get_bytes_per_sample(ga_nanaa AVSampleFormat sample_fmt)
{
     ཕྱིར sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

ཧྲིལ av_sample_fmt_is_planar(ga_nanaa AVSampleFormat sample_fmt)
{
     གལ་ཏེ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         ཕྱིར 0;
     ཕྱིར sample_fmt_info[sample_fmt].planar;
}

ཧྲིལ av_samples_get_buffer_size(ཧྲིལ *linesize, ཧྲིལ nb_channels, ཧྲིལ nb_samples,
                               ga_nanaa AVSampleFormat sample_fmt, ཧྲིལ align)
{
    ཧྲིལ line_size;
    ཧྲིལ sample_size = av_get_bytes_per_sample(sample_fmt);
    ཧྲིལ planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    གལ་ཏེ (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        ཕྱིར AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    གལ་ཏེ (!align) {
        གལ་ཏེ (nb_samples > INT_MAX - 31)
            ཕྱིར AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    གལ་ཏེ (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        ཕྱིར AVERROR(EINVAL);

    line_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    གལ་ཏེ (linesize)
        *linesize = line_size;

    ཕྱིར planar ? line_size * nb_channels : line_size;
}

ཧྲིལ av_samples_fill_arrays(uint8_t **audio_data, ཧྲིལ *linesize,
                           const uint8_t *buf, ཧྲིལ nb_channels, ཧྲིལ nb_samples,
                           ga_nanaa AVSampleFormat sample_fmt, ཧྲིལ align)
{
    ཧྲིལ ch, planar, buf_size, line_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&line_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    གལ་ཏེ (buf_size < 0)
        ཕྱིར buf_size;

    གལ་ཏེ (linesize)
        *linesize = line_size;

    memset(audio_data, 0, planar
                          ? parimaa_na(*audio_data) * nb_channels
                          : parimaa_na(*audio_data));

    གལ་ཏེ (!buf)
        ཕྱིར buf_size;

    audio_data[0] = (uint8_t *)buf;
    ཆེད་དུ (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + line_size;

    ཕྱིར buf_size;
}

ཧྲིལ av_samples_alloc(uint8_t **audio_data, ཧྲིལ *linesize, ཧྲིལ nb_channels,
                     ཧྲིལ nb_samples, ga_nanaa AVSampleFormat sample_fmt, ཧྲིལ align)
{
    uint8_t *buf;
    ཧྲིལ size = av_samples_get_buffer_size(NULL, nb_channels, nb_samples,
                                          sample_fmt, align);
    གལ་ཏེ (size < 0)
        ཕྱིར size;

    buf = av_malloc(size);
    གལ་ཏེ (!buf)
        ཕྱིར AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    གལ་ཏེ (size < 0) {
        av_free(buf);
        ཕྱིར size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    ཕྱིར size;
}

ཧྲིལ av_samples_alloc_array_and_samples(uint8_t ***audio_data, ཧྲིལ *linesize, ཧྲིལ nb_channels,
                                       ཧྲིལ nb_samples, ga_nanaa AVSampleFormat sample_fmt, ཧྲིལ align)
{
    ཧྲིལ ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, parimaa_na(**audio_data));
    གལ་ཏེ (!*audio_data)
        ཕྱིར AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    གལ་ཏེ (ret < 0)
        av_freep(audio_data);
    ཕྱིར ret;
}

ཧྲིལ av_samples_copy(uint8_t * const *dst, uint8_t * const *src, ཧྲིལ dst_offset,
                    ཧྲིལ src_offset, ཧྲིལ nb_samples, ཧྲིལ nb_channels,
                    ga_nanaa AVSampleFormat sample_fmt)
{
    ཧྲིལ planar      = av_sample_fmt_is_planar(sample_fmt);
    ཧྲིལ planes      = planar ? nb_channels : 1;
    ཧྲིལ block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ཧྲིལ data_size   = nb_samples * block_align;
    ཧྲིལ i;

    dst_offset *= block_align;
    src_offset *= block_align;

    གལ་ཏེ((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        ཆེད་དུ (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } དེ་མིན {
        ཆེད་དུ (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    ཕྱིར 0;
}

ཧྲིལ av_samples_set_silence(uint8_t * const *audio_data, ཧྲིལ offset, ཧྲིལ nb_samples,
                           ཧྲིལ nb_channels, ga_nanaa AVSampleFormat sample_fmt)
{
    ཧྲིལ planar      = av_sample_fmt_is_planar(sample_fmt);
    ཧྲིལ planes      = planar ? nb_channels : 1;
    ཧྲིལ block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ཧྲིལ data_size   = nb_samples * block_align;
    ཧྲིལ fill_char, i;

    གལ་ཏེ (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    དེ་མིན གལ་ཏེ (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    དེ་མིན
        fill_char = 0x00;

    offset *= block_align;

    ཆེད་དུ (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    ཕྱིར 0;
}
