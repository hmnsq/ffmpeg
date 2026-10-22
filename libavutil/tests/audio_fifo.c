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
#समावेश "config.h"

#समावेश <stdlib.h>
#समावेश <stdio.h>
#समावेश <inttypes.h>
#समावेश "libavutil/mem.h"
#समावेश "libavutil/audio_fifo.c"

#घोषणा MAX_CHANNELS    32


प्रकार काष्ठा TestStruct {
    स्थिर क्रमागत AVSampleFormat format;
    स्थिर पूर्णांक nb_ch;
    व्योम स्थिर *तथ्य_planes[MAX_CHANNELS];
    स्थिर पूर्णांक nb_samples_pch;
} TestStruct;

अटल स्थिर uint8_t तथ्य_U8 [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
अटल स्थिर int16_t तथ्य_S16[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
अटल स्थिर भग्न   तथ्य_FLT[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

अटल स्थिर TestStruct test_struct[] = {
    {.format = AV_SAMPLE_FMT_U8   , .nb_ch = 1, .तथ्य_planes = {तथ्य_U8 ,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_U8P  , .nb_ch = 2, .तथ्य_planes = {तथ्य_U8 , तथ्य_U8 +6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_S16  , .nb_ch = 1, .तथ्य_planes = {तथ्य_S16,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_S16P , .nb_ch = 2, .तथ्य_planes = {तथ्य_S16, तथ्य_S16+6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_FLT  , .nb_ch = 1, .तथ्य_planes = {तथ्य_FLT,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_FLTP , .nb_ch = 2, .तथ्य_planes = {तथ्य_FLT, तथ्य_FLT+6, }, .nb_samples_pch = 6 }
};

अटल व्योम free_तथ्य_planes(AVAudioFifo *afifo, व्योम **output_तथ्य)
{
    पूर्णांक i;
    क्रम (i = 0; i < afifo->nb_buffers; ++i){
        av_freep(&output_तथ्य[i]);
    }
    av_freep(&output_तथ्य);
}

अटल व्योम ERROR(स्थिर अक्षर *str)
{
    ख_लिखो(मानक_त्रुटि, "%s\n", str);
    निकास(1);
}

अटल व्योम print_audio_bytes(स्थिर TestStruct *test_sample, व्योम **तथ्य_planes, पूर्णांक nb_samples)
{
    पूर्णांक p, b, f;
    पूर्णांक byte_offset      = av_get_bytes_per_sample(test_sample->format);
    पूर्णांक buffers          = av_sample_fmt_is_planar(test_sample->format)
                                         ? test_sample->nb_ch : 1;
    पूर्णांक पंक्ति_आकार        = (buffers > 1) ? nb_samples * byte_offset
                                         : nb_samples * byte_offset * test_sample->nb_ch;
    क्रम (p = 0; p < buffers; ++p){
        क्रम(b = 0; b < पंक्ति_आकार; b+=byte_offset){
            क्रम (f = 0; f < byte_offset; f++){
                पूर्णांक order = !HAVE_BIGENDIAN ? (byte_offset - f - 1) : f;
                म_लिखो("%02x", *((uint8_t*)तथ्य_planes[p] + b + order));
            }
            अगर (b + byte_offset < पंक्ति_आकार)
                अक्षर_दो(' ');
        }
        अक्षर_दो('\n');
    }
}

अटल पूर्णांक read_samples_from_audio_fifo(AVAudioFifo* afifo, व्योम ***output, पूर्णांक nb_samples)
{
    पूर्णांक i;
    पूर्णांक samples        = FFMIN(nb_samples, afifo->nb_samples);
    पूर्णांक tot_elements   = !av_sample_fmt_is_planar(afifo->sample_fmt)
                         ? samples : afifo->channels * samples;
    व्योम **तथ्य_planes = av_malloc_array(afifo->nb_buffers, माप(व्योम*));
    अगर (!तथ्य_planes)
        ERROR("failed to allocate memory!");
    अगर (*output)
        free_तथ्य_planes(afifo, *output);
    *output            = तथ्य_planes;

    क्रम (i = 0; i < afifo->nb_buffers; ++i){
        तथ्य_planes[i] = av_malloc_array(tot_elements, afifo->sample_आकार);
        अगर (!तथ्य_planes[i])
            ERROR("failed to allocate memory!");
    }

    वापस av_audio_fifo_read(afifo, *output, nb_samples);
}

अटल पूर्णांक write_samples_to_audio_fifo(AVAudioFifo* afifo, स्थिर TestStruct *test_sample,
                                       पूर्णांक nb_samples, पूर्णांक offset)
{
    पूर्णांक offset_आकार, i;
    व्योम *तथ्य_planes[MAX_CHANNELS];

    अगर(nb_samples > test_sample->nb_samples_pch - offset){
        वापस 0;
    }
    अगर(offset >= test_sample->nb_samples_pch){
        वापस 0;
    }
    offset_आकार  = offset * afifo->sample_आकार;

    क्रम (i = 0; i < afifo->nb_buffers ; ++i){
        तथ्य_planes[i] = (uint8_t*)test_sample->तथ्य_planes[i] + offset_आकार;
    }

    वापस av_audio_fifo_write(afifo, तथ्य_planes, nb_samples);
}

अटल व्योम test_function(स्थिर TestStruct *test_sample)
{
    पूर्णांक ret, i;
    व्योम **output_तथ्य  = शून्य;
    AVAudioFifo *afifo  = av_audio_fifo_alloc(test_sample->format, test_sample->nb_ch,
                                            test_sample->nb_samples_pch);
    अगर (!afifo) {
        ERROR("ERROR: av_audio_fifo_alloc returned NULL!");
    }
    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    अगर (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    म_लिखो("written: %d\n", ret);

    ret = write_samples_to_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    अगर (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    म_लिखो("written: %d\n", ret);
    म_लिखो("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_आकार(afifo));

    ret = read_samples_from_audio_fifo(afifo, &output_तथ्य, test_sample->nb_samples_pch);
    अगर (ret < 0){
        ERROR("ERROR: av_audio_fifo_read failed!");
    }
    म_लिखो("read: %d\n", ret);
    print_audio_bytes(test_sample, output_तथ्य, ret);
    म_लिखो("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_आकार(afifo));

    /* test av_audio_fifo_peek */
    ret = av_audio_fifo_peek(afifo, output_तथ्य, afifo->nb_samples);
    अगर (ret < 0){
        ERROR("ERROR: av_audio_fifo_peek failed!");
    }
    म_लिखो("peek:\n");
    print_audio_bytes(test_sample, output_तथ्य, ret);
    म_लिखो("\n");

    /* test av_audio_fifo_peek_at */
    म_लिखो("peek_at:\n");
    क्रम (i = 0; i < afifo->nb_samples; ++i){
        ret = av_audio_fifo_peek_at(afifo, output_तथ्य, 1, i);
        अगर (ret < 0){
            ERROR("ERROR: av_audio_fifo_peek_at failed!");
        }
        म_लिखो("%d:\n", i);
        print_audio_bytes(test_sample, output_तथ्य, ret);
    }
    म_लिखो("\n");

    /* test av_audio_fifo_drain */
    ret = av_audio_fifo_drain(afifo, afifo->nb_samples);
    अगर (ret < 0){
        ERROR("ERROR: av_audio_fifo_drain failed!");
    }
    अगर (afifo->nb_samples){
        ERROR("drain failed to flush all samples in audio_fifo!");
    }

    /* deallocate */
    free_तथ्य_planes(afifo, output_तथ्य);
    av_audio_fifo_free(afifo);
}

पूर्णांक मुख्य(व्योम)
{
    पूर्णांक t, tests = माप(test_struct)/माप(test_struct[0]);

    क्रम (t = 0; t < tests; ++t){
        म_लिखो("\nTEST: %d\n\n", t+1);
        test_function(&test_struct[t]);
    }
    वापस 0;
}
