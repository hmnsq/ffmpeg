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
#అన్తర్భావ "config.h"

#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <inttypes.h>
#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/audio_fifo.c"

#నిర్వచించు MAX_CHANNELS    32


రకనిర్వచనం నిర్మాణం TestStruct {
    స్థిరరాశి గణన AVSampleFormat format;
    స్థిరరాశి పూర్ణాంకం nb_ch;
    శూన్య స్థిరరాశి *దత్తాంశం_planes[MAX_CHANNELS];
    స్థిరరాశి పూర్ణాంకం nb_samples_pch;
} TestStruct;

స్థిర స్థిరరాశి uint8_t దత్తాంశం_U8 [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
స్థిర స్థిరరాశి int16_t దత్తాంశం_S16[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
స్థిర స్థిరరాశి దశాంశం   దత్తాంశం_FLT[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

స్థిర స్థిరరాశి TestStruct test_struct[] = {
    {.format = AV_SAMPLE_FMT_U8   , .nb_ch = 1, .దత్తాంశం_planes = {దత్తాంశం_U8 ,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_U8P  , .nb_ch = 2, .దత్తాంశం_planes = {దత్తాంశం_U8 , దత్తాంశం_U8 +6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_S16  , .nb_ch = 1, .దత్తాంశం_planes = {దత్తాంశం_S16,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_S16P , .nb_ch = 2, .దత్తాంశం_planes = {దత్తాంశం_S16, దత్తాంశం_S16+6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_FLT  , .nb_ch = 1, .దత్తాంశం_planes = {దత్తాంశం_FLT,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_FLTP , .nb_ch = 2, .దత్తాంశం_planes = {దత్తాంశం_FLT, దత్తాంశం_FLT+6, }, .nb_samples_pch = 6 }
};

స్థిర శూన్య free_దత్తాంశం_planes(AVAudioFifo *afifo, శూన్య **output_దత్తాంశం)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < afifo->nb_buffers; ++i){
        av_freep(&output_దత్తాంశం[i]);
    }
    av_freep(&output_దత్తాంశం);
}

స్థిర శూన్య ERROR(స్థిరరాశి అక్షరం *str)
{
    fprintf(stderr, "%s\n", str);
    నిష్క్రమించు(1);
}

స్థిర శూన్య print_audio_బైట్లు(స్థిరరాశి TestStruct *test_sample, శూన్య **దత్తాంశం_planes, పూర్ణాంకం nb_samples)
{
    పూర్ణాంకం p, b, f;
    పూర్ణాంకం byte_స్థానభ్రంశం      = av_get_బైట్లు_చొప్పున_sample(test_sample->format);
    పూర్ణాంకం buffers          = av_sample_fmt_is_planar(test_sample->format)
                                         ? test_sample->nb_ch : 1;
    పూర్ణాంకం పంక్తి_కొలత        = (buffers > 1) ? nb_samples * byte_స్థానభ్రంశం
                                         : nb_samples * byte_స్థానభ్రంశం * test_sample->nb_ch;
    కొరకు (p = 0; p < buffers; ++p){
        కొరకు(b = 0; b < పంక్తి_కొలత; b+=byte_స్థానభ్రంశం){
            కొరకు (f = 0; f < byte_స్థానభ్రంశం; f++){
                పూర్ణాంకం క్రమం = !HAVE_BIGENDIAN ? (byte_స్థానభ్రంశం - f - 1) : f;
                రాయి("%02x", *((uint8_t*)దత్తాంశం_planes[p] + b + క్రమం));
            }
            ఒకవేళ (b + byte_స్థానభ్రంశం < పంక్తి_కొలత)
                అక్షరం_రాయి(' ');
        }
        అక్షరం_రాయి('\n');
    }
}

స్థిర పూర్ణాంకం read_samples_from_audio_fifo(AVAudioFifo* afifo, శూన్య ***output, పూర్ణాంకం nb_samples)
{
    పూర్ణాంకం i;
    పూర్ణాంకం samples        = FFMIN(nb_samples, afifo->nb_samples);
    పూర్ణాంకం tot_elements   = !av_sample_fmt_is_planar(afifo->sample_fmt)
                         ? samples : afifo->channels * samples;
    శూన్య **దత్తాంశం_planes = av_malloc_array(afifo->nb_buffers, పరిమాణం(శూన్య*));
    ఒకవేళ (!దత్తాంశం_planes)
        ERROR("failed to allocate memory!");
    ఒకవేళ (*output)
        free_దత్తాంశం_planes(afifo, *output);
    *output            = దత్తాంశం_planes;

    కొరకు (i = 0; i < afifo->nb_buffers; ++i){
        దత్తాంశం_planes[i] = av_malloc_array(tot_elements, afifo->sample_కొలత);
        ఒకవేళ (!దత్తాంశం_planes[i])
            ERROR("failed to allocate memory!");
    }

    తిరిగి av_audio_fifo_read(afifo, *output, nb_samples);
}

స్థిర పూర్ణాంకం write_samples_గమ్యం_audio_fifo(AVAudioFifo* afifo, స్థిరరాశి TestStruct *test_sample,
                                       పూర్ణాంకం nb_samples, పూర్ణాంకం స్థానభ్రంశం)
{
    పూర్ణాంకం స్థానభ్రంశం_కొలత, i;
    శూన్య *దత్తాంశం_planes[MAX_CHANNELS];

    ఒకవేళ(nb_samples > test_sample->nb_samples_pch - స్థానభ్రంశం){
        తిరిగి 0;
    }
    ఒకవేళ(స్థానభ్రంశం >= test_sample->nb_samples_pch){
        తిరిగి 0;
    }
    స్థానభ్రంశం_కొలత  = స్థానభ్రంశం * afifo->sample_కొలత;

    కొరకు (i = 0; i < afifo->nb_buffers ; ++i){
        దత్తాంశం_planes[i] = (uint8_t*)test_sample->దత్తాంశం_planes[i] + స్థానభ్రంశం_కొలత;
    }

    తిరిగి av_audio_fifo_write(afifo, దత్తాంశం_planes, nb_samples);
}

స్థిర శూన్య test_function(స్థిరరాశి TestStruct *test_sample)
{
    పూర్ణాంకం ret, i;
    శూన్య **output_దత్తాంశం  = ఖాళీ;
    AVAudioFifo *afifo  = av_audio_fifo_alloc(test_sample->format, test_sample->nb_ch,
                                            test_sample->nb_samples_pch);
    ఒకవేళ (!afifo) {
        ERROR("ERROR: av_audio_fifo_alloc returned NULL!");
    }
    ret = write_samples_గమ్యం_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    ఒకవేళ (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    రాయి("written: %d\n", ret);

    ret = write_samples_గమ్యం_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    ఒకవేళ (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    రాయి("written: %d\n", ret);
    రాయి("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_కొలత(afifo));

    ret = read_samples_from_audio_fifo(afifo, &output_దత్తాంశం, test_sample->nb_samples_pch);
    ఒకవేళ (ret < 0){
        ERROR("ERROR: av_audio_fifo_read failed!");
    }
    రాయి("read: %d\n", ret);
    print_audio_బైట్లు(test_sample, output_దత్తాంశం, ret);
    రాయి("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_కొలత(afifo));

    /* test av_audio_fifo_peek */
    ret = av_audio_fifo_peek(afifo, output_దత్తాంశం, afifo->nb_samples);
    ఒకవేళ (ret < 0){
        ERROR("ERROR: av_audio_fifo_peek failed!");
    }
    రాయి("peek:\n");
    print_audio_బైట్లు(test_sample, output_దత్తాంశం, ret);
    రాయి("\n");

    /* test av_audio_fifo_peek_at */
    రాయి("peek_at:\n");
    కొరకు (i = 0; i < afifo->nb_samples; ++i){
        ret = av_audio_fifo_peek_at(afifo, output_దత్తాంశం, 1, i);
        ఒకవేళ (ret < 0){
            ERROR("ERROR: av_audio_fifo_peek_at failed!");
        }
        రాయి("%d:\n", i);
        print_audio_బైట్లు(test_sample, output_దత్తాంశం, ret);
    }
    రాయి("\n");

    /* test av_audio_fifo_drain */
    ret = av_audio_fifo_drain(afifo, afifo->nb_samples);
    ఒకవేళ (ret < 0){
        ERROR("ERROR: av_audio_fifo_drain failed!");
    }
    ఒకవేళ (afifo->nb_samples){
        ERROR("drain failed to flush all samples in audio_fifo!");
    }

    /* deallocate */
    free_దత్తాంశం_planes(afifo, output_దత్తాంశం);
    av_audio_fifo_free(afifo);
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    పూర్ణాంకం t, tests = పరిమాణం(test_struct)/పరిమాణం(test_struct[0]);

    కొరకు (t = 0; t < tests; ++t){
        రాయి("\nTEST: %d\n\n", t+1);
        test_function(&test_struct[t]);
    }
    తిరిగి 0;
}
