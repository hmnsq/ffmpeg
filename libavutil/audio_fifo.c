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
    整数 nb_buffers;                 /**< number of buffers */
    整数 nb_samples;                 /**< number of samples currently in the FIFO */
    整数 allocated_samples;          /**< current allocated size, in samples */

    整数 channels;                   /**< number of channels */
    enum AVSampleFormat sample_fmt; /**< sample format */
    整数 sample_size;                /**< size, in bytes, of one sample in a buffer */
};

void av_audio_fifo_free(AVAudioFifo *af)
{
    如果 (af) {
        如果 (af->buf) {
            整数 i;
            为 (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(enum AVSampleFormat sample_fmt, 整数 channels,
                                 整数 nb_samples)
{
    AVAudioFifo *af;
    整数 buf_size, i;

    /* get channel buffer size (also validates parameters) */
    如果 (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        返回 NULL;

    af = av_mallocz(sizeof(*af));
    如果 (!af)
        返回 NULL;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, sizeof(*af->buf));
    如果 (!af->buf)
        goto error;

    为 (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        如果 (!af->buf[i])
            goto error;
    }
    af->allocated_samples = nb_samples;

    返回 af;

error:
    av_audio_fifo_free(af);
    返回 NULL;
}

整数 av_audio_fifo_realloc(AVAudioFifo *af, 整数 nb_samples)
{
    const size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    整数 i, ret, buf_size;

    如果 ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        返回 ret;

    如果 (buf_size > cur_size) {
        为 (i = 0; i < af->nb_buffers; i++) {
            如果 ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                返回 ret;
        }
    }
    af->allocated_samples = nb_samples;
    返回 0;
}

整数 av_audio_fifo_write(AVAudioFifo *af, void * const *data, 整数 nb_samples)
{
    整数 i, ret, size;

    /* automatically reallocate buffers if needed */
    如果 (av_audio_fifo_space(af) < nb_samples) {
        整数 current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        如果 (INT_MAX / 2 - current_size < nb_samples)
            返回 AVERROR(EINVAL);
        /* reallocate buffers */
        如果 ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            返回 ret;
    }

    size = nb_samples * af->sample_size;
    为 (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        如果 (ret < 0)
            返回 AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    返回 nb_samples;
}

整数 av_audio_fifo_peek(const AVAudioFifo *af, void * const *data, 整数 nb_samples)
{
    返回 av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

整数 av_audio_fifo_peek_at(const AVAudioFifo *af, void * const *data,
                          整数 nb_samples, 整数 offset)
{
    整数 i, ret, size;

    如果 (offset < 0 || offset >= af->nb_samples)
        返回 AVERROR(EINVAL);
    如果 (nb_samples < 0)
        返回 AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    如果 (!nb_samples)
        返回 0;
    如果 (offset > af->nb_samples - nb_samples)
        返回 AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    为 (i = 0; i < af->nb_buffers; i++) {
        如果 ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            返回 AVERROR_BUG;
    }

    返回 nb_samples;
}

整数 av_audio_fifo_read(AVAudioFifo *af, void * const *data, 整数 nb_samples)
{
    整数 i, size;

    如果 (nb_samples < 0)
        返回 AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    如果 (!nb_samples)
        返回 0;

    size = nb_samples * af->sample_size;
    为 (i = 0; i < af->nb_buffers; i++) {
        如果 (av_fifo_read(af->buf[i], data[i], size) < 0)
            返回 AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    返回 nb_samples;
}

整数 av_audio_fifo_drain(AVAudioFifo *af, 整数 nb_samples)
{
    整数 i, size;

    如果 (nb_samples < 0)
        返回 AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    如果 (nb_samples) {
        size = nb_samples * af->sample_size;
        为 (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    返回 0;
}

void av_audio_fifo_reset(AVAudioFifo *af)
{
    整数 i;

    为 (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

整数 av_audio_fifo_size(AVAudioFifo *af)
{
    返回 af->nb_samples;
}

整数 av_audio_fifo_space(AVAudioFifo *af)
{
    返回 af->allocated_samples - af->nb_samples;
}
