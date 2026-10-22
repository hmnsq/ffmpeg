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

#অন্তর্ভাব "error.h"
#অন্তর্ভাব "macros.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "samplefmt.h"

#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

প্রকারলেখ কাঠামো SampleFmtInfo {
    অক্ষর name[8];
    পূর্ণসংখ্যা bits;
    পূর্ণসংখ্যা planar;
    গণনা AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
স্থির ধ্রুবক SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
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

ধ্রুবক অক্ষর *av_get_sample_fmt_name(গণনা AVSampleFormat sample_fmt)
{
    যদি (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ফেরত ফাঁকা;
    ফেরত sample_fmt_info[sample_fmt].name;
}

গণনা AVSampleFormat av_get_sample_fmt(ধ্রুবক অক্ষর *name)
{
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        যদি (!strcmp(sample_fmt_info[i].name, name))
            ফেরত i;
    ফেরত AV_SAMPLE_FMT_NONE;
}

গণনা AVSampleFormat av_get_alt_sample_fmt(গণনা AVSampleFormat sample_fmt, পূর্ণসংখ্যা planar)
{
    যদি (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ফেরত AV_SAMPLE_FMT_NONE;
    যদি (sample_fmt_info[sample_fmt].planar == planar)
        ফেরত sample_fmt;
    ফেরত sample_fmt_info[sample_fmt].altform;
}

গণনা AVSampleFormat av_get_packed_sample_fmt(গণনা AVSampleFormat sample_fmt)
{
    যদি (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ফেরত AV_SAMPLE_FMT_NONE;
    যদি (sample_fmt_info[sample_fmt].planar)
        ফেরত sample_fmt_info[sample_fmt].altform;
    ফেরত sample_fmt;
}

গণনা AVSampleFormat av_get_planar_sample_fmt(গণনা AVSampleFormat sample_fmt)
{
    যদি (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        ফেরত AV_SAMPLE_FMT_NONE;
    যদি (sample_fmt_info[sample_fmt].planar)
        ফেরত sample_fmt;
    ফেরত sample_fmt_info[sample_fmt].altform;
}

অক্ষর *av_get_sample_fmt_string (অক্ষর *buf, পূর্ণসংখ্যা buf_আকার, গণনা AVSampleFormat sample_fmt)
{
    /* print header */
    যদি (sample_fmt < 0)
        snprintf(buf, buf_আকার, "name  " " depth");
    অন্যথা যদি (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_আকার, "%-6s" "   %2d ", info.name, info.bits);
    }

    ফেরত buf;
}

পূর্ণসংখ্যা av_get_bytes_per_sample(গণনা AVSampleFormat sample_fmt)
{
     ফেরত sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

পূর্ণসংখ্যা av_sample_fmt_is_planar(গণনা AVSampleFormat sample_fmt)
{
     যদি (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         ফেরত 0;
     ফেরত sample_fmt_info[sample_fmt].planar;
}

পূর্ণসংখ্যা av_samples_get_বাফার_আকার(পূর্ণসংখ্যা *linesize, পূর্ণসংখ্যা nb_channels, পূর্ণসংখ্যা nb_samples,
                               গণনা AVSampleFormat sample_fmt, পূর্ণসংখ্যা align)
{
    পূর্ণসংখ্যা সারি_আকার;
    পূর্ণসংখ্যা sample_আকার = av_get_bytes_per_sample(sample_fmt);
    পূর্ণসংখ্যা planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    যদি (!sample_আকার || nb_samples <= 0 || nb_channels <= 0)
        ফেরত AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    যদি (!align) {
        যদি (nb_samples > INT_MAX - 31)
            ফেরত AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    যদি (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_আকার)
        ফেরত AVERROR(EINVAL);

    সারি_আকার = planar ? FFALIGN(nb_samples * sample_আকার,               align) :
                         FFALIGN(nb_samples * sample_আকার * nb_channels, align);
    যদি (linesize)
        *linesize = সারি_আকার;

    ফেরত planar ? সারি_আকার * nb_channels : সারি_আকার;
}

পূর্ণসংখ্যা av_samples_fill_arrays(uint8_t **audio_তথ্য, পূর্ণসংখ্যা *linesize,
                           ধ্রুবক uint8_t *buf, পূর্ণসংখ্যা nb_channels, পূর্ণসংখ্যা nb_samples,
                           গণনা AVSampleFormat sample_fmt, পূর্ণসংখ্যা align)
{
    পূর্ণসংখ্যা ch, planar, buf_আকার, সারি_আকার;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_আকার = av_samples_get_বাফার_আকার(&সারি_আকার, nb_channels, nb_samples,
                                          sample_fmt, align);
    যদি (buf_আকার < 0)
        ফেরত buf_আকার;

    যদি (linesize)
        *linesize = সারি_আকার;

    memset(audio_তথ্য, 0, planar
                          ? আকার(*audio_তথ্য) * nb_channels
                          : আকার(*audio_তথ্য));

    যদি (!buf)
        ফেরত buf_আকার;

    audio_তথ্য[0] = (uint8_t *)buf;
    জন্য (ch = 1; planar && ch < nb_channels; ch++)
        audio_তথ্য[ch] = audio_তথ্য[ch-1] + সারি_আকার;

    ফেরত buf_আকার;
}

পূর্ণসংখ্যা av_samples_alloc(uint8_t **audio_তথ্য, পূর্ণসংখ্যা *linesize, পূর্ণসংখ্যা nb_channels,
                     পূর্ণসংখ্যা nb_samples, গণনা AVSampleFormat sample_fmt, পূর্ণসংখ্যা align)
{
    uint8_t *buf;
    পূর্ণসংখ্যা আকার_2 = av_samples_get_বাফার_আকার(ফাঁকা, nb_channels, nb_samples,
                                          sample_fmt, align);
    যদি (আকার_2 < 0)
        ফেরত আকার_2;

    buf = av_malloc(আকার_2);
    যদি (!buf)
        ফেরত AVERROR(ENOMEM);

    আকার_2 = av_samples_fill_arrays(audio_তথ্য, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    যদি (আকার_2 < 0) {
        av_free(buf);
        ফেরত আকার_2;
    }

    av_samples_set_silence(audio_তথ্য, 0, nb_samples, nb_channels, sample_fmt);

    ফেরত আকার_2;
}

পূর্ণসংখ্যা av_samples_alloc_array_and_samples(uint8_t ***audio_তথ্য, পূর্ণসংখ্যা *linesize, পূর্ণসংখ্যা nb_channels,
                                       পূর্ণসংখ্যা nb_samples, গণনা AVSampleFormat sample_fmt, পূর্ণসংখ্যা align)
{
    পূর্ণসংখ্যা ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_তথ্য = av_calloc(nb_planes, আকার(**audio_তথ্য));
    যদি (!*audio_তথ্য)
        ফেরত AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_তথ্য, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    যদি (ret < 0)
        av_freep(audio_তথ্য);
    ফেরত ret;
}

পূর্ণসংখ্যা av_samples_copy(uint8_t * ধ্রুবক *dst, uint8_t * ধ্রুবক *src, পূর্ণসংখ্যা dst_offset,
                    পূর্ণসংখ্যা src_offset, পূর্ণসংখ্যা nb_samples, পূর্ণসংখ্যা nb_channels,
                    গণনা AVSampleFormat sample_fmt)
{
    পূর্ণসংখ্যা planar      = av_sample_fmt_is_planar(sample_fmt);
    পূর্ণসংখ্যা planes      = planar ? nb_channels : 1;
    পূর্ণসংখ্যা block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    পূর্ণসংখ্যা তথ্য_আকার   = nb_samples * block_align;
    পূর্ণসংখ্যা i;

    dst_offset *= block_align;
    src_offset *= block_align;

    যদি((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= তথ্য_আকার) {
        জন্য (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, তথ্য_আকার);
    } অন্যথা {
        জন্য (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, তথ্য_আকার);
    }

    ফেরত 0;
}

পূর্ণসংখ্যা av_samples_set_silence(uint8_t * ধ্রুবক *audio_তথ্য, পূর্ণসংখ্যা offset, পূর্ণসংখ্যা nb_samples,
                           পূর্ণসংখ্যা nb_channels, গণনা AVSampleFormat sample_fmt)
{
    পূর্ণসংখ্যা planar      = av_sample_fmt_is_planar(sample_fmt);
    পূর্ণসংখ্যা planes      = planar ? nb_channels : 1;
    পূর্ণসংখ্যা block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    পূর্ণসংখ্যা তথ্য_আকার   = nb_samples * block_align;
    পূর্ণসংখ্যা fill_char, i;

    যদি (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    অন্যথা যদি (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    অন্যথা
        fill_char = 0x00;

    offset *= block_align;

    জন্য (i = 0; i < planes; i++)
        memset(audio_তথ্য[i] + offset, fill_char, তথ্য_আকার);

    ফেরত 0;
}
