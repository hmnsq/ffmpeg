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

#అన్తర్భావ "libavutil/timer.h"

#అన్తర్భావ <inttypes.h>

#అన్తర్భావ "libavutil/softfloat.h"
#అన్తర్భావ "libavutil/common.h"
#అన్తర్భావ "libavutil/log.h"

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

స్థిర స్థిరరాశి SoftFloat FLOAT_0_017776489257 = {0x1234, 12};
స్థిర స్థిరరాశి SoftFloat FLOAT_1374_40625 = {0xabcd, 25};
స్థిర స్థిరరాశి SoftFloat FLOAT_0_1249694824218 = {0xFFF, 15};

స్థిర ద్విగుణ కూడు_mul(పూర్ణాంకం i)
{
    ద్విగుణ d1 = i, d2 = i/100.0;

    కొరకు (పూర్ణాంకం j = 0; j < 1000; j++)
        d1 = (d1+1)*d2;
    తిరిగి d1;
}

స్థిర SoftFloat కూడు_mul_sf(పూర్ణాంకం i)
{
    SoftFloat one = av_int2sf(1, 0);
    SoftFloat sf1 = av_int2sf(i, 0);
    SoftFloat sf2 = av_div_sf(av_int2sf(i, 2), av_int2sf(200, 3));

    కొరకు (పూర్ణాంకం j = 0; j < 1000; j++)
        sf1 = av_mul_sf(av_కూడు_sf(sf1, one), sf2);
    తిరిగి sf1;
}

పూర్ణాంకం ప్రధాన(పూర్ణాంకం argc, అక్షరం **argv){
    SoftFloat one= av_int2sf(1, 0);
    SoftFloat sf1, sf2, sf3;
    ద్విగుణ d1, d2, d3;
    పూర్ణాంకం i, j;
    పూర్ణాంకం bench = argc > 1 && !strcmp(argv[1], "-t");
    av_log_సమితి_level(AV_LOG_DEBUG);

    d1= 1;
    కొరకు(i= 0; i<10; i++){
        d1= 1/(d1+1);
    }
    రాయి("test1 double=%d\n", (పూర్ణాంకం)(d1 * (1<<24)));

    sf1= one;
    కొరకు(i= 0; i<10; i++){
        sf1= av_div_sf(one, av_normalize_sf(av_కూడు_sf(one, sf1)));
    }
    రాయి("test1 sf    =%d\n", av_sf2int(sf1, 24));


    ఒకవేళ (bench) {
        కొరకు(i= 0; i<100; i++){
            ప్రారంభం_TIMER
            d1= కూడు_mul(i);
            STOP_TIMER("float add mul")
        }
    } లేకపోతే
        d1= కూడు_mul(99);
    రాయి("test2 double=%d\n", (పూర్ణాంకం)(d1 * (1<<24)));

    ఒకవేళ (bench) {
        కొరకు(i= 0; i<100; i++){
            ప్రారంభం_TIMER
            sf1= కూడు_mul_sf(i);
            STOP_TIMER("softfloat add mul")
        }
    } లేకపోతే
        sf1= కూడు_mul_sf(99);
    రాయి("test2 sf    =%d (%d %d)\n", av_sf2int(sf1, 24), sf1.ఘాతాంకం, sf1.mant);

    d1 = 0.0177764893;
    d2 = 1374.40625;
    d3 = 0.1249694824;
    d2 += d1;
    d3 += d2;
    రాయి("test3 double: %.10lf\n", d3);

    sf1 = FLOAT_0_017776489257;
    sf2 = FLOAT_1374_40625;
    sf3 = FLOAT_0_1249694824218;
    sf2 = av_కూడు_sf(sf1, sf2);
    sf3 = av_కూడు_sf(sf3, sf2);
    రాయి("test3 softfloat: %.10lf (0x%08x %d)\n", (ద్విగుణ)av_sf2double(sf3), sf3.mant, sf3.ఘాతాంకం);

    sf1 = av_int2sf(0xFFFFFFF0, 0);
    రాయి("test4 softfloat: %.10lf (0x%08x %d)\n", (ద్విగుణ)av_sf2double(sf1), sf1.mant, sf1.ఘాతాంకం);
    sf1 = av_int2sf(0x00000010, 0);
    రాయి("test4 softfloat: %.10lf (0x%08x %d)\n", (ద్విగుణ)av_sf2double(sf1), sf1.mant, sf1.ఘాతాంకం);

    sf1 = av_int2sf(0x1FFFFFFF, 0);
    రాయి("test4 softfloat: %.10lf (0x%08x %d)\n", (ద్విగుణ)av_sf2double(sf1), sf1.mant, sf1.ఘాతాంకం);
    sf1 = av_int2sf(0xE0000001, 0);
    రాయి("test4 softfloat: %.10lf (0x%08x %d)\n", (ద్విగుణ)av_sf2double(sf1), sf1.mant, sf1.ఘాతాంకం);


    sf1 = (SoftFloat){ 0x20000000,   MIN_EXP };
    sf1 = av_mul_sf(sf1, sf1);
    రాయి("test5 softfloat: %.10lf (0x%08x %d)\n", (ద్విగుణ)av_sf2double(sf1), sf1.mant, sf1.ఘాతాంకం);

    sf1 = (SoftFloat){ 0x20000000,   MIN_EXP };
    sf2 = (SoftFloat){ 0x20000000,   MAX_EXP };
    i = av_cmp_sf(sf1, sf2);
    j = av_cmp_sf(sf2, sf1);
    sf1 = av_div_sf(sf1, sf2);
    రాయి("test6 softfloat: %.10lf (0x%08x %d) %d %d\n", (ద్విగుణ)av_sf2double(sf1), sf1.mant, sf1.ఘాతాంకం, i, j);

    కొరకు(i= -50; i<50; i++) {
        sf1= av_int2sf(i, 0);
        కొరకు(j= -50; j<50; j++) {
            పూర్ణాంకం c;
            sf2= av_int2sf(j, 0);
            c = av_cmp_sf(sf1, sf2);
            ఒకవేళ (FFDIFFSIGN(i,j) != c && (FFDIFFSIGN(i,j)^c)<0) {
                రాయి("av_cmp_sf failed at %d %d as %X\n", i, j, c);
            }
            c = av_gt_sf(sf1, sf2);
            ఒకవేళ ((i>j) != c) {
                రాయి("av_gt_sf failed at %d %d as %X\n", i, j, c);
            }
        }
        sf1 = av_int2sf(1, i);
        కొరకు(j = -50; j < 50; j++) {
            పూర్ణాంకం c;
            sf2 = av_int2sf(1, j);
            c = av_cmp_sf(sf2, sf1);
            ఒకవేళ (FFDIFFSIGN(i,j) != c && (FFDIFFSIGN(i,j)^c) < 0) {
                రాయి("av_cmp_sf failed2 at %d %d as %X\n", i, j, c);
            }
            c = av_gt_sf(sf1, sf2);
            ఒకవేళ ((i<j) != c) {
                రాయి("av_gt_sf failed2 at %d %d as %X\n", i, j, c);
            }
        }
    }


    కొరకు(i= 0; i<4*36; i++){
        పూర్ణాంకం s, c;
        ద్విగుణ errs, errc;

        av_sincos_sf(i*(1ULL<<32)/36/4, &s, &c);
        errs = (ద్విగుణ)s/ (1<<30) - జ్యా(i*M_PI/36);
        errc = (ద్విగుణ)c/ (1<<30) - కోజ్యా(i*M_PI/36);
        ఒకవేళ (fabs(errs) > 0.000000004 || fabs(errc) >0.000000004) {
            రాయి("sincos FAIL %d %f %f %f %f\n", i, (దశాంశం)s/ (1<<30), (దశాంశం)c/ (1<<30), జ్యా(i*M_PI/36), కోజ్యా(i*M_PI/36));
        }

    }
    తిరిగి 0;

}
