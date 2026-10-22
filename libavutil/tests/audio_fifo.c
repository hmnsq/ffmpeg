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

#परिभाषय MAX_CHANNELS    32


प्रकारनिर्देश संरचना TestStruct {
    ध्रुव गणना AVSampleFormat format;
    ध्रुव पूर्णाङ्क nb_ch;
    शून्य ध्रुव *दत्त_planes[MAX_CHANNELS];
    ध्रुव पूर्णाङ्क nb_samples_pch;
} TestStruct;

स्थिर ध्रुव uint8_t दत्त_U8 [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
स्थिर ध्रुव int16_t दत्त_S16[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
स्थिर ध्रुव भिन्न   दत्त_FLT[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

स्थिर ध्रुव TestStruct test_struct[] = {
    {.format = AV_SAMPLE_FMT_U8   , .nb_ch = 1, .दत्त_planes = {दत्त_U8 ,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_U8P  , .nb_ch = 2, .दत्त_planes = {दत्त_U8 , दत्त_U8 +6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_S16  , .nb_ch = 1, .दत्त_planes = {दत्त_S16,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_S16P , .nb_ch = 2, .दत्त_planes = {दत्त_S16, दत्त_S16+6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_FLT  , .nb_ch = 1, .दत्त_planes = {दत्त_FLT,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_FLTP , .nb_ch = 2, .दत्त_planes = {दत्त_FLT, दत्त_FLT+6, }, .nb_samples_pch = 6 }
};

स्थिर शून्य free_दत्त_planes(AVAudioFifo *afifo, शून्य **output_दत्त)
{
    पूर्णाङ्क i;
    प्रति (i = 0; i < afifo->nb_buffers; ++i){
        av_freep(&output_दत्त[i]);
    }
    av_freep(&output_दत्त);
}

स्थिर शून्य ERROR(ध्रुव वर्ण *str)
{
    fprintf(stderr, "%s\n", str);
    निर्गच्छ(1);
}

स्थिर शून्य print_audio_अष्टकानि(ध्रुव TestStruct *test_sample, शून्य **दत्त_planes, पूर्णाङ्क nb_samples)
{
    पूर्णाङ्क p, b, f;
    पूर्णाङ्क byte_विस्थापनम्      = av_get_अष्टकानि_प्रत्येकम्_sample(test_sample->format);
    पूर्णाङ्क buffers          = av_sample_fmt_is_planar(test_sample->format)
                                         ? test_sample->nb_ch : 1;
    पूर्णाङ्क पङ्क्तिः_आकार        = (buffers > 1) ? nb_samples * byte_विस्थापनम्
                                         : nb_samples * byte_विस्थापनम् * test_sample->nb_ch;
    प्रति (p = 0; p < buffers; ++p){
        प्रति(b = 0; b < पङ्क्तिः_आकार; b+=byte_विस्थापनम्){
            प्रति (f = 0; f < byte_विस्थापनम्; f++){
                पूर्णाङ्क क्रमः = !HAVE_BIGENDIAN ? (byte_विस्थापनम् - f - 1) : f;
                प्रारूप_लिख("%02x", *((uint8_t*)दत्त_planes[p] + b + क्रमः));
            }
            यदि (b + byte_विस्थापनम् < पङ्क्तिः_आकार)
                अक्षरं_लिख(' ');
        }
        अक्षरं_लिख('\n');
    }
}

स्थिर पूर्णाङ्क read_samples_from_audio_fifo(AVAudioFifo* afifo, शून्य ***output, पूर्णाङ्क nb_samples)
{
    पूर्णाङ्क i;
    पूर्णाङ्क samples        = FFMIN(nb_samples, afifo->nb_samples);
    पूर्णाङ्क tot_elements   = !av_sample_fmt_is_planar(afifo->sample_fmt)
                         ? samples : afifo->channels * samples;
    शून्य **दत्त_planes = av_malloc_array(afifo->nb_buffers, परिमाण(शून्य*));
    यदि (!दत्त_planes)
        ERROR("failed to allocate memory!");
    यदि (*output)
        free_दत्त_planes(afifo, *output);
    *output            = दत्त_planes;

    प्रति (i = 0; i < afifo->nb_buffers; ++i){
        दत्त_planes[i] = av_malloc_array(tot_elements, afifo->sample_आकार);
        यदि (!दत्त_planes[i])
            ERROR("failed to allocate memory!");
    }

    प्रत्यागम av_audio_fifo_read(afifo, *output, nb_samples);
}

स्थिर पूर्णाङ्क write_samples_गन्तव्यम्_audio_fifo(AVAudioFifo* afifo, ध्रुव TestStruct *test_sample,
                                       पूर्णाङ्क nb_samples, पूर्णाङ्क विस्थापनम्)
{
    पूर्णाङ्क विस्थापनम्_आकार, i;
    शून्य *दत्त_planes[MAX_CHANNELS];

    यदि(nb_samples > test_sample->nb_samples_pch - विस्थापनम्){
        प्रत्यागम 0;
    }
    यदि(विस्थापनम् >= test_sample->nb_samples_pch){
        प्रत्यागम 0;
    }
    विस्थापनम्_आकार  = विस्थापनम् * afifo->sample_आकार;

    प्रति (i = 0; i < afifo->nb_buffers ; ++i){
        दत्त_planes[i] = (uint8_t*)test_sample->दत्त_planes[i] + विस्थापनम्_आकार;
    }

    प्रत्यागम av_audio_fifo_write(afifo, दत्त_planes, nb_samples);
}

स्थिर शून्य test_function(ध्रुव TestStruct *test_sample)
{
    पूर्णाङ्क ret, i;
    शून्य **output_दत्त  = रिक्त;
    AVAudioFifo *afifo  = av_audio_fifo_alloc(test_sample->format, test_sample->nb_ch,
                                            test_sample->nb_samples_pch);
    यदि (!afifo) {
        ERROR("ERROR: av_audio_fifo_alloc returned NULL!");
    }
    ret = write_samples_गन्तव्यम्_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    यदि (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    प्रारूप_लिख("written: %d\n", ret);

    ret = write_samples_गन्तव्यम्_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    यदि (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    प्रारूप_लिख("written: %d\n", ret);
    प्रारूप_लिख("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_आकार(afifo));

    ret = read_samples_from_audio_fifo(afifo, &output_दत्त, test_sample->nb_samples_pch);
    यदि (ret < 0){
        ERROR("ERROR: av_audio_fifo_read failed!");
    }
    प्रारूप_लिख("read: %d\n", ret);
    print_audio_अष्टकानि(test_sample, output_दत्त, ret);
    प्रारूप_लिख("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_आकार(afifo));

    /* test av_audio_fifo_peek */
    ret = av_audio_fifo_peek(afifo, output_दत्त, afifo->nb_samples);
    यदि (ret < 0){
        ERROR("ERROR: av_audio_fifo_peek failed!");
    }
    प्रारूप_लिख("peek:\n");
    print_audio_अष्टकानि(test_sample, output_दत्त, ret);
    प्रारूप_लिख("\n");

    /* test av_audio_fifo_peek_at */
    प्रारूप_लिख("peek_at:\n");
    प्रति (i = 0; i < afifo->nb_samples; ++i){
        ret = av_audio_fifo_peek_at(afifo, output_दत्त, 1, i);
        यदि (ret < 0){
            ERROR("ERROR: av_audio_fifo_peek_at failed!");
        }
        प्रारूप_लिख("%d:\n", i);
        print_audio_अष्टकानि(test_sample, output_दत्त, ret);
    }
    प्रारूप_लिख("\n");

    /* test av_audio_fifo_drain */
    ret = av_audio_fifo_drain(afifo, afifo->nb_samples);
    यदि (ret < 0){
        ERROR("ERROR: av_audio_fifo_drain failed!");
    }
    यदि (afifo->nb_samples){
        ERROR("drain failed to flush all samples in audio_fifo!");
    }

    /* deallocate */
    free_दत्त_planes(afifo, output_दत्त);
    av_audio_fifo_free(afifo);
}

पूर्णाङ्क मुख्यम्(शून्य)
{
    पूर्णाङ्क t, tests = परिमाण(test_struct)/परिमाण(test_struct[0]);

    प्रति (t = 0; t < tests; ++t){
        प्रारूप_लिख("\nTEST: %d\n\n", t+1);
        test_function(&test_struct[t]);
    }
    प्रत्यागम 0;
}
