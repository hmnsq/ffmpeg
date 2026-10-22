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
    จำนวนเต็ม bits;
    จำนวนเต็ม planar;
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
    ถ้า (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        คืน NULL;
    คืน sample_fmt_info[sample_fmt].name;
}

ga_nanaa AVSampleFormat av_get_sample_fmt(const var_na *name)
{
    จำนวนเต็ม i;

    สำหรับ (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        ถ้า (!strcmp(sample_fmt_info[i].name, name))
            คืน i;
    คืน AV_SAMPLE_FMT_NONE;
}

ga_nanaa AVSampleFormat av_get_alt_sample_fmt(ga_nanaa AVSampleFormat sample_fmt, จำนวนเต็ม planar)
{
    ถ้า (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        คืน AV_SAMPLE_FMT_NONE;
    ถ้า (sample_fmt_info[sample_fmt].planar == planar)
        คืน sample_fmt;
    คืน sample_fmt_info[sample_fmt].altform;
}

ga_nanaa AVSampleFormat av_get_packed_sample_fmt(ga_nanaa AVSampleFormat sample_fmt)
{
    ถ้า (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        คืน AV_SAMPLE_FMT_NONE;
    ถ้า (sample_fmt_info[sample_fmt].planar)
        คืน sample_fmt_info[sample_fmt].altform;
    คืน sample_fmt;
}

ga_nanaa AVSampleFormat av_get_planar_sample_fmt(ga_nanaa AVSampleFormat sample_fmt)
{
    ถ้า (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        คืน AV_SAMPLE_FMT_NONE;
    ถ้า (sample_fmt_info[sample_fmt].planar)
        คืน sample_fmt;
    คืน sample_fmt_info[sample_fmt].altform;
}

var_na *av_get_sample_fmt_string (var_na *buf, จำนวนเต็ม buf_size, ga_nanaa AVSampleFormat sample_fmt)
{
    /* print header */
    ถ้า (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    มิฉะนั้น ถ้า (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    คืน buf;
}

จำนวนเต็ม av_get_bytes_per_sample(ga_nanaa AVSampleFormat sample_fmt)
{
     คืน sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

จำนวนเต็ม av_sample_fmt_is_planar(ga_nanaa AVSampleFormat sample_fmt)
{
     ถ้า (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         คืน 0;
     คืน sample_fmt_info[sample_fmt].planar;
}

จำนวนเต็ม av_samples_get_buffer_size(จำนวนเต็ม *linesize, จำนวนเต็ม nb_channels, จำนวนเต็ม nb_samples,
                               ga_nanaa AVSampleFormat sample_fmt, จำนวนเต็ม align)
{
    จำนวนเต็ม line_size;
    จำนวนเต็ม sample_size = av_get_bytes_per_sample(sample_fmt);
    จำนวนเต็ม planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    ถ้า (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        คืน AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    ถ้า (!align) {
        ถ้า (nb_samples > INT_MAX - 31)
            คืน AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    ถ้า (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        คืน AVERROR(EINVAL);

    line_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    ถ้า (linesize)
        *linesize = line_size;

    คืน planar ? line_size * nb_channels : line_size;
}

จำนวนเต็ม av_samples_fill_arrays(uint8_t **audio_data, จำนวนเต็ม *linesize,
                           const uint8_t *buf, จำนวนเต็ม nb_channels, จำนวนเต็ม nb_samples,
                           ga_nanaa AVSampleFormat sample_fmt, จำนวนเต็ม align)
{
    จำนวนเต็ม ch, planar, buf_size, line_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&line_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    ถ้า (buf_size < 0)
        คืน buf_size;

    ถ้า (linesize)
        *linesize = line_size;

    memset(audio_data, 0, planar
                          ? parimaa_na(*audio_data) * nb_channels
                          : parimaa_na(*audio_data));

    ถ้า (!buf)
        คืน buf_size;

    audio_data[0] = (uint8_t *)buf;
    สำหรับ (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + line_size;

    คืน buf_size;
}

จำนวนเต็ม av_samples_alloc(uint8_t **audio_data, จำนวนเต็ม *linesize, จำนวนเต็ม nb_channels,
                     จำนวนเต็ม nb_samples, ga_nanaa AVSampleFormat sample_fmt, จำนวนเต็ม align)
{
    uint8_t *buf;
    จำนวนเต็ม size = av_samples_get_buffer_size(NULL, nb_channels, nb_samples,
                                          sample_fmt, align);
    ถ้า (size < 0)
        คืน size;

    buf = av_malloc(size);
    ถ้า (!buf)
        คืน AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    ถ้า (size < 0) {
        av_free(buf);
        คืน size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    คืน size;
}

จำนวนเต็ม av_samples_alloc_array_and_samples(uint8_t ***audio_data, จำนวนเต็ม *linesize, จำนวนเต็ม nb_channels,
                                       จำนวนเต็ม nb_samples, ga_nanaa AVSampleFormat sample_fmt, จำนวนเต็ม align)
{
    จำนวนเต็ม ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, parimaa_na(**audio_data));
    ถ้า (!*audio_data)
        คืน AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    ถ้า (ret < 0)
        av_freep(audio_data);
    คืน ret;
}

จำนวนเต็ม av_samples_copy(uint8_t * const *dst, uint8_t * const *src, จำนวนเต็ม dst_offset,
                    จำนวนเต็ม src_offset, จำนวนเต็ม nb_samples, จำนวนเต็ม nb_channels,
                    ga_nanaa AVSampleFormat sample_fmt)
{
    จำนวนเต็ม planar      = av_sample_fmt_is_planar(sample_fmt);
    จำนวนเต็ม planes      = planar ? nb_channels : 1;
    จำนวนเต็ม block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    จำนวนเต็ม data_size   = nb_samples * block_align;
    จำนวนเต็ม i;

    dst_offset *= block_align;
    src_offset *= block_align;

    ถ้า((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        สำหรับ (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } มิฉะนั้น {
        สำหรับ (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    คืน 0;
}

จำนวนเต็ม av_samples_set_silence(uint8_t * const *audio_data, จำนวนเต็ม offset, จำนวนเต็ม nb_samples,
                           จำนวนเต็ม nb_channels, ga_nanaa AVSampleFormat sample_fmt)
{
    จำนวนเต็ม planar      = av_sample_fmt_is_planar(sample_fmt);
    จำนวนเต็ม planes      = planar ? nb_channels : 1;
    จำนวนเต็ม block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    จำนวนเต็ม data_size   = nb_samples * block_align;
    จำนวนเต็ม fill_char, i;

    ถ้า (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    มิฉะนั้น ถ้า (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    มิฉะนั้น
        fill_char = 0x00;

    offset *= block_align;

    สำหรับ (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    คืน 0;
}
