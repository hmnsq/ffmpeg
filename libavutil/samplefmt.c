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

#समावेश "error.h"
#समावेश "macros.h"
#समावेश "mem.h"
#समावेश "samplefmt.h"

#समावेश <limits.h>
#समावेश <stdio.h>
#समावेश <string.h>

प्रकार काष्ठा SampleFmtInfo {
    अक्षर name[8];
    पूर्णांक bits;
    पूर्णांक planar;
    क्रमागत AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
अटल स्थिर SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
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

स्थिर अक्षर *av_get_sample_fmt_name(क्रमागत AVSampleFormat sample_fmt)
{
    अगर (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        वापस शून्य;
    वापस sample_fmt_info[sample_fmt].name;
}

क्रमागत AVSampleFormat av_get_sample_fmt(स्थिर अक्षर *name)
{
    पूर्णांक i;

    क्रम (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        अगर (!म_भेद(sample_fmt_info[i].name, name))
            वापस i;
    वापस AV_SAMPLE_FMT_NONE;
}

क्रमागत AVSampleFormat av_get_alt_sample_fmt(क्रमागत AVSampleFormat sample_fmt, पूर्णांक planar)
{
    अगर (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        वापस AV_SAMPLE_FMT_NONE;
    अगर (sample_fmt_info[sample_fmt].planar == planar)
        वापस sample_fmt;
    वापस sample_fmt_info[sample_fmt].altform;
}

क्रमागत AVSampleFormat av_get_packed_sample_fmt(क्रमागत AVSampleFormat sample_fmt)
{
    अगर (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        वापस AV_SAMPLE_FMT_NONE;
    अगर (sample_fmt_info[sample_fmt].planar)
        वापस sample_fmt_info[sample_fmt].altform;
    वापस sample_fmt;
}

क्रमागत AVSampleFormat av_get_planar_sample_fmt(क्रमागत AVSampleFormat sample_fmt)
{
    अगर (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        वापस AV_SAMPLE_FMT_NONE;
    अगर (sample_fmt_info[sample_fmt].planar)
        वापस sample_fmt;
    वापस sample_fmt_info[sample_fmt].altform;
}

अक्षर *av_get_sample_fmt_string (अक्षर *buf, पूर्णांक buf_आकार, क्रमागत AVSampleFormat sample_fmt)
{
    /* print header */
    अगर (sample_fmt < 0)
        snprintf(buf, buf_आकार, "name  " " depth");
    अन्यथा अगर (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_आकार, "%-6s" "   %2d ", info.name, info.bits);
    }

    वापस buf;
}

पूर्णांक av_get_bytes_per_sample(क्रमागत AVSampleFormat sample_fmt)
{
     वापस sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

पूर्णांक av_sample_fmt_is_planar(क्रमागत AVSampleFormat sample_fmt)
{
     अगर (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         वापस 0;
     वापस sample_fmt_info[sample_fmt].planar;
}

पूर्णांक av_samples_get_बफर_आकार(पूर्णांक *linesize, पूर्णांक nb_channels, पूर्णांक nb_samples,
                               क्रमागत AVSampleFormat sample_fmt, पूर्णांक align)
{
    पूर्णांक पंक्ति_आकार;
    पूर्णांक sample_आकार = av_get_bytes_per_sample(sample_fmt);
    पूर्णांक planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    अगर (!sample_आकार || nb_samples <= 0 || nb_channels <= 0)
        वापस AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    अगर (!align) {
        अगर (nb_samples > पूर्णांक_उच्च - 31)
            वापस AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    अगर (nb_channels > पूर्णांक_उच्च / align ||
        (int64_t)nb_channels * nb_samples > (पूर्णांक_उच्च - (align * nb_channels)) / sample_आकार)
        वापस AVERROR(EINVAL);

    पंक्ति_आकार = planar ? FFALIGN(nb_samples * sample_आकार,               align) :
                         FFALIGN(nb_samples * sample_आकार * nb_channels, align);
    अगर (linesize)
        *linesize = पंक्ति_आकार;

    वापस planar ? पंक्ति_आकार * nb_channels : पंक्ति_आकार;
}

पूर्णांक av_samples_fill_arrays(uint8_t **audio_तथ्य, पूर्णांक *linesize,
                           स्थिर uint8_t *buf, पूर्णांक nb_channels, पूर्णांक nb_samples,
                           क्रमागत AVSampleFormat sample_fmt, पूर्णांक align)
{
    पूर्णांक ch, planar, buf_आकार, पंक्ति_आकार;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_आकार = av_samples_get_बफर_आकार(&पंक्ति_आकार, nb_channels, nb_samples,
                                          sample_fmt, align);
    अगर (buf_आकार < 0)
        वापस buf_आकार;

    अगर (linesize)
        *linesize = पंक्ति_आकार;

    स_रखो(audio_तथ्य, 0, planar
                          ? माप(*audio_तथ्य) * nb_channels
                          : माप(*audio_तथ्य));

    अगर (!buf)
        वापस buf_आकार;

    audio_तथ्य[0] = (uint8_t *)buf;
    क्रम (ch = 1; planar && ch < nb_channels; ch++)
        audio_तथ्य[ch] = audio_तथ्य[ch-1] + पंक्ति_आकार;

    वापस buf_आकार;
}

पूर्णांक av_samples_alloc(uint8_t **audio_तथ्य, पूर्णांक *linesize, पूर्णांक nb_channels,
                     पूर्णांक nb_samples, क्रमागत AVSampleFormat sample_fmt, पूर्णांक align)
{
    uint8_t *buf;
    पूर्णांक आकार = av_samples_get_बफर_आकार(शून्य, nb_channels, nb_samples,
                                          sample_fmt, align);
    अगर (आकार < 0)
        वापस आकार;

    buf = av_malloc(आकार);
    अगर (!buf)
        वापस AVERROR(ENOMEM);

    आकार = av_samples_fill_arrays(audio_तथ्य, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    अगर (आकार < 0) {
        av_free(buf);
        वापस आकार;
    }

    av_samples_set_silence(audio_तथ्य, 0, nb_samples, nb_channels, sample_fmt);

    वापस आकार;
}

पूर्णांक av_samples_alloc_array_and_samples(uint8_t ***audio_तथ्य, पूर्णांक *linesize, पूर्णांक nb_channels,
                                       पूर्णांक nb_samples, क्रमागत AVSampleFormat sample_fmt, पूर्णांक align)
{
    पूर्णांक ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_तथ्य = av_calloc(nb_planes, माप(**audio_तथ्य));
    अगर (!*audio_तथ्य)
        वापस AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_तथ्य, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    अगर (ret < 0)
        av_freep(audio_तथ्य);
    वापस ret;
}

पूर्णांक av_samples_copy(uint8_t * स्थिर *dst, uint8_t * स्थिर *src, पूर्णांक dst_offset,
                    पूर्णांक src_offset, पूर्णांक nb_samples, पूर्णांक nb_channels,
                    क्रमागत AVSampleFormat sample_fmt)
{
    पूर्णांक planar      = av_sample_fmt_is_planar(sample_fmt);
    पूर्णांक planes      = planar ? nb_channels : 1;
    पूर्णांक block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    पूर्णांक तथ्य_आकार   = nb_samples * block_align;
    पूर्णांक i;

    dst_offset *= block_align;
    src_offset *= block_align;

    अगर((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= तथ्य_आकार) {
        क्रम (i = 0; i < planes; i++)
            स_नकल(dst[i] + dst_offset, src[i] + src_offset, तथ्य_आकार);
    } अन्यथा {
        क्रम (i = 0; i < planes; i++)
            स_हटाओ(dst[i] + dst_offset, src[i] + src_offset, तथ्य_आकार);
    }

    वापस 0;
}

पूर्णांक av_samples_set_silence(uint8_t * स्थिर *audio_तथ्य, पूर्णांक offset, पूर्णांक nb_samples,
                           पूर्णांक nb_channels, क्रमागत AVSampleFormat sample_fmt)
{
    पूर्णांक planar      = av_sample_fmt_is_planar(sample_fmt);
    पूर्णांक planes      = planar ? nb_channels : 1;
    पूर्णांक block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    पूर्णांक तथ्य_आकार   = nb_samples * block_align;
    पूर्णांक fill_char, i;

    अगर (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    अन्यथा अगर (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    अन्यथा
        fill_char = 0x00;

    offset *= block_align;

    क्रम (i = 0; i < planes; i++)
        स_रखो(audio_तथ्य[i] + offset, fill_char, तथ्य_आकार);

    वापस 0;
}
