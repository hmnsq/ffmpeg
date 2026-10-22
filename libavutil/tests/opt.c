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

#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <stdio.h>

#அந்தர்பாவ "libavutil/common.h"
#அந்தர்பாவ "libavutil/channel_layout.h"
#அந்தர்பாவ "libavutil/error.h"
#அந்தர்பாவ "libavutil/log.h"
#அந்தர்பாவ "libavutil/mem.h"
#அந்தர்பாவ "libavutil/rational.h"
#அந்தர்பாவ "libavutil/opt.h"
#அந்தர்பாவ "libavutil/pixdesc.h"

வகைவரை கட்டமைப்பு TestContext {
    மாறிலி AVClass *class;
    கட்டமைப்பு ChildContext *child;
    முழு இலக்கம்;
    முழு unum;
    முழு toggle;
    எழுத்து *string;
    முழு flags;
    AVRational rational;
    AVRational video_rate;
    முழு w, h;
    எண்ணிக்கை AVPixelFormat pix_fmt;
    எண்ணிக்கை AVSampleFormat sample_fmt;
    int64_t duration;
    uint8_t color[4];
    AVChannelLayout channel_layout;
    வெறுமை *இருமம்;
    முழு இருமம்_size;
    வெறுமை *binary1;
    முழு இருமம்_size1;
    வெறுமை *binary2;
    முழு இருமம்_size2;
    int64_t num64;
    தசம flt;
    இரட்டை dbl;
    எழுத்து *escape;
    முழு bool1;
    முழு bool2;
    முழு bool3;
    AVDictionary *dict1;
    AVDictionary *dict2;

    முழு           **array_int;
    unsigned     nb_array_int;

    எழுத்து          **array_str;
    unsigned     nb_array_str;

    AVDictionary  **array_dict;
    unsigned     nb_array_dict;
} TestContext;

#define OFFSET(x) offsetof(TestContext, x)

#define TEST_FLAG_COOL 01
#define TEST_FLAG_LAME 02
#define TEST_FLAG_MU   04

நிலையான மாறிலி AVOptionArrayDef array_str = {
    .sep         = '|',
    .def         = "str0|str\\|1|str\\\\2",
};

நிலையான மாறிலி AVOptionArrayDef array_dict = {
    // there are three levels of escaping - C string, array option, dict - so 8 backslashes are needed to get a literal one inside a dict key/val
    .def         = "k00=v\\\\\\\\00:k01=v\\,01,k10=v\\\\=1\\\\:0",
};

நிலையான மாறிலி AVOption test_options[]= {
    {"num",        "set num",            OFFSET(இலக்கம்),            AV_OPT_TYPE_INT,            { .i64 = 0 },                     -1,       100, 1 },
    {"unum",       "set unum",           OFFSET(unum),           AV_OPT_TYPE_UINT,           { .i64 = 1U << 31 },               0,  1U << 31, 1 },
    {"toggle",     "set toggle",         OFFSET(toggle),         AV_OPT_TYPE_INT,            { .i64 = 1 },                      0,         1, 1 },
    {"rational",   "set rational",       OFFSET(rational),       AV_OPT_TYPE_RATIONAL,       { .dbl = 1 },                      0,        10, 1 },
    {"string",     "set string",         OFFSET(string),         AV_OPT_TYPE_STRING,         { .str = "default" },       CHAR_MIN,  CHAR_MAX, 1 },
    {"escape",     "set escape str",     OFFSET(escape),         AV_OPT_TYPE_STRING,         { .str = "\\=," },          CHAR_MIN,  CHAR_MAX, 1 },
    {"flags",      "set flags",          OFFSET(flags),          AV_OPT_TYPE_FLAGS,          { .i64 = 1 },                      0,   INT_MAX, 1, .unit = "flags" },
    {"cool",       "set cool flag",      0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_COOL },   INT_MIN,   INT_MAX, 1, .unit = "flags" },
    {"lame",       "set lame flag",      0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_LAME },   INT_MIN,   INT_MAX, 1, .unit = "flags" },
    {"mu",         "set mu flag",        0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_MU },     INT_MIN,   INT_MAX, 1, .unit = "flags" },
    {"size",       "set size",           OFFSET(w),              AV_OPT_TYPE_IMAGE_SIZE,     { .str="200x300" },                0,         0, 1 },
    {"pix_fmt",    "set pixfmt",         OFFSET(pix_fmt),        AV_OPT_TYPE_PIXEL_FMT,      { .i64 = AV_PIX_FMT_0BGR },       -1,   INT_MAX, 1 },
    {"sample_fmt", "set samplefmt",      OFFSET(sample_fmt),     AV_OPT_TYPE_SAMPLE_FMT,     { .i64 = AV_SAMPLE_FMT_S16 },     -1,   INT_MAX, 1 },
    {"video_rate", "set videorate",      OFFSET(video_rate),     AV_OPT_TYPE_VIDEO_RATE,     { .str = "25" },                   0,         INT_MAX, 1 },
    {"duration",   "set duration",       OFFSET(duration),       AV_OPT_TYPE_DURATION,       { .i64 = 1000 },                   0, INT64_MAX, 1 },
    {"color",      "set color",          OFFSET(color),          AV_OPT_TYPE_COLOR,          { .str = "pink" },                 0,         0, 1 },
    {"cl",         "set channel layout", OFFSET(channel_layout), AV_OPT_TYPE_CHLAYOUT,       { .str = "hexagonal" },            0,         0, 1 },
    {"bin",        "set binary value",   OFFSET(இருமம்),         AV_OPT_TYPE_இருமம்,         { .str="62696e00" },               0,         0, 1 },
    {"bin1",       "set binary value",   OFFSET(binary1),        AV_OPT_TYPE_இருமம்,         { .str=வெற்று },                     0,         0, 1 },
    {"bin2",       "set binary value",   OFFSET(binary2),        AV_OPT_TYPE_இருமம்,         { .str="" },                       0,         0, 1 },
    {"num64",      "set num 64bit",      OFFSET(num64),          AV_OPT_TYPE_INT64,          { .i64 = 1LL << 32 },             -1, 1LL << 32, 1 },
    {"flt",        "set float",          OFFSET(flt),            AV_OPT_TYPE_FLOAT,          { .dbl = 1.0 / 3 },                0,       100, 1 },
    {"dbl",        "set double",         OFFSET(dbl),            AV_OPT_TYPE_DOUBLE,         { .dbl = 1.0 / 3 },                0,       100, 1 },
    {"bool1",      "set boolean value",  OFFSET(bool1),          AV_OPT_TYPE_BOOL,           { .i64 = -1 },                    -1,         1, 1 },
    {"bool2",      "set boolean value",  OFFSET(bool2),          AV_OPT_TYPE_BOOL,           { .i64 = 1 },                     -1,         1, 1 },
    {"bool3",      "set boolean value",  OFFSET(bool3),          AV_OPT_TYPE_BOOL,           { .i64 = 0 },                      0,         1, 1 },
    {"dict1",      "set dictionary value", OFFSET(dict1),        AV_OPT_TYPE_DICT,           { .str = வெற்று},                    0,         0, 1 },
    {"dict2",      "set dictionary value", OFFSET(dict2),        AV_OPT_TYPE_DICT,           { .str = "happy=':-)'"},           0,         0, 1 },
    {"array_int",  "array of ints",        OFFSET(array_int),    AV_OPT_TYPE_INT | AV_OPT_TYPE_FLAG_ARRAY, .max = INT_MAX,           .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    {"array_str",  "array of strings",     OFFSET(array_str),    AV_OPT_TYPE_STRING | AV_OPT_TYPE_FLAG_ARRAY, { .arr = &array_str }, .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    {"array_dict", "array of dicts",       OFFSET(array_dict),   AV_OPT_TYPE_DICT | AV_OPT_TYPE_FLAG_ARRAY, { .arr = &array_dict },  .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    { வெற்று },
};

நிலையான மாறிலி எழுத்து *test_get_name(வெறுமை *ctx)
{
    திரும்பு "test";
}

வகைவரை கட்டமைப்பு ChildContext {
    மாறிலி AVClass *class;
    int64_t child_num64;
    முழு child_இலக்கம்;
    unsigned முழு child_unum;
} ChildContext;

#undef OFFSET
#define OFFSET(x) offsetof(ChildContext, x)

நிலையான மாறிலி AVOption child_options[]= {
    {"child_num64", "set num 64bit", OFFSET(child_num64), AV_OPT_TYPE_INT64, { .i64 = 0 }, 0, 100, 1 | AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY },
    {"child_num",   "set child_num", OFFSET(child_இலக்கம்),   AV_OPT_TYPE_INT,   { .i64 = 1 }, 0, 100, 1 },
    {"child_unum",  "set child_unum", OFFSET(child_unum),  AV_OPT_TYPE_UINT,  { .i64 = 0 }, 0, 100, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY },
    { வெற்று },
};

நிலையான மாறிலி எழுத்து *child_get_name(வெறுமை *ctx)
{
    திரும்பு "child";
}

நிலையான மாறிலி AVClass child_class = {
    .class_name = "ChildContext",
    .item_name  = child_get_name,
    .option     = child_options,
    .version    = LIBAVUTIL_VERSION_INT,
};

நிலையான வெறுமை *test_child_next(வெறுமை *obj, வெறுமை *prev)
{
    TestContext *test_ctx = obj;
    எனில் (!prev)
        திரும்பு test_ctx->child;
    திரும்பு வெற்று;
}

நிலையான மாறிலி AVClass test_class = {
    .class_name = "TestContext",
    .item_name  = test_get_name,
    .option     = test_options,
    .child_next = test_child_next,
    .version    = LIBAVUTIL_VERSION_INT,
};

நிலையான வெறுமை log_callback_help(வெறுமை *ptr, முழு level, மாறிலி எழுத்து *fmt, va_list vl)
{
    vfprintf(stdout, fmt, vl);
}

முழு முதன்மை(வெறுமை)
{
    முழு i;

    av_log_set_level(AV_LOG_DEBUG);
    av_log_set_callback(log_callback_help);

    printf("Testing default values\n");
    {
        TestContext test_ctx = { 0 };
        test_ctx.class = &test_class;
        av_opt_set_defaults(&test_ctx);

        printf("num=%d\n", test_ctx.இலக்கம்);
        printf("unum=%u\n", test_ctx.unum);
        printf("toggle=%d\n", test_ctx.toggle);
        printf("string=%s\n", test_ctx.string);
        printf("escape=%s\n", test_ctx.escape);
        printf("flags=%d\n", test_ctx.flags);
        printf("rational=%d/%d\n", test_ctx.rational.இலக்கம், test_ctx.rational.den);
        printf("video_rate=%d/%d\n", test_ctx.video_rate.இலக்கம், test_ctx.video_rate.den);
        printf("width=%d height=%d\n", test_ctx.w, test_ctx.h);
        printf("pix_fmt=%s\n", av_get_pix_fmt_name(test_ctx.pix_fmt));
        printf("sample_fmt=%s\n", av_get_sample_fmt_name(test_ctx.sample_fmt));
        printf("duration=%"PRId64"\n", test_ctx.duration);
        printf("color=%d %d %d %d\n", test_ctx.color[0], test_ctx.color[1], test_ctx.color[2], test_ctx.color[3]);
        printf("channel_layout=%"PRId64"=%"PRId64"\n", test_ctx.channel_layout.u.mask, (int64_t)AV_CH_LAYOUT_HEXAGONAL);
        எனில் (test_ctx.இருமம்)
            printf("binary=%x %x %x %x\n", ((uint8_t*)test_ctx.இருமம்)[0], ((uint8_t*)test_ctx.இருமம்)[1], ((uint8_t*)test_ctx.இருமம்)[2], ((uint8_t*)test_ctx.இருமம்)[3]);
        printf("binary_size=%d\n", test_ctx.இருமம்_size);
        printf("num64=%"PRId64"\n", test_ctx.num64);
        printf("flt=%.6f\n", test_ctx.flt);
        printf("dbl=%.6f\n", test_ctx.dbl);

        க்கு (unsigned i = 0; i < test_ctx.nb_array_str; i++)
            printf("array_str[%u]=%s\n", i, test_ctx.array_str[i]);

        க்கு (unsigned i = 0; i < test_ctx.nb_array_dict; i++) {
            AVDictionary            *d = test_ctx.array_dict[i];
            மாறிலி AVDictionaryEntry *e = வெற்று;

            போது ((e = av_dict_iterate(d, e)))
                printf("array_dict[%u]: %s\t%s\n", i, e->சாவி, e->மதிப்பு);
        }

        av_opt_show2(&test_ctx, வெற்று, -1, 0);

        av_opt_free(&test_ctx);
    }

    printf("\nTesting av_opt_is_set_to_default()\n");
    {
        முழு ret;
        TestContext test_ctx = { 0 };
        மாறிலி AVOption *o = வெற்று;
        test_ctx.class = &test_class;

        av_log_set_level(AV_LOG_QUIET);

        போது (o = av_opt_next(&test_ctx, o)) {
            ret = av_opt_is_set_to_default_by_name(&test_ctx, o->name, 0);
            printf("name:%10s default:%d error:%s\n", o->name, !!ret, ret < 0 ? av_err2str(ret) : "");
        }
        av_opt_set_defaults(&test_ctx);
        போது (o = av_opt_next(&test_ctx, o)) {
            ret = av_opt_is_set_to_default_by_name(&test_ctx, o->name, 0);
            printf("name:%10s default:%d error:%s\n", o->name, !!ret, ret < 0 ? av_err2str(ret) : "");
        }
        av_opt_free(&test_ctx);
    }

    printf("\nTesting av_opt_get/av_opt_set()\n");
    {
        TestContext test_ctx = { 0 };
        TestContext test2_ctx = { 0 };
        மாறிலி AVOption *o = வெற்று;
        எழுத்து *val = வெற்று;
        முழு ret;

        test_ctx.class = &test_class;
        test2_ctx.class = &test_class;

        av_log_set_level(AV_LOG_QUIET);

        av_opt_set_defaults(&test_ctx);

        போது (o = av_opt_next(&test_ctx, o)) {
            எழுத்து *value1 = வெற்று;
            எழுத்து *value2 = வெற்று;
            முழு ret1 = AVERROR_BUG;
            முழு ret2 = AVERROR_BUG;
            முழு ret3 = AVERROR_BUG;

            எனில் (o->type == AV_OPT_TYPE_CONST)
                தொடர்;

            ret1 = av_opt_get(&test_ctx, o->name, 0, (uint8_t **)&value1);
            எனில் (ret1 >= 0) {
                ret2 = av_opt_set(&test2_ctx, o->name, value1, 0);
                எனில் (ret2 >= 0)
                    ret3 = av_opt_get(&test2_ctx, o->name, 0, (uint8_t **)&value2);
            }

            printf("name: %-11s get: %-16s set: %-16s get: %-16s %s\n", o->name,
                    ret1 >= 0 ? value1 : av_err2str(ret1),
                    ret2 >= 0 ? "OK" : av_err2str(ret2),
                    ret3 >= 0 ? value2 : av_err2str(ret3),
                    ret1 >= 0 && ret2 >= 0 && ret3 >= 0 && !strcmp(value1, value2) ? "OK" : "Mismatch");
            av_free(value1);
            av_free(value2);
        }

        // av_opt_set(NULL) with an array option resets it
        ret = av_opt_set(&test_ctx, "array_dict", வெற்று, 0);
        printf("av_opt_set(\"array_dict\", NULL) -> %d\n", ret);
        printf("array_dict=%sNULL; nb_array_dict=%u\n",
               test_ctx.array_dict ? "non-" : "", test_ctx.nb_array_dict);

        // av_opt_get() on an empty array should return a NULL string
        ret = av_opt_get(&test_ctx, "array_dict", AV_OPT_ALLOW_NULL, (uint8_t**)&val);
        printf("av_opt_get(\"array_dict\") -> %s\n", val ? val : "NULL");

        av_opt_free(&test_ctx);
        av_opt_free(&test2_ctx);
    }

    printf("\nTesting av_opt_get_array()\n");
    {
        நிலையான மாறிலி முழு int_array[] = { 5, 0, 42, 137, INT_MAX };

        TestContext test_ctx = { 0 };

        முழு     out_int   [FF_ARRAY_ELEMS(int_array)] = { 0 };
        இரட்டை  out_double[FF_ARRAY_ELEMS(int_array)] = { 0. };
        எழுத்து   *out_str   [FF_ARRAY_ELEMS(int_array)] = { வெற்று };
        AVDictionary *out_dict[2] = { வெற்று };

        முழு ret;

        test_ctx.class = &test_class;

        av_log_set_level(AV_LOG_QUIET);

        av_opt_set_defaults(&test_ctx);

        test_ctx.array_int    = av_memdup(int_array, அளவு(int_array));
        test_ctx.nb_array_int = FF_ARRAY_ELEMS(int_array);

        // retrieve as int
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               1, 3, AV_OPT_TYPE_INT, out_int);
        printf("av_opt_get_array(\"array_int\", 1, 3, INT)=%d -> [ %d, %d, %d ]\n",
               ret, out_int[0], out_int[1], out_int[2]);

        // retrieve as double
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               3, 2, AV_OPT_TYPE_DOUBLE, out_double);
        printf("av_opt_get_array(\"array_int\", 3, 2, DOUBLE)=%d -> [ %.2f, %.2f ]\n",
               ret, out_double[0], out_double[1]);

        // retrieve as str
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               0, 5, AV_OPT_TYPE_STRING, out_str);
        printf("av_opt_get_array(\"array_int\", 0, 5, STRING)=%d -> "
               "[ %s, %s, %s, %s, %s ]\n", ret,
               out_str[0], out_str[1], out_str[2], out_str[3], out_str[4]);

        க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(out_str); i++)
            av_freep(&out_str[i]);

        ret = av_opt_get_array(&test_ctx, "array_dict", 0, 0, 2,
                               AV_OPT_TYPE_DICT, out_dict);
        printf("av_opt_get_array(\"array_dict\", 0, 2, DICT)=%d\n", ret);

        க்கு (முழு i = 0; i < test_ctx.nb_array_dict; i++) {
            மாறிலி AVDictionaryEntry *e = வெற்று;
            போது ((e = av_dict_iterate(test_ctx.array_dict[i], e))) {
                மாறிலி AVDictionaryEntry *e1 = av_dict_get(out_dict[i], e->சாவி, வெற்று, 0);
                எனில் (!e1 || strcmp(e->மதிப்பு, e1->மதிப்பு)) {
                    printf("mismatching dict entry %s: %s/%s\n",
                           e->சாவி, e->மதிப்பு, e1 ? e1->மதிப்பு : "<missing>");
                }
            }
            av_dict_free(&out_dict[i]);
        }

        av_opt_free(&test_ctx);
    }

    printf("\nTest av_opt_serialize()\n");
    {
        TestContext test_ctx = { 0 };
        எழுத்து *buf;
        முழு ret;
        test_ctx.class = &test_class;

        av_log_set_level(AV_LOG_QUIET);

        av_opt_set_defaults(&test_ctx);
        எனில் (av_opt_serialize(&test_ctx, 0, 0, &buf, '=', ',') >= 0) {
            printf("%s\n", buf);
            av_opt_free(&test_ctx);
            memset(&test_ctx, 0, அளவு(test_ctx));
            test_ctx.class = &test_class;
            ret = av_set_options_string(&test_ctx, buf, "=", ",");
            av_free(buf);
            எனில் (ret < 0)
                printf("Error ret '%d'\n", ret);
            எனில் (av_opt_serialize(&test_ctx, 0, 0, &buf, '=', ',') >= 0) {
                ChildContext child_ctx = { .child_num64 = 1, .child_unum = 1 };
                printf("%s\n", buf);
                av_free(buf);
                child_ctx.class = &child_class;
                test_ctx.child = &child_ctx;
                printf("Exclude flag EXPORT:\n");
                எனில் (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_தேடல்_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    printf("%s\n", buf);
                    av_free(buf);
                }
                printf("Include flag EXPORT:\n");
                எனில் (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_தேடல்_CHILDREN,
                                     &buf, '=', ',') >= 0) {
                    printf("%s\n", buf);
                    av_free(buf);
                }
                printf("Exclude flag 1:\n");
                எனில் (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_தேடல்_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    printf("%s\n", buf);
                    av_free(buf);
                }
                printf("Include flag 1:\n");
                எனில் (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_தேடல்_CHILDREN,
                                     &buf, '=', ',') >= 0) {
                    printf("%s\n", buf);
                    av_free(buf);
                }
                printf("Exclude exact match flag 1:\n");
                எனில் (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_தேடல்_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT|AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    printf("%s\n", buf);
                    av_free(buf);
                }
                printf("Include exact match flag 1:\n");
                எனில் (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_தேடல்_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT,
                                     &buf, '=', ',') >= 0) {
                    printf("%s\n", buf);
                    av_free(buf);
                }
                printf("Exclude exact match flag EXPORT|READONLY:\n");
                எனில் (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_தேடல்_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT|AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    printf("%s\n", buf);
                    av_free(buf);
                }
                printf("Include exact match flag EXPORT|READONLY:\n");
                எனில் (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_தேடல்_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT,
                                     &buf, '=', ',') >= 0) {
                    printf("%s\n", buf);
                    av_free(buf);
                }
                av_opt_free(&child_ctx);
                test_ctx.child = வெற்று;
            }
        }
        av_opt_free(&test_ctx);
    }

    printf("\nTesting av_set_options_string()\n");
    {
        TestContext test_ctx = { 0 };
        நிலையான மாறிலி எழுத்து * மாறிலி options[] = {
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

        க்கு (i=0; i < FF_ARRAY_ELEMS(options); i++) {
            முழு silence_log = !strcmp(options[i], "rational=-1/0"); // inf formatting differs between platforms
            av_log(&test_ctx, AV_LOG_DEBUG, "Setting options string '%s'\n", options[i]);
            எனில் (silence_log)
                av_log_set_callback(வெற்று);
            எனில் (av_set_options_string(&test_ctx, options[i], "=", ":") < 0)
                printf("Error '%s'\n", options[i]);
            இல்லையெனில்
                printf("OK    '%s'\n", options[i]);
            av_log_set_callback(log_callback_help);
        }
        av_opt_free(&test_ctx);
    }

    printf("\nTesting av_opt_set_from_string()\n");
    {
        TestContext test_ctx = { 0 };
        நிலையான மாறிலி எழுத்து * மாறிலி options[] = {
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
        நிலையான மாறிலி எழுத்து * மாறிலி shorthand[] = { "num", "string", வெற்று };

        test_ctx.class = &test_class;
        av_opt_set_defaults(&test_ctx);

        av_log_set_level(AV_LOG_QUIET);

        க்கு (i=0; i < FF_ARRAY_ELEMS(options); i++) {
            av_log(&test_ctx, AV_LOG_DEBUG, "Setting options string '%s'\n", options[i]);
            எனில் (av_opt_set_from_string(&test_ctx, options[i], shorthand, "=", ":") < 0)
                printf("Error '%s'\n", options[i]);
            இல்லையெனில்
                printf("OK    '%s'\n", options[i]);
        }
        av_opt_free(&test_ctx);
    }

    printf("\nTesting av_opt_find2()\n");
    {
        TestContext test_ctx = { 0 };
        ChildContext child_ctx = { 0 };
        வெறுமை *target;
        மாறிலி AVOption *opt;

        test_ctx.class = &test_class;
        child_ctx.class = &child_class;
        test_ctx.child = &child_ctx;

        av_log_set_level(AV_LOG_QUIET);

        // Should succeed. num exists and has opt_flags 1
        opt = av_opt_find2(&test_ctx, "num", வெற்று, 1, 0, &target);
        எனில் (opt && target == &test_ctx)
            printf("OK    '%s'\n", opt->name);
        இல்லையெனில்
            printf("Error 'num'\n");

        // Should fail. num64 exists but has opt_flags 1, not 2
        opt = av_opt_find(&test_ctx, "num64", வெற்று, 2, 0);
        எனில் (opt)
            printf("OK    '%s'\n", opt->name);
        இல்லையெனில்
            printf("Error 'num64'\n");

        // Should fail. child_num exists but in a child object we're not searching
        opt = av_opt_find(&test_ctx, "child_num", வெற்று, 0, 0);
        எனில் (opt)
            printf("OK    '%s'\n", opt->name);
        இல்லையெனில்
            printf("Error 'child_num'\n");

        // Should succeed. child_num exists in a child object we're searching
        opt = av_opt_find2(&test_ctx, "child_num", வெற்று, 0, AV_OPT_தேடல்_CHILDREN, &target);
        எனில் (opt && target == &child_ctx)
            printf("OK    '%s'\n", opt->name);
        இல்லையெனில்
            printf("Error 'child_num'\n");

        // Should fail. foo doesn't exist
        opt = av_opt_find(&test_ctx, "foo", வெற்று, 0, 0);
        எனில் (opt)
            printf("OK    '%s'\n", opt->name);
        இல்லையெனில்
            printf("Error 'foo'\n");
    }

    printf("\nTesting av_opt_copy() into a memdup'ed object\n");
    {
        TestContext test_ctx = { 0 };
        TestContext *copy;
        uint8_t *layout_name = வெற்று;

        test_ctx.class = &test_class;
        av_opt_set_defaults(&test_ctx);
        av_opt_set(&test_ctx, "cl", "FL@Left+FR@Right", 0);

        copy = av_memdup(&test_ctx, அளவு(test_ctx));
        எனில் (!copy)
            திரும்பு 1;
        av_opt_copy(copy, &test_ctx);
        av_opt_free(&test_ctx);

        av_opt_get(copy, "cl", 0, &layout_name);
        printf("cl=%s\n", layout_name);
        av_free(layout_name);
        av_opt_free(copy);
        av_free(copy);
    }

    printf("\nTesting av_opt_copy() of a native layout into a custom layout\n");
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

        printf("copy: %d\n", av_opt_copy(&dst, &src));
        printf("same layout: %d\n", !av_channel_layout_compare(&src.channel_layout, &dst.channel_layout));
        av_opt_free(&src);
        av_opt_free(&dst);
    }

    திரும்பு 0;
}
