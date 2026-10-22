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
    صحيح sample_سائيز;                /**< size, in bytes, of one sample in a buffer */
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
    صحيح buf_سائيز, i;

    /* get channel buffer size (also validates parameters) */
    إذا (av_samples_get_بفر_سائيز(&buf_سائيز, channels, nb_samples, sample_fmt, 1) < 0)
        أرجع عدم;

    af = av_mallocz(حجم(*af));
    إذا (!af)
        أرجع عدم;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_سائيز = buf_سائيز / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, حجم(*af->buf));
    إذا (!af->buf)
        اذهب error;

    لكل (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_سائيز, 1, 0);
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
    ثابت size_t cur_سائيز = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    صحيح i, ret, buf_سائيز;

    إذا ((ret = av_samples_get_بفر_سائيز(&buf_سائيز, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        أرجع ret;

    إذا (buf_سائيز > cur_سائيز) {
        لكل (i = 0; i < af->nb_buffers; i++) {
            إذا ((ret = av_fifo_grow2(af->buf[i], buf_سائيز - cur_سائيز)) < 0)
                أرجع ret;
        }
    }
    af->allocated_samples = nb_samples;
    أرجع 0;
}

صحيح av_audio_fifo_write(AVAudioFifo *af, فراغ * ثابت *معلومات, صحيح nb_samples)
{
    صحيح i, ret, سائيز;

    /* automatically reallocate buffers if needed */
    إذا (av_audio_fifo_space(af) < nb_samples) {
        صحيح current_سائيز = av_audio_fifo_سائيز(af);
        /* check for integer overflow in new size calculation */
        إذا (وڌ_کان_وڌ_عدد / 2 - current_سائيز < nb_samples)
            أرجع AVERROR(EINVAL);
        /* reallocate buffers */
        إذا ((ret = av_audio_fifo_realloc(af, 2 * (current_سائيز + nb_samples))) < 0)
            أرجع ret;
    }

    سائيز = nb_samples * af->sample_سائيز;
    لكل (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], معلومات[i], سائيز);
        إذا (ret < 0)
            أرجع AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    أرجع nb_samples;
}

صحيح av_audio_fifo_peek(ثابت AVAudioFifo *af, فراغ * ثابت *معلومات, صحيح nb_samples)
{
    أرجع av_audio_fifo_peek_at(af, معلومات, nb_samples, 0);
}

صحيح av_audio_fifo_peek_at(ثابت AVAudioFifo *af, فراغ * ثابت *معلومات,
                          صحيح nb_samples, صحيح وٿي)
{
    صحيح i, ret, سائيز;

    إذا (وٿي < 0 || وٿي >= af->nb_samples)
        أرجع AVERROR(EINVAL);
    إذا (nb_samples < 0)
        أرجع AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    إذا (!nb_samples)
        أرجع 0;
    إذا (وٿي > af->nb_samples - nb_samples)
        أرجع AVERROR(EINVAL);

    وٿي *= af->sample_سائيز;
    سائيز = nb_samples * af->sample_سائيز;
    لكل (i = 0; i < af->nb_buffers; i++) {
        إذا ((ret = av_fifo_peek(af->buf[i], معلومات[i], سائيز, وٿي)) < 0)
            أرجع AVERROR_BUG;
    }

    أرجع nb_samples;
}

صحيح av_audio_fifo_read(AVAudioFifo *af, فراغ * ثابت *معلومات, صحيح nb_samples)
{
    صحيح i, سائيز;

    إذا (nb_samples < 0)
        أرجع AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    إذا (!nb_samples)
        أرجع 0;

    سائيز = nb_samples * af->sample_سائيز;
    لكل (i = 0; i < af->nb_buffers; i++) {
        إذا (av_fifo_read(af->buf[i], معلومات[i], سائيز) < 0)
            أرجع AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    أرجع nb_samples;
}

صحيح av_audio_fifo_drain(AVAudioFifo *af, صحيح nb_samples)
{
    صحيح i, سائيز;

    إذا (nb_samples < 0)
        أرجع AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    إذا (nb_samples) {
        سائيز = nb_samples * af->sample_سائيز;
        لكل (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], سائيز);
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

صحيح av_audio_fifo_سائيز(AVAudioFifo *af)
{
    أرجع af->nb_samples;
}

صحيح av_audio_fifo_space(AVAudioFifo *af)
{
    أرجع af->allocated_samples - af->nb_samples;
}
