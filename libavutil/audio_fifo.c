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

#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <stddef.h>

#அந்தர்பாவ "audio_fifo.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "fifo.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "samplefmt.h"

கட்டமைப்பு AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    முழு nb_buffers;                 /**< number of buffers */
    முழு nb_samples;                 /**< number of samples currently in the FIFO */
    முழு allocated_samples;          /**< current allocated size, in samples */

    முழு channels;                   /**< number of channels */
    எண்ணிக்கை AVSampleFormat sample_fmt; /**< sample format */
    முழு sample_size;                /**< size, in bytes, of one sample in a buffer */
};

வெறுமை av_audio_fifo_free(AVAudioFifo *af)
{
    எனில் (af) {
        எனில் (af->buf) {
            முழு i;
            க்கு (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(எண்ணிக்கை AVSampleFormat sample_fmt, முழு channels,
                                 முழு nb_samples)
{
    AVAudioFifo *af;
    முழு buf_size, i;

    /* get channel buffer size (also validates parameters) */
    எனில் (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        திரும்பு வெற்று;

    af = av_mallocz(அளவு(*af));
    எனில் (!af)
        திரும்பு வெற்று;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, அளவு(*af->buf));
    எனில் (!af->buf)
        செல் error;

    க்கு (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        எனில் (!af->buf[i])
            செல் error;
    }
    af->allocated_samples = nb_samples;

    திரும்பு af;

error:
    av_audio_fifo_free(af);
    திரும்பு வெற்று;
}

முழு av_audio_fifo_realloc(AVAudioFifo *af, முழு nb_samples)
{
    மாறிலி size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    முழு i, ret, buf_size;

    எனில் ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        திரும்பு ret;

    எனில் (buf_size > cur_size) {
        க்கு (i = 0; i < af->nb_buffers; i++) {
            எனில் ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                திரும்பு ret;
        }
    }
    af->allocated_samples = nb_samples;
    திரும்பு 0;
}

முழு av_audio_fifo_write(AVAudioFifo *af, வெறுமை * மாறிலி *data, முழு nb_samples)
{
    முழு i, ret, size;

    /* automatically reallocate buffers if needed */
    எனில் (av_audio_fifo_space(af) < nb_samples) {
        முழு current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        எனில் (INT_MAX / 2 - current_size < nb_samples)
            திரும்பு AVERROR(EINVAL);
        /* reallocate buffers */
        எனில் ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            திரும்பு ret;
    }

    size = nb_samples * af->sample_size;
    க்கு (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        எனில் (ret < 0)
            திரும்பு AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    திரும்பு nb_samples;
}

முழு av_audio_fifo_peek(மாறிலி AVAudioFifo *af, வெறுமை * மாறிலி *data, முழு nb_samples)
{
    திரும்பு av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

முழு av_audio_fifo_peek_at(மாறிலி AVAudioFifo *af, வெறுமை * மாறிலி *data,
                          முழு nb_samples, முழு offset)
{
    முழு i, ret, size;

    எனில் (offset < 0 || offset >= af->nb_samples)
        திரும்பு AVERROR(EINVAL);
    எனில் (nb_samples < 0)
        திரும்பு AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    எனில் (!nb_samples)
        திரும்பு 0;
    எனில் (offset > af->nb_samples - nb_samples)
        திரும்பு AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    க்கு (i = 0; i < af->nb_buffers; i++) {
        எனில் ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            திரும்பு AVERROR_BUG;
    }

    திரும்பு nb_samples;
}

முழு av_audio_fifo_read(AVAudioFifo *af, வெறுமை * மாறிலி *data, முழு nb_samples)
{
    முழு i, size;

    எனில் (nb_samples < 0)
        திரும்பு AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    எனில் (!nb_samples)
        திரும்பு 0;

    size = nb_samples * af->sample_size;
    க்கு (i = 0; i < af->nb_buffers; i++) {
        எனில் (av_fifo_read(af->buf[i], data[i], size) < 0)
            திரும்பு AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    திரும்பு nb_samples;
}

முழு av_audio_fifo_drain(AVAudioFifo *af, முழு nb_samples)
{
    முழு i, size;

    எனில் (nb_samples < 0)
        திரும்பு AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    எனில் (nb_samples) {
        size = nb_samples * af->sample_size;
        க்கு (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    திரும்பு 0;
}

வெறுமை av_audio_fifo_reset(AVAudioFifo *af)
{
    முழு i;

    க்கு (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

முழு av_audio_fifo_size(AVAudioFifo *af)
{
    திரும்பு af->nb_samples;
}

முழு av_audio_fifo_space(AVAudioFifo *af)
{
    திரும்பு af->allocated_samples - af->nb_samples;
}
