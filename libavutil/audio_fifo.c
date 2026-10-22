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

#ضمن <limits.h>
#ضمن <stddef.h>

#ضمن "audio_fifo.h"
#ضمن "error.h"
#ضمن "fifo.h"
#ضمن "macros.h"
#ضمن "mem.h"
#ضمن "samplefmt.h"

بنية AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    صحيح nb_buffers;                 /**< number of buffers */
    صحيح nb_samples;                 /**< number of samples currently in the FIFO */
    صحيح allocated_samples;          /**< current allocated size, in samples */

    صحيح channels;                   /**< number of channels */
    تعداد AVSampleFormat sample_fmt; /**< sample format */
    صحيح sample_ناپ;                /**< size, in bytes, of one sample in a buffer */
};

فراغ av_audio_fifo_free(AVAudioFifo *af)
{
    إذا (af) {
        إذا (af->buf) {
            صحيح i;
            لكل (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(تعداد AVSampleFormat sample_fmt, صحيح channels,
                                 صحيح nb_samples)
{
    AVAudioFifo *af;
    صحيح buf_ناپ, i;

    /* get channel buffer size (also validates parameters) */
    إذا (av_samples_get_بفر_ناپ(&buf_ناپ, channels, nb_samples, sample_fmt, 1) < 0)
        أرجع عدم;

    af = av_mallocz(حجم(*af));
    إذا (!af)
        أرجع عدم;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_ناپ = buf_ناپ / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, حجم(*af->buf));
    إذا (!af->buf)
        اذهب error;

    لكل (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_ناپ, 1, 0);
        إذا (!af->buf[i])
            اذهب error;
    }
    af->allocated_samples = nb_samples;

    أرجع af;

error:
    av_audio_fifo_free(af);
    أرجع عدم;
}

صحيح av_audio_fifo_realloc(AVAudioFifo *af, صحيح nb_samples)
{
    ثابت size_t cur_ناپ = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    صحيح i, ret, buf_ناپ;

    إذا ((ret = av_samples_get_بفر_ناپ(&buf_ناپ, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        أرجع ret;

    إذا (buf_ناپ > cur_ناپ) {
        لكل (i = 0; i < af->nb_buffers; i++) {
            إذا ((ret = av_fifo_grow2(af->buf[i], buf_ناپ - cur_ناپ)) < 0)
                أرجع ret;
        }
    }
    af->allocated_samples = nb_samples;
    أرجع 0;
}

صحيح av_audio_fifo_write(AVAudioFifo *af, فراغ * ثابت *انکڑے, صحيح nb_samples)
{
    صحيح i, ret, ناپ;

    /* automatically reallocate buffers if needed */
    إذا (av_audio_fifo_space(af) < nb_samples) {
        صحيح current_ناپ = av_audio_fifo_ناپ(af);
        /* check for integer overflow in new size calculation */
        إذا (ودھ_توں_ودھ_عدد / 2 - current_ناپ < nb_samples)
            أرجع AVERROR(EINVAL);
        /* reallocate buffers */
        إذا ((ret = av_audio_fifo_realloc(af, 2 * (current_ناپ + nb_samples))) < 0)
            أرجع ret;
    }

    ناپ = nb_samples * af->sample_ناپ;
    لكل (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], انکڑے[i], ناپ);
        إذا (ret < 0)
            أرجع AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    أرجع nb_samples;
}

صحيح av_audio_fifo_peek(ثابت AVAudioFifo *af, فراغ * ثابت *انکڑے, صحيح nb_samples)
{
    أرجع av_audio_fifo_peek_at(af, انکڑے, nb_samples, 0);
}

صحيح av_audio_fifo_peek_at(ثابت AVAudioFifo *af, فراغ * ثابت *انکڑے,
                          صحيح nb_samples, صحيح وتھ)
{
    صحيح i, ret, ناپ;

    إذا (وتھ < 0 || وتھ >= af->nb_samples)
        أرجع AVERROR(EINVAL);
    إذا (nb_samples < 0)
        أرجع AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    إذا (!nb_samples)
        أرجع 0;
    إذا (وتھ > af->nb_samples - nb_samples)
        أرجع AVERROR(EINVAL);

    وتھ *= af->sample_ناپ;
    ناپ = nb_samples * af->sample_ناپ;
    لكل (i = 0; i < af->nb_buffers; i++) {
        إذا ((ret = av_fifo_peek(af->buf[i], انکڑے[i], ناپ, وتھ)) < 0)
            أرجع AVERROR_BUG;
    }

    أرجع nb_samples;
}

صحيح av_audio_fifo_read(AVAudioFifo *af, فراغ * ثابت *انکڑے, صحيح nb_samples)
{
    صحيح i, ناپ;

    إذا (nb_samples < 0)
        أرجع AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    إذا (!nb_samples)
        أرجع 0;

    ناپ = nb_samples * af->sample_ناپ;
    لكل (i = 0; i < af->nb_buffers; i++) {
        إذا (av_fifo_read(af->buf[i], انکڑے[i], ناپ) < 0)
            أرجع AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    أرجع nb_samples;
}

صحيح av_audio_fifo_drain(AVAudioFifo *af, صحيح nb_samples)
{
    صحيح i, ناپ;

    إذا (nb_samples < 0)
        أرجع AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    إذا (nb_samples) {
        ناپ = nb_samples * af->sample_ناپ;
        لكل (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], ناپ);
        af->nb_samples -= nb_samples;
    }
    أرجع 0;
}

فراغ av_audio_fifo_reset(AVAudioFifo *af)
{
    صحيح i;

    لكل (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

صحيح av_audio_fifo_ناپ(AVAudioFifo *af)
{
    أرجع af->nb_samples;
}

صحيح av_audio_fifo_space(AVAudioFifo *af)
{
    أرجع af->allocated_samples - af->nb_samples;
}
