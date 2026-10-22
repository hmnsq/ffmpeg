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


प्रकारव्याख्या संरचना TestStruct {
    स्थिरांक गणना AVSampleFormat format;
    स्थिरांक पूर्णांक nb_ch;
    शून्य स्थिरांक *data_planes[MAX_CHANNELS];
    स्थिरांक पूर्णांक nb_samples_pch;
} TestStruct;

स्थिर स्थिरांक uint8_t data_U8 [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
स्थिर स्थिरांक int16_t data_S16[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
स्थिर स्थिरांक दशांश   data_FLT[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

स्थिर स्थिरांक TestStruct test_struct[] = {
    {.format = AV_SAMPLE_FMT_U8   , .nb_ch = 1, .data_planes = {data_U8 ,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_U8P  , .nb_ch = 2, .data_planes = {data_U8 , data_U8 +6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_S16  , .nb_ch = 1, .data_planes = {data_S16,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_S16P , .nb_ch = 2, .data_planes = {data_S16, data_S16+6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_FLT  , .nb_ch = 1, .data_planes = {data_FLT,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_FLTP , .nb_ch = 2, .data_planes = {data_FLT, data_FLT+6, }, .nb_samples_pch = 6 }
};

स्थिर शून्य free_data_planes(AVAudioFifo *afifo, शून्य **output_data)
{
    पूर्णांक i;
    साठी (i = 0; i < afifo->nb_buffers; ++i){
        av_freep(&output_data[i]);
    }
    av_freep(&output_data);
}

स्थिर शून्य ERROR(स्थिरांक अक्षर *str)
{
    ख_लिखो(मानक_त्रुटि, "%s\n", str);
    निकास(1);
}

स्थिर शून्य print_audio_bytes(स्थिरांक TestStruct *test_sample, शून्य **data_planes, पूर्णांक nb_samples)
{
    पूर्णांक p, b, f;
    पूर्णांक byte_offset      = av_get_bytes_per_sample(test_sample->format);
    पूर्णांक buffers          = av_sample_fmt_is_planar(test_sample->format)
                                         ? test_sample->nb_ch : 1;
    पूर्णांक ओळ_size        = (buffers > 1) ? nb_samples * byte_offset
                                         : nb_samples * byte_offset * test_sample->nb_ch;
    साठी (p = 0; p < buffers; ++p){
        साठी(b = 0; b < ओळ_size; b+=byte_offset){
            साठी (f = 0; f < byte_offset; f++){
                पूर्णांक order = !HAVE_BIGENDIAN ? (byte_offset - f - 1) : f;
                म_लिखो("%02x", *((uint8_t*)data_planes[p] + b + order));
            }
            जर (b + byte_offset < ओळ_size)
                अक्षर_दो(' ');
        }
        अक्षर_दो('\n');
    }
}

स्थिर पूर्णांक read_samples_from_audio_fifo(AVAudioFifo* afifo, शून्य ***output, पूर्णांक nb_samples)
{
    पूर्णांक i;
    पूर्णांक samples        = FFMIN(nb_samples, afifo->nb_samples);
    पूर्णांक tot_elements   = !av_sample_fmt_is_planar(afifo->sample_fmt)
                         ? samples : afifo->channels * samples;
    शून्य **data_planes = av_malloc_array(afifo->nb_buffers, आकार(शून्य*));
    जर (!data_planes)
        ERROR("failed to allocate memory!");
    जर (*output)
        free_data_planes(afifo, *output);
    *output            = data_planes;

    साठी (i = 0; i < afifo->nb_buffers; ++i){
        data_planes[i] = av_malloc_array(tot_elements, afifo->sample_size);
        जर (!data_planes[i])
            ERROR("failed to allocate memory!");
    }

    परत av_audio_fifo_read(afifo, *output, nb_samples);
}

स्थिर पूर्णांक write_samples_to_audio_fifo(AVAudioFifo* afifo, स्थिरांक TestStruct *test_sample,
                                       पूर्णांक nb_samples, पूर्णांक offset)
{
    पूर्णांक offset_size, i;
    शून्य *data_planes[MAX_CHANNELS];

    जर(nb_samples > test_sample->nb_samples_pch - offset){
        परत 0;
    }
    जर(offset >= test_sample->nb_samples_pch){
        परत 0;
    }
    offset_size  = offset * afifo->sample_size;

    साठी (i = 0; i < afifo->nb_buffers ; ++i){
        data_planes[i] = (uint8_t*)test_sample->data_planes[i] + offset_size;
    }

    परत av_audio_fifo_write(afifo, data_planes, nb_samples);
}

स्थिर शून्य test_function(स्थिरांक TestStruct *test_sample)
{
    पूर्णांक ret, i;
    शून्य **output_data  = रिक्त;
    AVAudioFifo *afifo  = av_audio_fifo_alloc(test_sample->format, test_sample->nb_ch,
                                            test_sample->nb_samples_pch);
    जर (!afifo) {
        ERROR("ERROR: av_audio_fifo_alloc returned NULL!");
    }
    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    जर (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    म_लिखो("written: %d\n", ret);

    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    जर (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    म_लिखो("written: %d\n", ret);
    म_लिखो("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));

    ret = read_samples_from_audio_fifo(afifo, &output_data, test_sample->nb_samples_pch);
    जर (ret < 0){
        ERROR("ERROR: av_audio_fifo_read failed!");
    }
    म_लिखो("read: %d\n", ret);
    print_audio_bytes(test_sample, output_data, ret);
    म_लिखो("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_size(afifo));

    /* test av_audio_fifo_peek */
    ret = av_audio_fifo_peek(afifo, output_data, afifo->nb_samples);
    जर (ret < 0){
        ERROR("ERROR: av_audio_fifo_peek failed!");
    }
    म_लिखो("peek:\n");
    print_audio_bytes(test_sample, output_data, ret);
    म_लिखो("\n");

    /* test av_audio_fifo_peek_at */
    म_लिखो("peek_at:\n");
    साठी (i = 0; i < afifo->nb_samples; ++i){
        ret = av_audio_fifo_peek_at(afifo, output_data, 1, i);
        जर (ret < 0){
            ERROR("ERROR: av_audio_fifo_peek_at failed!");
        }
        म_लिखो("%d:\n", i);
        print_audio_bytes(test_sample, output_data, ret);
    }
    म_लिखो("\n");

    /* test av_audio_fifo_drain */
    ret = av_audio_fifo_drain(afifo, afifo->nb_samples);
    जर (ret < 0){
        ERROR("ERROR: av_audio_fifo_drain failed!");
    }
    जर (afifo->nb_samples){
        ERROR("drain failed to flush all samples in audio_fifo!");
    }

    /* deallocate */
    free_data_planes(afifo, output_data);
    av_audio_fifo_free(afifo);
}

पूर्णांक main(शून्य)
{
    पूर्णांक t, tests = आकार(test_struct)/आकार(test_struct[0]);

    साठी (t = 0; t < tests; ++t){
        म_लिखो("\nTEST: %d\n\n", t+1);
        test_function(&test_struct[t]);
    }
    परत 0;
}
