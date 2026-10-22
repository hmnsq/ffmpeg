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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/common.h"
#అన్తర్భావ "libavutil/channel_layout.h"
#అన్తర్భావ "libavutil/error.h"
#అన్తర్భావ "libavutil/log.h"
#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/rational.h"
#అన్తర్భావ "libavutil/opt.h"
#అన్తర్భావ "libavutil/pixdesc.h"

రకనిర్వచనం నిర్మాణం TestContext {
    స్థిరరాశి AVClass *class;
    నిర్మాణం బిడ్డ_Context *బిడ్డ;
    పూర్ణాంకం అంకె;
    పూర్ణాంకం unum;
    పూర్ణాంకం toggle;
    అక్షరం *string;
    పూర్ణాంకం flags;
    AVRational rational;
    AVRational video_రేటు;
    పూర్ణాంకం w, h;
    గణన AVPixelFormat pix_fmt;
    గణన AVSampleFormat sample_fmt;
    int64_t duration;
    uint8_t color[4];
    AVChannelLayout channel_layout;
    శూన్య *ద్విమాన;
    పూర్ణాంకం ద్విమాన_కొలత;
    శూన్య *binary1;
    పూర్ణాంకం ద్విమాన_size1;
    శూన్య *binary2;
    పూర్ణాంకం ద్విమాన_size2;
    int64_t num64;
    దశాంశం flt;
    ద్విగుణ dbl;
    అక్షరం *escape;
    పూర్ణాంకం bool1;
    పూర్ణాంకం bool2;
    పూర్ణాంకం bool3;
    AVDictionary *dict1;
    AVDictionary *dict2;

    పూర్ణాంకం           **array_int;
    గుర్తులేని     nb_array_int;

    అక్షరం          **array_str;
    గుర్తులేని     nb_array_str;

    AVDictionary  **array_dict;
    గుర్తులేని     nb_array_dict;
} TestContext;

#నిర్వచించు స్థానభ్రంశం_2(x) offsetof(TestContext, x)

#నిర్వచించు TEST_FLAG_COOL 01
#నిర్వచించు TEST_FLAG_LAME 02
#నిర్వచించు TEST_FLAG_MU   04

స్థిర స్థిరరాశి AVOptionArrayDef array_str = {
    .sep         = '|',
    .def         = "str0|str\\|1|str\\\\2",
};

స్థిర స్థిరరాశి AVOptionArrayDef array_dict = {
    // there are three levels of escaping - C string, array option, dict - so 8 backslashes are needed to get a literal one inside a dict key/val
    .def         = "k00=v\\\\\\\\00:k01=v\\,01,k10=v\\\\=1\\\\:0",
};

స్థిర స్థిరరాశి AVOption test_options[]= {
    {"num",        "set num",            స్థానభ్రంశం_2(అంకె),            AV_OPT_TYPE_INT,            { .i64 = 0 },                     -1,       100, 1 },
    {"unum",       "set unum",           స్థానభ్రంశం_2(unum),           AV_OPT_TYPE_UINT,           { .i64 = 1U << 31 },               0,  1U << 31, 1 },
    {"toggle",     "set toggle",         స్థానభ్రంశం_2(toggle),         AV_OPT_TYPE_INT,            { .i64 = 1 },                      0,         1, 1 },
    {"rational",   "set rational",       స్థానభ్రంశం_2(rational),       AV_OPT_TYPE_RATIONAL,       { .dbl = 1 },                      0,        10, 1 },
    {"string",     "set string",         స్థానభ్రంశం_2(string),         AV_OPT_TYPE_STRING,         { .str = "default" },       CHAR_MIN,  CHAR_MAX, 1 },
    {"escape",     "set escape str",     స్థానభ్రంశం_2(escape),         AV_OPT_TYPE_STRING,         { .str = "\\=," },          CHAR_MIN,  CHAR_MAX, 1 },
    {"flags",      "set flags",          స్థానభ్రంశం_2(flags),          AV_OPT_TYPE_FLAGS,          { .i64 = 1 },                      0,   గరిష్ఠ_పూర్ణాంకం, 1, .unit = "flags" },
    {"cool",       "set cool flag",      0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_COOL },   INT_MIN,   గరిష్ఠ_పూర్ణాంకం, 1, .unit = "flags" },
    {"lame",       "set lame flag",      0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_LAME },   INT_MIN,   గరిష్ఠ_పూర్ణాంకం, 1, .unit = "flags" },
    {"mu",         "set mu flag",        0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_MU },     INT_MIN,   గరిష్ఠ_పూర్ణాంకం, 1, .unit = "flags" },
    {"size",       "set size",           స్థానభ్రంశం_2(w),              AV_OPT_TYPE_IMAGE_కొలత,     { .str="200x300" },                0,         0, 1 },
    {"pix_fmt",    "set pixfmt",         స్థానభ్రంశం_2(pix_fmt),        AV_OPT_TYPE_PIXEL_FMT,      { .i64 = AV_PIX_FMT_0BGR },       -1,   గరిష్ఠ_పూర్ణాంకం, 1 },
    {"sample_fmt", "set samplefmt",      స్థానభ్రంశం_2(sample_fmt),     AV_OPT_TYPE_SAMPLE_FMT,     { .i64 = AV_SAMPLE_FMT_S16 },     -1,   గరిష్ఠ_పూర్ణాంకం, 1 },
    {"video_rate", "set videorate",      స్థానభ్రంశం_2(video_రేటు),     AV_OPT_TYPE_VIDEO_రేటు,     { .str = "25" },                   0,         గరిష్ఠ_పూర్ణాంకం, 1 },
    {"duration",   "set duration",       స్థానభ్రంశం_2(duration),       AV_OPT_TYPE_DURATION,       { .i64 = 1000 },                   0, INT64_MAX, 1 },
    {"color",      "set color",          స్థానభ్రంశం_2(color),          AV_OPT_TYPE_COLOR,          { .str = "pink" },                 0,         0, 1 },
    {"cl",         "set channel layout", స్థానభ్రంశం_2(channel_layout), AV_OPT_TYPE_CHLAYOUT,       { .str = "hexagonal" },            0,         0, 1 },
    {"bin",        "set binary value",   స్థానభ్రంశం_2(ద్విమాన),         AV_OPT_TYPE_ద్విమాన,         { .str="62696e00" },               0,         0, 1 },
    {"bin1",       "set binary value",   స్థానభ్రంశం_2(binary1),        AV_OPT_TYPE_ద్విమాన,         { .str=ఖాళీ },                     0,         0, 1 },
    {"bin2",       "set binary value",   స్థానభ్రంశం_2(binary2),        AV_OPT_TYPE_ద్విమాన,         { .str="" },                       0,         0, 1 },
    {"num64",      "set num 64bit",      స్థానభ్రంశం_2(num64),          AV_OPT_TYPE_INT64,          { .i64 = 1LL << 32 },             -1, 1LL << 32, 1 },
    {"flt",        "set float",          స్థానభ్రంశం_2(flt),            AV_OPT_TYPE_FLOAT,          { .dbl = 1.0 / 3 },                0,       100, 1 },
    {"dbl",        "set double",         స్థానభ్రంశం_2(dbl),            AV_OPT_TYPE_DOUBLE,         { .dbl = 1.0 / 3 },                0,       100, 1 },
    {"bool1",      "set boolean value",  స్థానభ్రంశం_2(bool1),          AV_OPT_TYPE_BOOL,           { .i64 = -1 },                    -1,         1, 1 },
    {"bool2",      "set boolean value",  స్థానభ్రంశం_2(bool2),          AV_OPT_TYPE_BOOL,           { .i64 = 1 },                     -1,         1, 1 },
    {"bool3",      "set boolean value",  స్థానభ్రంశం_2(bool3),          AV_OPT_TYPE_BOOL,           { .i64 = 0 },                      0,         1, 1 },
    {"dict1",      "set dictionary value", స్థానభ్రంశం_2(dict1),        AV_OPT_TYPE_DICT,           { .str = ఖాళీ},                    0,         0, 1 },
    {"dict2",      "set dictionary value", స్థానభ్రంశం_2(dict2),        AV_OPT_TYPE_DICT,           { .str = "happy=':-)'"},           0,         0, 1 },
    {"array_int",  "array of ints",        స్థానభ్రంశం_2(array_int),    AV_OPT_TYPE_INT | AV_OPT_TYPE_FLAG_ARRAY, .max = గరిష్ఠ_పూర్ణాంకం,           .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    {"array_str",  "array of strings",     స్థానభ్రంశం_2(array_str),    AV_OPT_TYPE_STRING | AV_OPT_TYPE_FLAG_ARRAY, { .arr = &array_str }, .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    {"array_dict", "array of dicts",       స్థానభ్రంశం_2(array_dict),   AV_OPT_TYPE_DICT | AV_OPT_TYPE_FLAG_ARRAY, { .arr = &array_dict },  .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    { ఖాళీ },
};

స్థిర స్థిరరాశి అక్షరం *test_get_name(శూన్య *ctx)
{
    తిరిగి "test";
}

రకనిర్వచనం నిర్మాణం బిడ్డ_Context {
    స్థిరరాశి AVClass *class;
    int64_t బిడ్డ_num64;
    పూర్ణాంకం బిడ్డ_అంకె;
    గుర్తులేని పూర్ణాంకం బిడ్డ_unum;
} బిడ్డ_Context;

#నిర్వచనం_రద్దు స్థానభ్రంశం_2
#నిర్వచించు స్థానభ్రంశం_2(x) offsetof(బిడ్డ_Context, x)

స్థిర స్థిరరాశి AVOption బిడ్డ_options[]= {
    {"child_num64", "set num 64bit", స్థానభ్రంశం_2(బిడ్డ_num64), AV_OPT_TYPE_INT64, { .i64 = 0 }, 0, 100, 1 | AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY },
    {"child_num",   "set child_num", స్థానభ్రంశం_2(బిడ్డ_అంకె),   AV_OPT_TYPE_INT,   { .i64 = 1 }, 0, 100, 1 },
    {"child_unum",  "set child_unum", స్థానభ్రంశం_2(బిడ్డ_unum),  AV_OPT_TYPE_UINT,  { .i64 = 0 }, 0, 100, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY },
    { ఖాళీ },
};

స్థిర స్థిరరాశి అక్షరం *బిడ్డ_get_name(శూన్య *ctx)
{
    తిరిగి "child";
}

స్థిర స్థిరరాశి AVClass బిడ్డ_class = {
    .class_name = "ChildContext",
    .అంశం_name  = బిడ్డ_get_name,
    .option     = బిడ్డ_options,
    .సంస్కరణ    = LIBAVUTIL_సంస్కరణ_INT,
};

స్థిర శూన్య *test_బిడ్డ_తదుపరి(శూన్య *obj, శూన్య *prev)
{
    TestContext *test_ctx = obj;
    ఒకవేళ (!prev)
        తిరిగి test_ctx->బిడ్డ;
    తిరిగి ఖాళీ;
}

స్థిర స్థిరరాశి AVClass test_class = {
    .class_name = "TestContext",
    .అంశం_name  = test_get_name,
    .option     = test_options,
    .బిడ్డ_తదుపరి = test_బిడ్డ_తదుపరి,
    .సంస్కరణ    = LIBAVUTIL_సంస్కరణ_INT,
};

స్థిర శూన్య log_callback_help(శూన్య *ptr, పూర్ణాంకం level, స్థిరరాశి అక్షరం *fmt, va_list vl)
{
    vfprintf(stdout, fmt, vl);
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    పూర్ణాంకం i;

    av_log_సమితి_level(AV_LOG_DEBUG);
    av_log_సమితి_callback(log_callback_help);

    రాయి("Testing default values\n");
    {
        TestContext test_ctx = { 0 };
        test_ctx.class = &test_class;
        av_opt_సమితి_defaults(&test_ctx);

        రాయి("num=%d\n", test_ctx.అంకె);
        రాయి("unum=%u\n", test_ctx.unum);
        రాయి("toggle=%d\n", test_ctx.toggle);
        రాయి("string=%s\n", test_ctx.string);
        రాయి("escape=%s\n", test_ctx.escape);
        రాయి("flags=%d\n", test_ctx.flags);
        రాయి("rational=%d/%d\n", test_ctx.rational.అంకె, test_ctx.rational.den);
        రాయి("video_rate=%d/%d\n", test_ctx.video_రేటు.అంకె, test_ctx.video_రేటు.den);
        రాయి("width=%d height=%d\n", test_ctx.w, test_ctx.h);
        రాయి("pix_fmt=%s\n", av_get_pix_fmt_name(test_ctx.pix_fmt));
        రాయి("sample_fmt=%s\n", av_get_sample_fmt_name(test_ctx.sample_fmt));
        రాయి("duration=%"PRId64"\n", test_ctx.duration);
        రాయి("color=%d %d %d %d\n", test_ctx.color[0], test_ctx.color[1], test_ctx.color[2], test_ctx.color[3]);
        రాయి("channel_layout=%"PRId64"=%"PRId64"\n", test_ctx.channel_layout.u.ముసుగు_2, (int64_t)AV_CH_LAYOUT_HEXAGONAL);
        ఒకవేళ (test_ctx.ద్విమాన)
            రాయి("binary=%x %x %x %x\n", ((uint8_t*)test_ctx.ద్విమాన)[0], ((uint8_t*)test_ctx.ద్విమాన)[1], ((uint8_t*)test_ctx.ద్విమాన)[2], ((uint8_t*)test_ctx.ద్విమాన)[3]);
        రాయి("binary_size=%d\n", test_ctx.ద్విమాన_కొలత);
        రాయి("num64=%"PRId64"\n", test_ctx.num64);
        రాయి("flt=%.6f\n", test_ctx.flt);
        రాయి("dbl=%.6f\n", test_ctx.dbl);

        కొరకు (గుర్తులేని i = 0; i < test_ctx.nb_array_str; i++)
            రాయి("array_str[%u]=%s\n", i, test_ctx.array_str[i]);

        కొరకు (గుర్తులేని i = 0; i < test_ctx.nb_array_dict; i++) {
            AVDictionary            *d = test_ctx.array_dict[i];
            స్థిరరాశి AVDictionary_నమోదు *e = ఖాళీ;

            అయితే ((e = av_dict_iterate(d, e)))
                రాయి("array_dict[%u]: %s\t%s\n", i, e->కీలకం, e->విలువ);
        }

        av_opt_show2(&test_ctx, ఖాళీ, -1, 0);

        av_opt_free(&test_ctx);
    }

    రాయి("\nTesting av_opt_is_set_to_default()\n");
    {
        పూర్ణాంకం ret;
        TestContext test_ctx = { 0 };
        స్థిరరాశి AVOption *o = ఖాళీ;
        test_ctx.class = &test_class;

        av_log_సమితి_level(AV_LOG_QUIET);

        అయితే (o = av_opt_తదుపరి(&test_ctx, o)) {
            ret = av_opt_is_సమితి_గమ్యం_default_by_name(&test_ctx, o->name, 0);
            రాయి("name:%10s default:%d error:%s\n", o->name, !!ret, ret < 0 ? av_err2str(ret) : "");
        }
        av_opt_సమితి_defaults(&test_ctx);
        అయితే (o = av_opt_తదుపరి(&test_ctx, o)) {
            ret = av_opt_is_సమితి_గమ్యం_default_by_name(&test_ctx, o->name, 0);
            రాయి("name:%10s default:%d error:%s\n", o->name, !!ret, ret < 0 ? av_err2str(ret) : "");
        }
        av_opt_free(&test_ctx);
    }

    రాయి("\nTesting av_opt_get/av_opt_set()\n");
    {
        TestContext test_ctx = { 0 };
        TestContext test2_ctx = { 0 };
        స్థిరరాశి AVOption *o = ఖాళీ;
        అక్షరం *val = ఖాళీ;
        పూర్ణాంకం ret;

        test_ctx.class = &test_class;
        test2_ctx.class = &test_class;

        av_log_సమితి_level(AV_LOG_QUIET);

        av_opt_సమితి_defaults(&test_ctx);

        అయితే (o = av_opt_తదుపరి(&test_ctx, o)) {
            అక్షరం *value1 = ఖాళీ;
            అక్షరం *value2 = ఖాళీ;
            పూర్ణాంకం ret1 = AVERROR_BUG;
            పూర్ణాంకం ret2 = AVERROR_BUG;
            పూర్ణాంకం ret3 = AVERROR_BUG;

            ఒకవేళ (o->type == AV_OPT_TYPE_CONST)
                కొనసాగు;

            ret1 = av_opt_get(&test_ctx, o->name, 0, (uint8_t **)&value1);
            ఒకవేళ (ret1 >= 0) {
                ret2 = av_opt_సమితి(&test2_ctx, o->name, value1, 0);
                ఒకవేళ (ret2 >= 0)
                    ret3 = av_opt_get(&test2_ctx, o->name, 0, (uint8_t **)&value2);
            }

            రాయి("name: %-11s get: %-16s set: %-16s get: %-16s %s\n", o->name,
                    ret1 >= 0 ? value1 : av_err2str(ret1),
                    ret2 >= 0 ? "OK" : av_err2str(ret2),
                    ret3 >= 0 ? value2 : av_err2str(ret3),
                    ret1 >= 0 && ret2 >= 0 && ret3 >= 0 && !strcmp(value1, value2) ? "OK" : "Mismatch");
            av_free(value1);
            av_free(value2);
        }

        // av_opt_set(NULL) with an array option resets it
        ret = av_opt_సమితి(&test_ctx, "array_dict", ఖాళీ, 0);
        రాయి("av_opt_set(\"array_dict\", NULL) -> %d\n", ret);
        రాయి("array_dict=%sNULL; nb_array_dict=%u\n",
               test_ctx.array_dict ? "non-" : "", test_ctx.nb_array_dict);

        // av_opt_get() on an empty array should return a NULL string
        ret = av_opt_get(&test_ctx, "array_dict", AV_OPT_ALLOW_NULL, (uint8_t**)&val);
        రాయి("av_opt_get(\"array_dict\") -> %s\n", val ? val : "NULL");

        av_opt_free(&test_ctx);
        av_opt_free(&test2_ctx);
    }

    రాయి("\nTesting av_opt_get_array()\n");
    {
        స్థిర స్థిరరాశి పూర్ణాంకం int_array[] = { 5, 0, 42, 137, గరిష్ఠ_పూర్ణాంకం };

        TestContext test_ctx = { 0 };

        పూర్ణాంకం     బహిర్గతం_int   [FF_ARRAY_ELEMS(int_array)] = { 0 };
        ద్విగుణ  బహిర్గతం_double[FF_ARRAY_ELEMS(int_array)] = { 0. };
        అక్షరం   *బహిర్గతం_str   [FF_ARRAY_ELEMS(int_array)] = { ఖాళీ };
        AVDictionary *బహిర్గతం_dict[2] = { ఖాళీ };

        పూర్ణాంకం ret;

        test_ctx.class = &test_class;

        av_log_సమితి_level(AV_LOG_QUIET);

        av_opt_సమితి_defaults(&test_ctx);

        test_ctx.array_int    = av_memdup(int_array, పరిమాణం(int_array));
        test_ctx.nb_array_int = FF_ARRAY_ELEMS(int_array);

        // retrieve as int
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               1, 3, AV_OPT_TYPE_INT, బహిర్గతం_int);
        రాయి("av_opt_get_array(\"array_int\", 1, 3, INT)=%d -> [ %d, %d, %d ]\n",
               ret, బహిర్గతం_int[0], బహిర్గతం_int[1], బహిర్గతం_int[2]);

        // retrieve as double
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               3, 2, AV_OPT_TYPE_DOUBLE, బహిర్గతం_double);
        రాయి("av_opt_get_array(\"array_int\", 3, 2, DOUBLE)=%d -> [ %.2f, %.2f ]\n",
               ret, బహిర్గతం_double[0], బహిర్గతం_double[1]);

        // retrieve as str
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               0, 5, AV_OPT_TYPE_STRING, బహిర్గతం_str);
        రాయి("av_opt_get_array(\"array_int\", 0, 5, STRING)=%d -> "
               "[ %s, %s, %s, %s, %s ]\n", ret,
               బహిర్గతం_str[0], బహిర్గతం_str[1], బహిర్గతం_str[2], బహిర్గతం_str[3], బహిర్గతం_str[4]);

        కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(బహిర్గతం_str); i++)
            av_freep(&బహిర్గతం_str[i]);

        ret = av_opt_get_array(&test_ctx, "array_dict", 0, 0, 2,
                               AV_OPT_TYPE_DICT, బహిర్గతం_dict);
        రాయి("av_opt_get_array(\"array_dict\", 0, 2, DICT)=%d\n", ret);

        కొరకు (పూర్ణాంకం i = 0; i < test_ctx.nb_array_dict; i++) {
            స్థిరరాశి AVDictionary_నమోదు *e = ఖాళీ;
            అయితే ((e = av_dict_iterate(test_ctx.array_dict[i], e))) {
                స్థిరరాశి AVDictionary_నమోదు *e1 = av_dict_get(బహిర్గతం_dict[i], e->కీలకం, ఖాళీ, 0);
                ఒకవేళ (!e1 || strcmp(e->విలువ, e1->విలువ)) {
                    రాయి("mismatching dict entry %s: %s/%s\n",
                           e->కీలకం, e->విలువ, e1 ? e1->విలువ : "<missing>");
                }
            }
            av_dict_free(&బహిర్గతం_dict[i]);
        }

        av_opt_free(&test_ctx);
    }

    రాయి("\nTest av_opt_serialize()\n");
    {
        TestContext test_ctx = { 0 };
        అక్షరం *buf;
        పూర్ణాంకం ret;
        test_ctx.class = &test_class;

        av_log_సమితి_level(AV_LOG_QUIET);

        av_opt_సమితి_defaults(&test_ctx);
        ఒకవేళ (av_opt_serialize(&test_ctx, 0, 0, &buf, '=', ',') >= 0) {
            రాయి("%s\n", buf);
            av_opt_free(&test_ctx);
            memset(&test_ctx, 0, పరిమాణం(test_ctx));
            test_ctx.class = &test_class;
            ret = av_సమితి_options_string(&test_ctx, buf, "=", ",");
            av_free(buf);
            ఒకవేళ (ret < 0)
                రాయి("Error ret '%d'\n", ret);
            ఒకవేళ (av_opt_serialize(&test_ctx, 0, 0, &buf, '=', ',') >= 0) {
                బిడ్డ_Context బిడ్డ_ctx = { .బిడ్డ_num64 = 1, .బిడ్డ_unum = 1 };
                రాయి("%s\n", buf);
                av_free(buf);
                బిడ్డ_ctx.class = &బిడ్డ_class;
                test_ctx.బిడ్డ = &బిడ్డ_ctx;
                రాయి("Exclude flag EXPORT:\n");
                ఒకవేళ (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_శోధన_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    రాయి("%s\n", buf);
                    av_free(buf);
                }
                రాయి("Include flag EXPORT:\n");
                ఒకవేళ (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_శోధన_CHILDREN,
                                     &buf, '=', ',') >= 0) {
                    రాయి("%s\n", buf);
                    av_free(buf);
                }
                రాయి("Exclude flag 1:\n");
                ఒకవేళ (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_శోధన_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    రాయి("%s\n", buf);
                    av_free(buf);
                }
                రాయి("Include flag 1:\n");
                ఒకవేళ (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_శోధన_CHILDREN,
                                     &buf, '=', ',') >= 0) {
                    రాయి("%s\n", buf);
                    av_free(buf);
                }
                రాయి("Exclude exact match flag 1:\n");
                ఒకవేళ (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_శోధన_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT|AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    రాయి("%s\n", buf);
                    av_free(buf);
                }
                రాయి("Include exact match flag 1:\n");
                ఒకవేళ (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_శోధన_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT,
                                     &buf, '=', ',') >= 0) {
                    రాయి("%s\n", buf);
                    av_free(buf);
                }
                రాయి("Exclude exact match flag EXPORT|READONLY:\n");
                ఒకవేళ (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_శోధన_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT|AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    రాయి("%s\n", buf);
                    av_free(buf);
                }
                రాయి("Include exact match flag EXPORT|READONLY:\n");
                ఒకవేళ (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_శోధన_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT,
                                     &buf, '=', ',') >= 0) {
                    రాయి("%s\n", buf);
                    av_free(buf);
                }
                av_opt_free(&బిడ్డ_ctx);
                test_ctx.బిడ్డ = ఖాళీ;
            }
        }
        av_opt_free(&test_ctx);
    }

    రాయి("\nTesting av_set_options_string()\n");
    {
        TestContext test_ctx = { 0 };
        స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి options[] = {
            "",
            ":",
            "=",
            "foo=:",
            ":=foo",
            "=foo",
            "foo=",
            "foo",
            "foo=val",
            "foo==val",
            "toggle=:",
            "string=:",
            "toggle=1 : foo",
            "toggle=100",
            "toggle==1",
            "flags=+mu-lame : num=42: toggle=0",
            "num=42 : string=blahblah",
            "rational=0 : rational=1/2 : rational=1/-1",
            "rational=-1/0",
            "size=1024x768",
            "size=pal",
            "size=bogus",
            "pix_fmt=yuv420p",
            "pix_fmt=2",
            "pix_fmt=bogus",
            "sample_fmt=s16",
            "sample_fmt=2",
            "sample_fmt=bogus",
            "video_rate=pal",
            "video_rate=25",
            "video_rate=30000/1001",
            "video_rate=30/1.001",
            "video_rate=bogus",
            "duration=bogus",
            "duration=123.45",
            "duration=1\\:23\\:45.67",
            "color=blue",
            "color=0x223300",
            "color=0x42FF07AA",
            "cl=FL+FR",
            "cl=foo",
            "bin=boguss",
            "bin=111",
            "bin=ffff",
            "num=bogus",
            "num=44",
            "num=44.4",
            "num=-1",
            "num=-2",
            "num=101",
            "unum=bogus",
            "unum=44",
            "unum=44.4",
            "unum=-1",
            "unum=2147483648",
            "unum=2147483649",
            "num64=bogus",
            "num64=44",
            "num64=44.4",
            "num64=-1",
            "num64=-2",
            "num64=4294967296",
            "num64=4294967297",
            "flt=bogus",
            "flt=2",
            "flt=2.2",
            "flt=-1",
            "flt=101",
            "dbl=bogus",
            "dbl=2",
            "dbl=2.2",
            "dbl=-1",
            "dbl=101",
            "bool1=true",
            "bool2=auto",
            "dict1='happy=\\:-):sad=\\:-('",
            "array_int=0,32,2147483647",
            "array_int=2147483648", // out of range, should fail
        };

        test_ctx.class = &test_class;
        av_opt_సమితి_defaults(&test_ctx);

        av_log_సమితి_level(AV_LOG_QUIET);

        కొరకు (i=0; i < FF_ARRAY_ELEMS(options); i++) {
            పూర్ణాంకం silence_log = !strcmp(options[i], "rational=-1/0"); // inf formatting differs between platforms
            av_log(&test_ctx, AV_LOG_DEBUG, "Setting options string '%s'\n", options[i]);
            ఒకవేళ (silence_log)
                av_log_సమితి_callback(ఖాళీ);
            ఒకవేళ (av_సమితి_options_string(&test_ctx, options[i], "=", ":") < 0)
                రాయి("Error '%s'\n", options[i]);
            లేకపోతే
                రాయి("OK    '%s'\n", options[i]);
            av_log_సమితి_callback(log_callback_help);
        }
        av_opt_free(&test_ctx);
    }

    రాయి("\nTesting av_opt_set_from_string()\n");
    {
        TestContext test_ctx = { 0 };
        స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి options[] = {
            "",
            "5",
            "5:hello",
            "5:hello:size=pal",
            "5:size=pal:hello",
            ":",
            "=",
            " 5 : hello : size = pal ",
            "a_very_long_option_name_that_will_need_to_be_ellipsized_around_here=42"
        };
        స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి shorthand[] = { "num", "string", ఖాళీ };

        test_ctx.class = &test_class;
        av_opt_సమితి_defaults(&test_ctx);

        av_log_సమితి_level(AV_LOG_QUIET);

        కొరకు (i=0; i < FF_ARRAY_ELEMS(options); i++) {
            av_log(&test_ctx, AV_LOG_DEBUG, "Setting options string '%s'\n", options[i]);
            ఒకవేళ (av_opt_సమితి_from_string(&test_ctx, options[i], shorthand, "=", ":") < 0)
                రాయి("Error '%s'\n", options[i]);
            లేకపోతే
                రాయి("OK    '%s'\n", options[i]);
        }
        av_opt_free(&test_ctx);
    }

    రాయి("\nTesting av_opt_find2()\n");
    {
        TestContext test_ctx = { 0 };
        బిడ్డ_Context బిడ్డ_ctx = { 0 };
        శూన్య *లక్ష్యం;
        స్థిరరాశి AVOption *opt;

        test_ctx.class = &test_class;
        బిడ్డ_ctx.class = &బిడ్డ_class;
        test_ctx.బిడ్డ = &బిడ్డ_ctx;

        av_log_సమితి_level(AV_LOG_QUIET);

        // Should succeed. num exists and has opt_flags 1
        opt = av_opt_find2(&test_ctx, "num", ఖాళీ, 1, 0, &లక్ష్యం);
        ఒకవేళ (opt && లక్ష్యం == &test_ctx)
            రాయి("OK    '%s'\n", opt->name);
        లేకపోతే
            రాయి("Error 'num'\n");

        // Should fail. num64 exists but has opt_flags 1, not 2
        opt = av_opt_కనుగొను(&test_ctx, "num64", ఖాళీ, 2, 0);
        ఒకవేళ (opt)
            రాయి("OK    '%s'\n", opt->name);
        లేకపోతే
            రాయి("Error 'num64'\n");

        // Should fail. child_num exists but in a child object we're not searching
        opt = av_opt_కనుగొను(&test_ctx, "child_num", ఖాళీ, 0, 0);
        ఒకవేళ (opt)
            రాయి("OK    '%s'\n", opt->name);
        లేకపోతే
            రాయి("Error 'child_num'\n");

        // Should succeed. child_num exists in a child object we're searching
        opt = av_opt_find2(&test_ctx, "child_num", ఖాళీ, 0, AV_OPT_శోధన_CHILDREN, &లక్ష్యం);
        ఒకవేళ (opt && లక్ష్యం == &బిడ్డ_ctx)
            రాయి("OK    '%s'\n", opt->name);
        లేకపోతే
            రాయి("Error 'child_num'\n");

        // Should fail. foo doesn't exist
        opt = av_opt_కనుగొను(&test_ctx, "foo", ఖాళీ, 0, 0);
        ఒకవేళ (opt)
            రాయి("OK    '%s'\n", opt->name);
        లేకపోతే
            రాయి("Error 'foo'\n");
    }

    రాయి("\nTesting av_opt_copy() into a memdup'ed object\n");
    {
        TestContext test_ctx = { 0 };
        TestContext *copy;
        uint8_t *layout_name = ఖాళీ;

        test_ctx.class = &test_class;
        av_opt_సమితి_defaults(&test_ctx);
        av_opt_సమితి(&test_ctx, "cl", "FL@Left+FR@Right", 0);

        copy = av_memdup(&test_ctx, పరిమాణం(test_ctx));
        ఒకవేళ (!copy)
            తిరిగి 1;
        av_opt_copy(copy, &test_ctx);
        av_opt_free(&test_ctx);

        av_opt_get(copy, "cl", 0, &layout_name);
        రాయి("cl=%s\n", layout_name);
        av_free(layout_name);
        av_opt_free(copy);
        av_free(copy);
    }

    రాయి("\nTesting av_opt_copy() of a native layout into a custom layout\n");
    {
        TestContext src = { 0 }, dst = { 0 };
        AVChannelLayout native = { AV_CHANNEL_క్రమం_NATIVE };

        src.class = dst.class = &test_class;
        av_opt_సమితి_defaults(&src);
        av_opt_సమితి_defaults(&dst);
        av_opt_సమితి(&dst, "cl", "FL@Left+FR@Right", 0);

        native.u.ముసుగు_2      = (uintptr_t)dst.channel_layout.u.map;
        native.nb_channels = av_popcount64(native.u.ముసుగు_2);
        av_opt_సమితి_chlayout(&src, "cl", &native, 0);

        రాయి("copy: %d\n", av_opt_copy(&dst, &src));
        రాయి("same layout: %d\n", !av_channel_layout_compare(&src.channel_layout, &dst.channel_layout));
        av_opt_free(&src);
        av_opt_free(&dst);
    }

    తిరిగి 0;
}
