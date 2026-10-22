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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/channel_layout.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/rational.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/opt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixdesc.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ TestContext {
    ਅਚਲ AVClass *class;
    ਬਣਤਰ ਬੱਚਾ_Context *ਬੱਚਾ;
    ਪੂਰਨ ਅੰਕ;
    ਪੂਰਨ unum;
    ਪੂਰਨ toggle;
    ਅੱਖਰ *string;
    ਪੂਰਨ flags;
    AVRational rational;
    AVRational video_ਦਰ;
    ਪੂਰਨ w, h;
    ਗਿਣਤੀ AVPixelFormat pix_fmt;
    ਗਿਣਤੀ AVSampleFormat sample_fmt;
    int64_t duration;
    uint8_t color[4];
    AVChannelLayout channel_layout;
    ਖਾਲੀ *ਦੁਆਧਾਰੀ;
    ਪੂਰਨ ਦੁਆਧਾਰੀ_ਮਾਪ;
    ਖਾਲੀ *binary1;
    ਪੂਰਨ ਦੁਆਧਾਰੀ_size1;
    ਖਾਲੀ *binary2;
    ਪੂਰਨ ਦੁਆਧਾਰੀ_size2;
    int64_t num64;
    ਦਸ਼ਮਲਵ flt;
    ਦੁੱਗਣਾ dbl;
    ਅੱਖਰ *escape;
    ਪੂਰਨ bool1;
    ਪੂਰਨ bool2;
    ਪੂਰਨ bool3;
    AVDictionary *dict1;
    AVDictionary *dict2;

    ਪੂਰਨ           **array_int;
    ਬਿਨਾਨਿਸ਼ਾਨੀ     nb_array_int;

    ਅੱਖਰ          **array_str;
    ਬਿਨਾਨਿਸ਼ਾਨੀ     nb_array_str;

    AVDictionary  **array_dict;
    ਬਿਨਾਨਿਸ਼ਾਨੀ     nb_array_dict;
} TestContext;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਥ_2(x) offsetof(TestContext, x)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_FLAG_COOL 01
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_FLAG_LAME 02
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_FLAG_MU   04

ਸਥਿਰ ਅਚਲ AVOptionArrayDef array_str = {
    .sep         = '|',
    .def         = "str0|str\\|1|str\\\\2",
};

ਸਥਿਰ ਅਚਲ AVOptionArrayDef array_dict = {
    // there are three levels of escaping - C string, array option, dict - so 8 backslashes are needed to get a literal one inside a dict key/val
    .def         = "k00=v\\\\\\\\00:k01=v\\,01,k10=v\\\\=1\\\\:0",
};

ਸਥਿਰ ਅਚਲ AVOption test_options[]= {
    {"num",        "set num",            ਵਿੱਥ_2(ਅੰਕ),            AV_OPT_TYPE_INT,            { .i64 = 0 },                     -1,       100, 1 },
    {"unum",       "set unum",           ਵਿੱਥ_2(unum),           AV_OPT_TYPE_UINT,           { .i64 = 1U << 31 },               0,  1U << 31, 1 },
    {"toggle",     "set toggle",         ਵਿੱਥ_2(toggle),         AV_OPT_TYPE_INT,            { .i64 = 1 },                      0,         1, 1 },
    {"rational",   "set rational",       ਵਿੱਥ_2(rational),       AV_OPT_TYPE_RATIONAL,       { .dbl = 1 },                      0,        10, 1 },
    {"string",     "set string",         ਵਿੱਥ_2(string),         AV_OPT_TYPE_STRING,         { .str = "default" },       CHAR_MIN,  CHAR_MAX, 1 },
    {"escape",     "set escape str",     ਵਿੱਥ_2(escape),         AV_OPT_TYPE_STRING,         { .str = "\\=," },          CHAR_MIN,  CHAR_MAX, 1 },
    {"flags",      "set flags",          ਵਿੱਥ_2(flags),          AV_OPT_TYPE_FLAGS,          { .i64 = 1 },                      0,   ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1, .unit = "flags" },
    {"cool",       "set cool flag",      0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_COOL },   INT_MIN,   ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1, .unit = "flags" },
    {"lame",       "set lame flag",      0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_LAME },   INT_MIN,   ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1, .unit = "flags" },
    {"mu",         "set mu flag",        0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_MU },     INT_MIN,   ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1, .unit = "flags" },
    {"size",       "set size",           ਵਿੱਥ_2(w),              AV_OPT_TYPE_IMAGE_ਮਾਪ,     { .str="200x300" },                0,         0, 1 },
    {"pix_fmt",    "set pixfmt",         ਵਿੱਥ_2(pix_fmt),        AV_OPT_TYPE_PIXEL_FMT,      { .i64 = AV_PIX_FMT_0BGR },       -1,   ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1 },
    {"sample_fmt", "set samplefmt",      ਵਿੱਥ_2(sample_fmt),     AV_OPT_TYPE_SAMPLE_FMT,     { .i64 = AV_SAMPLE_FMT_S16 },     -1,   ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1 },
    {"video_rate", "set videorate",      ਵਿੱਥ_2(video_ਦਰ),     AV_OPT_TYPE_VIDEO_ਦਰ,     { .str = "25" },                   0,         ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1 },
    {"duration",   "set duration",       ਵਿੱਥ_2(duration),       AV_OPT_TYPE_DURATION,       { .i64 = 1000 },                   0, INT64_MAX, 1 },
    {"color",      "set color",          ਵਿੱਥ_2(color),          AV_OPT_TYPE_COLOR,          { .str = "pink" },                 0,         0, 1 },
    {"cl",         "set channel layout", ਵਿੱਥ_2(channel_layout), AV_OPT_TYPE_CHLAYOUT,       { .str = "hexagonal" },            0,         0, 1 },
    {"bin",        "set binary value",   ਵਿੱਥ_2(ਦੁਆਧਾਰੀ),         AV_OPT_TYPE_ਦੁਆਧਾਰੀ,         { .str="62696e00" },               0,         0, 1 },
    {"bin1",       "set binary value",   ਵਿੱਥ_2(binary1),        AV_OPT_TYPE_ਦੁਆਧਾਰੀ,         { .str=ਨਿਰਾ },                     0,         0, 1 },
    {"bin2",       "set binary value",   ਵਿੱਥ_2(binary2),        AV_OPT_TYPE_ਦੁਆਧਾਰੀ,         { .str="" },                       0,         0, 1 },
    {"num64",      "set num 64bit",      ਵਿੱਥ_2(num64),          AV_OPT_TYPE_INT64,          { .i64 = 1LL << 32 },             -1, 1LL << 32, 1 },
    {"flt",        "set float",          ਵਿੱਥ_2(flt),            AV_OPT_TYPE_FLOAT,          { .dbl = 1.0 / 3 },                0,       100, 1 },
    {"dbl",        "set double",         ਵਿੱਥ_2(dbl),            AV_OPT_TYPE_DOUBLE,         { .dbl = 1.0 / 3 },                0,       100, 1 },
    {"bool1",      "set boolean value",  ਵਿੱਥ_2(bool1),          AV_OPT_TYPE_BOOL,           { .i64 = -1 },                    -1,         1, 1 },
    {"bool2",      "set boolean value",  ਵਿੱਥ_2(bool2),          AV_OPT_TYPE_BOOL,           { .i64 = 1 },                     -1,         1, 1 },
    {"bool3",      "set boolean value",  ਵਿੱਥ_2(bool3),          AV_OPT_TYPE_BOOL,           { .i64 = 0 },                      0,         1, 1 },
    {"dict1",      "set dictionary value", ਵਿੱਥ_2(dict1),        AV_OPT_TYPE_DICT,           { .str = ਨਿਰਾ},                    0,         0, 1 },
    {"dict2",      "set dictionary value", ਵਿੱਥ_2(dict2),        AV_OPT_TYPE_DICT,           { .str = "happy=':-)'"},           0,         0, 1 },
    {"array_int",  "array of ints",        ਵਿੱਥ_2(array_int),    AV_OPT_TYPE_INT | AV_OPT_TYPE_FLAG_ARRAY, .max = ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ,           .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    {"array_str",  "array of strings",     ਵਿੱਥ_2(array_str),    AV_OPT_TYPE_STRING | AV_OPT_TYPE_FLAG_ARRAY, { .arr = &array_str }, .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    {"array_dict", "array of dicts",       ਵਿੱਥ_2(array_dict),   AV_OPT_TYPE_DICT | AV_OPT_TYPE_FLAG_ARRAY, { .arr = &array_dict },  .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    { ਨਿਰਾ },
};

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *test_get_name(ਖਾਲੀ *ctx)
{
    ਵਾਪਸ "test";
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਬੱਚਾ_Context {
    ਅਚਲ AVClass *class;
    int64_t ਬੱਚਾ_num64;
    ਪੂਰਨ ਬੱਚਾ_ਅੰਕ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬੱਚਾ_unum;
} ਬੱਚਾ_Context;

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਵਿੱਥ_2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਥ_2(x) offsetof(ਬੱਚਾ_Context, x)

ਸਥਿਰ ਅਚਲ AVOption ਬੱਚਾ_options[]= {
    {"child_num64", "set num 64bit", ਵਿੱਥ_2(ਬੱਚਾ_num64), AV_OPT_TYPE_INT64, { .i64 = 0 }, 0, 100, 1 | AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY },
    {"child_num",   "set child_num", ਵਿੱਥ_2(ਬੱਚਾ_ਅੰਕ),   AV_OPT_TYPE_INT,   { .i64 = 1 }, 0, 100, 1 },
    {"child_unum",  "set child_unum", ਵਿੱਥ_2(ਬੱਚਾ_unum),  AV_OPT_TYPE_UINT,  { .i64 = 0 }, 0, 100, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY },
    { ਨਿਰਾ },
};

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਬੱਚਾ_get_name(ਖਾਲੀ *ctx)
{
    ਵਾਪਸ "child";
}

ਸਥਿਰ ਅਚਲ AVClass ਬੱਚਾ_class = {
    .class_name = "ChildContext",
    .ਵਸਤੂ_name  = ਬੱਚਾ_get_name,
    .option     = ਬੱਚਾ_options,
    .ਸੰਸਕਰਣ    = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
};

ਸਥਿਰ ਖਾਲੀ *test_ਬੱਚਾ_ਅਗਲਾ(ਖਾਲੀ *obj, ਖਾਲੀ *prev)
{
    TestContext *test_ctx = obj;
    ਜੇ (!prev)
        ਵਾਪਸ test_ctx->ਬੱਚਾ;
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਅਚਲ AVClass test_class = {
    .class_name = "TestContext",
    .ਵਸਤੂ_name  = test_get_name,
    .option     = test_options,
    .ਬੱਚਾ_ਅਗਲਾ = test_ਬੱਚਾ_ਅਗਲਾ,
    .ਸੰਸਕਰਣ    = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
};

ਸਥਿਰ ਖਾਲੀ log_callback_help(ਖਾਲੀ *ptr, ਪੂਰਨ level, ਅਚਲ ਅੱਖਰ *fmt, va_list vl)
{
    vfprintf(stdout, fmt, vl);
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਪੂਰਨ i;

    av_log_ਸੈੱਟ_level(AV_LOG_DEBUG);
    av_log_ਸੈੱਟ_callback(log_callback_help);

    ਲਿਖੋ("Testing default values\n");
    {
        TestContext test_ctx = { 0 };
        test_ctx.class = &test_class;
        av_opt_ਸੈੱਟ_defaults(&test_ctx);

        ਲਿਖੋ("num=%d\n", test_ctx.ਅੰਕ);
        ਲਿਖੋ("unum=%u\n", test_ctx.unum);
        ਲਿਖੋ("toggle=%d\n", test_ctx.toggle);
        ਲਿਖੋ("string=%s\n", test_ctx.string);
        ਲਿਖੋ("escape=%s\n", test_ctx.escape);
        ਲਿਖੋ("flags=%d\n", test_ctx.flags);
        ਲਿਖੋ("rational=%d/%d\n", test_ctx.rational.ਅੰਕ, test_ctx.rational.den);
        ਲਿਖੋ("video_rate=%d/%d\n", test_ctx.video_ਦਰ.ਅੰਕ, test_ctx.video_ਦਰ.den);
        ਲਿਖੋ("width=%d height=%d\n", test_ctx.w, test_ctx.h);
        ਲਿਖੋ("pix_fmt=%s\n", av_get_pix_fmt_name(test_ctx.pix_fmt));
        ਲਿਖੋ("sample_fmt=%s\n", av_get_sample_fmt_name(test_ctx.sample_fmt));
        ਲਿਖੋ("duration=%"PRId64"\n", test_ctx.duration);
        ਲਿਖੋ("color=%d %d %d %d\n", test_ctx.color[0], test_ctx.color[1], test_ctx.color[2], test_ctx.color[3]);
        ਲਿਖੋ("channel_layout=%"PRId64"=%"PRId64"\n", test_ctx.channel_layout.u.ਨਕਾਬ_2, (int64_t)AV_CH_LAYOUT_HEXAGONAL);
        ਜੇ (test_ctx.ਦੁਆਧਾਰੀ)
            ਲਿਖੋ("binary=%x %x %x %x\n", ((uint8_t*)test_ctx.ਦੁਆਧਾਰੀ)[0], ((uint8_t*)test_ctx.ਦੁਆਧਾਰੀ)[1], ((uint8_t*)test_ctx.ਦੁਆਧਾਰੀ)[2], ((uint8_t*)test_ctx.ਦੁਆਧਾਰੀ)[3]);
        ਲਿਖੋ("binary_size=%d\n", test_ctx.ਦੁਆਧਾਰੀ_ਮਾਪ);
        ਲਿਖੋ("num64=%"PRId64"\n", test_ctx.num64);
        ਲਿਖੋ("flt=%.6f\n", test_ctx.flt);
        ਲਿਖੋ("dbl=%.6f\n", test_ctx.dbl);

        ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < test_ctx.nb_array_str; i++)
            ਲਿਖੋ("array_str[%u]=%s\n", i, test_ctx.array_str[i]);

        ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < test_ctx.nb_array_dict; i++) {
            AVDictionary            *d = test_ctx.array_dict[i];
            ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *e = ਨਿਰਾ;

            ਜਦੋਂ ((e = av_dict_iterate(d, e)))
                ਲਿਖੋ("array_dict[%u]: %s\t%s\n", i, e->ਕੁੰਜੀ, e->ਮੁੱਲ);
        }

        av_opt_show2(&test_ctx, ਨਿਰਾ, -1, 0);

        av_opt_free(&test_ctx);
    }

    ਲਿਖੋ("\nTesting av_opt_is_set_to_default()\n");
    {
        ਪੂਰਨ ret;
        TestContext test_ctx = { 0 };
        ਅਚਲ AVOption *o = ਨਿਰਾ;
        test_ctx.class = &test_class;

        av_log_ਸੈੱਟ_level(AV_LOG_QUIET);

        ਜਦੋਂ (o = av_opt_ਅਗਲਾ(&test_ctx, o)) {
            ret = av_opt_is_ਸੈੱਟ_ਮੰਜ਼ਿਲ_default_by_name(&test_ctx, o->name, 0);
            ਲਿਖੋ("name:%10s default:%d error:%s\n", o->name, !!ret, ret < 0 ? av_err2str(ret) : "");
        }
        av_opt_ਸੈੱਟ_defaults(&test_ctx);
        ਜਦੋਂ (o = av_opt_ਅਗਲਾ(&test_ctx, o)) {
            ret = av_opt_is_ਸੈੱਟ_ਮੰਜ਼ਿਲ_default_by_name(&test_ctx, o->name, 0);
            ਲਿਖੋ("name:%10s default:%d error:%s\n", o->name, !!ret, ret < 0 ? av_err2str(ret) : "");
        }
        av_opt_free(&test_ctx);
    }

    ਲਿਖੋ("\nTesting av_opt_get/av_opt_set()\n");
    {
        TestContext test_ctx = { 0 };
        TestContext test2_ctx = { 0 };
        ਅਚਲ AVOption *o = ਨਿਰਾ;
        ਅੱਖਰ *val = ਨਿਰਾ;
        ਪੂਰਨ ret;

        test_ctx.class = &test_class;
        test2_ctx.class = &test_class;

        av_log_ਸੈੱਟ_level(AV_LOG_QUIET);

        av_opt_ਸੈੱਟ_defaults(&test_ctx);

        ਜਦੋਂ (o = av_opt_ਅਗਲਾ(&test_ctx, o)) {
            ਅੱਖਰ *value1 = ਨਿਰਾ;
            ਅੱਖਰ *value2 = ਨਿਰਾ;
            ਪੂਰਨ ret1 = AVERROR_BUG;
            ਪੂਰਨ ret2 = AVERROR_BUG;
            ਪੂਰਨ ret3 = AVERROR_BUG;

            ਜੇ (o->type == AV_OPT_TYPE_CONST)
                ਜਾਰੀ;

            ret1 = av_opt_get(&test_ctx, o->name, 0, (uint8_t **)&value1);
            ਜੇ (ret1 >= 0) {
                ret2 = av_opt_ਸੈੱਟ(&test2_ctx, o->name, value1, 0);
                ਜੇ (ret2 >= 0)
                    ret3 = av_opt_get(&test2_ctx, o->name, 0, (uint8_t **)&value2);
            }

            ਲਿਖੋ("name: %-11s get: %-16s set: %-16s get: %-16s %s\n", o->name,
                    ret1 >= 0 ? value1 : av_err2str(ret1),
                    ret2 >= 0 ? "OK" : av_err2str(ret2),
                    ret3 >= 0 ? value2 : av_err2str(ret3),
                    ret1 >= 0 && ret2 >= 0 && ret3 >= 0 && !strcmp(value1, value2) ? "OK" : "Mismatch");
            av_free(value1);
            av_free(value2);
        }

        // av_opt_set(NULL) with an array option resets it
        ret = av_opt_ਸੈੱਟ(&test_ctx, "array_dict", ਨਿਰਾ, 0);
        ਲਿਖੋ("av_opt_set(\"array_dict\", NULL) -> %d\n", ret);
        ਲਿਖੋ("array_dict=%sNULL; nb_array_dict=%u\n",
               test_ctx.array_dict ? "non-" : "", test_ctx.nb_array_dict);

        // av_opt_get() on an empty array should return a NULL string
        ret = av_opt_get(&test_ctx, "array_dict", AV_OPT_ALLOW_NULL, (uint8_t**)&val);
        ਲਿਖੋ("av_opt_get(\"array_dict\") -> %s\n", val ? val : "NULL");

        av_opt_free(&test_ctx);
        av_opt_free(&test2_ctx);
    }

    ਲਿਖੋ("\nTesting av_opt_get_array()\n");
    {
        ਸਥਿਰ ਅਚਲ ਪੂਰਨ int_array[] = { 5, 0, 42, 137, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ };

        TestContext test_ctx = { 0 };

        ਪੂਰਨ     ਬਾਹਰਲਾ_int   [FF_ARRAY_ELEMS(int_array)] = { 0 };
        ਦੁੱਗਣਾ  ਬਾਹਰਲਾ_double[FF_ARRAY_ELEMS(int_array)] = { 0. };
        ਅੱਖਰ   *ਬਾਹਰਲਾ_str   [FF_ARRAY_ELEMS(int_array)] = { ਨਿਰਾ };
        AVDictionary *ਬਾਹਰਲਾ_dict[2] = { ਨਿਰਾ };

        ਪੂਰਨ ret;

        test_ctx.class = &test_class;

        av_log_ਸੈੱਟ_level(AV_LOG_QUIET);

        av_opt_ਸੈੱਟ_defaults(&test_ctx);

        test_ctx.array_int    = av_memdup(int_array, ਆਕਾਰ(int_array));
        test_ctx.nb_array_int = FF_ARRAY_ELEMS(int_array);

        // retrieve as int
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               1, 3, AV_OPT_TYPE_INT, ਬਾਹਰਲਾ_int);
        ਲਿਖੋ("av_opt_get_array(\"array_int\", 1, 3, INT)=%d -> [ %d, %d, %d ]\n",
               ret, ਬਾਹਰਲਾ_int[0], ਬਾਹਰਲਾ_int[1], ਬਾਹਰਲਾ_int[2]);

        // retrieve as double
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               3, 2, AV_OPT_TYPE_DOUBLE, ਬਾਹਰਲਾ_double);
        ਲਿਖੋ("av_opt_get_array(\"array_int\", 3, 2, DOUBLE)=%d -> [ %.2f, %.2f ]\n",
               ret, ਬਾਹਰਲਾ_double[0], ਬਾਹਰਲਾ_double[1]);

        // retrieve as str
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               0, 5, AV_OPT_TYPE_STRING, ਬਾਹਰਲਾ_str);
        ਲਿਖੋ("av_opt_get_array(\"array_int\", 0, 5, STRING)=%d -> "
               "[ %s, %s, %s, %s, %s ]\n", ret,
               ਬਾਹਰਲਾ_str[0], ਬਾਹਰਲਾ_str[1], ਬਾਹਰਲਾ_str[2], ਬਾਹਰਲਾ_str[3], ਬਾਹਰਲਾ_str[4]);

        ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(ਬਾਹਰਲਾ_str); i++)
            av_freep(&ਬਾਹਰਲਾ_str[i]);

        ret = av_opt_get_array(&test_ctx, "array_dict", 0, 0, 2,
                               AV_OPT_TYPE_DICT, ਬਾਹਰਲਾ_dict);
        ਲਿਖੋ("av_opt_get_array(\"array_dict\", 0, 2, DICT)=%d\n", ret);

        ਲਈ (ਪੂਰਨ i = 0; i < test_ctx.nb_array_dict; i++) {
            ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *e = ਨਿਰਾ;
            ਜਦੋਂ ((e = av_dict_iterate(test_ctx.array_dict[i], e))) {
                ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *e1 = av_dict_get(ਬਾਹਰਲਾ_dict[i], e->ਕੁੰਜੀ, ਨਿਰਾ, 0);
                ਜੇ (!e1 || strcmp(e->ਮੁੱਲ, e1->ਮੁੱਲ)) {
                    ਲਿਖੋ("mismatching dict entry %s: %s/%s\n",
                           e->ਕੁੰਜੀ, e->ਮੁੱਲ, e1 ? e1->ਮੁੱਲ : "<missing>");
                }
            }
            av_dict_free(&ਬਾਹਰਲਾ_dict[i]);
        }

        av_opt_free(&test_ctx);
    }

    ਲਿਖੋ("\nTest av_opt_serialize()\n");
    {
        TestContext test_ctx = { 0 };
        ਅੱਖਰ *buf;
        ਪੂਰਨ ret;
        test_ctx.class = &test_class;

        av_log_ਸੈੱਟ_level(AV_LOG_QUIET);

        av_opt_ਸੈੱਟ_defaults(&test_ctx);
        ਜੇ (av_opt_serialize(&test_ctx, 0, 0, &buf, '=', ',') >= 0) {
            ਲਿਖੋ("%s\n", buf);
            av_opt_free(&test_ctx);
            memset(&test_ctx, 0, ਆਕਾਰ(test_ctx));
            test_ctx.class = &test_class;
            ret = av_ਸੈੱਟ_options_string(&test_ctx, buf, "=", ",");
            av_free(buf);
            ਜੇ (ret < 0)
                ਲਿਖੋ("Error ret '%d'\n", ret);
            ਜੇ (av_opt_serialize(&test_ctx, 0, 0, &buf, '=', ',') >= 0) {
                ਬੱਚਾ_Context ਬੱਚਾ_ctx = { .ਬੱਚਾ_num64 = 1, .ਬੱਚਾ_unum = 1 };
                ਲਿਖੋ("%s\n", buf);
                av_free(buf);
                ਬੱਚਾ_ctx.class = &ਬੱਚਾ_class;
                test_ctx.ਬੱਚਾ = &ਬੱਚਾ_ctx;
                ਲਿਖੋ("Exclude flag EXPORT:\n");
                ਜੇ (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ਖੋਜ_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    ਲਿਖੋ("%s\n", buf);
                    av_free(buf);
                }
                ਲਿਖੋ("Include flag EXPORT:\n");
                ਜੇ (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ਖੋਜ_CHILDREN,
                                     &buf, '=', ',') >= 0) {
                    ਲਿਖੋ("%s\n", buf);
                    av_free(buf);
                }
                ਲਿਖੋ("Exclude flag 1:\n");
                ਜੇ (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ਖੋਜ_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    ਲਿਖੋ("%s\n", buf);
                    av_free(buf);
                }
                ਲਿਖੋ("Include flag 1:\n");
                ਜੇ (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ਖੋਜ_CHILDREN,
                                     &buf, '=', ',') >= 0) {
                    ਲਿਖੋ("%s\n", buf);
                    av_free(buf);
                }
                ਲਿਖੋ("Exclude exact match flag 1:\n");
                ਜੇ (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ਖੋਜ_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT|AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    ਲਿਖੋ("%s\n", buf);
                    av_free(buf);
                }
                ਲਿਖੋ("Include exact match flag 1:\n");
                ਜੇ (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ਖੋਜ_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT,
                                     &buf, '=', ',') >= 0) {
                    ਲਿਖੋ("%s\n", buf);
                    av_free(buf);
                }
                ਲਿਖੋ("Exclude exact match flag EXPORT|READONLY:\n");
                ਜੇ (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ਖੋਜ_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT|AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    ਲਿਖੋ("%s\n", buf);
                    av_free(buf);
                }
                ਲਿਖੋ("Include exact match flag EXPORT|READONLY:\n");
                ਜੇ (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ਖੋਜ_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT,
                                     &buf, '=', ',') >= 0) {
                    ਲਿਖੋ("%s\n", buf);
                    av_free(buf);
                }
                av_opt_free(&ਬੱਚਾ_ctx);
                test_ctx.ਬੱਚਾ = ਨਿਰਾ;
            }
        }
        av_opt_free(&test_ctx);
    }

    ਲਿਖੋ("\nTesting av_set_options_string()\n");
    {
        TestContext test_ctx = { 0 };
        ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ options[] = {
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
        av_opt_ਸੈੱਟ_defaults(&test_ctx);

        av_log_ਸੈੱਟ_level(AV_LOG_QUIET);

        ਲਈ (i=0; i < FF_ARRAY_ELEMS(options); i++) {
            ਪੂਰਨ silence_log = !strcmp(options[i], "rational=-1/0"); // inf formatting differs between platforms
            av_log(&test_ctx, AV_LOG_DEBUG, "Setting options string '%s'\n", options[i]);
            ਜੇ (silence_log)
                av_log_ਸੈੱਟ_callback(ਨਿਰਾ);
            ਜੇ (av_ਸੈੱਟ_options_string(&test_ctx, options[i], "=", ":") < 0)
                ਲਿਖੋ("Error '%s'\n", options[i]);
            ਨਹੀਂਤਾਂ
                ਲਿਖੋ("OK    '%s'\n", options[i]);
            av_log_ਸੈੱਟ_callback(log_callback_help);
        }
        av_opt_free(&test_ctx);
    }

    ਲਿਖੋ("\nTesting av_opt_set_from_string()\n");
    {
        TestContext test_ctx = { 0 };
        ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ options[] = {
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
        ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ shorthand[] = { "num", "string", ਨਿਰਾ };

        test_ctx.class = &test_class;
        av_opt_ਸੈੱਟ_defaults(&test_ctx);

        av_log_ਸੈੱਟ_level(AV_LOG_QUIET);

        ਲਈ (i=0; i < FF_ARRAY_ELEMS(options); i++) {
            av_log(&test_ctx, AV_LOG_DEBUG, "Setting options string '%s'\n", options[i]);
            ਜੇ (av_opt_ਸੈੱਟ_from_string(&test_ctx, options[i], shorthand, "=", ":") < 0)
                ਲਿਖੋ("Error '%s'\n", options[i]);
            ਨਹੀਂਤਾਂ
                ਲਿਖੋ("OK    '%s'\n", options[i]);
        }
        av_opt_free(&test_ctx);
    }

    ਲਿਖੋ("\nTesting av_opt_find2()\n");
    {
        TestContext test_ctx = { 0 };
        ਬੱਚਾ_Context ਬੱਚਾ_ctx = { 0 };
        ਖਾਲੀ *ਨਿਸ਼ਾਨਾ;
        ਅਚਲ AVOption *opt;

        test_ctx.class = &test_class;
        ਬੱਚਾ_ctx.class = &ਬੱਚਾ_class;
        test_ctx.ਬੱਚਾ = &ਬੱਚਾ_ctx;

        av_log_ਸੈੱਟ_level(AV_LOG_QUIET);

        // Should succeed. num exists and has opt_flags 1
        opt = av_opt_find2(&test_ctx, "num", ਨਿਰਾ, 1, 0, &ਨਿਸ਼ਾਨਾ);
        ਜੇ (opt && ਨਿਸ਼ਾਨਾ == &test_ctx)
            ਲਿਖੋ("OK    '%s'\n", opt->name);
        ਨਹੀਂਤਾਂ
            ਲਿਖੋ("Error 'num'\n");

        // Should fail. num64 exists but has opt_flags 1, not 2
        opt = av_opt_ਲੱਭੋ(&test_ctx, "num64", ਨਿਰਾ, 2, 0);
        ਜੇ (opt)
            ਲਿਖੋ("OK    '%s'\n", opt->name);
        ਨਹੀਂਤਾਂ
            ਲਿਖੋ("Error 'num64'\n");

        // Should fail. child_num exists but in a child object we're not searching
        opt = av_opt_ਲੱਭੋ(&test_ctx, "child_num", ਨਿਰਾ, 0, 0);
        ਜੇ (opt)
            ਲਿਖੋ("OK    '%s'\n", opt->name);
        ਨਹੀਂਤਾਂ
            ਲਿਖੋ("Error 'child_num'\n");

        // Should succeed. child_num exists in a child object we're searching
        opt = av_opt_find2(&test_ctx, "child_num", ਨਿਰਾ, 0, AV_OPT_ਖੋਜ_CHILDREN, &ਨਿਸ਼ਾਨਾ);
        ਜੇ (opt && ਨਿਸ਼ਾਨਾ == &ਬੱਚਾ_ctx)
            ਲਿਖੋ("OK    '%s'\n", opt->name);
        ਨਹੀਂਤਾਂ
            ਲਿਖੋ("Error 'child_num'\n");

        // Should fail. foo doesn't exist
        opt = av_opt_ਲੱਭੋ(&test_ctx, "foo", ਨਿਰਾ, 0, 0);
        ਜੇ (opt)
            ਲਿਖੋ("OK    '%s'\n", opt->name);
        ਨਹੀਂਤਾਂ
            ਲਿਖੋ("Error 'foo'\n");
    }

    ਲਿਖੋ("\nTesting av_opt_copy() into a memdup'ed object\n");
    {
        TestContext test_ctx = { 0 };
        TestContext *copy;
        uint8_t *layout_name = ਨਿਰਾ;

        test_ctx.class = &test_class;
        av_opt_ਸੈੱਟ_defaults(&test_ctx);
        av_opt_ਸੈੱਟ(&test_ctx, "cl", "FL@Left+FR@Right", 0);

        copy = av_memdup(&test_ctx, ਆਕਾਰ(test_ctx));
        ਜੇ (!copy)
            ਵਾਪਸ 1;
        av_opt_copy(copy, &test_ctx);
        av_opt_free(&test_ctx);

        av_opt_get(copy, "cl", 0, &layout_name);
        ਲਿਖੋ("cl=%s\n", layout_name);
        av_free(layout_name);
        av_opt_free(copy);
        av_free(copy);
    }

    ਲਿਖੋ("\nTesting av_opt_copy() of a native layout into a custom layout\n");
    {
        TestContext src = { 0 }, dst = { 0 };
        AVChannelLayout native = { AV_CHANNEL_ਕ੍ਰਮ_NATIVE };

        src.class = dst.class = &test_class;
        av_opt_ਸੈੱਟ_defaults(&src);
        av_opt_ਸੈੱਟ_defaults(&dst);
        av_opt_ਸੈੱਟ(&dst, "cl", "FL@Left+FR@Right", 0);

        native.u.ਨਕਾਬ_2      = (uintptr_t)dst.channel_layout.u.map;
        native.nb_channels = av_popcount64(native.u.ਨਕਾਬ_2);
        av_opt_ਸੈੱਟ_chlayout(&src, "cl", &native, 0);

        ਲਿਖੋ("copy: %d\n", av_opt_copy(&dst, &src));
        ਲਿਖੋ("same layout: %d\n", !av_channel_layout_compare(&src.channel_layout, &dst.channel_layout));
        av_opt_free(&src);
        av_opt_free(&dst);
    }

    ਵਾਪਸ 0;
}
