/*
 * Copyright (c) 2021 James Almer
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

#شامل <inttypes.h>
#شامل <stdio.h>
#شامل <string.h>

#شامل "libavutil/bprint.h"
#شامل "libavutil/channel_layout.h"
#شامل "libavutil/error.h"
#شامل "libavutil/macros.h"
#شامل "libavutil/mem.h"

#تعریف_کرو BPRINT_ARGS1(bp, ...)     (bp), __VA_ARGS__
#تعریف_کرو BPRINT_ARGS0(bp, ...)     __VA_ARGS__, (bp)
#تعریف_کرو ORD_ARGS1(str, سائز, ...) (str), (سائز), __VA_ARGS__
#تعریف_کرو ORD_ARGS0(str, سائز, ...) __VA_ARGS__, (str), (سائز)

// This macro presumes the AVBPrint to have been cleared before usage.
#تعریف_کرو CMP_BPRINT_AND_NONBPRINT(bp, func_name, ARG_ترتیب, ...) کرو {       \
    حرف *str;                                                             \
    صحیح سائز;                                                              \
    func_name ## _bprint(BPRINT_دلائل ## ARG_ترتیب((bp), __VA_ARGS__));     \
    اگر (لڑی_لمبائی((bp)->str) != (bp)->len) {                                  \
        لکھو("strlen of AVBPrint-string returned by "#func_name"_bprint" \
               " differs from AVBPrint.len: %zu vs. %u\n",                 \
               لڑی_لمبائی((bp)->str), (bp)->len);                              \
        توڑو;                                                             \
    }                                                                      \
    سائز = func_name(ORD_دلائل ## ARG_ترتیب(تہی, 0, __VA_ARGS__));         \
    اگر (سائز <= 0) {                                                       \
        لکھو(#func_name " returned %d\n", سائز);                         \
        توڑو;                                                             \
    }                                                                      \
    اگر ((bp)->len != سائز - 1) {                                           \
        لکھو("Return value %d of " #func_name " inconsistent with length"\
               " %u obtained from corresponding bprint version\n",         \
               سائز, (bp)->len);                                           \
        توڑو;                                                             \
    }                                                                      \
    str = av_malloc(سائز);                                                 \
    اگر (!str) {                                                            \
        لکھو("string of size %d could not be allocated.\n", سائز);       \
        توڑو;                                                             \
    }                                                                      \
    سائز = func_name(ORD_دلائل ## ARG_ترتیب(str, سائز, __VA_ARGS__));       \
    اگر (سائز <= 0 || (bp)->len != سائز - 1) {                              \
        لکھو("Return value %d of " #func_name " inconsistent with length"\
               " %d obtained in first pass.\n", سائز, (bp)->len);          \
        av_free(str);                                                      \
        توڑو;                                                             \
    }                                                                      \
    اگر (strcmp(str, (bp)->str)) {                                          \
        لکھو("Ordinary and _bprint versions of "#func_name" disagree: "  \
               "'%s' vs. '%s'\n", str, (bp)->str);                         \
        av_free(str);                                                      \
        توڑو;                                                             \
    }                                                                      \
    av_free(str);                                                          \
    } جب (0)


ساکن خالی channel_name(AVBPrint *bp, شمار AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_name, 1, channel);
}

ساکن خالی channel_description(AVBPrint *bp, شمار AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_description, 1, channel);
}

ساکن خالی channel_layout_from_نقاب(AVChannelLayout *layout,
                                     AVBPrint *bp, uint64_t channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    اگر (!av_channel_layout_from_نقاب(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    ورنہ
        av_bprintf(bp, "fail");
}

ساکن خالی channel_layout_from_string(AVChannelLayout *layout,
                                       AVBPrint *bp, ثابت حرف *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    اگر (!av_channel_layout_from_string(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    ورنہ
        av_bprintf(bp, "fail");
}

ساکن ثابت حرف* channel_ترتیب_نام[]  = {"UNSPEC", "NATIVE", "CUSTOM", "AMBI"};

ساکن خالی describe_type(AVBPrint *bp, AVChannelLayout *layout)
{
    اگر ((غیرعلامتی)layout->ترتیب < FF_ARRAY_ELEMS(channel_ترتیب_نام)) {
        av_bprintf(bp, "%-6s (", channel_ترتیب_نام[layout->ترتیب]);
        av_channel_layout_describe_bprint(layout, bp);
        av_bprintf(bp, ")");
    } ورنہ {
        av_bprintf(bp, "???");
    }
}

ساکن ثابت حرف *channel_layout_retype(AVChannelLayout *layout, AVBPrint *bp, ثابت حرف *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    اگر (!av_channel_layout_from_string(layout, channel_layout) &&
        av_channel_layout_check(layout)) {
        describe_type(bp, layout);
        برائے (صحیح i = 0; i < FF_CHANNEL_ترتیب_NB; i++) {
            صحیح ret;
            AVChannelLayout copy = {0};
            av_bprintf(bp, "\n ");
            اگر (av_channel_layout_copy(&copy, layout) < 0)
                واپس "nomem";
            ret = av_channel_layout_retype(&copy, i, 0);
            اگر (ret < 0 && (copy.ترتیب != layout->ترتیب || av_channel_layout_compare(&copy, layout)))
                av_bprintf(bp, "failed to keep existing layout on failure");
            اگر (ret >= 0 && copy.ترتیب != i)
                av_bprintf(bp, "returned success but did not change order");
            اگر (ret == AVERROR(ENOSYS)) {
                av_bprintf(bp, " != %s", channel_ترتیب_نام[i]);
            } ورنہ اگر (ret < 0) {
                av_bprintf(bp, "FAIL");
            } ورنہ {
                av_bprintf(bp, " %s ", ret ? "~~" : "==");
                describe_type(bp, &copy);
            }
            av_channel_layout_uninit(&copy);
        }
    } ورنہ {
        av_bprintf(bp, "fail");
    }
    واپس bp->str;
}

#تعریف_کرو CHANNEL_NAME(x)                                                    \
    channel_name(&bp, (x));                                                \
    لکھو("With %-32s %14s\n", AV_STRINGIFY(x)":", bp.str)

#تعریف_کرو CHANNEL_DESCRIPTION(x)                                             \
    channel_description(&bp, (x));                                         \
    لکھو("With %-23s %23s\n", AV_STRINGIFY(x)":", bp.str);

#تعریف_کرو CHANNEL_FROM_STRING(x)                                             \
    لکھو("With %-38s %8d\n", AV_STRINGIFY(x)":", av_channel_from_string(x))

#تعریف_کرو CHANNEL_LAYOUT_FROM_نقاب(x)                                        \
    channel_layout_from_نقاب(&layout, &bp, (x));

#تعریف_کرو CHANNEL_LAYOUT_FROM_STRING(x)                                      \
    channel_layout_from_string(&layout, &bp, (x));                         \
    لکھو("With \"%s\":%*s %32s\n", x, لڑی_لمبائی(x) > 32 ? 0 : 32 - (صحیح)لڑی_لمبائی(x), "", bp.str);

#تعریف_کرو CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(l, x)                            \
    ret = av_channel_layout_channel_from_اشاریہ(&layout, x);                \
    اگر (ret < 0)                                                           \
        ret = -1;                                                          \
    لکھو("On \"%s\" layout with %2d: %8d\n", l,  x, ret)

#تعریف_کرو CHANNEL_LAYOUT_SUBSET(l, xstr, x)                                  \
    نقاب_2 = av_channel_layout_subset(&layout, x);                           \
    لکھو("On \"%s\" layout with %-22s 0x%"PRIx64"\n", l, xstr, نقاب_2)

#تعریف_کرو CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(l, x)                            \
    ret = av_channel_layout_اشاریہ_from_channel(&layout, x);                \
    اگر (ret < 0)                                                           \
        ret = -1;                                                          \
    لکھو("On \"%s\" layout with %-23s %3d\n", l, AV_STRINGIFY(x)":", ret)

#تعریف_کرو CHANNEL_LAYOUT_CHANNEL_FROM_STRING(l, x)                           \
    ret = av_channel_layout_channel_from_string(&layout, x);               \
    اگر (ret < 0)                                                           \
        ret = -1;                                                          \
    لکھو("On \"%s\" layout with %-21s %3d\n", bp.str, AV_STRINGIFY(x)":", ret);

#تعریف_کرو CHANNEL_LAYOUT_اشاریہ_FROM_STRING(l, x)                             \
    ret = av_channel_layout_اشاریہ_from_string(&layout, x);                 \
    اگر (ret < 0)                                                           \
        ret = -1;                                                          \
    لکھو("On \"%s\" layout with %-20s %3d\n", l, AV_STRINGIFY(x)":", ret);

صحیح مین(خالی)
{
    ثابت AVChannelLayout *playout;
    AVChannelLayout layout = { 0 }, layout2 = { 0 };
    AVBPrint bp;
    خالی *iter = تہی;
    uint64_t نقاب_2;
    صحیح ret;

    av_bprint_init(&bp, 64, AV_BPRINT_سائز_AUTOMATIC);

    لکھو("Testing av_channel_layout_standard\n");
    جب (playout = av_channel_layout_standard(&iter)) {
        av_channel_layout_describe_bprint(playout, &bp);
        لکھو("%-14s ", bp.str);
        av_bprint_clear(&bp);
        برائے (صحیح i = 0; i < 63; i++) {
            صحیح idx = av_channel_layout_اشاریہ_from_channel(playout, i);
            اگر (idx >= 0) {
                اگر (idx)
                    av_bprintf(&bp, "+");
                av_channel_name_bprint(&bp, i);
            }
        }
        لکھو("%s\n", bp.str);
        av_bprint_clear(&bp);
    }

    لکھو("\nTesting av_channel_name\n");
    CHANNEL_NAME(AV_CHAN_FRONT_بایاں);
    CHANNEL_NAME(AV_CHAN_FRONT_دایاں);
    CHANNEL_NAME(63);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_بنیاد);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_انتہا);

    لکھو("Testing av_channel_description\n");
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_بایاں);
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_دایاں);
    CHANNEL_DESCRIPTION(63);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_بنیاد);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_انتہا);

    لکھو("\nTesting av_channel_from_string\n");
    CHANNEL_FROM_STRING("FL");
    CHANNEL_FROM_STRING("FR");
    CHANNEL_FROM_STRING("USR63");
    CHANNEL_FROM_STRING("AMBI0");
    CHANNEL_FROM_STRING("AMBI1023");
    CHANNEL_FROM_STRING("AMBI1024");
    CHANNEL_FROM_STRING("Dummy");
    CHANNEL_FROM_STRING("FL@Foo");
    CHANNEL_FROM_STRING("Foo@FL");
    CHANNEL_FROM_STRING("@FL");

    لکھو("\n==Native layouts==\n");

    لکھو("\nTesting av_channel_layout_from_string\n");
    CHANNEL_LAYOUT_FROM_STRING("0x3f");
    CHANNEL_LAYOUT_FROM_STRING("63");
    CHANNEL_LAYOUT_FROM_STRING("6c");
    CHANNEL_LAYOUT_FROM_STRING("6C");
    CHANNEL_LAYOUT_FROM_STRING("6 channels");
    CHANNEL_LAYOUT_FROM_STRING("6 channels (FL+FR+FC+LFE+BL+BR)");
    CHANNEL_LAYOUT_FROM_STRING("FL+FR+FC+LFE+BL+BR");
    CHANNEL_LAYOUT_FROM_STRING("5.1");
    CHANNEL_LAYOUT_FROM_STRING("FL+FR+USR63");
    CHANNEL_LAYOUT_FROM_STRING("FL+FR+FC+LFE+SL+SR");
    CHANNEL_LAYOUT_FROM_STRING("5.1(side)");

    لکھو("\nTesting av_channel_layout_from_mask\n");
    CHANNEL_LAYOUT_FROM_نقاب(AV_CH_LAYOUT_5POINT1);
    لکھو("With AV_CH_LAYOUT_5POINT1: %25s\n", bp.str);

    لکھو("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 3);
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 4);
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 5);
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 6);

    لکھو("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_بایاں);
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_دایاں);
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_CENTER);
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_کم_FREQUENCY);
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_بایاں);
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_دایاں);
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_عقب_CENTER);

    لکھو("\nTesting av_channel_layout_channel_from_string\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FC");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "LFE");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "SL");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "SR");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "BC");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "@");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL@Foo");

    لکھو("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "FC");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "LFE");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "SL");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "SR");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "BC");

    لکھو("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:",  AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_2POINT1:", AV_CH_LAYOUT_2POINT1);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_4POINT1:", AV_CH_LAYOUT_4POINT1);

    لکھو("\n==Custom layouts==\n");

    لکھو("\nTesting av_channel_layout_from_string\n");
    CHANNEL_LAYOUT_FROM_STRING("FL+FR+FC+BL+BR+LFE");
    CHANNEL_LAYOUT_FROM_STRING("2 channels (FR+FL)");
    CHANNEL_LAYOUT_FROM_STRING("2 channels (AMBI1023+FL)");
    CHANNEL_LAYOUT_FROM_STRING("3 channels (FR+FL)");
    CHANNEL_LAYOUT_FROM_STRING("-3 channels (FR+FL)");
    CHANNEL_LAYOUT_FROM_STRING("0 channels ()");
    CHANNEL_LAYOUT_FROM_STRING("2 channels (FL+FR");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 1+FR+FL");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 2+FC@Foo");
    CHANNEL_LAYOUT_FROM_STRING("FL@Foo+FR@Bar");
    CHANNEL_LAYOUT_FROM_STRING("FL+stereo");
    CHANNEL_LAYOUT_FROM_STRING("stereo+stereo");
    CHANNEL_LAYOUT_FROM_STRING("stereo@Boo");
    CHANNEL_LAYOUT_FROM_STRING("");
    CHANNEL_LAYOUT_FROM_STRING("@");
    CHANNEL_LAYOUT_FROM_STRING("@Dummy");
    CHANNEL_LAYOUT_FROM_STRING("@FL");
    CHANNEL_LAYOUT_FROM_STRING("Dummy");
    CHANNEL_LAYOUT_FROM_STRING("Dummy@FL");
    CHANNEL_LAYOUT_FROM_STRING("FR+Dummy");
    CHANNEL_LAYOUT_FROM_STRING("FR+Dummy@FL");
    CHANNEL_LAYOUT_FROM_STRING("UNK+UNSD");
    CHANNEL_LAYOUT_FROM_STRING("NONE");
    CHANNEL_LAYOUT_FROM_STRING("FR+@FL");
    CHANNEL_LAYOUT_FROM_STRING("FL+@");
    CHANNEL_LAYOUT_FROM_STRING("FR+FL@Foo+USR63@Foo");

    ret = av_channel_layout_copy(&layout2, &layout);
    اگر (ret < 0) {
        لکھو("Copying channel layout \"FR+FL@Foo+USR63@Foo\" failed; "
               "ret %d\n", ret);
    }
    ret = av_channel_layout_compare(&layout, &layout2);
    اگر (ret)
        لکھو("Channel layout and its copy compare unequal; ret: %d\n", ret);

    لکھو("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_اشاریہ_FROM_STRING(bp.str, "BC");

    لکھو("\nTesting av_channel_layout_channel_from_string\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "BC");

    لکھو("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_دایاں);
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_بایاں);
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, 63);
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_عقب_CENTER);

    لکھو("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 3);

    لکھو("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    لکھو("\n==Ambisonic layouts==\n");

    لکھو("\nTesting av_channel_layout_from_string\n");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 1");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 2+stereo");

    لکھو("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_AMBISONIC_بنیاد);
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_بایاں);
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_دایاں);
    CHANNEL_LAYOUT_اشاریہ_FROM_CHANNEL(bp.str, AV_CHAN_عقب_CENTER);

    لکھو("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 9);
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 10);
    CHANNEL_LAYOUT_CHANNEL_FROM_اشاریہ(bp.str, 11);

    لکھو("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    av_channel_layout_uninit(&layout);
    av_channel_layout_uninit(&layout2);

    لکھو("\nTesting av_channel_layout_retype\n");
    {
        ثابت حرف* layouts[] = {
            "FL@Boo",
            "stereo",
            "FR+FL",
            "ambisonic 2+stereo",
            "2C",
            تہی
        };
        برائے (صحیح i = 0; layouts[i]; i++)
            لکھو("With \"%s\": %s\n", layouts[i], channel_layout_retype(&layout, &bp, layouts[i]));
    }
    av_bprint_finalize(&bp, تہی);

    واپس 0;
}
