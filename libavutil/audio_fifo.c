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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stddef.h>

#అన్తర్భావ "audio_fifo.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "fifo.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "samplefmt.h"

నిర్మాణం AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    పూర్ణాంకం nb_buffers;                 /**< number of buffers */
    పూర్ణాంకం nb_samples;                 /**< number of samples currently in the FIFO */
    పూర్ణాంకం allocated_samples;          /**< current allocated size, in samples */

    పూర్ణాంకం channels;                   /**< number of channels */
    గణన AVSampleFormat sample_fmt; /**< sample format */
    పూర్ణాంకం sample_కొలత;                /**< size, in bytes, of one sample in a buffer */
};

శూన్య av_audio_fifo_free(AVAudioFifo *af)
{
    ఒకవేళ (af) {
        ఒకవేళ (af->buf) {
            పూర్ణాంకం i;
            కొరకు (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(గణన AVSampleFormat sample_fmt, పూర్ణాంకం channels,
                                 పూర్ణాంకం nb_samples)
{
    AVAudioFifo *af;
    పూర్ణాంకం buf_కొలత, i;

    /* get channel buffer size (also validates parameters) */
    ఒకవేళ (av_samples_get_బఫరు_కొలత(&buf_కొలత, channels, nb_samples, sample_fmt, 1) < 0)
        తిరిగి ఖాళీ;

    af = av_mallocz(పరిమాణం(*af));
    ఒకవేళ (!af)
        తిరిగి ఖాళీ;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_కొలత = buf_కొలత / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, పరిమాణం(*af->buf));
    ఒకవేళ (!af->buf)
        వెళ్ళు error;

    కొరకు (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_కొలత, 1, 0);
        ఒకవేళ (!af->buf[i])
            వెళ్ళు error;
    }
    af->allocated_samples = nb_samples;

    తిరిగి af;

error:
    av_audio_fifo_free(af);
    తిరిగి ఖాళీ;
}

పూర్ణాంకం av_audio_fifo_realloc(AVAudioFifo *af, పూర్ణాంకం nb_samples)
{
    స్థిరరాశి size_t cur_కొలత = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    పూర్ణాంకం i, ret, buf_కొలత;

    ఒకవేళ ((ret = av_samples_get_బఫరు_కొలత(&buf_కొలత, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        తిరిగి ret;

    ఒకవేళ (buf_కొలత > cur_కొలత) {
        కొరకు (i = 0; i < af->nb_buffers; i++) {
            ఒకవేళ ((ret = av_fifo_grow2(af->buf[i], buf_కొలత - cur_కొలత)) < 0)
                తిరిగి ret;
        }
    }
    af->allocated_samples = nb_samples;
    తిరిగి 0;
}

పూర్ణాంకం av_audio_fifo_write(AVAudioFifo *af, శూన్య * స్థిరరాశి *దత్తాంశం, పూర్ణాంకం nb_samples)
{
    పూర్ణాంకం i, ret, కొలత;

    /* automatically reallocate buffers if needed */
    ఒకవేళ (av_audio_fifo_space(af) < nb_samples) {
        పూర్ణాంకం current_కొలత = av_audio_fifo_కొలత(af);
        /* check for integer overflow in new size calculation */
        ఒకవేళ (గరిష్ఠ_పూర్ణాంకం / 2 - current_కొలత < nb_samples)
            తిరిగి AVERROR(EINVAL);
        /* reallocate buffers */
        ఒకవేళ ((ret = av_audio_fifo_realloc(af, 2 * (current_కొలత + nb_samples))) < 0)
            తిరిగి ret;
    }

    కొలత = nb_samples * af->sample_కొలత;
    కొరకు (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], దత్తాంశం[i], కొలత);
        ఒకవేళ (ret < 0)
            తిరిగి AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    తిరిగి nb_samples;
}

పూర్ణాంకం av_audio_fifo_peek(స్థిరరాశి AVAudioFifo *af, శూన్య * స్థిరరాశి *దత్తాంశం, పూర్ణాంకం nb_samples)
{
    తిరిగి av_audio_fifo_peek_at(af, దత్తాంశం, nb_samples, 0);
}

పూర్ణాంకం av_audio_fifo_peek_at(స్థిరరాశి AVAudioFifo *af, శూన్య * స్థిరరాశి *దత్తాంశం,
                          పూర్ణాంకం nb_samples, పూర్ణాంకం స్థానభ్రంశం)
{
    పూర్ణాంకం i, ret, కొలత;

    ఒకవేళ (స్థానభ్రంశం < 0 || స్థానభ్రంశం >= af->nb_samples)
        తిరిగి AVERROR(EINVAL);
    ఒకవేళ (nb_samples < 0)
        తిరిగి AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ఒకవేళ (!nb_samples)
        తిరిగి 0;
    ఒకవేళ (స్థానభ్రంశం > af->nb_samples - nb_samples)
        తిరిగి AVERROR(EINVAL);

    స్థానభ్రంశం *= af->sample_కొలత;
    కొలత = nb_samples * af->sample_కొలత;
    కొరకు (i = 0; i < af->nb_buffers; i++) {
        ఒకవేళ ((ret = av_fifo_peek(af->buf[i], దత్తాంశం[i], కొలత, స్థానభ్రంశం)) < 0)
            తిరిగి AVERROR_BUG;
    }

    తిరిగి nb_samples;
}

పూర్ణాంకం av_audio_fifo_read(AVAudioFifo *af, శూన్య * స్థిరరాశి *దత్తాంశం, పూర్ణాంకం nb_samples)
{
    పూర్ణాంకం i, కొలత;

    ఒకవేళ (nb_samples < 0)
        తిరిగి AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    ఒకవేళ (!nb_samples)
        తిరిగి 0;

    కొలత = nb_samples * af->sample_కొలత;
    కొరకు (i = 0; i < af->nb_buffers; i++) {
        ఒకవేళ (av_fifo_read(af->buf[i], దత్తాంశం[i], కొలత) < 0)
            తిరిగి AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    తిరిగి nb_samples;
}

పూర్ణాంకం av_audio_fifo_drain(AVAudioFifo *af, పూర్ణాంకం nb_samples)
{
    పూర్ణాంకం i, కొలత;

    ఒకవేళ (nb_samples < 0)
        తిరిగి AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    ఒకవేళ (nb_samples) {
        కొలత = nb_samples * af->sample_కొలత;
        కొరకు (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], కొలత);
        af->nb_samples -= nb_samples;
    }
    తిరిగి 0;
}

శూన్య av_audio_fifo_reset(AVAudioFifo *af)
{
    పూర్ణాంకం i;

    కొరకు (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

పూర్ణాంకం av_audio_fifo_కొలత(AVAudioFifo *af)
{
    తిరిగి af->nb_samples;
}

పూర్ణాంకం av_audio_fifo_space(AVAudioFifo *af)
{
    తిరిగి af->allocated_samples - af->nb_samples;
}
