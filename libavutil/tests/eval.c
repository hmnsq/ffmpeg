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

#समावेश "libavutil/timer.h"

#समावेश <math.h>
#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "libavutil/mathematics.h"
#समावेश "libavutil/eval.h"

अटल स्थिर द्विगुन const_मूल्यावली[] = {
    M_PI,
    M_E,
    0
};

अटल स्थिर अक्षर *स्थिर const_names[] = {
    "PI",
    "E",
    0
};

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
{
    पूर्णांक i;
    द्विगुन d;
    स्थिर अक्षर *स्थिर *व्यंजक;
    अटल स्थिर अक्षर *स्थिर exprs[] = {
        "",
        "1;2",
        "-20",
        "-PI",
        "+PI",
        "1+(5-2)^(3-1)+1/2+sin(PI)-max(-2.2,-3.1)",
        "80G/80Gi",
        "1k",
        "1Gi",
        "1gi",
        "1GiFoo",
        "1k+1k",
        "1Gi*3foo",
        "foo",
        "foo(",
        "foo()",
        "foo)",
        "sin",
        "sin(",
        "sin()",
        "sin)",
        "sin 10",
        "sin(1,2,3)",
        "sin(1 )",
        "1",
        "1foo",
        "bar + PI + E + 100f*2 + foo",
        "13k + 12f - foo(1, 2)",
        "1gi",
        "1Gi",
        "st(0, 123)",
        "st(1, 123); ld(1)",
        "lte(0, 1)",
        "lte(1, 1)",
        "lte(1, 0)",
        "lt(0, 1)",
        "lt(1, 1)",
        "gt(1, 0)",
        "gt(2, 7)",
        "gte(122, 122)",
        /* compute 1+2+...+N */
        "st(0, 1); while(lte(ld(0), 100), st(1, ld(1)+ld(0));st(0, ld(0)+1)); ld(1)",
        /* compute Fib(N) */
        "st(1, 1); st(2, 2); st(0, 1); while(lte(ld(0),10), st(3, ld(1)+ld(2)); st(1, ld(2)); st(2, ld(3)); st(0, ld(0)+1)); ld(3)",
        "while(0, 10)",
        "st(0, 1); while(lte(ld(0),100), st(1, ld(1)+ld(0)); st(0, ld(0)+1))",
        "isnan(1)",
        "isnan(NAN)",
        "isnan(INF)",
        "isinf(1)",
        "isinf(NAN)",
        "isinf(INF)",
        "floor(NAN)",
        "floor(123.123)",
        "floor(-123.123)",
        "trunc(123.123)",
        "trunc(-123.123)",
        "ceil(123.123)",
        "ceil(-123.123)",
        "sqrt(1764)",
        "isnan(sqrt(-1))",
        "not(1)",
        "not(NAN)",
        "not(0)",
        "6.0206dB",
        "-3.0103dB",
        "pow(0,1.23)",
        "pow(PI,1.23)",
        "PI^1.23",
        "pow(-1,1.23)",
        "if(1, 2)",
        "if(1, 1, 2)",
        "if(0, 1, 2)",
        "ifnot(0, 23)",
        "ifnot(1, NaN) + if(0, 1)",
        "ifnot(1, 1, 2)",
        "ifnot(0, 1, 2)",
        "taylor(1, 1)",
        "taylor(eq(mod(ld(1),4),1)-eq(mod(ld(1),4),3), PI/2, 1)",
        "root(sin(ld(0))-1, 2)",
        "root(sin(ld(0))+6+sin(ld(0)/12)-log(ld(0)), 100)",
        "7000000B*random(0)",
        "squish(2)",
        "-squish(2)",
        "gauss(0.1)",
        "-gauss(0.1)",
        "hypot(4,3)",
        "gcd(30,55)*print(min(9,1))",
        "-print(42)",
        "lerp(0, 100, 0.5)",
        "-lerp(0, 100, 0.5)",
        "bitor(42, 12)",
        "bitand(42, 12)",
        "bitand(NAN, 1)",
        "between(10, -3, 10)",
        "between(-4, -2, -1)",
        "between(1,2)",
        "clip(0, 2, 1)",
        "clip(0/0, 1, 2)",
        "clip(0, 0/0, 1)",
        शून्य
    };
    पूर्णांक ret;

    क्रम (व्यंजक = exprs; *व्यंजक; व्यंजक++) {
        म_लिखो("Evaluating '%s'\n", *व्यंजक);
        ret = av_व्यंजक_parse_and_eval(&d, *व्यंजक,
                               const_names, const_मूल्यावली,
                               शून्य, शून्य, शून्य, शून्य, शून्य, 0, शून्य);
        अगर (isnan(d))
            म_लिखो("'%s' -> nan\n\n", *व्यंजक);
        अन्यथा
            म_लिखो("'%s' -> %f\n\n", *व्यंजक, d);
        अगर (ret < 0)
            म_लिखो("av_expr_parse_and_eval failed\n");
    }

    ret = av_व्यंजक_parse_and_eval(&d, "1+(5-2)^(3-1)+1/2+sin(PI)-max(-2.2,-3.1)",
                           const_names, const_मूल्यावली,
                           शून्य, शून्य, शून्य, शून्य, शून्य, 0, शून्य);
    म_लिखो("%f == 12.7\n", d);
    अगर (ret < 0)
        म_लिखो("av_expr_parse_and_eval failed\n");
    ret = av_व्यंजक_parse_and_eval(&d, "80G/80Gi",
                           const_names, const_मूल्यावली,
                           शून्य, शून्य, शून्य, शून्य, शून्य, 0, शून्य);
    म_लिखो("%f == 0.931322575\n", d);
    अगर (ret < 0)
        म_लिखो("av_expr_parse_and_eval failed\n");

    अगर (argc > 1 && !म_भेद(argv[1], "-t")) {
        क्रम (i = 0; i < 1050; i++) {
            START_TIMER;
            ret = av_व्यंजक_parse_and_eval(&d, "1+(5-2)^(3-1)+1/2+sin(PI)-max(-2.2,-3.1)",
                                   const_names, const_मूल्यावली,
                                   शून्य, शून्य, शून्य, शून्य, शून्य, 0, शून्य);
            अगर (ret < 0)
                म_लिखो("av_expr_parse_and_eval failed\n");
            STOP_TIMER("av_expr_parse_and_eval");
        }
    }

    वापस 0;
}
