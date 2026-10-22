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

#ଅନ୍ତର୍ଭାଵ <limits.h>
#ଅନ୍ତର୍ଭାଵ <stddef.h>

#ଅନ୍ତର୍ଭାଵ "audio_fifo.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "fifo.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "samplefmt.h"

ସଂରଚନା AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_buffers;                 /**< number of buffers */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples;                 /**< number of samples currently in the FIFO */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା allocated_samples;          /**< current allocated size, in samples */

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା channels;                   /**< number of channels */
    ଗଣନା AVSampleFormat sample_fmt; /**< sample format */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା sample_size;                /**< size, in bytes, of one sample in a buffer */
};

ଶୂନ୍ୟ av_audio_fifo_free(AVAudioFifo *af)
{
    ଯଦି (af) {
        ଯଦି (af->buf) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
            ପାଇଁ (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(ଗଣନା AVSampleFormat sample_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା channels,
                                 ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples)
{
    AVAudioFifo *af;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା buf_size, i;

    /* get channel buffer size (also validates parameters) */
    ଯଦି (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        ଫେରନ୍ତୁ ଖାଲି;

    af = av_mallocz(ଆକାର(*af));
    ଯଦି (!af)
        ଫେରନ୍ତୁ ଖାଲି;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, ଆକାର(*af->buf));
    ଯଦି (!af->buf)
        ଯାଅ error;

    ପାଇଁ (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        ଯଦି (!af->buf[i])
            ଯାଅ error;
    }
    af->allocated_samples = nb_samples;

    ଫେରନ୍ତୁ af;

error:
    av_audio_fifo_free(af);
    ଫେରନ୍ତୁ ଖାଲି;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_audio_fifo_realloc(AVAudioFifo *af, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples)
{
    ଅଚଳ size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret, buf_size;

    ଯଦି ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        ଫେରନ୍ତୁ ret;

    ଯଦି (buf_size > cur_size) {
        ପାଇଁ (i = 0; i < af->nb_buffers; i++) {
            ଯଦି ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                ଫେରନ୍ତୁ ret;
        }
    }
    af->allocated_samples = nb_samples;
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_audio_fifo_write(AVAudioFifo *af, ଶୂନ୍ୟ * ଅଚଳ *data, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret, size;

    /* automatically reallocate buffers if needed */
    ଯଦି (av_audio_fifo_space(af) < nb_samples) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        ଯଦି (INT_MAX / 2 - current_size < nb_samples)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        /* reallocate buffers */
        ଯଦି ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            ଫେରନ୍ତୁ ret;
    }

    size = nb_samples * af->sample_size;
    ପାଇଁ (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    ଫେରନ୍ତୁ nb_samples;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_audio_fifo_peek(ଅଚଳ AVAudioFifo *af, ଶୂନ୍ୟ * ଅଚଳ *data, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples)
{
    ଫେରନ୍ତୁ av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_audio_fifo_peek_at(ଅଚଳ AVAudioFifo *af, ଶୂନ୍ୟ * ଅଚଳ *data,
                          ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples, ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret, size;

    ଯଦି (offset < 0 || offset >= af->nb_samples)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    ଯଦି (nb_samples < 0)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ଯଦି (!nb_samples)
        ଫେରନ୍ତୁ 0;
    ଯଦି (offset > af->nb_samples - nb_samples)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    ପାଇଁ (i = 0; i < af->nb_buffers; i++) {
        ଯଦି ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            ଫେରନ୍ତୁ AVERROR_BUG;
    }

    ଫେରନ୍ତୁ nb_samples;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_audio_fifo_read(AVAudioFifo *af, ଶୂନ୍ୟ * ଅଚଳ *data, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, size;

    ଯଦି (nb_samples < 0)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ଯଦି (!nb_samples)
        ଫେରନ୍ତୁ 0;

    size = nb_samples * af->sample_size;
    ପାଇଁ (i = 0; i < af->nb_buffers; i++) {
        ଯଦି (av_fifo_read(af->buf[i], data[i], size) < 0)
            ଫେରନ୍ତୁ AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    ଫେରନ୍ତୁ nb_samples;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_audio_fifo_drain(AVAudioFifo *af, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, size;

    ଯଦି (nb_samples < 0)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    ଯଦି (nb_samples) {
        size = nb_samples * af->sample_size;
        ପାଇଁ (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ av_audio_fifo_reset(AVAudioFifo *af)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_audio_fifo_size(AVAudioFifo *af)
{
    ଫେରନ୍ତୁ af->nb_samples;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_audio_fifo_space(AVAudioFifo *af)
{
    ଫେରନ୍ତୁ af->allocated_samples - af->nb_samples;
}
