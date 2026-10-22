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

ರಚನೆ AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    ಪೂರ್ಣಾಂಕ nb_buffers;                 /**< number of buffers */
    ಪೂರ್ಣಾಂಕ nb_samples;                 /**< number of samples currently in the FIFO */
    ಪೂರ್ಣಾಂಕ allocated_samples;          /**< current allocated size, in samples */

    ಪೂರ್ಣಾಂಕ channels;                   /**< number of channels */
    ಎಣಿಕೆ AVSampleFormat sample_fmt; /**< sample format */
    ಪೂರ್ಣಾಂಕ sample_ಗಾತ್ರ;                /**< size, in bytes, of one sample in a buffer */
};

ಶೂನ್ಯ av_audio_fifo_free(AVAudioFifo *af)
{
    ಆದರೆ (af) {
        ಆದರೆ (af->buf) {
            ಪೂರ್ಣಾಂಕ i;
            ಗಾಗಿ (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(ಎಣಿಕೆ AVSampleFormat sample_fmt, ಪೂರ್ಣಾಂಕ channels,
                                 ಪೂರ್ಣಾಂಕ nb_samples)
{
    AVAudioFifo *af;
    ಪೂರ್ಣಾಂಕ buf_ಗಾತ್ರ, i;

    /* get channel buffer size (also validates parameters) */
    ಆದರೆ (av_samples_get_ಬಫರ್_ಗಾತ್ರ(&buf_ಗಾತ್ರ, channels, nb_samples, sample_fmt, 1) < 0)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    af = av_mallocz(ಗಾತ್ರ(*af));
    ಆದರೆ (!af)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_ಗಾತ್ರ = buf_ಗಾತ್ರ / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, ಗಾತ್ರ(*af->buf));
    ಆದರೆ (!af->buf)
        ಹೋಗು error;

    ಗಾಗಿ (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_ಗಾತ್ರ, 1, 0);
        ಆದರೆ (!af->buf[i])
            ಹೋಗು error;
    }
    af->allocated_samples = nb_samples;

    ಹಿಂತಿರುಗಿ af;

error:
    av_audio_fifo_free(af);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಪೂರ್ಣಾಂಕ av_audio_fifo_realloc(AVAudioFifo *af, ಪೂರ್ಣಾಂಕ nb_samples)
{
    ಸ್ಥಿರಾಂಕ size_t cur_ಗಾತ್ರ = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    ಪೂರ್ಣಾಂಕ i, ret, buf_ಗಾತ್ರ;

    ಆದರೆ ((ret = av_samples_get_ಬಫರ್_ಗಾತ್ರ(&buf_ಗಾತ್ರ, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (buf_ಗಾತ್ರ > cur_ಗಾತ್ರ) {
        ಗಾಗಿ (i = 0; i < af->nb_buffers; i++) {
            ಆದರೆ ((ret = av_fifo_grow2(af->buf[i], buf_ಗಾತ್ರ - cur_ಗಾತ್ರ)) < 0)
                ಹಿಂತಿರುಗಿ ret;
        }
    }
    af->allocated_samples = nb_samples;
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_audio_fifo_write(AVAudioFifo *af, ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ *ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ nb_samples)
{
    ಪೂರ್ಣಾಂಕ i, ret, ಗಾತ್ರ_2;

    /* automatically reallocate buffers if needed */
    ಆದರೆ (av_audio_fifo_space(af) < nb_samples) {
        ಪೂರ್ಣಾಂಕ current_ಗಾತ್ರ = av_audio_fifo_ಗಾತ್ರ(af);
        /* check for integer overflow in new size calculation */
        ಆದರೆ (ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ / 2 - current_ಗಾತ್ರ < nb_samples)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        /* reallocate buffers */
        ಆದರೆ ((ret = av_audio_fifo_realloc(af, 2 * (current_ಗಾತ್ರ + nb_samples))) < 0)
            ಹಿಂತಿರುಗಿ ret;
    }

    ಗಾತ್ರ_2 = nb_samples * af->sample_ಗಾತ್ರ;
    ಗಾಗಿ (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], ದತ್ತಾಂಶ[i], ಗಾತ್ರ_2);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    ಹಿಂತಿರುಗಿ nb_samples;
}

ಪೂರ್ಣಾಂಕ av_audio_fifo_peek(ಸ್ಥಿರಾಂಕ AVAudioFifo *af, ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ *ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ nb_samples)
{
    ಹಿಂತಿರುಗಿ av_audio_fifo_peek_at(af, ದತ್ತಾಂಶ, nb_samples, 0);
}

ಪೂರ್ಣಾಂಕ av_audio_fifo_peek_at(ಸ್ಥಿರಾಂಕ AVAudioFifo *af, ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ *ದತ್ತಾಂಶ,
                          ಪೂರ್ಣಾಂಕ nb_samples, ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ)
{
    ಪೂರ್ಣಾಂಕ i, ret, ಗಾತ್ರ_2;

    ಆದರೆ (ಸ್ಥಾನಾಂತರ < 0 || ಸ್ಥಾನಾಂತರ >= af->nb_samples)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    ಆದರೆ (nb_samples < 0)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ಆದರೆ (!nb_samples)
        ಹಿಂತಿರುಗಿ 0;
    ಆದರೆ (ಸ್ಥಾನಾಂತರ > af->nb_samples - nb_samples)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಸ್ಥಾನಾಂತರ *= af->sample_ಗಾತ್ರ;
    ಗಾತ್ರ_2 = nb_samples * af->sample_ಗಾತ್ರ;
    ಗಾಗಿ (i = 0; i < af->nb_buffers; i++) {
        ಆದರೆ ((ret = av_fifo_peek(af->buf[i], ದತ್ತಾಂಶ[i], ಗಾತ್ರ_2, ಸ್ಥಾನಾಂತರ)) < 0)
            ಹಿಂತಿರುಗಿ AVERROR_BUG;
    }

    ಹಿಂತಿರುಗಿ nb_samples;
}

ಪೂರ್ಣಾಂಕ av_audio_fifo_read(AVAudioFifo *af, ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ *ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ nb_samples)
{
    ಪೂರ್ಣಾಂಕ i, ಗಾತ್ರ_2;

    ಆದರೆ (nb_samples < 0)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ಆದರೆ (!nb_samples)
        ಹಿಂತಿರುಗಿ 0;

    ಗಾತ್ರ_2 = nb_samples * af->sample_ಗಾತ್ರ;
    ಗಾಗಿ (i = 0; i < af->nb_buffers; i++) {
        ಆದರೆ (av_fifo_read(af->buf[i], ದತ್ತಾಂಶ[i], ಗಾತ್ರ_2) < 0)
            ಹಿಂತಿರುಗಿ AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    ಹಿಂತಿರುಗಿ nb_samples;
}

ಪೂರ್ಣಾಂಕ av_audio_fifo_drain(AVAudioFifo *af, ಪೂರ್ಣಾಂಕ nb_samples)
{
    ಪೂರ್ಣಾಂಕ i, ಗಾತ್ರ_2;

    ಆದರೆ (nb_samples < 0)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    ಆದರೆ (nb_samples) {
        ಗಾತ್ರ_2 = nb_samples * af->sample_ಗಾತ್ರ;
        ಗಾಗಿ (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], ಗಾತ್ರ_2);
        af->nb_samples -= nb_samples;
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ av_audio_fifo_reset(AVAudioFifo *af)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

ಪೂರ್ಣಾಂಕ av_audio_fifo_ಗಾತ್ರ(AVAudioFifo *af)
{
    ಹಿಂತಿರುಗಿ af->nb_samples;
}

ಪೂರ್ಣಾಂಕ av_audio_fifo_space(AVAudioFifo *af)
{
    ಹಿಂತಿರುಗಿ af->allocated_samples - af->nb_samples;
}
