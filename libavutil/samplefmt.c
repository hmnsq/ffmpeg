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

प्रकारव्याख्या संरचना SampleFmtInfo {
    अक्षर name[8];
    पूर्णांक bits;
    पूर्णांक planar;
    गणना AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
स्थिर स्थिरांक SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
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

स्थिरांक अक्षर *av_get_sample_fmt_name(गणना AVSampleFormat sample_fmt)
{
    जर (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        परत रिक्त;
    परत sample_fmt_info[sample_fmt].name;
}

गणना AVSampleFormat av_get_sample_fmt(स्थिरांक अक्षर *name)
{
    पूर्णांक i;

    साठी (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        जर (!म_भेद(sample_fmt_info[i].name, name))
            परत i;
    परत AV_SAMPLE_FMT_NONE;
}

गणना AVSampleFormat av_get_alt_sample_fmt(गणना AVSampleFormat sample_fmt, पूर्णांक planar)
{
    जर (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        परत AV_SAMPLE_FMT_NONE;
    जर (sample_fmt_info[sample_fmt].planar == planar)
        परत sample_fmt;
    परत sample_fmt_info[sample_fmt].altform;
}

गणना AVSampleFormat av_get_packed_sample_fmt(गणना AVSampleFormat sample_fmt)
{
    जर (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        परत AV_SAMPLE_FMT_NONE;
    जर (sample_fmt_info[sample_fmt].planar)
        परत sample_fmt_info[sample_fmt].altform;
    परत sample_fmt;
}

गणना AVSampleFormat av_get_planar_sample_fmt(गणना AVSampleFormat sample_fmt)
{
    जर (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        परत AV_SAMPLE_FMT_NONE;
    जर (sample_fmt_info[sample_fmt].planar)
        परत sample_fmt;
    परत sample_fmt_info[sample_fmt].altform;
}

अक्षर *av_get_sample_fmt_string (अक्षर *buf, पूर्णांक buf_size, गणना AVSampleFormat sample_fmt)
{
    /* print header */
    जर (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    अन्यथा जर (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    परत buf;
}

पूर्णांक av_get_bytes_per_sample(गणना AVSampleFormat sample_fmt)
{
     परत sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

पूर्णांक av_sample_fmt_is_planar(गणना AVSampleFormat sample_fmt)
{
     जर (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         परत 0;
     परत sample_fmt_info[sample_fmt].planar;
}

पूर्णांक av_samples_get_buffer_size(पूर्णांक *linesize, पूर्णांक nb_channels, पूर्णांक nb_samples,
                               गणना AVSampleFormat sample_fmt, पूर्णांक align)
{
    पूर्णांक ओळ_size;
    पूर्णांक sample_size = av_get_bytes_per_sample(sample_fmt);
    पूर्णांक planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    जर (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        परत AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    जर (!align) {
        जर (nb_samples > पूर्णांक_उच्च - 31)
            परत AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    जर (nb_channels > पूर्णांक_उच्च / align ||
        (int64_t)nb_channels * nb_samples > (पूर्णांक_उच्च - (align * nb_channels)) / sample_size)
        परत AVERROR(EINVAL);

    ओळ_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    जर (linesize)
        *linesize = ओळ_size;

    परत planar ? ओळ_size * nb_channels : ओळ_size;
}

पूर्णांक av_samples_fill_arrays(uint8_t **audio_data, पूर्णांक *linesize,
                           स्थिरांक uint8_t *buf, पूर्णांक nb_channels, पूर्णांक nb_samples,
                           गणना AVSampleFormat sample_fmt, पूर्णांक align)
{
    पूर्णांक ch, planar, buf_size, ओळ_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&ओळ_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    जर (buf_size < 0)
        परत buf_size;

    जर (linesize)
        *linesize = ओळ_size;

    स_रखो(audio_data, 0, planar
                          ? आकार(*audio_data) * nb_channels
                          : आकार(*audio_data));

    जर (!buf)
        परत buf_size;

    audio_data[0] = (uint8_t *)buf;
    साठी (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + ओळ_size;

    परत buf_size;
}

पूर्णांक av_samples_alloc(uint8_t **audio_data, पूर्णांक *linesize, पूर्णांक nb_channels,
                     पूर्णांक nb_samples, गणना AVSampleFormat sample_fmt, पूर्णांक align)
{
    uint8_t *buf;
    पूर्णांक size = av_samples_get_buffer_size(रिक्त, nb_channels, nb_samples,
                                          sample_fmt, align);
    जर (size < 0)
        परत size;

    buf = av_malloc(size);
    जर (!buf)
        परत AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    जर (size < 0) {
        av_free(buf);
        परत size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    परत size;
}

पूर्णांक av_samples_alloc_array_and_samples(uint8_t ***audio_data, पूर्णांक *linesize, पूर्णांक nb_channels,
                                       पूर्णांक nb_samples, गणना AVSampleFormat sample_fmt, पूर्णांक align)
{
    पूर्णांक ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, आकार(**audio_data));
    जर (!*audio_data)
        परत AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    जर (ret < 0)
        av_freep(audio_data);
    परत ret;
}

पूर्णांक av_samples_copy(uint8_t * स्थिरांक *dst, uint8_t * स्थिरांक *src, पूर्णांक dst_offset,
                    पूर्णांक src_offset, पूर्णांक nb_samples, पूर्णांक nb_channels,
                    गणना AVSampleFormat sample_fmt)
{
    पूर्णांक planar      = av_sample_fmt_is_planar(sample_fmt);
    पूर्णांक planes      = planar ? nb_channels : 1;
    पूर्णांक block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    पूर्णांक data_size   = nb_samples * block_align;
    पूर्णांक i;

    dst_offset *= block_align;
    src_offset *= block_align;

    जर((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        साठी (i = 0; i < planes; i++)
            स_नकल(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } अन्यथा {
        साठी (i = 0; i < planes; i++)
            स_हटाओ(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    परत 0;
}

पूर्णांक av_samples_set_silence(uint8_t * स्थिरांक *audio_data, पूर्णांक offset, पूर्णांक nb_samples,
                           पूर्णांक nb_channels, गणना AVSampleFormat sample_fmt)
{
    पूर्णांक planar      = av_sample_fmt_is_planar(sample_fmt);
    पूर्णांक planes      = planar ? nb_channels : 1;
    पूर्णांक block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    पूर्णांक data_size   = nb_samples * block_align;
    पूर्णांक fill_char, i;

    जर (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    अन्यथा जर (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    अन्यथा
        fill_char = 0x00;

    offset *= block_align;

    साठी (i = 0; i < planes; i++)
        स_रखो(audio_data[i] + offset, fill_char, data_size);

    परत 0;
}
