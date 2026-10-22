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
#ضمن "config.h"

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <inttypes.h>
#ضمن "libavutil/mem.h"
#ضمن "libavutil/audio_fifo.c"

#تعریف_کن MAX_CHANNELS    32


تعريفنوع بنية TestStruct {
    ثابت تعداد AVSampleFormat format;
    ثابت صحيح nb_ch;
    فراغ ثابت *داده_planes[MAX_CHANNELS];
    ثابت صحيح nb_samples_pch;
} TestStruct;

ساكن ثابت uint8_t داده_U8 [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
ساكن ثابت int16_t داده_S16[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
ساكن ثابت عائم   داده_FLT[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

ساكن ثابت TestStruct test_struct[] = {
    {.format = AV_SAMPLE_FMT_U8   , .nb_ch = 1, .داده_planes = {داده_U8 ,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_U8P  , .nb_ch = 2, .داده_planes = {داده_U8 , داده_U8 +6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_S16  , .nb_ch = 1, .داده_planes = {داده_S16,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_S16P , .nb_ch = 2, .داده_planes = {داده_S16, داده_S16+6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_FLT  , .nb_ch = 1, .داده_planes = {داده_FLT,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_FLTP , .nb_ch = 2, .داده_planes = {داده_FLT, داده_FLT+6, }, .nb_samples_pch = 6 }
};

ساكن فراغ free_داده_planes(AVAudioFifo *afifo, فراغ **output_داده)
{
    صحيح i;
    لكل (i = 0; i < afifo->nb_buffers; ++i){
        av_freep(&output_داده[i]);
    }
    av_freep(&output_داده);
}

ساكن فراغ ERROR(ثابت حرف *str)
{
    fprintf(stderr, "%s\n", str);
    خروج(1);
}

ساكن فراغ print_audio_بایتها(ثابت TestStruct *test_sample, فراغ **داده_planes, صحيح nb_samples)
{
    صحيح p, b, f;
    صحيح byte_جابه_جایی      = av_get_بایتها_در_هر_sample(test_sample->format);
    صحيح buffers          = av_sample_fmt_is_planar(test_sample->format)
                                         ? test_sample->nb_ch : 1;
    صحيح سطر_اندازه        = (buffers > 1) ? nb_samples * byte_جابه_جایی
                                         : nb_samples * byte_جابه_جایی * test_sample->nb_ch;
    لكل (p = 0; p < buffers; ++p){
        لكل(b = 0; b < سطر_اندازه; b+=byte_جابه_جایی){
            لكل (f = 0; f < byte_جابه_جایی; f++){
                صحيح ترتیب = !HAVE_BIGENDIAN ? (byte_جابه_جایی - f - 1) : f;
                چاپ_کن("%02x", *((uint8_t*)داده_planes[p] + b + ترتیب));
            }
            إذا (b + byte_جابه_جایی < سطر_اندازه)
                حرف_چاپ_کن(' ');
        }
        حرف_چاپ_کن('\n');
    }
}

ساكن صحيح read_samples_from_audio_fifo(AVAudioFifo* afifo, فراغ ***output, صحيح nb_samples)
{
    صحيح i;
    صحيح samples        = FFMIN(nb_samples, afifo->nb_samples);
    صحيح tot_elements   = !av_sample_fmt_is_planar(afifo->sample_fmt)
                         ? samples : afifo->channels * samples;
    فراغ **داده_planes = av_malloc_array(afifo->nb_buffers, حجم(فراغ*));
    إذا (!داده_planes)
        ERROR("failed to allocate memory!");
    إذا (*output)
        free_داده_planes(afifo, *output);
    *output            = داده_planes;

    لكل (i = 0; i < afifo->nb_buffers; ++i){
        داده_planes[i] = av_malloc_array(tot_elements, afifo->sample_اندازه);
        إذا (!داده_planes[i])
            ERROR("failed to allocate memory!");
    }

    أرجع av_audio_fifo_read(afifo, *output, nb_samples);
}

ساكن صحيح write_samples_مقصد_audio_fifo(AVAudioFifo* afifo, ثابت TestStruct *test_sample,
                                       صحيح nb_samples, صحيح جابه_جایی)
{
    صحيح جابه_جایی_اندازه, i;
    فراغ *داده_planes[MAX_CHANNELS];

    إذا(nb_samples > test_sample->nb_samples_pch - جابه_جایی){
        أرجع 0;
    }
    إذا(جابه_جایی >= test_sample->nb_samples_pch){
        أرجع 0;
    }
    جابه_جایی_اندازه  = جابه_جایی * afifo->sample_اندازه;

    لكل (i = 0; i < afifo->nb_buffers ; ++i){
        داده_planes[i] = (uint8_t*)test_sample->داده_planes[i] + جابه_جایی_اندازه;
    }

    أرجع av_audio_fifo_write(afifo, داده_planes, nb_samples);
}

ساكن فراغ test_function(ثابت TestStruct *test_sample)
{
    صحيح ret, i;
    فراغ **output_داده  = عدم;
    AVAudioFifo *afifo  = av_audio_fifo_alloc(test_sample->format, test_sample->nb_ch,
                                            test_sample->nb_samples_pch);
    إذا (!afifo) {
        ERROR("ERROR: av_audio_fifo_alloc returned NULL!");
    }
    ret = write_samples_مقصد_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    إذا (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    چاپ_کن("written: %d\n", ret);

    ret = write_samples_مقصد_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    إذا (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    چاپ_کن("written: %d\n", ret);
    چاپ_کن("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_اندازه(afifo));

    ret = read_samples_from_audio_fifo(afifo, &output_داده, test_sample->nb_samples_pch);
    إذا (ret < 0){
        ERROR("ERROR: av_audio_fifo_read failed!");
    }
    چاپ_کن("read: %d\n", ret);
    print_audio_بایتها(test_sample, output_داده, ret);
    چاپ_کن("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_اندازه(afifo));

    /* test av_audio_fifo_peek */
    ret = av_audio_fifo_peek(afifo, output_داده, afifo->nb_samples);
    إذا (ret < 0){
        ERROR("ERROR: av_audio_fifo_peek failed!");
    }
    چاپ_کن("peek:\n");
    print_audio_بایتها(test_sample, output_داده, ret);
    چاپ_کن("\n");

    /* test av_audio_fifo_peek_at */
    چاپ_کن("peek_at:\n");
    لكل (i = 0; i < afifo->nb_samples; ++i){
        ret = av_audio_fifo_peek_at(afifo, output_داده, 1, i);
        إذا (ret < 0){
            ERROR("ERROR: av_audio_fifo_peek_at failed!");
        }
        چاپ_کن("%d:\n", i);
        print_audio_بایتها(test_sample, output_داده, ret);
    }
    چاپ_کن("\n");

    /* test av_audio_fifo_drain */
    ret = av_audio_fifo_drain(afifo, afifo->nb_samples);
    إذا (ret < 0){
        ERROR("ERROR: av_audio_fifo_drain failed!");
    }
    إذا (afifo->nb_samples){
        ERROR("drain failed to flush all samples in audio_fifo!");
    }

    /* deallocate */
    free_داده_planes(afifo, output_داده);
    av_audio_fifo_free(afifo);
}

صحيح اصلی(فراغ)
{
    صحيح t, tests = حجم(test_struct)/حجم(test_struct[0]);

    لكل (t = 0; t < tests; ++t){
        چاپ_کن("\nTEST: %d\n\n", t+1);
        test_function(&test_struct[t]);
    }
    أرجع 0;
}
