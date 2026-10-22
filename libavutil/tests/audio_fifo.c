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
#અન્તર્ભાવ "config.h"

#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <inttypes.h>
#અન્તર્ભાવ "libavutil/mem.h"
#અન્તર્ભાવ "libavutil/audio_fifo.c"

#define MAX_CHANNELS    32


પ્રકારવ્યાખ્યા સંરચના TestStruct {
    અચલ ગણના AVSampleFormat format;
    અચલ પૂર્ણાંક nb_ch;
    શૂન્ય અચલ *data_planes[MAX_CHANNELS];
    અચલ પૂર્ણાંક nb_samples_pch;
} TestStruct;

સ્થિર અચલ uint8_t data_U8 [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
સ્થિર અચલ int16_t data_S16[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
સ્થિર અચલ દશાંશ   data_FLT[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

સ્થિર અચલ TestStruct test_struct[] = {
    {.format = AV_SAMPLE_FMT_U8   , .nb_ch = 1, .data_planes = {data_U8 ,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_U8P  , .nb_ch = 2, .data_planes = {data_U8 , data_U8 +6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_S16  , .nb_ch = 1, .data_planes = {data_S16,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_S16P , .nb_ch = 2, .data_planes = {data_S16, data_S16+6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_FLT  , .nb_ch = 1, .data_planes = {data_FLT,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_FLTP , .nb_ch = 2, .data_planes = {data_FLT, data_FLT+6, }, .nb_samples_pch = 6 }
};

સ્થિર શૂન્ય free_data_planes(AVAudioFifo *afifo, શૂન્ય **output_data)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < afifo->nb_buffers; ++i){
        av_freep(&output_data[i]);
    }
    av_freep(&output_data);
}

સ્થિર શૂન્ય ERROR(અચલ અક્ષર *str)
{
    fprintf(stderr, "%s\n", str);
    exit(1);
}

સ્થિર શૂન્ય print_audio_bytes(અચલ TestStruct *test_sample, શૂન્ય **data_planes, પૂર્ણાંક nb_samples)
{
    પૂર્ણાંક p, b, f;
    પૂર્ણાંક byte_offset      = av_get_bytes_per_sample(test_sample->format);
    પૂર્ણાંક buffers          = av_sample_fmt_is_planar(test_sample->format)
                                         ? test_sample->nb_ch : 1;
    પૂર્ણાંક લીટી_size        = (buffers > 1) ? nb_samples * byte_offset
                                         : nb_samples * byte_offset * test_sample->nb_ch;
    માટે (p = 0; p < buffers; ++p){
        માટે(b = 0; b < લીટી_size; b+=byte_offset){
            માટે (f = 0; f < byte_offset; f++){
                પૂર્ણાંક order = !HAVE_BIGENDIAN ? (byte_offset - f - 1) : f;
                printf("%02x", *((uint8_t*)data_planes[p] + b + order));
            }
            જો (b + byte_offset < લીટી_size)
                putchar(' ');
        }
        putchar('\n');
    }
}

સ્થિર પૂર્ણાંક read_samples_from_audio_fifo(AVAudioFifo* afifo, શૂન્ય ***output, પૂર્ણાંક nb_samples)
{
    પૂર્ણાંક i;
    પૂર્ણાંક samples        = FFMIN(nb_samples, afifo->nb_samples);
    પૂર્ણાંક tot_elements   = !av_sample_fmt_is_planar(afifo->sample_fmt)
                         ? samples : afifo->channels * samples;
    શૂન્ય **data_planes = av_malloc_array(afifo->nb_buffers, કદ(શૂન્ય*));
    જો (!data_planes)
        ERROR("failed to allocate memory!");
    જો (*output)
        free_data_planes(afifo, *output);
    *output            = data_planes;

    માટે (i = 0; i < afifo->nb_buffers; ++i){
        data_planes[i] = av_malloc_array(tot_elements, afifo->sample_size);
        જો (!data_planes[i])
            ERROR("failed to allocate memory!");
    }

    પાછા av_audio_fifo_read(afifo, *output, nb_samples);
}

સ્થિર પૂર્ણાંક write_samples_to_audio_fifo(AVAudioFifo* afifo, અચલ TestStruct *test_sample,
                                       પૂર્ણાંક nb_samples, પૂર્ણાંક offset)
{
    પૂર્ણાંક offset_size, i;
    શૂન્ય *data_planes[MAX_CHANNELS];

    જો(nb_samples > test_sample->nb_samples_pch - offset){
        પાછા 0;
    }
    જો(offset >= test_sample->nb_samples_pch){
        પાછા 0;
    }
    offset_size  = offset * afifo->sample_size;

    માટે (i = 0; i < afifo->nb_buffers ; ++i){
        data_planes[i] = (uint8_t*)test_sample->data_planes[i] + offset_size;
    }

    પાછા av_audio_fifo_write(afifo, data_planes, nb_samples);
}

સ્થિર શૂન્ય test_function(અચલ TestStruct *test_sample)
{
    પૂર્ણાંક ret, i;
    શૂન્ય **output_data  = ખાલી;
    AVAudioFifo *afifo  = av_audio_fifo_alloc(test_sample->format, test_sample->nb_ch,
                                            test_sample->nb_samples_pch);
    જો (!afifo) {
        ERROR("ERROR: av_audio_fifo_alloc returned NULL!");
    }
    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    જો (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    printf("written: %d\n", ret);

    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    જો (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    printf("written: %d\n", ret);
    printf("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));

    ret = read_samples_from_audio_fifo(afifo, &output_data, test_sample->nb_samples_pch);
    જો (ret < 0){
        ERROR("ERROR: av_audio_fifo_read failed!");
    }
    printf("read: %d\n", ret);
    print_audio_bytes(test_sample, output_data, ret);
    printf("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));

    /* test av_audio_fifo_peek */
    ret = av_audio_fifo_peek(afifo, output_data, afifo->nb_samples);
    જો (ret < 0){
        ERROR("ERROR: av_audio_fifo_peek failed!");
    }
    printf("peek:\n");
    print_audio_bytes(test_sample, output_data, ret);
    printf("\n");

    /* test av_audio_fifo_peek_at */
    printf("peek_at:\n");
    માટે (i = 0; i < afifo->nb_samples; ++i){
        ret = av_audio_fifo_peek_at(afifo, output_data, 1, i);
        જો (ret < 0){
            ERROR("ERROR: av_audio_fifo_peek_at failed!");
        }
        printf("%d:\n", i);
        print_audio_bytes(test_sample, output_data, ret);
    }
    printf("\n");

    /* test av_audio_fifo_drain */
    ret = av_audio_fifo_drain(afifo, afifo->nb_samples);
    જો (ret < 0){
        ERROR("ERROR: av_audio_fifo_drain failed!");
    }
    જો (afifo->nb_samples){
        ERROR("drain failed to flush all samples in audio_fifo!");
    }

    /* deallocate */
    free_data_planes(afifo, output_data);
    av_audio_fifo_free(afifo);
}

પૂર્ણાંક મુખ્ય(શૂન્ય)
{
    પૂર્ણાંક t, tests = કદ(test_struct)/કદ(test_struct[0]);

    માટે (t = 0; t < tests; ++t){
        printf("\nTEST: %d\n\n", t+1);
        test_function(&test_struct[t]);
    }
    પાછા 0;
}
