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
#ଅନ୍ତର୍ଭାଵ "config.h"

#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <inttypes.h>
#ଅନ୍ତର୍ଭାଵ "libavutil/mem.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/audio_fifo.c"

#define MAX_CHANNELS    32


ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା TestStruct {
    ଅଚଳ ଗଣନା AVSampleFormat format;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_ch;
    ଶୂନ୍ୟ ଅଚଳ *data_planes[MAX_CHANNELS];
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples_pch;
} TestStruct;

ସ୍ଥିର ଅଚଳ uint8_t data_U8 [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
ସ୍ଥିର ଅଚଳ int16_t data_S16[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
ସ୍ଥିର ଅଚଳ ଦଶମିକ   data_FLT[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

ସ୍ଥିର ଅଚଳ TestStruct test_struct[] = {
    {.format = AV_SAMPLE_FMT_U8   , .nb_ch = 1, .data_planes = {data_U8 ,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_U8P  , .nb_ch = 2, .data_planes = {data_U8 , data_U8 +6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_S16  , .nb_ch = 1, .data_planes = {data_S16,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_S16P , .nb_ch = 2, .data_planes = {data_S16, data_S16+6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_FLT  , .nb_ch = 1, .data_planes = {data_FLT,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_FLTP , .nb_ch = 2, .data_planes = {data_FLT, data_FLT+6, }, .nb_samples_pch = 6 }
};

ସ୍ଥିର ଶୂନ୍ୟ free_data_planes(AVAudioFifo *afifo, ଶୂନ୍ୟ **output_data)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < afifo->nb_buffers; ++i){
        av_freep(&output_data[i]);
    }
    av_freep(&output_data);
}

ସ୍ଥିର ଶୂନ୍ୟ ERROR(ଅଚଳ ଅକ୍ଷର *str)
{
    fprintf(stderr, "%s\n", str);
    exit(1);
}

ସ୍ଥିର ଶୂନ୍ୟ print_audio_bytes(ଅଚଳ TestStruct *test_sample, ଶୂନ୍ୟ **data_planes, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା p, b, f;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା byte_offset      = av_get_bytes_per_sample(test_sample->format);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା buffers          = av_sample_fmt_is_planar(test_sample->format)
                                         ? test_sample->nb_ch : 1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଧାଡ଼ି_size        = (buffers > 1) ? nb_samples * byte_offset
                                         : nb_samples * byte_offset * test_sample->nb_ch;
    ପାଇଁ (p = 0; p < buffers; ++p){
        ପାଇଁ(b = 0; b < ଧାଡ଼ି_size; b+=byte_offset){
            ପାଇଁ (f = 0; f < byte_offset; f++){
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା order = !HAVE_BIGENDIAN ? (byte_offset - f - 1) : f;
                printf("%02x", *((uint8_t*)data_planes[p] + b + order));
            }
            ଯଦି (b + byte_offset < ଧାଡ଼ି_size)
                putchar(' ');
        }
        putchar('\n');
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା read_samples_from_audio_fifo(AVAudioFifo* afifo, ଶୂନ୍ୟ ***output, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା samples        = FFMIN(nb_samples, afifo->nb_samples);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା tot_elements   = !av_sample_fmt_is_planar(afifo->sample_fmt)
                         ? samples : afifo->channels * samples;
    ଶୂନ୍ୟ **data_planes = av_malloc_array(afifo->nb_buffers, ଆକାର(ଶୂନ୍ୟ*));
    ଯଦି (!data_planes)
        ERROR("failed to allocate memory!");
    ଯଦି (*output)
        free_data_planes(afifo, *output);
    *output            = data_planes;

    ପାଇଁ (i = 0; i < afifo->nb_buffers; ++i){
        data_planes[i] = av_malloc_array(tot_elements, afifo->sample_size);
        ଯଦି (!data_planes[i])
            ERROR("failed to allocate memory!");
    }

    ଫେରନ୍ତୁ av_audio_fifo_read(afifo, *output, nb_samples);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା write_samples_to_audio_fifo(AVAudioFifo* afifo, ଅଚଳ TestStruct *test_sample,
                                       ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_samples, ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset_size, i;
    ଶୂନ୍ୟ *data_planes[MAX_CHANNELS];

    ଯଦି(nb_samples > test_sample->nb_samples_pch - offset){
        ଫେରନ୍ତୁ 0;
    }
    ଯଦି(offset >= test_sample->nb_samples_pch){
        ଫେରନ୍ତୁ 0;
    }
    offset_size  = offset * afifo->sample_size;

    ପାଇଁ (i = 0; i < afifo->nb_buffers ; ++i){
        data_planes[i] = (uint8_t*)test_sample->data_planes[i] + offset_size;
    }

    ଫେରନ୍ତୁ av_audio_fifo_write(afifo, data_planes, nb_samples);
}

ସ୍ଥିର ଶୂନ୍ୟ test_function(ଅଚଳ TestStruct *test_sample)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, i;
    ଶୂନ୍ୟ **output_data  = ଖାଲି;
    AVAudioFifo *afifo  = av_audio_fifo_alloc(test_sample->format, test_sample->nb_ch,
                                            test_sample->nb_samples_pch);
    ଯଦି (!afifo) {
        ERROR("ERROR: av_audio_fifo_alloc returned NULL!");
    }
    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    ଯଦି (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    printf("written: %d\n", ret);

    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    ଯଦି (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    printf("written: %d\n", ret);
    printf("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));

    ret = read_samples_from_audio_fifo(afifo, &output_data, test_sample->nb_samples_pch);
    ଯଦି (ret < 0){
        ERROR("ERROR: av_audio_fifo_read failed!");
    }
    printf("read: %d\n", ret);
    print_audio_bytes(test_sample, output_data, ret);
    printf("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));

    /* test av_audio_fifo_peek */
    ret = av_audio_fifo_peek(afifo, output_data, afifo->nb_samples);
    ଯଦି (ret < 0){
        ERROR("ERROR: av_audio_fifo_peek failed!");
    }
    printf("peek:\n");
    print_audio_bytes(test_sample, output_data, ret);
    printf("\n");

    /* test av_audio_fifo_peek_at */
    printf("peek_at:\n");
    ପାଇଁ (i = 0; i < afifo->nb_samples; ++i){
        ret = av_audio_fifo_peek_at(afifo, output_data, 1, i);
        ଯଦି (ret < 0){
            ERROR("ERROR: av_audio_fifo_peek_at failed!");
        }
        printf("%d:\n", i);
        print_audio_bytes(test_sample, output_data, ret);
    }
    printf("\n");

    /* test av_audio_fifo_drain */
    ret = av_audio_fifo_drain(afifo, afifo->nb_samples);
    ଯଦି (ret < 0){
        ERROR("ERROR: av_audio_fifo_drain failed!");
    }
    ଯଦି (afifo->nb_samples){
        ERROR("drain failed to flush all samples in audio_fifo!");
    }

    /* deallocate */
    free_data_planes(afifo, output_data);
    av_audio_fifo_free(afifo);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା t, tests = ଆକାର(test_struct)/ଆକାର(test_struct[0]);

    ପାଇଁ (t = 0; t < tests; ++t){
        printf("\nTEST: %d\n\n", t+1);
        test_function(&test_struct[t]);
    }
    ଫେରନ୍ତୁ 0;
}
