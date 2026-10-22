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
    ຈຳນວນເຕັມ bits;
    ຈຳນວນເຕັມ planar;
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
    ຖ້າ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ສົ່ງຄືນ NULL;
    ສົ່ງຄືນ sample_fmt_info[sample_fmt].name;
}

ga_nanaa AVSampleFormat av_get_sample_fmt(const var_na *name)
{
    ຈຳນວນເຕັມ i;

    ສຳລັບ (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        ຖ້າ (!strcmp(sample_fmt_info[i].name, name))
            ສົ່ງຄືນ i;
    ສົ່ງຄືນ AV_SAMPLE_FMT_NONE;
}

ga_nanaa AVSampleFormat av_get_alt_sample_fmt(ga_nanaa AVSampleFormat sample_fmt, ຈຳນວນເຕັມ planar)
{
    ຖ້າ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ສົ່ງຄືນ AV_SAMPLE_FMT_NONE;
    ຖ້າ (sample_fmt_info[sample_fmt].planar == planar)
        ສົ່ງຄືນ sample_fmt;
    ສົ່ງຄືນ sample_fmt_info[sample_fmt].altform;
}

ga_nanaa AVSampleFormat av_get_packed_sample_fmt(ga_nanaa AVSampleFormat sample_fmt)
{
    ຖ້າ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ສົ່ງຄືນ AV_SAMPLE_FMT_NONE;
    ຖ້າ (sample_fmt_info[sample_fmt].planar)
        ສົ່ງຄືນ sample_fmt_info[sample_fmt].altform;
    ສົ່ງຄືນ sample_fmt;
}

ga_nanaa AVSampleFormat av_get_planar_sample_fmt(ga_nanaa AVSampleFormat sample_fmt)
{
    ຖ້າ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ສົ່ງຄືນ AV_SAMPLE_FMT_NONE;
    ຖ້າ (sample_fmt_info[sample_fmt].planar)
        ສົ່ງຄືນ sample_fmt;
    ສົ່ງຄືນ sample_fmt_info[sample_fmt].altform;
}

var_na *av_get_sample_fmt_string (var_na *buf, ຈຳນວນເຕັມ buf_size, ga_nanaa AVSampleFormat sample_fmt)
{
    /* print header */
    ຖ້າ (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    ບໍ່ດັ່ງນັ້ນ ຖ້າ (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    ສົ່ງຄືນ buf;
}

ຈຳນວນເຕັມ av_get_bytes_per_sample(ga_nanaa AVSampleFormat sample_fmt)
{
     ສົ່ງຄືນ sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

ຈຳນວນເຕັມ av_sample_fmt_is_planar(ga_nanaa AVSampleFormat sample_fmt)
{
     ຖ້າ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         ສົ່ງຄືນ 0;
     ສົ່ງຄືນ sample_fmt_info[sample_fmt].planar;
}

ຈຳນວນເຕັມ av_samples_get_buffer_size(ຈຳນວນເຕັມ *linesize, ຈຳນວນເຕັມ nb_channels, ຈຳນວນເຕັມ nb_samples,
                               ga_nanaa AVSampleFormat sample_fmt, ຈຳນວນເຕັມ align)
{
    ຈຳນວນເຕັມ line_size;
    ຈຳນວນເຕັມ sample_size = av_get_bytes_per_sample(sample_fmt);
    ຈຳນວນເຕັມ planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    ຖ້າ (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        ສົ່ງຄືນ AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    ຖ້າ (!align) {
        ຖ້າ (nb_samples > INT_MAX - 31)
            ສົ່ງຄືນ AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    ຖ້າ (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        ສົ່ງຄືນ AVERROR(EINVAL);

    line_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    ຖ້າ (linesize)
        *linesize = line_size;

    ສົ່ງຄືນ planar ? line_size * nb_channels : line_size;
}

ຈຳນວນເຕັມ av_samples_fill_arrays(uint8_t **audio_data, ຈຳນວນເຕັມ *linesize,
                           const uint8_t *buf, ຈຳນວນເຕັມ nb_channels, ຈຳນວນເຕັມ nb_samples,
                           ga_nanaa AVSampleFormat sample_fmt, ຈຳນວນເຕັມ align)
{
    ຈຳນວນເຕັມ ch, planar, buf_size, line_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&line_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    ຖ້າ (buf_size < 0)
        ສົ່ງຄືນ buf_size;

    ຖ້າ (linesize)
        *linesize = line_size;

    memset(audio_data, 0, planar
                          ? parimaa_na(*audio_data) * nb_channels
                          : parimaa_na(*audio_data));

    ຖ້າ (!buf)
        ສົ່ງຄືນ buf_size;

    audio_data[0] = (uint8_t *)buf;
    ສຳລັບ (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + line_size;

    ສົ່ງຄືນ buf_size;
}

ຈຳນວນເຕັມ av_samples_alloc(uint8_t **audio_data, ຈຳນວນເຕັມ *linesize, ຈຳນວນເຕັມ nb_channels,
                     ຈຳນວນເຕັມ nb_samples, ga_nanaa AVSampleFormat sample_fmt, ຈຳນວນເຕັມ align)
{
    uint8_t *buf;
    ຈຳນວນເຕັມ size = av_samples_get_buffer_size(NULL, nb_channels, nb_samples,
                                          sample_fmt, align);
    ຖ້າ (size < 0)
        ສົ່ງຄືນ size;

    buf = av_malloc(size);
    ຖ້າ (!buf)
        ສົ່ງຄືນ AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    ຖ້າ (size < 0) {
        av_free(buf);
        ສົ່ງຄືນ size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    ສົ່ງຄືນ size;
}

ຈຳນວນເຕັມ av_samples_alloc_array_and_samples(uint8_t ***audio_data, ຈຳນວນເຕັມ *linesize, ຈຳນວນເຕັມ nb_channels,
                                       ຈຳນວນເຕັມ nb_samples, ga_nanaa AVSampleFormat sample_fmt, ຈຳນວນເຕັມ align)
{
    ຈຳນວນເຕັມ ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, parimaa_na(**audio_data));
    ຖ້າ (!*audio_data)
        ສົ່ງຄືນ AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    ຖ້າ (ret < 0)
        av_freep(audio_data);
    ສົ່ງຄືນ ret;
}

ຈຳນວນເຕັມ av_samples_copy(uint8_t * const *dst, uint8_t * const *src, ຈຳນວນເຕັມ dst_offset,
                    ຈຳນວນເຕັມ src_offset, ຈຳນວນເຕັມ nb_samples, ຈຳນວນເຕັມ nb_channels,
                    ga_nanaa AVSampleFormat sample_fmt)
{
    ຈຳນວນເຕັມ planar      = av_sample_fmt_is_planar(sample_fmt);
    ຈຳນວນເຕັມ planes      = planar ? nb_channels : 1;
    ຈຳນວນເຕັມ block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ຈຳນວນເຕັມ data_size   = nb_samples * block_align;
    ຈຳນວນເຕັມ i;

    dst_offset *= block_align;
    src_offset *= block_align;

    ຖ້າ((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        ສຳລັບ (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } ບໍ່ດັ່ງນັ້ນ {
        ສຳລັບ (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    ສົ່ງຄືນ 0;
}

ຈຳນວນເຕັມ av_samples_set_silence(uint8_t * const *audio_data, ຈຳນວນເຕັມ offset, ຈຳນວນເຕັມ nb_samples,
                           ຈຳນວນເຕັມ nb_channels, ga_nanaa AVSampleFormat sample_fmt)
{
    ຈຳນວນເຕັມ planar      = av_sample_fmt_is_planar(sample_fmt);
    ຈຳນວນເຕັມ planes      = planar ? nb_channels : 1;
    ຈຳນວນເຕັມ block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ຈຳນວນເຕັມ data_size   = nb_samples * block_align;
    ຈຳນວນເຕັມ fill_char, i;

    ຖ້າ (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    ບໍ່ດັ່ງນັ້ນ ຖ້າ (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    ບໍ່ດັ່ງນັ້ນ
        fill_char = 0x00;

    offset *= block_align;

    ສຳລັບ (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    ສົ່ງຄືນ 0;
}
