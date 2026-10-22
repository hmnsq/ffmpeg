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
    अचर गणना AVSampleFormat format;
    अचर पूर्णाङ्क nb_ch;
    शून्य अचर *data_planes[MAX_CHANNELS];
    अचर पूर्णाङ्क nb_samples_pch;
} TestStruct;

स्थिर अचर uint8_t data_U8 [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
स्थिर अचर int16_t data_S16[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
स्थिर अचर भिन्न   data_FLT[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

स्थिर अचर TestStruct test_struct[] = {
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
    लागि (i = 0; i < afifo->nb_buffers; ++i){
        av_freep(&output_data[i]);
    }
    av_freep(&output_data);
}

स्थिर शून्य ERROR(अचर वर्ण *str)
{
    ख_लिखो(मानक_त्रुटि, "%s\n", str);
    निकास(1);
}

स्थिर शून्य print_audio_bytes(अचर TestStruct *test_sample, शून्य **data_planes, पूर्णाङ्क nb_samples)
{
    पूर्णाङ्क p, b, f;
    पूर्णाङ्क byte_offset      = av_get_bytes_per_sample(test_sample->format);
    पूर्णाङ्क buffers          = av_sample_fmt_is_planar(test_sample->format)
                                         ? test_sample->nb_ch : 1;
    पूर्णाङ्क पङ्क्ति_size        = (buffers > 1) ? nb_samples * byte_offset
                                         : nb_samples * byte_offset * test_sample->nb_ch;
    लागि (p = 0; p < buffers; ++p){
        लागि(b = 0; b < पङ्क्ति_size; b+=byte_offset){
            लागि (f = 0; f < byte_offset; f++){
                पूर्णाङ्क order = !HAVE_BIGENDIAN ? (byte_offset - f - 1) : f;
                म_लिखो("%02x", *((uint8_t*)data_planes[p] + b + order));
            }
            यदि (b + byte_offset < पङ्क्ति_size)
                अक्षर_दो(' ');
        }
        अक्षर_दो('\n');
    }
}

स्थिर पूर्णाङ्क read_samples_from_audio_fifo(AVAudioFifo* afifo, शून्य ***output, पूर्णाङ्क nb_samples)
{
    पूर्णाङ्क i;
    पूर्णाङ्क samples        = FFMIN(nb_samples, afifo->nb_samples);
    पूर्णाङ्क tot_elements   = !av_sample_fmt_is_planar(afifo->sample_fmt)
                         ? samples : afifo->channels * samples;
    शून्य **data_planes = av_malloc_array(afifo->nb_buffers, परिमाण(शून्य*));
    यदि (!data_planes)
        ERROR("failed to allocate memory!");
    यदि (*output)
        free_data_planes(afifo, *output);
    *output            = data_planes;

    लागि (i = 0; i < afifo->nb_buffers; ++i){
        data_planes[i] = av_malloc_array(tot_elements, afifo->sample_size);
        यदि (!data_planes[i])
            ERROR("failed to allocate memory!");
    }

    फर्काऊ av_audio_fifo_read(afifo, *output, nb_samples);
}

स्थिर पूर्णाङ्क write_samples_to_audio_fifo(AVAudioFifo* afifo, अचर TestStruct *test_sample,
                                       पूर्णाङ्क nb_samples, पूर्णाङ्क offset)
{
    पूर्णाङ्क offset_size, i;
    शून्य *data_planes[MAX_CHANNELS];

    यदि(nb_samples > test_sample->nb_samples_pch - offset){
        फर्काऊ 0;
    }
    यदि(offset >= test_sample->nb_samples_pch){
        फर्काऊ 0;
    }
    offset_size  = offset * afifo->sample_size;

    लागि (i = 0; i < afifo->nb_buffers ; ++i){
        data_planes[i] = (uint8_t*)test_sample->data_planes[i] + offset_size;
    }

    फर्काऊ av_audio_fifo_write(afifo, data_planes, nb_samples);
}

स्थिर शून्य test_function(अचर TestStruct *test_sample)
{
    पूर्णाङ्क ret, i;
    शून्य **output_data  = रिक्त;
    AVAudioFifo *afifo  = av_audio_fifo_alloc(test_sample->format, test_sample->nb_ch,
                                            test_sample->nb_samples_pch);
    यदि (!afifo) {
        ERROR("ERROR: av_audio_fifo_alloc returned NULL!");
    }
    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    यदि (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    म_लिखो("written: %d\n", ret);

    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    यदि (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    म_लिखो("written: %d\n", ret);
    म_लिखो("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));

    ret = read_samples_from_audio_fifo(afifo, &output_data, test_sample->nb_samples_pch);
    यदि (ret < 0){
        ERROR("ERROR: av_audio_fifo_read failed!");
    }
    म_लिखो("read: %d\n", ret);
    print_audio_bytes(test_sample, output_data, ret);
    म_लिखो("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));

    /* test av_audio_fifo_peek */
    ret = av_audio_fifo_peek(afifo, output_data, afifo->nb_samples);
    यदि (ret < 0){
        ERROR("ERROR: av_audio_fifo_peek failed!");
    }
    म_लिखो("peek:\n");
    print_audio_bytes(test_sample, output_data, ret);
    म_लिखो("\n");

    /* test av_audio_fifo_peek_at */
    म_लिखो("peek_at:\n");
    लागि (i = 0; i < afifo->nb_samples; ++i){
        ret = av_audio_fifo_peek_at(afifo, output_data, 1, i);
        यदि (ret < 0){
            ERROR("ERROR: av_audio_fifo_peek_at failed!");
        }
        म_लिखो("%d:\n", i);
        print_audio_bytes(test_sample, output_data, ret);
    }
    म_लिखो("\n");

    /* test av_audio_fifo_drain */
    ret = av_audio_fifo_drain(afifo, afifo->nb_samples);
    यदि (ret < 0){
        ERROR("ERROR: av_audio_fifo_drain failed!");
    }
    यदि (afifo->nb_samples){
        ERROR("drain failed to flush all samples in audio_fifo!");
    }

    /* deallocate */
    free_data_planes(afifo, output_data);
    av_audio_fifo_free(afifo);
}

पूर्णाङ्क main(शून्य)
{
    पूर्णाङ्क t, tests = परिमाण(test_struct)/परिमाण(test_struct[0]);

    लागि (t = 0; t < tests; ++t){
        म_लिखो("\nTEST: %d\n\n", t+1);
        test_function(&test_struct[t]);
    }
    फर्काऊ 0;
}
