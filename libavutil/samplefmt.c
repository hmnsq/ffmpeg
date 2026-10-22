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
    صحيح بٹ;
    صحيح planar;
    تعداد AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
ساكن ثابت SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
    [AV_SAMPLE_FMT_U8]   = { .name =   "u8", .بٹ =  8, .planar = 0, .altform = AV_SAMPLE_FMT_U8P  },
    [AV_SAMPLE_FMT_S16]  = { .name =  "s16", .بٹ = 16, .planar = 0, .altform = AV_SAMPLE_FMT_S16P },
    [AV_SAMPLE_FMT_S32]  = { .name =  "s32", .بٹ = 32, .planar = 0, .altform = AV_SAMPLE_FMT_S32P },
    [AV_SAMPLE_FMT_S64]  = { .name =  "s64", .بٹ = 64, .planar = 0, .altform = AV_SAMPLE_FMT_S64P },
    [AV_SAMPLE_FMT_FLT]  = { .name =  "flt", .بٹ = 32, .planar = 0, .altform = AV_SAMPLE_FMT_FLTP },
    [AV_SAMPLE_FMT_DBL]  = { .name =  "dbl", .بٹ = 64, .planar = 0, .altform = AV_SAMPLE_FMT_DBLP },
    [AV_SAMPLE_FMT_U8P]  = { .name =  "u8p", .بٹ =  8, .planar = 1, .altform = AV_SAMPLE_FMT_U8   },
    [AV_SAMPLE_FMT_S16P] = { .name = "s16p", .بٹ = 16, .planar = 1, .altform = AV_SAMPLE_FMT_S16  },
    [AV_SAMPLE_FMT_S32P] = { .name = "s32p", .بٹ = 32, .planar = 1, .altform = AV_SAMPLE_FMT_S32  },
    [AV_SAMPLE_FMT_S64P] = { .name = "s64p", .بٹ = 64, .planar = 1, .altform = AV_SAMPLE_FMT_S64  },
    [AV_SAMPLE_FMT_FLTP] = { .name = "fltp", .بٹ = 32, .planar = 1, .altform = AV_SAMPLE_FMT_FLT  },
    [AV_SAMPLE_FMT_DBLP] = { .name = "dblp", .بٹ = 64, .planar = 1, .altform = AV_SAMPLE_FMT_DBL  },
    [AV_SAMPLE_FMT_DSD]  = { .name =  "dsd", .بٹ =  8, .planar = 0, .altform = AV_SAMPLE_FMT_DSD  },
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

حرف *av_get_sample_fmt_string (حرف *buf, صحيح buf_ناپ, تعداد AVSampleFormat sample_fmt)
{
    /* print header */
    إذا (sample_fmt < 0)
        snprintf(buf, buf_ناپ, "name  " " depth");
    وإلا إذا (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_ناپ, "%-6s" "   %2d ", info.name, info.بٹ);
    }

    أرجع buf;
}

صحيح av_get_بائٹاں_فی_sample(تعداد AVSampleFormat sample_fmt)
{
     أرجع sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].بٹ >> 3;
}

صحيح av_sample_fmt_is_planar(تعداد AVSampleFormat sample_fmt)
{
     إذا (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         أرجع 0;
     أرجع sample_fmt_info[sample_fmt].planar;
}

صحيح av_samples_get_بفر_ناپ(صحيح *linesize, صحيح nb_channels, صحيح nb_samples,
                               تعداد AVSampleFormat sample_fmt, صحيح align)
{
    صحيح سطر_ناپ;
    صحيح sample_ناپ = av_get_بائٹاں_فی_sample(sample_fmt);
    صحيح planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    إذا (!sample_ناپ || nb_samples <= 0 || nb_channels <= 0)
        أرجع AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    إذا (!align) {
        إذا (nb_samples > ودھ_توں_ودھ_عدد - 31)
            أرجع AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    إذا (nb_channels > ودھ_توں_ودھ_عدد / align ||
        (int64_t)nb_channels * nb_samples > (ودھ_توں_ودھ_عدد - (align * nb_channels)) / sample_ناپ)
        أرجع AVERROR(EINVAL);

    سطر_ناپ = planar ? FFALIGN(nb_samples * sample_ناپ,               align) :
                         FFALIGN(nb_samples * sample_ناپ * nb_channels, align);
    إذا (linesize)
        *linesize = سطر_ناپ;

    أرجع planar ? سطر_ناپ * nb_channels : سطر_ناپ;
}

صحيح av_samples_fill_arrays(uint8_t **audio_انکڑے, صحيح *linesize,
                           ثابت uint8_t *buf, صحيح nb_channels, صحيح nb_samples,
                           تعداد AVSampleFormat sample_fmt, صحيح align)
{
    صحيح ch, planar, buf_ناپ, سطر_ناپ;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_ناپ = av_samples_get_بفر_ناپ(&سطر_ناپ, nb_channels, nb_samples,
                                          sample_fmt, align);
    إذا (buf_ناپ < 0)
        أرجع buf_ناپ;

    إذا (linesize)
        *linesize = سطر_ناپ;

    memset(audio_انکڑے, 0, planar
                          ? حجم(*audio_انکڑے) * nb_channels
                          : حجم(*audio_انکڑے));

    إذا (!buf)
        أرجع buf_ناپ;

    audio_انکڑے[0] = (uint8_t *)buf;
    لكل (ch = 1; planar && ch < nb_channels; ch++)
        audio_انکڑے[ch] = audio_انکڑے[ch-1] + سطر_ناپ;

    أرجع buf_ناپ;
}

صحيح av_samples_alloc(uint8_t **audio_انکڑے, صحيح *linesize, صحيح nb_channels,
                     صحيح nb_samples, تعداد AVSampleFormat sample_fmt, صحيح align)
{
    uint8_t *buf;
    صحيح ناپ = av_samples_get_بفر_ناپ(عدم, nb_channels, nb_samples,
                                          sample_fmt, align);
    إذا (ناپ < 0)
        أرجع ناپ;

    buf = av_malloc(ناپ);
    إذا (!buf)
        أرجع AVERROR(ENOMEM);

    ناپ = av_samples_fill_arrays(audio_انکڑے, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    إذا (ناپ < 0) {
        av_free(buf);
        أرجع ناپ;
    }

    av_samples_سیٹ_silence(audio_انکڑے, 0, nb_samples, nb_channels, sample_fmt);

    أرجع ناپ;
}

صحيح av_samples_alloc_array_and_samples(uint8_t ***audio_انکڑے, صحيح *linesize, صحيح nb_channels,
                                       صحيح nb_samples, تعداد AVSampleFormat sample_fmt, صحيح align)
{
    صحيح ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_انکڑے = av_calloc(nb_planes, حجم(**audio_انکڑے));
    إذا (!*audio_انکڑے)
        أرجع AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_انکڑے, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    إذا (ret < 0)
        av_freep(audio_انکڑے);
    أرجع ret;
}

صحيح av_samples_copy(uint8_t * ثابت *dst, uint8_t * ثابت *src, صحيح dst_وتھ,
                    صحيح src_وتھ, صحيح nb_samples, صحيح nb_channels,
                    تعداد AVSampleFormat sample_fmt)
{
    صحيح planar      = av_sample_fmt_is_planar(sample_fmt);
    صحيح planes      = planar ? nb_channels : 1;
    صحيح بلاک_align = av_get_بائٹاں_فی_sample(sample_fmt) * (planar ? 1 : nb_channels);
    صحيح انکڑے_ناپ   = nb_samples * بلاک_align;
    صحيح i;

    dst_وتھ *= بلاک_align;
    src_وتھ *= بلاک_align;

    إذا((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= انکڑے_ناپ) {
        لكل (i = 0; i < planes; i++)
            حافظہ_نقل(dst[i] + dst_وتھ, src[i] + src_وتھ, انکڑے_ناپ);
    } وإلا {
        لكل (i = 0; i < planes; i++)
            memmove(dst[i] + dst_وتھ, src[i] + src_وتھ, انکڑے_ناپ);
    }

    أرجع 0;
}

صحيح av_samples_سیٹ_silence(uint8_t * ثابت *audio_انکڑے, صحيح وتھ, صحيح nb_samples,
                           صحيح nb_channels, تعداد AVSampleFormat sample_fmt)
{
    صحيح planar      = av_sample_fmt_is_planar(sample_fmt);
    صحيح planes      = planar ? nb_channels : 1;
    صحيح بلاک_align = av_get_بائٹاں_فی_sample(sample_fmt) * (planar ? 1 : nb_channels);
    صحيح انکڑے_ناپ   = nb_samples * بلاک_align;
    صحيح fill_char, i;

    إذا (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    وإلا إذا (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    وإلا
        fill_char = 0x00;

    وتھ *= بلاک_align;

    لكل (i = 0; i < planes; i++)
        memset(audio_انکڑے[i] + وتھ, fill_char, انکڑے_ناپ);

    أرجع 0;
}
