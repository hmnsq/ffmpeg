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

#समावेश <limits.h>
#समावेश <stddef.h>

#समावेश "audio_fifo.h"
#समावेश "error.h"
#समावेश "fifo.h"
#समावेश "macros.h"
#समावेश "mem.h"
#समावेश "samplefmt.h"

काष्ठा AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    पूर्णांक nb_buffers;                 /**< number of buffers */
    पूर्णांक nb_samples;                 /**< number of samples currently in the FIFO */
    पूर्णांक allocated_samples;          /**< current allocated size, in samples */

    पूर्णांक channels;                   /**< number of channels */
    क्रमागत AVSampleFormat sample_fmt; /**< sample format */
    पूर्णांक sample_आकार;                /**< size, in bytes, of one sample in a buffer */
};

व्योम av_audio_fifo_free(AVAudioFifo *af)
{
    अगर (af) {
        अगर (af->buf) {
            पूर्णांक i;
            क्रम (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(क्रमागत AVSampleFormat sample_fmt, पूर्णांक channels,
                                 पूर्णांक nb_samples)
{
    AVAudioFifo *af;
    पूर्णांक buf_आकार, i;

    /* get channel buffer size (also validates parameters) */
    अगर (av_samples_get_बफर_आकार(&buf_आकार, channels, nb_samples, sample_fmt, 1) < 0)
        वापस शून्य;

    af = av_mallocz(माप(*af));
    अगर (!af)
        वापस शून्य;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_आकार = buf_आकार / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, माप(*af->buf));
    अगर (!af->buf)
        जाओ error;

    क्रम (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_आकार, 1, 0);
        अगर (!af->buf[i])
            जाओ error;
    }
    af->allocated_samples = nb_samples;

    वापस af;

error:
    av_audio_fifo_free(af);
    वापस शून्य;
}

पूर्णांक av_audio_fifo_realloc(AVAudioFifo *af, पूर्णांक nb_samples)
{
    स्थिर माप_प्रकार cur_आकार = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    पूर्णांक i, ret, buf_आकार;

    अगर ((ret = av_samples_get_बफर_आकार(&buf_आकार, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        वापस ret;

    अगर (buf_आकार > cur_आकार) {
        क्रम (i = 0; i < af->nb_buffers; i++) {
            अगर ((ret = av_fifo_grow2(af->buf[i], buf_आकार - cur_आकार)) < 0)
                वापस ret;
        }
    }
    af->allocated_samples = nb_samples;
    वापस 0;
}

पूर्णांक av_audio_fifo_write(AVAudioFifo *af, व्योम * स्थिर *तथ्य, पूर्णांक nb_samples)
{
    पूर्णांक i, ret, आकार;

    /* automatically reallocate buffers if needed */
    अगर (av_audio_fifo_space(af) < nb_samples) {
        पूर्णांक current_आकार = av_audio_fifo_आकार(af);
        /* check for integer overflow in new size calculation */
        अगर (पूर्णांक_उच्च / 2 - current_आकार < nb_samples)
            वापस AVERROR(EINVAL);
        /* reallocate buffers */
        अगर ((ret = av_audio_fifo_realloc(af, 2 * (current_आकार + nb_samples))) < 0)
            वापस ret;
    }

    आकार = nb_samples * af->sample_आकार;
    क्रम (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], तथ्य[i], आकार);
        अगर (ret < 0)
            वापस AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    वापस nb_samples;
}

पूर्णांक av_audio_fifo_peek(स्थिर AVAudioFifo *af, व्योम * स्थिर *तथ्य, पूर्णांक nb_samples)
{
    वापस av_audio_fifo_peek_at(af, तथ्य, nb_samples, 0);
}

पूर्णांक av_audio_fifo_peek_at(स्थिर AVAudioFifo *af, व्योम * स्थिर *तथ्य,
                          पूर्णांक nb_samples, पूर्णांक offset)
{
    पूर्णांक i, ret, आकार;

    अगर (offset < 0 || offset >= af->nb_samples)
        वापस AVERROR(EINVAL);
    अगर (nb_samples < 0)
        वापस AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    अगर (!nb_samples)
        वापस 0;
    अगर (offset > af->nb_samples - nb_samples)
        वापस AVERROR(EINVAL);

    offset *= af->sample_आकार;
    आकार = nb_samples * af->sample_आकार;
    क्रम (i = 0; i < af->nb_buffers; i++) {
        अगर ((ret = av_fifo_peek(af->buf[i], तथ्य[i], आकार, offset)) < 0)
            वापस AVERROR_BUG;
    }

    वापस nb_samples;
}

पूर्णांक av_audio_fifo_read(AVAudioFifo *af, व्योम * स्थिर *तथ्य, पूर्णांक nb_samples)
{
    पूर्णांक i, आकार;

    अगर (nb_samples < 0)
        वापस AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    अगर (!nb_samples)
        वापस 0;

    आकार = nb_samples * af->sample_आकार;
    क्रम (i = 0; i < af->nb_buffers; i++) {
        अगर (av_fifo_read(af->buf[i], तथ्य[i], आकार) < 0)
            वापस AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    वापस nb_samples;
}

पूर्णांक av_audio_fifo_drain(AVAudioFifo *af, पूर्णांक nb_samples)
{
    पूर्णांक i, आकार;

    अगर (nb_samples < 0)
        वापस AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    अगर (nb_samples) {
        आकार = nb_samples * af->sample_आकार;
        क्रम (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], आकार);
        af->nb_samples -= nb_samples;
    }
    वापस 0;
}

व्योम av_audio_fifo_reset(AVAudioFifo *af)
{
    पूर्णांक i;

    क्रम (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

पूर्णांक av_audio_fifo_आकार(AVAudioFifo *af)
{
    वापस af->nb_samples;
}

पूर्णांक av_audio_fifo_space(AVAudioFifo *af)
{
    वापस af->allocated_samples - af->nb_samples;
}
