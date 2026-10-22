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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stddef.h>

#अन्तर्भाव "audio_fifo.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "fifo.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "samplefmt.h"

संरचना AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    पूर्णाङ्क nb_buffers;                 /**< number of buffers */
    पूर्णाङ्क nb_samples;                 /**< number of samples currently in the FIFO */
    पूर्णाङ्क allocated_samples;          /**< current allocated size, in samples */

    पूर्णाङ्क channels;                   /**< number of channels */
    गणना AVSampleFormat sample_fmt; /**< sample format */
    पूर्णाङ्क sample_size;                /**< size, in bytes, of one sample in a buffer */
};

शून्य av_audio_fifo_free(AVAudioFifo *af)
{
    यदि (af) {
        यदि (af->buf) {
            पूर्णाङ्क i;
            लागि (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(गणना AVSampleFormat sample_fmt, पूर्णाङ्क channels,
                                 पूर्णाङ्क nb_samples)
{
    AVAudioFifo *af;
    पूर्णाङ्क buf_size, i;

    /* get channel buffer size (also validates parameters) */
    यदि (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        फर्काऊ रिक्त;

    af = av_mallocz(परिमाण(*af));
    यदि (!af)
        फर्काऊ रिक्त;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, परिमाण(*af->buf));
    यदि (!af->buf)
        गच्छ error;

    लागि (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        यदि (!af->buf[i])
            गच्छ error;
    }
    af->allocated_samples = nb_samples;

    फर्काऊ af;

error:
    av_audio_fifo_free(af);
    फर्काऊ रिक्त;
}

पूर्णाङ्क av_audio_fifo_realloc(AVAudioFifo *af, पूर्णाङ्क nb_samples)
{
    अचर माप_प्रकार cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    पूर्णाङ्क i, ret, buf_size;

    यदि ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        फर्काऊ ret;

    यदि (buf_size > cur_size) {
        लागि (i = 0; i < af->nb_buffers; i++) {
            यदि ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                फर्काऊ ret;
        }
    }
    af->allocated_samples = nb_samples;
    फर्काऊ 0;
}

पूर्णाङ्क av_audio_fifo_write(AVAudioFifo *af, शून्य * अचर *data, पूर्णाङ्क nb_samples)
{
    पूर्णाङ्क i, ret, size;

    /* automatically reallocate buffers if needed */
    यदि (av_audio_fifo_space(af) < nb_samples) {
        पूर्णाङ्क current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        यदि (पूर्णांक_उच्च / 2 - current_size < nb_samples)
            फर्काऊ AVERROR(EINVAL);
        /* reallocate buffers */
        यदि ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            फर्काऊ ret;
    }

    size = nb_samples * af->sample_size;
    लागि (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        यदि (ret < 0)
            फर्काऊ AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    फर्काऊ nb_samples;
}

पूर्णाङ्क av_audio_fifo_peek(अचर AVAudioFifo *af, शून्य * अचर *data, पूर्णाङ्क nb_samples)
{
    फर्काऊ av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

पूर्णाङ्क av_audio_fifo_peek_at(अचर AVAudioFifo *af, शून्य * अचर *data,
                          पूर्णाङ्क nb_samples, पूर्णाङ्क offset)
{
    पूर्णाङ्क i, ret, size;

    यदि (offset < 0 || offset >= af->nb_samples)
        फर्काऊ AVERROR(EINVAL);
    यदि (nb_samples < 0)
        फर्काऊ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    यदि (!nb_samples)
        फर्काऊ 0;
    यदि (offset > af->nb_samples - nb_samples)
        फर्काऊ AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    लागि (i = 0; i < af->nb_buffers; i++) {
        यदि ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            फर्काऊ AVERROR_BUG;
    }

    फर्काऊ nb_samples;
}

पूर्णाङ्क av_audio_fifo_read(AVAudioFifo *af, शून्य * अचर *data, पूर्णाङ्क nb_samples)
{
    पूर्णाङ्क i, size;

    यदि (nb_samples < 0)
        फर्काऊ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    यदि (!nb_samples)
        फर्काऊ 0;

    size = nb_samples * af->sample_size;
    लागि (i = 0; i < af->nb_buffers; i++) {
        यदि (av_fifo_read(af->buf[i], data[i], size) < 0)
            फर्काऊ AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    फर्काऊ nb_samples;
}

पूर्णाङ्क av_audio_fifo_drain(AVAudioFifo *af, पूर्णाङ्क nb_samples)
{
    पूर्णाङ्क i, size;

    यदि (nb_samples < 0)
        फर्काऊ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    यदि (nb_samples) {
        size = nb_samples * af->sample_size;
        लागि (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    फर्काऊ 0;
}

शून्य av_audio_fifo_reset(AVAudioFifo *af)
{
    पूर्णाङ्क i;

    लागि (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

पूर्णाङ्क av_audio_fifo_size(AVAudioFifo *af)
{
    फर्काऊ af->nb_samples;
}

पूर्णाङ्क av_audio_fifo_space(AVAudioFifo *af)
{
    फर्काऊ af->allocated_samples - af->nb_samples;
}
