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

#ਅਨ੍ਤਰ੍ਭਾਵ <inttypes.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/bprint.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/channel_layout.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BPRINT_ARGS1(bp, ...)     (bp), __VA_ARGS__
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BPRINT_ARGS0(bp, ...)     __VA_ARGS__, (bp)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ORD_ARGS1(str, ਮਾਪ, ...) (str), (ਮਾਪ), __VA_ARGS__
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ORD_ARGS0(str, ਮਾਪ, ...) __VA_ARGS__, (str), (ਮਾਪ)

// This macro presumes the AVBPrint to have been cleared before usage.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CMP_BPRINT_AND_NONBPRINT(bp, func_name, ARG_ਕ੍ਰਮ, ...) ਕਰੋ {       \
    ਅੱਖਰ *str;                                                             \
    ਪੂਰਨ ਮਾਪ;                                                              \
    func_name ## _bprint(BPRINT_ਦਲੀਲਾਂ ## ARG_ਕ੍ਰਮ((bp), __VA_ARGS__));     \
    ਜੇ (ਲੜੀ_ਲੰਬਾਈ((bp)->str) != (bp)->len) {                                  \
        ਲਿਖੋ("strlen of AVBPrint-string returned by "#func_name"_bprint" \
               " differs from AVBPrint.len: %zu vs. %u\n",                 \
               ਲੜੀ_ਲੰਬਾਈ((bp)->str), (bp)->len);                              \
        ਰੋਕੋ;                                                             \
    }                                                                      \
    ਮਾਪ = func_name(ORD_ਦਲੀਲਾਂ ## ARG_ਕ੍ਰਮ(ਨਿਰਾ, 0, __VA_ARGS__));         \
    ਜੇ (ਮਾਪ <= 0) {                                                       \
        ਲਿਖੋ(#func_name " returned %d\n", ਮਾਪ);                         \
        ਰੋਕੋ;                                                             \
    }                                                                      \
    ਜੇ ((bp)->len != ਮਾਪ - 1) {                                           \
        ਲਿਖੋ("Return value %d of " #func_name " inconsistent with length"\
               " %u obtained from corresponding bprint version\n",         \
               ਮਾਪ, (bp)->len);                                           \
        ਰੋਕੋ;                                                             \
    }                                                                      \
    str = av_malloc(ਮਾਪ);                                                 \
    ਜੇ (!str) {                                                            \
        ਲਿਖੋ("string of size %d could not be allocated.\n", ਮਾਪ);       \
        ਰੋਕੋ;                                                             \
    }                                                                      \
    ਮਾਪ = func_name(ORD_ਦਲੀਲਾਂ ## ARG_ਕ੍ਰਮ(str, ਮਾਪ, __VA_ARGS__));       \
    ਜੇ (ਮਾਪ <= 0 || (bp)->len != ਮਾਪ - 1) {                              \
        ਲਿਖੋ("Return value %d of " #func_name " inconsistent with length"\
               " %d obtained in first pass.\n", ਮਾਪ, (bp)->len);          \
        av_free(str);                                                      \
        ਰੋਕੋ;                                                             \
    }                                                                      \
    ਜੇ (strcmp(str, (bp)->str)) {                                          \
        ਲਿਖੋ("Ordinary and _bprint versions of "#func_name" disagree: "  \
               "'%s' vs. '%s'\n", str, (bp)->str);                         \
        av_free(str);                                                      \
        ਰੋਕੋ;                                                             \
    }                                                                      \
    av_free(str);                                                          \
    } ਜਦੋਂ (0)


ਸਥਿਰ ਖਾਲੀ channel_name(AVBPrint *bp, ਗਿਣਤੀ AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_name, 1, channel);
}

ਸਥਿਰ ਖਾਲੀ channel_description(AVBPrint *bp, ਗਿਣਤੀ AVChannel channel)
{
    av_bprint_clear(bp);
    CMP_BPRINT_AND_NONBPRINT(bp, av_channel_description, 1, channel);
}

ਸਥਿਰ ਖਾਲੀ channel_layout_from_ਨਕਾਬ(AVChannelLayout *layout,
                                     AVBPrint *bp, uint64_t channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    ਜੇ (!av_channel_layout_from_ਨਕਾਬ(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    ਨਹੀਂਤਾਂ
        av_bprintf(bp, "fail");
}

ਸਥਿਰ ਖਾਲੀ channel_layout_from_string(AVChannelLayout *layout,
                                       AVBPrint *bp, ਅਚਲ ਅੱਖਰ *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    ਜੇ (!av_channel_layout_from_string(layout, channel_layout) &&
         av_channel_layout_check(layout))
        CMP_BPRINT_AND_NONBPRINT(bp, av_channel_layout_describe, 0, layout);
    ਨਹੀਂਤਾਂ
        av_bprintf(bp, "fail");
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ* channel_ਕ੍ਰਮ_ਨਾਂ[]  = {"UNSPEC", "NATIVE", "CUSTOM", "AMBI"};

ਸਥਿਰ ਖਾਲੀ describe_type(AVBPrint *bp, AVChannelLayout *layout)
{
    ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)layout->ਕ੍ਰਮ < FF_ARRAY_ELEMS(channel_ਕ੍ਰਮ_ਨਾਂ)) {
        av_bprintf(bp, "%-6s (", channel_ਕ੍ਰਮ_ਨਾਂ[layout->ਕ੍ਰਮ]);
        av_channel_layout_describe_bprint(layout, bp);
        av_bprintf(bp, ")");
    } ਨਹੀਂਤਾਂ {
        av_bprintf(bp, "???");
    }
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *channel_layout_retype(AVChannelLayout *layout, AVBPrint *bp, ਅਚਲ ਅੱਖਰ *channel_layout)
{
    av_channel_layout_uninit(layout);
    av_bprint_clear(bp);
    ਜੇ (!av_channel_layout_from_string(layout, channel_layout) &&
        av_channel_layout_check(layout)) {
        describe_type(bp, layout);
        ਲਈ (ਪੂਰਨ i = 0; i < FF_CHANNEL_ਕ੍ਰਮ_NB; i++) {
            ਪੂਰਨ ret;
            AVChannelLayout copy = {0};
            av_bprintf(bp, "\n ");
            ਜੇ (av_channel_layout_copy(&copy, layout) < 0)
                ਵਾਪਸ "nomem";
            ret = av_channel_layout_retype(&copy, i, 0);
            ਜੇ (ret < 0 && (copy.ਕ੍ਰਮ != layout->ਕ੍ਰਮ || av_channel_layout_compare(&copy, layout)))
                av_bprintf(bp, "failed to keep existing layout on failure");
            ਜੇ (ret >= 0 && copy.ਕ੍ਰਮ != i)
                av_bprintf(bp, "returned success but did not change order");
            ਜੇ (ret == AVERROR(ENOSYS)) {
                av_bprintf(bp, " != %s", channel_ਕ੍ਰਮ_ਨਾਂ[i]);
            } ਨਹੀਂਤਾਂ ਜੇ (ret < 0) {
                av_bprintf(bp, "FAIL");
            } ਨਹੀਂਤਾਂ {
                av_bprintf(bp, " %s ", ret ? "~~" : "==");
                describe_type(bp, &copy);
            }
            av_channel_layout_uninit(&copy);
        }
    } ਨਹੀਂਤਾਂ {
        av_bprintf(bp, "fail");
    }
    ਵਾਪਸ bp->str;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHANNEL_NAME(x)                                                    \
    channel_name(&bp, (x));                                                \
    ਲਿਖੋ("With %-32s %14s\n", AV_STRINGIFY(x)":", bp.str)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHANNEL_DESCRIPTION(x)                                             \
    channel_description(&bp, (x));                                         \
    ਲਿਖੋ("With %-23s %23s\n", AV_STRINGIFY(x)":", bp.str);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHANNEL_FROM_STRING(x)                                             \
    ਲਿਖੋ("With %-38s %8d\n", AV_STRINGIFY(x)":", av_channel_from_string(x))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHANNEL_LAYOUT_FROM_ਨਕਾਬ(x)                                        \
    channel_layout_from_ਨਕਾਬ(&layout, &bp, (x));

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHANNEL_LAYOUT_FROM_STRING(x)                                      \
    channel_layout_from_string(&layout, &bp, (x));                         \
    ਲਿਖੋ("With \"%s\":%*s %32s\n", x, ਲੜੀ_ਲੰਬਾਈ(x) > 32 ? 0 : 32 - (ਪੂਰਨ)ਲੜੀ_ਲੰਬਾਈ(x), "", bp.str);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(l, x)                            \
    ret = av_channel_layout_channel_from_ਸੂਚਕਾਂਕ(&layout, x);                \
    ਜੇ (ret < 0)                                                           \
        ret = -1;                                                          \
    ਲਿਖੋ("On \"%s\" layout with %2d: %8d\n", l,  x, ret)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHANNEL_LAYOUT_SUBSET(l, xstr, x)                                  \
    ਨਕਾਬ_2 = av_channel_layout_subset(&layout, x);                           \
    ਲਿਖੋ("On \"%s\" layout with %-22s 0x%"PRIx64"\n", l, xstr, ਨਕਾਬ_2)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(l, x)                            \
    ret = av_channel_layout_ਸੂਚਕਾਂਕ_from_channel(&layout, x);                \
    ਜੇ (ret < 0)                                                           \
        ret = -1;                                                          \
    ਲਿਖੋ("On \"%s\" layout with %-23s %3d\n", l, AV_STRINGIFY(x)":", ret)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHANNEL_LAYOUT_CHANNEL_FROM_STRING(l, x)                           \
    ret = av_channel_layout_channel_from_string(&layout, x);               \
    ਜੇ (ret < 0)                                                           \
        ret = -1;                                                          \
    ਲਿਖੋ("On \"%s\" layout with %-21s %3d\n", bp.str, AV_STRINGIFY(x)":", ret);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(l, x)                             \
    ret = av_channel_layout_ਸੂਚਕਾਂਕ_from_string(&layout, x);                 \
    ਜੇ (ret < 0)                                                           \
        ret = -1;                                                          \
    ਲਿਖੋ("On \"%s\" layout with %-20s %3d\n", l, AV_STRINGIFY(x)":", ret);

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਅਚਲ AVChannelLayout *playout;
    AVChannelLayout layout = { 0 }, layout2 = { 0 };
    AVBPrint bp;
    ਖਾਲੀ *iter = ਨਿਰਾ;
    uint64_t ਨਕਾਬ_2;
    ਪੂਰਨ ret;

    av_bprint_init(&bp, 64, AV_BPRINT_ਮਾਪ_AUTOMATIC);

    ਲਿਖੋ("Testing av_channel_layout_standard\n");
    ਜਦੋਂ (playout = av_channel_layout_standard(&iter)) {
        av_channel_layout_describe_bprint(playout, &bp);
        ਲਿਖੋ("%-14s ", bp.str);
        av_bprint_clear(&bp);
        ਲਈ (ਪੂਰਨ i = 0; i < 63; i++) {
            ਪੂਰਨ idx = av_channel_layout_ਸੂਚਕਾਂਕ_from_channel(playout, i);
            ਜੇ (idx >= 0) {
                ਜੇ (idx)
                    av_bprintf(&bp, "+");
                av_channel_name_bprint(&bp, i);
            }
        }
        ਲਿਖੋ("%s\n", bp.str);
        av_bprint_clear(&bp);
    }

    ਲਿਖੋ("\nTesting av_channel_name\n");
    CHANNEL_NAME(AV_CHAN_FRONT_ਖੱਬਾ);
    CHANNEL_NAME(AV_CHAN_FRONT_ਸੱਜਾ);
    CHANNEL_NAME(63);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_ਅਧਾਰ);
    CHANNEL_NAME(AV_CHAN_AMBISONIC_ਸਿਰਾ);

    ਲਿਖੋ("Testing av_channel_description\n");
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_ਖੱਬਾ);
    CHANNEL_DESCRIPTION(AV_CHAN_FRONT_ਸੱਜਾ);
    CHANNEL_DESCRIPTION(63);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_ਅਧਾਰ);
    CHANNEL_DESCRIPTION(AV_CHAN_AMBISONIC_ਸਿਰਾ);

    ਲਿਖੋ("\nTesting av_channel_from_string\n");
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

    ਲਿਖੋ("\n==Native layouts==\n");

    ਲਿਖੋ("\nTesting av_channel_layout_from_string\n");
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

    ਲਿਖੋ("\nTesting av_channel_layout_from_mask\n");
    CHANNEL_LAYOUT_FROM_ਨਕਾਬ(AV_CH_LAYOUT_5POINT1);
    ਲਿਖੋ("With AV_CH_LAYOUT_5POINT1: %25s\n", bp.str);

    ਲਿਖੋ("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 3);
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 4);
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 5);
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 6);

    ਲਿਖੋ("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ਖੱਬਾ);
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ਸੱਜਾ);
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_CENTER);
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_ਨੀਵਾਂ_FREQUENCY);
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_ਖੱਬਾ);
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_SIDE_ਸੱਜਾ);
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_ਪਿੱਠ_CENTER);

    ਲਿਖੋ("\nTesting av_channel_layout_channel_from_string\n");
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

    ਲਿਖੋ("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "FC");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "LFE");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "SL");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "SR");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "BC");

    ਲਿਖੋ("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:",  AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_2POINT1:", AV_CH_LAYOUT_2POINT1);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_4POINT1:", AV_CH_LAYOUT_4POINT1);

    ਲਿਖੋ("\n==Custom layouts==\n");

    ਲਿਖੋ("\nTesting av_channel_layout_from_string\n");
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
    ਜੇ (ret < 0) {
        ਲਿਖੋ("Copying channel layout \"FR+FL@Foo+USR63@Foo\" failed; "
               "ret %d\n", ret);
    }
    ret = av_channel_layout_compare(&layout, &layout2);
    ਜੇ (ret)
        ਲਿਖੋ("Channel layout and its copy compare unequal; ret: %d\n", ret);

    ਲਿਖੋ("\nTesting av_channel_layout_index_from_string\n");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_STRING(bp.str, "BC");

    ਲਿਖੋ("\nTesting av_channel_layout_channel_from_string\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FR@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "FL@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "USR63@Foo");
    CHANNEL_LAYOUT_CHANNEL_FROM_STRING(bp.str, "BC");

    ਲਿਖੋ("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ਸੱਜਾ);
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ਖੱਬਾ);
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, 63);
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_ਪਿੱਠ_CENTER);

    ਲਿਖੋ("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 1);
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 2);
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 3);

    ਲਿਖੋ("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    ਲਿਖੋ("\n==Ambisonic layouts==\n");

    ਲਿਖੋ("\nTesting av_channel_layout_from_string\n");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 1");
    CHANNEL_LAYOUT_FROM_STRING("ambisonic 2+stereo");

    ਲਿਖੋ("\nTesting av_channel_layout_index_from_channel\n");
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_AMBISONIC_ਅਧਾਰ);
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ਖੱਬਾ);
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_FRONT_ਸੱਜਾ);
    CHANNEL_LAYOUT_ਸੂਚਕਾਂਕ_FROM_CHANNEL(bp.str, AV_CHAN_ਪਿੱਠ_CENTER);

    ਲਿਖੋ("\nTesting av_channel_layout_channel_from_index\n");
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 0);
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 9);
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 10);
    CHANNEL_LAYOUT_CHANNEL_FROM_ਸੂਚਕਾਂਕ(bp.str, 11);

    ਲਿਖੋ("\nTesting av_channel_layout_subset\n");
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_STEREO:", AV_CH_LAYOUT_STEREO);
    CHANNEL_LAYOUT_SUBSET(bp.str, "AV_CH_LAYOUT_QUAD:", AV_CH_LAYOUT_QUAD);

    av_channel_layout_uninit(&layout);
    av_channel_layout_uninit(&layout2);

    ਲਿਖੋ("\nTesting av_channel_layout_retype\n");
    {
        ਅਚਲ ਅੱਖਰ* layouts[] = {
            "FL@Boo",
            "stereo",
            "FR+FL",
            "ambisonic 2+stereo",
            "2C",
            ਨਿਰਾ
        };
        ਲਈ (ਪੂਰਨ i = 0; layouts[i]; i++)
            ਲਿਖੋ("With \"%s\": %s\n", layouts[i], channel_layout_retype(&layout, &bp, layouts[i]));
    }
    av_bprint_finalize(&bp, ਨਿਰਾ);

    ਵਾਪਸ 0;
}
