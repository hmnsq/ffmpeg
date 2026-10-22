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
ساكن صحيح check_name_equivalence(ثابت حرف *name, ثابت حرف *پشت_name)
{
    أرجع پشت_name && !strcmp(name, پشت_name);
}

ساكن صحيح test_pix_fmt_دور_trip(فراغ)
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

ساكن صحيح test_color_range_دور_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCOL_RANGE_NB; i++) {
        ثابت حرف *name = av_color_range_name(i);
        إذا (!name)
            استمر;
        صحيح پشت = av_color_range_from_name(name);
        إذا (پشت < 0 || !check_name_equivalence(name, av_color_range_name(پشت)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_color_primaries_دور_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCOL_PRI_NB; i++) {
        ثابت حرف *name = av_color_primaries_name(i);
        إذا (!name)
            استمر;
        صحيح پشت = av_color_primaries_from_name(name);
        إذا (پشت < 0 || !check_name_equivalence(name, av_color_primaries_name(پشت)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_color_transfer_دور_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCOL_TRC_NB; i++) {
        ثابت حرف *name = av_color_transfer_name(i);
        إذا (!name)
            استمر;
        صحيح پشت = av_color_transfer_from_name(name);
        إذا (پشت < 0 || !check_name_equivalence(name, av_color_transfer_name(پشت)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_color_space_دور_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCOL_SPC_NB; i++) {
        ثابت حرف *name = av_color_space_name(i);
        إذا (!name)
            استمر;
        صحيح پشت = av_color_space_from_name(name);
        إذا (پشت < 0 || !check_name_equivalence(name, av_color_space_name(پشت)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_chroma_location_دور_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVCHROMA_LOC_NB; i++) {
        ثابت حرف *name = av_chroma_location_name(i);
        إذا (!name)
            استمر;
        صحيح پشت = av_chroma_location_from_name(name);
        إذا (پشت < 0 || !check_name_equivalence(name, av_chroma_location_name(پشت)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_alpha_نما_دور_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = 0; i < AVALPHA_نما_NB; i++) {
        ثابت حرف *name = av_alpha_نما_name(i);
        إذا (!name)
            استمر;
        صحيح پشت = av_alpha_نما_from_name(name);
        إذا (پشت < 0 || !check_name_equivalence(name, av_alpha_نما_name(پشت)))
            fail++;
    }
    أرجع fail;
}

ساكن صحيح test_chroma_location_pos_دور_trip(فراغ)
{
    صحيح fail = 0;
    لكل (صحيح i = AVCHROMA_LOC_UNSPECIFIED + 1; i < AVCHROMA_LOC_NB; i++) {
        صحيح xpos, ypos;
        إذا (av_chroma_location_enum_مقصد_pos(&xpos, &ypos, i) < 0) {
            fail++;
            استمر;
        }
        إذا ((صحيح)av_chroma_location_pos_مقصد_enum(xpos, ypos) != i)
            fail++;
    }
    أرجع fail;
}

صحيح اصلی(فراغ)
{
    صحيح skip = 0;

    چاپ_کن("Testing av_get_pix_fmt() / av_get_pix_fmt_name() round-trip\n");
    چاپ_کن("  result: %s\n",
           test_pix_fmt_دور_trip() ? "FAIL" : "OK");

    چاپ_کن("\nTesting av_color_*_name() / av_color_*_from_name() round-trips\n");
    چاپ_کن("  av_color_range:     %s\n",
           test_color_range_دور_trip()     ? "FAIL" : "OK");
    چاپ_کن("  av_color_primaries: %s\n",
           test_color_primaries_دور_trip() ? "FAIL" : "OK");
    چاپ_کن("  av_color_transfer:  %s\n",
           test_color_transfer_دور_trip()  ? "FAIL" : "OK");
    چاپ_کن("  av_color_space:     %s\n",
           test_color_space_دور_trip()     ? "FAIL" : "OK");
    چاپ_کن("  av_chroma_location: %s\n",
           test_chroma_location_دور_trip() ? "FAIL" : "OK");
    چاپ_کن("  av_alpha_mode:      %s\n",
           test_alpha_نما_دور_trip()      ? "FAIL" : "OK");

    چاپ_کن("\nTesting av_chroma_location_enum_to_pos / pos_to_enum round-trip\n");
    چاپ_کن("  result: %s\n",
           test_chroma_location_pos_دور_trip() ? "FAIL" : "OK");

    چاپ_کن("\nTesting pixel format descriptors\n");
    لكل (صحيح i = 0; i < AV_PIX_FMT_NB * 2; i++) {
        ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        إذا (!desc || !desc->name) {
            skip++;
            استمر;
        }
        إذا (skip) {
            چاپ_کن("  %3d unused pixel format values\n", skip);
            skip = 0;
        }
        چاپ_کن("  pix fmt %s avg_bpp:%d planes:%d\n", desc->name,
               av_get_padded_بیتها_در_هر_pixel(desc),
               av_pix_fmt_شمار_planes(i));
    }

    أرجع 0;
}
