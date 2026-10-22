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

#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "samplefmt.h"

#ଅନ୍ତର୍ଭାଵ <limits.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା SampleFmtInfo {
    ଅକ୍ଷର name[8];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା bits;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା planar;
    ଗଣନା AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
ସ୍ଥିର ଅଚଳ SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
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

ଅଚଳ ଅକ୍ଷର *av_get_sample_fmt_name(ଗଣନା AVSampleFormat sample_fmt)
{
    ଯଦି (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ଫେରନ୍ତୁ ଖାଲି;
    ଫେରନ୍ତୁ sample_fmt_info[sample_fmt].name;
}

ଗଣନା AVSampleFormat av_get_sample_fmt(ଅଚଳ ଅକ୍ଷର *name)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        ଯଦି (!strcmp(sample_fmt_info[i].name, name))
            ଫେରନ୍ତୁ i;
    ଫେରନ୍ତୁ AV_SAMPLE_FMT_NONE;
}

ଗଣନା AVSampleFormat av_get_alt_sample_fmt(ଗଣନା AVSampleFormat sample_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା planar)
{
    ଯଦି (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ଫେରନ୍ତୁ AV_SAMPLE_FMT_NONE;
    ଯଦି (sample_fmt_info[sample_fmt].planar == planar)
        ଫେରନ୍ତୁ sample_fmt;
    ଫେରନ୍ତୁ sample_fmt_info[sample_fmt].altform;
}

ଗଣନା AVSampleFormat av_get_packed_sample_fmt(ଗଣନା AVSampleFormat sample_fmt)
{
    ଯଦି (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ଫେରନ୍ତୁ AV_SAMPLE_FMT_NONE;
    ଯଦି (sample_fmt_info[sample_fmt].planar)
        ଫେରନ୍ତୁ sample_fmt_info[sample_fmt].altform;
    ଫେରନ୍ତୁ sample_fmt;
}

ଗଣନା AVSampleFormat av_get_planar_sample_fmt(ଗଣନା AVSampleFormat sample_fmt)
{
    ଯଦି (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ଫେରନ୍ତୁ AV_SAMPLE_FMT_NONE;
    ଯଦି (sample_fmt_info[sample_fmt].planar)
        ଫେରନ୍ତୁ sample_fmt;
    ଫେରନ୍ତୁ sample_fmt_info[sample_fmt].altform;
}

ଅକ୍ଷର *av_get_sample_fmt_string (ଅକ୍ଷର *buf, ପୂର୍ଣ୍ଣସଂଖ୍ୟା buf_size, ଗଣନା AVSampleFormat sample_fmt)
{
    /* print header */
    ଯଦି (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    ଅନ୍ୟଥା ଯଦି (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    ଫେରନ୍ତୁ buf;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_get_bytes_per_sample(ଗଣନା AVSampleFormat sample_fmt)
{
     ଫେରନ୍ତୁ sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_sample_fmt_is_planar(ଗଣନା AVSampleFormat sample_fmt)
{
     ଯଦି (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         ଫେରନ୍ତୁ 0;
     ଫେରନ୍ତୁ sample_fmt_info[sample_fmt].planar;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_samples_get_buffer_size(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *linesize, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_channels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples,
                               ଗଣନା AVSampleFormat sample_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା align)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଧାଡ଼ି_size;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା sample_size = av_get_bytes_per_sample(sample_fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    ଯଦି (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    ଯଦି (!align) {
        ଯଦି (nb_samples > INT_MAX - 31)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    ଯଦି (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଧାଡ଼ି_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    ଯଦି (linesize)
        *linesize = ଧାଡ଼ି_size;

    ଫେରନ୍ତୁ planar ? ଧାଡ଼ି_size * nb_channels : ଧାଡ଼ି_size;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_samples_fill_arrays(uint8_t **audio_data, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *linesize,
                           ଅଚଳ uint8_t *buf, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_channels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples,
                           ଗଣନା AVSampleFormat sample_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା align)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ch, planar, buf_size, ଧାଡ଼ି_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&ଧାଡ଼ି_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    ଯଦି (buf_size < 0)
        ଫେରନ୍ତୁ buf_size;

    ଯଦି (linesize)
        *linesize = ଧାଡ଼ି_size;

    memset(audio_data, 0, planar
                          ? ଆକାର(*audio_data) * nb_channels
                          : ଆକାର(*audio_data));

    ଯଦି (!buf)
        ଫେରନ୍ତୁ buf_size;

    audio_data[0] = (uint8_t *)buf;
    ପାଇଁ (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + ଧାଡ଼ି_size;

    ଫେରନ୍ତୁ buf_size;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_samples_alloc(uint8_t **audio_data, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *linesize, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_channels,
                     ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples, ଗଣନା AVSampleFormat sample_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା align)
{
    uint8_t *buf;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା size = av_samples_get_buffer_size(ଖାଲି, nb_channels, nb_samples,
                                          sample_fmt, align);
    ଯଦି (size < 0)
        ଫେରନ୍ତୁ size;

    buf = av_malloc(size);
    ଯଦି (!buf)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    ଯଦି (size < 0) {
        av_free(buf);
        ଫେରନ୍ତୁ size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    ଫେରନ୍ତୁ size;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_samples_alloc_array_and_samples(uint8_t ***audio_data, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *linesize, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_channels,
                                       ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples, ଗଣନା AVSampleFormat sample_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା align)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, ଆକାର(**audio_data));
    ଯଦି (!*audio_data)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    ଯଦି (ret < 0)
        av_freep(audio_data);
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_samples_copy(uint8_t * ଅଚଳ *dst, uint8_t * ଅଚଳ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_offset,
                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_offset, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_channels,
                    ଗଣନା AVSampleFormat sample_fmt)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା planar      = av_sample_fmt_is_planar(sample_fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes      = planar ? nb_channels : 1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା data_size   = nb_samples * block_align;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    dst_offset *= block_align;
    src_offset *= block_align;

    ଯଦି((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        ପାଇଁ (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } ଅନ୍ୟଥା {
        ପାଇଁ (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_samples_set_silence(uint8_t * ଅଚଳ *audio_data, ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples,
                           ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_channels, ଗଣନା AVSampleFormat sample_fmt)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା planar      = av_sample_fmt_is_planar(sample_fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା planes      = planar ? nb_channels : 1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା data_size   = nb_samples * block_align;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା fill_char, i;

    ଯଦି (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    ଅନ୍ୟଥା ଯଦି (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    ଅନ୍ୟଥା
        fill_char = 0x00;

    offset *= block_align;

    ପାଇଁ (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    ଫେରନ୍ତୁ 0;
}
