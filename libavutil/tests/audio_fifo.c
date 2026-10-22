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
#अन्तर्भाव "config.h"

#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <inttypes.h>
#अन्तर्भाव "libavutil/mem.h"
#अन्तर्भाव "libavutil/audio_fifo.c"

#define MAX_CHANNELS    32


प्रकारनिर्देश संरचना TestStruct {
    ध्रुव गणना AVSampleFormat format;
    ध्रुव पूर्णाङ्क nb_ch;
    शून्य ध्रुव *data_planes[MAX_CHANNELS];
    ध्रुव पूर्णाङ्क nb_samples_pch;
} TestStruct;

स्थिर ध्रुव uint8_t data_U8 [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
स्थिर ध्रुव int16_t data_S16[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
स्थिर ध्रुव भिन्न   data_FLT[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

स्थिर ध्रुव TestStruct test_struct[] = {
    {.format = AV_SAMPLE_FMT_U8   , .nb_ch = 1, .data_planes = {data_U8 ,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_U8P  , .nb_ch = 2, .data_planes = {data_U8 , data_U8 +6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_S16  , .nb_ch = 1, .data_planes = {data_S16,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_S16P , .nb_ch = 2, .data_planes = {data_S16, data_S16+6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_FLT  , .nb_ch = 1, .data_planes = {data_FLT,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_FLTP , .nb_ch = 2, .data_planes = {data_FLT, data_FLT+6, }, .nb_samples_pch = 6 }
};

स्थिर शून्य free_data_planes(AVAudioFifo *afifo, शून्य **output_data)
{
    पूर्णाङ्क i;
    प्रति (i = 0; i < afifo->nb_buffers; ++i){
        av_freep(&output_data[i]);
    }
    av_freep(&output_data);
}

स्थिर शून्य ERROR(ध्रुव वर्ण *str)
{
    fprintf(stderr, "%s\n", str);
    exit(1);
}

स्थिर शून्य print_audio_bytes(ध्रुव TestStruct *test_sample, शून्य **data_planes, पूर्णाङ्क nb_samples)
{
    पूर्णाङ्क p, b, f;
    पूर्णाङ्क byte_offset      = av_get_bytes_per_sample(test_sample->format);
    पूर्णाङ्क buffers          = av_sample_fmt_is_planar(test_sample->format)
                                         ? test_sample->nb_ch : 1;
    पूर्णाङ्क पङ्क्तिः_size        = (buffers > 1) ? nb_samples * byte_offset
                                         : nb_samples * byte_offset * test_sample->nb_ch;
    प्रति (p = 0; p < buffers; ++p){
        प्रति(b = 0; b < पङ्क्तिः_size; b+=byte_offset){
            प्रति (f = 0; f < byte_offset; f++){
                पूर्णाङ्क order = !HAVE_BIGENDIAN ? (byte_offset - f - 1) : f;
                printf("%02x", *((uint8_t*)data_planes[p] + b + order));
            }
            जइ (b + byte_offset < पङ्क्तिः_size)
                putchar(' ');
        }
        putchar('\n');
    }
}

स्थिर पूर्णाङ्क read_samples_from_audio_fifo(AVAudioFifo* afifo, शून्य ***output, पूर्णाङ्क nb_samples)
{
    पूर्णाङ्क i;
    पूर्णाङ्क samples        = FFMIN(nb_samples, afifo->nb_samples);
    पूर्णाङ्क tot_elements   = !av_sample_fmt_is_planar(afifo->sample_fmt)
                         ? samples : afifo->channels * samples;
    शून्य **data_planes = av_malloc_array(afifo->nb_buffers, परिमाण(शून्य*));
    जइ (!data_planes)
        ERROR("failed to allocate memory!");
    जइ (*output)
        free_data_planes(afifo, *output);
    *output            = data_planes;

    प्रति (i = 0; i < afifo->nb_buffers; ++i){
        data_planes[i] = av_malloc_array(tot_elements, afifo->sample_size);
        जइ (!data_planes[i])
            ERROR("failed to allocate memory!");
    }

    प्रत्यागम av_audio_fifo_read(afifo, *output, nb_samples);
}

स्थिर पूर्णाङ्क write_samples_to_audio_fifo(AVAudioFifo* afifo, ध्रुव TestStruct *test_sample,
                                       पूर्णाङ्क nb_samples, पूर्णाङ्क offset)
{
    पूर्णाङ्क offset_size, i;
    शून्य *data_planes[MAX_CHANNELS];

    जइ(nb_samples > test_sample->nb_samples_pch - offset){
        प्रत्यागम 0;
    }
    जइ(offset >= test_sample->nb_samples_pch){
        प्रत्यागम 0;
    }
    offset_size  = offset * afifo->sample_size;

    प्रति (i = 0; i < afifo->nb_buffers ; ++i){
        data_planes[i] = (uint8_t*)test_sample->data_planes[i] + offset_size;
    }

    प्रत्यागम av_audio_fifo_write(afifo, data_planes, nb_samples);
}

स्थिर शून्य test_function(ध्रुव TestStruct *test_sample)
{
    पूर्णाङ्क ret, i;
    शून्य **output_data  = रिक्त;
    AVAudioFifo *afifo  = av_audio_fifo_alloc(test_sample->format, test_sample->nb_ch,
                                            test_sample->nb_samples_pch);
    जइ (!afifo) {
        ERROR("ERROR: av_audio_fifo_alloc returned NULL!");
    }
    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    जइ (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    printf("written: %d\n", ret);

    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    जइ (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    printf("written: %d\n", ret);
    printf("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));

    ret = read_samples_from_audio_fifo(afifo, &output_data, test_sample->nb_samples_pch);
    जइ (ret < 0){
        ERROR("ERROR: av_audio_fifo_read failed!");
    }
    printf("read: %d\n", ret);
    print_audio_bytes(test_sample, output_data, ret);
    printf("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));

    /* test av_audio_fifo_peek */
    ret = av_audio_fifo_peek(afifo, output_data, afifo->nb_samples);
    जइ (ret < 0){
        ERROR("ERROR: av_audio_fifo_peek failed!");
    }
    printf("peek:\n");
    print_audio_bytes(test_sample, output_data, ret);
    printf("\n");

    /* test av_audio_fifo_peek_at */
    printf("peek_at:\n");
    प्रति (i = 0; i < afifo->nb_samples; ++i){
        ret = av_audio_fifo_peek_at(afifo, output_data, 1, i);
        जइ (ret < 0){
            ERROR("ERROR: av_audio_fifo_peek_at failed!");
        }
        printf("%d:\n", i);
        print_audio_bytes(test_sample, output_data, ret);
    }
    printf("\n");

    /* test av_audio_fifo_drain */
    ret = av_audio_fifo_drain(afifo, afifo->nb_samples);
    जइ (ret < 0){
        ERROR("ERROR: av_audio_fifo_drain failed!");
    }
    जइ (afifo->nb_samples){
        ERROR("drain failed to flush all samples in audio_fifo!");
    }

    /* deallocate */
    free_data_planes(afifo, output_data);
    av_audio_fifo_free(afifo);
}

पूर्णाङ्क main(शून्य)
{
    पूर्णाङ्क t, tests = परिमाण(test_struct)/परिमाण(test_struct[0]);

    प्रति (t = 0; t < tests; ++t){
        printf("\nTEST: %d\n\n", t+1);
        test_function(&test_struct[t]);
    }
    प्रत्यागम 0;
}
