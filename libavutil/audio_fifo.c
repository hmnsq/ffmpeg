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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>

#ಅನ್ತರ್ಭಾವ "audio_fifo.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "fifo.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "samplefmt.h"

ಸಂರಚನಾ AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    ಪೂರ್ಣಾಙ್ಕ nb_buffers;                 /**< number of buffers */
    ಪೂರ್ಣಾಙ್ಕ nb_samples;                 /**< number of samples currently in the FIFO */
    ಪೂರ್ಣಾಙ್ಕ allocated_samples;          /**< current allocated size, in samples */

    ಪೂರ್ಣಾಙ್ಕ channels;                   /**< number of channels */
    ಗಣನಾ AVSampleFormat sample_fmt; /**< sample format */
    ಪೂರ್ಣಾಙ್ಕ sample_size;                /**< size, in bytes, of one sample in a buffer */
};

ಶೂನ್ಯ av_audio_fifo_free(AVAudioFifo *af)
{
    ಯದಿ (af) {
        ಯದಿ (af->buf) {
            ಪೂರ್ಣಾಙ್ಕ i;
            ಪ್ರತಿ (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(ಗಣನಾ AVSampleFormat sample_fmt, ಪೂರ್ಣಾಙ್ಕ channels,
                                 ಪೂರ್ಣಾಙ್ಕ nb_samples)
{
    AVAudioFifo *af;
    ಪೂರ್ಣಾಙ್ಕ buf_size, i;

    /* get channel buffer size (also validates parameters) */
    ಯದಿ (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    af = av_mallocz(ಪರಿಮಾಣ(*af));
    ಯದಿ (!af)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, ಪರಿಮಾಣ(*af->buf));
    ಯದಿ (!af->buf)
        ಗಚ್ಛ error;

    ಪ್ರತಿ (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        ಯದಿ (!af->buf[i])
            ಗಚ್ಛ error;
    }
    af->allocated_samples = nb_samples;

    ಪ್ರತ್ಯಾಗಮ af;

error:
    av_audio_fifo_free(af);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಪೂರ್ಣಾಙ್ಕ av_audio_fifo_realloc(AVAudioFifo *af, ಪೂರ್ಣಾಙ್ಕ nb_samples)
{
    ಧ್ರುವ size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    ಪೂರ್ಣಾಙ್ಕ i, ret, buf_size;

    ಯದಿ ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಯದಿ (buf_size > cur_size) {
        ಪ್ರತಿ (i = 0; i < af->nb_buffers; i++) {
            ಯದಿ ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                ಪ್ರತ್ಯಾಗಮ ret;
        }
    }
    af->allocated_samples = nb_samples;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_audio_fifo_write(AVAudioFifo *af, ಶೂನ್ಯ * ಧ್ರುವ *data, ಪೂರ್ಣಾಙ್ಕ nb_samples)
{
    ಪೂರ್ಣಾಙ್ಕ i, ret, size;

    /* automatically reallocate buffers if needed */
    ಯದಿ (av_audio_fifo_space(af) < nb_samples) {
        ಪೂರ್ಣಾಙ್ಕ current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        ಯದಿ (INT_MAX / 2 - current_size < nb_samples)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        /* reallocate buffers */
        ಯದಿ ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
    }

    size = nb_samples * af->sample_size;
    ಪ್ರತಿ (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    ಪ್ರತ್ಯಾಗಮ nb_samples;
}

ಪೂರ್ಣಾಙ್ಕ av_audio_fifo_peek(ಧ್ರುವ AVAudioFifo *af, ಶೂನ್ಯ * ಧ್ರುವ *data, ಪೂರ್ಣಾಙ್ಕ nb_samples)
{
    ಪ್ರತ್ಯಾಗಮ av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

ಪೂರ್ಣಾಙ್ಕ av_audio_fifo_peek_at(ಧ್ರುವ AVAudioFifo *af, ಶೂನ್ಯ * ಧ್ರುವ *data,
                          ಪೂರ್ಣಾಙ್ಕ nb_samples, ಪೂರ್ಣಾಙ್ಕ offset)
{
    ಪೂರ್ಣಾಙ್ಕ i, ret, size;

    ಯದಿ (offset < 0 || offset >= af->nb_samples)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    ಯದಿ (nb_samples < 0)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ಯದಿ (!nb_samples)
        ಪ್ರತ್ಯಾಗಮ 0;
    ಯದಿ (offset > af->nb_samples - nb_samples)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    ಪ್ರತಿ (i = 0; i < af->nb_buffers; i++) {
        ಯದಿ ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            ಪ್ರತ್ಯಾಗಮ AVERROR_BUG;
    }

    ಪ್ರತ್ಯಾಗಮ nb_samples;
}

ಪೂರ್ಣಾಙ್ಕ av_audio_fifo_read(AVAudioFifo *af, ಶೂನ್ಯ * ಧ್ರುವ *data, ಪೂರ್ಣಾಙ್ಕ nb_samples)
{
    ಪೂರ್ಣಾಙ್ಕ i, size;

    ಯದಿ (nb_samples < 0)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ಯದಿ (!nb_samples)
        ಪ್ರತ್ಯಾಗಮ 0;

    size = nb_samples * af->sample_size;
    ಪ್ರತಿ (i = 0; i < af->nb_buffers; i++) {
        ಯದಿ (av_fifo_read(af->buf[i], data[i], size) < 0)
            ಪ್ರತ್ಯಾಗಮ AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    ಪ್ರತ್ಯಾಗಮ nb_samples;
}

ಪೂರ್ಣಾಙ್ಕ av_audio_fifo_drain(AVAudioFifo *af, ಪೂರ್ಣಾಙ್ಕ nb_samples)
{
    ಪೂರ್ಣಾಙ್ಕ i, size;

    ಯದಿ (nb_samples < 0)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    ಯದಿ (nb_samples) {
        size = nb_samples * af->sample_size;
        ಪ್ರತಿ (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ av_audio_fifo_reset(AVAudioFifo *af)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

ಪೂರ್ಣಾಙ್ಕ av_audio_fifo_size(AVAudioFifo *af)
{
    ಪ್ರತ್ಯಾಗಮ af->nb_samples;
}

ಪೂರ್ಣಾಙ್ಕ av_audio_fifo_space(AVAudioFifo *af)
{
    ಪ್ರತ್ಯಾಗಮ af->allocated_samples - af->nb_samples;
}
