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

#شامل "error.h"
#شامل "macros.h"
#شامل "mem.h"
#شامل "samplefmt.h"

#شامل <limits.h>
#شامل <stdio.h>
#شامل <string.h>

قسمتعریف ساخت SampleFmtInfo {
    حرف name[8];
    صحیح بٹ;
    صحیح planar;
    شمار AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
ساکن ثابت SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
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

ثابت حرف *av_get_sample_fmt_name(شمار AVSampleFormat sample_fmt)
{
    اگر (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        واپس تہی;
    واپس sample_fmt_info[sample_fmt].name;
}

شمار AVSampleFormat av_get_sample_fmt(ثابت حرف *name)
{
    صحیح i;

    برائے (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        اگر (!strcmp(sample_fmt_info[i].name, name))
            واپس i;
    واپس AV_SAMPLE_FMT_NONE;
}

شمار AVSampleFormat av_get_alt_sample_fmt(شمار AVSampleFormat sample_fmt, صحیح planar)
{
    اگر (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        واپس AV_SAMPLE_FMT_NONE;
    اگر (sample_fmt_info[sample_fmt].planar == planar)
        واپس sample_fmt;
    واپس sample_fmt_info[sample_fmt].altform;
}

شمار AVSampleFormat av_get_packed_sample_fmt(شمار AVSampleFormat sample_fmt)
{
    اگر (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        واپس AV_SAMPLE_FMT_NONE;
    اگر (sample_fmt_info[sample_fmt].planar)
        واپس sample_fmt_info[sample_fmt].altform;
    واپس sample_fmt;
}

شمار AVSampleFormat av_get_planar_sample_fmt(شمار AVSampleFormat sample_fmt)
{
    اگر (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        واپس AV_SAMPLE_FMT_NONE;
    اگر (sample_fmt_info[sample_fmt].planar)
        واپس sample_fmt;
    واپس sample_fmt_info[sample_fmt].altform;
}

حرف *av_get_sample_fmt_string (حرف *buf, صحیح buf_سائز, شمار AVSampleFormat sample_fmt)
{
    /* print header */
    اگر (sample_fmt < 0)
        snprintf(buf, buf_سائز, "name  " " depth");
    ورنہ اگر (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_سائز, "%-6s" "   %2d ", info.name, info.بٹ);
    }

    واپس buf;
}

صحیح av_get_بائٹیں_فی_sample(شمار AVSampleFormat sample_fmt)
{
     واپس sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].بٹ >> 3;
}

صحیح av_sample_fmt_is_planar(شمار AVSampleFormat sample_fmt)
{
     اگر (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         واپس 0;
     واپس sample_fmt_info[sample_fmt].planar;
}

صحیح av_samples_get_بفر_سائز(صحیح *linesize, صحیح nb_channels, صحیح nb_samples,
                               شمار AVSampleFormat sample_fmt, صحیح align)
{
    صحیح سطر_سائز;
    صحیح sample_سائز = av_get_بائٹیں_فی_sample(sample_fmt);
    صحیح planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    اگر (!sample_سائز || nb_samples <= 0 || nb_channels <= 0)
        واپس AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    اگر (!align) {
        اگر (nb_samples > زیادہ_سے_زیادہ_عدد - 31)
            واپس AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    اگر (nb_channels > زیادہ_سے_زیادہ_عدد / align ||
        (int64_t)nb_channels * nb_samples > (زیادہ_سے_زیادہ_عدد - (align * nb_channels)) / sample_سائز)
        واپس AVERROR(EINVAL);

    سطر_سائز = planar ? FFALIGN(nb_samples * sample_سائز,               align) :
                         FFALIGN(nb_samples * sample_سائز * nb_channels, align);
    اگر (linesize)
        *linesize = سطر_سائز;

    واپس planar ? سطر_سائز * nb_channels : سطر_سائز;
}

صحیح av_samples_fill_arrays(uint8_t **audio_ڈیٹا, صحیح *linesize,
                           ثابت uint8_t *buf, صحیح nb_channels, صحیح nb_samples,
                           شمار AVSampleFormat sample_fmt, صحیح align)
{
    صحیح ch, planar, buf_سائز, سطر_سائز;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_سائز = av_samples_get_بفر_سائز(&سطر_سائز, nb_channels, nb_samples,
                                          sample_fmt, align);
    اگر (buf_سائز < 0)
        واپس buf_سائز;

    اگر (linesize)
        *linesize = سطر_سائز;

    memset(audio_ڈیٹا, 0, planar
                          ? حجم(*audio_ڈیٹا) * nb_channels
                          : حجم(*audio_ڈیٹا));

    اگر (!buf)
        واپس buf_سائز;

    audio_ڈیٹا[0] = (uint8_t *)buf;
    برائے (ch = 1; planar && ch < nb_channels; ch++)
        audio_ڈیٹا[ch] = audio_ڈیٹا[ch-1] + سطر_سائز;

    واپس buf_سائز;
}

صحیح av_samples_alloc(uint8_t **audio_ڈیٹا, صحیح *linesize, صحیح nb_channels,
                     صحیح nb_samples, شمار AVSampleFormat sample_fmt, صحیح align)
{
    uint8_t *buf;
    صحیح سائز = av_samples_get_بفر_سائز(تہی, nb_channels, nb_samples,
                                          sample_fmt, align);
    اگر (سائز < 0)
        واپس سائز;

    buf = av_malloc(سائز);
    اگر (!buf)
        واپس AVERROR(ENOMEM);

    سائز = av_samples_fill_arrays(audio_ڈیٹا, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    اگر (سائز < 0) {
        av_free(buf);
        واپس سائز;
    }

    av_samples_سیٹ_silence(audio_ڈیٹا, 0, nb_samples, nb_channels, sample_fmt);

    واپس سائز;
}

صحیح av_samples_alloc_array_and_samples(uint8_t ***audio_ڈیٹا, صحیح *linesize, صحیح nb_channels,
                                       صحیح nb_samples, شمار AVSampleFormat sample_fmt, صحیح align)
{
    صحیح ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_ڈیٹا = av_calloc(nb_planes, حجم(**audio_ڈیٹا));
    اگر (!*audio_ڈیٹا)
        واپس AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_ڈیٹا, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    اگر (ret < 0)
        av_freep(audio_ڈیٹا);
    واپس ret;
}

صحیح av_samples_copy(uint8_t * ثابت *dst, uint8_t * ثابت *src, صحیح dst_انحراف,
                    صحیح src_انحراف, صحیح nb_samples, صحیح nb_channels,
                    شمار AVSampleFormat sample_fmt)
{
    صحیح planar      = av_sample_fmt_is_planar(sample_fmt);
    صحیح planes      = planar ? nb_channels : 1;
    صحیح بلاک_align = av_get_بائٹیں_فی_sample(sample_fmt) * (planar ? 1 : nb_channels);
    صحیح ڈیٹا_سائز   = nb_samples * بلاک_align;
    صحیح i;

    dst_انحراف *= بلاک_align;
    src_انحراف *= بلاک_align;

    اگر((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= ڈیٹا_سائز) {
        برائے (i = 0; i < planes; i++)
            حافظہ_نقل(dst[i] + dst_انحراف, src[i] + src_انحراف, ڈیٹا_سائز);
    } ورنہ {
        برائے (i = 0; i < planes; i++)
            memmove(dst[i] + dst_انحراف, src[i] + src_انحراف, ڈیٹا_سائز);
    }

    واپس 0;
}

صحیح av_samples_سیٹ_silence(uint8_t * ثابت *audio_ڈیٹا, صحیح انحراف, صحیح nb_samples,
                           صحیح nb_channels, شمار AVSampleFormat sample_fmt)
{
    صحیح planar      = av_sample_fmt_is_planar(sample_fmt);
    صحیح planes      = planar ? nb_channels : 1;
    صحیح بلاک_align = av_get_بائٹیں_فی_sample(sample_fmt) * (planar ? 1 : nb_channels);
    صحیح ڈیٹا_سائز   = nb_samples * بلاک_align;
    صحیح fill_char, i;

    اگر (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    ورنہ اگر (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    ورنہ
        fill_char = 0x00;

    انحراف *= بلاک_align;

    برائے (i = 0; i < planes; i++)
        memset(audio_ڈیٹا[i] + انحراف, fill_char, ڈیٹا_سائز);

    واپس 0;
}
