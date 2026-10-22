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

#ضمن <limits.h>
#ضمن <stdio.h>

#ضمن "libavutil/common.h"
#ضمن "libavutil/channel_layout.h"
#ضمن "libavutil/error.h"
#ضمن "libavutil/log.h"
#ضمن "libavutil/mem.h"
#ضمن "libavutil/rational.h"
#ضمن "libavutil/opt.h"
#ضمن "libavutil/pixdesc.h"

تعريفنوع بنية TestContext {
    ثابت AVClass *class;
    بنية ماشوم_Context *ماشوم;
    صحيح عدد;
    صحيح unum;
    صحيح toggle;
    حرف *string;
    صحيح flags;
    AVRational rational;
    AVRational video_شرح;
    صحيح w, h;
    تعداد AVPixelFormat pix_fmt;
    تعداد AVSampleFormat sample_fmt;
    int64_t duration;
    uint8_t color[4];
    AVChannelLayout channel_layout;
    فراغ *دوګونی;
    صحيح دوګونی_اندازه;
    فراغ *binary1;
    صحيح دوګونی_size1;
    فراغ *binary2;
    صحيح دوګونی_size2;
    int64_t num64;
    عائم flt;
    مزدوج dbl;
    حرف *escape;
    صحيح bool1;
    صحيح bool2;
    صحيح bool3;
    AVDictionary *dict1;
    AVDictionary *dict2;

    صحيح           **array_int;
    بینښه     nb_array_int;

    حرف          **array_str;
    بینښه     nb_array_str;

    AVDictionary  **array_dict;
    بینښه     nb_array_dict;
} TestContext;

#تعریف_کړه دننه_واټن_2(x) offsetof(TestContext, x)

#تعریف_کړه TEST_FLAG_COOL 01
#تعریف_کړه TEST_FLAG_LAME 02
#تعریف_کړه TEST_FLAG_MU   04

ساكن ثابت AVOptionArrayDef array_str = {
    .sep         = '|',
    .def         = "str0|str\\|1|str\\\\2",
};

ساكن ثابت AVOptionArrayDef array_dict = {
    // there are three levels of escaping - C string, array option, dict - so 8 backslashes are needed to get a literal one inside a dict key/val
    .def         = "k00=v\\\\\\\\00:k01=v\\,01,k10=v\\\\=1\\\\:0",
};

ساكن ثابت AVOption test_options[]= {
    {"num",        "set num",            دننه_واټن_2(عدد),            AV_OPT_TYPE_INT,            { .i64 = 0 },                     -1,       100, 1 },
    {"unum",       "set unum",           دننه_واټن_2(unum),           AV_OPT_TYPE_UINT,           { .i64 = 1U << 31 },               0,  1U << 31, 1 },
    {"toggle",     "set toggle",         دننه_واټن_2(toggle),         AV_OPT_TYPE_INT,            { .i64 = 1 },                      0,         1, 1 },
    {"rational",   "set rational",       دننه_واټن_2(rational),       AV_OPT_TYPE_RATIONAL,       { .dbl = 1 },                      0,        10, 1 },
    {"string",     "set string",         دننه_واټن_2(string),         AV_OPT_TYPE_STRING,         { .str = "default" },       CHAR_MIN,  CHAR_MAX, 1 },
    {"escape",     "set escape str",     دننه_واټن_2(escape),         AV_OPT_TYPE_STRING,         { .str = "\\=," },          CHAR_MIN,  CHAR_MAX, 1 },
    {"flags",      "set flags",          دننه_واټن_2(flags),          AV_OPT_TYPE_FLAGS,          { .i64 = 1 },                      0,   لوی_عدد, 1, .unit = "flags" },
    {"cool",       "set cool flag",      0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_COOL },   INT_MIN,   لوی_عدد, 1, .unit = "flags" },
    {"lame",       "set lame flag",      0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_LAME },   INT_MIN,   لوی_عدد, 1, .unit = "flags" },
    {"mu",         "set mu flag",        0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_MU },     INT_MIN,   لوی_عدد, 1, .unit = "flags" },
    {"size",       "set size",           دننه_واټن_2(w),              AV_OPT_TYPE_IMAGE_اندازه,     { .str="200x300" },                0,         0, 1 },
    {"pix_fmt",    "set pixfmt",         دننه_واټن_2(pix_fmt),        AV_OPT_TYPE_PIXEL_FMT,      { .i64 = AV_PIX_FMT_0BGR },       -1,   لوی_عدد, 1 },
    {"sample_fmt", "set samplefmt",      دننه_واټن_2(sample_fmt),     AV_OPT_TYPE_SAMPLE_FMT,     { .i64 = AV_SAMPLE_FMT_S16 },     -1,   لوی_عدد, 1 },
    {"video_rate", "set videorate",      دننه_واټن_2(video_شرح),     AV_OPT_TYPE_VIDEO_شرح,     { .str = "25" },                   0,         لوی_عدد, 1 },
    {"duration",   "set duration",       دننه_واټن_2(duration),       AV_OPT_TYPE_DURATION,       { .i64 = 1000 },                   0, INT64_MAX, 1 },
    {"color",      "set color",          دننه_واټن_2(color),          AV_OPT_TYPE_COLOR,          { .str = "pink" },                 0,         0, 1 },
    {"cl",         "set channel layout", دننه_واټن_2(channel_layout), AV_OPT_TYPE_CHLAYOUT,       { .str = "hexagonal" },            0,         0, 1 },
    {"bin",        "set binary value",   دننه_واټن_2(دوګونی),         AV_OPT_TYPE_دوګونی,         { .str="62696e00" },               0,         0, 1 },
    {"bin1",       "set binary value",   دننه_واټن_2(binary1),        AV_OPT_TYPE_دوګونی,         { .str=عدم },                     0,         0, 1 },
    {"bin2",       "set binary value",   دننه_واټن_2(binary2),        AV_OPT_TYPE_دوګونی,         { .str="" },                       0,         0, 1 },
    {"num64",      "set num 64bit",      دننه_واټن_2(num64),          AV_OPT_TYPE_INT64,          { .i64 = 1LL << 32 },             -1, 1LL << 32, 1 },
    {"flt",        "set float",          دننه_واټن_2(flt),            AV_OPT_TYPE_FLOAT,          { .dbl = 1.0 / 3 },                0,       100, 1 },
    {"dbl",        "set double",         دننه_واټن_2(dbl),            AV_OPT_TYPE_DOUBLE,         { .dbl = 1.0 / 3 },                0,       100, 1 },
    {"bool1",      "set boolean value",  دننه_واټن_2(bool1),          AV_OPT_TYPE_BOOL,           { .i64 = -1 },                    -1,         1, 1 },
    {"bool2",      "set boolean value",  دننه_واټن_2(bool2),          AV_OPT_TYPE_BOOL,           { .i64 = 1 },                     -1,         1, 1 },
    {"bool3",      "set boolean value",  دننه_واټن_2(bool3),          AV_OPT_TYPE_BOOL,           { .i64 = 0 },                      0,         1, 1 },
    {"dict1",      "set dictionary value", دننه_واټن_2(dict1),        AV_OPT_TYPE_DICT,           { .str = عدم},                    0,         0, 1 },
    {"dict2",      "set dictionary value", دننه_واټن_2(dict2),        AV_OPT_TYPE_DICT,           { .str = "happy=':-)'"},           0,         0, 1 },
    {"array_int",  "array of ints",        دننه_واټن_2(array_int),    AV_OPT_TYPE_INT | AV_OPT_TYPE_FLAG_ARRAY, .max = لوی_عدد,           .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    {"array_str",  "array of strings",     دننه_واټن_2(array_str),    AV_OPT_TYPE_STRING | AV_OPT_TYPE_FLAG_ARRAY, { .arr = &array_str }, .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    {"array_dict", "array of dicts",       دننه_واټن_2(array_dict),   AV_OPT_TYPE_DICT | AV_OPT_TYPE_FLAG_ARRAY, { .arr = &array_dict },  .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    { عدم },
};

ساكن ثابت حرف *test_get_name(فراغ *ctx)
{
    أرجع "test";
}

تعريفنوع بنية ماشوم_Context {
    ثابت AVClass *class;
    int64_t ماشوم_num64;
    صحيح ماشوم_عدد;
    بینښه صحيح ماشوم_unum;
} ماشوم_Context;

#تعریف_لغوه دننه_واټن_2
#تعریف_کړه دننه_واټن_2(x) offsetof(ماشوم_Context, x)

ساكن ثابت AVOption ماشوم_options[]= {
    {"child_num64", "set num 64bit", دننه_واټن_2(ماشوم_num64), AV_OPT_TYPE_INT64, { .i64 = 0 }, 0, 100, 1 | AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY },
    {"child_num",   "set child_num", دننه_واټن_2(ماشوم_عدد),   AV_OPT_TYPE_INT,   { .i64 = 1 }, 0, 100, 1 },
    {"child_unum",  "set child_unum", دننه_واټن_2(ماشوم_unum),  AV_OPT_TYPE_UINT,  { .i64 = 0 }, 0, 100, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY },
    { عدم },
};

ساكن ثابت حرف *ماشوم_get_name(فراغ *ctx)
{
    أرجع "child";
}

ساكن ثابت AVClass ماشوم_class = {
    .class_name = "ChildContext",
    .توکی_name  = ماشوم_get_name,
    .option     = ماشوم_options,
    .نسخه    = LIBAVUTIL_نسخه_INT,
};

ساكن فراغ *test_ماشوم_بل(فراغ *obj, فراغ *prev)
{
    TestContext *test_ctx = obj;
    إذا (!prev)
        أرجع test_ctx->ماشوم;
    أرجع عدم;
}

ساكن ثابت AVClass test_class = {
    .class_name = "TestContext",
    .توکی_name  = test_get_name,
    .option     = test_options,
    .ماشوم_بل = test_ماشوم_بل,
    .نسخه    = LIBAVUTIL_نسخه_INT,
};

ساكن فراغ log_callback_help(فراغ *ptr, صحيح level, ثابت حرف *fmt, va_list vl)
{
    vfprintf(stdout, fmt, vl);
}

صحيح اصلي(فراغ)
{
    صحيح i;

    av_log_سېټ_level(AV_LOG_DEBUG);
    av_log_سېټ_callback(log_callback_help);

    چاپ_کړه("Testing default values\n");
    {
        TestContext test_ctx = { 0 };
        test_ctx.class = &test_class;
        av_opt_سېټ_defaults(&test_ctx);

        چاپ_کړه("num=%d\n", test_ctx.عدد);
        چاپ_کړه("unum=%u\n", test_ctx.unum);
        چاپ_کړه("toggle=%d\n", test_ctx.toggle);
        چاپ_کړه("string=%s\n", test_ctx.string);
        چاپ_کړه("escape=%s\n", test_ctx.escape);
        چاپ_کړه("flags=%d\n", test_ctx.flags);
        چاپ_کړه("rational=%d/%d\n", test_ctx.rational.عدد, test_ctx.rational.den);
        چاپ_کړه("video_rate=%d/%d\n", test_ctx.video_شرح.عدد, test_ctx.video_شرح.den);
        چاپ_کړه("width=%d height=%d\n", test_ctx.w, test_ctx.h);
        چاپ_کړه("pix_fmt=%s\n", av_get_pix_fmt_name(test_ctx.pix_fmt));
        چاپ_کړه("sample_fmt=%s\n", av_get_sample_fmt_name(test_ctx.sample_fmt));
        چاپ_کړه("duration=%"PRId64"\n", test_ctx.duration);
        چاپ_کړه("color=%d %d %d %d\n", test_ctx.color[0], test_ctx.color[1], test_ctx.color[2], test_ctx.color[3]);
        چاپ_کړه("channel_layout=%"PRId64"=%"PRId64"\n", test_ctx.channel_layout.u.ماسک_2, (int64_t)AV_CH_LAYOUT_HEXAGONAL);
        إذا (test_ctx.دوګونی)
            چاپ_کړه("binary=%x %x %x %x\n", ((uint8_t*)test_ctx.دوګونی)[0], ((uint8_t*)test_ctx.دوګونی)[1], ((uint8_t*)test_ctx.دوګونی)[2], ((uint8_t*)test_ctx.دوګونی)[3]);
        چاپ_کړه("binary_size=%d\n", test_ctx.دوګونی_اندازه);
        چاپ_کړه("num64=%"PRId64"\n", test_ctx.num64);
        چاپ_کړه("flt=%.6f\n", test_ctx.flt);
        چاپ_کړه("dbl=%.6f\n", test_ctx.dbl);

        لكل (بینښه i = 0; i < test_ctx.nb_array_str; i++)
            چاپ_کړه("array_str[%u]=%s\n", i, test_ctx.array_str[i]);

        لكل (بینښه i = 0; i < test_ctx.nb_array_dict; i++) {
            AVDictionary            *d = test_ctx.array_dict[i];
            ثابت AVDictionary_ثبت *e = عدم;

            طالما ((e = av_dict_iterate(d, e)))
                چاپ_کړه("array_dict[%u]: %s\t%s\n", i, e->کلی, e->ارزښت);
        }

        av_opt_show2(&test_ctx, عدم, -1, 0);

        av_opt_free(&test_ctx);
    }

    چاپ_کړه("\nTesting av_opt_is_set_to_default()\n");
    {
        صحيح ret;
        TestContext test_ctx = { 0 };
        ثابت AVOption *o = عدم;
        test_ctx.class = &test_class;

        av_log_سېټ_level(AV_LOG_QUIET);

        طالما (o = av_opt_بل(&test_ctx, o)) {
            ret = av_opt_is_سېټ_منزل_default_by_name(&test_ctx, o->name, 0);
            چاپ_کړه("name:%10s default:%d error:%s\n", o->name, !!ret, ret < 0 ? av_err2str(ret) : "");
        }
        av_opt_سېټ_defaults(&test_ctx);
        طالما (o = av_opt_بل(&test_ctx, o)) {
            ret = av_opt_is_سېټ_منزل_default_by_name(&test_ctx, o->name, 0);
            چاپ_کړه("name:%10s default:%d error:%s\n", o->name, !!ret, ret < 0 ? av_err2str(ret) : "");
        }
        av_opt_free(&test_ctx);
    }

    چاپ_کړه("\nTesting av_opt_get/av_opt_set()\n");
    {
        TestContext test_ctx = { 0 };
        TestContext test2_ctx = { 0 };
        ثابت AVOption *o = عدم;
        حرف *val = عدم;
        صحيح ret;

        test_ctx.class = &test_class;
        test2_ctx.class = &test_class;

        av_log_سېټ_level(AV_LOG_QUIET);

        av_opt_سېټ_defaults(&test_ctx);

        طالما (o = av_opt_بل(&test_ctx, o)) {
            حرف *value1 = عدم;
            حرف *value2 = عدم;
            صحيح ret1 = AVERROR_BUG;
            صحيح ret2 = AVERROR_BUG;
            صحيح ret3 = AVERROR_BUG;

            إذا (o->type == AV_OPT_TYPE_CONST)
                استمر;

            ret1 = av_opt_get(&test_ctx, o->name, 0, (uint8_t **)&value1);
            إذا (ret1 >= 0) {
                ret2 = av_opt_سېټ(&test2_ctx, o->name, value1, 0);
                إذا (ret2 >= 0)
                    ret3 = av_opt_get(&test2_ctx, o->name, 0, (uint8_t **)&value2);
            }

            چاپ_کړه("name: %-11s get: %-16s set: %-16s get: %-16s %s\n", o->name,
                    ret1 >= 0 ? value1 : av_err2str(ret1),
                    ret2 >= 0 ? "OK" : av_err2str(ret2),
                    ret3 >= 0 ? value2 : av_err2str(ret3),
                    ret1 >= 0 && ret2 >= 0 && ret3 >= 0 && !strcmp(value1, value2) ? "OK" : "Mismatch");
            av_free(value1);
            av_free(value2);
        }

        // av_opt_set(NULL) with an array option resets it
        ret = av_opt_سېټ(&test_ctx, "array_dict", عدم, 0);
        چاپ_کړه("av_opt_set(\"array_dict\", NULL) -> %d\n", ret);
        چاپ_کړه("array_dict=%sNULL; nb_array_dict=%u\n",
               test_ctx.array_dict ? "non-" : "", test_ctx.nb_array_dict);

        // av_opt_get() on an empty array should return a NULL string
        ret = av_opt_get(&test_ctx, "array_dict", AV_OPT_ALLOW_NULL, (uint8_t**)&val);
        چاپ_کړه("av_opt_get(\"array_dict\") -> %s\n", val ? val : "NULL");

        av_opt_free(&test_ctx);
        av_opt_free(&test2_ctx);
    }

    چاپ_کړه("\nTesting av_opt_get_array()\n");
    {
        ساكن ثابت صحيح int_array[] = { 5, 0, 42, 137, لوی_عدد };

        TestContext test_ctx = { 0 };

        صحيح     بهر_int   [FF_ARRAY_ELEMS(int_array)] = { 0 };
        مزدوج  بهر_double[FF_ARRAY_ELEMS(int_array)] = { 0. };
        حرف   *بهر_str   [FF_ARRAY_ELEMS(int_array)] = { عدم };
        AVDictionary *بهر_dict[2] = { عدم };

        صحيح ret;

        test_ctx.class = &test_class;

        av_log_سېټ_level(AV_LOG_QUIET);

        av_opt_سېټ_defaults(&test_ctx);

        test_ctx.array_int    = av_memdup(int_array, حجم(int_array));
        test_ctx.nb_array_int = FF_ARRAY_ELEMS(int_array);

        // retrieve as int
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               1, 3, AV_OPT_TYPE_INT, بهر_int);
        چاپ_کړه("av_opt_get_array(\"array_int\", 1, 3, INT)=%d -> [ %d, %d, %d ]\n",
               ret, بهر_int[0], بهر_int[1], بهر_int[2]);

        // retrieve as double
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               3, 2, AV_OPT_TYPE_DOUBLE, بهر_double);
        چاپ_کړه("av_opt_get_array(\"array_int\", 3, 2, DOUBLE)=%d -> [ %.2f, %.2f ]\n",
               ret, بهر_double[0], بهر_double[1]);

        // retrieve as str
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               0, 5, AV_OPT_TYPE_STRING, بهر_str);
        چاپ_کړه("av_opt_get_array(\"array_int\", 0, 5, STRING)=%d -> "
               "[ %s, %s, %s, %s, %s ]\n", ret,
               بهر_str[0], بهر_str[1], بهر_str[2], بهر_str[3], بهر_str[4]);

        لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(بهر_str); i++)
            av_freep(&بهر_str[i]);

        ret = av_opt_get_array(&test_ctx, "array_dict", 0, 0, 2,
                               AV_OPT_TYPE_DICT, بهر_dict);
        چاپ_کړه("av_opt_get_array(\"array_dict\", 0, 2, DICT)=%d\n", ret);

        لكل (صحيح i = 0; i < test_ctx.nb_array_dict; i++) {
            ثابت AVDictionary_ثبت *e = عدم;
            طالما ((e = av_dict_iterate(test_ctx.array_dict[i], e))) {
                ثابت AVDictionary_ثبت *e1 = av_dict_get(بهر_dict[i], e->کلی, عدم, 0);
                إذا (!e1 || strcmp(e->ارزښت, e1->ارزښت)) {
                    چاپ_کړه("mismatching dict entry %s: %s/%s\n",
                           e->کلی, e->ارزښت, e1 ? e1->ارزښت : "<missing>");
                }
            }
            av_dict_free(&بهر_dict[i]);
        }

        av_opt_free(&test_ctx);
    }

    چاپ_کړه("\nTest av_opt_serialize()\n");
    {
        TestContext test_ctx = { 0 };
        حرف *buf;
        صحيح ret;
        test_ctx.class = &test_class;

        av_log_سېټ_level(AV_LOG_QUIET);

        av_opt_سېټ_defaults(&test_ctx);
        إذا (av_opt_serialize(&test_ctx, 0, 0, &buf, '=', ',') >= 0) {
            چاپ_کړه("%s\n", buf);
            av_opt_free(&test_ctx);
            memset(&test_ctx, 0, حجم(test_ctx));
            test_ctx.class = &test_class;
            ret = av_سېټ_options_string(&test_ctx, buf, "=", ",");
            av_free(buf);
            إذا (ret < 0)
                چاپ_کړه("Error ret '%d'\n", ret);
            إذا (av_opt_serialize(&test_ctx, 0, 0, &buf, '=', ',') >= 0) {
                ماشوم_Context ماشوم_ctx = { .ماشوم_num64 = 1, .ماشوم_unum = 1 };
                چاپ_کړه("%s\n", buf);
                av_free(buf);
                ماشوم_ctx.class = &ماشوم_class;
                test_ctx.ماشوم = &ماشوم_ctx;
                چاپ_کړه("Exclude flag EXPORT:\n");
                إذا (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_پلټنه_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    چاپ_کړه("%s\n", buf);
                    av_free(buf);
                }
                چاپ_کړه("Include flag EXPORT:\n");
                إذا (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_پلټنه_CHILDREN,
                                     &buf, '=', ',') >= 0) {
                    چاپ_کړه("%s\n", buf);
                    av_free(buf);
                }
                چاپ_کړه("Exclude flag 1:\n");
                إذا (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_پلټنه_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    چاپ_کړه("%s\n", buf);
                    av_free(buf);
                }
                چاپ_کړه("Include flag 1:\n");
                إذا (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_پلټنه_CHILDREN,
                                     &buf, '=', ',') >= 0) {
                    چاپ_کړه("%s\n", buf);
                    av_free(buf);
                }
                چاپ_کړه("Exclude exact match flag 1:\n");
                إذا (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_پلټنه_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT|AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    چاپ_کړه("%s\n", buf);
                    av_free(buf);
                }
                چاپ_کړه("Include exact match flag 1:\n");
                إذا (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_پلټنه_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT,
                                     &buf, '=', ',') >= 0) {
                    چاپ_کړه("%s\n", buf);
                    av_free(buf);
                }
                چاپ_کړه("Exclude exact match flag EXPORT|READONLY:\n");
                إذا (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_پلټنه_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT|AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    چاپ_کړه("%s\n", buf);
                    av_free(buf);
                }
                چاپ_کړه("Include exact match flag EXPORT|READONLY:\n");
                إذا (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_پلټنه_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT,
                                     &buf, '=', ',') >= 0) {
                    چاپ_کړه("%s\n", buf);
                    av_free(buf);
                }
                av_opt_free(&ماشوم_ctx);
                test_ctx.ماشوم = عدم;
            }
        }
        av_opt_free(&test_ctx);
    }

    چاپ_کړه("\nTesting av_set_options_string()\n");
    {
        TestContext test_ctx = { 0 };
        ساكن ثابت حرف * ثابت options[] = {
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
        av_opt_سېټ_defaults(&test_ctx);

        av_log_سېټ_level(AV_LOG_QUIET);

        لكل (i=0; i < FF_ARRAY_ELEMS(options); i++) {
            صحيح silence_log = !strcmp(options[i], "rational=-1/0"); // inf formatting differs between platforms
            av_log(&test_ctx, AV_LOG_DEBUG, "Setting options string '%s'\n", options[i]);
            إذا (silence_log)
                av_log_سېټ_callback(عدم);
            إذا (av_سېټ_options_string(&test_ctx, options[i], "=", ":") < 0)
                چاپ_کړه("Error '%s'\n", options[i]);
            وإلا
                چاپ_کړه("OK    '%s'\n", options[i]);
            av_log_سېټ_callback(log_callback_help);
        }
        av_opt_free(&test_ctx);
    }

    چاپ_کړه("\nTesting av_opt_set_from_string()\n");
    {
        TestContext test_ctx = { 0 };
        ساكن ثابت حرف * ثابت options[] = {
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
        ساكن ثابت حرف * ثابت shorthand[] = { "num", "string", عدم };

        test_ctx.class = &test_class;
        av_opt_سېټ_defaults(&test_ctx);

        av_log_سېټ_level(AV_LOG_QUIET);

        لكل (i=0; i < FF_ARRAY_ELEMS(options); i++) {
            av_log(&test_ctx, AV_LOG_DEBUG, "Setting options string '%s'\n", options[i]);
            إذا (av_opt_سېټ_from_string(&test_ctx, options[i], shorthand, "=", ":") < 0)
                چاپ_کړه("Error '%s'\n", options[i]);
            وإلا
                چاپ_کړه("OK    '%s'\n", options[i]);
        }
        av_opt_free(&test_ctx);
    }

    چاپ_کړه("\nTesting av_opt_find2()\n");
    {
        TestContext test_ctx = { 0 };
        ماشوم_Context ماشوم_ctx = { 0 };
        فراغ *موخه;
        ثابت AVOption *opt;

        test_ctx.class = &test_class;
        ماشوم_ctx.class = &ماشوم_class;
        test_ctx.ماشوم = &ماشوم_ctx;

        av_log_سېټ_level(AV_LOG_QUIET);

        // Should succeed. num exists and has opt_flags 1
        opt = av_opt_find2(&test_ctx, "num", عدم, 1, 0, &موخه);
        إذا (opt && موخه == &test_ctx)
            چاپ_کړه("OK    '%s'\n", opt->name);
        وإلا
            چاپ_کړه("Error 'num'\n");

        // Should fail. num64 exists but has opt_flags 1, not 2
        opt = av_opt_پیدا_کړه(&test_ctx, "num64", عدم, 2, 0);
        إذا (opt)
            چاپ_کړه("OK    '%s'\n", opt->name);
        وإلا
            چاپ_کړه("Error 'num64'\n");

        // Should fail. child_num exists but in a child object we're not searching
        opt = av_opt_پیدا_کړه(&test_ctx, "child_num", عدم, 0, 0);
        إذا (opt)
            چاپ_کړه("OK    '%s'\n", opt->name);
        وإلا
            چاپ_کړه("Error 'child_num'\n");

        // Should succeed. child_num exists in a child object we're searching
        opt = av_opt_find2(&test_ctx, "child_num", عدم, 0, AV_OPT_پلټنه_CHILDREN, &موخه);
        إذا (opt && موخه == &ماشوم_ctx)
            چاپ_کړه("OK    '%s'\n", opt->name);
        وإلا
            چاپ_کړه("Error 'child_num'\n");

        // Should fail. foo doesn't exist
        opt = av_opt_پیدا_کړه(&test_ctx, "foo", عدم, 0, 0);
        إذا (opt)
            چاپ_کړه("OK    '%s'\n", opt->name);
        وإلا
            چاپ_کړه("Error 'foo'\n");
    }

    چاپ_کړه("\nTesting av_opt_copy() into a memdup'ed object\n");
    {
        TestContext test_ctx = { 0 };
        TestContext *copy;
        uint8_t *layout_name = عدم;

        test_ctx.class = &test_class;
        av_opt_سېټ_defaults(&test_ctx);
        av_opt_سېټ(&test_ctx, "cl", "FL@Left+FR@Right", 0);

        copy = av_memdup(&test_ctx, حجم(test_ctx));
        إذا (!copy)
            أرجع 1;
        av_opt_copy(copy, &test_ctx);
        av_opt_free(&test_ctx);

        av_opt_get(copy, "cl", 0, &layout_name);
        چاپ_کړه("cl=%s\n", layout_name);
        av_free(layout_name);
        av_opt_free(copy);
        av_free(copy);
    }

    چاپ_کړه("\nTesting av_opt_copy() of a native layout into a custom layout\n");
    {
        TestContext src = { 0 }, dst = { 0 };
        AVChannelLayout native = { AV_CHANNEL_ترتیب_NATIVE };

        src.class = dst.class = &test_class;
        av_opt_سېټ_defaults(&src);
        av_opt_سېټ_defaults(&dst);
        av_opt_سېټ(&dst, "cl", "FL@Left+FR@Right", 0);

        native.u.ماسک_2      = (uintptr_t)dst.channel_layout.u.map;
        native.nb_channels = av_popcount64(native.u.ماسک_2);
        av_opt_سېټ_chlayout(&src, "cl", &native, 0);

        چاپ_کړه("copy: %d\n", av_opt_copy(&dst, &src));
        چاپ_کړه("same layout: %d\n", !av_channel_layout_compare(&src.channel_layout, &dst.channel_layout));
        av_opt_free(&src);
        av_opt_free(&dst);
    }

    أرجع 0;
}
