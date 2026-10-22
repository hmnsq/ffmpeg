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
    صحيح بٽ;
    صحيح planar;
    تعداد AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
ساكن ثابت SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
    [AV_SAMPLE_FMT_U8]   = { .name =   "u8", .بٽ =  8, .planar = 0, .altform = AV_SAMPLE_FMT_U8P  },
    [AV_SAMPLE_FMT_S16]  = { .name =  "s16", .بٽ = 16, .planar = 0, .altform = AV_SAMPLE_FMT_S16P },
    [AV_SAMPLE_FMT_S32]  = { .name =  "s32", .بٽ = 32, .planar = 0, .altform = AV_SAMPLE_FMT_S32P },
    [AV_SAMPLE_FMT_S64]  = { .name =  "s64", .بٽ = 64, .planar = 0, .altform = AV_SAMPLE_FMT_S64P },
    [AV_SAMPLE_FMT_FLT]  = { .name =  "flt", .بٽ = 32, .planar = 0, .altform = AV_SAMPLE_FMT_FLTP },
    [AV_SAMPLE_FMT_DBL]  = { .name =  "dbl", .بٽ = 64, .planar = 0, .altform = AV_SAMPLE_FMT_DBLP },
    [AV_SAMPLE_FMT_U8P]  = { .name =  "u8p", .بٽ =  8, .planar = 1, .altform = AV_SAMPLE_FMT_U8   },
    [AV_SAMPLE_FMT_S16P] = { .name = "s16p", .بٽ = 16, .planar = 1, .altform = AV_SAMPLE_FMT_S16  },
    [AV_SAMPLE_FMT_S32P] = { .name = "s32p", .بٽ = 32, .planar = 1, .altform = AV_SAMPLE_FMT_S32  },
    [AV_SAMPLE_FMT_S64P] = { .name = "s64p", .بٽ = 64, .planar = 1, .altform = AV_SAMPLE_FMT_S64  },
    [AV_SAMPLE_FMT_FLTP] = { .name = "fltp", .بٽ = 32, .planar = 1, .altform = AV_SAMPLE_FMT_FLT  },
    [AV_SAMPLE_FMT_DBLP] = { .name = "dblp", .بٽ = 64, .planar = 1, .altform = AV_SAMPLE_FMT_DBL  },
    [AV_SAMPLE_FMT_DSD]  = { .name =  "dsd", .بٽ =  8, .planar = 0, .altform = AV_SAMPLE_FMT_DSD  },
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

حرف *av_get_sample_fmt_string (حرف *buf, صحيح buf_سائيز, تعداد AVSampleFormat sample_fmt)
{
    /* print header */
    إذا (sample_fmt < 0)
        snprintf(buf, buf_سائيز, "name  " " depth");
    وإلا إذا (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_سائيز, "%-6s" "   %2d ", info.name, info.بٽ);
    }

    أرجع buf;
}

صحيح av_get_بائيٽون_في_sample(تعداد AVSampleFormat sample_fmt)
{
     أرجع sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].بٽ >> 3;
}

صحيح av_sample_fmt_is_planar(تعداد AVSampleFormat sample_fmt)
{
     إذا (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         أرجع 0;
     أرجع sample_fmt_info[sample_fmt].planar;
}

صحيح av_samples_get_بفر_سائيز(صحيح *linesize, صحيح nb_channels, صحيح nb_samples,
                               تعداد AVSampleFormat sample_fmt, صحيح align)
{
    صحيح سٽ_سائيز;
    صحيح sample_سائيز = av_get_بائيٽون_في_sample(sample_fmt);
    صحيح planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    إذا (!sample_سائيز || nb_samples <= 0 || nb_channels <= 0)
        أرجع AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    إذا (!align) {
        إذا (nb_samples > وڌ_کان_وڌ_عدد - 31)
            أرجع AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    إذا (nb_channels > وڌ_کان_وڌ_عدد / align ||
        (int64_t)nb_channels * nb_samples > (وڌ_کان_وڌ_عدد - (align * nb_channels)) / sample_سائيز)
        أرجع AVERROR(EINVAL);

    سٽ_سائيز = planar ? FFALIGN(nb_samples * sample_سائيز,               align) :
                         FFALIGN(nb_samples * sample_سائيز * nb_channels, align);
    إذا (linesize)
        *linesize = سٽ_سائيز;

    أرجع planar ? سٽ_سائيز * nb_channels : سٽ_سائيز;
}

صحيح av_samples_fill_arrays(uint8_t **audio_معلومات, صحيح *linesize,
                           ثابت uint8_t *buf, صحيح nb_channels, صحيح nb_samples,
                           تعداد AVSampleFormat sample_fmt, صحيح align)
{
    صحيح ch, planar, buf_سائيز, سٽ_سائيز;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_سائيز = av_samples_get_بفر_سائيز(&سٽ_سائيز, nb_channels, nb_samples,
                                          sample_fmt, align);
    إذا (buf_سائيز < 0)
        أرجع buf_سائيز;

    إذا (linesize)
        *linesize = سٽ_سائيز;

    memset(audio_معلومات, 0, planar
                          ? حجم(*audio_معلومات) * nb_channels
                          : حجم(*audio_معلومات));

    إذا (!buf)
        أرجع buf_سائيز;

    audio_معلومات[0] = (uint8_t *)buf;
    لكل (ch = 1; planar && ch < nb_channels; ch++)
        audio_معلومات[ch] = audio_معلومات[ch-1] + سٽ_سائيز;

    أرجع buf_سائيز;
}

صحيح av_samples_alloc(uint8_t **audio_معلومات, صحيح *linesize, صحيح nb_channels,
                     صحيح nb_samples, تعداد AVSampleFormat sample_fmt, صحيح align)
{
    uint8_t *buf;
    صحيح سائيز = av_samples_get_بفر_سائيز(عدم, nb_channels, nb_samples,
                                          sample_fmt, align);
    إذا (سائيز < 0)
        أرجع سائيز;

    buf = av_malloc(سائيز);
    إذا (!buf)
        أرجع AVERROR(ENOMEM);

    سائيز = av_samples_fill_arrays(audio_معلومات, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    إذا (سائيز < 0) {
        av_free(buf);
        أرجع سائيز;
    }

    av_samples_سيٽ_silence(audio_معلومات, 0, nb_samples, nb_channels, sample_fmt);

    أرجع سائيز;
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

صحيح av_samples_copy(uint8_t * ثابت *dst, uint8_t * ثابت *src, صحيح dst_وٿي,
                    صحيح src_وٿي, صحيح nb_samples, صحيح nb_channels,
                    تعداد AVSampleFormat sample_fmt)
{
    صحيح planar      = av_sample_fmt_is_planar(sample_fmt);
    صحيح planes      = planar ? nb_channels : 1;
    صحيح بلاڪ_align = av_get_بائيٽون_في_sample(sample_fmt) * (planar ? 1 : nb_channels);
    صحيح معلومات_سائيز   = nb_samples * بلاڪ_align;
    صحيح i;

    dst_وٿي *= بلاڪ_align;
    src_وٿي *= بلاڪ_align;

    إذا((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= معلومات_سائيز) {
        لكل (i = 0; i < planes; i++)
            يادگيري_نقل(dst[i] + dst_وٿي, src[i] + src_وٿي, معلومات_سائيز);
    } وإلا {
        لكل (i = 0; i < planes; i++)
            memmove(dst[i] + dst_وٿي, src[i] + src_وٿي, معلومات_سائيز);
    }

    أرجع 0;
}

صحيح av_samples_سيٽ_silence(uint8_t * ثابت *audio_معلومات, صحيح وٿي, صحيح nb_samples,
                           صحيح nb_channels, تعداد AVSampleFormat sample_fmt)
{
    صحيح planar      = av_sample_fmt_is_planar(sample_fmt);
    صحيح planes      = planar ? nb_channels : 1;
    صحيح بلاڪ_align = av_get_بائيٽون_في_sample(sample_fmt) * (planar ? 1 : nb_channels);
    صحيح معلومات_سائيز   = nb_samples * بلاڪ_align;
    صحيح fill_char, i;

    إذا (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    وإلا إذا (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    وإلا
        fill_char = 0x00;

    وٿي *= بلاڪ_align;

    لكل (i = 0; i < planes; i++)
        memset(audio_معلومات[i] + وٿي, fill_char, معلومات_سائيز);

    أرجع 0;
}
