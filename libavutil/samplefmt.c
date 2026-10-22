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

typedef struct SampleFmtInfo {
    char name[8];
    số_nguyên bits;
    số_nguyên planar;
    enum AVSampleFormat altform; ///< planar<->packed alternative form
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

const char *av_get_sample_fmt_name(enum AVSampleFormat sample_fmt)
{
    nếu (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        trả_về NULL;
    trả_về sample_fmt_info[sample_fmt].name;
}

enum AVSampleFormat av_get_sample_fmt(const char *name)
{
    số_nguyên i;

    cho (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        nếu (!strcmp(sample_fmt_info[i].name, name))
            trả_về i;
    trả_về AV_SAMPLE_FMT_NONE;
}

enum AVSampleFormat av_get_alt_sample_fmt(enum AVSampleFormat sample_fmt, số_nguyên planar)
{
    nếu (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        trả_về AV_SAMPLE_FMT_NONE;
    nếu (sample_fmt_info[sample_fmt].planar == planar)
        trả_về sample_fmt;
    trả_về sample_fmt_info[sample_fmt].altform;
}

enum AVSampleFormat av_get_packed_sample_fmt(enum AVSampleFormat sample_fmt)
{
    nếu (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        trả_về AV_SAMPLE_FMT_NONE;
    nếu (sample_fmt_info[sample_fmt].planar)
        trả_về sample_fmt_info[sample_fmt].altform;
    trả_về sample_fmt;
}

enum AVSampleFormat av_get_planar_sample_fmt(enum AVSampleFormat sample_fmt)
{
    nếu (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        trả_về AV_SAMPLE_FMT_NONE;
    nếu (sample_fmt_info[sample_fmt].planar)
        trả_về sample_fmt;
    trả_về sample_fmt_info[sample_fmt].altform;
}

char *av_get_sample_fmt_string (char *buf, số_nguyên buf_size, enum AVSampleFormat sample_fmt)
{
    /* print header */
    nếu (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    không_thì nếu (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    trả_về buf;
}

số_nguyên av_get_bytes_per_sample(enum AVSampleFormat sample_fmt)
{
     trả_về sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

số_nguyên av_sample_fmt_is_planar(enum AVSampleFormat sample_fmt)
{
     nếu (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         trả_về 0;
     trả_về sample_fmt_info[sample_fmt].planar;
}

số_nguyên av_samples_get_buffer_size(số_nguyên *linesize, số_nguyên nb_channels, số_nguyên nb_samples,
                               enum AVSampleFormat sample_fmt, số_nguyên align)
{
    số_nguyên line_size;
    số_nguyên sample_size = av_get_bytes_per_sample(sample_fmt);
    số_nguyên planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    nếu (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        trả_về AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    nếu (!align) {
        nếu (nb_samples > INT_MAX - 31)
            trả_về AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    nếu (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        trả_về AVERROR(EINVAL);

    line_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    nếu (linesize)
        *linesize = line_size;

    trả_về planar ? line_size * nb_channels : line_size;
}

số_nguyên av_samples_fill_arrays(uint8_t **audio_data, số_nguyên *linesize,
                           const uint8_t *buf, số_nguyên nb_channels, số_nguyên nb_samples,
                           enum AVSampleFormat sample_fmt, số_nguyên align)
{
    số_nguyên ch, planar, buf_size, line_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&line_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    nếu (buf_size < 0)
        trả_về buf_size;

    nếu (linesize)
        *linesize = line_size;

    memset(audio_data, 0, planar
                          ? sizeof(*audio_data) * nb_channels
                          : sizeof(*audio_data));

    nếu (!buf)
        trả_về buf_size;

    audio_data[0] = (uint8_t *)buf;
    cho (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + line_size;

    trả_về buf_size;
}

số_nguyên av_samples_alloc(uint8_t **audio_data, số_nguyên *linesize, số_nguyên nb_channels,
                     số_nguyên nb_samples, enum AVSampleFormat sample_fmt, số_nguyên align)
{
    uint8_t *buf;
    số_nguyên size = av_samples_get_buffer_size(NULL, nb_channels, nb_samples,
                                          sample_fmt, align);
    nếu (size < 0)
        trả_về size;

    buf = av_malloc(size);
    nếu (!buf)
        trả_về AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    nếu (size < 0) {
        av_free(buf);
        trả_về size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    trả_về size;
}

số_nguyên av_samples_alloc_array_and_samples(uint8_t ***audio_data, số_nguyên *linesize, số_nguyên nb_channels,
                                       số_nguyên nb_samples, enum AVSampleFormat sample_fmt, số_nguyên align)
{
    số_nguyên ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, sizeof(**audio_data));
    nếu (!*audio_data)
        trả_về AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    nếu (ret < 0)
        av_freep(audio_data);
    trả_về ret;
}

số_nguyên av_samples_copy(uint8_t * const *dst, uint8_t * const *src, số_nguyên dst_offset,
                    số_nguyên src_offset, số_nguyên nb_samples, số_nguyên nb_channels,
                    enum AVSampleFormat sample_fmt)
{
    số_nguyên planar      = av_sample_fmt_is_planar(sample_fmt);
    số_nguyên planes      = planar ? nb_channels : 1;
    số_nguyên block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    số_nguyên data_size   = nb_samples * block_align;
    số_nguyên i;

    dst_offset *= block_align;
    src_offset *= block_align;

    nếu((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        cho (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } không_thì {
        cho (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    trả_về 0;
}

số_nguyên av_samples_set_silence(uint8_t * const *audio_data, số_nguyên offset, số_nguyên nb_samples,
                           số_nguyên nb_channels, enum AVSampleFormat sample_fmt)
{
    số_nguyên planar      = av_sample_fmt_is_planar(sample_fmt);
    số_nguyên planes      = planar ? nb_channels : 1;
    số_nguyên block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    số_nguyên data_size   = nb_samples * block_align;
    số_nguyên fill_char, i;

    nếu (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    không_thì nếu (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    không_thì
        fill_char = 0x00;

    offset *= block_align;

    cho (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    trả_về 0;
}
