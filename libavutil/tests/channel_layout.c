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

#ಅನ್ತರ್ಭಾವ <inttypes.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/bprint.h"
#ಅನ್ತರ್ಭಾವ "libavutil/channel_layout.h"
#ಅನ್ತರ್ಭಾವ "libavutil/error.h"
#ಅನ್ತರ್ಭಾವ "libavutil/macros.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

#ವ್ಯಾಖ್ಯಾನಿಸು BPRINT_ARGS1(bp, ...)     (bp), __VA_ARGS__
#ವ್ಯಾಖ್ಯಾನಿಸು BPRINT_ARGS0(bp, ...)     __VA_ARGS__, (bp)
#ವ್ಯಾಖ್ಯಾನಿಸು ORD_ARGS1(str, ಗಾತ್ರ_2, ...) (str), (ಗಾತ್ರ_2), __VA_ARGS__
#ವ್ಯಾಖ್ಯಾನಿಸು ORD_ARGS0(str, ಗಾತ್ರ_2, ...) __VA_ARGS__, (str), (ಗಾತ್ರ_2)

// This macro presumes the AVBPrint to have been cleared before usage.
#ವ್ಯಾಖ್ಯಾನಿಸು CMP_BPRINT_AND_NONBPRINT(bp, func_name, ARG_ಕ್ರಮ, ...) ಮಾಡು {       \
    ಅಕ್ಷರ *str;                                                             \
    ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2;                                                              \
    func_name ## _bprint(BPRINT_ವಾದಗಳು ## ARG_ಕ್ರಮ((bp), __VA_ARGS__));     \
    ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಉದ್ದ((bp)->str) != (bp)->len) {                                  \
        ಬರೆ("strlen of AVBPrint-string returned by "#func_name"_bprint" \
               " differs from AVBPrint.len: %zu vs. %u\n",                 \
               ಅಕ್ಷರಸರಣಿ_ಉದ್ದ((bp)->str), (bp)->len);                              \
        ನಿಲ್ಲಿಸು;                                                             \
    }                                                                      \
    ಗಾತ್ರ_2 = func_name(ORD_ವಾದಗಳು ## ARG_ಕ್ರಮ(ಖಾಲಿ, 0, __VA_ARGS__));         \
    ಆದರೆ (ಗಾತ್ರ_2 <= 0) {                                                       \
        ಬರೆ(#func_name " returned %d\n", ಗಾತ್ರ_2);                         \
        ನಿಲ್ಲಿಸು;                                                             \
    }                                                                      \
    ಆದರೆ ((bp)->len != ಗಾತ್ರ_2 - 1) {                                           \
        ಬರೆ("Return value %d of " #func_name " inconsistent with length"\
               " %u obtained from corresponding bprint version\n",         \
               ಗಾತ್ರ_2, (bp)->len);                                           \
        ನಿಲ್ಲಿಸು;                                                             \
    }                                                                      \
    str = av_malloc(ಗಾತ್ರ_2);                                                 \
    ಆದರೆ (!str) {                                                            \
        ಬರೆ("string of size %d could not be allocated.\n", ಗಾತ್ರ_2);       \
        ನಿಲ್ಲಿಸು;                                                             \
    }                                                                      \
    ಗಾತ್ರ_2 = func_name(ORD_ವಾದಗಳು ## ARG_ಕ್ರಮ(str, ಗಾತ್ರ_2, __VA_ARGS__));       \
    ಆದರೆ (ಗಾತ್ರ_2 <= 0 || (bp)->len != ಗಾತ್ರ_2 - 1) {                              \
        ಬರೆ("Return value %d of " #func_name " inconsistent with length"\
               " %d obtained in first pass.\n", ಗಾತ್ರ_2, (bp)->len);          \
        av_free(str);                                                      \
        ನಿಲ್ಲಿಸು;                                                             \
    }                                                                      \
    ಆದರೆ (strcmp(str, (bp)->str)) {                                          \
        ಬರೆ("Ordinary and _bprint versions of "#func_name" disagree: "  \
               "'%s' vs. '%s'\n", str, (bp)->str);                         \
        av_free(str);                                                      \
        ನಿಲ್ಲಿಸು;                                                             \
    }                                                                      \
    av_free(str);                                                          \
    } ಆಗ (0)


ಸ್ಥಿರ ಶೂನ್ಯ channel_name(AVBPrint *bp, ಎಣಿಕೆ AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_name, 1, channel);
}

ಸ್ಥಿರ ಶೂನ್ಯ channel_description(AVBPrint *bp, ಎಣಿಕೆ AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_description, 1, channel);
}

ಸ್ಥಿರ ಶೂನ್ಯ channel_layout_from_ಮುಖವಾಡ(AVChannelLayout *layout,
                                     AVBPrint *bp, uint64_t channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    ಆದರೆ (!av_channel_layout_from_ಮುಖವಾಡ(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    ಇಲ್ಲದಿದ್ದರೆ
        av_bprintf(bp, "fail");
}

ಸ್ಥಿರ ಶೂನ್ಯ channel_layout_from_string(AVChannelLayout *layout,
                                       AVBPrint *bp, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    ಆದರೆ (!av_channel_layout_from_string(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    ಇಲ್ಲದಿದ್ದರೆ
        av_bprintf(bp, "fail");
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* channel_ಕ್ರಮ_ಹೆಸರುಗಳು[]  = {"UNSPEC", "NATIVE", "CUSTOM", "AMBI"};

ಸ್ಥಿರ ಶೂನ್ಯ describe_type(AVBPrint *bp, AVChannelLayout *layout)
{
    ಆದರೆ ((ಚಿಹ್ನೆರಹಿತ)layout->ಕ್ರಮ < FF_ARRAY_ELEMS(channel_ಕ್ರಮ_ಹೆಸರುಗಳು)) {
        av_bprintf(bp, "%-6s (", channel_ಕ್ರಮ_ಹೆಸರುಗಳು[layout->ಕ್ರಮ]);
        av_channel_layout_describe_bprint(layout, bp);
        av_bprintf(bp, ")");
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_bprintf(bp, "???");
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *channel_layout_retype(AVChannelLayout *layout, AVBPrint *bp, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    ಆದರೆ (!av_channel_layout_from_string(layout, channel_layout) &&
        av_channel_layout_check(layout)) {
        describe_type(bp, layout);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_CHANNEL_ಕ್ರಮ_NB; i++) {
            ಪೂರ್ಣಾಂಕ ret;
            AVChannelLayout copy = {0};
            av_bprintf(bp, "\n ");
            ಆದರೆ (av_channel_layout_copy(&copy, layout) < 0)
                ಹಿಂತಿರುಗಿ "nomem";
            ret = av_channel_layout_retype(&copy, i, 0);
            ಆದರೆ (ret < 0 && (copy.ಕ್ರಮ != layout->ಕ್ರಮ || av_channel_layout_compare(&copy, layout)))
                av_bprintf(bp, "failed to keep existing layout on failure");
            ಆದರೆ (ret >= 0 && copy.ಕ್ರಮ != i)
                av_bprintf(bp, "returned success but did not change order");
            ಆದರೆ (ret == AVERROR(ENOSYS)) {
                av_bprintf(bp, " != %s", channel_ಕ್ರಮ_ಹೆಸರುಗಳು[i]);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ret < 0) {
                av_bprintf(bp, "FAIL");
            } ಇಲ್ಲದಿದ್ದರೆ {
                av_bprintf(bp, " %s ", ret ? "~~" : "==");
                describe_type(bp, &copy);
            }
            av_channel_layout_uninit(&copy);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_bprintf(bp, "fail");
    }
    ಹಿಂತಿರುಗಿ bp->str;
}

#ವ್ಯಾಖ್ಯಾನಿಸು CHANNEL_NAME(x)                                                    \
    channel_name(&bp, (x));                                                \
    ಬರೆ("With %-32s %14s\n", AV_STRINGIFY(x)":", bp.str)

#ವ್ಯಾಖ್ಯಾನಿಸು CHANNEL_DESCRIPTION(x)                                             \
    channel_description(&bp, (x));                                         \
    ಬರೆ("With %-23s %23s\n", AV_STRINGIFY(x)":", bp.str);

#ವ್ಯಾಖ್ಯಾನಿಸು CHANNEL_FROM_STRING(x)                                             \
    ಬರೆ("With %-38s %8d\n", AV_STRINGIFY(x)":", av_channel_from_string(x))

#ವ್ಯಾಖ್ಯಾನಿಸು CHANNEL_LAYOUT_FROM_ಮುಖವಾಡ(x)                                        \
    channel_layout_from_ಮುಖವಾಡ(&layout, &bp, (x));

#ವ್ಯಾಖ್ಯಾನಿಸು CHANNEL_LAYOUT_FROM_STRING(x)                                      \
    channel_layout_from_string(&layout, &bp, (x));                         \
    ಬರೆ("With \"%s\":%*s %32s\n", x, ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(x) > 32 ? 0 : 32 - (ಪೂರ್ಣಾಂಕ)ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(x), "", bp.str);

#ವ್ಯಾಖ್ಯಾನಿಸು CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(l, x)                            \
    ret = av_channel_layout_channel_from_ಸೂಚ್ಯಂಕ(&layout, x);                \
    ಆದರೆ (ret < 0)                                                           \
        ret = -1;                                                          \
    ಬರೆ("On \"%s\" layout with %2d: %8d\n", l,  x, ret)

#ವ್ಯಾಖ್ಯಾನಿಸು CHANNEL_LAYOUT_SUBSET(l, xstr, x)                                  \
    ಮುಖವಾಡ_2 = av_channel_layout_subset(&layout, x);                           \
    ಬರೆ("On \"%s\" layout with %-22s 0x%"PRIx64"\n", l, xstr, ಮುಖವಾಡ_2)

#ವ್ಯಾಖ್ಯಾನಿಸು CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(l, x)                            \
    ret = av_channel_layout_ಸೂಚ್ಯಂಕ_from_channel(&layout, x);                \
    ಆದರೆ (ret < 0)                                                           \
        ret = -1;                                                          \
    ಬರೆ("On \"%s\" layout with %-23s %3d\n", l, AV_STRINGIFY(x)":", ret)

#ವ್ಯಾಖ್ಯಾನಿಸು CHANNEL_LAYOUT_CHANNEL_FROM_STRING(l, x)                           \
    ret = av_channel_layout_channel_from_string(&layout, x);               \
    ಆದರೆ (ret < 0)                                                           \
        ret = -1;                                                          \
    ಬರೆ("On \"%s\" layout with %-21s %3d\n", bp.str, AV_STRINGIFY(x)":", ret);

#ವ್ಯಾಖ್ಯಾನಿಸು CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(l, x)                             \
    ret = av_channel_layout_ಸೂಚ್ಯಂಕ_from_string(&layout, x);                 \
    ಆದರೆ (ret < 0)                                                           \
        ret = -1;                                                          \
    ಬರೆ("On \"%s\" layout with %-20s %3d\n", l, AV_STRINGIFY(x)":", ret);

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಸ್ಥಿರಾಂಕ AVChannelLayout *playout;
    AVChannelLayout layout = { 0 }, layout2 = { 0 };
    AVBPrint bp;
    ಶೂನ್ಯ *iter = ಖಾಲಿ;
    uint64_t ಮುಖವಾಡ_2;
    ಪೂರ್ಣಾಂಕ ret;

    av_bprint_init(&bp, 64, AV_BPRINT_ಗಾತ್ರ_AUTOMATIC);

    ಬರೆ("Testing av_channel_layout_standard\n");
    ಆಗ (playout = av_channel_layout_standard(&iter)) {
        av_channel_layout_describe_bprint(playout, &bp);
        ಬರೆ("%-14s ", bp.str);
        av_bprint_clear(&bp);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 63; i++) {
            ಪೂರ್ಣಾಂಕ idx = av_channel_layout_ಸೂಚ್ಯಂಕ_from_channel(playout, i);
            ಆದರೆ (idx >= 0) {
                ಆದರೆ (idx)
                    av_bprintf(&bp, "+");
                av_channel_name_bprint(&bp, i);
            }
        }
        ಬರೆ("%s\n", bp.str);
        av_bprint_clear(&bp);
    }

    ಬರೆ("\nTesting av_channel_name\n");
    CHANNEL_NAME(AV_CHAN_FRONT_ಎಡ);
    CHANNEL_NAME(AV_CHAN_FRONT_ಬಲ);
    CHANNEL_NAME(63);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_ತಳ);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_ಕೊನೆ);

    ಬರೆ("Testing av_channel_description\n");
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_ಎಡ);
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_ಬಲ);
    CHANNEL_DESCRIPTION(63);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_ತಳ);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_ಕೊನೆ);

    ಬರೆ("\nTesting av_channel_from_string\n");
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

    ಬರೆ("\n==Native layouts==\n");

    ಬರೆ("\nTesting av_channel_layout_from_string\n");
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

    ಬರೆ("\nTesting av_channel_layout_from_mask\n");
    CHANNEL_LAYOUT_FROM_ಮುಖವಾಡ(AV_CH_LAYOUT_5POINT1);
    ಬರೆ("With AV_CH_LAYOUT_5POINT1: %25s\n", bp.str);

    ಬರೆ("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 3);
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 4);
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 5);
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 6);

    ಬರೆ("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ಎಡ);
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ಬಲ);
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_CENTER);
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_ಕೆಳಗಿನ_FREQUENCY);
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_ಎಡ);
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_ಬಲ);
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_ಹಿಂಭಾಗ_CENTER);

    ಬರೆ("\nTesting av_channel_layout_channel_from_string\n");
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

    ಬರೆ("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "FC");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "LFE");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "SL");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "SR");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "BC");

    ಬರೆ("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:",  AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_2POINT1:", AV_CH_LAYOUT_2POINT1);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_4POINT1:", AV_CH_LAYOUT_4POINT1);

    ಬರೆ("\n==Custom layouts==\n");

    ಬರೆ("\nTesting av_channel_layout_from_string\n");
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
    ಆದರೆ (ret < 0) {
        ಬರೆ("Copying channel layout \"FR+FL@Foo+USR63@Foo\" failed; "
               "ret %d\n", ret);
    }
    ret = av_channel_layout_compare(&layout, &layout2);
    ಆದರೆ (ret)
        ಬರೆ("Channel layout and its copy compare unequal; ret: %d\n", ret);

    ಬರೆ("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_STRING(bp.str, "BC");

    ಬರೆ("\nTesting av_channel_layout_channel_from_string\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "BC");

    ಬರೆ("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ಬಲ);
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ಎಡ);
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, 63);
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_ಹಿಂಭಾಗ_CENTER);

    ಬರೆ("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 3);

    ಬರೆ("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    ಬರೆ("\n==Ambisonic layouts==\n");

    ಬರೆ("\nTesting av_channel_layout_from_string\n");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 1");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 2+stereo");

    ಬರೆ("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_AMBISONIC_ತಳ);
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ಎಡ);
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ಬಲ);
    CHANNEL_LAYOUT_ಸೂಚ್ಯಂಕ_FROM_CHANNEL(bp.str, AV_CHAN_ಹಿಂಭಾಗ_CENTER);

    ಬರೆ("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 9);
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 10);
    CHANNEL_LAYOUT_CHANNEL_FROM_ಸೂಚ್ಯಂಕ(bp.str, 11);

    ಬರೆ("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    av_channel_layout_uninit(&layout);
    av_channel_layout_uninit(&layout2);

    ಬರೆ("\nTesting av_channel_layout_retype\n");
    {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* layouts[] = {
            "FL@Boo",
            "stereo",
            "FR+FL",
            "ambisonic 2+stereo",
            "2C",
            ಖಾಲಿ
        };
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; layouts[i]; i++)
            ಬರೆ("With \"%s\": %s\n", layouts[i], channel_layout_retype(&layout, &bp, layouts[i]));
    }
    av_bprint_finalize(&bp, ಖಾಲಿ);

    ಹಿಂತಿರುಗಿ 0;
}
