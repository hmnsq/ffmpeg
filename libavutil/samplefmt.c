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

#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "samplefmt.h"

#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>

തരനിർവചനം ഘടന SampleFmtInfo {
    അക്ഷരം name[8];
    പൂർണ്ണസംഖ്യ bits;
    പൂർണ്ണസംഖ്യ planar;
    എണ്ണൽ AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
സ്ഥിതം സ്ഥിരം SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
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

സ്ഥിരം അക്ഷരം *av_get_sample_fmt_name(എണ്ണൽ AVSampleFormat sample_fmt)
{
    എങ്കിൽ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        തിരികെ ശൂന്യ;
    തിരികെ sample_fmt_info[sample_fmt].name;
}

എണ്ണൽ AVSampleFormat av_get_sample_fmt(സ്ഥിരം അക്ഷരം *name)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        എങ്കിൽ (!strcmp(sample_fmt_info[i].name, name))
            തിരികെ i;
    തിരികെ AV_SAMPLE_FMT_NONE;
}

എണ്ണൽ AVSampleFormat av_get_alt_sample_fmt(എണ്ണൽ AVSampleFormat sample_fmt, പൂർണ്ണസംഖ്യ planar)
{
    എങ്കിൽ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        തിരികെ AV_SAMPLE_FMT_NONE;
    എങ്കിൽ (sample_fmt_info[sample_fmt].planar == planar)
        തിരികെ sample_fmt;
    തിരികെ sample_fmt_info[sample_fmt].altform;
}

എണ്ണൽ AVSampleFormat av_get_packed_sample_fmt(എണ്ണൽ AVSampleFormat sample_fmt)
{
    എങ്കിൽ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        തിരികെ AV_SAMPLE_FMT_NONE;
    എങ്കിൽ (sample_fmt_info[sample_fmt].planar)
        തിരികെ sample_fmt_info[sample_fmt].altform;
    തിരികെ sample_fmt;
}

എണ്ണൽ AVSampleFormat av_get_planar_sample_fmt(എണ്ണൽ AVSampleFormat sample_fmt)
{
    എങ്കിൽ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        തിരികെ AV_SAMPLE_FMT_NONE;
    എങ്കിൽ (sample_fmt_info[sample_fmt].planar)
        തിരികെ sample_fmt;
    തിരികെ sample_fmt_info[sample_fmt].altform;
}

അക്ഷരം *av_get_sample_fmt_string (അക്ഷരം *buf, പൂർണ്ണസംഖ്യ buf_size, എണ്ണൽ AVSampleFormat sample_fmt)
{
    /* print header */
    എങ്കിൽ (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    അല്ലെങ്കിൽ എങ്കിൽ (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    തിരികെ buf;
}

പൂർണ്ണസംഖ്യ av_get_bytes_per_sample(എണ്ണൽ AVSampleFormat sample_fmt)
{
     തിരികെ sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

പൂർണ്ണസംഖ്യ av_sample_fmt_is_planar(എണ്ണൽ AVSampleFormat sample_fmt)
{
     എങ്കിൽ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         തിരികെ 0;
     തിരികെ sample_fmt_info[sample_fmt].planar;
}

പൂർണ്ണസംഖ്യ av_samples_get_buffer_size(പൂർണ്ണസംഖ്യ *linesize, പൂർണ്ണസംഖ്യ nb_channels, പൂർണ്ണസംഖ്യ nb_samples,
                               എണ്ണൽ AVSampleFormat sample_fmt, പൂർണ്ണസംഖ്യ align)
{
    പൂർണ്ണസംഖ്യ വരി_size;
    പൂർണ്ണസംഖ്യ sample_size = av_get_bytes_per_sample(sample_fmt);
    പൂർണ്ണസംഖ്യ planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    എങ്കിൽ (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        തിരികെ AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    എങ്കിൽ (!align) {
        എങ്കിൽ (nb_samples > INT_MAX - 31)
            തിരികെ AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    എങ്കിൽ (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        തിരികെ AVERROR(EINVAL);

    വരി_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    എങ്കിൽ (linesize)
        *linesize = വരി_size;

    തിരികെ planar ? വരി_size * nb_channels : വരി_size;
}

പൂർണ്ണസംഖ്യ av_samples_fill_arrays(uint8_t **audio_data, പൂർണ്ണസംഖ്യ *linesize,
                           സ്ഥിരം uint8_t *buf, പൂർണ്ണസംഖ്യ nb_channels, പൂർണ്ണസംഖ്യ nb_samples,
                           എണ്ണൽ AVSampleFormat sample_fmt, പൂർണ്ണസംഖ്യ align)
{
    പൂർണ്ണസംഖ്യ ch, planar, buf_size, വരി_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&വരി_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    എങ്കിൽ (buf_size < 0)
        തിരികെ buf_size;

    എങ്കിൽ (linesize)
        *linesize = വരി_size;

    memset(audio_data, 0, planar
                          ? വലുപ്പം(*audio_data) * nb_channels
                          : വലുപ്പം(*audio_data));

    എങ്കിൽ (!buf)
        തിരികെ buf_size;

    audio_data[0] = (uint8_t *)buf;
    വേണ്ടി (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + വരി_size;

    തിരികെ buf_size;
}

പൂർണ്ണസംഖ്യ av_samples_alloc(uint8_t **audio_data, പൂർണ്ണസംഖ്യ *linesize, പൂർണ്ണസംഖ്യ nb_channels,
                     പൂർണ്ണസംഖ്യ nb_samples, എണ്ണൽ AVSampleFormat sample_fmt, പൂർണ്ണസംഖ്യ align)
{
    uint8_t *buf;
    പൂർണ്ണസംഖ്യ size = av_samples_get_buffer_size(ശൂന്യ, nb_channels, nb_samples,
                                          sample_fmt, align);
    എങ്കിൽ (size < 0)
        തിരികെ size;

    buf = av_malloc(size);
    എങ്കിൽ (!buf)
        തിരികെ AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    എങ്കിൽ (size < 0) {
        av_free(buf);
        തിരികെ size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    തിരികെ size;
}

പൂർണ്ണസംഖ്യ av_samples_alloc_array_and_samples(uint8_t ***audio_data, പൂർണ്ണസംഖ്യ *linesize, പൂർണ്ണസംഖ്യ nb_channels,
                                       പൂർണ്ണസംഖ്യ nb_samples, എണ്ണൽ AVSampleFormat sample_fmt, പൂർണ്ണസംഖ്യ align)
{
    പൂർണ്ണസംഖ്യ ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, വലുപ്പം(**audio_data));
    എങ്കിൽ (!*audio_data)
        തിരികെ AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    എങ്കിൽ (ret < 0)
        av_freep(audio_data);
    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_samples_copy(uint8_t * സ്ഥിരം *dst, uint8_t * സ്ഥിരം *src, പൂർണ്ണസംഖ്യ dst_offset,
                    പൂർണ്ണസംഖ്യ src_offset, പൂർണ്ണസംഖ്യ nb_samples, പൂർണ്ണസംഖ്യ nb_channels,
                    എണ്ണൽ AVSampleFormat sample_fmt)
{
    പൂർണ്ണസംഖ്യ planar      = av_sample_fmt_is_planar(sample_fmt);
    പൂർണ്ണസംഖ്യ planes      = planar ? nb_channels : 1;
    പൂർണ്ണസംഖ്യ block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    പൂർണ്ണസംഖ്യ data_size   = nb_samples * block_align;
    പൂർണ്ണസംഖ്യ i;

    dst_offset *= block_align;
    src_offset *= block_align;

    എങ്കിൽ((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        വേണ്ടി (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } അല്ലെങ്കിൽ {
        വേണ്ടി (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_samples_set_silence(uint8_t * സ്ഥിരം *audio_data, പൂർണ്ണസംഖ്യ offset, പൂർണ്ണസംഖ്യ nb_samples,
                           പൂർണ്ണസംഖ്യ nb_channels, എണ്ണൽ AVSampleFormat sample_fmt)
{
    പൂർണ്ണസംഖ്യ planar      = av_sample_fmt_is_planar(sample_fmt);
    പൂർണ്ണസംഖ്യ planes      = planar ? nb_channels : 1;
    പൂർണ്ണസംഖ്യ block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    പൂർണ്ണസംഖ്യ data_size   = nb_samples * block_align;
    പൂർണ്ണസംഖ്യ fill_char, i;

    എങ്കിൽ (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    അല്ലെങ്കിൽ എങ്കിൽ (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    അല്ലെങ്കിൽ
        fill_char = 0x00;

    offset *= block_align;

    വേണ്ടി (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    തിരികെ 0;
}
