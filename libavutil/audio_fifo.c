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
    정수 nb_buffers;                 /**< number of buffers */
    정수 nb_samples;                 /**< number of samples currently in the FIFO */
    정수 allocated_samples;          /**< current allocated size, in samples */

    정수 channels;                   /**< number of channels */
    enum AVSampleFormat sample_fmt; /**< sample format */
    정수 sample_size;                /**< size, in bytes, of one sample in a buffer */
};

void av_audio_fifo_free(AVAudioFifo *af)
{
    만약 (af) {
        만약 (af->buf) {
            정수 i;
            위해 (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(enum AVSampleFormat sample_fmt, 정수 channels,
                                 정수 nb_samples)
{
    AVAudioFifo *af;
    정수 buf_size, i;

    /* get channel buffer size (also validates parameters) */
    만약 (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        반환 NULL;

    af = av_mallocz(sizeof(*af));
    만약 (!af)
        반환 NULL;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, sizeof(*af->buf));
    만약 (!af->buf)
        goto error;

    위해 (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        만약 (!af->buf[i])
            goto error;
    }
    af->allocated_samples = nb_samples;

    반환 af;

error:
    av_audio_fifo_free(af);
    반환 NULL;
}

정수 av_audio_fifo_realloc(AVAudioFifo *af, 정수 nb_samples)
{
    const size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    정수 i, ret, buf_size;

    만약 ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        반환 ret;

    만약 (buf_size > cur_size) {
        위해 (i = 0; i < af->nb_buffers; i++) {
            만약 ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                반환 ret;
        }
    }
    af->allocated_samples = nb_samples;
    반환 0;
}

정수 av_audio_fifo_write(AVAudioFifo *af, void * const *data, 정수 nb_samples)
{
    정수 i, ret, size;

    /* automatically reallocate buffers if needed */
    만약 (av_audio_fifo_space(af) < nb_samples) {
        정수 current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        만약 (INT_MAX / 2 - current_size < nb_samples)
            반환 AVERROR(EINVAL);
        /* reallocate buffers */
        만약 ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            반환 ret;
    }

    size = nb_samples * af->sample_size;
    위해 (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        만약 (ret < 0)
            반환 AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    반환 nb_samples;
}

정수 av_audio_fifo_peek(const AVAudioFifo *af, void * const *data, 정수 nb_samples)
{
    반환 av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

정수 av_audio_fifo_peek_at(const AVAudioFifo *af, void * const *data,
                          정수 nb_samples, 정수 offset)
{
    정수 i, ret, size;

    만약 (offset < 0 || offset >= af->nb_samples)
        반환 AVERROR(EINVAL);
    만약 (nb_samples < 0)
        반환 AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    만약 (!nb_samples)
        반환 0;
    만약 (offset > af->nb_samples - nb_samples)
        반환 AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    위해 (i = 0; i < af->nb_buffers; i++) {
        만약 ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            반환 AVERROR_BUG;
    }

    반환 nb_samples;
}

정수 av_audio_fifo_read(AVAudioFifo *af, void * const *data, 정수 nb_samples)
{
    정수 i, size;

    만약 (nb_samples < 0)
        반환 AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    만약 (!nb_samples)
        반환 0;

    size = nb_samples * af->sample_size;
    위해 (i = 0; i < af->nb_buffers; i++) {
        만약 (av_fifo_read(af->buf[i], data[i], size) < 0)
            반환 AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    반환 nb_samples;
}

정수 av_audio_fifo_drain(AVAudioFifo *af, 정수 nb_samples)
{
    정수 i, size;

    만약 (nb_samples < 0)
        반환 AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    만약 (nb_samples) {
        size = nb_samples * af->sample_size;
        위해 (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    반환 0;
}

void av_audio_fifo_reset(AVAudioFifo *af)
{
    정수 i;

    위해 (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

정수 av_audio_fifo_size(AVAudioFifo *af)
{
    반환 af->nb_samples;
}

정수 av_audio_fifo_space(AVAudioFifo *af)
{
    반환 af->allocated_samples - af->nb_samples;
}
