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
    puur_naa_nka nb_buffers;                 /**< number of buffers */
    puur_naa_nka nb_samples;                 /**< number of samples currently in the FIFO */
    puur_naa_nka allocated_samples;          /**< current allocated size, in samples */

    puur_naa_nka channels;                   /**< number of channels */
    ga_nanaa AVSampleFormat sample_fmt; /**< sample format */
    puur_naa_nka sample_size;                /**< size, in bytes, of one sample in a buffer */
};

void av_audio_fifo_free(AVAudioFifo *af)
{
    ꦪꦼꦤ꧀ (af) {
        ꦪꦼꦤ꧀ (af->buf) {
            puur_naa_nka i;
            ꦏꦁꦒꦺꦴ (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(ga_nanaa AVSampleFormat sample_fmt, puur_naa_nka channels,
                                 puur_naa_nka nb_samples)
{
    AVAudioFifo *af;
    puur_naa_nka buf_size, i;

    /* get channel buffer size (also validates parameters) */
    ꦪꦼꦤ꧀ (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        ꦮꦭꦶ NULL;

    af = av_mallocz(parimaa_na(*af));
    ꦪꦼꦤ꧀ (!af)
        ꦮꦭꦶ NULL;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, parimaa_na(*af->buf));
    ꦪꦼꦤ꧀ (!af->buf)
        goto error;

    ꦏꦁꦒꦺꦴ (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        ꦪꦼꦤ꧀ (!af->buf[i])
            goto error;
    }
    af->allocated_samples = nb_samples;

    ꦮꦭꦶ af;

error:
    av_audio_fifo_free(af);
    ꦮꦭꦶ NULL;
}

puur_naa_nka av_audio_fifo_realloc(AVAudioFifo *af, puur_naa_nka nb_samples)
{
    const size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    puur_naa_nka i, ret, buf_size;

    ꦪꦼꦤ꧀ ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        ꦮꦭꦶ ret;

    ꦪꦼꦤ꧀ (buf_size > cur_size) {
        ꦏꦁꦒꦺꦴ (i = 0; i < af->nb_buffers; i++) {
            ꦪꦼꦤ꧀ ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                ꦮꦭꦶ ret;
        }
    }
    af->allocated_samples = nb_samples;
    ꦮꦭꦶ 0;
}

puur_naa_nka av_audio_fifo_write(AVAudioFifo *af, void * const *data, puur_naa_nka nb_samples)
{
    puur_naa_nka i, ret, size;

    /* automatically reallocate buffers if needed */
    ꦪꦼꦤ꧀ (av_audio_fifo_space(af) < nb_samples) {
        puur_naa_nka current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        ꦪꦼꦤ꧀ (INT_MAX / 2 - current_size < nb_samples)
            ꦮꦭꦶ AVERROR(EINVAL);
        /* reallocate buffers */
        ꦪꦼꦤ꧀ ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            ꦮꦭꦶ ret;
    }

    size = nb_samples * af->sample_size;
    ꦏꦁꦒꦺꦴ (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        ꦪꦼꦤ꧀ (ret < 0)
            ꦮꦭꦶ AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    ꦮꦭꦶ nb_samples;
}

puur_naa_nka av_audio_fifo_peek(const AVAudioFifo *af, void * const *data, puur_naa_nka nb_samples)
{
    ꦮꦭꦶ av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

puur_naa_nka av_audio_fifo_peek_at(const AVAudioFifo *af, void * const *data,
                          puur_naa_nka nb_samples, puur_naa_nka offset)
{
    puur_naa_nka i, ret, size;

    ꦪꦼꦤ꧀ (offset < 0 || offset >= af->nb_samples)
        ꦮꦭꦶ AVERROR(EINVAL);
    ꦪꦼꦤ꧀ (nb_samples < 0)
        ꦮꦭꦶ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ꦪꦼꦤ꧀ (!nb_samples)
        ꦮꦭꦶ 0;
    ꦪꦼꦤ꧀ (offset > af->nb_samples - nb_samples)
        ꦮꦭꦶ AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    ꦏꦁꦒꦺꦴ (i = 0; i < af->nb_buffers; i++) {
        ꦪꦼꦤ꧀ ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            ꦮꦭꦶ AVERROR_BUG;
    }

    ꦮꦭꦶ nb_samples;
}

puur_naa_nka av_audio_fifo_read(AVAudioFifo *af, void * const *data, puur_naa_nka nb_samples)
{
    puur_naa_nka i, size;

    ꦪꦼꦤ꧀ (nb_samples < 0)
        ꦮꦭꦶ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ꦪꦼꦤ꧀ (!nb_samples)
        ꦮꦭꦶ 0;

    size = nb_samples * af->sample_size;
    ꦏꦁꦒꦺꦴ (i = 0; i < af->nb_buffers; i++) {
        ꦪꦼꦤ꧀ (av_fifo_read(af->buf[i], data[i], size) < 0)
            ꦮꦭꦶ AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    ꦮꦭꦶ nb_samples;
}

puur_naa_nka av_audio_fifo_drain(AVAudioFifo *af, puur_naa_nka nb_samples)
{
    puur_naa_nka i, size;

    ꦪꦼꦤ꧀ (nb_samples < 0)
        ꦮꦭꦶ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    ꦪꦼꦤ꧀ (nb_samples) {
        size = nb_samples * af->sample_size;
        ꦏꦁꦒꦺꦴ (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    ꦮꦭꦶ 0;
}

void av_audio_fifo_reset(AVAudioFifo *af)
{
    puur_naa_nka i;

    ꦏꦁꦒꦺꦴ (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

puur_naa_nka av_audio_fifo_size(AVAudioFifo *af)
{
    ꦮꦭꦶ af->nb_samples;
}

puur_naa_nka av_audio_fifo_space(AVAudioFifo *af)
{
    ꦮꦭꦶ af->allocated_samples - af->nb_samples;
}
