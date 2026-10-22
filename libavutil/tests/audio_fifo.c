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
#شامل "config.h"

#شامل <stdlib.h>
#شامل <stdio.h>
#شامل <inttypes.h>
#شامل "libavutil/mem.h"
#شامل "libavutil/audio_fifo.c"

#تعریف_کرو MAX_CHANNELS    32


قسمتعریف ساخت TestStruct {
    ثابت شمار AVSampleFormat format;
    ثابت صحیح nb_ch;
    خالی ثابت *ڈیٹا_planes[MAX_CHANNELS];
    ثابت صحیح nb_samples_pch;
} TestStruct;

ساکن ثابت uint8_t ڈیٹا_U8 [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
ساکن ثابت int16_t ڈیٹا_S16[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11                        };
ساکن ثابت اعشاری   ڈیٹا_FLT[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};

ساکن ثابت TestStruct test_struct[] = {
    {.format = AV_SAMPLE_FMT_U8   , .nb_ch = 1, .ڈیٹا_planes = {ڈیٹا_U8 ,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_U8P  , .nb_ch = 2, .ڈیٹا_planes = {ڈیٹا_U8 , ڈیٹا_U8 +6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_S16  , .nb_ch = 1, .ڈیٹا_planes = {ڈیٹا_S16,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_S16P , .nb_ch = 2, .ڈیٹا_planes = {ڈیٹا_S16, ڈیٹا_S16+6, }, .nb_samples_pch = 6 },
    {.format = AV_SAMPLE_FMT_FLT  , .nb_ch = 1, .ڈیٹا_planes = {ڈیٹا_FLT,             }, .nb_samples_pch = 12},
    {.format = AV_SAMPLE_FMT_FLTP , .nb_ch = 2, .ڈیٹا_planes = {ڈیٹا_FLT, ڈیٹا_FLT+6, }, .nb_samples_pch = 6 }
};

ساکن خالی free_ڈیٹا_planes(AVAudioFifo *afifo, خالی **output_ڈیٹا)
{
    صحیح i;
    برائے (i = 0; i < afifo->nb_buffers; ++i){
        av_freep(&output_ڈیٹا[i]);
    }
    av_freep(&output_ڈیٹا);
}

ساکن خالی ERROR(ثابت حرف *str)
{
    fprintf(stderr, "%s\n", str);
    باہر_نکلو(1);
}

ساکن خالی print_audio_بائٹیں(ثابت TestStruct *test_sample, خالی **ڈیٹا_planes, صحیح nb_samples)
{
    صحیح p, b, f;
    صحیح byte_انحراف      = av_get_بائٹیں_فی_sample(test_sample->format);
    صحیح buffers          = av_sample_fmt_is_planar(test_sample->format)
                                         ? test_sample->nb_ch : 1;
    صحیح سطر_سائز        = (buffers > 1) ? nb_samples * byte_انحراف
                                         : nb_samples * byte_انحراف * test_sample->nb_ch;
    برائے (p = 0; p < buffers; ++p){
        برائے(b = 0; b < سطر_سائز; b+=byte_انحراف){
            برائے (f = 0; f < byte_انحراف; f++){
                صحیح ترتیب = !HAVE_BIGENDIAN ? (byte_انحراف - f - 1) : f;
                لکھو("%02x", *((uint8_t*)ڈیٹا_planes[p] + b + ترتیب));
            }
            اگر (b + byte_انحراف < سطر_سائز)
                حرف_لکھو(' ');
        }
        حرف_لکھو('\n');
    }
}

ساکن صحیح read_samples_from_audio_fifo(AVAudioFifo* afifo, خالی ***output, صحیح nb_samples)
{
    صحیح i;
    صحیح samples        = FFMIN(nb_samples, afifo->nb_samples);
    صحیح tot_elements   = !av_sample_fmt_is_planar(afifo->sample_fmt)
                         ? samples : afifo->channels * samples;
    خالی **ڈیٹا_planes = av_malloc_array(afifo->nb_buffers, حجم(خالی*));
    اگر (!ڈیٹا_planes)
        ERROR("failed to allocate memory!");
    اگر (*output)
        free_ڈیٹا_planes(afifo, *output);
    *output            = ڈیٹا_planes;

    برائے (i = 0; i < afifo->nb_buffers; ++i){
        ڈیٹا_planes[i] = av_malloc_array(tot_elements, afifo->sample_سائز);
        اگر (!ڈیٹا_planes[i])
            ERROR("failed to allocate memory!");
    }

    واپس av_audio_fifo_read(afifo, *output, nb_samples);
}

ساکن صحیح write_samples_مقصد_audio_fifo(AVAudioFifo* afifo, ثابت TestStruct *test_sample,
                                       صحیح nb_samples, صحیح انحراف)
{
    صحیح انحراف_سائز, i;
    خالی *ڈیٹا_planes[MAX_CHANNELS];

    اگر(nb_samples > test_sample->nb_samples_pch - انحراف){
        واپس 0;
    }
    اگر(انحراف >= test_sample->nb_samples_pch){
        واپس 0;
    }
    انحراف_سائز  = انحراف * afifo->sample_سائز;

    برائے (i = 0; i < afifo->nb_buffers ; ++i){
        ڈیٹا_planes[i] = (uint8_t*)test_sample->ڈیٹا_planes[i] + انحراف_سائز;
    }

    واپس av_audio_fifo_write(afifo, ڈیٹا_planes, nb_samples);
}

ساکن خالی test_function(ثابت TestStruct *test_sample)
{
    صحیح ret, i;
    خالی **output_ڈیٹا  = تہی;
    AVAudioFifo *afifo  = av_audio_fifo_alloc(test_sample->format, test_sample->nb_ch,
                                            test_sample->nb_samples_pch);
    اگر (!afifo) {
        ERROR("ERROR: av_audio_fifo_alloc returned NULL!");
    }
    ret = write_samples_مقصد_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    اگر (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    لکھو("written: %d\n", ret);

    ret = write_samples_مقصد_audio_fifo(afifo, test_sample, test_sample->nb_samples_pch, 0);
    اگر (ret < 0){
        ERROR("ERROR: av_audio_fifo_write failed!");
    }
    لکھو("written: %d\n", ret);
    لکھو("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_سائز(afifo));

    ret = read_samples_from_audio_fifo(afifo, &output_ڈیٹا, test_sample->nb_samples_pch);
    اگر (ret < 0){
        ERROR("ERROR: av_audio_fifo_read failed!");
    }
    لکھو("read: %d\n", ret);
    print_audio_بائٹیں(test_sample, output_ڈیٹا, ret);
    لکھو("remaining samples in audio_fifo: %d\n\n", av_audio_fifo_سائز(afifo));

    /* test av_audio_fifo_peek */
    ret = av_audio_fifo_peek(afifo, output_ڈیٹا, afifo->nb_samples);
    اگر (ret < 0){
        ERROR("ERROR: av_audio_fifo_peek failed!");
    }
    لکھو("peek:\n");
    print_audio_بائٹیں(test_sample, output_ڈیٹا, ret);
    لکھو("\n");

    /* test av_audio_fifo_peek_at */
    لکھو("peek_at:\n");
    برائے (i = 0; i < afifo->nb_samples; ++i){
        ret = av_audio_fifo_peek_at(afifo, output_ڈیٹا, 1, i);
        اگر (ret < 0){
            ERROR("ERROR: av_audio_fifo_peek_at failed!");
        }
        لکھو("%d:\n", i);
        print_audio_بائٹیں(test_sample, output_ڈیٹا, ret);
    }
    لکھو("\n");

    /* test av_audio_fifo_drain */
    ret = av_audio_fifo_drain(afifo, afifo->nb_samples);
    اگر (ret < 0){
        ERROR("ERROR: av_audio_fifo_drain failed!");
    }
    اگر (afifo->nb_samples){
        ERROR("drain failed to flush all samples in audio_fifo!");
    }

    /* deallocate */
    free_ڈیٹا_planes(afifo, output_ڈیٹا);
    av_audio_fifo_free(afifo);
}

صحیح مین(خالی)
{
    صحیح t, tests = حجم(test_struct)/حجم(test_struct[0]);

    برائے (t = 0; t < tests; ++t){
        لکھو("\nTEST: %d\n\n", t+1);
        test_function(&test_struct[t]);
    }
    واپس 0;
}
