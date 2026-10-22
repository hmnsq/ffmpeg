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
    صحيح bits;
    صحيح planar;
    تعداد AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
ساكن ثابت SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
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

ثابت حرف *av_get_sample_fmt_name(تعداد AVSampleFormat sample_fmt)
{
    אם (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        החזר عدم;
    החזר sample_fmt_info[sample_fmt].name;
}

تعداد AVSampleFormat av_get_sample_fmt(ثابت حرف *name)
{
    صحيح i;

    עבור (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        אם (!strcmp(sample_fmt_info[i].name, name))
            החזר i;
    החזר AV_SAMPLE_FMT_NONE;
}

تعداد AVSampleFormat av_get_alt_sample_fmt(تعداد AVSampleFormat sample_fmt, صحيح planar)
{
    אם (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        החזר AV_SAMPLE_FMT_NONE;
    אם (sample_fmt_info[sample_fmt].planar == planar)
        החזר sample_fmt;
    החזר sample_fmt_info[sample_fmt].altform;
}

تعداد AVSampleFormat av_get_packed_sample_fmt(تعداد AVSampleFormat sample_fmt)
{
    אם (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        החזר AV_SAMPLE_FMT_NONE;
    אם (sample_fmt_info[sample_fmt].planar)
        החזר sample_fmt_info[sample_fmt].altform;
    החזר sample_fmt;
}

تعداد AVSampleFormat av_get_planar_sample_fmt(تعداد AVSampleFormat sample_fmt)
{
    אם (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        החזר AV_SAMPLE_FMT_NONE;
    אם (sample_fmt_info[sample_fmt].planar)
        החזר sample_fmt;
    החזר sample_fmt_info[sample_fmt].altform;
}

حرف *av_get_sample_fmt_string (حرف *buf, صحيح buf_size, تعداد AVSampleFormat sample_fmt)
{
    /* print header */
    אם (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    אחרת אם (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    החזר buf;
}

صحيح av_get_bytes_per_sample(تعداد AVSampleFormat sample_fmt)
{
     החזר sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

صحيح av_sample_fmt_is_planar(تعداد AVSampleFormat sample_fmt)
{
     אם (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         החזר 0;
     החזר sample_fmt_info[sample_fmt].planar;
}

صحيح av_samples_get_buffer_size(صحيح *linesize, صحيح nb_channels, صحيح nb_samples,
                               تعداد AVSampleFormat sample_fmt, صحيح align)
{
    صحيح line_size;
    صحيح sample_size = av_get_bytes_per_sample(sample_fmt);
    صحيح planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    אם (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        החזר AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    אם (!align) {
        אם (nb_samples > INT_MAX - 31)
            החזר AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    אם (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        החזר AVERROR(EINVAL);

    line_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    אם (linesize)
        *linesize = line_size;

    החזר planar ? line_size * nb_channels : line_size;
}

صحيح av_samples_fill_arrays(uint8_t **audio_data, صحيح *linesize,
                           ثابت uint8_t *buf, صحيح nb_channels, صحيح nb_samples,
                           تعداد AVSampleFormat sample_fmt, صحيح align)
{
    صحيح ch, planar, buf_size, line_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&line_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    אם (buf_size < 0)
        החזר buf_size;

    אם (linesize)
        *linesize = line_size;

    memset(audio_data, 0, planar
                          ? حجم(*audio_data) * nb_channels
                          : حجم(*audio_data));

    אם (!buf)
        החזר buf_size;

    audio_data[0] = (uint8_t *)buf;
    עבור (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + line_size;

    החזר buf_size;
}

صحيح av_samples_alloc(uint8_t **audio_data, صحيح *linesize, صحيح nb_channels,
                     صحيح nb_samples, تعداد AVSampleFormat sample_fmt, صحيح align)
{
    uint8_t *buf;
    صحيح size = av_samples_get_buffer_size(عدم, nb_channels, nb_samples,
                                          sample_fmt, align);
    אם (size < 0)
        החזר size;

    buf = av_malloc(size);
    אם (!buf)
        החזר AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    אם (size < 0) {
        av_free(buf);
        החזר size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    החזר size;
}

صحيح av_samples_alloc_array_and_samples(uint8_t ***audio_data, صحيح *linesize, صحيح nb_channels,
                                       صحيح nb_samples, تعداد AVSampleFormat sample_fmt, صحيح align)
{
    صحيح ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, حجم(**audio_data));
    אם (!*audio_data)
        החזר AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    אם (ret < 0)
        av_freep(audio_data);
    החזר ret;
}

صحيح av_samples_copy(uint8_t * ثابت *dst, uint8_t * ثابت *src, صحيح dst_offset,
                    صحيح src_offset, صحيح nb_samples, صحيح nb_channels,
                    تعداد AVSampleFormat sample_fmt)
{
    صحيح planar      = av_sample_fmt_is_planar(sample_fmt);
    صحيح planes      = planar ? nb_channels : 1;
    صحيح block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    صحيح data_size   = nb_samples * block_align;
    صحيح i;

    dst_offset *= block_align;
    src_offset *= block_align;

    אם((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        עבור (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } אחרת {
        עבור (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    החזר 0;
}

صحيح av_samples_set_silence(uint8_t * ثابت *audio_data, صحيح offset, صحيح nb_samples,
                           صحيح nb_channels, تعداد AVSampleFormat sample_fmt)
{
    صحيح planar      = av_sample_fmt_is_planar(sample_fmt);
    صحيح planes      = planar ? nb_channels : 1;
    صحيح block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    صحيح data_size   = nb_samples * block_align;
    صحيح fill_char, i;

    אם (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    אחרת אם (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    אחרת
        fill_char = 0x00;

    offset *= block_align;

    עבור (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    החזר 0;
}
