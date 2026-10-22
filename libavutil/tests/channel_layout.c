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

#ଅନ୍ତର୍ଭାଵ <inttypes.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "libavutil/bprint.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/channel_layout.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/error.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/macros.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/mem.h"

#define BPRINT_ARGS1(bp, ...)     (bp), __VA_ARGS__
#define BPRINT_ARGS0(bp, ...)     __VA_ARGS__, (bp)
#define ORD_ARGS1(str, size, ...) (str), (size), __VA_ARGS__
#define ORD_ARGS0(str, size, ...) __VA_ARGS__, (str), (size)

// This macro presumes the AVBPrint to have been cleared before usage.
#define CMP_BPRINT_AND_NONBPRINT(bp, func_name, ARG_ORDER, ...) କର {       \
    ଅକ୍ଷର *str;                                                             \
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା size;                                                              \
    func_name ## _bprint(BPRINT_ARGS ## ARG_ORDER((bp), __VA_ARGS__));     \
    ଯଦି (strlen((bp)->str) != (bp)->len) {                                  \
        printf("strlen of AVBPrint-string returned by "#func_name"_bprint" \
               " differs from AVBPrint.len: %zu vs. %u\n",                 \
               strlen((bp)->str), (bp)->len);                              \
        ଭାଙ୍ଗ;                                                             \
    }                                                                      \
    size = func_name(ORD_ARGS ## ARG_ORDER(ଖାଲି, 0, __VA_ARGS__));         \
    ଯଦି (size <= 0) {                                                       \
        printf(#func_name " returned %d\n", size);                         \
        ଭାଙ୍ଗ;                                                             \
    }                                                                      \
    ଯଦି ((bp)->len != size - 1) {                                           \
        printf("Return value %d of " #func_name " inconsistent with length"\
               " %u obtained from corresponding bprint version\n",         \
               size, (bp)->len);                                           \
        ଭାଙ୍ଗ;                                                             \
    }                                                                      \
    str = av_malloc(size);                                                 \
    ଯଦି (!str) {                                                            \
        printf("string of size %d could not be allocated.\n", size);       \
        ଭାଙ୍ଗ;                                                             \
    }                                                                      \
    size = func_name(ORD_ARGS ## ARG_ORDER(str, size, __VA_ARGS__));       \
    ଯଦି (size <= 0 || (bp)->len != size - 1) {                              \
        printf("Return value %d of " #func_name " inconsistent with length"\
               " %d obtained in first pass.\n", size, (bp)->len);          \
        av_free(str);                                                      \
        ଭାଙ୍ଗ;                                                             \
    }                                                                      \
    ଯଦି (strcmp(str, (bp)->str)) {                                          \
        printf("Ordinary and _bprint versions of "#func_name" disagree: "  \
               "'%s' vs. '%s'\n", str, (bp)->str);                         \
        av_free(str);                                                      \
        ଭାଙ୍ଗ;                                                             \
    }                                                                      \
    av_free(str);                                                          \
    } ଯେତେବେଳେ (0)


ସ୍ଥିର ଶୂନ୍ୟ channel_name(AVBPrint *bp, ଗଣନା AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_name, 1, channel);
}

ସ୍ଥିର ଶୂନ୍ୟ channel_description(AVBPrint *bp, ଗଣନା AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_description, 1, channel);
}

ସ୍ଥିର ଶୂନ୍ୟ channel_layout_from_mask(AVChannelLayout *layout,
                                     AVBPrint *bp, uint64_t channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    ଯଦି (!av_channel_layout_from_mask(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    ଅନ୍ୟଥା
        av_bprintf(bp, "fail");
}

ସ୍ଥିର ଶୂନ୍ୟ channel_layout_from_string(AVChannelLayout *layout,
                                       AVBPrint *bp, ଅଚଳ ଅକ୍ଷର *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    ଯଦି (!av_channel_layout_from_string(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    ଅନ୍ୟଥା
        av_bprintf(bp, "fail");
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର* channel_order_names[]  = {"UNSPEC", "NATIVE", "CUSTOM", "AMBI"};

ସ୍ଥିର ଶୂନ୍ୟ describe_type(AVBPrint *bp, AVChannelLayout *layout)
{
    ଯଦି ((unsigned)layout->order < FF_ARRAY_ELEMS(channel_order_names)) {
        av_bprintf(bp, "%-6s (", channel_order_names[layout->order]);
        av_channel_layout_describe_bprint(layout, bp);
        av_bprintf(bp, ")");
    } ଅନ୍ୟଥା {
        av_bprintf(bp, "???");
    }
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *channel_layout_retype(AVChannelLayout *layout, AVBPrint *bp, ଅଚଳ ଅକ୍ଷର *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    ଯଦି (!av_channel_layout_from_string(layout, channel_layout) &&
        av_channel_layout_check(layout)) {
        describe_type(bp, layout);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_CHANNEL_ORDER_NB; i++) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
            AVChannelLayout copy = {0};
            av_bprintf(bp, "\n ");
            ଯଦି (av_channel_layout_copy(&copy, layout) < 0)
                ଫେରନ୍ତୁ "nomem";
            ret = av_channel_layout_retype(&copy, i, 0);
            ଯଦି (ret < 0 && (copy.order != layout->order || av_channel_layout_compare(&copy, layout)))
                av_bprintf(bp, "failed to keep existing layout on failure");
            ଯଦି (ret >= 0 && copy.order != i)
                av_bprintf(bp, "returned success but did not change order");
            ଯଦି (ret == AVERROR(ENOSYS)) {
                av_bprintf(bp, " != %s", channel_order_names[i]);
            } ଅନ୍ୟଥା ଯଦି (ret < 0) {
                av_bprintf(bp, "FAIL");
            } ଅନ୍ୟଥା {
                av_bprintf(bp, " %s ", ret ? "~~" : "==");
                describe_type(bp, &copy);
            }
            av_channel_layout_uninit(&copy);
        }
    } ଅନ୍ୟଥା {
        av_bprintf(bp, "fail");
    }
    ଫେରନ୍ତୁ bp->str;
}

#define CHANNEL_NAME(x)                                                    \
    channel_name(&bp, (x));                                                \
    printf("With %-32s %14s\n", AV_STRINGIFY(x)":", bp.str)

#define CHANNEL_DESCRIPTION(x)                                             \
    channel_description(&bp, (x));                                         \
    printf("With %-23s %23s\n", AV_STRINGIFY(x)":", bp.str);

#define CHANNEL_FROM_STRING(x)                                             \
    printf("With %-38s %8d\n", AV_STRINGIFY(x)":", av_channel_from_string(x))

#define CHANNEL_LAYOUT_FROM_MASK(x)                                        \
    channel_layout_from_mask(&layout, &bp, (x));

#define CHANNEL_LAYOUT_FROM_STRING(x)                                      \
    channel_layout_from_string(&layout, &bp, (x));                         \
    printf("With \"%s\":%*s %32s\n", x, strlen(x) > 32 ? 0 : 32 - (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)strlen(x), "", bp.str);

#define CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(l, x)                            \
    ret = av_channel_layout_channel_from_index(&layout, x);                \
    ଯଦି (ret < 0)                                                           \
        ret = -1;                                                          \
    printf("On \"%s\" layout with %2d: %8d\n", l,  x, ret)

#define CHANNEL_LAYOUT_SUBSET(l, xstr, x)                                  \
    mask = av_channel_layout_subset(&layout, x);                           \
    printf("On \"%s\" layout with %-22s 0x%"PRIx64"\n", l, xstr, mask)

#define CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(l, x)                            \
    ret = av_channel_layout_index_from_channel(&layout, x);                \
    ଯଦି (ret < 0)                                                           \
        ret = -1;                                                          \
    printf("On \"%s\" layout with %-23s %3d\n", l, AV_STRINGIFY(x)":", ret)

#define CHANNEL_LAYOUT_CHANNEL_FROM_STRING(l, x)                           \
    ret = av_channel_layout_channel_from_string(&layout, x);               \
    ଯଦି (ret < 0)                                                           \
        ret = -1;                                                          \
    printf("On \"%s\" layout with %-21s %3d\n", bp.str, AV_STRINGIFY(x)":", ret);

#define CHANNEL_LAYOUT_INDEX_FROM_STRING(l, x)                             \
    ret = av_channel_layout_index_from_string(&layout, x);                 \
    ଯଦି (ret < 0)                                                           \
        ret = -1;                                                          \
    printf("On \"%s\" layout with %-20s %3d\n", l, AV_STRINGIFY(x)":", ret);

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ଶୂନ୍ୟ)
{
    ଅଚଳ AVChannelLayout *playout;
    AVChannelLayout layout = { 0 }, layout2 = { 0 };
    AVBPrint bp;
    ଶୂନ୍ୟ *iter = ଖାଲି;
    uint64_t mask;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    av_bprint_init(&bp, 64, AV_BPRINT_SIZE_AUTOMATIC);

    printf("Testing av_channel_layout_standard\n");
    ଯେତେବେଳେ (playout = av_channel_layout_standard(&iter)) {
        av_channel_layout_describe_bprint(playout, &bp);
        printf("%-14s ", bp.str);
        av_bprint_clear(&bp);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 63; i++) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା idx = av_channel_layout_index_from_channel(playout, i);
            ଯଦି (idx >= 0) {
                ଯଦି (idx)
                    av_bprintf(&bp, "+");
                av_channel_name_bprint(&bp, i);
            }
        }
        printf("%s\n", bp.str);
        av_bprint_clear(&bp);
    }

    printf("\nTesting av_channel_name\n");
    CHANNEL_NAME(AV_CHAN_FRONT_ବାମ);
    CHANNEL_NAME(AV_CHAN_FRONT_ଡାହାଣ);
    CHANNEL_NAME(63);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_BASE);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_END);

    printf("Testing av_channel_description\n");
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_ବାମ);
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_ଡାହାଣ);
    CHANNEL_DESCRIPTION(63);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_BASE);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_END);

    printf("\nTesting av_channel_from_string\n");
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

    printf("\n==Native layouts==\n");

    printf("\nTesting av_channel_layout_from_string\n");
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

    printf("\nTesting av_channel_layout_from_mask\n");
    CHANNEL_LAYOUT_FROM_MASK(AV_CH_LAYOUT_5POINT1);
    printf("With AV_CH_LAYOUT_5POINT1: %25s\n", bp.str);

    printf("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 3);
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 4);
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 5);
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 6);

    printf("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ବାମ);
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ଡାହାଣ);
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_CENTER);
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_ତଳ_FREQUENCY);
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_ବାମ);
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_ଡାହାଣ);
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_BACK_CENTER);

    printf("\nTesting av_channel_layout_channel_from_string\n");
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

    printf("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "FC");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "LFE");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "SL");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "SR");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "BC");

    printf("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:",  AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_2POINT1:", AV_CH_LAYOUT_2POINT1);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_4POINT1:", AV_CH_LAYOUT_4POINT1);

    printf("\n==Custom layouts==\n");

    printf("\nTesting av_channel_layout_from_string\n");
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
    ଯଦି (ret < 0) {
        printf("Copying channel layout \"FR+FL@Foo+USR63@Foo\" failed; "
               "ret %d\n", ret);
    }
    ret = av_channel_layout_compare(&layout, &layout2);
    ଯଦି (ret)
        printf("Channel layout and its copy compare unequal; ret: %d\n", ret);

    printf("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_INDEX_FROM_STRING(bp.str, "BC");

    printf("\nTesting av_channel_layout_channel_from_string\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "BC");

    printf("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ଡାହାଣ);
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ବାମ);
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, 63);
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_BACK_CENTER);

    printf("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 3);

    printf("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    printf("\n==Ambisonic layouts==\n");

    printf("\nTesting av_channel_layout_from_string\n");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 1");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 2+stereo");

    printf("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_AMBISONIC_BASE);
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ବାମ);
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ଡାହାଣ);
    CHANNEL_LAYOUT_INDEX_FROM_CHANNEL(bp.str, AV_CHAN_BACK_CENTER);

    printf("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 9);
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 10);
    CHANNEL_LAYOUT_CHANNEL_FROM_INDEX(bp.str, 11);

    printf("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    av_channel_layout_uninit(&layout);
    av_channel_layout_uninit(&layout2);

    printf("\nTesting av_channel_layout_retype\n");
    {
        ଅଚଳ ଅକ୍ଷର* layouts[] = {
            "FL@Boo",
            "stereo",
            "FR+FL",
            "ambisonic 2+stereo",
            "2C",
            ଖାଲି
        };
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; layouts[i]; i++)
            printf("With \"%s\": %s\n", layouts[i], channel_layout_retype(&layout, &bp, layouts[i]));
    }
    av_bprint_finalize(&bp, ଖାଲି);

    ଫେରନ୍ତୁ 0;
}
