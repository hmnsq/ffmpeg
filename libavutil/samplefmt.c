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

#అన్తర్భావ "error.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "samplefmt.h"

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

రకనిర్వచనం నిర్మాణం SampleFmtInfo {
    అక్షరం name[8];
    పూర్ణాంకం బిట్లు;
    పూర్ణాంకం planar;
    గణన AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
స్థిర స్థిరరాశి SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
    [AV_SAMPLE_FMT_U8]   = { .name =   "u8", .బిట్లు =  8, .planar = 0, .altform = AV_SAMPLE_FMT_U8P  },
    [AV_SAMPLE_FMT_S16]  = { .name =  "s16", .బిట్లు = 16, .planar = 0, .altform = AV_SAMPLE_FMT_S16P },
    [AV_SAMPLE_FMT_S32]  = { .name =  "s32", .బిట్లు = 32, .planar = 0, .altform = AV_SAMPLE_FMT_S32P },
    [AV_SAMPLE_FMT_S64]  = { .name =  "s64", .బిట్లు = 64, .planar = 0, .altform = AV_SAMPLE_FMT_S64P },
    [AV_SAMPLE_FMT_FLT]  = { .name =  "flt", .బిట్లు = 32, .planar = 0, .altform = AV_SAMPLE_FMT_FLTP },
    [AV_SAMPLE_FMT_DBL]  = { .name =  "dbl", .బిట్లు = 64, .planar = 0, .altform = AV_SAMPLE_FMT_DBLP },
    [AV_SAMPLE_FMT_U8P]  = { .name =  "u8p", .బిట్లు =  8, .planar = 1, .altform = AV_SAMPLE_FMT_U8   },
    [AV_SAMPLE_FMT_S16P] = { .name = "s16p", .బిట్లు = 16, .planar = 1, .altform = AV_SAMPLE_FMT_S16  },
    [AV_SAMPLE_FMT_S32P] = { .name = "s32p", .బిట్లు = 32, .planar = 1, .altform = AV_SAMPLE_FMT_S32  },
    [AV_SAMPLE_FMT_S64P] = { .name = "s64p", .బిట్లు = 64, .planar = 1, .altform = AV_SAMPLE_FMT_S64  },
    [AV_SAMPLE_FMT_FLTP] = { .name = "fltp", .బిట్లు = 32, .planar = 1, .altform = AV_SAMPLE_FMT_FLT  },
    [AV_SAMPLE_FMT_DBLP] = { .name = "dblp", .బిట్లు = 64, .planar = 1, .altform = AV_SAMPLE_FMT_DBL  },
    [AV_SAMPLE_FMT_DSD]  = { .name =  "dsd", .బిట్లు =  8, .planar = 0, .altform = AV_SAMPLE_FMT_DSD  },
};

స్థిరరాశి అక్షరం *av_get_sample_fmt_name(గణన AVSampleFormat sample_fmt)
{
    ఒకవేళ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        తిరిగి ఖాళీ;
    తిరిగి sample_fmt_info[sample_fmt].name;
}

గణన AVSampleFormat av_get_sample_fmt(స్థిరరాశి అక్షరం *name)
{
    పూర్ణాంకం i;

    కొరకు (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        ఒకవేళ (!strcmp(sample_fmt_info[i].name, name))
            తిరిగి i;
    తిరిగి AV_SAMPLE_FMT_NONE;
}

గణన AVSampleFormat av_get_alt_sample_fmt(గణన AVSampleFormat sample_fmt, పూర్ణాంకం planar)
{
    ఒకవేళ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        తిరిగి AV_SAMPLE_FMT_NONE;
    ఒకవేళ (sample_fmt_info[sample_fmt].planar == planar)
        తిరిగి sample_fmt;
    తిరిగి sample_fmt_info[sample_fmt].altform;
}

గణన AVSampleFormat av_get_packed_sample_fmt(గణన AVSampleFormat sample_fmt)
{
    ఒకవేళ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        తిరిగి AV_SAMPLE_FMT_NONE;
    ఒకవేళ (sample_fmt_info[sample_fmt].planar)
        తిరిగి sample_fmt_info[sample_fmt].altform;
    తిరిగి sample_fmt;
}

గణన AVSampleFormat av_get_planar_sample_fmt(గణన AVSampleFormat sample_fmt)
{
    ఒకవేళ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        తిరిగి AV_SAMPLE_FMT_NONE;
    ఒకవేళ (sample_fmt_info[sample_fmt].planar)
        తిరిగి sample_fmt;
    తిరిగి sample_fmt_info[sample_fmt].altform;
}

అక్షరం *av_get_sample_fmt_string (అక్షరం *buf, పూర్ణాంకం buf_కొలత, గణన AVSampleFormat sample_fmt)
{
    /* print header */
    ఒకవేళ (sample_fmt < 0)
        snprintf(buf, buf_కొలత, "name  " " depth");
    లేకపోతే ఒకవేళ (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_కొలత, "%-6s" "   %2d ", info.name, info.బిట్లు);
    }

    తిరిగి buf;
}

పూర్ణాంకం av_get_బైట్లు_చొప్పున_sample(గణన AVSampleFormat sample_fmt)
{
     తిరిగి sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].బిట్లు >> 3;
}

పూర్ణాంకం av_sample_fmt_is_planar(గణన AVSampleFormat sample_fmt)
{
     ఒకవేళ (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         తిరిగి 0;
     తిరిగి sample_fmt_info[sample_fmt].planar;
}

పూర్ణాంకం av_samples_get_బఫరు_కొలత(పూర్ణాంకం *linesize, పూర్ణాంకం nb_channels, పూర్ణాంకం nb_samples,
                               గణన AVSampleFormat sample_fmt, పూర్ణాంకం align)
{
    పూర్ణాంకం పంక్తి_కొలత;
    పూర్ణాంకం sample_కొలత = av_get_బైట్లు_చొప్పున_sample(sample_fmt);
    పూర్ణాంకం planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    ఒకవేళ (!sample_కొలత || nb_samples <= 0 || nb_channels <= 0)
        తిరిగి AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    ఒకవేళ (!align) {
        ఒకవేళ (nb_samples > గరిష్ఠ_పూర్ణాంకం - 31)
            తిరిగి AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    ఒకవేళ (nb_channels > గరిష్ఠ_పూర్ణాంకం / align ||
        (int64_t)nb_channels * nb_samples > (గరిష్ఠ_పూర్ణాంకం - (align * nb_channels)) / sample_కొలత)
        తిరిగి AVERROR(EINVAL);

    పంక్తి_కొలత = planar ? FFALIGN(nb_samples * sample_కొలత,               align) :
                         FFALIGN(nb_samples * sample_కొలత * nb_channels, align);
    ఒకవేళ (linesize)
        *linesize = పంక్తి_కొలత;

    తిరిగి planar ? పంక్తి_కొలత * nb_channels : పంక్తి_కొలత;
}

పూర్ణాంకం av_samples_fill_arrays(uint8_t **audio_దత్తాంశం, పూర్ణాంకం *linesize,
                           స్థిరరాశి uint8_t *buf, పూర్ణాంకం nb_channels, పూర్ణాంకం nb_samples,
                           గణన AVSampleFormat sample_fmt, పూర్ణాంకం align)
{
    పూర్ణాంకం ch, planar, buf_కొలత, పంక్తి_కొలత;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_కొలత = av_samples_get_బఫరు_కొలత(&పంక్తి_కొలత, nb_channels, nb_samples,
                                          sample_fmt, align);
    ఒకవేళ (buf_కొలత < 0)
        తిరిగి buf_కొలత;

    ఒకవేళ (linesize)
        *linesize = పంక్తి_కొలత;

    memset(audio_దత్తాంశం, 0, planar
                          ? పరిమాణం(*audio_దత్తాంశం) * nb_channels
                          : పరిమాణం(*audio_దత్తాంశం));

    ఒకవేళ (!buf)
        తిరిగి buf_కొలత;

    audio_దత్తాంశం[0] = (uint8_t *)buf;
    కొరకు (ch = 1; planar && ch < nb_channels; ch++)
        audio_దత్తాంశం[ch] = audio_దత్తాంశం[ch-1] + పంక్తి_కొలత;

    తిరిగి buf_కొలత;
}

పూర్ణాంకం av_samples_alloc(uint8_t **audio_దత్తాంశం, పూర్ణాంకం *linesize, పూర్ణాంకం nb_channels,
                     పూర్ణాంకం nb_samples, గణన AVSampleFormat sample_fmt, పూర్ణాంకం align)
{
    uint8_t *buf;
    పూర్ణాంకం కొలత = av_samples_get_బఫరు_కొలత(ఖాళీ, nb_channels, nb_samples,
                                          sample_fmt, align);
    ఒకవేళ (కొలత < 0)
        తిరిగి కొలత;

    buf = av_malloc(కొలత);
    ఒకవేళ (!buf)
        తిరిగి AVERROR(ENOMEM);

    కొలత = av_samples_fill_arrays(audio_దత్తాంశం, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    ఒకవేళ (కొలత < 0) {
        av_free(buf);
        తిరిగి కొలత;
    }

    av_samples_సమితి_silence(audio_దత్తాంశం, 0, nb_samples, nb_channels, sample_fmt);

    తిరిగి కొలత;
}

పూర్ణాంకం av_samples_alloc_array_and_samples(uint8_t ***audio_దత్తాంశం, పూర్ణాంకం *linesize, పూర్ణాంకం nb_channels,
                                       పూర్ణాంకం nb_samples, గణన AVSampleFormat sample_fmt, పూర్ణాంకం align)
{
    పూర్ణాంకం ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_దత్తాంశం = av_calloc(nb_planes, పరిమాణం(**audio_దత్తాంశం));
    ఒకవేళ (!*audio_దత్తాంశం)
        తిరిగి AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_దత్తాంశం, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    ఒకవేళ (ret < 0)
        av_freep(audio_దత్తాంశం);
    తిరిగి ret;
}

పూర్ణాంకం av_samples_copy(uint8_t * స్థిరరాశి *dst, uint8_t * స్థిరరాశి *src, పూర్ణాంకం dst_స్థానభ్రంశం,
                    పూర్ణాంకం src_స్థానభ్రంశం, పూర్ణాంకం nb_samples, పూర్ణాంకం nb_channels,
                    గణన AVSampleFormat sample_fmt)
{
    పూర్ణాంకం planar      = av_sample_fmt_is_planar(sample_fmt);
    పూర్ణాంకం planes      = planar ? nb_channels : 1;
    పూర్ణాంకం ఖండం_align = av_get_బైట్లు_చొప్పున_sample(sample_fmt) * (planar ? 1 : nb_channels);
    పూర్ణాంకం దత్తాంశం_కొలత   = nb_samples * ఖండం_align;
    పూర్ణాంకం i;

    dst_స్థానభ్రంశం *= ఖండం_align;
    src_స్థానభ్రంశం *= ఖండం_align;

    ఒకవేళ((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= దత్తాంశం_కొలత) {
        కొరకు (i = 0; i < planes; i++)
            జ్ఞాపకం_నకలు(dst[i] + dst_స్థానభ్రంశం, src[i] + src_స్థానభ్రంశం, దత్తాంశం_కొలత);
    } లేకపోతే {
        కొరకు (i = 0; i < planes; i++)
            memmove(dst[i] + dst_స్థానభ్రంశం, src[i] + src_స్థానభ్రంశం, దత్తాంశం_కొలత);
    }

    తిరిగి 0;
}

పూర్ణాంకం av_samples_సమితి_silence(uint8_t * స్థిరరాశి *audio_దత్తాంశం, పూర్ణాంకం స్థానభ్రంశం, పూర్ణాంకం nb_samples,
                           పూర్ణాంకం nb_channels, గణన AVSampleFormat sample_fmt)
{
    పూర్ణాంకం planar      = av_sample_fmt_is_planar(sample_fmt);
    పూర్ణాంకం planes      = planar ? nb_channels : 1;
    పూర్ణాంకం ఖండం_align = av_get_బైట్లు_చొప్పున_sample(sample_fmt) * (planar ? 1 : nb_channels);
    పూర్ణాంకం దత్తాంశం_కొలత   = nb_samples * ఖండం_align;
    పూర్ణాంకం fill_char, i;

    ఒకవేళ (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    లేకపోతే ఒకవేళ (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    లేకపోతే
        fill_char = 0x00;

    స్థానభ్రంశం *= ఖండం_align;

    కొరకు (i = 0; i < planes; i++)
        memset(audio_దత్తాంశం[i] + స్థానభ్రంశం, fill_char, దత్తాంశం_కొలత);

    తిరిగి 0;
}
