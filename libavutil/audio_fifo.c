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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "audio_fifo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "fifo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "samplefmt.h"

ਬਣਤਰ AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    ਪੂਰਨ nb_buffers;                 /**< number of buffers */
    ਪੂਰਨ nb_samples;                 /**< number of samples currently in the FIFO */
    ਪੂਰਨ allocated_samples;          /**< current allocated size, in samples */

    ਪੂਰਨ channels;                   /**< number of channels */
    ਗਿਣਤੀ AVSampleFormat sample_fmt; /**< sample format */
    ਪੂਰਨ sample_ਮਾਪ;                /**< size, in bytes, of one sample in a buffer */
};

ਖਾਲੀ av_audio_fifo_free(AVAudioFifo *af)
{
    ਜੇ (af) {
        ਜੇ (af->buf) {
            ਪੂਰਨ i;
            ਲਈ (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(ਗਿਣਤੀ AVSampleFormat sample_fmt, ਪੂਰਨ channels,
                                 ਪੂਰਨ nb_samples)
{
    AVAudioFifo *af;
    ਪੂਰਨ buf_ਮਾਪ, i;

    /* get channel buffer size (also validates parameters) */
    ਜੇ (av_samples_get_ਬਫਰ_ਮਾਪ(&buf_ਮਾਪ, channels, nb_samples, sample_fmt, 1) < 0)
        ਵਾਪਸ ਨਿਰਾ;

    af = av_mallocz(ਆਕਾਰ(*af));
    ਜੇ (!af)
        ਵਾਪਸ ਨਿਰਾ;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_ਮਾਪ = buf_ਮਾਪ / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, ਆਕਾਰ(*af->buf));
    ਜੇ (!af->buf)
        ਜਾਓ error;

    ਲਈ (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_ਮਾਪ, 1, 0);
        ਜੇ (!af->buf[i])
            ਜਾਓ error;
    }
    af->allocated_samples = nb_samples;

    ਵਾਪਸ af;

error:
    av_audio_fifo_free(af);
    ਵਾਪਸ ਨਿਰਾ;
}

ਪੂਰਨ av_audio_fifo_realloc(AVAudioFifo *af, ਪੂਰਨ nb_samples)
{
    ਅਚਲ size_t cur_ਮਾਪ = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    ਪੂਰਨ i, ret, buf_ਮਾਪ;

    ਜੇ ((ret = av_samples_get_ਬਫਰ_ਮਾਪ(&buf_ਮਾਪ, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        ਵਾਪਸ ret;

    ਜੇ (buf_ਮਾਪ > cur_ਮਾਪ) {
        ਲਈ (i = 0; i < af->nb_buffers; i++) {
            ਜੇ ((ret = av_fifo_grow2(af->buf[i], buf_ਮਾਪ - cur_ਮਾਪ)) < 0)
                ਵਾਪਸ ret;
        }
    }
    af->allocated_samples = nb_samples;
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_audio_fifo_write(AVAudioFifo *af, ਖਾਲੀ * ਅਚਲ *ਅੰਕੜੇ, ਪੂਰਨ nb_samples)
{
    ਪੂਰਨ i, ret, ਮਾਪ;

    /* automatically reallocate buffers if needed */
    ਜੇ (av_audio_fifo_space(af) < nb_samples) {
        ਪੂਰਨ current_ਮਾਪ = av_audio_fifo_ਮਾਪ(af);
        /* check for integer overflow in new size calculation */
        ਜੇ (ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ / 2 - current_ਮਾਪ < nb_samples)
            ਵਾਪਸ AVERROR(EINVAL);
        /* reallocate buffers */
        ਜੇ ((ret = av_audio_fifo_realloc(af, 2 * (current_ਮਾਪ + nb_samples))) < 0)
            ਵਾਪਸ ret;
    }

    ਮਾਪ = nb_samples * af->sample_ਮਾਪ;
    ਲਈ (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], ਅੰਕੜੇ[i], ਮਾਪ);
        ਜੇ (ret < 0)
            ਵਾਪਸ AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    ਵਾਪਸ nb_samples;
}

ਪੂਰਨ av_audio_fifo_peek(ਅਚਲ AVAudioFifo *af, ਖਾਲੀ * ਅਚਲ *ਅੰਕੜੇ, ਪੂਰਨ nb_samples)
{
    ਵਾਪਸ av_audio_fifo_peek_at(af, ਅੰਕੜੇ, nb_samples, 0);
}

ਪੂਰਨ av_audio_fifo_peek_at(ਅਚਲ AVAudioFifo *af, ਖਾਲੀ * ਅਚਲ *ਅੰਕੜੇ,
                          ਪੂਰਨ nb_samples, ਪੂਰਨ ਵਿੱਥ)
{
    ਪੂਰਨ i, ret, ਮਾਪ;

    ਜੇ (ਵਿੱਥ < 0 || ਵਿੱਥ >= af->nb_samples)
        ਵਾਪਸ AVERROR(EINVAL);
    ਜੇ (nb_samples < 0)
        ਵਾਪਸ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ਜੇ (!nb_samples)
        ਵਾਪਸ 0;
    ਜੇ (ਵਿੱਥ > af->nb_samples - nb_samples)
        ਵਾਪਸ AVERROR(EINVAL);

    ਵਿੱਥ *= af->sample_ਮਾਪ;
    ਮਾਪ = nb_samples * af->sample_ਮਾਪ;
    ਲਈ (i = 0; i < af->nb_buffers; i++) {
        ਜੇ ((ret = av_fifo_peek(af->buf[i], ਅੰਕੜੇ[i], ਮਾਪ, ਵਿੱਥ)) < 0)
            ਵਾਪਸ AVERROR_BUG;
    }

    ਵਾਪਸ nb_samples;
}

ਪੂਰਨ av_audio_fifo_read(AVAudioFifo *af, ਖਾਲੀ * ਅਚਲ *ਅੰਕੜੇ, ਪੂਰਨ nb_samples)
{
    ਪੂਰਨ i, ਮਾਪ;

    ਜੇ (nb_samples < 0)
        ਵਾਪਸ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ਜੇ (!nb_samples)
        ਵਾਪਸ 0;

    ਮਾਪ = nb_samples * af->sample_ਮਾਪ;
    ਲਈ (i = 0; i < af->nb_buffers; i++) {
        ਜੇ (av_fifo_read(af->buf[i], ਅੰਕੜੇ[i], ਮਾਪ) < 0)
            ਵਾਪਸ AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    ਵਾਪਸ nb_samples;
}

ਪੂਰਨ av_audio_fifo_drain(AVAudioFifo *af, ਪੂਰਨ nb_samples)
{
    ਪੂਰਨ i, ਮਾਪ;

    ਜੇ (nb_samples < 0)
        ਵਾਪਸ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    ਜੇ (nb_samples) {
        ਮਾਪ = nb_samples * af->sample_ਮਾਪ;
        ਲਈ (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], ਮਾਪ);
        af->nb_samples -= nb_samples;
    }
    ਵਾਪਸ 0;
}

ਖਾਲੀ av_audio_fifo_reset(AVAudioFifo *af)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

ਪੂਰਨ av_audio_fifo_ਮਾਪ(AVAudioFifo *af)
{
    ਵਾਪਸ af->nb_samples;
}

ਪੂਰਨ av_audio_fifo_space(AVAudioFifo *af)
{
    ਵਾਪਸ af->allocated_samples - af->nb_samples;
}
