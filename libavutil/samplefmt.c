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

#ضمن "error.h"
#ضمن "macros.h"
#ضمن "mem.h"
#ضمن "samplefmt.h"

#ضمن <limits.h>
#ضمن <stdio.h>
#ضمن <string.h>

تعريفنوع بنية SampleFmtInfo {
    حرف name[8];
    صحيح بټونه;
    صحيح planar;
    تعداد AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
ساكن ثابت SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
    [AV_SAMPLE_FMT_U8]   = { .name =   "u8", .بټونه =  8, .planar = 0, .altform = AV_SAMPLE_FMT_U8P  },
    [AV_SAMPLE_FMT_S16]  = { .name =  "s16", .بټونه = 16, .planar = 0, .altform = AV_SAMPLE_FMT_S16P },
    [AV_SAMPLE_FMT_S32]  = { .name =  "s32", .بټونه = 32, .planar = 0, .altform = AV_SAMPLE_FMT_S32P },
    [AV_SAMPLE_FMT_S64]  = { .name =  "s64", .بټونه = 64, .planar = 0, .altform = AV_SAMPLE_FMT_S64P },
    [AV_SAMPLE_FMT_FLT]  = { .name =  "flt", .بټونه = 32, .planar = 0, .altform = AV_SAMPLE_FMT_FLTP },
    [AV_SAMPLE_FMT_DBL]  = { .name =  "dbl", .بټونه = 64, .planar = 0, .altform = AV_SAMPLE_FMT_DBLP },
    [AV_SAMPLE_FMT_U8P]  = { .name =  "u8p", .بټونه =  8, .planar = 1, .altform = AV_SAMPLE_FMT_U8   },
    [AV_SAMPLE_FMT_S16P] = { .name = "s16p", .بټونه = 16, .planar = 1, .altform = AV_SAMPLE_FMT_S16  },
    [AV_SAMPLE_FMT_S32P] = { .name = "s32p", .بټونه = 32, .planar = 1, .altform = AV_SAMPLE_FMT_S32  },
    [AV_SAMPLE_FMT_S64P] = { .name = "s64p", .بټونه = 64, .planar = 1, .altform = AV_SAMPLE_FMT_S64  },
    [AV_SAMPLE_FMT_FLTP] = { .name = "fltp", .بټونه = 32, .planar = 1, .altform = AV_SAMPLE_FMT_FLT  },
    [AV_SAMPLE_FMT_DBLP] = { .name = "dblp", .بټونه = 64, .planar = 1, .altform = AV_SAMPLE_FMT_DBL  },
    [AV_SAMPLE_FMT_DSD]  = { .name =  "dsd", .بټونه =  8, .planar = 0, .altform = AV_SAMPLE_FMT_DSD  },
};

ثابت حرف *av_get_sample_fmt_name(تعداد AVSampleFormat sample_fmt)
{
    إذا (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        أرجع عدم;
    أرجع sample_fmt_info[sample_fmt].name;
}

تعداد AVSampleFormat av_get_sample_fmt(ثابت حرف *name)
{
    صحيح i;

    لكل (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        إذا (!strcmp(sample_fmt_info[i].name, name))
            أرجع i;
    أرجع AV_SAMPLE_FMT_NONE;
}

تعداد AVSampleFormat av_get_alt_sample_fmt(تعداد AVSampleFormat sample_fmt, صحيح planar)
{
    إذا (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        أرجع AV_SAMPLE_FMT_NONE;
    إذا (sample_fmt_info[sample_fmt].planar == planar)
        أرجع sample_fmt;
    أرجع sample_fmt_info[sample_fmt].altform;
}

تعداد AVSampleFormat av_get_packed_sample_fmt(تعداد AVSampleFormat sample_fmt)
{
    إذا (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        أرجع AV_SAMPLE_FMT_NONE;
    إذا (sample_fmt_info[sample_fmt].planar)
        أرجع sample_fmt_info[sample_fmt].altform;
    أرجع sample_fmt;
}

تعداد AVSampleFormat av_get_planar_sample_fmt(تعداد AVSampleFormat sample_fmt)
{
    إذا (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        أرجع AV_SAMPLE_FMT_NONE;
    إذا (sample_fmt_info[sample_fmt].planar)
        أرجع sample_fmt;
    أرجع sample_fmt_info[sample_fmt].altform;
}

حرف *av_get_sample_fmt_string (حرف *buf, صحيح buf_اندازه, تعداد AVSampleFormat sample_fmt)
{
    /* print header */
    إذا (sample_fmt < 0)
        snprintf(buf, buf_اندازه, "name  " " depth");
    وإلا إذا (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_اندازه, "%-6s" "   %2d ", info.name, info.بټونه);
    }

    أرجع buf;
}

صحيح av_get_بایټونه_فی_sample(تعداد AVSampleFormat sample_fmt)
{
     أرجع sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].بټونه >> 3;
}

صحيح av_sample_fmt_is_planar(تعداد AVSampleFormat sample_fmt)
{
     إذا (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         أرجع 0;
     أرجع sample_fmt_info[sample_fmt].planar;
}

صحيح av_samples_get_بفر_اندازه(صحيح *linesize, صحيح nb_channels, صحيح nb_samples,
                               تعداد AVSampleFormat sample_fmt, صحيح align)
{
    صحيح کرښه_اندازه;
    صحيح sample_اندازه = av_get_بایټونه_فی_sample(sample_fmt);
    صحيح planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    إذا (!sample_اندازه || nb_samples <= 0 || nb_channels <= 0)
        أرجع AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    إذا (!align) {
        إذا (nb_samples > لوی_عدد - 31)
            أرجع AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    إذا (nb_channels > لوی_عدد / align ||
        (int64_t)nb_channels * nb_samples > (لوی_عدد - (align * nb_channels)) / sample_اندازه)
        أرجع AVERROR(EINVAL);

    کرښه_اندازه = planar ? FFALIGN(nb_samples * sample_اندازه,               align) :
                         FFALIGN(nb_samples * sample_اندازه * nb_channels, align);
    إذا (linesize)
        *linesize = کرښه_اندازه;

    أرجع planar ? کرښه_اندازه * nb_channels : کرښه_اندازه;
}

صحيح av_samples_fill_arrays(uint8_t **audio_معلومات, صحيح *linesize,
                           ثابت uint8_t *buf, صحيح nb_channels, صحيح nb_samples,
                           تعداد AVSampleFormat sample_fmt, صحيح align)
{
    صحيح ch, planar, buf_اندازه, کرښه_اندازه;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_اندازه = av_samples_get_بفر_اندازه(&کرښه_اندازه, nb_channels, nb_samples,
                                          sample_fmt, align);
    إذا (buf_اندازه < 0)
        أرجع buf_اندازه;

    إذا (linesize)
        *linesize = کرښه_اندازه;

    memset(audio_معلومات, 0, planar
                          ? حجم(*audio_معلومات) * nb_channels
                          : حجم(*audio_معلومات));

    إذا (!buf)
        أرجع buf_اندازه;

    audio_معلومات[0] = (uint8_t *)buf;
    لكل (ch = 1; planar && ch < nb_channels; ch++)
        audio_معلومات[ch] = audio_معلومات[ch-1] + کرښه_اندازه;

    أرجع buf_اندازه;
}

صحيح av_samples_alloc(uint8_t **audio_معلومات, صحيح *linesize, صحيح nb_channels,
                     صحيح nb_samples, تعداد AVSampleFormat sample_fmt, صحيح align)
{
    uint8_t *buf;
    صحيح اندازه = av_samples_get_بفر_اندازه(عدم, nb_channels, nb_samples,
                                          sample_fmt, align);
    إذا (اندازه < 0)
        أرجع اندازه;

    buf = av_malloc(اندازه);
    إذا (!buf)
        أرجع AVERROR(ENOMEM);

    اندازه = av_samples_fill_arrays(audio_معلومات, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    إذا (اندازه < 0) {
        av_free(buf);
        أرجع اندازه;
    }

    av_samples_سېټ_silence(audio_معلومات, 0, nb_samples, nb_channels, sample_fmt);

    أرجع اندازه;
}

صحيح av_samples_alloc_array_and_samples(uint8_t ***audio_معلومات, صحيح *linesize, صحيح nb_channels,
                                       صحيح nb_samples, تعداد AVSampleFormat sample_fmt, صحيح align)
{
    صحيح ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_معلومات = av_calloc(nb_planes, حجم(**audio_معلومات));
    إذا (!*audio_معلومات)
        أرجع AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_معلومات, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    إذا (ret < 0)
        av_freep(audio_معلومات);
    أرجع ret;
}

صحيح av_samples_copy(uint8_t * ثابت *dst, uint8_t * ثابت *src, صحيح dst_دننه_واټن,
                    صحيح src_دننه_واټن, صحيح nb_samples, صحيح nb_channels,
                    تعداد AVSampleFormat sample_fmt)
{
    صحيح planar      = av_sample_fmt_is_planar(sample_fmt);
    صحيح planes      = planar ? nb_channels : 1;
    صحيح بلاک_align = av_get_بایټونه_فی_sample(sample_fmt) * (planar ? 1 : nb_channels);
    صحيح معلومات_اندازه   = nb_samples * بلاک_align;
    صحيح i;

    dst_دننه_واټن *= بلاک_align;
    src_دننه_واټن *= بلاک_align;

    إذا((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= معلومات_اندازه) {
        لكل (i = 0; i < planes; i++)
            حافظه_نقل(dst[i] + dst_دننه_واټن, src[i] + src_دننه_واټن, معلومات_اندازه);
    } وإلا {
        لكل (i = 0; i < planes; i++)
            memmove(dst[i] + dst_دننه_واټن, src[i] + src_دننه_واټن, معلومات_اندازه);
    }

    أرجع 0;
}

صحيح av_samples_سېټ_silence(uint8_t * ثابت *audio_معلومات, صحيح دننه_واټن, صحيح nb_samples,
                           صحيح nb_channels, تعداد AVSampleFormat sample_fmt)
{
    صحيح planar      = av_sample_fmt_is_planar(sample_fmt);
    صحيح planes      = planar ? nb_channels : 1;
    صحيح بلاک_align = av_get_بایټونه_فی_sample(sample_fmt) * (planar ? 1 : nb_channels);
    صحيح معلومات_اندازه   = nb_samples * بلاک_align;
    صحيح fill_char, i;

    إذا (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    وإلا إذا (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    وإلا
        fill_char = 0x00;

    دننه_واټن *= بلاک_align;

    لكل (i = 0; i < planes; i++)
        memset(audio_معلومات[i] + دننه_واټن, fill_char, معلومات_اندازه);

    أرجع 0;
}
