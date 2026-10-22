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
    පූර්ණ_සංඛ්‍යා bits;
    පූර්ණ_සංඛ්‍යා planar;
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
    නම් (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ආපසු NULL;
    ආපසු sample_fmt_info[sample_fmt].name;
}

ga_nanaa AVSampleFormat av_get_sample_fmt(const var_na *name)
{
    පූර්ණ_සංඛ්‍යා i;

    සඳහා (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        නම් (!strcmp(sample_fmt_info[i].name, name))
            ආපසු i;
    ආපසු AV_SAMPLE_FMT_NONE;
}

ga_nanaa AVSampleFormat av_get_alt_sample_fmt(ga_nanaa AVSampleFormat sample_fmt, පූර්ණ_සංඛ්‍යා planar)
{
    නම් (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ආපසු AV_SAMPLE_FMT_NONE;
    නම් (sample_fmt_info[sample_fmt].planar == planar)
        ආපසු sample_fmt;
    ආපසු sample_fmt_info[sample_fmt].altform;
}

ga_nanaa AVSampleFormat av_get_packed_sample_fmt(ga_nanaa AVSampleFormat sample_fmt)
{
    නම් (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ආපසු AV_SAMPLE_FMT_NONE;
    නම් (sample_fmt_info[sample_fmt].planar)
        ආපසු sample_fmt_info[sample_fmt].altform;
    ආපසු sample_fmt;
}

ga_nanaa AVSampleFormat av_get_planar_sample_fmt(ga_nanaa AVSampleFormat sample_fmt)
{
    නම් (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ආපසු AV_SAMPLE_FMT_NONE;
    නම් (sample_fmt_info[sample_fmt].planar)
        ආපසු sample_fmt;
    ආපසු sample_fmt_info[sample_fmt].altform;
}

var_na *av_get_sample_fmt_string (var_na *buf, පූර්ණ_සංඛ්‍යා buf_size, ga_nanaa AVSampleFormat sample_fmt)
{
    /* print header */
    නම් (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    නැතහොත් නම් (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    ආපසු buf;
}

පූර්ණ_සංඛ්‍යා av_get_bytes_per_sample(ga_nanaa AVSampleFormat sample_fmt)
{
     ආපසු sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

පූර්ණ_සංඛ්‍යා av_sample_fmt_is_planar(ga_nanaa AVSampleFormat sample_fmt)
{
     නම් (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         ආපසු 0;
     ආපසු sample_fmt_info[sample_fmt].planar;
}

පූර්ණ_සංඛ්‍යා av_samples_get_buffer_size(පූර්ණ_සංඛ්‍යා *linesize, පූර්ණ_සංඛ්‍යා nb_channels, පූර්ණ_සංඛ්‍යා nb_samples,
                               ga_nanaa AVSampleFormat sample_fmt, පූර්ණ_සංඛ්‍යා align)
{
    පූර්ණ_සංඛ්‍යා line_size;
    පූර්ණ_සංඛ්‍යා sample_size = av_get_bytes_per_sample(sample_fmt);
    පූර්ණ_සංඛ්‍යා planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    නම් (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        ආපසු AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    නම් (!align) {
        නම් (nb_samples > INT_MAX - 31)
            ආපසු AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    නම් (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        ආපසු AVERROR(EINVAL);

    line_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    නම් (linesize)
        *linesize = line_size;

    ආපසු planar ? line_size * nb_channels : line_size;
}

පූර්ණ_සංඛ්‍යා av_samples_fill_arrays(uint8_t **audio_data, පූර්ණ_සංඛ්‍යා *linesize,
                           const uint8_t *buf, පූර්ණ_සංඛ්‍යා nb_channels, පූර්ණ_සංඛ්‍යා nb_samples,
                           ga_nanaa AVSampleFormat sample_fmt, පූර්ණ_සංඛ්‍යා align)
{
    පූර්ණ_සංඛ්‍යා ch, planar, buf_size, line_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&line_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    නම් (buf_size < 0)
        ආපසු buf_size;

    නම් (linesize)
        *linesize = line_size;

    memset(audio_data, 0, planar
                          ? parimaa_na(*audio_data) * nb_channels
                          : parimaa_na(*audio_data));

    නම් (!buf)
        ආපසු buf_size;

    audio_data[0] = (uint8_t *)buf;
    සඳහා (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + line_size;

    ආපසු buf_size;
}

පූර්ණ_සංඛ්‍යා av_samples_alloc(uint8_t **audio_data, පූර්ණ_සංඛ්‍යා *linesize, පූර්ණ_සංඛ්‍යා nb_channels,
                     පූර්ණ_සංඛ්‍යා nb_samples, ga_nanaa AVSampleFormat sample_fmt, පූර්ණ_සංඛ්‍යා align)
{
    uint8_t *buf;
    පූර්ණ_සංඛ්‍යා size = av_samples_get_buffer_size(NULL, nb_channels, nb_samples,
                                          sample_fmt, align);
    නම් (size < 0)
        ආපසු size;

    buf = av_malloc(size);
    නම් (!buf)
        ආපසු AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    නම් (size < 0) {
        av_free(buf);
        ආපසු size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    ආපසු size;
}

පූර්ණ_සංඛ්‍යා av_samples_alloc_array_and_samples(uint8_t ***audio_data, පූර්ණ_සංඛ්‍යා *linesize, පූර්ණ_සංඛ්‍යා nb_channels,
                                       පූර්ණ_සංඛ්‍යා nb_samples, ga_nanaa AVSampleFormat sample_fmt, පූර්ණ_සංඛ්‍යා align)
{
    පූර්ණ_සංඛ්‍යා ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, parimaa_na(**audio_data));
    නම් (!*audio_data)
        ආපසු AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    නම් (ret < 0)
        av_freep(audio_data);
    ආපසු ret;
}

පූර්ණ_සංඛ්‍යා av_samples_copy(uint8_t * const *dst, uint8_t * const *src, පූර්ණ_සංඛ්‍යා dst_offset,
                    පූර්ණ_සංඛ්‍යා src_offset, පූර්ණ_සංඛ්‍යා nb_samples, පූර්ණ_සංඛ්‍යා nb_channels,
                    ga_nanaa AVSampleFormat sample_fmt)
{
    පූර්ණ_සංඛ්‍යා planar      = av_sample_fmt_is_planar(sample_fmt);
    පූර්ණ_සංඛ්‍යා planes      = planar ? nb_channels : 1;
    පූර්ණ_සංඛ්‍යා block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    පූර්ණ_සංඛ්‍යා data_size   = nb_samples * block_align;
    පූර්ණ_සංඛ්‍යා i;

    dst_offset *= block_align;
    src_offset *= block_align;

    නම්((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        සඳහා (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } නැතහොත් {
        සඳහා (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_samples_set_silence(uint8_t * const *audio_data, පූර්ණ_සංඛ්‍යා offset, පූර්ණ_සංඛ්‍යා nb_samples,
                           පූර්ණ_සංඛ්‍යා nb_channels, ga_nanaa AVSampleFormat sample_fmt)
{
    පූර්ණ_සංඛ්‍යා planar      = av_sample_fmt_is_planar(sample_fmt);
    පූර්ණ_සංඛ්‍යා planes      = planar ? nb_channels : 1;
    පූර්ණ_සංඛ්‍යා block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    පූර්ණ_සංඛ්‍යා data_size   = nb_samples * block_align;
    පූර්ණ_සංඛ්‍යා fill_char, i;

    නම් (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    නැතහොත් නම් (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    නැතහොත්
        fill_char = 0x00;

    offset *= block_align;

    සඳහා (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    ආපසු 0;
}
