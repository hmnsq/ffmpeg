/*
 * pixel format descriptor
 * Copyright (c) 2009 Michael Niedermayer <michaelni@gmx.at>
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

#include <stdio.h>
#include <string.h>

#include "libavutil/macros.h"
#include "libavutil/pixdesc.h"
#include "libavutil/pixfmt.h"

/*
 * from_name() may legitimately map to a different index when two enum
 * values share the same name string (e.g. AVCOL_PRI_RESERVED0 and
 * AVCOL_PRI_RESERVED both use "reserved"). Accept that as long as
 * name(back) equals name(i).
 */
static ကိန်းပြည့် check_name_equivalence(const var_na *name, const var_na *back_name)
{
    ပြန်ပေး back_name && !strcmp(name, back_name);
}

static ကိန်းပြည့် test_pix_fmt_round_trip(void)
{
    ကိန်းပြည့် fail = 0;
    အတွက် (ကိန်းပြည့် i = 0; i < AV_PIX_FMT_NB; i++) {
        const var_na *name = av_get_pix_fmt_name(i);
        အကယ်၍ (!name)
            continue;
        အကယ်၍ (av_get_pix_fmt(name) != i)
            fail++;
    }
    ပြန်ပေး fail;
}

static ကိန်းပြည့် test_color_range_round_trip(void)
{
    ကိန်းပြည့် fail = 0;
    အတွက် (ကိန်းပြည့် i = 0; i < AVCOL_RANGE_NB; i++) {
        const var_na *name = av_color_range_name(i);
        အကယ်၍ (!name)
            continue;
        ကိန်းပြည့် back = av_color_range_from_name(name);
        အကယ်၍ (back < 0 || !check_name_equivalence(name, av_color_range_name(back)))
            fail++;
    }
    ပြန်ပေး fail;
}

static ကိန်းပြည့် test_color_primaries_round_trip(void)
{
    ကိန်းပြည့် fail = 0;
    အတွက် (ကိန်းပြည့် i = 0; i < AVCOL_PRI_NB; i++) {
        const var_na *name = av_color_primaries_name(i);
        အကယ်၍ (!name)
            continue;
        ကိန်းပြည့် back = av_color_primaries_from_name(name);
        အကယ်၍ (back < 0 || !check_name_equivalence(name, av_color_primaries_name(back)))
            fail++;
    }
    ပြန်ပေး fail;
}

static ကိန်းပြည့် test_color_transfer_round_trip(void)
{
    ကိန်းပြည့် fail = 0;
    အတွက် (ကိန်းပြည့် i = 0; i < AVCOL_TRC_NB; i++) {
        const var_na *name = av_color_transfer_name(i);
        အကယ်၍ (!name)
            continue;
        ကိန်းပြည့် back = av_color_transfer_from_name(name);
        အကယ်၍ (back < 0 || !check_name_equivalence(name, av_color_transfer_name(back)))
            fail++;
    }
    ပြန်ပေး fail;
}

static ကိန်းပြည့် test_color_space_round_trip(void)
{
    ကိန်းပြည့် fail = 0;
    အတွက် (ကိန်းပြည့် i = 0; i < AVCOL_SPC_NB; i++) {
        const var_na *name = av_color_space_name(i);
        အကယ်၍ (!name)
            continue;
        ကိန်းပြည့် back = av_color_space_from_name(name);
        အကယ်၍ (back < 0 || !check_name_equivalence(name, av_color_space_name(back)))
            fail++;
    }
    ပြန်ပေး fail;
}

static ကိန်းပြည့် test_chroma_location_round_trip(void)
{
    ကိန်းပြည့် fail = 0;
    အတွက် (ကိန်းပြည့် i = 0; i < AVCHROMA_LOC_NB; i++) {
        const var_na *name = av_chroma_location_name(i);
        အကယ်၍ (!name)
            continue;
        ကိန်းပြည့် back = av_chroma_location_from_name(name);
        အကယ်၍ (back < 0 || !check_name_equivalence(name, av_chroma_location_name(back)))
            fail++;
    }
    ပြန်ပေး fail;
}

static ကိန်းပြည့် test_alpha_mode_round_trip(void)
{
    ကိန်းပြည့် fail = 0;
    အတွက် (ကိန်းပြည့် i = 0; i < AVALPHA_MODE_NB; i++) {
        const var_na *name = av_alpha_mode_name(i);
        အကယ်၍ (!name)
            continue;
        ကိန်းပြည့် back = av_alpha_mode_from_name(name);
        အကယ်၍ (back < 0 || !check_name_equivalence(name, av_alpha_mode_name(back)))
            fail++;
    }
    ပြန်ပေး fail;
}

static ကိန်းပြည့် test_chroma_location_pos_round_trip(void)
{
    ကိန်းပြည့် fail = 0;
    အတွက် (ကိန်းပြည့် i = AVCHROMA_LOC_UNSPECIFIED + 1; i < AVCHROMA_LOC_NB; i++) {
        ကိန်းပြည့် xpos, ypos;
        အကယ်၍ (av_chroma_location_enum_to_pos(&xpos, &ypos, i) < 0) {
            fail++;
            continue;
        }
        အကယ်၍ ((ကိန်းပြည့်)av_chroma_location_pos_to_enum(xpos, ypos) != i)
            fail++;
    }
    ပြန်ပေး fail;
}

ကိန်းပြည့် main(void)
{
    ကိန်းပြည့် skip = 0;

    printf("Testing av_get_pix_fmt() / av_get_pix_fmt_name() round-trip\n");
    printf("  result: %s\n",
           test_pix_fmt_round_trip() ? "FAIL" : "OK");

    printf("\nTesting av_color_*_name() / av_color_*_from_name() round-trips\n");
    printf("  av_color_range:     %s\n",
           test_color_range_round_trip()     ? "FAIL" : "OK");
    printf("  av_color_primaries: %s\n",
           test_color_primaries_round_trip() ? "FAIL" : "OK");
    printf("  av_color_transfer:  %s\n",
           test_color_transfer_round_trip()  ? "FAIL" : "OK");
    printf("  av_color_space:     %s\n",
           test_color_space_round_trip()     ? "FAIL" : "OK");
    printf("  av_chroma_location: %s\n",
           test_chroma_location_round_trip() ? "FAIL" : "OK");
    printf("  av_alpha_mode:      %s\n",
           test_alpha_mode_round_trip()      ? "FAIL" : "OK");

    printf("\nTesting av_chroma_location_enum_to_pos / pos_to_enum round-trip\n");
    printf("  result: %s\n",
           test_chroma_location_pos_round_trip() ? "FAIL" : "OK");

    printf("\nTesting pixel format descriptors\n");
    အတွက် (ကိန်းပြည့် i = 0; i < AV_PIX_FMT_NB * 2; i++) {
        const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        အကယ်၍ (!desc || !desc->name) {
            skip++;
            continue;
        }
        အကယ်၍ (skip) {
            printf("  %3d unused pixel format values\n", skip);
            skip = 0;
        }
        printf("  pix fmt %s avg_bpp:%d planes:%d\n", desc->name,
               av_get_padded_bits_per_pixel(desc),
               av_pix_fmt_count_planes(i));
    }

    ပြန်ပေး 0;
}
