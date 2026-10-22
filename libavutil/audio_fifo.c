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

#شامل <limits.h>
#شامل <stddef.h>

#شامل "audio_fifo.h"
#شامل "error.h"
#شامل "fifo.h"
#شامل "macros.h"
#شامل "mem.h"
#شامل "samplefmt.h"

ساختار AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    صحیح nb_buffers;                 /**< number of buffers */
    صحیح nb_samples;                 /**< number of samples currently in the FIFO */
    صحیح allocated_samples;          /**< current allocated size, in samples */

    صحیح channels;                   /**< number of channels */
    شمارش AVSampleFormat sample_fmt; /**< sample format */
    صحیح sample_size;                /**< size, in bytes, of one sample in a buffer */
};

تهی av_audio_fifo_free(AVAudioFifo *af)
{
    اگر (af) {
        اگر (af->buf) {
            صحیح i;
            برای (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(شمارش AVSampleFormat sample_fmt, صحیح channels,
                                 صحیح nb_samples)
{
    AVAudioFifo *af;
    صحیح buf_size, i;

    /* get channel buffer size (also validates parameters) */
    اگر (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        بازگشت پوچ;

    af = av_mallocz(اندازه(*af));
    اگر (!af)
        بازگشت پوچ;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, اندازه(*af->buf));
    اگر (!af->buf)
        برو error;

    برای (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        اگر (!af->buf[i])
            برو error;
    }
    af->allocated_samples = nb_samples;

    بازگشت af;

error:
    av_audio_fifo_free(af);
    بازگشت پوچ;
}

صحیح av_audio_fifo_realloc(AVAudioFifo *af, صحیح nb_samples)
{
    ثابت size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    صحیح i, ret, buf_size;

    اگر ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        بازگشت ret;

    اگر (buf_size > cur_size) {
        برای (i = 0; i < af->nb_buffers; i++) {
            اگر ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                بازگشت ret;
        }
    }
    af->allocated_samples = nb_samples;
    بازگشت 0;
}

صحیح av_audio_fifo_write(AVAudioFifo *af, تهی * ثابت *data, صحیح nb_samples)
{
    صحیح i, ret, size;

    /* automatically reallocate buffers if needed */
    اگر (av_audio_fifo_space(af) < nb_samples) {
        صحیح current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        اگر (INT_MAX / 2 - current_size < nb_samples)
            بازگشت AVERROR(EINVAL);
        /* reallocate buffers */
        اگر ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            بازگشت ret;
    }

    size = nb_samples * af->sample_size;
    برای (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        اگر (ret < 0)
            بازگشت AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    بازگشت nb_samples;
}

صحیح av_audio_fifo_peek(ثابت AVAudioFifo *af, تهی * ثابت *data, صحیح nb_samples)
{
    بازگشت av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

صحیح av_audio_fifo_peek_at(ثابت AVAudioFifo *af, تهی * ثابت *data,
                          صحیح nb_samples, صحیح offset)
{
    صحیح i, ret, size;

    اگر (offset < 0 || offset >= af->nb_samples)
        بازگشت AVERROR(EINVAL);
    اگر (nb_samples < 0)
        بازگشت AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    اگر (!nb_samples)
        بازگشت 0;
    اگر (offset > af->nb_samples - nb_samples)
        بازگشت AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    برای (i = 0; i < af->nb_buffers; i++) {
        اگر ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            بازگشت AVERROR_BUG;
    }

    بازگشت nb_samples;
}

صحیح av_audio_fifo_read(AVAudioFifo *af, تهی * ثابت *data, صحیح nb_samples)
{
    صحیح i, size;

    اگر (nb_samples < 0)
        بازگشت AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    اگر (!nb_samples)
        بازگشت 0;

    size = nb_samples * af->sample_size;
    برای (i = 0; i < af->nb_buffers; i++) {
        اگر (av_fifo_read(af->buf[i], data[i], size) < 0)
            بازگشت AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    بازگشت nb_samples;
}

صحیح av_audio_fifo_drain(AVAudioFifo *af, صحیح nb_samples)
{
    صحیح i, size;

    اگر (nb_samples < 0)
        بازگشت AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    اگر (nb_samples) {
        size = nb_samples * af->sample_size;
        برای (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    بازگشت 0;
}

تهی av_audio_fifo_reset(AVAudioFifo *af)
{
    صحیح i;

    برای (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

صحیح av_audio_fifo_size(AVAudioFifo *af)
{
    بازگشت af->nb_samples;
}

صحیح av_audio_fifo_space(AVAudioFifo *af)
{
    بازگشت af->allocated_samples - af->nb_samples;
}
