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

সংরচনা AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    পূর্ণাঙ্ক nb_buffers;                 /**< number of buffers */
    পূর্ণাঙ্ক nb_samples;                 /**< number of samples currently in the FIFO */
    পূর্ণাঙ্ক allocated_samples;          /**< current allocated size, in samples */

    পূর্ণাঙ্ক channels;                   /**< number of channels */
    গণনা AVSampleFormat sample_fmt; /**< sample format */
    পূর্ণাঙ্ক sample_size;                /**< size, in bytes, of one sample in a buffer */
};

শূন্য av_audio_fifo_free(AVAudioFifo *af)
{
    যদি (af) {
        যদি (af->buf) {
            পূর্ণাঙ্ক i;
            প্রতি (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(গণনা AVSampleFormat sample_fmt, পূর্ণাঙ্ক channels,
                                 পূর্ণাঙ্ক nb_samples)
{
    AVAudioFifo *af;
    পূর্ণাঙ্ক buf_size, i;

    /* get channel buffer size (also validates parameters) */
    যদি (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        প্রত্যাগম রিক্ত;

    af = av_mallocz(পরিমাণ(*af));
    যদি (!af)
        প্রত্যাগম রিক্ত;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, পরিমাণ(*af->buf));
    যদি (!af->buf)
        গচ্ছ error;

    প্রতি (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        যদি (!af->buf[i])
            গচ্ছ error;
    }
    af->allocated_samples = nb_samples;

    প্রত্যাগম af;

error:
    av_audio_fifo_free(af);
    প্রত্যাগম রিক্ত;
}

পূর্ণাঙ্ক av_audio_fifo_realloc(AVAudioFifo *af, পূর্ণাঙ্ক nb_samples)
{
    ধ্রুব size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    পূর্ণাঙ্ক i, ret, buf_size;

    যদি ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        প্রত্যাগম ret;

    যদি (buf_size > cur_size) {
        প্রতি (i = 0; i < af->nb_buffers; i++) {
            যদি ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                প্রত্যাগম ret;
        }
    }
    af->allocated_samples = nb_samples;
    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_audio_fifo_write(AVAudioFifo *af, শূন্য * ধ্রুব *data, পূর্ণাঙ্ক nb_samples)
{
    পূর্ণাঙ্ক i, ret, size;

    /* automatically reallocate buffers if needed */
    যদি (av_audio_fifo_space(af) < nb_samples) {
        পূর্ণাঙ্ক current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        যদি (INT_MAX / 2 - current_size < nb_samples)
            প্রত্যাগম AVERROR(EINVAL);
        /* reallocate buffers */
        যদি ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            প্রত্যাগম ret;
    }

    size = nb_samples * af->sample_size;
    প্রতি (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        যদি (ret < 0)
            প্রত্যাগম AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    প্রত্যাগম nb_samples;
}

পূর্ণাঙ্ক av_audio_fifo_peek(ধ্রুব AVAudioFifo *af, শূন্য * ধ্রুব *data, পূর্ণাঙ্ক nb_samples)
{
    প্রত্যাগম av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

পূর্ণাঙ্ক av_audio_fifo_peek_at(ধ্রুব AVAudioFifo *af, শূন্য * ধ্রুব *data,
                          পূর্ণাঙ্ক nb_samples, পূর্ণাঙ্ক offset)
{
    পূর্ণাঙ্ক i, ret, size;

    যদি (offset < 0 || offset >= af->nb_samples)
        প্রত্যাগম AVERROR(EINVAL);
    যদি (nb_samples < 0)
        প্রত্যাগম AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    যদি (!nb_samples)
        প্রত্যাগম 0;
    যদি (offset > af->nb_samples - nb_samples)
        প্রত্যাগম AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    প্রতি (i = 0; i < af->nb_buffers; i++) {
        যদি ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            প্রত্যাগম AVERROR_BUG;
    }

    প্রত্যাগম nb_samples;
}

পূর্ণাঙ্ক av_audio_fifo_read(AVAudioFifo *af, শূন্য * ধ্রুব *data, পূর্ণাঙ্ক nb_samples)
{
    পূর্ণাঙ্ক i, size;

    যদি (nb_samples < 0)
        প্রত্যাগম AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    যদি (!nb_samples)
        প্রত্যাগম 0;

    size = nb_samples * af->sample_size;
    প্রতি (i = 0; i < af->nb_buffers; i++) {
        যদি (av_fifo_read(af->buf[i], data[i], size) < 0)
            প্রত্যাগম AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    প্রত্যাগম nb_samples;
}

পূর্ণাঙ্ক av_audio_fifo_drain(AVAudioFifo *af, পূর্ণাঙ্ক nb_samples)
{
    পূর্ণাঙ্ক i, size;

    যদি (nb_samples < 0)
        প্রত্যাগম AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    যদি (nb_samples) {
        size = nb_samples * af->sample_size;
        প্রতি (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    প্রত্যাগম 0;
}

শূন্য av_audio_fifo_reset(AVAudioFifo *af)
{
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

পূর্ণাঙ্ক av_audio_fifo_size(AVAudioFifo *af)
{
    প্রত্যাগম af->nb_samples;
}

পূর্ণাঙ্ক av_audio_fifo_space(AVAudioFifo *af)
{
    প্রত্যাগম af->allocated_samples - af->nb_samples;
}
