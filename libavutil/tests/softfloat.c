/*
 * copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
 *
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

#شامل "libavutil/timer.h"

#شامل <inttypes.h>

#شامل "libavutil/softfloat.h"
#شامل "libavutil/common.h"
#شامل "libavutil/log.h"

#شامل <stdio.h>
#شامل <string.h>

ایستا ثابت SoftFloat FLOAT_0_017776489257 = {0x1234, 12};
ایستا ثابت SoftFloat FLOAT_1374_40625 = {0xabcd, 25};
ایستا ثابت SoftFloat FLOAT_0_1249694824218 = {0xFFF, 15};

ایستا دوگانه add_mul(صحیح i)
{
    دوگانه d1 = i, d2 = i/100.0;

    برای (صحیح j = 0; j < 1000; j++)
        d1 = (d1+1)*d2;
    بازگشت d1;
}

ایستا SoftFloat add_mul_sf(صحیح i)
{
    SoftFloat one = av_int2sf(1, 0);
    SoftFloat sf1 = av_int2sf(i, 0);
    SoftFloat sf2 = av_div_sf(av_int2sf(i, 2), av_int2sf(200, 3));

    برای (صحیح j = 0; j < 1000; j++)
        sf1 = av_mul_sf(av_add_sf(sf1, one), sf2);
    بازگشت sf1;
}

صحیح اصلی(صحیح argc, نویسه **argv){
    SoftFloat one= av_int2sf(1, 0);
    SoftFloat sf1, sf2, sf3;
    دوگانه d1, d2, d3;
    صحیح i, j;
    صحیح bench = argc > 1 && !strcmp(argv[1], "-t");
    av_log_set_level(AV_LOG_DEBUG);

    d1= 1;
    برای(i= 0; i<10; i++){
        d1= 1/(d1+1);
    }
    printf("test1 double=%d\n", (صحیح)(d1 * (1<<24)));

    sf1= one;
    برای(i= 0; i<10; i++){
        sf1= av_div_sf(one, av_normalize_sf(av_add_sf(one, sf1)));
    }
    printf("test1 sf    =%d\n", av_sf2int(sf1, 24));


    اگر (bench) {
        برای(i= 0; i<100; i++){
            START_TIMER
            d1= add_mul(i);
            STOP_TIMER("float add mul")
        }
    } وگرنه
        d1= add_mul(99);
    printf("test2 double=%d\n", (صحیح)(d1 * (1<<24)));

    اگر (bench) {
        برای(i= 0; i<100; i++){
            START_TIMER
            sf1= add_mul_sf(i);
            STOP_TIMER("softfloat add mul")
        }
    } وگرنه
        sf1= add_mul_sf(99);
    printf("test2 sf    =%d (%d %d)\n", av_sf2int(sf1, 24), sf1.exp, sf1.mant);

    d1 = 0.0177764893;
    d2 = 1374.40625;
    d3 = 0.1249694824;
    d2 += d1;
    d3 += d2;
    printf("test3 double: %.10lf\n", d3);

    sf1 = FLOAT_0_017776489257;
    sf2 = FLOAT_1374_40625;
    sf3 = FLOAT_0_1249694824218;
    sf2 = av_add_sf(sf1, sf2);
    sf3 = av_add_sf(sf3, sf2);
    printf("test3 softfloat: %.10lf (0x%08x %d)\n", (دوگانه)av_sf2double(sf3), sf3.mant, sf3.exp);

    sf1 = av_int2sf(0xFFFFFFF0, 0);
    printf("test4 softfloat: %.10lf (0x%08x %d)\n", (دوگانه)av_sf2double(sf1), sf1.mant, sf1.exp);
    sf1 = av_int2sf(0x00000010, 0);
    printf("test4 softfloat: %.10lf (0x%08x %d)\n", (دوگانه)av_sf2double(sf1), sf1.mant, sf1.exp);

    sf1 = av_int2sf(0x1FFFFFFF, 0);
    printf("test4 softfloat: %.10lf (0x%08x %d)\n", (دوگانه)av_sf2double(sf1), sf1.mant, sf1.exp);
    sf1 = av_int2sf(0xE0000001, 0);
    printf("test4 softfloat: %.10lf (0x%08x %d)\n", (دوگانه)av_sf2double(sf1), sf1.mant, sf1.exp);


    sf1 = (SoftFloat){ 0x20000000,   MIN_EXP };
    sf1 = av_mul_sf(sf1, sf1);
    printf("test5 softfloat: %.10lf (0x%08x %d)\n", (دوگانه)av_sf2double(sf1), sf1.mant, sf1.exp);

    sf1 = (SoftFloat){ 0x20000000,   MIN_EXP };
    sf2 = (SoftFloat){ 0x20000000,   MAX_EXP };
    i = av_cmp_sf(sf1, sf2);
    j = av_cmp_sf(sf2, sf1);
    sf1 = av_div_sf(sf1, sf2);
    printf("test6 softfloat: %.10lf (0x%08x %d) %d %d\n", (دوگانه)av_sf2double(sf1), sf1.mant, sf1.exp, i, j);

    برای(i= -50; i<50; i++) {
        sf1= av_int2sf(i, 0);
        برای(j= -50; j<50; j++) {
            صحیح c;
            sf2= av_int2sf(j, 0);
            c = av_cmp_sf(sf1, sf2);
            اگر (FFDIFFSIGN(i,j) != c && (FFDIFFSIGN(i,j)^c)<0) {
                printf("av_cmp_sf failed at %d %d as %X\n", i, j, c);
            }
            c = av_gt_sf(sf1, sf2);
            اگر ((i>j) != c) {
                printf("av_gt_sf failed at %d %d as %X\n", i, j, c);
            }
        }
        sf1 = av_int2sf(1, i);
        برای(j = -50; j < 50; j++) {
            صحیح c;
            sf2 = av_int2sf(1, j);
            c = av_cmp_sf(sf2, sf1);
            اگر (FFDIFFSIGN(i,j) != c && (FFDIFFSIGN(i,j)^c) < 0) {
                printf("av_cmp_sf failed2 at %d %d as %X\n", i, j, c);
            }
            c = av_gt_sf(sf1, sf2);
            اگر ((i<j) != c) {
                printf("av_gt_sf failed2 at %d %d as %X\n", i, j, c);
            }
        }
    }


    برای(i= 0; i<4*36; i++){
        صحیح s, c;
        دوگانه errs, errc;

        av_sincos_sf(i*(1ULL<<32)/36/4, &s, &c);
        errs = (دوگانه)s/ (1<<30) - sin(i*M_PI/36);
        errc = (دوگانه)c/ (1<<30) - cos(i*M_PI/36);
        اگر (fabs(errs) > 0.000000004 || fabs(errc) >0.000000004) {
            printf("sincos FAIL %d %f %f %f %f\n", i, (اعشاری)s/ (1<<30), (اعشاری)c/ (1<<30), sin(i*M_PI/36), cos(i*M_PI/36));
        }

    }
    بازگشت 0;

}
