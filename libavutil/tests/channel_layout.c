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

#अन्तर्भाव <inttypes.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/bprint.h"
#अन्तर्भाव "libavutil/channel_layout.h"
#अन्तर्भाव "libavutil/error.h"
#अन्तर्भाव "libavutil/macros.h"
#अन्तर्भाव "libavutil/mem.h"

#परिभाषय BPRINT_ARGS1(bp, ...)     (bp), __VA_ARGS__
#परिभाषय BPRINT_ARGS0(bp, ...)     __VA_ARGS__, (bp)
#परिभाषय ORD_ARGS1(str, आकार, ...) (str), (आकार), __VA_ARGS__
#परिभाषय ORD_ARGS0(str, आकार, ...) __VA_ARGS__, (str), (आकार)

// This macro presumes the AVBPrint to have been cleared before usage.
#परिभाषय CMP_BPRINT_AND_NONBPRINT(bp, func_name, ARG_क्रमः, ...) कुरु {       \
    वर्ण *str;                                                             \
    पूर्णाङ्क आकार;                                                              \
    func_name ## _bprint(BPRINT_तर्काः ## ARG_क्रमः((bp), __VA_ARGS__));     \
    यदि (वाक्यदैर्घ्यम्((bp)->str) != (bp)->len) {                                  \
        प्रारूप_लिख("strlen of AVBPrint-string returned by "#func_name"_bprint" \
               " differs from AVBPrint.len: %zu vs. %u\n",                 \
               वाक्यदैर्घ्यम्((bp)->str), (bp)->len);                              \
        भङ्ग;                                                             \
    }                                                                      \
    आकार = func_name(ORD_तर्काः ## ARG_क्रमः(रिक्त, 0, __VA_ARGS__));         \
    यदि (आकार <= 0) {                                                       \
        प्रारूप_लिख(#func_name " returned %d\n", आकार);                         \
        भङ्ग;                                                             \
    }                                                                      \
    यदि ((bp)->len != आकार - 1) {                                           \
        प्रारूप_लिख("Return value %d of " #func_name " inconsistent with length"\
               " %u obtained from corresponding bprint version\n",         \
               आकार, (bp)->len);                                           \
        भङ्ग;                                                             \
    }                                                                      \
    str = av_malloc(आकार);                                                 \
    यदि (!str) {                                                            \
        प्रारूप_लिख("string of size %d could not be allocated.\n", आकार);       \
        भङ्ग;                                                             \
    }                                                                      \
    आकार = func_name(ORD_तर्काः ## ARG_क्रमः(str, आकार, __VA_ARGS__));       \
    यदि (आकार <= 0 || (bp)->len != आकार - 1) {                              \
        प्रारूप_लिख("Return value %d of " #func_name " inconsistent with length"\
               " %d obtained in first pass.\n", आकार, (bp)->len);          \
        av_free(str);                                                      \
        भङ्ग;                                                             \
    }                                                                      \
    यदि (वाक्यं_तुलय(str, (bp)->str)) {                                          \
        प्रारूप_लिख("Ordinary and _bprint versions of "#func_name" disagree: "  \
               "'%s' vs. '%s'\n", str, (bp)->str);                         \
        av_free(str);                                                      \
        भङ्ग;                                                             \
    }                                                                      \
    av_free(str);                                                          \
    } यावत् (0)


स्थिर शून्य channel_name(AVBPrint *bp, गणना AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_name, 1, channel);
}

स्थिर शून्य channel_description(AVBPrint *bp, गणना AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_description, 1, channel);
}

स्थिर शून्य channel_layout_from_आवरणम्(AVChannelLayout *layout,
                                     AVBPrint *bp, uint64_t channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    यदि (!av_channel_layout_from_आवरणम्(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    अन्यथा
        av_bprintf(bp, "fail");
}

स्थिर शून्य channel_layout_from_string(AVChannelLayout *layout,
                                       AVBPrint *bp, ध्रुव वर्ण *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    यदि (!av_channel_layout_from_string(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    अन्यथा
        av_bprintf(bp, "fail");
}

स्थिर ध्रुव वर्ण* channel_क्रमः_नामानि[]  = {"UNSPEC", "NATIVE", "CUSTOM", "AMBI"};

स्थिर शून्य describe_type(AVBPrint *bp, AVChannelLayout *layout)
{
    यदि ((अचिह्नित)layout->क्रमः < FF_ARRAY_ELEMS(channel_क्रमः_नामानि)) {
        av_bprintf(bp, "%-6s (", channel_क्रमः_नामानि[layout->क्रमः]);
        av_channel_layout_describe_bprint(layout, bp);
        av_bprintf(bp, ")");
    } अन्यथा {
        av_bprintf(bp, "???");
    }
}

स्थिर ध्रुव वर्ण *channel_layout_retype(AVChannelLayout *layout, AVBPrint *bp, ध्रुव वर्ण *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    यदि (!av_channel_layout_from_string(layout, channel_layout) &&
        av_channel_layout_check(layout)) {
        describe_type(bp, layout);
        प्रति (पूर्णाङ्क i = 0; i < FF_CHANNEL_क्रमः_NB; i++) {
            पूर्णाङ्क ret;
            AVChannelLayout copy = {0};
            av_bprintf(bp, "\n ");
            यदि (av_channel_layout_copy(&copy, layout) < 0)
                प्रत्यागम "nomem";
            ret = av_channel_layout_retype(&copy, i, 0);
            यदि (ret < 0 && (copy.क्रमः != layout->क्रमः || av_channel_layout_compare(&copy, layout)))
                av_bprintf(bp, "failed to keep existing layout on failure");
            यदि (ret >= 0 && copy.क्रमः != i)
                av_bprintf(bp, "returned success but did not change order");
            यदि (ret == AVERROR(ENOSYS)) {
                av_bprintf(bp, " != %s", channel_क्रमः_नामानि[i]);
            } अन्यथा यदि (ret < 0) {
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
    प्रत्यागम bp->str;
}

#परिभाषय CHANNEL_NAME(x)                                                    \
    channel_name(&bp, (x));                                                \
    प्रारूप_लिख("With %-32s %14s\n", AV_STRINGIFY(x)":", bp.str)

#परिभाषय CHANNEL_DESCRIPTION(x)                                             \
    channel_description(&bp, (x));                                         \
    प्रारूप_लिख("With %-23s %23s\n", AV_STRINGIFY(x)":", bp.str);

#परिभाषय CHANNEL_FROM_STRING(x)                                             \
    प्रारूप_लिख("With %-38s %8d\n", AV_STRINGIFY(x)":", av_channel_from_string(x))

#परिभाषय CHANNEL_LAYOUT_FROM_आवरणम्(x)                                        \
    channel_layout_from_आवरणम्(&layout, &bp, (x));

#परिभाषय CHANNEL_LAYOUT_FROM_STRING(x)                                      \
    channel_layout_from_string(&layout, &bp, (x));                         \
    प्रारूप_लिख("With \"%s\":%*s %32s\n", x, वाक्यदैर्घ्यम्(x) > 32 ? 0 : 32 - (पूर्णाङ्क)वाक्यदैर्घ्यम्(x), "", bp.str);

#परिभाषय CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(l, x)                            \
    ret = av_channel_layout_channel_from_सूचकांक(&layout, x);                \
    यदि (ret < 0)                                                           \
        ret = -1;                                                          \
    प्रारूप_लिख("On \"%s\" layout with %2d: %8d\n", l,  x, ret)

#परिभाषय CHANNEL_LAYOUT_SUBSET(l, xstr, x)                                  \
    आवरणम्_2 = av_channel_layout_subset(&layout, x);                           \
    प्रारूप_लिख("On \"%s\" layout with %-22s 0x%"PRIx64"\n", l, xstr, आवरणम्_2)

#परिभाषय CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(l, x)                            \
    ret = av_channel_layout_सूचकांक_from_channel(&layout, x);                \
    यदि (ret < 0)                                                           \
        ret = -1;                                                          \
    प्रारूप_लिख("On \"%s\" layout with %-23s %3d\n", l, AV_STRINGIFY(x)":", ret)

#परिभाषय CHANNEL_LAYOUT_CHANNEL_FROM_STRING(l, x)                           \
    ret = av_channel_layout_channel_from_string(&layout, x);               \
    यदि (ret < 0)                                                           \
        ret = -1;                                                          \
    प्रारूप_लिख("On \"%s\" layout with %-21s %3d\n", bp.str, AV_STRINGIFY(x)":", ret);

#परिभाषय CHANNEL_LAYOUT_सूचकांक_FROM_STRING(l, x)                             \
    ret = av_channel_layout_सूचकांक_from_string(&layout, x);                 \
    यदि (ret < 0)                                                           \
        ret = -1;                                                          \
    प्रारूप_लिख("On \"%s\" layout with %-20s %3d\n", l, AV_STRINGIFY(x)":", ret);

पूर्णाङ्क मुख्यम्(शून्य)
{
    ध्रुव AVChannelLayout *playout;
    AVChannelLayout layout = { 0 }, layout2 = { 0 };
    AVBPrint bp;
    शून्य *iter = रिक्त;
    uint64_t आवरणम्_2;
    पूर्णाङ्क ret;

    av_bprint_init(&bp, 64, AV_BPRINT_आकार_AUTOMATIC);

    प्रारूप_लिख("Testing av_channel_layout_standard\n");
    यावत् (playout = av_channel_layout_standard(&iter)) {
        av_channel_layout_describe_bprint(playout, &bp);
        प्रारूप_लिख("%-14s ", bp.str);
        av_bprint_clear(&bp);
        प्रति (पूर्णाङ्क i = 0; i < 63; i++) {
            पूर्णाङ्क idx = av_channel_layout_सूचकांक_from_channel(playout, i);
            यदि (idx >= 0) {
                यदि (idx)
                    av_bprintf(&bp, "+");
                av_channel_name_bprint(&bp, i);
            }
        }
        प्रारूप_लिख("%s\n", bp.str);
        av_bprint_clear(&bp);
    }

    प्रारूप_लिख("\nTesting av_channel_name\n");
    CHANNEL_NAME(AV_CHAN_FRONT_वामः);
    CHANNEL_NAME(AV_CHAN_FRONT_दक्षिणः);
    CHANNEL_NAME(63);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_आधारः);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_अन्तः);

    प्रारूप_लिख("Testing av_channel_description\n");
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_वामः);
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_दक्षिणः);
    CHANNEL_DESCRIPTION(63);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_आधारः);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_अन्तः);

    प्रारूप_लिख("\nTesting av_channel_from_string\n");
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

    प्रारूप_लिख("\n==Native layouts==\n");

    प्रारूप_लिख("\nTesting av_channel_layout_from_string\n");
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

    प्रारूप_लिख("\nTesting av_channel_layout_from_mask\n");
    CHANNEL_LAYOUT_FROM_आवरणम्(AV_CH_LAYOUT_5POINT1);
    प्रारूप_लिख("With AV_CH_LAYOUT_5POINT1: %25s\n", bp.str);

    प्रारूप_लिख("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 3);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 4);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 5);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 6);

    प्रारूप_लिख("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_वामः);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_दक्षिणः);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_CENTER);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_नीचः_FREQUENCY);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_वामः);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_दक्षिणः);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_पृष्ठभागः_CENTER);

    प्रारूप_लिख("\nTesting av_channel_layout_channel_from_string\n");
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

    प्रारूप_लिख("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FC");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "LFE");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "SL");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "SR");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "BC");

    प्रारूप_लिख("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:",  AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_2POINT1:", AV_CH_LAYOUT_2POINT1);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_4POINT1:", AV_CH_LAYOUT_4POINT1);

    प्रारूप_लिख("\n==Custom layouts==\n");

    प्रारूप_लिख("\nTesting av_channel_layout_from_string\n");
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
    यदि (ret < 0) {
        प्रारूप_लिख("Copying channel layout \"FR+FL@Foo+USR63@Foo\" failed; "
               "ret %d\n", ret);
    }
    ret = av_channel_layout_compare(&layout, &layout2);
    यदि (ret)
        प्रारूप_लिख("Channel layout and its copy compare unequal; ret: %d\n", ret);

    प्रारूप_लिख("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_सूचकांक_FROM_STRING(bp.str, "BC");

    प्रारूप_लिख("\nTesting av_channel_layout_channel_from_string\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "BC");

    प्रारूप_लिख("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_दक्षिणः);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_वामः);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, 63);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_पृष्ठभागः_CENTER);

    प्रारूप_लिख("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 3);

    प्रारूप_लिख("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    प्रारूप_लिख("\n==Ambisonic layouts==\n");

    प्रारूप_लिख("\nTesting av_channel_layout_from_string\n");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 1");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 2+stereo");

    प्रारूप_लिख("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_AMBISONIC_आधारः);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_वामः);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_दक्षिणः);
    CHANNEL_LAYOUT_सूचकांक_FROM_CHANNEL(bp.str, AV_CHAN_पृष्ठभागः_CENTER);

    प्रारूप_लिख("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 9);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 10);
    CHANNEL_LAYOUT_CHANNEL_FROM_सूचकांक(bp.str, 11);

    प्रारूप_लिख("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    av_channel_layout_uninit(&layout);
    av_channel_layout_uninit(&layout2);

    प्रारूप_लिख("\nTesting av_channel_layout_retype\n");
    {
        ध्रुव वर्ण* layouts[] = {
            "FL@Boo",
            "stereo",
            "FR+FL",
            "ambisonic 2+stereo",
            "2C",
            रिक्त
        };
        प्रति (पूर्णाङ्क i = 0; layouts[i]; i++)
            प्रारूप_लिख("With \"%s\": %s\n", layouts[i], channel_layout_retype(&layout, &bp, layouts[i]));
    }
    av_bprint_finalize(&bp, रिक्त);

    प्रत्यागम 0;
}
