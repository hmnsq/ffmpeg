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

#அந்தர்பாவ "error.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "samplefmt.h"

#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>

வகைவரை கட்டமைப்பு SampleFmtInfo {
    எழுத்து name[8];
    முழு bits;
    முழு planar;
    எண்ணிக்கை AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
நிலையான மாறிலி SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
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

மாறிலி எழுத்து *av_get_sample_fmt_name(எண்ணிக்கை AVSampleFormat sample_fmt)
{
    எனில் (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        திரும்பு வெற்று;
    திரும்பு sample_fmt_info[sample_fmt].name;
}

எண்ணிக்கை AVSampleFormat av_get_sample_fmt(மாறிலி எழுத்து *name)
{
    முழு i;

    க்கு (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        எனில் (!strcmp(sample_fmt_info[i].name, name))
            திரும்பு i;
    திரும்பு AV_SAMPLE_FMT_NONE;
}

எண்ணிக்கை AVSampleFormat av_get_alt_sample_fmt(எண்ணிக்கை AVSampleFormat sample_fmt, முழு planar)
{
    எனில் (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        திரும்பு AV_SAMPLE_FMT_NONE;
    எனில் (sample_fmt_info[sample_fmt].planar == planar)
        திரும்பு sample_fmt;
    திரும்பு sample_fmt_info[sample_fmt].altform;
}

எண்ணிக்கை AVSampleFormat av_get_packed_sample_fmt(எண்ணிக்கை AVSampleFormat sample_fmt)
{
    எனில் (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        திரும்பு AV_SAMPLE_FMT_NONE;
    எனில் (sample_fmt_info[sample_fmt].planar)
        திரும்பு sample_fmt_info[sample_fmt].altform;
    திரும்பு sample_fmt;
}

எண்ணிக்கை AVSampleFormat av_get_planar_sample_fmt(எண்ணிக்கை AVSampleFormat sample_fmt)
{
    எனில் (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        திரும்பு AV_SAMPLE_FMT_NONE;
    எனில் (sample_fmt_info[sample_fmt].planar)
        திரும்பு sample_fmt;
    திரும்பு sample_fmt_info[sample_fmt].altform;
}

எழுத்து *av_get_sample_fmt_string (எழுத்து *buf, முழு buf_size, எண்ணிக்கை AVSampleFormat sample_fmt)
{
    /* print header */
    எனில் (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    இல்லையெனில் எனில் (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    திரும்பு buf;
}

முழு av_get_bytes_per_sample(எண்ணிக்கை AVSampleFormat sample_fmt)
{
     திரும்பு sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

முழு av_sample_fmt_is_planar(எண்ணிக்கை AVSampleFormat sample_fmt)
{
     எனில் (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         திரும்பு 0;
     திரும்பு sample_fmt_info[sample_fmt].planar;
}

முழு av_samples_get_buffer_size(முழு *linesize, முழு nb_channels, முழு nb_samples,
                               எண்ணிக்கை AVSampleFormat sample_fmt, முழு align)
{
    முழு வரி_size;
    முழு sample_size = av_get_bytes_per_sample(sample_fmt);
    முழு planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    எனில் (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        திரும்பு AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    எனில் (!align) {
        எனில் (nb_samples > INT_MAX - 31)
            திரும்பு AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    எனில் (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        திரும்பு AVERROR(EINVAL);

    வரி_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    எனில் (linesize)
        *linesize = வரி_size;

    திரும்பு planar ? வரி_size * nb_channels : வரி_size;
}

முழு av_samples_fill_arrays(uint8_t **audio_data, முழு *linesize,
                           மாறிலி uint8_t *buf, முழு nb_channels, முழு nb_samples,
                           எண்ணிக்கை AVSampleFormat sample_fmt, முழு align)
{
    முழு ch, planar, buf_size, வரி_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&வரி_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    எனில் (buf_size < 0)
        திரும்பு buf_size;

    எனில் (linesize)
        *linesize = வரி_size;

    memset(audio_data, 0, planar
                          ? அளவு(*audio_data) * nb_channels
                          : அளவு(*audio_data));

    எனில் (!buf)
        திரும்பு buf_size;

    audio_data[0] = (uint8_t *)buf;
    க்கு (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + வரி_size;

    திரும்பு buf_size;
}

முழு av_samples_alloc(uint8_t **audio_data, முழு *linesize, முழு nb_channels,
                     முழு nb_samples, எண்ணிக்கை AVSampleFormat sample_fmt, முழு align)
{
    uint8_t *buf;
    முழு size = av_samples_get_buffer_size(வெற்று, nb_channels, nb_samples,
                                          sample_fmt, align);
    எனில் (size < 0)
        திரும்பு size;

    buf = av_malloc(size);
    எனில் (!buf)
        திரும்பு AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    எனில் (size < 0) {
        av_free(buf);
        திரும்பு size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    திரும்பு size;
}

முழு av_samples_alloc_array_and_samples(uint8_t ***audio_data, முழு *linesize, முழு nb_channels,
                                       முழு nb_samples, எண்ணிக்கை AVSampleFormat sample_fmt, முழு align)
{
    முழு ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, அளவு(**audio_data));
    எனில் (!*audio_data)
        திரும்பு AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    எனில் (ret < 0)
        av_freep(audio_data);
    திரும்பு ret;
}

முழு av_samples_copy(uint8_t * மாறிலி *dst, uint8_t * மாறிலி *src, முழு dst_offset,
                    முழு src_offset, முழு nb_samples, முழு nb_channels,
                    எண்ணிக்கை AVSampleFormat sample_fmt)
{
    முழு planar      = av_sample_fmt_is_planar(sample_fmt);
    முழு planes      = planar ? nb_channels : 1;
    முழு block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    முழு data_size   = nb_samples * block_align;
    முழு i;

    dst_offset *= block_align;
    src_offset *= block_align;

    எனில்((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        க்கு (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } இல்லையெனில் {
        க்கு (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    திரும்பு 0;
}

முழு av_samples_set_silence(uint8_t * மாறிலி *audio_data, முழு offset, முழு nb_samples,
                           முழு nb_channels, எண்ணிக்கை AVSampleFormat sample_fmt)
{
    முழு planar      = av_sample_fmt_is_planar(sample_fmt);
    முழு planes      = planar ? nb_channels : 1;
    முழு block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    முழு data_size   = nb_samples * block_align;
    முழு fill_char, i;

    எனில் (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    இல்லையெனில் எனில் (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    இல்லையெனில்
        fill_char = 0x00;

    offset *= block_align;

    க்கு (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    திரும்பு 0;
}
