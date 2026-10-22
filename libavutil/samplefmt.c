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
    цяло bits;
    цяло planar;
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
    ако (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        върни NULL;
    върни sample_fmt_info[sample_fmt].name;
}

enum AVSampleFormat av_get_sample_fmt(const char *name)
{
    цяло i;

    за (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        ако (!strcmp(sample_fmt_info[i].name, name))
            върни i;
    върни AV_SAMPLE_FMT_NONE;
}

enum AVSampleFormat av_get_alt_sample_fmt(enum AVSampleFormat sample_fmt, цяло planar)
{
    ако (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        върни AV_SAMPLE_FMT_NONE;
    ако (sample_fmt_info[sample_fmt].planar == planar)
        върни sample_fmt;
    върни sample_fmt_info[sample_fmt].altform;
}

enum AVSampleFormat av_get_packed_sample_fmt(enum AVSampleFormat sample_fmt)
{
    ако (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        върни AV_SAMPLE_FMT_NONE;
    ако (sample_fmt_info[sample_fmt].planar)
        върни sample_fmt_info[sample_fmt].altform;
    върни sample_fmt;
}

enum AVSampleFormat av_get_planar_sample_fmt(enum AVSampleFormat sample_fmt)
{
    ако (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        върни AV_SAMPLE_FMT_NONE;
    ако (sample_fmt_info[sample_fmt].planar)
        върни sample_fmt;
    върни sample_fmt_info[sample_fmt].altform;
}

char *av_get_sample_fmt_string (char *buf, цяло buf_size, enum AVSampleFormat sample_fmt)
{
    /* print header */
    ако (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    иначе ако (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    върни buf;
}

цяло av_get_bytes_per_sample(enum AVSampleFormat sample_fmt)
{
     върни sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

цяло av_sample_fmt_is_planar(enum AVSampleFormat sample_fmt)
{
     ако (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         върни 0;
     върни sample_fmt_info[sample_fmt].planar;
}

цяло av_samples_get_buffer_size(цяло *linesize, цяло nb_channels, цяло nb_samples,
                               enum AVSampleFormat sample_fmt, цяло align)
{
    цяло line_size;
    цяло sample_size = av_get_bytes_per_sample(sample_fmt);
    цяло planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    ако (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        върни AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    ако (!align) {
        ако (nb_samples > INT_MAX - 31)
            върни AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    ако (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        върни AVERROR(EINVAL);

    line_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    ако (linesize)
        *linesize = line_size;

    върни planar ? line_size * nb_channels : line_size;
}

цяло av_samples_fill_arrays(uint8_t **audio_data, цяло *linesize,
                           const uint8_t *buf, цяло nb_channels, цяло nb_samples,
                           enum AVSampleFormat sample_fmt, цяло align)
{
    цяло ch, planar, buf_size, line_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&line_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    ако (buf_size < 0)
        върни buf_size;

    ако (linesize)
        *linesize = line_size;

    memset(audio_data, 0, planar
                          ? sizeof(*audio_data) * nb_channels
                          : sizeof(*audio_data));

    ако (!buf)
        върни buf_size;

    audio_data[0] = (uint8_t *)buf;
    за (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + line_size;

    върни buf_size;
}

цяло av_samples_alloc(uint8_t **audio_data, цяло *linesize, цяло nb_channels,
                     цяло nb_samples, enum AVSampleFormat sample_fmt, цяло align)
{
    uint8_t *buf;
    цяло size = av_samples_get_buffer_size(NULL, nb_channels, nb_samples,
                                          sample_fmt, align);
    ако (size < 0)
        върни size;

    buf = av_malloc(size);
    ако (!buf)
        върни AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    ако (size < 0) {
        av_free(buf);
        върни size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    върни size;
}

цяло av_samples_alloc_array_and_samples(uint8_t ***audio_data, цяло *linesize, цяло nb_channels,
                                       цяло nb_samples, enum AVSampleFormat sample_fmt, цяло align)
{
    цяло ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, sizeof(**audio_data));
    ако (!*audio_data)
        върни AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    ако (ret < 0)
        av_freep(audio_data);
    върни ret;
}

цяло av_samples_copy(uint8_t * const *dst, uint8_t * const *src, цяло dst_offset,
                    цяло src_offset, цяло nb_samples, цяло nb_channels,
                    enum AVSampleFormat sample_fmt)
{
    цяло planar      = av_sample_fmt_is_planar(sample_fmt);
    цяло planes      = planar ? nb_channels : 1;
    цяло block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    цяло data_size   = nb_samples * block_align;
    цяло i;

    dst_offset *= block_align;
    src_offset *= block_align;

    ако((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        за (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } иначе {
        за (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    върни 0;
}

цяло av_samples_set_silence(uint8_t * const *audio_data, цяло offset, цяло nb_samples,
                           цяло nb_channels, enum AVSampleFormat sample_fmt)
{
    цяло planar      = av_sample_fmt_is_planar(sample_fmt);
    цяло planes      = planar ? nb_channels : 1;
    цяло block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    цяло data_size   = nb_samples * block_align;
    цяло fill_char, i;

    ако (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    иначе ако (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    иначе
        fill_char = 0x00;

    offset *= block_align;

    за (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    върни 0;
}
