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

#include <limits.h>
#include <stddef.h>

#include "audio_fifo.h"
#include "error.h"
#include "fifo.h"
#include "macros.h"
#include "mem.h"
#include "samplefmt.h"

sa_nracanaa AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    පූර්ණ_සංඛ්‍යා nb_buffers;                 /**< number of buffers */
    පූර්ණ_සංඛ්‍යා nb_samples;                 /**< number of samples currently in the FIFO */
    පූර්ණ_සංඛ්‍යා allocated_samples;          /**< current allocated size, in samples */

    පූර්ණ_සංඛ්‍යා channels;                   /**< number of channels */
    ga_nanaa AVSampleFormat sample_fmt; /**< sample format */
    පූර්ණ_සංඛ්‍යා sample_size;                /**< size, in bytes, of one sample in a buffer */
};

void av_audio_fifo_free(AVAudioFifo *af)
{
    නම් (af) {
        නම් (af->buf) {
            පූර්ණ_සංඛ්‍යා i;
            සඳහා (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(ga_nanaa AVSampleFormat sample_fmt, පූර්ණ_සංඛ්‍යා channels,
                                 පූර්ණ_සංඛ්‍යා nb_samples)
{
    AVAudioFifo *af;
    පූර්ණ_සංඛ්‍යා buf_size, i;

    /* get channel buffer size (also validates parameters) */
    නම් (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        ආපසු NULL;

    af = av_mallocz(parimaa_na(*af));
    නම් (!af)
        ආපසු NULL;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, parimaa_na(*af->buf));
    නම් (!af->buf)
        goto error;

    සඳහා (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        නම් (!af->buf[i])
            goto error;
    }
    af->allocated_samples = nb_samples;

    ආපසු af;

error:
    av_audio_fifo_free(af);
    ආපසු NULL;
}

පූර්ණ_සංඛ්‍යා av_audio_fifo_realloc(AVAudioFifo *af, පූර්ණ_සංඛ්‍යා nb_samples)
{
    const size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    පූර්ණ_සංඛ්‍යා i, ret, buf_size;

    නම් ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        ආපසු ret;

    නම් (buf_size > cur_size) {
        සඳහා (i = 0; i < af->nb_buffers; i++) {
            නම් ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                ආපසු ret;
        }
    }
    af->allocated_samples = nb_samples;
    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_audio_fifo_write(AVAudioFifo *af, void * const *data, පූර්ණ_සංඛ්‍යා nb_samples)
{
    පූර්ණ_සංඛ්‍යා i, ret, size;

    /* automatically reallocate buffers if needed */
    නම් (av_audio_fifo_space(af) < nb_samples) {
        පූර්ණ_සංඛ්‍යා current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        නම් (INT_MAX / 2 - current_size < nb_samples)
            ආපසු AVERROR(EINVAL);
        /* reallocate buffers */
        නම් ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            ආපසු ret;
    }

    size = nb_samples * af->sample_size;
    සඳහා (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        නම් (ret < 0)
            ආපසු AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    ආපසු nb_samples;
}

පූර්ණ_සංඛ්‍යා av_audio_fifo_peek(const AVAudioFifo *af, void * const *data, පූර්ණ_සංඛ්‍යා nb_samples)
{
    ආපසු av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

පූර්ණ_සංඛ්‍යා av_audio_fifo_peek_at(const AVAudioFifo *af, void * const *data,
                          පූර්ණ_සංඛ්‍යා nb_samples, පූර්ණ_සංඛ්‍යා offset)
{
    පූර්ණ_සංඛ්‍යා i, ret, size;

    නම් (offset < 0 || offset >= af->nb_samples)
        ආපසු AVERROR(EINVAL);
    නම් (nb_samples < 0)
        ආපසු AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    නම් (!nb_samples)
        ආපසු 0;
    නම් (offset > af->nb_samples - nb_samples)
        ආපසු AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    සඳහා (i = 0; i < af->nb_buffers; i++) {
        නම් ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            ආපසු AVERROR_BUG;
    }

    ආපසු nb_samples;
}

පූර්ණ_සංඛ්‍යා av_audio_fifo_read(AVAudioFifo *af, void * const *data, පූර්ණ_සංඛ්‍යා nb_samples)
{
    පූර්ණ_සංඛ්‍යා i, size;

    නම් (nb_samples < 0)
        ආපසු AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    නම් (!nb_samples)
        ආපසු 0;

    size = nb_samples * af->sample_size;
    සඳහා (i = 0; i < af->nb_buffers; i++) {
        නම් (av_fifo_read(af->buf[i], data[i], size) < 0)
            ආපසු AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    ආපසු nb_samples;
}

පූර්ණ_සංඛ්‍යා av_audio_fifo_drain(AVAudioFifo *af, පූර්ණ_සංඛ්‍යා nb_samples)
{
    පූර්ණ_සංඛ්‍යා i, size;

    නම් (nb_samples < 0)
        ආපසු AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    නම් (nb_samples) {
        size = nb_samples * af->sample_size;
        සඳහා (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    ආපසු 0;
}

void av_audio_fifo_reset(AVAudioFifo *af)
{
    පූර්ණ_සංඛ්‍යා i;

    සඳහා (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

පූර්ණ_සංඛ්‍යා av_audio_fifo_size(AVAudioFifo *af)
{
    ආපසු af->nb_samples;
}

පූර්ණ_සංඛ්‍යා av_audio_fifo_space(AVAudioFifo *af)
{
    ආපසු af->allocated_samples - af->nb_samples;
}
