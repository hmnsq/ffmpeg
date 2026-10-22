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

sa_nracanaa AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    ចំនួនគត់ nb_buffers;                 /**< number of buffers */
    ចំនួនគត់ nb_samples;                 /**< number of samples currently in the FIFO */
    ចំនួនគត់ allocated_samples;          /**< current allocated size, in samples */

    ចំនួនគត់ channels;                   /**< number of channels */
    ga_nanaa AVSampleFormat sample_fmt; /**< sample format */
    ចំនួនគត់ sample_size;                /**< size, in bytes, of one sample in a buffer */
};

void av_audio_fifo_free(AVAudioFifo *af)
{
    ប្រសិនបើ (af) {
        ប្រសិនបើ (af->buf) {
            ចំនួនគត់ i;
            សម្រាប់ (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(ga_nanaa AVSampleFormat sample_fmt, ចំនួនគត់ channels,
                                 ចំនួនគត់ nb_samples)
{
    AVAudioFifo *af;
    ចំនួនគត់ buf_size, i;

    /* get channel buffer size (also validates parameters) */
    ប្រសិនបើ (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        ត្រឡប់ NULL;

    af = av_mallocz(parimaa_na(*af));
    ប្រសិនបើ (!af)
        ត្រឡប់ NULL;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, parimaa_na(*af->buf));
    ប្រសិនបើ (!af->buf)
        goto error;

    សម្រាប់ (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        ប្រសិនបើ (!af->buf[i])
            goto error;
    }
    af->allocated_samples = nb_samples;

    ត្រឡប់ af;

error:
    av_audio_fifo_free(af);
    ត្រឡប់ NULL;
}

ចំនួនគត់ av_audio_fifo_realloc(AVAudioFifo *af, ចំនួនគត់ nb_samples)
{
    const size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    ចំនួនគត់ i, ret, buf_size;

    ប្រសិនបើ ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        ត្រឡប់ ret;

    ប្រសិនបើ (buf_size > cur_size) {
        សម្រាប់ (i = 0; i < af->nb_buffers; i++) {
            ប្រសិនបើ ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                ត្រឡប់ ret;
        }
    }
    af->allocated_samples = nb_samples;
    ត្រឡប់ 0;
}

ចំនួនគត់ av_audio_fifo_write(AVAudioFifo *af, void * const *data, ចំនួនគត់ nb_samples)
{
    ចំនួនគត់ i, ret, size;

    /* automatically reallocate buffers if needed */
    ប្រសិនបើ (av_audio_fifo_space(af) < nb_samples) {
        ចំនួនគត់ current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        ប្រសិនបើ (INT_MAX / 2 - current_size < nb_samples)
            ត្រឡប់ AVERROR(EINVAL);
        /* reallocate buffers */
        ប្រសិនបើ ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            ត្រឡប់ ret;
    }

    size = nb_samples * af->sample_size;
    សម្រាប់ (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        ប្រសិនបើ (ret < 0)
            ត្រឡប់ AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    ត្រឡប់ nb_samples;
}

ចំនួនគត់ av_audio_fifo_peek(const AVAudioFifo *af, void * const *data, ចំនួនគត់ nb_samples)
{
    ត្រឡប់ av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

ចំនួនគត់ av_audio_fifo_peek_at(const AVAudioFifo *af, void * const *data,
                          ចំនួនគត់ nb_samples, ចំនួនគត់ offset)
{
    ចំនួនគត់ i, ret, size;

    ប្រសិនបើ (offset < 0 || offset >= af->nb_samples)
        ត្រឡប់ AVERROR(EINVAL);
    ប្រសិនបើ (nb_samples < 0)
        ត្រឡប់ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ប្រសិនបើ (!nb_samples)
        ត្រឡប់ 0;
    ប្រសិនបើ (offset > af->nb_samples - nb_samples)
        ត្រឡប់ AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    សម្រាប់ (i = 0; i < af->nb_buffers; i++) {
        ប្រសិនបើ ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            ត្រឡប់ AVERROR_BUG;
    }

    ត្រឡប់ nb_samples;
}

ចំនួនគត់ av_audio_fifo_read(AVAudioFifo *af, void * const *data, ចំនួនគត់ nb_samples)
{
    ចំនួនគត់ i, size;

    ប្រសិនបើ (nb_samples < 0)
        ត្រឡប់ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ប្រសិនបើ (!nb_samples)
        ត្រឡប់ 0;

    size = nb_samples * af->sample_size;
    សម្រាប់ (i = 0; i < af->nb_buffers; i++) {
        ប្រសិនបើ (av_fifo_read(af->buf[i], data[i], size) < 0)
            ត្រឡប់ AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    ត្រឡប់ nb_samples;
}

ចំនួនគត់ av_audio_fifo_drain(AVAudioFifo *af, ចំនួនគត់ nb_samples)
{
    ចំនួនគត់ i, size;

    ប្រសិនបើ (nb_samples < 0)
        ត្រឡប់ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    ប្រសិនបើ (nb_samples) {
        size = nb_samples * af->sample_size;
        សម្រាប់ (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    ត្រឡប់ 0;
}

void av_audio_fifo_reset(AVAudioFifo *af)
{
    ចំនួនគត់ i;

    សម្រាប់ (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

ចំនួនគត់ av_audio_fifo_size(AVAudioFifo *af)
{
    ត្រឡប់ af->nb_samples;
}

ចំនួនគត់ av_audio_fifo_space(AVAudioFifo *af)
{
    ត្រឡប់ af->allocated_samples - af->nb_samples;
}
