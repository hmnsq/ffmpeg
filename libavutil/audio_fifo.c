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
    صحيح sample_size;                /**< size, in bytes, of one sample in a buffer */
};

فراغ av_audio_fifo_free(AVAudioFifo *af)
{
    אם (af) {
        אם (af->buf) {
            صحيح i;
            עבור (i = 0; i < af->nb_buffers; i++) {
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
    صحيح buf_size, i;

    /* get channel buffer size (also validates parameters) */
    אם (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        החזר عدم;

    af = av_mallocz(حجم(*af));
    אם (!af)
        החזר عدم;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, حجم(*af->buf));
    אם (!af->buf)
        اذهب error;

    עבור (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        אם (!af->buf[i])
            اذهب error;
    }
    af->allocated_samples = nb_samples;

    החזר af;

error:
    av_audio_fifo_free(af);
    החזר عدم;
}

صحيح av_audio_fifo_realloc(AVAudioFifo *af, صحيح nb_samples)
{
    ثابت size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    صحيح i, ret, buf_size;

    אם ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        החזר ret;

    אם (buf_size > cur_size) {
        עבור (i = 0; i < af->nb_buffers; i++) {
            אם ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                החזר ret;
        }
    }
    af->allocated_samples = nb_samples;
    החזר 0;
}

صحيح av_audio_fifo_write(AVAudioFifo *af, فراغ * ثابت *data, صحيح nb_samples)
{
    صحيح i, ret, size;

    /* automatically reallocate buffers if needed */
    אם (av_audio_fifo_space(af) < nb_samples) {
        صحيح current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        אם (INT_MAX / 2 - current_size < nb_samples)
            החזר AVERROR(EINVAL);
        /* reallocate buffers */
        אם ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            החזר ret;
    }

    size = nb_samples * af->sample_size;
    עבור (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        אם (ret < 0)
            החזר AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    החזר nb_samples;
}

صحيح av_audio_fifo_peek(ثابت AVAudioFifo *af, فراغ * ثابت *data, صحيح nb_samples)
{
    החזר av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

صحيح av_audio_fifo_peek_at(ثابت AVAudioFifo *af, فراغ * ثابت *data,
                          صحيح nb_samples, صحيح offset)
{
    صحيح i, ret, size;

    אם (offset < 0 || offset >= af->nb_samples)
        החזר AVERROR(EINVAL);
    אם (nb_samples < 0)
        החזר AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    אם (!nb_samples)
        החזר 0;
    אם (offset > af->nb_samples - nb_samples)
        החזר AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    עבור (i = 0; i < af->nb_buffers; i++) {
        אם ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            החזר AVERROR_BUG;
    }

    החזר nb_samples;
}

صحيح av_audio_fifo_read(AVAudioFifo *af, فراغ * ثابت *data, صحيح nb_samples)
{
    صحيح i, size;

    אם (nb_samples < 0)
        החזר AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    אם (!nb_samples)
        החזר 0;

    size = nb_samples * af->sample_size;
    עבור (i = 0; i < af->nb_buffers; i++) {
        אם (av_fifo_read(af->buf[i], data[i], size) < 0)
            החזר AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    החזר nb_samples;
}

صحيح av_audio_fifo_drain(AVAudioFifo *af, صحيح nb_samples)
{
    صحيح i, size;

    אם (nb_samples < 0)
        החזר AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    אם (nb_samples) {
        size = nb_samples * af->sample_size;
        עבור (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    החזר 0;
}

فراغ av_audio_fifo_reset(AVAudioFifo *af)
{
    صحيح i;

    עבור (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

صحيح av_audio_fifo_size(AVAudioFifo *af)
{
    החזר af->nb_samples;
}

صحيح av_audio_fifo_space(AVAudioFifo *af)
{
    החזר af->allocated_samples - af->nb_samples;
}
