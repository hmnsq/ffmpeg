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
    ကိန်းပြည့် nb_buffers;                 /**< number of buffers */
    ကိန်းပြည့် nb_samples;                 /**< number of samples currently in the FIFO */
    ကိန်းပြည့် allocated_samples;          /**< current allocated size, in samples */

    ကိန်းပြည့် channels;                   /**< number of channels */
    ga_nanaa AVSampleFormat sample_fmt; /**< sample format */
    ကိန်းပြည့် sample_size;                /**< size, in bytes, of one sample in a buffer */
};

void av_audio_fifo_free(AVAudioFifo *af)
{
    အကယ်၍ (af) {
        အကယ်၍ (af->buf) {
            ကိန်းပြည့် i;
            အတွက် (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(ga_nanaa AVSampleFormat sample_fmt, ကိန်းပြည့် channels,
                                 ကိန်းပြည့် nb_samples)
{
    AVAudioFifo *af;
    ကိန်းပြည့် buf_size, i;

    /* get channel buffer size (also validates parameters) */
    အကယ်၍ (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        ပြန်ပေး NULL;

    af = av_mallocz(parimaa_na(*af));
    အကယ်၍ (!af)
        ပြန်ပေး NULL;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, parimaa_na(*af->buf));
    အကယ်၍ (!af->buf)
        goto error;

    အတွက် (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        အကယ်၍ (!af->buf[i])
            goto error;
    }
    af->allocated_samples = nb_samples;

    ပြန်ပေး af;

error:
    av_audio_fifo_free(af);
    ပြန်ပေး NULL;
}

ကိန်းပြည့် av_audio_fifo_realloc(AVAudioFifo *af, ကိန်းပြည့် nb_samples)
{
    const size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    ကိန်းပြည့် i, ret, buf_size;

    အကယ်၍ ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        ပြန်ပေး ret;

    အကယ်၍ (buf_size > cur_size) {
        အတွက် (i = 0; i < af->nb_buffers; i++) {
            အကယ်၍ ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                ပြန်ပေး ret;
        }
    }
    af->allocated_samples = nb_samples;
    ပြန်ပေး 0;
}

ကိန်းပြည့် av_audio_fifo_write(AVAudioFifo *af, void * const *data, ကိန်းပြည့် nb_samples)
{
    ကိန်းပြည့် i, ret, size;

    /* automatically reallocate buffers if needed */
    အကယ်၍ (av_audio_fifo_space(af) < nb_samples) {
        ကိန်းပြည့် current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        အကယ်၍ (INT_MAX / 2 - current_size < nb_samples)
            ပြန်ပေး AVERROR(EINVAL);
        /* reallocate buffers */
        အကယ်၍ ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            ပြန်ပေး ret;
    }

    size = nb_samples * af->sample_size;
    အတွက် (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        အကယ်၍ (ret < 0)
            ပြန်ပေး AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    ပြန်ပေး nb_samples;
}

ကိန်းပြည့် av_audio_fifo_peek(const AVAudioFifo *af, void * const *data, ကိန်းပြည့် nb_samples)
{
    ပြန်ပေး av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

ကိန်းပြည့် av_audio_fifo_peek_at(const AVAudioFifo *af, void * const *data,
                          ကိန်းပြည့် nb_samples, ကိန်းပြည့် offset)
{
    ကိန်းပြည့် i, ret, size;

    အကယ်၍ (offset < 0 || offset >= af->nb_samples)
        ပြန်ပေး AVERROR(EINVAL);
    အကယ်၍ (nb_samples < 0)
        ပြန်ပေး AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    အကယ်၍ (!nb_samples)
        ပြန်ပေး 0;
    အကယ်၍ (offset > af->nb_samples - nb_samples)
        ပြန်ပေး AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    အတွက် (i = 0; i < af->nb_buffers; i++) {
        အကယ်၍ ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            ပြန်ပေး AVERROR_BUG;
    }

    ပြန်ပေး nb_samples;
}

ကိန်းပြည့် av_audio_fifo_read(AVAudioFifo *af, void * const *data, ကိန်းပြည့် nb_samples)
{
    ကိန်းပြည့် i, size;

    အကယ်၍ (nb_samples < 0)
        ပြန်ပေး AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    အကယ်၍ (!nb_samples)
        ပြန်ပေး 0;

    size = nb_samples * af->sample_size;
    အတွက် (i = 0; i < af->nb_buffers; i++) {
        အကယ်၍ (av_fifo_read(af->buf[i], data[i], size) < 0)
            ပြန်ပေး AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    ပြန်ပေး nb_samples;
}

ကိန်းပြည့် av_audio_fifo_drain(AVAudioFifo *af, ကိန်းပြည့် nb_samples)
{
    ကိန်းပြည့် i, size;

    အကယ်၍ (nb_samples < 0)
        ပြန်ပေး AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    အကယ်၍ (nb_samples) {
        size = nb_samples * af->sample_size;
        အတွက် (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    ပြန်ပေး 0;
}

void av_audio_fifo_reset(AVAudioFifo *af)
{
    ကိန်းပြည့် i;

    အတွက် (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

ကိန်းပြည့် av_audio_fifo_size(AVAudioFifo *af)
{
    ပြန်ပေး af->nb_samples;
}

ကိန်းပြည့် av_audio_fifo_space(AVAudioFifo *af)
{
    ပြန်ပေး af->allocated_samples - af->nb_samples;
}
