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
    целое nb_buffers;                 /**< number of buffers */
    целое nb_samples;                 /**< number of samples currently in the FIFO */
    целое allocated_samples;          /**< current allocated size, in samples */

    целое channels;                   /**< number of channels */
    enum AVSampleFormat sample_fmt; /**< sample format */
    целое sample_size;                /**< size, in bytes, of one sample in a buffer */
};

void av_audio_fifo_free(AVAudioFifo *af)
{
    если (af) {
        если (af->buf) {
            целое i;
            для (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(enum AVSampleFormat sample_fmt, целое channels,
                                 целое nb_samples)
{
    AVAudioFifo *af;
    целое buf_size, i;

    /* get channel buffer size (also validates parameters) */
    если (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        вернуть NULL;

    af = av_mallocz(sizeof(*af));
    если (!af)
        вернуть NULL;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, sizeof(*af->buf));
    если (!af->buf)
        goto error;

    для (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        если (!af->buf[i])
            goto error;
    }
    af->allocated_samples = nb_samples;

    вернуть af;

error:
    av_audio_fifo_free(af);
    вернуть NULL;
}

целое av_audio_fifo_realloc(AVAudioFifo *af, целое nb_samples)
{
    const size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    целое i, ret, buf_size;

    если ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        вернуть ret;

    если (buf_size > cur_size) {
        для (i = 0; i < af->nb_buffers; i++) {
            если ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                вернуть ret;
        }
    }
    af->allocated_samples = nb_samples;
    вернуть 0;
}

целое av_audio_fifo_write(AVAudioFifo *af, void * const *data, целое nb_samples)
{
    целое i, ret, size;

    /* automatically reallocate buffers if needed */
    если (av_audio_fifo_space(af) < nb_samples) {
        целое current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        если (INT_MAX / 2 - current_size < nb_samples)
            вернуть AVERROR(EINVAL);
        /* reallocate buffers */
        если ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            вернуть ret;
    }

    size = nb_samples * af->sample_size;
    для (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        если (ret < 0)
            вернуть AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    вернуть nb_samples;
}

целое av_audio_fifo_peek(const AVAudioFifo *af, void * const *data, целое nb_samples)
{
    вернуть av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

целое av_audio_fifo_peek_at(const AVAudioFifo *af, void * const *data,
                          целое nb_samples, целое offset)
{
    целое i, ret, size;

    если (offset < 0 || offset >= af->nb_samples)
        вернуть AVERROR(EINVAL);
    если (nb_samples < 0)
        вернуть AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    если (!nb_samples)
        вернуть 0;
    если (offset > af->nb_samples - nb_samples)
        вернуть AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    для (i = 0; i < af->nb_buffers; i++) {
        если ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            вернуть AVERROR_BUG;
    }

    вернуть nb_samples;
}

целое av_audio_fifo_read(AVAudioFifo *af, void * const *data, целое nb_samples)
{
    целое i, size;

    если (nb_samples < 0)
        вернуть AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    если (!nb_samples)
        вернуть 0;

    size = nb_samples * af->sample_size;
    для (i = 0; i < af->nb_buffers; i++) {
        если (av_fifo_read(af->buf[i], data[i], size) < 0)
            вернуть AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    вернуть nb_samples;
}

целое av_audio_fifo_drain(AVAudioFifo *af, целое nb_samples)
{
    целое i, size;

    если (nb_samples < 0)
        вернуть AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    если (nb_samples) {
        size = nb_samples * af->sample_size;
        для (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    вернуть 0;
}

void av_audio_fifo_reset(AVAudioFifo *af)
{
    целое i;

    для (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

целое av_audio_fifo_size(AVAudioFifo *af)
{
    вернуть af->nb_samples;
}

целое av_audio_fifo_space(AVAudioFifo *af)
{
    вернуть af->allocated_samples - af->nb_samples;
}
