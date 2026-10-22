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

#అన్తర్భావ <inttypes.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/bprint.h"
#అన్తర్భావ "libavutil/channel_layout.h"
#అన్తర్భావ "libavutil/error.h"
#అన్తర్భావ "libavutil/macros.h"
#అన్తర్భావ "libavutil/mem.h"

#నిర్వచించు BPRINT_ARGS1(bp, ...)     (bp), __VA_ARGS__
#నిర్వచించు BPRINT_ARGS0(bp, ...)     __VA_ARGS__, (bp)
#నిర్వచించు ORD_ARGS1(str, కొలత, ...) (str), (కొలత), __VA_ARGS__
#నిర్వచించు ORD_ARGS0(str, కొలత, ...) __VA_ARGS__, (str), (కొలత)

// This macro presumes the AVBPrint to have been cleared before usage.
#నిర్వచించు CMP_BPRINT_AND_NONBPRINT(bp, func_name, ARG_క్రమం, ...) చేయి {       \
    అక్షరం *str;                                                             \
    పూర్ణాంకం కొలత;                                                              \
    func_name ## _bprint(BPRINT_వాదనలు ## ARG_క్రమం((bp), __VA_ARGS__));     \
    ఒకవేళ (అక్షరశ్రేణి_పొడవు((bp)->str) != (bp)->len) {                                  \
        రాయి("strlen of AVBPrint-string returned by "#func_name"_bprint" \
               " differs from AVBPrint.len: %zu vs. %u\n",                 \
               అక్షరశ్రేణి_పొడవు((bp)->str), (bp)->len);                              \
        ఆపు;                                                             \
    }                                                                      \
    కొలత = func_name(ORD_వాదనలు ## ARG_క్రమం(ఖాళీ, 0, __VA_ARGS__));         \
    ఒకవేళ (కొలత <= 0) {                                                       \
        రాయి(#func_name " returned %d\n", కొలత);                         \
        ఆపు;                                                             \
    }                                                                      \
    ఒకవేళ ((bp)->len != కొలత - 1) {                                           \
        రాయి("Return value %d of " #func_name " inconsistent with length"\
               " %u obtained from corresponding bprint version\n",         \
               కొలత, (bp)->len);                                           \
        ఆపు;                                                             \
    }                                                                      \
    str = av_malloc(కొలత);                                                 \
    ఒకవేళ (!str) {                                                            \
        రాయి("string of size %d could not be allocated.\n", కొలత);       \
        ఆపు;                                                             \
    }                                                                      \
    కొలత = func_name(ORD_వాదనలు ## ARG_క్రమం(str, కొలత, __VA_ARGS__));       \
    ఒకవేళ (కొలత <= 0 || (bp)->len != కొలత - 1) {                              \
        రాయి("Return value %d of " #func_name " inconsistent with length"\
               " %d obtained in first pass.\n", కొలత, (bp)->len);          \
        av_free(str);                                                      \
        ఆపు;                                                             \
    }                                                                      \
    ఒకవేళ (strcmp(str, (bp)->str)) {                                          \
        రాయి("Ordinary and _bprint versions of "#func_name" disagree: "  \
               "'%s' vs. '%s'\n", str, (bp)->str);                         \
        av_free(str);                                                      \
        ఆపు;                                                             \
    }                                                                      \
    av_free(str);                                                          \
    } అయితే (0)


స్థిర శూన్య channel_name(AVBPrint *bp, గణన AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_name, 1, channel);
}

స్థిర శూన్య channel_description(AVBPrint *bp, గణన AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_description, 1, channel);
}

స్థిర శూన్య channel_layout_from_ముసుగు(AVChannelLayout *layout,
                                     AVBPrint *bp, uint64_t channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    ఒకవేళ (!av_channel_layout_from_ముసుగు(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    లేకపోతే
        av_bprintf(bp, "fail");
}

స్థిర శూన్య channel_layout_from_string(AVChannelLayout *layout,
                                       AVBPrint *bp, స్థిరరాశి అక్షరం *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    ఒకవేళ (!av_channel_layout_from_string(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    లేకపోతే
        av_bprintf(bp, "fail");
}

స్థిర స్థిరరాశి అక్షరం* channel_క్రమం_పేర్లు[]  = {"UNSPEC", "NATIVE", "CUSTOM", "AMBI"};

స్థిర శూన్య describe_type(AVBPrint *bp, AVChannelLayout *layout)
{
    ఒకవేళ ((గుర్తులేని)layout->క్రమం < FF_ARRAY_ELEMS(channel_క్రమం_పేర్లు)) {
        av_bprintf(bp, "%-6s (", channel_క్రమం_పేర్లు[layout->క్రమం]);
        av_channel_layout_describe_bprint(layout, bp);
        av_bprintf(bp, ")");
    } లేకపోతే {
        av_bprintf(bp, "???");
    }
}

స్థిర స్థిరరాశి అక్షరం *channel_layout_retype(AVChannelLayout *layout, AVBPrint *bp, స్థిరరాశి అక్షరం *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    ఒకవేళ (!av_channel_layout_from_string(layout, channel_layout) &&
        av_channel_layout_check(layout)) {
        describe_type(bp, layout);
        కొరకు (పూర్ణాంకం i = 0; i < FF_CHANNEL_క్రమం_NB; i++) {
            పూర్ణాంకం ret;
            AVChannelLayout copy = {0};
            av_bprintf(bp, "\n ");
            ఒకవేళ (av_channel_layout_copy(&copy, layout) < 0)
                తిరిగి "nomem";
            ret = av_channel_layout_retype(&copy, i, 0);
            ఒకవేళ (ret < 0 && (copy.క్రమం != layout->క్రమం || av_channel_layout_compare(&copy, layout)))
                av_bprintf(bp, "failed to keep existing layout on failure");
            ఒకవేళ (ret >= 0 && copy.క్రమం != i)
                av_bprintf(bp, "returned success but did not change order");
            ఒకవేళ (ret == AVERROR(ENOSYS)) {
                av_bprintf(bp, " != %s", channel_క్రమం_పేర్లు[i]);
            } లేకపోతే ఒకవేళ (ret < 0) {
                av_bprintf(bp, "FAIL");
            } లేకపోతే {
                av_bprintf(bp, " %s ", ret ? "~~" : "==");
                describe_type(bp, &copy);
            }
            av_channel_layout_uninit(&copy);
        }
    } లేకపోతే {
        av_bprintf(bp, "fail");
    }
    తిరిగి bp->str;
}

#నిర్వచించు CHANNEL_NAME(x)                                                    \
    channel_name(&bp, (x));                                                \
    రాయి("With %-32s %14s\n", AV_STRINGIFY(x)":", bp.str)

#నిర్వచించు CHANNEL_DESCRIPTION(x)                                             \
    channel_description(&bp, (x));                                         \
    రాయి("With %-23s %23s\n", AV_STRINGIFY(x)":", bp.str);

#నిర్వచించు CHANNEL_FROM_STRING(x)                                             \
    రాయి("With %-38s %8d\n", AV_STRINGIFY(x)":", av_channel_from_string(x))

#నిర్వచించు CHANNEL_LAYOUT_FROM_ముసుగు(x)                                        \
    channel_layout_from_ముసుగు(&layout, &bp, (x));

#నిర్వచించు CHANNEL_LAYOUT_FROM_STRING(x)                                      \
    channel_layout_from_string(&layout, &bp, (x));                         \
    రాయి("With \"%s\":%*s %32s\n", x, అక్షరశ్రేణి_పొడవు(x) > 32 ? 0 : 32 - (పూర్ణాంకం)అక్షరశ్రేణి_పొడవు(x), "", bp.str);

#నిర్వచించు CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(l, x)                            \
    ret = av_channel_layout_channel_from_సూచీ(&layout, x);                \
    ఒకవేళ (ret < 0)                                                           \
        ret = -1;                                                          \
    రాయి("On \"%s\" layout with %2d: %8d\n", l,  x, ret)

#నిర్వచించు CHANNEL_LAYOUT_SUBSET(l, xstr, x)                                  \
    ముసుగు_2 = av_channel_layout_subset(&layout, x);                           \
    రాయి("On \"%s\" layout with %-22s 0x%"PRIx64"\n", l, xstr, ముసుగు_2)

#నిర్వచించు CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(l, x)                            \
    ret = av_channel_layout_సూచీ_from_channel(&layout, x);                \
    ఒకవేళ (ret < 0)                                                           \
        ret = -1;                                                          \
    రాయి("On \"%s\" layout with %-23s %3d\n", l, AV_STRINGIFY(x)":", ret)

#నిర్వచించు CHANNEL_LAYOUT_CHANNEL_FROM_STRING(l, x)                           \
    ret = av_channel_layout_channel_from_string(&layout, x);               \
    ఒకవేళ (ret < 0)                                                           \
        ret = -1;                                                          \
    రాయి("On \"%s\" layout with %-21s %3d\n", bp.str, AV_STRINGIFY(x)":", ret);

#నిర్వచించు CHANNEL_LAYOUT_సూచీ_FROM_STRING(l, x)                             \
    ret = av_channel_layout_సూచీ_from_string(&layout, x);                 \
    ఒకవేళ (ret < 0)                                                           \
        ret = -1;                                                          \
    రాయి("On \"%s\" layout with %-20s %3d\n", l, AV_STRINGIFY(x)":", ret);

పూర్ణాంకం ప్రధాన(శూన్య)
{
    స్థిరరాశి AVChannelLayout *playout;
    AVChannelLayout layout = { 0 }, layout2 = { 0 };
    AVBPrint bp;
    శూన్య *iter = ఖాళీ;
    uint64_t ముసుగు_2;
    పూర్ణాంకం ret;

    av_bprint_init(&bp, 64, AV_BPRINT_కొలత_AUTOMATIC);

    రాయి("Testing av_channel_layout_standard\n");
    అయితే (playout = av_channel_layout_standard(&iter)) {
        av_channel_layout_describe_bprint(playout, &bp);
        రాయి("%-14s ", bp.str);
        av_bprint_clear(&bp);
        కొరకు (పూర్ణాంకం i = 0; i < 63; i++) {
            పూర్ణాంకం idx = av_channel_layout_సూచీ_from_channel(playout, i);
            ఒకవేళ (idx >= 0) {
                ఒకవేళ (idx)
                    av_bprintf(&bp, "+");
                av_channel_name_bprint(&bp, i);
            }
        }
        రాయి("%s\n", bp.str);
        av_bprint_clear(&bp);
    }

    రాయి("\nTesting av_channel_name\n");
    CHANNEL_NAME(AV_CHAN_FRONT_ఎడమ);
    CHANNEL_NAME(AV_CHAN_FRONT_కుడి);
    CHANNEL_NAME(63);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_పునాది);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_చివర);

    రాయి("Testing av_channel_description\n");
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_ఎడమ);
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_కుడి);
    CHANNEL_DESCRIPTION(63);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_పునాది);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_చివర);

    రాయి("\nTesting av_channel_from_string\n");
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

    రాయి("\n==Native layouts==\n");

    రాయి("\nTesting av_channel_layout_from_string\n");
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

    రాయి("\nTesting av_channel_layout_from_mask\n");
    CHANNEL_LAYOUT_FROM_ముసుగు(AV_CH_LAYOUT_5POINT1);
    రాయి("With AV_CH_LAYOUT_5POINT1: %25s\n", bp.str);

    రాయి("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 3);
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 4);
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 5);
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 6);

    రాయి("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ఎడమ);
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_కుడి);
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_CENTER);
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_దిగువ_FREQUENCY);
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_ఎడమ);
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_కుడి);
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_వెనుక_CENTER);

    రాయి("\nTesting av_channel_layout_channel_from_string\n");
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

    రాయి("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "FC");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "LFE");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "SL");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "SR");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "BC");

    రాయి("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:",  AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_2POINT1:", AV_CH_LAYOUT_2POINT1);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_4POINT1:", AV_CH_LAYOUT_4POINT1);

    రాయి("\n==Custom layouts==\n");

    రాయి("\nTesting av_channel_layout_from_string\n");
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
    ఒకవేళ (ret < 0) {
        రాయి("Copying channel layout \"FR+FL@Foo+USR63@Foo\" failed; "
               "ret %d\n", ret);
    }
    ret = av_channel_layout_compare(&layout, &layout2);
    ఒకవేళ (ret)
        రాయి("Channel layout and its copy compare unequal; ret: %d\n", ret);

    రాయి("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_సూచీ_FROM_STRING(bp.str, "BC");

    రాయి("\nTesting av_channel_layout_channel_from_string\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "BC");

    రాయి("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_కుడి);
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ఎడమ);
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, 63);
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_వెనుక_CENTER);

    రాయి("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 3);

    రాయి("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    రాయి("\n==Ambisonic layouts==\n");

    రాయి("\nTesting av_channel_layout_from_string\n");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 1");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 2+stereo");

    రాయి("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_AMBISONIC_పునాది);
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ఎడమ);
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_కుడి);
    CHANNEL_LAYOUT_సూచీ_FROM_CHANNEL(bp.str, AV_CHAN_వెనుక_CENTER);

    రాయి("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 9);
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 10);
    CHANNEL_LAYOUT_CHANNEL_FROM_సూచీ(bp.str, 11);

    రాయి("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    av_channel_layout_uninit(&layout);
    av_channel_layout_uninit(&layout2);

    రాయి("\nTesting av_channel_layout_retype\n");
    {
        స్థిరరాశి అక్షరం* layouts[] = {
            "FL@Boo",
            "stereo",
            "FR+FL",
            "ambisonic 2+stereo",
            "2C",
            ఖాళీ
        };
        కొరకు (పూర్ణాంకం i = 0; layouts[i]; i++)
            రాయి("With \"%s\": %s\n", layouts[i], channel_layout_retype(&layout, &bp, layouts[i]));
    }
    av_bprint_finalize(&bp, ఖాళీ);

    తిరిగి 0;
}
