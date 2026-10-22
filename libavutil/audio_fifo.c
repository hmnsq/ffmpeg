/*
 * Audio FIFO
 * Copyright (c) 2012 Justin Ruggles <justin.ruggles@gmail.com>
 *
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

/**
 * @file
 * Audio FIFO
 */

#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <stddef.h>

#অন্তর্ভাব "audio_fifo.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "fifo.h"
#অন্তর্ভাব "macros.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "samplefmt.h"

কাঠামো AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    পূর্ণসংখ্যা nb_buffers;                 /**< number of buffers */
    পূর্ণসংখ্যা nb_samples;                 /**< number of samples currently in the FIFO */
    পূর্ণসংখ্যা allocated_samples;          /**< current allocated size, in samples */

    পূর্ণসংখ্যা channels;                   /**< number of channels */
    গণনা AVSampleFormat sample_fmt; /**< sample format */
    পূর্ণসংখ্যা sample_আকার;                /**< size, in bytes, of one sample in a buffer */
};

শূন্য av_audio_fifo_free(AVAudioFifo *af)
{
    যদি (af) {
        যদি (af->buf) {
            পূর্ণসংখ্যা i;
            জন্য (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(গণনা AVSampleFormat sample_fmt, পূর্ণসংখ্যা channels,
                                 পূর্ণসংখ্যা nb_samples)
{
    AVAudioFifo *af;
    পূর্ণসংখ্যা buf_আকার, i;

    /* get channel buffer size (also validates parameters) */
    যদি (av_samples_get_বাফার_আকার(&buf_আকার, channels, nb_samples, sample_fmt, 1) < 0)
        ফেরত ফাঁকা;

    af = av_mallocz(আকার(*af));
    যদি (!af)
        ফেরত ফাঁকা;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_আকার = buf_আকার / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, আকার(*af->buf));
    যদি (!af->buf)
        যাও error;

    জন্য (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_আকার, 1, 0);
        যদি (!af->buf[i])
            যাও error;
    }
    af->allocated_samples = nb_samples;

    ফেরত af;

error:
    av_audio_fifo_free(af);
    ফেরত ফাঁকা;
}

পূর্ণসংখ্যা av_audio_fifo_realloc(AVAudioFifo *af, পূর্ণসংখ্যা nb_samples)
{
    ধ্রুবক size_t cur_আকার = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    পূর্ণসংখ্যা i, ret, buf_আকার;

    যদি ((ret = av_samples_get_বাফার_আকার(&buf_আকার, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        ফেরত ret;

    যদি (buf_আকার > cur_আকার) {
        জন্য (i = 0; i < af->nb_buffers; i++) {
            যদি ((ret = av_fifo_grow2(af->buf[i], buf_আকার - cur_আকার)) < 0)
                ফেরত ret;
        }
    }
    af->allocated_samples = nb_samples;
    ফেরত 0;
}

পূর্ণসংখ্যা av_audio_fifo_write(AVAudioFifo *af, শূন্য * ধ্রুবক *তথ্য, পূর্ণসংখ্যা nb_samples)
{
    পূর্ণসংখ্যা i, ret, আকার_2;

    /* automatically reallocate buffers if needed */
    যদি (av_audio_fifo_space(af) < nb_samples) {
        পূর্ণসংখ্যা current_আকার = av_audio_fifo_আকার(af);
        /* check for integer overflow in new size calculation */
        যদি (INT_MAX / 2 - current_আকার < nb_samples)
            ফেরত AVERROR(EINVAL);
        /* reallocate buffers */
        যদি ((ret = av_audio_fifo_realloc(af, 2 * (current_আকার + nb_samples))) < 0)
            ফেরত ret;
    }

    আকার_2 = nb_samples * af->sample_আকার;
    জন্য (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], তথ্য[i], আকার_2);
        যদি (ret < 0)
            ফেরত AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    ফেরত nb_samples;
}

পূর্ণসংখ্যা av_audio_fifo_peek(ধ্রুবক AVAudioFifo *af, শূন্য * ধ্রুবক *তথ্য, পূর্ণসংখ্যা nb_samples)
{
    ফেরত av_audio_fifo_peek_at(af, তথ্য, nb_samples, 0);
}

পূর্ণসংখ্যা av_audio_fifo_peek_at(ধ্রুবক AVAudioFifo *af, শূন্য * ধ্রুবক *তথ্য,
                          পূর্ণসংখ্যা nb_samples, পূর্ণসংখ্যা offset)
{
    পূর্ণসংখ্যা i, ret, আকার_2;

    যদি (offset < 0 || offset >= af->nb_samples)
        ফেরত AVERROR(EINVAL);
    যদি (nb_samples < 0)
        ফেরত AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    যদি (!nb_samples)
        ফেরত 0;
    যদি (offset > af->nb_samples - nb_samples)
        ফেরত AVERROR(EINVAL);

    offset *= af->sample_আকার;
    আকার_2 = nb_samples * af->sample_আকার;
    জন্য (i = 0; i < af->nb_buffers; i++) {
        যদি ((ret = av_fifo_peek(af->buf[i], তথ্য[i], আকার_2, offset)) < 0)
            ফেরত AVERROR_BUG;
    }

    ফেরত nb_samples;
}

পূর্ণসংখ্যা av_audio_fifo_read(AVAudioFifo *af, শূন্য * ধ্রুবক *তথ্য, পূর্ণসংখ্যা nb_samples)
{
    পূর্ণসংখ্যা i, আকার_2;

    যদি (nb_samples < 0)
        ফেরত AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    যদি (!nb_samples)
        ফেরত 0;

    আকার_2 = nb_samples * af->sample_আকার;
    জন্য (i = 0; i < af->nb_buffers; i++) {
        যদি (av_fifo_read(af->buf[i], তথ্য[i], আকার_2) < 0)
            ফেরত AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    ফেরত nb_samples;
}

পূর্ণসংখ্যা av_audio_fifo_drain(AVAudioFifo *af, পূর্ণসংখ্যা nb_samples)
{
    পূর্ণসংখ্যা i, আকার_2;

    যদি (nb_samples < 0)
        ফেরত AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    যদি (nb_samples) {
        আকার_2 = nb_samples * af->sample_আকার;
        জন্য (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], আকার_2);
        af->nb_samples -= nb_samples;
    }
    ফেরত 0;
}

শূন্য av_audio_fifo_reset(AVAudioFifo *af)
{
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

পূর্ণসংখ্যা av_audio_fifo_আকার(AVAudioFifo *af)
{
    ফেরত af->nb_samples;
}

পূর্ণসংখ্যা av_audio_fifo_space(AVAudioFifo *af)
{
    ফেরত af->allocated_samples - af->nb_samples;
}
