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

ساخت AVAudioFifo {
    AVFifo **buf;                   /**< single buffer for interleaved, per-channel buffers for planar */
    صحیح nb_buffers;                 /**< number of buffers */
    صحیح nb_samples;                 /**< number of samples currently in the FIFO */
    صحیح allocated_samples;          /**< current allocated size, in samples */

    صحیح channels;                   /**< number of channels */
    شمار AVSampleFormat sample_fmt; /**< sample format */
    صحیح sample_سائز;                /**< size, in bytes, of one sample in a buffer */
};

خالی av_audio_fifo_free(AVAudioFifo *af)
{
    اگر (af) {
        اگر (af->buf) {
            صحیح i;
            برائے (i = 0; i < af->nb_buffers; i++) {
                av_fifo_freep2(&af->buf[i]);
            }
            av_freep(&af->buf);
        }
        av_free(af);
    }
}

AVAudioFifo *av_audio_fifo_alloc(شمار AVSampleFormat sample_fmt, صحیح channels,
                                 صحیح nb_samples)
{
    AVAudioFifo *af;
    صحیح buf_سائز, i;

    /* get channel buffer size (also validates parameters) */
    اگر (av_samples_get_بفر_سائز(&buf_سائز, channels, nb_samples, sample_fmt, 1) < 0)
        واپس تہی;

    af = av_mallocz(حجم(*af));
    اگر (!af)
        واپس تہی;

    af->channels    = channels;
    af->sample_fmt  = sample_fmt;
    af->sample_سائز = buf_سائز / nb_samples;
    af->nb_buffers  = av_sample_fmt_is_planar(sample_fmt) ? channels : 1;

    af->buf = av_calloc(af->nb_buffers, حجم(*af->buf));
    اگر (!af->buf)
        جاؤ error;

    برائے (i = 0; i < af->nb_buffers; i++) {
        af->buf[i] = av_fifo_alloc2(buf_سائز, 1, 0);
        اگر (!af->buf[i])
            جاؤ error;
    }
    af->allocated_samples = nb_samples;

    واپس af;

error:
    av_audio_fifo_free(af);
    واپس تہی;
}

صحیح av_audio_fifo_realloc(AVAudioFifo *af, صحیح nb_samples)
{
    ثابت size_t cur_سائز = av_fifo_can_read (af->buf[0]) +
                            av_fifo_can_write(af->buf[0]);
    صحیح i, ret, buf_سائز;

    اگر ((ret = av_samples_get_بفر_سائز(&buf_سائز, af->channels, nb_samples,
                                          af->sample_fmt, 1)) < 0)
        واپس ret;

    اگر (buf_سائز > cur_سائز) {
        برائے (i = 0; i < af->nb_buffers; i++) {
            اگر ((ret = av_fifo_grow2(af->buf[i], buf_سائز - cur_سائز)) < 0)
                واپس ret;
        }
    }
    af->allocated_samples = nb_samples;
    واپس 0;
}

صحیح av_audio_fifo_write(AVAudioFifo *af, خالی * ثابت *ڈیٹا, صحیح nb_samples)
{
    صحیح i, ret, سائز;

    /* automatically reallocate buffers if needed */
    اگر (av_audio_fifo_space(af) < nb_samples) {
        صحیح current_سائز = av_audio_fifo_سائز(af);
        /* check for integer overflow in new size calculation */
        اگر (زیادہ_سے_زیادہ_عدد / 2 - current_سائز < nb_samples)
            واپس AVERROR(EINVAL);
        /* reallocate buffers */
        اگر ((ret = av_audio_fifo_realloc(af, 2 * (current_سائز + nb_samples))) < 0)
            واپس ret;
    }

    سائز = nb_samples * af->sample_سائز;
    برائے (i = 0; i < af->nb_buffers; i++) {
        ret = av_fifo_write(af->buf[i], ڈیٹا[i], سائز);
        اگر (ret < 0)
            واپس AVERROR_BUG;
    }
    af->nb_samples += nb_samples;

    واپس nb_samples;
}

صحیح av_audio_fifo_peek(ثابت AVAudioFifo *af, خالی * ثابت *ڈیٹا, صحیح nb_samples)
{
    واپس av_audio_fifo_peek_at(af, ڈیٹا, nb_samples, 0);
}

صحیح av_audio_fifo_peek_at(ثابت AVAudioFifo *af, خالی * ثابت *ڈیٹا,
                          صحیح nb_samples, صحیح انحراف)
{
    صحیح i, ret, سائز;

    اگر (انحراف < 0 || انحراف >= af->nb_samples)
        واپس AVERROR(EINVAL);
    اگر (nb_samples < 0)
        واپس AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    اگر (!nb_samples)
        واپس 0;
    اگر (انحراف > af->nb_samples - nb_samples)
        واپس AVERROR(EINVAL);

    انحراف *= af->sample_سائز;
    سائز = nb_samples * af->sample_سائز;
    برائے (i = 0; i < af->nb_buffers; i++) {
        اگر ((ret = av_fifo_peek(af->buf[i], ڈیٹا[i], سائز, انحراف)) < 0)
            واپس AVERROR_BUG;
    }

    واپس nb_samples;
}

صحیح av_audio_fifo_read(AVAudioFifo *af, خالی * ثابت *ڈیٹا, صحیح nb_samples)
{
    صحیح i, سائز;

    اگر (nb_samples < 0)
        واپس AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);
    اگر (!nb_samples)
        واپس 0;

    سائز = nb_samples * af->sample_سائز;
    برائے (i = 0; i < af->nb_buffers; i++) {
        اگر (av_fifo_read(af->buf[i], ڈیٹا[i], سائز) < 0)
            واپس AVERROR_BUG;
    }
    af->nb_samples -= nb_samples;

    واپس nb_samples;
}

صحیح av_audio_fifo_drain(AVAudioFifo *af, صحیح nb_samples)
{
    صحیح i, سائز;

    اگر (nb_samples < 0)
        واپس AVERROR(EINVAL);
    nb_samples = FFMIN(nb_samples, af->nb_samples);

    اگر (nb_samples) {
        سائز = nb_samples * af->sample_سائز;
        برائے (i = 0; i < af->nb_buffers; i++)
            av_fifo_drain2(af->buf[i], سائز);
        af->nb_samples -= nb_samples;
    }
    واپس 0;
}

خالی av_audio_fifo_reset(AVAudioFifo *af)
{
    صحیح i;

    برائے (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset2(af->buf[i]);

    af->nb_samples = 0;
}

صحیح av_audio_fifo_سائز(AVAudioFifo *af)
{
    واپس af->nb_samples;
}

صحیح av_audio_fifo_space(AVAudioFifo *af)
{
    واپس af->allocated_samples - af->nb_samples;
}
