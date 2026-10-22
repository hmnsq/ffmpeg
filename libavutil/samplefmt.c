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

প্রকারনির্দেশ সংরচনা SampleFmtInfo {
    বর্ণ name[8];
    পূর্ণাঙ্ক bits;
    পূর্ণাঙ্ক planar;
    গণনা AVSampleFormat altform; ///< planar<->packed alternative form
} SampleFmtInfo;

/** this table gives more information about formats */
স্থির ধ্রুব SampleFmtInfo sample_fmt_info[AV_SAMPLE_FMT_NB] = {
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

ধ্রুব বর্ণ *av_get_sample_fmt_name(গণনা AVSampleFormat sample_fmt)
{
    যদি (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        প্রত্যাগম রিক্ত;
    প্রত্যাগম sample_fmt_info[sample_fmt].name;
}

গণনা AVSampleFormat av_get_sample_fmt(ধ্রুব বর্ণ *name)
{
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; i < AV_SAMPLE_FMT_NB; i++)
        যদি (!strcmp(sample_fmt_info[i].name, name))
            প্রত্যাগম i;
    প্রত্যাগম AV_SAMPLE_FMT_NONE;
}

গণনা AVSampleFormat av_get_alt_sample_fmt(গণনা AVSampleFormat sample_fmt, পূর্ণাঙ্ক planar)
{
    যদি (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        প্রত্যাগম AV_SAMPLE_FMT_NONE;
    যদি (sample_fmt_info[sample_fmt].planar == planar)
        প্রত্যাগম sample_fmt;
    প্রত্যাগম sample_fmt_info[sample_fmt].altform;
}

গণনা AVSampleFormat av_get_packed_sample_fmt(গণনা AVSampleFormat sample_fmt)
{
    যদি (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        প্রত্যাগম AV_SAMPLE_FMT_NONE;
    যদি (sample_fmt_info[sample_fmt].planar)
        প্রত্যাগম sample_fmt_info[sample_fmt].altform;
    প্রত্যাগম sample_fmt;
}

গণনা AVSampleFormat av_get_planar_sample_fmt(গণনা AVSampleFormat sample_fmt)
{
    যদি (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
        প্রত্যাগম AV_SAMPLE_FMT_NONE;
    যদি (sample_fmt_info[sample_fmt].planar)
        প্রত্যাগম sample_fmt;
    প্রত্যাগম sample_fmt_info[sample_fmt].altform;
}

বর্ণ *av_get_sample_fmt_string (বর্ণ *buf, পূর্ণাঙ্ক buf_size, গণনা AVSampleFormat sample_fmt)
{
    /* print header */
    যদি (sample_fmt < 0)
        snprintf(buf, buf_size, "name  " " depth");
    অন্যথা যদি (sample_fmt < AV_SAMPLE_FMT_NB) {
        SampleFmtInfo info = sample_fmt_info[sample_fmt];
        snprintf (buf, buf_size, "%-6s" "   %2d ", info.name, info.bits);
    }

    প্রত্যাগম buf;
}

পূর্ণাঙ্ক av_get_bytes_per_sample(গণনা AVSampleFormat sample_fmt)
{
     প্রত্যাগম sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}

পূর্ণাঙ্ক av_sample_fmt_is_planar(গণনা AVSampleFormat sample_fmt)
{
     যদি (sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB)
         প্রত্যাগম 0;
     প্রত্যাগম sample_fmt_info[sample_fmt].planar;
}

পূর্ণাঙ্ক av_samples_get_buffer_size(পূর্ণাঙ্ক *linesize, পূর্ণাঙ্ক nb_channels, পূর্ণাঙ্ক nb_samples,
                               গণনা AVSampleFormat sample_fmt, পূর্ণাঙ্ক align)
{
    পূর্ণাঙ্ক সারি_size;
    পূর্ণাঙ্ক sample_size = av_get_bytes_per_sample(sample_fmt);
    পূর্ণাঙ্ক planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    যদি (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        প্রত্যাগম AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    যদি (!align) {
        যদি (nb_samples > INT_MAX - 31)
            প্রত্যাগম AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    যদি (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        প্রত্যাগম AVERROR(EINVAL);

    সারি_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    যদি (linesize)
        *linesize = সারি_size;

    প্রত্যাগম planar ? সারি_size * nb_channels : সারি_size;
}

পূর্ণাঙ্ক av_samples_fill_arrays(uint8_t **audio_data, পূর্ণাঙ্ক *linesize,
                           ধ্রুব uint8_t *buf, পূর্ণাঙ্ক nb_channels, পূর্ণাঙ্ক nb_samples,
                           গণনা AVSampleFormat sample_fmt, পূর্ণাঙ্ক align)
{
    পূর্ণাঙ্ক ch, planar, buf_size, সারি_size;

    planar   = av_sample_fmt_is_planar(sample_fmt);
    buf_size = av_samples_get_buffer_size(&সারি_size, nb_channels, nb_samples,
                                          sample_fmt, align);
    যদি (buf_size < 0)
        প্রত্যাগম buf_size;

    যদি (linesize)
        *linesize = সারি_size;

    memset(audio_data, 0, planar
                          ? পরিমাণ(*audio_data) * nb_channels
                          : পরিমাণ(*audio_data));

    যদি (!buf)
        প্রত্যাগম buf_size;

    audio_data[0] = (uint8_t *)buf;
    প্রতি (ch = 1; planar && ch < nb_channels; ch++)
        audio_data[ch] = audio_data[ch-1] + সারি_size;

    প্রত্যাগম buf_size;
}

পূর্ণাঙ্ক av_samples_alloc(uint8_t **audio_data, পূর্ণাঙ্ক *linesize, পূর্ণাঙ্ক nb_channels,
                     পূর্ণাঙ্ক nb_samples, গণনা AVSampleFormat sample_fmt, পূর্ণাঙ্ক align)
{
    uint8_t *buf;
    পূর্ণাঙ্ক size = av_samples_get_buffer_size(রিক্ত, nb_channels, nb_samples,
                                          sample_fmt, align);
    যদি (size < 0)
        প্রত্যাগম size;

    buf = av_malloc(size);
    যদি (!buf)
        প্রত্যাগম AVERROR(ENOMEM);

    size = av_samples_fill_arrays(audio_data, linesize, buf, nb_channels,
                                  nb_samples, sample_fmt, align);
    যদি (size < 0) {
        av_free(buf);
        প্রত্যাগম size;
    }

    av_samples_set_silence(audio_data, 0, nb_samples, nb_channels, sample_fmt);

    প্রত্যাগম size;
}

পূর্ণাঙ্ক av_samples_alloc_array_and_samples(uint8_t ***audio_data, পূর্ণাঙ্ক *linesize, পূর্ণাঙ্ক nb_channels,
                                       পূর্ণাঙ্ক nb_samples, গণনা AVSampleFormat sample_fmt, পূর্ণাঙ্ক align)
{
    পূর্ণাঙ্ক ret, nb_planes = av_sample_fmt_is_planar(sample_fmt) ? nb_channels : 1;

    *audio_data = av_calloc(nb_planes, পরিমাণ(**audio_data));
    যদি (!*audio_data)
        প্রত্যাগম AVERROR(ENOMEM);
    ret = av_samples_alloc(*audio_data, linesize, nb_channels,
                           nb_samples, sample_fmt, align);
    যদি (ret < 0)
        av_freep(audio_data);
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_samples_copy(uint8_t * ধ্রুব *dst, uint8_t * ধ্রুব *src, পূর্ণাঙ্ক dst_offset,
                    পূর্ণাঙ্ক src_offset, পূর্ণাঙ্ক nb_samples, পূর্ণাঙ্ক nb_channels,
                    গণনা AVSampleFormat sample_fmt)
{
    পূর্ণাঙ্ক planar      = av_sample_fmt_is_planar(sample_fmt);
    পূর্ণাঙ্ক planes      = planar ? nb_channels : 1;
    পূর্ণাঙ্ক block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    পূর্ণাঙ্ক data_size   = nb_samples * block_align;
    পূর্ণাঙ্ক i;

    dst_offset *= block_align;
    src_offset *= block_align;

    যদি((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        প্রতি (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } অন্যথা {
        প্রতি (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_samples_set_silence(uint8_t * ধ্রুব *audio_data, পূর্ণাঙ্ক offset, পূর্ণাঙ্ক nb_samples,
                           পূর্ণাঙ্ক nb_channels, গণনা AVSampleFormat sample_fmt)
{
    পূর্ণাঙ্ক planar      = av_sample_fmt_is_planar(sample_fmt);
    পূর্ণাঙ্ক planes      = planar ? nb_channels : 1;
    পূর্ণাঙ্ক block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    পূর্ণাঙ্ক data_size   = nb_samples * block_align;
    পূর্ণাঙ্ক fill_char, i;

    যদি (sample_fmt == AV_SAMPLE_FMT_U8 || sample_fmt == AV_SAMPLE_FMT_U8P)
        fill_char = 0x80;
    অন্যথা যদি (sample_fmt == AV_SAMPLE_FMT_DSD)
        fill_char = 0x69; // only ultrasonic tones, filtered out on playback
    অন্যথা
        fill_char = 0x00;

    offset *= block_align;

    প্রতি (i = 0; i < planes; i++)
        memset(audio_data[i] + offset, fill_char, data_size);

    প্রত্যাগম 0;
}
