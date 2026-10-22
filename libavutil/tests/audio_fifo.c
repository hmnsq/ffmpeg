/*
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
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <inttypes.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/audio_fifo.c"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CHANNELS    32


ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ TestStruct {
    ਅਚਲ ਗਿਣਤੀ AVSampleFormat format;
    ਅਚਲ ਪੂਰਨ nb_ch;
    ਖਾਲੀ ਅਚਲ *ਅੰਕੜੇ_planes[MAX_CHANNELS];
    ਅਚਲ ਪੂਰਨ nb_samples_pch;
} TestStruct;

ਸਥਿਰ ਅਚਲ uint8_t ਅੰਕੜੇ_U8 [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
ਸਥਿਰ ਅਚਲ int16_t ਅੰਕੜੇ_S16[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
ਸਥਿਰ ਅਚਲ ਦਸ਼ਮਲਵ   ਅੰਕੜੇ_FLT[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

ਸਥਿਰ ਅਚਲ TestStruct test_struct[] = {
    {.format = AV_SAMPLE_FMT_U8   , .nb_ch = 1, .ਅੰਕੜੇ_planes = {ਅੰਕੜੇ_U8 ,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_U8P  , .nb_ch = 2, .ਅੰਕੜੇ_planes = {ਅੰਕੜੇ_U8 , ਅੰਕੜੇ_U8 +6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_S16  , .nb_ch = 1, .ਅੰਕੜੇ_planes = {ਅੰਕੜੇ_S16,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_S16P , .nb_ch = 2, .ਅੰਕੜੇ_planes = {ਅੰਕੜੇ_S16, ਅੰਕੜੇ_S16+6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_FLT  , .nb_ch = 1, .ਅੰਕੜੇ_planes = {ਅੰਕੜੇ_FLT,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_FLTP , .nb_ch = 2, .ਅੰਕੜੇ_planes = {ਅੰਕੜੇ_FLT, ਅੰਕੜੇ_FLT+6, }, .nb_samples_pch = 6 }
};

ਸਥਿਰ ਖਾਲੀ free_ਅੰਕੜੇ_planes(AVAudioFifo *afifo, ਖਾਲੀ **output_ਅੰਕੜੇ)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < afifo->nb_buffers; ++i){
        av_freep(&output_ਅੰਕੜੇ[i]);
    }
    av_freep(&output_ਅੰਕੜੇ);
}

ਸਥਿਰ ਖਾਲੀ ERROR(ਅਚਲ ਅੱਖਰ *str)
{
    fprintf(stderr, "%s\n", str);
    ਬਾਹਰ_ਨਿਕਲੋ(1);
}

ਸਥਿਰ ਖਾਲੀ print_audio_ਬਾਈਟਾਂ(ਅਚਲ TestStruct *test_sample, ਖਾਲੀ **ਅੰਕੜੇ_planes, ਪੂਰਨ nb_samples)
{
    ਪੂਰਨ p, b, f;
    ਪੂਰਨ byte_ਵਿੱਥ      = av_get_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_sample(test_sample->format);
    ਪੂਰਨ buffers          = av_sample_fmt_is_planar(test_sample->format)
                                         ? test_sample->nb_ch : 1;
    ਪੂਰਨ ਸਤਰ_ਮਾਪ        = (buffers > 1) ? nb_samples * byte_ਵਿੱਥ
                                         : nb_samples * byte_ਵਿੱਥ * test_sample->nb_ch;
    ਲਈ (p = 0; p < buffers; ++p){
        ਲਈ(b = 0; b < ਸਤਰ_ਮਾਪ; b+=byte_ਵਿੱਥ){
            ਲਈ (f = 0; f < byte_ਵਿੱਥ; f++){
                ਪੂਰਨ ਕ੍ਰਮ = !HAVE_BIGENDIAN ? (byte_ਵਿੱਥ - f - 1) : f;
                ਲਿਖੋ("%02x", *((uint8_t*)ਅੰਕੜੇ_planes[p] + b + ਕ੍ਰਮ));
            }
            ਜੇ (b + byte_ਵਿੱਥ < ਸਤਰ_ਮਾਪ)
                ਅੱਖਰ_ਲਿਖੋ(' ');
        }
        ਅੱਖਰ_ਲਿਖੋ('\n');
    }
}

ਸਥਿਰ ਪੂਰਨ read_samples_from_audio_fifo(AVAudioFifo* afifo, ਖਾਲੀ ***output, ਪੂਰਨ nb_samples)
{
    ਪੂਰਨ i;
    ਪੂਰਨ samples        = FFMIN(nb_samples, afifo->nb_samples);
    ਪੂਰਨ tot_elements   = !av_sample_fmt_is_planar(afifo->sample_fmt)
                         ? samples : afifo->channels * samples;
    ਖਾਲੀ **ਅੰਕੜੇ_planes = av_malloc_array(afifo->nb_buffers, ਆਕਾਰ(ਖਾਲੀ*));
    ਜੇ (!ਅੰਕੜੇ_planes)
        ERROR("failed to allocate memory!");
    ਜੇ (*output)
        free_ਅੰਕੜੇ_planes(afifo, *output);
    *output            = ਅੰਕੜੇ_planes;

    ਲਈ (i = 0; i < afifo->nb_buffers; ++i){
        ਅੰਕੜੇ_planes[i] = av_malloc_array(tot_elements, afifo->sample_ਮਾਪ);
        ਜੇ (!ਅੰਕੜੇ_planes[i])
            ERROR("failed to allocate memory!");
    }

    ਵਾਪਸ av_audio_fifo_read(afifo, *output, nb_samples);
}

ਸਥਿਰ ਪੂਰਨ write_samples_ਮੰਜ਼ਿਲ_audio_fifo(AVAudioFifo* afifo, ਅਚਲ TestStruct *test_sample,
                                       ਪੂਰਨ nb_samples, ਪੂਰਨ ਵਿੱਥ)
{
    ਪੂਰਨ ਵਿੱਥ_ਮਾਪ, i;
    ਖਾਲੀ *ਅੰਕੜੇ_planes[MAX_CHANNELS];

    ਜੇ(nb_samples > test_sample->nb_samples_pch - ਵਿੱਥ){
        ਵਾਪਸ 0;
    }
    ਜੇ(ਵਿੱਥ >= test_sample->nb_samples_pch){
        ਵਾਪਸ 0;
    }
    ਵਿੱਥ_ਮਾਪ  = ਵਿੱਥ * afifo->sample_ਮਾਪ;

    ਲਈ (i = 0; i < afifo->nb_buffers ; ++i){
        ਅੰਕੜੇ_planes[i] = (uint8_t*)test_sample->ਅੰਕੜੇ_planes[i] + ਵਿੱਥ_ਮਾਪ;
    }

    ਵਾਪਸ av_audio_fifo_write(afifo, ਅੰਕੜੇ_planes, nb_samples);
}

ਸਥਿਰ ਖਾਲੀ test_function(ਅਚਲ TestStruct *test_sample)
{
    ਪੂਰਨ ret, i;
    ਖਾਲੀ **output_ਅੰਕੜੇ  = ਨਿਰਾ;
    AVAudioFifo *afifo  = av_audio_fifo_alloc(test_sample->format, test_sample->nb_ch,
                                            test_sample->nb_samples_pch);
    ਜੇ (!afifo) {
        ERROR("ERROR: av_audio_fifo_alloc returned NULL!");
    }
    ret = write_samples_ਮੰਜ਼ਿਲ_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    ਜੇ (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    ਲਿਖੋ("written: %d\n", ret);

    ret = write_samples_ਮੰਜ਼ਿਲ_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    ਜੇ (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    ਲਿਖੋ("written: %d\n", ret);
    ਲਿਖੋ("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_ਮਾਪ(afifo));

    ret = read_samples_from_audio_fifo(afifo, &output_ਅੰਕੜੇ, test_sample->nb_samples_pch);
    ਜੇ (ret < 0){
        ERROR("ERROR: av_audio_fifo_read failed!");
    }
    ਲਿਖੋ("read: %d\n", ret);
    print_audio_ਬਾਈਟਾਂ(test_sample, output_ਅੰਕੜੇ, ret);
    ਲਿਖੋ("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_ਮਾਪ(afifo));

    /* test av_audio_fifo_peek */
    ret = av_audio_fifo_peek(afifo, output_ਅੰਕੜੇ, afifo->nb_samples);
    ਜੇ (ret < 0){
        ERROR("ERROR: av_audio_fifo_peek failed!");
    }
    ਲਿਖੋ("peek:\n");
    print_audio_ਬਾਈਟਾਂ(test_sample, output_ਅੰਕੜੇ, ret);
    ਲਿਖੋ("\n");

    /* test av_audio_fifo_peek_at */
    ਲਿਖੋ("peek_at:\n");
    ਲਈ (i = 0; i < afifo->nb_samples; ++i){
        ret = av_audio_fifo_peek_at(afifo, output_ਅੰਕੜੇ, 1, i);
        ਜੇ (ret < 0){
            ERROR("ERROR: av_audio_fifo_peek_at failed!");
        }
        ਲਿਖੋ("%d:\n", i);
        print_audio_ਬਾਈਟਾਂ(test_sample, output_ਅੰਕੜੇ, ret);
    }
    ਲਿਖੋ("\n");

    /* test av_audio_fifo_drain */
    ret = av_audio_fifo_drain(afifo, afifo->nb_samples);
    ਜੇ (ret < 0){
        ERROR("ERROR: av_audio_fifo_drain failed!");
    }
    ਜੇ (afifo->nb_samples){
        ERROR("drain failed to flush all samples in audio_fifo!");
    }

    /* deallocate */
    free_ਅੰਕੜੇ_planes(afifo, output_ਅੰਕੜੇ);
    av_audio_fifo_free(afifo);
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਪੂਰਨ t, tests = ਆਕਾਰ(test_struct)/ਆਕਾਰ(test_struct[0]);

    ਲਈ (t = 0; t < tests; ++t){
        ਲਿਖੋ("\nTEST: %d\n\n", t+1);
        test_function(&test_struct[t]);
    }
    ਵਾਪਸ 0;
}
