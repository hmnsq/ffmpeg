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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/common.h"
#अन्तर्भाव "libavutil/channel_layout.h"
#अन्तर्भाव "libavutil/error.h"
#अन्तर्भाव "libavutil/log.h"
#अन्तर्भाव "libavutil/mem.h"
#अन्तर्भाव "libavutil/rational.h"
#अन्तर्भाव "libavutil/opt.h"
#अन्तर्भाव "libavutil/pixdesc.h"

प्रकारव्याख्या संरचना TestContext {
    स्थिरांक AVClass *class;
    संरचना ChildContext *child;
    पूर्णांक अंक;
    पूर्णांक unum;
    पूर्णांक toggle;
    अक्षर *string;
    पूर्णांक flags;
    AVRational rational;
    AVRational video_rate;
    पूर्णांक w, h;
    गणना AVPixelFormat pix_fmt;
    गणना AVSampleFormat sample_fmt;
    int64_t duration;
    uint8_t color[4];
    AVChannelLayout channel_layout;
    शून्य *द्विमान;
    पूर्णांक द्विमान_size;
    शून्य *binary1;
    पूर्णांक द्विमान_size1;
    शून्य *binary2;
    पूर्णांक द्विमान_size2;
    int64_t num64;
    दशांश flt;
    द्विगुण dbl;
    अक्षर *escape;
    पूर्णांक bool1;
    पूर्णांक bool2;
    पूर्णांक bool3;
    AVDictionary *dict1;
    AVDictionary *dict2;

    पूर्णांक           **array_int;
    अचिन्हित     nb_array_int;

    अक्षर          **array_str;
    अचिन्हित     nb_array_str;

    AVDictionary  **array_dict;
    अचिन्हित     nb_array_dict;
} TestContext;

#define OFFSET(x) दुरत्व(TestContext, x)

#define TEST_FLAG_COOL 01
#define TEST_FLAG_LAME 02
#define TEST_FLAG_MU   04

स्थिर स्थिरांक AVOptionArrayDef array_str = {
    .sep         = '|',
    .def         = "str0|str\\|1|str\\\\2",
};

स्थिर स्थिरांक AVOptionArrayDef array_dict = {
    // there are three levels of escaping - C string, array option, dict - so 8 backslashes are needed to get a literal one inside a dict key/val
    .def         = "k00=v\\\\\\\\00:k01=v\\,01,k10=v\\\\=1\\\\:0",
};

स्थिर स्थिरांक AVOption test_options[]= {
    {"num",        "set num",            OFFSET(अंक),            AV_OPT_TYPE_INT,            { .i64 = 0 },                     -1,       100, 1 },
    {"unum",       "set unum",           OFFSET(unum),           AV_OPT_TYPE_UINT,           { .i64 = 1U << 31 },               0,  1U << 31, 1 },
    {"toggle",     "set toggle",         OFFSET(toggle),         AV_OPT_TYPE_INT,            { .i64 = 1 },                      0,         1, 1 },
    {"rational",   "set rational",       OFFSET(rational),       AV_OPT_TYPE_RATIONAL,       { .dbl = 1 },                      0,        10, 1 },
    {"string",     "set string",         OFFSET(string),         AV_OPT_TYPE_STRING,         { .str = "default" },       अक्षर_न्यून,  अक्षर_उच्च, 1 },
    {"escape",     "set escape str",     OFFSET(escape),         AV_OPT_TYPE_STRING,         { .str = "\\=," },          अक्षर_न्यून,  अक्षर_उच्च, 1 },
    {"flags",      "set flags",          OFFSET(flags),          AV_OPT_TYPE_FLAGS,          { .i64 = 1 },                      0,   पूर्णांक_उच्च, 1, .unit = "flags" },
    {"cool",       "set cool flag",      0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_COOL },   पूर्णांक_न्यून,   पूर्णांक_उच्च, 1, .unit = "flags" },
    {"lame",       "set lame flag",      0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_LAME },   पूर्णांक_न्यून,   पूर्णांक_उच्च, 1, .unit = "flags" },
    {"mu",         "set mu flag",        0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_MU },     पूर्णांक_न्यून,   पूर्णांक_उच्च, 1, .unit = "flags" },
    {"size",       "set size",           OFFSET(w),              AV_OPT_TYPE_IMAGE_SIZE,     { .str="200x300" },                0,         0, 1 },
    {"pix_fmt",    "set pixfmt",         OFFSET(pix_fmt),        AV_OPT_TYPE_PIXEL_FMT,      { .i64 = AV_PIX_FMT_0BGR },       -1,   पूर्णांक_उच्च, 1 },
    {"sample_fmt", "set samplefmt",      OFFSET(sample_fmt),     AV_OPT_TYPE_SAMPLE_FMT,     { .i64 = AV_SAMPLE_FMT_S16 },     -1,   पूर्णांक_उच्च, 1 },
    {"video_rate", "set videorate",      OFFSET(video_rate),     AV_OPT_TYPE_VIDEO_RATE,     { .str = "25" },                   0,         पूर्णांक_उच्च, 1 },
    {"duration",   "set duration",       OFFSET(duration),       AV_OPT_TYPE_DURATION,       { .i64 = 1000 },                   0, INT64_MAX, 1 },
    {"color",      "set color",          OFFSET(color),          AV_OPT_TYPE_COLOR,          { .str = "pink" },                 0,         0, 1 },
    {"cl",         "set channel layout", OFFSET(channel_layout), AV_OPT_TYPE_CHLAYOUT,       { .str = "hexagonal" },            0,         0, 1 },
    {"bin",        "set binary value",   OFFSET(द्विमान),         AV_OPT_TYPE_द्विमान,         { .str="62696e00" },               0,         0, 1 },
    {"bin1",       "set binary value",   OFFSET(binary1),        AV_OPT_TYPE_द्विमान,         { .str=रिक्त },                     0,         0, 1 },
    {"bin2",       "set binary value",   OFFSET(binary2),        AV_OPT_TYPE_द्विमान,         { .str="" },                       0,         0, 1 },
    {"num64",      "set num 64bit",      OFFSET(num64),          AV_OPT_TYPE_INT64,          { .i64 = 1LL << 32 },             -1, 1LL << 32, 1 },
    {"flt",        "set float",          OFFSET(flt),            AV_OPT_TYPE_FLOAT,          { .dbl = 1.0 / 3 },                0,       100, 1 },
    {"dbl",        "set double",         OFFSET(dbl),            AV_OPT_TYPE_DOUBLE,         { .dbl = 1.0 / 3 },                0,       100, 1 },
    {"bool1",      "set boolean value",  OFFSET(bool1),          AV_OPT_TYPE_BOOL,           { .i64 = -1 },                    -1,         1, 1 },
    {"bool2",      "set boolean value",  OFFSET(bool2),          AV_OPT_TYPE_BOOL,           { .i64 = 1 },                     -1,         1, 1 },
    {"bool3",      "set boolean value",  OFFSET(bool3),          AV_OPT_TYPE_BOOL,           { .i64 = 0 },                      0,         1, 1 },
    {"dict1",      "set dictionary value", OFFSET(dict1),        AV_OPT_TYPE_DICT,           { .str = रिक्त},                    0,         0, 1 },
    {"dict2",      "set dictionary value", OFFSET(dict2),        AV_OPT_TYPE_DICT,           { .str = "happy=':-)'"},           0,         0, 1 },
    {"array_int",  "array of ints",        OFFSET(array_int),    AV_OPT_TYPE_INT | AV_OPT_TYPE_FLAG_ARRAY, .max = पूर्णांक_उच्च,           .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    {"array_str",  "array of strings",     OFFSET(array_str),    AV_OPT_TYPE_STRING | AV_OPT_TYPE_FLAG_ARRAY, { .arr = &array_str }, .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    {"array_dict", "array of dicts",       OFFSET(array_dict),   AV_OPT_TYPE_DICT | AV_OPT_TYPE_FLAG_ARRAY, { .arr = &array_dict },  .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    { रिक्त },
};

स्थिर स्थिरांक अक्षर *test_get_name(शून्य *ctx)
{
    परत "test";
}

प्रकारव्याख्या संरचना ChildContext {
    स्थिरांक AVClass *class;
    int64_t child_num64;
    पूर्णांक child_अंक;
    अचिन्हित पूर्णांक child_unum;
} ChildContext;

#undef OFFSET
#define OFFSET(x) दुरत्व(ChildContext, x)

स्थिर स्थिरांक AVOption child_options[]= {
    {"child_num64", "set num 64bit", OFFSET(child_num64), AV_OPT_TYPE_INT64, { .i64 = 0 }, 0, 100, 1 | AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY },
    {"child_num",   "set child_num", OFFSET(child_अंक),   AV_OPT_TYPE_INT,   { .i64 = 1 }, 0, 100, 1 },
    {"child_unum",  "set child_unum", OFFSET(child_unum),  AV_OPT_TYPE_UINT,  { .i64 = 0 }, 0, 100, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY },
    { रिक्त },
};

स्थिर स्थिरांक अक्षर *child_get_name(शून्य *ctx)
{
    परत "child";
}

स्थिर स्थिरांक AVClass child_class = {
    .class_name = "ChildContext",
    .item_name  = child_get_name,
    .option     = child_options,
    .version    = LIBAVUTIL_VERSION_INT,
};

स्थिर शून्य *test_child_next(शून्य *obj, शून्य *prev)
{
    TestContext *test_ctx = obj;
    जर (!prev)
        परत test_ctx->child;
    परत रिक्त;
}

स्थिर स्थिरांक AVClass test_class = {
    .class_name = "TestContext",
    .item_name  = test_get_name,
    .option     = test_options,
    .child_next = test_child_next,
    .version    = LIBAVUTIL_VERSION_INT,
};

स्थिर शून्य log_callback_help(शून्य *ptr, पूर्णांक level, स्थिरांक अक्षर *fmt, बहु_सूची vl)
{
    भख_लिखो(मानक_निकास, fmt, vl);
}

पूर्णांक main(शून्य)
{
    पूर्णांक i;

    av_log_set_level(AV_LOG_DEBUG);
    av_log_set_callback(log_callback_help);

    म_लिखो("Testing default values\n");
    {
        TestContext test_ctx = { 0 };
        test_ctx.class = &test_class;
        av_opt_set_defaults(&test_ctx);

        म_लिखो("num=%d\n", test_ctx.अंक);
        म_लिखो("unum=%u\n", test_ctx.unum);
        म_लिखो("toggle=%d\n", test_ctx.toggle);
        म_लिखो("string=%s\n", test_ctx.string);
        म_लिखो("escape=%s\n", test_ctx.escape);
        म_लिखो("flags=%d\n", test_ctx.flags);
        म_लिखो("rational=%d/%d\n", test_ctx.rational.अंक, test_ctx.rational.den);
        म_लिखो("video_rate=%d/%d\n", test_ctx.video_rate.अंक, test_ctx.video_rate.den);
        म_लिखो("width=%d height=%d\n", test_ctx.w, test_ctx.h);
        म_लिखो("pix_fmt=%s\n", av_get_pix_fmt_name(test_ctx.pix_fmt));
        म_लिखो("sample_fmt=%s\n", av_get_sample_fmt_name(test_ctx.sample_fmt));
        म_लिखो("duration=%"PRId64"\n", test_ctx.duration);
        म_लिखो("color=%d %d %d %d\n", test_ctx.color[0], test_ctx.color[1], test_ctx.color[2], test_ctx.color[3]);
        म_लिखो("channel_layout=%"PRId64"=%"PRId64"\n", test_ctx.channel_layout.u.mask, (int64_t)AV_CH_LAYOUT_HEXAGONAL);
        जर (test_ctx.द्विमान)
            म_लिखो("binary=%x %x %x %x\n", ((uint8_t*)test_ctx.द्विमान)[0], ((uint8_t*)test_ctx.द्विमान)[1], ((uint8_t*)test_ctx.द्विमान)[2], ((uint8_t*)test_ctx.द्विमान)[3]);
        म_लिखो("binary_size=%d\n", test_ctx.द्विमान_size);
        म_लिखो("num64=%"PRId64"\n", test_ctx.num64);
        म_लिखो("flt=%.6f\n", test_ctx.flt);
        म_लिखो("dbl=%.6f\n", test_ctx.dbl);

        साठी (अचिन्हित i = 0; i < test_ctx.nb_array_str; i++)
            म_लिखो("array_str[%u]=%s\n", i, test_ctx.array_str[i]);

        साठी (अचिन्हित i = 0; i < test_ctx.nb_array_dict; i++) {
            AVDictionary            *d = test_ctx.array_dict[i];
            स्थिरांक AVDictionaryEntry *e = रिक्त;

            पर्यंत ((e = av_dict_iterate(d, e)))
                म_लिखो("array_dict[%u]: %s\t%s\n", i, e->किल्ली, e->मूल्य);
        }

        av_opt_show2(&test_ctx, रिक्त, -1, 0);

        av_opt_free(&test_ctx);
    }

    म_लिखो("\nTesting av_opt_is_set_to_default()\n");
    {
        पूर्णांक ret;
        TestContext test_ctx = { 0 };
        स्थिरांक AVOption *o = रिक्त;
        test_ctx.class = &test_class;

        av_log_set_level(AV_LOG_QUIET);

        पर्यंत (o = av_opt_next(&test_ctx, o)) {
            ret = av_opt_is_set_to_default_by_name(&test_ctx, o->name, 0);
            म_लिखो("name:%10s default:%d error:%s\n", o->name, !!ret, ret < 0 ? av_err2str(ret) : "");
        }
        av_opt_set_defaults(&test_ctx);
        पर्यंत (o = av_opt_next(&test_ctx, o)) {
            ret = av_opt_is_set_to_default_by_name(&test_ctx, o->name, 0);
            म_लिखो("name:%10s default:%d error:%s\n", o->name, !!ret, ret < 0 ? av_err2str(ret) : "");
        }
        av_opt_free(&test_ctx);
    }

    म_लिखो("\nTesting av_opt_get/av_opt_set()\n");
    {
        TestContext test_ctx = { 0 };
        TestContext test2_ctx = { 0 };
        स्थिरांक AVOption *o = रिक्त;
        अक्षर *val = रिक्त;
        पूर्णांक ret;

        test_ctx.class = &test_class;
        test2_ctx.class = &test_class;

        av_log_set_level(AV_LOG_QUIET);

        av_opt_set_defaults(&test_ctx);

        पर्यंत (o = av_opt_next(&test_ctx, o)) {
            अक्षर *value1 = रिक्त;
            अक्षर *value2 = रिक्त;
            पूर्णांक ret1 = AVERROR_BUG;
            पूर्णांक ret2 = AVERROR_BUG;
            पूर्णांक ret3 = AVERROR_BUG;

            जर (o->type == AV_OPT_TYPE_CONST)
                सुरूठेवा;

            ret1 = av_opt_get(&test_ctx, o->name, 0, (uint8_t **)&value1);
            जर (ret1 >= 0) {
                ret2 = av_opt_set(&test2_ctx, o->name, value1, 0);
                जर (ret2 >= 0)
                    ret3 = av_opt_get(&test2_ctx, o->name, 0, (uint8_t **)&value2);
            }

            म_लिखो("name: %-11s get: %-16s set: %-16s get: %-16s %s\n", o->name,
                    ret1 >= 0 ? value1 : av_err2str(ret1),
                    ret2 >= 0 ? "OK" : av_err2str(ret2),
                    ret3 >= 0 ? value2 : av_err2str(ret3),
                    ret1 >= 0 && ret2 >= 0 && ret3 >= 0 && !म_भेद(value1, value2) ? "OK" : "Mismatch");
            av_free(value1);
            av_free(value2);
        }

        // av_opt_set(NULL) with an array option resets it
        ret = av_opt_set(&test_ctx, "array_dict", रिक्त, 0);
        म_लिखो("av_opt_set(\"array_dict\", NULL) -> %d\n", ret);
        म_लिखो("array_dict=%sNULL; nb_array_dict=%u\n",
               test_ctx.array_dict ? "non-" : "", test_ctx.nb_array_dict);

        // av_opt_get() on an empty array should return a NULL string
        ret = av_opt_get(&test_ctx, "array_dict", AV_OPT_ALLOW_NULL, (uint8_t**)&val);
        म_लिखो("av_opt_get(\"array_dict\") -> %s\n", val ? val : "NULL");

        av_opt_free(&test_ctx);
        av_opt_free(&test2_ctx);
    }

    म_लिखो("\nTesting av_opt_get_array()\n");
    {
        स्थिर स्थिरांक पूर्णांक int_array[] = { 5, 0, 42, 137, पूर्णांक_उच्च };

        TestContext test_ctx = { 0 };

        पूर्णांक     out_int   [FF_ARRAY_ELEMS(int_array)] = { 0 };
        द्विगुण  out_double[FF_ARRAY_ELEMS(int_array)] = { 0. };
        अक्षर   *out_str   [FF_ARRAY_ELEMS(int_array)] = { रिक्त };
        AVDictionary *out_dict[2] = { रिक्त };

        पूर्णांक ret;

        test_ctx.class = &test_class;

        av_log_set_level(AV_LOG_QUIET);

        av_opt_set_defaults(&test_ctx);

        test_ctx.array_int    = av_memdup(int_array, आकार(int_array));
        test_ctx.nb_array_int = FF_ARRAY_ELEMS(int_array);

        // retrieve as int
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               1, 3, AV_OPT_TYPE_INT, out_int);
        म_लिखो("av_opt_get_array(\"array_int\", 1, 3, INT)=%d -> [ %d, %d, %d ]\n",
               ret, out_int[0], out_int[1], out_int[2]);

        // retrieve as double
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               3, 2, AV_OPT_TYPE_DOUBLE, out_double);
        म_लिखो("av_opt_get_array(\"array_int\", 3, 2, DOUBLE)=%d -> [ %.2f, %.2f ]\n",
               ret, out_double[0], out_double[1]);

        // retrieve as str
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               0, 5, AV_OPT_TYPE_STRING, out_str);
        म_लिखो("av_opt_get_array(\"array_int\", 0, 5, STRING)=%d -> "
               "[ %s, %s, %s, %s, %s ]\n", ret,
               out_str[0], out_str[1], out_str[2], out_str[3], out_str[4]);

        साठी (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(out_str); i++)
            av_freep(&out_str[i]);

        ret = av_opt_get_array(&test_ctx, "array_dict", 0, 0, 2,
                               AV_OPT_TYPE_DICT, out_dict);
        म_लिखो("av_opt_get_array(\"array_dict\", 0, 2, DICT)=%d\n", ret);

        साठी (पूर्णांक i = 0; i < test_ctx.nb_array_dict; i++) {
            स्थिरांक AVDictionaryEntry *e = रिक्त;
            पर्यंत ((e = av_dict_iterate(test_ctx.array_dict[i], e))) {
                स्थिरांक AVDictionaryEntry *e1 = av_dict_get(out_dict[i], e->किल्ली, रिक्त, 0);
                जर (!e1 || म_भेद(e->मूल्य, e1->मूल्य)) {
                    म_लिखो("mismatching dict entry %s: %s/%s\n",
                           e->किल्ली, e->मूल्य, e1 ? e1->मूल्य : "<missing>");
                }
            }
            av_dict_free(&out_dict[i]);
        }

        av_opt_free(&test_ctx);
    }

    म_लिखो("\nTest av_opt_serialize()\n");
    {
        TestContext test_ctx = { 0 };
        अक्षर *buf;
        पूर्णांक ret;
        test_ctx.class = &test_class;

        av_log_set_level(AV_LOG_QUIET);

        av_opt_set_defaults(&test_ctx);
        जर (av_opt_serialize(&test_ctx, 0, 0, &buf, '=', ',') >= 0) {
            म_लिखो("%s\n", buf);
            av_opt_free(&test_ctx);
            स_रखो(&test_ctx, 0, आकार(test_ctx));
            test_ctx.class = &test_class;
            ret = av_set_options_string(&test_ctx, buf, "=", ",");
            av_free(buf);
            जर (ret < 0)
                म_लिखो("Error ret '%d'\n", ret);
            जर (av_opt_serialize(&test_ctx, 0, 0, &buf, '=', ',') >= 0) {
                ChildContext child_ctx = { .child_num64 = 1, .child_unum = 1 };
                म_लिखो("%s\n", buf);
                av_free(buf);
                child_ctx.class = &child_class;
                test_ctx.child = &child_ctx;
                म_लिखो("Exclude flag EXPORT:\n");
                जर (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_शोध_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    म_लिखो("%s\n", buf);
                    av_free(buf);
                }
                म_लिखो("Include flag EXPORT:\n");
                जर (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_शोध_CHILDREN,
                                     &buf, '=', ',') >= 0) {
                    म_लिखो("%s\n", buf);
                    av_free(buf);
                }
                म_लिखो("Exclude flag 1:\n");
                जर (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_शोध_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    म_लिखो("%s\n", buf);
                    av_free(buf);
                }
                म_लिखो("Include flag 1:\n");
                जर (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_शोध_CHILDREN,
                                     &buf, '=', ',') >= 0) {
                    म_लिखो("%s\n", buf);
                    av_free(buf);
                }
                म_लिखो("Exclude exact match flag 1:\n");
                जर (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_शोध_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT|AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    म_लिखो("%s\n", buf);
                    av_free(buf);
                }
                म_लिखो("Include exact match flag 1:\n");
                जर (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_शोध_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT,
                                     &buf, '=', ',') >= 0) {
                    म_लिखो("%s\n", buf);
                    av_free(buf);
                }
                म_लिखो("Exclude exact match flag EXPORT|READONLY:\n");
                जर (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_शोध_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT|AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    म_लिखो("%s\n", buf);
                    av_free(buf);
                }
                म_लिखो("Include exact match flag EXPORT|READONLY:\n");
                जर (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_शोध_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT,
                                     &buf, '=', ',') >= 0) {
                    म_लिखो("%s\n", buf);
                    av_free(buf);
                }
                av_opt_free(&child_ctx);
                test_ctx.child = रिक्त;
            }
        }
        av_opt_free(&test_ctx);
    }

    म_लिखो("\nTesting av_set_options_string()\n");
    {
        TestContext test_ctx = { 0 };
        स्थिर स्थिरांक अक्षर * स्थिरांक options[] = {
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
        av_opt_set_defaults(&test_ctx);

        av_log_set_level(AV_LOG_QUIET);

        साठी (i=0; i < FF_ARRAY_ELEMS(options); i++) {
            पूर्णांक silence_log = !म_भेद(options[i], "rational=-1/0"); // inf formatting differs between platforms
            av_log(&test_ctx, AV_LOG_DEBUG, "Setting options string '%s'\n", options[i]);
            जर (silence_log)
                av_log_set_callback(रिक्त);
            जर (av_set_options_string(&test_ctx, options[i], "=", ":") < 0)
                म_लिखो("Error '%s'\n", options[i]);
            अन्यथा
                म_लिखो("OK    '%s'\n", options[i]);
            av_log_set_callback(log_callback_help);
        }
        av_opt_free(&test_ctx);
    }

    म_लिखो("\nTesting av_opt_set_from_string()\n");
    {
        TestContext test_ctx = { 0 };
        स्थिर स्थिरांक अक्षर * स्थिरांक options[] = {
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
        स्थिर स्थिरांक अक्षर * स्थिरांक shorthand[] = { "num", "string", रिक्त };

        test_ctx.class = &test_class;
        av_opt_set_defaults(&test_ctx);

        av_log_set_level(AV_LOG_QUIET);

        साठी (i=0; i < FF_ARRAY_ELEMS(options); i++) {
            av_log(&test_ctx, AV_LOG_DEBUG, "Setting options string '%s'\n", options[i]);
            जर (av_opt_set_from_string(&test_ctx, options[i], shorthand, "=", ":") < 0)
                म_लिखो("Error '%s'\n", options[i]);
            अन्यथा
                म_लिखो("OK    '%s'\n", options[i]);
        }
        av_opt_free(&test_ctx);
    }

    म_लिखो("\nTesting av_opt_find2()\n");
    {
        TestContext test_ctx = { 0 };
        ChildContext child_ctx = { 0 };
        शून्य *target;
        स्थिरांक AVOption *opt;

        test_ctx.class = &test_class;
        child_ctx.class = &child_class;
        test_ctx.child = &child_ctx;

        av_log_set_level(AV_LOG_QUIET);

        // Should succeed. num exists and has opt_flags 1
        opt = av_opt_find2(&test_ctx, "num", रिक्त, 1, 0, &target);
        जर (opt && target == &test_ctx)
            म_लिखो("OK    '%s'\n", opt->name);
        अन्यथा
            म_लिखो("Error 'num'\n");

        // Should fail. num64 exists but has opt_flags 1, not 2
        opt = av_opt_find(&test_ctx, "num64", रिक्त, 2, 0);
        जर (opt)
            म_लिखो("OK    '%s'\n", opt->name);
        अन्यथा
            म_लिखो("Error 'num64'\n");

        // Should fail. child_num exists but in a child object we're not searching
        opt = av_opt_find(&test_ctx, "child_num", रिक्त, 0, 0);
        जर (opt)
            म_लिखो("OK    '%s'\n", opt->name);
        अन्यथा
            म_लिखो("Error 'child_num'\n");

        // Should succeed. child_num exists in a child object we're searching
        opt = av_opt_find2(&test_ctx, "child_num", रिक्त, 0, AV_OPT_शोध_CHILDREN, &target);
        जर (opt && target == &child_ctx)
            म_लिखो("OK    '%s'\n", opt->name);
        अन्यथा
            म_लिखो("Error 'child_num'\n");

        // Should fail. foo doesn't exist
        opt = av_opt_find(&test_ctx, "foo", रिक्त, 0, 0);
        जर (opt)
            म_लिखो("OK    '%s'\n", opt->name);
        अन्यथा
            म_लिखो("Error 'foo'\n");
    }

    म_लिखो("\nTesting av_opt_copy() into a memdup'ed object\n");
    {
        TestContext test_ctx = { 0 };
        TestContext *copy;
        uint8_t *layout_name = रिक्त;

        test_ctx.class = &test_class;
        av_opt_set_defaults(&test_ctx);
        av_opt_set(&test_ctx, "cl", "FL@Left+FR@Right", 0);

        copy = av_memdup(&test_ctx, आकार(test_ctx));
        जर (!copy)
            परत 1;
        av_opt_copy(copy, &test_ctx);
        av_opt_free(&test_ctx);

        av_opt_get(copy, "cl", 0, &layout_name);
        म_लिखो("cl=%s\n", layout_name);
        av_free(layout_name);
        av_opt_free(copy);
        av_free(copy);
    }

    म_लिखो("\nTesting av_opt_copy() of a native layout into a custom layout\n");
    {
        TestContext src = { 0 }, dst = { 0 };
        AVChannelLayout native = { AV_CHANNEL_ORDER_NATIVE };

        src.class = dst.class = &test_class;
        av_opt_set_defaults(&src);
        av_opt_set_defaults(&dst);
        av_opt_set(&dst, "cl", "FL@Left+FR@Right", 0);

        native.u.mask      = (uintptr_t)dst.channel_layout.u.map;
        native.nb_channels = av_popcount64(native.u.mask);
        av_opt_set_chlayout(&src, "cl", &native, 0);

        म_लिखो("copy: %d\n", av_opt_copy(&dst, &src));
        म_लिखो("same layout: %d\n", !av_channel_layout_compare(&src.channel_layout, &dst.channel_layout));
        av_opt_free(&src);
        av_opt_free(&dst);
    }

    परत 0;
}
