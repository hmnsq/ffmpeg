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

#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <stddef.h>

#അന്തര്ഭാവ "audio_fifo.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "fifo.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "samplefmt.h"

ഘടന AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    പൂർണ്ണസംഖ്യ nb_buffers;                 /**< number of buffers */
    പൂർണ്ണസംഖ്യ nb_samples;                 /**< number of samples currently in the FIFO */
    പൂർണ്ണസംഖ്യ allocated_samples;          /**< current allocated size, in samples */

    പൂർണ്ണസംഖ്യ channels;                   /**< number of channels */
    എണ്ണൽ AVSampleFormat sample_fmt; /**< sample format */
    പൂർണ്ണസംഖ്യ sample_size;                /**< size, in bytes, of one sample in a buffer */
};

ശൂന്യം av_audio_fifo_free(AVAudioFifo *af)
{
    എങ്കിൽ (af) {
        എങ്കിൽ (af->buf) {
            പൂർണ്ണസംഖ്യ i;
            വേണ്ടി (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(എണ്ണൽ AVSampleFormat sample_fmt, പൂർണ്ണസംഖ്യ channels,
                                 പൂർണ്ണസംഖ്യ nb_samples)
{
    AVAudioFifo *af;
    പൂർണ്ണസംഖ്യ buf_size, i;

    /* get channel buffer size (also validates parameters) */
    എങ്കിൽ (av_samples_get_buffer_size(&buf_size, channels, nb_samples, sample_fmt, 1) < 0)
        തിരികെ ശൂന്യ;

    af = av_mallocz(വലുപ്പം(*af));
    എങ്കിൽ (!af)
        തിരികെ ശൂന്യ;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_size = buf_size / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, വലുപ്പം(*af->buf));
    എങ്കിൽ (!af->buf)
        പോകുക error;

    വേണ്ടി (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_size, 1, 0);
        എങ്കിൽ (!af->buf[i])
            പോകുക error;
    }
    af->allocated_samples = nb_samples;

    തിരികെ af;

error:
    av_audio_fifo_free(af);
    തിരികെ ശൂന്യ;
}

പൂർണ്ണസംഖ്യ av_audio_fifo_realloc(AVAudioFifo *af, പൂർണ്ണസംഖ്യ nb_samples)
{
    സ്ഥിരം size_t cur_size = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    പൂർണ്ണസംഖ്യ i, ret, buf_size;

    എങ്കിൽ ((ret = av_samples_get_buffer_size(&buf_size, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        തിരികെ ret;

    എങ്കിൽ (buf_size > cur_size) {
        വേണ്ടി (i = 0; i < af->nb_buffers; i++) {
            എങ്കിൽ ((ret = av_fifo_grow2(af->buf[i], buf_size - cur_size)) < 0)
                തിരികെ ret;
        }
    }
    af->allocated_samples = nb_samples;
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_audio_fifo_write(AVAudioFifo *af, ശൂന്യം * സ്ഥിരം *data, പൂർണ്ണസംഖ്യ nb_samples)
{
    പൂർണ്ണസംഖ്യ i, ret, size;

    /* automatically reallocate buffers if needed */
    എങ്കിൽ (av_audio_fifo_space(af) < nb_samples) {
        പൂർണ്ണസംഖ്യ current_size = av_audio_fifo_size(af);
        /* check for integer overflow in new size calculation */
        എങ്കിൽ (INT_MAX / 2 - current_size < nb_samples)
            തിരികെ AVERROR(EINVAL);
        /* reallocate buffers */
        എങ്കിൽ ((ret = av_audio_fifo_realloc(af, 2 * (current_size + nb_samples))) < 0)
            തിരികെ ret;
    }

    size = nb_samples * af->sample_size;
    വേണ്ടി (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], data[i], size);
        എങ്കിൽ (ret < 0)
            തിരികെ AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    തിരികെ nb_samples;
}

പൂർണ്ണസംഖ്യ av_audio_fifo_peek(സ്ഥിരം AVAudioFifo *af, ശൂന്യം * സ്ഥിരം *data, പൂർണ്ണസംഖ്യ nb_samples)
{
    തിരികെ av_audio_fifo_peek_at(af, data, nb_samples, 0);
}

പൂർണ്ണസംഖ്യ av_audio_fifo_peek_at(സ്ഥിരം AVAudioFifo *af, ശൂന്യം * സ്ഥിരം *data,
                          പൂർണ്ണസംഖ്യ nb_samples, പൂർണ്ണസംഖ്യ offset)
{
    പൂർണ്ണസംഖ്യ i, ret, size;

    എങ്കിൽ (offset < 0 || offset >= af->nb_samples)
        തിരികെ AVERROR(EINVAL);
    എങ്കിൽ (nb_samples < 0)
        തിരികെ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    എങ്കിൽ (!nb_samples)
        തിരികെ 0;
    എങ്കിൽ (offset > af->nb_samples - nb_samples)
        തിരികെ AVERROR(EINVAL);

    offset *= af->sample_size;
    size = nb_samples * af->sample_size;
    വേണ്ടി (i = 0; i < af->nb_buffers; i++) {
        എങ്കിൽ ((ret = av_fifo_peek(af->buf[i], data[i], size, offset)) < 0)
            തിരികെ AVERROR_BUG;
    }

    തിരികെ nb_samples;
}

പൂർണ്ണസംഖ്യ av_audio_fifo_read(AVAudioFifo *af, ശൂന്യം * സ്ഥിരം *data, പൂർണ്ണസംഖ്യ nb_samples)
{
    പൂർണ്ണസംഖ്യ i, size;

    എങ്കിൽ (nb_samples < 0)
        തിരികെ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    എങ്കിൽ (!nb_samples)
        തിരികെ 0;

    size = nb_samples * af->sample_size;
    വേണ്ടി (i = 0; i < af->nb_buffers; i++) {
        എങ്കിൽ (av_fifo_read(af->buf[i], data[i], size) < 0)
            തിരികെ AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    തിരികെ nb_samples;
}

പൂർണ്ണസംഖ്യ av_audio_fifo_drain(AVAudioFifo *af, പൂർണ്ണസംഖ്യ nb_samples)
{
    പൂർണ്ണസംഖ്യ i, size;

    എങ്കിൽ (nb_samples < 0)
        തിരികെ AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    എങ്കിൽ (nb_samples) {
        size = nb_samples * af->sample_size;
        വേണ്ടി (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], size);
        af->nb_samples -= nb_samples;
    }
    തിരികെ 0;
}

ശൂന്യം av_audio_fifo_reset(AVAudioFifo *af)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

പൂർണ്ണസംഖ്യ av_audio_fifo_size(AVAudioFifo *af)
{
    തിരികെ af->nb_samples;
}

പൂർണ്ണസംഖ്യ av_audio_fifo_space(AVAudioFifo *af)
{
    തിരികെ af->allocated_samples - af->nb_samples;
}
