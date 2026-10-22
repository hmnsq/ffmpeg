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

#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "macros.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "samplefmt.h"

#અન્તર્ભાવ <limits.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>

પ્રકારવ્યાખ્યા સંરચના SampleFmtInfo {
    અક્ષર name[8];
    પૂર્ણાંક bits;
    પૂર્ણાંક planar;
    ગણના AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
સ્થિર અચલ SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
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

અચલ અક્ષર *av_get_sample_fmt_name(ગણના AVSampleFormat sample_fmt)
{
    જો (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        પાછા ખાલી;
    પાછા sample_fmt_info[sample_fmt].name;
}

ગણના AVSampleFormat av_get_sample_fmt(અચલ અક્ષર *name)
{
    પૂર્ણાંક i;

    માટે (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        જો (!strcmp(sample_fmt_info[i].name, name))
            પાછા i;
    પાછા AV_SAMPLE_FMT_NONE;
}

ગણના AVSampleFormat av_get_alt_sample_fmt(ગણના AVSampleFormat sample_fmt, પૂર્ણાંક planar)
{
    જો (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        પાછા AV_SAMPLE_FMT_NONE;
    જો (sample_fmt_info[sample_fmt].planar == planar)
        પાછા sample_fmt;
    પાછા sample_fmt_info[sample_fmt].altform;
}

ગણના AVSampleFormat av_get_packed_sample_fmt(ગણના AVSampleFormat sample_fmt)
{
    જો (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        પાછા AV_SAMPLE_FMT_NONE;
    જો (sample_fmt_info[sample_fmt].planar)
        પાછા sample_fmt_info[sample_fmt].altform;
    પાછા sample_fmt;
}

ગણના AVSampleFormat av_get_planar_sample_fmt(ગણના AVSampleFormat sample_fmt)
{
    જો (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        પાછા AV_SAMPLE_FMT_NONE;
    જો (sample_fmt_info[sample_fmt].planar)
        પાછા sample_fmt;
    પાછા sample_fmt_info[sample_fmt].altform;
}

અક્ષર *av_get_sample_fmt_string (અક્ષર *buf, પૂર્ણાંક buf_size, ગણના AVSampleFormat sample_fmt)
{
    /* print header */
    જો (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    નહીંતર જો (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    પાછા buf;
}

પૂર્ણાંક av_get_bytes_per_sample(ગણના AVSampleFormat sample_fmt)
{
     પાછા sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

પૂર્ણાંક av_sample_fmt_is_planar(ગણના AVSampleFormat sample_fmt)
{
     જો (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         પાછા 0;
     પાછા sample_fmt_info[sample_fmt].planar;
}

પૂર્ણાંક av_samples_get_buffer_size(પૂર્ણાંક *linesize, પૂર્ણાંક nb_channels, પૂર્ણાંક nb_samples,
                               ગણના AVSampleFormat sample_fmt, પૂર્ણાંક align)
{
    પૂર્ણાંક લીટી_size;
    પૂર્ણાંક sample_size = av_get_bytes_per_sample(sample_fmt);
    પૂર્ણાંક planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    જો (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        પાછા AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    જો (!align) {
        જો (nb_samples > INT_MAX - 31)
            પાછા AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    જો (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        પાછા AVERROR(EINVAL);

    લીટી_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    જો (linesize)
        *linesize = લીટી_size;

    પાછા planar ? લીટી_size * nb_channels : લીટી_size;
}

પૂર્ણાંક av_samples_fill_arrays(uint8_t **audio_data, પૂર્ણાંક *linesize,
                           અચલ uint8_t *buf, પૂર્ણાંક nb_channels, પૂર્ણાંક nb_samples,
                           ગણના AVSampleFormat sample_fmt, પૂર્ણાંક align)
{
    પૂર્ણાંક ch, planar, buf_size, લીટી_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&લીટી_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    જો (buf_size < 0)
        પાછા buf_size;

    જો (linesize)
        *linesize = લીટી_size;

    memset(audio_data, 0, planar
                          ? કદ(*audio_data) * nb_channels
                          : કદ(*audio_data));

    જો (!buf)
        પાછા buf_size;

    audio_data[0] = (uint8_t *)buf;
    માટે (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + લીટી_size;

    પાછા buf_size;
}

પૂર્ણાંક av_samples_alloc(uint8_t **audio_data, પૂર્ણાંક *linesize, પૂર્ણાંક nb_channels,
                     પૂર્ણાંક nb_samples, ગણના AVSampleFormat sample_fmt, પૂર્ણાંક align)
{
    uint8_t *buf;
    પૂર્ણાંક size = av_samples_get_buffer_size(ખાલી, nb_channels, nb_samples,
                                          sample_fmt, align);
    જો (size < 0)
        પાછા size;

    buf = av_malloc(size);
    જો (!buf)
        પાછા AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    જો (size < 0) {
        av_free(buf);
        પાછા size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    પાછા size;
}

પૂર્ણાંક av_samples_alloc_array_and_samples(uint8_t ***audio_data, પૂર્ણાંક *linesize, પૂર્ણાંક nb_channels,
                                       પૂર્ણાંક nb_samples, ગણના AVSampleFormat sample_fmt, પૂર્ણાંક align)
{
    પૂર્ણાંક ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, કદ(**audio_data));
    જો (!*audio_data)
        પાછા AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    જો (ret < 0)
        av_freep(audio_data);
    પાછા ret;
}

પૂર્ણાંક av_samples_copy(uint8_t * અચલ *dst, uint8_t * અચલ *src, પૂર્ણાંક dst_offset,
                    પૂર્ણાંક src_offset, પૂર્ણાંક nb_samples, પૂર્ણાંક nb_channels,
                    ગણના AVSampleFormat sample_fmt)
{
    પૂર્ણાંક planar      = av_sample_fmt_is_planar(sample_fmt);
    પૂર્ણાંક planes      = planar ? nb_channels : 1;
    પૂર્ણાંક block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    પૂર્ણાંક data_size   = nb_samples * block_align;
    પૂર્ણાંક i;

    dst_offset *= block_align;
    src_offset *= block_align;

    જો((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        માટે (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } નહીંતર {
        માટે (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    પાછા 0;
}

પૂર્ણાંક av_samples_set_silence(uint8_t * અચલ *audio_data, પૂર્ણાંક offset, પૂર્ણાંક nb_samples,
                           પૂર્ણાંક nb_channels, ગણના AVSampleFormat sample_fmt)
{
    પૂર્ણાંક planar      = av_sample_fmt_is_planar(sample_fmt);
    પૂર્ણાંક planes      = planar ? nb_channels : 1;
    પૂર્ણાંક block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    પૂર્ણાંક data_size   = nb_samples * block_align;
    પૂર્ણાંક fill_char, i;

    જો (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    નહીંતર જો (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    નહીંતર
        fill_char = 0x00;

    offset *= block_align;

    માટે (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    પાછા 0;
}
