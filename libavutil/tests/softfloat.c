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

#अन्तर्भाव "libavutil/timer.h"

#अन्तर्भाव <inttypes.h>

#अन्तर्भाव "libavutil/softfloat.h"
#अन्तर्भाव "libavutil/common.h"
#अन्तर्भाव "libavutil/log.h"

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

स्थिर स्थिरांक SoftFloat FLOAT_0_017776489257 = {0x1234, 12};
स्थिर स्थिरांक SoftFloat FLOAT_1374_40625 = {0xabcd, 25};
स्थिर स्थिरांक SoftFloat FLOAT_0_1249694824218 = {0xFFF, 15};

स्थिर द्विगुण add_mul(पूर्णांक i)
{
    द्विगुण d1 = i, d2 = i/100.0;

    साठी (पूर्णांक j = 0; j < 1000; j++)
        d1 = (d1+1)*d2;
    परत d1;
}

स्थिर SoftFloat add_mul_sf(पूर्णांक i)
{
    SoftFloat one = av_int2sf(1, 0);
    SoftFloat sf1 = av_int2sf(i, 0);
    SoftFloat sf2 = av_div_sf(av_int2sf(i, 2), av_int2sf(200, 3));

    साठी (पूर्णांक j = 0; j < 1000; j++)
        sf1 = av_mul_sf(av_add_sf(sf1, one), sf2);
    परत sf1;
}

पूर्णांक main(पूर्णांक argc, अक्षर **argv){
    SoftFloat one= av_int2sf(1, 0);
    SoftFloat sf1, sf2, sf3;
    द्विगुण d1, d2, d3;
    पूर्णांक i, j;
    पूर्णांक bench = argc > 1 && !म_भेद(argv[1], "-t");
    av_log_set_level(AV_LOG_DEBUG);

    d1= 1;
    साठी(i= 0; i<10; i++){
        d1= 1/(d1+1);
    }
    म_लिखो("test1 double=%d\n", (पूर्णांक)(d1 * (1<<24)));

    sf1= one;
    साठी(i= 0; i<10; i++){
        sf1= av_div_sf(one, av_normalize_sf(av_add_sf(one, sf1)));
    }
    म_लिखो("test1 sf    =%d\n", av_sf2int(sf1, 24));


    जर (bench) {
        साठी(i= 0; i<100; i++){
            START_TIMER
            d1= add_mul(i);
            STOP_TIMER("float add mul")
        }
    } अन्यथा
        d1= add_mul(99);
    म_लिखो("test2 double=%d\n", (पूर्णांक)(d1 * (1<<24)));

    जर (bench) {
        साठी(i= 0; i<100; i++){
            START_TIMER
            sf1= add_mul_sf(i);
            STOP_TIMER("softfloat add mul")
        }
    } अन्यथा
        sf1= add_mul_sf(99);
    म_लिखो("test2 sf    =%d (%d %d)\n", av_sf2int(sf1, 24), sf1.exp, sf1.mant);

    d1 = 0.0177764893;
    d2 = 1374.40625;
    d3 = 0.1249694824;
    d2 += d1;
    d3 += d2;
    म_लिखो("test3 double: %.10lf\n", d3);

    sf1 = FLOAT_0_017776489257;
    sf2 = FLOAT_1374_40625;
    sf3 = FLOAT_0_1249694824218;
    sf2 = av_add_sf(sf1, sf2);
    sf3 = av_add_sf(sf3, sf2);
    म_लिखो("test3 softfloat: %.10lf (0x%08x %d)\n", (द्विगुण)av_sf2double(sf3), sf3.mant, sf3.exp);

    sf1 = av_int2sf(0xFFFFFFF0, 0);
    म_लिखो("test4 softfloat: %.10lf (0x%08x %d)\n", (द्विगुण)av_sf2double(sf1), sf1.mant, sf1.exp);
    sf1 = av_int2sf(0x00000010, 0);
    म_लिखो("test4 softfloat: %.10lf (0x%08x %d)\n", (द्विगुण)av_sf2double(sf1), sf1.mant, sf1.exp);

    sf1 = av_int2sf(0x1FFFFFFF, 0);
    म_लिखो("test4 softfloat: %.10lf (0x%08x %d)\n", (द्विगुण)av_sf2double(sf1), sf1.mant, sf1.exp);
    sf1 = av_int2sf(0xE0000001, 0);
    म_लिखो("test4 softfloat: %.10lf (0x%08x %d)\n", (द्विगुण)av_sf2double(sf1), sf1.mant, sf1.exp);


    sf1 = (SoftFloat){ 0x20000000,   MIN_EXP };
    sf1 = av_mul_sf(sf1, sf1);
    म_लिखो("test5 softfloat: %.10lf (0x%08x %d)\n", (द्विगुण)av_sf2double(sf1), sf1.mant, sf1.exp);

    sf1 = (SoftFloat){ 0x20000000,   MIN_EXP };
    sf2 = (SoftFloat){ 0x20000000,   MAX_EXP };
    i = av_cmp_sf(sf1, sf2);
    j = av_cmp_sf(sf2, sf1);
    sf1 = av_div_sf(sf1, sf2);
    म_लिखो("test6 softfloat: %.10lf (0x%08x %d) %d %d\n", (द्विगुण)av_sf2double(sf1), sf1.mant, sf1.exp, i, j);

    साठी(i= -50; i<50; i++) {
        sf1= av_int2sf(i, 0);
        साठी(j= -50; j<50; j++) {
            पूर्णांक c;
            sf2= av_int2sf(j, 0);
            c = av_cmp_sf(sf1, sf2);
            जर (FFDIFFSIGN(i,j) != c && (FFDIFFSIGN(i,j)^c)<0) {
                म_लिखो("av_cmp_sf failed at %d %d as %X\n", i, j, c);
            }
            c = av_gt_sf(sf1, sf2);
            जर ((i>j) != c) {
                म_लिखो("av_gt_sf failed at %d %d as %X\n", i, j, c);
            }
        }
        sf1 = av_int2sf(1, i);
        साठी(j = -50; j < 50; j++) {
            पूर्णांक c;
            sf2 = av_int2sf(1, j);
            c = av_cmp_sf(sf2, sf1);
            जर (FFDIFFSIGN(i,j) != c && (FFDIFFSIGN(i,j)^c) < 0) {
                म_लिखो("av_cmp_sf failed2 at %d %d as %X\n", i, j, c);
            }
            c = av_gt_sf(sf1, sf2);
            जर ((i<j) != c) {
                म_लिखो("av_gt_sf failed2 at %d %d as %X\n", i, j, c);
            }
        }
    }


    साठी(i= 0; i<4*36; i++){
        पूर्णांक s, c;
        द्विगुण errs, errc;

        av_sincos_sf(i*(1ULL<<32)/36/4, &s, &c);
        errs = (द्विगुण)s/ (1<<30) - sin(i*M_PI/36);
        errc = (द्विगुण)c/ (1<<30) - cos(i*M_PI/36);
        जर (भ_असल(errs) > 0.000000004 || भ_असल(errc) >0.000000004) {
            म_लिखो("sincos FAIL %d %f %f %f %f\n", i, (दशांश)s/ (1<<30), (दशांश)c/ (1<<30), sin(i*M_PI/36), cos(i*M_PI/36));
        }

    }
    परत 0;

}
