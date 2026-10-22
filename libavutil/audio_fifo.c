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

#અન્તર્ભાવ <limits.h>
#અન્તર્ભાવ <stddef.h>

#અન્તર્ભાવ "audio_fifo.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "fifo.h"
#અન્તર્ભાવ "macros.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "samplefmt.h"

સંરચના AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    પૂર્ણાંક nb_buffers;                 /**< number of buffers */
    પૂર્ણાંક nb_samples;                 /**< number of samples currently in the FIFO */
    પૂર્ણાંક allocated_samples;          /**< current allocated size, in samples */

    પૂર્ણાંક channels;                   /**< number of channels */
    ગણના AVSampleFormat sample_fmt; /**< sample format */
    પૂર્ણાંક sample_size;                /**< size, in bytes, of one sample in a buffer */
};

શૂન્ય av_audio_fifo_free(AVAudioFifo *af)
{
    જો (af) {
        જો (af->buf) {
            પૂર્ણાંક i;
            માટે (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(ગણના AVSampleFormat sample_fmt, પૂર્ણાંક channels,
                                 પૂર્ણાંક nb_samples)
{
    AVAudioFifo *af;
    પૂર્ણાંક buf_size, i;

    /* get channel buffer size (also validates parameters) */
    જો (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        પાછા ખાલી;

    af = av_mallocz(કદ(*af));
    જો (!af)
        પાછા ખાલી;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, કદ(*af->buf));
    જો (!af->buf)
        જાઓ error;

    માટે (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        જો (!af->buf[i])
            જાઓ error;
    }
    af->allocated_samples = nb_samples;

    પાછા af;

error:
    av_audio_fifo_free(af);
    પાછા ખાલી;
}

પૂર્ણાંક av_audio_fifo_realloc(AVAudioFifo *af, પૂર્ણાંક nb_samples)
{
    અચલ size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    પૂર્ણાંક i, ret, buf_size;

    જો ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        પાછા ret;

    જો (buf_size > cur_size) {
        માટે (i = 0; i < af->nb_buffers; i++) {
            જો ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                પાછા ret;
        }
    }
    af->allocated_samples = nb_samples;
    પાછા 0;
}

પૂર્ણાંક av_audio_fifo_write(AVAudioFifo *af, શૂન્ય * અચલ *data, પૂર્ણાંક nb_samples)
{
    પૂર્ણાંક i, ret, size;

    /* automatically reallocate buffers if needed */
    જો (av_audio_fifo_space(af) < nb_samples) {
        પૂર્ણાંક current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        જો (INT_MAX / 2 - current_size < nb_samples)
            પાછા AVERROR(EINVAL);
        /* reallocate buffers */
        જો ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            પાછા ret;
    }

    size = nb_samples * af->sample_size;
    માટે (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        જો (ret < 0)
            પાછા AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    પાછા nb_samples;
}

પૂર્ણાંક av_audio_fifo_peek(અચલ AVAudioFifo *af, શૂન્ય * અચલ *data, પૂર્ણાંક nb_samples)
{
    પાછા av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

પૂર્ણાંક av_audio_fifo_peek_at(અચલ AVAudioFifo *af, શૂન્ય * અચલ *data,
                          પૂર્ણાંક nb_samples, પૂર્ણાંક offset)
{
    પૂર્ણાંક i, ret, size;

    જો (offset < 0 || offset >= af->nb_samples)
        પાછા AVERROR(EINVAL);
    જો (nb_samples < 0)
        પાછા AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    જો (!nb_samples)
        પાછા 0;
    જો (offset > af->nb_samples - nb_samples)
        પાછા AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    માટે (i = 0; i < af->nb_buffers; i++) {
        જો ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            પાછા AVERROR_BUG;
    }

    પાછા nb_samples;
}

પૂર્ણાંક av_audio_fifo_read(AVAudioFifo *af, શૂન્ય * અચલ *data, પૂર્ણાંક nb_samples)
{
    પૂર્ણાંક i, size;

    જો (nb_samples < 0)
        પાછા AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    જો (!nb_samples)
        પાછા 0;

    size = nb_samples * af->sample_size;
    માટે (i = 0; i < af->nb_buffers; i++) {
        જો (av_fifo_read(af->buf[i], data[i], size) < 0)
            પાછા AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    પાછા nb_samples;
}

પૂર્ણાંક av_audio_fifo_drain(AVAudioFifo *af, પૂર્ણાંક nb_samples)
{
    પૂર્ણાંક i, size;

    જો (nb_samples < 0)
        પાછા AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    જો (nb_samples) {
        size = nb_samples * af->sample_size;
        માટે (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    પાછા 0;
}

શૂન્ય av_audio_fifo_reset(AVAudioFifo *af)
{
    પૂર્ણાંક i;

    માટે (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

પૂર્ણાંક av_audio_fifo_size(AVAudioFifo *af)
{
    પાછા af->nb_samples;
}

પૂર્ણાંક av_audio_fifo_space(AVAudioFifo *af)
{
    પાછા af->allocated_samples - af->nb_samples;
}
