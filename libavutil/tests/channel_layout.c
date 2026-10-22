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

#समावेश <inttypes.h>
#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "libavutil/bprint.h"
#समावेश "libavutil/channel_layout.h"
#समावेश "libavutil/error.h"
#समावेश "libavutil/macros.h"
#समावेश "libavutil/mem.h"

#घोषणा BPRINT_ARGS1(bp, ...)     (bp), __VA_ARGS__
#घोषणा BPRINT_ARGS0(bp, ...)     __VA_ARGS__, (bp)
#घोषणा ORD_ARGS1(str, आकार, ...) (str), (आकार), __VA_ARGS__
#घोषणा ORD_ARGS0(str, आकार, ...) __VA_ARGS__, (str), (आकार)

// This macro presumes the AVBPrint to have been cleared before usage.
#घोषणा CMP_BPRINT_AND_NONBPRINT(bp, func_name, ARG_ORDER, ...) करो {       \
    अक्षर *str;                                                             \
    पूर्णांक आकार;                                                              \
    func_name ## _bprint(BPRINT_ARGS ## ARG_ORDER((bp), __VA_ARGS__));     \
    अगर (म_माप((bp)->str) != (bp)->len) {                                  \
        म_लिखो("strlen of AVBPrint-string returned by "#func_name"_bprint" \
               " differs from AVBPrint.len: %zu vs. %u\n",                 \
               म_माप((bp)->str), (bp)->len);                              \
        अवरोध;                                                             \
    }                                                                      \
    आकार = func_name(ORD_ARGS ## ARG_ORDER(शून्य, 0, __VA_ARGS__));         \
    अगर (आकार <= 0) {                                                       \
        म_लिखो(#func_name " returned %d\n", आकार);                         \
        अवरोध;                                                             \
    }                                                                      \
    अगर ((bp)->len != आकार - 1) {                                           \
        म_लिखो("Return value %d of " #func_name " inconsistent with length"\
               " %u obtained from corresponding bprint version\n",         \
               आकार, (bp)->len);                                           \
        अवरोध;                                                             \
    }                                                                      \
    str = av_malloc(आकार);                                                 \
    अगर (!str) {                                                            \
        म_लिखो("string of size %d could not be allocated.\n", आकार);       \
        अवरोध;                                                             \
    }                                                                      \
    आकार = func_name(ORD_ARGS ## ARG_ORDER(str, आकार, __VA_ARGS__));       \
    अगर (आकार <= 0 || (bp)->len != आकार - 1) {                              \
        म_लिखो("Return value %d of " #func_name " inconsistent with length"\
               " %d obtained in first pass.\n", आकार, (bp)->len);          \
        av_free(str);                                                      \
        अवरोध;                                                             \
    }                                                                      \
    अगर (म_भेद(str, (bp)->str)) {                                          \
        म_लिखो("Ordinary and _bprint versions of "#func_name" disagree: "  \
               "'%s' vs. '%s'\n", str, (bp)->str);                         \
        av_free(str);                                                      \
        अवरोध;                                                             \
    }                                                                      \
    av_free(str);                                                          \
    } जबतक (0)


अटल व्योम channel_name(AVBPrint *bp, क्रमागत AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_name, 1, channel);
}

अटल व्योम channel_description(AVBPrint *bp, क्रमागत AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_description, 1, channel);
}

अटल व्योम channel_layout_from_mask(AVChannelLayout *layout,
                                     AVBPrint *bp, uint64_t channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    अगर (!av_channel_layout_from_mask(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    अन्यथा
        av_bprintf(bp, "fail");
}

अटल व्योम channel_layout_from_string(AVChannelLayout *layout,
                                       AVBPrint *bp, स्थिर अक्षर *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    अगर (!av_channel_layout_from_string(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    अन्यथा
        av_bprintf(bp, "fail");
}

अटल स्थिर अक्षर* channel_order_names[]  = {"UNSPEC", "NATIVE", "CUSTOM", "AMBI"};

अटल व्योम describe_type(AVBPrint *bp, AVChannelLayout *layout)
{
    अगर ((अचिन्हित)layout->order < FF_ARRAY_ELEMS(channel_order_names)) {
        av_bprintf(bp, "%-6s (", channel_order_names[layout->order]);
        av_channel_layout_describe_bprint(layout, bp);
        av_bprintf(bp, ")");
    } अन्यथा {
        av_bprintf(bp, "???");
    }
}

अटल स्थिर अक्षर *channel_layout_retype(AVChannelLayout *layout, AVBPrint *bp, स्थिर अक्षर *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    अगर (!av_channel_layout_from_string(layout, channel_layout) &&
        av_channel_layout_check(layout)) {
        describe_type(bp, layout);
        क्रम (पूर्णांक i = 0; i < FF_CHANNEL_ORDER_NB; i++) {
            पूर्णांक ret;
            AVChannelLayout copy = {0};
            av_bprintf(bp, "\n ");
            अगर (av_channel_layout_copy(&copy, layout) < 0)
                वापस "nomem";
            ret = av_channel_layout_retype(&copy, i, 0);
            अगर (ret < 0 && (copy.order != layout->order || av_channel_layout_compare(&copy, layout)))
                av_bprintf(bp, "failed to keep existing layout on failure");
            अगर (ret >= 0 && copy.order != i)
                av_bprintf(bp, "returned success but did not change order");
            अगर (ret == AVERROR(ENOSYS)) {
                av_bprintf(bp, " != %s", channel_order_names[i]);
            } अन्यथा अगर (ret < 0) {
                av_bprintf(bp, "FAIL");
            } अन्यथा {
                av_bprintf(bp, " %s ", ret ? "~~" : "==");
                describe_type(bp, &copy);
            }
            av_channel_layout_uninit(&copy);
        }
    } अन्यथा {
        av_bprintf(bp, "fail");
    }
    वापस bp->str;
}

#घोषणा CHANNEL_NAME(x)                                                    \
    channel_name(&bp, (x));                                                \
    म_लिखो("With %-32s %14s\n", AV_STRINGIFY(x)":", bp.str)

#घोषणा CHANNEL_DESCRIPTION(x)                                             \
    channel_description(&bp, (x));                                         \
    म_लिखो("With %-23s %23s\n", AV_STRINGIFY(x)":", bp.str);

#घोषणा CHANNEL_FROM_STRING(x)                                             \
    म_लिखो("With %-38s %8d\n", AV_STRINGIFY(x)":", av_channel_from_string(x))

#घोषणा CHANNEL_LAYOUT_FROM_MASK(x)                                        \
    channel_layout_from_mask(&layout, &bp, (x));

#घोषणा CHANNEL_LAYOUT_FROM_STRING(x)                                      \
    channel_layout_from_string(&layout, &bp, (x));                         \
    म_लिखो("With \"%s\":%*s %32s\n", x, म_माप(x) > 32 ? 0 : 32 - (पूर्णांक)म_माप(x), "", bp.str);

#घोषणा CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(l, x)                            \
    ret = av_channel_layout_channel_from_सूचकांक(&layout, x);                \
    अगर (ret < 0)                                                           \
        ret = -1;                                                          \
    म_लिखो("On \"%s\" layout with %2d: %8d\n", l,  x, ret)

#घोषणा CHANNEL_LAYOUT_SUBSET(l, xstr, x)                                  \
    mask = av_channel_layout_subset(&layout, x);                           \
    म_लिखो("On \"%s\" layout with %-22s 0x%"PRIx64"\n", l, xstr, mask)

#घोषणा CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(l, x)                            \
    ret = av_channel_layout_सूचकांक_from_channel(&layout, x);                \
    अगर (ret < 0)                                                           \
        ret = -1;                                                          \
    म_लिखो("On \"%s\" layout with %-23s %3d\n", l, AV_STRINGIFY(x)":", ret)

#घोषणा CHANNEL_LAYOUT_CHANNEL_FROM_STRING(l, x)                           \
    ret = av_channel_layout_channel_from_string(&layout, x);               \
    अगर (ret < 0)                                                           \
        ret = -1;                                                          \
    म_लिखो("On \"%s\" layout with %-21s %3d\n", bp.str, AV_STRINGIFY(x)":", ret);

#घोषणा CHANNEL_LAYOUT_सूचकांक_FROM_STRING(l, x)                             \
    ret = av_channel_layout_सूचकांक_from_string(&layout, x);                 \
    अगर (ret < 0)                                                           \
        ret = -1;                                                          \
    म_लिखो("On \"%s\" layout with %-20s %3d\n", l, AV_STRINGIFY(x)":", ret);

पूर्णांक मुख्य(व्योम)
{
    स्थिर AVChannelLayout *playout;
    AVChannelLayout layout = { 0 }, layout2 = { 0 };
    AVBPrint bp;
    व्योम *iter = शून्य;
    uint64_t mask;
    पूर्णांक ret;

    av_bprint_init(&bp, 64, AV_BPRINT_आकार_AUTOMATIC);

    म_लिखो("Testing av_channel_layout_standard\n");
    जबतक (playout = av_channel_layout_standard(&iter)) {
        av_channel_layout_describe_bprint(playout, &bp);
        म_लिखो("%-14s ", bp.str);
        av_bprint_clear(&bp);
        क्रम (पूर्णांक i = 0; i < 63; i++) {
            पूर्णांक idx = av_channel_layout_सूचकांक_from_channel(playout, i);
            अगर (idx >= 0) {
                अगर (idx)
                    av_bprintf(&bp, "+");
                av_channel_name_bprint(&bp, i);
            }
        }
        म_लिखो("%s\n", bp.str);
        av_bprint_clear(&bp);
    }

    म_लिखो("\nTesting av_channel_name\n");
    CHANNEL_NAME(AV_CHAN_FRONT_बायाँ);
    CHANNEL_NAME(AV_CHAN_FRONT_दायाँ);
    CHANNEL_NAME(63);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_BASE);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_END);

    म_लिखो("Testing av_channel_description\n");
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_बायाँ);
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_दायाँ);
    CHANNEL_DESCRIPTION(63);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_BASE);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_END);

    म_लिखो("\nTesting av_channel_from_string\n");
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

    म_लिखो("\n==Native layouts==\n");

    म_लिखो("\nTesting av_channel_layout_from_string\n");
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

    म_लिखो("\nTesting av_channel_layout_from_mask\n");
    CHANNEL_LAYOUT_FROM_MASK(AV_CH_LAYOUT_5POINT1);
    म_लिखो("With AV_CH_LAYOUT_5POINT1: %25s\n", bp.str);

    म_लिखो("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 3);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 4);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 5);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 6);

    म_लिखो("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_बायाँ);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_दायाँ);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_CENTER);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_निचला_FREQUENCY);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_बायाँ);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_दायाँ);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_BACK_CENTER);

    म_लिखो("\nTesting av_channel_layout_channel_from_string\n");
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

    म_लिखो("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FC");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "LFE");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "SL");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "SR");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "BC");

    म_लिखो("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:",  AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_2POINT1:", AV_CH_LAYOUT_2POINT1);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_4POINT1:", AV_CH_LAYOUT_4POINT1);

    म_लिखो("\n==Custom layouts==\n");

    म_लिखो("\nTesting av_channel_layout_from_string\n");
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
    अगर (ret < 0) {
        म_लिखो("Copying channel layout \"FR+FL@Foo+USR63@Foo\" failed; "
               "ret %d\n", ret);
    }
    ret = av_channel_layout_compare(&layout, &layout2);
    अगर (ret)
        म_लिखो("Channel layout and its copy compare unequal; ret: %d\n", ret);

    म_लिखो("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "BC");

    म_लिखो("\nTesting av_channel_layout_channel_from_string\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "BC");

    म_लिखो("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_दायाँ);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_बायाँ);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, 63);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_BACK_CENTER);

    म_लिखो("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 3);

    म_लिखो("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    म_लिखो("\n==Ambisonic layouts==\n");

    म_लिखो("\nTesting av_channel_layout_from_string\n");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 1");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 2+stereo");

    म_लिखो("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_AMBISONIC_BASE);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_बायाँ);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_दायाँ);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_BACK_CENTER);

    म_लिखो("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 9);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 10);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 11);

    म_लिखो("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    av_channel_layout_uninit(&layout);
    av_channel_layout_uninit(&layout2);

    म_लिखो("\nTesting av_channel_layout_retype\n");
    {
        स्थिर अक्षर* layouts[] = {
            "FL@Boo",
            "stereo",
            "FR+FL",
            "ambisonic 2+stereo",
            "2C",
            शून्य
        };
        क्रम (पूर्णांक i = 0; layouts[i]; i++)
            म_लिखो("With \"%s\": %s\n", layouts[i], channel_layout_retype(&layout, &bp, layouts[i]));
    }
    av_bprint_finalize(&bp, शून्य);

    वापस 0;
}
