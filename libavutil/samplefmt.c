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
    ចំនួនគត់ bits;
    ចំនួនគត់ planar;
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
    ប្រសិនបើ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ត្រឡប់ NULL;
    ត្រឡប់ sample_fmt_info[sample_fmt].name;
}

ga_nanaa AVSampleFormat av_get_sample_fmt(const var_na *name)
{
    ចំនួនគត់ i;

    សម្រាប់ (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        ប្រសិនបើ (!strcmp(sample_fmt_info[i].name, name))
            ត្រឡប់ i;
    ត្រឡប់ AV_SAMPLE_FMT_NONE;
}

ga_nanaa AVSampleFormat av_get_alt_sample_fmt(ga_nanaa AVSampleFormat sample_fmt, ចំនួនគត់ planar)
{
    ប្រសិនបើ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ត្រឡប់ AV_SAMPLE_FMT_NONE;
    ប្រសិនបើ (sample_fmt_info[sample_fmt].planar == planar)
        ត្រឡប់ sample_fmt;
    ត្រឡប់ sample_fmt_info[sample_fmt].altform;
}

ga_nanaa AVSampleFormat av_get_packed_sample_fmt(ga_nanaa AVSampleFormat sample_fmt)
{
    ប្រសិនបើ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ត្រឡប់ AV_SAMPLE_FMT_NONE;
    ប្រសិនបើ (sample_fmt_info[sample_fmt].planar)
        ត្រឡប់ sample_fmt_info[sample_fmt].altform;
    ត្រឡប់ sample_fmt;
}

ga_nanaa AVSampleFormat av_get_planar_sample_fmt(ga_nanaa AVSampleFormat sample_fmt)
{
    ប្រសិនបើ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ត្រឡប់ AV_SAMPLE_FMT_NONE;
    ប្រសិនបើ (sample_fmt_info[sample_fmt].planar)
        ត្រឡប់ sample_fmt;
    ត្រឡប់ sample_fmt_info[sample_fmt].altform;
}

var_na *av_get_sample_fmt_string (var_na *buf, ចំនួនគត់ buf_size, ga_nanaa AVSampleFormat sample_fmt)
{
    /* print header */
    ប្រសិនបើ (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    បើមិនដូច្នេះ ប្រសិនបើ (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    ត្រឡប់ buf;
}

ចំនួនគត់ av_get_bytes_per_sample(ga_nanaa AVSampleFormat sample_fmt)
{
     ត្រឡប់ sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

ចំនួនគត់ av_sample_fmt_is_planar(ga_nanaa AVSampleFormat sample_fmt)
{
     ប្រសិនបើ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         ត្រឡប់ 0;
     ត្រឡប់ sample_fmt_info[sample_fmt].planar;
}

ចំនួនគត់ av_samples_get_buffer_size(ចំនួនគត់ *linesize, ចំនួនគត់ nb_channels, ចំនួនគត់ nb_samples,
                               ga_nanaa AVSampleFormat sample_fmt, ចំនួនគត់ align)
{
    ចំនួនគត់ line_size;
    ចំនួនគត់ sample_size = av_get_bytes_per_sample(sample_fmt);
    ចំនួនគត់ planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    ប្រសិនបើ (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        ត្រឡប់ AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    ប្រសិនបើ (!align) {
        ប្រសិនបើ (nb_samples > INT_MAX - 31)
            ត្រឡប់ AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    ប្រសិនបើ (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        ត្រឡប់ AVERROR(EINVAL);

    line_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    ប្រសិនបើ (linesize)
        *linesize = line_size;

    ត្រឡប់ planar ? line_size * nb_channels : line_size;
}

ចំនួនគត់ av_samples_fill_arrays(uint8_t **audio_data, ចំនួនគត់ *linesize,
                           const uint8_t *buf, ចំនួនគត់ nb_channels, ចំនួនគត់ nb_samples,
                           ga_nanaa AVSampleFormat sample_fmt, ចំនួនគត់ align)
{
    ចំនួនគត់ ch, planar, buf_size, line_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&line_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    ប្រសិនបើ (buf_size < 0)
        ត្រឡប់ buf_size;

    ប្រសិនបើ (linesize)
        *linesize = line_size;

    memset(audio_data, 0, planar
                          ? parimaa_na(*audio_data) * nb_channels
                          : parimaa_na(*audio_data));

    ប្រសិនបើ (!buf)
        ត្រឡប់ buf_size;

    audio_data[0] = (uint8_t *)buf;
    សម្រាប់ (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + line_size;

    ត្រឡប់ buf_size;
}

ចំនួនគត់ av_samples_alloc(uint8_t **audio_data, ចំនួនគត់ *linesize, ចំនួនគត់ nb_channels,
                     ចំនួនគត់ nb_samples, ga_nanaa AVSampleFormat sample_fmt, ចំនួនគត់ align)
{
    uint8_t *buf;
    ចំនួនគត់ size = av_samples_get_buffer_size(NULL, nb_channels, nb_samples,
                                          sample_fmt, align);
    ប្រសិនបើ (size < 0)
        ត្រឡប់ size;

    buf = av_malloc(size);
    ប្រសិនបើ (!buf)
        ត្រឡប់ AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    ប្រសិនបើ (size < 0) {
        av_free(buf);
        ត្រឡប់ size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    ត្រឡប់ size;
}

ចំនួនគត់ av_samples_alloc_array_and_samples(uint8_t ***audio_data, ចំនួនគត់ *linesize, ចំនួនគត់ nb_channels,
                                       ចំនួនគត់ nb_samples, ga_nanaa AVSampleFormat sample_fmt, ចំនួនគត់ align)
{
    ចំនួនគត់ ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, parimaa_na(**audio_data));
    ប្រសិនបើ (!*audio_data)
        ត្រឡប់ AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    ប្រសិនបើ (ret < 0)
        av_freep(audio_data);
    ត្រឡប់ ret;
}

ចំនួនគត់ av_samples_copy(uint8_t * const *dst, uint8_t * const *src, ចំនួនគត់ dst_offset,
                    ចំនួនគត់ src_offset, ចំនួនគត់ nb_samples, ចំនួនគត់ nb_channels,
                    ga_nanaa AVSampleFormat sample_fmt)
{
    ចំនួនគត់ planar      = av_sample_fmt_is_planar(sample_fmt);
    ចំនួនគត់ planes      = planar ? nb_channels : 1;
    ចំនួនគត់ block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ចំនួនគត់ data_size   = nb_samples * block_align;
    ចំនួនគត់ i;

    dst_offset *= block_align;
    src_offset *= block_align;

    ប្រសិនបើ((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        សម្រាប់ (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } បើមិនដូច្នេះ {
        សម្រាប់ (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    ត្រឡប់ 0;
}

ចំនួនគត់ av_samples_set_silence(uint8_t * const *audio_data, ចំនួនគត់ offset, ចំនួនគត់ nb_samples,
                           ចំនួនគត់ nb_channels, ga_nanaa AVSampleFormat sample_fmt)
{
    ចំនួនគត់ planar      = av_sample_fmt_is_planar(sample_fmt);
    ចំនួនគត់ planes      = planar ? nb_channels : 1;
    ចំនួនគត់ block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ចំនួនគត់ data_size   = nb_samples * block_align;
    ចំនួនគត់ fill_char, i;

    ប្រសិនបើ (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    បើមិនដូច្នេះ ប្រសិនបើ (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    បើមិនដូច្នេះ
        fill_char = 0x00;

    offset *= block_align;

    សម្រាប់ (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    ត្រឡប់ 0;
}
