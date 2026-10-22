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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/common.h"
#ಅನ್ತರ್ಭಾವ "libavutil/channel_layout.h"
#ಅನ್ತರ್ಭಾವ "libavutil/error.h"
#ಅನ್ತರ್ಭಾವ "libavutil/log.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"
#ಅನ್ತರ್ಭಾವ "libavutil/rational.h"
#ಅನ್ತರ್ಭಾವ "libavutil/opt.h"
#ಅನ್ತರ್ಭಾವ "libavutil/pixdesc.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ TestContext {
    ಸ್ಥಿರಾಂಕ AVClass *class;
    ರಚನೆ ಮಗು_Context *ಮಗು;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ;
    ಪೂರ್ಣಾಂಕ unum;
    ಪೂರ್ಣಾಂಕ toggle;
    ಅಕ್ಷರ *string;
    ಪೂರ್ಣಾಂಕ flags;
    AVRational rational;
    AVRational video_ದರ;
    ಪೂರ್ಣಾಂಕ w, h;
    ಎಣಿಕೆ AVPixelFormat pix_fmt;
    ಎಣಿಕೆ AVSampleFormat sample_fmt;
    int64_t duration;
    uint8_t color[4];
    AVChannelLayout channel_layout;
    ಶೂನ್ಯ *ದ್ವಿಮಾನ;
    ಪೂರ್ಣಾಂಕ ದ್ವಿಮಾನ_ಗಾತ್ರ;
    ಶೂನ್ಯ *binary1;
    ಪೂರ್ಣಾಂಕ ದ್ವಿಮಾನ_size1;
    ಶೂನ್ಯ *binary2;
    ಪೂರ್ಣಾಂಕ ದ್ವಿಮಾನ_size2;
    int64_t num64;
    ದಶಮಾಂಶ flt;
    ದ್ವಿಗುಣ dbl;
    ಅಕ್ಷರ *escape;
    ಪೂರ್ಣಾಂಕ bool1;
    ಪೂರ್ಣಾಂಕ bool2;
    ಪೂರ್ಣಾಂಕ bool3;
    AVDictionary *dict1;
    AVDictionary *dict2;

    ಪೂರ್ಣಾಂಕ           **array_int;
    ಚಿಹ್ನೆರಹಿತ     nb_array_int;

    ಅಕ್ಷರ          **array_str;
    ಚಿಹ್ನೆರಹಿತ     nb_array_str;

    AVDictionary  **array_dict;
    ಚಿಹ್ನೆರಹಿತ     nb_array_dict;
} TestContext;

#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಥಾನಾಂತರ_2(x) offsetof(TestContext, x)

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_FLAG_COOL 01
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_FLAG_LAME 02
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_FLAG_MU   04

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOptionArrayDef array_str = {
    .sep         = '|',
    .def         = "str0|str\\|1|str\\\\2",
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOptionArrayDef array_dict = {
    // there are three levels of escaping - C string, array option, dict - so 8 backslashes are needed to get a literal one inside a dict key/val
    .def         = "k00=v\\\\\\\\00:k01=v\\,01,k10=v\\\\=1\\\\:0",
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOption test_options[]= {
    {"num",        "set num",            ಸ್ಥಾನಾಂತರ_2(ಅಂಕೆ),            AV_OPT_TYPE_INT,            { .i64 = 0 },                     -1,       100, 1 },
    {"unum",       "set unum",           ಸ್ಥಾನಾಂತರ_2(unum),           AV_OPT_TYPE_UINT,           { .i64 = 1U << 31 },               0,  1U << 31, 1 },
    {"toggle",     "set toggle",         ಸ್ಥಾನಾಂತರ_2(toggle),         AV_OPT_TYPE_INT,            { .i64 = 1 },                      0,         1, 1 },
    {"rational",   "set rational",       ಸ್ಥಾನಾಂತರ_2(rational),       AV_OPT_TYPE_RATIONAL,       { .dbl = 1 },                      0,        10, 1 },
    {"string",     "set string",         ಸ್ಥಾನಾಂತರ_2(string),         AV_OPT_TYPE_STRING,         { .str = "default" },       CHAR_MIN,  CHAR_MAX, 1 },
    {"escape",     "set escape str",     ಸ್ಥಾನಾಂತರ_2(escape),         AV_OPT_TYPE_STRING,         { .str = "\\=," },          CHAR_MIN,  CHAR_MAX, 1 },
    {"flags",      "set flags",          ಸ್ಥಾನಾಂತರ_2(flags),          AV_OPT_TYPE_FLAGS,          { .i64 = 1 },                      0,   ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1, .unit = "flags" },
    {"cool",       "set cool flag",      0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_COOL },   INT_MIN,   ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1, .unit = "flags" },
    {"lame",       "set lame flag",      0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_LAME },   INT_MIN,   ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1, .unit = "flags" },
    {"mu",         "set mu flag",        0,                      AV_OPT_TYPE_CONST,          { .i64 = TEST_FLAG_MU },     INT_MIN,   ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1, .unit = "flags" },
    {"size",       "set size",           ಸ್ಥಾನಾಂತರ_2(w),              AV_OPT_TYPE_IMAGE_ಗಾತ್ರ,     { .str="200x300" },                0,         0, 1 },
    {"pix_fmt",    "set pixfmt",         ಸ್ಥಾನಾಂತರ_2(pix_fmt),        AV_OPT_TYPE_PIXEL_FMT,      { .i64 = AV_PIX_FMT_0BGR },       -1,   ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1 },
    {"sample_fmt", "set samplefmt",      ಸ್ಥಾನಾಂತರ_2(sample_fmt),     AV_OPT_TYPE_SAMPLE_FMT,     { .i64 = AV_SAMPLE_FMT_S16 },     -1,   ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1 },
    {"video_rate", "set videorate",      ಸ್ಥಾನಾಂತರ_2(video_ದರ),     AV_OPT_TYPE_VIDEO_ದರ,     { .str = "25" },                   0,         ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1 },
    {"duration",   "set duration",       ಸ್ಥಾನಾಂತರ_2(duration),       AV_OPT_TYPE_DURATION,       { .i64 = 1000 },                   0, INT64_MAX, 1 },
    {"color",      "set color",          ಸ್ಥಾನಾಂತರ_2(color),          AV_OPT_TYPE_COLOR,          { .str = "pink" },                 0,         0, 1 },
    {"cl",         "set channel layout", ಸ್ಥಾನಾಂತರ_2(channel_layout), AV_OPT_TYPE_CHLAYOUT,       { .str = "hexagonal" },            0,         0, 1 },
    {"bin",        "set binary value",   ಸ್ಥಾನಾಂತರ_2(ದ್ವಿಮಾನ),         AV_OPT_TYPE_ದ್ವಿಮಾನ,         { .str="62696e00" },               0,         0, 1 },
    {"bin1",       "set binary value",   ಸ್ಥಾನಾಂತರ_2(binary1),        AV_OPT_TYPE_ದ್ವಿಮಾನ,         { .str=ಖಾಲಿ },                     0,         0, 1 },
    {"bin2",       "set binary value",   ಸ್ಥಾನಾಂತರ_2(binary2),        AV_OPT_TYPE_ದ್ವಿಮಾನ,         { .str="" },                       0,         0, 1 },
    {"num64",      "set num 64bit",      ಸ್ಥಾನಾಂತರ_2(num64),          AV_OPT_TYPE_INT64,          { .i64 = 1LL << 32 },             -1, 1LL << 32, 1 },
    {"flt",        "set float",          ಸ್ಥಾನಾಂತರ_2(flt),            AV_OPT_TYPE_FLOAT,          { .dbl = 1.0 / 3 },                0,       100, 1 },
    {"dbl",        "set double",         ಸ್ಥಾನಾಂತರ_2(dbl),            AV_OPT_TYPE_DOUBLE,         { .dbl = 1.0 / 3 },                0,       100, 1 },
    {"bool1",      "set boolean value",  ಸ್ಥಾನಾಂತರ_2(bool1),          AV_OPT_TYPE_BOOL,           { .i64 = -1 },                    -1,         1, 1 },
    {"bool2",      "set boolean value",  ಸ್ಥಾನಾಂತರ_2(bool2),          AV_OPT_TYPE_BOOL,           { .i64 = 1 },                     -1,         1, 1 },
    {"bool3",      "set boolean value",  ಸ್ಥಾನಾಂತರ_2(bool3),          AV_OPT_TYPE_BOOL,           { .i64 = 0 },                      0,         1, 1 },
    {"dict1",      "set dictionary value", ಸ್ಥಾನಾಂತರ_2(dict1),        AV_OPT_TYPE_DICT,           { .str = ಖಾಲಿ},                    0,         0, 1 },
    {"dict2",      "set dictionary value", ಸ್ಥಾನಾಂತರ_2(dict2),        AV_OPT_TYPE_DICT,           { .str = "happy=':-)'"},           0,         0, 1 },
    {"array_int",  "array of ints",        ಸ್ಥಾನಾಂತರ_2(array_int),    AV_OPT_TYPE_INT | AV_OPT_TYPE_FLAG_ARRAY, .max = ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ,           .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    {"array_str",  "array of strings",     ಸ್ಥಾನಾಂತರ_2(array_str),    AV_OPT_TYPE_STRING | AV_OPT_TYPE_FLAG_ARRAY, { .arr = &array_str }, .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    {"array_dict", "array of dicts",       ಸ್ಥಾನಾಂತರ_2(array_dict),   AV_OPT_TYPE_DICT | AV_OPT_TYPE_FLAG_ARRAY, { .arr = &array_dict },  .flags = AV_OPT_FLAG_RUNTIME_PARAM },
    { ಖಾಲಿ },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *test_get_name(ಶೂನ್ಯ *ctx)
{
    ಹಿಂತಿರುಗಿ "test";
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಮಗು_Context {
    ಸ್ಥಿರಾಂಕ AVClass *class;
    int64_t ಮಗು_num64;
    ಪೂರ್ಣಾಂಕ ಮಗು_ಅಂಕೆ;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಮಗು_unum;
} ಮಗು_Context;

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಸ್ಥಾನಾಂತರ_2
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಥಾನಾಂತರ_2(x) offsetof(ಮಗು_Context, x)

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOption ಮಗು_options[]= {
    {"child_num64", "set num 64bit", ಸ್ಥಾನಾಂತರ_2(ಮಗು_num64), AV_OPT_TYPE_INT64, { .i64 = 0 }, 0, 100, 1 | AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY },
    {"child_num",   "set child_num", ಸ್ಥಾನಾಂತರ_2(ಮಗು_ಅಂಕೆ),   AV_OPT_TYPE_INT,   { .i64 = 1 }, 0, 100, 1 },
    {"child_unum",  "set child_unum", ಸ್ಥಾನಾಂತರ_2(ಮಗು_unum),  AV_OPT_TYPE_UINT,  { .i64 = 0 }, 0, 100, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY },
    { ಖಾಲಿ },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಗು_get_name(ಶೂನ್ಯ *ctx)
{
    ಹಿಂತಿರುಗಿ "child";
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass ಮಗು_class = {
    .class_name = "ChildContext",
    .ಅಂಶ_name  = ಮಗು_get_name,
    .option     = ಮಗು_options,
    .ಆವೃತ್ತಿ    = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
};

ಸ್ಥಿರ ಶೂನ್ಯ *test_ಮಗು_ಮುಂದಿನ(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *prev)
{
    TestContext *test_ctx = obj;
    ಆದರೆ (!prev)
        ಹಿಂತಿರುಗಿ test_ctx->ಮಗು;
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass test_class = {
    .class_name = "TestContext",
    .ಅಂಶ_name  = test_get_name,
    .option     = test_options,
    .ಮಗು_ಮುಂದಿನ = test_ಮಗು_ಮುಂದಿನ,
    .ಆವೃತ್ತಿ    = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
};

ಸ್ಥಿರ ಶೂನ್ಯ log_callback_help(ಶೂನ್ಯ *ptr, ಪೂರ್ಣಾಂಕ level, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list vl)
{
    vfprintf(stdout, fmt, vl);
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ i;

    av_log_ಗಣ_level(AV_LOG_DEBUG);
    av_log_ಗಣ_callback(log_callback_help);

    ಬರೆ("Testing default values\n");
    {
        TestContext test_ctx = { 0 };
        test_ctx.class = &test_class;
        av_opt_ಗಣ_defaults(&test_ctx);

        ಬರೆ("num=%d\n", test_ctx.ಅಂಕೆ);
        ಬರೆ("unum=%u\n", test_ctx.unum);
        ಬರೆ("toggle=%d\n", test_ctx.toggle);
        ಬರೆ("string=%s\n", test_ctx.string);
        ಬರೆ("escape=%s\n", test_ctx.escape);
        ಬರೆ("flags=%d\n", test_ctx.flags);
        ಬರೆ("rational=%d/%d\n", test_ctx.rational.ಅಂಕೆ, test_ctx.rational.den);
        ಬರೆ("video_rate=%d/%d\n", test_ctx.video_ದರ.ಅಂಕೆ, test_ctx.video_ದರ.den);
        ಬರೆ("width=%d height=%d\n", test_ctx.w, test_ctx.h);
        ಬರೆ("pix_fmt=%s\n", av_get_pix_fmt_name(test_ctx.pix_fmt));
        ಬರೆ("sample_fmt=%s\n", av_get_sample_fmt_name(test_ctx.sample_fmt));
        ಬರೆ("duration=%"PRId64"\n", test_ctx.duration);
        ಬರೆ("color=%d %d %d %d\n", test_ctx.color[0], test_ctx.color[1], test_ctx.color[2], test_ctx.color[3]);
        ಬರೆ("channel_layout=%"PRId64"=%"PRId64"\n", test_ctx.channel_layout.u.ಮುಖವಾಡ_2, (int64_t)AV_CH_LAYOUT_HEXAGONAL);
        ಆದರೆ (test_ctx.ದ್ವಿಮಾನ)
            ಬರೆ("binary=%x %x %x %x\n", ((uint8_t*)test_ctx.ದ್ವಿಮಾನ)[0], ((uint8_t*)test_ctx.ದ್ವಿಮಾನ)[1], ((uint8_t*)test_ctx.ದ್ವಿಮಾನ)[2], ((uint8_t*)test_ctx.ದ್ವಿಮಾನ)[3]);
        ಬರೆ("binary_size=%d\n", test_ctx.ದ್ವಿಮಾನ_ಗಾತ್ರ);
        ಬರೆ("num64=%"PRId64"\n", test_ctx.num64);
        ಬರೆ("flt=%.6f\n", test_ctx.flt);
        ಬರೆ("dbl=%.6f\n", test_ctx.dbl);

        ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < test_ctx.nb_array_str; i++)
            ಬರೆ("array_str[%u]=%s\n", i, test_ctx.array_str[i]);

        ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < test_ctx.nb_array_dict; i++) {
            AVDictionary            *d = test_ctx.array_dict[i];
            ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *e = ಖಾಲಿ;

            ಆಗ ((e = av_dict_iterate(d, e)))
                ಬರೆ("array_dict[%u]: %s\t%s\n", i, e->ಕೀಲಿ, e->ಮೌಲ್ಯ);
        }

        av_opt_show2(&test_ctx, ಖಾಲಿ, -1, 0);

        av_opt_free(&test_ctx);
    }

    ಬರೆ("\nTesting av_opt_is_set_to_default()\n");
    {
        ಪೂರ್ಣಾಂಕ ret;
        TestContext test_ctx = { 0 };
        ಸ್ಥಿರಾಂಕ AVOption *o = ಖಾಲಿ;
        test_ctx.class = &test_class;

        av_log_ಗಣ_level(AV_LOG_QUIET);

        ಆಗ (o = av_opt_ಮುಂದಿನ(&test_ctx, o)) {
            ret = av_opt_is_ಗಣ_ಗಮ್ಯ_default_by_name(&test_ctx, o->name, 0);
            ಬರೆ("name:%10s default:%d error:%s\n", o->name, !!ret, ret < 0 ? av_err2str(ret) : "");
        }
        av_opt_ಗಣ_defaults(&test_ctx);
        ಆಗ (o = av_opt_ಮುಂದಿನ(&test_ctx, o)) {
            ret = av_opt_is_ಗಣ_ಗಮ್ಯ_default_by_name(&test_ctx, o->name, 0);
            ಬರೆ("name:%10s default:%d error:%s\n", o->name, !!ret, ret < 0 ? av_err2str(ret) : "");
        }
        av_opt_free(&test_ctx);
    }

    ಬರೆ("\nTesting av_opt_get/av_opt_set()\n");
    {
        TestContext test_ctx = { 0 };
        TestContext test2_ctx = { 0 };
        ಸ್ಥಿರಾಂಕ AVOption *o = ಖಾಲಿ;
        ಅಕ್ಷರ *val = ಖಾಲಿ;
        ಪೂರ್ಣಾಂಕ ret;

        test_ctx.class = &test_class;
        test2_ctx.class = &test_class;

        av_log_ಗಣ_level(AV_LOG_QUIET);

        av_opt_ಗಣ_defaults(&test_ctx);

        ಆಗ (o = av_opt_ಮುಂದಿನ(&test_ctx, o)) {
            ಅಕ್ಷರ *value1 = ಖಾಲಿ;
            ಅಕ್ಷರ *value2 = ಖಾಲಿ;
            ಪೂರ್ಣಾಂಕ ret1 = AVERROR_BUG;
            ಪೂರ್ಣಾಂಕ ret2 = AVERROR_BUG;
            ಪೂರ್ಣಾಂಕ ret3 = AVERROR_BUG;

            ಆದರೆ (o->type == AV_OPT_TYPE_CONST)
                ಮುಂದುವರಿ;

            ret1 = av_opt_get(&test_ctx, o->name, 0, (uint8_t **)&value1);
            ಆದರೆ (ret1 >= 0) {
                ret2 = av_opt_ಗಣ(&test2_ctx, o->name, value1, 0);
                ಆದರೆ (ret2 >= 0)
                    ret3 = av_opt_get(&test2_ctx, o->name, 0, (uint8_t **)&value2);
            }

            ಬರೆ("name: %-11s get: %-16s set: %-16s get: %-16s %s\n", o->name,
                    ret1 >= 0 ? value1 : av_err2str(ret1),
                    ret2 >= 0 ? "OK" : av_err2str(ret2),
                    ret3 >= 0 ? value2 : av_err2str(ret3),
                    ret1 >= 0 && ret2 >= 0 && ret3 >= 0 && !strcmp(value1, value2) ? "OK" : "Mismatch");
            av_free(value1);
            av_free(value2);
        }

        // av_opt_set(NULL) with an array option resets it
        ret = av_opt_ಗಣ(&test_ctx, "array_dict", ಖಾಲಿ, 0);
        ಬರೆ("av_opt_set(\"array_dict\", NULL) -> %d\n", ret);
        ಬರೆ("array_dict=%sNULL; nb_array_dict=%u\n",
               test_ctx.array_dict ? "non-" : "", test_ctx.nb_array_dict);

        // av_opt_get() on an empty array should return a NULL string
        ret = av_opt_get(&test_ctx, "array_dict", AV_OPT_ALLOW_NULL, (uint8_t**)&val);
        ಬರೆ("av_opt_get(\"array_dict\") -> %s\n", val ? val : "NULL");

        av_opt_free(&test_ctx);
        av_opt_free(&test2_ctx);
    }

    ಬರೆ("\nTesting av_opt_get_array()\n");
    {
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ int_array[] = { 5, 0, 42, 137, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ };

        TestContext test_ctx = { 0 };

        ಪೂರ್ಣಾಂಕ     ಹೊರಹೋಗು_int   [FF_ARRAY_ELEMS(int_array)] = { 0 };
        ದ್ವಿಗುಣ  ಹೊರಹೋಗು_double[FF_ARRAY_ELEMS(int_array)] = { 0. };
        ಅಕ್ಷರ   *ಹೊರಹೋಗು_str   [FF_ARRAY_ELEMS(int_array)] = { ಖಾಲಿ };
        AVDictionary *ಹೊರಹೋಗು_dict[2] = { ಖಾಲಿ };

        ಪೂರ್ಣಾಂಕ ret;

        test_ctx.class = &test_class;

        av_log_ಗಣ_level(AV_LOG_QUIET);

        av_opt_ಗಣ_defaults(&test_ctx);

        test_ctx.array_int    = av_memdup(int_array, ಗಾತ್ರ(int_array));
        test_ctx.nb_array_int = FF_ARRAY_ELEMS(int_array);

        // retrieve as int
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               1, 3, AV_OPT_TYPE_INT, ಹೊರಹೋಗು_int);
        ಬರೆ("av_opt_get_array(\"array_int\", 1, 3, INT)=%d -> [ %d, %d, %d ]\n",
               ret, ಹೊರಹೋಗು_int[0], ಹೊರಹೋಗು_int[1], ಹೊರಹೋಗು_int[2]);

        // retrieve as double
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               3, 2, AV_OPT_TYPE_DOUBLE, ಹೊರಹೋಗು_double);
        ಬರೆ("av_opt_get_array(\"array_int\", 3, 2, DOUBLE)=%d -> [ %.2f, %.2f ]\n",
               ret, ಹೊರಹೋಗು_double[0], ಹೊರಹೋಗು_double[1]);

        // retrieve as str
        ret = av_opt_get_array(&test_ctx, "array_int", 0,
                               0, 5, AV_OPT_TYPE_STRING, ಹೊರಹೋಗು_str);
        ಬರೆ("av_opt_get_array(\"array_int\", 0, 5, STRING)=%d -> "
               "[ %s, %s, %s, %s, %s ]\n", ret,
               ಹೊರಹೋಗು_str[0], ಹೊರಹೋಗು_str[1], ಹೊರಹೋಗು_str[2], ಹೊರಹೋಗು_str[3], ಹೊರಹೋಗು_str[4]);

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(ಹೊರಹೋಗು_str); i++)
            av_freep(&ಹೊರಹೋಗು_str[i]);

        ret = av_opt_get_array(&test_ctx, "array_dict", 0, 0, 2,
                               AV_OPT_TYPE_DICT, ಹೊರಹೋಗು_dict);
        ಬರೆ("av_opt_get_array(\"array_dict\", 0, 2, DICT)=%d\n", ret);

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < test_ctx.nb_array_dict; i++) {
            ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *e = ಖಾಲಿ;
            ಆಗ ((e = av_dict_iterate(test_ctx.array_dict[i], e))) {
                ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *e1 = av_dict_get(ಹೊರಹೋಗು_dict[i], e->ಕೀಲಿ, ಖಾಲಿ, 0);
                ಆದರೆ (!e1 || strcmp(e->ಮೌಲ್ಯ, e1->ಮೌಲ್ಯ)) {
                    ಬರೆ("mismatching dict entry %s: %s/%s\n",
                           e->ಕೀಲಿ, e->ಮೌಲ್ಯ, e1 ? e1->ಮೌಲ್ಯ : "<missing>");
                }
            }
            av_dict_free(&ಹೊರಹೋಗು_dict[i]);
        }

        av_opt_free(&test_ctx);
    }

    ಬರೆ("\nTest av_opt_serialize()\n");
    {
        TestContext test_ctx = { 0 };
        ಅಕ್ಷರ *buf;
        ಪೂರ್ಣಾಂಕ ret;
        test_ctx.class = &test_class;

        av_log_ಗಣ_level(AV_LOG_QUIET);

        av_opt_ಗಣ_defaults(&test_ctx);
        ಆದರೆ (av_opt_serialize(&test_ctx, 0, 0, &buf, '=', ',') >= 0) {
            ಬರೆ("%s\n", buf);
            av_opt_free(&test_ctx);
            memset(&test_ctx, 0, ಗಾತ್ರ(test_ctx));
            test_ctx.class = &test_class;
            ret = av_ಗಣ_options_string(&test_ctx, buf, "=", ",");
            av_free(buf);
            ಆದರೆ (ret < 0)
                ಬರೆ("Error ret '%d'\n", ret);
            ಆದರೆ (av_opt_serialize(&test_ctx, 0, 0, &buf, '=', ',') >= 0) {
                ಮಗು_Context ಮಗು_ctx = { .ಮಗು_num64 = 1, .ಮಗು_unum = 1 };
                ಬರೆ("%s\n", buf);
                av_free(buf);
                ಮಗು_ctx.class = &ಮಗು_class;
                test_ctx.ಮಗು = &ಮಗು_ctx;
                ಬರೆ("Exclude flag EXPORT:\n");
                ಆದರೆ (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ಹುಡುಕು_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    ಬರೆ("%s\n", buf);
                    av_free(buf);
                }
                ಬರೆ("Include flag EXPORT:\n");
                ಆದರೆ (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ಹುಡುಕು_CHILDREN,
                                     &buf, '=', ',') >= 0) {
                    ಬರೆ("%s\n", buf);
                    av_free(buf);
                }
                ಬರೆ("Exclude flag 1:\n");
                ಆದರೆ (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ಹುಡುಕು_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    ಬರೆ("%s\n", buf);
                    av_free(buf);
                }
                ಬರೆ("Include flag 1:\n");
                ಆದರೆ (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ಹುಡುಕು_CHILDREN,
                                     &buf, '=', ',') >= 0) {
                    ಬರೆ("%s\n", buf);
                    av_free(buf);
                }
                ಬರೆ("Exclude exact match flag 1:\n");
                ಆದರೆ (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ಹುಡುಕು_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT|AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    ಬರೆ("%s\n", buf);
                    av_free(buf);
                }
                ಬರೆ("Include exact match flag 1:\n");
                ಆದರೆ (av_opt_serialize(&test_ctx, 1,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ಹುಡುಕು_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT,
                                     &buf, '=', ',') >= 0) {
                    ಬರೆ("%s\n", buf);
                    av_free(buf);
                }
                ಬರೆ("Exclude exact match flag EXPORT|READONLY:\n");
                ಆದರೆ (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ಹುಡುಕು_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT|AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE,
                                     &buf, '=', ',') >= 0) {
                    ಬರೆ("%s\n", buf);
                    av_free(buf);
                }
                ಬರೆ("Include exact match flag EXPORT|READONLY:\n");
                ಆದರೆ (av_opt_serialize(&test_ctx, AV_OPT_FLAG_EXPORT | AV_OPT_FLAG_READONLY,
                                     AV_OPT_SERIALIZE_SKIP_DEFAULTS|AV_OPT_SERIALIZE_ಹುಡುಕು_CHILDREN|
                                     AV_OPT_SERIALIZE_OPT_FLAGS_EXACT,
                                     &buf, '=', ',') >= 0) {
                    ಬರೆ("%s\n", buf);
                    av_free(buf);
                }
                av_opt_free(&ಮಗು_ctx);
                test_ctx.ಮಗು = ಖಾಲಿ;
            }
        }
        av_opt_free(&test_ctx);
    }

    ಬರೆ("\nTesting av_set_options_string()\n");
    {
        TestContext test_ctx = { 0 };
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ options[] = {
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
        av_opt_ಗಣ_defaults(&test_ctx);

        av_log_ಗಣ_level(AV_LOG_QUIET);

        ಗಾಗಿ (i=0; i < FF_ARRAY_ELEMS(options); i++) {
            ಪೂರ್ಣಾಂಕ silence_log = !strcmp(options[i], "rational=-1/0"); // inf formatting differs between platforms
            av_log(&test_ctx, AV_LOG_DEBUG, "Setting options string '%s'\n", options[i]);
            ಆದರೆ (silence_log)
                av_log_ಗಣ_callback(ಖಾಲಿ);
            ಆದರೆ (av_ಗಣ_options_string(&test_ctx, options[i], "=", ":") < 0)
                ಬರೆ("Error '%s'\n", options[i]);
            ಇಲ್ಲದಿದ್ದರೆ
                ಬರೆ("OK    '%s'\n", options[i]);
            av_log_ಗಣ_callback(log_callback_help);
        }
        av_opt_free(&test_ctx);
    }

    ಬರೆ("\nTesting av_opt_set_from_string()\n");
    {
        TestContext test_ctx = { 0 };
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ options[] = {
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
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ shorthand[] = { "num", "string", ಖಾಲಿ };

        test_ctx.class = &test_class;
        av_opt_ಗಣ_defaults(&test_ctx);

        av_log_ಗಣ_level(AV_LOG_QUIET);

        ಗಾಗಿ (i=0; i < FF_ARRAY_ELEMS(options); i++) {
            av_log(&test_ctx, AV_LOG_DEBUG, "Setting options string '%s'\n", options[i]);
            ಆದರೆ (av_opt_ಗಣ_from_string(&test_ctx, options[i], shorthand, "=", ":") < 0)
                ಬರೆ("Error '%s'\n", options[i]);
            ಇಲ್ಲದಿದ್ದರೆ
                ಬರೆ("OK    '%s'\n", options[i]);
        }
        av_opt_free(&test_ctx);
    }

    ಬರೆ("\nTesting av_opt_find2()\n");
    {
        TestContext test_ctx = { 0 };
        ಮಗು_Context ಮಗು_ctx = { 0 };
        ಶೂನ್ಯ *ಗುರಿ;
        ಸ್ಥಿರಾಂಕ AVOption *opt;

        test_ctx.class = &test_class;
        ಮಗು_ctx.class = &ಮಗು_class;
        test_ctx.ಮಗು = &ಮಗು_ctx;

        av_log_ಗಣ_level(AV_LOG_QUIET);

        // Should succeed. num exists and has opt_flags 1
        opt = av_opt_find2(&test_ctx, "num", ಖಾಲಿ, 1, 0, &ಗುರಿ);
        ಆದರೆ (opt && ಗುರಿ == &test_ctx)
            ಬರೆ("OK    '%s'\n", opt->name);
        ಇಲ್ಲದಿದ್ದರೆ
            ಬರೆ("Error 'num'\n");

        // Should fail. num64 exists but has opt_flags 1, not 2
        opt = av_opt_ಕಂಡುಹಿಡಿ(&test_ctx, "num64", ಖಾಲಿ, 2, 0);
        ಆದರೆ (opt)
            ಬರೆ("OK    '%s'\n", opt->name);
        ಇಲ್ಲದಿದ್ದರೆ
            ಬರೆ("Error 'num64'\n");

        // Should fail. child_num exists but in a child object we're not searching
        opt = av_opt_ಕಂಡುಹಿಡಿ(&test_ctx, "child_num", ಖಾಲಿ, 0, 0);
        ಆದರೆ (opt)
            ಬರೆ("OK    '%s'\n", opt->name);
        ಇಲ್ಲದಿದ್ದರೆ
            ಬರೆ("Error 'child_num'\n");

        // Should succeed. child_num exists in a child object we're searching
        opt = av_opt_find2(&test_ctx, "child_num", ಖಾಲಿ, 0, AV_OPT_ಹುಡುಕು_CHILDREN, &ಗುರಿ);
        ಆದರೆ (opt && ಗುರಿ == &ಮಗು_ctx)
            ಬರೆ("OK    '%s'\n", opt->name);
        ಇಲ್ಲದಿದ್ದರೆ
            ಬರೆ("Error 'child_num'\n");

        // Should fail. foo doesn't exist
        opt = av_opt_ಕಂಡುಹಿಡಿ(&test_ctx, "foo", ಖಾಲಿ, 0, 0);
        ಆದರೆ (opt)
            ಬರೆ("OK    '%s'\n", opt->name);
        ಇಲ್ಲದಿದ್ದರೆ
            ಬರೆ("Error 'foo'\n");
    }

    ಬರೆ("\nTesting av_opt_copy() into a memdup'ed object\n");
    {
        TestContext test_ctx = { 0 };
        TestContext *copy;
        uint8_t *layout_name = ಖಾಲಿ;

        test_ctx.class = &test_class;
        av_opt_ಗಣ_defaults(&test_ctx);
        av_opt_ಗಣ(&test_ctx, "cl", "FL@Left+FR@Right", 0);

        copy = av_memdup(&test_ctx, ಗಾತ್ರ(test_ctx));
        ಆದರೆ (!copy)
            ಹಿಂತಿರುಗಿ 1;
        av_opt_copy(copy, &test_ctx);
        av_opt_free(&test_ctx);

        av_opt_get(copy, "cl", 0, &layout_name);
        ಬರೆ("cl=%s\n", layout_name);
        av_free(layout_name);
        av_opt_free(copy);
        av_free(copy);
    }

    ಬರೆ("\nTesting av_opt_copy() of a native layout into a custom layout\n");
    {
        TestContext src = { 0 }, dst = { 0 };
        AVChannelLayout native = { AV_CHANNEL_ಕ್ರಮ_NATIVE };

        src.class = dst.class = &test_class;
        av_opt_ಗಣ_defaults(&src);
        av_opt_ಗಣ_defaults(&dst);
        av_opt_ಗಣ(&dst, "cl", "FL@Left+FR@Right", 0);

        native.u.ಮುಖವಾಡ_2      = (uintptr_t)dst.channel_layout.u.map;
        native.nb_channels = av_popcount64(native.u.ಮುಖವಾಡ_2);
        av_opt_ಗಣ_chlayout(&src, "cl", &native, 0);

        ಬರೆ("copy: %d\n", av_opt_copy(&dst, &src));
        ಬರೆ("same layout: %d\n", !av_channel_layout_compare(&src.channel_layout, &dst.channel_layout));
        av_opt_free(&src);
        av_opt_free(&dst);
    }

    ಹಿಂತಿರುಗಿ 0;
}
