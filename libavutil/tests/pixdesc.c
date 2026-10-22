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
ساكن صحيح check_name_equivalence(ثابت حرف *name, ثابت حرف *پٹھ_name)
{
    أرجع پٹھ_name && !strcmp(name, پٹھ_name);
}

ساكن صحيح test_pix_fmt_گیڑا_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AV_PIX_FMT_NB; i++) {
        ثابت حرف *name = av_get_pix_fmt_name(i);
        إذا (!name)
            استمر;
        إذا (av_get_pix_fmt(name) != i)
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_color_range_گیڑا_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCOL_RANGE_NB; i++) {
        ثابت حرف *name = av_color_range_name(i);
        إذا (!name)
            استمر;
        صحيح پٹھ = av_color_range_from_name(name);
        إذا (پٹھ < 0 || !check_name_equivalence(name, av_color_range_name(پٹھ)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_color_primaries_گیڑا_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCOL_PRI_NB; i++) {
        ثابت حرف *name = av_color_primaries_name(i);
        إذا (!name)
            استمر;
        صحيح پٹھ = av_color_primaries_from_name(name);
        إذا (پٹھ < 0 || !check_name_equivalence(name, av_color_primaries_name(پٹھ)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_color_transfer_گیڑا_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCOL_TRC_NB; i++) {
        ثابت حرف *name = av_color_transfer_name(i);
        إذا (!name)
            استمر;
        صحيح پٹھ = av_color_transfer_from_name(name);
        إذا (پٹھ < 0 || !check_name_equivalence(name, av_color_transfer_name(پٹھ)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_color_space_گیڑا_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCOL_SPC_NB; i++) {
        ثابت حرف *name = av_color_space_name(i);
        إذا (!name)
            استمر;
        صحيح پٹھ = av_color_space_from_name(name);
        إذا (پٹھ < 0 || !check_name_equivalence(name, av_color_space_name(پٹھ)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_chroma_location_گیڑا_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCHROMA_LOC_NB; i++) {
        ثابت حرف *name = av_chroma_location_name(i);
        إذا (!name)
            استمر;
        صحيح پٹھ = av_chroma_location_from_name(name);
        إذا (پٹھ < 0 || !check_name_equivalence(name, av_chroma_location_name(پٹھ)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_alpha_منوال_گیڑا_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVALPHA_منوال_NB; i++) {
        ثابت حرف *name = av_alpha_منوال_name(i);
        إذا (!name)
            استمر;
        صحيح پٹھ = av_alpha_منوال_from_name(name);
        إذا (پٹھ < 0 || !check_name_equivalence(name, av_alpha_منوال_name(پٹھ)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_chroma_location_pos_گیڑا_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = AVCHROMA_LOC_UNSPECIFIED + 1; i < AVCHROMA_LOC_NB; i++) {
        صحيح xpos, ypos;
        إذا (av_chroma_location_enum_منزل_pos(&xpos, &ypos, i) < 0) {
            fail++;
            استمر;
        }
        إذا ((صحيح)av_chroma_location_pos_منزل_enum(xpos, ypos) != i)
            fail++;
    }
    أرجع fail;
}

صحيح مکھ(فراغ)
{
    صحيح skip = 0;

    لکھو("Testing av_get_pix_fmt() / av_get_pix_fmt_name() round-trip\n");
    لکھو("  result: %s\n",
           test_pix_fmt_گیڑا_trip() ? "FAIL" : "OK");

    لکھو("\nTesting av_color_*_name() / av_color_*_from_name() round-trips\n");
    لکھو("  av_color_range:     %s\n",
           test_color_range_گیڑا_trip()     ? "FAIL" : "OK");
    لکھو("  av_color_primaries: %s\n",
           test_color_primaries_گیڑا_trip() ? "FAIL" : "OK");
    لکھو("  av_color_transfer:  %s\n",
           test_color_transfer_گیڑا_trip()  ? "FAIL" : "OK");
    لکھو("  av_color_space:     %s\n",
           test_color_space_گیڑا_trip()     ? "FAIL" : "OK");
    لکھو("  av_chroma_location: %s\n",
           test_chroma_location_گیڑا_trip() ? "FAIL" : "OK");
    لکھو("  av_alpha_mode:      %s\n",
           test_alpha_منوال_گیڑا_trip()      ? "FAIL" : "OK");

    لکھو("\nTesting av_chroma_location_enum_to_pos / pos_to_enum round-trip\n");
    لکھو("  result: %s\n",
           test_chroma_location_pos_گیڑا_trip() ? "FAIL" : "OK");

    لکھو("\nTesting pixel format descriptors\n");
    لكل (صحيح i = 0; i < AV_PIX_FMT_NB * 2; i++) {
        ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        إذا (!desc || !desc->name) {
            skip++;
            استمر;
        }
        إذا (skip) {
            لکھو("  %3d unused pixel format values\n", skip);
            skip = 0;
        }
        لکھو("  pix fmt %s avg_bpp:%d planes:%d\n", desc->name,
               av_get_padded_بٹ_فی_pixel(desc),
               av_pix_fmt_گنتی_planes(i));
    }

    أرجع 0;
}
