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
    ཧྲིལ nb_buffers;                 /**< number of buffers */
    ཧྲིལ nb_samples;                 /**< number of samples currently in the FIFO */
    ཧྲིལ allocated_samples;          /**< current allocated size, in samples */

    ཧྲིལ channels;                   /**< number of channels */
    ga_nanaa AVSampleFormat sample_fmt; /**< sample format */
    ཧྲིལ sample_size;                /**< size, in bytes, of one sample in a buffer */
};

void av_audio_fifo_free(AVAudioFifo *af)
{
    གལ་ཏེ (af) {
        གལ་ཏེ (af->buf) {
            ཧྲིལ i;
            ཆེད་དུ (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(ga_nanaa AVSampleFormat sample_fmt, ཧྲིལ channels,
                                 ཧྲིལ nb_samples)
{
    AVAudioFifo *af;
    ཧྲིལ buf_size, i;

    /* get channel buffer size (also validates parameters) */
    གལ་ཏེ (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        ཕྱིར NULL;

    af = av_mallocz(parimaa_na(*af));
    གལ་ཏེ (!af)
        ཕྱིར NULL;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, parimaa_na(*af->buf));
    གལ་ཏེ (!af->buf)
        goto error;

    ཆེད་དུ (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        གལ་ཏེ (!af->buf[i])
            goto error;
    }
    af->allocated_samples = nb_samples;

    ཕྱིར af;

error:
    av_audio_fifo_free(af);
    ཕྱིར NULL;
}

ཧྲིལ av_audio_fifo_realloc(AVAudioFifo *af, ཧྲིལ nb_samples)
{
    const size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    ཧྲིལ i, ret, buf_size;

    གལ་ཏེ ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        ཕྱིར ret;

    གལ་ཏེ (buf_size > cur_size) {
        ཆེད་དུ (i = 0; i < af->nb_buffers; i++) {
            གལ་ཏེ ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                ཕྱིར ret;
        }
    }
    af->allocated_samples = nb_samples;
    ཕྱིར 0;
}

ཧྲིལ av_audio_fifo_write(AVAudioFifo *af, void * const *data, ཧྲིལ nb_samples)
{
    ཧྲིལ i, ret, size;

    /* automatically reallocate buffers if needed */
    གལ་ཏེ (av_audio_fifo_space(af) < nb_samples) {
        ཧྲིལ current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        གལ་ཏེ (INT_MAX / 2 - current_size < nb_samples)
            ཕྱིར AVERROR(EINVAL);
        /* reallocate buffers */
        གལ་ཏེ ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            ཕྱིར ret;
    }

    size = nb_samples * af->sample_size;
    ཆེད་དུ (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        གལ་ཏེ (ret < 0)
            ཕྱིར AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    ཕྱིར nb_samples;
}

ཧྲིལ av_audio_fifo_peek(const AVAudioFifo *af, void * const *data, ཧྲིལ nb_samples)
{
    ཕྱིར av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

ཧྲིལ av_audio_fifo_peek_at(const AVAudioFifo *af, void * const *data,
                          ཧྲིལ nb_samples, ཧྲིལ offset)
{
    ཧྲིལ i, ret, size;

    གལ་ཏེ (offset < 0 || offset >= af->nb_samples)
        ཕྱིར AVERROR(EINVAL);
    གལ་ཏེ (nb_samples < 0)
        ཕྱིར AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    གལ་ཏེ (!nb_samples)
        ཕྱིར 0;
    གལ་ཏེ (offset > af->nb_samples - nb_samples)
        ཕྱིར AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    ཆེད་དུ (i = 0; i < af->nb_buffers; i++) {
        གལ་ཏེ ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            ཕྱིར AVERROR_BUG;
    }

    ཕྱིར nb_samples;
}

ཧྲིལ av_audio_fifo_read(AVAudioFifo *af, void * const *data, ཧྲིལ nb_samples)
{
    ཧྲིལ i, size;

    གལ་ཏེ (nb_samples < 0)
        ཕྱིར AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    གལ་ཏེ (!nb_samples)
        ཕྱིར 0;

    size = nb_samples * af->sample_size;
    ཆེད་དུ (i = 0; i < af->nb_buffers; i++) {
        གལ་ཏེ (av_fifo_read(af->buf[i], data[i], size) < 0)
            ཕྱིར AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    ཕྱིར nb_samples;
}

ཧྲིལ av_audio_fifo_drain(AVAudioFifo *af, ཧྲིལ nb_samples)
{
    ཧྲིལ i, size;

    གལ་ཏེ (nb_samples < 0)
        ཕྱིར AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    གལ་ཏེ (nb_samples) {
        size = nb_samples * af->sample_size;
        ཆེད་དུ (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    ཕྱིར 0;
}

void av_audio_fifo_reset(AVAudioFifo *af)
{
    ཧྲིལ i;

    ཆེད་དུ (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

ཧྲིལ av_audio_fifo_size(AVAudioFifo *af)
{
    ཕྱིར af->nb_samples;
}

ཧྲིལ av_audio_fifo_space(AVAudioFifo *af)
{
    ཕྱིར af->allocated_samples - af->nb_samples;
}
