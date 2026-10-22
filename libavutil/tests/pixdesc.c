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

#ضمن <stdio.h>
#ضمن <string.h>

#ضمن "libavutil/macros.h"
#ضمن "libavutil/pixdesc.h"
#ضمن "libavutil/pixfmt.h"

/*
 * from_name() may legitimately map to a different index when two enum
 * values share the same name string (e.g. AVCOL_PRI_RESERVED0 and
 * AVCOL_PRI_RESERVED both use "reserved"). Accept that as long as
 * name(back) equals name(i).
 */
ساكن صحيح check_name_equivalence(ثابت حرف *name, ثابت حرف *back_name)
{
    أرجع back_name && !strcmp(name, back_name);
}

ساكن صحيح test_pix_fmt_round_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AV_PIX_FMT_NB; i++) {
        ثابت حرف *name = av_get_pix_fmt_name(i);
        𐤀𐤌 (!name)
            استمر;
        𐤀𐤌 (av_get_pix_fmt(name) != i)
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_color_range_round_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCOL_RANGE_NB; i++) {
        ثابت حرف *name = av_color_range_name(i);
        𐤀𐤌 (!name)
            استمر;
        صحيح back = av_color_range_from_name(name);
        𐤀𐤌 (back < 0 || !check_name_equivalence(name, av_color_range_name(back)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_color_primaries_round_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCOL_PRI_NB; i++) {
        ثابت حرف *name = av_color_primaries_name(i);
        𐤀𐤌 (!name)
            استمر;
        صحيح back = av_color_primaries_from_name(name);
        𐤀𐤌 (back < 0 || !check_name_equivalence(name, av_color_primaries_name(back)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_color_transfer_round_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCOL_TRC_NB; i++) {
        ثابت حرف *name = av_color_transfer_name(i);
        𐤀𐤌 (!name)
            استمر;
        صحيح back = av_color_transfer_from_name(name);
        𐤀𐤌 (back < 0 || !check_name_equivalence(name, av_color_transfer_name(back)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_color_space_round_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCOL_SPC_NB; i++) {
        ثابت حرف *name = av_color_space_name(i);
        𐤀𐤌 (!name)
            استمر;
        صحيح back = av_color_space_from_name(name);
        𐤀𐤌 (back < 0 || !check_name_equivalence(name, av_color_space_name(back)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_chroma_location_round_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCHROMA_LOC_NB; i++) {
        ثابت حرف *name = av_chroma_location_name(i);
        𐤀𐤌 (!name)
            استمر;
        صحيح back = av_chroma_location_from_name(name);
        𐤀𐤌 (back < 0 || !check_name_equivalence(name, av_chroma_location_name(back)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_alpha_mode_round_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVALPHA_MODE_NB; i++) {
        ثابت حرف *name = av_alpha_mode_name(i);
        𐤀𐤌 (!name)
            استمر;
        صحيح back = av_alpha_mode_from_name(name);
        𐤀𐤌 (back < 0 || !check_name_equivalence(name, av_alpha_mode_name(back)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_chroma_location_pos_round_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = AVCHROMA_LOC_UNSPECIFIED + 1; i < AVCHROMA_LOC_NB; i++) {
        صحيح xpos, ypos;
        𐤀𐤌 (av_chroma_location_enum_to_pos(&xpos, &ypos, i) < 0) {
            fail++;
            استمر;
        }
        𐤀𐤌 ((صحيح)av_chroma_location_pos_to_enum(xpos, ypos) != i)
            fail++;
    }
    أرجع fail;
}

صحيح main(فراغ)
{
    صحيح skip = 0;

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
    لكل (صحيح i = 0; i < AV_PIX_FMT_NB * 2; i++) {
        ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        𐤀𐤌 (!desc || !desc->name) {
            skip++;
            استمر;
        }
        𐤀𐤌 (skip) {
            printf("  %3d unused pixel format values\n", skip);
            skip = 0;
        }
        printf("  pix fmt %s avg_bpp:%d planes:%d\n", desc->name,
               av_get_padded_bits_per_pixel(desc),
               av_pix_fmt_count_planes(i));
    }

    أرجع 0;
}
