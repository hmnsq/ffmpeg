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

#include <limits.h>
#include <stddef.h>

#include "audio_fifo.h"
#include "error.h"
#include "fifo.h"
#include "macros.h"
#include "mem.h"
#include "samplefmt.h"

struct AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    số_nguyên nb_buffers;                 /**< number of buffers */
    số_nguyên nb_samples;                 /**< number of samples currently in the FIFO */
    số_nguyên allocated_samples;          /**< current allocated size, in samples */

    số_nguyên channels;                   /**< number of channels */
    enum AVSampleFormat sample_fmt; /**< sample format */
    số_nguyên sample_size;                /**< size, in bytes, of one sample in a buffer */
};

void av_audio_fifo_free(AVAudioFifo *af)
{
    nếu (af) {
        nếu (af->buf) {
            số_nguyên i;
            cho (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(enum AVSampleFormat sample_fmt, số_nguyên channels,
                                 số_nguyên nb_samples)
{
    AVAudioFifo *af;
    số_nguyên buf_size, i;

    /* get channel buffer size (also validates parameters) */
    nếu (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        trả_về NULL;

    af = av_mallocz(sizeof(*af));
    nếu (!af)
        trả_về NULL;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, sizeof(*af->buf));
    nếu (!af->buf)
        goto error;

    cho (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        nếu (!af->buf[i])
            goto error;
    }
    af->allocated_samples = nb_samples;

    trả_về af;

error:
    av_audio_fifo_free(af);
    trả_về NULL;
}

số_nguyên av_audio_fifo_realloc(AVAudioFifo *af, số_nguyên nb_samples)
{
    const size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    số_nguyên i, ret, buf_size;

    nếu ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        trả_về ret;

    nếu (buf_size > cur_size) {
        cho (i = 0; i < af->nb_buffers; i++) {
            nếu ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                trả_về ret;
        }
    }
    af->allocated_samples = nb_samples;
    trả_về 0;
}

số_nguyên av_audio_fifo_write(AVAudioFifo *af, void * const *data, số_nguyên nb_samples)
{
    số_nguyên i, ret, size;

    /* automatically reallocate buffers if needed */
    nếu (av_audio_fifo_space(af) < nb_samples) {
        số_nguyên current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        nếu (INT_MAX / 2 - current_size < nb_samples)
            trả_về AVERROR(EINVAL);
        /* reallocate buffers */
        nếu ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            trả_về ret;
    }

    size = nb_samples * af->sample_size;
    cho (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        nếu (ret < 0)
            trả_về AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    trả_về nb_samples;
}

số_nguyên av_audio_fifo_peek(const AVAudioFifo *af, void * const *data, số_nguyên nb_samples)
{
    trả_về av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

số_nguyên av_audio_fifo_peek_at(const AVAudioFifo *af, void * const *data,
                          số_nguyên nb_samples, số_nguyên offset)
{
    số_nguyên i, ret, size;

    nếu (offset < 0 || offset >= af->nb_samples)
        trả_về AVERROR(EINVAL);
    nếu (nb_samples < 0)
        trả_về AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    nếu (!nb_samples)
        trả_về 0;
    nếu (offset > af->nb_samples - nb_samples)
        trả_về AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    cho (i = 0; i < af->nb_buffers; i++) {
        nếu ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            trả_về AVERROR_BUG;
    }

    trả_về nb_samples;
}

số_nguyên av_audio_fifo_read(AVAudioFifo *af, void * const *data, số_nguyên nb_samples)
{
    số_nguyên i, size;

    nếu (nb_samples < 0)
        trả_về AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    nếu (!nb_samples)
        trả_về 0;

    size = nb_samples * af->sample_size;
    cho (i = 0; i < af->nb_buffers; i++) {
        nếu (av_fifo_read(af->buf[i], data[i], size) < 0)
            trả_về AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    trả_về nb_samples;
}

số_nguyên av_audio_fifo_drain(AVAudioFifo *af, số_nguyên nb_samples)
{
    số_nguyên i, size;

    nếu (nb_samples < 0)
        trả_về AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    nếu (nb_samples) {
        size = nb_samples * af->sample_size;
        cho (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    trả_về 0;
}

void av_audio_fifo_reset(AVAudioFifo *af)
{
    số_nguyên i;

    cho (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

số_nguyên av_audio_fifo_size(AVAudioFifo *af)
{
    trả_về af->nb_samples;
}

số_nguyên av_audio_fifo_space(AVAudioFifo *af)
{
    trả_về af->allocated_samples - af->nb_samples;
}
