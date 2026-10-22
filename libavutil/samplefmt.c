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

#अन्तर्भाव "error.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "samplefmt.h"

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

प्रकारनिर्देश संरचना SampleFmtInfo {
    वर्ण name[8];
    पूर्णाङ्क bits;
    पूर्णाङ्क planar;
    गणना AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
स्थिर ध्रुव SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
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

ध्रुव वर्ण *av_get_sample_fmt_name(गणना AVSampleFormat sample_fmt)
{
    सचे (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        पटिनिवत्त रिक्त;
    पटिनिवत्त sample_fmt_info[sample_fmt].name;
}

गणना AVSampleFormat av_get_sample_fmt(ध्रुव वर्ण *name)
{
    पूर्णाङ्क i;

    अत्थाय (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        सचे (!strcmp(sample_fmt_info[i].name, name))
            पटिनिवत्त i;
    पटिनिवत्त AV_SAMPLE_FMT_NONE;
}

गणना AVSampleFormat av_get_alt_sample_fmt(गणना AVSampleFormat sample_fmt, पूर्णाङ्क planar)
{
    सचे (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        पटिनिवत्त AV_SAMPLE_FMT_NONE;
    सचे (sample_fmt_info[sample_fmt].planar == planar)
        पटिनिवत्त sample_fmt;
    पटिनिवत्त sample_fmt_info[sample_fmt].altform;
}

गणना AVSampleFormat av_get_packed_sample_fmt(गणना AVSampleFormat sample_fmt)
{
    सचे (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        पटिनिवत्त AV_SAMPLE_FMT_NONE;
    सचे (sample_fmt_info[sample_fmt].planar)
        पटिनिवत्त sample_fmt_info[sample_fmt].altform;
    पटिनिवत्त sample_fmt;
}

गणना AVSampleFormat av_get_planar_sample_fmt(गणना AVSampleFormat sample_fmt)
{
    सचे (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        पटिनिवत्त AV_SAMPLE_FMT_NONE;
    सचे (sample_fmt_info[sample_fmt].planar)
        पटिनिवत्त sample_fmt;
    पटिनिवत्त sample_fmt_info[sample_fmt].altform;
}

वर्ण *av_get_sample_fmt_string (वर्ण *buf, पूर्णाङ्क buf_size, गणना AVSampleFormat sample_fmt)
{
    /* print header */
    सचे (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    अञ्ञथा सचे (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    पटिनिवत्त buf;
}

पूर्णाङ्क av_get_bytes_per_sample(गणना AVSampleFormat sample_fmt)
{
     पटिनिवत्त sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

पूर्णाङ्क av_sample_fmt_is_planar(गणना AVSampleFormat sample_fmt)
{
     सचे (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         पटिनिवत्त 0;
     पटिनिवत्त sample_fmt_info[sample_fmt].planar;
}

पूर्णाङ्क av_samples_get_buffer_size(पूर्णाङ्क *linesize, पूर्णाङ्क nb_channels, पूर्णाङ्क nb_samples,
                               गणना AVSampleFormat sample_fmt, पूर्णाङ्क align)
{
    पूर्णाङ्क पङ्क्तिः_size;
    पूर्णाङ्क sample_size = av_get_bytes_per_sample(sample_fmt);
    पूर्णाङ्क planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    सचे (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        पटिनिवत्त AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    सचे (!align) {
        सचे (nb_samples > INT_MAX - 31)
            पटिनिवत्त AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    सचे (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        पटिनिवत्त AVERROR(EINVAL);

    पङ्क्तिः_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    सचे (linesize)
        *linesize = पङ्क्तिः_size;

    पटिनिवत्त planar ? पङ्क्तिः_size * nb_channels : पङ्क्तिः_size;
}

पूर्णाङ्क av_samples_fill_arrays(uint8_t **audio_data, पूर्णाङ्क *linesize,
                           ध्रुव uint8_t *buf, पूर्णाङ्क nb_channels, पूर्णाङ्क nb_samples,
                           गणना AVSampleFormat sample_fmt, पूर्णाङ्क align)
{
    पूर्णाङ्क ch, planar, buf_size, पङ्क्तिः_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&पङ्क्तिः_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    सचे (buf_size < 0)
        पटिनिवत्त buf_size;

    सचे (linesize)
        *linesize = पङ्क्तिः_size;

    memset(audio_data, 0, planar
                          ? परिमाण(*audio_data) * nb_channels
                          : परिमाण(*audio_data));

    सचे (!buf)
        पटिनिवत्त buf_size;

    audio_data[0] = (uint8_t *)buf;
    अत्थाय (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + पङ्क्तिः_size;

    पटिनिवत्त buf_size;
}

पूर्णाङ्क av_samples_alloc(uint8_t **audio_data, पूर्णाङ्क *linesize, पूर्णाङ्क nb_channels,
                     पूर्णाङ्क nb_samples, गणना AVSampleFormat sample_fmt, पूर्णाङ्क align)
{
    uint8_t *buf;
    पूर्णाङ्क size = av_samples_get_buffer_size(रिक्त, nb_channels, nb_samples,
                                          sample_fmt, align);
    सचे (size < 0)
        पटिनिवत्त size;

    buf = av_malloc(size);
    सचे (!buf)
        पटिनिवत्त AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    सचे (size < 0) {
        av_free(buf);
        पटिनिवत्त size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    पटिनिवत्त size;
}

पूर्णाङ्क av_samples_alloc_array_and_samples(uint8_t ***audio_data, पूर्णाङ्क *linesize, पूर्णाङ्क nb_channels,
                                       पूर्णाङ्क nb_samples, गणना AVSampleFormat sample_fmt, पूर्णाङ्क align)
{
    पूर्णाङ्क ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, परिमाण(**audio_data));
    सचे (!*audio_data)
        पटिनिवत्त AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    सचे (ret < 0)
        av_freep(audio_data);
    पटिनिवत्त ret;
}

पूर्णाङ्क av_samples_copy(uint8_t * ध्रुव *dst, uint8_t * ध्रुव *src, पूर्णाङ्क dst_offset,
                    पूर्णाङ्क src_offset, पूर्णाङ्क nb_samples, पूर्णाङ्क nb_channels,
                    गणना AVSampleFormat sample_fmt)
{
    पूर्णाङ्क planar      = av_sample_fmt_is_planar(sample_fmt);
    पूर्णाङ्क planes      = planar ? nb_channels : 1;
    पूर्णाङ्क block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    पूर्णाङ्क data_size   = nb_samples * block_align;
    पूर्णाङ्क i;

    dst_offset *= block_align;
    src_offset *= block_align;

    सचे((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        अत्थाय (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } अञ्ञथा {
        अत्थाय (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    पटिनिवत्त 0;
}

पूर्णाङ्क av_samples_set_silence(uint8_t * ध्रुव *audio_data, पूर्णाङ्क offset, पूर्णाङ्क nb_samples,
                           पूर्णाङ्क nb_channels, गणना AVSampleFormat sample_fmt)
{
    पूर्णाङ्क planar      = av_sample_fmt_is_planar(sample_fmt);
    पूर्णाङ्क planes      = planar ? nb_channels : 1;
    पूर्णाङ्क block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    पूर्णाङ्क data_size   = nb_samples * block_align;
    पूर्णाङ्क fill_char, i;

    सचे (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    अञ्ञथा सचे (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    अञ्ञथा
        fill_char = 0x00;

    offset *= block_align;

    अत्थाय (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    पटिनिवत्त 0;
}
