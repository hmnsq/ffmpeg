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
    पूर्णाङ्क द्वयङ्काः;
    पूर्णाङ्क planar;
    गणना AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
स्थिर ध्रुव SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
    [AV_SAMPLE_FMT_U8]   = { .name =   "u8", .द्वयङ्काः =  8, .planar = 0, .altform = AV_SAMPLE_FMT_U8P  },
    [AV_SAMPLE_FMT_S16]  = { .name =  "s16", .द्वयङ्काः = 16, .planar = 0, .altform = AV_SAMPLE_FMT_S16P },
    [AV_SAMPLE_FMT_S32]  = { .name =  "s32", .द्वयङ्काः = 32, .planar = 0, .altform = AV_SAMPLE_FMT_S32P },
    [AV_SAMPLE_FMT_S64]  = { .name =  "s64", .द्वयङ्काः = 64, .planar = 0, .altform = AV_SAMPLE_FMT_S64P },
    [AV_SAMPLE_FMT_FLT]  = { .name =  "flt", .द्वयङ्काः = 32, .planar = 0, .altform = AV_SAMPLE_FMT_FLTP },
    [AV_SAMPLE_FMT_DBL]  = { .name =  "dbl", .द्वयङ्काः = 64, .planar = 0, .altform = AV_SAMPLE_FMT_DBLP },
    [AV_SAMPLE_FMT_U8P]  = { .name =  "u8p", .द्वयङ्काः =  8, .planar = 1, .altform = AV_SAMPLE_FMT_U8   },
    [AV_SAMPLE_FMT_S16P] = { .name = "s16p", .द्वयङ्काः = 16, .planar = 1, .altform = AV_SAMPLE_FMT_S16  },
    [AV_SAMPLE_FMT_S32P] = { .name = "s32p", .द्वयङ्काः = 32, .planar = 1, .altform = AV_SAMPLE_FMT_S32  },
    [AV_SAMPLE_FMT_S64P] = { .name = "s64p", .द्वयङ्काः = 64, .planar = 1, .altform = AV_SAMPLE_FMT_S64  },
    [AV_SAMPLE_FMT_FLTP] = { .name = "fltp", .द्वयङ्काः = 32, .planar = 1, .altform = AV_SAMPLE_FMT_FLT  },
    [AV_SAMPLE_FMT_DBLP] = { .name = "dblp", .द्वयङ्काः = 64, .planar = 1, .altform = AV_SAMPLE_FMT_DBL  },
    [AV_SAMPLE_FMT_DSD]  = { .name =  "dsd", .द्वयङ्काः =  8, .planar = 0, .altform = AV_SAMPLE_FMT_DSD  },
};

ध्रुव वर्ण *av_get_sample_fmt_name(गणना AVSampleFormat sample_fmt)
{
    यदि (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        प्रत्यागम रिक्त;
    प्रत्यागम sample_fmt_info[sample_fmt].name;
}

गणना AVSampleFormat av_get_sample_fmt(ध्रुव वर्ण *name)
{
    पूर्णाङ्क i;

    प्रति (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        यदि (!वाक्यं_तुलय(sample_fmt_info[i].name, name))
            प्रत्यागम i;
    प्रत्यागम AV_SAMPLE_FMT_NONE;
}

गणना AVSampleFormat av_get_alt_sample_fmt(गणना AVSampleFormat sample_fmt, पूर्णाङ्क planar)
{
    यदि (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        प्रत्यागम AV_SAMPLE_FMT_NONE;
    यदि (sample_fmt_info[sample_fmt].planar == planar)
        प्रत्यागम sample_fmt;
    प्रत्यागम sample_fmt_info[sample_fmt].altform;
}

गणना AVSampleFormat av_get_packed_sample_fmt(गणना AVSampleFormat sample_fmt)
{
    यदि (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        प्रत्यागम AV_SAMPLE_FMT_NONE;
    यदि (sample_fmt_info[sample_fmt].planar)
        प्रत्यागम sample_fmt_info[sample_fmt].altform;
    प्रत्यागम sample_fmt;
}

गणना AVSampleFormat av_get_planar_sample_fmt(गणना AVSampleFormat sample_fmt)
{
    यदि (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        प्रत्यागम AV_SAMPLE_FMT_NONE;
    यदि (sample_fmt_info[sample_fmt].planar)
        प्रत्यागम sample_fmt;
    प्रत्यागम sample_fmt_info[sample_fmt].altform;
}

वर्ण *av_get_sample_fmt_string (वर्ण *buf, पूर्णाङ्क buf_आकार, गणना AVSampleFormat sample_fmt)
{
    /* print header */
    यदि (sample_fmt < 0)
        snprintf(buf, buf_आकार, "name  " " depth");
    अन्यथा यदि (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_आकार, "%-6s" "   %2d ", info.name, info.द्वयङ्काः);
    }

    प्रत्यागम buf;
}

पूर्णाङ्क av_get_अष्टकानि_प्रत्येकम्_sample(गणना AVSampleFormat sample_fmt)
{
     प्रत्यागम sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].द्वयङ्काः >> 3;
}

पूर्णाङ्क av_sample_fmt_is_planar(गणना AVSampleFormat sample_fmt)
{
     यदि (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         प्रत्यागम 0;
     प्रत्यागम sample_fmt_info[sample_fmt].planar;
}

पूर्णाङ्क av_samples_get_बफर_आकार(पूर्णाङ्क *linesize, पूर्णाङ्क nb_channels, पूर्णाङ्क nb_samples,
                               गणना AVSampleFormat sample_fmt, पूर्णाङ्क align)
{
    पूर्णाङ्क पङ्क्तिः_आकार;
    पूर्णाङ्क sample_आकार = av_get_अष्टकानि_प्रत्येकम्_sample(sample_fmt);
    पूर्णाङ्क planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    यदि (!sample_आकार || nb_samples <= 0 || nb_channels <= 0)
        प्रत्यागम AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    यदि (!align) {
        यदि (nb_samples > अधिकतम_पूर्णाङ्कः - 31)
            प्रत्यागम AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    यदि (nb_channels > अधिकतम_पूर्णाङ्कः / align ||
        (int64_t)nb_channels * nb_samples > (अधिकतम_पूर्णाङ्कः - (align * nb_channels)) / sample_आकार)
        प्रत्यागम AVERROR(EINVAL);

    पङ्क्तिः_आकार = planar ? FFALIGN(nb_samples * sample_आकार,               align) :
                         FFALIGN(nb_samples * sample_आकार * nb_channels, align);
    यदि (linesize)
        *linesize = पङ्क्तिः_आकार;

    प्रत्यागम planar ? पङ्क्तिः_आकार * nb_channels : पङ्क्तिः_आकार;
}

पूर्णाङ्क av_samples_fill_arrays(uint8_t **audio_दत्त, पूर्णाङ्क *linesize,
                           ध्रुव uint8_t *buf, पूर्णाङ्क nb_channels, पूर्णाङ्क nb_samples,
                           गणना AVSampleFormat sample_fmt, पूर्णाङ्क align)
{
    पूर्णाङ्क ch, planar, buf_आकार, पङ्क्तिः_आकार;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_आकार = av_samples_get_बफर_आकार(&पङ्क्तिः_आकार, nb_channels, nb_samples,
                                          sample_fmt, align);
    यदि (buf_आकार < 0)
        प्रत्यागम buf_आकार;

    यदि (linesize)
        *linesize = पङ्क्तिः_आकार;

    स्मृतिं_पूरय(audio_दत्त, 0, planar
                          ? परिमाण(*audio_दत्त) * nb_channels
                          : परिमाण(*audio_दत्त));

    यदि (!buf)
        प्रत्यागम buf_आकार;

    audio_दत्त[0] = (uint8_t *)buf;
    प्रति (ch = 1; planar && ch < nb_channels; ch++)
        audio_दत्त[ch] = audio_दत्त[ch-1] + पङ्क्तिः_आकार;

    प्रत्यागम buf_आकार;
}

पूर्णाङ्क av_samples_alloc(uint8_t **audio_दत्त, पूर्णाङ्क *linesize, पूर्णाङ्क nb_channels,
                     पूर्णाङ्क nb_samples, गणना AVSampleFormat sample_fmt, पूर्णाङ्क align)
{
    uint8_t *buf;
    पूर्णाङ्क आकार = av_samples_get_बफर_आकार(रिक्त, nb_channels, nb_samples,
                                          sample_fmt, align);
    यदि (आकार < 0)
        प्रत्यागम आकार;

    buf = av_malloc(आकार);
    यदि (!buf)
        प्रत्यागम AVERROR(ENOMEM);

    आकार = av_samples_fill_arrays(audio_दत्त, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    यदि (आकार < 0) {
        av_free(buf);
        प्रत्यागम आकार;
    }

    av_samples_समुच्चयः_silence(audio_दत्त, 0, nb_samples, nb_channels, sample_fmt);

    प्रत्यागम आकार;
}

पूर्णाङ्क av_samples_alloc_array_and_samples(uint8_t ***audio_दत्त, पूर्णाङ्क *linesize, पूर्णाङ्क nb_channels,
                                       पूर्णाङ्क nb_samples, गणना AVSampleFormat sample_fmt, पूर्णाङ्क align)
{
    पूर्णाङ्क ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_दत्त = av_calloc(nb_planes, परिमाण(**audio_दत्त));
    यदि (!*audio_दत्त)
        प्रत्यागम AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_दत्त, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    यदि (ret < 0)
        av_freep(audio_दत्त);
    प्रत्यागम ret;
}

पूर्णाङ्क av_samples_copy(uint8_t * ध्रुव *dst, uint8_t * ध्रुव *src, पूर्णाङ्क dst_विस्थापनम्,
                    पूर्णाङ्क src_विस्थापनम्, पूर्णाङ्क nb_samples, पूर्णाङ्क nb_channels,
                    गणना AVSampleFormat sample_fmt)
{
    पूर्णाङ्क planar      = av_sample_fmt_is_planar(sample_fmt);
    पूर्णाङ्क planes      = planar ? nb_channels : 1;
    पूर्णाङ्क खण्डम्_align = av_get_अष्टकानि_प्रत्येकम्_sample(sample_fmt) * (planar ? 1 : nb_channels);
    पूर्णाङ्क दत्त_आकार   = nb_samples * खण्डम्_align;
    पूर्णाङ्क i;

    dst_विस्थापनम् *= खण्डम्_align;
    src_विस्थापनम् *= खण्डम्_align;

    यदि((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= दत्त_आकार) {
        प्रति (i = 0; i < planes; i++)
            स्मृतिं_प्रतिलिख(dst[i] + dst_विस्थापनम्, src[i] + src_विस्थापनम्, दत्त_आकार);
    } अन्यथा {
        प्रति (i = 0; i < planes; i++)
            memmove(dst[i] + dst_विस्थापनम्, src[i] + src_विस्थापनम्, दत्त_आकार);
    }

    प्रत्यागम 0;
}

पूर्णाङ्क av_samples_समुच्चयः_silence(uint8_t * ध्रुव *audio_दत्त, पूर्णाङ्क विस्थापनम्, पूर्णाङ्क nb_samples,
                           पूर्णाङ्क nb_channels, गणना AVSampleFormat sample_fmt)
{
    पूर्णाङ्क planar      = av_sample_fmt_is_planar(sample_fmt);
    पूर्णाङ्क planes      = planar ? nb_channels : 1;
    पूर्णाङ्क खण्डम्_align = av_get_अष्टकानि_प्रत्येकम्_sample(sample_fmt) * (planar ? 1 : nb_channels);
    पूर्णाङ्क दत्त_आकार   = nb_samples * खण्डम्_align;
    पूर्णाङ्क fill_char, i;

    यदि (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    अन्यथा यदि (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    अन्यथा
        fill_char = 0x00;

    विस्थापनम् *= खण्डम्_align;

    प्रति (i = 0; i < planes; i++)
        स्मृतिं_पूरय(audio_दत्त[i] + विस्थापनम्, fill_char, दत्त_आकार);

    प्रत्यागम 0;
}
